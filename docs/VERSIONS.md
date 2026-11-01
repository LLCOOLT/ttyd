# Versions

One source tree builds seven versions of the game. This page says what differs between them and how the sources express those differences. Every statement about build flags here comes from `configure.py`; the macros are in `include/version.h`.

| Version | `BUILD_VERSION` | What it is | Code line |
|---|---|---|---|
| `G8MJ01` | 0 | Japanese release, Rev 0 | JP |
| `G8ME01` | 1 | North American release, Rev 0 | US |
| `G8MP01` | 2 | European release, Rev 0: English, German, French, Spanish and Italian, 50 Hz and 60 Hz | US plus PAL changes |
| `G8ME01_DEMO` | 3 | US demo build `MarioSt_MN7_NOA_20040619a` (June 2004), shipped as `zz_PaperMario2_game.tgc` on the Interactive Multi-Game Demo Disc Version 17 (USA) | JP plus demo changes |
| `G8MJ01_DEMO` | 4 | Japanese store demo, shipped as `files/local/tgc/PaperMarioRPG.tgc` on Gekkan Nintendo Tentou Demo 2004.7.1 (Japan) | the demo code, a little later than the US demo |
| `G8ME01_DEMO2` | 5 | US demo built on 18 September 2004, shipped as `zz_PaperMario2_game.tgc` on the Interactive Multi-Game Demo Disc Version 19 (USA) (also 20-22 and 35) | US plus a few demo changes |
| `G8MP01_DEMO` | 6 | European demo built on 23 September 2004, shipped as `zz_PaperMario2_PALDEMO_20040924.tgc` on the Interactive Multi-Game Demo Disk - November 2004 (Europe) | PAL plus the same demo changes |

## Preprocessor macros

`configure.py` passes `-DBUILD_VERSION=<n>` (the index above) and `-DVERSION_<version>` to every unit. The game code (`src/`, `rels/`, `include/`) does not test those directly: `include/version.h` turns them into `VERSION`, one of seven ordered values, and every version condition compares `VERSION` with them.

| Value | Version |
|---|---|
| `VERSION_DEMO_US` (0) | `G8ME01_DEMO` |
| `VERSION_DEMO_JP` (1) | `G8MJ01_DEMO` |
| `VERSION_JP` (2) | `G8MJ01` |
| `VERSION_US` (3) | `G8ME01` |
| `VERSION_DEMO_US2` (4) | `G8ME01_DEMO2` |
| `VERSION_DEMO_EU` (5) | `G8MP01_DEMO` |
| `VERSION_EU` (6) | `G8MP01` |

The June US demo comes before the Japanese store demo: in five places the Japanese demo already has the release code where the US demo has the older one (the `a_shop_keihin` event of `src/event/evt_shop.c`, the Goombella tip event of `hei_01`, `btlevtcmd_ACSuccessEffect`, the 8-row `_party_max_hp_table`, and the US demo's reset `OSReport` in `src/mario/mariost.c`). The two September 2004 demos sit between the US and the European release they were built from.

The order follows the history of the code, so one comparison names a code line:

- **US, PAL and the September demos: `#if VERSION >= VERSION_US`.** The European release was made from the US code, so everything US changed applies to PAL as well, and the two September demos were built from the US and PAL code.
- **PAL and the European demo: `#if VERSION >= VERSION_DEMO_EU`**: what PAL changed on top of US, usually nested in or next to a US block. What PAL changed after the European demo is `#if VERSION == VERSION_EU` (`mot_slit` and `mot_slit_post`, `kpa_cancel_attack_mode` and its call from `kpa_03`'s `jumpstand_evt`, the longer `shopper_talk_evt`). The opposite of the first is `#if VERSION < VERSION_DEMO_EU`.
- **US and the September US demo: `#if VERSION == VERSION_US || VERSION == VERSION_DEMO_US2`**: what US has and PAL replaced (`VERSION != VERSION_US && VERSION != VERSION_DEMO_US2` for the opposite).
- **JP and both early demos: `#if VERSION <= VERSION_JP`.** The June US demo is in English, but its code is the Japanese code from before localization: of the main executable functions where JP and US differ, 373 match JP in the US demo and none match US.
- **Both early demos: `#if VERSION <= VERSION_DEMO_JP`**, and the releases and the September demos: `#if VERSION >= VERSION_JP`. The two early demos are one code line: the Japanese demo is the demo code a little later, without the US demo's English text and a few kiosk changes, so a demo difference covers both unless the Japanese demo's own code shows otherwise.
- **June US demo only: `#if VERSION == VERSION_DEMO_US`** (or `!=` for every other version): what the June US demo has on top of the demo code, mostly for its English text (see [below](#the-japanese-demo-compared-with-the-us-demo-g8mj01_demo)). Where it already has the US code, the condition is `#if VERSION == VERSION_DEMO_US || VERSION >= VERSION_US`.
- **One version: `#if VERSION == VERSION_JP`** (and the same for the others).
- **Every demo: `#if VERSION <= VERSION_DEMO_JP || VERSION == VERSION_DEMO_US2 || VERSION == VERSION_DEMO_EU`**, and the three releases only: `#if VERSION == VERSION_JP || VERSION == VERSION_US || VERSION == VERSION_EU` (kiosk code the September demos took from the June demo).
- **The September demos: `#if VERSION == VERSION_DEMO_US2 || VERSION == VERSION_DEMO_EU`**; with PAL: `#if VERSION >= VERSION_DEMO_US2` (`seq_e3Main`); the US and PAL releases without them: `#if VERSION == VERSION_US || VERSION == VERSION_EU`.
- **Every version but one: `#if VERSION != VERSION_JP`.** JP is the only version without a change that both early demos and the US code line have (for example the battle work allocation in `src/battle/battle.c`), so `!= VERSION_JP` covers every other version. `#if VERSION != VERSION_DEMO_US` is every version except the June US demo.

In comments, "the demo" and "the demos" mean the two early demos (the code both share), "the US demo" the June US demo, "the September demos" (or "the 2004-09 demos") `G8ME01_DEMO2` and `G8MP01_DEMO`, and "every demo" or "all four demos" all of them. "The releases" or "retail" (also "the retail versions", "the retail builds", "the later releases", "later versions") on code under `VERSION >= VERSION_JP` means the release code line, which the September demos build as well: "retail only" there means "not in the early demos". "PAL" on code under `VERSION >= VERSION_DEMO_EU` means the PAL code line, the European demo included.

`tools/check_versions.py` (run by the lint job on every push and pull request) fails if a file in the game code uses the per-version macros, tests an ordered value with `#ifdef`/`defined()` (always true), tests `VERSION` before `version.h` is included, or names a `VERSION_` value that `version.h` does not define (an undefined name is 0 in `#if`, which would make `VERSION == VERSION_DEMO_JP` true everywhere). The library code under `libs/` still tests the per-version macros directly; for it, `configure.py` also defines `VERSION_G8ME01` when building `G8MP01` and both September demos (and `VERSION_G8MP01` for the European demo), and what the two early demos share is written `defined(VERSION_G8ME01_DEMO) || defined(VERSION_G8MJ01_DEMO)`.

Assembly files get the same index as `BUILD_VERSION` through `--defsym` (for example the TRK stubs in `libs/trk/src/TRK_MINNOW_DOLPHIN.a/targsupp.s`).

### Helpers in `include/version.h`

- `VERSION_PICK(jp, us)`: the JP value, or the US value when `VERSION >= VERSION_US` (US, PAL and the September demos). The early demos get the JP value. Used for constants that changed between the releases, such as struct sizes, offsets, counts and literal values.
- `FPS_FRAMES(n)`: an integer frame count. In the US code line it is `n * gp->framerate / 60`, so a count written for 60 Hz becomes the right count at 50 Hz in the European release; in JP and the early demos it is just `n`.
- `FPS_EASE(n)` and `FPS_EASE_D(jp, us)`: the same scaling for easing divisors (`FPS_EASE_D` covers JP sites that were written with a double literal where US writes a float).

`gp->framerate` is set at boot in `src/mario/mariost.c`: always 60 in JP and the early demos, 60 or 50 from the video mode in US, PAL and the September demos (PAL also picks 60 for EURGB60).

## What differs

### JP → US (`G8ME01`)

- **Text.** English text, fonts and text layout. Many message and window routines changed with it (`src/driver/msgdrv.c`, `src/manager/fontmgr.c`, `src/manager/winmgr.c`, the `src/window/` files).
- **Frame rate.** Timers, frame counts and easing go through `FPS_FRAMES`/`FPS_EASE` so that the same code runs at 50 Hz in Europe.
- **Data structures.** Some structs gained members; those members sit inside `#if VERSION >= VERSION_US` in the struct, so field accesses are right in every version. Offsets that moved are written with `VERSION_PICK`.
- **Memory.** The map heap is 670 KiB instead of 660 KiB, and US map allocations take the heap base as a parameter, so battle maps get their own sub-heap (`src/memory.c`, `src/mario/mariost.c`).
- **Bug fixes.** A few JP bugs are fixed, for example the key check in `src/event/evt_mobj.c` (see [KNOWN_GAME_BUGS.md](KNOWN_GAME_BUGS.md)).
- **RELs.** `dig` and `qiz` are not on the US disc.

### US → PAL (`G8MP01`)

- **Five languages** chosen from the console language (English, German, French, Spanish, Italian; Dutch falls back to English), a 50/60 Hz choice with PAL and EURGB60 render modes (`src/mario/mariost.c`), and PAL wording of the system messages (`src/romfont.c`).
- **Battle and story changes** found in the European code, for example an extra event-hit command and a slide-return event id in the battle unit (`include/battle/battle_event_cmd.h`, `include/battle/battle_unit.h`), longer mail scripts (`include/evt/evt_sub.h`), and `sysDebugReport` (`include/system.h`).
- **RELs.** `dig` and `qiz` are back, and `tst.rel`, a developer test REL with test battles, test maps and SGI's GLU tessellator, ships only in this release and the Japanese demo (`rels/tst/`).

### The early demos compared with JP (`G8MJ01_DEMO`, `G8ME01_DEMO`)

- **Kiosk behaviour.** After a minute without input the early demos end the session (the September demos do the same): in the field or in a battle they raise the kiosk timeout flag, which sends the game to the game-over sequence, and in any other sequence they reset (`src/mario/mariost.c`). The retail games raise the same flag after two minutes in the field or a battle, but only the kiosk mode of the show build acts on it. The demo has an extra sequence, `seq_demo` (`src/sequence/seq_demo.c`, listed in `src/sequence/seqdef.c`).
- **Older code.** Many functions are earlier versions of the JP code: the differences of the demo code are marked `VERSION <= VERSION_DEMO_JP` (or `VERSION >= VERSION_JP` for what only the releases and the later demos have) throughout `src/`, the largest group of version conditionals in the tree.
- **Memory.** The smart heap is a fixed 7 MiB block from the default heap (`src/memory.c`).
- **Small-data thresholds.** The retail main executables are compiled with `-sdata 48 -sdata2 6`; the demo's with `-sdata 8 -sdata2 4`. The demo puts no variable over 8 bytes in `.sdata`/`.sbss` (`PadChanMask[4]` of `src/sdk/DEMOPad.c` is in `.data`) and no constant over 4 bytes in `.sdata2` (the 6-byte string `"title"` is in `.rodata`). RELs use `-sdata 0 -sdata2 0` in every version.
- **Precompiled headers.** Main-executable units get the MSL math constants from `include/msl_main.pch` (the `MAIN_PCH` set in `configure.py`); the demo keeps those constants in a different set of units (`MAIN_PCH_DEMO_ADD`), and a few demo units use `include/msl_math.pch`, the math header without the constants (`MATH_PCH_DEMO`).
- **RELs.** The June US demo has six areas: Petal Meadows (`hei`), Petalburg (`nok`), Hooktail Castle (`gon`), the Great Tree (`mri`), Bowser's stage (`kpa`) and the system REL (`sys`).

### The Japanese demo compared with the US demo (`G8MJ01_DEMO`)

The Japanese store demo is the demo code a little after the US demo (it already has the release code in the five places listed [above](#preprocessor-macros)), without the US demo's English text. Compared function by function with relocations masked, 6,890 of its 6,905 main executable functions are identical to the US demo's; where the US demo and JP differ, it follows the US demo in 1,509 functions and JP in 3. The functions that differ are mostly text and kiosk code: the message parser and font setup (`msgAnalize`, `fontmgrTexSetup`), the kiosk loop in `src/mario/mariost.c`, the attract screens (`src/sequence/seq_e3.c`, where the Japanese demo still draws the title's PRESS START with `pressStartGX`, and `seq_logoInit`) and the shop setup. The six RELs the two demos share have the same code; their data differs in a few places (`hei_01`, `kpa_00`, `mri_puni` and `punidrv` of `mri`).

- **RELs.** All 32: JP's 31 and `tst`. Those outside the US demo are close to JP's.
- **What only the US demo has** (`VERSION == VERSION_DEMO_US`, checked against the Japanese demo's objects, which have the JP code in these places): the English font setup (`fontmgrTexSetup`), the message parser without the `HM` icon test (`msgAnalize`), its attract screens (`src/sequence/seq_e3.c`), the logo and E3 file loading at the start of `seq_logoInit`, the ninth row of `_party_max_hp_table` (`src/mario/mario_pouch.c`), the fixed-width `btlevtcmd_ACSuccessEffect`, the shop setup without the prize-list event (`evt_shop_setup`), the trailing word after a script in `src/window/win_main.c`, and in `hei_01` the missing Goombella tip event. Every other demo difference builds the Japanese demo's code as well.
- **Build.** Same small-data thresholds and precompiled-header sets as the US demo. Every unit links from C. `tst.c` registers `tst_nakayama_init_evt`, which this version's `evt_init.c` does not define; the original linker left that reference as 0 with no relocation, and the build reproduces it by dropping the relocation before `dtk rel make` (`config/G8MJ01_DEMO/unresolved_symbols.txt`, see [BUILDING.md](BUILDING.md)).
- **Configuration.** `config/G8MJ01_DEMO` comes from the original linker maps of this demo (`MarioSt.MAP` and one map per REL except `end` and `tst`, which were ported from JP and PAL), so its object boundaries are the original ones. Symbols keep the names the other versions use.

### The September 2004 demos (`G8ME01_DEMO2`, `G8MP01_DEMO`)

Both are kiosk builds of the release code, made a few days after the US release (`Sep 18 2004`, US `Sep  9 2004`) and a few days before the European one (`Sep 23 2004`, PAL `Sep 26 2004`). Compared function by function with relocations masked:

- **`G8ME01_DEMO2` is the US code.** 6,947 of its 6,967 main executable functions have the US code; where US and PAL differ it follows US in all 209 functions, and none of PAL's changes. Its seven RELs have the US code (980 of 980 functions).
- **`G8MP01_DEMO` is the PAL code.** 7,023 of its 7,041 main executable functions have the PAL code; where US and PAL differ it follows PAL in 212 functions and US in 2. It predates three PAL changes: `mot_slit` and `mot_slit_post` (`src/motion/mot_slit.c`), `kpa_cancel_attack_mode` and its call from `jumpstand_evt` (`rels/kpa`), and the longer `shopper_talk_evt` (`src/event/evt_shop.c`). Its seven RELs have the PAL code otherwise.
- **The demo changes** (in both unless noted, the same code in both where US and PAL agree): the kiosk timeout in `marioStMain` and the idle timer start in `marioStInit` (`src/mario/mariost.c`), the logo sequence (`src/sequence/seq_logo.c`) and, in the September US demo only, the attract screens (`src/sequence/seq_e3.c`); that demo also has no progressive-scan screen and picks its video mode from the TV format and the EURGB60 setting as PAL does (`OSGetEuRgb60Mode`, render-mode tables copied in `marioStInit`), the game-over sequence (`seq_gameOverMain`), the status window (`statusWinDisp` and the per-language menu icon tables), the pad input of `makeKey` (`src/system.c`), the level-up help in `btlseqEnd_DispMain`, the drop item of `evt_npc_get_drop_item` (the June demo's code), `Btl_UnitSetup`, and the event data of `gon_01` and `gon_10`. The build date is in `src/R_build.c`.
- **Build.** Retail flags (`-sdata 48 -sdata2 6`, the retail precompiled-header sets). `VERSION_DEMO_US2` and `VERSION_DEMO_EU` come after `VERSION_US`, so both take the US code (`>= VERSION_US`); the European demo also takes PAL's changes (`>= VERSION_DEMO_EU`) except the three it predates (`== VERSION_EU`), and the September US demo the US-only code (`VERSION == VERSION_US || VERSION == VERSION_DEMO_US2`). For the library code `configure.py` defines `VERSION_G8ME01` for both and `VERSION_G8MP01` for the European demo. Every unit links from C; `config/<version>/not_linked.txt` (see [below](#which-units-build-for-which-version)) is empty for both. The main executables need a `force_active` list in `config.yml`, since their seven RELs leave many of the full game's functions and data unreferenced.
- **RELs.** `gon`, `gor`, `hei`, `kpa`, `mri`, `nok` and `tik`; no `sys`.

## REL sets

| Area | JP | US | PAL | June US demo | JP demo | Sept. demos | | Area | JP | US | PAL | June US demo | JP demo | Sept. demos |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| `aaa` | ✓ | ✓ | ✓ | | ✓ | | | `kpa` | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| `aji` | ✓ | ✓ | ✓ | | ✓ | | | `las` | ✓ | ✓ | ✓ | | ✓ | |
| `bom` | ✓ | ✓ | ✓ | | ✓ | | | `moo` | ✓ | ✓ | ✓ | | ✓ | |
| `dig` | ✓ | | ✓ | | ✓ | | | `mri` | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| `dmo` | ✓ | ✓ | ✓ | | ✓ | | | `muj` | ✓ | ✓ | ✓ | | ✓ | |
| `dou` | ✓ | ✓ | ✓ | | ✓ | | | `nok` | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| `eki` | ✓ | ✓ | ✓ | | ✓ | | | `pik` | ✓ | ✓ | ✓ | | ✓ | |
| `end` | ✓ | ✓ | ✓ | | ✓ | | | `qiz` | ✓ | | ✓ | | ✓ | |
| `gon` | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | | `rsh` | ✓ | ✓ | ✓ | | ✓ | |
| `gor` | ✓ | ✓ | ✓ | | ✓ | ✓ | | `sys` | ✓ | ✓ | ✓ | ✓ | ✓ | |
| `gra` | ✓ | ✓ | ✓ | | ✓ | | | `tik` | ✓ | ✓ | ✓ | | ✓ | ✓ |
| `hei` | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | | `tou` | ✓ | ✓ | ✓ | | ✓ | |
| `hom` | ✓ | ✓ | ✓ | | ✓ | | | `tou2` | ✓ | ✓ | ✓ | | ✓ | |
| `jin` | ✓ | ✓ | ✓ | | ✓ | | | `tst` | | | ✓ | | ✓ | |
| `jon` | ✓ | ✓ | ✓ | | ✓ | | | `usu` | ✓ | ✓ | ✓ | | ✓ | |
| | | | | | | | | `win` | ✓ | ✓ | ✓ | | ✓ | |
| | | | | | | | | `yuu` | ✓ | ✓ | ✓ | | ✓ | |
| **Total** | 31 | 29 | 32 | 6 | 32 | 7 | | | | | | | | |

The two September 2004 demos (`G8ME01_DEMO2`, `G8MP01_DEMO`) have the same seven RELs.

Each version's set is the list of REL folders in `config/<version>/` and the lines of `config/<version>/build.sha1` (one per REL plus `MarioSt.dol`). [GLOSSARY.md](GLOSSARY.md#area-codes) says what each area is.

## Which units build for which version

In `configure.py`, each object is declared once as `Matching`: every unit is compiled from C and linked in every version that has it. Which versions have a unit is decided by `config/<version>/splits.txt` alone: a version builds only the units its splits name, so a unit that exists in only some versions (`battle/battle_ufo.c` in PAL, the European demo and both early demos, the `dig` and `qiz` units in JP, PAL and the Japanese demo, everything in `tst` in PAL and the Japanese demo) is simply not built for the others.

Per-version data lives in `config/<version>/`: `config.yml` (the files to split and their hashes), `splits.txt` (which source file owns which address range), `symbols.txt` (every symbol with its address) and `build.sha1`.

## Adding a version difference

See [CONTRIBUTING.md](CONTRIBUTING.md#adding-a-version-difference).
