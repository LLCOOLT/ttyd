#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon);

__declspec(section ".data") u64 fd_las_07_negone_one_374;
__declspec(section ".data") s32 fd_las_07_neg_one_382[1];
__declspec(section ".data") s32 fd_las_07___local_PI_383[1];
__declspec(section ".data") s32 fd_las_07___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_07_one_negone_373;
__declspec(section ".data") s32 fd_las_07___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_07_one_381[1];
__declspec(section ".data") u64 fd_las_07_negone_one_360;
__declspec(section ".data") s32 fd_las_07_neg_one_365[1];
__declspec(section ".data") s32 fd_las_07___local_PI_366[1];
__declspec(section ".data") s32 fd_las_07___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_07_one_negone_359;
__declspec(section ".data") s32 fd_las_07___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_07_one_364[1];
static s32 w1_door_close[22];
static s32 w1_door_open[22];
static s32 w2_door_close[22];
static s32 w2_door_open[22];
static s32 e1_door_close[22];
static s32 e1_door_open[22];
static s32 e2_door_close[22];
static s32 e2_door_open[22];
static s32 door_matigai_evt[16];
static s32 bero_entry_data[75];
s32 las_07_init_evt[57];

__declspec(section ".data") u64 fd_las_07_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_07_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_07___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_07___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_07_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_07___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_07_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_07_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_07_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_07___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_07___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_07_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_07___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_07_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r1_01"), 0, LW(0), 0)
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
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(door_matigai_evt)
    IF_INT_EQUAL(GSWF(4325), 1)
        CALL(evt_snd_sfxon, STRING("SFX_STG8_DOOR_NG_OPEN1"), 0)
        SET_VALUE(GSWF(4325), 0)
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 65542, 20000, 100000, 0, 0, -1, (s32)door_matigai_evt,
    -1, 0, (s32)"las_06", (s32)"e_bero", 327685, (s32)w1_door_close, (s32)w1_door_open, (s32)"e_bero_1",
    65542, 20000, 100000, 0, 0, -1, (s32)door_matigai_evt, -1,
    0, (s32)"las_08", (s32)"w_bero_1", 327685, (s32)e1_door_close, (s32)e1_door_open, (s32)"w_bero_2", 65542,
    20000, 100000, 0, 0, -1, (s32)door_matigai_evt, -1, 0,
    (s32)"las_08", (s32)"e_bero_2", 327685, (s32)w2_door_close, (s32)w2_door_open, (s32)"e_bero_2", 65542, 20000,
    100000, 0, 0, -1, (s32)door_matigai_evt, -1, 0, (s32)"las_08",
    (s32)"w_bero_2", 327685, (s32)e2_door_close, (s32)e2_door_open, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(las_07_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_cam_road_reset)
    END_INLINE_EVENT
    CALL(evt_mobj_badgeblk, STRING("mobj00"), -100, 60, -300, 121, 0, GSWF(4373), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj01"), 100, 60, -300, 156, 0, GSWF(4374), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_badge_gat\0"), 0, 60, -300, 263, 0, GSWF(4376), 1)
    RETURN
EVT_END()

