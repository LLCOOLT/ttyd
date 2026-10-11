#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_map_entry_airport_harbor);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 mri_countdown[];
extern s32 mri_puni_init[];
extern s32 puni_disp_info[];
extern s32 puni_piders_check[];

__declspec(section ".data") u64 fd_mri_19_negone_one_374;
__declspec(section ".data") s32 fd_mri_19_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_19___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_19___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_19_one_negone_373;
__declspec(section ".data") s32 fd_mri_19___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_19_one_381[1];
__declspec(section ".data") u64 fd_mri_19_negone_one_360;
__declspec(section ".data") s32 fd_mri_19_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_19___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_19___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_19_one_negone_359;
__declspec(section ".data") s32 fd_mri_19___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_19_one_364[1];
static s32 bero_entry_data[75];
static s32 ueki_access_data[28];
static s32 cloud_wind_event[39];
s32 mri_19_init_evt[146];

__declspec(section ".data") u64 fd_mri_19_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_19_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_19___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_19___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_19_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_19___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_19_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_19_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_19_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_19___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_19___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_19_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_19___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_19_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"dokan1", 131072, 2, 100000, 0, 0, -1, 0,
    10, 0, (s32)"mri_05", (s32)"dokan4", 65537, 0, 0, (s32)"dokan2",
    131072, 9, 100000, 0, 0, -1, 0, 6,
    0, (s32)"mri_06", (s32)"dokan1", 65537, 0, 0, (s32)"dokan3", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan4", 65537, 0, 0, (s32)"dokan4", 131072, 6,
    100000, 0, 0, -1, 0, 10, 0, 0,
    (s32)"dokan3", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

static s32 ueki_access_data[] = {
    1, (s32)"A_ueki01", (s32)"S_ueki01", 0, 1, (s32)"A_ueki02", (s32)"S_ueki02", 0,
    1, (s32)"A_ueki03", (s32)"S_ueki03", 0, 1, (s32)"A_ueki04", (s32)"S_ueki04", 0,
    1, (s32)"A_ueki05", (s32)"S_ueki05", 0, 1, (s32)"A_ueki08", (s32)"S_ueki08", 0,
    4, 0, 0, 0,
};

static EVT_BEGIN(cloud_wind_event)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_map_entry_airport_harbor, 0, STRING("hikou"), STRING("a_hi"))
    CALL(evt_map_entry_airport_harbor, 0, STRING("hikou1"), STRING("a_hi1"))
    CALL(evt_hitobj_attr_onoff, 1, 1, STRING("a_hi"), 16)
    SET_VALUE(GSWF(2874), 1)
    RETURN
EVT_END()

EVT_BEGIN(mri_19_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 19, 110, -319, -1000, -1000, 0, 0)
    CALL(evt_puni_set_hamari, 25, -319, 113, 112, 108, -317, -321)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(mri_puni_init))
    SPAWN_EVENT(PTR(puni_disp_info))
    SPAWN_EVENT(PTR(mri_countdown))
    SWITCH(GSW(0))
        CASE_BETWEEN(109, 110)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI1"))
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_powerupblk, STRING("pblk00"), -360, -175, 25, 0, GSWF(5545), 0)
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    IF_INT_EQUAL(GSWF(2874), 0)
        CALL(evt_cloud_init)
        CALL(evt_cloud_ent, 0, STRING("S_f2_isk"), STRING("A_f2_isk"), PTR(cloud_wind_event))
        CALL(evt_hitobj_attr_onoff, 1, 0, STRING("a_hi"), 16)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_f2_isk"), 1)
        CALL(evt_hitobj_onoff, STRING("A_f2_isk"), 1, 0)
        CALL(evt_map_entry_airport_harbor, 0, STRING("hikou"), STRING("a_hi"))
        CALL(evt_map_entry_airport_harbor, 0, STRING("hikou1"), STRING("a_hi1"))
    END_IF
    SPAWN_EVENT(PTR(puni_piders_check))
    RETURN
EVT_END()

