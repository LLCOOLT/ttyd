// Battle unit data for the tree stage object (unit_object_tree).
#include "battle/battle.h"
#include "battle/battle_stage_object.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "version.h"

static USER_FUNC(_rumble_tree);
static USER_FUNC(_turn_tree);

static BattleUnitKindPart parts[1];
static EvtWord init_event[25];
static EvtWord damage_event[14];
#if VERSION <= VERSION_DEMO_US
static s32 _data[34];
#else
static s32 _data[35];
#endif
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[4];
static BattleDataEntry data_table[1];
static EvtWord attack_event[5];
static EvtWord wait_event[2];

BattleUnitKind unit_object_tree = {
    216,
    "btl_un_tree",
    999,
    0,
    1,
    1,
    2,
    0,
    0,
    0,
    0,
    100,
    9,
    24,
    24,
    0,
    0,
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
    UNIT_ATTR_TARGET_SORT_OFFSET | UNIT_ATTR_NO_GRAVITY_BOB | UNIT_ATTR_ACTS_IN_ZERO_GRAVITY | UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {28, "M_S_1"},
    {31, "M_S_1"},
    {39, "M_O_1"},
    {BTL_POSE_STAY_DEFAULT, "M_S_1"},
};

static BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_tree", "b_mario", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, pose_table},
};

/**
 * Init for a stage tree the player can hit (spawned by battle_stage_object.c as _entry_tree_data):
 * registers the wait, attack and damage scripts, never moves, and idles. Its part is hidden and has no shadow.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Hit reaction: wobbles the tree object up and down (_rumble_tree),
 * then tips it over to 90 degrees and snaps it back upright (_turn_tree).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(_rumble_tree, BTL_UNIT_SELF)
    CALL(_turn_tree, -2)
    RETURN
EVT_END()

/** The tree never acts on its own turn; it just returns to its (empty) idle script. */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static s32 _data[] = {
    -5, 0, 15, 0, -15, 0, 14, 0,
    -13, 0, 12, 0, -11, 0, 10, 0,
    -9, 0, 8, 0, -7, 0, 6, 0,
    -6, 0, 5, 0, -4, 0, 2, 0,
#if VERSION <= VERSION_DEMO_US
    -2, 0,
#else
    -2, 0, 0,
#endif
};

/** Idle: nothing; the tree has no idle animation. */
static EVT_BEGIN(wait_event)
    RETURN
EVT_END()

/**
 * Shakes the tree's stage object (args[0] unit) when it is hit:
 * adds one entry of the _data offset table to its height each frame for 34 frames,
 * a decaying up-and-down wobble. Run from damage_event before _turn_tree.
 */
static USER_FUNC(_rumble_tree) {
    BattleUnit* unit;
    BattleStageObject* object;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (!unit) {
        return EVT_RETURN_DONE;
    }
    object = BattleGetObjectPtr(unit->stageObjectId);
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    object->position.y += _data[event->userdata[0]];
    event->userdata[0]++;
    if ((u32)event->userdata[0] >= 34) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Tilts the tree's stage object (the running unit) about X by 3 degrees a frame up to 90 over 30 frames,
 * then snaps it back upright. Run from damage_event after _rumble_tree.
 */
static USER_FUNC(_turn_tree) {
    BattleUnit* unit;
    BattleStageObject* object;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    object = BattleGetObjectPtr(unit->stageObjectId);
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    event->userdata[0] += 3;
    if (event->userdata[0] > 90) {
        object->rotation.x = 0.0f;
        return EVT_RETURN_DONE;
    }
    object->rotation.x = event->userdata[0];
    return EVT_RETURN_BLOCK;
}
