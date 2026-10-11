"""relrun.py <module>...: generate + link all code-free REL files of each module.
Keeps files that leave the module's REL byte-identical; bisects to drop the ones that don't.
Run `python configure.py && python -m ninja` first so the original module .plf exists."""
import os
import re
import subprocess
import sys

here = os.path.dirname(os.path.abspath(__file__))
py = sys.executable


def run(args, **kw):
    return subprocess.run(args, capture_output=True, text=True, encoding='utf-8', errors='replace', **kw)


def build():
    run([py, 'configure.py'])
    return run([py, '-m', 'ninja'])


def rel_ok(mod):
    r = run([py, os.path.join(here, 'relcmp.py'), mod])
    out = r.stdout
    return 'reloc-area diffs: 0' in out and 'section' not in out and 'header diffs' not in out


def setcfg(mod, status, files):
    if files:
        run([py, '-I', os.path.join(here, 'relcfg.py'), mod, status, *files])


for mod in sys.argv[1:]:
    lst = run([py, '-I', os.path.join(here, 'relbatch.py'), 'list', mod]).stdout.split('\n')
    cfg = open('configure.py', encoding='utf-8').read()
    cands = []
    for line in lst:
        if line.endswith(' OK'):
            name = line[:-3]
            if re.search(r'Object\(Matching, "' + re.escape(name) + '"', cfg) and f'"{mod}"' in cfg:
                continue
            cands.append(name)
    if not cands:
        print(mod, 'nothing to do')
        continue
    gen = run([py, '-I', os.path.join(here, 'relbatch.py'), 'gen', mod, *cands]).stdout
    good = [l[4:] for l in gen.split('\n') if l.startswith('gen ')]
    for l in gen.split('\n'):
        if l.startswith(('fail', 'skip')):
            print(mod, l)
    setcfg(mod, 'NonMatching', good)
    # ninja compiles NonMatching sources too, so one file that doesn't compile breaks every build: drop those
    run([py, 'configure.py'])
    cfg = open('configure.py', encoding='utf-8').read()
    blk = re.search(r'    Rel\(\s*"' + re.escape(mod) + r'",\s*\[(.*?)\n        \]', cfg, re.S).group(1)
    for name in re.findall(r'Object\(NonMatching, "([^"]+)"', blk):
        if run([py, '-I', os.path.join(here, 'relcc.py'), f'rels/{mod}/src/{name}']).returncode:
            print(mod, 'COMPILE-FAIL', name)
            setcfg(mod, 'Remove', [name])
            if name in good:
                good.remove(name)
    # try all, then bisect failures
    pending = [good]
    kept = []
    failed = []
    splits = open(f'config/G8MJ01/{mod}/splits.txt', encoding='utf-8').read()
    while pending:
        group = pending.pop()
        setcfg(mod, 'Matching', group)
        r = build()
        ok = r.returncode == 0 and rel_ok(mod)
        if ok:
            kept += group
            continue
        setcfg(mod, 'NonMatching', group)
        if len(group) == 1:
            failed.append(group[0])
            continue
        half = len(group) // 2
        pending += [group[:half], group[half:]]
    # some RELs were built with deferred inlining: retry failed code files that way, pinned per file
    for name in failed:
        b = re.search(r'^' + re.escape(name) + r':\n((?:\t.*\n)*)', splits, re.M)
        if not b or '.text' not in b.group(1):
            print(mod, 'FAIL', name)
            continue
        # functions placed by their float constants too
        env = dict(os.environ, UNITGEN_FLOATS='1')
        subprocess.run([py, '-I', os.path.join(here, 'relbatch.py'), 'gen', mod, name], capture_output=True, env=env)
        setcfg(mod, 'Matching', [name])
        r = build()
        if r.returncode == 0 and rel_ok(mod):
            kept.append(name)
            print(mod, 'kept (floats)', name)
            continue
        setcfg(mod, 'NonMatching', [name])
        env = dict(os.environ, UNITGEN_DEFERRED='1')
        subprocess.run([py, '-I', os.path.join(here, 'relbatch.py'), 'gen', mod, name], capture_output=True, env=env)
        setcfg(mod, 'MatchingDeferred', [name])
        r = build()
        if r.returncode == 0 and rel_ok(mod):
            kept.append(name)
            print(mod, 'kept (deferred)', name)
            continue
        setcfg(mod, 'NonMatching', [name])
        setcfg(mod, 'Plain', [name])
        run([py, '-I', os.path.join(here, 'relbatch.py'), 'gen', mod, name])
        print(mod, 'FAIL', name)
    build()
    print(mod, f'kept {len(kept)}/{len(good)}')
