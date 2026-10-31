// Battle unit data for the switch stage object (unit_object_switch).
#include "battle/battle.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_stage_object.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_map.h"
#include "manager/evtmgr_cmd.h"
#include "version.h"

static USER_FUNC(_rumble_switch);

static BattleUnitKindPart parts[1];
static StatusVulnerability regist;
static BattleDataEntry data_table[1];
static EvtWord init_event[25];

BattleUnitKind unit_object_switch = {
    UNIT_UNUSED_SWITCH,     // unitType
    "btl_un_switch",        // name
    999,                    // maxHp
    0,                      // maxFp
    1,                      // dangerHP
    1,                      // perilHP
    2,                      // level
    0,                      // bonusExp
    0,                      // bonusCoin
    0,                      // bonusCoinRate
    0,                      // baseCoin
    100,                    // runRate
    9,                      // pbSoftCap
    24,                     // width
    24,                     // height
    {0, 0},                 // hitOffset
    {0.0f, 0.0f, 0.0f},     // centerOffset
    {0, 0},                 // hpGaugeOffset
    {0.0f, 0.0f, 0.0f},     // talkTogeBaseOffset
    {0.0f, 0.0f, 0.0f},     // heldItemBaseOffset
    {0.0f, 0.0f, 0.0f},     // burnFlameOffset
    0.0f,                   // vivianOffsetX
    0.0f,                   // vivianOffsetZ
    {12.0f, 0.0f, 0.0f},    // bintaHitOffset
    {12.0f, 15.6f, 0.0f},   // kissHitOffset
    {0.0f, 0.0f, 0.0f},     // cutBaseOffset
    0.0f,                   // cutWidth
    0.0f,                   // cutHeight
    0,                      // turnOrder
    0,                      // turnOrderVariance
    -1,                     // swallowChance
    0,                      // swallowAttributes
    100,                    // hammerKnockbackChance
    20,                     // itemStealParam
    {0.0f, 0.0f, 0.0f},     // starPointDispOffset
    "SFX_BTL_DAMAGE1",      // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1",  // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    UNIT_ATTR_TARGET_SORT_OFFSET | UNIT_ATTR_NO_GRAVITY_BOB | UNIT_ATTR_ACTS_IN_ZERO_GRAVITY | UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR,             // attributeFlags
    &regist,                // statusVulnerability
    1,                      // numParts
    parts,                  // parts
    init_event,             // initEventCode
    data_table,             // dataTable
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};
static StatusVulnerability regist = {0};

static PoseTableEntry pose_table[] = {
    {28, "M_S_1"},
    {31, "M_S_1"},
    {39, "M_O_1"},
    {BTL_POSE_STAY_DEFAULT, "M_S_1"},
};

static BattleUnitKindPart parts[] = {
    {
        1,                    // partNum
        "btl_un_switch",      // partName
        "b_mario",            // modelName
        {0.0f, 0.0f, 0.0f},   // positionOffset
        {0.0f, 25.0f, 0.0f},  // hitBaseOffset
        {0.0f, 30.0f, 0.0f},  // hitCursorBaseOffset
        20,                   // shadowSize
        30,                   // hitHeight
        255,                  // baseAlpha
        &defence,             // defense
        &defence_attr,        // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW,           // attributes
        0,                    // counterAttributes
        pose_table,           // poseTable
    },
};

static BattleDataEntry data_table[] = {
    {0, NULL},
};

static EvtWord attack_event[5];
static EvtWord wait_event[2];
static EvtWord damage_event[22];

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 256, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(_rumble_switch, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(evt_map_playanim, STRING("switch_a"), 0, 0)
    WAIT_MS(500)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    RETURN
EVT_END()

static s32 _data[] = {
    -5, 0, 15, 0, -15, 0, 14, 0, -13, 0, 12, 0, -11, 0, 10, 0, -9, 0,
#if VERSION <= VERSION_DEMO_US
    8, 0, -7, 0, 6, 0, -6, 0, 5, 0, -4, 0, 2, 0, -2, 0,
#else
    8, 0, -7, 0, 6, 0, -6, 0, 5, 0, -4, 0, 2, 0, -2, 0, 0,
#endif
};

static USER_FUNC(_rumble_switch) {
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
