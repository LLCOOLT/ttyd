#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_party_use_check);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_party_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_tik_03_negone_one_374;
__declspec(section ".data") s32 fd_tik_03_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_03___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_03_one_negone_373;
__declspec(section ".data") s32 fd_tik_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_03_one_381[1];
__declspec(section ".data") u64 fd_tik_03_negone_one_360;
__declspec(section ".data") s32 fd_tik_03_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_03___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_03_one_negone_359;
__declspec(section ".data") s32 fd_tik_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_03_one_364[1];
s32 bero_05_custom_in[30];
__declspec(section ".data") s32 bero_05_custom_out[12];
static s32 bero_entry_data[45];
static s32 bero_entry_data2[30];
static s32 guide_init[48];
static __declspec(section ".data") s32 guide_talk[11];
static s32 npcEnt[46];
static s32 puni_walk_se[20];
s32 puni_soguu_3[584];
s32 anm_para_snd[72];
s32 anm_rapa_snd[72];
s32 puni_switch[133];
s32 puni_nakama[93];
s32 tik03_switch_evt[70];
s32 tik_03_init_evt[116];

__declspec(section ".data") u64 fd_tik_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_03_one_364[] = {
    1065353216,
};

EVT_BEGIN(bero_05_custom_in)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 112)
        IF_INT_EQUAL(GSWF(2884), 0)
            SET_VALUE(GSWF(2884), 1)
        END_IF
        IF_INT_EQUAL(GSWF(2840), 1)
            SET_VALUE(GSWF(2840), 0)
        END_IF
        IF_INT_EQUAL(GSWF(2827), 1)
            SET_VALUE(GSWF(2827), 0)
        END_IF
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(bero_05_custom_out)
    IF_INT_EQUAL(GSW(0), 69)
        SET_VALUE(GSW(0), 70)
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"s_bero_1", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tik_04", (s32)"n_bero_1", 65537, 0, 0, (s32)"dokan",
    131072, 2, 100000, 0, 0, -1, (s32)bero_05_custom_in, 10,
    0, (s32)"win_06", (s32)"dokan1", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_entry_data2[] = {
    (s32)"dokan", 131072, 2, 100000, 0, 0, -1, 0,
    10, (s32)bero_05_custom_out, (s32)"sys_01", (s32)"stg_2", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(guide_init)
    SWITCH(GSW(0))
        CASE_EQUAL(66)
        CALL(evt_npc_set_position, STRING("me"), -80, -149, 50)
        CALL(evt_npc_set_ry, STRING("me"), 90)
        CASE_EQUAL(67)
        CALL(evt_npc_set_position, STRING("me"), 100, -150, 50)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        CASE_EQUAL(68)
        CALL(evt_npc_set_position, STRING("me"), 230, -50, 80)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(guide_talk)
    SWITCH(GSW(0))
        CASE_EQUAL(67)
        WAIT_MS(1000)
        CALL_CHILD(PTR(puni_switch))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガイド"*/"\x83\x4B\x83\x43\x83\x68", 1536, 0, (s32)guide_init, 0, (s32)guide_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(puni_walk_se)
    LOOP(0)
        CALL(evt_npc_get_position, STRING("ガイド"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_MOVE2_1"), LW(0), LW(1), LW(2), 0)
        WAIT_FRAMES(5)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(puni_soguu_3)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(200)
    CALL(evt_mario_normalize)
    WAIT_MS(200)
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ガイド"), 0, 0, 0, 0, 0, 0, 0, 30)
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("ガイド"), STRING("R_1"))
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_key_onoff, 1)
    END_INLINE_EVENT
    CALL(evt_npc_set_ry, STRING("ガイド"), 270)
    SPAWN_EVENT_GET_ID(PTR(puni_walk_se), LW(10))
    CALL(evt_npc_move_position, STRING("ガイド"), -455, 59, 0, FLOAT(180.0f), 0)
    DELETE_EVENT(LW(10))
    SET_VALUE(GW(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(2), 0)
                IF_INT_LESS(LW(0), -370)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mario_normalize)
        LOOP(0)
            CALL(evt_mario_party_use_check, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir, 0, 270, -1)
        SET_VALUE(GW(0), 1)
    END_INLINE_EVENT
    LOOP(GW(0))
        CALL(evt_npc_reverse_ry, STRING("ガイド"))
        WAIT_MS(800)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), 30)
        CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(120.0f))
        CALL(evt_party_set_dir_npc, 0, STRING("ガイド"))
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS_OR_EQUAL(LW(2), 10)
        CALL(evt_mario_mov_pos2, LW(0), 10, FLOAT(120.0f))
    END_IF
    CALL(evt_mario_set_dir_npc, STRING("ガイド"))
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1073741856)
    CALL(evt_npc_set_ry, STRING("ガイド"), 90)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ガイド"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_set_anim, STRING("ガイド"), STRING("S_1"))
    WAIT_MS(500)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG2_PUNI1"))
    CALL(evt_snd_envoff, 512)
    CALL(evt_msg_print, 0, STRING("mac_1_012"), 0, STRING("ガイド"))
    CALL(evt_cam3d_evt_set, -400, -35, 432, -418, -105, 24, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_1_013"), 0, STRING("ガイド"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_1_014"), 0, STRING("ガイド"))
    CALL(evt_msg_select, 0, STRING("mac_1_014_yesno"))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("mac_1_019"))
        ELSE
        CALL(evt_msg_print_add, 0, STRING("mac_1_015"))
        CALL(evt_mario_set_dir, 90, 300, 0)
        CALL(evt_msg_print_party, STRING("mac_1_016"))
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_msg_print_party, STRING("mac_1_017"))
        CALL(evt_msg_print, 0, STRING("mac_1_018"), 0, STRING("ガイド"))
    END_IF
    WAIT_MS(333)
    CALL(evt_msg_print_party, STRING("mac_1_020"))
    CALL(evt_cam3d_evt_set, -435, -78, 289, -435, -130, -7, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("mac_1_021"), 0, STRING("ガイド"))
    CALL(evt_cam3d_evt_set, -400, -33, 432, -400, -105, 24, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("mac_1_022"))
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING("mac_1_023"), 0, STRING("ガイド"))
    CALL(evt_cam3d_evt_set, -400, -33, 432, -400, -105, 24, 500, 11)
    WAIT_MS(333)
    CALL(evt_msg_print_party, STRING("mac_1_024"))
    CALL(evt_cam3d_evt_set, -445, -90, 257, -445, -141, -42, 0, 11)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_1_025"), 0, STRING("ガイド"))
    CALL(evt_cam3d_evt_set, -400, -23, 432, -400, -95, 24, 0, 11)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_1_026"), 0, STRING("ガイド"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 25)
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_1_027"), 0, STRING("ガイド"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("mac_1_028"))
    CALL(evt_msg_print, 0, STRING("mac_1_029"), 0, STRING("ガイド"))
    CALL(evt_cam3d_evt_set, 100, -23, 432, 100, -95, 24, 3000, 11)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_npc_get_position, STRING("ガイド"), LW(10), LW(11), LW(12))
            IF_INT_LESS_OR_EQUAL(LW(0), LW(10))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_npc_get_position, STRING("ガイド"), LW(10), LW(11), LW(12))
            IF_INT_LESS_OR_EQUAL(LW(0), LW(10))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    SPAWN_EVENT_GET_ID(PTR(puni_walk_se), LW(10))
    CALL(evt_npc_move_position, STRING("ガイド"), 100, 50, 0, FLOAT(180.0f), 0)
    DELETE_EVENT(LW(10))
    WAIT_MS(200)
    CALL(evt_npc_set_ry, STRING("ガイド"), 270)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_1_029_00"), 0, STRING("ガイド"))
    CALL(evt_npc_flag_onoff, 0, STRING("ガイド"), 1073741856)
    WAIT_MS(800)
    CALL(evt_cam3d_evt_off, 0, 11)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1"))
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    SET_VALUE(GSW(0), 67)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(anm_para_snd)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 55, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 115, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 175, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 245, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 305, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 365, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 425, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), -454, -50, -90, 0)
    RETURN
EVT_END()

EVT_BEGIN(anm_rapa_snd)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), -454, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 425, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 365, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 305, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 245, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 175, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 115, -50, -90, 0)
    WAIT_MS(100)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_LOAD_APPEAR1"), 55, -50, -90, 0)
    RETURN
EVT_END()

EVT_BEGIN(puni_switch)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_stop, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1073741856)
    CALL(evt_msg_print, 0, STRING("mac_1_029_01"), 0, STRING("me"))
    CALL(evt_npc_set_ry, STRING("me"), 90)
    SPAWN_EVENT_GET_ID(PTR(puni_walk_se), LW(10))
    CALL(evt_npc_move_position, STRING("me"), 220, 50, 0, FLOAT(120.0f), 0)
    DELETE_EVENT(LW(10))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("mac_1_030"), 0, STRING("me"))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BIKKURI_SWITCH_ON1"), 220, 50, 0, 0)
    CALL(evt_cam_shake, 4, FLOAT(0.01953125f), FLOAT(0.0f), 100)
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
    SET_VALUE(GSWF(1334), 1)
    CALL(evt_map_playanim, STRING("anm_para"), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kabe_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kabe_2"), 1)
    CALL(evt_hitobj_onoff, STRING("a_para_d"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("a_para_d1"), 1, 0)
    CALL_CHILD(PTR(anm_para_snd))
    CALL(evt_npc_set_position, STRING("me"), 230, -50, 80)
    CALL(evt_npc_flag_onoff, 0, STRING("ガイド"), 1073741856)
    CALL(evt_party_run, 0)
    SET_VALUE(GSW(0), 68)
    CALL(evt_mario_key_onoff, 1)
    WAIT_MS(1500)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("para"), 1)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    RETURN
EVT_END()

EVT_BEGIN(puni_nakama)
    LOOP(0)
        IF_INT_EQUAL(GSW(0), 68)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(2), -90)
                IF_INT_GREATER_OR_EQUAL(LW(0), 300)
                    BREAK_LOOP
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_stop, 1)
    CALL(evt_npc_get_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ガイド"), 0, -1000, 0)
    CALL(evt_mario_set_party_pos, 1, 10, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 35)
    ADD(LW(2), 30)
    CALL(evt_party_move_pos2, 1, LW(0), LW(2), FLOAT(120.0f))
    CALL(evt_msg_print, 0, STRING("mac_1_031"), 0, STRING("extparty"))
    WAIT_MS(200)
    SET_VALUE(GSW(0), 69)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 1)
    RETURN
EVT_END()

EVT_BEGIN(tik03_switch_evt)
    IF_INT_EQUAL(GSWF(1334), 0)
        CALL(evt_map_playanim, STRING("anm_para"), 0, 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kabe_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kabe_2"), 1)
        CALL(evt_hitobj_onoff, STRING("a_para_d"), 1, 0)
        SET_VALUE(GSWF(1334), 1)
        CALL_CHILD(PTR(anm_para_snd))
        WAIT_MS(800)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("para"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("para"), 1)
        CALL(evt_map_playanim, STRING("anm_rapa"), 0, 0)
        SET_VALUE(GSWF(1334), 0)
        CALL_CHILD(PTR(anm_rapa_snd))
        WAIT_MS(800)
        CALL(evt_hitobj_onoff, STRING("a_para_d"), 0, 1)
        CALL(evt_hitobj_onoff, STRING("a_para_d1"), 0, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(tik_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_EQUAL(GSW(0), 66)
        SPAWN_EVENT(PTR(puni_soguu_3))
    END_IF
    IF_INT_LESS_OR_EQUAL(GSW(0), 67)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kabe_2"), 1)
        ELSE
        IF_INT_EQUAL(GSWF(1334), 0)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kabe_1"), 1)
            ELSE
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kabe_1"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("para"), 1)
            CALL(evt_hitobj_onoff, STRING("a_para_d"), 1, 0)
            CALL(evt_hitobj_onoff, STRING("a_para_d1"), 1, 0)
        END_IF
    END_IF
    IF_INT_LESS_OR_EQUAL(GSW(0), 68)
        SPAWN_EVENT(PTR(puni_nakama))
    END_IF
    CALL(evt_item_entry, STRING("item_00"), 276, -450, -50, -50, 16, GSWF(1356), 0)
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 325, -50, 0, STRING("kakoi"), 125, GSWF(5590))
    IF_INT_LESS(GSW(0), 71)
        SET_VALUE(LW(0), STRING("dokan"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("dokan"), PTR(bero_entry_data2))
        SET_VALUE(LW(0), STRING("dokan"))
        CALL_CHILD(PTR(bero_case_switch_on))
    END_IF
    RETURN
EVT_END()

