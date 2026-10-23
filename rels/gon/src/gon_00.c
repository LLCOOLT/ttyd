#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mobj_jumpstand_blue);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_sub_get_system_flag);

__declspec(section ".data") u64 fd_gon_00_negone_one_374;
__declspec(section ".data") s32 fd_gon_00_neg_one_382[1];
__declspec(section ".data") s32 fd_gon_00___local_PI_383[1];
__declspec(section ".data") s32 fd_gon_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gon_00_one_negone_373;
__declspec(section ".data") s32 fd_gon_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gon_00_one_381[1];
__declspec(section ".data") u64 fd_gon_00_negone_one_360;
__declspec(section ".data") s32 fd_gon_00_neg_one_365[1];
__declspec(section ".data") s32 fd_gon_00___local_PI_366[1];
__declspec(section ".data") s32 fd_gon_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gon_00_one_negone_359;
__declspec(section ".data") s32 fd_gon_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gon_00_one_364[1];
static s32 bero_entry_data[60];
static s32 e3_bero[30];
s32 gon_00_init_evt[77];

__declspec(section ".data") u64 fd_gon_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gon_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_00_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"hei_00", (s32)"a_usiro_bero", 65537, 0, 0, (s32)"e_bero_1",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"gon_01", (s32)"w_bero_1", 65537, 0, 0, (s32)"e_bero_3", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"gon_01", (s32)"w_bero_2", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 e3_bero[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"gon_00", (s32)"w_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(gon_00_init_evt)
    SET_VALUE(GSWF(255), 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    WAIT_FRAMES(1)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_GON1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 160, 60, -90, 0, 0)
    CALL(evt_mobj_recovery_blk, STRING("mobj_recover"), 6, -150, 260, 0, 0, 0)
    CALL(evt_mobj_jumpstand_blue, 0, STRING("mobj_jump"), 230, 0, 0, -90, 0, 0)
    CALL(evt_map_playanim, STRING("hokori\0"), 1, 0)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 4096)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("w_bero"), PTR(e3_bero))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
    END_IF
    RETURN
EVT_END()

