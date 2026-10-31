// win_05 (ウィンディん家周辺, Flurrie's house in Boggly Woods): inside Flurrie's house.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_fade.h"
#include "evt/evt_item.h"
#include "driver/itemdrv.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"
#include "win.h"
#include "evt/evt_story.h"

static BeroEntry bero_entry_data[2];

EVT_BEGIN(win_05_door_open)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SPAWN_EVENT(PTR(evt_win_door_open))
    RETURN
EVT_END()

EVT_BEGIN(win_05_door_close)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SPAWN_EVENT(PTR(evt_win_door_close))
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "win_04", // nextMapName
        "e_bero", // nextBeroName
        4, // enterAnimeType
        4, // exitAnimeType
        win_05_door_close, // enterAnimeArg
        win_05_door_open, // exitAnimeArg
    },
    {0},
};

static EVT_BEGIN(item_get00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), ITEM_SUPER_APPEAL_P, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), ITEM_FLAG_BADGE_RETURN | ITEM_FLAG_NO_TOUCH)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(cloud_toujou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("クラウダ"), 104, 13, 110)
    CALL(evt_cam3d_evt_set, 89, 95, 242, 43, 52, 0, 0, 11)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    CALL(evt_npc_wait_pera, STRING("クラウダ"))
    CALL(evt_seq_wait, 2)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_npc_get_position, STRING("クラウダ"), LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_00_04"), 0, STRING("クラウダ"))
    WAIT_MS(1000)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG2_03_03_FLURRIE_INTRO)
    CALL(evt_fade_set_mapchange_type, 0, FADE_OUT_BLACK, 100, FADE_IN_BLACK, 100)
    CALL(evt_bero_mapchange, STRING("win_03"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(win_05_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_itembox, STRING("mobj_box00"), -45, 0, -75, 0, 0, PTR(item_get00), GSWF(GSWF_WIN05_SUPER_APPEAL_P_CHEST_OPENED))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 64, 0, 118, STRING("S_yukaA"), 125, GSWF(GSWF_WIN05_STAR_PIECE_PANEL))
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG2_WIN1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_WIN2"))
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_03_02_SEALED_ENTRANCE_2)
        SPAWN_EVENT(PTR(cloud_toujou))
    END_IF
    RETURN
EVT_END()
