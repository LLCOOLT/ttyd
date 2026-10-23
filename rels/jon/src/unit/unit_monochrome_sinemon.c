#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetOverTurnCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);

__declspec(section ".data") u64 fd_monochrome_sinemon_negone_one_374;
__declspec(section ".data") s32 fd_monochrome_sinemon_neg_one_382[1];
__declspec(section ".data") s32 fd_monochrome_sinemon___local_PI_383[1];
__declspec(section ".data") s32 fd_monochrome_sinemon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_monochrome_sinemon_one_negone_373;
__declspec(section ".data") s32 fd_monochrome_sinemon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_monochrome_sinemon_one_381[1];
__declspec(section ".data") u64 fd_monochrome_sinemon_negone_one_360;
__declspec(section ".data") s32 fd_monochrome_sinemon_neg_one_365[1];
__declspec(section ".data") s32 fd_monochrome_sinemon___local_PI_366[1];
__declspec(section ".data") s32 fd_monochrome_sinemon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_monochrome_sinemon_one_negone_359;
__declspec(section ".data") s32 fd_monochrome_sinemon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_monochrome_sinemon_one_364[1];
BattleUnitKind unit_monochrome_sinemon;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") s32 defence_turn[2];
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_sinemon_attack[48];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_turn[15];
static __declspec(section ".data") BattleDataEntry data_table[4];
static s32 init_event[42];
static s32 dmg_avoid_counter_thorn_head_event[76];
static s32 damage_event[58];
static s32 dmg_turn_event[96];
static s32 wakeup_event[104];
static s32 attack_event[454];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_monochrome_sinemon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_monochrome_sinemon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_monochrome_sinemon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_monochrome_sinemon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_monochrome_sinemon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_monochrome_sinemon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_monochrome_sinemon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_monochrome_sinemon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_monochrome_sinemon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_monochrome_sinemon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_monochrome_sinemon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_monochrome_sinemon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_monochrome_sinemon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_monochrome_sinemon_one_364[] = {
    1065353216,
};

BattleUnitKind unit_monochrome_sinemon = {
    26,
    "btl_un_monochrome_sinemon",
    2,
    0,
    1,
    1,
    12,
    0,
    2,
    70,
    1,
    70,
    9999,
    26,
    32,
    4,
    32,
    0.0f,
    16.0f,
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
    10.0f,
    24.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    26.0f,
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
    "SFX_ENM_EMON_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x40000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{2, 99, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 2, 0, 0, 0}};

static __declspec(section ".data") s32 defence_turn[] = {
    0, 0,
};

static __declspec(section ".data") StatusVulnerability regist = {50, 100, 50, 100, 50, 100, 0, 70, 100, 70, 100, 70, 100, 100, 70, 50, 70, 100, 70, 100, 100, 95};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_monochrome_sinemon", "c_sinemon_w", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2009, 0x1, pose_table},
};

static s32 weapon_sinemon_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 30, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "SIN_N_1"},
    {2, "SIN_Y_1"},
    {9, "SIN_Y_1"},
    {5, "SIN_K_1"},
    {4, "SIN_I_1"},
    {3, "SIN_I_1"},
    {28, "SIN_S_1"},
    {29, "SIN_Q_1"},
    {30, "SIN_Q_1"},
    {31, "SIN_A_1a"},
    {39, "SIN_D_1"},
    {50, "SIN_A_1a"},
    {40, "SIN_W_1"},
    {42, "SIN_R_1"},
    {56, "SIN_I_1"},
    {57, "SIN_I_1"},
    {65, "SIN_T_1"},
    {69, "SIN_S_1"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "SIN_N_2"},
    {2, "SIN_Y_2"},
    {9, "SIN_Y_2"},
    {5, "SIN_K_2"},
    {4, "SIN_K_2"},
    {3, "SIN_K_2"},
    {28, "SIN_D_2"},
    {29, "SIN_D_2"},
    {30, "SIN_D_2"},
    {31, "SIN_D_2"},
    {39, "SIN_D_2"},
    {56, "SIN_K_2"},
    {57, "SIN_K_2"},
    {65, "SIN_D_2"},
    {69, "SIN_D_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_EMON_MOVE1"), STRING("SFX_ENM_EMON_MOVE2"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_EMON_MOVE1"), STRING("SFX_ENM_EMON_MOVE2"), 0, 7, 7)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_ENM_EMON_JUMP1"), STRING("SFX_ENM_EMON_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 15)
        ADD(LW(1), 45)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 7)
        ADD(LW(1), 25)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 10)
    ADD(LW(1), 35)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_GetDamage, -2, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(15), 1)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("SIN_D_1"))
    END_IF
    CALL(btlevtcmd_GetOverTurnCount, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("SIN_D_2"))
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 10, -1)
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 5, -1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dmg_turn_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -29999990, -29999989, (s32)defence_turn, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_turn,
    196699, (s32)btlevtcmd_OnStatusFlag, -29999990, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 2,
    65545, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"SIN_D_2", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 15, -1,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 10, -1,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos,
    -2, -30000000, 7, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000,
    7, -29999998, 393307, (s32)btlevtcmd_SetHitOffset, -29999990, -29999989, 0, -10,
    0, 262235, (s32)btlevtcmd_OffPartsCounterAttribute, -2, 1, 1, 2, 1,
};

static s32 wakeup_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_GetOverTurnCount,
    -29999990, -30000000, 131126, -30000000, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990,
    -30000000, 131097, -30000000, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    33, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)&defence, 196699, (s32)btlevtcmd_OffStatusFlag,
    -29999990, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"SIN_S_1", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, 0, -29999998,
    327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 0, -29999998, 393307, (s32)btlevtcmd_SetHitOffset,
    -29999990, -29999989, 0, 0, 0, 262235, (s32)btlevtcmd_OnPartsCounterAttribute, -2,
    1, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE2", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 12, -1, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_GetOverTurnCount, -2, -30000000, 131101, -30000000, 1, 65630,
    (s32)wakeup_event, 2, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_mode,
    0, 8, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 3, 65546, 800,
    32, 196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0,
    65630, -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_sinemon_attack,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_sinemon_attack, -29999997, -29999996, 33, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_sinemon_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_sinemon_attack, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 100, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0, -1, 1,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65647, -29999985, 65541, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_EMON_MOVE1", -250000000, 0, -250000000, 65545,
    7, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_EMON_MOVE2", -250000000, 0, -250000000,
    65545, 7, 6, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_EMON_MOVE3",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    65546, 750, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_EMON_DASH1\0", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999995, -250000000, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999995, -29999998, 0, -1, 0, 65631,
    -29999985, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_sinemon_attack, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 50, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998,
    0, -1, 0, 65546, 500, 65540, 98, 65539,
    91, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_sinemon_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_sinemon_attack, 256, -29999995, 327771, (s32)btlevtcmd_JumpSetting, -2, 20,
    -229998976, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 75, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_EMON_MOVE1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20,
    -229999488, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 100, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_EMON_MOVE2", -250000000, 0, -250000000, 65540, 98, 65539, 98,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

