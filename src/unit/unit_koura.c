#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_SetBaseScale);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRotateOffset);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddPartsDispOffset[];
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_AddPartsRotateOffset[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_snd_se[];

BattleUnitKind unit_koura;
static BattleDataEntry data_table[7];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[5];
PoseTableEntry pose_table_crack_lv1[5];
PoseTableEntry pose_table_crack_lv2[5];
static BattleUnitKindPart parts[2];
static s32 init_event[46];
static s32 phase_event[38];
s32 koura_open[72];
s32 koura_close[79];
s32 damage_core[92];
s32 pose_tbl_reset[58];
static s32 dead_event[243];
s32 destroy_event[47];
static s32 damage_event[10];
static s32 wait_event[6];
static s32 attack_event[2];

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
    0x10000000,
    &regist,
    2,
    parts,
    init_event,
    data_table,
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

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {28, "PKO_S_1"},
    {31, "PKO_S_1"},
    {39, "PKO_D_1"},
    {68, "PKO_Z_1"},
    {69, "PKO_S_1"},
};

PoseTableEntry pose_table_crack_lv1[] = {
    {28, "PKO_S_2"},
    {31, "PKO_S_2"},
    {39, "PKO_D_2"},
    {68, "PKO_Z_2"},
    {69, "PKO_S_2"},
};

PoseTableEntry pose_table_crack_lv2[] = {
    {28, "PKO_S_3"},
    {31, "PKO_S_3"},
    {39, "PKO_D_3"},
    {68, "PKO_Z_3"},
    {69, "PKO_S_3"},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_koura", "c_koura", 0.0f, 0.0f, 0.0f, 20.0f, 40.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x80009, 0, pose_table},
    {2, "btl_un_koura", "c_koura", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3010000, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetBaseScale, -2, FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.5f))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHp, -2, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL_CHILD(PTR(koura_open))
        END_IF
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHp, -2, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL_CHILD(PTR(koura_close))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(koura_open)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_PhaseEventStartDeclare, -2)
    CALL(btlevtcmd_SetRotateOffset, -2, -23, 0, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 16777216)
    LOOP(30)
        CALL(btlevtcmd_AddRotate, -2, 0, 0, 2)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetUnitWork, -2, 1, 1)
    CALL(btlevtcmd_OffAttribute, LW(3), 64)
    CALL(btlevtcmd_OnPartsAttribute, -2, 1, 65536)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 1)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 68)
    RETURN
EVT_END()

EVT_BEGIN(koura_close)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_PhaseEventStartDeclare, -2)
    CALL(btlevtcmd_SetRotateOffset, -2, -23, 0, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 60)
    LOOP(30)
        CALL(btlevtcmd_AddRotate, -2, 0, 0, -2)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    CALL(btlevtcmd_OnAttribute, LW(3), 64)
    CALL(btlevtcmd_OffPartsAttribute, -2, 1, 65536)
    CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, 16777216)
    CALL(btlevtcmd_StartWaitEvent, -2)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 damage_core[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999999, 196699, (s32)btlevtcmd_GetHp, -2,
    -30000000, 65570, -30000000, 65576, 3, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table_crack_lv2, 131097, -29999999, 2, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_NOKO_GUARD3", -250000000, 0, -250000000, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    3, 2, 65576, 6, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1,
    (s32)pose_table_crack_lv1, 131097, -29999999, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_GUARD3",
    -250000000, 0, -250000000, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3,
    1, 42, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 131097,
    -29999999, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_GUARD3", -250000000, 0,
    -250000000, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 49,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39, 65546, 500, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 pose_tbl_reset[] = {
    196699, (s32)btlevtcmd_GetHp, -2, -30000000, 65570, -30000000, 65576, 3,
    262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_crack_lv2, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_NOKO_GUARD3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3,
    2, 65576, 6, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_crack_lv1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_GUARD3", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 3, 1, 42, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 49,
    2, 1,
};

static s32 dead_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999997, 196699, (s32)btlevtcmd_OffAttribute, -29999997,
    96, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999997, 1, 16777216, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_NOKO_GUARD4", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PKO_H_1", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"PKO_H_2", 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 2, 16777216, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, 1,
    23, 0, 0, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, 2, -23,
    0, 0, 110, 65541, 5, 393307, (s32)btlevtcmd_AddPartsDispOffset, -2,
    1, 0, 1, 0, 393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 2,
    0, 1, 0, 65545, 2, 6, 65541, 6,
    393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 1, 0, 1, 0, 393307,
    (s32)btlevtcmd_AddPartsDispOffset, -2, 2, 0, 1, 0, 65545, 1,
    6, 65541, 2, 393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 1, 0,
    1, 0, 393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 2, 0, 1,
    0, 65545, 2, 6, 112, 110, 65541, 10,
    393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 1, -1, 0, 0, 393307,
    (s32)btlevtcmd_AddPartsDispOffset, -2, 2, 1, 0, 0, 65545, 1,
    6, 65541, 5, 393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 1, -1,
    0, 0, 393307, (s32)btlevtcmd_AddPartsDispOffset, -2, 2, 1, 0,
    0, 65545, 2, 6, 112, 110, 65541, 10,
    393307, (s32)btlevtcmd_AddPartsRotateOffset, -2, 1, 0, 1, 0, 393307,
    (s32)btlevtcmd_AddPartsRotateOffset, -2, 2, 0, 1, 0, 65545, 2,
    6, 112, 110, 65541, 14, 393307, (s32)btlevtcmd_AddPartsRotateOffset, -2,
    1, -1, 0, 0, 393307, (s32)btlevtcmd_AddPartsRotateOffset, -2, 2,
    1, 0, 0, 65545, 1, 6, 112, 65541,
    20, 393307, (s32)btlevtcmd_AddPartsRotate, -2, 1, 0, 0, 2,
    393307, (s32)btlevtcmd_AddPartsRotate, -2, 2, 0, 0, -2, 65545,
    1, 6, 65541, 8, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1,
    16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 16777216, 65545, 2,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    2, 16777216, 65545, 2, 6, 196699, (s32)btlevtcmd_KillUnit, -2,
    0, 2, 1,
};

EVT_BEGIN(destroy_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    CALL(btlevtcmd_OffAttribute, LW(3), 96)
    CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, -2, 1, 16777216)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_KillUnit, -2, 0)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

