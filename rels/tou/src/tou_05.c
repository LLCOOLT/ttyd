// tou_05 (闘技場, Glitz Pit): Grubba's (ガンス) office: match registration and reset, first-league scenes.
// Connects tou_04, tou_06 (storage) and tou_13.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "driver/msgdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_item.h"
#include "evt/evt_npc.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_hit.h"
#include "evt/evt_img.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_paper.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "tou.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "driver/mapdrv.h"
#include "mario/mario.h"

static void gans_msg_callback(s32 type, void** work);

extern EvtWord evt_hiki_open[];
static EvtWord evt_kinoshikowa[222];

/**
 * Entrance script for the air duct: puts Mario and the partner at the duct mouth and walks them out of it.
 * The first time (GSWF_TOU05_DUCT_GRATE_FALLEN clear) the duct grate (haikikau_2) falls off with a clatter,
 * the partner remarks (stg3_tou_456) and the flag is set; the hit object a_haikikan is switched on.
 * Control returns to Mario and LW(0) is set to 1.
 */
static EVT_BEGIN(evt_dakuto)
    CALL(evt_mario_normalize)
    CALL(evt_mario_set_pos, -160, 85, -65)
    CALL(evt_party_set_pos, 0, -160, 85, -70)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_seq_wait, 2)
        IF_INT_EQUAL(GSWF(GSWF_TOU05_DUCT_GRATE_FALLEN), 0)
            CALL(evt_mapobj_get_position, STRING("haikikau_2"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DUCT_KOUSHI_FALL1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("haikikau_2"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_haikikan"), 1, 1)
            WAIT_MS(300)
        END_IF
        CALL(evt_mario_mov_pos, -130, -65, 500)
        CALL(evt_party_move_pos, 0, -130, -70, 500)
        IF_INT_EQUAL(GSWF(GSWF_TOU05_DUCT_GRATE_FALLEN), 0)
            CALL(evt_party_stop, 0)
            WAIT_MS(300)
            CALL(evt_msg_print_party, STRING("stg3_tou_456"))
            WAIT_MS(300)
            CALL(evt_party_run, 0)
            SET_VALUE(GSWF(GSWF_TOU05_DUCT_GRATE_FALLEN), 1)
        END_IF
        CALL(evt_mario_key_onoff, 1)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

/**
 * Door animation callback for the office door (door_1), opening: LW(0) is the swing angle;
 * turns door_1 about the Y axis by 0.44 times the angle.
 */
static EVT_BEGIN(n_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback for the office door (door_1), closing:
 * turns door_1 about the Y axis by -0.44 times the angle.
 */
static EVT_BEGIN(n_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
/**
 * Entrance script: cancels a registered but unplayed match (clears GSWF_TOU_MATCH_RESERVED)
 * when Mario leaves through the door.
 */
EVT_BEGIN(n_bero_match_reset)
    IF_INT_EQUAL(GSWF(GSWF_TOU_MATCH_RESERVED), 1)
        DEBUG_PUT_MSG(STRING("登録していた試合をリセット"))
    END_IF
    SET_VALUE(GSWF(GSWF_TOU_MATCH_RESERVED), 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()
#endif

/** Doors of Grubba's office: the north door back to the corridor (tou_04) and the west door to tou_13. */
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
#if VERSION <= VERSION_DEMO_US
        NULL, // exitEvent
#else
        (s32*)n_bero_match_reset, // exitEvent
#endif
        "tou_04", // nextMapName
        "s_bero_5", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_door_close, // enterAnimeArg
        n_door_open, // exitAnimeArg
    },
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_dakuto, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_13", // nextMapName
        "w_bero_", // nextBeroName
        0, 0, 0, 0, // enterAnimeType..exitAnimeArg
    },
    {0},
};

/**
 * Scene run when Mario opens Grubba's desk drawer (hikidasi_H) before STORY_STG3_31_GRUBBAS_PLANS:
 * the partner spots a paper (stg3_tou_456_01), Mario reads it and is shocked,
 * and the partner explains the blueprints of a machine under the ring powered by a Crystal Star (stg3_tou_458).
 * Grubba (ガンス) comes in, catches Mario with his secret paper (stg3_tou_459),
 * the partner accuses him over King K and Bandy Andy (460),
 * Grubba flees through the door (461) and the partner urges Mario after him (462);
 * the story advances to STORY_STG3_31_GRUBBAS_PLANS and the office door's entrance is switched on.
 */
EVT_BEGIN(evt_takurami)
#if VERSION >= VERSION_JP
    CALL(evt_mario_key_onoff, 0)
#endif
    // The partner spots a paper in the drawer and Mario takes it out.
    CALL(evt_msg_print_party, STRING("stg3_tou_456_01"))
    CALL(evt_party_stop, 0)
    CALL(evt_party_move_pos2, 0, 100, 60, FLOAT(60.0f))
    CALL(evt_party_stop, 0)
    // Mario reads the paper and is shocked; a startled bubble pops up.
    CALL(evt_mario_set_pose, STRING("M_L_2"))
    WAIT_MS(3000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kami_2"), MAPOBJ_FLAG_HIDE)
    // The partner explains the blueprints of a machine under the ring powered by a Crystal Star,
    // and the music fades out.
    CALL(evt_msg_print_party, STRING("stg3_tou_458"))
    WAIT_MS(300)
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
    // Grubba flings the office door open and walks in on them.
    CALL(evt_npc_set_position, STRING("ガンス"), 0, 0, -160)
    CALL(evt_npc_flag_onoff, 1, STRING("ガンス"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_flag_onoff, 0, STRING("ガンス"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_npc_move_position, STRING("ガンス"), 0, -80, 0, FLOAT(80.0f), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(800)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    // The camera cuts to Grubba, who is caught red-handed and speaks.
    CALL(evt_cam3d_evt_set, 0, 82, 150, 0, 37, -112, 500, 11)
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, 0, STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_459"), 0, STRING("ガンス"))
    WAIT_MS(300)
    // Mario and his partner turn to confront him; the partner accuses him over King K and Bandy Andy.
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
    // Grubba bolts for the door and leaves, closing it behind him.
    CALL(evt_msg_print, 0, STRING("stg3_tou_461"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_npc_move_position, STRING("ガンス"), 0, -130, 0, FLOAT(100.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
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
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    // The camera returns to normal and the partner urges Mario to go after him.
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print_party, STRING("stg3_tou_462"))
    WAIT_MS(300)
    // The story moves on to Grubba's plans, the office door's entrance is switched on
    // and control returns to Mario.
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_31_GRUBBAS_PLANS)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(bero_case_switch_on)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Closes the desk drawer (kami_2 papers hidden) with the drawer-shut sound and re-registers evt_hiki_open. */
EVT_BEGIN(evt_hiki_close)
#if VERSION >= VERSION_JP
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
#endif
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kami_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_get_position, LW(0), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DRAWER_SHUT1"), LW(10), LW(11), LW(12), 0)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(9), LW(1))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_sub_intpl_init, 11, 100, 0, 30)
    LOOP(31)
        CALL(evt_sub_intpl_get_value)
#else
    CALL(evt_sub_intpl_msec_init, 11, 100, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
#endif
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, LW(8), 0, 0, LW(0))
        CALL(evt_hit_bind_update, LW(9))
        WAIT_FRAMES(1)
#if VERSION >= VERSION_JP
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
#endif
    END_LOOP
    SET_VALUE(LW(0), LW(8))
    SET_VALUE(LW(1), LW(9))
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(1), 0, PTR(evt_hiki_open), 0)
#if VERSION >= VERSION_JP
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/**
 * Case event for opening one of Grubba's desk drawers (LW(0) the drawer map object, LW(1) its hit object):
 * Mario steps up to the desk, the drawer slides out with the drawer sound
 * and a case to close it again (evt_hiki_close) is registered.
 * Opening hikidasi_H before STORY_STG3_31_GRUBBAS_PLANS also brings the partner over and plays evt_takurami;
 * opening hikidasi_N gives Mario a Star Piece the first time (GSWF_TOU05_DRAWER_STAR_PIECE_TAKEN).
 */
EVT_BEGIN(evt_hiki_open)
#if VERSION >= VERSION_JP
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
#endif
    // The partner comes over to the desk when it is the special drawer and Grubba's secret is still unknown.
    IF_STR_EQUAL(LW(0), STRING("hikidasi_H"))
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_31_GRUBBAS_PLANS)
#if VERSION <= VERSION_DEMO_US
            CALL(evt_mario_key_onoff, 0)
#endif
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
    // Mario steps up to the desk.
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), 20)
        CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
    // The drawer slides open with its drawer sound.
    CALL(evt_mapobj_get_position, LW(0), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DRAWER_OPEN1"), LW(10), LW(11), LW(12), 0)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(9), LW(1))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_sub_intpl_init, 11, 0, 100, 30)
    LOOP(31)
        CALL(evt_sub_intpl_get_value)
#else
    CALL(evt_sub_intpl_msec_init, 11, 0, 100, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
#endif
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, LW(8), 0, 0, LW(0))
        CALL(evt_hit_bind_update, LW(9))
        WAIT_FRAMES(1)
#if VERSION >= VERSION_JP
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
#endif
    END_LOOP
    // A button case is registered so the drawer can be pushed shut again.
    SET_VALUE(LW(0), LW(8))
    SET_VALUE(LW(1), LW(9))
    CALL(evt_run_case_evt, CASE_COND_PUSH, 1, LW(1), 0, PTR(evt_hiki_close), 0)
    // The special drawer plays the discovery scene of Grubba's secret paper.
    IF_STR_EQUAL(LW(0), STRING("hikidasi_H"))
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_31_GRUBBAS_PLANS)
            CALL_CHILD(evt_takurami)
#if VERSION <= VERSION_DEMO_US
            CALL(evt_party_run, 0)
#else
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_party_run, 0)
            CALL(evt_cam_letter_box_disable, 0)
#endif
            CALL(evt_exit_case_evt)
            RETURN
        END_IF
    END_IF
    // The other drawer holds a Star Piece, which Mario takes the first time only.
    IF_STR_EQUAL(LW(0), STRING("hikidasi_N"))
        IF_INT_EQUAL(GSWF(GSWF_TOU05_DRAWER_STAR_PIECE_TAKEN), 0)
            CALL(evt_item_entry, STRING("item02"), ITEM_STAR_PIECE, 0, -1000, 0, ITEM_ENTRY_FIXED, -1, 0)
            CALL(evt_item_get_item, STRING("item02"))
            SET_VALUE(GSWF(GSWF_TOU05_DRAWER_STAR_PIECE_TAKEN), 1)
            SET_VALUE(GSWF(GSWF_TOU05_STAR_PIECE_DRAWER), 1)
        END_IF
    END_IF
    // Control returns to the player.
#if VERSION >= VERSION_JP
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_party_run, 0)
#if VERSION >= VERSION_JP
    CALL(evt_cam_letter_box_disable, 0)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/**
 * NPC init for Grubba (ガンス) in his office: before STORY_STG3_04_GONZALES_IS_BORN he stands at (120, 0, 0) facing
 * 270.
 */
static EVT_BEGIN(init_gans)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_03_GRUBBA)
        CALL(evt_npc_set_position, STRING("me"), 120, 0, 0)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_npc_set_position, STRING("me"), 120, 0, 0)
        CALL(evt_npc_set_ry, STRING("me"), 270)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of Grubba in the office when Mario signs up for the Glitz Pit:
 * Grubba asks (stg3_tou_54) and Mario answers the yes/no menu (stg3_tou_52_yn).
 * One answer gets a short reply (stg3_tou_53).
 * The other fades out, resets everyone in front of Grubba, and they talk (stg3_tou_55, 55_01, 56);
 * the story advances to STORY_STG3_03_GRUBBA and evt_kinoshikowa runs.
 */
static EVT_BEGIN(talk_gans)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_54"), 0, STRING("ガンス"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_52_yn"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("stg3_tou_53"))
    ELSE
        CALL(evt_msg_continue)
        CALL(evt_fade_entry, FADE_OUT_BLACK, 500, 0, 0, 0)
        WAIT_MS(500)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kami_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mario_set_pos, 20, 0, 0)
        CALL(evt_party_set_pos, 0, 0, 0, -30)
        CALL(evt_npc_set_position, STRING("ガンス"), 120, 0, 0)
        CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
        CALL(evt_mario_set_dir_npc, STRING("ガンス"))
        CALL(evt_party_set_dir_npc, 0, STRING("ガンス"))
        CALL(evt_cam3d_evt_set, 70, 113, 386, 70, 45, -8, 0, 11)
        WAIT_MS(1000)
        CALL(evt_fade_entry, FADE_IN_BLACK, 500, 0, 0, 0)
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
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_03_GRUBBA)
        CALL_CHILD(evt_kinoshikowa)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * NPC init for Jolene (キノシコワ, the Toad receptionist):
 * from STORY_STG3_32_BOSS_BATTLE on she stands at (127, 0, 7) facing 270.
 */
static EVT_BEGIN(init_kinoshikowa)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("キノシコワ"), 127, 0, 7)
        CALL(evt_npc_set_ry, STRING("キノシコワ"), 270)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of Jolene in the office, who handles two Trouble Center jobs.
 * Job 13, clearing the garbage (Battle Trunks) out of the storeroom:
 * she asks Mario to clear it out (irai_13_00 the first time, then 13_02)
 * until he talks to her holding all 20 Battle Trunks,
 * when she notes it is done (13_03_b the first time, else 13_04) and sets GSWF_TROUBLE_WORK_1.
 * After that she complains about the smell while he still carries any (13_04),
 * and once he has none left she thanks him, pays 30 coins (13_03, 13_05),
 * records the play time in GSW_TOU_JOLENE_TROUBLE_TIME and finishes the job.
 * Job 23, Toodles's magazine: if Mario already has the Wrestling Mag she insists she only reads it to follow
 * trends (irai_23_03); otherwise she promises to return it soon (23_00), gives in when Mario insists (23_01),
 * fetches it from the back of the office and hands it over (23_02, ITEM_WRESTLING_MAG).
 * Outside the jobs she says nothing before STORY_STG3_32_BOSS_BATTLE
 * and later tells Mario she is busy (stg3_tou_re_008).
 */
static EVT_BEGIN(talk_kinoshikowa)
    // Job 13 (the Battle Trunks): Jolene asks Mario to clear the pile out,
    // and once he holds all 20 she notes it is done.
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 13)
        CALL(evt_pouch_check_item, ITEM_BATTLE_TRUNKS, LW(0))
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_1), 0)
            IF_INT_EQUAL(LW(0), 20)
                IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
                    CALL(evt_msg_print, 0, STRING("irai_13_03_b"), 0, 0)
                    SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
                ELSE
                    CALL(evt_msg_print, 0, STRING("irai_13_04"), 0, 0)
                END_IF
                SET_VALUE(GSWF(GSWF_TROUBLE_WORK_1), 1)
            ELSE
                IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
                    CALL(evt_msg_print, 0, STRING("irai_13_00"), 0, 0)
                    SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
                ELSE
                    CALL(evt_msg_print, 0, STRING("irai_13_02"), 0, 0)
                END_IF
            END_IF
        ELSE
            // With the trunks gone from his pack she thanks him, pays 30 coins and the job is finished;
            // while he still carries any she complains about the smell.
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print, 0, STRING("irai_13_03"), 0, 0)
                CALL(evt_sub_get_coin, 30)
                CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
                WAIT_MS(200)
                CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
                WAIT_MS(200)
                CALL(evt_msg_print, 0, STRING("irai_13_05"), 0, 0)
                CALL(evt_sub_save_playtime, GSW(GSW_TOU_JOLENE_TROUBLE_TIME))
                SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
                SET_VALUE(GSWF(GSWF_TROUBLE_13_SOLVED), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
            ELSE
                CALL(evt_msg_print, 0, STRING("irai_13_04"), 0, 0)
            END_IF
        END_IF
        RETURN
    END_IF
    // Job 23 (Toodles's magazine): if Mario already has the Wrestling Mag she insists she only reads it to
    // follow trends.
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 23)
        CALL(evt_pouch_check_item, ITEM_WRESTLING_MAG, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_msg_print, 0, STRING("irai_23_03"), 0, 0)
        ELSE
            // Otherwise she promises to return it soon, gives in when Mario insists,
            // hurries to the back of the office with the camera following her and fetches it.
            CALL(evt_msg_print, 0, STRING("irai_23_00"), 0, 0)
            CALL(evt_mario_set_pose, STRING("M_N_3"))
            WAIT_MS(500)
            CALL(evt_mario_set_pose, STRING("M_I_2"))
            WAIT_MS(1000)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_msg_print, 0, STRING("irai_23_01"), 0, 0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_npc_get_position, STRING("me"), LW(3), LW(4), LW(5))
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INTANGIBLE)
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
            CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INTANGIBLE)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
            WAIT_MS(200)
            // She hands the Wrestling Mag over to Mario.
            CALL(evt_msg_print, 0, STRING("irai_23_02"), 0, 0)
            CALL(evt_item_entry, STRING("pm"), ITEM_WRESTLING_MAG, 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_item_get_item, STRING("pm"))
            CALL(evt_item_get_item_end_wait, STRING("pm"))
            CALL(evt_npc_set_ry, STRING("me"), 270)
        END_IF
        RETURN
    END_IF
    // Outside the jobs she says nothing early in the story and later tells Mario she is busy.
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_tou_re_008"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

/** NPCs of Grubba's office: Grubba and Jolene. */
static NpcSetupInfo npcEnt[] = {
    {
        "ガンス", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_gans, // initEvent
        NULL, // regularEvent
        talk_gans, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノシコワ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_kinoshikowa, // initEvent
        NULL, // regularEvent
        talk_kinoshikowa, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Scene after Mario signs up: Grubba (stg3_tou_57) calls in Jolene (キノシコワ), who enters through the office door,
 * walks to the desk and talks with Grubba (stg3_tou_58 to 61);
 * then she leads Mario out, the door opens, GSWF_TOU_JOLENE_ESCORT_1_PENDING is set
 * and the map changes to tou_04.
 */
static EVT_BEGIN(evt_kinoshikowa)
    CALL(evt_msg_print, 0, STRING("stg3_tou_57"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, 0, -180)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
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
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(50.0f), 1)
        CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    SET_VALUE(GSWF(GSWF_TOU_JOLENE_ESCORT_1_PENDING), 1)
    CALL(evt_bero_mapchange, STRING("tou_04"), 0)
    RETURN
EVT_END()

/**
 * Scene on Mario's first visit to the office (before STORY_STG3_03_GRUBBA, run from the map init):
 * Grubba (ガンス) greets Mario with his theme (BGM_EVT_STG3_GANCE1),
 * explains the fighter's contract (stg3_tou_43 to 47, with a yes/no menu),
 * walks around Mario as camera moves in, then leaves through the door;
 * GSWF_TOU_GRUBBA_ESCORT_PENDING is set and the map changes to tou_04.
 */
static EVT_BEGIN(evt_sensyu)
    // The map's music fades out and, after a pause, Grubba's theme starts as he notices Mario.
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG3_GANCE1"))
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("ガンス"))
    CALL(evt_eff_fukidashi, 1, STRING("eff"), STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    // Grubba welcomes the new challenger and the camera pushes in while the partner steps aside.
    CALL(evt_msg_print, 0, STRING("stg3_tou_43"), 0, STRING("ガンス"))
    CALL(evt_cam3d_evt_set, 75, 114, 386, 75, 45, -8, 1000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 0, -30, FLOAT(60.0f))
        CALL(evt_party_set_dir_npc, 0, STRING("ガンス"))
    END_INLINE_EVENT
    // Mario raises his hand to volunteer and nods as Grubba explains the contract.
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
    // Grubba asks whether Mario wants to fight (a yes/no menu); either answer carries on.
    CALL(evt_msg_select, 0, STRING("stg3_tou_45_yn"))
    CALL(evt_msg_print_add, 0, STRING("stg3_tou_46_00"))
    // Grubba circles around Mario, the camera following, talking as he goes.
    CALL(evt_npc_flag_onoff, 1, STRING("ガンス"), NPC_FLAG_INTANGIBLE)
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
    // Mario is startled and shakes his head from side to side.
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
    // The camera pulls back for Grubba's last words.
    CALL(evt_cam3d_evt_set, 0, 140, 534, 0, 45, -80, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_47"), 0, STRING("ガンス"))
    WAIT_MS(300)
    // Grubba leaves through the door.
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ガンス"), -10, -120, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("ガンス"), 10, -120, 0, FLOAT(80.0f), 1)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_open_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_npc_move_position, STRING("ガンス"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("ガンス"), 0, -1000, 0)
    END_INLINE_EVENT
    // Mario follows into the corridor; the Grubba escort is queued and the map changes to the corridor.
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 0, -200, FLOAT(60.0f))
    END_INLINE_EVENT
    WAIT_MS(1000)
    SET_VALUE(GSWF(GSWF_TOU_GRUBBA_ESCORT_PENDING), 1)
    CALL(evt_bero_mapchange, STRING("tou_04"), 0)
    RETURN
EVT_END()

/**
 * Chapter 3 intro scene: Grubba welcomes Mario and offers to enter him in the Glitz Pit (stg3_tou_51 to 55),
 * asks yes/no, and advances the story to STORY_STG3_03_GRUBBA.
 */
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
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG3_GANCE1"))
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_msg_print, 0, STRING("stg3_tou_51"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_eff_fukidashi, 1, STRING("eff"), STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kami_1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_msg_print, 0, STRING("stg3_tou_52"), 0, STRING("ガンス"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_52_yn"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("stg3_tou_53"))
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("a_p_tukue"), 0, PTR(talk_gans), 0)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_03_GRUBBA)
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
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_04_GONZALES_IS_BORN)
        CALL_CHILD(evt_kinoshikowa)
    END_IF
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Scene run from the map init when GSWF_TOU_PROMOTION_PENDING is set (the promotion to the first league, the
 * majors): Jolene (キノシコワ) comes in, Grubba jumps out from behind the desk
 * and the two talk (stg3_tou_287 to 293); Grubba hands Mario 30 coins;
 * Jolene leaves through the door, GSWF_TOU_JOLENE_ESCORT_MAJORS_PENDING is set and the map changes to tou_04.
 */
static EVT_BEGIN(evt_1st_leagu)
    // Mario and his partner stand in Grubba's office; the camera frames the desk.
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, 0, -160)
    CALL(evt_mario_set_pos, 0, 0, -165)
    CALL(evt_party_set_pos, 0, 0, 0, -180)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_npc_set_position, STRING("ガンス"), 125, 0, 25)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_mapobj_trans, 1, STRING("hikidasi_H"), 0, 0, 10)
    CALL(evt_cam3d_evt_set, 75, 100, 371, 75, 37, 13, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    WAIT_MS(3000)
    // After a long pause the door swings open and Jolene walks in.
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
        CALL(evt_npc_move_position, STRING("キノシコワ"), 1, -100, 0, FLOAT(50.0f), 1)
        CALL(evt_npc_move_position, STRING("キノシコワ"), 50, -100, 0, FLOAT(50.0f), 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1200)
        CALL(evt_party_move_pos2, 0, -20, -30, FLOAT(60.0f))
        CALL(evt_party_stop, 0)
        CALL(evt_party_move_pos2, 0, -50, -30, FLOAT(60.0f))
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    // Mario and his partner step aside and the door shuts.
    BEGIN_INLINE_EVENT
        WAIT_MS(800)
        CALL(evt_mario_mov_pos2, -10, -20, FLOAT(60.0f))
        CALL(evt_mario_set_dir, 90, 200, 0)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    // Grubba, startled, leaps out from behind the desk (the drawer is shoved shut).
    CALL(evt_eff_fukidashi, 1, 0, STRING("ガンス"), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_get_position, STRING("ガンス"), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_JP
    CALL(evt_npc_sound_data_set, STRING("ガンス"), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR, 0, EVT_NULLPTR)
#endif
    CALL(evt_npc_jump_position_nohit, STRING("ガンス"), LW(0), LW(1), LW(2), 300, 20)
#if VERSION >= VERSION_JP
    CALL(evt_npc_sound_data_reset, STRING("ガンス"))
#endif
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kami_2"), MAPOBJ_FLAG_HIDE)
    WAIT_MS(300)
    SET_VALUE(LW(0), STRING("hikidasi_H"))
    SET_VALUE(LW(1), STRING("a_hikidasi_H"))
    CALL_CHILD(evt_hiki_close)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    // Jolene and Grubba talk about Mario's promotion to the majors.
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ガンス"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_287"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_288"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_289"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_290"), 0, STRING("ガンス"))
    WAIT_MS(300)
    // The camera slowly moves in as Grubba walks over to Mario.
    CALL(evt_cam3d_evt_set, 15, 90, 269, 15, 37, -26, 4000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 70, -100, 0, FLOAT(50.0f), 1)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("mario"))
    END_INLINE_EVENT
    CALL(evt_npc_status_onoff, 1, STRING("ガンス"), 2)
    CALL(evt_npc_move_position, STRING("ガンス"), 110, 85, 0, FLOAT(50.0f), 1)
    CALL(evt_npc_move_position, STRING("ガンス"), 25, 50, 0, FLOAT(50.0f), 1)
    CALL(evt_npc_move_position, STRING("ガンス"), 25, -10, 0, FLOAT(50.0f), 1)
    CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_291"), 0, STRING("ガンス"))
    WAIT_MS(300)
    // Grubba hands Mario 30 coins and Mario holds them up.
    CALL(evt_pouch_add_coin, 30)
    CALL(evt_mario_set_pose, STRING("M_I_U"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 50)
    CALL(evt_item_entry, STRING("coin"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    WAIT_MS(1000)
    CALL(evt_item_delete, STRING("coin"))
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    // Grubba and Jolene finish talking.
    CALL(evt_msg_print, 0, STRING("stg3_tou_292_02"), 0, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_292"), 0, STRING("ガンス"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_293"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    // Jolene leaves through the door.
    CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -100, 0, FLOAT(50.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL_CHILD(n_door_open)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(50.0f), 1)
        CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
    END_INLINE_EVENT
    // Mario follows, the escort to the major-league room is queued and the map changes to the corridor.
    CALL(evt_party_run, 0)
    CALL(evt_mario_mov_pos2, 0, -200, FLOAT(60.0f))
    SET_VALUE(GSWF(GSWF_TOU_JOLENE_ESCORT_MAJORS_PENDING), 1)
    CALL(evt_bero_mapchange, STRING("tou_04"), 0)
    RETURN
EVT_END()

/**
 * Muffled voices heard from the air duct, spawned when Mario drops in (entrance "fall")
 * before STORY_STG3_20_12_JOLENES_SECRET: repeats two "........" bubbles (stg3_tou_316_03, 316_04) at x -50
 * and 50 every second until evt_nozoki deletes it (event id in GW(9)).
 */
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

/**
 * Mario peeks down into Grubba's office through the gap in the air duct (a_nozoki):
 * the camera moves in and a paper animation opens the dark panel (kuro_P).
 * Before STORY_STG3_20_12_JOLENES_SECRET Grubba (ガンス) and Jolene (キノシコワ) talk below:
 * the storage room intruder, King K's disappearance and keeping it quiet,
 * and Grubba asking where Jolene keeps vanishing to, which she refuses to answer (stg3_tou_316_05 to 316_17);
 * she leaves and Grubba grumbles that good fighters are a dying breed (320).
 * The partner whispers to Mario (321), Grubba hears the ceiling and asks who is there (322),
 * Mario picks a noise (Squeak, Meow or Belch) and Grubba reacts (325 to 325_02) and goes back to the ring;
 * the panel closes, the partner sums up (326) and the story advances to STORY_STG3_20_12_JOLENES_SECRET.
 * On later visits Mario just looks until A is pressed.
 */
EVT_BEGIN(evt_nozoki)
    // Mario freezes in place; the first time, Grubba and Jolene are placed in the office below.
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_12_JOLENES_SECRET)
        DELETE_EVENT(GW(9))
        CALL(evt_npc_set_position, STRING("ガンス"), 120, 0, 0)
        CALL(evt_set_dir_to_target, STRING("ガンス"), STRING("キノシコワ"))
        CALL(evt_npc_set_position, STRING("キノシコワ"), 20, 0, 0)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ガンス"))
        CALL(evt_npc_flag_onoff, 1, STRING("ガンス"), NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_status_onoff, 1, STRING("ガンス"), 2)
        CALL(evt_npc_flag_onoff, 1, STRING("キノシコワ"), NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
    END_IF
    // The camera moves in and the dark panel over the vent peels open like a page,
    // letting Mario see into the office.
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
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kuro_P"), MAPOBJ_FLAG_HIDE)
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_onoff, STRING("img"), 0)
    // The first time: Grubba and Jolene talk below about the storage room intruder,
    // King K's disappearance and keeping it quiet.
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_12_JOLENES_SECRET)
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
        // The camera pulls back; Grubba asks where Jolene keeps vanishing to and she refuses to say.
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
        // Jolene leaves through the door, and Grubba grumbles that good fighters are a dying breed.
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -120, 0, FLOAT(80.0f), 1)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_open_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
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
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(evt_msg_print, 0, STRING("stg3_tou_320"), 0, STRING("ガンス"))
        WAIT_MS(300)
        // Mario and his partner crouch in the vent; the partner whispers to him and Mario nods.
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
        // Grubba hears something in the ceiling and asks who is there; Mario answers with a noise (Squeak,
        // Meow or Belch) and Grubba reacts.
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
        // Grubba shrugs it off, goes back to the ring and leaves the office.
        CALL(evt_cam3d_evt_set, 0, 145, 534, 0, 50, -8, 1000, 11)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING("ガンス"), 115, -80, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("ガンス"), 0, -120, 0, FLOAT(80.0f), 1)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_open_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
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
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL_CHILD(n_door_open)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        // The panel closes again and the partner sums up what they heard;
        // the story moves on to Jolene's secret.
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
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kuro_P"), MAPOBJ_FLAG_HIDE)
        CALL(evt_cam3d_evt_set, 0, 210, 345, 0, 185, -4, 1000, 11)
        WAIT_MS(1000)
        CALL(evt_msg_print_party, STRING("stg3_tou_326"))
        WAIT_MS(300)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_12_JOLENES_SECRET)
    ELSE
        // On later visits Mario just looks down into the office until A is pressed, then the panel closes.
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
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kuro_P"), MAPOBJ_FLAG_HIDE)
    END_IF
    // The camera returns to normal and control goes back to Mario.
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Scene when Mario enters the office after STORY_STG3_34_RETURN_TO_ROGUEPORT before re-entering the league:
 * Jolene (キノシコワ) greets the Great Gonzales (stg3_tou_re_003, 004),
 * tells him attendance fell after he gave the belt back (005 onward),
 * finds his records are gone (005_2) and signs him up again as a minor-league fighter (006, 007),
 * walking about the room as she talks; sets GSWF_TOU_REENTERED_LEAGUE.
 */
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
    CALL(evt_mario_dispflag_onoff, 1, MARIO_DISP_FLAG_POSE_LOCK)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 300, 1, 10)
    CALL(evt_mario_dispflag_onoff, 0, MARIO_DISP_FLAG_POSE_LOCK)
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
    SET_VALUE(GSWF(GSWF_TOU_REENTERED_LEAGUE), 1)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init for tou_05, Grubba's office: sets up the Star Piece, the desk papers and the camera animation,
 * drops Mario in from the ceiling when he enters through "fall",
 * and chooses the scene to run from the story progress.
 */
EVT_BEGIN(tou_05_init_evt)
    // Set up the doors, the camera animation and the Star Piece on the floor.
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_map_playanim, STRING("anm_camera"), 1, 0)
    CALL(evt_item_entry, STRING("item01"), ITEM_STAR_PIECE, -135, 0, 105, ITEM_ENTRY_FIXED, GSWF(GSWF_TOU05_STAR_PIECE), 0)
#if VERSION >= VERSION_JP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("paifu"), MAPOBJ_FLAG_BBOX_CULL)
#endif
    CALL(evt_bero_get_entername, LW(0))
    // Entering through the air vent ("fall"): Mario drops into the office from the ceiling
    // and the partner follows a moment later.
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
    // Show the vent's dark panel to match the entrance, and bind the two desk drawers once the vent trip is
    // done.
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("fall"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kuro_Y"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kuro_P"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kuro_Y"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kuro_P"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_04_AIR_DUCT_EXIT)
        SET_VALUE(LW(0), STRING("hikidasi_N"))
        SET_VALUE(LW(1), STRING("a_hikidasi_N"))
        CALL(evt_hit_bind_mapobj, LW(1), LW(0))
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(1), 0, PTR(evt_hiki_open), 0)
        SET_VALUE(LW(0), STRING("hikidasi_H"))
        SET_VALUE(LW(1), STRING("a_hikidasi_H"))
        CALL(evt_hit_bind_mapobj, LW(1), LW(0))
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(1), 0, PTR(evt_hiki_open), 0)
    END_IF
    // Place the NPCs; talking to Grubba's desk becomes available early in the story,
    // and the vent peek is set up.
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_03_GRUBBA)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("a_p_tukue"), 0, PTR(talk_gans), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kami_1"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_12_JOLENES_SECRET)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("fall"))
            SPAWN_EVENT_GET_ID(PTR(evt_nozoki_msg), GW(9))
        END_IF
    END_IF
    CALL(evt_run_case_evt, CASE_COND_STAND_ON_A, 1, STRING("a_nozoki"), 0, PTR(evt_nozoki), 0)
    // Mario falling through the vent is sent on to the next room once he drops below the floor.
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
    // Unless map events are being skipped, choose the scene: Grubba's first-visit speech,
    // the promotion scene, or none.
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_SKIP_MAP_EVENTS)
        RETURN
    END_IF
    SET_VALUE(LW(0), 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_03_GRUBBA)
        SET_VALUE(LW(0), 1)
        IF_INT_EQUAL(GSWF(GSWF_TOU_GRUBBA_ESCORT_PENDING), 0)
            SPAWN_EVENT(evt_sensyu)
        ELSE
            SET_VALUE(GSWF(GSWF_TOU_GRUBBA_ESCORT_PENDING), 0)
            SPAWN_EVENT(evt_sensyu2)
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TOU_PROMOTION_PENDING), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG3_GANCE1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        SET_VALUE(LW(0), 1)
        SPAWN_EVENT(evt_1st_leagu)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kami_2"), MAPOBJ_FLAG_HIDE)
    END_IF
    // Choose the music and ambience for the story point.
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_31_GRUBBAS_PLANS)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_snd_envoff, PSND_FADE_OUT)
    ELSE
        IF_INT_EQUAL(LW(0), 0)
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
        END_IF
    END_IF
    // Show the open or closed air duct, depending on whether the way out has been used.
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_30_04_AIR_DUCT_EXIT)
        SET_VALUE(LF(0), 0)
        CASE_LESS(STORY_STG3_34_RETURN_TO_ROGUEPORT)
        SET_VALUE(LF(0), 1)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU13_DUCT_EXIT_OPEN_REVISIT), 0)
            SET_VALUE(LF(0), 0)
        ELSE
            SET_VALUE(LF(0), 1)
        END_IF
    END_SWITCH
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("haikikau_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("haikikau_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("a_haikikan"), 1, 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("haikikau_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("haikikau_2"), MAPOBJ_FLAG_HIDE)
    END_IF
    // After the return to Rogueport, a visitor who has not yet re-entered the league gets Jolene's re-entry
    // talk.
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_NOT_EQUAL(LW(0), STRING("fall"))
            IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
                SPAWN_EVENT(evt_sensyu_reentry)
            END_IF
        END_IF
    END_IF
    // Switch on the hidden walls and doors.
    CALL(evt_hitobj_onoff, STRING("haiku_kabe"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("kore"), 1, 0)
    CALL(evt_hitobj_attr_onoff, 1, 1, STRING("w_bero"), 4)
    RETURN
EVT_END()

/**
 * Message-window callback: counts printed text windows (type 2) into GW(10),
 * so a scene script can wait for Grubba's speech to reach a given line.
 */
static void gans_msg_callback(s32 type, void** work) {
    EventEntry* evt = ((MsgWinData*)*work)->event;
    if (type == 2) {
        evtSetValue(evt, GW(10), evtGetValue(evt, GW(10)) + 1);
    }
}
