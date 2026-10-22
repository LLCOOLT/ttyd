#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_map_set_blend);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
extern s32 evt_bero_info_run[];
extern s32 evt_win_door_close[];
extern s32 evt_win_door_open[];

__declspec(section ".data") u64 fd_win_05_negone_one_374;
__declspec(section ".data") s32 fd_win_05_neg_one_382[1];
__declspec(section ".data") s32 fd_win_05___local_PI_383[1];
__declspec(section ".data") s32 fd_win_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_win_05_one_negone_373;
__declspec(section ".data") s32 fd_win_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_win_05_one_381[1];
__declspec(section ".data") u64 fd_win_05_negone_one_360;
__declspec(section ".data") s32 fd_win_05_neg_one_365[1];
__declspec(section ".data") s32 fd_win_05___local_PI_366[1];
__declspec(section ".data") s32 fd_win_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_win_05_one_negone_359;
__declspec(section ".data") s32 fd_win_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_win_05_one_364[1];
__declspec(section ".data") s32 win_05_door_open[10];
__declspec(section ".data") s32 win_05_door_close[10];
static s32 bero_entry_data[30];
static s32 item_get00[34];
static s32 cloud_toujou[126];
s32 win_05_init_evt[42];

__declspec(section ".data") u64 fd_win_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_win_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_win_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_win_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_win_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_win_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_win_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_win_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_win_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_win_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_win_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_win_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_win_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_win_05_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(win_05_door_open)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SPAWN_EVENT(PTR(evt_win_door_open))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(win_05_door_close)
    SET_VALUE(LW(8), STRING("S_doa_e_l"))
    SET_VALUE(LW(9), STRING("S_doa_e_r"))
    SPAWN_EVENT(PTR(evt_win_door_close))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65536, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"win_04", (s32)"e_bero", 262148, (s32)win_05_door_close, (s32)win_05_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(item_get00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), 259, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 258)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(cloud_toujou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("クラウダ"), 104, 13, 110)
    CALL(evt_cam3d_evt_set, 89, 95, 242, 43, 52, 0, 0, 11)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    CALL(evt_npc_wait_pera, STRING("クラウダ"))
    CALL(evt_seq_wait, 2)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    CALL(evt_npc_get_position, STRING("クラウダ"), LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_00_04"), 0, STRING("クラウダ"))
    WAIT_MS(1000)
    SET_VALUE(GSW(0), 77)
    CALL(evt_fade_set_mapchange_type, 0, 10, 100, 9, 100)
    CALL(evt_bero_mapchange, STRING("win_03"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(win_05_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_itembox, STRING("mobj_box00"), -45, 0, -75, 0, 0, PTR(item_get00), GSWF(2684))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 64, 0, 118, STRING("S_yukaA"), 125, GSWF(5611))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_WIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG2_WIN2\0\0"))
    IF_INT_EQUAL(GSW(0), 76)
        SPAWN_EVENT(PTR(cloud_toujou))
    END_IF
    RETURN
EVT_END()

