// gor_12 (ゴロツキタウン, Rogueport): final epilogue sea scene (ending, story flag 402); on finish goes to aaa_00 (title).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_sub.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_fade.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "party.h"
#include "gor.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"

static EVT_BEGIN(epilogue_evt)
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_END_MUJ1"))
    CALL(evt_cam_ctrl_onoff, 4, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_party_dispflg_onoff, 0, PARTY_DISP_FLAG_HIDDEN, 1)
    CALL(evt_seq_wait, 2)
    WAIT_MS(7000)
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 8000)
    CALL(evt_snd_envoff_f, PSND_FADE_OUT, 8000)
    CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_BLACK, 4000, FADE_IN_BLACK, 300)
    CALL(evt_bero_mapchange, STRING("aaa_00"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(gor_12_init_evt)
    CALL(evt_map_playanim, STRING("anm_umi"), 1, 0)
    CALL(evt_map_playanim, STRING("anm_nami"), 1, 0)
    CALL(evt_map_playanim, STRING("anm_kirakira"), 1, 0)
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
EVT_END_PAD()
