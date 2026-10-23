#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);

__declspec(section ".data") f32 fd_dou_06_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dou_06_neg_one_382;
__declspec(section ".data") f32 fd_dou_06___local_PI_383;
__declspec(section ".data") f32 fd_dou_06___local_3PIO2_385;
__declspec(section ".data") f32 fd_dou_06_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dou_06___local_PIO2_384;
__declspec(section ".data") f32 fd_dou_06_one_381;
__declspec(section ".data") f32 fd_dou_06_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dou_06_neg_one_365;
__declspec(section ".data") f32 fd_dou_06___local_PI_366;
__declspec(section ".data") f32 fd_dou_06___local_3PIO2_368;
__declspec(section ".data") f32 fd_dou_06_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_dou_06___local_PIO2_367;
__declspec(section ".data") f32 fd_dou_06_one_364;
static BeroEntry bero_entry_data[3];
s32 dou_06_init_evt[41];

__declspec(section ".data") f32 fd_dou_06_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_dou_06_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_dou_06___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_dou_06___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_dou_06_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_dou_06___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_dou_06_one_381 = 1.0f;

__declspec(section ".data") f32 fd_dou_06_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_dou_06_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_dou_06___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_dou_06___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_dou_06_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_dou_06___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_dou_06_one_364 = 1.0f;

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        6, // sfxId
        20000, // directionId
        100000, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        (s32)"dou_05", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        (s32)"door_01", // enterAnimeArg
        (s32)"door_02", // exitAnimeArg
    },
    {
        "s_bero", // hitName
        0, 0, // type..sfxId
        20000, // directionId
        100000, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        (s32)"dou_10", // nextMapName
        "n_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(dou_06_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG5_DOU1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG5_DOU9"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    WAIT_FRAMES(1)
    CALL(evt_map_playanim, STRING("nami"), 1, 0)
    CALL(evt_map_playanim, STRING("moku"), 1, 0)
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 50, 0, 0, STRING("s06_jimen\0\0"), 125, GSWF(5647))
    RETURN
EVT_END()

