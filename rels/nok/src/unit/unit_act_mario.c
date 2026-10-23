#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "unit/party/unit_party_christine.h"

EffectEntry* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 scale);

static USER_FUNC(_clauda_breath_effect_fire);
static USER_FUNC(_clauda_breath_effect_ready);
USER_FUNC(_status_window_off);
USER_FUNC(btlevtcmd_AddPartsRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_DivePosition);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpSetting);
USER_FUNC(btlevtcmd_SetAlpha);
USER_FUNC(btlevtcmd_SetDispOffset);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetPartsRotate);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(evt_audience_joy_ending);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff_delete_ptr);
USER_FUNC(evt_sub_random);
extern s32 unit_act_atmic_teresa[];
extern s32 unit_act_clauda[];
extern s32 unit_act_kinopiko[];
extern s32 unit_act_kinopio[];
extern s32 unit_act_teresa[];

__declspec(section ".data") u64 fd_act_mario_negone_one_374;
__declspec(section ".data") s32 fd_act_mario_neg_one_382[1];
__declspec(section ".data") s32 fd_act_mario___local_PI_383[1];
__declspec(section ".data") s32 fd_act_mario___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_act_mario_one_negone_373;
__declspec(section ".data") s32 fd_act_mario___local_PIO2_384[1];
__declspec(section ".data") s32 fd_act_mario_one_381[1];
__declspec(section ".data") u64 fd_act_mario_negone_one_360;
__declspec(section ".data") s32 fd_act_mario_neg_one_365[1];
__declspec(section ".data") s32 fd_act_mario___local_PI_366[1];
__declspec(section ".data") s32 fd_act_mario___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_act_mario_one_negone_359;
__declspec(section ".data") s32 fd_act_mario___local_PIO2_367[1];
__declspec(section ".data") s32 fd_act_mario_one_364[1];
BattleUnitKind unit_act_mario;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[7];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static s32 init_event[15];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 phase_event[2];
static __declspec(section ".data") s32 attack_event[5];
static __declspec(section ".data") s32 wait_event[6];
s32 entry_unit_data[96];
static s32 battle_entry_event[168];
s32 _battle_event[155];
s32 _act_target_enemy[33];
s32 _act_target_mario[26];
s32 _act_mario_jump_attack[240];
s32 _act_clauda_press_attack[350];
s32 _act_clauda_breath_attack[269];
s32 _act_teresa_attack[190];
s32 _act_atmic_teresa_press_attack[188];

__declspec(section ".data") u64 fd_act_mario_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_act_mario_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_act_mario___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_act_mario___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_act_mario_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_act_mario___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_act_mario_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_act_mario_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_act_mario_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_act_mario___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_act_mario___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_act_mario_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_act_mario___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_act_mario_one_364[] = {
    1065353216,
};

BattleUnitKind unit_act_mario = {
    181,
    "btl_un_act_mario",
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
    {28, "EM_S_1"},
    {31, "KNP_S_1"},
    {39, "EM_D_1"},
    {42, "EM_R_1"},
    {40, "EM_W_1"},
    {65, "EM_T_1"},
    {69, "EM_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_act_mario", "c_mario", 0.0f, 0.0f, 0.0f, -5.0f, 30.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(_status_window_off)
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

s32 entry_unit_data[] = {
    (s32)unit_act_clauda, 0, 67108868, -1022623744, 0, 1084227584, 0, 0,
    0, 0, 0, 0, (s32)unit_act_teresa, 16777216, 67108868, 1110704128,
    1109393408, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_act_teresa, 16777216, 67108868, 1118437376, 1109393408, 0, 0, 0,
    0, 0, 0, 0, (s32)unit_act_atmic_teresa, 16777216, 67108868, 1125515264,
    1109393408, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_act_kinopio, 33554432, 67108868, -1030356992, 0, -1038090240, 0, 0,
    0, 0, 0, 0, (s32)unit_act_kinopio, 33554432, 67108868, -1049624576,
    0, -1038090240, 0, 0, 0, 0, 0, 0,
    (s32)unit_act_kinopiko, 33554432, 67108868, -1036779520, 0, -1038090240, 0, 0,
    0, 0, 0, 0, (s32)unitdata_Party_Christine, 33554432, 67108868, 0,
    -1035468800, 1121714176, 0, 0, 0, 0, 0, 0,
};

static s32 battle_entry_event[] = {
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 327771, (s32)btlevtcmd_GetHomePos, -3, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    1, 262235, (s32)btlevtcmd_GetStageSize, -29999994, -250000000, -250000000, 131127, -29999994,
    -1, 327771, (s32)btlevtcmd_GetHomePos, -3, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetPos, -3, -29999994, -29999999, -29999998, 196699, (s32)btlevtcmd_GetUnitId, -2,
    -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, -30000000, 262235, (s32)btlevtcmd_SpawnUnit,
    -29999997, (s32)entry_unit_data, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, -29999997,
    262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)(void*)((u8*)entry_unit_data + 0x30), 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    2, -29999997, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)(void*)((u8*)entry_unit_data + 0x60), 0, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 3, -29999997, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)(void*)((u8*)entry_unit_data + 0x90),
    0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, -29999997, 262235, (s32)btlevtcmd_SpawnUnit,
    -29999997, (s32)(void*)((u8*)entry_unit_data + 0xC0), 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -29999997,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -29999997, 1, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)(void*)((u8*)entry_unit_data + 0xF0),
    0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 6, -29999997, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -29999997, 1, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)(void*)((u8*)entry_unit_data + 0x120), 0, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 7, -29999997, 196699, (s32)btlevtcmd_ChangeFaceDirection, -29999997, 1,
    262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)(void*)((u8*)entry_unit_data + 0x150), 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    8, -29999997, 196699, (s32)btlevtcmd_ChangeFaceDirection, -29999997, 1, 65628, (s32)_battle_event,
    65546, 2000, 327771, (s32)evt_msg_print, 2, (s32)"ep_39", 0, -2,
    65546, 1000, 196699, (s32)btlevtcmd_onoff_battleflag, 1, 32, 2, 1,
};

EVT_BEGIN(_battle_event)
    LABEL(0)
    CALL_CHILD(PTR(_act_mario_jump_attack))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(evt_sub_random, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(_act_clauda_press_attack))
        ELSE
        CALL_CHILD(PTR(_act_clauda_breath_attack))
    END_IF
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A_7"))
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 65)
    WAIT_MS(1000)
    CALL_CHILD(PTR(_act_teresa_attack))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    CALL(btlevtcmd_GetUnitWork, -2, 3, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 65)
    WAIT_MS(1000)
    CALL_CHILD(PTR(_act_teresa_attack))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 65)
    WAIT_MS(1000)
    CALL_CHILD(PTR(_act_atmic_teresa_press_attack))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 65)
    WAIT_MS(1500)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    CALL(btlevtcmd_GetUnitWork, -2, 7, LW(5))
    CALL(btlevtcmd_GetBodyId, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 65)
    WAIT_MS(1500)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(_act_target_enemy)
    CALL(evt_sub_random, 2, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetUnitWork, -2, 2, LW(3))
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetUnitWork, -2, 3, LW(3))
        CASE_DEFAULT
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(3))
    END_SWITCH
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    RETURN
EVT_END()

EVT_BEGIN(_act_target_mario)
    CALL(evt_sub_random, 1, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
        CASE_DEFAULT
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(3))
    END_SWITCH
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    RETURN
EVT_END()

s32 _act_mario_jump_attack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 65, 65546, 1000, 65630, (s32)_act_target_enemy, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    131122, -30000000, -20, 131122, -29999999, 0, 131122, -29999998,
    0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999994, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 131122, -29999994, 36, 393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000,
    -29999999, -29999998, -29999994, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999,
    -29999998, -29999994, 3, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"EM_J_1D", 65546, 50, 65647, -29999985, 131163, (s32)btlevtcmd_StopWaitEvent, -29999997,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 983131, (s32)evt_eff, 0, (s32)"hit", 0, -30000000,
    -29999999, -29999998, -229998976, 3, 0, 0, 0, 0,
    0, 0, 65627, (s32)evt_audience_joy_ending, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996,
    39, 65546, 1000, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 112, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20,
    -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_R_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 196699,
    (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 2, 1,
};

s32 _act_clauda_press_attack[] = {
    262235, (s32)btlevtcmd_AnimeChangePoseType, -29999995, -29999994, 65, 65546, 1000, 65630,
    (s32)_act_target_enemy, 458843, (s32)btlevtcmd_CalculateFaceDirection, -29999995, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -29999995, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -29999995,
    -29999994, (s32)"PWD_A1_1", 196699, (s32)btlevtcmd_SetFallAccel, -29999995, -229999796, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998, 5,
    458843, (s32)btlevtcmd_JumpPosition, -29999995, -30000000, -29999999, -29999998, 60, -1,
    65647, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996, 39, 327771,
    (s32)evt_sub_intpl_init_float, 5, -229998976, -229999847, 10, 65541, 11, 196699,
    (s32)evt_sub_intpl_get_float, -29999993, -250000000, 327771, (s32)btlevtcmd_GetScale, -29999997, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -29999997, -30000000, -29999993, -29999998, 65545,
    1, 6, 65546, 1500, 327771, (s32)evt_sub_intpl_init_float, 5, -229999847,
    -229998720, 10, 65541, 11, 196699, (s32)evt_sub_intpl_get_float, -29999993, -250000000,
    327771, (s32)btlevtcmd_GetScale, -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -29999997, -30000000, -29999993, -29999998, 65545, 1, 6, 327771,
    (s32)evt_sub_intpl_init_float, 7, -229998720, -229998976, 30, 65541, 31, 196699,
    (s32)evt_sub_intpl_get_float, -29999993, -250000000, 327771, (s32)btlevtcmd_GetScale, -29999997, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -29999997, -30000000, -29999993, -29999998, 65545,
    1, 6, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996,
    28, 112, 131163, (s32)btlevtcmd_JumpContinue, -29999995, 65647, -29999986, 327771,
    (s32)evt_sub_intpl_init_float, 11, -229998976, -229999591, 10, 65541, 10, 196699,
    (s32)evt_sub_intpl_get_float, -29999993, -250000000, 327771, (s32)btlevtcmd_GetScale, -29999995, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -29999995, -30000000, -29999993, -29999998, 65545,
    1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229999591, -229998976, 6,
    65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999993, -250000000, 327771, (s32)btlevtcmd_GetScale,
    -29999995, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -29999995, -30000000,
    -29999993, -29999998, 65545, 1, 6, 112, 110, 327771,
    (s32)evt_sub_intpl_init_float, 11, -229998976, -229998464, 10, 65541, 10, 196699,
    (s32)evt_sub_intpl_get_float, -29999993, -250000000, 327771, (s32)btlevtcmd_GetScale, -29999995, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -29999995, -29999993, -29999999, -29999998, 65545,
    1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464, -229998976, 6,
    65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999993, -250000000, 327771, (s32)btlevtcmd_GetScale,
    -29999995, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -29999995, -29999993,
    -29999999, -29999998, 65545, 1, 6, 112, 327771, (s32)btlevtcmd_GetPos,
    -29999995, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999995, -30000000,
    20, 131125, -29999999, 20, 327771, (s32)btlevtcmd_SetRotate, -29999995, 0,
    0, 0, 196699, (s32)btlevtcmd_SetFallAccel, -29999995, -229999693, 458843, (s32)btlevtcmd_JumpPosition,
    -29999995, -30000000, -29999999, -29999998, 18, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999995, -29999994, (s32)"PWD_Y_1", 65627, (s32)evt_audience_joy_ending, 65546, 500, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999986, 196699, (s32)btlevtcmd_SetMoveSpeed, -29999995, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -29999995, -29999994, 40, 327771, (s32)btlevtcmd_GetHomePos, -29999995, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -29999995, -30000000, -29999999, -29999998, -229993856,
    -29999991, 655451, (s32)btlevtcmd_DivePosition, -29999995, -30000000, -29999999, -29999998, -29999991,
    0, 4, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999995, -29999994,
    28, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 2, 1,
};

EVT_BEGIN(_act_clauda_breath_attack)
    CALL(btlevtcmd_JumpSetting, LW(5), 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 65)
    WAIT_MS(1000)
    CALL(_clauda_breath_effect_ready)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A2_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A2_2"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, LW(5), LW(6))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_A2_3"))
    CALL(_clauda_breath_effect_fire, LW(12))
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 39)
        LOOP(30)
            CALL(btlevtcmd_SetDispOffset, LW(3), 2, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 28)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, -2, 3, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 39)
        LOOP(30)
            CALL(btlevtcmd_SetDispOffset, LW(3), 2, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 28)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 39)
        LOOP(30)
            CALL(btlevtcmd_SetDispOffset, LW(3), 2, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 28)
    END_SIBLING_EVENT
    WAIT_FRAMES(120)
    CALL(evt_eff_delete_ptr, LW(12))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("PWD_Y_1"))
    CALL(evt_audience_joy_ending)
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 28)
    RETURN
EVT_END()

EVT_BEGIN(_act_teresa_attack)
    CALL_CHILD(PTR(_act_target_mario))
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 42)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetAlpha, LW(5), LW(6), 255)
        SET_VALUE(LW(7), 256)
        LOOP(16)
            WAIT_FRAMES(1)
            SUBTRACT(LW(7), 16)
            CALL(btlevtcmd_SetAlpha, LW(5), LW(6), LW(7))
        END_LOOP
        WAIT_FRAMES(20)
        CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("A_1"))
        CALL(btlevtcmd_SetAlpha, LW(5), LW(6), 0)
        SET_VALUE(LW(7), -1)
        LOOP(8)
            WAIT_FRAMES(1)
            ADD(LW(7), 32)
            CALL(btlevtcmd_SetAlpha, LW(5), LW(6), LW(7))
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(5), LW(0), 20)
    SUBTRACT(LW(1), 10)
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), 60, -5, 4, 0, -1)
    CALL(btlevtcmd_SetAlpha, LW(5), LW(6), 255)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("A_2"))
    WAIT_MS(250)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 39)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, LW(5), LW(6), 42)
    CALL(btlevtcmd_AddPartsRotate, LW(5), LW(6), 0, 180, 0)
    CALL(btlevtcmd_GetHomePos, LW(5), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), 40, 0, 4, 0, -1)
    CALL(btlevtcmd_SetPartsRotate, LW(5), LW(6), 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 28)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    RETURN
EVT_END()

EVT_BEGIN(_act_atmic_teresa_press_attack)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("R_1"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(2), 10)
    CALL(btlevtcmd_DivePosition, LW(5), -125, 100, LW(2), 120, 10, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("Z_1"))
    CALL(btlevtcmd_DivePosition, LW(5), -125, 0, LW(2), 30, 0, 1, 0, -1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
        CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 39)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(3))
        CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
        CALL(btlevtcmd_StopWaitEvent, LW(3))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
        CALL(evt_audience_joy_ending)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(4), 39)
        WAIT_MS(1000)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
    END_SIBLING_EVENT
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("W_1"))
    CALL(btlevtcmd_GetHomePos, LW(5), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, LW(5), LW(0), LW(1), LW(2), 60, 50, 6, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(5), LW(6), STRING("S_1"))
    RETURN
EVT_END()

static USER_FUNC(_clauda_breath_effect_fire) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    BattleUnit* unit;
    s32 var;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    var = args[0];
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->mSizeMultiplier * (unit->faceDirection * 25);
    pos.y += 15.0f * unit->mSizeMultiplier;
    eff = effKumokumoN64Entry(0, 0, pos.x, pos.y, pos.z, 0.0f, -2.0f, 1.0f);
    ((s32*)eff->userdata)[6] = 76;
    ((s32*)eff->userdata)[7] = 167;
    ((s32*)eff->userdata)[8] = 202;
    ((s32*)eff->userdata)[10] = 125;
    ((s32*)eff->userdata)[11] = 27;
    ((s32*)eff->userdata)[12] = 245;
    ((f32*)eff->userdata)[22] = -10.0f;
    evtSetValue(event, var, (s32)eff);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_clauda_breath_effect_ready) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->mSizeMultiplier * (unit->faceDirection * 20);
    pos.y += 25.0f * unit->mSizeMultiplier;
    eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 0.0f, 2.0f, 1.0f);
    ((s32*)eff->userdata)[6] = 76;
    ((s32*)eff->userdata)[7] = 167;
    ((s32*)eff->userdata)[8] = 202;
    ((s32*)eff->userdata)[10] = 125;
    ((s32*)eff->userdata)[11] = 27;
    ((s32*)eff->userdata)[12] = 245;
    return EVT_RETURN_DONE;
}

USER_FUNC(_status_window_off) {
    _battleWorkPointer->statusWindowOff = 1;
    return EVT_RETURN_DONE;
}

