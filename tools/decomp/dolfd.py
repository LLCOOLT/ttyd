"""dolfd.py <src/...c> [symbol...] : compile one DOL source WITHOUT ninja (safe to run while another
process builds) and diff it against build/G8MJ01/obj/<path>.o. With no symbols, prints per-function
match %; with symbols, prints a side-by-side asm diff (target | ours) for each."""
import json
import os
import shlex
import subprocess
import sys
import tempfile

src = sys.argv[1].replace('\\', '/')
syms = sys.argv[2:]
rel = src.split('src/', 1)[1][:-2]
obj = f'build\\G8MJ01\\src\\{rel.replace("/", chr(92))}.o'
cmd = subprocess.run([sys.executable, '-m', 'ninja', '-t', 'commands', obj], capture_output=True, text=True).stdout.strip().splitlines()
if not cmd:
    print('no ninja command for', obj); sys.exit(1)
line = cmd[-1]
tmp = os.path.join(tempfile.gettempdir(), 'dolfd', str(os.getpid()))
os.makedirs(tmp, exist_ok=True)
# compile into a private dir instead of build/
line = line.replace(' -o build\\G8MJ01\\src\\' + os.path.dirname(rel).replace('/', '\\'), ' -o ' + tmp)
line = line.replace(' -o build\\G8MJ01\\src', ' -o ' + tmp)
line = line.split(' && ')[0]
r = subprocess.run(line, shell=True, capture_output=True, text=True)
ours = os.path.join(tmp, os.path.basename(rel) + '.o')
if r.returncode or not os.path.exists(ours):
    print(r.stdout[-3000:], r.stderr[-2000:]); sys.exit(1)
target = f'build/G8MJ01/obj/{rel}.o'
out = os.path.join(tmp, 'd.json')
objdiff = os.path.join('build', 'tools', 'objdiff-cli.exe')
if not syms:
    subprocess.run([objdiff, 'diff', '-1', target, '-2', ours, '-o', out], capture_output=True)
    d = json.load(open(out))
    for s in d.get('left', {}).get('symbols', []):
        if s.get('kind', '') in ('SYMBOL_FUNCTION', 'function') or s.get('instructions'):
            print(f"{s.get('match_percent', 0):7.2f}% {s.get('name')}")
    sys.exit(0)
for sym in syms:
    subprocess.run([objdiff, 'diff', '-1', target, '-2', ours, '-o', out, sym], capture_output=True)
    d = json.load(open(out))

    def find(side):
        for s in d.get(side, {}).get('symbols', []):
            if s.get('name') == sym:
                return s

    L, R = find('left'), find('right')
    lp = (L or {}).get('match_percent')
    print(f"== {sym}: {lp}%")
    if lp == 100:
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
