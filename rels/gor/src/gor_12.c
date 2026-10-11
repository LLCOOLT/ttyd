#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_ctrl_onoff);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_party_dispflg_onoff);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_envon);
extern s32 evt_map_playanim[];
extern s32 evt_mario_kill_party[];
extern s32 evt_sub_get_system_flag[];

__declspec(section ".data") u64 fd_gor_12_negone_one_374;
__declspec(section ".data") s32 fd_gor_12_neg_one_382[1];
__declspec(section ".data") s32 fd_gor_12___local_PI_383[1];
__declspec(section ".data") s32 fd_gor_12___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gor_12_one_negone_373;
__declspec(section ".data") s32 fd_gor_12___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gor_12_one_381[1];
__declspec(section ".data") u64 fd_gor_12_negone_one_360;
__declspec(section ".data") s32 fd_gor_12_neg_one_365[1];
__declspec(section ".data") s32 fd_gor_12___local_PI_366[1];
__declspec(section ".data") s32 fd_gor_12___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gor_12_one_negone_359;
__declspec(section ".data") s32 fd_gor_12___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gor_12_one_364[1];
static s32 epilogue_evt[49];
s32 gor_12_init_evt[35];

__declspec(section ".data") u64 fd_gor_12_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gor_12_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gor_12___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gor_12___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gor_12_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gor_12___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gor_12_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gor_12_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gor_12_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gor_12___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gor_12___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gor_12_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gor_12___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gor_12_one_364[] = {
    1065353216,
};

static EVT_BEGIN(epilogue_evt)
    CALL(evt_snd_envon, 272, STRING("ENV_END_MUJ1"))
    CALL(evt_cam_ctrl_onoff, 4, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_party_dispflg_onoff, 0, 1, 1)
    CALL(evt_seq_wait, 2)
    WAIT_MS(7000)
    CALL(evt_snd_bgmoff_f, 512, 8000)
    CALL(evt_snd_envoff_f, 512, 8000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 4000, 9, 300)
    CALL(evt_bero_mapchange, STRING("aaa_00"), STRING(""))
    RETURN
EVT_END()

s32 gor_12_init_evt[] = {
    262235, (s32)evt_map_playanim, (s32)"anm_umi", 1, 0, 262235, (s32)evt_map_playanim, (s32)"anm_nami",
    1, 0, 262235, (s32)evt_map_playanim, (s32)"anm_kirakira", 1, 0, 131163,
    (s32)evt_sub_get_system_flag, -30000000, 131102, -30000000, 2, 2, 33, 131096,
    -170000000, 402, 131163, (s32)evt_mario_kill_party, 0, 65628, (s32)epilogue_evt, 33,
    2, 1, 0,
};

