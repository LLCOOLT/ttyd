// tik_16 (埋没した都市, Rogueport Sewers): the room with the pipes to The Great Tree (mri_00) and Petalburg (nok_01).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_damage.h"
#include "evt/evt_movefloor.h"
#include "driver/hitdrv.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "tik.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

static BeroEntry bero_entry_data[7];
static HitDamageReturn hitDmgRetPoints[9];

static BeroEntry bero_entry_data[] = {
    {
        "w_bero_2", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tik_17", // nextMapName
        "e_bero_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "w_bero_1", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tik_17", // nextMapName
        "e_bero_1", // nextBeroName
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
        "tik_15", // nextMapName
        "w_bero_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "e_bero_1", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tik_15", // nextMapName
        "w_bero_1", // nextBeroName
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
        NULL, // exitEvent
        "mri_00", // nextMapName
        "dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, // exitEvent
        "nok_01", // nextMapName
        "dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static HitDamageReturn hitDmgRetPoints[] = {
    {"mod_1", {0.0f, -1000.0f, 0.0f}},
    {"mod_2", {-250.0f, 0.0f, 0.0f}},
    {"mod_3", {-250.0f, 0.0f, 0.0f}},
    {"mod_4", {250.0f, 0.0f, 0.0f}},
    {"mod_5", {250.0f, 0.0f, 0.0f}},
    {"mod_6", {0.0f, -1000.0f, 0.0f}},
    {"a_dai_1", {0.0f, -1000.0f, 0.0f}},
    {"a_dai_2", {0.0f, -1000.0f, 0.0f}},
    {0},
};

/**
 * Map-init part for the Great Tree pipe.
 * Binds the pipe's hit to its model and, if GSWF_TIK16_PIPE_MRI_OPEN is set,
 * puts the pipe already risen (30 units up) and hides its cover.
 */
static EVT_BEGIN(evt_switch_00_init)
    CALL(evt_hit_bind_mapobj, STRING("a_dokan_1"), STRING("S_dakan_1"))
    IF_INT_EQUAL(GSWF(GSWF_TIK16_PIPE_MRI_OPEN), 1)
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_1"), 0, 30, 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_1"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("dokan_1_k"), MAPOBJ_FLAG_HIDE)
    END_IF
    RETURN
EVT_END()

/** Switches the Great Tree pipe's exit off if its switch has not been pressed yet. */
static EVT_BEGIN(evt_switch_00_after)
    IF_INT_EQUAL(GSWF(GSWF_TIK16_PIPE_MRI_OPEN), 0)
        SET_VALUE(LW(0), STRING("dokan_1"))
        CALL_CHILD(bero_case_switch_off)
    END_IF
    RETURN
EVT_END()

/**
 * Tornado switch handler for the Great Tree pipe:
 * the pipe rises 30 units over a second with the pipe-appear sound,
 * its cover is hidden and the exit is switched on.
 */
static EVT_BEGIN(evt_switch_00)
    CALL(evt_mapobj_get_position, STRING("S_dakan_1"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOKAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 30, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_1"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_1"))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("dokan_1_k"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(LW(0), STRING("dokan_1"))
    CALL_CHILD(bero_case_switch_on)
    RETURN
EVT_END()

/**
 * Map-init part for the Petalburg pipe.
 * Binds the pipe's hit to its model and, if GSWF_TIK16_PIPE_NOK_OPEN is set,
 * puts the pipe already risen and hides its cover.
 */
static EVT_BEGIN(evt_switch_01_init)
    CALL(evt_hit_bind_mapobj, STRING("a_dokan_2"), STRING("S_dakan_2"))
    IF_INT_EQUAL(GSWF(GSWF_TIK16_PIPE_NOK_OPEN), 1)
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_2"), 0, 30, 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_2"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("dokan_2_k"), MAPOBJ_FLAG_HIDE)
    END_IF
    RETURN
EVT_END()

/** Switches the Petalburg pipe's exit off if its switch has not been pressed yet. */
static EVT_BEGIN(evt_switch_01_after)
    IF_INT_EQUAL(GSWF(GSWF_TIK16_PIPE_NOK_OPEN), 0)
        SET_VALUE(LW(0), STRING("dokan_2"))
        CALL_CHILD(bero_case_switch_off)
    END_IF
    RETURN
EVT_END()

/**
 * Tornado switch handler for the Petalburg pipe:
 * the pipe rises 30 units over a second, its cover is hidden and the exit is switched on.
 */
static EVT_BEGIN(evt_switch_01)
    CALL(evt_mapobj_get_position, STRING("S_dakan_2"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOKAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 30, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_2"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_2"))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("dokan_2_k"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(LW(0), STRING("dokan_2"))
    CALL_CHILD(bero_case_switch_on)
    RETURN
EVT_END()

/**
 * Map init script of tik_16, the room with the pipes to The Great Tree (mri_00) and Petalburg (nok_01).
 * Sets up the two tornado switches that open each pipe (GSWF_TIK16_PIPE_MRI_OPEN and GSWF_TIK16_PIPE_NOK_OPEN),
 * the large block, a moving floor and a Shine Sprite power block, plus fall recovery and the water animation.
 */
EVT_BEGIN(tik_16_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_TIK7"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL_CHILD(evt_switch_00_init)
    CALL_CHILD(evt_switch_01_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(evt_switch_00_after)
    CALL_CHILD(evt_switch_01_after)
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(evt_gazigazi_entry)
    CALL(evt_map_playanim, STRING("anm_mizu"), 1, 0)
    CALL(evt_mobj_lv_blk, STRING("block"), 0, 0, 0, 0, GSWF(GSWF_TIK16_BIG_BLOCK_BROKEN), STRING("MOBJ_Lv1BigBigBlock"))
    IF_INT_EQUAL(GSWF(GSWF_TIK16_BIG_BLOCK_BROKEN), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("block"), MOBJ_FLAG_NO_CULL)
    END_IF
    SET_VALUE(LW(0), STRING("dai_3"))
    SET_VALUE(LW(1), STRING("a_dai_3"))
    SET_VALUE(LW(2), 0)
    SET_VALUE(LW(3), -75)
    SET_VALUE(LW(4), 2000)
    SET_VALUE(LW(5), 500)
    SET_VALUE(LW(6), 1)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(12), 0)
    SPAWN_EVENT(moving_floor)
    CALL(evt_mobj_tornadoswitch_blue, 0, STRING("switch00"), -125, 0, 0, PTR(evt_switch_00), GSWF(GSWF_TIK16_PIPE_MRI_OPEN))
    CALL(evt_mobj_tornadoswitch_blue, 0, STRING("switch01"), 125, 0, 0, PTR(evt_switch_01), GSWF(GSWF_TIK16_PIPE_NOK_OPEN))
    CALL(evt_mobj_powerupblk, STRING("pblk1"), 125, 160, -100, 0, GSWF(GSWF_TIK16_SHINE_SPRITE), 0)
    RETURN
EVT_END()
