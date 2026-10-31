// The Great Tree (mri) battle unit: Lord Crump (kanbu2) in the Magnus von Grapple fight: its parts, defence/status
// tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"
#include "version.h"

BattleUnitKind unit_boss_kanbu2;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
BattleWeapon weapon_kanbu2_attack;
static EvtWord init_event[37];
static EvtWord damage_event[10];
static EvtWord dead_event[26];
static EvtWord attack_event[24];
static EvtWord wait_event[6];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_guard[18];
static EvtWord normal_attack_event[365];

BattleUnitKind unit_boss_kanbu2 = {
    188,
    "btl_un_kanbu2",
    15,
    0,
    1,
    1,
    1,
    10,
    0,
    100,
    0,
    100,
    9,
    56,
    59,
    56,
    59,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    28.0f,
    38.35f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    42.0f,
    52.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BTL_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 100, 100, 100, 100, 0};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_kanbu2", "c_kanbu", 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

BattleWeapon weapon_kanbu2_attack = {
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
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
    0, // counterResistFlags
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
 * Init event of Lord Crump: installs wait, attack, damage and the default confusion events,
 * sets the walk and run sounds (SFX_BOSS_KANBU_MOVE1L/R), and starts the idle loop.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of Lord Crump: runs the default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Lord Crump's defeat script (data table entry 49):
 * prints a Japanese debug message ("after this he is due to ride the Magnus von Grapple"),
 * hops off 300 units to the right and removes himself from the battle.
 */
static EVT_BEGIN(dead_event)
    CALL(evt_msg_print, 1, STRING("このあと\nまぐなむばってんだーに　のるよてい<key>"), 0, 0)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(5.0f), FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, 300, 0, 0, 0, -1)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Lord Crump's turn: uses an enemy item if he has one,
 * otherwise always performs the basic attack (weapon_kanbu2_attack).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_kanbu2_attack))
    CALL_CHILD(normal_attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of Lord Crump: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {BTL_POSE_TALK, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static PoseTableEntry pose_table_guard[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "G_2"},
    {BTL_POSE_TALK, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "G_2"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "G_2"},
};

/**
 * Lord Crump's basic attack (weapon in LW(9), weapon_kanbu2_attack):
 * picks a target, runs at it and does a belly flop.
 * He hops (SFX_BOSS_KANBU_JUMP1, poses A_1A and A_1B) over the target;
 * the pre-damage check decides between a dodge and a hit,
 * and on a hit he lands on it (A_1C, SFX_BOSS_KANBU_HIP_ATTACK1 and 2),
 * bounces and gets up (D_1) before returning home.
 * Falls back to the flustered reaction when confused with nothing to hit.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(2.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
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
        CASE_END
        LABEL(90)
        GOTO(98)
        LABEL(91)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        GOTO(98)
        LABEL(98)
        CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_HIP_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(evt_btl_camera_shake_h, 0, 10, 0, 60, 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 0, FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 10)
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 0, FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
        WAIT_FRAMES(25)
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_HIP_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_HIP_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_1"))
        WAIT_FRAMES(15)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 15, 0, FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
        WAIT_FRAMES(10)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(7.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
        RETURN
EVT_END()
