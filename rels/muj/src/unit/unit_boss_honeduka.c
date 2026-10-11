#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_StartWaitEvent);
extern s32 btldefaultevt_Damage[];

__declspec(section ".data") u64 fd_boss_honeduka_negone_one_374;
__declspec(section ".data") s32 fd_boss_honeduka_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_honeduka___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_honeduka___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_honeduka_one_negone_373;
__declspec(section ".data") s32 fd_boss_honeduka___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_honeduka_one_381[1];
__declspec(section ".data") u64 fd_boss_honeduka_negone_one_360;
__declspec(section ".data") s32 fd_boss_honeduka_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_honeduka___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_honeduka___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_honeduka_one_negone_359;
__declspec(section ".data") s32 fd_boss_honeduka___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_honeduka_one_364[1];
BattleUnitKind unit_boss_honeduka;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[4];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 init_event[21];
static __declspec(section ".data") s32 damage_event[10];
s32 honeduka_damage_sub_event[14];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boss_honeduka_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_honeduka_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_honeduka___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_honeduka___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_honeduka_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_honeduka___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_honeduka_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_honeduka_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_honeduka_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_honeduka___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_honeduka___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_honeduka_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_honeduka___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_honeduka_one_364[] = {
    1065353216,
};

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
    0x52200000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 80, 0, 100, 0, 100, 100, 50, 0, 0, 100, 0, 100, 40, 50, 0, 0, 100, 50, 0, 0, 0};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {69, "KRT_Z_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {9, honeduka_damage_sub_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_honeduka", "c_honezuka", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2090009, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

EVT_BEGIN(honeduka_damage_sub_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    CALL(btlevtcmd_RunDataEventChild, LW(3), 71)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

