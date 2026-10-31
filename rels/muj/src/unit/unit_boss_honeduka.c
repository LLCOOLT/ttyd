// Keelhaul Key (muj) battle unit: the Bone Pile (honeduka) of the Cortez fight: its parts, defence/status tables, and
// events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"

// Unit work slots of the Bone Pile (btlevtcmd_GetUnitWork).
enum {
    UW_BOSS_HONEDUKA_OWNER_ID = 0, // unit id of Cortez, whose bone-pile damage event it runs
};

BattleUnitKind unit_boss_honeduka;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[4];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static EvtWord init_event[21];
static EvtWord damage_event[10];
extern EvtWord honeduka_damage_sub_event[];
static EvtWord wait_event[6];

/**
 * Unit data of the Bone Pile: 100 HP, 100x100 units in size; ties together its sounds, parts,
 * status vulnerability, init event and event table.
 */
BattleUnitKind unit_boss_honeduka = {
    94,
    "btl_un_honeduka",
    100,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    9,
    100,
    100,
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
    50.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    32.0f,
    0.0f,
    0.0f,
    50.0f,
    65.0f,
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
    "SFX_BOSS_KOR_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_KNOCKBACK_POSE | UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR | UNIT_ATTR_HP_LOCKED,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Bone Pile: 0 against every kind of hit. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of the Bone Pile: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of the Bone Pile (percent chance each status takes hold): immune to sleep, dizzy,
 * confusion, Huge, Tiny, Attack Down, fright, Gale Force, Dodgy, Invisible, instant KO;
 * resists freeze (50%), Defense Down (40%), allergic (50%), Slow (50%); the rest take hold at 80%
 * or better.
 */
static StatusVulnerability regist = {0, 80, 0, 100, 0, 100, 100, 50, 0, 0, 100, 0, 100, 40, 50, 0, 0, 100, 50, 0, 0, 0};

/** Pose table of the Bone Pile: maps its battle poses to its animations (KRT_*). */
static PoseTableEntry pose_table[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_Z_1"},
};

/** Event table of the Bone Pile: honeduka_damage_sub_event (tag 9). */
static BattleDataEntry data_table[] = {
    {9, honeduka_damage_sub_event},
    {0, NULL},
};

/** Parts of the Bone Pile: 1 part (model c_honezuka). */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_honeduka", "c_honezuka", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NOT_TARGETABLE | PART_ATTR_UNTATTLEABLE | PART_ATTR_NO_SHADOW, 0, pose_table},
};

/**
 * Init event of the standalone Bone Pile unit: sets unit flag 0x1000000 (no mirror flip),
 * installs its wait and damage events and gives it no actions per turn.
 * Nothing in the tree spawns this unit (Cortez's bone pile is his own part 4);
 * its owner would be in unit work 0.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage event of the Bone Pile: runs the default damage reaction,
 * which calls its data tag 9 (honeduka_damage_sub_event) to pass the hit on to Cortez.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Damage sub-event of the Bone Pile (honeduka):
 * after it is hit it runs its owner's (unit work 0, Cortez) bone-pile damage event,
 * mode2_honeduka_damage_event (data tag 70 on the US demo and earlier, 71 later;
 * the tag number differs by version), then returns to waiting.
 */
EVT_BEGIN(honeduka_damage_sub_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_HONEDUKA_OWNER_ID, LW(3))
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_RunDataEventChild, LW(3), 70)
#else
    CALL(btlevtcmd_RunDataEventChild, LW(3), 71)
#endif
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of the Bone Pile: sets the idle pose (KRT_Z_1) from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
