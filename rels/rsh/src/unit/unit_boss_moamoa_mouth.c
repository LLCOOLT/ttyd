// Smorg Miasma (moamoa_mouth), Smorg's mouth part of the boss battle unit, used on the Excess Express.
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
#include "rsh.h"
#include "version.h"

// Unit work slots of Mr. Moamoa's mouth (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_BOSS_MOAMOA_MOUTH_BODY = 0 // unit id of the main body
};

BattleUnitKind unit_boss_moamoa_mouth;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[4];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_moamoa_attack;
static EvtWord init_event[26];
static EvtWord damage_event[10];
static EvtWord dead_event[88];
static EvtWord attack_event[21];
const char* mouth_Attack_front[7];
static EvtWord evt_attack[302];
static EvtWord wait_event[6];

/**
 * Unit kind of the Smorg Miasma (mouth) (HP 6, level 0):
 * its size, offsets, damage sounds, status vulnerability, parts and init event.
 */
BattleUnitKind unit_boss_moamoa_mouth = {
    111,
    "btl_un_moamoa_mouth",
    6,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    10,
    200,
    120,
    40,
    100,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    280.0f,
    40.0f,
    0.0f,
    100.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_US
    250.0f,
#else
    0.0f,
#endif
    0.0f,
    100.0f,
    0.0f,
    0.0f,
    80.0f,
    80.0f,
    20.0f,
    0.0f,
    120.0f,
    0.0f,
    200.0f,
    120.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MOA_G_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x240000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Smorg Miasma (mouth): 1 damage points off every hit. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Element reactions of the Smorg Miasma (mouth): no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the Smorg Miasma (mouth) (percent chance to take each status):
 * immune to sleep, stop, dizzy, poison, confusion, electric shock, burn, freeze, growing huge, shrinking,
 * attack up, attack down, defence up, defence down, allergy, fright, gale force, speed up, slow, dodgy,
 * invisibility and instant kill.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Pose table of the Smorg Miasma (mouth): maps each battle pose to the animation it plays (S_* animations).
 */
static PoseTableEntry pose_table[] = {
    {28, "S_2"},
    {31, "D_2_1"},
    {39, "D_2_1"},
    {BTL_POSE_STAY_DEFAULT, "S_2"},
};

/** Data table of the Smorg Miasma (mouth): event handlers for being defeated. */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/**
 * Body part of the Smorg Miasma (mouth) (model c_g_moamoa_b): hit position, defences, attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_moamoa_mouth", "c_g_moamoa_b", 0.0f, 0.0f, 0.0f, 67.0f, 82.0f, 10.0f, 63.0f, 95.0f, 10.0f, 20, 30, 255, &defence, &defence_attr, 0x600001, 0, pose_table},
};

/** Weapon of the Smorg Miasma (mouth)'s attack: 10 damage. */
static BattleWeapon weapon_moamoa_attack = {
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
    {10, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init event of the Smorg's mouth part: installs its wait, attack,
 * damage and default confusion events and moves its HP gauge to offset (50, 62).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetHpGaugeOffset, BTL_UNIT_SELF, 50, 62)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Smorg's mouth: runs the default damage handling with LW(10) = -2 and LW(11) = 1. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Death of the Smorg's mouth: it plays the arm-down sound and the L_2_6 pose,
 * then clears the main body's mouth slot (unit work 6 = -1),
 * gives the main body the no-parts defence table and its weakness pose table, moves its hit marker,
 * plays the BIG sounds and the V_1 pose on it, and kills the mouth unit.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_ARM_DOWN2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("L_2_6"))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MOAMOA_MOUTH_BODY, LW(1))
    CALL(btlevtcmd_SetUnitWork, LW(1), 6, -1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(1), 1, PTR(moamoa_defence_no_parts))
    CALL(btlevtcmd_OffPartsAttribute, LW(1), 1, PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(1), 1, PTR(moamoa1_weakness_pose_table))
    CALL(btlevtcmd_SetHitOffset, LW(1), 1, 0, 32, 0)
    CALL(btlevtcmd_SetHitCursorOffset, LW(1), 1, 0, 41, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_BIG1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_BIG2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, LW(1), 1, STRING("V_1"))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(1), 1)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/** Phase event of the Smorg's mouth: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Attack event of the Smorg's mouth: uses an enemy item if it has one, otherwise runs evt_attack. */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL_CHILD(evt_attack)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Moves another Smorg unit along with an attack: plays the first section of the pose list at LW(1) (sections end
 * at a NULL entry) on part LW(5) of unit LW(0) with the arm-move sound running,
 * waits until the main body (LW(6))
 * has unit work 0 set back to non-zero (done by the attacker after its damage check),
 * then plays the next section.
 * Not used by the mouth: its evt_attack never spawns it (the tentacles' copies are spawned for the other two
 * tentacles).
 */
static EVT_BEGIN(evt_attack_other_arm)
    SET_INT_READ_ADDR(LW(1))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_ARM_MOVE1"), EVT_NULLPTR, 0, LW(15))
    LOOP(0)
        READ_INT(LW(2))
        IF_INT_EQUAL(LW(2), 0)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_AnimeChangePose, LW(0), LW(5), LW(2))
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AnimeWaitPlayComplete, LW(0), LW(5))
    END_LOOP
    CALL(evt_snd_sfxoff, LW(15))
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, LW(6), 0, LW(10))
        IF_INT_NOT_EQUAL(LW(10), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_ARM_MOVE1"), EVT_NULLPTR, 0, LW(15))
    LOOP(0)
        READ_INT(LW(2))
        IF_INT_EQUAL(LW(2), 0)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_AnimeChangePose, LW(0), LW(5), LW(2))
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AnimeWaitPlayComplete, LW(0), LW(5))
    END_LOOP
    CALL(evt_snd_sfxoff, LW(15))
    RETURN
EVT_END()

/** Animation names (A_2_1, A_2_2) the Smorg mouth plays, in order, for its attack. */
const char* mouth_Attack_front[] = {
    "A_2_1",
    "A_2_2",
    NULL,
    "A_2_3",
    NULL,
    "A_2_4",
    NULL,
};

/**
 * The Smorg mouth's attack: samples the targets of weapon_moamoa_attack,
 * sets the main body's unit work 0 to 0 and
 * its pose to S_1_1, plays the first section of mouth_Attack_front (A_2_1, A_2_2),
 * waits a second and plays A_2_3,
 * damage-checks every selected target, sets the main body's unit work 0 back to 1 and finishes with A_2_4.
 */
static EVT_BEGIN(evt_attack)
    // Choose the targets for the mouth's attack; a confused mouth is flustered when there are none.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_moamoa_attack))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        RETURN
    END_IF
    // The camera closes in on the mouth and its target, and the attack is announced.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_moamoa_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_moamoa_attack))
    // The main body freezes its idle animation while the mouth strikes.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MOAMOA_MOUTH_BODY, LW(6))
    CALL(btlevtcmd_SetUnitWork, LW(6), 0, 0)
    CALL(btlevtcmd_AnimeChangePose, LW(6), 1, STRING("S_1_1"))
    SET_VALUE(LW(15), 0)
    // The mouth rears up and gapes open.
    SET_INT_READ_ADDR(PTR(&mouth_Attack_front))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_ARM_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LOOP(0)
        READ_INT(LW(2))
        IF_INT_EQUAL(LW(2), 0)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(2))
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    END_LOOP
    // A pause, then the mouth snaps down (or the mouth's closing animation runs on its own).
    WAIT_MS(1000)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MOA_G_ARM_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
    IF_INT_EQUAL(LW(15), 0)
        LOOP(0)
            READ_INT(LW(2))
            IF_INT_EQUAL(LW(2), 0)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(2))
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        END_LOOP
    ELSE
        BEGIN_SIBLING_EVENT
            LOOP(0)
                READ_INT(LW(2))
                IF_INT_EQUAL(LW(2), 0)
                    BREAK_LOOP
                END_IF
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(2))
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            END_LOOP
            LOOP(0)
                READ_INT(LW(2))
                IF_INT_EQUAL(LW(2), 0)
                    BREAK_LOOP
                END_IF
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(2))
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            END_LOOP
            SET_VALUE(GF(9), 0)
        END_SIBLING_EVENT
        WAIT_MS(70)
    END_IF
    // Every target is checked in turn: those who dodge are skipped, the rest take the bite.
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    LOOP(0)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_moamoa_attack), 256, LW(5))
        SWITCH(LW(5))
            CASE_EQUAL(1)
            IF_INT_EQUAL(LW(10), 0)
                CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_moamoa_attack))
            END_IF
            CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_moamoa_attack), 256, LW(5))
            CASE_EQUAL(4)
            CASE_EQUAL(3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
            CASE_EQUAL(6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
            CASE_EQUAL(2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_SWITCH
        CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
        IF_INT_EQUAL(LW(3), -1)
            BREAK_LOOP
        END_IF
        ADD(LW(10), 1)
    END_LOOP
    // The main body resumes idling and the mouth finishes its animation and returns.
    CALL(btlevtcmd_SetUnitWork, LW(6), 0, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    IF_INT_EQUAL(LW(15), 0)
        LOOP(0)
            READ_INT(LW(2))
            IF_INT_EQUAL(LW(2), 0)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(2))
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        END_LOOP
    ELSE
        SET_VALUE(GF(9), 1)
        WAIT_WHILE(GF(9))
    END_IF
    RETURN
EVT_END()

/** Idle event: shows the unit's table pose for state 1. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
