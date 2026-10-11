"""relsmall.py [maxsize]: list REL files whose .text is at most maxsize bytes (default 0x100)."""
import glob
import os
import re
import sys

limit = int(sys.argv[1], 0) if len(sys.argv) > 1 else 0x100
cfg = open('configure.py', encoding='utf-8').read()
for path in sorted(glob.glob('config/G8MJ01/*/splits.txt')):
    mod = os.path.basename(os.path.dirname(path))
    s = open(path, encoding='utf-8').read()
    for f in re.finditer(r'^(\S+\.c):\n((?:\t.*\n)*)', s, re.M):
        t = re.search(r'\.text\s+start:0x(\w+) end:0x(\w+)', f.group(2))
        if not t:
            continue
        sz = int(t.group(2), 16) - int(t.group(1), 16)
        if sz <= limit:
            done = re.search(r'Object\(Matching, "' + re.escape(f.group(1)) + '"', cfg) is not None
            print(mod, f.group(1), hex(sz), 'DONE' if done else '')
