"""relbatch.py gen <module> [file...]  : generate C for code-free REL files (no .text) of a module
   relbatch.py list <module>          : list candidate files and why some are skipped

Generated files go to rels/<module>/src/<path>.c with `#pragma force_active on` so the REL linker
keeps unreferenced data like the original. Files with .bss or non-string .rodata objects are skipped."""
import os
import re
import subprocess
import sys

cmd, mod = sys.argv[1], sys.argv[2]
only = set(sys.argv[3:])
here = os.path.dirname(os.path.abspath(__file__))
snipdir = os.path.join(here, 'relfuncs')
splits = open(f'config/G8MJ01/{mod}/splits.txt', encoding='utf-8').read()


def snippet(name, f):
    for path in (os.path.join(snipdir, mod, name[:-2], f + '.c'), os.path.join(snipdir, f + '.c')):
        if os.path.exists(path):
            return path
    return None


def candidates():
    for m in re.finditer(r'^(\S+\.c):\n((?:\t.*\n)*)', splits, re.M):
        name, body = m.group(1), m.group(2)
        if only and name not in only:
            continue
        asm = f'build/G8MJ01/{mod}/asm/{name[:-2]}.s'
        if not os.path.exists(asm):
            if '.text' not in body:
                yield name, 'no asm'
            continue
        src = open(asm, encoding='utf-8').read()
        if '.text' in body:
            missing = [f for f in re.findall(r'^\.fn (\w+)', src, re.M) if not snippet(name, f)]
            if missing:
                if only:
                    yield name, 'no snippet for ' + ','.join(missing[:4])
                continue
        if '.bss' in body:
            # fine when the snippets declare every .bss object (function statics / file statics)
            bss = re.findall(r'^\.obj (\w+), \w+', src.split('.section .bss')[1], re.M) if '.section .bss' in src else ['?']
            decl = ''.join(open(snippet(name, f), encoding='utf-8').read() for f in re.findall(r'^\.fn (\w+)', src, re.M))
            if any(not b.startswith('gap_') and not re.search(r'\b' + re.escape(b.split('$')[0]) + r'\b', decl) for b in bss):
                yield name, 'has .bss'
                continue
        m2 = re.search(r'^(?:\.section )?\.rodata\b.*?(?=^\.section|^\.data\b|^\.bss\b|\Z)', src, re.M | re.S)
        ro = re.findall(r'^\.obj (\w+), \w+', m2.group(0), re.M) if m2 else []
        # compiler float constants are fine when only code uses them (the snippets recreate them)
        # (a code-only "jumptable_" of string pointers is a local array's initializer template)
        bad = [r for r in ro if not r.startswith(('str_', 'gap_', 'zero_', 'dat_'))
               and not (r.startswith(('float_', 'double_', 'vec3_', 'jumptable_')) and f'.4byte {r}' not in src)]
        if bad:
            yield name, 'rodata objs ' + ','.join(bad[:3])
            continue
        yield name, None


def apply_snippets(text, name):
    """Replace `// TODO: [static ]USER_FUNC(f) { }` stubs with relfuncs/<f>.c, fixing the prototype and includes."""
    incs = []
    decls = []
    for m in list(re.finditer(r'^// TODO: (static )?USER_FUNC\((\w+)\) \{ \}$', text, re.M)):
        static, f = m.group(1) or '', m.group(2)
        path = snippet(name, f)
        if not path:
            continue
        snip = open(path, encoding='utf-8').read()
        proto = re.search(r'^// proto: (.*)$', snip, re.M).group(1)
        incs += [i for i in re.findall(r'^// include: (\S+)$', snip, re.M) if i not in incs]
        decls += [d for d in re.findall(r'^// decl: (.*)$', snip, re.M) if d not in decls]
        code = re.sub(r'^// (proto|include|decl): .*\n', '', snip, flags=re.M).rstrip('\n')
        if static and not proto.startswith('static '):
            head = proto.rstrip(';')
            code = re.sub(r'^' + re.escape(head), lambda _: 'static ' + head, code, count=1, flags=re.M)
            proto = 'static ' + proto
        text = text.replace(m.group(0), code, 1)
        text = re.sub(r'^USER_FUNC\(' + f + r'\);$', lambda _: proto, text, count=1, flags=re.M)
        # function statics the snippet defines itself: drop unitgen's file-level copy (`name$N` -> fd_<file>_name_N)
        for local in re.findall(r'^ +static [^=;(]*?\b(\w+)(?:\[\w*\])*\s*[=;]', code, re.M):
            fd = r'fd_\w+?_' + local + r'_\d+'
            text = re.sub(r'^__declspec\(section "[.\w]+"\) [\w ]+ ' + fd + r'\[\d*\] = \{\n(?:.*\n)*?\};\n', '', text, flags=re.M)
            text = re.sub(r'^__declspec\(section "[.\w]+"\) [\w ]+ ' + fd + r'(?:\[\d*\])?( = [^\n]*)?;\n', '', text, flags=re.M)
    if decls:
        text = re.sub(r'^(USER_FUNC|void |extern |static |__declspec|s32 |u64 )', lambda m: '\n'.join(decls) + '\n\n' + m.group(1),
                      text, count=1, flags=re.M)
    if incs:
        text = text.replace('#include "evt/evt_cmd.h"\n', '#include "evt/evt_cmd.h"\n' + ''.join(f'#include "{i}"\n' for i in incs), 1)
    return text


if cmd == 'list':
    for name, why in candidates():
        print(name, why or 'OK')
    sys.exit(0)

cfg_text = open('configure.py', encoding='utf-8').read()
blk = re.search(r'    Rel\(\s*"' + re.escape(mod) + r'",\s*\[(.*?)\n        \]', cfg_text, re.S)
matching = set(re.findall(r'Object\(Matching, "([^"]+)"', blk.group(1))) if blk else set()
for name, why in candidates():
    if why:
        print('skip', name, why)
        continue
    if name in matching:
        # ttydasm reads the linked module, which already contains our object: strings would decode wrong
        print('skip', name, 'already Matching (set it NonMatching and rebuild before regenerating)')
        continue
    base = name[:-2]
    # statics defined inside this file's function snippets: unitgen places the function where they were
    asm = open(f'build/G8MJ01/{mod}/asm/{base}.s', encoding='utf-8').read()
    statics = set()
    for f in re.findall(r'^\.fn (\w+)', asm, re.M):
        if snippet(name, f):
            statics.update(re.findall(r'^ +static [^=;(]*?\b(\w+)(?:\[\w*\])*\s*[=;]', open(snippet(name, f), encoding='utf-8').read(), re.M))
    env = dict(os.environ, UNITGEN_FNSTATICS=','.join(sorted(statics)))
    r = subprocess.run([sys.executable, '-I', os.path.join(here, 'unitgen.py'), base, '--module', mod],
                       capture_output=True, text=True, encoding='utf-8', env=env)
    out_text = apply_snippets(r.stdout, name) if not r.returncode else r.stdout
    if r.returncode or 'TODO' in out_text:
        print('fail', name, (r.stderr or '')[-300:], 'TODO' if 'TODO' in r.stdout else '')
        continue
    text = out_text.replace('#include "evt/evt_cmd.h"\n', '#include "evt/evt_cmd.h"\n\n#pragma force_active on\n', 1)
    out = f'rels/{mod}/src/{name}'
    os.makedirs(os.path.dirname(out), exist_ok=True)
    open(out, 'w', encoding='utf-8', newline='\n').write(text)
    print('gen', name)
