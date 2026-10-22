#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_kagemario_init_14_text_4DB8);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_breaking_floor);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill_14_data_AF00[];

__declspec(section ".data") u64 fd_jin_11_negone_one_374;
__declspec(section ".data") s32 fd_jin_11_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_11___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_11___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_11_one_negone_373;
__declspec(section ".data") s32 fd_jin_11___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_11_one_381[1];
__declspec(section ".data") u64 fd_jin_11_negone_one_360;
__declspec(section ".data") s32 fd_jin_11_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_11___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_11___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_11_one_negone_359;
__declspec(section ".data") s32 fd_jin_11___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_11_one_364[1];
__declspec(section ".data") s32 jin_11_ana[12];
static __declspec(section ".data") s32 s_close[12];
static __declspec(section ".data") s32 s_open[12];
static s32 bero_entry_data[45];
__declspec(section ".data") s32 evt_yuka[5];
s32 jin_11_init_evt[54];

__declspec(section ".data") u64 fd_jin_11_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_11_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_11___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_11___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_11_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_11___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_11_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_11_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_11_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_11___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_11___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_11_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_11___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_11_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(jin_11_ana)
    SET_VALUE(GSWF(2079), 1)
    CALL(evt_bero_mapchange, STRING("jin_07"), 0)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door10"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door10"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"s_bero", 65538, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"jin_10", (s32)"n_bero", 327685, (s32)s_close, (s32)s_open, (s32)"ana",
    0, 4, 845, 115, 77, -1, 0, 0,
    (s32)jin_11_ana, (s32)"jin_07", 0, 262148, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(evt_yuka)
    SET_VALUE(GSW(0), 208)
    RETURN
EVT_END()

EVT_BEGIN(jin_11_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init_14_text_4DB8)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_14_data_AF00))
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -50, 60, -40, 0, 0)
    CALL(evt_mobj_powerupblk, STRING("pblk00"), 40, 60, -40, 0, GSWF(5551), 0)
    IF_INT_LESS(GSW(0), 208)
        CALL(evt_mobj_breaking_floor, STRING("mobj_bf00\0\0"), 845, 115, 5, 0, PTR(evt_yuka), GSWF(2233))
    END_IF
    RETURN
EVT_END()

