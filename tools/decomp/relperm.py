"""relperm.py <module> <file.c> <snippet path> <function>: try every order of the snippet's leading declaration
block (the lines between the function's opening brace and the first blank line), regenerating and diffing each.
Keeps the best order in the snippet file."""
import itertools
import os
import re
import subprocess
import sys

here = os.path.dirname(os.path.abspath(__file__))
mod, cfile, snip, func = sys.argv[1:5]
orig = open(snip, encoding='utf-8').read()
lines = orig.split('\n')
start = next(i for i, l in enumerate(lines) if l.endswith('{') and not l.startswith(' ')) + 1
end = next(i for i in range(start, len(lines)) if lines[i].strip() == '')
decls = lines[start:end]


def score(text):
    open(snip, 'w', encoding='utf-8', newline='\n').write(text)
    subprocess.run([sys.executable, '-I', os.path.join(here, 'relbatch.py'), 'gen', mod, cfile], capture_output=True)
    r = subprocess.run([sys.executable, '-I', os.path.join(here, 'relfd.py'), f'rels/{mod}/src/{cfile}', func],
                       capture_output=True, text=True)
    m = re.search(r'== \S+: ([\d.]+|None)%', r.stdout)
    return float(m.group(1)) if m and m.group(1) != 'None' else -1.0


def greedy():
    """too many declarations to permute: repeatedly move single declarations to their best position"""
    cur = list(decls)
    best = score('\n'.join(lines[:start] + cur + lines[end:]))
    improved = True
    while improved and best < 100.0:
        improved = False
        for d in list(cur):
            for pos in range(len(cur)):
                rest = [x for x in cur if x is not d]
                cand = rest[:pos] + [d] + rest[pos:]
                if cand == cur:
                    continue
                s = score('\n'.join(lines[:start] + cand + lines[end:]))
                if s > best:
                    best, cur, improved = s, cand, True
                    print(f'{s}%', ' | '.join(p.strip() for p in cur), flush=True)
    return best, '\n'.join(lines[:start] + cur + lines[end:])


best, best_text = -1.0, orig
if '--greedy' in sys.argv or len(decls) > 8:
    best, best_text = greedy()
for perm in [] if best >= 0 else itertools.permutations(decls):
    text = '\n'.join(lines[:start] + list(perm) + lines[end:])
    s = score(text)
    if s > best:
        best, best_text = s, text
        print(f'{s}%', ' | '.join(p.strip() for p in perm), flush=True)
    if s >= 100.0:
        break
open(snip, 'w', encoding='utf-8', newline='\n').write(best_text)
subprocess.run([sys.executable, '-I', os.path.join(here, 'relbatch.py'), 'gen', mod, cfile], capture_output=True)
print('best', best)
