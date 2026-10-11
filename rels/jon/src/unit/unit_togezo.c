#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_ChangeDataTable);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetOverTurnCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_OffPartsCounterAttribute);
USER_FUNC(btlevtcmd_OffStatusFlag);
USER_FUNC(btlevtcmd_OnPartsCounterAttribute);
USER_FUNC(btlevtcmd_OnStatusFlag);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetOverTurnCount);
USER_FUNC(btlevtcmd_SetPartsDefenceAttrTable);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetRegistStatus);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_eff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_random);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AddUnitWork[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
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
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_togezo_negone_one_374;
__declspec(section ".data") s32 fd_togezo_neg_one_382[1];
__declspec(section ".data") s32 fd_togezo___local_PI_383[1];
__declspec(section ".data") s32 fd_togezo___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_togezo_one_negone_373;
__declspec(section ".data") s32 fd_togezo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_togezo_one_381[1];
__declspec(section ".data") u64 fd_togezo_negone_one_360;
__declspec(section ".data") s32 fd_togezo_neg_one_365[1];
__declspec(section ".data") s32 fd_togezo___local_PI_366[1];
__declspec(section ".data") s32 fd_togezo___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_togezo_one_negone_359;
__declspec(section ".data") s32 fd_togezo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_togezo_one_364[1];
BattleUnitKind unit_togezo_15_data_275B0;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") s32 defence_turn[2];
static __declspec(section ".data") s32 defence_attr_turn[2];
static __declspec(section ".data") s32 regist_turn[6];
static __declspec(section ".data") s32 defence_guard[2];
static __declspec(section ".data") s32 defence_attr_guard[2];
static __declspec(section ".data") s32 regist_guard[6];
static PoseTableEntry pose_table[15];
static PoseTableEntry pose_table_turn[14];
static PoseTableEntry pose_table_guard[12];
static __declspec(section ".data") BattleDataEntry data_table[5];
static __declspec(section ".data") s32 data_table_turn[6];
static __declspec(section ".data") s32 data_table_guard[8];
static BattleUnitKindPart parts[1];
static s32 weapon_togezo_attack[48];
static s32 init_event[52];
static s32 dmg_avoid_counter_thorn_event[61];
static __declspec(section ".data") s32 damage_event[10];
static s32 dmg_turn_event[84];
static s32 wakeup_event[90];
static s32 attack_event[71];
static s32 normal_attack_event[813];
static s32 guard_event[95];
static s32 guard_cancel_event[89];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_togezo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_togezo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_togezo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_togezo___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_togezo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_togezo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_togezo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_togezo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_togezo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_togezo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_togezo___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_togezo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_togezo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_togezo_one_364[] = {
    1065353216,
};

BattleUnitKind unit_togezo_15_data_275B0 = {
    41,
    "btl_un_togezo",
    3,
    0,
    1,
    1,
    9,
    0,
    1,
    70,
    0,
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
    12.0f,
    16.0f,
    0.0f,
    0.0f,
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
    "SFX_ENM_TOGEZO_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{3, 3, 3, 3, 3}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 90, 80, 100, 80, 100, 100, 70, 100, 90, 100, 90, 100, 95, 90, 100, 30, 100, 90, 100, 100, 100};

static __declspec(section ".data") s32 defence_turn[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_turn[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_turn[] = {
    1684300900, 1684300900, 1684300900, 1684300900, 1684300900, 1684275200,
};

static __declspec(section ".data") s32 defence_guard[] = {
    1667457891, 1660944384,
};

static __declspec(section ".data") s32 defence_attr_guard[] = {
    33686018, 33554432,
};

static __declspec(section ".data") s32 regist_guard[] = {
    1684300900, 1684300900, 1684300900, 1684300900, 1684300900, 1684275200,
};

static PoseTableEntry pose_table[] = {
    {1, "TGZ_N_1"},
    {2, "TGZ_Y_1"},
    {9, "TGZ_Y_1"},
    {5, "TGZ_K_1"},
    {4, "TGZ_X_1"},
    {3, "TGZ_X_1"},
    {28, "TGZ_S_1"},
    {29, "TGZ_Q_1"},
    {30, "TGZ_Q_1"},
    {31, "TGZ_A_1"},
    {39, "TGZ_D_1"},
    {40, "TGZ_W_1"},
    {42, "TGZ_R_1"},
    {65, "TGZ_T_1"},
    {69, "TGZ_S_1"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "TGZ_N_2"},
    {2, "TGZ_Y_2"},
    {9, "TGZ_Y_2"},
    {5, "TGZ_K_2"},
    {4, "TGZ_X_2"},
    {3, "TGZ_X_2"},
    {28, "TGZ_S_2"},
    {29, "TGZ_Q_2"},
    {30, "TGZ_Q_2"},
    {31, "TGZ_S_1"},
    {39, "TGZ_D_3"},
    {40, "TGZ_W_1"},
    {42, "TGZ_R_1"},
    {69, "TGZ_S_2"},
};

static PoseTableEntry pose_table_guard[] = {
    {1, "TGZ_P_1"},
    {2, "TGZ_P_1"},
    {9, "TGZ_P_1"},
    {5, "TGZ_P_1"},
    {4, "TGZ_P_1"},
    {3, "TGZ_P_1"},
    {28, "TGZ_P_1"},
    {29, "TGZ_P_1"},
    {30, "TGZ_P_1"},
    {31, "TGZ_P_1"},
    {39, "TGZ_P_1"},
    {69, "TGZ_P_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_event},
    {39, dmg_avoid_counter_thorn_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static __declspec(section ".data") s32 data_table_turn[] = {
    13, (s32)dmg_turn_event, 48, (s32)btldefaultevt_Dummy, 0, 0,
};

static __declspec(section ".data") s32 data_table_guard[] = {
    37, (s32)dmg_avoid_counter_thorn_event, 39, (s32)dmg_avoid_counter_thorn_event, 48, (s32)btldefaultevt_Dummy, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_togezo", "c_togezo", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x1009, 0x5, pose_table},
};

static s32 weapon_togezo_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 1535, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_TOGEZO_MOVE1L"), STRING("SFX_ENM_TOGEZO_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_TOGEZO_MOVE1L"), STRING("SFX_ENM_TOGEZO_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_ENM_KURI_JUMP1"), STRING("SFX_ENM_KURI_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 45)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 25)
        GOTO(90)
    END_IF
    ADD(LW(1), 35)
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

static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(defence_turn))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(defence_attr_turn))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(regist_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), 1)
    CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), LW(11), 1)
    CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), LW(11), 4)
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table_turn))
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(evt_snd_sfxon, STRING("SFX_CONDITION_INSIDE"), 0)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
    RETURN
EVT_END()

static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, LW(10))
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, LW(10), LW(11), PTR(&defence_attr))
    CALL(btlevtcmd_SetRegistStatus, LW(10), PTR(&regist))
    CALL(btlevtcmd_OffStatusFlag, LW(10), 1)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_OnPartsCounterAttribute, LW(10), LW(11), 1)
    CALL(btlevtcmd_OnPartsCounterAttribute, LW(10), LW(11), 4)
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 69)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetOverTurnCount, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(wakeup_event))
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(guard_cancel_event))
        GOTO(99)
        ELSE
        SET_VALUE(LW(0), 50)
        ADD(LW(0), 50)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 50)
            CALL_CHILD(PTR(normal_attack_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(guard_event))
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_togezo_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_togezo_attack,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_togezo_attack,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_togezo_attack, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999986, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999986,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEZO_TURN1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 15, 0, 65541, 5, 131122, -30000000, -36,
    131127, -30000000, -29999986, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -30000000, 65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"TGZ_P_1", 65541, 5, 131122, -30000000, -36, 131127, -30000000,
    -29999986, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -30000000, 65545,
    1, 6, 65545, 5, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1,
    1, 131122, -30000000, -36, 131127, -30000000, -29999986, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 2, -30000000, 110, 65541, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000, 131096, -30000000, 0, 7,
    33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 0, -30000000, 65545, 1, 6, 112,
    65545, 10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEZO_ROLL1", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 30, 0, -229999847, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 30, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGEZO_ROLL2", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229990784, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0, 0, 1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_togezo_attack, 0, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEZO_ROLL5",
    -250000000, 0, -250000000, 110, 131122, -30000000, -18, 131127,
    -30000000, -29999986, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -30000000, 131122,
    -30000000, 1, 131127, -30000000, -29999986, 65541, 18, 262235,
    (s32)btlevtcmd_AddUnitWork, -2, 2, -30000000, 65545, 3, 6, 112,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229997952, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 0,
    0, 1, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 26, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229998976, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 0, 0, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1,
    0, 65545, 10, 65540, 97, 65539, 91, 393307,
    (s32)evt_btl_camera_shake_h, 0, 1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGEZO_ROLL4", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    (s32)weapon_togezo_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_togezo_attack, 256,
    -29999995, 131122, -30000000, 36, 131127, -30000000, -29999986, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 2, -36, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 30, 131125,
    -29999998, 10, 327771, (s32)btlevtcmd_JumpSetting, -2, 30, 0, -229999488,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 30, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEZO_JUMP1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 30, 131125, -29999998, 5, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 15, 0, -229999488, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, 0, -29999998, 15, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGEZO_JUMP1", -250000000, 0, -250000000, 110, 131122, -30000000, 18,
    131127, -30000000, -29999986, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, -30000000,
    131122, -30000000, -1, 131127, -30000000, -29999986, 65541, 18,
    262235, (s32)btlevtcmd_AddUnitWork, -2, 2, -30000000, 65545, 2, 6,
    112, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 18, 131125, -29999998,
    10, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229998976, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, 0, -29999998, 0, 0, 1, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 9, 131125, -29999998, 5, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229999488, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998,
    0, 0, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0,
    65545, 3, 196699, (s32)evt_sub_random, 99, -30000000, 131098, -30000000,
    30, 65540, 98, 32, 65540, 97, 33, 65539,
    97, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEZO_TURN2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 15, 0, 65541, 5, 131122, -30000000,
    36, 131127, -30000000, -29999986, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    0, -30000000, 65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"TGZ_S_1", 65541, 5, 131122, -30000000, 36, 131127,
    -30000000, -29999986, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -30000000,
    65545, 1, 6, 65545, 5, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGZ_S_1", 65546, 250,
    65540, 99, 65539, 98, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGEZO_ROLL3",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1,
    131122, -30000000, 36, 131127, -30000000, -29999986, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 2, -30000000, 110, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 1, -30000000, 131096, -30000000, 0, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 7, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -30000000, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -30000000, 65545, 1, 6, 112, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, 0, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1,
    0, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -2, 1, (s32)defence_guard, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable,
    -2, 1, (s32)defence_attr_guard, 196699, (s32)btlevtcmd_SetRegistStatus, -2, (s32)regist_guard, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_guard, 196699, (s32)btlevtcmd_ChangeDataTable, -2, (s32)data_table_guard,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 4096, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 1, 65546, 250, 65540, 99, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static s32 guard_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGEZO_TURN1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 15,
    0, 65541, 5, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    36, 65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"TGZ_P_1", 65541, 5, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    36, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65545, 5, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989,
    (s32)defence_guard, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990, -29999989, (s32)defence_attr_guard, 196699, (s32)btlevtcmd_SetRegistStatus,
    -29999990, (s32)regist_guard, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_guard, 196699,
    (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table_guard, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999990, -29999989, 4096,
    262235, (s32)btlevtcmd_SetUnitWork, -29999990, 0, 1, 2, 1,
};

static s32 guard_cancel_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGEZO_TURN2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 15,
    0, 65541, 5, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -36, 65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"TGZ_S_1", 65541, 5, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -36, 65545, 1, 6, 65545, 5, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -29999990, -29999989, (s32)&defence, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990, -29999989, (s32)&defence_attr,
    196699, (s32)btlevtcmd_SetRegistStatus, -29999990, (s32)&regist, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989,
    (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990,
    -29999989, 4096, 262235, (s32)btlevtcmd_SetUnitWork, -29999990, 0, 0, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

