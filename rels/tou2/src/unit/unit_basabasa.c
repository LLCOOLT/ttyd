// unit_basabasa: Swooper, battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "data_tables.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"

// Unit work slots of the Swooper (initial values come from the battle setup).
enum {
    UW_BASABASA_START_FLYING = 0, // 1: starts the battle already in flight instead of hanging from the ceiling
};

BattleUnitKind unit_basabasa;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleWeapon weapon_basabasa_drain_attack_biribiri_counterd;
static BattleDataEntry data_table[14];
static BattleUnitKindPart parts[1];
static StatusVulnerability regist;
static BattleWeapon weapon_basabasa_attack;
static EvtWord init_event[78];
static EvtWord dmg_first_attack_pos[12];
static EvtWord damage_event[10];
static EvtWord damage_event_ceil[51];
static EvtWord counter_damage_event[16];
static EvtWord ceil_fall_ready_event[23];
static EvtWord attack_event[448];
static EvtWord wait_event[6];

/**
 * Unit kind of the Swooper (HP 6, level 17): its size, offsets, damage sounds, status vulnerability,
 * parts and init event.
 */
BattleUnitKind unit_basabasa = {
    74,
    "btl_un_basabasa",
    6,
    0,
    1,
    1,
    17,
    0,
    2,
    70,
    0,
    50,
    9999,
    32,
    32,
    6,
    32,
    0.0f,
    16.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -15.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    0.0f,
    16.0f,
    20.8f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    32.0f,
    32.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BASA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_CEILING | UNIT_ATTR_REQUIRED_FOR_CLEAR | UNIT_ATTR_BILLBOARD,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Swooper: no damage reduction. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element reactions of the Swooper: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Weapon of the Swooper's drain attack (biribiri counter variant): no HP damage. */
static BattleWeapon weapon_basabasa_drain_attack_biribiri_counterd = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, 0, 0, // acHelpMsg..counterResistFlags
    TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
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

/** Pose table of the Swooper: maps each battle pose to the animation it plays (BSA_* animations). */
static PoseTableEntry pose_table[] = {
    {1, "BSA_N_1"},
    {2, "BSA_Y_1"},
    {9, "BSA_Y_1"},
    {5, "BSA_K_1"},
    {4, "BSA_X_1"},
    {3, "BSA_X_1"},
    {BTL_POSE_NORMAL, "BSA_S_1"},
    {29, "BSA_Q_1"},
    {30, "BSA_Q_1"},
    {31, "BSA_S_1"},
    {BTL_POSE_DAMAGE, "BSA_D_1"},
    {50, "BSA_A_1"},
    {BTL_POSE_RUN, "BSA_R_1"},
    {BTL_POSE_WALK, "BSA_W_1"},
    {BTL_POSE_DANGER, "BSA_X_1"},
    {BTL_POSE_PERIL, "BSA_X_1"},
    {BTL_POSE_TALK, "BSA_T_1"},
    {BTL_POSE_STAY_DEFAULT, "BSA_S_1"},
};

/**
 * Pose table (ceiling) of the Swooper: maps each battle pose to the animation it plays (BSA_* animations).
 */
static PoseTableEntry pose_table_ceil[] = {
    {1, "BSA_N_2"},
    {2, "BSA_Y_2"},
    {9, "BSA_Y_2"},
    {5, "BSA_K_2"},
    {4, "BSA_X_2"},
    {3, "BSA_X_2"},
    {BTL_POSE_NORMAL, "BSA_S_2"},
    {29, "BSA_Q_2"},
    {30, "BSA_Q_2"},
    {31, "BSA_S_2"},
    {BTL_POSE_DAMAGE, "BSA_D_2"},
    {50, "BSA_A_1"},
    {BTL_POSE_RUN, "BSA_S_1"},
    {BTL_POSE_WALK, "BSA_S_1"},
    {BTL_POSE_DANGER, "BSA_X_2"},
    {BTL_POSE_PERIL, "BSA_X_2"},
    {BTL_POSE_TALK, "BSA_T_2"},
    {BTL_POSE_STAY_DEFAULT, "BSA_S_2"},
};

/**
 * Data table of the Swooper: event handlers for the counter-hit reactions (tags 25-36) and a First Strike on it.
 */
static BattleDataEntry data_table[] = {
    {26, counter_damage_event},
    {25, counter_damage_event},
    {27, counter_damage_event},
    {28, counter_damage_event},
    {29, counter_damage_event},
    {30, counter_damage_event},
    {31, counter_damage_event},
    {32, counter_damage_event},
    {33, counter_damage_event},
    {34, counter_damage_event},
    {35, counter_damage_event},
    {36, counter_damage_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

/** Body part of the Swooper (model c_basabasa): hit position, defences, attributes and pose table. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_basabasa", "c_basabasa", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table_ceil},
};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Swooper (percent chance to take each status): extra prone to gale force;
 * resists most other statuses.
 */
static StatusVulnerability regist = {80, 85, 100, 100, 80, 100, 100, 80, 100, 80, 100, 80, 100, 80, 80, 80, 110, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of the Swooper (percent chance to take each status): extra prone to dizzy;
 * resists most other statuses.
 */
static StatusVulnerability regist = {80, 85, 105, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 95, 80, 80, 95, 100, 80, 100, 100, 95};
#endif

/** Weapon of the Swooper's attack: 3 damage. */
static BattleWeapon weapon_basabasa_attack = {
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

/** Sounds the Swooper's poses play as they animate: wing flaps while waiting and moving. */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"BSA_S_1", 0.01f, NULL, "SFX_ENM_BASA_WAIT1", 0, 1},
    {"BSA_W_1", 0.01f, NULL, "SFX_ENM_BASA_MOVE1", 0, 1},
    {"BSA_R_1", 0.01f, NULL, "SFX_ENM_BASA_MOVE1", 0, 1},
    {"BSA_T_1", 0.01f, NULL, "SFX_ENM_BASA_WAIT1", 0, 1},
    {"BSA_A_1", 0.01f, NULL, "SFX_ENM_BASA_WAIT1", 0, 1},
    {"BSA_N_1", 0.01f, NULL, "SFX_ENM_BASA_WAIT1", 0, 1},
    {"BSA_K_1", 0.01f, NULL, "SFX_ENM_BASA_WAIT1", 0, 1},
    {"BSA_X_1", 0.01f, NULL, "SFX_ENM_BASA_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Makes a ceiling-hanging Swooper let go.
 * If UNIT_ATTR_CEILING is set it clears it and sets UNIT_ATTR_FLOATING, switches to the airborne pose,
 * drops the unit and its home position 70 units and resets the hit, cursor,
 * status-icon and held-item offsets for the lowered body. Returns its home position in LW(0..2).
 */
static EVT_BEGIN(ceil_sky_event)
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_SetPossessionItemOffset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, 0, -30, 0)
    CALL(btlevtcmd_AddHomePos, BTL_UNIT_SELF, 0, -30, 0)
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 30, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 16, 21, 0)
    CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 6, 32)
    CALL(btlevtcmd_AddHomePos, BTL_UNIT_SELF, 0, -40, 0)
    LABEL(99)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    RETURN
EVT_END()

/**
 * Init event of the Swooper: registers its events (the ceiling-aware damage_event_ceil and the ceiling-fall
 * event), the pose sound table and the offsets for hanging upside down.
 * If unit work 0 is 1 it starts already dropped from the ceiling, then starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_ceil))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, PTR(ceil_fall_ready_event))
    CALL(btlevtcmd_SetPossessionItemOffset, BTL_UNIT_SELF, 0, -20, 0)
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, -50, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, -30, 0)
    CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 6, 10)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 16, -18, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BASABASA_START_FLYING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(ceil_sky_event)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data event 48, which the standard damage reaction runs
 * when the Swooper is the victim of a first strike (battle_seq gives it damage code 57):
 * drops it from the ceiling (ceil_sky_event), puts it at Y = 10 and waits for the attack to end.
 */
static EVT_BEGIN(dmg_first_attack_pos)
    CALL_CHILD(ceil_sky_event)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
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
 * Damage event while hanging: runs the default damage reaction,
 * then drops the Swooper from the ceiling (ceil_sky_event) and dives it to its new home over 60 frames,
 * unless the hit knocked it out for good or did no damage.
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
    CALL(btlevtcmd_GetTotalDamage, LW(10), LW(12))
    IF_INT_EQUAL(LW(12), 0)
        RETURN
    END_IF
    CALL_CHILD(ceil_sky_event)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 0, 0, -1)
    RETURN
EVT_END()

/**
 * Data events 25 to 36, which the standard damage reaction runs for the counter-damage codes 44 to 55:
 * drops the Swooper from the ceiling (ceil_sky_event), then runs subsetevt_counter_damage with its damage code.
 */
static EVT_BEGIN(counter_damage_event)
    CALL_CHILD(ceil_sky_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    CALL_CHILD(subsetevt_counter_damage)
    RETURN
EVT_END()

/**
 * Ceiling-fall event (registered with btlevtcmd_SetEventCeilFall,
 * run for every unit when the stage's overhead iron frame falls, _fall_frame_event):
 * default damage reaction, then drops it from the ceiling and dives it to its new home over 60 frames.
 */
static EVT_BEGIN(ceil_fall_ready_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL_CHILD(ceil_sky_event)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 0, 0, -1)
    RETURN
EVT_END()

/**
 * Attack event of the Swooper: uses an enemy item if one fits, otherwise picks a target and swoops at it.
 * If hanging from the ceiling it first drops 30 units, then dives at the target,
 * wobbling up and down twice on the approach, and checks damage.
 * A miss flies past and a hit shakes the camera;
 * either way it returns home and goes back to hanging (rising 30 units, "BSA_S_2") or hovering ("BSA_S_1").
 * A confused unit with no target runs subsetevt_confuse_flustered.
 */
static EVT_BEGIN(attack_event)
    // The Swooper may use an item instead of attacking.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // Choose a target; a confused Swooper with none is flustered, and either way the turn ends.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_basabasa_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_basabasa_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The attack is announced and the camera frames the Swooper and its target.
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_basabasa_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_basabasa_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    // A Swooper hanging from the ceiling lets go and drops 30 units before it flies.
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, 0, -30, 0)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.5f))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
        SUBTRACT(LW(1), 40)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    END_IF
    // It bobs up and down twice as it flaps toward the target.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), -6)
    LOOP(2)
        ADD(LW(1), 13)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, 10, 0, 0, -1)
        ADD(LW(1), -13)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -10, 0, 0, -1)
    END_LOOP
    // It dives at the target.
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.5f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
    // Check how the target defends against the swoop.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_basabasa_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The target dodged: the Swooper flies past it.
    LABEL(90)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.5f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, -1)
    WAIT_MS(200)
    GOTO(98)
    // The swoop hits: the camera shakes and the damage is dealt, then it flies on past.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_basabasa_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_basabasa_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.5f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 4, 0, -1)
    WAIT_MS(200)
    GOTO(98)
    // It flies back home.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING, LW(7))
    IF_INT_EQUAL(LW(7), 1)
        SUBTRACT(LW(1), 30)
    END_IF
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    // It settles back into its place: hanging from the ceiling or hovering.
    LABEL(99)
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BSA_S_2"))
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, 0, 30, 0)
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BSA_S_1"))
        WAIT_FRAMES(1)
    END_IF
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
