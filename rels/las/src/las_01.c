#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);

__declspec(section ".data") u64 fd_las_01_negone_one_374;
__declspec(section ".data") s32 fd_las_01_neg_one_382[1];
__declspec(section ".data") s32 fd_las_01___local_PI_383[1];
__declspec(section ".data") s32 fd_las_01___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_01_one_negone_373;
__declspec(section ".data") s32 fd_las_01___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_01_one_381[1];
__declspec(section ".data") u64 fd_las_01_negone_one_360;
__declspec(section ".data") s32 fd_las_01_neg_one_365[1];
__declspec(section ".data") s32 fd_las_01___local_PI_366[1];
__declspec(section ".data") s32 fd_las_01___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_01_one_negone_359;
__declspec(section ".data") s32 fd_las_01___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_01_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
s32 las_01_init_evt[35];

__declspec(section ".data") u64 fd_las_01_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_01_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_01___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_01___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_01_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_01___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_01_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_01_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_01_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_01___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_01___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_01_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_01___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_01_one_364[] = {
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

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_00", (s32)"e_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_02", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(las_01_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS2"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_map_playanim, STRING("hamon"), 1, 0)
    CALL(evt_item_entry, STRING("item_01"), 140, -710, 448, -175, 16, GSWF(4383), 0)
    RETURN
EVT_END()

