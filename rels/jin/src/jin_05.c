#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill[];

__declspec(section ".data") u64 fd_jin_05_negone_one_374;
__declspec(section ".data") s32 fd_jin_05_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_05___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_05_one_negone_373;
__declspec(section ".data") s32 fd_jin_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_05_one_381[1];
__declspec(section ".data") u64 fd_jin_05_negone_one_360;
__declspec(section ".data") s32 fd_jin_05_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_05___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_05_one_negone_359;
__declspec(section ".data") s32 fd_jin_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_05_one_364[1];
static s32 check_roll[16];
static s32 bero_entry_data[30];
s32 item_box_00[34];
static s32 mobj_box01[34];
s32 jin_05_init_evt[63];

__declspec(section ".data") u64 fd_jin_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_05_one_364[] = {
    1065353216,
};

static EVT_BEGIN(check_roll)
    CALL(evt_mario_get_motion, LW(0))
    IF_INT_EQUAL(LW(0), 22)
        SET_VALUE(LW(0), 0)
        ELSE
        SET_VALUE(LW(0), 1)
    END_IF
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"s_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)check_roll, (s32)"jin_00", (s32)"n_bero_1", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(item_box_00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("_item00"), 60, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("_item00"), 2)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("_item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(mobj_box01)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box01"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("_item01"), 253, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("_item01"), 258)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box01"))
    CALL(evt_item_get_item, STRING("_item01"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(jin_05_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    CALL(evt_mobj_powerupblk, STRING("pblk00"), 65, 60, 35, 0, GSWF(5549), 0)
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 125, 0, 75, 0, 0, PTR(item_box_00), GSWF(2235))
    CALL(evt_mobj_itembox, STRING("mobj_box01"), -55, 0, 55, 0, 0, PTR(mobj_box01), GSWF(2237))
    CALL(evt_item_entry, STRING("item_00"), 125, -10, 0, -40, 16, GSWF(5635), 0)
    RETURN
EVT_END()

