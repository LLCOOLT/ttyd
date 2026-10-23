#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "stdio.h"
#include "evt/evt_bero.h"

static char name[8];

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_eff);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_npc_check);
USER_FUNC(evt_npc_set_link);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
static USER_FUNC(make_name);

__declspec(section ".data") u64 fd_las_02_negone_one_374;
__declspec(section ".data") s32 fd_las_02_neg_one_382[1];
__declspec(section ".data") s32 fd_las_02___local_PI_383[1];
__declspec(section ".data") s32 fd_las_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_02_one_negone_373;
__declspec(section ".data") s32 fd_las_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_02_one_381[1];
__declspec(section ".data") u64 fd_las_02_negone_one_360;
__declspec(section ".data") s32 fd_las_02_neg_one_365[1];
__declspec(section ".data") s32 fd_las_02___local_PI_366[1];
__declspec(section ".data") s32 fd_las_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_02_one_negone_359;
__declspec(section ".data") s32 fd_las_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_02_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
static s32 rousoku_init[46];
s32 las_02_init_evt[44];

__declspec(section ".data") u64 fd_las_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_02_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door1_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door1_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door1_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door1_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_1"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_door2_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_01", (s32)"e_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_03", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(rousoku_init)
    SET_VALUE(LW(0), 1)
    LOOP(18)
        CALL(make_name, LW(0), LW(1))
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(1), 1)
        CALL(evt_mapobj_get_position, LW(1), LW(2), LW(3), LW(4))
        SUBTRACT_FLOAT(LW(3), FLOAT(7.0f))
        CALL(evt_eff, 0, STRING("fire"), 3, LW(2), LW(3), LW(4), FLOAT(1.0f), 1000, 0, 0, 0, 0, 0, 0)
        ADD(LW(0), 1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(las_02_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_badgeblk, STRING("mobj00"), -550, 480, 60, 130, 0, GSWF(4371), 0)
    CALL(evt_npc_check, STRING("スーパーキラー大砲１"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_link, STRING("スーパーキラー大砲１"), STRING("スーパーキラー大砲２"))
    END_IF
    CALL_CHILD(PTR(rousoku_init))
    RETURN
EVT_END()

static USER_FUNC(make_name) {
    s32* args = event->args;

    sprintf(name, "hi%d\0\0\0", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}

