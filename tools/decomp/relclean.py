"""relclean.py: compile-check every NonMatching REL object listed in configure.py and drop the ones that don't
compile (ninja builds NonMatching sources too, so one broken file fails every build)."""
import os
import re
import subprocess
import sys

here = os.path.dirname(os.path.abspath(__file__))
py = sys.executable
subprocess.run([py, 'configure.py'], capture_output=True)
cfg = open('configure.py', encoding='utf-8').read()
for m in re.finditer(r'    Rel\(\s*"(\w+)",\s*\[(.*?)\n        \]', cfg, re.S):
    mod = m.group(1)
    bad = []
    for name in re.findall(r'Object\(NonMatching, "([^"]+)"', m.group(2)):
        if not os.path.exists(f'rels/{mod}/src/{name}'):
            bad.append(name)
            continue
        r = subprocess.run([py, '-I', os.path.join(here, 'relcc.py'), f'rels/{mod}/src/{name}'], capture_output=True, text=True)
        if r.returncode:
            bad.append(name)
    if bad:
        print(mod, 'drop', ' '.join(bad))
        subprocess.run([py, '-I', os.path.join(here, 'relcfg.py'), mod, 'Remove', *bad])
