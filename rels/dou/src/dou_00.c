// dou_00 (洞窟, Pirate's Grotto): entrance cave reached from Keelhaul Key (muj_05).
// Arrival cutscene (story 242 to 243), a save block and Ruin Powder; the door leads to dou_01.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "driver/animdrv.h"

#include "driver/mapdrv.h"
#include "driver/envdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_telop.h"
#include "dou.h"
#include "evt/evt_story.h"

static void water_tev(MapTevCallbackInfo* info);

static BeroEntry bero_entry_data[3];
extern EvtWord totsunyu_event[];

static EVT_BEGIN(bero_in_event)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_19_SKULL_ROCK)
        CALL_CHILD(totsunyu_event)
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)bero_in_event, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "muj_05", // nextMapName
        "e_bero", // nextBeroName
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
        "dou_01", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static EVT_BEGIN(back_light)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_blend_set_flag, 0, STRING("mario"), ANIM_MATERIAL_FLAG_NO_BLEND)
    CALL(evt_map_blend_off, 0)
    RETURN
EVT_END()

EVT_BEGIN(totsunyu_event)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_dou_00"), 0, 0)
    SPAWN_EVENT(back_light)
    WAIT_MS(200)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_19_01_ENTERING_THE_GROTTO)
    CALL(evt_mario_key_onoff, 1)
    BEGIN_INLINE_EVENT
        CALL(evt_telop_entry, 10)
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(dou_00_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG5_DOU1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG5_DOU1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    WAIT_FRAMES(1)
    CALL(evt_map_playanim, STRING("nami"), 1, 0)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 30, 85, -75, 0, 0)
    CALL(evt_item_entry, STRING("item_01"), ITEM_RUIN_POWDER, -245, 0, 85, ITEM_ENTRY_FIXED, GSWF(GSWF_DOU00_RUIN_POWDER_TAKEN), 0)
    CALL(evt_map_set_tevcallback, 1, PTR(water_tev))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s00_suimen"), MAPOBJ_TEV_CALLBACK(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s00_suimen"), MAPOBJ_FLAG_DISPLAY_LIST)
    RETURN
EVT_END()

static void water_tev(MapTevCallbackInfo* info) {
    envSetWater(info);
}
