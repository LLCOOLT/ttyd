#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetSelectNextEnemy);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_sub_random);
static USER_FUNC(teresa_check_move);
static USER_FUNC(teresa_check_teresa);
static USER_FUNC(teresa_check_trans);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SetAlpha[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_purple_teresa_negone_one_374;
__declspec(section ".data") s32 fd_purple_teresa_neg_one_382[1];
__declspec(section ".data") s32 fd_purple_teresa___local_PI_383[1];
__declspec(section ".data") s32 fd_purple_teresa___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_purple_teresa_one_negone_373;
__declspec(section ".data") s32 fd_purple_teresa___local_PIO2_384[1];
__declspec(section ".data") s32 fd_purple_teresa_one_381[1];
__declspec(section ".data") u64 fd_purple_teresa_negone_one_360;
__declspec(section ".data") s32 fd_purple_teresa_neg_one_365[1];
__declspec(section ".data") s32 fd_purple_teresa___local_PI_366[1];
__declspec(section ".data") s32 fd_purple_teresa___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_purple_teresa_one_negone_359;
__declspec(section ".data") s32 fd_purple_teresa___local_PIO2_367[1];
__declspec(section ".data") s32 fd_purple_teresa_one_364[1];
BattleUnitKind unit_purple_teresa_15_data_493B8;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_teresa_attack[48];
static s32 weapon_teresa_trans_myself[48];
static s32 weapon_teresa_trans[48];
static s32 weapon_teresa_move[48];
static PoseTableEntry pose_table[17];
static __declspec(section ".data") BattleDataEntry data_table[1];
static s32 init_event[47];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[153];
static s32 normal_attack_event[354];
static s32 trans_myself_event[196];
static s32 trans_event[289];
static s32 move_event[84];
static s32 move_event_sub[103];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_purple_teresa_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_purple_teresa_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_purple_teresa___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_purple_teresa___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_purple_teresa_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_purple_teresa___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_purple_teresa_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_purple_teresa_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_purple_teresa_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_purple_teresa___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_purple_teresa___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_purple_teresa_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_purple_teresa___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_purple_teresa_one_364[] = {
    1065353216,
};

BattleUnitKind unit_purple_teresa_15_data_493B8 = {
    106,
    "btl_un_purple_teresa",
    8,
    0,
    1,
    1,
    24,
    0,
    4,
    70,
    0,
    50,
    9999,
    34,
    32,
    0,
    32,
    0.0f,
    16.0f,
    0.0f,
    0,
    -3,
    0.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    0.0f,
    17.0f,
    20.8f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    34.0f,
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
    "SFX_ENM_TELESA_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {40, 40, 100, 0, 40, 100, 100, 40, 100, 85, 100, 85, 100, 90, 50, 40, 85, 100, 0, 100, 100, 10};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_purple_teresa", "c_teresa_p", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_teresa_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_teresa_trans_myself[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677852672, 0, 0, 100, 0, 0,
};

static s32 weapon_teresa_trans[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830240, 536870912, 770, 0, 264, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677852672, 0, 0, 100, 0, 0,
};

static s32 weapon_teresa_move[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 8, 2047, 0,
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
    {31, "A_2"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 15)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 18, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(13), 0)
        ELSE
        SET_VALUE(LW(13), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 5, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 0)
        ELSE
        CALL(teresa_check_trans, -2, LW(14))
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 5, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(15), 0)
        ELSE
        CALL(teresa_check_move, LW(15))
    END_IF
    SET_VALUE(LW(0), 0)
    ADD(LW(0), 50)
    ADD(LW(0), 25)
    ADD(LW(0), 25)
    ADD(LW(0), 15)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 25)
    IF_INT_LESS(LW(1), LW(0))
        IF_INT_EQUAL(LW(13), 1)
            CALL_CHILD(PTR(trans_myself_event))
            GOTO(99)
        END_IF
    END_IF
    ADD(LW(0), 25)
    IF_INT_LESS(LW(1), LW(0))
        IF_INT_EQUAL(LW(14), 1)
            CALL_CHILD(PTR(trans_event))
            GOTO(99)
        END_IF
    END_IF
    ADD(LW(0), 15)
    IF_INT_LESS(LW(1), LW(0))
        IF_INT_EQUAL(LW(15), 1)
            CALL_CHILD(PTR(move_event))
            GOTO(99)
        END_IF
    END_IF
    CALL_CHILD(PTR(normal_attack_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_teresa_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_teresa_attack,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_teresa_attack,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_teresa_attack, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TELESA_MOVE3", -250000000, 0, -250000000,
    110, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, 255, 131122, -29999993,
    256, 65541, 16, 65545, 1, 131126, -29999993, 16,
    262235, (s32)btlevtcmd_SetAlpha, -2, 1, -29999993, 6, 65545, 20,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TELESA_MOVE4", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1", 262235, (s32)btlevtcmd_SetAlpha, -2, 1,
    0, 131122, -29999993, -1, 65541, 8, 65545, 1,
    131125, -29999993, 32, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, -29999993,
    6, 112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 15, 131125, -29999998,
    5, 131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 60, -5, 4, 0, -1, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, 255,
    65545, 15, 110, 65545, 9, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TELESA_ATTACK1", -250000000, 0, -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_2", 65545, 15, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_teresa_attack, 0, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 65539, 90, 65545,
    30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"X_1", 65545, 60,
    65540, 98, 65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0, 1,
    1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_add_zoom, 0, -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_teresa_attack, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_teresa_attack, 256, -29999995, 65545,
    30, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_AddPartsRotate,
    -2, 1, 0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 40, 0, 4, 0, -1, 393307, (s32)btlevtcmd_SetPartsRotate,
    -2, 1, 0, 0, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    2, 1,
};

static s32 trans_myself_event[] = {
    131122, -29999997, -2, 131122, -29999996, 1, 262235, (s32)btlevtcmd_CheckStatus,
    -2, 18, -29999992, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_teresa_trans_myself, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_teresa_trans_myself, 196699,
    (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 300,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 30,
    131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 30, 10, 4, 0, -1, 65545, 30,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TELESA_MOVE2", -250000000, 0, -250000000, 131096,
    -29999992, 0, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, 255, 131122,
    -29999993, 256, 110, 65541, 16, 65545, 1, 131126,
    -29999993, 8, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, -29999993, 6,
    112, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1", 393307,
    (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 180, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 10, 0, 5, 0, -1, 65545,
    10, 65541, 6, 65545, 1, 393307, (s32)btlevtcmd_AddPartsRotate, -2,
    1, 0, 15, 0, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"S_1", 65541, 6, 65545, 1, 393307, (s32)btlevtcmd_AddPartsRotate,
    -2, 1, 0, 15, 0, 6, 65545, 12,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 262235, (s32)btlevtcmd_SetAlpha, -2, 1, 255, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, (s32)weapon_teresa_trans_myself, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_teresa_trans_myself,
    256, -29999995, 2, 1,
};

static s32 trans_event[] = {
    65539, 0, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy,
    -2, -30000000, (s32)weapon_teresa_trans, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_teresa_trans, -29999997, -29999996,
    131096, -29999997, -1, 65540, 99, 33, 196699, (s32)teresa_check_teresa,
    -29999997, -30000000, 131096, -30000000, 1, 262235, (s32)btlevtcmd_CheckStatus, -29999997,
    18, -30000000, 131096, -30000000, 0, 65540, 1, 33,
    33, 65540, 0, 65539, 1, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_teresa_trans,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    (s32)weapon_teresa_trans, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 300, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -29999990, -29999989, -29999988, 131100,
    -30000000, -29999990, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 0,
    0, 32, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 180,
    0, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TELESA_MOVE3", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, 255, 131122, -29999993,
    256, 110, 65541, 16, 65545, 1, 131126, -29999993,
    16, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, -29999993, 6, 112,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000,
    40, 131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 60, -5, 4, 0, -1, 393307,
    (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 0, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TELESA_MOVE4", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_SetAlpha, -2, 1, 0, 131122, -29999993,
    -1, 65541, 16, 65545, 1, 131125, -29999993, 16,
    262235, (s32)btlevtcmd_SetAlpha, -2, 1, -29999993, 6, 262235, (s32)btlevtcmd_SetAlpha,
    -2, 1, 255, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 40, 0,
    0, 0, -1, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_teresa_trans_myself, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_teresa_trans_myself, 256, -29999995, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 30, -5, 4, 0, -1,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, 1, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65545, 20, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65539, 99, 2,
    1,
};

static EVT_BEGIN(move_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_teresa_move))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_teresa_move), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    SET_VALUE(LW(12), 80)
    LABEL(0)
    CALL(teresa_check_teresa, LW(3), LW(5))
    IF_INT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_GetUnitWork, LW(3), 0, LW(6))
        IF_INT_EQUAL(LW(6), 0)
            SPAWN_EVENT(PTR(move_event_sub))
            ADD(LW(12), 20)
        END_IF
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        GOTO(0)
    END_IF
    WAIT_FRAMES(LW(12))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
    RETURN
EVT_END()

static s32 move_event_sub[] = {
    196699, (s32)btlevtcmd_GetUnitId, -2, -29999999, 131096, -29999997, -29999999, 131122,
    -30000000, 0, 131122, -29999999, 0, 32, 196699, (s32)evt_sub_random,
    20, -30000000, 131125, -30000000, 60, 131122, -29999999, 12,
    33, 65545, -30000000, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, 1,
    262235, (s32)btlevtcmd_OnPartsAttribute, -29999997, 1, 6291456, 110, 65541, 60,
    327771, (s32)btlevtcmd_AddRotate, -29999997, 0, -29999999, 0, 65545, 1,
    6, 112, 110, 65545, 30, 196699, (s32)btlevtcmd_GetUnitId, -2,
    -30000000, 131096, -29999997, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"T_1", 33, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TELESA_MOVE1\0\0\0", -250000000,
    0, -250000000, 393307, (s32)btlevtcmd_GetPartsPos, -29999997, 1, -30000000, -29999999,
    -29999998, 131122, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -29999997, -30000000,
    -29999999, -29999998, 60, 10, 4, 0, -1, 327771,
    (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(teresa_check_trans) {
    s32* args = event->args;
    s32 num = 0;
    s32 id = evtGetValue(event, args[0]);
    s32 self;
    s32 i;

    self = BattleTransID(event, id);

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL) {
            if (unit->currentKind == 0x4B && !BtlUnit_CheckStatus(unit, 0x12) && i != self) {
                num++;
            }
            if (unit->currentKind == 0x6A && !BtlUnit_CheckStatus(unit, 0x12) && i != self) {
                num++;
            }
        }
    }
    if (num >= 1) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
static USER_FUNC(teresa_check_move) {
    s32* args = event->args;
    s32 num = 0;
    s32 i;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL) {
            if (unit->currentKind == 0x4B && unit->work[0] == 0) {
                num++;
            }
            if (unit->currentKind == 0x6A && unit->work[0] == 0) {
                num++;
            }
        }
    }
    if (num >= 1) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
static USER_FUNC(teresa_check_teresa) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 result = 0;
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit == NULL) {
        evtSetValue(event, args[1], 0);
        return EVT_RETURN_DONE;
    }
    if (unit->currentKind == 0x4B) {
        result = 1;
    }
    if (unit->currentKind == 0x6A) {
        result = 1;
    }
    evtSetValue(event, args[1], result);
    return EVT_RETURN_DONE;
}
