#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_npc_check);
USER_FUNC(evt_npc_set_link);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_gazigazi_entry[];

__declspec(section ".data") u64 fd_dou_12_negone_one_374;
__declspec(section ".data") s32 fd_dou_12_neg_one_382[1];
__declspec(section ".data") s32 fd_dou_12___local_PI_383[1];
__declspec(section ".data") s32 fd_dou_12___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_dou_12_one_negone_373;
__declspec(section ".data") s32 fd_dou_12___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dou_12_one_381[1];
__declspec(section ".data") u64 fd_dou_12_negone_one_360;
__declspec(section ".data") s32 fd_dou_12_neg_one_365[1];
__declspec(section ".data") s32 fd_dou_12___local_PI_366[1];
__declspec(section ".data") s32 fd_dou_12___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_dou_12_one_negone_359;
__declspec(section ".data") s32 fd_dou_12___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dou_12_one_364[1];
static s32 bero_entry_data[75];
static s32 hitDmgRetPoints[20];
s32 dou_12_init_evt[47];

__declspec(section ".data") u64 fd_dou_12_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dou_12_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dou_12___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dou_12___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dou_12_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dou_12___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dou_12_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dou_12_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dou_12_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dou_12___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dou_12___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dou_12_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dou_12___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dou_12_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"dou_02", (s32)"e_bero_1", 65537, 0, 0, (s32)"w_bero_2",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"dou_02", (s32)"e_bero_2", 65537, 0, 0, (s32)"e_bero_1", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"dou_03", (s32)"w_bero_1", 65537, 0, 0, (s32)"e_bero_2", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"dou_03",
    (s32)"w_bero_2", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

static s32 hitDmgRetPoints[] = {
    (s32)"mod_01", 0, -998637568, 0, (s32)"mod_02", 0, -998637568, 0,
    (s32)"mod_03", 0, -998637568, 0, (s32)"mod_04", 0, -998637568, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(dou_12_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG5_DOU1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG5_DOU3"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_map_playanim, STRING("nami"), 1, 0)
    CALL(evt_map_playanim, STRING("moku"), 1, 0)
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_npc_check, STRING("キラー大砲１"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_link, STRING("キラー大砲１"), STRING("キラー大砲２\0\0\0"))
    END_IF
    RETURN
EVT_END()

