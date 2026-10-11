#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_eki_04_negone_one_374;
__declspec(section ".data") s32 fd_eki_04_neg_one_382[1];
__declspec(section ".data") s32 fd_eki_04___local_PI_383[1];
__declspec(section ".data") s32 fd_eki_04___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_eki_04_one_negone_373;
__declspec(section ".data") s32 fd_eki_04___local_PIO2_384[1];
__declspec(section ".data") s32 fd_eki_04_one_381[1];
__declspec(section ".data") u64 fd_eki_04_negone_one_360;
__declspec(section ".data") s32 fd_eki_04_neg_one_365[1];
__declspec(section ".data") s32 fd_eki_04___local_PI_366[1];
__declspec(section ".data") s32 fd_eki_04___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_eki_04_one_negone_359;
__declspec(section ".data") s32 fd_eki_04___local_PIO2_367[1];
__declspec(section ".data") s32 fd_eki_04_one_364[1];
static __declspec(section ".data") s32 e_close[12];
static __declspec(section ".data") s32 e_open[12];
static __declspec(section ".data") s32 s_close[12];
static __declspec(section ".data") s32 s_open[12];
static s32 bero_data[45];
s32 evt_jump[21];
s32 eki_04_init_evt[66];

__declspec(section ".data") u64 fd_eki_04_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_04_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_04___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_04___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_04_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_04___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_04_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_eki_04_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_04_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_04___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_04___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_04_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_04___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_04_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(e_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("e_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("e_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("s_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("s_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"e_bero", 65539, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"eki_03", (s32)"w_bero_2", 327685, (s32)e_close, (s32)e_open, (s32)"s_bero",
    65539, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"eki_05", (s32)"n_bero", 327685, (s32)s_close, (s32)s_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_jump)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_jump_jumpstand, 360, -900, 70, 300, 700, 75, 310, -900, 65, 6000, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(eki_04_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_cam_road_reset)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG6_EKI2"))
    CALL(evt_mobj_jumpstand_red, 0, STRING("mobj_jump"), 360, -900, 70, PTR(evt_jump), 0)
    CALL(evt_item_entry, STRING("item01"), 152, -250, -815, 70, 16, GSWF(3744), 0)
    CALL(evt_item_entry, STRING("item02"), 262, -250, 230, 40, 16, GSWF(3747), 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("futi_"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("hasira"), 2)
    IF_INT_LESS(GSW(0), 316)
        SET_VALUE(GSW(0), 316)
    END_IF
    RETURN
EVT_END()

