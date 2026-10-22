#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

u16 toge_flag;

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_area_check);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(get_toge_name);
USER_FUNC(toge_check_flag);
USER_FUNC(toge_flag_onoff);
extern s32 evt_bero_info_run[];
extern s32 evt_gazigazi_entry[];

__declspec(section ".data") u64 fd_las_03_negone_one_374;
__declspec(section ".data") s32 fd_las_03_neg_one_382[1];
__declspec(section ".data") s32 fd_las_03___local_PI_383[1];
__declspec(section ".data") s32 fd_las_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_03_one_negone_373;
__declspec(section ".data") s32 fd_las_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_03_one_381[1];
__declspec(section ".data") u64 fd_las_03_negone_one_360;
__declspec(section ".data") s32 fd_las_03_neg_one_365[1];
__declspec(section ".data") s32 fd_las_03___local_PI_366[1];
__declspec(section ".data") s32 fd_las_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_03_one_negone_359;
__declspec(section ".data") s32 fd_las_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_03_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[45];
static __declspec(section ".data") s32 dmgRetPoint[12];
s32 toge_data[18];
s32 toge_evt_sub[121];
s32 toge_evt[86];
s32 las_03_init_evt[32];

__declspec(section ".data") u64 fd_las_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_03_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_02", (s32)"e_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero_1",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_04", (s32)"w_bero", 327685, (s32)e_door_close, (s32)e_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static __declspec(section ".data") s32 dmgRetPoint[] = {
    (s32)"A_yuka_02", 0, -998637568, 0, (s32)"A_yuka_03", 0, -998637568, 0,
    0, 0, 0, 0,
};

s32 toge_data[] = {
    (s32)"S_toge_01", (s32)"A_toge_01", (s32)"S_toge_02", (s32)"A_toge_02", (s32)"S_toge_03", (s32)"A_toge_03", (s32)"S_toge_04", (s32)"A_toge_04",
    (s32)"S_toge_05", (s32)"A_toge_05", (s32)"S_toge_06", (s32)"A_toge_06", (s32)"S_toge_07", (s32)"A_toge_07", (s32)"S_toge_08", (s32)"A_toge_08",
    (s32)"S_toge_09", (s32)"A_toge_09",
};

EVT_BEGIN(toge_evt_sub)
    SET_VALUE(LW(2), LW(0))
    CALL(get_toge_name, LW(2), LW(3), LW(4))
    CALL(toge_check_flag, LW(2), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(toge_flag_onoff, LW(2), 1)
    CALL(evt_mapobj_get_position, LW(3), LW(7), LW(8), LW(9))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_FLOOR_TRAP1"), LW(7), LW(8), LW(9), 0)
    CALL(evt_sub_intpl_msec_init, 0, 0, 30, 150)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_trans, 0, LW(3), 0, LW(0), 0)
    CALL(evt_hit_bind_update, LW(4))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, LW(3), LW(7), LW(8), LW(9))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_FLOOR_TRAP2"), LW(7), LW(8), LW(9), 0)
    CALL(evt_sub_intpl_msec_init, 0, 30, 0, 400)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_trans, 0, LW(3), 0, LW(0), 0)
    CALL(evt_hit_bind_update, LW(4))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_mapobj_trans, 0, LW(3), 0, 0, 0)
    CALL(evt_hit_bind_update, LW(4))
    CALL(toge_flag_onoff, LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(toge_evt)
    CALL(evt_hit_damage_return_set, PTR(dmgRetPoint))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    SET_INT_READ_ADDR(PTR(toge_data))
    LOOP(9)
        READ_INT2(LW(0), LW(1))
        CALL(evt_hit_bind_mapobj, LW(1), LW(0))
    END_LOOP
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    LOOP(0)
        CALL(evt_mario_get_motion, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 32)
            CALL(evt_mario_get_pos, 0, LW(1), LW(2), LW(3))
            SET_VALUE(LW(4), 0)
            LOOP(0)
                CALL(get_toge_name, LW(4), LW(5), LW(6))
                CALL(evt_mapobj_get_position, LW(5), LW(6), LW(7), LW(8))
                CALL(evt_sub_area_check, 1, LW(6), LW(8), 90, LW(1), LW(3), LW(9))
                IF_INT_EQUAL(LW(9), 1)
                    SET_VALUE(LW(0), LW(4))
                    SPAWN_EVENT(PTR(toge_evt_sub))
                END_IF
                ADD(LW(4), 1)
                IF_INT_GREATER_OR_EQUAL(LW(4), 9)
                    BREAK_LOOP
                END_IF
            END_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(las_03_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_badgeblk, STRING("mobj_badge_gat\0"), -350, 0, -100, 264, 0, GSWF(4375), 1)
    SPAWN_EVENT(PTR(toge_evt))
    RETURN
EVT_END()

USER_FUNC(get_toge_name) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], toge_data[idx * 2]);
    evtSetValue(event, args[2], toge_data[idx * 2 + 1]);
    return EVT_RETURN_DONE;
}
USER_FUNC(toge_check_flag) {
    s32* args = event->args;
    s32 bit = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], toge_flag & (1 << bit));
    return EVT_RETURN_DONE;
}
USER_FUNC(toge_flag_onoff) {
    s32* args = event->args;
    s32 bit = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);

    if (on) {
        toge_flag |= (1 << bit);
    } else {
        toge_flag &= ~(1 << bit);
    }
    return EVT_RETURN_DONE;
}
