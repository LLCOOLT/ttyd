#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "kpa.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_koopa_chk_dead);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_seq_set_seq);
USER_FUNC(evt_sub_get_system_flag);
USER_FUNC(kpa_status_init);

__declspec(section ".data") u64 fd_kpa_02_negone_one_374;
__declspec(section ".data") s32 fd_kpa_02_neg_one_382[1];
__declspec(section ".data") s32 fd_kpa_02___local_PI_383[1];
__declspec(section ".data") s32 fd_kpa_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_kpa_02_one_negone_373;
__declspec(section ".data") s32 fd_kpa_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_kpa_02_one_381[1];
__declspec(section ".data") u64 fd_kpa_02_negone_one_360;
__declspec(section ".data") s32 fd_kpa_02_neg_one_365[1];
__declspec(section ".data") s32 fd_kpa_02___local_PI_366[1];
__declspec(section ".data") s32 fd_kpa_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_kpa_02_one_negone_359;
__declspec(section ".data") s32 fd_kpa_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_kpa_02_one_364[1];
__declspec(section ".data") s32 fd_kpa_02__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_kpa_02__half_localstatic3_sqrtf[2];
s32 kpa_act_stg1_mobj[151];
s32 kpa_act_stg1_item[31];
static s32 kpa_fall[41];
static s32 kpa_goal[38];
static s32 npcEnt[23];
s32 kpa_02_init_evt[36];

__declspec(section ".data") u64 fd_kpa_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_kpa_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_02_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_kpa_02__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_kpa_02__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

s32 kpa_act_stg1_mobj[] = {
    4, -231254400, -229872000, 4, -231126400, -229872000, 0, -231075200,
    -229872000, 4, -231024000, -229872000, 4, -231024000, -229718400, 4,
    -230972800, -229872000, 4, -230921600, -229872000, 9, -230768000, -230000000,
    7, -230627200, -229974400, 121, 10, -230588800, -230000000, 0,
    -230384000, -229872000, 4, -230000000, -229974400, 0, -229948800, -229974400,
    7, -229782400, -229974400, 121, 10, -229744000, -230000000, 4,
    -230051200, -229795200, 4, -230000000, -229795200, 4, -229948800, -229795200,
    4, -229897600, -229795200, 0, -229488000, -229769600, 9, -229411200,
    -230000000, 9, -229232000, -230000000, 4, -229180800, -230051200, 4,
    -229180800, -230000000, 4, -229129600, -230051200, 4, -229129600, -230000000,
    4, -229129600, -229948800, 4, -229078400, -230051200, 4, -229078400,
    -230000000, 4, -229078400, -229948800, 4, -229078400, -229897600, 4,
    -229027200, -230051200, 4, -229027200, -230000000, 4, -229027200, -229948800,
    4, -229027200, -229897600, 4, -229027200, -229846400, 4, -228976000,
    -230051200, 4, -228976000, -230000000, 4, -228976000, -229948800, 4,
    -228976000, -229897600, 4, -228976000, -229846400, 4, -228976000, -229795200,
    4, -228924800, -230051200, 4, -228924800, -230000000, 4, -228924800,
    -229948800, 4, -228924800, -229897600, 4, -228924800, -229846400, 4,
    -228924800, -229795200, 15, -228732800, -230000000, (s32)kpa_goal, -1,
};

s32 kpa_act_stg1_item[] = {
    0, -230704000, -229884800, 0, -230665600, -229884800, 0, -230512000,
    -229859200, 0, -230473600, -229859200, 0, -230230400, -229936000, 0,
    -230192000, -229936000, 0, -229846400, -229872000, 0, -229808000, -229872000,
    0, -229667200, -229833600, 0, -229628800, -229833600, -1,
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

static EVT_BEGIN(kpa_goal)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(GSW(0), 116)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 4096)
        CALL(evt_cam_letter_box_disable, 0)
        CALL(evt_seq_set_seq, 5, 0, 0)
        ELSE
        BEGIN_INLINE_EVENT
            WAIT_MS(300)
            CALL(evt_cam_letter_box_disable, 0)
        END_INLINE_EVENT
        CALL(evt_bero_mapchange, STRING("nok_00"), STRING("w_bero\0"))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(kpa_02_init_evt)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(kpa_init))
    CALL(evt_mario_set_pos, -1450, 0, -5)
    SET_VALUE(LW(0), PTR(kpa_act_stg1_mobj))
    CALL_CHILD(PTR(kpa_read_mobj))
    SET_VALUE(LW(0), PTR(kpa_act_stg1_item))
    CALL_CHILD(PTR(kpa_read_item))
    SPAWN_EVENT(PTR(kpa_fall))
    CALL(kpa_status_init, 1, GSW(1221), GSW(1222))
    SET_VALUE(LSW(1), 0)
    SPAWN_EVENT(PTR(kpa_stage_start))
    SPAWN_EVENT(PTR(kpa_time))
    RETURN
EVT_END()

