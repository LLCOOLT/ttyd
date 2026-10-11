#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_pad.h"
#include "system.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"

static USER_FUNC(_battle_set_lecture_unit_id);
USER_FUNC(_set_lecture_mode);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_DivePosition);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_onoff_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_msg_print);
USER_FUNC(_get_defence_ac_result);
USER_FUNC(_config_key_record);
static USER_FUNC(_krb_get_dir);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetPosFloat[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PadCheckTrigger[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_msg_continue[];
extern s32 evt_snd_sfxon[];
extern s32 pose_table_christine_stay[];
extern s32 unit_lecture_frankli[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_lecture_christine_negone_one_374;
__declspec(section ".data") s32 fd_lecture_christine_neg_one_382[1];
__declspec(section ".data") s32 fd_lecture_christine___local_PI_383[1];
__declspec(section ".data") s32 fd_lecture_christine___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_lecture_christine_one_negone_373;
__declspec(section ".data") s32 fd_lecture_christine___local_PIO2_384[1];
__declspec(section ".data") s32 fd_lecture_christine_one_381[1];
__declspec(section ".data") u64 fd_lecture_christine_negone_one_360;
__declspec(section ".data") s32 fd_lecture_christine_neg_one_365[1];
__declspec(section ".data") s32 fd_lecture_christine___local_PI_366[1];
__declspec(section ".data") s32 fd_lecture_christine___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_lecture_christine_one_negone_359;
__declspec(section ".data") s32 fd_lecture_christine___local_PIO2_367[1];
__declspec(section ".data") s32 fd_lecture_christine_one_364[1];
BattleUnitKind unit_lecture_christine;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
__declspec(section ".data") s32 entry_lecture_frankli[12];
static s32 init_event[78];
static __declspec(section ".data") s32 damage_event[10];
s32 lecture_christine_ac_counter_damage_event[117];
static __declspec(section ".data") s32 phase_event[2];
static __declspec(section ".data") s32 wait_event[6];
static s32 attack_event[19];
s32 lec_weapon_zutsuki_1[48];
s32 lec_weapon_zutsuki_2[48];
s32 lecture_zutsuki_attack_event[570];

USER_FUNC(_get_defence_ac_result) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 var = args[0];
    s32 result = 0;

    switch (wp->actionCommands.mDefenseResult) {
        case 1:
            result = 2;
            break;
        case 2:
            result = 3;
            break;
        case 4:
            result = 1;
            break;
        case 5:
            result = 0;
            break;
    }
    evtSetValue(event, var, result);
    return EVT_RETURN_DONE;
}

USER_FUNC(_config_key_record) {
    s32 record = event->args[0];
    BattleWork* wp = _battleWorkPointer;
    BattleWorkPad* pad = &wp->actionCommands.pad;

    wp->actionCommands.mDefenseResult = 4;
    BtlPad_WorkInit(pad);
    pad->mButtonsPressedHistory[0] = record;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_lecture_christine_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_lecture_christine_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_lecture_christine___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_lecture_christine___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_lecture_christine_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_lecture_christine___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_lecture_christine_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_lecture_christine_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_lecture_christine_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_lecture_christine___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_lecture_christine___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_lecture_christine_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_lecture_christine___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_lecture_christine_one_364[] = {
    1065353216,
};

BattleUnitKind unit_lecture_christine = {
    177,
    "btl_un_christine",
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
    8,
    24,
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
    "SFX_PARTY_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x2000000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {36, lecture_christine_ac_counter_damage_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_christine", "c_pkr", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x880009, 0, pose_table_christine_stay},
};

__declspec(section ".data") s32 entry_lecture_frankli[] = {
    (s32)unit_lecture_frankli, 33554432, 67108865, 0, 0, -1036779520, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(_set_lecture_mode)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_lecture_frankli), 0)
    CALL(btlevtcmd_SetUnitWork, -2, 0, LW(3))
    CALL(_battle_set_lecture_unit_id, LW(3))
    CALL(btlevtcmd_ChangeFaceDirection, LW(3), -1)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
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

EVT_BEGIN(lecture_christine_ac_counter_damage_event)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 39)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(2), 25)
    ADD(LW(3), 25)
    CALL(btlevtcmd_DivePosition, -2, LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
    CALL(btlevtcmd_SetTalkPose, -2, STRING("PKR_D_1"))
    CALL(btlevtcmd_SetStayPose, -2, STRING("PKR_D_1"))
    CALL(evt_msg_print, 2, STRING("mac_0_b_t2_015"), 0, -2)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, -2, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_TransStageFloorPosition, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(2), 30)
    CALL(btlevtcmd_JumpPosition, -2, LW(2), LW(3), LW(4), 20, -1)
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(2), 15)
    CALL(btlevtcmd_JumpPosition, -2, LW(2), LW(3), LW(4), 10, -1)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetUnitWork, -6, 1, LW(0))
    IF_INT_EQUAL(LW(0), 7)
        CALL(btlevtcmd_SetUnitWork, -6, 1, 8)
        ELSE
        CALL(btlevtcmd_SetUnitWork, -6, 3, 7)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL_CHILD(PTR(lecture_zutsuki_attack_event))
    CALL(btlevtcmd_GetUnitWork, -6, 1, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetUnitWork, -6, 1, 4)
    END_SWITCH
    RETURN
EVT_END()

s32 lec_weapon_zutsuki_1[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 86023, 12, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 lec_weapon_zutsuki_2[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 86023, 12, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 lecture_zutsuki_attack_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 131096, -30000000, 3,
    131122, -29999988, (s32)lec_weapon_zutsuki_1, 32, 131122, -29999988, (s32)lec_weapon_zutsuki_2, 33,
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2,
    7, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0,
    -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0,
    -29999986, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, -29999986,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131122, -29999990,
    0, 65539, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_A_2B",
    65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PKR_J_1A", 107,
    65545, 15, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_KURI_ATTACK1", 0, 109, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 14, 0, 110, 327771, (s32)btlevtcmd_GetPosFloat, -2, -29999995,
    -29999994, -29999993, 131122, -29999992, 0, 65541, 36, 327771,
    (s32)btlevtcmd_GetPosFloat, -2, -29999988, -29999987, -29999986, 393307, (s32)_krb_get_dir, -29999995,
    -29999994, -29999988, -29999987, -29999992, 327771, (s32)btlevtcmd_GetRotate, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetRotate, -2, -30000000, -29999999, -29999992,
    131124, -29999995, -29999988, 131124, -29999994, -29999987, 65545, 1,
    6, 112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 131125, -29999998, 5, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, 36, 0, -1, 262235, (s32)btlevtcmd_GetUnitWork, -6,
    1, -30000000, 65570, -30000000, 65572, 3, 196699, (s32)btlevtcmd_SetTalkPose,
    -6, (s32)"T_1", 196699, (s32)btlevtcmd_SetStayPose, -6, (s32)"S_1", 327771, (s32)evt_msg_print,
    2, (s32)"mac_0_b_t2_006", 0, -6, 65545, 1, 65539, 11,
    262235, (s32)btlevtcmd_PadCheckTrigger, 0, 256, -30000000, 131096, -30000000, 0,
    65545, 1, 65540, 11, 33, 65546, 50, 107,
    65546, 100, 65627, (s32)evt_msg_continue, 109, 65546, 100, 65572,
    7, 196699, (s32)btlevtcmd_SetTalkPose, -6, (s32)"T_1", 196699, (s32)btlevtcmd_SetStayPose, -6,
    (s32)"S_1", 327771, (s32)evt_msg_print, 2, (s32)"mac_0_b_t2_014", 0, -6, 65545,
    1, 65539, 12, 262235, (s32)btlevtcmd_PadCheckTrigger, 0, 512, -30000000,
    131096, -30000000, 0, 65545, 1, 65540, 12, 33,
    65546, 50, 107, 65546, 100, 65627, (s32)evt_msg_continue, 109,
    65546, 100, 49, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0,
    196699, (s32)evt_btl_camera_set_zoom, 0, -229833600, 65545, 10, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 109, 262235,
    (s32)btlevtcmd_GetUnitWork, -6, 1, -30000000, 65570, -30000000, 65572, 3,
    131163, (s32)_config_key_record, 256, 65572, 7, 131163, (s32)_config_key_record, 512,
    49, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999988, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999988, 256, -29999995, 131163, (s32)_get_defence_ac_result, -30000000,
    65570, -30000000, 65572, 0, 65572, 1, 262235, (s32)btlevtcmd_SetUnitWork,
    -6, 3, 4, 65572, 2, 262235, (s32)btlevtcmd_SetUnitWork, -6,
    3, 5, 65572, 3, 262235, (s32)btlevtcmd_SetUnitWork, -6, 3,
    6, 49, 131125, -29999990, 1, 110, 327771, (s32)btlevtcmd_GetRotate,
    -2, -250000000, -250000000, -29999994, 131098, -29999994, 0, 131127,
    -29999994, -1, 33, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127,
    -29999994, -30000000, 131128, -29999994, 15, 131122, -29999993, 15,
    65539, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999994,
    131126, -29999993, 1, 65545, 1, 131101, -29999993, 1,
    65540, 20, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 95, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 65539,
    99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1, 0,
};

static USER_FUNC(_krb_get_dir) {
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

static USER_FUNC(_battle_set_lecture_unit_id) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 value;

    value = evtGetValue(event, *args++);
    wp->field_424 = value;
    return EVT_RETURN_DONE;
}

USER_FUNC(_set_lecture_mode) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -3);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);

    unit->mAttributeFlags |= 0x40000000;
    wp->lectureMode = 1;
    return EVT_RETURN_DONE;
}

