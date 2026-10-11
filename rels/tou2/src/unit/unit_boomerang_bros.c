#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AttackDeclareAll);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetFirstAttackTarget);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetSelectEnemy);
USER_FUNC(btlevtcmd_GetSelectNextEnemy);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_sub_random);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_AddUnitWork[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_DivePartsPosition[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boomerang_bros_negone_one_374;
__declspec(section ".data") s32 fd_boomerang_bros_neg_one_382[1];
__declspec(section ".data") s32 fd_boomerang_bros___local_PI_383[1];
__declspec(section ".data") s32 fd_boomerang_bros___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boomerang_bros_one_negone_373;
__declspec(section ".data") s32 fd_boomerang_bros___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boomerang_bros_one_381[1];
__declspec(section ".data") u64 fd_boomerang_bros_negone_one_360;
__declspec(section ".data") s32 fd_boomerang_bros_neg_one_365[1];
__declspec(section ".data") s32 fd_boomerang_bros___local_PI_366[1];
__declspec(section ".data") s32 fd_boomerang_bros___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boomerang_bros_one_negone_359;
__declspec(section ".data") s32 fd_boomerang_bros___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boomerang_bros_one_364[1];
BattleUnitKind unit_boomerang_bros;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[4];
s32 weapon_boomerang_bros_attack[48];
s32 weapon_boomerang_bros_renzoku_attack[48];
static s32 init_event[21];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[71];
static s32 damage_check_sub[107];
static __declspec(section ".data") s32 damage_check_no_last[7];
static s32 damage_check_last[38];
s32 boomerang_move_event[355];
static s32 normal_attack_event[174];
static s32 renzoku_attack_event[178];
s32 normal_attack_event_confuse[322];
s32 renzoku_attack_event_confuse[328];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boomerang_bros_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boomerang_bros_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boomerang_bros___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boomerang_bros___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boomerang_bros_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boomerang_bros___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boomerang_bros_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boomerang_bros_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boomerang_bros_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boomerang_bros___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boomerang_bros___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boomerang_bros_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boomerang_bros___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boomerang_bros_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boomerang_bros = {
    57,
    "btl_un_boomerang_bros",
    7,
    0,
    1,
    1,
    20,
    0,
    2,
    70,
    2,
    50,
    9999,
    36,
    44,
    3,
    44,
    0.0f,
    22.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    0.0f,
    10.0f,
    28.0f,
    0.0f,
    0.0f,
    22.0f,
    0.0f,
    36.0f,
    44.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BOOME_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    4,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 80, 70, 100, 80, 100, 100, 70, 100, 80, 100, 80, 100, 95, 80, 70, 60, 100, 80, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "BRO_N_1"},
    {2, "BRO_Y_1"},
    {9, "BRO_Y_1"},
    {5, "BRO_K_1"},
    {4, "BRO_X_1"},
    {3, "BRO_X_1"},
    {27, "BRO_D_1"},
    {28, "BRO_S_1"},
    {29, "BRO_Q_1"},
    {30, "BRO_Q_1"},
    {31, "BRO_S_1"},
    {39, "BRO_D_1"},
    {42, "BRO_R_1"},
    {40, "BRO_W_1"},
    {56, "BRO_X_1"},
    {57, "BRO_X_1"},
    {65, "BRO_T_1"},
    {69, "BRO_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_boomerang_bros", "c_burosu_b", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_boomerang_bros", "c_burosu_b", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_boomerang_bros", "c_burosu_b", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_boomerang_bros", "c_burosu_b", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

s32 weapon_boomerang_bros_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_boomerang_bros_renzoku_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
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
    CALL(btlevtcmd_SetUnitWork, -2, 7, 0)
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
    CALL(btlevtcmd_GetHp, -2, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 3)
        SET_VALUE(LW(0), 70)
        ADD(LW(0), 30)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 30)
            CALL_CHILD(PTR(renzoku_attack_event))
            GOTO(99)
        END_IF
    END_IF
    CALL_CHILD(PTR(normal_attack_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_check_sub)
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(6), 0, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(99)
    LABEL(91)
    CALL(btlevtcmd_GetUnitWork, -2, 7, LW(8))
    IF_INT_EQUAL(LW(8), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(6))
        CALL(btlevtcmd_SetUnitWork, -2, 7, 1)
    END_IF
    IF_INT_EQUAL(LW(7), 1)
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(6), 256, LW(5))
        ELSE
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(6), 0, LW(5))
    END_IF
    SET_VALUE(LW(0), 1)
    GOTO(99)
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_check_no_last)
    SET_VALUE(LW(7), 0)
    CALL_CHILD(PTR(damage_check_sub))
    RETURN
EVT_END()

static EVT_BEGIN(damage_check_last)
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetUnitWork, -2, 7, LW(8))
        IF_INT_EQUAL(LW(8), 0)
            CALL(btlevtcmd_ResultACDefence, LW(3), LW(6))
            CALL(btlevtcmd_SetUnitWork, -2, 7, 1)
        END_IF
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(6), 256, LW(5))
        ELSE
        SET_VALUE(LW(7), 1)
        CALL_CHILD(PTR(damage_check_sub))
    END_IF
    RETURN
EVT_END()

s32 boomerang_move_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, -29999985, (s32)"BRO_A_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999999, 20, 393307, (s32)btlevtcmd_SetPartsPos, -2,
    -29999985, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999985,
    0, 0, -180, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, -29999985, 0,
    0, 0, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 16777216, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 33554432, 131122, -29999991, 0, 110,
    65541, 0, 65545, 1, 393307, (s32)btlevtcmd_GetPartsPos, -2, -29999985,
    -29999990, -29999988, -29999987, 131096, -29999991, 2, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 7, 0, 33, 65570, -29999991, 65572, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999997, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    3, -29999996, 131096, -29999997, -1, 131122, -29999991, 1,
    48, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999989, -29999988,
    -29999987, 131101, -29999990, -29999989, 48, 33, 65630, (s32)damage_check_no_last,
    131122, -29999991, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5, -30000000,
    46, 65572, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999997,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -29999996, 131096, -29999997, -1,
    131122, -29999991, 2, 48, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -29999989, -29999988, -29999987, 131101, -29999990, -29999989, 48,
    33, 65630, (s32)damage_check_no_last, 131122, -29999991, 2, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 6, -30000000, 46, 65572, 2, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -29999997, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -29999996,
    131096, -29999997, -1, 131122, -29999991, 3, 48, 33,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999989, -29999988, -29999987, 131098,
    -29999990, -29999989, 48, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 6,
    -30000000, 131096, -29999986, 0, 65630, (s32)damage_check_no_last, 32, 65630,
    (s32)damage_check_last, 33, 131122, -29999991, 3, 46, 65572, 3,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999997, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    3, -29999996, 131096, -29999997, -1, 131122, -29999991, 4,
    48, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999989, -29999988,
    -29999987, 131098, -29999990, -29999989, 48, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 5, -30000000, 131096, -29999986, 0, 65630, (s32)damage_check_no_last,
    32, 65630, (s32)damage_check_last, 33, 131122, -29999991, 4, 46,
    65572, 4, 7, 46, 49, 65539, 10, 6,
    112, 110, 65541, 0, 65545, 1, 393307, (s32)btlevtcmd_AddPartsRotate,
    -2, -29999985, 0, 0, 64, 6, 112, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK2", -250000000, 0, -29999992, 720987, (s32)btlevtcmd_DivePartsPosition,
    -2, -29999985, -200, -29999999, -29999998, 40, -230020480, 4,
    0, -1, 131163, (s32)evt_snd_sfxoff, -29999992, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BOOME_ATTACK3", -250000000, 0, -29999992, 720987, (s32)btlevtcmd_DivePartsPosition, -2, -29999985,
    -30000000, -29999999, -29999998, 40, -229979520, 1, 0, -1,
    131163, (s32)evt_snd_sfxoff, -29999992, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 16777216,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 33554432, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BOOME_ATTACK4", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AddUnitWork, -2, 0,
    1, 2, 1,
};

static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_boomerang_bros_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_boomerang_bros_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, LW(3), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(normal_attack_event_confuse))
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_boomerang_bros_attack))
    CALL(btlevtcmd_AttackDeclareAll, -2)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_boomerang_bros_attack))
    SET_VALUE(LW(0), 1)
    SET_VALUE(LW(1), 3)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 6, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    LABEL(10)
    CALL(btlevtcmd_SetUnitWork, -2, LW(0), LW(3))
    CALL(btlevtcmd_SetUnitWork, -2, LW(1), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    ADD(LW(0), 1)
    ADD(LW(1), 1)
    GOTO(10)
    LABEL(20)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(27)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(14), 1)
    SET_VALUE(LW(6), PTR(weapon_boomerang_bros_attack))
    SPAWN_EVENT(PTR(boomerang_move_event))
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_S_1"))
    WAIT_MS(500)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(renzoku_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_boomerang_bros_renzoku_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_boomerang_bros_renzoku_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, LW(3), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(normal_attack_event_confuse))
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_boomerang_bros_renzoku_attack))
    CALL(btlevtcmd_AttackDeclareAll, -2)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_boomerang_bros_renzoku_attack))
    SET_VALUE(LW(0), 1)
    SET_VALUE(LW(1), 3)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 6, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    LABEL(10)
    CALL(btlevtcmd_SetUnitWork, -2, LW(0), LW(3))
    CALL(btlevtcmd_SetUnitWork, -2, LW(1), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    ADD(LW(0), 1)
    ADD(LW(1), 1)
    GOTO(10)
    LABEL(20)
    SET_VALUE(LW(6), PTR(weapon_boomerang_bros_renzoku_attack))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(27)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(14), 0)
    SPAWN_EVENT(PTR(boomerang_move_event))
    WAIT_MS(750)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(27)
    SET_VALUE(LW(15), 4)
    SET_VALUE(LW(14), 1)
    SPAWN_EVENT(PTR(boomerang_move_event))
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 2)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_S_1"))
    WAIT_MS(500)
    LABEL(99)
    RETURN
EVT_END()

s32 normal_attack_event_confuse[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_boomerang_bros_attack, 131163,
    (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_boomerang_bros_attack,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"BRO_A_2A",
    65545, 27, 131122, -29999985, 2, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BOOME_ATTACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, -29999985,
    (s32)"BRO_A_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -29999999, 20, 393307, (s32)btlevtcmd_SetPartsPos, -2, -29999985, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999985, 0, 0, -180,
    393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, -29999985, 0, 0, 0, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999985,
    33554432, 110, 65541, 0, 65545, 1, 393307, (s32)btlevtcmd_AddPartsRotate,
    -2, -29999985, 0, 0, 64, 6, 112, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK2", -250000000, 0, -29999992, 720987, (s32)btlevtcmd_DivePartsPosition,
    -2, -29999985, 250, 40, 0, 15, -230020480, 4,
    0, -1, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 720987, (s32)btlevtcmd_DivePartsPosition, -2,
    -29999985, -30, 40, 0, 15, -229979520, 1, 0,
    -1, 131163, (s32)evt_snd_sfxoff, -29999992, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK3",
    -250000000, 0, -29999992, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 20, 720987, (s32)btlevtcmd_DivePartsPosition, -2, -29999985,
    -30000000, -29999999, -29999998, 15, -230010240, 1, 0, -1,
    131163, (s32)evt_snd_sfxoff, -29999992, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 16777216,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 33554432, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BOOME_ATTACK4", -250000000, 0, -250000000, 65539, 0, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, (s32)weapon_boomerang_bros_attack, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65540, 97, 65539, 91, 131096, -29999990,
    0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 7, -29999992, 131096, -29999992,
    0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_boomerang_bros_attack, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    7, 1, 33, 131125, -29999990, 1, 33, 110,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_boomerang_bros_attack, 0, -29999995,
    196699, (s32)evt_sub_random, 10, -30000000, 131125, -30000000, 30, 65545,
    -30000000, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_boomerang_bros_attack, 256,
    -29999995, 112, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 65540, 0, 33,
    65539, 99, 65545, 100, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    2, 1,
};

s32 renzoku_attack_event_confuse[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_boomerang_bros_renzoku_attack, 131163,
    (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_boomerang_bros_renzoku_attack,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0, 65541,
    2, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"BRO_A_2A", 65545, 27, 131122, -29999985, 2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, -29999985, (s32)"BRO_A_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 20, 393307, (s32)btlevtcmd_SetPartsPos, -2, -29999985,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999985, 0,
    0, -180, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, -29999985, 0, 0,
    0, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, -29999985, 33554432, 110, 65541, 0, 65545, 1,
    393307, (s32)btlevtcmd_AddPartsRotate, -2, -29999985, 0, 0, 64, 6,
    112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK2", -250000000, 0, -29999992,
    720987, (s32)btlevtcmd_DivePartsPosition, -2, -29999985, 250, 40, 0, 15,
    -230020480, 4, 0, -1, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 720987,
    (s32)btlevtcmd_DivePartsPosition, -2, -29999985, -30, 40, 0, 15, -229979520,
    1, 0, -1, 131163, (s32)evt_snd_sfxoff, -29999992, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_BOOME_ATTACK3", -250000000, 0, -29999992, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 131125, -29999999, 20, 720987, (s32)btlevtcmd_DivePartsPosition,
    -2, -29999985, -30000000, -29999999, -29999998, 15, -230010240, 1,
    0, -1, 131163, (s32)evt_snd_sfxoff, -29999992, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    -29999985, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 33554432, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOOME_ATTACK4", -250000000, 0, -250000000, 6, 65539,
    0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_boomerang_bros_renzoku_attack, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 97, 65539,
    91, 131096, -29999990, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 7,
    -29999992, 131096, -29999992, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_boomerang_bros_renzoku_attack,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 7, 1, 33, 131125, -29999990,
    1, 33, 110, 65541, 3, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_boomerang_bros_renzoku_attack, 0, -29999995, 196699, (s32)evt_sub_random, 10,
    -30000000, 131125, -30000000, 30, 65545, -30000000, 6, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_boomerang_bros_renzoku_attack, 256, -29999995, 112,
    65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 65540, 0, 33, 65539, 99,
    65545, 160, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

