// Battle unit Ruff Puff (`kurokumorn`): tst.rel's copy of rels/eki/src/unit/unit_kurokumorn.c.
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

// Unit work slots of the Ruff Puff.
enum {
    UW_KUROKUMORN_LOW = 0,    // 1 while it hovers low (y 10), in reach of hammers and shell tosses; 0 while high (y 40)
    UW_KUROKUMORN_UNUSED = 1, // cleared by init_event; nothing reads it
};

BattleUnitKind unit_kurokumorn;
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

/** Unit definition of the Ruff Puff: 7 HP, level 23, 1 part, with its sounds, init script and data table. */
BattleUnitKind unit_kurokumorn = {
    UNIT_RUFF_PUFF,
    "btl_un_kurokumorn",
    7,
    0,
    1,
    1,
    23,
    0,
    1,
    70,
    2,
    50,
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

/** Defence of the Ruff Puff: none, so it takes full damage from every kind of attack. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type modifiers of the Ruff Puff: it is healed by electric attacks. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 3}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Ruff Puff (100% is the normal chance): immune to Electrified; resists Sleep
 * 60%, Stop 80%, Dizzy 80%, Confusion 70%, Freeze 70%, Tiny 70%, Attack Down 70%, Defense Down 70%, Allergic
 * 70%, Fright 70%, Gale Force 90%, Slow 70% and instant KO 95%.
 */
static StatusVulnerability regist = {60, 80, 80, 100, 70, 0, 100, 70, 100, 70, 100, 70, 100, 70, 70, 70, 90, 100, 70, 100, 100, 95};
#else
static StatusVulnerability regist = {75, 75, 100, 100, 70, 0, 100, 100, 100, 90, 100, 90, 100, 90, 60, 70, 95, 100, 70, 100, 100, 95};
#endif

/**
 * Body of the Ruff Puff: one targetable part, the model `c_kmoon`, with its hit box, defence tables and pose
 * table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_kurokumorn", "c_kmoon", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
};

/**
 * Attack data of the Ruff Puff's swoop: hits one opposing unit for 4 damage; flips shelled enemies over;
 * knocks flying enemies out of the air.
 */
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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
 * Attack data of the Ruff Puff's thunder: hits every opposing unit for 4 electric damage, ignoring the
 * target's defence.
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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
 * Attack AI of the Ruff Puff: uses an enemy item if it has one.
 * If it is charged (counter attribute 1024 on its part,
 * set by charge_event) it releases the thunder attack on everyone.
 * Otherwise it draws a normal attack (60) or a charge (40).
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
    SET_VALUE(LW(0), 60)
    ADD(LW(0), 40)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 60)
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
 * The Ruff Puff's charged lightning attack on every target of the opposing side:
 * it winds up for 60 frames, drops pokopi_thunder effects from above (eight bolts in four volleys of two,
 * around the middle of the targets' side of the stage) while the camera shakes,
 * and then resolves the damage on each target in turn,
 * showing each avoid animation. The charge flag is cleared when the bolts start.
 */
static EVT_BEGIN(thunder_event)
    // Picks a random opposing unit as the first target (flustered if confused and none is left).
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
    // Declares the thunder attack on every opposing unit, pays its cost and turns toward them.
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // Wind-up: the charge sound plays with pose A_2B for a second, then poses A_3A and A_3B.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(30)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3B"))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_ELECTRIC)
    // Lightning falls in four rounds of two bolts, 12 frames apart, scattered over the party's half of the stage.
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
    // The camera shakes as the bolts strike.
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 30, 0)
    SET_VALUE(LW(6), 0)
    LABEL(0)
    // Goes through each opposing unit in turn and works out whether the lightning hits it.
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
    // Miss branch: this unit is spared.
    LABEL(90)
    GOTO(97)
    // Hit branch: reads the defence result (once, for the first unit) and applies the damage.
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(97)
    LABEL(97)
    // Next target, until all have been checked.
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    // The cloud settles back into its idle pose.
    LABEL(98)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(250)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Pose table of the Ruff Puff: its 17 battle poses (status, hurt and action) and the animation each one
 * plays; the idle animation is `S_1`.
 */
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
 * Data table of the Ruff Puff: event 42 runs counter_event; event 48 runs dmg_first_attack_pos for the First
 * Strike that opens the battle.
 */
static BattleDataEntry data_table[] = {
    {42, counter_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

/**
 * Battle init script for the Ruff Puff: installs the wait, unison phase, attack, damage and confusion handlers,
 * clears unit work 0 and 1 and starts barrier_event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KUROKUMORN_LOW, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KUROKUMORN_UNUSED, 0)
    SPAWN_EVENT(barrier_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Looping script started from init_event: every 31 frames, for as long as the unit exists,
 * shows the glowing charge effect (akari_charge_n64) over the Ruff Puff
 * while it is charged (counter attribute 1024); it stops when the unit is gone.
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

/**
 * Data-table event 48, which the default damage script runs (damage code 0x39)
 * when the battle opens with Mario's or his partner's First Strike on this unit:
 * it sets the unit's height to 10 and waits for the strike to end.
 */
static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Damage handler: selects this unit (-2) and its part 1
 * and runs the shared default damage reaction (btldefaultevt_Damage).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Empty counter handler (data table slot 42). */
static EVT_BEGIN(counter_event)
    RETURN
EVT_END()

/**
 * Runs at the start of the enemy phase before the player's turn, if the Ruff Puff can act and is not charged:
 * with a 50% chance it switches height.
 * UW_KUROKUMORN_LOW = 1 means it is low: it then rises to y = 40
 * and its part gets the flags that keep hammers and shell tosses off it;
 * otherwise it dives down to y = 10 and the flags are cleared. Plays the matching movement sound.
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
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KUROKUMORN_LOW, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 40)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KUROKUMORN_LOW, 0)
        ELSE
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 10)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_KUROKUMORN_LOW, 1)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Normal attack: the Ruff Puff squashes and shakes, dives up and back,
 * then swoops through the target at its hit position and returns home, resetting its scale.
 * A hit shakes the camera and zooms in; avoid results start the target's avoid animation.
 */
static EVT_BEGIN(normal_attack_event)
    // Picks the target: the preset first-attack target when battle flag 2 is set, otherwise a random opposing unit;
    // with no target it does nothing (or is flustered when confused).
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
    // Declares the attack, pays its cost and turns to face the target while the camera zooms in.
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    // Wind-up: the cloud trembles and squashes itself narrower (rolling sound), then draws back and up away from the
    // target.
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -40)
    SET_VALUE(LW(1), 60)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    // It swoops down at the target with a rushing sound.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 40, -40, 1, 0, -1)
    CALL(evt_snd_sfxoff, LW(15))
    // Checks the outcome of the hit: a miss, dodge or guard goes to the no-damage branch; a connecting hit applies
    // the Action Command defence result and deals the damage.
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
    // Miss branch: it passes the target.
    LABEL(90)
    GOTO(98)
    // Hit branch: the camera shakes and pulls in, the defence result is read and the damage is applied.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(98)
    // It rises over the target, floats back to its home position and settles into its idle pose.
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
 * Charging turn: zooms the camera on the Ruff Puff,
 * plays the charge sound and animation for 80 frames and sets counter attribute 1024 on its part,
 * so that it is charged for its next attack (and for barrier_event's glow).
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

/**
 * Wait (idle) event: refreshes the body animation (part 1) from the pose table and resets the unit's scale to 1,
 * undoing any squash from an earlier animation.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    RETURN
EVT_END()
