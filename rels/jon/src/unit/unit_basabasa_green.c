#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AddHomePos);
USER_FUNC(btlevtcmd_AddPos);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckAttribute);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_DivePosition);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventCeilFall);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetKissHitOffset);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetPossessionItemOffset);
USER_FUNC(btlevtcmd_SetStatusIconOffset);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddScale[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetDamage[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckCounter[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_counter_damage[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_basabasa_green_negone_one_374;
__declspec(section ".data") s32 fd_basabasa_green_neg_one_382[1];
__declspec(section ".data") s32 fd_basabasa_green___local_PI_383[1];
__declspec(section ".data") s32 fd_basabasa_green___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_basabasa_green_one_negone_373;
__declspec(section ".data") s32 fd_basabasa_green___local_PIO2_384[1];
__declspec(section ".data") s32 fd_basabasa_green_one_381[1];
__declspec(section ".data") u64 fd_basabasa_green_negone_one_360;
__declspec(section ".data") s32 fd_basabasa_green_neg_one_365[1];
__declspec(section ".data") s32 fd_basabasa_green___local_PI_366[1];
__declspec(section ".data") s32 fd_basabasa_green___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_basabasa_green_one_negone_359;
__declspec(section ".data") s32 fd_basabasa_green___local_PIO2_367[1];
__declspec(section ".data") s32 fd_basabasa_green_one_364[1];
BattleUnitKind unit_basabasa_green;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static s32 weapon_basabasa_drain_attack_biribiri_counterd[48];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_ceil[18];
static BattleDataEntry data_table[14];
static BattleUnitKindPart parts[1];
static __declspec(section ".data") StatusVulnerability regist;
static s32 weapon_basabasa_attack[48];
static s32 pose_sound_timing_table[45];
static s32 ceil_sky_event[98];
static s32 init_event[78];
static __declspec(section ".data") s32 dmg_first_attack_pos[12];
static __declspec(section ".data") s32 damage_event[10];
static s32 damage_event_ceil[51];
static s32 counter_damage_event[16];
static s32 ceil_fall_ready_event[23];
static s32 attack_event[683];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_basabasa_green_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_basabasa_green_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_basabasa_green___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_basabasa_green___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_basabasa_green_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_basabasa_green___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_basabasa_green_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_basabasa_green_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_basabasa_green_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_basabasa_green___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_basabasa_green___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_basabasa_green_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_basabasa_green___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_basabasa_green_one_364[] = {
    1065353216,
};

BattleUnitKind unit_basabasa_green = {
    167,
    "btl_un_basabasa_green",
    20,
    0,
    1,
    1,
    35,
    2,
    2,
    70,
    2,
    50,
    9999,
    32,
    32,
    6,
    32,
    0.0f,
    16.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -15.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    0.0f,
    16.0f,
    20.8f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    32.0f,
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
    "SFX_ENM_BASA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4040002,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static s32 weapon_basabasa_drain_attack_biribiri_counterd[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 0, 0, 8192,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "BSA_N_1"},
    {2, "BSA_Y_1"},
    {9, "BSA_Y_1"},
    {5, "BSA_K_1"},
    {4, "BSA_X_1"},
    {3, "BSA_X_1"},
    {28, "BSA_S_1"},
    {29, "BSA_Q_1"},
    {30, "BSA_Q_1"},
    {31, "BSA_S_1"},
    {39, "BSA_D_1"},
    {50, "BSA_A_1"},
    {42, "BSA_R_1"},
    {40, "BSA_W_1"},
    {56, "BSA_X_1"},
    {57, "BSA_X_1"},
    {65, "BSA_T_1"},
    {69, "BSA_S_1"},
};

static PoseTableEntry pose_table_ceil[] = {
    {1, "BSA_N_2"},
    {2, "BSA_Y_2"},
    {9, "BSA_Y_2"},
    {5, "BSA_K_2"},
    {4, "BSA_X_2"},
    {3, "BSA_X_2"},
    {28, "BSA_S_2"},
    {29, "BSA_Q_2"},
    {30, "BSA_Q_2"},
    {31, "BSA_S_2"},
    {39, "BSA_D_2"},
    {50, "BSA_A_1"},
    {42, "BSA_S_1"},
    {40, "BSA_S_1"},
    {56, "BSA_X_2"},
    {57, "BSA_X_2"},
    {65, "BSA_T_2"},
    {69, "BSA_S_2"},
};

static BattleDataEntry data_table[] = {
    {26, counter_damage_event},
    {25, counter_damage_event},
    {27, counter_damage_event},
    {28, counter_damage_event},
    {29, counter_damage_event},
    {30, counter_damage_event},
    {31, counter_damage_event},
    {32, counter_damage_event},
    {33, counter_damage_event},
    {34, counter_damage_event},
    {35, counter_damage_event},
    {36, counter_damage_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_basabasa_green", "c_basabasa_g", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table_ceil},
};

static __declspec(section ".data") StatusVulnerability regist = {50, 55, 90, 100, 50, 100, 100, 50, 100, 75, 100, 75, 100, 80, 50, 50, 75, 100, 50, 100, 100, 20};

static s32 weapon_basabasa_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 71, 0, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 pose_sound_timing_table[] = {
    (s32)"BSA_S_1", 1008981770, 0, (s32)"SFX_ENM_BASA_WAIT1", 1, (s32)"BSA_W_1", 1008981770, 0,
    (s32)"SFX_ENM_BASA_MOVE1", 1, (s32)"BSA_R_1", 1008981770, 0, (s32)"SFX_ENM_BASA_MOVE1", 1, (s32)"BSA_T_1",
    1008981770, 0, (s32)"SFX_ENM_BASA_WAIT1", 1, (s32)"BSA_A_1", 1008981770, 0, (s32)"SFX_ENM_BASA_WAIT1",
    1, (s32)"BSA_N_1", 1008981770, 0, (s32)"SFX_ENM_BASA_WAIT1", 1, (s32)"BSA_K_1", 1008981770,
    0, (s32)"SFX_ENM_BASA_WAIT1", 1, (s32)"BSA_X_1", 1008981770, 0, (s32)"SFX_ENM_BASA_WAIT1", 1,
    0, 0, 0, 0, 1,
};

static EVT_BEGIN(ceil_sky_event)
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_OffAttribute, -2, 2)
    CALL(btlevtcmd_OnAttribute, -2, 4)
    CALL(btlevtcmd_SetPossessionItemOffset, -2, 0, 0, 0)
    CALL(btlevtcmd_SetEventCeilFall, -2, 0)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddPos, -2, 0, -30, 0)
    CALL(btlevtcmd_AddHomePos, -2, 0, -30, 0)
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, 30, 0)
    CALL(btlevtcmd_SetKissHitOffset, -2, 16, 21, 0)
    CALL(btlevtcmd_SetStatusIconOffset, -2, 6, 32)
    CALL(btlevtcmd_AddHomePos, -2, 0, -40, 0)
    LABEL(99)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_ceil))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventCeilFall, -2, PTR(ceil_fall_ready_event))
    CALL(btlevtcmd_SetPossessionItemOffset, -2, 0, -20, 0)
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_SetHitOffset, -2, 1, 0, -50, 0)
    CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, -30, 0)
    CALL(btlevtcmd_SetStatusIconOffset, -2, 6, 10)
    CALL(btlevtcmd_SetKissHitOffset, -2, 16, -18, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(ceil_sky_event))
        CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(dmg_first_attack_pos)
    CALL_CHILD(PTR(ceil_sky_event))
    CALL(btlevtcmd_SetPos, -2, LW(0), 10, LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
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
    CALL(btlevtcmd_GetTotalDamage, LW(10), LW(12))
    IF_INT_EQUAL(LW(12), 0)
        RETURN
    END_IF
    CALL_CHILD(PTR(ceil_sky_event))
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 60, 0, 0, 0, -1)
    RETURN
EVT_END()

static EVT_BEGIN(counter_damage_event)
    CALL_CHILD(PTR(ceil_sky_event))
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    CALL_CHILD(PTR(subsetevt_counter_damage))
    RETURN
EVT_END()

static EVT_BEGIN(ceil_fall_ready_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL_CHILD(PTR(ceil_sky_event))
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 60, 0, 0, 0, -1)
    RETURN
EVT_END()

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_basabasa_attack, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_basabasa_attack, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_basabasa_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_basabasa_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 262235, (s32)btlevtcmd_CheckAttribute, -2, 2, -30000000, 131096, -30000000,
    1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 65545, 1,
    327771, (s32)btlevtcmd_AddPos, -2, 0, -30, 0, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229997440, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 30, 131126, -29999999, 40,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0, -16,
    0, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    33, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131125, -29999999, -6, 65541,
    2, 131125, -29999999, 13, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 10, 10, 0, 0, -1, 131125,
    -29999999, -13, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    10, -10, 0, 0, -1, 6, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996416, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15, 131126, -29999999,
    10, 131126, -29999998, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000,
    -29999999, -29999998, 0, -16, 0, 0, -1, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_basabasa_attack, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996416, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 50, 131125, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    -1, 65546, 200, 65540, 98, 65539, 91, 131122,
    -70000000, 0, 458843, (s32)btlevtcmd_PreCheckCounter, -2, -29999997, -29999996, (s32)weapon_basabasa_attack,
    256, -29999995, 131096, -29999995, 17, 131122, -70000000, 1,
    33, 131096, -29999995, 14, 131122, -70000000, 1, 33,
    131096, -70000000, 1, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_basabasa_attack, 131122, -29999991, (s32)weapon_basabasa_drain_attack_biribiri_counterd,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    2, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -45,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BASA_SUCK1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"BSA_A_2", 65541, 2, 65541, 10,
    327771, (s32)btlevtcmd_AddScale, -2, 0, -229999949, 0, 65545, 1,
    6, 65541, 10, 327771, (s32)btlevtcmd_AddScale, -2, 0, -230000051,
    0, 65545, 1, 6, 6, 393307, (s32)evt_btl_camera_shake_h, 0,
    1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_add_zoom, 0, -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_basabasa_attack,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_basabasa_attack, 256, -29999995,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 15, 131125, -29999998, 10, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 196699, (s32)btlevtcmd_GetDamage, -29999997, -29999990, 131101, -29999990, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"BSA_N_1", 65546, 300, 262235,
    (s32)btlevtcmd_RecoverHp, -2, 1, -29999990, 327771, (s32)btlevtcmd_GetPos, -2, -29999995,
    -29999994, -29999993, 131125, -29999994, 20, 131125, -29999993, 10,
    983131, (s32)evt_eff, (s32)"", (s32)"recovery", 7, -29999995, -29999994, -29999993,
    -29999990, 0, 0, 0, 0, 0, 0, 0,
    131122, -30000000, 0, 65541, 0, 131101, -30000000, 5,
    7, 33, 327771, (s32)btlevtcmd_AddScale, -2, -230000102, -229999898, 0,
    131125, -30000000, 1, 65545, 1, 6, 131122, -30000000,
    0, 65541, 0, 131101, -30000000, 10, 7, 33,
    327771, (s32)btlevtcmd_AddScale, -2, -229999898, -230000102, 0, 131125, -30000000,
    1, 65545, 1, 6, 131122, -30000000, 0, 65541,
    0, 131101, -30000000, 5, 7, 33, 327771, (s32)btlevtcmd_AddScale,
    -2, -230000102, -229999898, 0, 131125, -30000000, 1, 65545,
    1, 6, 327771, (s32)btlevtcmd_SetScale, -2, 1, 1, 1,
    65546, 1000, 33, 65546, 500, 65540, 98, 65539,
    98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_CheckAttribute, -2, 2,
    -29999993, 131096, -29999993, 1, 131126, -29999999, 30, 33,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 0, -10,
    0, 0, -1, 65539, 99, 262235, (s32)btlevtcmd_CheckAttribute, -2,
    2, -30000000, 131096, -30000000, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"BSA_S_2", 65545, 1, 327771, (s32)btlevtcmd_AddPos, -2, 0,
    30, 0, 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"BSA_S_1",
    65545, 1, 33, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

