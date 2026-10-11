"""fd.py <unit> <symbol>... : rebuild unit's object, print side-by-side asm diff (target | ours)."""
import json, os, subprocess, sys, tempfile

repo = os.getcwd()
unit, syms = sys.argv[1], sys.argv[2:]
obj = "build/G8MJ01/src/" + unit.split("/", 1)[1] + ".o"
r = subprocess.run([sys.executable, "-m", "ninja", obj.replace("/", "\\")], capture_output=True, text=True)
if r.returncode:
    print(r.stdout[-4000:], r.stderr[-2000:]); sys.exit(1)
out = os.path.join(tempfile.gettempdir(), "fd.json")
for sym in syms:
    subprocess.run([os.path.join(repo, "build", "tools", "objdiff-cli.exe"), "diff", "-p", ".", "-u", unit, "-o", out, sym],
                   capture_output=True)
    d = json.load(open(out))
    def find(side):
        for s in d.get(side, {}).get("symbols", []):
            if s.get("name") == sym:
                return s
    L, R = find("left"), find("right")
    lp = (L or {}).get("match_percent")
    print(f"== {sym}: {lp if lp is not None else (R or {}).get('match_percent')}%")
    li = (L or {}).get("instructions", [])
    ri = (R or {}).get("instructions", [])
    if lp == 100 or (R or {}).get("match_percent") == 100:
        continue
    for i in range(max(len(li), len(ri))):
        a = li[i] if i < len(li) else {}
        b = ri[i] if i < len(ri) else {}
        fa = a.get("instruction", {}).get("formatted", "")
        fb = b.get("instruction", {}).get("formatted", "")
        k = a.get("diff_kind") or b.get("diff_kind") or ""
        mark = "  " if not k else "!!"
        print(f"{mark} {fa:40s} | {fb}")
