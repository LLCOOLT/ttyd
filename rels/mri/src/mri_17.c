#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/imgdrv.h"
#include "mario/mariost.h"

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff);
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
USER_FUNC(evt_item_set_position);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_set_offscreen);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_mobj_breaking_floor);
USER_FUNC(evt_mobj_switch_blue);
USER_FUNC(evt_mri_get16bitdata);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_glide_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_sound_data_reset);
USER_FUNC(evt_npc_sound_data_set);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_offscreen_get_boundingbox);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_puni_all_fall_check);
USER_FUNC(evt_puni_count_area);
USER_FUNC(evt_puni_flag_onoff);
USER_FUNC(evt_puni_get_flag);
USER_FUNC(evt_puni_get_position);
USER_FUNC(evt_puni_get_trap_index);
USER_FUNC(evt_puni_init_puni);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_set_anim);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_mode);
USER_FUNC(evt_puni_set_position);
USER_FUNC(evt_puni_set_trap_index);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_puni_wait_systemmode);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_area_check);
USER_FUNC(evt_target_flag_onoff);
USER_FUNC(evt_target_set_position);
static USER_FUNC(set_depthPlaneOffset);
extern s32 evt_bero_info_run[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 mri_countdown[];
extern s32 mri_guide_goryu[];
extern s32 mri_puni_init[];
extern s32 mri_puni_walk_se[];
extern s32 mri_punipuni_itemremove[];
extern s32 mri_punipuni_itemselect[];
extern s32 mri_punipuni_itemset[];
extern s32 mri_punipuni_setup[];
extern s32 puni_disp_info[];

__declspec(section ".data") u64 fd_mri_17_negone_one_374;
__declspec(section ".data") s32 fd_mri_17_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_17___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_17___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_17_one_negone_373;
__declspec(section ".data") s32 fd_mri_17___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_17_one_381[1];
__declspec(section ".data") u64 fd_mri_17_negone_one_360;
__declspec(section ".data") s32 fd_mri_17_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_17___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_17___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_17_one_negone_359;
__declspec(section ".data") s32 fd_mri_17___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_17_one_364[1];
s32 bero_02_into_event[14];
static s32 bero_entry_data[60];
static __declspec(section ".data") s32 guide_init[2];
static __declspec(section ".data") s32 guide_talk[8];
static __declspec(section ".data") s32 sister_init[2];
static __declspec(section ".data") s32 sister_talk[8];
static __declspec(section ".data") s32 rival_init[2];
static __declspec(section ".data") s32 rival_talk[8];
static s32 npcEnt[92];
static s32 ueki_access_data[16];
s32 trap_position[102];
s32 trap_main[122];
s32 trap_restore[59];
s32 wana_kemuri[130];
s32 wana_offscreen[219];
s32 trap_event[716];
s32 trap_check[185];
static s32 punipuni_ball00_init[34];
static s32 punipuni_ball00[45];
static __declspec(section ".data") s32 breakyuka_init[11];
static s32 breakyuka_main[131];
s32 strange_statue[56];
s32 switch_event[41];
s32 mri_17_init_evt[208];

__declspec(section ".data") u64 fd_mri_17_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_17_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_17___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_17___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_17_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_17___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_17_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_17_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_17_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_17___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_17___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_17_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_17___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_17_one_364[] = {
    1065353216,
};

EVT_BEGIN(bero_02_into_event)
    IF_INT_EQUAL(GSWF(2872), 0)
        SPAWN_EVENT(PTR(strange_statue))
        SET_VALUE(GSWF(2872), 1)
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"mri_12", (s32)"e_bero_2", 65537, 0, 0, (s32)"dokan1",
    131072, 9, 100000, 0, 0, -1, 0, 6,
    0, 0, (s32)"dokan2", 65537, 0, 0, (s32)"dokan2", 131072,
    2, 100000, 0, 0, -1, (s32)bero_02_into_event, 10, 0,
    0, (s32)"dokan1", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static __declspec(section ".data") EVT_BEGIN(guide_init)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(guide_talk)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_06"), 0, STRING("me"))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(sister_init)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(sister_talk)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_07"), 0, STRING("me"))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(rival_init)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(rival_talk)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_08"), 0, STRING("me"))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガイド"*/"\x83\x4B\x83\x43\x83\x68", 1536, 0, (s32)guide_init, 0, (s32)guide_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ガイド妹"*/"\x83\x4B\x83\x43\x83\x68\x96\x85",
    1536, 0, (s32)sister_init, 0, (s32)sister_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ライバル"*/"\x83\x89\x83\x43\x83\x6F\x83\x8B", 1536,
    0, (s32)rival_init, 0, (s32)rival_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 ueki_access_data[] = {
    1, (s32)"A_f1_ueki01", (s32)"S_f1_ueki01", 0, 1, (s32)"A_f1_ueki02", (s32)"S_f1_ueki02", 0,
    1, (s32)"A_f1_ueki03", (s32)"S_f1_ueki03", 0, 4, 0, 0, 0,
};

s32 trap_position[] = {
    4587498, 4653047, 4259829, 3080158, 2621395, 3735521, 4259825, 2621434,
    4521959, 4128740, 2097133, 2359287, 3014607, 3997686, 2031593, 2883572,
    4653028, 2097121, 1703917, 1441766, 4063219, 3669997, 3801043, 3014646,
    3145734, 3473385, 4128722, 3735514, 2031578, 2490338, 2424830, 1900515,
    2097104, 3932139, 2359280, 5111775, 3801041, 3080154, 2752489, 2097115,
    2621394, 3473393, 2293721, 4521962, 4194299, 4456412, 3014627, 3276752,
    5046235, 2424818, 3407815, 1179619, 3670007, 4849624, 3866621, 3997635,
    2293721, 4587502, 4587487, 3276779, 3538937, 3669964, 2228207, 3407841,
    5373941, 3211255, 3604428, 3145727, 3866598, 4390867, 2031591, 3014638,
    3080167, 2883538, 2752502, 4063188, 2752484, 2883533, 5832677, 3342296,
    3407836, 3342327, 2228171, 2555883, 2031571, 2752462, 4259800, 2097119,
    4521973, 4456400, 3932126, 4325336, 3735545, 4587489, 3080147, 5046246,
    3538917, 4325358, 1769461, 4521931, 2752477, 3276742,
};

EVT_BEGIN(trap_main)
    CALL(evt_puni_wait_systemmode, 2)
    SET_VALUE(LW(10), 1)
    SET_VALUE(LW(11), 0)
    LOOP(0)
        CALL(evt_mri_get16bitdata, PTR(trap_position), LW(11), LW(0))
        ADD(LW(11), 1)
        CALL(evt_mri_get16bitdata, PTR(trap_position), LW(11), LW(2))
        ADD(LW(11), 1)
        CALL(evt_puni_get_trap_index, LW(10), LW(12))
        IF_INT_EQUAL(LW(12), 1)
            CALL(evt_puni_init_puni, LW(10), 24, LW(0), 0, LW(2), 0)
            CALL(evt_puni_flag_onoff, LW(10), 0, 10485760)
            IF_INT_EQUAL(LW(10), 1)
                CALL(evt_puni_flag_onoff, LW(10), 0, 2048)
                CALL(evt_puni_set_position, LW(10), 39, 0, 14)
                CALL(evt_npc_set_position, STRING("ガイド"), 39, 0, 14)
            END_IF
            IF_INT_EQUAL(LW(10), 2)
                CALL(evt_puni_flag_onoff, LW(10), 0, 2048)
                CALL(evt_puni_set_position, LW(10), 113, 0, 17)
                CALL(evt_npc_set_position, STRING("ガイド妹"), 113, 0, 17)
            END_IF
            IF_INT_EQUAL(LW(10), 4)
                CALL(evt_puni_flag_onoff, LW(10), 0, 2048)
                CALL(evt_puni_set_position, LW(10), 120, 0, -50)
                CALL(evt_npc_set_position, STRING("ライバル"), 120, 0, -50)
            END_IF
        END_IF
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(trap_restore)
    CALL(evt_puni_wait_systemmode, 2)
    SET_VALUE(LW(10), 1)
    SET_VALUE(LW(11), 0)
    LOOP(0)
        CALL(evt_mri_get16bitdata, PTR(trap_position), LW(11), LW(0))
        ADD(LW(11), 1)
        CALL(evt_mri_get16bitdata, PTR(trap_position), LW(11), LW(2))
        ADD(LW(11), 1)
        CALL(evt_puni_get_trap_index, LW(10), LW(12))
        IF_INT_EQUAL(LW(12), 1)
            CALL(evt_puni_init_puni, LW(10), 16, LW(0), 0, LW(2), 0)
            CALL(evt_puni_flag_onoff, LW(10), 0, 8388608)
        END_IF
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(wana_kemuri)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, -18, 25, 76, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 5, 10, 70, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 23, 23, 77, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 41, 0, 70, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 66, 9, 72, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 85, 14, 70, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 103, 2, 78, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, 124, 15, 70, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(wana_offscreen)
    CALL(evt_img_entry, STRING("capture_img"))
    CALL(evt_img_set_paper, STRING("capture_img"), STRING("OFF_d_batan"))
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_hako"), STRING("offscreen"))
    CALL(evt_img_alloc_capture, STRING("capture_img"), 0, STRING("offscreen"), 1, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF2_DOOR_GRID_SHUT1"), 50, 0, 0, 0)
        WAIT_MS(1750)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_DOOR_GRID_DOWN1"), 50, 0, 0, 0)
        SPAWN_EVENT(PTR(wana_kemuri))
        CALL(evt_cam_shake, 4, FLOAT(0.029296875f), FLOAT(0.0f), 500)
    END_INLINE_EVENT
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_1"))
    CALL(evt_img_onoff, STRING("capture_img"), 1)
    CALL(evt_img_wait_animend, STRING("capture_img"))
    CALL(evt_img_free_capture, STRING("capture_img"), 0)
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_release, STRING("capture_img"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_hako"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako"), 1)
    CALL(evt_hitobj_onoff, STRING("A_hako"), 1, 1)
    CALL(evt_img_entry, STRING("capture_img"))
    CALL(evt_img_set_paper, STRING("capture_img"), STRING("OFF_d_saku"))
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_dokan1"), STRING("offscreen"))
    CALL(evt_offscreen_get_boundingbox, STRING("offscreen"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, STRING("capture_img"), 0, 0, 1, LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_clear_virtual_point, STRING("capture_img"))
    CALL(set_depthPlaneOffset, STRING("capture_img"), FLOAT(-4.0f))
    CALL(evt_img_set_shadow, STRING("capture_img"), 2)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("A_dokan1"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF2_DOKAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF2_DOKAN_APPEAR2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_2"))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_dokan1"), 1)
    CALL(evt_img_onoff, STRING("capture_img"), 1)
    CALL(evt_img_wait_animend, STRING("capture_img"))
    CALL(evt_img_free_capture, STRING("capture_img"), 0)
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_release, STRING("capture_img"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_dokan1"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_dokan1"), 1)
    CALL(evt_hitobj_onoff, STRING("A_dokan1"), 1, 1)
    RETURN
EVT_END()

EVT_BEGIN(trap_event)
    WAIT_WHILE(GF(15))
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力幹部"), 1073742368)
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力部下Ａ"), 1073742368)
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力部下Ｂ"), 1073742368)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 80, 151, 555, 80, 56, 13, 500, 11)
    WAIT_MS(500)
    CALL_CHILD(PTR(wana_offscreen))
    CALL_CHILD(PTR(mri_guide_goryu))
    CALL(evt_target_flag_onoff, 0, 1, 1)
    SET_VALUE(LW(10), 1)
    LOOP(0)
        CALL(evt_puni_set_mode, LW(10), 24)
        CALL(evt_puni_flag_onoff, LW(10), 0, 2097152)
        CALL(evt_puni_set_anim, LW(10), 0)
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_puni_flag_onoff, 1, 0, 262144)
    CALL(evt_puni_set_mode, 1, 30)
    CALL(evt_puni_get_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1073743392)
    CALL(evt_npc_set_ry, STRING("ガイド"), 270)
    SET_VALUE(LW(0), STRING("ガイド"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_glide_position, STRING("ガイド"), 12, 6, 8, 0, FLOAT(120.0f), 0, 0, 0)
    DELETE_EVENT(LW(9))
    CALL(evt_cam3d_evt_set, 13, 110, 326, 13, 56, 20, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_01"), 0, STRING("ガイド"))
    CALL(evt_msg_toge, 2, 5, 230, 0)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_3RD_ENEMY"))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_02"), 0, 0)
    CALL(evt_cam3d_evt_set, 50, 164, 624, 50, 56, 7, 500, 11)
    WAIT_MS(500)
    CALL(evt_npc_set_position, STRING("第三勢力部下Ａ"), 10, 180, 90)
    CALL(evt_npc_set_position, STRING("第三勢力部下Ｂ"), 90, 180, 90)
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), 50, 180, 90)
    CALL(evt_npc_set_ry, STRING("第三勢力部下Ａ"), 90)
    CALL(evt_npc_set_ry, STRING("第三勢力部下Ｂ"), 270)
    CALL(evt_npc_sound_data_set, STRING("第三勢力部下Ａ"), 0, 0, 0, 0, 0)
    CALL(evt_npc_sound_data_set, STRING("第三勢力部下Ｂ"), 0, 0, 0, 0, 0)
    CALL(evt_npc_sound_data_set, STRING("第三勢力幹部"), 0, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_npc_set_anim, STRING("第三勢力部下Ａ"), STRING("R_1"))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_3RD_FALL1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_set_anim, STRING("第三勢力部下Ａ"), STRING("S_1"))
        CALL(evt_npc_glide_position, STRING("第三勢力部下Ａ"), 10, 0, 90, 500, 0, 0, 2, 0)
        CALL(evt_npc_set_position, STRING("第三勢力部下Ａ"), 10, 0, 90)
        CALL(evt_npc_get_position, STRING("第三勢力部下Ａ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_3RD_LANDING1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_set_anim, STRING("第三勢力部下Ａ"), STRING("S_1"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(150)
        CALL(evt_npc_set_anim, STRING("第三勢力部下Ｂ"), STRING("R_1"))
        CALL(evt_npc_get_position, STRING("第三勢力部下Ｂ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_3RD_FALL1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_glide_position, STRING("第三勢力部下Ｂ"), 90, 0, 90, 500, 0, 0, 2, 0)
        CALL(evt_npc_set_position, STRING("第三勢力部下Ｂ"), 90, 0, 90)
        CALL(evt_npc_get_position, STRING("第三勢力部下Ｂ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_3RD_LANDING1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_set_anim, STRING("第三勢力部下Ｂ"), STRING("S_1"))
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("第三勢力幹部"), STRING("R_1"))
    CALL(evt_npc_get_position, STRING("第三勢力幹部"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_KANBU_FALL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_glide_position, STRING("第三勢力幹部"), 50, 0, 90, 500, 0, 0, 2, 0)
    CALL(evt_npc_set_position, STRING("第三勢力幹部"), 50, 0, 90)
    CALL(evt_npc_get_position, STRING("第三勢力幹部"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_KANBU_LANDING1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING("第三勢力幹部"), STRING("S_1"))
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0068359375f), 500)
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 50, 8, FLOAT(120.0f))
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力幹部"), 1024)
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力部下Ａ"), 1024)
    CALL(evt_npc_flag_onoff, 1, STRING("第三勢力部下Ｂ"), 1024)
    CALL(evt_npc_sound_data_reset, STRING("第三勢力部下Ａ"))
    CALL(evt_npc_sound_data_reset, STRING("第三勢力部下Ｂ"))
    CALL(evt_npc_sound_data_reset, STRING("第三勢力幹部"))
    CALL(evt_cam3d_evt_set, 50, 121, 451, 50, 43, 7, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_03"), 0, STRING("第三勢力幹部"))
    CALL(evt_cam3d_evt_set, 50, 151, 548, 50, 56, 7, 500, 11)
    WAIT_MS(500)
    CALL(evt_npc_set_ry, STRING("第三勢力幹部"), 270)
    WAIT_MS(200)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_npc_set_ry, STRING("第三勢力部下Ａ"), 90)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_04"), 0, STRING("第三勢力幹部"))
    WAIT_MS(500)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, -58, 151, 548, -58, 56, 7, 1300, 11)
        WAIT_MS(1300)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), STRING("第三勢力部下Ａ"))
        CALL(evt_npc_set_ry, LW(10), 270)
        CALL(evt_npc_move_position, LW(10), -84, 66, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_move_position, LW(10), -200, -5, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), STRING("第三勢力部下Ｂ"))
        CALL(evt_npc_set_ry, LW(10), 270)
        CALL(evt_npc_move_position, LW(10), -84, 66, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_move_position, LW(10), -200, -5, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
    END_INLINE_EVENT
    SET_VALUE(LW(10), STRING("第三勢力幹部"))
    CALL(evt_npc_set_ry, LW(10), 270)
    CALL(evt_npc_move_position, LW(10), -84, 66, 0, FLOAT(120.0f), 0)
    CALL(evt_npc_move_position, LW(10), -200, -5, 0, FLOAT(120.0f), 0)
    CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
    WAIT_WHILE(GF(0))
    WAIT_MS(2000)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_cam3d_evt_set, 34, 122, 390, 34, 56, 14, 500, 11)
    WAIT_MS(500)
    CALL(evt_npc_set_ry, STRING("ガイド"), 90)
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_05"), 0, STRING("ガイド"))
    CALL(evt_npc_get_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_puni_flag_onoff, 1, 1, 262144)
    CALL(evt_puni_set_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_puni_set_mode, 1, 24)
    SET_VALUE(GSW(0), 102)
    SET_VALUE(GF(1), 0)
    CALL(evt_cam3d_evt_off, 300, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(2), 73)
            BREAK_LOOP
        END_IF
        IF_INT_LESS_OR_EQUAL(LW(2), -105)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_stop, 0)
    CALL(evt_msg_print_party, STRING("stg2_mri_e18_00_09"))
    CALL(evt_puni_get_position, 1, LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_12"), 0, STRING("ガイド"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
    RETURN
EVT_END()

EVT_BEGIN(trap_check)
    SET_VALUE(LW(10), 50)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(12), -25)
    SET_VALUE(LW(13), 70)
    CALL(evt_puni_wait_systemmode, 2)
    LOOP(0)
        CALL(evt_puni_count_area, LW(10), LW(11), LW(12), LW(13), LW(8))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_area_check, 1, LW(10), LW(12), LW(13), LW(0), LW(2), LW(9))
        IF_INT_GREATER_OR_EQUAL(LW(11), 5)
            SET_VALUE(LW(9), 0)
        END_IF
        IF_INT_LESS_OR_EQUAL(LW(11), -5)
            SET_VALUE(LW(9), 0)
        END_IF
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_area_check, 1, LW(10), LW(12), LW(13), LW(0), LW(2), LW(14))
        IF_INT_GREATER_OR_EQUAL(LW(11), 5)
            SET_VALUE(LW(14), 0)
        END_IF
        IF_INT_LESS_OR_EQUAL(LW(11), -5)
            SET_VALUE(LW(14), 0)
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(8), 10)
            IF_INT_EQUAL(GSWF(2870), 1)
                IF_INT_EQUAL(LW(9), 1)
                    IF_INT_EQUAL(LW(14), 1)
                        BREAK_LOOP
                    END_IF
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SPAWN_EVENT(PTR(trap_event))
    SET_VALUE(GF(1), 1)
    WAIT_WHILE(GF(1))
    SET_VALUE(LW(8), 1)
    LOOP(0)
        CALL(evt_puni_get_flag, LW(8), LW(9))
        AND(LW(9), 1024)
        IF_INT_NOT_EQUAL(LW(9), 0)
            CALL(evt_puni_get_position, LW(8), LW(0), LW(1), LW(2))
            SET_VALUE(LW(9), 0)
            IF_INT_GREATER(LW(0), -50)
                IF_INT_LESS(LW(0), 160)
                    IF_INT_GREATER(LW(2), -100)
                        IF_INT_LESS(LW(2), 70)
                            IF_INT_LESS(LW(1), 10)
                                IF_INT_GREATER(LW(1), -5)
                                    SET_VALUE(LW(9), 1)
                                END_IF
                            END_IF
                        END_IF
                    END_IF
                END_IF
            END_IF
            IF_INT_EQUAL(LW(9), 1)
                CALL(evt_puni_flag_onoff, LW(8), 0, 8388608)
                CALL(evt_puni_set_trap_index, LW(8), 1)
            END_IF
        END_IF
        ADD(LW(8), 1)
        IF_INT_EQUAL(LW(8), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(punipuni_ball00_init)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_sui_hikari"), 1)
    CALL_CHILD(PTR(mri_punipuni_setup))
    IF_INT_EQUAL(GSWF(2870), 1)
        CALL(evt_item_set_position, LW(10), 50, 30, -58)
        CALL(evt_target_flag_onoff, LW(11), 0, 3)
    END_IF
    CALL(evt_target_set_position, LW(11), 50, 0, -15)
    SET_VALUE(GF(15), 0)
    RETURN
EVT_END()

static EVT_BEGIN(punipuni_ball00)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_EQUAL(GSWF(2870), 0)
        CALL_CHILD(PTR(mri_punipuni_itemselect))
        IF_INT_EQUAL(LW(1), 0)
            GOTO(100)
        END_IF
        SET_VALUE(GSWF(2870), 1)
        CALL(evt_item_set_position, LW(10), 50, 30, -58)
        SET_VALUE(GF(15), 1)
        CALL_CHILD(PTR(mri_punipuni_itemset))
        SET_VALUE(GF(15), 0)
        ELSE
        SET_VALUE(GSWF(2870), 0)
        CALL_CHILD(PTR(mri_punipuni_itemremove))
    END_IF
    LABEL(100)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(breakyuka_init)
    IF_INT_EQUAL(GSWF(2871), 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_01"), 1, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(breakyuka_main)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak_01"), 1, 1)
    CALL(evt_puni_all_fall_check)
    CALL(evt_mario_wait_landon)
    CALL(evt_puni_get_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e18_00_13"), 0, STRING("ガイド"))
    SET_VALUE(LW(10), 1)
    SET_VALUE(LW(11), 2)
    SET_VALUE(LW(12), 4)
    CALL(evt_puni_flag_onoff, LW(10), 1, 2048)
    CALL(evt_npc_set_position, STRING("ガイド"), 0, -1000, 0)
    CALL(evt_puni_get_trap_index, LW(11), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_puni_flag_onoff, LW(11), 1, 2048)
        CALL(evt_npc_set_position, STRING("ガイド妹"), 0, -1000, 0)
    END_IF
    CALL(evt_puni_get_trap_index, LW(12), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_puni_flag_onoff, LW(12), 1, 2048)
        CALL(evt_npc_set_position, STRING("ライバル"), 0, -1000, 0)
    END_IF
    SET_VALUE(LW(10), 1)
    LOOP(0)
        CALL(evt_puni_get_trap_index, LW(10), LW(12))
        IF_INT_EQUAL(LW(12), 1)
            CALL(evt_puni_set_mode, LW(10), 16)
            CALL(evt_puni_flag_onoff, LW(10), 1, 2097152)
        END_IF
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(GSW(0), 106)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
    RETURN
EVT_END()

EVT_BEGIN(strange_statue)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    CALL(evt_party_move_pos2, 0, 50, -50, FLOAT(120.0f))
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(300)
    CALL(evt_party_set_dir, 0, 90, 200)
    WAIT_MS(400)
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(350)
    CALL(evt_party_set_dir, 0, 90, 200)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg2_mri_e18_00_11"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(switch_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_wait_landon)
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING("SFX_STG2_SWITCH_QUAKE1"), LW(10))
    CALL(evt_cam_shake, 4, FLOAT(0.0146484375f), FLOAT(0.0f), 1000)
    CALL(evt_snd_sfxoff, LW(10))
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    CALL(evt_msg_print_party, STRING("stg2_mri_e18_00_10"))
    CALL(evt_party_run, 0)
    SET_VALUE(GSW(0), 103)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(mri_17_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 17, 0, -309, -1000, -1000, 6, 0)
    CALL(evt_puni_set_hamari, -128, 0, 94, 7, -3, -307, -311)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(mri_puni_init))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT(PTR(puni_disp_info))
    SPAWN_EVENT(PTR(mri_countdown))
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    CALL(evt_map_playanim, STRING("sui_hikari"), 1, 0)
    SPAWN_EVENT(PTR(mri_countdown))
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(109, 110)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI4"))
    END_SWITCH
    SET_VALUE(LW(10), STRING("punipuni"))
    SET_VALUE(LW(11), 0)
    SPAWN_EVENT(PTR(punipuni_ball00_init))
    CALL(evt_run_case_evt, 9, 1, STRING("A_dai_mae"), 0, PTR(punipuni_ball00), 0)
    SPAWN_EVENT(PTR(breakyuka_init))
    CALL(evt_mobj_breaking_floor, STRING("mobj_bf00"), 0, 0, -35, 1, PTR(breakyuka_main), GSWF(2871))
    IF_INT_LESS(GSW(0), 103)
        CALL(evt_mobj_switch_blue, 1, STRING("switch"), 60, -309, 53, PTR(switch_event), 0)
    END_IF
    CALL(evt_item_entry, STRING("item_01"), 125, 168, -310, -44, 16, GSWF(5617), 0)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(101)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hako"), 1)
        CALL(evt_hitobj_onoff, STRING("A_hako"), 1, 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_dokan1"), 1)
        CALL(evt_hitobj_onoff, STRING("A_dokan1"), 1, 0)
        CALL(evt_paper_entry, STRING("OFF_d_batan"))
        CALL(evt_paper_entry, STRING("OFF_d_saku"))
        SPAWN_EVENT(PTR(trap_check))
        CASE_BETWEEN(102, 105)
        SPAWN_EVENT(PTR(trap_main))
        CASE_BETWEEN(106, 107)
        SPAWN_EVENT(PTR(trap_restore))
        CASE_GREATER_OR_EQUAL(106)
    END_SWITCH
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_saku_mae"), 2)
    RETURN
EVT_END()

static USER_FUNC(set_depthPlaneOffset) {
    s32* args = event->args;
    ImageEntry* img = imgNameToPtr((const char*)evtGetValue(event, args[0]), gp->inBattle != 0);

    img->offsetZ = evtGetFloat(event, args[1]);
    return EVT_RETURN_DONE;
}
