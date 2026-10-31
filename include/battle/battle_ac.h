// Declares the action command manager, its work data and button-icon drawing helpers.
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
    s32 blinkTimer;            // 0x0, frame counter for the icon blink (ac_repeatedly_lv)
    u8 reserved_04[0xC - 0x4]; // 0x4, never accessed
    GXColor color;             // 0xC, icon colour
    s8 colorStep[4];           // 0x10, per-frame colour delta while the icon blinks
    f32 iconX;                 // 0x14, see actionCommandDisp
    f32 iconY;                 // 0x18, see actionCommandDisp
    s32 reserved_1C;           // 0x1C, never read
    s32 slideTimer;            // 0x20, frames of the icon slide in (0..20) / out (40..60)
    s32 iconStep;              // 0x24, step shown by the icon (lst_rc_keep, stick_keep_left), -1 = none
    f32 gaugeRatio;            // 0x28, power gauge fill, 0..1
} BattleACDispParams;

// BattleActions.setupFlags (BattleActionCommandSetup)
enum BattleAcSetupFlags {
    AC_SETUP_FLAG_CONFUSED_AUTO = 0x1, // a confused unit's command plays itself (TOKEN_FLAG_CONFUSED_ACTION)
    AC_SETUP_FLAG_RETRIES = 0x2,       // a failed input may be retried: setupParam counts the tries left
};

// BattleActions.doneFlags
#define AC_DONE_FLAG_FINISHED 0x1 // the command reached its end state (the delete handler forces it otherwise)

typedef struct BattleActions {
    struct BattleUnit* acUnit;       // 0x0
    s32 setupFlags;                  // 0x4, BattleAcSetupFlags (BattleActionCommandSetup)
    s32 setupParam;                  // 0x8, BattleActionCommandSetup setupParam
    s32 acState;                     // 0xC
    BattleACMainCallback maincb;     // 0x10
    BattleACResultCallback resultcb; // 0x14
    DispCallback dispcb;             // 0x18
    BattleACDeleteCallback deletecb; // 0x1C
    s32 defenseResult;               // 0x20
    s32 resultCount;                 // 0x24
    s32 result;                      // 0x28
    s8 baseAcDifficulty;             // 0x2C
    u8 acDifficulty;                 // 0x2D, 0 (easiest) to 6
    s32 doneFlags;                   // 0x30, AC_DONE_FLAG_FINISHED
    u32 acFlags;                     // 0x34, btlevtcmd_AcSetFlag; 0x10 tested in signal timing
    s32 params[8];                   // 0x38, btlevtcmd_AcSetParam/AcSetParamAll/AcGetParam
    s32 outputParams[8];             // 0x58
    s32 gaugeParams[4];              // 0x78, btlevtcmd_AcSetGaugeParam
    s16 countdown;                   // 0x88, per-frame countdown in repeatedly/signal_timing/stick_rotate
    BattleWorkPad pad;               // 0x8C
    u32 seId;                        // 0x288, power gauge SFX id (battle_ac.c)
    f32 seValue;                     // 0x28C, power gauge SFX value
    union {                          // 0x290, gauge display parameters (ac_*.c use their own views)
        BattleACDispParams disp;
        u8 dispData[0x2BC - 0x290];
    };
    u8 work[0x30C - 0x2BC]; // 0x2BC, per-command work (each ac_*.c casts it to its own struct)
} BattleActions;
// The struct ends at 0x30C: the last word of work[] (BattleWork 0x1F98) is used by battleAcMain_PendulumCraneTiming.

void BattleActionCommandManagerInit(BattleWork* wp);
void BattleActionCommandManager(BattleWork* wp);
s32 BattleActionCommandResult(BattleWork* work);
void BattleActionCommandDeclareACResult(BattleWork* work, BattleWeapon* weapon, s32 result);

void BattleActionCommandStart(BattleWork* work);
void BattleActionCommandStop(BattleWork* work);
s32 BattleActionCommandGetDefenceResult(void);
void BattleActionCommandResetDefenceResult(void);
s32 BattleActionCommandGetDifficulty(BattleWork* work);

void BattleActionCommandSetup(BattleWork* work, s32 id, BattleUnit* unit, s32 setupFlags, s32 setupParam);
void BattleActionCommandSetDifficulty(BattleWork* work, BattleUnit* unit, s32 difficulty);
s32 BattleActionCommandGetPrizeLv(BattleWork* work, BattleUnit* unit, s32 lv);
void BattleAcGaugeSeInit(void);
void BattleAcGaugeSeUpdate(f32 value);
void BattleAcGaugeSeDelete(void);
s32 BattleActionCommandCheckDefence(BattleUnit* unit, BattleWeapon* weapon);
u16 BattleACGetButtonIcon(s32 button, s32 pressed);
void BattleAcDrawGauge(s32 x, s32 y, s32 width, f32 ratio, s32 level, s32 a, s32 b, s32 c, s32 flags);
