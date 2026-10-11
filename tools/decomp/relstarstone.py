"""relstarstone.py: write per-file starstone_entry snippets (the effect type differs per map)."""
import glob
import os
import re

here = os.path.dirname(os.path.abspath(__file__))
generic = open(os.path.join(here, 'relfuncs', 'starstone_entry.c'), encoding='utf-8').read()
for asm in glob.glob('build/G8MJ01/*/asm/*.s'):
    src = open(asm, encoding='utf-8').read()
    m = re.search(r'^\.fn starstone_entry, \w+\n(.*?)^\.endfn', src, re.M | re.S)
    if not m:
        continue
    body = m.group(1)
    before = body[:body.index('bl effStarStoneEntry')]
    t = re.findall(r'li r3, (0x[0-9a-f]+)', before)
    if not t:
        print('no type', asm)
        continue
    mod = asm.replace('\\', '/').split('/')[2]
    base = os.path.basename(asm)[:-2]
    out = os.path.join(here, 'relfuncs', mod, base)
    os.makedirs(out, exist_ok=True)
    text = re.sub(r'effStarStoneEntry\(\d+,', f'effStarStoneEntry({int(t[-1], 16)},', generic)
    open(os.path.join(out, 'starstone_entry.c'), 'w', encoding='utf-8', newline='\n').write(text)
    print(mod, base, int(t[-1], 16))
