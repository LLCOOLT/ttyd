#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "driver/hitdrv.h"
#include "string.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_damage.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_sub.h"

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff64);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_cam_keep_off);
USER_FUNC(evt_mario_cam_y_on);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mobj_jumpstand_blue);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_set_rotate);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_area_check);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(mario_moveride_check);

__declspec(section ".data") u64 fd_muj_04_negone_one_374;
__declspec(section ".data") s32 fd_muj_04_neg_one_382[1];
__declspec(section ".data") s32 fd_muj_04___local_PI_383[1];
__declspec(section ".data") s32 fd_muj_04___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_muj_04_one_negone_373;
__declspec(section ".data") s32 fd_muj_04___local_PIO2_384[1];
__declspec(section ".data") s32 fd_muj_04_one_381[1];
__declspec(section ".data") u64 fd_muj_04_negone_one_360;
__declspec(section ".data") s32 fd_muj_04_neg_one_365[1];
__declspec(section ".data") s32 fd_muj_04___local_PI_366[1];
__declspec(section ".data") s32 fd_muj_04___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_muj_04_one_negone_359;
__declspec(section ".data") s32 fd_muj_04___local_PIO2_367[1];
__declspec(section ".data") s32 fd_muj_04_one_364[1];
static s32 npcEnt[138];
static s32 evt_haikei_in[16];
static s32 bero_entry_data[75];
s32 hitname[17];
s32 mapanim[17];
s32 mario_hashi_anime[34];
s32 erumos00_attack[50];
s32 erumos01_attack[50];
s32 sanders_attack[88];
s32 mario_katsugi[24];
s32 sanders_funto[477];
__declspec(section ".data") s32 yashi_yure_init[5];
s32 yashi_yure[255];
static s32 hitDmgRetPoints[16];
static s32 tree_tbl[18];
static s32 kusa_tbl[20];
s32 muj_04_init_evt[131];

__declspec(section ".data") u64 fd_muj_04_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_muj_04_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_muj_04___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_muj_04___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_muj_04_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_muj_04___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_muj_04_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_muj_04_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_muj_04_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_muj_04___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_muj_04___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_muj_04_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_muj_04___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_muj_04_one_364[] = {
    1065353216,
};

static s32 npcEnt[] = {
    (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 1536, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76",
    1536, 0, (s32)npc_init_evt, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 1536,
    0, (s32)npc_init_evt, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", 1536, 0,
    (s32)npc_init_evt, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 1536, 0, (s32)npc_init_evt,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

static EVT_BEGIN(evt_haikei_in)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
        WAIT_FRAMES(10)
        CALL(evt_mario_cam_keep_off)
        CALL(evt_mario_cam_y_on)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"muj_03", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"muj_05", (s32)"w_bero", 65537, 0, 0, (s32)"dokan_1", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"A_dokan", 65537, 0, 0, (s32)"A_dokan", 268566528, 9,
    100000, 0, 0, -1, (s32)evt_haikei_in, 6, 0, 0,
    (s32)"dokan_1", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

s32 hitname[] = {
    (s32)"A_hasi01", (s32)"A_hasi02", (s32)"A_hasi03", (s32)"A_hasi04", (s32)"A_hasi05", (s32)"A_hasi06", (s32)"A_hasi07", (s32)"A_hasi08",
    (s32)"A_hasi09", (s32)"A_hasi010", (s32)"A_hasi011", (s32)"A_hasi012", (s32)"A_hasi013", (s32)"A_hasi014", (s32)"A_hasi015", (s32)"A_hasi016",
    (s32)"A_hasi017",
};

s32 mapanim[] = {
    (s32)"S_hasi01", (s32)"S_hasi02", (s32)"S_hasi03", (s32)"S_hasi04", (s32)"S_hasi05", (s32)"S_hasi06", (s32)"S_hasi07", (s32)"S_hasi08",
    (s32)"S_hasi09", (s32)"S_hasi10", (s32)"S_hasi11", (s32)"S_hasi12", (s32)"S_hasi13", (s32)"S_hasi14", (s32)"S_hasi15", (s32)"S_hasi16",
    (s32)"S_hasi17",
};

EVT_BEGIN(mario_hashi_anime)
    SET_VALUE(LW(1), 0)
    LOOP(0)
        CALL(mario_moveride_check)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_BRIDGE_CREAK1"), LW(10), LW(11), LW(12), 0)
            CALL(evt_map_playanim, LW(0), 0, 0)
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

s32 erumos00_attack[] = {
    458843, (s32)evt_npc_sound_data_set, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", 0, 0, -250000000, -250000000, -250000000,
    65546, 500, 65541, 0, 327771, (s32)evt_npc_get_position, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG5_ELMOS_MOVE1_2", -30000000, -29999999, -29999998,
    0, 655451, (s32)evt_npc_glide_position, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", -25, 125, 0, 0,
    -229882240, 0, 11, 0, 655451, (s32)evt_npc_glide_position, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", -35,
    125, 0, 0, -229875072, 0, 11, 0, 6,
    2, 1,
};

s32 erumos01_attack[] = {
    458843, (s32)evt_npc_sound_data_set, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 0, 0, -250000000, -250000000, -250000000,
    65546, 500, 65541, 0, 327771, (s32)evt_npc_get_position, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG5_ELMOS_MOVE1_2", -30000000, -29999999, -29999998,
    0, 655451, (s32)evt_npc_glide_position, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 25, 125, 0, 0,
    -229887360, 0, 11, 0, 655451, (s32)evt_npc_glide_position, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 35,
    125, 0, 0, -229876096, 0, 11, 0, 6,
    2, 1,
};

EVT_BEGIN(sanders_attack)
    WAIT_MS(600)
    BEGIN_INLINE_EVENT
        LOOP(0)
            WAIT_MS(200)
            CALL(evt_npc_get_position, STRING("サンダース"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_THUNDERS_DAMAGED1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_sub_random, 30, LW(10))
            ADD(LW(10), -15)
            ADD(LW(10), LW(0))
            CALL(evt_sub_random, 30, LW(11))
            ADD(LW(11), LW(1))
            CALL(evt_eff, STRING(""), STRING("hit"), 3, LW(10), LW(11), LW(2), FLOAT(0.5f), 18, 0, 0, 0, 0, 0, 0)
            WAIT_MS(400)
        END_LOOP
    END_INLINE_EVENT
    LOOP(0)
        WAIT_MS(100)
        CALL(evt_sub_intpl_msec_init, 11, 0, 360, 200)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_npc_set_rotate, STRING("サンダース"), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mario_katsugi)
    LOOP(0)
        CALL(evt_npc_get_position, STRING("めがね水夫"), LW(0), LW(1), LW(2))
        ADD(LW(1), 40)
        ADD(LW(2), 5)
        CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

s32 sanders_funto[] = {
    327771, (s32)evt_npc_set_position, (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 0, 112, 0, 196699, (s32)evt_npc_set_ry,
    (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 90, 327771, (s32)evt_npc_set_position, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", -25, 112, -20,
    196699, (s32)evt_npc_set_ry, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 270, 327771, (s32)evt_npc_set_position, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 25,
    112, -20, 196699, (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 90, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 32, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 32,
    458843, (s32)evt_npc_sound_data_set, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", (s32)"SFX_STG5_KANBU_GLASSES_MOVE1L", (s32)"SFX_STG5_KANBU_GLASSES_MOVE1R", -250000000, -250000000, -250000000,
    196699, (s32)evt_npc_set_ry, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", 90, 196699, (s32)evt_npc_set_ry, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 270,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", 32, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 32, 327771, (s32)evt_npc_set_position, (s32)/*"エルモスA"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x41", -60, 125, 0,
    327771, (s32)evt_npc_set_position, (s32)/*"エルモスB"*/"\x83\x47\x83\x8B\x83\x82\x83\x58\x42", 60, 125, 0, 131163, (s32)evt_mario_key_onoff,
    0, 131163, (s32)evt_bero_exec_wait, 65536, 65627, (s32)evt_mario_normalize, 131163, (s32)evt_party_stop,
    0, 327771, (s32)evt_msg_print, 0, (s32)"stg5_muj_23", 0, (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 107,
    327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_VOICE_MARIO_FIND1", -30000000, -29999999, -29999998, 0, 109, 786523, (s32)evt_eff_fukidashi,
    0, (s32)"", 0, 0, 0, 0, 0, 0,
    0, 0, 60, 786523, (s32)evt_eff_fukidashi, 3, (s32)"", 0,
    0, 0, 0, 0, 0, 0, 0, 60,
    65546, 1000, 589915, (s32)evt_cam3d_evt_set, 0, 260, 532, 0,
    165, -10, 1000, 11, 65546, 500, 196699, (s32)evt_snd_bgmon,
    512, (s32)"BGM_EVT_DANGER4", 107, 262235, (s32)evt_mario_mov_pos2, -150, 0, -229846400,
    109, 107, 327771, (s32)evt_party_move_pos2, 0, -180, 0, -229846400,
    109, 65546, 500, 65546, 500, 786523, (s32)evt_eff_fukidashi, 1,
    (s32)"", (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 0, 0, 0, 0, 0, 0,
    0, 60, 65546, 1000, 196699, (s32)evt_set_dir_to_target, (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", (s32)"mario",
    589915, (s32)evt_cam3d_evt_set, -60, 260, 532, -60, 165, -10,
    500, 11, 65546, 1000, 327771, (s32)evt_msg_print, 0, (s32)"stg5_muj_24",
    0, (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 131163, (s32)evt_mario_set_pose, (s32)"M_N_5B", 196699, (s32)evt_set_dir_to_target, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76",
    (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 65546, 500, 131163, (s32)evt_mario_set_pose, (s32)"M_S_1", 327771, (s32)evt_msg_print,
    0, (s32)"stg5_muj_25", 0, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 327771, (s32)evt_msg_print, 0, (s32)"stg5_muj_26",
    0, (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58", 107, 327771, (s32)evt_sub_intpl_msec_init, 11, 0, 360,
    200, 65541, 0, 65627, (s32)evt_sub_intpl_msec_get_value, 327771, (s32)evt_npc_set_rotate, (s32)/*"サンダース"*/"\x83\x54\x83\x93\x83\x5F\x81\x5B\x83\x58",
    0, -30000000, 0, 131096, -29999999, 0, 7, 33,
    65545, 1, 6, 109, 65546, 200, 131122, -90000000,
    1, 107, 262235, (s32)evt_npc_flag_onoff, 0, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 1536, 327771,
    (s32)evt_npc_get_position, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG5_THUNDERS_THROW1",
    -30000000, -29999999, -29999998, 0, 327771, (s32)evt_mario_get_pos, 0, -30000000,
    -29999999, -29999998, 196699, (s32)evt_npc_set_ry, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 270, 458843, (s32)evt_npc_jump_position_nohit,
    (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", -30000000, -29999999, -29999998, 500, 70, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 131088, 109, 107, 262235, (s32)evt_npc_flag_onoff, 0,
    (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 1536, 196699, (s32)evt_npc_set_ry, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 270, 458843, (s32)evt_npc_jump_position_nohit,
    (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", -105, 116, 0, 500, 70, 196699, (s32)evt_npc_set_anim,
    (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", (s32)"F_1", 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 131088, 327771,
    (s32)evt_msg_print, 0, (s32)"stg5_muj_27", 0, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 131122, -90000000, 0,
    109, 107, 65546, 350, 327771, (s32)evt_mario_get_pos, 0, -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE2", -30000000, -29999999, -29999998,
    0, 131163, (s32)evt_mario_set_pose, (s32)"M_D_8", 109, 589915, (s32)evt_cam3d_evt_set, -110,
    260, 532, -110, 165, -10, 500, 11, 65546,
    500, 65628, (s32)erumos00_attack, 65628, (s32)erumos01_attack, 65628, (s32)sanders_attack, 65547,
    -90000000, 196699, (s32)evt_npc_set_anim, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", (s32)"S_1", 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 512, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", 1536, 65545,
    1, 327771, (s32)evt_msg_print, 0, (s32)"stg5_muj_28", 0, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", 65546,
    1000, 65627, (s32)evt_mario_cam_keep_off, 131163, (s32)evt_mario_cont_onoff, 0, 107, 196699,
    (s32)evt_npc_set_anim, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", (s32)"U_1", 131163, (s32)evt_mario_set_pose, (s32)"M_I_6", 65628, (s32)mario_katsugi,
    65546, 300, 196699, (s32)evt_npc_set_anim, (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", (s32)"R_4", 458843, (s32)evt_npc_move_position,
    (s32)/*"めがね水夫"*/"\x82\xDF\x82\xAA\x82\xCB\x90\x85\x95\x76", -300, -20, 0, -229815680, 0, 109, 107,
    65546, 300, 458843, (s32)evt_npc_move_position, (s32)/*"オドオド水夫"*/"\x83\x49\x83\x68\x83\x49\x83\x68\x90\x85\x95\x76", -300, -20, 0,
    -229815680, 0, 109, 107, 327771, (s32)evt_party_move_pos2, 0, -300,
    -20, -229815680, 109, 65546, 2000, 131122, -170000000, 234,
    393307, (s32)evt_fade_set_mapchange_type, 0, 2, 500, 1, 500, 196699,
    (s32)evt_bero_mapchange, (s32)"muj_03", (s32)"e_bero", 2, 1,
};

__declspec(section ".data") EVT_BEGIN(yashi_yure_init)
    SET_VALUE(GW(10), 0)
    RETURN
EVT_END()

EVT_BEGIN(yashi_yure)
    ADD(GW(10), 1)
    IF_INT_EQUAL(GW(10), 1)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mapobj_get_position, STRING("S_yasi_ki"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_OBJ_TREE_SHAKE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_OBJ_LEAF_SHAKE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_sub_intpl_init, 1, 0, -40, 15)
        LOOP(16)
            CALL(evt_sub_intpl_get_value)
            CALL(evt_mapobj_trans, 1, STRING("S_yasi_mi02"), 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mapobj_get_position, STRING("S_yasi_mi01"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_COCONUTS_FALL1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(500)
        CALL(evt_mario_key_onoff, 1)
        BEGIN_INLINE_EVENT
            LOOP(0)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_sub_area_check, 0, 40, -489, 20, LW(0), LW(2), LW(10))
                IF_INT_EQUAL(LW(10), 1)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_mapobj_trans, 1, STRING("S_yasi_mi02"), 0, -1000, 0)
            CALL(evt_item_entry, STRING("yashi00"), 166, 0, -1000, 0, 16, -1, 0)
            CALL(evt_item_flag_on, STRING("yashi00"), 2)
            CALL(evt_item_get_item, STRING("yashi00"))
            CALL(evt_mario_key_onoff, 1)
        END_INLINE_EVENT
        RETURN
    END_IF
    IF_INT_EQUAL(GW(10), 2)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mapobj_get_position, STRING("S_yasi_ki"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_OBJ_TREE_SHAKE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_OBJ_LEAF_SHAKE1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(100)
        WAIT_MS(50)
        CALL(evt_sub_intpl_init, 1, 0, -40, 15)
        LOOP(16)
            CALL(evt_sub_intpl_get_value)
            CALL(evt_mapobj_trans, 1, STRING("S_yasi_mi01"), 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mapobj_get_position, STRING("S_yasi_mi01"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG5_COCONUTS_FALL1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(500)
        CALL(evt_mario_key_onoff, 1)
        BEGIN_INLINE_EVENT
            LOOP(0)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_sub_area_check, 0, 50, -489, 20, LW(0), LW(2), LW(10))
                IF_INT_EQUAL(LW(10), 1)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_mapobj_trans, 1, STRING("S_yasi_mi01"), 0, -1000, 0)
            CALL(evt_item_entry, STRING("yashi01"), 166, 0, -1000, 0, 16, -1, 0)
            CALL(evt_item_flag_on, STRING("yashi01"), 2)
            CALL(evt_item_get_item, STRING("yashi01"))
            CALL(evt_mario_key_onoff, 1)
        END_INLINE_EVENT
        RETURN
    END_IF
    RETURN
EVT_END()

static s32 hitDmgRetPoints[] = {
    (s32)"S_l_dai_03", -1009254400, 1125515264, 0, (s32)"A_r_dai", 1137541120, 1125515264, 0,
    (s32)"dokan_1", 0, -998637568, 0, 0, 0, 0, 0,
};

static s32 tree_tbl[] = {
    5, (s32)"A_treeA_02", (s32)"treeA_02_m", (s32)"treeA_02_ha", 0, 0, 5, (s32)"A_treeA_04",
    (s32)"treeA_04_m", (s32)"treeA_04_ha", 0, 0, 7, 0, 0, 0,
    0, 0,
};

static s32 kusa_tbl[] = {
    1, (s32)"A_kuwa_move_01", (s32)"S_kuwa_move_01", 0, 1, (s32)"A_kuwa_move_02", (s32)"S_kuwa_move_02", 0,
    1, (s32)"A_kuwa_move_03", (s32)"S_kuwa_move_03", 0, 1, (s32)"A_kuwa_move_04", (s32)"S_kuwa_move_04", 0,
    4, 0, 0, 0,
};

EVT_BEGIN(muj_04_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG5_MUJ1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG5_MUJ6"))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_item_entry, STRING("item_00"), 283, 290, 60, 10, 16, GSWF(3148), 0)
    CALL(evt_item_entry, STRING("item_01"), 164, -367, 150, -73, 16, GSWF(3158), 0)
    CALL(evt_mobj_powerupblk, STRING("pblk00"), 450, 210, -90, 0, GSWF(5553), 0)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_map_playanim, STRING("S_mizu"), 1, 0)
    CALL(evt_map_playanim, STRING("S_mizu_02"), 1, 0)
    SPAWN_EVENT(PTR(mario_hashi_anime))
    SPAWN_EVENT(PTR(yashi_yure_init))
    CALL(evt_run_case_evt, 13, 1, STRING("A_hai_yasi"), 0, PTR(yashi_yure), 0)
    SWITCH(GSW(0))
        CASE_EQUAL(233)
        SPAWN_EVENT(PTR(sanders_funto))
    END_SWITCH
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_hitobj_attr_onoff, 1, 1, STRING("A_hasi18"), 2097152)
    CALL(evt_hitobj_attr_onoff, 1, 1, STRING("A_srt"), 2097152)
    CALL(evt_mobj_jumpstand_blue, 0, STRING("mobj_jump00"), 150, 425, 10, 130, 0, 0)
    CALL(evt_eff64, STRING("sunlight"), STRING("sunlight_n64\0\0\0"), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    SET_VALUE(LW(0), PTR(tree_tbl))
    CALL_CHILD(PTR(evt_sub_tree_access_entry))
    SET_VALUE(LW(0), PTR(kusa_tbl))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    RETURN
EVT_END()

USER_FUNC(mario_moveride_check) {
    s32 i;
    const char* name;
    s32 anim;
    HitEntry* hit = marioGetPtr()->hitobjStandOn;

    name = NULL;
    for (i = 0; i < 17; i++) {
        if (hit != NULL && strcmp(hitGetName(hit), (const char*)hitname[i]) == 0) {
            name = (const char*)hitname[i];
            anim = mapanim[i];
            break;
        }
    }
    event->lwData[0] = 0;
    if (name != NULL && event->lwData[1] != (s32)name) {
        event->lwData[0] = anim;
    }
    event->lwData[1] = (s32)name;
    return EVT_RETURN_DONE;
}
