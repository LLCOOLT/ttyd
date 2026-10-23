#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam_ctrl_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mobj_signboard);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_insert);
USER_FUNC(evt_npc_add_dirdist);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_start_for_event);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_stop_for_event);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_sub_get_dir);
USER_FUNC(evt_sub_save_playtime);

__declspec(section ".data") u64 fd_tik_06_negone_one_374;
__declspec(section ".data") s32 fd_tik_06_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_06___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_06_one_negone_373;
__declspec(section ".data") s32 fd_tik_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_06_one_381[1];
__declspec(section ".data") u64 fd_tik_06_negone_one_360;
__declspec(section ".data") s32 fd_tik_06_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_06___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_06_one_negone_359;
__declspec(section ".data") s32 fd_tik_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_06_one_364[1];
static s32 oshimodo_event[32];
static s32 bero_entry_data[75];
s32 iri_12_kino_makkino_talk[284];
s32 iri_12_kino_talk[36];
static __declspec(section ".data") s32 iri_12_makkino_talk[7];
static s32 iri_12_init[85];
static s32 evt_kanban[16];
static s32 evt_kanban2[45];
s32 tik_06_init_evt[47];

__declspec(section ".data") u64 fd_tik_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_06_one_364[] = {
    1065353216,
};

static EVT_BEGIN(oshimodo_event)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_ctrl_onoff, 4, 0)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_bero_exec_wait, 65536)
        WAIT_MS(750)
        CALL(evt_msg_print, 0, STRING("tik_06_01"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_cam_ctrl_onoff, 4, 1)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"dokan_1", 131072, 9, 100000, 0, 0, -1, 0,
    6, 0, (s32)"jon_00", (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_2",
    131072, 8, 100000, 0, 0, -1, 0, 6,
    0, (s32)"tik_18", (s32)"dokan_1", 65537, 0, 0, (s32)"dokan_3", 131072,
    9, 100000, 0, 0, -1, 0, 6, (s32)oshimodo_event,
    0, (s32)"dokan_3", 65537, 0, 0, (s32)"e_bero", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"tik_05",
    (s32)"w_bero", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(iri_12_kino_makkino_talk)
    CALL(evt_set_dir_to_target, STRING("キーノ"), STRING("mario"))
    CALL(evt_set_dir_to_target, STRING("マッキノ"), STRING("mario"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("キーノ"))
    CALL(evt_npc_wait_pera, STRING("マッキノ"))
    CALL(evt_msg_print, 0, STRING("irai_12_001_3"), 0, STRING("キーノ"))
    CALL(evt_msg_print, 0, STRING("irai_12_001_4"), 0, STRING("マッキノ"))
    CALL(evt_msg_print, 0, STRING("irai_12_001_5"), 0, STRING("キーノ"))
    IF_INT_EQUAL(LW(0), 1)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_npc_get_position, STRING("マッキノ"), LW(3), LW(4), LW(5))
            CALL(evt_sub_get_dir, LW(0), LW(2), LW(3), LW(5), LW(6))
            DIVIDE(LW(6), 90)
            MULTIPLY(LW(6), 90)
            ADD(LW(6), 45)
            CALL(evt_npc_add_dirdist, LW(3), LW(5), LW(6), 20)
            CALL(evt_npc_status_onoff, 0, STRING("マッキノ"), 2)
            CALL(evt_npc_flag_onoff, 1, STRING("マッキノ"), 32)
            CALL(evt_npc_move_position, STRING("マッキノ"), LW(3), LW(5), 0, 70, 0)
            WAIT_FRAMES(1)
            CALL(evt_npc_status_onoff, 1, STRING("マッキノ"), 2)
            CALL(evt_set_dir_to_target, STRING("マッキノ"), STRING("mario"))
        END_INLINE_EVENT
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("キーノ"), LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dir, LW(0), LW(2), LW(3), LW(5), LW(6))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(6), 20)
    CALL(evt_npc_flag_onoff, 1, STRING("キーノ"), 32)
    CALL(evt_npc_move_position, STRING("キーノ"), LW(0), LW(2), 0, 60, 0)
    CALL(evt_mario_set_dir_npc, STRING("キーノ"))
    WAIT_MS(500)
    CALL(evt_item_entry, STRING("tf"), 94, 0, -1000, 0, 17, -1, 0)
    CALL(evt_item_get_item, STRING("tf"))
    CALL(evt_item_get_item_end_wait, STRING("tf"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("irai_12_001_6"), 0, STRING("マッキノ"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("マッキノ"), 1073750048)
        CALL(evt_npc_move_position, STRING("マッキノ"), 220, 0, 0, 60, 4)
        CALL(evt_npc_jump_position_nohit, STRING("マッキノ"), 254, 15, 0, 400, 15)
        CALL(evt_npc_jump_position_nohit, STRING("マッキノ"), 285, 30, 0, 400, 15)
        CALL(evt_npc_set_position, STRING("マッキノ"), 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_npc_get_position, STRING("キーノ"), LW(0), LW(1), LW(2))
    ADD(LW(0), 25)
    LOOP(0)
        CALL(evt_npc_get_position, STRING("マッキノ"), LW(3), LW(4), LW(5))
        IF_INT_GREATER_OR_EQUAL(LW(3), LW(0))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING("キーノ"), 1073750048)
    CALL(evt_npc_move_position, STRING("キーノ"), 220, 0, 0, 60, 4)
    CALL(evt_npc_jump_position_nohit, STRING("キーノ"), 254, 15, 0, 400, 15)
    CALL(evt_npc_jump_position_nohit, STRING("キーノ"), 285, 30, 0, 400, 15)
    CALL(evt_npc_set_position, STRING("キーノ"), 0, -1000, 0)
    CALL(evt_sub_save_playtime, GSW(1429))
    SET_VALUE(GSW(1420), 0)
    SET_VALUE(GSWF(5386), 1)
    CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(iri_12_kino_talk)
    IF_INT_EQUAL(GSW(1420), 12)
        IF_INT_EQUAL(GSWF(5407), 0)
            IF_INT_EQUAL(GSWF(5405), 0)
                CALL(evt_msg_print, 0, STRING("irai_12_001_1"), 0, 0)
                SET_VALUE(GSWF(5405), 1)
                ELSE
                CALL(evt_msg_print, 0, STRING("irai_12_001_2"), 0, 0)
            END_IF
            ELSE
            SET_VALUE(LW(0), 0)
            CALL_CHILD(PTR(iri_12_kino_makkino_talk))
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(iri_12_makkino_talk)
    SET_VALUE(LW(0), 1)
    CALL_CHILD(PTR(iri_12_kino_makkino_talk))
    RETURN
EVT_END()

static EVT_BEGIN(iri_12_init)
    IF_INT_EQUAL(GSW(1420), 12)
        CALL(evt_npc_entry, STRING("キーノ"), STRING("c_kokinopio"))
        CALL(evt_npc_set_tribe, STRING("キーノ"), STRING("キノピオ子"))
        CALL(evt_npc_set_position, STRING("キーノ"), 60, 0, -70)
        IF_INT_EQUAL(GSWF(5407), 0)
            CALL(evt_npc_set_ry, STRING("キーノ"), 270)
            ELSE
            CALL(evt_npc_set_ry, STRING("キーノ"), 90)
        END_IF
        CALL(evt_npc_flag_onoff, 1, STRING("キーノ"), 1536)
        CALL(evt_npc_status_onoff, 1, STRING("キーノ"), 2)
        CALL(evt_npc_change_interrupt, STRING("キーノ"), 6, PTR(iri_12_kino_talk))
        IF_INT_EQUAL(GSWF(5407), 1)
            CALL(evt_npc_entry, STRING("マッキノ"), STRING("c_suifu_k"))
            CALL(evt_npc_set_tribe, STRING("マッキノ"), STRING("水夫"))
            CALL(evt_npc_set_position, STRING("マッキノ"), 90, 0, -70)
            CALL(evt_npc_set_ry, STRING("マッキノ"), 90)
            CALL(evt_npc_flag_onoff, 1, STRING("マッキノ"), 1536)
            CALL(evt_npc_status_onoff, 1, STRING("マッキノ"), 2)
            CALL(evt_npc_change_interrupt, STRING("マッキノ"), 6, PTR(iri_12_makkino_talk))
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_kanban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_msg_print, 0, STRING("tik_06_02"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_kanban2)
    CALL(evt_npc_stop_for_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    SET_VALUE(LW(0), GSW(33))
    SET_VALUE(LW(1), GSW(32))
    SET_VALUE(LW(4), GSW(35))
    MULTIPLY(LW(4), 256)
    ADD(LW(1), LW(4))
    SET_VALUE(LW(2), GSW(34))
    SET_VALUE(LW(3), 100)
    CALL(evt_msg_print_insert, 0, STRING("msg_jon_kanban_3"), 0, 0, LW(0), LW(1), LW(2), LW(3))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_npc_start_for_event)
    RETURN
EVT_END()

EVT_BEGIN(tik_06_init_evt)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(iri_12_init))
    CALL(evt_mobj_signboard, STRING("board"), -50, 0, 50, PTR(evt_kanban), LSWF(0))
    CALL(evt_mobj_signboard, STRING("board2"), 50, 0, -250, PTR(evt_kanban2), LSWF(0))
    CALL(evt_item_entry, STRING("item_00"), 125, 290, 0, -50, 16, GSWF(5593), 0)
    RETURN
EVT_END()

