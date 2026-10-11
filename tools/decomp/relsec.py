"""relsec.py <rels/<mod>/src/...c>: compile one REL source (relcc.py) and compare each section's size and bytes
(relocated instruction fields masked) against the split target object."""
import os
import struct
import subprocess
import sys
import tempfile

here = os.path.dirname(os.path.abspath(__file__))


# R_PPC_ADDR16_LO/HI/HA fill the low half of the instruction, R_PPC_REL24 the branch target
FIELDS = {4: 0xFFFF, 5: 0xFFFF, 6: 0xFFFF, 10: 0x03FFFFFC, 11: 0xFFFC}


def differs(t, o, off, rt, ro):
    mask = rt.get(off, 0) | ro.get(off, 0)
    a, = struct.unpack_from('>I', t, off)
    b, = struct.unpack_from('>I', o, off)
    return (a & ~mask) != (b & ~mask)


def sections(path):
    d = open(path, 'rb').read()
    shoff, = struct.unpack_from('>I', d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', d, 0x2E)
    hdrs = [struct.unpack_from('>IIIIIIIIII', d, shoff + i * shentsize) for i in range(shnum)]
    strtab = hdrs[shstrndx]
    name = lambda off: d[strtab[4] + off:d.index(b'\0', strtab[4] + off)].decode()
    secs = {}
    relocs = {}
    for i, h in enumerate(hdrs):
        n = name(h[0])
        if h[1] == 4:  # SHT_RELA
            tgt = name(hdrs[h[7]][0])
            # word offset -> bits the relocation fills in (the rest must still match)
            rs = relocs.setdefault(tgt, {})
            for j in range(h[5] // 12):
                off, info = struct.unpack_from('>II', d, h[4] + j * 12)
                typ = info & 0xFF
                field = FIELDS.get(typ, 0xFFFFFFFF) if (off & 3) == 0 else 0xFFFF
                rs[off & ~3] = rs.get(off & ~3, 0) | field
        elif n in ('.text', '.rodata', '.data', '.bss'):
            secs[n] = (h[5], d[h[4]:h[4] + h[5]] if h[1] != 8 else b'')
    # .bss has no bytes to compare: compare its layout instead, as the object offsets (dtk pads sizes to the next object)
    bss = [i for i, h in enumerate(hdrs) if name(h[0]) == '.bss']
    symtab = [h for h in hdrs if h[1] == 2]
    if bss and symtab and '.bss' in secs:
        st = symtab[0]
        strs = hdrs[st[6]]
        objs = []
        for j in range(st[5] // 16):
            nm, value, size, info, _, shndx = struct.unpack_from('>IIIBBH', d, st[4] + j * 16)
            sname = d[strs[4] + nm:d.index(b'\0', strs[4] + nm)].decode(errors='replace')
            if shndx == bss[0] and size and not sname.startswith('gap_'):
                objs.append((value, size))
        secs['.bss'] = (secs['.bss'][0], b''.join(struct.pack('>I', v) for v in sorted(set(v for v, _ in objs))))
    return secs, relocs


src = sys.argv[1].replace('\\', '/')
mod = src.split('/')[1]
rel = src.split('/src/', 1)[1][:-2]
tmp = os.path.join(tempfile.gettempdir(), 'relsec')
r = subprocess.run([sys.executable, '-I', os.path.join(here, 'relcc.py'), src, tmp], capture_output=True, text=True)
if r.returncode:
    sys.exit(r.stdout + r.stderr)
ours, our_rel = sections(os.path.join(tmp, os.path.basename(rel) + '.o'))
target, tgt_rel = sections(f'build/G8MJ01/{mod}/obj/{rel}.o')
if '--score' in sys.argv:
    # total differing words over all sections (size mismatches count heavily); 0 = identical
    total = 0
    for sec in ('.text', '.rodata', '.data', '.bss'):
        t = target.get(sec, (0, b''))
        o = ours.get(sec, (0, b''))
        if sec == '.bss':
            total += 0 if t[1] == o[1] and o[0] <= t[0] < o[0] + 8 else 4 + abs(t[0] - o[0])
            continue
        if not (o[0] < t[0] < o[0] + 8 and not t[1][o[0]:].strip(b'\0')):
            total += abs(t[0] - o[0]) * 4
        total += sum(1 for off in range(0, min(len(t[1]), len(o[1])) & ~3, 4)
                     if differs(t[1], o[1], off, tgt_rel.get(sec, {}), our_rel.get(sec, {})))
    print(total)
    sys.exit(0)
for sec in ('.text', '.rodata', '.data', '.bss'):
    t = target.get(sec, (0, b''))
    o = ours.get(sec, (0, b''))
    diffs = [off for off in range(0, min(len(t[1]), len(o[1])) & ~3, 4)
             if differs(t[1], o[1], off, tgt_rel.get(sec, {}), our_rel.get(sec, {}))]
    status = 'OK' if t[0] == o[0] and not diffs else 'DIFF'
    if sec == '.bss':
        status = ('OK' if t[0] == o[0] else 'OK (tail padding)') if t[1] == o[1] and o[0] <= t[0] < o[0] + 8 else 'DIFF (layout)'
        diffs = []
    # the split's end can include alignment padding the linker adds anyway
    if status == 'DIFF' and not diffs and o[0] < t[0] and t[0] - o[0] < 8 and not t[1][o[0]:].strip(b'\0'):
        status = 'OK (tail padding)'
    print(f'{sec:8} target {t[0]:#x} ours {o[0]:#x} {status}', ' first diffs at ' + ', '.join(hex(x) for x in diffs[:6]) if diffs else '')
