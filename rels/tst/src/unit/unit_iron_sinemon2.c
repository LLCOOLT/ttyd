// Battle unit Iron Shinemon (second variant) (`iron_sinemon2`): tst.rel's copy of rels/tou2/src/unit/unit_iron_sinemon2.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "mario/mario_pouch.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "evt/evt_msg.h"
#include "version.h"
#include "evt/evt_story.h"

static USER_FUNC(get_id);
static USER_FUNC(yoshi_exist);

BattleUnitKind unit_iron_sinemon2;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_iron_sinemon_attack;
#if VERSION <= VERSION_DEMO_US
static PoseTableEntry pose_table[17];
#else
static PoseTableEntry pose_table[18];
#endif
static BattleDataEntry data_table[3];
static EvtWord init_event2[18];
static EvtWord init_event_sub[47];
static EvtWord dmg_avoid_counter_thorn_head_event[76];
static EvtWord damage_event[102];
#if VERSION <= VERSION_DEMO_US
static EvtWord phase_event[164];
#else
static EvtWord phase_event[188];
#endif
static EvtWord attack_event[385];
static EvtWord wait_event[6];

BattleUnitKind unit_iron_sinemon2 = {
    62,
    "btl_un_iron_sinemon2",
    6,
    0,
    1,
    1,
    18,
    0,
    2,
    100,
    1,
    70,
    9,
    52,
    54,
    4,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    0.0f,
    16.0f,
    36.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    52.0f,
    54.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_ISIN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x40000,
    &regist,
    1,
    parts,
    init_event2,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{4, 4, 4, 4, 4}};

static BattleUnitDefense defence_turn = {0};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_iron_sinemon2", "c_sinemon_m", 0.0f, 0.0f, 0.0f, 0.0f, 37.0f, 0.0f, 0.0f, 45.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
};

static BattleWeapon weapon_iron_sinemon_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

static PoseTableEntry pose_table[] = {
    {1, "SIN_N_1"},
    {2, "SIN_Y_1"},
    {9, "SIN_Y_1"},
    {5, "SIN_K_1"},
    {4, "SIN_I_1"},
    {3, "SIS_I_1"},
    {28, "SIN_S_1"},
    {29, "SIN_Q_1"},
    {30, "SIN_Q_1"},
    {31, "SIN_A_1a"},
    {39, "SIN_D_1"},
    {50, "SIN_A_1a"},
    {40, "SIN_W_1"},
    {42, "SIN_R_1"},
#if VERSION >= VERSION_JP
    {BTL_POSE_TALK, "SIN_T_1"},
#endif
    {56, "SIN_I_1"},
    {57, "SIN_I_1"},
    {BTL_POSE_STAY_DEFAULT, "SIN_S_1"},
};

static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Init script of the first Iron Cleft of the pair:
 * sets unit work 0 to 0 (first of the pair), stores the other Iron Cleft's id in unit work 1 (from get_id)
 * and runs init_event_sub.
 */
static EVT_BEGIN(init_event1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(get_id, LW(0), LW(1))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(1))
    CALL_CHILD(init_event_sub)
    RETURN
EVT_END()

/**
 * Init script of the second Iron Cleft of the pair:
 * sets unit work 0 to 1 (second of the pair), stores the other Iron Cleft's id in unit work 1 (from get_id)
 * and runs init_event_sub.
 */
static EVT_BEGIN(init_event2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
    CALL(get_id, LW(0), LW(1))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    CALL_CHILD(init_event_sub)
    RETURN
EVT_END()

/**
 * Shared part of the Iron Clefts' init: installs the wait, phase, attack,
 * damage and confusion handlers (confusion reuses the attack), scales the unit to 1.5 x 1.5,
 * sets its walk and run sounds and starts the wait event.
 */
static EVT_BEGIN(init_event_sub)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetBaseScale, BTL_UNIT_SELF, FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.0f))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE1"), STRING("SFX_BOSS_ISIN_MOVE2"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE1"), STRING("SFX_BOSS_ISIN_MOVE2"), 0, 7, 7)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Spike spark shown when an attacker is hurt by (or avoids) the spiked head:
 * waits 30 frames, then spawns the toge_flush effect in front of and above the unit (52 up,
 * 67 when Huge and 37 when Tiny, with the front offset scaled to match).
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
        ADD(LW(1), 67)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 14)
        ADD(LW(1), 37)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    ADD(LW(1), 52)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Damage handler of the Iron Cleft.
 * It runs the default damage script; then, the first time an Iron Cleft of the pair takes real damage (and only
 * once ever, tracked by GSWF_TOU_IRON_CLEFTS_WEAKNESS_SEEN),
 * the camera moves in and the two Iron Clefts speak the weakness lines stg3_tou_272 and stg3_tou_273
 * before the flag is set.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TOU_IRON_CLEFTS_WEAKNESS_SEEN), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetTotalDamage, BTL_UNIT_SELF, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 91, 74, 334, 91, 52, 0, 30, 4)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_msg_print, 2, STRING("stg3_tou_272"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    CALL(evt_msg_print, 2, STRING("stg3_tou_273"), 0, LW(0))
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    SET_VALUE(GSWF(GSWF_TOU_IRON_CLEFTS_WEAKNESS_SEEN), 1)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Guess: Phase script of the Iron Cleft pair.
 * Only the first of the pair runs it (unit work 0 = 0),
 * and only until the pair has been beaten (GSWF_TOU_IRON_CLEFTS_BEATEN).
 * On the first turn before the player's turn it runs the intro:
 * the camera moves in, the partner and the Iron Clefts talk (lines stg3_tou_266 and 267 the first time only,
 * then stg3_tou_268/269 or, if Yoshi is the partner, stg3_tou_270/271),
 * and GSWF_TOU_IRON_CLEFTS_INTRO_SEEN is set.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
#if VERSION <= VERSION_DEMO_US
    DEBUG_PUT_MSG(STRING("ぺぺぺまん２"))
#endif
    IF_INT_EQUAL(GSWF(GSWF_TOU_IRON_CLEFTS_BEATEN), 1)
        RETURN
    END_IF
#if VERSION <= VERSION_DEMO_US
    DEBUG_PUT_MSG(STRING("ぺぺぺまん３"))
#endif
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
#if VERSION <= VERSION_DEMO_US
        DEBUG_PUT_MSG(STRING("ぺぺぺまん４"))
#endif
        CALL(btlevtcmd_get_turn, LW(0))
        IF_INT_EQUAL(LW(0), 1)
#if VERSION <= VERSION_DEMO_US
            DEBUG_PUT_MSG(STRING("ぺぺぺまん５"))
#endif
            CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_PARTNER)
            CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_prilimit, 1)
            CALL(evt_btl_camera_set_mode, 1, 3)
            CALL(evt_btl_camera_set_moveto, 1, -104, 74, 334, -102, 52, 0, 30, 4)
            WAIT_FRAMES(30)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            IF_INT_EQUAL(GSWF(GSWF_TOU_IRON_CLEFTS_INTRO_SEEN), 0)
                CALL(evt_msg_print_battle_party, STRING("stg3_tou_266"))
            ELSE
                CALL(evt_msg_print_battle_party, STRING("stg3_tou_267"))
            END_IF
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_moveto, 1, 91, 74, 334, 91, 52, 0, 30, 4)
            WAIT_FRAMES(30)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(yoshi_exist, LW(0))
            IF_INT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_JP
                CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
                CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY_DEFAULT)
#endif
                CALL(evt_msg_print, 2, STRING("stg3_tou_268"), 0, BTL_UNIT_SELF)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
#if VERSION >= VERSION_JP
                CALL(btlevtcmd_SetTalkPoseType, LW(0), BTL_POSE_TALK)
                CALL(btlevtcmd_SetStayPoseType, LW(0), BTL_POSE_STAY_DEFAULT)
#endif
                CALL(evt_msg_print, 2, STRING("stg3_tou_269"), 0, LW(0))
            ELSE
#if VERSION >= VERSION_JP
                CALL(btlevtcmd_SetTalkPoseType, BTL_UNIT_SELF, BTL_POSE_TALK)
                CALL(btlevtcmd_SetStayPoseType, BTL_UNIT_SELF, BTL_POSE_STAY_DEFAULT)
#endif
                CALL(evt_msg_print, 2, STRING("stg3_tou_270"), 0, BTL_UNIT_SELF)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
#if VERSION >= VERSION_JP
                CALL(btlevtcmd_SetTalkPoseType, LW(0), BTL_POSE_TALK)
                CALL(btlevtcmd_SetStayPoseType, LW(0), BTL_POSE_STAY_DEFAULT)
#endif
                CALL(evt_msg_print, 2, STRING("stg3_tou_271"), 0, LW(0))
            END_IF
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            IF_INT_EQUAL(GSWF(GSWF_TOU_IRON_CLEFTS_INTRO_SEEN), 0)
                SET_VALUE(GSWF(GSWF_TOU_IRON_CLEFTS_INTRO_SEEN), 1)
            END_IF
            CALL(evt_btl_camera_set_prilimit, 0)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Attack script of the Iron Cleft: it picks a target, walks toward it with the heavy step sounds,
 * curls up (pose type
 * 50) for 750 ms and rolls into it at speed 3 (weapon_iron_sinemon_attack). A miss lets it run past; a hit shakes the
 * camera and applies the damage with the guard-timing check.
 * It then hops twice with camera shakes and walks home.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_iron_sinemon_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_iron_sinemon_attack), LW(3), LW(4))
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
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_iron_sinemon_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_iron_sinemon_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        LOOP(0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(7)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    WAIT_MS(750)
    DELETE_EVENT(LW(14))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    SUBTRACT(LW(2), FLOAT(30.0f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 25)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_iron_sinemon_attack), 256, LW(5))
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
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 75)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    WAIT_MS(500)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_noshake, 0)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_iron_sinemon_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_iron_sinemon_attack), 256, LW(5))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(1.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 75)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 20, 0)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 100)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 20, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_ISIN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(evt_btl_camera_noshake, 0)
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
 * Script helper: args[0] and args[1] receive the unit indices of the two Shinemon kinds 0x3D
 * and 0x3E on the field (left unset if a kind is missing).
 */
static USER_FUNC(get_id) {
    EvtWord* args = event->args;
    s32 i;
    s32 id1;
    s32 id2;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL) {
            if (unit->currentKind == 0x3D) {
                id1 = i;
            }
            if (unit->currentKind == 0x3E) {
                id2 = i;
            }
        }
    }
    evtSetValue(event, args[0], id1);
    evtSetValue(event, args[1], id2);
    return EVT_RETURN_DONE;
}
/** Script helper: args[0] receives 1 when Yoshi is in the party data (partyData[4] flag 1 set), else 0. */
static USER_FUNC(yoshi_exist) {
    EvtWord* args = event->args;
    PouchData* pouch = pouchGetPtr();
    s32 exist = 0;

    if (pouch->partyData[4].flags & 1) {
        exist = 1;
    }
    evtSetValue(event, args[0], exist);
    return EVT_RETURN_DONE;
}
