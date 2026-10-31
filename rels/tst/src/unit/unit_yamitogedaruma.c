// Battle unit Dark Bristle (`yamitogedaruma`): tst.rel's copy of rels/jon/src/unit/unit_yamitogedaruma.c.
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

BattleUnitKind unit_yamitogedaruma;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_turn[15];
static BattleDataEntry data_table[6];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_togedaruma_attack;
static EvtWord init_event[21];
static EvtWord dmg_avoid_counter_thorn_head_event[63];
static EvtWord dmg_avoid_counter_thorn_front_event[121];
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[131];
static EvtWord attack_event[358];
static EvtWord wait_event[102];

BattleUnitKind unit_yamitogedaruma = {
    165,
    "btl_un_yamitogedaruma",
    8,
    0,
    1,
    1,
#if VERSION <= VERSION_DEMO_US
    40,
    0,
    1,
    70,
    4,
#else
    34,
    1,
    2,
    70,
    2,
#endif
    50,
    9999,
    46,
    40,
    4,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    0.0f,
    20.0f,
    26.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    46.0f,
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
    "SFX_ENM_TOGEDA_DAMAGED1",
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

static BattleUnitDefense defence = {{4, 4, 4, 4, 4}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static BattleUnitDefense defence_turn = {0};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {20, 70, 30, 100, 30, 100, 100, 50, 100, 50, 100, 50, 100, 50, 50, 30, 55, 100, 50, 100, 100, 30};
#else
static StatusVulnerability regist = {20, 80, 20, 100, 20, 100, 100, 40, 100, 50, 100, 50, 100, 100, 40, 30, 20, 100, 40, 100, 100, 30};
#endif

static PoseTableEntry pose_table[] = {
    {1, "TGD_N_1"},
    {2, "TGD_I_1"},
    {9, "TGD_I_1"},
    {5, "TGD_K_1"},
    {4, "TGD_X_1"},
    {3, "TGD_X_1"},
    {28, "TGD_S_4"},
    {29, "TGD_Q_1"},
    {30, "TGD_Q_1"},
    {31, "TGD_S_2"},
    {39, "TGD_D_1"},
    {50, "TGD_A_1"},
    {40, "TGD_S_4"},
    {42, "TGD_S_4"},
    {56, "TGD_X_1"},
    {57, "TGD_X_1"},
    {BTL_POSE_TALK, "TGD_T_1"},
    {BTL_POSE_STAY_DEFAULT, "TGD_S_4"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "TGD_N_2"},
    {2, "TGD_I_2"},
    {9, "TGD_Z_4"},
    {5, "TGD_K_2"},
    {4, "TGD_X_2"},
    {3, "TGD_X_2"},
    {28, "TGD_S_5"},
    {29, "TGD_Q_2"},
    {30, "TGD_Q_2"},
    {31, "TGD_S_3"},
    {39, "TGD_D_2"},
    {56, "TGD_X_2"},
    {57, "TGD_X_2"},
    {BTL_POSE_TALK, "TGD_S_5"},
    {BTL_POSE_STAY_DEFAULT, "TGD_S_5"},
};

static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {39, dmg_avoid_counter_thorn_front_event},
    {38, dmg_avoid_counter_thorn_front_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_yamitogedaruma", "c_togedaruma_b", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2009, 0x7, pose_table},
};

static BattleWeapon weapon_togedaruma_attack = {
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
#if VERSION <= VERSION_DEMO_US
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#else
    {8, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
#endif
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY, // counterResistFlags
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

/**
 * Init event of the Dark Bristle: registers its wait,
 * attack and damage events (attack_event also handles confusion) and starts waiting.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data-table event 37, run when an attacker is hurt by the spikes on top:
 * after 30 frames a toge_flush flash appears over its head (higher when Huge, lower when Tiny)
 * and it waits 60 more frames.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 58)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 32)
        GOTO(90)
    END_IF
    ADD(LW(1), 45)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/**
 * Data-table events 38 and 39, run when an attacker is hurt by the spikes in front:
 * with SFX_ENM_TOGEDA_MOVE1 it plays TGD_J_1 then TGD_J_2 (TGD_J_3 and TGD_J_4 while flipped),
 * and after 30 frames a toge_flush flash appears in front of it (further out and higher when Huge,
 * closer when Tiny).
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_front_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 17, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_3"))
            WAIT_FRAMES(60)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_4"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_1"))
            WAIT_FRAMES(60)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_2"))
        END_IF
    END_SIBLING_EVENT
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 53)
        ADD(LW(1), 26)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 33)
        ADD(LW(1), 16)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 43)
    ADD(LW(1), 21)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/** Damage event of the Dark Bristle: runs the default damage reaction (btldefaultevt_Damage) for its body part. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data-table event 13: flips the Dark Bristle over.
 * Switches to the overturned defence and pose tables,
 * sets the flipped status flag and the overturned counter to 2,
 * plays SFX_ENM_INSIDE1 and hops (rolling half a turn unless it was already flipped),
 * then rests on its back at height 10 and makes that its home position.
 */
static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(12))
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 2)
    WAIT_FRAMES(2)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_ENM_INSIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("TGD_S_1"))
    IF_INT_LESS_OR_EQUAL(LW(12), 0)
        SET_VALUE(LW(12), 0)
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 10, 0)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                IF_INT_GREATER_OR_EQUAL(LW(12), 10)
                    BREAK_LOOP
                END_IF
                ADD(LW(12), 1)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, -18)
            END_LOOP
        END_SIBLING_EVENT
    END_IF
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 25, -1)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("TGD_S_5"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    RETURN
EVT_END()

/**
 * Run instead of a normal attack while the Dark Bristle is flipped: counts the overturned counter down.
 * While it is still above 0 it just goes back to waiting;
 * at 0 it restores its normal defence and pose tables, clears the flipped status flag,
 * rolls back upright with a hop (SFX_ENM_TOGEDA_MOVE6) and sets its home position back on the floor.
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
    CALL(btlevtcmd_OffStatusFlag, LW(10), 1)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    SET_VALUE(LW(12), 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 10, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            IF_INT_GREATER_OR_EQUAL(LW(12), 10)
                BREAK_LOOP
            END_IF
            ADD(LW(12), 1)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, -18)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_ENM_TOGEDA_MOVE6"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("TGD_S_4"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack event of the Dark Bristle. While flipped it runs wakeup_event instead.
 * Otherwise it uses an item if it decides to, or picks the front-most target (the first-attack target on a first
 * strike), rears up (TGD_J_1) and charges at it (TGD_A_1).
 * A dodge or miss sends it hopping onto the target's spot, where it sits (TGD_N_1) for 1.5 s;
 * a hit shakes the camera and damages the target (8 damage, 7 in the demos). It then hops home.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_togedaruma_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_togedaruma_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_togedaruma_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_togedaruma_attack))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_1"))
    WAIT_FRAMES(10)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_A_1"))
    WAIT_MS(400)
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(7.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_togedaruma_attack), 256, LW(5))
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_A_1"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 0, FLOAT(0.099609375f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), FLOAT(60.0f), -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_N_1"))
    WAIT_MS(1500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_togedaruma_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_togedaruma_attack), 256, LW(5))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEDA_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(5.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_J_2"))
    WAIT_FRAMES(15)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("TGD_S_4"))
    WAIT_MS(400)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Wait event of the Dark Bristle: plays the idle pose,
 * then every frame turns off its pre-emptive front-spike counter while it is asleep, stopped, dizzy, poisoned,
 * confused or frozen (statuses 1-5 and 9), and turns it back on otherwise.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    SET_VALUE(LW(15), 0)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 3, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 5, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 9, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 2)
    ELSE
        CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, 2)
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()
