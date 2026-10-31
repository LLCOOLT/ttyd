#!/usr/bin/env python3
"""Check that the same function has the same name in every version's symbols.txt.

For each module (the main executable and each REL) and each source file of config/<version>/splits.txt,
the functions of that file are listed in address order for every version that has it and lined up
against the JP list (the demo against JP as well, US and PAL against each other and JP). Functions
that line up between two matching neighbours, in a run of the same length, are taken to be the same
function; if their names differ (and neither name appears elsewhere in the other version's file, which
would mean a function that moved), that is reported. Runs that do not line up (functions added or removed
in one version) are reported with -v for a manual look.

Known differences (the same slot holding a different function in another version) are listed in
KNOWN below with the reason. It needs no game files. Usage: python tools/check_symbols.py [-v]
"""

import argparse
import difflib
import os
import re
import sys
from typing import Dict, List, Optional, Tuple

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
VERSIONS = ["G8MJ01", "G8ME01", "G8MP01", "G8ME01_DEMO"]
# Pairs to compare: every version against JP, and PAL against US (PAL is built from the US code).
PAIRS = [("G8MJ01", "G8ME01"), ("G8MJ01", "G8MP01"), ("G8MJ01", "G8ME01_DEMO"), ("G8ME01", "G8MP01")]

SYMBOL = re.compile(r"^(\S+)\s*=\s*(\.\w+):0x([0-9A-Fa-f]+);\s*//(.*)$")
SPLIT_FILE = re.compile(r"^(\S.*):\s*$")
SPLIT_SECTION = re.compile(r"^\s+(\.\w+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)")
SIZE = re.compile(r"\bsize:0x([0-9A-Fa-f]+)")

# (module, file, name in version A, name in version B): reason the two are different functions.
KNOWN: Dict[Tuple[str, str, str, str], str] = {
    ("main", "sequence/seq_e3.c", "pressStartGX", "e3DispShadow"):
        "the demo's kiosk screen draws a character shadow (x, y, z) where JP copies the title's PRESS START",
}

Func = Tuple[str, int, int]  # name, address, size


def parse_module(version: str, module: str) -> Optional[Dict[str, List[Func]]]:
    base = os.path.join(ROOT, "config", version) if module == "main" else os.path.join(ROOT, "config", version, module)
    sym_path, split_path = os.path.join(base, "symbols.txt"), os.path.join(base, "splits.txt")
    if not (os.path.isfile(sym_path) and os.path.isfile(split_path)):
        return None
    ranges: List[Tuple[int, int, str]] = []
    current = None
    with open(split_path, encoding="utf-8") as f:
        for line in f:
            m = SPLIT_FILE.match(line)
            if m and not line.startswith("Sections"):
                current = m.group(1)
                continue
            m = SPLIT_SECTION.match(line)
            if m and current and m.group(1) in (".text", ".init"):
                ranges.append((int(m.group(2), 16), int(m.group(3), 16), current))
    ranges.sort()
    units: Dict[str, List[Func]] = {}
    with open(sym_path, encoding="utf-8") as f:
        for line in f:
            m = SYMBOL.match(line.strip())
            if not m or m.group(2) not in (".text", ".init") or "type:function" not in m.group(4):
                continue
            addr = int(m.group(3), 16)
            sm = SIZE.search(m.group(4))
            size = int(sm.group(1), 16) if sm else 0
            for start, end, unit in ranges:
                if start <= addr < end:
                    units.setdefault(unit, []).append((m.group(1), addr, size))
                    break
    for funcs in units.values():
        funcs.sort(key=lambda fn: fn[1])
    return units


def modules() -> List[str]:
    found = {"main"}
    for v in VERSIONS:
        d = os.path.join(ROOT, "config", v)
        for name in os.listdir(d):
            if os.path.isfile(os.path.join(d, name, "symbols.txt")):
                found.add(name)
    return sorted(found)


def compare(a: List[Func], b: List[Func]):
    """Yield (kind, funcs_a, funcs_b) for the parts of the two lists that are not identical."""
    names_a, names_b = [f[0] for f in a], [f[0] for f in b]
    sm = difflib.SequenceMatcher(a=names_a, b=names_b, autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        # A name that the other version has elsewhere in the file is a moved function, not a renamed one.
        moved = any(n in names_b for n in names_a[i1:i2]) or any(n in names_a for n in names_b[j1:j2])
        if tag == "replace" and i2 - i1 == j2 - j1 and not moved:
            yield "renamed", a[i1:i2], b[j1:j2]
        else:
            yield "unaligned", a[i1:i2], b[j1:j2]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("-v", "--verbose", action="store_true", help="also list runs that do not line up")
    args = parser.parse_args()

    data = {v: {m: parse_module(v, m) for m in modules()} for v in VERSIONS}
    problems = 0
    known = 0
    unaligned = 0
    for module in modules():
        for va, vb in PAIRS:
            ua, ub = data[va][module], data[vb][module]
            if not ua or not ub:
                continue
            for unit in sorted(set(ua) & set(ub)):
                for kind, fa, fb in compare(ua[unit], ub[unit]):
                    if kind == "renamed":
                        for x, y in zip(fa, fb):
                            key = (module, unit, x[0], y[0])
                            if key in KNOWN or (module, unit, y[0], x[0]) in KNOWN:
                                known += 1
                                continue
                            problems += 1
                            same = "same size" if x[2] == y[2] else f"size 0x{x[2]:X} vs 0x{y[2]:X}"
                            print(f"{module} {unit}: {va} {x[0]} (0x{x[1]:X}) / {vb} {y[0]} (0x{y[1]:X}), {same}")
                    else:
                        unaligned += 1
                        if args.verbose:
                            na = ", ".join(f[0] for f in fa) or "-"
                            nb = ", ".join(f[0] for f in fb) or "-"
                            print(f"  {module} {unit}: only in {va}: {na} | only in {vb}: {nb}")
    print(f"check_symbols: {problems} name mismatch(es), {known} known different function(s), "
          f"{unaligned} run(s) present in one version only" + ("" if args.verbose else " (-v lists them)"))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
