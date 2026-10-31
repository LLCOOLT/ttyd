// Battle status effects: the visual effects of statuses on units and the status-change announcement.
#include <dolphin/pad.h>
#include "version.h"
#include "battle/battle_status_effect.h"
#include "battle/battle_unit.h"
#include "battle/battle.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "battle/battle_pad.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include <stdio.h>
#include <string.h>
#include "driver/icondrv.h"
#include "battle/battle_sub.h"
#include "eff/eff_fire.h"
#include "eff/eff_ice.h"
#include "eff/eff_sleep.h"
#include "battle/battle_damage.h"

// StChgMsg.flags: who the pending status message is about.
#define ST_CHG_MSG_FLAG_MARIO 0x1   // Mario
#define ST_CHG_MSG_FLAG_PARTNER 0x2 // a partner on the player's side
#define ST_CHG_MSG_FLAG_OTHER 0x4   // any other unit

#define ST_CHG_MSG(i) ((StChgMsg*)_battleWorkPointer->announce.stChg.msg + (i)) /* cast keeps the 0x18D88 displacement folded into each access */

BOOL BattleStatusChangeAnnouceMain_Unit(BattleUnit* unit);
void BattleStatusChangeMsgSetAnnouce(BattleUnit* unit, s32 index, s32 changed);
void BattleStatusChangeInfoWorkInit(BattleUnit* unit);
static void _st_chg_msg_disp(void);

typedef struct StChgMsgData {
    s8 type;
    const char* name;
    const char* msg1;
    const char* msg0;
} StChgMsgData;

// Status Type Priority Data. The demo defines it first; its .data follows that order (retail keeps it in .sdata).
#if VERSION <= VERSION_DEMO_JP
/**
 * Demo copy of the status announcement order: Charge first, then Poison, Sleep and so on, ending with -1.
 * BattleStatusChangeMsgMain shows pending messages in this order and _get_pri ranks queued changes by it.
 */
s8 _st_pri_data[] = {
    STATUS_CHARGE, //charge is elevated
    STATUS_POISON, //poison is elevated
    STATUS_SLEEP,
    STATUS_STOP,
    STATUS_DIZZY,
    STATUS_CONFUSE,
    STATUS_ELECTRIC,
    STATUS_DODGY,
    STATUS_BURN,
    STATUS_FREEZE,
    STATUS_HUGE,
    STATUS_TINY,
    STATUS_ATTACK_UP,
    STATUS_ATTACK_DOWN,
    STATUS_DEFENSE_UP,
    STATUS_DEFENSE_DOWN,
    STATUS_ALLERGIC,
    STATUS_INVISIBLE,
    STATUS_FAST,
    STATUS_SLOW,
    STATUS_PAYBACK,
    STATUS_HOLD_FAST,
    STATUS_HP_REGEN,
    STATUS_FP_REGEN,
    -1,
};
#endif

/**
 * Message for each status change announcement (the Japanese status name is only a label):
 * msg1 when the status took hold, msg0 when not; only Charge differs ("...But it had no effect!").
 * Ends with type -1.
 */
StChgMsgData _st_chg_msg_data[] = {
    { 4, "どく", "msg_st_chg_poison", "msg_st_chg_poison" },
    { 16, "チャージ", "msg_st_chg_charge", "msg_st_chg_charge3" },
    { 1, "ねむり", "msg_st_chg_sleep", "msg_st_chg_sleep" },
    { 2, "ストップ", "msg_st_chg_stan", "msg_st_chg_stan" },
    { 3, "グルグル", "msg_st_chg_guruguru", "msg_st_chg_guruguru" },
    { 5, "こんらん", "msg_st_chg_confusion", "msg_st_chg_confusion" },
    { 6, "ビリビリ", "msg_st_chg_biribiri", "msg_st_chg_biribiri" },
    { 7, "ヨケヨケ", "msg_st_chg_dodge", "msg_st_chg_dodge" },
    { 8, "ひだるま", "msg_st_chg_fire", "msg_st_chg_fire" },
    { 9, "こおりづけ", "msg_st_chg_freeze", "msg_st_chg_freeze" },
    { 10, "デカデカ", "msg_st_chg_big", "msg_st_chg_big" },
    { 11, "ミニミニ", "msg_st_chg_small", "msg_st_chg_small" },
    { 12, "つよつよ", "msg_st_chg_tuyotuyo", "msg_st_chg_tuyotuyo" },
    { 13, "よわよわ", "msg_st_chg_yowayowa", "msg_st_chg_yowayowa" },
    { 14, "カチカチ", "msg_st_chg_hard", "msg_st_chg_hard" },
    { 15, "フニャフニャ", "msg_st_chg_soft", "msg_st_chg_soft" },
    { 0, "アレルギー", "msg_st_chg_allergy", "msg_st_chg_allergy" },
    { 18, "とうめい", "msg_st_chg_trans", "msg_st_chg_trans" },
    { 19, "はやい", "msg_st_chg_quick", "msg_st_chg_quick" },
    { 20, "のろい", "msg_st_chg_slow", "msg_st_chg_slow" },
    { 21, "しかえし", "msg_st_chg_counter", "msg_st_chg_counter" },
    { 22, "ボムカウンター", "msg_st_chg_bombcounter", "msg_st_chg_bombcounter" },
    { 23, "じわじわＨＰ", "msg_st_chg_reg_hp", "msg_st_chg_reg_hp" },
    { 24, "じわじわＦＰ", "msg_st_chg_reg_fp", "msg_st_chg_reg_fp" },
    { -1, "", "", "" },
};

#if VERSION >= VERSION_JP
//.sdata
// Status Type Priority Data
s8 _st_pri_data[] = {
    STATUS_CHARGE, //charge is elevated
    STATUS_POISON, //poison is elevated
    STATUS_SLEEP,
    STATUS_STOP,
    STATUS_DIZZY,
    STATUS_CONFUSE,
    STATUS_ELECTRIC,
    STATUS_DODGY,
    STATUS_BURN,
    STATUS_FREEZE,
    STATUS_HUGE,
    STATUS_TINY,
    STATUS_ATTACK_UP,
    STATUS_ATTACK_DOWN,
    STATUS_DEFENSE_UP,
    STATUS_DEFENSE_DOWN,
    STATUS_ALLERGIC,
    STATUS_INVISIBLE,
    STATUS_FAST,
    STATUS_SLOW,
    STATUS_PAYBACK,
    STATUS_HOLD_FAST,
    STATUS_HP_REGEN,
    STATUS_FP_REGEN,
    -1,
};
#endif

// local prototypes
static void BSE_Sleep(BattleUnit* unit);
static void BSE_SleepDelete(BattleUnit* unit);
static void BSE_Biribiri(BattleUnit* unit);
static void BSE_BiribiriDelete(BattleUnit* unit);
static void BSE_Fire(BattleUnit* unit);
static void BSE_FireDelete(BattleUnit* unit);
static void BSE_Freeze(BattleUnit* unit);
static void BSE_FreezeDelete(BattleUnit* unit);
static void BSE_Kagegakure(BattleUnit* unit);
static void BSE_KagegakureDelete(BattleUnit* unit);
static s32 _get_pri(s8 type);

/**
 * Status-effect setup for a new unit, called from BtlUnit_Entry;
 * empty in every version (the effect pointers start NULL).
 */
void BattleStatusEffectInit(BattleUnit* unit) {
    ; // stubbed in retail
}

/**
 * Runs every frame for each unit from battle_disp.c:
 * creates, moves or removes the sleep Zs, Electrified sparks, Burn flames,
 * Freeze ice block and the Veil icon to match the unit's current statuses.
 */
void BattleStatusEffectMain(BattleUnit* unit) {
    BSE_Sleep(unit);
    BSE_Biribiri(unit);
    BSE_Fire(unit);
    BSE_Freeze(unit);
    BSE_Kagegakure(unit);
}

/** Removes all of the unit's status effects; called when the unit is deleted from battle. */
void BattleStatusEffectDelete(BattleUnit* unit) {
    BSE_SleepDelete(unit);
    BSE_BiribiriDelete(unit);
    BSE_FireDelete(unit);
    BSE_FreezeDelete(unit);
    BSE_KagegakureDelete(unit);
}

#include "driver/effdrv.h"
// FAKE: local prototype with two extra arguments (eff_spark.h: (s32 type, f32 x, f32 y, f32 z)): BSE_Biribiri passes
// 10 and half the unit width, which effSparkEntry never reads; the target computes and passes them.
EffectEntry* effSparkEntry(s32, s32, f32, f32, f32, f32);
#define EFF_SLEEP(u) ((u)->sleepEff)
#define EFF_SPARK(u) ((u)->sparkEff)

// BSE_Sleep, BSE_SleepDelete, BSE_Biribiri and 1 more size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * While the unit is asleep, keeps a sleep effect (the floating Zs) at the top-right of its body part:
 * half the width across and 0.95 of the height up, scaled by the unit's size (at body height for ceiling units).
 * Deletes it once the unit wakes.
 */
static void BSE_Sleep(BattleUnit* unit) {
    f32 x, y, z;
    f32* wk;
    f32 dx, dy;
    BOOL on = FALSE;

    if (BtlUnit_CheckStatus(unit, STATUS_SLEEP)) {
        on = TRUE;
    }
    if (on) {
        if (EFF_SLEEP(unit) == NULL) {
            EFF_SLEEP(unit) = effSleepEntry(0, 0, -1000.0f, -1000.0f, -1000.0f, 1.0f, 60.0f);
        }
        wk = (f32*)EFF_SLEEP(unit)->userdata;
        BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
        dx = 0.5f * (unit->sizeMultiplier * BtlUnit_GetWidth(unit));
        dy = 0.95f * (unit->sizeMultiplier * BtlUnit_GetHeight(unit));
        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
            dy = 0.0f;
        }
        x += dx;
        y += dy;
        wk[1] = x;
        wk[2] = y;
        wk[3] = z;
    } else {
        BSE_SleepDelete(unit);
    }
}

/** Deletes the unit's sleep effect if it has one. */
static void BSE_SleepDelete(BattleUnit* unit) {
    if (EFF_SLEEP(unit) != NULL) {
        effDelete(EFF_SLEEP(unit));
        EFF_SLEEP(unit) = NULL;
    }
}

/**
 * Biribiri = Electrified.
 * While the unit is Electrified, keeps a spark effect around the middle of its body part (half its width as
 * radius, half its height up, 10 units in front); deletes it when the status ends.
 */
static void BSE_Biribiri(BattleUnit* unit) {
    f32 x, y, z;
    f32* wk;
    f32 dy;
    BOOL on = FALSE;

    if (BtlUnit_CheckStatus(unit, STATUS_ELECTRIC)) {
        on = TRUE;
    }
    if (on) {
        if (EFF_SPARK(unit) == NULL) {
            EFF_SPARK(unit) = effSparkEntry(0, 10, -1000.0f, -1000.0f, -1000.0f, BtlUnit_GetWidth(unit) / 2);
        }
        wk = (f32*)EFF_SPARK(unit)->userdata;
        BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
        dy = unit->sizeMultiplier * (BtlUnit_GetHeight(unit) / 2);
        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
            dy = 0.0f;
        }
        y += dy;
        wk[1] = x;
        wk[2] = y;
        wk[3] = 10.0f + z;
    } else {
        BSE_BiribiriDelete(unit);
    }
}

/** Deletes the unit's Electrified spark effect if it has one. */
static void BSE_BiribiriDelete(BattleUnit* unit) {
    if (EFF_SPARK(unit) != NULL) {
        effDelete(EFF_SPARK(unit));
        EFF_SPARK(unit) = NULL;
    }
}
#pragma optimize_for_size reset

#define EFF_FIRE(u) ((u)->fireEff)
#define EFF_ICE(u) ((u)->iceEff)

// BSE_Fire, BSE_FireDelete, BSE_Freeze and 1 more size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * While the unit is Burned, keeps a flame effect on it at the unit kind's burnFlameOffset (mirrored by facing
 * direction and scaled by size); deletes it when the burn ends.
 */
static void BSE_Fire(BattleUnit* unit) {
    f32 x, y, z;
    f32* wk;
    BOOL on = FALSE;

    if (BtlUnit_CheckStatus(unit, STATUS_BURN)) {
        on = TRUE;
    }
    if (on) {
        if (EFF_FIRE(unit) == NULL) {
            EFF_FIRE(unit) = effFireEntry(0, 0, -1000.0f, -1000.0f, -1000.0f, 1.0f);
        }
        wk = (f32*)EFF_FIRE(unit)->userdata;
        BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
        x += unit->sizeMultiplier * (unit->kindParams->burnFlameOffset.x * (unit->faceDirection >= 0 ? 1.0f : -1.0f));
        y += unit->kindParams->burnFlameOffset.y * unit->sizeMultiplier;
        z += unit->kindParams->burnFlameOffset.z * unit->sizeMultiplier;
        wk[1] = x;
        wk[2] = y;
        wk[3] = z + 5.0f;
    } else {
        BSE_FireDelete(unit);
    }
}

/** Deletes the unit's Burn flame effect if it has one. */
static void BSE_FireDelete(BattleUnit* unit) {
    if (EFF_FIRE(unit) != NULL) {
        effDelete(EFF_FIRE(unit));
        EFF_FIRE(unit) = NULL;
    }
}

/**
 * While the unit is Frozen, keeps an ice-block effect around it,
 * scaled to the smaller of width/20 and height/36 (times the size multiplier)
 * and raised by 20 units per scale step.
 */
static void BSE_Freeze(BattleUnit* unit) {
    f32 x, y, z;
    f32* wk;
    f32 a, b, sc;
    BOOL on = FALSE;

    if (BtlUnit_CheckStatus(unit, STATUS_FREEZE)) {
        on = TRUE;
    }
    if (on) {
        if (EFF_ICE(unit) == NULL) {
            EFF_ICE(unit) = effIceEntry(0, -1, -1000.0f, -1000.0f, -1000.0f, 1.0f);
        }
        wk = (f32*)EFF_ICE(unit)->userdata;
        {
            BattleUnitPart* parts = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
            a = unit->width / 20.0f;
            b = unit->height / 36.0f;
            sc = a <= b ? a : b;
            sc *= unit->sizeMultiplier;
            wk[4] = sc;
            BtlUnit_GetPartsWorldPos(parts, &x, &y, &z);
        }
        wk[1] = x;
        wk[2] = 20.0f * sc + y;
        wk[3] = 10.0f + z;
    } else {
        BSE_FreezeDelete(unit);
    }
}

/**
 * Removes the unit's ice-block effect with effSoftDelete, so instead of vanishing it plays out the rest of its
 * animation and then sags, fades and drips smoke puffs (effIceMain).
 */
static void BSE_FreezeDelete(BattleUnit* unit) {
    if (EFF_ICE(unit) != NULL) {
        effSoftDelete(EFF_ICE(unit));
        EFF_ICE(unit) = NULL;
    }
}

#pragma optimize_for_size reset

/**
 * Kagegakure = hiding in the shadows (Vivian's Veil).
 * While the command menu is up (BATTLE_DISP_FLAG_COMMAND_MENU) and the unit is UNIT_ATTR_VEILED,
 * shows icon 0xA1 (0x99 in the demos) named "_biK_<unitId>" at the unit's body part; removes it otherwise.
 */
static void BSE_Kagegakure(BattleUnit* unit) {
    char name[0x10];
    f32 x, y, z;
    BOOL on = FALSE;

    if ((_battleWorkPointer->dispFlags & BATTLE_DISP_FLAG_COMMAND_MENU) && (unit->attributeFlags & UNIT_ATTR_VEILED)) {
        on = TRUE;
    }
    if (on) {
        if (unit->kageIcon == NULL) {
            sprintf(name, "_biK_%02x", *(s32*)unit);
#if VERSION >= VERSION_US
            iconEntry(name, 0xA1);
#else
            iconEntry(name, 0x99);
#endif
            unit->kageIcon = iconNameToPtr(name);
        }
        BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &x, &y, &z);
        iconSetPos(unit->kageIcon->name, x, y, z + 5.0f);
    } else {
        BSE_KagegakureDelete(unit);
    }
}

/** Deletes the unit's Veil icon if it has one. */
static void BSE_KagegakureDelete(BattleUnit* unit) {
    if (unit->kageIcon != NULL) {
        iconDelete(unit->kageIcon->name);
        unit->kageIcon = NULL;
    }
}

/**
 * Starts the start-of-turn Burn damage animation for a unit;
 * battle_seq.c calls it with active 1 for every living unit whose Burn strength is above 0.
 */
void BSE_TurnFirstProcessEffectEntry(BattleUnit* unit, s16 active) {
    unit->burnDamageFlameState = 1;
    unit->burnDamageFlameActive = active;
}

// BSE_TurnFirstProcessEffectMain size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * Steps the start-of-turn Burn animation each frame:
 * spawns a flame at the unit, pulses its scale between 0.4 and 2.0 for 60 frames,
 * then deletes it and deals 1 damage unless the unit is hidden by BtlUnit_CheckShadowGuard.
 * Returns TRUE while still animating.
 */
BOOL BSE_TurnFirstProcessEffectMain(BattleUnit* unit) {
    BattleUnitPart* part;
    f32 x, y, z;
    f32* work;
    u16 ac;
    u16 st;

    part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
    st = unit->burnDamageFlameState;
    if (st == 0) {
        return FALSE;
    }
    ac = unit->burnDamageFlameActive;
    if (ac == 0) {
        return FALSE;
    }
    switch (ac) {
        case 1:
            switch (st) {
                case 1:
                    unit->burnDamageFlameState = st + 1;
                    unit->burnDamageFlameScale = 1.0f;
                    BtlUnit_GetPartsWorldPos(part, &x, &y, &z);
                    z += 5.0f;
                    unit->burnDamageFlameEff = effFireEntry(0, 0, x, y, z, unit->burnDamageFlameScale);
                    unit->burnDamageFlameAnimTimer = 0;
                    break;
                case 2:
                    work = (f32*)unit->burnDamageFlameEff->userdata;
                    unit->burnDamageFlameAnimTimer++;
                    unit->burnDamageFlameScale = 1.6f * sinfd(unit->burnDamageFlameAnimTimer * 3) + 0.4f;
                    work[9] = unit->burnDamageFlameScale;
                    if (unit->burnDamageFlameAnimTimer >= 60) {
                        unit->burnDamageFlameState++;
                    }
                    break;
                case 3:
                    effDelete(unit->burnDamageFlameEff);
                    unit->burnDamageFlameEff = NULL;
                    unit->burnDamageFlameState = 0;
                    if (!BtlUnit_CheckShadowGuard(unit)) {
                        BattleDamageDirect(-5, unit, NULL, 1, 0, 0x118, 0, 1);
                    }
                case 0:
                default:
                    return FALSE;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
#pragma optimize_for_size reset

// BattleStatusChangeInfoWorkInit size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * Empties the unit's six-entry status-change queue (statusChangeInfo).
 * Called when the unit enters battle, from BtlUnit_ClearStatus and (not in the demos)
 * after the status messages have been shown.
 */
void BattleStatusChangeInfoWorkInit(BattleUnit* unit) {
    s32 i;
    StChgInfo* e = &unit->statusChangeInfo[0];

    for (i = 0; i < 6; i++) {
        StChgInfo* p = &e[i];
        p->type = -1;
        p->strength = 0;
        p->stagger = 0;
        p->stackOffset = 0;
        p->reserved_04 = 0;
    }
}
#pragma optimize_for_size reset

// FAKE: inlining off from here to the end of the file (FAKES.md); without it 11 functions change length, e.g. BattleStatusEffectMain 19 -> 373 instructions
#pragma dont_inline on
/**
 * Priority of a status for the change messages:
 * 24 for the first entry of _st_pri_data (Charge) down to 1 for the last, -1 if the status is not listed.
 * type is a StatusEffectType stored as s8 in _st_pri_data
 */
static s32 _get_pri(s8 type) {
    s8* val;
    s32 priority = 24; // _st_pri_data has 24 entries: the first gets 24, the last 1

    for (val = _st_pri_data;; priority--, val++) {
        if (*val == -1) {
            return -1; // reached end of list
        }
        if (*val == type) {
            return priority;
        }
    }
    return -1;
}

// BattleStatusChangeInfoSetAnnouce size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * Queues a status change on the unit (battle_damage.c calls it when a status is inflicted or changed):
 * inserts it into the six-entry statusChangeInfo list by _get_pri priority,
 * replacing an entry of the same status, then gives each entry a 10-step stagger and a stacking offset.
 * BattleStatusChangeMsgAdjust still reads the queued types; nothing reads the stagger or offsets.
 * Guess: they laid out per-unit popups that BattleStatusChangeAnnouceMain_Unit no longer draws.
 */
void BattleStatusChangeInfoSetAnnouce(BattleUnit* unit, s32 type, s32 strength, s32 changed) {
    StChgInfo* e = &unit->statusChangeInfo[0];
    StChgInfo tmp, swap;
    s8 pri = _get_pri(type);
    s32 i, j, n;
    u8 u, t;

    for (i = 0; i < 6; i++) {
        s32 cur = e[i].type;

        n = _get_pri(cur);
        if (pri >= (s8)n)
            break;
    }
    if (i >= 6)
        return;
    tmp.type = type;
    tmp.strength = strength;
    tmp.changed = changed;
    if (type == e[i].type) {
        e[i] = tmp;
    } else {
        for (; i < 6; i++) {
            swap = e[i];
            e[i] = tmp;
            tmp = swap;
        }
    }
    j = 0;
    n = j;
    t = 0;
    for (i = 0; i < 6; i++) {
        if (e[i].type == -1)
            break;
        e[i].stagger = t;
        e[i].reserved_04 = j;
        t += 10;
        n++;
    }
    if (t == 0)
        goto L3;
    u = 0x50;
    goto Ld;
L3:
    u = 0x3C;
Ld:;
    for (j = n; j >= 0; j--) {
        if (e[j].type != -1) {
            e[j].stackOffset = u;
            u += 10;
        }
    }
}

#pragma optimize_for_size reset
// BattleStatusChangeAnnouceMain, BattleStatusChangeAnnouceMain_Unit size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * Runs the per-unit status announcements for every unit and returns TRUE while any is still showing;
 * since BattleStatusChangeAnnouceMain_Unit is empty it always returns FALSE.
 * Called from the battle sequence alongside BattleStatusChangeMsgMain.
 */
BOOL BattleStatusChangeAnnouceMain(BattleWork* wp) {
    s32 i;
    BOOL ret;
    BattleUnit* unit;

    ret = FALSE;
    for (i = 0; i < BATTLE_UNIT_MAX; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit && BattleStatusChangeAnnouceMain_Unit(unit)) {
            ret = TRUE;
        }
    }
    return ret;
}

/** Per-unit status announcement step; empty in every version, so it never holds up the battle sequence. */
BOOL BattleStatusChangeAnnouceMain_Unit(BattleUnit* unit) {
    return FALSE;
}
#pragma optimize_for_size reset

// BattleStatusChangeMsgWorkInit size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/** Clears the 28 status-change message slots in BattleWork (one per status type) at battle start. */
void BattleStatusChangeMsgWorkInit(void) {
    StChgMsg* msg = ST_CHG_MSG(0);
    s32 i;

    memset(msg, 0, 0x258);
    for (i = 0; i < 28; i++) {
        msg[i].type = -1;
    }
}
#pragma optimize_for_size reset

/**
 * Marks the status-change message for status index as pending and records who it is about:
 * ST_CHG_MSG_FLAG_MARIO, _PARTNER (a partner on the player's side) or _OTHER (any other unit).
 * changed selects msg1 over msg0 (only Charge differs).
 */
void BattleStatusChangeMsgSetAnnouce(BattleUnit* unit, s32 index, s32 changed) {
    StChgMsg* msg = ST_CHG_MSG(index);
    s32 id;

    msg->unitId = unit->unitId;
    msg->type = index;
    msg->timer = 0;
    msg->changed = changed;
    id = unit->currentKind;
    if (id == UNIT_MARIO) {
        msg->flags |= ST_CHG_MSG_FLAG_MARIO;
    } else if (id >= UNIT_GOOMBELLA && id < UNIT_MAX && unit->alliance == 0) {
        msg->flags |= ST_CHG_MSG_FLAG_PARTNER;
    } else {
        msg->flags |= ST_CHG_MSG_FLAG_OTHER;
    }
}
// the rest of this unit is size-optimised, as in the original (the object differs without it)
// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
/**
 * Rebuilds the pending status messages before they are shown:
 * for each status, re-marks it from every living unit whose statusChangeInfo queue holds it,
 * and drops it if no unit does or if its bit is set in the StChgWork mask.
 */
void BattleStatusChangeMsgAdjust(BattleWork* wp) {
    s32 t;
    StChgWork* base;
    s8 i;
    StChgMsg* msg;
    s32 j;
    BattleUnit* unit;
    s32 n, found, k;
    StChgInfo* e;

    base = &wp->announce.stChg;

    for (i = 0; i < 28; i++) {
        t = i;
        msg = &base->msg[t];
        if (msg->type == -1)
            continue;
        msg->flags = 0;
        for (j = 0; j < BATTLE_UNIT_MAX; j++) {
            unit = BattleGetUnitPtr(wp, j);
            if (unit && !BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
                e = &unit->statusChangeInfo[0];
                found = 0;
                k = 0;
                for (n = 0; n < 6; n++) {
                    if (i == e[n].type) {
                        found = 1;
                        break;
                    }
                    k++;
                }
                if (found) {
                    BattleStatusChangeMsgSetAnnouce(unit, t, e[k].changed);
                }
            }
        }
        if (!msg->flags) {
            msg->unitId = -1;
            msg->type = -1;
        } else if (*(s64*)&base->maskHi & (s64)(1 << t)) {
            msg->unitId = -1;
            msg->type = -1;
        }
    }
}

/**
 * Shows the pending status-change message of highest priority, one per call:
 * loads its text (msg_st_chg_*), keeps it up for 90 frames (A or B skips) and registers _st_chg_msg_disp.
 * Returns TRUE while any message is pending, which holds the battle sequence.
 * The retail versions also clear every unit's queue once a message was shown.
 */
BOOL BattleStatusChangeMsgMain(BattleWork* wp) {
    StChgWork* base = &wp->announce.stChg;
    StChgMsg* msg;
    BOOL ret = FALSE;
    s32 i;

    for (i = 0; _st_pri_data[i] != -1; i++) {
        msg = &base->msg[_st_pri_data[i]];
        if (msg->type == -1)
            continue;
        ret = TRUE;
        BattleGetUnitPtr(wp, msg->unitId);
        if (msg->timer) {
            msg->timer--;
            if (BattlePadCheckTrigger((PAD_BUTTON_A | PAD_BUTTON_B))) {
                msg->timer = 0;
            }
            if (!msg->timer) {
                msg->type = -1;
            }
        } else {
            sprintf(base->text, "");
            for (i = 0; i < 28; i++) {
                if (msg->type == _st_chg_msg_data[i].type || _st_chg_msg_data[i].type == -1) {
                    if (msg->changed) {
                        sprintf(base->text, msgSearch(_st_chg_msg_data[i].msg1));
                    } else {
                        sprintf(base->text, msgSearch(_st_chg_msg_data[i].msg0));
                    }
                    break;
                }
            }
            msg->timer = 90;
        }
        dispEntry(CAMERA_2D, 900.0f, 1, (DispCallback)_st_chg_msg_disp, 0);
        break;
    }
#if VERSION >= VERSION_JP
    if (ret) {
        for (i = 0; i < BATTLE_UNIT_MAX; i++) {
            BattleUnit* unit = BattleGetUnitPtr(wp, i);
            if (unit)
                BattleStatusChangeInfoWorkInit(unit);
        }
    }
#endif
    return ret;
}

typedef void (*WakuColByRefFunc)(u16, GXColor*, f32, f32, f32, f32, f32);

/**
 * Draws the current status-change text centred near the top of the screen (y -120) in a white-bordered window
 * sized to the text, 29 units per line.
 */
static void _st_chg_msg_disp(void) {
    StChgWork* st = &_battleWorkPointer->announce.stChg;
    f32 y;
    f32 x;
    u16 width;
    u16 lines;
    GXColor col0;
    width = FontGetMessageWidthLine((const char*)st->text, &lines);
    lines++;
    col0 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    y = 0.0f;
    x = y - (width / 2);
    y = -120.0f;
    // the color is passed by address here (same ABI as by-value GXColor)
    ((WakuColByRefFunc)windowDispGX_Waku_col)(0, &col0, x - 20.0f, ((lines - 1) * 29) + -117.0f, (f32)(width + 40), (f32)(lines * 29 + 1), 10.0f);
    FontDrawStart();
    FontDrawMessage(x, (s32)y + (lines - 1) * 29, (const char*)st->text);
}
