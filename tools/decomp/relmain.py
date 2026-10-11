"""relmain.py <module>...: write relfuncs/<mod>/<mod>/{_prolog,_epilog,_unresolved}.c snippets for a REL's
main file (<mod>.c) when its _prolog/_epilog only run the ctor/dtor loops plus plain calls whose
arguments are symbol addresses (relSetEvtAddr/relSetBtlAddr) or nothing. Run relbatch.py gen afterwards."""
import os
import re
import sys

here = os.path.dirname(os.path.abspath(__file__))


def unesc(s):
    return re.sub(r'\\(\d{3})', lambda m: chr(int(m.group(1), 8)), s)


def parse(body):
    """Return (before_loop_calls, after_loop_calls) or None. Each call is (name, [arg symbols])."""
    lines = [re.sub(r'^/\* .*? \*/\t', '', l).strip() for l in body.split('\n')]
    before, after, cur = [], [], None
    regs = {}
    seen_loop = False
    for l in lines:
        if not l or l.startswith(('.fn', '.endfn')):
            continue
        if l.startswith('bne '):
            seen_loop = True
            continue
        m = re.match(r'lis r(\d+), (\w+)@ha', l)
        if m:
            if m.group(2) not in ('_ctors', '_dtors'):
                regs[int(m.group(1))] = m.group(2)
            continue
        m = re.match(r'addi r(\d+), r(\d+), (\w+)@l', l)
        if m:
            if m.group(3) not in ('_ctors', '_dtors'):
                regs[int(m.group(1))] = m.group(3)
            continue
        m = re.match(r'bl (\w+)', l)
        if m:
            n = len(regs)
            if sorted(regs) != list(range(3, 3 + n)):
                return None
            (after if seen_loop else before).append((m.group(1), [regs[r] for r in range(3, 3 + n)]))
            regs = {}
            continue
        if re.match(r'(stwu|mflr|stw|lwz|mtlr|addi r1|blr|mr r31|b |mtctr|bctrl|addi r31|cmplwi r12|\.L_)', l):
            continue
        return None
    return before, after


def main(mod):
    asm = f'build/G8MJ01/{mod}/asm/{mod}.s'
    if not os.path.exists(asm):
        print(mod, 'no asm')
        return
    src = open(asm, encoding='utf-8').read()
    fns = dict(re.findall(r'^\.fn (\w+), \w+\n(.*?)^\.endfn', src, re.M | re.S))
    # vivian's pose table is swapped out while the module is loaded (gra, jin, usu)
    pose = 'pose_buf' in fns['_prolog']
    extra = set(fns) - {'_prolog', '_epilog', '_unresolved'} - ({f'evt_{mod}_vivian_pose_set'} if pose else set())
    if extra:
        print(mod, 'also needs snippets for:', ', '.join(sorted(extra)))
    tails = {'_prolog': [], '_epilog': []}
    if pose:
        fns['_prolog'] = fns['_prolog'][:fns['_prolog'].index('li r3, 0x3c')]
        fns['_epilog'] = fns['_epilog'][:fns['_epilog'].index('lis r4, partyPoseTbl')]
        tails['_prolog'] = ['    pose_buf = _mapAlloc(sizeof(partyPoseTbl[6]));',
                            '    memcpy(pose_buf, partyPoseTbl[6], sizeof(partyPoseTbl[6]));']
        tails['_epilog'] = ['    memcpy(partyPoseTbl[6], pose_buf, sizeof(partyPoseTbl[6]));', '    _mapFree(pose_buf);']
    strs = {m.group(1): unesc(m.group(2)) for m in re.finditer(r'^\.obj (str_\w+), \w+\n\t\.string "(.*?)(?:\\000)*"$', src, re.M)}
    out = os.path.join(here, 'relfuncs', mod, mod)
    os.makedirs(out, exist_ok=True)
    externs = set()

    def calls(lst):
        res = []
        for name, args in lst:
            cargs = []
            for a in args:
                if a in strs:
                    cargs.append('"%s"' % strs[a])
                else:
                    cargs.append(a)
                    externs.add(a)
            res.append(f'    {name}({", ".join(cargs)});')
            if name not in ('relSetEvtAddr', 'relSetBtlAddr'):
                externs.add(name + '()')
        return res

    parts = {}
    for f, var, arr in (('_prolog', 'ctor', '_ctors'), ('_epilog', 'dtor', '_dtors')):
        p = parse(fns[f])
        if p is None:
            if os.path.exists(os.path.join(out, f + '.manual.c')):
                parts[f] = None  # hand-written, see <f>.manual.c
                continue
            print(mod, 'unhandled', f, '(write relfuncs/%s/%s/%s.manual.c)' % (mod, mod, f))
            return
        before, after = p
        parts[f] = [f'void {f}(void) {{', f'    voidfunctionptr* {var};', '']
        parts[f] += calls(before)
        parts[f] += [f'    for ({var} = {arr}; *{var} != NULL; {var}++) {{', f'        (*{var})();', '    }']
        parts[f] += calls(after)
        parts[f] += tails[f]
        parts[f] += ['}']
    decls = ['typedef void (*voidfunctionptr)(void);', 'extern voidfunctionptr _ctors[];', 'extern voidfunctionptr _dtors[];']
    for e in sorted(externs):
        decls.append(f'void {e[:-2]}(void);' if e.endswith('()') else f'extern s32 {e}[];')
    incs = ['// include: data/mapdata.h']
    if pose:
        decls += ['extern char* partyPoseTbl[20][15];', 'static void* pose_buf;']
        incs += ['// include: memory.h', '// include: string.h']
        name = f'evt_{mod}_vivian_pose_set'
        write(out, name, [f'USER_FUNC({name}) {{', '    s32* args = event->args;',
                          '    s32 index = evtGetValue(event, args[0]);',
                          '    partyPoseTbl[6][index] = (char*)evtGetValue(event, args[1]);',
                          '    return EVT_RETURN_DONE;', '}'], proto=f'USER_FUNC({name});')
    decls = ['// decl: ' + d for d in decls]
    for f, extra in (('_prolog', incs), ('_epilog', [])):
        if parts[f] is None:
            manual = open(os.path.join(out, f + '.manual.c'), encoding='utf-8').read().rstrip('\n').split('\n')
            write(out, f, extra + decls + manual)
        else:
            write(out, f, extra + decls + parts[f])
    write(out, '_unresolved', ['void _unresolved(void) {', '}'])
    print(mod, 'ok')


def write(out, f, lines, proto=None):
    head = [l for l in lines if l.startswith(('// include:', '// decl:'))]
    rest = [l for l in lines if not l.startswith(('// include:', '// decl:'))]
    text = '\n'.join(head + [f'// proto: {proto or f"void {f}(void);"}'] + rest) + '\n'
    open(os.path.join(out, f + '.c'), 'w', encoding='utf-8', newline='\n').write(text)


for m in sys.argv[1:]:
    main(m)
