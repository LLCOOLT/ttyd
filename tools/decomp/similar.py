#!/usr/bin/env python3
"""Function-similarity lookup / clustering over the target asm (DOL + RELs).

Each function from build/G8MJ01/asm/**.s and build/G8MJ01/<mod>/asm/**.s is
turned into a normalized opcode sequence (mnemonic only; registers,
immediates and relocations masked).  Similarity = rapidfuzz normalized
Levenshtein similarity (1 - dist / max(len)) on those sequences, with a
length prefilter.  A secondary "regsim" compares mnemonic+register operands
(immediates/symbols masked) to rank exact-opcode ties.

Matched status always comes fresh from build/G8MJ01/report.json
(function fuzzy_match_percent == 100).

Usage:
  similar.py --build                 rebuild cache + tools/decomp/similar/clusters.json
  similar.py <fn> [--unit U]         nearest MATCHED functions (references) + source
  similar.py <fn> --all              nearest functions regardless of status
  similar.py --propagate <fn> [--unit U]
                                     unmatched near-duplicates of a matched fn
  similar.py --families [--top 40] [--min-insns 8]
                                     largest clusters with matched/unmatched counts
Options: --threshold T (default 0.9), -n N (results, default 8)

(coddog itself could not be built on this machine - no C toolchain / Windows SDK -
so this reimplements its `match`/`cluster` idea for multi-object MWCC output.)
"""
import argparse
import json
import os
import re
import sys
import time
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BUILD = os.path.join(ROOT, "build", "G8MJ01")
REPORT = os.path.join(BUILD, "report.json")
OUTDIR = os.path.join(ROOT, "tools", "decomp", "similar")
CACHE = os.path.join(OUTDIR, "cache.json")
CLUSTERS = os.path.join(OUTDIR, "clusters.json")
RELFUNCS = os.path.join(ROOT, "tools", "decomp", "relfuncs")

CACHE_THRESHOLD = 0.85   # neighbours kept in cache
CACHE_MAX_NEIGH = 64     # per unique sequence
MIN_FUZZY_INSNS = 3      # below this only exact-sequence peers are recorded
FAMILY_THRESHOLD = 0.95
FAMILY_MIN_INSNS = 16    # shorter fns join a family only on identical opcode+register form

INSN_RE = re.compile(r"^/\* [0-9A-Fa-f]+ [0-9A-Fa-f]+\s+(?:[0-9A-Fa-f]{2} ){4}\*/\s+(\S+)\s*(.*)$")
FN_RE = re.compile(r"^\.fn\s+([^,\s]+)")
REG_RE = re.compile(r"^(r\d+|f\d+|cr\d+|qr\d+|lr|ctr)$")


# ---------------------------------------------------------------- parsing
def asm_files():
    """Yield (unit_name, path) for every target asm file."""
    dol = os.path.join(BUILD, "asm")
    for dp, _, fns in os.walk(dol):
        for f in fns:
            if f.endswith(".s"):
                p = os.path.join(dp, f)
                rel = os.path.relpath(p, dol)[:-2].replace("\\", "/")
                yield "MarioSt/" + rel, p
    for mod in sorted(os.listdir(BUILD)):
        d = os.path.join(BUILD, mod, "asm")
        if mod == "asm" or not os.path.isdir(d):
            continue
        for dp, _, fns in os.walk(d):
            for f in fns:
                if f.endswith(".s"):
                    p = os.path.join(dp, f)
                    rel = os.path.relpath(p, d)[:-2].replace("\\", "/")
                    yield mod + "/" + rel, p


def norm_operand(op):
    op = op.strip()
    if REG_RE.match(op):
        return op
    m = re.match(r"^(.*)\((r\d+)\)$", op)
    if m:
        return "N(" + m.group(2) + ")"
    return "N"


def parse_asm(path):
    funcs = []
    cur = None
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            if cur is None:
                m = FN_RE.match(line)
                if m:
                    cur = [m.group(1), [], []]
                continue
            if line.startswith(".endfn"):
                funcs.append(cur)
                cur = None
                continue
            m = INSN_RE.match(line)
            if m:
                mn = m.group(1).rstrip("+-")
                cur[1].append(mn)
                ops = [norm_operand(o) for o in m.group(2).split(",")] if m.group(2) else []
                cur[2].append(mn + " " + ",".join(ops))
    return funcs


def load_report():
    with open(REPORT, encoding="utf-8") as fh:
        r = json.load(fh)
    status = {}
    srcs = {}
    for u in r["units"]:
        srcs[u["name"]] = u.get("metadata", {}).get("source_path")
        for f in u.get("functions", []) or []:
            status[(u["name"], f["name"])] = f.get("fuzzy_match_percent") == 100
    return status, srcs


def snippet_path(unit, fn):
    mod, _, rest = unit.partition("/")
    if mod == "MarioSt":
        return None
    base = rest.split("/")[-1]
    for cand in (os.path.join(RELFUNCS, mod, base, fn + ".c"),
                 os.path.join(RELFUNCS, mod, fn + ".c"),
                 os.path.join(RELFUNCS, fn + ".c")):
        if os.path.isfile(cand):
            return os.path.relpath(cand, ROOT).replace("\\", "/")
    return None


# ---------------------------------------------------------------- build
class Tok:
    def __init__(self):
        self.m = {}

    def enc(self, seq):
        out = []
        for t in seq:
            c = self.m.get(t)
            if c is None:
                c = self.m[t] = chr(0x100 + len(self.m))
            out.append(c)
        return "".join(out)


def build():
    from rapidfuzz.distance import Levenshtein
    from rapidfuzz import process

    t0 = time.time()
    os.makedirs(OUTDIR, exist_ok=True)
    otok, rtok = Tok(), Tok()
    funcs = []  # dict(unit, name, n, op, rg)
    for unit, path in asm_files():
        for name, ops, rgs in parse_asm(path):
            funcs.append({"unit": unit, "name": name, "n": len(ops),
                          "op": otok.enc(ops), "rg": rtok.enc(rgs)})
    print(f"parsed {len(funcs)} functions in {time.time()-t0:.1f}s", file=sys.stderr)

    # unique opcode sequences
    uniq = {}
    for i, f in enumerate(funcs):
        uniq.setdefault(f["op"], []).append(i)
    useqs = sorted(uniq.keys(), key=len)
    uid_of = {s: k for k, s in enumerate(useqs)}
    for f in funcs:
        f["uid"] = uid_of[f["op"]]
    lens = [len(s) for s in useqs]
    print(f"{len(useqs)} unique opcode sequences", file=sys.stderr)

    neigh = [[] for _ in useqs]
    thr = CACHE_THRESHOLD
    import bisect
    for k, q in enumerate(useqs):
        L = len(q)
        if L < MIN_FUZZY_INSNS:
            continue
        c_lo = bisect.bisect_left(lens, max(MIN_FUZZY_INSNS, int(L * thr)))
        c_hi = bisect.bisect_right(lens, int(L / thr) + 1)
        res = process.extract(q, useqs[c_lo:c_hi], scorer=Levenshtein.normalized_similarity,
                              score_cutoff=thr, limit=CACHE_MAX_NEIGH + 1)
        lst = [(c_lo + idx, round(float(sc), 4)) for _, sc, idx in res if c_lo + idx != k]
        lst.sort(key=lambda x: -x[1])
        neigh[k] = lst[:CACHE_MAX_NEIGH]
    print(f"similarity done in {time.time()-t0:.1f}s", file=sys.stderr)

    cache = {
        "funcs": [{"unit": f["unit"], "name": f["name"], "n": f["n"], "uid": f["uid"], "rg": f["rg"]} for f in funcs],
        "members": [uniq[s] for s in useqs],
        "neigh": neigh,
    }
    with open(CACHE, "w", encoding="utf-8") as fh:
        json.dump(cache, fh, separators=(",", ":"))
    write_clusters(cache)
    print(f"wrote {os.path.relpath(CACHE, ROOT)}, {os.path.relpath(CLUSTERS, ROOT)} in {time.time()-t0:.1f}s",
          file=sys.stderr)


def load_cache():
    if not os.path.isfile(CACHE):
        print("no cache; building...", file=sys.stderr)
        build()
    with open(CACHE, encoding="utf-8") as fh:
        return json.load(fh)


# ---------------------------------------------------------------- queries
def neighbours(cache, i, threshold, limit=200):
    """[(j, sim, regsim)] sorted best-first for function index i."""
    from rapidfuzz.distance import Levenshtein
    funcs = cache["funcs"]
    f = funcs[i]
    out = []
    for j in cache["members"][f["uid"]]:
        if j != i:
            out.append((j, 1.0))
    if len(out) < limit:
        for u, s in cache["neigh"][f["uid"]]:
            if s < threshold:
                break
            for j in cache["members"][u]:
                out.append((j, s))
            if len(out) >= limit * 4:
                break
    res = [(j, s, Levenshtein.normalized_similarity(f["rg"], funcs[j]["rg"])) for j, s in out]
    res.sort(key=lambda x: (-x[1], -x[2]))
    return res[:limit]


def source_of(unit, name, srcs):
    return {"src": srcs.get(unit), "snippet": snippet_path(unit, name)}


def entry(cache, j, s, r, status, srcs, with_src):
    f = cache["funcs"][j]
    d = {"fn": f["name"], "unit": f["unit"], "size": f["n"] * 4, "sim": round(s, 4),
         "regsim": round(r, 4), "matched": status.get((f["unit"], f["name"]), False)}
    if with_src and d["matched"]:
        d.update(source_of(f["unit"], f["name"], srcs))
    return d


def families(cache, status):
    funcs = cache["funcs"]
    parent = list(range(len(funcs)))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        a, b = find(a), find(b)
        if a != b:
            parent[max(a, b)] = min(a, b)

    for uid, mem in enumerate(cache["members"]):
        n = funcs[mem[0]]["n"]
        if n >= FAMILY_MIN_INSNS:
            for j in mem[1:]:
                union(mem[0], j)
            for u, s in cache["neigh"][uid]:
                if s < FAMILY_THRESHOLD:
                    break
                union(mem[0], cache["members"][u][0])
        else:
            byrg = {}
            for j in mem:
                byrg.setdefault(funcs[j]["rg"], []).append(j)
            for grp in byrg.values():
                for j in grp[1:]:
                    union(grp[0], j)
    groups = defaultdict(list)
    for i in range(len(funcs)):
        groups[find(i)].append(i)
    fams = []
    for root, mem in groups.items():
        if len(mem) < 2:
            continue
        m = sum(1 for j in mem if status.get((funcs[j]["unit"], funcs[j]["name"]), False))
        fams.append({"members": mem, "matched": m, "unmatched": len(mem) - m})
    fams.sort(key=lambda f: (-f["unmatched"], -len(f["members"])))
    return fams


def write_clusters(cache):
    status, srcs = load_report()
    funcs = cache["funcs"]
    out = {}
    for i, f in enumerate(funcs):
        key = f["unit"] + ":" + f["name"]
        nb = neighbours(cache, i, 0.9, limit=200)
        d = {"fn": f["name"], "unit": f["unit"], "size": f["n"] * 4,
             "matched": status.get((f["unit"], f["name"]), False)}
        if d["matched"]:
            d.update(source_of(f["unit"], f["name"], srcs))
        d["similar"] = [entry(cache, j, s, r, status, srcs, True) for j, s, r in nb[:8]]
        best_m = [x for x in nb if status.get((funcs[x[0]]["unit"], funcs[x[0]]["name"]), False)][:3]
        d["best_matched"] = [entry(cache, j, s, r, status, srcs, True) for j, s, r in best_m]
        out[key] = d
    fams = families(cache, status)
    famout = []
    for k, fm in enumerate(fams):
        mem = fm["members"]
        famout.append({"id": k, "size": len(mem), "matched": fm["matched"], "unmatched": fm["unmatched"],
                       "insns": funcs[mem[0]]["n"],
                       "members": [funcs[j]["unit"] + ":" + funcs[j]["name"] for j in mem]})
        for j in mem:
            out[funcs[j]["unit"] + ":" + funcs[j]["name"]]["family"] = k
    unm = [d for d in out.values() if not d["matched"]]
    stats = {
        "functions": len(funcs),
        "matched": sum(1 for d in out.values() if d["matched"]),
        "unmatched_with_matched_ge_0.95": sum(1 for d in unm if d["best_matched"] and d["best_matched"][0]["sim"] >= 0.95),
        "unmatched_with_matched_ge_0.90": sum(1 for d in unm if d["best_matched"]),
        "families": len(famout),
        "report_mtime": time.ctime(os.path.getmtime(REPORT)),
    }
    with open(CLUSTERS, "w", encoding="utf-8") as fh:
        json.dump({"stats": stats, "families": famout, "functions": out}, fh, indent=1)
    print(json.dumps(stats), file=sys.stderr)


def find_fn(cache, name, unit):
    hits = [i for i, f in enumerate(cache["funcs"]) if f["name"] == name and (not unit or unit in f["unit"])]
    if not hits:
        sys.exit(f"function {name!r} not found" + (f" in unit matching {unit!r}" if unit else ""))
    if len(hits) > 1:
        units = sorted({cache["funcs"][i]["unit"] for i in hits})
        print(f"note: {name} exists in {len(hits)} units ({', '.join(units[:10])}"
              f"{'...' if len(units) > 10 else ''}); showing all, use --unit to narrow\n")
    return hits


def fmt(d, status_col=True):
    s = f"  {d['sim']*100:6.2f}% (regs {d['regsim']*100:5.1f}%)  {d['fn']:<40} {d['unit']:<36} 0x{d['size']:X}"
    if status_col:
        s += "  MATCHED" if d["matched"] else "  unmatched"
    if d.get("src"):
        s += f"\n           src: {d['src']}"
    if d.get("snippet"):
        s += f"   snippet: {d['snippet']}"
    return s


def cmd_lookup(args, propagate=False):
    cache = load_cache()
    status, srcs = load_report()
    for i in find_fn(cache, args.fn, args.unit):
        f = cache["funcs"][i]
        me = status.get((f["unit"], f["name"]), False)
        print(f"{f['name']}  [{f['unit']}]  size 0x{f['n']*4:X}  {'MATCHED' if me else 'unmatched'}")
        if me:
            so = source_of(f["unit"], f["name"], srcs)
            print(f"  src: {so['src']}" + (f"   snippet: {so['snippet']}" if so["snippet"] else ""))
        nb = neighbours(cache, i, args.threshold, limit=1000)
        rows = [entry(cache, j, s, r, status, srcs, True) for j, s, r in nb]
        if propagate:
            rows = [d for d in rows if not d["matched"]]
            title = f"unmatched near-duplicates (>= {args.threshold}):"
        elif args.all:
            title = f"nearest functions (>= {args.threshold}):"
        else:
            rows = [d for d in rows if d["matched"]]
            title = f"nearest MATCHED functions (>= {args.threshold}):"
        print(title)
        n = args.n if not propagate else max(args.n, 1000)
        for d in rows[:n]:
            print(fmt(d, status_col=args.all))
        if not rows:
            print("  (none)")
        print()


def cmd_families(args):
    cache = load_cache()
    status, srcs = load_report()
    funcs = cache["funcs"]
    fams = [f for f in families(cache, status) if funcs[f["members"][0]]["n"] >= args.min_insns]
    if args.sort == "size":
        fams.sort(key=lambda f: -len(f["members"]))
    print(f"{'#':>3} {'size':>4} {'match':>5} {'unm':>4} {'insns':>5}  example (matched ref first)")
    for k, fm in enumerate(fams[:args.top]):
        mem = fm["members"]
        ref = next((j for j in mem if status.get((funcs[j]["unit"], funcs[j]["name"]))), None)
        ex = ref if ref is not None else mem[0]
        tag = "ref " if ref is not None else ""
        units = sorted({funcs[j]["unit"].split("/")[0] for j in mem})
        print(f"{k:>3} {len(mem):>4} {fm['matched']:>5} {fm['unmatched']:>4} {funcs[mem[0]]['n']:>5}  "
              f"{tag}{funcs[ex]['name']} [{funcs[ex]['unit']}]  mods: {','.join(units[:8])}{'...' if len(units) > 8 else ''}")
        if args.verbose:
            for j in mem:
                st = "M" if status.get((funcs[j]["unit"], funcs[j]["name"])) else "-"
                print(f"        {st} {funcs[j]['name']} [{funcs[j]['unit']}]")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("fn", nargs="?")
    ap.add_argument("--unit", help="substring of unit name (e.g. aji/aji_01 or MarioSt/battle)")
    ap.add_argument("--build", action="store_true", help="rebuild cache and clusters.json")
    ap.add_argument("--clusters", action="store_true", help="rewrite clusters.json from cache with fresh report.json")
    ap.add_argument("--propagate", metavar="FN")
    ap.add_argument("--families", action="store_true")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--min-insns", type=int, default=1, help="families: skip families of tiny functions")
    ap.add_argument("--sort", choices=["unmatched", "size"], default="unmatched")
    ap.add_argument("-v", "--verbose", action="store_true", help="families: list members")
    ap.add_argument("--all", action="store_true", help="lookup: include unmatched neighbours")
    ap.add_argument("--threshold", type=float, default=0.9)
    ap.add_argument("-n", type=int, default=8)
    args = ap.parse_args()
    if args.build:
        build()
    elif args.clusters:
        write_clusters(load_cache())
    elif args.families:
        cmd_families(args)
    elif args.propagate:
        args.fn = args.propagate
        cmd_lookup(args, propagate=True)
    elif args.fn:
        cmd_lookup(args)
    elif not args.build:
        ap.print_help()


if __name__ == "__main__":
    main()
