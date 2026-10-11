#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_img_alloc_capture);
USER_FUNC(evt_img_clear_virtual_point);
USER_FUNC(evt_img_entry);
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
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_moo_07_negone_one_374;
__declspec(section ".data") s32 fd_moo_07_neg_one_382[1];
__declspec(section ".data") s32 fd_moo_07___local_PI_383[1];
__declspec(section ".data") s32 fd_moo_07___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_moo_07_one_negone_373;
__declspec(section ".data") s32 fd_moo_07___local_PIO2_384[1];
__declspec(section ".data") s32 fd_moo_07_one_381[1];
__declspec(section ".data") u64 fd_moo_07_negone_one_360;
__declspec(section ".data") s32 fd_moo_07_neg_one_365[1];
__declspec(section ".data") s32 fd_moo_07___local_PI_366[1];
__declspec(section ".data") s32 fd_moo_07___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_moo_07_one_negone_359;
__declspec(section ".data") s32 fd_moo_07___local_PIO2_367[1];
__declspec(section ".data") s32 fd_moo_07_one_364[1];
static s32 bero_entry_data[45];
static s32 rock_main[79];
static s32 rock_evt0[21];
s32 moo_07_init_evt[69];

__declspec(section ".data") u64 fd_moo_07_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_moo_07_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_moo_07___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_moo_07___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_moo_07_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_moo_07___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_moo_07_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_moo_07_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_moo_07_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_moo_07___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_moo_07___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_moo_07_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_moo_07___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_moo_07_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"moo_06", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"moo_00", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

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

static EVT_BEGIN(rock_evt0)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(LW(10), STRING("S_iwa_07"))
    SET_VALUE(LW(11), STRING("A_iwa_07"))
    CALL_CHILD(PTR(rock_main))
    SET_VALUE(GSWF(4034), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(moo_07_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_MON1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_MOO1"))
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_03"), 1, 0)
    CALL(evt_paper_entry, STRING("OFF_d_bom_ver2"))
    IF_INT_EQUAL(GSWF(4034), 0)
        CALL(evt_run_case_evt, 15, 1, STRING("A_iwa_07"), 0, PTR(rock_evt0), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_iwa_07"), 1)
        CALL(evt_hitobj_onoff, STRING("A_iwa_07"), 1, 0)
    END_IF
    CALL(evt_item_entry, STRING("item_01"), 143, 5, 0, 400, 16, GSWF(4039), 0)
    RETURN
EVT_END()

