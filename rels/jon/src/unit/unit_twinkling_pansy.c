#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff64);
USER_FUNC(evt_sub_random);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsBlur[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_map_blend_off[];
extern s32 evt_map_set_blend[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_twinkling_pansy_negone_one_374;
__declspec(section ".data") s32 fd_twinkling_pansy_neg_one_382[1];
__declspec(section ".data") s32 fd_twinkling_pansy___local_PI_383[1];
__declspec(section ".data") s32 fd_twinkling_pansy___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_twinkling_pansy_one_negone_373;
__declspec(section ".data") s32 fd_twinkling_pansy___local_PIO2_384[1];
__declspec(section ".data") s32 fd_twinkling_pansy_one_381[1];
__declspec(section ".data") u64 fd_twinkling_pansy_negone_one_360;
__declspec(section ".data") s32 fd_twinkling_pansy_neg_one_365[1];
__declspec(section ".data") s32 fd_twinkling_pansy___local_PI_366[1];
__declspec(section ".data") s32 fd_twinkling_pansy___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_twinkling_pansy_one_negone_359;
__declspec(section ".data") s32 fd_twinkling_pansy___local_PIO2_367[1];
__declspec(section ".data") s32 fd_twinkling_pansy_one_364[1];
BattleUnitKind unit_twinkling_pansy_15_data_40EC8;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_twinkling_pansy_attack[48];
static s32 attack_event[46];
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static s32 init_event[23];
static s32 twink_event[56];
static __declspec(section ".data") s32 damage_event[10];
static s32 song_event[300];
static s32 escape_event[96];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_twinkling_pansy_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_twinkling_pansy_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_twinkling_pansy___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_twinkling_pansy___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_twinkling_pansy_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_twinkling_pansy___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_twinkling_pansy_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_twinkling_pansy_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_twinkling_pansy_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_twinkling_pansy___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_twinkling_pansy___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_twinkling_pansy_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_twinkling_pansy___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_twinkling_pansy_one_364[] = {
    1065353216,
};

BattleUnitKind unit_twinkling_pansy_15_data_40EC8 = {
    70,
    "btl_un_twinkling_pansy",
    20,
    0,
    1,
    1,
    100,
    0,
    5,
    70,
    5,
    70,
    9999,
    22,
    32,
    5,
    32,
    0.0f,
    16.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    11.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    11.0f,
    0.0f,
    0.0f,
    6.0f,
    20.8f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    22.0f,
    32.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_PANSY_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {50, 10, 10, 100, 30, 100, 100, 10, 100, 10, 100, 10, 100, 10, 10, 100, 60, 100, 10, 100, 100, 10};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_twinkling_pansy", "c_kpansy", 0.0f, 0.0f, 0.0f, 0.0f, 29.0f, 0.0f, 0.0f, 34.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_twinkling_pansy_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    20, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 71, 2047, -2147483648,
    1258618880, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(0), 20)
    ADD(LW(0), 80)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 20)
        SET_VALUE(LW(9), PTR(weapon_twinkling_pansy_attack))
        CALL_CHILD(PTR(song_event))
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(escape_event))
    GOTO(99)
    LABEL(99)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "PAN_N_1"},
    {2, "PAN_Y_1"},
    {9, "PAN_Y_1"},
    {5, "PAN_K_1"},
    {4, "PAN_X_1"},
    {3, "PAN_X_1"},
    {28, "PAN_S_1"},
    {29, "PAN_Q_1"},
    {30, "PAN_Q_1"},
    {31, "PAN_S_1"},
    {39, "PAN_D_1"},
    {50, "PAN_A_1"},
    {42, "PAN_R_1"},
    {40, "PAN_W_1"},
    {56, "PAN_X_1"},
    {57, "PAN_X_1"},
    {65, "PAN_T_1"},
    {69, "PAN_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    SPAWN_EVENT(PTR(twink_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(twink_event)
    LABEL(0)
    WAIT_FRAMES(40)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(btlevtcmd_GetStatusMg, -2, LW(3))
    MULTIPLY_FLOAT(LW(1), LW(3))
    ADD(LW(2), 15)
    CALL(evt_eff64, STRING(""), STRING("stardust_n64"), 2, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
END_IF
GOTO(0)
LABEL(99)
RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 song_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 131122, -30000000, 255, 131122, -29999999, 255,
    65541, 0, 131098, -30000000, 192, 7, 33, 393307,
    (s32)evt_map_set_blend, 0, -30000000, -29999999, -29999999, 255, 131126, -30000000,
    2, 65545, 1, 6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PANSY_ATTACK1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50,
    110, 65541, 10, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131098, -29999985, 0, 983131, (s32)evt_eff64, (s32)"", (s32)"onpu_n64",
    1, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 0, 0, 0, 32, 983131, (s32)evt_eff64, (s32)"",
    (s32)"onpu_n64", 2, -30000000, -29999999, -29999998, 0, 0, 0,
    0, 0, 0, 0, 0, 33, 65545, 12,
    6, 112, 65545, 120, 131122, -29999994, 0, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 10, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 97, 46, 49, 65539,
    90, 65540, 97, 65539, 91, 131096, -29999994, 0,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 131122, -29999994, 1, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131096, -29999997, -1, 65540, 98, 33, 65540, 10,
    65539, 98, 131122, -30000000, 192, 131122, -29999999, 255,
    65541, 0, 131101, -30000000, 256, 7, 33, 393307,
    (s32)evt_map_set_blend, 0, -30000000, -29999999, -29999999, 255, 131125, -30000000,
    2, 65545, 1, 6, 131163, (s32)evt_map_blend_off, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69,
    65546, 500, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 escape_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PANSY_ESCAPE1_1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PAN_E_1", 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    180, 0, 65546, 250, 786523, (s32)btlevtcmd_SetPartsBlur, -2, 1,
    255, 255, 255, 255, 100, 100, 100, 100,
    0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 67108864, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PANSY_ESCAPE1_2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, -229979520, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PANSY_ESCAPE2", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229990784, 524379, (s32)btlevtcmd_MovePosition, -2, 300, -29999999, -29999998,
    0, -1, 0, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 67108864,
    65546, 500, 196699, (s32)btlevtcmd_KillUnit, -2, 0, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

