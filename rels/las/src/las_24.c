#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "las.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_breaking_floor);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_floatswitch_red);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_mobj_lv_blk);
USER_FUNC(evt_mobj_set_scale);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_party_get_name_hitobj_ride);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_jump_pos);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_sub_get_sincos);
#ifdef VERSION_G8ME01
USER_FUNC(las_24_adjust_for_framerate);
#endif

__declspec(section ".data") u64 fd_las_24_negone_one_374;
__declspec(section ".data") s32 fd_las_24_neg_one_382[1];
__declspec(section ".data") s32 fd_las_24___local_PI_383[1];
__declspec(section ".data") s32 fd_las_24___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_las_24_one_negone_373;
__declspec(section ".data") s32 fd_las_24___local_PIO2_384[1];
__declspec(section ".data") s32 fd_las_24_one_381[1];
__declspec(section ".data") u64 fd_las_24_negone_one_360;
__declspec(section ".data") s32 fd_las_24_neg_one_365[1];
__declspec(section ".data") s32 fd_las_24___local_PI_366[1];
__declspec(section ".data") s32 fd_las_24___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_las_24_one_negone_359;
__declspec(section ".data") s32 fd_las_24___local_PIO2_367[1];
__declspec(section ".data") s32 fd_las_24_one_364[1];
static s32 w_door_close[22];
static s32 w_door_open[22];
static s32 bero_entry_data[60];
static s32 haguruma_hontai[15];
static __declspec(section ".data") s32 haguruma_hontai2[6];
static __declspec(section ".data") s32 haguruma_kage[12];
static __declspec(section ".data") s32 haguruma_kage2[5];
static s32 haguruma_evt[194];
__declspec(section ".data") s32 cloud_blk_evt[10];
__declspec(section ".data") s32 break_floor_evt[5];
s32 jump_evt[68];
#ifdef VERSION_G8ME01
static s32 dai_evt[17];
#else
static s32 dai_evt[13];
#endif
static s32 box_evt[33];
s32 las_24_init_evt[190];

__declspec(section ".data") u64 fd_las_24_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_24_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_24___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_24___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_24_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_24___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_24_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_las_24_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_las_24_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_las_24___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_las_24___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_las_24_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_las_24___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_las_24_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_01"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("S_doa_02"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"las_22", (s32)"e_bero", 327685, (s32)w_door_close, (s32)w_door_open, (s32)"s_bero_1",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"las_23", (s32)"n_bero_2", 65537, 0, 0, (s32)"s_bero_2", 0,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"las_25", (s32)"n_bero_1", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 haguruma_hontai[] = {
    (s32)"S_hgm_01a", (s32)"S_hgm_02a", (s32)"S_hgm_03a", (s32)"S_hgm_04a", (s32)"S_hgm_06a", (s32)"S_hgm_07a", (s32)"S_hgm_08a", (s32)"S_hgm_10a",
    (s32)"S_hgm_11a", (s32)"S_hgm_14a", (s32)"S_hgm_15a", (s32)"S_hgm_16a", (s32)"S_hgm_19a", (s32)"S_hgm_20a", (s32)"S_hgm_24a",
};

static __declspec(section ".data") s32 haguruma_hontai2[] = {
    (s32)"S_hgm_05a", (s32)"S_hgm_09a", (s32)"S_hgm_12a", (s32)"S_hgm_13a", (s32)"S_hgm_17a", (s32)"S_hgm_18a",
};

static __declspec(section ".data") s32 haguruma_kage[] = {
    (s32)"S_hgm_01b", (s32)"S_hgm_02b", (s32)"S_hgm_03b", (s32)"S_hgm_04b", (s32)"S_hgm_06b", (s32)"S_hgm_07b", (s32)"S_hgm_08b", (s32)"S_hgm_10b",
    (s32)"S_hgm_11b", (s32)"S_hgm_14b", (s32)"S_hgm_15b", (s32)"S_hgm_16b",
};

static __declspec(section ".data") s32 haguruma_kage2[] = {
    (s32)"S_hgm_05b", (s32)"S_hgm_09b", (s32)"S_hgm_12b", (s32)"S_hgm_13b", (s32)"S_hgm_17b",
};

static EVT_BEGIN(haguruma_evt)
    SET_FLOAT_VALUE(LW(0), FLOAT(20.0f))
    SET_FLOAT_VALUE(LW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(4), FLOAT(0.0f))
    LOOP(0)
        SET_INT_READ_ADDR(PTR(haguruma_hontai))
        LOOP(15)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(0))
        END_LOOP
        SET_INT_READ_ADDR(PTR(haguruma_kage))
        LOOP(12)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(0))
        END_LOOP
        SET_INT_READ_ADDR(PTR(haguruma_hontai2))
        LOOP(6)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(1))
        END_LOOP
        SET_INT_READ_ADDR(PTR(haguruma_kage2))
        LOOP(5)
            READ_INT(LW(5))
            CALL(evt_mapobj_rotate, 0, LW(5), 0, 0, LW(1))
        END_LOOP
        CALL(evt_sub_get_sincos, LW(2), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(41.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_21a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_21b"), 0, 0, LW(5))
        CALL(evt_sub_get_sincos, LW(3), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(22.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_22a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_22b"), 0, 0, LW(5))
        CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), FLOAT(110.0f))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_23a"), 0, 0, LW(5))
        CALL(evt_mapobj_rotate, 0, STRING("S_hgm_23b"), 0, 0, LW(5))
        ADD_FLOAT(LW(0), FLOAT(1.0f))
        IF_INT_GREATER_OR_EQUAL(LW(0), 360)
            SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(1), FLOAT(-1.0f))
        IF_INT_LESS_OR_EQUAL(LW(1), -360)
            ADD_FLOAT(LW(1), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(2), FLOAT(0.89941406f))
        IF_INT_GREATER_OR_EQUAL(LW(2), 360)
            SUBTRACT_FLOAT(LW(2), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(3), FLOAT(0.89941406f))
        IF_INT_GREATER_OR_EQUAL(LW(3), 360)
            SUBTRACT_FLOAT(LW(3), FLOAT(360.0f))
        END_IF
        ADD_FLOAT(LW(4), FLOAT(1.0f))
        IF_INT_GREATER_OR_EQUAL(LW(4), 360)
            SUBTRACT_FLOAT(LW(4), FLOAT(360.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(cloud_blk_evt)
    SET_VALUE(GSWF(4356), 1)
    CALL(evt_mobj_flag_onoff, 0, STRING("blk"), 256)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(break_floor_evt)
    SET_VALUE(GSW(0), 396)
    RETURN
EVT_END()

EVT_BEGIN(jump_evt)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            LOOP(90)
                CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
                IF_INT_GREATER_OR_EQUAL(LW(1), -201)
                    IF_INT_LESS_OR_EQUAL(LW(1), -199)
                        RETURN
                    END_IF
                END_IF
                CALL(evt_party_get_name_hitobj_ride, 0, LW(0))
                IF_STR_EQUAL(LW(0), STRING("MOBJ_jump"))
                    CALL(evt_party_jump_pos, 0, -455, -200, 50, 600, 0, -1000)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
    END_INLINE_EVENT
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_jump_jumpstand, -500, -200, 0, -545, 100, 0, -450, -200, 0, 1000, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(dai_evt)
    SET_VALUE(LW(0), STRING("S_move_dai"))
    SET_VALUE(LW(1), STRING("A_move_dai"))
    SET_VALUE(LW(2), 7200)
#ifdef VERSION_G8ME01
    CALL(las_24_adjust_for_framerate, LW(2), LW(2))
#endif
    CALL_CHILD(PTR(move_dai))
    RETURN
EVT_END()

static EVT_BEGIN(box_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("key"), 48, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("key"))
    SET_VALUE(GSW(0), 397)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(las_24_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG8_LST3"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG8_LAS7"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_05a"), 2)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_19a"), 2)
    CALL(evt_mapobj_flag_onoff, 0, 0, STRING("S_hgm_24a"), 2)
    SPAWN_EVENT(PTR(haguruma_evt))
    CALL(evt_map_playanim, STRING("kusari"), 1, 0)
    IF_INT_LESS(GSW(0), 396)
        IF_INT_EQUAL(GSWF(4356), 0)
            CALL(evt_cloud_init)
            CALL(evt_cloud_ent, 0, STRING("S_hako"), STRING("A_hako"), PTR(cloud_blk_evt))
            ELSE
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hako"), 1)
            CALL(evt_hitobj_onoff, STRING("A_hako"), 1, 0)
        END_IF
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_hako"), 1)
        CALL(evt_hitobj_onoff, STRING("A_hako"), 1, 0)
    END_IF
    CALL(evt_mobj_lv_blk, STRING("blk"), -495, 100, 0, 0, GSWF(4357), STRING("MOBJ_Lv2BigBigBlock"))
    IF_INT_EQUAL(GSWF(4357), 0)
        CALL(evt_mobj_flag_onoff, 0, STRING("blk"), 64)
        IF_INT_EQUAL(GSWF(4356), 0)
            CALL(evt_mobj_flag_onoff, 1, STRING("blk"), 256)
            CALL(evt_mobj_set_scale, STRING("blk"), FLOAT(0.9980469f), FLOAT(0.9980469f), FLOAT(0.9980469f))
        END_IF
    END_IF
    CALL(evt_mobj_breaking_floor, STRING("brkflr"), -500, 100, 0, 0, PTR(break_floor_evt), GSWF(4358))
    CALL(evt_mobj_jumpstand_red, 0, STRING("jump"), -500, -200, 0, PTR(jump_evt), 0)
    CALL(evt_hit_bind_mapobj, STRING("A_move_dai"), STRING("S_move_dai"))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_move_dai"), 1)
    CALL(evt_hitobj_onoff, STRING("A_move_dai"), 0, 0)
    CALL(evt_mobj_floatswitch_red, 0, STRING("dai_switch"), -150, -440, 75, PTR(dai_evt), 0)
    CALL(evt_mobj_badgeblk, STRING("mobj_hatena_gat"), -625, -200, -100, 121, 0, GSWF(4390), 0)
    CALL(evt_mobj_brick, STRING("mobj_kakusi"), -625, -115, -100, 161, 11, 0, GSWF(4391))
    CALL(evt_mobj_itembox, STRING("box"), -255, -380, 75, 0, 0, PTR(box_evt), GSWF(4370))
    RETURN
EVT_END()


#ifdef VERSION_G8ME01
#include "mario/mariost.h"
#include "manager/evtmgr_cmd.h"

USER_FUNC(las_24_adjust_for_framerate) {
    s32* args = event->args;
    s32 value = evtGetValue(event, args[0]);

    if (gp->framerate != 60) {
        value *= 1.2f;
    }
    evtSetValue(event, args[1], value);
    return EVT_RETURN_DONE;
}
#endif
