#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AddHomePos);
USER_FUNC(btlevtcmd_AddPos);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckAttribute);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_DivePosition);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventCeilFall);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetKissHitOffset);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetPossessionItemOffset);
USER_FUNC(btlevtcmd_SetStatusIconOffset);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(evt_btl_camera_add_zoom);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_btl_camera_shake_h);
extern s32 btldefaultevt_Damage[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_counter_damage[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_basabasa_negone_one_374;
__declspec(section ".data") s32 fd_basabasa_neg_one_382[1];
__declspec(section ".data") s32 fd_basabasa___local_PI_383[1];
__declspec(section ".data") s32 fd_basabasa___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_basabasa_one_negone_373;
__declspec(section ".data") s32 fd_basabasa___local_PIO2_384[1];
__declspec(section ".data") s32 fd_basabasa_one_381[1];
__declspec(section ".data") u64 fd_basabasa_negone_one_360;
__declspec(section ".data") s32 fd_basabasa_neg_one_365[1];
__declspec(section ".data") s32 fd_basabasa___local_PI_366[1];
__declspec(section ".data") s32 fd_basabasa___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_basabasa_one_negone_359;
__declspec(section ".data") s32 fd_basabasa___local_PIO2_367[1];
__declspec(section ".data") s32 fd_basabasa_one_364[1];
BattleUnitKind unit_basabasa;
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
static s32 attack_event[448];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_basabasa_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_basabasa_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_basabasa___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_basabasa___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_basabasa_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_basabasa___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_basabasa_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_basabasa_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_basabasa_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_basabasa___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_basabasa___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_basabasa_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_basabasa___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_basabasa_one_364[] = {
    1065353216,
};

BattleUnitKind unit_basabasa = {
    74,
    "btl_un_basabasa",
    6,
    0,
    1,
    1,
    17,
    0,
    2,
    70,
    0,
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
    {1, "btl_un_basabasa", "c_basabasa", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table_ceil},
};

static __declspec(section ".data") StatusVulnerability regist = {80, 85, 105, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 95, 80, 80, 95, 100, 80, 100, 100, 95};

static s32 weapon_basabasa_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 20615, 0, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 pose_sound_timing_table[] = {
    (s32)"BSA_S_1", 1008981770, 0, (s32)"SFX_ENM_BASA_WAIT1", 1, (s32)"BSA_W_1", 1008981770, 0,
    (s32)"SFX_ENM_BASA_MOVE1\0", 1, (s32)"BSA_R_1", 1008981770, 0, (s32)"SFX_ENM_BASA_MOVE1\0", 1, (s32)"BSA_T_1",
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

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_basabasa_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_basabasa_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_basabasa_attack))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_basabasa_attack))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddPos, -2, 0, -30, 0)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(2.5f))
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 30)
        SUBTRACT(LW(1), 40)
        CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    ADD(LW(1), -6)
    LOOP(2)
        ADD(LW(1), 13)
        CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 10, 10, 0, 0, -1)
        ADD(LW(1), -13)
        CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 10, -10, 0, 0, -1)
    END_LOOP
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.5f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(1), 10)
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), PTR(weapon_basabasa_attack), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.5f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 0, 0, 0, 0, -1)
    WAIT_MS(200)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(weapon_basabasa_attack))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(weapon_basabasa_attack), 256, LW(5))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.5f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 0, 0, 4, 0, -1)
    WAIT_MS(200)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(7))
    IF_INT_EQUAL(LW(7), 1)
        SUBTRACT(LW(1), 30)
    END_IF
    CALL(btlevtcmd_DivePosition, -2, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BSA_S_2"))
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddPos, -2, 0, 30, 0)
        ELSE
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BSA_S_1"))
        WAIT_FRAMES(1)
    END_IF
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

