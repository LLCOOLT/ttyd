"""odiff.py <source .c> [fn...] [--json] [--all] [--ctx N] [--rows N] [--ninja] [--keep]

Ninja-free per-function objdiff for agents (safe to run while the checker owns the build).
Compiles ONE source into a private temp dir and runs build/tools/objdiff-cli.exe against the split
target object, then prints a compact result:
  * section summary (match %, sizes when they differ)
  * per-function match % (only the non-100% ones unless --all)
  * for each requested fn: only the mismatching instruction rows (+ --ctx rows of context)
  * data mismatches: rodata/data/bss byte ranges that differ, mapped to the containing symbols,
    and relocation mismatches (different target symbol / addend), which relsec.py does not see
  * unpaired symbols: target functions / named globals with no counterpart in ours, and vice versa
--json emits all of that machine-readably (every function, all rows of requested fns).

Compiling:
  rels/<mod>/src/...c  -> like relcc.py (module cflags from build.ninja; honours RELCC_DEFERRED=1,
                          RELCC_EXTRA, RELCC_VER). --ninja uses the file's own configured ninja
                          command instead (only for units that configure.py builds).
  src/... or libs/...  -> the exact command from `python -m ninja -t commands <obj>` (read-only).
Target object path comes from objdiff.json (fallback: build/G8MJ01/[<mod>/]obj/<path>.o).
"""
import argparse
import base64
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
OBJDIFF = os.path.join(ROOT, 'build', 'tools', 'objdiff-cli.exe')

ap = argparse.ArgumentParser(usage=__doc__)
ap.add_argument('src')
ap.add_argument('fns', nargs='*')
ap.add_argument('--json', action='store_true')
ap.add_argument('--all', action='store_true', help='list 100%% functions too')
ap.add_argument('--ctx', type=int, default=2, help='context rows around mismatches')
ap.add_argument('--rows', type=int, default=0, help='max mismatch rows per fn (0 = no limit)')
ap.add_argument('--max-data', type=int, default=25, help='max data/reloc mismatch lines per section')
ap.add_argument('--ninja', action='store_true', help='REL: use the configured ninja command, not relcc')
ap.add_argument('--keep', action='store_true', help='keep the temp dir (prints its path)')
a = ap.parse_args()

os.chdir(ROOT)
src = a.src.replace('\\', '/')
if src.startswith('./'):
    src = src[2:]
is_rel = src.startswith('rels/')


def die(msg, code=1):
    if a.json:
        json.dump({'error': msg}, sys.stdout)
        print()
    else:
        print(msg)
    sys.exit(code)


# ---- locate unit / target -------------------------------------------------------------------
unit = None
try:
    for u in json.load(open('objdiff.json', encoding='utf-8'))['units']:
        if u.get('metadata', {}).get('source_path') == src:
            unit = u
            break
    if unit is None and is_rel:
        mod, rest = src.split('/')[1], src.split('/src/', 1)[1][:-2]
        for u in json.load(open('objdiff.json', encoding='utf-8'))['units']:
            if u['name'] == f'{mod}/{rest}':
                unit = u
                break
except (OSError, ValueError):
    pass

if is_rel:
    mod, rest = src.split('/')[1], src.split('/src/', 1)[1][:-2]
    target = (unit or {}).get('target_path') or f'build/G8MJ01/{mod}/obj/{rest}.o'
else:
    rest = src.split('src/', 1)[1][:-2]
    target = (unit or {}).get('target_path') or f'build/G8MJ01/obj/{rest}.o'
if not os.path.exists(target):
    die(f'no target object {target}')

tmp = tempfile.mkdtemp(prefix='odiff_')
ours = os.path.join(tmp, os.path.basename(rest) + '.o')


def cleanup():
    if a.keep:
        print(f'(kept {tmp})', file=sys.stderr)
    else:
        shutil.rmtree(tmp, ignore_errors=True)


# ---- compile ----------------------------------------------------------------------------------
def ninja_cmd(obj):
    r = subprocess.run([sys.executable, '-m', 'ninja', '-t', 'commands', obj.replace('/', '\\')],
                       capture_output=True, text=True)
    lines = r.stdout.strip().splitlines()
    if not lines:
        return None
    line = lines[-1].split(' && ')[0].replace(' -MMD', '').replace(' -MD', '')  # no stray .d in cwd
    line, n = re.subn(r' -o \S+', lambda m: ' -o ' + ours.replace('\\', '\\\\'), line, count=1)
    return line if n else None


if is_rel and not a.ninja:
    r = subprocess.run([sys.executable, '-I', os.path.join(HERE, 'relcc.py'), src, tmp],
                       capture_output=True, text=True, encoding='utf-8', errors='replace')
else:
    base = (unit or {}).get('base_path') or (None if is_rel else f'build/G8MJ01/src/{rest}.o')
    cmd = base and ninja_cmd(base)
    if not cmd:
        cleanup()
        die(f'no ninja compile command for {base or src} (not configured?)')
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True, encoding='utf-8', errors='replace')
if r.returncode or not os.path.exists(ours):
    out = (r.stdout + r.stderr).strip()
    cleanup()
    die('compile failed:\n' + out[-4000:])

# ---- diff -------------------------------------------------------------------------------------
dj = os.path.join(tmp, 'diff.json')
r = subprocess.run([OBJDIFF, '--no-color', '-L', 'error', 'diff', '-1', target, '-2', ours, '-o', dj],
                   capture_output=True, text=True, encoding='utf-8', errors='replace')
if r.returncode or not os.path.exists(dj):
    cleanup()
    die('objdiff-cli failed:\n' + (r.stdout + r.stderr)[-3000:])
D = json.load(open(dj, encoding='utf-8'))
# second pass with the progress report's scoring (relocation targets ignored): 'report' per fn
REP = {}
r2 = subprocess.run([OBJDIFF, '--no-color', '-L', 'error', 'diff', '-1', target, '-2', ours, '-c', 'functionRelocDiffs=none',
                     '-o', dj + '.rep'], capture_output=True, text=True, encoding='utf-8', errors='replace')
if not r2.returncode and os.path.exists(dj + '.rep'):
    REP = {s['name']: float(s.get('match_percent', 0.0)) for s in json.load(open(dj + '.rep', encoding='utf-8'))['left']['symbols']
           if s.get('kind') == 'SYMBOL_FUNCTION' and s.get('target_symbol') is not None}
cleanup()

SIDES = ('left', 'right')   # left = target, right = ours


def i0(x):
    return int(x or 0)      # proto3 JSON omits zero values


# Section membership: objdiff lists each "[.sec]" section symbol followed by that section's symbols;
# "[.sec-N]" entries are its combined per-section pseudo symbols; undefined externs have no kind.
def index_side(side):
    syms = D[side]['symbols']
    by_sec, sec_of, cur = {}, {}, None
    for i, s in enumerate(syms):
        k, n = s.get('kind'), s['name']
        if k == 'SYMBOL_SECTION':
            m = re.match(r'^\[(.+?)\]$', n)
            cur = m.group(1) if m and not re.search(r'-\d+$', m.group(1)) else None
            continue
        if k in ('SYMBOL_FUNCTION', 'SYMBOL_OBJECT') and cur:
            by_sec.setdefault(cur, []).append(s)
            sec_of[i] = cur
    for v in by_sec.values():
        v.sort(key=lambda s: i0(s.get('address')))
    return syms, by_sec, sec_of


IDX = {side: index_side(side) for side in SIDES}


def sym_at(side, sec, off):
    best = None
    for s in IDX[side][1].get(sec, []):
        ad, sz = i0(s.get('address')), i0(s.get('size'))
        if ad <= off < ad + max(sz, 1):
            best = s
        elif ad > off:
            break
    return f"{best['name']}+0x{off - i0(best.get('address')):x}" if best else f'{sec}+0x{off:x}'


def reloc_target(side, rel):
    syms, _, sec_of = IDX[side]
    t = rel.get('target_symbol')
    name = syms[t]['name'] if t is not None and t < len(syms) else '?'
    if t in sec_of:
        name += f'@{sec_of[t]}'
    ad = i0(rel.get('addend'))
    return name + (f'{ad:+#x}' if ad else '')


# ---- sections ---------------------------------------------------------------------------------
secs = {}
for side in SIDES:
    for s in D[side]['sections']:
        if s.get('kind'):
            secs.setdefault(s['name'], {})[side] = s
sec_rows = []
for name, d in secs.items():
    L, R = d.get('left', {}), d.get('right', {})
    sec_rows.append({'name': name, 'kind': (L or R).get('kind', '')[8:].lower(),
                     'match': L.get('match_percent', R.get('match_percent', 0.0)) if L and R else None,
                     'size_target': i0(L.get('size')) if L else None, 'size_ours': i0(R.get('size')) if R else None})

# ---- functions --------------------------------------------------------------------------------
Lsyms, Rsyms = IDX['left'][0], IDX['right'][0]
def exact_pct(L, R):
    """% of instruction rows with no diff of any kind (args/relocs included); 100.0 only for a byte-exact fn."""
    li, ri = L.get('instructions', []), R.get('instructions', [])
    n = max(len(li), len(ri))
    if not n:
        return None
    ok = sum(1 for k in range(n) if k < len(li) and k < len(ri)
             and not li[k].get('diff_kind') and not ri[k].get('diff_kind'))
    return round(100.0 * ok / n, 4)


funcs = []
for s in Lsyms:
    if s.get('kind') == 'SYMBOL_FUNCTION':
        t = s.get('target_symbol')
        funcs.append({'name': s['name'], 'size': i0(s.get('size')),
                      'match': float(s.get('match_percent', 0.0)) if t is not None else None,
                      'exact': exact_pct(s, Rsyms[t]) if t is not None else None,
                      'report': REP.get(s['name']) if t is not None else None,
                      'ours': Rsyms[t]['name'] if t is not None else None})
unpaired = {'target': [], 'ours': []}
for side, key in (('left', 'target'), ('right', 'ours')):
    for s in IDX[side][0]:
        k = s.get('kind')
        if k not in ('SYMBOL_FUNCTION', 'SYMBOL_OBJECT') or s.get('target_symbol') is not None:
            continue
        # skip dtk auto-named literals/gaps (str_802C0F38, float_1_gon_00005a70, gap_03_...)
        if k == 'SYMBOL_OBJECT' and re.search(r'^gap_|_[0-9a-fA-F]{8}$', s['name']):
            continue
        if k == 'SYMBOL_FUNCTION' or s.get('flags', {}).get('global'):
            unpaired[key].append(('fn ' if k == 'SYMBOL_FUNCTION' else 'obj ') + s['name'])


def find_fn(name):
    for side in SIDES:
        for i, s in enumerate(IDX[side][0]):
            if s['name'] == name and s.get('kind') == 'SYMBOL_FUNCTION':
                return side, i, s
    return None, None, None


def ins_text(row):
    ins = row.get('instruction')
    return ins.get('formatted', '') if ins else ''


def fn_rows(name):
    side, i, s = find_fn(name)
    if s is None:
        return {'name': name, 'error': 'not found'}
    t = s.get('target_symbol')
    other = 'right' if side == 'left' else 'left'
    o = IDX[other][0][t] if t is not None else {}
    L, R = (s, o) if side == 'left' else (o, s)
    li, ri = L.get('instructions', []), R.get('instructions', [])
    rows = []
    for k in range(max(len(li), len(ri))):
        x = li[k] if k < len(li) else {}
        y = ri[k] if k < len(ri) else {}
        dk = x.get('diff_kind') or y.get('diff_kind') or ''
        ad = (x.get('instruction') or y.get('instruction') or {}).get('address')
        rows.append({'row': k, 'addr': i0(ad), 'kind': dk[5:].lower() if dk else '',
                     'target': ins_text(x), 'ours': ins_text(y)})
    return {'name': name, 'match': float(s.get('match_percent', 0.0)) if t is not None else None,
            'paired': t is not None, 'rows': rows}


fn_out = [fn_rows(n) for n in a.fns]


# ---- data / relocation mismatches -------------------------------------------------------------
def data_segments(side, sec):
    out, off = [], 0
    for e in sec.get('data_diff', []):
        b = base64.b64decode(e.get('data', '')) if e.get('data') else b''
        n = len(b)
        out.append({'kind': e.get('kind', ''), 'off': off, 'len': n, 'size': i0(e.get('size')), 'bytes': b})
        off += n
    return out


data_out = []
for name, d in secs.items():
    if 'left' not in d or 'right' not in d or d['left'].get('kind') == 'SECTION_CODE':
        continue
    item = {'section': name, 'bytes': [], 'relocs': []}
    L, R = data_segments('left', d['left']), data_segments('right', d['right'])
    for k in range(max(len(L), len(R))):
        x = L[k] if k < len(L) else None
        y = R[k] if k < len(R) else None
        kind = (x and x['kind']) or (y and y['kind'])
        if not kind:
            continue
        ent = {'kind': kind[5:].lower()}
        if x and x['len']:
            ent['target'] = sym_at('left', name, x['off'])
            ent['target_bytes'] = x['bytes'][:16].hex()
            ent['len_target'] = x['len']
        if y and y['len']:
            ent['ours'] = sym_at('right', name, y['off'])
            ent['ours_bytes'] = y['bytes'][:16].hex()
            ent['len_ours'] = y['len']
        item['bytes'].append(ent)
    rl = {}
    for side in SIDES:
        for e in d[side].get('reloc_diff', []):
            if e.get('kind'):
                rl.setdefault(i0(e.get('start')), {})[side] = e
    for off in sorted(rl):
        x, y = rl[off].get('left'), rl[off].get('right')
        ent = {'kind': ((x or y).get('kind') or '')[5:].lower(), 'offset': off,
               'type': (x or y)['relocation'].get('type_name', '')}
        if x:
            ent['at_target'] = sym_at('left', name, off)
            ent['target'] = reloc_target('left', x['relocation'])
        if y:
            ent['at_ours'] = sym_at('right', name, off)
            ent['ours'] = reloc_target('right', y['relocation'])
        item['relocs'].append(ent)
    if item['bytes'] or item['relocs']:
        data_out.append(item)

# ---- output -----------------------------------------------------------------------------------
result = {'source': src, 'unit': (unit or {}).get('name'), 'target': target, 'sections': sec_rows,
          'functions': funcs, 'diffs': fn_out, 'data': data_out, 'unpaired': unpaired}
if a.json:
    json.dump(result, sys.stdout, indent=1)
    print()
    sys.exit(0)

print(f'== {src}  vs  {target}')
print('   ' + '  '.join(
    f"{s['name']} {s['match']:.2f}%" if s['match'] is not None else f"{s['name']} (one side only)"
    for s in sec_rows) )
for s in sec_rows:
    if s['size_target'] is not None and s['size_ours'] is not None and s['size_target'] != s['size_ours']:
        print(f"   !! {s['name']} size target 0x{s['size_target']:x} vs ours 0x{s['size_ours']:x}")
full = [f for f in funcs if f['match'] == 100.0]
for f in funcs:
    if f['match'] != 100.0 or a.all:
        m = f"{f['match']:7.2f}%" if f['match'] is not None else ' MISSING'
        print(f"{m} {f['name']} ({f['size']}b)")
print(f"-- {len(full)}/{len(funcs)} functions 100%")
for k, lst in unpaired.items():
    if lst:
        lst = sorted(lst)  # 'fn ' sorts before 'obj '
        print(f"   only in {k} ({len(lst)}): " + ', '.join(lst[:12]) + (' ...' if len(lst) > 12 else ''))

for fd in fn_out:
    if 'error' in fd:
        print(f"\n== {fd['name']}: not found")
        continue
    print(f"\n== {fd['name']}: {fd['match']:.2f}%" if fd['paired'] else f"\n== {fd['name']}: unpaired")
    rows = fd['rows']
    bad = [r['row'] for r in rows if r['kind']]
    if not bad:
        continue
    show = set()
    for b in bad:
        show.update(range(max(0, b - a.ctx), min(len(rows), b + a.ctx + 1)))
    shown_bad, last = 0, None
    for r in rows:
        if r['row'] not in show:
            continue
        if last is not None and r['row'] != last + 1:
            print('   ...')
        last = r['row']
        if r['kind']:
            shown_bad += 1
            if a.rows and shown_bad > a.rows:
                print(f'   ... ({len(bad) - a.rows} more mismatching rows)')
                break
        tag = (r['kind'][:6] if r['kind'] else '').ljust(6)
        print(f"{tag} {r['addr']:5x}  {r['target']:42s} | {r['ours']}")
    print(f"-- {len(bad)} mismatching rows of {len(rows)}")

for d in data_out:
    print(f"\n== data {d['section']}: {len(d['bytes'])} byte diffs, {len(d['relocs'])} reloc diffs")
    n = 0
    for e in d['bytes']:
        n += 1
        if n > a.max_data:
            print('   ...')
            break
        lt = f"{e.get('target', '-')} [{e.get('len_target', 0)}] {e.get('target_bytes', '')}"
        rt = f"{e.get('ours', '-')} [{e.get('len_ours', 0)}] {e.get('ours_bytes', '')}"
        print(f"   {e['kind'][:7]:7s} {lt}  |  {rt}")
    n = 0
    for e in d['relocs']:
        n += 1
        if n > a.max_data:
            print('   ...')
            break
        at = e.get('at_target') or e.get('at_ours')
        print(f"   reloc {e['kind'][:7]:7s} {at} {e['type']}: {e.get('target', '-')}  |  {e.get('ours', '-')}")
