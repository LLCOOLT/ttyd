#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/mapdrv.h"
#include "driver/envdrv.h"

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_map_blend_off);
USER_FUNC(evt_map_blend_set_flag);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_blend);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_telop_entry);
void water_tev(MapTevCallbackInfo* info);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_dou_00_negone_one_374;
__declspec(section ".data") s32 fd_dou_00_neg_one_382[1];
__declspec(section ".data") s32 fd_dou_00___local_PI_383[1];
__declspec(section ".data") s32 fd_dou_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_dou_00_one_negone_373;
__declspec(section ".data") s32 fd_dou_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_dou_00_one_381[1];
__declspec(section ".data") u64 fd_dou_00_negone_one_360;
__declspec(section ".data") s32 fd_dou_00_neg_one_365[1];
__declspec(section ".data") s32 fd_dou_00___local_PI_366[1];
__declspec(section ".data") s32 fd_dou_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_dou_00_one_negone_359;
__declspec(section ".data") s32 fd_dou_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_dou_00_one_364[1];
static __declspec(section ".data") s32 bero_in_event[11];
static s32 bero_entry_data[45];
static s32 back_light[35];
s32 totsunyu_event[46];
s32 dou_00_init_evt[61];

__declspec(section ".data") u64 fd_dou_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dou_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dou_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dou_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dou_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dou_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dou_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_dou_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_dou_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_dou_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_dou_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_dou_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_dou_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_dou_00_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(bero_in_event)
    IF_INT_EQUAL(GSW(0), 242)
        CALL_CHILD(PTR(totsunyu_event))
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, (s32)bero_in_event,
    -1, 0, (s32)"muj_05", (s32)"e_bero", 65537, 0, 0, (s32)"e_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"dou_01", (s32)"w_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(back_light)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 2000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_blend_set_flag, 0, STRING("mario"), 2048)
    CALL(evt_map_blend_off, 0)
    RETURN
EVT_END()

EVT_BEGIN(totsunyu_event)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg5_dou_00"), 0, 0)
    SPAWN_EVENT(PTR(back_light))
    WAIT_MS(200)
    SET_VALUE(GSW(0), 243)
    CALL(evt_mario_key_onoff, 1)
    BEGIN_INLINE_EVENT
        CALL(evt_telop_entry, 10)
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(dou_00_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG5_DOU1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG5_DOU1"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    WAIT_FRAMES(1)
    CALL(evt_map_playanim, STRING("nami"), 1, 0)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 30, 85, -75, 0, 0)
    CALL(evt_item_entry, STRING("item_01"), 137, -245, 0, 85, 16, GSWF(2990), 0)
    CALL(evt_map_set_tevcallback, 1, PTR(water_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s00_suimen"), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s00_suimen"), 256)
    RETURN
EVT_END()

void water_tev(MapTevCallbackInfo* info) {
    envSetWater(info);
}
