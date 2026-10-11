#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_JumpSetting);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetScale);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_sub_random);
static USER_FUNC(chorobon_copy_status);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AddScale[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeSetMotionSpeed[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHpDamage[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckCounter[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RecoverFp[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMoveSoundDataWork[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SpawnUnit[];
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
extern s32 evt_eff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_counter_damage[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_green_chorobon_negone_one_374;
__declspec(section ".data") s32 fd_green_chorobon_neg_one_382[1];
__declspec(section ".data") s32 fd_green_chorobon___local_PI_383[1];
__declspec(section ".data") s32 fd_green_chorobon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_green_chorobon_one_negone_373;
__declspec(section ".data") s32 fd_green_chorobon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_green_chorobon_one_381[1];
__declspec(section ".data") u64 fd_green_chorobon_negone_one_360;
__declspec(section ".data") s32 fd_green_chorobon_neg_one_365[1];
__declspec(section ".data") s32 fd_green_chorobon___local_PI_366[1];
__declspec(section ".data") s32 fd_green_chorobon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_green_chorobon_one_negone_359;
__declspec(section ".data") s32 fd_green_chorobon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_green_chorobon_one_364[1];
BattleUnitKind unit_green_chorobon_28_data_22E58;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static s32 weapon_chorobon_drain_attack[48];
static s32 attack_event[139];
static __declspec(section ".data") s32 entry_chorobon[12];
static s32 friend_event[223];
static s32 weapon_chorobon_drain_attack_biribiri_counterd[48];
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[14];
static s32 rabbit_move[123];
static s32 pose_sound_timing_table[20];
static s32 init_event[31];
static __declspec(section ".data") s32 damage_event[10];
static s32 counter_damage_event[41];
static s32 return_event[24];
static s32 drain_attack_event[887];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_green_chorobon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_green_chorobon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_green_chorobon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_green_chorobon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_green_chorobon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_green_chorobon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_green_chorobon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_green_chorobon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_green_chorobon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_green_chorobon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_green_chorobon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_green_chorobon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_green_chorobon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_green_chorobon_one_364[] = {
    1065353216,
};

BattleUnitKind unit_green_chorobon_28_data_22E58 = {
    86,
    "btl_un_green_chorobon",
    5,
    0,
    1,
    1,
    19,
    0,
    3,
    70,
    0,
    60,
    9999,
    28,
    32,
    5,
    32,
    0.0f,
    16.0f,
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
    9.0f,
    20.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    28.0f,
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
    "SFX_ENM_CHORO2_DAMAGED1",
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

static __declspec(section ".data") StatusVulnerability regist = {85, 85, 80, 100, 85, 100, 100, 70, 100, 90, 100, 90, 100, 95, 60, 85, 80, 100, 80, 100, 100, 95};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_green_chorobon", "c_chorobon_g", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_chorobon_drain_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 71, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    LABEL(0)
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 50)
        CALL_CHILD(PTR(drain_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 40)
        IF_INT_LESS_OR_EQUAL(LW(0), 170)
            ADD(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(PTR(friend_event))
                WAIT_MS(500)
                GOTO(99)
            END_IF
            ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
        SET_VALUE(LW(4), LW(0))
        CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
        MULTIPLY(LW(4), LW(5))
        IF_INT_LESS(LW(4), 0)
            SUBTRACT(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(PTR(friend_event))
                WAIT_MS(500)
                GOTO(99)
            END_IF
            ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") s32 entry_chorobon[] = {
    (s32)&unit_green_chorobon_28_data_22E58, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static s32 friend_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"CBN_K_1",
    131122, -29999988, 120, 131122, -29999987, 45, 131122, -29999986,
    10, 131122, -29999985, 10, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    10, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_SPLIT1", -250000000, 0,
    -250000000, 65541, 0, 65545, 1, 131126, -29999988, 1,
    131100, -29999988, 1, 7, 33, 131126, -29999986, 1,
    131100, -29999986, 0, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -29999987, 131126, -29999985, 1, 131122, -29999986, -29999985, 131096,
    -29999985, 7, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_SPLIT1_2", -250000000, 0,
    -250000000, 33, 33, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"CBN_S_1", 327771, (s32)btlevtcmd_GetPos, -2,
    -29999993, -29999992, -29999991, 110, 327771, (s32)btlevtcmd_JumpSetting, -2, 0,
    10, -229999488, 458843, (s32)btlevtcmd_JumpPosition, -2, -29999993, -29999992, -29999991,
    -229979520, -1, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_SPLIT2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_chorobon, 0, 196699,
    (s32)chorobon_copy_status, -2, -29999997, 327771, (s32)btlevtcmd_SetPos, -29999997, -29999993, -29999992,
    -29999991, 327771, (s32)btlevtcmd_JumpSetting, -29999997, 0, 10, -229999488, 110,
    327771, (s32)btlevtcmd_SetRotateOffset, -29999997, 0, 10, 0, 131122, -29999988,
    0, 65541, 0, 65545, 1, 131125, -29999988, 1,
    131101, -29999988, 30, 7, 33, 327771, (s32)btlevtcmd_AddRotate, -29999997,
    0, 0, 20, 6, 327771, (s32)btlevtcmd_SetRotate, -29999997, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -29999997, 0, 0, 0,
    112, 458843, (s32)btlevtcmd_JumpPosition, -29999997, -30000000, -29999999, -29999998, -229969280,
    -1, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 65546,
    1000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static s32 weapon_chorobon_drain_attack_biribiri_counterd[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 0, 0, 8192,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "CBN_N_1"},
    {2, "CBN_Y_1"},
    {9, "CBN_Y_1"},
    {5, "CBN_K_1"},
    {4, "CBN_X_1"},
    {3, "CBN_X_1"},
    {28, "CBN_S_1"},
    {29, "CBN_Q_1"},
    {30, "CBN_Q_1"},
    {31, "CBN_S_1"},
    {39, "CBN_D_1"},
    {50, "CBN_A_1"},
    {42, "CBN_R_1"},
    {40, "CBN_W_1"},
    {56, "CBN_X_1"},
    {57, "CBN_X_1"},
    {65, "CBN_T_1"},
    {69, "CBN_S_1"},
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
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static s32 rabbit_move[] = {
    65541, 2, 327771, (s32)btlevtcmd_AddScale, -2, -229999837, -230000245, 0,
    65545, 1, 6, 65539, 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131122, -29999989, -29999995, 131126, -29999989,
    -30000000, 131122, -29999988, -29999989, 131098, -29999988, 0, 131127,
    -29999988, -1, 33, 131099, -29999988, -29999992, 131101, -29999989,
    0, 131125, -30000000, -29999992, 32, 131126, -30000000, -29999992,
    33, 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999994, -29999998, 0, -1, 65541,
    2, 327771, (s32)btlevtcmd_AddScale, -2, -229999837, -230000245, 0, 65545,
    1, 6, 65540, 0, 32, 327771, (s32)btlevtcmd_SetScale, -2,
    -229998976, -229998976, -229998976, 458843, (s32)btlevtcmd_JumpPosition, -2, -29999995, -29999994,
    -29999993, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_LANDING1", -250000000,
    0, -250000000, 65541, 2, 327771, (s32)btlevtcmd_AddScale, -2, -229999837,
    -230000245, 0, 65545, 1, 6, 33, 65541, 2,
    327771, (s32)btlevtcmd_AddScale, -2, -230000163, -229999755, 0, 65545, 1,
    6, 2, 1,
};

static s32 pose_sound_timing_table[] = {
    (s32)"CBN_S_1", 1058362709, 0, (s32)"SFX_ENM_CHORO2_MOVE1", 1, (s32)"CBN_S_1", 1062557013, 0,
    (s32)"SFX_ENM_CHORO2_WAIT2", 1, (s32)"CBN_S_1", 1070246571, 0, (s32)"SFX_ENM_CHORO2_WAIT1", 1, 0,
    0, 0, 0, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, -2, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_ENM_CHORO2_MOVE1"), 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(counter_damage_event)
    CALL(btlevtcmd_SetScale, -2, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    CALL_CHILD(PTR(subsetevt_counter_damage))
    CALL(btlevtcmd_CheckDamageCode, -2, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, -2, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL_CHILD(PTR(return_event))
    RETURN
EVT_END()

static EVT_BEGIN(return_event)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_JumpSetting, -2, 0, FLOAT(4.0f), FLOAT(0.5996094f))
    CALL(btlevtcmd_GetHomePos, -2, LW(5), LW(6), LW(7))
    SET_VALUE(LW(8), 40)
    CALL_CHILD(PTR(rabbit_move))
    RETURN
EVT_END()

static s32 drain_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_chorobon_drain_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_chorobon_drain_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_chorobon_drain_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_chorobon_drain_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229995904, -229999386, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999995, -29999994, -29999993, 131122, -29999994, 0,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -29999995, 50, 131122, -29999992, 50,
    65630, (s32)rabbit_move, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 350, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_JumpSetting, -2, 60, 0,
    -229999284, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 5, 131126, -29999999, 10,
    131126, -29999998, 2, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    (s32)weapon_chorobon_drain_attack, 256, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 49, 65539, 90, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 0, -229996928, -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 5,
    131122, -29999999, 0, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229998464,
    -229999796, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 30, 131122, -29999999, 0, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"CBN_N_1", 65546, 1000, 65540, 98, 65539,
    91, 131122, -70000000, 0, 458843, (s32)btlevtcmd_PreCheckCounter, -2, -29999997,
    -29999996, (s32)weapon_chorobon_drain_attack, 256, -29999995, 131096, -29999995, 17, 131122,
    -70000000, 1, 33, 131096, -29999995, 14, 131122, -70000000,
    1, 33, 131096, -70000000, 1, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_chorobon_drain_attack, 131122,
    -29999991, (s32)weapon_chorobon_drain_attack_biribiri_counterd, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 2, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_ATTACK1_1",
    -250000000, 0, -250000000, 196699, (s32)btlevtcmd_GetBodyId, -29999997, -30000000, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999997, -30000000, 37, 107, 131122, -30000000, 89,
    131122, -29999999, 1, 131122, -29999998, 2, 131122, -29999995,
    -29999998, 65539, 20, 131126, -29999995, 1, 131100, -29999995,
    0, 131122, -29999995, -29999998, 131096, -29999999, 0, 131122,
    -29999999, 1, 32, 131122, -29999999, 0, 33, 33,
    327771, (s32)btlevtcmd_SetDispOffset, -29999997, -29999999, 0, 0, 65545, 1,
    131126, -30000000, 1, 131101, -30000000, 1, 65540, 20,
    33, 327771, (s32)btlevtcmd_SetDispOffset, -29999997, 0, 0, 0, 109,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_ATTACK1_2", -250000000, 0, -250000000, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131122, -29999986, 20, 131096, -29999985,
    -1, 131122, -29999986, -20, 33, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, -29999986, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998464,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"CBN_A_2", 65545, 90, 262235,
    (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"CBN_R_2", 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 65541,
    4, 65545, 1, 327771, (s32)btlevtcmd_AddScale, -2, 0, -230000204,
    0, 6, 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229999796, -229998976,
    65541, 20, 65545, 1, 327771, (s32)btlevtcmd_AddScale, -2, -230000010,
    -229999949, 0, 6, 65545, 1, 327771, (s32)btlevtcmd_SetScale, -2,
    -229998976, -229998976, -229998976, 393307, (s32)evt_btl_camera_shake_h, 0, 1, 1,
    8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_add_zoom,
    0, -50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_ATTACK2", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_chorobon_drain_attack, 131122, -29999991, (s32)weapon_chorobon_drain_attack, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 196699, (s32)btlevtcmd_GetHpDamage,
    -29999997, -29999990, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 131101,
    -29999990, 1, 327771, (s32)btlevtcmd_AddScale, -2, -229999488, -229999488, 0,
    33, 65541, 4, 327771, (s32)btlevtcmd_AddScale, -2, -230000081, -229999878,
    0, 65545, 1, 6, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_AddScale, -2, -229999673, -230000491,
    0, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20,
    -1, 65541, 2, 327771, (s32)btlevtcmd_AddScale, -2, -229999837, -230000245,
    0, 65545, 1, 6, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 327771, (s32)btlevtcmd_AddScale, -2, -230000327, -229999509, 0, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 10, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_CHORO2_LANDING1", -250000000, 0, -250000000, 65541, 2,
    327771, (s32)btlevtcmd_AddScale, -2, -229999837, -230000245, 0, 65545, 1,
    6, 65541, 2, 327771, (s32)btlevtcmd_AddScale, -2, -230000163, -229999755,
    0, 65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"CBN_W_1", 131101, -29999990, 1, 65541, 20, 327771, (s32)btlevtcmd_AddScale,
    -2, -230000025, -230000025, 0, 65545, 1, 6, 196699,
    (s32)btlevtcmd_GetBodyId, -2, -29999999, 327771, (s32)btlevtcmd_GetPos, -2, -29999995, -29999994,
    -29999993, 131125, -29999994, 45, 131125, -29999993, 10, 131096,
    -29999991, (s32)weapon_chorobon_drain_attack, 262235, (s32)btlevtcmd_RecoverHp, -2, -29999999, -29999990, 983131,
    (s32)evt_eff, (s32)"", (s32)"recovery", 7, -29999995, -29999994, -29999993, -29999990,
    0, 0, 0, 0, 0, 0, 0, 32,
    262235, (s32)btlevtcmd_RecoverFp, -2, -29999999, -29999990, 983131, (s32)evt_eff, (s32)"",
    (s32)"recovery", 8, -29999995, -29999994, -29999993, -29999990, 0, 0,
    0, 0, 0, 0, 0, 33, 327771, (s32)btlevtcmd_SetScale,
    -2, -229998976, -229998976, -229998976, 33, 65541, 2, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 30,
    589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_ENM_CHORO2_ATTACK3", 0, 0, -1, -1,
    0, 0, 65541, 2, 327771, (s32)btlevtcmd_AddScale, -2, -229999837,
    -230000245, 0, 65545, 1, 6, 327771, (s32)btlevtcmd_SetScale, -2,
    -229998976, -229998976, -229998976, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 6, -2, 65545, 16, 65541, 2, 327771,
    (s32)btlevtcmd_AddScale, -2, -229999837, -230000245, 0, 65545, 1, 6,
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 589915, (s32)btlevtcmd_SetMoveSoundDataWork,
    -2, 0, 0, 0, -1, -1, 0, 0,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 6, -2,
    6, 65541, 2, 327771, (s32)btlevtcmd_AddScale, -2, -229999837, -230000245,
    0, 65545, 1, 6, 65541, 2, 327771, (s32)btlevtcmd_AddScale,
    -2, -230000163, -229999755, 0, 65545, 1, 6, 65540,
    98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_nomove_y_onoff, 0, 0, 65630,
    (s32)return_event, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static USER_FUNC(chorobon_copy_status) {
    s32* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->currentHp = unit1->currentHp;
    if (unit2->currentHp > unit2->maxHp) {
        unit2->currentHp = unit2->maxHp;
    }
    unit2->mSizeChangeTurns = unit1->mSizeChangeTurns;
    unit2->mSizeChangeStrength = unit1->mSizeChangeStrength;
    unit2->hpGauge.field_0xC = unit2->currentHp;
    unit2->hpGauge.field_0x10 = unit2->currentHp;
    unit2->hpGauge.field_0x14 = unit2->hpGauge.field_0x18 = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

