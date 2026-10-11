"""relcfg.py <module> <Matching|NonMatching|Remove> <file>... : ensure each file is listed in the module's Rel()
block in configure.py with the given status (creates the Rel block if needed), or drop it with Remove."""
import re
import sys

mod, status = sys.argv[1], sys.argv[2]
files = sys.argv[3:]
p = 'configure.py'
s = open(p, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in s else '\n'
m = re.search(r'    Rel\(\s*"' + re.escape(mod) + r'",\s*\[(.*?)\n        \]', s, re.S)
if not m:
    if status == 'Remove':
        sys.exit(0)
    anchor = '    Rel(' + nl + '        "tou2",'
    assert anchor in s
    block = nl.join(['    Rel(', f'        "{mod}",', '        [', '        ]', '    ),', ''])
    s = s.replace(anchor, block + anchor, 1)
    m = re.search(r'    Rel\(\s*"' + re.escape(mod) + r'",\s*\[(.*?)\n        \]', s, re.S)
body = m.group(1)
for f in files:
    pat = re.compile(r'Object\((?:Matching|NonMatching), "' + re.escape(f) + '"')
    full = re.compile(r'Object\((?:Matching|NonMatching), "' + re.escape(f) + r'"(?:, extra_cflags=\[[^\]]*\])?\)')
    if status == 'Remove':
        body = re.sub(r'\r?\n *Object\((?:Matching|NonMatching), "' + re.escape(f) + r'"[^\n]*\),', '', body)
    elif status in ('MatchingDeferred', 'NonMatchingDeferred'):
        # file built with the old deferred-inlining flags
        st = status.replace('Deferred', '')
        new = f'Object({st}, "{f}", extra_cflags=["-inline auto,deferred"])'
        if full.search(body):
            body = full.sub(lambda _: new, body)
        else:
            body = body.rstrip() + nl + f'            {new},'
    elif status == 'Plain' and full.search(body):
        # drop a deferred pin, keeping the Matching/NonMatching status
        body = full.sub(lambda m: re.sub(r', extra_cflags=\[[^\]]*\]', '', m.group(0)), body)
    elif pat.search(body):
        body = pat.sub(f'Object({status}, "{f}"', body)
    else:
        body = body.rstrip() + nl + f'            Object({status}, "{f}"),'
s = s[:m.start(1)] + body + s[m.end(1):]
open(p, 'w', encoding='utf-8', newline='').write(s)
