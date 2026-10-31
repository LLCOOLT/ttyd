// aji_03 (敵のアジト, X-Naut Fortress): the crane game room: the UFO-catcher crane (ufo_main) and its prizes
// (keihin) and badges, the clockwork (zenmai) switches.
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"

#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "dolphin/mtx.h"
#include "driver/itemdrv.h"
#include "string.h"
#include "system.h"
#include "stdio.h"
#include "icon_ids.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_pouch.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_window.h"
#include "party/party_motion.h"
#include "aji.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/casedrv.h"

void icon_disp(CameraId camera, void* param);

USER_FUNC(evt_sousa_icon);
USER_FUNC(item_chk);
void icon_disp(CameraId camera, void* param);

static BeroEntry bero_entry_data[2];
extern EvtWord evt_kaitentou[];
extern EvtWord evt_kaitentou2[];
extern EvtWord ufo_hand[];
extern EvtWord move_left[];
extern EvtWord move_left2[];
extern EvtWord move_up[];
extern EvtWord move_up2[];
extern EvtWord hand_success[];
extern EvtWord hand_fail[];
extern EvtWord hand_release[];
extern EvtWord ufo_main[];
extern EvtWord evt_ufo_init[];
extern EvtWord evt_zenmai[];
extern EvtWord blink_sw[];
extern EvtWord evt_ufo_sousaban[];
extern EvtWord evt_sw_reinit[];
extern EvtWord evt_sw0[];
extern EvtWord evt_sw1[];
extern EvtWord evt_sw2[];
s32 haguruma_tbl[2];
extern EvtWord badge_evt[];
extern EvtWord badge_evt2[];
extern EvtWord badge_evt3[];

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "e_bero", // hitName
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
        "w_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(evt_kaitentou)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(10), MAPOBJ_FLAG_HIDE)
    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
    LOOP(0)
        CALL(evt_mapobj_rotate, 1, LW(10), 0, LW(0), 0)
        ADD_FLOAT(LW(0), FLOAT(5.0f))
        IF_FLOAT_GREATER(LW(0), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(GF(15), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(10), MAPOBJ_FLAG_HIDE)
    RETURN
EVT_END()

EVT_BEGIN(evt_kaitentou2)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(10), MAPOBJ_FLAG_HIDE)
    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
    LOOP(0)
        CALL(evt_mapobj_rotate, 1, LW(10), 0, 0, LW(0))
        ADD_FLOAT(LW(0), FLOAT(5.0f))
        IF_FLOAT_GREATER(LW(0), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(GF(15), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(10), MAPOBJ_FLAG_HIDE)
    RETURN
EVT_END()

static EVT_BEGIN(evt_hari)
    SET_VALUE(LW(6), LW(8))
    SET_VALUE(LW(7), LW(9))
    SET_VALUE(LW(8), LW(10))
    IF_INT_NOT_EQUAL(LW(6), -1)
    END_IF
    SET_VALUE(LW(2), 0)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        CALL(evt_sub_random, 900, LW(3))
        IF_INT_EQUAL(LF(0), 0)
            MULTIPLY(LW(3), -1)
            SET_VALUE(LF(0), 1)
        ELSE
            SET_VALUE(LF(0), 0)
        END_IF
        CALL(evt_sub_random, 1500, LW(9))
        ADD(LW(9), 1500)
        CALL(evt_sub_intpl_msec_init, 11, LW(2), LW(3), LW(9))
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_rotate, 1, LW(8), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(GF(15), 1)
                SET_VALUE(LW(3), LW(0))
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
        SET_VALUE(LW(2), LW(3))
        IF_INT_EQUAL(GF(15), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    IF_INT_NOT_EQUAL(LW(6), -1)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, LW(2), 0, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, LW(8), 0, 0, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(ufo_hand)
    LOOP(0)
        SET_VALUE(GF(9), 1)
        CALL(evt_sub_intpl_msec_init, 11, 0, 3000, 1000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(LW(2), LW(0))
        SET_FLOAT_VALUE(LW(3), LW(0))
        MULTIPLY_FLOAT(LW(3), FLOAT(-1.0f))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_1_a"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_2_a"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_1_b"), 0, 0, LW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_2_b"), 0, 0, LW(3))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, 3000, 0, 1000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(LW(2), LW(0))
        SET_FLOAT_VALUE(LW(3), LW(0))
        MULTIPLY_FLOAT(LW(3), FLOAT(-1.0f))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_1_a"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_2_a"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_1_b"), 0, 0, LW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_te_2_b"), 0, 0, LW(3))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        SET_VALUE(GF(9), 0)
        WAIT_FRAMES(2)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(move_left)
    SET_VALUE(GF(10), 1)
    RETURN
EVT_END()

EVT_BEGIN(move_left2)
    SET_VALUE(GF(10), 0)
    RETURN
EVT_END()

EVT_BEGIN(move_up)
    SET_VALUE(GF(11), 1)
    RETURN
EVT_END()

EVT_BEGIN(move_up2)
    SET_VALUE(GF(11), 0)
    RETURN
EVT_END()

EVT_BEGIN(hand_success)
    CALL(evt_sub_intpl_msec_init, 11, 0, 3000, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_c"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_c"), 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(hand_fail)
    CALL(evt_sub_intpl_msec_init, 11, 0, 5000, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_c"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_c"), 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 5000, 0, 1000)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_c"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_c"), 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(hand_release)
    CALL(evt_sub_intpl_msec_init, 11, 3000, 0, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_a"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_b"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_1_c"), 0, 0, LW(0))
    CALL(evt_mapobj_rotate, 1, STRING("S_te_2_c"), 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(ufo_main)
    SET_VALUE(GF(10), 0)
    SET_VALUE(GF(11), 0)
    SET_VALUE(GF(12), 0)
    SET_VALUE(GF(14), 0)
    SET_VALUE(GW(10), 230)
    SET_VALUE(GW(11), 100)
    CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
    LOOP(0)
        SPAWN_EVENT_GET_ID(PTR(ufo_hand), LW(9))
        LOOP(0)
            IF_INT_EQUAL(GF(10), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(GF(12), 1)
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(0), LW(1), LW(2), LW(3))
        LOOP(0)
            ADD(GW(10), -1)
            CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
            CALL(evt_mapobj_get_position, STRING("S_kure"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfx_pos, LW(3), LW(0), LW(1), LW(2))
            IF_INT_LESS(GW(10), -150)
                BREAK_LOOP
            END_IF
            IF_INT_NOT_EQUAL(GF(10), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_snd_sfxoff, LW(3))
        LOOP(0)
            IF_INT_EQUAL(GF(11), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(0), LW(1), LW(2), LW(3))
        LOOP(0)
            ADD(GW(11), -1)
            CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
            CALL(evt_mapobj_get_position, STRING("S_kure"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfx_pos, LW(3), LW(0), LW(1), LW(2))
            IF_INT_LESS(GW(11), -100)
                BREAK_LOOP
            END_IF
            IF_INT_NOT_EQUAL(GF(11), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_snd_sfxoff, LW(3))
        LABEL(100)
        IF_INT_EQUAL(GF(9), 1)
            WAIT_FRAMES(1)
            GOTO(100)
        END_IF
        DELETE_EVENT(LW(9))
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_sub_intpl_msec_init, 11, 0, -600, 2000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), LW(0), GW(11))
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfx_pos, LW(5), LW(2), LW(3), LW(4))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        CALL(item_chk, LW(0), LW(8))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(PTR(hand_success))
            SET_VALUE(LF(0), 1)
        ELSE
            CALL_CHILD(PTR(hand_success))
            SET_VALUE(LF(0), 0)
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_item_move_3d_position, LW(8), GW(10), 105, GW(11), 2000, 11)
            END_INLINE_EVENT
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, -600, 0, 2000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), LW(0), GW(11))
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfx_pos, LW(5), LW(2), LW(3), LW(4))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_snd_sfxoff, LW(5))
        IF_INT_EQUAL(LF(0), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_item_move_3d_position, LW(8), GW(10), 105, 110, 3000, 11)
            END_INLINE_EVENT
        END_IF
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_sub_intpl_msec_init, 11, GW(11), 110, 3000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, LW(0))
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfx_pos, LW(5), LW(2), LW(3), LW(4))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
        SET_VALUE(GW(11), 110)
        CALL(evt_snd_sfxoff, LW(5))
        CALL(evt_cam3d_evt_set, 50, 145, 529, 50, 50, -13, 2000, 11)
        IF_INT_EQUAL(LF(0), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_item_move_3d_position, LW(8), 40, 105, GW(11), 3000, 11)
            END_INLINE_EVENT
        END_IF
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_sub_intpl_msec_init, 11, GW(10), 40, 3000)
        LABEL(3)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_trans, 1, STRING("S_kure"), LW(0), 0, GW(11))
        CALL(evt_mapobj_get_position, STRING("S_kure"), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfx_pos, LW(5), LW(2), LW(3), LW(4))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(3)
        END_IF
        SET_VALUE(GW(10), 40)
        CALL(evt_snd_sfxoff, LW(5))
        IF_INT_EQUAL(LF(0), 1)
            BEGIN_INLINE_EVENT
                WAIT_MS(300)
                CALL(evt_item_set_move_dir_speed, LW(8), 0, FLOAT(0.0f))
                CALL(evt_item_set_gravity, LW(8), FLOAT(1.0f))
                CALL(evt_item_set_bound_rate, LW(8), FLOAT(1.0f))
                CALL(evt_item_set_jump_power, LW(8), FLOAT(0.0f))
                CALL(evt_item_set_bound_limit, LW(8), 0)
                CALL(evt_sub_random, 30, LW(0))
                ADD(LW(0), 20)
                CALL(evt_item_set_bound_next_speed, LW(8), LW(0))
                CALL(evt_sub_random, 90, LW(0))
                ADD(LW(0), 45)
                CALL(evt_item_set_bound_next_dir, LW(8), LW(0))
                CALL(evt_item_flag_on, LW(8), ITEM_FLAG_RESTORE_MOTION)
                CALL(evt_item_status_on, LW(8), ITEM_STATUS_CUSTOM_LAUNCH)
                CALL(evt_item_change_mode, LW(8), 5)
            END_INLINE_EVENT
            CALL_CHILD(PTR(hand_release))
        ELSE
            CALL_CHILD(PTR(hand_release))
        END_IF
        SET_VALUE(GF(12), 0)
        RETURN
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_ufo_init)
    LOOP(3)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
        WAIT_MS(100)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
        WAIT_MS(100)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_tama_a"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_tama_b"), MAPOBJ_FLAG_HIDE)
            WAIT_MS(500)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_tama_a"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_tama_b"), MAPOBJ_FLAG_HIDE)
            WAIT_MS(500)
            IF_INT_EQUAL(GF(14), 1)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 0, 0, 36000, 3000)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_hikari"), 0, LW(0), 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(GF(14), 1)
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    SPAWN_EVENT(PTR(ufo_main))
    RETURN
EVT_END()

EVT_BEGIN(evt_zenmai)
    CALL(evt_snd_sfxon, STRING("SFX_STG7_AMB_GEAR1"), 0)
    LOOP(0)
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_19_THE_DOOR_TO_LORD_CRUMP)
            CALL(evt_sub_intpl_msec_init, 0, 0, 36000, 2000)
        ELSE
            CALL(evt_sub_intpl_msec_init, 0, 0, 36000, 1000)
        END_IF
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(LW(2), LW(0))
        SET_FLOAT_VALUE(LW(3), LW(0))
        MULTIPLY_FLOAT(LW(3), FLOAT(-1.0f))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmai1"), 0, 0, LW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmai2"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmai3"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmai4"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmai5"), 0, 0, LW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmai6"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais1"), 0, 0, LW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais2"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais3"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais4"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais5"), 0, 0, LW(3))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais6"), 0, 0, LW(2))
        CALL(evt_mapobj_rotate, 1, STRING("S_zenmais_ari"), 0, 0, LW(2))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(blink_sw)
    LOOP(0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
        WAIT_MS(600)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
        WAIT_MS(600)
    END_LOOP
    RETURN
EVT_END()

#if VERSION >= VERSION_US
EVT_BEGIN(evt_ufo_sousaban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 230, 200, 380, 230, 130, -13, 1000, 11)
    WAIT_MS(1200)
    CALL(evt_mapobj_get_position, STRING("S_kure"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(0), LW(1), LW(2), LW(3))
    SPAWN_EVENT(PTR(evt_ufo_init))
    WAIT_MS(2200)
    CALL(evt_snd_sfxoff, LW(3))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 2300, 400, 3000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            SET_FLOAT_VALUE(GW(10), LW(0))
            CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, -65, 175, 529, -65, 80, -13, 3000, 11)
    WAIT_MS(3400)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_PANEL_FIRST_USE), 0)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_PANEL_FIRST_USE), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_00_01"), 0, 0)
    END_IF
    WAIT_MS(300)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        LOOP(0)
            CALL(evt_sousa_icon, 0, 200, 130)
        END_LOOP
    END_INLINE_EVENT
    WAIT_FRAMES(1)
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(1)
    SET_VALUE(GF(10), 1)
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 256)
        ELSE
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(1)
    SET_VALUE(GF(10), 0)
    DELETE_EVENT(LW(10))
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        LOOP(0)
            CALL(evt_sousa_icon, 1, 200, 70)
        END_LOOP
    END_INLINE_EVENT
    WAIT_FRAMES(1)
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 512)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(1)
    SET_VALUE(GF(11), 1)
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 512)
        ELSE
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(1)
    SET_VALUE(GF(11), 0)
    DELETE_EVENT(LW(10))
    LOOP(0)
        IF_INT_EQUAL(GF(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_sub_intpl_msec_init, 11, 400, 2300, 3000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        SET_FLOAT_VALUE(GW(10), LW(0))
        CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(GW(10), 230)
    SET_VALUE(GW(11), 100)
    CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(GF(14), 1)
    CALL(evt_cam_shift_reset)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#else
EVT_BEGIN(evt_ufo_sousaban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 230, 200, 380, 230, 130, -13, 1000, 11)
    WAIT_MS(1200)
    CALL(evt_mapobj_get_position, STRING("S_kure"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_MOVE1"), LW(0), LW(1), LW(2), LW(3))
    SPAWN_EVENT(PTR(evt_ufo_init))
    WAIT_MS(2200)
    CALL(evt_snd_sfxoff, LW(3))
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 2300, 400, 3000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            SET_FLOAT_VALUE(GW(10), LW(0))
            CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, -65, 175, 529, -65, 80, -13, 3000, 11)
    WAIT_MS(3400)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_PANEL_FIRST_USE), 0)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_PANEL_FIRST_USE), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_00_01"), 0, 0)
    END_IF
    WAIT_MS(300)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        LOOP(0)
            CALL(evt_sousa_icon, 0, 200, 130)
        END_LOOP
    END_INLINE_EVENT
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GF(10), 1)
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 256)
        ELSE
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GF(10), 0)
    DELETE_EVENT(LW(10))
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        LOOP(0)
            CALL(evt_sousa_icon, 1, 200, 70)
        END_LOOP
    END_INLINE_EVENT
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 512)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GF(11), 1)
    LOOP(0)
        CALL(evt_key_get_button, 0, LW(0))
        IF_BITS_SET(LW(0), 512)
        ELSE
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GF(11), 0)
    DELETE_EVENT(LW(10))
    LOOP(0)
        IF_INT_EQUAL(GF(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_sub_intpl_msec_init, 11, 400, 2300, 3000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        SET_FLOAT_VALUE(GW(10), LW(0))
        CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(GW(10), 230)
    SET_VALUE(GW(11), 100)
    CALL(evt_mapobj_trans, 1, STRING("S_kure"), GW(10), 0, GW(11))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(GF(14), 1)
    CALL(evt_cam_shift_reset)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#endif

static EVT_BEGIN(evt_sw)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 0)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 0)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 0)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 0)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 1)
        CALL(evt_mario_key_onoff, 0)
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, 20, 125, 394, 20, 55, 0, 1000, 11)
        WAIT_MS(1500)
        BEGIN_INLINE_EVENT
            CALL(evt_mapobj_get_position, STRING("S_pato4"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_SIREN1"), LW(0), LW(1), LW(2), LW(3))
            WAIT_MS(3000)
            CALL(evt_snd_sfxoff, LW(3))
        END_INLINE_EVENT
        SET_VALUE(LW(10), STRING("S_pato4"))
        SPAWN_EVENT(PTR(evt_kaitentou))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
        SET_VALUE(LW(8), -1)
        SET_VALUE(LW(9), -1)
        SET_VALUE(LW(10), STRING("S_hari01"))
        SPAWN_EVENT(PTR(evt_hari))
        SET_VALUE(LW(8), -1)
        SET_VALUE(LW(9), -1)
        SET_VALUE(LW(10), STRING("S_hari02"))
        SPAWN_EVENT(PTR(evt_hari))
        WAIT_MS(500)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui_01"), 0, PTR(evt_ufo_sousaban), 0)
        CALL(evt_cam3d_evt_off, 500, 11)
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_sw_reinit)
    SET_VALUE(GF(15), 1)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui1"), 0, PTR(evt_sw0), 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui2"), 0, PTR(evt_sw1), 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui3"), 0, PTR(evt_sw2), 0)
    END_IF
    DELETE_EVENT(GW(13))
    DELETE_EVENT(GW(14))
    DELETE_EVENT(GW(15))
    WAIT_FRAMES(5)
    SET_VALUE(GF(15), 0)
    SET_VALUE(LW(0), STRING("sui__1"))
    SET_VALUE(LW(1), STRING("sui__2"))
    SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(13))
    SET_VALUE(LW(0), STRING("sui_2_1"))
    SET_VALUE(LW(1), STRING("sui_2_2"))
    SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(14))
    SET_VALUE(LW(0), STRING("sui_3_1"))
    SET_VALUE(LW(1), STRING("sui_3_2"))
    SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(15))
    RETURN
EVT_END()

EVT_BEGIN(evt_sw0)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 0)
        IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 0)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_BUTTON_PUSH1"), LW(0), LW(1), LW(2), 0)
    IF_INT_EQUAL(LF(0), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 1)
        DELETE_EVENT(GW(13))
        WAIT_FRAMES(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui__1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("sui__2"), MAPOBJ_FLAG_HIDE)
        SET_VALUE(LW(10), STRING("S_pato1"))
        SPAWN_EVENT(PTR(evt_kaitentou2))
        SET_VALUE(LW(8), STRING("meta_1_1"))
        SET_VALUE(LW(9), STRING("meta_1_2"))
        SET_VALUE(LW(10), STRING("S_hari04"))
        SPAWN_EVENT(PTR(evt_hari))
        CALL_CHILD(PTR(evt_sw))
        CALL(evt_exit_case_evt)
    ELSE
        CALL_CHILD(PTR(evt_sw_reinit))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_sw1)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 1)
        IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 1)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_BUTTON_PUSH1"), LW(0), LW(1), LW(2), 0)
    IF_INT_EQUAL(LF(0), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 1)
        DELETE_EVENT(GW(14))
        WAIT_FRAMES(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("sui_2_2"), MAPOBJ_FLAG_HIDE)
        SET_VALUE(LW(10), STRING("S_pato2"))
        SPAWN_EVENT(PTR(evt_kaitentou2))
        SET_VALUE(LW(8), STRING("meta_2_1"))
        SET_VALUE(LW(9), STRING("meta_2_2"))
        SET_VALUE(LW(10), STRING("S_hari05"))
        SPAWN_EVENT(PTR(evt_hari))
        CALL_CHILD(PTR(evt_sw))
        CALL(evt_exit_case_evt)
    ELSE
        CALL_CHILD(PTR(evt_sw_reinit))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_sw2)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 1)
        IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 0)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CRANE_BUTTON_PUSH1"), LW(0), LW(1), LW(2), 0)
    IF_INT_EQUAL(LF(0), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 1)
        DELETE_EVENT(GW(15))
        WAIT_FRAMES(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui_3_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("sui_3_2"), MAPOBJ_FLAG_HIDE)
        SET_VALUE(LW(10), STRING("S_pato3"))
        SPAWN_EVENT(PTR(evt_kaitentou2))
        SET_VALUE(LW(8), STRING("meta_3_1"))
        SET_VALUE(LW(9), STRING("meta_3_2"))
        SET_VALUE(LW(10), STRING("S_hari06"))
        SPAWN_EVENT(PTR(evt_hari))
        CALL_CHILD(PTR(evt_sw))
        CALL(evt_exit_case_evt)
    ELSE
        CALL_CHILD(PTR(evt_sw_reinit))
    END_IF
    RETURN
EVT_END()

s32 haguruma_tbl[] = {
    85, -1,
};

static EVT_BEGIN(evt_haguruma)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_pouch_check_item, ITEM_COG, LW(0))
    IF_INT_LESS(LW(0), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_00_00"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    CALL(evt_win_item_select, 0, PTR(haguruma_tbl), LW(0), 0)
    IF_INT_NOT_EQUAL(LW(0), -1)
        BEGIN_INLINE_EVENT
            CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
            CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
            WAIT_MS(2000)
            CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
            CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
        END_INLINE_EVENT
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_zenmais_nashi"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_zenmais_ari"), MAPOBJ_FLAG_HIDE)
        SPAWN_EVENT(PTR(evt_zenmai))
        CALL(evt_pouch_remove_item, LW(0), LW(1))
        SET_VALUE(GSWF(GSWF_AJI03_COG_INSERTED), 1)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui1"), 0, PTR(evt_sw0), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui2"), 0, PTR(evt_sw1), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui3"), 0, PTR(evt_sw2), 0)
        SET_VALUE(LW(0), STRING("sui__1"))
        SET_VALUE(LW(1), STRING("sui__2"))
        SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(13))
        SET_VALUE(LW(0), STRING("sui_2_1"))
        SET_VALUE(LW(1), STRING("sui_2_2"))
        SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(14))
        SET_VALUE(LW(0), STRING("sui_3_1"))
        SET_VALUE(LW(1), STRING("sui_3_2"))
        SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(15))
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_exit_case_evt)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(badge_evt)
    SET_VALUE(GSWF(GSWF_AJI03_CRANE_PRIZE_A), 1)
    RETURN
EVT_END()

EVT_BEGIN(badge_evt2)
    SET_VALUE(GSWF(GSWF_AJI03_CRANE_PRIZE_B), 1)
    RETURN
EVT_END()

EVT_BEGIN(badge_evt3)
    SET_VALUE(GSWF(GSWF_AJI03_STAR_PIECE_PRIZE), 1)
    RETURN
EVT_END()

EVT_BEGIN(aji_03_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_AJI3"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hikari"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_trans, 1, STRING("S_kure"), 230, 0, 100)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_tama_a"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_tama_b"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_rotate, 1, STRING("S_tanadoor_1"), 0, 70, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_tanadoor_2"), 0, 70, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 1)
        SET_VALUE(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 1)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_COG_INSERTED), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_tanadoor_1"), 0, PTR(evt_haguruma), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_zenmais_ari"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_zenmais_nashi"), MAPOBJ_FLAG_HIDE)
        SPAWN_EVENT(PTR(evt_zenmai))
        IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 1)
            CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui_01"), 0, PTR(evt_ufo_sousaban), 0)
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_COG_INSERTED), 1)
        IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 0)
            CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui1"), 0, PTR(evt_sw0), 0)
            CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui2"), 0, PTR(evt_sw1), 0)
            CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_sui3"), 0, PTR(evt_sw2), 0)
            SET_VALUE(LW(0), STRING("sui__1"))
            SET_VALUE(LW(1), STRING("sui__2"))
            SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(13))
            SET_VALUE(LW(0), STRING("sui_2_1"))
            SET_VALUE(LW(1), STRING("sui_2_2"))
            SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(14))
            SET_VALUE(LW(0), STRING("sui_3_1"))
            SET_VALUE(LW(1), STRING("sui_3_2"))
            SPAWN_EVENT_GET_ID(PTR(blink_sw), GW(15))
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui__2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui_2_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui_3_2"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui__1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("sui_3_1"), MAPOBJ_FLAG_HIDE)
    END_IF
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_pato1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_pato2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_pato3"), MAPOBJ_FLAG_HIDE)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_1), 1)
        SET_VALUE(LW(10), STRING("S_pato1"))
        SPAWN_EVENT(PTR(evt_kaitentou2))
        SET_VALUE(LW(8), STRING("meta_1_1"))
        SET_VALUE(LW(9), STRING("meta_1_2"))
        SET_VALUE(LW(10), STRING("S_hari04"))
        SPAWN_EVENT(PTR(evt_hari))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_2), 1)
        SET_VALUE(LW(10), STRING("S_pato2"))
        SPAWN_EVENT(PTR(evt_kaitentou2))
        SET_VALUE(LW(8), STRING("meta_2_1"))
        SET_VALUE(LW(9), STRING("meta_2_2"))
        SET_VALUE(LW(10), STRING("S_hari05"))
        SPAWN_EVENT(PTR(evt_hari))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_BUTTON_3), 1)
        SET_VALUE(LW(10), STRING("S_pato3"))
        SPAWN_EVENT(PTR(evt_kaitentou2))
        SET_VALUE(LW(8), STRING("meta_3_1"))
        SET_VALUE(LW(9), STRING("meta_3_2"))
        SET_VALUE(LW(10), STRING("S_hari06"))
        SPAWN_EVENT(PTR(evt_hari))
    END_IF
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_pato4"), MAPOBJ_FLAG_HIDE)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 1)
        SET_VALUE(LW(10), STRING("S_pato4"))
        SPAWN_EVENT(PTR(evt_kaitentou))
        SET_VALUE(LW(8), -1)
        SET_VALUE(LW(9), -1)
        SET_VALUE(LW(10), STRING("S_hari01"))
        SPAWN_EVENT(PTR(evt_hari))
        SET_VALUE(LW(8), -1)
        SET_VALUE(LW(9), -1)
        SET_VALUE(LW(10), STRING("S_hari02"))
        SPAWN_EVENT(PTR(evt_hari))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_ACTIVATED), 1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_1_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_3_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
    END_IF
    CALL(evt_item_entry, STRING("keihin00"), ITEM_COIN, -150, 50, 100, 16, -1, 0)
    CALL(evt_item_entry, STRING("keihin01"), ITEM_COIN, -100, 50, 100, 16, -1, 0)
    CALL(evt_item_entry, STRING("keihin02"), ITEM_COIN, -50, 50, 100, 16, -1, 0)
    CALL(evt_item_entry, STRING("keihin03"), ITEM_COIN, -150, 50, 0, 16, -1, 0)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_PRIZE_A), 0)
        CALL(evt_item_entry, STRING("keihin04"), ITEM_FEELING_FINE, -100, 50, 0, 16, -1, PTR(badge_evt))
    END_IF
    CALL(evt_item_entry, STRING("keihin05"), ITEM_COIN, -50, 50, 0, 16, -1, 0)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_CRANE_PRIZE_B), 0)
        CALL(evt_item_entry, STRING("keihin06"), ITEM_FEELING_FINE_P, -150, 50, -100, 16, -1, PTR(badge_evt2))
    END_IF
    CALL(evt_item_entry, STRING("keihin07"), ITEM_COIN, -100, 50, -100, 16, -1, 0)
    IF_INT_EQUAL(GSWF(GSWF_AJI03_STAR_PIECE_PRIZE), 0)
        CALL(evt_item_entry, STRING("keihin08"), ITEM_STAR_PIECE, -50, 50, -100, 16, -1, PTR(badge_evt3))
    END_IF
    SPAWN_EVENT(PTR(evt_emergency))
    RETURN
EVT_END()

USER_FUNC(evt_sousa_icon) {
    EvtWord* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 x = evtGetValue(event, args[1]);
    s32 y = evtGetValue(event, args[2]);

    event->userdata[0] = type;
    event->userdata[1] = x;
    event->userdata[2] = y;
    dispEntry(CAMERA_2D, 0.0f, 0, icon_disp, event);
    return EVT_RETURN_YIELD;
}

void icon_disp(CameraId camera, void* param) {
    EventEntry* event = param;
    Mtx trans;
    Mtx scale;
    Mtx rot;

    camGetPtr(camera);
    if (event->userdata[0] == 0) {
        PSMTXTrans(trans, event->userdata[1] - 70, event->userdata[2], 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXRotRad(rot, 'z', 0.0f);
        PSMTXConcat(trans, scale, trans);
        PSMTXConcat(trans, rot, trans);
        iconDispGx2(trans, 0x10, ICON_163);
        PSMTXTrans(trans, event->userdata[1], event->userdata[2], 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXConcat(trans, scale, trans);
        iconDispGx2(trans, 0x10, ICON_064);
    } else {
        PSMTXTrans(trans, event->userdata[1] - 30, event->userdata[2] + 100, 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXRotRad(rot, 'z', 4.712389f);
        PSMTXConcat(trans, scale, trans);
        PSMTXConcat(trans, rot, trans);
        iconDispGx2(trans, 0x10, ICON_163);
        PSMTXTrans(trans, event->userdata[1], event->userdata[2], 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXConcat(trans, scale, trans);
        iconDispGx2(trans, 0x10, ICON_066);
    }
}

static USER_FUNC(evt_itemNameToItemID) {
    static char tmp[64];
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    ItemEntry* item = itemNameToPtr(name);

    strncpy(tmp, name, sizeof(tmp));
    evtSetValue(event, args[1], item->itemId);
    evtSetValue(event, args[2], (EvtWord)name);
    return EVT_RETURN_DONE;
}

USER_FUNC(item_chk) {
    char name[256];
    EvtWord* args = event->args;
    f32 x = evtGetValue(event, GW(10));
    f32 z = evtGetValue(event, GW(11));
    f32 minDist = 20.0f;
    s32 i;
    ItemEntry* found = NULL;
    ItemEntry* item;

    for (i = 0; i < 32; i++) {
        sprintf(name, "keihin%02d", i);
        item = itemNameToPtr(name);
        if (item != NULL) {
            f32 dist = distABf(item->position.x, item->position.z, x, z);
            if (dist < minDist) {
                minDist = dist;
                found = item;
            }
        }
    }
    if (found != NULL) {
        evtSetValue(event, args[0], TRUE);
        evtSetValue(event, args[1], (EvtWord)found->name);
    } else {
        evtSetValue(event, args[0], FALSE);
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
