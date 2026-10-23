#!/usr/bin/env python3
"""Render an objdiff report.json as a decomp.dev-style progress page.

Reads the report (never modifies it) and writes a single self-contained HTML
file: headline measures, per-category bars, and a treemap with one cell per
unit, sized by code bytes and colored by fuzzy match percent.

Usage:
    python tools/progress_treemap.py [build/G8MJ01/report.json] [-o build/progress.html]
        [--commit HASH] [--baseline report.json] [--baseline-label "upstream 62131fc"]
        [--svg docs/progress.svg]
"""

import argparse
import datetime
import html
import json
import os
import subprocess
import sys


def num(m, key):
    v = m.get(key, 0)
    try:
        return float(v)
    except (TypeError, ValueError):
        return 0.0


def summarize(m):
    return {
        "code": [num(m, "matched_code"), num(m, "total_code"), num(m, "complete_code")],
        "data": [num(m, "matched_data"), num(m, "total_data"), num(m, "complete_data")],
        "funcs": [num(m, "matched_functions"), num(m, "total_functions")],
        "units": [num(m, "complete_units"), num(m, "total_units")],
        "fuzzy": num(m, "fuzzy_match_percent"),
    }


def group_of(unit):
    name = unit["name"]
    module = unit.get("metadata", {}).get("module_name") or name.split("/")[0]
    parts = name.split("/")
    if module == "MarioSt":
        if len(parts) > 2:
            sub = parts[1]
            if sub.endswith(".a"):
                sub = "runtime libs"
            return "DOL", sub
        return "DOL", "core"
    return "REL", module


def load(path):
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


def true_c_info(root, report):
    """(L 2026-10-19) True C: asm stand-ins are not matched. Returns (stats, asm fns by file basename,
    baseline fuzzy by (basename, fn)) from scratch/true_c.py + paved.py, or ({}, {}, {}) if unavailable."""
    try:
        import importlib.util
        sys.path.insert(0, os.path.join(root, "scratch"))
        spec = importlib.util.spec_from_file_location("true_c", os.path.join(root, "scratch", "true_c.py"))
        tc = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(tc)
        import paved
        base = load(paved.BASELINE)
        bf = {(u["name"].rsplit("/", 1)[-1], f["name"]): num(f, "fuzzy_match_percent")
              for u in base["units"] for f in u.get("functions") or []}
        st = tc.stats(report)
        st["_paved"] = {(b, n) for b, n, _ in paved.stats()["paved"]}
        return st, paved.asm_fns_by_file(), bf
    except Exception as e:
        print(f"true C info unavailable ({e}); showing raw report figures")
        return {}, {}, {}


def build_payload(report, commit, baseline, baseline_label, root=None):
    stats, asm, bf = true_c_info(root, report) if root else ({}, {}, {})
    units = []
    for u in report.get("units", []):
        m = u.get("measures", {})
        size = num(m, "total_code")
        if size <= 0:
            continue
        kind, group = group_of(u)
        mc, fz = num(m, "matched_code_percent"), num(m, "fuzzy_match_percent")
        fn_ok, fn_tot = int(num(m, "matched_functions")), int(num(m, "total_functions"))
        complete = bool(u.get("metadata", {}).get("complete"))
        a = asm.get(u["name"].rsplit("/", 1)[-1], ())
        n_asm = n_paved = 0
        if a:
            # L 2026-10-19: the map reflects only NEEDED asm (C that never matched). Paved asm sits over C that
            # matched, so it counts as matched here; needed asm counts as unmatched (fuzzy at its C's score).
            mbytes = fbytes = 0.0
            for f in u.get("functions") or []:
                s = num(f, "size")
                key = (u["name"].rsplit("/", 1)[-1], f["name"])
                if f["name"] in a:
                    n_asm += 1
                    if key in stats.get("_paved", ()):
                        n_paved += 1
                        fbytes += s * 100
                        mbytes += s
                    else:
                        fbytes += s * bf.get(key, 0.0)
                else:
                    fbytes += s * num(f, "fuzzy_match_percent")
                    if num(f, "fuzzy_match_percent") >= 100:
                        mbytes += s
            mc, fz = 100 * mbytes / size, fbytes / size
            fn_ok -= n_asm - n_paved
            # blue: links only thanks to needed asm; a file whose asm is all paved is green (its C matched)
            linked_asm = complete and n_asm > n_paved
            complete = complete and n_asm == n_paved
        else:
            linked_asm = False
        units.append({
            "n": u["name"],
            "k": kind,
            "g": group,
            "s": int(size),
            "f": round(fz, 2),
            "mc": round(mc, 2),
            "fn": [fn_ok, fn_tot],
            "c": complete,
            "asm": n_asm,
            "pv": n_paved,
            "la": linked_asm,
            "cat": u.get("metadata", {}).get("progress_categories", []),
        })
    cats = [{"id": c["id"], "name": c["name"], "m": summarize(c.get("measures", {}))}
            for c in report.get("categories", [])]
    payload = {
        "overall": summarize(report.get("measures", {})),
        "categories": cats,
        "units": units,
        "commit": commit,
        "generated": datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC"),
    }
    if stats:
        # headline and category bars show true C too: rebuild code/function sums from the true-C unit figures
        def resum(us, m):
            t = sum(x["s"] for x in us) or 1
            s = summarize(m)
            s["code"] = [sum(x["s"] * x["mc"] / 100 for x in us), t, sum(x["s"] for x in us if x["c"])]
            s["funcs"] = [sum(x["fn"][0] for x in us), sum(x["fn"][1] for x in us)]
            s["units"] = [sum(1 for x in us if x["c"]), len(us)]
            s["fuzzy"] = sum(x["s"] * x["f"] for x in us) / t
            return s
        # L 2026-10-19: Code/Functions bars show the build (100%) again; the map's blue cells and the true C
        # note carry the asm distinction. resum() is kept for a true-C-bars view if wanted later.
        payload["true"] ={k: stats[k] for k in ("true_code", "true_fuzzy", "true_linked", "c_fns", "asm_fns",
                                                 "total_fns", "build_code", "paved_fns", "needed_fns", "paved_bytes") if k in stats}
    if baseline is not None:
        payload["baseline"] = {"label": baseline_label, "m": summarize(baseline.get("measures", {}))}
    return payload


def squarify(values, x, y, w, h):
    """Squarified treemap layout; values sorted descending. Returns [(x, y, w, h)]."""
    out = []
    total = sum(values)
    if total <= 0 or w <= 0 or h <= 0:
        return [(x, y, 0, 0)] * len(values)
    scale = w * h / total
    rest = [v * scale for v in values]
    row = []

    def worst(r, length):
        s = sum(r)
        return max(length * length * max(r) / (s * s), s * s / (length * length * min(r)))

    def lay():
        nonlocal x, y, w, h
        s = sum(row)
        if w >= h:
            cw = s / h if h else 0
            cy = y
            for a in row:
                ch = a / cw if cw else 0
                out.append((x, cy, cw, ch))
                cy += ch
            x += cw
            w -= cw
        else:
            ch = s / w if w else 0
            cx = x
            for a in row:
                cw = a / ch if ch else 0
                out.append((cx, y, cw, ch))
                cx += cw
            y += ch
            h -= ch

    i = 0
    while i < len(rest):
        length = min(w, h)
        if not row or worst(row + [rest[i]], length) <= worst(row, length):
            row.append(rest[i])
            i += 1
        else:
            lay()
            row = []
    if row:
        lay()
    return out


def cell_color(u):
    if u["c"]:
        return "#30a454"
    if u.get("la"):
        # linked only thanks to asm stand-ins: blue, darker the more of the file is exact C
        import colorsys
        t = max(0.0, min(100.0, u["mc"])) / 100
        r, g, b = colorsys.hls_to_rgb(205 / 360, 0.72 - 0.30 * t, 0.60)
        return "#%02x%02x%02x" % (round(r * 255), round(g * 255), round(b * 255))
    if u["f"] >= 100:
        return "#7fd38a"
    import colorsys
    import math
    t = max(0.0, min(99.99, u["f"])) / 100
    hue = t * 85 / 360
    sat = (62 + 13 * math.sin(t * math.pi)) / 100
    light = (52 + 3 * math.sin(t * math.pi)) / 100
    r, g, b = colorsys.hls_to_rgb(hue, light, sat)
    return "#%02x%02x%02x" % (round(r * 255), round(g * 255), round(b * 255))


def render_svg(payload, width=960, height=540):
    """Static treemap for README embedding (no scripts, renders on GitHub)."""
    groups = {}
    for u in payload["units"]:
        key = ("rel/" if u["k"] == "REL" else "") + u["g"]
        label = u["g"] + ".rel" if u["k"] == "REL" else u["g"]
        g = groups.setdefault(key, {"label": label, "units": [], "v": 0, "m": 0.0})
        g["units"].append(u)
        g["v"] += u["s"]
        g["m"] += u["s"] * u["mc"] / 100
    glist = sorted(groups.values(), key=lambda g: -g["v"])
    o = payload["overall"]
    pc = lambda a: 100 * a[0] / a[1] if a[1] else 0
    head = 28
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height + head}" '
        f'viewBox="0 0 {width} {height + head}" font-family="Helvetica,Arial,sans-serif">',
        f'<rect width="{width}" height="{height + head}" fill="#14181a"/>',
        (f'<text x="8" y="19" font-size="14" fill="#e8ece8">C {t["true_code"]:.2f}% exact, {t["true_fuzzy"]:.2f}% fuzzy · '
         f'data {pc(o["data"]):.2f}% · functions {t.get("c_fns", "?")}/{t.get("total_fns", "?")} exact</text>'
         if (t := payload.get("true")) and "true_fuzzy" in t else
         f'<text x="8" y="19" font-size="14" fill="#e8ece8">Code {pc(o["code"]):.2f}% matched · '
         f'{100 * o["code"][2] / o["code"][1]:.2f}% fully linked · data {pc(o["data"]):.2f}% · '
         f'functions {int(o["funcs"][0])}/{int(o["funcs"][1])}</text>'),
        f'<text x="{width - 8}" y="19" font-size="11" fill="#9aa49c" text-anchor="end">'
        f'{html.escape(payload.get("commit") or "")} · {payload["generated"]}</text>',
    ]
    labels = []
    for (gx, gy, gw, gh), g in zip(squarify([g["v"] for g in glist], 0, head, width, height), glist):
        us = sorted(g["units"], key=lambda u: -u["s"])
        for (x, y, w, h), u in zip(squarify([u["s"] for u in us], gx + 1, gy + 1, gw - 2, gh - 2), us):
            if w < 0.3 or h < 0.3:
                continue
            parts.append(f'<rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}" fill="{cell_color(u)}" '
                         f'stroke="#14181a" stroke-width="0.5"/>')
        parts.append(f'<rect x="{gx:.1f}" y="{gy:.1f}" width="{gw:.1f}" height="{gh:.1f}" fill="none" stroke="#14181a" stroke-width="2"/>')
        if gw > 60 and gh > 18:
            text = f'{g["label"]} {100 * g["m"] / g["v"]:.0f}%'
            tw = min(gw - 6, 6.2 * len(text) + 8)
            labels.append(f'<rect x="{gx + 3:.1f}" y="{gy + 3:.1f}" width="{tw:.1f}" height="14" rx="2" fill="#ffffff" fill-opacity="0.8"/>'
                          f'<text x="{gx + 7:.1f}" y="{gy + 14:.1f}" font-size="10.5" font-weight="bold" fill="#111">{html.escape(text)}</text>')
    parts += labels
    parts.append("</svg>")
    return "\n".join(parts)


def git_head(path):
    try:
        out = subprocess.run(["git", "rev-parse", "--short", "HEAD"], cwd=path,
                             capture_output=True, text=True, timeout=10)
        return out.stdout.strip() or None
    except Exception:
        return None


def main():
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("report", nargs="?", default=os.path.join(root, "build", "G8MJ01", "report.json"))
    ap.add_argument("-o", "--output", default=os.path.join(root, "build", "progress.html"))
    ap.add_argument("--commit", help="commit label to show (default: git HEAD)")
    ap.add_argument("--baseline", help="optional older report.json to compare against")
    ap.add_argument("--baseline-label", default="baseline")
    ap.add_argument("--svg", help="also write a static SVG treemap here (for README embedding)")
    ap.add_argument("--raw", action="store_true",
                    help="show the report as-is; default is the C view for G8MJ01")
    args = ap.parse_args()

    report = load(args.report)
    baseline = load(args.baseline) if args.baseline else None
    commit = args.commit or git_head(root)
    # true C uses the JP source scan and the JP 10-16 baseline, so it only applies to the G8MJ01 report
    jp = "G8MJ01" in os.path.abspath(args.report)
    payload = build_payload(report, commit, baseline, args.baseline_label, None if args.raw or not jp else root)

    template_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "progress_treemap.html")
    with open(template_path, "r", encoding="utf-8") as f:
        template = f.read()
    data = json.dumps(payload, separators=(",", ":")).replace("</", "<\\/")
    out = template.replace("/*__DATA__*/null", data)
    out = out.replace("__COMMIT__", html.escape(commit or "working tree"))
    if (t := payload.get("true")) and "true_fuzzy" in t:
        note = (f'<p class="cmp">All code is C. The map colours each file by how closely its C matches the original: '
                f'<b>green</b> = byte-exact and linked. Hover a cell for its counts. '
                f'C: <b>{t["true_code"]:.2f}%</b> exact, <b>{t["true_fuzzy"]:.2f}%</b> fuzzy · '
                f'<b>{t.get("c_fns", "?")}/{t.get("total_fns", "?")}</b> functions exact.</p>')
        out = out.replace('<section class="bars"', note + '<section class="bars"', 1)

    os.makedirs(os.path.dirname(os.path.abspath(args.output)), exist_ok=True)
    with open(args.output, "w", encoding="utf-8") as f:
        f.write(out)
    if args.svg:
        os.makedirs(os.path.dirname(os.path.abspath(args.svg)), exist_ok=True)
        with open(args.svg, "w", encoding="utf-8") as f:
            f.write(render_svg(payload))
    o = payload["overall"]
    pct = lambda a: 100 * a[0] / a[1] if a[1] else 0
    print(f"{args.output}: code {pct(o['code']):.2f}%  linked {100 * o['code'][2] / o['code'][1]:.2f}%  "
          f"data {pct(o['data']):.2f}%  units shown {len(payload['units'])}")


if __name__ == "__main__":
    sys.exit(main())
