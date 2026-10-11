"""relpermsetup.py <rels/<mod>/src/...c> <function> [outdir]: set up a decomp-permuter job for one REL function.

Preprocesses the generated source with the module's own flags (RELCC_DEFERRED=1 / RELCC_EXTRA as in relcc.py),
writes base.c, compile.sh, settings.toml and a target.o link, and an objdump wrapper that disassembles only the
function so the rest of the file does not enter the score. Run the permuter afterwards with
    python <decomp-permuter>/permuter.py <outdir> -j8
"""
import os
import re
import subprocess
import sys

src = sys.argv[1].replace('\\', '/')
fn = sys.argv[2]
mod = src.split('/')[1]
rel = src.split('/src/', 1)[1][:-2]
out = sys.argv[3] if len(sys.argv) > 3 else os.path.join(os.environ.get('TEMP', '.'), 'perm', fn)
os.makedirs(out, exist_ok=True)
root = os.getcwd().replace('\\', '/')

ninja = open('build.ninja', encoding='utf-8').read().replace('$\n    ', '').replace('$\n      ', '')
m = re.search(r'^build build\\G8MJ01\\' + mod + r'\\src\\\S+\.o: mwcc_sjis .*?\n  mw_version = (\S+)\n  cflags = (.*?)\n',
              ninja, re.M | re.S)
if not m:
    sys.exit(f'no REL compile statement for {mod}')
ver, cflags = m.group(1), m.group(2).replace(' -inline auto,deferred', '')
if os.environ.get('RELCC_DEFERRED') == '1':
    cflags += ' -inline auto,deferred'
cflags += ' ' + os.environ.get('RELCC_EXTRA', '')
cc = f'{root}/build/compilers/{ver.replace(chr(92), "/")}/mwcceppc.exe'
# absolute include paths so compile.sh works from the permuter's temp files
cflags = re.sub(r'-i\s+(\S+)', lambda mm: '-i ' + (mm.group(1) if os.path.isabs(mm.group(1)) else f'{root}/{mm.group(1)}'),
                cflags.replace('\\', '/'))

# preprocess without sjiswrap so the UTF-8 text survives; candidates are compiled through sjiswrap
r = subprocess.run(f'"{cc}" {cflags} -EP {src}', shell=True, capture_output=True)
if r.returncode:
    sys.exit(r.stdout.decode('utf-8', 'replace') + r.stderr.decode('utf-8', 'replace'))
text = r.stdout.decode('utf-8', 'replace').replace('\r\n', '\n')
# pycparser does not know MWCC extensions
text = re.sub(r'^###.*$|^#\s.*$', '', text, flags=re.M)
text = re.sub(r'__declspec\s*\([^()]*\)|__attribute__\s*\(\(.*?\)\)', '', text)
text = text.replace('__typeof__(sizeof(0))', 'unsigned long')
# pycparser reads "sizeof(T) + x" as sizeof of a cast
text = re.sub(r'\bsizeof\s*\(\s*(\w+(?:\s*\*)*)\s*\)', r'(sizeof(\1))', text)
text = re.sub(r'\n{3,}', '\n\n', text)
open(os.path.join(out, 'base.c'), 'w', encoding='utf-8', newline='\n').write(text)

open(os.path.join(out, 'compile.sh'), 'w', newline='\n').write(
    f'#!/bin/bash\n"{root}/build/tools/sjiswrap.exe" "{cc}" {cflags} -c "$1" -o "$3"\n')
dump = os.path.join(out, 'fndump.py')
# branch targets inside the function are printed as absolute addresses; make them function-relative
open(dump, 'w', newline='\n').write(
    'import re, subprocess, sys\n'
    f'out = subprocess.run([r"{root}/build/binutils/powerpc-eabi-objdump.exe", "-dr", "-EB", "-mpowerpc",'
    f' "-M", "broadway", "--disassemble={fn}", sys.argv[1]], capture_output=True, text=True).stdout\n'
    f'out = re.sub(r"(?<= )[0-9a-f]+ <{fn}(?:\\+0x([0-9a-f]+))?>", lambda m: "%x" % int(m.group(1) or "0", 16), out)\n'
    'sys.stdout.write(out)\n')
open(os.path.join(out, 'settings.toml'), 'w', newline='\n').write(
    f'func_name = "{fn}"\ncompiler_type = "mwcc"\n'
    f'objdump_command = "{sys.executable.replace(chr(92), "/")} {dump.replace(chr(92), "/")}"\n')
target = f'build/G8MJ01/{mod}/obj/{rel}.o'
with open(target, 'rb') as a, open(os.path.join(out, 'target.o'), 'wb') as b:
    b.write(a.read())
print(out)
