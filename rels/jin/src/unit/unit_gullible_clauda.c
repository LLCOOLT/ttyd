#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_SetDiveSound);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetScale[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_msg_print[];
extern s32 evt_sub_intpl_get_float[];
extern s32 evt_sub_intpl_init_float[];
extern s32 evt_sub_random[];
extern s32 pose_table_clauda_stay[];
extern s32 weaponGetPowerFromGulliblePartyAttackLv[];

__declspec(section ".data") u64 fd_gullible_clauda_negone_one_374;
__declspec(section ".data") s32 fd_gullible_clauda_neg_one_382[1];
__declspec(section ".data") s32 fd_gullible_clauda___local_PI_383[1];
__declspec(section ".data") s32 fd_gullible_clauda___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gullible_clauda_one_negone_373;
__declspec(section ".data") s32 fd_gullible_clauda___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gullible_clauda_one_381[1];
__declspec(section ".data") u64 fd_gullible_clauda_negone_one_360;
__declspec(section ".data") s32 fd_gullible_clauda_neg_one_365[1];
__declspec(section ".data") s32 fd_gullible_clauda___local_PI_366[1];
__declspec(section ".data") s32 fd_gullible_clauda___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gullible_clauda_one_negone_359;
__declspec(section ".data") s32 fd_gullible_clauda___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gullible_clauda_one_364[1];
BattleUnitKind unit_gullible_clauda;
static s32 enemyWeapon_ClaudaNormalAttack[48];
static __declspec(section ".data") BattleUnitDefense defence_clauda;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_clauda;
static __declspec(section ".data") StatusVulnerability regist_clauda;
static __declspec(section ".data") BattleDataEntry data_table_clauda[2];
static BattleUnitKindPart parts_clauda[1];
static s32 init_event_clauda[50];
s32 damage_event_clauda[22];
static s32 dead_event_clauda[177];
static s32 attack_event_clauda[393];
static __declspec(section ".data") s32 wait_event_clauda[6];

__declspec(section ".data") u64 fd_gullible_clauda_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_clauda_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_clauda___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_clauda___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_clauda_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_clauda___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_clauda_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gullible_clauda_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_clauda_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_clauda___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_clauda___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_clauda_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_clauda___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_clauda_one_364[] = {
    1065353216,
};

BattleUnitKind unit_gullible_clauda = {
    83,
    "btl_un_gullible_clauda",
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
    42,
    46,
    12,
    40,
    0.0f,
    23.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    21.0f,
    29.9f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    42.0f,
    46.0f,
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
    &regist_clauda,
    1,
    parts_clauda,
    init_event_clauda,
    data_table_clauda,
};

static s32 enemyWeapon_ClaudaNormalAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 4, 6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 656130, 0, 82055, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence_clauda = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_clauda = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_clauda = {60, 80, 105, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 90, 70, 0, 0, 100, 70, 100, 100, 0};

static __declspec(section ".data") BattleDataEntry data_table_clauda[] = {
    {49, dead_event_clauda},
    {0, NULL},
};

static BattleUnitKindPart parts_clauda[] = {
    {1, "btl_un_clauda", "c_windy", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_clauda, &defence_attr_clauda, 0x9, 0, pose_table_clauda_stay},
};

static EVT_BEGIN(init_event_clauda)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_clauda))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_clauda))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_clauda))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 3)
    CALL(btlevtcmd_SetDiveSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(damage_event_clauda)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(20), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event_clauda[] = {
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
    327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_03_win", 0, -2, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PWD_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0, 3,
    655451, (s32)evt_btl_camera_set_moveto, 0, 90, 58, 228, 90, 38,
    -20, 30, 11, 65545, 37, 327771, (s32)evt_msg_print, 2,
    (s32)"stg4_jin_26_04", 0, -49999984, 65546, 200, 65572, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 65541, 0, 131096, -49999981, 2,
    7, 33, 65545, 1, 6, 65572, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 49, 196699, (s32)btlevtcmd_KillUnit, -2, 1,
    131122, -49999980, 2, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2,
    1,
};

static s32 attack_event_clauda[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_ClaudaNormalAttack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1,
    -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 400,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_CLAUD_ATTACK1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999796,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 131163, (s32)btlevtcmd_GetResultAC, -29999995, 131103, -29999995, 2,
    196699, (s32)evt_sub_random, 40, -29999995, 131126, -29999995, 20, 131125,
    -30000000, -29999995, 196699, (s32)evt_sub_random, 20, -29999995, 131126, -29999995,
    10, 131125, -29999999, -29999995, 33, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 60, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999994, 131097, -29999994, 1,
    131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33,
    131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33,
    131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_A1_2", 131163, (s32)btlevtcmd_JumpContinue, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PWD_D_3", 65545, 30, 65540,
    95, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_CLAUD_ATTACK2", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 131163, (s32)btlevtcmd_JumpContinue, -2,
    393307, (s32)evt_btl_camera_shake_h, 0, 8, 0, 30, 13, 65647,
    -29999985, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976, -229999591, 10, 65541,
    10, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229999591,
    -229998976, 6, 65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -30000000, -29999995, -29999998, 65545, 1, 6, 112,
    110, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976, -229998464, 10, 65541,
    10, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464,
    -229998976, 6, 65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -29999995, -29999999, -29999998, 65545, 1, 6, 112,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65546, 700, 65539, 95, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 65539,
    99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_clauda)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

