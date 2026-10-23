#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "evt/evt_bero.h"
#include "aji.h"

USER_FUNC(camAtY);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(slit_chk);

__declspec(section ".data") u64 fd_aji_08_negone_one_374;
__declspec(section ".data") s32 fd_aji_08_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_08___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_08___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_08_one_negone_373;
__declspec(section ".data") s32 fd_aji_08___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_08_one_381[1];
__declspec(section ".data") u64 fd_aji_08_negone_one_360;
__declspec(section ".data") s32 fd_aji_08_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_08___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_08___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_08_one_negone_359;
__declspec(section ".data") s32 fd_aji_08___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_08_one_364[1];
static s32 s_door_open[22];
static s32 s_door_close[22];
s32 evt_slit0[15];
s32 evt_slit1[15];
s32 evt_slit2[15];
static s32 bero_entry_data[75];
s32 heya_tenura_onoff[68];
s32 aji_08_init_evt[148];

__declspec(section ".data") u64 fd_aji_08_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_08_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_08___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_08___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_08_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_08___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_08_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_08_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_08_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_08___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_08___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_08_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_08___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_08_one_364[] = {
    1065353216,
};

static EVT_BEGIN(s_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.16601563f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_2"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_1"), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.16601563f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_2"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("S_door1_1"), LW(0), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_slit0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_bero_mapchange, STRING("aji_06"), STRING("tenjo"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_slit1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_bero_mapchange, STRING("aji_07"), STRING("tenjo"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_slit2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_bero_mapchange, STRING("aji_09"), STRING("tenjo"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"s_bero_1", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"aji_01", (s32)"n_bero_3", 327685, (s32)s_door_close, (s32)s_door_open, (s32)"s_bero_2",
    251658240, 20000, 100000, 0, 0, -1, 0, 0,
    (s32)evt_slit0, (s32)"aji_06", (s32)"tenjo", 65537, 0, 0, (s32)"s_bero_3", 251658240,
    20000, 100000, 0, 0, -1, 0, 0, (s32)evt_slit1,
    (s32)"aji_07", (s32)"tenjo", 65537, 0, 0, (s32)"s_bero_4", 251658240, 20000,
    100000, 0, 0, -1, 0, 0, (s32)evt_slit2, (s32)"aji_09",
    (s32)"tenjo", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(heya_tenura_onoff)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_heya"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_tenura"), 1)
    SET_VALUE(LW(0), 0)
    LOOP(0)
        CALL(camAtY, LW(1))
        IF_INT_GREATER_OR_EQUAL(LW(1), 180)
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_heya"), 1)
                CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_tenura"), 1)
                SET_VALUE(LW(0), 1)
            END_IF
            ELSE
            IF_INT_EQUAL(LW(0), 1)
                CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_heya"), 1)
                CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_tenura"), 1)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(aji_08_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI2"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT_GET_ID(PTR(heya_tenura_onoff), LW(0))
    SPAWN_EVENT(PTR(evt_emergency))
    BEGIN_INLINE_EVENT
        CALL(slit_chk)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("bari"), 1, 0)
    CALL(evt_map_playanim, STRING("awa1"), 1, 0)
    CALL(evt_map_playanim, STRING("awa2"), 1, 0)
    CALL(evt_item_entry, STRING("item00"), 125, -975, 170, 75, 16, GSWF(5666), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mapobj_get_position, STRING("S_ita"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_AMB_CEILING_MOVE1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_sub_intpl_msec_init, 11, -100, 100, 1000)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_ita"), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
            CALL(evt_mapobj_get_position, STRING("S_ita"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_AMB_CEILING_MOVE1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_sub_intpl_msec_init, 11, 100, -100, 1000)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_rotate, 1, STRING("S_ita"), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        CALL(evt_npc_check_delete, STRING("軍団ザコ魔法使い"))
    END_IF
    RETURN
EVT_END()

USER_FUNC(camAtY) {
    s32* args = event->args;

    evtSetValue(event, args[0], camGetPtr(CAMERA_3D)->cameraAt.y);
    return EVT_RETURN_DONE;
}
USER_FUNC(slit_chk) {
    MarioWork* mario = marioGetPtr();

    if (mario->flags & 0x100000) {
        if ((mario->position.x < -200.0f || mario->position.x > 300.0f) && mario->position.y < 169.0f &&
            mario->position.y > 160.0f) {
            camCtrlOff(CAMERA_3D);
            evtStopID(event->lwData[0]);
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_BLOCK;
}
