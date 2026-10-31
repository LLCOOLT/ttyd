// las_24 (ラストダンジョン, Palace of Shadow): the room with the cloud blocks and the breaking floor.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cloud.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "las.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

#if VERSION >= VERSION_US
// Declaration of the script helper that stretches a duration for the game's frame rate (defined at the end of this
// file; US and later).
USER_FUNC(las_24_adjust_for_framerate);
#endif

static BeroEntry bero_entry_data[4];
static const char* haguruma_hontai[15];
static const char* haguruma_hontai2[6];
static const char* haguruma_kage[12];
static const char* haguruma_kage2[5];

/**
 * Door animation script (closing) for the west door, used as the enter/exit animation of this room's bero entry.
 * LW(0) holds the angle step of the swing, and the script turns the door panels S_doa_01 and S_doa_02 by it,
 * the second one the opposite way.
 */
static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation script (opening) for the west door, used as the enter/exit animation of this room's bero entry.
 * LW(0) holds the angle step of the swing, and the script turns the door panels S_doa_01 and S_doa_02 by it,
 * the second one the opposite way.
 */
static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        6, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "las_22", // nextMapName
        "e_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_door_close, // enterAnimeArg
        w_door_open, // exitAnimeArg
    },
    {
        "s_bero_1", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "las_23", // nextMapName
        "n_bero_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "s_bero_2", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "las_25", // nextMapName
        "n_bero_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static const char* haguruma_hontai[] = {
    "S_hgm_01a",
    "S_hgm_02a",
    "S_hgm_03a",
    "S_hgm_04a",
    "S_hgm_06a",
    "S_hgm_07a",
    "S_hgm_08a",
    "S_hgm_10a",
    "S_hgm_11a",
    "S_hgm_14a",
    "S_hgm_15a",
    "S_hgm_16a",
    "S_hgm_19a",
    "S_hgm_20a",
    "S_hgm_24a",
};

static const char* haguruma_hontai2[] = {
    "S_hgm_05a",
    "S_hgm_09a",
    "S_hgm_12a",
    "S_hgm_13a",
    "S_hgm_17a",
    "S_hgm_18a",
};

static const char* haguruma_kage[] = {
    "S_hgm_01b",
    "S_hgm_02b",
    "S_hgm_03b",
    "S_hgm_04b",
    "S_hgm_06b",
    "S_hgm_07b",
    "S_hgm_08b",
    "S_hgm_10b",
    "S_hgm_11b",
    "S_hgm_14b",
    "S_hgm_15b",
    "S_hgm_16b",
};

static const char* haguruma_kage2[] = {
    "S_hgm_05b",
    "S_hgm_09b",
    "S_hgm_12b",
    "S_hgm_13b",
    "S_hgm_17b",
};

/**
 * Event script: runs while the room is loaded and spins the gears of the turntable room (see las_22):
 * the same two counter-rotating gear sets plus the sine-driven gear pairs S_hgm_21..23,
 * with different gear counts.
 */
static EVT_BEGIN(haguruma_evt)
    SET_FLOAT_VALUE(LW(0), FLOAT(20.0f))
    SET_FLOAT_VALUE(LW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(4), FLOAT(0.0f))
    LOOP(0)
        SET_INT_READ_ADDR(PTR(&haguruma_hontai))
        LOOP(15)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(0))
        END_LOOP
        SET_INT_READ_ADDR(PTR(&haguruma_kage))
        LOOP(12)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(0))
        END_LOOP
        SET_INT_READ_ADDR(PTR(&haguruma_hontai2))
        LOOP(6)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(1))
        END_LOOP
        SET_INT_READ_ADDR(PTR(&haguruma_kage2))
        LOOP(5)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(1))
        END_LOOP
        CALL(evt_sub_get_sincos, LW(2), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(41.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_21a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_21b"), 0, 0, LW(5))
        CALL(evt_sub_get_sincos, LW(3), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(22.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_22a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_22b"), 0, 0, LW(5))
        CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(110.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_23a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_23b"), 0, 0, LW(5))
        ADD_FLOAT(LW(0), FLOAT(1.0f))
        IF_INT_GREATER_OR_EQUAL(LW(0), 360)
            SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(1), FLOAT(-1.0f))
        IF_INT_LESS_OR_EQUAL(LW(1), -360)
            ADD_FLOAT(LW(1), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(2), FLOAT(0.89941406f))
        IF_INT_GREATER_OR_EQUAL(LW(2), 360)
            SUBTRACT_FLOAT(LW(2), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(3), FLOAT(0.89941406f))
        IF_INT_GREATER_OR_EQUAL(LW(3), 360)
            SUBTRACT_FLOAT(LW(3), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(4), FLOAT(1.0f))
        IF_INT_GREATER_OR_EQUAL(LW(4), 360)
            SUBTRACT_FLOAT(LW(4), FLOAT(360.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Event script: runs when the cloud over the big stone block has been blown away by Flurrie.
 * Sets GSWF_LAS24_BLOCK_UNCOVERED and makes the block solid.
 */
EVT_BEGIN(cloud_blk_evt)
    SET_VALUE(GSWF(GSWF_LAS24_BLOCK_UNCOVERED), 1)
    CALL(evt_mobj_flag_onoff, 0, STRING("blk"), MOBJ_FLAG_NO_HIT)
    RETURN
EVT_END()

/** Event script: runs when the breaking floor gives way; sets the story to STORY_STG8_12_LARGE_STONE_BLOCK. */
EVT_BEGIN(break_floor_evt)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG8_12_LARGE_STONE_BLOCK)
    RETURN
EVT_END()

/**
 * Event script: the red jump stand.
 * Mario jumps from the stand at (-500, -200) to the ledge at (-450, -200);
 * if a partner is present it first jumps to the ledge when it stands on the stand ("MOBJ_jump").
 */
EVT_BEGIN(jump_evt)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            LOOP(90)
                CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
                IF_INT_GREATER_OR_EQUAL(LW(1), -201)
                    IF_INT_LESS_OR_EQUAL(LW(1), -199)
                        RETURN
                    END_IF
                END_IF
                CALL(evt_party_get_name_hitobj_ride, 0, LW(0))
                IF_STR_EQUAL(LW(0), STRING("MOBJ_jump"))
                    CALL(evt_party_jump_pos, 0, -455, -200, 50, 600, 0, -1000)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
    END_INLINE_EVENT
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_jump_jumpstand, -500, -200, 0, -545, 100, 0, -450, -200, 0, 1000, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Event script: starts the moving platform S_move_dai (hit object A_move_dai) via move_dai.
 * The movement time is 7200, scaled for the frame rate in the US and later versions.
 */
static EVT_BEGIN(dai_evt)
    SET_VALUE(LW(0), STRING("S_move_dai"))
    SET_VALUE(LW(1), STRING("A_move_dai"))
    SET_VALUE(LW(2), 7200)
#if VERSION >= VERSION_US
    CALL(las_24_adjust_for_framerate, LW(2), LW(2))
#endif
    CALL_CHILD(move_dai)
    RETURN
EVT_END()

/**
 * Event script: the key chest of las_24 opens and Mario receives Palace Key 0x30;
 * the story progress is set to STORY_STG8_13_KEY.
 */
static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), ITEM_PALACE_KEY_0x30, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG8_13_KEY)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script for las_24, the cloud and breaking floor room:
 * music, the door set, the gear animation, the cloud over the big stone block (until
 * STORY_STG8_12_LARGE_STONE_BLOCK), the big stone block, the breaking floor, a red jump stand,
 * a moving platform with its red floating switch, a coin block,
 * a hidden brick with Point Swap and the key chest with Palace Key 0x30.
 */
EVT_BEGIN(las_24_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG8_LST3"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG8_LAS7"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 2)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_05a"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_19a"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_24a"), MAPOBJ_FLAG_BBOX_CULL)
    SPAWN_EVENT(haguruma_evt)
    CALL(evt_map_playanim, STRING("kusari"), 1, 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG8_12_LARGE_STONE_BLOCK)
        IF_INT_EQUAL(GSWF(GSWF_LAS24_BLOCK_UNCOVERED), 0)
            CALL(evt_cloud_init)
            CALL(evt_cloud_ent, 0, STRING("S_hako"), STRING("A_hako"), PTR(cloud_blk_evt))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hako"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("A_hako"), 1, 0)
        END_IF
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hako"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_hako"), 1, 0)
    END_IF
    CALL(evt_mobj_lv_blk, STRING("blk"), -495, 100, 0, 0, GSWF(GSWF_LAS24_BIG_BLOCK_BROKEN), STRING("MOBJ_Lv2BigBigBlock"))
    IF_INT_EQUAL(GSWF(GSWF_LAS24_BIG_BLOCK_BROKEN), 0)
        CALL(evt_mobj_flag_onoff, 0, STRING("blk"), MOBJ_FLAG_FALL)
        IF_INT_EQUAL(GSWF(GSWF_LAS24_BLOCK_UNCOVERED), 0)
            CALL(evt_mobj_flag_onoff, 1, STRING("blk"), MOBJ_FLAG_NO_HIT)
            CALL(evt_mobj_set_scale, STRING("blk"), FLOAT(0.9980469f), FLOAT(0.9980469f), FLOAT(0.9980469f))
        END_IF
    END_IF
    CALL(evt_mobj_breaking_floor, STRING("brkflr"), -500, 100, 0, 0, PTR(break_floor_evt), GSWF(GSWF_LAS24_FLOOR_BROKEN))
    CALL(evt_mobj_jumpstand_red, 0, STRING("jump"), -500, -200, 0, PTR(jump_evt), 0)
    CALL(evt_hit_bind_mapobj, STRING("A_move_dai"), STRING("S_move_dai"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_move_dai"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_move_dai"), 0, 0)
    CALL(evt_mobj_floatswitch_red, 0, STRING("dai_switch"), -150, -440, 75, PTR(dai_evt), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_hatena_gat"), -625, -200, -100, ITEM_COIN, 0, GSWF(GSWF_LAS24_COIN_BLOCK_HIT), 0)
    CALL(evt_mobj_brick, STRING("mobj_kakusi"), -625, -115, -100, ITEM_POINT_SWAP, 11, 0, GSWF(GSWF_LAS24_POINT_SWAP_HIDDEN_BLOCK_HIT))
    CALL(evt_mobj_itembox, STRING("box"), -255, -380, 75, 0, 0, PTR(box_evt), GSWF(GSWF_LAS24_KEY_CHEST_OPENED))
    RETURN
EVT_END()

#if VERSION >= VERSION_US
#include "mario/mariost.h"
#include "manager/evtmgr_cmd.h"

/**
 * Script helper: reads a duration in args[0] and returns it in args[1],
 * multiplied by 1.2 when the frame rate is not 60 so the platform ride lasts as long on PAL timing.
 */
USER_FUNC(las_24_adjust_for_framerate) {
    EvtWord* args = event->args;
    s32 value = evtGetValue(event, args[0]);

    if (gp->framerate != 60) {
        value *= 1.2f;
    }
    evtSetValue(event, args[1], value);
    return EVT_RETURN_DONE;
}
#endif
