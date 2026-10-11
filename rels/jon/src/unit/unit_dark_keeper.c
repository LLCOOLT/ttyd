#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_random);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_JumpPartsContinue[];
extern s32 btlevtcmd_JumpPartsPosition[];
extern s32 btlevtcmd_JumpPartsSetting[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_dark_keeper_negone_one_374;
__declspec(section ".data") s32 fd_dark_keeper_neg_one_382[1];
__declspec(section ".data") s32 fd_dark_keeper___local_PI_383[1];
__declspec(section ".data") s32 fd_dark_keeper___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_dark_keeper_one_negone_373;
__declspec(section ".data") s32 fd_dark_keeper___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dark_keeper_one_381[1];
__declspec(section ".data") u64 fd_dark_keeper_negone_one_360;
__declspec(section ".data") s32 fd_dark_keeper_neg_one_365[1];
__declspec(section ".data") s32 fd_dark_keeper___local_PI_366[1];
__declspec(section ".data") s32 fd_dark_keeper___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_dark_keeper_one_negone_359;
__declspec(section ".data") s32 fd_dark_keeper___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dark_keeper_one_364[1];
BattleUnitKind unit_dark_keeper_15_data_5E0F0;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
static s32 weapon_monban_attack[48];
static s32 weapon_monban_throw_attack[48];
static __declspec(section ".data") s32 pose_sound_timing_table[10];
static s32 init_event[46];
static s32 dmg_avoid_counter_thorn_head_event[76];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[52];
static s32 normal_attack_event[391];
static s32 throw_attack_event[343];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_dark_keeper_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dark_keeper_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dark_keeper___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dark_keeper___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dark_keeper_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dark_keeper___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dark_keeper_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dark_keeper_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dark_keeper_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dark_keeper___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dark_keeper___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dark_keeper_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dark_keeper___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dark_keeper_one_364[] = {
    1065353216,
};

BattleUnitKind unit_dark_keeper_15_data_5E0F0 = {
    55,
    "btl_un_dark_keeper",
    20,
    0,
    1,
    1,
    28,
    1,
    3,
    70,
    2,
    50,
    9999,
    31,
    46,
    0,
    46,
    0.0f,
    20.0f,
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
    15.5f,
    0.0f,
    0.0f,
    15.5f,
    29.9f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    28.0f,
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
    "SFX_ENM_MONBAN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {90, 80, 80, 100, 90, 100, 100, 70, 100, 90, 100, 90, 100, 95, 70, 0, 60, 100, 70, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_2"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_1"},
    {39, "D_1"},
    {50, "A_1"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_dark_keeper", "c_monban_t", 0.0f, 0.0f, 0.0f, 8.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
    {2, "btl_un_dark_keeper", "c_monban_t", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static s32 weapon_monban_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 2043, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_monban_throw_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 16519, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 pose_sound_timing_table[] = {
    (s32)"S_2", 1059760811, 0, (s32)"SFX_ENM_MONBAN_WAIT1", 1, 0, 0, 0,
    0, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_MONBAN_MOVE2R"), STRING("SFX_ENM_MONBAN_MOVE2L"), 0, 5, 5)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_MONBAN_MOVE2R"), STRING("SFX_ENM_MONBAN_MOVE2L"), 0, 10, 10)
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 18)
        ADD(LW(1), 60)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 10)
        ADD(LW(1), 33)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 14)
    ADD(LW(1), 48)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
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

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 50)
        SET_VALUE(LW(9), PTR(weapon_monban_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    SET_VALUE(LW(9), PTR(weapon_monban_throw_attack))
    CALL_CHILD(PTR(throw_attack_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_MOVE1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1", 65545, 20, 110, 65541,
    6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_MOVE2R", -250000000, 0, -250000000,
    65545, 5, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_MOVE2L", -250000000, 0,
    -250000000, 65545, 5, 6, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"R_2", 65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_MOVE3",
    -250000000, 0, -29999985, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131122, -29999995, 30, 196699, (s32)btlevtcmd_GetStatusMg, -2,
    -29999994, 131132, -29999995, -29999994, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    -29999995, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, 0, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 30, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 0, -1, 0, 65545, 60, 65540, 98,
    65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0,
    -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229998976, -229998976, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_MONBAN_MOVE2R", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 10, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229998976, -229998976,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_MOVE2L", -250000000, 0, -250000000, 65540,
    98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"T_1", 65541,
    3, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_LAUGH1", -250000000, 0, -29999985,
    65545, 10, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_2",
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static s32 throw_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_THROW1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 65545, 28, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_MONBAN_THROW2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    2, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 33554432, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"A_3", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 5, 131125,
    -29999999, 10, 393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, 2, 10, 0, 0,
    131096, -29999985, -1, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0,
    0, -45, 32, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0,
    180, -45, 33, 110, 65541, 30, 393307, (s32)btlevtcmd_AddPartsRotate,
    -2, 2, 0, 0, 3, 65545, 1, 6,
    112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 30, 0, -229999488, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, -29999999, -29999998, 30, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 0, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 196699, (s32)btlevtcmd_JumpPartsContinue, -2, 2,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    2, 33554432, 65540, 98, 65539, 91, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 2, 33554432, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65545, 2, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"T_1", 65541,
    3, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MONBAN_LAUGH1", -250000000, 0, -29999985,
    65545, 10, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_2",
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

