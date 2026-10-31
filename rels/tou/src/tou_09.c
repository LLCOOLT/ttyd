// tou_09 (闘技場, Glitz Pit): the side corridor; exits to tou_04 and tou_11; the shut-in "tojikome" scene.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "tou.h"
#include "mario/mario.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"

static EVT_BEGIN(n_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(toile_in)
    SET_VALUE(GSWF(GSWF_TOU04_ARRIVED_FROM_TOILET_A), 0)
    SET_VALUE(GSWF(GSWF_TOU04_ARRIVED_FROM_TOILET_B), 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(toile_out)
    CALL(evt_map_playanim, STRING("anm_mizu"), 0, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_map_playanim, STRING("anm_futa"), 0, 0)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_TOILET1"), LW(0), LW(1), LW(2), 0)
    SET_VALUE(GSWF(GSWF_TOU04_ARRIVED_FROM_TOILET_A), 1)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("R_door_9"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("R_door_9"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_in)
    CALL(evt_mario_set_pos, -235, 12, 135)
    CALL(evt_party_set_pos, 0, -235, 12, 120)
    CALL(evt_party_set_dir, 0, 90, 0)
    SET_FLOAT_VALUE(LW(0), FLOAT(180.0f))
    CALL_CHILD(w_door_close)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        SET_VALUE(LW(0), 2)
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(w_door_close)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -160, 130, FLOAT(150.0f))
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_party_move_pos2, 0, -180, 120, FLOAT(150.0f))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static BeroEntry bero_data[] = {
    {
        "n_bero", // hitName
        1, // type
        4, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_04", // nextMapName
        "s_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_door_close, // enterAnimeArg
        n_door_open, // exitAnimeArg
    },
    {
        "dokan", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        100, // length
        (s32*)toile_in, // enterEvent
        6, // caseType
        (s32*)toile_out, // exitEvent
        "tou_04", // nextMapName
        "toire", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "a_door_9_omote", // hitName
        1, // type
        16, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_in, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_11", // nextMapName
        "e_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_door_close, // enterAnimeArg
        w_door_open, // exitAnimeArg
    },
    {0},
};

static EVT_BEGIN(evt_toile)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("t_door_2"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("t_door_3"), 8388608)
    CALL(evt_mario_adjust_dir)
    WAIT_FRAMES(1)
    CALL(evt_mario_dispflag_onoff, 1, MARIO_DISP_FLAG_DIR_LOCK)
#if VERSION >= VERSION_JP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_party_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(10))
    IF_INT_GREATER(LW(10), 100)
        CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    END_IF
#endif
    BEGIN_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
        CALL(evt_party_move_pos2, 0, 210, 100, FLOAT(80.0f))
#else
        CALL(evt_party_move_pos2, 0, 200, 110, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
#endif
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
    CALL(evt_mario_mov_pos2, 210, 115, FLOAT(80.0f))
#else
    CALL(evt_mario_mov_pos2, 200, 130, FLOAT(80.0f))
#endif
    CALL(evt_mario_dispflag_onoff, 0, MARIO_DISP_FLAG_DIR_LOCK)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, -80, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("door_2"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
        CALL(evt_party_move_pos2, 0, 265, 100, FLOAT(80.0f))
#else
        CALL(evt_party_move_pos2, 0, 265, 110, FLOAT(80.0f))
#endif
    END_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
    CALL(evt_mario_mov_pos2, 265, 115, FLOAT(80.0f))
#else
    CALL(evt_mario_mov_pos2, 270, 130, FLOAT(80.0f))
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, -80, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("door_2"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("t_door_2"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("t_door_3"), 8388608)
#if VERSION >= VERSION_JP
    CALL(evt_party_set_pos, 0, 265, 0, 110)
#endif
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_toile2)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("t_door_2"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("t_door_3"), 8388608)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, -80, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("door_2"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 200, 110, FLOAT(80.0f))
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 200, 130, FLOAT(80.0f))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, -80, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("door_2"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("t_door_2"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("t_door_3"), 8388608)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_tojikome_msg)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DOOR_NOTOPEN1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_msg_print_party, STRING("stg3_tou_421_02"))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(tou_09_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG3_00_WELCOME_TO_GLITZVILLE, STORY_STG3_12_MINI_YOSHI_EGG)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
#else
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
#endif
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_GREATER_OR_EQUAL(STORY_STG3_33_PEACH_THE_SECRET_WEAPON)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
#else
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
#endif
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(evt_tou_locker_init)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(bero_case_switch_off)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("n_bero"), 0, PTR(evt_tojikome_msg), 0)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("t_door_2"), 0, PTR(evt_toile), 0)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("t_door_3"), 0, PTR(evt_toile2), 0)
    CALL(evt_hitobj_onoff, STRING("a_door_9_ura"), 1, 0)
    RETURN
EVT_END()
