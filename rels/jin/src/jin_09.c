#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_jump_jumpstand);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_random);
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill[];

__declspec(section ".data") u64 fd_jin_09_negone_one_374;
__declspec(section ".data") s32 fd_jin_09_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_09___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_09___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_09_one_negone_373;
__declspec(section ".data") s32 fd_jin_09___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_09_one_381[1];
__declspec(section ".data") u64 fd_jin_09_negone_one_360;
__declspec(section ".data") s32 fd_jin_09_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_09___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_09___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_09_one_negone_359;
__declspec(section ".data") s32 fd_jin_09___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_09_one_364[1];
static s32 bero_entry_data[30];
s32 jin_09_jumpstand[21];
s32 jin_09_init_evt[214];

__declspec(section ".data") u64 fd_jin_09_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_09_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_09___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_09___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_09_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_09___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_09_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_09_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_09_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_09___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_09___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_09_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_09___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_09_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)"e_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"jin_10", (s32)"w_bero", 65537, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(jin_09_jumpstand)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_jump_jumpstand, 0, 0, 0, -10, 700, 0, 50, 0, 0, 1800, 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(jin_09_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    CALL(evt_mobj_powerupblk, STRING("blk00"), -120, 60, 90, 0, GSWF(5550), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_random, 3000, LW(0))
            ADD(LW(0), 1000)
            WAIT_MS(LW(0))
            CALL(evt_map_playanim, STRING("sizuku_01"), 0, 0)
            CALL(evt_map_checkanim, STRING("sizuku_01"), LW(0), LW(1))
            WAIT_MS(LW(1))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_AMB_WATERDROP1"), -76, 0, 13, 0)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_random, 3000, LW(0))
            ADD(LW(0), 1000)
            WAIT_MS(LW(0))
            CALL(evt_map_playanim, STRING("sizuku_02"), 0, 0)
            CALL(evt_map_checkanim, STRING("sizuku_02"), LW(0), LW(1))
            WAIT_MS(LW(1))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_AMB_WATERDROP1"), 32, 0, -64, 0)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mobj_jumpstand_red, 0, STRING("jumpstand"), 0, 0, 0, PTR(jin_09_jumpstand), 0)
    IF_INT_NOT_EQUAL(GSWF(2079), 0)
        SET_VALUE(GSWF(2079), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_mario_cont_onoff, 0)
            CALL(evt_party_cont_onoff, 0, 0)
            CALL(evt_mario_set_pos, 0, 365, 0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(evt_party_set_pos, 0, 0, 395, 0)
            END_IF
            CALL(evt_cam_road_reset)
            CALL(evt_seq_wait, 2)
            CALL(evt_mario_cont_onoff, 1)
            WAIT_MS(180)
            CALL(evt_party_cont_onoff, 0, 1)
            CALL(evt_mario_key_onoff, 1)
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
        CALL(evt_bero_mapchange, STRING("gra_06"), STRING("ana"))
    END_INLINE_EVENT
    RETURN
EVT_END()

