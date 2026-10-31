// tou_13 (闘技場, Glitz Pit): the small passage between tou_05 and tou_07.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "tou.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "driver/mapdrv.h"
#include "driver/camdrv.h"

/** Exits of this passage: east to the champion's room tou_07 and west to Grubba's office tou_05. */
static BeroEntry bero_data[] = {
    {
        "e_bero_", // hitName
        0, 0, // type..sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_07", // nextMapName
        "e_bero", // nextBeroName
        0, 0, 0, 0, // enterAnimeType..exitAnimeArg
    },
    {
        "w_bero_", // hitName
        0, 0, // type..sfxId
        BERO_DIR_E, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_05", // nextMapName
        "w_bero", // nextBeroName
        0, 0, 0, 0, // enterAnimeType..exitAnimeArg
    },
    {0},
};

/**
 * Air duct scene: the duct cover is knocked off with a camera shake and clang,
 * the vent cover s_deguti is hidden and its hit object deguti switched off,
 * and the entrance switch is turned on.
 * The first time the story advances to STORY_STG3_30_04_AIR_DUCT_EXIT;
 * on later visits GSWF_TOU13_DUCT_EXIT_OPEN_REVISIT is set instead. The case event then exits.
 */
static EVT_BEGIN(evt_dakuto)
    CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.049804688f), FLOAT(0.0f), 500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_DUCT_KOUSHI_HIT1"), 188, 0, 0, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_deguti"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("deguti"), 1, 0)
    SET_VALUE(LW(0), 1)
    CALL_CHILD(bero_case_switch_on)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_04_AIR_DUCT_EXIT)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_04_AIR_DUCT_EXIT)
    ELSE
        SET_VALUE(GSWF(GSWF_TOU13_DUCT_EXIT_OPEN_REVISIT), 1)
    END_IF
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/**
 * Eavesdropping scene, run before STORY_STG3_30_03_EAVESDROPPING once Mario walks past x 75:
 * muffled talk comes through the wall (stg3_tou_455_01) and Mario and the partner step closer.
 * Grubba's voice gloats that "that baby" keeps his body from ever getting weak (455_02),
 * the partner recognizes Grubba and suspects him of the fighters' disappearances (455_05),
 * and Grubba says he will lock the room up, hide the paper about it in his desk drawer (455_03)
 * and that the new champ may have to disappear (455_04). The story advances to STORY_STG3_30_03_EAVESDROPPING.
 */
EVT_BEGIN(evt_nusumi)
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), 75)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_wait_landon)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_toge, 2, 200, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_01"), 0, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING("m"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING("p"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 60, 0, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 100, 0, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_cam3d_evt_set, 125, 100, 337, 125, 40, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 200, 40, 0)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_02"), 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_455_05"))
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 200, 40, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_03"), 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 2, 200, 40, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_455_04"), 0, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_03_EAVESDROPPING)
    RETURN
EVT_END()

/**
 * First visit to the passage: waits until Mario has walked past x=-120, then stops him,
 * the partner remarks stg3_tou_455 and the story advances to STORY_STG3_30_02_AIR_DUCT_1ST_TIME.
 */
static EVT_BEGIN(evt_first)
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), -120)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_wait_landon)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_455"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_02_AIR_DUCT_1ST_TIME)
    RETURN
EVT_END()

/**
 * Map init for tou_13, the passage between Grubba's office and the champion's room:
 * music by story stage, the air-duct exit (deguti, broken with the hammer)
 * and the entry scenes by story progress.
 */
EVT_BEGIN(tou_13_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG3_00_WELCOME_TO_GLITZVILLE, STORY_STG3_12_MINI_YOSHI_EGG)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
#else
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU7"))
#endif
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_GREATER_OR_EQUAL(STORY_STG3_33_PEACH_THE_SECRET_WEAPON)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
#else
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU7"))
#endif
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU7"))
        CALL(evt_snd_set_rev_mode, 2)
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_30_04_AIR_DUCT_EXIT)
        SET_VALUE(LF(0), 0)
        CASE_LESS(STORY_STG3_34_RETURN_TO_ROGUEPORT)
        SET_VALUE(LF(0), 1)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU13_DUCT_EXIT_OPEN_REVISIT), 0)
            SET_VALUE(LF(0), 0)
        ELSE
            SET_VALUE(LF(0), 1)
        END_IF
    END_SWITCH
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_run_case_evt, CASE_COND_HAMMER_2, 1, STRING("deguti"), 0, PTR(evt_dakuto), 0)
        SET_VALUE(LW(0), 1)
        CALL_CHILD(bero_case_switch_off)
    ELSE
        CALL(evt_hitobj_onoff, STRING("deguti"), 1, 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_deguti"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_03_EAVESDROPPING)
        SPAWN_EVENT(evt_nusumi)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_30_02_AIR_DUCT_1ST_TIME)
        SPAWN_EVENT(evt_first)
    END_IF
    RETURN
EVT_END()
