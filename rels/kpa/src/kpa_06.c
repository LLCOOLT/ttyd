#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "kpa.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_koopa_chk_dead);
USER_FUNC(evt_koopa_set_level);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_sub_get_system_flag);
USER_FUNC(kpa_status_init);

__declspec(section ".data") u64 fd_kpa_06_negone_one_374;
__declspec(section ".data") s32 fd_kpa_06_neg_one_382[1];
__declspec(section ".data") s32 fd_kpa_06___local_PI_383[1];
__declspec(section ".data") s32 fd_kpa_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_kpa_06_one_negone_373;
__declspec(section ".data") s32 fd_kpa_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_kpa_06_one_381[1];
__declspec(section ".data") u64 fd_kpa_06_negone_one_360;
__declspec(section ".data") s32 fd_kpa_06_neg_one_365[1];
__declspec(section ".data") s32 fd_kpa_06___local_PI_366[1];
__declspec(section ".data") s32 fd_kpa_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_kpa_06_one_negone_359;
__declspec(section ".data") s32 fd_kpa_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_kpa_06_one_364[1];
static s32 kpa_act_stg3_mobj[68];
static s32 kpa_fall[41];
static s32 kpa_goal[22];
static s32 npcEnt[23];
s32 kpa_06_init_evt[56];

__declspec(section ".data") u64 fd_kpa_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_kpa_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kpa_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kpa_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kpa_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kpa_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kpa_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kpa_06_one_364[] = {
    1065353216,
};

static s32 kpa_act_stg3_mobj[] = {
    9, -230230400, -230000000, 4, -230179200, -230000000, 4, -230128000,
    -230000000, 4, -230128000, -229948800, 4, -230076800, -230000000, 4,
    -230076800, -229948800, 4, -230076800, -229897600, 4, -230025600, -230000000,
    4, -230025600, -229948800, 4, -230025600, -229897600, 4, -230025600,
    -229846400, 4, -229974400, -230000000, 4, -229974400, -229948800, 4,
    -229974400, -229897600, 4, -229974400, -229846400, 4, -229974400, -229795200,
    4, -229923200, -230000000, 4, -229923200, -229948800, 4, -229923200,
    -229897600, 4, -229923200, -229846400, 4, -229923200, -229795200, 15,
    -229731200, -230000000, (s32)kpa_goal, -1,
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
    SET_VALUE(GSW(0), 343)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_cam_letter_box_disable, 0)
    END_INLINE_EVENT
    CALL(evt_bero_mapchange, STRING("kpa_07"), STRING(""))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(kpa_06_init_evt)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(kpa_init))
    CALL(evt_mario_set_pos, -400, 500, -5)
    CALL(evt_mario_set_dir, 90, 0, 0)
    SET_VALUE(LW(0), PTR(kpa_act_stg3_mobj))
    CALL_CHILD(PTR(kpa_read_mobj))
    SPAWN_EVENT(PTR(kpa_fall))
    CALL(kpa_status_init, 3, GSW(1221), GSW(1222))
    SET_VALUE(LSW(1), 0)
    SET_VALUE(LSWF(2), 1)
    SPAWN_EVENT(PTR(kpa_bgm_change))
    CALL(evt_snd_envoff, 512)
    SPAWN_EVENT(PTR(kpa_time))
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 2)
        RETURN
    END_IF
    CALL(evt_koopa_set_level, GSW(1223))
    RETURN
EVT_END()

