#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_kagemario_init_14_text_4DB8);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_party_get_name_hitobj_ride);
USER_FUNC(evt_party_jump_pos);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill_14_data_AF00[];

__declspec(section ".data") u64 fd_jin_06_negone_one_374;
__declspec(section ".data") s32 fd_jin_06_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_06___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_06___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_06_one_negone_373;
__declspec(section ".data") s32 fd_jin_06___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_06_one_381[1];
__declspec(section ".data") u64 fd_jin_06_negone_one_360;
__declspec(section ".data") s32 fd_jin_06_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_06___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_06___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_06_one_negone_359;
__declspec(section ".data") s32 fd_jin_06___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_06_one_364[1];
static __declspec(section ".data") s32 w_close[12];
static __declspec(section ".data") s32 w_open[12];
static s32 bero_entry_data[30];
__declspec(section ".data") s32 jin_06_wall_open_evt[5];
s32 jin_06_jumpstand[53];
static s32 mobj_box00[34];
s32 jin_06_init_evt[165];

__declspec(section ".data") u64 fd_jin_06_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_06_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_06___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_06___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_06_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_06___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_06_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_06_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_06_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_06___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_06___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_06_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_06___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_06_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door07"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door07"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 65538, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"jin_07", (s32)"e_bero", 327685, (s32)w_close, (s32)w_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(jin_06_wall_open_evt)
    SET_VALUE(GSWF(2229), 1)
    RETURN
EVT_END()

EVT_BEGIN(jin_06_jumpstand)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            LOOP(0)
                CALL(evt_party_get_name_hitobj_ride, 0, LW(0))
                IF_STR_EQUAL(LW(0), STRING("MOBJ_mobj_jump"))
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_party_jump_pos, 0, 30, 0, 50, 600, 0, -1000)
        END_IF
    END_INLINE_EVENT
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_jump_jumpstand, 0, 0, 0, 0, 400, 0, 0, 0, 50, 1000, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(mobj_box00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), 281, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 258)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(jin_06_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init_14_text_4DB8)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_14_data_AF00))
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 650, 0, -150, 0, 0, PTR(mobj_box00), GSWF(2238))
    CALL(evt_mobj_jumpstand_red, 0, STRING("mobj_jump"), 0, 0, 0, PTR(jin_06_jumpstand), 0)
    IF_INT_NOT_EQUAL(GSWF(2079), 0)
        SET_VALUE(GSWF(2079), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_cam_letter_box_disable, 1)
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_mario_set_pos, 5, 365, 0)
            CALL(evt_party_set_pos, 0, 5, 645, 0)
            CALL(evt_cam_road_reset)
            CALL(evt_seq_wait, 2)
            CALL(evt_mario_wait_landon)
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_cam_letter_box_disable, 0)
        END_INLINE_EVENT
        SET_VALUE(LW(0), 1)
        ELSE
        SET_VALUE(LW(0), 0)
    END_IF
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_seq_wait, 2)
            LOOP(0)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                IF_INT_LESS(LW(1), 365)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(1), 365)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_bero_mapchange, STRING("jin_00"), STRING("ana"))
    END_INLINE_EVENT
    IF_INT_EQUAL(GSWF(2229), 0)
        CALL(evt_cloud_init)
        CALL(evt_cloud_ent, 0, STRING("mekure"), STRING("a_mekure\0\0\0"), PTR(jin_06_wall_open_evt))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("mekure"), 1)
        CALL(evt_hitobj_onoff, STRING("a_mekure\0\0\0"), 0, 0)
    END_IF
    IF_INT_LESS(GSW(0), 195)
        SET_VALUE(GSW(0), 195)
    END_IF
    RETURN
EVT_END()

