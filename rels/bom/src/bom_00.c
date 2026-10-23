#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_letter_box_onoff);
USER_FUNC(evt_eff64);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_party_dispflg_onoff);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);

__declspec(section ".data") u64 fd_bom_00_negone_one_374;
__declspec(section ".data") s32 fd_bom_00_neg_one_382[1];
__declspec(section ".data") s32 fd_bom_00___local_PI_383[1];
__declspec(section ".data") s32 fd_bom_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_bom_00_one_negone_373;
__declspec(section ".data") s32 fd_bom_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_bom_00_one_381[1];
__declspec(section ".data") u64 fd_bom_00_negone_one_360;
__declspec(section ".data") s32 fd_bom_00_neg_one_365[1];
__declspec(section ".data") s32 fd_bom_00___local_PI_366[1];
__declspec(section ".data") s32 fd_bom_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_bom_00_one_negone_359;
__declspec(section ".data") s32 fd_bom_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_bom_00_one_364[1];
s32 evt_bom_snowfall[18];
static s32 tree_tbl[24];
static __declspec(section ".data") s32 evt_tree[7];
static s32 first_evt_dokan[36];
static s32 bero_entry_data[45];
static s32 first_evt[108];
s32 first_evt2[101];
s32 bom_00_init_evt[66];

__declspec(section ".data") u64 fd_bom_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_bom_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_00_one_364[] = {
    1065353216,
};

EVT_BEGIN(evt_bom_snowfall)
    CALL(evt_eff64, 0, STRING("snowfall_n64"), 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static s32 tree_tbl[] = {
    3, (s32)"A_ki1", (s32)"S_ki_1", (s32)"S_ha_1", 0, 0, 3, (s32)"A_ki2",
    (s32)"S_ki_2", (s32)"S_ha_2", 0, 0, 3, (s32)"A_ki3", (s32)"S_ki_3", (s32)"S_ha_3",
    0, 0, 7, 0, 0, 0, 0, 0,
};

static __declspec(section ".data") EVT_BEGIN(evt_tree)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    RETURN
EVT_END()

static EVT_BEGIN(first_evt_dokan)
    IF_INT_EQUAL(GSWF(3884), 1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_party_dispflg_onoff, 0, 1, 1)
    SET_VALUE(GF(0), 1)
    WAIT_WHILE(GF(0))
    CALL(evt_mario_dispflag_onoff, 0, 1)
    CALL(evt_party_dispflg_onoff, 0, 1, 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"dokan", 131072, 9, 100000, 0, 0, -1, (s32)first_evt_dokan,
    6, 0, (s32)"tik_07", (s32)"dokan__1", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"bom_03", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(first_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam_letter_box_onoff, 1, 0)
    CALL(evt_cam3d_evt_set, -176, 567, 533, -176, 471, -9, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_cam3d_evt_set, -176, 183, 533, -176, 87, -9, 6000, 11)
    WAIT_MS(6000)
    SET_VALUE(GF(0), 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_mario_mov_pos2, -155, 31, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_party_move_pos2, 0, -188, 31, FLOAT(60.0f))
    CALL(evt_party_set_dir, 0, 90, 300)
    CALL(evt_cam3d_evt_set, -175, 90, 295, -175, 35, 0, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg7_bom_01"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(0), 352)
    SET_VALUE(GSWF(3884), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(first_evt2)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_cam3d_evt_set, -176, 567, 533, -176, 471, -9, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_cam3d_evt_set, -176, 183, 533, -176, 87, -9, 6000, 11)
    WAIT_MS(6000)
    SET_VALUE(GF(0), 0)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_mario_mov_pos2, -155, 31, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_party_move_pos2, 0, -188, 31, FLOAT(60.0f))
    CALL(evt_party_set_dir, 0, 90, 300)
    CALL(evt_cam3d_evt_set, -175, 90, 295, -175, 35, 0, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg7_bom_01_00"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSWF(3884), 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(bom_00_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_BOM1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_BOM1"))
    CALL_CHILD(PTR(evt_bom_snowfall))
    CALL_CHILD(PTR(evt_tree))
    CALL(evt_mobj_brick, STRING("mobj_badge_gat2"), 215, 65, -75, 255, 12, 0, GSWF(3891))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -300, 5, 0, STRING("S_gra02_dai"), 125, GSWF(5658))
    IF_INT_EQUAL(GSWF(3884), 0)
        SWITCH(GSW(0))
            CASE_LESS(349)
            SPAWN_EVENT(PTR(first_evt2))
            CASE_DEFAULT
            SPAWN_EVENT(PTR(first_evt))
        END_SWITCH
        ELSE
        IF_INT_GREATER_OR_EQUAL(GSW(0), 349)
            IF_INT_LESS(GSW(0), 352)
                SET_VALUE(GSW(0), 352)
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

