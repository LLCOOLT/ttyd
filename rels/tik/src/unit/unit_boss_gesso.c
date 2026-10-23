#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "battle/battle_pad.h"
#include "system.h"

EffectEntry* effOpukuJetwN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);

USER_FUNC(_test_rtn);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetHpGaugeOffset);
USER_FUNC(btlevtcmd_SetPartsDefenceAttrTable);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRegistStatus);
USER_FUNC(btlevtcmd_SetStatusIconOffset);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(_ikasumi_effect);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PhaseEventStartDeclare[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_SpawnUnit[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StatusWindowOnOff[];
extern s32 btlevtcmd_StopWaitEvent[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_eff_fukidashi[];
extern s32 evt_msg_print[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_snd_sfxon_3d[];
extern s32 unit_boss_gesso_left_arm[];
extern s32 unit_boss_gesso_right_arm[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_gesso_negone_one_374;
__declspec(section ".data") s32 fd_boss_gesso_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_gesso___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_gesso___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_gesso_one_negone_373;
__declspec(section ".data") s32 fd_boss_gesso___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_gesso_one_381[1];
__declspec(section ".data") u64 fd_boss_gesso_negone_one_360;
__declspec(section ".data") s32 fd_boss_gesso_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_gesso___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_gesso___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_gesso_one_negone_359;
__declspec(section ".data") s32 fd_boss_gesso___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_gesso_one_364[1];
BattleUnitKind unit_boss_gesso;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
__declspec(section ".data") s32 defence_ceil[2];
__declspec(section ".data") s32 defence_attr_ceil[2];
__declspec(section ".data") s32 regist_ceil[6];
__declspec(section ".data") s32 R_defence_turn[2];
__declspec(section ".data") s32 R_defence_attr_turn[2];
__declspec(section ".data") s32 R_regist_turn[6];
static PoseTableEntry pose_table[11];
static PoseTableEntry pose_table_ceil[12];
s32 gesso_pose_table_turn[20];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
__declspec(section ".data") s32 gesso_arm_wait_event[4];
static s32 battle_entry_event[315];
static s32 init_event[121];
__declspec(section ".data") s32 entry_gesso_left_arm_entry_data[12];
__declspec(section ".data") s32 entry_gesso_right_arm_entry_data[12];
static s32 damage_event[34];
static s32 phase_event[488];
static s32 attack_event[48];
s32 weapon_gesso_ikasumi_attack[48];
s32 gesso_ikasumi_attack[193];
static __declspec(section ".data") s32 wait_event[6];
s32 dead_subevent[48];

__declspec(section ".data") u64 fd_boss_gesso_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_gesso_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_gesso___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_gesso___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_gesso_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_gesso___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_gesso_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_gesso_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_gesso_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_gesso___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_gesso___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_gesso_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_gesso___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_gesso_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_gesso = {
    8,
    "btl_un_gesso",
    12,
    0,
    1,
    1,
    41,
    0,
    0,
    100,
    0,
    50,
    9,
    120,
    120,
    46,
    -75,
    0.0f,
    0.0f,
    0.0f,
    5,
    -175,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    60.0f,
    0.0f,
    0.0f,
    60.0f,
    78.0f,
    0.0f,
    0.0f,
    120.0f,
    0.0f,
    120.0f,
    110.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GESSO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 100, 100, 0, 0, 0};

__declspec(section ".data") s32 defence_ceil[] = {
    33686018, 33554432,
};

__declspec(section ".data") s32 defence_attr_ceil[] = {
    0, 0,
};

__declspec(section ".data") s32 regist_ceil[] = {
    0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 R_defence_turn[] = {
    0, 0,
};

__declspec(section ".data") s32 R_defence_attr_turn[] = {
    0, 0,
};

__declspec(section ".data") s32 R_regist_turn[] = {
    1684300900, 1684300900, 1684300900, 1684300800, 6579200, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "GSO_N2_1"},
    {2, "GSO_D2_2"},
    {9, "GSO_D2_2"},
    {5, "GSO_K2_1"},
    {4, "GSO_X2_1"},
    {3, "GSO_K2_1"},
    {28, "GSO_S2_1"},
    {29, "GSO_Q2_1"},
    {31, "GSO_S2_1"},
    {39, "GSO_D2_1"},
    {69, "GSO_S2_1"},
};

static PoseTableEntry pose_table_ceil[] = {
    {1, "GSO_N1_1"},
    {2, "GSO_D1_3"},
    {9, "GSO_D1_3"},
    {5, "GSO_K1_1"},
    {4, "GSO_X1_1"},
    {3, "GSO_K1_1"},
    {28, "GSO_S1_1"},
    {29, "GSO_Q1_2"},
    {31, "GSO_S1_1"},
    {39, "GSO_D1_2"},
    {65, "GSO_K1_1"},
    {69, "GSO_S1_1"},
};

s32 gesso_pose_table_turn[] = {
    1, (s32)"GSO_N3_1", 2, (s32)"GSO_D3_2", 9, (s32)"GSO_D3_2", 5, (s32)"GSO_K3_1",
    4, (s32)"GSO_K3_1", 3, (s32)"GSO_K3_1", 28, (s32)"GSO_V_1", 31, (s32)"GSO_D3_1",
    39, (s32)"GSO_D3_1", 69, (s32)"GSO_V_1",
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {50, dead_subevent},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gesso", "c_gesso", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 103, -175, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

__declspec(section ".data") EVT_BEGIN(gesso_arm_wait_event)
    CALL(_test_rtn)
    RETURN
EVT_END()

static s32 battle_entry_event[] = {
    196699, (s32)btlevtcmd_OnAttribute, -2, 16777216, 65546, 1000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_GESSO_APPEAR1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"GSO_F_4", 196699, (s32)btlevtcmd_OffAttribute, -2, 16777216, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 196699, (s32)btlevtcmd_SetTalkPose, -2,
    (s32)"GSO_X1_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"GSO_X1_2", 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 655451, (s32)evt_btl_camera_set_moveto, 0, 84, 177, 558, 84,
    140, 10, 30, 11, 65545, 30, 327771, (s32)evt_msg_print,
    2, (s32)"tik_02_gs_01", 0, -2, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_CONDITION_FIND1", 95,
    65, 0, 0, 786523, (s32)evt_eff_fukidashi, 2, (s32)"", 0,
    0, 0, 95, 65, 0, 0, 135, 60,
    65545, 60, 327771, (s32)evt_msg_print, 2, (s32)"tik_02_gs_02", 0, -2,
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 3,
    655451, (s32)evt_btl_camera_set_moveto, 0, 63, 143, 646, 63, 100,
    0, 30, 11, 65545, 30, 196699, (s32)btlevtcmd_GetUnitId, -2,
    -29999990, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_gesso_left_arm_entry_data, 0, 131163, (s32)btlevtcmd_StopWaitEvent,
    -29999997, 196699, (s32)btlevtcmd_OnAttribute, -29999997, 16777216, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -29999990, 327771,
    (s32)btlevtcmd_SetPos, -29999997, 320, 6, 53, 327771, (s32)btlevtcmd_SetHomePos, -29999997,
    320, 6, 53, 65644, -29999986, 65545, 35, 393307,
    (s32)btlevtcmd_snd_se, -29999997, (s32)"SFX_BOSS_GESSO_ARM_APPEAR1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999997, 1, (s32)"GSO_F2_1", 196699, (s32)btlevtcmd_OffAttribute, -29999997, 16777216, 196699,
    (s32)btlevtcmd_AnimeWaitPlayComplete, -29999997, 1, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 109, 262235,
    (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_gesso_right_arm_entry_data, 0, 131163, (s32)btlevtcmd_StopWaitEvent, -29999997, 196699,
    (s32)btlevtcmd_OnAttribute, -29999997, 16777216, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -29999997,
    262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -29999990, 327771, (s32)btlevtcmd_SetPos, -29999997,
    59, 166, -18, 327771, (s32)btlevtcmd_SetHomePos, -29999997, 59, 166,
    -18, 65644, -29999985, 65545, 5, 393307, (s32)btlevtcmd_snd_se, -29999997,
    (s32)"SFX_BOSS_GESSO_ARM_APPEAR1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, 1,
    (s32)"GSO_F2_1", 196699, (s32)btlevtcmd_OffAttribute, -29999997, 16777216, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999997,
    1, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 109, 65628, (s32)gesso_arm_wait_event, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999986, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 655451, (s32)evt_btl_camera_set_moveto, 0, 84, 177, 558, 84,
    140, 10, 30, 11, 65545, 30, 327771, (s32)evt_msg_print,
    2, (s32)"tik_02_gs_03", 0, -2, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1,
    196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto, 0, -117,
    62, 284, -115, 43, 0, 30, 11, 65546,
    500, 196699, (s32)btlevtcmd_SetTalkPose, -4, (s32)"PKR_T_1", 196699, (s32)btlevtcmd_SetStayPose, -4,
    (s32)"PKR_S_1", 327771, (s32)evt_msg_print, 2, (s32)"tik_02_gs_03_01", 0, -4, 131163,
    (s32)btlevtcmd_StartWaitEvent, -4, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 220)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OnAttribute, -2, 2)
    CALL(btlevtcmd_OnPartsAttribute, -2, 1, 6291456)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_ceil))
    CALL(btlevtcmd_SetHpGaugeOffset, -2, 5, -175)
    CALL(btlevtcmd_SetStatusIconOffset, -2, 46, -75)
    CALL(btlevtcmd_SetHitOffset, -2, 1, 9, -122, 30)
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 9, -122, 30)
    CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(defence_ceil))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, -2, 1, PTR(defence_attr_ceil))
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_ceil))
    CALL(btlevtcmd_SetStatusIconOffset, -2, 46, -75)
    CALL(btlevtcmd_OnAttribute, -2, 16777216)
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

__declspec(section ".data") s32 entry_gesso_left_arm_entry_data[] = {
    (s32)unit_boss_gesso_left_arm, 16777216, 67108868, 0, -998637568, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_gesso_right_arm_entry_data[] = {
    (s32)unit_boss_gesso_right_arm, 16777216, 67108868, 0, -998637568, 0, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetUnitWork, -2, 4, 1)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, -2, 4, 3)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    RETURN
EVT_END()

static s32 phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131097, -30000000, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 1, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 131125, -30000000, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 3, -30000000, 131101, -30000000, 2, 131163,
    (s32)btlevtcmd_PhaseEventStartDeclare, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GSO_U_1", 196699,
    (s32)btlevtcmd_ftof, 75, -30000000, 65545, -30000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_GESSO_WAKE1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ftof, 45, -30000000,
    65545, -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_WAKE2", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table, 262235, (s32)btlevtcmd_SetHpGaugeOffset, -2, 0, 0, 262235,
    (s32)btlevtcmd_SetStatusIconOffset, -2, 46, 118, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -2, 1,
    (s32)&defence, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -2, 1, (s32)&defence_attr, 196699, (s32)btlevtcmd_SetRegistStatus,
    -2, (s32)&regist, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 55, 113, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 0, 2, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3,
    0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 33, 33,
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108869, 131097, -30000000, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 2, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 131125, -30000000, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 3, -30000000, 131101, -30000000, 2, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 131163, (s32)btlevtcmd_PhaseEventStartDeclare, -2, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 196699, (s32)btlevtcmd_OnAttribute, -2, 2,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 6291456, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table_ceil, 262235, (s32)btlevtcmd_SetHpGaugeOffset, -2, 5, -175, 262235,
    (s32)btlevtcmd_SetStatusIconOffset, -2, 46, -75, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1,
    393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 9, -122, 30, 393307,
    (s32)btlevtcmd_SetHitCursorOffset, -2, 1, 9, -122, 30, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -2, 1, (s32)defence_ceil, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -2, 1, (s32)defence_attr_ceil,
    196699, (s32)btlevtcmd_SetRegistStatus, -2, (s32)regist_ceil, 262235, (s32)btlevtcmd_SetStatusIconOffset, -2, 46,
    -75, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GSO_J_1", 65545, 48,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GSO_J_2", 131122, -29999995, 0,
    65541, 4, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    65570, -29999995, 65572, 0, 131125, -29999999, 50, 65572,
    1, 131125, -29999999, 75, 42, 131125, -29999999, 100,
    49, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_UP1", -250000000, 0, -250000000,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30, 0,
    5, 0, -1, 131125, -29999995, 1, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131126, -29999999, 30, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 16, 0, 11,
    0, -1, 6, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131122, -29999999, 220, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_APPEAR1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"GSO_F_4", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    65546, 333, 196699, (s32)btlevtcmd_GetUnitId, -2, -29999990, 262235, (s32)btlevtcmd_SpawnUnit,
    -29999997, (s32)entry_gesso_left_arm_entry_data, 0, 131163, (s32)btlevtcmd_StopWaitEvent, -29999997, 196699, (s32)btlevtcmd_OnAttribute,
    -29999997, 16777216, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, -29999997, 262235,
    (s32)btlevtcmd_SetUnitWork, -29999997, 0, -29999990, 327771, (s32)btlevtcmd_SetPos, -29999997, 320,
    6, 53, 327771, (s32)btlevtcmd_SetHomePos, -29999997, 320, 6, 53,
    65644, -29999986, 65545, 35, 393307, (s32)btlevtcmd_snd_se, -29999997, (s32)"SFX_BOSS_GESSO_ARM_APPEAR1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, 1, (s32)"GSO_F2_1",
    196699, (s32)btlevtcmd_OffAttribute, -29999997, 16777216, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999997, 1,
    131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 109, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_gesso_right_arm_entry_data,
    0, 131163, (s32)btlevtcmd_StopWaitEvent, -29999997, 196699, (s32)btlevtcmd_OnAttribute, -29999997, 16777216,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997,
    0, -29999990, 327771, (s32)btlevtcmd_SetPos, -29999997, 59, 166, -18,
    327771, (s32)btlevtcmd_SetHomePos, -29999997, 59, 166, -18, 65644, -29999985,
    65545, 5, 393307, (s32)btlevtcmd_snd_se, -29999997, (s32)"SFX_BOSS_GESSO_ARM_APPEAR1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, 1, (s32)"GSO_F2_1", 196699, (s32)btlevtcmd_OffAttribute,
    -29999997, 16777216, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999997, 1, 131163, (s32)btlevtcmd_StartWaitEvent,
    -29999997, 109, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 33, 33, 33, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(gesso_ikasumi_attack))
    RETURN
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 weapon_gesso_ikasumi_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 852738, 0, 135, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 gesso_ikasumi_attack[] = {
    131122, -29999988, (s32)weapon_gesso_ikasumi_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"GSO_A2_1", 110, 196699, (s32)btlevtcmd_ftof, 16, -30000000, 65545,
    -30000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_UP1", -250000000, 0, -250000000,
    196699, (s32)btlevtcmd_ftof, 55, -30000000, 65545, -30000000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_GESSO_UP1", -250000000, 0, -250000000, 112, 196699, (s32)btlevtcmd_ftof,
    120, -30000000, 65545, -30000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_ftof, 90, -29999993, 196699, (s32)_ikasumi_effect,
    -2, -29999993, 107, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_GESSO_SUMI1", -250000000,
    0, -29999985, 65545, -29999993, 131163, (s32)evt_snd_sfxoff, -29999985, 109,
    196699, (s32)btlevtcmd_ftof, 10, -30000000, 65545, -30000000, 131122, -29999990,
    0, 65539, 50, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 131097, -29999995, 1, 65570, -29999995,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 49, 32, 131096, -29999990, 0, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 33, 131125, -29999990, 1,
    196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1, 65540,
    50, 33, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 65539, 99,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

USER_FUNC(_ikasumi_effect) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 count = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    Vec pos;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x -= 95.0f;
    pos.y += 75.0f;
    eff = effOpukuJetwN64Entry(0, count, pos.x, pos.y, pos.z, 2.0f);
    ((f32*)eff->userdata)[14] = 135.0f;
    ((s32*)eff->userdata)[6] = 0;
    ((s32*)eff->userdata)[7] = 0;
    ((s32*)eff->userdata)[8] = 0;
    ((s32*)eff->userdata)[10] = 0;
    ((s32*)eff->userdata)[11] = 0;
    ((s32*)eff->userdata)[12] = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(_test_rtn) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit;
    BattleUnit* target;
    s32 targetId;

    if (id == -1) {
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    // debug: pick a unit with the d-pad, then scale and move it
    if (BattlePadMultiCheckTrigger(2, 1)) {
        event->userdata[0]++;
        if (event->userdata[0] >= 3) {
            event->userdata[0] = 0;
        }
    }
    if (BattlePadMultiCheckTrigger(2, 2)) {
        event->userdata[0]--;
        if (event->userdata[0] < 0) {
            event->userdata[0] = 2;
        }
    }
    switch (event->userdata[0]) {
        case 0:
            targetId = BattleTransID(event, -2);
            break;
        case 1:
            targetId = unit->work[1];
            break;
        case 2:
            targetId = unit->work[2];
            break;
    }
    target = BattleGetUnitPtr(wp, targetId);
    BattlePadMultiCheckTrigger(2, 3);
    if (BattlePadMultiCheckNow(2, 0x40)) {
        target->mScale.x += 0.02f;
        target->mScale.y += 0.02f;
        target->mScale.z += 0.02f;
    }
    if (BattlePadMultiCheckNow(2, 0x20)) {
        target->mScale.x -= 0.02f;
        target->mScale.y -= 0.02f;
        target->mScale.z -= 0.02f;
    }
    target->mPosition.x += 0.1f * keyGetStickX(2);
    target->mPosition.y += 0.1f * keyGetSubStickY(2);
    target->mPosition.z -= 0.1f * keyGetStickY(2);
    BattlePadMultiCheckTrigger(2, 0x100);
    return EVT_RETURN_BLOCK;
}

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

EVT_BEGIN(dead_subevent)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(3))
    CALL(btlevtcmd_GetUnitId, LW(3), LW(3))
    BEGIN_SIBLING_EVENT_GET_ID(LW(1))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_KillUnit, LW(3), 0)
        END_IF
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetUnitWork, -2, 2, LW(3))
    CALL(btlevtcmd_GetUnitId, LW(3), LW(3))
    BEGIN_SIBLING_EVENT_GET_ID(LW(2))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_KillUnit, LW(3), 0)
        END_IF
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(1))
    CALL(btlevtcmd_WaitEventEnd, LW(2))
    RETURN
EVT_END()

