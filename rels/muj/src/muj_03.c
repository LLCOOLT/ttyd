#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_eff64);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
extern s32 evt_bero_info_run[];
extern s32 evt_cam3d_evt_off[];
extern s32 evt_cam3d_evt_set[];
extern s32 evt_mario_key_onoff[];
extern s32 evt_mario_normalize[];
extern s32 evt_mario_set_dir[];
extern s32 evt_mario_set_pos[];
extern s32 evt_msg_print[];
extern s32 evt_msg_print_party[];
extern s32 evt_npc_flag_onoff[];
extern s32 evt_npc_jump_position_nohit[];
extern s32 evt_npc_set_position[];
extern s32 evt_npc_set_ry[];
extern s32 evt_npc_sound_data_set[];
extern s32 evt_party_run[];
extern s32 evt_party_set_dir[];
extern s32 evt_party_set_pos[];
extern s32 evt_party_stop[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 evt_sub_tree_access_entry[];

__declspec(section ".data") u64 fd_muj_03_negone_one_374;
__declspec(section ".data") s32 fd_muj_03_neg_one_382[1];
__declspec(section ".data") s32 fd_muj_03___local_PI_383[1];
__declspec(section ".data") s32 fd_muj_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_muj_03_one_negone_373;
__declspec(section ".data") s32 fd_muj_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_muj_03_one_381[1];
__declspec(section ".data") u64 fd_muj_03_negone_one_360;
__declspec(section ".data") s32 fd_muj_03_neg_one_365[1];
__declspec(section ".data") s32 fd_muj_03___local_PI_366[1];
__declspec(section ".data") s32 fd_muj_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_muj_03_one_negone_359;
__declspec(section ".data") s32 fd_muj_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_muj_03_one_364[1];
s32 muj_03_event_01[22];
static s32 bero_entry_data[45];
s32 nigeru_suifu01[271];
static s32 evt_kusa_5[20];
static s32 evt_kusa_7[20];
static s32 tree_tbl[30];
static s32 kusa_tbl[36];
s32 muj_03_init_evt[112];

__declspec(section ".data") u64 fd_muj_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_muj_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_muj_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_muj_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_muj_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_muj_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_muj_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_muj_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_muj_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_muj_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_muj_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_muj_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_muj_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_muj_03_one_364[] = {
    1065353216,
};

EVT_BEGIN(muj_03_event_01)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 234)
        IF_INT_EQUAL(GSWF(3131), 0)
            SPAWN_EVENT(PTR(nigeru_suifu01))
            SET_VALUE(GSWF(3131), 1)
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"muj_02", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, (s32)muj_03_event_01, -1,
    0, (s32)"muj_04", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

s32 nigeru_suifu01[] = {
    327771, (s32)evt_npc_set_position, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 570, 150, -50, 196699, (s32)evt_npc_set_ry,
    (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 90, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 1073776160, 327771,
    (s32)evt_npc_set_position, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 530, 150, -50, 196699, (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76",
    90, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 1073776160, 458843, (s32)evt_npc_sound_data_set,
    (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", (s32)"SFX_STG5_KANBU_GLASSES_MOVE1L", (s32)"SFX_STG5_KANBU_GLASSES_MOVE1R", -250000000, -250000000, -250000000, 131163, (s32)evt_mario_key_onoff,
    0, 65627, (s32)evt_mario_normalize, 131163, (s32)evt_party_stop, 0, 262235, (s32)evt_mario_set_pos,
    610, 150, 0, 262235, (s32)evt_mario_set_dir, 270, 0, 0,
    327771, (s32)evt_party_set_pos, 0, 630, 150, 25, 262235, (s32)evt_party_set_dir,
    0, 270, 0, 65546, 500, 262235, (s32)evt_npc_flag_onoff, 0,
    (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 32768, 262235, (s32)evt_npc_flag_onoff, 0, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 32768, 327771,
    (s32)evt_msg_print, 0, (s32)"stg5_muj_90_22", 0, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 131122, -90000000, 1,
    107, 196699, (s32)evt_npc_set_ry, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 270, 65546, 200, 458843,
    (s32)evt_npc_jump_position_nohit, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 464, 180, -50, 500, 50, 65546,
    300, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 382, 180, -50, 500,
    50, 327771, (s32)evt_npc_set_position, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 0, -1000, 0, 131122,
    -90000000, 0, 109, 65547, -90000000, 196699, (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76",
    270, 65546, 500, 327771, (s32)evt_msg_print, 0, (s32)"stg5_muj_90_23", 0,
    (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 65546, 200, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 464, 180,
    -50, 500, 50, 65546, 300, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76",
    382, 180, -50, 500, 50, 65546, 800, 196699,
    (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 90, 65546, 200, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76",
    465, 180, -50, 500, 50, 196699, (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76",
    90, 65546, 200, 589915, (s32)evt_cam3d_evt_set, 465, 288, 263,
    465, 240, -8, 500, 11, 65546, 500, 196699,
    (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 270, 65546, 1000, 327771, (s32)evt_msg_print, 0,
    (s32)"stg5_muj_90_24", 0, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 196699, (s32)evt_cam3d_evt_off, 500, 11, 65546,
    500, 107, 65546, 300, 458843, (s32)evt_npc_jump_position_nohit, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 382,
    180, -50, 500, 50, 327771, (s32)evt_npc_set_position, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 0,
    -1000, 0, 109, 262235, (s32)evt_party_set_dir, 0, 270, 200,
    65546, 300, 262235, (s32)evt_party_set_dir, 0, 90, 200, 65546,
    300, 262235, (s32)evt_party_set_dir, 0, 270, 200, 65546, 300,
    262235, (s32)evt_party_set_dir, 0, 90, 200, 65546, 300, 262235,
    (s32)evt_party_set_dir, 0, 270, 200, 131163, (s32)evt_msg_print_party, (s32)"stg5_muj_90_25", 131163,
    (s32)evt_party_run, 0, 131163, (s32)evt_mario_key_onoff, 1, 2, 1,
};

static EVT_BEGIN(evt_kusa_5)
    CALL(evt_item_delete_check, STRING("item_kusa_5"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_5"), 146, -250, 10, 95, 4, GSWF(3155), 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_kusa_7)
    CALL(evt_item_delete_check, STRING("item_kusa_7"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_kusa_7"), 121, 175, 210, -50, 4, GSWF(3156), 0)
    END_IF
    RETURN
EVT_END()

static s32 tree_tbl[] = {
    5, (s32)"A_treeA_01", (s32)"treeA_01_m", (s32)"treeA_01_ha", 0, 0, 5, (s32)"A_treeA_02",
    (s32)"treeA_02_m", (s32)"treeA_02_ha", 0, 0, 5, (s32)"A_treeA_03", (s32)"treeA_03_m", (s32)"treeA_03_ha",
    0, 0, 5, (s32)"A_treeA_04", (s32)"treeA_04_m", (s32)"treeA_04_ha", 0, 0,
    7, 0, 0, 0, 0, 0,
};

static s32 kusa_tbl[] = {
    1, (s32)"A_kuwa_move_01", (s32)"S_kuwa_move_01", 0, 1, (s32)"A_kuwa_move_02", (s32)"S_kuwa_move_02", 0,
    1, (s32)"A_kuwa_move_03", (s32)"S_kuwa_move_03", 0, 1, (s32)"A_kuwa_move_04", (s32)"S_kuwa_move_04", 0,
    1, (s32)"A_kuwa_move_05", (s32)"S_kuwa_move_05", (s32)evt_kusa_5, 1, (s32)"A_kuwa_move_06", (s32)"S_kuwa_move_06", 0,
    1, (s32)"A_kuwa_move_07", (s32)"S_kuwa_move_07", (s32)evt_kusa_7, 1, (s32)"A_kuwa_move_08", (s32)"S_kuwa_move_08", 0,
    4, 0, 0, 0,
};

EVT_BEGIN(muj_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG5_MUJ1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG5_MUJ5"))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_badgeblk, STRING("mobj01"), -50, 9, 0, 121, 0, GSWF(3133), 0)
    CALL(evt_mobj_brick, STRING("mobj02"), -50, 94, 0, 0, 13, 0, GSWF(3134))
    CALL(evt_mobj_brick, STRING("bblk00"), -470, 155, -50, 0, 0, 0, GSWF(3145))
    CALL(evt_mobj_powerupblk, STRING("pblk01"), -470, 240, -50, 0, GSWF(5552), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj03"), -50, 270, -100, 129, 0, GSWF(3147), 0)
    CALL(evt_mobj_brick, STRING("mobj_hidden2"), -50, 209, 0, 156, 11, 0, GSWF(3153))
    CALL(evt_item_entry, STRING("item_00"), 125, 275, 10, 100, 16, GSWF(5642), 0)
    CALL(evt_eff64, STRING("sunlight"), STRING("sunlight_n64"), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    SET_VALUE(LW(0), PTR(kusa_tbl))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    RETURN
EVT_END()

