// rsh_08 (列車, Excess Express): tiny connector room off rsh_01; only door data and an init event for the second trip
// (nidome).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_map.h"
#include "evt/evt_snd.h"
#include "rsh.h"
#include "evt/evt_story.h"

BeroEntry bero_data_a_nidome[2];
BeroEntry bero_data_b_nidome[2];
BeroEntry bero_data_c_nidome[2];

BeroEntry bero_data_a_nidome[] = {
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

BeroEntry bero_data_b_nidome[] = {
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_b", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

BeroEntry bero_data_c_nidome[] = {
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_c", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

/**
 * Init script of rsh_08_a, the connector room off rsh_01 (the only map of rsh_08):
 * picks the music for the station the train has reached (Poshley Heights, Rogueport or the train ambience),
 * chooses the door set that leads back to rsh_01 a,
 * b or c from the scenery variant flag (GSWF_RSH_REVISIT_VARIANT_A, B or C)
 * and starts the shaking train scenery.
 */
EVT_BEGIN(rsh_08_a_init_evt)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_POSHLEY), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
#if VERSION <= VERSION_DEMO_US
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR5"))
#else
            CALL(evt_snd_envoff, PSND_FADE_OUT)
#endif
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        ELSE
            CALL(evt_snd_bgmoff, PSND_FADE_OUT)
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        END_IF
    END_IF
    SET_VALUE(LW(0), PTR(bero_data_a_nidome))
    IF_INT_EQUAL(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 1)
        SET_VALUE(LW(0), PTR(bero_data_a_nidome))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 1)
        SET_VALUE(LW(0), PTR(bero_data_b_nidome))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 1)
        SET_VALUE(LW(0), PTR(bero_data_c_nidome))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_map_playanim, STRING("yure"), 1, 0)
    RETURN
EVT_END()
