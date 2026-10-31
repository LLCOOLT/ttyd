// Flurrie (clauda) partner unit for the Doopliss fight in Creepy Steeple (placed off screen in the battle setup).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "unit/party/unit_party_clauda.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"

BattleUnitKind unit_gullible_clauda;
static BattleWeapon enemyWeapon_ClaudaNormalAttack;
static BattleUnitDefense defence_clauda;
static BattleUnitDefenseAttr defence_attr_clauda;
static StatusVulnerability regist_clauda;
static BattleDataEntry data_table_clauda[2];
static BattleUnitKindPart parts_clauda[1];
static EvtWord init_event_clauda[50];
extern EvtWord damage_event_clauda[];
#if VERSION <= VERSION_DEMO_JP
static EvtWord dead_event_clauda[156];
#else
static EvtWord dead_event_clauda[177];
#endif
static EvtWord attack_event_clauda[393];
static EvtWord wait_event_clauda[6];

/**
 * Unit kind of the Flurrie double:
 * 10 HP, level 0, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_gullible_clauda = {
    83,
    "btl_un_gullible_clauda",
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
    42,
    46,
    12,
    40,
    0.0f,
    23.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    21.0f,
    29.9f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    42.0f,
    46.0f,
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
    UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist_clauda,
    1,
    parts_clauda,
    init_event_clauda,
    data_table_clauda,
};

/**
 * Flurrie double's ClaudaNormalAttack:
 * damage scaled to the party level to a single target, a jump-style hit.
 */
static BattleWeapon enemyWeapon_ClaudaNormalAttack = {
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
    {2, 4, 6, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    10, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED, // special
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

/** Defence of the Flurrie double's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence_clauda = {{0, 0, 0, 0, 0}};

/** Defence attributes of the Flurrie double's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_attr_clauda = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Flurrie double in the demo, as a percent of the normal chance:
 * immune to fright, gale force, instant kill;
 * sleep 60%, stop 80%, freeze 70% (and 7 other statuses lowered).
 */
static StatusVulnerability regist_clauda = {60, 80, 70, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 70, 70, 0, 0, 100, 70, 100, 100, 0};
#else
/**
 * Status vulnerability of the Flurrie double in the retail versions, as a percent of the normal chance:
 * immune to fright, gale force, instant kill; sleep 60%, stop 80%, freeze 70%;
 * raised chance for dizzy 105% (and 6 other statuses lowered).
 */
static StatusVulnerability regist_clauda = {60, 80, 105, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 90, 70, 0, 0, 100, 70, 100, 100, 0};
#endif

/** Event table of the Flurrie double: its defeat script. */
static BattleDataEntry data_table_clauda[] = {
    {49, dead_event_clauda},
    {0, NULL},
};

/** Body part of the Flurrie double: a single part using the model "c_windy". */
static BattleUnitKindPart parts_clauda[] = {
    {1, "btl_un_clauda", "c_windy", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_clauda, &defence_attr_clauda, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table_clauda_stay},
};

/**
 * Init script of the Doopliss-controlled Flurrie.
 * Registers her wait, attack, damage and confusion handlers,
 * sets the hang (walk, run, dive) and jump sound effects, and starts her waiting.
 */
static EVT_BEGIN(init_event_clauda)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_clauda))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_clauda))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_clauda))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 3)
    CALL(btlevtcmd_SetDiveSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage script of the Doopliss-controlled Flurrie:
 * if the hit carries damage code 1024 it sets GW(20)
 * so the fake Mario's phase script knows the partner was struck, then runs the default damage handling.
 */
EVT_BEGIN(damage_event_clauda)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(20), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Defeat script of the Doopliss-controlled Flurrie.
 * She first walks back to her home position if she is away from it, then collapses.
 * With GW(19) at 0 (the fake Mario is still standing) the camera frames her
 * and her farewell lines (stg4_jin_26_03_win and stg4_jin_26_04) play;
 * with GW(19) at 1 or 2 (the fake Mario was hit by damage code 1024,
 * or is already down) she only plays the collapse pose, waiting for GW(19) to reach 2 first.
 * She is then removed from the battle and GW(20) is set to 2 so the fake Mario's phase script knows she is gone.
 */
static EVT_BEGIN(dead_event_clauda)
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
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
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
        CALL(evt_msg_print, 2, STRING("stg4_jin_26_03_win"), 0, BTL_UNIT_SELF)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_D_3"))
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
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_D_3"))
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
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_D_3"))
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
 * Attack script of the Doopliss-controlled Flurrie: her body slam.
 * She uses an item if the enemy item check says so;
 * otherwise she picks a target, jumps onto it (aiming a little off when the action command is not successful),
 * squashes flat on impact with a camera shake, then walks back home.
 * Missed or blocked hits trigger the target's avoid reaction.
 */
static EVT_BEGIN(attack_event_clauda)
    // She may use an enemy item instead of attacking.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(&enemyWeapon_ClaudaNormalAttack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Target: she picks one for her body slam.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    // The attack is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // Wind-up: Flurrie crouches (PWD_A1_1) and then leaps into the air.
    WAIT_MS(400)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_GetResultAC, LW(5))
    IF_BITS_CLEAR(LW(5), 2)
        // She aims a little off the mark when the action command is not successful.
        CALL(evt_sub_random, 40, LW(5))
        SUBTRACT(LW(5), 20)
        ADD(LW(0), LW(5))
        CALL(evt_sub_random, 20, LW(5))
        SUBTRACT(LW(5), 10)
        ADD(LW(1), LW(5))
    END_IF
    // She comes down on the target; the pre-damage check decides between a dodge and a hit.
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -1)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        // Impact: she lands flat (PWD_A1_2, PWD_D_3) and the camera shakes as the slam hits for its damage.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_2"))
        CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_D_3"))
        WAIT_FRAMES(30)
        GOTO(95)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(evt_btl_camera_shake_h, 0, 8, 0, 30, 13)
    // She squashes and swells back to full size.
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.39941406f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(0.39941406f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    WAIT_MS(700)
    // She walks back to her home position.
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays Flurrie's idle pose from her pose table. */
static EVT_BEGIN(wait_event_clauda)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
