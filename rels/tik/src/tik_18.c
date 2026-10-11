#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_map_entry_airport_harbor);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_gazigazi_entry[];

__declspec(section ".data") u64 fd_tik_18_negone_one_374;
__declspec(section ".data") s32 fd_tik_18_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_18___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_18___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_18_one_negone_373;
__declspec(section ".data") s32 fd_tik_18___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_18_one_381[1];
__declspec(section ".data") u64 fd_tik_18_negone_one_360;
__declspec(section ".data") s32 fd_tik_18_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_18___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_18___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_18_one_negone_359;
__declspec(section ".data") s32 fd_tik_18___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_18_one_364[1];
static s32 bero_entry_data[75];
__declspec(section ".data") s32 tik_18_cloud_evt[5];
static s32 hitDmgRetPoints[52];
s32 tik_18_init_evt[96];

__declspec(section ".data") u64 fd_tik_18_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_18_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_18___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_18___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_18_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_18___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_18_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_18_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_18_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_18___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_18___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_18_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_18___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_18_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"dokan_1", 131072, 9, 100000, 0, 0, -1, 0,
    6, 0, (s32)"tik_06", (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_2",
    131072, 2, 100000, 0, 0, -1, 0, 10,
    0, (s32)"tik_07", (s32)"dokan_2", 65537, 0, 0, (s32)"e_bero_1", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"tik_17", (s32)"w_bero_1", 65537, 0, 0, (s32)"e_bero_2", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"tik_17",
    (s32)"w_bero_2", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(tik_18_cloud_evt)
    SET_VALUE(GSWF(1351), 1)
    RETURN
EVT_END()

static s32 hitDmgRetPoints[] = {
    (s32)"mod_1", 0, -998637568, 0, (s32)"mod_2", 0, -998637568, 0,
    (s32)"mod_3", 0, -998637568, 0, (s32)"mod_4", 0, -998637568, 0,
    (s32)"mod_5", 0, -998637568, 0, (s32)"mod_6", 0, -998637568, 0,
    (s32)"mod_7", 0, -998637568, 0, (s32)"mod_8", 0, -998637568, 0,
    (s32)"mod_9", 0, -998637568, 0, (s32)"mod_10", 0, -998637568, 0,
    (s32)"mod_11", 0, -998637568, 0, (s32)"mod_12", 0, -998637568, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(tik_18_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK7"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_map_playanim, STRING("anm_mizu"), 1, 0)
    IF_INT_EQUAL(GSWF(1351), 0)
        CALL(evt_cloud_init)
        CALL(evt_cloud_ent, 0, STRING("s_win_1"), STRING("a_win_1"), PTR(tik_18_cloud_evt))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_win_1"), 1)
        CALL(evt_hitobj_onoff, STRING("a_win_1"), 1, 0)
    END_IF
    IF_INT_LESS(GSW(0), 261)
        CALL(evt_npc_check_delete, STRING("カメック"))
        CALL(evt_npc_check_delete, STRING("トゲノコ"))
        ELSE
        CALL(evt_npc_check_delete, STRING("ハンニャー１"))
        CALL(evt_npc_check_delete, STRING("ハンニャー２"))
    END_IF
    CALL(evt_map_entry_airport_harbor, 1, STRING("S_Ship_Change_01"), STRING("ue"))
    CALL(evt_mobj_badgeblk, STRING("mobj_01"), 110, 0, -38, 157, 0, GSWF(1365), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_02"), 310, 0, -38, 158, 0, GSWF(1366), 0)
    RETURN
EVT_END()

