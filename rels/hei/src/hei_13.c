// hei_13 (平原, Petal Meadows): field linking hei_00 and hei_01 with pipes.
// Horsetail item, a Close Call block, bricks and a Happy Heart.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "evt/evt_case.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mobj.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "hei.h"
#include "data_tables.h"
#include "version.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"

static BeroEntry bero_entry_data[5];
static TreeAccess ki_data[2];
extern EvtWord evt_anm_kan[];

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
        "hei_00", // nextMapName
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
        "hei_01", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "a_dokan_1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "a_dokan_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "a_dokan_2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "a_dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static TreeAccess ki_data[] = {
    {0, "a_ki_1", "miki_", "ha_temae", "ha_usiro", NULL},
    {7, NULL, NULL, NULL, 0, NULL},
};

EVT_BEGIN(evt_anm_kan)
    IF_INT_EQUAL(GF(0), 1)
        GOTO(99)
    END_IF
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(GSW(GSW_HEI13_CAN_HITS), 10)
            SET_VALUE(GF(0), 1)
            WAIT_MS(200)
            CALL(evt_item_entry, STRING("item_tukushi"), ITEM_HORSETAIL, 565, 15, -65, ITEM_ENTRY_LAUNCH_5S, -1, 0)
        ELSE
            ADD(GSW(GSW_HEI13_CAN_HITS), 1)
            IF_INT_EQUAL(GSW(GSW_HEI13_CAN_HITS), 10)
                SET_VALUE(GF(0), 1)
                WAIT_MS(200)
                CALL(evt_item_entry, STRING("item_tukushi"), ITEM_HORSETAIL, 565, 15, -65, ITEM_ENTRY_LAUNCH_5S, -1, 0)
            END_IF
        END_IF
    END_INLINE_EVENT
    LABEL(99)
    CALL(evt_map_playanim, STRING("anm_kan_1"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(hei_13_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    SET_VALUE(GF(0), 0)
    SET_VALUE(GSW(GSW_HEI13_CAN_HITS), 0)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_mobj_badgeblk, STRING("m"), -320, 60, -100, ITEM_CLOSE_CALL, 0, GSWF(GSWF_HEI13_CLOSE_CALL_BLOCK_HIT), 1)
    SET_VALUE(LSWF(3), 0)
    CALL(evt_mobj_brick, STRING("mm"), 325, 175, -100, 0, 0, 0, LSWF(3))
    IF_INT_EQUAL(LSWF(3), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("mm"), MOBJ_FLAG_NO_SHADOW)
    END_IF
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_CLEAR(LW(0), GLOBAL_FLAG_KIOSK)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_item_entry, STRING("i"), ITEM_HAPPY_HEART, 325, 200, -100, ITEM_ENTRY_STAY, GSWF(GSWF_HEI13_HAPPY_HEART_TAKEN), 0)
#else
        CALL(evt_item_entry, STRING("i"), ITEM_HAPPY_HEART, 325, 200, -100, ITEM_ENTRY_FIXED, GSWF(GSWF_HEI13_HAPPY_HEART_TAKEN), 0)
#endif
    END_IF
    CALL(evt_mobj_brick, STRING("10m"), 325, 60, -100, 0, 3, 0, GSWF(GSWF_HEI13_COIN_BRICK_EMPTIED))
    SET_VALUE(LW(0), PTR(ki_data))
    CALL_CHILD(evt_sub_tree_access_entry)
    CALL(evt_map_playanim, STRING("anm_mugi"), 1, 0)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG1_HEI1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG1_HEI1"))
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_CLEAR(LW(0), GLOBAL_FLAG_KIOSK)
        CALL(evt_run_case_evt, CASE_COND_HAMMER, 1, STRING("a_kan_5"), 0, PTR(evt_anm_kan), 0)
    END_IF
    RETURN
EVT_END()
