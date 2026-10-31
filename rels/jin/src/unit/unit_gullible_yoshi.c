// Yoshi partner unit for the Doopliss fight in Creepy Steeple (placed off screen in the battle setup).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "unit/party/unit_party_yoshi.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"

// Declaration of the Yoshi partner unit's script helper that puts Yoshi's animation back to the player's chosen
// colour; defined in src/unit/party/unit_party_yoshi.c.
USER_FUNC(yoshi_original_color_anim_set);

BattleUnitKind unit_gullible_yoshi;
static BattleWeapon enemyWeapon_YoshiNormalAttack;
static BattleUnitDefense defence_yoshi;
static BattleUnitDefenseAttr defence_attr_yoshi;
static StatusVulnerability regist_yoshi;
static BattleDataEntry data_table_yoshi[2];
static BattleUnitKindPart parts_yoshi[1];
static EvtWord init_event_yoshi[24];
extern EvtWord damage_event_yoshi[];
#if VERSION <= VERSION_DEMO_US
static EvtWord dead_event_yoshi[156];
#else
static EvtWord dead_event_yoshi[177];
#endif
static EvtWord attack_event_yoshi[748];
#if VERSION <= VERSION_DEMO_US
static EvtWord wait_event_yoshi[6];
#else
static EvtWord wait_event_yoshi[7];
#endif

BattleUnitKind unit_gullible_yoshi = {
    82,
    "btl_un_gullible_yoshi",
    10,
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
    24,
    28,
    4,
    24,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
    18.2f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    24.0f,
    28.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_PARTY_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x10000000,
    &regist_yoshi,
    1,
    parts_yoshi,
    init_event_yoshi,
    data_table_yoshi,
};

static BattleWeapon enemyWeapon_YoshiNormalAttack = {
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
    weaponGetPowerFromGulliblePartyAttackLv, // hpDamageFn
    {1, 1, 1, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_DIMINISHING_BY_HIT | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
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

static BattleUnitDefense defence_yoshi = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr_yoshi = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist_yoshi = {60, 80, 70, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 70, 70, 0, 0, 100, 70, 100, 100, 0};
#else
static StatusVulnerability regist_yoshi = {60, 80, 70, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 90, 70, 0, 0, 100, 70, 100, 100, 0};
#endif

static BattleDataEntry data_table_yoshi[] = {
    {49, dead_event_yoshi},
    {0, NULL},
};

static BattleUnitKindPart parts_yoshi[] = {
    {1, "btl_un_yoshi", "c_babyyoshi", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_yoshi, &defence_attr_yoshi, 0x9, 0, pose_table_yoshi_stay},
};

/**
 * Init script of the Doopliss-controlled Yoshi.
 * Registers his wait, attack, damage and confusion handlers,
 * applies his original body colour animation and starts him waiting.
 */
static EVT_BEGIN(init_event_yoshi)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_yoshi))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_yoshi))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_yoshi))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(yoshi_original_color_anim_set, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage script of the Doopliss-controlled Yoshi:
 * if the hit carries damage code 1024 it sets GW(20)
 * so the fake Mario's phase script knows the partner was struck, then runs the default damage handling.
 */
EVT_BEGIN(damage_event_yoshi)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(20), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Defeat script of the Doopliss-controlled Yoshi.
 * He first walks back to his home position if he is away from it, then collapses.
 * With GW(19) at 0 (the fake Mario is still standing) the camera frames him
 * and his farewell lines (stg4_jin_26_03_yos and stg4_jin_26_04) play;
 * with GW(19) at 1 or 2 he only plays the collapse pose, waiting for GW(19) to reach 2 first.
 * He is then removed from the battle and GW(20) is set to 2 so the fake Mario's phase script knows he is gone.
 */
static EVT_BEGIN(dead_event_yoshi)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(3), LW(4), LW(5))
    SET_VALUE(LW(6), 1)
    IF_INT_EQUAL(LW(0), LW(3))
        IF_INT_EQUAL(LW(1), LW(4))
            IF_INT_EQUAL(LW(2), LW(5))
                SET_VALUE(LW(6), 0)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LW(6), 1)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    END_IF
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    SWITCH(GW(19))
        CASE_EQUAL(0)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 130, 58, 228, 130, 38, -20, 30, 11)
        WAIT_FRAMES(37)
        CALL(evt_msg_print, 2, STRING("stg4_jin_26_03_yos"), 0, BTL_UNIT_SELF)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_D_3"))
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_DIE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
#endif
        WAIT_MS(500)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 90, 58, 228, 90, 38, -20, 30, 11)
        WAIT_FRAMES(37)
        CALL(evt_msg_print, 2, STRING("stg4_jin_26_04"), 0, GW(16))
        WAIT_MS(200)
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_D_3"))
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_DIE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
#endif
        LOOP(0)
            IF_INT_EQUAL(GW(19), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_D_3"))
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_DIE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
#endif
    END_SWITCH
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 1)
    SET_VALUE(GW(20), 2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Attack script of the Doopliss-controlled Yoshi: a flutter-jump stomp.
 * After an item check he picks a target, runs in place, hops and flutter-jumps over it, spins,
 * and dives onto it. While the hit connects he bounces up and dives again for a random one to four total stomps.
 * A miss or block makes him tumble back, and he then walks home.
 */
static EVT_BEGIN(attack_event_yoshi)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(&enemyWeapon_YoshiNormalAttack))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
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
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    WAIT_FRAMES(20)
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 350)
    BEGIN_INLINE_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(3)
        END_LOOP
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_R_5"))
    WAIT_FRAMES(25)
    DELETE_EVENT(LW(13))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_J_1A"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
    ADD(LW(1), 35)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 25, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_3"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    ADD(LW(7), 40)
    SET_VALUE(LW(10), FLOAT(1.0f))
    BEGIN_INLINE_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 190, EVT_NULLPTR)
            WAIT_FRAMES(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 381, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 668, EVT_NULLPTR)
            WAIT_FRAMES(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 859, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 1145, EVT_NULLPTR)
            WAIT_FRAMES(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 1241, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 1527, EVT_NULLPTR)
            WAIT_FRAMES(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 1814, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 2100, EVT_NULLPTR)
            WAIT_FRAMES(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 2196, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), EVT_NULLPTR, 1742, EVT_NULLPTR)
            WAIT_FRAMES(6)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1R"), EVT_NULLPTR, 1527, EVT_NULLPTR)
            WAIT_FRAMES(7)
        END_LOOP
    END_INLINE_EVENT
    CALL(btl_yoshi_yoroyoro_jump_calc_param, BTL_UNIT_SELF, LW(6), LW(7), LW(8), LW(10), LW(9))
    CALL(btl_yoshi_yoroyoro_jump_move, BTL_UNIT_SELF, LW(6), LW(7), LW(8), LW(10), LW(9))
    DELETE_EVENT(LW(13))
    CALL(evt_sub_random, 4, LW(11))
    ADD(LW(11), 1)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 1048832, LW(5))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
    END_SWITCH
    IF_INT_LESS_OR_EQUAL(LW(10), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKR_A_2B"))
        WAIT_FRAMES(20)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKR_J_1A"))
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_J_1B"))
        SET_VALUE(LW(0), 1)
        SET_VALUE(LW(1), 9)
        MULTIPLY(LW(15), -40)
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 12, 0)
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        WAIT_FRAMES(15)
        LOOP(LW(0))
            SET_VALUE(LW(2), LW(1))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_YOSHI_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            LOOP(LW(2))
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(15))
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_1"))
        WAIT_FRAMES(15)
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_1"))
    END_IF
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 4, 0, 0, 0, -1)
    IF_INT_NOT_EQUAL(LW(5), 1)
        IF_INT_EQUAL(LW(5), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(5), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(5), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(15), LW(1))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        SUBTRACT(LW(15), LW(1))
        DIVIDE(LW(15), 10)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 0, 0, 0, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_D_1"))
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, -7, 0)
        CALL(evt_btl_camera_shake_h, 0, 4, 0, 10, 13)
        WAIT_FRAMES(40)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_5"))
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, 0, 0)
        WAIT_FRAMES(54)
        GOTO(95)
    END_IF
    IF_INT_LESS(LW(10), LW(11))
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 0, LW(5))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
        ADD(LW(1), 40)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        ADD(LW(10), 1)
        GOTO(10)
    ELSE
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    LABEL(90)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_D_1"))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    WAIT_FRAMES(20)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays Yoshi's idle pose from his pose table. */
static EVT_BEGIN(wait_event_yoshi)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
#if VERSION <= VERSION_DEMO_US
EVT_END()
#else
EVT_END_PAD()
#endif
