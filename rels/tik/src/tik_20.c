#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_entry_airport_harbor);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_gazigazi_entry[];
extern s32 moving_floor[];

__declspec(section ".data") u64 fd_tik_20_negone_one_374;
__declspec(section ".data") s32 fd_tik_20_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_20___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_20___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_20_one_negone_373;
__declspec(section ".data") s32 fd_tik_20___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_20_one_381[1];
__declspec(section ".data") u64 fd_tik_20_negone_one_360;
__declspec(section ".data") s32 fd_tik_20_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_20___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_20___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_20_one_negone_359;
__declspec(section ".data") s32 fd_tik_20___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_20_one_364[1];
static s32 bero_entry_data[30];
static s32 hitDmgRetPoints[28];
s32 tik_20_init_evt[104];

__declspec(section ".data") u64 fd_tik_20_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_20_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_20___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_20___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_20_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_20___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_20_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_20_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_20_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_20___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_20___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_20_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_20___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_20_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tik_15", (s32)"e_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static s32 hitDmgRetPoints[] = {
    (s32)"mod_1", 0, -998637568, 0, (s32)"mod_2", 0, -998637568, 0,
    (s32)"mod_3", 0, -998637568, 0, (s32)"mod_4", 0, -998637568, 0,
    (s32)"mod_5", 0, -998637568, 0, (s32)"ue", 0, -998637568, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(tik_20_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK7"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_map_playanim, STRING("anm_mizu"), 1, 0)
    CALL(evt_map_entry_airport_harbor, 1, STRING("S_Ship_Change_01"), STRING("ue"))
    SET_VALUE(LW(0), STRING("dai_3"))
    SET_VALUE(LW(1), STRING("a_dai_3"))
    SET_VALUE(LW(2), -10)
    SET_VALUE(LW(3), 30)
    SET_VALUE(LW(4), 900)
    SET_VALUE(LW(5), 500)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(12), 0)
    SPAWN_EVENT(PTR(moving_floor))
    CALL(evt_item_entry, STRING("item_01"), 274, 180, 100, -125, 16, GSWF(1367), 0)
    CALL(evt_mobj_powerupblk, STRING("pblk01"), -50, 60, -75, 0, GSWF(5535), 0)
    CALL(evt_mobj_powerupblk, STRING("pblk02"), 0, 100, -25, 0, GSWF(5536), 0)
    CALL(evt_mobj_powerupblk, STRING("pblk03\0"), 50, 60, -75, 0, GSWF(5537), 0)
    RETURN
EVT_END()

