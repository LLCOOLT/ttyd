#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_OffPartsCounterAttribute);
USER_FUNC(btlevtcmd_OnPartsCounterAttribute);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetOverTurnCount[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffStatusFlag[];
extern s32 btlevtcmd_OnStatusFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetOverTurnCount[];
extern s32 btlevtcmd_SetPartsDefenceTable[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
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
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_yamitogedaruma_negone_one_374;
__declspec(section ".data") s32 fd_yamitogedaruma_neg_one_382[1];
__declspec(section ".data") s32 fd_yamitogedaruma___local_PI_383[1];
__declspec(section ".data") s32 fd_yamitogedaruma___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_yamitogedaruma_one_negone_373;
__declspec(section ".data") s32 fd_yamitogedaruma___local_PIO2_384[1];
__declspec(section ".data") s32 fd_yamitogedaruma_one_381[1];
__declspec(section ".data") u64 fd_yamitogedaruma_negone_one_360;
__declspec(section ".data") s32 fd_yamitogedaruma_neg_one_365[1];
__declspec(section ".data") s32 fd_yamitogedaruma___local_PI_366[1];
__declspec(section ".data") s32 fd_yamitogedaruma___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_yamitogedaruma_one_negone_359;
__declspec(section ".data") s32 fd_yamitogedaruma___local_PIO2_367[1];
__declspec(section ".data") s32 fd_yamitogedaruma_one_364[1];
BattleUnitKind unit_yamitogedaruma;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") s32 defence_turn[2];
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_turn[15];
static __declspec(section ".data") BattleDataEntry data_table[6];
static BattleUnitKindPart parts[1];
static s32 weapon_togedaruma_attack[48];
static s32 init_event[21];
static s32 dmg_avoid_counter_thorn_head_event[63];
static s32 dmg_avoid_counter_thorn_front_event[121];
static __declspec(section ".data") s32 damage_event[10];
static s32 dmg_turn_event[131];
static s32 wakeup_event[134];
static s32 attack_event[358];
static s32 wait_event[102];

__declspec(section ".data") u64 fd_yamitogedaruma_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_yamitogedaruma_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_yamitogedaruma___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_yamitogedaruma___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_yamitogedaruma_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_yamitogedaruma___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_yamitogedaruma_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_yamitogedaruma_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_yamitogedaruma_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_yamitogedaruma___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_yamitogedaruma___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_yamitogedaruma_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_yamitogedaruma___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_yamitogedaruma_one_364[] = {
    1065353216,
};

BattleUnitKind unit_yamitogedaruma = {
    165,
    "btl_un_yamitogedaruma",
    8,
    0,
    1,
    1,
    34,
    1,
    2,
    70,
    2,
    50,
    9999,
    46,
    40,
    4,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    0.0f,
    20.0f,
    26.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    46.0f,
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
    "SFX_ENM_TOGEDA_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{4, VERSION_PICK(4, 99), 4, 4, 4}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, VERSION_PICK(0, 2), 0, 0, 0}};

static __declspec(section ".data") s32 defence_turn[] = {
    0, 0,
};

static __declspec(section ".data") StatusVulnerability regist = {20, 80, 20, 100, 20, 100, VERSION_PICK(100, 0), 40, 100, 50, 100, 50, 100, 100, 40, 30, 20, 100, 40, 100, 100, 30};

static PoseTableEntry pose_table[] = {
    {1, "TGD_N_1"},
    {2, "TGD_I_1"},
    {9, "TGD_I_1"},
    {5, "TGD_K_1"},
    {4, "TGD_X_1"},
    {3, "TGD_X_1"},
    {28, "TGD_S_4"},
    {29, "TGD_Q_1"},
    {30, "TGD_Q_1"},
    {31, "TGD_S_2"},
    {39, "TGD_D_1"},
    {50, "TGD_A_1"},
    {40, "TGD_S_4"},
    {42, "TGD_S_4"},
    {56, "TGD_X_1"},
    {57, "TGD_X_1"},
    {65, "TGD_T_1"},
    {69, "TGD_S_4"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "TGD_N_2"},
    {2, "TGD_I_2"},
    {9, "TGD_Z_4"},
    {5, "TGD_K_2"},
    {4, "TGD_X_2"},
    {3, "TGD_X_2"},
    {28, "TGD_S_5"},
    {29, "TGD_Q_2"},
    {30, "TGD_Q_2"},
    {31, "TGD_S_3"},
    {39, "TGD_D_2"},
    {56, "TGD_X_2"},
    {57, "TGD_X_2"},
    {65, "TGD_S_5"},
    {69, "TGD_S_5"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {39, dmg_avoid_counter_thorn_front_event},
    {38, dmg_avoid_counter_thorn_front_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_yamitogedaruma", "c_togedaruma_b", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2009, 0x7, pose_table},
};

static s32 weapon_togedaruma_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 30, 8196,
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

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 58)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 32)
        GOTO(90)
    END_IF
    ADD(LW(1), 45)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

static s32 dmg_avoid_counter_thorn_front_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEDA_MOVE1", -250000000, 0, -250000000, 110,
    262235, (s32)btlevtcmd_CheckStatus, -2, 17, -30000000, 131097, -30000000, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_J_3", 65545, 60, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_J_4", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"TGD_J_1", 65545, 60, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"TGD_J_2", 33, 112, 65545, 30, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_CheckStatus, -2, 10, -29999997,
    131097, -29999997, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 53,
    131125, -29999999, 26, 65540, 90, 33, 262235, (s32)btlevtcmd_CheckStatus,
    -2, 11, -29999997, 131097, -29999997, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 33, 131125, -29999999, 16, 65540, 90,
    33, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 43, 131125, -29999999,
    21, 65540, 90, 65539, 90, 983131, (s32)evt_eff, (s32)"",
    (s32)"toge_flush", 0, -30000000, -29999999, -29999998, 60, 0, 0,
    0, 0, 0, 0, 0, 65545, 60, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dmg_turn_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -29999990, -29999989, (s32)defence_turn, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_turn,
    196699, (s32)btlevtcmd_OnStatusFlag, -29999990, 1, 196699, (s32)btlevtcmd_GetOverTurnCount, -29999990, -29999988,
    196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 2, 65545, 2, 393307, (s32)btlevtcmd_snd_se,
    -29999990, (s32)"SFX_ENM_INSIDE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990,
    -29999989, (s32)"TGD_S_1", 131100, -29999988, 0, 131122, -29999988, 0,
    327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 10, 0, 110, 65541,
    0, 131101, -29999988, 10, 7, 33, 131125, -29999988,
    1, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -18, 6, 112, 33, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 25, -1, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"TGD_S_5", 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2,
    -30000000, 10, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 10,
    -29999998, 2, 1,
};

static s32 wakeup_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_GetOverTurnCount,
    -29999990, -30000000, 131126, -30000000, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990,
    -30000000, 131097, -30000000, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    33, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)&defence, 196699, (s32)btlevtcmd_OffStatusFlag,
    -29999990, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table, 131122,
    -29999988, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 10, 0,
    110, 65541, 0, 131101, -29999988, 10, 7, 33,
    131125, -29999988, 1, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -18, 6, 112, 393307, (s32)btlevtcmd_snd_se, -29999990,
    (s32)"SFX_ENM_TOGEDA_MOVE6", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 18, -1, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"TGD_S_4", 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2,
    -30000000, 0, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 0,
    -29999998, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_GetOverTurnCount, -2, -30000000, 131101, -30000000, 1, 65630,
    (s32)wakeup_event, 2, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097,
    -30000000, 0, 65546, 750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996,
    32, 196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0,
    65630, -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_togedaruma_attack,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_togedaruma_attack, -29999997, -29999996, 33, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_togedaruma_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_togedaruma_attack, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGEDA_MOVE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"TGD_J_1", 65545, 10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEDA_MOVE2",
    -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_A_1",
    65546, 400, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229992832, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_togedaruma_attack, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_A_1",
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 131163, (s32)evt_snd_sfxoff, -29999985, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGEDA_MOVE3", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 0,
    0, -229999898, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998,
    -229938560, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEDA_MOVE4", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_N_1", 65546, 1500,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_J_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGEDA_MOVE5\0\0\0", -250000000, 0, -250000000, 65540, 98, 65539, 91,
    393307, (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_togedaruma_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)weapon_togedaruma_attack, 256, -29999995, 131163, (s32)evt_snd_sfxoff, -29999985, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGEDA_MOVE3", -250000000, 0, -250000000, 65540, 98, 65539,
    98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229994880,
    -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_J_2", 65545, 15,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGD_S_4", 65546, 400, 65539,
    99, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    LABEL(0)
    SET_VALUE(LW(15), 0)
    CALL(btlevtcmd_CheckStatus, -2, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 3, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 5, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 9, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        ADD(LW(15), 1)
    END_IF
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_OffPartsCounterAttribute, -2, 1, 2)
        ELSE
        CALL(btlevtcmd_OnPartsCounterAttribute, -2, 1, 2)
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

