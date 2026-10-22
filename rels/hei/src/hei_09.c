#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/mapdrv.h"
#include "driver/envdrv.h"

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
void hei_test_water_tev(MapTevCallbackInfo* info);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_hei_09_negone_one_374;
__declspec(section ".data") s32 fd_hei_09_neg_one_382[1];
__declspec(section ".data") s32 fd_hei_09___local_PI_383[1];
__declspec(section ".data") s32 fd_hei_09___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_09_one_negone_373;
__declspec(section ".data") s32 fd_hei_09___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_09_one_381[1];
__declspec(section ".data") u64 fd_hei_09_negone_one_360;
__declspec(section ".data") s32 fd_hei_09_neg_one_365[1];
__declspec(section ".data") s32 fd_hei_09___local_PI_366[1];
__declspec(section ".data") s32 fd_hei_09___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_09_one_negone_359;
__declspec(section ".data") s32 fd_hei_09___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_09_one_364[1];
static s32 bero_entry_data[45];
s32 hei_09_init_evt[44];

__declspec(section ".data") u64 fd_hei_09_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_09_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_09___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_09___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_09_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_09___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_09_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_09_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_09_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_09___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_09___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_09_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_09___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_09_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"hei_08", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"hei_10", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(hei_09_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG1_TORIDE1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_HEI3"))
    CALL(evt_snd_set_rev_mode, 1)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_map_playanim, STRING("mizu\0\0\0"), 1, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(hei_test_water_tev))
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("mizu\0\0\0"), 16777216)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("mizu\0\0\0"), 256)
    RETURN
EVT_END()

void hei_test_water_tev(MapTevCallbackInfo* info) {
    envSetWater(info);
}
