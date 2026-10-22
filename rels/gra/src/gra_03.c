#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_kagemario_init_11_text_804);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill_11_data_4F98[];

__declspec(section ".data") u64 fd_gra_03_negone_one_374;
__declspec(section ".data") s32 fd_gra_03_neg_one_382[1];
__declspec(section ".data") s32 fd_gra_03___local_PI_383[1];
__declspec(section ".data") s32 fd_gra_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gra_03_one_negone_373;
__declspec(section ".data") s32 fd_gra_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gra_03_one_381[1];
__declspec(section ".data") u64 fd_gra_03_negone_one_360;
__declspec(section ".data") s32 fd_gra_03_neg_one_365[1];
__declspec(section ".data") s32 fd_gra_03___local_PI_366[1];
__declspec(section ".data") s32 fd_gra_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gra_03_one_negone_359;
__declspec(section ".data") s32 fd_gra_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gra_03_one_364[1];
static s32 bero_entry_data[45];
s32 gra_03_init_evt[41];

__declspec(section ".data") u64 fd_gra_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gra_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gra_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gra_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gra_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gra_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gra_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gra_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gra_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gra_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gra_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gra_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gra_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gra_03_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"e_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"gra_02", (s32)"w_bero_2", 65537, 0, 0, (s32)"w_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"gra_04", (s32)"e_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(gra_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_GRA1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_GRA1"))
    CALL(evt_mobj_brick, STRING("blk00"), -120, 60, 90, 0, 3, 0, GSWF(2083))
    CALL(evt_mobj_badgeblk, STRING("blk01\0\0"), 230, 60, -88, 133, 0, GSWF(2084), 0)
    CALL(evt_kagemario_init_11_text_804)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_11_data_4F98))
    RETURN
EVT_END()

