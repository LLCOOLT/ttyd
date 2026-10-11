#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_tik_14_negone_one_374;
__declspec(section ".data") s32 fd_tik_14_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_14___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_14___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_14_one_negone_373;
__declspec(section ".data") s32 fd_tik_14___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_14_one_381[1];
__declspec(section ".data") u64 fd_tik_14_negone_one_360;
__declspec(section ".data") s32 fd_tik_14_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_14___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_14___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_14_one_negone_359;
__declspec(section ".data") s32 fd_tik_14___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_14_one_364[1];
static s32 bero_entry_data[45];
static s32 item_get00[34];
s32 tik_14_init_evt[30];

__declspec(section ".data") u64 fd_tik_14_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_14_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_14___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_14___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_14_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_14___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_14_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_14_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_14_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_14___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_14___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_14_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_14___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_14_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"dokan_1", 131072, 2, 100000, 0, 0, -1, 0,
    10, 0, (s32)"tik_06", (s32)"dokan_3", 65537, 0, 0, (s32)"dokan_2",
    131072, 8, 100000, 0, 0, -1, 0, 6,
    0, (s32)"tik_06", (s32)"dokan_3", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(item_get00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), 148, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 2)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(tik_14_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 0, 25, -110, 0, 0, PTR(item_get00), GSWF(1361))
    RETURN
EVT_END()

