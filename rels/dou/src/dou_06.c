#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_dou_06_negone_one_374;
__declspec(section ".data") s32 fd_dou_06_neg_one_382[1];
__declspec(section ".data") s32 fd_dou_06___local_PI_383[1];
__declspec(section ".data") s32 fd_dou_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_dou_06_one_negone_373;
__declspec(section ".data") s32 fd_dou_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dou_06_one_381[1];
__declspec(section ".data") u64 fd_dou_06_negone_one_360;
__declspec(section ".data") s32 fd_dou_06_neg_one_365[1];
__declspec(section ".data") s32 fd_dou_06___local_PI_366[1];
__declspec(section ".data") s32 fd_dou_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_dou_06_one_negone_359;
__declspec(section ".data") s32 fd_dou_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dou_06_one_364[1];
static s32 bero_entry_data[45];
s32 dou_06_init_evt[41];

__declspec(section ".data") u64 fd_dou_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dou_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dou_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dou_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dou_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dou_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dou_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dou_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dou_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dou_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dou_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dou_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dou_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dou_06_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"dou_05", (s32)"e_bero", 65537, (s32)"door_01", (s32)"door_02", (s32)"s_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"dou_10", (s32)"n_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
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
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 50, 0, 0, STRING("s06_jimen"), 125, GSWF(5647))
    RETURN
EVT_END()

