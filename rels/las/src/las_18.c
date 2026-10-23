#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/mobjdrv.h"
#include "driver/animdrv.h"
#include "evt/evt_bero.h"
#include "las.h"

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_floatswitch_blue);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_hit_onoff);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_set_position);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_party_get_status);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(get_mobj_seq);
USER_FUNC(switch_alpha_off);
USER_FUNC(switch_set_alpha);

__declspec(section ".data") u64 fd_las_18_negone_one_374;
__declspec(section ".data") s32 fd_las_18_neg_one_382[1];
__declspec(section ".data") s32 fd_las_18___local_PI_383[1];
__declspec(section ".data") s32 fd_las_18___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_18_one_negone_373;
__declspec(section ".data") s32 fd_las_18___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_18_one_381[1];
__declspec(section ".data") u64 fd_las_18_negone_one_360;
__declspec(section ".data") s32 fd_las_18_neg_one_365[1];
__declspec(section ".data") s32 fd_las_18___local_PI_366[1];
__declspec(section ".data") s32 fd_las_18___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_18_one_negone_359;
__declspec(section ".data") s32 fd_las_18___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_18_one_364[1];
static __declspec(section ".data") s32 w_door_close[12];
static __declspec(section ".data") s32 w_door_open[12];
static s32 bero_entry_data[30];
static s32 box_evt[30];
s32 vivian_check[92];
static s32 switch_evt[48];
static s32 hint_plate[14];
s32 las_18_init_evt[71];

__declspec(section ".data") u64 fd_las_18_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_18_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_18___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_18___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_18_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_18___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_18_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_18_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_18_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_18___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_18___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_18_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_18___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_18_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("S_door1"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 65537, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_10", (s32)"se_bero_2", 327685, (s32)w_door_close, (s32)w_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), 45, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

USER_FUNC(switch_set_alpha) {
    s32 alpha = evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("switch");

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    if (alpha > 0x24) {
        mobj->flags &= ~2;
    } else {
        mobj->flags |= 2;
    }
    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){255, 255, 255, alpha});
    animPoseSetMaterialFlagOn(mobj->poseId, 0x40);
    return EVT_RETURN_DONE;
}

USER_FUNC(switch_alpha_off) {
    MapObjectEntry* mobj = mobjNameToPtrNoAssert("switch");

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    mobj->flags &= ~2;
    animPoseSetMaterialEvtColor(mobj->poseId, (GXColor){255, 255, 255, 255});
    animPoseSetMaterialFlagOff(mobj->poseId, 0x40);
    return EVT_RETURN_DONE;
}

EVT_BEGIN(vivian_check)
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(15), 0)
    LOOP(0)
        CALL(get_mobj_seq, STRING("switch"), LW(0))
        IF_INT_GREATER(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_mario_get_party, LW(0))
        IF_INT_EQUAL(LW(0), 6)
            CALL(evt_party_get_status, 6, LW(0))
            IF_INT_EQUAL(LW(0), 2)
                ADD(LW(15), 4)
                ELSE
                SUBTRACT(LW(15), 4)
            END_IF
            ELSE
            SUBTRACT(LW(15), 4)
        END_IF
        IF_INT_GREATER(LW(15), 160)
            SET_VALUE(LW(15), 160)
        END_IF
        IF_INT_LESS(LW(15), 0)
            SET_VALUE(LW(15), 0)
        END_IF
        CALL(switch_set_alpha, LW(15))
        IF_INT_EQUAL(LW(15), 160)
            IF_INT_EQUAL(GSWF(4382), 0)
                SET_VALUE(GSWF(4382), 1)
                CALL(evt_snd_bgmoff, 1024)
                CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
                WAIT_MS(2000)
                CALL(evt_snd_bgmoff, 513)
                CALL(evt_snd_bgmon, 288, 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

USER_FUNC(get_mobj_seq) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtrNoAssert((const char*)evtGetValue(event, args[0]));

    if (mobj == NULL) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], mobj->state);
    }
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(switch_evt)
    CALL(switch_alpha_off)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1250)
    CALL(evt_cam3d_evt_set, 0, 100, 363, 0, 30, -30, 500, 11)
    WAIT_MS(1000)
    CALL(evt_mobj_set_position, STRING("box"), 0, -30, 0)
    CALL(evt_mobj_flag_onoff, 0, STRING("box"), 16448)
    CALL(evt_mobj_hit_onoff, STRING("box"), 1)
    SET_VALUE(LW(0), STRING("box"))
    CALL_CHILD(PTR(box_syutugen))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(hint_plate)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg8_las_43"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(las_18_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_floatswitch_blue, 0, STRING("switch"), 75, 60, 0, PTR(switch_evt), GSWF(4352))
    CALL(evt_mobj_flag_onoff, 1, STRING("switch"), 2)
    IF_INT_EQUAL(GSWF(4352), 0)
        SPAWN_EVENT(PTR(vivian_check))
    END_IF
    CALL(evt_mobj_itembox, STRING("box"), 0, 0, 0, 0, 0, PTR(box_evt), GSWF(4369))
    IF_INT_EQUAL(GSWF(4352), 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("box"), 16384)
        CALL(evt_mobj_hit_onoff, STRING("box"), 0)
    END_IF
    CALL(evt_run_case_evt, 9, 1, STRING("A_pure\0"), 0, PTR(hint_plate), 0)
    RETURN
EVT_END()

