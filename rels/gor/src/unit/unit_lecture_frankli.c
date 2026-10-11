#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(btlevtcmd_onoff_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_SuitoruBadgeEffect[];
extern s32 btlevtcmd_ACSuccessEffect[];
extern s32 btlevtcmd_AcGetOutputParam[];
extern s32 btlevtcmd_AcGetParam[];
extern s32 btlevtcmd_AcSetDifficulty[];
extern s32 btlevtcmd_AcSetFlag[];
extern s32 btlevtcmd_AcSetParam[];
extern s32 btlevtcmd_AcSetParamAll[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetDamage[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultCountAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_InviteApInfoReport[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PadCheckNow[];
extern s32 btlevtcmd_PadCheckTrigger[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ac_timing_flag_onoff[];
extern s32 btlevtcmd_ac_timing_get_success_frame[];
extern s32 btlevtcmd_snd_se[];
extern s32 btlevtcmd_snd_voice[];
extern s32 evt_audience_ap_recovery[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_msg_continue[];
extern s32 evt_snd_sfxon[];
extern s32 weaponGetPowerFromMarioHammerLv[];
extern s32 weaponGetPowerFromMarioJumpLv[];

__declspec(section ".data") u64 fd_lecture_frankli_negone_one_374;
__declspec(section ".data") s32 fd_lecture_frankli_neg_one_382[1];
__declspec(section ".data") s32 fd_lecture_frankli___local_PI_383[1];
__declspec(section ".data") s32 fd_lecture_frankli___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_lecture_frankli_one_negone_373;
__declspec(section ".data") s32 fd_lecture_frankli___local_PIO2_384[1];
__declspec(section ".data") s32 fd_lecture_frankli_one_381[1];
__declspec(section ".data") u64 fd_lecture_frankli_negone_one_360;
__declspec(section ".data") s32 fd_lecture_frankli_neg_one_365[1];
__declspec(section ".data") s32 fd_lecture_frankli___local_PI_366[1];
__declspec(section ".data") s32 fd_lecture_frankli___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_lecture_frankli_one_negone_359;
__declspec(section ".data") s32 fd_lecture_frankli___local_PIO2_367[1];
__declspec(section ".data") s32 fd_lecture_frankli_one_364[1];
BattleUnitKind unit_lecture_frankli;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[5];
s32 _lec_weapon_jump[48];
s32 _lec_weapon_hammer[48];
static __declspec(section ".data") BattleDataEntry data_table[4];
static BattleUnitKindPart parts[1];
static s32 init_event[38];
static __declspec(section ".data") s32 damage_event[10];
static s32 phase_event[681];
static __declspec(section ".data") s32 attack_event[5];
static __declspec(section ".data") s32 wait_event[6];
s32 lecAttackEvent_Jump[735];
s32 lecAttackEvent_Hammer[651];
s32 lecture_end_event[51];

__declspec(section ".data") u64 fd_lecture_frankli_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_lecture_frankli_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_lecture_frankli___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_lecture_frankli___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_lecture_frankli_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_lecture_frankli___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_lecture_frankli_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_lecture_frankli_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_lecture_frankli_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_lecture_frankli___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_lecture_frankli___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_lecture_frankli_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_lecture_frankli___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_lecture_frankli_one_364[] = {
    1065353216,
};

BattleUnitKind unit_lecture_frankli = {
    178,
    "btl_un_frankli",
    10,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    28,
    24,
    5,
    25,
    0.0f,
    14.0f,
    0.0f,
    0,
    0,
    0.0f,
    30.0f,
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
    15.6f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x12000000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {27, "D_1"},
    {28, "S_1"},
    {31, "D_2"},
    {39, "D_2"},
    {69, "S_1"},
};

s32 _lec_weapon_jump[] = {
    (s32)"btl_wn_mario_normal_jump", 10420224, 0, (s32)"msg_normal_jump", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromMarioJumpLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 219143, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)lecAttackEvent_Jump, 100, 0, 0,
};

s32 _lec_weapon_hammer[] = {
    (s32)"btl_wn_mario_normal_hammer", 10223616, 0, (s32)"msg_normal_hammer", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, (s32)"msg_ac_hammer", 198791, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)lecAttackEvent_Hammer, 100, 0, 0,
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {68, _lec_weapon_jump},
    {69, _lec_weapon_hammer},
    {70, lecture_end_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_frankli", "c_kuri_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x90009, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_onoff_battleflag, 1, 4096)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StopWaitEvent, -3)
            CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("M_S_1"))
            CALL(btlevtcmd_SetUnitWork, -2, 1, 1)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 0, 58, 256, 0, 41, 0, 30, 11)
            WAIT_MS(500)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_000"), 0, -2)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_onoff_battleflag, 1, 16777216)
            CALL(btlevtcmd_StartWaitEvent, -3)
            RETURN
        END_IF
        CASE_EQUAL(2)
        CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, -2, 1, 3)
            CALL(btlevtcmd_StopWaitEvent, -3)
            CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("M_S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_003"), 0, -2)
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 0, 180, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, -2, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, -2, 0, 180, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_004"), 0, -2)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
            CALL(btlevtcmd_StopWaitEvent, LW(3))
            CALL(btlevtcmd_SetTalkPose, LW(3), STRING("PKR_T_1"))
            CALL(btlevtcmd_SetStayPose, LW(3), STRING("PKR_S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_005"), 0, LW(3))
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_StartWaitEvent, -3)
            BEGIN_INLINE_EVENT
                CALL(evt_sub_intpl_init, 5, 180, 0, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, -2, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
            END_INLINE_EVENT
            RETURN
        END_IF
        CASE_EQUAL(4)
        CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, -2, 1, 5)
            CALL(btlevtcmd_StopWaitEvent, -3)
            CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("M_S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_007"), 0, -2)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_onoff_battleflag, 0, 16777216)
            CALL(btlevtcmd_onoff_battleflag, 1, 33554432)
            RETURN
        END_IF
        CASE_EQUAL(6)
        CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, -2, 1, 7)
            CALL(btlevtcmd_StopWaitEvent, -3)
            CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("M_S_1"))
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 180, 0, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, -6, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, -6, 0, 0, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_011"), 0, -2)
            BEGIN_SIBLING_EVENT_GET_ID(LW(0))
                CALL(evt_sub_intpl_init, 5, 0, 180, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, -2, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, -2, 0, 180, 0)
            END_SIBLING_EVENT
            CALL(btlevtcmd_WaitEventEnd, LW(0))
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_012"), 0, -2)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(3))
            CALL(btlevtcmd_StopWaitEvent, LW(3))
            CALL(btlevtcmd_SetTalkPose, LW(3), STRING("PKR_T_1"))
            CALL(btlevtcmd_SetStayPose, LW(3), STRING("PKR_S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_013"), 0, LW(3))
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(btlevtcmd_StartWaitEvent, -3)
            BEGIN_INLINE_EVENT
                CALL(evt_sub_intpl_init, 5, 180, 0, 20)
                LOOP(21)
                    CALL(evt_sub_intpl_get_value)
                    CALL(btlevtcmd_SetRotate, -2, 0, LW(0), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
            END_INLINE_EVENT
            RETURN
        END_IF
        CASE_EQUAL(8)
        CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_SetUnitWork, -2, 1, 9)
            CALL(btlevtcmd_onoff_battleflag, 0, 33554432)
            CALL(btlevtcmd_onoff_battleflag, 1, 134217728)
            CALL(btlevtcmd_StopWaitEvent, -3)
            CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("M_S_1"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_016"), 0, -2)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 0, 58, 256, 0, 41, 0, 30, 11)
            WAIT_MS(500)
            CALL(evt_msg_print, 2, STRING("mac_0_b_t2_017"), 0, -2)
            CALL(evt_msg_select, 0, STRING("mac_0_b_t2_018"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("mac_0_b_t2_019"))
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                RETURN
                ELSE
                CALL(evt_msg_print_add, 0, STRING("mac_0_b_t2_020"))
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_onoff_battleflag, 1, 32)
                RETURN
            END_IF
        END_IF
        CASE_EQUAL(9)
        CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_GetUnitWork, -6, 3, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(4)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_021"), 0, -2)
                CASE_EQUAL(5)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_022"), 0, -2)
                CASE_EQUAL(6)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_023"), 0, -2)
                CASE_EQUAL(7)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_021"), 0, -2)
            END_SWITCH
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            RETURN
        END_IF
        CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_sub_intpl_init, 5, 180, 0, 20)
            LOOP(21)
                CALL(evt_sub_intpl_get_value)
                CALL(btlevtcmd_SetRotate, -6, 0, LW(0), 0)
                WAIT_FRAMES(1)
            END_LOOP
            CALL(btlevtcmd_SetRotate, -6, 0, 0, 0)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_GetUnitWork, -6, 2, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(1)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_021"), 0, -2)
                CASE_EQUAL(2)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_022"), 0, -2)
                CASE_EQUAL(3)
                CALL(evt_msg_print, 2, STRING("mac_0_b_t2_023"), 0, -2)
            END_SWITCH
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            RETURN
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

s32 lecAttackEvent_Jump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000, 1,
    196699, (s32)btlevtcmd_SetTalkPose, -6, (s32)"T_1", 196699, (s32)btlevtcmd_SetStayPose, -6, (s32)"S_1",
    327771, (s32)evt_msg_print, 2, (s32)"mac_0_b_t2_001", 0, -6, 33, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 327771,
    (s32)btlevtcmd_SetupAC, -2, 1, 1, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163,
    (s32)btlevtcmd_StartAC, 1, 131122, -29999990, 0, 65539, 10, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 131101, -29999990,
    1, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36,
    3, -1, 32, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000,
    0, -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998,
    36, 0, -1, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_J_1D", 262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000,
    1, 131100, -29999990, 0, 65647, -30000000, 327771, (s32)evt_sub_intpl_init,
    5, 0, 180, 20, 65541, 21, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetRotate, -6, 0, -30000000, 0, 65545, 1,
    6, 327771, (s32)btlevtcmd_SetRotate, -6, 0, 180, 0, 112,
    131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 33, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1,
    131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 65545, -30000000,
    131100, -29999990, 0, 196699, (s32)btlevtcmd_SetTalkPose, -6, (s32)"T_1", 196699,
    (s32)btlevtcmd_SetStayPose, -6, (s32)"S_1", 327771, (s32)evt_msg_print, 2, (s32)"mac_0_b_t2_002", 0,
    -6, 65545, 1, 65539, 11, 262235, (s32)btlevtcmd_PadCheckTrigger, 0,
    256, -30000000, 131096, -30000000, 0, 65545, 1, 65540,
    11, 33, 65546, 150, 65627, (s32)evt_msg_continue, 33, 32,
    196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128,
    -30000000, 2, 65545, -30000000, 33, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0,
    1, 65627, (s32)btlevtcmd_ResultAC, 131096, -29999990, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -6, 2, 0, 262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000,
    131096, -30000000, 9, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 65570,
    -30000000, 65572, 3, 262235, (s32)btlevtcmd_SetUnitWork, -6, 2, 1,
    65572, 1, 262235, (s32)btlevtcmd_SetUnitWork, -6, 2, 2, 65572,
    2, 262235, (s32)btlevtcmd_SetUnitWork, -6, 2, 3, 49, 33,
    33, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 131096, -29999990, 0, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000,
    -1, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_StopAC,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B",
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 8, -1, 65540, 95, 33, 196699, (s32)btlevtcmd_snd_voice,
    -2, 2, 131163, (s32)btlevtcmd_GetResultCountAC, -29999994, 131100, -29999994, 1,
    107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 65545, 10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 109, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 131072, -29999995, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 327771,
    (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 65545, 2, 131125,
    -29999990, 1, 65540, 10, 32, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995,
    65545, 2, 33, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 262235, (s32)btlevtcmd_GetUnitWork,
    -6, 1, -30000000, 131096, -30000000, 1, 65647, -29999986,
    327771, (s32)evt_sub_intpl_init, 5, 180, 0, 20, 65541, 21,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -6, 0, -30000000, 0,
    65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -6, 0, 0,
    0, 112, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B",
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 30, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 8, -1, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 262235, (s32)btlevtcmd_GetUnitWork, -6, 1,
    -30000000, 131096, -30000000, 1, 262235, (s32)btlevtcmd_SetUnitWork, -6, 1,
    2, 33, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 lecAttackEvent_Hammer[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7,
    262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000, 5,
    196699, (s32)btlevtcmd_SetTalkPose, -6, (s32)"T_1", 196699, (s32)btlevtcmd_SetStayPose, -6, (s32)"S_1",
    327771, (s32)evt_msg_print, 2, (s32)"mac_0_b_t2_008", 0, -6, 65539, 1,
    262235, (s32)btlevtcmd_PadCheckNow, 0, 262144, -30000000, 131096, -30000000, 0,
    65545, 1, 65540, 1, 33, 65627, (s32)evt_msg_continue, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 300, 110, 65539, 2, 327771, (s32)btlevtcmd_GetPos,
    -3, -30000000, -29999999, -29999998, 131098, -30000000, 0, 65545,
    1, 65540, 2, 33, 327771, (s32)evt_sub_intpl_init, 5, 0,
    180, 20, 65541, 21, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -6, 0, -30000000, 0, 65545, 1, 6, 327771,
    (s32)btlevtcmd_SetRotate, -6, 0, 180, 0, 112, 65647, -29999985,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915,
    (s32)btlevtcmd_AcSetParamAll, 4, 25, 0, 0, 0, -250000000, -250000000,
    -250000000, 262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000,
    5, 131163, (s32)btlevtcmd_AcSetFlag, 2, 32, 131163, (s32)btlevtcmd_AcSetFlag, 0,
    33, 327771, (s32)btlevtcmd_SetupAC, -2, 3, 1, 0, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 35, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 350, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_H_1A", 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD1", -250000000, 0, -250000000, 65545, 30,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_H_1B", 131163, (s32)btlevtcmd_StartAC, 1,
    262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000, 5,
    65539, 5, 196699, (s32)btlevtcmd_AcGetParam, 4, -30000000, 131096, -30000000,
    0, 65545, 1, 65540, 5, 33, 33, 112,
    131122, -29999986, 0, 262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000,
    131096, -30000000, 5, 65647, -29999986, 131122, -29999995, 5,
    65541, -29999995, 262235, (s32)btlevtcmd_PadCheckNow, 0, 262144, -30000000, 131096,
    -30000000, 0, 131178, -29999985, -30000000, 131096, -30000000, 0,
    32, 65640, -29999985, 196699, (s32)btlevtcmd_AcSetParam, 2, 1, 196699,
    (s32)btlevtcmd_SetTalkPose, -6, (s32)"T_1", 196699, (s32)btlevtcmd_SetStayPose, -6, (s32)"S_1", 327771,
    (s32)evt_msg_print, 2, (s32)"mac_0_b_t2_009", 0, -6, 65539, 6, 262235,
    (s32)btlevtcmd_PadCheckNow, 0, 262144, -30000000, 131096, -30000000, 0, 65545,
    1, 65540, 6, 33, 65546, 200, 65627, (s32)evt_msg_continue,
    196699, (s32)btlevtcmd_AcSetParam, 2, 0, 65641, -29999985, 33, 33,
    65545, 1, 131122, -29999995, 5, 6, 112, 33,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131097, -29999986, 0, 65631, -29999986,
    33, 262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000,
    5, 196699, (s32)btlevtcmd_SetTalkPose, -6, (s32)"T_1", 196699, (s32)btlevtcmd_SetStayPose, -6,
    (s32)"S_1", 327771, (s32)evt_msg_print, 2, (s32)"mac_0_b_t2_010", 0, -6, 65539,
    10, 262235, (s32)btlevtcmd_PadCheckNow, 0, 262144, -30000000, 131097, -30000000,
    0, 65545, 1, 65540, 10, 33, 65627, (s32)btlevtcmd_ResultAC,
    65546, 200, 65627, (s32)evt_msg_continue, 32, 65627, (s32)btlevtcmd_ResultAC, 33,
    262235, (s32)btlevtcmd_SetUnitWork, -6, 2, 0, 262235, (s32)btlevtcmd_GetUnitWork, -6,
    1, -30000000, 131096, -30000000, 9, 196699, (s32)btlevtcmd_AcGetOutputParam, 2,
    -30000000, 65570, -30000000, 65572, 3, 262235, (s32)btlevtcmd_SetUnitWork, -6,
    2, 1, 65572, 1, 262235, (s32)btlevtcmd_SetUnitWork, -6, 2,
    2, 65572, 2, 262235, (s32)btlevtcmd_SetUnitWork, -6, 2, 3,
    49, 33, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING1", 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_H_1C", 65545, 7, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_HIT_GROUND2",
    0, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 65540, 90,
    33, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -30000000, -29999994, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)btlevtcmd_GetDamage,
    -29999997, -30000000, 393307, (s32)evt_btl_camera_shake_h, 0, -30000000, 0, 10,
    13, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_S_1", 65545, 10, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000, 5,
    262235, (s32)btlevtcmd_SetUnitWork, -6, 1, 6, 33, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

EVT_BEGIN(lecture_end_event)
    CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("M_S_1"))
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 0, 58, 256, 0, 41, 0, 30, 11)
    WAIT_MS(500)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, -2, STRING("T_1"))
    CALL(btlevtcmd_SetStayPose, -2, STRING("S_1"))
    CALL(evt_msg_print, 2, STRING("mac_0_b_t2_024"), 0, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(500)
    CALL(btlevtcmd_onoff_battleflag, 1, 32)
    RETURN
EVT_END()

