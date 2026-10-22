#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_gazigazi_entry[];
extern s32 hikari_evt[];

__declspec(section ".data") u64 fd_las_23_negone_one_374;
__declspec(section ".data") s32 fd_las_23_neg_one_382[1];
__declspec(section ".data") s32 fd_las_23___local_PI_383[1];
__declspec(section ".data") s32 fd_las_23___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_23_one_negone_373;
__declspec(section ".data") s32 fd_las_23___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_23_one_381[1];
__declspec(section ".data") u64 fd_las_23_negone_one_360;
__declspec(section ".data") s32 fd_las_23_neg_one_365[1];
__declspec(section ".data") s32 fd_las_23___local_PI_366[1];
__declspec(section ".data") s32 fd_las_23___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_23_one_negone_359;
__declspec(section ".data") s32 fd_las_23___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_23_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e1_door_close[22];
static s32 e1_door_open[22];
static s32 e2_door_close[22];
static s32 e2_door_open[22];
static s32 bero_entry_data[90];
static s32 w_bero_mapchg[15];
static s32 dmgRetPoint[24];
s32 las_23_init_evt[93];

__declspec(section ".data") u64 fd_las_23_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_23_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_23___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_23___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_23_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_23___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_23_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_23_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_23_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_23___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_23___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_23_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_23___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_23_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_21", (s32)"e_bero_1", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero_1",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_25", (s32)"w_bero", 327685, (s32)e1_door_close, (s32)e1_door_open, (s32)"e_bero_2", 65542,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"las_25", (s32)"w_bero", 327685, (s32)e2_door_close, (s32)e2_door_open, (s32)"n_bero_1", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"las_22",
    (s32)"s_bero", 65537, 0, 0, (s32)"n_bero_2", 0, 20000, 100000,
    0, 0, -1, 0, -1, 0, (s32)"las_24", (s32)"s_bero_1",
    65537, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

static s32 w_bero_mapchg[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_21", (s32)"e_bero_2", 327685, (s32)w_door_close, (s32)w_door_open,
};

static s32 dmgRetPoint[] = {
    (s32)"A_oti_01", 0, -998637568, 0, (s32)"A_oti_02", 0, -998637568, 0,
    (s32)"A_oti_03", 0, -998637568, 0, (s32)"A_oti_04", 0, -998637568, 0,
    (s32)"A_oti_05", 0, -998637568, 0, 0, 0, 0, 0,
};

EVT_BEGIN(las_23_init_evt)
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST3"))
    END_IF
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_under"), 1)
        CALL(evt_hitobj_onoff, STRING("A_under"), 1, 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_paipu"), 1)
        CALL(evt_hitobj_onoff, STRING("jav_01"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("jav_02"), 1, 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_yuka"), 1)
        CALL(evt_hitobj_onoff, STRING("A_be\0\0\0"), 1, 0)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("w_bero"), PTR(w_bero_mapchg))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
        SPAWN_EVENT(PTR(hikari_evt))
    END_IF
    CALL(evt_hit_damage_return_set, PTR(dmgRetPoint))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    RETURN
EVT_END()

