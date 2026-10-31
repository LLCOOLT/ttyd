// Keelhaul Key (muj) battle unit: Cortez Rapier (cortez_rapier), Cortez's rapier, one of his weapons: its parts, defence/status
// tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "muj.h"

// Unit work slots of this unit (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_BOSS_CORTEZ_RAPIER_DOWN_COUNT = 1, // revive countdown while knocked down (0: active)
    UW_BOSS_CORTEZ_RAPIER_WEAPON_NO = 2,  // which of Cortez's weapons this is (3 for the rapier)
};

BattleUnitKind unit_boss_cortez_rapier;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
BattleWeapon weapon_cortez_rapier_float_attack;
#if VERSION <= VERSION_DEMO_JP
static PoseTableEntry pose_table[4];
#else
static PoseTableEntry pose_table[6];
#endif
static BattleDataEntry data_table[21];
static BattleUnitKindPart parts[1];
static EvtWord init_event[47];
static EvtWord damage_event[10];
static EvtWord avoid_thorn_event[33];
static EvtWord attack_event[545];
static EvtWord wait_event[10];
static EvtWord cortez_damage_sub_event[25];

/**
 * Unit data of Cortez Rapier: 4 HP, 140x30 units in size; ties together its sounds, parts,
 * status vulnerability, init event and event table.
 */
BattleUnitKind unit_boss_cortez_rapier = {
    96,
    "btl_un_cortez_rapier",
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
    140,
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
    70.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    70.0f,
    0.0f,
    0.0f,
    70.0f,
    19.5f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    140.0f,
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
    UNIT_ATTR_FLOATING | UNIT_ATTR_NO_HP_GAUGE,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of Cortez Rapier: 0 against every kind of hit. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of Cortez Rapier: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo builds: Status vulnerability of Cortez Rapier (percent chance each status takes hold):
 * immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible, instant KO; resists freeze (50%),
 * Defense Down (50%), allergic (50%), Slow (50%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 50, 0, 0, 100, 0, 100, 50, 50, 0, 90, 100, 50, 0, 0, 0};
#else
/**
 * Retail builds: Status vulnerability of Cortez Rapier (percent chance each status takes hold):
 * immune to sleep, Huge, Tiny, Attack Down, fright, Dodgy, Invisible, instant KO; resists allergic (50%),
 * Slow (50%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 80, 95, 100, 90, 100, 100, 85, 0, 0, 100, 0, 100, 90, 50, 0, 90, 100, 50, 0, 0, 0};
#endif

/**
 * Weapon of Cortez Rapier (float attack): targets every unit for 2 damage, ignores Defense;
 * used by attack_event.
 */
BattleWeapon weapon_cortez_rapier_float_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Pose table of Cortez Rapier: maps its battle poses to its animations (KRT_*). */
static PoseTableEntry pose_table[] = {
#if VERSION >= VERSION_JP
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
#endif
    {BTL_POSE_NORMAL, "KRT_S_1"},
    {31, "KRT_S_1"},
    {BTL_POSE_DAMAGE, "KRT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Event table of Cortez Rapier: cortez_damage_sub_event (tag 9), cortez_weapon_dead_event (tag 49),
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

/** Parts of Cortez Rapier: 1 part (model c_buki3). */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez_rapier", "c_buki3", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, COUNTER_ATTR_PREEMPTIVE_FRONT_SPIKY | COUNTER_ATTR_FRONT_SPIKY, pose_table},
};

/**
 * Init event of Cortez's rapier weapon: sets the unit flag 0x1000000, installs its wait, phase, unison phase,
 * attack, damage and (default) confusion events,
 * stores weapon number 3 in unit work 2 and clears unit work 1 (the flag that makes it sit out its attack),
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_CORTEZ_RAPIER_WEAPON_NO, 3)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_CORTEZ_RAPIER_DOWN_COUNT, 0)
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of Cortez's rapier: runs the default damage handling with LW(10) = -2 and LW(11) = 1. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data event (tags 37 to 39) run when an attacker is hurt by the rapier's spikes:
 * shows the toge_flush spike flash at its hit position on part 1, 40 forward and 5 back in z.
 */
static EVT_BEGIN(avoid_thorn_event)
    CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/** Phase event of the rapier: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/**
 * Attack event of Cortez's rapier; while knocked down (unit work 1, its revive countdown, is not 0) it only
 * restarts the wait event.
 * Otherwise it takes the selected targets of
 * weapon_cortez_rapier_float_attack, spins in the KRT_Z_1 pose (six turns in 60 frames) with the sword-dance
 * sound while it flies across the stage through them,
 * damage-checking each target as it passes (avoid poses on a dodge, defence check on the first),
 * then returns home.
 */
static EVT_BEGIN(attack_event)
    // While the Rapier is knocked down it only goes back to idling.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_CORTEZ_RAPIER_DOWN_COUNT, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(12), PTR(&weapon_cortez_rapier_float_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, BTL_UNIT_SELF, 1)
    // The Rapier lies flat and spins six times in 60 frames, boring through the air.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_Z_1"))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 13, 0)
        CALL(evt_sub_intpl_init, 0, 0, -2160, 60)
        LOOP(60)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, LW(0), 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), EVT_NULLPTR, EVT_NULLPTR, LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 20)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 0, 4, 0, -1)
    // It flies across the whole stage through every target, with a whirring sound.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_DANCE2"), EVT_NULLPTR, 0, LW(9))
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        SET_VALUE(LW(5), 5)
        LOOP(LW(5))
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfx_pos, LW(9), LW(0), LW(1), LW(2))
            WAIT_FRAMES(1)
            SET_VALUE(LW(5), 5)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 13, 0)
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(5), 5)
        LOOP(LW(5))
            IF_INT_LESS(LW(0), 118)
                ADD(LW(0), 1)
            END_IF
            SET_VALUE(LW(1), LW(0))
            DIVIDE(LW(1), 2)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, LW(1), 0, 0)
            SET_VALUE(LW(5), 5)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(0), 0)
        CALL(btlevtcmd_GetStageSize, LW(5), EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), LW(5))
        CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(7.0f), LW(14))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(14), 0, 1, 0, 0)
    END_SIBLING_EVENT
    SET_VALUE(LW(10), 0)
    // As it passes each target, that target is checked in turn.
    LABEL(10)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(1), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(1), 40)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(2))
    IF_INT_GREATER_OR_EQUAL(LW(2), 0)
        IF_INT_LESS(LW(0), LW(1))
            WAIT_FRAMES(1)
            GOTO(10)
        END_IF
    ELSE
        IF_INT_GREATER(LW(0), LW(1))
            WAIT_FRAMES(1)
            GOTO(10)
        END_IF
    END_IF
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
        CASE_EQUAL(1)
        GOTO(91)
        CASE_DEFAULT
        GOTO(97)
    END_SWITCH
    LABEL(90)
    GOTO(97)
    // A hit applies the damage (the Action Command defence result is used for the first target only).
    LABEL(91)
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    // If a target Superguarded, the Rapier is repelled: it tumbles backwards and recoils home at once.
    IF_INT_EQUAL(LW(5), 21)
        DELETE_EVENT(LW(13))
        CALL(evt_snd_sfxoff, LW(9))
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
    // After the last target, it flies back in from the other side of the stage and returns home.
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    DELETE_EVENT(LW(14))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), LW(0))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(14))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(14), 0, 5, 0, -1)
    DELETE_EVENT(LW(13))
    CALL(evt_snd_sfxoff, LW(9))
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Idle event of Cortez's rapier: waits for the loop timing of its animation
 * and plays the pose table pose for state 1.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeWaitPlayLoopTiming, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Data event (entry 9) of Cortez's rapier: when the weapon takes damage it plays the KRT_Z_1 pose on the unit in
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
