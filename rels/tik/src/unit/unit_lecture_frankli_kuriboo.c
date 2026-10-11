#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"

static USER_FUNC(_battle_set_lecture_unit_id);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetMaxMoveCount);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_get_turn);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_toge);
static USER_FUNC(lecture_init);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];

__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_negone_one_374;
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_neg_one_382[1];
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PI_383[1];
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_one_negone_373;
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_one_381[1];
__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_negone_one_360;
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_neg_one_365[1];
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PI_366[1];
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_one_negone_359;
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_one_364[1];
BattleUnitKind unit_lecture_frankli_kuriboo;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[5];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static s32 init_event[53];
static s32 entry_event[29];
static s32 phase_event[160];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 wait_event[6];

static USER_FUNC(lecture_init) {
    return EVT_RETURN_DONE;
}

static USER_FUNC(_battle_set_lecture_unit_id) {
    BattleWork* wp = _battleWorkPointer;
    s32 value;

    value = evtGetValue(event, event->args[0]);
    wp->field_424 = value;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_lecture_frankli_kuriboo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_lecture_frankli_kuriboo_one_364[] = {
    1065353216,
};

BattleUnitKind unit_lecture_frankli_kuriboo = {
    180,
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
    "SFX_ENM_KURI_DAMAGED11",
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

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_frankli", "c_kuri_h", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x890009, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(lecture_init)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(_battle_set_lecture_unit_id, LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetPos, -2, 0, -1000, 0)
    CALL(btlevtcmd_ChangeFaceDirection, -2, 1)
    CALL(btlevtcmd_SetMaxMoveCount, -2, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(entry_event)
    WAIT_MS(900)
    CALL(btlevtcmd_SetPos, -2, -250, 0, -30)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("dokan_1"))
    CALL(btlevtcmd_MovePosition, -2, -60, 0, -30, 45, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("tik_15"))
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_get_turn, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_StopWaitEvent, -3)
            CALL(btlevtcmd_AnimeChangePose, -3, 1, STRING("dokan_2"))
            CALL(btlevtcmd_SetTalkPose, -2, STRING("gor_02"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("tik_15"))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_msg_print, 2, STRING("dokan"), 0, -2)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 71, 49, 213, 71, 35, 0, 30, 11)
            WAIT_FRAMES(30)
            CALL(evt_msg_toge, 1, 0, 0, 0)
            CALL(evt_msg_print, 2, STRING("dokan_3"), 0, -2)
            CALL(evt_btl_camera_set_moveto, 0, 111, 85, 213, 111, 71, 0, 30, 11)
            WAIT_FRAMES(30)
            CALL(evt_msg_toge, 1, 0, 0, 0)
            CALL(evt_msg_print, 2, STRING("dokan_5"), 0, -2)
            CALL(btlevtcmd_ChangeFaceDirection, -2, -1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_FRAMES(60)
            CALL(evt_msg_print, 2, STRING("dokan_4"), 0, -2)
            CALL(btlevtcmd_ChangeFaceDirection, -2, 1)
            WAIT_MS(1500)
            CALL(btlevtcmd_ChangeFaceDirection, -2, -1)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, -60, 82, 340, -60, 60, 13, 30, 11)
            WAIT_FRAMES(30)
            CALL(evt_msg_print, 2, STRING("dokan_6"), 0, -2)
            CALL(btlevtcmd_ChangeFaceDirection, -2, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            GOTO(99)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

