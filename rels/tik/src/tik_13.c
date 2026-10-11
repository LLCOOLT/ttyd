#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_tik_13_negone_one_374;
__declspec(section ".data") s32 fd_tik_13_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_13___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_13___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_13_one_negone_373;
__declspec(section ".data") s32 fd_tik_13___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_13_one_381[1];
__declspec(section ".data") u64 fd_tik_13_negone_one_360;
__declspec(section ".data") s32 fd_tik_13_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_13___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_13___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_13_one_negone_359;
__declspec(section ".data") s32 fd_tik_13___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_13_one_364[1];
static s32 bero_entry_data[30];
s32 tik_13_init_evt[60];

__declspec(section ".data") u64 fd_tik_13_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_13_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_13___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_13___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_13_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_13___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_13_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_13_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_13_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_13___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_13___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_13_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_13___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_13_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"e_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tik_02", (s32)"w_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(tik_13_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK6"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_map_playanim, STRING("anm_mizu"), 0, 0)
            CALL(evt_map_checkanim, STRING("anm_mizu"), LW(0), LW(1))
            WAIT_MS(LW(1))
            CALL(evt_mapobj_get_position, STRING("Tshatu"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG0_AMB_WATERDROP2"), LW(0), LW(1), LW(2), 0)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_item_entry, STRING("item_00"), 125, -30, 52, -70, 16, GSWF(5596), 0)
    RETURN
EVT_END()

