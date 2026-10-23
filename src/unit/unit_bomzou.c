#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"

USER_FUNC(btlevtcmd_AfterReactionEntry);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff64);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_sub_random);

static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table_3[4];
static PoseTableEntry pose_table_2[4];
static PoseTableEntry pose_table_1[4];
BattleUnitKind unit_bomzou;
s32 weapon_bomzou_explosion[48];
static BattleUnitKindPart parts[1];
static s32 init_event[70];
static s32 phase_event[67];
static s32 wait_event[57];
s32 end_battle_evt[19];
static s32 explosion_event[173];
static BattleDataEntry data_table[4];
static s32 damage_event[10];
static s32 attack_event[5];
static s32 dead_event[6];

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table_3[] = {
    {28, "B_2"},
    {31, "B_2"},
    {39, "B_2"},
    {69, "B_2"},
};

static PoseTableEntry pose_table_2[] = {
    {28, "B_3"},
    {31, "B_3"},
    {39, "B_3"},
    {69, "B_3"},
};

static PoseTableEntry pose_table_1[] = {
    {28, "B_4"},
    {31, "B_4"},
    {39, "B_4"},
    {69, "B_4"},
};

BattleUnitKind unit_bomzou = {
    219,
    "btl_un_bomzou",
    1,
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
    0x12400000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

s32 weapon_bomzou_explosion[] = {
    0, 0, 0, 0, 1677721600, 0, 0, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 35651616, 536870912, 50332418, 0, 131200, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 658020, 503645445, 83886080,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_bomzou", "c_bakudan", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x80009, 0, pose_table_3},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 2)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_GREATER_OR_EQUAL(3)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_3))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_2))
        CASE_GREATER_OR_EQUAL(1)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_1))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("B_1"))
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, -2, 0, LW(0))
        SWITCH(LW(0))
            CASE_GREATER_OR_EQUAL(3)
            CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_3))
            CASE_GREATER_OR_EQUAL(2)
            CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_2))
            CASE_GREATER_OR_EQUAL(1)
            CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_1))
        END_SWITCH
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_PhaseEventStartDeclare, -2)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("B_2"))
            WAIT_FRAMES(36)
            CALL_CHILD(PTR(explosion_event))
            ELSE
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    LABEL(0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_GREATER(LW(0), 1)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(evt_eff64, 0, STRING("sweat_n64"), 1, LW(0), LW(1), LW(2), 15, -45, 15, 0, 0, 0, 0, 0)
    CALL(evt_sub_random, 45, LW(0))
    ADD(LW(0), 45)
    WAIT_FRAMES(LW(0))
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(end_battle_evt)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_snd_sfxoff, LW(0))
        CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    END_IF
    RETURN
EVT_END()

static s32 explosion_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131097, -30000000, 0,
    131163, (s32)evt_snd_sfxoff, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0,
    33, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131,
    (s32)evt_eff, (s32)"", (s32)"hibashira", 2, -30000000, -29999999, -29999998, -30000000,
    -29999999, -29999998, 1, -229998976, 60, 0, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_THUNDERS_BOMB2\0", -250000000, 0, -250000000, 65627, (s32)btlevtcmd_StageDispellFog,
    196699, (s32)btlevtcmd_OnAttribute, -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1,
    50331648, 393307, (s32)evt_btl_camera_shake_h, 0, 10, 0, 60, 4,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"B_2", 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    1, (s32)weapon_bomzou_explosion, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_bomzou_explosion, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131122, -29999990, 0,
    65539, 10, 196699, (s32)btlevtcmd_GetUnitId, -2, -30000000, 131096, -30000000,
    -29999997, 65540, 80, 33, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -250000000, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999999, -250000000,
    -250000000, 131126, -30000000, -29999999, 131100, -30000000, -1, 131127,
    -30000000, -1, 33, 131099, -30000000, 50, 65540, 80,
    33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_bomzou_explosion, 256,
    -29999995, 131096, -29999995, 1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_bomzou_explosion, 256, -29999995, 33, 65539, 80, 196699,
    (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990,
    1, 65540, 10, 33, 65539, 99, 196699, (s32)btlevtcmd_KillUnit,
    -2, 0, 2, 1, 0,
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {53, explosion_event},
    {63, end_battle_evt},
    {0, NULL},
};

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_AfterReactionEntry, -2, 53)
    RETURN
EVT_END()

