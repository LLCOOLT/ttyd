// las_11 (ラストダンジョン, Palace of Shadow): a riddle room off las_10.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
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
        "nw_bero_1", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
    },
    {0},
};

/** Event script: the key chest of las_11 opens and Mario receives Palace Key 0x26. */
static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), ITEM_PALACE_KEY_0x26, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Event script: the floating switch of las_11 was hit.
 * The camera shows the spot, the key chest drops into the room (box_syutugen),
 * a success jingle plays and the camera returns.
 */
static EVT_BEGIN(switch_evt)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1250)
    CALL(evt_cam3d_evt_set, 0, 100, 363, 0, 30, -30, 500, 11)
    WAIT_MS(1000)
    CALL(evt_mobj_set_position, STRING("box"), 0, -30, 0)
    CALL(evt_mobj_flag_onoff, 0, STRING("box"), MOBJ_FLAG_INVISIBLE | MOBJ_FLAG_FALL)
    CALL(evt_mobj_hit_onoff, STRING("box"), 1)
    SET_VALUE(LW(0), STRING("box"))
    CALL_CHILD(box_syutugen)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
    WAIT_MS(2000)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Event script: the sound of a big block falling in las_11.
 * Waits 1.4 seconds, then plays the block's thud 1400 units above its start position.
 */
static EVT_BEGIN(block_break)
    CALL(evt_mobj_get_position, STRING("me"), LW(0), LW(1), LW(2))
    WAIT_MS(900)
    WAIT_MS(500)
    ADD(LW(1), 1400)
    CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLOCK_OJAMA1"), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

/** Event script: reading the hint plate of las_11 (stg8_las_36). */
static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_36"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script for las_11, a Riddle Tower room (the chest holds Palace Key 0x26):
 * music, the door back to las_10, four big blocks (two stone ones that can be smashed, two metal ones),
 * a floating blue switch that reveals the key chest, and the hint plate.
 */
EVT_BEGIN(las_11_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG8_LAS1"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 2)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_mobj_lv_blk, STRING("stone1"), 150, 50, 0, PTR(block_break), GSWF(GSWF_LAS_TOWER_BIG_BLOCK_A), STRING("MOBJ_Lv2BigBlock"))
    CALL(evt_mobj_lv_blk, STRING("stone2"), -150, 0, 75, PTR(block_break), GSWF(GSWF_LAS_TOWER_BIG_BLOCK_B), STRING("MOBJ_Lv2BigBlock"))
    CALL(evt_mobj_lv_blk, STRING("metal1"), 150, 0, 75, 0, GSWF(GSWF_LAS_TOWER_BIG_BLOCK_C), STRING("MOBJ_Lv3BigBlock"))
    CALL(evt_mobj_lv_blk, STRING("metal2"), -150, 50, 0, 0, GSWF(GSWF_LAS_TOWER_BIG_BLOCK_D), STRING("MOBJ_Lv3BigBlock"))
    CALL(evt_mobj_floatswitch_blue, 0, STRING("switch"), -150, 110, -10, PTR(switch_evt), GSWF(GSWF_LAS11_FLOAT_SWITCH_PRESSED))
    CALL(evt_mobj_itembox, STRING("box"), 0, 0, 0, 0, 0, PTR(box_evt), GSWF(GSWF_LAS11_KEY_CHEST_OPENED))
    IF_INT_EQUAL(GSWF(GSWF_LAS11_FLOAT_SWITCH_PRESSED), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("box"), MOBJ_FLAG_INVISIBLE)
        CALL(evt_mobj_hit_onoff, STRING("box"), 0)
    END_IF
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_pure"), 0, PTR(hint_plate), 0)
    RETURN
EVT_END()
