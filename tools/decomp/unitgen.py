"""unitgen.py <asm basename> [--module MarioSt]

Generates C for a battle unit file (BattleUnitKind + parts + defence tables +
pose/data tables + evt scripts) from the dtk asm. Scripts are decompiled with
tools/ttydasm. Functions are emitted as TODO prototypes; write them by hand.
Output goes to stdout."""
import glob
import re
import struct
import subprocess
import sys

sys.stdout.reconfigure(encoding='utf-8')
base = sys.argv[1]
module = sys.argv[sys.argv.index('--module') + 1] if '--module' in sys.argv else 'MarioSt'
path = glob.glob(f'build/G8MJ01/asm/**/{base}.s', recursive=True)
if module != 'MarioSt':
    path = glob.glob(f'build/G8MJ01/{module}/asm/**/{base}.s', recursive=True)
src = open(path[0], encoding='utf-8').read()
import os
TTYDASM = os.path.abspath('tools/ttydasm/target/release/ttydasm.exe')


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


# ---- parse objects ----
objs = []  # dicts: name, scope, section, addr, data(bytearray), relocs{off:sym}
section = None
cur = None
for line in src.splitlines():
    m = re.match(r'^(?:\.section )?\.?(text|rodata|data|sdata2|sdata|bss|sbss|sbss2)\b', line.strip())
    if line.startswith('.section') or line.strip() in ('.text', '.rodata', '.data'):
        mm = re.match(r'^(?:\.section )?(\.\w+)', line.strip())
        section = mm.group(1)
        continue
    m = re.match(r'^# \.\w+:0x[0-9A-F]+ \| (0x[0-9A-F]+) \| size: (0x[0-9A-F]+)', line)
    if m:
        pending_addr = int(m.group(1), 16)
        continue
    m = re.match(r'^\.obj (\S+), (\w+)', line)
    if m:
        cur = dict(name=m.group(1), scope=m.group(2), section=section, addr=pending_addr,
                   data=bytearray(), relocs={})
        objs.append(cur)
        continue
    if line.startswith('.endobj'):
        cur = None
        continue
    if cur is None:
        continue
    t = line.strip()
    if t.startswith('.4byte '):
        v = t[7:]
        if v.startswith('0x'):
            cur['data'] += struct.pack('>I', int(v, 16))
        else:
            sym, _, add = v.partition('+')
            cur['relocs'][len(cur['data'])] = (sym, int(add, 16) if add else 0)
            cur['data'] += b'\0\0\0\0'
    elif t.startswith('.rel '):
        sym, lab = [x.strip() for x in t[5:].split(',')]
        cur['relocs'][len(cur['data'])] = (sym, ('label', int(lab[3:], 16)))
        cur['data'] += bytes(4)
    elif t.startswith('.string '):
        cur['data'] += unesc(t[9:-1])
    elif t.startswith('.float '):
        cur['data'] += struct.pack('>f', float(t[7:]))
    elif t.startswith('.double '):
        cur['data'] += struct.pack('>d', float(t[8:]))
    elif t.startswith('.skip '):
        cur['data'] += b'\0' * int(t[6:], 0)
    elif t.startswith('.byte '):
        cur['data'] += bytes(int(x, 0) for x in t[6:].split(','))
    elif t.startswith('.2byte '):
        cur['data'] += b''.join(struct.pack('>H', int(x, 0)) for x in t[7:].split(','))

byname = {}
for o in objs:
    byname.setdefault(o['name'], o)
for o in objs:
    for off, (sym, add) in list(o['relocs'].items()):
        if isinstance(add, tuple):
            o['relocs'][off] = (sym, add[1] - byname[sym]['addr'] if sym in byname else 0)
strs = {o['name']: bytes(o['data']).split(b'\0')[0] for o in objs if o['name'].startswith('str_')}
# dtk sometimes labels a plain string with dat_ (e.g. when it is global); treat those as strings too
for o in objs:
    d = bytes(o['data']) + b'\0'  # .string adds the terminator
    # also strings dtk typed as floats (e.g. "GSO_D2_1" read as vec3_) when data points at them
    guessed = o['name'].startswith(('vec3_', 'float_')) and f'.4byte {o["name"]}\n' in src
    if (o['name'].startswith('dat_') or guessed) and o['section'] == '.rodata' and not o['relocs']:
        s, _, rest = d.partition(b'\0')
        if s and not rest.strip(b'\0') and all(b >= 0x20 or b in (9, 10) for b in s):
            strs[o['name']] = s
for o in objs:
    if o['name'].startswith('zero_') and o['section'] in ('.sdata2', '.rodata'):
        strs[o['name']] = b''
fns = re.findall(r'^\.fn (\S+), (\w+)', src, re.M)
fnames = {f for f, _ in fns}


def cstr(b):
    if all(32 <= x < 127 for x in b):
        return '"%s"' % b.decode().replace('\\', '\\\\').replace('"', '\\"')
    try:
        txt = b.decode('shift_jis')
    except UnicodeDecodeError:
        txt = '?'
    return '/*"%s"*/"%s"' % (txt, ''.join('\\x%02X' % x for x in b))


def ffmt(v):
    packed = struct.pack('>f', v)
    for p in range(1, 12):
        s = '%.*g' % (p, v)
        if 'e' in s and abs(v) >= 1:
            s = repr(float(s))
        if struct.pack('>f', float(s)) == packed:
            if 'e' not in s and '.' not in s and 'n' not in s:
                s += '.0'
            return s + 'f'
    return repr(v) + 'f'


# ---- type inference ----
types = {}  # name -> type key
UNIT_KIND = 0xC4
for o in objs:
    if o['section'] == '.data' and len(o['data']) == UNIT_KIND and o['scope'] == 'global' and 0xB8 in o['relocs']:
        types[o['name']] = 'kind'


def ref(o, off):
    r = o['relocs'].get(off)
    return r[0] if r else None


for name in [n for n, t in types.items() if t == 'kind']:
    k = byname[name]
    if ref(k, 0xB0):
        types[ref(k, 0xB0)] = 'regist'
    if ref(k, 0xB8):
        types[ref(k, 0xB8)] = 'parts'
    if ref(k, 0xBC):
        types[ref(k, 0xBC)] = 'evt'
    if ref(k, 0xC0):
        types[ref(k, 0xC0)] = 'datatable'
for name in [n for n, t in list(types.items()) if t == 'parts']:
    p = byname[name]
    for i in range(len(p['data']) // 0x4C):
        b = i * 0x4C
        if ref(p, b + 0x38):
            types[ref(p, b + 0x38)] = 'defence'
        if ref(p, b + 0x3C):
            types[ref(p, b + 0x3C)] = 'defence'
        if ref(p, b + 0x48):
            types[ref(p, b + 0x48)] = 'pose'
for name in [n for n, t in list(types.items()) if t == 'datatable']:
    d = byname.get(name)
    if d:
        for off in range(4, len(d['data']), 8):
            s = ref(d, off)
            if s in byname:
                types.setdefault(s, 'evt')
for o in objs:
    if o['name'].startswith('pose_table') and len(o['data']) % 8 == 0:
        types.setdefault(o['name'], 'pose')
# any other local data object whose first word looks like an evt command -> evt
for o in objs:
    if o['section'] in ('.data', '.sdata') and o['name'] not in types and not o['name'].startswith(('str_', 'gap_')):
        w = struct.unpack('>I', o['data'][:4])[0] if len(o['data']) >= 4 else 0
        last = struct.unpack('>I', o['data'][-4:])[0] if len(o['data']) >= 4 else 0
        if (w >> 16) < 0x20 and 1 <= (w & 0xFFFF) < 0x80 and (len(o['data']) % 4 == 0) and last == 1:
            # walk the command headers: the first END (opcode 1) must be the final word
            off, n = 0, len(o['data'])
            while off < n:
                hdr = struct.unpack('>I', o['data'][off:off + 4])[0]
                if (hdr & 0xFFFF) == 1:
                    break
                off += 4 + (hdr >> 16) * 4
            if off == n - 4:
                types[o['name']] = 'evt'

# ---- emit helpers ----
used_ext = {}


def word_val(o, off, kind='i'):
    r = o['relocs'].get(off)
    if r:
        sym, add = r
        if sym in strs:
            return cstr(strs[sym])
        if sym not in byname and sym not in fnames:
            used_ext.setdefault(sym, 'data')
        if types.get(sym) in ('regist', 'defence', 'kind'):
            return '&' + sym
        if add:
            base = ('&' + sym) if types.get(sym) in ('regist', 'defence', 'kind') else sym
            return f'(void*)((u8*){base} + 0x{add:X})'
        return sym
    v = struct.unpack('>I', o['data'][off:off + 4])[0]
    if kind == 'f':
        return ffmt(struct.unpack('>f', o['data'][off:off + 4])[0])
    if kind == 'x':
        return '0x%X' % v if v else '0'
    if kind == 'p':
        return 'NULL' if v == 0 else '(void*)0x%X' % v
    return str(struct.unpack('>i', o['data'][off:off + 4])[0])


def fmt_fields(o, b, spec):
    """spec: list of (size, kind) where kind in i,u,f,p,x,s(pad)"""
    out = []
    off = b
    for size, kind in spec:
        if kind == 'pad':
            off += size
            continue
        if size == 4:
            out.append(word_val(o, off, kind))
        elif size == 2:
            v = struct.unpack('>h' if kind == 'i' else '>H', o['data'][off:off + 2])[0]
            out.append(str(v))
        elif size == 1:
            v = struct.unpack('>b' if kind == 'i' else '>B', o['data'][off:off + 1])[0]
            out.append(str(v))
        off += size
    return out


V = [(4, 'f')] * 3
KIND_SPEC = ([(4, 'i'), (4, 'p'), (2, 'i'), (2, 'i')] + [(1, 'u')] * 8 + [(2, 'i')] * 5 + [(2, 'pad')] + V +
             [(2, 'i')] * 2 + V + V + V + [(4, 'f')] * 2 + V + V + V + [(4, 'f')] * 2 +
             [(1, 'i')] * 3 + [(1, 'u')] * 3 + [(2, 'pad')] + V + [(4, 'p')] * 4 + [(4, 'x'), (4, 'p'), (1, 'i'),
                                                                                   (3, 'pad')] + [(4, 'p')] * 3)
PART_SPEC = [(4, 'i'), (4, 'p'), (4, 'p')] + V + V + V + [(2, 'i')] * 3 + [(2, 'pad')] + [(4, 'p')] * 2 + \
    [(4, 'x')] * 2 + [(4, 'p')]


def is_pair(o):
    d = o['data']
    return o['section'] == '.data' and len(d) == 8 and not o['relocs'] and \
        d in (bytes.fromhex('BF8000003F800000'), bytes.fromhex('3F800000BF800000'))


def emit(o):
    t = types.get(o['name'])
    st = ('static ' if o['scope'] == 'local' and '$' not in o['name'] else '') + ('__declspec(section ".data") ' if o['section'] == '.data' and len(o['data']) <= 48 else '')
    n = o['name']
    d = o['data']
    if t == 'kind':
        return f'{st}BattleUnitKind {n} = {{\n    ' + ',\n    '.join(fmt_fields(o, 0, KIND_SPEC)) + ',\n};\n'
    if t == 'parts':
        rows = ['    {' + ', '.join(fmt_fields(o, i * 0x4C, PART_SPEC)) + '},' for i in range(len(d) // 0x4C)]
        return f'{st}BattleUnitKindPart {n}[] = {{\n' + '\n'.join(rows) + '\n};\n'
    if t == 'regist':
        return f'{st}StatusVulnerability {n} = {{' + ', '.join(str(x) for x in d[:22]) + '};\n'
    if t == 'defence':
        tn = 'BattleUnitDefense' if n.endswith('defence') or 'attr' not in n else 'BattleUnitDefenseAttr'
        return f'{st}{tn} {n} = {{{{' + ', '.join(str(x) for x in d[:5]) + '}};\n'
    if t == 'pose':
        rows = ['    {%s, %s},' % (word_val(o, i), word_val(o, i + 4)) for i in range(0, len(d), 8)]
        return f'{st}PoseTableEntry {n}[] = {{\n' + '\n'.join(rows) + '\n};\n'
    if t == 'datatable':
        rows = ['    {%s, %s},' % (word_val(o, i), word_val(o, i + 4, 'p')) for i in range(0, len(d), 8)]
        return f'{st}BattleDataEntry {n}[] = {{\n' + '\n'.join(rows) + '\n};\n'
    if t == 'evt':
        r = subprocess.run([TTYDASM, 'extract', '-m', module, '-s', f'{n}@0x{o["addr"]:X}', '-p', '.'],
                           capture_output=True, text=True, encoding='utf-8')
        if r.returncode == 0 and 'EVT_BEGIN' in r.stdout:
            return st + ptr_offsets(o, fix_script(r.stdout))
        t = None
    if is_pair(o):
        return f'{st}u64 {n} = 0x{d.hex().upper()};\n'
    # fallback: raw words
    if len(d) % 4 == 0 and len(d):
        vals = [('(s32)' + v if (i in o['relocs']) else v) for i, v in ((i, word_val(o, i, 'i')) for i in range(0, len(d), 4))]
        rows = ['    ' + ', '.join(vals[i:i + 8]) + ',' for i in range(0, len(vals), 8)]
        return f'{st}s32 {n}[] = {{\n' + '\n'.join(rows) + '\n};\n'
    # odd-sized string object (e.g. a pose name in .data)
    text = d.rstrip(b'\0')
    if text and not o['relocs'] and all(32 <= c < 127 for c in text):
        esc = text.decode().replace('\\', '\\\\').replace('"', '\\"')
        return f'{st}char {n}[] = "{esc}";\n'
    return f'// TODO {n}: {len(d)} bytes\n'


def ptr_offsets(o, text):
    """ttydasm prints a pointer to sym+off as PTR(sym): restore the offsets from the object's relocations,
    matching each symbol's PTR() uses in order with its relocations in offset order."""
    per = {}
    for off in sorted(o['relocs']):
        sym, add = o['relocs'][off]
        per.setdefault(sym, []).append(add if isinstance(add, int) else 0)
    if not any(any(v) for v in per.values()):
        return text
    seen = {}

    def fix(m):
        sym = m.group(1)
        i = seen.get(sym, 0)
        seen[sym] = i + 1
        adds = per.get(sym, [])
        if i < len(adds) and adds[i]:
            return f'PTR((u8*){sym} + 0x{adds[i]:X})'
        return m.group(0)
    return re.sub(r'PTR\((\w+)\)', fix, text)


def fix_script(text):
    out = []
    for line in text.splitlines():
        line = line.replace(chr(0), '')
        if line.strip() == 'END':
            continue
        if line.startswith('EVT_BEGIN'):
            out.append(line)
            continue
        line = re.sub(r'STRING\("((?:[^"\\]|\\.)*?) *"\)', lambda m: 'STRING("%s")' % m.group(1), line)

        def wrap(m):
            name = m.group(0)
            if name in byname or name in used_ext or name in ext_names:
                if name in strs:
                    return name
                return f'PTR(&{name})' if types.get(name) in ('regist', 'defence', 'kind') else f'PTR({name})'
            return name
        head = ''
        mm = re.match(r'^(\s*CALL\(\s*\w+)(.*)$', line)
        if mm:
            head, line = mm.group(1), mm.group(2)
            fn = head.split('(')[1].strip()
            ext_funcs.add(fn)
        line = re.sub(r'(?<![\w"])[A-Za-z_]\w*(?![\w(])', wrap, line)
        out.append(head + line)
        for s in re.findall(r'PTR\((\w+)\)', head + line):
            if s not in byname:
                used_ext.setdefault(s, 'data')
    return '\n'.join(out) + '\n'


ext_funcs = set()
ext_names = set()
# names referenced from scripts that aren't local objects: gather from script relocations
for o in objs:
    for off, (sym, add) in o['relocs'].items():
        if sym not in byname and sym not in strs:
            ext_names.add(sym)

FWD = os.environ.get('UNITGEN_DEFERRED') != '1'  # RELs build with -inline auto (no deferred): source order = text order
# also place functions by their float constants (the pool keeps them next to the strings of the data defined before)
FLOATS = os.environ.get('UNITGEN_FLOATS') == '1'
fn_strs = {}
# compiler constants used only by code share the .rodata pool with strings, in order of first use
codeconst = {o['name'] for o in objs if o['section'] == '.rodata' and o['name'].startswith(('float_', 'double_', 'vec3_', 'zero_', 'dat_')) and o['name'] not in strs
             and not any(sym == o['name'] for x in objs for sym, _ in x['relocs'].values())}
# function-local statics (`name$N`) a snippet defines itself are emitted with the function: the function takes the
# static's place in the data order
FNSTATICS = set(filter(None, os.environ.get('UNITGEN_FNSTATICS', '').split(',')))
static_owner = {}
for m in re.finditer(r'^\.fn (\S+), (\w+)\n(.*?)^\.endfn', src, re.M | re.S):
    for r in re.findall(r'([\w$]+)@l', m.group(3)):
        if '$' in r and r.split('$')[0] in FNSTATICS and r not in static_owner and \
                any(o['name'] == r and o['section'] in ('.data', '.sdata') for o in objs):
            static_owner[r] = (m.group(1), m.group(2))
owned = {f for f, _ in static_owner.values()}
for m in re.finditer(r'^\.fn (\S+), (\w+)\n(.*?)^\.endfn', src, re.M | re.S):
    refs = []
    for r in re.findall(r'(\w+)@l', m.group(3)):
        # constants are created when the function is parsed; string literals too for static functions, but a
        # global (deferred) function's strings are only created at codegen, after all the data
        # (zero_ objects count as empty strings; with FLOATS a code-only one is the 0.0f constant)
        if ((r in codeconst and (r.startswith(('vec3_', 'dat_')) or FLOATS)) or (r in strs and r.startswith(('vec3_', 'dat_'))) or ((FWD or m.group(2) == 'local') and r in strs and (not r.startswith('zero_') or FLOATS))) and r not in refs:
            refs.append(r)
    if refs:
        # constants are pooled in parse order, which the address order follows better than first use in the asm
        addr = {o['name']: (o['section'], o['addr']) for o in objs}
        refs.sort(key=lambda r: addr.get(r, ('', 0)))
    if refs:
        fn_strs[m.group(1)] = refs
    if os.environ.get('UNITGEN_DEBUG'):
        print('refs', m.group(1), refs, file=sys.stderr)
# every function goes through the ordered merge (reverse text order = source order) so their relative order holds
static_of = {f: r for r, (f, _) in static_owner.items()}
fn_objs = [dict(name=f, scope=sc, section='.text', relocs={i * 4: (r, 0) for i, r in enumerate(fn_strs.get(f, []))}, fn=True,
                static=static_of.get(f))
           for f, sc in (fns if FWD else reversed(fns))] if (fn_strs or FWD or owned) else []

body = []
order = [o for o in objs if o['section'] in ('.data', '.sdata') and not o['name'].startswith(('gap_', 'jumptable_'))]
if '--data-first' not in sys.argv:
    sd = [o for o in order if o['section'] == '.sdata']
    dd = [o for o in order if o['section'] == '.data']
    tt = list(fn_objs)
    pools = {}
    # with UNITGEN_FLOATS, a constant no function references (left by dead code) can't anchor anything
    fn_refd = {r for refs in fn_strs.values() for r in refs}
    for so in objs:
        if FLOATS and so['name'] in codeconst and so['name'] not in strs and so['name'] not in fn_refd:
            continue
        if so['name'] in strs or so['name'] in codeconst:
            pools.setdefault(so['section'], []).append(so['addr'])
    str_addr = {so['name']: (so['section'], so['addr']) for so in objs if so['name'] in strs or so['name'] in codeconst}
    # dedupe by content: first string object with given content in each pool
    expected = {sec: sorted(v) for sec, v in pools.items()}
    used = set()

    def new_strs(o):
        res = []
        for off in sorted(o['relocs']):
            sym = o['relocs'][off][0]
            if sym in str_addr and sym not in used and sym not in [r for r in res]:
                res.append(sym)
        return res

    def ok(o):
        nxt = {sec: [a for a in v if a not in used_addr] for sec, v in expected.items()}
        for sym in new_strs(o):
            sec, a = str_addr[sym]
            if not nxt[sec] or nxt[sec][0] != a:
                return False
            nxt[sec].pop(0)
        return True

    used_addr = set()
    merged = []
    i = j = 0
    k = 0
    while i < len(dd) or j < len(sd) or k < len(tt):
        cands = []
        # a snippet-defined function static waits for its function, which is emitted in its place
        if i < len(dd) and dd[i]['name'] not in static_owner:
            cands.append(('d', dd[i]))
        if j < len(sd):
            cands.append(('s', sd[j]))
        if k < len(tt):
            st = tt[k].get('static')
            if st:
                if i < len(dd) and dd[i]['name'] == st:
                    cands.insert(0, ('t', tt[k]))
            elif ok(tt[k]) or not cands:
                cands.insert(0, ('t', tt[k]))
        if not cands:
            cands.append(('d', dd[i]) if i < len(dd) else ('t', tt[k]))
        pick = None
        for kind, o in cands:
            if ok(o) and new_strs(o):
                pick = (kind, o)
                break
        if pick is None:
            for kind, o in cands:
                if not new_strs(o):
                    pick = (kind, o)
                    break
        if pick is None:
            pick = cands[0]
        kind, o = pick
        for sym in new_strs(o):
            used.add(sym)
            used_addr.add(str_addr[sym][1])
        merged.append(o)
        if kind == 'd':
            i += 1
        elif kind == 't':
            k += 1
            if o.get('static') and i < len(dd) and dd[i]['name'] == o['static']:
                for sym in new_strs(dd[i]):
                    used.add(sym)
                    used_addr.add(str_addr[sym][1])
                i += 1
        else:
            j += 1
    order = merged
def todo(f, scope):
    return f'// TODO: {"static " if scope == "local" else ""}USER_FUNC({f}) {{ }}'


placed = set()
for o in order:
    if o.get('fn'):
        body.append(todo(o['name'], o['scope']) + '\n')
        placed.add(o['name'])
        continue
    if o['name'] in static_owner:
        continue
    body.append(emit(o))
order = [o for o in order if not o.get('fn') and o['name'] not in static_owner]

fwd = []
for o in order:
    t = types.get(o['name'])
    n = o['name']
    size = len(o['data'])
    decl = (f'u64 {n}' if is_pair(o) else None) or {'parts': f'BattleUnitKindPart {n}[{size // 0x4C}]', 'regist': f'StatusVulnerability {n}',
            'defence': ('BattleUnitDefenseAttr ' if 'attr' in n else 'BattleUnitDefense ') + n, 'pose': f'PoseTableEntry {n}[{size // 8}]',
            'datatable': f'BattleDataEntry {n}[{size // 8}]', 'kind': f'BattleUnitKind {n}'}.get(t, f's32 {n}[{size // 4}]')
    if size % 4 and t is None and emit(o).startswith(('char ', 'static char ', '__declspec(section ".data") char ')):
        decl = f'char {n}[]'
    fwd.append(('static ' if o['scope'] == 'local' and '$' not in o['name'] else '') + ('__declspec(section ".data") ' if o['section'] == '.data' and len(o['data']) <= 48 else '') + f'{decl};')

_out = []
_out.append('#include "battle/battle_unit.h"')
_out.append('#include "evt/evt_cmd.h"')
_out.append('')
for f in sorted(ext_funcs | (fnames & ext_funcs)):
    _out.append(f'USER_FUNC({f});')
for f, scope in fns:
    if f not in ext_funcs:
        _out.append(f'USER_FUNC({f});')
for e in sorted(set(used_ext) - ext_funcs - fnames):
    _out.append(f'extern s32 {e}[];')
_out.append('')
_out.append('\n'.join(fwd))
_out.append('')
_out.append('\n'.join(body))
for f, scope in (fns if FWD else reversed(fns)):
    if f not in placed:
        _out.append(todo(f, scope))

_text = '\n'.join(str(x) for x in _out)
_base = base.split('/')[-1].replace('unit_party_', '').replace('unit_', '')
_text = re.sub(r'(?<![\w$])(\w+(?:\$\w+)+)', lambda m: 'fd_' + _base + '_' + m.group(1).replace('$', '_'), _text)
print(_text)
