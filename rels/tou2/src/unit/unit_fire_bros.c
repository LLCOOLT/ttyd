// unit_fire_bros: Fire Bro, battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "system.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"
#include "evt/evt_sub.h"

// Unit work slots of this unit (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_FIRE_BROS_THROWN = 0,   // fireballs thrown so far in the barrage (nagemakuri) attack
    UW_FIRE_BROS_FINISHED = 1, // fireballs whose flight has finished (fire_move_event counts them)
};

BattleUnitKind unit_fire_bros;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[7];
BattleWeapon weapon_fire_bros_attack;
BattleWeapon weapon_fire_bros_renzoku_attack;
BattleWeapon weapon_fire_bros_nagemakuri_attack;
static EvtWord init_event[21];
static EvtWord damage_event[10];
static EvtWord attack_event[92];
static EvtWord normal_attack_event[125];
static EvtWord renzoku_attack_event[141];
static EvtWord nagemakuri_attack_event[316];
extern EvtWord nagemakuri_judge_last_attack_event[];
static EvtWord wait_event[6];

// dont_inline: MWCC would inline this function into its callers; the original calls it (checked by removing it).
#pragma dont_inline on
/**
 * Advances the weapon target list to the next target and returns its unit and part index,
 * or -1 and 0 at the end of the list.
 */
static void fire_bros_get_next_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;

    wt->currentTarget++;
    if (wt->currentTarget < wt->numTargets) {
        BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];
        *unitIdx = target->unitIdx;
        *partIdx = target->partIdx;
    } else {
        *unitIdx = -1;
        *partIdx = 0;
    }
}
#pragma dont_inline reset

// dont_inline: MWCC would inline this function into its callers; the original calls it (checked by removing it).
#pragma dont_inline on
/** Returns the unit and part index of the weapon target currently selected in the target list. */
static void fire_bros_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}
#pragma dont_inline reset

/**
 * Script helper for the Fire Bro's throwing barrage (nagemakuri):
 * collects the possible targets and writes five random (unit, part) pairs, one per fireball,
 * into the script variables passed as arguments.
 */
static USER_FUNC(fire_bros_nagemakuri_set_target) {
    EvtWord* args = event->args;
    s32 unitIdx[20];
    s32 partIdx[20];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    fire_bros_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        fire_bros_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}

/**
 * Unit data of the Fire Bro: 7 HP and level 20, with its parts, status vulnerability, init event and event
 * data table.
 */
BattleUnitKind unit_fire_bros = {
    58,
    "btl_un_fire_bros",
    7,
    0,
    1,
    1,
    20,
    0,
    2,
    70,
    2,
    50,
    9999,
    36,
    44,
    3,
    44,
    0.0f,
    22.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    0.0f,
    10.0f,
    28.0f,
    0.0f,
    0.0f,
    22.0f,
    0.0f,
    36.0f,
    44.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_FIREB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    7,
    parts,
    init_event,
    data_table,
};

#if VERSION <= VERSION_DEMO_JP
/**
 * Defence of the Fire Bro: 1 against normal, ice, explosion and electric hits;
 * immune to fire (defence 99 cancels the hit).
 */
static BattleUnitDefense defence = {{1, 99, 1, 1, 1}};
#else
/** Defense of the Fire Bro against normal, fire, ice, explosion and electric attacks: 1, 1, 1, 1, 1. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};
#endif

#if VERSION <= VERSION_DEMO_JP
/** Damage-type reactions of the Fire Bro: immune to fire. */
static BattleUnitDefenseAttr defence_attr = {{0, 2, 0, 0, 0}};
#else
/** Damage-type reactions of the Fire Bro: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};
#endif

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Fire Bro (both early demos), as the percent chance each status takes hold: resists
 * 13 statuses (down to 40% of the normal chance).
 */
static StatusVulnerability regist = {80, 80, 70, 100, 80, 100, 100, 70, 100, 80, 100, 80, 100, 80, 80, 40, 60, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of the Fire Bro (the retail releases), as the percent chance each status takes
 * hold: resists 13 statuses (down to 60% of the normal chance).
 */
static StatusVulnerability regist = {80, 80, 70, 100, 80, 100, 100, 70, 100, 80, 100, 80, 100, 95, 80, 70, 60, 100, 80, 100, 100, 95};
#endif

/**
 * Pose table of the Fire Bro: maps each battle pose (idle, hurt, attacking and so on) to its animation,
 * named BRO_*.
 */
static PoseTableEntry pose_table[] = {
    {1, "BRO_N_1"},
    {2, "BRO_Y_1"},
    {9, "BRO_Y_1"},
    {5, "BRO_K_1"},
    {4, "BRO_X_1"},
    {3, "BRO_X_1"},
    {27, "BRO_D_1"},
    {BTL_POSE_NORMAL, "BRO_S_1"},
    {29, "BRO_Q_1"},
    {30, "BRO_Q_1"},
    {31, "BRO_S_1"},
    {BTL_POSE_DAMAGE, "BRO_D_1"},
    {BTL_POSE_RUN, "BRO_R_1"},
    {BTL_POSE_WALK, "BRO_W_1"},
    {BTL_POSE_DANGER, "BRO_X_1"},
    {BTL_POSE_PERIL, "BRO_X_1"},
    {BTL_POSE_TALK, "BRO_T_1"},
    {BTL_POSE_STAY_DEFAULT, "BRO_S_1"},
};

/**
 * Event data table of the Fire Bro: no custom reactions, so the standard battle handlers run for every
 * event.
 */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/**
 * Parts of the Fire Bro: 7 parts: parts 1 to 7 (model c_burosu_f), each with its defense tables,
 * attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
    {2, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {3, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {5, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {6, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {7, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon record of the Fire Bro's fireball throw: 3 damage and inflicts burn (30%). */
BattleWeapon weapon_fire_bros_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    2, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, // poisonStrength..dodgyTime
    30, // burnChance
    3, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Weapon record of the Fire Bro's rapid-fire fireball throws: 2 damage and inflicts burn (30%). */
BattleWeapon weapon_fire_bros_renzoku_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    2, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, // poisonStrength..dodgyTime
    30, // burnChance
    3, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon record of the Fire Bro's fireball barrage on the whole party: 1 damage, can hit several targets
 * and inflicts burn (30%).
 */
BattleWeapon weapon_fire_bros_nagemakuri_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    2, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, // poisonStrength..dodgyTime
    30, // burnChance
    3, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init event of the Fire Bro: registers its wait, attack,
 * damage and confusion events and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event: runs the default battle damage reaction on the unit itself (part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Attack event of the Fire Bro: a first strike always uses normal_attack_event,
 * otherwise it uses an enemy item if one fits.
 * With 3 HP or less it picks the two-shot renzoku_attack_event 30% of the time
 * and the all-target nagemakuri_attack_event otherwise;
 * with more HP it picks the single-shot normal_attack_event 70% of the time and renzoku_attack_event the rest.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 3)
        SET_VALUE(LW(0), 50)
        ADD(LW(0), 50)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 30)
            CALL_CHILD(renzoku_attack_event)
            GOTO(99)
        END_IF
        CALL_CHILD(nagemakuri_attack_event)
        GOTO(99)
    ELSE
        SET_VALUE(LW(0), 70)
        ADD(LW(0), 30)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 70)
            CALL_CHILD(normal_attack_event)
            GOTO(99)
        END_IF
        CALL_CHILD(renzoku_attack_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Shared hit check for the Fire Bro's fireballs:
 * LW(6) is the weapon, LW(3) and LW(4) the target and part,
 * LW(7) = 1 marks the last hit and LW(8) = 1 the barrage.
 * It pre-checks the hit and sets LW(0) = 1 only on a hit; a dodge or miss lets the fireball fly on.
 * On a hit it records it, in part 2's work 10 for the two-shot attack,
 * or for the barrage in work 10 of the first fireball part (2 to 7) aimed at this target,
 * then applies the damage with the guard result, as the last hit when LW(7) is 1.
 */
static EVT_BEGIN(damage_check_sub)
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(6), 0, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(99)
    LABEL(91)
    SET_VALUE(LW(0), 1)
    IF_INT_EQUAL(LW(6), PTR(&weapon_fire_bros_renzoku_attack))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 10, 1)
    END_IF
    IF_INT_EQUAL(LW(8), 1)
        SET_VALUE(LW(13), 0)
        SET_VALUE(LW(14), 5)
        LOOP(0)
            SET_VALUE(LW(12), 2)
            LOOP(0)
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), LW(13), LW(1))
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), LW(14), LW(2))
                IF_INT_EQUAL(LW(3), LW(1))
                    IF_INT_EQUAL(LW(4), LW(2))
                        ADD(LW(13), 10)
                        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), LW(13), 1)
                        GOTO(98)
                    END_IF
                END_IF
                ADD(LW(12), 1)
                IF_INT_GREATER(LW(12), 7)
                    BREAK_LOOP
                END_IF
            END_LOOP
            ADD(LW(13), 1)
            ADD(LW(14), 1)
        END_LOOP
    END_IF
    LABEL(98)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(6))
    IF_INT_EQUAL(LW(7), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(6), DAMAGE_FLAG_LAST_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(6), 0, LW(5))
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/** Checks a boomerang hit that is not the last one (LW(7) = 0): runs damage_check_sub. */
static EVT_BEGIN(damage_check_no_last)
    SET_VALUE(LW(7), 0)
    CALL_CHILD(damage_check_sub)
    RETURN
EVT_END()

/**
 * Hit check for the last fireball aimed at a target:
 * if an earlier fireball of the same attack already hit it (part 2's work 10 for the two-shot attack,
 * the matching fireball part's work 10 for the barrage),
 * the target takes the last hit with the guard result straight away;
 * otherwise it runs damage_check_sub with LW(7) = 1.
 */
static EVT_BEGIN(damage_check_last)
    IF_INT_EQUAL(LW(6), PTR(&weapon_fire_bros_renzoku_attack))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 2, 10, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            SET_VALUE(LW(0), 1)
        ELSE
            SET_VALUE(LW(0), 0)
        END_IF
        GOTO(10)
    END_IF
    IF_INT_EQUAL(LW(8), 1)
        SET_VALUE(LW(13), 0)
        SET_VALUE(LW(14), 5)
        LOOP(0)
            SET_VALUE(LW(12), 2)
            LOOP(0)
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), LW(13), LW(1))
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), LW(14), LW(2))
                IF_INT_EQUAL(LW(3), LW(1))
                    IF_INT_EQUAL(LW(4), LW(2))
                        ADD(LW(13), 10)
                        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), LW(13), LW(0))
                        GOTO(10)
                    END_IF
                END_IF
                ADD(LW(12), 1)
                IF_INT_GREATER(LW(12), 7)
                    BREAK_LOOP
                END_IF
            END_LOOP
            ADD(LW(13), 1)
            ADD(LW(14), 1)
        END_LOOP
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(6))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(6), DAMAGE_FLAG_LAST_HIT, LW(5))
    ELSE
        SET_VALUE(LW(7), 1)
        CALL_CHILD(damage_check_sub)
    END_IF
    RETURN
EVT_END()

/**
 * Flight of one Fire Bro fireball (part LW(15)) at the target in LW(3)/LW(4):
 * it starts at the Bro and bounces along the floor in 100-unit hops (five hops, of height 6 or 5 chosen at
 * random), spinning, with a bounce sound each hop.
 * A sibling loop checks the target as the fireball passes its hit position (damage_check_last when LW(14) is 1,
 * else damage_check_no_last); a hit hides the fireball and ends the flight,
 * a miss lets it bounce on until it leaves the stage (x beyond 250).
 * At the end the part is hidden and unit work 1 (fireballs finished) goes up by one.
 */
EVT_BEGIN(fire_move_event)
    // The Fire Bro throws a fireball: it appears in its hand and starts spinning.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(15), STRING("BRO_A_1B"))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(15), 15, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 15)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, -180)
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(15), 0, 0, 0)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(9), LW(10), LW(11))
    SUBTRACT(LW(9), LW(0))
    SET_VALUE(LW(10), 0)
    // In parallel, the fireball is checked against the party every frame; it ends if it hits someone or leaves the screen.
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(12), LW(13))
            SWITCH(LW(10))
                CASE_EQUAL(0)
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(11), LW(12), LW(13))
                IF_INT_GREATER_OR_EQUAL(LW(9), 0)
                    IF_INT_LESS_OR_EQUAL(LW(0), LW(11))
                        BREAK_SWITCH
                    END_IF
                ELSE
                    IF_INT_GREATER_OR_EQUAL(LW(0), LW(11))
                        BREAK_SWITCH
                    END_IF
                END_IF
                IF_INT_EQUAL(LW(14), 0)
                    CALL_CHILD(damage_check_no_last)
                ELSE
                    CALL_CHILD(damage_check_last)
                END_IF
                IF_INT_EQUAL(LW(0), 1)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
                    SET_VALUE(LW(10), 2)
                ELSE
                    SET_VALUE(LW(10), 1)
                END_IF
                CASE_END
                CASE_EQUAL(1)
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(11), LW(12), LW(13))
                IF_INT_GREATER_OR_EQUAL(LW(11), 250)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
                    SET_VALUE(LW(10), 2)
                END_IF
                IF_INT_LESS_OR_EQUAL(LW(11), -250)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
                    SET_VALUE(LW(10), 2)
                END_IF
                CASE_END
                CASE_EQUAL(2)
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(15), 15, 1)
                BREAK_LOOP
                CASE_END
            END_SWITCH
        END_LOOP
    END_SIBLING_EVENT
    // The fireball spins as it travels.
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, 16)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_sub_random, 1, LW(11))
    IF_INT_EQUAL(LW(11), 0)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
        // The fireball bounces along the ground in a series of hops, with a sizzle on each landing, until it is used up.
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, 6, FLOAT(0.5996094f))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    ELSE
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, 5, FLOAT(0.5996094f))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        IF_INT_EQUAL(LW(10), 2)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(0), 0, LW(2), 0, -1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), 15, LW(10))
        IF_INT_EQUAL(LW(10), 1)
            GOTO(99)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FIREB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_IF
    // The fireball disappears and the throw is counted as finished.
    LABEL(99)
    WAIT_FRAMES(6)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, 1)
    RETURN
EVT_END()

/**
 * The Fire Bro's single fireball: picks a target, throws one fireball ("BRO_A_1A") by spawning fire_move_event,
 * and waits until it reports back (unit work 1).
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_fire_bros_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_fire_bros_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_fire_bros_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_fire_bros_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_1A"))
    WAIT_FRAMES(40)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(14), 1)
    SET_VALUE(LW(6), PTR(&weapon_fire_bros_attack))
    SET_VALUE(LW(8), 0)
    SPAWN_EVENT(fire_move_event)
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(20)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Fire Bro's two-fireball attack (weapon_fire_bros_renzoku_attack):
 * throws one fireball, 12 frames later a second one, spawning fire_move_event each time,
 * and waits until both have reported back (unit work 1 reaches 2).
 */
static EVT_BEGIN(renzoku_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_fire_bros_renzoku_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_fire_bros_renzoku_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_fire_bros_renzoku_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_fire_bros_renzoku_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 10, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(20)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(14), 0)
    SET_VALUE(LW(6), PTR(&weapon_fire_bros_renzoku_attack))
    SET_VALUE(LW(8), 0)
    SPAWN_EVENT(fire_move_event)
    WAIT_FRAMES(12)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(20)
    SET_VALUE(LW(15), 3)
    SET_VALUE(LW(14), 1)
    SET_VALUE(LW(6), PTR(&weapon_fire_bros_renzoku_attack))
    SET_VALUE(LW(8), 0)
    SPAWN_EVENT(fire_move_event)
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 2)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(20)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Fire Bro's barrage (weapon_fire_bros_nagemakuri_attack, every target):
 * after declaring the attack it stores a target from fire_bros_nagemakuri_set_target in the work of each
 * fireball part 2 to 7, then throws the six fireballs one after another (BRO_A_2A, 15 frames apart),
 * each with nagemakuri_judge_last_attack_event deciding whether it is the last at its target
 * and fire_move_event flying it. It waits until unit work 1 shows all six have finished.
 */
static EVT_BEGIN(nagemakuri_attack_event)
    // Choose the targets for the Fire Bro's barrage of fireballs.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_fire_bros_nagemakuri_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_fire_bros_nagemakuri_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_fire_bros_nagemakuri_attack))
    // The attack on the whole party is announced.
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_fire_bros_nagemakuri_attack))
    SET_VALUE(LW(10), 2)
    // Aim up to eight fireballs, each at a target in the party.
    LOOP(0)
        IF_INT_GREATER(LW(10), 7)
            BREAK_LOOP
        END_IF
        CALL(fire_bros_nagemakuri_set_target, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), LW(6), LW(7), LW(8), LW(9))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 0, LW(0))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 1, LW(2))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 2, LW(4))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 3, LW(6))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 4, LW(8))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 5, LW(1))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 6, LW(3))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 7, LW(5))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 8, LW(7))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 9, LW(9))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 10, 0)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 11, 0)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 12, 0)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 13, 0)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(10), 14, 0)
        ADD(LW(10), 1)
    END_LOOP
    WAIT_FRAMES(12)
    SET_VALUE(LW(10), 0)
    SET_VALUE(LW(11), 5)
    // Throw the fireballs one by one: the Fire Bro turns to the next target, winds up and flings a fireball.
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_THROWN, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, 0)
    LOOP(0)
        SET_VALUE(LW(15), 2)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_THROWN, LW(1))
            IF_INT_GREATER_OR_EQUAL(LW(1), 6)
                LOOP(0)
                    WAIT_FRAMES(1)
                    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_THROWN, LW(1))
                    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, LW(2))
                    SUBTRACT(LW(1), 6)
                    IF_INT_GREATER(LW(2), LW(1))
                        WAIT_FRAMES(3)
                        BREAK_LOOP
                    END_IF
                END_LOOP
            END_IF
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_2A"))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), LW(10), LW(3))
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(15), LW(11), LW(4))
            CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(14))
            CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(14))
            CALL_CHILD(nagemakuri_judge_last_attack_event)
            SET_VALUE(LW(6), PTR(&weapon_fire_bros_nagemakuri_attack))
            SET_VALUE(LW(8), 1)
            SPAWN_EVENT(fire_move_event)
            CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_THROWN, 1)
            WAIT_FRAMES(15)
            ADD(LW(15), 1)
            IF_INT_GREATER(LW(15), 7)
                BREAK_LOOP
            END_IF
        END_LOOP
        ADD(LW(10), 1)
        ADD(LW(11), 1)
        // Wait until every fireball has finished, then the Fire Bro relaxes.
        IF_INT_GREATER(LW(10), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_FIRE_BROS_FINISHED, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 6)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(30)
    // The Fire Bro goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Decides whether the fireball about to be thrown (part LW(15), target LW(3)/LW(4)) is the last one of the
 * barrage at its target: LW(14) = 0 if a later fireball part (up to part 7) is aimed at the same target,
 * otherwise 1.
 */
EVT_BEGIN(nagemakuri_judge_last_attack_event)
    SET_VALUE(LW(0), LW(10))
    SET_VALUE(LW(1), LW(11))
    SET_VALUE(LW(13), LW(15))
    ADD(LW(13), 1)
    LOOP(0)
        IF_INT_GREATER(LW(0), 0)
            SET_VALUE(LW(14), 1)
            GOTO(99)
        END_IF
        LOOP(0)
            IF_INT_GREATER(LW(13), 7)
                SET_VALUE(LW(13), 2)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(13), LW(0), LW(5))
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(13), LW(1), LW(6))
            IF_INT_EQUAL(LW(3), LW(5))
                IF_INT_EQUAL(LW(4), LW(6))
                    SET_VALUE(LW(14), 0)
                    GOTO(99)
                END_IF
            END_IF
            ADD(LW(13), 1)
        END_LOOP
        ADD(LW(0), 1)
        ADD(LW(1), 1)
    END_LOOP
    LABEL(99)
    RETURN
EVT_END()

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
