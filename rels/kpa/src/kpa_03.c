#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_koopa_chk_dead);
USER_FUNC(evt_koopa_get_level);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mario_cam_off);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_set_hosei_xyz);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_seq_wait);
USER_FUNC(kpa_status_init);
extern s32 kpa_dead[];
extern s32 kpa_fall_sub[];
extern s32 kpa_init[];
extern s32 kpa_read_item[];
extern s32 kpa_read_mobj[];
extern s32 kpa_stage_start[];
extern s32 kpa_time[];

__declspec(section ".data") u64 fd_kpa_03_negone_one_374;
__declspec(section ".data") s32 fd_kpa_03_neg_one_382[1];
__declspec(section ".data") s32 fd_kpa_03___local_PI_383[1];
__declspec(section ".data") s32 fd_kpa_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_kpa_03_one_negone_373;
__declspec(section ".data") s32 fd_kpa_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_kpa_03_one_381[1];
__declspec(section ".data") u64 fd_kpa_03_negone_one_360;
__declspec(section ".data") s32 fd_kpa_03_neg_one_365[1];
__declspec(section ".data") s32 fd_kpa_03___local_PI_366[1];
__declspec(section ".data") s32 fd_kpa_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_kpa_03_one_negone_359;
__declspec(section ".data") s32 fd_kpa_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_kpa_03_one_364[1];
static s32 kpa_act_stg2_mobj[209];
s32 kpa_act_stg2_item[85];
static s32 kpa_fall[41];
s32 kairyu_evt[38];
static s32 jumpstand_evt[60];
static s32 npcEnt[23];
s32 kpa_03_init_evt[44];

__declspec(section ".data") u64 fd_kpa_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_kpa_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_03_one_364[] = {
    1065353216,
};

static s32 kpa_act_stg2_mobj[] = {
    12, -231305600, -230000000, 4, -231126400, -229795200, 12, -231126400,
    -229744000, 4, -230947200, -230000000, 4, -230947200, -229948800, 4,
    -230947200, -229897600, 0, -230793600, -229897600, 4, -230742400, -230000000,
    4, -230742400, -229948800, 4, -230742400, -229897600, 4, -230486400,
    -229974400, 4, -230435200, -229974400, 0, -230384000, -229974400, 4,
    -230384000, -229744000, 12, -230307200, -230000000, 4, -230230400, -230000000,
    4, -230230400, -229948800, 4, -230230400, -229744000, 4, -230230400,
    -229692800, 4, -230230400, -229641600, 4, -230076800, -230000000, 4,
    -230076800, -229948800, 4, -230076800, -229744000, 4, -230076800, -229692800,
    4, -230076800, -229641600, 12, -229948800, -230000000, 4, -229872000,
    -229974400, 0, -229820800, -229974400, 4, -229769600, -229974400, 0,
    -229718400, -229974400, 12, -229641600, -230000000, 4, -229488000, -229974400,
    4, -229436800, -229923200, 4, -229385600, -229923200, 4, -229334400,
    -229923200, 4, -229283200, -229923200, 4, -229232000, -229923200, 4,
    -229180800, -229923200, 4, -229129600, -229923200, 4, -229078400, -229974400,
    4, -229488000, -229692800, 4, -229488000, -229641600, 4, -229436800,
    -229744000, 4, -229385600, -229744000, 4, -229334400, -229744000, 4,
    -229283200, -229744000, 4, -229232000, -229744000, 4, -229180800, -229744000,
    4, -229129600, -229744000, 4, -229078400, -229692800, 4, -229078400,
    -229641600, 12, -229001600, -230000000, 16, -228822400, -230000000, (s32)jumpstand_evt,
    4, -228643200, -230000000, 4, -228592000, -230000000, 4, -228592000,
    -229948800, 4, -228540800, -230000000, 4, -228540800, -229948800, 4,
    -228540800, -229897600, 4, -228540800, -229744000, 4, -228540800, -229692800,
    4, -228540800, -229641600, 4, -228489600, -230000000, 4, -228489600,
    -229948800, 4, -228489600, -229897600, 11, -228464000, -229846400, 4,
    -228489600, -229744000, 4, -228489600, -229692800, 4, -228489600, -229641600,
    -1,
};

s32 kpa_act_stg2_item[] = {
    0, -231075200, -229782400, 0, -231024000, -229782400, 0, -230896000,
    -229987200, 0, -230896000, -229936000, 0, -230844800, -229987200, 0,
    -230844800, -229936000, 0, -230793600, -229987200, 0, -230793600, -229936000,
    0, -229872000, -230000000, 0, -229820800, -230000000, 0, -229769600,
    -230000000, 0, -229718400, -230000000, 0, -229385600, -229974400, 0,
    -229334400, -229974400, 0, -229283200, -229974400, 0, -229232000, -229974400,
    0, -229180800, -229974400, 0, -229360000, -229846400, 0, -229360000,
    -229795200, 0, -229308800, -229846400, 0, -229308800, -229795200, 0,
    -229257600, -229846400, 0, -229257600, -229795200, 0, -229206400, -229846400,
    0, -229206400, -229795200, 0, -228822400, -229680000, 0, -228822400,
    -229641600, 0, -228822400, -229603200, -1,
};

static EVT_BEGIN(kpa_fall)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        CALL(evt_koopa_chk_dead, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 1)
            BREAK_LOOP
        END_IF
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(1), -20)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_EQUAL(LF(0), 0)
        CALL_CHILD(PTR(kpa_fall_sub))
        ELSE
        CALL_CHILD(PTR(kpa_dead))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(kairyu_evt)
    CALL(evt_seq_wait, 2)
    LOOP(0)
        IF_INT_NOT_EQUAL(LSWF(3), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(0), -175)
            IF_INT_LESS_OR_EQUAL(LW(0), -100)
                IF_INT_LESS(LW(1), 400)
                    CALL(evt_mario_set_hosei_xyz, 0, FLOAT(-0.7998047f), 0)
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(jumpstand_evt)
    DELETE_EVENT(GW(15))
    BEGIN_INLINE_EVENT
        WAIT_MS(600)
        CALL(evt_koopa_get_level, GSW(1223))
        CALL(evt_bero_mapchange, STRING("kpa_04"), STRING("kpa_next_map"))
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
    ADD(LW(3), 700)
    CALL(evt_mario_jump_jumpstand, LW(0), LW(1), LW(2), LW(0), LW(3), LW(2), LW(0), LW(3), LW(2), 4000, 3)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(kpa_03_init_evt)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(kpa_init))
    CALL(evt_mario_set_pos, -1400, 0, -5)
    SET_VALUE(LW(0), PTR(kpa_act_stg2_mobj))
    CALL_CHILD(PTR(kpa_read_mobj))
    SET_VALUE(LW(0), PTR(kpa_act_stg2_item))
    CALL_CHILD(PTR(kpa_read_item))
    CALL(evt_map_playanim, STRING("anm_umi"), 1, 0)
    SPAWN_EVENT(PTR(kpa_fall))
    CALL(kpa_status_init, 2, GSW(1221), GSW(1222))
    SET_VALUE(LSW(1), 1)
    SPAWN_EVENT(PTR(kpa_stage_start))
    SPAWN_EVENT(PTR(kairyu_evt))
    SPAWN_EVENT_GET_ID(PTR(kpa_time), GW(15))
    RETURN
EVT_END()

