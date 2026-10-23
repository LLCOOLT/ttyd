#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "party/party_motion.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);

__declspec(section ".data") u64 fd_hennya_negone_one_374;
__declspec(section ".data") s32 fd_hennya_neg_one_382[1];
__declspec(section ".data") s32 fd_hennya___local_PI_383[1];
__declspec(section ".data") s32 fd_hennya___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hennya_one_negone_373;
__declspec(section ".data") s32 fd_hennya___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hennya_one_381[1];
__declspec(section ".data") u64 fd_hennya_negone_one_360;
__declspec(section ".data") s32 fd_hennya_neg_one_365[1];
__declspec(section ".data") s32 fd_hennya___local_PI_366[1];
__declspec(section ".data") s32 fd_hennya___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hennya_one_negone_359;
__declspec(section ".data") s32 fd_hennya___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hennya_one_364[1];
BattleUnitKind unit_hennya;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
static s32 weapon_hannya_attack[48];
static PoseTableEntry pose_table[18];
static s32 init_event[25];
static s32 dmg_avoid_counter_thorn_head_event[68];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[455];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_hennya_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hennya_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hennya___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hennya___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hennya_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hennya___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hennya_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hennya_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hennya_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hennya___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hennya___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hennya_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hennya___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hennya_one_364[] = {
    1065353216,
};

BattleUnitKind unit_hennya = {
    163,
    "btl_un_hennya",
    12,
    0,
    1,
    1,
    33,
    1,
    3,
    70,
    1,
    50,
    9999,
    26,
    40,
    3,
    35,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    0.0f,
    13.0f,
    20.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    26.0f,
    40.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_HANNYA_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {70, 90, 70, 150, 70, 150, 150, 70, 150, 90, 150, 90, 150, 90, 70, 80, 80, 150, 70, 0, 0, 30};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_hennya", "c_hannya_t", 0.0f, 0.0f, 0.0f, 0.0f, 27.0f, 0.0f, 0.0f, 37.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
};

static s32 weapon_hannya_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 2, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_3"},
    {39, "D_1"},
    {50, "A_1"},
    {40, "W_1"},
    {42, "R_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 31)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 53)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 33)
        GOTO(90)
    END_IF
    ADD(LW(1), 43)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65545,
    30, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_EnemyItemUseCheck,
    -2, -30000000, 131097, -30000000, 0, 65630, -30000000, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_hannya_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_hannya_attack,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_hannya_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_hannya_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999986, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HANNYA_CHARGE1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1",
    131122, -29999985, 0, 65541, 0, 65545, 2, 327771,
    (s32)btlevtcmd_AddPos, -2, 1, 0, 0, 65545, 2, 327771,
    (s32)btlevtcmd_AddPos, -2, -1, 0, 0, 131125, -29999985, 1,
    131101, -29999985, 10, 7, 33, 6, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_HANNYA_MOVE1", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_3", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    0, -29999998, 0, -1, 0, 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_hannya_attack, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 131127, -29999986, 500, 131125, -30000000,
    -29999986, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, 0, -29999998, 0, -1, 0, 65540, 98,
    65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0,
    -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_hannya_attack, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_hannya_attack, 256, -29999995, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 131127, -29999986, 500, 131125, -30000000,
    -29999986, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, 0, -29999998, 0, -1, 0, 65540, 98,
    65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)evt_snd_sfxoff,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HANNYA_MOVE2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos,
    -2, 300, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_3", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 50,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_HANNYA_MOVE3\0\0\0", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229994880, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 30, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229997952, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 10, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229998976, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65546, 300, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

