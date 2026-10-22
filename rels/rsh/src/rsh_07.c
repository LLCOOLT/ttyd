#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_sub_get_mapname);
extern s32 evt_bero_info_run[];
extern s32 evt_rsh_window[];

__declspec(section ".data") u64 fd_rsh_07_negone_one_374;
__declspec(section ".data") s32 fd_rsh_07_neg_one_382[1];
__declspec(section ".data") s32 fd_rsh_07___local_PI_383[1];
__declspec(section ".data") s32 fd_rsh_07___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_rsh_07_one_negone_373;
__declspec(section ".data") s32 fd_rsh_07___local_PIO2_384[1];
__declspec(section ".data") s32 fd_rsh_07_one_381[1];
__declspec(section ".data") u64 fd_rsh_07_negone_one_360;
__declspec(section ".data") s32 fd_rsh_07_neg_one_365[1];
__declspec(section ".data") s32 fd_rsh_07___local_PI_366[1];
__declspec(section ".data") s32 fd_rsh_07___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_rsh_07_one_negone_359;
__declspec(section ".data") s32 fd_rsh_07___local_PIO2_367[1];
__declspec(section ".data") s32 fd_rsh_07_one_364[1];
static s32 bero_data_a[30];
static s32 bero_data_b[30];
static s32 bero_data_c[30];
static __declspec(section ".data") s32 init_unten[6];
static s32 talk_unten[19];
static s32 npc_data[46];
static __declspec(section ".data") s32 access_tbl[5];
static s32 evt_access[14];
static s32 evt_access_entry[23];
s32 rsh_07_init_evt[113];
__declspec(section ".data") s32 rsh_07_a_init_evt[11];
__declspec(section ".data") s32 rsh_07_b_init_evt[11];
static __declspec(section ".data") s32 window_tbl[5];
s32 rsh_07_c_init_evt[16];

__declspec(section ".data") u64 fd_rsh_07_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_07_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_07___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_07___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_07_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_07___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_07_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_rsh_07_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_07_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_07___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_07___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_07_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_07___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_07_one_364[] = {
    1065353216,
};

static s32 bero_data_a[] = {
    (s32)"e_bero", 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_04_a", (s32)"w_bero", 65537, (s32)"w_door_close", (s32)"w_door_open", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static s32 bero_data_b[] = {
    (s32)"w_bero", 65536, 2, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_04_b", (s32)"w_bero", 65537, (s32)"w_door_close", (s32)"w_door_open", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static s32 bero_data_c[] = {
    (s32)"w_bero", 65536, 2, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_04_c", (s32)"w_bero", 65537, (s32)"w_door_close", (s32)"w_door_open", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static __declspec(section ".data") EVT_BEGIN(init_unten)
    CALL(evt_npc_set_ry, STRING("me"), 270)
    RETURN
EVT_END()

static EVT_BEGIN(talk_unten)
    IF_INT_EQUAL(GSWF(3581), 0)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_08"), 0, 0)
        ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_08_1"), 0, 0)
    END_IF
    RETURN
EVT_END()

static s32 npc_data[] = {
    (s32)/*"運転手"*/"\x89\x5E\x93\x5D\x8E\xE8", 1073874448, 0, (s32)init_unten, 0, (s32)talk_unten, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static __declspec(section ".data") s32 access_tbl[] = {
    (s32)"nittei", (s32)"stg6_rsh_c_00_1", (s32)"soujyuu", (s32)"stg6_rsh_260", 0,
};

static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, LW(1), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(access_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, 9, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(rsh_07_init_evt)
    IF_INT_EQUAL(GSWF(3579), 0)
        IF_INT_EQUAL(GSWF(3580), 0)
            IF_INT_EQUAL(GSWF(3581), 0)
                CALL(evt_map_playanim, STRING("yure"), 1, 0)
                CALL(evt_map_playanim, STRING("hai_sora"), 1, 0)
                CALL(evt_map_playanim, STRING("hai_yama"), 1, 0)
                CALL(evt_map_playanim, STRING("hai_iwayama"), 1, 0)
                CALL(evt_map_playanim, STRING("hai_saboten"), 1, 0)
            END_IF
        END_IF
    END_IF
    CALL(evt_npc_setup, PTR(npc_data))
    CALL_CHILD(PTR(evt_access_entry))
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 210, 60, -145, 0, 0)
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
            CALL(evt_sub_get_mapname, LW(0))
            IF_STR_EQUAL(LW(0), STRING("rsh_07_a"))
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH1"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_07_b"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_07_c"))
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH2"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(rsh_07_a_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_07_init_evt))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(rsh_07_b_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_07_init_evt))
    RETURN
EVT_END()

static __declspec(section ".data") s32 window_tbl[] = {
    (s32)"mado_uturi_1", (s32)"mado_uturi_2", (s32)"mado_uturi_3", (s32)"mado_uturi_4\0\0\0", 0,
};

EVT_BEGIN(rsh_07_c_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_07_init_evt))
    SET_VALUE(LW(0), PTR(window_tbl))
    CALL_CHILD(PTR(evt_rsh_window))
    RETURN
EVT_END()

