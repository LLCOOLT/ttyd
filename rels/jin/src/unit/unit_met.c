// Buzzy Beetle (met): enemy battle unit; Creepy Steeple's copy of the unit data and scripts.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"

// Unit work slots of the Buzzy Beetle.
enum {
    UW_MET_ON_CEILING = 0, // nonzero (from the battle setup): hangs from the ceiling; 0 on the floor
    UW_MET_SPIN_STOP = 1,  // set to 1 to stop the shell spin loop of its attack
    UW_MET_SPIN_SPEED = 2, // degrees per frame the shell spin loop turns it
};

BattleUnitKind unit_met;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_ceil[18];
#if VERSION <= VERSION_DEMO_JP
static PoseTableEntry pose_table_turn[15];
#else
static PoseTableEntry pose_table_turn[17];
#endif
static BattleDataEntry data_table[3];
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
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[71];
static EvtWord attack_event[546];
static EvtWord wait_event[6];
static EvtWord damage_event_ceil[49];
static EvtWord counter_damage_event_ceil[76];
static EvtWord ceil_fall_ready_event[158];
static EvtWord attack_event_ceil[467];
static EvtWord wait_event_ceil[6];

/**
 * Unit kind of the Buzzy Beetle:
 * 5 HP, level 16, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_met = {
    72,
    "btl_un_met",
    5,
    0,
    1,
    1,
    16,
    0,
    2,
    70,
    1,
    60,
    9999,
    28,
    20,
    5,
    20,
    0.0f,
    10.0f,
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
    12.0f,
    15.0f,
    0.0f,
    0.0f,
    10.0f,
    0.0f,
    28.0f,
    20.0f,
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
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/**
 * Pose table of the Buzzy Beetle:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table[] = {
    {1, "MET_N_1"},
    {2, "MET_Y_1"},
    {9, "MET_Y_1"},
    {5, "MET_K_1"},
    {4, "MET_X_1"},
    {3, "MET_X_1"},
    {BTL_POSE_NORMAL, "MET_S_1"},
    {29, "MET_Q_1"},
    {30, "MET_Q_1"},
    {31, "MET_A_1"},
    {BTL_POSE_DAMAGE, "MET_D_1"},
    {50, "MET_A_1"},
    {BTL_POSE_WALK, "MET_W_1"},
    {BTL_POSE_RUN, "MET_R_1"},
    {BTL_POSE_DANGER, "MET_X_1"},
    {BTL_POSE_PERIL, "MET_X_1"},
    {BTL_POSE_TALK, "MET_T_1"},
    {BTL_POSE_STAY_DEFAULT, "MET_S_1"},
};

/**
 * Pose table of the Buzzy Beetle while on the ceiling:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table_ceil[] = {
    {1, "SMT_N_1"},
    {2, "SMT_Y_1"},
    {9, "SMT_Y_1"},
    {5, "SMT_K_1"},
    {4, "SMT_X_1"},
    {3, "SMT_X_1"},
    {BTL_POSE_NORMAL, "SMT_S_1"},
    {29, "SMT_Q_1"},
    {30, "SMT_Q_1"},
    {31, "SMT_A_1"},
    {BTL_POSE_DAMAGE, "SMT_D_1"},
    {50, "SMT_A_1"},
    {BTL_POSE_WALK, "SMT_W_1"},
    {BTL_POSE_RUN, "SMT_R_1"},
    {BTL_POSE_DANGER, "SMT_X_1"},
    {BTL_POSE_PERIL, "SMT_X_1"},
    {BTL_POSE_TALK, "SMT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "SMT_S_1"},
};

/**
 * Pose table of the Buzzy Beetle while flipped over:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table_turn[] = {
    {1, "MET_N_2"},
    {2, "MET_Y_2"},
    {9, "MET_Y_2"},
    {5, "MET_K_2"},
    {4, "MET_X_2"},
    {3, "MET_X_2"},
    {BTL_POSE_NORMAL, "MET_S_2"},
    {29, "MET_Q_2"},
    {30, "MET_Q_2"},
    {31, "MET_A_1"},
    {BTL_POSE_DAMAGE, "MET_D_3"},
#if VERSION >= VERSION_JP
    {50, "MET_A_1"},
    {BTL_POSE_WALK, "MET_W_1"},
#endif
    {BTL_POSE_DANGER, "MET_X_2"},
    {BTL_POSE_PERIL, "MET_X_2"},
    {BTL_POSE_TALK, "MET_S_2"},
    {BTL_POSE_STAY_DEFAULT, "MET_S_2"},
};

/** Event table of the Buzzy Beetle: its reaction to being flipped over, nothing special on a First Strike. */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Event table of the Buzzy Beetle:
 * the reaction when it is hurt while attacking (tags 25-36), nothing special on a First Strike.
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

/** Buzzy Beetle's attack: 3 damage to a single target, a shell-toss-style hit. */
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

/** Buzzy Beetle's ceiling attack: 4 damage to a single target, a jump-style hit. */
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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
 * Defence of the Buzzy Beetle's body: 4 against normal, ice and electric hits;
 * immune to fire and explosions (defence 99 cancels the hit).
 */
static BattleUnitDefense defence = {{4, 99, 4, 99, 4}};

/**
 * Defence attributes of the Buzzy Beetle's body: fire (takes no damage), explosion (takes no damage);
 * every other type is dealt normally.
 */
static BattleUnitDefenseAttr defence_attr = {{0, 2, 0, 2, 0}};

/** Defence of the Buzzy Beetle's body per damage type while flipped over: 0 against every damage type. */
static BattleUnitDefense defence_turn = {0};

/**
 * Defence attributes of the Buzzy Beetle's body while flipped over:
 * none, so every damage type is dealt normally.
 */
static BattleUnitDefenseAttr defence_attr_turn = {0};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Buzzy Beetle in the demo, as a percent of the normal chance: immune to burn;
 * sleep 75%, stop 90%, freeze 75%, instant kill 95% (and 9 other statuses lowered).
 */
static StatusVulnerability regist = {75, 90, 75, 100, 75, 100, 0, 75, 100, 75, 100, 75, 100, 75, 75, 60, 65, 100, 75, 100, 100, 95};
#else
/**
 * Status vulnerability of the Buzzy Beetle in the retail versions, as a percent of the normal chance:
 * immune to burn; sleep 75%, stop 90%, freeze 75%, instant kill 95% (and 9 other statuses lowered).
 */
static StatusVulnerability regist = {75, 90, 75, 100, 75, 100, 0, 75, 100, 90, 100, 90, 100, 95, 75, 60, 30, 100, 75, 100, 100, 95};
#endif

/** Body part of the Buzzy Beetle: a single part using the model "c_met". */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_met", "c_met", 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 25.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/**
 * Init script of the Buzzy Beetle: runs init_event2 to set up the handlers for its current position (floor or
 * ceiling), then starts it waiting.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_MET_ON_CEILING, LW(15))
    CALL_CHILD(init_event2)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Sets up the Buzzy Beetle's handlers according to unit work 0.
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_MET_ON_CEILING, LW(15))
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
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 12, -15, 0)
    END_IF
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/** Damage script of the Buzzy Beetle: runs the default damage handling on itself. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Reaction when the Buzzy Beetle is flipped onto its back:
 * swaps in the flipped defence, attribute and pose tables, sets status flag 1 and a flip count of 1 turn,
 * plays pose type 39 with SFX_ENM_INSIDE1 and bounces twice on the spot.
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
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 12, -1)
    RETURN
EVT_END()

/**
 * Called on the Buzzy Beetle's turn while it is flipped over.
 * It counts the flip counter down; while it is still above 0 the unit stays on its back
 * and goes back to waiting.
 * At 0 it restores the normal tables and pose, clears status flag 1 and hops upright with SFX_ENM_INSIDE2.
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
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack script of the Buzzy Beetle: its shell roll. If it is still flipped over it gets up instead.
 * With a first-strike flag the target is the one already chosen,
 * otherwise it checks for an item use and samples a target.
 * It then curls up and spins (unit work 1 and 2 hold the stop flag and spin speed for a background rotation
 * loop), trailing smoke, and slides along the floor into the target.
 * A miss or block makes it bounce away, a hit deals damage and knocks it back in two hops.
 * Afterwards it walks home. If it has no target it can be flustered when confused.
 */
static EVT_BEGIN(attack_event)
    // Flipped over: it gets up instead of attacking.
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    // First Strike: the first-attack target is already fixed and the camera pulls in on it.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        WAIT_FRAMES(30)
    ELSE
        // It may use an enemy item instead of attacking.
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        // Target: it picks one for its attack; with none, a confused one flusters, otherwise the attack ends.
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
    // The attack is declared and it walks to a spot in front of the target.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_met_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // Wind-up: it hops into its shell and spins up with a smoke trail behind it.
    WAIT_MS(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_ATTACK2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_STOP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_STOP, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_SPEED, 10)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_SPEED, 20)
    WAIT_MS(100)
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
    // It slides along the floor into the target; the pre-damage check decides between a dodge and a hit.
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 0)
    DELETE_EVENT(LW(13))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_attack), 256, LW(5))
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
    // Miss: it skids past the target (which dodges for some kinds of miss), stops
    // and hops back out of its shell.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_SPEED, 10)
    WAIT_MS(250)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_STOP, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    GOTO(98)
    // Hit: the shell hits for the weapon damage and knocks the Buzzy Beetle back in two hops.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_met_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_attack), 256, LW(5))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_SPEED, 10)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_SPIN_STOP, 1)
    GOTO(98)
    // It walks back to its home position.
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

/** Wait script: plays the Buzzy Beetle's idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Damage script of the Buzzy Beetle while on the ceiling:
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
 * Counter-damage script of the Buzzy Beetle on the ceiling:
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_ON_CEILING, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 12, 15, 0)
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
 * The Buzzy Beetle falls from the ceiling (SFX_ENM_FALL1):
 * it drops to the floor with a landing sound, removes the ceiling attributes, re-runs init_event2 for the floor,
 * and lands on its back, flipped over for 1 turn with the flipped tables.
 */
static EVT_BEGIN(ceil_fall_ready_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetJumpSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 15, LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_turn))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_ON_CEILING, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 12, 15, 0)
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
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 12, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    RETURN
EVT_END()

/**
 * Attack script of the Buzzy Beetle while on the ceiling:
 * it moves above the target, drops onto it (SFX_ENM_MET_FALL1 and landing sound) and, if the hit connects,
 * deals damage.
 * It then wobbles on the floor for 60 frames, loses the ceiling attributes and tables for good,
 * hops back to its original x position and runs init_event2 to continue as a floor unit.
 */
static EVT_BEGIN(attack_event_ceil)
    // First Strike: the first-attack target is already fixed and the camera pulls in on it.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        // It may use an enemy item instead of attacking.
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        // Target: it picks one for its attack; with none, a confused one flusters, otherwise the attack ends.
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
    // The attack is declared.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // It moves along the ceiling to a spot above the target, then lets go and falls.
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(10), LW(11), LW(12))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(11), LW(12), 60, -1, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetJumpSpeed, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    // It drops onto the target; the pre-damage check decides between a dodge and a hit.
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 18, LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_ceil_attack), 256, LW(5))
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
    // Miss: it lands without hitting (the target dodges for some kinds of miss).
    LABEL(90)
    GOTO(98)
    // Hit: the fall lands for its damage.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_met_ceil_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_met_ceil_attack), 256, LW(5))
    GOTO(98)
    // It wobbles on the floor, then loses its ceiling status for good and switches to its floor poses
    // and events.
    LABEL(98)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, -18, 0)
    SET_FLOAT_VALUE(LW(12), FLOAT(30.0f))
    SET_FLOAT_VALUE(LW(13), FLOAT(0.0f))
    LOOP(60)
        CALL(evt_sub_get_sincos, LW(13), LW(14), LW(15))
        MULTIPLY_FLOAT(LW(14), LW(12))
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(14))
        SUBTRACT_FLOAT(LW(12), FLOAT(0.5f))
        ADD_FLOAT(LW(13), FLOAT(10.0f))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_MET_ON_CEILING, 0)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 12, 15, 0)
    // It hops back toward its original spot and carries on as a floor unit.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_MET_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
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

/** Wait script of the Buzzy Beetle on the ceiling: plays its idle pose from its pose table. */
static EVT_BEGIN(wait_event_ceil)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
