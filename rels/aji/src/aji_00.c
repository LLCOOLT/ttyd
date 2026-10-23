#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "aji.h"

#pragma force_active on

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_npc_battle_start);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_set_battle_info);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_wait_battle_end);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_telop_entry);

__declspec(section ".data") u64 fd_aji_00_negone_one_374;
__declspec(section ".data") s32 fd_aji_00_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_00___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_00_one_negone_373;
__declspec(section ".data") s32 fd_aji_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_00_one_381[1];
__declspec(section ".data") u64 fd_aji_00_negone_one_360;
__declspec(section ".data") s32 fd_aji_00_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_00___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_00_one_negone_359;
__declspec(section ".data") s32 fd_aji_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_00_one_364[1];
__declspec(section ".data") s32 fd_aji_00__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_aji_00__half_localstatic3_sqrtf[2];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
static s32 first_evt[333];
static s32 evt_door_msg[14];
static s32 npcEnt[69];
s32 aji_00_init_evt[91];

__declspec(section ".data") u64 fd_aji_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_00_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_aji_00__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_aji_00__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"aji_19", (s32)"e_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero",
    65546, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"aji_01", (s32)"w_bero_1", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(first_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER2"))
    CALL(evt_snd_envoff, 512)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_set_position, STRING("手下１"), 225, 0, -25)
    CALL(evt_npc_set_position, STRING("手下２"), 265, 0, 25)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_cam3d_evt_set, -225, 65, 342, -225, 45, -8, 1000, 11)
    WAIT_MS(250)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_cam3d_evt_set, 225, 65, 342, 225, 45, -8, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg7_aji_00_00_02"), 0, STRING("手下１"))
    CALL(evt_npc_move_position, STRING("手下１"), 200, -25, 0, FLOAT(80.0f), 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_00_00_03"), 0, STRING("手下２"))
    CALL(evt_npc_move_position, STRING("手下２"), 239, 25, 0, FLOAT(80.0f), 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_00_00_04"), 0, STRING("手下２"))
    CALL(evt_cam3d_evt_set, 175, 97, 542, 175, 71, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_off, 2000, 11)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING("M_I_Y"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下２"), -160, 0, 0, FLOAT(200.0f), 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("手下１"), -200, 0, 0, FLOAT(200.0f), 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_npc_set_battle_info, STRING("手下１"), 6)
    CALL(evt_npc_battle_start, STRING("手下１"))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_mario_set_pos, -200, 0, 0)
    CALL(evt_party_set_pos, 0, -240, 0, 0)
    CALL(evt_npc_set_position, STRING("手下１"), -180, 0, 0)
    CALL(evt_npc_set_position, STRING("手下２"), -150, 0, -55)
    CALL(evt_npc_set_ry, STRING("手下１"), 90)
    CALL(evt_npc_set_ry, STRING("手下２"), 90)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下１"), 225, -25, 0, FLOAT(180.0f), 0)
        CALL(evt_npc_set_position, STRING("手下１"), 0, -1000, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("手下２"), 265, 25, 0, FLOAT(180.0f), 0)
        CALL(evt_npc_set_position, STRING("手下２"), 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg7_aji_00_00_06"), 0, 0)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -220, 65, 342, -220, 45, -8, 800, 11)
    WAIT_MS(800)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg7_aji_00_00_07"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_msg_print_party, STRING("stg7_aji_00_00_08"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    SET_VALUE(GSW(0), 361)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI2"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_telop_entry, 16)
    RETURN
EVT_END()

static EVT_BEGIN(evt_door_msg)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_64"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"手下１"*/"\x8E\xE8\x89\xBA\x82\x50", 1073743360, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"手下２"*/"\x8E\xE8\x89\xBA\x82\x51",
    1073743360, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(aji_00_init_evt)
    IF_INT_LESS(GSW(0), 361)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN1"))
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    END_IF
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI2"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_LESS(GSW(0), 361)
        SPAWN_EVENT(PTR(first_evt))
    END_IF
    CALL(evt_mobj_recovery_blk, STRING("r_blk"), 20, -100, 60, -200, 0, 0)
    CALL(evt_mobj_save_blk, STRING("s_blk"), 100, 60, -200, 0, 0)
    SPAWN_EVENT(PTR(evt_emergency))
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_map_playanim, STRING("hosi_01"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi_03"), 1, 0)
    SWITCH(GSW(0))
        CASE_BETWEEN(376, 402)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_run_case_evt, 9, 1, STRING("w_bero"), 0, PTR(evt_door_msg), 0)
    END_SWITCH
    RETURN
EVT_END()

