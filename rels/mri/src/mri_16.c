// mri_16 (巨木の中, The Great Tree): the water room: the mechanism that drains the water (water_shikake) and
// the rising bars (bar_shikake), with an item box.
#include "mri_puni.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_damage.h"
#include "mri.h"
#include "driver/hitdrv.h"
#include "driver/itemdrv.h"
#include "evt/evt_cam.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/camdrv.h"

static s32 ssf;

static USER_FUNC(ss_check);
static USER_FUNC(ss_set);

static BeroEntry bero_entry_data[7];
extern EvtWord water_shikake[];
extern EvtWord bar_shikake[];
extern EvtWord bar_shikake_up[];
extern EvtWord switch_up_down[];
static HitDamageReturn hitDmgRetPoints[5];

/**
 * Reads the bar-switch state ssf for the script:
 * returns it as a float in args[0] (0 idle, 1 Mario is riding the bar switch, 2 he left it).
 * The odd extra statements only keep the compiled order of the original.
 */
static USER_FUNC(ss_check) {
    s32 dest;
    s32 notSet;

    // FAKE: the dead condition moves the ssf load ahead of event->args; casts, temps and u32 index variants do not
    // reproduce it
    dest = event->args[0];
    notSet = !ssf;
    if ((notSet && !ssf) != 0) {
    }
    evtSetFloat(event, dest, ssf);
    return EVT_RETURN_DONE;
}

/** Stores the bar-switch state ssf from args[0] (0 idle, 1 ridden, 2 released). */
static USER_FUNC(ss_set) {
    ssf = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

/** Returns in args[1] the index stored in the Puni data of the slot args[0]. */
static USER_FUNC(puni_get_id) {
    s32 offset;
    EvtWord* args = event->args;
    PuniData* puni;

    offset = evtGetValue(event, args[0]) * sizeof(PuniData);
    puni = (PuniData*)((u8*)puniGetPunidat() + offset);
    evtSetValue(event, args[1], puni->index);
    return EVT_RETURN_DONE;
}

static BeroEntry bero_entry_data[] = {
    {
        "dokan1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan4", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        10, // caseType
        NULL, // exitEvent
        "mri_18", // nextMapName
        "dokan2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan3", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan6", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan4", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_W, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        10, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan6", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_E, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        10, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan3", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan7", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, // exitEvent
        "mri_13", // nextMapName
        "dokan", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Starts a camera shake that builds up over half a second (strength 0 to 0.007),
 * used as the water starts to drain; it then leaves a small steady shake on.
 */
static EVT_BEGIN(cam_shake)
    CALL(evt_sub_intpl_msec_init, 11, 0, 7, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(evt_cam_shake, CAMERA_3D, LW(0), FLOAT(0.0f), 100)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.0068359375f), FLOAT(0.0f), 0)
    RETURN
EVT_END()

/** Fades the camera shake out over half a second (strength 0.007 to 0). */
static EVT_BEGIN(cam_shake2)
    CALL(evt_sub_intpl_msec_init, 11, 7, 0, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(evt_cam_shake, CAMERA_3D, LW(0), FLOAT(0.0f), 100)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    RETURN
EVT_END()

/**
 * Blue switch pressed: drains the water in the room.
 * Punies already on the lower level are re-placed at fixed spots there,
 * the water level drops with a quake and a flowing-water sound while the camera follows it down,
 * the stairs and ledges of the drained room become solid, and a jingle plays.
 */
EVT_BEGIN(water_shikake)
    CALL(evt_mario_key_onoff, 0)
#if VERSION >= VERSION_JP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_wait_landon)
        CALL(evt_mario_set_mov_spd, FLOAT(0.0f))
    END_INLINE_EVENT
#endif
#if VERSION <= VERSION_DEMO_US
    CALL(evt_mario_normalize)
#endif
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(40))
    SET_VALUE(LW(10), 1)
    LOOP(0)
        SET_VALUE(LF(0), 1)
        CALL(evt_puni_get_flag, LW(10), LW(0))
        AND_RAW(LW(0), 1024)
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 0)
        END_IF
        CALL(evt_puni_get_position, LW(10), LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(1), -200)
            SET_VALUE(LF(0), 0)
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_puni_set_mode, LW(10), PUNI_MODE_HAGURE)
            CALL(evt_puni_flag_onoff, LW(10), 0, 1048576)
            CALL(puni_get_id, LW(10), LW(3))
            AND(LW(3), 8)
            SUBTRACT(LW(3), 4)
            ADD(LW(3), -230)
            CALL(evt_puni_set_position, LW(10), LW(3), -320, LW(2))
        END_IF
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_l03"), 1, 1)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_before"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_now"), MAPOBJ_FLAG_HIDE)
    CALL(evt_snd_sfxon, STRING("SFX_STG2_QUAKE1"), GW(0))
    CALL(evt_snd_sfxon, STRING("SFX_STG2_WATER_FLOW1"), GW(1))
    SPAWN_EVENT_GET_ID(PTR(cam_shake), LW(10))
    CALL(evt_map_playanim, STRING("mizu_guru"), 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, -154, 186, 520, -14, 100, -48, 1500, 11)
        WAIT_MS(3500)
        CALL(evt_cam3d_evt_set, -154, -184, 520, -14, -271, -48, 5000, 11)
        WAIT_MS(2500)
        CALL(evt_snd_sfxoff, GW(0))
        WAIT_MS(2500)
        WAIT_MS(8000)
        CALL(evt_snd_sfxoff, GW(1))
        CALL(evt_cam3d_evt_off, 0, 11)
    END_INLINE_EVENT
    CALL(evt_map_checkanim, STRING("mizu_guru"), LW(0), LW(1))
    WAIT_MS(LW(1))
    DELETE_EVENT(LW(10))
    CALL_CHILD(cam_shake2)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_now"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_mizu_after"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_mizu_after"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f2_kaidan"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_mizu_after"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f2_kai_rak"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak_ana"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa01"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_isk_03"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa01"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa02"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa03"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa04"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa05"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_mkusa_06"), 1, 1)
    CALL(evt_hitobj_onoff, STRING("A_f1_kaidan"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_mizu_before"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak_l03"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_l04"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_f1_rak_r03"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_mizi_kusa"), 1, 1)
    CALL(evt_puni_set_ymode, 5)
    CALL(evt_puni_set_maze)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Hit script of the light-blue bar switch when Mario rides it: sets the bar-switch state to 1 so the bar sinks. */
EVT_BEGIN(bar_shikake)
    DEBUG_PUT_MSG(STRING("のったとき"))
    CALL(ss_set, 1)
    RETURN
EVT_END()

/** Hit script of the bar switch when Mario gets off it: sets the bar-switch state to 2 so the bar rises again. */
EVT_BEGIN(bar_shikake_up)
    DEBUG_PUT_MSG(STRING("のらなかったとき"))
    CALL(ss_set, 2)
    RETURN
EVT_END()

/**
 * Per-frame control of the bar (S_sikake): sinks it up to 10 units while Mario rides the bar switch (state 1)
 * and lets it rise back (state 2), moving the blue switch box (mobj00) with it
 * until the water switch is pressed.
 */
EVT_BEGIN(switch_up_down)
    SET_FLOAT_VALUE(LW(2), FLOAT(0.0f))
    IF_INT_EQUAL(GSWF(GSWF_MRI16_WATER_SWITCH_PRESSED), 0)
        CALL(evt_mobj_get_y_position, STRING("mobj00"), LW(3))
    ELSE
        SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    END_IF
    SET_FLOAT_VALUE(LW(4), LW(3))
    LOOP(0)
        CALL(ss_check, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            SET_FLOAT_VALUE(LW(1), FLOAT(-0.3330078f))
            ADD_FLOAT(LW(2), LW(1))
            MULTIPLY_FLOAT(LW(1), FLOAT(5.0f))
            ADD_FLOAT(LW(4), LW(1))
            IF_FLOAT_LESS_OR_EQUAL(LW(2), FLOAT(-10.0f))
                SET_FLOAT_VALUE(LW(2), FLOAT(-10.0f))
                SET_FLOAT_VALUE(LW(4), FLOAT(-50.0f))
                ADD_FLOAT(LW(4), LW(3))
                CALL(ss_set, 0)
            END_IF
            CASE_EQUAL(2)
            SET_FLOAT_VALUE(LW(1), FLOAT(0.08300781f))
            ADD_FLOAT(LW(2), LW(1))
            MULTIPLY_FLOAT(LW(1), FLOAT(5.0f))
            ADD_FLOAT(LW(4), LW(1))
            IF_FLOAT_GREATER_OR_EQUAL(LW(2), FLOAT(0.0f))
                SET_FLOAT_VALUE(LW(2), FLOAT(0.0f))
                SET_FLOAT_VALUE(LW(4), LW(3))
                CALL(ss_set, 0)
            END_IF
        END_SWITCH
        CALL(evt_mapobj_trans, 1, STRING("S_sikake"), 0, LW(2), 0)
        CALL(evt_hit_bind_update, STRING("A_sikake"))
        IF_INT_EQUAL(GSWF(GSWF_MRI16_WATER_SWITCH_PRESSED), 0)
            CALL(evt_mobj_set_y_position, STRING("mobj00"), LW(4))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static HitDamageReturn hitDmgRetPoints[] = {
    {"S_f2_yuka01_l", {-248.0f, 80.0f, 27.0f}},
    {"S_f2_yuka01_r", {248.0f, 80.0f, 27.0f}},
    {"A_f1_yuka04", {-244.0f, -319.0f, 34.0f}},
    {"A_f1_yuka03", {0.0f, -1000.0f, 0.0f}},
    {0},
};

/**
 * Script when the treasure chest is opened: the Shrink Stomp badge appears above the chest
 * and Mario collects it with the normal item fanfare.
 * From US on the badge can return to the chest if Mario leaves it.
 */
static EVT_BEGIN(mobj_box00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), ITEM_SHRINK_STOMP, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_item_flag_on, STRING("item00"), ITEM_FLAG_NO_TOUCH)
#else
    CALL(evt_item_flag_on, STRING("item00"), ITEM_FLAG_BADGE_RETURN | ITEM_FLAG_NO_TOUCH)
#endif
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Map init script of mri_16, the water room: sets up the Puni, the blue water switch, the bar switch and bar,
 * the water level or drained water depending on GSWF_MRI16_WATER_SWITCH_PRESSED, the Dizzy Dial,
 * the Shrink Stomp chest (the badge) and a Shine Sprite block.
 */
EVT_BEGIN(mri_16_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 16, 80, -319, -1000, -1000, 4, 3)
    CALL(evt_puni_set_hamari, -231, -319, -71, 82, -2, -317, -401)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(mri_puni_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    SPAWN_EVENT(puni_disp_info)
    SPAWN_EVENT(mri_countdown)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_23_TIME_BOMB_ACTIVATED, STORY_STG2_23_01_X_NAUT_BATTLE)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG2_MRI10"))
    END_SWITCH
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    CALL(evt_mobj_switch_blue, 0, STRING("mobj00"), 0, 79, -120, PTR(water_shikake), GSWF(GSWF_MRI16_WATER_SWITCH_PRESSED))
    IF_INT_EQUAL(GSWF(GSWF_MRI16_WATER_SWITCH_PRESSED), 0)
        CALL(evt_mobj_flag_onoff, 0, STRING("mobj00"), MOBJ_FLAG_FALL)
    END_IF
    CALL(evt_hit_bind_mapobj, STRING("A_sikake"), STRING("S_sikake"))
    CALL(ss_set, 0)
    CALL(evt_mobj_rideswitch_lightblue, STRING("mobj01"), 125, 80, -120, PTR(bar_shikake), PTR(bar_shikake_up), GSWF(GSWF_MRI16_BAR_SWITCH_PRESSED))
    SPAWN_EVENT(switch_up_down)
    IF_INT_EQUAL(GSWF(GSWF_MRI16_WATER_SWITCH_PRESSED), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_now"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_after"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_f2_kaidan"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_mizu_after"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_l03"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_kai_rak"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_ana"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_mizi_kusa"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa01"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa02"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa03"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa04"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_mkusa05"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_mkusa_06"), 1, 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_now"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_mizu_before"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_f1_kaidan"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_mizu_before"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_l03"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_l04"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_f1_rak_r03"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("A_isk_03"), 1, 0)
        CALL(evt_puni_set_ymode, 5)
    END_IF
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(evt_gazigazi_entry)
    CALL(evt_item_entry, STRING("item_00"), ITEM_DIZZY_DIAL, -115, 0, -25, ITEM_ENTRY_STAY, GSWF(GSWF_MRI16_DIZZY_DIAL_TAKEN), 0)
    CALL(evt_mobj_itembox, STRING("mobj_box00"), -125, 0, 125, 0, 0, PTR(mobj_box00), GSWF(GSWF_MRI16_SHRINK_STOMP_CHEST_OPENED))
    CALL(evt_mobj_powerupblk, STRING("pblk1"), 65, -260, -70, 0, GSWF(GSWF_MRI16_SHINE_SPRITE), 0)
    RETURN
EVT_END()
