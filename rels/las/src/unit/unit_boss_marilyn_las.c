#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SortPhaseMoveTable);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_msg_print);
extern s32 battle_evt_majo_disp_off[];
extern s32 battle_evt_majo_disp_on[];
extern s32 btl_marilyn_zoom_17_data_5C2B8[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetWidth[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff64[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_snd_sfxon[];
extern s32 evt_sub_random[];
extern s32 evt_sub_rumble_onoff[];
extern s32 majo3_shadow_tail_event_17_data_5E094[];
extern s32 majo_unison_phase_event_17_data_5C5E4[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_dead_core_nospin_norotate[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_marilyn_las_negone_one_374;
__declspec(section ".data") s32 fd_boss_marilyn_las_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_marilyn_las___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_marilyn_las___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_marilyn_las_one_negone_373;
__declspec(section ".data") s32 fd_boss_marilyn_las___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_marilyn_las_one_381[1];
__declspec(section ".data") u64 fd_boss_marilyn_las_negone_one_360;
__declspec(section ".data") s32 fd_boss_marilyn_las_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_marilyn_las___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_marilyn_las___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_marilyn_las_one_negone_359;
__declspec(section ".data") s32 fd_boss_marilyn_las___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_marilyn_las_one_364[1];
BattleUnitKind unit_boss_marilyn_las;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 weapon_marilyn_kagenuke_attack1[48];
static s32 weapon_marilyn_thunder_attack1[48];
static s32 weapon_marilyn_charge1[48];
static s32 marilyn_down[19];
static s32 marilyn_up[27];
static s32 init_event[37];
static s32 damage_event[22];
static s32 dead_event[152];
static s32 unison_phase_event[83];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[93];
static s32 kagenuke_attack_event[238];
static s32 thunder_attack_event[235];
static s32 charge_attack_event[58];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boss_marilyn_las_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_marilyn_las_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_marilyn_las___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_marilyn_las___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_marilyn_las_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_marilyn_las___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_marilyn_las_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_marilyn_las_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_marilyn_las_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_marilyn_las___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_marilyn_las___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_marilyn_las_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_marilyn_las___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_marilyn_las_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_marilyn_las = {
    134,
    "btl_un_marilyn4",
    40,
    0,
    1,
    1,
    57,
    0,
    0,
    100,
    0,
    50,
    7,
    40,
    54,
    0,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    0,
    6.0f,
    24.0f,
    0.0f,
    20.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    0.0f,
    16.0f,
    35.1f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    40.0f,
    54.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MARI_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {50, 50, 50, 100, 50, 100, 100, 40, 100, 60, 100, 60, 100, 80, 40, 0, 0, 100, 40, 100, 100, 5};

static PoseTableEntry pose_table[] = {
    {1, "MRR_N_1"},
    {2, "MRR_Z_1"},
    {9, "MRR_Z_1"},
    {5, "MRR_X_1"},
    {4, "MRR_X_1"},
    {3, "MRR_X_1"},
    {28, "MRR_S_1"},
    {29, "MRR_Q_2"},
    {30, "MRR_Q_2"},
    {31, "MRR_D_1"},
    {39, "MRR_D_1"},
    {50, "MRR_S_1"},
    {42, "MRR_R_1"},
    {40, "MRR_W_1"},
    {56, "MRR_S_1"},
    {57, "MRR_S_1"},
    {65, "MRR_T_1"},
    {69, "MRR_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_marilyn4", "c_maririn", 0.0f, 0.0f, 0.0f, 15.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 38, 56, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_marilyn_kagenuke_attack1[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_marilyn_thunder_attack1[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 131140, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_marilyn_charge1[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 7,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 marilyn_down[] = {
    107, 65546, 250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MARI_SHADOW1", -250000000,
    0, -250000000, 109, 327771, (s32)battle_evt_majo_disp_off, -2, 1, 0,
    0, 2, 1,
};

static s32 marilyn_up[] = {
    107, 65546, 250, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MARI_SHADOW2", -250000000,
    0, -250000000, 109, 458843, (s32)battle_evt_majo_disp_on, -2, 1, -30000000,
    -29999999, -29999998, 0, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 8, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    SPAWN_EVENT(PTR(majo3_shadow_tail_event_17_data_5E094))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(12), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, -2, LW(3), LW(4), LW(5))
    SET_VALUE(LW(6), 1)
    IF_INT_EQUAL(LW(0), LW(3))
        IF_INT_EQUAL(LW(1), LW(4))
            IF_INT_EQUAL(LW(2), LW(5))
                SET_VALUE(LW(6), 0)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LW(6), 1)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
        CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_ResetFaceDirection, -2)
    END_IF
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    SWITCH(GW(11))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        LOOP(0)
            IF_INT_EQUAL(GW(11), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        GOTO(99)
        CASE_EQUAL(2)
        SWITCH(GW(13))
            CASE_EQUAL(0)
            CASE_DEFAULT
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL_CHILD(PTR(btl_marilyn_zoom_17_data_5C2B8))
            CALL(btlevtcmd_SetTalkPose, -2, STRING("MRR_D_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("MRR_D_1"))
            CALL(evt_msg_print, 2, STRING("btl_majo3_12"), 0, -2)
            GOTO(90)
        END_SWITCH
    END_SWITCH
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL_CHILD(PTR(btl_marilyn_zoom_17_data_5C2B8))
    CALL(btlevtcmd_SetTalkPose, -2, STRING("MRR_D_1"))
    CALL(btlevtcmd_SetStayPose, -2, STRING("MRR_D_1"))
    CALL(evt_msg_print, 2, STRING("btl_majo3_09"), 0, -2)
    LABEL(90)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    LABEL(99)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("MRR_D_3"))
    SET_VALUE(GW(12), 2)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(majo_unison_phase_event_17_data_5C5E4))
        CALL(btlevtcmd_GetUnitWork, -2, 4, LW(3))
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, -2, 4, LW(4))
            CALL(btlevtcmd_StartWaitEvent, -2)
            WAIT_MS(200)
            CALL_CHILD(PTR(marilyn_down))
            WAIT_MS(500)
            SWITCH(LW(4))
                CASE_EQUAL(0)
                SET_VALUE(LW(0), 55)
                SET_VALUE(LW(2), 0)
                CASE_EQUAL(1)
                SET_VALUE(LW(0), 105)
                SET_VALUE(LW(2), 10)
                CASE_EQUAL(2)
                SET_VALUE(LW(0), 155)
                SET_VALUE(LW(2), 20)
            END_SWITCH
            SET_VALUE(LW(1), 0)
            CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), LW(2))
            CALL_CHILD(PTR(marilyn_up))
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(2), 0)
    CALL(btlevtcmd_GetUnitWork, -2, 9, LW(0))
    IF_INT_LESS(LW(0), 2)
        SET_VALUE(LW(2), 25)
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 3, 40, 35, LW(2))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, -2, 9, 0)
        SET_VALUE(LW(9), PTR(weapon_marilyn_kagenuke_attack1))
        CALL_CHILD(PTR(kagenuke_attack_event))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, -2, 9, 0)
        SET_VALUE(LW(9), PTR(weapon_marilyn_thunder_attack1))
        CALL_CHILD(PTR(thunder_attack_event))
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetUnitWork, -2, 9, LW(0))
        ADD(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, -2, 9, LW(0))
        SET_VALUE(LW(9), PTR(weapon_marilyn_charge1))
        CALL_CHILD(PTR(charge_attack_event))
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 kagenuke_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MARI_ARM_FOLD1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A1_1", 65630, (s32)marilyn_down, 65546,
    300, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 30, 131122, -29999999, 0, 65630,
    (s32)marilyn_up, 65546, 600, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MARI_HAND_CLAP1", -250000000,
    0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A2_1", 65545,
    4, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A2_2", 65546, 350,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A2_3", 65546, 100, 131163,
    (s32)evt_snd_sfxoff, -29999985, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 98,
    65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65539, 98,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A2_4", 65546, 400, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A1_1", 65630, (s32)marilyn_down, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 65546, 200, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 65630, (s32)marilyn_up, 2, 1,
};

static s32 thunder_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MARI_POWER1", -250000000, 0,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A3_1", 65546, 800,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A3_2", 65546, 150, 131163,
    (s32)evt_snd_sfxoff, -29999985, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990,
    0, 65539, 10, 196699, (s32)evt_sub_random, 2, -29999993, 131125,
    -29999993, 3, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_GetWidth, -29999997, -29999995, 196699, (s32)btlevtcmd_GetHeight, -29999997,
    -29999994, 983131, (s32)evt_eff64, (s32)"", (s32)"thunder_n64", -29999993, -30000000, -29999999,
    -29999998, -29999995, -29999994, 0, 0, 0, 0, 0,
    0, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_MARI_ATTACK_THUNDER1", 0, 393307, (s32)evt_btl_camera_shake_h, 0,
    3, 0, 25, 13, 107, 196699, (s32)evt_sub_rumble_onoff, 0,
    0, 65546, 300, 196699, (s32)evt_sub_rumble_onoff, 1, 0, 109,
    65546, 83, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 97,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546,
    1000, 2, 1,
};

static s32 charge_attack_event[] = {
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 7,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 65546, 300, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MRR_A3_1", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MARI_CHARGE1\0\0",
    -250000000, 0, -29999985, 65546, 800, 107, 65546, 1000,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 109, 131163, (s32)evt_snd_sfxoff, -29999985,
    458843, (s32)btlevtcmd_CheckDamage, -2, -2, 1, -29999991, 256, -29999995,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

