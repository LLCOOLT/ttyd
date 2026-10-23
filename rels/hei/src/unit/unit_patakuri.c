#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "system.h"
#include "manager/evtmgr_cmd.h"

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
static USER_FUNC(krb_get_dir);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
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
extern s32 btlevtcmd_GetPosFloat[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MoveDirectionAdd[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffAttribute[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ReplaceParts[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMoveSoundDataWork[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetRotate[];
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
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_patakuri_negone_one_374;
__declspec(section ".data") s32 fd_patakuri_neg_one_382[1];
__declspec(section ".data") s32 fd_patakuri___local_PI_383[1];
__declspec(section ".data") s32 fd_patakuri___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_patakuri_one_negone_373;
__declspec(section ".data") s32 fd_patakuri___local_PIO2_384[1];
__declspec(section ".data") s32 fd_patakuri_one_381[1];
__declspec(section ".data") u64 fd_patakuri_negone_one_360;
__declspec(section ".data") s32 fd_patakuri_neg_one_365[1];
__declspec(section ".data") s32 fd_patakuri___local_PI_366[1];
__declspec(section ".data") s32 fd_patakuri___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_patakuri_one_negone_359;
__declspec(section ".data") s32 fd_patakuri___local_PIO2_367[1];
__declspec(section ".data") s32 fd_patakuri_one_364[1];
BattleUnitKind unit_patakuri;
static __declspec(section ".data") BattleUnitDefense defence_patakuri;
static __declspec(section ".data") BattleUnitDefenseAttr defence_patakuri_attr;
static __declspec(section ".data") StatusVulnerability regist_patakuri;
static s32 weapon_patakuri_attack[48];
static BattleUnitKindPart parts_patakuri[1];
static PoseTableEntry pose_table_patakuri[19];
static __declspec(section ".data") BattleDataEntry data_table_patakuri[3];
static s32 pose_sound_timing_table[35];
static s32 init_event_patakuri[26];
static s32 dmg_fall_event[107];
static s32 patakuri_dmg_first_attack_pos[19];
static s32 attack_event_patakuri[391];
static __declspec(section ".data") s32 wait_event_patakuri[12];
static PoseTableEntry pose_table[20];
static __declspec(section ".data") s32 data_table[4];
static __declspec(section ".data") s32 defence[2];
static __declspec(section ".data") s32 defence_attr[2];
static __declspec(section ".data") s32 regist[6];
static s32 parts[19];
static s32 weapon_kuriboo_attack[48];
static s32 init_event[42];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[492];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_patakuri_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_patakuri_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_patakuri___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_patakuri___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_patakuri_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_patakuri___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_patakuri_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_patakuri_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_patakuri_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_patakuri___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_patakuri___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_patakuri_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_patakuri___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_patakuri_one_364[] = {
    1065353216,
};

BattleUnitKind unit_patakuri = {
    2,
    "btl_un_patakuri",
    2,
    0,
    1,
    1,
    7,
    0,
    1,
    60,
    0,
    60,
    9999,
    23,
    25,
    5,
    25,
    0.0f,
    12.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    11.5f,
    0.0f,
    0.0f,
    11.5f,
    16.25f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    23.0f,
    25.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_PATAKURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x40004,
    &regist_patakuri,
    1,
    parts_patakuri,
    init_event_patakuri,
    data_table_patakuri,
};

static __declspec(section ".data") BattleUnitDefense defence_patakuri = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_patakuri_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_patakuri = {100, 110, 120, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 110, 110, 100, 100, 100, 100, 150};

static s32 weapon_patakuri_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 20615, 0, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static BattleUnitKindPart parts_patakuri[] = {
    {1, "btl_un_patakuri", "c_kuribo", 0.0f, 0.0f, 0.0f, 0.0f, 22.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_patakuri, &defence_patakuri_attr, 0x600809, 0, pose_table_patakuri},
};

static PoseTableEntry pose_table_patakuri[] = {
    {1, "PTK_N_1"},
    {2, "PTK_Y_1"},
    {9, "PTK_Y_1"},
    {5, "PTK_K_1"},
    {4, "PTK_I_1"},
    {3, "PTK_I_1"},
    {28, "PTK_S_1"},
    {29, "PTK_Q_1"},
    {30, "PTK_Q_1"},
    {31, "PTK_S_1"},
    {39, "PTK_D_1"},
    {50, "PTK_A_1"},
    {42, "PTK_R_1"},
    {41, "PTK_R_2"},
    {40, "PTK_W_1"},
    {56, "PTK_I_1"},
    {57, "PTK_I_1"},
    {65, "PTK_T_1"},
    {69, "PTK_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table_patakuri[] = {
    {14, dmg_fall_event},
    {48, patakuri_dmg_first_attack_pos},
    {0, NULL},
};

static s32 pose_sound_timing_table[] = {
    (s32)"PTK_S_1", 1008981770, 0, (s32)"SFX_ENM_PATAKURI_WAIT1", 1, (s32)"PTK_W_1", 1008981770, 0,
    (s32)"SFX_ENM_PATAKURI_MOVE1", 1, (s32)"PTK_R_1", 1008981770, 0, (s32)"SFX_ENM_PATAKURI_MOVE1", 1, (s32)"PTK_K_1",
    1008981770, 0, (s32)"SFX_ENM_PATAKURI_WAIT1", 1, (s32)"PTK_N_1", 1008981770, 0, (s32)"SFX_ENM_PATAKURI_WAIT1",
    1, (s32)"PTK_I_1", 1008981770, 0, (s32)"SFX_ENM_PATAKURI_WAIT1", 1, 0, 0,
    0, 0, 1,
};

static EVT_BEGIN(init_event_patakuri)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_patakuri))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_patakuri))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event_patakuri))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dmg_fall_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_OffAttribute,
    -29999990, 4, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, -29999989, 2048, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986, 65546, 1000, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -29999990, -29999989, (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table, 327771,
    (s32)btlevtcmd_ReplaceParts, -29999990, -29999989, (s32)parts, 1, 196699, (s32)btlevtcmd_OnUnitFlag, -29999990,
    4, 131122, -29999989, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989,
    39, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FALL1", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 131122, -29999999,
    0, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229998976, 458843, (s32)btlevtcmd_JumpPosition, -29999990,
    -30000000, -29999999, -29999998, 10, -1, 327771, (s32)btlevtcmd_SetHomePos, -29999990,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KURI_MOVE1", -250000000,
    0, -250000000, 65546, 500, 196699, (s32)btlevtcmd_ChangeKind, -29999990, 1,
    65630, (s32)init_event, 65545, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989,
    39, 2, 1,
};

static EVT_BEGIN(patakuri_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static s32 attack_event_patakuri[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_patakuri_attack, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_patakuri_attack, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode,
    0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163,
    (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_patakuri_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_patakuri_attack, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 40, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 50, 131125, -29999999,
    40, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0,
    -16, 0, 0, -1, 65546, 100, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 196699, (s32)evt_btl_camera_nomove_y_onoff,
    0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PATAKURI_MOVE2", -250000000, 0, -250000000, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0, 5, 4,
    0, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_patakuri_attack,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PATAKURI_MOVE3", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 50, 131126, -29999999, 10,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0, -20,
    1, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69,
    65546, 500, 65540, 98, 65539, 91, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PATAKURI_MOVE3", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131126, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 0, -16, 1, 0, 0, 393307, (s32)evt_btl_camera_shake_h,
    0, 1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    (s32)weapon_patakuri_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_patakuri_attack, 256,
    -29999995, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_ENM_PATAKURI_MOVE1", (s32)"SFX_ENM_PATAKURI_MOVE1", 0, 15,
    15, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229992832, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    0, -10, 0, 0, -2, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_patakuri)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    LABEL(0)
    WAIT_FRAMES(30)
    GOTO(0)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "KUR_N_1"},
    {2, "KUR_Y_1"},
    {9, "KUR_Y_1"},
    {5, "KUR_K_1"},
    {4, "KUR_I_1"},
    {3, "KUR_I_1"},
    {28, "KUR_S_1"},
    {29, "KUR_Q_1"},
    {30, "KUR_Q_1"},
    {31, "KUR_S_1"},
    {39, "KUR_D_1"},
    {50, "KUR_A_1"},
    {51, "KUR_A_2"},
    {42, "KUR_R_1"},
    {41, "KUR_R_2"},
    {40, "KUR_W_1"},
    {56, "KUR_I_1"},
    {57, "KUR_I_1"},
    {65, "KUR_T_1"},
    {69, "KUR_S_1"},
};

static __declspec(section ".data") s32 data_table[] = {
    48, (s32)btldefaultevt_Dummy, 0, 0,
};

static __declspec(section ".data") s32 defence[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist[] = {
    1684956260, 1684300900, 1684300900, 1684300910, 1684300900, 1687552000,
};

static s32 parts[] = {
    1, (s32)"btl_un_kuriboo", (s32)"c_kuribo", 0, 0, 0, 0, 1102053376,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence, (s32)defence_attr,
    9, 0, (s32)pose_table,
};

static s32 weapon_kuriboo_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 20615, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_ENM_KURI_JUMP1"), STRING("SFX_ENM_KURI_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
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

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65546,
    750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_kuriboo_attack, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_kuriboo_attack, -29999997, -29999996, 33, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 196699,
    (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630, -30000000,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 327771, (s32)btlevtcmd_JumpSetting, -2,
    20, -230000000, -229999386, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_kuriboo_attack, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_kuriboo_attack, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, 100, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998,
    1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998,
    0, -1, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 170, 196699, (s32)evt_btl_camera_set_mode,
    0, 3, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0, 1, 107, 327771,
    (s32)btlevtcmd_GetPosFloat, -2, -29999995, -29999994, -29999993, 131122, -29999992, 0,
    65541, 32, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999991, -29999990, -29999989,
    393307, (s32)krb_get_dir, -29999995, -29999994, -29999991, -29999990, -29999992, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, -29999992, 131124, -29999995, -29999991,
    131124, -29999994, -29999990, 65545, 1, 6, 109, 107,
    65541, 12, 65545, 1, 6, 131122, -29999985, 50,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, -29999985, 109, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 32, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_kuriboo_attack, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 91, 46, 49, 65539,
    90, 131163, (s32)btlevtcmd_JumpContinue, -2, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 131122, -29999985, 69, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_MoveDirectionAdd, -2, -30000000, 30, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    10, -1, 65546, 500, 65540, 95, 65539, 91,
    393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KURI_ATTACK1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, (s32)weapon_kuriboo_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_kuriboo_attack,
    256, -29999995, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    131122, -29999985, 69, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, -29999985,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131122, -29999999,
    0, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 30, -1, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 10,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 6, -1,
    65540, 95, 65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_ENM_KURI_MOVE1", (s32)"SFX_ENM_KURI_MOVE2", 0, 3, 3,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 41, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -2, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(krb_get_dir) {
    s32* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);
    s32 dir = evtGetValue(event, args[4]);
    f32 dx = x2 - x1;
    f32 dz = z2 - z1;

    if (dx == 0.0f && dz == 0.0f) {
        evtSetValue(event, args[4], dir);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[4], angleABf(dx, dz, 0.0f, 0.0f));
    return EVT_RETURN_DONE;
}
