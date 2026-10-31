// unit_npc_christine: Goombella as a non-partner battle unit (NPC version).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"

BattleUnitKind unit_npc_christine;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[25];
static EvtWord damage_event[10];
static EvtWord attack_event[5];
static EvtWord wait_event[6];

/**
 * Unit kind of Goombella:
 * 10 HP, level 1, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_npc_christine = {
    221,
    "btl_un_christine",
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
    24,
    24,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    30.0f,
    0.0f,
    0.0f,
    30.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
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
    UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of Goombella's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of Goombella's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Status vulnerability of Goombella: immune to every status. */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Pose table of Goombella:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table[] = {
    {BTL_POSE_NORMAL, "PKR_S_1"},
    {31, "PKR_S_1"},
    {BTL_POSE_DAMAGE, "PKR_S_1"},
    {BTL_POSE_STAY_DEFAULT, "PKR_S_1"},
};

/** Event table of Goombella: empty, so it has no special reactions. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/** Body part of Goombella: a single part using the model "c_pkr". */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_christine", "c_pkr", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_TARGETABLE | PART_ATTR_UNTATTLEABLE, 0, pose_table},
};

/** Init event of Goombella as an NPC battle unit: installs attack, damage and confusion events and forbids movement. */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of Goombella as an NPC: runs the default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event of Goombella as an NPC: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Attack event of Goombella as an NPC: does nothing and returns to waiting. */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of Goombella as an NPC: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
