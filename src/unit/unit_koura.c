// Battle unit data for the Koopa shell (unit_koura), used by Koops, with its cracked poses.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "version.h"

BattleUnitKind unit_koura;
static BattleDataEntry data_table[7];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[5];
PoseTableEntry pose_table_crack_lv1[5];
PoseTableEntry pose_table_crack_lv2[5];
static BattleUnitKindPart parts[2];
static EvtWord init_event[46];
#if VERSION <= VERSION_DEMO_US
static EvtWord phase_event[22];
#else
static EvtWord phase_event[38];
#endif
extern EvtWord koura_open[];
extern EvtWord koura_close[];
extern EvtWord damage_core[];
extern EvtWord pose_tbl_reset[];
static EvtWord dead_event[243];
extern EvtWord destroy_event[];
static EvtWord damage_event[10];
static EvtWord wait_event[6];
static EvtWord attack_event[2];

BattleUnitKind unit_koura = {
    223,
    "btl_un_koura",
    8,
    0,
    5,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    24,
    24,
    24,
    24,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    25.0f,
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
    "SFX_BTL_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {28, "PKO_S_1"},
    {31, "PKO_S_1"},
    {39, "PKO_D_1"},
    {BTL_POSE_SHELL_SHIELD, "PKO_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "PKO_S_1"},
};

PoseTableEntry pose_table_crack_lv1[] = {
    {28, "PKO_S_2"},
    {31, "PKO_S_2"},
    {39, "PKO_D_2"},
    {BTL_POSE_SHELL_SHIELD, "PKO_Z_2"},
    {BTL_POSE_STAY_DEFAULT, "PKO_S_2"},
};

PoseTableEntry pose_table_crack_lv2[] = {
    {28, "PKO_S_3"},
    {31, "PKO_S_3"},
    {39, "PKO_D_3"},
    {BTL_POSE_SHELL_SHIELD, "PKO_Z_3"},
    {BTL_POSE_STAY_DEFAULT, "PKO_S_3"},
};

static BattleDataEntry data_table[] = {
    {59, koura_open},
    {60, koura_close},
    {9, damage_core},
    {61, pose_tbl_reset},
    {62, destroy_event},
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_koura", "c_koura", 0.0f, 0.0f, 0.0f, 20.0f, 40.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_UNTATTLEABLE, 0, pose_table},
    {2, "btl_un_koura", "c_koura", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, pose_table},
};

/**
 * Init for Koops's Shell Shield shell: draws it at 1.5x scale, registers the wait, phase,
 * attack and damage scripts, and clears the open flag, open-for-turn flag and crack stage (unit work 1-3).
 * Unit work 0 holds the shielded unit.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetBaseScale, BTL_UNIT_SELF, FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.5f))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Hit reaction: the default damage script with no special pose (LW10 = -2); the crack poses come from damage_core. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Opens the shell off Mario before the player phase and closes it again after.
 * Since the US release it skips both when the shell has no HP left.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
#if VERSION <= VERSION_DEMO_US
        CALL_CHILD(koura_open)
#else
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL_CHILD(koura_open)
        END_IF
#endif
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
#if VERSION <= VERSION_DEMO_US
        CALL_CHILD(koura_close)
#else
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL_CHILD(koura_close)
        END_IF
#endif
    END_IF
    RETURN
EVT_END()

/**
 * Shell Shield: tilts the shell up off Mario over 30 frames before his turn (data tag 59).
 * Shows Mario, makes him targetable again and the shell untargetable, and sets unit work 1 (open) and 2.
 * Does nothing if already open.
 */
EVT_BEGIN(koura_open)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, -23, 0, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(3))
    CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN)
    LOOP(30)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, 2)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
    CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_NOT_SAMPLED_AS_TARGET)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_SHELL_SHIELD)
    RETURN
EVT_END()

/**
 * Shell Shield: lowers the shell back over Mario after his turn (data tag 60),
 * hiding him and making the shell the target again. Also run before a Mario/partner position swap.
 * Does nothing if already closed.
 */
EVT_BEGIN(koura_close)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, -23, 0, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 60)
    LOOP(30)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, -2)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(3))
    CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_NOT_SAMPLED_AS_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle: just plays the stay pose from the current (crack-stage) pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Shell Shield damage reaction (data tag 9): picks the intact,
 * cracked or badly cracked pose table from the shell's HP (above 6, 4-6, 3 or less),
 * plays the crack sound when the stage changes, and records the stage in unit work 3.
 */
EVT_BEGIN(damage_core)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(1))
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(3)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_crack_lv2))
        IF_INT_NOT_EQUAL(LW(1), 2)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_NOKO_GUARD3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_IF
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 2)
        CASE_LESS_OR_EQUAL(6)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_crack_lv1))
        IF_INT_NOT_EQUAL(LW(1), 1)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_NOKO_GUARD3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_IF
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
        CASE_DEFAULT
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        IF_INT_NOT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_NOKO_GUARD3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_IF
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 39)
#if VERSION <= VERSION_DEMO_US
    WAIT_FRAMES(30)
#else
    WAIT_MS(500)
#endif
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data tag 61: reapplies the crack-stage pose table for the shell's current HP (as damage_core does, but without
 * the hurt pose); plays the crack sound unless the shell is intact.
 */
EVT_BEGIN(pose_tbl_reset)
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(3)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_crack_lv2))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_NOKO_GUARD3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 2)
        CASE_LESS_OR_EQUAL(6)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_crack_lv1))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_NOKO_GUARD3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
        CASE_DEFAULT
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Death data event (tag 49): the shell breaks.
 * Gives the shielded unit back its normal targeting and visibility, plays the break sound,
 * then the two halves (parts 1 and 2) spring apart, tip over and blink out before the unit is removed.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(3))
    CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_SHELL_SHIELDED | UNIT_ATTR_NOT_SAMPLED_AS_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_NOKO_GUARD4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKO_H_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("PKO_H_2"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, 1, 23, 0, 0)
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, 2, -23, 0, 0)
    BEGIN_SIBLING_EVENT
        LOOP(5)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 1, 0, 1, 0)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 2, 0, 1, 0)
            WAIT_FRAMES(2)
        END_LOOP
        LOOP(6)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 1, 0, 1, 0)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 2, 0, 1, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(2)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 1, 0, 1, 0)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 2, 0, 1, 0)
            WAIT_FRAMES(2)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 1, -1, 0, 0)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 2, 1, 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(5)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 1, -1, 0, 0)
            CALL(btlevtcmd_AddPartsDispOffset, BTL_UNIT_SELF, 2, 1, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_AddPartsRotateOffset, BTL_UNIT_SELF, 1, 0, 1, 0)
            CALL(btlevtcmd_AddPartsRotateOffset, BTL_UNIT_SELF, 2, 0, 1, 0)
            WAIT_FRAMES(2)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(14)
            CALL(btlevtcmd_AddPartsRotateOffset, BTL_UNIT_SELF, 1, -1, 0, 0)
            CALL(btlevtcmd_AddPartsRotateOffset, BTL_UNIT_SELF, 2, 1, 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    LOOP(20)
        CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 1, 0, 0, 2)
        CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 2, 0, 0, -2)
        WAIT_FRAMES(1)
    END_LOOP
    LOOP(8)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        WAIT_FRAMES(2)
    END_LOOP
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Data tag 62: removes the shell instantly in a puff of smoke,
 * giving Mario back his normal targeting and visibility, without the split-in-two break animation of dead_event.
 */
EVT_BEGIN(destroy_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(3))
    CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_SHELL_SHIELDED | UNIT_ATTR_NOT_SAMPLED_AS_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/** The shell never acts on its own turn; empty. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()
