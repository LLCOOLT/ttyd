"""flip.py <to: Matching|NonMatching> <path>: flips one Object() in configure.py; exits 1 if not found"""
import sys
to, path = sys.argv[1], sys.argv[2]
frm = 'NonMatching' if to == 'Matching' else 'Matching'
s = open('configure.py', encoding='utf-8').read()
old = f'Object({frm}, "{path}"'
if s.count(old) != 1:
    print('NOT FOUND', old); sys.exit(1)
open('configure.py', 'w', encoding='utf-8', newline='').write(s.replace(old, f'Object({to}, "{path}"'))
