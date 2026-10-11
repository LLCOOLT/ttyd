#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_GetOverTurnCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_OffStatusFlag);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetOverTurnCount);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OnStatusFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_moveto[];
extern s32 evt_btl_camera_set_posoffset[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_msg_print[];
extern s32 evt_snd_sfxoff[];
extern s32 pose_table_nokotarou_stay[];
extern s32 pose_table_nokotarou_turn[];
extern s32 weaponGetPowerFromGulliblePartyAttackLv[];

__declspec(section ".data") u64 fd_gullible_nokotarou_negone_one_374;
__declspec(section ".data") s32 fd_gullible_nokotarou_neg_one_382[1];
__declspec(section ".data") s32 fd_gullible_nokotarou___local_PI_383[1];
__declspec(section ".data") s32 fd_gullible_nokotarou___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gullible_nokotarou_one_negone_373;
__declspec(section ".data") s32 fd_gullible_nokotarou___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gullible_nokotarou_one_381[1];
__declspec(section ".data") u64 fd_gullible_nokotarou_negone_one_360;
__declspec(section ".data") s32 fd_gullible_nokotarou_neg_one_365[1];
__declspec(section ".data") s32 fd_gullible_nokotarou___local_PI_366[1];
__declspec(section ".data") s32 fd_gullible_nokotarou___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gullible_nokotarou_one_negone_359;
__declspec(section ".data") s32 fd_gullible_nokotarou___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gullible_nokotarou_one_364[1];
BattleUnitKind unit_gullible_nokotarou;
static s32 enemyWeapon_NokotarouKouraAttack[48];
static s32 enemyWeapon_NokotarouShubibinAttack[48];
static __declspec(section ".data") BattleUnitDefense defence_nokotarou;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_nokotarou;
static __declspec(section ".data") s32 defence_turn_nokotarou[2];
static __declspec(section ".data") StatusVulnerability regist_nokotarou;
static __declspec(section ".data") BattleDataEntry data_table_nokotarou[3];
static BattleUnitKindPart parts_nokotarou[1];
static s32 dmg_turn_event[64];
static s32 wakeup_event[67];
static s32 init_event_nokotarou[62];
static s32 damage_event_nokotarou[24];
static s32 dead_event_nokotarou[177];
static s32 _change_koura_pose[34];
static s32 _change_koura_pose_fast[34];
static s32 _restore_koura_pose[47];
static s32 _koura_rotate_start[99];
static s32 _koura_rotate_stop[13];
static s32 attack_event_nokotarou[33];
static s32 attack_event_nokotarou_koura[393];
static s32 attack_event_nokotarou_shubibin[339];
static __declspec(section ".data") s32 wait_event_nokotarou[6];

__declspec(section ".data") u64 fd_gullible_nokotarou_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_nokotarou_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_nokotarou___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_nokotarou___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_nokotarou_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_nokotarou___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_nokotarou_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gullible_nokotarou_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gullible_nokotarou_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gullible_nokotarou___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gullible_nokotarou___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gullible_nokotarou_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gullible_nokotarou___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gullible_nokotarou_one_364[] = {
    1065353216,
};

BattleUnitKind unit_gullible_nokotarou = {
    81,
    "btl_un_gullible_nokotarou",
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
    28,
    40,
    10,
    30,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
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
    26.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    28.0f,
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
    "SFX_PARTY_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x10000000,
    &regist_nokotarou,
    1,
    parts_nokotarou,
    init_event_nokotarou,
    data_table_nokotarou,
};

static s32 enemyWeapon_NokotarouKouraAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 3, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553664516, 525058, 0, 65671, 1535, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 enemyWeapon_NokotarouShubibinAttack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerFromGulliblePartyAttackLv,
    2, 3, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536887300, 525058, 0, 65671, 1535, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence_nokotarou = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_nokotarou = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") s32 defence_turn_nokotarou[] = {
    0, 0,
};

static __declspec(section ".data") StatusVulnerability regist_nokotarou = {60, 80, 70, 100, 70, 100, 100, 70, 100, 70, 100, 70, 100, 90, 70, 0, 0, 100, 70, 100, 100, 0};

static __declspec(section ".data") BattleDataEntry data_table_nokotarou[] = {
    {49, dead_event_nokotarou},
    {13, dmg_turn_event},
    {0, NULL},
};

static BattleUnitKindPart parts_nokotarou[] = {
    {1, "btl_un_nokotarou", "c_pnk", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_nokotarou, &defence_attr_nokotarou, 0x1009, 0, pose_table_nokotarou_stay},
};

static s32 dmg_turn_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -29999990, -29999989, (s32)defence_turn_nokotarou, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_nokotarou_turn,
    196699, (s32)btlevtcmd_OnStatusFlag, -29999990, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990, 2,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"PNK_D_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_INSIDE1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 12, -1, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 6, -1, 2, 1,
};

static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_nokotarou))
    CALL(btlevtcmd_OffStatusFlag, LW(10), 1)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_stay))
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("PNK_S_1"))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(init_event_nokotarou)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_nokotarou))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_nokotarou))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_nokotarou))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 9, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 11, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event_nokotarou)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(20), 1)
    END_IF
    CALL_CHILD(PTR(_koura_rotate_stop))
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event_nokotarou[] = {
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999996, -29999995, 131122, -29999994, 1, 131096,
    -30000000, -29999997, 131096, -29999999, -29999996, 131096, -29999998, -29999995,
    131122, -29999994, 0, 33, 33, 33, 131096, -29999994,
    1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229993856, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 33, 65545,
    1, 65627, (s32)btlevtcmd_WaitAttackEnd, 65570, -49999981, 65572, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto, 0, 130, 58,
    228, 130, 38, -20, 30, 11, 65545, 37,
    327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_03_nok", 0, -2, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PNK_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000,
    0, -250000000, 65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0, 3,
    655451, (s32)evt_btl_camera_set_moveto, 0, 90, 58, 228, 90, 38,
    -20, 30, 11, 65545, 37, 327771, (s32)evt_msg_print, 2,
    (s32)"stg4_jin_26_04", 0, -49999984, 65546, 200, 65572, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 65541, 0, 131096, -49999981, 2,
    7, 33, 65545, 1, 6, 65572, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PNK_D_3", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 49, 196699, (s32)btlevtcmd_KillUnit, -2, 1,
    131122, -49999980, 2, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2,
    1,
};

static EVT_BEGIN(_change_koura_pose)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_2"))
    LOOP(18)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 15, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_1"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 15, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(_change_koura_pose_fast)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_2"))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 27, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_1"))
    LOOP(3)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 30, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(_restore_koura_pose)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_1"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 45, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PNK_K_2"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, -2, 0, 15, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(_koura_rotate_start)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 1)
    CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
    BEGIN_INLINE_EVENT
        LABEL(0)
        CALL(btlevtcmd_GetUnitWork, -2, 8, LW(1))
        IF_INT_EQUAL(LW(1), 0)
            GOTO(10)
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, 10, LW(11))
        IF_INT_NOT_EQUAL(LW(11), 0)
            CALL(btlevtcmd_SetUnitWork, -2, 10, 0)
            CALL(btlevtcmd_GetUnitWork, -2, 9, LW(10))
            MULTIPLY(LW(10), -1)
            MULTIPLY(LW(0), -1)
            CALL(btlevtcmd_SetUnitWork, -2, 9, LW(10))
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, 9, LW(10))
        IF_INT_GREATER_OR_EQUAL(LW(10), 0)
            ADD(LW(0), 1)
            IF_INT_GREATER(LW(0), LW(10))
                SET_VALUE(LW(0), LW(10))
            END_IF
            ELSE
            SUBTRACT(LW(0), 1)
            IF_INT_LESS(LW(0), LW(10))
                SET_VALUE(LW(0), LW(10))
            END_IF
        END_IF
        CALL(btlevtcmd_AddRotate, -2, 0, LW(0), 0)
        WAIT_FRAMES(1)
        GOTO(0)
        LABEL(10)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(_koura_rotate_stop)
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event_nokotarou)
    CALL(btlevtcmd_GetOverTurnCount, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(wakeup_event))
        RETURN
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 2, 80, 20)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL_CHILD(PTR(attack_event_nokotarou_koura))
        CASE_EQUAL(1)
        CALL_CHILD(PTR(attack_event_nokotarou_shubibin))
    END_SWITCH
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 attack_event_nokotarou_koura[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_NokotarouKouraAttack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699,
    (s32)evt_btl_camera_set_mode, 0, 10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1,
    -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 100, 65545, 20, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    65630, (s32)_change_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_ATTACK1", -250000000, 0, -29999987, 131122, -30000000,
    15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 9, 45, 65630, (s32)_koura_rotate_start,
    65545, 30, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999994, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom,
    0, 400, 65545, 30, 131163, (s32)evt_snd_sfxoff, -29999987, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_ATTACK2", -250000000, 0, -29999987, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999995, -29999998, 131125, -29999998, 5, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0, -29999987, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, -29999987, -1, 0,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 40,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 65630, (s32)_koura_rotate_stop, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65540, 99, 33, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 65539, 90, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    30, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18,
    -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1, 65630,
    (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 65545, 30,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

static s32 attack_event_nokotarou_shubibin[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 131122, -29999988,
    (s32)enemyWeapon_NokotarouShubibinAttack, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2,
    -30000000, -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 100,
    65545, 20, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65630, (s32)_change_koura_pose,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_NOKO_SHUBIBIN1", -250000000, 0, -29999987, 262235, (s32)btlevtcmd_SetUnitWork, -2, 5,
    0, 131122, -30000000, 15, 262235, (s32)btlevtcmd_SetUnitWork, -2, 9,
    45, 65630, (s32)_koura_rotate_start, 65546, 500, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 65546, 500, 65631,
    -29999985, 131163, (s32)evt_snd_sfxoff, -29999987, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_NOKO_SHUBIBIN2",
    -250000000, 0, -29999987, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 131122, -29999990,
    0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999995, -29999998, 131125, -29999998, 5, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999994,
    131097, -29999994, 1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65540, 50, 33, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 80, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, -400, -29999999, -29999998, 0, -1,
    0, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131127, -30000000, -1, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 65630, (s32)_koura_rotate_stop, 65630, (s32)_restore_koura_pose, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 65545, 30, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_nokotarou)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

