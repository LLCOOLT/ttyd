// Battle unit Hammer Bro (`hammer_bros`): tst.rel's copy of rels/tik/src/unit/unit_hammer_bros.c.
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

// Unit work slots of the Hammer Bro (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_HAMMER_BROS_BARRAGE_UNIT_1 = 0, // barrage throw 1: target unit (slots 0-4 hold throws 1-5)
    UW_HAMMER_BROS_BARRAGE_UNIT_2 = 1, // barrage throw 2: target unit
    UW_HAMMER_BROS_BARRAGE_UNIT_3 = 2, // barrage throw 3: target unit
    UW_HAMMER_BROS_BARRAGE_UNIT_4 = 3, // barrage throw 4: target unit
    UW_HAMMER_BROS_BARRAGE_UNIT_5 = 4, // barrage throw 5: target unit
    UW_HAMMER_BROS_BARRAGE_PART_1 = 5, // barrage throw 1: target part (slots 5-9 hold throws 1-5)
    UW_HAMMER_BROS_BARRAGE_PART_2 = 6, // barrage throw 2: target part
    UW_HAMMER_BROS_BARRAGE_PART_3 = 7, // barrage throw 3: target part
    UW_HAMMER_BROS_BARRAGE_PART_4 = 8, // barrage throw 4: target part
    UW_HAMMER_BROS_BARRAGE_PART_5 = 9, // barrage throw 5: target part
    UW_HAMMER_BROS_HIT_1 = 10,         // barrage throw 1 hit (unit slot + 10); in the series: an earlier throw hit
    UW_HAMMER_BROS_HIT_2 = 11,         // barrage throw 2 hit
    UW_HAMMER_BROS_HIT_3 = 12,         // barrage throw 3 hit
    UW_HAMMER_BROS_HIT_4 = 13,         // barrage throw 4 hit
    UW_HAMMER_BROS_HIT_5 = 14,         // barrage throw 5 hit
};

static USER_FUNC(hammer_bros_nagemakuri_set_target);
static void hammer_bros_get_next_target(s32* unitIdx, s32* partIdx);
static void hammer_bros_get_target(s32* unitIdx, s32* partIdx);

BattleUnitKind unit_hammer_bros;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[6];
static BattleWeapon weapon_hammer_bros_attack;
static BattleWeapon weapon_hammer_bros_renzoku_attack;
static BattleWeapon weapon_hammer_bros_nagemakuri_attack;
static EvtWord init_event[21];
static EvtWord damage_event[10];
static EvtWord attack_event[96];
static EvtWord normal_attack_event[112];
static EvtWord renzoku_attack_event[111];
static EvtWord renzoku_attack_event_sub_no_last[13];
static EvtWord renzoku_attack_event_sub_last[39];
static EvtWord nagemakuri_attack_event[186];
static EvtWord nagemakuri_attack_event_sub[49];
static EvtWord nagemakuri_attack_event_sub_no_last[13];
static EvtWord nagemakuri_attack_event_sub_last[76];
static EvtWord wait_event[6];

/** Advances to the next weapon target and returns its unit and part index, or (-1, 0) after the last one. */
static void hammer_bros_get_next_target(s32* unitIdx, s32* partIdx) {
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

/** Returns the unit and part index of the weapon target currently selected in weaponTargets. */
static void hammer_bros_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}

/**
 * Script helper: picks five random targets from the weapon's current target list
 * and writes them as (unit, part) pairs to args, for the Bro's rapid throwing ('nagemakuri') attack.
 */
static USER_FUNC(hammer_bros_nagemakuri_set_target) {
    EvtWord* args = event->args;
    s32 unitIdx[20];
    s32 partIdx[20];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    hammer_bros_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        hammer_bros_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}

/**
 * Unit kind of Hammer Bro: 7 max HP, level 26. The battle engine reads it when the unit spawns:
 * size, offsets, sounds, status vulnerability, parts, init script and event table.
 */
BattleUnitKind unit_hammer_bros = {
    56,
    "btl_un_hammer_bros",
    7,
    0,
    1,
    1,
    26,
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
    "SFX_ENM_HUMMER_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    6,
    parts,
    init_event,
    data_table,
};

/**
 * Defence of Hammer Bro per element (normal, fire, ice, explosion, electric), subtracted from each hit:
 * 1 against every element.
 */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Element reactions of Hammer Bro: none, every element hits normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of Hammer Bro (the demos), as the percent chance a status takes hold:
 * always hit by Poison, Electric, Burn, Huge, Attack Up, Defense Up, Fast, Dodgy and Invisible;
 * otherwise Sleep 60, Stop 80, Dizzy 80, Confuse 80, Freeze 80, Tiny 80, Attack Down 80, Defense Down 80,
 * Allergic 80, Fright 40, Gale Force 60, Slow 80 and instant KO 95.
 */
static StatusVulnerability regist = {60, 80, 80, 100, 80, 100, 100, 80, 100, 80, 100, 80, 100, 80, 80, 40, 60, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of Hammer Bro (the final versions), as the percent chance a status takes hold:
 * always hit by Poison, Electric, Burn, Huge, Attack Up, Defense Up, Fast, Dodgy and Invisible;
 * otherwise Sleep 80, Stop 80, Dizzy 70, Confuse 80, Freeze 70, Tiny 80, Attack Down 80, Defense Down 95,
 * Allergic 80, Fright 70, Gale Force 60, Slow 80 and instant KO 95.
 */
static StatusVulnerability regist = {80, 80, 70, 100, 80, 100, 100, 70, 100, 80, 100, 80, 100, 95, 80, 70, 60, 100, 80, 100, 100, 95};
#endif

/**
 * Pose table of Hammer Bro: maps its battle pose types (stay, walk, hurt, dead, talk and so on) to
 * animation names, 18 entries such as BRO_N_1, BRO_Y_1, BRO_K_1, BRO_X_1.
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
 * Event table of Hammer Bro: maps event tags to the scripts that react to them (no custom reactions);
 * tag 0 ends it.
 */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/**
 * Body parts of Hammer Bro: 6 parts (model c_burosu_h); the first is the body.
 * Each part names its defence tables and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_hammer_bros", "c_burosu_h", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
    {2, "btl_un_hammer_bros", "c_burosu_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {3, "btl_un_hammer_bros", "c_burosu_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_hammer_bros", "c_burosu_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {5, "btl_un_hammer_bros", "c_burosu_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {6, "btl_un_hammer_bros", "c_burosu_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Attack data of Hammer Bro's attack: base damage 4, 100% accuracy. */
static BattleWeapon weapon_hammer_bros_attack = {
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Attack data of Hammer Bro's renzoku attack: base damage 2, 100% accuracy. */
static BattleWeapon weapon_hammer_bros_renzoku_attack = {
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
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Attack data of Hammer Bro's nagemakuri attack: base damage 2, 100% accuracy. */
static BattleWeapon weapon_hammer_bros_nagemakuri_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init script of the Hammer Bro.
 * Registers its wait, attack and damage scripts and sets its walking and jumping sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage reaction of the Hammer Bro: the default damage script. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Attack script of the Hammer Bro.
 * Picks one of three attacks: the single hammer throw (normal_attack_event),
 * the successive throws (renzoku_attack_event) or the barrage (nagemakuri_attack_event);
 * with a 50 percent chance for the barrage or the series when several targets exist,
 * and the normal throw otherwise. Uses the confused-attack and enemy-item checks first.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_1, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_2, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_3, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_4, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_5, 0)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
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
        IF_INT_LESS(LW(1), 50)
            CALL_CHILD(renzoku_attack_event)
            GOTO(99)
        END_IF
        CALL_CHILD(nagemakuri_attack_event)
        GOTO(99)
    ELSE
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Starts the target's avoid animation for the result of a pre-damage check (3, 6 or 2 select the three avoid
 * types, 38 to 40).
 */
static EVT_BEGIN(start_avoid)
    IF_INT_EQUAL(LW(5), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(5), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(5), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

/**
 * A missed hammer throw: the hammer (part LW(15), BRO_A_1B) spins out from the Bro with SFX_ENM_HUMMER_ATTACK1
 * and 2, the target starts its dodge (start_avoid) as the hammer passes it, and the hammer bounces twice on the
 * floor behind the target (SFX_ENM_HUMMER_ATTACK3) and is hidden.
 */
static EVT_BEGIN(hammer_bros_attack_common_event1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HUMMER_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(15), STRING("BRO_A_1B"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
    MULTIPLY(LW(0), 10)
    ADD(LW(6), LW(0))
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, -135)
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(15), 0, 5, 0)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HUMMER_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(10)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, 32)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid)
                    BREAK_LOOP
                END_IF
            ELSE
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(15), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_GREATER_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 60, 0, FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8), 60, -1)
    CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HUMMER_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(6), 100)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, FLOAT(4.0f), FLOAT(0.5996094f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), 0, LW(8), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HUMMER_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(6), 150)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, FLOAT(4.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), 0, LW(8), 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
    RETURN
EVT_END()

/**
 * Flight of a hammer throw that hits: the hammer (part LW(15), BRO_A_1B) spins out from the Bro with
 * SFX_ENM_HUMMER_ATTACK1 and 2 and lands on the target's hit position; the caller then applies the damage.
 */
static EVT_BEGIN(hammer_bros_attack_common_event2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HUMMER_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(15), STRING("BRO_A_1B"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
    MULTIPLY(LW(0), 10)
    ADD(LW(6), LW(0))
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, -135)
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(15), 0, 5, 0)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HUMMER_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(10)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, 32)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 60, 0, FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), LW(7), LW(8), 60, -1)
    RETURN
EVT_END()

/**
 * After a hammer hits: the hammer (part LW(15)), still spinning, bounces off the target 50 units back toward the
 * Bro, drops to the floor and is hidden.
 */
static EVT_BEGIN(hammer_bros_attack_common_event3)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(15), 0, 0, 32)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(15), STRING("BRO_A_1B"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(6), 50)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(15), 0, FLOAT(2.0f), FLOAT(0.5f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(15), LW(6), 0, LW(8), 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(15), PART_ATTR_NO_SHADOW)
    RETURN
EVT_END()

/**
 * One hammer throw (weapon LW(9)) at LW(3), LW(4), used by all three attacks: checks the hit in advance; a dodge
 * plays the missed throw (hammer_bros_attack_common_event1).
 * A hit, with LW(11) = 1, is first marked for the _last scripts (unit work 10 for the series, the target's slot
 * mark in unit work 10 to 14 for the barrage); then the hammer flies in (common_event2),
 * the guard result and the
 * damage are applied (as the last hit when LW(10) = 1) and the hammer bounces off (common_event3).
 */
static EVT_BEGIN(damage_check_event_sub)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        GOTO(90)
        CASE_EQUAL(2)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    CALL_CHILD(hammer_bros_attack_common_event1)
    GOTO(99)
    LABEL(91)
    IF_INT_EQUAL(LW(11), 1)
        IF_INT_EQUAL(LW(9), PTR(&weapon_hammer_bros_renzoku_attack))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_1, 1)
        ELSE
            SET_VALUE(LW(13), UW_HAMMER_BROS_BARRAGE_UNIT_1)
            SET_VALUE(LW(14), UW_HAMMER_BROS_BARRAGE_PART_1)
            LOOP(0)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(13), LW(5))
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(14), LW(6))
                IF_INT_EQUAL(LW(3), LW(5))
                    IF_INT_EQUAL(LW(4), LW(6))
                        ADD(LW(13), 10)
                        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, LW(13), 1)
                        BREAK_LOOP
                    END_IF
                END_IF
                ADD(LW(13), 1)
                ADD(LW(14), 1)
            END_LOOP
        END_IF
    END_IF
    CALL_CHILD(hammer_bros_attack_common_event2)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    IF_INT_EQUAL(LW(10), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
    END_IF
    CALL_CHILD(hammer_bros_attack_common_event3)
    GOTO(99)
    LABEL(99)
    RETURN
EVT_END()

/**
 * The Hammer Bro's single hammer throw: samples a target (or the first-attack target), pays the weapon cost,
 * winds up (BRO_A_1A), throws once through damage_check_event_sub and goes back to its wait pose.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_hammer_bros_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_hammer_bros_attack), LW(3), LW(4))
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
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_hammer_bros_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_hammer_bros_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_1A"))
    WAIT_FRAMES(27)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(9), PTR(&weapon_hammer_bros_attack))
    SET_VALUE(LW(10), 1)
    SET_VALUE(LW(11), 0)
    CALL_CHILD(damage_check_event_sub)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Hammer Bro's series of four throws (renzoku = in a row) at one target with
 * weapon_hammer_bros_renzoku_attack:
 * it winds up (BRO_A_1A) before each and spawns them 250 ms apart with hammer parts 2 to 5, the fourth through
 * renzoku_attack_event_sub_last, then waits 1.5 seconds.
 */
static EVT_BEGIN(renzoku_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_hammer_bros_renzoku_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_hammer_bros_renzoku_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_hammer_bros_renzoku_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_hammer_bros_renzoku_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(14), 0)
    SET_VALUE(LW(15), 2)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(14), 4)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_1A"))
        WAIT_FRAMES(27)
        IF_INT_EQUAL(LW(14), 3)
            SPAWN_EVENT(renzoku_attack_event_sub_last)
        ELSE
            SPAWN_EVENT(renzoku_attack_event_sub_no_last)
        END_IF
        WAIT_MS(250)
        ADD(LW(14), 1)
        ADD(LW(15), 1)
    END_LOOP
    LABEL(98)
    WAIT_MS(1500)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * One of the first three throws of the series: damage_check_event_sub with the series weapon, not the last hit,
 * marking a hit (LW(10) = 0, LW(11) = 1).
 */
static EVT_BEGIN(renzoku_attack_event_sub_no_last)
    SET_VALUE(LW(9), PTR(&weapon_hammer_bros_renzoku_attack))
    SET_VALUE(LW(10), 0)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(damage_check_event_sub)
    RETURN
EVT_END()

/**
 * The fourth throw of the series: when an earlier throw hit (unit work 10) it flies in and applies the guard
 * result and the damage as the last hit without a new dodge check, then bounces off; otherwise it is a normal
 * throw as the last hit.
 */
static EVT_BEGIN(renzoku_attack_event_sub_last)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_HIT_1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(hammer_bros_attack_common_event2)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_hammer_bros_renzoku_attack))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_hammer_bros_renzoku_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
        CALL_CHILD(hammer_bros_attack_common_event3)
    ELSE
        SET_VALUE(LW(9), PTR(&weapon_hammer_bros_renzoku_attack))
        SET_VALUE(LW(10), 1)
        SET_VALUE(LW(11), 0)
        CALL_CHILD(damage_check_event_sub)
    END_IF
    RETURN
EVT_END()

/**
 * The Hammer Bro's barrage (nagemakuri = throwing wildly): declares an attack on all targets, draws five random
 * targets (hammer_bros_nagemakuri_set_target; units in unit work 0 to 4, parts in 5 to 9)
 * and throws at the first
 * four in turn, facing each and spawning nagemakuri_attack_event_sub 250 ms apart with hammer parts 2 to 5, then
 * waits 1.5 seconds.
 */
static EVT_BEGIN(nagemakuri_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_hammer_bros_nagemakuri_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_hammer_bros_nagemakuri_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_hammer_bros_nagemakuri_attack))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_hammer_bros_nagemakuri_attack))
    CALL(hammer_bros_nagemakuri_set_target, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), LW(6), LW(7), LW(8), LW(9))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_UNIT_1, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_UNIT_2, LW(2))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_UNIT_3, LW(4))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_UNIT_4, LW(6))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_UNIT_5, LW(8))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_PART_1, LW(1))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_PART_2, LW(3))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_PART_3, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_PART_4, LW(7))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HAMMER_BROS_BARRAGE_PART_5, LW(9))
    SET_VALUE(LW(12), 0)
    SET_VALUE(LW(13), UW_HAMMER_BROS_BARRAGE_UNIT_1)
    SET_VALUE(LW(14), UW_HAMMER_BROS_BARRAGE_PART_1)
    SET_VALUE(LW(15), 2)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(12), 4)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(13), LW(3))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(14), LW(4))
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(10))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(10))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BRO_A_1A"))
        WAIT_FRAMES(27)
        SPAWN_EVENT(nagemakuri_attack_event_sub)
        WAIT_MS(250)
        ADD(LW(12), 1)
        ADD(LW(13), 1)
        ADD(LW(14), 1)
        ADD(LW(15), 1)
    END_LOOP
    LABEL(98)
    WAIT_MS(1500)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * One throw of the barrage (slot LW(13)): when a later throw (up to slot 3) goes to the same target it runs
 * nagemakuri_attack_event_sub_no_last, otherwise nagemakuri_attack_event_sub_last,
 * so each target's final throw is
 * its last hit.
 */
static EVT_BEGIN(nagemakuri_attack_event_sub)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(13), LW(3))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(14), LW(4))
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(13), 3)
            CALL_CHILD(nagemakuri_attack_event_sub_last)
            BREAK_LOOP
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(13), LW(5))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                CALL_CHILD(nagemakuri_attack_event_sub_no_last)
                BREAK_LOOP
            END_IF
        END_IF
    END_LOOP
    RETURN
EVT_END()

/**
 * A barrage throw that is not the target's final one:
 * damage_check_event_sub with the barrage weapon, not the last
 * hit, marking a hit (LW(10) = 0, LW(11) = 1).
 */
static EVT_BEGIN(nagemakuri_attack_event_sub_no_last)
    SET_VALUE(LW(9), PTR(&weapon_hammer_bros_nagemakuri_attack))
    SET_VALUE(LW(10), 0)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(damage_check_event_sub)
    RETURN
EVT_END()

/**
 * A target's final barrage throw: when an earlier throw already hit it (its mark in unit work 10 to 14) the
 * hammer
 * flies in and the guard result and the damage are applied as the last hit without a new dodge check, then it
 * bounces off; otherwise it is a normal throw as the last hit.
 */
static EVT_BEGIN(nagemakuri_attack_event_sub_last)
    SET_VALUE(LW(13), UW_HAMMER_BROS_BARRAGE_UNIT_1)
    SET_VALUE(LW(14), UW_HAMMER_BROS_BARRAGE_PART_1)
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(13), LW(5))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                ADD(LW(13), 10)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(13), LW(0))
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
    END_LOOP
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(hammer_bros_attack_common_event2)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_hammer_bros_nagemakuri_attack))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_hammer_bros_nagemakuri_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
        CALL_CHILD(hammer_bros_attack_common_event3)
    ELSE
        SET_VALUE(LW(9), PTR(&weapon_hammer_bros_nagemakuri_attack))
        SET_VALUE(LW(10), 1)
        SET_VALUE(LW(11), 0)
        CALL_CHILD(damage_check_event_sub)
    END_IF
    RETURN
EVT_END()

/** Wait script of the Hammer Bro: shows its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
