#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_entry_airport_harbor);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_jumpstand_blue);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_win_item_select);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 hikari_evt[];

__declspec(section ".data") u64 fd_las_25_negone_one_374;
__declspec(section ".data") s32 fd_las_25_neg_one_382[1];
__declspec(section ".data") s32 fd_las_25___local_PI_383[1];
__declspec(section ".data") s32 fd_las_25___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_25_one_negone_373;
__declspec(section ".data") s32 fd_las_25___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_25_one_381[1];
__declspec(section ".data") u64 fd_las_25_negone_one_360;
__declspec(section ".data") s32 fd_las_25_neg_one_365[1];
__declspec(section ".data") s32 fd_las_25___local_PI_366[1];
__declspec(section ".data") s32 fd_las_25___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_25_one_negone_359;
__declspec(section ".data") s32 fd_las_25___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_25_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e1_door_close[22];
static s32 e1_door_open[22];
static s32 e2_door_close[22];
static s32 e2_door_open[22];
static s32 bero_entry_data[75];
static s32 w_bero_mapchg[15];
static __declspec(section ".data") s32 key_tbl[2];
static s32 key_check_evt[23];
static __declspec(section ".data") s32 unlock_evt[10];
s32 las_25_init_evt[174];

__declspec(section ".data") u64 fd_las_25_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_25_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_25___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_25___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_25_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_25___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_25_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_25_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_25_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_25___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_25___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_25_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_25___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_25_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_23", (s32)"e_bero_1", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero_1",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_26", (s32)"w_bero", 327685, (s32)e1_door_close, (s32)e1_door_open, (s32)"e_bero_2", 65542,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"las_27", (s32)"w_bero", 327685, (s32)e2_door_close, (s32)e2_door_open, (s32)"n_bero_1", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"las_24",
    (s32)"s_bero_2", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

static s32 w_bero_mapchg[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_23", (s32)"e_bero_2", 327685, (s32)w_door_close, (s32)w_door_open,
};

static __declspec(section ".data") s32 key_tbl[] = {
    48, -1,
};

static EVT_BEGIN(key_check_evt)
    CALL(evt_pouch_check_item, 48, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
        IF_INT_EQUAL(LW(0), -1)
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(unlock_evt)
    SET_VALUE(GSW(0), 398)
    SET_VALUE(LW(0), STRING("e_bero_2"))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

EVT_BEGIN(las_25_init_evt)
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST3"))
    END_IF
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_npc_check_delete, STRING("ファントム３"))
        CALL(evt_npc_check_delete, STRING("ファントム４"))
        CALL(evt_npc_check_delete, STRING("ファントム５"))
        CALL(evt_npc_check_delete, STRING("ファントム６"))
        ELSE
        CALL(evt_npc_check_delete, STRING("ファントム１"))
        CALL(evt_npc_check_delete, STRING("ファントム２"))
    END_IF
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_under"), 1)
        CALL(evt_hitobj_onoff, STRING("A_under"), 1, 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("hikou"), 1)
        CALL(evt_hitobj_onoff, STRING("a_hi"), 1, 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_yuka"), 1)
        CALL(evt_hitobj_onoff, STRING("A_be"), 1, 0)
        CALL(evt_map_entry_airport_harbor, 0, STRING("hikou"), STRING("a_hi"))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("w_bero"), PTR(w_bero_mapchg))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
        SPAWN_EVENT(PTR(hikari_evt))
    END_IF
    CALL(evt_mobj_lock, STRING("lock"), 48, 690, -380, 0, -90, PTR(key_check_evt), PTR(unlock_evt), GSWF(4359))
    IF_INT_EQUAL(GSWF(4359), 0)
        SET_VALUE(LW(0), STRING("e_bero_2"))
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    CALL(evt_mobj_jumpstand_blue, 0, STRING("jump"), 720, -675, -600, 75, 0, 0)
    CALL(evt_mobj_flag_onoff, 0, STRING("jump"), 64)
    CALL(evt_item_entry, STRING("item02"), 151, 225, -350, 0, 16, GSWF(4379), 0)
    CALL(evt_item_entry, STRING("item03"), 130, 375, -450, 0, 16, GSWF(4392), 0)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 600, 60, -75, 0, 0)
    RETURN
EVT_END()

