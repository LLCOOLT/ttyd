#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetOverTurnCount);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseDirect[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeDataTable[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_ChangeKind[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetHpDamageCount[];
extern s32 btlevtcmd_GetOverTurnCount[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OffStatusFlag[];
extern s32 btlevtcmd_OnStatusFlag[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ReplaceParts[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHitOffset[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsDefenceTable[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetUnitWork[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_nomove_y_onoff[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_patapata_negone_one_374;
__declspec(section ".data") s32 fd_patapata_neg_one_382[1];
__declspec(section ".data") s32 fd_patapata___local_PI_383[1];
__declspec(section ".data") s32 fd_patapata___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_patapata_one_negone_373;
__declspec(section ".data") s32 fd_patapata___local_PIO2_384[1];
__declspec(section ".data") s32 fd_patapata_one_381[1];
__declspec(section ".data") u64 fd_patapata_negone_one_360;
__declspec(section ".data") s32 fd_patapata_neg_one_365[1];
__declspec(section ".data") s32 fd_patapata___local_PI_366[1];
__declspec(section ".data") s32 fd_patapata___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_patapata_one_negone_359;
__declspec(section ".data") s32 fd_patapata___local_PIO2_367[1];
__declspec(section ".data") s32 fd_patapata_one_364[1];
BattleUnitKind unit_patapata_26_data_29498;
static s32 weapon_patapata_attack[48];
static __declspec(section ".data") BattleUnitDefense defence_patapata;
static __declspec(section ".data") BattleUnitDefenseAttr defence_patapata_attr;
static __declspec(section ".data") StatusVulnerability regist_patapata;
static BattleUnitKindPart parts_patapata[1];
static PoseTableEntry pose_table_patapata[18];
static __declspec(section ".data") BattleDataEntry data_table_patapata[3];
static s32 pose_sound_timing_table[40];
static s32 init_event_patapata[26];
static s32 dmg_fall_event[189];
static s32 patapata_dmg_first_attack_pos[19];
static s32 attack_event_patapata[541];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_turn[17];
static __declspec(section ".data") s32 data_table[6];
static __declspec(section ".data") s32 defence[2];
static __declspec(section ".data") s32 defence_attr[2];
static __declspec(section ".data") s32 defence_turn[2];
static __declspec(section ".data") s32 regist[6];
static s32 parts[19];
static s32 weapon_nokonoko_attack[48];
static s32 init_event[41];
static __declspec(section ".data") s32 damage_event[10];
static s32 dmg_turn_event[78];
static s32 wakeup_event[88];
static s32 first_attack_event[302];
static s32 attack_event[548];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_patapata_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_patapata_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_patapata___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_patapata___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_patapata_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_patapata___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_patapata_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_patapata_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_patapata_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_patapata___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_patapata___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_patapata_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_patapata___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_patapata_one_364[] = {
    1065353216,
};

BattleUnitKind unit_patapata_26_data_29498 = {
    15,
    "btl_un_patapata",
    4,
    0,
    1,
    1,
    9,
    0,
    0,
    70,
    1,
    60,
    9999,
    36,
    40,
    -4,
    40,
    0.0f,
    24.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    9.0f,
    6.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    11.0f,
    24.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    36.0f,
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
    "SFX_ENM_PATA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x40004,
    &regist_patapata,
    1,
    parts_patapata,
    init_event_patapata,
    data_table_patapata,
};

static s32 weapon_patapata_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 20615, 0, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence_patapata = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_patapata_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_patapata = {95, 100, 120, 100, 90, 100, 100, 90, 100, 95, 100, 95, 100, 95, 90, 95, 110, 100, 90, 100, 100, 100};

static BattleUnitKindPart parts_patapata[] = {
    {1, "btl_un_patapata", "c_nokoteki", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence_patapata, &defence_patapata_attr, 0x600809, 0, pose_table_patapata},
};

static PoseTableEntry pose_table_patapata[] = {
    {1, "PTP_N_1"},
    {2, "PTP_Y_1"},
    {9, "PTP_Y_1"},
    {5, "PTP_K_1"},
    {4, "PTP_X_1"},
    {3, "PTP_X_1"},
    {28, "PTP_S_1"},
    {29, "PTP_Q_1"},
    {30, "PTP_Q_1"},
    {31, "PTP_S_1"},
    {39, "PTP_D_1"},
    {50, "PTP_A_1"},
    {42, "PTP_R_1"},
    {40, "PTP_W_1"},
    {56, "PTP_X_1"},
    {57, "PTP_X_1"},
    {65, "PTP_T_1"},
    {69, "PTP_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table_patapata[] = {
    {14, dmg_fall_event},
    {48, patapata_dmg_first_attack_pos},
    {0, NULL},
};

static s32 pose_sound_timing_table[] = {
    (s32)"PTP_S_1", 1008981770, 0, (s32)"SFX_ENM_PATA_WAIT1", 1, (s32)"PTP_W_1", 1008981770, 0,
    (s32)"SFX_ENM_PATA_MOVE1", 1, (s32)"PTP_R_1", 1008981770, 0, (s32)"SFX_ENM_PATA_MOVE1", 1, (s32)"PTP_N_1",
    1008981770, 0, (s32)"SFX_ENM_PATA_WAIT1", 1, (s32)"PTP_K_1", 1008981770, 0, (s32)"SFX_ENM_PATA_WAIT1",
    1, (s32)"PTP_A_3", 1008981770, 0, (s32)"SFX_ENM_PATA_WAIT1", 1, (s32)"PTP_X_1", 1008981770,
    0, (s32)"SFX_ENM_PATA_WAIT1", 1, 0, 0, 0, 0, 1,
};

static EVT_BEGIN(init_event_patapata)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_patapata))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event_patapata))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dmg_fall_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_OffAttribute,
    -29999990, 4, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, -29999989, 2048, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 39, 65546, 500, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -29999990, -29999989, (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table, 327771,
    (s32)btlevtcmd_ReplaceParts, -29999990, -29999989, (s32)parts, 1, 262235, (s32)btlevtcmd_AnimeChangePoseDirect, -29999990,
    -29999989, (s32)"NKT_D_1", 196699, (s32)btlevtcmd_ChangeKind, -29999990, 14, 196699, (s32)btlevtcmd_OnUnitFlag,
    -29999990, 4, 131122, -29999989, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990,
    -29999989, 39, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FALL1", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 131122,
    -29999999, 0, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229998976, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -30000000, -29999999, -29999998, 10, -1, 327771, (s32)btlevtcmd_SetHomePos,
    -29999990, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHpDamageCount, -29999990, -30000000,
    131100, -30000000, 1, 65545, 30, 196699, (s32)btlevtcmd_SetEventWait, -2,
    (s32)wait_event, 196699, (s32)btlevtcmd_SetEventAttack, -2, (s32)attack_event, 196699, (s32)btlevtcmd_SetEventDamage, -2,
    (s32)damage_event, 196699, (s32)btlevtcmd_SetEventConfusion, -2, (s32)attack_event, 458843, (s32)btlevtcmd_SetRunSound, -2,
    (s32)"SFX_ENM_NOKO_MOVE3L", (s32)"SFX_ENM_NOKO_MOVE3R", 0, 3, 3, 458843, (s32)btlevtcmd_SetWalkSound, -2,
    (s32)"SFX_ENM_NOKO_MOVE3L", (s32)"SFX_ENM_NOKO_MOVE3L", 0, 6, 6, 196699, (s32)btlevtcmd_SetOverTurnCount, -2,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 39, 2, 33,
    196699, (s32)btlevtcmd_SetEventWait, -2, (s32)wait_event, 196699, (s32)btlevtcmd_SetEventAttack, -2, (s32)attack_event,
    196699, (s32)btlevtcmd_SetEventDamage, -2, (s32)damage_event, 196699, (s32)btlevtcmd_SetEventConfusion, -2, (s32)attack_event,
    458843, (s32)btlevtcmd_SetRunSound, -2, (s32)"SFX_ENM_NOKO_MOVE3L", (s32)"SFX_ENM_NOKO_MOVE3R", 0, 3, 3,
    458843, (s32)btlevtcmd_SetWalkSound, -2, (s32)"SFX_ENM_NOKO_MOVE3L", (s32)"SFX_ENM_NOKO_MOVE3L", 0, 6, 6,
    196699, (s32)btlevtcmd_SetOverTurnCount, -2, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989,
    39, 65630, (s32)dmg_turn_event, 2, 1,
};

static EVT_BEGIN(patapata_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static s32 attack_event_patapata[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 65545, 50, 32, 196699, (s32)btlevtcmd_EnemyItemUseCheck,
    -2, -30000000, 131097, -30000000, 0, 65630, -30000000, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_patapata_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_patapata_attack,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_patapata_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_patapata_attack, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 45, 131125, -29999999, 30,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996416,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0, -16,
    0, 0, -1, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)evt_btl_camera_nomove_y_onoff, 0, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PATA_MOVE2", -250000000,
    0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229998976, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PTP_A_1", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 6, 131125, -29999999,
    6, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0,
    0, 0, 0, 0, 65545, 11, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PATA_MOVE3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PTP_A_4", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999999, 20, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_patapata_attack, 1048832, -29999995,
    32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_patapata_attack, 256,
    -29999995, 33, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229994880, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0,
    0, 0, 0, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    25, 131122, -29999999, 20, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 0, 0, 0, 0, 0, 65540,
    98, 65539, 91, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50,
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_patapata_attack,
    131097, -30000000, 0, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)weapon_patapata_attack, 1048832, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_patapata_attack, 256, -29999995, 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_PATA_ATTACK1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 131125,
    -29999999, 30, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 107, 131122,
    -30000000, 0, 65541, 24, 131126, -30000000, 45, 131098,
    -30000000, 0, 131125, -30000000, 360, 33, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, -30000000, 65545, 1, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 65545, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131126, -29999999, 20, 327771, (s32)btlevtcmd_SetPos, -2,
    -30000000, -29999999, -29999998, 109, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 0, 30, 0, 0, 0, 65545,
    10, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0, -10,
    0, 0, -1, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static PoseTableEntry pose_table[] = {
    {1, "NKT_N_1"},
    {2, "NKT_Y_1"},
    {9, "NKT_Y_1"},
    {5, "NKT_K_1"},
    {4, "NKT_X_1"},
    {3, "NKT_X_1"},
    {28, "NKT_S_1"},
    {29, "NKT_Q_1"},
    {30, "NKT_Q_1"},
    {31, "NKT_S_1"},
    {39, "NKT_D_1"},
    {50, "NKT_A_1"},
    {42, "NKT_R_1"},
    {40, "NKT_W_1"},
    {56, "NKT_X_1"},
    {57, "NKT_X_1"},
    {65, "NKT_T_1"},
    {69, "NKT_S_1"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "NKT_N_2"},
    {2, "NKT_B_1"},
    {9, "NKT_B_1"},
    {5, "NKT_K_2"},
    {4, "NKT_K_2"},
    {3, "NKT_K_2"},
    {28, "NKT_S_2"},
    {29, "NKT_Q_1"},
    {30, "NKT_Q_1"},
    {31, "NKT_D_1"},
    {39, "NKT_D_1"},
    {42, "NKT_R_1"},
    {40, "NKT_W_1"},
    {56, "NKT_K_2"},
    {57, "NKT_K_2"},
    {65, "NKT_S_2"},
    {69, "NKT_S_2"},
};

static __declspec(section ".data") s32 data_table[] = {
    13, (s32)dmg_turn_event, 48, (s32)btldefaultevt_Dummy, 0, 0,
};

static __declspec(section ".data") s32 defence[] = {
    16843009, 16777216,
};

static __declspec(section ".data") s32 defence_attr[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_turn[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist[] = {
    1600412260, 1516528730, 1683973215, 1683970655, 1516526180, 1684275200,
};

static s32 parts[] = {
    1, (s32)"btl_un_nokonoko", (s32)"c_nokoteki", 0, 0, 0, 0, 1106247680,
    0, 0, 1109393408, 0, 1310750, 16711680, (s32)defence, (s32)defence_attr,
    4105, 0, (s32)pose_table,
};

static s32 weapon_nokonoko_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 525058, 0, 135, 1535, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetOverTurnCount, -2, 0)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dmg_turn_event[] = {
    393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, -15, 0, 131122,
    -29999990, -2, 131122, -29999989, 1, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990,
    -29999989, (s32)defence_turn, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_turn, 196699,
    (s32)btlevtcmd_OnStatusFlag, -29999990, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"NKT_D_1", 65545, 2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_INSIDE1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 15, -1, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 10, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"NKT_S_2", 2, 1,
};

static s32 wakeup_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_GetOverTurnCount,
    -29999990, -30000000, 131126, -30000000, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990,
    -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"NKT_S_3", 65546, 400, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33,
    262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)defence, 196699, (s32)btlevtcmd_OffStatusFlag, -29999990,
    1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999990, -29999989, (s32)"NKT_S_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE2", -250000000,
    0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 393307, (s32)btlevtcmd_SetHitOffset, -2, 1,
    0, 0, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 first_attack_event[] = {
    196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_nokonoko_attack, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_JUMP1", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_NOKO_SHELL1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"NKT_A_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_MOVE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 0, 110, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -29999985, 131096, -29999985, 1, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 7, 33, 65545, 1, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 1, -29999986, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    -29999986, 0, 6, 112, 65546, 100, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 1, 20, 65546, 100, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 40, 65546, 100, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229991808,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_GetPos, -2, -250000000, -29999995, -250000000, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999995, -29999998, 0, 0, 1, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_nokonoko_attack, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, (s32)weapon_nokonoko_attack, 256, -29999995, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 1, 10, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -229996928,
    -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_MOVE2",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -229999488,
    -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 75, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_MOVE2",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_GetOverTurnCount, -2, -30000000, 131101, -30000000, 1, 65630,
    (s32)wakeup_event, 2, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 65545, 30,
    32, 196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0,
    65630, -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_nokonoko_attack,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_nokonoko_attack, -29999997, -29999996, 33, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_nokonoko_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_nokonoko_attack, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 100, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_NOKO_JUMP1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20,
    -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_SHELL1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"NKT_A_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_MOVE1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0, 110, 65541, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999985, 131096, -29999985, 1,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 7, 33,
    65545, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999986, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, -29999986, 0, 6, 112, 65546,
    100, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 20, 65546, 100,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 40, 65546, 100, 65647,
    -29999987, 65541, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 10, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test",
    0, -30000000, -29999999, -29999998, -229999693, 0, 0, 0,
    0, 0, 0, 0, 65545, 3, 6, 112,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999995,
    -250000000, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999995, -29999998, 0,
    0, 1, 65631, -29999987, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_nokonoko_attack, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 100, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, 0, -29999998, 0, 0, 1, 65546, 250,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 10, 65546, 250, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_NOKO_JUMP1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -229989760, -229999591, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    40, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20,
    -1, 65540, 98, 65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0,
    1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_add_zoom, 0, -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_nokonoko_attack,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_nokonoko_attack, 256, -29999995,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 10, 327771, (s32)btlevtcmd_JumpSetting, -2,
    20, -229996928, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_NOKO_MOVE2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2,
    20, -229999488, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 75, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_NOKO_MOVE2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 1, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

