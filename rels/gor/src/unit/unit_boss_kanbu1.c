// unit_boss_kanbu1: Lord Crump (X-Naut leader), boss battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"
#include "gor.h"

// Unit work slots of Lord Crump in the prologue battle.
enum {
    UW_BOSS_KANBU1_CHRISTINE_ID = 0,      // unit id of Goombella, spawned at init; she speaks the tutorial comments
    UW_BOSS_KANBU1_AC_SUCCESS_TALKED = 1, // 1 once Goombella commented on Mario's first successful action command
    UW_BOSS_KANBU1_AC_FAIL_TALKED = 2,    // 1 once Goombella commented on Mario's first failed action command
    UW_BOSS_KANBU1_HALF_HP_TALKED = 3,    // 1 once Goombella commented on Crump being at half HP
};

static USER_FUNC(_mario_ac_failed_check);
static USER_FUNC(_mario_ac_success_check);

BattleUnitKind unit_boss_kanbu1;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
BattleWeapon weapon_kanbu1_attack;
BattleUnitSetup entry_npc_christine;
static EvtWord init_event[82];
static EvtWord phase_event[282];
static EvtWord damage_event[10];
static EvtWord attack_event[24];
static EvtWord wait_event[6];
static EvtWord dead_event[276];
static PoseTableEntry pose_table[18];
static EvtWord normal_attack_event[365];

/**
 * Unit kind of Lord Crump:
 * 5 HP, level 20, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_boss_kanbu1 = {
    6,
    "btl_un_kanbu1",
    5,
    0,
    1,
    1,
    20,
    0,
    0,
    100,
    0,
    50,
    9,
    56,
    59,
    0,
    56,
    0.0f,
    26.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    28.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    28.0f,
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
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KANBU_DAMAGED1",
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

/** Defence of Lord Crump's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of Lord Crump's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Status vulnerability of Lord Crump, as a percent of the normal chance: immune to fright, instant kill. */
static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 100, 100, 100, 100, 100, 0};

/** Event table of Lord Crump: nothing special on a First Strike, its defeat script. */
static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {49, dead_event},
    {0, NULL},
};

/** Body part of Lord Crump: a single part using the model "c_kanbu". */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_kanbu1", "c_kanbu", 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/** Lord Crump's attack: 1 damage to a single target, a hammer-style hit. */
BattleWeapon weapon_kanbu1_attack = {
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
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
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
 * Setup entry that adds Goombella as a unit of Lord Crump's battle
 * (his init script places her at (-140, 0, 5)).
 */
BattleUnitSetup entry_npc_christine = {
    &unit_npc_christine, // unitKindParams
    2, // alliance
    {0}, // pad_05
    BATTLE_PHASE_BEFORE_PLAYER, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Init event of Lord Crump: installs his wait, attack, damage, confusion and phase events,
 * spawns the Goombella unit (entry_npc_christine) at (-140, 0, 5) as his unit work 0,
 * clears work 1 to 3 (message flags) and sets the heavy walk and run sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_onoff_battleflag, 1, BATTLE_FLAG_NO_OBJECT_FALL)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_npc_christine), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
    CALL(btlevtcmd_SetPos, LW(3), -140, 0, 5)
    CALL(btlevtcmd_SetHomePos, LW(3), -140, 0, 5)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_AC_SUCCESS_TALKED, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_AC_FAIL_TALKED, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_HALF_HP_TALKED, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Phase event of Lord Crump: on turn 1 before the player's phase the camera swings to Mario,
 * who turns round while Goombella speaks (mac_0_b_t1_000) and raises his hand.
 * After the player's phase it plays one-time comments:
 * when Crump is at half HP or less (mac_0_b_t1_003),
 * after Mario's first successful action command (001) and after his first failed one (002).
 */
static EVT_BEGIN(phase_event)
    // Turn 1, before the player's phase: the camera swings to Mario, who turns round.
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, -117, 62, 284, -115, 43, 0, 30, 11)
            WAIT_MS(500)
            BEGIN_SIBLING_EVENT_GET_ID(LW(5))
                CALL(evt_sub_intpl_init, 0, 0, 180, 15)
                LOOP(16)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_MARIO, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(5))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
            CALL(btlevtcmd_SetTalkPose, LW(3), STRING("PKR_T_1"))
            CALL(btlevtcmd_SetStayPose, LW(3), STRING("PKR_S_1"))
            // Goombella speaks and Mario raises his hand; the camera swings back.
            CALL(evt_msg_print, 2, STRING("mac_0_b_t1_000"), 0, LW(3))
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_snd_se, BTL_UNIT_MARIO, STRING("SFX_VOICE_MARIO_HAND_UP1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_N_2"))
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_MARIO, 1)
            CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_MARIO, 1, BTL_POSE_STAY)
            BEGIN_SIBLING_EVENT_GET_ID(LW(5))
                CALL(evt_sub_intpl_init, 0, 180, 0, 15)
                LOOP(16)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, BTL_UNIT_MARIO, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(5))
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_MARIO)
            RETURN
        END_IF
    END_IF
    // After the player's phase: one-time comments.
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_HALF_HP_TALKED, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(1))
            DIVIDE(LW(1), 2)
            CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), LW(1))
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_HALF_HP_TALKED, 1)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
                // Lord Crump is at half HP or less: Goombella comments.
                CALL(evt_msg_print, 2, STRING("mac_0_b_t1_003"), 0, LW(3))
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                RETURN
            END_IF
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_AC_SUCCESS_TALKED, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(_mario_ac_success_check, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_AC_SUCCESS_TALKED, 1)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
                // Mario's first successful action command: Goombella comments.
                CALL(evt_msg_print, 2, STRING("mac_0_b_t1_001"), 0, LW(3))
                CALL(btlevtcmd_StatusWindowOnOff, 1)
            END_IF
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_AC_FAIL_TALKED, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(_mario_ac_failed_check, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_AC_FAIL_TALKED, 1)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
                // Mario's first failed action command: Goombella comments.
                CALL(evt_msg_print, 2, STRING("mac_0_b_t1_002"), 0, LW(3))
                CALL(btlevtcmd_StatusWindowOnOff, 1)
            END_IF
        END_IF
    END_IF
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
 * Attack event of Lord Crump: uses an enemy item if he has one,
 * otherwise always runs normal_attack_event with weapon_kanbu1_attack.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_kanbu1_attack))
    CALL_CHILD(normal_attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of Lord Crump: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Death event of Lord Crump: spins him over 48 frames with the defeat sound, puffs smoke, pays out the coins,
 * experience and Star Points, tips him over, then runs a short Goombella dialogue with Mario turning to face her
 * (mac_0_b_t1_004 and 005) before the unit is removed.
 * It is the scripted end of the fight with Goombella's commentary.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(0), 50)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 50)
    END_IF
    SET_VALUE(LW(0), 48)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LABEL(10)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 0, -15, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_GetPos, LW(10), LW(3), LW(1), LW(2))
    ADD(LW(2), 10)
    ADD(LW(1), 30)
    CALL(_add_star_point_disp_offset, LW(10), LW(3), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    CALL(btlevtcmd_SetRotateOffset, LW(10), 0, 0, 0)
    SET_VALUE(LW(0), 30)
    LABEL(20)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 3, 0, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetBackItem, LW(10))
    CALL(btlevtcmd_OnPartsAttribute, LW(10), 1, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_MARIO)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_S_1"))
    BEGIN_SIBLING_EVENT_GET_ID(LW(5))
        CALL(evt_sub_intpl_init, 0, 0, 180, 15)
        LOOP(16)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_MARIO, 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(5))
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_KANBU1_CHRISTINE_ID, LW(3))
    CALL(btlevtcmd_SetTalkPose, LW(3), STRING("PKR_T_1"))
    CALL(btlevtcmd_SetStayPose, LW(3), STRING("PKR_S_1"))
    CALL(evt_msg_print, 2, STRING("mac_0_b_t1_004"), 0, LW(3))
    CALL(evt_btl_camera_set_mode, 0, 17)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_msg_print, 2, STRING("mac_0_b_t1_005"), 0, LW(3))
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(5))
        CALL(evt_sub_intpl_init, 0, 180, 0, 15)
        LOOP(16)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_MARIO, 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(5))
    CALL(btlevtcmd_KillUnit, LW(10), 0)
    RETURN
EVT_END()

/**
 * Pose table of Lord Crump:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {BTL_POSE_TALK, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_RUN, "R_2"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Pose table of Lord Crump while guarding:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table_guard[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {BTL_POSE_NORMAL, "G_2"},
    {BTL_POSE_TALK, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "G_2"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_RUN, "R_2"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "G_2"},
};

/**
 * Lord Crump's basic attack (weapon in LW(9), weapon_kanbu1_attack):
 * picks a target, runs at it and does a belly flop.
 * He hops (SFX_BOSS_KANBU_JUMP1, poses A_1A and A_1B) over the target;
 * the pre-damage check decides between a dodge and a hit,
 * and on a hit he lands on it (A_1C, SFX_BOSS_KANBU_HIP_ATTACK1 and 2),
 * bounces and gets up (D_1) before returning home.
 * Falls back to the flustered reaction when confused with nothing to hit.
 */
static EVT_BEGIN(normal_attack_event)
    // Target: the first-strike target if the battle opened that way, otherwise one picked for his attack.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    // No target: a confused Crump flusters, otherwise the attack ends.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
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
    // He runs at the target.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    // Wind-up: he hops up (A_1A, A_1B) over the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(2.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    // The pre-damage check decides between a dodge and a hit.
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
        // Miss: he comes down without hitting (the target dodges for some kinds of miss).
        LABEL(90)
        GOTO(98)
        // Hit: he belly flops onto the target for the weapon damage.
        LABEL(91)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        GOTO(98)
        LABEL(98)
        CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
        // He lands flat (A_1C) with a thud, then bounces twice.
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
        // He gets up (D_1) and dusts himself off.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_1"))
        WAIT_FRAMES(15)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 15, 0, FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
        // He trots back to his home position.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
        WAIT_FRAMES(10)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(7.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
        RETURN
EVT_END()

/**
 * Script helper: stores in args[0] whether Mario's last action command was a success (the battle work's
 * marioAcSuccess).
 */
static USER_FUNC(_mario_ac_success_check) {
    evtSetValue(event, event->args[0], _battleWorkPointer->marioAcSuccess);
    return EVT_RETURN_DONE;
}
/** Script helper: stores in args[0] whether Mario's last action command failed (the battle work's marioAcFailed). */
static USER_FUNC(_mario_ac_failed_check) {
    evtSetValue(event, event->args[0], _battleWorkPointer->marioAcFailed);
    return EVT_RETURN_DONE;
}
