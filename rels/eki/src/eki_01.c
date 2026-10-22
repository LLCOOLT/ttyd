#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mobj_switch_blue);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_win_item_select);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_eki_01_negone_one_374;
__declspec(section ".data") s32 fd_eki_01_neg_one_382[1];
__declspec(section ".data") s32 fd_eki_01___local_PI_383[1];
__declspec(section ".data") s32 fd_eki_01___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_eki_01_one_negone_373;
__declspec(section ".data") s32 fd_eki_01___local_PIO2_384[1];
__declspec(section ".data") s32 fd_eki_01_one_381[1];
__declspec(section ".data") u64 fd_eki_01_negone_one_360;
__declspec(section ".data") s32 fd_eki_01_neg_one_365[1];
__declspec(section ".data") s32 fd_eki_01___local_PI_366[1];
__declspec(section ".data") s32 fd_eki_01___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_eki_01_one_negone_359;
__declspec(section ".data") s32 fd_eki_01___local_PIO2_367[1];
__declspec(section ".data") s32 fd_eki_01_one_364[1];
static __declspec(section ".data") s32 e_close[12];
static __declspec(section ".data") s32 e_open[12];
static __declspec(section ".data") s32 w_close[12];
static __declspec(section ".data") s32 w_open[12];
static __declspec(section ".data") s32 n_close[12];
static __declspec(section ".data") s32 n_open[12];
static s32 bero_data[60];
static s32 evt_origami[129];
static __declspec(section ".data") s32 key_tbl[2];
static s32 evt_chk[23];
static __declspec(section ".data") s32 evt_lock[10];
__declspec(section ".data") s32 evt_kami_1[5];
__declspec(section ".data") s32 evt_kami_2[5];
__declspec(section ".data") s32 evt_kami_3[5];
__declspec(section ".data") s32 evt_kami_4[5];
__declspec(section ".data") s32 evt_kami_5[5];
__declspec(section ".data") s32 evt_kami_6[5];
s32 eki_01_init_evt[223];

__declspec(section ".data") u64 fd_eki_01_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_01_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_01___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_01___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_01_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_01___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_01_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_eki_01_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_01_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_01___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_01___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_01_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_01___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_01_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(e_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_3"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_3"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"e_bero", 65539, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"eki_03", (s32)"w_bero_1", 327685, (s32)e_close, (s32)e_open, (s32)"w_dero",
    65539, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"eki_00", (s32)"e_bero", 327685, (s32)w_close, (s32)w_open, (s32)"n_bero", 65539,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"eki_02", (s32)"s_bero", 327685, (s32)n_close, (s32)n_open, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(evt_origami)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 516, 126, 408, 171, 90, -55, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, STRING("dann"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN1"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(1666)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN2"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(266)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN2"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(366)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN2"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(333)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN2"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(333)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN2"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(333)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_PERA_KAI_DOWN2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("dann"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("n_origami"), 1)
    CALL(evt_hitobj_onoff, STRING("a_oritatami"), 1, 1)
    CALL(evt_map_playanim, STRING("anm_kaidan"), 0, 0)
    CALL(evt_map_checkanim, STRING("anm_kaidan"), LW(0), LW(1))
    WAIT_MS(LW(1))
    WAIT_MS(1000)
    SET_VALUE(GSW(0), 313)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static __declspec(section ".data") s32 key_tbl[] = {
    25, -1,
};

static EVT_BEGIN(evt_chk)
    CALL(evt_pouch_check_item, 25, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
        IF_INT_EQUAL(LW(0), -1)
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_lock)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(PTR(bero_case_switch_on))
    SET_VALUE(GSW(0), 315)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_kami_1)
    SET_VALUE(GSWF(3748), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_kami_2)
    SET_VALUE(GSWF(3749), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_kami_3)
    SET_VALUE(GSWF(3750), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_kami_4)
    SET_VALUE(GSWF(3751), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_kami_5)
    SET_VALUE(GSWF(3752), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_kami_6)
    SET_VALUE(GSWF(3753), 1)
    RETURN
EVT_END()

EVT_BEGIN(eki_01_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG6_EKI2_2"))
    IF_INT_LESS(GSW(0), 313)
        CALL(evt_mobj_switch_blue, 0, STRING("origami_sw"), 90, 10, -60, PTR(evt_origami), GSWF(3727))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("dann"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("n_origami"), 1)
        CALL(evt_hitobj_onoff, STRING("a_oritatami"), 1, 0)
        ELSE
        CALL(evt_map_playanim, STRING("anm_kaidan"), 2, 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("dann"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("n_origami"), 1)
        CALL(evt_hitobj_onoff, STRING("a_oritatami"), 1, 1)
    END_IF
    IF_INT_LESS(GSW(0), 315)
        CALL(evt_mobj_lock, STRING("lock"), 25, 394, 10, 0, -80, PTR(evt_chk), PTR(evt_lock), GSWF(3726))
        SET_VALUE(LW(0), 0)
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    CALL(evt_cloud_init)
    IF_INT_EQUAL(GSWF(3748), 0)
        CALL(evt_cloud_ent, 0, STRING("kami_1"), STRING("a_kami_1"), PTR(evt_kami_1))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_1"), 1)
        CALL(evt_hitobj_onoff, STRING("a_kami_1"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(3749), 0)
        CALL(evt_cloud_ent, 0, STRING("kami_2"), STRING("a_kami_2"), PTR(evt_kami_2))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_2"), 1)
        CALL(evt_hitobj_onoff, STRING("a_kami_2"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(3750), 0)
        CALL(evt_cloud_ent, 0, STRING("kami_3"), STRING("a_kami_3"), PTR(evt_kami_3))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_3"), 1)
        CALL(evt_hitobj_onoff, STRING("a_kami_3"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(3751), 0)
        CALL(evt_cloud_ent, 0, STRING("kami_4"), STRING("a_kami_4"), PTR(evt_kami_4))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_4"), 1)
        CALL(evt_hitobj_onoff, STRING("a_kami_4"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(3752), 0)
        CALL(evt_cloud_ent, 0, STRING("kami_5"), STRING("a_kami_5"), PTR(evt_kami_5))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_5"), 1)
        CALL(evt_hitobj_onoff, STRING("a_kami_5"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(3753), 0)
        CALL(evt_cloud_ent, 0, STRING("kami_6"), STRING("a_kami_6\0\0\0"), PTR(evt_kami_6))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_6"), 1)
        CALL(evt_hitobj_onoff, STRING("a_kami_6\0\0\0"), 1, 0)
    END_IF
    RETURN
EVT_END()

