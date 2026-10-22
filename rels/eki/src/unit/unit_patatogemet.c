#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_ChangeDataTable);
USER_FUNC(btlevtcmd_ChangeKind);
USER_FUNC(btlevtcmd_CheckAttribute);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetHpDamageCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_ReplaceParts);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventCeilFall);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetKissHitOffset);
USER_FUNC(btlevtcmd_SetOverTurnCount);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_eff);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
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
extern s32 btlevtcmd_GetOverTurnCount[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffPartsCounterAttribute[];
extern s32 btlevtcmd_OffStatusFlag[];
extern s32 btlevtcmd_OnPartsCounterAttribute[];
extern s32 btlevtcmd_OnStatusFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetJumpSpeed[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsDefenceAttrTable[];
extern s32 btlevtcmd_SetPartsDefenceTable[];
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
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_counter_damage[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_patatogemet_negone_one_374;
__declspec(section ".data") s32 fd_patatogemet_neg_one_382[1];
__declspec(section ".data") s32 fd_patatogemet___local_PI_383[1];
__declspec(section ".data") s32 fd_patatogemet___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_patatogemet_one_negone_373;
__declspec(section ".data") s32 fd_patatogemet___local_PIO2_384[1];
__declspec(section ".data") s32 fd_patatogemet_one_381[1];
__declspec(section ".data") u64 fd_patatogemet_negone_one_360;
__declspec(section ".data") s32 fd_patatogemet_neg_one_365[1];
__declspec(section ".data") s32 fd_patatogemet___local_PI_366[1];
__declspec(section ".data") s32 fd_patatogemet___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_patatogemet_one_negone_359;
__declspec(section ".data") s32 fd_patatogemet___local_PIO2_367[1];
__declspec(section ".data") s32 fd_patatogemet_one_364[1];
BattleUnitKind unit_patatogemet_7_data_10380;
static s32 weapon_patamet_attack[48];
static __declspec(section ".data") BattleUnitDefense defence_pata;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_pata;
static __declspec(section ".data") s32 regist_pata[6];
static PoseTableEntry pose_table_pata[18];
static __declspec(section ".data") BattleDataEntry data_table_pata[4];
static BattleUnitKindPart parts_pata[1];
static s32 pose_sound_timing_table[45];
static s32 init_event_pata[26];
static s32 dmg_avoid_counter_thorn_head_event_pata[61];
static __declspec(section ".data") s32 damage_event_pata[10];
static s32 dmg_fall_event_pata[106];
static s32 dmg_first_attack_pos_event_pata[19];
static s32 attack_event_pata[339];
static __declspec(section ".data") s32 wait_event_pata[6];
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_ceil[17];
static PoseTableEntry pose_table_turn[16];
static __declspec(section ".data") s32 data_table[8];
static s32 data_table_ceil[28];
static s32 weapon_met_attack[48];
static s32 weapon_met_ceil_attack[48];
static __declspec(section ".data") s32 defence[2];
static __declspec(section ".data") s32 defence_attr[2];
static __declspec(section ".data") s32 defence_turn[2];
static __declspec(section ".data") s32 defence_attr_turn[2];
static __declspec(section ".data") StatusVulnerability regist;
static s32 parts[19];
static __declspec(section ".data") s32 init_event[12];
static s32 init_event2[148];
static s32 dmg_avoid_counter_thorn_head_event[61];
static __declspec(section ".data") s32 damage_event[10];
static s32 dmg_turn_event[82];
static s32 wakeup_event[96];
static s32 attack_event[546];
static __declspec(section ".data") s32 wait_event[6];
static s32 damage_event_ceil[49];
static s32 counter_damage_event_ceil[76];
static s32 ceil_fall_ready_event[163];
static s32 attack_event_ceil[426];
static __declspec(section ".data") s32 wait_event_ceil[6];

__declspec(section ".data") u64 fd_patatogemet_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_patatogemet_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_patatogemet___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_patatogemet___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_patatogemet_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_patatogemet___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_patatogemet_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_patatogemet_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_patatogemet_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_patatogemet___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_patatogemet___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_patatogemet_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_patatogemet___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_patatogemet_one_364[] = {
    1065353216,
};

BattleUnitKind unit_patatogemet_7_data_10380 = {
    105,
    "btl_un_patatogemet",
    5,
    0,
    1,
    1,
    24,
    0,
    2,
    70,
    2,
    50,
    9999,
    28,
    30,
    5,
    30,
    0.0f,
    17.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    0.0f,
    14.0f,
    19.5f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    28.0f,
    30.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_MET_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    1,
    parts_pata,
    init_event_pata,
    data_table_pata,
};

static s32 weapon_patamet_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 20615, 1424, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence_pata = {{4, 99, 4, 99, 4}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_pata = {{0, 2, 0, 2, 0}};

static __declspec(section ".data") s32 regist_pata[] = {
    1264216420, 1264844875, 1683645530, 1683966780, 1516522340, 1683947520,
};

static PoseTableEntry pose_table_pata[] = {
    {1, "PTM_N_1"},
    {2, "PTM_Y_1"},
    {9, "PTM_Y_1"},
    {5, "PTM_K_1"},
    {4, "PTM_X_1"},
    {3, "PTM_X_1"},
    {28, "PTM_S_1"},
    {29, "PTM_Q_1"},
    {30, "PTM_Q_1"},
    {31, "PTM_S_1"},
    {39, "PTM_D_1"},
    {50, "PTM_A_1"},
    {42, "PTM_R_1"},
    {40, "PTM_W_1"},
    {56, "PTM_X_1"},
    {57, "PTM_X_1"},
    {65, "PTM_T_1"},
    {69, "PTM_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table_pata[] = {
    {14, dmg_fall_event_pata},
    {37, dmg_avoid_counter_thorn_head_event_pata},
    {48, dmg_first_attack_pos_event_pata},
    {0, NULL},
};

static BattleUnitKindPart parts_pata[] = {
    {1, "btl_un_patatogemet", "c_met", 0.0f, 0.0f, 0.0f, 0.0f, 23.0f, 0.0f, 0.0f, 28.0f, 0.0f, 20, 30, 255, &defence_pata, &defence_attr_pata, 0x600809, 0x1, pose_table_pata},
};

static s32 pose_sound_timing_table[] = {
    (s32)"PTM_S_1", 1008981770, 0, (s32)"SFX_ENM_PATAMET_WAIT1", 1, (s32)"PTM_W_1", 1008981770, 0,
    (s32)"SFX_ENM_PATAMET_WAIT1", 1, (s32)"PTM_R_1", 1008981770, 0, (s32)"SFX_ENM_PATAMET_WAIT1", 1, (s32)"PTM_A_1",
    1008981770, 0, (s32)"SFX_ENM_PATAMET_WAIT1", 1, (s32)"PTM_K_1", 1008981770, 0, (s32)"SFX_ENM_PATAMET_WAIT1",
    1, (s32)"PTM_N_1", 1008981770, 0, (s32)"SFX_ENM_PATAMET_WAIT1", 1, (s32)"PTM_X_1", 1008981770,
    0, (s32)"SFX_ENM_PATAMET_WAIT1", 1, (s32)"PTM_T_1", 1008981770, 0, (s32)"SFX_ENM_PATAMET_WAIT1", 1,
    0, 0, 0, 0, 1,
};

static EVT_BEGIN(init_event_pata)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_pata))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_pata))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_pata))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event_pata))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event_pata)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 50)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 30)
        GOTO(90)
    END_IF
    ADD(LW(1), 40)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event_pata)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(dmg_fall_event_pata)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, LW(10), 4)
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), 2048)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_ReplaceParts, LW(10), LW(11), PTR(parts), 1)
    CALL(btlevtcmd_OnUnitFlag, LW(10), 4)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ChangeKind, LW(10), 73)
    CALL(btlevtcmd_GetHpDamageCount, LW(10), LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(init_event))
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
        RETURN
        ELSE
        CALL_CHILD(PTR(init_event))
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
        CALL_CHILD(PTR(dmg_turn_event))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(dmg_first_attack_pos_event_pata)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static s32 attack_event_pata[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000,
    131097, -30000000, 0, 65630, -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy,
    -2, -30000000, (s32)weapon_patamet_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_patamet_attack, -29999997, -29999996,
    33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16,
    -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33,
    65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_patamet_attack, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_patamet_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PATAMET_MOVE1", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 30, -229998976, 0, 0, -1, 65546, 250,
    131163, (s32)evt_snd_sfxoff, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PATAMET_MOVE2", -250000000,
    0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229990784, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 10, 131126,
    -29999999, 30, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    0, -10, 0, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_patamet_attack, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -29999997, -250000000,
    -29999995, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 75, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999995, -29999998, 0, 0, 0,
    0, -1, 65546, 300, 65540, 98, 65539, 91,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_patamet_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_patamet_attack, 256, -29999995, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PATAMET_ATTACK1",
    -250000000, 0, -250000000, 65540, 98, 65539, 98, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 0, -10, 0, 0,
    -1, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_pata)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "TMT_N_1"},
    {2, "TMT_Y_1"},
    {9, "TMT_Y_1"},
    {5, "TMT_K_1"},
    {4, "TMT_X_1"},
    {3, "TMT_X_1"},
    {28, "TMT_S_1"},
    {29, "TMT_Q_1"},
    {30, "TMT_Q_1"},
    {31, "TMT_A_1"},
    {39, "TMT_D_1"},
    {50, "TMT_A_1"},
    {40, "TMT_W_1"},
    {42, "TMT_R_1"},
    {56, "TMT_X_1"},
    {57, "TMT_X_1"},
    {69, "TMT_S_1"},
};

static PoseTableEntry pose_table_ceil[] = {
    {1, "STM_N_1"},
    {2, "STM_Y_1"},
    {9, "STM_Y_1"},
    {5, "STM_K_1"},
    {4, "STM_X_1"},
    {3, "STM_X_1"},
    {28, "STM_S_1"},
    {29, "STM_Q_1"},
    {30, "STM_Q_1"},
    {31, "STM_A_1"},
    {39, "STM_D_1"},
    {50, "STM_A_1"},
    {40, "STM_W_1"},
    {42, "STM_R_1"},
    {56, "STM_X_1"},
    {57, "STM_X_1"},
    {69, "STM_S_1"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "TMT_Y_2"},
    {2, "TMT_Y_2"},
    {9, "TMT_Y_2"},
    {5, "TMT_S_3"},
    {4, "TMT_S_3"},
    {3, "TMT_S_3"},
    {28, "TMT_S_3"},
    {29, "TMT_Q_2"},
    {30, "TMT_Q_2"},
    {31, "TMT_A_1"},
    {39, "TMT_S_3"},
    {40, "TMT_W_1"},
    {42, "TMT_R_1"},
    {56, "TMT_S_3"},
    {57, "TMT_S_3"},
    {69, "TMT_S_3"},
};

static __declspec(section ".data") s32 data_table[] = {
    13, (s32)dmg_turn_event, 37, (s32)dmg_avoid_counter_thorn_head_event, 48, (s32)btldefaultevt_Dummy, 0, 0,
};

static s32 data_table_ceil[] = {
    26, (s32)counter_damage_event_ceil, 25, (s32)counter_damage_event_ceil, 27, (s32)counter_damage_event_ceil, 28, (s32)counter_damage_event_ceil,
    29, (s32)counter_damage_event_ceil, 30, (s32)counter_damage_event_ceil, 31, (s32)counter_damage_event_ceil, 32, (s32)counter_damage_event_ceil,
    33, (s32)counter_damage_event_ceil, 34, (s32)counter_damage_event_ceil, 35, (s32)counter_damage_event_ceil, 36, (s32)counter_damage_event_ceil,
    48, (s32)btldefaultevt_Dummy, 0, 0,
};

static s32 weapon_met_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553664516, 770, 0, 135, 1535, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_met_ceil_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 20615, 1535, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 defence[] = {
    73598051, 67108864,
};

static __declspec(section ".data") s32 defence_attr[] = {
    131074, 0,
};

static __declspec(section ".data") s32 defence_turn[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_turn[] = {
    0, 0,
};

static __declspec(section ".data") StatusVulnerability regist = {75, 90, 75, 100, 75, 100, 0, 75, 100, 90, 100, 90, 100, 95, 75, 60, 30, 100, 75, 100, 100, 95};

static s32 parts[] = {
    1, (s32)"btl_un_togemet", (s32)"c_met", 0, 0, 0, 0, 1102577664,
    0, 0, 1105199104, 0, 1310750, 16711680, (s32)defence, (s32)defence_attr,
    9, 1, (s32)pose_table,
};

static __declspec(section ".data") EVT_BEGIN(init_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(15))
    CALL_CHILD(PTR(init_event2))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(init_event2)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
        CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
        CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
        CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
        CALL(btlevtcmd_SetEventCeilFall, -2, 0)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 4096)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, 0, 0)
        ELSE
        CALL(btlevtcmd_OnAttribute, -2, 2)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 4194304)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 2097152)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_ceil))
        CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_ceil))
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        SET_VALUE(LW(1), 130)
        CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_ceil))
        CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_ceil))
        CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_ceil))
        CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event_ceil))
        CALL(btlevtcmd_SetEventCeilFall, -2, PTR(ceil_fall_ready_event))
        CALL(btlevtcmd_SetHitOffset, -2, 1, 0, -50, 0)
        CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, -50, 0)
        CALL(btlevtcmd_SetKissHitOffset, -2, 14, -17, 0)
    END_IF
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_MET_MOVE1L"), STRING("SFX_ENM_MET_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetOverTurnCount, -2, 0)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 38)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 18)
        GOTO(90)
    END_IF
    ADD(LW(1), 28)
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

static s32 dmg_turn_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -29999990, -29999989, (s32)defence_turn, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990, -29999989, (s32)defence_attr_turn,
    262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_turn, 196699, (s32)btlevtcmd_OnStatusFlag, -29999990,
    1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990,
    -29999989, 39, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE1", -250000000, 0,
    -250000000, 65545, 4, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 5, -29999998, 18, -1, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 5, -29999998, 12, -1, 327771, (s32)btlevtcmd_SetHomePos, -2,
    -30000000, 5, -29999998, 262235, (s32)btlevtcmd_OffPartsCounterAttribute, -2, 1, 1,
    2, 1,
};

static s32 wakeup_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_GetOverTurnCount,
    -29999990, -30000000, 131126, -30000000, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990,
    -30000000, 131097, -30000000, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    33, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)defence, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable,
    -29999990, -29999989, (s32)defence_attr, 196699, (s32)btlevtcmd_OffStatusFlag, -29999990, 1, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989,
    69, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE2", -250000000, 0, -250000000,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998,
    18, -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, 0, -29999998,
    262235, (s32)btlevtcmd_OnPartsCounterAttribute, -2, 1, 1, 327771, (s32)btlevtcmd_SetHomePos, -2,
    -30000000, 0, -29999998, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_GetOverTurnCount, -2, -30000000, 131101, -30000000, 1, 65630,
    (s32)wakeup_event, 2, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 65545, 30,
    32, 196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0,
    65630, -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_met_attack,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_met_attack, -29999997, -29999996, 33, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_met_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_met_attack, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 100, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_MET_ATTACK1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20,
    -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_SHELL1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_ATTACK2",
    -250000000, 0, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 0, 110, 65541, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999985, 131096, -29999985, 1,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 7, 33,
    65545, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999986, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, -29999986, 0, 6, 112, 65546,
    100, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 10, 65546, 100,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 20, 65546, 100, 65647,
    -29999987, 65541, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 10, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test",
    0, -30000000, -29999999, -29999998, -229999693, 0, 0, 0,
    0, 0, 0, 0, 65545, 3, 6, 112,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229991808, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999995,
    -250000000, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999995, -29999998, 0,
    0, 0, 65631, -29999987, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_met_attack, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    100, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0,
    0, 0, 65546, 250, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2,
    10, 65546, 250, 131163, (s32)evt_snd_sfxoff, -29999985, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 1, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_JUMP1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -229989760, -229999591, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_JUMP1", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20, -1, 65540,
    98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_met_attack, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_met_attack, 256, -29999995, 131163,
    (s32)evt_snd_sfxoff, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 10, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -229996928, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_MOVE2", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20, -1, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -229999488, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 75,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_MOVE2", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20, -1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 65540, 98, 65539, 98,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event_ceil)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_CheckDamageCode, -2, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, -2, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_GetTotalDamage, -2, LW(12))
    IF_INT_EQUAL(LW(12), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(ceil_fall_ready_event))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(counter_damage_event_ceil)
    CALL(btlevtcmd_OffAttribute, -2, 2)
    CALL(btlevtcmd_OffPartsAttribute, -2, 1, 4194304)
    CALL(btlevtcmd_OffPartsAttribute, -2, 1, 2097152)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, -2, 14, 17, 0)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), 0, LW(2))
    CALL_CHILD(PTR(init_event2))
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    CALL_CHILD(PTR(subsetevt_counter_damage))
    RETURN
EVT_END()

static s32 ceil_fall_ready_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FALL1", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, 0, 196699, (s32)btlevtcmd_SetJumpSpeed, -2, 0, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999796, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 20, -29999998, 15,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEMET_LANDING1", -250000000, 0, -250000000,
    196699, (s32)btlevtcmd_OffAttribute, -2, 2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1,
    4194304, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 2097152, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table_turn, 196699, (s32)btlevtcmd_ChangeDataTable, -2, (s32)data_table, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 393307, (s32)btlevtcmd_SetHitOffset, -2, 1,
    0, 0, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -2, 1, 0,
    0, 0, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 14, 17, 0,
    65630, (s32)init_event2, 131122, -29999990, -2, 131122, -29999989, 1,
    262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)defence_turn, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990,
    -29999989, (s32)defence_attr_turn, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_turn, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 69, 196699, (s32)btlevtcmd_OnStatusFlag, -29999990, 1,
    196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 5, -29999998, 18, -1, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 5, -29999998, 12, -1, 327771, (s32)btlevtcmd_SetHomePos,
    -2, -30000000, 5, -29999998, 262235, (s32)btlevtcmd_OffPartsCounterAttribute, -2, 1,
    1, 2, 1,
};

static s32 attack_event_ceil[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000,
    131097, -30000000, 0, 65630, -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy,
    -2, -30000000, (s32)weapon_met_ceil_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_met_ceil_attack, -29999997, -29999996,
    33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16,
    -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2, 33,
    65540, 99, 33, 327771, (s32)btlevtcmd_GetPos, -2, -29999993, -29999992,
    -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 250, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0, 1, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_met_ceil_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_met_ceil_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    65546, 100, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999990, -29999989, -29999988, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999989, -29999988, 60, -1,
    1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 65546, 250,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_FALL1\0\0", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, 0, 196699, (s32)btlevtcmd_SetJumpSpeed, -2, 0, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999796, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 20, -29999998,
    15, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEMET_LANDING1", -250000000, 0,
    -250000000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, (s32)weapon_met_ceil_attack, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    (s32)weapon_met_ceil_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_met_ceil_attack, 256,
    -29999995, 65540, 98, 65539, 98, 65545, 60, 196699,
    (s32)btlevtcmd_OffAttribute, -2, 2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 4194304,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 2097152, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable, -2, (s32)data_table, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 0, 393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0,
    0, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -2, 1, 0, 0,
    0, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 14, 17, 0, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 327771, (s32)btlevtcmd_JumpSetting, -2, 20,
    -229996928, -229999796, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 25, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_MET_JUMP1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 0, -29999998, 20, -1, 327771, (s32)btlevtcmd_JumpSetting, -2,
    20, -229999488, -229999796, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 25, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MET_JUMP1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 20, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 327771, (s32)btlevtcmd_SetHomePos, -2, -29999993, 0,
    -29999991, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2,
    -29999993, 0, -29999991, 0, -1, 0, 65630, (s32)init_event2,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_ceil)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

