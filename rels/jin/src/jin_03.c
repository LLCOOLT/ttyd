#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_kagemario_init_14_text_4DB8);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill_14_data_AF00[];

__declspec(section ".data") u64 fd_jin_03_negone_one_374;
__declspec(section ".data") s32 fd_jin_03_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_03___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_03_one_negone_373;
__declspec(section ".data") s32 fd_jin_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_03_one_381[1];
__declspec(section ".data") u64 fd_jin_03_negone_one_360;
__declspec(section ".data") s32 fd_jin_03_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_03___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_03_one_negone_359;
__declspec(section ".data") s32 fd_jin_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_03_one_364[1];
static __declspec(section ".data") s32 n_close[12];
static __declspec(section ".data") s32 n_open[12];
static __declspec(section ".data") s32 s_close[12];
static __declspec(section ".data") s32 s_open[12];
static __declspec(section ".data") s32 w1_close[12];
static __declspec(section ".data") s32 w1_open[12];
static __declspec(section ".data") s32 w2_close[12];
static __declspec(section ".data") s32 w2_open[12];
__declspec(section ".data") s32 w3_close[12];
__declspec(section ".data") s32 w3_open[12];
static s32 bero_entry_data[90];
s32 jin_03_kaidan_temae_kesu[13];
s32 jin_03_kaidan_naka_kesu[13];
s32 jin_03_kaidan_oku_kesu[13];
s32 jin_03_init_evt[55];

__declspec(section ".data") u64 fd_jin_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_03_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(n_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door01"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door01"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w1_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00A"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w1_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00A"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w2_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00B"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w2_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00B"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(w3_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00C"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(w3_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00C"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"n_bero", 65538, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"jin_01", (s32)"s_bero_2", 327685, (s32)n_close, (s32)n_open, (s32)"s_bero",
    65538, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"jin_02", (s32)"n_bero_2", 327685, (s32)s_close, (s32)s_open, (s32)"w_bero3", 65538,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"jin_00", (s32)"e_bero_3", 327685, (s32)w1_close, (s32)w1_open, (s32)"w_bero1", 65538, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"jin_00",
    (s32)"e_bero_1", 327685, (s32)w3_close, (s32)w3_open, (s32)"w_bero2", 65538, 20000, 100000,
    0, 0, -1, 0, -1, 0, (s32)"jin_00", (s32)"e_bero_2",
    327685, (s32)w2_close, (s32)w2_open, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

EVT_BEGIN(jin_03_kaidan_temae_kesu)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kaidan01"), 1)
    CALL(evt_hitobj_onoff, STRING("a_kaidan01"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_03_kaidan_naka_kesu)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kaidan02"), 1)
    CALL(evt_hitobj_onoff, STRING("a_kaidan02"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_03_kaidan_oku_kesu)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kaidan03"), 1)
    CALL(evt_hitobj_onoff, STRING("a_kaidan03"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init_14_text_4DB8)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_14_data_AF00))
    IF_INT_EQUAL(LSW(1), 0)
        SPAWN_EVENT(PTR(jin_03_kaidan_temae_kesu))
        SPAWN_EVENT(PTR(jin_03_kaidan_oku_kesu))
        ELSE
        IF_INT_EQUAL(LSW(1), 1)
            SPAWN_EVENT(PTR(jin_03_kaidan_naka_kesu))
            SPAWN_EVENT(PTR(jin_03_kaidan_oku_kesu))
            ELSE
            SPAWN_EVENT(PTR(jin_03_kaidan_temae_kesu))
            SPAWN_EVENT(PTR(jin_03_kaidan_naka_kesu))
        END_IF
    END_IF
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 125, 0, 0, STRING("S_yuka\0"), 125, GSWF(5634))
    RETURN
EVT_END()

