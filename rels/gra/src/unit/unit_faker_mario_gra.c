#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario_pouch.h"

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
static USER_FUNC(vivian_comeback);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetEventAttack[];
extern s32 btlevtcmd_SetEventConfusion[];
extern s32 btlevtcmd_SetEventDamage[];
extern s32 btlevtcmd_SetEventWait[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetRunSound[];
extern s32 btlevtcmd_SetWalkSound[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_sub_random[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_faker_mario_gra_negone_one_374;
__declspec(section ".data") s32 fd_faker_mario_gra_neg_one_382[1];
__declspec(section ".data") s32 fd_faker_mario_gra___local_PI_383[1];
__declspec(section ".data") s32 fd_faker_mario_gra___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_faker_mario_gra_one_negone_373;
__declspec(section ".data") s32 fd_faker_mario_gra___local_PIO2_384[1];
__declspec(section ".data") s32 fd_faker_mario_gra_one_381[1];
__declspec(section ".data") u64 fd_faker_mario_gra_negone_one_360;
__declspec(section ".data") s32 fd_faker_mario_gra_neg_one_365[1];
__declspec(section ".data") s32 fd_faker_mario_gra___local_PI_366[1];
__declspec(section ".data") s32 fd_faker_mario_gra___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_faker_mario_gra_one_negone_359;
__declspec(section ".data") s32 fd_faker_mario_gra___local_PIO2_367[1];
__declspec(section ".data") s32 fd_faker_mario_gra_one_364[1];
BattleUnitKind unit_faker_mario_gra;
static __declspec(section ".data") BattleUnitDefense defence_fmario;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_fmario;
static __declspec(section ".data") StatusVulnerability regist_fmario;
static PoseTableEntry pose_table_fmario_stay[15];
static __declspec(section ".data") BattleDataEntry data_table_fmario[2];
static BattleUnitKindPart parts_fmario[1];
static s32 weapon_masao_jump[48];
static s32 weapon_masao_hammer[48];
static s32 weapon_masao_kururin_jump[48];
static s32 weapon_masao_kaiten_hammer[48];
static s32 mario_zoom[19];
static s32 enemy_zoom[19];
static s32 fmario_zoom[19];
static s32 gparty_zoom[19];
static s32 init_event_fmario[42];
static __declspec(section ".data") s32 dead_event_fmario[2];
static __declspec(section ".data") s32 damage_event_fmario[10];
static s32 attack_event_fmario[60];
static s32 jump_attack_voice[36];
static s32 marioAttackEvent_NormalJump[344];
static s32 marioAttackEvent_KururinJump[469];
static s32 marioAttackEvent_NormalHammer[299];
static s32 marioAttackEvent_KaitenHammer[299];
static __declspec(section ".data") s32 wait_event_fmario[6];

__declspec(section ".data") u64 fd_faker_mario_gra_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_faker_mario_gra_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_faker_mario_gra___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_faker_mario_gra___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_faker_mario_gra_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_faker_mario_gra___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_faker_mario_gra_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_faker_mario_gra_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_faker_mario_gra_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_faker_mario_gra___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_faker_mario_gra___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_faker_mario_gra_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_faker_mario_gra___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_faker_mario_gra_one_364[] = {
    1065353216,
};

BattleUnitKind unit_faker_mario_gra = {
    78,
    "btl_un_hatena",
    40,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    70,
    7,
    24,
    40,
    12,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
    32.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    24.0f,
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
    "SFX_MARIO_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist_fmario,
    1,
    parts_fmario,
    init_event_fmario,
    data_table_fmario,
};

static __declspec(section ".data") BattleUnitDefense defence_fmario = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_fmario = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") StatusVulnerability regist_fmario = {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static PoseTableEntry pose_table_fmario_stay[] = {
    {1, "EM_N_1"},
    {2, "EM_Y_2"},
    {9, "EM_Y_2"},
    {5, "EM_K_1"},
    {4, "EM_K_1"},
    {3, "EM_K_1"},
    {28, "EM_S_1"},
    {39, "EM_D_1"},
    {50, "EM_A_1"},
    {42, "EM_R_1"},
    {40, "EM_W_1"},
    {56, "EM_D_3"},
    {57, "EM_D_3"},
    {65, "EM_T_1"},
    {69, "EM_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table_fmario[] = {
    {49, dead_event_fmario},
    {0, NULL},
};

static BattleUnitKindPart parts_fmario[] = {
    {1, "btl_un_hatena", "c_mario", 0.0f, 0.0f, 0.0f, 3.0f, 27.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_fmario, &defence_attr_fmario, 0x9, 0, pose_table_fmario_stay},
};

static s32 weapon_masao_jump[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 88071, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_hammer[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, 0, 67591, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_kururin_jump[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 88071, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_kaiten_hammer[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, 0, 67591, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(mario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -110, 65, 332, -110, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(enemy_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 115, 65, 332, 115, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(fmario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(gparty_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 130, 65, 332, 130, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static s32 init_event_fmario[] = {
    196699, (s32)btlevtcmd_SetEventWait, -2, (s32)wait_event_fmario, 196699, (s32)btlevtcmd_SetEventAttack, -2, (s32)attack_event_fmario,
    196699, (s32)btlevtcmd_SetEventDamage, -2, (s32)damage_event_fmario, 196699, (s32)btlevtcmd_SetEventConfusion, -2, (s32)btldefaultevt_Confuse,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, -1610612736, 458843, (s32)btlevtcmd_SetWalkSound, -2,
    (s32)"SFX_BOSS_NM_MOVE1L", (s32)"SFX_BOSS_NM_MOVE1R", 0, 20, 20, 458843, (s32)btlevtcmd_SetRunSound, -2,
    (s32)"SFX_BOSS_NM_MOVE1L", (s32)"SFX_BOSS_NM_MOVE1R", 0, 10, 10, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(dead_event_fmario)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event_fmario)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event_fmario)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 4, 50, 50, 20, 20)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(weapon_masao_jump))
        CALL_CHILD(PTR(marioAttackEvent_NormalJump))
        CASE_EQUAL(1)
        SET_VALUE(LW(9), PTR(weapon_masao_hammer))
        CALL_CHILD(PTR(marioAttackEvent_NormalHammer))
        CASE_EQUAL(2)
        SET_VALUE(LW(9), PTR(weapon_masao_kururin_jump))
        CALL_CHILD(PTR(marioAttackEvent_KururinJump))
        CASE_EQUAL(3)
        SET_VALUE(LW(9), PTR(weapon_masao_kaiten_hammer))
        CALL_CHILD(PTR(marioAttackEvent_KaitenHammer))
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 jump_attack_voice[] = {
    196699, (s32)evt_sub_random, 2, -29999985, 65570, -29999985, 65572, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_1", -250000000, 0, -250000000, 65572,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_2", -250000000, 0, -250000000,
    65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_5", -250000000, 0,
    -250000000, 49, 2, 1,
};

static s32 marioAttackEvent_NormalJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_D_2", 65545, 40, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 98, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_W_1",
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_KururinJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_D_2", 65545, 40, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65647, -29999986, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999488, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, 36, 0, -1, 112, 65545, 15,
    65631, -29999986, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131127, -29999985,
    -30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_Z_2", 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 12, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP_KURURIN1",
    -250000000, 0, -250000000, 65541, 12, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -29999985, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 4, 0, 0, 0, -1, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    8, -1, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_NormalHammer[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11,
    393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 24, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1A", 65546, 66, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_NM_HAMMER_FURU2", -250000000, 0, -250000000, 65546, 233, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1B", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_A_1C", 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_HAMMER_DON2",
    -250000000, 0, -250000000, 65546, 100, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 700, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_S_1", 65546, 200, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static s32 marioAttackEvent_KaitenHammer[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11,
    393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 24, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1A", 65546, 66, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_NM_HAMMER_FURU2", -250000000, 0, -250000000, 65546, 233, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1B", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_A_1C", 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_HAMMER_DON2",
    -250000000, 0, -250000000, 65546, 100, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 700, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_S_1", 65546, 200, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_fmario)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(vivian_comeback) {
    pouchGetPtr()->partyData[6].flags &= ~2;
    return 1;
}

#ifdef VERSION_G8ME01
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "manager/evtmgr_cmd.h"

// US only: restore the moves of the unit for this turn.
USER_FUNC(faker_mario_gra_sync_max_moves) {
    BattleUnit* unit;
    s32 id = evtGetValue(event, event->args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit != NULL) {
        unit->maxMovesThisTurn = unit->movesRemaining;
    }
    return EVT_RETURN_DONE;
}
#endif
