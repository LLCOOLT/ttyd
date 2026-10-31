// Rogueport Sewers (tik) battle unit: Koopa Paratroopa (patapata): its parts, defence/status tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "data_tables.h"
#include "battle/battle_sub.h"

// Unit work slots of this unit (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_PATAPATA_SPIN_DONE = 0,  // 1 ends the shell-spin loop of the Koopa's shell attacks
    UW_PATAPATA_SPIN_SPEED = 1, // degrees the shell turns per frame while it spins
};

BattleUnitKind unit_patapata;
static BattleWeapon weapon_patapata_attack;
static BattleUnitDefense defence_patapata;
static BattleUnitDefenseAttr defence_patapata_attr;
static StatusVulnerability regist_patapata;
static BattleUnitKindPart parts_patapata[1];
static PoseTableEntry pose_table_patapata[18];
static BattleDataEntry data_table_patapata[3];
static PoseSoundTiming pose_sound_timing_table[8];
static EvtWord init_event_patapata[26];
static EvtWord dmg_fall_event[189];
static EvtWord patapata_dmg_first_attack_pos[19];
static EvtWord attack_event_patapata[541];
static PoseTableEntry pose_table[18];
#if VERSION <= VERSION_DEMO_JP
static PoseTableEntry pose_table_turn[15];
#else
static PoseTableEntry pose_table_turn[17];
#endif
static BattleDataEntry data_table[3];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_nokonoko_attack;
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[78];
static EvtWord attack_event[548];
static EvtWord wait_event[6];

/**
 * Unit kind of the Paratroopa (HP 4, level 9): its size, offsets, damage sounds, status vulnerability,
 * parts and init event.
 */
BattleUnitKind unit_patapata = {
    15,
    "btl_un_patapata",
    4,
    0,
    1,
    1,
    9,
    0,
    0,
    70,
    1,
    60,
    9999,
    36,
    40,
    -4,
    40,
    0.0f,
    24.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    9.0f,
    6.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    11.0f,
    24.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    36.0f,
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
    "SFX_ENM_PATA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING | UNIT_ATTR_REQUIRED_FOR_CLEAR,
    &regist_patapata,
    1,
    parts_patapata,
    init_event_patapata,
    data_table_patapata,
};

/** Weapon of the Paratroopa's attack: 2 damage. */
static BattleWeapon weapon_patapata_attack = {
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    0, // counterResistFlags
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

/** Defence of the Paratroopa (Paratroopa form): 1 damage points off every hit. */
static BattleUnitDefense defence_patapata = {{1, 1, 1, 1, 1}};

/** Defence of the Paratroopa (Paratroopa form): no damage reduction. */
static BattleUnitDefenseAttr defence_patapata_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Paratroopa (Paratroopa form) (percent chance to take each status):
 * extra prone to dizzy and gale force; resists most other statuses.
 */
static StatusVulnerability regist_patapata = {100, 100, 120, 100, 95, 100, 100, 95, 100, 95, 100, 95, 100, 95, 95, 100, 120, 100, 95, 100, 100, 100};
#else
/**
 * Status vulnerability of the Paratroopa (Paratroopa form) (percent chance to take each status):
 * extra prone to dizzy and gale force; resists most other statuses.
 */
static StatusVulnerability regist_patapata = {95, 100, 120, 100, 90, 100, 100, 90, 100, 95, 100, 95, 100, 95, 90, 95, 110, 100, 90, 100, 100, 100};
#endif

/**
 * Body part of the Paratroopa (Paratroopa form) (model c_nokoteki):
 * hit position, defences, attributes and pose table.
 */
static BattleUnitKindPart parts_patapata[] = {
    {1, "btl_un_patapata", "c_nokoteki", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence_patapata, &defence_patapata_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_WINGED | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table_patapata},
};

/**
 * Pose table (patapata) of the Paratroopa: maps each battle pose to the animation it plays (PTP_* animations).
 */
static PoseTableEntry pose_table_patapata[] = {
    {1, "PTP_N_1"},
    {2, "PTP_Y_1"},
    {9, "PTP_Y_1"},
    {5, "PTP_K_1"},
    {4, "PTP_X_1"},
    {3, "PTP_X_1"},
    {BTL_POSE_NORMAL, "PTP_S_1"},
    {29, "PTP_Q_1"},
    {30, "PTP_Q_1"},
    {31, "PTP_S_1"},
    {BTL_POSE_DAMAGE, "PTP_D_1"},
    {50, "PTP_A_1"},
    {BTL_POSE_RUN, "PTP_R_1"},
    {BTL_POSE_WALK, "PTP_W_1"},
    {BTL_POSE_DANGER, "PTP_X_1"},
    {BTL_POSE_PERIL, "PTP_X_1"},
    {BTL_POSE_TALK, "PTP_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PTP_S_1"},
};

/** Data table of the Paratroopa: its fall when knocked out of the air and its First Strike reaction. */
static BattleDataEntry data_table_patapata[] = {
    {14, dmg_fall_event},
    {48, patapata_dmg_first_attack_pos},
    {0, NULL},
};

/** Sounds the Paratroopa's poses play as they animate: wing flaps while waiting, hovering and moving. */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"PTP_S_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_W_1", 0.01f, NULL, "SFX_ENM_PATA_MOVE1", 0, 1},
    {"PTP_R_1", 0.01f, NULL, "SFX_ENM_PATA_MOVE1", 0, 1},
    {"PTP_N_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_K_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_A_3", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_X_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init event of the Koopa Paratroopa: registers its wait,
 * attack (attack_event_patapata, also its confusion event)
 * and damage events and its pose sound table, then starts the wait event.
 */
static EVT_BEGIN(init_event_patapata)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_patapata))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_patapata))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data event 14 (the Paratroopa is knocked out of the air):
 * drops its flying attributes, then after 500 ms swaps its pose,
 * data table and part for the walking Koopa Troopa's, changes its unit kind to 14 (UNIT_KOOPA_TROOPA),
 * plays the fall sound and drops it to the floor, setting its home position there.
 * It then installs the Koopa's wait, attack, damage and confusion events and footstep sounds.
 * If its HP damage count is above 1 it also runs dmg_turn_event so it lands flipped over.
 */
static EVT_BEGIN(dmg_fall_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, LW(10), UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_WINGED)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_ReplaceParts, LW(10), LW(11), PTR(parts), 1)
    CALL(btlevtcmd_AnimeChangePoseDirect, LW(10), LW(11), STRING("NKT_D_1"))
    CALL(btlevtcmd_ChangeKind, LW(10), UNIT_KOOPA_TROOPA)
    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_KIND_CHANGED)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHpDamageCount, LW(10), LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        WAIT_FRAMES(30)
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
        CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
        CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
        RETURN
    END_IF
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL_CHILD(dmg_turn_event)
    RETURN
EVT_END()

/**
 * Data event 48 of the Paratroopa, run by the default damage event
 * when the battle opens with a first strike on it
 * (damage code 0x39, set in battle_seq): sets its Y to 10 and waits for the attack to end.
 */
static EVT_BEGIN(patapata_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Attack event of the flying Koopa Paratroopa:
 * on a first strike it takes the first-attack target, otherwise it uses an enemy item if it has one or samples a
 * target, and does a diving attack on it: it swoops to a point in front of the target, rears back (PTP_A_1) and
 * dives (PTP_A_4) with the damage check (on a first strike with DAMAGE_FLAG_ALWAYS_HIT added,
 * so it cannot miss).
 * A miss flies on past; a hit shakes the camera and it bounces back up while spinning three full turns.
 * It then flies home and goes back to waiting. A confused unit with no target runs subsetevt_confuse_flustered.
 */
static EVT_BEGIN(attack_event_patapata)
    // Choose the target: the First Strike target if the battle opened with one,
    // otherwise it may use an item or pick a normal target.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        WAIT_FRAMES(50)
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_patapata_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_patapata_attack), LW(3), LW(4))
    END_IF
    // No target left: a confused Paratroopa is flustered; either way it ends its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The camera frames the Paratroopa and its target, and the attack is announced.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_patapata_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_patapata_attack))
    // It swoops to a spot in front of and above the target, then rears back.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 45)
    ADD(LW(1), 30)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.5f))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATA_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTP_A_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 6)
    ADD(LW(1), 6)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    WAIT_FRAMES(11)
    // It dives at the target (a First Strike dive cannot miss).
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATA_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTP_A_4"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_ALWAYS_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    // Check how the target defends against the dive.
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
    // The target dodged: the Paratroopa flies on past and climbs back up.
    LABEL(90)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
    SET_VALUE(LW(1), 20)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    GOTO(98)
    // The dive hits: the camera shakes and the damage is dealt.
    LABEL(91)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_patapata_attack))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_ALWAYS_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    // It bounces off the target, spinning three full turns in the air.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATA_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    ADD(LW(1), 30)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(24)
            SUBTRACT(LW(0), 45)
            IF_INT_LESS(LW(0), 0)
                ADD(LW(0), 360)
            END_IF
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(1), 20)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    END_INLINE_EVENT
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 30, 0, 0, 0)
    WAIT_FRAMES(10)
    GOTO(98)
    // It flies back home and returns to waiting.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Pose table of the Paratroopa: maps each battle pose to the animation it plays (NKT_* animations). */
static PoseTableEntry pose_table[] = {
    {1, "NKT_N_1"},
    {2, "NKT_Y_1"},
    {9, "NKT_Y_1"},
    {5, "NKT_K_1"},
    {4, "NKT_X_1"},
    {3, "NKT_X_1"},
    {BTL_POSE_NORMAL, "NKT_S_1"},
    {29, "NKT_Q_1"},
    {30, "NKT_Q_1"},
    {31, "NKT_S_1"},
    {BTL_POSE_DAMAGE, "NKT_D_1"},
    {50, "NKT_A_1"},
    {BTL_POSE_RUN, "NKT_R_1"},
    {BTL_POSE_WALK, "NKT_W_1"},
    {BTL_POSE_DANGER, "NKT_X_1"},
    {BTL_POSE_PERIL, "NKT_X_1"},
    {BTL_POSE_TALK, "NKT_T_1"},
    {BTL_POSE_STAY_DEFAULT, "NKT_S_1"},
};

/**
 * Pose table (flipped over) of the Paratroopa: maps each battle pose to the animation it plays (NKT_*
 * animations).
 */
static PoseTableEntry pose_table_turn[] = {
    {1, "NKT_N_2"},
    {2, "NKT_B_1"},
    {9, "NKT_B_1"},
    {5, "NKT_K_2"},
    {4, "NKT_K_2"},
    {3, "NKT_K_2"},
    {BTL_POSE_NORMAL, "NKT_S_2"},
    {29, "NKT_Q_1"},
    {30, "NKT_Q_1"},
    {31, "NKT_D_1"},
    {BTL_POSE_DAMAGE, "NKT_D_1"},
#if VERSION >= VERSION_JP
    {BTL_POSE_RUN, "NKT_R_1"},
    {BTL_POSE_WALK, "NKT_W_1"},
#endif
    {BTL_POSE_DANGER, "NKT_K_2"},
    {BTL_POSE_PERIL, "NKT_K_2"},
    {BTL_POSE_TALK, "NKT_S_2"},
    {BTL_POSE_STAY_DEFAULT, "NKT_S_2"},
};

/**
 * Data table of the Paratroopa: event handlers for being flipped over and a First Strike on it (no reaction).
 */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/** Defence of the Paratroopa: 1 damage points off every hit. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Element reactions of the Paratroopa: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {0};

/** Defence of the Paratroopa (flipped over): no damage reduction. */
static BattleUnitDefense defence_turn = {0};

#if VERSION <= VERSION_DEMO_JP
/** Status vulnerability of the Paratroopa (percent chance to take each status): resists most statuses. */
static StatusVulnerability regist = {100, 100, 90, 100, 95, 100, 100, 95, 100, 95, 100, 95, 100, 95, 95, 100, 90, 100, 95, 100, 100, 100};
#else
/** Status vulnerability of the Paratroopa (percent chance to take each status): resists most statuses. */
static StatusVulnerability regist = {95, 100, 90, 100, 90, 100, 100, 90, 100, 95, 100, 95, 100, 95, 90, 95, 90, 100, 90, 100, 100, 100};
#endif

/** Parts of the Paratroopa : hit positions, defences, attributes and pose tables. */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_nokonoko", // partName
        "c_nokoteki", // modelName
        {0}, // positionOffset
        {0.0f, 30.0f, 0.0f}, // hitBaseOffset
        {0.0f, 40.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_SHELLED, // attributes
        0, // counterAttributes
        pose_table, // poseTable
    },
};

/** Weapon of the Paratroopa's shell slam: 2 damage, hammer-type contact attack. */
static BattleWeapon weapon_nokonoko_attack = {
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
    ELEMENT_NORMAL, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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
 * Init event of the Koopa Troopa: registers its wait, attack,
 * damage and confusion events (the confusion event is
 * the attack event too), clears the over-turn counter, sets its run and walk footstep sounds
 * (SFX_ENM_NOKO_MOVE3L / 3R), then starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event: runs the default battle damage reaction on the unit itself (part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data event 13 (a stomp flips the Koopa over):
 * switches the unit to its flipped-over defence and pose tables,
 * sets STATUS_FLAG_FLIPPED with the over-turn counter at 2 and drops the hit offset,
 * plays the "NKT_D_1" pose with the shell sound, and hops once in place.
 */
static EVT_BEGIN(dmg_turn_event)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, -15, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 2)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("NKT_D_1"))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("NKT_S_2"))
    RETURN
EVT_END()

/**
 * Runs in place of a flipped Koopa's attack (attack_event calls it): counts the over-turn counter down by one;
 * while turns remain it only wriggles ("NKT_S_3") for 400 ms and passes.
 * At zero it restores the upright defence and pose tables, clears STATUS_FLAG_FLIPPED and hops back on its feet.
 */
static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_S_3"))
        WAIT_MS(400)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("NKT_S_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * A first-strike version of the Koopa Troopa's shell attack:
 * takes the first-attack target, hops and curls into its shell,
 * spins up (0, then 20, then 40 degrees per frame) and slides into the target, applying weapon_nokonoko_attack
 * without a pre-damage check (so it cannot miss), then bounces off in two hops and walks home.
 * Nothing in this file points at it.
 */
static EVT_BEGIN(first_attack_event)
    CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_nokonoko_attack))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_A_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 20)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 40)
    WAIT_MS(100)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack event of the Koopa Troopa: a flipped Koopa runs wakeup_event instead.
 * Otherwise it uses an enemy item if one fits, or picks a target (the first-strike target when
 * BATTLE_FLAG_FIRST_ATTACK is set), then spin-jumps into its shell,
 * spins up in three steps (kicking up smoke) and slides into the target with the damage check.
 * A miss slides past and turns back; a hit shakes the camera and bounces off in two hops,
 * then it returns home and goes back to waiting.
 * A confused unit with no target runs subsetevt_confuse_flustered.
 */
static EVT_BEGIN(attack_event)
    // A Koopa flipped onto its back spends its turn getting back on its feet instead of attacking.
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    // Choose the target: the First Strike target if the battle opened with one,
    // otherwise it may use an item or pick a normal target.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
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
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_nokonoko_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_nokonoko_attack), LW(3), LW(4))
    END_IF
    // No target left: a confused Koopa is flustered; either way it ends its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The camera frames the Koopa and its target, and the attack is announced.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    // The Koopa hops and curls into its shell.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_A_1"))
    // It spins up in three steps, kicking up smoke.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 20)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 40)
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    // It slides along the floor into the target.
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    DELETE_EVENT(LW(13))
    // Check how the target defends against the shell slam.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The target dodged: the shell slides past, slows to a stop and hops back upright.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    WAIT_MS(250)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 10)
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    GOTO(98)
    // The slam hits: the camera shakes, the damage is dealt and the Koopa bounces off in two hops.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_SPEED, 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATAPATA_SPIN_DONE, 1)
    GOTO(98)
    // It walks back home and returns to waiting.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
