// Keelhaul Key (muj) battle unit: Cortez Sabre (cortez_saber), Cortez's saber, one of his weapons: its parts, defence/status tables,
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
#include "muj.h"

// Unit work slots of Cortez's saber (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_BOSS_CORTEZ_SABER_REVIVE_COUNTDOWN = 1, // turns until it rises again while knocked down; 0 when up
    UW_BOSS_CORTEZ_SABER_FORMATION_SLOT = 2    // its slot (0 to 3) in Cortez's weapon formation
};

BattleUnitKind unit_boss_cortez_saber;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
BattleWeapon weapon_cortez_saber_float_attack;
#if VERSION <= VERSION_DEMO_JP
static PoseTableEntry pose_table[4];
#else
static PoseTableEntry pose_table[6];
#endif
static PoseTableEntry pose_table_break[4];
static BattleDataEntry data_table[21];
static BattleUnitKindPart parts[1];
static EvtWord init_event[47];
static EvtWord damage_event[10];
static EvtWord avoid_thorn_event[33];
static EvtWord attack_event[414];
static EvtWord wait_event[10];
static EvtWord cortez_damage_sub_event[25];

/**
 * Unit data of Cortez Sabre: 4 HP, 120x50 units in size; ties together its sounds, parts,
 * status vulnerability, init event and event table.
 */
BattleUnitKind unit_boss_cortez_saber = {
    98,
    "btl_un_cortez_saber",
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
    120,
    50,
    0,
    30,
    0.0f,
    25.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    0.0f,
    60.0f,
    32.5f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    120.0f,
    50.0f,
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

/** Defence of Cortez Sabre: 0 against every kind of hit. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of Cortez Sabre: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo builds: Status vulnerability of Cortez Sabre (percent chance each status takes hold):
 * immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible, instant KO; resists freeze (50%),
 * Defense Down (50%), allergic (50%), Slow (50%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 50, 0, 0, 100, 0, 100, 50, 50, 0, 90, 100, 50, 0, 0, 0};
#else
/**
 * Retail builds: Status vulnerability of Cortez Sabre (percent chance each status takes hold):
 * immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible, instant KO; resists allergic (50%),
 * Slow (50%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 85, 0, 0, 100, 0, 100, 90, 50, 0, 90, 100, 50, 0, 0, 0};
#endif

/**
 * Weapon of Cortez Sabre (float attack): targets one unit for 3 damage; used by attack_event.
 */
BattleWeapon weapon_cortez_saber_float_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/** Pose table of Cortez Sabre: maps its battle poses to its animations (KRT_*). */
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

/** Pose table of Cortez Sabre once it is broken off: only the lying pose KRT_Z_1. */
static PoseTableEntry pose_table_break[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_Z_1"},
};

/**
 * Event table of Cortez Sabre: cortez_damage_sub_event (tag 9), cortez_weapon_dead_event (tag 49),
 * cortez_weapon_break_event (tags 70, 71), cortez_weapon_blow_dead_event (tag 58),
 * cortez_weapon_counter_damage_event (tags 36, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35),
 * avoid_thorn_event (tags 39, 37, 38).
 */
static BattleDataEntry data_table[] = {
    {9, cortez_damage_sub_event},
    {49, cortez_weapon_dead_event},
#if VERSION <= VERSION_DEMO_JP
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

/** Parts of Cortez Sabre: 1 part (model c_buki1). */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez_saber", "c_buki1", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3010009, 0x6, pose_table},
};

/**
 * Init event of Cortez's saber weapon: sets UNIT_FLAG_NO_BACKFACE_FLIP, installs its wait, phase, unison phase,
 * attack, damage and (default) confusion events,
 * stores weapon number 1 in unit work 2 and clears unit work 1 (the flag that makes it sit out its attack),
 * and allows no movement.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(cortez_weapon_phase_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(cortez_weapon_unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_CORTEZ_SABER_FORMATION_SLOT, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_CORTEZ_SABER_REVIVE_COUNTDOWN, 0)
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of Cortez's saber: runs the default damage handling with LW(10) = -2 and LW(11) = 1. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data event (tags 37 to 39) run when an attacker is hurt by the saber's spikes:
 * shows the toge_flush spike flash at its hit position on part 1, 40 forward and 5 back in z.
 */
static EVT_BEGIN(avoid_thorn_event)
    CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Attack event of Cortez's saber; while knocked down (unit work 1, its revive countdown, is not 0) it only
 * restarts the wait event.
 * Otherwise it picks a target with weapon_cortez_saber_float_attack,
 * winds up with a tilt of 60 degrees and a swing of 135,
 * dives onto the target and slashes down with the sword-dance sound.
 * It plays the avoid pose on a dodge, or applies the damage with the action command defence check,
 * A superguarded saber recoils home at once; otherwise it returns home and straightens.
 */
static EVT_BEGIN(attack_event)
    // While the Sabre is knocked down it only goes back to idling.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_CORTEZ_SABER_REVIVE_COUNTDOWN, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(&weapon_cortez_saber_float_attack))
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
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 38, 15, 0)
    // The Sabre tilts back 60 degrees and winds up with a swing of 135 degrees.
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 0, 0, -60, 20)
        LOOP(20)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init, 2, 0, -135, 30)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 35)
    // It dives onto the target.
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 50, -10, 4, 0, -1)
    WAIT_MS(200)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(evt_sub_intpl_init, 0, -135, 60, 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // It slashes down with a whooshing sound.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_DANCE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(7)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
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
    // The slash misses or is blocked: the Sabre plays its dodge reaction.
    LABEL(90)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    GOTO(95)
    // The slash lands: the Action Command defence result and damage are applied.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    // If the target Superguarded, the Sabre is repelled: it tumbles backwards and recoils home at once.
    IF_INT_EQUAL(LW(5), 21)
        DELETE_EVENT(LW(15))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
        ADD(LW(1), 15)
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init, 5, -60, 0, 20)
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
    // Otherwise it straightens up and returns home after a short pause.
    LABEL(95)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    WAIT_MS(500)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 11, -60, 0, 15)
        LOOP(15)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init, 11, 60, 0, 15)
        LOOP(15)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, EVT_NULLPTR, EVT_NULLPTR, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -10, 4, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Idle event of Cortez's saber: waits for the loop timing of its animation
 * and plays the pose table pose for state 1.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Data event (entry 9) of Cortez's saber: when the weapon takes damage it plays the KRT_Z_1 pose on the unit in
 * LW(10) and waits 30 frames.
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
