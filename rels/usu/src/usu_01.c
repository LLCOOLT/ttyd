#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include "string.h"
#include "mario/mario_pouch.h"
#include "memory.h"
#include "data/item_data.h"
#include "driver/npcdrv.h"
#include "driver/mobjdrv.h"

extern ItemData itemDataTable[];
void mapObjFlagOn(const char* name, u32 flags);
void mapObjFlagOff(const char* name, u32 flags);

static USER_FUNC(bgm_start_wait);
static USER_FUNC(booboo_main);
USER_FUNC(box_r);
USER_FUNC(check_tabemono);
USER_FUNC(chk_fuki);
USER_FUNC(delete_item_list);
USER_FUNC(door_dark_flag);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam3d_evt_set_xyz);
USER_FUNC(evt_cam3d_evt_xyz_off);
USER_FUNC(evt_cam_get_at);
USER_FUNC(evt_cam_get_pos);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_door_load_mapflag);
USER_FUNC(evt_door_param);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_img_alloc_capture);
USER_FUNC(evt_img_clear_virtual_point);
USER_FUNC(evt_img_entry);
USER_FUNC(evt_img_onoff);
USER_FUNC(evt_img_release);
USER_FUNC(evt_img_set_paper);
USER_FUNC(evt_img_set_paper_anim);
USER_FUNC(evt_img_set_virtual_point);
USER_FUNC(evt_img_wait_animend);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_item_get_position);
USER_FUNC(evt_item_set_position);
USER_FUNC(evt_kagemario_init_29_text_1A0C);
USER_FUNC(evt_key_get_buttontrg);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_adjust_dir);
USER_FUNC(evt_mario_balloon_off);
USER_FUNC(evt_mario_balloon_tenten);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_hello_party);
USER_FUNC(evt_mario_init_camid);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_party_door_move);
USER_FUNC(evt_mario_party_use_check);
USER_FUNC(evt_mario_set_camid);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_wait_movable);
USER_FUNC(evt_mario_wait_rideon);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mobj_set_anim);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_msg_close);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_get_reglid);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_restart_regular_event);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_paper_delete);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_get_status);
USER_FUNC(evt_party_move_behind_mario);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_set_homing_dist);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_party_yoshi_ride);
USER_FUNC(evt_pouch_add_item);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_get_haveitemcnt);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_shop_setup);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_bgmon_f);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_area_check);
USER_FUNC(evt_sub_get_dist);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_save_playtime);
USER_FUNC(evt_win_item_select);
USER_FUNC(get_item_list);
USER_FUNC(ie2_npc_disp_off);
USER_FUNC(ie2_npc_disp_on);
USER_FUNC(lect_cam_load);
USER_FUNC(lect_cam_save);
USER_FUNC(mainwindow_opendisable);
USER_FUNC(mainwindow_openenable);
USER_FUNC(mobj_ry);
static USER_FUNC(npc_process);
static USER_FUNC(set_fook_evt);
USER_FUNC(shop_item_disp_off);
USER_FUNC(shop_item_disp_on);
USER_FUNC(sleep_voice);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);
static void majin_callback(s32 type);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 door_close_se[];
extern s32 door_light[];
extern s32 door_light2[];
extern s32 door_open_se[];
extern s32 door_up_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_door_entry[];
extern s32 evt_sub_mail_event[];
extern s32 evt_sub_tree_access_entry[];
extern s32 evt_usu_kagemario_party_kill_29_data_104A8[];
extern s32 house_close_se[];
extern s32 roll_majin_lecture[];
extern s32 roll_majin_lecture_init[];

__declspec(section ".data") u64 fd_usu_01_negone_one_374;
__declspec(section ".data") s32 fd_usu_01_neg_one_382[1];
__declspec(section ".data") s32 fd_usu_01___local_PI_383[1];
__declspec(section ".data") s32 fd_usu_01___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_usu_01_one_negone_373;
__declspec(section ".data") s32 fd_usu_01___local_PIO2_384[1];
__declspec(section ".data") s32 fd_usu_01_one_381[1];
__declspec(section ".data") u64 fd_usu_01_negone_one_360;
__declspec(section ".data") s32 fd_usu_01_neg_one_365[1];
__declspec(section ".data") s32 fd_usu_01___local_PI_366[1];
__declspec(section ".data") s32 fd_usu_01___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_usu_01_one_negone_359;
__declspec(section ".data") s32 fd_usu_01___local_PIO2_367[1];
__declspec(section ".data") s32 fd_usu_01_one_364[1];
__declspec(section ".data") s32 villagerF_init[7];
s32 villagerF_talk[52];
__declspec(section ".data") s32 villagerG_init[7];
s32 villagerG_talk[52];
__declspec(section ".data") s32 villagerH_init[7];
s32 villagerH_talk[44];
s32 villagerI_init[19];
s32 villagerI_pig_init[19];
s32 villagerI_talk[57];
s32 villagerJ_init[19];
s32 villagerJ_pig_init[19];
s32 villagerJ_talk[57];
s32 shop_man_init[36];
s32 shop_man_talk[28];
__declspec(section ".data") s32 shop_woman_init[7];
s32 shop_woman_talk[163];
static s32 kizayarou_init[38];
s32 kizayarou_pig_init[14];
static s32 kizayarou_talk[33];
s32 childABC_talk_01[28];
s32 childABC_talk_02[28];
s32 childABC_talk_03[28];
s32 childABC_talk_04[28];
s32 aunt_init[22];
s32 aunt_pig_init[29];
s32 iri_20_out_house[407];
s32 iri_20_aunt_to_house[149];
s32 aunt_talk[687];
__declspec(section ".data") s32 childA_init[7];
s32 childA_talk[31];
__declspec(section ".data") s32 childB_init[7];
s32 childB_talk[31];
__declspec(section ".data") s32 childC_init[7];
s32 childC_talk[31];
s32 gatekeeper_init[38];
s32 gatekeeper_pig_init[33];
s32 gatekeeper_talk[145];
__declspec(section ".data") s32 crow_f_init[8];
__declspec(section ".data") s32 crow_g_init[8];
__declspec(section ".data") s32 crow_h_init[8];
__declspec(section ".data") s32 crow_i_init[8];
__declspec(section ".data") s32 crow_j_init[8];
static s32 musume_talk[84];
s32 musume_a_init[40];
static s32 musume_a_entry[15];
s32 musume_a_pig_entry[15];
s32 musume_b_init[40];
static s32 musume_b_entry[15];
s32 musume_b_pig_entry[15];
s32 musume_c_init[40];
static s32 musume_c_entry[15];
s32 musume_c_pig_entry[15];
static s32 urouro_move[24];
s32 urouro_move_semai[24];
static s32 npcEnt[552];
s32 village_chief_change_pig_event[166];
s32 evt_mon_open[112];
static s32 cam_up[34];
static __declspec(section ".data") s32 cam_down[8];
s32 usu01_check_vivian[36];
s32 usu01_crowFG_talk_event[355];
s32 usu01_crowHI_talk_event[250];
s32 usu01_crowJ_talk_event[226];
__declspec(section ".data") s32 minka_npc[6];
__declspec(section ".data") s32 minka_item[2];
__declspec(section ".data") s32 shop_npc[6];
__declspec(section ".data") s32 shop_mobj[4];
__declspec(section ".data") s32 shop_item[5];
static __declspec(section ".data") s32 evt_door_1_1[12];
static __declspec(section ".data") s32 evt_door_1_2[12];
static s32 evt_wall_1[28];
static __declspec(section ".data") s32 door_1_open[12];
static s32 door_1_close[14];
static s32 door_1[18];
s32 evt_door_2_1_1[15];
__declspec(section ".data") s32 evt_door_2_1_2[2];
s32 evt_wall_2_1[28];
s32 loop_msg[84];
s32 mise_kiza_msg[32];
s32 mawari_house_delay[46];
s32 door_2_1_open[23];
s32 door_2_1[18];
s32 evt_ie2_door2_1[244];
s32 evt_ie2_door2_2[226];
static __declspec(section ".data") s32 evt_door_3_1[12];
static __declspec(section ".data") s32 evt_door_3_2[12];
static s32 evt_wall_3[30];
__declspec(section ".data") s32 door_3_item[2];
static __declspec(section ".data") s32 door_3_open[12];
static s32 door_3_close[14];
static s32 door_3[18];
static s32 bero_entry_data[45];
s32 usu01_gusun[80];
s32 evt_monban_buta_main[34];
s32 evt_monban_buta[18];
s32 evt_monban_buta2[17];
s32 evt_monban_look[119];
static __declspec(section ".data") s32 lock_tbl[2];
static s32 lock_item_check[41];
s32 unlock[13];
static __declspec(section ".data") s32 obj_list[12];
static __declspec(section ".data") s32 goods_list[12];
static s32 trade_list[24];
static s32 shopper_data[38];
__declspec(section ".data") s32 shopper_talk1[11];
__declspec(section ".data") s32 shopper_talk2[11];
static s32 booboo_name[16];
__declspec(section ".data") s32 evt_roll_get[2];
static __declspec(section ".data") s32 key_tbl[2];
static s32 evt_majin[330];
static s32 evt_majin2[237];
s32 tree_onoff[57];
static __declspec(section ".data") s32 evt_ki_1[12];
static s32 evt_ki_2[20];
static s32 evt_ki_3[20];
static s32 tree_tbl[30];
__declspec(section ".data") s32 usu_01_tree_init[7];
static s32 mobj_box00[34];
s32 usu_01_init_evt[350];


__declspec(section ".data") u64 fd_usu_01_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_usu_01_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_usu_01___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_usu_01___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_usu_01_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_usu_01___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_usu_01_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_usu_01_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_usu_01_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_usu_01___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_usu_01___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_usu_01_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_usu_01___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_usu_01_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(villagerF_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｆ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(villagerF_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_msg_print, 0, STRING("stg4_usu_82"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_30"), 0, STRING("me"))
        CALL(evt_msg_select, 0, STRING("stg4_usu_30_yn"))
        CALL(evt_msg_print_add, 0, STRING("stg4_usu_30_00"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_84"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_84_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_84_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(villagerG_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｇ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(villagerG_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_msg_print, 0, STRING("stg4_usu_85"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_86"), 0, STRING("me"))
        CALL(evt_msg_select, 0, STRING("stg4_usu_86_yn"))
        CALL(evt_msg_print_add, 0, STRING("stg4_usu_86_00"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_87"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_87_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_87_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(villagerH_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｈ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(villagerH_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_msg_print, 0, STRING("stg4_usu_88"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_89"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_90"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_90_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_90_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerI_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｉ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("村人Ｉ"), 0, -2000, 0)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerI_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｉ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村人Ｉ"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerI_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_91"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_92"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_93"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_93_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_93_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerJ_init)
    CALL(evt_npc_flag_onoff, 1, STRING("村人Ｊ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("村人Ｊ"), 0, -2000, 0)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerJ_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ村人Ｊ"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ村人Ｊ"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(villagerJ_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_94"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_95"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_96"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_96_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_96_1_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(shop_man_init)
    CALL(evt_npc_flag_onoff, 1, STRING("店の主人"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_LESS(219)
        CALL(evt_npc_set_position, STRING("店の主人"), -125, 0, -475)
        CALL(evt_npc_set_ry, STRING("店の主人"), 90)
        CALL(evt_npc_flag_onoff, 1, STRING("店の主人"), 4194304)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("店の主人"), -130, 0, -480)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(shop_man_talk)
    SWITCH(GSW(0))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_61_5"), 0, STRING("店の主人"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_61_6"), 0, STRING("店の主人"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_61_7"), 0, STRING("店の主人"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(shop_woman_init)
    CALL(evt_npc_flag_onoff, 1, STRING("お店の奥さん"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(shop_woman_talk)
    SWITCH(GSW(0))
        CASE_LESS(184)
        IF_INT_EQUAL(GSWF(1925), 0)
            CALL(evt_msg_print, 0, STRING("stg4_usu_52"), 0, STRING("me"))
            WAIT_MS(200)
            CALL(evt_mario_set_pose, STRING("M_I_2"))
            WAIT_MS(1000)
            CALL(evt_msg_print, 0, STRING("stg4_usu_53"), 0, STRING("me"))
            CALL(evt_mario_set_pose, STRING("M_I_N"))
            WAIT_MS(1000)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            BEGIN_INLINE_EVENT_GET_ID(LW(10))
                CALL(sleep_voice)
            END_INLINE_EVENT
            SET_VALUE(GF(0), 0)
            CALL(evt_msg_print, 0, STRING("stg4_usu_54"), 0, STRING("me"))
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_YAWN1"), LW(0), LW(1), LW(2), 0)
                CALL(evt_mario_set_pose, STRING("M_I_5"))
                WAIT_MS(1000)
                CALL(evt_mario_set_pose, STRING("M_N_5A"))
                WAIT_MS(1000)
                SET_VALUE(GF(0), 1)
            END_INLINE_EVENT
            CALL(evt_msg_continue)
            LOOP(0)
                WAIT_FRAMES(1)
                IF_INT_EQUAL(GF(0), 1)
                    BREAK_LOOP
                END_IF
            END_LOOP
            DELETE_EVENT(LW(10))
            CALL(evt_snd_sfxoff, GW(10))
            WAIT_MS(200)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_AWAKE1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_5B"))
            WAIT_MS(600)
            CALL(evt_mario_set_pose, STRING("M_N_2"))
            WAIT_MS(600)
            CALL(evt_msg_print, 0, STRING("stg4_usu_55"), 0, STRING("me"))
            SET_VALUE(GSWF(1925), 1)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg4_usu_56"), 0, STRING("me"))
        END_IF
        CASE_LESS(185)
        CALL(evt_msg_print, 0, STRING("stg4_usu_58"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_msg_print, 0, STRING("stg4_usu_58_01"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_59"), 0, STRING("me"))
        CALL(evt_msg_continue)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(kizayarou_init)
    CALL(evt_npc_flag_onoff, 1, STRING("キザ野郎"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("キザ野郎"), 0, -2000, 0)
        CASE_LESS(219)
        CALL(evt_npc_set_position, STRING("キザ野郎"), -100, 0, -450)
        CALL(evt_npc_flag_onoff, 1, STRING("キザ野郎"), 4194304)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("キザ野郎"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(kizayarou_pig_init)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタキザ野郎"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(kizayarou_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_61_00"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_61"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(childABC_talk_01)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg4_usu_63"), 0, STRING("子供Ａ"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_msg_print, 0, STRING("stg4_usu_64"), 0, STRING("子供Ｂ"))
    END_INLINE_EVENT
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg4_usu_65"), 0, STRING("子供Ｃ"))
    RETURN
EVT_END()

EVT_BEGIN(childABC_talk_02)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg4_usu_79"), 0, STRING("子供Ａ"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_msg_print, 0, STRING("stg4_usu_80"), 0, STRING("子供Ｂ"))
    END_INLINE_EVENT
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg4_usu_81"), 0, STRING("子供Ｃ"))
    RETURN
EVT_END()

EVT_BEGIN(childABC_talk_03)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg4_usu_81_2"), 0, STRING("子供Ａ"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_msg_print, 0, STRING("stg4_usu_81_3"), 0, STRING("子供Ｂ"))
    END_INLINE_EVENT
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg4_usu_81_4"), 0, STRING("子供Ｃ"))
    RETURN
EVT_END()

EVT_BEGIN(childABC_talk_04)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg4_usu_81_4_2"), 0, STRING("子供Ａ"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_msg_print, 0, STRING("stg4_usu_81_4_3"), 0, STRING("子供Ｂ"))
    END_INLINE_EVENT
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg4_usu_81_4_4"), 0, STRING("子供Ｃ"))
    RETURN
EVT_END()

EVT_BEGIN(aunt_init)
    CALL(evt_npc_flag_onoff, 1, STRING("おばさん"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        IF_INT_EQUAL(GSWF(1927), 1)
            CALL(evt_npc_set_position, STRING("おばさん"), 0, -2000, 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(aunt_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタおばさん"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(200)
        IF_INT_EQUAL(GSWF(1927), 0)
            CALL(evt_npc_set_position, STRING("ブタおばさん"), 0, -2000, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタおばさん"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(iri_20_out_house)
    CALL(evt_mario_key_onoff, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set_xyz, -420, 1, 0, 0, 150, 11)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(14), 0)
        SPAWN_EVENT(PTR(door_light2))
    END_IF
    SPAWN_EVENT(PTR(door_up_se))
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(3)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(8))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(3)
            END_IF
        END_INLINE_EVENT
    END_IF
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(9), 0)
        BEGIN_INLINE_EVENT
            WAIT_MS(400)
            SPAWN_EVENT(PTR(house_close_se))
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            SET_VALUE(LW(6), 0)
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 3)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(9))
            SET_VALUE(LW(6), 1)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(2)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    IF_INT_EQUAL(LW(14), 0)
        SPAWN_EVENT(PTR(door_light))
    END_IF
    SPAWN_EVENT(PTR(door_open_se))
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 2)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(1)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    CALL(evt_door_param, LW(0), 5, LW(1), LW(2), LW(3))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("おばさん"), LW(1), LW(3), 0, 60, 0)
        CALL(evt_npc_move_position, STRING("おばさん"), -368, 0, 0, 60, 0)
        CALL(evt_npc_set_ry, STRING("おばさん"), 270)
        WAIT_MS(300)
    END_INLINE_EVENT
    CALL(evt_mario_party_door_move, LW(1), LW(3), 60)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -420, 0, 60)
        CALL(evt_mario_set_dir_npc, STRING("おばさん"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -450, -1, 60)
        CALL(evt_party_set_dir_npc, 0, STRING("おばさん"))
    END_INLINE_EVENT
    WAIT_MS(2000)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            SPAWN_EVENT(PTR(door_close_se))
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 3)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(0)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    CALL(evt_cam3d_evt_xyz_off, 100, 11)
    CALL(door_dark_flag, LW(0), 0)
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        IF_INT_NOT_EQUAL(LW(15), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, LW(1), 1)
        END_IF
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 2048)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 4096)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 0)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 2048)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 2048)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 4096)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_load_mapflag, LW(1))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(iri_20_aunt_to_house)
    CALL(evt_npc_move_position, STRING("おばさん"), -390, -40, 0, 60, 0)
    SET_VALUE(LW(0), PTR(door_1))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_move_position, STRING("me"), -390, -20, 0, 60, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1024)
    SPAWN_EVENT(PTR(door_open_se))
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 0)
            SET_VALUE(LF(0), 0)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(0)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("おばさん"), -390, -185, 0, 60, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            SPAWN_EVENT(PTR(door_close_se))
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 1)
            SET_VALUE(LF(0), 0)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(1)
            END_IF
        END_INLINE_EVENT
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(aunt_talk)
    IF_INT_EQUAL(GSW(1420), 20)
        IF_INT_EQUAL(GSWF(5405), 0)
            CALL(evt_msg_print, 0, STRING("irai_20_001"), 0, STRING("me"))
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32)
            BEGIN_INLINE_EVENT
                CALL(evt_npc_move_position, STRING("me"), -390, -130, 0, 60, 0)
            END_INLINE_EVENT
            CALL(evt_mario_mov_pos2, -390, -100, 60)
            WAIT_MS(500)
            CALL(evt_npc_flag_onoff, 0, STRING("me"), 32)
            SET_VALUE(LW(0), PTR(door_1))
            SET_VALUE(LW(14), 0)
            SET_VALUE(LW(15), 0)
            CALL_CHILD(PTR(iri_20_out_house))
            CALL(evt_snd_bgmoff_f, 1024, 2000)
            WAIT_MS(1000)
            BEGIN_INLINE_EVENT
                WAIT_MS(2000)
                CALL(evt_snd_bgmoff, 1024)
                CALL(evt_snd_bgmon, 1, STRING("BGM_EVT_ORGEL1"))
            END_INLINE_EVENT
            CALL(evt_msg_print, 0, STRING("irai_20_002"), 0, STRING("me"))
            CALL(evt_mario_set_pose, STRING("M_N_1"))
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("irai_20_003"), 0, STRING("me"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_snd_bgmoff_f, 513, 3000)
            CALL_CHILD(PTR(iri_20_aunt_to_house))
            CALL(evt_snd_bgmoff_f, 513, 2000)
            CALL(evt_snd_bgmon_f, 288, 0, 2000)
            CALL(evt_snd_bgmon, 160, 0)
            CALL(evt_snd_envon, 160, 0)
            CALL(evt_snd_env_lpf, 0, 0)
            SET_VALUE(GSWF(5405), 1)
            ELSE
            IF_INT_EQUAL(GSWF(5406), 0)
                CALL(evt_msg_print, 0, STRING("irai_20_004"), 0, STRING("me"))
                ELSE
                CALL(evt_npc_flag_onoff, 1, STRING("おばさん"), 32)
                CALL(evt_npc_flag_onoff, 1, STRING("子供Ｂ"), 32)
                SET_VALUE(GF(0), 1)
                BEGIN_INLINE_EVENT
                    CALL(evt_party_move_pos2, 0, -443, -140, 60)
                    CALL(evt_party_set_dir_npc, 0, STRING("おばさん"))
                    WAIT_MS(300)
                    SET_VALUE(GF(0), 0)
                END_INLINE_EVENT
                CALL(evt_mario_mov_pos2, -415, -150, 60)
                CALL(evt_mario_set_dir_npc, STRING("おばさん"))
                WAIT_MS(400)
                CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
                WAIT_FRAMES(1)
                CALL(evt_npc_wait_pera, STRING("me"))
                WAIT_WHILE(GF(0))
                CALL(evt_npc_flag_onoff, 0, STRING("おばさん"), 32)
                CALL(evt_npc_flag_onoff, 0, STRING("子供Ｂ"), 32)
                CALL(evt_msg_print, 0, STRING("irai_20_005"), 0, STRING("me"))
                CALL(evt_msg_select, 0, STRING("irai_20_006"))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(evt_msg_print_add, 0, STRING("irai_20_007"))
                    ELSE
                    CALL(evt_msg_continue)
                    CALL(evt_mario_set_pose, STRING("M_I_2"))
                    WAIT_MS(1200)
                    CALL(evt_mario_set_pose, STRING("M_S_1"))
                    CALL(evt_msg_print, 0, STRING("irai_20_008"), 0, STRING("me"))
                END_IF
                BEGIN_INLINE_EVENT
                    CALL(evt_msg_print, 0, STRING("irai_20_009"), 0, STRING("子供Ａ"))
                END_INLINE_EVENT
                BEGIN_INLINE_EVENT
                    WAIT_MS(500)
                    CALL(evt_msg_print, 0, STRING("irai_20_010"), 0, STRING("子供Ｂ"))
                END_INLINE_EVENT
                WAIT_MS(1000)
                CALL(evt_msg_print, 0, STRING("irai_20_011"), 0, STRING("子供Ｃ"))
                CALL(evt_msg_print, 0, STRING("irai_20_012"), 0, STRING("me"))
                CALL(evt_pouch_get_haveitemcnt, LW(0))
                CALL(evt_pouch_check_item, 1, LW(1))
                IF_INT_EQUAL(LW(1), 0)
                    SET_VALUE(LW(1), 10)
                    ELSE
                    SET_VALUE(LW(1), 20)
                END_IF
                IF_INT_LESS(LW(0), LW(1))
                    CALL(evt_msg_continue)
                    CALL(evt_item_entry, STRING("sd"), 217, 0, -1000, 0, 17, -1, 0)
                    CALL(evt_item_get_item, STRING("sd"))
                    CALL(evt_item_get_item_end_wait, STRING("sd"))
                    SET_VALUE(GSWF(1938), 1)
                    ELSE
                    CALL(evt_msg_print_add, 0, STRING("irai_20_012_1"))
                    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
                    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
                    CALL(evt_npc_move_position, STRING("me"), -363, -152, 0, 40, 0)
                    WAIT_MS(300)
                    CALL(evt_item_entry, STRING("iri_20"), 217, -345, 20, -132, 16, GSWF(1938), 0)
                    WAIT_MS(300)
                    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, 40, 0)
                    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
                END_IF
                CALL(evt_msg_print, 0, STRING("irai_20_014"), 0, STRING("me"))
                CALL(evt_sub_save_playtime, GSW(1453))
                SET_VALUE(GSW(1420), 0)
                SET_VALUE(GSWF(5394), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
                BEGIN_INLINE_EVENT
                    CALL(evt_msg_print, 0, STRING("irai_20_015"), 0, STRING("子供Ａ"))
                END_INLINE_EVENT
                BEGIN_INLINE_EVENT
                    WAIT_MS(500)
                    CALL(evt_msg_print, 0, STRING("irai_20_016"), 0, STRING("子供Ｂ"))
                END_INLINE_EVENT
                BEGIN_INLINE_EVENT
                    WAIT_MS(1000)
                    CALL(evt_msg_print, 0, STRING("irai_20_017"), 0, STRING("子供Ｃ"))
                END_INLINE_EVENT
            END_IF
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(200)
        IF_INT_EQUAL(GSWF(1927), 0)
            CALL(evt_msg_print, 0, STRING("stg4_usu_62"), 0, STRING("me"))
            CALL_CHILD(PTR(childABC_talk_01))
            WAIT_MS(1400)
            CALL(evt_msg_print, 0, STRING("stg4_usu_66"), 0, STRING("me"))
            CALL(evt_msg_select, 0, STRING("stg4_usu_66_yn"))
            CALL(evt_msg_continue)
            WAIT_FRAMES(1)
            CALL(evt_pouch_get_haveitemcnt, LW(1))
            IF_INT_EQUAL(LW(1), 0)
                SET_VALUE(LW(0), 1)
            END_IF
            IF_INT_EQUAL(LW(0), 0)
                CALL(get_item_list, LW(0))
                LOOP(0)
                    CALL(evt_win_item_select, 0, LW(0), LW(1), 0)
                    IF_INT_NOT_EQUAL(LW(1), -1)
                        CALL(check_tabemono, LW(1), LW(2))
                        IF_INT_EQUAL(LW(2), 1)
                            CALL(evt_pouch_remove_item, LW(1), LW(2))
                            BREAK_LOOP
                            ELSE
                            CALL(evt_msg_print, 0, STRING("stg4_usu_67"), 0, 0)
                        END_IF
                        ELSE
                        BREAK_LOOP
                    END_IF
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(delete_item_list, LW(0))
                IF_INT_NOT_EQUAL(LW(1), -1)
                    CALL(evt_msg_print, 0, STRING("stg4_usu_68"), 0, STRING("me"))
                    CALL(evt_item_entry, STRING("orei"), 130, 0, 0, 0, 17, -1, 0)
                    CALL(evt_item_get_item, STRING("orei"))
                    CALL(evt_item_get_item_end_wait, STRING("orei"))
                    CALL(evt_msg_print, 0, STRING("stg4_usu_69"), 0, STRING("me"))
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg4_usu_70"), 0, STRING("me"))
                END_IF
                ELSE
                CALL(evt_msg_print, 0, STRING("stg4_usu_70"), 0, STRING("me"))
            END_IF
            WAIT_MS(500)
            CALL(evt_snd_sfxon, STRING("SFX_STG4_TEMPLE_BELL1"), 0)
            WAIT_MS(2000)
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CHANGE_PIG1"), LW(0), LW(1), LW(2), 0)
            BEGIN_INLINE_EVENT
                ADD(LW(2), 20)
                CALL(evt_eff, 0, STRING("kemuri_test"), 7, LW(0), LW(1), LW(2), FLOAT(1.5f), 0, 0, 0, 0, 0, 0, 0)
            END_INLINE_EVENT
            WAIT_MS(300)
            CALL(evt_npc_set_position, STRING("ブタおばさん"), LW(0), LW(1), LW(2))
            CALL(evt_npc_set_position, STRING("me"), 0, -2000, 0)
            CALL(evt_npc_get_reglid, STRING("ブタおばさん"), LW(0))
            DELETE_EVENT(LW(0))
            CALL(evt_npc_restart_regular_event, STRING("ブタおばさん"))
            BEGIN_INLINE_EVENT
                CALL(evt_msg_print, 0, STRING("stg4_usu_71"), 0, STRING("子供Ａ"))
            END_INLINE_EVENT
            BEGIN_INLINE_EVENT
                WAIT_MS(400)
                CALL(evt_msg_print, 0, STRING("stg4_usu_72"), 0, STRING("子供Ｂ"))
            END_INLINE_EVENT
            BEGIN_INLINE_EVENT
                WAIT_MS(600)
                CALL(evt_msg_print, 0, STRING("stg4_usu_73"), 0, STRING("子供Ｃ"))
            END_INLINE_EVENT
            SET_VALUE(GSWF(1927), 1)
            ELSE
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_msg_print, 0, STRING("stg4_usu_73_01"), 0, STRING("me"))
        END_IF
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_77"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_78"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_81_1"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_81_4_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(childA_init)
    CALL(evt_npc_flag_onoff, 1, STRING("子供Ａ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(childA_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        IF_INT_EQUAL(GSWF(1927), 1)
            CALL(evt_msg_print, 0, STRING("stg4_usu_74"), 0, STRING("me"))
            ELSE
            CALL_CHILD(PTR(childABC_talk_01))
        END_IF
        CASE_LESS(222)
        CALL_CHILD(PTR(childABC_talk_02))
        CASE_LESS_OR_EQUAL(402)
        CALL_CHILD(PTR(childABC_talk_03))
        CASE_DEFAULT
        CALL_CHILD(PTR(childABC_talk_04))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(childB_init)
    CALL(evt_npc_flag_onoff, 1, STRING("子供Ｂ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(childB_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        IF_INT_EQUAL(GSWF(1927), 1)
            CALL(evt_msg_print, 0, STRING("stg4_usu_75"), 0, STRING("me"))
            ELSE
            CALL_CHILD(PTR(childABC_talk_01))
        END_IF
        CASE_LESS(222)
        CALL_CHILD(PTR(childABC_talk_02))
        CASE_LESS_OR_EQUAL(402)
        CALL_CHILD(PTR(childABC_talk_03))
        CASE_DEFAULT
        CALL_CHILD(PTR(childABC_talk_04))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(childC_init)
    CALL(evt_npc_flag_onoff, 1, STRING("子供Ｃ"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(childC_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        IF_INT_EQUAL(GSWF(1927), 1)
            CALL(evt_msg_print, 0, STRING("stg4_usu_76"), 0, STRING("me"))
            ELSE
            CALL_CHILD(PTR(childABC_talk_01))
        END_IF
        CASE_LESS(222)
        CALL_CHILD(PTR(childABC_talk_02))
        CASE_LESS_OR_EQUAL(402)
        CALL_CHILD(PTR(childABC_talk_03))
        CASE_DEFAULT
        CALL_CHILD(PTR(childABC_talk_04))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(gatekeeper_init)
    CALL(evt_npc_flag_onoff, 1, STRING("門番"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(181)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_npc_set_position, STRING("門番"), 400, 0, -55)
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("門番"), 0, -2000, 0)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("門番"), 400, 0, -55)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(gatekeeper_pig_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ブタ門番"), 1536)
    SWITCH(GSW(0))
        CASE_LESS(181)
        CALL(evt_npc_set_position, STRING("ブタ門番"), 0, -2000, 0)
        CASE_LESS(200)
        CALL(evt_npc_set_position, STRING("ブタ門番"), 400, 0, -55)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタ門番"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(gatekeeper_talk)
    SWITCH(GSW(0))
        CASE_LESS(179)
        CALL(evt_mario_mov_pos2, 350, -50, 120)
        WAIT_FRAMES(1)
        CALL(evt_mario_set_dir, 90, 300, 0)
        CALL(evt_party_move_behind_mario, 0)
        CALL(evt_cam3d_evt_set, 372, 124, 321, 372, 57, -61, 500, 11)
        WAIT_MS(500)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        CALL(evt_msg_print, 0, STRING("stg4_usu_44"), 0, STRING("me"))
        CALL(evt_cam3d_evt_set, 342, 124, 321, 342, 57, -61, 500, 11)
        WAIT_MS(500)
        CALL(evt_party_stop, 0)
        WAIT_MS(200)
        CALL(evt_msg_print_party, STRING("stg4_usu_45"))
        CALL(evt_party_run, 0)
        CALL(evt_cam3d_evt_off, 1000, 11)
        SPAWN_EVENT(PTR(village_chief_change_pig_event))
        SET_VALUE(GSW(0), 179)
        RETURN
        CASE_LESS(180)
        CALL(evt_msg_print, 0, STRING("stg4_usu_45_01"), 0, STRING("me"))
        CASE_LESS(181)
        CALL(evt_msg_print, 0, STRING("stg4_usu_46"), 0, STRING("me"))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_48"), 0, STRING("me"))
        CASE_LESS(219)
        CALL(evt_msg_print, 0, STRING("stg4_usu_49"), 0, STRING("me"))
        CASE_LESS(222)
        CALL(evt_msg_print, 0, STRING("stg4_usu_49_1"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg4_usu_49_2"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_usu_49_2_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_f_init)
    CALL(evt_npc_set_position, STRING("me"), 275, 83, 355)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_g_init)
    CALL(evt_npc_set_position, STRING("me"), 250, 112, 355)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_h_init)
    CALL(evt_npc_set_position, STRING("me"), -147, 110, 346)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_i_init)
    CALL(evt_npc_set_position, STRING("me"), -175, 110, 348)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(crow_j_init)
    CALL(evt_npc_set_position, STRING("me"), -195, 100, -157)
    RETURN
EVT_END()

static EVT_BEGIN(musume_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("ブタ３人娘Ａ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_01"), 0, STRING("ブタ３人娘Ａ"))
        CALL(evt_npc_get_position, STRING("ブタ３人娘Ｂ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_02"), 0, STRING("ブタ３人娘Ｂ"))
        CALL(evt_npc_get_position, STRING("ブタ３人娘Ｃ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_03"), 0, STRING("ブタ３人娘Ｃ"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_04"), 0, STRING("３人娘Ａ"))
        CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_05"), 0, STRING("３人娘Ｂ"))
        CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_06"), 0, STRING("３人娘Ｃ"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(musume_a_init)
    CALL(evt_npc_set_position, LW(0), -440, 0, 180)
    CALL(evt_npc_set_ry, LW(0), 90)
    CALL(evt_npc_flag_onoff, 1, LW(0), 1536)
    CALL(evt_npc_change_interrupt, LW(0), 6, PTR(musume_talk))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, LW(0), 32768)
        CALL(evt_seq_wait, 2)
        CALL(evt_npc_wait_pera, LW(0))
        CALL(evt_npc_flag_onoff, 0, LW(0), 32768)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(musume_a_entry)
    CALL(evt_npc_entry, STRING("３人娘Ａ"), STRING("c_dance_r"))
    CALL(evt_npc_set_tribe, STRING("３人娘Ａ"), STRING("踊り子"))
    SET_VALUE(LW(0), STRING("３人娘Ａ"))
    CALL_CHILD(PTR(musume_a_init))
    RETURN
EVT_END()

EVT_BEGIN(musume_a_pig_entry)
    CALL(evt_npc_entry, STRING("ブタ３人娘Ａ"), STRING("c_bubusan"))
    CALL(evt_npc_set_tribe, STRING("ブタ３人娘Ａ"), STRING("ブタ"))
    SET_VALUE(LW(0), STRING("ブタ３人娘Ａ"))
    CALL_CHILD(PTR(musume_a_init))
    RETURN
EVT_END()

EVT_BEGIN(musume_b_init)
    CALL(evt_npc_set_position, LW(0), -410, 0, 150)
    CALL(evt_npc_set_ry, LW(0), 90)
    CALL(evt_npc_flag_onoff, 1, LW(0), 1536)
    CALL(evt_npc_change_interrupt, LW(0), 6, PTR(musume_talk))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, LW(0), 32768)
        CALL(evt_seq_wait, 2)
        CALL(evt_npc_wait_pera, LW(0))
        CALL(evt_npc_flag_onoff, 0, LW(0), 32768)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(musume_b_entry)
    CALL(evt_npc_entry, STRING("３人娘Ｂ"), STRING("c_dance_p"))
    CALL(evt_npc_set_tribe, STRING("３人娘Ｂ"), STRING("踊り子ピンク"))
    SET_VALUE(LW(0), STRING("３人娘Ｂ"))
    CALL_CHILD(PTR(musume_b_init))
    RETURN
EVT_END()

EVT_BEGIN(musume_b_pig_entry)
    CALL(evt_npc_entry, STRING("ブタ３人娘Ｂ"), STRING("c_bubusan"))
    CALL(evt_npc_set_tribe, STRING("ブタ３人娘Ｂ"), STRING("ブタ"))
    SET_VALUE(LW(0), STRING("ブタ３人娘Ｂ"))
    CALL_CHILD(PTR(musume_b_init))
    RETURN
EVT_END()

EVT_BEGIN(musume_c_init)
    CALL(evt_npc_set_position, LW(0), -380, 0, 180)
    CALL(evt_npc_set_ry, LW(0), 90)
    CALL(evt_npc_flag_onoff, 1, LW(0), 1536)
    CALL(evt_npc_change_interrupt, LW(0), 6, PTR(musume_talk))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, LW(0), 32768)
        CALL(evt_seq_wait, 2)
        CALL(evt_npc_wait_pera, LW(0))
        CALL(evt_npc_flag_onoff, 0, LW(0), 32768)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(musume_c_entry)
    CALL(evt_npc_entry, STRING("３人娘Ｃ"), STRING("c_dance_k"))
    CALL(evt_npc_set_tribe, STRING("３人娘Ｃ"), STRING("踊り子黄緑"))
    SET_VALUE(LW(0), STRING("３人娘Ｃ"))
    CALL_CHILD(PTR(musume_c_init))
    RETURN
EVT_END()

EVT_BEGIN(musume_c_pig_entry)
    CALL(evt_npc_entry, STRING("ブタ３人娘Ｃ"), STRING("c_bubusan"))
    CALL(evt_npc_set_tribe, STRING("ブタ３人娘Ｃ"), STRING("ブタ"))
    SET_VALUE(LW(0), STRING("ブタ３人娘Ｃ"))
    CALL_CHILD(PTR(musume_c_init))
    RETURN
EVT_END()

static EVT_BEGIN(urouro_move)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1073741824)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(50.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(urouro_move_semai)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1073741824)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(15.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"村人Ｆ"*/"\x91\xBA\x90\x6C\x82\x65", 1074267648, 0, (s32)villagerF_init, 0, (s32)villagerF_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"村人Ｇ"*/"\x91\xBA\x90\x6C\x82\x66",
    525824, 0, (s32)villagerG_init, (s32)urouro_move, (s32)villagerG_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"村人Ｈ"*/"\x91\xBA\x90\x6C\x82\x67", 1074267648,
    0, (s32)villagerH_init, 0, (s32)villagerH_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"村人Ｉ"*/"\x91\xBA\x90\x6C\x82\x68", 1074267648, 0,
    (s32)villagerI_init, 0, (s32)villagerI_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"村人Ｊ"*/"\x91\xBA\x90\x6C\x82\x69", 525824, 0, (s32)villagerJ_init,
    (s32)urouro_move, (s32)villagerJ_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"店の主人"*/"\x93\x58\x82\xCC\x8E\xE5\x90\x6C", 1074267648, 0, (s32)shop_man_init, 0,
    (s32)shop_man_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"お店の奥さん"*/"\x82\xA8\x93\x58\x82\xCC\x89\x9C\x82\xB3\x82\xF1", 1074267648, 0, (s32)shop_woman_init, 0, (s32)shop_woman_talk,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"キザ野郎"*/"\x83\x4C\x83\x55\x96\xEC\x98\x59", 1074267648, 0, (s32)kizayarou_init, 0, (s32)kizayarou_talk, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"おばさん"*/"\x82\xA8\x82\xCE\x82\xB3\x82\xF1", 1074267648, 0, (s32)aunt_init, 0, (s32)aunt_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"子供Ａ"*/"\x8E\x71\x8B\x9F\x82\x60",
    1074267648, 0, (s32)childA_init, 0, (s32)childA_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"子供Ｂ"*/"\x8E\x71\x8B\x9F\x82\x61", 1074267648,
    0, (s32)childB_init, 0, (s32)childB_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"子供Ｃ"*/"\x8E\x71\x8B\x9F\x82\x62", 1074267648, 0,
    (s32)childC_init, 0, (s32)childC_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"門番"*/"\x96\xE5\x94\xD4", 1074267648, 0, (s32)gatekeeper_init,
    0, (s32)gatekeeper_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"ブタキザ野郎"*/"\x83\x75\x83\x5E\x83\x4C\x83\x55\x96\xEC\x98\x59", 525824, 0, (s32)kizayarou_pig_init, (s32)urouro_move,
    (s32)kizayarou_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"ブタおばさん"*/"\x83\x75\x83\x5E\x82\xA8\x82\xCE\x82\xB3\x82\xF1", 525824, 0, (s32)aunt_pig_init, (s32)urouro_move, (s32)aunt_talk,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ブタ門番"*/"\x83\x75\x83\x5E\x96\xE5\x94\xD4", 525824, 0, (s32)gatekeeper_pig_init, 0, (s32)gatekeeper_talk, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"ブタ村人Ｉ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x68", 525824, 0, (s32)villagerI_pig_init, (s32)urouro_move, (s32)villagerI_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ブタ村人Ｊ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x69",
    525824, 0, (s32)villagerJ_pig_init, (s32)urouro_move, (s32)villagerJ_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"カラスＦ"*/"\x83\x4A\x83\x89\x83\x58\x82\x65", 1073743360,
    0, (s32)crow_f_init, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"カラスＧ"*/"\x83\x4A\x83\x89\x83\x58\x82\x66", 1073743360, 0,
    (s32)crow_g_init, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"カラスＨ"*/"\x83\x4A\x83\x89\x83\x58\x82\x67", 1073743360, 0, (s32)crow_h_init,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"カラスＩ"*/"\x83\x4A\x83\x89\x83\x58\x82\x68", 1073743360, 0, (s32)crow_i_init, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"カラスＪ"*/"\x83\x4A\x83\x89\x83\x58\x82\x69", 1073743360, 0, (s32)crow_j_init, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(village_chief_change_pig_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS_OR_EQUAL(LW(0), -300)
        GOTO(10)
    END_IF
    GOTO(0)
    LABEL(10)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_snd_sfxon, STRING("SFX_STG4_TEMPLE_BELL1"), 0)
    WAIT_MS(500)
    CALL(evt_mario_get_party, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mario_hello_party, 0, 1)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_party_get_pos, 0, LW(3), LW(4), LW(5))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_mario_set_dir, 90, 100, 0)
        ELSE
        CALL(evt_mario_set_dir, 270, 100, 0)
    END_IF
    ADD(LW(0), LW(3))
    DIVIDE(LW(0), 2)
    ADD(LW(2), LW(5))
    DIVIDE(LW(2), 2)
    SET_VALUE(LW(4), LW(1))
    SET_VALUE(LW(5), LW(2))
    ADD(LW(1), 35)
    SUBTRACT(LW(2), 13)
    ADD(LW(4), 100)
    ADD(LW(5), 330)
    CALL(evt_cam3d_evt_set, LW(0), LW(4), LW(5), LW(0), LW(1), LW(2), 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg4_usu_50"))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_mon_open)
    IF_INT_LESS(GSW(0), 182)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING("stg4_usu_45_02"), 0, STRING("門番"))
        CALL(evt_mario_key_onoff, 1)
        ELSE
        CALL(evt_cam_letter_box_disable, 1)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_monato"), 1)
        CALL(evt_mapobj_get_position, STRING("S_mon01"), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_FENCE_OPEN1"), LW(10), LW(11), LW(12), LW(9))
        CALL(evt_sub_intpl_msec_init, 11, 0, 900, 1000)
        LABEL(123)
        CALL(evt_sub_intpl_msec_get_value)
        SET_FLOAT_VALUE(LW(2), LW(0))
        MULTIPLY_FLOAT(LW(2), FLOAT(0.0546875f))
        SET_FLOAT_VALUE(LW(3), LW(0))
        MULTIPLY_FLOAT(LW(3), FLOAT(-0.09375f))
        CALL(evt_mapobj_rotate, 1, STRING("S_mon01"), 0, LW(2), 0)
        CALL(evt_mapobj_rotate, 1, STRING("S_mon02"), 0, LW(3), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(123)
        END_IF
        CALL(evt_hitobj_onoff, STRING("A_mon"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_mon02"), 1, 1)
        CALL(evt_snd_sfxoff, LW(9))
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_cam_letter_box_disable, 0)
        SET_VALUE(GSW(0), 183)
        CALL(evt_exit_case_evt)
    END_IF
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

EVT_BEGIN(usu01_check_vivian)
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
        SET_VALUE(GW(2), 0)
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(usu01_crowFG_talk_event)
    SET_VALUE(LW(15), 0)
    LABEL(0)
    IF_INT_NOT_EQUAL(GW(0), 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("カラスＦ"), LW(3), LW(4), LW(5))
    CALL(evt_sub_area_check, 1, LW(3), LW(5), 20, LW(0), LW(2), LW(6))
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
                CALL(evt_npc_get_position, STRING("カラスＦ"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
                CALL(evt_msg_print, 0, STRING("stg4_jin_153"), 0, STRING("カラスＦ"))
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
            CALL(evt_npc_get_position, STRING("カラスＦ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
            SWITCH(GSW(0))
                CASE_LESS(210)
                CALL(evt_msg_print, 0, STRING("stg4_usu_137"), 0, STRING("カラスＦ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_138"), 0, STRING("カラスＧ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_139"), 0, STRING("カラスＦ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_140"), 0, STRING("カラスＧ"))
                CALL_CHILD(PTR(cam_down))
                IF_INT_EQUAL(GSWF(1928), 0)
                    CALL(evt_party_cont_onoff, 0, 1)
                    LOOP(0)
                        CALL(evt_party_get_status, 6, LW(0))
                        IF_INT_EQUAL(LW(0), 0)
                            BREAK_LOOP
                        END_IF
                        WAIT_FRAMES(1)
                    END_LOOP
                    WAIT_MS(400)
                    CALL(evt_party_stop, 0)
                    CALL(evt_party_move_pos2, 0, 280, 350, FLOAT(80.0f))
                    WAIT_FRAMES(1)
                    CALL(evt_party_set_dir, 0, 270, 200)
                    CALL(evt_mario_set_dir, 90, 200, 0)
                    WAIT_MS(300)
                    CALL(evt_msg_print_party, STRING("stg4_usu_149"))
                    WAIT_MS(300)
                    CALL(evt_mario_set_pose, STRING("M_N_2"))
                    WAIT_MS(500)
                    CALL(evt_mario_set_pose, STRING("M_S_1"))
                    CALL(evt_msg_print_party, STRING("stg4_usu_150"))
                    WAIT_MS(300)
                    SET_VALUE(GSWF(1928), 1)
                    CALL(evt_party_cont_onoff, 0, 0)
                    CALL(evt_party_run, 0)
                END_IF
                CASE_LESS(222)
                CALL(evt_msg_print, 0, STRING("stg4_usu_141"), 0, STRING("カラスＦ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_142"), 0, STRING("カラスＧ"))
                CALL_CHILD(PTR(cam_down))
                CASE_LESS_OR_EQUAL(402)
                CALL(evt_msg_print, 0, STRING("stg4_usu_142_1"), 0, STRING("カラスＦ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_142_2"), 0, STRING("カラスＧ"))
                CALL_CHILD(PTR(cam_down))
                CASE_DEFAULT
                CALL(evt_msg_print, 0, STRING("stg4_usu_142_2_1"), 0, STRING("カラスＦ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_142_2_2"), 0, STRING("カラスＧ"))
                CALL_CHILD(PTR(cam_down))
            END_SWITCH
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(evt_mario_key_onoff, 1)
            CALL(mainwindow_openenable)
            SET_VALUE(GW(0), 1)
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(usu01_crowHI_talk_event)
    SET_VALUE(LW(15), 0)
    LABEL(0)
    IF_INT_NOT_EQUAL(GW(1), 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("カラスＨ"), LW(3), LW(4), LW(5))
    CALL(evt_sub_area_check, 1, LW(3), LW(5), 80, LW(0), LW(2), LW(6))
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
                CALL_CHILD(PTR(cam_up))
                CALL(evt_npc_get_position, STRING("カラスＨ"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
                CALL(evt_msg_print, 0, STRING("stg4_jin_153"), 0, STRING("カラスＨ"))
                CALL_CHILD(PTR(cam_down))
                CALL(evt_mario_key_onoff, 1)
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
            CALL(evt_npc_get_position, STRING("カラスＨ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
            SWITCH(GSW(0))
                CASE_LESS(210)
                CALL(evt_msg_print, 0, STRING("stg4_usu_143"), 0, STRING("カラスＨ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_144"), 0, STRING("カラスＩ"))
                CASE_LESS(222)
                CALL(evt_msg_print, 0, STRING("stg4_usu_145"), 0, STRING("カラスＨ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_146"), 0, STRING("カラスＩ"))
                CASE_LESS_OR_EQUAL(402)
                CALL(evt_msg_print, 0, STRING("stg4_usu_146_1"), 0, STRING("カラスＨ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_146_2"), 0, STRING("カラスＩ"))
                CASE_DEFAULT
                CALL(evt_msg_print, 0, STRING("stg4_usu_146_2_1"), 0, STRING("カラスＨ"))
                CALL(evt_msg_print, 0, STRING("stg4_usu_146_2_2"), 0, STRING("カラスＩ"))
            END_SWITCH
            CALL_CHILD(PTR(cam_down))
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(evt_mario_key_onoff, 1)
            CALL(mainwindow_openenable)
            SET_VALUE(GW(1), 1)
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(usu01_crowJ_talk_event)
    SET_VALUE(LW(15), 0)
    LABEL(0)
    IF_INT_NOT_EQUAL(GW(2), 0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("カラスＪ"), LW(3), LW(4), LW(5))
    CALL(evt_sub_area_check, 1, LW(3), LW(5), 20, LW(0), LW(2), LW(6))
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
                CALL_CHILD(PTR(cam_up))
                CALL(evt_npc_get_position, STRING("カラスＪ"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
                CALL(evt_msg_print, 0, STRING("stg4_jin_153"), 0, STRING("カラスＪ"))
                CALL_CHILD(PTR(cam_down))
                CALL(evt_mario_key_onoff, 1)
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
            CALL(evt_npc_get_position, STRING("カラスＪ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_CROW_HOWL1"), LW(0), LW(1), LW(2), 0)
            SWITCH(GSW(0))
                CASE_LESS(210)
                CALL(evt_msg_print, 0, STRING("stg4_usu_147"), 0, STRING("カラスＪ"))
                CASE_LESS(222)
                CALL(evt_msg_print, 0, STRING("stg4_usu_148"), 0, STRING("カラスＪ"))
                CASE_LESS_OR_EQUAL(402)
                CALL(evt_msg_print, 0, STRING("stg4_usu_148_1"), 0, STRING("カラスＪ"))
                CASE_DEFAULT
                CALL(evt_msg_print, 0, STRING("stg4_usu_148_1_1"), 0, STRING("カラスＪ"))
            END_SWITCH
            CALL_CHILD(PTR(cam_down))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(mainwindow_openenable)
            SET_VALUE(GW(2), 1)
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

__declspec(section ".data") s32 minka_npc[] = {
    (s32)/*"おばさん"*/"\x82\xA8\x82\xCE\x82\xB3\x82\xF1", (s32)/*"ブタおばさん"*/"\x83\x75\x83\x5E\x82\xA8\x82\xCE\x82\xB3\x82\xF1", (s32)/*"子供Ａ"*/"\x8E\x71\x8B\x9F\x82\x60", (s32)/*"子供Ｂ"*/"\x8E\x71\x8B\x9F\x82\x61", (s32)/*"子供Ｃ"*/"\x8E\x71\x8B\x9F\x82\x62", 0,
};

__declspec(section ".data") s32 minka_item[] = {
    (s32)"iri_20", 0,
};

__declspec(section ".data") s32 shop_npc[] = {
    (s32)/*"お店の奥さん"*/"\x82\xA8\x93\x58\x82\xCC\x89\x9C\x82\xB3\x82\xF1", (s32)/*"キザ野郎"*/"\x83\x4C\x83\x55\x96\xEC\x98\x59", (s32)/*"ブタキザ野郎"*/"\x83\x75\x83\x5E\x83\x4C\x83\x55\x96\xEC\x98\x59", (s32)/*"店の主人"*/"\x93\x58\x82\xCC\x8E\xE5\x90\x6C", (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 0,
};

__declspec(section ".data") s32 shop_mobj[] = {
    (s32)"usu_00_lock", (s32)"pera_box", (s32)"mobj_box00", 0,
};

__declspec(section ".data") s32 shop_item[] = {
    (s32)"item_02", (s32)"item_03", (s32)"item_04", (s32)"item_05", 0,
};

static __declspec(section ".data") EVT_BEGIN(evt_door_1_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie1_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_door_1_2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie1_door"), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_1)
    SET_FLOAT_VALUE(LW(1), LW(0))
    MULTIPLY_FLOAT(LW(1), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie1_kai1"), LW(1), 0, 0)
    SET_FLOAT_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie1_kai2"), LW(2), 0, 0)
    RETURN
EVT_END()

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
    0, 3, 2, (s32)"S_usu01_ie1_door", (s32)"A_door46", (s32)"A_door45", (s32)"S_usu01_ie1", 0,
    (s32)"S_usu01_ie1_naka", 0, (s32)evt_door_1_1, (s32)evt_door_1_2, (s32)evt_wall_1, (s32)minka_npc, 0, (s32)minka_item,
    (s32)door_1_open, (s32)door_1_close,
};

EVT_BEGIN(evt_door_2_1_1)
    SET_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_door_2_1_2)
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_2_1)
    SET_FLOAT_VALUE(LW(1), LW(0))
    MULTIPLY_FLOAT(LW(1), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_kai1"), 0, 0, LW(1))
    SET_FLOAT_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_kai2"), 0, 0, LW(2))
    RETURN
EVT_END()

EVT_BEGIN(loop_msg)
    IF_INT_LESS(GSW(0), 200)
        RETURN
    END_IF
    IF_INT_GREATER(GSW(0), 215)
        RETURN
    END_IF
    CALL(evt_mario_wait_movable)
    WAIT_MS(LW(3))
    SET_INT_INDEXED(LW(2), 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(chk_fuki, LW(0), LW(4))
            IF_INT_EQUAL(LW(4), 1)
                GET_INT_INDEXED(LW(2), LW(5))
                IF_INT_EQUAL(LW(5), 1)
                    CALL(evt_msg_close, LW(1))
                END_IF
                SET_INT_INDEXED(LW(2), 0)
                ELSE
                SET_INT_INDEXED(LW(2), 1)
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    LOOP(0)
        LOOP(0)
            GET_INT_INDEXED(LW(2), LW(5))
            IF_INT_EQUAL(LW(5), 1)
                WAIT_FRAMES(1)
                GET_INT_INDEXED(LW(2), LW(5))
                IF_INT_EQUAL(LW(5), 1)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_msg_print, 0, LW(1), 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mise_kiza_msg)
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(0), STRING("キザ野郎"))
        SET_VALUE(LW(1), STRING("stg4_usu_61_3"))
        SET_RAW_VALUE(LW(2), LSWF(2))
        SET_VALUE(LW(3), 700)
        CALL_CHILD(PTR(loop_msg))
    END_SIBLING_EVENT
    SET_VALUE(LW(0), STRING("店の主人"))
    SET_VALUE(LW(1), STRING("stg4_usu_61_4"))
    SET_RAW_VALUE(LW(2), LSWF(3))
    SET_VALUE(LW(3), 300)
    CALL_CHILD(PTR(loop_msg))
    RETURN
EVT_END()

EVT_BEGIN(mawari_house_delay)
    IF_INT_EQUAL(GSW(0), 180)
        IF_INT_EQUAL(GSWF(1925), 1)
            SPAWN_EVENT(PTR(evt_monban_buta2))
        END_IF
    END_IF
    DELETE_EVENT(GW(3))
    CALL(evt_msg_close, STRING("stg4_usu_61_3"))
    CALL(evt_msg_close, STRING("stg4_usu_61_4"))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_usu01_ie3"), 1)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_usu01_ie3"), 1)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(door_2_1_open)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    DELETE_EVENT(GW(4))
    CALL(evt_msg_close, STRING("stg4_usu_61_1"))
    CALL(evt_msg_close, STRING("stg4_usu_61_2"))
    SPAWN_EVENT_GET_ID(PTR(mise_kiza_msg), GW(3))
    RETURN
EVT_END()

s32 door_2_1[] = {
    0, 3, 2, (s32)"S_usu01_ie2_door1", (s32)"A_usu01_ie2_door2_u", (s32)"A_usu01_ie2_door2", (s32)"S_usu01_ie2", 0,
    (s32)"S_usu01_ie2_naka", 0, (s32)evt_door_2_1_1, 0, (s32)evt_wall_2_1, (s32)shop_npc, (s32)shop_mobj, (s32)shop_item,
    (s32)door_2_1_open, (s32)mawari_house_delay,
};

USER_FUNC(sleep_voice) {
    MarioWork* mario = marioGetPtr();
    s32 loops;

    if (isFirstCall) {
        event->userdata[0] = -1;
    }
    if (strcmp(mario->animName, "M_N_5A") == 0) {
        loops = animPoseGetLoopTimes(mario->paperAnimGroupId[marioAnimeId()]);
        if (loops != event->userdata[0]) {
            event->userdata[0] = loops;
            evtSetValue(event, GW(10), psndSFXOn_3D("SFX_VOICE_MARIO_SLEEP1", &mario->position));
        }
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(get_item_list) {
    s32* args = event->args;
    s32* list = _mapAlloc((pouchGetHaveItemCnt() + 1) * sizeof(s32));
    s32 n;
    s32 i;

    for (i = 0, n = 0; i < 20; i++) {
        if (pouchHaveItem(i)) {
            list[n] = pouchHaveItem(i);
            n++;
        }
    }
    list[n] = -1;
    evtSetValue(event, args[0], (s32)list);
    return EVT_RETURN_DONE;
}

USER_FUNC(delete_item_list) {
    _mapFree((void*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

USER_FUNC(check_tabemono) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    BOOL food = FALSE;

    if (*(u16*)&itemDataTable[id].usable_locations & 4) {
        food = TRUE;
    }
    evtSetValue(event, args[1], food);
    return EVT_RETURN_DONE;
}

USER_FUNC(chk_fuki) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = npcGetWorkPtr()->field_0x10;

    if (npc != NULL && strcmp(npc->description, name) == 0) {
        evtSetValue(event, args[1], TRUE);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[1], FALSE);
    return EVT_RETURN_DONE;
}

USER_FUNC(shop_item_disp_off) {
    s32 i;

    for (i = 0; i < 6; i++) {
        mapObjFlagOn((const char*)obj_list[i * 2], 1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(shop_item_disp_on) {
    s32 i;

    for (i = 0; i < 6; i++) {
        mapObjFlagOff((const char*)obj_list[i * 2], 1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(ie2_npc_disp_off) {
    const char* show[] = {"\202\250\223X\202\314\211\234\202\263\202\361", "\203L\203U\226\354\230Y",
                          "\203u\203^\203L\203U\226\354\230Y", "\223X\202\314\216\345\220l", NULL};
    const char* hide[] = {"\203y\203\211\226\202\220l", NULL};
    s32 i;

    for (i = 0; show[i] != NULL; i++) {
        animPoseSetMaterialFlagOff(npcNameToPtr(show[i])->poseId, 0x1800);
    }
    for (i = 0; hide[i] != NULL; i++) {
        animPoseSetMaterialFlagOn(npcNameToPtr(hide[i])->poseId, 0x1800);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(ie2_npc_disp_on) {
    const char* hide[] = {"\202\250\223X\202\314\211\234\202\263\202\361", "\203L\203U\226\354\230Y",
                          "\203u\203^\203L\203U\226\354\230Y", "\223X\202\314\216\345\220l", NULL};
    const char* show[] = {"\203y\203\211\226\202\220l", NULL};
    s32 i;

    for (i = 0; hide[i] != NULL; i++) {
        animPoseSetMaterialFlagOn(npcNameToPtr(hide[i])->poseId, 0x1800);
    }
    for (i = 0; show[i] != NULL; i++) {
        animPoseSetMaterialFlagOff(npcNameToPtr(show[i])->poseId, 0x1800);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(set_fook_evt) {
    s32* args = event->args;
    s32* work = (s32*)evtGetValue(event, args[0]);

    work[1] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(booboo_main) {
    u32 i;

    for (i = 0; i < 8; i++) {
        if (npcNameToPtr_NoAssert((const char*)booboo_name[i * 2]) != NULL) {
            animPoseSetMaterialLightFlagOn(npcNameToPtr((const char*)booboo_name[i * 2])->poseId, 0x10);
        }
    }
    return EVT_RETURN_DONE;
}

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

EVT_BEGIN(evt_ie2_door2_1)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_usu01_ie2_naka2"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_usu01_ie2_naka2"), 4096)
    CALL(evt_item_delete_check, STRING("item_05"), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING("item_05"), LW(0), LW(1), LW(2))
        CALL(evt_item_set_position, STRING("item_05"), LW(0), -1000, LW(2))
    END_IF
    CALL(evt_mario_mov_pos2, -213, -471, FLOAT(135.0f))
    CALL(evt_party_set_homing_dist, 0, FLOAT(20.0f))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door3"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_party_door_move, -297, -416, FLOAT(135.0f))
    CALL(evt_party_move_behind_mario, 0)
    CALL(evt_party_set_homing_dist, 0, FLOAT(50.0f))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door3"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    DELETE_EVENT(GW(3))
    CALL(evt_msg_close, STRING("stg4_usu_61_3"))
    CALL(evt_msg_close, STRING("stg4_usu_61_4"))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 185)
        CALL(shop_item_disp_off)
    END_IF
    CALL(ie2_npc_disp_off)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_WALL_MOVE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 300, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("S_usu01_ie2_mkabe"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door3"), LW(0), 0, 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_FALL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_ie2_door2_2)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
        CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door3"), LW(0), 0, 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_set_homing_dist, 0, FLOAT(20.0f))
    CALL(evt_party_move_behind_mario, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_WALL_MOVE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 300, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("S_usu01_ie2_mkabe"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 185)
        CALL(shop_item_disp_on)
    END_IF
    CALL(ie2_npc_disp_on)
    SPAWN_EVENT_GET_ID(PTR(mise_kiza_msg), GW(3))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door3"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_party_door_move, -213, -471, FLOAT(135.0f))
    CALL(evt_party_move_behind_mario, 0)
    CALL(evt_party_set_homing_dist, 0, FLOAT(50.0f))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie2_door3"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_usu01_ie2_naka2"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_usu01_ie2_naka2"), 4096)
    CALL(evt_item_delete_check, STRING("item_05"), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING("item_05"), LW(0), LW(1), LW(2))
        CALL(evt_item_set_position, STRING("item_05"), LW(0), 0, LW(2))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_door_3_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie3_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_door_3_2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie3_door"), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_3)
    SET_FLOAT_VALUE(LW(1), LW(0))
    MULTIPLY_FLOAT(LW(1), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie3_kai1"), LW(1), 0, 0)
    WAIT_FRAMES(10)
    SET_FLOAT_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_usu01_ie3_kai2"), LW(2), 0, 0)
    RETURN
EVT_END()

__declspec(section ".data") s32 door_3_item[] = {
    (s32)"item01", 0,
};

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
    0, 3, 2, (s32)"S_usu01_ie3_door", (s32)"A_usu01_ie3_doaa_u", (s32)"A_usu01_ie3_doaa", (s32)"S_usu01_ie3", 0,
    (s32)"S_usu01_ie3_naka", 0, (s32)evt_door_3_1, (s32)evt_door_3_2, (s32)evt_wall_3, 0, 0, (s32)door_3_item,
    (s32)door_3_open, (s32)door_3_close,
};

static s32 bero_entry_data[] = {
    (s32)"e_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"gra_00", (s32)"w_bero", 65537, 0, 0, (s32)"w_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"usu_00", (s32)"e_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(usu01_gusun)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 219)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(2232), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    IF_INT_GREATER_OR_EQUAL(LW(3), 0)
        IF_INT_LESS_OR_EQUAL(LW(3), 100)
            IF_INT_LESS(GSW(0), 200)
                CALL(evt_msg_toge, 2, 37, 30, -244)
                CALL(evt_msg_print, 0, STRING("stg4_usu_51"), 0, 0)
                ELSE
                CALL(evt_msg_toge, 2, 37, 30, -244)
                CALL(evt_msg_print, 0, STRING("stg4_usu_61_1"), 0, 0)
                CALL(evt_msg_toge, 2, 37, 30, -244)
                CALL(evt_msg_print, 0, STRING("stg4_usu_61_2"), 0, 0)
            END_IF
            RETURN
        END_IF
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(evt_monban_buta_main)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_set_position, STRING("ブタ門番"), 400, 0, -55)
    CALL(evt_npc_set_position, STRING("門番"), 0, -2000, 0)
    CALL(evt_snd_sfxon, STRING("SFX_STG4_TEMPLE_BELL1"), 0)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(LW(0), STRING("e_bero"))
    CALL_CHILD(PTR(bero_case_switch_on))
    SET_VALUE(GSW(0), 181)
    RETURN
EVT_END()

EVT_BEGIN(evt_monban_buta)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 181)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL_CHILD(PTR(evt_monban_buta_main))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_monban_buta2)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 181)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1000)
    CALL_CHILD(PTR(evt_monban_buta_main))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_monban_look)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(GSW(0), 182)
            RETURN
        END_IF
        IF_INT_GREATER_OR_EQUAL(GSW(0), 181)
            SET_VALUE(LW(0), 420)
            SET_VALUE(LW(1), 0)
            SET_VALUE(LW(2), 0)
            CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
            CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(6))
            IF_INT_LESS(LW(6), 100)
                CALL(evt_mario_key_onoff, 0)
                CALL(evt_mario_normalize)
                CALL(evt_party_yoshi_ride, 0, 0)
                CALL(evt_mario_wait_rideon)
                CALL(evt_mario_set_dir_npc, STRING("ブタ門番"))
                CALL(evt_party_set_dir_npc, 0, STRING("ブタ門番"))
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2"), LW(0), LW(1), LW(2), 0)
                CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
                CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
                WAIT_MS(1000)
                CALL(evt_party_stop, 0)
                WAIT_MS(200)
                CALL(evt_msg_print_party, STRING("stg4_usu_47"))
                CALL(evt_party_run, 0)
                CALL(evt_mario_key_onoff, 1)
                SET_VALUE(GSW(0), 182)
                RETURN
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") s32 lock_tbl[] = {
    21, -1,
};

static EVT_BEGIN(lock_item_check)
    CALL(evt_pouch_check_item, 21, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(evt_win_item_select, 0, PTR(lock_tbl), LW(0), 0)
        IF_INT_EQUAL(LW(0), -1)
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_IF
        ELSE
        IF_INT_EQUAL(GSWF(1925), 1)
            CALL(evt_set_dir_to_target, STRING("お店の奥さん"), STRING("mario"))
            CALL(evt_msg_print, 0, STRING("stg4_usu_57"), 0, STRING("お店の奥さん"))
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(unlock)
    CALL(evt_run_case_evt, 9, 1, STRING("A_usu01_ie2_door3"), 0, PTR(evt_ie2_door2_1), 0)
    SET_VALUE(GSW(0), 185)
    RETURN
EVT_END()

static __declspec(section ".data") s32 obj_list[] = {
    (s32)"mi02_S_item_01", (s32)"A_item_01", (s32)"mi02_mi02_S_item_02", (s32)"A_item_02", (s32)"mi02_S_item_03", (s32)"A_item_03", (s32)"mi02_S_item_04", (s32)"A_item_04",
    (s32)"mi02_S_item_05", (s32)"A_item_05", (s32)"mi02_S_item_06", (s32)"A_item_06",
};

static __declspec(section ".data") s32 goods_list[] = {
    129, 20, 177, 10, 140, 30, 155, 20,
    149, 15, 151, 40,
};

static s32 trade_list[] = {
    129, 655360, 177, 327680, 140, 983040, 155, 655360,
    149, 458752, 151, 1310720, 182, 196608, 167, 917504,
    152, 262144, 191, 13107200, 173, 786432, 0, 0,
};

static s32 shopper_data[] = {
    (s32)/*"お店の奥さん"*/"\x82\xA8\x93\x58\x82\xCC\x89\x9C\x82\xB3\x82\xF1", 0, 0, (s32)"usugurashop_00", (s32)"usugurashop_01", (s32)"usugurashop_02", (s32)"usugurashop_03", (s32)"usugurashop_04",
    (s32)"usugurashop_05", (s32)"usugurashop_06", (s32)"usugurashop_07", (s32)"usugurashop_08", (s32)"usugurashop_09", (s32)"usugurashop_10", (s32)"usugurashop_11", (s32)"usugurashop_12",
    (s32)"usugurashop_13", (s32)"usugurashop_14", (s32)"usugurashop_15", (s32)"usugurashop_16", (s32)"usugurashop_17", (s32)"usugurashop_18", (s32)"usugurashop_19", (s32)"usugurashop_20",
    (s32)"usugurashop_21", (s32)"usugurashop_22", (s32)"usugurashop_23", (s32)"usugurashop_24", (s32)"usugurashop_25", (s32)"usugurashop_26", (s32)"usugurashop_27", (s32)"usugurashop_28",
    (s32)"usugurashop_29", (s32)"usugurashop_30", (s32)"usugurashop_31", (s32)"usugurashop_32", (s32)"usugurashop_33", (s32)"usugurashop_34",
};

__declspec(section ".data") EVT_BEGIN(shopper_talk1)
    CALL(evt_msg_print, 0, STRING("stg4_usu_59"), 0, STRING("me"))
    SET_VALUE(LW(0), -100)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(shopper_talk2)
    CALL(evt_msg_print, 0, STRING("stg4_usu_60"), 0, STRING("me"))
    SET_VALUE(LW(0), -100)
    RETURN
EVT_END()

static s32 booboo_name[] = {
    (s32)/*"ブタキザ野郎"*/"\x83\x75\x83\x5E\x83\x4C\x83\x55\x96\xEC\x98\x59", 117440512, (s32)/*"ブタおばさん"*/"\x83\x75\x83\x5E\x82\xA8\x82\xCE\x82\xB3\x82\xF1", 16777216, (s32)/*"ブタ門番"*/"\x83\x75\x83\x5E\x96\xE5\x94\xD4", 50397184, (s32)/*"ブタ村人Ｉ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x68", 83951616,
    (s32)/*"ブタ村人Ｊ"*/"\x83\x75\x83\x5E\x91\xBA\x90\x6C\x82\x69", 67174400, (s32)/*"ブタ３人娘Ａ"*/"\x83\x75\x83\x5E\x82\x52\x90\x6C\x96\xBA\x82\x60", 67174400, (s32)/*"ブタ３人娘Ｂ"*/"\x83\x75\x83\x5E\x82\x52\x90\x6C\x96\xBA\x82\x61", 67174400, (s32)/*"ブタ３人娘Ｃ"*/"\x83\x75\x83\x5E\x82\x52\x90\x6C\x96\xBA\x82\x62", 67174400,
};

__declspec(section ".data") EVT_BEGIN(evt_roll_get)
    RETURN
EVT_END()

static __declspec(section ".data") s32 key_tbl[] = {
    35, -1,
};

static EVT_BEGIN(evt_majin)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_adjust_dir)
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -260, -395, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -235, -370, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    IF_INT_EQUAL(GSWF(1932), 0)
        CALL(evt_mobj_get_position, STRING("pera_box"), LW(0), LW(1), LW(2))
        ADD(LW(1), 30)
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_01"), 0, 0)
        CALL(evt_mobj_get_position, STRING("pera_box"), LW(3), LW(4), LW(5))
        ADD(LW(4), 30)
        CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLACKBOX_SWING1"), LW(3), LW(4), LW(5), LW(15))
        CALL(evt_mobj_set_anim, STRING("pera_box"), STRING("A_3"))
        CALL(evt_mobj_wait_animation_end, STRING("pera_box"))
        CALL(evt_snd_sfxoff, LW(15))
        WAIT_MS(300)
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_02"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_G"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_03"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_04"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_N_5B"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_05"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_06"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_Z"))
        WAIT_MS(1600)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_07"), PTR(majin_callback), 0)
        CALL(evt_mobj_exec_cancel, STRING("pera_box"))
        SET_VALUE(GSWF(1932), 1)
        ELSE
        CALL(evt_pouch_check_item, 35, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(evt_mobj_get_position, STRING("pera_box"), LW(0), LW(1), LW(2))
            ADD(LW(1), 30)
            CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
            CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_08"), PTR(majin_callback), 0)
            CALL(evt_mobj_exec_cancel, STRING("pera_box"))
            ELSE
            CALL(evt_mobj_get_position, STRING("pera_box"), LW(0), LW(1), LW(2))
            ADD(LW(1), 30)
            CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
            CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_09"), PTR(majin_callback), 0)
            CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
            IF_INT_EQUAL(LW(0), -1)
                CALL(evt_mobj_get_position, STRING("pera_box"), LW(0), LW(1), LW(2))
                ADD(LW(1), 30)
                CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
                CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_10"), PTR(majin_callback), 0)
                CALL(evt_mobj_exec_cancel, STRING("pera_box"))
                ELSE
                CALL(evt_pouch_remove_item, 35, LW(0))
                CALL(evt_mobj_get_position, STRING("pera_box"), LW(0), LW(1), LW(2))
                ADD(LW(1), 30)
                CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
                CALL(evt_msg_print, 0, STRING("stg4_usu_majin3_11"), PTR(majin_callback), 0)
                CALL(evt_mario_set_pose, STRING("M_I_N"))
            END_IF
        END_IF
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_majin2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mobj_wait_animation_end, STRING("pera_box"))
    CALL(evt_pouch_add_item, 3, LW(0))
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_EVT_PERAMAJIN1"))
    CALL(evt_snd_envoff, 1024)
    CALL(bgm_start_wait)
    WAIT_MS(1000)
    CALL(evt_paper_entry, STRING("OFF_d_kusya"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_kusya"))
    CALL(evt_img_alloc_capture, STRING("img"), 0, 0, 1, 0, 0, 608, 480)
    CALL(evt_img_set_virtual_point, STRING("img"), 0, 0, 100)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_img_clear_virtual_point, STRING("img"))
    END_INLINE_EVENT
    CALL(evt_img_onoff, STRING("img"), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_APPEAR1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_COME1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_mario_set_camid, 7)
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(lect_cam_save)
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    WAIT_FRAMES(1)
    CALL_CHILD(PTR(roll_majin_lecture_init))
    CALL_CHILD(PTR(roll_majin_lecture))
    LOOP(6)
        CALL(evt_mario_dispflag_onoff, 1, 1)
        WAIT_MS(100)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_PERAMAJIN_BLINKING1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_dispflag_onoff, 0, 1)
        WAIT_MS(100)
    END_LOOP
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_mario_set_pos, LW(10), LW(11), LW(12))
    CALL(evt_mario_dispflag_onoff, 0, 1)
    CALL(evt_mario_init_camid)
    CALL(lect_cam_load, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_GOOUT1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff_f, 513, 2000)
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_2"))
    CALL(evt_img_wait_animend, STRING("img"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_GOOUT2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_img_release, STRING("img"))
    CALL(evt_paper_delete, STRING("OFF_d_kusya"))
    SET_VALUE(GSW(0), 187)
    SET_VALUE(GSWF(1931), 1)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_snd_envoff, 513)
    CALL(evt_snd_envon, 288, 0)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static void majin_callback(s32 type) {
    MapObjectEntry* mobj = mobjNameToPtr("pera_box");

    if (type == 0) {
        animPoseSetAnim(mobj->poseId, "A_2", TRUE);
    } else if (type == 5) {
        if (animPoseGetLoopTimes(mobj->poseId) >= 1.0f) {
            animPoseSetAnim(mobj->poseId, "A_2", TRUE);
        }
    } else if (type == 2) {
        animPoseSetAnim(mobj->poseId, "S_1", TRUE);
    }
}

USER_FUNC(box_r) {
    MapObjectEntry* mobj = mobjNameToPtr("pera_box");

    mobj->rotation.y = 135.0f;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

BOOL psndBGMStartCheck(s32 id);

static USER_FUNC(bgm_start_wait) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(mobj_ry) {
    MapObjectEntry* mobj = mobjNameToPtr("mobj_box00");

    mobj->rotation.y = 135.0f;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

EVT_BEGIN(tree_onoff)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_mapobj_get_position, LW(10), LW(3), LW(4), LW(5))
        CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(9))
        IF_INT_GREATER(LW(9), LW(11))
            IF_INT_EQUAL(LF(0), 1)
                CALL(evt_mapobj_flag_onoff, 1, 1, LW(10), 1)
                SET_VALUE(LF(0), 0)
            END_IF
            ELSE
            IF_INT_EQUAL(LF(0), 0)
                CALL(evt_mapobj_flag_onoff, 1, 0, LW(10), 1)
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_ki_1)
    CALL(evt_npc_set_anim, STRING("カラスＪ"), STRING("A_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("カラスＪ"), STRING("S_1"))
    RETURN
EVT_END()

static EVT_BEGIN(evt_ki_2)
    CALL(evt_npc_set_anim, STRING("カラスＨ"), STRING("A_1"))
    CALL(evt_npc_set_anim, STRING("カラスＩ"), STRING("A_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("カラスＨ"), STRING("S_1"))
    CALL(evt_npc_set_anim, STRING("カラスＩ"), STRING("S_1"))
    RETURN
EVT_END()

static EVT_BEGIN(evt_ki_3)
    CALL(evt_npc_set_anim, STRING("カラスＦ"), STRING("A_1"))
    CALL(evt_npc_set_anim, STRING("カラスＧ"), STRING("A_1"))
    WAIT_MS(1500)
    CALL(evt_npc_set_anim, STRING("カラスＦ"), STRING("S_1"))
    CALL(evt_npc_set_anim, STRING("カラスＧ"), STRING("S_1"))
    RETURN
EVT_END()

static s32 tree_tbl[] = {
    2, (s32)"A_ki_1", (s32)"S_usu01_ki01", 0, 0, (s32)evt_ki_1, 2, (s32)"A_ki_2",
    (s32)"S_usu01_ki02", 0, 0, (s32)evt_ki_2, 2, (s32)"A_ki_3", (s32)"S_usu01_ki03", 0,
    0, (s32)evt_ki_3, 2, (s32)"A_ki_4", (s32)"S_usu01_ki05", 0, 0, 0,
    7, 0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(usu_01_tree_init)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    RETURN
EVT_END()

static EVT_BEGIN(mobj_box00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), 274, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 258)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(usu_01_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_USU1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
    CALL(evt_kagemario_init_29_text_1A0C)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_29_data_104A8))
    CALL(evt_npc_setup, PTR(npcEnt))
    SWITCH(GSW(0))
        CASE_BETWEEN(178, 200)
        CALL_CHILD(PTR(musume_a_pig_entry))
        CALL_CHILD(PTR(musume_b_pig_entry))
        CALL_CHILD(PTR(musume_c_pig_entry))
        CASE_BETWEEN(200, 215)
        CALL_CHILD(PTR(musume_a_entry))
        CALL_CHILD(PTR(musume_b_entry))
        CALL_CHILD(PTR(musume_c_entry))
    END_SWITCH
    IF_INT_LESS(GSW(0), 185)
        CALL(evt_mobj_lock, STRING("usu_00_lock"), 21, FLOAT(-263.5f), FLOAT(10.099609f), FLOAT(-432.0498f), 135, PTR(lock_item_check), PTR(unlock), GSWF(1926))
        ELSE
        CALL(evt_run_case_evt, 9, 1, STRING("A_usu01_ie2_door3"), 0, PTR(evt_ie2_door2_1), 0)
    END_IF
    SET_VALUE(LW(0), PTR(door_1))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(door_2_1))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(door_3))
    CALL_CHILD(PTR(evt_door_entry))
    CALL(evt_run_case_evt, 9, 1, STRING("A_usu01_ie2_door3_u"), 0, PTR(evt_ie2_door2_2), 0)
    SPAWN_EVENT(PTR(evt_monban_look))
    IF_INT_EQUAL(GSW(0), 180)
        IF_INT_EQUAL(GSWF(1925), 1)
            SPAWN_EVENT(PTR(evt_monban_buta))
        END_IF
    END_IF
    SPAWN_EVENT_GET_ID(PTR(usu01_gusun), GW(4))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 185)
        IF_INT_LESS(GSW(0), 200)
            CALL(set_fook_evt, PTR(shopper_data), PTR(shopper_talk1))
            ELSE
            IF_INT_LESS(GSW(0), 213)
                CALL(set_fook_evt, PTR(shopper_data), PTR(shopper_talk2))
            END_IF
        END_IF
        CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("mi02_S_items"), 16384)
    SET_VALUE(GW(0), 0)
    SET_VALUE(GW(1), 0)
    SET_VALUE(GW(2), 0)
    SPAWN_EVENT(PTR(usu01_check_vivian))
    SPAWN_EVENT(PTR(usu01_crowFG_talk_event))
    SPAWN_EVENT(PTR(usu01_crowHI_talk_event))
    SPAWN_EVENT(PTR(usu01_crowJ_talk_event))
    IF_INT_LESS(GSW(0), 183)
        CALL(evt_run_case_evt, 9, 1, STRING("A_mon"), 0, PTR(evt_mon_open), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_monato"), 1)
        CALL(evt_hitobj_onoff, STRING("A_mon02"), 1, 0)
        ELSE
        CALL(evt_mapobj_rotate, 1, STRING("S_mon01"), 0, 50, 0)
        CALL(evt_mapobj_rotate, 1, STRING("S_mon02"), 0, -85, 0)
        CALL(evt_hitobj_onoff, STRING("A_mon"), 1, 0)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(booboo_main)
    END_INLINE_EVENT
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki1"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki2"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki3"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki4"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ki5"), 2)
    CALL_CHILD(PTR(usu_01_tree_init))
    SET_VALUE(LW(10), STRING("ki3"))
    SET_VALUE(LW(11), 450)
    SPAWN_EVENT(PTR(tree_onoff))
    CALL(evt_item_entry, STRING("item_01"), 125, 210, 0, 265, 16, GSWF(5630), 0)
    CALL(evt_item_entry, STRING("item_02"), 151, -275, 0, -310, 16, GSWF(1935), 0)
    CALL(evt_item_entry, STRING("item_03"), 134, -305, 0, -380, 16, GSWF(1936), 0)
    CALL(evt_item_entry, STRING("item_04"), 156, -335, 0, -410, 16, GSWF(1937), 0)
    CALL(evt_item_entry, STRING("item_05"), 164, -250, 0, -500, 16, GSWF(1939), 0)
    CALL(evt_mobj_itembox, STRING("mobj_box00"), -255, 0, -288, 0, 0, PTR(mobj_box00), GSWF(1934))
    CALL(mobj_ry)
    BEGIN_INLINE_EVENT
        CALL(npc_process)
    END_INLINE_EVENT
    IF_INT_GREATER_OR_EQUAL(GSW(0), 187)
        SET_VALUE(GSWF(1931), 1)
    END_IF
    CALL(evt_mobj_itembox, STRING("pera_box"), -289, 0, -341, 3, PTR(evt_majin), PTR(evt_majin2), GSWF(1931))
    CALL(evt_mobj_flag_onoff, 0, STRING("pera_box"), 64)
    CALL(box_r)
    IF_INT_EQUAL(GSWF(5394), 1)
        CALL(evt_item_entry, STRING("iri_20"), 217, -345, 20, -132, 16, GSWF(1938), 0)
    END_IF
    SPAWN_EVENT(PTR(evt_sub_mail_event))
    RETURN
EVT_END()

