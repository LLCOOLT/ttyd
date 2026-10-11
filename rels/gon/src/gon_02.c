#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_pera_onoff);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_height);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_rotate);
USER_FUNC(evt_npc_set_width);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_gon_02_negone_one_374;
__declspec(section ".data") s32 fd_gon_02_neg_one_382[1];
__declspec(section ".data") s32 fd_gon_02___local_PI_383[1];
__declspec(section ".data") s32 fd_gon_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gon_02_one_negone_373;
__declspec(section ".data") s32 fd_gon_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gon_02_one_381[1];
__declspec(section ".data") u64 fd_gon_02_negone_one_360;
__declspec(section ".data") s32 fd_gon_02_neg_one_365[1];
__declspec(section ".data") s32 fd_gon_02___local_PI_366[1];
__declspec(section ".data") s32 fd_gon_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gon_02_one_negone_359;
__declspec(section ".data") s32 fd_gon_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gon_02_one_364[1];
static s32 door01_close[22];
static s32 door01_open[22];
static __declspec(section ".data") s32 door02_close[12];
static __declspec(section ".data") s32 door02_open[12];
static s32 bero_entry_data[60];
s32 gon_02_init_evt[248];

__declspec(section ".data") u64 fd_gon_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gon_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gon_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gon_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gon_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gon_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gon_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gon_02_one_364[] = {
    1065353216,
};

static EVT_BEGIN(door01_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(door01_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(door02_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door03"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(door02_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door03"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65548, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"gon_01", (s32)"e_bero", 327685, (s32)door01_close, (s32)door01_open, (s32)"e_bero",
    65548, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"gon_03", (s32)"w_bero", 327685, (s32)door02_close, (s32)door02_open, (s32)"w_bero2", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"gon_01", (s32)"e_bero_2", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(gon_02_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG1_GON1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG1_GON1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_npc_entry, STRING("\"カロン00\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン00\""), -454, 0, -35)
    CALL(evt_npc_set_rotate, STRING("\"カロン00\""), 0, 0, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン00\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン00\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン00\""), 1048576)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン00\""), 33554432)
    CALL(evt_npc_set_width, STRING("\"カロン00\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン00\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン01\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン01\""), -127, 0, 37)
    CALL(evt_npc_set_rotate, STRING("\"カロン01\""), 0, 180, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン01\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン01\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン01\""), 1048576)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン01\""), 33554432)
    CALL(evt_npc_set_width, STRING("\"カロン01\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン01\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン02\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン02\""), 12, 0, -29)
    CALL(evt_npc_set_rotate, STRING("\"カロン02\""), 0, 0, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン02\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン02\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン02\""), 1048576)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン02\""), 33554432)
    CALL(evt_npc_set_width, STRING("\"カロン02\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン02\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン03\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン03\""), 310, 0, -33)
    CALL(evt_npc_set_rotate, STRING("\"カロン03\""), 0, 180, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン03\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン03\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン03\""), 1048576)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン03\""), 33554432)
    CALL(evt_npc_set_width, STRING("\"カロン03\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン03\""), 7)
    CALL(evt_npc_entry, STRING("\"カロン04\""), STRING("c_karon_g"))
    CALL(evt_npc_set_position, STRING("\"カロン04\""), 511, 0, 50)
    CALL(evt_npc_set_rotate, STRING("\"カロン04\""), 0, 0, 0)
    CALL(evt_npc_set_anim, STRING("\"カロン04\""), STRING("KRN_Z_2"))
    CALL(evt_npc_pera_onoff, STRING("\"カロン04\""), 0)
    CALL(evt_npc_flag_onoff, 0, STRING("\"カロン04\""), 1048576)
    CALL(evt_npc_flag_onoff, 1, STRING("\"カロン04\""), 33554432)
    CALL(evt_npc_set_width, STRING("\"カロン04\""), 30)
    CALL(evt_npc_set_height, STRING("\"カロン04\""), 7)
    CALL(evt_map_playanim, STRING("hokori"), 1, 0)
    CALL(evt_mobj_badgeblk, STRING("m"), 200, 60, -50, 242, 0, GSWF(1502), 1)
    RETURN
EVT_END()

