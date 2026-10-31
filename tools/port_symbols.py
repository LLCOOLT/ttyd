#!/usr/bin/env python3
"""Port a version's symbols.txt and splits.txt to another release of the same game.

The target is first auto-analysed by dtk (a config with no symbols or splits, run through `dtk dol split`), which
gives its function boundaries. Then, per module (main.dol or one REL):

1. Code: source and target functions are aligned in address order on their instruction words with relocated
   fields masked (branch targets, lis/addi/load/store immediates off lis registers, r2 and r13). Identical
   functions anchor the alignment; between anchors, functions pair up in order by similarity, and source
   functions that dtk did not split out are searched for directly in the target gap.
2. References: every reference made by paired code (and by pointers in paired data) gives a source/target
   address pair. For main.dol these are read from the instructions (zipped where the code is identical; where
   it differs, the two functions' lists of referenced addresses are aligned on opcode and register); for RELs
   from the relocation tables (REL references into main.dol vote on main.dol). Each source symbol takes the
   target address most of its references vote for. Functions are placed only by references to their start
   (calls, pointers), and those outvote the code pairing when two look-alike functions swapped places. A
   variable may move to the small-data twin of its section (.sdata <-> .data, .sbss <-> .bss, .sdata2 <->
   .rodata) when the versions were built with different -sdata/-sdata2 thresholds; a small-data access and a
   lis-based one pair up for this.
3. Neighbours: runs of symbols nothing refers to take the address shift of the placed symbols around them
   while their bytes agree (pointers and relocated words aside). What is left between two placed symbols is
   found by its contents in the target gap, or pairs in order with dtk's own symbol starts there.
   Placements that break source order (per target section) are dropped, and so are function starts where the
   code before falls through into them; steps 2-3 repeat until nothing changes.
4. Splits: each unit's section ranges come from the symbols it holds (those that moved section in their new
   section); a range never takes in another unit's symbols, starts or ends inside a symbol, or starts
   unaligned. Section alignments come from dtk's analysis of the target. In main.dol, unported variables at a
   unit boundary (small data in the source, .data/.bss/.rodata in the target) go to the unit whose code or
   data refers to them.
5. Symbols: a function comes before the labels at its address (mwld never finishes linking a split object
   with a label ahead of its function), @-named compiler symbols are local, and fn_/lbl_<addr> names that would
   clash with dtk's take their target address.

Source symbols with no confident target are left out of the target symbols (dtk names that address
fn_/lbl_ itself) and listed in the report, with the ported data whose contents differ and the functions
paired by similarity only (real differences between the versions, or places to check).

Usage:
  port_symbols.py --src-config config/G8ME01 --src-orig orig/G8ME01 \
                  --tgt-auto scratch/auto --tgt-orig orig/G8MP01 --out config/G8MP01 \
                  [--module NAME[=SRCCONFIG,SRCORIG]]... [--report report.txt] [--addr-map map.txt]
--module main is main.dol; other names are RELs. A module may take its source from another version
(e.g. --module dig=config/G8MJ01,orig/G8MJ01).
"""

import argparse
import bisect
import difflib
import os
import re
import struct
import sys
from collections import Counter, defaultdict

SYM_RE = re.compile(r"^(\S+) = (\.[\w.]+):0x([0-9A-Fa-f]+);\s*//\s*(.*)$")

LOADSTORE = set(range(32, 56))  # lwz .. stfdu
ADDI, ADDIS, ORI = 14, 15, 24

# A symbol may change section between versions only between a small-data section and its large counterpart, when
# the versions were compiled with different -sdata/-sdata2 thresholds.
SECTION_TWINS = {(".sdata", ".data"), (".data", ".sdata"), (".sbss", ".bss"), (".bss", ".sbss"),
                 (".sdata2", ".rodata"), (".rodata", ".sdata2"), (".sbss2", ".bss"), (".bss", ".sbss2")}


# ---------------------------------------------------------------------------------------------------------------
# Symbols and splits files


class Sym:
    __slots__ = ("name", "sec", "addr", "attrs", "size", "type")

    def __init__(self, name, sec, addr, attrs):
        self.name, self.sec, self.addr = name, sec, addr
        self.attrs = attrs
        self.size = 0
        self.type = "object"
        for a in attrs:
            if a.startswith("size:"):
                self.size = int(a[5:], 16)
            elif a.startswith("type:"):
                self.type = a[5:]

    def line(self, name=None, addr=None, size=None, sec=None):
        attrs = []
        t = self.addr if addr is None else addr
        for a in self.attrs:
            if a.startswith("size:"):
                if size is not None:
                    a = f"size:0x{size:X}"
            elif a.startswith("align:"):
                # an alignment the target address does not have is dropped to the one it has
                n = int(a[6:], 0)
                while n > 1 and t % n:
                    n //= 2
                if n < 4:
                    continue
                a = f"align:{n}"
            attrs.append(a)
        if size is not None and not any(a.startswith("size:") for a in self.attrs) and size:
            attrs.insert(1, f"size:0x{size:X}")
        if (name or self.name).startswith("@") and not any(a.startswith("scope:") for a in attrs):
            # compiler-generated: local to its unit, which matters once units of the target link from the split
            attrs.insert(2 if len(attrs) > 1 else len(attrs), "scope:local")
        return f"{name or self.name} = {sec or self.sec}:0x{(self.addr if addr is None else addr):08X}; // {' '.join(attrs)}"


def read_symbols(path):
    syms = []
    for line in open(path, encoding="utf-8"):
        m = SYM_RE.match(line.rstrip("\n"))
        if m:
            syms.append(Sym(m.group(1), m.group(2), int(m.group(3), 16), m.group(4).split()))
    return syms


def read_splits(path):
    """Returns (header lines, [(unit, unit header line, [(section, start, end, extra)])])."""
    header, units, cur = [], [], None
    for line in open(path, encoding="utf-8"):
        line = line.rstrip("\n")
        if line and not line[0].isspace():
            if line == "Sections:":
                cur = None
                header.append(line)
                continue
            cur = [line[:-1], line, []]
            units.append(cur)
            continue
        if cur is None:
            header.append(line)
            continue
        if not line.strip():
            continue
        parts = line.split()
        sec = parts[0]
        start = end = None
        extra = []
        for p in parts[1:]:
            if p.startswith("start:"):
                start = int(p[6:], 16)
            elif p.startswith("end:"):
                end = int(p[4:], 16)
            else:
                extra.append(p)
        cur[2].append((sec, start, end, extra))
    while header and not header[-1].strip():
        header.pop()
    return header, units


# ---------------------------------------------------------------------------------------------------------------
# Binaries


class Image:
    """A module's bytes by section: sections[name] = (start, end, data or None for bss)."""

    def __init__(self):
        self.sections = {}
        self.order = []

    def sec_of(self, addr):
        for name in self.order:
            s, e, _ = self.sections[name]
            if s <= addr < e:
                return name
        return None

    def word(self, sec, addr):
        s, e, d = self.sections[sec]
        if d is None or addr + 4 > e:
            return None
        return struct.unpack_from(">I", d, addr - s)[0]

    def bytes(self, sec, addr, n):
        s, e, d = self.sections[sec]
        if d is None:
            return None
        return d[addr - s:min(addr - s + n, e - s)]


def load_dol(path):
    b = open(path, "rb").read()
    offs = struct.unpack_from(">18I", b, 0)
    addrs = struct.unpack_from(">18I", b, 0x48)
    sizes = struct.unpack_from(">18I", b, 0x90)
    bss_addr, bss_size = struct.unpack_from(">2I", b, 0xD8)
    img = Image()
    names = {0: ".init", 1: ".text", 7: ".ctors", 8: ".dtors", 9: ".rodata", 10: ".data", 11: ".sdata", 12: ".sdata2"}
    for i, n in names.items():
        if sizes[i]:
            img.sections[n] = (addrs[i], addrs[i] + sizes[i], b[offs[i]:offs[i] + sizes[i]])
    for n in (".init", ".text"):
        # dtk ends code sections at the last non-zero word
        s, e, d = img.sections[n]
        while e > s and d[e - s - 4:e - s] == b"\0\0\0\0":
            e -= 4
        img.sections[n] = (s, e, d)
    sd, sd2 = img.sections[".sdata"], img.sections[".sdata2"]
    img.sections[".bss"] = (bss_addr, sd[0], None)
    img.sections[".sbss"] = (sd[1], sd2[0], None)
    img.sections[".sbss2"] = (sd2[1], bss_addr + bss_size, None)
    img.order = sorted(img.sections, key=lambda n: img.sections[n][0])
    # Small-data bases from __init_registers: lis r2/r13 then ori/addi
    init = img.sections[".init"]
    img.sda = {}
    words = struct.unpack_from(f">{len(init[2]) // 4}I", init[2])
    for i in range(len(words) - 1):
        w, n = words[i], words[i + 1]
        if w >> 26 == ADDIS and (w >> 16) & 31 == 0:
            rd = (w >> 21) & 31
            if rd in (2, 13) and n >> 26 in (ORI, ADDI) and (n >> 16) & 31 == rd:
                lo = n & 0xFFFF
                if n >> 26 == ADDI and lo & 0x8000:
                    lo -= 0x10000
                img.sda[rd] = ((w & 0xFFFF) << 16) + lo & 0xFFFFFFFF
    img.relocs = None
    return img


REL_SECTIONS = {1: ".text", 2: ".ctors", 3: ".dtors", 4: ".rodata", 5: ".data", 6: ".bss"}


def load_rel(path):
    """Sections are addressed by offset within the section (as in dtk's REL symbols). Relocations are
    {(section, offset): (type, module, target section name or None, addend)}."""
    b = open(path, "rb").read()
    mod_id, _, _, nsec, secoff = struct.unpack_from(">5I", b, 0)
    imp_off, imp_size = struct.unpack_from(">2I", b, 0x28)
    img = Image()
    for i in range(nsec):
        off, size = struct.unpack_from(">2I", b, secoff + i * 8)
        off &= ~1
        if not size or i not in REL_SECTIONS:
            continue
        name = REL_SECTIONS[i]
        img.sections[name] = (0, size, b[off:off + size] if off else None)
    img.order = [REL_SECTIONS[i] for i in sorted(REL_SECTIONS) if REL_SECTIONS[i] in img.sections]
    img.sda = {}
    img.mod_id = mod_id
    relocs = {}
    for i in range(imp_size // 8):
        mid, roff = struct.unpack_from(">2I", b, imp_off + i * 8)
        sec, pos = None, 0
        while True:
            o, t, s, add = struct.unpack_from(">HBBI", b, roff)
            roff += 8
            if t == 203:
                break
            if t == 202:
                sec, pos = REL_SECTIONS.get(s), 0
                continue
            pos += o
            if t == 201:
                continue
            if sec is None:
                continue
            tsec = REL_SECTIONS.get(s) if mid == mod_id else None
            relocs[(sec, pos)] = (t, mid, tsec, add)
    img.relocs = relocs
    return img


# ---------------------------------------------------------------------------------------------------------------
# Code masking


def mask_words(words):
    out = []
    lis = set()
    for w in words:
        op = w >> 26
        if op == 18:
            out.append(w & 0xFC000003)
            continue
        if op == 16:
            out.append(w & 0xFFFF0003)
            continue
        rd, ra = (w >> 21) & 31, (w >> 16) & 31
        if op == ADDIS and ra == 0:
            lis.add(rd)
            out.append(w & 0xFFFF0000)
            continue
        if op in LOADSTORE or op in (ADDI, ORI):
            src = rd if op == ORI else ra
            if src in (2, 13) and op != ORI or src in lis:
                out.append(w & 0xFFFF0000)
                if op != ORI and op not in (36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55) and rd != ra:
                    lis.discard(rd)
                continue
            if op != ORI and op not in (36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55):
                lis.discard(rd)
        out.append(w)
    return tuple(out)


def code_words(img, sec, addr, size):
    d = img.bytes(sec, addr, size)
    n = len(d) // 4
    return struct.unpack_from(f">{n}I", d) if n else ()


def code_refs(ws, wt):
    """Address pairs referenced by two structurally identical instruction streams (main.dol)."""
    # hs/ht: registers holding a lis value or a full address (lis+addi), per stream
    pairs = []
    hs, ht = {}, {}
    stores = (36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55)
    for w, v in zip(ws, wt):
        op = w >> 26
        rd, ra = (w >> 21) & 31, (w >> 16) & 31
        if op == 18:
            if w & 1:
                for r in (0, *range(3, 13)):
                    hs.pop(r, None), ht.pop(r, None)
            continue
        if op == ADDIS and ra == 0:
            hs[rd], ht[rd] = (w & 0xFFFF) << 16, (v & 0xFFFF) << 16
            continue
        if op in LOADSTORE or op == ADDI:
            si, ti = w & 0xFFFF, v & 0xFFFF
            si -= (si & 0x8000) << 1
            ti -= (ti & 0x8000) << 1
            if ra in hs:
                a, b = (hs[ra] + si) & 0xFFFFFFFF, (ht[ra] + ti) & 0xFFFFFFFF
                pairs.append((a, b))
                if op == ADDI:
                    hs[rd], ht[rd] = a, b
                    continue
            elif ra in (2, 13):
                pairs.append((ra, si, ti))
            if op not in stores:
                hs.pop(rd, None), ht.pop(rd, None)
            continue
        if op == ORI:
            if rd in hs:
                a, b = hs[rd] | (w & 0xFFFF), ht[rd] | (v & 0xFFFF)
                pairs.append((a, b))
                hs[ra], ht[ra] = a, b
                continue
            hs.pop(ra, None), ht.pop(ra, None)
            continue
        if op == 31:
            xo = (w >> 1) & 0x3FF
            if xo == 444 and rd == (w >> 11) & 31:  # mr ra, rs
                if rd in hs:
                    hs[ra], ht[ra] = hs[rd], ht[rd]
                else:
                    hs.pop(ra, None), ht.pop(ra, None)
                continue
            # most X-form results go to rd; logical ops write ra
            hs.pop(rd, None), ht.pop(rd, None)
            hs.pop(ra, None), ht.pop(ra, None)
            continue
        if op in (7, 8, 12, 13, 20, 21, 23, 24, 25, 26, 27, 28, 29):
            hs.pop(rd, None), ht.pop(rd, None)
            hs.pop(ra, None), ht.pop(ra, None)
    return pairs


def branch_pairs(ws, wt, sa, ta):
    out = []
    for i, (w, v) in enumerate(zip(ws, wt)):
        if w >> 26 == 18 and w & 1 and not w & 2:
            so = w & 0x03FFFFFC
            so -= (so & 0x02000000) << 1
            to = v & 0x03FFFFFC
            to -= (to & 0x02000000) << 1
            out.append((sa + 4 * i + so, ta + 4 * i + to))
    return out


def stream_refs(ws, base, sda):
    """The addresses one instruction stream refers to, in order, each keyed by (opcode, register) so that two
    versions of a function can be aligned on them even when their code differs. A small-data access (off r2/r13)
    and a lis-based one with the same opcode and register get the same key: a variable that moved between .sdata
    and .data pairs up."""
    out = []
    hs = {}
    stores = (36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55)
    for i, w in enumerate(ws):
        op = w >> 26
        rd, ra = (w >> 21) & 31, (w >> 16) & 31
        if op == 18:
            if w & 1:
                if not w & 2:
                    o = w & 0x03FFFFFC
                    o -= (o & 0x02000000) << 1
                    out.append((("bl",), (base + 4 * i + o) & 0xFFFFFFFF))
                for r in (0, *range(3, 13)):
                    hs.pop(r, None)
            continue
        if op == ADDIS and ra == 0:
            hs[rd] = (w & 0xFFFF) << 16
            continue
        if op in LOADSTORE or op == ADDI:
            si = w & 0xFFFF
            si -= (si & 0x8000) << 1
            a = None
            if ra in hs:
                a = (hs[ra] + si) & 0xFFFFFFFF
            elif ra in (2, 13) and ra in sda:
                a = (sda[ra] + si) & 0xFFFFFFFF
            if a is not None:
                out.append(((op, rd), a))
                if op == ADDI:
                    hs[rd] = a
                    continue
            if op not in stores:
                hs.pop(rd, None)
            continue
        if op == ORI:
            if rd in hs:
                a = hs[rd] | (w & 0xFFFF)
                out.append(((ADDI, ra), a))  # lis+ori builds the address lis+addi builds elsewhere
                hs[ra] = a
                continue
            hs.pop(ra, None)
            continue
        if op == 31:
            xo = (w >> 1) & 0x3FF
            if xo == 444 and rd == (w >> 11) & 31:  # mr ra, rs
                if rd in hs:
                    hs[ra] = hs[rd]
                else:
                    hs.pop(ra, None)
                continue
            hs.pop(rd, None)
            hs.pop(ra, None)
            continue
        if op in (7, 8, 12, 13, 20, 21, 23, 24, 25, 26, 27, 28, 29):
            hs.pop(rd, None)
            hs.pop(ra, None)
    return out


def aligned_refs(rs, rt):
    """Address pairs from two stream_refs lists, aligned on their keys."""
    sm = difflib.SequenceMatcher(None, [k for k, _ in rs], [k for k, _ in rt], autojunk=False)
    pairs = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            pairs += [(rs[i1 + k][1], rt[j1 + k][1]) for k in range(i2 - i1)]
    return pairs


# ---------------------------------------------------------------------------------------------------------------
# Porting one module


class Module:
    def __init__(self, name, src_syms, src_img, tgt_syms, tgt_img):
        self.name = name
        self.ssyms = src_syms
        self.simg = src_img
        self.tsyms = tgt_syms
        self.timg = tgt_img
        self.map = {}  # id(src sym) -> target addr
        self.size = {}  # id(src sym) -> target size (functions from fuzzy pairing)
        self.how = {}
        self.votes = defaultdict(Counter)
        self.dropped = set()
        by_sec = defaultdict(list)
        for s in src_syms:
            by_sec[s.sec].append(s)
        for v in by_sec.values():
            v.sort(key=lambda s: s.addr)
        self.sby_sec = by_sec
        self.saddrs = {k: [s.addr for s in v] for k, v in by_sec.items()}
        tby = defaultdict(list)
        for s in tgt_syms:
            tby[s.sec].append(s)
        for v in tby.values():
            v.sort(key=lambda s: s.addr)
        self.tby_sec = tby
        # dtk's own functions in the target, per code section: (starts, ends)
        self.tfuncs = {}
        for sec, v in tby.items():
            fs = sorted((x.addr, x.addr + x.size) for x in v if x.type == "function" and x.size)
            self.tfuncs[sec] = ([a for a, _ in fs], [b for _, b in fs])

    # -- code -------------------------------------------------------------------------------------------------
    def match_code(self):
        for sec in (".init", ".text"):
            if sec not in self.simg.sections or sec not in self.timg.sections:
                continue
            sf = [s for s in self.sby_sec.get(sec, []) if s.type == "function" and s.size]
            tf = [s for s in self.tby_sec.get(sec, []) if s.type == "function" and s.size]
            smask = [mask_words(code_words(self.simg, sec, s.addr, s.size)) for s in sf]
            tmask = [mask_words(code_words(self.timg, sec, s.addr, s.size)) for s in tf]
            sh = [hash(m) for m in smask]
            th = [hash(m) for m in tmask]
            sm = difflib.SequenceMatcher(None, sh, th, autojunk=False)
            for tag, i1, i2, j1, j2 in sm.get_opcodes():
                if tag == "equal":
                    for k in range(i2 - i1):
                        self._set(sf[i1 + k], tf[j1 + k].addr, "code-exact")
                    continue
                self._fuzzy(sec, sf[i1:i2], smask[i1:i2], tf[j1:j2], tmask[j1:j2])

    def fn_start_ok(self, sec, t):
        """A function may start inside one of dtk's target functions only where the code before cannot fall
        into it (blr, rfi, bctr or an unconditional branch)."""
        starts, ends = self.tfuncs.get(sec, ([], []))
        k = bisect.bisect_right(starts, t) - 1
        if k < 0 or starts[k] == t or t >= ends[k]:
            return True
        prev = self.timg.word(sec, t - 4)
        return prev is not None and (prev in (0x4E800020, 0x4C000064, 0x4E800420) or prev >> 26 == 18 and not prev & 3)

    def fn_size(self, s, sec, t):
        """A function's size in the target: the source's where the code agrees over it, otherwise that of dtk's
        function starting there (or the rest of the dtk function it starts in). dtk ends a function early when its
        last instructions cannot be reached (an epilogue after a call that never returns, a blr after an endless
        loop) and makes a function of them; the source size, where the code agrees over it, takes them back."""
        starts, ends = self.tfuncs.get(sec, ([], []))
        k = bisect.bisect_right(starts, t) - 1
        if k < 0 or t >= ends[k] or t + s.size == ends[k]:
            return None
        if self._bytes_agree(s.sec, s, t, sec) and (starts[k] != t or t + s.size < ends[k] or self._tail_unnamed(sec, ends[k], t + s.size)):
            return None
        return ends[k] - t

    def _tail_unnamed(self, sec, a, b):
        """Whether [a, b) holds nothing dtk named but its own fn_ functions."""
        syms = [x for x in self.tby_sec.get(sec, []) if a <= x.addr < b]
        return all(x.name.startswith("fn_") and x.type == "function" for x in syms)

    def _set(self, s, taddr, how, size=None):
        if s.type == "function" and not self.fn_start_ok(s.sec, taddr):
            self.dropped.add((id(s), taddr))
            return
        self.map[id(s)] = taddr
        self.how[id(s)] = how
        if size is not None:
            self.size[id(s)] = size

    def sec_at(self, sec, t):
        """The target section holding t for a symbol of sec: sec itself, or its small-data twin (main.dol only;
        REL sections are addressed by offset, and RELs have no small data)."""
        ts, te, _ = self.timg.sections.get(sec, (0, 0, None))
        if self.timg.relocs is not None or ts <= t <= te:
            return sec
        return self.timg.sec_of(t) or sec

    def tsec(self, s):
        """The target section of a placed symbol (its own section unless it moved to a small-data twin)."""
        return self.sec_at(s.sec, self.map[id(s)])

    def moved(self, s):
        return id(s) in self.map and self.tsec(s) != s.sec

    def _fuzzy(self, sec, sf, smask, tf, tmask):
        if not sf:
            return
        # Search the target gap for exact copies of functions dtk did not split out the same way
        lo = tf[0].addr if tf else None
        hi = tf[-1].addr + tf[-1].size if tf else None
        if lo is None:
            return
        gap_raw = code_words(self.timg, sec, lo, hi - lo)
        gap = mask_words(gap_raw)
        tstarts = {t.addr for t in tf}
        used = []
        rest = []
        cursor = 0
        for s, m in zip(sf, smask):
            found = -1
            n = len(m)
            for k in range(cursor, len(gap) - n + 1):
                if gap[k:k + n] == m:
                    found = k
                    break
            if found > 0 and lo + found * 4 not in tstarts:
                # A copy inside a dtk function is a function of its own only if the code before it cannot fall
                # into it (blr, rfi or an unconditional branch); otherwise the target function starts earlier
                prev = gap_raw[found - 1]
                if not (prev in (0x4E800020, 0x4C000064) or prev >> 26 == 18 and not prev & 3):
                    found = -1
            if found >= 0 and n >= 2:
                self._set(s, lo + found * 4, "code-exact-gap")
                cursor = found + n
                used.append((lo + found * 4, lo + found * 4 + n * 4))
            else:
                rest.append((s, m))
        if not rest:
            return
        # Pair the rest in order with unused target functions by similarity (monotonic DP)
        tleft = [(t, m) for t, m in zip(tf, tmask) if not any(a <= t.addr < b for a, b in used)]
        if not tleft:
            return
        n, k = len(rest), len(tleft)
        if n * k > 400000:  # too far apart to pair by similarity
            return
        sim = [[0.0] * k for _ in range(n)]
        for i, (s, m) in enumerate(rest):
            for j, (t, tm) in enumerate(tleft):
                if max(len(m), len(tm)) > 3 * min(len(m), len(tm)) + 4:
                    continue
                r = difflib.SequenceMatcher(None, m, tm, autojunk=False).ratio()
                sim[i][j] = r
        best = [[0.0] * (k + 1) for _ in range(n + 1)]
        choice = [[0] * (k + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(k - 1, -1, -1):
                a, b = best[i + 1][j], best[i][j + 1]
                c = sim[i][j] + best[i + 1][j + 1] if sim[i][j] >= 0.6 else -1
                if c >= a and c >= b:
                    best[i][j], choice[i][j] = c, 2
                elif a >= b:
                    best[i][j], choice[i][j] = a, 0
                else:
                    best[i][j], choice[i][j] = b, 1
        i = j = 0
        while i < n and j < k:
            c = choice[i][j]
            if c == 2:
                s, t = rest[i][0], tleft[j][0]
                # dtk's function may stop short of unreachable last instructions: where the code agrees over the
                # source size (and only dtk's own fn_ functions lie past dtk's end), that size is the function's
                size = t.size
                if (s.size > t.size and self._bytes_agree(s.sec, s, t.addr, t.sec)
                        and self._tail_unnamed(t.sec, t.addr + t.size, t.addr + s.size)):
                    size = s.size
                self._set(s, t.addr, f"code-similar {sim[i][j]:.2f}", size=size)
                i += 1
                j += 1
            elif c == 0:
                i += 1
            else:
                j += 1

    # -- references -------------------------------------------------------------------------------------------
    def sym_at(self, sec, addr):
        """The source symbol holding addr."""
        syms = self.sby_sec.get(sec, [])
        addrs = self.saddrs.get(sec, [])
        i = bisect.bisect_right(addrs, addr) - 1
        # Prefer a sized symbol containing addr; labels at the same address come first
        while i >= 0:
            s = syms[i]
            if s.addr == addr or s.addr <= addr < s.addr + max(s.size, 1):
                # walk back over symbols at the same address, prefer objects/functions with size
                j = i
                while j > 0 and syms[j - 1].addr == s.addr:
                    j -= 1
                cands = [x for x in syms[j:i + 1] if x.addr == s.addr]
                sized = [x for x in cands if x.size]
                return sized[0] if sized else cands[0]
            if s.addr < addr - 0x10000:
                break
            i -= 1
            if i >= 0 and syms[i].addr + max(syms[i].size, 1) <= addr and syms[i].addr != addr:
                break
        return None

    def vote(self, sa, ta, weight=1):
        sec = self.simg.sec_of(sa)
        tsec = self.timg.sec_of(ta)
        if sec is None or tsec is None or tsec != sec and (sec, tsec) not in SECTION_TWINS:
            return
        s = self.sym_at(sec, sa)
        if s is None or s.type == "function" and sa != s.addr:
            return  # code inside a function moves when the function changes size: only calls place it
        self.votes[id(s)][ta - (sa - s.addr)] += weight

    def collect_dol_code_refs(self, sda_s, sda_t):
        for sec in (".init", ".text"):
            for s in self.sby_sec.get(sec, []):
                if s.type != "function" or id(s) not in self.map:
                    continue
                ta = self.map[id(s)]
                ws = code_words(self.simg, sec, s.addr, s.size)
                wt = code_words(self.timg, sec, ta, self.size.get(id(s), s.size))
                if len(ws) != len(wt) or mask_words(ws) != mask_words(wt):
                    # different code (paired by similarity, or placed by references): align what the two
                    # versions refer to
                    for a, b in aligned_refs(stream_refs(ws, s.addr, sda_s), stream_refs(wt, ta, sda_t)):
                        self.vote(a, b)
                    continue
                for p in code_refs(ws, wt):
                    if len(p) == 3:
                        r, si, ti = p
                        if r in sda_s and r in sda_t:
                            self.vote((sda_s[r] + si) & 0xFFFFFFFF, (sda_t[r] + ti) & 0xFFFFFFFF)
                    else:
                        self.vote(*p)
                for a, b in branch_pairs(ws, wt, s.addr, ta):
                    self.vote(a, b, 3)

    def collect_rel_refs(self, main=None):
        """Relocation pairs at the same offset in paired symbols. Votes on this module, and on main for
        references to main.dol (when main is the same pair of versions)."""
        sr, tr = self.simg.relocs, self.timg.relocs
        sbypos = defaultdict(list)
        for (sec, off), r in sr.items():
            sbypos[sec].append(off)
        for v in sbypos.values():
            v.sort()
        for s in self.ssyms:
            if id(s) not in self.map or not s.size or self.how.get(id(s), "").startswith("code-similar"):
                continue
            ta = self.map[id(s)]
            offs = sbypos.get(s.sec, [])
            i = bisect.bisect_left(offs, s.addr)
            while i < len(offs) and offs[i] < s.addr + s.size:
                so = offs[i]
                i += 1
                a = sr[(s.sec, so)]
                b = tr.get((s.sec, ta + so - s.addr))
                if b is None or a[0] != b[0] or a[1] != self.simg.mod_id and a[1] != 0:
                    continue
                if a[1] == self.simg.mod_id and b[1] == self.timg.mod_id:
                    if a[2] and a[2] == b[2]:
                        self.vote_sec(a[2], a[3], b[3], 3 if a[0] == 10 else 1)
                elif a[1] == 0 and b[1] == 0 and main is not None:
                    main.vote(a[3], b[3], 3 if a[0] == 10 else 1)

    def vote_sec(self, sec, sa, ta, weight=1):
        s = self.sym_at(sec, sa)
        if s is None or s.type == "function" and sa != s.addr:
            return
        self.votes[id(s)][ta - (sa - s.addr)] += weight

    def collect_dol_data_refs(self):
        lo = min(v[0] for v in self.simg.sections.values())
        hi = max(v[1] for v in self.simg.sections.values())
        for sec in (".ctors", ".dtors", ".rodata", ".data", ".sdata", ".sdata2"):
            for s in self.sby_sec.get(sec, []):
                if id(s) not in self.map or s.size < 4:
                    continue
                ta = self.map[id(s)]
                a = self.simg.bytes(sec, s.addr, s.size)
                b = self.timg.bytes(sec, ta, s.size)
                if a is None or b is None or len(a) != len(b):
                    continue
                n = (len(a) - (s.addr & 3)) // 4
                base = (4 - (s.addr & 3)) & 3
                same = total = 0
                ptrs = []
                for k in range(n):
                    o = base + 4 * k
                    if o + 4 > len(a):
                        break
                    x = struct.unpack_from(">I", a, o)[0]
                    y = struct.unpack_from(">I", b, o)[0]
                    if lo <= x < hi and 0x80000000 <= y < 0x81800000:
                        ptrs.append((x, y))
                    else:
                        total += 1
                        same += x == y
                if total and same < 0.9 * total:
                    continue
                for x, y in ptrs:
                    self.vote(x, y)

    def resolve_votes(self):
        changed = 0
        for s in self.ssyms:
            v = self.votes.get(id(s))
            if not v:
                continue
            ta, n = v.most_common(1)[0]
            tot = sum(v.values())
            if (id(s), ta) in self.dropped:
                continue
            if n < 0.6 * tot:
                continue
            if id(s) in self.map:
                if self.map[id(s)] == ta or s.type != "function" or n < 3:
                    continue
                # Calls and pointers outvote the code: twin functions whose struct offsets changed places
                # (one version's A is byte-identical to the other's B) pair crosswise on code alone
                if self.how[id(s)].startswith("code-similar") or n >= 0.8 * tot:
                    for x in self.sby_sec[s.sec]:
                        if x is not s and self.map.get(id(x)) == ta and x.type == "function":
                            self.map.pop(id(x))
                            self.size.pop(id(x), None)
                            self.dropped.add((id(x), ta))
                    self._set(s, ta, f"refs {n}/{tot}")
                    self.size.pop(id(s), None)
                    changed += 1
                continue
            if s.type != "function" and n < 3 and not self._bytes_agree(s.sec, s, ta, self.sec_at(s.sec, ta)):
                continue  # one or two references to data whose bytes differ there: wait for more evidence
            self._set(s, ta, f"refs {n}/{tot}")
            changed += 1
        return changed

    def prune(self):
        """Drop placements that break source order within a section."""
        dropped = 0
        for sec, syms in self.sby_sec.items():
            groups = defaultdict(list)
            for i, s in enumerate(syms):
                if id(s) in self.map:
                    groups[self.tsec(s)].append((self.map[id(s)], i, s))
            for lst in groups.values():
                lst.sort(key=lambda x: (x[0], x[1]))
                kept = {id(x[2]) for x in longest_in_order(lst)}
                for t, i, s in lst:
                    if id(s) not in kept:
                        self.map.pop(id(s))
                        self.size.pop(id(s), None)
                        self.dropped.add((id(s), t))
                        dropped += 1
        return dropped

    # -- neighbours -------------------------------------------------------------------------------------------
    def interpolate(self):
        """Runs of unplaced symbols between two placed ones take the left or the right neighbour's shift (the
        size change lies somewhere in the run). The split point must leave every symbol's bytes in agreement;
        among several, the one that puts most symbols on dtk's own symbol starts wins."""
        changed = 0
        for sec, syms in self.sby_sec.items():
            if sec not in self.timg.sections:
                continue
            syms = [s for s in syms if not self.moved(s)]
            ts, te, _ = self.timg.sections[sec]
            auto_starts = {x.addr for x in self.tby_sec.get(sec, [])}
            i = 0
            n = len(syms)
            while i < n:
                if id(syms[i]) in self.map:
                    i += 1
                    continue
                r0 = i
                while i < n and id(syms[i]) not in self.map:
                    i += 1
                r1 = i
                run = syms[r0:r1]
                P = syms[r0 - 1] if r0 > 0 else None
                N = syms[r1] if r1 < n else None
                dP = self.map[id(P)] - P.addr if P else None
                dN = self.map[id(N)] - N.addr if N else None
                lo = self.map[id(P)] if P else ts
                hi = self.map[id(N)] if N else te

                def fits(s, d):
                    if d is None:
                        return False
                    t = s.addr + d
                    if not (lo <= t <= hi and ts <= t < te) or (id(s), t) in self.dropped:
                        return False
                    if s.addr % 4 == 0 and s.size >= 4 and t % 4:
                        return False
                    return self._bytes_agree(sec, s, t)

                okP = [fits(s, dP) for s in run]
                okN = [fits(s, dN) for s in run] if dN != dP else okP
                L = len(run)
                if dP == dN or dP is None or dN is None:
                    # grow inwards from each placed end while the bytes agree; a disagreement may be where the
                    # shift changes, so nothing past it is placed from that side
                    placed = set()
                    if dP is not None:
                        for j in range(L):
                            if not okP[j]:
                                break
                            placed.add(j)
                    if dN is not None:
                        for j in range(L - 1, -1, -1):
                            if not okN[j]:
                                break
                            placed.add(j)
                    for j in sorted(placed):
                        self._set(run[j], run[j].addr + (dP if dP is not None else dN), "neighbours")
                        changed += 1
                    continue
                # prefix with dP, suffix with dN
                prefP = [True] * (L + 1)
                for k in range(1, L + 1):
                    prefP[k] = prefP[k - 1] and okP[k - 1]
                sufN = [True] * (L + 1)
                for k in range(L - 1, -1, -1):
                    sufN[k] = sufN[k + 1] and okN[k]
                valid = [k for k in range(L + 1) if prefP[k] and sufN[k]]
                if not valid:
                    # place the agreeing ends, leave the middle
                    kp = max(k for k in range(L + 1) if prefP[k])
                    kn = min(k for k in range(L + 1) if sufN[k])
                    if kn < kp:
                        continue
                    picks = [(s, dP) for s in run[:kp]] + [(s, dN) for s in run[kn:]]
                else:
                    def score(k):
                        return sum((x.addr + (dP if j < k else dN)) in auto_starts for j, x in enumerate(run))
                    best = max(score(k) for k in valid)
                    top = [k for k in valid if score(k) == best]
                    k0, k1 = min(top), max(top)
                    picks = [(s, dP) for s in run[:k0]] + [(s, dN) for s in run[k1:]]
                for s, d in picks:
                    self._set(s, s.addr + d, "neighbours")
                    changed += 1
        return changed

    def fill_gaps(self):
        """Unplaced symbols between two placed ones whose contents changed: when dtk found exactly as many
        symbol starts in the target gap as there are sized source symbols, they pair up in order."""
        changed = 0
        for sec, syms in self.sby_sec.items():
            if sec not in self.timg.sections:
                continue
            tad = sorted({x.addr for x in self.tby_sec.get(sec, [])})
            syms = [s for s in syms if not self.moved(s)]
            n = len(syms)
            i = 0
            while i < n:
                if id(syms[i]) in self.map:
                    i += 1
                    continue
                r0 = i
                while i < n and id(syms[i]) not in self.map:
                    i += 1
                if r0 == 0 or i >= n:
                    continue
                P, N = syms[r0 - 1], syms[i]
                run = syms[r0:i]
                sized = []
                for s in run:
                    if s.size and s.type != "label" and (not sized or sized[-1].addr != s.addr):
                        sized.append(s)
                if not sized:
                    continue
                tp, tn = self.map[id(P)], self.map[id(N)]
                # symbols whose contents occur exactly once in the target gap
                found = self._search_gap(sec, sized, tp, tn)
                if found:
                    for s, t in found:
                        for x in run:
                            if x.addr == s.addr and id(x) not in self.map:
                                self._set(x, t, "content")
                                changed += 1
                    continue
                first = sized[0].addr + (tp - P.addr)  # where the first one starts if P kept its size
                k0 = bisect.bisect_left(tad, min(first, tp + 1))
                k1 = bisect.bisect_left(tad, tn)
                cands = [t for t in tad[k0:k1] if t > tp]
                if len(cands) != len(sized):
                    if len(sized) == 1 and tp < first < tn and all(t == first for t in cands):
                        cands = [first]
                    else:
                        continue
                for s, t in zip(sized, cands):
                    if (id(s), t) in self.dropped or s.addr % 4 == 0 and s.size >= 4 and t % 4:
                        continue
                    for x in run:
                        if x.addr == s.addr and id(x) not in self.map:
                            self._set(x, t, "gap")
                            changed += 1
        return changed

    def _masked(self, img, sec, start, end):
        """Section bytes with pointers (main.dol) or relocated words (RELs) zeroed."""
        key = (id(img), sec)
        cache = self.__dict__.setdefault("_mcache", {})
        if key not in cache:
            s0, e0, d = img.sections[sec]
            m = bytearray(d)
            if img.relocs is not None:
                for (sc, o), r in img.relocs.items():
                    if sc == sec:
                        m[o - s0:o - s0 + 4] = b"\0\0\0\0"
            else:
                for o in range(0, len(m) - 3, 4):
                    if m[o] == 0x80 or m[o] == 0x81:
                        m[o:o + 4] = b"\0\0\0\0"
            cache[key] = (s0, bytes(m))
        s0, m = cache[key]
        return m[start - s0:end - s0]

    def _search_gap(self, sec, sized, tp, tn):
        if self.timg.sections[sec][2] is None or tn - tp > 0x20000 or len(sized) > 400:
            return []
        gap = self._masked(self.timg, sec, tp, tn)
        out = []
        for s in sized:
            if s.size < 8:
                continue
            pat = self._masked(self.simg, sec, s.addr, s.addr + s.size)
            if len(pat) != s.size or not any(pat):
                continue
            k = gap.find(pat)
            hits = []
            while k >= 0 and len(hits) < 2:
                if (tp + k) % 4 == s.addr % 4:
                    hits.append(tp + k)
                k = gap.find(pat, k + 1)
            if len(hits) == 1 and (id(s), hits[0]) not in self.dropped:
                out.append((s, hits[0]))
        # keep them in order
        lst = longest_in_order([(t, i, s) for i, (s, t) in enumerate(out)])
        return [(s, t) for t, i, s in lst]

    def _bytes_agree(self, sec, s, ta, tsec=None):
        tsec = tsec or sec
        if tsec not in self.timg.sections:
            return False
        a = self.simg.bytes(sec, s.addr, max(s.size, 4))
        if a is None:
            return True  # bss: the neighbours agree on the shift
        b = self.timg.bytes(tsec, ta, max(s.size, 4))
        if b is None or len(a) != len(b):
            return False
        if s.type == "function":
            n = len(a) // 4
            return mask_words(struct.unpack_from(f">{n}I", a)) == mask_words(struct.unpack_from(f">{n}I", b))
        if self.simg.relocs is not None:
            # REL: positions with relocations hold placeholders
            diff = 0
            for o in range(0, len(a)):
                if a[o] != b[o]:
                    diff += 1
            if diff == 0:
                return True
            rs = {o - s.addr for (sc, o) in self.simg.relocs if sc == sec and s.addr <= o < s.addr + len(a)}
            for o in range(0, len(a)):
                if a[o] != b[o] and not any(r <= o < r + 4 for r in rs):
                    return False
            return True
        for o in range(0, len(a) - 3, 4):
            x = struct.unpack_from(">I", a, o)[0]
            y = struct.unpack_from(">I", b, o)[0]
            if x != y and not (0x80000000 <= x < 0x81800000 and 0x80000000 <= y < 0x81800000):
                return False
        return a[len(a) & ~3:] == b[len(b) & ~3:]

    # -- output -----------------------------------------------------------------------------------------------
    def target_symbols(self):
        """Ported symbols plus the dtk symbols they do not cover."""
        out = []
        ported_ranges = defaultdict(list)
        sizes = {}
        by_tgt = defaultdict(list)
        for sec, syms in self.sby_sec.items():
            for i, s in enumerate(syms):
                if id(s) not in self.map:
                    continue
                by_tgt[self.tsec(s)].append((self.map[id(s)], i, s))
        conflicts = []
        jt_starts = {sec: sorted(x.addr for x in v if x.name.startswith("jumptable_"))
                     for sec, v in self.tby_sec.items()}
        for sec, lst in by_tgt.items():
            lst.sort(key=lambda x: (x[0], x[1]))
            # Two source symbols on one target address: keep both only if the source had them together
            final = []
            for t, i, s in lst:
                if final and final[-1][0] == t and final[-1][2].addr != s.addr and s.size and final[-1][2].size:
                    conflicts.append(s)
                    continue
                final.append((t, i, s))
            ts, te, tdata = self.timg.sections[sec]
            for idx, (t, i, s) in enumerate(final):
                size = self.size.get(id(s))
                if size is None and s.type == "function" and s.size:
                    size = self.fn_size(s, sec, t)
                if size is None and s.size:
                    size = s.size
                    # The next source symbol: if it is ported, the change in distance is a change in size
                    # (when this symbol filled the gap); otherwise stop at the next ported target symbol
                    srcs = self.sby_sec[s.sec]
                    nxt_src = next((x for x in srcs[i + 1:] if x.addr > s.addr and x.type != "label"), None)
                    nxt_tgt = next((x[0] for x in final[idx + 1:] if x[0] > t and x[2].type != "label"), te)
                    if (nxt_src is not None and id(nxt_src) in self.map and self.map[id(nxt_src)] > t
                            and self.tsec(nxt_src) == sec and s.sec == sec):
                        sgap = nxt_src.addr - s.addr
                        tgap = self.map[id(nxt_src)] - t
                        if tgap != sgap and s.type != "function":
                            if s.size == sgap:
                                size = tgap
                                if tgap > s.size:
                                    # grown: stop at a new dtk symbol inside the extra space
                                    tad = [x.addr for x in self.tby_sec.get(sec, [])]
                                    k = bisect.bisect_right(tad, t + s.size - 1)
                                    if k < len(tad) and tad[k] < t + tgap:
                                        size = tad[k] - t
                            elif tgap < s.size:
                                size = tgap
                    if size > nxt_tgt - t:
                        size = nxt_tgt - t
                    # dtk's jump tables are exact: never run into one
                    jts = jt_starts.get(sec, [])
                    k = bisect.bisect_right(jts, t)
                    if k < len(jts) and jts[k] < t + size:
                        size = jts[k] - t
                    if t + size > te:
                        size = te - t
                sizes[id(s)] = size
                out.append((sec, t, s.line(addr=t, size=size if s.size else None, sec=sec)))
                if s.type != "label" and size:
                    ported_ranges[sec].append((t, t + size))
        self.conflicts = conflicts
        self.out_size = sizes
        for c in conflicts:
            self.map.pop(id(c), None)
        # dtk symbols not covered
        for sec, syms in self.tby_sec.items():
            rngs = sorted(ported_ranges.get(sec, []))
            starts = [r[0] for r in rngs]
            taken = {o[1] for o in out if o[0] == sec}
            for s in syms:
                if s.addr in taken:
                    continue
                i = bisect.bisect_right(starts, s.addr) - 1
                if i >= 0 and rngs[i][0] <= s.addr < rngs[i][1]:
                    continue
                # also ranges starting earlier but longer
                j = i - 1
                inside = False
                while j >= 0 and j > i - 8:
                    if rngs[j][0] <= s.addr < rngs[j][1]:
                        inside = True
                        break
                    j -= 1
                if inside:
                    continue
                # dtk symbol overlapping the start of a ported one: shrink it
                k = bisect.bisect_right(starts, s.addr)
                size = s.size
                if k < len(rngs) and size and s.addr + size > rngs[k][0]:
                    size = rngs[k][0] - s.addr
                out.append((sec, s.addr, s.line(size=size if s.size else None), "auto"))
        order = {n: i for i, n in enumerate(self.timg.order)}
        # at one address the function comes before its labels: mwld never finishes a link whose split object has
        # a label ahead of the function it starts (dtk keeps this order)
        out.sort(key=lambda x: (order.get(x[0], 99), x[1], "type:label" in x[2] and "type:function" not in x[2]))
        return out

    @staticmethod
    def align_gap_starts(out, split_lines):
        """A dtk symbol after padding, outside every unit, starts data the source lacks. dtk splits it into an
        object of its own, which must keep the alignment the padding came from once the unit before it is
        compiled from C (the compiled object carries no trailing padding)."""
        ranges = defaultdict(list)
        for line in split_lines:
            m = re.match(r"^\t(\S+)\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
            if m:
                ranges[m.group(1)].append((int(m.group(2), 16), int(m.group(3), 16)))
        for v in ranges.values():
            v.sort()
        lines = []
        prev_end = {}
        for o in out:
            sec, addr, line = o[0], o[1], o[2]
            m = re.search(r"size:0x([0-9A-F]+)", line)
            size = int(m.group(1), 16) if m else 0
            rs = ranges.get(sec, [])
            k = bisect.bisect_right(rs, (addr, 0xFFFFFFFF)) - 1
            in_unit = k >= 0 and rs[k][0] <= addr < rs[k][1]
            if (len(o) > 3 and not in_unit and sec not in (".init", ".text")
                    and addr > prev_end.get(sec, addr) and "align:" not in line):
                a = 4
                while a < 32 and addr % (a * 2) == 0:
                    a *= 2
                if a > 4:
                    line += f" align:{a}"
            prev_end[sec] = max(prev_end.get(sec, 0), addr + size)
            lines.append(line)
        return lines

    def tmap(self, sec, addr, end=False):
        """Target address for a source address in sec, from the nearest ported symbol."""
        syms = self.sby_sec.get(sec, [])
        addrs = self.saddrs.get(sec, [])
        i = bisect.bisect_left(addrs, addr)
        # symbol exactly at addr
        def placed(x):
            return id(x) in self.map and not self.moved(x)

        if not end:
            j = i
            while j < len(syms) and syms[j].addr == addr:
                if placed(syms[j]):
                    return self.map[id(syms[j])]
                j += 1
        # nearest mapped symbol before/after
        best = None
        for j in range(i - 1, -1, -1):
            s = syms[j]
            if placed(s):
                best = (s, j)
                break
        nb = None
        for j in range(i, len(syms)):
            if placed(syms[j]):
                nb = syms[j]
                break
        if end and best is not None:
            s = best[0]
            tsz = self.size.get(id(s), s.size)
            if s.addr + s.size == addr:
                return self.map[id(s)] + tsz
            if s.addr + s.size <= addr:
                return self.map[id(s)] + tsz + (addr - s.addr - s.size)
        if nb is not None:
            return self.map[id(nb)] - (nb.addr - addr)
        if best is not None:
            s = best[0]
            return self.map[id(s)] + (addr - s.addr)
        return None


def longest_in_order(lst):
    """lst: (target addr, source index, sym) sorted by target. The longest run whose source indices also
    increase (non-decreasing), so a few wrong placements do not push out their neighbours."""
    tails, tails_i, prev = [], [], [None] * len(lst)
    for k, (t, i, s) in enumerate(lst):
        p = bisect.bisect_right(tails, i)
        if p > 0:
            prev[k] = tails_i[p - 1]
        if p == len(tails):
            tails.append(i)
            tails_i.append(k)
        else:
            tails[p] = i
            tails_i[p] = k
    out = []
    k = tails_i[-1] if tails_i else None
    while k is not None:
        out.append(lst[k])
        k = prev[k]
    return out[::-1]


def port_splits(mod, header, units):
    """Each unit's ranges from its own ported symbols (a unit with nothing ported in a section loses that range).
    Neighbouring units share boundaries."""
    # per section, units in address order
    secs = defaultdict(list)
    for ui, (name, line, ranges) in enumerate(units):
        for ri, (sec, a, b, extra) in enumerate(ranges):
            secs[sec].append((a, b, ui, ri))
    new = {}
    problems = []
    for sec, lst in secs.items():
        lst.sort()
        if sec not in mod.timg.sections:
            problems.append(f"{sec}: not in target")
            continue
        ts, te, _ = mod.timg.sections[sec]
        ss, se, _ = mod.simg.sections[sec]
        placed = [x for x in mod.sby_sec.get(sec, []) if id(x) in mod.map and not mod.moved(x)]
        paddrs = [x.addr for x in placed]

        def tend(x):
            size = mod.out_size.get(id(x))
            return mod.map[id(x)] + (x.size if size is None else size)

        # per range: (start, first placed symbol, end of the last placed symbol, end) from the unit's own symbols
        local = []
        for a, b, ui, ri in lst:
            inside = placed[bisect.bisect_left(paddrs, a):bisect.bisect_left(paddrs, b)]
            if not inside:
                local.append(None)
                continue
            first, last = inside[0], max(inside, key=tend)
            # the bytes before the first and after the last placed symbol, less those that moved section
            gone = [x for x in mod.sby_sec.get(sec, []) if a <= x.addr < b and mod.moved(x) and x.type != "label"]
            lead = first.addr - a - sum(x.size for x in gone if x.addr < first.addr)
            trail = b - last.addr - last.size - sum(x.size for x in gone if x.addr >= last.addr + last.size)
            local.append((mod.map[id(first)] - max(0, lead), mod.map[id(first)], tend(last),
                          tend(last) + max(0, trail)))
        prev = ts
        for k, (a, b, ui, ri) in enumerate(lst):
            if local[k] is None:
                lost = [x for x in mod.sby_sec.get(sec, []) if a <= x.addr < b and x.size and id(x) not in mod.map]
                if lost:
                    problems.append(f"{units[ui][0]} {sec}: nothing ported ({len(lost)} symbols lost)")
                new[(ui, ri)] = (None, None)
                continue
            lo, first_t, end_min, hi = local[k]
            t0 = ts if a == ss else lo
            if t0 < prev <= first_t:
                t0 = prev
            if k + 1 < len(lst) and lst[k + 1][0] == b and local[k + 1] is not None:
                n_lo = local[k + 1][0]
                t1 = n_lo if end_min <= n_lo else hi
            else:
                t1 = hi
                if b >= se and t1 is not None and t1 >= te - 0x20:
                    t1 = te  # the section's last unit, as in the source
                elif t1 is not None and t1 < te:
                    # code or data the source lacks follows: end where the target's next symbol starts when
                    # only padding lies between, so the gap dtk fills starts aligned
                    tad = [x.addr for x in mod.tby_sec.get(sec, [])]
                    j = bisect.bisect_left(tad, t1)
                    nxt = tad[j] if j < len(tad) else None  # (dtk's section end may be short of the DOL's)
                    d = mod.timg.sections[sec][2]
                    if nxt is not None and nxt - t1 < 0x20 and (d is None or not any(d[t1 - ts:nxt - ts])):
                        t1 = nxt
            if t1 < t0:
                problems.append(f"{units[ui][0]} {sec}: no target range (0x{t0:X}, 0x{t1:X})")
                t0 = t1 = None
            else:
                prev = max(prev, t1)
            new[(ui, ri)] = (t0, t1)
    # Symbols that moved to the small-data twin of their section (another -sdata threshold) stay with their unit:
    # its range there grows to hold them, or the unit gets a range in that section
    ranges_of = [list(r) for _, _, r in units]
    for ui, (name, line, ranges) in enumerate(units):
        grow = {}
        for sec, a, b, extra in ranges:
            syms = mod.sby_sec.get(sec, [])
            addrs = mod.saddrs.get(sec, [])
            for x in syms[bisect.bisect_left(addrs, a):bisect.bisect_left(addrs, b)]:
                if not mod.moved(x) or x.type == "label":
                    continue
                t = mod.map[id(x)]
                e = t + (mod.out_size.get(id(x)) or x.size)
                r = grow.setdefault(mod.tsec(x), [t, e])
                r[0], r[1] = min(r[0], t), max(r[1], e)
        for tsec, (t0, t1) in grow.items():
            ri = next((k for k, r in enumerate(ranges_of[ui]) if r[0] == tsec), None)
            if ri is None:
                ranges_of[ui].append((tsec, None, None, []))
                new[(ui, len(ranges_of[ui]) - 1)] = (t0, t1)
                continue
            o0, o1 = new.get((ui, ri), (None, None))
            if o0 is None or o0 == o1:
                new[(ui, ri)] = (t0, t1)
            else:
                new[(ui, ri)] = (min(o0, t0), max(o1, t1))
    # A range stretched to its neighbour (shared boundaries) must not take in another unit's symbols, such as the
    # ones that moved section: clip it at the nearest symbol of another unit on either side
    hard = defaultdict(list)  # target section -> [(start, end, unit, moved section)]
    for ui, (name, line, ranges) in enumerate(units):
        for sec, a, b, extra in ranges:
            syms = mod.sby_sec.get(sec, [])
            addrs = mod.saddrs.get(sec, [])
            for x in syms[bisect.bisect_left(addrs, a):bisect.bisect_left(addrs, b)]:
                if id(x) in mod.map and x.type != "label" and x.size:
                    t = mod.map[id(x)]
                    hard[mod.tsec(x)].append((t, t + (mod.out_size.get(id(x)) or x.size), ui, mod.moved(x)))
    for v in hard.values():
        v.sort()
    for (ui, ri), (t0, t1) in list(new.items()):
        if t0 is None:
            continue
        spans = hard.get(ranges_of[ui][ri][0], [])
        own = [(a, b) for a, b, u, _ in spans if u == ui and t0 <= a < t1]
        if not own:
            continue
        own_lo, own_hi = min(a for a, _ in own), max(b for _, b in own)
        k = bisect.bisect_left(spans, (own_hi,))
        while k < len(spans) and (spans[k][2] == ui or spans[k][0] < own_hi):
            k += 1
        if k < len(spans) and spans[k][0] < t1:
            t1 = spans[k][0]
        k = bisect.bisect_left(spans, (own_lo,)) - 1
        while k >= 0 and (spans[k][2] == ui or spans[k][1] > own_lo):
            k -= 1
        if k >= 0 and spans[k][1] > t0:
            t0 = spans[k][1]
        new[(ui, ri)] = (t0, t1)
    # enforce order. Where two ranges still overlap and one side has only symbols that moved section in the
    # overlap, that side gives way: those symbols then lie in the other unit's range (code that moved between
    # units, or a wrong guess of which unit they belong to)
    by_sec = defaultdict(list)
    for (ui, ri), (t0, t1) in new.items():
        if t0 is not None and t1 > t0:
            by_sec[ranges_of[ui][ri][0]].append([t0, t1, ui, ri])
    for sec, lst in by_sec.items():
        lst.sort()
        spans = hard.get(sec, [])

        def fixed(u, lo, hi):
            k = bisect.bisect_left(spans, (lo - 0x10000,))
            while k < len(spans) and spans[k][0] < hi:
                a, b, v, mv = spans[k]
                if v == u and not mv and b > lo:
                    return True
                k += 1
            return False

        start = mod.timg.sections[sec][0]
        prev = None
        for r in lst:
            if r[0] < start:
                problems.append(f"{units[r[2]][0]} {sec}: starts before the section (0x{r[0]:X})")
            if prev is not None and r[0] < prev[1]:
                if prev[1] <= r[1] and not fixed(prev[2], r[0], prev[1]):
                    prev[1] = r[0]
                elif not fixed(r[2], r[0], prev[1]):
                    r[0] = min(prev[1], r[1])
                else:
                    problems.append(f"{units[r[2]][0]} {sec}: overlaps {units[prev[2]][0]} (0x{r[0]:X} < 0x{prev[1]:X})")
            if prev is None or r[1] > prev[1]:
                prev = r
        # a range may not start or end inside a target symbol: take the whole symbol where the neighbour leaves
        # room, otherwise leave it out
        syms = sorted(mod.out_spans.get(sec, []))
        sstarts = [x[0] for x in syms]
        for k, r in enumerate(lst):
            for end in (False, True):
                t = r[1] if end else r[0]
                j = bisect.bisect_left(sstarts, t) - 1
                while j >= 0 and not syms[j][0] < t < syms[j][1] and syms[j][0] > t - 0x10000:
                    j -= 1
                if j < 0 or not syms[j][0] < t < syms[j][1]:
                    continue
                a, e = syms[j]
                if end:
                    nxt = min((x[0] for x in lst[k + 1:] if x[1] > x[0]), default=None)
                    r[1] = e if nxt is None or nxt >= e else max(a, r[0])
                else:
                    prv = max((x[1] for x in lst[:k] if x[1] > x[0]), default=None)
                    r[0] = a if prv is None or prv <= a else min(e, r[1])
            if r[0] % 4 and (r[0] + 3) & ~3 < r[1]:
                r[0] = (r[0] + 3) & ~3  # a unit starts word-aligned (what precedes is the last one's padding)
        for k, r in enumerate(lst):
            if r[1] % 4:
                # and ends word-aligned: the bytes up to the next word are its padding
                up = min((r[1] + 3) & ~3, mod.timg.sections[sec][1])
                nxt = min((x[0] for x in lst[k + 1:] if x[1] > x[0]), default=None)
                if nxt is None and syms and syms[-1][1] <= r[1]:
                    # the section's last unit: dtk ends the section with its last symbol, so no padding follows
                    up = r[1]
                if nxt is None or nxt >= up:
                    r[1] = up
            # padding before the next unit belongs to this one
            nxt = min((x[0] for x in lst[k + 1:] if x[1] > x[0]), default=None)
            ts_, _, d = mod.timg.sections[sec]
            if nxt is not None and 0 < nxt - r[1] < 0x20 and (d is None or not any(d[r[1] - ts_:nxt - ts_])):
                r[1] = nxt
        for t0, t1, ui, ri in lst:
            new[(ui, ri)] = (t0, t1)
    if mod.timg.relocs is None:
        reassign_by_refs(mod, ranges_of, new, hard)
    order = {n: i for i, n in enumerate(mod.timg.order)}
    lines = list(header) + [""]
    for ui, (name, line, ranges) in enumerate(units):
        body = []
        for ri, (sec, a, b, extra) in sorted(enumerate(ranges_of[ui]), key=lambda x: order.get(x[1][0], 99)):
            t0, t1 = new.get((ui, ri), (None, None))
            if t0 is None or t1 == t0:
                continue
            fmt = f"\t{sec:<11} start:0x{t0:08X} end:0x{t1:08X}"
            if extra:
                fmt += " " + " ".join(extra)
            body.append(fmt)
        lines.append(line)
        lines += body
        lines.append("")
    return lines, problems


def reassign_by_refs(mod, ranges_of, new, hard):
    """Variables the target has in .data/.bss/.rodata but the source in small data (another -sdata threshold),
    when nothing ported names them, lie at a unit boundary of the target, in the wrong unit as often as not. A run
    of such unported symbols at the end of one unit (or the start of the next) that only the other unit's code or
    data refers to goes to that unit. A run at the end of a unit that only a unit between the two refers to, one
    with no range in that section, becomes that unit's range. (main.dol only: the references are read from the
    target's code and pointers.)"""
    timg = mod.timg
    refs = defaultdict(set)
    for (ui, ri), (t0, t1) in new.items():
        if t0 is None or t1 <= t0:
            continue
        sec = ranges_of[ui][ri][0]
        if sec not in timg.sections or timg.sections[sec][2] is None:
            continue
        if sec in (".init", ".text"):
            for _, a in stream_refs(code_words(timg, sec, t0, t1 - t0), t0, timg.sda):
                refs[a].add(ui)
        else:
            d = timg.bytes(sec, t0 & ~3, t1 - (t0 & ~3))
            for k in range(0, len(d) - 3, 4):
                w = struct.unpack_from(">I", d, k)[0]
                if timg.sec_of(w) is not None:
                    refs[w].add(ui)
    rng = defaultdict(list)
    for (ui, ri), (t0, t1) in new.items():
        if t0 is not None and t1 > t0:
            rng[ranges_of[ui][ri][0]].append([t0, t1, ui, ri])
    for sec in (".rodata", ".data", ".bss", ".sdata", ".sbss", ".sdata2", ".sbss2"):
        lst = sorted(rng.get(sec, []))
        spans = sorted(mod.out_spans.get(sec, []))
        starts = [a for a, _ in spans]
        ported = {a for a, _, _, _ in hard.get(sec, [])}
        has = {r[2] for r in lst}
        for A, B in zip(lst, lst[1:]):
            if A[1] != B[0]:
                continue
            # back from A's end, run by run: B's, then those of the units between (each before the last)
            moved, limit = False, B[2]
            while True:
                k = bisect.bisect_left(starts, A[1]) - 1
                run = who = None
                while k >= 0 and spans[k][0] >= A[0]:
                    a = spans[k][0]
                    r = refs.get(a)
                    if a in ported or not r or len(r) != 1:
                        break
                    u = next(iter(r))
                    if u == A[2] or (who is not None and u != who):
                        break
                    if not (u == B[2] == limit or (A[2] < u < limit and u not in has)):
                        break
                    who, run = u, a
                    k -= 1
                if run is None or run % 4 or run <= A[0]:
                    break
                if who == B[2]:
                    B[0] = run
                else:
                    ranges_of[who].append((sec, None, None, []))
                    new[(who, len(ranges_of[who]) - 1)] = (run, A[1])
                    has.add(who)
                A[1], limit, moved = run, who, True
            if moved:
                continue
            # forward from B's start
            k = bisect.bisect_left(starts, B[0])
            run = None
            while k < len(spans) and spans[k][0] < B[1]:
                a = spans[k][0]
                if a in ported or refs.get(a) != {A[2]}:
                    break
                run = spans[k][1]
                k += 1
            if run is not None:
                nxt = starts[k] if k < len(spans) and spans[k][0] < B[1] else B[1]
                if nxt % 4 == 0 and nxt < B[1]:
                    A[1] = B[0] = nxt
        for t0, t1, ui, ri in lst:
            new[(ui, ri)] = (t0, t1)


def port_module(name, src_cfg, src_orig, tgt_auto, tgt_orig, out_dir, main=None, src_main_same=True):
    is_main = name == "main"
    sub = "" if is_main else name
    ssyms = read_symbols(os.path.join(src_cfg, sub, "symbols.txt"))
    tsyms = read_symbols(os.path.join(tgt_auto, sub, "symbols.txt"))
    if is_main:
        simg = load_dol(os.path.join(src_orig, "sys", "main.dol"))
        timg = load_dol(os.path.join(tgt_orig, "sys", "main.dol"))
    else:
        simg = load_rel(os.path.join(src_orig, "files", "rel", name + ".rel"))
        timg = load_rel(os.path.join(tgt_orig, "files", "rel", name + ".rel"))
    mod = Module(name, ssyms, simg, tsyms, timg)
    mod.auto_splits = os.path.join(tgt_auto, sub, "splits.txt")
    mod.match_code()
    for _ in range(8):
        if is_main:
            mod.collect_dol_code_refs(simg.sda, timg.sda)
            mod.collect_dol_data_refs()
        else:
            mod.collect_rel_refs(main if src_main_same else None)
        c = mod.resolve_votes()
        mod.votes.clear()
        mod.prune()
        c += mod.interpolate()
        mod.prune()
        if not c:
            c += mod.fill_gaps()
            mod.prune()
        if not c:
            break
    return mod


def merge_section_header(src, auto):
    """Section alignments from dtk's analysis of the target (the largest its start addresses allow, which
    always reproduces them); the rest of the header from the source."""
    def aligns(lines):
        out = {}
        for line in lines:
            m = re.match(r"^\s+(\S+)\s.*align:(\d+)", line)
            if m:
                out[m.group(1)] = int(m.group(2))
        return out
    ta = aligns(auto)
    out = []
    for line in src:
        m = re.match(r"^(\s+(\S+)\s.*align:)(\d+)(.*)$", line)
        if m and m.group(2) in ta:
            a, b = int(m.group(3)), ta[m.group(2)]
            if b != a:
                line = f"{m.group(1)}{b}{m.group(4)}"
        out.append(line)
    return out


def write_module(mod, src_cfg, out_dir, report):
    sub = "" if mod.name == "main" else mod.name
    os.makedirs(os.path.join(out_dir, sub), exist_ok=True)
    out = mod.target_symbols()
    mod.out_spans = defaultdict(list)
    for o in out:
        m = re.search(r"size:0x([0-9A-F]+)", o[2])
        if m and int(m.group(1), 16):
            mod.out_spans[o[0]].append((o[1], o[1] + int(m.group(1), 16)))
    header, units = read_splits(os.path.join(src_cfg, sub, "splits.txt"))
    auto_header, _ = read_splits(mod.auto_splits)
    header = merge_section_header(header, auto_header)
    slines, problems = port_splits(mod, header, units)
    lines = Module.align_gap_starts(out, slines)
    # A source symbol named after its address (fn_/lbl_<addr>) can land on another address that dtk names the same
    # way: it takes the name of its own target address
    names = Counter(line.split(" ", 1)[0] for line in lines)
    for k, line in enumerate(lines):
        m = re.match(r"^(fn|lbl)_([0-9A-F]{8}) = (\S+):0x([0-9A-F]{8});", line)
        if m and names[line.split(" ", 1)[0]] > 1 and m.group(2) != m.group(4):
            lines[k] = f"{m.group(1)}_{m.group(4)}" + line[len(m.group(1)) + 9:]
    with open(os.path.join(out_dir, sub, "symbols.txt"), "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines) + "\n")
    with open(os.path.join(out_dir, sub, "splits.txt"), "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(slines).rstrip("\n") + "\n")
    hows = Counter(mod.how[id(s)].split()[0] for s in mod.ssyms if id(s) in mod.map)
    missing = [s for s in mod.ssyms if id(s) not in mod.map]
    fn_total = sum(1 for s in mod.ssyms if s.type == "function")
    fn_mapped = sum(1 for s in mod.ssyms if s.type == "function" and id(s) in mod.map)
    report.write(f"== {mod.name}: {len(mod.ssyms) - len(missing)}/{len(mod.ssyms)} symbols ported "
                 f"({fn_mapped}/{fn_total} functions); {dict(hows)}\n")
    moved = Counter(f"{s.sec}->{mod.tsec(s)}" for s in mod.ssyms if mod.moved(s))
    if moved:
        report.write(f"  moved section: {dict(moved)}\n")
    for p in problems:
        report.write(f"  split: {p}\n")
    for s in missing:
        report.write(f"  unported: {s.name} {s.sec}:0x{s.addr:08X} {s.type} size:0x{s.size:X}\n")
    for s in mod.ssyms:
        h = mod.how.get(id(s), "")
        if h.startswith("code-similar") and id(s) in mod.map:
            report.write(f"  similar: {s.name} -> 0x{mod.map[id(s)]:08X} ({h})\n")
    # Ported data whose contents differ (pointers / relocated words aside): real version differences, or a
    # wrong placement
    changed = 0
    for s in mod.ssyms:
        if id(s) not in mod.map or s.type == "function" or not s.size:
            continue
        if mod.simg.sections.get(s.sec, (0, 0, None))[2] is None:
            continue
        ta = mod.map[id(s)]
        tsec = mod.tsec(s)
        tsize = mod.out_size.get(id(s), s.size)
        if tsize == s.size and mod._bytes_agree(s.sec, s, ta, tsec):
            continue
        changed += 1
        a = mod.simg.bytes(s.sec, s.addr, min(s.size, 16)).hex()
        b = mod.timg.bytes(tsec, ta, min(tsize, 16)).hex()
        report.write(f"  changed: {s.name} {s.sec}:0x{s.addr:08X} -> 0x{ta:08X} size 0x{s.size:X} -> 0x{tsize:X} "
                     f"[{a}] [{b}]\n")
    report.write(f"  ({changed} ported data symbols differ in content)\n")
    return len(missing), problems


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--src-config", required=True)
    ap.add_argument("--src-orig", required=True)
    ap.add_argument("--tgt-auto", required=True)
    ap.add_argument("--tgt-orig", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--module", action="append", default=[])
    ap.add_argument("--report", default=None)
    ap.add_argument("--addr-map", default=None, help="write 'module section src_addr tgt_addr name' per ported symbol")
    args = ap.parse_args()
    mods = args.module or ["main"]
    report = open(args.report, "w", encoding="utf-8") if args.report else sys.stdout
    main_mod = None
    rel_specs = []
    for m in mods:
        if "=" in m:
            n, src = m.split("=", 1)
            cfg, orig = src.split(",")
            rel_specs.append((n, cfg, orig, False))
        else:
            rel_specs.append((m, args.src_config, args.src_orig, True))
    if any(n == "main" for n, *_ in rel_specs):
        main_mod = port_module("main", args.src_config, args.src_orig, args.tgt_auto, args.tgt_orig, args.out)
    rels = []
    for n, cfg, orig, same in rel_specs:
        if n == "main":
            continue
        rels.append((port_module(n, cfg, orig, args.tgt_auto, args.tgt_orig, args.out, main_mod, same), cfg))
    if main_mod is not None:
        # REL references to main.dol voted on main: settle them
        main_mod.resolve_votes()
        main_mod.prune()
        main_mod.interpolate()
        main_mod.prune()
        write_module(main_mod, args.src_config, args.out, report)
    for mod, cfg in rels:
        write_module(mod, cfg, args.out, report)
    if args.addr_map:
        with open(args.addr_map, "w", encoding="utf-8", newline="\n") as f:
            for mod in ([main_mod] if main_mod else []) + [m for m, _ in rels]:
                for x in mod.ssyms:
                    if id(x) in mod.map:
                        f.write(f"{mod.name} {x.sec} 0x{x.addr:08X} 0x{mod.map[id(x)]:08X} "
                                f"0x{x.size:X} 0x{mod.out_size.get(id(x)) or x.size:X} {x.name}\n")


if __name__ == "__main__":
    main()
