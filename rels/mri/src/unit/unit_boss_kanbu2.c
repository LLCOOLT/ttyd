#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_JumpSetting);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_msg_print);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_kanbu2_negone_one_374;
__declspec(section ".data") s32 fd_boss_kanbu2_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_kanbu2___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_kanbu2___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_kanbu2_one_negone_373;
__declspec(section ".data") s32 fd_boss_kanbu2___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_kanbu2_one_381[1];
__declspec(section ".data") u64 fd_boss_kanbu2_negone_one_360;
__declspec(section ".data") s32 fd_boss_kanbu2_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_kanbu2___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_kanbu2___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_kanbu2_one_negone_359;
__declspec(section ".data") s32 fd_boss_kanbu2___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_kanbu2_one_364[1];
BattleUnitKind unit_boss_kanbu2;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
s32 weapon_kanbu2_attack[48];
static s32 init_event[37];
static __declspec(section ".data") s32 damage_event[10];
static s32 dead_event[26];
static s32 attack_event[24];
static __declspec(section ".data") s32 wait_event[6];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_guard[18];
static s32 normal_attack_event[365];

__declspec(section ".data") u64 fd_boss_kanbu2_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_kanbu2_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_kanbu2___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_kanbu2___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_kanbu2_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_kanbu2___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_kanbu2_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_kanbu2_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_kanbu2_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_kanbu2___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_kanbu2___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_kanbu2_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_kanbu2___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_kanbu2_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_kanbu2 = {
    188,
    "btl_un_kanbu2",
    15,
    0,
    1,
    1,
    1,
    10,
    0,
    100,
    0,
    100,
    9,
    56,
    59,
    56,
    59,
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
    21.0f,
    0.0f,
    0.0f,
    28.0f,
    38.35f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    42.0f,
    52.0f,
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

static __declspec(section ".data") StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0, 100, 100, 100, 100, 0};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_kanbu2", "c_kanbu", 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

s32 weapon_kanbu2_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 4231, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(evt_msg_print, 1, STRING("このあと\nまぐなむばってんだーに　のるよてい<key>"), 0, 0)
    CALL(btlevtcmd_JumpSetting, -2, 0, FLOAT(5.0f), FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, -2, 300, 0, 0, 0, -1)
    CALL(btlevtcmd_KillUnit, -2, 0)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(weapon_kanbu2_attack))
    CALL_CHILD(PTR(normal_attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {65, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_guard[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "G_2"},
    {65, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "G_2"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "G_2"},
};

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"R_2", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 0, -1, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_JUMP1",
    -250000000, 0, -250000000, 110, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1A", 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B",
    112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229997952, -229999796, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65540, 98, 65539, 98, 131163, (s32)btlevtcmd_JumpContinue, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1C", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KANBU_HIP_ATTACK1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 0, 10,
    0, 60, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, 0, -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1C", 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 10, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, 0, -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 10, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1C", 65545, 25, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_HIP_ATTACK2",
    -250000000, 0, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KANBU_HIP_ATTACK2", -250000000, 0, -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"D_1", 65545, 15, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -2, 15, 0, -229998976,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 10, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65545, 10, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1",
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229992832, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998,
    0, -1, 0, 2, 1,
};

