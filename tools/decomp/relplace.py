"""relplace.py <rels/<mod>/src/...c>: search for function positions that make a generated REL file match.

The file is split into top-level blocks (separated by blank lines, after the forward declarations). Each
function block is moved, one at a time, to every slot between its neighbouring functions (functions keep
their relative order, since source order = text order), keeping whichever position lowers relsec's score.
Repeats until no move helps. Rewrites the file in place with the best layout found."""
import os
import re
import subprocess
import sys

here = os.path.dirname(os.path.abspath(__file__))
path = sys.argv[1]
text = open(path, encoding='utf-8').read()

# split off the header: everything up to the first definition with a body
m = re.search(r'^(?:static |__declspec\(section "\.data"\) )*(?:EVT_BEGIN\(|USER_FUNC\(\w+\) \{|[\w ]+\*? ?\w+\([^;]*\) \{|[\w ]+ \w+\[\] = \{|u64 \w+ = |s32 \w+\[\] = \{)', text, re.M)
head, body = text[:m.start()], text[m.start():]
blocks = [b for b in body.split('\n\n') if b.strip()]
is_fn = [bool(re.match(r'^(?:static )?(?:USER_FUNC\(\w+\) \{|[\w ]+\*? ?\w+\([^;]*\) \{)', b) and 'EVT_BEGIN' not in b.split('\n')[0]) for b in blocks]


def render(bl):
    return head + '\n\n'.join(bl) + '\n'


def score(bl):
    open(path, 'w', encoding='utf-8', newline='\n').write(render(bl))
    r = subprocess.run([sys.executable, '-I', os.path.join(here, 'relsec.py'), path, '--score'], capture_output=True, text=True)
    try:
        return int(r.stdout.strip().split('\n')[-1])
    except ValueError:
        return 10 ** 9


best = score(blocks)
print('start', best, flush=True)
improved = True
while improved and best:
    improved = False
    fn_idx = [i for i, f in enumerate(is_fn) if f]
    for k, i in enumerate(fn_idx):
        lo = fn_idx[k - 1] + 1 if k else 0
        hi = fn_idx[k + 1] if k + 1 < len(fn_idx) else len(blocks)
        fn = blocks[i]
        others = blocks[:i] + blocks[i + 1:]
        flags = is_fn[:i] + is_fn[i + 1:]
        for pos in range(lo, hi):
            if pos == i:
                continue
            cand = others[:pos] + [fn] + others[pos:]
            s = score(cand)
            if s < best:
                best, blocks, is_fn = s, cand, flags[:pos] + [True] + flags[pos:]
                improved = True
                print('moved', fn.split('\n')[0][:50], '->', pos, 'score', best, flush=True)
                break
        if improved:
            break
open(path, 'w', encoding='utf-8', newline='\n').write(render(blocks))
print('best', best)
