#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/mapdrv.h"
#include "driver/hitdrv.h"
#include "driver/effdrv.h"
#include "evt/evt_bero.h"

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_scale);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_sub_get_sincos);
USER_FUNC(hi_onoff);
USER_FUNC(mugen_kairou_get_list);

__declspec(section ".data") u64 fd_las_08_negone_one_374;
__declspec(section ".data") s32 fd_las_08_neg_one_382[1];
__declspec(section ".data") s32 fd_las_08___local_PI_383[1];
__declspec(section ".data") s32 fd_las_08___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_08_one_negone_373;
__declspec(section ".data") s32 fd_las_08___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_08_one_381[1];
__declspec(section ".data") u64 fd_las_08_negone_one_360;
__declspec(section ".data") s32 fd_las_08_neg_one_365[1];
__declspec(section ".data") s32 fd_las_08___local_PI_366[1];
__declspec(section ".data") s32 fd_las_08___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_08_one_negone_359;
__declspec(section ".data") s32 fd_las_08___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_08_one_364[1];
static s32 w1_door_close[22];
static s32 w1_door_open[22];
static s32 w2_door_close[22];
static s32 w2_door_open[22];
static s32 e1_door_close[22];
static s32 e1_door_open[22];
static s32 e2_door_close[22];
static s32 e2_door_open[22];
static s32 door_matigai_evt[15];
s32 door_seikai_evt[19];
static s32 bero_entry_data[75];
s32 e_bero_1_matigai[15];
s32 e_bero_1_seikai[15];
s32 e_bero_2_seikai[15];
s32 taimatu_data[16];
s32 hikari_anim[52];
s32 taimatu_evt[18];
__declspec(section ".data") s32 mugen_kairou_list[7];
s32 mugen_kairou_init[96];
s32 las_08_init_evt[22];

__declspec(section ".data") u64 fd_las_08_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_08_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_08___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_08___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_08_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_08___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_08_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_08_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_08_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_08___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_08___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_08_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_08___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_08_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l1_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_l2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r1_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r1_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r1_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r2_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(door_matigai_evt)
    IF_INT_EQUAL(GSW(0), 385)
        SET_VALUE(GSW(1121), 0)
        SET_VALUE(GSWF(4325), 1)
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(door_seikai_evt)
    IF_INT_EQUAL(GSW(0), 385)
        ADD(GSW(1121), 1)
        IF_INT_GREATER_OR_EQUAL(GSW(1121), 7)
            SET_VALUE(GSW(0), 386)
        END_IF
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)door_matigai_evt, (s32)"las_07", (s32)"e_bero_1", 327685, (s32)w1_door_close, (s32)w1_door_open, (s32)"e_bero_1",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    (s32)door_seikai_evt, (s32)"las_09", (s32)"w_bero", 327685, (s32)e1_door_close, (s32)e1_door_open, (s32)"w_bero_2", 65542,
    20000, 100000, 0, 0, -1, 0, -1, (s32)door_matigai_evt,
    (s32)"las_07", (s32)"e_bero_2", 327685, (s32)w2_door_close, (s32)w2_door_open, (s32)"e_bero_2", 65542, 20000,
    100000, 0, 0, -1, 0, -1, (s32)door_matigai_evt, (s32)"las_07",
    (s32)"w_bero_2", 327685, (s32)e2_door_close, (s32)e2_door_open, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

s32 e_bero_1_matigai[] = {
    (s32)"e_bero_1", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)door_matigai_evt, (s32)"las_07", (s32)"w_bero_1", 327685, (s32)e1_door_close, (s32)e1_door_open,
};

s32 e_bero_1_seikai[] = {
    (s32)"e_bero_1", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)door_seikai_evt, (s32)"las_08", (s32)"w_bero_1", 327685, (s32)e1_door_close, (s32)e1_door_open,
};

s32 e_bero_2_seikai[] = {
    (s32)"e_bero_2", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)door_seikai_evt, (s32)"las_08", (s32)"w_bero_2", 327685, (s32)e2_door_close, (s32)e2_door_open,
};

s32 taimatu_data[] = {
    (s32)"S_hikari_01", (s32)"A_hi_01", (s32)"S_hikari_02", (s32)"A_hi_02", (s32)"S_hikari_03", (s32)"A_hi_03", (s32)"S_hikari_04", (s32)"A_hi_04",
    (s32)"S_hikari_05", (s32)"A_hi_05", (s32)"S_hikari_06", (s32)"A_hi_06", (s32)"S_hikari_07", (s32)"A_hi_07", (s32)"S_hikari_08", (s32)"A_hi_08",
};

EVT_BEGIN(hikari_anim)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    SET_VALUE(LW(0), 0)
    LOOP(0)
        CALL(evt_sub_get_sincos, LW(0), LW(1), LW(2))
        MULTIPLY_FLOAT(LW(1), FLOAT(0.19921875f))
        ADD_FLOAT(LW(1), FLOAT(0.7998047f))
        SET_INT_READ_ADDR(PTR(taimatu_data))
        LOOP(8)
            READ_INT2(LW(3), LW(4))
            CALL(evt_mapobj_scale, 0, LW(3), LW(1), LW(1), LW(1))
        END_LOOP
        ADD(LW(0), 2)
        IF_INT_GREATER_OR_EQUAL(LW(0), 360)
            SUBTRACT(LW(0), 360)
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(taimatu_evt)
    SET_INT_READ_ADDR(PTR(taimatu_data))
    LOOP(8)
        READ_INT2(LW(0), LW(1))
        CALL(evt_mapobj_flag_onoff, 0, 1, LW(0), 1)
    END_LOOP
    SPAWN_EVENT(PTR(hikari_anim))
    RETURN
EVT_END()

__declspec(section ".data") s32 mugen_kairou_list[] = {
    7, 7, 3, 3, 7, 3, 7,
};

EVT_BEGIN(mugen_kairou_init)
    CALL_CHILD(PTR(taimatu_evt))
    IF_INT_EQUAL(GSW(0), 385)
        CALL(mugen_kairou_get_list, GSW(1121), LW(0))
        CALL(hi_onoff, LW(0), 1)
        CALL(evt_seq_wait, 2)
        CALL(evt_bero_exec_wait, 65536)
        CALL(mugen_kairou_get_list, GSW(1121), LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(7)
            IF_INT_LESS(GSW(1121), 6)
                SET_VALUE(LW(0), STRING("e_bero_1"))
                CALL_CHILD(PTR(bero_case_switch_off))
                CALL(evt_bero_overwrite, STRING("e_bero_1"), PTR(e_bero_1_seikai))
                SET_VALUE(LW(0), STRING("e_bero_1"))
                CALL_CHILD(PTR(bero_case_switch_on))
            END_IF
            CASE_EQUAL(3)
            SET_VALUE(LW(0), STRING("e_bero_2"))
            CALL_CHILD(PTR(bero_case_switch_off))
            CALL(evt_bero_overwrite, STRING("e_bero_2"), PTR(e_bero_2_seikai))
            SET_VALUE(LW(0), STRING("e_bero_2"))
            CALL_CHILD(PTR(bero_case_switch_on))
            SET_VALUE(LW(0), STRING("e_bero_1"))
            CALL_CHILD(PTR(bero_case_switch_off))
            CALL(evt_bero_overwrite, STRING("e_bero_1"), PTR(e_bero_1_matigai))
            SET_VALUE(LW(0), STRING("e_bero_1"))
            CALL_CHILD(PTR(bero_case_switch_on))
        END_SWITCH
        ELSE
        CALL(hi_onoff, 4, 1)
        CALL(hi_onoff, 5, 1)
        CALL(hi_onoff, 6, 1)
        CALL(hi_onoff, 7, 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(las_08_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT(PTR(mugen_kairou_init))
    RETURN
EVT_END()

EffectEntry* effTorchEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

USER_FUNC(hi_onoff) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    MapObject* obj = mapGetMapObj((const char*)taimatu_data[index * 2]);
    Vec pos;

    if (on) {
        obj->flags &= ~1;
        hitObjGetPos((const char*)taimatu_data[index * 2 + 1], &pos);
        effSetName(effTorchEntry(0, pos.x, pos.y, pos.z, 0.7f), (const char*)taimatu_data[index * 2 + 1]);
    } else {
        obj->flags |= 1;
        effSoftDelete(effNameToPtr((const char*)taimatu_data[index * 2 + 1]));
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(mugen_kairou_get_list) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], mugen_kairou_list[index]);
    return EVT_RETURN_DONE;
}
