"""secsize.py <src path as in splits, e.g. unit/unit_system.c>: compare split section sizes
with the compiled object's section sizes, and list trailing gap objects in the target asm."""
import glob
import re
import subprocess
import sys

name = sys.argv[1]
splits = open('config/G8MJ01/splits.txt', encoding='utf-8').read()
m = re.search(r'^' + re.escape(name) + r':\n((?:\t.*\n)+)', splits, re.M)
want = {}
for line in m.group(1).splitlines():
    mm = re.match(r'\t(\S+)\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)', line)
    if mm:
        want[mm.group(1)] = (int(mm.group(2), 16), int(mm.group(3), 16))
obj = 'build/G8MJ01/src/' + name[:-2] + '.o'
out = subprocess.run([__import__('os').path.abspath('build/tools/dtk.exe'), 'elf', 'info', obj], capture_output=True, text=True).stdout
have = {}
for line in out.splitlines():
    mm = re.match(r'\s+(\.\w+) \| (?:code|data|rodata|bss)\s+\| (0x[0-9A-F]+)', line)
    if mm:
        have[mm.group(1)] = int(mm.group(2), 16)
asm = glob.glob('build/G8MJ01/asm/' + name[:-2] + '.s')
gaps = re.findall(r'^\.obj (gap_\w+)', open(asm[0]).read(), re.M) if asm else []
for sec, (s, e) in want.items():
    h = have.get(sec)
    flag = '' if h == e - s else '  <-- diff'
    print(f'{sec:8} split 0x{e - s:X}  obj {hex(h) if h is not None else None}{flag}')
print('gaps:', gaps)
