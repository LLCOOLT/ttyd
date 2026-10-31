// Rogueport Sewers (tik) battle unit: R. Tentacle (gesso_right_arm), Blooper's right tentacle: its parts, defence/status tables, and
// attack events.
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "tik.h"

// Unit work slots of the Blooper's right tentacle (slots read on the Blooper body stay raw).
enum {
    UW_BOSS_GESSO_RIGHT_ARM_BODY = 0, // unit id of the Blooper body, -1 if none
};

static USER_FUNC(_check_zenei_kouei);

BattleUnitKind unit_boss_gesso_right_arm;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[4];
#if VERSION >= VERSION_JP
BattleDataEntry gesso_right_arm_data_table[13];
#endif
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
static EvtWord init_event[25];
static EvtWord damage_event[31];
#if VERSION >= VERSION_JP
extern EvtWord gesso_right_arm_damage_event[];
#endif
BattleWeapon weapon_gesso_right_arm_front_attack;
BattleWeapon weapon_gesso_right_arm_rear_attack;
static EvtWord attack_event[273];
static EvtWord wait_event[6];
extern EvtWord gesso_fall_check[];

/**
 * Unit kind of the R. Tentacle (HP 3, level 0):
 * its size, offsets, damage sounds, status vulnerability, parts and init event.
 */
BattleUnitKind unit_boss_gesso_right_arm = {
    10,
    "btl_un_gesso_right_arm",
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
    60,
    110,
    -68,
    -100,
    0.0f,
    0.0f,
    0.0f,
    -85,
    -140,
    0.0f,
    0.0f,
    0.0f,
    30.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    30.0f,
    0.0f,
    0.0f,
    30.0f,
    71.5f,
    0.0f,
    -60.0f,
    -60.0f,
    0.0f,
    60.0f,
    100.0f,
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
#if VERSION <= VERSION_DEMO_US
    data_table,
#else
    gesso_right_arm_data_table,
#endif
};

/** Defence of the R. Tentacle: no damage reduction. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element reactions of the R. Tentacle: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the R. Tentacle (percent chance to take each status):
 * immune to sleep, stop, dizzy, poison, confusion, electric shock, freeze, growing huge, shrinking, attack up,
 * attack down, defence up, defence down, allergy, fright, gale force, speed up, slow, dodgy,
 * invisibility and instant kill.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/** Pose table of the R. Tentacle: maps each battle pose to the animation it plays (GSO_* animations). */
static PoseTableEntry pose_table[] = {
    {BTL_POSE_NORMAL, "GSO_S1_1"},
    {31, "GSO_S1_1"},
    {BTL_POSE_DAMAGE, "GSO_D1_1"},
    {BTL_POSE_STAY_DEFAULT, "GSO_S1_1"},
};

#if VERSION >= VERSION_JP
/** Data table of the Blooper's R. Tentacle: its damage reaction for the hit tags 24 to 36. */
BattleDataEntry gesso_right_arm_data_table[] = {
    {24, gesso_right_arm_damage_event},
    {25, gesso_right_arm_damage_event},
    {26, gesso_right_arm_damage_event},
    {27, gesso_right_arm_damage_event},
    {28, gesso_right_arm_damage_event},
    {29, gesso_right_arm_damage_event},
    {30, gesso_right_arm_damage_event},
    {31, gesso_right_arm_damage_event},
    {32, gesso_right_arm_damage_event},
    {33, gesso_right_arm_damage_event},
    {34, gesso_right_arm_damage_event},
    {35, gesso_right_arm_damage_event},
    {36, gesso_right_arm_damage_event},
};
#endif

/** Data table of the R. Tentacle: event handlers for its arm hit pose and being defeated. */
static BattleDataEntry data_table[] = {
    {10, gesso_arm_damage_pose_event},
    {49, gesso_arm_dead_event},
    {0},
};

/** Body part of the R. Tentacle (model c_gesso2): hit position, defences, attributes and pose table. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_gesso_right_arm", "c_gesso2", 0.0f, 0.0f, 0.0f, 85.0f, -110.0f, 0.0f, 85.0f, -110.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, VERSION_PICK(0x680009, 0x2680009), 0, pose_table},
};

/**
 * Init script of the Blooper's right tentacle.
 * Registers its damage, phase and attack scripts and starts it waiting.
 */
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
 * Damage reaction of the right tentacle: runs the default damage,
 * then tells the body (unit work 0) to go back to its wait script if it is idle.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StartWaitEvent, LW(3))
        END_IF
    END_IF
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
/** Damage reaction of the Blooper's right tentacle (JP and later); the same as the left tentacle's damage event. */
EVT_BEGIN(gesso_right_arm_damage_event)
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StartWaitEvent, LW(3))
        END_IF
    END_IF
    RETURN
EVT_END()
#endif

/** Phase script of the right tentacle; does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Weapon of the R. Tentacle's front swat: 1 damage. */
BattleWeapon weapon_gesso_right_arm_front_attack = {
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

/** Weapon of the R. Tentacle's rear swat: 1 damage. */
BattleWeapon weapon_gesso_right_arm_rear_attack = {
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
    TARGET_WEIGHT_PREFER_BACK, // targetWeightFlags
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
 * Attack script of the right tentacle: uses an enemy item if it has one;
 * otherwise picks the front or rear weapon
 * at random (they prefer front or back targets) and samples a target. The first time it targets Mario (unit kind
 * 0xDE, tracked in the Blooper's unit work 5) the Blooper asks whether Mario thinks it would taste good, with a
 * yes/no answer (tik_02_gs_04). It then swings with GSO_A1_1 or GSO_A1_3 depending on the target's side of the
 * stage (_check_zenei_kouei) and damage-checks the targets.
 */
static EVT_BEGIN(attack_event)
    // The tentacle may use an item instead of attacking.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // Pick the front or rear swat at random and choose a target.
    CALL(evt_sub_random, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        SET_VALUE(LW(12), PTR(&weapon_gesso_right_arm_front_attack))
    ELSE
        SET_VALUE(LW(12), PTR(&weapon_gesso_right_arm_rear_attack))
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    // The attack is announced and the guard timing is awaited.
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    // The first time the target is Mario, the Blooper stops to ask whether he thinks it would taste good (yes
    // or no).
    SET_VALUE(LW(11), 0)
    CALL(btlevtcmd_GetUnitKind, LW(3), LW(0))
    IF_INT_EQUAL(LW(0), UNIT_MARIO)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(9))
        CALL(btlevtcmd_GetUnitWork, LW(9), 5, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(11), 1)
            CALL(btlevtcmd_SetUnitWork, LW(9), 5, 1)
        END_IF
    END_IF
    IF_INT_NOT_EQUAL(LW(11), 0)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(9))
        CALL(evt_msg_print, 2, STRING("tik_02_gs_04_1"), 0, LW(9))
        CALL(evt_msg_print, 2, STRING("tik_02_gs_04_2"), 0, LW(9))
        CALL(evt_msg_select, 0, STRING("tik_02_gs_04_3"))
        CALL(evt_msg_continue)
        IF_INT_EQUAL(LW(0), 0)
            BEGIN_INLINE_EVENT
                CALL(evt_msg_print, 2, STRING("tik_02_gs_04_3_y"), 0, LW(9))
                CALL(btlevtcmd_StatusWindowOnOff, 1)
            END_INLINE_EVENT
        ELSE
            BEGIN_INLINE_EVENT
                CALL(evt_msg_toge, 2, 110, 120, 30)
                CALL(evt_msg_print, 2, STRING("tik_02_gs_04_3_n"), 0, LW(9))
                CALL(btlevtcmd_StatusWindowOnOff, 1)
            END_INLINE_EVENT
        END_IF
    END_IF
    // The tentacle swings across the stage, from the near or far side depending on where the target stands.
    CALL(_check_zenei_kouei, LW(3), LW(13))
    IF_INT_EQUAL(LW(13), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_A1_1"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_A1_3"))
    END_IF
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftof, 32, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_ARM_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_ftof, 55, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
#if VERSION >= VERSION_US
    CALL(btlevtcmd_ftof, 97, LW(0))
#else
    CALL(btlevtcmd_ftof, 94, LW(0))
#endif
    WAIT_FRAMES(LW(0))
    // The swat lands unless the target dodges; then the damage is dealt.
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
    // The swing finishes and the tentacle returns to waiting.
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script of the right tentacle: shows its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Death script shared by the two tentacles.
 * Plays the arm's retreat sound and pose (GSO_F1_1),
 * clears the body's slot that pointed to this arm (the left arm waits 50 frames, the right 80) and
 * then runs the fall check; finally kills the arm unit.
 */
EVT_BEGIN(gesso_arm_dead_event)
    CALL(btlevtcmd_GetUnitKind, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), UNIT_BLOOPER_RIGHT_TENTACLE)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_ARM_GOOUT1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_F1_1"))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 2, -1)
        END_IF
        WAIT_FRAMES(50)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 2, -1)
        END_IF
    ELSE
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_GESSO_ARM_GOOUT1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GSO_F1_1"))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 1, -1)
        END_IF
        WAIT_FRAMES(80)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 1, -1)
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 2)
        GOTO(99)
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        WAIT_FRAMES(1)
        GOTO(10)
    END_IF
    CALL_CHILD(gesso_fall_check)
    LABEL(99)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Called when a tentacle has died.
 * If both tentacles are gone and the Blooper is not already falling, it makes the Blooper fall:
 * it plays the fall poses with the fall and down sounds, shakes the camera,
 * then switches the Blooper to the "turned" state with its own defence table,
 * status resistances and hit offsets so it can be attacked from the front.
 */
EVT_BEGIN(gesso_fall_check)
    CALL(btlevtcmd_GetUnitWork, LW(3), 1, LW(0))
    CALL(btlevtcmd_GetUnitId, LW(0), LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(3), 2, LW(0))
    CALL(btlevtcmd_GetUnitId, LW(0), LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(3), 4, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(3), 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_SetUnitWork, LW(3), 4, 2)
    CALL(btlevtcmd_GetUnitWork, LW(3), 3, 0)
    CALL(btlevtcmd_StopWaitEvent, LW(3))
    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("GSO_F_1"))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(3), 1)
    CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("GSO_F_2"))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftof, 16, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_BOSS_GESSO_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(3), 1)
    CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(3), 1, PTR(gesso_pose_table_turn))
    CALL(btlevtcmd_SetHpGaugeOffset, LW(3), 0, 0)
    CALL(btlevtcmd_SetStatusIconOffset, LW(3), 46, 118)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(3), 1, PTR(gesso_defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(3), 1, PTR(gesso_defence_attr_turn))
    CALL(btlevtcmd_SetRegistStatus, LW(3), PTR(gesso_regist_turn))
    CALL(btlevtcmd_SetHitOffset, LW(3), 1, -15, -90, 0)
    CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 55, 113)
    CALL(evt_btl_camera_shake_h, 0, 6, 0, 30, 4)
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, 1)
    CALL(btlevtcmd_SetHitOffset, LW(3), 1, 51, 38, 30)
    CALL(btlevtcmd_SetHitCursorOffset, LW(3), 1, 51, 38, 30)
    CALL(btlevtcmd_SetUnitWork, LW(3), 4, 0)
    CALL(btlevtcmd_StartWaitEvent, LW(3))
    RETURN
EVT_END()

/** When a tentacle is hit, makes the Blooper body (unit work 0) stop waiting and take the same damage pose (LW(14)). */
EVT_BEGIN(gesso_arm_damage_pose_event)
    CALL(btlevtcmd_GetUnitKind, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), UNIT_BLOOPER_RIGHT_TENTACLE)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
    ELSE
        IF_INT_EQUAL(LW(0), UNIT_BLOOPER_LEFT_TENTACLE)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GESSO_RIGHT_ARM_BODY, LW(3))
        ELSE
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_StopWaitEvent, LW(3))
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), 1, LW(14))
    RETURN
EVT_END()

/**
 * Script helper.
 * Sets args[1] to 0 if the unit args[0] stands at X >= -120 and to 1 if it is farther to the left.
 * zenei and kouei mean front and rear (row), matching the right tentacle's front and rear weapons, whose target
 * weights prefer front and back targets.
 */
static USER_FUNC(_check_zenei_kouei) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    f32 x, y, z;

    id = BattleTransID(event, id);
    BtlUnit_GetPos(BattleGetUnitPtr(wp, id), &x, &y, &z);
    if (x >= -120.0f) {
        evtSetValue(event, out, 0);
    } else {
        evtSetValue(event, out, 1);
    }
    return EVT_RETURN_DONE;
}
