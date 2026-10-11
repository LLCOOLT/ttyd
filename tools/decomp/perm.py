"""perm.py <src.c> <symbol> <template.c> [--decl NAME:var1,var2,...] [--max N]

Compiles a mini translation unit (prelude of <src.c> up to the first function
+ template) and scores <symbol> against the original object, ignoring
relocation symbol names. Template may contain {NAME} placeholders; with --decl,
every permutation of the comma list is substituted as 'f32 a, b, c;'.
Prints best candidates."""
import itertools, json, os, re, subprocess, sys, tempfile

src, sym, tmpl_path = sys.argv[1:4]
args = sys.argv[4:]
decls = {}
sep = {}
maxn = 100000
cutmark = '// clang-format off'
i = 0
while i < len(args):
    if args[i] == '--decl':
        name, vs = args[i + 1].split(':', 1)
        decls[name] = vs.split(';') if ';' in vs else vs.split(',')
        if ';' in vs:
            sep[name] = ';\n    '
        else:
            sep[name] = ', '
        i += 2
    elif args[i] == '--cut':
        cutmark = args[i + 1]; i += 2
    elif args[i] == '--max':
        maxn = int(args[i + 1]); i += 2
    else:
        raise SystemExit('bad arg ' + args[i])

text = open(src, encoding='utf-8').read()
cut = text.index(cutmark)
prelude = text[:cut]
tmpl = open(tmpl_path, encoding='utf-8').read()
unit = src.replace('\\', '/').split('src/', 1)[1][:-2]
target = f'build/G8MJ01/obj/{unit}.o'

compile_cmd = None
out = subprocess.run([sys.executable, '-m', 'ninja', '-t', 'commands', f'build/G8MJ01/src/{unit}.o'],
                     capture_output=True, text=True).stdout.strip().splitlines()[-1]
tmpdir = tempfile.mkdtemp(prefix='perm')
cfile = os.path.join(tmpdir, 'mini.c')
ofile = os.path.join(tmpdir, 'mini.o')
cmd = out.replace('src\\' + unit.replace('/', '\\') + '.c', cfile).split(' -o ')[0] + ' -o ' + ofile
cmd = cmd.replace(' -MMD', '')

STRIP = re.compile(r'([A-Za-z_@$.][\w@$.]*)@(sda21|ha|l)')
def norm(s):
    s = STRIP.sub(r'SYM@\2', s)
    s = re.sub(r'^(bl?) \S+', r'\1 X', s)
    s = re.sub(r'^(b\w*) 0x[0-9a-f]+', r'\1 L', s)
    return s

def insns(d, side):
    for s in d.get(side, {}).get('symbols', []):
        if s.get('name') == sym:
            return [norm(x.get('instruction', {}).get('formatted', '')) for x in s.get('instructions', [])]
    return None

def score(code):
    open(cfile, 'w', encoding='utf-8').write(prelude + code)
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    if r.returncode:
        return -1, r.stdout[-800:] + r.stderr[-800:]
    j = os.path.join(tmpdir, 'd.json')
    subprocess.run([os.path.join('build', 'tools', 'objdiff-cli.exe'), 'diff', '-1', target, '-2', ofile,
                    '-o', j, sym], capture_output=True)
    d = json.load(open(j))
    a, b = insns(d, 'left'), insns(d, 'right')
    if a is None or b is None:
        return -1, 'symbol missing'
    import difflib
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    same = sum(bl.size for bl in sm.get_matching_blocks())
    return 100.0 * same / max(len(a), len(b)), ''

names = list(decls)
pools = [list(itertools.permutations(decls[n])) for n in names]
results = []
for n_, combo in enumerate(itertools.product(*pools) if names else [()]):
    if n_ >= maxn:
        break
    code = tmpl
    for n, perm in zip(names, combo):
        code = code.replace('{' + n + '}', sep[n].join(perm))
    sc, err = score(code)
    if sc < 0:
        print('ERR', err); break
    results.append((sc, combo))
    if sc == 100.0:
        print('FOUND', combo); break
results.sort(key=lambda x: -x[0])
for sc, c in results[:8]:
    print(f'{sc:.2f}', c)
