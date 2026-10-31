// aji_15 (敵のアジト, X-Naut Fortress): the shower room where Peach takes a shower (peach_evt_syawa_main).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "mario/mario.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "aji.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/casedrv.h"

static USER_FUNC(peach_chk_aftershower);
static USER_FUNC(peach_set_pos);

static BeroEntry bero_entry_data[2];
extern EvtWord peach_evt_yuge[];
extern EvtWord peach_evt_syawa_main[];
extern EvtWord peach_evt_syawa_init[];

/**
 * Door close animation step: moves the two door leaves S_door1_1
 * and S_door1_2 in opposite directions along Z by the animation value in LW(0) times -0.22167969;
 * the open and close scripts apply the same transform.
 */
static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.22167969f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

/**
 * Door open animation step: moves the two door leaves S_door1_1
 * and S_door1_2 in opposite directions along Z by the animation value in LW(0) times -0.22167969;
 * the open and close scripts apply the same transform.
 */
static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.22167969f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "e_bero", // hitName
        1, // type
        10, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "aji_16", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
    },
    {0},
};

/**
 * Puffs steam (the kemuri_test effect) at random spots above the bath every 0.7 seconds, forever,
 * while Peach is bathing.
 */
EVT_BEGIN(peach_evt_yuge)
    LOOP(0)
        CALL(evt_sub_random, 38, LW(0))
        SUBTRACT(LW(0), 19)
        ADD(LW(0), -30)
        CALL(evt_sub_random, 20, LW(1))
        SUBTRACT(LW(1), 10)
        ADD(LW(1), 60)
        CALL(evt_eff, 0, STRING("kemuri_test"), 1, LW(0), LW(1), -15, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(700)
    END_LOOP
    RETURN
EVT_END()

/** Script function: sets Mario's (Peach's) position directly to the x, y and z floats in args[0] to args[2]. */
static USER_FUNC(peach_set_pos) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    MarioWork* mario = marioGetPtr();

    mario->position = (Vec){x, y, z};
    return EVT_RETURN_DONE;
}

/**
 * Peach's shower scene (case script on the bath A_furo):
 * she steps to the tub (peach_aji_35, or peach_aji_35_1 on a repeat visit), hangs up her clothes,
 * showers humming (SFX_PEACH_SHOWER1, SFX_VOICE_PEACH_HAMMING1 to 3) amid steam, says peach_aji_36 and 37,
 * changes clothes (SFX_PEACH_CHANGE_CLOTH1, evt_peach_set_condition 1) and leaves;
 * GSWF_AJI15_PEACH_SHOWER_TAKEN records that she has showered.
 */
EVT_BEGIN(peach_evt_syawa_main)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(30))
    CALL(evt_snd_envoff, PSND_FADE_HOLD)
    CALL(evt_mario_key_onoff, 0)
    CALL(peach_chk_aftershower, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    ELSE
        CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_2"), STRING("P_T_2"))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI15_PEACH_SHOWER_TAKEN), 0)
        CALL(evt_msg_print, 0, STRING("peach_aji_35"), 0, STRING("mario"))
    ELSE
        CALL(evt_msg_print, 0, STRING("peach_aji_35_1"), 0, STRING("mario"))
    END_IF
    CALL(evt_cam3d_evt_set, -30, 130, 336, -30, 68, -58, 1400, 11)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS_OR_EQUAL(LW(0), -60)
        CALL(evt_mario_mov_pos2, -85, -60, FLOAT(48.0f))
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(0), 0)
        IF_INT_GREATER(LW(2), -10)
            SET_VALUE(LW(0), 30)
            SET_VALUE(LW(2), -15)
            CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(48.0f))
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(0), 25)
        CALL(evt_mario_mov_pos2, 25, -41, FLOAT(48.0f))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -28, -45, FLOAT(48.0f))
    END_INLINE_EVENT
    WAIT_MS(1400)
    CALL(evt_mario_wait_move_end)
    CALL(evt_mario_cont_onoff, 0)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 13, 0, 1000, 300)
        LABEL(20)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(20)
        END_IF
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 13, 1000, 800, 200)
        LABEL(21)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(21)
        END_IF
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 11, -45, -15, 600)
    LABEL(10)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(peach_set_pos, FLOAT(-28.0f), GW(0), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
    CALL(evt_mario_cont_onoff, 1)
    WAIT_MS(800)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_CHANGE_CLOTH1"), LW(0), LW(1), LW(2), LW(3))
    CALL(evt_snd_sfx_dist, LW(3), 0)
    WAIT_MS(1000)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_HANG_CLOTH1"), 0, 0, 0, 0)
    CALL(evt_mapobj_trans, 1, STRING("p_fuku"), 0, -10, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_fuku"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_intpl_msec_init, 0, -10, 0, 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("p_fuku"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_map_playanim, STRING("fuku"), 0, 0)
    CALL(evt_map_checkanim, STRING("fuku"), LW(0), LW(1))
    WAIT_MS(LW(1))
    WAIT_MS(500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_SHOWER1"), -40, 0, -30, 0)
    WAIT_MS(300)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_SHOWER2"), -40, 0, -30, LW(10))
    CALL(evt_sub_intpl_msec_init, 12, FLOAT(0.0f), FLOAT(1.0f), 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_scale, 1, STRING("S_syawa"), LW(0), FLOAT(1.0f), FLOAT(1.0f))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    WAIT_MS(500)
    SPAWN_EVENT_GET_ID(PTR(peach_evt_yuge), LW(9))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_sub_random, 2, LW(3))
    SWITCH(LW(3))
        CASE_EQUAL(0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_HAMMING1"), LW(0), LW(1), LW(2), 0)
        CASE_EQUAL(1)
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_HAMMING2"), LW(0), LW(1), LW(2), 0)
        CASE_EQUAL(2)
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_PEACH_HAMMING3"), LW(0), LW(1), LW(2), 0)
    END_SWITCH
    WAIT_MS(1500)
    CALL(evt_map_set_fog, 2, 900, 1500, 255, 255, 255)
    CALL(evt_map_fog_onoff, 1)
    CALL(evt_sub_intpl_msec_init, 12, 900, 0, 5000)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_map_set_fog, 2, LW(0), 1200, 255, 255, 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("peach_aji_36"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_SHOWER1"), -40, 0, -30, 0)
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_sub_intpl_msec_init, 12, FLOAT(1.0f), FLOAT(0.0f), 500)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_scale, 1, STRING("S_syawa"), LW(0), FLOAT(1.0f), FLOAT(1.0f))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    WAIT_MS(500)
    DELETE_EVENT(LW(9))
    WAIT_MS(1800)
    CALL(evt_sub_intpl_msec_init, 13, 0, 900, 5000)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_map_set_fog, 2, LW(0), 1200, 255, 255, 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_map_fog_onoff, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_HANG_CLOTH1"), 0, 0, 0, 0)
    CALL(evt_map_playanim, STRING("taoru2"), 0, 0)
    CALL(evt_map_checkanim, STRING("taoru2"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_sub_intpl_msec_init, 0, 0, -10, 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("taoru"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("taoru"), MAPOBJ_FLAG_HIDE)
    WAIT_MS(1500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_HANG_CLOTH1"), 0, 0, 0, 0)
    CALL(evt_mapobj_trans, 1, STRING("taoru"), 0, -10, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("taoru"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_intpl_msec_init, 0, -10, 0, 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("taoru"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_map_playanim, STRING("taoru"), 0, 0)
    CALL(evt_map_checkanim, STRING("taoru"), LW(0), LW(1))
    WAIT_MS(LW(1))
    WAIT_MS(800)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_HANG_CLOTH1"), 0, 0, 0, 0)
    CALL(evt_map_playanim, STRING("fuku2"), 0, 0)
    CALL(evt_map_checkanim, STRING("fuku2"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_sub_intpl_msec_init, 0, 0, -10, 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("p_fuku"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_fuku"), MAPOBJ_FLAG_HIDE)
    CALL(evt_snd_sfxon_3d, STRING("SFX_PEACH_CHANGE_CLOTH1"), 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_peach_set_condition, 1)
    CALL(evt_mario_cont_onoff, 0)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 13, 800, 1000, 200)
        LABEL(22)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(22)
        END_IF
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 13, 1000, 0, 300)
        LABEL(23)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(23)
        END_IF
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 11, -15, -45, 600)
    LABEL(11)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(peach_set_pos, FLOAT(-28.0f), GW(0), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(11)
    END_IF
    CALL(evt_mario_cont_onoff, 1)
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 30, 130, 336, 30, 60, -58, 1250, 11)
    CALL(evt_mario_mov_pos2, 30, -45, FLOAT(48.0f))
    CALL(evt_mario_wait_move_end)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_2"), STRING("P_T_2"))
    CALL(evt_msg_print, 0, STRING("peach_aji_37"), 0, STRING("mario"))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("P_S_1"), STRING("P_T_1"))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    SET_VALUE(GSWF(GSWF_AJI15_PEACH_SHOWER_TAKEN), 1)
    CALL(evt_cam3d_evt_off, 800, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Shower room set-up: hides Peach's dress (p_fuku) and the towel,
 * flattens the shower stream and starts its animation.
 * If the player is Peach it removes the partner,
 * plays the towel animation and attaches peach_evt_syawa_main to the bath hit area A_furo;
 * for Mario's visit it stops after the set-up.
 */
EVT_BEGIN(peach_evt_syawa_init)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_fuku"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("taoru"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_scale, 1, STRING("S_syawa"), 0, 1, 1)
    CALL(evt_map_playanim, STRING("syawa"), 1, 0)
    CALL(evt_mario_get_mode, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("taoru"), MAPOBJ_FLAG_HIDE)
    CALL(evt_map_playanim, STRING("taoru"), 0, 0)
    CALL(evt_map_checkanim, STRING("taoru"), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_furo"), 0, PTR(peach_evt_syawa_main), 0)
    RETURN
EVT_END()

/**
 * Init script of aji_15, the shower room: sets up the exits,
 * removes the elite grunt 軍団ザコエリート once Lord Crump is beaten (and during Peach's visit),
 * plays BGM_EVT_PEACH1 with the ambience off, runs the shower room set-up (peach_evt_syawa_init)
 * and records the first entry in GSWF_AJI15_PEACH1_SHOWER_ROOM_ENTERED.
 */
EVT_BEGIN(aji_15_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_npc_check_delete, STRING("軍団ザコエリート"))
    END_IF
    CALL(evt_mario_get_mode, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_mario_set_mode, 1)
        CALL(evt_npc_check_delete, STRING("軍団ザコエリート"))
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_PEACH1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
    ELSE
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_PEACH1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
    END_IF
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 1)
#endif
    CALL_CHILD(peach_evt_syawa_init)
    IF_INT_EQUAL(GSWF(GSWF_AJI15_PEACH1_SHOWER_ROOM_ENTERED), 0)
        SET_VALUE(GSWF(GSWF_AJI15_PEACH1_SHOWER_ROOM_ENTERED), 1)
    END_IF
    SPAWN_EVENT(evt_emergency)
    RETURN
EVT_END()

/**
 * Script function: returns in args[0] whether Peach already has her
 * after-shower state (peachFlags bit 0x10 set) as 1 or 0.
 */
static USER_FUNC(peach_chk_aftershower) {
    EvtWord* args = event->args;

    if (marioGetPtr()->peachFlags & 0x10) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
