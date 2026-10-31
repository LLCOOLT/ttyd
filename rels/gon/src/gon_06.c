// gon_06 (ゴンババ, Hooktail Castle): room with a chest opened by the Black Key (0x22) that gives the Paper Curse.
// Paper genie (peramajin) scene (story 43 to 45), Attack FX R item, Dry Bones-type enemies.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "driver/mobjdrv.h"
#include "driver/animdrv.h"
#include "evt/evt_bero.h"
#include "gon.h"
#include "mario/mario_pouch.h"
#include "evt/evt_cam.h"
#include "evt/evt_hit.h"
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "evt/evt_lecture.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_paper.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_window.h"
#include "pmario_sound.h"
#include "version.h"
#include "evt/evt_story.h"

static USER_FUNC(bgm_start_wait);
static void majin_callback(s32 type);

static BeroEntry bero_entry_data[3];
extern EvtWord evt_ori_open[];
extern EvtWord tsuritenjo_event[];
static s32 key_tbl[2];

/**
 * Door animation callback, closing for the w_bero exit to gon_05:
 * rotates map object "door01" about Y by 0.444 times the value in LW(0).
 */
static EVT_BEGIN(door01_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door01"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback, opening for the w_bero exit to gon_05:
 * rotates map object "door01" about Y by -0.444 times the value in LW(0).
 */
static EVT_BEGIN(door01_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door01"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback, closing for the e_bero exit to gon_07:
 * rotates map object "door02" about Y by -0.444 times the value in LW(0).
 */
static EVT_BEGIN(door02_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback, opening for the e_bero exit to gon_07:
 * rotates map object "door02" about Y by 0.444 times the value in LW(0).
 */
static EVT_BEGIN(door02_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Exits (beros) of this room: w_bero to gon_05 and e_bero to gon_07. */
static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        12, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gon_05", // nextMapName
        "e_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        door01_close, // enterAnimeArg
        door01_open, // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        12, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gon_07", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        door02_close, // enterAnimeArg
        door02_open, // exitAnimeArg
    },
    {0},
};

/**
 * Runs when Mario steps on the red switch: slides the bar grid ori02 up with its sound, waits,
 * slides it back down and shakes the camera when it lands, while its hit areas follow it.
 */
EVT_BEGIN(evt_ori_open)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 2)
    CALL(evt_hit_bind_mapobj, STRING("a_ori_03"), STRING("ori02"))
    CALL(evt_hit_bind_mapobj, STRING("a_ori_03_atari"), STRING("ori02"))
    CALL(evt_mapobj_get_position, STRING("ori02"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_DOOR_GRID_OPEN1"), LW(10), LW(11), LW(12), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(0), LW(1))
        CALL(evt_mapobj_trans, 1, STRING("ori02"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_ori_03"))
        CALL(evt_hit_bind_update, STRING("a_ori_03_atari"))
        IF_INT_GREATER_OR_EQUAL(LW(0), 150)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(LW(1), -10)
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, STRING("ori02"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_DOOR_GRID_SHUT1"), LW(10), LW(11), LW(12), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(0), LW(1))
        CALL(evt_mapobj_trans, 1, STRING("ori02"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_ori_03"))
        CALL(evt_hit_bind_update, STRING("a_ori_03_atari"))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_get_position, STRING("ori02"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG1_DOOR_GRID_DOWN1"), LW(10), LW(11), LW(12), 0)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_rumble_onoff, 0, 0)
        WAIT_MS(200)
        CALL(evt_sub_rumble_onoff, 1, 0)
    END_SIBLING_EVENT
    CALL(evt_cam_shake, 4, FLOAT(0.0048828125f), FLOAT(0.0f), 500)
    RETURN
EVT_END()

/**
 * Cutscene run when Mario comes into gon_06 at the STORY_STG1_13_A_SUSPICIOUS_ROOM step, that is,
 * after escaping the countdown trap set off in gon_07 (item_evt):
 * he and the partner walk in through the door, the partner speaks (stg1_gon_18_00), Mario nods,
 * the music resumes and the story moves to STORY_STG1_13_01_50_SECONDS_TO_ESCAPE.
 * Guess: tsuritenjo (吊り天井, hanging ceiling) names that trap, a ceiling that comes down.
 */
EVT_BEGIN(tsuritenjo_event)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_set_pos, 620, 0, 0)
    CALL(evt_party_set_pos, 0, 670, 0, 0)
#if VERSION >= VERSION_JP
    CALL(evt_cam_road_reset)
#endif
    CALL(evt_bero_mario_go_init)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 1)
    SPAWN_EVENT(bero_play_enter_anime)
    CALL(evt_bero_mario_go_wait)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 570, 0, FLOAT(150.0f))
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 520, 0, FLOAT(150.0f))
    WAIT_MS(300)
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg1_gon_18_00"))
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_snd_bgmon_f, PSND_FADE_IN | PSND_FADE_OUT, STRING("BGM_STG1_GON1"), 3000)
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG1_GON1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG1_13_01_50_SECONDS_TO_ESCAPE)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_npc_start_for_event)
#if VERSION >= VERSION_JP
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
#endif
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

/**
 * Message callback for the chest's lines: switches the chest between its talking (A_2)
 * and idle (S_1) animations as the text reaches the marked points.
 */
static void majin_callback(s32 type) {
    MapObjectEntry* mobj = mobjNameToPtr("box");

    if (type == 0) {
        animPoseSetAnim(mobj->poseId, "A_2", TRUE);
    } else if (type == 5) {
        if (animPoseGetLoopTimes(mobj->poseId) >= 1.0f) {
            animPoseSetAnim(mobj->poseId, "A_2", TRUE);
        }
    } else if (type == 2) {
        animPoseSetAnim(mobj->poseId, "S_1", TRUE);
    }
}

/** Script helper: blocks until the lecture/cutscene music (BGM channel 1) has actually started. */
static USER_FUNC(bgm_start_wait) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/** Items offered in the item menu at the chest: only the Black Key (0x22). */
static s32 key_tbl[] = {
    ITEM_BLACK_KEY_0x22, -1,
};

/**
 * Pre-open event of the black chest ("box"): the chest swings and speaks to Mario (stg1_gon_12_01 to _07)
 * while Mario reacts, and once Mario carries the Black Key (ITEM_BLACK_KEY_0) the chest takes it (stg1_gon_12_08
 * to _11) and opens. GSWF_GON06_BLACK_CHEST_TALKED makes the first talk play only once.
 */
static EVT_BEGIN(evt_majin)
    // Mario is frozen and turns toward the black chest.
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_adjust_dir)
    // First visit: the chest talks to Mario.
    IF_INT_EQUAL(GSWF(GSWF_GON06_BLACK_CHEST_TALKED), 0)
        CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
        ADD(LW(1), 30)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
            IF_INT_LESS_OR_EQUAL(LW(3), LW(0))
                CALL(evt_mario_set_dir, 90, 200, 0)
            ELSE
                CALL(evt_mario_set_dir, 270, 200, 0)
            END_IF
        END_INLINE_EVENT
        // The chest is startled by visitors.
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_01"), 0, 0)
        // The camera moves in and the chest swings on its base.
        CALL(evt_cam3d_evt_set, 380, 125, 418, 380, 55, 24, 650, 11)
        CALL(evt_mobj_get_position, STRING("box"), LW(3), LW(4), LW(5))
        ADD(LW(4), 30)
        CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLACKBOX_SWING1"), LW(3), LW(4), LW(5), LW(15))
        CALL(evt_mobj_set_anim, STRING("box"), STRING("A_3"))
        CALL(evt_mobj_wait_animation_end, STRING("box"))
        CALL(evt_snd_sfxoff, LW(15))
        // The chest chats with Mario while he shrugs, startles and shakes his head in turn.
        WAIT_MS(300)
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_02"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_03"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_04"), PTR(majin_callback), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2_3"), LW(0), LW(1), LW(2), 0)
        END_INLINE_EVENT
        CALL(evt_mario_set_pose, STRING("M_N_5B"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_05"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_06"), PTR(majin_callback), 0)
        CALL(evt_mario_set_pose, STRING("M_I_Z"))
        WAIT_MS(1600)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("stg1_gon_12_07"), PTR(majin_callback), 0)
        // The talk is over: the chest keeps the story-flag so it only plays once.
        CALL(evt_mobj_exec_cancel, STRING("box"))
        SET_VALUE(GSWF(GSWF_GON06_BLACK_CHEST_TALKED), 1)
        CALL(evt_cam3d_evt_off, 500, 11)
    ELSE
        // Later visits: without the Black Key the chest reminds Mario to find it.
        CALL(evt_pouch_check_item, ITEM_BLACK_KEY_0x22, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
            ADD(LW(1), 30)
            CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
            CALL(evt_msg_print, 0, STRING("stg1_gon_12_08"), PTR(majin_callback), 0)
            CALL(evt_mobj_exec_cancel, STRING("box"))
        ELSE
            // Mario carries the Black Key: the chest greets him.
            CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
            ADD(LW(1), 30)
            CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
            CALL(evt_msg_print, 0, STRING("stg1_gon_12_09"), PTR(majin_callback), 0)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
                IF_INT_LESS_OR_EQUAL(LW(3), LW(0))
                    CALL(evt_mario_set_dir, 90, 200, 0)
                ELSE
                    CALL(evt_mario_set_dir, 270, 200, 0)
                END_IF
            END_INLINE_EVENT
            // Mario picks an item to open the chest with.
#if VERSION <= VERSION_DEMO_JP
            CALL(evt_win_item_select, PTR(key_tbl), LW(0))
#else
            CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
#endif
            // Mario backs out of the menu and the chest tells him to use the key.
            IF_INT_EQUAL(LW(0), -1)
                CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
                ADD(LW(1), 30)
                CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
                CALL(evt_msg_print, 0, STRING("stg1_gon_12_10"), PTR(majin_callback), 0)
                CALL(evt_mobj_exec_cancel, STRING("box"))
            ELSE
                // Mario hands over the Black Key and the partner steps aside; the chest cackles as the curse is
                // set up.
                BEGIN_INLINE_EVENT
                    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                    ADD(LW(0), 35)
                    ADD(LW(2), 35)
                    CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(80.0f))
                END_INLINE_EVENT
                CALL(evt_pouch_remove_item, ITEM_BLACK_KEY_0x22, LW(0))
                CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
                ADD(LW(1), 30)
                ADD(LW(1), 50)
                CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
                CALL(evt_msg_print, 0, STRING("stg1_gon_12_11"), PTR(majin_callback), 0)
#if VERSION >= VERSION_JP
                CALL(evt_mario_set_pose, STRING("M_I_N"))
#endif
                CALL(evt_cam3d_evt_set, 380, 110, 330, 380, 57, 23, 500, 11)
            END_IF
        END_IF
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Event after the black chest is opened: Mario receives the Paper Curse item (ITEM_PAPER_CURSE),
 * the Paper Mage's music starts and the Paper Mage appears from the paper image OFF_d_kusya
 * and gives his lecture (slit_majin_lecture), then leaves.
 * The story advances to STORY_STG1_13_01_01_PAPER_MAGE_2 (or STORY_STG1_13_A_SUSPICIOUS_ROOM if it is already
 * past that), the bero case and ceiling events are started,
 * five Dry Bones NPCs (KRN_Z_2) are entered in the cell and the red cell switch (mobj_switch1) is placed.
 */
static EVT_BEGIN(evt_majin2)
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    CALL(evt_mario_key_onoff, 0)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_mario_normalize)
#endif
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_pouch_add_item, ITEM_PAPER_CURSE, LW(0))
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_EVT_PERAMAJIN1"))
    CALL(evt_snd_envoff, PSND_FADE_HOLD)
    CALL(bgm_start_wait)
    WAIT_MS(1000)
    CALL(evt_paper_entry, STRING("OFF_d_kusya"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_kusya"))
    CALL(evt_img_alloc_capture, STRING("img"), 0, 0, 1, 0, 0, 608, 480)
    CALL(evt_img_set_virtual_point, STRING("img"), 380, 0, -50)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_img_clear_virtual_point, STRING("img"))
    END_INLINE_EVENT
    CALL(evt_img_onoff, STRING("img"), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_APPEAR1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_COME1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_mario_set_camid, 7)
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(lect_cam_save)
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    WAIT_FRAMES(1)
    CALL_CHILD(slit_majin_lecture_init)
    CALL_CHILD(slit_majin_lecture)
    LOOP(6)
        CALL(evt_mario_dispflag_onoff, 1, 1)
        WAIT_MS(100)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_PERAMAJIN_BLINKING1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_dispflag_onoff, 0, 1)
        WAIT_MS(100)
    END_LOOP
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_mario_set_pos, LW(10), LW(11), LW(12))
    CALL(evt_mario_dispflag_onoff, 0, 1)
    CALL(evt_mario_init_camid)
    CALL(lect_cam_load, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_GOOUT1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT | PSND_CH(1), 2000)
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_2"))
    CALL(evt_img_wait_animend, STRING("img"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_PERAMAJIN_GOOUT2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_img_release, STRING("img"))
    CALL(evt_paper_delete, STRING("OFF_d_kusya"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG1_13_01_01_PAPER_MAGE_2)
    SET_VALUE(GSWF(GSWF_GON06_BLACK_CHEST_OPENED), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_snd_envoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_npc_start_for_event)
    RETURN
EVT_END()

/**
 * Map init for gon_06: sets up the doors, six dormant Dry Bones, the red switch for the bar grid,
 * the Attack FX R badge, and the black chest (box) that speaks to Mario and holds the Paper Curse;
 * once the story is past STORY_STG1_13_01_01_PAPER_MAGE_2 the chest counts as already opened.
 */
EVT_BEGIN(gon_06_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG1_13_A_SUSPICIOUS_ROOM)
        SPAWN_EVENT(bero_case_entry)
        SPAWN_EVENT(tsuritenjo_event)
    ELSE
        CALL_CHILD(evt_bero_info_run)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG1_GON1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG1_GON1"))
        CALL(evt_snd_set_rev_mode, 2)
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    END_IF
    CALL(evt_npc_entry, STRING("\"カロン00\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン00\""), -467, 0, 76)
    CALL(evt_npc_set_rotate, STRING("\"カロン00\""), 0, 0, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン00\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン00\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン00\""), NPC_FLAG_NO_AUTO_UPDATE)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン00\""), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_set_width, STRING("\"カロン00\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン00\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン01\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン01\""), -361, 0, -83)
    CALL(evt_npc_set_rotate, STRING("\"カロン01\""), 0, 180, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン01\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン01\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン01\""), NPC_FLAG_NO_AUTO_UPDATE)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン01\""), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_set_width, STRING("\"カロン01\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン01\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン02\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン02\""), -222, 0, 52)
    CALL(evt_npc_set_rotate, STRING("\"カロン02\""), 0, 0, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン02\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン02\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン02\""), NPC_FLAG_NO_AUTO_UPDATE)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン02\""), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_set_width, STRING("\"カロン02\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン02\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン03\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン03\""), 8, 0, -115)
    CALL(evt_npc_set_rotate, STRING("\"カロン03\""), 0, 180, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン03\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン03\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン03\""), NPC_FLAG_NO_AUTO_UPDATE)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン03\""), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_set_width, STRING("\"カロン03\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン03\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン04\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン04\""), 343, 0, -49)
    CALL(evt_npc_set_rotate, STRING("\"カロン04\""), 0, 0, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン04\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン04\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン04\""), NPC_FLAG_NO_AUTO_UPDATE)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン04\""), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_set_width, STRING("\"カロン04\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン04\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン05\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン05\""), 541, 0, 96)
    CALL(evt_npc_set_rotate, STRING("\"カロン05\""), 0, 180, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン05\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン05\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン05\""), NPC_FLAG_NO_AUTO_UPDATE)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン05\""), NPC_FLAG_NO_BILLBOARD)
    CALL(evt_npc_set_width, STRING("\"カロン05\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン05\""), 7)
    CALL(evt_mobj_switch_red, 0, STRING("mobj_switch1"), 92, 0, 120, PTR(evt_ori_open), GSWF(GSWF_GON06_CELL_SWITCH))
    CALL(evt_item_entry, STRING("item01"), ITEM_ATTACK_FX_R, -100, 0, -100, ITEM_ENTRY_FIXED, GSWF(GSWF_GON06_ATTACK_FX_R_TAKEN), 0)
    CALL(evt_sub_rumble_onoff, 1, 0)
    WAIT_FRAMES(1)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_map_playanim, STRING("hokori"), 1, 0)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG1_13_01_01_PAPER_MAGE_2)
        SET_VALUE(GSWF(GSWF_GON06_BLACK_CHEST_OPENED), 1)
    END_IF
    CALL(evt_mobj_itembox, STRING("box"), 380, 0, 0, 3, PTR(evt_majin), PTR(evt_majin2), GSWF(GSWF_GON06_BLACK_CHEST_OPENED))
    CALL(evt_mobj_flag_onoff, 0, STRING("box"), MOBJ_FLAG_FALL)
    RETURN
EVT_END()
