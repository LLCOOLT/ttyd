// Battle unit for a Boo (テレサ) acting in Flurrie's stage play in the epilogue (nok.rel); it only plays its
// scripted part.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"
#include "version.h"

BattleUnitKind unit_act_teresa;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[7];
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[9];
static EvtWord wait_event[6];

/**
 * Unit kind of the Boo actor (HP 10, level 1): its size, offsets, damage sounds, status vulnerability,
 * parts and init event.
 */
BattleUnitKind unit_act_teresa = {
    UNIT_EPILOGUE_BOO,
    "btl_un_act_teresa",
    10,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    28,
    24,
    5,
    25,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    30.0f,
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
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Boo actor: no damage reduction. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element reactions of the Boo actor: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the Boo actor (percent chance to take each status):
 * immune to sleep, stop, dizzy, poison, confusion, electric shock, burn, freeze, growing huge, shrinking,
 * attack up, attack down, defence up, defence down, allergy, fright, gale force, speed up, slow, dodgy,
 * invisibility and instant kill.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/** Pose table of the Boo actor: maps each battle pose to the animation it plays (S_* animations). */
static PoseTableEntry pose_table[] = {
    {BTL_POSE_NORMAL, "S_1"},
    {31, "A_2"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Data table of the Boo actor: empty; it has no event hooks. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/** Body part of the Boo actor (model c_teresa): hit position, defences, attributes and pose table. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_teresa", "c_teresa", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/**
 * Init event of the Boo stage actor: installs only its wait event and starts it;
 * this unit never attacks or takes damage.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Boo stage actor: does nothing. */
static EVT_BEGIN(damage_event)
    RETURN
EVT_END()

/** Phase event of the Boo stage actor: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Attack event of the Boo stage actor: does nothing. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

/** Idle event of the Boo stage actor: shows the unit's table pose for state 1. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
