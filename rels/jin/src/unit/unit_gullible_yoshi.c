#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "unit/party/unit_party_yoshi.h"

#pragma force_active on

USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(yoshi_original_color_anim_set);

__declspec(section ".data") u64 fd_gullible_yoshi_negone_one_374;
__declspec(section ".data") s32 fd_gullible_yoshi_neg_one_382[1];
__declspec(section ".data") s32 fd_gullible_yoshi___local_PI_383[1];
__declspec(section ".data") s32 fd_gullible_yoshi___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gullible_yoshi_one_negone_373;
__declspec(section ".data") s32 fd_gullible_yoshi___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gullible_yoshi_one_381[1];
__declspec(section ".data") u64 fd_gullible_yoshi_negone_one_360;
__declspec(section ".data") s32 fd_gullible_yoshi_neg_one_365[1];
__declspec(section ".data") s32 fd_gullible_yoshi___local_PI_366[1];
__declspec(section ".data") s32 fd_gullible_yoshi___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gullible_yoshi_one_negone_359;
__declspec(section ".data") s32 fd_gullible_yoshi___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gullible_yoshi_one_364[1];
BattleUnitKind unit_gullible_yoshi;
static s32 enemyWeapon_YoshiNormalAttack[48];
static __declspec(section ".data") BattleUnitDefense defence_yoshi;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_yoshi;
static __declspec(section ".data") StatusVulnerability regist_yoshi;
static __declspec(section ".data") BattleDataEntry data_table_yoshi[2];
static BattleUnitKindPart parts_yoshi[1];
static s32 init_event_yoshi[24];
s32 damage_event_yoshi[22];
static s32 dead_event_yoshi[177];
static s32 attack_event_yoshi[748];
static __declspec(section ".data") s32 wait_event_yoshi[7];

__declspec(section ".data") u64 fd_gullible_yoshi_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_yoshi_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_yoshi___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_yoshi___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_yoshi_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_yoshi___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_yoshi_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gullible_yoshi_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_yoshi_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_yoshi___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_yoshi___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_yoshi_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_yoshi___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_yoshi_one_364[] = {
    1065353216,
};

BattleUnitKind unit_gullible_yoshi = {
    82,
    "btl_un_gullible_yoshi",
    10,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    9,
    24,
    28,
    4,
    24,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
    18.2f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    24.0f,
    28.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_PARTY_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x10000000,
    &regist_yoshi,
    1,
    parts_yoshi,
    init_event_yoshi,
    data_table_yoshi,
};

static s32 enemyWeapon_YoshiNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 86167, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence_yoshi = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_yoshi = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_yoshi = {60, 80, 70, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 90, 70, 0, 0, 100, 70, 100, 100, 0};

static __declspec(section ".data") BattleDataEntry data_table_yoshi[] = {
    {49, dead_event_yoshi},
    {0, NULL},
};

static BattleUnitKindPart parts_yoshi[] = {
    {1, "btl_un_yoshi", "c_babyyoshi", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_yoshi, &defence_attr_yoshi, 0x9, 0, pose_table_yoshi_stay},
};

static EVT_BEGIN(init_event_yoshi)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_yoshi))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_yoshi))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_yoshi))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(yoshi_original_color_anim_set, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(damage_event_yoshi)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(20), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event_yoshi[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 65545,
    1, 65627, (s32)btlevtcmd_WaitAttackEnd, 65570, -49999981, 65572, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto, 0, 130, 58,
    228, 130, 38, -20, 30, 11, 65545, 37,
    327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_03_yos", 0, -2, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0, 3,
    655451, (s32)evt_btl_camera_set_moveto, 0, 90, 58, 228, 90, 38,
    -20, 30, 11, 65545, 37, 327771, (s32)evt_msg_print, 2,
    (s32)"stg4_jin_26_04", 0, -49999984, 65546, 200, 65572, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 65541, 0, 131096, -49999981, 2,
    7, 33, 65545, 1, 6, 65572, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 49, 196699, (s32)btlevtcmd_KillUnit, -2, 1,
    131122, -49999980, 2, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2,
    1,
};

static s32 attack_event_yoshi[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_YoshiNormalAttack, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 65545, 20,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 350, 65644, -29999987, 65541, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 0, -250000000, 65545, 2,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 0, -250000000, 65545,
    3, 6, 109, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_R_5",
    65545, 25, 65631, -29999987, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_J_1A", 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999693, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 25, 131125, -29999999, 35, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_JUMP1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 25, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PYS_A_3", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994,
    -29999993, -29999992, 131125, -29999993, 40, 131122, -29999990, -229998976,
    65644, -29999987, 65541, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L",
    -250000000, 190, -250000000, 65545, 6, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 381, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 668, -250000000, 65545, 6, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 859, -250000000, 65545, 7,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 1145, -250000000, 65545,
    6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 1241, -250000000,
    65545, 7, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 1527,
    -250000000, 65545, 6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000,
    1814, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1L",
    -250000000, 2100, -250000000, 65545, 6, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 2196, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_PARTY_BATTLE_MOVE1L", -250000000, 1742, -250000000, 65545, 6, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_MOVE1R", -250000000, 1527, -250000000, 65545, 7,
    6, 109, 458843, (s32)btl_yoshi_yoroyoro_jump_calc_param, -2, -29999994, -29999993, -29999992,
    -29999990, -29999991, 458843, (s32)btl_yoshi_yoroyoro_jump_move, -2, -29999994, -29999993, -29999992,
    -29999990, -29999991, 65631, -29999987, 196699, (s32)evt_sub_random, 4, -29999989,
    131125, -29999989, 1, 131122, -29999990, 0, 65539, 10,
    131101, -29999990, 1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 1048832, -29999995, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 33, 65570, -29999995, 65579,
    2, 65579, 3, 65579, 6, 65579, 4, 46,
    65572, 1, 42, 49, 131100, -29999990, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_A_2B", 65545, 20, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 131096, -29999990, 0, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_J_1B",
    131122, -30000000, 1, 131122, -29999999, 9, 131127, -29999985,
    -40, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 12, 0, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65545, 15, 65541,
    -30000000, 131122, -29999998, -29999999, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_YOSHI_ATTACK1",
    -250000000, 0, -250000000, 65541, -29999998, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -29999985, 65545, 1, 6, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_1",
    65545, 15, 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_1",
    33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 4, 0,
    0, 0, -1, 131097, -29999995, 1, 131096, -29999995,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131122, -29999985, -29999999, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 131126, -29999985, -29999999, 131128,
    -29999985, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    -29999985, 0, 0, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PYS_D_1", 327771, (s32)btlevtcmd_SetDispOffset, -2, 0, -7, 0,
    393307, (s32)evt_btl_camera_shake_h, 0, 4, 0, 10, 13, 65545,
    40, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_A_5", 327771, (s32)btlevtcmd_SetDispOffset,
    -2, 0, 0, 0, 65545, 54, 65540, 95,
    33, 131098, -29999990, -29999989, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 0, -29999995,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999796, 131125, -29999999, 40, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 131125, -29999990, 1,
    65540, 10, 32, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995, 33,
    65539, 90, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PYS_D_1", 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    25, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 16,
    -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 20,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") s32 wait_event_yoshi[] = {
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 2, 1, 0,
};

