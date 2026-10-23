#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_sub_get_system_flag);

__declspec(section ".data") u64 fd_hei_13_negone_one_374;
__declspec(section ".data") s32 fd_hei_13_neg_one_382[1];
__declspec(section ".data") s32 fd_hei_13___local_PI_383[1];
__declspec(section ".data") s32 fd_hei_13___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_13_one_negone_373;
__declspec(section ".data") s32 fd_hei_13___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_13_one_381[1];
__declspec(section ".data") u64 fd_hei_13_negone_one_360;
__declspec(section ".data") s32 fd_hei_13_neg_one_365[1];
__declspec(section ".data") s32 fd_hei_13___local_PI_366[1];
__declspec(section ".data") s32 fd_hei_13___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_13_one_negone_359;
__declspec(section ".data") s32 fd_hei_13___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_13_one_364[1];
static s32 bero_entry_data[75];
static __declspec(section ".data") s32 ki_data[12];
s32 evt_anm_kan[59];
s32 hei_13_init_evt[110];

__declspec(section ".data") u64 fd_hei_13_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_13_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_13___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_13___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_13_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_13___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_13_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_13_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_13_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_13___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_13___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_13_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_13___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_13_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"hei_00", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"hei_01", (s32)"w_bero", 65537, 0, 0, (s32)"a_dokan_1", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"a_dokan_2", 65537, 0, 0, (s32)"a_dokan_2", 131072, 9,
    100000, 0, 0, -1, 0, 6, 0, 0,
    (s32)"a_dokan_1", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

static __declspec(section ".data") s32 ki_data[] = {
    0, (s32)"a_ki_1", (s32)"miki_", (s32)"ha_temae", (s32)"ha_usiro", 0, 7, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(evt_anm_kan)
    IF_INT_EQUAL(GF(0), 1)
        GOTO(99)
    END_IF
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(GSW(301), 10)
            SET_VALUE(GF(0), 1)
            WAIT_MS(200)
            CALL(evt_item_entry, STRING("item_tukushi"), 175, 565, 15, -65, 5, -1, 0)
            ELSE
            ADD(GSW(301), 1)
            IF_INT_EQUAL(GSW(301), 10)
                SET_VALUE(GF(0), 1)
                WAIT_MS(200)
                CALL(evt_item_entry, STRING("item_tukushi"), 175, 565, 15, -65, 5, -1, 0)
            END_IF
        END_IF
    END_INLINE_EVENT
    LABEL(99)
    CALL(evt_map_playanim, STRING("anm_kan_1"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(hei_13_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SET_VALUE(GF(0), 0)
    SET_VALUE(GSW(301), 0)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_mobj_badgeblk, STRING("m"), -320, 60, -100, 299, 0, GSWF(1797), 1)
    SET_VALUE(LSWF(3), 0)
    CALL(evt_mobj_brick, STRING("mm"), 325, 175, -100, 0, 0, 0, LSWF(3))
    IF_INT_EQUAL(LSWF(3), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("mm"), 2)
    END_IF
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_CLEAR(LW(0), 4096)
        CALL(evt_item_entry, STRING("i"), 292, 325, 200, -100, 16, GSWF(1798), 0)
    END_IF
    CALL(evt_mobj_brick, STRING("10m"), 325, 60, -100, 0, 3, 0, GSWF(1799))
    SET_VALUE(LW(0), PTR(ki_data))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    CALL(evt_map_playanim, STRING("anm_mugi"), 1, 0)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG1_HEI1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_HEI1"))
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_CLEAR(LW(0), 4096)
        CALL(evt_run_case_evt, 13, 1, STRING("a_kan_5"), 0, PTR(evt_anm_kan), 0)
    END_IF
    RETURN
EVT_END()

