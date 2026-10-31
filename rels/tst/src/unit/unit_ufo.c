#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"

USER_FUNC(_ufo_damage_end);
USER_FUNC(_ufo_damage_start);
USER_FUNC(_ufo_main);

BattleUnitKind unit_ufo;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[5];
static PoseTableEntry pose_table_2[4];
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[2];
static EvtWord init_event[20];
static EvtWord main_event[4];
static EvtWord damage_event[56];
static EvtWord attack_event[2];
static EvtWord wait_event[7];

BattleUnitKind unit_ufo = {
    208,
    "btl_un_ufo",
    120,
    0,
    1,
    1,
    1,
    0,
    0,
    100,
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
    0,
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
    0x100C0000,
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
    {28, "CAT_S_1"},
    {31, "CAT_S_1"},
    {39, "CAT_K_1"},
    {40, "CAT_W_1"},
    {69, "CAT_S_1"},
};

static PoseTableEntry pose_table_2[] = {
    {28, "BRT_O_1"},
    {31, "BRT_O_1"},
    {39, "BRT_O_1"},
    {69, "BRT_O_1"},
};

static BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "bll_un_ufo", "ufo", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 65.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, /*"おとしもの"*/"\x82\xA8\x82\xC6\x82\xB5\x82\xE0\x82\xCC", "coin", 0.0f, -15.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x410000, 0, pose_table_2},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    SPAWN_EVENT(PTR(main_event))
    RETURN
EVT_END()

static EVT_BEGIN(main_event)
    CALL(_ufo_main)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 39)
        SET_VALUE(LW(15), LW(14))
        CALL(_ufo_damage_start)
        CALL_CHILD(PTR(subsetevt_damage))
        SET_VALUE(LW(14), 40)
        CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(10), LW(14))
        CALL(_ufo_damage_end)
        ELSE
        SET_VALUE(LW(14), 39)
        SET_VALUE(LW(15), LW(14))
        CALL_CHILD(PTR(subsetevt_damage))
        SET_VALUE(LW(14), 40)
    END_IF
    RETURN
    OPCODE_END_SCRIPT,
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END_PAD()
