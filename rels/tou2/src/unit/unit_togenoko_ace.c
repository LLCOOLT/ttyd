#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetOverTurnCount);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_random);
static USER_FUNC(togenoko_getnum);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
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
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_JumpPosition[];
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
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHitOffset[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetOverTurnCount[];
extern s32 btlevtcmd_SetPartsDefenceAttrTable[];
extern s32 btlevtcmd_SetPartsDefenceTable[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRegistStatus[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetUnitWork[];
extern s32 btlevtcmd_SpawnUnit[];
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
extern s32 evt_sub_get_sincos[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_togenoko_ace_negone_one_374;
__declspec(section ".data") s32 fd_togenoko_ace_neg_one_382[1];
__declspec(section ".data") s32 fd_togenoko_ace___local_PI_383[1];
__declspec(section ".data") s32 fd_togenoko_ace___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_togenoko_ace_one_negone_373;
__declspec(section ".data") s32 fd_togenoko_ace___local_PIO2_384[1];
__declspec(section ".data") s32 fd_togenoko_ace_one_381[1];
__declspec(section ".data") u64 fd_togenoko_ace_negone_one_360;
__declspec(section ".data") s32 fd_togenoko_ace_neg_one_365[1];
__declspec(section ".data") s32 fd_togenoko_ace___local_PI_366[1];
__declspec(section ".data") s32 fd_togenoko_ace___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_togenoko_ace_one_negone_359;
__declspec(section ".data") s32 fd_togenoko_ace___local_PIO2_367[1];
__declspec(section ".data") s32 fd_togenoko_ace_one_364[1];
BattleUnitKind unit_togenoko_ace_28_data_48988;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") s32 defence_turn[2];
static __declspec(section ".data") s32 defence_attr_turn[2];
static __declspec(section ".data") s32 regist_turn[6];
static __declspec(section ".data") s32 defence_guard[2];
static __declspec(section ".data") s32 defence_attr_guard[2];
static __declspec(section ".data") s32 regist_guard[6];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_turn[15];
static PoseTableEntry pose_table_guard[15];
static PoseTableEntry pose_table_guard_turn[15];
static __declspec(section ".data") BattleDataEntry data_table[4];
static __declspec(section ".data") s32 data_table_turn[6];
static __declspec(section ".data") s32 data_table_guard[8];
static BattleUnitKindPart parts[1];
static s32 weapon_togenoko_normal_attack[48];
static s32 weapon_togenoko_shell_attack[48];
static s32 weapon_togenoko_charge[48];
static s32 init_event[37];
static __declspec(section ".data") s32 damage_event[10];
static s32 dmg_avoid_counter_thorn_head_event[61];
static s32 dmg_turn_event[116];
static s32 wakeup_event[104];
static __declspec(section ".data") s32 entry_togenoko[12];
static s32 attack_event[333];
static s32 normal_attack_event[406];
static s32 shell_attack_event[489];
static s32 charge_event[99];
static s32 guard_event[127];
static s32 guard_cancel_event[90];
static s32 friend_event[88];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_togenoko_ace_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_togenoko_ace_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_togenoko_ace___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_togenoko_ace___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_togenoko_ace_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_togenoko_ace___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_togenoko_ace_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_togenoko_ace_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_togenoko_ace_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_togenoko_ace___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_togenoko_ace___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_togenoko_ace_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_togenoko_ace___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_togenoko_ace_one_364[] = {
    1065353216,
};

BattleUnitKind unit_togenoko_ace_28_data_48988 = {
    60,
    "btl_un_togenoko_ace",
    25,
    0,
    1,
    1,
    30,
    1,
    3,
    70,
    2,
    50,
    9999,
    36,
    50,
    -4,
    50,
    0.0f,
    25.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    13.0f,
    32.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    36.0f,
    50.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_TOGENOKO_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {60, 65, 65, 100, 65, 100, 100, 60, 100, 85, 100, 85, 100, 90, 70, 60, 60, 100, 70, 100, 100, 95};

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
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {50, "A_1"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_turn[] = {
    {1, "N_2"},
    {2, "Z_2"},
    {9, "Z_2"},
    {5, "K_2"},
    {4, "S_2"},
    {3, "S_2"},
    {28, "S_2"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {39, "D_1"},
    {56, "S_2"},
    {57, "S_2"},
    {65, "S_2"},
    {69, "S_2"},
};

static PoseTableEntry pose_table_guard[] = {
    {1, "A_1"},
    {2, "A_1"},
    {9, "A_1"},
    {5, "A_1"},
    {4, "A_1"},
    {3, "A_1"},
    {28, "A_1"},
    {29, "A_1"},
    {30, "A_1"},
    {31, "A_1"},
    {39, "A_1"},
    {56, "A_1"},
    {57, "A_1"},
    {65, "A_1"},
    {69, "A_1"},
};

static PoseTableEntry pose_table_guard_turn[] = {
    {1, "G_1"},
    {2, "G_1"},
    {9, "G_1"},
    {5, "G_1"},
    {4, "G_1"},
    {3, "G_1"},
    {28, "G_1"},
    {29, "G_1"},
    {30, "G_1"},
    {31, "G_1"},
    {39, "G_1"},
    {56, "G_1"},
    {57, "G_1"},
    {65, "G_1"},
    {69, "G_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {37, dmg_avoid_counter_thorn_head_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static __declspec(section ".data") s32 data_table_turn[] = {
    13, (s32)dmg_turn_event, 48, (s32)btldefaultevt_Dummy, 0, 0,
};

static __declspec(section ".data") s32 data_table_guard[] = {
    37, (s32)dmg_avoid_counter_thorn_head_event, 13, (s32)dmg_turn_event, 48, (s32)btldefaultevt_Dummy, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_togenoko_ace", "c_togenoko_b", 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x1009, 0x1, pose_table},
};

static s32 weapon_togenoko_normal_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 525058, 0, 135, 2, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_togenoko_shell_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536887300, 525058, 0, 135, 1535, 8192,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_togenoko_charge[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 5,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_TOGENOKO_MOVE3"), STRING("SFX_ENM_TOGENOKO_MOVE4"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_TOGENOKO_MOVE3"), STRING("SFX_ENM_TOGENOKO_MOVE4"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 70)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 40)
        GOTO(90)
    END_IF
    ADD(LW(1), 55)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static s32 dmg_turn_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 393307, (s32)btlevtcmd_SetHitOffset,
    -29999990, -29999989, 0, -20, 0, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990,
    -29999989, (s32)defence_turn, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990, -29999989, (s32)defence_attr_turn, 196699,
    (s32)btlevtcmd_SetRegistStatus, -29999990, (s32)regist_turn, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000,
    131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table_turn,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 39, 32, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -29999990, -29999989, (s32)pose_table_guard_turn, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 69,
    33, 196699, (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table_turn, 196699, (s32)btlevtcmd_OnStatusFlag, -29999990,
    1, 262235, (s32)btlevtcmd_OffPartsCounterAttribute, -29999990, -29999989, 1, 196699, (s32)btlevtcmd_SetOverTurnCount,
    -29999990, 2, 65545, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE1",
    -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -29999990,
    -30000000, -29999999, -29999998, 15, -1, 458843, (s32)btlevtcmd_JumpPosition, -29999990,
    -30000000, -29999999, -29999998, 10, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990,
    -29999989, 69, 2, 1,
};

static s32 wakeup_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_GetOverTurnCount,
    -29999990, -30000000, 131126, -30000000, 1, 196699, (s32)btlevtcmd_SetOverTurnCount, -29999990,
    -30000000, 131097, -30000000, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -29999990, 2,
    33, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)&defence, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable,
    -29999990, -29999989, (s32)&defence_attr, 196699, (s32)btlevtcmd_SetRegistStatus, -29999990, (s32)&regist, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table,
    196699, (s32)btlevtcmd_OffStatusFlag, -29999990, 1, 262235, (s32)btlevtcmd_OnPartsCounterAttribute, -29999990, -29999989,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_INSIDE2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"S_1", 196699, (s32)btlevtcmd_SetFallAccel, -29999990,
    -229998976, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998, 12, -1, 393307,
    (s32)btlevtcmd_SetHitOffset, -29999990, -29999989, 0, 0, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -29999990, 2, 1,
};

static __declspec(section ".data") s32 entry_togenoko[] = {
    (s32)&unit_togenoko_ace_28_data_48988, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(weapon_togenoko_normal_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetOverTurnCount, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(wakeup_event))
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(0), 80)
        ADD(LW(0), 20)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 80)
            CALL_CHILD(PTR(guard_cancel_event))
            GOTO(99)
        END_IF
        GOTO(99)
        ELSE
        CALL(btlevtcmd_CheckStatus, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(0), 0)
            ADD(LW(0), 50)
            ADD(LW(0), 35)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 50)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_togenoko_normal_attack))
                CALL_CHILD(PTR(normal_attack_event))
                GOTO(99)
            END_IF
            SET_VALUE(LW(9), PTR(weapon_togenoko_shell_attack))
            CALL_CHILD(PTR(shell_attack_event))
            GOTO(99)
        END_IF
        CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, -2)
            RETURN
        END_IF
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
                    GOTO(10)
                END_IF
                ELSE
                GOTO(9)
            END_IF
        END_LOOP
        LABEL(9)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 40)
            IF_INT_LESS_OR_EQUAL(LW(0), 130)
                ADD(LW(2), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    GOTO(10)
                END_IF
                ELSE
                GOTO(11)
            END_IF
        END_LOOP
        LABEL(10)
        CALL(togenoko_getnum, LW(10))
        CALL(evt_sub_random, 99, LW(11))
        SWITCH(LW(10))
            CASE_EQUAL(1)
            IF_INT_LESS(LW(11), 0)
                CALL_CHILD(PTR(friend_event))
                GOTO(99)
            END_IF
            CASE_END
            CASE_EQUAL(2)
            IF_INT_LESS(LW(11), 0)
                CALL_CHILD(PTR(friend_event))
                GOTO(99)
            END_IF
            CASE_END
            CASE_EQUAL(3)
            IF_INT_LESS(LW(11), 0)
                CALL_CHILD(PTR(friend_event))
                GOTO(99)
            END_IF
            CASE_END
        END_SWITCH
        LABEL(11)
        SET_VALUE(LW(0), 0)
        ADD(LW(0), 50)
        ADD(LW(0), 35)
        ADD(LW(0), 15)
        ADD(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        SET_VALUE(LW(0), 50)
        IF_INT_LESS(LW(1), LW(0))
            SET_VALUE(LW(9), PTR(weapon_togenoko_normal_attack))
            CALL_CHILD(PTR(normal_attack_event))
            GOTO(99)
        END_IF
        ADD(LW(0), 35)
        IF_INT_LESS(LW(1), LW(0))
            SET_VALUE(LW(9), PTR(weapon_togenoko_shell_attack))
            CALL_CHILD(PTR(shell_attack_event))
            GOTO(99)
        END_IF
        ADD(LW(0), 15)
        IF_INT_LESS(LW(1), LW(0))
            SET_VALUE(LW(9), PTR(weapon_togenoko_charge))
            CALL_CHILD(PTR(charge_event))
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
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 65546,
    750, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 33, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 110, 65541, 10, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGENOKO_MOVE3", -250000000, 0, -250000000, 65545, 3, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGENOKO_MOVE4", -250000000, 0, -250000000, 65545, 3, 6,
    112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_3", 65545, 60,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_MOVE5", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 10,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    0, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 500, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, 0, -29999998, 0, -1, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1",
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, 300, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229989760, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1",
    65540, 98, 65539, 91, 393307, (s32)evt_btl_camera_shake_h, 0, 1,
    1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_add_zoom, 0, -50, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -29999990, -29999989, -29999988,
    131131, -29999990, -30000000, 131131, -29999989, -29999999, 131131, -29999988,
    -29999998, 131132, -29999990, -229999232, 131132, -29999989, -229999232, 131132,
    -29999988, -229999232, 131130, -30000000, -29999990, 131130, -29999999, -29999989,
    131130, -29999998, -29999988, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, 0,
    -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_MOVE6", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 20, 0, -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_MOVE6",
    -250000000, 0, -250000000, 65540, 98, 65539, 98, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65546, 500, 2, 1,
};

static s32 shell_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 65546, 100, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGENOKO_MOVE1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_JumpSetting, -2, 20,
    -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 0, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_SHELL1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_MOVE2",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 10, 110, 65541, 0,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999985, 131096, -29999985, 1,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 7, 33,
    65545, 1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999986, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, -29999986, 0, 6, 112, 65546,
    200, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 20, 65546, 200,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 40, 65546, 200, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 65647, -29999987, 65541, 0, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 10,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 0, -30000000, -29999999, -29999998,
    -229999693, 0, 0, 0, 0, 0, 0, 0,
    65545, 3, 6, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229987712,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_GetPos, -2, -250000000, -29999995, -250000000, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999995, -29999998, 0, 0, 0, 131122, -29999994,
    0, 65539, 10, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229987712, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -2, -250000000, -29999995, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 100, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999995, -29999998, 0, 0, 0, 65540, 97,
    65539, 91, 131096, -29999994, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 131122, -29999994, 1, 33, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65540, 97, 65539,
    97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097, -29999997, -1,
    65540, 10, 33, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 500, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229987712, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, 0, 0, 65546, 500, 327771, (s32)btlevtcmd_SetPos, -2,
    250, -29999999, -29999998, 65539, 98, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGENOKO_ATTACK1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229987712,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, 0, 0, 65631,
    -29999987, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_SHELL2", -250000000, 0, -250000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_ATTACK2", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -229989760, -229999591, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1,
    65545, 3, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

static s32 charge_event[] = {
    131122, -29999997, -2, 131122, -29999996, 1, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_togenoko_charge, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_togenoko_charge, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_CHARGE1", -250000000,
    0, -250000000, 110, 65541, 8, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_TOGENOKO_MOVE3", -250000000, 0, -250000000, 65545, 3, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_TOGENOKO_MOVE4", -250000000, 0, -250000000, 65545, 3, 6,
    112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_3", 65545, 48,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 107, 65545, 60,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 109, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    (s32)weapon_togenoko_charge, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_togenoko_charge, 256,
    -29999995, 2, 1,
};

static s32 guard_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 110, 65545,
    10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_SHELL1", -250000000, 0, -250000000,
    65545, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"A_1", 112,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_MOVE1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -29999990,
    20, 0, -229999488, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999,
    -29999998, 20, -1, 131124, -29999988, -229969280, 131124, -29999987,
    -230000000, 65541, 15, 262235, (s32)evt_sub_get_sincos, -29999987, -29999986, -29999985,
    131132, -29999986, -29999988, 327771, (s32)btlevtcmd_SetRotate, -29999990, 0, 0,
    -29999986, 131131, -29999988, -229997952, 131130, -29999987, -229969280, 65545,
    1, 6, 327771, (s32)btlevtcmd_SetRotate, -29999990, 0, 0, 0,
    262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)defence_guard, 262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990,
    -29999989, (s32)defence_attr_guard, 196699, (s32)btlevtcmd_SetRegistStatus, -29999990, (s32)regist_guard, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -29999990, -29999989, (s32)pose_table_guard, 196699, (s32)btlevtcmd_ChangeDataTable, -29999990, (s32)data_table_guard, 262235,
    (s32)btlevtcmd_SetUnitWork, -29999990, 0, 1, 393307, (s32)btlevtcmd_SetHitOffset, -29999990, -29999989,
    0, -20, 0, 65546, 300, 2, 1,
};

static s32 guard_cancel_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 110, 65545,
    10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_SHELL2", -250000000, 0, -250000000,
    65545, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"S_1", 112,
    327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting,
    -29999990, 20, 0, -229999488, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000,
    -29999999, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_MOVE6",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -29999990, -29999989, (s32)&defence,
    262235, (s32)btlevtcmd_SetPartsDefenceAttrTable, -29999990, -29999989, (s32)&defence_attr, 196699, (s32)btlevtcmd_SetRegistStatus, -29999990,
    (s32)&regist, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -29999990, -29999989, (s32)pose_table, 196699, (s32)btlevtcmd_ChangeDataTable,
    -29999990, (s32)data_table, 262235, (s32)btlevtcmd_SetUnitWork, -29999990, 0, 0, 393307,
    (s32)btlevtcmd_SetHitOffset, -29999990, -29999989, 0, 0, 0, 65546, 300,
    2, 1,
};

static s32 friend_event[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_TOGENOKO_CALL1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"B_1", 65545, 40, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_togenoko,
    0, 327771, (s32)btlevtcmd_SetPos, -29999997, 300, -29999999, -29999998, 65545,
    10, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, 1, (s32)"R_1", 196699, (s32)btlevtcmd_SetMoveSpeed,
    -29999997, 8, 524379, (s32)btlevtcmd_MovePosition, -29999997, -30000000, -29999999, -29999998,
    0, -1, 0, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, 1, (s32)"S_1", 65546, 500,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 300, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static USER_FUNC(togenoko_getnum) {
    s32* args = event->args;
    s32 num = 0;
    s32 i;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, i);
        if (unit != NULL && unit->currentKind == 0x3C) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}
