// tik_14 (埋没した都市, Rogueport Sewers): a small pipe room with an item box.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_item.h"
#include "driver/itemdrv.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "tik.h"
#include "evt/evt_story.h"

static BeroEntry bero_entry_data[3];

static BeroEntry bero_entry_data[] = {
    {
        "dokan_1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_E, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        10, // caseType
        NULL, // exitEvent
        "tik_06", // nextMapName
        "dokan_3", // nextBeroName
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
        "tik_06", // nextMapName
        "dokan_3", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/** Item-box callback: puts a Mushroom at the box, waits for the chest animation and gives it to Mario. */
static EVT_BEGIN(item_get00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), ITEM_MUSHROOM, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), ITEM_FLAG_NO_TOUCH)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script of tik_14, a small pipe room.
 * Starts the sewer music and ambience, sets up the exit to tik_06
 * and places the item box holding a Mushroom (GSWF_TIK14_CHEST_OPENED).
 */
EVT_BEGIN(tik_14_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_TIK1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 0, 25, -110, 0, 0, PTR(item_get00), GSWF(GSWF_TIK14_CHEST_OPENED))
    RETURN
EVT_END()
