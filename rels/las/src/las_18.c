// las_18 (ラストダンジョン, Palace of Shadow): a riddle room off las_10: the switch only Vivian reaches.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"

#include "driver/mobjdrv.h"
#include "driver/animdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "las.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"

static USER_FUNC(get_mobj_seq);

static BeroEntry bero_entry_data[2];

/**
 * Door animation script (closing) for the west door, used as the enter/exit animation of this room's bero entry.
 * LW(0) holds the angle step of the swing, and the script turns the door panel S_door1 by it.
 */
static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation script (opening) for the west door, used as the enter/exit animation of this room's bero entry.
 * LW(0) holds the angle step of the swing, and the script turns the door panel S_door1 by it.
 */
static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Exit of las_18: west door w_bero_1 to las_10 (se_bero_2). */
static BeroEntry bero_entry_data[] = {
    {
        "w_bero_1", // hitName
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
        "se_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_door_close, // enterAnimeArg
        w_door_open, // exitAnimeArg
    },
    {0},
};

/** Event script: the key chest of las_18 opens and Mario receives Palace Key 0x2D. */
static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), ITEM_PALACE_KEY_0x2D, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Script helper: sets the alpha (0..255) of the map object "switch" to args[0], tinting it white;
 * below alpha 0x25 the switch also stops casting a shadow.
 * Used to fade the hidden switch in while Vivian is hiding in shadow next to it.
 * Does nothing once the switch is gone.
 */
static USER_FUNC(switch_set_alpha) {
    s32 alpha = evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("switch");

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    if (alpha > 0x24) {
        mobj->flags &= ~MOBJ_FLAG_NO_SHADOW;
    } else {
        mobj->flags |= MOBJ_FLAG_NO_SHADOW;
    }
    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){255, 255, 255, alpha});
    animPoseSetMaterialFlagOn(mobj->poseId, ANIM_MATERIAL_FLAG_EVT_COLOR);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: restores the map object "switch" to fully opaque with its shadow
 * and turns the evt colour override off.
 */
static USER_FUNC(switch_alpha_off) {
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("switch");

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    mobj->flags &= ~MOBJ_FLAG_NO_SHADOW;
    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){255, 255, 255, 255});
    animPoseSetMaterialFlagOff(mobj->poseId, ANIM_MATERIAL_FLAG_EVT_COLOR);
    return EVT_RETURN_DONE;
}

/**
 * Event script: the hidden switch of las_18 only becomes visible if Vivian is the partner
 * and in her shadow form (status 2): the switch's alpha rises by 4 per frame up to 160 while she hides
 * and falls back when she leaves.
 * When it reaches 160 for the first time it plays a success jingle and sets GSWF_LAS18_HIDDEN_SWITCH_REVEALED.
 * Ends when the switch has been pressed.
 */
EVT_BEGIN(vivian_check)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(15), 0)
    LOOP(0)
        CALL(get_mobj_seq, STRING("switch"), LW(0))
        IF_INT_GREATER(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_mario_get_party, LW(0))
        IF_INT_EQUAL(LW(0), 6)
            CALL(evt_party_get_status, 6, LW(0))
            IF_INT_EQUAL(LW(0), 2)
                ADD(LW(15), 4)
            ELSE
                SUBTRACT(LW(15), 4)
            END_IF
        ELSE
            SUBTRACT(LW(15), 4)
        END_IF
        IF_INT_GREATER(LW(15), 160)
            SET_VALUE(LW(15), 160)
        END_IF
        IF_INT_LESS(LW(15), 0)
            SET_VALUE(LW(15), 0)
        END_IF
        CALL(switch_set_alpha, LW(15))
        IF_INT_EQUAL(LW(15), 160)
            IF_INT_EQUAL(GSWF(GSWF_LAS18_HIDDEN_SWITCH_REVEALED), 0)
                SET_VALUE(GSWF(GSWF_LAS18_HIDDEN_SWITCH_REVEALED), 1)
                CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
                CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
                WAIT_MS(2000)
                CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
                CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/** Script helper: returns the state of the map object named args[0] in args[1], or 1 if the object no longer exists. */
static USER_FUNC(get_mobj_seq) {
    EvtWord* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtrNoAssert((const char*)evtGetValue(event, args[0]));

    if (mobj == NULL) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], mobj->state);
    }
    return EVT_RETURN_DONE;
}

/**
 * Event script: the switch of las_18 was hit.
 * The switch-alpha effect is turned off, the camera shows the spot and the key chest drops in (box_syutugen).
 */
static EVT_BEGIN(switch_evt)
    CALL(switch_alpha_off)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1250)
    CALL(evt_cam3d_evt_set, 0, 100, 363, 0, 30, -30, 500, 11)
    WAIT_MS(1000)
    CALL(evt_mobj_set_position, STRING("box"), 0, -30, 0)
    CALL(evt_mobj_flag_onoff, 0, STRING("box"), MOBJ_FLAG_INVISIBLE | MOBJ_FLAG_FALL)
    CALL(evt_mobj_hit_onoff, STRING("box"), 1)
    SET_VALUE(LW(0), STRING("box"))
    CALL_CHILD(box_syutugen)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Event script: reading the hint plate of las_18 (stg8_las_43). */
static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_43"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script for las_18, a Riddle Tower room (the chest holds Palace Key 0x2D):
 * music, the door to las_10, the nearly invisible blue floating switch that only Vivian can reveal,
 * the key chest and the hint plate.
 */
EVT_BEGIN(las_18_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG8_LAS1"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 2)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_mobj_floatswitch_blue, 0, STRING("switch"), 75, 60, 0, PTR(switch_evt), GSWF(GSWF_LAS18_SWITCH_PRESSED))
    CALL(evt_mobj_flag_onoff, 1, STRING("switch"), MOBJ_FLAG_NO_SHADOW)
    IF_INT_EQUAL(GSWF(GSWF_LAS18_SWITCH_PRESSED), 0)
        SPAWN_EVENT(vivian_check)
    END_IF
    CALL(evt_mobj_itembox, STRING("box"), 0, 0, 0, 0, 0, PTR(box_evt), GSWF(GSWF_LAS18_KEY_CHEST_OPENED))
    IF_INT_EQUAL(GSWF(GSWF_LAS18_SWITCH_PRESSED), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("box"), MOBJ_FLAG_INVISIBLE)
        CALL(evt_mobj_hit_onoff, STRING("box"), 0)
    END_IF
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_pure"), 0, PTR(hint_plate), 0)
    RETURN
EVT_END()
