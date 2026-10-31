// moo_02 (月, the Moon): the field with the way into the X-Naut Fortress (aji_00); paths to moo_05 and moo_06.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_case.h"
#include "evt/evt_hit.h"
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_paper.h"
#include "evt/evt_snd.h"
#include "party/party_motion.h"
#include "moo.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "driver/mapdrv.h"

static BeroEntry bero_entry_data[6];

EVT_BEGIN(n_bero_in)
    CALL(evt_mario_bgmode_on)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mario_cam_y_off)
    CALL(evt_hit_get_position, STRING("n_bero"), LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL_CHILD(PTR(bero_case_entry))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(n_bero_out)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_mapchange, STRING("aji_19"), STRING("w_bero"))
    SET_VALUE(LW(0), 1)
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
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "moo_05", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_2", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "n_bero", // hitName
        4099, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)n_bero_in, // enterEvent
        5, // caseType
        (s32*)n_bero_out, // exitEvent
        "aji_00", // nextMapName
        "w_bero", // nextBeroName
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
        "moo_06", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static EVT_BEGIN(dokan_evt)
#if VERSION >= VERSION_US
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_07_A_PIPE_APPEARS)
#else
    CALL(evt_mario_key_onoff, 0)
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mapobj_get_position, STRING("S_iwa_04"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_WALL_BREAK1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 0, STRING("S_iwa_04"), STRING("offscreen"))
#if VERSION >= VERSION_US
    CALL(evt_offscreen_get_boundingbox2, STRING("offscreen"), LW(0), LW(1), LW(2), LW(3))
    IF_INT_GREATER(LW(2), 0)
        IF_INT_GREATER(LW(3), 0)
#endif
            CALL(evt_img_entry, STRING("img"))
            CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_bom_ver2"))
#if VERSION >= VERSION_US
            CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("offscreen"), 1, 0, 0, 0, 0)
#else
    CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("offscreen"), 0, 0, 0, 0, 0)
#endif
            CALL(evt_img_clear_virtual_point, STRING("img"))
            CALL(evt_img_set_shadow, STRING("img"), 2)
            CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("S_iwa_04"), MAPOBJ_FLAG_HIDE)
#if VERSION >= VERSION_US
            CALL(evt_hitobj_onoff, STRING("A_iwa_04"), 1, 0)
#endif
            CALL(evt_img_wait_animend, STRING("img"))
            CALL(evt_img_free_capture, STRING("img"), 0)
            CALL(evt_img_set_shadow, STRING("img"), 0)
            CALL(evt_img_onoff, STRING("img"), 0)
            CALL(evt_img_release, STRING("img"))
#if VERSION >= VERSION_US
        END_IF
    END_IF
#endif
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_clear_offscreen, 0, STRING("S_iwa_04"))
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("S_iwa_04"), MAPOBJ_FLAG_HIDE)
#else
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_07_A_PIPE_APPEARS)
#endif
    CALL(evt_hitobj_onoff, STRING("A_iwa_04"), 1, 0)
#if VERSION <= VERSION_JP
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

#if VERSION <= VERSION_JP
static EVT_BEGIN(rock_main)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mapobj_get_position, LW(10), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_WALL_BREAK1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_offscreen_entry, STRING("offscreen"))
    CALL(evt_mapobj_set_offscreen, 0, LW(10), STRING("offscreen"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, LW(10), MAPOBJ_FLAG_HIDE)
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_d_bom_ver2"))
    CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("offscreen"), 0, 0, 0, 0, 0)
    CALL(evt_img_clear_virtual_point, STRING("img"))
    CALL(evt_img_set_shadow, STRING("img"), 2)
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_release, STRING("img"))
    CALL(evt_offscreen_delete, STRING("offscreen"))
    CALL(evt_mapobj_clear_offscreen, 0, LW(10))
    CALL(evt_hitobj_onoff, LW(11), 1, 0)
    RETURN
EVT_END()
#endif

static EVT_BEGIN(rock_evt0)
#if VERSION >= VERSION_US
    SET_VALUE(GSWF(GSWF_MOO02_ROCK_A_BOMBED), 1)
#else
    CALL(evt_mario_key_onoff, 0)
#endif
    SET_VALUE(LW(10), STRING("S_iwa_01"))
    SET_VALUE(LW(11), STRING("A_iwa_01"))
    CALL_CHILD(PTR(rock_main))
#if VERSION <= VERSION_JP
    SET_VALUE(GSWF(GSWF_MOO02_ROCK_A_BOMBED), 1)
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(rock_evt1)
#if VERSION >= VERSION_US
    SET_VALUE(GSWF(GSWF_MOO02_ROCK_B_BOMBED), 1)
#else
    CALL(evt_mario_key_onoff, 0)
#endif
    SET_VALUE(LW(10), STRING("S_iwa_07"))
    SET_VALUE(LW(11), STRING("A_iwa_07"))
    CALL_CHILD(PTR(rock_main))
#if VERSION <= VERSION_JP
    SET_VALUE(GSWF(GSWF_MOO02_ROCK_B_BOMBED), 1)
    CALL(evt_mario_key_onoff, 1)
#endif
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(moo_02_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_MON1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_MOO2"))
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_03"), 1, 0)
    CALL(evt_map_playanim, STRING("light"), 1, 0)
    CALL(evt_item_entry, STRING("item00"), ITEM_STAR_PIECE, -55, 0, -135, 16, GSWF(GSWF_MOO02_STAR_PIECE), 0)
    CALL(evt_paper_entry, STRING("OFF_d_bom_ver2"))
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_07_A_PIPE_APPEARS)
        CALL(evt_run_case_evt, CASE_COND_BOBBERY, 1, STRING("A_iwa_04"), 0, PTR(dokan_evt), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_04"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_iwa_04"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_MOO02_ROCK_A_BOMBED), 0)
        CALL(evt_run_case_evt, CASE_COND_BOBBERY, 1, STRING("A_iwa_01"), 0, PTR(rock_evt0), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_01"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_iwa_01"), 1, 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_MOO02_ROCK_B_BOMBED), 0)
        CALL(evt_run_case_evt, CASE_COND_BOBBERY, 1, STRING("A_iwa_07"), 0, PTR(rock_evt1), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_iwa_07"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_iwa_07"), 1, 0)
    END_IF
    CALL(evt_item_entry, STRING("item_01"), ITEM_POWER_PUNCH, 330, 0, 403, 16, GSWF(GSWF_MOO02_POWER_PUNCH), 0)
    RETURN
EVT_END()
