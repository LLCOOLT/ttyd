#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 evt_sub_tree_access_entry[];

__declspec(section ".data") u64 fd_hei_04_negone_one_374;
__declspec(section ".data") s32 fd_hei_04_neg_one_382[1];
__declspec(section ".data") s32 fd_hei_04___local_PI_383[1];
__declspec(section ".data") s32 fd_hei_04___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_04_one_negone_373;
__declspec(section ".data") s32 fd_hei_04___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_04_one_381[1];
__declspec(section ".data") u64 fd_hei_04_negone_one_360;
__declspec(section ".data") s32 fd_hei_04_neg_one_365[1];
__declspec(section ".data") s32 fd_hei_04___local_PI_366[1];
__declspec(section ".data") s32 fd_hei_04___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_04_one_negone_359;
__declspec(section ".data") s32 fd_hei_04___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_04_one_364[1];
static s32 bero_entry_data[45];
static s32 evt_ki_3[20];
static s32 ki_data[24];
s32 evt_kusa_11[20];
s32 evt_kusa_12[20];
static s32 kusa_data[48];
s32 hei_04_init_evt[40];

__declspec(section ".data") u64 fd_hei_04_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_04_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_04___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_04___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_04_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_04___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_04_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_04_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_04_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_04___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_04___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_04_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_04___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_04_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"hei_03", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"hei_05", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_ki_3)
    CALL(evt_item_delete_check, STRING("item_ki_3"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_ki_3"), 121, 17, 90, -122, 14, GSWF(1791), 0)
    END_IF
    RETURN
EVT_END()

static s32 ki_data[] = {
    0, (s32)"a_ki_1", (s32)"miki_1", (s32)"ha_temae", (s32)"ha_usiro", 0, 0, (s32)"a_ki_2",
    (s32)"miki_2", (s32)"ha_temae_2", (s32)"ha_usiro_2", 0, 0, (s32)"a_ki_3", (s32)"miki_3", (s32)"ha_temae_3",
    (s32)"ha_usiro_3", (s32)evt_ki_3, 7, 0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_kusa_11)
    CALL(evt_item_delete_check, STRING("item_kusa_11"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_11"), 121, 364, 75, -95, 4, GSWF(1790), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_kusa_12)
    CALL(evt_item_delete_check, STRING("item_kusa_12"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_12"), 139, 320, 75, -55, 4, GSWF(1801), 0)
    END_IF
    RETURN
EVT_END()

static s32 kusa_data[] = {
    0, (s32)"a_kusa_1", (s32)"kusa_1", 0, 0, (s32)"a_kusa_2", (s32)"kusa_2", 0,
    0, (s32)"a_kusa_3", (s32)"kusa_3", 0, 0, (s32)"a_kusa_4", (s32)"kusa_4", 0,
    0, (s32)"a_kisa_5", (s32)"kusa_5", 0, 0, (s32)"a_kusa_6", (s32)"kusa_6", 0,
    0, (s32)"a_kusa_7", (s32)"kusa_7", 0, 0, (s32)"a_kusa_9", (s32)"kusa_9", 0,
    0, (s32)"a_kusa_10", (s32)"kusa_10", 0, 0, (s32)"a_kusa_11", (s32)"kusa_11", (s32)evt_kusa_11,
    0, (s32)"a_kusa_12", (s32)"kusa_12", (s32)evt_kusa_12, 4, 0, 0, 0,
};

EVT_BEGIN(hei_04_init_evt)
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
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("group1\0"), 2)
    RETURN
EVT_END()

