// Battle unit for a Toad (キノピオ) acting in Flurrie's stage play in the epilogue (nok.rel); it only plays its
// scripted part.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_cmd.h"
#include "version.h"

BattleUnitKind unit_act_kinopio;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[7];
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[9];
static EvtWord wait_event[6];

BattleUnitKind unit_act_kinopio = {
    185,
    "btl_un_act_kinopio",
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

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {28, "KNP_S_1"},
    {31, "KNP_S_1"},
    {39, "KNP_D_1"},
    {42, "KNP_R_1"},
    {40, "KNP_W_1"},
    {BTL_POSE_TALK, "KNP_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KNP_S_1"},
};

static BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_teresa", "c_kinopio", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

/**
 * Init event of the Toad stage actor: installs only its wait event and starts it;
 * this unit never attacks or takes damage.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Toad stage actor: does nothing. */
static EVT_BEGIN(damage_event)
    RETURN
EVT_END()

/** Phase event of the Toad stage actor: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Attack event of the Toad stage actor: does nothing. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

/** Idle event of the Toad stage actor: shows the unit's table pose for state 1. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
