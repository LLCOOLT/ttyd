#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_npc_check);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_glide_position);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_ry_lr);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_puni_count);
USER_FUNC(evt_puni_flag_onoff);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_mode);
USER_FUNC(evt_puni_set_position);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_target_flag_onoff);
USER_FUNC(evt_target_set_position);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);
extern s32 bero_case_switch_off[];
extern s32 evt_bero_info_run[];
extern s32 evt_mri_door_close[];
extern s32 evt_mri_door_open[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 mri_countdown[];
extern s32 mri_guide_goryu[];
extern s32 mri_puni_init[];
extern s32 mri_puni_save[];
extern s32 mri_puni_walk_se[];
extern s32 puni_disp_info[];
extern s32 puni_piders_check[];

__declspec(section ".data") u64 fd_mri_06_negone_one_374;
__declspec(section ".data") s32 fd_mri_06_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_06___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_06_one_negone_373;
__declspec(section ".data") s32 fd_mri_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_06_one_381[1];
__declspec(section ".data") u64 fd_mri_06_negone_one_360;
__declspec(section ".data") s32 fd_mri_06_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_06___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_06_one_negone_359;
__declspec(section ".data") s32 fd_mri_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_06_one_364[1];
static s32 rival_init[21];
static s32 rival_talk[20];
s32 puni_6_init[21];
s32 puni_6_talk[20];
s32 puni_7_init[21];
s32 puni_7_talk[20];
s32 puni_8_init[17];
s32 puni_8_talk[20];
s32 puni_9_init[21];
s32 puni_9_talk[20];
s32 puni_10_init[17];
s32 puni_10_regl[19];
s32 puni_10_talk[20];
s32 puni_11_init[17];
s32 puni_11_regl[19];
s32 puni_11_talk[20];
static s32 npcEnt[184];
static __declspec(section ".data") s32 bero_s_doa_close[10];
static __declspec(section ".data") s32 bero_s_doa_open[10];
static s32 bero_entry_data[120];
static s32 door_switch_init[17];
s32 ueki_evt_02[20];
static s32 ueki_access_data[28];
s32 paiders_a[84];
s32 paiders_b[86];
static s32 puni_lose[82];
s32 apper_toge[252];
static __declspec(section ".data") s32 cloud_wind_event[5];
s32 mri_06_init_evt[207];

__declspec(section ".data") u64 fd_mri_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_06_one_364[] = {
    1065353216,
};

static EVT_BEGIN(rival_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), 390, 0, 15)
            CALL(evt_npc_set_ry_lr, STRING("me"), 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(rival_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_021"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_021_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_6_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), 390, 0, -35)
            CALL(evt_npc_set_ry_lr, STRING("me"), 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_6_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_022"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_022_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_7_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), -350, -310, 100)
            CALL(evt_npc_set_ry, STRING("me"), 90)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_7_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_023"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_023_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_8_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), -380, 0, 10)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_8_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_024"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_024_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_9_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), 330, -310, 45)
            CALL(evt_npc_set_ry_lr, STRING("me"), 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_9_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_025"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_025_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_10_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), -120, -310, 50)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_10_regl)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(puni_10_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_026"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_026_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_11_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), -190, -310, 125)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_11_regl)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(puni_11_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_027"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_027_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ライバル"*/"\x83\x89\x83\x43\x83\x6F\x83\x8B", 525824, 0, (s32)rival_init, 0, (s32)rival_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"プニ族６"*/"\x83\x76\x83\x6A\x91\xB0\x82\x55",
    525824, 0, (s32)puni_6_init, 0, (s32)puni_6_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"プニ族７"*/"\x83\x76\x83\x6A\x91\xB0\x82\x56", 525824,
    0, (s32)puni_7_init, 0, (s32)puni_7_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"プニ族８"*/"\x83\x76\x83\x6A\x91\xB0\x82\x57", 525824, 0,
    (s32)puni_8_init, 0, (s32)puni_8_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"プニ族９"*/"\x83\x76\x83\x6A\x91\xB0\x82\x58", 525824, 0, (s32)puni_9_init,
    0, (s32)puni_9_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"プニ族１０"*/"\x83\x76\x83\x6A\x91\xB0\x82\x50\x82\x4F", 525824, 0, (s32)puni_10_init, (s32)puni_10_regl,
    (s32)puni_10_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"プニ族１１"*/"\x83\x76\x83\x6A\x91\xB0\x82\x50\x82\x50", 525824, 0, (s32)puni_11_init, (s32)puni_11_regl, (s32)puni_11_talk,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

static __declspec(section ".data") EVT_BEGIN(bero_s_doa_close)
    SET_VALUE(LW(9), 1)
    SET_VALUE(LW(10), STRING("S_doa"))
    SPAWN_EVENT(PTR(evt_mri_door_close))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(bero_s_doa_open)
    SET_VALUE(LW(9), 1)
    SET_VALUE(LW(10), STRING("S_doa"))
    SPAWN_EVENT(PTR(evt_mri_door_open))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"e_bero", 65536, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"mri_15", (s32)"w_bero", 262148, (s32)bero_s_doa_close, (s32)bero_s_doa_open, (s32)"w_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"mri_07", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero02", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"mri_08", (s32)"w_bero", 65537, 0, 0, (s32)"w_bero02", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"mri_11",
    (s32)"e_bero", 65537, 0, 0, (s32)"dokan1", 131072, 2, 100000,
    0, 0, -1, 0, 10, 0, (s32)"mri_19", (s32)"dokan2",
    65537, 0, 0, (s32)"dokan2", 131072, 9, 100000, 0,
    0, -1, 0, 6, 0, 0, (s32)"dokan3", 65537,
    0, 0, (s32)"dokan3", 131072, 2, 100000, 0, 0,
    -1, 0, 10, 0, 0, (s32)"dokan2", 65537, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(door_switch_init)
    IF_INT_EQUAL(GSWF(2865), 0)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        ELSE
        CALL(evt_map_playanim, STRING("light"), 2, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(ueki_evt_02)
    CALL(evt_item_delete_check, STRING("item_ueki02"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_ueki02"), 125, -95, -310, -52, 0, GSWF(5614), 0)
    END_IF
    RETURN
EVT_END()

static s32 ueki_access_data[] = {
    1, (s32)"A_ueki01", (s32)"S_ueki01", 0, 1, (s32)"A_ueki02", (s32)"S_ueki02", (s32)ueki_evt_02,
    1, (s32)"A_ueki03", (s32)"S_ueki03", 0, 1, (s32)"A_ueki04", (s32)"S_ueki04", 0,
    1, (s32)"A_ueki05", (s32)"S_ueki05", 0, 1, (s32)"A_ueki06", (s32)"S_ueki06", 0,
    4, 0, 0, 0,
};

EVT_BEGIN(paiders_a)
    SET_VALUE(LW(0), STRING("パイダースA"))
    SET_VALUE(LW(1), 75)
    SET_VALUE(LW(2), 130)
    SET_VALUE(LW(3), 40)
    SET_VALUE(LW(4), 0)
    CALL(evt_npc_set_position, LW(0), LW(1), LW(2), LW(3))
    LOOP(0)
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_S_1"))
        WAIT_MS(5000)
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_W_1"))
        CALL(evt_npc_glide_position, LW(0), LW(1), LW(4), LW(3), 0, FLOAT(120.0f), 0, 11, 0)
        CALL(evt_target_flag_onoff, 1, 0, 5)
        CALL(evt_target_set_position, 1, LW(1), LW(4), LW(3))
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_S_1"))
        WAIT_MS(2000)
        CALL(evt_target_flag_onoff, 1, 1, 1)
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_W_2"))
        CALL(evt_npc_glide_position, LW(0), LW(1), LW(2), LW(3), 0, FLOAT(120.0f), 0, 11, 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(paiders_b)
    SET_VALUE(LW(0), STRING("パイダースB"))
    SET_VALUE(LW(1), -235)
    SET_VALUE(LW(2), 130)
    SET_VALUE(LW(3), 60)
    SET_VALUE(LW(4), 0)
    CALL(evt_npc_set_position, LW(0), LW(1), LW(2), LW(3))
    WAIT_MS(2000)
    LOOP(0)
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_S_1"))
        WAIT_MS(5000)
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_W_1"))
        CALL(evt_npc_glide_position, LW(0), LW(1), LW(4), LW(3), 0, FLOAT(120.0f), 0, 11, 0)
        CALL(evt_target_flag_onoff, 1, 0, 5)
        CALL(evt_target_set_position, 1, LW(1), LW(4), LW(3))
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_S_1"))
        WAIT_MS(3000)
        CALL(evt_target_flag_onoff, 1, 1, 1)
        CALL(evt_npc_set_anim, LW(0), STRING("PAI_W_2"))
        CALL(evt_npc_glide_position, LW(0), LW(1), LW(2), LW(3), 0, FLOAT(120.0f), 0, 11, 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(puni_lose)
    SET_VALUE(LW(0), GSWF(2848))
    ADD(LW(0), GSWF(2856))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_bero_exec_wait, 65536)
        CALL(evt_puni_flag_onoff, 1, 0, 131072)
        CALL(evt_npc_flag_onoff, 1, STRING("ガイドsp"), 512)
        CALL(evt_puni_count, 0, LW(0))
        IF_INT_EQUAL(GSWF(2856), 0)
            CALL(evt_msg_print, 0, STRING("stg2_mri_e17_03"), 0, STRING("ガイドsp"))
            ELSE
            IF_INT_LESS_OR_EQUAL(LW(0), 11)
                CALL(evt_msg_print, 0, STRING("stg2_mri_e17_03_01"), 0, STRING("ガイドsp"))
                ELSE
                CALL(evt_msg_print, 0, STRING("stg2_mri_e17_03"), 0, STRING("ガイドsp"))
            END_IF
        END_IF
        CALL(evt_puni_flag_onoff, 1, 1, 131072)
        IF_INT_EQUAL(GSWF(2848), 1)
            SET_VALUE(GSWF(2848), 0)
        END_IF
        IF_INT_EQUAL(GSWF(2856), 1)
            SET_VALUE(GSWF(2856), 0)
        END_IF
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(apper_toge)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(LW(10), STRING("トゲ族"))
    SET_VALUE(LW(11), STRING("ガイドsp"))
    CALL(evt_npc_set_position, LW(10), 375, 0, -50)
    CALL(evt_npc_set_ry, LW(10), 270)
    CALL(evt_npc_flag_onoff, 1, LW(10), 1073741856)
    CALL(evt_bero_exec_wait, 65536)
    CALL_CHILD(PTR(mri_guide_goryu))
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 270, -130, FLOAT(120.0f))
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, STRING(""), LW(10), 0, 0, 0, 0, 0, 0, 0, 60)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_TOGE_JUMP1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_jump_position_nohit, LW(10), LW(0), LW(1), LW(2), 200, 18)
    WAIT_MS(200)
    CALL(evt_cam3d_evt_set, 319, 151, 578, 319, 56, 37, 1000, 11)
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_TOGE_MOVE1"), LW(0), LW(1), LW(2), LW(9))
    CALL(evt_npc_set_ry, LW(10), 90)
    CALL(evt_npc_move_position, LW(10), 400, 75, 0, FLOAT(180.0f), 0)
    CALL(evt_npc_move_position, LW(10), 470, 75, 0, FLOAT(180.0f), 0)
    CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
    CALL(evt_snd_sfxoff, LW(9))
    WAIT_MS(500)
    CALL(evt_puni_flag_onoff, 1, 0, 262144)
    CALL(evt_puni_set_mode, 1, 30)
    CALL(evt_npc_set_ry, LW(11), 270)
    CALL(evt_npc_flag_onoff, 1, LW(11), 1073743392)
    CALL(evt_cam3d_evt_set, 290, 100, 232, 290, 45, -63, 500, 11)
    SET_VALUE(LW(0), LW(11))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, LW(11), 290, -66, 0, FLOAT(120.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_npc_set_ry, LW(11), 90)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e17_03_02"), 0, LW(11))
    CALL(evt_npc_set_ry, LW(11), 270)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e17_03_03"), 0, LW(11))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_npc_get_position, LW(11), LW(0), LW(1), LW(2))
    CALL(evt_puni_set_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_puni_set_mode, 1, 1)
    CALL(evt_puni_flag_onoff, 1, 1, 262144)
    SET_VALUE(GSW(0), 97)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(cloud_wind_event)
    SET_VALUE(GSWF(2846), 1)
    RETURN
EVT_END()

EVT_BEGIN(mri_06_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 6, 0, -309, -1000, -1000, 0, 1)
    CALL(evt_puni_set_hamari, 0, -309, 70, 2, -2, -307, -311)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(mri_puni_init))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_npc_flag_onoff, 1, STRING("トゲ族"), 524288)
    CALL(evt_npc_check, STRING("パイダース2F_2"), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_npc_flag_onoff, 1, STRING("パイダース2F_2"), 524288)
    END_IF
    CALL(evt_npc_check, STRING("パイダース2F_3"), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_npc_flag_onoff, 1, STRING("パイダース2F_3"), 524288)
    END_IF
    SPAWN_EVENT(PTR(puni_disp_info))
    SPAWN_EVENT(PTR(mri_countdown))
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(109, 110)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI1"))
    END_SWITCH
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -250, -249, -100, PTR(mri_puni_save), 0)
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    CALL(evt_npc_change_fbat_mode, 1)
    SPAWN_EVENT(PTR(door_switch_init))
    SPAWN_EVENT(PTR(puni_lose))
    IF_INT_EQUAL(GSW(0), 96)
        SPAWN_EVENT(PTR(apper_toge))
    END_IF
    SPAWN_EVENT(PTR(puni_piders_check))
    CALL(evt_mobj_badgeblk, STRING("mobj_badge_gat"), -150, 85, -138, 277, 0, GSWF(2845), 1)
    CALL(evt_mobj_brick, STRING("mobj_hidden1"), -150, 0, -138, 121, 11, 0, LSWF(1))
    IF_INT_EQUAL(GSWF(2846), 0)
        CALL(evt_cloud_init)
        CALL(evt_cloud_ent, 0, STRING("S_nisekabe"), STRING("A_nisekabe"), PTR(cloud_wind_event))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_nisekabe"), 1)
        CALL(evt_hitobj_onoff, STRING("A_nisekabe"), 1, 0)
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_oku_ha"), 2)
    CALL(evt_hitobj_onoff, STRING("A_futa\0"), 1, 0)
    RETURN
EVT_END()

