#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_tik_21_negone_one_374;
__declspec(section ".data") s32 fd_tik_21_neg_one_382[1];
__declspec(section ".data") s32 fd_tik_21___local_PI_383[1];
__declspec(section ".data") s32 fd_tik_21___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tik_21_one_negone_373;
__declspec(section ".data") s32 fd_tik_21___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tik_21_one_381[1];
__declspec(section ".data") u64 fd_tik_21_negone_one_360;
__declspec(section ".data") s32 fd_tik_21_neg_one_365[1];
__declspec(section ".data") s32 fd_tik_21___local_PI_366[1];
__declspec(section ".data") s32 fd_tik_21___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tik_21_one_negone_359;
__declspec(section ".data") s32 fd_tik_21___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tik_21_one_364[1];
static s32 bero_entry_data[30];
s32 hari_trap[107];
static __declspec(section ".data") s32 hitDmgRetPoints[12];
static s32 mobj_box00[34];
s32 tik_21_init_evt[35];

__declspec(section ".data") u64 fd_tik_21_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_21_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_21___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_21___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_21_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_21___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_21_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tik_21_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tik_21_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tik_21___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tik_21___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tik_21_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tik_21___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tik_21_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"s_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tik_15", (s32)"n_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(hari_trap)
    CALL(evt_hit_bind_mapobj, STRING("a_toge"), STRING("s_toge"))
    LOOP(0)
        CALL(evt_hitobj_attr_onoff, 1, 1, STRING("a_yuka"), 2048)
        CALL(evt_mapobj_get_position, STRING("s_toge"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_FLOOR_TRAP1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_sub_intpl_msec_init, 1, -5, 30, 150)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_trans, 1, STRING("s_toge"), 0, LW(0), 0)
            CALL(evt_hit_bind_update, STRING("a_toge"))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_MS(1500)
        CALL(evt_mapobj_get_position, STRING("s_toge"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_FLOOR_TRAP2"), LW(0), LW(1), LW(2), 0)
        CALL(evt_sub_intpl_msec_init, 4, 30, -5, 300)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_trans, 1, STRING("s_toge"), 0, LW(0), 0)
            CALL(evt_hit_bind_update, STRING("a_toge"))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_hitobj_attr_onoff, 1, 0, STRING("a_yuka"), 2048)
#ifdef VERSION_G8ME01
        WAIT_MS(2000)
#else
        WAIT_MS(2200)
#endif
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") s32 hitDmgRetPoints[] = {
    (s32)"mod_1", 0, -998637568, 0, (s32)"mod_2", 1124204544, 0, -1031798784,
    0, 0, 0, 0,
};

static EVT_BEGIN(mobj_box00)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("item00"), 284, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 258)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_item, STRING("item00"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(tik_21_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_TIK1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG0_TIK1\0\0"))
    CALL(evt_snd_set_rev_mode, 2)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_hit_damage_return_set, PTR(hitDmgRetPoints))
    SPAWN_EVENT(PTR(hari_trap))
    CALL(evt_mobj_itembox, STRING("mobj_box00"), 150, 0, -100, 0, 0, PTR(mobj_box00), GSWF(1368))
    RETURN
EVT_END()

