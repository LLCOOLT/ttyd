#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "unit/party/unit_party_clauda.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);

__declspec(section ".data") f32 fd_act_clauda_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_act_clauda_neg_one_382;
__declspec(section ".data") f32 fd_act_clauda___local_PI_383;
__declspec(section ".data") f32 fd_act_clauda___local_3PIO2_385;
__declspec(section ".data") f32 fd_act_clauda_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_act_clauda___local_PIO2_384;
__declspec(section ".data") f32 fd_act_clauda_one_381;
__declspec(section ".data") f32 fd_act_clauda_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_act_clauda_neg_one_365;
__declspec(section ".data") f32 fd_act_clauda___local_PI_366;
__declspec(section ".data") f32 fd_act_clauda___local_3PIO2_368;
__declspec(section ".data") f32 fd_act_clauda_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_act_clauda___local_PIO2_367;
__declspec(section ".data") f32 fd_act_clauda_one_364;
BattleUnitKind unit_act_clauda;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static __declspec(section ".data") s32 init_event[9];
static __declspec(section ".data") s32 damage_event[2];
static __declspec(section ".data") s32 phase_event[2];
static __declspec(section ".data") s32 attack_event[2];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") f32 fd_act_clauda_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_act_clauda_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_act_clauda___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_act_clauda___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_act_clauda_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_act_clauda___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_act_clauda_one_381 = 1.0f;

__declspec(section ".data") f32 fd_act_clauda_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_act_clauda_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_act_clauda___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_act_clauda___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_act_clauda_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_act_clauda___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_act_clauda_one_364 = 1.0f;

BattleUnitKind unit_act_clauda = {
    182,
    "btl_un_act_clauda",
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

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_clauda", "c_windy", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table_clauda_stay},
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

