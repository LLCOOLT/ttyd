#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_tou_13_negone_one_374;
__declspec(section ".data") s32 fd_tou_13_neg_one_382[1];
__declspec(section ".data") s32 fd_tou_13___local_PI_383[1];
__declspec(section ".data") s32 fd_tou_13___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tou_13_one_negone_373;
__declspec(section ".data") s32 fd_tou_13___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tou_13_one_381[1];
__declspec(section ".data") u64 fd_tou_13_negone_one_360;
__declspec(section ".data") s32 fd_tou_13_neg_one_365[1];
__declspec(section ".data") s32 fd_tou_13___local_PI_366[1];
__declspec(section ".data") s32 fd_tou_13___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tou_13_one_negone_359;
__declspec(section ".data") s32 fd_tou_13___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tou_13_one_364[1];
static s32 bero_data[45];
static s32 evt_dakuto[44];
s32 evt_nusumi[182];
static s32 evt_first[42];
s32 tou_13_init_evt[117];

__declspec(section ".data") u64 fd_tou_13_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_13_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_13___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_13___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_13_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_13___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_13_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tou_13_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_13_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_13___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_13___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_13_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_13___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_13_one_364[] = {
    1065353216,
};

static s32 bero_data[] = {
    (s32)"e_bero_", 0, 6, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tou_07", (s32)"e_bero", 0, 0, 0, (s32)"w_bero_",
    0, 2, 100000, 0, 0, -1, 0, -1,
    0, (s32)"tou_05", (s32)"w_bero", 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_dakuto)
    CALL(evt_cam_shake, 4, FLOAT(0.049804688f), FLOAT(0.0f), 500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DUCT_KOUSHI_HIT1"), 188, 0, 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_deguti"), 1)
    CALL(evt_hitobj_onoff, STRING("deguti"), 1, 0)
    SET_VALUE(LW(0), 1)
    CALL_CHILD(PTR(bero_case_switch_on))
    IF_INT_LESS(GSW(0), 162)
        SET_VALUE(GSW(0), 162)
        ELSE
        SET_VALUE(GSWF(2501), 1)
    END_IF
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(evt_nusumi)
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), 75)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_wait_landon)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_toge, 2, 200, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_01"), 0, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING("m"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING("p"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 60, 0, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 100, 0, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_cam3d_evt_set, 125, 100, 337, 125, 40, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 200, 40, 0)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_02"), 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_455_05"))
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 200, 40, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_03"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 200, 40, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_04"), 0, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(0), 161)
    RETURN
EVT_END()

static EVT_BEGIN(evt_first)
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), -120)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_wait_landon)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_455"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(0), 160)
    RETURN
EVT_END()

EVT_BEGIN(tou_13_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(127, 137)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU2"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU7"))
        CALL(evt_snd_bgmoff, 26624)
        CASE_GREATER_OR_EQUAL(165)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU2"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU7"))
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU7"))
        CALL(evt_snd_set_rev_mode, 2)
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SWITCH(GSW(0))
        CASE_LESS(162)
        SET_VALUE(LF(0), 0)
        CASE_LESS(172)
        SET_VALUE(LF(0), 1)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2501), 0)
            SET_VALUE(LF(0), 0)
            ELSE
            SET_VALUE(LF(0), 1)
        END_IF
    END_SWITCH
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_run_case_evt, 14, 1, STRING("deguti"), 0, PTR(evt_dakuto), 0)
        SET_VALUE(LW(0), 1)
        CALL_CHILD(PTR(bero_case_switch_off))
        ELSE
        CALL(evt_hitobj_onoff, STRING("deguti"), 1, 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_deguti"), 1)
    END_IF
    IF_INT_LESS(GSW(0), 161)
        SPAWN_EVENT(PTR(evt_nusumi))
    END_IF
    IF_INT_LESS(GSW(0), 160)
        SPAWN_EVENT(PTR(evt_first))
    END_IF
    RETURN
EVT_END()

