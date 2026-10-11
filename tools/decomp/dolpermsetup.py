"""dolpermsetup.py <src/...c | libs/...c> <function> [outdir]: set up a decomp-permuter job for one DOL function.

Same output layout as relpermsetup.py (base.c, compile.sh, settings.toml, target.o, fndump.py), but the compiler
command is the unit's exact ninja command (`python -m ninja -t commands <obj>`). Units without a compile rule yet
borrow a sibling .c's command (else src/event/evt_env.c). Target = build/G8MJ01/obj/<unit>.o.
DOLCC_EXTRA adds extra cflags. Run the permuter afterwards with
    python <decomp-permuter>/permuter.py <outdir> -j8
"""
import glob
import os
import re
import shlex
import subprocess
import sys

BS = chr(92)
src = sys.argv[1].replace(BS, '/')
fn = sys.argv[2]
out = sys.argv[3] if len(sys.argv) > 3 else os.path.join(os.environ.get('TEMP', '.'), 'perm', fn)
os.makedirs(out, exist_ok=True)
root = os.getcwd().replace(BS, '/')
NINJA = open('build.ninja', encoding='utf-8').read()


def unit_of(path):
    """configure.py unit name for a source path (src/a/b.c -> a/b, libs/x/src/a/b.c -> a/b)."""
    m = re.search(r'^build build\\G8MJ01\\src\\(\S+)\.o: mwcc\S* \$\n\s+' + re.escape(path.replace('/', BS)) + r'\s',
                  NINJA, re.M)
    if m:
        return m.group(1).replace(BS, '/')
    if path.startswith('libs/'):
        return path.split('/src/', 1)[1][:-2]
    return path[len('src/'):-2]


def cmd_for(unit):
    obj = BS.join(['build', 'G8MJ01', 'src'] + unit.split('/')) + '.o'
    r = subprocess.run([sys.executable, '-m', 'ninja', '-t', 'commands', obj], capture_output=True, text=True)
    lines = r.stdout.strip().splitlines()
    return lines[-1].split(' && ')[0] if lines else None


unit = unit_of(src)
cmd = cmd_for(unit)
if not cmd:
    donors = sorted(p.replace(BS, '/') for p in glob.glob(f'{os.path.dirname(src)}/*.c')) + ['src/event/evt_env.c']
    for dn in donors:
        if dn == src:
            continue
        cmd = cmd_for(unit_of(dn))
        if cmd:
            print(f'(compile flags borrowed from {dn})', file=sys.stderr)
            break
if not cmd:
    sys.exit(f'no ninja compile command for {src}')

# cmd: sjiswrap cc flags... -c <src> -o <out>; drop the source/output/depfile args
args = shlex.split(cmd.replace(BS, '/'))
cc = args[1] if os.path.isabs(args[1]) else f'{root}/{args[1]}'
flags, i = [], 2
while i < len(args):
    a = args[i]
    if a in ('-c', '-o'):
        i += 2
    elif a in ('-MMD', '-MD'):
        i += 1
    elif a == '-i' and i + 1 < len(args):
        p = args[i + 1]
        flags += ['-i', p if os.path.isabs(p) else f'{root}/{p}']
        i += 2
    else:
        flags.append(f'"{a}"' if ' ' in a else a)
        i += 1
cflags = ' '.join(flags) + ' ' + os.environ.get('DOLCC_EXTRA', '')

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
    f'objdump_command = "{sys.executable.replace(BS, "/")} {dump.replace(BS, "/")}"\n')
target = f'build/G8MJ01/obj/{unit}.o'
if not os.path.exists(target):
    sys.exit(f'no target object {target}')
with open(target, 'rb') as a, open(os.path.join(out, 'target.o'), 'wb') as b:
    b.write(a.read())
print(out)
