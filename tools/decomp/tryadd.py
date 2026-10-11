"""tryadd.py <module> <path> [deferred]: add Object(Matching, "<path>") to a REL module block in configure.py
(with -inline auto,deferred if requested), run the full build + SHA-1 check, and remove the line again on failure."""
import re
import subprocess
import sys

mod, path = sys.argv[1], sys.argv[2]
flags = ', extra_cflags=["-inline auto,deferred"]' if len(sys.argv) > 3 and sys.argv[3] == 'deferred' else ''
orig = open('configure.py', encoding='utf-8').read()
blk = re.search(r'    Rel\(\s*"' + re.escape(mod) + r'",\s*\[(.*?)\n        \]', orig, re.S)
if f'"{path}"' in blk.group(1):
    print('ALREADY PRESENT'); sys.exit(1)
line = f'\n            Object(Matching, "{path}"{flags}),'
new = orig[:blk.end(1)] + line + orig[blk.end(1):]
open('configure.py', 'w', encoding='utf-8', newline='').write(new)
subprocess.run([sys.executable, 'configure.py'], capture_output=True)
subprocess.run([sys.executable, '-m', 'ninja'], capture_output=True)
subprocess.run(['rm', '-f', 'build/G8MJ01/ok'])
r = subprocess.run([sys.executable, '-m', 'ninja', 'build\\G8MJ01\\ok'], capture_output=True, text=True)
if '32 files OK' in r.stdout:
    print('KEEP', mod, path)
else:
    print('REVERT', mod, path)
    print('\n'.join(l for l in r.stdout.splitlines() if 'FAIL' in l or 'error' in l.lower())[:2000])
    cur = open('configure.py', encoding='utf-8').read()
    open('configure.py', 'w', encoding='utf-8', newline='').write(cur.replace(line, '', 1))
    subprocess.run([sys.executable, 'configure.py'], capture_output=True)
