// unit_monban: Gus (monban, gatekeeper) battle unit, fought in Rogueport west side.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "data_tables.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "evt/evt_story.h"

BattleUnitKind unit_monban;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
static BattleWeapon weapon_monban_attack;
static BattleWeapon weapon_monban_throw_attack;
static EvtWord init_event[46];
static EvtWord dmg_avoid_counter_thorn_head_event[76];
static EvtWord damage_event[10];
static EvtWord phase_event[68];
static EvtWord attack_event[52];
static EvtWord normal_attack_event[391];
static EvtWord throw_attack_event[343];
static EvtWord wait_event[6];

BattleUnitKind unit_monban = {
    7,
    "btl_un_monban",
    20,
    0,
    1,
    1,
    45,
    0,
    0,
    100,
    0,
    100,
    9,
    31,
    46,
    0,
    46,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.5f,
    0.0f,
    0.0f,
    15.5f,
    29.9f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    28.0f,
    40.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_MONBAN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {70, 70, 60, 40, 60, 40, 100, 60, 30, 60, 30, 60, 40, 60, 60, 0, 60, 100, 60, 70, 70, 50};
#else
static StatusVulnerability regist = {90, 80, 80, 40, 90, 40, 100, 70, 30, 90, 30, 90, 40, 95, 70, 0, 60, 100, 70, 70, 70, 50};
#endif

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_2"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_1"},
    {39, "D_1"},
    {50, "A_1"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_2"},
};

static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_monban", "c_monban", 0.0f, 0.0f, 0.0f, 8.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
    {2, "btl_un_monban", "c_monban", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static BattleWeapon weapon_monban_attack = {
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
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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

static BattleWeapon weapon_monban_throw_attack = {
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
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_GROUNDS_WINGED, // special
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

static PoseSoundTiming pose_sound_timing_table[] = {
    {"S_2", 0.6666667f, NULL, "SFX_ENM_MONBAN_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init event of Gus: installs phase, attack, damage and confusion events,
 * sets the run and walk sounds and the pose sound timing table.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE2R"), STRING("SFX_ENM_MONBAN_MOVE2L"), 0, 5, 5)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE2R"), STRING("SFX_ENM_MONBAN_MOVE2L"), 0, 10, 10)
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Spark effect (toge_flush) shown when an attack on Gus's spiked head is turned away:
 * it waits 30 frames, then places the flash above his head at a height that depends on whether he has status 10
 * or 11.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 18)
        ADD(LW(1), 60)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 10)
        ADD(LW(1), 33)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 14)
    ADD(LW(1), 48)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/** Damage event of Gus: runs the default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Phase event of Gus: the first time his turn starts while Mario has 5 or fewer HP,
 * the camera moves in and he taunts with gor_02_008_01 (flag GSWF_GUS_TAUNT_SHOWN keeps it from repeating).
 */
static EVT_BEGIN(phase_event)
    IF_INT_EQUAL(GSWF(GSWF_GUS_TAUNT_SHOWN), 0)
        CALL(btlevtcmd_GetHp, BTL_UNIT_MARIO, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 5)
            CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_PLAYER)
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
                IF_INT_NOT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL(evt_btl_camera_set_mode, 0, 3)
                    CALL(evt_btl_camera_set_moveto, 0, 88, 88, 432, 88, 60, 0, 30, 11)
                    WAIT_FRAMES(30)
                    CALL(evt_msg_print, 2, STRING("gor_02_008_01"), 0, BTL_UNIT_SELF)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    SET_VALUE(GSWF(GSWF_GUS_TAUNT_SHOWN), 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    WAIT_FRAMES(60)
                END_IF
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Attack event of Gus: uses an enemy item if he has one,
 * otherwise 50% weapon_monban_attack (normal_attack_event)
 * and 50% weapon_monban_throw_attack (throw_attack_event).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 50)
        SET_VALUE(LW(9), PTR(&weapon_monban_attack))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_monban_throw_attack))
    CALL_CHILD(throw_attack_event)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Gus's melee attack: picks a target, runs at it, hops in with SFX_ENM_MONBAN_MOVE sounds, strikes,
 * and the pre-damage check decides between a dodge and a hit with the action-command result;
 * afterwards he laughs (SFX_ENM_MONBAN_LAUGH1) and returns home.
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1"))
    WAIT_FRAMES(20)
    BEGIN_SIBLING_EVENT
        LOOP(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE2R"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(5)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE2L"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(5)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SET_VALUE(LW(5), 30)
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(5), LW(6))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), LW(5))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
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
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    WAIT_FRAMES(60)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE2R"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_MOVE2L"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("T_1"))
    LOOP(3)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_LAUGH1"), EVT_NULLPTR, 0, LW(15))
        WAIT_FRAMES(10)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_2"))
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Gus's ranged attack (weapon_monban_throw_attack):
 * picks a target and throws something at it (SFX_ENM_MONBAN_THROW1 and 2, poses A_2 and A_3);
 * the pre-damage check decides between a dodge and a hit, then he laughs and returns to idle.
 */
static EVT_BEGIN(throw_attack_event)
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_THROW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2"))
    WAIT_FRAMES(28)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_THROW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 33554432)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("A_3"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
    ADD(LW(1), 10)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, 2, 10, 0, 0)
    IF_INT_EQUAL(LW(15), -1)
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, -45)
    ELSE
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 180, -45)
    END_IF
    BEGIN_SIBLING_EVENT
        LOOP(30)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 3)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 30, 0, FLOAT(0.5f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 30, -1)
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
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 33554432)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 33554432)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(2)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("T_1"))
    LOOP(3)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_LAUGH1"), EVT_NULLPTR, 0, LW(15))
        WAIT_FRAMES(10)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_2"))
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of Gus: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
