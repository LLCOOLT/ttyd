// crimson_patatogemet (unit kind 174): a variant of tst's unit_patatogemet.c with its own kind, name and
// stats.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "data_tables.h"
#include "battle/battle_sub.h"

BattleUnitKind unit_crimson_patatogemet;
static BattleWeapon weapon_patamet_attack;
static BattleUnitDefense defence_pata;
static BattleUnitDefenseAttr defence_attr_pata;
static StatusVulnerability regist_pata;
static PoseTableEntry pose_table_pata[18];
static BattleDataEntry data_table_pata[4];
static BattleUnitKindPart parts_pata[1];
static PoseSoundTiming pose_sound_timing_table[9];
static EvtWord init_event_pata[26];
EvtWord crimson_dmg_avoid_counter_thorn_head_event_pata[61];
static EvtWord damage_event_pata[10];
static EvtWord dmg_fall_event_pata[106];
static EvtWord dmg_first_attack_pos_event_pata[19];
static EvtWord attack_event_pata[339];
static EvtWord wait_event_pata[6];
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_ceil[17];
#if VERSION <= VERSION_DEMO_US
static PoseTableEntry pose_table_turn[14];
#else
static PoseTableEntry pose_table_turn[16];
#endif
static BattleDataEntry data_table[4];
static BattleDataEntry data_table_ceil[14];
static BattleWeapon weapon_met_attack;
static BattleWeapon weapon_met_ceil_attack;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static BattleUnitDefenseAttr defence_attr_turn;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static EvtWord init_event[12];
#if VERSION <= VERSION_DEMO_US
static EvtWord init_event2[142];
#else
static EvtWord init_event2[148];
#endif
static EvtWord dmg_avoid_counter_thorn_head_event[61];
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[82];
static EvtWord wakeup_event[96];
static EvtWord attack_event[546];
static EvtWord wait_event[6];
static EvtWord damage_event_ceil[49];
#if VERSION <= VERSION_DEMO_US
static EvtWord counter_damage_event_ceil[70];
#else
static EvtWord counter_damage_event_ceil[76];
#endif
#if VERSION <= VERSION_DEMO_US
static EvtWord ceil_fall_ready_event[157];
#else
static EvtWord ceil_fall_ready_event[163];
#endif
#if VERSION <= VERSION_DEMO_US
static EvtWord attack_event_ceil[420];
#else
static EvtWord attack_event_ceil[426];
#endif
static EvtWord wait_event_ceil[6];

BattleUnitKind unit_crimson_patatogemet = {
    174,
    "btl_un_crimson_patatogemet",
    5,
    0,
    1,
    1,
    21,
    0,
    1,
    60,
    1,
    50,
    9999,
    28,
    30,
    5,
    30,
    0.0f,
    17.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    0.0f,
    14.0f,
    19.5f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    28.0f,
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
    "SFX_ENM_MET_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
#if VERSION >= VERSION_US
    &regist_pata,
#else
    &regist,
#endif
    1,
    parts_pata,
    init_event_pata,
    data_table_pata,
};

static BattleWeapon weapon_patamet_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_FIERY | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#else
    COUNTER_RESIST_FIERY | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#endif
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

static BattleUnitDefense defence_pata = {{4, 99, 4, 99, 4}};

static BattleUnitDefenseAttr defence_attr_pata = {{0, 2, 0, 2, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist_pata = {60, 90, 75, 100, 75, 100, 0, 75, 100, 75, 100, 75, 100, 75, 75, 60, 65, 100, 75, 100, 100, 95};
#else
static StatusVulnerability regist_pata = {75, 90, 75, 100, 75, 100, 0, 75, 100, 90, 100, 90, 100, 95, 75, 60, 30, 100, 75, 100, 100, 95};
#endif

static PoseTableEntry pose_table_pata[] = {
    {1, "PTM_N_1"},
    {2, "PTM_Y_1"},
    {9, "PTM_Y_1"},
    {5, "PTM_K_1"},
    {4, "PTM_X_1"},
    {3, "PTM_X_1"},
    {28, "PTM_S_1"},
    {29, "PTM_Q_1"},
    {30, "PTM_Q_1"},
    {31, "PTM_S_1"},
    {39, "PTM_D_1"},
    {50, "PTM_A_1"},
    {42, "PTM_R_1"},
    {40, "PTM_W_1"},
    {56, "PTM_X_1"},
    {57, "PTM_X_1"},
    {BTL_POSE_TALK, "PTM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PTM_S_1"},
};

static BattleDataEntry data_table_pata[] = {
    {14, dmg_fall_event_pata},
    {37, crimson_dmg_avoid_counter_thorn_head_event_pata},
    {48, dmg_first_attack_pos_event_pata},
    {0, NULL},
};

static BattleUnitKindPart parts_pata[] = {
    {1, "btl_un_crimson_patatogemet", "c_met_h", 0.0f, 0.0f, 0.0f, 0.0f, 23.0f, 0.0f, 0.0f, 28.0f, 0.0f, 20, 30, 255, &defence_pata, &defence_attr_pata, 0x600809, 0x1, pose_table_pata},
};

static PoseSoundTiming pose_sound_timing_table[] = {
    {"PTM_S_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_W_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_R_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_A_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_K_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_N_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_X_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {"PTM_T_1", 0.01f, NULL, "SFX_ENM_PATAMET_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init script of the winged form: installs its own wait,
 * attack and damage handlers (confusion reuses the attack), sets the pose sound table and starts the wait event.
 */
static EVT_BEGIN(init_event_pata)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_pata))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_pata))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_pata))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_pata))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * After the Red Spiky Parabuzzy dodges or counters,
 * flashes a thorn-spark effect (toge_flush) above its head 30 frames later,
 * higher or lower depending on whether it is Mega or Mini.
 */
EVT_BEGIN(crimson_dmg_avoid_counter_thorn_head_event_pata)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 50)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 30)
        GOTO(90)
    END_IF
    ADD(LW(1), 40)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Damage handler: runs the shared default damage script (btldefaultevt_Damage) with its default parameters
 * (LW(10) = -2, LW(11) = 1).
 */
static EVT_BEGIN(damage_event_pata)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Called when the winged form is hit down: clears its flying state and winged part attribute,
 * switches to the ground tables and parts, changes its kind to the wingless version (kind 73) and lands,
 * then runs init_event; if it took more than one point of damage it also flips over (dmg_turn_event).
 */
static EVT_BEGIN(dmg_fall_event_pata)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, LW(10), 4)
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), 2048)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_ReplaceParts, LW(10), LW(11), PTR(parts), 1)
    CALL(btlevtcmd_OnUnitFlag, LW(10), 4)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ChangeKind, LW(10), 73)
    CALL(btlevtcmd_GetHpDamageCount, LW(10), LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL_CHILD(init_event)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
        RETURN
    ELSE
        CALL_CHILD(init_event)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
        CALL_CHILD(dmg_turn_event)
    END_IF
    RETURN
EVT_END()

/**
 * Positioning script that runs before the unit's first attack in a battle:
 * puts it at height 10 and waits for the attack to end.
 */
static EVT_BEGIN(dmg_first_attack_pos_event_pata)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Attack script of the winged form: picks a target after the item-use check, flies up,
 * then dives in shell form at the target; on a miss it flies past,
 * on a hit it plays the attack sound and deals damage. It then flies back home.
 */
static EVT_BEGIN(attack_event_pata)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_patamet_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_patamet_attack), LW(3), LW(4))
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
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_patamet_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_patamet_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAMET_MOVE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, FLOAT(1.0f), 0, 0, -1)
    WAIT_MS(250)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAMET_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(9.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 10)
    SUBTRACT(LW(1), 30)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patamet_attack), 256, LW(5))
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
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, LW(3), EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 0, 0, -1)
    WAIT_MS(300)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_patamet_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patamet_attack), 256, LW(5))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAMET_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle script of the winged form: sets the standard waiting pose from the unit's pose table. */
static EVT_BEGIN(wait_event_pata)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "TMT_N_1"},
    {2, "TMT_Y_1"},
    {9, "TMT_Y_1"},
    {5, "TMT_K_1"},
    {4, "TMT_X_1"},
    {3, "TMT_X_1"},
    {28, "TMT_S_1"},
    {29, "TMT_Q_1"},
    {30, "TMT_Q_1"},
    {31, "TMT_A_1"},
    {39, "TMT_D_1"},
    {50, "TMT_A_1"},
    {40, "TMT_W_1"},
    {42, "TMT_R_1"},
    {56, "TMT_X_1"},
    {57, "TMT_X_1"},
    {BTL_POSE_STAY_DEFAULT, "TMT_S_1"},
};

static PoseTableEntry pose_table_ceil[] = {
    {1, "STM_N_1"},
    {2, "STM_Y_1"},
    {9, "STM_Y_1"},
    {5, "STM_K_1"},
    {4, "STM_X_1"},
    {3, "STM_X_1"},
    {28, "STM_S_1"},
    {29, "STM_Q_1"},
    {30, "STM_Q_1"},
    {31, "STM_A_1"},
    {39, "STM_D_1"},
    {50, "STM_A_1"},
    {40, "STM_W_1"},
    {42, "STM_R_1"},
    {56, "STM_X_1"},
    {57, "STM_X_1"},
    {BTL_POSE_STAY_DEFAULT, "STM_S_1"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "TMT_Y_2"},
    {2, "TMT_Y_2"},
    {9, "TMT_Y_2"},
    {5, "TMT_S_3"},
    {4, "TMT_S_3"},
    {3, "TMT_S_3"},
    {28, "TMT_S_3"},
    {29, "TMT_Q_2"},
    {30, "TMT_Q_2"},
    {31, "TMT_A_1"},
    {39, "TMT_S_3"},
#if VERSION >= VERSION_JP
    {40, "TMT_W_1"},
    {42, "TMT_R_1"},
#endif
    {56, "TMT_S_3"},
    {57, "TMT_S_3"},
    {BTL_POSE_STAY_DEFAULT, "TMT_S_3"},
};

static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleDataEntry data_table_ceil[] = {
    {26, counter_damage_event_ceil},
    {25, counter_damage_event_ceil},
    {27, counter_damage_event_ceil},
    {28, counter_damage_event_ceil},
    {29, counter_damage_event_ceil},
    {30, counter_damage_event_ceil},
    {31, counter_damage_event_ceil},
    {32, counter_damage_event_ceil},
    {33, counter_damage_event_ceil},
    {34, counter_damage_event_ceil},
    {35, counter_damage_event_ceil},
    {36, counter_damage_event_ceil},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleWeapon weapon_met_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_ALL, // counterResistFlags
#else
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#endif
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
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

static BattleWeapon weapon_met_ceil_attack = {
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
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_ALL, // counterResistFlags
#else
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#endif
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

static BattleUnitDefense defence = {{4, 99, 4, 99, 4}};

static BattleUnitDefenseAttr defence_attr = {{0, 2, 0, 2, 0}};

static BattleUnitDefense defence_turn = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr_turn = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {60, 90, 75, 100, 75, 100, 0, 75, 100, 75, 100, 75, 100, 75, 75, 60, 65, 100, 75, 100, 100, 95};
#else
static StatusVulnerability regist = {75, 90, 75, 100, 75, 100, 0, 75, 100, 90, 100, 90, 100, 95, 75, 60, 30, 100, 75, 100, 100, 95};
#endif

static BattleUnitKindPart parts[] = {
    {1, "btl_un_crimson_togemet", "c_met_h", 0.0f, 0.0f, 0.0f, 0.0f, 23.0f, 0.0f, 0.0f, 28.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
};

/**
 * Init script of the crimson shell-backed unit:
 * reads unit work 0 (1 means it starts on the ceiling) into LW(15),
 * runs init_event2 to install the right handlers and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(15))
    CALL_CHILD(init_event2)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Installs the handlers for the spiked unit's current form, chosen by unit work 0:
 * on the ground (0) its normal wait, attack, damage and confusion scripts;
 * on the ceiling (1) the ceiling pose and data tables at height 130 with the ceiling scripts
 * and the fall script. Both set the run and walk sounds and clear the flipped-over count.
 */
static EVT_BEGIN(init_event2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 4096)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    ELSE
        CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 2)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 4194304)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 2097152)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_ceil))
        CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_ceil))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(1), 130)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_ceil))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_ceil))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_ceil))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_ceil))
        CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, PTR(ceil_fall_ready_event))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, -50, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, -50, 0)
#if VERSION >= VERSION_JP // the JP demo has no kiss move offsets
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, -17, 0)
#endif
    END_IF
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Spike spark shown when an attacker is hurt by (or avoids) the spiked head:
 * waits 30 frames, then spawns the toge_flush effect above the unit's head (38 units up when Huge, 18 when Tiny,
 * else 28).
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 38)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 18)
        GOTO(90)
    END_IF
    ADD(LW(1), 28)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Damage handler: runs the shared default damage script (btldefaultevt_Damage) with its default parameters
 * (LW(10) = -2, LW(11) = 1).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Flips the spiked unit onto its back: swaps in the flipped defence, pose and attribute tables,
 * marks status flag 1 (flipped) with a flipped-over count of 1, plays the shell sound,
 * lands it in two bounces at height 5 and turns off the spike counter on part 1.
 */
static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(4)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 12, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 5, LW(2))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 1)
    RETURN
EVT_END()

/**
 * Turn-over recovery of the spiked unit: counts down the flipped-over count;
 * at 0 it restores the normal defence and pose tables, clears status flag 1, plays the wake-up sound,
 * hops to the ground and turns the spike counter on part 1 back on; otherwise it keeps lying flipped.
 */
static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr))
    CALL(btlevtcmd_OffStatusFlag, LW(10), 1)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 18, -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, 1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack script of the crimson shell-backed unit: if it is lying flipped it gets up (wakeup_event);
 * otherwise it picks a target (after the item-use check),
 * jumps into its shell and spins up while rolling at the target, leaving dust puffs.
 * If the attack misses it rolls past the target and jumps back;
 * if it hits it deals damage with the guard-timing check and bounces off, then walks home.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        WAIT_FRAMES(30)
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_met_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_met_attack), LW(3), LW(4))
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
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_met_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_met_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_ATTACK2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 10)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 20)
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 0)
    DELETE_EVENT(LW(13))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_attack), 256, LW(5))
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
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 10)
    WAIT_MS(250)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_met_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_attack), 256, LW(5))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle script: sets the standard waiting pose from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Damage handler while it hangs on the ceiling:
 * runs the default damage script, and unless the hit knocked it out (damage flag 0x200) without a Life Shroom
 * revive (0x800) it runs ceil_fall_ready_event when it took damage while still on the ceiling, so it falls.
 */
static EVT_BEGIN(damage_event_ceil)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_GetTotalDamage, BTL_UNIT_SELF, LW(12))
    IF_INT_EQUAL(LW(12), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(ceil_fall_ready_event)
    END_IF
    RETURN
EVT_END()

/**
 * Counter-damage handler on the ceiling for the spiked unit:
 * leaves the ceiling state (ground pose and data tables, hit offsets, home position,
 * init_event2 for the ground form) and then applies the counter damage.
 */
static EVT_BEGIN(counter_damage_event_ceil)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 4194304)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 2097152)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, 17, 0)
#endif
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL_CHILD(init_event2)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    CALL_CHILD(subsetevt_counter_damage)
    RETURN
EVT_END()

/**
 * Makes the ceiling spiked unit fall: plays the fall sound, drops it to the ground with the landing sound,
 * swaps to the ground tables and runs init_event2,
 * then leaves it lying flipped over (turned tables, flipped-over count 1) after two bounces,
 * with its spike counter turned off.
 */
static EVT_BEGIN(ceil_fall_ready_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetJumpSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 20, LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEMET_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 4194304)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 2097152)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_turn))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, 17, 0)
#endif
    CALL_CHILD(init_event2)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_OnStatusFlag, LW(10), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 12, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 5, LW(2))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 1)
    RETURN
EVT_END()

/**
 * Attack script on the ceiling for the spiked unit:
 * picks a target, slides along the ceiling over it,
 * drops with the fall and landing sounds and hits it (guard check and damage), waits a second,
 * then jumps back down, restores the ground form (init_event2) and walks home.
 */
static EVT_BEGIN(attack_event_ceil)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_met_ceil_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_met_ceil_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(10), LW(11), LW(12))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(11), LW(12), 60, -1, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetJumpSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 20, LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEMET_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_ceil_attack), 256, LW(5))
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
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_ceil_attack), 256, LW(5))
    GOTO(98)
    LABEL(98)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 4194304)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 2097152)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, 17, 0)
#endif
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(7), 0, LW(9))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(7), 0, LW(9), 0, -1, 0)
    CALL_CHILD(init_event2)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle script for the ceiling form: sets the standard waiting pose from the unit's pose table. */
static EVT_BEGIN(wait_event_ceil)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
