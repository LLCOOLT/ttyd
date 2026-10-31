// Views of BattleUnit and BattleWork at the older layout offsets the tst REL was built against.
#pragma once

#include "dolphin/types.h"
#include "battle/battle_stage_object.h"

struct BattleWeapon;

// tst.rel was built against older battle headers than the PAL game it ships with, so a few of its units read the
// battle structs at other offsets. These views give those fields their tst offsets.
// - BattleUnit: tst's has no PAL slideReturnEventId (the US layout), so countersetWeapon and the fields after it sit 4 bytes
//   lower (countersetWeapon 0x314, not PAL 0x318).
// - BattleWork: tst's places stageObjectWork 0x2A0 further in, at 0x1837C (PAL and US 0x180DC).
typedef struct TstBattleUnit {
    u8 pad_000[0x308];                      // 0x0, as BattleUnit without slideReturnEventId
    ItemType heldItem;                      // 0x308
    ItemDropData* dropTable;                // 0x30C
    u8 stolenCoins;                         // 0x310
    u8 moveColorLv;                         // 0x311
    u8 moveColorLvDisp;                     // 0x312
    u8 pad_313;                             // 0x313
    struct BattleWeapon* countersetWeapon;  // 0x314
    void (*deleteFunc)(struct BattleUnit*); // 0x318
    struct smartEntry* screenTexBuf;        // 0x31C
} TstBattleUnit;

typedef struct TstBattleWork {
    u8 pad_00000[0x1837C];                 // 0x0, as BattleWork in tst's headers
    BattleStageObjectWork stageObjectWork; // 0x1837C
} TstBattleWork;

#define TST_BATTLE_UNIT(unit) ((TstBattleUnit*)(unit))
#define TST_BATTLE_WORK(work) ((TstBattleWork*)(work))
