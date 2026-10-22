#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_floatswitch_blue);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_hit_onoff);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_set_position);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 box_syutugen[];
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_las_12_negone_one_374;
__declspec(section ".data") s32 fd_las_12_neg_one_382[1];
__declspec(section ".data") s32 fd_las_12___local_PI_383[1];
__declspec(section ".data") s32 fd_las_12___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_12_one_negone_373;
__declspec(section ".data") s32 fd_las_12___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_12_one_381[1];
__declspec(section ".data") u64 fd_las_12_negone_one_360;
__declspec(section ".data") s32 fd_las_12_neg_one_365[1];
__declspec(section ".data") s32 fd_las_12___local_PI_366[1];
__declspec(section ".data") s32 fd_las_12___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_12_one_negone_359;
__declspec(section ".data") s32 fd_las_12___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_12_one_364[1];
static __declspec(section ".data") s32 w_door_close[12];
static __declspec(section ".data") s32 w_door_open[12];
static s32 bero_entry_data[30];
static s32 box_evt[30];
static s32 switch_evt[46];
static s32 hint_plate[14];
s32 kabenuke_check_evt[42];
s32 las_12_init_evt[62];

__declspec(section ".data") u64 fd_las_12_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_12_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_12___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_12___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_12_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_12___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_12_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_12_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_12_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_12___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_12___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_12_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_12___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_12_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 65537, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_10", (s32)"ne_bero_1", 327685, (s32)w_door_close, (s32)w_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), 39, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(switch_evt)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1250)
    CALL(evt_cam3d_evt_set, -150, 100, 363, -150, 30, -30, 500, 11)
    WAIT_MS(1000)
    CALL(evt_mobj_set_position, STRING("box"), -150, -30, 0)
    CALL(evt_mobj_flag_onoff, 0, STRING("box"), 16448)
    CALL(evt_mobj_hit_onoff, STRING("box"), 1)
    SET_VALUE(LW(0), STRING("box"))
    CALL_CHILD(PTR(box_syutugen))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_37"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(kabenuke_check_evt)
    IF_INT_EQUAL(GSWF(4381), 1)
        RETURN
    END_IF
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
    WAIT_MS(2000)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    SET_VALUE(GSWF(4381), 1)
    RETURN
EVT_END()

EVT_BEGIN(las_12_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_floatswitch_blue, 0, STRING("switch"), 150, 60, 0, PTR(switch_evt), GSWF(4342))
    CALL(evt_mobj_itembox, STRING("box"), -150, 0, 0, 0, 0, PTR(box_evt), GSWF(4363))
    IF_INT_EQUAL(GSWF(4342), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("box"), 16384)
        CALL(evt_mobj_hit_onoff, STRING("box"), 0)
    END_IF
    CALL(evt_run_case_evt, 9, 1, STRING("A_pure\0"), 0, PTR(hint_plate), 0)
    SPAWN_EVENT(PTR(kabenuke_check_evt))
    RETURN
EVT_END()

