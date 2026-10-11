"""relfd.py <rels/<mod>/src/...c> <symbol>... : compile one REL source with relcc.py (no ninja) and print a
side-by-side asm diff (target | ours) of each symbol against the split target object."""
import json
import os
import subprocess
import sys
import tempfile

here = os.path.dirname(os.path.abspath(__file__))
src = sys.argv[1].replace('\\', '/')
syms = sys.argv[2:]
mod = src.split('/')[1]
rel = src.split('/src/', 1)[1][:-2]
tmp = os.path.join(tempfile.gettempdir(), 'relfd')
r = subprocess.run([sys.executable, '-I', os.path.join(here, 'relcc.py'), src, tmp], capture_output=True, text=True)
if r.returncode:
    print(r.stdout, r.stderr)
    sys.exit(1)
ours = os.path.join(tmp, os.path.basename(rel) + '.o')
target = f'build/G8MJ01/{mod}/obj/{rel}.o'
out = os.path.join(tmp, 'fd%d.json' % os.getpid())
for sym in syms:
    subprocess.run([os.path.join('build', 'tools', 'objdiff-cli.exe'), 'diff', '-1', target, '-2', ours, '-o', out, sym],
                   capture_output=True)
    d = json.load(open(out))

    def find(side):
        for s in d.get(side, {}).get('symbols', []):
            if s.get('name') == sym:
                return s

    L, R = find('left'), find('right')
    lp = (L or {}).get('match_percent')
    print(f"== {sym}: {lp if lp is not None else (R or {}).get('match_percent')}%")
    if lp == 100 or (R or {}).get('match_percent') == 100:
        continue
    li = (L or {}).get('instructions', [])
    ri = (R or {}).get('instructions', [])
    for i in range(max(len(li), len(ri))):
        a = li[i] if i < len(li) else {}
        b = ri[i] if i < len(ri) else {}
        fa = a.get('instruction', {}).get('formatted', '')
        fb = b.get('instruction', {}).get('formatted', '')
        k = a.get('diff_kind') or b.get('diff_kind') or ''
        print(f"{'!!' if k else '  '} {fa:40s} | {fb}")

try:
    os.remove(out)
except OSError:
    pass
