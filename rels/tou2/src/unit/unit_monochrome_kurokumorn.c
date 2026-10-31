// unit_monochrome_kurokumorn: Dark Puff (`monochrome_kurokumorn`), battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "version.h"

// Unit work slots of the Dark Puff.
enum {
    UW_MONOCHROME_KUROKUMORN_LOW = 0,    // 1 while it hovers low (y 10), in reach of hammers and shell tosses; 0 while high (y 40)
    UW_MONOCHROME_KUROKUMORN_UNUSED = 1, // cleared by init_event; nothing reads it
};

BattleUnitKind unit_monochrome_kurokumorn;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_kurokumorn_attack;
static BattleWeapon weapon_kurokumorn_thunder_attack;
static EvtWord thunder_event[493];
static PoseTableEntry pose_table[17];
static BattleDataEntry data_table[3];
static EvtWord init_event[37];
static EvtWord barrier_event[59];
static EvtWord dmg_first_attack_pos[19];
static EvtWord damage_event[10];
static EvtWord counter_event[2];
static EvtWord unison_phase_event[140];
static EvtWord normal_attack_event[386];
static EvtWord charge_event[58];
static EvtWord wait_event[12];

/**
 * Unit data of the Dark Puff: 3 HP and level 10, with its parts, status vulnerability, init event and
 * event data table.
 */
BattleUnitKind unit_monochrome_kurokumorn = {
    UNIT_DARK_PUFF,
    "btl_un_monochrome_kurokumorn",
    3,
    0,
    1,
    1,
    10,
    0,
    1,
    70,
    1,
    60,
    9999,
    35,
    30,
    4,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    -3,
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
    17.5f,
    0.0f,
    0.0f,
    17.5f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    35.0f,
    30.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KUMO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/**
 * Defense of the Dark Puff against normal, fire, ice, explosion and electric attacks: none, so it takes
 * full damage from every element.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type reactions of the Dark Puff: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Dark Puff (both early demos), as the percent chance each status takes hold:
 * resists 9 statuses (down to 90% of the normal chance); extra vulnerable to dizziness and Gale Force.
 */
static StatusVulnerability regist = {100, 100, 110, 100, 90, 100, 100, 90, 100, 90, 100, 90, 100, 90, 90, 90, 110, 100, 90, 100, 100, 95};
#else
/**
 * Status vulnerability of the Dark Puff (the retail releases), as the percent chance each status takes
 * hold: resists 10 statuses (down to 80% of the normal chance); extra vulnerable to dizziness and Gale
 * Force.
 */
static StatusVulnerability regist = {95, 95, 105, 100, 90, 100, 100, 100, 100, 95, 100, 95, 100, 95, 80, 90, 105, 100, 90, 100, 100, 95};
#endif

/**
 * Parts of the Dark Puff: a single body part (part 1, model c_kmoon_wb), each with its defense tables,
 * attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_monochrome_kurokumorn", "c_kmoon_wb", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
};

/** Weapon record of the Dark Puff's swoop: 2 damage. */
static BattleWeapon weapon_kurokumorn_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    1, // superguardsAllowed
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    COUNTER_RESIST_ELECTRIC, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
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
 * Weapon record of the Dark Puff's lightning attack on the whole party: 2 damage, can hit several targets
 * and ignores Defense.
 */
static BattleWeapon weapon_kurokumorn_thunder_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
#if VERSION >= VERSION_US
    2, // superguardsAllowed
#else
    0, // superguardsAllowed
#endif
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_ELECTRIC, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, // poisonStrength..electricChance
    3, // electricTime
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyChance..sizeChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeStrength..allergicChance
    0, 0, 0, 0, 0, 0, 0, 0, // allergicTime..frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack script of the monochrome Dark Puff: item use first;
 * if it is charged (part counter attribute 1024) it fires the thunder attack (thunder_event);
 * otherwise 50% of the time it uses its normal attack (normal_attack_event) and
 * otherwise it charges up (charge_event).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_ELECTRIC, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(&weapon_kurokumorn_thunder_attack))
        CALL_CHILD(thunder_event)
        GOTO(99)
    END_IF
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 50)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(9), PTR(&weapon_kurokumorn_attack))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL_CHILD(charge_event)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dark Puff's charged thunder attack with the weapon in LW(9):
 * it clears the charged flag, plays poses A_2B to A_3B, calls down eight pokopi_thunder_n64 bolts over the
 * targets' side of the stage, then resolves the first target and each one after it in turn
 * (pre-damage and damage checks)
 * before dropping back to its resting pose.
 */
static EVT_BEGIN(thunder_event)
    // Dark Puff gets ready to strike the whole party with lightning.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // The attack on every target is announced.
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // Dark Puff gathers a charge: the charge sound plays with its A_2B, A_3A and A_3B poses.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(30)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3B"))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_ELECTRIC)
    // Bolts of lightning crackle down in sequence while the thunder sounds.
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetEnemyBelong, LW(3), LW(10))
        IF_INT_EQUAL(LW(10), 0)
            SET_VALUE(LW(10), 125)
        ELSE
            SET_VALUE(LW(10), -125)
        END_IF
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), -60)
        ADD(LW(2), -60)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), 60)
        ADD(LW(2), 60)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        WAIT_FRAMES(12)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), 0)
        ADD(LW(2), -75)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), 0)
        ADD(LW(2), 75)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        WAIT_FRAMES(12)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), 60)
        ADD(LW(2), -60)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), -60)
        ADD(LW(2), 60)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        WAIT_FRAMES(12)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), 75)
        ADD(LW(2), 0)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        SET_VALUE(LW(0), LW(10))
        SET_VALUE(LW(2), 0)
        ADD(LW(0), -75)
        ADD(LW(2), 0)
        CALL(evt_eff64, STRING(""), STRING("pokopi_thunder_n64"), 0, LW(0), 210, LW(2), LW(0), 0, LW(2), FLOAT(4.0f), 20, 0, 0, 0)
        WAIT_FRAMES(12)
    END_SIBLING_EVENT
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 30, 0)
    SET_VALUE(LW(6), 0)
    // For each target in turn, find out how it reacts to the bolt.
    LABEL(0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // A bolt that misses is dodged or lands harmlessly.
    LABEL(90)
    GOTO(97)
    // A bolt that hits applies its damage (unless the target blocked it).
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(97)
    // Move on to the next target, or finish.
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    // Dark Puff settles back into its idle pose.
    LABEL(98)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(250)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Pose table of the Dark Puff: maps each battle pose (idle, hurt, attacking and so on) to its animation. */
static PoseTableEntry pose_table[] = {
    {STATUS_SLEEP, "N_1"},
    {STATUS_STOP, "Y_1"},
    {STATUS_FREEZE, "Y_1"},
    {STATUS_CONFUSE, "K_1"},
    {STATUS_POISON, "X_1"},
    {STATUS_DIZZY, "X_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Event data table of the Dark Puff: scripts that replace the standard handling for its counter hook (tag
 * 42) and the battle opening with a First Strike on it (tag 48).
 */
static BattleDataEntry data_table[] = {
    {42, counter_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

/**
 * Init script of a Puff: registers its wait, unison-phase, attack, damage and confusion handlers,
 * clears unit work 0 and 1, spawns barrier_event to show its charged state and starts the idle event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MONOCHROME_KUROKUMORN_LOW, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MONOCHROME_KUROKUMORN_UNUSED, 0)
    SPAWN_EVENT(barrier_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Loops while the Dark Puff exists: every 31 frames, if it is charged (part counter attribute 1024),
 * plays the akari_charge_n64 glow effect above it, scaled to its size.
 */
static EVT_BEGIN(barrier_event)
    LABEL(0)
    WAIT_FRAMES(31)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_ELECTRIC, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(1), 20)
        CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(3))
        CALL(evt_eff64, STRING(""), STRING("akari_charge_n64"), 0, LW(0), LW(1), LW(2), LW(3), 30, 0, 0, 0, 0, 0, 0)
    END_IF
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/** Position event for a first strike on this unit: sets its height to 10 and waits for the attack to finish. */
static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Damage reaction: runs the default damage handling (btldefaultevt_Damage) with LW(10) = -2 (the unit itself)
 * and LW(11) = 1.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Counter event of the Puff: empty, it does nothing. */
static EVT_BEGIN(counter_event)
    RETURN
EVT_END()

/**
 * Start-of-turn event of the Dark Puff (not while it is charged or unable to act):
 * 50% of the time it changes height.
 * From up high it sinks to height 10 with SFX_ENM_KUMO_MOVE5 and clears PART_ATTR_HAMMERLIKE_CANNOT_TARGET and
 * PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET on its body, so hammers and shell attacks reach it (unit work 0 = 1);
 * from down low it rises back to height 40 with SFX_ENM_KUMO_MOVE4 and sets them again (work 0 = 0).
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_ELECTRIC, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(evt_sub_random, 99, LW(0))
    IF_INT_LESS(LW(0), 50)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_MONOCHROME_KUROKUMORN_LOW, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 40)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MONOCHROME_KUROKUMORN_LOW, 0)
        ELSE
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 10)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MONOCHROME_KUROKUMORN_LOW, 1)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * The Puff's plain attack with the weapon in LW(9):
 * picks a target and plays the A_2A and A_1A attack poses with SFX_ENM_KUMO_MOVE1 to 3 without leaving its spot;
 * the damage check decides between a miss and a hit, then it returns to S_1.
 */
static EVT_BEGIN(normal_attack_event)
    // Use the target of the opening first attack if there was one, otherwise choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // The attack is announced.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    // Dark Puff shudders and shrinks as it gathers itself for a swoop.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 1, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, -1, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(40)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.009765625f), 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // It pulls back, then dives at the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -40)
    SET_VALUE(LW(1), 60)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 40, -40, 1, 0, -1)
    CALL(evt_snd_sfxoff, LW(15))
    // Find out how the target reacts to the dive.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
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
        SET_VALUE(LW(15), 1)
        CASE_END
    END_SWITCH
    // The dive missed: Dark Puff sweeps on past the target.
    LABEL(90)
    GOTO(98)
    // The dive connects: the damage is applied.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(98)
    // Dark Puff floats back to its home position and relaxes.
    LABEL(98)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(10), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(1), LW(12), 40, 0, 4, 0, -1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 40, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_MS(250)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Charges the Dark Puff: zooms the camera onto it,
 * sets the charged flag (part counter attribute 1024) with SFX_ENM_KUMO_CHARGE1 and the A_2A/A_2B poses,
 * so its next attack is the thunder.
 */
static EVT_BEGIN(charge_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_ELECTRIC)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(600)
    LABEL(99)
    RETURN
EVT_END()

/** Idle event of the Puff: sets the pose from the pose table and resets its scale to 1. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    RETURN
EVT_END()
