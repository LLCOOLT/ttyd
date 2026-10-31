// Keelhaul Key (muj) battle unit: Cortez's sword (cortez_sword), one of his weapons: its parts, defence/status tables,
// and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "muj.h"

BattleUnitKind unit_boss_cortez_sword;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
BattleWeapon weapon_cortez_sword_float_attack;
#if VERSION <= VERSION_DEMO_US
static PoseTableEntry pose_table[4];
#else
static PoseTableEntry pose_table[6];
#endif
PoseTableEntry pose_table_otitabuki[4];
static PoseTableEntry pose_table_break[4];
static BattleDataEntry data_table[21];
static BattleUnitKindPart parts[1];
static EvtWord init_event[47];
static EvtWord damage_event[10];
static EvtWord avoid_thorn_event[33];
static EvtWord attack_event[862];
static EvtWord wait_event[10];
static EvtWord cortez_damage_sub_event[25];

BattleUnitKind unit_boss_cortez_sword = {
    97,
    "btl_un_cortez_sword",
    4,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    20,
    130,
    30,
    0,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    65.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    65.0f,
    0.0f,
    0.0f,
    65.0f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    130.0f,
    30.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KOR_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x2000004,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 50, 0, 0, 100, 0, 100, 50, 50, 0, 90, 100, 50, 0, 0, 0};
#else
static StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 85, 0, 0, 100, 0, 100, 90, 50, 0, 90, 100, 50, 0, 0, 0};
#endif

BattleWeapon weapon_cortez_sword_float_attack = {
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
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
#if VERSION >= VERSION_JP
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
#endif
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

PoseTableEntry pose_table_otitabuki[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_Z_1"},
};

static PoseTableEntry pose_table_break[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_Z_1"},
};

static BattleDataEntry data_table[] = {
    {9, cortez_damage_sub_event},
    {49, cortez_weapon_dead_event},
#if VERSION <= VERSION_DEMO_US
    {70, cortez_weapon_break_event},
#else
    {71, cortez_weapon_break_event},
#endif
    {58, cortez_weapon_blow_dead_event},
    {36, cortez_weapon_counter_damage_event},
    {24, cortez_weapon_counter_damage_event},
    {25, cortez_weapon_counter_damage_event},
    {26, cortez_weapon_counter_damage_event},
    {27, cortez_weapon_counter_damage_event},
    {28, cortez_weapon_counter_damage_event},
    {29, cortez_weapon_counter_damage_event},
    {30, cortez_weapon_counter_damage_event},
    {31, cortez_weapon_counter_damage_event},
    {32, cortez_weapon_counter_damage_event},
    {33, cortez_weapon_counter_damage_event},
    {34, cortez_weapon_counter_damage_event},
    {35, cortez_weapon_counter_damage_event},
    {39, avoid_thorn_event},
    {37, avoid_thorn_event},
    {38, avoid_thorn_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez_sword", "c_buki2", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3010009, 0x7, pose_table},
};

/** Guess: init event of one of Cortez's floating swords: sets its work values, its slot and its home height. */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(cortez_weapon_phase_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(cortez_weapon_unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Guess: damage event of a sword: runs the default damage reaction. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Guess: event run when a sword touches a spiked attacker: plays its hurt reaction. */
static EVT_BEGIN(avoid_thorn_event)
    CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Works out the height a floating sword of Cortez's should hover at (LW(5)) from his mode (unit work 8 of the
 * owner) and the sword's slot (unit work 2): each slot has its own spot around him.
 */
EVT_BEGIN(cortez_weapon_get_home_height)
    SET_VALUE(LW(5), 0)
    CALL(btlevtcmd_GetPos, LW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitWork, LW(9), 0, LW(3))
    CALL(btlevtcmd_GetUnitWork, LW(3), 8, LW(4))
    SWITCH(LW(4))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 20)
            CASE_EQUAL(1)
            ADD(LW(5), 60)
            CASE_EQUAL(2)
            ADD(LW(5), 60)
            CASE_EQUAL(3)
            ADD(LW(5), 20)
        END_SWITCH
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 20)
            CASE_EQUAL(1)
            ADD(LW(5), 20)
            CASE_EQUAL(2)
            ADD(LW(5), 60)
            CASE_EQUAL(3)
            ADD(LW(5), 60)
        END_SWITCH
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 60)
            CASE_EQUAL(1)
            ADD(LW(5), 20)
            CASE_EQUAL(2)
            ADD(LW(5), 60)
            CASE_EQUAL(3)
            ADD(LW(5), 20)
        END_SWITCH
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            ADD(LW(5), 60)
            CASE_EQUAL(1)
            ADD(LW(5), 20)
            CASE_EQUAL(2)
            ADD(LW(5), 20)
            CASE_EQUAL(3)
            ADD(LW(5), 60)
        END_SWITCH
    END_SWITCH
    RETURN
EVT_END()

/**
 * Sets the sword's hit-detection attribute on its body part according to its home height:
 * a sword raised to 40 or higher gets part attributes 6291456 turned on, a lower one turns them off.
 */
EVT_BEGIN(cortez_weapon_set_formation_attribute)
    CALL(btlevtcmd_GetBodyId, LW(9), LW(0))
    CALL(btlevtcmd_GetHomePos, LW(9), EVT_NULLPTR, LW(1), EVT_NULLPTR)
    IF_INT_GREATER_OR_EQUAL(LW(1), 40)
        CALL(btlevtcmd_OnPartsAttribute, LW(9), LW(0), 6291456)
    ELSE
        CALL(btlevtcmd_OffPartsAttribute, LW(9), LW(0), 6291456)
    END_IF
    RETURN
EVT_END()

/**
 * Phase event run in the unison phase (before the player's turn) for a sword:
 * when Cortez is in mode 4 or later and the sword has no pending delay,
 * it dives to the height for its slot and updates its home position.
 */
EVT_BEGIN(cortez_weapon_unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
#if VERSION >= VERSION_JP
        IF_INT_EQUAL(LW(0), -1)
            RETURN
        END_IF
#endif
        CALL(btlevtcmd_GetUnitWork, LW(0), 5, LW(1))
        IF_INT_GREATER_OR_EQUAL(LW(1), 4)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(9))
#if VERSION >= VERSION_JP
                IF_INT_EQUAL(LW(9), -1)
                    RETURN
                END_IF
#endif
                CALL_CHILD(cortez_weapon_get_home_height)
                IF_INT_NOT_EQUAL(LW(1), LW(5))
                    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 60, 0, 4, 0, -1)
                    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                    CALL_CHILD(cortez_weapon_set_formation_attribute)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                    RETURN
                END_IF
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Per-turn phase event of a sword: counts its timer in unit work 1 down each turn and, when it reaches zero,
 * it spins and swoops to attack (rotation sibling event), returning to its home spot afterwards.
 */
EVT_BEGIN(cortez_weapon_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 0)
                CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                    CALL(evt_sub_intpl_init, 5, -90, 0, 20)
                    CALL(evt_sub_intpl_get_value)
                    LOOP(20)
                        CALL(evt_sub_intpl_get_value)
                        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), 0, 0)
                        WAIT_FRAMES(1)
                    END_LOOP
                END_SIBLING_EVENT
                CALL(btlevtcmd_WaitEventEnd, LW(0))
                CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(9))
                CALL_CHILD(cortez_weapon_get_home_height)
                CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 60, 0, 4, 0, -1)
                CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                CALL_CHILD(cortez_weapon_set_formation_attribute)
                CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_ClearAllStatus, BTL_UNIT_SELF)
                CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 65536)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
                CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, 33554432)
                CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                RETURN
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Guess: attack event of a sword: it swings at one target, spinning,
 * with the sword sounds and a hit for the weapon damage, then returns to its home spot.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(&weapon_cortez_sword_float_attack))
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
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_Z_1"))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 48, 19, 0)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 0, 0, -30, 30)
        CALL(evt_sub_intpl_get_value)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(10)
        CALL(evt_sub_intpl_init, 2, 0, -55, 30)
        CALL(evt_sub_intpl_get_value)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(1), -20)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 105)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, -10, 4, 0, 0)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 52, 0, 1, 0, 0)
    END_SIBLING_EVENT
    CALL(evt_sub_random, 40, LW(5))
    ADD(LW(5), 12)
    WAIT_FRAMES(LW(5))
    DELETE_EVENT(LW(15))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(evt_sub_intpl_init, 2, 0, 475, 30)
        CALL(evt_sub_intpl_get_value)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            ADD(LW(0), -55)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_DANCE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(1), -20)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 45)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 28, 0, 0, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(40)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(40)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(40)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(40)
        CASE_DEFAULT
        GOTO(41)
    END_SWITCH
    LABEL(40)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    GOTO(45)
    LABEL(41)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 0, LW(6))
    IF_INT_EQUAL(LW(6), 21)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
        ADD(LW(1), 15)
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init, 5, -30, 0, 20)
            CALL(evt_sub_intpl_get_value)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init, 5, 0, -30, 20)
            CALL(evt_sub_intpl_get_value)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 21, 0, 5, 0, -1)
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init, 4, -30, 0, 20)
            CALL(evt_sub_intpl_get_value)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 4, 0, -1)
        RETURN
    END_IF
    LABEL(45)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    WAIT_MS(800)
    LABEL(50)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 2, 60, -225, 30)
        CALL(evt_sub_intpl_get_value)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 2, -30, -90, 20)
        CALL(evt_sub_intpl_get_value)
        LOOP(20)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 35)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -15, 5, 0, -1)
    WAIT_MS(300)
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(evt_sub_intpl_init, 5, -225, 180, 30)
        CALL(evt_sub_intpl_get_value)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(1), -20)
        CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 60)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 6, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_DANCE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    WAIT_FRAMES(7)
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_DEFAULT
        GOTO(91)
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    GOTO(95)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(6))
    IF_INT_EQUAL(LW(6), 21)
        DELETE_EVENT(LW(14))
        DELETE_EVENT(LW(15))
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
        ADD(LW(1), 15)
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init, 5, 0, -30, 20)
            CALL(evt_sub_intpl_get_value)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 21, 0, 5, 0, -1)
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init, 4, -30, 0, 20)
            CALL(evt_sub_intpl_get_value)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 4, 0, -1)
        RETURN
    END_IF
    LABEL(95)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    WAIT_MS(300)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(evt_sub_intpl_init, 11, -90, 0, 10)
        CALL(evt_sub_intpl_get_value)
        LOOP(10)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_GetStageSize, LW(1), EVT_NULLPTR, EVT_NULLPTR)
    ADD(LW(1), 80)
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(1))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(5.0f), LW(13))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(13), 0, 1, 0, -1)
    WAIT_MS(500)
    CALL(btlevtcmd_GetStageSize, LW(1), EVT_NULLPTR, EVT_NULLPTR)
    ADD(LW(1), 80)
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), LW(1))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 4, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Guess: wait (idle) event of a sword: keeps its default idle pose. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Guess: sub-event of a sword damage handling: applies the knock-back for a hit part,
 * then continues in the default damage flow.
 */
static EVT_BEGIN(cortez_damage_sub_event)
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(11))
    CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("KRT_Z_1"))
    WAIT_FRAMES(30)
    LABEL(90)
    RETURN
EVT_END()

/**
 * Damage event of a sword hit during Cortez's counter phase:
 * flags the unit hit and, depending on the damage code, plays the knocked-back pose,
 * runs the sword's data event and lets it fall under gravity.
 */
EVT_BEGIN(cortez_weapon_counter_damage_event)
    CALL(btlevtcmd_OnUnitFlag, LW(10), 1)
    SWITCH(LW(0))
        CASE_EQUAL(43)
        CALL(evt_snd_sfxon, STRING("SFX_BTL_ATTACK_MISS3"), 0)
        SET_VALUE(LW(14), 36)
        CASE_OR_EQUAL(46)
        CASE_OR_EQUAL(49)
        CASE_OR_EQUAL(50)
        CASE_OR_EQUAL(54)
        SET_VALUE(LW(14), 29)
        CASE_END
        CASE_DEFAULT
        SET_VALUE(LW(14), 39)
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(10), LW(2), LW(3), LW(4))
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(2), 25)
    ADD(LW(3), 25)
    CALL(btlevtcmd_DivePosition, LW(10), LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetHomePos, LW(10), LW(2), LW(3), LW(4))
    CALL(btlevtcmd_TransStageFloorPosition, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(2), LW(3), LW(4), 20, -1)
    CALL(btlevtcmd_JumpPosition, LW(10), LW(2), LW(3), LW(4), 10, -1)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Guess: death event of a sword: runs cortez_weapon_dead_event. */
static EVT_BEGIN(dead_event)
    RETURN
EVT_END()

/**
 * Death event of a sword: it falls to the stage floor with a clatter, bounces once, sets its home there,
 * marks itself dead (unit work 1 = 2) and makes the body part untargetable.
 */
EVT_BEGIN(cortez_weapon_dead_event)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    ADD(LW(1), 1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.39941406f))
    CALL(btlevtcmd_FallPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 0, 0, -90, 15)
        CALL(evt_sub_intpl_get_value)
        LOOP(15)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 2)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 65536)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_break))
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 33554432)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Break event of a sword: tells its owner Cortez that this slot is gone (writes -1 into the owner's unit work
 * for the sword's slot), so he no longer counts it.
 */
EVT_BEGIN(cortez_weapon_break_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(1))
        SWITCH(LW(1))
            CASE_EQUAL(0)
            CALL(btlevtcmd_SetUnitWork, LW(0), 1, -1)
            CASE_EQUAL(1)
            CALL(btlevtcmd_SetUnitWork, LW(0), 2, -1)
            CASE_EQUAL(2)
            CALL(btlevtcmd_SetUnitWork, LW(0), 3, -1)
            CASE_EQUAL(3)
            CALL(btlevtcmd_SetUnitWork, LW(0), 4, -1)
        END_SWITCH
    END_IF
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 50331648)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Death event used when a sword is blown away: it spins at 20 degrees per frame
 * and flies off the side of the stage; its coins and experience are stored for the player before it leaves.
 */
EVT_BEGIN(cortez_weapon_blow_dead_event)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_CLAUD_BREATH3"), 0)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), 39)
    BEGIN_SIBLING_EVENT
        LABEL(0)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 20, 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    ADD(LW(1), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 2, 0, -1)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(1))
        SWITCH(LW(1))
            CASE_EQUAL(0)
            CALL(btlevtcmd_SetUnitWork, LW(0), 1, -1)
            CASE_EQUAL(1)
            CALL(btlevtcmd_SetUnitWork, LW(0), 2, -1)
            CASE_EQUAL(2)
            CALL(btlevtcmd_SetUnitWork, LW(0), 3, -1)
            CASE_EQUAL(3)
            CALL(btlevtcmd_SetUnitWork, LW(0), 4, -1)
        END_SWITCH
    END_IF
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()
