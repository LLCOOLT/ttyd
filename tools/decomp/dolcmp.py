"""dolcmp.py: compare built DOL vs original; print differing addresses with nearest symbol"""
import struct, bisect, re
a=open('orig/G8MJ01/sys/main.dol','rb').read(); b=open('build/G8MJ01/MarioSt.dol','rb').read()
offs=struct.unpack('>18I',a[:72]); addrs=struct.unpack('>18I',a[72:144]); sizes=struct.unpack('>18I',a[144:216])
def addr(o):
    for i in range(18):
        if offs[i]<=o<offs[i]+sizes[i]: return addrs[i]+o-offs[i]
syms=[]
for l in open('config/G8MJ01/symbols.txt'):
    m=re.match(r'(\S+) = \.\w+:0x([0-9A-F]+);',l)
    if m: syms.append((int(m.group(2),16),m.group(1)))
syms.sort(); ks=[s[0] for s in syms]
print('sizes',len(a),len(b))
d=[i for i in range(min(len(a),len(b))) if a[i]!=b[i]]
print(len(d),'bytes differ')
seen=0
for i in d:
    ad=addr(i)
    if ad is None: print(hex(i),'?'); continue
    j=bisect.bisect_right(ks,ad)-1
    print(hex(ad), syms[j][1]+'+'+hex(ad-syms[j][0]), a[i&~3:(i&~3)+4].hex(), b[i&~3:(i&~3)+4].hex())
    seen+=1
    if seen>25: break
