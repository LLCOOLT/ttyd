#!/usr/bin/env python3
"""Script-aware source formatter for the TTYD C tree.

clang-format (with the repository's .clang-format) formats C code. Regions it
handles badly are protected and normalised here instead:
  * EVT scripts (EVT_BEGIN ... EVT_END): one command per line, indented four
    spaces per IF/ELSE/SWITCH/LOOP/INLINE/SIBLING nesting level (a line holding
    two commands, such as `END_IF CALL(...)` or `RETURN EVT_END()`, is split);
  * multi-line top-level initialiser tables: kept as laid out, only tabs and
    trailing whitespace are normalised;
  * lines whose text or line number ends up in the binary (assert-style
    macros, __LINE__): kept verbatim, and the file is left alone if formatting
    would move them.

usage: python tools/format_check.py [--write] [--verbose] [paths...]
  Without --write, lists the files that would change and exits 1 if there are any.
  With --write, reformats them. Paths default to include/, src/ and rels/.
  --self-test runs the built-in regression cases (script regions, one command per line).
  clang-format comes from $CLANG_FORMAT, the default LLVM install or PATH; without it the
  check is skipped with a message, as it is with a clang-format major version other than
  the one the tree is formatted with (CLANG_FORMAT_MAJOR) unless --any-version is given.
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CLANG_FORMAT_CANDIDATES = [
    os.environ.get("CLANG_FORMAT", ""),
    "C:/Program Files/LLVM/bin/clang-format.exe",
    "clang-format",
]

# Directories never formatted: vendored code and sources whose text is in the binary.
EXCLUDED_DIRS = (
    "libs/",              # vendored SDK/runtime libraries keep their own style
    "rels/tst/src/glu/",  # vendored GLU: assert() text and __LINE__ are in the binary
    "rels/tst/include/glu/",
    "build/",
    "orig/",
    "tools/",
)
SOURCE_DIRS = ("include", "src", "rels")

# Lines whose text or line number is compiled into the game (assert macros stringify the condition).
LINE_SENSITIVE = re.compile(r"(?<![\w])(assert|ASSERT\w*|TST_ASSERTMSG)\s*\(|\b__LINE__\b")

NOTES = []
PLACEHOLDER = "int format_check_region_%d;"
PLACEHOLDER_RE = re.compile(r"^int format_check_region_(\d+);$")
OFF = "/* clang-format off */"
ON = "/* clang-format on */"

SCRIPT_BEGIN = re.compile(r"^\s*(static\s+)?(const\s+)?EVT_BEGIN\s*\(")
SCRIPT_END = re.compile(r"^\s*EVT_END(_PAD4?)?\s*\(\s*\)")
SCRIPT_END_ANY = re.compile(r"\bEVT_END(_PAD4?)?\s*\(\s*\)")
# a script command: an upper-case macro name, with or without an argument list
COMMAND_START = re.compile(r"[A-Z][A-Z0-9_]*\b")
OPENERS = re.compile(r"^(IF_\w+|LOOP|SWITCH|SWITCH_RAW|BEGIN_INLINE_EVENT\w*|BEGIN_SIBLING_EVENT\w*)\b")
CLOSERS = re.compile(r"^(END_IF|END_LOOP|END_SWITCH|END_INLINE_EVENT|END_SIBLING_EVENT)\b")
MIDDLES = re.compile(r"^(ELSE)\b")


# The tree is formatted with this clang-format major version; others lay out some code differently.
CLANG_FORMAT_MAJOR = 23


def find_clang_format():
    """Return (path, major version) of the first clang-format found, or (None, None)."""
    for c in CLANG_FORMAT_CANDIDATES:
        if not c:
            continue
        try:
            r = subprocess.run([c, "--version"], capture_output=True, text=True, check=True)
        except (OSError, subprocess.CalledProcessError):
            continue
        m = re.search(r"version (\d+)", r.stdout)
        return c, int(m.group(1)) if m else None
    return None, None


def strip_code(line, in_comment):
    """Return (code text without strings/comments, still-in-block-comment)."""
    out = []
    i = 0
    n = len(line)
    while i < n:
        if in_comment:
            j = line.find("*/", i)
            if j < 0:
                return "".join(out), True
            i = j + 2
            in_comment = False
            continue
        c = line[i]
        if c == "/" and i + 1 < n and line[i + 1] == "/":
            break
        if c == "/" and i + 1 < n and line[i + 1] == "*":
            in_comment = True
            i += 2
            continue
        if c in "\"'":
            q = c
            i += 1
            while i < n and line[i] != q:
                i += 2 if line[i] == "\\" else 1
            i += 1
            out.append(q + q)
            continue
        out.append(c)
        i += 1
    return "".join(out), in_comment


def find_regions(lines):
    """Return [(start, end, kind)] of protected line ranges (inclusive)."""
    regions = []
    depth = 0          # brace depth outside scripts
    in_comment = False
    i = 0
    n = len(lines)
    table_start = None
    stmt_start = None  # first line of the current top-level statement
    pp_cont = False    # inside a multi-line preprocessor directive
    pp_depth = []      # per open #if: [depth at #if, depth at the end of its first branch]
    while i < n:
        line = lines[i]
        if pp_cont or (not in_comment and line.lstrip().startswith("#")):
            if not pp_cont:
                # follow braces through one branch of each #if: the other branches repeat them
                m = re.match(r"\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b", line)
                d = m.group(1) if m else None
                if d in ("if", "ifdef", "ifndef"):
                    pp_depth.append([depth, None])
                elif d in ("elif", "else") and pp_depth:
                    if pp_depth[-1][1] is None:
                        pp_depth[-1][1] = depth
                    depth = pp_depth[-1][0]
                elif d == "endif" and pp_depth:
                    start, first = pp_depth.pop()
                    if first is not None:
                        depth = first
            pp_cont = line.rstrip().endswith("\\")
            i += 1
            continue
        code, in_comment_after = strip_code(line, in_comment)
        if depth == 0 and not in_comment and SCRIPT_BEGIN.match(line):
            j = i
            # EVT_END may share a line with the last command (`RETURN EVT_END()`): search, not match
            while j < n and not SCRIPT_END_ANY.search(strip_code(lines[j], False)[0]) and lines[j].strip() != "};":
                j += 1
            if j >= n:
                raise ValueError("EVT_BEGIN without EVT_END at line %d" % (i + 1))
            regions.append((i, j, "script"))
            i = j + 1
            stmt_start = None
            continue
        stripped = code.strip()
        if depth == 0 and stripped and not stripped.startswith("#"):
            if stmt_start is None:
                stmt_start = i
            # top-level initialiser: '=' before the first '{' of the statement
            if "{" in code and table_start is None:
                pre = "".join(strip_code(l, False)[0] for l in lines[stmt_start:i]) + code[: code.index("{")]
                if "=" in pre:
                    table_start = stmt_start
        if not stripped.startswith("#"):
            depth += code.count("{") - code.count("}")
        if depth < 0:
            depth = 0
        if depth == 0 and stripped and not stripped.startswith("#"):
            if table_start is not None:
                if i > table_start:
                    regions.append((table_start, i, "table"))
                table_start = None
            if stripped.endswith(";") or stripped.endswith("}"):
                stmt_start = None
        in_comment = in_comment_after
        i += 1
    return regions


def normalise_ws(line):
    m = re.match(r"^[ \t]*", line)
    lead = m.group(0).replace("\t", "    ")
    return (lead + line[m.end():]).rstrip()


VERSIONS = {"VERSION_DEMO_JP": 0, "VERSION_DEMO_US": 1, "VERSION_JP": 2, "VERSION_US": 3, "VERSION_EU": 4}


def eval_condition(cond, version):
    """Evaluate an #if condition on VERSION for one version; None if it is not a VERSION test."""
    cond = re.sub(r"//.*|/\*.*?\*/", "", cond).strip()
    expr = re.sub(r"\bVERSION_\w+\b", lambda m: str(VERSIONS.get(m.group(0), "X")), cond)
    expr = re.sub(r"\bVERSION\b", str(version), expr)
    expr = expr.replace("&&", " and ").replace("||", " or ")
    expr = re.sub(r"!(?!=)", " not ", expr)
    if not re.fullmatch(r"[\d\s()<>=!andotr]*", expr):
        return None
    try:
        return bool(eval(expr, {"__builtins__": {}}))
    except Exception:
        return None


def split_commands(line):
    """Split a script line holding several commands (`END_IF CALL(f, 1)`, `RETURN EVT_END()`)
    into one line per command. A trailing // comment stays with the last command; lines that
    start or end inside an argument list are returned unchanged."""
    lead = line[: len(line) - len(line.lstrip())]
    code, _ = strip_code(line, False)
    if line.lstrip().startswith(("#", "/")) or code.count("(") != code.count(")"):
        return [line]
    cuts = []
    depth = 0
    i = 0
    n = len(line)
    prev_end = False  # a command ended just before (identifier or closing parenthesis)
    while i < n:
        c = line[i]
        if c == "/" and i + 1 < n and line[i + 1] in "/*":
            break
        if c in "\"'":
            q = c
            i += 1
            while i < n and line[i] != q:
                i += 2 if line[i] == "\\" else 1
            i += 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            prev_end = depth == 0
        elif depth == 0 and c.isspace():
            pass
        elif depth == 0 and COMMAND_START.match(line, i):
            m = COMMAND_START.match(line, i)
            if prev_end and line[i - 1].isspace():
                cuts.append(i)
            i = m.end()
            prev_end = True
            continue
        else:
            prev_end = False
        i += 1
    if not cuts:
        return [line]
    parts = []
    start = 0
    for c in cuts:
        parts.append(line[start:c].rstrip())
        start = c
    parts.append(line[start:])
    return [parts[0]] + [lead + p.strip() for p in parts[1:]]


def normalise_script(block):
    """Re-indent one EVT_BEGIN..EVT_END block; None if its nesting cannot be followed.

    Nesting is followed separately for each game version (VERSION #if blocks may open
    or close a level in one version only); a line is indented for the deepest version
    that compiles it. Lines that hold more than one command are split first.
    """
    split = []
    paren = 0
    for k, raw in enumerate(block):
        parts = split_commands(raw) if k > 0 and paren == 0 else [raw]
        split.extend(parts)
        code, _ = strip_code(raw, False)
        if not raw.lstrip().startswith("#"):
            paren = max(0, paren + code.count("(") - code.count(")"))
    block = split
    out = []
    versions = sorted(VERSIONS.values())
    depth = {v: 1 for v in versions}
    pp_stack = []  # per #if: (visible set before it, any branch taken per version)
    visible = {v: True for v in versions}
    cont_shift = None
    paren = 0
    for k, raw in enumerate(block):
        line = normalise_ws(raw)
        s = line.strip()
        if k == 0:
            out.append(line)
            continue
        if k == len(block) - 1:
            out.append(s)
            continue
        if not s:
            out.append("")
            continue
        if paren > 0:  # continuation of a call split over lines: keep its offset
            old = len(line) - len(line.lstrip())
            out.append(" " * max(0, old + cont_shift) + s)
            paren += s.count("(") - s.count(")")
            continue
        if s.startswith("#"):
            m = re.match(r"#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)", s)
            if m:
                d, cond = m.group(1), m.group(2)
                if d in ("ifdef", "ifndef"):
                    return None
                if d == "if":
                    res = {v: eval_condition(cond, v) for v in versions}
                    if None in res.values():
                        return None
                    pp_stack.append((dict(visible), dict(res)))
                    visible = {v: visible[v] and res[v] for v in versions}
                elif d == "elif":
                    if not pp_stack:
                        return None
                    outer, taken = pp_stack[-1]
                    res = {v: eval_condition(cond, v) for v in versions}
                    if None in res.values():
                        return None
                    visible = {v: outer[v] and not taken[v] and res[v] for v in versions}
                    pp_stack[-1] = (outer, {v: taken[v] or res[v] for v in versions})
                elif d == "else":
                    if not pp_stack:
                        return None
                    outer, taken = pp_stack[-1]
                    visible = {v: outer[v] and not taken[v] for v in versions}
                elif pp_stack:
                    visible = pp_stack.pop()[0]
                # an #endif whose #if sits before EVT_BEGIN closes nothing here
            out.append(s)
            continue
        live = [v for v in versions if visible[v]]
        if not live:
            out.append(line)
            continue
        if CLOSERS.match(s):
            for v in live:
                depth[v] -= 1
            ind = max(depth[v] for v in live)
        elif MIDDLES.match(s):
            ind = max(depth[v] for v in live) - 1
        else:
            ind = max(depth[v] for v in live)
        if any(depth[v] < 1 for v in live) or ind < 1:
            return None
        if OPENERS.match(s):
            for v in live:
                depth[v] += 1
        old = len(line) - len(line.lstrip())
        out.append("    " * ind + s)
        p = s.count("(") - s.count(")")
        if p > 0:
            paren = p
            cont_shift = 4 * ind - old
    return out


def run_clang_format(cf, text, path):
    style = "--style=file:" + os.path.join(ROOT, ".clang-format").replace("\\", "/")
    r = subprocess.run([cf, style, "--assume-filename=" + path], input=text.encode("utf-8"), capture_output=True)
    if r.returncode != 0:
        raise RuntimeError("clang-format failed on %s: %s" % (path, r.stderr.decode("utf-8", "replace")))
    return r.stdout.decode("utf-8")


def format_text(cf, text, path):
    """Return the formatted text (newlines as \n), or None if the file must be left as is."""
    lines = text.split("\n")
    if lines and lines[-1] == "":
        lines.pop()
    regions = find_regions(lines)
    in_region = [None] * len(lines)
    for r, (a, b, _) in enumerate(regions):
        for k in range(a, b + 1):
            in_region[k] = r
    in_pp = [False] * len(lines)  # preprocessor directives, with their continuation lines
    cont = False
    for k, l in enumerate(lines):
        in_pp[k] = cont or l.lstrip().startswith("#")
        cont = in_pp[k] and l.rstrip().endswith("\\")
    sensitive = [k for k, l in enumerate(lines)
                 if in_region[k] is None and not in_pp[k] and LINE_SENSITIVE.search(l)]
    sens = set(sensitive)
    # scripts and tables become one placeholder declaration each; line-sensitive lines are fenced off
    marked = []
    k = 0
    while k < len(lines):
        r = in_region[k]
        if r is not None:
            marked.append(PLACEHOLDER % r)
            k = regions[r][1] + 1
        elif k in sens:
            marked.append(OFF)
            while k < len(lines) and k in sens:
                marked.append(lines[k])
                k += 1
            marked.append(ON)
        else:
            marked.append(lines[k])
            k += 1
    fmt = run_clang_format(cf, "\n".join(marked) + "\n", path).split("\n")
    if fmt and fmt[-1] == "":
        fmt.pop()
    result = []
    seen = 0
    for l in fmt:
        s = l.strip()
        if s in (OFF, ON):
            continue
        m = PLACEHOLDER_RE.match(s)
        if m:
            a, b, kind = regions[int(m.group(1))]
            block = lines[a : b + 1]
            new = normalise_script(block) if kind == "script" else None
            if new is None and kind == "script":
                NOTES.append("%s:%d: script nesting does not balance; only whitespace normalised" % (path, a + 1))
            if new is None:
                new = [normalise_ws(x) for x in block]
            result.extend(new)
            seen += 1
            continue
        result.append(l)
    if seen != len(regions):
        raise RuntimeError("%s: protected regions lost in clang-format output" % path)
    # line-sensitive lines must stay where they are, with the same text
    for k in sensitive:
        if k >= len(result) or result[k].strip() != lines[k].strip():
            NOTES.append("%s:%d: formatting would move a line-sensitive line; file left as is" % (path, k + 1))
            return None
        result[k] = result[k].rstrip()
    return "\n".join(result) + "\n"


def wanted(rel):
    rel = rel.replace("\\", "/")
    if not rel.endswith((".c", ".h")):
        return False
    if not rel.startswith(tuple(d + "/" for d in SOURCE_DIRS)):
        return False
    return not rel.startswith(EXCLUDED_DIRS)


def tree_files():
    r = subprocess.run(["git", "ls-files", "--", *SOURCE_DIRS], cwd=ROOT, capture_output=True, text=True, check=True)
    return [f for f in r.stdout.split("\n") if f and wanted(f)]


def process(cf, rel, write):
    path = os.path.join(ROOT, rel)
    raw = open(path, encoding="utf-8", newline="").read()
    nl = "\r\n" if "\r\n" in raw else "\n"
    text = raw.replace("\r\n", "\n")
    new = format_text(cf, text, rel)
    if new is None or new == text:
        return False
    if write:
        open(path, "w", encoding="utf-8", newline="").write(new.replace("\n", nl))
    return True


SELF_TEST_IN = """#if VERSION <= VERSION_DEMO_US
EVT_BEGIN(a)
    RETURN
EVT_END()
#else
EVT_BEGIN(a)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF CALL(f, LW(13), STRING("x y"))
    RETURN EVT_END()
#endif
"""
SELF_TEST_OUT = """#if VERSION <= VERSION_DEMO_US
EVT_BEGIN(a)
    RETURN
EVT_END()
#else
EVT_BEGIN(a)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    CALL(f, LW(13), STRING("x y"))
    RETURN
EVT_END()
#endif
"""


def self_test():
    """Regression cases that need no clang-format: script regions and command splitting."""
    lines = SELF_TEST_IN.rstrip("\n").split("\n")
    regions = find_regions(lines)
    assert [(a, b) for a, b, _ in regions] == [(1, 3), (5, 9)], regions
    got = []
    k = 0
    for a, b, _ in regions:
        got += lines[k:a] + normalise_script(lines[a : b + 1])
        k = b + 1
    got += lines[k:]
    assert "\n".join(got) + "\n" == SELF_TEST_OUT, "\n".join(got)
    print("self-test OK")
    return 0


def main(argv):
    if "--self-test" in argv:
        return self_test()
    write = "--write" in argv
    verbose = "--verbose" in argv
    args = [a for a in argv if not a.startswith("--")]
    cf, major = find_clang_format()
    if cf is None:
        print("clang-format not found: skipping the format check")
        return 0
    if major != CLANG_FORMAT_MAJOR and "--any-version" not in argv:
        print("clang-format %s found, the tree is formatted with %d: skipping the format check "
              "(--any-version runs it anyway)" % (major, CLANG_FORMAT_MAJOR))
        return 0
    if args:
        files = []
        for a in args:
            rel = os.path.relpath(os.path.abspath(a), ROOT).replace("\\", "/")
            if os.path.isdir(a):
                files += [f for f in tree_files() if f.startswith(rel.rstrip("/") + "/")]
            elif wanted(rel):
                files.append(rel)
    else:
        files = tree_files()
    changed = []
    for rel in files:
        if process(cf, rel, write):
            changed.append(rel)
            if verbose or not write:
                print(rel)
    if verbose:
        for n in NOTES:
            print("note: " + n)
    verb = "reformatted" if write else "would be reformatted"
    print("%d of %d files %s" % (len(changed), len(files), verb))
    return 1 if changed and not write else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
