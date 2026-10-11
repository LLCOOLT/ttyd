#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "party.h"
#include "manager/evtmgr_cmd.h"
#include "driver/mobjdrv.h"

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_get_name_hitobj_head);
USER_FUNC(evt_mario_get_name_hitobj_ride);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_set_hosei_xyz);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_float_blk);
USER_FUNC(evt_mobj_get_kindname);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_get_y_position);
USER_FUNC(evt_mobj_jumpstand_blue);
USER_FUNC(evt_mobj_set_y_position);
USER_FUNC(evt_mobj_switch_float_blk);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_party_get_name_hitobj_head);
USER_FUNC(evt_party_get_name_hitobj_ride);
USER_FUNC(evt_party_set_hosei_xyz);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfx_pos);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(set_mobj_y_position);
static USER_FUNC(set_party_y_pos);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 hikari_evt[];

__declspec(section ".data") u64 fd_las_21_negone_one_374;
__declspec(section ".data") s32 fd_las_21_neg_one_382[1];
__declspec(section ".data") s32 fd_las_21___local_PI_383[1];
__declspec(section ".data") s32 fd_las_21___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_21_one_negone_373;
__declspec(section ".data") s32 fd_las_21___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_21_one_381[1];
__declspec(section ".data") u64 fd_las_21_negone_one_360;
__declspec(section ".data") s32 fd_las_21_neg_one_365[1];
__declspec(section ".data") s32 fd_las_21___local_PI_366[1];
__declspec(section ".data") s32 fd_las_21___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_21_one_negone_359;
__declspec(section ".data") s32 fd_las_21___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_21_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 e1_door_close[22];
static s32 e1_door_open[22];
static s32 e2_door_close[22];
static s32 e2_door_open[22];
static s32 bero_entry_data[75];
static s32 w_bero_mapchg[15];
s32 floatblk_stop_se[47];
s32 floatblk_shake[27];
s32 floatblk_evt[336];
s32 floatblk21_1_evt[62];
s32 floatblk21_2_evt[62];
s32 las_21_init_evt[211];

__declspec(section ".data") u64 fd_las_21_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_21_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_21___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_21___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_21_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_21___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_21_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_21_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_21_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_21___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_21___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_21_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_21___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_21_one_364[] = {
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

static EVT_BEGIN(e1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(e1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_r_02"), 0, LW(0), 0)
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

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_19", (s32)"e_bero_1", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"e_bero_1",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_23", (s32)"w_bero", 327685, (s32)e1_door_close, (s32)e1_door_open, (s32)"e_bero_2", 65542,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"las_23", (s32)"w_bero", 327685, (s32)e2_door_close, (s32)e2_door_open, (s32)"n_bero", 0, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"las_20",
    (s32)"s_bero_2", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

static s32 w_bero_mapchg[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_19", (s32)"e_bero_2", 327685, (s32)w_door_close, (s32)w_door_open,
};

EVT_BEGIN(floatblk_stop_se)
    CALL(evt_mobj_get_position, LW(15), LW(0), LW(1), LW(2))
    CALL(evt_mobj_get_kindname, LW(15), LW(3))
    SET_VALUE(LF(0), 0)
    IF_STR_EQUAL(LW(3), STRING("MOBJ_green_big02_FlowBlock"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(3), STRING("MOBJ_purple_big02_FlowBlock"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(3), STRING("MOBJ_orange_big02_FlowBlock"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLOCK_B_FLOAT_STOP1"), LW(0), LW(1), LW(2), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(floatblk_shake)
    CALL(evt_sub_intpl_init, 11, 10, 3, 4)
    LABEL(0)
    CALL(evt_sub_intpl_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(evt_cam_shake, 4, FLOAT(0.0f), LW(0), 100)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(floatblk_evt)
    SET_VALUE(LW(15), LW(0))
    SET_VALUE(LW(14), LW(1))
    SET_VALUE(LW(13), LW(2))
    SET_VALUE(LW(12), LW(3))
    SET_VALUE(LW(11), LW(4))
    IF_INT_LESS(LW(12), LW(11))
        SET_FLOAT_VALUE(LW(10), FLOAT(0.099609375f))
        SET_FLOAT_VALUE(LW(9), FLOAT(0.049804688f))
        SET_VALUE(LF(1), 0)
        ELSE
        SET_FLOAT_VALUE(LW(10), FLOAT(-0.099609375f))
        SET_FLOAT_VALUE(LW(9), FLOAT(-0.049804688f))
        SET_VALUE(LF(1), 1)
    END_IF
    SPAWN_EVENT(PTR(floatblk_shake))
    WAIT_MS(500)
    CALL(evt_mobj_get_position, LW(15), LW(0), LW(1), LW(2))
    CALL(evt_mobj_get_kindname, LW(15), LW(3))
    SET_VALUE(LF(0), 0)
    IF_STR_EQUAL(LW(3), STRING("MOBJ_green_big02_FlowBlock"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(3), STRING("MOBJ_purple_big02_FlowBlock"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(3), STRING("MOBJ_orange_big02_FlowBlock"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(1), 0)
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLOCK_B_FLOAT_MOVE1"), LW(0), LW(1), LW(2), LW(8))
            ELSE
            CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLOCK_S_FLOAT_MOVE1"), LW(0), LW(1), LW(2), LW(8))
        END_IF
        ELSE
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLOCK_B_FLOAT_DOWN1"), LW(0), LW(1), LW(2), 0)
            ELSE
            CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_BLOCK_S_FLOAT_DOWN1"), LW(0), LW(1), LW(2), 0)
        END_IF
        SET_VALUE(LW(8), -1)
    END_IF
    CALL(evt_mobj_get_y_position, LW(15), LW(7))
    LOOP(0)
        SET_VALUE(LF(0), 0)
        IF_INT_EQUAL(LF(1), 1)
            CALL(evt_mario_get_name_hitobj_head, LW(0))
            IF_STR_EQUAL(LW(0), LW(14))
                SET_VALUE(LF(0), 1)
            END_IF
            CALL(evt_mario_get_party, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(evt_party_get_name_hitobj_head, 0, LW(0))
                IF_STR_EQUAL(LW(0), LW(14))
                    SET_VALUE(LF(0), 1)
                END_IF
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            GOTO(50)
        END_IF
        CALL(evt_mobj_exec_cancel, LW(13))
        SET_VALUE(LW(0), LW(12))
        SET_VALUE(LW(12), LW(11))
        SET_VALUE(LW(11), LW(0))
        IF_INT_EQUAL(LF(1), 0)
            SET_FLOAT_VALUE(LW(10), FLOAT(-0.099609375f))
            SET_FLOAT_VALUE(LW(9), FLOAT(-0.049804688f))
            SET_VALUE(LF(1), 1)
            ELSE
            SET_FLOAT_VALUE(LW(10), FLOAT(0.099609375f))
            SET_FLOAT_VALUE(LW(9), FLOAT(0.099609375f))
            SET_VALUE(LF(1), 0)
        END_IF
        LABEL(50)
        CALL(evt_mobj_get_y_position, LW(15), LW(0))
        ADD_FLOAT(LW(0), LW(10))
        CALL(set_mobj_y_position, LW(15), LW(0))
        SET_VALUE(LF(0), 0)
        IF_INT_EQUAL(LF(1), 0)
            IF_INT_GREATER_OR_EQUAL(LW(0), LW(11))
                CALL(evt_mobj_set_y_position, LW(15), LW(11))
                SET_VALUE(LF(0), 1)
            END_IF
            ELSE
            IF_INT_LESS_OR_EQUAL(LW(0), LW(11))
                CALL(evt_mobj_set_y_position, LW(15), LW(11))
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        CALL(evt_mobj_get_position, LW(15), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfx_pos, LW(8), LW(0), LW(1), LW(2))
        IF_INT_NOT_EQUAL(LF(1), 0)
            CALL(evt_mario_get_name_hitobj_ride, LW(1))
            IF_STR_EQUAL(LW(1), LW(14))
                CALL(evt_mario_set_hosei_xyz, FLOAT(0.0f), LW(10), FLOAT(0.0f))
            END_IF
            CALL(evt_mario_get_party, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(evt_party_get_name_hitobj_ride, 0, LW(0))
                IF_STR_EQUAL(LW(0), LW(14))
                    CALL(evt_party_set_hosei_xyz, 0, FLOAT(0.0f), LW(10), FLOAT(0.0f))
                END_IF
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 1)
            BREAK_LOOP
        END_IF
        ADD_FLOAT(LW(10), LW(9))
        IF_INT_LESS_OR_EQUAL(LW(10), FLOAT(-2.0f))
            SET_FLOAT_VALUE(LW(10), FLOAT(-2.0f))
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(10), FLOAT(2.0f))
            SET_FLOAT_VALUE(LW(10), FLOAT(2.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_sfxoff, LW(8))
    SPAWN_EVENT(PTR(floatblk_stop_se))
    IF_INT_EQUAL(LF(1), 1)
        SPAWN_EVENT(PTR(floatblk_shake))
        WAIT_MS(1000)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(floatblk21_1_evt)
    SET_TYPE(239)
    IF_INT_EQUAL(LSWF(8), 0)
        SET_VALUE(LW(0), STRING("21blk1"))
        SET_VALUE(LW(1), STRING("MOBJ_21blk1"))
        SET_VALUE(LW(2), STRING("21switch1"))
        SET_VALUE(LW(3), -130)
        SET_VALUE(LW(4), -580)
        SET_VALUE(LSWF(8), 1)
        ELSE
        SET_VALUE(LW(0), STRING("21blk1"))
        SET_VALUE(LW(1), STRING("MOBJ_21blk1"))
        SET_VALUE(LW(2), STRING("21switch1"))
        SET_VALUE(LW(3), -580)
        SET_VALUE(LW(4), -130)
        SET_VALUE(LSWF(8), 0)
    END_IF
    CALL_CHILD(PTR(floatblk_evt))
    CALL(evt_mobj_get_y_position, STRING("21blk1"), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), -130)
        SET_VALUE(LSWF(8), 0)
        ELSE
        SET_VALUE(LSWF(8), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(floatblk21_2_evt)
    SET_TYPE(239)
    IF_INT_EQUAL(LSWF(9), 0)
        SET_VALUE(LW(0), STRING("21blk2"))
        SET_VALUE(LW(1), STRING("MOBJ_21blk2"))
        SET_VALUE(LW(2), STRING("21switch2"))
        SET_VALUE(LW(3), -130)
        SET_VALUE(LW(4), -580)
        SET_VALUE(LSWF(9), 1)
        ELSE
        SET_VALUE(LW(0), STRING("21blk2"))
        SET_VALUE(LW(1), STRING("MOBJ_21blk2"))
        SET_VALUE(LW(2), STRING("21switch2"))
        SET_VALUE(LW(3), -580)
        SET_VALUE(LW(4), -130)
        SET_VALUE(LSWF(9), 0)
    END_IF
    CALL_CHILD(PTR(floatblk_evt))
    CALL(evt_mobj_get_y_position, STRING("21blk2"), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), -130)
        SET_VALUE(LSWF(9), 0)
        ELSE
        SET_VALUE(LSWF(9), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(las_21_init_evt)
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST1"))
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST3"))
    END_IF
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    IF_INT_LESS(GSW(0), 390)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_under"), 1)
        CALL(evt_hitobj_onoff, STRING("A_under"), 1, 0)
        CALL(evt_npc_check_delete, STRING("ワンワン２"))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_yuka"), 1)
        CALL(evt_hitobj_onoff, STRING("A_be"), 1, 0)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("w_bero"), PTR(w_bero_mapchg))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
        CALL(evt_npc_check_delete, STRING("ワンワン１"))
        SPAWN_EVENT(PTR(hikari_evt))
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 390)
        IF_INT_EQUAL(GSWF(4353), 0)
            SET_VALUE(LW(0), -220)
            ELSE
            SET_VALUE(LW(0), -580)
        END_IF
        IF_INT_EQUAL(GSWF(4354), 0)
            SET_VALUE(LW(1), -120)
            ELSE
            SET_VALUE(LW(1), -580)
        END_IF
        SET_VALUE(LW(2), -580)
        SET_VALUE(LSWF(8), 1)
        SET_VALUE(LW(3), -580)
        SET_VALUE(LSWF(9), 1)
        CALL(evt_mobj_float_blk, STRING("19blk1"), -350, LW(0), 0, 2, 2, 0, 0)
        CALL(evt_mobj_float_blk, STRING("19blk2"), -250, LW(1), 0, 0, 2, 0, 0)
        CALL(evt_mobj_float_blk, STRING("21blk1"), 50, LW(2), 0, 1, 2, 0, 0)
        CALL(evt_mobj_float_blk, STRING("21blk2"), 150, LW(3), 0, 3, 2, 0, 0)
        CALL(evt_mobj_flag_onoff, 1, STRING("19blk1"), 128)
        CALL(evt_mobj_flag_onoff, 1, STRING("19blk2"), 128)
        CALL(evt_mobj_flag_onoff, 1, STRING("21blk1"), 128)
        CALL(evt_mobj_flag_onoff, 1, STRING("21blk2"), 128)
        CALL(evt_mobj_switch_float_blk, STRING("21switch1"), 175, -480, -67, STRING("21blk1"), 1, PTR(floatblk21_1_evt), 0)
        CALL(evt_mobj_switch_float_blk, STRING("21switch2"), 300, -30, 15, STRING("21blk2"), 3, PTR(floatblk21_2_evt), 0)
    END_IF
    CALL(evt_mobj_jumpstand_blue, 0, STRING("jump"), 700, -650, -580, 75, 0, 0)
    CALL(evt_mobj_flag_onoff, 0, STRING("jump"), 64)
    RETURN
EVT_END()

static USER_FUNC(set_party_y_pos) {
    s32* args = event->args;
    PartyEntry* party = partyGetPtr(0);

    if (party == NULL) {
        return EVT_RETURN_DONE;
    }
    party->position.y = evtGetFloat(event, args[0]);
    return EVT_RETURN_DONE;
}
USER_FUNC(set_mobj_y_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    MapObjectEntry* mobj = mobjNameToPtr(name);

    mobj->position.y = y;
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}
