// las_13 (ラストダンジョン, Palace of Shadow): a riddle room off las_10: the switch and the small star.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "eff/eff_small_star.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_snd.h"
#include "las.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"

static USER_FUNC(small_star);

static BeroEntry bero_entry_data[2];

/**
 * Door animation script (closing) for the east door, used as the enter/exit animation of this room's bero entry.
 * LW(0) holds the angle step of the swing, and the script turns the door panel S_door1 by it.
 */
static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation script (opening) for the east door, used as the enter/exit animation of this room's bero entry.
 * LW(0) holds the angle step of the swing, and the script turns the door panel S_door1 by it.
 */
static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Exit of las_13: east door e_bero_1 to las_10 (sw_bero_1). */
static BeroEntry bero_entry_data[] = {
    {
        "e_bero_1", // hitName
        1, // type
        1, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "las_10", // nextMapName
        "sw_bero_1", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
    },
    {0},
};

/** Event script: the key chest of las_13 opens and Mario receives Palace Key 0x28. */
static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), ITEM_PALACE_KEY_0x28, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Event script: checks the red switch riddle after each press.
 * When switch 1 has been hit twice and switch 2 three times (switch 2 only counts before switch 1 is touched),
 * it sparkles both switches away, plays a success jingle and makes the key chest (Palace Key 0x28) appear,
 * then sets GSWF_LAS13_RED_SWITCHES_SOLVED.
 */
EVT_BEGIN(switch_check)
    SET_VALUE(LW(0), 0)
    IF_INT_EQUAL(LSW(1), 2)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSW(2), 3)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(evt_mario_key_onoff, 0)
        WAIT_MS(300)
        CALL(evt_mobj_get_position, STRING("switch1"), LW(0), LW(1), LW(2))
        CALL(small_star, LW(0), LW(1), LW(2))
        CALL(evt_mobj_get_position, STRING("switch2"), LW(0), LW(1), LW(2))
        CALL(small_star, LW(0), LW(1), LW(2))
        CALL(evt_mobj_delete, STRING("switch1"))
        CALL(evt_mobj_delete, STRING("switch2"))
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
        CALL(evt_cam3d_evt_set, 0, 100, 363, 0, 30, -30, 500, 11)
        WAIT_MS(1000)
        CALL(evt_mobj_set_position, STRING("box"), 0, -30, 0)
        CALL(evt_mobj_flag_onoff, 0, STRING("box"), MOBJ_FLAG_INVISIBLE | MOBJ_FLAG_FALL)
        CALL(evt_mobj_hit_onoff, STRING("box"), 1)
        SET_VALUE(LW(0), STRING("box"))
        CALL_CHILD(box_syutugen)
        CALL(evt_cam3d_evt_off, 500, 11)
        CALL(evt_mario_key_onoff, 1)
        SET_VALUE(GSWF(GSWF_LAS13_RED_SWITCHES_SOLVED), 1)
    END_IF
    RETURN
EVT_END()

/**
 * Event script: the first switch of las_13 was hit.
 * Counts the hit in LSW(1) (up to 255) and re-checks the puzzle with switch_check.
 */
static EVT_BEGIN(switch1_evt)
    IF_INT_LESS(LSW(1), 255)
        ADD(LSW(1), 1)
    END_IF
    CALL_CHILD(switch_check)
    RETURN
EVT_END()

/**
 * Event script: the second switch of las_13 was hit.
 * Counts the hit in LSW(2) (up to 255) only while LSW(1) is 0, and re-checks the puzzle with switch_check.
 */
static EVT_BEGIN(switch2_evt)
    IF_INT_EQUAL(LSW(1), 0)
        IF_INT_LESS(LSW(2), 255)
            ADD(LSW(2), 1)
        END_IF
    END_IF
    CALL_CHILD(switch_check)
    RETURN
EVT_END()

/** Event script: reading the hint plate of las_13 (stg8_las_38). */
static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_38"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script for las_13, a Riddle Tower room:
 * music, the door back to las_10, the two red floating switches (until solved),
 * the key chest (hidden until solved) and the hint plate.
 */
EVT_BEGIN(las_13_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG8_LAS1"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 2)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    IF_INT_EQUAL(GSWF(GSWF_LAS13_RED_SWITCHES_SOLVED), 0)
        SET_VALUE(LSW(1), 0)
        SET_VALUE(LSW(2), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("switch1"), 150, 60, 0, PTR(switch1_evt), GSWF(GSWF_LAS13_RED_SWITCHES_SOLVED))
        CALL(evt_mobj_floatswitch_red, 0, STRING("switch2"), -150, 60, 0, PTR(switch2_evt), GSWF(GSWF_LAS13_RED_SWITCHES_SOLVED))
    END_IF
    CALL(evt_mobj_itembox, STRING("box"), 0, 0, 0, 0, 0, PTR(box_evt), GSWF(GSWF_LAS13_KEY_CHEST_OPENED))
    IF_INT_EQUAL(GSWF(GSWF_LAS13_RED_SWITCHES_SOLVED), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("box"), MOBJ_FLAG_INVISIBLE)
        CALL(evt_mobj_hit_onoff, STRING("box"), 0)
    END_IF
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_pure"), 0, PTR(hint_plate), 0)
    RETURN
EVT_END()

/** Script helper: spawns a small star sparkle effect above the point (args[0], args[1], args[2]). */
static USER_FUNC(small_star) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effSmallStarEntry(0, 4, x, 12.5f + y, z, 0.0f, -1.0f, 0.0f);
    return EVT_RETURN_DONE;
}
