// las_20 (ラストダンジョン, Palace of Shadow): the room of star switches (hosi).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "las.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/camdrv.h"

static USER_FUNC(get_hosi_name);

static BeroEntry bero_entry_data[4];
static const char* haguruma_hontai[14];
static const char* haguruma_hontai2[6];
static const char* haguruma_kage[12];
static const char* haguruma_kage2[5];
const char* hosi_name[14];

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "e_bero", // hitName
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
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
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
        "las_19", // nextMapName
        "n_bero", // nextBeroName
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
        "las_21", // nextMapName
        "n_bero", // nextBeroName
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

static EVT_BEGIN(haguruma_evt)
    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(4), FLOAT(0.0f))
    LOOP(0)
        SET_INT_READ_ADDR(PTR(&haguruma_hontai))
        LOOP(14)
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

static EVT_BEGIN(dai_evt)
    SET_VALUE(LW(0), STRING("S_move_dai"))
    SET_VALUE(LW(1), STRING("A_move_dai"))
    SET_VALUE(LW(2), 2700)
    CALL_CHILD(move_dai)
    RETURN
EVT_END()

const char* hosi_name[] = {
    "S_hosi_02a",
    "S_hosi_02b",
    "S_hosi_03a",
    "S_hosi_03b",
    "S_hosi_04a",
    "S_hosi_04b",
    "S_hosi_05a",
    "S_hosi_05b",
    "S_hosi_06a",
    "S_hosi_06b",
    "S_hosi_07a",
    "S_hosi_07b",
    "S_hosi_08a",
    "S_hosi_08b",
};

EVT_BEGIN(hosi_sw_check)
    SET_VALUE(LW(0), 0)
    IF_INT_EQUAL(LSWF(1), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(2), 0)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(3), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(4), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(5), 0)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(6), 1)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LSWF(7), 0)
        ADD(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 7)
        CALL(evt_mario_key_onoff, 0)
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, -289, 112, 1038, -289, -43, -63, 800, 11)
        WAIT_MS(800)
        SET_VALUE(LW(0), 0)
        LOOP(7)
            CALL(get_hosi_name, LW(0), LW(1), LW(2))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(2), MAPOBJ_FLAG_HIDE)
            ADD(LW(0), 1)
        END_LOOP
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(1), 6)
        LOOP(50)
            CALL(get_hosi_name, LW(0), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(2), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(3), MAPOBJ_FLAG_HIDE)
            CALL(get_hosi_name, LW(1), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(2), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(3), MAPOBJ_FLAG_HIDE)
            WAIT_MS(50)
            SET_VALUE(LW(1), LW(0))
            ADD(LW(0), 1)
            MODULO(LW(0), 7)
        END_LOOP
        LOOP(0)
            IF_INT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            CALL(get_hosi_name, LW(0), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(2), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(3), MAPOBJ_FLAG_HIDE)
            CALL(get_hosi_name, LW(1), LW(2), LW(3))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(2), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(3), MAPOBJ_FLAG_HIDE)
            WAIT_MS(50)
            SET_VALUE(LW(1), LW(0))
            ADD(LW(0), 1)
            MODULO(LW(0), 7)
        END_LOOP
        CALL(get_hosi_name, LW(1), LW(2), LW(3))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(2), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(3), MAPOBJ_FLAG_HIDE)
        WAIT_MS(200)
        SET_VALUE(LW(0), 0)
        LOOP(7)
            CALL(get_hosi_name, LW(0), LW(1), LW(2))
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(2), MAPOBJ_FLAG_HIDE)
            ADD(LW(0), 1)
        END_LOOP
        CALL(evt_snd_sfxon, STRING("SFX_STG8_STAR_LIGHTUP2"), 0)
        WAIT_MS(100)
        CALL(evt_snd_sfxon, STRING("SFX_STG8_QUAKE3"), LW(10))
        CALL(evt_cam_shake, CAMERA_3D, FLOAT(0.01953125f), FLOAT(0.0f), 1000)
        CALL(evt_snd_sfxoff, LW(10))
        CALL(evt_mobj_delete, STRING("hosi_02_sw"))
        CALL(evt_mobj_delete, STRING("hosi_03_sw"))
        CALL(evt_mobj_delete, STRING("hosi_04_sw"))
        CALL(evt_mobj_delete, STRING("hosi_05_sw"))
        CALL(evt_mobj_delete, STRING("hosi_06_sw"))
        CALL(evt_mobj_delete, STRING("hosi_07_sw"))
        CALL(evt_mobj_delete, STRING("hosi_08_sw"))
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG8_11_STAR_PUZZLE)
        CALL(evt_cam3d_evt_off, 800, 11)
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(hosi_onoff)
    GET_INT_INDEXED(LW(2), LW(3))
    IF_INT_EQUAL(LW(3), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
        SET_INT_INDEXED(LW(2), 1)
        CALL(evt_mapobj_get_position, LW(0), LW(3), LW(4), LW(5))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_eff64, STRING(""), STRING("stardust_n64"), 2, LW(3), LW(4), LW(5), 30, 0, 0, 0, 0, 0, 0, 0)
#else
        CALL(evt_eff64, 0, STRING("stardust_n64"), 2, LW(3), LW(4), LW(5), 30, 0, 0, 0, 0, 0, 0, 0)
#endif
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG8_STAR_LIGHTUP1"), LW(3), LW(4), LW(5), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
        SET_INT_INDEXED(LW(2), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(hosi_02_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_02a"))
    SET_VALUE(LW(1), STRING("S_hosi_02b"))
    SET_RAW_VALUE(LW(2), LSWF(1))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_03_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_03a"))
    SET_VALUE(LW(1), STRING("S_hosi_03b"))
    SET_RAW_VALUE(LW(2), LSWF(2))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_04_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_04a"))
    SET_VALUE(LW(1), STRING("S_hosi_04b"))
    SET_RAW_VALUE(LW(2), LSWF(3))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_05_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_05a"))
    SET_VALUE(LW(1), STRING("S_hosi_05b"))
    SET_RAW_VALUE(LW(2), LSWF(4))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_06_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_06a"))
    SET_VALUE(LW(1), STRING("S_hosi_06b"))
    SET_RAW_VALUE(LW(2), LSWF(5))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_07_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_07a"))
    SET_VALUE(LW(1), STRING("S_hosi_07b"))
    SET_RAW_VALUE(LW(2), LSWF(6))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_08_sw_evt)
    SET_VALUE(LW(0), STRING("S_hosi_08a"))
    SET_VALUE(LW(1), STRING("S_hosi_08b"))
    SET_RAW_VALUE(LW(2), LSWF(7))
    CALL_CHILD(hosi_onoff)
    CALL_CHILD(hosi_sw_check)
    RETURN
EVT_END()

EVT_BEGIN(hosi_init)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG8_11_STAR_PUZZLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_02a"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_03a"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_04a"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_05a"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_06a"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_07a"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_08a"), MAPOBJ_FLAG_HIDE)
        SET_VALUE(LSWF(1), 0)
        SET_VALUE(LSWF(2), 0)
        SET_VALUE(LSWF(3), 0)
        SET_VALUE(LSWF(4), 0)
        SET_VALUE(LSWF(5), 0)
        SET_VALUE(LSWF(6), 0)
        SET_VALUE(LSWF(7), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_02_sw"), -545, -50, -120, PTR(hosi_02_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_03_sw"), -460, -50, -120, PTR(hosi_03_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_04_sw"), -376, -50, -120, PTR(hosi_04_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_05_sw"), -289, -50, -120, PTR(hosi_05_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_06_sw"), -205, -50, -120, PTR(hosi_06_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_07_sw"), -121, -50, -120, PTR(hosi_07_sw_evt), 0)
        CALL(evt_mobj_floatswitch_red, 0, STRING("hosi_08_sw"), -37, -50, -120, PTR(hosi_08_sw_evt), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_02b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_03b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_04b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_05b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_06b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_07b"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_hosi_08b"), MAPOBJ_FLAG_HIDE)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(las_20_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG8_LST3"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG8_LAS5"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 2)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_01a"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_08a"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_09a"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_12a"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 0, STRING("S_hgm_19a"), MAPOBJ_FLAG_BBOX_CULL)
    SPAWN_EVENT(haguruma_evt)
    CALL(evt_map_playanim, STRING("kusari"), 1, 0)
    CALL(evt_hit_bind_mapobj, STRING("A_move_dai"), STRING("S_move_dai"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_move_dai"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_move_dai"), 0, 0)
    CALL(evt_mobj_switch_red, 0, STRING("dai_switch"), -250, -290, 100, PTR(dai_evt), 0)
    SPAWN_EVENT(hosi_init)
    CALL(evt_mobj_badgeblk, STRING("mobj_item00"), 295, -440, -15, ITEM_REPEL_CAPE, 0, GSWF(GSWF_LAS20_REPEL_CAPE_BLOCK_HIT), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_item01"), 640, -320, -135, ITEM_LIFE_SHROOM, 0, GSWF(GSWF_LAS20_LIFE_SHROOM_BLOCK_HIT), 0)
    RETURN
EVT_END()

static USER_FUNC(get_hosi_name) {
    EvtWord* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], (EvtWord)hosi_name[idx * 2]);
    evtSetValue(event, args[2], (EvtWord)hosi_name[idx * 2 + 1]);
    return EVT_RETURN_DONE;
}
