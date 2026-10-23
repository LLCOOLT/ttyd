#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_hitobj_attr_onoff);
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
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_key_get_buttontrg);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_set_offscreen);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_cam_off);
USER_FUNC(evt_mario_cam_on);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_msg_togelr);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_offscreen_delete);
USER_FUNC(evt_offscreen_entry);
USER_FUNC(evt_offscreen_get_boundingbox);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_move_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_coin);
USER_FUNC(evt_sub_get_system_flag);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_save_playtime);
void gans_msg_callback(s32 type, void** work);
extern s32 bero_case_switch_on[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_item_delete[];
extern s32 evt_npc_jump_position_nohit[];
extern s32 evt_npc_sound_data_reset[];
extern s32 evt_npc_sound_data_set[];
extern s32 evt_pouch_add_coin[];

__declspec(section ".data") u64 fd_tou_05_negone_one_374;
__declspec(section ".data") s32 fd_tou_05_neg_one_382[1];
__declspec(section ".data") s32 fd_tou_05___local_PI_383[1];
__declspec(section ".data") s32 fd_tou_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tou_05_one_negone_373;
__declspec(section ".data") s32 fd_tou_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tou_05_one_381[1];
__declspec(section ".data") u64 fd_tou_05_negone_one_360;
__declspec(section ".data") s32 fd_tou_05_neg_one_365[1];
__declspec(section ".data") s32 fd_tou_05___local_PI_366[1];
__declspec(section ".data") s32 fd_tou_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tou_05_one_negone_359;
__declspec(section ".data") s32 fd_tou_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tou_05_one_364[1];
static s32 evt_dakuto[90];
static __declspec(section ".data") s32 n_door_open[12];
static __declspec(section ".data") s32 n_door_close[12];
s32 n_bero_match_reset[14];
static s32 bero_data[45];
s32 evt_takurami[352];
s32 evt_hiki_close[86];
s32 evt_hiki_open[193];
static s32 init_gans[29];
static s32 talk_gans[182];
static s32 init_kinoshikowa[18];
static s32 talk_kinoshikowa[386];
static s32 npcEnt[69];
static s32 evt_kinoshikowa[222];
static s32 evt_sensyu[430];
s32 evt_sensyu2[208];
static s32 evt_1st_leagu[467];
s32 evt_nozoki_msg[33];
s32 evt_nozoki[769];
s32 evt_sensyu_reentry[293];
s32 tou_05_init_evt[445];

__declspec(section ".data") u64 fd_tou_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tou_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_05_one_364[] = {
    1065353216,
};

static EVT_BEGIN(evt_dakuto)
    CALL(evt_mario_normalize)
    CALL(evt_mario_set_pos, -160, 85, -65)
    CALL(evt_party_set_pos, 0, -160, 85, -70)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_seq_wait, 2)
        IF_INT_EQUAL(GSWF(2401), 0)
            CALL(evt_mapobj_get_position, STRING("haikikau_2"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DUCT_KOUSHI_FALL1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("haikikau_2"), 1)
            CALL(evt_hitobj_onoff, STRING("a_haikikan"), 1, 1)
            WAIT_MS(300)
        END_IF
        CALL(evt_mario_mov_pos, -130, -65, 500)
        CALL(evt_party_move_pos, 0, -130, -70, 500)
        IF_INT_EQUAL(GSWF(2401), 0)
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_msg_print_party, STRING("stg3_tou_456"))
            WAIT_MS(300)
            CALL(evt_party_run, 0)
            SET_VALUE(GSWF(2401), 1)
        END_IF
        CALL(evt_mario_key_onoff, 1)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(n_bero_match_reset)
    IF_INT_EQUAL(GSWF(2388), 1)
        DEBUG_PUT_MSG(STRING("登録していた試合をリセット"))
    END_IF
    SET_VALUE(GSWF(2388), 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"n_bero", 65540, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)n_bero_match_reset, (s32)"tou_04", (s32)"s_bero_5", 327685, (s32)n_door_close, (s32)n_door_open, (s32)"w_bero",
    0, 20000, 100000, 0, 0, -1, (s32)evt_dakuto, -1,
    0, (s32)"tou_13", (s32)"w_bero_", 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_takurami)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print_party, STRING("stg3_tou_456_01"))
    CALL(evt_party_stop, 0)
    CALL(evt_party_move_pos2, 0, 100, 60, FLOAT(60.0f))
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_pose, STRING("M_L_2"))
    WAIT_MS(3000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kami_2"), 1)
    CALL(evt_msg_print_party, STRING("stg3_tou_458"))
    WAIT_MS(300)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_npc_set_position, STRING("ガンス"), 0, 0, -160)
    CALL(evt_npc_flag_onoff, 1, STRING("ガンス"), 32768)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(n_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_flag_onoff, 0, STRING("ガンス"), 32768)
    CALL(evt_npc_move_position, STRING("ガンス"), 0, -80, 0, FLOAT(80.0f), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(800)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 82, 150, 0, 37, -112, 500, 11)
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, 0, STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_459"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_mario_set_pos, 130, 0, 44)
    CALL(evt_party_set_pos, 0, 78, 0, 85)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_cam3d_evt_set, 115, 74, 296, 115, 35, 74, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_460"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 82, 150, 0, 37, -112, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_461"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_npc_move_position, STRING("ガンス"), 0, -130, 0, FLOAT(100.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(n_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ガンス"), 0, -200, 0, FLOAT(100.0f), 1)
        CALL(evt_npc_set_position, STRING("ガンス"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(n_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print_party, STRING("stg3_tou_462"))
    WAIT_MS(300)
    SET_VALUE(GSW(0), 163)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(PTR(bero_case_switch_on))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_hiki_close)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_2"), 1)
    CALL(evt_mapobj_get_position, LW(0), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DRAWER_SHUT1"), LW(10), LW(11), LW(12), 0)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(9), LW(1))
    CALL(evt_sub_intpl_msec_init, 11, 100, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, LW(8), 0, 0, LW(0))
        CALL(evt_hit_bind_update, LW(9))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(LW(0), LW(8))
    SET_VALUE(LW(1), LW(9))
    CALL(evt_run_case_evt, 9, 1, LW(1), 0, PTR(evt_hiki_open), 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(evt_hiki_open)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    IF_STR_EQUAL(LW(0), STRING("hikidasi_H"))
        IF_INT_LESS(GSW(0), 163)
            BEGIN_INLINE_EVENT
                CALL(evt_party_stop, 0)
                WAIT_MS(100)
                CALL(evt_party_move_pos2, 0, 120, 65, FLOAT(60.0f))
                CALL(evt_party_stop, 0)
                WAIT_MS(100)
                CALL(evt_party_move_pos2, 0, 85, 55, FLOAT(60.0f))
                CALL(evt_party_set_dir, 0, 90, 300)
            END_INLINE_EVENT
        END_IF
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), 20)
        CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
    CALL(evt_mapobj_get_position, LW(0), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DRAWER_OPEN1"), LW(10), LW(11), LW(12), 0)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(9), LW(1))
    CALL(evt_sub_intpl_msec_init, 11, 0, 100, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, LW(8), 0, 0, LW(0))
        CALL(evt_hit_bind_update, LW(9))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(LW(0), LW(8))
    SET_VALUE(LW(1), LW(9))
    CALL(evt_run_case_evt, 10, 1, LW(1), 0, PTR(evt_hiki_close), 0)
    IF_STR_EQUAL(LW(0), STRING("hikidasi_H"))
        IF_INT_LESS(GSW(0), 163)
            CALL_CHILD(PTR(evt_takurami))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_party_run, 0)
            CALL(evt_cam_letter_box_disable, 0)
            CALL(evt_exit_case_evt)
            RETURN
        END_IF
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hikidasi_N"))
        IF_INT_EQUAL(GSWF(2508), 0)
            CALL(evt_item_entry, STRING("item02"), 125, 0, -1000, 0, 16, -1, 0)
            CALL(evt_item_get_item, STRING("item02"))
            SET_VALUE(GSWF(2508), 1)
            SET_VALUE(GSWF(5625), 1)
        END_IF
    END_IF
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_cam_letter_box_disable, 0)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(init_gans)
    SWITCH(GSW(0))
        CASE_LESS(130)
        CALL(evt_npc_set_position, STRING("me"), 120, 0, 0)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        CASE_LESS(131)
        CALL(evt_npc_set_position, STRING("me"), 120, 0, 0)
        CALL(evt_npc_set_ry, STRING("me"), 270)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_gans)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_54"), 0, STRING("ガンス"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_52_yn"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("stg3_tou_53"))
        ELSE
        CALL(evt_msg_continue)
        CALL(evt_fade_entry, 10, 500, 0, 0, 0)
        WAIT_MS(500)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kami_1"), 1)
        CALL(evt_mario_set_pos, 20, 0, 0)
        CALL(evt_party_set_pos, 0, 0, 0, -30)
        CALL(evt_npc_set_position, STRING("ガンス"), 120, 0, 0)
        CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
        CALL(evt_mario_set_dir_npc, STRING("ガンス"))
        CALL(evt_party_set_dir_npc, 0, STRING("ガンス"))
        CALL(evt_cam3d_evt_set, 70, 113, 386, 70, 45, -8, 0, 11)
        WAIT_MS(1000)
        CALL(evt_fade_entry, 9, 500, 0, 0, 0)
        WAIT_MS(500)
        CALL(evt_msg_print, 0, STRING("stg3_tou_55"), 0, 0)
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_55_01"), 0, STRING("ガンス"))
        WAIT_MS(300)
        SET_VALUE(GW(10), 0)
        BEGIN_INLINE_EVENT
            LOOP(0)
                IF_INT_GREATER(GW(10), 2)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_5B"))
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_I_G"))
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
        END_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg3_tou_56"), PTR(gans_msg_callback), STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_eff_fukidashi, 0, STRING("a"), 0, 4, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
        SET_VALUE(GSW(0), 130)
        CALL_CHILD(PTR(evt_kinoshikowa))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_kinoshikowa)
    SWITCH(GSW(0))
        CASE_LESS(164)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("キノシコワ"), 127, 0, 7)
        CALL(evt_npc_set_ry, STRING("キノシコワ"), 270)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_kinoshikowa)
    IF_INT_EQUAL(GSW(1420), 13)
        CALL(evt_pouch_check_item, 107, LW(0))
        IF_INT_EQUAL(GSWF(5406), 0)
            IF_INT_EQUAL(LW(0), 20)
                IF_INT_EQUAL(GSWF(5405), 0)
                    CALL(evt_msg_print, 0, STRING("irai_13_03_b"), 0, 0)
                    SET_VALUE(GSWF(5405), 1)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("irai_13_04"), 0, 0)
                END_IF
                SET_VALUE(GSWF(5406), 1)
                ELSE
                IF_INT_EQUAL(GSWF(5405), 0)
                    CALL(evt_msg_print, 0, STRING("irai_13_00"), 0, 0)
                    SET_VALUE(GSWF(5405), 1)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("irai_13_02"), 0, 0)
                END_IF
            END_IF
            ELSE
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print, 0, STRING("irai_13_03"), 0, 0)
                CALL(evt_sub_get_coin, 30)
                CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
                WAIT_MS(200)
                CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
                WAIT_MS(200)
                CALL(evt_msg_print, 0, STRING("irai_13_05"), 0, 0)
                CALL(evt_sub_save_playtime, GSW(1437))
                SET_VALUE(GSW(1420), 0)
                SET_VALUE(GSWF(5387), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
                ELSE
                CALL(evt_msg_print, 0, STRING("irai_13_04"), 0, 0)
            END_IF
        END_IF
        RETURN
    END_IF
    IF_INT_EQUAL(GSW(1420), 23)
        CALL(evt_pouch_check_item, 99, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_msg_print, 0, STRING("irai_23_03"), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("irai_23_00"), 0, 0)
            CALL(evt_mario_set_pose, STRING("M_N_3"))
            WAIT_MS(500)
            CALL(evt_mario_set_pose, STRING("M_I_2"))
            WAIT_MS(1000)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_msg_print, 0, STRING("irai_23_01"), 0, 0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32)
            CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
            BEGIN_INLINE_EVENT
                WAIT_MS(800)
                CALL(evt_cam3d_evt_set, -51, 121, 485, -51, 45, -9, 1800, 11)
            END_INLINE_EVENT
            IF_INT_GREATER(LW(2), LW(5))
                SET_VALUE(LF(0), 0)
                CALL(evt_npc_move_position, STRING("me"), 120, -70, 0, 80, 0)
                CALL(evt_npc_move_position, STRING("me"), 30, -70, 0, 80, 0)
                ELSE
                SET_VALUE(LF(0), 1)
                CALL(evt_npc_move_position, STRING("me"), 120, 65, 0, 80, 0)
                CALL(evt_npc_move_position, STRING("me"), 30, 60, 0, 80, 0)
            END_IF
            CALL(evt_npc_move_position, STRING("me"), -108, -85, 0, 80, 0)
            WAIT_MS(500)
            CALL(evt_cam3d_evt_off, 1800, 11)
            IF_INT_EQUAL(LF(0), 0)
                CALL(evt_npc_move_position, STRING("me"), 30, -70, 0, 80, 0)
                CALL(evt_npc_move_position, STRING("me"), 127, -70, 0, 80, 0)
                CALL(evt_npc_move_position, STRING("me"), 127, 0, 0, 80, 0)
                ELSE
                CALL(evt_npc_move_position, STRING("me"), 30, 60, 0, 80, 0)
                CALL(evt_npc_move_position, STRING("me"), 127, 65, 0, 80, 0)
                CALL(evt_npc_move_position, STRING("me"), 127, 10, 0, 80, 0)
            END_IF
            CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
            WAIT_FRAMES(1)
            CALL(evt_npc_wait_pera, STRING("me"))
            WAIT_MS(300)
            CALL(evt_npc_flag_onoff, 0, STRING("me"), 32)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_msg_print, 0, STRING("irai_23_02"), 0, 0)
            CALL(evt_item_entry, STRING("pm"), 99, 0, -1000, 0, 17, -1, 0)
            CALL(evt_item_get_item, STRING("pm"))
            CALL(evt_item_get_item_end_wait, STRING("pm"))
            CALL(evt_npc_set_ry, STRING("me"), 270)
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(164)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_tou_re_008"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 1073743360, 0, (s32)init_gans, 0, (s32)talk_gans, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F",
    1073743360, 0, (s32)init_kinoshikowa, 0, (s32)talk_kinoshikowa, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_kinoshikowa)
    CALL(evt_msg_print, 0, STRING("stg3_tou_57"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, 0, -180)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(n_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 1, -70, 0, FLOAT(50.0f), 1)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 35, -75, 0, FLOAT(50.0f), 1)
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(600)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
    CALL(evt_mario_set_dir_npc, STRING("ガンス"))
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ガンス"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_58"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_59"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg3_tou_60"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_mario_set_dir_npc, STRING("キノシコワ"))
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_61"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(600)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_mov_pos, 0, -200, 3000)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -120, 0, FLOAT(50.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(n_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(50.0f), 1)
        CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(GSWF(2376), 1)
    CALL(evt_bero_mapchange, STRING("tou_04"), 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_sensyu)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envoff, 512)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG3_GANCE1"))
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("ガンス"))
    CALL(evt_eff_fukidashi, 1, STRING("eff"), STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg3_tou_43"), 0, STRING("ガンス"))
    CALL(evt_cam3d_evt_set, 75, 114, 386, 75, 45, -8, 1000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 0, -30, FLOAT(60.0f))
        CALL(evt_party_set_dir_npc, 0, STRING("ガンス"))
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 20, 0, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_44"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_45"), 0, STRING("ガンス"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_45_yn"))
    CALL(evt_msg_print_add, 0, STRING("stg3_tou_46_00"))
    CALL(evt_npc_flag_onoff, 1, STRING("ガンス"), 32)
    CALL(evt_npc_status_onoff, 1, STRING("ガンス"), 2)
    CALL(evt_npc_move_position, STRING("ガンス"), 120, -70, 0, FLOAT(50.0f), 1)
    CALL(evt_cam3d_evt_set, -30, 114, 386, -30, 45, -8, 2000, 11)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_get_position, STRING("ガンス"), LW(0), LW(1), LW(2))
            CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
            IF_INT_LESS(LW(0), LW(3))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("ガンス"), -45, -70, 0, FLOAT(50.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_46_00_01"), 0, STRING("ガンス"))
    CALL(evt_npc_move_position, STRING("ガンス"), -45, 0, 0, FLOAT(50.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_46_01"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -40, 97, 287, -40, 45, -8, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_46_02"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -40, 80, 189, -40, 45, -8, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_46_03"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_cam3d_evt_set, -15, 80, 189, -15, 45, -8, 300, 11)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(300)
    LOOP(2)
        CALL(evt_mario_set_dir, 90, 200, 0)
        WAIT_MS(250)
        CALL(evt_mario_set_dir, 270, 200, 0)
        WAIT_MS(250)
    END_LOOP
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 140, 534, 0, 45, -80, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_47"), 0, STRING("ガンス"))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ガンス"), -10, -120, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("ガンス"), 10, -120, 0, FLOAT(80.0f), 1)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_open_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_npc_move_position, STRING("ガンス"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("ガンス"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 0, -200, FLOAT(60.0f))
    END_INLINE_EVENT
    WAIT_MS(1000)
    SET_VALUE(GSWF(2375), 1)
    CALL(evt_bero_mapchange, STRING("tou_04"), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_sensyu2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, 20, 0, 0)
    CALL(evt_party_set_pos, 0, 0, 0, -30)
    CALL(evt_npc_set_position, STRING("ガンス"), 120, 0, 0)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("ガンス"))
    CALL(evt_party_set_dir_npc, 0, STRING("ガンス"))
    CALL(evt_cam3d_evt_set, 70, 113, 386, 70, 45, -8, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG3_GANCE1"))
    CALL(evt_snd_envoff, 512)
    CALL(evt_msg_print, 0, STRING("stg3_tou_51"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_eff_fukidashi, 1, STRING("eff"), STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kami_1"), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_52"), 0, STRING("ガンス"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_52_yn"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("stg3_tou_53"))
        CALL(evt_run_case_evt, 9, 1, STRING("a_p_tukue"), 0, PTR(talk_gans), 0)
        SET_VALUE(GSW(0), 130)
        ELSE
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("stg3_tou_55"), 0, 0)
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_55_01"), 0, STRING("ガンス"))
        WAIT_MS(300)
        SET_VALUE(GW(10), 0)
        BEGIN_INLINE_EVENT
            LOOP(0)
                IF_INT_GREATER(GW(10), 2)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_5B"))
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_I_G"))
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
        END_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg3_tou_56"), PTR(gans_msg_callback), STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_eff_fukidashi, 0, STRING("a"), 0, 4, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
        SET_VALUE(GSW(0), 131)
        CALL_CHILD(PTR(evt_kinoshikowa))
    END_IF
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 evt_1st_leagu[] = {
    131163, (s32)evt_mario_key_onoff, 0, 131163, (s32)evt_party_stop, 0, 327771, (s32)evt_npc_set_position,
    (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 0, 0, -160, 262235, (s32)evt_mario_set_pos, 0, 0,
    -165, 327771, (s32)evt_party_set_pos, 0, 0, 0, -180, 262235,
    (s32)evt_mario_set_dir, 90, 0, 0, 262235, (s32)evt_party_set_dir, 0, 90,
    0, 327771, (s32)evt_npc_set_position, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 125, 0, 25, 196699,
    (s32)evt_set_dir_to_target, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", (s32)"mario", 393307, (s32)evt_mapobj_trans, 1, (s32)"hikidasi_H", 0,
    0, 10, 589915, (s32)evt_cam3d_evt_set, 75, 100, 371, 75,
    37, 13, 0, 11, 131163, (s32)evt_seq_wait, 2, 65546,
    1000, 65546, 3000, 131122, -29999999, 0, 65628, (s32)bero_open_door_play_se,
    327771, (s32)evt_sub_intpl_msec_init, 11, 0, -180, 500, 65541, 0,
    65627, (s32)evt_sub_intpl_msec_get_value, 65630, (s32)n_door_open, 131096, -29999999, 0, 7,
    33, 6, 131122, -90000000, 0, 107, 262235, (s32)evt_npc_status_onoff,
    1, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 2, 458843, (s32)evt_npc_move_position, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 1, -100,
    0, -229948800, 1, 458843, (s32)evt_npc_move_position, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 50, -100,
    0, -229948800, 1, 131122, -90000000, 1, 109, 107,
    65546, 1200, 327771, (s32)evt_party_move_pos2, 0, -20, -30, -229938560,
    131163, (s32)evt_party_stop, 0, 327771, (s32)evt_party_move_pos2, 0, -50, -30,
    -229938560, 131163, (s32)evt_party_stop, 0, 262235, (s32)evt_party_set_dir, 0, 90,
    200, 109, 107, 65546, 800, 262235, (s32)evt_mario_mov_pos2, -10,
    -20, -229938560, 262235, (s32)evt_mario_set_dir, 90, 200, 0, 131122,
    -29999999, 0, 65628, (s32)bero_close_door_play_se, 327771, (s32)evt_sub_intpl_msec_init, 11, -180,
    0, 500, 65541, 0, 65627, (s32)evt_sub_intpl_msec_get_value, 65630, (s32)n_door_open,
    131096, -29999999, 0, 7, 33, 6, 109, 786523,
    (s32)evt_eff_fukidashi, 1, 0, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 0, 0, 0, 0,
    0, 0, 0, 0, 327771, (s32)evt_npc_get_position, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", -30000000,
    -29999999, -29999998, 458843, (s32)evt_npc_sound_data_set, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", -250000000, -250000000, -250000000,
    0, -250000000, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", -30000000, -29999999, -29999998,
    300, 20, 131163, (s32)evt_npc_sound_data_reset, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 327771, (s32)evt_mapobj_flag_onoff, 1,
    1, (s32)"kami_2", 1, 65546, 300, 131122, -30000000, (s32)"hikidasi_H",
    131122, -29999999, (s32)"a_hikidasi_H", 65630, (s32)evt_hiki_close, 65541, 0, 131096,
    -90000000, 1, 7, 33, 65545, 1, 6, 196699,
    (s32)evt_set_dir_to_target, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_287", 0,
    (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 65546, 300, 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_288", 0,
    (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 65546, 300, 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_289", 0,
    (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 65546, 300, 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_290", 0,
    (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 65546, 300, 589915, (s32)evt_cam3d_evt_set, 15, 90, 269,
    15, 37, -26, 4000, 11, 107, 458843, (s32)evt_npc_move_position,
    (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 70, -100, 0, -229948800, 1, 196699, (s32)evt_set_dir_to_target,
    (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", (s32)"mario", 109, 262235, (s32)evt_npc_status_onoff, 1, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 2,
    458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 110, 85, 0, -229948800, 1,
    458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 25, 50, 0, -229948800, 1,
    458843, (s32)evt_npc_move_position, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 25, -10, 0, -229948800, 1,
    196699, (s32)evt_set_dir_to_target, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", (s32)"mario", 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_291",
    0, (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 65546, 300, 131163, (s32)evt_pouch_add_coin, 30, 131163,
    (s32)evt_mario_set_pose, (s32)"M_I_U", 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998,
    131125, -29999999, 50, 589915, (s32)evt_item_entry, (s32)"coin", 121, -30000000,
    -29999999, -29999998, 17, -1, 0, 65546, 1000, 131163,
    (s32)evt_item_delete, (s32)"coin", 131163, (s32)evt_mario_set_pose, (s32)"M_S_1", 327771, (s32)evt_msg_print, 0,
    (s32)"stg3_tou_292_02", 0, 0, 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_292", 0,
    (s32)/*"ガンス"*/"\x83\x4B\x83\x93\x83\x58", 65546, 300, 327771, (s32)evt_msg_print, 0, (s32)"stg3_tou_293", 0,
    (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 65546, 300, 458843, (s32)evt_npc_move_position, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 0, -100,
    0, -229948800, 1, 131122, -29999999, 0, 65628, (s32)bero_open_door_play_se,
    327771, (s32)evt_sub_intpl_msec_init, 11, 0, 180, 500, 65541, 0,
    65627, (s32)evt_sub_intpl_msec_get_value, 65630, (s32)n_door_open, 131096, -29999999, 0, 7,
    33, 6, 107, 458843, (s32)evt_npc_move_position, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 0, -200,
    0, -229948800, 1, 327771, (s32)evt_npc_set_position, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 0, -1000,
    0, 109, 131163, (s32)evt_party_run, 0, 262235, (s32)evt_mario_mov_pos2, 0,
    -200, -229938560, 131122, -129997623, 1, 196699, (s32)evt_bero_mapchange, (s32)"tou_04",
    0, 2, 1,
};

EVT_BEGIN(evt_nozoki_msg)
    LOOP(0)
        CALL(evt_msg_toge, 2, -50, 100, 0)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_03"), 0, 0)
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 50, 100, 0)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_04"), 0, 0)
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_nozoki)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    IF_INT_LESS(GSW(0), 152)
        DELETE_EVENT(GW(9))
        CALL(evt_npc_set_position, STRING("ガンス"), 120, 0, 0)
        CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("キノシコワ"))
        CALL(evt_npc_set_position, STRING("キノシコワ"), 20, 0, 0)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ガンス"))
        CALL(evt_npc_flag_onoff, 1, STRING("ガンス"), 32)
        CALL(evt_npc_status_onoff, 1, STRING("ガンス"), 2)
        CALL(evt_npc_flag_onoff, 1, STRING("キノシコワ"), 32)
        CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
    END_IF
    CALL(evt_cam3d_evt_set, 0, 145, 534, 0, 50, -8, 2000, 11)
    WAIT_MS(2000)
    CALL(evt_paper_entry, STRING("OFF_d_meku"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_meku"))
    CALL(evt_offscreen_entry, STRING("ofs"))
    CALL(evt_mapobj_set_offscreen, 1, STRING("kuro_P"), STRING("ofs"))
    CALL(evt_offscreen_get_boundingbox, STRING("ofs"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_free_capture, STRING("img"), 0)
    CALL(evt_img_free_capture, STRING("img"), 1)
    CALL(evt_img_free_capture, STRING("img"), 2)
    CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("ofs"), 0, LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, STRING("img"), 2, STRING("ofs"), 0, LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_clear_virtual_point, STRING("img"))
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_img_onoff, STRING("img"), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF3_VIEW_ROOM1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kuro_P"), 1)
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_onoff, STRING("img"), 0)
    IF_INT_LESS(GSW(0), 152)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_05"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_06"), 0, STRING("キノシコワ"))
        WAIT_MS(300)
        CALL(evt_cam3d_evt_set, 70, 114, 386, 70, 45, -8, 1200, 11)
        WAIT_MS(1200)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_07"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_08"), 0, STRING("キノシコワ"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_09"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_10"), 0, STRING("キノシコワ"))
        WAIT_MS(300)
        CALL(evt_cam3d_evt_set, 0, 145, 534, 0, 50, -8, 1000, 11)
        WAIT_MS(1000)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_11"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_12"), 0, STRING("キノシコワ"))
        WAIT_MS(300)
        CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
        WAIT_MS(600)
        CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, 0, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ガンス"))
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_13"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_14"), 0, STRING("キノシコワ"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_15"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_16"), 0, STRING("キノシコワ"))
        WAIT_MS(300)
        CALL(evt_msg_print, 0, STRING("stg3_tou_316_17"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -120, 0, FLOAT(80.0f), 1)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_open_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        BEGIN_INLINE_EVENT
            CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(80.0f), 1)
            CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
        END_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_msg_print, 0, STRING("stg3_tou_320"), 0, STRING("ガンス"))
        WAIT_MS(300)
        CALL(evt_mario_set_pos, -20, 150, 0)
        CALL(evt_mario_set_dir, 90, 0, 0)
        CALL(evt_party_set_pos, 0, 20, 150, 0)
        CALL(evt_party_set_dir, 0, 270, -1)
        CALL(evt_party_stop, 0)
        CALL(evt_cam3d_evt_set, 0, 210, 345, 0, 185, -4, 2000, 11)
        WAIT_MS(2000)
        CALL(evt_msg_print_party, STRING("stg3_tou_321"))
        WAIT_MS(300)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(500)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_cam3d_evt_set, 100, 114, 386, 100, 45, -8, 0, 11)
        WAIT_FRAMES(1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_322"), 0, STRING("ガンス"))
        CALL(evt_msg_select, 0, STRING("stg3_tou_322_yn"))
        CALL(evt_msg_continue)
        CALL(evt_msg_toge, 2, 100, 120, 0)
        CALL(evt_msg_togelr, 2)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_323_kur"), 0, 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_325"), 0, STRING("ガンス"))
            CASE_EQUAL(1)
            CALL(evt_msg_print, 0, STRING("stg3_tou_324_kur"), 0, 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_325_01"), 0, STRING("ガンス"))
            CASE_EQUAL(2)
            CALL(evt_msg_print, 0, STRING("stg3_tou_324_01_kur"), 0, 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_325_02"), 0, STRING("ガンス"))
        END_SWITCH
        CALL(evt_cam3d_evt_set, 0, 145, 534, 0, 50, -8, 1000, 11)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING("ガンス"), 115, -80, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("ガンス"), 0, -120, 0, FLOAT(80.0f), 1)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_open_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        BEGIN_INLINE_EVENT
            CALL(evt_npc_move_position, STRING("ガンス"), 0, -200, 0, FLOAT(80.0f), 1)
            CALL(evt_npc_set_position, STRING("ガンス"), 0, -1000, 0)
        END_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(n_door_open))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        WAIT_MS(500)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_OFF3_VIEW_ROOM2"), LW(0), LW(1), LW(2), 0)
        END_INLINE_EVENT
        CALL(evt_img_onoff, STRING("img"), 1)
        CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_2"))
        CALL(evt_img_wait_animend, STRING("img"))
        CALL(evt_img_onoff, STRING("img"), 0)
        CALL(evt_mapobj_clear_offscreen, 1, STRING("kuro_P"))
        CALL(evt_img_release, STRING("img"))
        CALL(evt_offscreen_delete, STRING("ofs"))
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kuro_P"), 1)
        CALL(evt_cam3d_evt_set, 0, 210, 345, 0, 185, -4, 1000, 11)
        WAIT_MS(1000)
        CALL(evt_msg_print_party, STRING("stg3_tou_326"))
        WAIT_MS(300)
        SET_VALUE(GSW(0), 152)
        ELSE
        LOOP(0)
            CALL(evt_key_get_buttontrg, 0, LW(0))
            IF_BITS_SET(LW(0), 256)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_OFF3_VIEW_ROOM2"), LW(0), LW(1), LW(2), 0)
        END_INLINE_EVENT
        CALL(evt_img_onoff, STRING("img"), 1)
        CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_2"))
        CALL(evt_img_wait_animend, STRING("img"))
        CALL(evt_img_onoff, STRING("img"), 0)
        CALL(evt_mapobj_clear_offscreen, 1, STRING("kuro_P"))
        CALL(evt_img_release, STRING("img"))
        CALL(evt_offscreen_delete, STRING("ofs"))
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kuro_P"), 1)
    END_IF
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_sensyu_reentry)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("キノシコワ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_003"), 0, STRING("キノシコワ"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_004"), 0, STRING("キノシコワ"))
    CALL(evt_cam3d_evt_set, 31, 105, 315, 31, 55, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 115, -75, 0, FLOAT(70.0f), 0)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 40, -80, 0, FLOAT(70.0f), 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_005"), 0, STRING("キノシコワ"))
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_005_1"), 0, STRING("キノシコワ"))
    CALL(evt_cam3d_evt_set, 111, 105, 310, 111, 55, -14, 2000, 11)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 115, -75, 0, FLOAT(70.0f), 0)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 120, 0, 0, FLOAT(70.0f), 0)
    CALL(evt_npc_set_ry, STRING("キノシコワ"), 270)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_005_1_1"), 0, STRING("キノシコワ"))
    WAIT_MS(800)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("キノシコワ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    CALL(evt_cam3d_evt_set, 65, 104, 335, 65, 55, 12, 2000, 11)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 115, -75, 0, FLOAT(70.0f), 0)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 40, -80, 0, FLOAT(70.0f), 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_005_2"), 0, STRING("キノシコワ"))
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 300, 1, 10)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_005_3"), 0, STRING("キノシコワ"))
    CALL(evt_mario_set_pose, STRING("M_N_B"))
    WAIT_MS(600)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_006"), 0, STRING("キノシコワ"))
    CALL(evt_cam3d_evt_set, 111, 105, 310, 111, 55, -14, 2000, 11)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 115, -75, 0, FLOAT(70.0f), 0)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 127, 0, 0, FLOAT(70.0f), 0)
    CALL(evt_npc_set_ry, STRING("キノシコワ"), 270)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_re_007"), 0, STRING("キノシコワ"))
    SET_VALUE(GSWF(2500), 1)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(tou_05_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_map_playanim, STRING("anm_camera"), 1, 0)
    CALL(evt_item_entry, STRING("item01"), 125, -135, 0, 105, 16, GSWF(5624), 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("paifu"), 2)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("fall"))
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mario_set_pos, -775, 150, 10)
        CALL(evt_party_set_pos, 0, -800, 150, 0)
        CALL(evt_cam_road_reset)
        CALL(evt_mario_cam_off)
        CALL(evt_mario_set_pos, -775, 250, 10)
        CALL(evt_party_set_pos, 0, -800, 250, 0)
        CALL(evt_mario_cont_onoff, 0)
        CALL(evt_party_cont_onoff, 0, 0)
        BEGIN_INLINE_EVENT
            CALL(evt_seq_wait, 2)
            WAIT_MS(500)
            CALL(evt_mario_cont_onoff, 1)
            CALL(evt_mario_wait_landon)
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_mario_cam_on)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_seq_wait, 2)
            WAIT_MS(800)
            CALL(evt_party_cont_onoff, 0, 1)
        END_INLINE_EVENT
    END_IF
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("fall"))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kuro_Y"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kuro_P"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kuro_Y"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kuro_P"), 1)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 162)
        SET_VALUE(LW(0), STRING("hikidasi_N"))
        SET_VALUE(LW(1), STRING("a_hikidasi_N"))
        CALL(evt_hit_bind_mapobj, LW(1), LW(0))
        CALL(evt_run_case_evt, 9, 1, LW(1), 0, PTR(evt_hiki_open), 0)
        SET_VALUE(LW(0), STRING("hikidasi_H"))
        SET_VALUE(LW(1), STRING("a_hikidasi_H"))
        CALL(evt_hit_bind_mapobj, LW(1), LW(0))
        CALL(evt_run_case_evt, 9, 1, LW(1), 0, PTR(evt_hiki_open), 0)
    END_IF
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_EQUAL(GSW(0), 130)
        CALL(evt_run_case_evt, 9, 1, STRING("a_p_tukue"), 0, PTR(talk_gans), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_1"), 1)
    END_IF
    IF_INT_LESS(GSW(0), 152)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("fall"))
            SPAWN_EVENT_GET_ID(PTR(evt_nozoki_msg), GW(9))
        END_IF
    END_IF
    CALL(evt_run_case_evt, 5, 1, STRING("a_nozoki"), 0, PTR(evt_nozoki), 0)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("fall"))
        BEGIN_INLINE_EVENT
            LOOP(0)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                IF_INT_LESS(LW(1), 140)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_bero_mapchange, STRING("tou_06"), STRING("fall"))
        END_INLINE_EVENT
    END_IF
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 2)
        RETURN
    END_IF
    SET_VALUE(LW(0), 0)
    IF_INT_LESS(GSW(0), 130)
        SET_VALUE(LW(0), 1)
        IF_INT_EQUAL(GSWF(2375), 0)
            SPAWN_EVENT(PTR(evt_sensyu))
            ELSE
            SET_VALUE(GSWF(2375), 0)
            SPAWN_EVENT(PTR(evt_sensyu2))
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(2393), 1)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG3_GANCE1"))
        CALL(evt_snd_envoff, 512)
        SET_VALUE(LW(0), 1)
        SPAWN_EVENT(PTR(evt_1st_leagu))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kami_2"), 1)
    END_IF
    IF_INT_EQUAL(GSW(0), 163)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envoff, 512)
        ELSE
        IF_INT_EQUAL(LW(0), 0)
            SWITCH(GSW(0))
                CASE_BETWEEN(127, 137)
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU2"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU6"))
                CALL(evt_snd_bgmoff, 26624)
                CASE_GREATER_OR_EQUAL(165)
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU2"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU6"))
                CALL(evt_snd_bgmoff, 26624)
                CASE_DEFAULT
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU1"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU6"))
            END_SWITCH
        END_IF
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(162)
        SET_VALUE(LF(0), 0)
        CASE_LESS(172)
        SET_VALUE(LF(0), 1)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2501), 0)
            SET_VALUE(LF(0), 0)
            ELSE
            SET_VALUE(LF(0), 1)
        END_IF
    END_SWITCH
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("haikikau_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("haikikau_2"), 1)
        CALL(evt_hitobj_onoff, STRING("a_haikikan"), 1, 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("haikikau_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("haikikau_2"), 1)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_NOT_EQUAL(LW(0), STRING("fall"))
            IF_INT_EQUAL(GSWF(2500), 0)
                SPAWN_EVENT(PTR(evt_sensyu_reentry))
            END_IF
        END_IF
    END_IF
    CALL(evt_hitobj_onoff, STRING("haiku_kabe"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("kore\0\0\0"), 1, 0)
    CALL(evt_hitobj_attr_onoff, 1, 1, STRING("w_bero"), 4)
    RETURN
EVT_END()

void gans_msg_callback(s32 type, void** work) {
#ifdef VERSION_G8ME01
    EventEntry* evt = *(EventEntry**)((u8*)*work + 0xF200);
#else
    EventEntry* evt = *(EventEntry**)((u8*)*work + 0x7A00);
#endif
    if (type == 2) {
        evtSetValue(evt, GW(10), evtGetValue(evt, GW(10)) + 1);
    }
}
