import struct,sys
def load(p):
    d=open(p,'rb').read()
    shoff=struct.unpack('>I',d[0x20:0x24])[0]; es,n,si=struct.unpack('>HHH',d[0x2e:0x34])
    H=[struct.unpack('>IIIIIIIIII',d[shoff+i*es:shoff+i*es+40]) for i in range(n)]
    nm=lambda off,tab: d[H[tab][4]+off:].split(b'\0')[0].decode()
    names=[nm(h[0],si) for h in H]
    symtab=[i for i,h in enumerate(H) if h[1]==2][0]
    st=H[symtab]; syms=[]
    for k in range(st[5]//16):
        o=st[4]+k*16; name,val,size,info,oth,shn=struct.unpack('>IIIBBH',d[o:o+16])
        syms.append((nm(name,st[6]),val,shn))
    out={}
    for i,h in enumerate(H):
        if h[1]==4:
            tgt=names[h[7]]
            L=[]
            for k in range(h[5]//12):
                o=h[4]+k*12; off,info,add=struct.unpack('>IIi',d[o:o+12])
                s=syms[info>>8]; t=info&0xff
                if s[2] and s[2]<0xff00: L.append((off,t,names[s[2]],s[1]+add))
                else: L.append((off,t,s[0],add))
            out[tgt]=sorted(L)
    return out
a=load(sys.argv[1]); b=load(sys.argv[2])
for sec in sorted(set(a)|set(b)):
    x=a.get(sec,[]); y=b.get(sec,[])
    print(sec,len(x),len(y))
    nd=0
    for i in range(max(len(x),len(y))):
        u=x[i] if i<len(x) else None; v=y[i] if i<len(y) else None
        if u!=v:
            print('  ',[hex(e) if isinstance(e,int) else e for e in (u or ())],'|',[hex(e) if isinstance(e,int) else e for e in (v or ())]); nd+=1
            if nd>15: break
