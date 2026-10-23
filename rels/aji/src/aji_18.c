#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "driver/fadedrv.h"

s32 key_list[4];

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_del_case_evt);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_party);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_all_party_recovery);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_mario_recovery);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_win_item_select);
#ifdef VERSION_G8ME01
USER_FUNC(N_evt_sub_status_gauge_force_update);
#endif
static USER_FUNC(make_list);
static USER_FUNC(sysflag);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_emergency[];

__declspec(section ".data") u64 fd_aji_18_negone_one_374;
__declspec(section ".data") s32 fd_aji_18_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_18___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_18___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_18_one_negone_373;
__declspec(section ".data") s32 fd_aji_18___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_18_one_381[1];
__declspec(section ".data") u64 fd_aji_18_negone_one_360;
__declspec(section ".data") s32 fd_aji_18_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_18___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_18___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_18_one_negone_359;
__declspec(section ".data") s32 fd_aji_18___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_18_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
s32 evt_machine[266];
s32 key_lock_koujyou[14];
static s32 evt_koopa_after[118];
#ifdef VERSION_G8ME01
s32 aji_18_init_evt[301];
#else
s32 aji_18_init_evt[299];
#endif

static USER_FUNC(make_list) {
    s32 n = 0;

    if ((s32)pouchCheckItem(0x1D) > 0) {
        key_list[n++] = 0x1D;
    }
    if ((s32)pouchCheckItem(0x1E) > 0) {
        key_list[n++] = 0x1E;
    }
    if ((s32)pouchCheckItem(0x1F) > 0) {
        key_list[n++] = 0x1F;
    }
    key_list[n] = -1;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_aji_18_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_18_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_18___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_18___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_18_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_18___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_18_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_18_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_18_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_18___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_18___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_18_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_18___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_18_one_364[] = {
    1065353216,
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
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"aji_01", (s32)"e_bero_4", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero",
    65546, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"aji_13", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_machine)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_67"), 0, 0)
    SET_VALUE(LW(10), 0)
    CALL(evt_pouch_check_item, 29, LW(11))
    ADD(LW(10), LW(11))
    CALL(evt_pouch_check_item, 30, LW(11))
    ADD(LW(10), LW(11))
    CALL(evt_pouch_check_item, 31, LW(11))
    ADD(LW(10), LW(11))
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    CALL(make_list)
    CALL(evt_win_item_select, 0, PTR(key_list), LW(10), 0)
    SWITCH(LW(10))
        CASE_EQUAL(29)
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi1_aka"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi1_mid"), 1)
            SET_VALUE(GSWF(4191), 1)
            CALL(evt_pouch_remove_item, LW(10), LW(1))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_exit_case_evt)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg7_aji_67_01"), 0, 0)
        END_IF
        CASE_EQUAL(30)
        IF_INT_EQUAL(LW(0), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi2_aka"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi2_mid"), 1)
            SET_VALUE(GSWF(4192), 1)
            CALL(evt_pouch_remove_item, LW(10), LW(1))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_exit_case_evt)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg7_aji_67_01"), 0, 0)
        END_IF
        CASE_EQUAL(31)
        IF_INT_EQUAL(LW(0), 2)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi3_aka"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi3_mid"), 1)
            SET_VALUE(GSWF(4193), 1)
            CALL(evt_pouch_remove_item, LW(10), LW(1))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_exit_case_evt)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg7_aji_67_01"), 0, 0)
        END_IF
        CASE_DEFAULT
    END_SWITCH
    IF_INT_EQUAL(GSWF(4191), 1)
        IF_INT_EQUAL(GSWF(4192), 1)
            IF_INT_EQUAL(GSWF(4193), 1)
                SET_VALUE(GSW(0), 369)
                CALL(evt_del_case_evt, 0, GW(10))
                SET_VALUE(LW(0), STRING("e_bero"))
                CALL_CHILD(PTR(bero_case_switch_on))
                CALL(evt_cam3d_evt_set, -140, 90, 369, 150, 60, -98, 500, 11)
                WAIT_MS(1200)
                CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_lights1_m"), 1)
                CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_r"), 1)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_LAMP1"), LW(0), LW(1), LW(2), 0)
                WAIT_MS(700)
                CALL(evt_cam3d_evt_off, 11, 0)
            END_IF
        END_IF
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(key_lock_koujyou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg7_aji_67_02"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_koopa_after)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 75, 0, FLOAT(80.0f))
    END_INLINE_EVENT
    CALL(evt_party_move_pos2, 0, 115, 0, FLOAT(80.0f))
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(500)
    CALL(evt_fade_end_wait)
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print_party, STRING("stg7_aji_43"))
    CALL(evt_cam3d_evt_set, 95, 55, 292, 95, 41, -8, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg7_aji_44"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_THINK1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_Z"))
    WAIT_MS(1500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg7_aji_45"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

static USER_FUNC(sysflag) {
    if (gp->flags & 1) {
        gp->flags &= ~1;
        fadeEntry(0x1C, 0, (GXColor){0, 0, 0, 0});
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(aji_18_init_evt)
    CALL(sysflag)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI1"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 369)
        SET_VALUE(GSWF(4191), 1)
        SET_VALUE(GSWF(4192), 1)
        SET_VALUE(GSWF(4193), 1)
    END_IF
    IF_INT_EQUAL(GSWF(4191), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi1_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi1_mid"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi1_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi1_mid"), 1)
    END_IF
    IF_INT_EQUAL(GSWF(4192), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi2_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi2_mid"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi2_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi2_mid"), 1)
    END_IF
    IF_INT_EQUAL(GSWF(4193), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi3_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi3_mid"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_kagi3_aka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_kagi3_mid"), 1)
    END_IF
    SET_VALUE(LW(0), 0)
    CALL(evt_pouch_check_item, 29, LW(1))
    ADD(LW(0), LW(1))
    CALL(evt_pouch_check_item, 30, LW(1))
    ADD(LW(0), LW(1))
    CALL(evt_pouch_check_item, 31, LW(1))
    ADD(LW(0), LW(1))
    IF_INT_EQUAL(GSWF(4191), 0)
        SET_VALUE(LW(0), 0)
        CALL(evt_run_case_evt, 9, 1, STRING("A_kagi1"), 0, PTR(evt_machine), 0)
    END_IF
    IF_INT_EQUAL(GSWF(4192), 0)
        SET_VALUE(LW(0), 1)
        CALL(evt_run_case_evt, 9, 1, STRING("A_kagi2"), 0, PTR(evt_machine), 0)
    END_IF
    IF_INT_EQUAL(GSWF(4193), 0)
        SET_VALUE(LW(0), 2)
        CALL(evt_run_case_evt, 9, 1, STRING("A_kagi3"), 0, PTR(evt_machine), 0)
    END_IF
    IF_INT_LESS(GSW(0), 369)
        CALL(evt_run_case_evt, 9, 1, STRING("e_bero"), 0, PTR(key_lock_koujyou), GW(10))
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_m"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_lights1_r"), 1)
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_lights1_m"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_r"), 1)
    END_IF
    SWITCH(GSW(0))
        CASE_BETWEEN(373, 375)
        CALL(evt_run_case_evt, 9, 1, STRING("e_bero"), 0, PTR(key_lock_koujyou), 0)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_lights1_m"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_lights1_r"), 1)
    END_SWITCH
    SWITCH(GSW(0))
        CASE_BETWEEN(373, 375)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("e_bero"))
            CALL(evt_mario_get_party, LW(15))
            IF_INT_EQUAL(LW(15), 0)
                CALL(evt_mario_set_party, 0, 1)
                CALL(evt_party_run, 0)
#ifdef VERSION_G8ME01
            END_IF
#endif
                CALL(evt_pouch_mario_recovery)
                CALL(evt_pouch_all_party_recovery)
#ifdef VERSION_G8ME01
            CALL(N_evt_sub_status_gauge_force_update)
#else
            END_IF
#endif
            SPAWN_EVENT(PTR(evt_koopa_after))
        END_IF
    END_SWITCH
    SPAWN_EVENT(PTR(evt_emergency))
    RETURN
EVT_END()

