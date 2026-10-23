#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "mri.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_set_position);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_breaking_floor);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_puni_all_fall_check);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_target_flag_onoff);
USER_FUNC(evt_target_set_position);

__declspec(section ".data") u64 fd_mri_12_negone_one_374;
__declspec(section ".data") s32 fd_mri_12_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_12___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_12___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_12_one_negone_373;
__declspec(section ".data") s32 fd_mri_12___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_12_one_381[1];
__declspec(section ".data") u64 fd_mri_12_negone_one_360;
__declspec(section ".data") s32 fd_mri_12_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_12___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_12___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_12_one_negone_359;
__declspec(section ".data") s32 fd_mri_12___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_12_one_364[1];
static s32 bero_entry_data[90];
static s32 punipuni_ball00_init[32];
static s32 punipuni_ball00[51];
static s32 evt_f1_ueki_01[20];
static s32 ueki_access_data[32];
static __declspec(section ".data") s32 breakyuka_init[11];
static __declspec(section ".data") s32 breakyuka_main[9];
s32 mri_12_init_evt[140];

__declspec(section ".data") u64 fd_mri_12_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_12_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_12___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_12___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_12_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_12___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_12_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_12_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_12_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_12___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_12___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_12_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_12___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_12_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"e_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"mri_11", (s32)"w_bero", 65537, 0, 0, (s32)"e_bero_2",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"mri_17", (s32)"w_bero", 65537, 0, 0, (s32)"dokan1", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan2", 65537, 0, 0, (s32)"dokan2", 131072, 6,
    100000, 0, 0, -1, 0, 10, 0, 0,
    (s32)"dokan1", 65537, 0, 0, (s32)"dokan3", 131072, 9, 100000,
    0, 0, -1, 0, 6, 0, (s32)"mri_18", (s32)"dokan1",
    65537, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

static EVT_BEGIN(punipuni_ball00_init)
    CALL_CHILD(PTR(mri_punipuni_setup))
    IF_INT_EQUAL(GSWF(2859), 1)
        CALL(evt_item_set_position, LW(10), 5, 30, -95)
        CALL(evt_target_flag_onoff, LW(11), 0, 3)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_sui_hikari"), 1)
    END_IF
    CALL(evt_target_set_position, LW(11), 5, 0, -65)
    RETURN
EVT_END()

static EVT_BEGIN(punipuni_ball00)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_EQUAL(GSWF(2859), 0)
        CALL_CHILD(PTR(mri_punipuni_itemselect))
        IF_INT_EQUAL(LW(1), 0)
            GOTO(100)
        END_IF
        SET_VALUE(GSWF(2859), 1)
        CALL(evt_item_set_position, LW(10), 5, 30, -95)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_sui_hikari"), 1)
        CALL_CHILD(PTR(mri_punipuni_itemset))
        ELSE
        SET_VALUE(GSWF(2859), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_sui_hikari"), 1)
        CALL_CHILD(PTR(mri_punipuni_itemremove))
    END_IF
    LABEL(100)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_f1_ueki_01)
    CALL(evt_item_delete_check, STRING("item_ueki_01"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_ueki_01"), 121, -190, -309, 65, 4, GSWF(2860), 0)
    END_IF
    RETURN
EVT_END()

static s32 ueki_access_data[] = {
    1, (s32)"A_f1_ueki01", (s32)"S_f1_ueki01", (s32)evt_f1_ueki_01, 1, (s32)"A_f1_ueki02", (s32)"S_f1_ueki02", 0,
    1, (s32)"A_f2_ueki01", (s32)"S_f2_ueki01", 0, 1, (s32)"A_f2_ueki02", (s32)"S_f2_ueki02", 0,
    1, (s32)"A_f2_ueki03", (s32)"S_f2_ueki03", 0, 1, (s32)"A_f2_ueki04", (s32)"S_f2_ueki04", 0,
    1, (s32)"A_f2_ueki05", (s32)"S_f2_ueki05", 0, 4, 0, 0, 0,
};

static __declspec(section ".data") EVT_BEGIN(breakyuka_init)
    IF_INT_EQUAL(GSWF(2858), 0)
        CALL(evt_hitobj_onoff, STRING("A_f2_rak_01"), 1, 0)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(breakyuka_main)
    CALL(evt_hitobj_onoff, STRING("A_f2_rak_01"), 1, 1)
    CALL(evt_puni_all_fall_check)
    RETURN
EVT_END()

EVT_BEGIN(mri_12_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 12, 0, -250, -310, -1000, 3, 0)
    CALL(evt_puni_set_hamari, 0, 0, 0, 6, -6, -248, -312)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(mri_puni_init))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT(PTR(puni_disp_info))
    SPAWN_EVENT(PTR(mri_countdown))
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(109, 110)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI9"))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI1"))
    END_SWITCH
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    CALL(evt_map_playanim, STRING("sui_hikari"), 1, 0)
    SPAWN_EVENT(PTR(breakyuka_init))
    CALL(evt_mobj_breaking_floor, STRING("mobj_bf00"), -45, 0, -64, 1, PTR(breakyuka_main), GSWF(2858))
    SET_VALUE(LW(10), STRING("punipuni"))
    SET_VALUE(LW(11), 0)
    SPAWN_EVENT(PTR(punipuni_ball00_init))
    CALL(evt_run_case_evt, 9, 1, STRING("A_dai_mae"), 0, PTR(punipuni_ball00), 0)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_item_entry, STRING("item_00"), 125, -175, -310, -85, 16, GSWF(5615), 0)
    RETURN
EVT_END()

