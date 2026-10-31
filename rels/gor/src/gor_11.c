// gor_11 (ゴロツキタウン, Rogueport): epilogue sea scene (ending, story flag 402); on finish returns to gor_00.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_fade.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "party.h"
#include "gor.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"

/**
 * Ending sequence on the sea view: fades out the music, starts the sea ambience,
 * freezes and hides Mario and the partner, fades the screen black for 5 seconds and back in over 1 second,
 * holds it for 5 more seconds (JP and later then fade the ambience out)
 * and changes the map to gor_00 (Rogueport).
 */
static EVT_BEGIN(epilogue_evt)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_END_MUJ1"))
    CALL(evt_cam_ctrl_onoff, 4, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_party_dispflg_onoff, 0, PARTY_DISP_FLAG_HIDDEN, 1)
    CALL(evt_seq_wait, 2)
    CALL(evt_fade_entry, FADE_OUT_BLACK, 1, 0, 0, 0)
    WAIT_MS(2000)
    WAIT_MS(3000)
    CALL(evt_fade_in, 1000)
    WAIT_MS(5000)
#if VERSION >= VERSION_JP
    CALL(evt_snd_envoff_f, PSND_FADE_OUT, 3000)
#endif
    CALL(evt_fade_set_mapchange_type, 0, FADE_OUT_BLACK, 1500, -1, -1)
    CALL(evt_bero_mapchange, STRING("gor_00"), STRING(""))
    RETURN
EVT_END()

/**
 * Init script of gor_11, the sea view of the ending:
 * plays the sea animations and, when the story is at STORY_STG8_END_AFTER_THE_BATTLE,
 * removes the partner and runs the epilogue (fade in, ambience, fade out, then back to gor_00).
 * JP and later skip it if map events are being skipped.
 */
EVT_BEGIN(gor_11_init_evt)
    CALL(evt_map_playanim, STRING("anm_umi"), 1, 0)
    CALL(evt_map_playanim, STRING("anm_nami"), 1, 0)
#if VERSION >= VERSION_JP
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_SKIP_MAP_EVENTS)
        RETURN
    END_IF
#endif
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG8_END_AFTER_THE_BATTLE)
        CALL(evt_mario_kill_party, 0)
        SPAWN_EVENT(epilogue_evt)
    END_IF
    RETURN
EVT_END()
