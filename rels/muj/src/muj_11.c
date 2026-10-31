// muj_11 (無人島, Keelhaul Key): the passage between muj_10 and Cortez's lair, with its warning
// event (warning_event).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_snd.h"
#include "muj.h"
#include "evt/evt_story.h"

static BeroEntry bero_entry_data[3];
extern EvtWord warning_event[];

static EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "muj_10", // nextMapName
        "A_b_bero03", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_close, // enterAnimeArg
        w_open, // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "muj_12", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_close, // enterAnimeArg
        e_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(warning_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon, STRING("SFX_STG5_ELMOS_VOICE1"), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon, STRING("SFX_STG5_ELMOS_VOICE1"), 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg5_dou_20"), 0, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG5_32_CORTEZS_WARNING)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(muj_11_init_evt)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG5_33_CORTEZ_AND_THE_TREASURE)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG5_GHOST1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
    ELSE
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG5_DOU1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG5_MUJ9"))
    END_IF
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_31_FOUR_EYES)
        SPAWN_EVENT(warning_event)
    END_IF
#if VERSION <= VERSION_DEMO_US
    // the demo has a heart block and a save block in this room
    CALL(evt_mobj_recovery_blk, STRING("r_blk"), 12, 0, 60, -20, 0, 0)
    CALL(evt_mobj_save_blk, STRING("s_blk"), 50, 60, -20, 0, 0)
#endif
    RETURN
EVT_END()
