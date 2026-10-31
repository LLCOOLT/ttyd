// unit_dark_keeper: Dark Craw (`dark_keeper`) battle unit (a gatekeeper-type enemy sharing Gus's sounds).

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
#include "evt/evt_sub.h"

BattleUnitKind unit_dark_keeper;
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
static EvtWord phase_event[2];
static EvtWord attack_event[52];
static EvtWord normal_attack_event[391];
static EvtWord throw_attack_event[343];
static EvtWord wait_event[6];

/**
 * Unit data of the Dark Craw: 20 HP and level 28, with its parts, status vulnerability, init event and
 * event data table.
 */
BattleUnitKind unit_dark_keeper = {
    55,
    "btl_un_dark_keeper",
    20,
    0,
    1,
    1,
    28,
    1,
    3,
    70,
    2,
    50,
    9999,
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

/**
 * Defense of the Dark Craw against normal, fire, ice, explosion and electric attacks: none, so it takes
 * full damage from every element.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type reactions of the Dark Craw: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Dark Craw (both early demos), as the percent chance each status takes hold: immune
 * to Fright; resists 12 statuses (down to 60% of the normal chance).
 */
static StatusVulnerability regist = {70, 70, 60, 100, 60, 100, 100, 60, 100, 60, 100, 60, 100, 60, 60, 0, 60, 100, 60, 100, 100, 95};
#else
/**
 * Status vulnerability of the Dark Craw (the retail releases), as the percent chance each status takes
 * hold: immune to Fright; resists 12 statuses (down to 60% of the normal chance).
 */
static StatusVulnerability regist = {90, 80, 80, 100, 90, 100, 100, 70, 100, 90, 100, 90, 100, 95, 70, 0, 60, 100, 70, 100, 100, 95};
#endif

/** Pose table of the Dark Craw: maps each battle pose (idle, hurt, attacking and so on) to its animation. */
static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {BTL_POSE_NORMAL, "S_2"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {50, "A_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_2"},
};

/**
 * Event data table of the Dark Craw: scripts that replace the standard handling for an attacker being hurt
 * by its spiked head (tag 37).
 */
static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Parts of the Dark Craw: 2 parts: parts 1 and 2 (model c_monban_t), each with its defense tables,
 * attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_dark_keeper", "c_monban_t", 0.0f, 0.0f, 0.0f, 8.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, COUNTER_ATTR_TOP_SPIKY, pose_table},
    {2, "btl_un_dark_keeper", "c_monban_t", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon record of the Dark Craw's charge: 6 damage and counts as a hammer-type hit. */
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
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/** Weapon record of the Dark Craw's thrown-weapon attack: 6 damage. */
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
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/**
 * Sound cues for the animations of the Dark Craw: each entry plays a sound effect at a set time within a
 * pose, such as SFX_ENM_MONBAN_WAIT1.
 */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"S_2", 0.6666667f, NULL, "SFX_ENM_MONBAN_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init event of the Dark Keeper: registers its wait, phase, attack, damage and confusion events,
 * the run and walk footstep sounds and the pose sound table, then starts the wait event.
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
 * Data event 37 (damage code 31, run when an attacker is hurt by its spiked head):
 * after 30 frames flashes the "toge_flush" spike effect near its head,
 * placed 60 units up (Huge, status 10), 33 (Tiny, status 11) or 48 otherwise.
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 18)
        ADD(LW(1), 60)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
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

/** Damage event: runs the default battle damage reaction on the unit itself (part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event of the Bandit: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/**
 * Attack event of the Dark Keeper: uses an enemy item if one fits,
 * otherwise a roll of 0-99 under 50 (about half the time) picks the normal attack (weapon_monban_attack,
 * normal_attack_event) and the rest the throw attack (weapon_monban_throw_attack).
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
 * The Dark Keeper's charge: winds up with stamping footsteps,
 * then runs along the floor into the target (weapon in LW(9)).
 * A hit shakes the camera and knocks the target back; a miss runs on past.
 * Afterwards it walks home and laughs three times before going back to its stance.
 */
static EVT_BEGIN(normal_attack_event)
    // Use the target of the opening first attack if there was one, otherwise choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // The attack is announced; Dark Craw turns to face its target.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    // Dark Craw crouches and stomps its feet, then breaks into a run toward the target.
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
    // Find out how the target reacts to the charge.
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
    // The charge missed: Dark Craw runs on past the target.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    WAIT_FRAMES(60)
    GOTO(98)
    // The charge connects: the damage is applied, then Dark Craw hops back twice with a step sound each time.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Dark Craw walks back to its home position and laughs three times.
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
 * The Dark Craw's spear throw (weapon in LW(9)):
 * it picks a target (the first-strike target during a first strike), winds up and throws its spear,
 * part 2 (otherwise hidden), spinning along an arc to the target's hit position.
 * A dodge plays the avoid reaction and the spear flies on; a hit takes the guard result and deals the damage;
 * either way the spear is hidden again. Then it laughs three times and returns to its stance.
 */
static EVT_BEGIN(throw_attack_event)
    // Use the target of the opening first attack if there was one, otherwise choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    // The attack is announced; Dark Craw turns to face its target.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    // Dark Craw winds up and throws the weapon in its hand; the weapon becomes a spinning projectile.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_THROW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2"))
    WAIT_FRAMES(28)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MONBAN_THROW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
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
    // The thrown weapon spins through the air toward the target.
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
    // The throw missed: the weapon flies on and is restored to Dark Craw.
    LABEL(90)
    CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    GOTO(98)
    // The throw hits: the damage is applied.
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_FRAMES(2)
    GOTO(98)
    // Dark Craw laughs three times and returns to its idle pose.
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

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
