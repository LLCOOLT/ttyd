#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "dolphin/mtx.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "driver/mobjdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_door.h"
#include "evt/evt_mario.h"
#include "bom.h"

static USER_FUNC(anim_tevcallback);
static USER_FUNC(anim_tevcallback_mobj);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bg_set_color);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_kinopio_setup);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_replace_mapobj);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_get_dispdir);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_set_width);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_move_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_breed_pose);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_set_pose);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_get_haveitemcnt);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_shop_setup);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_coin);
USER_FUNC(evt_sub_get_dir);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_save_playtime);
USER_FUNC(evt_win_item_select);
static USER_FUNC(yami_view);
extern s32 envSetYami[];

__declspec(section ".data") u64 fd_bom_02_negone_one_374;
__declspec(section ".data") s32 fd_bom_02_neg_one_382[1];
__declspec(section ".data") s32 fd_bom_02___local_PI_383[1];
__declspec(section ".data") s32 fd_bom_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_bom_02_one_negone_373;
__declspec(section ".data") s32 fd_bom_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_bom_02_one_381[1];
__declspec(section ".data") u64 fd_bom_02_negone_one_360;
__declspec(section ".data") s32 fd_bom_02_neg_one_365[1];
__declspec(section ".data") s32 fd_bom_02___local_PI_366[1];
__declspec(section ".data") s32 fd_bom_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_bom_02_one_negone_359;
__declspec(section ".data") s32 fd_bom_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_bom_02_one_364[1];
__declspec(section ".data") s32 evt_ie1_door_1[12];
__declspec(section ".data") s32 evt_ie1_wall[12];
__declspec(section ".data") s32 ie1_npc[2];
__declspec(section ".data") s32 evt_ie1_door_open[12];
s32 evt_ie1_door_close[14];
s32 ie1_door[18];
__declspec(section ".data") s32 evt_ie2_door_1[12];
__declspec(section ".data") s32 evt_ie2_wall[12];
__declspec(section ".data") s32 ie2_npc[2];
__declspec(section ".data") s32 evt_ie2_door_open[12];
s32 evt_ie2_door_close[14];
s32 ie2_door[18];
__declspec(section ".data") s32 evt_ie3_door_1[12];
__declspec(section ".data") s32 evt_ie3_door_2[12];
__declspec(section ".data") s32 evt_ie3_wall[12];
__declspec(section ".data") s32 ie3_npc[3];
__declspec(section ".data") s32 evt_ie3_door_open[12];
s32 evt_ie3_door_close[14];
__declspec(section ".data") s32 ie3_item[2];
s32 ie3_door[18];
static s32 bero_entry_data[30];
static s32 evt_kime_pose[52];
static s32 evt_taihou[190];
s32 urotuku_white[190];
static s32 init_soncho[13];
static s32 talk_soncho[421];
static __declspec(section ".data") s32 init_murabito_e[2];
#ifdef VERSION_G8ME01
static s32 talk_murabito_e[281];
#else
static s32 talk_murabito_e[253];
#endif
static __declspec(section ".data") s32 init_murabito_f[2];
static s32 talk_murabito_f[44];
static s32 init_murabito_g[17];
static s32 talk_murabito_g[81];
static __declspec(section ".data") s32 init_murabito_h[2];
__declspec(section ".data") s32 iri_26_item_tbl[2];
static s32 talk_murabito_h[151];
static __declspec(section ".data") s32 init_murabito_i[2];
static s32 talk_murabito_i[44];
__declspec(section ".data") s32 init_tenin[8];
__declspec(section ".data") s32 talk_tenin[2];
static s32 init_white[83];
#ifdef VERSION_G8ME01
s32 mario_jump[203];
#else
s32 mario_jump[197];
#endif
#ifndef VERSION_G8ME01
__declspec(section ".data") s32 mario_jump_tail[6];
#endif
__declspec(section ".data") s32 iri_25_item_tbl[2];
static s32 talk_white[117];
s32 iri_25_white_bed[363];
s32 evt_white_bed[505];
static s32 kiza_talk[28];
static s32 kiza_entry[30];
static s32 npcEnt[207];
static __declspec(section ".data") s32 obj_list[12];
static __declspec(section ".data") s32 goods_list[12];
static s32 trade_list[26];
static s32 shopper_data[38];
static s32 sekai_yami_evt[459];
static s32 minnnanokoe_evt[183];
static s32 kino_dt[38];
s32 bom_02_init_evt[312];

__declspec(section ".data") u64 fd_bom_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_bom_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_02_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(evt_ie1_door_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie1_door"), FLOAT(0.0f), LW(0), FLOAT(0.0f))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_ie1_wall)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.6660156f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie1_kai"), FLOAT(0.0f), FLOAT(0.0f), LW(0))
    RETURN
EVT_END()

__declspec(section ".data") s32 ie1_npc[] = {
    (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", 0,
};

__declspec(section ".data") EVT_BEGIN(evt_ie1_door_open)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

EVT_BEGIN(evt_ie1_door_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

s32 ie1_door[] = {
    0, 3, 1, (s32)"S_ie1_door", (s32)"A_ie1_door1", (s32)"A_ie1_door1_u", (s32)"S_ie1_soto", 0,
    (s32)"S_ie1_naka", 0, (s32)evt_ie1_door_1, 0, (s32)evt_ie1_wall, (s32)ie1_npc, 0, 0,
    (s32)evt_ie1_door_open, (s32)evt_ie1_door_close,
};

__declspec(section ".data") EVT_BEGIN(evt_ie2_door_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie2_door"), FLOAT(0.0f), LW(0), FLOAT(0.0f))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_ie2_wall)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie2_kai"), FLOAT(0.0f), FLOAT(0.0f), LW(0))
    RETURN
EVT_END()

__declspec(section ".data") s32 ie2_npc[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", 0,
};

__declspec(section ".data") EVT_BEGIN(evt_ie2_door_open)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

EVT_BEGIN(evt_ie2_door_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

s32 ie2_door[] = {
    0, 3, 1, (s32)"S_ie2_door", (s32)"A__ie2_door2", (s32)"A__ie2_door2_u", (s32)"S_ie2_soto", 0,
    (s32)"S_ie2_naka", 0, (s32)evt_ie2_door_1, 0, (s32)evt_ie2_wall, (s32)ie2_npc, 0, 0,
    (s32)evt_ie2_door_open, (s32)evt_ie2_door_close,
};

__declspec(section ".data") EVT_BEGIN(evt_ie3_door_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie3_door"), FLOAT(0.0f), LW(0), FLOAT(0.0f))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_ie3_door_2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie3_door"), FLOAT(0.0f), FLOAT(0.0f), LW(0))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_ie3_wall)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie3_kai"), FLOAT(0.0f), FLOAT(0.0f), LW(0))
    RETURN
EVT_END()

__declspec(section ".data") s32 ie3_npc[] = {
    (s32)/*"ホワイト"*/"\x83\x7A\x83\x8F\x83\x43\x83\x67", (s32)/*"ボムヘイG"*/"\x83\x7B\x83\x80\x83\x77\x83\x43\x47", 0,
};

__declspec(section ".data") EVT_BEGIN(evt_ie3_door_open)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

EVT_BEGIN(evt_ie3_door_close)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

__declspec(section ".data") s32 ie3_item[] = {
    (s32)"item_00", 0,
};

s32 ie3_door[] = {
    0, 3, 1, (s32)"S_ie3_door", (s32)"A_ie3_door3_u", (s32)"A_ie3_door3", (s32)"S_ie3_soto", 0,
    (s32)"S_ie3_naka", 0, (s32)evt_ie3_door_1, (s32)evt_ie3_door_2, (s32)evt_ie3_wall, (s32)ie3_npc, 0, (s32)ie3_item,
    (s32)evt_ie3_door_open, (s32)evt_ie3_door_close,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"bom_01", (s32)"e_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_kime_pose)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING("PKR_Y_1"))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING("PNK_Y_1"))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING("Y_1"))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING("PYS_Y_1"))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING("PWD_Y_1"))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING("PTR_Y_1"))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING("PCH_Y_1"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(evt_taihou)
    CALL(evt_cam3d_evt_set, 140, 100, 593, 140, 40, 248, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 180, 225, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 160, 250, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(500)
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg7_bom_60"), 0, STRING("me"))
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(200)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL_CHILD(PTR(evt_kime_pose))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_party_set_breed_pose, 0, 1)
    CALL(evt_msg_print_party, STRING("stg7_bom_60_2"))
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg7_bom_61"), 0, STRING("me"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 50, 152, 800, 50, 57, 260, 3000, 11)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 131088)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_move_position, STRING("me"), -45, 270, 0, FLOAT(60.0f), 1)
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir_npc, STRING("me"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir_npc, 0, STRING("me"))
    END_INLINE_EVENT
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg7_bom_62"), 0, STRING("me"))
    WAIT_MS(300)
    CALL(evt_npc_move_position, STRING("me"), -140, 200, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 131088)
    SET_VALUE(GSW(0), 356)
    CALL(evt_cam3d_evt_off, 500, 11)
    RETURN
EVT_END()

EVT_BEGIN(urotuku_white)
    IF_INT_EQUAL(GSWF(3888), 1)
        CALL(evt_msg_print, 0, STRING("stg7_bom_41_01"), 0, STRING("me"))
        RETURN
    END_IF
    CALL(evt_cam3d_evt_set, 120, 97, 700, 120, 65, 251, 800, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg7_bom_39"), 0, STRING("me"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    CALL(evt_npc_set_position, STRING("ホワイト"), 230, 30, -125)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(evt_ie3_door_1))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(evt_ie3_door_1))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 132624)
    CALL(evt_npc_status_onoff, 1, STRING("ホワイト"), 2)
    CALL(evt_npc_move_position, STRING("ホワイト"), 200, -85, 0, FLOAT(60.0f), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg7_bom_41"), 0, STRING("ホワイト"))
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LABEL(3)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(evt_ie3_door_1))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(3)
        END_IF
        CALL(evt_npc_move_position, STRING("ホワイト"), 230, -125, 0, FLOAT(80.0f), 1)
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(4)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(evt_ie3_door_1))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(4)
        END_IF
        CALL(evt_npc_set_position, STRING("ホワイト"), 380, 45, -150)
        CALL(evt_npc_set_ry, STRING("ホワイト"), 270)
        CALL(evt_npc_flag_onoff, 0, STRING("ホワイト"), 1536)
        CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("N_1"))
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    CALL(evt_msg_print_add, 0, STRING("stg7_bom_40"))
    CALL(evt_msg_print_add, 0, STRING("stg7_bom_40_02"))
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSWF(3888), 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_soncho)
    SWITCH(GSW(0))
        CASE_LESS(356)
        CALL(evt_npc_set_position, STRING("me"), 120, 0, 265)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_soncho)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 32)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("stg7_bom_20_00"), 0, STRING("me"))
        CASE_LESS(354)
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 3)
            IF_INT_EQUAL(GSWF(3886), 0)
                SET_VALUE(GSWF(3886), 1)
                CALL(evt_msg_print, 0, STRING("stg7_bom_20"), 0, STRING("me"))
                WAIT_MS(300)
                CALL(evt_mario_set_pose, STRING("M_I_2"))
                WAIT_MS(800)
                CALL(evt_mario_set_pose, STRING("M_S_1"))
                CALL(evt_msg_print, 0, STRING("stg7_bom_21"), 0, STRING("me"))
                ELSE
                CALL(evt_msg_print, 0, STRING("stg7_bom_21_01"), 0, STRING("me"))
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32)
                RETURN
            END_IF
            WAIT_MS(300)
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_party_move_pos2, 0, 80, 300, FLOAT(60.0f))
            CALL(evt_party_set_dir_npc, 0, STRING("me"))
            CALL(evt_msg_print_party, STRING("stg7_bom_22"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_23"), 0, STRING("me"))
            CALL(evt_party_run, 0)
            ELSE
            BEGIN_INLINE_EVENT
                CALL(evt_party_move_pos, 0, 50, 280, 500)
                CALL(evt_party_set_dir_npc, 0, STRING("me"))
            END_INLINE_EVENT
            CALL(evt_mario_mov_pos, 70, 260, 500)
            CALL(evt_mario_set_dir, 90, 200, 0)
            CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
            IF_INT_EQUAL(GSWF(3886), 0)
                SET_VALUE(GSWF(3886), 1)
                CALL(evt_msg_print, 0, STRING("stg7_bom_20"), 0, STRING("me"))
                WAIT_MS(300)
                CALL(evt_mario_set_pose, STRING("M_I_2"))
                WAIT_MS(800)
                CALL(evt_mario_set_pose, STRING("M_S_1"))
                CALL(evt_msg_print, 0, STRING("stg7_bom_21"), 0, STRING("me"))
                ELSE
                CALL(evt_msg_print, 0, STRING("stg7_bom_21_01"), 0, STRING("me"))
            END_IF
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_party_move_pos2, 0, 80, 300, FLOAT(60.0f))
            CALL(evt_party_set_dir_npc, 0, STRING("me"))
            CALL(evt_msg_print, 0, STRING("stg7_bom_24"), 0, STRING("party"))
            WAIT_MS(300)
            CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 60)
            WAIT_MS(1000)
            CALL(evt_cam3d_evt_set, 90, 105, 611, 90, 45, 266, 500, 11)
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("stg7_bom_25"), 0, STRING("party"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_26"), 0, STRING("me"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_27"), 0, STRING("party"))
            WAIT_MS(300)
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            CALL(evt_npc_jump_position_nohit, STRING("me"), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
            CALL(evt_msg_print, 0, STRING("stg7_bom_28"), 0, STRING("me"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_29"), 0, STRING("party"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_30"), 0, STRING("me"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_31"), 0, STRING("party"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_32"), 0, STRING("me"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg7_bom_32_02"), 0, STRING("party"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_2"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_2"))
            WAIT_MS(500)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_msg_print, 0, STRING("stg7_bom_33"), 0, STRING("me"))
            SET_VALUE(GSW(0), 354)
            CALL(evt_cam3d_evt_off, 500, 11)
            CALL(evt_party_run, 0)
        END_IF
        CASE_LESS(355)
        SET_VALUE(LW(0), 0)
        IF_INT_EQUAL(GSWF(3874), 1)
            ADD(LW(0), 1)
        END_IF
        IF_INT_EQUAL(GSWF(3876), 1)
            ADD(LW(0), 1)
        END_IF
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 0, STRING("stg7_bom_34"), 0, STRING("me"))
            CALL(evt_msg_select, 0, STRING("stg7_bom_34_yn"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("stg7_bom_38"))
                ELSE
                CALL(evt_msg_print_add, 0, STRING("stg7_bom_37"))
            END_IF
            CASE_EQUAL(1)
            IF_INT_EQUAL(GSWF(3874), 0)
                CALL(evt_msg_print, 0, STRING("stg7_bom_38_01"), 0, STRING("me"))
            END_IF
            IF_INT_EQUAL(GSWF(3876), 0)
                IF_INT_EQUAL(GSWF(3880), 0)
                    CALL(evt_msg_print, 0, STRING("stg7_bom_38_02"), 0, STRING("me"))
                    ELSE
                    CALL_CHILD(PTR(urotuku_white))
                END_IF
            END_IF
        END_SWITCH
        CASE_LESS(356)
        CALL_CHILD(PTR(evt_taihou))
    END_SWITCH
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 32)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(init_murabito_e)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_e)
    IF_INT_EQUAL(GSW(1420), 30)
#ifdef VERSION_G8ME01
        IF_INT_EQUAL(GSWF(5406), 0)
#endif
        IF_INT_EQUAL(GSWF(5405), 0)
            CALL(evt_msg_print, 0, STRING("irai_30_001"), 0, 0)
            SET_VALUE(GSWF(5405), 1)
            ELSE
            CALL(evt_msg_print, 0, STRING("irai_30_002"), 0, 0)
#ifndef VERSION_G8ME01
            IF_INT_EQUAL(GSWF(5406), 0)
#endif
                CALL(evt_msg_print_add, 0, STRING("irai_30_003"))
#ifdef VERSION_G8ME01
            END_IF
#endif
                ELSE
#ifdef VERSION_G8ME01
            SET_VALUE(LF(0), 0)
            IF_INT_EQUAL(GSWF(5405), 0)
                SET_VALUE(LF(0), 1)
                ELSE
                CALL(evt_msg_print, 0, STRING("irai_30_002"), 0, 0)
#endif
                CALL(evt_msg_continue)
#ifdef VERSION_G8ME01
            END_IF
#endif
                CALL(evt_npc_flag_onoff, 1, STRING("me"), 32)
                SET_VALUE(GF(0), 1)
                BEGIN_INLINE_EVENT
                    CALL(evt_party_move_pos2, 0, 175, 45, 60)
                    CALL(evt_party_set_dir_npc, 0, STRING("me"))
                    WAIT_MS(300)
                    SET_VALUE(GF(0), 0)
                END_INLINE_EVENT
                CALL(evt_mario_mov_pos2, 145, 45, 60)
                CALL(evt_mario_set_dir_npc, STRING("me"))
                WAIT_WHILE(GF(0))
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32)
                CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
                WAIT_FRAMES(1)
                CALL(evt_npc_wait_pera, STRING("me"))
                CALL(evt_mario_set_pose, STRING("M_I_2"))
                WAIT_MS(1000)
                CALL(evt_mario_set_pose, STRING("M_S_1"))
#ifdef VERSION_G8ME01
            IF_INT_EQUAL(LF(0), 0)
#endif
                CALL(evt_msg_print, 0, STRING("irai_30_004"), 0, 0)
#ifdef VERSION_G8ME01
                ELSE
                CALL(evt_msg_print, 0, STRING("irai_30_003_1"), 0, 0)
            END_IF
#endif
                CALL(evt_pouch_get_haveitemcnt, LW(0))
                CALL(evt_pouch_check_item, 1, LW(1))
                IF_INT_EQUAL(LW(1), 0)
                    SET_VALUE(LW(1), 10)
                    ELSE
                    SET_VALUE(LW(1), 20)
                END_IF
                IF_INT_LESS(LW(0), LW(1))
                    CALL(evt_msg_continue)
                    CALL(evt_item_entry, STRING("sr"), 201, 0, -1000, 0, 17, -1, 0)
                    CALL(evt_item_get_item, STRING("sr"))
                    CALL(evt_item_get_item_end_wait, STRING("sr"))
                    SET_VALUE(GSWF(3890), 1)
                    ELSE
                    CALL(evt_msg_print_add, 0, STRING("irai_30_005_1"))
                    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
                    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
                    CALL(evt_npc_move_position, STRING("me"), 50, 35, 0, 60, 0)
                    CALL(evt_item_entry, STRING("iri_30"), 201, 50, 0, 35, 16, GSWF(3890), 0)
                    WAIT_MS(600)
                    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, 60, 0)
                    CALL(evt_npc_status_onoff, 0, STRING("me"), 2)
                END_IF
                CALL(evt_msg_print, 0, STRING("irai_30_006"), 0, 0)
                SET_VALUE(GSW(1420), 0)
                SET_VALUE(GSWF(5404), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
            END_IF
#ifndef VERSION_G8ME01
        END_IF
#endif
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("stg7_bom_10_00"), 0, STRING("me"))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING("stg7_bom_10"), 0, STRING("me"))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING("stg7_bom_10_1"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg7_bom_11"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_bom_11_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(init_murabito_f)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_f)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("stg7_bom_12_00"), 0, STRING("me"))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING("stg7_bom_12"), 0, STRING("me"))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING("stg7_bom_12_1"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg7_bom_13"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_bom_13_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_murabito_g)
    IF_INT_EQUAL(GSW(1420), 25)
        CALL(evt_npc_set_position, STRING("me"), 270, 30, -180)
        CALL(evt_npc_set_ry, STRING("me"), 90)
        RETURN
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_g)
    IF_INT_EQUAL(GSW(1420), 25)
        IF_INT_EQUAL(GSWF(5405), 1)
            IF_INT_EQUAL(GSWF(5407), 0)
                CALL(evt_msg_print, 0, STRING("irai_25_00"), 0, 0)
                SET_VALUE(GSWF(5406), 1)
                RETURN
            END_IF
        END_IF
        IF_INT_EQUAL(GSWF(5409), 1)
            IF_INT_EQUAL(GSWF(5410), 0)
                CALL(evt_msg_print, 0, STRING("irai_25_01"), 0, 0)
                RETURN
            END_IF
        END_IF
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("stg7_bom_14_00"), 0, STRING("me"))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING("stg7_bom_14"), 0, STRING("me"))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING("stg7_bom_14_1"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg7_bom_15"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_bom_15_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(init_murabito_h)
    RETURN
EVT_END()

__declspec(section ".data") s32 iri_26_item_tbl[] = {
    229, -1,
};

static EVT_BEGIN(talk_murabito_h)
    IF_INT_EQUAL(GSW(1420), 26)
        CALL(evt_pouch_check_item, 229, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("irai_26_01"), 0, 0)
            CALL(evt_msg_select, 0, STRING("irai_26_01_s"))
            CALL(evt_msg_print_add, 0, STRING("irai_26_02"))
            CALL(evt_msg_select, 0, STRING("irai_26_02_s"))
            CALL(evt_msg_print_add, 0, STRING("irai_26_03"))
            CALL(evt_msg_select, 0, STRING("irai_26_03_s"))
            CALL(evt_msg_print_add, 0, STRING("irai_26_04"))
            CALL(evt_win_item_select, 0, PTR(iri_26_item_tbl), LW(0), 0)
            IF_INT_NOT_EQUAL(LW(0), -1)
                CALL(evt_pouch_remove_item, 229, LW(0))
                CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
                LOOP(3)
                    CALL(evt_npc_jump_position_nohit, STRING("me"), LW(0), LW(1), LW(2), 150, 5)
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(evt_msg_print, 0, STRING("irai_26_05"), 0, 0)
                CALL(evt_sub_get_coin, 20)
                CALL(evt_sub_save_playtime, GSW(1461))
                SET_VALUE(GSW(1420), 0)
                SET_VALUE(GSWF(5400), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
            END_IF
            ELSE
            CALL(evt_msg_print, 0, STRING("irai_26_00"), 0, 0)
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("stg7_bom_16_00"), 0, STRING("me"))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING("stg7_bom_16"), 0, STRING("me"))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING("stg7_bom_16_1"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg7_bom_17"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_bom_17_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(init_murabito_i)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_i)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("stg7_bom_18_00"), 0, STRING("me"))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING("stg7_bom_18"), 0, STRING("me"))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING("stg7_bom_18_1"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg7_bom_19"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_bom_19_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_tenin)
    CALL(evt_npc_set_position, STRING("me"), 125, 30, -450)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(talk_tenin)
    RETURN
EVT_END()

static EVT_BEGIN(init_white)
    IF_INT_EQUAL(GSW(1420), 25)
        IF_INT_EQUAL(GSWF(5409), 1)
            IF_INT_EQUAL(GSWF(5411), 0)
                CALL(evt_npc_set_position, STRING("ホワイト"), 380, 45, -150)
                CALL(evt_npc_set_ry, STRING("ホワイト"), 270)
                IF_INT_EQUAL(GSWF(5410), 1)
                    CALL(evt_npc_flag_onoff, 0, STRING("me"), 16777216)
                    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1536)
                    ELSE
                    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("N_1"))
                    CALL(evt_npc_set_width, STRING("ホワイト"), 10)
                    CALL(evt_npc_change_interrupt, STRING("ホワイト"), 6, 0)
                END_IF
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(3880), 1)
        IF_INT_EQUAL(GSWF(3876), 0)
            CALL(evt_npc_set_width, STRING("ホワイト"), 10)
            CALL(evt_npc_set_position, STRING("ホワイト"), 380, 45, -150)
            CALL(evt_npc_set_ry, STRING("ホワイト"), 270)
            CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("N_1"))
            CALL(evt_npc_change_interrupt, STRING("ホワイト"), 6, 0)
        END_IF
    END_IF
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
EVT_BEGIN(mario_jump)
    CALL(evt_mario_cam_keep_on)
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 32)
    CALL(evt_npc_get_position, STRING("ホワイト"), LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FLD_JUMP1"), LW(10), LW(11), LW(12), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 500, 2, -1000)
    BEGIN_INLINE_EVENT
        SUBTRACT(LW(0), 40)
        SUBTRACT(LW(2), 40)
        CALL(evt_eff, 0, STRING("nice"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(evt_eff, 0, STRING("small_star"), 3, LW(0), LW(1), LW(2), 0, -1, 0, 3, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WHITE_DAMAGED1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WHITE_NICE1"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.009765625f), 100)
    END_INLINE_EVENT
    ADD(LW(2), -10)
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FLD_JUMP4"), LW(10), LW(11), LW(12), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 500, 2, -1000)
    BEGIN_INLINE_EVENT
        SUBTRACT(LW(0), 40)
        SUBTRACT(LW(2), 40)
        CALL(evt_eff, 0, STRING("nice"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(evt_eff, 0, STRING("small_star"), 3, LW(0), LW(1), LW(2), 0, -1, 0, 3, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WHITE_DAMAGED1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WHITE_GOOD1"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.009765625f), 100)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FLD_JUMP2"), LW(10), LW(11), LW(12), 0)
    CALL(evt_mario_jump_pos, 335, 30, -130, 500, 2, -1000)
    CALL(evt_npc_flag_onoff, 0, STRING("ホワイト"), 32)
    CALL(evt_mario_cam_keep_off)
    RETURN
EVT_END()
#else
s32 mario_jump[] = {
    65627, (s32)evt_mario_cam_keep_on, 327771, (s32)evt_mario_get_pos, 0, -29999990, -29999989, -29999988,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"ホワイト"*/"\x83\x7A\x83\x8F\x83\x43\x83\x67", 32, 327771, (s32)evt_npc_get_position, (s32)/*"ホワイト"*/"\x83\x7A\x83\x8F\x83\x43\x83\x67",
    -30000000, -29999999, -29999998, 131125, -29999999, 20, 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_VOICE_MARIO_FLD_JUMP1", -29999990, -29999989, -29999988, 0, 458843, (s32)evt_mario_jump_pos, -30000000,
    -29999999, -29999998, 500, 2, -1000, 107, 131126, -30000000,
    20, 131126, -29999998, 20, 983131, (s32)evt_eff, 0, (s32)"nice",
    0, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 0, 0, 0, 109, 983131, (s32)evt_eff, 0,
    (s32)"small_star", 3, -30000000, -29999999, -29999998, 0, -1, 0,
    3, 0, 0, 0, 0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG7_WHITE_DAMAGED1",
    -30000000, -29999999, -29999998, 0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG7_WHITE_NICE1", -30000000,
    -29999999, -29999998, 0, 107, 327771, (s32)evt_cam_shake, 4, -230000000,
    -229999990, 100, 109, 131125, -29999998, -10, 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_VOICE_MARIO_FLD_JUMP4", -29999990, -29999989, -29999988, 0, 458843, (s32)evt_mario_jump_pos, -30000000,
    -29999999, -29999998, 500, 2, -1000, 107, 131126, -30000000,
    20, 131126, -29999998, 20, 983131, (s32)evt_eff, 0, (s32)"nice",
    1, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 0, 0, 0, 109, 983131, (s32)evt_eff, 0,
    (s32)"small_star", 3, -30000000, -29999999, -29999998, 0, -1, 0,
    3, 0, 0, 0, 0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG7_WHITE_DAMAGED1",
    -30000000, -29999999, -29999998, 0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG7_WHITE_GOOD1", -30000000,
    -29999999, -29999998, 0, 107, 327771, (s32)evt_cam_shake, 4, -230000000,
    -229999990, 100, 109, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_FLD_JUMP2", -29999990, -29999989,
    -29999988, 0, 458843, (s32)evt_mario_jump_pos, 335, 30, -130, 500,
    2, -1000, 262235, (s32)evt_npc_flag_onoff, 0,
};
#endif

#ifndef VERSION_G8ME01  // US: this tail is part of mario_jump (US script above)
__declspec(section ".data") s32 mario_jump_tail[] = {
    (s32)/*"ホワイト"*/"\x83\x7A\x83\x8F\x83\x43\x83\x67", 32, 65627, (s32)evt_mario_cam_keep_off, 2, 1,
};
#endif

__declspec(section ".data") s32 iri_25_item_tbl[] = {
    109, -1,
};

static EVT_BEGIN(talk_white)
    IF_INT_EQUAL(GSW(1420), 25)
        IF_INT_EQUAL(GSWF(5409), 1)
            IF_INT_EQUAL(GSWF(5411), 0)
                SET_VALUE(LF(0), 0)
                IF_INT_EQUAL(GSWF(5410), 1)
                    SET_VALUE(LF(0), 1)
                END_IF
                IF_INT_EQUAL(LF(0), 1)
                    CALL(evt_msg_print, 0, STRING("irai_25_19"), 0, STRING("ホワイト"))
                END_IF
                CALL(evt_win_item_select, 0, PTR(iri_25_item_tbl), LW(0), 0)
                IF_INT_NOT_EQUAL(LW(0), 109)
                    RETURN
                END_IF
                CALL(evt_msg_print, 0, STRING("irai_25_18"), 0, STRING("ホワイト"))
                CALL(evt_pouch_remove_item, 109, LW(0))
                SET_VALUE(GSWF(5411), 1)
                BEGIN_INLINE_EVENT
                    WAIT_MS(1000)
                    CALL(evt_mario_set_dir, 270, 300, 0)
                END_INLINE_EVENT
                BEGIN_INLINE_EVENT
                    WAIT_MS(1000)
                    CALL(evt_party_set_dir_npc, 0, STRING("ホワイト"))
                END_INLINE_EVENT
                CALL(evt_npc_set_width, STRING("ホワイト"), 40)
                CALL(evt_npc_status_onoff, 1, STRING("ホワイト"), 2)
                CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 32)
                CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 131088)
                CALL(evt_npc_jump_position_nohit, STRING("ホワイト"), 245, 30, -110, 500, 80)
                CALL(evt_npc_move_position, STRING("ホワイト"), 170, -55, 0, FLOAT(80.0f), 1)
                CALL(evt_npc_set_position, STRING("ホワイト"), 0, -1000, 0)
                RETURN
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(iri_25_white_bed)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_msg_print, 0, STRING("irai_25_02"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_mario_mov_pos2, 330, -120, 60)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(200)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_03"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_04"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_05"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_06"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_07"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_08"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_09"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_10"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_11"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("irai_25_12"), 0, 0)
    CALL(evt_msg_select, 0, STRING("irai_25_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(100)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    GOTO(101)
    LABEL(100)
    CALL(evt_msg_print_add, 0, STRING("irai_25_13"))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
    LABEL(101)
    CALL(evt_party_run, 0)
    CALL(evt_msg_print, 0, STRING("irai_25_14"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("N_2"))
    WAIT_MS(600)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WHITE_ROUND1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("O_1"))
    WAIT_MS(1900)
    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("O_2"))
    WAIT_MS(1200)
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 1536)
    CALL(evt_msg_print, 0, STRING("irai_25_15"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("irai_25_16"), 0, STRING("ホワイト"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("irai_25_17"), 0, STRING("ホワイト"))
    CALL_CHILD(PTR(talk_white))
    CALL(evt_npc_change_interrupt, STRING("ホワイト"), 6, PTR(talk_white))
    CALL(evt_npc_set_width, STRING("ホワイト"), 30)
    SET_VALUE(GSWF(5410), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(evt_white_bed)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_msg_print, 0, STRING("stg7_bom_43"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_43_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 32)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("ホワイト"), LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dir, LW(3), LW(5), LW(0), LW(2), LW(6))
    IF_INT_GREATER_OR_EQUAL(LW(6), 80)
        IF_INT_LESS_OR_EQUAL(LW(6), 100)
            CALL(evt_mario_mov_pos2, 376, -111, 60)
        END_IF
    END_IF
    CALL(evt_mario_mov_pos2, 330, -120, 60)
    WAIT_FRAMES(1)
    CALL(evt_npc_flag_onoff, 0, STRING("ホワイト"), 32)
    CALL(evt_mario_get_dispdir, LW(0))
    IF_INT_LESS(LW(0), 180)
        CALL(evt_mario_set_dir, 90, 200, 0)
        WAIT_MS(200)
    END_IF
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_44"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_44_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_45"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_45_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_46"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_46_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_47"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_47_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_48"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_48_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_49"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_49_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_50"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_50_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_51"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_51_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_52"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_52_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    CALL(evt_msg_print, 0, STRING("stg7_bom_53"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg7_bom_53_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(evt_msg_continue)
    CALL_CHILD(PTR(mario_jump))
    GOTO(1)
    LABEL(0)
    CALL(evt_msg_print_add, 0, STRING("stg7_bom_54"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
    LABEL(1)
    CALL(evt_msg_print, 0, STRING("stg7_bom_55"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("N_2"))
    WAIT_MS(600)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_WHITE_ROUND1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("O_1"))
    WAIT_MS(1900)
    CALL(evt_npc_set_anim, STRING("ホワイト"), STRING("O_2"))
    WAIT_MS(1200)
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 1536)
    CALL(evt_msg_print, 0, STRING("stg7_bom_56"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("stg7_bom_57"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg7_bom_58"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("stg7_bom_59"), 0, STRING("ホワイト"))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_set_dir, 270, 0, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_party_set_dir_npc, 0, STRING("ホワイト"))
    END_INLINE_EVENT
    CALL(evt_npc_status_onoff, 1, STRING("ホワイト"), 2)
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("ホワイト"), 131088)
    CALL(evt_npc_jump_position_nohit, STRING("ホワイト"), 245, 30, -110, 500, 80)
    CALL(evt_npc_move_position, STRING("ホワイト"), 170, -55, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_set_position, STRING("ホワイト"), 0, -1000, 0)
    SET_VALUE(GSWF(3876), 1)
    SET_VALUE(LW(0), 0)
    IF_INT_EQUAL(GSWF(3874), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(GSWF(3876), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        SET_VALUE(GSW(0), 355)
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(kiza_talk)
    SWITCH(GSW(0))
        CASE_LESS(354)
        CALL(evt_msg_print, 0, STRING("stg7_bom_19_01"), 0, STRING("me"))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING("stg7_bom_19_02"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_bom_19_03"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(kiza_entry)
    CALL(evt_npc_entry, STRING("キザ野郎"), STRING("c_kiza"))
    CALL(evt_npc_set_tribe, STRING("キザ野郎"), STRING("キザ野郎"))
    CALL(evt_npc_set_position, STRING("キザ野郎"), -190, 5, -130)
    CALL(evt_npc_set_ry, STRING("キザ野郎"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("キザ野郎"), 1536)
    CALL(evt_npc_change_interrupt, STRING("キザ野郎"), 6, PTR(kiza_talk))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"村長"*/"\x91\xBA\x92\xB7", 1073743360, 0, (s32)init_soncho, 0, (s32)talk_soncho, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ボムヘイE"*/"\x83\x7B\x83\x80\x83\x77\x83\x43\x45",
    1073743360, 0, (s32)init_murabito_e, 0, (s32)talk_murabito_e, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ボムヘイF"*/"\x83\x7B\x83\x80\x83\x77\x83\x43\x46", 1073743360,
    0, (s32)init_murabito_f, 0, (s32)talk_murabito_f, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"ボムヘイG"*/"\x83\x7B\x83\x80\x83\x77\x83\x43\x47", 1073743360, 0,
    (s32)init_murabito_g, 0, (s32)talk_murabito_g, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ボムヘイH"*/"\x83\x7B\x83\x80\x83\x77\x83\x43\x48", 1073743360, 0, (s32)init_murabito_h,
    0, (s32)talk_murabito_h, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"ボムヘイI"*/"\x83\x7B\x83\x80\x83\x77\x83\x43\x49", 1073743360, 0, (s32)init_murabito_i, 0,
    (s32)talk_murabito_i, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"店員"*/"\x93\x58\x88\xF5", 1073743360, 0, (s32)init_tenin, 0, (s32)talk_tenin,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ホワイト"*/"\x83\x7A\x83\x8F\x83\x43\x83\x67", 1090519040, 0, (s32)init_white, 0, (s32)talk_white, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

static __declspec(section ".data") s32 obj_list[] = {
    (s32)"S_item_01", (s32)"A_item_01", (s32)"S_item_02", (s32)"A_item_02", (s32)"S_item_03", (s32)"A_item_03", (s32)"S_item_04", (s32)"A_item_04",
    (s32)"S_item_05", (s32)"A_item_05", (s32)"S_item_06", (s32)"A_item_06",
};

static __declspec(section ".data") s32 goods_list[] = {
    130, 30, 131, 6, 137, 15, 140, 12,
    155, 20, 149, 15,
};

static s32 trade_list[] = {
    130, 983040, 131, 196608, 137, 458752, 140, 393216,
    155, 655360, 149, 458752, 132, 524288, 173, 917504,
    224, 3932160, 192, 1310720, 220, 983040, 228, 1572864,
    0, 0,
};

static s32 shopper_data[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", 0, 0, (s32)"shop_00", (s32)"shop_01", (s32)"shop_02", (s32)"shop_03", (s32)"shop_04",
    (s32)"shop_05", (s32)"shop_06", (s32)"shop_07", (s32)"shop_08", (s32)"shop_09", (s32)"shop_10", (s32)"shop_11", (s32)"shop_12",
    (s32)"shop_13", (s32)"shop_14", (s32)"shop_15", (s32)"shop_16", (s32)"shop_17", (s32)"shop_18", (s32)"shop_19", (s32)"shop_20",
    (s32)"shop_21", (s32)"shop_22", (s32)"shop_23", (s32)"shop_24", (s32)"shop_25", (s32)"shop_26", (s32)"shop_27", (s32)"shop_28",
    (s32)"shop_29", (s32)"shop_30", (s32)"shop_31", (s32)"shop_32", (s32)"shop_33", (s32)"shop_34",
};

void envSetYamiView(Mtx mtx);

static USER_FUNC(yami_view) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){0.0f, 100.0f, 100.0f + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){0.0f, 0.0f, z});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(sekai_yami_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("村長"), -30, 0, 175)
    CALL(evt_npc_set_ry, STRING("村長"), 90)
    CALL(evt_npc_set_position, STRING("ボムヘイE"), -160, 0, -40)
    CALL(evt_npc_set_position, STRING("ボムヘイF"), -165, 0, 295)
    CALL(evt_npc_set_position, STRING("ボムヘイG"), 117, 0, 251)
    CALL(evt_npc_status_onoff, 1, STRING("ボムヘイE"), 2)
    CALL(evt_npc_status_onoff, 1, STRING("ボムヘイF"), 2)
    CALL(evt_npc_status_onoff, 1, STRING("ボムヘイG"), 2)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_bom02"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_bom02"), 256)
    CALL(anim_tevcallback, STRING("村長"), 1)
    CALL(anim_tevcallback, STRING("ボムヘイE"), 1)
    CALL(anim_tevcallback, STRING("ボムヘイF"), 1)
    CALL(anim_tevcallback, STRING("ボムヘイG"), 1)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(yami_view, -800)
    CALL(evt_cam3d_evt_set, -30, 88, 723, -30, 55, 24, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_sfxon, STRING("SFX_STG8_QUAKE1"), LW(15))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイE"), 10, -40, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイE"), 190, -40, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイE"), 10, -40, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイE"), -160, -40, 0, 120, 0)
        END_LOOP
        WAIT_MS(2000)
        CALL(evt_npc_reverse_ry, STRING("ボムヘイE"))
        WAIT_FRAMES(1)
        CALL(evt_npc_wait_pera, STRING("ボムヘイE"))
        CALL(evt_npc_reverse_ry, STRING("ボムヘイE"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイF"), -62, 295, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイF"), 44, 295, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイF"), 131, 295, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイF"), 44, 295, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイF"), -62, 295, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイF"), -165, 295, 0, 120, 0)
        END_LOOP
        WAIT_MS(2000)
        CALL(evt_npc_reverse_ry, STRING("ボムヘイF"))
        WAIT_FRAMES(1)
        CALL(evt_npc_wait_pera, STRING("ボムヘイF"))
        CALL(evt_npc_reverse_ry, STRING("ボムヘイF"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイG"), 26, 251, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイG"), -83, 251, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイG"), -180, 251, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイG"), -83, 251, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイG"), 26, 251, 0, 120, 0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_move_position, STRING("ボムヘイG"), 117, 251, 0, 120, 0)
        END_LOOP
        WAIT_MS(2000)
        CALL(evt_npc_reverse_ry, STRING("ボムヘイG"))
        WAIT_FRAMES(1)
        CALL(evt_npc_wait_pera, STRING("ボムヘイG"))
        CALL(evt_npc_reverse_ry, STRING("ボムヘイG"))
    END_INLINE_EVENT
    SET_FLOAT_VALUE(LW(0), FLOAT(0.0068359375f))
    LOOP(5)
        CALL(evt_cam_shake, 4, FLOAT(0.0f), LW(0), 1000)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.75f))
    END_LOOP
    SET_VALUE(GF(0), 1)
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_MS(2000)
    CALL(evt_npc_reverse_ry, STRING("村長"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("村長"))
    CALL(evt_npc_reverse_ry, STRING("村長"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("村長"))
    CALL(evt_cam3d_evt_set, -30, 55, 473, -30, 35, 24, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg8_dark_08"), 0, STRING("村長"))
    WAIT_MS(2000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING("las_26"), STRING("sekai_yami2"))
    RETURN
EVT_END()

static EVT_BEGIN(minnnanokoe_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("村長"), 50, 0, 200)
    CALL(evt_npc_set_ry, STRING("村長"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("村長"), 32768)
    CALL(evt_npc_set_position, STRING("ボムヘイE"), -250, 0, 150)
    CALL(evt_npc_set_ry, STRING("ボムヘイE"), 90)
    CALL(evt_npc_status_onoff, 1, STRING("ボムヘイE"), 2)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_bom02"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_bom02"), 256)
    CALL(anim_tevcallback, STRING("村長"), 1)
    CALL(anim_tevcallback, STRING("ボムヘイE"), 1)
    CALL(anim_tevcallback_mobj, STRING("mobj_save"), 1)
    CALL(yami_view, -800)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(evt_cam3d_evt_set, 50, 218, 1025, 50, 70, 188, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 0, STRING("村長"), 32768)
    CALL(evt_cam3d_evt_set, 30, 92, 484, 30, 40, 188, 2000, 11)
    CALL(evt_npc_move_position, STRING("ボムヘイE"), 0, 150, 2000, 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_63"), 0, STRING("ボムヘイE"))
    CALL(evt_npc_set_ry, STRING("村長"), 270)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg8_las_148_64"), 0, STRING("村長"))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("ボムヘイE"), -450, -50, 0, 90, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("村長"), -400, 0, 0, 90, 0)
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING("bom_01"), STRING("minnnanokoe"))
    RETURN
EVT_END()

static s32 kino_dt[] = {
    198, -1009483776, 1112014848, -1018691584, 15, -1014071296, 1110966272, -1017184256,
    -1014464512, 1106247680, -1020198912, -1008828416, 1132527616, 1118830592, -1012236288, 1119354880,
    -1019281408, -1043857408, -1012924416, 1106247680, -1025114112, (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", (s32)"yado_00", (s32)"yado_01",
    (s32)"yado_02", (s32)"yado_03", (s32)"yado_04", (s32)"yado_05", (s32)"yado_06", (s32)"yado_07", (s32)"yado_08", (s32)"yado_09",
    (s32)"yado_10", (s32)"yado_11", (s32)"yado_12", (s32)"yado_13", 0, 0,
};

EVT_BEGIN(bom_02_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(GSW(0), 400)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("sekai_yami2"))
            CALL(evt_snd_bgmoff, 512)
            CALL(evt_snd_envoff, 512)
            SET_VALUE(LF(0), 1)
        END_IF
        IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
            CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG8_VOICE1"))
            CALL(evt_snd_envoff, 512)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_BOM1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG7_BOM3"))
    END_IF
    CALL_CHILD(PTR(evt_bom_snowfall))
    CALL(evt_npc_setup, PTR(npcEnt))
    SWITCH(GSW(0))
        CASE_BETWEEN(352, 357)
        CALL_CHILD(PTR(kiza_entry))
    END_SWITCH
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    CALL(evt_kinopio_setup, PTR(kino_dt))
    SET_VALUE(LW(0), PTR(ie1_door))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(ie2_door))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), PTR(ie3_door))
    CALL_CHILD(PTR(evt_door_entry))
    SET_VALUE(LW(0), STRING("group3713047r"))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING("group3713048r"))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING("group3713049r"))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    CALL(evt_mobj_powerupblk, STRING("pblk01"), 425, 0, -45, 0, GSWF(5565), 0)
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -30, 0, 115, STRING("S_wakuaaa"), 125, GSWF(5661))
    CALL(evt_item_entry, STRING("item_00"), 125, 210, 30, -168, 16, GSWF(5660), 0)
    CALL(evt_item_entry, STRING("item_01"), 164, -220, 5, -115, 16, GSWF(3892), 0)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -300, 65, 10, 0, 0)
    IF_INT_EQUAL(GSW(0), 400)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("sekai_yami2"))
            SPAWN_EVENT(PTR(sekai_yami_evt))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
            SPAWN_EVENT(PTR(minnnanokoe_evt))
        END_IF
    END_IF
    CALL(evt_eff, 0, STRING("nice"), 0, 0, -1000, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("nice"), 1, 0, -1000, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_map_playanim, STRING("yuge"), 1, 0)
    IF_INT_EQUAL(GSWF(3880), 1)
        IF_INT_EQUAL(GSWF(3876), 0)
            CALL(evt_run_case_evt, 9, 1, STRING("A_w_bed"), 0, PTR(evt_white_bed), 0)
        END_IF
    END_IF
    CALL(evt_map_replace_mapobj, STRING("hi1"), 1)
    CALL(evt_map_replace_mapobj, STRING("hi2"), 1)
    CALL(evt_map_replace_mapobj, STRING("hi3"), 1)
    CALL(evt_map_replace_mapobj, STRING("hi4"), 1)
    CALL(evt_map_replace_mapobj, STRING("hi5"), 1)
    CALL(evt_map_replace_mapobj, STRING("hi6"), 1)
    IF_INT_EQUAL(GSW(1420), 25)
        IF_INT_EQUAL(GSWF(5409), 1)
            IF_INT_EQUAL(GSWF(5411), 0)
                IF_INT_EQUAL(GSWF(5410), 0)
                    CALL(evt_run_case_evt, 9, 1, STRING("A_w_bed"), 0, PTR(iri_25_white_bed), 0)
                END_IF
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        IF_INT_EQUAL(GSWF(5404), 1)
            CALL(evt_item_entry, STRING("iri_30"), 201, 50, 0, 35, 16, GSWF(3890), 0)
        END_IF
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ie1_naka"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ie2_naka"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ie3_naka"), 2)
    RETURN
EVT_END()

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

static USER_FUNC(anim_tevcallback_mobj) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);

    animPoseSetMaterialFlagOn(mobjNameToPtr(name)->poseId, (flag & 0xF) << 24);
    return EVT_RETURN_DONE;
}

