#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_set_mode);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_kamek_kemuri2);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_scale);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_sfx_pos);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_sincos);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
extern s32 evt_memcard_save[];
extern s32 evt_npc_setup[];
extern s32 evt_snd_envon[];
extern s32 npc_init_evt[];

__declspec(section ".data") u64 fd_kpa_00_negone_one_374;
__declspec(section ".data") s32 fd_kpa_00_neg_one_382[1];
__declspec(section ".data") s32 fd_kpa_00___local_PI_383[1];
__declspec(section ".data") s32 fd_kpa_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_kpa_00_one_negone_373;
__declspec(section ".data") s32 fd_kpa_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_kpa_00_one_381[1];
__declspec(section ".data") u64 fd_kpa_00_negone_one_360;
__declspec(section ".data") s32 fd_kpa_00_neg_one_365[1];
__declspec(section ".data") s32 fd_kpa_00___local_PI_366[1];
__declspec(section ".data") s32 fd_kpa_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_kpa_00_one_negone_359;
__declspec(section ".data") s32 fd_kpa_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_kpa_00_one_364[1];
s32 kpa_00_first_evt[61];
s32 kpa_00_fly_evt[380];
static s32 npcEnt[69];
s32 kpa_00_init_evt[24];

__declspec(section ".data") u64 fd_kpa_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_kpa_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_00_one_364[] = {
    1065353216,
};

EVT_BEGIN(kpa_00_first_evt)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mario_set_pos, -1000, 0, 0)
    CALL(evt_cam3d_evt_set, 0, 292, 534, 0, 203, -8, 0, 11)
    CALL(evt_seq_wait, 2)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STGK_CASTLE1"))
        CALL(evt_snd_bgm_scope, 0, 1)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 134, 534, 0, 45, -8, 5000, 11)
    WAIT_MS(4500)
    WAIT_MS(500)
    WAIT_MS(1000)
    CALL(evt_bero_mapchange, STRING("kpa_01"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(kpa_00_fly_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ババ"), 262144)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("飛クッパ"), 0, 30, -15)
    CALL(evt_npc_set_scale, STRING("飛クッパ"), FLOAT(0.099609375f), FLOAT(0.099609375f), FLOAT(0.099609375f))
    CALL(evt_npc_set_ry, STRING("飛クッパ"), 90)
    CALL(evt_npc_set_position, STRING("ババ"), 10, 20, 0)
    CALL(evt_npc_set_scale, STRING("ババ"), FLOAT(0.099609375f), FLOAT(0.099609375f), FLOAT(0.099609375f))
    CALL(evt_npc_set_ry, STRING("ババ"), 90)
    CALL(evt_cam3d_evt_set, 0, 134, 534, 0, 45, -8, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(500)
    SET_FLOAT_VALUE(GW(0), FLOAT(-1.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.25f))
    SET_FLOAT_VALUE(GW(2), FLOAT(0.0f))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 3000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_sub_get_sincos, LW(0), LW(2), LW(3))
        SET_FLOAT_VALUE(GW(0), LW(3))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_sub_intpl_msec_init, 11, 90, 0, 3000)
        LABEL(3)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_sub_get_sincos, LW(0), LW(2), LW(3))
        SET_FLOAT_VALUE(GW(2), LW(3))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(3)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_sub_intpl_msec_init, 11, 100, 600, 2000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
        CALL(evt_npc_set_scale, STRING("飛クッパ"), LW(0), LW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1500)
        CALL(evt_sub_intpl_msec_init, 11, 100, 600, 2000)
        LABEL(5)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
        CALL(evt_npc_set_scale, STRING("ババ"), LW(0), LW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(5)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1500)
        CALL(evt_npc_kamek_kemuri2, STRING("ババ"), 2000, 1)
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(4), -1000)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 1)
                BREAK_LOOP
            END_IF
            ADD(LW(4), 30)
            CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_FLY1"), LW(0), LW(1), LW(4), LW(3))
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_sub_intpl_msec_init, 11, 10, 190, 3000)
        LABEL(4)
        CALL(evt_sub_intpl_msec_get_value)
        SET_FLOAT_VALUE(LW(2), GW(2))
        MULTIPLY_FLOAT(LW(2), FLOAT(60.0f))
        ADD_FLOAT(LW(2), FLOAT(20.0f))
        CALL(evt_npc_set_position, STRING("ババ"), LW(0), LW(2), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(4)
        END_IF
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_AIRSHIP_MOVE1"), 0, 0, 0, LW(3))
    SET_VALUE(LW(4), -1000)
    CALL(evt_sub_intpl_msec_init, 11, 0, 210, 3000)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    SET_FLOAT_VALUE(LW(2), GW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(40.0f))
    ADD_FLOAT(LW(2), FLOAT(70.0f))
    ADD(LW(4), 3)
    CALL(evt_npc_set_position, STRING("飛クッパ"), LW(0), LW(2), -15)
    CALL(evt_snd_sfx_pos, LW(3), LW(0), LW(2), LW(4))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_snd_sfxoff, LW(3))
    WAIT_MS(800)
    SET_VALUE(GSW(0), 61)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 6, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 3)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 0)
    CALL(evt_fade_set_mapchange_type, 1, 59, 0, 58, 0)
    CALL(evt_bero_mapchange, STRING("nok_01"), STRING("nokotarou"))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ババ"*/"\x83\x6F\x83\x6F", 32, 0, (s32)npc_init_evt, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"飛クッパ"*/"\x94\xF2\x83\x4E\x83\x62\x83\x70",
    32, 0, (s32)npc_init_evt, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

s32 kpa_00_init_evt[] = {
    131163, (s32)evt_mario_set_mode, 2, 196699, (s32)evt_snd_envon, 272, (s32)"ENV_KOOPA_KPA1\0", 131163,
    (s32)evt_npc_setup, (s32)npcEnt, 65570, -170000000, 65572, 59, 65628, (s32)kpa_00_first_evt,
    65572, 60, 65628, (s32)kpa_00_fly_evt, 49, 2, 1, 0,
};

