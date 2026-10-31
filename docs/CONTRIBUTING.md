# Contributing

Contributions are welcome: clearer names and types, comments that explain what code does, documentation, and anything that makes the code easier to read while every version still builds byte-identical. Please open an issue in this repository for questions.

## The five-version check

Every change must keep all five versions byte-identical. Before you commit, build each version whose game files you have and confirm the check line:

```sh
for v in G8MJ01 G8ME01 G8MP01 G8ME01_DEMO G8MJ01_DEMO; do
    python configure.py --version $v && ninja || break
done
```

| Version | Expected |
|---|---|
| `G8MJ01` | `32 files OK` |
| `G8ME01` | `30 files OK` |
| `G8MP01` | `33 files OK` |
| `G8ME01_DEMO` | `7 files OK` |
| `G8MJ01_DEMO` | `33 files OK` |

This applies to every kind of change, including comment-only and header-only edits:

- Declaration order and prototype types can change register allocation, so moving or retyping a declaration is checked like a code change.
- Line numbers are part of the output in a few places: the SDK's `ASSERT` macros, and in `rels/tst/` the SGI GLU sources (`rels/tst/src/glu/`) and the test units that call `__assert2("file.c", line, ...)`. Do not reflow or re-indent those files, and do not add or remove lines above an assertion in them.
- `src/` and `rels/` sources are UTF-8 and are converted to Shift-JIS when compiled (see [BUILDING.md](BUILDING.md#troubleshooting)), so keep files UTF-8.

[BUILDING.md](BUILDING.md) explains the builds; objdiff (same page) shows exactly which function or data object differs when a check fails.

## Code standards

The code is meant to read like the original source. In order of importance:

- **Struct fields, not offsets.** Access data through struct members, never pointer arithmetic on raw byte offsets (`*(T*)((u8*)p + 0x1C)`). If a struct is not known yet, define it with the members you can name and padding for the rest. One struct per object: declare it once, in the header of the code that owns it. Unnamed bytes follow one rule: `pad_<hex offset>` (`u8 pad_1C[0x20 - 0x1C];`) for bytes no code reads or writes, and `reserved_<hex offset>` for a field that holds a value (set in data or written by the code) that nothing reads. A field that something reads gets a real name.
- **Typed data.** Tables are arrays of structs, floats are `f32`, strings are strings, flags and ids use the enums and named constants that exist (`include/` has most of them), and scripts use the script macros (`include/evt/evt_cmd.h`) rather than raw words.
- **Story flags by name.** Saved story values and flags use the names in `include/evt/evt_story.h`, written the same way in scripts and in C: `IF_INT_EQUAL(GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED), 0)`, `swGet(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED)`, `swByteGet(GSW_TOU_PLAYER_RANK)`. Story progress is `GSW(GSW_STORY_PROGRESS)` compared with the `STORY_*` values, which follow the event table in `src/event.c` (`CASE_LESS(STORY_STG1_00_PETAL_MEADOWS)`). A new name gets a one-line meaning in the header; a block the code indexes gets a `_BASE` name and an offset. Area-local values (`LSW`/`LSWF`) are reused by every map and stay numbers.
- **The named word types.** A script word is `EvtWord` (`include/evt/evt_word.h`); an integer that holds an address for address arithmetic is `AddrWord` (`include/addr_word.h`); a sound parameter that takes a name or an id is `SfxNameWord` (`include/sfx_name_word.h`). Do not store pointers in `s32`.
- **Names.** Use the original names where they are known (the symbol maps; see [NAME_PROVENANCE.md](NAME_PROVENANCE.md) for the ones that were invented). Give fields, locals and parameters real names: no `unk_`, `field_`, `var_r31`, `temp_f0`, `a1` placeholders in new code.
- **Naming style.** Struct members, locals and parameters are camelCase with no prefix (`position`, `attributeFlags`; not mPosition). Enumerators and macro constants are UPPER_SNAKE with a prefix naming their enum (`UNIT_ATTR_FLOATING`, `PART_ATTR_WINGED`, `NPC_FLAG_HIDDEN`; not kFloating). Functions and data keep the original symbol name where one is known, whatever its style; new function names follow the style of their file. Never put an address in a name (`card_title`, `_800C23B4`): describe what the thing is. Log an invented symbol name (a function or data label in `config/<version>/symbols.txt`) or story flag in [NAME_PROVENANCE.md](NAME_PROVENANCE.md); for other invented names (types, struct fields, enum members, static functions) the comment at the declaration gives the evidence.
- **Declarations live in headers.** A function or variable used by more than one file is declared in its owner's header and included, not re-declared with `extern` in each `.c` file.
- **No assembly.** The only assembly is what the original sources had in assembly: routines in `libs/`, the hardware helpers in `include/hwaccess.h` and the word copy `memcpy_as4` in `src/system.c`. Do not add inline asm or asm-backed functions, and do not use the `register` keyword or other means of choosing registers to force a match.
- **Formatting.** Code follows the repository's `.clang-format`; scripts (`EVT_BEGIN` ... `EVT_END`) have one command per line, indented four spaces per `IF`/`ELSE`/`SWITCH`/`LOOP`/inline-event level. `python tools/format_check.py` lists files that do not (with `--write` it fixes them); it uses clang-format for C code, keeps multi-line data tables as laid out and never moves lines whose text or line number is compiled in (asserts). `libs/` and the GLU code in `rels/tst` keep their own style. The lint job runs the check.
- **Comments** say what code does and why, especially for game logic, version differences and anything surprising. Every function, `USER_FUNC` and event script has a description directly above it as a doc block (`/** ... */` for a short one, otherwise `/**`, ` * ` lines and ` */`; keep lines to about 110 characters and break them where the text reads naturally: at a sentence end, after a colon, semicolon or comma, or before a joining word such as "and" or "then", never inside a short parenthesis); inline notes inside bodies and on struct members use `//`. In a file whose line numbers reach the object (it uses `__LINE__` or an assert macro that passes it), a description must not add lines: open with `/** ` on its first line and close with ` */` on its last. Start a description with `Guess:` when it is inferred rather than confirmed in the code, or `Unknown:` followed by what is known. A bug of the original game gets a `// BUG:` comment and a row in [KNOWN_GAME_BUGS.md](KNOWN_GAME_BUGS.md).

## Fakes

Sometimes the natural C does not produce the original instructions, and a small behaviour-identical trick does: an extra temporary, a no-op cast, a dead guard, a particular declaration order, a pragma. These are allowed, as long as:

1. the behaviour is identical: a fake never reads uninitialised memory and never changes what the code does;
2. it is marked at the site with a `// FAKE:` comment that says what the trick does;
3. it has a row in [FAKES.md](FAKES.md) (version, file, function, what the trick is, the natural forms that were tried).

Replacing a fake with natural C that still matches is always welcome; then delete its comment and its row. [FAKES.md](FAKES.md) explains why such tricks change the compiler's output.

## Adding a version difference

When code differs between versions (see [VERSIONS.md](VERSIONS.md)):

- **Pick the right condition.** Compare `VERSION` with the ordered values from `include/version.h`: US-and-PAL code goes inside `#if VERSION >= VERSION_US`, code of JP and both demos inside `#if VERSION <= VERSION_JP`, code of both demos inside `#if VERSION <= VERSION_DEMO_US`, and code for one version inside `#if VERSION == VERSION_EU` (or `_JP`, `_US`, `_DEMO_US`, `_DEMO_JP`). The two demos share their code, so a demo difference covers both unless the Japanese demo shows otherwise; `VERSION == VERSION_DEMO_US` is for what only the US demo has, mostly its English text. Include `version.h` before the first condition. `python tools/check_versions.py` checks this (it needs no game files, and the lint job runs it on every push and pull request); configure.py's `VERSION_G8M*` macros are for `version.h` and the library code only.
- **Keep it small.** Wrap only the statements, members or values that differ, not a whole function, unless most of it differs. For a single value, use `VERSION_PICK(jp, us)` from `include/version.h`; for frame counts and easing that the US code scales by the frame rate, use `FPS_FRAMES(n)` and `FPS_EASE(n)`.
- **Structs.** A member that exists only in some versions sits inside the `#ifdef` in the struct itself, so every field access stays correct for every version. Put the version's offset in the member's comment when it helps (`// 0x2CC (US 0x2D0)`).
- **Say why.** Start the block with a short comment when the difference is not obvious (`// PAL: the plain modes are 50Hz ...`).
- **Units and data.** A unit that exists only in some versions is listed once as `Matching` in `configure.py`; its address ranges and symbols go in the `config/<version>/splits.txt` and `symbols.txt` of each version that has it, and the splits alone decide which versions build it.
- **Check all five builds.**

## Commit messages

One line that says what changed, in the imperative or as a short statement; a leading area (`battle:`, `pal:`, `docs:`) helps when the change sits in one place. For example:

```
battle: name the BattleUnit status fields
pal: tst.rel test battle units match from C
demo: mapdrv links from C (bmapUnLoad dead guard, see FAKES.md)
docs: VERSIONS.md lists the REL sets
```

Add a body when the reason is not obvious. Keep each commit to one topic, and make sure every commit passes the five-version check on its own.
