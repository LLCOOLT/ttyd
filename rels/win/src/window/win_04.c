#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/dispdrv.h"
#include "stdlib.h"
#include "memory.h"
#include "driver/camdrv.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "driver/fadedrv.h"
#include "manager/evtmgr_cmd.h"

typedef struct Flower { s16 state; s16 timer; f32 x; f32 y; f32 scale; f32 targetScale; s32 alpha; } Flower;
typedef struct FlowerWork { s32 count; Flower* flowers; } FlowerWork;
void flower_disp(CameraId camera, void* param);
void envAddTev(s32 type, void* param);
static s32 ssf[3];

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_flower);
USER_FUNC(evt_flower_end);
USER_FUNC(evt_flower_end_main);
USER_FUNC(evt_flower_init);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_position);
USER_FUNC(evt_item_move_3d_position);
USER_FUNC(evt_item_set_position);
USER_FUNC(evt_key_get_button);
USER_FUNC(evt_map_blend_set_flag);
USER_FUNC(evt_map_pauseanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_blend);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_check_key_item);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_dump_item);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_delete);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_dispflg_onoff);
USER_FUNC(evt_party_force_reset_outofscreen);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_set_pose);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_get_value_para);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_win_item_select);
USER_FUNC(fade_alpha);
USER_FUNC(flower_pos_report);
USER_FUNC(ss_ch_check);
USER_FUNC(ss_ch_set);
static f32 randf(f32 min, f32 max);
void flower_disp(CameraId camera, void* param);
void mirror_ball(void* param);
extern s32 all_party_lecture[];
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_win_door_close[];
extern s32 evt_win_door_open[];
extern s32 evt_win_door_open_pure[];

__declspec(section ".data") u64 fd_win_04_negone_one_374;
__declspec(section ".data") s32 fd_win_04_neg_one_382[1];
__declspec(section ".data") s32 fd_win_04___local_PI_383[1];
__declspec(section ".data") s32 fd_win_04___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_win_04_one_negone_373;
__declspec(section ".data") s32 fd_win_04___local_PIO2_384[1];
__declspec(section ".data") s32 fd_win_04_one_381[1];
__declspec(section ".data") u64 fd_win_04_negone_one_360;
__declspec(section ".data") s32 fd_win_04_neg_one_365[1];
__declspec(section ".data") s32 fd_win_04___local_PI_366[1];
__declspec(section ".data") s32 fd_win_04___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_win_04_one_negone_359;
__declspec(section ".data") s32 fd_win_04___local_PIO2_367[1];
__declspec(section ".data") s32 fd_win_04_one_364[1];
__declspec(section ".data") s32 win_04w_door_open[10];
__declspec(section ".data") s32 win_04w_door_close[10];
__declspec(section ".data") s32 win_04e_door_open[10];
__declspec(section ".data") s32 win_04e_door_close[10];
static __declspec(section ".data") s32 out_w_bero[12];
s32 bero_witchtrio[15];
static s32 bero_entry_data[45];
s32 meet_clouda[76];
s32 meet_clouda2[139];
s32 clouda_inai[17];
s32 clouda_irai[444];
s32 clouda_irai_ato[20];
s32 mirror_trans[35];
s32 mirror_rotate[41];
s32 mario_move_wait[63];
s32 dummy1_jump[26];
s32 dummy2_jump[32];
static __declspec(section ".data") s32 item_list[2];
s32 clouda_nakama[1556];
s32 touch_door[39];
s32 mirror_ball_event[18];
static s32 texture_0[1248];
s32 rose_table_direct[165];
s32 rose_table[120];
s32 flower_event[28];
s32 flower_disp_pos[21];
static s32 cloud_toujou[95];
s32 win_04_init_evt[94];

int rand(void);

__declspec(section ".data") u64 fd_win_04_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_win_04_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_win_04___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_win_04___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_win_04_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_win_04___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_win_04_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_win_04_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_win_04_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_win_04___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_win_04___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_win_04_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_win_04___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_win_04_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(win_04w_door_open)
    SET_VALUE(LW(8), STRING("S_doa_w_l"))
    SET_VALUE(LW(9), STRING("S_doa_w_r"))
    SPAWN_EVENT(PTR(evt_win_door_open))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(win_04w_door_close)
    SET_VALUE(LW(8), STRING("S_doa_w_l"))
    SET_VALUE(LW(9), STRING("S_doa_w_r"))
    SPAWN_EVENT(PTR(evt_win_door_close))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(win_04e_door_open)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SPAWN_EVENT(PTR(evt_win_door_open))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(win_04e_door_close)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SPAWN_EVENT(PTR(evt_win_door_close))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(out_w_bero)
    CALL(evt_fade_set_mapchange_type, 0, 2, 500, 1, 500)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

s32 bero_witchtrio[] = {
    (s32)"w_bero", 65536, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)out_w_bero, (s32)"win_00", (s32)"", 262148, (s32)win_04w_door_close, (s32)win_04w_door_open,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65536, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"win_03", (s32)"n_bero", 262148, (s32)win_04w_door_close, (s32)win_04w_door_open, (s32)"e_bero",
    65536, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"win_05", (s32)"w_bero", 262148, (s32)win_04e_door_close, (s32)win_04e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(meet_clouda)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    CALL(evt_party_move_pos2, 1, -110, 0, FLOAT(120.0f))
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_00"), 0, STRING("extparty"))
    CALL(evt_cam3d_evt_set, 186, 202, 539, 186, 106, -3, 500, 11)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -140, 100, 341, -140, 40, -3, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_01"), 0, STRING("extparty"))
    CALL(evt_cam3d_evt_off, 300, 11)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(0), 81)
    SPAWN_EVENT(PTR(meet_clouda2))
    RETURN
EVT_END()

EVT_BEGIN(meet_clouda2)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(0), 150)
            IF_INT_GREATER_OR_EQUAL(LW(1), 50)
                IF_INT_LESS(LW(1), 51)
                    BREAK_LOOP
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(evt_party_force_reset_outofscreen, 0)
        CALL(evt_party_stop, 0)
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), 50)
        IF_INT_LESS(LW(2), 0)
            ADD(LW(2), 50)
            ELSE
            SUBTRACT(LW(2), 50)
        END_IF
        CALL(evt_party_move_pos2, 0, 130, LW(2), FLOAT(120.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_party_force_reset_outofscreen, 1)
    CALL(evt_party_stop, 1)
    CALL(evt_party_get_pos, 1, LW(0), LW(1), LW(2))
    ADD(LW(0), 50)
    IF_INT_LESS(LW(2), 0)
        ADD(LW(2), 50)
        ELSE
        SUBTRACT(LW(2), 50)
    END_IF
    CALL(evt_party_move_pos2, 1, 160, LW(2), FLOAT(120.0f))
    CALL(evt_party_set_dir, 1, 90, 200)
    LOOP(0)
        IS_EVENT_RUNNING(LW(10), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_02"), 0, STRING("extparty"))
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(0), 82)
    RETURN
EVT_END()

EVT_BEGIN(clouda_inai)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_03"), 0, 0)
    CALL(evt_msg_print_party, STRING("stg2_win_e04_04"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(clouda_irai)
    CALL(evt_mario_key_onoff, 0)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(evt_party_force_reset_outofscreen, 0)
        CALL(evt_party_stop, 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_party_move_pos2, 0, 255, LW(2), FLOAT(120.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_party_force_reset_outofscreen, 1)
        CALL(evt_party_stop, 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_party_move_pos2, 1, 225, LW(2), FLOAT(120.0f))
        CALL(evt_party_set_dir, 1, 90, 200)
    END_INLINE_EVENT
    LOOP(0)
        IS_EVENT_RUNNING(LW(10), LW(0))
        IS_EVENT_RUNNING(LW(11), LW(1))
        IF_INT_EQUAL(LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_03"), 0, 0)
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_party_set_dir, 0, 90, -1)
    CALL(evt_party_set_dir, 1, 90, -1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 4, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_mario_dispflag_onoff, 1, 256)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_cam3d_evt_set, 50, 90, 308, 248, 105, 20, 0, 11)
    END_INLINE_EVENT
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_party_move_pos2, 0, 200, 0, FLOAT(120.0f))
        CALL(evt_party_set_dir, 0, 90, -1)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    SET_VALUE(GF(1), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_party_move_pos2, 1, 230, 15, FLOAT(120.0f))
        CALL(evt_party_set_dir, 1, 90, -1)
        SET_VALUE(GF(1), 0)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 240, 0, FLOAT(120.0f))
    WAIT_WHILE(GF(0))
    WAIT_WHILE(GF(1))
    CALL(evt_mario_dispflag_onoff, 0, 256)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_04"), 0, STRING("extparty"))
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_05"), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_06"), 0, STRING("extparty"))
    WAIT_MS(500)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_07"), 0, 0)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg2_win_e05_00_08"))
    WAIT_MS(500)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_09"), 0, 0)
    CALL(evt_cam3d_evt_set, 200, 120, 194, 200, 85, -3, 0, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg2_win_e05_00_10"))
    CALL(evt_cam3d_evt_set, 110, 199, 257, 393, 72, -135, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_11"), 0, 0)
    CALL(evt_cam3d_evt_set, 220, 130, 243, 220, 87, -3, 0, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_12"), 0, STRING("extparty"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_msg_select, 0, STRING("stg2_win_e05_00_12_yn"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_14"), 0, STRING("extparty"))
        ELSE
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1"), LW(0), LW(1), LW(2), 0)
        END_INLINE_EVENT
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(500)
        CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_13"), 0, STRING("extparty"))
    END_IF
    CALL(evt_cam3d_evt_off, 300, 11)
    WAIT_MS(300)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_00_15"), 0, 0)
    SET_VALUE(GSW(0), 83)
    SET_VALUE(GSWF(2681), 1)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(LW(0), STRING("w_bero"))
    CALL_CHILD(PTR(bero_case_switch_off))
    CALL(evt_bero_overwrite, STRING("w_bero"), PTR(bero_witchtrio))
    SET_VALUE(LW(0), STRING("w_bero"))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

EVT_BEGIN(clouda_irai_ato)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e05_19"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(mirror_trans)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_CRAUD_LIGHT2"), 170, 50, 10, LW(9))
    CALL(evt_sub_intpl_msec_init, 0, 0, -100, 1500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        SET_FLOAT_VALUE(GW(1), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_sfxoff, LW(9))
    RETURN
EVT_END()

EVT_BEGIN(mirror_rotate)
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 0, 0, 360, 6000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_trans, 1, STRING("S_mirre"), 0, GW(1), 0)
            CALL(evt_mapobj_rotate, 1, STRING("S_mirre"), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mario_move_wait)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SET_VALUE(LW(6), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        SET_VALUE(LW(3), LW(0))
        SET_VALUE(LW(4), LW(1))
        SET_VALUE(LW(5), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_EQUAL(LW(0), LW(3))
            IF_INT_EQUAL(LW(1), LW(4))
                IF_INT_EQUAL(LW(2), LW(5))
                    ADD(LW(6), 1)
                    IF_INT_GREATER_OR_EQUAL(LW(6), 2)
                        BREAK_LOOP
                    END_IF
                    ELSE
                    SET_VALUE(LW(6), 0)
                END_IF
                ELSE
                SET_VALUE(LW(6), 0)
            END_IF
            ELSE
            SET_VALUE(LW(6), 0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(dummy1_jump)
    CALL(evt_npc_set_position, STRING("dummy1"), LW(0), LW(1), LW(2))
    ADD(LW(0), -90)
    ADD(LW(2), -30)
    CALL(evt_npc_jump_position_nohit, STRING("dummy1"), LW(0), LW(1), LW(2), 800, 100)
    CALL(ss_ch_set, 0, 1)
    RETURN
EVT_END()

EVT_BEGIN(dummy2_jump)
    CALL(evt_party_get_pos, 1, LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("dummy2"), LW(0), LW(1), LW(2))
    ADD(LW(0), -90)
    ADD(LW(2), 30)
    CALL(evt_npc_jump_position_nohit, STRING("dummy2"), LW(0), LW(1), LW(2), 800, 100)
    CALL(ss_ch_set, 1, 1)
    RETURN
EVT_END()

USER_FUNC(ss_ch_check) {
    u64 out; // FAKEMATCH (decomp-permuter): reorders the args[1] load
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    out = args[1];
    evtSetFloat(event, out, ssf[index]);
    return EVT_RETURN_DONE;
}

USER_FUNC(ss_ch_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    ssf[index] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(fade_alpha) {
    s32* args = event->args;
    s32 r = evtGetValue(event, args[0]);
    s32 g = evtGetValue(event, args[1]);
    s32 b = evtGetValue(event, args[2]);
    s32 a = evtGetValue(event, args[3]);

    fadeEntry(13, 0, (GXColor){r, g, b, a});
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") s32 item_list[] = {
    63, -1,
};

EVT_BEGIN(clouda_nakama)
    CALL(evt_npc_flag_onoff, 1, STRING("クラウダ"), 1536)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    CALL(evt_win_item_select, 0, PTR(item_list), LW(0), 0)
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_toge, 2, 350, 100, 0)
        CALL(evt_msg_print, 0, STRING("stg2_win_e09_00_01"), 0, 0)
        CALL(evt_party_run, 0)
        CALL(evt_party_run, 1)
        CALL(evt_mario_key_onoff, 1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_cam3d_evt_set, 186, 201, 538, 186, 106, -3, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_00"), 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_dispflag_onoff, 1, 256)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, 255, LW(2), FLOAT(120.0f))
    CALL(evt_item_entry, STRING("necklace"), 63, 0, -1000, 0, 16, -1, 0)
    CALL(evt_item_flag_on, STRING("necklace"), 2)
    CALL(evt_item_set_position, STRING("necklace"), 280, 50, 0)
    CALL(evt_mario_dump_item, 63)
    CALL(evt_snd_bgmoff, 512)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 185, -20, FLOAT(120.0f))
        CALL(evt_party_set_dir, 0, 90, -1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 1, 210, -25, FLOAT(120.0f))
        CALL(evt_party_set_dir, 1, 90, -1)
    END_INLINE_EVENT
    CALL(evt_mario_dispflag_onoff, 0, 256)
    CALL(evt_mario_mov_pos2, 150, 0, FLOAT(120.0f))
    CALL_CHILD(PTR(mario_move_wait))
    CALL(evt_mario_set_dir, 90, 200, 0)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 500)
    SPAWN_EVENT(PTR(evt_win_door_open_pure))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_item_get_position, STRING("necklace"), LW(0), LW(1), LW(2))
        ADD(LW(0), 50)
        CALL(evt_item_move_3d_position, STRING("necklace"), LW(0), LW(1), LW(2), 500, 0)
        CALL(evt_item_set_position, STRING("necklace"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SET_VALUE(LW(0), 1)
    SET_VALUE(LW(1), 500)
    SPAWN_EVENT(PTR(evt_win_door_open_pure))
    WAIT_MS(1500)
    CALL(evt_msg_toge, 2, 350, 100, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_01"), 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_CRAUD_LIGHT1"), 170, 50, 10, LW(9))
        CALL(evt_sub_intpl_msec_init, 0, 0, 100, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_trans, 1, STRING("S_syan"), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_snd_sfxoff, LW(9))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 0, 0, 120, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(fade_alpha, 0, 0, 0, LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_party_set_dir, 1, 270, -1)
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_QUESTION1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 1, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 1, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_eff_fukidashi, 4, STRING(""), 0, 1, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_mario_set_pose, STRING("M_N_3"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 175, 150, 297, 175, 155, -3, 1000, 11)
    WAIT_MS(1000)
    SET_VALUE(GW(1), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S"), 2048)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("hika_"), 2048)
        CALL(evt_map_blend_set_flag, 1, STRING("mario"), 2048)
        CALL(evt_map_blend_set_flag, 1, STRING("party"), 2048)
        CALL(evt_map_blend_set_flag, 1, STRING("extparty"), 2048)
        CALL(evt_map_blend_set_flag, 1, STRING("クラウダ"), 2048)
        CALL(evt_map_set_blend, 0, 255, 255, 255, 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("hika_"), 1)
        CALL(evt_map_playanim, STRING("kirakira"), 1, 0)
        CALL(evt_sub_intpl_msec_init, 0, 0, 255, 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_map_set_blend, 0, 255, 255, 255, LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        SPAWN_EVENT(PTR(mirror_ball_event))
        SPAWN_EVENT_GET_ID(PTR(mirror_rotate), GW(10))
        CALL_CHILD(PTR(mirror_trans))
        WAIT_MS(500)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1500)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_CLOUDA1"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 0, 0, 1000, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), 1000)
            SET_VALUE(LW(2), 200)
            SET_VALUE(LW(3), 40)
            SET_VALUE(LW(4), 120)
            MULTIPLY_FLOAT(LW(2), LW(0))
            MULTIPLY_FLOAT(LW(3), LW(0))
            MULTIPLY_FLOAT(LW(4), LW(0))
            CALL(fade_alpha, LW(2), LW(3), LW(4), 120)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(1000)
    WAIT_WHILE(GF(0))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 110, 128, 307, 250, 110, 5, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_set_dir, 1, 90, -1)
    CALL(evt_npc_set_ry, STRING("クラウダ"), 270)
    CALL(evt_npc_set_position, STRING("クラウダ"), 350, 50, 0)
    WAIT_MS(300)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 500)
    SPAWN_EVENT(PTR(evt_win_door_open_pure))
    WAIT_MS(1500)
    CALL(evt_cam3d_evt_set, 272, 75, 175, 272, 75, -1, 0, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("クラウダ"), 1073741824)
        CALL(evt_npc_flag_onoff, 0, STRING("クラウダ"), 1536)
        CALL(evt_npc_move_position, STRING("クラウダ"), 270, 0, 0, FLOAT(30.0f), 0)
        SET_VALUE(LW(8), STRING("S_doa_e_l"))
        SET_VALUE(LW(9), STRING("S_doa_e_r"))
        SET_VALUE(LW(0), 1)
        SET_VALUE(LW(1), 500)
        SPAWN_EVENT(PTR(evt_win_door_open_pure))
        WAIT_MS(500)
    END_INLINE_EVENT
    WAIT_MS(2000)
    SPAWN_EVENT(PTR(flower_event))
    WAIT_MS(2500)
    CALL(evt_npc_set_anim, STRING("クラウダ"), STRING("PWD_A_7"))
    CALL(evt_npc_get_position, STRING("クラウダ"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_CRAUD_WINK1"), LW(0), LW(1), LW(2), 0)
    ADD(LW(0), -15)
    ADD(LW(1), 25)
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("kiss"), 2, LW(0), LW(1), LW(2), -45, 0, 0, 0, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 0, 100, 0, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_trans, 1, STRING("S_syan"), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(1000)
    SET_VALUE(GW(0), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("hika_"), 1)
    CALL(evt_map_pauseanim, 0, STRING("kirakira"))
    CALL(evt_mapobj_trans, 1, STRING("S_mirre"), 0, 100, 0)
    DELETE_EVENT(GW(10))
    CALL(fade_alpha, 0, 0, 0, 0)
    CALL(evt_cam3d_evt_set, 225, 170, 391, 225, 100, -3, 0, 11)
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_party_dispflg_onoff, 0, 16, 1)
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), -15)
        CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 90, -1)
        CALL(evt_party_dispflg_onoff, 0, 16, 0)
    END_INLINE_EVENT
    CALL(evt_party_dispflg_onoff, 1, 16, 1)
    CALL(evt_party_get_pos, 1, LW(0), LW(1), LW(2))
    ADD(LW(0), -25)
    CALL(evt_party_move_pos2, 1, LW(0), LW(2), FLOAT(80.0f))
    CALL(evt_party_set_dir, 1, 90, -1)
    CALL(evt_party_dispflg_onoff, 1, 16, 0)
    WAIT_MS(700)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("クラウダ"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_npc_flag_onoff, 1, STRING("クラウダ"), 1536)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_02"), 0, STRING("クラウダ"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_QUESTION1_2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_I_G"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 270, 134, 245, 270, 90, -1, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_03"), 0, STRING("クラウダ"))
    CALL(evt_cam3d_evt_set, 150, 134, 245, 150, 90, -1, 0, 11)
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_N_C"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 270, 134, 245, 270, 90, -1, 0, 11)
    CALL(evt_npc_get_position, STRING("クラウダ"), LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_05"), 0, STRING("クラウダ"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_set_pose, STRING("M_N_7"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_entry, STRING("dummy1"), STRING("c_pguide"))
        CALL(evt_npc_flag_onoff, 1, STRING("dummy1"), 32)
        CALL(evt_npc_flag_onoff, 1, STRING("dummy1"), 128)
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_set_position, STRING("dummy1"), LW(0), LW(1), LW(2))
        CALL(evt_party_cont_onoff, 0, 0)
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), 30)
        LOOP(0)
            CALL(evt_npc_get_position, STRING("クラウダ"), LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(3), LW(0))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_CRAUD_ATTACK1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_party_set_dir, 0, 270, -1)
        CALL(evt_mario_get_party, LW(10))
        SWITCH(LW(10))
            CASE_EQUAL(1)
            CALL(evt_party_set_pose, 0, STRING("PKR_R_1"))
            CASE_EQUAL(2)
            CALL(evt_party_set_pose, 0, STRING("PNK_D_1"))
        END_SWITCH
        CALL(ss_ch_set, 0, 0)
        SPAWN_EVENT(PTR(dummy1_jump))
        LOOP(0)
            CALL(evt_npc_get_position, STRING("dummy1"), LW(0), LW(1), LW(2))
            CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
            CALL(ss_ch_check, 0, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SWITCH(LW(10))
            CASE_EQUAL(1)
            CALL(evt_party_set_pose, 0, STRING("PKR_D_4"))
            CASE_EQUAL(2)
            CALL(evt_party_set_pose, 0, STRING("PNK_D_4"))
        END_SWITCH
        CALL(evt_npc_delete, STRING("dummy1"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_entry, STRING("dummy2"), STRING("c_pguide"))
        CALL(evt_npc_flag_onoff, 1, STRING("dummy2"), 32)
        CALL(evt_npc_flag_onoff, 1, STRING("dummy2"), 128)
        CALL(evt_party_get_pos, 1, LW(0), LW(1), LW(2))
        CALL(evt_npc_set_position, STRING("dummy2"), LW(0), LW(1), LW(2))
        CALL(evt_party_cont_onoff, 1, 0)
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), 30)
        LOOP(0)
            CALL(evt_npc_get_position, STRING("クラウダ"), LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(3), LW(0))
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_party_set_dir, 1, 270, -1)
        CALL(evt_party_set_pose, 1, STRING("R_1"))
        CALL(ss_ch_set, 1, 0)
        SPAWN_EVENT(PTR(dummy2_jump))
        LOOP(0)
            CALL(evt_npc_get_position, STRING("dummy2"), LW(0), LW(1), LW(2))
            CALL(evt_party_set_pos, 1, LW(0), LW(1), LW(2))
            CALL(ss_ch_check, 1, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_party_set_pose, 1, STRING("D_2"))
        CALL(evt_npc_delete, STRING("dummy2"))
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 150, 143, 292, 150, 90, -3, 300, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 20)
    ADD(LW(1), 5)
    ADD(LW(2), -3)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_jump_position_nohit, STRING("クラウダ"), LW(0), LW(1), LW(2), 500, 1)
    END_INLINE_EVENT
    WAIT_MS(100)
    CALL(evt_npc_set_anim, STRING("クラウダ"), STRING("PWD_A3_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("クラウダ"), STRING("PWD_A3_2"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_CRAUD_KISS1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1000)
    ADD(LW(0), 5)
    ADD(LW(1), 30)
    CALL(evt_eff, 0, STRING("kiss"), 2, LW(0), LW(1), LW(2), -45, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1700)
    CALL(evt_npc_set_anim, STRING("クラウダ"), STRING("PWD_A3_3"))
    CALL(ss_ch_set, 2, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_DOWN1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_I_S"))
        WAIT_MS(2000)
        CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_FALL_CRUSH1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_D_2"))
        WAIT_MS(1000)
        CALL(ss_ch_set, 2, 1)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, FLOAT(165.19922f), FLOAT(143.0f), FLOAT(292.0f), FLOAT(165.19922f), FLOAT(90.0f), FLOAT(-3.0f), 500, 11)
    CALL(evt_npc_flag_onoff, 0, STRING("クラウダ"), 1536)
    CALL(evt_npc_jump_position_nohit, STRING("クラウダ"), 205, 50, 0, 500, 1)
    CALL(evt_npc_set_anim, STRING("クラウダ"), STRING("PWD_S_1"))
    LOOP(0)
        CALL(ss_ch_check, 2, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING("クラウダ"), 1536)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_06"), 0, STRING("クラウダ"))
    CALL(evt_mario_set_pose, STRING("M_U_3"))
    WAIT_MS(650)
    CALL(evt_mario_set_pose, STRING("M_N_C"))
    WAIT_MS(400)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_MS(500)
    CALL(evt_party_set_dir, 0, 90, -1)
    CALL(evt_mario_get_party, LW(10))
    SWITCH(LW(10))
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING("PKR_S_1"))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING("PNK_S_1"))
    END_SWITCH
    CALL(evt_party_set_dir, 1, 90, -1)
    CALL(evt_party_set_pose, 1, STRING("S_1"))
    CALL(evt_party_cont_onoff, 0, 1)
    CALL(evt_party_cont_onoff, 1, 1)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_07"), 0, STRING("クラウダ"))
    CALL(evt_mario_set_pose, STRING("M_I_N"))
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 205, 143, 292, 205, 90, -3, 500, 0)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_07_01"), 0, STRING("クラウダ"))
    CALL(evt_npc_set_anim, STRING("クラウダ"), STRING("PWD_A_7"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    WAIT_MS(1000)
    WAIT_MS(500)
    SET_VALUE(LW(8), STRING("クラウダ"))
    SET_VALUE(LW(9), 5)
    CALL_CHILD(PTR(all_party_lecture))
    CALL(evt_party_move_pos2, 1, 148, 30, FLOAT(120.0f))
    CALL(evt_msg_print, 0, STRING("stg2_win_e09_09"), 0, STRING("extparty"))
    CALL(evt_cam3d_evt_off, 300, 11)
    SET_VALUE(GSWF(2682), 1)
    SET_VALUE(GSW(0), 87)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_WIN1"))
    CALL(evt_snd_bgmoff, 22528)
    CALL(evt_snd_envon, 272, STRING("ENV_STG2_WIN2"))
    CALL(evt_snd_env_lpf, 0, 800)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(touch_door)
    SWITCH(GSW(0))
        CASE_LESS(82)
        CALL_CHILD(PTR(clouda_inai))
        CASE_EQUAL(82)
        CALL_CHILD(PTR(clouda_irai))
        CASE_BETWEEN(83, 85)
        CALL_CHILD(PTR(clouda_irai_ato))
        CASE_EQUAL(86)
        CALL(evt_mario_check_key_item, 63, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(clouda_irai_ato))
            ELSE
            CALL_CHILD(PTR(clouda_nakama))
            IF_INT_EQUAL(LW(0), 1)
                CALL(evt_exit_case_evt)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(mirror_ball_event)
    CALL(evt_map_set_tevcallback, 1, PTR(mirror_ball))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_mirre"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_mirre"), 256)
    RETURN
EVT_END()

static s32 texture_0[] = {
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    2017569580, -8309, 1, -1, -195591933, 1438871632, 2019675025, -1087438199,
    1, -1, -1847092695, -2, -2130384012, -8388523, -344686365, -715341824,
    -2130474747, -86, 1879087624, -87, -2130384011, 5592405, -2130384011, 5592405,
    1, -1, 1, -1, 1889657715, 193091670, 2013303304, -32982,
    1, -1, 2013303304, -141239, 2019675025, -17268215, 1614867284, 630543701,
    -1996166315, -16777131, -2132548813, -16646058, -348853676, 142253, -353048141, 2797557,
    2013303304, -22623, 1, -1, -94988025, 218147498, 1879093739, -1622515615,
    -1847092695, -2, -2130400533, -209, -195594045, -715341824, 2023939092, 191860527,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    -1991902121, 96584129, -340428541, 808505424, -2136806379, -1042222864, -344620829, 1349533888,
    -342496428, -1431655765, -344593612, 141989, -344593676, 666541, -350950893, 142253,
    -346690828, 699381, -346756428, 11190101, -357242574, 700405, -363599662, 11206485,
    -351053824, 133391, -478912512, -547323904, -80246588, -1214982956, -344593644, 170634157,
    -346789567, -1073741824, -348853741, 34220973, -348853676, 170634677, -361436942, 170634677,
    -361436910, 36416949, -376182703, 179305941, -382541775, 187545045, -533608433, 179541,
    -260925081, -1442774783, -195596159, -596623168, -804292157, 118427405, -61344680, -1431655766,
    -195594046, 50400517, 1879087624, -1077968897, 1887562806, 1650676320, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    -2132548748, -490618431, -344593644, 170601389, -2130384044, -1044266559, -346756460, 187379117,
    -348853709, 170634677, -363601742, 170634677, -361438991, 187379125, -248264657, 766891349,
    -382478288, 179303765, 1268834385, 1431655766, -1072856669, 1818, -1744399640, 952306736,
    -491552766, -50858021, -1473537273, 2058010624, -1070691867, -805306361, -1070693948, 491472,
    -1207076446, -33685248, -661550618, -2143236044, -1070761565, 4259614, -1878684953, 856334338,
    -665796593, 768955733, -936460273, -1, -1072854555, 122439, -1979346938, 710567313,
    -1341414518, 218827274, -61344680, -1431655766, -1878684953, -903684082, -61380512, 49264,
    -1989804969, 1347437379, 1, -1, -1991902121, 1396917059, 2013303304, -150,
    1, -1, 1, -1, -2130474747, -86, -2130400533, -209,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, -1847092695, -2,
    -2130455759, -504172296, -353054512, 34277645, 2023938899, -50823131, -353150976, -8421376,
    -512573425, 766858581, -1072789019, 67085, -493725632, -16973312, -342587228, 1952206960,
    -615356416, -1787326705, -1070628124, -1073741824, -478978048, 252644647, -2113560568, 1414637206,
    -1207139933, 219966700, -1070628124, 3, -342525758, 1473053440, -887982079, -102310756,
    -900497406, -1206955, -1861847040, 1381258497, -344620829, 1426915587, -481075200, 50563446,
    -1204977212, 4231332, -1204979294, 420417295, -615288832, 1600054019, -888047616, -403317405,
    -934232018, -1, -195587898, 1355837532, -1070628413, 4243648, -617453568, -140643341,
    -61241180, 353837023, -359364348, 1426063488, -523147168, 1886417008, -363599630, -520585634,
    -2130384076, 5592405, -481075200, -567475712, -350950861, -2132776840, -344593612, -1595381656,
    2013311983, -4247669, 1, -1, 1612770196, 1649956437, 2013311983, -4247669,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    -1847092695, -2, 1746983795, -119371483, 1879089674, -184888859, -357256757, 1073742378,
    -353066518, 1073741826, -357242542, 34254773, -359339726, 170638837, -378279823, 187545045,
    -376209116, 50397441, -344686365, 1078152517, -399418912, 50529024, -615354368, 1985763568,
    1612770196, -1994025643, 1885399924, 1616402005, -342561931, -1, -342561931, -1,
    -342525758, 12611792, -342525758, 339152131, -344686333, 473171717, -342561931, -1,
    -344622845, 49216, -615356416, -655302698, -615356416, -526437066, 1885465460, 153458005,
    -342525758, 903311360, -344626879, -1023410176, -342561931, -1, -344622813, 13,
    -1557487608, 1710601773, -344688349, 1941979200, 1883300756, 1348634917, -344626879, -1073741824,
    -533692124, -800042892, -378279823, 2021154398, -1599542411, 1077952576, -390930383, 2019319390,
    -357242510, -522160008, -346756364, -522162056, -365696814, -528975752, -348853612, -529500040,
    -342496428, -353703190, 1887560564, 1130518614, -342496428, -92636550, -342561931, -1,
    2013311983, -16593, 1, -1, 1751180180, -1956489130, 1, -1,
    2013303304, -2351, -2130384140, -8388523, -2132483245, -1044188929, 1757602547, 1432978168,
    -500017056, -1335853056, -369891150, 36421077, -239824698, 34212693, -667901431, -2147483584,
    -380442543, 196080981, -401481615, 2062067872, -399386608, 44755551, -401481711, -1431655681,
    -401483760, 133165, -344686333, 1349533888, 1407244304, 1448498517, -350977788, 1077964880,
    -342496428, -1431655682, -342561931, -161, -346756396, 8448639, -344593612, 10549854,
    -344622910, 218170112, -481075200, -2134875427, -342496428, -1431639425, -344620796, -721420288,
    -478980096, -1729077056, -342561931, -1, 1619321748, 159537238, 1082452853, 1431672102,
    1480649620, 1431722082, -346785565, -714031104, -353076923, 483422272, -353048109, 2797525,
    -348886686, -1073741824, -344593612, 11074135, -355145293, 11206485, -350950925, 10549854,
    -1731662987, 1077952576, -399390705, -530554768, -1154508790, 1027422645, -533612531, -522133280,
    -371988335, 2021161080, -348853709, 1752725624, -374085519, 2021161080, -350950861, 2021161080,
    -344593612, -1595873056, -342561931, -1, -344593612, 1751673056, -342561931, -1,
    2028200820, 1481658971, 1, -1, 2026101618, 1665370895, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    2013303304, 1087567613, -195594013, 1463092080, 1, -1, 2023941141, -2050375040,
    -1207131286, 12627059, -535705585, -2105715371, -61380512, 218300416, -1341416600, -1065293189,
    -804280275, 715827882, -1072848406, -176474596, -327831477, 1431696643, -1207144064, 219151103,
    -357246800, 8448634, -350950861, 10549855, -1072782872, 184697012, -369899473, 14704213,
    -346756396, 11075159, -344593644, -2002059689, -361438991, 11070047, -355145261, 11075413,
    -344593612, 10676821, -481013726, -1657864192, -350950893, 11206485, -350950893, 11206485,
    -216694523, 1247687939, -802174481, 2146058256, -350950893, 11075159, -1026648056, -1254539994,
    -105656272, -1426107051, -638466001, -2132247465, -936460273, -1, -1475771674, 201995212,
    -1072797244, -254754624, -395130865, 2054715512, -1844920306, 357913941, -248262609, 1583249528,
    -369891182, 2021161184, -348853676, 2021161192, -359339662, 1584953568, -346756428, 2021189792,
    -344593580, 2020108392, -344622878, 199941, -342496428, 2063268586, -2132548748, 1347445315,
    -2130400533, 792707071, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    2013303304, -131330, -344686332, 1900102464, 2013303304, -184878342, -344626879, -1073741824,
    -195594046, -1069523755, -61382464, 192, -353076957, 218103808, -69627771, 1557642685,
    -61344680, -1431655766, -61344680, -1431655766, -195594046, 28887, -61344680, -1431655766,
    -195591933, -721223680, -195651448, -715311869, -61344680, -1431655766, -61344680, -1431655766,
    -1072786969, 33570960, -380385265, 16406357, -195592061, -583594752, -1207006780, 62589,
    -376186832, 11206485, -378281903, 11206485, -1072791100, 244, -802111474, -1593878699,
    -376184751, 11206485, -376217472, 252645293, 1675675663, 1431655766, -1072793374, 117769567,
    -1207137818, 17177076, -1072786970, -1874853888, -1072793150, 1073742079, -936418976, 255,
    -523122673, 1431787100, -365698927, 1585113312, -504178608, 1585111040, -350950925, 1585113248,
    -350950893, 2028527744, -344593644, 2028513440, -348882653, 13, -344686365, 13655,
    1612770164, 1431656024, 2023936881, 1267675071, 1885393810, 1653288959, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1879087624, -84476162, -344622845, 49216, -1847092695, -16777217, 1887495028, 354781666,
    -346756396, 757926667, -359346097, 755698178, -344593612, -1389688318, -348853676, -1389688318,
    -936402456, 503415016, -195651449, 1884648789, -357244622, -1246942454, -378286065, -709022966,
    -195589915, 12604789, -2130379689, 1431633920, -395130865, 1440067370, -535709683, -22016,
    -195585849, 3495381, -195594046, 12605397, -535709683, -22016, -535707634, 1414921515,
    -195591965, -720568107, -1962506236, -1786784417, -1207076446, 503514639, -61376351, 1883291648,
    -195591997, -715374507, -61374204, 1426063552, -594309018, -719987339, -1072795231, -14745600,
    -2130379689, 5592405, -2130379689, 5592405, -195649368, -1068141227, -1733755817, 1426063360,
    -61374237, 1440022528, -195596256, -269152971, -67460953, 894795615, -357267196, 1438679168,
    2013303304, -1610479825, 2013311983, 801112063, -2130386124, 256590659, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 2013311984, -117506049, 1, -1, 1, -1,
    2026101619, 621404924, -346791580, 192, -1979084279, -16777217, -344622811, 1086353488,
    -348853612, -1255339262, -359339694, -1255331062, -344593612, -1121252862, -348853612, -1255339520,
    -376182671, -709546230, -386734031, 1440071434, -355145293, -173078016, -359339694, 1442818560,
    -399384334, 43775, -382541775, 1432353440, -374111932, 53, -638488544, 36541783,
    -195653466, 2002050256, -193497022, 51197917, 2013303304, 167914110, -1328815469, 543839637,
    -936408603, -1069547520, -401487857, 2146074624, -367796047, 1438461706, -380442575, 1442818560,
    -399386608, 1442818720, -386736079, 1431797496, -376182671, 1432353440, -365696814, 1467934848,
    -365696846, 1585117408, -348853676, 2021189856, -225146619, -1602223915, -348956672, 132029,
    -2130451661, 1128483727, 1, -1, 2013303304, -1356873793, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1889657716, -2050366983, 1, -1, -1847092695, -83951617,
    -344626879, 3, -346793984, 12255, 2026036082, 1476571135, -2130400533, 805306367,
    2026040084, 1431634443, 2028135155, 1449165055, 1, -1, 1, -1,
    2013303304, -2146787329, 2013303304, 662700031, 1, -1, 1, -1,
    -1847092695, -16777217, 2028196593, 165738751, 1, -1, 1, -1,
    -495822784, 8421311, -2130384365, 1431633920, 1, -1, 1, -1,
    -2130384365, 1431633920, 1879093772, 1449142911, 1, -1, 1, -1,
    2013303304, 33598207, 2023940979, 1620312288, 1, -1, -1847092695, -16777217,
    2013303304, -1077993681, 1, -1, 2013303305, 794820607, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 1, -1, 1, -1,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
    1, -1, 1, -1, 0, 0, 0, 0,
};

s32 rose_table_direct[] = {
    -1018913751, 1130360996, 1061662228, -1022521508, 1130065428, 1061326684, -1030568018, 1131161190,
    1060320051, -1045451244, 1131591107, 1060320051, 1118817485, 1131504599, 1065017672, 1124462100,
    1130342646, 1062668861, 1127029801, 1129812460, 1061662228, -1024560988, -1017777357, 1062836634,
    -1030852444, -1016860508, 1062333317, -1044696269, -1017636454, 1061158912, 1106058936, -1017195397,
    1061326684, 1123969925, -1016464671, 1062165545, 1128288748, -1018226278, 1060655596, -1019009434,
    -1020027863, 1064682127, -1029071176, -1020676014, 1064346583, -1043579535, -1021584343, 1061830001,
    1107508593, -1020379136, 1060991140, 1118569759, -1021620388, 1062333317, 1128052163, -1021508977,
    1062668861, -1016988303, 1130928538, 1060487823, -1015123804, 1119837225, 1061158912, -1015655301,
    1108122010, 1064011039, -1015708385, -1038006354, 1063172178, -1016745820, -1028116972, 1062668861,
    -1015866982, -1017768837, 1064514355, 1131490181, 1129817702, 1064514355, 1132306760, 1125728911,
    1064178811, 1131609457, 1121103380, 1060823368, 1132236636, 1102734950, 1063004406, 1131582587,
    -1028857528, 1062668861, 1131348623, -1021543711, 1062668861, 1131916820, -1018222346, 1060823368,
    -1014214492, 1126494372, 1060991140, -1014077194, 1119526584, 1065017672, -1014127985, -1047018865,
    1063172178, -1014622454, -1027612344, 1060823368, -1014533652, -1022292787, 1064346583, -1013828813,
    -1016956846, 1062668861, 1133100073, 1131256873, 1064178811, 1133529989, 1125957632, 1063675494,
    1133531955, 1121680097, 1065185444, 1133329777, -1051732214, 1060320051, 1132857917, -1030067323,
    1060823368, 1132871025, -1022531338, 1064346583, -1019487191, 1132903793, 1061662228, -1019989197,
    -1015684792, 1060655596, 1128307753, -1014693888, 1064011039, -1020265103, 1127913882, 1061997773,
    -1018504151, 1125302272, 1065353216, 1128082309, 1127392870, 1064514355, 1129488712, 1123058975,
    1064178811, 1131127112, 1117816095, 1061997773, -1020616376, -1024424673, 1064178811, 1128112456,
    -1027046113, 1063675494, 1127063880, -1023769313, 1060655596,
};

s32 rose_table[] = {
    -1019565397, 1130758144, -1023060650, 1130758144, -1029701632, 1130758144, -1042983592, 1130758144,
    1104500048, 1130758144, 1117782016, 1130758144, 1124422998, 1130758144, 1127918250, 1130758144,
    -1019565397, -1017380864, -1023060650, -1017380864, -1029701632, -1017380864, -1042983592, -1017380864,
    1104500048, -1017380864, 1117782016, -1017380864, 1124422998, -1017380864, 1127918250, -1017380864,
    -1019565397, -1020657664, -1023060650, -1020657664, -1029701632, -1020657664, -1042983592, -1020657664,
    1104500048, -1020657664, 1117782016, -1020657664, 1124422998, -1020657664, 1127918250, -1020657664,
    -1016070144, 1130758144, -1016070144, 1126545116, -1016070144, 1120590702, -1016070144, 1108644424,
    -1016070144, -1042733936, -1016070144, -1028203668, -1016070144, -1021593892, -1016070144, -1017380864,
    1131413504, 1130758144, 1131413504, 1126545116, 1131413504, 1120590702, 1131413504, 1108644424,
    1131413504, -1042733936, 1131413504, -1028203668, 1131413504, -1021593892, 1131413504, -1017380864,
    -1014235136, 1130758144, -1014235136, 1126545116, -1014235136, 1120590702, -1014235136, 1108644424,
    -1014235136, -1042733936, -1014235136, -1028203668, -1014235136, -1021593892, -1014235136, -1017380864,
    1133248512, 1130758144, 1133248512, 1126545116, 1133248512, 1120590702, 1133248512, 1108644424,
    1133248512, -1042733936, 1133248512, -1028203668, 1133248512, -1021593892, 1133248512, -1017380864,
    -1019346944, 1132920832, -1019346944, -1014890496, 1128136704, 1132920832, 1128136704, -1014890496,
};

EVT_BEGIN(flower_event)
    SET_VALUE(GW(0), 0)
    CALL(evt_flower_init)
    LOOP(0)
        CALL(evt_flower)
        IF_INT_EQUAL(GW(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_flower_end)
    LOOP(0)
        CALL(evt_flower_end_main)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(flower_disp_pos)
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(evt_key_get_button, 0, LW(0))
        AND_RAW(LW(0), 256)
        IF_INT_NOT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(flower_pos_report)
    RETURN
EVT_END()

void mirror_ball(void* param) {
    envAddTev(10, param);
}

void flower_disp(CameraId camera, void* param) {
    FlowerWork* wp = param;
    CameraEntry* cam = camGetPtr(camera);
    GXTexObj tex;
    Mtx trans;
    Mtx scale;
    Mtx mtx;
    f32 w;
    f32 h;
    Flower* fl;
    s32 i;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXInitTexObj(&tex, texture_0, 101, 92, GX_TF_CMPR, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    w = 101.0f;
    h = 92.0f;
    for (i = 0, fl = wp->flowers; i < wp->count; i++, fl++) {
        GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, fl->alpha});
        PSMTXTrans(trans, fl->x, fl->y, 0.0f);
        PSMTXScale(scale, fl->scale, fl->scale, fl->scale);
        PSMTXConcat(cam->view, trans, mtx);
        PSMTXConcat(mtx, scale, mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-w / 2, h / 2, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(-w / 2, -h / 2, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXPosition3f32(w / 2, -h / 2, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(w / 2, h / 2, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXEnd();
    }
}

static EVT_BEGIN(cloud_toujou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_cam3d_evt_set, 75, 205, 539, 75, 110, -3, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_00_02"), 0, 0)
    CALL(evt_cam3d_evt_set, 60, 120, 352, 276, 120, 15, 0, 11)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 300, 80, 40)
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_00_03"), 0, 0)
    CALL(evt_fade_set_mapchange_type, 0, 2, 500, 1, 500)
    CALL(evt_bero_mapchange, STRING("win_05"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(win_04_init_evt)
    SET_VALUE(GSWF(253), 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_WIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG2_WIN2"))
    CALL(evt_snd_bgmoff, 22528)
    CALL(evt_snd_env_lpf, 0, 800)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -125, 60, -95, 0, 0)
    IF_INT_EQUAL(GSW(0), 80)
        SPAWN_EVENT(PTR(meet_clouda))
    END_IF
    IF_INT_EQUAL(GSW(0), 81)
        SPAWN_EVENT(PTR(meet_clouda2))
    END_IF
    IF_INT_EQUAL(GSW(0), 83)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("w_bero"), PTR(bero_witchtrio))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
    END_IF
    IF_INT_LESS_OR_EQUAL(GSW(0), 86)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_run_case_evt, 9, 1, STRING("e_bero"), 0, PTR(touch_door), 0)
    END_IF
    IF_INT_EQUAL(GSW(0), 76)
        SPAWN_EVENT(PTR(cloud_toujou))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("hika_"), 1)
    RETURN
EVT_END()

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return (max - min) * r + min;
}

USER_FUNC(evt_flower_init) {
    FlowerWork* wp = _mapAlloc(sizeof(FlowerWork));

    wp->count = 55;
    wp->flowers = _mapAlloc(wp->count * sizeof(Flower));
    event->lwData[10] = (s32)wp;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_flower) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    Flower* fl = wp->flowers;
    s32 i;

    for (i = 0; i < wp->count; i++, fl++) {
        switch (fl->state) {
            case 0:
                fl->timer = rand() % 100;
                fl->state++;
                break;
            case 1:
                if (--fl->timer < 0) {
                    fl->x = ((Vec*)rose_table_direct)[i].x;
                    fl->y = ((Vec*)rose_table_direct)[i].y;
                    fl->targetScale = ((Vec*)rose_table_direct)[i].z;
                    fl->scale = 0.0f;
                    fl->state++;
                }
                break;
            case 2:
                if (fl->scale < fl->targetScale) {
                    fl->scale += 0.08f;
                } else {
                    fl->timer = 0;
                    fl->state++;
                }
                fl->alpha += 20;
                if (fl->alpha > 255) {
                    fl->alpha = 255;
                }
                break;
        }
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, flower_disp, wp);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_flower_end) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    Flower* fl = wp->flowers;
    s32 i;

    for (i = 0; i < wp->count; i++, fl++) {
        fl->state = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_flower_end_main) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    Flower* fl = wp->flowers;
    s32 i;

    for (i = 0; i < wp->count; i++, fl++) {
        switch (fl->state) {
            case 0:
                fl->alpha -= 10;
                if (fl->alpha < 0) {
                    fl->alpha = 0;
                    fl->state++;
                }
                break;
            case 1:
                break;
        }
    }
    dispEntry(CAMERA_2D, 1000.0f, 0, flower_disp, wp);
    return EVT_RETURN_DONE;
}

USER_FUNC(flower_pos_report) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    s32 i;

    for (i = 0; i < wp->count; i++) {
    }
    return EVT_RETURN_DONE;
}
