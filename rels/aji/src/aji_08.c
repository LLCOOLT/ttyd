// aji_08 (敵のアジト, X-Naut Fortress): the corridor with the moving ceiling (evt_slit, tenjo) and an X-Naut
// PhD (gundan_zako_magician).
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "aji.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

static USER_FUNC(camAtY);
static USER_FUNC(slit_chk);

extern EvtWord evt_slit0[];
extern EvtWord evt_slit1[];
extern EvtWord evt_slit2[];
static BeroEntry bero_entry_data[5];
extern EvtWord heya_tenura_onoff[];

/**
 * Door open animation step: moves the two door leaves S_door1_2
 * and S_door1_1 in opposite directions along X by the animation value in LW(0) times 0.16601563;
 * the open and close scripts apply the same transform.
 */
static EVT_BEGIN(s_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.16601563f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_2"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_1"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Door close animation step: moves the two door leaves S_door1_2
 * and S_door1_1 in opposite directions along X by the animation value in LW(0) times 0.16601563;
 * the open and close scripts apply the same transform.
 */
static EVT_BEGIN(s_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.16601563f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_2"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_1"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Exit event of the ceiling slit s_bero_2: locks the controls
 * and changes the map to aji_06 (the potion laboratory), entering as "tenjo" (from the ceiling).
 */
EVT_BEGIN(evt_slit0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_bero_mapchange, STRING("aji_06"), STRING("tenjo"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

/**
 * Exit event of the ceiling slit with exitEvent evt_slit1:
 * the map changes to aji_07 (the teleporter room), entering as "tenjo".
 */
EVT_BEGIN(evt_slit1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_bero_mapchange, STRING("aji_07"), STRING("tenjo"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

/** Exit event of the ceiling slit with exitEvent evt_slit2: the map changes to aji_09, entering as "tenjo". */
EVT_BEGIN(evt_slit2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_bero_mapchange, STRING("aji_09"), STRING("tenjo"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "s_bero_1", // hitName
        1, // type
        10, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "aji_01", // nextMapName
        "n_bero_3", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_door_close, // enterAnimeArg
        s_door_open, // exitAnimeArg
    },
    {
        "s_bero_2", // hitName
        3840, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, 0, // enterEvent..caseType
        (s32*)evt_slit0, // exitEvent
        "aji_06", // nextMapName
        "tenjo", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "s_bero_3", // hitName
        3840, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, 0, // enterEvent..caseType
        (s32*)evt_slit1, // exitEvent
        "aji_07", // nextMapName
        "tenjo", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "s_bero_4", // hitName
        3840, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, 0, // enterEvent..caseType
        (s32*)evt_slit2, // exitEvent
        "aji_09", // nextMapName
        "tenjo", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Swaps the room model with the roof model by the camera height:
 * while the camera looks from y = 180 or higher the roof S_tenura is shown and the room S_heya hidden,
 * otherwise the other way round. Runs forever.
 */
EVT_BEGIN(heya_tenura_onoff)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_heya"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_tenura"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(LW(0), 0)
    LOOP(0)
        CALL(camAtY, LW(1))
        IF_INT_GREATER_OR_EQUAL(LW(1), 180)
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_heya"), MAPOBJ_FLAG_HIDE)
                CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_tenura"), MAPOBJ_FLAG_HIDE)
                SET_VALUE(LW(0), 1)
            END_IF
        ELSE
            IF_INT_EQUAL(LW(0), 1)
                CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_heya"), MAPOBJ_FLAG_HIDE)
                CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_tenura"), MAPOBJ_FLAG_HIDE)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Init script of aji_08, the corridor above the fortress rooms:
 * plays BGM_STG7_DUN2, sets up the exits and the roof- swap check, places a Star Piece (GSWF_AJI08_STAR_PIECE),
 * and runs the ceiling plate S_ita rocking back and forth forever with SFX_STG7_AMB_CEILING_MOVE1;
 * the X-Naut magician grunt is removed once Lord Crump is beaten.
 */
EVT_BEGIN(aji_08_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_AJI2"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 1)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    SPAWN_EVENT_GET_ID(PTR(heya_tenura_onoff), LW(0))
    SPAWN_EVENT(evt_emergency)
    BEGIN_INLINE_EVENT
        CALL(slit_chk)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("bari"), 1, 0)
    CALL(evt_map_playanim, STRING("awa1"), 1, 0)
    CALL(evt_map_playanim, STRING("awa2"), 1, 0)
    CALL(evt_item_entry, STRING("item00"), ITEM_STAR_PIECE, -975, 170, 75, ITEM_ENTRY_FIXED, GSWF(GSWF_AJI08_STAR_PIECE), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mapobj_get_position, STRING("S_ita"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_AMB_CEILING_MOVE1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_sub_intpl_msec_init, 11, -100, 100, 1000)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_ita"), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
            CALL(evt_mapobj_get_position, STRING("S_ita"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_AMB_CEILING_MOVE1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_sub_intpl_msec_init, 11, 100, -100, 1000)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_ita"), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_npc_check_delete, STRING("軍団ザコ魔法使い"))
    END_IF
    RETURN
EVT_END()

/** Script function: returns the 3D camera's look-at height (cameraAt.y) in args[0]. */
static USER_FUNC(camAtY) {
    EvtWord* args = event->args;

    evtSetValue(event, args[0], camGetPtr(CAMERA_3D)->cameraAt.y);
    return EVT_RETURN_DONE;
}
/**
 * Script function: waits until paper-mode Mario is at a slit position (x below -200 or above 300, height 160 to
 * 169), then switches off the 3D camera control and stops the event whose ID is in LW(0),
 * the roof-swap script heya_tenura_onoff. Blocks until then.
 */
static USER_FUNC(slit_chk) {
    MarioWork* mario = marioGetPtr();

    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        if ((mario->position.x < -200.0f || mario->position.x > 300.0f) && mario->position.y < 169.0f &&
            mario->position.y > 160.0f) {
            camCtrlOff(CAMERA_3D);
            evtStopID(event->lwData[0]);
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_BLOCK;
}
