#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mobj_switch_red);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_random);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill[];

__declspec(section ".data") u64 fd_jin_02_negone_one_374;
__declspec(section ".data") s32 fd_jin_02_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_02___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_02_one_negone_373;
__declspec(section ".data") s32 fd_jin_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_02_one_381[1];
__declspec(section ".data") u64 fd_jin_02_negone_one_360;
__declspec(section ".data") s32 fd_jin_02_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_02___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_02_one_negone_359;
__declspec(section ".data") s32 fd_jin_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_02_one_364[1];
static __declspec(section ".data") s32 n2_close[12];
static __declspec(section ".data") s32 n2_open[12];
__declspec(section ".data") s32 n1_close[12];
__declspec(section ".data") s32 n1_open[12];
static s32 bero_entry_data[45];
static s32 cam_shake[62];
s32 evt_kaidan_temae[144];
s32 jin_02_init_evt[33];

__declspec(section ".data") u64 fd_jin_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_02_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(n2_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door03"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n2_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door03"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n1_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n1_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"n_bero_2", 65538, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"jin_03", (s32)"s_bero", 327685, (s32)n2_close, (s32)n2_open, (s32)"n_bero_1",
    65538, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"jin_00", (s32)"s_bero", 327685, (s32)n1_close, (s32)n1_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(cam_shake)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_KAIDAN_MOVE1"), 300, 100, -200, LW(9))
    CALL(evt_sub_intpl_init, 11, 0, 10, 30)
    LABEL(0)
    CALL(evt_sub_intpl_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(evt_cam_shake, 4, LW(0), FLOAT(0.0f), 100)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_sub_intpl_init, 11, 10, 0, 30)
    LABEL(1)
    CALL(evt_sub_intpl_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(evt_cam_shake, 4, LW(0), FLOAT(0.0f), 100)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_snd_sfxoff, LW(9))
    RETURN
EVT_END()

EVT_BEGIN(evt_kaidan_temae)
    IF_INT_NOT_EQUAL(LSW(1), 1)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mario_normalize)
        CALL(evt_party_stop, 0)
        IF_INT_EQUAL(GSWF(2234), 0)
            BEGIN_INLINE_EVENT_GET_ID(LW(3))
                WAIT_MS(500)
                CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                WAIT_MS(1000)
                LOOP(0)
                    CALL(evt_sub_random, 200, LW(0))
                    ADD(LW(0), 300)
                    CALL(evt_mario_set_dir, 90, LW(0), 0)
                    WAIT_MS(LW(0))
                    CALL(evt_sub_random, 300, LW(0))
                    ADD(LW(0), 400)
                    CALL(evt_mario_set_dir, 270, LW(0), 0)
                    WAIT_MS(LW(0))
                END_LOOP
            END_INLINE_EVENT
            BEGIN_INLINE_EVENT_GET_ID(LW(4))
                WAIT_MS(500)
                CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
                WAIT_MS(1000)
                LOOP(0)
                    CALL(evt_sub_random, 200, LW(0))
                    ADD(LW(0), 400)
                    CALL(evt_party_set_dir, 0, 90, LW(0))
                    WAIT_MS(LW(0))
                    CALL(evt_sub_random, 200, LW(0))
                    ADD(LW(0), 200)
                    CALL(evt_party_set_dir, 0, 270, LW(0))
                    WAIT_MS(LW(0))
                END_LOOP
            END_INLINE_EVENT
        END_IF
        CALL_CHILD(PTR(cam_shake))
        IF_INT_EQUAL(GSWF(2234), 0)
            WAIT_MS(500)
            DELETE_EVENT(LW(3))
            DELETE_EVENT(LW(4))
            SET_VALUE(GSWF(2234), 1)
        END_IF
        ADD(LSW(1), 1)
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_party_run, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(jin_02_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN2"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    CALL(evt_mobj_switch_red, 0, STRING("mobj_switch1\0\0\0"), 485, 30, -10, PTR(evt_kaidan_temae), 0)
    RETURN
EVT_END()

