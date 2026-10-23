#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);

__declspec(section ".data") u64 fd_hei_06_negone_one_374;
__declspec(section ".data") s32 fd_hei_06_neg_one_382[1];
__declspec(section ".data") s32 fd_hei_06___local_PI_383[1];
__declspec(section ".data") s32 fd_hei_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_06_one_negone_373;
__declspec(section ".data") s32 fd_hei_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_06_one_381[1];
__declspec(section ".data") u64 fd_hei_06_negone_one_360;
__declspec(section ".data") s32 fd_hei_06_neg_one_365[1];
__declspec(section ".data") s32 fd_hei_06___local_PI_366[1];
__declspec(section ".data") s32 fd_hei_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_06_one_negone_359;
__declspec(section ".data") s32 fd_hei_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_06_one_364[1];
static s32 bero_entry_data[45];
static s32 ki_data[30];
s32 evt_kusa_8[20];
static s32 kusa_data[40];
s32 hei_06_init_evt[63];

__declspec(section ".data") u64 fd_hei_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_06_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"hei_05", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"hei_07", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 ki_data[] = {
    0, (s32)"a_ki_1", (s32)"miki__1", (s32)"ha_temae_1", (s32)"ha_usiro_1", 0, 0, (s32)"a_ki_2",
    (s32)"miki__2", (s32)"ha_temae_2", (s32)"ha_usiro_2", 0, 0, (s32)"a_ki_3", (s32)"miki__3", (s32)"ha_temae_3",
    (s32)"ha_usiro_3", 0, 0, (s32)"a_ki_4", (s32)"miki__4", (s32)"ha_temae_4", (s32)"ha_usiro_4", 0,
    7, 0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_kusa_8)
    CALL(evt_item_delete_check, STRING("item_kusa_8"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_8"), 121, 200, 75, 60, 4, GSWF(1794), 0)
    END_IF
    RETURN
EVT_END()

static s32 kusa_data[] = {
    0, (s32)"a_kusa_2", (s32)"kusa_2", 0, 0, (s32)"a_kusa_3", (s32)"kusa_3", 0,
    0, (s32)"a_kusa_4", (s32)"kusa_4", 0, 0, (s32)"a_kusa_5", (s32)"kusa_5", 0,
    0, (s32)"a_kusa_6", (s32)"kusa_6", 0, 0, (s32)"a_kusa_8", (s32)"kusa_8", (s32)evt_kusa_8,
    0, (s32)"a_kusa_12", (s32)"kusa_12", 0, 0, (s32)"a_kusa_13", (s32)"kusa_13", 0,
    0, (s32)"a_kusa_14", (s32)"kusa_14", 0, 4, 0, 0, 0,
};

EVT_BEGIN(hei_06_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG1_HEI1"))
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_HEI1"))
    CALL(evt_npc_change_fbat_mode, 1)
    SET_VALUE(LW(0), PTR(ki_data))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    SET_VALUE(LW(0), PTR(kusa_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    CALL(evt_mobj_recovery_blk, STRING("mobj_recover"), 5, 375, 160, -75, 0, 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_hatenablk"), -25, 110, -75, 132, 0, GSWF(1795), 0)
    CALL(evt_item_entry, STRING("item_00"), 164, 50, 50, 105, 16, GSWF(1806), 0)
    RETURN
EVT_END()

