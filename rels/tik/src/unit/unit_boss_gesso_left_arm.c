// Rogueport Sewers (tik) battle unit: L. Tentacle (gesso_left_arm), Blooper's left tentacle: its parts, defence/status tables, and
// attack events.
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "tik.h"

// Unit work slots of the Blooper's left tentacle (the body's slots it reads are left as numbers).
enum {
    UW_BOSS_GESSO_LEFT_ARM_BODY = 0, // unit id of the Blooper's body, -1 when there is none
};

BattleUnitKind unit_boss_gesso_left_arm;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[4];
#if VERSION >= VERSION_JP
BattleDataEntry gesso_left_arm_data_table[13];
#endif
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
static EvtWord init_event[25];
static EvtWord damage_event[31];
#if VERSION >= VERSION_JP
extern EvtWord gesso_left_arm_damage_event[];
#endif
BattleWeapon weapon_gesso_left_arm_attack;
static EvtWord attack_event[171];
static EvtWord wait_event[6];

/**
 * Unit kind of the L. Tentacle (HP 3, level 0):
 * its size, offsets, damage sounds, status vulnerability, parts and init event.
 */
BattleUnitKind unit_boss_gesso_left_arm = {
    UNIT_BLOOPER_LEFT_TENTACLE,
    "btl_un_gesso_left_arm",
    3,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    9,
    150,
    40,
    -240,
    36,
    0.0f,
    0.0f,
    0.0f,
    -255,
    -5,
    0.0f,
    0.0f,
    0.0f,
    75.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    75.0f,
    0.0f,
    0.0f,
    75.0f,
    26.0f,
    0.0f,
    -215.0f,
    20.0f,
    0.0f,
    150.0f,
    40.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GESSO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_KNOCKBACK_POSE,
    &regist,
    1,
    parts,
    init_event,
#if VERSION <= VERSION_DEMO_JP
    data_table,
#else
    gesso_left_arm_data_table,
#endif
};

/** Defence of the L. Tentacle: no damage reduction. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element reactions of the L. Tentacle: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the L. Tentacle (percent chance to take each status):
 * immune to sleep, stop, dizzy, poison, confusion, electric shock, freeze, growing huge, shrinking, attack up,
 * attack down, defence up, defence down, allergy, fright, gale force, speed up, slow, dodgy,
 * invisibility and instant kill.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/** Pose table of the L. Tentacle: maps each battle pose to the animation it plays (GSO_* animations). */
static PoseTableEntry pose_table[] = {
    {BTL_POSE_NORMAL, "GSO_S1_1"},
    {31, "GSO_S1_1"},
    {BTL_POSE_DAMAGE, "GSO_D1_1"},
    {BTL_POSE_STAY_DEFAULT, "GSO_S1_1"},
};

#if VERSION >= VERSION_JP
/** Data table of the Blooper's L. Tentacle: its damage reaction for the hit tags 24 to 36. */
BattleDataEntry gesso_left_arm_data_table[] = {
    {24, gesso_left_arm_damage_event},
    {25, gesso_left_arm_damage_event},
    {26, gesso_left_arm_damage_event},
    {27, gesso_left_arm_damage_event},
    {28, gesso_left_arm_damage_event},
    {29, gesso_left_arm_damage_event},
    {30, gesso_left_arm_damage_event},
    {31, gesso_left_arm_damage_event},
    {32, gesso_left_arm_damage_event},
    {33, gesso_left_arm_damage_event},
    {34, gesso_left_arm_damage_event},
    {35, gesso_left_arm_damage_event},
    {36, gesso_left_arm_damage_event},
};
#endif

/** Data table of the L. Tentacle: event handlers for its arm hit pose and being defeated. */
static BattleDataEntry data_table[] = {
    {10, gesso_arm_damage_pose_event},
    {49, gesso_arm_dead_event},
    {0},
};

/** Body part of the L. Tentacle (model c_gesso3): hit position, defences, attributes and pose table. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_gesso_left_arm", "c_gesso3", 0.0f, 0.0f, 0.0f, 270.0f, 20.0f, 0.0f, 270.0f, 20.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, VERSION_PICK(PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_UNTATTLEABLE, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_UNTATTLEABLE | PART_ATTR_NO_SHADOW), 0, pose_table},
};

/** Init script of the Blooper's left tentacle. Registers its damage, phase and attack scripts and starts it waiting. */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage reaction of the left tentacle: runs the default damage, then,
 * if the body (unit work 0) is idle (work 4 not above 0), tells the body to go back to its wait script.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_LEFT_ARM_BODY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StartWaitEvent, LW(3))
        END_IF
    END_IF
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
/**
 * Damage reaction of the Blooper's left tentacle (JP and later).
 * Plays the hit pose (38 or 39 depending on the damage pattern), runs the damage and,
 * if the tentacle was defeated, the death event; otherwise it returns to the wait pose.
 * Afterwards the body is told to wait again when no tentacle fall is in progress.
 */
EVT_BEGIN(gesso_left_arm_damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_SHOW_HP_GAUGE)
    SET_VALUE(LW(14), 39)
    SET_VALUE(LW(15), -1)
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 38)
    END_IF
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
    END_SIBLING_EVENT
    CALL_CHILD(subsetevt_damage)
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_DEFEATED, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        WAIT_FRAMES(30)
        CALL_CHILD(subsetevt_dead)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_LAST_HIT, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_WaitAttackEnd)
    END_IF
    CALL(btlevtcmd_ResetFaceDirection, LW(10))
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    LABEL(99)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_LEFT_ARM_BODY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StartWaitEvent, LW(3))
        END_IF
    END_IF
    RETURN
EVT_END()
#endif

/** Phase script of the left tentacle; does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Weapon of the L. Tentacle's swat: 1 damage. */
BattleWeapon weapon_gesso_left_arm_attack = {
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
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT, // targetWeightFlags
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
 * Attack script of the left tentacle: uses an enemy item if it has one; otherwise samples a target for
 * weapon_gesso_left_arm_attack, swings (GSO_A1_1) with the arm-move and attack sounds,
 * damage-checks the target (and each further one if the weapon hits several) and waits for the pose to finish.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(&weapon_gesso_left_arm_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_A1_1"))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftof, 16, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_ARM_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_ftof, 44, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
#if VERSION >= VERSION_US
    CALL(btlevtcmd_ftof, 67, LW(0))
#else
    CALL(btlevtcmd_ftof, 64, LW(0))
#endif
    WAIT_FRAMES(LW(0))
    LABEL(50)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 1)
        SWITCH(LW(5))
            CASE_EQUAL(3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
            CASE_EQUAL(6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
            CASE_EQUAL(2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_SWITCH
    ELSE
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
        IF_INT_NOT_EQUAL(LW(3), -1)
            GOTO(50)
        END_IF
    END_IF
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script of the left tentacle: shows its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
