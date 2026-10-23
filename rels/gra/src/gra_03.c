#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "gra.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);

__declspec(section ".data") f32 fd_gra_03_negone_one_374[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_gra_03_neg_one_382;
__declspec(section ".data") f32 fd_gra_03___local_PI_383;
__declspec(section ".data") f32 fd_gra_03___local_3PIO2_385;
__declspec(section ".data") f32 fd_gra_03_one_negone_373[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_gra_03___local_PIO2_384;
__declspec(section ".data") f32 fd_gra_03_one_381;
__declspec(section ".data") f32 fd_gra_03_negone_one_360[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_gra_03_neg_one_365;
__declspec(section ".data") f32 fd_gra_03___local_PI_366;
__declspec(section ".data") f32 fd_gra_03___local_3PIO2_368;
__declspec(section ".data") f32 fd_gra_03_one_negone_359[2] __attribute__((aligned(8)));
__declspec(section ".data") f32 fd_gra_03___local_PIO2_367;
__declspec(section ".data") f32 fd_gra_03_one_364;
static BeroEntry bero_entry_data[3];
s32 gra_03_init_evt[41];

__declspec(section ".data") f32 fd_gra_03_negone_one_374[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_gra_03_neg_one_382 = -1.0f;

__declspec(section ".data") f32 fd_gra_03___local_PI_383 = 3.1415927f;

__declspec(section ".data") f32 fd_gra_03___local_3PIO2_385 = 4.712389f;

__declspec(section ".data") f32 fd_gra_03_one_negone_373[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_gra_03___local_PIO2_384 = 1.5707964f;

__declspec(section ".data") f32 fd_gra_03_one_381 = 1.0f;

__declspec(section ".data") f32 fd_gra_03_negone_one_360[2] __attribute__((aligned(8))) = {-1.0f, 1.0f};

__declspec(section ".data") f32 fd_gra_03_neg_one_365 = -1.0f;

__declspec(section ".data") f32 fd_gra_03___local_PI_366 = 3.1415927f;

__declspec(section ".data") f32 fd_gra_03___local_3PIO2_368 = 4.712389f;

__declspec(section ".data") f32 fd_gra_03_one_negone_359[2] __attribute__((aligned(8))) = {1.0f, -1.0f};

__declspec(section ".data") f32 fd_gra_03___local_PIO2_367 = 1.5707964f;

__declspec(section ".data") f32 fd_gra_03_one_364 = 1.0f;

static BeroEntry bero_entry_data[] = {
    {
        "e_bero", // hitName
        0, 0, // type..sfxId
        20000, // directionId
        100000, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        (s32)"gra_02", // nextMapName
        "w_bero_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        20000, // directionId
        100000, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        (s32)"gra_04", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(gra_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_GRA1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_GRA1"))
    CALL(evt_mobj_brick, STRING("blk00"), -120, 60, 90, 0, 3, 0, GSWF(2083))
    CALL(evt_mobj_badgeblk, STRING("blk01\0\0"), 230, 60, -88, 133, 0, GSWF(2084), 0)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    RETURN
EVT_END()

