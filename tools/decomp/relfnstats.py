"""relfnstats.py [N]: list REL function names by number of files they appear in (with size), excluding
functions that already have a snippet in relfuncs/. Shows which hand-written snippets unlock the most files."""
import collections
import glob
import os
import re
import sys

here = os.path.dirname(os.path.abspath(__file__))
snips = {os.path.basename(p)[:-2] for p in glob.glob(os.path.join(here, 'relfuncs', '*.c'))}  # generic snippets
count = collections.Counter()
sizes = {}
files = collections.defaultdict(list)
for asm in glob.glob('build/G8MJ01/*/asm/**/*.s', recursive=True):
    parts = asm.replace('\\', '/').split('/')
    if parts[2] == 'asm':
        continue  # DOL
    src = open(asm, encoding='utf-8').read()
    for m in re.finditer(r'^# \.text:0x\w+ \| 0x\w+ \| size: (0x\w+)\n\.fn (\w+),', src, re.M):
        name = m.group(2)
        if name in snips or os.path.exists(os.path.join(here, 'relfuncs', parts[2], *parts[4:])[:-2] + '/' + name + '.c'):
            continue
        count[name] += 1
        sizes[name] = int(m.group(1), 16)
        files[name].append(parts[2] + '/' + '/'.join(parts[4:]))
if len(sys.argv) > 1 and sys.argv[1] == 'files':
    # files ordered by code size still missing a snippet
    cfg = open('configure.py', encoding='utf-8').read()
    todo = collections.defaultdict(list)
    for name, fl in files.items():
        for f in fl:
            todo[f].append(name)
    rows = []
    for f, names in todo.items():
        mod, path = f.split('/', 1)
        if re.search(r'Object\(Matching, "' + re.escape(path[:-2] + '.c') + '"', cfg) and f'Rel("{mod}"' in cfg:
            continue
        rows.append((sum(sizes[n] for n in names), f, names))
    for size, f, names in sorted(rows)[:int(sys.argv[2]) if len(sys.argv) > 2 else 60]:
        print(f'{size:#6x} {f}: {", ".join(names)}')
    sys.exit(0)
n = int(sys.argv[1]) if len(sys.argv) > 1 else 40
for name, c in count.most_common(n):
    print(f'{c:3d} {sizes[name]:#6x} {name}  ({", ".join(files[name][:3])}{"..." if c > 3 else ""})')
