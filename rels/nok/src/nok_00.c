#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "memory.h"
#include "string.h"

typedef struct PosterWork { u32 flags; s32 group; s32 shape; } PosterWork;
PosterWork* poster;
void draw_poster(void* userdata, s32 group);
void animPoseDrawShape(s32 poseId, s32 shapeIdx);
void animPoseSetDispCallBack(s32 poseId, void (*callback)(void*, s32), void* userdata);

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_kinopio_setup);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_goodbye_party);
USER_FUNC(evt_mario_hello_party);
USER_FUNC(evt_mario_jump_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_mode);
USER_FUNC(evt_mario_set_motion);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_talk_motion);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_blur_onoff);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_kamek_move_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_pera_onoff);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_autotalkpose);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_move_pos);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_get_haveitemcnt);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_shop_setup);
USER_FUNC(evt_snd_bgm_freq);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_bgmon_f);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_snd_sfxon_3d_ex);
USER_FUNC(evt_sub_get_system_flag);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_sub_save_playtime);
USER_FUNC(evt_telop_entry);
USER_FUNC(evt_win_item_select);
USER_FUNC(kpa_chg_pose);
USER_FUNC(pposter_init);
USER_FUNC(pposter_nok_on);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);
void nok_stg2_013_cb(s32 type, void** work);
void draw_poster(void* userdata, s32 group);
extern s32 bero_case_entry[];
extern s32 evt_bero_info_run[];
extern s32 evt_door_setup[];
extern s32 evt_gazigazi_entry[];
extern s32 evt_memcard_save[];
extern s32 npc_init_evt[];

__declspec(section ".data") u64 fd_nok_00_negone_one_374;
__declspec(section ".data") s32 fd_nok_00_neg_one_382[1];
__declspec(section ".data") s32 fd_nok_00___local_PI_383[1];
__declspec(section ".data") s32 fd_nok_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_nok_00_one_negone_373;
__declspec(section ".data") s32 fd_nok_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_nok_00_one_381[1];
__declspec(section ".data") u64 fd_nok_00_negone_one_360;
__declspec(section ".data") s32 fd_nok_00_neg_one_365[1];
__declspec(section ".data") s32 fd_nok_00___local_PI_366[1];
__declspec(section ".data") s32 fd_nok_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_nok_00_one_negone_359;
__declspec(section ".data") s32 fd_nok_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_nok_00_one_364[1];
s32 nokonoko_A_init[27];
__declspec(section ".data") s32 nokonoko_A_regl[2];
s32 nokonoko_A_talk[55];
__declspec(section ".data") s32 nokonoko_B_init[12];
s32 nokonoko_B_regl[19];
s32 nokonoko_B_talk[44];
s32 nokonoko_B_damage[18];
s32 nokonoko_C_regl[19];
s32 nokonoko_C_talk[44];
s32 nokonoko_D_talk[52];
__declspec(section ".data") s32 iri_15_item_tbl1[2];
__declspec(section ".data") s32 iri_15_item_tbl2[2];
s32 nokonoko_F_talk[318];
static s32 init_white[24];
static s32 talk_white[36];
static s32 kizayarou_regl[19];
static s32 kizayarou_talk[92];
static s32 kizayarou_init[38];
static s32 npcEnt[230];
static s32 bero_entry_data[45];
static __declspec(section ".data") s32 yado_npc[2];
__declspec(section ".data") s32 yado_map[2];
static s32 yado_data[19];
static __declspec(section ".data") s32 mise_npc[2];
static s32 mise_data[19];
static __declspec(section ".data") s32 ie_npc[2];
static __declspec(section ".data") s32 ie_map[2];
static s32 ie_data[19];
static __declspec(section ".data") s32 obj_list[12];
static __declspec(section ".data") s32 goods_list[12];
static s32 trade_list[26];
static s32 shopper_data[38];
static s32 kino_dt[38];
s32 first_time_camera[195];
static s32 hitDmgRetPoints[40];
s32 nok_00_koopa_npc_entry[35];
s32 nok_00_koopa_evt[1250];
s32 nok_00_init_evt[205];

void nok_stg2_013_cb(s32 type, void** work) {
    s32* msg = *work;

    switch (type) {
        case 5:
            if (msg[4] > 0x31) {
                evtSetValue(NULL, LSWF(2), 1);
            }
            break;
    }
}

USER_FUNC(pposter_nok_on) {
    poster->flags |= 1;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_nok_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_nok_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_nok_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_nok_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_nok_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_nok_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_nok_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_nok_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_nok_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_nok_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_nok_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_nok_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_nok_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_nok_00_one_364[] = {
    1065353216,
};

EVT_BEGIN(nokonoko_A_init)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1536)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 26)
        CALL(evt_npc_set_position, STRING("me"), -350, 0, 65)
    END_IF
    IF_INT_EQUAL(GSW(0), 116)
        CALL(evt_npc_set_position, STRING("me"), -260, 0, 90)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(nokonoko_A_regl)
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_A_talk)
    SWITCH(GSW(0))
        CASE_LESS(32)
        CALL(evt_msg_print, 0, STRING("stg1_nok_02"), 0, 0)
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("stg1_nok_02_01"), 0, 0)
        CASE_LESS(65)
        CALL(evt_msg_print, 0, STRING("stg1_nok_03"), 0, 0)
        CASE_EQUAL(354)
        SET_VALUE(GSWF(3877), 1)
        CALL(evt_msg_print, 0, STRING("stg7_nok_01"), 0, 0)
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg1_nok_03_1"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_nok_01_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(nokonoko_B_init)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 512)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 8)
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_B_regl)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_B_talk)
    SWITCH(GSW(0))
        CASE_LESS(32)
        CALL(evt_msg_print, 0, STRING("stg1_nok_04"), 0, 0)
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("stg1_nok_04_01"), 0, 0)
        CASE_LESS(65)
        CALL(evt_msg_print, 0, STRING("stg1_nok_05"), 0, 0)
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg1_nok_05_1"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(""), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_B_damage)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KNP_O_1"))
    CALL(evt_msg_print, 1, STRING(""), 0, 0)
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING("me"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_C_regl)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_C_talk)
    SWITCH(GSW(0))
        CASE_LESS(32)
        CALL(evt_msg_print, 0, STRING("stg1_nok_06"), 0, 0)
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("stg1_nok_06_01"), 0, 0)
        CASE_LESS(65)
        CALL(evt_msg_print, 0, STRING("stg1_nok_07"), 0, 0)
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("me"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg1_nok_07_1_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_D_talk)
    SWITCH(GSW(0))
        CASE_LESS(32)
        CALL(evt_msg_print, 0, STRING("me"), 0, 0)
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("stg1_nok_08_01"), 0, 0)
        CASE_LESS(65)
        CALL(evt_msg_print, 0, STRING("stg1_nok_09"), 0, 0)
        CALL(evt_msg_select, 0, STRING("stg1_nok_09_yesno"))
        CALL(evt_msg_print_add, 0, STRING("stg1_nok_09_01"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg1_nok_09_01_1"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg1_nok_09_01_1_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") s32 iri_15_item_tbl1[] = {
    159, -1,
};

__declspec(section ".data") s32 iri_15_item_tbl2[] = {
    206, -1,
};

EVT_BEGIN(nokonoko_F_talk)
    IF_INT_EQUAL(GSW(1420), 15)
        IF_INT_EQUAL(GSWF(5405), 0)
            CALL(evt_msg_print, 0, STRING(""), 0, 0)
            SET_VALUE(GSWF(5405), 1)
            ELSE
            CALL(evt_msg_print, 0, STRING("irai_15_002"), 0, 0)
            SET_VALUE(LF(0), 0)
            CALL(evt_pouch_get_haveitemcnt, LW(0))
            IF_INT_GREATER(LW(0), 0)
                CALL(evt_msg_continue)
                CALL(evt_win_item_select, 0, 1, LW(0), 0)
                ELSE
                SET_VALUE(LW(0), -1)
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_EQUAL(GSWF(5407), 0)
                IF_INT_EQUAL(LW(0), 159)
                    CALL(evt_pouch_remove_item, 159, LW(0))
                    IF_INT_EQUAL(GSWF(5406), 0)
                        CALL(evt_msg_print, 0, STRING(""), 0, 0)
                        SET_VALUE(GSWF(5406), 1)
                        ELSE
                        CALL(evt_msg_print, 0, STRING("irai_15_004"), 0, 0)
                        SET_VALUE(GSWF(5407), 1)
                    END_IF
                    ELSE
                    IF_INT_EQUAL(LF(0), 0)
                        CALL(evt_msg_print, 0, STRING("irai_15_008"), 0, 0)
                        ELSE
                        CALL(evt_msg_print_add, 0, STRING("irai_15_008"))
                    END_IF
                END_IF
                ELSE
                IF_INT_EQUAL(LW(0), 206)
                    CALL(evt_pouch_remove_item, 206, LW(0))
                    CALL(evt_msg_print, 0, STRING("nok_00"), 0, 0)
                    CALL(evt_item_entry, STRING("nok_01"), 167, 0, -1000, 0, 17, -1, 0)
                    CALL(evt_item_get_item, STRING("nok_01"))
                    CALL(evt_item_get_item_end_wait, STRING("nok_01"))
                    CALL(evt_msg_print, 0, STRING("nok_00"), 0, 0)
                    CALL(evt_sub_save_playtime, GSW(1445))
                    SET_VALUE(GSW(1420), 0)
                    SET_VALUE(GSWF(5389), 1)
                    CALL(evt_msg_print, 0, STRING("nok_01"), 0, 0)
                    ELSE
                    IF_INT_EQUAL(LF(0), 0)
                        CALL(evt_msg_print, 0, STRING("me"), 0, 0)
                        ELSE
                        CALL(evt_msg_print_add, 0, STRING("me"))
                    END_IF
                END_IF
            END_IF
        END_IF
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(5389), 1)
        CALL(evt_msg_print, 0, STRING("irai_15_010"), 0, 0)
        CALL(evt_msg_select, 0, STRING("irai_15_010_sel"))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("irai_15_012"))
            SET_VALUE(LF(0), 0)
            CALL(evt_pouch_get_haveitemcnt, LW(0))
            IF_INT_GREATER(LW(0), 0)
                CALL(evt_msg_continue)
                CALL(evt_win_item_select, 0, 1, LW(0), 0)
                ELSE
                SET_VALUE(LW(0), -1)
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_EQUAL(LW(0), 159)
                CALL(evt_pouch_remove_item, 159, LW(0))
                CALL(evt_msg_print, 0, STRING("irai_15_013"), 0, 0)
                CALL(evt_item_entry, STRING("nok_01"), 167, 0, -1000, 0, 17, -1, 0)
                CALL(evt_item_get_item, STRING("nok_01"))
                CALL(evt_item_get_item_end_wait, STRING("nok_01"))
                CALL(evt_msg_print, 0, STRING("irai_15_015"), 0, 0)
                ELSE
                IF_INT_EQUAL(LF(0), 0)
                    CALL(evt_msg_print, 0, STRING("irai_15_016"), 0, 0)
                    ELSE
                    CALL(evt_msg_print_add, 0, STRING("irai_15_016"))
                END_IF
            END_IF
            ELSE
            CALL(evt_msg_print_add, 0, STRING("irai_15_016"))
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(32)
        CALL(evt_msg_print, 0, STRING("stg1_nok_17"), 0, 0)
        CASE_LESS(56)
        CALL(evt_msg_print, 0, STRING("stg1_nok_17_01"), 0, 0)
        CASE_LESS(65)
        CALL(evt_msg_print, 0, STRING("stg1_nok_18"), 0, 0)
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg1_nok_18_1"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg1_nok_18_1_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_white)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 4096)
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_EQUAL(116)
        CASE_LESS(269)
        CALL(evt_npc_set_position, STRING("me"), 375, 50, -105)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_white)
    SWITCH(GSW(0))
        CASE_LESS(32)
        CALL(evt_msg_print, 0, STRING("stg1_nok_19_01"), 0, 0)
        CASE_LESS(55)
        CALL(evt_msg_print, 0, STRING("stg1_nok_19_02"), 0, 0)
        CASE_LESS(112)
        CALL(evt_msg_print, 0, STRING("nok_00"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("nok_01"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(kizayarou_regl)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

static EVT_BEGIN(kizayarou_talk)
    CALL(evt_mario_get_party, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        IF_INT_EQUAL(LSWF(1), 0)
            CALL(evt_msg_print, 0, STRING("nok"), 0, 0)
            CALL(evt_party_set_dir_npc, 0, STRING("me"))
            CALL(evt_party_cont_onoff, 0, 0)
            CALL(evt_msg_print, 0, STRING("stg1_nok_11"), 0, STRING("party"))
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(evt_msg_print, 0, STRING("stg1_nok_12"), 0, 0)
            CALL(evt_party_cont_onoff, 0, 0)
            CALL(evt_msg_print, 0, STRING("stg1_nok_13"), 0, STRING("party"))
            CALL(evt_party_cont_onoff, 0, 1)
            SET_VALUE(LSWF(1), 1)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg1_nok_14"), 0, 0)
            CALL(evt_party_set_dir_npc, 0, STRING("me"))
            CALL(evt_party_cont_onoff, 0, 0)
            CALL(evt_msg_print, 0, STRING("stg1_nok_15"), 0, STRING("party"))
            CALL(evt_party_cont_onoff, 0, 1)
        END_IF
        ELSE
        CALL(evt_msg_print, 0, STRING("stg1_nok_16"), 0, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(kizayarou_init)
    SET_VALUE(LW(0), STRING("キザ野郎"))
    CALL(evt_npc_entry, LW(0), STRING("c_kiza"))
    CALL(evt_npc_set_tribe, LW(0), STRING("キザ野郎"))
    CALL(evt_npc_change_interrupt, LW(0), 6, PTR(kizayarou_talk))
    CALL(evt_npc_change_interrupt, LW(0), 1, PTR(kizayarou_regl))
    CALL(evt_npc_set_position, LW(0), 350, 0, 175)
    CALL(evt_npc_set_ry, LW(0), 270)
    CALL(evt_npc_flag_onoff, 1, LW(0), 1536)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ノコノコA"*/"\x83\x6D\x83\x52\x83\x6D\x83\x52\x41", 0, 0, (s32)nokonoko_A_init, (s32)nokonoko_A_regl, (s32)nokonoko_A_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ノコノコB"*/"\x83\x6D\x83\x52\x83\x6D\x83\x52\x42",
    0, 0, (s32)npc_init_evt, (s32)nokonoko_B_regl, (s32)nokonoko_B_talk, (s32)nokonoko_B_damage, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ノコノコC"*/"\x83\x6D\x83\x52\x83\x6D\x83\x52\x43", 0,
    0, (s32)npc_init_evt, (s32)nokonoko_C_regl, (s32)nokonoko_C_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"ノコノコD"*/"\x83\x6D\x83\x52\x83\x6D\x83\x52\x44", 0, 0,
    (s32)npc_init_evt, 0, (s32)nokonoko_D_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ノコノコF"*/"\x83\x6D\x83\x52\x83\x6D\x83\x52\x46", 0, 0, (s32)npc_init_evt,
    0, (s32)nokonoko_F_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", 0, 0, (s32)npc_init_evt, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"店員"*/"\x93\x58\x88\xF5", 0, 0, (s32)npc_init_evt, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ババ"*/"\x83\x6F\x83\x6F", 0, 0, (s32)npc_init_evt, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"ホワイト"*/"\x83\x7A\x83\x8F\x83\x43\x83\x67", 1073743360, 0, (s32)init_white, 0, (s32)talk_white, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"hei_01", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"nok_01", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static __declspec(section ".data") s32 yado_npc[] = {
    (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", 0,
};

__declspec(section ".data") s32 yado_map[] = {
    (s32)"S_yad_mae", 0,
};

static s32 yado_data[] = {
    1, 9, (s32)"A_yad_doa01", 9, (s32)"A_yad_in_doa", (s32)"S_yado_open", (s32)"S_yado_doa_open", (s32)"S_yado_close",
    (s32)"S_yado_doa_close", (s32)"S_yad_mae", (s32)"S_yad_doa01", (s32)"S_yado_in", (s32)"A_yado_in", (s32)"S_yado_in", (s32)"A_yado_in", (s32)yado_npc,
    (s32)yado_map, 0, 0,
};

static __declspec(section ".data") s32 mise_npc[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", 0,
};

static s32 mise_data[] = {
    1, 9, (s32)"A_mise_doa", 9, (s32)"A_mise_in_doa", (s32)"S_mise_open", (s32)"S_mise_doa_open", (s32)"S_mise_close",
    (s32)"S_mise_doa_close", (s32)"S_mise_mae", (s32)"S_mise_doa", (s32)"S_mise_in", (s32)"A_mise_in", (s32)"S_mise_in", (s32)"A_mise_in", (s32)mise_npc,
    0, 0, 0,
};

static __declspec(section ".data") s32 ie_npc[] = {
    (s32)/*"ノコノコD"*/"\x83\x6D\x83\x52\x83\x6D\x83\x52\x44", 0,
};

static __declspec(section ".data") s32 ie_map[] = {
    (s32)"S_ie_mae", 0,
};

static s32 ie_data[] = {
    1, 9, (s32)"A_ie_doa", 9, (s32)"A_ie_in_doa", (s32)"S_ie_open", (s32)"S_ie_doa_open", (s32)"S_ie_close",
    (s32)"S_ie_doa_close", (s32)"S_ie_mae", (s32)"S_ie_doa", (s32)"S_ie_in", (s32)"A_ie_in", (s32)"S_ie_in", (s32)"A_ie_in", (s32)ie_npc,
    (s32)ie_map, 0, 0,
};

static __declspec(section ".data") s32 obj_list[] = {
    (s32)"S_item_01", (s32)"A_item_01", (s32)"S_item_02", (s32)"A_item_02", (s32)"S_item_03", (s32)"A_item_03", (s32)"S_item_04", (s32)"A_item_04",
    (s32)"S_item_05", (s32)"A_item_05", (s32)"S_item_06", (s32)"A_item_06",
};

static __declspec(section ".data") s32 goods_list[] = {
    132, 8, 139, 5, 143, 5, 147, 8,
    154, 5, 148, 4,
};

static s32 trade_list[] = {
    132, 262144, 139, 131072, 143, 131072, 147, 262144,
    154, 131072, 148, 131072, 138, 655360, 223, 3932160,
    222, 262144, 234, 655360, 167, 131072, 169, 327680,
    0, 0,
};

static s32 shopper_data[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", 0, 0, (s32)"shop_00", (s32)"shop_01", (s32)"shop_02", (s32)"shop_03", (s32)"shop_04",
    (s32)"shop_05", (s32)"shop_06", (s32)"shop_07", (s32)"shop_08", (s32)"shop_09", (s32)"shop_10", (s32)"shop_11", (s32)"shop_12",
    (s32)"shop_13", (s32)"shop_14", (s32)"shop_15", (s32)"shop_16", (s32)"shop_17", (s32)"shop_18", (s32)"shop_19", (s32)"shop_20",
    (s32)"shop_21", (s32)"shop_22", (s32)"shop_23", (s32)"shop_24", (s32)"shop_25", (s32)"shop_26", (s32)"shop_27", (s32)"shop_28",
    (s32)"shop_29", (s32)"shop_30", (s32)"shop_31", (s32)"shop_32", (s32)"shop_33", (s32)"shop_34",
};

static s32 kino_dt[] = {
    0, 0, 0, 0, 5, -1014595584, 1109655552, -1015021568,
    -1014628352, 1103626240, -1017380864, -1007190016, 1130561536, -1033895936, -1012695040, 1119092736,
    -1017053184, -1041235968, -1012596736, 1103626240, -1020002304, (s32)/*"宿店員"*/"\x8F\x68\x93\x58\x88\xF5", (s32)"yado_00", (s32)"yado_01",
    (s32)"yado_02", (s32)"yado_03", (s32)"yado_04", (s32)"yado_05", (s32)"yado_06", (s32)"yado_07", (s32)"yado_08", (s32)"yado_09",
    (s32)"yado_10", (s32)"yado_11", (s32)"yado_12", (s32)"yado_13", 0, 0,
};

EVT_BEGIN(first_time_camera)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_set_pos, -545, 0, 0)
    CALL(evt_party_set_pos, 0, -555, 0, 0)
    CALL(evt_npc_set_position, STRING("ノコノコA"), -250, 0, 65)
    CALL(evt_cam3d_evt_set, 730, 617, 915, 245, 93, 144, 0, 11)
    CALL(evt_seq_wait, 2)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_telop_entry, 2)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, FLOAT(-450.0f), FLOAT(400.0f), FLOAT(840.0f), FLOAT(-300.0f), FLOAT(165.0f), FLOAT(255.0f), 6000, 13)
        WAIT_MS(8500)
        CALL(evt_cam3d_evt_set, FLOAT(-380.0f), FLOAT(90.0f), FLOAT(352.0f), FLOAT(-380.0f), FLOAT(35.0f), FLOAT(47.0f), 0, 13)
    END_INLINE_EVENT
    WAIT_MS(6000)
    CALL(evt_mario_mov_pos2, -400, 65, FLOAT(120.0f))
    WAIT_MS(500)
    CALL(evt_npc_move_position, STRING("ノコノコA"), -350, 65, 0, FLOAT(60.0f), 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg1_nok_01"), 0, STRING("ノコノコA"))
    CALL(evt_mario_get_motion, LW(0))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_talk_motion)
    WAIT_MS(500)
    CALL(evt_mario_set_motion, LW(0))
    CALL(evt_msg_print, 0, STRING("stg1_nok_01_01"), 0, STRING("ノコノコA"))
    CALL(evt_mario_get_party, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mario_goodbye_party, 0)
        CALL(evt_mario_hello_party, 0, 1)
    END_IF
    CALL(evt_party_move_pos, 0, -414, 79, 500)
    CALL(evt_party_stop, 0)
    WAIT_MS(100)
    CALL(evt_msg_print, 0, STRING("stg1_nok_01_02"), 0, STRING("party"))
    CALL(evt_msg_print, 0, STRING("stg1_nok_01_03"), 0, STRING("ノコノコA"))
    CALL(evt_msg_print, 0, STRING("stg1_nok_01_04"), 0, STRING("party"))
    WAIT_MS(100)
    CALL(evt_cam3d_evt_off, 500, 4)
    CALL(evt_snd_bgmon_f, 768, STRING("BGM_STG1_NOK1"), 2000)
    SET_VALUE(GSW(0), 26)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

static s32 hitDmgRetPoints[] = {
    (s32)"mod_00", 0, -998637568, 0, (s32)"mod_01", 0, -998637568, 0,
    (s32)"mod_02", 0, -998637568, 0, (s32)"mod_04", 0, -998637568, 0,
    (s32)"mod_05", 0, -998637568, 0, (s32)"mod_06", 0, -998637568, 0,
    (s32)"mod_07", 0, -998637568, 0, (s32)"mod_08", 0, -998637568, 0,
    (s32)"A_hasi04", 0, -998637568, 0, 0, 0, 0, 0,
};

EVT_BEGIN(nok_00_koopa_npc_entry)
    CALL(evt_npc_entry, STRING("poster"), STRING("c_p_peach"))
    CALL(evt_npc_pera_onoff, STRING("poster"), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("poster"), 32)
    CALL(evt_mapobj_get_position, STRING("S_ie_mad02"), LW(0), LW(1), LW(2))
    SUBTRACT_FLOAT(LW(1), FLOAT(25.0f))
    ADD_FLOAT(LW(2), FLOAT(8.0f))
    CALL(evt_npc_set_position, STRING("poster"), LW(0), LW(1), LW(2))
    CALL(pposter_init)
    RETURN
EVT_END()

EVT_BEGIN(nok_00_koopa_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG1_NOK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_NOK1"))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mario_set_pos, -500, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_npc_set_position, STRING("ババ"), -550, 50, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ノコノコA"), 32768)
    CALL(evt_npc_set_ry, STRING("ノコノコA"), 90)
    CALL(evt_cam3d_evt_set, -315, 146, 529, -315, 50, -13, 0, 11)
    CALL(evt_seq_wait, 2)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
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
        WAIT_MS(300)
        CALL(evt_npc_kamek_move_position, STRING("ババ"), -405, 57, 10, 0, 50, 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -342, 80, 60)
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ノコノコA"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    CALL(evt_npc_flag_onoff, 0, STRING("ノコノコA"), 32768)
    CALL(evt_npc_set_ry, STRING("ノコノコA"), 270)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("kpa_stg2_004"), 0, STRING("ノコノコA"))
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_KUPPA1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_NOK1"))
    CALL(evt_npc_get_position, STRING("ノコノコA"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(0))
    ADD(LW(3), 1)
    LOOP(10)
        CALL(evt_npc_set_position, STRING("ノコノコA"), LW(3), LW(1), LW(2))
        SUBTRACT(LW(3), 2)
        WAIT_MS(50)
        CALL(evt_npc_set_position, STRING("ノコノコA"), LW(3), LW(1), LW(2))
        ADD(LW(3), 2)
        WAIT_MS(50)
    END_LOOP
    CALL(evt_npc_set_position, STRING("ノコノコA"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_autotalkpose, STRING("ノコノコA"), STRING("NOK_S_2"), STRING("NOK_T_2"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_004_1"), 0, STRING("ノコノコA"))
    CALL(evt_npc_flag_onoff, 0, STRING("ノコノコA"), 1024)
    CALL(evt_npc_set_anim, STRING("ノコノコA"), STRING("NOK_R_2"))
    WAIT_MS(1000)
    CALL(evt_npc_set_ry, STRING("ノコノコA"), 90)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_NOKO_ESCAPE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_blur_onoff, 1, STRING("ノコノコA"))
    CALL(evt_npc_move_position, STRING("ノコノコA"), -70, 50, 0, 180, 0)
    CALL(evt_npc_blur_onoff, 0, STRING("ノコノコA"))
    CALL(evt_mapobj_get_position, STRING("S_mise_doa"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(0), -250)
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(500)
    CALL(evt_mapobj_get_position, STRING("S_ie_doa"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(0), -200)
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 1, STRING("ノコノコA"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("ノコノコB"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("ノコノコC"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("ノコノコD"), 128)
    CALL(evt_cam3d_evt_set, -335, 133, 430, -335, 55, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_007"), 0, STRING("mario"))
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ババ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
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
    CALL(evt_npc_flag_onoff, 1, STRING("ババ"), 32)
    CALL(evt_cam3d_evt_set, -280, 133, 430, -280, 55, -13, 2000, 11)
    CALL(evt_npc_kamek_move_position, STRING("ババ"), -275, 135, 10, 0, 80, 0)
    SET_VALUE(GF(0), 1)
    WAIT_FRAMES(1)
    CALL(evt_npc_flag_onoff, 0, STRING("ババ"), 32)
    CALL(evt_msg_print, 0, STRING("kpa_stg2_008"), 0, STRING("ババ"))
    CALL(evt_cam3d_evt_set, 290, 144, 479, 290, 57, -13, 2000, 11)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, 350, 166, 162, 350, 115, -134, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_snd_sfxon, STRING("SFX_KUPPA_FIND_PEACH1"), 0)
    WAIT_MS(400)
    CALL(evt_mario_set_pos, 200, 0, 40)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("kpa_stg2_009"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 300, 192, 363, 300, 105, -130, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pos, 130, 0, 40)
    CALL(evt_mario_mov_pos2, 190, -37, 120)
    CALL(evt_mario_jump_pos, 230, 25, -85, 600, 0, -1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_LAUGH2_1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_3"), STRING("KPA_T_2"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_010"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 350, 166, 162, 350, 115, -134, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_toge, 3, 355, 100, -150)
    CALL(evt_msg_print, 0, STRING("kpa_stg2_011"), 0, 0)
    CALL(evt_cam3d_evt_set, 300, 192, 363, 300, 105, -130, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_012"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 190, 176, 363, 190, 90, -130, 800, 11)
    WAIT_MS(800)
    CALL(evt_npc_set_position, STRING("ババ"), 30, 70, -35)
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
    CALL(evt_npc_kamek_move_position, STRING("ババ"), 150, -35, 20, 0, 60, 0)
    SET_VALUE(GF(0), 1)
    WAIT_FRAMES(1)
    SET_VALUE(LSWF(2), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(LSWF(2), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_npc_set_anim, STRING("ババ"), STRING("A_4"))
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("kpa_stg2_013"), PTR(nok_stg2_013_cb), STRING("ババ"))
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_3"), STRING("KPA_T_2"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_014"), 0, STRING("mario"))
    CALL(evt_npc_flag_onoff, 0, STRING("ノコノコA"), 128)
    CALL(evt_npc_set_position, STRING("ノコノコA"), 420, 0, 0)
    CALL(evt_npc_set_ry, STRING("ノコノコA"), 270)
    CALL(evt_msg_print, 0, STRING("kpa_stg2_015"), 0, STRING("ノコノコA"))
    CALL(kpa_chg_pose, STRING("KPA_S_1"))
    SET_VALUE(GW(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("ノコノコA"), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), 1)
        LOOP(0)
            IF_INT_EQUAL(GW(0), 1)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_set_position, STRING("ノコノコA"), LW(3), LW(1), LW(2))
            SUBTRACT(LW(3), 2)
            WAIT_MS(50)
            CALL(evt_npc_set_position, STRING("ノコノコA"), LW(3), LW(1), LW(2))
            ADD(LW(3), 2)
            WAIT_MS(50)
        END_LOOP
        CALL(evt_npc_set_position, STRING("ノコノコA"), LW(0), LW(1), LW(2))
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 324, 189, 551, 324, 85, -44, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_SURPRISED1_2"), LW(0), LW(1), LW(2), 0)
    ADD(LW(1), 65)
    CALL(evt_eff_fukidashi, 2, STRING(""), 0, 0, 0, LW(0), LW(1), LW(2), 0, 0, 60)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ババ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 403, 104, 331, 403, 43, -17, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_msg_print, 0, STRING("kpa_stg2_016"), 0, STRING("ノコノコA"))
    SET_VALUE(GW(0), 1)
    WAIT_MS(100)
    CALL(evt_cam3d_evt_set, 306, 168, 344, 306, 85, -130, 1000, 11)
    CALL(evt_npc_flag_onoff, 0, STRING("ノコノコA"), 1024)
    CALL(evt_npc_set_anim, STRING("ノコノコA"), STRING("NOK_R_4"))
    CALL(evt_npc_move_position, STRING("ノコノコA"), 408, -46, 500, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_NOKO_JUMP1"), 408, 0, -46, 0)
    CALL(evt_npc_jump_position_nohit, STRING("ノコノコA"), 374, 50, -77, 500, 60)
    CALL(evt_npc_move_position, STRING("ノコノコA"), 374, -125, 500, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_NOKO_JUMP1"), 374, 50, -125, 0)
    CALL(evt_npc_jump_position_nohit, STRING("ノコノコA"), 374, 64, -153, 500, 20)
    BEGIN_INLINE_EVENT
        WAIT_MS(750)
        CALL(evt_npc_set_anim, STRING("ノコノコA"), STRING("NOK_A_1"))
        CALL(evt_npc_set_anim, STRING("poster"), STRING("A_1"))
        WAIT_MS(750)
        CALL(evt_npc_set_anim, STRING("ノコノコA"), STRING("NOK_S_3"))
        CALL(evt_npc_set_anim, STRING("poster"), STRING("Z_2"))
        CALL(evt_npc_flag_onoff, 1, STRING("poster"), 128)
        CALL(pposter_nok_on)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ノコノコA"), 1024)
    CALL(evt_npc_get_position, STRING("ノコノコA"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_NOKO_JUMP1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_snd_sfxon_3d_ex, STRING("SFX_KUPPA_NOKO_POSTER1"), LW(0), LW(1), LW(2), 255, 255, 750, 16, 0)
    CALL(evt_npc_jump_position_nohit, STRING("ノコノコA"), LW(0), LW(1), LW(2), 1500, 50)
    CALL(kpa_chg_pose, STRING("KPA_O_1"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_SURPRISED1_1"), LW(0), LW(1), LW(2), 0)
    ADD(LW(1), 65)
    CALL(evt_eff_fukidashi, 2, STRING(""), 0, 0, 0, LW(0), LW(1), LW(2), 0, 0, 60)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ババ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(kpa_chg_pose, STRING("KPA_S_5"))
    CALL(evt_npc_set_anim, STRING("ノコノコA"), STRING("NOK_R_3"))
    CALL(evt_npc_move_position, STRING("ノコノコA"), 316, -154, 500, 0, 0)
    CALL(evt_npc_move_position, STRING("ノコノコA"), 280, -199, 500, 0, 0)
    CALL(evt_npc_set_ry, STRING("ノコノコA"), 90)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ie_in_kabe"), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_mapobj_get_position, STRING("S_ie_doa"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN1"), LW(0), LW(1), LW(2), 0)
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(30)
            ADD_FLOAT(LW(0), FLOAT(3.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_ie_doa"), 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_MS(500)
        CALL(evt_mapobj_get_position, STRING("S_ie_doa"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d_ex, STRING("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 255, 255, 400, 16, 0)
        SET_FLOAT_VALUE(LW(0), FLOAT(90.0f))
        LOOP(30)
            SUBTRACT_FLOAT(LW(0), FLOAT(3.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_ie_doa"), 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, STRING("ノコノコA"), 1073741824)
    CALL(evt_npc_move_position, STRING("ノコノコA"), 258, -179, 500, 0, 0)
    CALL(evt_npc_move_position, STRING("ノコノコA"), 335, -231, 500, 0, 0)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 208, 177, 333, 208, 97, -134, 800, 11)
    WAIT_MS(800)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_5"), STRING("KPA_T_5"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_017"), 0, STRING("mario"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_018"), 0, STRING("ババ"))
    WAIT_MS(1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_SATIATED2_2"), LW(0), LW(1), LW(2), 0)
    SET_VALUE(GF(1), 0)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 32000)
        LOOP(40)
            SUBTRACT(LW(0), 750)
            CALL(evt_snd_bgm_freq, 0, LW(0))
            WAIT_MS(50)
        END_LOOP
        CALL(evt_snd_bgmoff_f, 512, 2000)
        SET_VALUE(GF(1), 1)
    END_INLINE_EVENT
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_2"), STRING("KPA_T_4"))
    CALL(evt_msg_print, 0, STRING("kpa_stg2_019"), 0, STRING("mario"))
    LABEL(99)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(GF(1), 0)
        GOTO(99)
    END_IF
    SET_VALUE(GSW(0), 117)
    CALL(evt_fade_entry, 6, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 6)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 0)
    CALL(evt_fade_set_mapchange_type, 1, 59, 0, 58, 0)
    CALL(evt_bero_mapchange, STRING("mri_00"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(nok_00_init_evt)
    IF_INT_EQUAL(GSW(0), 116)
        CALL(evt_mario_set_mode, 2)
        CALL_CHILD(PTR(nok_00_koopa_npc_entry))
        SPAWN_EVENT(PTR(nok_00_koopa_evt))
        ELSE
        SET_VALUE(LW(0), PTR(bero_entry_data))
        CALL(evt_bero_get_info)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG1_NOK1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG1_NOK1"))
        IF_INT_LESS(GSW(0), 26)
            SPAWN_EVENT(PTR(bero_case_entry))
            SPAWN_EVENT(PTR(first_time_camera))
            ELSE
            CALL_CHILD(PTR(evt_bero_info_run))
        END_IF
    END_IF
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 23)
        IF_INT_LESS_OR_EQUAL(GSW(0), 56)
            CALL_CHILD(PTR(kizayarou_init))
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(1624), 0)
        SET_VALUE(GSWF(1624), 1)
    END_IF
    CALL(evt_map_playanim, STRING("S_kawa"), 1, 0)
    SET_VALUE(LW(0), PTR(yado_data))
    CALL_CHILD(PTR(evt_door_setup))
    SET_VALUE(LW(0), PTR(mise_data))
    CALL_CHILD(PTR(evt_door_setup))
    SET_VALUE(LW(0), PTR(ie_data))
    CALL_CHILD(PTR(evt_door_setup))
    IF_INT_NOT_EQUAL(GSW(0), 116)
        CALL(evt_mobj_save_blk, STRING("mobj_save"), 155, 60, -60, 0, 0)
    END_IF
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    CALL(evt_kinopio_setup, PTR(kino_dt))
    LOOP(5)
        CALL(evt_sub_random, 10, LW(0))
        CALL(evt_eff, 0, STRING("butterfly"), LW(0), -395, 20, 250, 0, 0, 0, 0, 0, 0, 0, 0)
    END_LOOP
    LOOP(5)
        CALL(evt_sub_random, 10, LW(0))
        CALL(evt_eff, 0, STRING("butterfly"), LW(0), -80, 20, 270, 0, 0, 0, 0, 0, 0, 0, 0)
    END_LOOP
    LOOP(2)
        CALL(evt_sub_random, 10, LW(0))
        CALL(evt_eff, 0, STRING("butterfly"), LW(0), -40, 20, 470, 0, 0, 0, 0, 0, 0, 0, 0)
    END_LOOP
    LOOP(2)
        CALL(evt_sub_random, 10, LW(0))
        CALL(evt_eff, 0, STRING("butterfly"), LW(0), 375, 20, 250, 0, 0, 0, 0, 0, 0, 0, 0)
    END_LOOP
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -70, 0, 350, STRING("S_ground03"), 125, GSWF(5601))
    RETURN
EVT_END()

USER_FUNC(pposter_init) {
    NpcEntry* npc;

    poster = _mapAlloc(sizeof(PosterWork));
    memset(poster, 0, sizeof(PosterWork));
    poster->shape = animPoseGetShapeIdx(npcNameToPtr("poster")->poseId, "pPlaneShape2");
    // ノコノコA
    npc = npcNameToPtr("\x83\x6D\x83\x52\x83\x6D\x83\x52\x41");
    poster->group = animPoseGetGroupIdx(npc->poseId, "locator7");
    animPoseSetDispCallBack(npc->poseId, draw_poster, NULL);
    return EVT_RETURN_DONE;
}

void draw_poster(void* userdata, s32 group) {
    NpcEntry* npc = npcNameToPtr("poster");

    if (group == poster->group) {
        if ((poster->flags & 1) != 0) {
            animPoseDrawShape(npc->poseId, poster->shape);
        }
    }
}

