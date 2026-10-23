#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_StartWaitEvent);

__declspec(section ".data") u64 fd_npc_christine_negone_one_374;
__declspec(section ".data") s32 fd_npc_christine_neg_one_382[1];
__declspec(section ".data") s32 fd_npc_christine___local_PI_383[1];
__declspec(section ".data") s32 fd_npc_christine___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_npc_christine_one_negone_373;
__declspec(section ".data") s32 fd_npc_christine___local_PIO2_384[1];
__declspec(section ".data") s32 fd_npc_christine_one_381[1];
__declspec(section ".data") u64 fd_npc_christine_negone_one_360;
__declspec(section ".data") s32 fd_npc_christine_neg_one_365[1];
__declspec(section ".data") s32 fd_npc_christine___local_PI_366[1];
__declspec(section ".data") s32 fd_npc_christine___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_npc_christine_one_negone_359;
__declspec(section ".data") s32 fd_npc_christine___local_PIO2_367[1];
__declspec(section ".data") s32 fd_npc_christine_one_364[1];
BattleUnitKind unit_npc_christine;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[4];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static s32 init_event[25];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 phase_event[2];
static __declspec(section ".data") s32 attack_event[5];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_npc_christine_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_npc_christine_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_npc_christine___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_npc_christine___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_npc_christine_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_npc_christine___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_npc_christine_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_npc_christine_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_npc_christine_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_npc_christine___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_npc_christine___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_npc_christine_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_npc_christine___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_npc_christine_one_364[] = {
    1065353216,
};

BattleUnitKind unit_npc_christine = {
    221,
    "btl_un_christine",
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
    30.0f,
    0.0f,
    0.0f,
    30.0f,
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
    0x12000000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {28, "PKR_S_1"},
    {31, "PKR_S_1"},
    {39, "PKR_S_1"},
    {69, "PKR_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_christine", "c_pkr\0\0", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x90009, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
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

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

