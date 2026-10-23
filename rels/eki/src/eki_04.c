#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);

__declspec(section ".data") f32 fd_eki_04_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_eki_04_neg_one_382;
__declspec(section ".data") f32 fd_eki_04___local_PI_383;
__declspec(section ".data") f32 fd_eki_04___local_3PIO2_385;
__declspec(section ".data") f32 fd_eki_04_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_eki_04___local_PIO2_384;
__declspec(section ".data") f32 fd_eki_04_one_381;
__declspec(section ".data") f32 fd_eki_04_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_eki_04_neg_one_365;
__declspec(section ".data") f32 fd_eki_04___local_PI_366;
__declspec(section ".data") f32 fd_eki_04___local_3PIO2_368;
__declspec(section ".data") f32 fd_eki_04_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_eki_04___local_PIO2_367;
__declspec(section ".data") f32 fd_eki_04_one_364;
static __declspec(section ".data") s32 e_close[12];
static __declspec(section ".data") s32 e_open[12];
static __declspec(section ".data") s32 s_close[12];
static __declspec(section ".data") s32 s_open[12];
static BeroEntry bero_data[3];
s32 evt_jump[21];
s32 eki_04_init_evt[66];

__declspec(section ".data") f32 fd_eki_04_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_eki_04_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_eki_04___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_eki_04___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_eki_04_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_eki_04___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_eki_04_one_381 = 1.0f;

__declspec(section ".data") f32 fd_eki_04_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_eki_04_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_eki_04___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_eki_04___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_eki_04_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_eki_04___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_eki_04_one_364 = 1.0f;

static __declspec(section ".data") EVT_BEGIN(e_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("e_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("e_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("s_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("s_door"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_data[] = {
    {
        "e_bero", // hitName
        1, // type
        3, // sfxId
        20000, // directionId
        100000, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        (s32)"eki_03", // nextMapName
        "w_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        (s32)e_close, // enterAnimeArg
        (s32)e_open, // exitAnimeArg
    },
    {
        "s_bero", // hitName
        1, // type
        3, // sfxId
        20000, // directionId
        100000, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        (s32)"eki_05", // nextMapName
        "n_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        (s32)s_close, // enterAnimeArg
        (s32)s_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(evt_jump)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_jump_jumpstand, 360, -900, 70, 300, 700, 75, 310, -900, 65, 6000, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(eki_04_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_cam_road_reset)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG6_EKI2"))
    CALL(evt_mobj_jumpstand_red, 0, STRING("mobj_jump"), 360, -900, 70, PTR(evt_jump), 0)
    CALL(evt_item_entry, STRING("item01"), 152, -250, -815, 70, 16, GSWF(3744), 0)
    CALL(evt_item_entry, STRING("item02"), 262, -250, 230, 40, 16, GSWF(3747), 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("futi_"), 2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("hasira\0"), 2)
    IF_INT_LESS(GSW(0), 316)
        SET_VALUE(GSW(0), 316)
    END_IF
    RETURN
EVT_END()

