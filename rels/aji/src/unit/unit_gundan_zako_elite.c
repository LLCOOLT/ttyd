#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_sub_random);

__declspec(section ".data") u64 fd_gundan_zako_elite_negone_one_374;
__declspec(section ".data") s32 fd_gundan_zako_elite_neg_one_382[1];
__declspec(section ".data") s32 fd_gundan_zako_elite___local_PI_383[1];
__declspec(section ".data") s32 fd_gundan_zako_elite___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gundan_zako_elite_one_negone_373;
__declspec(section ".data") s32 fd_gundan_zako_elite___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gundan_zako_elite_one_381[1];
__declspec(section ".data") u64 fd_gundan_zako_elite_negone_one_360;
__declspec(section ".data") s32 fd_gundan_zako_elite_neg_one_365[1];
__declspec(section ".data") s32 fd_gundan_zako_elite___local_PI_366[1];
__declspec(section ".data") s32 fd_gundan_zako_elite___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gundan_zako_elite_one_negone_359;
__declspec(section ".data") s32 fd_gundan_zako_elite___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gundan_zako_elite_one_364[1];
BattleUnitKind unit_gundan_zako_elite;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[16];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static s32 weapon_gundan_zako_attack[48];
static s32 weapon_gundan_zako_jump_attack[48];
static s32 weapon_gundan_zako_dekadeka_bottle[48];
static s32 init_event[42];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[98];
static s32 attack_common_event1[182];
static s32 attack_common_event2[33];
static s32 normal_attack_event[307];
static s32 jump_attack_event[324];
static s32 dekadeka_event[125];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_gundan_zako_elite_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gundan_zako_elite_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gundan_zako_elite___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gundan_zako_elite___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gundan_zako_elite_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gundan_zako_elite___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gundan_zako_elite_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gundan_zako_elite_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gundan_zako_elite_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gundan_zako_elite___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gundan_zako_elite___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gundan_zako_elite_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gundan_zako_elite___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gundan_zako_elite_one_364[] = {
    1065353216,
};

BattleUnitKind unit_gundan_zako_elite = {
    120,
    "btl_un_gundan_zako_elite",
    10,
    0,
    1,
    1,
    28,
    0,
    2,
    70,
    2,
    50,
    9999,
    30,
    36,
    0,
    36,
    0.0f,
    18.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
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
    12.0f,
    27.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    30.0f,
    36.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_3RD1_DAMAGED1",
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

static __declspec(section ".data") StatusVulnerability regist = {70, 70, 70, 100, 70, 100, 100, 60, 100, 85, 100, 85, 100, 85, 60, 80, 60, 100, 60, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {27, "Z_1"},
    {28, "S_1"},
    {29, "D_1"},
    {30, "D_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_1"},
    {40, "W_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gundan_zako_elite", "c_zako_e", 0.0f, 0.0f, 0.0f, 0.0f, 28.0f, 0.0f, 0.0f, 38.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_gundan_zako_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 4231, 2, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_jump_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 20615, 12, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_gundan_zako_dekadeka_bottle[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 100, 50462720, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_3RD1_MOVE1"), STRING("SFX_ENM_3RD1_MOVE2"), 0, 5, 5)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_3RD1_MOVE1"), STRING("SFX_ENM_3RD1_MOVE2"), 0, 10, 10)
    CALL(btlevtcmd_SetJumpSound, -2, 0, STRING("SFX_ENM_3RD1_LANDING1"))
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
    LABEL(10)
    SET_VALUE(LW(0), 0)
    ADD(LW(0), 50)
    ADD(LW(0), 30)
    ADD(LW(0), 20)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 50)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 30)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(PTR(jump_attack_event))
        GOTO(99)
    END_IF
    ADD(LW(0), 20)
    IF_INT_LESS(LW(1), LW(0))
        CALL(btlevtcmd_CheckStatus, -2, 10, LW(2))
        IF_INT_EQUAL(LW(2), 0)
            CALL_CHILD(PTR(dekadeka_event))
            GOTO(99)
        END_IF
    END_IF
    GOTO(10)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 attack_common_event1[] = {
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 8,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999986, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999986, 110, 65541, 9, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_MOVE1",
    -250000000, 0, -250000000, 65545, 5, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_3RD1_MOVE2", -250000000, 0, -250000000, 65545, 5, 6, 112,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_2", 65541, 9, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 10, 131125, -29999998, 1, 983131, (s32)evt_eff, (s32)"",
    (s32)"kemuri_test", 0, -30000000, -29999999, -29999998, -229999488, 10, 0,
    0, 0, 0, 0, 0, 65545, 10, 6,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 10, 983131, (s32)evt_eff, (s32)"",
    (s32)"kemuri_test", 0, -30000000, -29999999, -29999998, -229999488, 10, 0,
    0, 0, 0, 0, 0, 65647, -29999985, 65541,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_MOVE3", -250000000, 0, -250000000,
    65545, 5, 6, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 90, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0,
    -1, 0, 65631, -29999985, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    10, 131125, -29999998, 1, 2, 1,
};

static EVT_BEGIN(attack_common_event2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_1"))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(7.0f))
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    131122, -29999991, (s32)weapon_gundan_zako_attack, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 33, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    65630, (s32)attack_common_event1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_ATTACK1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3", 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 20, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229995904, -229999796,
    110, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0,
    0, 112, 65541, 0, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -29999990, -250000000, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -250000000,
    -250000000, 131096, -29999986, -1, 131100, -30000000, -29999990, 7,
    33, 32, 131101, -30000000, -29999990, 7, 33, 33,
    65545, 1, 6, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 0, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 65539, 90, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_3RD1_MISS1", -250000000, 0, -250000000, 131163, (s32)btlevtcmd_JumpContinue, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_2", 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229999488, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 1, 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_3", 65545, 10, 65540, 98,
    65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0,
    -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 48,
    327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229997952, -229999898, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 0, 0, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_3RD1_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"J_1B", 65545, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 65545, 20, 65540, 98, 65539, 98, 65630,
    (s32)attack_common_event2, 2, 1,
};

static s32 jump_attack_event[] = {
    131122, -29999991, (s32)weapon_gundan_zako_jump_attack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997,
    -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16,
    -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33,
    65540, 99, 33, 65630, (s32)attack_common_event1, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_ATTACK2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    10, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229998208, -229999796, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0, 0, 196699,
    (s32)evt_btl_camera_nomove_y_onoff, 0, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 0, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue,
    -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_MISS1", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131, (s32)evt_eff64,
    (s32)"", (s32)"kemuri1_n64", 4, -30000000, -29999999, -29999998, 0, 0,
    0, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"D_2", 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229999488, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 1, 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_3", 65545, 10, 65540, 98,
    65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 131163, (s32)btlevtcmd_JumpContinue,
    -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_ATTACK3", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131, (s32)evt_eff64,
    (s32)"", (s32)"kemuri1_n64", 4, -30000000, -29999999, -29999998, 0, 0,
    0, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 10, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229999488,
    -229999693, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0,
    0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 5, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, -229999488, -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    0, -29999998, 0, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    3, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229999488, -229999898, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0, 0, 65545,
    15, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65545, 10,
    65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65630, (s32)attack_common_event2, 2, 1,
};

static s32 dekadeka_event[] = {
    131122, -29999997, -2, 131122, -29999996, 1, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_gundan_zako_dekadeka_bottle, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_gundan_zako_dekadeka_bottle, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 300, 65545, 60, 110, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_3RD1_BOTTLE1", -250000000, 0, -250000000, 65545, 40, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_BOTTLE2", -250000000, 0, -250000000, 112, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4A", 65545, 80, 110, 65545,
    10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_BOTTLE3", -250000000, 0, -250000000,
    65545, 30, 65541, 3, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_BOTTLE4",
    -250000000, 0, -250000000, 65545, 20, 6, 112, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4B", 65545, 120, 107, 65545,
    5, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_3RD1_BOTTLE5\0\0\0", -250000000, 0, -250000000,
    65545, 55, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 109, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_gundan_zako_dekadeka_bottle, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)weapon_gundan_zako_dekadeka_bottle, 256, -29999995, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

