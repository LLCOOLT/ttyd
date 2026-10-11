#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_eff);
USER_FUNC(evt_koopa_chk_dead);
USER_FUNC(evt_koopa_get_level);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mario_cam_off);
USER_FUNC(evt_mario_get_name_hitobj_ride);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_npc_setup);
static USER_FUNC(kpa_get_level);
USER_FUNC(kpa_status_init);
extern s32 kpa_dead[];
extern s32 kpa_fall_sub[];
extern s32 kpa_init[];
extern s32 kpa_read_item[];
extern s32 kpa_read_mobj[];
extern s32 kpa_stage_start[];
extern s32 kpa_time[];

__declspec(section ".data") u64 fd_kpa_05_negone_one_374;
__declspec(section ".data") s32 fd_kpa_05_neg_one_382[1];
__declspec(section ".data") s32 fd_kpa_05___local_PI_383[1];
__declspec(section ".data") s32 fd_kpa_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_kpa_05_one_negone_373;
__declspec(section ".data") s32 fd_kpa_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_kpa_05_one_381[1];
__declspec(section ".data") u64 fd_kpa_05_negone_one_360;
__declspec(section ".data") s32 fd_kpa_05_neg_one_365[1];
__declspec(section ".data") s32 fd_kpa_05___local_PI_366[1];
__declspec(section ".data") s32 fd_kpa_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_kpa_05_one_negone_359;
__declspec(section ".data") s32 fd_kpa_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_kpa_05_one_364[1];
static s32 kpa_act_stg3_mobj[118];
s32 kpa_act_stg3_item[79];
static s32 kpa_fall[92];
static s32 jumpstand_evt[60];
static s32 npcEnt[23];
s32 kpa_05_init_evt[44];

__declspec(section ".data") u64 fd_kpa_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_kpa_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_05_one_364[] = {
    1065353216,
};

static s32 kpa_act_stg3_mobj[] = {
    13, -231088000, -229897600, 3, -229998976, 13, -230704000, -229897600,
    2, -229997952, 14, -230524800, -229769600, 3, -229998976, 0,
    -230332800, -229795200, 5, -230230400, -229974400, 5, -230179200, -229974400,
    5, -230128000, -229974400, 5, -230076800, -229974400, 5, -230025600,
    -229974400, 5, -229974400, -229974400, 5, -229923200, -229974400, 5,
    -229872000, -229923200, 1, -229744000, -229974400, 1, -229692800, -229974400,
    1, -229692800, -229923200, 1, -229641600, -229923200, 0, -229590400,
    -230000000, 1, -229590400, -229923200, 14, -229603200, -229872000, 6,
    -229999488, 1, -229539200, -229923200, 1, -229488000, -229974400, 1,
    -229488000, -229923200, 1, -229436800, -229974400, 5, -229257600, -230000000,
    5, -229206400, -230000000, 0, -229283200, -229820800, 5, -229027200,
    -229974400, 5, -228976000, -229974400, 5, -228924800, -229948800, 5,
    -228924800, -229897600, 16, -228848000, -230000000, (s32)jumpstand_evt, 5, -228771200,
    -229948800, 5, -228771200, -229897600, 5, -228720000, -229974400, 5,
    -228668800, -229974400, 11, -228489600, -229795200, -1,
};

s32 kpa_act_stg3_item[] = {
    0, -230179200, -229820800, 0, -230128000, -229820800, 0, -230025600,
    -229820800, 0, -229974400, -229820800, 0, -229744000, -230000000, 0,
    -229692800, -230000000, 0, -229641600, -230000000, 0, -229641600, -229974400,
    0, -229641600, -229948800, 0, -229590400, -229948800, 0, -229539200,
    -229948800, 0, -229539200, -229974400, 0, -229539200, -230000000, 0,
    -229488000, -230000000, 0, -229436800, -230000000, 0, -229385600, -230000000,
    0, -229283200, -229910400, 0, -229232000, -229910400, 0, -229180800,
    -229910400, 0, -228848000, -229910400, 0, -228848000, -229872000, 0,
    -228848000, -229833600, 0, -228592000, -229987200, 0, -228592000, -229948800,
    0, -228540800, -229987200, 0, -228540800, -229948800, -1,
};

static EVT_BEGIN(kpa_fall)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        CALL(evt_koopa_chk_dead, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 1)
            BREAK_LOOP
        END_IF
        CALL(evt_mario_get_name_hitobj_ride, LW(0))
        IF_STR_EQUAL(LW(0), STRING("a_magu"))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD_FLOAT(LW(1), FLOAT(3.0f))
        ADD_FLOAT(LW(2), FLOAT(5.0f))
        CALL(kpa_get_level, LW(3))
        SWITCH(LW(3))
            CASE_EQUAL(0)
            SET_FLOAT_VALUE(LW(3), FLOAT(0.7998047f))
            CASE_EQUAL(1)
            SET_FLOAT_VALUE(LW(3), FLOAT(1.6992188f))
            CASE_EQUAL(2)
            SET_FLOAT_VALUE(LW(3), FLOAT(3.0f))
            CASE_EQUAL(3)
            SET_FLOAT_VALUE(LW(3), FLOAT(4.5f))
        END_SWITCH
        CALL(evt_eff, STRING(""), STRING("splash"), 2, LW(0), LW(1), LW(2), LW(3), 0, 0, 0, 0, 0, 0, 0)
        CALL_CHILD(PTR(kpa_fall_sub))
        ELSE
        CALL_CHILD(PTR(kpa_dead))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(jumpstand_evt)
    DELETE_EVENT(GW(15))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_koopa_get_level, GSW(1223))
        CALL(evt_bero_mapchange, STRING("kpa_06"), STRING("kpa_next_map"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(1), 400)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mario_cam_off)
    END_INLINE_EVENT
    CALL(evt_mobj_get_position, STRING("me"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(1))
    ADD(LW(3), 800)
    CALL(evt_mario_jump_jumpstand, LW(0), LW(1), LW(2), LW(0), LW(3), LW(2), LW(0), LW(3), LW(2), 4000, 3)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(kpa_05_init_evt)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(kpa_init))
    CALL(evt_mario_set_pos, -1500, 150, -5)
    CALL(evt_cam_road_reset)
    SET_VALUE(LW(0), PTR(kpa_act_stg3_mobj))
    CALL_CHILD(PTR(kpa_read_mobj))
    SET_VALUE(LW(0), PTR(kpa_act_stg3_item))
    CALL_CHILD(PTR(kpa_read_item))
    CALL(evt_map_playanim, STRING("anm_magu"), 1, 0)
    SPAWN_EVENT(PTR(kpa_fall))
    CALL(kpa_status_init, 3, GSW(1221), GSW(1222))
    SET_VALUE(LSW(1), 2)
    SPAWN_EVENT(PTR(kpa_stage_start))
    SPAWN_EVENT_GET_ID(PTR(kpa_time), GW(15))
    RETURN
EVT_END()

s32 kpaGetLevel(void);

static USER_FUNC(kpa_get_level) {
    s32* args = event->args;
    evtSetValue(event, args[0], kpaGetLevel());
    return EVT_RETURN_DONE;
}
