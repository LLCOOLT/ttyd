"""fixpairs2.py [--apply]: find split .data ranges that END with an 8-byte {-1.0f, 1.0f} object
(the next TU's leading pair) and move the boundary back 8 bytes (prev end and next start)."""
import re
import struct
import sys

dol = open('orig/G8MJ01/sys/main.dol', 'rb').read()
offs = struct.unpack('>18I', dol[:72])
addrs = struct.unpack('>18I', dol[72:144])
sizes = struct.unpack('>18I', dol[144:216])


def word(a):
    for i in range(18):
        if addrs[i] <= a < addrs[i] + sizes[i]:
            o = offs[i] + a - addrs[i]
            return struct.unpack('>I', dol[o:o + 4])[0]
    return None


splitp = 'config/G8MJ01/splits.txt'
splits = open(splitp, encoding='utf-8').read()
ranges = [(int(s, 16), int(e, 16)) for s, e in re.findall(r'\.data       start:0x([0-9A-F]+) end:0x([0-9A-F]+)', splits)]
starts = {s for s, e in ranges}
n = 0
for s, e in ranges:
    if e in starts and e - 8 > s and word(e - 8) == 0xBF800000 and word(e - 4) == 0x3F800000:
        n += 1
        print(f'boundary 0x{e:08X} -> 0x{e - 8:08X}')
        if '--apply' in sys.argv:
            splits = splits.replace(f'.data       start:0x{e:08X} ', f'.data       start:0x{e - 8:08X} ')
            splits = splits.replace(f'.data       start:0x{s:08X} end:0x{e:08X}\n', f'.data       start:0x{s:08X} end:0x{e - 8:08X}\n')
print(n)
if '--apply' in sys.argv:
    open(splitp, 'w', encoding='utf-8', newline='').write(splits)
