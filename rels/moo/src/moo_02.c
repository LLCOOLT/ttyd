#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "moo.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hit_get_position);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_img_alloc_capture);
USER_FUNC(evt_img_clear_virtual_point);
USER_FUNC(evt_img_entry);
USER_FUNC(evt_img_free_capture);
USER_FUNC(evt_img_onoff);
USER_FUNC(evt_img_release);
USER_FUNC(evt_img_set_paper);
USER_FUNC(evt_img_set_paper_anim);
USER_FUNC(evt_img_set_shadow);
USER_FUNC(evt_img_wait_animend);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_set_offscreen);
USER_FUNC(evt_mario_bgmode_on);
USER_FUNC(evt_mario_cam_y_off);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
#ifdef VERSION_G8ME01
USER_FUNC(evt_offscreen_get_boundingbox2);
#endif

__declspec(section ".data") u64 fd_moo_02_negone_one_374;
__declspec(section ".data") s32 fd_moo_02_neg_one_382[1];
__declspec(section ".data") s32 fd_moo_02___local_PI_383[1];
__declspec(section ".data") s32 fd_moo_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_moo_02_one_negone_373;
__declspec(section ".data") s32 fd_moo_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_moo_02_one_381[1];
__declspec(section ".data") u64 fd_moo_02_negone_one_360;
__declspec(section ".data") s32 fd_moo_02_neg_one_365[1];
__declspec(section ".data") s32 fd_moo_02___local_PI_366[1];
__declspec(section ".data") s32 fd_moo_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_moo_02_one_negone_359;
__declspec(section ".data") s32 fd_moo_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_moo_02_one_364[1];
s32 n_bero_in[25];
__declspec(section ".data") s32 n_bero_out[12];
static s32 bero_entry_data[90];
#ifdef VERSION_G8ME01
static s32 dokan_evt[122];
#else
static s32 dokan_evt[102];
#endif
#ifdef VERSION_G8ME01
#else
static s32 rock_main[79];
#endif
#ifdef VERSION_G8ME01
static s32 rock_evt0[15];
#else
static s32 rock_evt0[21];
#endif
#ifdef VERSION_G8ME01
static s32 rock_evt1[15];
#else
static s32 rock_evt1[21];
#endif
s32 moo_02_init_evt[132];

__declspec(section ".data") u64 fd_moo_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_moo_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_moo_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_moo_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_moo_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_moo_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_moo_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_moo_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_moo_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_moo_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_moo_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_moo_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_moo_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_moo_02_one_364[] = {
    1065353216,
};

EVT_BEGIN(n_bero_in)
    CALL(evt_mario_bgmode_on)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mario_cam_y_off)
    CALL(evt_hit_get_position, STRING("n_bero"), LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL_CHILD(PTR(bero_case_entry))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_bero_out)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_mapchange, STRING("aji_19"), STRING("w_bero"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"moo_05", (s32)"e_bero", 65537, 0, 0, (s32)"dokan_1",
    131072, 9, 100000, 0, 0, -1, 0, 6,
    0, 0, (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_2", 268566528,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan_1", 65537, 0, 0, (s32)"n_bero", 268632064, 20000,
    100000, 0, 0, -1, (s32)n_bero_in, 5, (s32)n_bero_out, (s32)"aji_00",
    (s32)"w_bero", 65537, 0, 0, (s32)"e_bero", 0, 20000, 100000,
    0, 0, -1, 0, -1, 0, (s32)"moo_06", (s32)"w_bero",
    65537, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

static EVT_BEGIN(dokan_evt)
#ifdef VERSION_G8ME01
    SET_VALUE(GSW(0), 359)
#else
    CALL(evt_mario_key_onoff, 0)
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mapobj_get_position, STRING("S_iwa_04"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_WALL_BREAK1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 0, STRING("S_iwa_04"), STRING("offscreen"))
#ifdef VERSION_G8ME01
    CALL(evt_offscreen_get_boundingbox2, STRING("offscreen"), LW(0), LW(1), LW(2), LW(3))
    IF_INT_GREATER(LW(2), 0)
        IF_INT_GREATER(LW(3), 0)
#endif
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_bom_ver2"))
#ifdef VERSION_G8ME01
            CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("offscreen"), 1, 0, 0, 0, 0)
#else
    CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("offscreen"), 0, 0, 0, 0, 0)
#endif
    CALL(evt_img_clear_virtual_point, STRING("img"))
    CALL(evt_img_set_shadow, STRING("img"), 2)
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("S_iwa_04"), 1)
#ifdef VERSION_G8ME01
            CALL(evt_hitobj_onoff, STRING("A_iwa_04"), 1, 0)
#endif
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_free_capture, STRING("img"), 0)
    CALL(evt_img_set_shadow, STRING("img"), 0)
    CALL(evt_img_onoff, STRING("img"), 0)
    CALL(evt_img_release, STRING("img"))
#ifdef VERSION_G8ME01
        END_IF
    END_IF
#endif
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_clear_offscreen, 0, STRING("S_iwa_04"))
#ifdef VERSION_G8ME01
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("S_iwa_04"), 1)
#else
    SET_VALUE(GSW(0), 359)
#endif
    CALL(evt_hitobj_onoff, STRING("A_iwa_04"), 1, 0)
#ifndef VERSION_G8ME01
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

#ifndef VERSION_G8ME01
static EVT_BEGIN(rock_main)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mapobj_get_position, LW(10), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_WALL_BREAK1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 0, LW(10), STRING("offscreen"))
    CALL(evt_mapobj_flag_onoff, 0, 1, LW(10), 1)
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_bom_ver2"))
    CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("offscreen"), 0, 0, 0, 0, 0)
    CALL(evt_img_clear_virtual_point, STRING("img"))
    CALL(evt_img_set_shadow, STRING("img"), 2)
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_release, STRING("img"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_clear_offscreen, 0, LW(10))
    CALL(evt_hitobj_onoff, LW(11), 1, 0)
    RETURN
EVT_END()
#endif

static EVT_BEGIN(rock_evt0)
#ifdef VERSION_G8ME01
    SET_VALUE(GSWF(4029), 1)
#else
    CALL(evt_mario_key_onoff, 0)
#endif
    SET_VALUE(LW(10), STRING("S_iwa_01"))
    SET_VALUE(LW(11), STRING("A_iwa_01"))
    CALL_CHILD(PTR(rock_main))
#ifndef VERSION_G8ME01
    SET_VALUE(GSWF(4029), 1)
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(rock_evt1)
#ifdef VERSION_G8ME01
    SET_VALUE(GSWF(4030), 1)
#else
    CALL(evt_mario_key_onoff, 0)
#endif
    SET_VALUE(LW(10), STRING("S_iwa_07"))
    SET_VALUE(LW(11), STRING("A_iwa_07"))
    CALL_CHILD(PTR(rock_main))
#ifndef VERSION_G8ME01
    SET_VALUE(GSWF(4030), 1)
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(moo_02_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_MON1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_MOO2"))
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_03"), 1, 0)
    CALL(evt_map_playanim, STRING("light"), 1, 0)
    CALL(evt_item_entry, STRING("item00"), 125, -55, 0, -135, 16, GSWF(5664), 0)
    CALL(evt_paper_entry, STRING("OFF_d_bom_ver2"))
    IF_INT_LESS(GSW(0), 359)
        CALL(evt_run_case_evt, 15, 1, STRING("A_iwa_04"), 0, PTR(dokan_evt), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_iwa_04"), 1)
        CALL(evt_hitobj_onoff, STRING("A_iwa_04"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(4029), 0)
        CALL(evt_run_case_evt, 15, 1, STRING("A_iwa_01"), 0, PTR(rock_evt0), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_iwa_01"), 1)
        CALL(evt_hitobj_onoff, STRING("A_iwa_01"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(4030), 0)
        CALL(evt_run_case_evt, 15, 1, STRING("A_iwa_07"), 0, PTR(rock_evt1), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_iwa_07"), 1)
        CALL(evt_hitobj_onoff, STRING("A_iwa_07"), 1, 0)
    END_IF
    CALL(evt_item_entry, STRING("item_01"), 142, 330, 0, 403, 16, GSWF(4037), 0)
    RETURN
EVT_END()

