"""relcc.py <rels/<mod>/src/...c> [outdir]: compile one REL source with the module's flags (taken from
build.ninja) without going through ninja. Useful to check snippets while a batch owns the build."""
import os
import re
import subprocess
import sys

src = sys.argv[1].replace('\\', '/')
mod = src.split('/')[1]
out = sys.argv[2] if len(sys.argv) > 2 else os.path.join(os.environ.get('TEMP', '.'), 'relcc')
os.makedirs(out, exist_ok=True)
ninja = open('build.ninja', encoding='utf-8').read().replace('$\n    ', '').replace('$\n      ', '')
m = re.search(r'^build build\\G8MJ01\\' + mod + r'\\src\\\S+\.o: mwcc_sjis .*?\n  mw_version = (\S+)\n  cflags = (.*?)\n', ninja, re.M | re.S)
if not m:
    sys.exit(f'no REL compile statement for {mod}')
ver, cflags = os.environ.get('RELCC_VER', m.group(1)), m.group(2)
extra = os.environ.get('RELCC_EXTRA', '')
# the module's first compile statement may belong to a file pinned to the old deferred mode
cflags = cflags.replace(' -inline auto,deferred', '')
if os.environ.get('RELCC_DEFERRED') == '1':
    cflags += ' -inline auto,deferred'
cmd = f'build\\tools\\sjiswrap.exe build\\compilers\\{ver}\\mwcceppc.exe {cflags} {extra} -c {src} -o {out}'
r = subprocess.run(cmd, shell=True, capture_output=True, text=True, encoding='utf-8', errors='replace')
print(r.stdout + r.stderr)
sys.exit(r.returncode)
