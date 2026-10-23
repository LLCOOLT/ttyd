#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);

__declspec(section ".data") u64 fd_rsh_08_negone_one_374;
__declspec(section ".data") s32 fd_rsh_08_neg_one_382[1];
__declspec(section ".data") s32 fd_rsh_08___local_PI_383[1];
__declspec(section ".data") s32 fd_rsh_08___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_rsh_08_one_negone_373;
__declspec(section ".data") s32 fd_rsh_08___local_PIO2_384[1];
__declspec(section ".data") s32 fd_rsh_08_one_381[1];
__declspec(section ".data") u64 fd_rsh_08_negone_one_360;
__declspec(section ".data") s32 fd_rsh_08_neg_one_365[1];
__declspec(section ".data") s32 fd_rsh_08___local_PI_366[1];
__declspec(section ".data") s32 fd_rsh_08___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_rsh_08_one_negone_359;
__declspec(section ".data") s32 fd_rsh_08___local_PIO2_367[1];
__declspec(section ".data") s32 fd_rsh_08_one_364[1];
s32 bero_data_a_nidome[30];
s32 bero_data_b_nidome[30];
s32 bero_data_c_nidome[30];
s32 rsh_08_a_init_evt[72];

__declspec(section ".data") u64 fd_rsh_08_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_08_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_08___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_08___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_08_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_08___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_08_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_rsh_08_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_08_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_08___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_08___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_08_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_08___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_08_one_364[] = {
    1065353216,
};

s32 bero_data_a_nidome[] = {
    (s32)"e_bero", 65544, 6, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_01_a", (s32)"e_bero", 65537, (s32)"e_door_close", (s32)"e_door_open", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 bero_data_b_nidome[] = {
    (s32)"e_bero", 65544, 6, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_01_b", (s32)"e_bero", 65537, (s32)"e_door_close", (s32)"e_door_open", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 bero_data_c_nidome[] = {
    (s32)"e_bero", 65544, 6, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_01_c", (s32)"e_bero", 65537, (s32)"e_door_close", (s32)"e_door_open", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(rsh_08_a_init_evt)
    IF_INT_EQUAL(GSWF(3460), 1)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        ELSE
        IF_INT_EQUAL(GSWF(3461), 1)
            CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_GOR1"))
            CALL(evt_snd_envoff, 512)
            CALL(evt_snd_bgmoff, 26624)
            ELSE
            CALL(evt_snd_bgmoff, 512)
            CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
        END_IF
    END_IF
    SET_VALUE(LW(0), PTR(bero_data_a_nidome))
    IF_INT_EQUAL(GSWF(3453), 1)
        SET_VALUE(LW(0), PTR(bero_data_a_nidome))
    END_IF
    IF_INT_EQUAL(GSWF(3454), 1)
        SET_VALUE(LW(0), PTR(bero_data_b_nidome))
    END_IF
    IF_INT_EQUAL(GSWF(3455), 1)
        SET_VALUE(LW(0), PTR(bero_data_c_nidome))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_map_playanim, STRING("yure\0\0\0"), 1, 0)
    RETURN
EVT_END()

