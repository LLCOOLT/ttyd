// pik_03 (ピカリーヒルズ, Poshley Sanctum): the hidden inner room of the sanctum.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_fade.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "pik.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"

static BeroEntry bero_data[2];

/**
 * Enter-event of the s_bero entrance of the hidden room:
 * places Mario and the partner at the entrance and walks them forward into the room with the letter box off,
 * then turns on the case events for the entrance. Returns 1 in LW(0).
 */
EVT_BEGIN(bero_in)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, 0, 0, 660)
    CALL(evt_party_set_pos, 0, -10, 0, 670)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 35, 610, FLOAT(120.0f))
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_cam_letter_box_disable, 0)
        CALL_CHILD(bero_case_entry)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 10, 620, FLOAT(120.0f))
    END_INLINE_EVENT
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

/**
 * Exit-event of the s_bero entrance: locks the controls, gets Mario off Yoshi (evt_party_yoshi_ride),
 * walks Mario back out of the room and changes map to pik_02 at h_bero while the partner follows.
 * Returns 1 in LW(0).
 */
EVT_BEGIN(bero_out)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_yoshi_ride, 0, 0)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("s_bero"), 8388608)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 35, 610, FLOAT(120.0f))
        CALL(evt_mario_mov_pos2, -10, 670, FLOAT(120.0f))
        CALL(evt_bero_mapchange, STRING("pik_02"), STRING("h_bero"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_party_move_pos2, 0, 10, 620, FLOAT(120.0f))
        CALL(evt_party_move_pos2, 0, 0, 660, FLOAT(120.0f))
    END_INLINE_EVENT
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

/** Doors and exits of pik_03: s_bero to pik_02. */
static BeroEntry bero_data[] = {
    {
        "s_bero", // hitName
        1, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)bero_in, // enterEvent
        8, // caseType
        (s32*)bero_out, // exitEvent
        "pik_02", // nextMapName
        "h_bero", // nextBeroName
        4, // enterAnimeType
        4, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Examine script of the hidden room's altar: locks the controls,
 * sets story progress to STORY_STG6_53_THE_REAL_GARNET_STAR, stops the NPCs,
 * fades out the music (JP and later) and runs evt_sub_starstone for the Garnet Star (star number 6),
 * then returns the controls.
 */
static EVT_BEGIN(evt_daiza)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_53_THE_REAL_GARNET_STAR)
    CALL(evt_npc_stop_for_event)
    SET_VALUE(LW(0), 6)
    SET_VALUE(LW(1), STRING("star"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
#endif
    CALL_CHILD(evt_sub_starstone)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script for pik_03, the hidden room behind the sanctum: sets up the entrance, music and ambience;
 * before the real Garnet Star has been taken it places the Garnet Star item on the altar
 * and registers the case event (evt_daiza) that picks it up; also places the L Emblem and a Shine Sprite block.
 * When entered through "next" Mario and the partner are placed on the altar side and the screen fades in.
 */
EVT_BEGIN(pik_03_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_PIK3"))
    CALL(evt_snd_set_rev_mode, 2)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_53_THE_REAL_GARNET_STAR)
        CALL(evt_item_entry, STRING("star"), ITEM_GARNET_STAR, 0, 45, -950, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_53_THE_REAL_GARNET_STAR)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("dai_a"), 0, PTR(evt_daiza), 0)
    END_IF
    CALL(evt_item_entry, STRING("item01"), ITEM_L_EMBLEM, -305, 330, -990, ITEM_ENTRY_FIXED, GSWF(GSWF_PIK03_L_EMBLEM_TAKEN), 0)
    CALL(evt_mobj_powerupblk, STRING("pblk00"), -265, 290, 550, 0, GSWF(GSWF_PIK03_SHINE_SPRITE), 0)
    CALL(evt_map_entry_airport_harbor, 0, STRING("hikou"), STRING("a_hi1"))
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("next"))
        CALL(evt_mario_set_pos, -25, 9, -925)
        CALL(evt_party_set_pos, 0, 25, 9, -925)
        CALL(evt_mario_set_dir, 90, 0, 0)
        CALL(evt_party_set_dir, 0, 270, 0)
        CALL(evt_cam_road_reset)
        CALL(evt_mario_key_onoff, 0)
        BEGIN_INLINE_EVENT
            CALL(evt_seq_wait, 2)
            CALL(evt_fade_end_wait)
            CALL(evt_mario_key_onoff, 1)
        END_INLINE_EVENT
    END_IF
    RETURN
EVT_END()
