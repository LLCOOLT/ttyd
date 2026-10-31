// mri_10 (巨木の中, The Great Tree): a small room off mri_09 with an item box.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_item.h"
#include "evt/evt_lecture.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "mri_puni.h"
#include "mri.h"
#include "version.h"
#include "evt/evt_story.h"

static BeroEntry bero_entry_data[2];

/** Exit of mri_10: south road s_bero to mri_09 (n_bero). */
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
        NULL, // exitEvent
        "mri_09", // nextMapName
        "n_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Script after the Super Boots chest is opened:
 * the music is stopped, the Puni counter is hidden,
 * Super Boots appear above the chest and Mario collects them as an important item with the fanfare,
 * then the music returns, the story is set to STORY_STG2_21_03_SUPER_BOOTS and Mario can move again.
 */
static EVT_BEGIN(item_evt)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_envoff, PSND_FADE_HOLD)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_puni_puninum_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(lect_juyoitem_rel_set, PTR(all_juyoitem_lecture_rel))
    CALL(evt_item_entry, STRING("item00"), ITEM_SUPER_BOOTS, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_important_item, STRING("item00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_item_get_item_end_wait, STRING("item00"))
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_snd_envoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG2_21_03_SUPER_BOOTS)
    CALL(evt_puni_puninum_onoff, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script of mri_10, a small side room off mri_09 with a chest that holds the Super Boots;
 * plays the water animations and the room music.
 */
EVT_BEGIN(mri_10_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 10, 0, -310, -1000, -1000, 0, 0)
    CALL(evt_puni_set_hamari, 110, 0, 60, 2, -2, -1000, -1000)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(mri_puni_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    SPAWN_EVENT(puni_disp_info)
    SPAWN_EVENT(mri_countdown)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_23_TIME_BOMB_ACTIVATED, STORY_STG2_23_01_X_NAUT_BATTLE)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_MRI1"))
    END_SWITCH
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 0, 0, 25, 1, 0, PTR(item_evt), GSWF(GSWF_MRI10_SUPER_BOOTS_CHEST_OPENED))
    RETURN
EVT_END()
