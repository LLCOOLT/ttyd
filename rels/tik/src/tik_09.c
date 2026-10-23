#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);

__declspec(section ".data") u64 fd_tik_09_negone_one_374;
__declspec(section ".data") s32 fd_tik_09_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_09___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_09___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_09_one_negone_373;
__declspec(section ".data") s32 fd_tik_09___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_09_one_381[1];
__declspec(section ".data") u64 fd_tik_09_negone_one_360;
__declspec(section ".data") s32 fd_tik_09_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_09___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_09___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_09_one_negone_359;
__declspec(section ".data") s32 fd_tik_09___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_09_one_364[1];
static s32 bero_entry_data[45];
s32 evt_tik09_dokan[51];
s32 tik_09_init_evt[36];

__declspec(section ".data") u64 fd_tik_09_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_09_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_09___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_09___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_09_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_09___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_09_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_09_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_09_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_09___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_09___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_09_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_09___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_09_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"dokan_1", 131072, 9, 100000, 0, 0, -1, 0,
    6, 0, (s32)"tik_10", (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_2",
    131072, 8, 100000, 0, 0, -1, 0, 6,
    0, (s32)"tik_06", (s32)"dokan_1", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_tik09_dokan)
    CALL(evt_hit_bind_mapobj, STRING("a_dokan_1"), STRING("dokan_1_s"))
    CALL(evt_mapobj_trans, 0, STRING("dokan_1_s"), 0, 0, 0)
    CALL(evt_hit_bind_update, STRING("a_dokan_1"))
    WAIT_MS(1500)
    CALL(evt_sub_intpl_init, 13, 0, 30, 100)
    LOOP(100)
        CALL(evt_sub_intpl_get_value)
        CALL(evt_mapobj_trans, 0, STRING("dokan_1_s"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_1"))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_trans, 0, STRING("dokan_1_s"), 0, 30, 0)
    CALL(evt_hit_bind_update, STRING("a_dokan_1"))
    RETURN
EVT_END()

EVT_BEGIN(tik_09_init_evt)
    CALL(evt_hit_bind_mapobj, STRING("a_dokan_1"), STRING("dokan_1_s"))
    CALL(evt_mapobj_trans, 1, STRING("dokan_1_s"), 0, 30, 0)
    CALL(evt_hit_bind_update, STRING("a_dokan_1"))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1\0\0"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT(PTR(evt_tik09_dokan))
    RETURN
EVT_END()

