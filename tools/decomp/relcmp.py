"""relcmp.py <module>: compare build/G8MJ01/<module>/<module>.rel with the original REL and report
differing bytes as (section, offset), plus header/relocation-table differences."""
import struct
import sys

mod = sys.argv[1]
a = open(f'orig/G8MJ01/files/rel/{mod}.rel', 'rb').read()
b = open(f'build/G8MJ01/{mod}/{mod}.rel', 'rb').read()
print('sizes', hex(len(a)), hex(len(b)))


def sections(x):
    n, off = struct.unpack('>II', x[0xC:0x14])
    out = []
    for i in range(n):
        o, sz = struct.unpack('>II', x[off + i * 8:off + i * 8 + 8])
        out.append((i, o & ~1, sz))
    return out


sa, sb = sections(a), sections(b)
for (i, oa, za), (_, ob, zb) in zip(sa, sb):
    if za != zb or oa != ob:
        print(f'section {i}: orig off {oa:#x} size {za:#x} | ours off {ob:#x} size {zb:#x}')
hdr = [i for i in range(0x40) if i < len(a) and i < len(b) and a[i] != b[i]]
if hdr:
    print('header diffs at', [hex(i) for i in hdr])
shown = 0
for i, o, sz in sa:
    if not o or not sz:
        continue
    for k in range(sz):
        if o + k >= len(b) or a[o + k] != b[o + k]:
            print(f'section {i} +{k:#x}: {a[o + k:o + k + 4].hex()} vs {b[o + k:o + k + 4].hex()}')
            shown += 1
            break
end_a = max(o + sz for i, o, sz in sa if o)
tail_diff = [i for i in range(end_a, min(len(a), len(b))) if a[i] != b[i]]
print('reloc-area diffs:', len(tail_diff), hex(tail_diff[0]) if tail_diff else '')
