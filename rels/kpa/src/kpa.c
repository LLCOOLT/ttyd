// kpa (クッパ編, Bowser's interludes): registers kpa_00..kpa_07 and runs the side-scrolling stages: the object and item
// streams, coins, score, lives, the timer and the status display.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "driver/animdrv.h"

#include "manager/evtmgr_cmd.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "manager/fontmgr.h"
#include "driver/mobjdrv.h"
#include "memory.h"
#include "mario/mariost.h"
#include "mario/mario_pouch.h"
#include "stdio.h"
#include "mario/mario.h"
#include "data/mapdata.h"
#include "evt/evt_sub.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_twoddisp.h"
#include "koopa.h"
#include "kpa_act.h"
#include "kpa.h"
#include "driver/icondrv.h"
#include "driver/itemdrv.h"
#include "version.h"
#include "evt/evt_story.h"
#include "rel_module.h"
// FAKE: kpa.c calls iconDispGx through this prototype (the types it was compiled with) instead of the one in driver/icondrv.h; same registers, behaviour-identical.
typedef void (*IconDispGxArgOrderFn)(f32, Vec*, s16, u16);

typedef struct KpaGameWork {
    u8 stage;
    u8 lives;
    u8 time;
} KpaGameWork;
KpaGameWork* kwp;
static void kpa_stageclear_disp(CameraId camera, void* param);
static void kpa_status_disp(CameraId camera, void* param);
#define NUMERIC_ID ((u16*)numeric_id)

static USER_FUNC(kpa_add_coin);
static USER_FUNC(kpa_get_msg);
static USER_FUNC(kpa_make_item_name);
static USER_FUNC(kpa_make_mobj_name);
// Forward declaration; defined below (the script helper that turns on the Bowser map-object pool).
USER_FUNC(kpa_mobj_on);
static USER_FUNC(kpa_muteki_check);
static USER_FUNC(kpa_nohitenemy_ct_clear);
static USER_FUNC(kpa_pole_hitoff);
static USER_FUNC(kpa_set_time);
static USER_FUNC(kpa_status_main);
static USER_FUNC(kpa_time_countdown);
// Forward declaration; defined below.
USER_FUNC(kpa_fire_off);

s32 numeric_id[5];
extern EvtWord kpa_stage_clear[];

/**
 * Shared init for every side-scrolling stage (kpa_02..kpa_06 call it first):
 * puts the player in Bowser mode, shows the score HUD, and resets the time to 180 s.
 * A fresh arrival from another map also resets the try counter GSW_KPA_LIVES to 1;
 * "kpa_replay" (after a death) keeps it.
 * Clears the stage flags LSWF(2) = intro done, LSWF(3) = stage over, LSWF(4) = dying,
 * LSWF(5) = reached the goal pole.
 */
EVT_BEGIN(kpa_init)
    CALL(evt_mario_set_mode, 2)
    CALL(evt_mario_kill_party, 0)
    CALL(kpa_mobj_on)
    CALL(kpa_score_disp_init)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("kpa_replay"))
        SET_VALUE(GSW(GSW_KPA_TIME_LEFT), 180)
    ELSE
        IF_STR_NOT_EQUAL(LW(0), STRING("kpa_next_map"))
            SET_VALUE(GSW(GSW_KPA_LIVES), 1)
            SET_VALUE(GSW(GSW_KPA_TIME_LEFT), 180)
        END_IF
    END_IF
    CALL(evt_cam_type_change, 1, CAMERA_3D)
    SET_VALUE(LSWF(2), 0)
    SET_VALUE(LSWF(3), 0)
    SET_VALUE(LSWF(4), 0)
    SET_VALUE(LSWF(5), 0)
    RETURN
EVT_END()

/**
 * Builds a stage's map objects from a table (LW(0) = address of a kpa_act_stgN_mobj stream).
 * Each record is a type id followed by its coordinates, and -1 ends the list.
 * Types: 0/1 big obstruction blocks (levels 1/2), 2-5 bricks, 6 badge block, 7 hidden block, 8 plain block,
 * 9-11 pipes, 12 coral, 13-14 fire-bar bases, 15 goal pole (runs kpa_stage_clear), 16/17 red/blue jump stands.
 */
EVT_BEGIN(kpa_read_mobj)
    SET_INT_READ_ADDR(LW(0))
    LOOP(100)
        READ_INT(LW(1))
        IF_INT_EQUAL(LW(1), -1)
            BREAK_LOOP
        END_IF
        CALL(kpa_make_mobj_name, LW(2))
        SWITCH(LW(1))
            CASE_EQUAL(0)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_ojama_blk, LW(2), LW(3), LW(4), 0, 0, 0, STRING("MOBJ_Lv1BigBlock"))
            CASE_EQUAL(1)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_stone_blk, LW(2), LW(3), LW(4), 0, 0, 0, STRING("MOBJ_Lv2BigBlock"))
            CASE_EQUAL(2)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_brick, LW(2), LW(3), LW(4), 0, 0, 0, 0, 0)
            CASE_EQUAL(4)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_brick, LW(2), LW(3), LW(4), 0, 0, 2, 0, 0)
            CASE_EQUAL(3)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_brick, LW(2), LW(3), LW(4), 0, 0, 1, 0, 0)
            CASE_EQUAL(5)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_brick, LW(2), LW(3), LW(4), 0, 0, 3, 0, 0)
            CASE_EQUAL(6)
            READ_INT3(LW(3), LW(4), LW(5))
            CALL(evt_mobj_koopa_badgeblk, LW(2), LW(3), LW(4), 0, LW(5), 0, 0, 0)
            CASE_EQUAL(7)
            READ_INT3(LW(3), LW(4), LW(5))
            CALL(evt_mobj_koopa_hidden_blk, LW(2), LW(3), LW(4), 0, LW(5), 1, 0, 0)
            CASE_EQUAL(8)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_blk, LW(2), LW(3), LW(4), 0, 0, 0, 0)
            CASE_EQUAL(9)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_dokan, 0, LW(2), LW(3), LW(4), 0, 0, 0)
            CASE_EQUAL(10)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_dokan, 1, LW(2), LW(3), LW(4), 0, 0, 0)
            CASE_EQUAL(11)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_dokan, 2, LW(2), LW(3), LW(4), 0, 0, 0)
            CASE_EQUAL(12)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mobj_koopa_sango, LW(2), LW(3), LW(4), 0, 0, 0)
            CASE_EQUAL(13)
            READ_INT4(LW(3), LW(4), LW(5), LW(6))
            CALL(evt_mobj_koopa_fireber_dodai, 0, LW(2), LW(3), LW(4), 0, LW(5), LW(6), 0, 0)
            CASE_EQUAL(14)
            READ_INT4(LW(3), LW(4), LW(5), LW(6))
            CALL(evt_mobj_koopa_fireber_dodai, 1, LW(2), LW(3), LW(4), 0, LW(5), LW(6), 0, 0)
            CASE_EQUAL(15)
            READ_INT3(LW(3), LW(4), LW(5))
            CALL(evt_mobj_koopa_pole, STRING("pole"), LW(3), LW(4), 0, LW(5), PTR(kpa_stage_clear), LSWF(3))
            CASE_EQUAL(16)
            READ_INT3(LW(3), LW(4), LW(5))
            CALL(evt_mobj_jumpstand_red, 0, LW(2), LW(3), LW(4), 0, LW(5), 0)
            CASE_EQUAL(17)
            READ_INT3(LW(3), LW(4), LW(5))
            CALL(evt_mobj_jumpstand_blue, 0, LW(2), LW(5), LW(3), LW(4), 0, 0, 0)
        END_SWITCH
    END_LOOP
    RETURN
EVT_END()

/**
 * Pickup script for the stage coins made by kpa_read_item; LW(0)..LW(2) = coin position.
 * Adds a coin to Bowser's coin tally through kpa_add_coin.
 */
EVT_BEGIN(kpa_coin_evt)
    CALL(kpa_add_coin, LW(0), LW(1), LW(2))
    RETURN
EVT_END()

/**
 * Places a stage's coins from a table (LW(0) = address of a kpa_act_stgN_item stream; records are x, y pairs,
 * -1 ends the list). Each coin is a fixed ITEM_COIN picked up instantly, running kpa_coin_evt.
 */
EVT_BEGIN(kpa_read_item)
    SET_INT_READ_ADDR(LW(0))
    LOOP(0)
        READ_INT(LW(1))
        IF_INT_EQUAL(LW(1), -1)
            BREAK_LOOP
        END_IF
        CALL(kpa_make_item_name, LW(2))
        READ_INT2(LW(3), LW(4))
        CALL(evt_item_entry, LW(2), ITEM_COIN, LW(3), LW(4), 0, ITEM_ENTRY_FIXED, -1, PTR(kpa_coin_evt))
        CALL(evt_item_flag_on, LW(2), ITEM_FLAG_INSTANT_GET)
    END_LOOP
    RETURN
EVT_END()

/**
 * REL entry point: runs the static constructors
 * and registers the init script of each of the eight kpa maps (kpa_00..kpa_07) with the map loader.
 */
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("kpa_00", kpa_00_init_evt);
    relSetEvtAddr("kpa_01", kpa_01_init_evt);
    relSetEvtAddr("kpa_02", kpa_02_init_evt);
    relSetEvtAddr("kpa_03", kpa_03_init_evt);
    relSetEvtAddr("kpa_04", kpa_04_init_evt);
    relSetEvtAddr("kpa_05", kpa_05_init_evt);
    relSetEvtAddr("kpa_06", kpa_06_init_evt);
    relSetEvtAddr("kpa_07", kpa_07_init_evt);
}

/** REL exit point: runs the static destructors. */
void _epilog(void) {
    voidfunctionptr* dtor;

    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

/** Unresolved-import stub for the REL (empty). */
void _unresolved(void) {
}

/**
 * Script helper: returns the current Bowser stage number (1..3, from kwp->stage as set by kpa_status_init) in
 * args[0].
 */
USER_FUNC(kpa_status_get_stage) {
    evtSetValue(event, event->args[0], kwp->stage);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: calls mobjKoopaOn() to allocate the 128-entry map-object table used by the side-scrolling
 * stages. Runs once from kpa_init.
 */
USER_FUNC(kpa_mobj_on) {
    mobjKoopaOn();
    return EVT_RETURN_DONE;
}

/**
 * Script helper: writes a fresh unique map-object name ("mobj0", "mobj1", ... in hex) to args[0],
 * so kpa_read_mobj can give every block its own name.
 */
static USER_FUNC(kpa_make_mobj_name) {
    static char name[16];
    static s32 no;
    EvtWord* args = event->args;

    sprintf(name, "mobj%x", no);
    no++;
    evtSetValue(event, args[0], (EvtWord)name);
    return EVT_RETURN_DONE;
}

/** Script helper: writes a fresh unique item name ("item 0", "item 1", ... in hex) to args[0] for kpa_read_item. */
static USER_FUNC(kpa_make_item_name) {
    static char name[16];
    static s32 no;
    EvtWord* args = event->args;

    sprintf(name, "item%2x", no);
    no++;
    evtSetValue(event, args[0], (EvtWord)name);
    return EVT_RETURN_DONE;
}

/**
 * Script helper for kpa_coin_evt: args[0..2] = coin x, y, z.
 * Adds one coin to Bowser's stage coin tally at that position (kpaAddCoinPos),
 * then takes one coin back out of the pouch.
 * Guess: the second step undoes the coin the item pickup itself added to the pouch,
 * so only the stage tally counts.
 */
static USER_FUNC(kpa_add_coin) {
    EvtWord* args = event->args;

    kpaAddCoinPos(1, &(Vec){evtGetFloat(event, args[0]), evtGetFloat(event, args[1]), evtGetFloat(event, args[2])});
    pouchAddCoin(-1);
    return EVT_RETURN_DONE;
}

/**
 * Bowser's death sequence, shared by all stages:
 * runs once (LSWF(3)), locks controls, plays the defeated pose,
 * and has Bowser pop up and fall off the bottom of the screen.
 * It then bumps the try counter (max 99) and returns to the current stage with "kpa_replay" (stage 1: kpa_02, 2:
 * kpa_03, 3: kpa_05). Called on a timeout, a pit fall or lethal damage.
 */
EVT_BEGIN(kpa_dead)
    IF_INT_EQUAL(LSWF(3), 1)
        RETURN
    END_IF
    SET_VALUE(LSWF(3), 1)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_cam_letter_box_onoff, 0, 0)
#if VERSION >= VERSION_JP
    CALL(kpa_fire_off)
#endif
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_mario_adjust_dir)
    CALL(kpa_nohitenemy_ct_clear)
    CALL(evt_cam_ctrl_onoff, CAMERA_3D, 0)
    CALL(evt_mario_set_motion, 0)
    CALL(kpa_chg_pose, STRING("KPA2_D_4"))
    SET_VALUE(LSWF(4), 1)
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(4), LW(5), LW(6))
    SET_FLOAT_VALUE(LW(3), LW(5))
    SET_FLOAT_VALUE(LW(0), LW(3))
    SET_FLOAT_VALUE(LW(1), FLOAT(8.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(-0.13964844f))
    CALL(evt_koopa_chk_dead, LW(7))
    IF_INT_EQUAL(LW(7), 1)
        MULTIPLY_FLOAT(LW(1), FLOAT(0.69921875f))
    END_IF
    SUBTRACT_FLOAT(LW(3), FLOAT(200.0f))
    CALL(evt_sub_get_mapname, LW(15))
    IF_STR_EQUAL(LW(15), STRING("kpa_03"))
        SET_VALUE(LW(5), 150)
    ELSE
        SET_VALUE(LW(5), 155)
    END_IF
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(1), 0)
            SET_FLOAT_VALUE(LF(0), 0)
        ELSE
            SET_FLOAT_VALUE(LF(0), 1)
        END_IF
        ADD_FLOAT(LW(0), LW(1))
        ADD_FLOAT(LW(1), LW(2))
        IF_INT_LESS(LW(1), 0)
            IF_INT_EQUAL(LF(0), 0)
            END_IF
        END_IF
        IF_INT_LESS(LW(0), LW(3))
            BREAK_LOOP
        END_IF
        CALL(evt_mario_set_pos, LW(4), LW(0), LW(5))
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_LESS(GSW(GSW_KPA_LIVES), 99)
        ADD(GSW(GSW_KPA_LIVES), 1)
    END_IF
    CALL(kpa_status_get_stage, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(1), STRING("kpa_02"))
        CASE_EQUAL(2)
        SET_VALUE(LW(1), STRING("kpa_03"))
        CASE_EQUAL(3)
        SET_VALUE(LW(1), STRING("kpa_05"))
    END_SWITCH
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_cam_letter_box_disable, 0)
    END_INLINE_EVENT
    CALL(evt_bero_mapchange, LW(1), STRING("kpa_replay"))
    RETURN
EVT_END()

/**
 * Handler for Bowser falling into a pit: locks the letterbox, controls and camera,
 * waits until the ride-object lookup under Bowser returns a name, then runs kpa_dead.
 * Guess: the wait is for the end of the fall; the loop condition is the only evidence.
 */
EVT_BEGIN(kpa_fall_sub)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_cam_letter_box_onoff, 0, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_ctrl_onoff, CAMERA_3D, 0)
    CALL(evt_mario_get_pos, 0, LW(13), LW(14), LW(15))
    LOOP(0)
        CALL(evt_mario_get_name_hitobj_ride, LW(0))
        IF_STR_NOT_EQUAL(LW(0), STRING(""))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL_CHILD(kpa_dead)
    RETURN
EVT_END()

/** Script helper: zeroes the player's kpaNoHitTimer, the post-hit window in which enemies cannot hurt Bowser again. */
static USER_FUNC(kpa_nohitenemy_ct_clear) {
    MarioWork* mario = marioGetPtr();

    mario->kpaNoHitTimer = 0;
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/**
 * Script helper: calls kpaFireDelete(), which removes Bowser's fire-breath effect and stops its looping sound.
 * Run when Bowser dies so the flame does not linger (JP and later).
 */
USER_FUNC(kpa_fire_off) {
    kpaFireDelete();
    return EVT_RETURN_DONE;
}
#endif

/**
 * Script helper: args[0] = scale. Resizes Bowser uniformly and scales his collision box to match.
 * kpa_stage_start uses it to shrink him to about 0.4 for the intro and restore 1.0.
 */
static USER_FUNC(kpa_set_scale) {
    f32 scale = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();

    mario->scale = (Vec){scale, scale, scale};
    mario->wPlayerCollisionBox.x = scale * kpaGetWidth(1);
    mario->wPlayerCollisionBox.y = 75.0f * scale;
    return EVT_RETURN_DONE;
}

/**
 * Background music controller for the side-scrolling stages, spawned by the stage start.
 * Every frame it picks a track from the stage (LSW(1) = 0..2) and the time left:
 * the normal theme, a faster "UP1" variant when 30 s or less remain (and "UP2" for the first stage).
 * It switches to the invincibility music (BGM_STGK_FIELD2) while Bowser is invincible,
 * the defeat jingle when LSWF(4) is set and the goal jingle when LSWF(5) is set, then stops.
 * Changes wait 300 ms.
 */
EVT_BEGIN(kpa_bgm_change)
    IF_INT_GREATER(GSW(GSW_KPA_TIME_LEFT), 30)
        SET_VALUE(LW(2), 0)
    ELSE
        SET_VALUE(LW(2), 1)
    END_IF
    SET_VALUE(LW(3), -1)
    SET_VALUE(LW(4), -1)
    LABEL(10)
    IF_INT_GREATER(GSW(GSW_KPA_TIME_LEFT), 30)
        SET_VALUE(LW(3), 0)
        ADD(LW(3), LSW(1))
    ELSE
        IF_INT_EQUAL(LW(2), 0)
            SET_VALUE(LW(3), 3)
            ADD(LW(3), LSW(1))
        ELSE
            SET_VALUE(LW(3), 6)
        END_IF
    END_IF
    CALL(kpa_muteki_check)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(3), 7)
        SET_VALUE(LW(2), 0)
    END_IF
    IF_INT_EQUAL(LSWF(4), 1)
        SET_VALUE(LW(3), 8)
    END_IF
    IF_INT_EQUAL(LSWF(5), 1)
        SET_VALUE(LW(3), 9)
    END_IF
    IF_INT_NOT_EQUAL(LW(3), LW(4))
        SET_VALUE(LW(4), LW(3))
        SWITCH(LW(3))
            CASE_EQUAL(0)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD1"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD3"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(2)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD4"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(3)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD1_UP1"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(4)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD3_UP1"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(5)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD4_UP1"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(6)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STGK_FIELD1_UP2"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CASE_EQUAL(7)
            CALL(evt_snd_bgmoff, PSND_FADE_OUT)
            CALL(evt_snd_bgmon, PSND_FADE_OUT | PSND_CH(1), STRING("BGM_STGK_FIELD2"))
            CASE_EQUAL(8)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_FF_KUPPA_DOWN1"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            RETURN
            CASE_EQUAL(9)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_FF_KUPPA_GOAL1"))
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            RETURN
        END_SWITCH
        WAIT_MS(300)
    END_IF
    WAIT_FRAMES(1)
    GOTO(10)
    RETURN
EVT_END()

/**
 * Stage intro, spawned by each side-scrolling map:
 * fades out the sound, shrinks Bowser, frames him with the camera,
 * shows the cross and infinity 2D icons ("batu", "mugen") and prints the try message from kpa_get_msg.
 * Then it fades in, restores Bowser's size and control,
 * starts the music controller and sets LSWF(2) (intro done), which also starts kpa_time.
 */
EVT_BEGIN(kpa_stage_start)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_cam_letter_box_onoff, 0, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 1000)
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_map_blend_set_flag, 1, STRING("mario"), ANIM_MATERIAL_FLAG_NO_BLEND)
    CALL(evt_map_blend_set_flag, 1, STRING("mario"), ANIM_MATERIAL_FLAG_NO_BLEND2)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    CALL(evt_map_set_blend, 1, 0, 0, 0, 255)
    CALL(kpa_set_scale, FLOAT(0.39941406f))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 20)
    ADD(LW(1), 25)
    ADD(LW(2), 400)
    CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(0), LW(1), 0, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dispdir, 180)
    CALL(evt_seq_wait, 2)
    CALL(evt_twoddisp_init)
#if VERSION >= VERSION_US
    CALL(evt_twoddisp_entry, STRING("batu"), 477)
#else
    CALL(evt_twoddisp_entry, STRING("batu"), 469)
#endif
    CALL(evt_twoddisp_set_base_position, STRING("batu"), 20, -50)
    CALL(evt_twoddisp_set_position, STRING("batu"), 10, 0)
#if VERSION >= VERSION_US
    CALL(evt_twoddisp_entry, STRING("mugen"), 529)
#else
    CALL(evt_twoddisp_entry, STRING("mugen"), 526)
#endif
    CALL(evt_twoddisp_set_base_position, STRING("mugen"), 20, -50)
    CALL(evt_twoddisp_set_position, STRING("mugen"), 54, 3)
    CALL(kpa_get_msg, LW(0))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA2_S_1"), STRING("KPA2_T_1"))
    CALL(evt_msg_print, 0, LW(0), 0, STRING("mario"))
    CALL(evt_fade_out, 1000)
    SPAWN_EVENT(kpa_bgm_change)
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_map_blend_off, 0)
    CALL(evt_map_blend_off, 1)
    CALL(evt_twoddisp_flag_onoff, 0, STRING("batu"), 1)
    CALL(evt_twoddisp_flag_onoff, 0, STRING("mugen"), 1)
    CALL(kpa_set_scale, FLOAT(1.0f))
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_fade_in, 1000)
    SET_VALUE(LSWF(2), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

s32 numeric_id[] = {
#if VERSION >= VERSION_US
    31523299, 31785447, 32047595, 32309743, 32571891,
#else
    30999003, 31261151, 31523299, 31785447, 32047595,
#endif
};

#if VERSION >= VERSION_US
u16 kpa_status_icon_tbl[6][3] = {
    { 0x21A, 0x221, 0x21C }, { 0x21B, 0x221, 0x21C }, { 0x21B, 0x222, 0x21D },
    { 0x21B, 0x223, 0x21E }, { 0x21B, 0x224, 0x21F }, { 0x21B, 0x225, 0x220 },
};
#endif

/**
 * Event that calls kpa_status_main every frame so the HUD (score, coins, stage, tries, time) keeps being drawn.
 * Started by kpa_status_init.
 */
EVT_BEGIN(kpa_status_main_evt)
    LOOP(0)
        CALL(kpa_status_main)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * The stage clock.
 * Waits for the intro (LSWF(2)), then counts 180 seconds down in 10-second steps with the stopwatch helper,
 * updating the HUD through kpa_set_time. When it runs out it disables the goal pole and runs kpa_dead.
 * It stops quietly if the stage ends first (LSWF(3)).
 */
EVT_BEGIN(kpa_time)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 180)
    SUBTRACT(LW(1), GSW(GSW_KPA_TIME_LEFT))
    SET_VALUE(LW(3), LW(1))
    DIVIDE(LW(1), 10)
    MODULO(LW(3), 10)
    MULTIPLY(LW(3), 1000)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        IF_INT_NOT_EQUAL(LSWF(2), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    LOOP(0)
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(0))
        LOOP(0)
            IF_INT_NOT_EQUAL(LSWF(3), 0)
                RETURN
            END_IF
            CALL(evt_sub_get_stopwatch, LW(0), LW(2))
            IF_INT_EQUAL(LF(0), 0)
                ADD(LW(2), LW(3))
            END_IF
            CALL(kpa_set_time, LW(2), LW(1), GSW(GSW_KPA_TIME_LEFT))
            IF_INT_GREATER_OR_EQUAL(LW(2), 10000)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LF(0), 1)
        ADD(LW(1), 1)
        IF_INT_GREATER_OR_EQUAL(LW(1), 18)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(kpa_pole_hitoff)
    CALL_CHILD(kpa_dead)
    RETURN
EVT_END()

/**
 * Script helper: returns the intro message id "kpa_start_NNN" in args[0].
 * NNN = tries (capped at 30) + 30 per earlier stage - 1, so each retry shows a different line.
 */
static USER_FUNC(kpa_get_msg) {
    static char label[16];
    EvtWord* args = event->args;
    s32 n = kwp->lives;
    s32 stage = kwp->stage;

    if (n > 30) {
        n = 30;
    }
    sprintf(label, "kpa_start_%03d", n + (stage - 1) * 30 - 1);
    evtSetValue(event, args[0], (EvtWord)label);
    return EVT_RETURN_DONE;
}

/** Script helper: returns in LW(0) whether Bowser is currently invincible (kpaMutekiCheck). */
static USER_FUNC(kpa_muteki_check) {
    event->lwData[0] = kpaMutekiCheck();
    return EVT_RETURN_DONE;
}

// US moved these icons up by 8 in the icon table.
#if VERSION >= VERSION_US
#define KPA_ICON_OFS 8
#else
#define KPA_ICON_OFS 0
#endif

/**
 * Draw callback of the Bowser HUD, queued each frame by kpa_status_main:
 * the stage/score/tries/time labels (language- specific icons), the six-digit score, the coin count,
 * the stage number, the try counter (leading zero dropped) and the three-digit time.
 * The US release moved the number icons up by 8.
 */
static void kpa_status_disp(CameraId camera, void* param) {
    Vec pos;
    s32 digit[6];
    s32 i;
    s32 n;

    pos.x = -210.0f;
    pos.y = 160.0f;
#if VERSION >= VERSION_US
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, kpa_status_icon_tbl[gp->language][0]);
#else
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, (u32)gp->language ? 0x210 : 0x206);
#endif
    pos.x = 50.0f;
    pos.y = 160.0f;
#if VERSION >= VERSION_US
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, kpa_status_icon_tbl[gp->language][1]);
#else
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, 0x208);
#endif
    pos.x = 220.0f;
    pos.y = 160.0f;
#if VERSION >= VERSION_US
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, kpa_status_icon_tbl[gp->language][2]);
#else
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, 0x207);
#endif

    n = pouchGetKpaScore();
    digit[0] = n / 100000;
    pos.x = -250.0f;
    pos.y = 130.0f;
    n %= 100000;
    digit[1] = n / 10000;
    n %= 10000;
    digit[2] = n / 1000;
    n %= 1000;
    digit[3] = n / 100;
    n %= 100;
    digit[4] = n / 10;
    digit[5] = n % 10;
    for (i = 0; i < 6; i++) {
        ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }
    pos.x += 20.0f;
    ((IconDispGxArgOrderFn)iconDispGx)(0.7f, &pos, ICON_DISP_2D, 0x18B + KPA_ICON_OFS);
    pos.x += 30.0f;
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, 0x1D5 + KPA_ICON_OFS);

    n = pouchGetKpaCoin();
    digit[0] = n / 10;
    digit[1] = n % 10;
    pos.x += 20.0f;
    for (i = 0; i < 2; i++) {
        ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }

    pos.x = 50.0f;
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, NUMERIC_ID[kwp->stage]);
    pos.x += 20.0f;
    ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, 0x1EE + KPA_ICON_OFS);

    n = kwp->lives;
    digit[0] = n / 10;
    digit[1] = n % 10;
    pos.x += 20.0f;
    for (i = digit[0] == 0; i < 2; i++) {
        ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }

    n = kwp->time;
    pos.x = 212.0f;
    digit[0] = n / 100;
    n %= 100;
    digit[1] = n / 10;
    digit[2] = n % 10;
    for (i = 0; i < 3; i++) {
        ((IconDispGxArgOrderFn)iconDispGx)(1.0f, &pos, ICON_DISP_2D, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }
}

/** Script helper: queues kpa_status_disp for this frame on the 2D camera. */
static USER_FUNC(kpa_status_main) {
    dispEntry(CAMERA_2D, 1000.0f, 0, kpa_status_disp, NULL);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = stage, args[1] = tries, args[2] = time left.
 * Allocates the stage work block (kwp) with those values
 * and starts kpa_status_main_evt in a copy of the calling event's state.
 */
USER_FUNC(kpa_status_init) {
    EvtWord* args = event->args;
    s32 stage = evtGetValue(event, args[0]);
    s32 lives = evtGetValue(event, args[1]);
    s32 time = evtGetValue(event, args[2]);
    EventEntry* evt = evtEntryType(kpa_status_main_evt, event->priority, 0, event->type);
    s32 i;

    evt->unitId = event->unitId;
    evt->ownerNPC = event->ownerNPC;
    for (i = 0; i < 16; i++) {
        evt->lwData[i] = event->lwData[i];
    }
    for (i = 0; i < 3; i++) {
        evt->lfData[i] = event->lfData[i];
    }
    evt->uwBase = event->uwBase;
    evt->ufBase = event->ufBase;
    kwp = _mapAlloc(sizeof(KpaGameWork));
    kwp->stage = stage;
    kwp->lives = lives;
    kwp->time = time;
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = elapsed milliseconds in the current 10 s step, args[1] = completed 10 s steps,
 * args[2] = result.
 * Computes the time left (180 minus elapsed seconds), stores it in the HUD and returns it in args[2].
 */
static USER_FUNC(kpa_set_time) {
    EvtWord* args = event->args;
    s32 sec = evtGetValue(event, args[0]) / 1000;
    s32 time = 180 - (sec + evtGetValue(event, args[1]) * 10);

    if (time < 0) {
        time = 0;
    }
    kwp->time = time;
    evtSetValue(event, args[2], time);
    return EVT_RETURN_DONE;
}

/** Script helper: makes the goal pole ("pole") untouchable so a timed-out run cannot still finish. */
static USER_FUNC(kpa_pole_hitoff) {
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("pole");

    if (mobj != NULL) {
        mobj->flags |= MOBJ_FLAG_NO_HIT;
    }
    return EVT_RETURN_DONE;
}

/**
 * Draw callback that prints the large stage-clear text in the middle of the screen (the Japanese "goal in"
 * caption).
 */
static void kpa_stageclear_disp(CameraId camera, void* param) {
    FontDrawStart();
    FontDrawScale(2.0f);
    FontDrawEdge();
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    FontDrawString(-140.0f, 40.0f, "ゴールイン！！");
    FontDrawEdgeOff();
}

/**
 * Goal pole script: locks controls, plays the counter sound
 * while kpa_time_countdown turns each remaining second into 100 points,
 * then shows the "stageclear" effect and waits 3.5 s before returning control.
 */
EVT_BEGIN(kpa_stage_clear)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_sfxon, STRING("SFX_KUPPA_COUNTER1"), LW(0))
    CALL(kpa_time_countdown)
    CALL(evt_snd_sfxoff, LW(0))
    CALL(evt_eff, 0, STRING("stageclear"), 1, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(3500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Script helper: queues kpa_stageclear_disp for this frame on the 2D camera. */
static USER_FUNC(kpa_stageclear_disp_entry) {
    dispEntry(CAMERA_2D, 1000.0f, 0, kpa_stageclear_disp, NULL);
    return EVT_RETURN_DONE;
}

/**
 * Script helper for the goal tally: each call removes one second from the time left and adds 100 points;
 * it blocks the script (EVT_RETURN_BLOCK) until the time reaches zero.
 */
static USER_FUNC(kpa_time_countdown) {
    KpaGameWork* wp = kwp;

    if (wp->time != 0) {
        wp->time--;
        kpaAddScore(100);
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

/** Script helper: returns the 3D camera position (x, y, z) in args[0..2]. */
static USER_FUNC(kpa_get_cam_pt) {
    EvtWord* args = event->args;
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    evtSetFloat(event, args[0], cam->cameraPos.x);
    evtSetFloat(event, args[1], cam->cameraPos.y);
    evtSetFloat(event, args[2], cam->cameraPos.z);
    return EVT_RETURN_DONE;
}
