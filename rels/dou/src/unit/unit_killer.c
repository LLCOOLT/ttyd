#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
extern s32 _add_star_point_disp_offset[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_w[];
extern s32 evt_eff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_killer_negone_one_374;
__declspec(section ".data") s32 fd_killer_neg_one_382[1];
__declspec(section ".data") s32 fd_killer___local_PI_383[1];
__declspec(section ".data") s32 fd_killer___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_killer_one_negone_373;
__declspec(section ".data") s32 fd_killer___local_PIO2_384[1];
__declspec(section ".data") s32 fd_killer_one_381[1];
__declspec(section ".data") u64 fd_killer_negone_one_360;
__declspec(section ".data") s32 fd_killer_neg_one_365[1];
__declspec(section ".data") s32 fd_killer___local_PI_366[1];
__declspec(section ".data") s32 fd_killer___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_killer_one_negone_359;
__declspec(section ".data") s32 fd_killer___local_PIO2_367[1];
__declspec(section ".data") s32 fd_killer_one_364[1];
BattleUnitKind unit_killer;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_killer_charge_attack[48];
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static s32 init_event[39];
static __declspec(section ".data") s32 damage_event[10];
static s32 start_avoid[26];
static s32 attack_event[407];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_killer_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_killer_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_killer___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_killer___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_killer_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_killer___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_killer_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_killer_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_killer_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_killer___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_killer___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_killer_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_killer___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_killer_one_364[] = {
    1065353216,
};

BattleUnitKind unit_killer = {
    91,
    "btl_un_killer",
    2,
    0,
    1,
    1,
    1,
    0,
    0,
    70,
    0,
    50,
    9999,
    32,
    26,
    3,
    26,
    0.0f,
    13.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    0.0f,
    16.0f,
    16.9f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    32.0f,
    26.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KILLER_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 105, 0, 50, 150, 100, 70, 100, 95, 100, 95, 100, 95, 75, 0, 100, 100, 75, 100, 100, 95};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_killer", "c_kilr", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_killer_charge_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 4231, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "KIL_N_1"},
    {2, "KIL_D_1"},
    {9, "KIL_D_1"},
    {5, "KIL_K_1"},
    {4, "KIL_X_1"},
    {3, "KIL_X_1"},
    {28, "KIL_S_1"},
    {29, "KIL_Q_1"},
    {30, "KIL_Q_1"},
    {31, "KIL_A_1"},
    {39, "KIL_D_1"},
    {50, "KIL_A_1"},
    {40, "KIL_W_1"},
    {42, "KIL_R_1"},
    {56, "KIL_X_1"},
    {57, "KIL_X_1"},
    {65, "KIL_T_1"},
    {69, "KIL_S_1"},
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
    CALL(btlevtcmd_StartWaitEvent, -2)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, -2, LW(0), 10, LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), 10, LW(2))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(start_avoid)
    IF_INT_EQUAL(LW(5), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(5), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(5), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65546,
    750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_EnemyItemUseCheck,
    -2, -30000000, 131097, -30000000, 0, 65630, -30000000, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_killer_charge_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_killer_charge_attack,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_killer_charge_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_killer_charge_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_CHARGE1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 65545, 30, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_KILLER_MOVE1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_killer_charge_attack, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 65540, 90,
    46, 65572, 6, 65540, 90, 65572, 2, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 10, -29999998, 0, -1, 65630, (s32)start_avoid, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 500,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 10, -29999998, 0, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_ATTACK1", -250000000, 0, -250000000, 393307,
    (s32)evt_btl_camera_shake_w, 0, 5, 0, 15, 0, 65546, 300,
    196699, (s32)btlevtcmd_OnAttribute, -2, 16777216, 65546, 500, 65540, 98,
    65539, 91, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229991808, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 10, -29999998,
    0, -1, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, (s32)weapon_killer_charge_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_killer_charge_attack,
    256, -29999995, 393307, (s32)evt_btl_camera_shake_w, 0, 5, 0, 15,
    0, 196699, (s32)btlevtcmd_OnAttribute, -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    1, 33554432, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_ATTACK1", -250000000, 0,
    -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999998,
    10, 131125, -29999999, 20, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test",
    17, -30000000, -29999999, -29999998, -229998976, 0, 0, 0,
    0, 0, 0, 0, 196699, (s32)btlevtcmd_GetCoin, -2, -30000000,
    131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -2, -30000000, 131163,
    (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -2, -29999997, -29999999, -29999998,
    131125, -29999998, 10, 131125, -29999999, 30, 327771, (s32)_add_star_point_disp_offset,
    -29999990, -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point\0",
    0, -29999997, -29999999, -29999998, -30000000, 0, 0, 0,
    0, 0, 0, 0, 131101, -30000000, 1, 65541,
    -30000000, 6, 33, 65546, 500, 65540, 98, 65539,
    98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 200, 65539,
    99, 196699, (s32)btlevtcmd_KillUnit, -2, 0, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

