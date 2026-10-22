#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_gon_10_negone_one_374;
__declspec(section ".data") s32 fd_gon_10_neg_one_382[1];
__declspec(section ".data") s32 fd_gon_10___local_PI_383[1];
__declspec(section ".data") s32 fd_gon_10___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gon_10_one_negone_373;
__declspec(section ".data") s32 fd_gon_10___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gon_10_one_381[1];
__declspec(section ".data") u64 fd_gon_10_negone_one_360;
__declspec(section ".data") s32 fd_gon_10_neg_one_365[1];
__declspec(section ".data") s32 fd_gon_10___local_PI_366[1];
__declspec(section ".data") s32 fd_gon_10___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gon_10_one_negone_359;
__declspec(section ".data") s32 fd_gon_10___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gon_10_one_364[1];
static s32 door02_close[22];
static s32 door02_open[22];
static s32 door01_close[22];
static s32 door01_open[22];
static s32 bero_entry_data[45];
s32 gon_10_init_evt[46];

__declspec(section ".data") u64 fd_gon_10_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_10_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon_10___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon_10___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_10_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon_10___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_10_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gon_10_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_10_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon_10___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon_10___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_10_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon_10___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_10_one_364[] = {
    1065353216,
};

static EVT_BEGIN(door02_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door03"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door04"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(door02_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door03"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door04"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(door01_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(door01_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65549, 2, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"gon_11", (s32)"w_bero", 327685, (s32)door02_close, (s32)door02_open, (s32)"e_bero",
    65548, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"gon_05", (s32)"w_bero_5", 327685, (s32)door01_close, (s32)door01_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(gon_10_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_GON3"))
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -460, 1010, -145, 0, 0)
    CALL(evt_mobj_recovery_blk, STRING("mobj_recover"), 6, -400, 1010, -146, 0, 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 55)
        CALL(evt_mapobj_flag_onoff, 0, 1, STRING("en\0"), 1)
    END_IF
    RETURN
EVT_END()

