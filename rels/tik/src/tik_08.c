#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_cam_ctrl_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mobj_signboard);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_tik_08_negone_one_374;
__declspec(section ".data") s32 fd_tik_08_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_08___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_08___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_08_one_negone_373;
__declspec(section ".data") s32 fd_tik_08___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_08_one_381[1];
__declspec(section ".data") u64 fd_tik_08_negone_one_360;
__declspec(section ".data") s32 fd_tik_08_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_08___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_08___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_08_one_negone_359;
__declspec(section ".data") s32 fd_tik_08___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_08_one_364[1];
s32 oshimodo_event_sub[33];
static __declspec(section ".data") s32 oshimodo_event[10];
static s32 bero_oshimodo[15];
static s32 bero_entry_data[45];
static s32 bero_entry_data2[30];
static s32 evt_kanban[16];
s32 tik_08_init_evt[68];

__declspec(section ".data") u64 fd_tik_08_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_08_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_08___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_08___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_08_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_08___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_08_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_08_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_08_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_08___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_08___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_08_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_08___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_08_one_364[] = {
    1065353216,
};

EVT_BEGIN(oshimodo_event_sub)
    CALL(evt_cam_ctrl_onoff, 4, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(750)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("tik_08_01"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_ctrl_onoff, 4, 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(oshimodo_event)
    SPAWN_EVENT(PTR(oshimodo_event_sub))
    SET_VALUE(GSWF(1341), 1)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_oshimodo[] = {
    (s32)"dokan", 131072, 9, 100000, 0, 0, -1, 0,
    6, (s32)oshimodo_event, 0, (s32)"dokan", 65537, 0, 0,
};

static s32 bero_entry_data[] = {
    (s32)"dokan", 131072, 9, 100000, 0, 0, -1, 0,
    6, 0, (s32)"usu_00", (s32)"dokan_1", 65537, 0, 0, (s32)"s_bero",
    65537, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"tik_07", (s32)"n_bero", 131074, (s32)"door", 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_entry_data2[] = {
    (s32)"dokan", 131072, 9, 100000, 0, 0, -1, 0,
    6, 0, (s32)"sys_01", (s32)"stg_4", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_kanban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_msg_print, 0, STRING("tik_08_02"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(tik_08_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_LESS_OR_EQUAL(GSW(0), 175)
        SET_VALUE(LW(0), STRING("dokan"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("dokan"), PTR(bero_oshimodo))
        SET_VALUE(LW(0), STRING("dokan"))
        CALL_CHILD(PTR(bero_case_switch_on))
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 176)
        IF_INT_LESS(GSW(0), 178)
            SET_VALUE(LW(0), STRING("dokan"))
            CALL_CHILD(PTR(bero_case_switch_off))
            CALL(evt_bero_overwrite, STRING("dokan"), PTR(bero_entry_data2))
            SET_VALUE(LW(0), STRING("dokan"))
            CALL_CHILD(PTR(bero_case_switch_on))
        END_IF
    END_IF
    CALL(evt_mobj_signboard, STRING("board"), 85, 0, 0, PTR(evt_kanban), 0)
    RETURN
EVT_END()

