#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_letter_box_onoff);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_envon);
extern s32 hom_10_evt_resha_left[];
extern s32 hom_10_evt_resha_right[];
extern s32 hom_10_evt_resha_start3[];
extern s32 hom_10_evt_resha_start4[];

__declspec(section ".data") u64 fd_hom_11_negone_one_374;
__declspec(section ".data") s32 fd_hom_11_neg_one_382[1];
__declspec(section ".data") s32 fd_hom_11___local_PI_383[1];
__declspec(section ".data") s32 fd_hom_11___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hom_11_one_negone_373;
__declspec(section ".data") s32 fd_hom_11___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hom_11_one_381[1];
__declspec(section ".data") u64 fd_hom_11_negone_one_360;
__declspec(section ".data") s32 fd_hom_11_neg_one_365[1];
__declspec(section ".data") s32 fd_hom_11___local_PI_366[1];
__declspec(section ".data") s32 fd_hom_11___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hom_11_one_negone_359;
__declspec(section ".data") s32 fd_hom_11___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hom_11_one_364[1];
s32 hom_11_init_evt[140];

__declspec(section ".data") u64 fd_hom_11_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hom_11_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hom_11___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hom_11___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hom_11_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hom_11___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hom_11_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hom_11_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hom_11_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hom_11___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hom_11___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hom_11_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hom_11___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hom_11_one_364[] = {
    1065353216,
};

EVT_BEGIN(hom_11_init_evt)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH2"))
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    IF_INT_EQUAL(GSWF(3578), 0)
        CALL_CHILD(PTR(hom_10_evt_resha_right))
        CALL_CHILD(PTR(hom_10_evt_resha_start3))
        SET_VALUE(LW(0), 500)
        SET_VALUE(LW(1), -500)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("renketu"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_3"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_4"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_5"), 1)
        ELSE
        CALL_CHILD(PTR(hom_10_evt_resha_left))
        CALL_CHILD(PTR(hom_10_evt_resha_start4))
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(1), 1000)
        CALL(evt_mapobj_trans, 1, STRING("train"), -1500, 0, 0)
    END_IF
    CALL(evt_cam_letter_box_onoff, 1, 1)
    CALL(evt_cam3d_evt_set, LW(0), 300, 1400, LW(0), 125, 0, 0, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_cam3d_evt_set, LW(1), 300, 1400, LW(1), 125, 0, 8000, 0)
        WAIT_MS(4000)
        CALL(evt_bero_mapchange, STRING("rsh_02_b"), STRING("nidome\0"))
    END_INLINE_EVENT
    RETURN
EVT_END()

