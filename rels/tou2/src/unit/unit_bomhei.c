#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeDataTable[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetHpDamage[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_OnPartsCounterAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSoundDataWork[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_StageDispellFog[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_w[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_bomhei_negone_one_374;
__declspec(section ".data") s32 fd_bomhei_neg_one_382[1];
__declspec(section ".data") s32 fd_bomhei___local_PI_383[1];
__declspec(section ".data") s32 fd_bomhei___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_bomhei_one_negone_373;
__declspec(section ".data") s32 fd_bomhei___local_PIO2_384[1];
__declspec(section ".data") s32 fd_bomhei_one_381[1];
__declspec(section ".data") u64 fd_bomhei_negone_one_360;
__declspec(section ".data") s32 fd_bomhei_neg_one_365[1];
__declspec(section ".data") s32 fd_bomhei___local_PI_366[1];
__declspec(section ".data") s32 fd_bomhei___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_bomhei_one_negone_359;
__declspec(section ".data") s32 fd_bomhei___local_PIO2_367[1];
__declspec(section ".data") s32 fd_bomhei_one_364[1];
BattleUnitKind unit_bomhei_28_data_17C48;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_spark[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static __declspec(section ".data") s32 data_table_spark[4];
static BattleUnitKindPart parts[1];
static __declspec(section ".data") StatusVulnerability regist;
static s32 weapon_bomhei_attack[48];
static s32 weapon_bomhei_bomb[48];
static s32 bomb_event[106];
static s32 init_event[42];
static s32 damage_event[58];
static s32 change_spark_event[70];
static s32 attack_event[440];
static __declspec(section ".data") s32 wait_event[6];
static s32 damage_event_spark[25];
static s32 attack_event_spark[288];
static s32 wait_event_spark[27];

__declspec(section ".data") u64 fd_bomhei_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bomhei_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bomhei___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bomhei___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bomhei_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bomhei___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bomhei_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_bomhei_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bomhei_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bomhei___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bomhei___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bomhei_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bomhei___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bomhei_one_364[] = {
    1065353216,
};

BattleUnitKind unit_bomhei_28_data_17C48 = {
    43,
    "btl_un_bomhei",
    4,
    0,
    1,
    1,
    12,
    0,
    1,
    70,
    1,
    50,
    9999,
    32,
    30,
    4,
    30,
    0.0f,
    15.0f,
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
    16.0f,
    0.0f,
    0.0f,
    11.0f,
    16.0f,
    0.0f,
    2.0f,
    15.0f,
    0.0f,
    32.0f,
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
    "SFX_ENM_BOMB_DAMAGED1",
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

static PoseTableEntry pose_table[] = {
    {1, "BOM_N_1"},
    {2, "BOM_Y_1"},
    {9, "BOM_Y_1"},
    {5, "BOM_K_1"},
    {4, "BOM_X_1"},
    {3, "BOM_X_1"},
    {28, "BOM_S_1"},
    {29, "BOM_Q_1"},
    {30, "BOM_Q_1"},
    {31, "BOM_S_1"},
    {39, "BOM_D_1"},
    {50, "BOM_A_1"},
    {42, "BOM_R_1"},
    {40, "BOM_W_1"},
    {56, "BOM_X_1"},
    {57, "BOM_X_1"},
    {65, "BOM_T_1"},
    {69, "BOM_S_1"},
};

static PoseTableEntry pose_table_spark[] = {
    {1, "BOM_N_2"},
    {2, "BOM_Y_2"},
    {9, "BOM_Y_2"},
    {5, "BOM_K_2"},
    {4, "BOM_X_2"},
    {3, "BOM_X_2"},
    {28, "BOM_S_2"},
    {29, "BOM_Q_2"},
    {30, "BOM_Q_2"},
    {31, "BOM_S_2"},
    {39, "BOM_D_2"},
    {50, "BOM_A_2"},
    {42, "BOM_R_2"},
    {40, "BOM_W_2"},
    {56, "BOM_X_2"},
    {57, "BOM_X_2"},
    {65, "BOM_T_2"},
    {69, "BOM_S_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static __declspec(section ".data") s32 data_table_spark[] = {
    48, (s32)btldefaultevt_Dummy, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_bomhei", "c_bomhey", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1000, pose_table},
};

static __declspec(section ".data") StatusVulnerability regist = {70, 100, 70, 0, 70, 150, 100, 100, 100, 90, 100, 90, 100, 95, 80, 90, 80, 100, 80, 100, 100, 95};

static s32 weapon_bomhei_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553664516, 770, 0, 135, 0, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_bomhei_bomb[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553664516, 770, 0, 8327, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1644900, 0, 0,
};

static s32 bomb_event[] = {
    393307, (s32)evt_btl_camera_shake_w, 0, 5, 0, 15, 0, 196699,
    (s32)btlevtcmd_OnAttribute, -2, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 33554432,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131097, -30000000, -1,
    131163, (s32)evt_snd_sfxoff, -30000000, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENM_BOMB_ATTACK2", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"",
    (s32)"sandars", 0, -30000000, -29999999, -29999998, 0, 0, 0,
    0, 0, 0, 0, 0, 65627, (s32)btlevtcmd_StageDispellFog, 196699,
    (s32)btlevtcmd_GetCoin, -2, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp,
    -2, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 131101, -30000000, 1,
    65541, -30000000, 6, 33, 65546, 1000, 131096, -29999985,
    1, 65627, (s32)btlevtcmd_WaitAttackEnd, 33, 196699, (s32)btlevtcmd_KillUnit, -2, 0,
    2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, -1)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_BOMB_MOVE2"), STRING("SFX_ENM_BOMB_MOVE2"), 0, 4, 4)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_BOMB_MOVE2"), STRING("SFX_ENM_BOMB_MOVE2"), 0, 10, 10)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(27)
            CASE_OR_EQUAL(25)
            SET_VALUE(LW(15), 1)
            CALL_CHILD(PTR(bomb_event))
            RETURN
            CASE_END
        END_SWITCH
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(change_spark_event))
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 change_spark_event[] = {
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39, 262235, (s32)btlevtcmd_CheckDamageCode, -2,
    256, -30000000, 131096, -30000000, 0, 65540, 99, 33,
    196699, (s32)btlevtcmd_GetHpDamage, -2, -29999985, 131101, -29999985, 1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_SPARK1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetEventWait,
    -2, (s32)wait_event_spark, 196699, (s32)btlevtcmd_SetEventAttack, -2, (s32)attack_event_spark, 196699, (s32)btlevtcmd_SetEventDamage,
    -2, (s32)damage_event_spark, 196699, (s32)btlevtcmd_SetEventConfusion, -2, (s32)attack_event_spark, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table_spark, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39,
    262235, (s32)btlevtcmd_OnPartsCounterAttribute, -2, 1, 8192, 196699, (s32)btlevtcmd_ChangeDataTable, -2,
    (s32)data_table_spark, 33, 65539, 99, 2, 1,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_bomhei_attack, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_bomhei_attack, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode,
    0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163,
    (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_bomhei_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_bomhei_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_MOVE1", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_MOVE1",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0, -1, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760,
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, 10, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 0, -1, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_bomhei_attack, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 30,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0, -1,
    1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 60,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0, -1,
    0, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229998976, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 90,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0, -1,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"BOM_N_1", 65546, 500,
    65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_bomhei_attack,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_bomhei_attack, 256, -29999995,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -229997952, -229999488, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    75, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_MOVE3", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -229998976, -229999488, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    100, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_MOVE3", -250000000, 0, -250000000,
    65540, 98, 65539, 98, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_ENM_BOMB_MOVE4",
    (s32)"SFX_ENM_BOMB_MOVE4", 0, 10, 10, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -2, 1, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event_spark)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(15), 1)
        CALL_CHILD(PTR(bomb_event))
        ELSE
        CALL_CHILD(PTR(btldefaultevt_Damage))
    END_IF
    RETURN
EVT_END()

static s32 attack_event_spark[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_bomhei_bomb, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_bomhei_bomb, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode,
    0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163,
    (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_bomhei_bomb, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_bomhei_bomb, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_MOVE1", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_MOVE1",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0, -1, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760,
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, 10, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_bomhei_bomb, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    500, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 131122, -29999985, 0, 65630, (s32)bomb_event, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 2, 65539, 91,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_bomhei_bomb, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_bomhei_bomb, 256, -29999995, 131122, -29999985, 0, 65630,
    (s32)bomb_event, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 1000, 2,
    65539, 98, 65546, 1000, 65539, 99, 2, 1,
};

static s32 wait_event_spark[] = {
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0,
    -29999985, 131096, -29999985, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BOMB_WAIT1\0",
    -250000000, 0, -29999985, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, -29999985,
    33, 2, 1,
};

