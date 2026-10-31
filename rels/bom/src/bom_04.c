// bom_04 (ボム村, Fahr Outpost): the snowfield between bom_03 and the village (bom_01).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "bom.h"
#include "data_tables.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

static TreeAccess tree_tbl[4];
static BeroEntry bero_entry_data[3];

static TreeAccess tree_tbl[] = {
    {3, "A_ki1", "S_ki_1", "S_ha_1", 0, NULL},
    {3, "A_ki2", "S_ki_2", "S_ha_2", 0, NULL},
    {3, "A_ki3", "S_ki_3", "S_ha_3", 0, NULL},
    {7, NULL, NULL, NULL, 0, NULL},
};

static EVT_BEGIN(evt_tree)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(evt_sub_tree_access_entry)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero4", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "bom_03", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "e_bero4", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "bom_01", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(bom_04_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(evt_bom_snowfall)
    CALL_CHILD(evt_tree)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_BOM1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_BOM1"))
    CALL(evt_item_entry, STRING("item00"), ITEM_STAR_PIECE, 450, 5, 110, ITEM_ENTRY_FIXED, GSWF(GSWF_BOM04_STAR_PIECE), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_badge_gat"), 150, 0, -75, ITEM_HP_PLUS_P, 0, GSWF(GSWF_BOM04_HP_PLUS_P), 1)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_bom04_hei2"), MAPOBJ_FLAG_BBOX_CULL)
    RETURN
EVT_END()
