// Pit of 100 Trials battle unit: the Spiky Parabuzzy (`patatogemet`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "data_tables.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "version.h"

// Unit work slots of this unit (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_PATATOGEMET_ON_CEILING = 0, // nonzero while it clings to the ceiling (ceiling tables and scripts)
    UW_PATATOGEMET_SPIN_DONE = 1,  // 1 ends the shell-spin loop of its shell attack
    UW_PATATOGEMET_SPIN_SPEED = 2, // degrees the shell turns per frame while it spins
};

BattleUnitKind unit_patatogemet;
static BattleWeapon weapon_patamet_attack;
static BattleUnitDefense defence_pata;
static BattleUnitDefenseAttr defence_attr_pata;
static StatusVulnerability regist_pata;
static PoseTableEntry pose_table_pata[18];
static BattleDataEntry data_table_pata[4];
static BattleUnitKindPart parts_pata[1];
static PoseSoundTiming pose_sound_timing_table[9];
static EvtWord init_event_pata[26];
static EvtWord dmg_avoid_counter_thorn_head_event_pata[61];
static EvtWord damage_event_pata[10];
static EvtWord dmg_fall_event_pata[106];
static EvtWord dmg_first_attack_pos_event_pata[19];
static EvtWord attack_event_pata[339];
static EvtWord wait_event_pata[6];
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_ceil[17];
#if VERSION <= VERSION_DEMO_JP
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
static EvtWord init_event2[148];
static EvtWord dmg_avoid_counter_thorn_head_event[61];
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[82];
static EvtWord attack_event[546];
static EvtWord wait_event[6];
static EvtWord damage_event_ceil[49];
static EvtWord counter_damage_event_ceil[76];
static EvtWord ceil_fall_ready_event[163];
static EvtWord attack_event_ceil[426];
static EvtWord wait_event_ceil[6];

/** Unit data of the Spiky Parabuzzy: stats, sounds, attributes, parts, init script and data table. */
BattleUnitKind unit_patatogemet = {
    105,
    "btl_un_patatogemet",
    5,
    0,
    1,
    1,
    24,
    0,
    2,
    70,
    2,
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
    UNIT_ATTR_FLOATING,
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

/** Attack data for the Spiky Parabuzzy's dive from the air: 3 damage. */
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    COUNTER_RESIST_FIERY | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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

/**
 * Defence of the Spiky Parabuzzy while it still has its wings: 4 against normal, ice and electric hits;
 * immune to fire and explosions (defence 99 cancels the hit).
 */
static BattleUnitDefense defence_pata = {{4, 99, 4, 99, 4}};

/** Element response of the Spiky Parabuzzy, flying form: it is immune to fire and explosions. */
static BattleUnitDefenseAttr defence_attr_pata = {{0, 2, 0, 2, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Spiky Parabuzzy, flying form (percent, 0 is immune): immune to burn. Demo
 * values.
 */
static StatusVulnerability regist_pata = {75, 90, 75, 100, 75, 100, 0, 75, 100, 75, 100, 75, 100, 75, 75, 60, 95, 100, 75, 100, 100, 95};
#else
/**
 * Status vulnerability of the Spiky Parabuzzy, flying form (percent, 0 is immune): immune to burn.
 * Released game values.
 */
static StatusVulnerability regist_pata = {75, 90, 105, 100, 75, 100, 0, 75, 100, 90, 100, 90, 100, 95, 75, 60, 90, 100, 75, 100, 100, 95};
#endif

/** Pose table of the Spiky Parabuzzy, flying form: battle pose types mapped to animation names. */
static PoseTableEntry pose_table_pata[] = {
    {1, "PTM_N_1"},
    {2, "PTM_Y_1"},
    {9, "PTM_Y_1"},
    {5, "PTM_K_1"},
    {4, "PTM_X_1"},
    {3, "PTM_X_1"},
    {BTL_POSE_NORMAL, "PTM_S_1"},
    {29, "PTM_Q_1"},
    {30, "PTM_Q_1"},
    {31, "PTM_S_1"},
    {BTL_POSE_DAMAGE, "PTM_D_1"},
    {50, "PTM_A_1"},
    {BTL_POSE_RUN, "PTM_R_1"},
    {BTL_POSE_WALK, "PTM_W_1"},
    {BTL_POSE_DANGER, "PTM_X_1"},
    {BTL_POSE_PERIL, "PTM_X_1"},
    {BTL_POSE_TALK, "PTM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PTM_S_1"},
};

/**
 * Data table of the Spiky Parabuzzy, flying form: event handlers keyed by tag (dmg_fall_event_pata,
 * dmg_avoid_counter_thorn_head_event_pata, dmg_first_attack_pos_event_pata).
 */
static BattleDataEntry data_table_pata[] = {
    {14, dmg_fall_event_pata},
    {37, dmg_avoid_counter_thorn_head_event_pata},
    {48, dmg_first_attack_pos_event_pata},
    {0, NULL},
};

/** Body part of the Spiky Parabuzzy, flying form: hit position, size, defence tables and attributes. */
static BattleUnitKindPart parts_pata[] = {
    {1, "btl_un_patatogemet", "c_met", 0.0f, 0.0f, 0.0f, 0.0f, 23.0f, 0.0f, 0.0f, 28.0f, 0.0f, 20, 30, 255, &defence_pata, &defence_attr_pata, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_WINGED | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, COUNTER_ATTR_TOP_SPIKY, pose_table_pata},
};

/** Sound table of the Spiky Parabuzzy: the sound each animation plays while it runs. */
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
 * Init script of the flying Spiky Parabuzzy: installs its wing wait, attack, damage and confusion handlers,
 * sets the pose sound timing table (wing flaps) and starts it waiting.
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
 * Plays the "toge_flush" spark effect over the flying Spiky Parabuzzy's spiked head 30 frames
 * after an attacker is hurt by its spikes,
 * at a height that depends on its size statuses 10 (Huge) and 11 (Tiny),
 * so the spark follows the changed size.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event_pata)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 50)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
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

/** Damage script of the flying Spiky Parabuzzy: runs the default damage handling on itself. */
static EVT_BEGIN(damage_event_pata)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Fall reaction of the flying Spiky Parabuzzy (data event 14), run when it loses its wings.
 * It clears its flying attribute, switches to the walking pose table, data table and parts, drops to the floor,
 * and changes its unit kind to the Spike Top, which re-runs init_event for the grounded form.
 * If the hit did more than 1 HP damage it also lands flipped over (dmg_turn_event).
 */
static EVT_BEGIN(dmg_fall_event_pata)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, LW(10), UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_WINGED)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_ReplaceParts, LW(10), LW(11), PTR(parts), 1)
    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_KIND_CHANGED)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ChangeKind, LW(10), UNIT_SPIKE_TOP)
    CALL(btlevtcmd_GetHpDamageCount, LW(10), LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL_CHILD(init_event)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
        RETURN
    ELSE
        CALL_CHILD(init_event)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
        CALL_CHILD(dmg_turn_event)
    END_IF
    RETURN
EVT_END()

/**
 * Data event 48 (the battle opens with Mario's or the partner's First Strike on it) of the flying Spiky
 * Parabuzzy: it sets its y position to 10 (near the
 * floor) and waits for the attack to end.
 */
static EVT_BEGIN(dmg_first_attack_pos_event_pata)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Attack script of the flying Spiky Parabuzzy: a swoop.
 * With a first-strike flag the target is the one already chosen,
 * otherwise it checks for an item use and samples a target.
 * It rises 40 units, dives past the target into it, and on a hit deals damage,
 * then flies back up and returns to its home position. If it has no target it can be flustered when confused.
 */
static EVT_BEGIN(attack_event_pata)
    // After a First Strike it attacks right away; otherwise it uses an item if it has one, or picks a target
    // (a confused Spiky Parabuzzy with nobody to hit gets flustered).
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
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
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
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
    // Declare the attack.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_patamet_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // It flaps up over the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAMET_MOVE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, FLOAT(1.0f), 0, 0, -1)
    WAIT_MS(250)
    CALL(evt_snd_sfxoff, LW(15))
    // It folds its wings and dives straight at the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAMET_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(9.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 10)
    SUBTRACT(LW(1), 30)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    // Find out whether the dive connects.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patamet_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Miss or dodge: it swoops past and hovers there for a moment.
    LABEL(90)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, LW(3), EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 0, 0, -1)
    WAIT_MS(300)
    GOTO(98)
    // Hit: the damage is dealt.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_patamet_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patamet_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAMET_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    // It flies back up and home.
    LABEL(98)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays the flying Spiky Parabuzzy's idle pose from its pose table. */
static EVT_BEGIN(wait_event_pata)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/** Pose table of the Spiky Parabuzzy: battle pose types mapped to animation names. */
static PoseTableEntry pose_table[] = {
    {1, "TMT_N_1"},
    {2, "TMT_Y_1"},
    {9, "TMT_Y_1"},
    {5, "TMT_K_1"},
    {4, "TMT_X_1"},
    {3, "TMT_X_1"},
    {BTL_POSE_NORMAL, "TMT_S_1"},
    {29, "TMT_Q_1"},
    {30, "TMT_Q_1"},
    {31, "TMT_A_1"},
    {BTL_POSE_DAMAGE, "TMT_D_1"},
    {50, "TMT_A_1"},
    {BTL_POSE_WALK, "TMT_W_1"},
    {BTL_POSE_RUN, "TMT_R_1"},
    {BTL_POSE_DANGER, "TMT_X_1"},
    {BTL_POSE_PERIL, "TMT_X_1"},
    {BTL_POSE_STAY_DEFAULT, "TMT_S_1"},
};

/** Pose table of the Spiky Parabuzzy, on the ceiling: battle pose types mapped to animation names. */
static PoseTableEntry pose_table_ceil[] = {
    {1, "STM_N_1"},
    {2, "STM_Y_1"},
    {9, "STM_Y_1"},
    {5, "STM_K_1"},
    {4, "STM_X_1"},
    {3, "STM_X_1"},
    {BTL_POSE_NORMAL, "STM_S_1"},
    {29, "STM_Q_1"},
    {30, "STM_Q_1"},
    {31, "STM_A_1"},
    {BTL_POSE_DAMAGE, "STM_D_1"},
    {50, "STM_A_1"},
    {BTL_POSE_WALK, "STM_W_1"},
    {BTL_POSE_RUN, "STM_R_1"},
    {BTL_POSE_DANGER, "STM_X_1"},
    {BTL_POSE_PERIL, "STM_X_1"},
    {BTL_POSE_STAY_DEFAULT, "STM_S_1"},
};

/** Pose table of the Spiky Parabuzzy, flipped on its back: battle pose types mapped to animation names. */
static PoseTableEntry pose_table_turn[] = {
    {1, "TMT_Y_2"},
    {2, "TMT_Y_2"},
    {9, "TMT_Y_2"},
    {5, "TMT_S_3"},
    {4, "TMT_S_3"},
    {3, "TMT_S_3"},
    {BTL_POSE_NORMAL, "TMT_S_3"},
    {29, "TMT_Q_2"},
    {30, "TMT_Q_2"},
    {31, "TMT_A_1"},
    {BTL_POSE_DAMAGE, "TMT_S_3"},
#if VERSION >= VERSION_JP
    {BTL_POSE_WALK, "TMT_W_1"},
    {BTL_POSE_RUN, "TMT_R_1"},
#endif
    {BTL_POSE_DANGER, "TMT_S_3"},
    {BTL_POSE_PERIL, "TMT_S_3"},
    {BTL_POSE_STAY_DEFAULT, "TMT_S_3"},
};

/**
 * Data table of the Spiky Parabuzzy: event handlers keyed by tag (dmg_turn_event,
 * dmg_avoid_counter_thorn_head_event).
 */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Data table of the Spiky Parabuzzy, on the ceiling: event handlers keyed by tag
 * (counter_damage_event_ceil).
 */
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
    {0},
};

/** Attack data for the Spiky Parabuzzy's spiked shell roll: 3 damage. */
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
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/** Attack data for the Spiky Parabuzzy's drop from the ceiling: 5 damage. */
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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

/**
 * Defence of the Spiky Parabuzzy once it has lost its wings: 4 against normal, ice and electric hits;
 * immune to fire and explosions (defence 99 cancels the hit).
 */
static BattleUnitDefense defence = {{4, 99, 4, 99, 4}};

/** Element response of the Spiky Parabuzzy: it is immune to fire and explosions. */
static BattleUnitDefenseAttr defence_attr = {{0, 2, 0, 2, 0}};

/** Damage reduction of the Spiky Parabuzzy, flipped on its back: none, every attack type does full damage. */
static BattleUnitDefense defence_turn = {0};

/**
 * Element response of the Spiky Parabuzzy, flipped on its back: none, every attack type is treated
 * normally.
 */
static BattleUnitDefenseAttr defence_attr_turn = {0};

#if VERSION <= VERSION_DEMO_JP
/** Status vulnerability of the Spiky Parabuzzy (percent, 0 is immune): immune to burn. Demo values. */
static StatusVulnerability regist = {75, 90, 75, 100, 75, 100, 0, 75, 100, 75, 100, 75, 100, 75, 75, 60, 65, 100, 75, 100, 100, 95};
#else
/**
 * Status vulnerability of the Spiky Parabuzzy (percent, 0 is immune): immune to burn. Released game
 * values.
 */
static StatusVulnerability regist = {75, 90, 75, 100, 75, 100, 0, 75, 100, 90, 100, 90, 100, 95, 75, 60, 30, 100, 75, 100, 100, 95};
#endif

/** Body part of the Spiky Parabuzzy: hit position, size, defence tables and attributes. */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_togemet", // partName
        "c_met", // modelName
        {0}, // positionOffset
        {0.0f, 23.0f, 0.0f}, // hitBaseOffset
        {0.0f, 28.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        COUNTER_ATTR_TOP_SPIKY, // counterAttributes
        pose_table, // poseTable
    },
};

/**
 * Init script of the Spike Top form of the Spiky Parabuzzy:
 * runs init_event2 to set up the handlers for its current position (floor or ceiling), then starts it waiting.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_ON_CEILING, LW(15))
    CALL_CHILD(init_event2)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Sets up the Spike Top form of the Spiky Parabuzzy's handlers according to unit work 0.
 * With 0 it is on the floor: wait, attack, damage
 * and confusion scripts are installed (confusion reuses the attack script),
 * ceiling fall is disabled and its cursor offset is cleared.
 * With any other value it hangs from the ceiling:
 * it gets the ceiling attribute flags, pose table and data table, is placed at height 130 as its home position,
 * gets the ceiling versions of the scripts plus ceil_fall_ready_event,
 * and its hit and cursor offsets move down by 50.
 * Both cases set the run and walk sounds and clear its flip count.
 */
static EVT_BEGIN(init_event2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_ON_CEILING, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELLED)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    ELSE
        CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
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
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, -17, 0)
    END_IF
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Plays the "toge_flush" spark effect over the Spike Top form of the Spiky Parabuzzy's spiked head 30 frames
 * after an attacker is hurt by its spikes, at a height that depends on its size statuses 10 (Huge) and 11
 * (Tiny), so the spark follows the changed size.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 38)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
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

/** Damage script of the Spike Top form of the Spiky Parabuzzy: runs the default damage handling on itself. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Reaction when the Spike Top form of the Spiky Parabuzzy is flipped onto its back:
 * swaps in the flipped defence, attribute and pose tables, sets status flag 1 and a flip count of 1 turn,
 * plays pose type 39 with SFX_ENM_INSIDE1, bounces twice, and sets its home slightly above the floor.
 * It also drops the spike counter attribute of part 1, so landing on its upturned belly no longer hurts.
 */
static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(4)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 12, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 5, LW(2))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_TOP_SPIKY)
    RETURN
EVT_END()

/**
 * Called on the Spike Top form of the Spiky Parabuzzy's turn while it is flipped over.
 * It counts the flip counter down; while it is still above 0 the unit stays on its back
 * and goes back to waiting.
 * At 0 it restores the normal tables and pose, clears status flag 1, hops upright with SFX_ENM_INSIDE2,
 * and turns the spike counter attribute of part 1 back on.
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
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 18, -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_TOP_SPIKY)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack script of the Spike Top form of the Spiky Parabuzzy: its shell roll.
 * If it is still flipped over it gets up instead.
 * With a first-strike flag the target is the one already chosen,
 * otherwise it checks for an item use and samples a target.
 * It then curls up and spins (unit work 1 and 2 hold the stop flag and spin speed for a background rotation
 * loop), trailing smoke, and slides along the floor into the target.
 * A miss or block makes it bounce away, a hit deals damage and knocks it back in two hops.
 * Afterwards it walks home. If it has no target it can be flustered when confused.
 */
static EVT_BEGIN(attack_event)
    // If the Spiky Parabuzzy is lying on its back it gets up instead of attacking.
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    // Pick the target (the First Strike target, or an enemy item use, or a sampled enemy); a confused Spiky
    // Parabuzzy with nobody to hit gets flustered.
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
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_met_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_met_attack), LW(3), LW(4))
    END_IF
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
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_met_attack))
    // Declare the attack.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_met_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    // It hops, curls into its shell and starts spinning.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_ATTACK2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_DONE, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_SPEED, 10)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_SPEED, 20)
    WAIT_MS(100)
    // It slides along the floor toward the target, trailing smoke.
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
    // Find out whether the roll connects.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Miss or dodge: it skids past, stops spinning and hops back upright.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_SPEED, 10)
    WAIT_MS(250)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_DONE, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    GOTO(98)
    // Hit: the damage is dealt and the Spiky Parabuzzy bounces off in two hops.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_met_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_SPEED, 10)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_SPIN_DONE, 1)
    GOTO(98)
    // Walk back home.
    LABEL(98)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays the Spike Top form of the Spiky Parabuzzy's idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Damage script of the Spike Top form of the Spiky Parabuzzy while on the ceiling:
 * runs the default damage handling, then, if the attack did real damage (and its damage code is not the 512-only
 * code), the unit still has the ceiling attribute set and it falls via ceil_fall_ready_event.
 */
static EVT_BEGIN(damage_event_ceil)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_KO, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_LIFE_SHROOM, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_GetTotalDamage, BTL_UNIT_SELF, LW(12))
    IF_INT_EQUAL(LW(12), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(ceil_fall_ready_event)
    END_IF
    RETURN
EVT_END()

/**
 * Counter-damage script of the Spike Top form of the Spiky Parabuzzy on the ceiling:
 * removes the ceiling attributes and tables, restores the floor pose and data tables,
 * resets unit work 0 and the hit offsets, drops its home position to the floor,
 * re-runs init_event2 and runs the shared counter-damage script.
 */
static EVT_BEGIN(counter_damage_event_ceil)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_ON_CEILING, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, 17, 0)
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
 * The Spike Top form of the Spiky Parabuzzy falls from the ceiling (SFX_ENM_FALL1):
 * it drops to the floor with its landing sound, removes the ceiling attributes,
 * re-runs init_event2 for the floor, and lands on its back,
 * flipped over for 1 turn with the flipped tables and without its spike counter attribute.
 */
static EVT_BEGIN(ceil_fall_ready_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetJumpSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 20, LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_TOGEMET_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_turn))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_ON_CEILING, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, 17, 0)
    CALL_CHILD(init_event2)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 5, LW(2), 12, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 5, LW(2))
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_TOP_SPIKY)
    RETURN
EVT_END()

/**
 * Attack script of the Spike Top form of the Spiky Parabuzzy while on the ceiling:
 * it moves above the target, drops onto it (SFX_ENM_MET_FALL1 and its landing sound) and, if the hit connects,
 * deals damage.
 * After 60 frames it loses the ceiling attributes and tables for good,
 * hops back to its original x position and runs init_event2 to continue as a floor unit.
 */
static EVT_BEGIN(attack_event_ceil)
    // Pick the target (the First Strike target, or an enemy item use, or a sampled enemy); a confused Spiky
    // Parabuzzy with nobody to hit gets flustered.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
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
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
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
    // Declare the attack.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    // It crawls along the ceiling until it is above the target.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(10), LW(11), LW(12))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(11), LW(12), 60, -1, 1)
    // It curls up and drops onto the target with a falling sound.
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
    // Find out whether the drop connects.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_ceil_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Hit: the damage is dealt.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_ceil_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(98)
    // The Spiky Parabuzzy wobbles on the floor, then leaves the ceiling for good and goes back to its floor
    // tables.
    LABEL(98)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_PATATOGEMET_ON_CEILING, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 14, 17, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // Two hops back to its old column, then it walks home and restarts as a floor unit.
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(7), 0, LW(9))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(7), 0, LW(9), 0, -1, 0)
    CALL_CHILD(init_event2)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script of the Spike Top form of the Spiky Parabuzzy on the ceiling: plays its idle pose from its pose table. */
static EVT_BEGIN(wait_event_ceil)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
