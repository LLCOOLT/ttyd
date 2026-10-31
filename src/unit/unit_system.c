// Battle unit data for the invisible system unit (unit_system) that runs battle-wide scripts.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"
#include "version.h"

static BattleUnitKindPart parts[1];
BattleUnitKind unit_system;
static EvtWord init_event[21];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleDataEntry data_table[1];
static StatusVulnerability regist;
static EvtWord damage_event[2];
static EvtWord attack_event[2];
static EvtWord wait_event[2];

/** The system unit's single part: hidden, untargetable and without a shadow, so it never appears on stage. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_system", NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, NULL},
};

#if VERSION <= VERSION_DEMO_JP
// the demo defines regist here (it is .data there, small data in retail)
/** Status chances for the system unit: all 0, so no status can ever land on it. */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

/**
 * The invisible system unit that the battle enters before Mario (entryunit_system in battle.c).
 * It has no HP gauge, locked HP and is ignored when checking for a cleared battle;
 * it exists to run battle-wide scripts.
 */
BattleUnitKind unit_system = {
    220,
    "btl_un_system",
    999,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
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
    UNIT_ATTR_NO_GRAVITY_BOB | UNIT_ATTR_ACTS_IN_ZERO_GRAVITY | UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR | UNIT_ATTR_HP_LOCKED,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/**
 * Init for the invisible system unit that Btl_UnitSetup enters before Mario (entryunit_system):
 * registers the empty wait, attack and damage scripts, never moves, and idles.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Defence 0 against every element; it never takes hits anyway. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element response of the system unit: immune to every kind of hit. */
static BattleUnitDefenseAttr defence_attr = {{2, 2, 2, 2, 2}};

/** Data events for the system unit: none. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

#if VERSION >= VERSION_JP
/** Status chances for the system unit: all 0, so no status can ever land on it. */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

/** Hit reaction: nothing; the system unit cannot be hurt (its HP is locked). */
static EVT_BEGIN(damage_event)
    RETURN
EVT_END()

/** The system unit never acts on its own turn; empty. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

/** Idle: nothing. */
static EVT_BEGIN(wait_event)
    RETURN
EVT_END()
