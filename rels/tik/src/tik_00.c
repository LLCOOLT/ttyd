#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "mario/mario.h"
#include "party.h"
#include "pmario_sound.h"
#include "driver/mapdrv.h"
#include "memory.h"
#include "dolphin/gx.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "dolphin/mtx.h"
#include "string.h"
#include "stdio.h"
#include "driver/msgdrv.h"

void mapGrpSetColor(const char* name, GXColor color);
typedef struct UranaiWork { s32 lwData[16]; s32 gwData[32]; smartEntry* buf; GXTexObj tex; s32 ready; EventEntry* capEvent; s32 x; s32 y; s32 w; s32 h; } UranaiWork;
void uranai_cap(CameraId cameraId, void* param);
double tan(double);
static inline f32 tanf(f32 x) { return tan(x); }
extern s32 evt_uranai_cap[];
const char* search_evt_moji(s32 id);
s32 uranaisi_ryokin_rtn(s32 type);
static s32 ssf;
UranaiWork* uranai_wp;
char* uranaisi_msgp;

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos);
USER_FUNC(card_camid);
USER_FUNC(evt_badgeShop_starmaniac_dec);
USER_FUNC(evt_badgeShop_starmaniac_get_kind_cnt);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_door_end_wait);
USER_FUNC(evt_door_param);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_set_mapchange_type);
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
USER_FUNC(evt_img_wait_animend);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_color);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_set_offscreen);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_cam_off);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_dispdir);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dispdir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_check);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_add_insert);
USER_FUNC(evt_msg_print_insert);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_offscreen);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_ry_lr);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_offscreen_get_boundingbox);
USER_FUNC(evt_offscreen_get_boundingbox2);
static USER_FUNC(evt_osreport);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dispdir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_add_coin);
USER_FUNC(evt_pouch_add_item);
USER_FUNC(evt_pouch_add_starpiece);
USER_FUNC(evt_pouch_get_coin);
USER_FUNC(evt_pouch_get_starpiece);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_shop_setup);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_bgmon_f);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_envon_f);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_language);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_uranaisi_msg_alloc);
USER_FUNC(evt_uranaisi_msg_free);
USER_FUNC(evt_uranaisi_msg_set);
USER_FUNC(evt_win_coin_off);
USER_FUNC(evt_win_coin_on);
USER_FUNC(evt_win_coin_wait);
USER_FUNC(evt_win_other_select);
USER_FUNC(johoya_data_alloc);
USER_FUNC(johoya_keti_newjoho_check);
USER_FUNC(johoya_keti_newjoho_makelabel);
USER_FUNC(johoya_keti_newjoho_setreadflag);
USER_FUNC(johoya_keti_oldspeak_check);
USER_FUNC(johoya_keti_oldspeak_makelabel);
USER_FUNC(johoya_keti_oldspeak_setreadflag);
static USER_FUNC(scale_func);
static USER_FUNC(setmertn);
static USER_FUNC(ss_set);
USER_FUNC(unk_tik_00000598);
USER_FUNC(unk_tik_000005c0);
USER_FUNC(unk_tik_000005e8);
USER_FUNC(uranai_bbox);
USER_FUNC(uranai_cap_evt);
USER_FUNC(uranai_exit_func);
USER_FUNC(uranai_init_func);
USER_FUNC(uranaisi_data_alloc);
USER_FUNC(uranaisi_data_free);
USER_FUNC(uranaisi_next_check);
USER_FUNC(uranaisi_next_makelabel);
USER_FUNC(uranaisi_ryokin);
USER_FUNC(uranaisi_starpiece_check);
USER_FUNC(uranaisi_starpiece_makelabel);
USER_FUNC(uranaisi_starpiece_setreadflag);
USER_FUNC(uranaisi_supercoin_check);
USER_FUNC(uranaisi_supercoin_makelabel);
USER_FUNC(uranaisi_supercoin_setreadflag);
USER_FUNC(uranaisi_table_clear);
USER_FUNC(mario_key_onoff_wait);
USER_FUNC(card_xlu);
void card_tev(MapTevCallbackInfo* info);
void uranai_cap(CameraId cameraId, void* param);
static USER_FUNC(ss_check);
extern s32 door_close_se[];
extern s32 door_open_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_door_close[];
extern s32 evt_door_entry[];
extern s32 evt_door_open[];
extern s32 evt_door_open_quick[];
extern s32 evt_sub_mail_event[];
extern s32 moving_floor[];
extern s32 npc_init_evt[];
extern s32 tik_villager_urouro[];

__declspec(section ".data") u64 fd_tik_00_negone_one_374;
__declspec(section ".data") s32 fd_tik_00_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_00___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_00_one_negone_373;
__declspec(section ".data") s32 fd_tik_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_00_one_381[1];
__declspec(section ".data") u64 fd_tik_00_negone_one_360;
__declspec(section ".data") s32 fd_tik_00_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_00___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_00_one_negone_359;
__declspec(section ".data") s32 fd_tik_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_00_one_364[1];
static s32 bero_entry_data[60];
static __declspec(section ".data") s32 obj_list[12];
static __declspec(section ".data") s32 goods_list[12];
static s32 trade_list[24];
static s32 shopper_data[38];
s32 uranaisi_next_evt[152];
s32 uranaisi_starpiece_evt[60];
s32 uranaisi_supercoin_evt[60];
static s32 name_tbl[18];
__declspec(section ".data") s32 evt_uranai_cap[4];
s32 uranai_init[147];
s32 uranai_main[595];
s32 uranai_exit[98];
s32 uranaisi_table_talk[226];
__declspec(section ".data") s32 uranaisi_direct_talk[8];
__declspec(section ".data") s32 uranaisi_init[10];
s32 unk_evt_tik_0000f438[14];
__declspec(section ".data") s32 starmaniac_get_event[5];
s32 starmaniac_talk[227];
s32 johoyaketi_talk[186];
__declspec(section ".data") s32 kuribo5_init[2];
s32 kuribo5_talk[76];
s32 chusan4_init[13];
s32 chusan4_regl[25];
s32 chusan4_talk[76];
__declspec(section ".data") s32 borodo3_init[2];
__declspec(section ".data") s32 borodo3_regl[4];
s32 borodo3_talk[76];
__declspec(section ".data") s32 borodo4_init[2];
s32 borodo4_talk[76];
__declspec(section ".data") s32 pinkbom_init[2];
s32 pinkbom_talk[76];
__declspec(section ".data") s32 master_2_init[8];
s32 master_2_talk[76];
static s32 npcEnt[253];
static s32 evt_door_01_00[18];
s32 evt_wall_01_00[62];
s32 evt_wall_01_01[66];
s32 evt_wall_01_02[66];
static __declspec(section ".data") s32 door_data_01_npc[2];
static __declspec(section ".data") s32 evt_wall_01[12];
s32 evt_open_01[39];
s32 evt_close_01[60];
static s32 door_data_01[18];
static __declspec(section ".data") s32 evt_door_02_00[12];
s32 evt_wall_02_00[62];
s32 evt_wall_02_01[66];
s32 evt_wall_02_02[66];
s32 evt_wall_02_03[62];
static s32 evt_wall_02[14];
static __declspec(section ".data") s32 mise_npc[2];
__declspec(section ".data") s32 evt_open_02[12];
s32 evt_close_02[14];
static s32 door_data_02[18];
static __declspec(section ".data") s32 evt_door_03_00[12];
s32 evt_wall_03_00[62];
s32 evt_wall_03_01[66];
s32 evt_wall_03_02[66];
s32 evt_wall_03_03[62];
static s32 evt_wall_03[14];
static __declspec(section ".data") s32 door_data_03_npc[5];
__declspec(section ".data") s32 evt_open_03[12];
s32 evt_close_03[14];
static __declspec(section ".data") s32 door_data_03_mobj[2];
static s32 door_data_03[18];
static __declspec(section ".data") s32 evt_door_04_00[12];
static __declspec(section ".data") s32 evt_door_04_01[12];
static s32 evt_wall_04[15];
s32 evt_open_04_open[179];
static s32 evt_door_04_close[87];
static s32 door_data_04[18];
s32 evt_door_stg7_open[27];
__declspec(section ".data") s32 evt_door_stg7_close[7];
static s32 evt_door_04_entry[64];
s32 tensou_return[243];
s32 tensou_init_event[182];
s32 tensou_event[209];
s32 tensou_anim_event[30];
s32 tensou_sw_event[94];
s32 kurihakase_event[221];
s32 hashira_bomb_sub[144];
s32 hashira_bomb[45];
static s32 epilogue_npc_entry[25];
static s32 epilogue_evt[127];
static s32 mobj_box01[34];
s32 tik_00_init_evt[214];

__declspec(section ".data") u64 fd_tik_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_00_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tik_07", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"tik_01", (s32)"w_bero_1", 65537, 0, 0, (s32)"tensou", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"tik_00", (s32)"tensou", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static __declspec(section ".data") s32 obj_list[] = {
    (s32)"sina_1", (s32)"a_sina1", (s32)"sina_2", (s32)"a_sina_2", (s32)"sina_3", (s32)"a_sina_3", (s32)"sina_4", (s32)"a_sina_4",
    (s32)"sina_5", (s32)"a_sina_5", (s32)"sina_6", (s32)"a_sina_6",
};

static __declspec(section ".data") s32 goods_list[] = {
    157, 15, 158, 15, 150, 200, 156, 200,
    126, 110, 127, 350,
};

static s32 trade_list[] = {
    157, 458752, 158, 458752, 150, 3276800, 156, 3276800,
    126, 6553600, 127, 19660800, 213, 1638400, 203, 1310720,
    202, 524288, 209, 983040, 196, 2621440, 0, 0,
};

static s32 shopper_data[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", 0, 0, (s32)"tik_shop_00", (s32)"tik_shop_01", (s32)"tik_shop_02", (s32)"tik_shop_03", (s32)"tik_shop_04",
    (s32)"tik_shop_05", (s32)"tik_shop_06", (s32)"tik_shop_07", (s32)"tik_shop_08", (s32)"tik_shop_09", (s32)"tik_shop_10", (s32)"tik_shop_11", (s32)"tik_shop_12",
    (s32)"tik_shop_13", (s32)"tik_shop_14", (s32)"tik_shop_15", (s32)"tik_shop_16", (s32)"tik_shop_17", (s32)"tik_shop_18", (s32)"tik_shop_19", (s32)"tik_shop_20",
    (s32)"tik_shop_21", (s32)"tik_shop_22", (s32)"tik_shop_23", (s32)"tik_shop_24", (s32)"tik_shop_25", (s32)"tik_shop_26", (s32)"tik_shop_27", (s32)"tik_shop_28",
    (s32)"tik_shop_29", (s32)"shop_30", (s32)"shop_31", (s32)"shop_32", (s32)"shop_33", (s32)"shop_34",
};

EVT_BEGIN(uranaisi_next_evt)
    IF_INT_LESS(GSW(0), 405)
        CALL(uranaisi_data_alloc, 0, STRING("un_next"))
        CALL(uranaisi_next_check, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(uranaisi_next_makelabel, 0, LW(1))
            CALL(evt_msg_print, 0, LW(1), 0, STRING("me"))
            ELSE
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_win_coin_on, 0, LW(12))
                CALL(evt_osreport, 0, LW(1))
                CALL(evt_msg_print, 1, STRING("ゆうこうな　データが\n見つかりませんでした\nメッセージを　とうろく　してください\n<key>\n<scrl_auto>\n<once_stop>\n"), 0, STRING("me"))
                CALL(evt_msg_print_add_insert, 1, STRING("げんざいの　イベントばんごうは\n『%s』\nです\n<key>"), LW(1))
                CALL(uranaisi_ryokin, 0, LW(2))
                CALL(evt_pouch_add_coin, LW(2))
                CALL(evt_win_coin_wait, LW(12))
                WAIT_MS(200)
                CALL(evt_win_coin_off, LW(12))
                ELSE
                CALL(evt_win_coin_on, 0, LW(12))
                CALL(evt_osreport, 0, LW(1))
                CALL(evt_msg_print, 1, STRING("ゆうこうな　データが\nじゅうふくして　みつかりました\nゆうこうな　メッセージは　１つにしてください\n<key>\n<scrl_auto>\n<once_stop>"), 0, STRING("me"))
                SET_VALUE(LW(2), 0)
                SET_VALUE(LW(3), LW(0))
                LOOP(LW(0))
                    CALL(uranaisi_next_makelabel, LW(2), LW(1))
                    CALL(evt_msg_print_add_insert, 1, STRING("『%s』\n<key>\n<scrl_auto>\n<once_stop>\n"), LW(1))
                    ADD(LW(2), 1)
                END_LOOP
                CALL(evt_msg_print_add_insert, 1, STRING("いじょう　%dこが\nじゅうふくしている　メッセージです\n<key>"), LW(3))
                CALL(uranaisi_ryokin, 0, LW(2))
                CALL(evt_pouch_add_coin, LW(2))
                CALL(evt_win_coin_wait, LW(12))
                WAIT_MS(200)
                CALL(evt_win_coin_off, LW(12))
            END_IF
        END_IF
        CALL(uranaisi_data_free)
        ELSE
        CALL(evt_msg_print, 0, STRING("uranaisi_17"), 0, STRING("me"))
        CALL(evt_win_coin_on, 0, LW(12))
        WAIT_MS(500)
        CALL(uranaisi_ryokin, 0, LW(2))
        CALL(evt_pouch_add_coin, LW(2))
        CALL(evt_win_coin_wait, LW(12))
        WAIT_MS(500)
        CALL(evt_win_coin_off, LW(12))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(uranaisi_starpiece_evt)
    CALL(uranaisi_data_alloc, 1, STRING("un_starpiece"))
    CALL(uranaisi_starpiece_check, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_win_coin_on, 0, LW(12))
        CALL(evt_msg_print, 0, STRING("uranaisi_14"), 0, STRING("me"))
        CALL(uranaisi_ryokin, 1, LW(2))
        CALL(evt_pouch_add_coin, LW(2))
        CALL(evt_win_coin_wait, LW(12))
        WAIT_MS(200)
        CALL(evt_win_coin_off, LW(12))
        ELSE
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(0))
        CALL(uranaisi_starpiece_makelabel, LW(0), LW(0))
        CALL(evt_msg_print, 0, LW(0), 0, STRING("me"))
        CALL(uranaisi_starpiece_setreadflag)
    END_IF
    CALL(uranaisi_data_free)
    RETURN
EVT_END()

EVT_BEGIN(uranaisi_supercoin_evt)
    CALL(uranaisi_data_alloc, 2, STRING("un_supercoin"))
    CALL(uranaisi_supercoin_check, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_win_coin_on, 0, LW(12))
        CALL(evt_msg_print, 0, STRING("uranaisi_16"), 0, STRING("me"))
        CALL(uranaisi_ryokin, 2, LW(2))
        CALL(evt_pouch_add_coin, LW(2))
        CALL(evt_win_coin_wait, LW(12))
        WAIT_MS(200)
        CALL(evt_win_coin_off, LW(12))
        ELSE
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(0))
        CALL(uranaisi_supercoin_makelabel, LW(0), LW(0))
        CALL(evt_msg_print, 0, LW(0), 0, STRING("me"))
        CALL(uranaisi_supercoin_setreadflag)
    END_IF
    CALL(uranaisi_data_free)
    RETURN
EVT_END()

static s32 name_tbl[] = {
    (s32)"card_1", 0, (s32)"card_2", 1, (s32)"card_3", 2, (s32)"card_4", 3,
    (s32)"card_5", 1, (s32)"card_6", 0, (s32)"card_7", 3, (s32)"card_8", 2,
    (s32)"card_9", 1,
};

__declspec(section ".data") EVT_BEGIN(evt_uranai_cap)
    CALL(uranai_cap_evt)
    RETURN
EVT_END()

static USER_FUNC(setmertn) {
    event->ownerNPC = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

static USER_FUNC(ss_check) {
    s32 a;
    s32 z;

    // FAKEMATCH (decomp-permuter): the dead condition moves the ssf load ahead of event->args; casts, temps and
    // u32 index variants do not reproduce it
    a = event->args[0];
    z = !ssf;
    if ((z && !ssf) != 0) {
    }
    evtSetFloat(event, a, ssf);
    return EVT_RETURN_DONE;
}

static USER_FUNC(ss_set) {
    ssf = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_uranaisi_msg_free) {
    if (uranaisi_msgp == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(uranaisi_msgp);
    uranaisi_msgp = NULL;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_uranaisi_msg_alloc) {
    uranaisi_msgp = _mapAlloc(0x100);
    memset(uranaisi_msgp, 0, 0x100);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_uranaisi_msg_set) {
    s32* args = event->args;
    const char* msg = msgSearch((const char*)evtGetValue(event, args[0]));

    sprintf(uranaisi_msgp, msg, uranaisi_ryokin_rtn(0), uranaisi_ryokin_rtn(1), uranaisi_ryokin_rtn(2));
    evtSetValue(event, args[1], (s32)uranaisi_msgp);
    return EVT_RETURN_DONE;
}

static USER_FUNC(evt_osreport) {
    s32* args = event->args;

    switch (evtGetValue(event, args[0])) {
        case 0:
            evtSetValue(event, args[1], (s32)search_evt_moji(evtGetValue(event, GSW(0))));
            break;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(uranai_init_func) {
    char name[64];
    s32 i;

    uranai_wp = _mapAlloc(sizeof(UranaiWork));
    memset(uranai_wp, 0, sizeof(UranaiWork));
    memcpy(uranai_wp->lwData, event->lwData, sizeof(uranai_wp->lwData));
    memcpy(uranai_wp->gwData, evtGetWork()->gwData, sizeof(uranai_wp->gwData));
    for (i = 0; i < 9; i++) {
        sprintf(name, "card_omote_%d", i + 1);
        if (mapGetMapObj(name) != NULL) {
            mapGetMapObj(name)->field_0x4[1] = 5;
        }
        sprintf(name, "card_ura_%d", i + 1);
        if (mapGetMapObj(name) != NULL) {
            mapGetMapObj(name)->field_0x4[1] = 5;
        }
    }
    uranai_wp->capEvent = evtEntry(evt_uranai_cap, 0, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(uranai_exit_func) {
    memcpy(event->lwData, uranai_wp->lwData, sizeof(uranai_wp->lwData));
    memcpy(evtGetWork()->gwData, uranai_wp->gwData, sizeof(uranai_wp->gwData));
    evtDelete(uranai_wp->capEvent);
    _mapFree(uranai_wp);
    return EVT_RETURN_DONE;
}

void uranai_cap(CameraId cameraId, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 half;
    u16 w = uranai_wp->w;
    u16 h = uranai_wp->h;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    CameraEntry saved;
    NpcEntry* npc;
    AnimationPoseData* data;
    Vec bmin;
    Vec bmax;
    f32 scale;

    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(0.0f, 0.0f, w, h, 0.0f, 1.0f);
    GXSetScissor(1, 1, w - 2, h - 2);
    C_MTXPerspective(projMtx, 25.0f, w / h, 1.0f, 1000.0f);
    GXSetProjection(projMtx, GX_PERSPECTIVE);
    {
        static const Vec uranai_pos = {0.0f, 0.0f, 0.0f};
        static const Vec uranai_up = {0.0f, 1.0f, 0.0f};
        static const Vec uranai_target = {0.0f, 0.0f, 0.0f};
        Vec pos;
        Vec up;
        Vec target;

        target = uranai_target;
        target.y = h / 3.0f;
        up = uranai_up;
        pos = uranai_pos;
        half = 0.5f;
        pos.y = h / 3.0f;
        {
            f32 t = tan(0.21816616f);

            pos.z = 0.7f * ((h * half) / t);
        }
        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    saved = *camGetPtr(cameraId);
    npc = npcNameToPtr("\202\244\202\347\202\310\202\242\216t");
    data = animPoseGetAnimBaseDataPtr(npc->poseId);
    bmin = (Vec){data->bboxMin.x, data->bboxMin.y, data->bboxMin.z};
    bmax = (Vec){data->bboxMax.x, data->bboxMax.y, data->bboxMax.z};
    scale = w / (2.0f * (bmax.x - bmin.x));
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    animPosePeraOff(npc->poseId);
    PSMTXIdentity(ident);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, scale);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, scale);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, scale);
    animPosePeraOn(npc->poseId);
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    uranai_wp->buf = smartAlloc(GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0), 3);
    GXSetTexCopySrc(0, 0, w, h);
    GXSetTexCopyDst(w, h, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(uranai_wp->buf->address, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj(&uranai_wp->tex, uranai_wp->buf->address, w, h, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&uranai_wp->tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    uranai_wp->ready = 1;
}

USER_FUNC(uranai_cap_evt) {
    dispEntry(CAMERA_SHADOW, 0.0f, 3, uranai_cap, NULL);
    return EVT_RETURN_BLOCK;
}

void card_tev(MapTevCallbackInfo* info) {
    if (uranai_wp->ready) {
        GXLoadTexObj(smartTexObj(&uranai_wp->tex, &uranai_wp->buf->address), GX_TEXMAP0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        info->tevStage = 1;
        info->texMap = 1;
        info->texCoord = 1;
    }
}

USER_FUNC(uranai_bbox) {
    s32* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 w = evtGetValue(event, args[2]);
    s32 h = evtGetValue(event, args[3]);

    uranai_wp->x = x;
    uranai_wp->y = x;
    uranai_wp->w = x;
    uranai_wp->h = x;
    return EVT_RETURN_DONE;
}

USER_FUNC(card_xlu) {
    const char* name = (const char*)evtGetValue(event, LW(2));

    if (isFirstCall) {
        event->userdata[0] = 255;
    }
    mapGrpSetColor(name, (GXColor){0xFF, 0xFF, 0xFF, event->userdata[0]});
    event->userdata[0] -= 8;
    if (event->userdata[0] < 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

EVT_BEGIN(uranai_init)
    CALL(uranai_init_func)
    SET_VALUE(GW(15), LW(0))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("supotto"), 1)
    CALL(unk_tik_000005e8)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("uranai_mae"), 6144)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, 1000)
    SET_VALUE(LW(0), 0)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_color, 1, STRING("uranai_mae"), LW(0), LW(0), LW(0), 255)
        CALL(evt_mapobj_color, 1, STRING("ie_1_door"), LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("uranai_mae"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ie_1_door"), 1)
    CALL(evt_mapobj_trans, 1, STRING("card"), 0, 0, 0)
    SET_INT_READ_ADDR(PTR(name_tbl))
    LOOP(9)
        READ_INT2(LW(0), LW(1))
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(0), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(0), 6144)
        CALL(evt_mapobj_trans, 1, LW(0), 0, -1000, 0)
    END_LOOP
    CALL(evt_map_set_tevcallback, 1, PTR(card_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("card_omote_5"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("card_omote_5"), 256)
    CALL(evt_offscreen_entry, STRING("ofs"))
    CALL(evt_npc_set_offscreen, STRING("うらない師"), STRING("ofs"))
    CALL(evt_offscreen_get_boundingbox, STRING("ofs"), LW(0), LW(1), LW(2), LW(3))
    CALL(uranai_bbox, LW(0), LW(1), LW(2), LW(3))
    CALL(evt_offscreen_delete, STRING("ofs"))
    CALL(evt_npc_set_offscreen, STRING("うらない師"), 0)
    RETURN
EVT_END()

EVT_BEGIN(uranai_main)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_snd_sfxon, STRING("SFX_EVT_FORTUNE_CARD_MOVE1"), 0)
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 11, -1300, 1300, 3000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, STRING("card_1"), 0, -200, 0)
        CALL(evt_mapobj_rotate, 1, STRING("card_1"), LW(0), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING("card_1"), 0, 180, 0)
        IF_FLOAT_GREATER(LW(0), FLOAT(-20.0f))
            CALL(evt_npc_flag_onoff, 1, STRING("うらない師"), 128)
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_FLOAT_VALUE(LW(8), FLOAT(0.0f))
    SET_INT_READ_ADDR(PTR(name_tbl))
    LOOP(9)
        READ_INT2(LW(0), LW(1))
        SWITCH(LW(1))
            CASE_EQUAL(0)
            SET_VALUE(LW(2), 500)
            SET_VALUE(LF(0), 0)
            CASE_EQUAL(1)
            SET_VALUE(LW(2), -500)
            SET_VALUE(LF(0), 0)
            CASE_EQUAL(2)
            SET_VALUE(LW(2), 500)
            SET_VALUE(LF(0), 1)
            CASE_EQUAL(3)
            SET_VALUE(LW(2), -500)
            SET_VALUE(LF(0), 1)
        END_SWITCH
        BEGIN_INLINE_EVENT
            WAIT_MS(100)
            CALL(evt_mapobj_get_position, LW(0), LW(10), LW(11), LW(12))
            CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_FORTUNE_CARD_MOVE2"), LW(10), LW(11), LW(12), 0)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            SET_VALUE(LW(9), LW(0))
            MULTIPLY_FLOAT(LW(2), FLOAT(10.0f))
            CALL(evt_sub_intpl_msec_init, 11, LW(2), 0, 360)
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value)
                DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
                IF_INT_EQUAL(LF(0), 0)
                    CALL(evt_mapobj_trans, 1, LW(9), LW(8), 0, LW(0))
                    ELSE
                    CALL(evt_mapobj_trans, 1, LW(9), LW(8), LW(0), 0)
                END_IF
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(1), 0)
                    BREAK_LOOP
                END_IF
            END_LOOP
        END_INLINE_EVENT
        ADD_FLOAT(LW(8), FLOAT(0.19921875f))
        WAIT_MS(300)
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_snd_sfxon, STRING("SFX_EVT_FORTUNE_CARD_MOVE3"), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 600, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        SET_FLOAT_VALUE(LW(8), FLOAT(0.0f))
        SET_INT_READ_ADDR(PTR(name_tbl))
        LOOP(9)
            READ_INT2(LW(2), LW(3))
            CALL(evt_mapobj_trans, 1, LW(2), LW(8), -100, 0)
            CALL(evt_mapobj_rotate, 1, LW(2), LW(0), 0, 0)
            CALL(evt_mapobj_trans, 1, LW(2), LW(8), 100, 0)
            ADD_FLOAT(LW(8), FLOAT(0.19921875f))
        END_LOOP
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_sub_intpl_msec_init, 11, 600, -600, 1500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        SET_FLOAT_VALUE(LW(8), FLOAT(0.0f))
        SET_FLOAT_VALUE(LW(9), FLOAT(0.0f))
        SET_INT_READ_ADDR(PTR(name_tbl))
        LOOP(9)
            READ_INT2(LW(2), LW(3))
            SET_FLOAT_VALUE(LW(6), FLOAT(60.0f))
            SET_FLOAT_VALUE(LW(7), LW(9))
            MULTIPLY_FLOAT(LW(7), FLOAT(15.0f))
            SUBTRACT_FLOAT(LW(6), LW(7))
            CALL(evt_mapobj_trans, 1, LW(2), LW(8), -100, 0)
            IF_FLOAT_LESS(LW(0), LW(6))
                CALL(evt_mapobj_rotate, 1, LW(2), LW(6), 0, 0)
                ELSE
                CALL(evt_mapobj_rotate, 1, LW(2), LW(0), 0, 0)
            END_IF
            CALL(evt_mapobj_trans, 1, LW(2), LW(8), 100, 0)
            ADD_FLOAT(LW(8), FLOAT(0.19921875f))
            ADD_FLOAT(LW(9), FLOAT(1.0f))
        END_LOOP
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_FLOAT_VALUE(LW(8), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(9), FLOAT(0.0f))
    SET_INT_READ_ADDR(PTR(name_tbl))
    LOOP(9)
        READ_INT2(LW(2), LW(3))
        SET_FLOAT_VALUE(LW(6), FLOAT(60.0f))
        SET_FLOAT_VALUE(LW(7), LW(9))
        MULTIPLY_FLOAT(LW(7), FLOAT(15.0f))
        SUBTRACT_FLOAT(LW(6), LW(7))
        BEGIN_INLINE_EVENT
            IF_INT_EQUAL(LW(9), 4)
                CALL(evt_snd_sfxon, STRING("SFX_EVT_FORTUNE_CARD_MOVE4"), 0)
                CALL(evt_sub_intpl_msec_init, 0, 0, 500, 1000)
                ELSE
                CALL(evt_sub_intpl_msec_init, 1, 0, -3000, 1000)
            END_IF
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value)
                DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
                CALL(evt_mapobj_trans, 1, LW(2), 0, LW(0), 0)
                CALL(evt_mapobj_trans, 1, LW(2), LW(8), -100, 0)
                CALL(evt_mapobj_rotate, 1, LW(2), LW(6), 0, 0)
                CALL(evt_mapobj_trans, 1, LW(2), LW(8), 100, 0)
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(1), 0)
                    BREAK_LOOP
                END_IF
            END_LOOP
        END_INLINE_EVENT
        ADD_FLOAT(LW(8), FLOAT(0.19921875f))
        ADD_FLOAT(LW(9), FLOAT(1.0f))
    END_LOOP
    WAIT_MS(1200)
    CALL(card_camid, STRING("card_omote_5"), 4)
    CALL(card_camid, STRING("card_ura_5"), 4)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(50.0f))
    SET_FLOAT_VALUE(GW(2), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(3), FLOAT(0.0f))
    CALL(evt_snd_sfxon, STRING("SFX_EVT_FORTUNE_CARD_MOVE5"), 0)
    BEGIN_INLINE_EVENT_GET_ID(LW(9))
        LOOP(0)
            CALL(evt_mapobj_trans, 1, STRING("card_5"), GW(0), GW(1), GW(2))
            CALL(evt_mapobj_rotate, 1, STRING("card_5"), 0, GW(3), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 13, 500, 700, 300)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            SET_FLOAT_VALUE(GW(1), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 12, 700, -200, 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            SET_FLOAT_VALUE(GW(1), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, -450, 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            SET_FLOAT_VALUE(GW(2), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 37800, 2000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            SET_FLOAT_VALUE(GW(3), LW(0))
            IF_FLOAT_GREATER(GW(3), FLOAT(3600.0f))
                CALL(evt_mapobj_flag_onoff, 1, 1, STRING("card_omote_5"), 1)
                CALL(evt_npc_flag_onoff, 0, STRING("うらない師"), 128)
            END_IF
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(2500)
    DELETE_EVENT(LW(9))
    SET_VALUE(LW(0), GW(15))
    RETURN
EVT_END()

EVT_BEGIN(uranai_exit)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("uranai_mae"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_1_door"), 1)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_color, 1, STRING("uranai_mae"), LW(0), LW(0), LW(0), 255)
        CALL(evt_mapobj_color, 1, STRING("ie_1_door"), LW(0), LW(0), LW(0), 255)
        SET_VALUE(LW(2), 255)
        SUBTRACT(LW(2), LW(0))
        CALL(evt_mapobj_color, 1, STRING("supotto"), 255, 255, 255, LW(2))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("supotto"), 1)
    CALL(evt_mapobj_color, 1, STRING("supotto"), 255, 255, 255, 255)
    SET_INT_READ_ADDR(PTR(name_tbl))
    LOOP(9)
        READ_INT2(LW(0), LW(1))
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(0), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(0), 6144)
    END_LOOP
    CALL(uranai_exit_func)
    RETURN
EVT_END()

EVT_BEGIN(uranaisi_table_talk)
    CALL(setmertn, STRING("うらない師"))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
    CALL(evt_npc_set_ry, STRING("me"), 180)
    LOOP(0)
        IF_INT_EQUAL(GSWF(6), 0)
            IF_INT_EQUAL(GSWF(5), 0)
                CALL(evt_msg_print, 0, STRING("uranaisi_00"), 0, STRING("me"))
                SET_VALUE(GSWF(5), 1)
                SET_VALUE(GSWF(237), 1)
                ELSE
                IF_INT_EQUAL(GSWF(237), 0)
                    CALL(evt_msg_print, 0, STRING("uranaisi_01"), 0, STRING("me"))
                    SET_VALUE(GSWF(237), 1)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("uranaisi_19"), 0, STRING("me"))
                END_IF
            END_IF
            CALL(evt_msg_select, 0, STRING("uranaisi_03"))
            IF_INT_EQUAL(LW(0), 1)
                CALL(evt_msg_print_add, 0, STRING("uranaisi_06"))
                GOTO(0)
            END_IF
            WAIT_MS(200)
            ELSE
            CALL(evt_msg_print, 0, STRING("uranaisi_02"), 0, STRING("me"))
        END_IF
        SET_VALUE(GSWF(6), 1)
        CALL(evt_win_coin_on, 0, LW(12))
        CALL(evt_uranaisi_msg_alloc)
        CALL(evt_uranaisi_msg_set, STRING("uranaisi_04"), LW(1))
        CALL(evt_msg_select, 1, LW(1))
        CALL(evt_uranaisi_msg_free)
        IF_INT_EQUAL(LW(0), 4)
            CALL(evt_win_coin_off, LW(12))
            CALL(evt_msg_print_add, 0, STRING("uranaisi_06"))
            GOTO(0)
        END_IF
        CALL(uranaisi_ryokin, LW(0), LW(2))
        CALL(evt_pouch_get_coin, LW(1))
        IF_INT_LESS(LW(1), LW(2))
            CALL(evt_msg_print_add, 0, STRING("uranaisi_07"))
            CALL(evt_win_coin_off, LW(12))
            GOTO(0)
        END_IF
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_msg_print_add, 0, STRING("uranaisi_08"))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING("uranaisi_09"))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING("uranaisi_11"))
        END_SWITCH
        MULTIPLY(LW(2), -1)
        CALL(evt_pouch_add_coin, LW(2))
        CALL(evt_win_coin_wait, LW(12))
        WAIT_MS(200)
        CALL(evt_win_coin_off, LW(12))
        CALL_CHILD(PTR(uranai_init))
        CALL(evt_msg_print, 0, STRING("uranaisi_12"), 0, STRING("me"))
        BEGIN_INLINE_EVENT
            CALL(evt_npc_set_anim, STRING("me"), STRING("I_1"))
            WAIT_MS(240)
            CALL(evt_npc_set_anim, STRING("me"), STRING("S_2"))
        END_INLINE_EVENT
        CALL_CHILD(PTR(uranai_main))
        CALL(evt_npc_set_anim, STRING("me"), STRING("D_1"))
        WAIT_MS(170)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL_CHILD(PTR(uranaisi_next_evt))
            CASE_EQUAL(1)
            CALL_CHILD(PTR(uranaisi_starpiece_evt))
            CASE_EQUAL(2)
            CALL_CHILD(PTR(uranaisi_supercoin_evt))
        END_SWITCH
        CALL_CHILD(PTR(uranai_exit))
    END_LOOP
    LABEL(0)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(uranaisi_direct_talk)
    CALL(evt_msg_print, 0, STRING("uranaisi_18"), 0, STRING("me"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(uranaisi_init)
    CALL(evt_run_case_evt, 9, 1, STRING("uranai"), 0, PTR(uranaisi_table_talk), 0)
    RETURN
EVT_END()

EVT_BEGIN(unk_evt_tik_0000f438)
    CALL_CHILD(PTR(npc_init_evt))
    IF_INT_LESS(GSW(0), 20)
        CALL(evt_npc_set_position, STRING("me"), 400, -20, 175)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(starmaniac_get_event)
    CALL(ss_set, 1)
    RETURN
EVT_END()

EVT_BEGIN(starmaniac_talk)
    CALL(evt_badgeShop_starmaniac_get_kind_cnt, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("starmaniac_02"), 0, STRING("me"))
        RETURN
    END_IF
    CALL(unk_tik_000005c0)
    IF_INT_EQUAL(GSWF(1325), 0)
        CALL(evt_msg_print, 0, STRING("starmaniac_00"), 0, STRING("me"))
        SET_VALUE(GSWF(1325), 1)
        ELSE
        CALL(evt_msg_print, 0, STRING("starmaniac_01"), 0, STRING("me"))
    END_IF
    CALL(evt_msg_select, 0, STRING("starmaniac_03"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("starmaniac_05"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_pouch_get_starpiece, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("starmaniac_06"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("starmaniac_07"))
    LABEL(0)
    CALL(evt_win_coin_on, 2, LW(12))
    CALL(evt_win_other_select, 13)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("starmaniac_08"), 0, STRING("me"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_sub_get_language, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_insert, 0, STRING("starmaniac_09"), 0, STRING("me"), LW(3), LW(2), LW(4))
        ELSE
        CALL(evt_msg_print_insert, 0, STRING("starmaniac_09"), 0, STRING("me"), LW(2), LW(3), LW(4))
    END_IF
    CALL(evt_msg_select, 0, STRING("starmaniac_10"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print_add, 0, STRING("starmaniac_11"))
        GOTO(0)
    END_IF
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print_add, 0, STRING("starmaniac_15"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_badgeShop_starmaniac_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_starpiece, LW(3))
    CALL(evt_win_coin_wait, LW(12))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(12))
    CALL(evt_badgeShop_starmaniac_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("starmaniac_12"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_pouch_get_starpiece, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("starmaniac_12"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("starmaniac_13"))
    CALL(evt_msg_select, 0, STRING("starmaniac_10"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("starmaniac_14"))
        CALL(unk_tik_00000598)
        RETURN
    END_IF
    CALL(evt_msg_continue)
    GOTO(0)
    CALL(unk_tik_00000598)
    RETURN
EVT_END()

EVT_BEGIN(johoyaketi_talk)
    IF_INT_EQUAL(GSWF(3), 0)
        CALL(evt_msg_print, 0, STRING("johoyaketi_00"), 0, STRING("me"))
        SET_VALUE(GSWF(3), 1)
        RETURN
    END_IF
    CALL(johoya_keti_newjoho_check, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(johoya_keti_oldspeak_check, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("johoyaketi_08"), 0, STRING("me"))
            ELSE
            CALL(evt_msg_print, 0, STRING("johoyaketi_06"), 0, STRING("me"))
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(0))
            CALL(johoya_keti_oldspeak_makelabel, LW(0), LW(0), LW(3), LW(4), LW(5))
            CALL(evt_msg_print_add, 0, LW(0))
            CALL(johoya_keti_oldspeak_setreadflag)
            CALL(evt_msg_print_add, 0, STRING("johoyaketi_07"))
        END_IF
        ELSE
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        CALL(johoya_keti_newjoho_makelabel, LW(0), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_msg_print_insert, 0, STRING("johoyaketi_01"), 0, STRING("me"), LW(5), LW(4), LW(3))
        CALL(evt_win_coin_on, 0, LW(12))
        CALL(evt_msg_select, 0, STRING("johoyaketi_02"))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_pouch_get_coin, LW(0))
            IF_INT_LESS(LW(0), LW(5))
                CALL(evt_msg_print_add, 0, STRING("johoyaketi_09"))
                CALL(evt_win_coin_off, LW(12))
                RETURN
            END_IF
            MULTIPLY(LW(5), -1)
            CALL(evt_pouch_add_coin, LW(5))
            CALL(evt_win_coin_wait, LW(12))
            WAIT_MS(500)
            CALL(evt_win_coin_off, LW(12))
            CALL(evt_msg_print_add, 0, LW(2))
            CALL(johoya_keti_newjoho_setreadflag)
            CALL(evt_msg_print_add, 0, STRING("johoyaketi_07"))
            ELSE
            CALL(evt_win_coin_off, LW(12))
            CALL(johoya_keti_oldspeak_check, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("johoyaketi_04"))
                ELSE
                CALL(evt_msg_print_add, 0, STRING("johoyaketi_05"))
                SUBTRACT(LW(0), 1)
                CALL(evt_sub_random, LW(0), LW(0))
                CALL(johoya_keti_oldspeak_makelabel, LW(0), LW(0), LW(3), LW(4), LW(5))
                CALL(evt_msg_print_add, 0, LW(0))
                CALL(johoya_keti_oldspeak_setreadflag)
                CALL(evt_msg_print_add, 0, STRING("johoyaketi_07"))
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(kuribo5_init)
    RETURN
EVT_END()

EVT_BEGIN(kuribo5_talk)
    SWITCH(GSW(0))
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("tik_001_01"), 0, STRING("me"))
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("tik_001_02"), 0, STRING("me"))
        CASE_LESS(164)
        CALL(evt_msg_print, 0, STRING("tik_001_03"), 0, STRING("me"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("tik_001_04"), 0, STRING("me"))
        CASE_LESS(261)
        CALL(evt_msg_print, 0, STRING("tik_001_05"), 0, STRING("me"))
        CASE_LESS(339)
        CALL(evt_msg_print, 0, STRING("tik_001_06"), 0, STRING("me"))
        CASE_LESS(373)
        CALL(evt_msg_print, 0, STRING("tik_001_07"), 0, STRING("me"))
        CASE_LESS(401)
        CALL(evt_msg_print, 0, STRING("tik_001_08"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("tik_001_09"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(chusan4_init)
    CALL(evt_npc_set_position, STRING("me"), -175, -19, 235)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    RETURN
EVT_END()

EVT_BEGIN(chusan4_regl)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("me"), 175, 235, 0, FLOAT(40.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING("me"), -175, 235, 0, FLOAT(40.0f), 0)
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(chusan4_talk)
    SWITCH(GSW(0))
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("tik_002_01"), 0, STRING("me"))
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("tik_002_02"), 0, STRING("me"))
        CASE_LESS(164)
        CALL(evt_msg_print, 0, STRING("tik_002_03"), 0, STRING("me"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("tik_002_04"), 0, STRING("me"))
        CASE_LESS(261)
        CALL(evt_msg_print, 0, STRING("tik_002_05"), 0, STRING("me"))
        CASE_LESS(339)
        CALL(evt_msg_print, 0, STRING("tik_002_06"), 0, STRING("me"))
        CASE_LESS(373)
        CALL(evt_msg_print, 0, STRING("tik_002_07"), 0, STRING("me"))
        CASE_LESS(401)
        CALL(evt_msg_print, 0, STRING("tik_002_08"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("tik_002_09"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(borodo3_init)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(borodo3_regl)
    CALL_CHILD(PTR(tik_villager_urouro))
    RETURN
EVT_END()

EVT_BEGIN(borodo3_talk)
    SWITCH(GSW(0))
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("tik_003_01"), 0, STRING("me"))
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("tik_003_02"), 0, STRING("me"))
        CASE_LESS(164)
        CALL(evt_msg_print, 0, STRING("tik_003_03"), 0, STRING("me"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("tik_003_04"), 0, STRING("me"))
        CASE_LESS(261)
        CALL(evt_msg_print, 0, STRING("tik_003_05"), 0, STRING("me"))
        CASE_LESS(339)
        CALL(evt_msg_print, 0, STRING("tik_003_06"), 0, STRING("me"))
        CASE_LESS(373)
        CALL(evt_msg_print, 0, STRING("tik_003_07"), 0, STRING("me"))
        CASE_LESS(401)
        CALL(evt_msg_print, 0, STRING("tik_003_08"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("tik_003_09"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(borodo4_init)
    RETURN
EVT_END()

EVT_BEGIN(borodo4_talk)
    SWITCH(GSW(0))
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("tik_004_01"), 0, STRING("me"))
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("tik_004_02"), 0, STRING("me"))
        CASE_LESS(164)
        CALL(evt_msg_print, 0, STRING("tik_004_03"), 0, STRING("me"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("tik_004_04"), 0, STRING("me"))
        CASE_LESS(261)
        CALL(evt_msg_print, 0, STRING("tik_004_05"), 0, STRING("me"))
        CASE_LESS(339)
        CALL(evt_msg_print, 0, STRING("tik_004_06"), 0, STRING("me"))
        CASE_LESS(373)
        CALL(evt_msg_print, 0, STRING("tik_004_07"), 0, STRING("me"))
        CASE_LESS(401)
        CALL(evt_msg_print, 0, STRING("tik_004_08"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("tik_004_09"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(pinkbom_init)
    RETURN
EVT_END()

EVT_BEGIN(pinkbom_talk)
    SWITCH(GSW(0))
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("tik_005_01"), 0, STRING("me"))
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("tik_005_02"), 0, STRING("me"))
        CASE_LESS(164)
        CALL(evt_msg_print, 0, STRING("tik_005_03"), 0, STRING("me"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("tik_005_04"), 0, STRING("me"))
        CASE_LESS(261)
        CALL(evt_msg_print, 0, STRING("tik_005_05"), 0, STRING("me"))
        CASE_LESS(339)
        CALL(evt_msg_print, 0, STRING("tik_005_06"), 0, STRING("me"))
        CASE_LESS(373)
        CALL(evt_msg_print, 0, STRING("tik_005_07"), 0, STRING("me"))
        CASE_LESS(401)
        CALL(evt_msg_print, 0, STRING("tik_005_08"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("tik_005_09"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(master_2_init)
    CALL(evt_npc_set_position, STRING("me"), -85, 95, -535)
    RETURN
EVT_END()

EVT_BEGIN(master_2_talk)
    SWITCH(GSW(0))
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("tik_005_10"), 0, STRING("me"))
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("tik_005_11"), 0, STRING("me"))
        CASE_LESS(164)
        CALL(evt_msg_print, 0, STRING("tik_005_12"), 0, STRING("me"))
        CASE_LESS(215)
        CALL(evt_msg_print, 0, STRING("tik_005_13"), 0, STRING("me"))
        CASE_LESS(261)
        CALL(evt_msg_print, 0, STRING("tik_005_14"), 0, STRING("me"))
        CASE_LESS(339)
        CALL(evt_msg_print, 0, STRING("tik_005_15"), 0, STRING("me"))
        CASE_LESS(373)
        CALL(evt_msg_print, 0, STRING("tik_005_16"), 0, STRING("me"))
        CASE_LESS(401)
        CALL(evt_msg_print, 0, STRING("tik_005_17"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("tik_005_18"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"うらない師"*/"\x82\xA4\x82\xE7\x82\xC8\x82\xA2\x8E\x74", 525824, 0, (s32)uranaisi_init, 0, (s32)uranaisi_direct_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"星マニア"*/"\x90\xAF\x83\x7D\x83\x6A\x83\x41",
    525824, 0, (s32)unk_evt_tik_0000f438, 0, (s32)starmaniac_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"情報屋ケチ"*/"\x8F\xEE\x95\xF1\x89\xAE\x83\x50\x83\x60", 525824,
    0, (s32)npc_init_evt, 0, (s32)johoyaketi_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"クリボー５"*/"\x83\x4E\x83\x8A\x83\x7B\x81\x5B\x82\x54", 525824, 0,
    (s32)kuribo5_init, 0, (s32)kuribo5_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"チューさん４"*/"\x83\x60\x83\x85\x81\x5B\x82\xB3\x82\xF1\x82\x53", 525824, 0, (s32)chusan4_init,
    (s32)chusan4_regl, (s32)chusan4_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"ボロドー３"*/"\x83\x7B\x83\x8D\x83\x68\x81\x5B\x82\x52", 525824, 0, (s32)borodo3_init, (s32)borodo3_regl,
    (s32)borodo3_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"ボロドー４"*/"\x83\x7B\x83\x8D\x83\x68\x81\x5B\x82\x53", 525824, 0, (s32)borodo4_init, 0, (s32)borodo4_talk,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ピンクボム兵"*/"\x83\x73\x83\x93\x83\x4E\x83\x7B\x83\x80\x95\xBA", 525824, 0, (s32)pinkbom_init, 0, (s32)pinkbom_talk, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"マスター２"*/"\x83\x7D\x83\x58\x83\x5E\x81\x5B\x82\x51", 525824, 0, (s32)master_2_init, 0, (s32)master_2_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"店員"*/"\x93\x58\x88\xF5",
    525824, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_door_01_00)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("supotto"), 1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("ie_1_door"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_01_00)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            ELSE
            WAIT_MS(300)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_1_1"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(300)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_1_1"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_01_01)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(100)
            ELSE
            WAIT_MS(200)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_1_2"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(200)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_1_2"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_01_02)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(200)
            ELSE
            WAIT_MS(100)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_1_3"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(200)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_1_3"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") s32 door_data_01_npc[] = {
    (s32)/*"うらない師"*/"\x82\xA4\x82\xE7\x82\xC8\x82\xA2\x8E\x74", 0,
};

static __declspec(section ".data") EVT_BEGIN(evt_wall_01)
    IF_INT_EQUAL(LW(6), 0)
        SPAWN_EVENT(PTR(evt_wall_01_00))
        SPAWN_EVENT(PTR(evt_wall_01_01))
        SPAWN_EVENT(PTR(evt_wall_01_02))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_open_01)
    CALL(evt_mapobj_trans, 1, STRING("card"), 0, -1000, 0)
    CALL(evt_mapobj_trans, 1, STRING("ie_1_naka"), 0, FLOAT(0.19921875f), 0)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    CALL(evt_mobj_check, STRING("pblk1"), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("pblk1"), 2)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_close_01)
    CALL(evt_mapobj_trans, 1, STRING("card"), 0, -1000, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("mon"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kuro_maku"), 1)
    CALL(evt_door_end_wait)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("mon"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kuro_maku"), 1)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    CALL(evt_mobj_check, STRING("pblk1"), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_mobj_flag_onoff, 0, STRING("pblk1"), 2)
    END_IF
    RETURN
EVT_END()

static s32 door_data_01[] = {
    2, 3, 1, (s32)"ie_1_door", (s32)"a_door_1_N", (s32)"a_door_1", (s32)"ie_1_soto", 0,
    (s32)"ie_1_naka", 0, (s32)evt_door_01_00, 0, (s32)evt_wall_01, (s32)door_data_01_npc, 0, 0,
    (s32)evt_open_01, (s32)evt_close_01,
};

static __declspec(section ".data") EVT_BEGIN(evt_door_02_00)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("ie_2_door"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_02_00)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            ELSE
            WAIT_MS(300)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_2_1"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(300)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_2_1"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_02_01)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(100)
            ELSE
            WAIT_MS(200)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_2_2"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(200)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_2_2"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_02_02)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(200)
            ELSE
            WAIT_MS(100)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_2_3"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(200)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_2_3"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_02_03)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(300)
            ELSE
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_2_4"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(300)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_2_4"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_02)
    IF_INT_EQUAL(LW(6), 0)
        SPAWN_EVENT(PTR(evt_wall_02_00))
        SPAWN_EVENT(PTR(evt_wall_02_01))
        SPAWN_EVENT(PTR(evt_wall_02_02))
        SPAWN_EVENT(PTR(evt_wall_02_03))
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") s32 mise_npc[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", 0,
};

__declspec(section ".data") EVT_BEGIN(evt_open_02)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

EVT_BEGIN(evt_close_02)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

static s32 door_data_02[] = {
    2, 3, 1, (s32)"ie_2_door", (s32)"a_door_2_N", (s32)"a_door_2", (s32)"ie_2_soto", 0,
    (s32)"ie_2_naka", 0, (s32)evt_door_02_00, 0, (s32)evt_wall_02, (s32)mise_npc, 0, 0,
    (s32)evt_open_02, (s32)evt_close_02,
};

static __declspec(section ".data") EVT_BEGIN(evt_door_03_00)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("ie_3_door"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_03_00)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            ELSE
            WAIT_MS(300)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_3_1"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(300)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_3_1"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_03_01)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(100)
            ELSE
            WAIT_MS(200)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_3_2"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(200)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_3_2"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_03_02)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(200)
            ELSE
            WAIT_MS(100)
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_3_3"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(200)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_3_3"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_wall_03_03)
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LW(1), 0)
            WAIT_MS(300)
            ELSE
        END_IF
        CALL(evt_mapobj_get_position, STRING("ie_3_4"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(1), 0)
        WAIT_MS(300)
        CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
        ELSE
        CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
    END_IF
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ie_3_4"), 0, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_03)
    IF_INT_EQUAL(LW(6), 0)
        SPAWN_EVENT(PTR(evt_wall_03_00))
        SPAWN_EVENT(PTR(evt_wall_03_01))
        SPAWN_EVENT(PTR(evt_wall_03_02))
        SPAWN_EVENT(PTR(evt_wall_03_03))
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") s32 door_data_03_npc[] = {
    (s32)/*"情報屋ケチ"*/"\x8F\xEE\x95\xF1\x89\xAE\x83\x50\x83\x60", (s32)/*"ボロドー４"*/"\x83\x7B\x83\x8D\x83\x68\x81\x5B\x82\x53", (s32)/*"ピンクボム兵"*/"\x83\x73\x83\x93\x83\x4E\x83\x7B\x83\x80\x95\xBA", (s32)/*"マスター２"*/"\x83\x7D\x83\x58\x83\x5E\x81\x5B\x82\x51", 0,
};

__declspec(section ".data") EVT_BEGIN(evt_open_03)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

EVT_BEGIN(evt_close_03)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

static __declspec(section ".data") s32 door_data_03_mobj[] = {
    (s32)"kururin1", 0,
};

static s32 door_data_03[] = {
    2, 3, 1, (s32)"ie_3_door", (s32)"a_door_3_N", (s32)"a_door_3", (s32)"ie_3_soto", 0,
    (s32)"ie_3_naka", 0, (s32)evt_door_03_00, 0, (s32)evt_wall_03, (s32)door_data_03_npc, (s32)door_data_03_mobj, 0,
    (s32)evt_open_03, (s32)evt_close_03,
};

static __declspec(section ".data") EVT_BEGIN(evt_door_04_00)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("ie_4door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_door_04_01)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("ie_4door"), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_wall_04)
    SET_FLOAT_VALUE(LW(2), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("ie_4_1_"), 0, LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_open_04_open)
    SWITCH(GSW(0))
        CASE_LESS(377)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_4_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ie_4_2"), 1)
        IF_INT_EQUAL(GW(10), 0)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("wa_pu"), 1)
            ELSE
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("wa_pu"), 1)
        END_IF
        CASE_LESS(405)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ie_4_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_4_2"), 1)
        IF_INT_EQUAL(GW(10), 0)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("wa_pu"), 1)
            ELSE
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("wa_pu"), 1)
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_4_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ie_4_2"), 1)
        IF_INT_EQUAL(GW(10), 0)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("wa_pu"), 1)
            ELSE
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("wa_pu"), 1)
        END_IF
    END_SWITCH
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

static EVT_BEGIN(evt_door_04_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    IF_INT_LESS(GSW(0), 377)
        IF_INT_EQUAL(GSWF(1329), 0)
            CALL(evt_door_end_wait)
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_party_stop, 0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 40)
            CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(120.0f))
            BEGIN_INLINE_EVENT
                CALL(evt_mario_set_dir, 270, 200, 0)
            END_INLINE_EVENT
            CALL(evt_party_set_dir, 0, 90, 200)
            CALL(evt_msg_print_party, STRING("tik_00_tensou_1"))
            SET_VALUE(GSWF(1329), 1)
            CALL(evt_party_run, 0)
            CALL(evt_mario_key_onoff, 1)
            RETURN
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 377)
        CALL(evt_door_end_wait)
        CALL(evt_mario_key_onoff, 0)
        CALL_CHILD(PTR(kurihakase_event))
        CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    RETURN
EVT_END()

static s32 door_data_04[] = {
    0, 3, 1, (s32)"ie_4door", (s32)"a_door_4_N", (s32)"a_door_4", (s32)"ie_4_soto", 0,
    (s32)"ie_4_naka", 0, (s32)evt_door_04_00, (s32)evt_door_04_01, (s32)evt_wall_04, 0, 0, 0,
    (s32)evt_open_04_open, (s32)evt_door_04_close,
};

EVT_BEGIN(evt_door_stg7_open)
    IF_INT_EQUAL(GSWF(1327), 0)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_toge, 1, 0, 0, 0)
        CALL(evt_msg_print, 0, STRING("tik_000"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    SPAWN_EVENT(PTR(evt_door_open))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_door_stg7_close)
    SET_VALUE(GSWF(1327), 1)
    SPAWN_EVENT(PTR(evt_door_close))
    RETURN
EVT_END()

static EVT_BEGIN(evt_door_04_entry)
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, LW(1), 1)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 0)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(2), 0)
        SET_VALUE(LW(15), 0)
        CALL(evt_run_case_evt, 9, 1, LW(2), 0, PTR(evt_door_stg7_close), 0)
    END_IF
    IF_INT_NOT_EQUAL(LW(3), 0)
        SET_VALUE(LW(15), 0)
        CALL(evt_run_case_evt, 9, 1, LW(3), 0, PTR(evt_door_stg7_open), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(tensou_return)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_map_playanim, STRING("anm_wa-p"), 1, 0)
    BEGIN_INLINE_EVENT
        LOOP(10)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("wa_pu"), 1)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_hit_get_position, STRING("A_tensou"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WARP_LIGHT1"), LW(0), LW(1), LW(2), LW(9))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 5, 0, 5760, 4000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            MODULO(LW(0), 360)
            CALL(evt_party_set_dispdir, 0, LW(0))
            ADD(LW(0), 180)
            MODULO(LW(0), 360)
            CALL(evt_mario_set_dispdir, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 12, 0, 100, 800)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(scale_func, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WARP1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
    CALL(evt_party_get_pos, 0, LW(5), LW(6), LW(7))
    CALL(evt_sub_intpl_msec_init, 12, 70, 0, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(LW(8), LW(0))
        ADD(LW(0), LW(3))
        CALL(evt_mario_set_pos, LW(2), LW(0), LW(4))
        ADD(LW(8), LW(6))
        CALL(evt_party_set_pos, 0, LW(5), LW(8), LW(7))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(9))
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_color, 1, STRING("wa_pu"), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("wa_pu"), 1)
    CALL(evt_mapobj_color, 1, STRING("wa_pu"), 255, 255, 255, 255)
    CALL(evt_mario_cont_onoff, 1)
    CALL(evt_party_cont_onoff, 0, 1)
    CALL(evt_party_cont_onoff, 1, 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    RETURN
EVT_END()

EVT_BEGIN(tensou_init_event)
    SET_VALUE(GW(10), 0)
    SWITCH(GSW(0))
        CASE_LESS(377)
        CALL(evt_map_playanim, STRING("anm_PC"), 1, 0)
        CALL(evt_map_playanim, STRING("anm_Terop"), 1, 0)
        CALL(evt_map_playanim, STRING("anm_tiktik"), 1, 0)
        CASE_LESS(405)
        CASE_DEFAULT
        CALL(evt_map_playanim, STRING("anm_PC"), 1, 0)
        CALL(evt_map_playanim, STRING("anm_Terop"), 1, 0)
        CALL(evt_map_playanim, STRING("anm_tiktik"), 1, 0)
    END_SWITCH
    IF_INT_EQUAL(GSWF(4175), 0)
        RETURN
    END_IF
    SET_VALUE(GSWF(4175), 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_pos, -305, 38, -250)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_pos, 0, -275, 38, -250)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_party_set_pos, 1, -290, 38, -265)
    CALL(evt_party_set_dir, 1, 270, 0)
    CALL(evt_cam_road_reset)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(0), PTR(door_data_04))
    SPAWN_EVENT(PTR(evt_door_open_quick))
    CALL_CHILD(PTR(tensou_return))
    SWITCH(GSW(0))
        CASE_LESS(377)
        IF_INT_EQUAL(GSWF(1328), 0)
            WAIT_MS(1500)
            CALL(evt_msg_print_party, STRING("tik_00_tensou_0"))
            SET_VALUE(GSWF(1328), 1)
        END_IF
        CASE_LESS(378)
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, -300, 109, 111, -300, 70, -184, 500, 11)
        WAIT_MS(500)
        CALL(evt_party_set_dir, 0, 270, 300)
        WAIT_MS(300)
        CALL(evt_party_set_dir, 0, 90, 300)
        WAIT_MS(300)
        CALL(evt_party_set_dir, 0, 270, 300)
        WAIT_MS(300)
        CALL(evt_mario_set_dir, 90, 300, 0)
        CALL(evt_msg_print_party, STRING("stg7_tik_01"))
        CALL(evt_mario_set_pose, STRING("M_N_1"))
        WAIT_MS(700)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_cam3d_evt_off, 500, 11)
        CASE_DEFAULT
    END_SWITCH
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

USER_FUNC(card_camid) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 camId = evtGetValue(event, args[1]);

    if (mapGetMapObj(name) != NULL) {
        mapGetMapObj(name)->field_0x4[1] = camId;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_tik_000005e8) {
    MapObject* obj = mapGetMapObj("supotto");

    obj->field_0x4[0] = 10;
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_tik_000005c0) {
    psndSetFlag(0x80);
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_tik_00000598) {
    psndClearFlag(0x80);
    return EVT_RETURN_DONE;
}

USER_FUNC(mario_key_onoff_wait) {
    marioGetPtr();
    switch (!marioChkKey()) {
        default:
            return EVT_RETURN_BLOCK;
        case 0:
            return EVT_RETURN_DONE;
    }
}

static USER_FUNC(scale_func) {
    f32 s = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);

    mario->scale = (Vec){s, s, s};
    if (party != NULL) {
        party->scale = (Vec){s, s, s};
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(tensou_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_mov_pos2, -305, -250, FLOAT(100.0f))
    CALL(evt_party_move_pos2, 0, -275, -250, FLOAT(100.0f))
    CALL(evt_hit_get_position, STRING("tensou"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WARP_LIGHT1"), LW(0), LW(1), LW(2), LW(9))
    SET_VALUE(GW(0), 0)
    CALL(evt_mario_get_dispdir, LW(0))
    CALL(evt_mario_get_dispdir, LW(1))
    BEGIN_INLINE_EVENT
        LOOP(0)
            ADD(LW(0), GW(0))
            ADD(LW(1), GW(0))
            CALL(evt_mario_set_dispdir, LW(0))
            CALL(evt_party_set_dispdir, 0, LW(1))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WARP1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 30, 3000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mario_cam_off)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
    CALL(evt_party_get_pos, 0, LW(5), LW(6), LW(7))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 12, 100, 0, 800)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(scale_func, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WARP2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 12, 0, 100, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(LW(8), LW(0))
        ADD(LW(0), LW(3))
        CALL(evt_mario_set_pos, LW(2), LW(0), LW(4))
        ADD(LW(8), LW(6))
        CALL(evt_party_set_pos, 0, LW(5), LW(8), LW(7))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(2000)
    CALL(evt_snd_sfxoff, LW(9))
    SET_VALUE(GSWF(1326), 1)
    CALL(evt_bero_mapchange, STRING("aji_07"), 0)
    RETURN
EVT_END()

EVT_BEGIN(tensou_anim_event)
    SET_VALUE(GW(10), 1)
    CALL(evt_map_playanim, STRING("anm_saisho"), 0, 0)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("hikari"), 1)
    CALL(evt_map_checkanim, STRING("anm_saisho"), LW(1), LW(2))
    WAIT_MS(LW(2))
    CALL(evt_map_playanim, STRING("anm_wa-p"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(tensou_sw_event)
    CALL(evt_snd_sfxon, STRING("SFX_STG7_SWITCH_WARP1"), 0)
    IF_INT_LESS(GSW(0), 377)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("wa_pu"), 1)
        SPAWN_EVENT(PTR(tensou_anim_event))
        CALL(evt_run_case_evt, 0, 1, STRING("tensou"), 0, PTR(tensou_event), 0)
        CALL(evt_exit_case_evt)
        ELSE
        IF_INT_GREATER_OR_EQUAL(GSW(0), 403)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("sui__1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("sui__2"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("wa_pu"), 1)
            SPAWN_EVENT(PTR(tensou_anim_event))
            CALL(evt_run_case_evt, 0, 1, STRING("tensou"), 0, PTR(tensou_event), 0)
            CALL(evt_exit_case_evt)
            ELSE
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_msg_toge, 1, 0, 0, 0)
            CALL(evt_msg_print, 0, STRING("stg7_tik_01_01"), 0, 0)
            CALL(evt_mario_key_onoff, 1)
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(kurihakase_event)
    CALL(evt_party_stop, 0)
    CALL(evt_snd_envon_f, 272, STRING("ENV_STG0_TIK2"), 2000)
    CALL(evt_npc_set_position, STRING("クリハカセ"), -30, 0, 170)
    CALL(evt_npc_flag_onoff, 1, STRING("クリハカセ"), 1536)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        SUBTRACT(LW(0), 40)
        CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(120.0f))
        CALL(evt_party_set_dir, 0, 90, -1)
    END_INLINE_EVENT
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_7_000"), 0, STRING("クリハカセ"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 30)
    WAIT_MS(800)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_FRANKURI1"))
    CALL(evt_cam3d_evt_set, -175, 55, 409, 83, 30, -123, 400, 11)
    WAIT_MS(900)
    CALL(evt_msg_print, 0, STRING("mac_7_001"), 0, STRING("クリハカセ"))
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -105, 125, FLOAT(120.0f))
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -71, 139, FLOAT(120.0f))
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_7_002"), 0, STRING("クリハカセ"))
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_7_003"), 0, STRING("クリハカセ"))
    CALL(evt_party_move_pos2, 0, -100, 145, FLOAT(120.0f))
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("mac_7_004"))
    CALL(evt_msg_print, 0, STRING("mac_7_005"), 0, STRING("クリハカセ"))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("mac_7_006"))
    WAIT_MS(250)
    CALL(evt_msg_print, 0, STRING("mac_7_007"), 0, STRING("クリハカセ"))
    WAIT_MS(200)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_set_ry_lr, STRING("クリハカセ"), 1)
    CALL(evt_npc_move_position, STRING("クリハカセ"), 160, 64, 0, FLOAT(120.0f), 0)
    CALL(evt_npc_set_position, STRING("クリハカセ"), 0, -1000, 0)
    CALL(evt_party_run, 0)
    SET_VALUE(GSW(0), 378)
    CALL(evt_snd_bgmon_f, 768, STRING("BGM_STG0_TIK1"), 2000)
    RETURN
EVT_END()

EVT_BEGIN(hashira_bomb_sub)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mapobj_get_position, STRING("S_ana_before"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_WALL_BREAK1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_hitobj_onoff, STRING("a_bom_mae"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("a_bom_go"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("ro_ru"), 1, 0)
    SET_VALUE(GSWF(1330), 1)
    CALL(evt_img_entry, STRING("capture_img"))
    CALL(evt_img_set_paper, STRING("capture_img"), STRING("OFF_d_bom_ver2"))
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 1, STRING("bom_mae"), STRING("offscreen"))
    CALL(evt_offscreen_get_boundingbox2, STRING("offscreen"), LW(10), LW(11), LW(12), LW(13))
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(LW(12), 0)
        IF_INT_EQUAL(LW(13), 0)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_img_alloc_capture, STRING("capture_img"), 0, STRING("offscreen"), 1, LW(10), LW(11), LW(12), LW(13))
        CALL(evt_img_clear_virtual_point, STRING("capture_img"))
        CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_1"))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("bom_mae"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("bom_go"), 1)
        CALL(evt_img_wait_animend, STRING("capture_img"))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("bom_mae"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("bom_go"), 1)
    END_IF
    CALL(evt_mapobj_clear_offscreen, 1, STRING("bom_mae"))
    CALL(evt_img_free_capture, STRING("capture_img"), 0)
    CALL(evt_img_free_capture, STRING("capture_img"), 1)
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_release, STRING("capture_img"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    RETURN
EVT_END()

EVT_BEGIN(hashira_bomb)
    IF_INT_EQUAL(GSWF(1330), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("bom_go"), 1)
        CALL(evt_hitobj_onoff, STRING("a_bom_go"), 1, 0)
        CALL(evt_paper_entry, STRING("OFF_d_bom_ver2"))
        CALL(evt_run_case_evt, 15, 1, STRING("a_bom_mae"), 0, PTR(hashira_bomb_sub), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("bom_mae"), 1)
        CALL(evt_hitobj_onoff, STRING("a_bom_mae"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("ro_ru"), 1, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(epilogue_npc_entry)
    CALL(evt_npc_entry, STRING("クリスチーヌ"), STRING("c_pkr"))
    CALL(evt_npc_set_tribe, STRING("クリスチーヌ"), STRING("クリスチーヌ"))
    CALL(evt_npc_set_position, STRING("クリスチーヌ"), -540, 20, -25)
    CALL(evt_npc_set_ry, STRING("クリスチーヌ"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("クリスチーヌ"), 1073742880)
    RETURN
EVT_END()

static EVT_BEGIN(epilogue_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN1"))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_cam3d_evt_set, -350, 160, 582, -350, 65, 40, 0, 11)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_4_naka"), 1)
    CALL(evt_seq_wait, 2)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_npc_move_position, STRING("クリスチーヌ"), -345, -25, 0, 60, 0)
    CALL(evt_npc_move_position, STRING("クリスチーヌ"), -345, -5, 0, 60, 0)
    SET_VALUE(LW(0), PTR(door_data_04))
    SPAWN_EVENT(PTR(door_open_se))
    CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SPAWN_EVENT(PTR(evt_door_04_00))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_move_position, STRING("クリスチーヌ"), -345, -70, 0, 60, 0)
    SET_VALUE(LW(0), PTR(door_data_04))
    SPAWN_EVENT(PTR(door_close_se))
    CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SPAWN_EVENT(PTR(evt_door_04_00))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 900, 9, 900)
    CALL(evt_bero_mapchange, STRING("moo_04"), STRING(""))
    RETURN
EVT_END()

static EVT_BEGIN(mobj_box01)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box01"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item01"), 246, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item01"), 258)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box01"))
    CALL(evt_item_get_item, STRING("item01"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(tik_00_init_evt)
    IF_INT_NOT_EQUAL(GSW(0), 402)
        IF_INT_NOT_EQUAL(GSW(0), 377)
            CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
            CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK2"))
            ELSE
            CALL(evt_snd_bgmoff, 512)
            CALL(evt_snd_envoff, 512)
        END_IF
    END_IF
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(johoya_data_alloc, STRING("jketi_code"))
    SET_VALUE(GSWF(6), 0)
    SET_VALUE(GSWF(237), 0)
    CALL(uranaisi_table_clear)
    SET_VALUE(LW(0), PTR(door_data_01))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(door_data_02))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(door_data_03))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(door_data_04))
    CALL_CHILD(PTR(evt_door_04_entry))
    SPAWN_EVENT(PTR(tensou_init_event))
    CALL(evt_run_case_evt, 9, 1, STRING("a_sui"), 0, PTR(tensou_sw_event), 0)
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    SET_VALUE(LW(0), STRING("ugo_yuka"))
    SET_VALUE(LW(1), STRING("a_ugo_yuka"))
    SET_VALUE(LW(2), 75)
    SET_VALUE(LW(3), 0)
    SET_VALUE(LW(4), 2000)
    SET_VALUE(LW(5), 500)
    SET_VALUE(LW(6), 1)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(12), 0)
    SPAWN_EVENT(PTR(moving_floor))
    SPAWN_EVENT(PTR(hashira_bomb))
    CALL(evt_mobj_powerupblk, STRING("pblk1"), 525, 209, -175, 0, GSWF(5530), 0)
    CALL(evt_mobj_itembox, STRING("mobj_box01"), -375, -60, 320, 0, 0, PTR(mobj_box01), GSWF(1354))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -220, 95, -360, STRING("ie_3_naka"), 125, GSWF(5588))
    CALL(evt_item_entry, STRING("item_00"), 125, 460, -40, 215, 16, GSWF(5585), 0)
    CALL(evt_item_entry, STRING("item_01"), 125, 530, 20, -220, 16, GSWF(5586), 0)
    CALL(evt_item_entry, STRING("item_02"), 125, -530, 20, -220, 16, GSWF(5587), 0)
    IF_INT_EQUAL(GSW(0), 402)
        CALL(evt_mario_kill_party, 0)
        CALL_CHILD(PTR(epilogue_npc_entry))
        SPAWN_EVENT(PTR(epilogue_evt))
    END_IF
    SPAWN_EVENT(PTR(evt_sub_mail_event))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_1"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_2"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_3"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_4"), 2)
    RETURN
EVT_END()
