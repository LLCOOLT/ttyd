#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_ctrl_onoff);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_in);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_party_dispflg_onoff);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_sub_get_system_flag);

__declspec(section ".data") u64 fd_gor_11_negone_one_374;
__declspec(section ".data") s32 fd_gor_11_neg_one_382[1];
__declspec(section ".data") s32 fd_gor_11___local_PI_383[1];
__declspec(section ".data") s32 fd_gor_11___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gor_11_one_negone_373;
__declspec(section ".data") s32 fd_gor_11___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gor_11_one_381[1];
__declspec(section ".data") u64 fd_gor_11_negone_one_360;
__declspec(section ".data") s32 fd_gor_11_neg_one_365[1];
__declspec(section ".data") s32 fd_gor_11___local_PI_366[1];
__declspec(section ".data") s32 fd_gor_11___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gor_11_one_negone_359;
__declspec(section ".data") s32 fd_gor_11___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gor_11_one_364[1];
static s32 epilogue_evt[62];
s32 gor_11_init_evt[29];

__declspec(section ".data") u64 fd_gor_11_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gor_11_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gor_11___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gor_11___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gor_11_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gor_11___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gor_11_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gor_11_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gor_11_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gor_11___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gor_11___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gor_11_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gor_11___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gor_11_one_364[] = {
    1065353216,
};

static EVT_BEGIN(epilogue_evt)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_END_MUJ1"))
    CALL(evt_cam_ctrl_onoff, 4, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_party_dispflg_onoff, 0, 1, 1)
    CALL(evt_seq_wait, 2)
    CALL(evt_fade_entry, 10, 1, 0, 0, 0)
    WAIT_MS(2000)
    WAIT_MS(3000)
    CALL(evt_fade_in, 1000)
    WAIT_MS(5000)
    CALL(evt_snd_envoff_f, 512, 3000)
    CALL(evt_fade_set_mapchange_type, 0, 10, 1500, -1, -1)
    CALL(evt_bero_mapchange, STRING("gor_00"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(gor_11_init_evt)
    CALL(evt_map_playanim, STRING("anm_umi"), 1, 0)
    CALL(evt_map_playanim, STRING("anm_nami"), 1, 0)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 2)
        RETURN
    END_IF
    IF_INT_EQUAL(GSW(0), 402)
        CALL(evt_mario_kill_party, 0)
        SPAWN_EVENT(PTR(epilogue_evt))
    END_IF
    RETURN
EVT_END()

