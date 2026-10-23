#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "bom.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);

__declspec(section ".data") u64 fd_bom_04_negone_one_374;
__declspec(section ".data") s32 fd_bom_04_neg_one_382[1];
__declspec(section ".data") s32 fd_bom_04___local_PI_383[1];
__declspec(section ".data") s32 fd_bom_04___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_bom_04_one_negone_373;
__declspec(section ".data") s32 fd_bom_04___local_PIO2_384[1];
__declspec(section ".data") s32 fd_bom_04_one_381[1];
__declspec(section ".data") u64 fd_bom_04_negone_one_360;
__declspec(section ".data") s32 fd_bom_04_neg_one_365[1];
__declspec(section ".data") s32 fd_bom_04___local_PI_366[1];
__declspec(section ".data") s32 fd_bom_04___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_bom_04_one_negone_359;
__declspec(section ".data") s32 fd_bom_04___local_PIO2_367[1];
__declspec(section ".data") s32 fd_bom_04_one_364[1];
static s32 tree_tbl[24];
static __declspec(section ".data") s32 evt_tree[7];
static s32 bero_entry_data[45];
s32 bom_04_init_evt[47];

__declspec(section ".data") u64 fd_bom_04_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_04_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_04___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_04___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_04_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_04___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_04_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_bom_04_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_04_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_04___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_04___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_04_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_04___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_04_one_364[] = {
    1065353216,
};

static s32 tree_tbl[] = {
    3, (s32)"A_ki1", (s32)"S_ki_1", (s32)"S_ha_1", 0, 0, 3, (s32)"A_ki2",
    (s32)"S_ki_2", (s32)"S_ha_2", 0, 0, 3, (s32)"A_ki3", (s32)"S_ki_3", (s32)"S_ha_3",
    0, 0, 7, 0, 0, 0, 0, 0,
};

static __declspec(section ".data") EVT_BEGIN(evt_tree)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero4", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"bom_03", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero4",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"bom_01", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(bom_04_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_bom_snowfall))
    CALL_CHILD(PTR(evt_tree))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_BOM1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_BOM1"))
    CALL(evt_item_entry, STRING("item00"), 125, 450, 5, 110, 16, GSWF(5663), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_badge_gat"), 150, 0, -75, 279, 0, GSWF(3887), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_bom04_hei2\0\0\0"), 2)
    RETURN
EVT_END()

