#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "mri.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_ry_lr);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_puni_flag_onoff);
USER_FUNC(evt_puni_init_puni);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_mode);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_shop_setup);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);

__declspec(section ".data") u64 fd_mri_07_negone_one_374;
__declspec(section ".data") s32 fd_mri_07_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_07___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_07___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_07_one_negone_373;
__declspec(section ".data") s32 fd_mri_07___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_07_one_381[1];
__declspec(section ".data") u64 fd_mri_07_negone_one_360;
__declspec(section ".data") s32 fd_mri_07_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_07___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_07___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_07_one_negone_359;
__declspec(section ".data") s32 fd_mri_07___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_07_one_364[1];
static __declspec(section ".data") s32 obj_list[12];
static __declspec(section ".data") s32 goods_list[12];
static s32 trade_list[24];
static s32 shopper_data[38];
s32 chibitoge_nakama[287];
static s32 chibitoge_init[29];
static __declspec(section ".data") s32 chibitoge_talk[4];
__declspec(section ".data") s32 punishop_init[12];
__declspec(section ".data") s32 punishop_talk[2];
__declspec(section ".data") s32 puniinfo_init[12];
s32 puniinfo_talk[118];
static s32 npcEnt[92];
static s32 bero_entry_data[30];
s32 mri_07_init_evt[108];

__declspec(section ".data") u64 fd_mri_07_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_07_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_07___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_07___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_07_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_07___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_07_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_07_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_07_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_07___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_07___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_07_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_07___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_07_one_364[] = {
    1065353216,
};

static __declspec(section ".data") s32 obj_list[] = {
    (s32)"S_item_01", (s32)"A_item_01", (s32)"S_item_02", (s32)"A_item_02", (s32)"S_item_03", (s32)"A_item_03", (s32)"S_item_04", (s32)"A_item_04",
    (s32)"S_item_05", (s32)"A_item_05", (s32)"S_item_06", (s32)"A_item_06",
};

static __declspec(section ".data") s32 goods_list[] = {
    144, 10, 131, 15, 163, 3, 146, 8,
    154, 5, 148, 3,
};

static s32 trade_list[] = {
    144, 327680, 131, 458752, 163, 65536, 146, 262144,
    154, 131072, 148, 65536, 149, 917504, 150, 4915200,
    151, 2818048, 162, 262144, 142, 1114112, 0, 0,
};

static s32 shopper_data[] = {
    (s32)/*"プニ店員"*/"\x83\x76\x83\x6A\x93\x58\x88\xF5", 0, 0, (s32)"stg2_shop_00", (s32)"stg2_shop_01", (s32)"stg2_shop_02", (s32)"stg2_shop_03", (s32)"stg2_shop_04",
    (s32)"stg2_shop_05", (s32)"stg2_shop_06", (s32)"stg2_shop_07", (s32)"stg2_shop_08", (s32)"stg2_shop_09", (s32)"stg2_shop_10", (s32)"stg2_shop_11", (s32)"stg2_shop_12",
    (s32)"stg2_shop_13", (s32)"stg2_shop_14", (s32)"stg2_shop_15", (s32)"stg2_shop_16", (s32)"stg2_shop_17", (s32)"stg2_shop_18", (s32)"stg2_shop_19", (s32)"stg2_shop_20",
    (s32)"stg2_shop_21", (s32)"stg2_shop_22", (s32)"stg2_shop_23", (s32)"stg2_shop_24", (s32)"stg2_shop_25", (s32)"stg2_shop_26", (s32)"stg2_shop_27", (s32)"stg2_shop_28",
    (s32)"stg2_shop_29", (s32)"stg2_shop_30", (s32)"stg2_shop_31", (s32)"stg2_shop_32", (s32)"stg2_shop_33", (s32)"stg2_shop_34",
};

EVT_BEGIN(chibitoge_nakama)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_TOGETTI_JUMP1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_jump_position_nohit, STRING("me"), -167, 44, 41, 400, 50)
    CALL_CHILD(PTR(mri_guide_goryu))
    CALL(evt_puni_flag_onoff, 1, 0, 262144)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイドsp"), 1536)
    CALL(evt_msg_print, 0, STRING("stg2_mri_f01_00"), 0, STRING("ガイドsp"))
    CALL(evt_cam3d_evt_set, 211, 151, 548, 211, 56, 7, 0, 11)
    CALL(evt_npc_set_ry_lr, STRING("プニ店員"), 0)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg2_mri_f01_01"), 0, STRING("プニ店員"))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    CALL(evt_msg_print_party, STRING("stg2_mri_f01_02"))
    CALL(evt_msg_select, 0, STRING("stg2_mri_f01_yesno"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_TOGETTI_JUMP1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_jump_position_nohit, STRING("ちびトゲ"), -138, 0, 72, 300, 30)
        WAIT_MS(200)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), 1073741856)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_TOGETTI_MOVE1"), LW(0), LW(1), LW(2), LW(9))
        ADD(LW(0), 200)
        CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(180.0f), 0)
        CALL(evt_snd_sfxoff, LW(9))
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CALL(evt_msg_print, 0, STRING("stg2_mri_f01_03"), 0, STRING("ガイドsp"))
        CALL(evt_cam3d_evt_set, 211, 151, 548, 211, 56, 7, 0, 11)
        WAIT_FRAMES(1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_f01_04"), 0, STRING("プニ店員"))
        CALL(evt_cam3d_evt_off, 0, 11)
        WAIT_FRAMES(1)
        ELSE
        CALL(evt_msg_print_party, STRING("stg2_mri_f01_05"))
        CALL(evt_npc_flag_onoff, 0, STRING("me"), 512)
        CALL(evt_msg_toge, 1, 0, 0, 0)
        CALL(evt_msg_print, 0, STRING("stg2_mri_f01_06"), 0, 0)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), 512)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_TOGETTI_JUMP1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_jump_position_nohit, STRING("me"), -138, 0, 72, 300, 30)
        WAIT_MS(500)
        CALL(evt_cam3d_evt_set, 211, 151, 548, 211, 56, 7, 0, 11)
        WAIT_FRAMES(1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_f01_07"), 0, STRING("プニ店員"))
        CALL(evt_cam3d_evt_off, 0, 11)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CALL(evt_puni_init_puni, 3, 1, LW(0), LW(1), LW(2), 0)
        SET_VALUE(GSWF(2878), 1)
    END_IF
    CALL(evt_puni_flag_onoff, 1, 1, 262144)
    CALL(evt_puni_set_mode, 1, 1)
    CALL(evt_npc_flag_onoff, 0, STRING("ガイドsp"), 1536)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

static EVT_BEGIN(chibitoge_init)
    SWITCH(GSW(0))
        CASE_BETWEEN(102, 105)
        CASE_GREATER_OR_EQUAL(118)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2836), 0)
            IF_INT_EQUAL(GSWF(2878), 0)
                CALL(evt_npc_set_position, STRING("me"), -170, 0, 0)
                CALL(evt_npc_set_ry, STRING("me"), 90)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(chibitoge_talk)
    CALL_CHILD(PTR(chibitoge_nakama))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(punishop_init)
    CALL(evt_npc_set_position, STRING("me"), 207, 0, -6)
    CALL(evt_npc_set_ry, STRING("me"), 270)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(punishop_talk)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(puniinfo_init)
    CALL(evt_npc_set_position, STRING("me"), 235, 0, 124)
    CALL(evt_npc_set_ry, STRING("me"), 270)
    RETURN
EVT_END()

EVT_BEGIN(puniinfo_talk)
    SWITCH(GSW(0))
        CASE_LESS(112)
        SWITCH(LSW(714))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_00"), 0, STRING("me"))
            SET_VALUE(LSW(714), 1)
            CASE_EQUAL(1)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_01"), 0, STRING("me"))
            SET_VALUE(LSW(714), 2)
            CASE_EQUAL(2)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02"), 0, STRING("me"))
            SET_VALUE(LSW(714), 0)
        END_SWITCH
        CASE_LESS(401)
        SWITCH(LSW(714))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02_01"), 0, STRING("me"))
            SET_VALUE(LSW(714), 1)
            CASE_EQUAL(1)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02_02"), 0, STRING("me"))
            SET_VALUE(LSW(714), 2)
            CASE_EQUAL(2)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02_03"), 0, STRING("me"))
            SET_VALUE(LSW(714), 0)
        END_SWITCH
        CASE_DEFAULT
        SWITCH(LSW(714))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02_04"), 0, STRING("me"))
            SET_VALUE(LSW(714), 1)
            CASE_EQUAL(1)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02_05"), 0, STRING("me"))
            SET_VALUE(LSW(714), 2)
            CASE_EQUAL(2)
            CALL(evt_msg_print, 0, STRING("stg2_mri_f00_02_06"), 0, STRING("me"))
            SET_VALUE(LSW(714), 0)
        END_SWITCH
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ちびトゲ"*/"\x82\xBF\x82\xD1\x83\x67\x83\x51", 1536, 0, (s32)chibitoge_init, 0, (s32)chibitoge_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"プニ店員"*/"\x83\x76\x83\x6A\x93\x58\x88\xF5",
    1536, 0, (s32)punishop_init, 0, (s32)punishop_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"プニ情報屋"*/"\x83\x76\x83\x6A\x8F\xEE\x95\xF1\x89\xAE", 1536,
    0, (s32)puniinfo_init, 0, (s32)puniinfo_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 bero_entry_data[] = {
    (s32)"e_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"mri_06", (s32)"w_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(mri_07_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 7, 0, -310, -1000, -1000, 0, 0)
    CALL(evt_puni_set_hamari, -129, 0, 96, 2, -2, -1000, -1000)
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
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    SWITCH(GSW(0))
        CASE_BETWEEN(109, 110)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI1"))
    END_SWITCH
    CALL(evt_mobj_recovery_blk, STRING("mobj_recover\0\0\0"), 8, 290, 82, 120, 0, 0)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    RETURN
EVT_END()

