// hei_11 (平原, Petal Meadows): Shhwonk Fortress passage between hei_10 and hei_12.
// Only the map doors, water and field enemies.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_map.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "hei.h"
#include "driver/mapdrv.h"

extern s32 hei_test_water_tev[];

static BeroEntry bero_entry_data[3];

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "hei_10", // nextMapName
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
        "hei_12", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Petal Meadows hei_11 map init: sets the fortress music and reverb
 * and the animated water effect (tev callback); nothing else.
 */
EVT_BEGIN(hei_11_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG1_TORIDE1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG1_HEI3"))
    CALL(evt_snd_set_rev_mode, 1)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_map_playanim, STRING("mizu"), 1, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(hei_test_water_tev))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("mizu"), MAPOBJ_TEV_CALLBACK(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("mizu"), MAPOBJ_FLAG_DISPLAY_LIST)
    RETURN
EVT_END()
