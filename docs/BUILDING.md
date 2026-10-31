# Building

This page covers everything needed to build the five supported versions and check them against the originals. For a one-version quick start, see the [README](../README.md#quick-build).

## Versions

| `--version` | Game | What goes in `orig/<version>/` | Build output | Check |
|---|---|---|---|---|
| `G8MJ01` (default) | Japan, Rev 0 | the disc image | `MarioSt.dol` + 31 RELs | `32 files OK` |
| `G8ME01` | North America, Rev 0 | the disc image | `MarioSt.dol` + 29 RELs | `30 files OK` |
| `G8MP01` | Europe, Rev 0 | the disc image | `MarioSt.dol` + 32 RELs (with `tst.rel`) | `33 files OK` |
| `G8ME01_DEMO` | US demo, June 2004 | `zz_PaperMario2_game.tgc` from the Interactive Multi-Game Demo Disc Version 17 (USA) | `MarioSt.dol` + 6 RELs | `7 files OK` |
| `G8MJ01_DEMO` | Japanese store demo, 2004 | `PaperMarioRPG.tgc` from Gekkan Nintendo Tentou Demo 2004.7.1 (Japan) | `MarioSt.dol` + 32 RELs (with `tst.rel`) | `33 files OK` |

The expected hashes are in `config/<version>/build.sha1`; the counts above are the number of lines in each of those files. [VERSIONS.md](VERSIONS.md) lists which RELs each version has.

## Dependencies

### Windows

Native tooling is recommended; WSL and msys2 are not needed. (Under WSL, objdiff gets no filesystem notifications, so automatic rebuilds do not work.)

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%` (also available from the [Microsoft Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K)).
- Install [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`, or `pip install ninja` and run it as `python -m ninja`.

### macOS

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages): `brew install ninja`
- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine): `brew install --cask --no-quarantine gcenx/wine/wine-crossover`

After an OS upgrade, if macOS says `Wine Crossover.app` is unverified, unquarantine it:

```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

### Linux

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- On x86 and x86_64, [wibo](https://github.com/decompals/wibo), a minimal wrapper for 32-bit Windows programs, is downloaded and used automatically. On other platforms, install Wine from your package manager.

### Downloaded on the first build

The first `configure.py` + `ninja` needs an internet connection. It downloads into `build/`, at the versions pinned in `configure.py`: [decomp-toolkit](https://github.com/encounter/decomp-toolkit) (`dtk`), [objdiff-cli](https://github.com/encounter/objdiff), [sjiswrap](https://github.com/encounter/sjiswrap), the Metrowerks CodeWarrior compilers, GNU binutils for PowerPC and, on Linux, wibo. Later builds reuse them. [THIRD_PARTY.md](THIRD_PARTY.md#build-time-tools) says what each is for. If you already have these tools, pass their paths instead (`--dtk`, `--objdiff`, `--sjiswrap`, `--compilers`, `--binutils`, `--wrapper`; see [tools/README.md](../tools/README.md#configurepy)).

## Game files

The disc image can be ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ or TGC. Put one file per version folder:

- `orig/G8MJ01/`: the Japanese disc.
- `orig/G8ME01/`: the North American disc.
- `orig/G8MP01/`: the European disc. This release is the only one that ships the developer test REL `files/rel/tst.rel`; nothing extra is needed, it is read from the disc.
- `orig/G8ME01_DEMO/`: the demo is not a disc of its own. It is the file `zz_PaperMario2_game.tgc` inside the Interactive Multi-Game Demo Disc Version 17 (USA). Extract that file from the demo disc (for example in Dolphin: right-click the demo disc, **Properties → Filesystem**, right-click `zz_PaperMario2_game.tgc`, **Extract File**) and copy it into `orig/G8ME01_DEMO/`. Do not put the whole demo disc image there.
- `orig/G8MJ01_DEMO/`: the same for the Japanese store demo: the file `files/local/tgc/PaperMarioRPG.tgc` inside Gekkan Nintendo Tentou Demo 2004.7.1 (Japan). Extract it the same way and copy it into `orig/G8MJ01_DEMO/`.

On the first build, decomp-toolkit extracts `sys/main.dol` and `files/rel/*.rel` from the image into the same folder. After that the image can be deleted to save space. Instead of an image, you can also provide an already extracted `sys/main.dol` and `files/rel/` directly.

Game files are ignored by git (`orig/*/*` in `.gitignore`); never commit them.

## Building

```sh
python configure.py --version G8ME01   # or G8MJ01 (the default), G8MP01, G8ME01_DEMO, G8MJ01_DEMO
ninja
```

`configure.py` writes `build.ninja` and `objdiff.json` for the chosen version. `ninja` compiles, links, and ends by checking every output against `config/<version>/build.sha1`. A matching build reports `N files OK` with N from the table above. To run only the check again:

```sh
ninja build/G8ME01/ok
```

Outputs, per version in its own folder (`build/G8MJ01/`, `build/G8ME01/`, `build/G8MP01/`, `build/G8ME01_DEMO/`, `build/G8MJ01_DEMO/`):

- `build/<version>/MarioSt.dol`: the main executable (`sys/main.dol` on the disc).
- `build/<version>/<area>/<area>.rel`: one REL per area (`aaa.rel`, `aji.rel`, ...), the files in `files/rel/` on the disc.
- `build/<version>/report.json`: the objdiff progress report, written by `ninja` (or `ninja progress`).

`python configure.py --map` also writes linker map files.

Each REL is linked into a partially linked module (`build/<version>/<area>/<area>.plf`), and `dtk rel make` turns all of them into RELs at once. One REL needs a step in between: the Japanese demo's `tst.rel` references `tst_nakayama_init_evt`, which that version does not define, and the original linker left the reference as 0 with no relocation, which `dtk rel make` cannot produce from an undefined symbol. For that REL, the linker writes `tst.linked.plf`, and `tools/drop_relocations.py` copies it to `tst.plf` without the relocations against the symbols in `config/G8MJ01_DEMO/unresolved_symbols.txt`. `configure.py` sets this up through `config.rel_dropped_relocations`; no other version or REL uses it.

### Switching versions and building all five

The version folders sit side by side, so switching is just re-running `configure.py`:

```sh
for v in G8MJ01 G8ME01 G8MP01 G8ME01_DEMO G8MJ01_DEMO; do
    python configure.py --version $v && ninja || break
done
```

Every change must keep all five builds at their `N files OK` (see [CONTRIBUTING.md](CONTRIBUTING.md#the-five-version-check)). Only the versions whose discs you have can be checked locally.

## Running a build

An unmodified build is byte-identical to the original files, so it plays exactly like your disc. To try a modified build, give an extracted copy of the game your built files and boot that copy in [Dolphin](https://dolphin-emu.org/):

1. In Dolphin, right-click the game, choose **Properties → Filesystem**, right-click the disc and choose **Extract Entire Disc** into an empty folder. This gives a `sys/` folder and a `files/` folder.
2. Replace `sys/main.dol` with `build/<version>/MarioSt.dol`.
3. Replace each `files/rel/<area>.rel` you changed with `build/<version>/<area>/<area>.rel`.
4. In Dolphin, choose **File → Open** and select `sys/main.dol` in that folder. Dolphin boots the extracted folder as a disc.

Keep your original disc image unchanged and work on the extracted copy. After an edit, the hash check no longer reports all files OK: the changed outputs differ from the originals, which is expected for a modified build. The check only says whether the build is still identical to the original game.

**Android.** The compilers are Windows programs, so build on a computer, then copy the whole extracted folder (with its `sys/` and `files/`) to the device and, in Dolphin for Android, add its parent folder to the game list or open `sys/main.dol` directly. These Android steps have not been tested yet.

## Diffing with objdiff

After a build, `objdiff.json` exists in the project root. Download [objdiff](https://github.com/encounter/objdiff/releases), set **Project directory** in the project settings, and the configuration loads automatically. Select an object in the left sidebar to compare it with the original. Changes to sources, headers, `configure.py`, `splits.txt` or `symbols.txt` rebuild automatically.

![objdiff](../assets/objdiff.png)

`objdiff.json` describes the version last configured; re-run `configure.py --version ...` to diff another one.

## Troubleshooting

- **A file fails the hash check on an unmodified tree.** Check that the disc is the right version and revision (Rev 0 for the three releases) and that `--version` matches the folder you put it in. For the US demo, check that `orig/G8ME01_DEMO/` holds `zz_PaperMario2_game.tgc` (or its extracted files), and for the Japanese demo that `orig/G8MJ01_DEMO/` holds `PaperMarioRPG.tgc`, not the whole demo disc.
- **Two builds at once.** `build.ninja`, `objdiff.json` and ninja's own log belong to the last `configure.py` run in that checkout. Do not run two `ninja` processes, or `configure.py` while `ninja` runs, in the same checkout; build the versions one after another, or use a separate clone or `git worktree` for each parallel build.
- **Japanese text in sources.** Sources are UTF-8 and may contain Japanese text (strings, comments). The compilers read Shift-JIS, so the build runs them through sjiswrap, which converts on the fly. Keep files UTF-8; an editor that re-saves a file in another encoding changes the bytes of its strings.
- **"wine: command not found" or the compilers do not start** (macOS, non-x86 Linux): install Wine as above, or pass a wrapper with `--wrapper`.
- **No internet on the first build.** Copy the `build/tools`, `build/compilers` and `build/binutils` folders from another checkout, or pass the tool paths to `configure.py`.
