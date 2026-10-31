// tik_06 (埋没した都市, Rogueport Sewers): the entrance to the Pit of 100 Trials (jon_00), with residents and trouble 12
// (irai_12).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_item.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "tik.h"
#include "evt/evt_story.h"
#include "driver/camdrv.h"

static BeroEntry bero_entry_data[5];
extern EvtWord iri_12_kino_makkino_talk[];
extern EvtWord iri_12_kino_talk[];

/**
 * Pushes Mario back when he tries to use the blocked pipe (oshimodo = push back):
 * takes control, makes him leave the pipe, shows tik_06_01 and gives control back. Returns 0 in LW(0).
 */
static EVT_BEGIN(oshimodo_event)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_ctrl_onoff, CAMERA_3D, 0)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_bero_exec_wait, 65536)
        WAIT_MS(750)
        CALL(evt_msg_print, 0, STRING("tik_06_01"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_cam_ctrl_onoff, CAMERA_3D, 1)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

/**
 * Doors of this room: the pipe to the Pit of 100 Trials (jon_00), the pipe to tik_18, the pipe Mario comes out
 * of from tik_10 and tik_14 (entering it only shows "You can't enter from here!") and the east exit to the
 * Thousand-Year Door room (tik_05).
 */
static BeroEntry bero_entry_data[] = {
    {
        "dokan_1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, // exitEvent
        "jon_00", // nextMapName
        "dokan_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_UP, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, // exitEvent
        "tik_18", // nextMapName
        "dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_3", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        (s32*)oshimodo_event, // exitEvent
        0, // nextMapName
        "dokan_3", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "e_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tik_05", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Conversation of the Trouble Center request 12 (irai_12) with Kino (キーノ, a young Toad girl)
 * and Makkino (マッキノ, a sailor).
 * They both turn to Mario and talk (irai_12_001_3 to 5);
 * if Makkino was the one spoken to (LW(0) = 1) he steps toward Mario first.
 * Mario receives the Silver Card, Makkino says irai_12_001_6, both hop away to the right and vanish,
 * the request is marked solved (GSWF_TROUBLE_12_SOLVED, play time saved in GSW_TIK06_TROUBLE12_TIME,
 * GSW_TROUBLE_ACTIVE cleared) and sys_request_finish is shown.
 */
EVT_BEGIN(iri_12_kino_makkino_talk)
    CALL(evt_set_dir_to_target, STRING("キーノ"), STRING("mario"))
    CALL(evt_set_dir_to_target, STRING("マッキノ"), STRING("mario"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("キーノ"))
    CALL(evt_npc_wait_pera, STRING("マッキノ"))
    CALL(evt_msg_print, 0, STRING("irai_12_001_3"), 0, STRING("キーノ"))
    CALL(evt_msg_print, 0, STRING("irai_12_001_4"), 0, STRING("マッキノ"))
    CALL(evt_msg_print, 0, STRING("irai_12_001_5"), 0, STRING("キーノ"))
    IF_INT_EQUAL(LW(0), 1)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_npc_get_position, STRING("マッキノ"), LW(3), LW(4), LW(5))
            CALL(evt_sub_get_dir, LW(0), LW(2), LW(3), LW(5), LW(6))
            DIVIDE(LW(6), 90)
            MULTIPLY(LW(6), 90)
            ADD(LW(6), 45)
            CALL(evt_npc_add_dirdist, LW(3), LW(5), LW(6), 20)
            CALL(evt_npc_status_onoff, 0, STRING("マッキノ"), 2)
            CALL(evt_npc_flag_onoff, 1, STRING("マッキノ"), NPC_FLAG_INTANGIBLE)
            CALL(evt_npc_move_position, STRING("マッキノ"), LW(3), LW(5), 0, 70, 0)
            WAIT_FRAMES(1)
            CALL(evt_npc_status_onoff, 1, STRING("マッキノ"), 2)
            CALL(evt_set_dir_to_target, STRING("マッキノ"), STRING("mario"))
        END_INLINE_EVENT
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("キーノ"), LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dir, LW(0), LW(2), LW(3), LW(5), LW(6))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(6), 20)
    CALL(evt_npc_flag_onoff, 1, STRING("キーノ"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_move_position, STRING("キーノ"), LW(0), LW(2), 0, 60, 0)
    CALL(evt_mario_set_dir_npc, STRING("キーノ"))
    WAIT_MS(500)
    CALL(evt_item_entry, STRING("tf"), ITEM_SILVER_CARD, 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_item_get_item, STRING("tf"))
    CALL(evt_item_get_item_end_wait, STRING("tf"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("irai_12_001_6"), 0, STRING("マッキノ"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("マッキノ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SKIP_HIT_ATTR4 | NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_move_position, STRING("マッキノ"), 220, 0, 0, 60, 4)
        CALL(evt_npc_jump_position_nohit, STRING("マッキノ"), 254, 15, 0, 400, 15)
        CALL(evt_npc_jump_position_nohit, STRING("マッキノ"), 285, 30, 0, 400, 15)
        CALL(evt_npc_set_position, STRING("マッキノ"), 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_npc_get_position, STRING("キーノ"), LW(0), LW(1), LW(2))
    ADD(LW(0), 25)
    LOOP(0)
        CALL(evt_npc_get_position, STRING("マッキノ"), LW(3), LW(4), LW(5))
        IF_INT_GREATER_OR_EQUAL(LW(3), LW(0))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING("キーノ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SKIP_HIT_ATTR4 | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_move_position, STRING("キーノ"), 220, 0, 0, 60, 4)
    CALL(evt_npc_jump_position_nohit, STRING("キーノ"), 254, 15, 0, 400, 15)
    CALL(evt_npc_jump_position_nohit, STRING("キーノ"), 285, 30, 0, 400, 15)
    CALL(evt_npc_set_position, STRING("キーノ"), 0, -1000, 0)
    CALL(evt_sub_save_playtime, GSW(GSW_TIK06_TROUBLE12_TIME))
    SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
    SET_VALUE(GSWF(GSWF_TROUBLE_12_SOLVED), 1)
    CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
    RETURN
EVT_END()

/**
 * Interrupt (talk) script for Kino while Trouble request 12 is active.
 * Before Makkino has arrived (GSWF_TROUBLE_WORK_2 = 0) it says irai_12_001_1 the first time
 * and irai_12_001_2 afterwards; once Makkino stands beside her it starts the final conversation with LW(0) = 0.
 */
EVT_BEGIN(iri_12_kino_talk)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 12)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_2), 0)
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
                CALL(evt_msg_print, 0, STRING("irai_12_001_1"), 0, 0)
                SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
            ELSE
                CALL(evt_msg_print, 0, STRING("irai_12_001_2"), 0, 0)
            END_IF
        ELSE
            SET_VALUE(LW(0), 0)
            CALL_CHILD(iri_12_kino_makkino_talk)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Talk script of Makkino for Trouble Center request 12:
 * runs the final conversation with LW(0) = 1, so Makkino steps toward Mario first.
 */
static EVT_BEGIN(iri_12_makkino_talk)
    SET_VALUE(LW(0), 1)
    CALL_CHILD(iri_12_kino_makkino_talk)
    RETURN
EVT_END()

/**
 * Sets up Kino and Makkino while Trouble Center request 12 is active.
 * Kino stands at (60, 0, -70) facing left (or right once Makkino has come);
 * Makkino appears at (90, 0, -70) only after GSWF_TROUBLE_WORK_2 is set. Each gets a talk interrupt script.
 */
static EVT_BEGIN(iri_12_init)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 12)
        CALL(evt_npc_entry, STRING("キーノ"), STRING("c_kokinopio"))
        CALL(evt_npc_set_tribe, STRING("キーノ"), STRING("キノピオ子"))
        CALL(evt_npc_set_position, STRING("キーノ"), 60, 0, -70)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_2), 0)
            CALL(evt_npc_set_ry, STRING("キーノ"), 270)
        ELSE
            CALL(evt_npc_set_ry, STRING("キーノ"), 90)
        END_IF
        CALL(evt_npc_flag_onoff, 1, STRING("キーノ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_npc_status_onoff, 1, STRING("キーノ"), 2)
        CALL(evt_npc_change_interrupt, STRING("キーノ"), 6, PTR(iri_12_kino_talk))
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_2), 1)
            CALL(evt_npc_entry, STRING("マッキノ"), STRING("c_suifu_k"))
            CALL(evt_npc_set_tribe, STRING("マッキノ"), STRING("水夫"))
            CALL(evt_npc_set_position, STRING("マッキノ"), 90, 0, -70)
            CALL(evt_npc_set_ry, STRING("マッキノ"), 90)
            CALL(evt_npc_flag_onoff, 1, STRING("マッキノ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
            CALL(evt_npc_status_onoff, 1, STRING("マッキノ"), 2)
            CALL(evt_npc_change_interrupt, STRING("マッキノ"), 6, PTR(iri_12_makkino_talk))
        END_IF
    END_IF
    RETURN
EVT_END()

/** Signboard script: says tik_06_02 with Mario's controls disabled. */
static EVT_BEGIN(evt_kanban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_msg_print, 0, STRING("tik_06_02"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Signboard script for the Pit of 100 Trials board:
 * shows the player's records (deepest floor, Power Bounce record and the Star Pieces found there) in
 * msg_jon_kanban_3.
 */
static EVT_BEGIN(evt_kanban2)
    CALL(evt_npc_stop_for_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    SET_VALUE(LW(0), GSW(GSW_JON_DEEPEST_FLOOR))
    SET_VALUE(LW(1), GSW(GSW_POWER_BOUNCE_RECORD_LO))
    SET_VALUE(LW(4), GSW(GSW_POWER_BOUNCE_RECORD_HI))
    MULTIPLY(LW(4), 256)
    ADD(LW(1), LW(4))
    // BUG: nothing in the game writes GSW 34, so the sign always shows 0 found (original game)
    SET_VALUE(LW(2), GSW(GSW_JON_STAR_PIECES_FOUND))
    SET_VALUE(LW(3), 100)
    CALL(evt_msg_print_insert, 0, STRING("msg_jon_kanban_3"), 0, 0, LW(0), LW(1), LW(2), LW(3))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_npc_start_for_event)
    RETURN
EVT_END()

/**
 * Map init script of tik_06, the room in front of the Pit of 100 Trials.
 * Starts the ambience (music only in the demo), sets up the exits and the Trouble request 12 characters,
 * two signboards (one shows the Pit record: deepest floor and best times) and a Star Piece.
 */
EVT_BEGIN(tik_06_init_evt)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_TIK1"))
#else
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
#endif
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_TIK1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(iri_12_init)
    CALL(evt_mobj_signboard, STRING("board"), -50, 0, 50, PTR(evt_kanban), LSWF(0))
    CALL(evt_mobj_signboard, STRING("board2"), 50, 0, -250, PTR(evt_kanban2), LSWF(0))
    CALL(evt_item_entry, STRING("item_00"), ITEM_STAR_PIECE, 290, 0, -50, ITEM_ENTRY_FIXED, GSWF(GSWF_TIK06_STAR_PIECE), 0)
    RETURN
EVT_END()
