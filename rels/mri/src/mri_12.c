// mri_12 (巨木の中, The Great Tree): a junction room with planters and a Puni-ball pad, joining mri_11, mri_17
// and mri_18.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "evt/evt_case.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "mri_puni.h"
#include "mri.h"
#include "data_tables.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "driver/mapdrv.h"

static BeroEntry bero_entry_data[6];
static KusaAccess ueki_access_data[8];

static BeroEntry bero_entry_data[] = {
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
        "mri_11", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "e_bero_2", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "mri_17", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        10, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan3", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, // exitEvent
        "mri_18", // nextMapName
        "dokan1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static EVT_BEGIN(punipuni_ball00_init)
    CALL_CHILD(mri_punipuni_setup)
    IF_INT_EQUAL(GSWF(GSWF_MRI12_ORB_ON_PEDESTAL), 1)
        CALL(evt_item_set_position, LW(10), 5, 30, -95)
        CALL(evt_target_flag_onoff, LW(11), 0, 3)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_sui_hikari"), MAPOBJ_FLAG_HIDE)
    END_IF
    CALL(evt_target_set_position, LW(11), 5, 0, -65)
    RETURN
EVT_END()

static EVT_BEGIN(punipuni_ball00)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_EQUAL(GSWF(GSWF_MRI12_ORB_ON_PEDESTAL), 0)
        CALL_CHILD(mri_punipuni_itemselect)
        IF_INT_EQUAL(LW(1), 0)
            GOTO(100)
        END_IF
        SET_VALUE(GSWF(GSWF_MRI12_ORB_ON_PEDESTAL), 1)
        CALL(evt_item_set_position, LW(10), 5, 30, -95)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_sui_hikari"), MAPOBJ_FLAG_HIDE)
        CALL_CHILD(mri_punipuni_itemset)
    ELSE
        SET_VALUE(GSWF(GSWF_MRI12_ORB_ON_PEDESTAL), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_sui_hikari"), MAPOBJ_FLAG_HIDE)
        CALL_CHILD(mri_punipuni_itemremove)
    END_IF
    LABEL(100)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_f1_ueki_01)
    CALL(evt_item_delete_check, STRING("item_ueki_01"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_ueki_01"), ITEM_COIN, -190, -309, 65, ITEM_ENTRY_LAUNCH, GSWF(GSWF_MRI12_PLANTER_COIN_TAKEN), 0)
    END_IF
    RETURN
EVT_END()

static KusaAccess ueki_access_data[] = {
    {1, "A_f1_ueki01", "S_f1_ueki01", evt_f1_ueki_01},
    {1, "A_f1_ueki02", "S_f1_ueki02", NULL},
    {1, "A_f2_ueki01", "S_f2_ueki01", NULL},
    {1, "A_f2_ueki02", "S_f2_ueki02", NULL},
    {1, "A_f2_ueki03", "S_f2_ueki03", NULL},
    {1, "A_f2_ueki04", "S_f2_ueki04", NULL},
    {1, "A_f2_ueki05", "S_f2_ueki05", NULL},
    {4, NULL, NULL, NULL},
};

static EVT_BEGIN(breakyuka_init)
    IF_INT_EQUAL(GSWF(GSWF_MRI12_FLOOR_BROKEN), 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_01"), 1, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(breakyuka_main)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak_01"), 1, 1)
    CALL(evt_puni_all_fall_check)
    RETURN
EVT_END()

EVT_BEGIN(mri_12_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 12, 0, -250, -310, -1000, 3, 0)
    CALL(evt_puni_set_hamari, 0, 0, 0, 6, -6, -248, -312)
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
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(evt_sub_kusa_access_entry)
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
    CALL(evt_map_playanim, STRING("sui_hikari"), 1, 0)
    SPAWN_EVENT(breakyuka_init)
    CALL(evt_mobj_breaking_floor, STRING("mobj_bf00"), -45, 0, -64, 1, PTR(breakyuka_main), GSWF(GSWF_MRI12_FLOOR_BROKEN))
    SET_VALUE(LW(10), STRING("punipuni"))
    SET_VALUE(LW(11), 0)
    SPAWN_EVENT(punipuni_ball00_init)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_dai_mae"), 0, PTR(punipuni_ball00), 0)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_item_entry, STRING("item_00"), ITEM_STAR_PIECE, -175, -310, -85, ITEM_ENTRY_FIXED, GSWF(GSWF_MRI12_STAR_PIECE), 0)
    RETURN
EVT_END()
