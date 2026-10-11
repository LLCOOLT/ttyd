#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_muj_11_negone_one_374;
__declspec(section ".data") s32 fd_muj_11_neg_one_382[1];
__declspec(section ".data") s32 fd_muj_11___local_PI_383[1];
__declspec(section ".data") s32 fd_muj_11___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_muj_11_one_negone_373;
__declspec(section ".data") s32 fd_muj_11___local_PIO2_384[1];
__declspec(section ".data") s32 fd_muj_11_one_381[1];
__declspec(section ".data") u64 fd_muj_11_negone_one_360;
__declspec(section ".data") s32 fd_muj_11_neg_one_365[1];
__declspec(section ".data") s32 fd_muj_11___local_PI_366[1];
__declspec(section ".data") s32 fd_muj_11___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_muj_11_one_negone_359;
__declspec(section ".data") s32 fd_muj_11___local_PIO2_367[1];
__declspec(section ".data") s32 fd_muj_11_one_364[1];
static __declspec(section ".data") s32 w_close[12];
static __declspec(section ".data") s32 w_open[12];
static __declspec(section ".data") s32 e_close[12];
static __declspec(section ".data") s32 e_open[12];
static s32 bero_entry_data[45];
s32 warning_event[38];
s32 muj_11_init_evt[35];

__declspec(section ".data") u64 fd_muj_11_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_muj_11_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_muj_11___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_muj_11___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_muj_11_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_muj_11___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_muj_11_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_muj_11_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_muj_11_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_muj_11___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_muj_11___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_muj_11_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_muj_11___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_muj_11_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65538, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"muj_10", (s32)"A_b_bero03", 327685, (s32)w_close, (s32)w_open, (s32)"e_bero",
    65538, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"muj_12", (s32)"w_bero", 327685, (s32)e_close, (s32)e_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(warning_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon, STRING("SFX_STG5_ELMOS_VOICE1"), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon, STRING("SFX_STG5_ELMOS_VOICE1"), 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg5_dou_20"), 0, 0)
    SET_VALUE(GSW(0), 252)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(muj_11_init_evt)
    IF_INT_LESS(GSW(0), 253)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG5_GHOST1"))
        CALL(evt_snd_envoff, 512)
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG5_DOU1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG5_MUJ9"))
    END_IF
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_EQUAL(GSW(0), 251)
        SPAWN_EVENT(PTR(warning_event))
    END_IF
    RETURN
EVT_END()

