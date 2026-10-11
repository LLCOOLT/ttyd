"""reltrim.py <module> <file.c>...: in config/G8MJ01/<module>/splits.txt, end each section of the file before a
trailing dtk gap_ object (alignment padding that the compiler doesn't emit for this TU)."""
import re
import sys

mod = sys.argv[1]
p = f'config/G8MJ01/{mod}/splits.txt'
s = open(p, encoding='utf-8', newline='').read()
for name in sys.argv[2:]:
    asm = open(f'build/G8MJ01/{mod}/asm/{name[:-2]}.s', encoding='utf-8').read()
    # last object of each section: "# .sec:0xOFF | 0xADDR | size: 0xN\n.obj gap_..."
    last = {}
    for m in re.finditer(r'^# (\.\w+):0x\w+ \| (0x\w+) \| size: (0x\w+)\n\.(?:obj|fn) (\S+),', asm, re.M):
        last[m.group(1)] = (m.group(4), int(m.group(2), 16))
    block = re.search(r'^' + re.escape(name) + r':\n((?:\t.*\n)*)', s, re.M)
    body = block.group(1)
    new = body
    for sec, (obj, addr) in last.items():
        if obj.startswith('gap_'):
            new = re.sub(r'(\t' + re.escape(sec) + r'\s+start:0x\w+ end:)0x\w+', lambda m: m.group(1) + f'0x{addr:08X}', new)
            print(name, sec, 'end ->', hex(addr))
    s = s[:block.start(1)] + new + s[block.end(1):]
open(p, 'w', encoding='utf-8', newline='').write(s)
