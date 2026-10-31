// unit_lecture_frankli: Professor Frankly in the action-command tutorial battle.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_audience.h"
#include "evt/evt_msg.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_sub.h"
#include "version.h"

// Unit work slots (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_LECTURE_FRANKLI_PARTNER = 0,    // read as the unit id of the partner who answers him (never written here)
    UW_LECTURE_FRANKLI_STEP = 1,       // lesson step (0 to 9) that phase_event and Mario's scripts follow
    UW_LECTURE_FRANKLI_TIMING = 2,     // Mario's practice press: 1 nicely done, 2 a little early, 3 a little late
    UW_LECTURE_FRANKLI_TIMING_OLD = 3, // read in step 5 (4 or 7 nice, 5 early, 6 late); never written here
};

BattleUnitKind unit_lecture_frankli;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
BattleWeapon _lec_weapon_jump;
BattleWeapon _lec_weapon_hammer;
static BattleDataEntry data_table[4];
static BattleUnitKindPart parts[1];
static EvtWord init_event[38];
static EvtWord damage_event[10];
static EvtWord phase_event[681];
static EvtWord attack_event[5];
static EvtWord wait_event[6];
extern EvtWord lecAttackEvent_Jump[];
extern EvtWord lecAttackEvent_Hammer[];
extern EvtWord lecture_end_event[];

/**
 * Unit kind of Prof. Frankly:
 * 10 HP, level 1, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_lecture_frankli = {
    178,
    "btl_un_frankli",
    10,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    28,
    24,
    5,
    25,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    30.0f,
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
    15.6f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of Prof. Frankly's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of Prof. Frankly's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Status vulnerability of Prof. Frankly: immune to every status. */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Pose table of Prof. Frankly:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table[] = {
    {27, "D_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {31, "D_2"},
    {BTL_POSE_DAMAGE, "D_2"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Prof. Frankly's jump: damage from Mario's level to a single target, a jump-style hit. */
BattleWeapon _lec_weapon_jump = {
    "btl_wn_mario_normal_jump", // name
#if VERSION >= VERSION_US
    167, // icon
#else
    159, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_normal_jump", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromMarioJumpLv, // hpDamageFn
    {1, 1, 2, 2, 3, 3, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_jump", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ATTACK_FX | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    lecAttackEvent_Jump, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Prof. Frankly's hammer: damage from Mario's level to a single target, a hammer-style hit. */
BattleWeapon _lec_weapon_hammer = {
    "btl_wn_mario_normal_hammer", // name
#if VERSION >= VERSION_US
    164, // icon
#else
    156, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_normal_hammer", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromMarioHammerLv, // hpDamageFn
    {1, 2, 2, 4, 3, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_hammer", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_ATTACK_FX | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    lecAttackEvent_Hammer, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Event table of Prof. Frankly: the jump and hammer practice weapons
 *  and the end-of-lecture script (the tags are one higher in the retail versions).
 */
static BattleDataEntry data_table[] = {
#if VERSION <= VERSION_DEMO_US
    {67, &_lec_weapon_jump},
    {68, &_lec_weapon_hammer},
    {69, lecture_end_event},
#else
    {68, &_lec_weapon_jump},
    {69, &_lec_weapon_hammer},
    {70, lecture_end_event},
#endif
    {0, NULL},
};

/** Body part of Prof. Frankly: a single part using the model "c_kuri_h". */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_frankli", "c_kuri_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_TARGETABLE | PART_ATTR_UNTATTLEABLE, 0, pose_table},
};

/**
 * Init event of Professor Frankly in the action-command tutorial:
 * installs phase, attack, damage and confusion events,
 * forbids movement and starts the lesson state (unit work 1) at 0.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, 0)
    CALL(btlevtcmd_onoff_battleflag, 1, 4096)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of Professor Frankly in the tutorial: runs the default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Phase event that scripts the action-command lesson: unit work 1 is the step (0 to 9).
 * Each step waits for the right phase and then has Frankly talk (mac_0_b_t2_000 to 023) with the camera framed
 * on Mario or Goombella, then moves to the next step;
 * the last steps repeat prompts depending on how many tries the player has made.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        // Step 0, before the player's phase: Frankly introduces the Jump action command
        // and asks Mario to jump on an enemy.
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, 1)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 0, 58, 256, 0, 41, 0, 30, 11)
            WAIT_MS(500)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_000"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_onoff_battleflag, 1, 16777216)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_MARIO)
            RETURN
        END_IF
        CASE_EQUAL(2)
        // Step 1, after Mario's jump: Frankly points out the NICE rating,
        // then asks Goombella to take her turn and she answers.
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, 3)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_003"), 0, BTL_UNIT_SELF)
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 0, 180, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 180, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_004"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_PARTNER, LW(3))
            CALL(btlevtcmd_StopWaitEvent, LW(3))
            CALL(btlevtcmd_SetTalkPose, LW(3), STRING("PKR_T_1"))
            CALL(btlevtcmd_SetStayPose, LW(3), STRING("PKR_S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_005"), 0, LW(3))
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_MARIO)
            BEGIN_INLINE_EVENT
                CALL(evt_sub_intpl_init, 5, 180, 0, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
            END_INLINE_EVENT
            RETURN
        END_IF
        CASE_EQUAL(4)
        // Step 2, before the player's phase: Frankly explains the Guard action command Mario just did.
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, 5)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_007"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_onoff_battleflag, 0, 16777216)
            CALL(btlevtcmd_onoff_battleflag, 1, 33554432)
            RETURN
        END_IF
        CASE_EQUAL(6)
        // Step 3, after the attack: Frankly praises the Action Command,
        // then asks Goombella to attack Mario once more for the Superguard lesson.
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, 7)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 180, 0, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, 0, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_011"), 0, BTL_UNIT_SELF)
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 0, 180, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 180, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_012"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_PARTNER, LW(3))
            CALL(btlevtcmd_StopWaitEvent, LW(3))
            CALL(btlevtcmd_SetTalkPose, LW(3), STRING("PKR_T_1"))
            CALL(btlevtcmd_SetStayPose, LW(3), STRING("PKR_S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_013"), 0, LW(3))
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_MARIO)
            BEGIN_INLINE_EVENT
                CALL(evt_sub_intpl_init, 5, 180, 0, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
            END_INLINE_EVENT
            RETURN
        END_IF
        CASE_EQUAL(8)
        // Step 4, before the player's phase: Frankly explains the Superguard
        // and offers more practice (a yes or no choice).
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_LECTURE_FRANKLI_STEP, 9)
            CALL(btlevtcmd_onoff_battleflag, 0, 33554432)
            CALL(btlevtcmd_onoff_battleflag, 1, 134217728)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_016"), 0, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 0, 58, 256, 0, 41, 0, 30, 11)
            WAIT_MS(500)
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_017"), 0, BTL_UNIT_SELF)
            CALL(evt_msg_select, 0, STRING("mac_0_b_t2_018"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("mac_0_b_t2_019"))
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                RETURN
            ELSE
                CALL(evt_msg_print_add, 0, STRING("mac_0_b_t2_020"))
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_onoff_battleflag, 1, 32)
                RETURN
            END_IF
        END_IF
        CASE_EQUAL(9)
        // Step 5, before the player's phase: Frankly's feedback on Mario's practice try (nicely done,
        // a little early or a little late).
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING_OLD, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(4)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_021"), 0, BTL_UNIT_SELF)
                CASE_EQUAL(5)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_022"), 0, BTL_UNIT_SELF)
                CASE_EQUAL(6)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_023"), 0, BTL_UNIT_SELF)
                CASE_EQUAL(7)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_021"), 0, BTL_UNIT_SELF)
            END_SWITCH
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            RETURN
        END_IF
        // Step 6, after the player's phase: the same feedback after the next try.
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_sub_intpl_init, 5, 180, 0, 20)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, LW(0), 0)
                WAIT_FRAMES(1)
            END_LOOP
            CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, 0, 0)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(1)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_021"), 0, BTL_UNIT_SELF)
                CASE_EQUAL(2)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_022"), 0, BTL_UNIT_SELF)
                CASE_EQUAL(3)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_023"), 0, BTL_UNIT_SELF)
            END_SWITCH
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            RETURN
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Attack event of Professor Frankly: does nothing (he never attacks). */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of Professor Frankly: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Mario's Jump in the Action Command tutorial, the attack script of _lec_weapon_jump (data table tag 67):
 * approaches
 * the target with Professor Frankly's explanation (mac_0_b_t2_001),
 * freezes just before landing for his prompt to
 * press A (mac_0_b_t2_002), stores the timing result in the lecture's unit work 2 and, on a success,
 * stomps a second
 * time; at the end it moves the lecture progress on to 2.
 */
EVT_BEGIN(lecAttackEvent_Jump)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_LECTURE, STRING("T_1"))
        CALL(btlevtcmd_SetStayPose, BTL_UNIT_LECTURE, STRING("S_1"))
        // Frankly explains how the Action Command details appear once a target is chosen.
        CALL(evt_msg_print, 2, STRING("mac_0_b_t2_001"), 0, BTL_UNIT_LECTURE)
    END_IF
    // The attack is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 1, 1, 0)
    // Mario walks up to the enemy.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetTakeoffPosition, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(6))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_StartAC, 1)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    // He jumps (M_J_1B) with his jump cry and the jump slows into a hover just above the enemy.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_J_1B"))
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 36, 3, -1)
    ELSE
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_VOICE_MARIO_BATTLE_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 36, 0, -1)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_J_1D"))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        IF_INT_LESS_OR_EQUAL(LW(10), 0)
            // Frankly freezes the action and tells Mario to press A just before landing,
            // then waits for the button.
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 0, 180, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, 180, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
        END_IF
        CALL(btlevtcmd_ac_timing_flag_onoff, 1, 1)
        CALL(btlevtcmd_ac_timing_get_success_frame, LW(0))
        DIVIDE(LW(0), 2)
        WAIT_FRAMES(LW(0))
        IF_INT_LESS_OR_EQUAL(LW(10), 0)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_LECTURE, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_LECTURE, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_002"), 0, BTL_UNIT_LECTURE)
#if VERSION >= VERSION_JP
            WAIT_FRAMES(1)
#endif
            LABEL(11)
            CALL(btlevtcmd_PadCheckTrigger, 0, 256, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                WAIT_FRAMES(1)
                GOTO(11)
            END_IF
#if VERSION >= VERSION_JP
            WAIT_MS(150)
#endif
            CALL(evt_msg_continue)
        END_IF
    ELSE
        CALL(btlevtcmd_ac_timing_flag_onoff, 1, 1)
        CALL(btlevtcmd_ac_timing_get_success_frame, LW(0))
        DIVIDE(LW(0), 2)
        WAIT_FRAMES(LW(0))
    END_IF
    // The timing of the press is judged and stored for the lecture.
    CALL(btlevtcmd_ac_timing_flag_onoff, 0, 1)
    CALL(btlevtcmd_ResultAC)
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
        IF_INT_EQUAL(LW(0), 9)
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(3)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 1)
                CASE_EQUAL(1)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 2)
                CASE_EQUAL(2)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 3)
            END_SWITCH
        END_IF
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_CLEAR(LW(6), 2)
        // The stomp lands for its damage.
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        IF_INT_EQUAL(LW(10), 0)
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
        END_IF
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_StopAC)
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_WeaponAftereffect, LW(0))
        // He bounces off the enemy in three small hops.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_J_1B"))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 27)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
        GOTO(95)
    END_IF
    // Success: a second stomp follows with a cheer and the NICE effect.
    CALL(btlevtcmd_snd_voice, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_GetResultCountAC, LW(6))
    IF_INT_LESS_OR_EQUAL(LW(6), 1)
        BEGIN_INLINE_EVENT
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 0)
            CALL(evt_btl_camera_set_zoom, 0, 200)
            WAIT_FRAMES(10)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
            CALL(evt_btl_camera_set_zoom, 0, 250)
        END_INLINE_EVENT
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131072, LW(5))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
        WAIT_FRAMES(2)
        ADD(LW(10), 1)
        GOTO(10)
    ELSE
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
        WAIT_FRAMES(2)
    END_IF
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StopAC)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_WeaponAftereffect, LW(0))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        // A last bounce and the lecture moves on to its next step.
        BEGIN_SIBLING_EVENT_GET_ID(LW(14))
            CALL(evt_sub_intpl_init, 5, 180, 0, 20)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, LW(0), 0)
                WAIT_FRAMES(1)
            END_LOOP
            CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, 0, 0)
        END_SIBLING_EVENT
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_J_1B"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    CALL(btlevtcmd_WaitEventEnd, LW(14))
    // He walks back to his home position.
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_W_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, 2)
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Mario's Hammer in the Action Command tutorial, the attack script of _lec_weapon_hammer (data table tag 68):
 * Professor Frankly prompts the player to tilt and hold the stick left (mac_0_b_t2_008, 009) and to release it
 * when
 * the light comes on (mac_0_b_t2_010); the result goes to the lecture's unit work 2
 * and the progress moves on to 6.
 */
EVT_BEGIN(lecAttackEvent_Hammer)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    // The attack is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 5)
        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_LECTURE, STRING("T_1"))
        CALL(btlevtcmd_SetStayPose, BTL_UNIT_LECTURE, STRING("S_1"))
        // Frankly tells Mario to tilt and hold the stick left, and waits until he does.
        CALL(evt_msg_print, 2, STRING("mac_0_b_t2_008"), 0, BTL_UNIT_LECTURE)
        LABEL(1)
        CALL(btlevtcmd_PadCheckNow, 0, 262144, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            WAIT_FRAMES(1)
            GOTO(1)
        END_IF
        CALL(evt_msg_continue)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    BEGIN_SIBLING_EVENT
        LABEL(2)
        CALL(btlevtcmd_GetPos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(0), 0)
            WAIT_FRAMES(1)
            GOTO(2)
        END_IF
        CALL(evt_sub_intpl_init, 5, 0, 180, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_LECTURE, 0, 180, 0)
    END_SIBLING_EVENT
    // The hammer swing action command starts.
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
        CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AcSetParamAll, 4, 25, 0, 0, 0, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
        IF_INT_EQUAL(LW(0), 5)
            CALL(btlevtcmd_AcSetFlag, 2)
        ELSE
            CALL(btlevtcmd_AcSetFlag, 0)
        END_IF
        CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 3, 1, 0)
        // Mario walks up to the enemy.
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 35)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        ADD(LW(2), 5)
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
        CALL(evt_btl_camera_set_zoom, 0, 350)
        // He lifts the hammer (M_H_1A, M_H_1B) while the gauge charges.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_H_1A"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_MARIO_HAMMER_HOLD1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_H_1B"))
        CALL(btlevtcmd_StartAC, 1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
        IF_INT_EQUAL(LW(0), 5)
            LABEL(5)
            CALL(btlevtcmd_AcGetParam, 4, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                WAIT_FRAMES(1)
                GOTO(5)
            END_IF
        END_IF
    END_SIBLING_EVENT
    SET_VALUE(LW(14), 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 5)
        BEGIN_SIBLING_EVENT_GET_ID(LW(14))
            SET_VALUE(LW(5), 5)
            LOOP(LW(5))
                CALL(btlevtcmd_PadCheckNow, 0, 262144, LW(0))
                IF_INT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_JP
                    IS_EVENT_RUNNING(LW(15), LW(0))
                    IF_INT_EQUAL(LW(0), 0)
                    ELSE
#endif
                        SUSPEND_EVENT(LW(15))
                        CALL(btlevtcmd_AcSetParam, 2, 1)
                        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_LECTURE, STRING("T_1"))
                        CALL(btlevtcmd_SetStayPose, BTL_UNIT_LECTURE, STRING("S_1"))
                        // Frankly tells him to keep holding the stick.
                        CALL(evt_msg_print, 2, STRING("mac_0_b_t2_009"), 0, BTL_UNIT_LECTURE)
                        LABEL(6)
                        CALL(btlevtcmd_PadCheckNow, 0, 262144, LW(0))
                        IF_INT_EQUAL(LW(0), 0)
                            WAIT_FRAMES(1)
                            GOTO(6)
                        END_IF
#if VERSION >= VERSION_JP
                        WAIT_MS(200)
#endif
                        CALL(evt_msg_continue)
                        CALL(btlevtcmd_AcSetParam, 2, 0)
                        RESUME_EVENT(LW(15))
#if VERSION >= VERSION_JP
                    END_IF
#endif
                END_IF
                WAIT_FRAMES(1)
                SET_VALUE(LW(5), 5)
            END_LOOP
        END_SIBLING_EVENT
    END_IF
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    IF_INT_NOT_EQUAL(LW(14), 0)
        DELETE_EVENT(LW(14))
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 5)
        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_LECTURE, STRING("T_1"))
        CALL(btlevtcmd_SetStayPose, BTL_UNIT_LECTURE, STRING("S_1"))
        // Frankly tells him to release the stick when the light comes on, and waits.
        CALL(evt_msg_print, 2, STRING("mac_0_b_t2_010"), 0, BTL_UNIT_LECTURE)
        LABEL(10)
        CALL(btlevtcmd_PadCheckNow, 0, 262144, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            WAIT_FRAMES(1)
            GOTO(10)
        END_IF
        CALL(btlevtcmd_ResultAC)
#if VERSION >= VERSION_JP
        WAIT_MS(200)
#endif
        CALL(evt_msg_continue)
    ELSE
        CALL(btlevtcmd_ResultAC)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 9)
        // The release is judged and stored for the lecture.
        CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(3)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 1)
            CASE_EQUAL(1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 2)
            CASE_EQUAL(2)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_TIMING, 3)
        END_SWITCH
    END_IF
    // He swings the hammer down (M_H_1C) and hits the ground.
    CALL(evt_snd_sfxon, STRING("SFX_MARIO_HAMMER_SWING1"), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_H_1C"))
    WAIT_FRAMES(7)
    CALL(evt_snd_sfxon, STRING("SFX_MARIO_HAMMER_HIT_GROUND2"), 0)
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_CLEAR(LW(6), 2)
        // The hit lands for its damage.
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 0)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_GetDamage, LW(3), LW(0))
    CALL(evt_btl_camera_shake_h, 0, LW(0), 0, 10, 13)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    WAIT_FRAMES(30)
    // He stands up straight and walks back to his home position.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_S_1"))
    WAIT_FRAMES(10)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_W_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 5)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_LECTURE, UW_LECTURE_FRANKLI_STEP, 6)
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * End of the action command tutorial battle: Mario returns to his idle pose, the camera zooms on Frankly,
 * the status window is hidden and Frankly says his closing line (mac_0_b_t2_024),
 * then a battle flag (32) is set to end the fight.
 */
EVT_BEGIN(lecture_end_event)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 0, 58, 256, 0, 41, 0, 30, 11)
    WAIT_MS(500)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("T_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("S_1"))
    CALL(evt_msg_print, 2, STRING("mac_0_b_t2_024"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(500)
    CALL(btlevtcmd_onoff_battleflag, 1, 32)
    RETURN
EVT_END()
