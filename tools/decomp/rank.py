"""rank.py [--dol|--rel] [--top N] [--units] [--min-fuzzy P] [--max-fuzzy P] [--filter S] [--desc] [--json]

Rank work from the objdiff report (build/G8MJ01/report.json, refreshed by the checker's builds).

Default view: NEAR-MISS FUNCTIONS across the DOL and all RELs, sorted by unmatched bytes
(size * (1 - fuzzy/100)), smallest first (= cheapest to finish). Only functions with
min-fuzzy <= fuzzy < 100 are listed (default min-fuzzy 50, so undecompiled 0% functions don't flood
the list). Columns: left bytes, size, fuzzy %, complete flag of the unit (C = unit already linked as
complete), unit, function.

--units: per-unit view of units not yet marked complete (add --all for complete ones too), ranked by
code bytes left, then functions left.
"""
import argparse
import json
import os
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))

ap = argparse.ArgumentParser()
g = ap.add_mutually_exclusive_group()
g.add_argument('--dol', action='store_true', help='only DOL (MarioSt) units')
g.add_argument('--rel', action='store_true', help='only REL units')
ap.add_argument('--top', type=int, default=40)
ap.add_argument('--units', action='store_true', help='per-unit view')
ap.add_argument('--min-fuzzy', type=float, default=50.0)
ap.add_argument('--max-fuzzy', type=float, default=100.0, help='exclusive upper bound (default 100)')
ap.add_argument('--filter', default='', help='substring of unit name (e.g. "las/" or "battle")')
ap.add_argument('--desc', action='store_true', help='largest remaining first')
ap.add_argument('--json', action='store_true')
ap.add_argument('--all', action='store_true', help='--units: also list complete units (their data%% is often <100 '
                'only because of anonymous-symbol pairing)')
ap.add_argument('--report', default=os.path.join(ROOT, 'build', 'G8MJ01', 'report.json'))
a = ap.parse_args()

rep = json.load(open(a.report, encoding='utf-8'))


def want(u):
    md = u.get('metadata', {})
    is_dol = md.get('module_name', u['name'].split('/')[0]) == 'MarioSt'
    if a.dol and not is_dol or a.rel and is_dol:
        return False
    return a.filter in u['name']


def fz(f):
    return float(f.get('fuzzy_match_percent', 0.0))  # proto3 omits 0


rows = []
for u in rep['units']:
    if not want(u):
        continue
    md = u.get('metadata', {})
    complete = bool(md.get('complete'))
    src = md.get('source_path', '')
    if not src and '/' in u['name'] and not u['name'].startswith('MarioSt/'):
        mod, rest = u['name'].split('/', 1)
        cand = f'rels/{mod}/src/{rest}.c'
        if os.path.exists(os.path.join(ROOT, cand)):
            src = cand + ' (not in configure)'
    if a.units:
        fns = u.get('functions', [])
        left = [f for f in fns if fz(f) < 100]
        bytes_left = sum(int(f.get('size', 0)) * (1 - fz(f) / 100) for f in fns)
        m = u.get('measures', {})
        data_pct = float(m.get('matched_data_percent', 0.0))
        if complete and not a.all or not left and complete and data_pct >= 100:
            continue
        rows.append({'unit': u['name'], 'complete': complete, 'source': src, 'funcs_left': len(left),
                     'funcs_total': len(fns), 'bytes_left': round(bytes_left, 1),
                     'code_total': int(m.get('total_code', 0)), 'fuzzy': float(m.get('fuzzy_match_percent', 0.0)),
                     'data_pct': data_pct})
        continue
    for f in u.get('functions', []):
        p = fz(f)
        if not (a.min_fuzzy <= p < a.max_fuzzy):
            continue
        size = int(f.get('size', 0))
        rows.append({'unit': u['name'], 'function': f['name'], 'size': size, 'fuzzy': round(p, 2),
                     'bytes_left': round(size * (1 - p / 100), 1), 'complete': complete, 'source': src})

if a.units:
    rows.sort(key=lambda r: (r['bytes_left'], r['funcs_left'], 100 - r['data_pct']), reverse=a.desc)
else:
    rows.sort(key=lambda r: (r['bytes_left'], -r['fuzzy']), reverse=a.desc)
total = len(rows)
rows = rows[:a.top] if a.top > 0 else rows

if a.json:
    json.dump({'total': total, 'rows': rows}, sys.stdout, indent=1)
    print()
    sys.exit(0)

if a.units:
    print(f'{"left":>8} {"fn left":>9} {"code%":>6} {"data%":>6} C  unit  (source)')
    for r in rows:
        print(f'{r["bytes_left"]:8.1f} {r["funcs_left"]:4d}/{r["funcs_total"]:<4d} {r["fuzzy"]:6.2f} {r["data_pct"]:6.2f} '
              f'{"C" if r["complete"] else " "}  {r["unit"]}  {r["source"] or "(no source)"}')
else:
    print(f'{"left":>7} {"size":>6} {"fuzzy":>6} C  unit :: function')
    for r in rows:
        print(f'{r["bytes_left"]:7.1f} {r["size"]:6d} {r["fuzzy"]:6.2f} {"C" if r["complete"] else " "}  '
              f'{r["unit"]} :: {r["function"]}')
print(f'-- {len(rows)} of {total} shown (report: {os.path.relpath(a.report, ROOT)})')
