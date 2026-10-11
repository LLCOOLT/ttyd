"""relmakename.py: write per-file relfuncs snippets for every REL `make_name` (sprintf of an evt value into a
static name buffer, then return the buffer through the second arg)."""
import glob
import os
import re

here = os.path.dirname(os.path.abspath(__file__))
for asm in glob.glob('build/G8MJ01/*/asm/**/*.s', recursive=True):
    parts = asm.replace('\\', '/').split('/')
    if parts[2] == 'asm':
        continue
    src = open(asm, encoding='utf-8').read()
    m = re.search(r'^\.fn make_name, \w+\n(.*?)^\.endfn', src, re.M | re.S)
    if not m:
        continue
    body = m.group(1)
    fmt = re.search(r'lis r4, (str_\w+)@ha', body)
    buf = re.search(r'lis r6, (\S+)@ha', body)
    if not fmt or not buf or 'sprintf' not in body:
        print('skip', asm)
        continue
    s = re.search(r'^\.obj ' + re.escape(fmt.group(1)) + r', \w+\n\t\.string "(.*?)(?:\\000)*"$', src, re.M).group(1)
    b = buf.group(1)
    size = int(re.search(r'^# \.bss:0x\w+ \| 0x\w+ \| size: (0x\w+)\n\.obj ' + re.escape(b) + ',', src, re.M).group(1), 16)
    mod, path = parts[2], '/'.join(parts[4:])[:-2]
    lines = ['// include: string.h' if False else '// include: stdio.h']
    if '$' in b:
        lines += ['// proto: USER_FUNC(make_name);', 'USER_FUNC(make_name) {', '    s32* args = event->args;',
                  f'    static char {b.split("$")[0]}[{size}];', '']
        b = b.split('$')[0]
    else:
        lines += [f'// decl: static char {b}[{size}];', '// proto: USER_FUNC(make_name);', 'USER_FUNC(make_name) {',
                  '    s32* args = event->args;', '']
    lines += [f'    sprintf({b}, "{s}", evtGetValue(event, args[0]));', f'    evtSetValue(event, args[1], (s32){b});',
              '    return EVT_RETURN_DONE;', '}']
    out = os.path.join(here, 'relfuncs', mod, path)
    os.makedirs(out, exist_ok=True)
    open(os.path.join(out, 'make_name.c'), 'w', encoding='utf-8', newline='\n').write('\n'.join(lines) + '\n')
    print('wrote', mod, path, s, b, size)
