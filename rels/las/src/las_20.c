#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "las.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff64);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_delete);
USER_FUNC(evt_mobj_floatswitch_red);
USER_FUNC(evt_mobj_switch_red);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_sincos);
USER_FUNC(get_hosi_name);

__declspec(section ".data") u64 fd_las_20_negone_one_374;
__declspec(section ".data") s32 fd_las_20_neg_one_382[1];
__declspec(section ".data") s32 fd_las_20___local_PI_383[1];
__declspec(section ".data") s32 fd_las_20___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_20_one_negone_373;
__declspec(section ".data") s32 fd_las_20___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_20_one_381[1];
__declspec(section ".data") u64 fd_las_20_negone_one_360;
__declspec(section ".data") s32 fd_las_20_neg_one_365[1];
__declspec(section ".data") s32 fd_las_20___local_PI_366[1];
__declspec(section ".data") s32 fd_las_20___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_20_one_negone_359;
__declspec(section ".data") s32 fd_las_20___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_20_one_364[1];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[60];
static s32 haguruma_hontai[14];
static __declspec(section ".data") s32 haguruma_hontai2[6];
static __declspec(section ".data") s32 haguruma_kage[12];
static __declspec(section ".data") s32 haguruma_kage2[5];
static s32 haguruma_evt[194];
static s32 dai_evt[13];
s32 hosi_name[14];
s32 hosi_sw_check[303];
s32 hosi_onoff[69];
s32 hosi_02_sw_evt[15];
s32 hosi_03_sw_evt[15];
s32 hosi_04_sw_evt[15];
s32 hosi_05_sw_evt[15];
s32 hosi_06_sw_evt[15];
s32 hosi_07_sw_evt[15];
s32 hosi_08_sw_evt[15];
s32 hosi_init[175];
s32 las_20_init_evt[103];

__declspec(section ".data") u64 fd_las_20_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_20_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_20___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_20___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_20_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_20___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_20_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_20_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_20_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_20___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_20___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_20_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_20___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_20_one_364[] = {
    1065353216,
};

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"e_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_22", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, (s32)"s_bero_1",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_19", (s32)"n_bero", 65537, 0, 0, (s32)"s_bero_2", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"las_21", (s32)"n_bero", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 haguruma_hontai[] = {
    (s32)"S_hgm_01a", (s32)"S_hgm_02a", (s32)"S_hgm_03a", (s32)"S_hgm_04a", (s32)"S_hgm_06a", (s32)"S_hgm_07a", (s32)"S_hgm_08a", (s32)"S_hgm_10a",
    (s32)"S_hgm_11a", (s32)"S_hgm_14a", (s32)"S_hgm_15a", (s32)"S_hgm_16a", (s32)"S_hgm_19a", (s32)"S_hgm_20a",
};

static __declspec(section ".data") s32 haguruma_hontai2[] = {
    (s32)"S_hgm_05a", (s32)"S_hgm_09a", (s32)"S_hgm_12a", (s32)"S_hgm_13a", (s32)"S_hgm_17a", (s32)"S_hgm_18a",
};

static __declspec(section ".data") s32 haguruma_kage[] = {
    (s32)"S_hgm_01b", (s32)"S_hgm_02b", (s32)"S_hgm_03b", (s32)"S_hgm_04b", (s32)"S_hgm_06b", (s32)"S_hgm_07b", (s32)"S_hgm_08b", (s32)"S_hgm_10b",
    (s32)"S_hgm_11b", (s32)"S_hgm_14b", (s32)"S_hgm_15b", (s32)"S_hgm_16b",
};

static __declspec(section ".data") s32 haguruma_kage2[] = {
    (s32)"S_hgm_05b", (s32)"S_hgm_09b", (s32)"S_hgm_12b", (s32)"S_hgm_13b", (s32)"S_hgm_17b",
};

static EVT_BEGIN(haguruma_evt)
    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(4), FLOAT(0.0f))
    LOOP(0)
        SET_INT_READ_ADDR(PTR(haguruma_hontai))
        LOOP(14)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(0))
        END_LOOP
        SET_INT_READ_ADDR(PTR(haguruma_kage))
        LOOP(12)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(0))
        END_LOOP
        SET_INT_READ_ADDR(PTR(haguruma_hontai2))
        LOOP(6)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(1))
        END_LOOP
        SET_INT_READ_ADDR(PTR(haguruma_kage2))
        LOOP(5)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(1))
        END_LOOP
        CALL(evt_sub_get_sincos, LW(2), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(41.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_21a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_21b"), 0, 0, LW(5))
        CALL(evt_sub_get_sincos, LW(3), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(22.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_22a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_22b"), 0, 0, LW(5))
        CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(110.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_23a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_23b"), 0, 0, LW(5))
        ADD_FLOAT(LW(0), FLOAT(1.0f))
        IF_INT_GREATER_OR_EQUAL(LW(0), 360)
            SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(1), FLOAT(-1.0f))
        IF_INT_LESS_OR_EQUAL(LW(1), -360)
            ADD_FLOAT(LW(1), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(2), FLOAT(0.89941406f))
        IF_INT_GREATER_OR_EQUAL(LW(2), 360)
            SUBTRACT_FLOAT(LW(2), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(3), FLOAT(0.89941406f))
        IF_INT_GREATER_OR_EQUAL(LW(3), 360)
            SUBTRACT_FLOAT(LW(3), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(4), FLOAT(1.0f))
        IF_INT_GREATER_OR_EQUAL(LW(4), 360)
            SUBTRACT_FLOAT(LW(4), FLOAT(360.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(dai_evt)
    SET_VALUE(LW(0), STRING("S_move_dai"))
    SET_VALUE(LW(1), STRING("A_move_dai"))
    SET_VALUE(LW(2), 2700)
    CALL_CHILD(PTR(move_dai))
    RETURN
EVT_END()

s32 hosi_name[] = {
    (s32)"S_hosi_02a", (s32)"S_hosi_02b", (s32)"S_hosi_03a", (s32)"S_hosi_03b", (s32)"S_hosi_04a", (s32)"S_hosi_04b", (s32)"S_hosi_05a", (s32)"S_hosi_05b",
    (s32)"S_hosi_06a", (s32)"S_hosi_06b", (s32)"S_hosi_07a", (s32)"S_hosi_07b", (s32)"S_hosi_08a", (s32)"S_hosi_08b",
};

EVT_BEGIN(hosi_sw_check)
    SET_VALUE(LW(0), 0)
    IF_INT_EQUAL(LSWF(1), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(2), 0)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(3), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(4), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(5), 0)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(6), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(7), 0)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 7)
        CALL(evt_mario_key_onoff, 0)
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, -289, 112, 1038, -289, -43, -63, 800, 11)
        WAIT_MS(800)
        SET_VALUE(LW(0), 0)
        LOOP(7)
            CALL(get_hosi_name, LW(0), LW(1), LW(2))
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(1), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, LW(2), 1)
            ADD(LW(0), 1)
        END_LOOP
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(1), 6)
        LOOP(50)
            CALL(get_hosi_name, LW(0), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, 1, 0, LW(2), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(3), 1)
            CALL(get_hosi_name, LW(1), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(2), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, LW(3), 1)
            WAIT_MS(50)
            SET_VALUE(LW(1), LW(0))
            ADD(LW(0), 1)
            MODULO(LW(0), 7)
        END_LOOP
        LOOP(0)
            IF_INT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            CALL(get_hosi_name, LW(0), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, 1, 0, LW(2), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(3), 1)
            CALL(get_hosi_name, LW(1), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(2), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, LW(3), 1)
            WAIT_MS(50)
            SET_VALUE(LW(1), LW(0))
            ADD(LW(0), 1)
            MODULO(LW(0), 7)
        END_LOOP
        CALL(get_hosi_name, LW(1), LW(2), LW(3))
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(2), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(3), 1)
        WAIT_MS(200)
        SET_VALUE(LW(0), 0)
        LOOP(7)
            CALL(get_hosi_name, LW(0), LW(1), LW(2))
            CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(2), 1)
            ADD(LW(0), 1)
        END_LOOP
        CALL(evt_snd_sfxon, STRING("SFX_STG8_STAR_LIGHTUP2"), 0)
        WAIT_MS(100)
        CALL(evt_snd_sfxon, STRING("SFX_STG8_QUAKE3"), LW(10))
        CALL(evt_cam_shake, 4, FLOAT(0.01953125f), FLOAT(0.0f), 1000)
        CALL(evt_snd_sfxoff, LW(10))
        CALL(evt_mobj_delete, STRING("hosi_02_sw"))
        CALL(evt_mobj_delete, STRING("hosi_03_sw"))
        CALL(evt_mobj_delete, STRING("hosi_04_sw"))
        CALL(evt_mobj_delete, STRING("hosi_05_sw"))
        CALL(evt_mobj_delete, STRING("hosi_06_sw"))
        CALL(evt_mobj_delete, STRING("hosi_07_sw"))
        CALL(evt_mobj_delete, STRING("hosi_08_sw"))
        SET_VALUE(GSW(0), 395)
        CALL(evt_cam3d_evt_off, 800, 11)
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(hosi_onoff)
    GET_INT_INDEXED(LW(2), LW(3))
    IF_INT_EQUAL(LW(3), 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(0), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(1), 1)
        SET_INT_INDEXED(LW(2), 1)
        CALL(evt_mapobj_get_position, LW(0), LW(3), LW(4), LW(5))
        CALL(evt_eff64, 0, STRING("stardust_n64"), 2, LW(3), LW(4), LW(5), 30, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG8_STAR_LIGHTUP1"), LW(3), LW(4), LW(5), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(0), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 1)
        SET_INT_INDEXED(LW(2), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(hosi_02_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_02a"))
    SET_VALUE(LW(1), STRING("S_hosi_02b"))
    SET_RAW_VALUE(LW(2), LSWF(1))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_03_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_03a"))
    SET_VALUE(LW(1), STRING("S_hosi_03b"))
    SET_RAW_VALUE(LW(2), LSWF(2))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_04_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_04a"))
    SET_VALUE(LW(1), STRING("S_hosi_04b"))
    SET_RAW_VALUE(LW(2), LSWF(3))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_05_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_05a"))
    SET_VALUE(LW(1), STRING("S_hosi_05b"))
    SET_RAW_VALUE(LW(2), LSWF(4))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_06_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_06a"))
    SET_VALUE(LW(1), STRING("S_hosi_06b"))
    SET_RAW_VALUE(LW(2), LSWF(5))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_07_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_07a"))
    SET_VALUE(LW(1), STRING("S_hosi_07b"))
    SET_RAW_VALUE(LW(2), LSWF(6))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_08_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_08a"))
    SET_VALUE(LW(1), STRING("S_hosi_08b"))
    SET_RAW_VALUE(LW(2), LSWF(7))
    CALL_CHILD(PTR(hosi_onoff))
    CALL_CHILD(PTR(hosi_sw_check))
    RETURN
EVT_END()

EVT_BEGIN(hosi_init)
    IF_INT_LESS(GSW(0), 395)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_02a"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_03a"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_04a"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_05a"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_06a"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_07a"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_08a"), 1)
        SET_VALUE(LSWF(1), 0)
        SET_VALUE(LSWF(2), 0)
        SET_VALUE(LSWF(3), 0)
        SET_VALUE(LSWF(4), 0)
        SET_VALUE(LSWF(5), 0)
        SET_VALUE(LSWF(6), 0)
        SET_VALUE(LSWF(7), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_02_sw"), -545, -50, -120, PTR(hosi_02_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_03_sw"), -460, -50, -120, PTR(hosi_03_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_04_sw"), -376, -50, -120, PTR(hosi_04_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_05_sw"), -289, -50, -120, PTR(hosi_05_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_06_sw"), -205, -50, -120, PTR(hosi_06_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_07_sw"), -121, -50, -120, PTR(hosi_07_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_08_sw"), -37, -50, -120, PTR(hosi_08_sw_evt), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_02b"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_03b"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_04b"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_05b"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_06b"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_07b"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hosi_08b"), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(las_20_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST3"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS5"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_01a"), 2)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_08a"), 2)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_09a"), 2)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_12a"), 2)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_19a"), 2)
    SPAWN_EVENT(PTR(haguruma_evt))
    CALL(evt_map_playanim, STRING("kusari"), 1, 0)
    CALL(evt_hit_bind_mapobj, STRING("A_move_dai"), STRING("S_move_dai"))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_move_dai"), 1)
    CALL(evt_hitobj_onoff, STRING("A_move_dai"), 0, 0)
    CALL(evt_mobj_switch_red, 0, STRING("dai_switch"), -250, -290, 100, PTR(dai_evt), 0)
    SPAWN_EVENT(PTR(hosi_init))
    CALL(evt_mobj_badgeblk, STRING("mobj_item00"), 295, -440, -15, 136, 0, GSWF(4388), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_item01"), 640, -320, -135, 151, 0, GSWF(4389), 0)
    RETURN
EVT_END()

USER_FUNC(get_hosi_name) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], hosi_name[idx * 2]);
    evtSetValue(event, args[2], hosi_name[idx * 2 + 1]);
    return EVT_RETURN_DONE;
}
