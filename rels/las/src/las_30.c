#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "stdio.h"

static char name[8];

USER_FUNC(evt_eff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_wait_animation_end);
static USER_FUNC(make_name);
extern s32 evt_bero_get_info[];
extern s32 evt_bero_info_run[];
extern s32 evt_mobj_itembox[];
extern s32 evt_mobj_recovery_blk[];
extern s32 evt_mobj_save_blk[];
extern s32 evt_snd_bgmoff[];
extern s32 evt_snd_bgmon[];
extern s32 evt_snd_envoff[];
extern s32 evt_snd_envon[];
extern s32 evt_snd_set_rev_mode[];

__declspec(section ".data") u64 fd_las_30_negone_one_374;
__declspec(section ".data") s32 fd_las_30_neg_one_382[1];
__declspec(section ".data") s32 fd_las_30___local_PI_383[1];
__declspec(section ".data") s32 fd_las_30___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_30_one_negone_373;
__declspec(section ".data") s32 fd_las_30___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_30_one_381[1];
__declspec(section ".data") u64 fd_las_30_negone_one_360;
__declspec(section ".data") s32 fd_las_30_neg_one_365[1];
__declspec(section ".data") s32 fd_las_30___local_PI_366[1];
__declspec(section ".data") s32 fd_las_30___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_30_one_negone_359;
__declspec(section ".data") s32 fd_las_30___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_30_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
static s32 rousoku_init[46];
static s32 mobj_box01[34];
static s32 mobj_box02[34];
s32 las_30_init_evt[71];

__declspec(section ".data") u64 fd_las_30_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_30_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_30___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_30___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_30_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_30___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_30_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_30_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_30_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_30___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_30___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_30_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_30___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_30_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_28", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_29", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(rousoku_init)
    SET_VALUE(LW(0), 1)
    LOOP(12)
        CALL(make_name, LW(0), LW(1))
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(1), 1)
        CALL(evt_mapobj_get_position, LW(1), LW(2), LW(3), LW(4))
        SUBTRACT_FLOAT(LW(3), FLOAT(7.0f))
        CALL(evt_eff, 0, STRING("fire"), 3, LW(2), LW(3), LW(4), FLOAT(0.5f), 1000, 0, 0, 0, 0, 0, 0)
        ADD(LW(0), 1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(mobj_box01)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box01"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item01"), 150, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item01"), 2)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box01"))
    CALL(evt_item_get_item, STRING("item01"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(mobj_box02)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box02"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item02"), 156, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item02"), 2)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box02"))
    CALL(evt_item_get_item, STRING("item02"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

s32 las_30_init_evt[] = {
    131096, -170000000, 400, 196699, (s32)evt_snd_bgmon, 512, (s32)"BGM_EVT_DANGER2", 131163,
    (s32)evt_snd_envoff, 512, 32, 131163, (s32)evt_snd_bgmoff, 512, 196699, (s32)evt_snd_envon,
    272, (s32)"ENV_STG8_LAS1", 33, 131163, (s32)evt_snd_set_rev_mode, 2, 131122, -30000000,
    (s32)bero_entry_data, 65627, (s32)evt_bero_get_info, 65630, (s32)evt_bero_info_run, 458843, (s32)evt_mobj_save_blk, (s32)"mobj_save",
    1150, 60, -125, 0, 0, 524379, (s32)evt_mobj_recovery_blk, (s32)"r_blk",
    10, -1050, 860, -75, 0, 0, 589915, (s32)evt_mobj_itembox,
    (s32)"mobj_box01", -1150, 800, -75, 0, 0, (s32)mobj_box01, -129995607,
    589915, (s32)evt_mobj_itembox, (s32)"mobj_box02", 1050, 0, -125, 0, 0,
    (s32)mobj_box02, -129995606, 65630, (s32)rousoku_init, 2, 1, 0,
};

static USER_FUNC(make_name) {
    s32* args = event->args;

    sprintf(name, "hi%d\0\0\0", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}

