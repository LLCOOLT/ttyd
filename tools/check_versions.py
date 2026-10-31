#!/usr/bin/env python3
"""Check how the game code tests the version it is built for.

The game code (src/, rels/, include/) writes version conditions with the ordered values from
include/version.h: `#if VERSION >= VERSION_US`, `#if VERSION <= VERSION_DEMO_JP` and so on. This script
fails if a file

  1. uses one of configure.py's per-version macros (VERSION_G8MJ01, VERSION_G8ME01, VERSION_G8MP01,
     VERSION_G8ME01_DEMO, VERSION_G8MJ01_DEMO, VERSION_G8ME01_DEMO2, VERSION_G8MP01_DEMO) instead; only include/version.h turns those into VERSION;
  2. tests one of the ordered values with #ifdef/#ifndef/defined() (VERSION_JP and the others are always
     defined, so such a test is true in every version);
  3. tests VERSION in an #if before include/version.h is included (directly or through another header):
     an undefined name counts as 0 in #if, so `VERSION == VERSION_DEMO_JP` would quietly be true everywhere;
  4. names in an #if a VERSION_ value that include/version.h does not define (such as the old VERSION_DEMO),
     which counts as 0 the same way.

It needs no game files. Usage: python tools/check_versions.py [-v]
"""

import argparse
import os
import re
import sys
from typing import Dict, List, Optional, Set

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
SCAN_DIRS = ["src", "rels", "include"]
EXTS = (".c", ".h", ".inc", ".cpp")
VERSION_HEADER = "include/version.h"
# Include search paths of the game code (configure.py), plus each REL's own include folder.
INCLUDE_DIRS = ["include", "libs/dolsdk2004/include", "libs/dolsdk2004/include/libc", "libs/musyx/include"]

OLD_MACRO = re.compile(r"\bVERSION_G8M(?:J01|E01|P01)(?:_DEMO2?)?\b")
ORDERED = r"VERSION_(?:DEMO_US2|DEMO_US|DEMO_JP|DEMO_EU|JP|US|EU)\b"
VERSION_NAME = re.compile(r"\bVERSION_\w+")
DEFINE_VALUE = re.compile(r"^\s*#\s*define\s+(VERSION_\w+)\s+\d")
DEFINED_TEST = re.compile(r"^\s*#\s*(?:ifdef|ifndef)\s+" + ORDERED + r"|\bdefined\s*\(?\s*" + ORDERED)
IF_LINE = re.compile(r"^\s*#\s*(?:if|elif)\b(.*)")
USES_VERSION = re.compile(r"\bVERSION\b")
INCLUDE = re.compile(r'^\s*#\s*include\s*[<"]([^">]+)[">]')


def rel(path: str) -> str:
    return os.path.relpath(path, ROOT).replace(os.sep, "/")


def strip_comments(text: str) -> str:
    """Blank out comments, keeping line breaks and string literals."""
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("\n" * text.count("\n", i, j))
            i = j
        elif c == '"' or c == "'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            out.append(text[i:j + 1])
            i = j + 1
        else:
            out.append(c)
            i += 1
    return "".join(out)


class Checker:
    def __init__(self) -> None:
        self.lines: Dict[str, List[str]] = {}
        self.provides: Dict[str, bool] = {}
        self.values: Set[str] = set()
        for line in self.read(os.path.join(ROOT, VERSION_HEADER)):
            m = DEFINE_VALUE.match(line)
            if m:
                self.values.add(m.group(1))

    def read(self, path: str) -> List[str]:
        if path not in self.lines:
            with open(path, encoding="utf-8", errors="replace") as f:
                self.lines[path] = strip_comments(f.read()).split("\n")
        return self.lines[path]

    def resolve(self, name: str, from_file: str) -> Optional[str]:
        dirs = [os.path.dirname(from_file)]
        parts = rel(from_file).split("/")
        if parts[0] == "rels" and len(parts) > 2:
            dirs.append(os.path.join(ROOT, "rels", parts[1], "include"))
        dirs += [os.path.join(ROOT, d) for d in INCLUDE_DIRS]
        for d in dirs:
            p = os.path.normpath(os.path.join(d, name))
            if os.path.isfile(p):
                return p
        return None

    def includes_version(self, path: str, stack: Set[str]) -> bool:
        """True if including `path` brings in include/version.h."""
        if rel(path) == VERSION_HEADER:
            return True
        if path in self.provides:
            return self.provides[path]
        if path in stack:
            return False
        stack.add(path)
        result = False
        for line in self.read(path):
            m = INCLUDE.match(line)
            if m:
                inc = self.resolve(m.group(1), path)
                if inc and self.includes_version(inc, stack):
                    result = True
                    break
        stack.discard(path)
        self.provides[path] = result
        return result

    def check(self, path: str) -> List[str]:
        errors = []
        name = rel(path)
        have_version = name == VERSION_HEADER
        for no, line in enumerate(self.read(path), 1):
            m = INCLUDE.match(line)
            if m:
                inc = self.resolve(m.group(1), path)
                if inc and self.includes_version(inc, set()):
                    have_version = True
                continue
            if name == VERSION_HEADER:
                continue
            if OLD_MACRO.search(line):
                errors.append(f"{name}:{no}: uses {OLD_MACRO.search(line).group(0)}; "
                              "write the condition with VERSION (include/version.h)")
            if DEFINED_TEST.search(line):
                errors.append(f"{name}:{no}: tests whether an ordered version value is defined "
                              "(always true); compare VERSION with it instead")
            m = IF_LINE.match(line)
            if m:
                for used in VERSION_NAME.findall(m.group(1)):
                    if used not in self.values and not OLD_MACRO.fullmatch(used):
                        errors.append(f"{name}:{no}: {used} is not a version value of include/version.h "
                                      "(an unknown name counts as 0 in #if)")
            if m and USES_VERSION.search(m.group(1)) and not have_version:
                errors.append(f"{name}:{no}: tests VERSION before include/version.h is included")
                have_version = True  # one report per file is enough
        return errors


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("-v", "--verbose", action="store_true", help="print the number of files checked")
    args = parser.parse_args()

    checker = Checker()
    errors: List[str] = []
    count = 0
    for top in SCAN_DIRS:
        for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, top)):
            dirnames.sort()
            for fn in sorted(filenames):
                if fn.endswith(EXTS):
                    count += 1
                    errors += checker.check(os.path.join(dirpath, fn))
    for e in errors:
        print(e)
    if args.verbose or errors:
        print(f"check_versions: {count} files, {len(errors)} problem(s)")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
