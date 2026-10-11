#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario_pouch.h"
#include "party.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include "driver/npcdrv.h"
#include "memory.h"
#include "dolphin/mtx.h"
#include "stdlib.h"
#include "mario/mariost.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "eff/eff_small_star.h"
#include "manager/evtmgr_cmd.h"
#include "eff/eff_kemu_test.h"
#include "driver/fadedrv.h"
#include "driver/effdrv.h"

typedef struct UsuCbInfo { u8 field_0x0[0x8]; u16 field_0x8; } UsuCbInfo;
typedef struct KpaSen { s8 state; u8 field_0x1; u16 wait; f32 t; Vec start; Vec end; u8 pose99Lo; u8 pose99Hi; u8 pose1Lo; u8 pose1Hi; } KpaSen;
KpaSen* kpaSen;
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
s32 calcPose(s32 i, s32 lo, s32 hi, s32 flag);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
void extLoadShadowMtx(Mtx mtx);
void extLoadShadowRenderMode(void);
void extLoadShadowVertex(void);
void extLoadShadowTev(void);
void extDrawShadow(void);
void kpaSen_ext_disp(CameraId camera, void* param);
void kpaSen_ext_shadow_disp(CameraId camera, void* param);
void effKemuTestDrawCam(EffectEntry* effect, s32 camera);

USER_FUNC(L_evt_hitobj_flag_onoff);
USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos);
static USER_FUNC(anim_tevcallback);
USER_FUNC(bakuhatu_kemuri);
static USER_FUNC(booboo_main);
static USER_FUNC(delete_npc_regl_evt);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_bg_set_color);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam3d_evt_set_npc_rel);
USER_FUNC(evt_cam3d_evt_set_rel);
USER_FUNC(evt_cam_get_at);
USER_FUNC(evt_cam_get_pos);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_cam_letter_box_onoff);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff64);
USER_FUNC(evt_eff_delete);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_delete);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_item_get_position);
USER_FUNC(evt_item_set_bound_rate);
USER_FUNC(evt_item_set_gravity);
USER_FUNC(evt_item_set_jump_power);
USER_FUNC(evt_item_set_move_dir_speed);
USER_FUNC(evt_item_set_position);
USER_FUNC(evt_item_status_on);
USER_FUNC(evt_kagemario_init_29_text_1A0C);
USER_FUNC(evt_key_get_buttontrg);
USER_FUNC(evt_kinopio_setup);
USER_FUNC(evt_koopa_fire);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_balloon_off);
USER_FUNC(evt_mario_balloon_tenten);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_dump_item);
USER_FUNC(evt_mario_flag_onoff);
USER_FUNC(evt_mario_get_mode);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_party_use_check);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_mode);
USER_FUNC(evt_mario_set_motion);
USER_FUNC(evt_mario_set_party);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_wait_rideon);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_delete);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_dir);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_get_reglid);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_kamek_move_position);
USER_FUNC(evt_npc_majo_disp_off);
USER_FUNC(evt_npc_majo_disp_on);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_restart_regular_event);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_autotalkpose);
USER_FUNC(evt_npc_set_height);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_stay_anim);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_set_width);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_start_for_event);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_stop_for_event);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_dispflg_onoff);
USER_FUNC(evt_party_get_status);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_party_yoshi_ride);
USER_FUNC(evt_pouch_all_party_recovery);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_mario_recovery);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfx_all_stop);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_area_check);
USER_FUNC(evt_sub_get_coin);
USER_FUNC(evt_sub_get_dir);
USER_FUNC(evt_sub_get_dist);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_sub_rumble_onoff);
USER_FUNC(evt_telop_entry);
USER_FUNC(evt_win_item_select);
static USER_FUNC(getYoshiColor);
USER_FUNC(kpaSen_toge_syugo);
USER_FUNC(kpaSen_zako_syugo);
USER_FUNC(kpa_chg_pose);
USER_FUNC(mainwindow_opendisable);
USER_FUNC(mainwindow_openenable);
static USER_FUNC(npc_process);
USER_FUNC(party_scale);
static USER_FUNC(small_star);
static USER_FUNC(starstone_entry);
static USER_FUNC(starstone_set_pos);
static USER_FUNC(starstone_set_ry);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);
USER_FUNC(white_off);
USER_FUNC(white_on);
static USER_FUNC(yami_view);
void kpaSen_ext_dispent(void);
void kpaSen_ext_shadow_disp(CameraId camera, void* param);
void kpaSen_ext_disp(CameraId camera, void* param);
void kpaSen_ext_main(void);
s32 calcPose(s32 i, s32 lo, s32 hi, s32 flag);
void kpaSen_ext_init(void);
void kpa_stg5_009_7_cb(s32 type, UsuCbInfo** param);
USER_FUNC(party_tev);
extern s32 all_party_lecture_29_data_10988[];
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 envSetYami[];
extern s32 evt_bero_info_run[];
extern s32 evt_door_entry[];
extern s32 evt_door_open[];
extern s32 evt_memcard_save[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 evt_sub_tree_access_entry[];
extern s32 evt_usu_kagemario_party_kill_29_data_104A8[];
extern s32 npc_init_evt[];

__declspec(section ".data") u64 fd_usu_00_negone_one_374;
__declspec(section ".data") s32 fd_usu_00_neg_one_382[1];
__declspec(section ".data") s32 fd_usu_00___local_PI_383[1];
__declspec(section ".data") s32 fd_usu_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_usu_00_one_negone_373;
__declspec(section ".data") s32 fd_usu_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_usu_00_one_381[1];
__declspec(section ".data") u64 fd_usu_00_negone_one_360;
__declspec(section ".data") s32 fd_usu_00_neg_one_365[1];
__declspec(section ".data") s32 fd_usu_00___local_PI_366[1];
__declspec(section ".data") s32 fd_usu_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_usu_00_one_negone_359;
__declspec(section ".data") s32 fd_usu_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_usu_00_one_364[1];
s32 villagerA_init[28];
s32 villagerA_pig_init[19];
s32 villagerA_talk[65];
__declspec(section ".data") s32 villagerB_init[7];
s32 villagerB_talk[52];
__declspec(section ".data") s32 villagerC_init[7];
s32 villagerC_talk[52];
s32 villagerD_init[19];
s32 villagerD_pig_init[19];
s32 villagerD_talk[88];
s32 villagerE_init[19];
s32 villagerE_pig_init[19];
s32 villagerE_talk[65];
s32 villagerK_init[19];
s32 villagerK_pig_init[19];
s32 villagerK_talk[65];
s32 village_chief_init[20];
s32 village_chief_pig_init[27];
__declspec(section ".data") s32 iri_15_item_tbl[2];
s32 village_chief_talk[199];
s32 chief_mario_talk_init[183];
s32 chief_mario_talk[55];
static s32 vivian_init[44];
static __declspec(section ".data") s32 key_tbl[2];
static s32 vivian_talk[29];
__declspec(section ".data") s32 nise_mario_talk[8];
__declspec(section ".data") s32 christine_talk[8];
__declspec(section ".data") s32 nokotaro_talk[8];
__declspec(section ".data") s32 cloud_talk[8];
__declspec(section ".data") s32 yoshi_talk[8];
__declspec(section ".data") s32 crow_a_init[8];
__declspec(section ".data") s32 crow_b_init[8];
__declspec(section ".data") s32 crow_c_init[8];
__declspec(section ".data") s32 crow_d_init[8];
__declspec(section ".data") s32 crow_e_init[8];
static s32 urouro_move[24];
static s32 npcEnt[460];
s32 usu00_stage4_coming_event[839];
s32 usu00_3witch_init[41];
s32 usu00_3witch_event[275];
s32 gra00_2witch_find_ranpel_event[197];
s32 usu00_vivian_cry_event[58];
s32 usu00_vivian_joinup_event[608];
static s32 cam_up[34];
static __declspec(section ".data") s32 cam_down[8];
s32 usu00_check_vivian[33];
s32 usu00_crowAB_talk_event[299];
s32 usu00_crowCDE_talk_event[307];
s32 chief_pig_event[66];
static s32 kino_dt[38];
static __declspec(section ".data") s32 yado_npc[2];
__declspec(section ".data") s32 yado_mobj[2];
__declspec(section ".data") s32 village_chief_npc[8];
static __declspec(section ".data") s32 evt_door_1_1[12];
static __declspec(section ".data") s32 evt_door_1_2[2];
static s32 evt_wall_1[30];
__declspec(section ".data") s32 door_1_npc[2];
static __declspec(section ".data") s32 door_1_open[12];
static s32 door_1_close[14];
static s32 door_1[18];
__declspec(section ".data") s32 evt_door_2_1[12];
s32 evt_door_2_2[15];
static s32 evt_wall_2[123];
s32 evt_door2_chk[30];
s32 evt_door2_close[14];
static s32 door_2[18];
static __declspec(section ".data") s32 evt_door_3_1[12];
static __declspec(section ".data") s32 evt_door_3_2[12];
static s32 evt_wall_3[30];
static __declspec(section ".data") s32 door_3_open[12];
static s32 door_3_close[14];
static s32 door_3[18];
s32 dokan_1_evt[32];
static s32 bero_entry_data[45];
static s32 oshimodo_event[28];
static s32 bero_oshimodo[15];
s32 koopa_dokan_evt[57];
s32 bero_koopa_dokan[15];
s32 door_ie1_koopa_evt[26];
s32 door_ie2_koopa_evt[26];
s32 door_ie3_koopa_evt[26];
static s32 evt_ki_1[20];
static s32 evt_ki_2[28];
static s32 tree_tbl[24];
__declspec(section ".data") s32 usu_00_tree_init[7];
s32 kusa_01_evt[26];
s32 evt_kusa_04[25];
s32 evt_kusa_06[25];
static s32 kusa_tbl[84];
__declspec(section ".data") s32 usu_00_kusa_init[7];
__declspec(section ".data") s32 evt_ichikorori_ball_get[5];
s32 usu_00_touch_ichikorori_ball[72];
static __declspec(section ".data") s32 booboo_name[10];
s32 kpaSen_ext_entry_data[117];
static __declspec(section ".data") s32 baba_talk[8];
s32 kanbu_regl[48];
__declspec(section ".data") s32 kanbu_talk[4];
static s32 koopa_npc_entry[205];
s32 usu_00_koopa_first_evt[196];
s32 bakuhatu_evt[64];
s32 murabito_out[172];
s32 usu_00_koopa_second_evt[1315];
static s32 sekai_yami_npc_init[17];
static s32 sekai_yami_npc[22];
static __declspec(section ".data") s32 sekai_yami_shake[11];
static s32 sekai_yami_evt[260];
static s32 minnnanokoe_npc_entry[94];
static s32 minnnanokoe_evt[381];
static s32 evt_after_peach[151];
static s32 epilogue_npc_entry[48];
static s32 epilogue_evt_sub[167];
static s32 epilogue_evt[73];
s32 usu_00_init_evt[658];

static USER_FUNC(getYoshiColor) {
    s32* args = event->args;
    evtSetValue(event, args[0], pouchGetPartyColor(4));
    return EVT_RETURN_DONE;
}

USER_FUNC(party_tev) {
    animPoseSetMaterialFlagOff(partyGetPtr(0)->paperAnimGroup, 0x0F000000);
    return EVT_RETURN_DONE;
}

void kpa_stg5_009_7_cb(s32 type, UsuCbInfo** param) {
    UsuCbInfo* info = *param;

    switch (type) {
        case 3:
            if (info->field_0x8 == 1) {
                psndBGMOn(0x201, "BGM_FF_GET_ITEM1");
            }
            break;
    }
}

static USER_FUNC(booboo_main);
static USER_FUNC(booboo_main) {
    u32 i;

    for (i = 0; i < 5; i++) {
        animPoseSetMaterialLightFlagOn(npcNameToPtr((const char*)booboo_name[i * 2])->poseId, 0x10);
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_usu_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_usu_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_usu_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_usu_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_usu_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_usu_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_usu_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_usu_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_usu_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_usu_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_usu_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_usu_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_usu_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_usu_00_one_364[] = {
    1065353216,
};

EVT_BEGIN(villagerA_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ａ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("村人Ａ"), 0, -2000, 0)
        CASE_BETWEEN(265, 267)
        CALL(evt_npc_set_position, STRING("村人Ａ"), -180, 0, 0)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerA_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ａ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村人Ａ"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerA_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(266)
        CALL(evt_msg_print, 0, STRING("kpa_stg5_005"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_29"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_30"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_31"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_31_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_31_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(villagerB_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｂ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(villagerB_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(266)
        CALL(evt_msg_print, 0, STRING("kpa_stg5_006"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_msg_print, 0, STRING("stg4_usu_32"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_33"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_34"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_34_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_34_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(villagerC_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｃ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(villagerC_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(266)
        CALL(evt_msg_print, 0, STRING("kpa_stg5_007"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_msg_print, 0, STRING("stg4_usu_35"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_36"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_37"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_37_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_37_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerD_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｄ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("村人Ｄ"), 0, -2000, 0)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerD_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｄ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村人Ｄ"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerD_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(266)
        CALL(evt_msg_print, 0, STRING("kpa_stg5_008"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_38"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_39"), 0, STRING("me"))
        CASE_BETWEEN(354, 354)
        IF_INT_EQUAL(GSWF(3889), 1)
            SET_VALUE(GSWF(3880), 1)
            CALL(evt_msg_print, 0, STRING("stg7_usu_01"), 0, STRING("me"))
            ELSE
            CALL(evt_msg_print, 0, STRING("stg4_usu_40"), 0, STRING("me"))
        END_IF
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_40"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_40_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_40_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerE_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｅ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("村人Ｅ"), 0, -2000, 0)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerE_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｅ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村人Ｅ"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerE_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(266)
        CALL(evt_msg_print, 0, STRING("kpa_stg5_009"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_41"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_42"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_43"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerK_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｋ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("村人Ｋ"), 0, -2000, 0)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerK_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｋ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村人Ｋ"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerK_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(266)
        CALL(evt_msg_print, 0, STRING("kpa_stg5_006"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_01"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_02"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_03"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_03_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_43_03_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(village_chief_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村長"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(179)
        CASE_LESS(202)
        CALL(evt_npc_set_position, STRING("村長"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(village_chief_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村長"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(179)
        CALL(evt_npc_set_position, STRING("ブタ村長"), 0, -2000, 0)
        CASE_LESS(202)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村長"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") s32 iri_15_item_tbl[] = {
    98, -1,
};

EVT_BEGIN(village_chief_talk)
    IF_INT_EQUAL(GSW(1420), 17)
        IF_INT_EQUAL(GSWF(5405), 0)
            CALL(evt_msg_print, 0, STRING("irai_17_00"), 0, 0)
            CALL(evt_item_entry, STRING("kairanban"), 98, 0, -1000, 0, 17, -1, 0)
            CALL(evt_item_get_item, STRING("kairanban"))
            CALL(evt_item_get_item_end_wait, STRING("kairanban"))
            SET_VALUE(GSWF(5405), 1)
            ELSE
            IF_INT_EQUAL(GSWF(5406), 0)
                CALL(evt_msg_print, 0, STRING("irai_17_01"), 0, 0)
                ELSE
                IF_INT_EQUAL(GSWF(5407), 0)
                    CALL(evt_msg_print, 0, STRING("irai_17_02"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("irai_17_03"), 0, 0)
                    CALL(evt_win_item_select, 0, PTR(iri_15_item_tbl), LW(0), 0)
                    IF_INT_NOT_EQUAL(LW(0), -1)
                        CALL(evt_pouch_remove_item, 98, LW(0))
                        CALL(evt_msg_print, 0, STRING("irai_17_04"), 0, 0)
                        CALL(evt_sub_get_coin, 30)
                        CALL(evt_msg_print, 0, STRING("irai_17_05"), 0, 0)
                        SET_VALUE(GSW(1420), 0)
                        SET_VALUE(GSWF(5391), 1)
                        CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
                    END_IF
                END_IF
            END_IF
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(180)
        CALL(evt_msg_print, 0, STRING("stg4_usu_20"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_22"), 0, STRING("me"))
        CASE_LESS(210)
        IF_INT_EQUAL(GSWF(1929), 0)
            SET_VALUE(GSWF(1929), 1)
            CALL(evt_msg_print, 0, STRING("stg4_usu_24"), 0, STRING("me"))
            CALL(evt_set_dir_to_target, STRING("me"), STRING("にせマリオ"))
            ELSE
            CALL(evt_msg_print, 0, STRING("stg4_usu_25"), 0, STRING("me"))
            CALL(evt_set_dir_to_target, STRING("me"), STRING("にせマリオ"))
        END_IF
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_25"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_157"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_157_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_157_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(chief_mario_talk_init)
    CALL(evt_npc_entry, STRING("にせマリオ"), STRING("c_mario"))
    CALL(evt_npc_entry, STRING("クリスチーヌ"), STRING("c_pkr"))
    CALL(evt_npc_entry, STRING("ノコタロウ"), STRING("c_pnk"))
    CALL(evt_npc_entry, STRING("クラウダ"), STRING("c_windy"))
    CALL(getYoshiColor, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(0), STRING("c_babyyoshi"))
        CASE_EQUAL(1)
        SET_VALUE(LW(0), STRING("c_babyyoshi2"))
        CASE_EQUAL(2)
        SET_VALUE(LW(0), STRING("c_babyyoshi3"))
        CASE_EQUAL(3)
        SET_VALUE(LW(0), STRING("c_babyyoshi4"))
        CASE_EQUAL(4)
        SET_VALUE(LW(0), STRING("c_babyyoshi5"))
        CASE_EQUAL(5)
        SET_VALUE(LW(0), STRING("c_babyyoshi6"))
        CASE_EQUAL(6)
        SET_VALUE(LW(0), STRING("c_babyyoshi7"))
    END_SWITCH
    CALL(evt_npc_entry, STRING("チビヨッシー"), LW(0))
    CALL(evt_npc_set_tribe, STRING("にせマリオ"), STRING("にせマリオ"))
    CALL(evt_npc_set_tribe, STRING("クリスチーヌ"), STRING("クリスチーヌ"))
    CALL(evt_npc_set_tribe, STRING("ノコタロウ"), STRING("ノコタロウ"))
    CALL(evt_npc_set_tribe, STRING("クラウダ"), STRING("クラウダ"))
    CALL(evt_npc_set_tribe, STRING("チビヨッシー"), STRING("ヨッシー"))
    CALL(evt_npc_flag_onoff, 1, STRING("にせマリオ"), 1074267648)
    CALL(evt_npc_flag_onoff, 1, STRING("クリスチーヌ"), 1074267648)
    CALL(evt_npc_flag_onoff, 1, STRING("ノコタロウ"), 1074267648)
    CALL(evt_npc_flag_onoff, 1, STRING("クラウダ"), 1074267648)
    CALL(evt_npc_flag_onoff, 1, STRING("チビヨッシー"), 1074267648)
    CALL(evt_npc_set_position, STRING("にせマリオ"), -3, 0, -388)
    CALL(evt_npc_set_position, STRING("クリスチーヌ"), -34, 0, -347)
    CALL(evt_npc_set_position, STRING("ノコタロウ"), -75, 0, -316)
    CALL(evt_npc_set_position, STRING("クラウダ"), -125, 0, -341)
    CALL(evt_npc_set_position, STRING("チビヨッシー"), -105, 0, -291)
    CALL(evt_npc_set_ry, STRING("にせマリオ"), 90)
    CALL(evt_npc_set_ry, STRING("クリスチーヌ"), 90)
    CALL(evt_npc_set_ry, STRING("ノコタロウ"), 90)
    CALL(evt_npc_set_ry, STRING("クラウダ"), 90)
    CALL(evt_npc_set_ry, STRING("チビヨッシー"), 90)
    CALL(evt_npc_change_interrupt, STRING("にせマリオ"), 6, PTR(nise_mario_talk))
    CALL(evt_npc_change_interrupt, STRING("クリスチーヌ"), 6, PTR(christine_talk))
    CALL(evt_npc_change_interrupt, STRING("ノコタロウ"), 6, PTR(nokotaro_talk))
    CALL(evt_npc_change_interrupt, STRING("クラウダ"), 6, PTR(cloud_talk))
    CALL(evt_npc_change_interrupt, STRING("チビヨッシー"), 6, PTR(yoshi_talk))
    RETURN
EVT_END()

EVT_BEGIN(chief_mario_talk)
    IF_INT_NOT_EQUAL(GSWF(1930), 0)
        RETURN
    END_IF
    LABEL(0)
    CALL(evt_npc_get_position, STRING("村長"), LW(0), LW(1), LW(2))
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(6))
    IF_INT_GREATER(LW(6), 100)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING("村長"), STRING("にせマリオ"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_23"), 0, STRING("村長"))
    SET_VALUE(GSWF(1930), 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(vivian_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ビビアン"), 525824)
    SWITCH(GSW(0))
        CASE_BETWEEN(203, 205)
        CALL(evt_npc_set_tribe, STRING("ビビアン"), STRING("ビビアンべそ"))
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("PTR_S_3"), STRING("PTR_T_3"))
        CALL(evt_npc_set_position, STRING("me"), -71, 0, 329)
        CALL(evt_npc_set_ry, STRING("me"), 90)
        IF_INT_GREATER_OR_EQUAL(GSW(0), 204)
            CALL(evt_npc_change_interrupt, STRING("me"), 1, PTR(urouro_move))
            CALL(evt_npc_restart_regular_event, STRING("me"))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") s32 key_tbl[] = {
    67, -1,
};

static EVT_BEGIN(vivian_talk)
    CALL(evt_pouch_check_item, 67, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL_CHILD(PTR(usu00_vivian_joinup_event))
            RETURN
        END_IF
    END_IF
    CALL(evt_msg_print, 0, STRING("stg4_usu_109"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(nise_mario_talk)
    CALL(evt_msg_print, 0, STRING("stg4_usu_25_01"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(christine_talk)
    CALL(evt_msg_print, 0, STRING("stg4_usu_25_02"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(nokotaro_talk)
    CALL(evt_msg_print, 0, STRING("stg4_usu_25_03"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(cloud_talk)
    CALL(evt_msg_print, 0, STRING("stg4_usu_25_04"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(yoshi_talk)
    CALL(evt_msg_print, 0, STRING("stg4_usu_25_05"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_a_init)
    CALL(evt_npc_set_position, STRING("me"), -420, 90, 26)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_b_init)
    CALL(evt_npc_set_position, STRING("me"), -405, 60, 30)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_c_init)
    CALL(evt_npc_set_position, STRING("me"), 29, 120, -215)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_d_init)
    CALL(evt_npc_set_position, STRING("me"), 75, 110, -233)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_e_init)
    CALL(evt_npc_set_position, STRING("me"), 104, 110, -233)
    RETURN
EVT_END()

static EVT_BEGIN(urouro_move)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1073741824)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(50.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"村人Ａ"*/"\x91\xBA\x90\x6C\x82\x60", 1074267648, 0, (s32)villagerA_init, 0, (s32)villagerA_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"村人Ｂ"*/"\x91\xBA\x90\x6C\x82\x61",
    1074267648, 0, (s32)villagerB_init, 0, (s32)villagerB_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"村人Ｃ"*/"\x91\xBA\x90\x6C\x82\x62", 525824,
    0, (s32)villagerC_init, (s32)urouro_move, (s32)villagerC_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"村人Ｄ"*/"\x91\xBA\x90\x6C\x82\x63", 1074267648, 0,
    (s32)villagerD_init, 0, (s32)villagerD_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"村人Ｅ"*/"\x91\xBA\x90\x6C\x82\x64", 525824, 0, (s32)villagerE_init,
    (s32)urouro_move, (s32)villagerE_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"村人Ｋ"*/"\x91\xBA\x90\x6C\x82\x6A", 1074267648, 0, (s32)villagerK_init, 0,
    (s32)villagerK_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"村長"*/"\x91\xBA\x92\xB7", 1074267648, 0, (s32)village_chief_init, 0, (s32)village_chief_talk,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ビビアン"*/"\x83\x72\x83\x72\x83\x41\x83\x93", 1074267648, 0, (s32)vivian_init, 0, (s32)vivian_talk, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", 1074267648, 0, (s32)npc_init_evt, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ブタ村人Ａ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x60",
    525824, 0, (s32)villagerA_pig_init, (s32)urouro_move, (s32)villagerA_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ブタ村人Ｄ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x63", 525824,
    0, (s32)villagerD_pig_init, (s32)urouro_move, (s32)villagerD_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"ブタ村人Ｅ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x64", 525824, 0,
    (s32)villagerE_pig_init, (s32)urouro_move, (s32)villagerE_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ブタ村人Ｋ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x6A", 525824, 0, (s32)villagerK_pig_init,
    (s32)urouro_move, (s32)villagerK_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"ブタ村長"*/"\x83\x75\x83\x5E\x91\xBA\x92\xB7", 525824, 0, (s32)village_chief_pig_init, (s32)urouro_move,
    (s32)village_chief_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"カラスＡ"*/"\x83\x4A\x83\x89\x83\x58\x82\x60", 1073743360, 0, (s32)crow_a_init, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"カラスＢ"*/"\x83\x4A\x83\x89\x83\x58\x82\x61", 1073743360, 0, (s32)crow_b_init, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"カラスＣ"*/"\x83\x4A\x83\x89\x83\x58\x82\x62", 1073743360, 0, (s32)crow_c_init, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"カラスＤ"*/"\x83\x4A\x83\x89\x83\x58\x82\x63",
    1073743360, 0, (s32)crow_d_init, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"カラスＥ"*/"\x83\x4A\x83\x89\x83\x58\x82\x64", 1073743360,
    0, (s32)crow_e_init, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(usu00_stage4_coming_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam_letter_box_onoff, 1, 0)
    CALL(evt_npc_get_position, STRING("ブタ村人Ａ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("村人Ａ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ブタ村人Ａ"), 0, -2000, 0)
    CALL(evt_cam3d_evt_set, -255, 593, 704, -255, 497, 162, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_npc_set_tribe, STRING("村人Ａ"), STRING("ウスグラ村人音付き"))
    CALL(evt_npc_set_tribe, STRING("村長"), STRING("ウスグラ村長音付き"))
    CALL(evt_cam3d_evt_set, -255, 166, 704, -255, 71, 162, 5000, 0)
    WAIT_MS(5500)
    SET_VALUE(GF(0), 0)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(600)
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -255, 175, FLOAT(60.0f))
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -225, 175, FLOAT(60.0f))
    CALL(evt_party_set_dir, 0, 270, 300)
    WAIT_MS(300)
    CALL(evt_party_set_dir, 0, 90, 300)
    WAIT_MS(300)
    CALL(evt_party_set_dir, 0, 270, 300)
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(300)
    CALL(evt_party_set_dir, 0, 90, 300)
    WAIT_MS(300)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg4_usu_00_0"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg4_usu_00"), 0, STRING("村人Ａ"))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_cam3d_evt_set, -210, 100, 419, -210, 41, 185, 1000, 11)
    CALL(evt_npc_move_position, STRING("村人Ａ"), -175, 175, 1000, 0, 0)
    CALL(evt_npc_set_ry, STRING("村人Ａ"), 270)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg4_usu_01"), 0, STRING("村人Ａ"))
    WAIT_MS(100)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_5"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(400)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_02"), 0, STRING("村人Ａ"))
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg4_usu_03"))
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg4_usu_04"), 0, STRING("村人Ａ"))
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING("SFX_STG4_TEMPLE_BELL1"), 0)
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, 0, STRING("村人Ａ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_npc_reverse_ry, STRING("村人Ａ"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("村人Ａ"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_05"), 0, STRING("村人Ａ"))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("村人Ａ"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CHANGE_PIG1"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        ADD(LW(2), 20)
        CALL(evt_eff, 0, STRING("kemuri_test"), 7, LW(0), LW(1), LW(2), FLOAT(1.5f), 0, 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    CALL(evt_npc_get_reglid, STRING("ブタ村人Ａ"), LW(10))
    DELETE_EVENT(LW(10))
    CALL(evt_npc_set_position, STRING("ブタ村人Ａ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("村人Ａ"), 0, -2000, 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_npc_get_position, STRING("ブタ村人Ａ"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_msg_print, 0, STRING("stg4_usu_06"), 0, STRING("ブタ村人Ａ"))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("ブタ村人Ａ"), -197, 90, 0, FLOAT(40.0f), 0)
        CALL(evt_npc_move_position, STRING("ブタ村人Ａ"), -276, -14, 0, FLOAT(40.0f), 0)
        CALL(evt_npc_restart_regular_event, STRING("ブタ村人Ａ"))
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ａ"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｄ"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｋ"), 32)
    CALL(evt_msg_print_party, STRING("stg4_usu_07"))
    WAIT_MS(1000)
    CALL(evt_npc_get_position, STRING("村長"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("村長"), -40, 0, 184)
    CALL(evt_msg_print, 0, STRING("stg4_usu_08"), 0, STRING("村長"))
    CALL(evt_npc_move_position, STRING("村長"), -175, 175, 4000, 0, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg4_usu_09"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_10"), 0, STRING("村長"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_set_ry, STRING("村長"), 90)
        WAIT_MS(100)
        CALL(evt_npc_move_position, STRING("村長"), -77, -169, 5000, 0, 0)
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("村長"), -77, -190, 500, 0, 0)
        CALL(evt_npc_set_position, STRING("村長"), LW(0), LW(1), LW(2))
        CALL(evt_npc_set_ry, STRING("村長"), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(5100)
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
            CALL(evt_mapobj_rotate, 1, STRING("S__ie2_door"), 0, LW(0), 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        WAIT_MS(500)
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
            CALL(evt_mapobj_rotate, 1, STRING("S__ie2_door"), 0, LW(0), 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(600)
    CALL(evt_party_set_dir, 0, 270, 300)
    WAIT_MS(500)
    CALL(evt_party_set_dir, 0, 90, 300)
    WAIT_MS(500)
    CALL(evt_party_run, 0)
    CALL(evt_cam3d_evt_set, -428, 588, 1255, -15, -195, -327, 5000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_telop_entry, 7)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -215, 137, FLOAT(60.0f))
    CALL(evt_mario_mov_pos2, -95, -105, FLOAT(60.0f))
    CALL(evt_cam3d_evt_set, -45, 132, 111, -45, 49, -200, 0, 11)
    CALL(evt_npc_set_position, STRING("村長"), 5, 0, -340)
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -98, -131, FLOAT(60.0f))
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -79, -180, FLOAT(60.0f))
    CALL(evt_party_run, 0)
    SET_VALUE(LW(0), PTR(door_2))
    SET_VALUE(LW(15), 0)
    CALL_CHILD(PTR(evt_door_open))
    CALL(evt_cam3d_evt_set, -45, 132, 111, -45, 49, -361, 1000, 11)
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -80, -320, FLOAT(60.0f))
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -55, -335, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_msg_print, 0, STRING("stg4_usu_11"), 0, STRING("村長"))
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg4_usu_12"), 0, STRING("村長"))
    CALL(evt_cam3d_evt_set, -70, 100, -16, -70, 39, -361, 400, 11)
    WAIT_MS(400)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg4_usu_13"))
    CALL(evt_cam3d_evt_set, -40, 80, -90, -40, 33, -361, 900, 11)
    WAIT_MS(900)
    CALL(evt_msg_print, 0, STRING("stg4_usu_14"), 0, STRING("村長"))
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg4_usu_15"), 0, STRING("村長"))
    WAIT_MS(300)
    CALL(evt_party_move_pos2, 0, -60, -305, FLOAT(60.0f))
    WAIT_MS(300)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg4_usu_16"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_17"), 0, STRING("村長"))
    WAIT_MS(250)
    CALL(evt_msg_print_party, STRING("stg4_usu_18"))
    WAIT_MS(250)
    CALL(evt_msg_print, 0, STRING("stg4_usu_19"), 0, STRING("村長"))
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    SET_VALUE(GSW(0), 178)
    CALL(evt_snd_bgm_scope, 0, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("ブタ村人Ａ"), 32)
    CALL(evt_npc_flag_onoff, 0, STRING("ブタ村人Ｄ"), 32)
    CALL(evt_npc_flag_onoff, 0, STRING("ブタ村人Ｋ"), 32)
    RETURN
EVT_END()

EVT_BEGIN(usu00_3witch_init)
    CALL(evt_npc_entry, STRING("マリリン"), STRING("c_maririn"))
    CALL(evt_npc_entry, STRING("マジョリン"), STRING("c_majyorin"))
    CALL(evt_npc_entry, STRING("ランペル"), STRING("c_ranpel"))
    CALL(evt_npc_set_tribe, STRING("マリリン"), STRING("マリリン"))
    CALL(evt_npc_set_tribe, STRING("マジョリン"), STRING("マジョリン"))
    CALL(evt_npc_set_tribe, STRING("ランペル"), STRING("ランペル"))
    CALL(evt_npc_flag_onoff, 1, STRING("マリリン"), 1074267648)
    CALL(evt_npc_flag_onoff, 1, STRING("マジョリン"), 1074267648)
    CALL(evt_npc_flag_onoff, 1, STRING("ランペル"), 1074267648)
    RETURN
EVT_END()

EVT_BEGIN(usu00_3witch_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_cam3d_evt_set, -25, 495, 530, -25, 400, -62, 0, 11)
    CALL(evt_npc_set_position, STRING("ビビアン"), -71, 0, 179)
    CALL(evt_npc_set_position, STRING("マリリン"), 23, 0, 159)
    CALL(evt_npc_set_position, STRING("マジョリン"), -9, 0, 198)
    CALL(evt_npc_set_ry, STRING("ビビアン"), 90)
    CALL(evt_npc_set_ry, STRING("マリリン"), 270)
    CALL(evt_npc_set_ry, STRING("マジョリン"), 270)
    CALL(evt_npc_set_position, STRING("ランペル"), 0, -1000, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg4_usu_97"), 0, STRING("マジョリン"))
    CALL(evt_cam3d_evt_set, -25, 100, 530, -25, 5, -62, 3000, 11)
    WAIT_MS(3500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_97_01"), 0, STRING("マジョリン"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_98"), 0, STRING("マリリン"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_99"), 0, STRING("マジョリン"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_100"), 0, STRING("ビビアン"))
    CALL(evt_npc_set_tribe, STRING("ビビアン"), STRING("ビビアン困る"))
    CALL(evt_npc_set_autotalkpose, STRING("ビビアン"), STRING("PTR_S_4"), STRING("PTR_T_5"))
    CALL(evt_cam3d_evt_set, -10, 60, 382, -10, -15, -62, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg4_usu_101"), 0, STRING("マジョリン"))
    CALL(evt_cam3d_evt_set, -68, 68, 382, -68, -7, -62, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg4_usu_102"), 0, STRING("ビビアン"))
    CALL(evt_cam3d_evt_set, -10, 60, 382, -10, -15, -62, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg4_usu_103"), 0, STRING("マジョリン"))
    CALL(evt_cam3d_evt_set, -68, 68, 382, -68, -7, -62, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg4_usu_103_02"), 0, STRING("ビビアン"))
    CALL(evt_cam3d_evt_set, -25, 100, 530, -25, 5, -62, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg4_usu_104"), 0, STRING("マジョリン"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_105"), 0, STRING("ビビアン"))
    CALL(evt_cam3d_evt_set, 0, 85, 455, 0, -5, -62, 1200, 11)
    WAIT_MS(1200)
    CALL(evt_msg_print, 0, STRING("stg4_usu_106"), 0, STRING("マジョリン"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_107"), 0, STRING("マリリン"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_majo_disp_off, STRING("マジョリン"))
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_npc_majo_disp_off, STRING("マリリン"))
    WAIT_MS(1000)
    SET_VALUE(GSW(0), 202)
    CALL(evt_bero_mapchange, STRING("gra_06"), STRING("n_bero"))
    RETURN
EVT_END()

EVT_BEGIN(gra00_2witch_find_ranpel_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_pos, -500, 0, 0)
    CALL(evt_party_set_pos, 0, -500, 0, 0)
    CALL(evt_cam3d_evt_set, 10, 100, 730, 10, 0, 88, 0, 11)
    CALL(evt_npc_set_position, STRING("ランペル"), 149, 0, 385)
    CALL(evt_npc_set_position, STRING("マリリン"), -9, 0, 348)
    CALL(evt_npc_set_position, STRING("マジョリン"), 27, 0, 348)
    CALL(evt_npc_set_ry, STRING("ランペル"), 270)
    CALL(evt_npc_set_ry, STRING("マリリン"), 90)
    CALL(evt_npc_set_ry, STRING("マジョリン"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("ランペル"), 1074266144)
    CALL(evt_npc_flag_onoff, 1, STRING("マリリン"), 1074266144)
    CALL(evt_npc_flag_onoff, 1, STRING("マジョリン"), 1074266144)
    CALL(evt_npc_flag_onoff, 1, STRING("マリリン"), 32768)
    WAIT_FRAMES(1)
    CALL(evt_npc_flag_onoff, 0, STRING("マリリン"), 32768)
    CALL(evt_seq_wait, 2)
    CALL(evt_fade_end_wait)
    CALL(evt_msg_print, 0, STRING("stg4_usu_151"), 0, STRING("マジョリン"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_152"), 0, STRING("マリリン"))
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("ランペル"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_LANPEL_ESCAPE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_set_anim, STRING("ランペル"), STRING("R_2"))
        CALL(evt_npc_flag_onoff, 0, STRING("ランペル"), 1024)
        CALL(evt_npc_move_position, STRING("ランペル"), -131, 385, 1200, 0, 0)
    END_INLINE_EVENT
    WAIT_MS(400)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("マジョリン"), 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("マリリン"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(250)
    CALL(evt_npc_set_ry, STRING("マリリン"), 270)
    WAIT_MS(950)
    SET_VALUE(GSW(0), 214)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 55, 0, 54, 0)
    CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    RETURN
EVT_END()

EVT_BEGIN(usu00_vivian_cry_event)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING("ビビアン"), STRING("PTR_S_3"), STRING("PTR_T_3"))
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -71, 68, 588, -71, -8, 88, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg4_usu_108"), 0, STRING("ビビアン"))
    CALL(evt_cam3d_evt_off, 0, 11)
    SET_VALUE(GSW(0), 204)
    CALL(evt_npc_change_interrupt, STRING("ビビアン"), 1, PTR(urouro_move))
    CALL(evt_npc_restart_regular_event, STRING("ビビアン"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(usu00_vivian_joinup_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ビビアン"), 32)
    CALL(evt_msg_print, 0, STRING("stg4_usu_110"), 0, STRING("ビビアン"))
    CALL(evt_npc_get_position, STRING("ビビアン"), LW(0), LW(1), LW(2))
    ADD(LW(0), -40)
    CALL(evt_mario_mov_pos, LW(0), LW(2), 500)
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_npc_set_ry, STRING("ビビアン"), 270)
    CALL(evt_npc_flag_onoff, 0, STRING("ビビアン"), 32)
    CALL(evt_cam3d_evt_set_rel, 0, 52, 296, 20, 43, 26, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING("M_C_3"))
    CALL(evt_npc_get_position, STRING("ビビアン"), LW(0), LW(1), LW(2))
    ADD(LW(0), -20)
    CALL(evt_item_entry, STRING("ichikorori"), 67, LW(0), 10, LW(2), 17, -1, 0)
    WAIT_MS(1000)
    CALL(evt_item_delete, STRING("ichikorori"))
    CALL(evt_mario_dump_item, 67)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_111"), 0, STRING("ビビアン"))
    WAIT_MS(500)
    CALL(evt_npc_set_ry, STRING("ビビアン"), 90)
    CALL(evt_npc_get_position, STRING("ビビアン"), LW(0), LW(1), LW(2))
    ADD(LW(0), 30)
    ADD(LW(2), -1)
    CALL(evt_item_entry, STRING("shine"), 67, LW(0), LW(1), LW(2), 17, -1, 0)
    WAIT_MS(700)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ビビアン"), 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_npc_get_position, STRING("ビビアン"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position_nohit, STRING("ビビアン"), LW(0), LW(1), LW(2), 200, FLOAT(15.0f))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg4_usu_112"), 0, STRING("ビビアン"))
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING("M_N_H"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 200, 1, -1000)
    WAIT_MS(700)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_npc_set_ry, STRING("ビビアン"), 270)
    CALL(evt_msg_print, 0, STRING("stg4_usu_113"), 0, STRING("ビビアン"))
    CALL(evt_msg_select, 0, STRING("stg4_usu_113_select"))
    CALL(evt_msg_continue)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(500)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_114"), 0, STRING("ビビアン"))
        CALL(evt_mario_set_pose, STRING("M_N_1"))
        WAIT_MS(1000)
        ELSE
        CALL(evt_msg_print, 0, STRING("stg4_usu_115"), 0, STRING("ビビアン"))
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(500)
    END_IF
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_item_get_position, STRING("shine"), LW(0), LW(1), LW(2))
    LOOP(10)
        CALL(evt_item_set_position, STRING("shine"), LW(0), LW(1), LW(2))
        WAIT_FRAMES(4)
        CALL(evt_item_set_position, STRING("shine"), 0, -1000, 0)
        WAIT_FRAMES(2)
    END_LOOP
    CALL(evt_item_delete, STRING("shine"))
    CALL(evt_npc_set_tribe, STRING("ビビアン"), STRING("ビビアン"))
    CALL(evt_npc_set_autotalkpose, STRING("ビビアン"), STRING("PTR_S_1"), STRING("PTR_T_1"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_116"), 0, STRING("ビビアン"))
    CALL(evt_mario_set_pose, STRING("M_I_G"))
    WAIT_MS(750)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_117"), 0, STRING("ビビアン"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_118"), 0, STRING("ビビアン"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -84, 190, 1146, -41, 110, 21, 0, 0)
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_T_1"))
    WAIT_MS(3000)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_S_1"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_set_rel, 0, 52, 296, 20, 43, 26, 0, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_119"), 0, STRING("ビビアン"))
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg4_usu_120"), 0, STRING("ビビアン"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_B"))
    WAIT_MS(700)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg4_usu_121"), 0, STRING("ビビアン"))
    CALL(evt_npc_get_position, STRING("ビビアン"), LW(0), LW(1), LW(2))
    ADD(LW(0), -15)
    CALL(evt_npc_flag_onoff, 1, STRING("ビビアン"), 32)
    CALL(evt_npc_move_position, STRING("ビビアン"), LW(0), LW(2), 0, 60, 0)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        ADD(LW(0), -10)
        ADD(LW(1), 50)
        ADD(LW(2), 60)
        CALL(evt_eff64, 0, STRING("recover_heart_n64"), 2, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VIVIAN_KISS2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_get_position, STRING("ビビアン"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VIVIAN_KISS1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_A4_2"))
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(400)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_A4_1"))
    CALL(evt_npc_flag_onoff, 0, STRING("ビビアン"), 1024)
    CALL(evt_npc_status_onoff, 0, STRING("ビビアン"), 2)
    SUBTRACT(LW(0), -15)
    CALL(evt_npc_move_position, STRING("ビビアン"), LW(0), LW(2), 0, 20, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg4_usu_121_01"), 0, STRING("ビビアン"))
    CALL(evt_cam3d_evt_set_npc_rel, STRING("ビビアン"), 0, 50, 290, 0, 45, 14, 800, 11)
    WAIT_MS(800)
    SET_VALUE(LW(8), STRING("ビビアン"))
    SET_VALUE(LW(9), 6)
    CALL_CHILD(PTR(all_party_lecture_29_data_10988))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
    CALL(evt_msg_print_party, STRING("stg4_usu_123"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg4_usu_124"))
    CALL(evt_cam3d_evt_off, 1000, 11)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_USU1"))
    WAIT_MS(1000)
    SET_VALUE(GSW(0), 206)
    SET_VALUE(GSWF(2081), 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

static EVT_BEGIN(cam_up)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_get_pos, 4, LW(0), LW(1), LW(2))
        CALL(evt_cam_get_at, 4, LW(3), LW(4), LW(5))
        ADD(LW(1), 85)
        ADD(LW(4), 85)
        CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 500, 11)
    END_INLINE_EVENT
    WAIT_MS(600)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(cam_down)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    RETURN
EVT_END()

EVT_BEGIN(usu00_check_vivian)
    LABEL(0)
    CALL(evt_mario_get_party, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 6)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_party_get_status, 6, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(GW(0), 0)
        SET_VALUE(GW(1), 0)
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(usu00_crowAB_talk_event)
    SET_VALUE(LW(15), 0)
    LABEL(0)
    IF_INT_NOT_EQUAL(GW(0), 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("カラスＢ"), LW(3), LW(4), LW(5))
    CALL(evt_mario_get_mode, LW(7))
    IF_INT_EQUAL(LW(7), 2)
        SET_VALUE(LW(8), 60)
        ELSE
        SET_VALUE(LW(8), 20)
    END_IF
    CALL(evt_sub_area_check, 1, LW(3), LW(5), LW(8), LW(0), LW(2), LW(6))
    IF_INT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_balloon_tenten)
            SET_VALUE(LW(15), 1)
        END_IF
        ELSE
        IF_INT_EQUAL(LW(15), 1)
            CALL(evt_mario_balloon_off)
            SET_VALUE(LW(15), 0)
        END_IF
    END_IF
    IF_INT_EQUAL(LW(15), 1)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        CALL(evt_mario_party_use_check, LW(1))
        IF_INT_EQUAL(LW(1), 0)
            IF_BITS_SET(LW(0), 256)
                CALL(evt_mario_balloon_off)
                SET_VALUE(LW(15), 0)
                CALL(evt_mario_key_onoff, 0)
                CALL(evt_party_cont_onoff, 0, 0)
                CALL(mainwindow_opendisable)
                CALL_CHILD(PTR(cam_up))
                CALL(evt_npc_get_position, STRING("カラスＢ"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
                IF_INT_EQUAL(LW(7), 2)
                    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_7_1"), 0, STRING("カラスＢ"))
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg4_jin_152"), 0, STRING("カラスＢ"))
                END_IF
                CALL_CHILD(PTR(cam_down))
                CALL(evt_mario_key_onoff, 1)
                CALL(evt_party_cont_onoff, 0, 1)
                CALL(mainwindow_openenable)
            END_IF
        END_IF
    END_IF
    CALL(evt_mario_get_party, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 6)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_party_get_status, 6, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    IF_INT_EQUAL(LW(15), 1)
        CALL(evt_mario_balloon_off)
        SET_VALUE(LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(GSW(0), 206)
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_party_cont_onoff, 0, 0)
            CALL(mainwindow_opendisable)
            CALL_CHILD(PTR(cam_up))
            WAIT_MS(1000)
            CALL(evt_npc_get_position, STRING("カラスＢ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
            SWITCH(GSW(0))
                CASE_LESS(210)
                CALL(evt_msg_print, 0, STRING("stg4_usu_125"), 0, STRING("カラスＡ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_126"), 0, STRING("カラスＢ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_127"), 0, STRING("カラスＡ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_128"), 0, STRING("カラスＢ"))
                CASE_LESS(222)
                CALL(evt_msg_print, 0, STRING("stg4_usu_129"), 0, STRING("カラスＡ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_130"), 0, STRING("カラスＢ"))
                CASE_LESS_OR_EQUAL(402)
                CALL(evt_msg_print, 0, STRING("stg4_usu_130_1"), 0, STRING("カラスＡ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_130_2"), 0, STRING("カラスＢ"))
                CASE_DEFAULT
                CALL(evt_msg_print, 0, STRING("stg4_usu_130_2_1"), 0, STRING("カラスＡ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_130_2_2"), 0, STRING("カラスＢ"))
            END_SWITCH
            CALL_CHILD(PTR(cam_down))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(mainwindow_openenable)
            SET_VALUE(GW(0), 1)
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(usu00_crowCDE_talk_event)
    SET_VALUE(LW(15), 0)
    LABEL(0)
    IF_INT_NOT_EQUAL(GW(1), 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("カラスＤ"), LW(3), LW(4), LW(5))
    CALL(evt_sub_area_check, 1, LW(3), LW(5), 60, LW(0), LW(2), LW(6))
    IF_INT_LESS_OR_EQUAL(LW(2), -250)
        SET_VALUE(LW(6), 0)
    END_IF
    IF_INT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_balloon_tenten)
            SET_VALUE(LW(15), 1)
        END_IF
        ELSE
        IF_INT_EQUAL(LW(15), 1)
            CALL(evt_mario_balloon_off)
            SET_VALUE(LW(15), 0)
        END_IF
    END_IF
    IF_INT_EQUAL(LW(15), 1)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        CALL(evt_mario_party_use_check, LW(1))
        IF_INT_EQUAL(LW(1), 0)
            IF_BITS_SET(LW(0), 256)
                CALL(evt_mario_balloon_off)
                SET_VALUE(LW(15), 0)
                CALL(evt_mario_key_onoff, 0)
                CALL(evt_party_cont_onoff, 0, 0)
                CALL(mainwindow_opendisable)
                CALL_CHILD(PTR(cam_up))
                CALL(evt_npc_get_position, STRING("カラスＤ"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
                CALL(evt_mario_get_mode, LW(7))
                IF_INT_EQUAL(LW(7), 2)
                    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_7_2"), 0, STRING("カラスＤ"))
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg4_jin_152"), 0, STRING("カラスＤ"))
                END_IF
                CALL_CHILD(PTR(cam_down))
                CALL(evt_mario_key_onoff, 1)
                CALL(evt_party_cont_onoff, 0, 1)
                CALL(mainwindow_openenable)
            END_IF
        END_IF
    END_IF
    CALL(evt_mario_get_party, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 6)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_party_get_status, 6, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    IF_INT_EQUAL(LW(15), 1)
        CALL(evt_mario_balloon_off)
        SET_VALUE(LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(GSW(0), 206)
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_party_cont_onoff, 0, 0)
            CALL(mainwindow_opendisable)
            CALL_CHILD(PTR(cam_up))
            WAIT_MS(1000)
            CALL(evt_npc_get_position, STRING("カラスＤ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
            SWITCH(GSW(0))
                CASE_LESS(210)
                CALL(evt_msg_print, 0, STRING("stg4_usu_131"), 0, STRING("カラスＣ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_132"), 0, STRING("カラスＤ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_133"), 0, STRING("カラスＥ"))
                CASE_LESS(222)
                CALL(evt_msg_print, 0, STRING("stg4_usu_134"), 0, STRING("カラスＣ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_135"), 0, STRING("カラスＤ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_136"), 0, STRING("カラスＥ"))
                CASE_LESS_OR_EQUAL(402)
                CALL(evt_msg_print, 0, STRING("stg4_usu_136_1"), 0, STRING("カラスＣ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_136_2"), 0, STRING("カラスＤ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_136_3"), 0, STRING("カラスＥ"))
                CASE_DEFAULT
                CALL(evt_msg_print, 0, STRING("stg4_usu_136_3_1"), 0, STRING("カラスＣ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_136_3_2"), 0, STRING("カラスＤ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_136_3_3"), 0, STRING("カラスＥ"))
            END_SWITCH
            CALL_CHILD(PTR(cam_down))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(mainwindow_openenable)
            SET_VALUE(GW(1), 1)
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(chief_pig_event)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_get_position, STRING("ブタ村長"), LW(3), LW(4), LW(5))
        CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(6))
        IF_INT_LESS_OR_EQUAL(LW(6), 100)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_yoshi_ride, 0, 0)
    CALL(evt_mario_wait_rideon)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_dir_npc, STRING("ブタ村長"))
    CALL(evt_party_set_dir_npc, 0, STRING("ブタ村長"))
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg4_usu_21"))
    SET_VALUE(GSW(0), 180)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 kino_dt[] = {
    176, 1132068864, 1098907648, -1013579776, 10, 1138196480, 1098907648, -1019019264,
    1137082368, 0, -1020788736, 1124532224, 1123287040, -1020592128, 1136066560, 1110966272,
    -1016856576, -1035468800, 1135378432, 0, -1018167296, (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", (s32)"usugurayado_00", (s32)"usugurayado_01",
    (s32)"usugurayado_02", (s32)"usugurayado_03", (s32)"usugurayado_04", (s32)"usugurayado_05", (s32)"usugurayado_06", (s32)"usugurayado_07", (s32)"usugurayado_08", (s32)"usugurayado_09",
    (s32)"usugurayado_10", (s32)"usugurayado_11", (s32)"usugurayado_12", (s32)"usugurayado_13", 0, 0,
};

static __declspec(section ".data") s32 yado_npc[] = {
    (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", 0,
};

__declspec(section ".data") s32 yado_mobj[] = {
    (s32)"pblk00", 0,
};

__declspec(section ".data") s32 village_chief_npc[] = {
    (s32)/*"村長"*/"\x91\xBA\x92\xB7", (s32)/*"ブタ村長"*/"\x83\x75\x83\x5E\x91\xBA\x92\xB7", (s32)/*"にせマリオ"*/"\x82\xC9\x82\xB9\x83\x7D\x83\x8A\x83\x49", (s32)/*"クリスチーヌ"*/"\x83\x4E\x83\x8A\x83\x58\x83\x60\x81\x5B\x83\x6B", (s32)/*"ノコタロウ"*/"\x83\x6D\x83\x52\x83\x5E\x83\x8D\x83\x45", (s32)/*"クラウダ"*/"\x83\x4E\x83\x89\x83\x45\x83\x5F", (s32)/*"チビヨッシー"*/"\x83\x60\x83\x72\x83\x88\x83\x62\x83\x56\x81\x5B", 0,
};

static __declspec(section ".data") EVT_BEGIN(evt_door_1_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie1_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_door_1_2)
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_1)
    SET_FLOAT_VALUE(LW(1), LW(0))
    MULTIPLY_FLOAT(LW(1), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("ie1_kai1"), LW(1), 0, 0)
    WAIT_FRAMES(10)
    SET_FLOAT_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("ie1_kai2"), LW(2), 0, 0)
    RETURN
EVT_END()

__declspec(section ".data") s32 door_1_npc[] = {
    (s32)/*"村人Ｂ"*/"\x91\xBA\x90\x6C\x82\x61", 0,
};

static __declspec(section ".data") EVT_BEGIN(door_1_open)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

static EVT_BEGIN(door_1_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

static s32 door_1[] = {
    0, 3, 2, (s32)"S_ie1_door", (s32)"A_ie1door_u", (s32)"A_ie1door", (s32)"S_ie1", 0,
    (s32)"S_ie1_naka", 0, (s32)evt_door_1_1, 0, (s32)evt_wall_1, (s32)door_1_npc, 0, 0,
    (s32)door_1_open, (s32)door_1_close,
};

__declspec(section ".data") EVT_BEGIN(evt_door_2_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING("S__ie2_door"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_door_2_2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S__ie2_door"), LW(0), 0, 0)
    ADD(GW(2), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_2)
    IF_INT_EQUAL(LW(1), LW(0))
        SET_FLOAT_VALUE(LW(1), LW(0))
        MULTIPLY_FLOAT(LW(1), FLOAT(-0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai1"), LW(1), 0, 0)
        WAIT_FRAMES(5)
        SET_FLOAT_VALUE(LW(2), LW(0))
        MULTIPLY_FLOAT(LW(2), FLOAT(0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai2"), LW(2), 0, 0)
        WAIT_FRAMES(5)
        SET_FLOAT_VALUE(LW(3), LW(0))
        MULTIPLY_FLOAT(LW(3), FLOAT(-0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai3"), 0, 0, LW(3))
        WAIT_FRAMES(10)
        SET_FLOAT_VALUE(LW(4), LW(0))
        MULTIPLY_FLOAT(LW(4), FLOAT(0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai4"), LW(4), 0, 0)
        ELSE
        SET_FLOAT_VALUE(LW(4), LW(0))
        MULTIPLY_FLOAT(LW(4), FLOAT(0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai4"), LW(4), 0, 0)
        WAIT_FRAMES(10)
        SET_FLOAT_VALUE(LW(3), LW(0))
        MULTIPLY_FLOAT(LW(3), FLOAT(-0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai3"), 0, 0, LW(3))
        WAIT_FRAMES(5)
        SET_FLOAT_VALUE(LW(2), LW(0))
        MULTIPLY_FLOAT(LW(2), FLOAT(0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai2"), LW(2), 0, 0)
        WAIT_FRAMES(5)
        SET_FLOAT_VALUE(LW(1), LW(0))
        MULTIPLY_FLOAT(LW(1), FLOAT(-0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("ie2_kai1"), LW(1), 0, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_door2_chk)
    SWITCH(GSW(0))
        CASE_BETWEEN(202, 211)
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_gochisou"), 1)
        CALL(evt_hitobj_onoff, STRING("A_gochisou"), 1, 0)
    END_SWITCH
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

EVT_BEGIN(evt_door2_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

static s32 door_2[] = {
    0, 3, 2, (s32)"S__ie2_door", (s32)"A_ie2door_u", (s32)"A_ie2door", (s32)"S_ie2", 0,
    (s32)"S_ie2_naka", 0, (s32)evt_door_2_1, (s32)evt_door_2_2, (s32)evt_wall_2, (s32)village_chief_npc, 0, 0,
    (s32)evt_door2_chk, (s32)evt_door2_close,
};

static __declspec(section ".data") EVT_BEGIN(evt_door_3_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie3_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_door_3_2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie3_door"), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_3)
    SET_FLOAT_VALUE(LW(1), LW(0))
    MULTIPLY_FLOAT(LW(1), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("ie3_kai1"), LW(1), 0, 0)
    WAIT_FRAMES(10)
    SET_FLOAT_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("ie3_kai2"), LW(2), 0, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(door_3_open)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

static EVT_BEGIN(door_3_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

static s32 door_3[] = {
    0, 3, 2, (s32)"S_ie3_door", (s32)"A_ie3door_u", (s32)"A_ie3door", (s32)"S_ie3", 0,
    (s32)"S_ie3_naka", 0, (s32)evt_door_3_1, (s32)evt_door_3_2, (s32)evt_wall_3, (s32)yado_npc, (s32)yado_mobj, 0,
    (s32)door_3_open, (s32)door_3_close,
};

EVT_BEGIN(dokan_1_evt)
    IF_INT_LESS(GSW(0), 178)
        CALL(evt_mario_dispflag_onoff, 1, 1)
        CALL(evt_party_dispflg_onoff, 0, 1, 1)
        SET_VALUE(GF(0), 1)
        WAIT_WHILE(GF(0))
        CALL(evt_mario_dispflag_onoff, 0, 1)
        CALL(evt_party_dispflg_onoff, 0, 1, 0)
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"dokan_1", 131072, 9, 100000, 0, 0, -1, (s32)dokan_1_evt,
    6, 0, (s32)"tik_08", (s32)"dokan", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"usu_01", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(oshimodo_event)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_bero_exec_wait, 65536)
        CALL(evt_msg_toge, 1, 0, 0, 0)
        CALL(evt_msg_print, 0, STRING("stg4_jin_151"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_oshimodo[] = {
    (s32)"dokan_1", 131072, 9, 100000, 0, 0, -1, 0,
    6, (s32)oshimodo_event, 0, (s32)"dokan_1", 65537, 0, 0,
};

EVT_BEGIN(koopa_dokan_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_2"), 0, STRING("mario"))
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
        SET_VALUE(LW(0), STRING("dokan_1"))
        CALL_CHILD(PTR(bero_case_switch_off))
        LOOP(0)
            CALL(evt_mario_get_motion, LW(0))
            IF_INT_EQUAL(LW(0), 3)
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(LW(0), 10)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        DEBUG_PUT_MSG(STRING("おりた"))
        SET_VALUE(LW(0), STRING("dokan_1"))
        CALL_CHILD(PTR(bero_case_switch_on))
    END_INLINE_EVENT
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

s32 bero_koopa_dokan[] = {
    (s32)"dokan_1", 131072, 9, 100000, 0, 0, -1, 0,
    6, (s32)koopa_dokan_evt, 0, 0, 65537, 0, 0,
};

EVT_BEGIN(door_ie1_koopa_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mapobj_get_position, STRING("S_ie1_door"), LW(0), LW(1), LW(2))
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_4"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(door_ie2_koopa_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mapobj_get_position, STRING("S__ie2_door"), LW(0), LW(1), LW(2))
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_5"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(door_ie3_koopa_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mapobj_get_position, STRING("S_ie3_door"), LW(0), LW(1), LW(2))
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_6"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_ki_1)
    CALL(evt_npc_set_anim, STRING("カラスＡ"), STRING("A_1"))
    CALL(evt_npc_set_anim, STRING("カラスＢ"), STRING("A_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("カラスＡ"), STRING("S_1"))
    CALL(evt_npc_set_anim, STRING("カラスＢ"), STRING("S_1"))
    RETURN
EVT_END()

static EVT_BEGIN(evt_ki_2)
    CALL(evt_npc_set_anim, STRING("カラスＣ"), STRING("A_1"))
    CALL(evt_npc_set_anim, STRING("カラスＤ"), STRING("A_1"))
    CALL(evt_npc_set_anim, STRING("カラスＥ"), STRING("A_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("カラスＣ"), STRING("S_1"))
    CALL(evt_npc_set_anim, STRING("カラスＤ"), STRING("S_1"))
    CALL(evt_npc_set_anim, STRING("カラスＥ"), STRING("S_1"))
    RETURN
EVT_END()

static s32 tree_tbl[] = {
    2, (s32)"A_ki_1", (s32)"S_usu00_ki01", 0, 0, (s32)evt_ki_1, 2, (s32)"A_ki_2",
    (s32)"S_usu00_ki02", 0, 0, (s32)evt_ki_2, 2, (s32)"A_ki_3", (s32)"S_usu00_ki03", 0,
    0, 0, 7, 0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(usu_00_tree_init)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    RETURN
EVT_END()

EVT_BEGIN(kusa_01_evt)
    IF_INT_EQUAL(GSW(0), 266)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
        CALL(evt_msg_print, 0, STRING("kpa_stg5_009_7"), PTR(kpa_stg5_009_7_cb), STRING("mario"))
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_kusa_04)
    IF_INT_EQUAL(GF(1), 1)
        RETURN
    END_IF
    CALL(evt_item_delete_check, STRING("item_kusa_04"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_04"), 125, 130, 0, 455, 4, GSWF(5628), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_kusa_06)
    IF_INT_EQUAL(GF(1), 1)
        RETURN
    END_IF
    CALL(evt_item_delete_check, STRING("item_kusa_06"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_06"), 121, 330, 0, 275, 4, GSWF(1933), 0)
    END_IF
    RETURN
EVT_END()

static s32 kusa_tbl[] = {
    2, (s32)"A_kusa_01", (s32)"S_kusa_01", (s32)kusa_01_evt, 2, (s32)"A_kusa_02", (s32)"S_kusa_02", 0,
    2, (s32)"A_kusa_03", (s32)"S_kusa_03", 0, 2, (s32)"A_kusa_04", (s32)"S_kusa_04", (s32)evt_kusa_04,
    2, (s32)"A_kusa_05", (s32)"S_kusa_05", 0, 2, (s32)"A_kusa_06", (s32)"S_kusa_06", (s32)evt_kusa_06,
    2, (s32)"A_kusa_07", (s32)"S_kusa_07", 0, 2, (s32)"A_kusa_08", (s32)"S_kusa_08", 0,
    2, (s32)"A_kusa_09", (s32)"S_kusa_09", 0, 2, (s32)"A_kusa_10", (s32)"S_kusa_010", 0,
    2, (s32)"A_kusa_11", (s32)"S_kusa_011", 0, 2, (s32)"A_kusa_12", (s32)"S_kusa_012", 0,
    2, (s32)"A_kusa_13", (s32)"S_kusa_013", 0, 2, (s32)"A_kusa_14", (s32)"S_kusa_014", 0,
    2, (s32)"A_kusa_15", (s32)"S_kusa_015", 0, 2, (s32)"A_kusa_16", (s32)"S_kusa_016", 0,
    2, (s32)"A_kusa_17", (s32)"S_kusa_017", 0, 2, (s32)"A_kusa_18", (s32)"S_kusa_018", 0,
    2, (s32)"A_kusa_19", (s32)"S_kusa_019", 0, 2, (s32)"A_kusa_20", (s32)"S_kusa_020", 0,
    4, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(usu_00_kusa_init)
    SET_VALUE(LW(0), PTR(kusa_tbl))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_ichikorori_ball_get)
    SET_VALUE(GSW(0), 205)
    RETURN
EVT_END()

EVT_BEGIN(usu_00_touch_ichikorori_ball)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 204)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), -260)
        SET_VALUE(LW(4), 0)
        SET_VALUE(LW(5), 325)
        IF_INT_LESS(LW(2), LW(5))
            ADD(LW(5), 20)
            ELSE
            ADD(LW(5), -20)
        END_IF
        CALL(evt_sub_get_dir, LW(0), LW(2), LW(3), LW(5), LW(6))
        CALL(evt_item_entry, STRING("ichikorori_ball"), 67, LW(3), LW(4), LW(5), 2, -1, PTR(evt_ichikorori_ball_get))
        CALL(evt_item_set_move_dir_speed, STRING("ichikorori_ball"), LW(6), FLOAT(90.0f))
        CALL(evt_item_set_gravity, STRING("ichikorori_ball"), FLOAT(1.0f))
        CALL(evt_item_set_bound_rate, STRING("ichikorori_ball"), FLOAT(0.5996094f))
        CALL(evt_item_set_jump_power, STRING("ichikorori_ball"), FLOAT(500.0f))
        CALL(evt_item_status_on, STRING("ichikorori_ball"), 16)
        CALL(evt_exit_case_evt)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") s32 booboo_name[] = {
    (s32)/*"ブタ村人Ａ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x60", 33619968, (s32)/*"ブタ村人Ｄ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x63", 65536, (s32)/*"ブタ村人Ｅ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x64", 100728832, (s32)/*"ブタ村人Ｋ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x6A", 83951616,
    (s32)/*"ブタ村長"*/"\x83\x75\x83\x5E\x91\xBA\x92\xB7", 150994944,
};

s32 kpaSen_ext_entry_data[] = {
    (s32)"c_zako_n", (s32)"S_1", 0, (s32)"c_zako_n", (s32)"S_1", 1090519040, (s32)"c_zako_n", (s32)"S_1",
    1098907648, (s32)"c_zako_n", (s32)"S_1", 1103101952, (s32)"c_zako_n", (s32)"S_1", 1107296256, (s32)"c_zako_n",
    (s32)"S_1", 1109393408, (s32)"c_zako_n", (s32)"R_1", 0, (s32)"c_zako_n", (s32)"R_1", 1088421888,
    (s32)"c_zako_n", (s32)"R_1", 1096810496, (s32)"c_togenoko", (s32)"S_1", 0, (s32)"c_togenoko", (s32)"S_1",
    1090519040, (s32)"c_togenoko", (s32)"S_1", 1098907648, (s32)"c_togenoko", (s32)"S_1", 1103101952, (s32)"c_togenoko",
    (s32)"S_1", 1107296256, (s32)"c_togenoko", (s32)"S_1", 1109393408, (s32)"c_togenoko", (s32)"R_1", 0,
    (s32)"c_togenoko", (s32)"R_1", 1088421888, (s32)"c_togenoko", (s32)"R_1", 1096810496, (s32)"c_burosu_h", (s32)"BRO_S_1",
    0, (s32)"c_burosu_h", (s32)"BRO_S_1", 1090519040, (s32)"c_burosu_h", (s32)"BRO_S_1", 1098907648, (s32)"c_burosu_h",
    (s32)"BRO_S_1", 1103101952, (s32)"c_burosu_h", (s32)"BRO_S_1", 1107296256, (s32)"c_burosu_h", (s32)"BRO_S_1", 1109393408,
    (s32)"c_burosu_h", (s32)"BRO_R_1", 0, (s32)"c_burosu_h", (s32)"BRO_R_1", 1088421888, (s32)"c_burosu_h", (s32)"BRO_R_1",
    1096810496, (s32)"c_kamek", (s32)"KMK_S_1", 0, (s32)"c_kamek", (s32)"KMK_S_1", 1090519040, (s32)"c_kamek",
    (s32)"KMK_S_1", 1098907648, (s32)"c_kamek", (s32)"KMK_S_1", 1103101952, (s32)"c_kamek", (s32)"KMK_S_1", 1107296256,
    (s32)"c_kamek", (s32)"KMK_S_1", 1109393408, (s32)"c_kamek", (s32)"KMK_S_1", 1111490560, (s32)"c_kamek", (s32)"KMK_S_1",
    1113587712, (s32)"c_kamek", (s32)"KMK_R_1", 0, (s32)"c_kamek", (s32)"KMK_R_1", 1088421888, (s32)"c_kamek",
    (s32)"KMK_R_1", 1096810496, 0, 0, 0,
};

void kpaSen_ext_init(void) {
    ExtPose* pose = extGetPosePtr();
    Vec base = {85.0f, 0.0f, 75.0f};
    s32 i;

    kpaSen = _mapAlloc(sizeof(KpaSen) * 200);
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        pose->flags |= 3;
        PSMTXIdentity(pose->mtx);
        if (i < 100) {
            pose->rot = 90.0f;
            kpaSen[i].end.x = (base.x + 30.0f * ((f32)i / 10.0f)) - 9.0f;
            kpaSen[i].end.y = 0.0f;
            kpaSen[i].end.z = base.z + 50.0f * (f32)(i % 10 - 5);
            pose->mtx[0][3] = kpaSen[i].start.x = base.x + 200.0f;
            pose->mtx[1][3] = kpaSen[i].start.y = 0.0f;
            pose->mtx[2][3] = kpaSen[i].start.z = base.z + 20.0f * (f32)(i % 10 - 5);
            kpaSen[i].wait = (i / 10) * 3 + 1;
            kpaSen[i].pose99Lo = 0;
            kpaSen[i].pose99Hi = 5;
            kpaSen[i].pose1Lo = 6;
            kpaSen[i].pose1Hi = 8;
        } else {
            pose->rot = 270.0f;
            kpaSen[i].end.x = (base.x + -30.0f * ((f32)(i - 100) / 10.0f)) - 150.0f;
            kpaSen[i].end.y = 0.0f;
            kpaSen[i].end.z = base.z + 50.0f * (f32)((i - 100) % 10 - 5);
            pose->mtx[0][3] = kpaSen[i].start.x = base.x - 350.0f;
            pose->mtx[1][3] = kpaSen[i].start.y = 0.0f;
            pose->mtx[2][3] = kpaSen[i].start.z = base.z + 20.0f * (f32)((i - 100) % 10 - 5);
            kpaSen[i].wait = ((i - 100) / 10) * 3 + 1;
            switch (rand() % 3) {
                case 0:
                    kpaSen[i].pose99Lo = 9;
                    kpaSen[i].pose99Hi = 14;
                    kpaSen[i].pose1Lo = 15;
                    kpaSen[i].pose1Hi = 17;
                    break;
                case 1:
                    kpaSen[i].pose99Lo = 18;
                    kpaSen[i].pose99Hi = 23;
                    kpaSen[i].pose1Lo = 24;
                    kpaSen[i].pose1Hi = 26;
                    break;
                case 2:
                    kpaSen[i].pose99Lo = 27;
                    kpaSen[i].pose99Hi = 34;
                    kpaSen[i].pose1Lo = 35;
                    kpaSen[i].pose1Hi = 37;
                    break;
            }
        }
        kpaSen[i].state = -1;
        kpaSen[i].t = 0.0f;
        if (i == 6) {
            pose->flags &= ~1;
        }
        if (i == 106 || i == 116) {
            pose->flags &= ~1;
        }
    }
}

s32 calcPose(s32 i, s32 lo, s32 hi, s32 flag) {
    s32 range = hi - lo + 1;
    s32 n = flag ? 6 : 7;

    return lo + ((gp->retraceCount + i * i) % (range * n)) / n;
}

void kpaSen_ext_main(void) {
    ExtPose* pose = extGetPosePtr();
    s32 i;

    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        switch (kpaSen[i].state) {
            case 0:
                kpaSen[i].wait--;
                if (kpaSen[i].wait == 0) {
                    kpaSen[i].state++;
                }
                break;
            case 1:
                if (i < 100) {
                    pose->frame = calcPose(i, kpaSen[i].pose1Lo, kpaSen[i].pose1Hi, 1);
                    if (i % 10 == 0) {
                    }
                } else {
                    pose->frame = calcPose(i - 100, kpaSen[i].pose1Lo, kpaSen[i].pose1Hi, 1);
                }
                pose->mtx[0][3] = kpaSen[i].start.x * (1.0f - kpaSen[i].t) + kpaSen[i].end.x * kpaSen[i].t;
                pose->mtx[2][3] = kpaSen[i].start.z * (1.0f - kpaSen[i].t) + kpaSen[i].end.z * kpaSen[i].t;
                kpaSen[i].t += 0.03;
                kpaSen[i].wait++;
                if (kpaSen[i].t >= 1.0f) {
                    pose->mtx[0][3] = kpaSen[i].end.x;
                    pose->mtx[2][3] = kpaSen[i].end.z;
                    kpaSen[i].state = 99;
                }
                break;
            case 99:
                if (i < 100) {
                    pose->frame = calcPose(i, kpaSen[i].pose99Lo, kpaSen[i].pose99Hi, 0);
                } else {
                    pose->frame = calcPose(i - 100, kpaSen[i].pose99Lo, kpaSen[i].pose99Hi, 0);
                }
                break;
            case -1:
                break;
        }
    }
}

void kpaSen_ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

void kpaSen_ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {10.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 10.0f, 0.0f, 0.1f},
        {0.0f, 0.0f, 10.0f, 0.0f},
    };

    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}

static __declspec(section ".data") EVT_BEGIN(baba_talk)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_009_1"), 0, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(kanbu_regl)
    CALL(evt_seq_wait, 2)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("カンブー"), -200, 200, 0, FLOAT(30.0f), 0)
        WAIT_MS(300)
        CALL(evt_npc_reverse_ry, STRING("カンブー"))
        WAIT_MS(300)
        CALL(evt_npc_reverse_ry, STRING("カンブー"))
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("カンブー"), 100, 200, 0, FLOAT(30.0f), 0)
        WAIT_MS(300)
        CALL(evt_npc_reverse_ry, STRING("カンブー"))
        WAIT_MS(300)
        CALL(evt_npc_reverse_ry, STRING("カンブー"))
        WAIT_MS(300)
    END_LOOP
    RETURN
EVT_END()

void kpaSen_ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, kpaSen_ext_disp, NULL);
    dispEntry(CAMERA_3D, 0.0f, 2, kpaSen_ext_shadow_disp, NULL);
}

USER_FUNC(kpaSen_zako_syugo) {
    s32 i;

    for (i = 0; i < 100; i++) {
        kpaSen[i].state = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(kpaSen_toge_syugo) {
    s32 i;

    for (i = 100; i < 200; i++) {
        kpaSen[i].state = 0;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(small_star) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effSmallStarEntry(3, 2, x, y, z, 0.0f, -1.0f, 0.0f);
    return EVT_RETURN_DONE;
}

USER_FUNC(bakuhatu_kemuri) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);

    effKemuTestDrawCam(effKemuTestEntry(8, x, y, 0.0f, 2.5f), 8);
    return EVT_RETURN_DONE;
}

USER_FUNC(white_on) {
    fadeWhiteOutOn();
    return EVT_RETURN_DONE;
}

USER_FUNC(white_off) {
    fadeWhiteOutOff();
    return EVT_RETURN_DONE;
}

__declspec(section ".data") EVT_BEGIN(kanbu_talk)
    CALL_CHILD(PTR(usu_00_koopa_second_evt))
    RETURN
EVT_END()

static EVT_BEGIN(koopa_npc_entry)
    CALL(evt_npc_get_reglid, STRING("ビビアン"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("ブタ村長"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("ブタ村人Ｋ"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("ブタ村人Ｅ"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("ブタ村人Ｄ"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("ブタ村人Ａ"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("宿店員"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("村人Ｂ"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("村長"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_delete, STRING("ビビアン"))
    CALL(evt_npc_delete, STRING("ブタ村長"))
    CALL(evt_npc_delete, STRING("ブタ村人Ｋ"))
    CALL(evt_npc_delete, STRING("ブタ村人Ｅ"))
    CALL(evt_npc_delete, STRING("ブタ村人Ｄ"))
    CALL(evt_npc_delete, STRING("ブタ村人Ａ"))
    CALL(evt_npc_delete, STRING("宿店員"))
    CALL(evt_npc_delete, STRING("村人Ｂ"))
    CALL(evt_npc_delete, STRING("村長"))
    CALL(evt_npc_entry, STRING("ババ"), STRING("c_kamek_be"))
    CALL(evt_npc_set_tribe, STRING("ババ"), STRING("カメックババ"))
    CALL(evt_npc_set_position, STRING("ババ"), 0, -1000, 0)
    CALL(evt_npc_set_ry, STRING("ババ"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("ババ"), 1536)
    CALL(evt_npc_status_onoff, 1, STRING("ババ"), 2)
    CALL(evt_npc_change_interrupt, STRING("ババ"), 6, PTR(baba_talk))
    CALL(evt_npc_set_width, STRING("ババ"), 30)
    CALL(evt_npc_set_height, STRING("ババ"), 40)
    CALL(evt_npc_entry, STRING("カンブー"), STRING("c_kanbu"))
    CALL(evt_npc_set_tribe, STRING("カンブー"), STRING("第三勢力幹部"))
    CALL(evt_npc_set_position, STRING("カンブー"), 100, 0, 200)
    CALL(evt_npc_set_ry, STRING("カンブー"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("カンブー"), 16778752)
    CALL(evt_npc_status_onoff, 1, STRING("カンブー"), 2)
    CALL(evt_npc_change_interrupt, STRING("カンブー"), 6, PTR(kanbu_talk))
    CALL(evt_npc_set_width, STRING("カンブー"), 30)
    CALL(evt_npc_set_height, STRING("カンブー"), 60)
    CALL(evt_npc_entry, STRING("トゲノコ"), STRING("c_togenoko"))
    CALL(evt_npc_set_position, STRING("トゲノコ"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("ハンマー"), STRING("c_burosu_h"))
    CALL(evt_npc_set_position, STRING("ハンマー"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("カメック"), STRING("c_kamek"))
    CALL(evt_npc_set_position, STRING("カメック"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("ザコ"), STRING("c_zako_n"))
    CALL(evt_npc_set_position, STRING("ザコ"), 0, -1000, 0)
    RETURN
EVT_END()

EVT_BEGIN(usu_00_koopa_first_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, -300, 0, 50)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_mario_flag_onoff, 1, 1024)
    CALL(evt_npc_set_position, STRING("ババ"), -400, 25, 100)
    CALL(evt_npc_set_ry, STRING("ババ"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("ババ"), 1073741856)
    CALL(evt_cam3d_evt_set, -50, 213, 677, -50, 100, 37, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_npc_get_reglid, STRING("村人Ｃ"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_fade_end_wait)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_FLY1"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_kamek_move_position, STRING("ババ"), -100, 100, 10, 0, 60, 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 0, 50, 60)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(300)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_KUPPA1"))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam3d_evt_set, -50, 138, 480, -50, 60, 37, 800, 11)
    WAIT_MS(800)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_000"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_001"), 0, STRING("ババ"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_002"), 0, STRING("mario"))
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_mario_flag_onoff, 0, 1024)
    CALL(evt_npc_flag_onoff, 0, STRING("ババ"), 1073741856)
    CALL(evt_cam3d_evt_off, 800, 11)
    WAIT_MS(800)
    CALL(evt_npc_restart_regular_event, STRING("村人Ｃ"))
    SET_VALUE(GSW(0), 266)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(bakuhatu_evt)
    CALL(bakuhatu_kemuri, FLOAT(0.0f), FLOAT(0.0f))
    WAIT_MS(100)
    CALL(bakuhatu_kemuri, FLOAT(0.0f), FLOAT(180.0f))
    CALL(bakuhatu_kemuri, FLOAT(161.19531f), FLOAT(-127.259766f))
    CALL(bakuhatu_kemuri, FLOAT(-228.0f), FLOAT(0.0f))
    WAIT_MS(40)
    CALL(bakuhatu_kemuri, FLOAT(0.0f), FLOAT(-180.0f))
    CALL(bakuhatu_kemuri, FLOAT(-161.19531f), FLOAT(127.259766f))
    CALL(bakuhatu_kemuri, FLOAT(161.19531f), FLOAT(127.259766f))
    WAIT_MS(40)
    CALL(bakuhatu_kemuri, FLOAT(228.0f), FLOAT(0.0f))
    CALL(bakuhatu_kemuri, FLOAT(-161.19531f), FLOAT(-127.259766f))
    WAIT_MS(100)
    CALL(bakuhatu_kemuri, FLOAT(0.0f), FLOAT(0.0f))
    CALL(bakuhatu_kemuri, FLOAT(171.19531f), FLOAT(-127.259766f))
    WAIT_MS(70)
    CALL(bakuhatu_kemuri, FLOAT(-171.19531f), FLOAT(127.259766f))
    CALL(bakuhatu_kemuri, FLOAT(171.19531f), FLOAT(127.259766f))
    RETURN
EVT_END()

EVT_BEGIN(murabito_out)
    CALL(delete_npc_regl_evt, STRING("村人Ｃ"))
    CALL(delete_npc_regl_evt, STRING("村人Ｅ"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("村人Ｄ"), 1073741824)
        CALL(evt_npc_status_onoff, 1, STRING("村人Ｄ"), 2)
        CALL(evt_npc_set_ry, STRING("村人Ｄ"), 90)
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("村人Ｄ"), -207, -150, 0, 180, 0)
        CALL(evt_npc_set_position, STRING("村人Ｄ"), 0, -1000, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("村人Ｃ"), 1073741824)
        CALL(evt_npc_status_onoff, 1, STRING("村人Ｃ"), 2)
        CALL(evt_npc_set_ry, STRING("村人Ｃ"), 90)
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("村人Ｃ"), -340, 60, 0, 180, 0)
        CALL(evt_npc_set_position, STRING("村人Ｃ"), 0, -1000, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("村人Ｅ"), 1073741824)
        CALL(evt_npc_status_onoff, 1, STRING("村人Ｅ"), 2)
        CALL(evt_npc_move_position, STRING("村人Ｅ"), 440, 200, 0, 180, 0)
        CALL(evt_npc_set_position, STRING("村人Ｅ"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("村人Ａ"), 1073741824)
        CALL(evt_npc_status_onoff, 1, STRING("村人Ａ"), 2)
        CALL(evt_npc_set_ry, STRING("村人Ａ"), 90)
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("村人Ａ"), -340, 30, 0, 180, 0)
        CALL(evt_npc_set_position, STRING("村人Ａ"), 0, -1000, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("村人Ｋ"), 1073741824)
        CALL(evt_npc_status_onoff, 1, STRING("村人Ｋ"), 2)
        CALL(evt_npc_set_ry, STRING("村人Ｋ"), 90)
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("村人Ｋ"), -170, -190, 0, 180, 0)
        CALL(evt_npc_move_position, STRING("村人Ｋ"), -207, -215, 0, 150, 0)
        CALL(evt_npc_set_position, STRING("村人Ｋ"), 0, -1000, 0)
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(usu_00_koopa_second_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_motion, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("カンブー"), LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dir, LW(0), LW(2), LW(3), LW(5), LW(6))
    IF_INT_LESS(LW(6), 180)
        SET_VALUE(LW(7), 90)
        ELSE
        SET_VALUE(LW(7), 270)
    END_IF
    CALL(evt_npc_set_ry, STRING("カンブー"), LW(7))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_010_00"), 0, STRING("カンブー"))
    CALL(evt_npc_get_position, STRING("カンブー"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), 75)
        CALL(evt_npc_set_ry, STRING("カンブー"), 90)
        ELSE
        CALL(evt_npc_set_ry, STRING("カンブー"), 270)
    END_IF
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("カンブー"))
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("カンブー"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(0), 75)
            CALL(evt_mario_set_dir, 90, 300, 0)
            CALL(evt_mario_dispflag_onoff, 1, 256)
        END_IF
        CALL(evt_mario_mov_pos, -70, 290, 1500)
        CALL(evt_mario_dispflag_onoff, 0, 256)
        CALL(evt_mario_set_dir_npc, STRING("カンブー"))
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_FLY1"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("ババ"), 32)
        WAIT_MS(500)
        CALL(evt_npc_kamek_move_position, STRING("ババ"), -15, 240, 8, 1500, 0, 0)
        CALL(evt_npc_flag_onoff, 0, STRING("ババ"), 32)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 75, 116, 612, 75, 50, 268, 1500, 11)
    CALL(evt_npc_flag_onoff, 1, STRING("カンブー"), 32)
    CALL(evt_npc_move_position, STRING("カンブー"), 75, 275, 1500, 0, 4)
    WAIT_MS(300)
    CALL(evt_npc_flag_onoff, 0, STRING("カンブー"), 32)
    CALL(evt_npc_get_position, STRING("カンブー"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position_nohit, STRING("カンブー"), LW(0), LW(1), LW(2), 300, 20)
    WAIT_MS(500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_GRASS_SHAKE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING("カンブー"), STRING("C_2"))
    WAIT_MS(300)
    CALL(evt_npc_get_dir, STRING("カンブー"), LW(3))
    IF_INT_LESS(LW(3), 180)
        ADD(LW(0), 10)
        ELSE
        SUBTRACT(LW(0), 10)
    END_IF
    ADD(LW(1), 45)
    ADD(LW(2), 5)
    CALL(evt_item_entry, STRING("item"), 67, LW(0), LW(1), LW(2), 17, -1, 0)
    WAIT_MS(800)
    CALL(evt_npc_set_stay_anim, STRING("カンブー"))
    CALL(evt_item_delete, STRING("item"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_010"), 0, STRING("カンブー"))
    CALL(evt_cam3d_evt_set, 0, 147, 737, 0, 60, 245, 800, 11)
    WAIT_MS(800)
    CALL(evt_npc_set_anim, STRING("ババ"), STRING("A_3A"))
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("ババ"), STRING("A_3B"), STRING("T_10"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_011"), 0, STRING("ババ"))
    CALL(evt_npc_set_autotalkpose, STRING("ババ"), STRING("S_2"), STRING("T_9"))
    CALL(evt_npc_set_stay_anim, STRING("ババ"))
    CALL(evt_npc_set_ry, STRING("カンブー"), 270)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_012"), 0, STRING("カンブー"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 10)
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_4"), STRING("KPA_T_3"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_013"), 0, STRING("mario"))
    CALL(evt_npc_status_onoff, 0, STRING("カンブー"), 2)
    CALL(evt_npc_get_position, STRING("カンブー"), LW(0), LW(1), LW(2))
    ADD(LW(0), 10)
    CALL(evt_npc_move_position, STRING("カンブー"), LW(0), LW(2), 0, FLOAT(60.0f), 0)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_014"), 0, STRING("カンブー"))
    CALL(evt_npc_get_position, STRING("カンブー"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_3RD_SHUGOU1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(500)
    CALL(evt_ext_entry, 200, PTR(kpaSen_ext_entry_data), PTR(kpaSen_ext_init), PTR(kpaSen_ext_main), PTR(kpaSen_ext_dispent))
    SPAWN_EVENT(PTR(murabito_out))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 40, 90, 381, 85, 45, 113, 800, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("カンブー"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_TAIGUN_MOVE1"), LW(0), LW(1), LW(2), 0)
        CALL(kpaSen_zako_syugo)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("カンブー"), 93, 0, 109, 500, 60)
    WAIT_MS(1300)
    CALL(evt_cam3d_evt_set, 42, 29, 375, 85, 45, 113, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_015"), 0, STRING("カンブー"))
    CALL(evt_cam3d_evt_set, -80, 172, 456, -80, 50, 78, 800, 11)
    WAIT_MS(800)
    CALL(evt_mario_flag_onoff, 1, 1024)
    CALL(evt_mario_dispflag_onoff, 1, 256)
    CALL(evt_npc_status_onoff, 0, STRING("ババ"), 2)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_FLY1"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_kamek_move_position, STRING("ババ"), -43, 90, 10, 0, FLOAT(90.0f), 0)
        SET_VALUE(GF(0), 1)
        CALL(evt_npc_set_ry, STRING("ババ"), 90)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -103, 120, FLOAT(90.0f))
    CALL(evt_mario_dispflag_onoff, 0, 256)
    CALL(evt_mario_set_dir, 90, 300, 0)
    LOOP(0)
        IF_INT_NOT_EQUAL(GF(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("ババ"), STRING("A_3A"))
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("ババ"), STRING("A_3B"), STRING("T_10"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_016"), 0, STRING("ババ"))
    WAIT_FRAMES(1)
    CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_SHUGOU1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_TAIGUN_MOVE1"), LW(0), LW(1), LW(2), 0)
    CALL(kpaSen_toge_syugo)
    WAIT_MS(1500)
    CALL(evt_npc_set_autotalkpose, STRING("ババ"), STRING("S_2"), STRING("T_9"))
    CALL(evt_npc_set_stay_anim, STRING("ババ"))
    CALL(evt_cam3d_evt_set, -14, 225, 715, -4, 57, 120, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_017"), 0, STRING("カンブー"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_018"), 0, STRING("ババ"))
    WAIT_MS(2000)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("カンブー"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 40, 90, 381, 85, 45, 113, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_019"), 0, STRING("カンブー"))
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_npc_set_anim, STRING("カンブー"), STRING("C_2"))
    WAIT_MS(250)
    CALL(evt_npc_get_position, STRING("カンブー"), LW(2), LW(3), LW(4))
    CALL(evt_mario_get_pos, 0, LW(5), LW(6), LW(7))
    ADD_FLOAT(LW(5), FLOAT(60.0f))
    SUBTRACT_FLOAT(LW(2), FLOAT(10.0f))
    ADD_FLOAT(LW(3), FLOAT(45.0f))
    ADD_FLOAT(LW(4), FLOAT(5.0f))
    ADD_FLOAT(LW(6), FLOAT(50.0f))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(3))
    SET_FLOAT_VALUE(GW(2), LW(4))
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_APPEAR1"), LW(2), LW(3), LW(4), 0)
    WAIT_MS(100)
    CALL(evt_item_entry, STRING("itikoro"), 67, LW(2), LW(3), LW(4), 17, -1, 0)
    SET_VALUE(LW(8), LW(3))
    ADD(LW(8), 12)
    SET_VALUE(LW(9), LW(4))
    ADD(LW(9), 5)
    CALL(evt_eff64, STRING(""), STRING("stardust2_n64"), 3, LW(2), LW(8), LW(9), 32, 32, 4, 12, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_SHINE1"), LW(2), LW(8), LW(9), 0)
    WAIT_MS(1000)
    CALL(evt_npc_set_anim, STRING("カンブー"), STRING("S_1"))
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(1), 30)
        SET_FLOAT_VALUE(LW(8), LW(7))
        SUBTRACT_FLOAT(LW(8), LW(4))
        DIVIDE_FLOAT(LW(8), LW(1))
        SET_VALUE(LW(0), 0)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                WAIT_FRAMES(1)
                CONTINUE_LOOP
            END_IF
            IF_INT_EQUAL(LW(0), LW(1))
                BREAK_LOOP
            END_IF
            ADD_FLOAT(LW(4), LW(8))
            SET_FLOAT_VALUE(GW(2), LW(4))
            ADD(LW(0), 1)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(8), FLOAT(-4.1992188f))
        SET_FLOAT_VALUE(LW(9), FLOAT(4.0f))
        SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
        SET_FLOAT_VALUE(LW(11), FLOAT(-0.25976563f))
        SET_VALUE(LF(0), 0)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                WAIT_FRAMES(1)
                CONTINUE_LOOP
            END_IF
            ADD_FLOAT(LW(2), LW(8))
            ADD_FLOAT(LW(3), LW(9))
            CALL(evt_item_set_position, STRING("itikoro"), LW(2), LW(3), GW(2))
            IF_INT_EQUAL(LF(0), 0)
                IF_INT_LESS_OR_EQUAL(LW(2), LW(5))
                    SET_VALUE(LF(0), 1)
                    MULTIPLY_FLOAT(LW(8), FLOAT(-0.44921875f))
                    SET_FLOAT_VALUE(LW(10), FLOAT(-0.049804688f))
                    SET_FLOAT_VALUE(LW(12), LW(2))
                    SUBTRACT_FLOAT(LW(12), FLOAT(5.0f))
                    SET_FLOAT_VALUE(LW(13), LW(3))
                    ADD_FLOAT(LW(13), FLOAT(15.0f))
                    CALL(small_star, LW(12), LW(13), GW(2))
                END_IF
            END_IF
            IF_INT_LESS_OR_EQUAL(LW(3), 0)
                SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
                MULTIPLY_FLOAT(LW(9), FLOAT(-0.5f))
                SET_FLOAT_VALUE(LW(12), LW(9))
                MULTIPLY_FLOAT(LW(12), FLOAT(10.0f))
                IF_INT_LESS_OR_EQUAL(LW(12), 2)
                    BREAK_LOOP
                    ELSE
                    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_JUMP1"), LW(2), LW(3), GW(2), 0)
                END_IF
            END_IF
            ADD_FLOAT(LW(8), LW(10))
            ADD_FLOAT(LW(9), LW(11))
            IF_INT_EQUAL(LF(0), 1)
                SET_FLOAT_VALUE(LW(12), LW(8))
                MULTIPLY_FLOAT(LW(12), 10)
                IF_INT_LESS_OR_EQUAL(LW(12), 2)
                    SET_FLOAT_VALUE(LW(8), FLOAT(0.19921875f))
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_item_set_position, STRING("itikoro"), LW(2), 0, GW(2))
    END_INLINE_EVENT
    CALL(evt_item_get_position, STRING("itikoro"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_FLY1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(160)
    CALL(evt_cam3d_evt_set, -80, 172, 456, -80, 50, 78, 0, 11)
    WAIT_FRAMES(1)
    SET_VALUE(GF(0), 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_SURPRISED2_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_5"), STRING("KPA_T_5"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_020"), 0, STRING("mario"))
    SET_VALUE(GF(0), 1)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 60)
    ADD(LW(1), 50)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_HIT1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(500)
    WAIT_MS(1000)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
    CALL(evt_msg_print, 0, STRING("kpa_stg5_021"), 0, STRING("mario"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_ANGRY1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_koopa_fire, 1000)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_item_get_position, STRING("itikoro"), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        SUBTRACT(LW(3), 1)
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_item_set_position, STRING("itikoro"), LW(3), LW(1), LW(2))
            WAIT_FRAMES(2)
            ADD(LW(3), 2)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_item_set_position, STRING("itikoro"), LW(3), LW(1), LW(2))
            WAIT_FRAMES(2)
            SUBTRACT(LW(3), 2)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -14, 225, 715, -4, 57, 120, 1000, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("kpa_stg5_022"), 0, STRING("カンブー"))
    WAIT_MS(100)
    CALL(evt_item_get_position, STRING("itikoro"), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_BIRIBIRI1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff64, STRING(""), STRING("akari_charge_n64"), 0, LW(0), LW(1), LW(2), FLOAT(0.5f), 48, 0, 0, 0, 0, 0, 0)
    WAIT_MS(800)
    CALL(evt_eff64, STRING("rad"), STRING("radiation_n64"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_ITIKORO_LIGHT1"), LW(0), LW(1), LW(2), LW(15))
    WAIT_MS(1000)
    CALL(kpa_chg_pose, STRING("KPA_O_1"))
    SPAWN_EVENT(PTR(bakuhatu_evt))
    WAIT_MS(350)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_rumble_onoff, 0, 0)
        WAIT_MS(5000)
        CALL(evt_sub_rumble_onoff, 1, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_eff_delete, STRING("rad"))
        CALL(evt_snd_sfxoff, LW(15))
        CALL(evt_item_get_position, STRING("itikoro"), LW(0), LW(1), LW(2))
        CALL(evt_item_delete, STRING("itikoro"))
        SET_VALUE(GF(0), 1)
        CALL(evt_snd_sfxon, STRING("SFX_KUPPA_ITIKORO_EXPLOSION1"), 0)
    END_INLINE_EVENT
    CALL(evt_fade_entry, 10, 600, 255, 255, 255)
    CALL(evt_fade_end_wait)
    WAIT_MS(3000)
    SET_VALUE(GSW(0), 267)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(white_on)
    CALL(evt_cam_letter_box_onoff, 0, 1)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_fade_entry, 6, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(white_off)
    CALL(evt_cam_letter_box_disable, 0)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 15)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 0)
    CALL(evt_fade_set_mapchange_type, 1, 59, 0, 58, 0)
    CALL(evt_bero_mapchange, STRING("muj_00"), STRING(""))
    RETURN
EVT_END()

void envSetYamiView(Mtx mtx);

static USER_FUNC(yami_view) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){0.0f, 100.0f, 100.0f + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){0.0f, 0.0f, z});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}

static USER_FUNC(anim_tevcallback) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr_NoAssert(name);

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(npc->poseId, (flag & 0xF) << 24);
    return EVT_RETURN_DONE;
}

static USER_FUNC(delete_npc_regl_evt);
static USER_FUNC(delete_npc_regl_evt) {
    NpcEntry* npc = npcNameToPtr_NoAssert((const char*)evtGetValue(event, event->args[0]));

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    if (npc->regularEvtId != 0) {
        evtDeleteID(npc->regularEvtId);
        npc->moveEvent = NULL;
        npc->regularEvtId = 0;
    } else if (npc->moveEvent != NULL) {
        npc->moveEvent = NULL;
    }
    return EVT_RETURN_DONE;
}

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

static USER_FUNC(starstone_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effSetName(effStarStoneEntry(3, x, y, z, 1.0f), name);
    return EVT_RETURN_DONE;
}

static USER_FUNC(starstone_set_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[2] = x;
    ((f32*)eff->userdata)[3] = y;
    ((f32*)eff->userdata)[4] = z;
    return EVT_RETURN_DONE;
}

static USER_FUNC(starstone_set_ry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 ry = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[7] = ry;
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(sekai_yami_npc_init)
    CALL(delete_npc_regl_evt, STRING("村人Ａ"))
    CALL(delete_npc_regl_evt, STRING("村人Ｂ"))
    CALL(delete_npc_regl_evt, STRING("村人Ｃ"))
    CALL(delete_npc_regl_evt, STRING("村人Ｄ"))
    CALL(delete_npc_regl_evt, STRING("村人Ｅ"))
    RETURN
EVT_END()

static EVT_BEGIN(sekai_yami_npc)
    LOOP(0)
        CALL(evt_sub_random, 400, LW(1))
        ADD(LW(1), 100)
        WAIT_MS(LW(1))
        CALL(evt_npc_reverse_ry, LW(0))
        WAIT_FRAMES(1)
        CALL(evt_npc_wait_pera, LW(0))
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(sekai_yami_shake)
    LOOP(0)
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.009765625f), 500)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(sekai_yami_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_usu00"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_usu00"), 256)
    CALL(anim_tevcallback, STRING("村人Ａ"), 1)
    CALL(anim_tevcallback, STRING("村人Ｂ"), 1)
    CALL(anim_tevcallback, STRING("村人Ｃ"), 1)
    CALL(anim_tevcallback, STRING("村人Ｄ"), 1)
    CALL(anim_tevcallback, STRING("村人Ｅ"), 1)
    CALL(anim_tevcallback, STRING("村人Ｋ"), 1)
    CALL(anim_tevcallback, STRING("カラスＣ"), 1)
    CALL(anim_tevcallback, STRING("カラスＤ"), 1)
    CALL(anim_tevcallback, STRING("カラスＥ"), 1)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(yami_view, -800)
    CALL(evt_cam3d_evt_set, 0, 80, 687, 0, 70, -13, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    LOOP(2)
        CALL(evt_snd_sfxon, STRING("SFX_STG8_LIGHT1"), 0)
        CALL(evt_fade_entry, 10, 0, 255, 255, 255)
        WAIT_MS(100)
        CALL(evt_fade_entry, 9, 0, 255, 255, 255)
        WAIT_MS(100)
    END_LOOP
    SET_VALUE(LW(0), STRING("村人Ａ"))
    SPAWN_EVENT(PTR(sekai_yami_npc))
    SET_VALUE(LW(0), STRING("村人Ｂ"))
    SPAWN_EVENT(PTR(sekai_yami_npc))
    SET_VALUE(LW(0), STRING("村人Ｃ"))
    SPAWN_EVENT(PTR(sekai_yami_npc))
    SET_VALUE(LW(0), STRING("村人Ｄ"))
    SPAWN_EVENT(PTR(sekai_yami_npc))
    SET_VALUE(LW(0), STRING("村人Ｅ"))
    SPAWN_EVENT(PTR(sekai_yami_npc))
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING("カラスＣ"), 2)
        CALL(evt_npc_get_position, STRING("カラスＣ"), LW(0), LW(1), LW(2))
        CALL(evt_npc_set_ry, STRING("カラスＣ"), 270)
        CALL(evt_npc_jump_position_nohit, STRING("カラスＣ"), -10, 250, LW(2), 1500, 30)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING("カラスＤ"), 2)
        CALL(evt_npc_set_ry, STRING("カラスＤ"), 90)
        CALL(evt_npc_get_position, STRING("カラスＤ"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING("カラスＤ"), 100, 250, LW(2), 1500, 30)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING("カラスＥ"), 2)
        CALL(evt_npc_set_ry, STRING("カラスＥ"), 90)
        CALL(evt_npc_get_position, STRING("カラスＥ"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING("カラスＥ"), 150, 250, LW(2), 1500, 30)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_STG8_QUAKE1"), LW(0))
    SPAWN_EVENT(PTR(sekai_yami_shake))
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING("stg8_dark_05"), 0, 0)
    WAIT_MS(1500)
    CALL(evt_snd_sfxoff, LW(0))
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING("muj_01"), STRING("sekai_yami2"))
    RETURN
EVT_END()

static EVT_BEGIN(minnnanokoe_npc_entry)
    CALL(evt_npc_entry, STRING("おばさん"), STRING("c_f_mama"))
    CALL(evt_npc_set_tribe, STRING("おばさん"), STRING("ウスグラおばさん"))
    CALL(evt_npc_set_position, STRING("おばさん"), -120, 0, -90)
    CALL(evt_npc_set_ry, STRING("おばさん"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("おばさん"), 512)
    CALL(evt_npc_entry, STRING("子供１"), STRING("c_f_child_a"))
    CALL(evt_npc_set_tribe, STRING("子供１"), STRING("ウスグラ子供A"))
    CALL(evt_npc_set_position, STRING("子供１"), -80, 0, -25)
    CALL(evt_npc_set_ry, STRING("子供１"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("子供１"), 512)
    CALL(evt_npc_entry, STRING("子供２"), STRING("c_f_child_b"))
    CALL(evt_npc_set_tribe, STRING("子供２"), STRING("ウスグラ子供B"))
    CALL(evt_npc_set_position, STRING("子供２"), -50, 0, 0)
    CALL(evt_npc_set_ry, STRING("子供２"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("子供２"), 512)
    CALL(evt_npc_entry, STRING("子供３"), STRING("c_f_child_c"))
    CALL(evt_npc_set_tribe, STRING("子供３"), STRING("ウスグラ子供C"))
    CALL(evt_npc_set_position, STRING("子供３"), -100, 0, 10)
    CALL(evt_npc_set_ry, STRING("子供３"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("子供３"), 512)
    RETURN
EVT_END()

static EVT_BEGIN(minnnanokoe_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("村長"), -60, 0, -75)
    CALL(evt_npc_set_ry, STRING("村長"), 270)
    CALL(evt_npc_set_position, STRING("村人Ａ"), 0, 0, -100)
    CALL(evt_npc_set_ry, STRING("村人Ａ"), 270)
    CALL(evt_npc_set_position, STRING("村人Ｃ"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("村人Ｄ"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("村人Ｅ"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("村人Ｋ"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("カラスＣ"), 1000, -1000, 0)
    CALL(evt_npc_set_position, STRING("カラスＤ"), 1000, -1000, 0)
    CALL(evt_npc_set_position, STRING("カラスＥ"), 1000, -1000, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_usu00"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_usu00"), 256)
    CALL(anim_tevcallback, STRING("おばさん"), 1)
    CALL(anim_tevcallback, STRING("子供１"), 1)
    CALL(anim_tevcallback, STRING("子供２"), 1)
    CALL(anim_tevcallback, STRING("子供３"), 1)
    CALL(anim_tevcallback, STRING("村人Ａ"), 1)
    CALL(anim_tevcallback, STRING("村長"), 1)
    CALL(yami_view, -800)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(evt_cam3d_evt_set, -350, 90, 737, -76, 70, 0, 0, 11)
    CALL(starstone_entry, STRING("starstone"), -75, 60, 0)
    SET_VALUE(GW(3), 60)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(starstone_set_pos, STRING("starstone"), -75, GW(3), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(0)
            CALL(starstone_set_ry, STRING("starstone"), LW(0))
            SUBTRACT_FLOAT(LW(0), FLOAT(3.0f))
            IF_INT_LESS_OR_EQUAL(LW(0), FLOAT(0.0f))
                ADD_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 6000, 6500, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(3), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, 6500, 6000, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(3), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(2)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_26"), 0, STRING("子供１"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_27"), 0, STRING("子供２"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_28"), 0, STRING("子供３"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_29"), 0, STRING("子供１"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_30"), 0, STRING("子供２"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_31"), 0, STRING("子供３"))
    CALL(evt_npc_flag_onoff, 1, STRING("子供１"), 32768)
    CALL(evt_npc_flag_onoff, 1, STRING("子供２"), 32768)
    CALL(evt_npc_flag_onoff, 1, STRING("子供３"), 32768)
    CALL(evt_npc_flag_onoff, 1, STRING("おばさん"), 32768)
    CALL(evt_cam3d_evt_set, -75, 92, 313, -75, 52, -35, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_32"), 0, STRING("村人Ａ"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_33"), 0, STRING("おばさん"))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_34"), 0, STRING("村長"))
    CALL(evt_cam3d_evt_set, -185, 70, 858, -91, 111, -36, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_35"), 0, STRING("子供１"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_36"), 0, STRING("子供２"))
    CALL(evt_msg_print, 0, STRING("stg8_las_148_37"), 0, STRING("子供３"))
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING("muj_01"), STRING("minnnanokoe"))
    RETURN
EVT_END()

__declspec(section ".rodata") Vec party_scale_vec = {1.0f, 1.0f, 1.0f};

USER_FUNC(party_scale) {
    partyGetPtr(0)->scale = party_scale_vec;
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(evt_after_peach)
    CALL(evt_mario_key_onoff, 0)
    CALL(party_scale)
    CALL(evt_mario_set_pos, -90, 0, -50)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_pos, 0, -130, 0, -60)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_party_run, 0)
    CALL(evt_npc_set_position, STRING("村長"), -30, 0, -50)
    CALL(evt_npc_set_ry, STRING("村長"), 270)
    CALL(evt_cam3d_evt_set, -75, 105, 275, -75, 45, -67, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_npc_get_reglid, STRING("村人Ｃ"), LW(10))
    DELETE_EVENT(LW(10))
    CALL(evt_npc_set_position, STRING("村人Ｃ"), 85, 0, 10)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg4_usu_153"), 0, STRING("村長"))
    CALL(evt_msg_select, 0, STRING("stg4_usu_153_select"))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("stg4_usu_154"))
        ELSE
        CALL(evt_msg_print_add, 0, STRING("stg4_usu_155"))
    END_IF
    CALL(evt_cam3d_evt_set, -110, 105, 275, -110, 45, -67, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg4_usu_156"))
    CALL(evt_party_run, 0)
    CALL(evt_msg_print, 0, STRING("stg4_usu_157"), 0, STRING("村長"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(0), 219)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_npc_restart_regular_event, STRING("村人Ｃ"))
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｃ"), 268435456)
    CALL(evt_npc_stop_for_event)
    CALL(evt_npc_start_for_event)
    CALL(evt_npc_flag_onoff, 0, STRING("村人Ｃ"), 268435456)
    RETURN
EVT_END()

static USER_FUNC(npc_process) {
    NpcWork* wp = npcGetWorkPtr();
    NpcEntry* npc = wp->entries;
    s32 i;

    for (i = 0; i < wp->total; i++, npc++) {
        if (npc->flags & 1) {
            if (npc->position.y <= -1000.0f) {
                npc->flags |= 0x800;
            } else {
                npc->flags &= ~0x800;
            }
        }
    }
    return EVT_RETURN_BLOCK;
}

static EVT_BEGIN(epilogue_npc_entry)
    CALL(evt_npc_entry, STRING("クリスチーヌ"), STRING("c_pkr"))
    CALL(evt_npc_set_tribe, STRING("クリスチーヌ"), STRING("クリスチーヌ"))
    CALL(evt_npc_set_position, STRING("クリスチーヌ"), -25, 0, 100)
    CALL(evt_npc_set_ry, STRING("クリスチーヌ"), 90)
    CALL(evt_npc_entry, STRING("マジョリン"), STRING("c_majyorin"))
    CALL(evt_npc_set_tribe, STRING("マジョリン"), STRING("マジョリン"))
    CALL(evt_npc_set_position, STRING("マジョリン"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("マリリン"), STRING("c_maririn"))
    CALL(evt_npc_set_tribe, STRING("マリリン"), STRING("マリリン"))
    CALL(evt_npc_set_position, STRING("マリリン"), 0, -1000, 0)
    RETURN
EVT_END()

static EVT_BEGIN(epilogue_evt_sub)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_T_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_S_1"))
    CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_T_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_S_1"))
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_A4_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_S_1"))
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_npc_majo_disp_on, STRING("マリリン"), 60, 0, 80, 0)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    CALL(evt_npc_majo_disp_on, STRING("マジョリン"), 75, 0, 120, 0)
    WAIT_WHILE(GF(0))
    WAIT_MS(300)
    CALL(evt_npc_set_ry, STRING("ビビアン"), 90)
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("ビビアン"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("マジョリン"), STRING("MJR_T_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("マジョリン"), STRING("MJR_S_1"))
    CALL(evt_npc_set_anim, STRING("マリリン"), STRING("MRR_T_1"))
    WAIT_MS(1000)
    CALL(evt_npc_set_anim, STRING("マリリン"), STRING("MRR_S_1"))
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_T_1"))
    WAIT_MS(1000)
    CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_S_1"))
    CALL(evt_npc_set_anim, STRING("マジョリン"), STRING("MJR_T_1"))
    WAIT_MS(1000)
    CALL(evt_npc_set_anim, STRING("マジョリン"), STRING("MJR_S_1"))
    WAIT_MS(500)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_npc_majo_disp_off, STRING("マリリン"))
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    CALL(evt_npc_majo_disp_off, STRING("マジョリン"))
    WAIT_WHILE(GF(0))
    WAIT_MS(500)
    CALL(evt_npc_set_ry, STRING("ビビアン"), 270)
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("ビビアン"))
    WAIT_MS(500)
    LOOP(0)
        CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_T_1"))
        WAIT_MS(1500)
        CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_S_1"))
        CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_T_1"))
        WAIT_MS(1500)
        CALL(evt_npc_set_anim, STRING("ビビアン"), STRING("PTR_S_1"))
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(epilogue_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_USU1"))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_npc_set_position, STRING("ビビアン"), 25, 0, 100)
    CALL(evt_npc_set_ry, STRING("ビビアン"), 270)
    CALL(evt_cam3d_evt_set, 0, 109, 495, 0, 50, 100, 0, 11)
    CALL(evt_seq_wait, 2)
    SPAWN_EVENT(PTR(epilogue_evt_sub))
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("ep_41"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_snd_bgmoff_f, 512, 3000)
    CALL(evt_snd_envoff_f, 512, 3000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 900, 9, 900)
    CALL(evt_bero_mapchange, STRING("muj_20"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(usu_00_init_evt)
    SET_VALUE(GF(1), 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 265)
        IF_INT_LESS_OR_EQUAL(GSW(0), 266)
            CALL(evt_mario_set_mode, 2)
            SET_VALUE(GF(1), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        SWITCH(GSW(0))
            CASE_BETWEEN(201, 202)
            CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_WITCH1"))
            CALL(evt_snd_envoff, 512)
            CASE_EQUAL(203)
            CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_WITCH1"))
            CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
            CASE_BETWEEN(204, 205)
            CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_WITCH1"))
            CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
            CASE_EQUAL(400)
            SET_VALUE(LF(1), 0)
            CALL(evt_bero_get_entername, LW(0))
            IF_STR_EQUAL(LW(0), STRING("sekai_yami2"))
                CALL(evt_snd_bgmoff, 512)
                CALL(evt_snd_envoff, 512)
                SET_VALUE(LF(1), 1)
            END_IF
            IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
                CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG8_VOICE1"))
                CALL(evt_snd_envoff, 512)
                SET_VALUE(LF(1), 1)
            END_IF
            IF_INT_EQUAL(LF(1), 0)
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_USU1"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
            END_IF
            CASE_DEFAULT
            IF_INT_NOT_EQUAL(GSW(0), 402)
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_USU1"))
            END_IF
            CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
        END_SWITCH
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_USU1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        CALL(evt_kagemario_init_29_text_1A0C)
    END_IF
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_EQUAL(GF(1), 1)
        SET_VALUE(LW(0), STRING("dokan_1"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("dokan_1"), PTR(bero_koopa_dokan))
        SET_VALUE(LW(0), STRING("dokan_1"))
        CALL_CHILD(PTR(bero_case_switch_on))
        SET_VALUE(LW(0), 1)
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("bero"), 1)
        CALL(evt_hitobj_attr_onoff, 1, 0, STRING("e_bero"), 8388612)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_02"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_03"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_04"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_06"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_07"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_08"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_09"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_10"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_11"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_12"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_13"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_14"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_15"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_16"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_17"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_18"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_19"), 1)
        CALL(L_evt_hitobj_flag_onoff, 1, 1, STRING("A_kusa_20"), 1)
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        CALL(evt_mobj_save_blk, STRING("mobj_save"), 365, 60, -50, 0, 0)
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        CALL(evt_item_entry, STRING("item00"), 125, -220, 0, -225, 16, GSWF(5629), 0)
    END_IF
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_29_data_104A8))
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_EQUAL(GF(1), 1)
        CALL_CHILD(PTR(koopa_npc_entry))
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        SET_VALUE(LW(0), PTR(door_1))
        CALL_CHILD(PTR(evt_door_entry))
        SET_VALUE(LW(0), PTR(door_2))
        CALL_CHILD(PTR(evt_door_entry))
        SET_VALUE(LW(0), PTR(door_3))
        CALL_CHILD(PTR(evt_door_entry))
        ELSE
        CALL(evt_run_case_evt, 9, 1, STRING("A_ie1door"), 0, PTR(door_ie1_koopa_evt), 0)
        CALL(evt_run_case_evt, 9, 1, STRING("A_ie2door"), 0, PTR(door_ie2_koopa_evt), 0)
        CALL(evt_run_case_evt, 9, 1, STRING("A_ie3door"), 0, PTR(door_ie3_koopa_evt), 0)
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        CALL(evt_kinopio_setup, PTR(kino_dt))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki1"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki2"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki3"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki4"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki5"), 2)
    CALL_CHILD(PTR(usu_00_kusa_init))
    CALL_CHILD(PTR(usu_00_tree_init))
    SWITCH(GSW(0))
        CASE_LESS(178)
        SPAWN_EVENT(PTR(usu00_stage4_coming_event))
        CASE_BETWEEN(179, 179)
        SPAWN_EVENT(PTR(chief_pig_event))
    END_SWITCH
    SWITCH(GSW(0))
        CASE_BETWEEN(203, 209)
        CALL_CHILD(PTR(chief_mario_talk_init))
        SPAWN_EVENT(PTR(chief_mario_talk))
    END_SWITCH
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("evt_majo3"))
        CALL_CHILD(PTR(usu00_3witch_init))
        SPAWN_EVENT(PTR(usu00_3witch_event))
    END_IF
    IF_INT_EQUAL(GSW(0), 203)
        SPAWN_EVENT(PTR(usu00_vivian_cry_event))
    END_IF
    IF_INT_LESS(GSW(0), 205)
        CALL(evt_run_case_evt, 9, 1, STRING("A_kusa_07"), 0, PTR(usu_00_touch_ichikorori_ball), 0)
    END_IF
    IF_INT_EQUAL(GSW(0), 213)
        CALL_CHILD(PTR(usu00_3witch_init))
        SPAWN_EVENT(PTR(gra00_2witch_find_ranpel_event))
    END_IF
    SPAWN_EVENT(PTR(usu00_check_vivian))
    SET_VALUE(GW(0), 0)
    SET_VALUE(GW(1), 0)
    SPAWN_EVENT(PTR(usu00_crowAB_talk_event))
    SPAWN_EVENT(PTR(usu00_crowCDE_talk_event))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 200)
        IF_INT_LESS(GSW(0), 212)
            SET_VALUE(LW(0), STRING("dokan_1"))
            CALL_CHILD(PTR(bero_case_switch_off))
            CALL(evt_bero_overwrite, STRING("dokan_1"), PTR(bero_oshimodo))
            SET_VALUE(LW(0), STRING("dokan_1"))
            CALL_CHILD(PTR(bero_case_switch_on))
        END_IF
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        BEGIN_INLINE_EVENT
            CALL(booboo_main)
        END_INLINE_EVENT
    END_IF
    IF_INT_EQUAL(GSW(0), 265)
        CALL(evt_npc_change_interrupt, STRING("カンブー"), 1, PTR(kanbu_regl))
        CALL(evt_npc_restart_regular_event, STRING("カンブー"))
        CALL(evt_mario_kill_party, 0)
        SPAWN_EVENT(PTR(usu_00_koopa_first_evt))
        CALL(evt_cam_road_reset)
    END_IF
    IF_INT_EQUAL(GSW(0), 266)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("player"))
            CALL(evt_npc_change_interrupt, STRING("カンブー"), 1, PTR(kanbu_regl))
            CALL(evt_npc_restart_regular_event, STRING("カンブー"))
            CALL(evt_mario_set_pos, 0, 0, 50)
            CALL(evt_mario_set_dir, 90, 0, 0)
            CALL(evt_npc_set_position, STRING("ババ"), -100, 25, 100)
            ELSE
            CALL(evt_mario_set_pos, 30, 0, 180)
            CALL(evt_mario_set_dir, 90, 0, 0)
            CALL(evt_npc_set_position, STRING("ババ"), -100, 25, 100)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                WAIT_MS(1000)
                SPAWN_EVENT(PTR(usu_00_koopa_second_evt))
            END_INLINE_EVENT
        END_IF
        CALL(evt_cam_road_reset)
    END_IF
    IF_INT_EQUAL(GSW(0), 218)
        CALL(evt_mario_get_party, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
            CALL(evt_pouch_mario_recovery)
            CALL(evt_pouch_all_party_recovery)
        END_IF
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_pos, 0, -130, 0, -60)
        SPAWN_EVENT(PTR(evt_after_peach))
    END_IF
    IF_INT_EQUAL(GSW(0), 400)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("sekai_yami2"))
            CALL_CHILD(PTR(sekai_yami_npc_init))
            SPAWN_EVENT(PTR(sekai_yami_evt))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
            CALL_CHILD(PTR(minnnanokoe_npc_entry))
            SPAWN_EVENT(PTR(minnnanokoe_evt))
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 402)
        CALL(evt_mario_kill_party, 0)
        CALL_CHILD(PTR(epilogue_npc_entry))
        SPAWN_EVENT(PTR(epilogue_evt))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(npc_process)
    END_INLINE_EVENT
    RETURN
EVT_END()

