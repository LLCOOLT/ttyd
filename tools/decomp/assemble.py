"""assemble.py <gen.c> <funcs.c> <out.c> <includes-file> [static fn names...]"""
import sys
gen = open(sys.argv[1], encoding='utf-8').read()
fn = open(sys.argv[2], encoding='utf-8').read()
inc = open(sys.argv[4], encoding='utf-8').read()
gen = gen[:gen.index('// TODO:')] if '// TODO:' in gen else gen
for name in sys.argv[5:]:
    kind, n = name.split(':')
    gen = gen.replace(f'USER_FUNC({n});\n', kind.replace('@', n) + '\n')
open(sys.argv[3], 'w', encoding='utf-8', newline='\n').write(inc + gen + fn)
