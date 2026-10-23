#pragma once

#include <dolphin/types.h>
#include "battle/battle_database_common.h"
#include "battle/battle_pad.h"
#include "driver/dispdrv.h"

typedef struct BattleWork BattleWork;

typedef s32 (*BattleACMainCallback)(BattleWork* work);
typedef s32 (*BattleACResultCallback)(BattleWork* work);
typedef void (*BattleACDeleteCallback)(BattleWork* work);

typedef struct BattleACDispParams {
    u8 pad_00[0xC - 0x0];           // 0x0, no named access
    GXColor color;                  // 0xC, icon colour
    u8 pad_10[0x14 - 0x10];         // 0x10, no named access
    f32 iconX;                      // 0x14, see actionCommandDisp
    f32 iconY;                      // 0x18, see actionCommandDisp
    u8 slideTimerBase[0x20 - 0x1C]; // 0x1C, only used as slideTimerBase[4] == slideTimer (codegen view in ac_air_gauge/ac_power_gauge_lv)
    s32 slideTimer;                 // 0x20, frames of the icon slide in (0..20) / out (40..60)
    u8 pad_24[0x28 - 0x24];         // 0x24, no named access
    f32 gaugeRatio;                 // 0x28, power gauge fill, 0..1
} BattleACDispParams;

typedef struct BattleActions {
    struct BattleUnit* mAcUnit;      // 0x0
    s32 setupFlags;                  // 0x4, BattleActionCommandSetup a4; bit0: auto-play while confused
    s32 setupParam;                  // 0x8, BattleActionCommandSetup a5
    s32 mAcState;                    // 0xC
    BattleACMainCallback maincb;     // 0x10
    BattleACResultCallback resultcb; // 0x14
    DispCallback dispcb;             // 0x18
    BattleACDeleteCallback deletecb; // 0x1C
    s32 mDefenseResult;              // 0x20
    s32 mResultCount;                // 0x24
    s32 result;                      // 0x28
    s8 mBaseAcDifficulty;            // 0x2C
    s8 mAcDifficulty;                // 0x2D
    u8 pad_2E[2];                    // 0x2E, never accessed
    s32 doneFlags;                   // 0x30, bit 1: AC finished (delete handler forces the end state otherwise)
    u32 acFlags;                     // 0x34, btlevtcmd_AcSetFlag; 0x10 tested in signal timing
    s32 params[8];                   // 0x38, btlevtcmd_AcSetParam/AcSetParamAll/AcGetParam
    u32 outputParams[8];             // 0x58
    s32 gaugeParams[4];              // 0x78, btlevtcmd_AcSetGaugeParam
    s16 countdown;                   // 0x88, per-frame countdown in repeatedly/signal_timing/stick_rotate
    u8 pad_8A[0x8C - 0x8A];          // 0x8A, never accessed
    BattleWorkPad pad;               // 0x8C
    u32 seId;                        // 0x288, power gauge SFX id (battle_ac.c)
    f32 seValue;                     // 0x28C, power gauge SFX value
    union {                          // 0x290, gauge display parameters (ac_*.c use their own views)
        BattleACDispParams disp;
        u8 dispData[0x2BC - 0x290];
    };
    u8 work[0x30C - 0x2BC];          // 0x2BC, per-command work (each ac_*.c casts it to its own struct)
} BattleActions;
// NB: 0x308 is as far as I can pin to this struct (0x1F98 in battleAcMain_PendulumCraneTiming, TODO?)

void BattleActionCommandManagerInit(BattleWork* wp);
void BattleActionCommandManager(BattleWork* wp);
s32 BattleActionCommandResult(BattleWork* work);
void BattleActionCommandDeclareACResult(BattleWork* work, BattleWeapon* weapon, s32 result);

void BattleActionCommandStart(BattleWork* work);
void BattleActionCommandStop(BattleWork* work);
s32 BattleActionCommandGetDefenceResult(void);
void BattleActionCommandResetDefenceResult(void);
s8 BattleActionCommandGetDifficulty(BattleWork* work);
