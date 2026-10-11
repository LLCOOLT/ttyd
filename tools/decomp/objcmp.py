"""objcmp.py <src path, e.g. unit/unit_bomzou.c>: list target vs our object section/offset/size side by side."""
import os
import re
import subprocess
import sys

name = sys.argv[1][:-2]
asm = open(f'build/G8MJ01/asm/{name}.s', encoding='utf-8').read()
target = []
for m in re.finditer(r'^# (\.\w+):(0x[0-9A-F]+) \| 0x[0-9A-F]+ \| size: (0x[0-9A-F]+)\n\.(?:obj|fn) (\S+),', asm, re.M):
    target.append((m.group(4), m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
out = subprocess.run([os.path.abspath('build/tools/dtk.exe'), 'elf', 'info', f'build/G8MJ01/src/{name}.o'],
                     capture_output=True, text=True).stdout
ours = {}
for line in out.splitlines():
    m = re.match(r'\s+(\.\w+) \| (0x[0-9A-F]+)\s+\| (0x[0-9A-F]+)\s+\| (\S+)', line)
    if m:
        ours.setdefault(m.group(4), []).append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
for n, sec, off, size in target:
    o = ours.get(n, [None])[0]
    flag = '' if o == (sec, off, size) else '   <--'
    if n.startswith(('str_', 'gap_', 'float_', 'double_', 'zero_')) and o is None:
        flag = ''
    print(f'{n:32} {sec:8} {off:#7x} {size:#6x}   ours: {o}{flag}')
