"""gendata.py <asm-file-basename> <obj-name> <kinds> [--externs]

Emits C initializer rows for a struct-array object from the dtk asm.
<kinds> is one char per 4-byte word of an entry:
  s = string pointer (str_ symbol -> C literal, 0 -> NULL)
  p = pointer to symbol (0 -> NULL)
  x = hex int, d = signed decimal int, f = float
  h = two halfwords (hex), b = four bytes (hex)
With --externs, also prints `extern s32 sym[];` for every p-symbol."""
import glob
import re
import struct
import sys

sys.stdout.reconfigure(encoding='utf-8')
base, obj, kinds = sys.argv[1:4]
want_ext = '--externs' in sys.argv
f = glob.glob(f'build/G8MJ01/asm/**/{base}.s', recursive=True)[0]
src = open(f, encoding='utf-8').read()


def unesc(s):
    out = bytearray()
    i = 0
    while i < len(s):
        c = s[i]
        if c == '\\':
            n = s[i + 1]
            if n in '01234567':
                j = i + 1
                d = ''
                while j < len(s) and len(d) < 3 and s[j] in '01234567':
                    d += s[j]
                    j += 1
                out.append(int(d, 8))
                i = j
                continue
            out.append({'n': 10, 't': 9, '"': 34, '\\': 92, 'r': 13}[n])
            i += 2
            continue
        out.append(ord(c))
        i += 1
    return bytes(out)


strs = {}
for m in re.finditer(r'^\.obj (\w+), \w+\n((?:\t\.string "(?:[^"\\]|\\.)*"\n)+)', src, re.M):
    b = b''.join(unesc(x) for x in re.findall(r'\.string "((?:[^"\\]|\\.)*)"', m.group(2)))
    strs[m.group(1)] = b.split(b'\0')[0]


def cstr(b):
    if all(32 <= x < 127 for x in b):
        return '"%s"' % b.decode().replace('\\', '\\\\').replace('"', '\\"')
    try:
        txt = b.decode('shift_jis')
    except UnicodeDecodeError:
        txt = '?'
    return '/*"%s"*/"%s"' % (txt, ''.join('\\x%02X' % x for x in b))


body = re.search(r'^\.obj %s, \w+\n(.*?)^\.endobj' % re.escape(obj), src, re.M | re.S).group(1)
words = re.findall(r'\.4byte (\S+)', body)
assert len(words) % len(kinds) == 0, (len(words), len(kinds))
ext = []
rows = []


def val(x):
    return int(x, 16) if x.startswith('0x') else None


for k in range(0, len(words), len(kinds)):
    out = []
    for kind, x in zip(kinds, words[k:k + len(kinds)]):
        v = val(x)
        if kind == 's':
            out.append('NULL' if v == 0 else cstr(strs[x]))
        elif kind == 'p':
            if v == 0:
                out.append('NULL')
            else:
                out.append(x)
                if x not in ext:
                    ext.append(x)
        elif kind == 'x':
            out.append('0x%X' % v if v else '0')
        elif kind == 'd':
            out.append(str(struct.unpack('>i', struct.pack('>I', v))[0]))
        elif kind == 'f':
            out.append(repr(struct.unpack('>f', struct.pack('>I', v))[0]) + 'f')
        elif kind == 'h':
            out.append('0x%X, 0x%X' % (v >> 16, v & 0xFFFF))
        elif kind == 'b':
            out.append(', '.join('0x%02X' % ((v >> s) & 0xFF) for s in (24, 16, 8, 0)))
    rows.append('\t{' + ', '.join(out) + '},')
if want_ext:
    print('\n'.join('extern s32 %s[];' % e for e in ext))
    print()
print('\n'.join(rows))
