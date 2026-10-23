#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "eff/eff_small_star.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "las.h"

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_delete);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_floatswitch_red);
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
static USER_FUNC(small_star);

__declspec(section ".data") u64 fd_las_13_negone_one_374;
__declspec(section ".data") s32 fd_las_13_neg_one_382[1];
__declspec(section ".data") s32 fd_las_13___local_PI_383[1];
__declspec(section ".data") s32 fd_las_13___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_13_one_negone_373;
__declspec(section ".data") s32 fd_las_13___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_13_one_381[1];
__declspec(section ".data") u64 fd_las_13_negone_one_360;
__declspec(section ".data") s32 fd_las_13_neg_one_365[1];
__declspec(section ".data") s32 fd_las_13___local_PI_366[1];
__declspec(section ".data") s32 fd_las_13___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_13_one_negone_359;
__declspec(section ".data") s32 fd_las_13___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_13_one_364[1];
static __declspec(section ".data") s32 e_door_close[12];
static __declspec(section ".data") s32 e_door_open[12];
static s32 bero_entry_data[30];
static s32 box_evt[30];
s32 switch_check[114];
static __declspec(section ".data") s32 switch1_evt[11];
static s32 switch2_evt[15];
static s32 hint_plate[14];
s32 las_13_init_evt[79];

__declspec(section ".data") u64 fd_las_13_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_13_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_13___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_13___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_13_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_13___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_13_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_13_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_13_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_13___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_13___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_13_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_13___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_13_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"e_bero_1", 65537, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_10", (s32)"sw_bero_1", 327685, (s32)e_door_close, (s32)e_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), 40, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(switch_check)
    SET_VALUE(LW(0), 0)
    IF_INT_EQUAL(LSW(1), 2)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSW(2), 3)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(evt_mario_key_onoff, 0)
        WAIT_MS(300)
        CALL(evt_mobj_get_position, STRING("switch1"), LW(0), LW(1), LW(2))
        CALL(small_star, LW(0), LW(1), LW(2))
        CALL(evt_mobj_get_position, STRING("switch2"), LW(0), LW(1), LW(2))
        CALL(small_star, LW(0), LW(1), LW(2))
        CALL(evt_mobj_delete, STRING("switch1"))
        CALL(evt_mobj_delete, STRING("switch2"))
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
        CALL(evt_cam3d_evt_set, 0, 100, 363, 0, 30, -30, 500, 11)
        WAIT_MS(1000)
        CALL(evt_mobj_set_position, STRING("box"), 0, -30, 0)
        CALL(evt_mobj_flag_onoff, 0, STRING("box"), 16448)
        CALL(evt_mobj_hit_onoff, STRING("box"), 1)
        SET_VALUE(LW(0), STRING("box"))
        CALL_CHILD(PTR(box_syutugen))
        CALL(evt_cam3d_evt_off, 500, 11)
        CALL(evt_mario_key_onoff, 1)
        SET_VALUE(GSWF(4343), 1)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(switch1_evt)
    IF_INT_LESS(LSW(1), 255)
        ADD(LSW(1), 1)
    END_IF
    CALL_CHILD(PTR(switch_check))
    RETURN
EVT_END()

static EVT_BEGIN(switch2_evt)
    IF_INT_EQUAL(LSW(1), 0)
        IF_INT_LESS(LSW(2), 255)
            ADD(LSW(2), 1)
        END_IF
    END_IF
    CALL_CHILD(PTR(switch_check))
    RETURN
EVT_END()

static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_38"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(las_13_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_EQUAL(GSWF(4343), 0)
        SET_VALUE(LSW(1), 0)
        SET_VALUE(LSW(2), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("switch1"), 150, 60, 0, PTR(switch1_evt), GSWF(4343))
        CALL(evt_mobj_floatswitch_red, 0, STRING("switch2"), -150, 60, 0, PTR(switch2_evt), GSWF(4343))
    END_IF
    CALL(evt_mobj_itembox, STRING("box"), 0, 0, 0, 0, 0, PTR(box_evt), GSWF(4364))
    IF_INT_EQUAL(GSWF(4343), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("box"), 16384)
        CALL(evt_mobj_hit_onoff, STRING("box"), 0)
    END_IF
    CALL(evt_run_case_evt, 9, 1, STRING("A_pure"), 0, PTR(hint_plate), 0)
    RETURN
EVT_END()

static USER_FUNC(small_star) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effSmallStarEntry(0, 4, x, 12.5f + y, z, 0.0f, -1.0f, 0.0f);
    return EVT_RETURN_DONE;
}
