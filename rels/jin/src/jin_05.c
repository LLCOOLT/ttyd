// jin_05 (ダイム寺院, Creepy Steeple): treasure room with chests holding Cookbook and Ice Smash, a Star Piece and a
// power-up block; door to jin_00.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_item.h"
#include "driver/itemdrv.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "jin.h"
#include "evt/evt_story.h"

static BeroEntry bero_entry_data[2];
extern EvtWord item_box_00[];

/**
 * Exit event of the roll-through doorway: returns 0 in LW(0), which blocks the exit,
 * while Mario is in motion 22 (MARIO_MOTION_ROLL, the paper-roll form), and 1 otherwise.
 */
static EVT_BEGIN(check_roll)
    CALL(evt_mario_get_motion, LW(0))
    IF_INT_EQUAL(LW(0), 22)
        SET_VALUE(LW(0), 0)
    ELSE
        SET_VALUE(LW(0), 1)
    END_IF
    RETURN
EVT_END()

/** Doors of this room: the south exit (s_bero) to jin_00. */
static BeroEntry bero_entry_data[] = {
    {
        "s_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        (s32*)check_roll, // exitEvent
        "jin_00", // nextMapName
        "n_bero_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Chest script for mobj_box00: freezes Mario, makes the Cookbook appear from the chest
 * and gives it to him once the lid has opened.
 */
EVT_BEGIN(item_box_00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("_item00"), ITEM_COOKBOOK, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
    CALL(evt_item_flag_on, STRING("_item00"), ITEM_FLAG_NO_TOUCH)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("_item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Chest script for the Ice Smash chest (mobj_box01):
 * the item appears at the chest while it opens and Mario receives the badge; control is locked meanwhile.
 */
static EVT_BEGIN(mobj_box01)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box01"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("_item01"), ITEM_ICE_SMASH, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_item_flag_on, STRING("_item01"), ITEM_FLAG_NO_TOUCH)
#else
    CALL(evt_item_flag_on, STRING("_item01"), ITEM_FLAG_BADGE_RETURN | ITEM_FLAG_NO_TOUCH)
#endif
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box01"))
    CALL(evt_item_get_item, STRING("_item01"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Creepy Steeple jin_05 map init: starts the steeple music and reverb, the shadow-Mario tint and the exit,
 * and places a power-up block (Shine Sprite), the Cookbook chest, the Ice Smash chest and a Star Piece.
 */
EVT_BEGIN(jin_05_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(evt_usu_kagemario_party_kill)
    CALL(evt_mobj_powerupblk, STRING("pblk00"), 65, 60, 35, 0, GSWF(GSWF_JIN05_SHINE_SPRITE), 0)
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 125, 0, 75, 0, 0, PTR(item_box_00), GSWF(GSWF_JIN05_COOKBOOK_CHEST_OPENED))
    CALL(evt_mobj_itembox, STRING("mobj_box01"), -55, 0, 55, 0, 0, PTR(mobj_box01), GSWF(GSWF_JIN05_ICE_SMASH_CHEST_OPENED))
    CALL(evt_item_entry, STRING("item_00"), ITEM_STAR_PIECE, -10, 0, -40, ITEM_ENTRY_FIXED, GSWF(GSWF_JIN05_STAR_PIECE), 0)
    RETURN
EVT_END()
