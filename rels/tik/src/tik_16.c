#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_damage.h"
#include "evt/evt_movefloor.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_lv_blk);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_tornadoswitch_blue);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value_para);
USER_FUNC(evt_sub_intpl_msec_init);

__declspec(section ".data") u64 fd_tik_16_negone_one_374;
__declspec(section ".data") s32 fd_tik_16_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_16___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_16___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_16_one_negone_373;
__declspec(section ".data") s32 fd_tik_16___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_16_one_381[1];
__declspec(section ".data") u64 fd_tik_16_negone_one_360;
__declspec(section ".data") s32 fd_tik_16_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_16___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_16___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_16_one_negone_359;
__declspec(section ".data") s32 fd_tik_16___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_16_one_364[1];
static s32 bero_entry_data[105];
static s32 hitDmgRetPoints[36];
static s32 evt_switch_00_init[26];
static __declspec(section ".data") s32 evt_switch_00_after[11];
static s32 evt_switch_00[56];
static s32 evt_switch_01_init[26];
static __declspec(section ".data") s32 evt_switch_01_after[11];
static s32 evt_switch_01[56];
s32 tik_16_init_evt[115];

__declspec(section ".data") u64 fd_tik_16_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_16_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_16___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_16___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_16_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_16___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_16_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_16_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_16_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_16___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_16___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_16_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_16___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_16_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"w_bero_2", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tik_17", (s32)"e_bero_2", 65537, 0, 0, (s32)"w_bero_1",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"tik_17", (s32)"e_bero_1", 65537, 0, 0, (s32)"e_bero_2", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"tik_15", (s32)"w_bero_2", 65537, 0, 0, (s32)"e_bero_1", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"tik_15",
    (s32)"w_bero_1", 65537, 0, 0, (s32)"dokan_1", 131072, 9, 100000,
    0, 0, -1, 0, 6, 0, (s32)"mri_00", (s32)"dokan_1",
    65537, 0, 0, (s32)"dokan_2", 131072, 9, 100000, 0,
    0, -1, 0, 6, 0, (s32)"nok_01", (s32)"dokan_1", 65537,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};

static s32 hitDmgRetPoints[] = {
    (s32)"mod_1", 0, -998637568, 0, (s32)"mod_2", -1015414784, 0, 0,
    (s32)"mod_3", -1015414784, 0, 0, (s32)"mod_4", 1132068864, 0, 0,
    (s32)"mod_5", 1132068864, 0, 0, (s32)"mod_6", 0, -998637568, 0,
    (s32)"a_dai_1", 0, -998637568, 0, (s32)"a_dai_2", 0, -998637568, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(evt_switch_00_init)
    CALL(evt_hit_bind_mapobj, STRING("a_dokan_1"), STRING("S_dakan_1"))
    IF_INT_EQUAL(GSWF(1345), 1)
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_1"), 0, 30, 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_1"))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("dokan_1_k"), 1)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_switch_00_after)
    IF_INT_EQUAL(GSWF(1345), 0)
        SET_VALUE(LW(0), STRING("dokan_1"))
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_switch_00)
    CALL(evt_mapobj_get_position, STRING("S_dakan_1"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOKAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 30, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_1"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_1"))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("dokan_1_k"), 1)
    SET_VALUE(LW(0), STRING("dokan_1"))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

static EVT_BEGIN(evt_switch_01_init)
    CALL(evt_hit_bind_mapobj, STRING("a_dokan_2"), STRING("S_dakan_2"))
    IF_INT_EQUAL(GSWF(1346), 1)
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_2"), 0, 30, 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_2"))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("dokan_2_k"), 1)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_switch_01_after)
    IF_INT_EQUAL(GSWF(1346), 0)
        SET_VALUE(LW(0), STRING("dokan_2"))
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_switch_01)
    CALL(evt_mapobj_get_position, STRING("S_dakan_2"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOKAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 30, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_trans, 1, STRING("S_dakan_2"), 0, LW(0), 0)
        CALL(evt_hit_bind_update, STRING("a_dokan_2"))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("dokan_2_k"), 1)
    SET_VALUE(LW(0), STRING("dokan_2"))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

EVT_BEGIN(tik_16_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK7"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL_CHILD(PTR(evt_switch_00_init))
    CALL_CHILD(PTR(evt_switch_01_init))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_switch_00_after))
    CALL_CHILD(PTR(evt_switch_01_after))
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_map_playanim, STRING("anm_mizu"), 1, 0)
    CALL(evt_mobj_lv_blk, STRING("block"), 0, 0, 0, 0, GSWF(1347), STRING("MOBJ_Lv1BigBigBlock"))
    IF_INT_EQUAL(GSWF(1347), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("block"), 128)
    END_IF
    SET_VALUE(LW(0), STRING("dai_3"))
    SET_VALUE(LW(1), STRING("a_dai_3"))
    SET_VALUE(LW(2), 0)
    SET_VALUE(LW(3), -75)
    SET_VALUE(LW(4), 2000)
    SET_VALUE(LW(5), 500)
    SET_VALUE(LW(6), 1)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(12), 0)
    SPAWN_EVENT(PTR(moving_floor))
    CALL(evt_mobj_tornadoswitch_blue, 0, STRING("switch00"), -125, 0, 0, PTR(evt_switch_00), GSWF(1345))
    CALL(evt_mobj_tornadoswitch_blue, 0, STRING("switch01"), 125, 0, 0, PTR(evt_switch_01), GSWF(1346))
    CALL(evt_mobj_powerupblk, STRING("pblk1\0\0"), 125, 160, -100, 0, GSWF(5534), 0)
    RETURN
EVT_END()

