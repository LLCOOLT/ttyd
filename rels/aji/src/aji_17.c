#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "mario/mario.h"
#include "string.h"
#include "eff/eff_peach_fukidashi.h"
#include "manager/evtmgr.h"
#include "driver/effdrv.h"
#include "system.h"
#include "mario/mariost.h"
#include "dolphin/os.h"
#include "dolphin/gx.h"
#include "memory.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "dolphin/mtx.h"

typedef struct DanceData { u16 flags; u8 step; u8 movePos; f32 cx; f32 cy; f32 rot; } DanceData;
double sin(double x);
double cos(double x);
typedef struct HorogramWork { void* buf0; void* buf1; GXTexObj tex0; GXTexObj tex1; u16 ready; u16 flags; } HorogramWork;
s32 aji_17_bss_pad;
HorogramWork* horogram_wp;
DanceData dance_dt;
void peach_capture(CameraId cameraId, void* param);
void disp_horogram(CameraId cameraId, void* param);
void noiseDisp(CameraId cameraId, void* param);
int rand(void);

static USER_FUNC(bgm_start_wait);
USER_FUNC(btn_check);
USER_FUNC(compute_horogram_pos);
USER_FUNC(compute_move_pos);
USER_FUNC(compute_peach_pos);
USER_FUNC(dance_data_init);
USER_FUNC(dance_flag_check);
USER_FUNC(dance_flag_onoff);
USER_FUNC(dance_get_step);
USER_FUNC(dance_reverse);
USER_FUNC(disp_horogram_evt);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_eff_softdelete);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_in);
USER_FUNC(evt_fade_out);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_fade_softfocus_onoff);
USER_FUNC(evt_fade_tec_onoff);
USER_FUNC(evt_fuki_btn);
USER_FUNC(evt_fuki_btn_set_batu);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_pauseanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_replayanim);
USER_FUNC(evt_map_set_blend);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_scale);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_adjust_dir);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_dispdir);
USER_FUNC(evt_mario_get_mode);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dispdir);
USER_FUNC(evt_mario_set_mode);
USER_FUNC(evt_mario_set_party);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_set_reardir);
USER_FUNC(evt_mario_wait_move_end);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_pera_onoff);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_autotalkpose);
USER_FUNC(evt_npc_set_color);
USER_FUNC(evt_npc_set_height);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_set_width);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_peach_set_condition);
USER_FUNC(evt_pouch_all_party_recovery);
USER_FUNC(evt_pouch_mario_recovery);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_shuryolight_init_2_text_B870);
USER_FUNC(evt_shuryolight_run_evt_2_text_B538);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_envon_f);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfx_all_stop);
USER_FUNC(evt_snd_sfx_vol);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_stopwatch);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(get_center);
USER_FUNC(get_local_rotate);
USER_FUNC(horogram_cap_evt);
USER_FUNC(horogram_flag_onoff);
USER_FUNC(horogram_init);
USER_FUNC(horogram_set_pose);
USER_FUNC(move_center);
USER_FUNC(noise);
USER_FUNC(peach_dance_after_fail);
USER_FUNC(peach_evt_stg4_read_quiz_data);
static USER_FUNC(peach_set_pose);
USER_FUNC(set_local_rotate);
USER_FUNC(set_npc_pos);
static USER_FUNC(viewport);
USER_FUNC(wait_move_end);
USER_FUNC(wait_action_begin);
USER_FUNC(wait_action_end);
void peach_capture(CameraId cameraId, void* param);
void disp_horogram(CameraId cameraId, void* param);
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 s, f32 t);
void noiseDisp(CameraId cameraId, void* param);
extern s32 bero_case_entry[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_memcard_save[];
extern s32 evt_sub_stopwatch[];
extern s32 npc_init_evt[];
extern s32 shuryolight_head_normal_2_data_37004[];
extern s32 shuryolight_pow_normal_2_data_36ED8[];
extern s32 shuryolight_tue_normal_2_data_37104[];

__declspec(section ".data") u64 fd_aji_17_negone_one_374;
__declspec(section ".data") s32 fd_aji_17_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_17___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_17___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_17_one_negone_373;
__declspec(section ".data") s32 fd_aji_17___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_17_one_381[1];
__declspec(section ".data") u64 fd_aji_17_negone_one_360;
__declspec(section ".data") s32 fd_aji_17_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_17___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_17___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_17_one_negone_359;
__declspec(section ".data") s32 fd_aji_17___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_17_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 bero_entry_data[30];
s32 evt_emergency[48];
s32 evt_last[728];
s32 evt_last2[339];
s32 evt_camera[68];
s32 mail_sousin_se[36];
static s32 peach_evt_stg1[1131];
f32 move_pos_list[15][2];
s32 peach_dance_move[95];
s32 peach_dance_pose[44];
__declspec(section ".data") s32 peach_dance_action_step[2];
s32 dance_action_turn_sub[108];
__declspec(section ".data") s32 peach_dance_action_turn[12];
s32 peach_dance_action_reverse[18];
s32 peach_dance_action_fail[28];
s32 dance_btn_disp_sub[49];
s32 dance_btn_disp[25];
s32 dance_btn_batu[20];
s32 dance_btn_clear[56];
s32 dance_btn_clear_all[47];
s32 wait_action_time[16];
s32 peach_dance_dark[27];
s32 peach_dance_light[27];
s32 peach_evt_dance[504];
static s32 peach_evt_stg2[900];
static s32 peach_evt_stg3[352];
static s32 peach_evt_stg3_1[650];
s32 peach_evt_stg4_quiz_data[5][4];
static s32 peach_evt_stg4[980];
static s32 peach_evt_stg5[408];
static s32 peach_evt_stg5_1[528];
static s32 peach_evt_stg6[1467];
static __declspec(section ".data") s32 teshita1_init[9];
static __declspec(section ".data") s32 teshita2_init[9];
static __declspec(section ".data") s32 syuryo_init[9];
static s32 npcEnt[92];
s32 tec_talk[36];
s32 aji_17_init_evt[253];

USER_FUNC(peach_evt_stg4_read_quiz_data) {
    s32* args = event->args;
    s32 no = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], peach_evt_stg4_quiz_data[no][0]);
    evtSetValue(event, args[2], peach_evt_stg4_quiz_data[no][1]);
    evtSetValue(event, args[3], peach_evt_stg4_quiz_data[no][2]);
    evtSetValue(event, args[4], peach_evt_stg4_quiz_data[no][3]);
    return EVT_RETURN_DONE;
}

BOOL psndBGMStartCheck(s32 id);

static USER_FUNC(bgm_start_wait) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

__declspec(section ".data") u64 fd_aji_17_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_17_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_17___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_17___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_17_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_17___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_17_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_17_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_17_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_17___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_17___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_17_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_17___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_17_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"aji_01", (s32)"e_bero_5", 327685, (s32)w_door_close, (s32)w_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

const GXColor noise_color = {0, 0, 0, 0};

EVT_BEGIN(evt_emergency)
    IF_INT_NOT_EQUAL(GSW(0), 376)
        LOOP(0)
            IF_INT_EQUAL(GSW(0), 376)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, 255, LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_IF
    CALL(evt_map_set_blend, 0, 255, 96, 96, 255)
    RETURN
EVT_END()

EVT_BEGIN(evt_last)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_party_stop, 0)
    WAIT_MS(800)
    CALL(evt_msg_print_party, STRING("stg7_aji_46"))
    WAIT_MS(300)
    LOOP(3)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
        WAIT_MS(100)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kurai"), 1)
        WAIT_MS(100)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING("eff0"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING("eff1"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1600)
        CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_TEC_ACTIVE1"), 0, 0, -120, 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_TEC_ACTIVE1"), 0, 0, -100, 0)
        WAIT_MS(800)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("moni_1"), 0, 0)
    CALL(evt_map_checkanim, STRING("moni_1"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai_0"), 1)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_47"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_fade_tec_onoff, 1, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 20, 20, FLOAT(80.0f))
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -20, 20, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_48"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING("SFX_STG7_TEC_SANDSTORM1"), LW(10))
    CALL(evt_snd_sfx_vol, LW(10), 0)
    SET_VALUE(LF(0), 0)
    LOOP(2)
        CALL(evt_sub_intpl_msec_init, 11, 0, 128, 300)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(noise, LW(0))
        IF_INT_GREATER(LW(0), 127)
            SET_VALUE(LW(0), 127)
        END_IF
        CALL(evt_snd_sfx_vol, LW(10), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            SET_VALUE(LF(0), 1)
            CALL(evt_mario_set_pose, STRING("M_I_2"))
        END_IF
    END_LOOP
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_49"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_50"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 1, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_51"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING("SFX_STG7_TEC_SANDSTORM1"), LW(10))
    CALL(evt_snd_sfx_vol, LW(10), 0)
    LOOP(2)
        CALL(evt_sub_intpl_msec_init, 11, 0, 255, 300)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(noise, LW(0))
        IF_INT_GREATER(LW(0), 127)
            SET_VALUE(LW(0), 127)
        END_IF
        CALL(evt_snd_sfx_vol, LW(10), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_LOOP
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(noise, LW(0))
    IF_INT_GREATER(LW(0), 127)
        SET_VALUE(LW(0), 127)
    END_IF
    CALL(evt_snd_sfx_vol, LW(10), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 0, 128, 300)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(noise, LW(0))
    IF_INT_GREATER(LW(0), 127)
        SET_VALUE(LW(0), 127)
    END_IF
    CALL(evt_snd_sfx_vol, LW(10), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(noise, 255)
    CALL(evt_snd_sfx_vol, LW(10), 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_52"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg7_aji_53"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_54"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pose, STRING("M_I_N"))
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg7_aji_55"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_adjust_dir)
    CALL(evt_fade_tec_onoff, 1, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_56"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("stg7_aji_57"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_bero_mapchange, STRING("aji_16"), STRING("peach"))
    RETURN
EVT_END()

EVT_BEGIN(evt_last2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_mario_set_pos, 20, 0, 20)
    CALL(evt_party_set_pos, 0, -20, 0, 20)
    CALL(evt_cam3d_evt_set, 0, 100, -170, 0, 40, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_reardir)
    CALL(evt_fade_softfocus_onoff, 0)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg7_aji_59"))
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai_0"), 1)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_60"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(300)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
        LABEL(10)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(noise, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(10)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_TEC_SHUTDOWN1"), 0, 0, -100, 0)
    CALL(evt_sub_intpl_msec_init, 2, 0, 239, 200)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(LW(2), 480)
    SUBTRACT(LW(2), LW(0))
    SUBTRACT(LW(2), LW(0))
    CALL(viewport, 0, LW(0), 608, LW(2))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 2, 0, 303, 300)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(LW(2), 608)
    SUBTRACT(LW(2), LW(0))
    SUBTRACT(LW(2), LW(0))
    CALL(viewport, LW(0), 240, LW(2), 1)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(viewport, 0, 0, 1, 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    WAIT_MS(2000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai_0"), 1)
    CALL(evt_mario_set_pos, 20, 0, 35)
    CALL(evt_party_set_pos, 0, -30, 0, 35)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_adjust_dir)
    CALL(evt_cam3d_evt_set, 0, 152, 565, 0, 57, 24, 0, 11)
    WAIT_FRAMES(1)
    CALL(viewport, 0, 0, 608, 480)
    WAIT_MS(300)
    SPAWN_EVENT(PTR(evt_emergency))
    CALL(evt_msg_print, 0, STRING("stg7_aji_61"), 0, 0)
    WAIT_MS(300)
    SET_VALUE(GSW(0), 376)
    CALL(evt_cam3d_evt_set, 0, 92, 320, 0, 40, 24, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg7_aji_62"))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
        IF_FLOAT_NOT_EQUAL(LW(0), LW(3))
            BREAK_LOOP
        END_IF
        IF_FLOAT_NOT_EQUAL(LW(1), LW(4))
            BREAK_LOOP
        END_IF
        IF_FLOAT_NOT_EQUAL(LW(2), LW(5))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_camera)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, LW(6), LW(7), 2000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        WAIT_MS(1000)
        CALL(evt_sub_intpl_msec_init, 11, LW(7), LW(6), 2000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_sousin_se)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_MAIL_SOUSIN1"), 0, 0, -100, 0)
    WAIT_MS(600)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_MAIL_SOUSIN1"), 0, 0, -100, 0)
    WAIT_MS(600)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_MAIL_SOUSIN1"), 0, 0, -100, 0)
    WAIT_MS(900)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_MAIL_SOUSIN2"), 0, 0, -100, 0)
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg1)
    CALL(evt_mario_set_mode, 1)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, -230, 0, 0)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    BEGIN_INLINE_EVENT
        WAIT_MS(800)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -140, 0, 60)
    WAIT_MS(800)
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(300)
    WAIT_MS(500)
    LOOP(3)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
        WAIT_MS(100)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kurai"), 1)
        WAIT_MS(100)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING("eff0"), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(peach_set_pose, STRING("P_S_4"))
    BEGIN_INLINE_EVENT
        WAIT_MS(1600)
        CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_TEC_ACTIVE1"), 0, 0, -120, 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    WAIT_MS(1000)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_TEC_ACTIVE1"), 0, 0, -100, 0)
        WAIT_MS(800)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("moni_1"), 0, 0)
    WAIT_MS(500)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_42"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_4"), STRING("P_T_4"))
    CALL(evt_msg_print, 0, STRING("peach_aji_43"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 450, 0, 105, -150, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 0, 20, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 20, 45, 2700)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos, -30, -68, 2700)
    END_INLINE_EVENT
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_44"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_wait_move_end)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1R"), STRING("P_T_1R"))
    CALL(evt_msg_print, 0, STRING("peach_aji_45"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_48"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(peach_set_pose, STRING("P_S_4"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_4"), STRING("P_T_4"))
    CALL(evt_msg_print, 0, STRING("peach_aji_49"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_50"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_52"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_53"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(peach_set_pose, STRING("P_B_2"))
    WAIT_MS(1200)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
    CALL(evt_msg_print, 0, STRING("peach_aji_53_01"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_54"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_55"), 0, STRING("mario"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_56"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(peach_set_pose, STRING("P_S_4"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_4"), STRING("P_T_4"))
    CALL(evt_msg_print, 0, STRING("peach_aji_57"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 230, 45, 372, 22, 85, -25, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_P_1"), STRING("P_T_9"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_01"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_02"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_S_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_03"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_04"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_05"), 0, STRING("mario"))
    CALL(peach_set_pose, STRING("P_P_1"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_06"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_C_1"), STRING("P_T_8"))
    CALL(evt_msg_print, 0, STRING("peach_aji_58_07"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_65"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_S_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_66"), 0, STRING("mario"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_67"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    CALL(evt_msg_print, 0, STRING("peach_aji_68"), 0, STRING("mario"))
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_KEYBOARD1"), 0, 25, -120, LW(15))
    CALL(peach_set_pose, STRING("P_A_1R"))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING("P_S_1R"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_69"), 0, STRING("mario"))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_meil"), 1)
    CALL(evt_map_playanim, STRING("mel"), 0, 0)
    CALL(evt_map_checkanim, STRING("mel"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_meil"), 1)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_70"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_71"), 0, STRING("mario"))
    WAIT_MS(600)
    CALL(evt_mario_mov_pos, -230, 0, 1200)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_72"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 59)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_aji_17"), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 2)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING("kpa_00"), STRING(""))
    RETURN
EVT_END()

static const GXColor horogram_amb = {0xFF, 0xFF, 0xFF, 0xFF};
static const Vec horogram_pos = {0.0f, 0.0f, 20.0f};
static const Vec horogram_up = {0.0f, 1.0f, 0.0f};
static const Vec horogram_target = {0.0f, 0.0f, 0.0f};

f32 move_pos_list[15][2] = {
    {0.0f, -80.0f},
    {39.37592f, -74.69887f},
    {75.489975f, -58.18756f},
    {102.47971f, -29.07189f},
    {109.125275f, 10.068815f},
    {90.71562f, 45.247093f},
    {58.11264f, 67.92478f},
    {19.846874f, 78.68708f},
    {-19.921722f, 78.67708f},
    {-58.15683f, 67.90478f},
    {-90.7439f, 45.2171f},
    {-109.13224f, 10.028812f},
    {-102.458244f, -29.111893f},
    {-75.446236f, -58.217556f},
    {-39.30409f, -74.71887f},
};

EVT_BEGIN(peach_dance_move)
    CALL(get_center, LW(2), LW(3))
    CALL(compute_move_pos, LW(4), LW(5))
    BEGIN_INLINE_EVENT
        CALL(move_center, LW(2), LW(3), LW(4), LW(5), 600)
    END_INLINE_EVENT
    SET_VALUE(LW(6), LW(5))
    ADD(LW(5), 323)
    ADD(LW(6), 27)
    CALL(evt_cam3d_evt_set, LW(4), 95, LW(5), LW(4), 45, LW(6), 600, 11)
    WAIT_FRAMES(1)
    SPAWN_EVENT(PTR(peach_dance_pose))
    LOOP(0)
        CALL(dance_flag_check, 4, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(get_center, LW(0), LW(1))
        CALL(evt_mario_get_pos, 0, LW(2), LW(4), LW(3))
        CALL(compute_peach_pos, LW(0), LW(1), LW(2), LW(3))
        CALL(evt_mario_set_pos, LW(2), LW(4), LW(3))
        CALL(compute_horogram_pos, LW(0), LW(1), LW(2), LW(3))
        CALL(set_npc_pos, STRING("ホログラム"), LW(2), FLOAT(0.0f), LW(3))
        CALL(set_npc_pos, STRING("ダミー"), LW(0), FLOAT(5.0f), LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_pose)
    CALL(dance_flag_check, 8, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(dance_get_step, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(peach_set_pose, STRING("P_O_F_1"))
        CALL(horogram_set_pose, STRING("P_O_F_2"))
        CASE_EQUAL(1)
        CALL(peach_set_pose, STRING("P_O_R_1"))
        CALL(horogram_set_pose, STRING("P_O_R_2"))
        CASE_EQUAL(2)
        CALL(peach_set_pose, STRING("P_O_N_1"))
        CALL(horogram_set_pose, STRING("P_O_N_2"))
        CASE_DEFAULT
        DEBUG_PUT_MSG(STRING("dance_dt.step error"))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(peach_dance_action_step)
    RETURN
EVT_END()

EVT_BEGIN(dance_action_turn_sub)
    CALL(evt_mario_get_dispdir, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        SET_VALUE(LW(6), 360)
    END_IF
    SET_VALUE(LW(7), LW(6))
    SUBTRACT(LW(7), 180)
    CALL(get_local_rotate, LW(8))
    SET_FLOAT_VALUE(LW(9), LW(8))
    ADD_FLOAT(LW(9), FLOAT(3.140625f))
    MULTIPLY_FLOAT(LW(8), FLOAT(1000.0f))
    MULTIPLY_FLOAT(LW(9), FLOAT(1000.0f))
    CALL(evt_npc_get_position, STRING("ホログラム"), LW(2), LW(0), LW(3))
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_DANCE_TURN1"), LW(2), 0, LW(3), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, LW(6), LW(7), 400)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        SET_VALUE(LW(2), 360)
        SUBTRACT(LW(2), LW(0))
        CALL(evt_npc_set_ry, STRING("ホログラム"), LW(2))
        CALL(evt_mario_set_dir, LW(0), 0, 0)
        CALL(evt_mario_set_dispdir, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(9), 400)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(set_local_rotate, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(peach_dance_action_turn)
    CALL(dance_flag_onoff, 2, 1)
    CALL_CHILD(PTR(dance_action_turn_sub))
    CALL(dance_flag_onoff, 2, 0)
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_action_reverse)
    CALL(dance_flag_onoff, 2, 1)
    CALL_CHILD(PTR(dance_action_turn_sub))
    CALL(dance_reverse)
    CALL(dance_flag_check, 1, LW(0))
    CALL(dance_flag_onoff, 2, 0)
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_action_fail)
    CALL(dance_flag_onoff, 2, 1)
    CALL(dance_flag_onoff, 8, 1)
    CALL(peach_set_pose, STRING("P_O_D_1"))
    CALL(horogram_set_pose, STRING("P_O_F_2"))
    WAIT_MS(400)
    CALL(peach_dance_after_fail)
    CALL(dance_flag_onoff, 8, 0)
    CALL(dance_flag_onoff, 2, 0)
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_disp_sub)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_VALUE(LW(4), STRING("btn_01"))
        CASE_EQUAL(1)
        SET_VALUE(LW(4), STRING("btn_02"))
        CASE_EQUAL(2)
        SET_VALUE(LW(4), STRING("btn_03"))
    END_SWITCH
    SWITCH(LW(2))
        CASE_EQUAL(1)
        SET_VALUE(LW(3), 0)
        CASE_EQUAL(2)
        SET_VALUE(LW(3), 45)
        CASE_EQUAL(0)
        SET_VALUE(LW(3), -45)
    END_SWITCH
    CALL(evt_fuki_btn, LW(2), LW(4), STRING("ダミー"), 0, 0, 0, 0, LW(3), -1)
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_disp)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CALL(dance_flag_onoff, 4096, 1)
        CASE_EQUAL(1)
        CALL(dance_flag_onoff, 8192, 1)
        CASE_EQUAL(2)
        CALL(dance_flag_onoff, 16384, 1)
    END_SWITCH
    CALL_CHILD(PTR(dance_btn_disp_sub))
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_batu)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CALL(evt_fuki_btn_set_batu, STRING("btn_01"))
        CASE_EQUAL(1)
        CALL(evt_fuki_btn_set_batu, STRING("btn_02"))
        CASE_EQUAL(2)
        CALL(evt_fuki_btn_set_batu, STRING("btn_03"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_clear)
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CALL(dance_flag_check, 4096, LW(3))
        IF_INT_EQUAL(LW(3), 1)
            CALL(evt_eff_softdelete, STRING("btn_01"))
            CALL(dance_flag_onoff, 4096, 0)
        END_IF
        CASE_EQUAL(1)
        CALL(dance_flag_check, 8192, LW(3))
        IF_INT_EQUAL(LW(3), 1)
            CALL(evt_eff_softdelete, STRING("btn_02"))
            CALL(dance_flag_onoff, 8192, 0)
        END_IF
        CASE_EQUAL(2)
        CALL(dance_flag_check, 16384, LW(3))
        IF_INT_EQUAL(LW(3), 1)
            CALL(evt_eff_softdelete, STRING("btn_03"))
            CALL(dance_flag_onoff, 16384, 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(dance_btn_clear_all)
    CALL(dance_flag_check, 4096, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_eff_softdelete, STRING("btn_01"))
        CALL(dance_flag_onoff, 4096, 0)
    END_IF
    CALL(dance_flag_check, 8192, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_eff_softdelete, STRING("btn_02"))
        CALL(dance_flag_onoff, 8192, 0)
    END_IF
    CALL(dance_flag_check, 16384, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_eff_softdelete, STRING("btn_03"))
        CALL(dance_flag_onoff, 16384, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(wait_action_time)
    LOOP(0)
        CALL(evt_sub_get_stopwatch, LW(12), LW(4))
        IF_INT_GREATER_OR_EQUAL(LW(4), 660)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_dark)
    CALL(evt_sub_intpl_msec_init, 11, 255, 192, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_dance_light)
    CALL(evt_sub_intpl_msec_init, 11, 192, 255, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(peach_evt_dance)
    CALL(evt_npc_pera_onoff, STRING("ホログラム"), 0)
    CALL(evt_npc_set_ry, STRING("ホログラム"), 180)
    CALL(evt_npc_pera_onoff, STRING("ホログラム2"), 0)
    CALL(evt_npc_set_ry, STRING("ホログラム2"), 180)
    LABEL(100)
    SET_VALUE(LW(15), 0)
    SET_VALUE(LW(14), 0)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(12), 0)
    SET_VALUE(LW(11), 0)
    CALL(dance_data_init)
    CALL(get_center, LW(2), LW(3))
    CALL(evt_npc_set_position, STRING("ダミー"), LW(2), FLOAT(5.0f), LW(3))
    CALL(peach_set_pose, STRING("P_O_Z_1"))
    CALL(evt_npc_set_anim, STRING("ホログラム"), STRING("P_O_Z_1"))
    CALL(evt_npc_set_anim, STRING("ホログラム2"), STRING("P_O_Z_1R"))
    WAIT_MS(350)
    CALL(peach_set_pose, STRING("P_O_S_1"))
    CALL(horogram_set_pose, STRING("P_O_S_2"))
    WAIT_MS(1000)
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_EVT_PEACH_WALTZ1"))
    CALL(bgm_start_wait)
    WAIT_MS(4000)
    SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(13))
    SPAWN_EVENT(PTR(peach_dance_move))
    LOOP(0)
        CALL(evt_sub_get_stopwatch, LW(13), LW(4))
        IF_INT_GREATER_OR_EQUAL(LW(4), 660)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(LW(11), 2000)
    LOOP(0)
        CALL(evt_sub_get_stopwatch, LW(13), LW(4))
        IF_INT_GREATER_OR_EQUAL(LW(4), 32000)
            BREAK_LOOP
        END_IF
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(12))
        SPAWN_EVENT(PTR(peach_dance_move))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(12), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 660)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_random, 2, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_RAW_VALUE(LW(2), 1)
            CASE_EQUAL(1)
            SET_RAW_VALUE(LW(2), 0)
            CASE_EQUAL(2)
            SET_RAW_VALUE(LW(2), 2)
        END_SWITCH
        CALL_CHILD(PTR(dance_btn_disp))
        SPAWN_EVENT(PTR(peach_dance_move))
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(14))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(14), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 660)
                SET_VALUE(LW(3), 2)
                BREAK_LOOP
            END_IF
            CALL(btn_check, LW(2), LW(3))
            IF_INT_NOT_EQUAL(LW(3), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        DELETE_EVENT(LW(14))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(12), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 1320)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(13), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), LW(11))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        ADD(LW(11), 2000)
        SPAWN_EVENT(PTR(peach_dance_move))
        IF_INT_NOT_EQUAL(LW(3), 0)
            SWITCH(LW(3))
                CASE_EQUAL(1)
                ADD(LW(15), 1)
                CALL_CHILD(PTR(dance_btn_clear))
                SWITCH(LW(2))
                    CASE_EQUAL(1)
                    SPAWN_EVENT(PTR(peach_dance_action_step))
                    CASE_EQUAL(2)
                    SPAWN_EVENT(PTR(peach_dance_action_turn))
                    CASE_EQUAL(0)
                    SPAWN_EVENT(PTR(peach_dance_action_reverse))
                END_SWITCH
                CASE_EQUAL(2)
                CALL(evt_npc_get_position, STRING("ホログラム"), LW(5), LW(6), LW(7))
                CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_DANCE_NG1"), LW(5), 0, LW(7), 0)
                CALL_CHILD(PTR(dance_btn_batu))
                SPAWN_EVENT(PTR(peach_dance_action_fail))
            END_SWITCH
        END_IF
        CALL_CHILD(PTR(dance_btn_clear_all))
        LOOP(0)
            CALL(evt_sub_get_stopwatch, LW(12), LW(4))
            IF_INT_GREATER_OR_EQUAL(LW(4), 1980)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        DELETE_EVENT(LW(12))
    END_LOOP
    DELETE_EVENT(LW(13))
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_snd_envon_f, 272, STRING("ENV_STG7_AJI4"), 2000)
    WAIT_MS(400)
    CALL(horogram_flag_onoff, 1, 4)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(horogram_set_pose, STRING("P_S_1"))
    WAIT_MS(300)
    SET_VALUE(LW(10), LW(15))
    CALL(evt_npc_get_position, STRING("ホログラム"), LW(2), LW(0), LW(3))
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_DANCE_APPEAR1"), LW(2), 0, LW(3), 0)
    CALL(evt_sub_intpl_msec_init, 11, 192, 0, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_npc_set_color, STRING("ホログラム"), 255, 255, 255, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING("ホログラム"), 128)
    CALL_CHILD(PTR(peach_dance_light))
    SET_VALUE(LW(15), LW(10))
    CALL(evt_cam3d_evt_set, 0, 105, 243, 0, 55, -53, 1500, 11)
    CALL(dance_data_init)
    CALL(compute_peach_pos, 0, -80, LW(0), LW(1))
    CALL(evt_mario_mov_pos, LW(0), LW(1), 1500)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    IF_INT_LESS(LW(15), 10)
        CALL(evt_map_replayanim, 0, STRING("moza"))
        CALL(evt_msg_print, 0, STRING("peach_aji_94"), 0, 0)
        CALL(evt_map_pauseanim, 0, STRING("moza"))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_set_position, STRING("ダミー"), LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("peach_aji_95"), 0, STRING("ダミー"))
        CALL(horogram_flag_onoff, 0, 4)
        CALL(evt_npc_set_ry, STRING("ホログラム"), 180)
        CALL_CHILD(PTR(peach_dance_dark))
        CALL(compute_horogram_pos, 0, -80, LW(2), LW(3))
        CALL(evt_npc_set_position, STRING("ホログラム"), LW(2), 0, LW(3))
        CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_DANCE_APPEAR1"), LW(2), 0, LW(3), 0)
        CALL(evt_sub_intpl_msec_init, 11, 0, 192, 500)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_npc_set_color, STRING("ホログラム"), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_cam3d_evt_set, 0, 95, 243, 0, 45, -53, 700, 11)
        WAIT_MS(700)
        GOTO(100)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg2)
    CALL(evt_mario_set_mode, 1)
    CALL(evt_npc_entry, STRING("ダミー"), STRING("c_peach"))
    CALL(evt_npc_flag_onoff, 1, STRING("ダミー"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("ダミー"), 32)
    CALL(evt_npc_set_width, STRING("ダミー"), FLOAT(20.0f))
    CALL(evt_npc_set_height, STRING("ダミー"), FLOAT(47.0f))
    CALL(evt_npc_entry, STRING("ホログラム"), STRING("c_peach"))
    CALL(evt_npc_set_tribe, STRING("ホログラム"), STRING("ピーチ姫"))
    CALL(evt_npc_flag_onoff, 1, STRING("ホログラム"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("ホログラム"), 32)
    CALL(evt_npc_set_color, STRING("ホログラム"), 255, 255, 255, 255)
    CALL(evt_npc_set_width, STRING("ホログラム"), FLOAT(20.0f))
    CALL(evt_npc_set_height, STRING("ホログラム"), FLOAT(47.0f))
    CALL(evt_npc_entry, STRING("ホログラム2"), STRING("c_peach_r"))
    CALL(evt_npc_set_tribe, STRING("ホログラム2"), STRING("ピーチ姫"))
    CALL(evt_npc_flag_onoff, 1, STRING("ホログラム2"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("ホログラム2"), 32)
    CALL(evt_npc_set_color, STRING("ホログラム2"), 255, 255, 255, 255)
    CALL(evt_npc_set_width, STRING("ホログラム2"), FLOAT(20.0f))
    CALL(evt_npc_set_height, STRING("ホログラム2"), FLOAT(47.0f))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(horogram_init)
    WAIT_FRAMES(1)
    CALL(evt_npc_set_color, STRING("ホログラム"), 255, 255, 255, 0)
    CALL(evt_npc_set_color, STRING("ホログラム2"), 255, 255, 255, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(horogram_cap_evt)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(disp_horogram_evt)
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_76"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_76_01"), 0, STRING("mario"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_76_02"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_77"), 0, STRING("mario"))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_78"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 300, 1, 20)
    CALL(evt_msg_print, 0, STRING("peach_aji_79"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_80"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_adjust_dir)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_83"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_84"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(peach_set_pose, STRING("P_C_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_C_1"), STRING("P_T_8"))
    CALL(evt_msg_print, 0, STRING("peach_aji_85"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_86"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL_CHILD(PTR(peach_dance_dark))
    LABEL(100)
    CALL(evt_npc_set_position, STRING("ホログラム"), 30, 0, -68)
    CALL(evt_sub_intpl_msec_init, 11, 0, 192, 500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_DANCE_APPEAR1"), 30, 0, -67, 0)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_npc_set_color, STRING("ホログラム"), 255, 255, 255, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(peach_set_pose, STRING("P_B_2"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
    CALL(evt_msg_print, 0, STRING("peach_aji_91"), 0, STRING("mario"))
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_cam3d_evt_set, 0, 95, 243, 0, 45, -53, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("peach_aji_92"), 0, STRING("mario"))
    CALL(dance_data_init)
    CALL(compute_peach_pos, 0, -80, LW(0), LW(1))
    CALL(compute_horogram_pos, 0, -80, LW(2), LW(3))
    DEBUG_PUT_MSG(STRING("move_pos"))
    DEBUG_PUT_REG(LW(0))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ホログラム"), LW(2), LW(3), 0, FLOAT(48.0f), 0)
        CALL(evt_npc_set_ry, STRING("ホログラム"), 180)
        CALL(evt_npc_set_anim, STRING("ホログラム"), STRING("P_S_1"))
        CALL(evt_npc_set_anim, STRING("ホログラム2"), STRING("P_S_1R"))
        CALL(horogram_flag_onoff, 1, 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, LW(0), LW(1), FLOAT(48.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_93"), 0, 0)
    CALL_CHILD(PTR(peach_evt_dance))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_96"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_97"), 0, STRING("mario"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_98"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 1000, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_KEYBOARD1"), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING("P_A_1R"))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING("P_S_1R"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_99"), 0, STRING("mario"))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_meil"), 1)
    CALL(evt_map_playanim, STRING("mel"), 0, 0)
    CALL(evt_map_checkanim, STRING("mel"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_meil"), 1)
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_100"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -140, 88, 226, -140, 55, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_peach_set_condition, 6)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_7"), STRING("P_T_13"))
    CALL(evt_msg_print, 0, STRING("peach_aji_101"), 0, STRING("mario"))
    CALL(evt_msg_print, 0, STRING("peach_aji_101_01"), 0, 0)
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_102"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    CALL(evt_peach_set_condition, 0)
    SET_VALUE(GSW(0), 114)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_aji_17"), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 5)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING("hei_00"), STRING(""))
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg3)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_115"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_116"), 0, STRING("mario"))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_msg_print, 0, STRING("peach_aji_117"), 0, 0)
    CALL(evt_msg_print, 0, STRING("peach_aji_118"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_119"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("peach_aji_119_01"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_119_02"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_set_dir, 90, 0, 0)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_S_4"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_4"), STRING("P_T_4"))
    CALL(evt_msg_print, 0, STRING("peach_aji_120"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_121"), 0, 0)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 1000, 11)
    WAIT_MS(1300)
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(peach_set_pose, STRING("P_G_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_G_1"), STRING("P_G_10"))
    CALL(evt_msg_print, 0, STRING("peach_aji_122"), 0, STRING("mario"))
    CALL(peach_set_pose, STRING("P_E_1"))
    WAIT_MS(400)
    CALL(peach_set_pose, STRING("P_E_2"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_123"), 0, 0)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_124"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_125"), 0, 0)
    CALL(evt_fade_set_mapchange_type, 0, 10, 600, 9, 300)
    CALL(evt_bero_mapchange, STRING("aji_01"), STRING("e_bero_5"))
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg3_1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_set_pos, -215, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -140, 0, 80)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(100)
    CALL(evt_mario_wait_move_end)
    CALL(evt_msg_print, 0, STRING("peach_aji_156"), 0, STRING("mario"))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_157"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("peach_aji_157_01"), 0, STRING("mario"))
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(peach_set_pose, STRING("P_S_4"))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_157_02"), 0, 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_157_03"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_157_04"), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_158"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_159"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("peach_aji_160"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_161"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_KEYBOARD1"), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING("P_A_1R"))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING("P_S_1R"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_163"), 0, STRING("mario"))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_meil"), 1)
    CALL(evt_map_playanim, STRING("mel"), 0, 0)
    CALL(evt_map_checkanim, STRING("mel"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_meil"), 1)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_164"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_165"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(2500)
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_166"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 169)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_aji_17"), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 8)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING("mri_01"), STRING(""))
    RETURN
EVT_END()

s32 peach_evt_stg4_quiz_data[5][4] = {
    (s32)"peach_aji_174", (s32)"peach_aji_175", (s32)"peach_aji_175_sel", 1, (s32)"peach_aji_178", (s32)"peach_aji_179", (s32)"peach_aji_179_sel", 0,
    (s32)"peach_aji_180", (s32)"peach_aji_181", (s32)"peach_aji_183_sel", 2, (s32)"peach_aji_184", (s32)"peach_aji_185", (s32)"peach_aji_185_sel", 1,
    (s32)"peach_aji_186", (s32)"peach_aji_187", (s32)"peach_aji_187_sel", 2,
};

static EVT_BEGIN(peach_evt_stg4)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 115, 133, 430, 115, 55, -13, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_mario_set_pos, -215, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_cam3d_evt_set, -105, 133, 430, -105, 55, -13, 3000, 0)
    WAIT_MS(3000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -140, 0, 80)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(PTR(w_door_close))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(100)
    CALL(evt_mario_wait_move_end)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("peach_aji_166_01"), 0, STRING("mario"))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_msg_print, 0, STRING("peach_aji_166_02"), 0, STRING("mario"))
    WAIT_MS(2000)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_166_03"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_166_04"), 0, STRING("mario"))
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 700, 11)
    WAIT_MS(700)
    CALL(evt_msg_print, 0, STRING("peach_aji_166_05"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_166_06"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("peach_aji_166_07"), 0, STRING("mario"))
    CALL(evt_mario_set_dir, 90, 0, 0)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_S_4"))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("peach_aji_166_08"), 0, 0)
    CALL(peach_set_pose, STRING("P_S_1"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_167"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_168"), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    CALL(evt_msg_print, 0, STRING("peach_aji_169"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    SET_VALUE(LW(15), 0)
    SET_VALUE(LF(15), 0)
    LOOP(0)
        CALL(peach_evt_stg4_read_quiz_data, LW(15), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_map_replayanim, 0, STRING("moza"))
        CALL(evt_msg_print, 0, LW(2), 0, 0)
        CALL(evt_map_pauseanim, 0, STRING("moza"))
        CALL(peach_set_pose, STRING("P_C_1"))
        CALL(evt_cam3d_evt_set, 0, 108, 233, 0, 65, -13, 0, 11)
        WAIT_FRAMES(1)
        WAIT_MS(500)
        CALL(evt_map_replayanim, 0, STRING("moza"))
        SET_VALUE(LF(0), 0)
        IF_INT_EQUAL(LW(15), 2)
            IF_INT_EQUAL(LF(15), 1)
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            CALL(evt_msg_print, 0, LW(3), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("peach_aji_181_01"), 0, 0)
        END_IF
        CALL(evt_map_pauseanim, 0, STRING("moza"))
        IF_INT_EQUAL(LW(15), 2)
            IF_INT_EQUAL(LF(15), 0)
                CALL(evt_mario_get_pos, 0, LW(12), LW(13), LW(14))
                CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED1_3"), LW(12), LW(13), LW(14), 0)
                CALL(peach_set_pose, STRING("P_B_2"))
                WAIT_MS(500)
                CALL(evt_cam3d_evt_set, 230, 45, 327, 22, 85, -25, 0, 11)
                WAIT_FRAMES(1)
                CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
                CALL(evt_msg_print, 0, STRING("peach_aji_182"), 0, STRING("mario"))
                WAIT_MS(500)
                CALL(evt_map_replayanim, 0, STRING("moza"))
                CALL(evt_msg_print, 0, STRING("peach_aji_183"), 0, 0)
                CALL(evt_map_pauseanim, 0, STRING("moza"))
                CALL(peach_set_pose, STRING("P_C_1"))
                WAIT_FRAMES(1)
                CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
                SET_VALUE(LF(15), 1)
            END_IF
        END_IF
        CALL(evt_msg_select, 0, LW(4))
        CALL(evt_msg_continue)
        IF_INT_EQUAL(LW(5), LW(0))
            CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(15), 4)
                CALL(evt_map_replayanim, 0, STRING("moza"))
                CALL(evt_msg_print, 0, STRING("peach_aji_190"), 0, 0)
                CALL(evt_map_pauseanim, 0, STRING("moza"))
                BREAK_LOOP
            END_IF
            ADD(LW(15), 1)
            ELSE
            CALL(evt_map_replayanim, 0, STRING("moza"))
            CALL(evt_msg_print, 0, STRING("peach_aji_188"), 0, 0)
            CALL(evt_map_pauseanim, 0, STRING("moza"))
            SET_VALUE(LW(15), 0)
            CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
            WAIT_FRAMES(1)
        END_IF
        WAIT_MS(500)
    END_LOOP
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_190_01"), 0, STRING("mario"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_190_02"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 700, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_KEYBOARD1"), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING("P_A_1R"))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING("P_S_1R"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_192"), 0, STRING("mario"))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_meil"), 1)
    CALL(evt_map_playanim, STRING("mel"), 0, 0)
    CALL(evt_map_checkanim, STRING("mel"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_meil"), 1)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_193"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_open_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_open))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_peach_set_condition, 6)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_7"), STRING("P_T_13"))
    CALL(evt_msg_print, 0, STRING("peach_aji_194"), 0, STRING("mario"))
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_195"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    CALL(evt_peach_set_condition, 0)
    SET_VALUE(GSW(0), 215)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_aji_17"), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 11)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING("gor_04"), 0)
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg5)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_set_pos, -200, 0, 0)
    CALL(evt_cam3d_evt_set, 230, 45, 372, 22, 85, -25, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    WAIT_MS(500)
    CALL(evt_mario_mov_pos2, -140, 0, 60)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    WAIT_MS(200)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_G_1"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_G_1"), STRING("P_G_10"))
    CALL(evt_msg_print, 0, STRING("peach_aji_206"), 0, STRING("mario"))
    CALL(peach_set_pose, STRING("P_E_1"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_207"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(2000)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_208"), 0, STRING("mario"))
    WAIT_MS(2000)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_209"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_C_1"), STRING("P_T_8"))
    CALL(evt_msg_print, 0, STRING("peach_aji_210"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_211"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("peach_aji_212"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_213"), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_214"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_215"), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    CALL(evt_msg_print, 0, STRING("peach_aji_216"), 0, STRING("mario"))
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_217"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_off, 1000, 11)
    SET_VALUE(GSW(0), 262)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg5_1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai_0"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_set_pos, -220, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_open))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 2000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 2000, 11)
        CALL(evt_mario_mov_pos, -30, -68, 2000)
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mario_wait_move_end)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_260"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_261"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_262"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_263"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_264"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 700, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(150)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_KEYBOARD1"), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING("P_A_1R"))
    WAIT_MS(3000)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(peach_set_pose, STRING("P_S_1R"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_265"), 0, STRING("mario"))
    WAIT_MS(500)
    SPAWN_EVENT(PTR(mail_sousin_se))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_meil"), 1)
    CALL(evt_map_playanim, STRING("mel"), 0, 0)
    CALL(evt_map_checkanim, STRING("mel"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_meil"), 1)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_266"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_267"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, -140, 92, 226, -140, 59, 55, 2000, 11)
    CALL(evt_mario_mov_pos, -140, 0, 2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_open))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_msg_print, 0, STRING("peach_aji_267_01"), 0, 0)
    CALL(evt_peach_set_condition, 6)
    CALL(evt_mario_set_dir, 90, 200, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_7"), STRING("P_T_13"))
    CALL(evt_msg_print, 0, STRING("peach_aji_267_02"), 0, STRING("mario"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_mario_mov_pos, -230, 0, 1000)
    WAIT_MS(500)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL_CHILD(PTR(w_door_close))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    WAIT_MS(2000)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_268"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_sub_intpl_msec_init, 11, 255, 96, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 265)
    CALL(evt_peach_set_condition, 0)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_aji_17"), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 14)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING("usu_00"), STRING(""))
    RETURN
EVT_END()

static EVT_BEGIN(peach_evt_stg6)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    CALL(evt_mario_set_mode, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
    CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
    CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
    CALL(evt_map_playanim, STRING("moza"), 1, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_282"), 0, STRING("mario"))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 45, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("ren1"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1500, 11)
    CALL(evt_mario_mov_pos, -30, -68, 1500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_282_01"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_QUESTION1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 1, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    CALL(evt_msg_print, 0, STRING("peach_aji_282_02"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_282_03"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_dispflag_onoff, 1, 512)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_282_04"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_283"), 0, 0)
    CALL(peach_set_pose, STRING("P_S_4"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_4"), STRING("P_T_4"))
    CALL(evt_msg_print, 0, STRING("peach_aji_284"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    WAIT_MS(300)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_285"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_286"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_287"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 220, 200, 380, -147, 60, -4, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_mario_set_reardir)
    WAIT_MS(3000)
    CALL(evt_fade_out, 1000)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -25, 75, 135, -25, 50, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_adjust_dir)
    CALL(peach_set_pose, STRING("P_B_2"))
    CALL(evt_fade_in, 1000)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
    CALL(evt_msg_print, 0, STRING("peach_aji_288"), 0, STRING("mario"))
    CALL(peach_set_pose, STRING("P_C_1"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_289"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_C_1"), STRING("P_T_8"))
    CALL(evt_msg_print, 0, STRING("peach_aji_290"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_291"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, -30, 67, -220, -30, 37, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_set_dispdir, 0)
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_292"), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_293"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_294"), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_295"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_296"), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_297"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_298"), 0, 0)
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(evt_mario_set_dispdir, 180)
    CALL(peach_set_pose, STRING("P_S_4"))
    WAIT_MS(300)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_4"), STRING("P_T_4"))
    CALL(evt_msg_print, 0, STRING("peach_aji_299"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_300"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    WAIT_MS(500)
    CALL(peach_set_pose, STRING("P_P_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_P_1"), STRING("P_T_9"))
    CALL(evt_msg_print, 0, STRING("peach_aji_301"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_302"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    LABEL(100)
    CALL(evt_cam3d_evt_set, 0, 92, 171, 0, 59, -13, 700, 11)
    CALL(evt_mario_mov_pos, 0, -95, 700)
    WAIT_MS(1000)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_KEYBOARD1"), 0, 25, 120, LW(15))
    CALL(peach_set_pose, STRING("P_A_1R"))
    WAIT_MS(1000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    WAIT_MS(500)
    SET_VALUE(LW(0), 180)
    CALL_CHILD(PTR(w_door_open))
    CALL(evt_npc_set_position, STRING("手下１"), -140, 0, 0)
    CALL(evt_npc_set_position, STRING("シュリョー"), -190, 0, 0)
    CALL(evt_npc_set_position, STRING("手下２"), -240, 0, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(PTR(w_door_close))
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下１"), -80, 0, 0, FLOAT(60.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("シュリョー"), -130, 0, 0, FLOAT(60.0f), 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("手下２"), -180, 0, 0, FLOAT(60.0f), 0)
    CALL(evt_msg_print, 0, STRING("peach_aji_303"), 0, STRING("シュリョー"))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED2_1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 200, 1, 10)
    WAIT_MS(300)
    CALL(peach_set_pose, STRING("P_C_1"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
    CALL(evt_msg_print, 0, STRING("peach_aji_304"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, -130, 121, 344, -130, 65, 66, 1500, 11)
    WAIT_MS(1500)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG8_3RDHEAD1"))
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING("peach_aji_305"), 0, STRING("シュリョー"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下１"), 30, -70, 0, FLOAT(60.0f), 0)
        CALL(evt_npc_set_ry, STRING("手下１"), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("シュリョー"), 32)
        CALL(evt_npc_move_position, STRING("シュリョー"), -30, -70, 0, FLOAT(60.0f), 0)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下２"), -100, -70, 0, FLOAT(60.0f), 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_306"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 140, 332, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    WAIT_WHILE(GF(0))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_307"), 0, STRING("シュリョー"))
    CALL(evt_msg_print, 0, STRING("peach_aji_308"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, -30, 100, 184, -30, 65, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("peach_aji_309"), 0, STRING("シュリョー"))
    CALL(evt_cam3d_evt_set, 0, 80, 44, 0, 130, -150, 0, 11)
    WAIT_FRAMES(1)
    CALL(peach_set_pose, STRING("P_C_1"))
    WAIT_MS(700)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    CALL(evt_msg_print, 0, STRING("peach_aji_310"), 0, 0)
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_cam3d_evt_set, 0, 75, 387, 0, 75, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("peach_aji_311"), 0, STRING("シュリョー"))
    CALL(evt_msg_print, 0, STRING("peach_aji_312"), 0, STRING("手下２"))
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下１"), 105, -95, 0, 70, 4)
        CALL(evt_npc_set_ry, STRING("手下１"), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下２"), -105, -95, 0, 60, 4)
        CALL(evt_npc_set_ry, STRING("手下２"), 90)
    END_INLINE_EVENT
    WAIT_MS(1400)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("手下１"), 1073741824)
        CALL(evt_npc_status_onoff, 0, STRING("手下１"), 2)
        WAIT_FRAMES(1)
        CALL(evt_npc_move_position, STRING("手下１"), 105, -100, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_move_position, STRING("手下１"), 105, -95, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING("手下１"), 2)
        CALL(evt_npc_flag_onoff, 0, STRING("手下１"), 1073741824)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("手下２"), 1073741824)
        CALL(evt_npc_status_onoff, 0, STRING("手下２"), 2)
        WAIT_FRAMES(1)
        CALL(evt_npc_move_position, STRING("手下２"), -105, -100, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_move_position, STRING("手下２"), -105, -95, 100, 0, 0)
        WAIT_MS(100)
        CALL(evt_npc_status_onoff, 1, STRING("手下２"), 2)
        CALL(evt_npc_flag_onoff, 0, STRING("手下２"), 1073741824)
    END_INLINE_EVENT
    CALL(evt_mapobj_get_position, STRING("S_sui2"), LW(0), LW(1), LW(2))
    CALL(evt_mapobj_get_position, STRING("S_sui3"), LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_TEC_BUTTON1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_TEC_BUTTON1"), LW(3), LW(4), LW(5), 0)
    WAIT_MS(500)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_mario_adjust_dir)
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_mario_set_reardir)
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_313"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, 0, 80, -249, 0, 25, 21, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 1, 0)
    CALL(evt_mario_set_dispdir, 0)
    CALL(peach_set_pose, STRING("P_C_1"))
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_C_1"), STRING("P_T_8"))
    CALL(evt_msg_print, 0, STRING("peach_aji_314"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 75, 387, 0, 75, -13, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
    CALL(evt_fade_tec_onoff, 0, 0)
    CALL(peach_set_pose, STRING("P_S_1"))
    CALL(evt_mario_set_dispdir, 180)
    CALL(evt_mario_set_reardir)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 0, 512)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_315"), 0, 0)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_map_pauseanim, 0, STRING("kika_3"))
    WAIT_MS(500)
    CALL(evt_map_pauseanim, 0, STRING("kika_2"))
    WAIT_MS(500)
    CALL(evt_map_pauseanim, 0, STRING("kika_1"))
    WAIT_MS(500)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai_0"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("monihiraku"), 1)
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_msg_print, 0, STRING("peach_aji_316"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_317"), 0, STRING("シュリョー"))
    CALL(peach_set_pose, STRING("P_S_6"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_6"), STRING("P_T_6"))
    CALL(evt_msg_print, 0, STRING("peach_aji_318"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("peach_aji_319"), 0, STRING("シュリョー"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_SURPRISED1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_B_2"), STRING("P_T_7"))
    CALL(evt_msg_print, 0, STRING("peach_aji_320"), 0, STRING("mario"))
    CALL(evt_cam3d_evt_set, -35, 100, 184, -35, 65, -13, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("peach_aji_321"), 0, STRING("シュリョー"))
    SET_VALUE(GSW(0), 341)
    WAIT_MS(2000)
    CALL(evt_snd_bgmoff_f, 512, 1000)
    CALL(evt_snd_envoff_f, 512, 1000)
    CALL(evt_fade_entry, 15, 300, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_aji_17"), 1)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    SET_VALUE(LF(10), 0)
    SET_VALUE(LW(0), 17)
    CALL_CHILD(PTR(evt_memcard_save))
    CALL(evt_mario_set_mode, 2)
    CALL(evt_snd_bgmoff_f, 512, 2000)
    CALL(evt_snd_envoff_f, 512, 2000)
    CALL(evt_snd_sfx_all_stop)
    CALL(evt_fade_set_mapchange_type, 1, 57, 0, 56, 0)
    CALL(evt_bero_mapchange, STRING("gor_01"), STRING(""))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(teshita1_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(teshita2_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(syuryo_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"手下１"*/"\x8E\xE8\x89\xBA\x82\x50", 0, 0, (s32)teshita1_init, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"手下２"*/"\x8E\xE8\x89\xBA\x82\x51",
    0, 0, (s32)teshita2_init, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"シュリョー"*/"\x83\x56\x83\x85\x83\x8A\x83\x87\x81\x5B", 0,
    0, (s32)syuryo_init, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(tec_talk)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_map_replayanim, 0, STRING("moza"))
    IF_INT_EQUAL(GSWF(4219), 0)
        CALL(evt_msg_print, 0, STRING("stg7_aji_tec_00"), 0, 0)
        SET_VALUE(GSWF(4219), 1)
        ELSE
        CALL(evt_msg_print, 0, STRING("stg7_aji_tec_01"), 0, 0)
    END_IF
    CALL(evt_map_pauseanim, 0, STRING("moza"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(aji_17_init_evt)
    SET_VALUE(LW(0), STRING("S_camera_1"))
    SET_VALUE(LW(1), -30)
    SET_VALUE(LW(2), 60)
    SPAWN_EVENT(PTR(evt_camera))
    SET_VALUE(LW(0), STRING("S_camera_2"))
    SET_VALUE(LW(1), -60)
    SET_VALUE(LW(2), 30)
    SPAWN_EVENT(PTR(evt_camera))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_meil"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kikai_0"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("polySurface1161_q00063"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("polySurface1168_q00065"), 2)
    CALL(evt_mapobj_scale, 0, STRING("ren2"), 5, 5, 1)
    IF_INT_EQUAL(GSW(0), 58)
        SPAWN_EVENT(PTR(peach_evt_stg1))
    END_IF
    IF_INT_EQUAL(GSW(0), 113)
        SPAWN_EVENT(PTR(peach_evt_stg2))
    END_IF
    IF_INT_EQUAL(GSW(0), 165)
        SPAWN_EVENT(PTR(peach_evt_stg3))
    END_IF
    IF_INT_EQUAL(GSW(0), 168)
        SPAWN_EVENT(PTR(peach_evt_stg3_1))
        CALL(evt_mario_kill_party, 0)
    END_IF
    IF_INT_EQUAL(GSW(0), 214)
        SPAWN_EVENT(PTR(peach_evt_stg4))
    END_IF
    IF_INT_EQUAL(GSW(0), 261)
        SPAWN_EVENT(PTR(peach_evt_stg5))
    END_IF
    IF_INT_EQUAL(GSW(0), 264)
        SPAWN_EVENT(PTR(peach_evt_stg5_1))
    END_IF
    IF_INT_EQUAL(GSW(0), 340)
        CALL(evt_npc_setup, PTR(npcEnt))
        CALL(evt_shuryolight_init_2_text_B870, STRING("シュリョー"))
        CALL(evt_shuryolight_run_evt_2_text_B538, PTR(shuryolight_pow_normal_2_data_36ED8), PTR(shuryolight_head_normal_2_data_37004), PTR(shuryolight_tue_normal_2_data_37104))
        SPAWN_EVENT(PTR(peach_evt_stg6))
    END_IF
    IF_INT_EQUAL(GSW(0), 375)
        IF_INT_EQUAL(GSWF(4186), 0)
            CALL(evt_mario_get_party, LW(15))
            IF_INT_EQUAL(LW(15), 0)
                CALL(evt_mario_set_party, 0, 1)
                CALL(evt_party_run, 0)
                CALL(evt_pouch_mario_recovery)
                CALL(evt_pouch_all_party_recovery)
            END_IF
            SET_VALUE(GSWF(4186), 1)
            SPAWN_EVENT(PTR(evt_last))
            ELSE
            SPAWN_EVENT(PTR(evt_last2))
            SET_VALUE(LW(0), PTR(bero_entry_data))
            CALL(evt_bero_get_info)
            CALL_CHILD(PTR(bero_case_entry))
            RETURN
        END_IF
    END_IF
    SPAWN_EVENT(PTR(evt_emergency))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    SWITCH(GSW(0))
        CASE_EQUAL(58)
        CASE_EQUAL(168)
        CASE_EQUAL(214)
        CASE_DEFAULT
        CALL_CHILD(PTR(evt_bero_info_run))
    END_SWITCH
    CALL(evt_mario_get_mode, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_mario_kill_party, 0)
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI4"))
    END_IF
    IF_INT_GREATER(GSW(0), 402)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kurai"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kikai"), 1)
        CALL(evt_map_playanim, STRING("kika_1"), 1, 0)
        CALL(evt_map_playanim, STRING("kika_2"), 1, 0)
        CALL(evt_map_playanim, STRING("kika_3"), 1, 0)
        CALL(evt_map_playanim, STRING("moni_1"), 2, 0)
        CALL(evt_map_playanim, STRING("moza"), 1, 0)
        CALL(evt_map_pauseanim, 0, STRING("moza"))
        CALL(evt_run_case_evt, 9, 1, STRING("keyboard"), 0, PTR(tec_talk), 0)
    END_IF
    CALL(evt_snd_set_rev_mode, 1)
    RETURN
EVT_END()

static __declspec(section ".rodata") const char horogram_pose_suffix[] = "R";

USER_FUNC(horogram_set_pose) {
    char name[24];
    const char* pose = (const char*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = npcNameToPtr("\203z\203\215\203O\203\211\203\200");
    NpcEntry* npc2 = npcNameToPtr("\203z\203\215\203O\203\211\203\2002");
    MarioWork* mario = marioGetPtr();

    animPoseSetAnim(npc->poseId, pose, TRUE);
    strcpy(name, pose);
    strcat(name, horogram_pose_suffix);
    animPoseSetAnim(npc2->poseId, name, TRUE);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_fuki_btn_set_batu) {
    effSetPeachFukiBatu((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_fuki_btn) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    const char* npcName = (const char*)evtGetValue(event, args[2]);
    f32 x = evtGetFloat(event, args[3]);
    f32 y = evtGetFloat(event, args[4]);
    f32 z = evtGetFloat(event, args[5]);
    f32 size = evtGetFloat(event, args[6]);
    f32 angle = evtGetFloat(event, args[7]);
    f32 unk = evtGetFloat(event, args[8]);
    NpcEntry* npc;
    EffectEntry* eff;

    if (strcmp(npcName, "me") == 0) {
        npc = event->ownerNPC;
    } else {
        npc = npcNameToPtr(npcName);
    }
    eff = effPeachFukidashiEntry(type, npc, 10000, 0.0f, 0.0f, 0.0f, 0.0f, angle);
    if (name != NULL && strcmp(name, "") != 0) {
        effSetName(eff, name);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(peach_dance_after_fail) {
    marioChgPoseTime("P_O_F_1", 20);
    return EVT_RETURN_DONE;
}

USER_FUNC(set_npc_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    NpcEntry* npc = npcNameToPtr(name);

    npc->position.x = npc->prevPosition.x = x;
    npc->position.y = npc->prevPosition.y = y;
    npc->position.z = npc->prevPosition.z = z;
    return EVT_RETURN_DONE;
}

USER_FUNC(btn_check) {
    s32* args = event->args;
    s32 dir = evtGetValue(event, args[0]);
    u32 btn = keyGetButtonTrg(0);
    s32 a = btn & 0x100;
    s32 b = btn & 0x200;
    s32 x = btn & 0x400;
    s32 ret = 0;

    switch (dir) {
    case 1:
        if (a && !(b | x)) {
            ret = 1;
        } else if (!a && (b | x)) {
            ret = 2;
        }
        break;
    case 2:
        if (b && !(a | x)) {
            ret = 1;
        } else if (!b && (a | x)) {
            ret = 2;
        }
        break;
    case 0:
        if (x && !(a | b)) {
            ret = 1;
        } else if (!x && (a | b)) {
            ret = 2;
        }
        break;
    default:
        if (a | b | x) {
            ret = 2;
        }
        break;
    }
    evtSetValue(event, args[1], ret);
    return EVT_RETURN_DONE;
}

USER_FUNC(wait_move_end) {
    return (dance_dt.flags & 4) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

USER_FUNC(wait_action_begin) {
    return (dance_dt.flags & 2) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(wait_action_end) {
    return (dance_dt.flags & 2) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

USER_FUNC(compute_horogram_pos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 z = evtGetFloat(event, args[1]);
    f32 s = sin(dance_dt.rot);
    f32 c = cos(dance_dt.rot);

    evtSetFloat(event, args[2], x - 5.5f * s);
    evtSetFloat(event, args[3], z + 5.5f * c);
    return EVT_RETURN_DONE;
}

USER_FUNC(compute_peach_pos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 z = evtGetFloat(event, args[1]);
    f32 s = sin(dance_dt.rot);
    f32 c = cos(dance_dt.rot);

    evtSetFloat(event, args[2], x + 5.5f * s);
    evtSetFloat(event, args[3], z - 5.5f * c);
    return EVT_RETURN_DONE;
}

USER_FUNC(compute_move_pos) {
    s32* args = event->args;

    if (!(dance_dt.flags & 1)) {
        dance_dt.movePos = (dance_dt.movePos + 1) % 15;
    } else if (dance_dt.movePos != 0) {
        dance_dt.movePos--;
    } else {
        dance_dt.movePos = 14;
    }
    evtSetFloat(event, args[0], move_pos_list[dance_dt.movePos][0]);
    evtSetFloat(event, args[1], move_pos_list[dance_dt.movePos][1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(move_center) {
    s32* args = event->args;
    f32 x0 = evtGetFloat(event, args[0]);
    f32 z0 = evtGetFloat(event, args[1]);
    f32 x1 = evtGetFloat(event, args[2]);
    f32 z1 = evtGetFloat(event, args[3]);
    s32 frames = evtGetValue(event, args[4]);
    OSTime now = gp->renderTime;
    s32 elapsed;

    if (isFirstCall) {
        dance_dt.flags |= 4;
        event->userdata[0] = ((u64)now >> 32) & 0xFFFFFFFF;
        event->userdata[1] = now & 0xFFFFFFFF;
        return EVT_RETURN_BLOCK;
    }
    elapsed = OSTicksToMilliseconds((u64)(s32)((u32)now - event->userdata[1]));
    if (elapsed < frames) {
        dance_dt.cx = intplGetValue(11, elapsed, frames, x0, x1);
        dance_dt.cy = intplGetValue(11, elapsed, frames, z0, z1);
        return EVT_RETURN_BLOCK;
    }
    dance_dt.cx = x1;
    dance_dt.cy = z1;
    dance_dt.flags &= ~4;
    if (++dance_dt.step >= 3) {
        dance_dt.step = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(dance_reverse) {
    if (dance_dt.flags & 1) {
        dance_dt.flags &= ~1;
    } else {
        dance_dt.flags |= 1;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(dance_flag_check) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);

    if (dance_dt.flags & mask) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(dance_flag_onoff) {
    s32* args = event->args;
    s32 mask = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);

    if (on) {
        dance_dt.flags |= mask;
    } else {
        dance_dt.flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(dance_data_init) {
    dance_dt.flags = 0;
    dance_dt.cx = 0.0f;
    dance_dt.cy = -80.0f;
    dance_dt.rot = -0.4712389f;
    dance_dt.step = 0;
    dance_dt.movePos = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(dance_get_step) {
    evtSetValue(event, event->args[0], dance_dt.step);
    return EVT_RETURN_DONE;
}

USER_FUNC(set_local_rotate) {
    f32 r;

    dance_dt.rot = evtGetFloat(event, event->args[0]);
    r = dance_dt.rot;
    if (r > 6.2831855f) {
        dance_dt.rot = r - 6.2831855f;
    }
    if (dance_dt.rot < 0.0f) {
        dance_dt.rot += 6.2831855f;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(get_local_rotate) {
    evtSetFloat(event, event->args[0], dance_dt.rot);
    return EVT_RETURN_DONE;
}

USER_FUNC(get_center) {
    s32* args = event->args;

    evtSetFloat(event, args[0], dance_dt.cx);
    evtSetFloat(event, args[1], dance_dt.cy);
    return EVT_RETURN_DONE;
}

USER_FUNC(horogram_flag_onoff) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);

    if (on) {
        horogram_wp->flags |= mask;
    } else {
        horogram_wp->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(horogram_init) {
    u32 size = GXGetTexBufferSize(0x260, 0x1E0, GX_TF_RGBA8, GX_FALSE, 0);

    horogram_wp = _mapAlloc(sizeof(HorogramWork));
    horogram_wp->buf0 = _mapAlloc(size);
    horogram_wp->buf1 = _mapAlloc(GXGetTexBufferSize(0x260, 0x1E0, GX_TF_Z8, GX_FALSE, 0));
    horogram_wp->ready = 0;
    horogram_wp->flags = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(horogram_cap_evt) {
    dispEntry(CAMERA_3D, 1000.0f, 0, peach_capture, NULL);
    return EVT_RETURN_BLOCK;
}

void peach_capture(CameraId cameraId, void* param) {
    CameraEntry saved = *camGetCurPtr();
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    NpcEntry* holo;
    NpcEntry* holo2;
    NpcEntry* npc;

    holo = npcNameToPtr("\203z\203\215\203O\203\211\203\200");
    holo2 = npcNameToPtr("\203z\203\215\203O\203\211\203\2002");
    if (90.0f <= holo->direction && holo->direction < 270.0f) {
        npc = holo2;
        if (!(horogram_wp->flags & 2)) {
            animPoseSetLocalTime(holo2->poseId, 0.0f);
        }
        horogram_wp->flags |= 2;
    } else {
        npc = holo;
        if (horogram_wp->flags & 2) {
            animPoseSetLocalTime(holo->poseId, 0.0f);
        }
        horogram_wp->flags &= ~2;
    }
    if (!(horogram_wp->flags & 1)) {
        npc = holo;
    }
    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(0.0f, 0.0f, 608.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 606, 478);
    C_MTXOrtho(projMtx, 28.0f, 0.0f, -14.0f, 14.0f, 1.0f, 100.0f);
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);
    {
        Vec pos;
        Vec up;
        Vec target;

        target = horogram_target;
        up = horogram_up;
        pos = horogram_pos;

        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    PSMTXIdentity(ident);
    animPoseSetMaterialFlagOff(npc->poseId, 0x40);
    animPoseMain(npc->poseId);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, 1.0f);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, 1.0f);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, 1.0f);
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_RGBA8, GX_TRUE);
    GXCopyTex(horogram_wp->buf0, GX_FALSE);
    GXPixModeSync();
    GXSetTexCopyDst(0x130, 0xF0, GX_TF_Z8, GX_TRUE);
    GXCopyTex(horogram_wp->buf1, GX_TRUE);
    GXPixModeSync();
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    horogram_wp->ready = 1;
}

USER_FUNC(disp_horogram_evt) {
    dispEntry(CAMERA_3D, 0.0f, 2, disp_horogram, NULL);
    return EVT_RETURN_BLOCK;
}

void disp_horogram(CameraId cameraId, void* param) {
    GXCullMode cull;
    Mtx mtx;
    Mtx trans;
    Mtx rot;
    GXColor mat;
    f32 angle;
    NpcEntry* npc = npcNameToPtr("\203z\203\215\203O\203\211\203\200");

    if (horogram_wp->ready) {
        GXGetCullMode(&cull);
        GXInitTexObj(&horogram_wp->tex0, horogram_wp->buf0, 0x130, 0xF0, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&horogram_wp->tex0, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXInitTexObj(&horogram_wp->tex1, horogram_wp->buf1, 0x130, 0xF0, GX_TF_Z8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&horogram_wp->tex1, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        PSMTXTrans(trans, npc->position.x, npc->position.y, npc->position.z);
        angle = reviseAngle(-npc->direction);
        angle -= camGetPtr(cameraId)->viewYaw;
        angle += (horogram_wp->flags & 4) ? 180.0f : 0.0f;
        PSMTXRotRad(rot, 'y', 0.017453292f * angle);
        PSMTXConcat(trans, rot, mtx);
        PSMTXConcat(camGetPtr(cameraId)->view, mtx, mtx);
        GXSetCurrentMtx(0);
        GXLoadTexObj(&horogram_wp->tex0, GX_TEXMAP0);
        GXLoadTexObj(&horogram_wp->tex1, GX_TEXMAP1);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        mat = npc->color;
        GXSetChanMatColor(GX_COLOR0A0, mat);
        GXSetChanAmbColor(GX_COLOR0A0, horogram_amb);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumTevStages(2);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_A0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
        GXSetCullMode(GX_CULL_NONE);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-28.0f, 55.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(28.0f, 55.0f, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(28.0f, 0.0f, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-28.0f, 0.0f, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXSetCullMode(cull);
    }
}

static void polygon(f32 x, f32 y, f32 w, f32 h, f32 s, f32 t) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x, y, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x + w, y, 0.0f);
    GXTexCoord2f32(s, 0.0f);
    GXPosition3f32(x + w, y - h, 0.0f);
    GXTexCoord2f32(s, t);
    GXPosition3f32(x, y - h, 0.0f);
    GXTexCoord2f32(0.0f, t);
}

static USER_FUNC(peach_set_pose) {
    const char* pose = (const char*)evtGetValue(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    marioChgPose(pose);
    return EVT_RETURN_DONE;
}

USER_FUNC(noise) {
    s32 alpha = evtGetValue(event, event->args[0]);
    dispEntry(CAMERA_2D, 1100.0f, 0, noiseDisp, (void*)alpha);
    return EVT_RETURN_DONE;
}

void noiseDisp(CameraId cameraId, void* param) {
    CameraEntry* cam;
    s32 ry;
    s32 y;
    s32 x;
    Mtx mtx;
    s32 i;
    u8* buf;
    u8 col;
    s32 n;
    s32 len;
    s32 start;
    s32 off;
    s32 by;
    GXTexObj tex;
    cam = camGetPtr(cameraId);

    buf = smartAlloc(GXGetTexBufferSize(64, 64, GX_TF_I8, GX_FALSE, 0), 3)->address;
    for (y = 0; y < 64; y++) {
        by = y / 4;
        ry = y % 4;
        for (x = 0; x < 64; x++) {
            off = (by << 8) + (x / 8) * 32;
            off += x % 8;
            off += (ry << 3);
            col = (y & 1) ? 0xFF : 0;
            buf[off] = col;
        }
        n = rand() % 100 + 100;
        for (i = 0; i < n; i++) {
            len = rand() % 4 + 2;
            start = rand() % (65 - len);
            col = rand() % 255;
            for (x = start; x < start + len; x++) {
                off = (x / 8) * 32 + by * 256;
                off += x % 8;
                off += ry * 8;
                buf[off] = col;
            }
        }
    }
    DCFlushRange(buf, 0x1000);
    GXInitTexObj(&tex, buf, 64, 64, GX_TF_I8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    PSMTXScale(mtx, 9.5f, 7.5f, 0.0f);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    {
        GXColor c = noise_color;
        c.a = (u8)(s32)param;
        GXSetTevColor(GX_TEVREG0, c);
    }
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(-gp->fbWidth / 2, gp->efbHeight / 2, 0);
    GXTexCoord2s16(0, 1);
    GXPosition3s16(gp->fbWidth / 2, gp->efbHeight / 2, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(gp->fbWidth / 2, -gp->efbHeight / 2, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(-gp->fbWidth, -gp->efbHeight / 2, 0);
    GXTexCoord2s16(0, 0);
}

static USER_FUNC(viewport) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 w = evtGetFloat(event, args[2]);
    f32 h = evtGetFloat(event, args[3]);
    CameraEntry* cam;

    cam = camGetPtr(CAMERA_3D);
    cam->viewport[0] = x;
    cam->viewport[1] = y;
    cam->viewport[2] = w;
    cam->viewport[3] = h;
    cam = camGetPtr(CAMERA_2D);
    cam->viewport[0] = x;
    cam->viewport[1] = y;
    cam->viewport[2] = w;
    cam->viewport[3] = h;
    return EVT_RETURN_DONE;
}


#pragma explicit_zero_data on
static __declspec(section ".data") s32 aji_17_data_pad = 0;
#pragma explicit_zero_data reset
