# Tools

Scripts for building, checking and reporting. Run them from the repository root. Build steps are in [docs/BUILDING.md](../docs/BUILDING.md).

## configure.py

`configure.py` (in the repository root) writes `build.ninja` and `objdiff.json` for one version. `python configure.py --help` lists every option; the common ones:

| Option | Effect |
|---|---|
| `--version G8MJ01` / `G8ME01` / `G8MP01` / `G8ME01_DEMO` | version to build (default `G8MJ01`) |
| `--map` | also write linker map files |
| `--non-matching` | link units that are equivalent but not matching (for modified builds) |
| `--debug` | build with debug information (not matching) |
| `--warn all` / `off` / `error` | how to treat compiler warnings |
| `--no-progress` | skip the progress report |
| `--build-dir DIR` | build somewhere other than `build/` |
| `--dtk`, `--objdiff`, `--sjiswrap`, `--compilers`, `--binutils`, `--ninja`, `--wrapper` | use tools you already have instead of downloading them |
| `--verbose` | more output, including per-module progress |

`python configure.py progress` prints the progress of the last build and writes its report.

## Scripts

| Script | What it does | Usage |
|---|---|---|
| `tools/project.py` | the build generator behind `configure.py` (from dtk-template): compile and link rules, the hash check, progress | used by `configure.py` |
| `tools/download_tool.py` | downloads the build tools (dtk, objdiff-cli, sjiswrap, compilers, binutils, wibo) | called by the build |
| `tools/transform_dep.py` | converts compiler dependency files to Unix paths for non-Windows builds | called by the build |
| `tools/ninja_syntax.py` | the ninja file writer (from ninja) | used by `tools/project.py` |
| `tools/decompctx.py` | writes `ctx.c`, a single file with every header a source file includes, for the Context box on [decomp.me](https://decomp.me) | `python tools/decompctx.py src/driver/npcdrv.c` |
| `tools/changes_fmt.py` | formats an objdiff-cli report-changes JSON as a list of regressions (and, with `--all`, improvements) | `python tools/changes_fmt.py changes.json [-o out.md] [--all]` |
| `tools/update_readme.py` | refreshes the README badges and the "Detailed progress" tables from each version's `build/<version>/report.json` | build the versions, then `python tools/update_readme.py` |
| `tools/progress_treemap.py` | renders a `report.json` as a self-contained HTML progress page (and optionally `docs/progress.svg`): headline figures, per-category bars and a treemap with one cell per unit | `python tools/progress_treemap.py build/G8MJ01/report.json -o build/progress.html [--svg docs/progress.svg]` |
| `tools/check_versions.py` | checks the version conditions of the game code: `VERSION` compared with the ordered values of `include/version.h`, never configure.py's `VERSION_G8M*` macros, and `version.h` included before the first test. Needs no game files; the lint job runs it | `python tools/check_versions.py [-v]` |
| `tools/check_symbols.py` | lines up each source file's functions across the four versions' `symbols.txt` and `splits.txt` and fails if the same function has different names (known different functions in the same slot are listed in the script). Needs no game files; the lint job runs it | `python tools/check_symbols.py [-v]` (`-v` also lists functions only one version has) |
| `tools/format_check.py` | checks the formatting of `include/`, `src/` and `rels/`: clang-format with `.clang-format` for C code, script blocks indented by nesting, data tables and assert lines left as laid out; skips with a message when clang-format (major version 23) is not installed. The lint job runs it | `python tools/format_check.py [paths...]` (`--write` reformats) |
| `tools/port_symbols.py` | carries one version's `symbols.txt` and `splits.txt` over to another release of the game: pairs functions by their instructions, places data by the references to it, and writes a report of what it could not place. Used to set up a new version's configuration from an existing one | see the usage text at the top of the script |

`tools/progress_treemap.html` is the page template that `tools/progress_treemap.py` fills in.

## ttydasm: script disassembler

`tools/ttydasm/` is a small Rust program that reads a built module and prints a script (an `EVT_BEGIN` array) as script macros, which helps when reading or writing scripts. It reads the JP build (`build/G8MJ01/`), so build that version first.

```sh
cd tools/ttydasm
cargo run --release -- extract -m gor -s gor_00_init_evt     # a script in gor.rel
cargo run --release -- extract -m dol -s evt_bero_info_run   # a script in MarioSt.dol
```

`-m` is the module (`dol` or `MarioSt` for the main executable, otherwise the area code), `-s` the symbol, and `-p` the path to the repository root if you run it from somewhere else (default `../..`).
