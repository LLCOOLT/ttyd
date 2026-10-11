"""tv.py <variants.txt> <unit> <symbol>
variants.txt: first block is OLD text, following blocks are candidate replacements;
blocks separated by a line '====='. Scores the original, tries each candidate,
then applies the best one only if it beats the original (ties -> keep original).
Line endings of the source file are preserved."""
import os, subprocess, sys

vfile, unit, sym = sys.argv[1:4]
src = 'src/' + unit.split('/', 1)[1] + '.c'
blocks = open(vfile, encoding='utf-8').read().split('\n=====\n')
old, cands = blocks[0], blocks[1:]
raw = open(src, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in raw else '\n'
orig = raw.replace('\r\n', '\n')
assert old in orig, 'OLD text not found'
here = os.path.dirname(os.path.abspath(__file__))
fd = os.path.join(here, 'fd.py')


def write(text):
    open(src, 'w', encoding='utf-8', newline='').write(text.replace('\n', nl))


def score_now():
    r = subprocess.run([sys.executable, fd, unit, sym], capture_output=True, text=True)
    line = next((l for l in r.stdout.splitlines() if l.startswith('==')), r.stdout[-500:])
    try:
        return float(line.rsplit(' ', 1)[1].rstrip('%'))
    except Exception:
        return -1


write(orig)
base = score_now()
print(f'[orig] {base}')
best = (base, None)
for i, c in enumerate(cands):
    write(orig.replace(old, c, 1))
    score = score_now()
    sec = subprocess.run([sys.executable, os.path.join(here, 'sec.py'), unit, sym], capture_output=True, text=True).stdout.strip()
    print(f'[{i}] {score}  {c.strip().splitlines()[0][:60]}  {sec}')
    if score > best[0]:
        best = (score, c)
if best[1] is not None:
    write(orig.replace(old, best[1], 1))
    print('applied best:', best[0])
else:
    write(orig)
    print('kept original:', base)
subprocess.run([sys.executable, fd, unit, sym], capture_output=True)
