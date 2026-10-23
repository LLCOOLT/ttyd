#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "evt/evt_bero.h"
#include "gra.h"

static USER_FUNC(booboo_main);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);

__declspec(section ".data") u64 fd_gra_02_negone_one_374;
__declspec(section ".data") s32 fd_gra_02_neg_one_382[1];
__declspec(section ".data") s32 fd_gra_02___local_PI_383[1];
__declspec(section ".data") s32 fd_gra_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gra_02_one_negone_373;
__declspec(section ".data") s32 fd_gra_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gra_02_one_381[1];
__declspec(section ".data") u64 fd_gra_02_negone_one_360;
__declspec(section ".data") s32 fd_gra_02_neg_one_365[1];
__declspec(section ".data") s32 fd_gra_02___local_PI_366[1];
__declspec(section ".data") s32 fd_gra_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gra_02_one_negone_359;
__declspec(section ".data") s32 fd_gra_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gra_02_one_364[1];
s32 shopmaster_pig_init[14];
s32 shopmaster_talk[33];
static s32 urouro_move[24];
static s32 npcEnt[46];
__declspec(section ".data") s32 w_bero_2_in[5];
static s32 bero_entry_data[75];
__declspec(section ".data") s32 gra02_get_key[5];
s32 gra02_straw_blow_evt[23];
static __declspec(section ".data") s32 booboo_name[1];
s32 gra_02_init_evt[86];

__declspec(section ".data") u64 fd_gra_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gra_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gra_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gra_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gra_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gra_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gra_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gra_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gra_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gra_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gra_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gra_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gra_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gra_02_one_364[] = {
    1065353216,
};

EVT_BEGIN(shopmaster_pig_init)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタお店の主人"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(shopmaster_talk)
    SWITCH(GSW(0))
        CASE_LESS(200)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_gra_17"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_gra_18"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(urouro_move)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1073741824)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(50.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ブタお店の主人"*/"\x83\x75\x83\x5E\x82\xA8\x93\x58\x82\xCC\x8E\xE5\x90\x6C", 1536, 0, (s32)shopmaster_pig_init, (s32)urouro_move, (s32)shopmaster_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(w_bero_2_in)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero_1", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"gra_01", (s32)"e_bero1", 65537, 0, 0, (s32)"w_bero_2",
    268435456, 6, 242, 21, -450, -1, (s32)w_bero_2_in, 0,
    0, (s32)"gra_03", (s32)"e_bero", 65537, 0, 0, (s32)"dokan_1", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_2", 268566528, 9,
    100000, 0, 0, -1, 0, 6, 0, 0,
    (s32)"dokan_1", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(gra02_get_key)
    SET_VALUE(GSW(0), 184)
    RETURN
EVT_END()

EVT_BEGIN(gra02_straw_blow_evt)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    SET_VALUE(GSW(0), 188)
    RETURN
EVT_END()

static __declspec(section ".data") s32 booboo_name[] = {
    (s32)/*"ブタお店の主人"*/"\x83\x75\x83\x5E\x82\xA8\x93\x58\x82\xCC\x8E\xE5\x90\x6C",
};

EVT_BEGIN(gra_02_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_GRA1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_USU1"))
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_item_entry, STRING("item00"), 125, -125, 0, -110, 16, GSWF(5631), 0)
    CALL(evt_item_entry, STRING("item01"), 125, 305, 0, -35, 16, GSWF(5632), 0)
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_LESS(GSW(0), 184)
        CALL(evt_item_entry, STRING("key00"), 21, -30, 0, 0, 0, -1, PTR(gra02_get_key))
    END_IF
    IF_INT_LESS(GSW(0), 188)
        CALL(evt_cloud_init)
        CALL(evt_cloud_ent, 0, STRING("S_wara"), STRING("polySurface981_q023"), PTR(gra02_straw_blow_evt))
        ELSE
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S_wara"), 1)
        CALL(evt_hitobj_onoff, STRING("polySurface981_q023"), 0, 0)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(booboo_main)
    END_INLINE_EVENT
    RETURN
EVT_END()

static USER_FUNC(booboo_main) {
    animPoseSetMaterialLightFlagOn(npcNameToPtr((const char*)booboo_name[0])->poseId, 0x10);
    return EVT_RETURN_DONE;
}
