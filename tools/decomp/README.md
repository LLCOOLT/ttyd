# Decomp helper scripts

Small scripts used while matching code. Run them from the repository root after
`python configure.py && python -m ninja` has produced `build/G8MJ01`.

| Script | Purpose |
| --- | --- |
| `fd.py <unit> <fn>...` | Rebuild one object and print a side-by-side asm diff (target \| ours) for each function. `<unit>` is the objdiff unit name, e.g. `MarioSt/battle/battle_acrobat`. |
| `sec.py <unit> <fn>` | Print per-section match percentages for a unit. |
| `tv.py <variants.txt> <unit> <fn>` | Try alternative source snippets (blocks separated by a `=====` line; the first block is the current text) and keep the best one, only if it beats the original. |
| `perm.py` | Brute-force local declaration order in a mini translation unit. |
| `flip.py Matching\|NonMatching <path>` | Flip one `Object(...)` in `configure.py`. |
| `tryflip.sh <path>...` | Flip each object to Matching, run the SHA-1 check, and revert if it fails. |
| `dolcmp.py` | Byte-compare `build/G8MJ01/MarioSt.dol` with the original DOL and name the differing symbols. |
| `secsize.py <path>` | Compare a unit's split section sizes with the compiled object and list trailing `gap_` objects. |
| `objcmp.py <path>` | List every target object next to the compiled object's section/offset/size. |
| `gendata.py <asm> <obj> <kinds>` | Emit C initializer rows for a struct array from the dtk asm. |
| `unitgen.py <asm basename>` | Generate C for a battle unit file (unit/part tables, defence tables, pose/data tables, evt scripts via `tools/ttydasm`). Run against an unflipped build. |
| `assemble.py` | Combine `unitgen.py` output with hand-written functions. |
| `fixpairs2.py [--apply]` | Move `.data` split boundaries so each TU starts with its leading `{-1.0f, 1.0f}` pair. |

`unitgen.py` needs `tools/ttydasm` built (`cargo build --release` in that directory).
