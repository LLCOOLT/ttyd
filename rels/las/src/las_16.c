#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_img_alloc_capture);
USER_FUNC(evt_img_clear_virtual_point);
USER_FUNC(evt_img_entry);
USER_FUNC(evt_img_onoff);
USER_FUNC(evt_img_release);
USER_FUNC(evt_img_set_paper);
USER_FUNC(evt_img_set_paper_anim);
USER_FUNC(evt_img_wait_animend);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_set_offscreen);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_offscreen_get_boundingbox2);
USER_FUNC(evt_paper_delete);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_las_16_negone_one_374;
__declspec(section ".data") s32 fd_las_16_neg_one_382[1];
__declspec(section ".data") s32 fd_las_16___local_PI_383[1];
__declspec(section ".data") s32 fd_las_16___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_16_one_negone_373;
__declspec(section ".data") s32 fd_las_16___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_16_one_381[1];
__declspec(section ".data") u64 fd_las_16_negone_one_360;
__declspec(section ".data") s32 fd_las_16_neg_one_365[1];
__declspec(section ".data") s32 fd_las_16___local_PI_366[1];
__declspec(section ".data") s32 fd_las_16___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_16_one_negone_359;
__declspec(section ".data") s32 fd_las_16___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_16_one_364[1];
static __declspec(section ".data") s32 w_door_close[12];
static __declspec(section ".data") s32 w_door_open[12];
static s32 bero_entry_data[30];
static s32 box_evt[30];
static s32 bomb_wall_evt[206];
static s32 hint_plate[14];
s32 las_16_init_evt[84];

__declspec(section ".data") u64 fd_las_16_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_16_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_16___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_16___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_16_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_16___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_16_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_16_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_16_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_16___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_16___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_16_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_16___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_16_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 65537, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_10", (s32)"ne_bero_2", 327685, (s32)w_door_close, (s32)w_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), 43, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(bomb_wall_evt)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mapobj_get_position, STRING("S_ana_ana"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_WALL_BREAK1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_paper_entry, STRING("OFF_d_bom_ver2"))
    CALL(evt_offscreen_entry, STRING("ofs"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_onoff, STRING("img"), 0)
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_bom_ver2"))
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_ana_ana"), STRING("ofs"))
    CALL(evt_offscreen_get_boundingbox2, STRING("ofs"), LW(0), LW(1), LW(2), LW(3))
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(LW(2), 0)
        IF_INT_EQUAL(LW(3), 0)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("ofs"), 1, LW(0), LW(1), LW(2), LW(3))
        WAIT_FRAMES(1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_ana"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_before"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ana_after"), 1)
        CALL(evt_img_clear_virtual_point, STRING("img"))
        CALL(evt_img_onoff, STRING("img"), 1)
        CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
        CALL(evt_img_wait_animend, STRING("img"))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_ana"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_before"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ana_after"), 1)
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_IF
    CALL(evt_hitobj_onoff, STRING("A_ana_ana"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_ana_before"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_ana_after"), 1, 1)
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_ana_ana"))
    CALL(evt_img_release, STRING("img"))
    CALL(evt_paper_delete, STRING("OFF_d_bom_ver2"))
    CALL(evt_offscreen_delete, STRING("ofs"))
    SET_VALUE(GSWF(4348), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_41"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(las_16_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_EQUAL(GSWF(4348), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_after"), 1)
        CALL(evt_hitobj_onoff, STRING("A_ana_after"), 1, 0)
        CALL(evt_run_case_evt, 15, 1, STRING("A_ana_ana"), 0, PTR(bomb_wall_evt), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_ana"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_ana_before"), 1)
        CALL(evt_hitobj_onoff, STRING("A_ana_ana"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_ana_before"), 1, 0)
    END_IF
    CALL(evt_mobj_itembox, STRING("box"), 150, 0, 0, 0, 0, PTR(box_evt), GSWF(4367))
    CALL(evt_run_case_evt, 9, 1, STRING("A_pure"), 0, PTR(hint_plate), 0)
    RETURN
EVT_END()

