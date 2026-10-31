// Script commands for the battle stage: stage and audience darkness, stage lights.
#include "evt/evt_batstage.h"
#include "battle/battle.h"
#include "manager/evtmgr_cmd.h"
#include <dolphin/mtx.h>
#include "battle/battle_stage.h"
// FAKE: evt_batstage.c calls BattleStageSetStgDarkBase through this prototype (the types it was compiled with) instead of the one in battle/battle_stage.h; same registers, behaviour-identical.
typedef void (*BattleStageSetStgDarkBaseS32Fn)(u8, s32, s32);
// FAKE: evt_batstage.c calls BattleStageSetStgDark through this prototype (the types it was compiled with) instead of the one in battle/battle_stage.h; same registers, behaviour-identical.
typedef void (*BattleStageSetStgDarkS32Fn)(u8, s32, s32);
// FAKE: evt_batstage.c calls BattleStageSetAudDarkBase through this prototype (the types it was compiled with) instead of the one in battle/battle_stage.h; same registers, behaviour-identical.
typedef void (*BattleStageSetAudDarkBaseS32Fn)(u8, s32, s32);
// FAKE: evt_batstage.c calls BattleStageSetAudDark through this prototype (the types it was compiled with) instead of the one in battle/battle_stage.h; same registers, behaviour-identical.
typedef void (*BattleStageSetAudDarkS32Fn)(u8, s32, s32);
// FAKE: evt_batstage.c calls BattleStageReturnStgDarkBase through this prototype (the types it was compiled with) instead of the one in battle/battle_stage.h; same registers, behaviour-identical.
typedef void (*BattleStageReturnStgDarkBaseS32Fn)(s32, s32);
// FAKE: evt_batstage.c calls BattleStageReturnAudDarkBase through this prototype (the types it was compiled with) instead of the one in battle/battle_stage.h; same registers, behaviour-identical.
typedef void (*BattleStageReturnAudDarkBaseS32Fn)(s32, s32);

/**
 * Fades the battle stage's darkness: args are the darkness level (0-255), the fade time in frames and a mode.
 * Used by the battle-end and Showstopper (sac_suki) scripts.
 */
USER_FUNC(evt_batstage_set_stg_dark) {
    EvtWord* args = event->args;
    u8 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    s32 c = evtGetValue(event, args[2]);
    ((BattleStageSetStgDarkS32Fn)BattleStageSetStgDark)(a, b, c);
    return EVT_RETURN_DONE;
}

/** Sets the stage's base darkness (the level evt_batstage_return_stg_dark_base fades back to): level, frames, mode. */
USER_FUNC(evt_batstage_set_stg_dark_base) {
    EvtWord* args = event->args;
    u8 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    s32 c = evtGetValue(event, args[2]);
    ((BattleStageSetStgDarkBaseS32Fn)BattleStageSetStgDarkBase)(a, b, c);
    return EVT_RETURN_DONE;
}

/** Fades the stage darkness back to its base level; args are the fade time in frames and a mode. */
USER_FUNC(evt_batstage_return_stg_dark_base) {
    EvtWord* args = event->args;
    s32 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    ((BattleStageReturnStgDarkBaseS32Fn)BattleStageReturnStgDarkBase)(a, b);
    return EVT_RETURN_DONE;
}

/** Fades the audience's darkness: args are the darkness level (0-255), the fade time in frames and a mode. */
USER_FUNC(evt_batstage_set_aud_dark) {
    EvtWord* args = event->args;
    u8 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    s32 c = evtGetValue(event, args[2]);
    ((BattleStageSetAudDarkS32Fn)BattleStageSetAudDark)(a, b, c);
    return EVT_RETURN_DONE;
}

/** Sets the audience's base darkness level (restored by evt_batstage_return_aud_dark_base): level, frames, mode. */
USER_FUNC(evt_batstage_set_aud_dark_base) {
    EvtWord* args = event->args;
    u8 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    s32 c = evtGetValue(event, args[2]);
    ((BattleStageSetAudDarkBaseS32Fn)BattleStageSetAudDarkBase)(a, b, c);
    return EVT_RETURN_DONE;
}

/** Fades the audience darkness back to its base level; args are the fade time in frames and a mode. */
USER_FUNC(evt_batstage_return_aud_dark_base) {
    EvtWord* args = event->args;
    s32 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    ((BattleStageReturnAudDarkBaseS32Fn)BattleStageReturnAudDarkBase)(a, b);
    return EVT_RETURN_DONE;
}

/**
 * Spotlights the acting unit for an Appeal: dims stage and audience to 140
 * and aims up to three grey "sys_activeUnit_N" lights at it (arg 1: only the third, in white).
 * Paired with ..._player_off.
 */
USER_FUNC(evt_batstage_light_set_player_on) {
    EvtWord* args = event->args;
    BattleWork* bw = _battleWorkPointer;
    s32 sel = evtGetValue(event, *args++);
    s32 i;
    s32 idx;
    char names[3][32] = {"sys_activeUnit_1", "sys_activeUnit_2", "sys_activeUnit_3"};
    Vec pos[3] = {{100.0f, 250.0f, 70.0f}, {-300.0f, 250.0f, 70.0f}, {-120.0f, 250.0f, -70.0f}};
    Vec tg[3] = {{100.0f, 0.0f, -70.0f}, {-300.0f, 0.0f, -70.0f}, {-120.0f, 0.0f, -70.0f}};
    Vec tu[3] = {{15.0f, 0.0f, 15.0f}, {-15.0f, 0.0f, 15.0f}, {0.0f, 0.0f, -15.0f}};
    Vec upv[3] = {{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}};
    u8 col[3][3] = {{120, 120, 120}, {120, 120, 120}, {120, 120, 120}};
    u8 en[3] = {0, 0, 0};
    u8 en2[4] = {0, 0, 0, 0}; // FAKE: unused; its zero initialiser template stays in the unit's data

    switch (sel) {
        case 1:
            en[2] = 1;
            col[2][0] = 255;
            col[2][1] = 255;
            col[2][2] = 255;
            break;
        default:
            en[0] = 1;
            en[1] = 1;
            en[2] = 1;
            break;
    }
    for (i = 0; i < 3; i++) {
        if (en[i]) {
            idx = BattleStageGetLightNumberByName(names[i]);
            if (idx == -1) {
                idx = BattleStageSysLightEntry(names[i]);
            }
            BattleStageLightSetLightColor(idx, col[i][0], col[i][1], col[i][2], 30, 0);
            BattleStageLightSetWidth(idx, 120, 1, 0);
            BattleStageLightSetPosition(idx, pos[i].x, pos[i].y, pos[i].z, 0, 0);
            BattleStageLightSetUpVec(idx, upv[i].x, upv[i].y, upv[i].z, 0, 0);
            BattleStageLightSetTarget(idx, tg[i].x, tg[i].y, tg[i].z, 0, 0);
            BattleStageLightSetTargetByUnit(idx, bw->activeUnitId, tu[i].x, tu[i].y, tu[i].z, 30, 5);
        }
    }
    BattleStageSetStgDark(140, 30, 0);
    BattleStageSetAudDark(140, 0, 0);
    return EVT_RETURN_DONE;
}

/**
 * Undoes evt_batstage_light_set_player_on: restores stage and audience darkness
 * and releases the three sys_activeUnit spotlights over 30 frames.
 */
USER_FUNC(evt_batstage_light_set_player_off) {
    s32 idx;
    BattleStageReturnAudDarkBase(0, 0);
    BattleStageReturnStgDarkBase(30, 0);
    idx = BattleStageGetLightNumberByName("sys_activeUnit_1");
    if (idx != -1) {
        BattleStageLightRelease(idx, 30, 0);
    }
    idx = BattleStageGetLightNumberByName("sys_activeUnit_2");
    if (idx != -1) {
        BattleStageLightRelease(idx, 30, 0);
    }
    idx = BattleStageGetLightNumberByName("sys_activeUnit_3");
    if (idx != -1) {
        BattleStageLightRelease(idx, 30, 0);
    }
    return EVT_RETURN_DONE;
}
