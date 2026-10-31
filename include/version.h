// VERSION and VERSION_PICK: selects the demo, JP, US or EU code and data from one source tree.
#pragma once

// Building one source tree for seven releases
//
// configure.py defines one VERSION_<id> macro for the version being built (and BUILD_VERSION, its index in
// configure.py's VERSIONS list). This header turns that into VERSION, one of seven ordered values:
//
//   VERSION_DEMO_US   2004-06 US demo (G8ME01_DEMO): the pre-final JP code with English text.
//   VERSION_DEMO_JP   2004 Japanese store demo (G8MJ01_DEMO): the same pre-final code, a little later. In five
//                     places it already has the release code where the US demo has the older one (evt_shop's
//                     a_shop_keihin event, hei_01's Goombella tip event, btlevtcmd_ACSuccessEffect, the 8-row
//                     _party_max_hp_table, the US demo's reset OSReport in mariost.c).
//   VERSION_JP        Japanese release (G8MJ01). The base: code outside every version block is the JP code.
//   VERSION_US        US release (G8ME01).
//   VERSION_DEMO_US2  2004-09 US demo (G8ME01_DEMO2), built from the US release code.
//   VERSION_DEMO_EU   2004-09 European demo (G8MP01_DEMO), built from the PAL code before its last fixes.
//   VERSION_EU        European release (G8MP01). It is built from the US code, so everything the US release
//                     changed applies to it as well.
//
// The order follows the code's history (the demos, JP, US localisation, PAL on top of US), so a range test says
// which line of the code a block belongs to:
//   US, both 2004-09 demos and PAL  #if VERSION >= VERSION_US
//   JP and both early demos         #if VERSION <= VERSION_JP
//   both early demos                #if VERSION <= VERSION_DEMO_JP
//   the releases and later demos    #if VERSION >= VERSION_JP
//   JP only                         #if VERSION == VERSION_JP
//   PAL and the EU demo             #if VERSION >= VERSION_DEMO_EU
//   PAL only                        #if VERSION == VERSION_EU  (what the EU demo predates)
//   all but PAL and the EU demo     #if VERSION < VERSION_DEMO_EU
//   US and the 2004-09 US demo      #if VERSION == VERSION_US || VERSION == VERSION_DEMO_US2
//   June US demo only               #if VERSION == VERSION_DEMO_US  (mostly its English text)
//   all but the June US demo        #if VERSION != VERSION_DEMO_US
//   all but JP                      #if VERSION != VERSION_JP
//   June US demo, US onwards        #if VERSION == VERSION_DEMO_US || VERSION >= VERSION_US  (where the June
//                                   US demo already has the US localisation)
// configure.py's per-version macros (VERSION_G8MJ01, VERSION_G8ME01, VERSION_G8MP01, VERSION_G8ME01_DEMO,
// VERSION_G8MJ01_DEMO, VERSION_G8ME01_DEMO2, VERSION_G8MP01_DEMO; PAL and both 2004-09 demos also define
// VERSION_G8ME01, the EU demo VERSION_G8MP01 too) are read only here and in the library code under libs/.
// tools/check_versions.py fails if the game code (src/, rels/, include/) uses them, or tests VERSION before
// including this header.
//
// For a single value that differs between JP and US, use VERSION_PICK below; for frame counts and easing that
// the US code scales by the frame rate, FPS_FRAMES and FPS_EASE. Wrap only what differs (see docs/VERSIONS.md
// and docs/CONTRIBUTING.md).

#define VERSION_DEMO_US 0  // G8ME01_DEMO, 2004-06 US demo: pre-final JP code with English text
#define VERSION_DEMO_JP 1  // G8MJ01_DEMO, Japanese store demo: the same code, a little later
#define VERSION_JP 2       // G8MJ01
#define VERSION_US 3       // G8ME01
#define VERSION_DEMO_US2 4 // G8ME01_DEMO2, 2004-09 US demo: US code
#define VERSION_DEMO_EU 5  // G8MP01_DEMO, 2004-09 European demo: PAL code
#define VERSION_EU 6       // G8MP01, built from the US code

// The 2004-09 demos also define their release's macros, so they are tested first.
#if defined(VERSION_G8MP01_DEMO)
#define VERSION VERSION_DEMO_EU
#elif defined(VERSION_G8ME01_DEMO2)
#define VERSION VERSION_DEMO_US2
#elif defined(VERSION_G8MJ01_DEMO)
#define VERSION VERSION_DEMO_JP
#elif defined(VERSION_G8ME01_DEMO)
#define VERSION VERSION_DEMO_US
#elif defined(VERSION_G8MP01)
#define VERSION VERSION_EU
#elif defined(VERSION_G8ME01)
#define VERSION VERSION_US
#else
#define VERSION VERSION_JP
#endif

// VERSION_PICK(jp, us): the JP value (also the early demos'), or the US value (also PAL's and the 2004-09 demos').
#if VERSION >= VERSION_US
#define VERSION_PICK(jp, us) (us)
#else
#define VERSION_PICK(jp, us) (jp)
#endif

// FPS_EASE(n): easing divisor. US scales it by the frame rate (gp->framerate / 60); JP uses n as is.
// Needs mario/mariost.h for gp.
#if VERSION >= VERSION_US
#define FPS_EASE(n) ((n) * gp->framerate / 60.0f)
#else
#define FPS_EASE(n) (n)
#endif

// FPS_EASE_D(jp, us): for JP sites written with a double literal (8.0) that US writes as a float (8.0f).
// Same argument order as VERSION_PICK(jp, us).
#if VERSION >= VERSION_US
#define FPS_EASE_D(jp, us) FPS_EASE(us)
#else
#define FPS_EASE_D(jp, us) (jp)
#endif

// FPS_FRAMES(n): integer frame count. US scales it to the frame rate (n * gp->framerate / 60).
#if VERSION >= VERSION_US
#define FPS_FRAMES(n) ((n) * gp->framerate / 60)
#else
#define FPS_FRAMES(n) (n)
#endif
