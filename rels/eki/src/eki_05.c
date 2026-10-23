#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "eki.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_item_delete);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_important_item);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_item_set_bound_rate);
USER_FUNC(evt_item_set_gravity);
USER_FUNC(evt_item_set_jump_power);
USER_FUNC(evt_item_set_move_dir_speed);
USER_FUNC(evt_item_status_on);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(lect_juyoitem_rel_set);
#ifdef VERSION_G8ME01
USER_FUNC(evt_mapobj_flag_onoff);
#endif

__declspec(section ".data") u64 fd_eki_05_negone_one_374;
__declspec(section ".data") s32 fd_eki_05_neg_one_382[1];
__declspec(section ".data") s32 fd_eki_05___local_PI_383[1];
__declspec(section ".data") s32 fd_eki_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_eki_05_one_negone_373;
__declspec(section ".data") s32 fd_eki_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_eki_05_one_381[1];
__declspec(section ".data") u64 fd_eki_05_negone_one_360;
__declspec(section ".data") s32 fd_eki_05_neg_one_365[1];
__declspec(section ".data") s32 fd_eki_05___local_PI_366[1];
__declspec(section ".data") s32 fd_eki_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_eki_05_one_negone_359;
__declspec(section ".data") s32 fd_eki_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_eki_05_one_364[1];
static __declspec(section ".data") s32 n_close[12];
static __declspec(section ".data") s32 n_open[12];
static __declspec(section ".data") s32 w_close[12];
static __declspec(section ".data") s32 w_open[12];
static s32 bero_data[60];
s32 grass_open_1[14];
s32 grass_open_2[23];
s32 evt_boots[42];
__declspec(section ".data") s32 evt_elvkey[5];
static s32 evt_head[38];
#ifdef VERSION_G8ME01
s32 eki_05_init_evt[112];
#else
s32 eki_05_init_evt[106];
#endif

__declspec(section ".data") u64 fd_eki_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_eki_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_05_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(n_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door_2"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"n_bero", 65539, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"eki_04", (s32)"s_bero", 327685, (s32)n_close, (s32)n_open, (s32)"w_bero_1",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"eki_06", (s32)"e_bero_2", 65537, 0, 0, (s32)"w_bero_2", 65539,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"eki_06", (s32)"e_bero_1", 327685, (s32)w_close, (s32)w_open, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(grass_open_1)
    IF_INT_EQUAL(GF(0), 1)
        CALL(evt_map_playanim, STRING("anm_nata"), 0, 0)
        SET_VALUE(GF(0), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(grass_open_2)
    IF_INT_EQUAL(GF(0), 0)
        CALL(evt_map_playanim, STRING("anm_tana"), 0, 0)
        SET_VALUE(GF(0), 1)
        ELSE
        CALL(evt_map_playanim, STRING("anm_nata"), 0, 0)
        SET_VALUE(GF(0), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_boots)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("tbox"), LW(0), LW(1), LW(2))
    CALL(lect_juyoitem_rel_set, PTR(all_juyoitem_lecture_rel))
    CALL(evt_item_entry, STRING("boots"), 8, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("tbox"))
    CALL(evt_item_get_important_item, STRING("boots"))
    CALL(evt_item_get_item, STRING("boots"))
    CALL(evt_item_get_item_end_wait, STRING("boots"))
    SET_VALUE(GSW(0), 319)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_elvkey)
    SET_VALUE(GSW(0), 320)
    RETURN
EVT_END()

static EVT_BEGIN(evt_head)
    CALL(evt_item_delete, STRING("elvkey"))
    CALL(evt_item_entry, STRING("elvkey"), 26, -135, 166, -70, 4, -1, PTR(evt_elvkey))
    CALL(evt_item_set_move_dir_speed, STRING("elvkey"), FLOAT(135.0f), FLOAT(90.0f))
    CALL(evt_item_set_gravity, STRING("elvkey"), FLOAT(1.0f))
    CALL(evt_item_set_bound_rate, STRING("elvkey"), FLOAT(0.5996094f))
    CALL(evt_item_set_jump_power, STRING("elvkey"), FLOAT(500.0f))
    CALL(evt_item_status_on, STRING("elvkey"), 16)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(eki_05_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG6_EKI2"))
    SET_VALUE(GF(0), 0)
    CALL(evt_run_case_evt, 9, 1, STRING("a_garasu_1"), 0, PTR(grass_open_1), 0)
    CALL(evt_run_case_evt, 9, 1, STRING("a_garasu_2"), 0, PTR(grass_open_2), 0)
    IF_INT_LESS(GSW(0), 319)
        CALL(evt_mobj_itembox, STRING("tbox"), -85, 295, 0, 1, 0, PTR(evt_boots), GSWF(3728))
    END_IF
    IF_INT_LESS(GSW(0), 320)
        CALL(evt_item_entry, STRING("elvkey"), 26, -135, 136, -70, 17, -1, PTR(evt_elvkey))
        CALL(evt_run_case_evt, 16, 1, STRING("a_t_2"), 0, PTR(evt_head), 0)
    END_IF
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_map_playanim, STRING("anm_mizu"), 0, 0)
            CALL(evt_map_checkanim, STRING("anm_mizu"), LW(0), LW(1))
            WAIT_MS(700)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_AMB_WATERDROP1"), -129, 295, -17, 0)
            WAIT_MS(100)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_AMB_WATERDROP1"), 179, 295, -17, 0)
            WAIT_MS(100)
        END_LOOP
    END_INLINE_EVENT
#ifdef VERSION_G8ME01
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S"), 2)
#endif
    RETURN
EVT_END()

