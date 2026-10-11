#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "system.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle.h"

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(evt_eff);
USER_FUNC(evt_msg_print);
static USER_FUNC(get_attacker);
static USER_FUNC(krb_get_dir);
static u16 krb_comp_dir(f32 x, f32 z);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AddScale[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_EnemyItemUseCheck[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPosFloat[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MoveDirectionAdd[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetMoveSoundDataWork[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
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

__declspec(section ".data") u64 fd_yami_togekuri_negone_one_374;
__declspec(section ".data") s32 fd_yami_togekuri_neg_one_382[1];
__declspec(section ".data") s32 fd_yami_togekuri___local_PI_383[1];
__declspec(section ".data") s32 fd_yami_togekuri___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_yami_togekuri_one_negone_373;
__declspec(section ".data") s32 fd_yami_togekuri___local_PIO2_384[1];
__declspec(section ".data") s32 fd_yami_togekuri_one_381[1];
__declspec(section ".data") u64 fd_yami_togekuri_negone_one_360;
__declspec(section ".data") s32 fd_yami_togekuri_neg_one_365[1];
__declspec(section ".data") s32 fd_yami_togekuri___local_PI_366[1];
__declspec(section ".data") s32 fd_yami_togekuri___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_yami_togekuri_one_negone_359;
__declspec(section ".data") s32 fd_yami_togekuri___local_PIO2_367[1];
__declspec(section ".data") s32 fd_yami_togekuri_one_364[1];
BattleUnitKind unit_yami_togekuri;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_togekuri_attack[48];
static PoseTableEntry pose_table[19];
static __declspec(section ".data") BattleDataEntry data_table[3];
static s32 init_event[42];
static s32 dmg_avoid_counter_thorn_head_event[127];
static __declspec(section ".data") s32 damage_event[10];
static s32 SinTable[91];
static s32 attack_event[597];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_yami_togekuri_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_yami_togekuri_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_yami_togekuri___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_yami_togekuri___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_yami_togekuri_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_yami_togekuri___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_yami_togekuri_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_yami_togekuri_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_yami_togekuri_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_yami_togekuri___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_yami_togekuri___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_yami_togekuri_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_yami_togekuri___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_yami_togekuri_one_364[] = {
    1065353216,
};

BattleUnitKind unit_yami_togekuri = {
    155,
    "btl_un_yami_togekuri",
    7,
    0,
    1,
    1,
    13,
    0,
    2,
    70,
    0,
    50,
    9999,
    23,
    30,
    5,
    30,
    0.0f,
    15.0f,
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
    18.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    23.0f,
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
    "SFX_ENM_TOGEKURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x40000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 90, 80, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 90, 80, 90, 90, 100, 80, 100, 100, 80};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_yami_togekuri", "c_kuribo_y", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0x1, pose_table},
};

static s32 weapon_togekuri_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 20615, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "TGK_N_1"},
    {2, "TGK_Y_1"},
    {9, "TGK_Y_1"},
    {5, "TGK_K_1"},
    {4, "TGK_I_1"},
    {3, "TGK_I_1"},
    {28, "TGK_S_1"},
    {29, "TGK_Q_1"},
    {30, "TGK_Q_1"},
    {31, "TGK_S_1"},
    {39, "TGK_D_1"},
    {50, "TGK_A_1"},
    {41, "TGK_R_2"},
    {42, "TGK_R_1"},
    {40, "TGK_W_1"},
    {56, "TGK_I_1"},
    {57, "TGK_I_1"},
    {65, "TGK_T_1"},
    {69, "TGK_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_TOGEKURI_MOVE1"), STRING("SFX_ENM_TOGEKURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_TOGEKURI_MOVE1"), STRING("SFX_ENM_TOGEKURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_ENM_KURI_JUMP1"), STRING("SFX_ENM_KURI_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
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
    CALL(btlevtcmd_GetUnitId, -6, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, -6, 0, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(get_attacker, LW(0))
            IF_INT_EQUAL(LW(0), 2)
                RETURN
            END_IF
            WAIT_MS(2500)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_ChangeFaceDirection, -6, -1)
            CALL(get_attacker, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print, 2, STRING("mac_0_092_06"), 0, -6)
                ELSE
                CALL(evt_msg_print, 2, STRING("mac_0_092_07"), 0, -6)
            END_IF
            CALL(btlevtcmd_SetUnitWork, -6, 0, 1)
            CALL(btlevtcmd_ChangeFaceDirection, -6, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 SinTable[] = {
    0, 1016002431, 1024389697, 1029070406, 1032772668, 1035108056, 1037439687, 1039767156,
    1041138526, 1042296892, 1043452104, 1044603759, 1045751522, 1046894990, 1048033895, 1048871917,
    1049436235, 1049997768, 1050556282, 1051111641, 1051663679, 1052212227, 1052757117, 1053298149,
    1053835221, 1054368099, 1054896682, 1055420769, 1055940258, 1056454916, 1056964608, 1057216904,
    1057466566, 1057713526, 1057957702, 1058199008, 1058437396, 1058672780, 1058905078, 1059134238,
    1059360193, 1059582844, 1059802155, 1060018028, 1060230427, 1060439287, 1060644523, 1060846084,
    1061043904, 1061237933, 1061428086, 1061614346, 1061796631, 1061974889, 1062149053, 1062319090,
    1062484950, 1062646565, 1062803884, 1062956876, 1063105488, 1063249689, 1063389409, 1063524617,
    1063655261, 1063781325, 1063902742, 1064019511, 1064131566, 1064238873, 1064341432, 1064439176,
    1064532089, 1064620136, 1064703300, 1064781549, 1064854866, 1064923216, 1064986600, 1065044968,
    1065098337, 1065146655, 1065189940, 1065228159, 1065261310, 1065289379, 1065312347, 1065330231,
    1065342999, 1065350666, 1065353216,
};

static s32 attack_event[] = {
    196699, (s32)btlevtcmd_EnemyItemUseCheck, -2, -30000000, 131097, -30000000, 0, 65630,
    -30000000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 20, -230000000, -229999386, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_togekuri_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_togekuri_attack,
    -29999997, -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2,
    16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 2,
    33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 8,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_togekuri_attack,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_togekuri_attack, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, 80, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000,
    -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 0, -1, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    43, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 170, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0, 1, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    15, 0, 107, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999995, -29999994,
    -29999993, 131122, -29999992, 0, 65541, 28, 327771, (s32)btlevtcmd_GetPosFloat,
    -2, -29999991, -29999990, -29999989, 393307, (s32)krb_get_dir, -29999995, -29999994,
    -29999991, -29999990, -29999992, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    -29999992, 131124, -29999995, -29999991, 131124, -29999994, -29999990, 65545,
    1, 6, 109, 107, 65541, 12, 65545, 1,
    6, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 51, 109, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    2, 131126, -29999999, 4, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 28, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_togekuri_attack, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    131163, (s32)btlevtcmd_JumpContinue, -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KURI_LANDING_MISS1", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_SetDispOffset, -2, 0, -230012288, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGK_D_1", 65545, 40, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGK_A_2", 327771, (s32)btlevtcmd_SetDispOffset, -2, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 12, 0,
    110, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -250000000, -29999994, 131128,
    -29999994, 10, 131127, -29999994, -1, 131122, -29999993, 10,
    65539, 10, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999994,
    131126, -29999993, 1, 65545, 1, 131101, -29999993, 1,
    65540, 10, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"TGK_K_1",
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 112, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_MoveDirectionAdd, -2,
    -30000000, -30, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    20, -1, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0,
    65545, 40, 65540, 95, 65539, 91, 393307, (s32)evt_btl_camera_shake_h,
    0, 1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 65541, 4, 327771,
    (s32)btlevtcmd_AddScale, -2, -229999919, -230000122, 0, 65545, 1, 6,
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, (s32)weapon_togekuri_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_togekuri_attack,
    256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43, 110,
    327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -250000000, -29999994, 131128, -29999994,
    10, 131127, -29999994, -1, 131122, -29999993, 10, 65539,
    20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999994, 131126,
    -29999993, 1, 65545, 1, 131101, -29999993, 1, 65540,
    20, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131122,
    -29999999, 0, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 28, -1, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    10, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 6,
    -1, 65540, 95, 65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_ENM_KURI_MOVE1", (s32)"SFX_ENM_KURI_MOVE2", 0, 3,
    3, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 41,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -2, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

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

double hypot(double x, double y);

static u16 krb_comp_dir(f32 x, f32 z) {
    f32 dist = hypot(x, z);
    f32 s = __fabs(z) / dist;
    u16 i;
    u16 lo = 0;
    u16 hi = 90;
    u16 mid;

    for (i = 0; i < 7; i++) {
        mid = lo + (hi - lo) / 2;
        if (((f32*)SinTable)[mid] < s) {
            lo = mid;
        }
        if (!(((f32*)SinTable)[(u16)mid] < s)) {
            hi = mid;
        }
    }
    mid = __fabs(((f32*)SinTable)[lo] - s) < __fabs(((f32*)SinTable)[hi] - s) ? lo : hi;
    if (x < 0.0f && z >= 0.0f) {
        mid = 180 - mid;
    }
    if (x < 0.0f && z < 0.0f) {
        mid += 180;
    }
    if (x >= 0.0f && z < 0.0f) {
        mid = 360 - mid;
    }
    return (u16)mid;
}

static USER_FUNC(get_attacker) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit = BattleGetUnitPtr(wp, wp->activeUnitId);

    if (unit->initialKind == 0xDE) {
        evtSetValue(event, args[0], 0);
    } else if (unit->initialKind == 0xE0) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 2);
    }
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

