#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 mri_countdown[];
extern s32 mri_puni_init[];
extern s32 puni_disp_info[];

__declspec(section ".data") u64 fd_mri_18_negone_one_374;
__declspec(section ".data") s32 fd_mri_18_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_18___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_18___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_18_one_negone_373;
__declspec(section ".data") s32 fd_mri_18___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_18_one_381[1];
__declspec(section ".data") u64 fd_mri_18_negone_one_360;
__declspec(section ".data") s32 fd_mri_18_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_18___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_18___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_18_one_negone_359;
__declspec(section ".data") s32 fd_mri_18___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_18_one_364[1];
static s32 bero_entry_data[75];
static s32 evt_ueki_04[20];
static s32 ueki_access_data[28];
s32 mri_18_init_evt[105];

__declspec(section ".data") u64 fd_mri_18_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_18_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_18___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_18___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_18_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_18___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_18_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_18_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_18_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_18___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_18___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_18_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_18___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_18_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"dokan1", 131072, 6, 100000, 0, 0, -1, 0,
    10, 0, (s32)"mri_12", (s32)"dokan3", 65537, 0, 0, (s32)"dokan2",
    131072, 9, 100000, 0, 0, -1, 0, 6,
    0, (s32)"mri_16", (s32)"dokan2", 65537, 0, 0, (s32)"dokan3", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan4", 65537, 0, 0, (s32)"dokan4", 131072, 2,
    100000, 0, 0, -1, 0, 10, 0, 0,
    (s32)"dokan3", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

static EVT_BEGIN(evt_ueki_04)
    CALL(evt_item_delete_check, STRING("item_ueki_04"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_ueki_04"), 121, 50, -320, -35, 4, GSWF(2873), 0)
    END_IF
    RETURN
EVT_END()

static s32 ueki_access_data[] = {
    1, (s32)"A_ueki01", (s32)"S_ueki01", 0, 1, (s32)"A_ueki02", (s32)"S_ueki02", 0,
    1, (s32)"A_ueki03", (s32)"S_ueki03", 0, 1, (s32)"A_ueki04", (s32)"S_ueki04", (s32)evt_ueki_04,
    1, (s32)"A_ueki05", (s32)"S_ueki05", 0, 1, (s32)"A_ueki08", (s32)"S_ueki08", 0,
    4, 0, 0, 0,
};

EVT_BEGIN(mri_18_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 18, -89, -319, -1000, -1000, 0, 0)
    CALL(evt_puni_set_hamari, 9, -139, 106, -87, -91, -317, -321)
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
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI4"))
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_GREATER(GSW(0), 113)
        CALL(evt_npc_check_delete, STRING("軍団ザコ"))
        CALL(evt_npc_check_delete, STRING("バリアーン２"))
    END_IF
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02\0"), 1, 0)
    RETURN
EVT_END()

