#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);

__declspec(section ".data") u64 fd_act_teresa_negone_one_374;
__declspec(section ".data") s32 fd_act_teresa_neg_one_382[1];
__declspec(section ".data") s32 fd_act_teresa___local_PI_383[1];
__declspec(section ".data") s32 fd_act_teresa___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_act_teresa_one_negone_373;
__declspec(section ".data") s32 fd_act_teresa___local_PIO2_384[1];
__declspec(section ".data") s32 fd_act_teresa_one_381[1];
__declspec(section ".data") u64 fd_act_teresa_negone_one_360;
__declspec(section ".data") s32 fd_act_teresa_neg_one_365[1];
__declspec(section ".data") s32 fd_act_teresa___local_PI_366[1];
__declspec(section ".data") s32 fd_act_teresa___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_act_teresa_one_negone_359;
__declspec(section ".data") s32 fd_act_teresa___local_PIO2_367[1];
__declspec(section ".data") s32 fd_act_teresa_one_364[1];
BattleUnitKind unit_act_teresa;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[7];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static __declspec(section ".data") s32 init_event[9];
static __declspec(section ".data") s32 damage_event[2];
static __declspec(section ".data") s32 phase_event[2];
static __declspec(section ".data") s32 attack_event[2];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_act_teresa_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_act_teresa_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_act_teresa___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_act_teresa___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_act_teresa_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_act_teresa___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_act_teresa_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_act_teresa_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_act_teresa_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_act_teresa___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_act_teresa___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_act_teresa_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_act_teresa___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_act_teresa_one_364[] = {
    1065353216,
};

BattleUnitKind unit_act_teresa = {
    183,
    "btl_un_act_teresa",
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

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {28, "S_1"},
    {31, "A_2"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_teresa", "c_teresa\0\0\0", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static __declspec(section ".data") EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

