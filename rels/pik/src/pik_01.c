#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/mapdrv.h"
#include "driver/mobjdrv.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "dolphin/mtx.h"
#include "mario/mario.h"

static USER_FUNC(anim_tevcallback);
USER_FUNC(chk_luigi_color);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bg_set_color);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_get_target_dir);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_party_use_check);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_mode);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_entry);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_lock_unlock);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_set_anim);
USER_FUNC(evt_mobj_set_position);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_npc_add_dirdist);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_get_reglid);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_kamek_move_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_autotalkpose);
USER_FUNC(evt_npc_set_force_regl_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_wait_pera);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_move_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_get_haveitemcnt);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_coin);
USER_FUNC(evt_sub_get_dir);
USER_FUNC(evt_sub_get_sincos);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_get_value_para);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_win_item_select);
USER_FUNC(kpa_chg_pose);
USER_FUNC(kpa_lock_hit_scale);
USER_FUNC(set_r);
static USER_FUNC(starstone_entry);
static USER_FUNC(starstone_set_pos);
static USER_FUNC(starstone_set_ry);
static USER_FUNC(yami_view);
void test_tev2(MapTevCallbackInfo* info);
void test_tev(MapTevCallbackInfo* info);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 bero_open_door_play_se[];
extern s32 envSetYami[];
extern s32 evt_bero_info_run[];
extern s32 evt_gazigazi_entry[];
extern s32 evt_pik_yajirushi[];
extern s32 npc_init_evt[];

__declspec(section ".data") u64 fd_pik_01_negone_one_374;
__declspec(section ".data") s32 fd_pik_01_neg_one_382[1];
__declspec(section ".data") s32 fd_pik_01___local_PI_383[1];
__declspec(section ".data") s32 fd_pik_01___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_pik_01_one_negone_373;
__declspec(section ".data") s32 fd_pik_01___local_PIO2_384[1];
__declspec(section ".data") s32 fd_pik_01_one_381[1];
__declspec(section ".data") u64 fd_pik_01_negone_one_360;
__declspec(section ".data") s32 fd_pik_01_neg_one_365[1];
__declspec(section ".data") s32 fd_pik_01___local_PI_366[1];
__declspec(section ".data") s32 fd_pik_01___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_pik_01_one_negone_359;
__declspec(section ".data") s32 fd_pik_01___local_PIO2_367[1];
__declspec(section ".data") s32 fd_pik_01_one_364[1];
static s32 dmgReturnPt[36];
static s32 n_door_open[22];
static s32 n_door_close[22];
static s32 bero_data[60];
static __declspec(section ".data") s32 name_tbl[2];
s32 evt_powan[346];
static s32 init_powan[18];
static __declspec(section ".data") s32 talk_powan[8];
s32 miyageya_talk[563];
s32 miyageya_init[24];
__declspec(section ".data") s32 iri_29_item_tbl1[2];
__declspec(section ".data") s32 iri_29_item_tbl2[2];
__declspec(section ".data") s32 iri_29_item_tbl3[2];
s32 konarikin_talk[426];
s32 konarikin_init[29];
s32 narikin_papa_mama_talk[55];
s32 narikin_papa_init[23];
s32 narikin_mama_init[23];
s32 madam_talk[19];
s32 madam_init[18];
static __declspec(section ".data") s32 baba_talk[8];
static __declspec(section ".data") s32 baba_init[9];
__declspec(section ".data") s32 takun4_init[7];
s32 takun4_talk[37];
s32 takun5_init[25];
s32 takun5_talk[28];
s32 takun6_init[25];
s32 takun6_talk[28];
static s32 npc_data[184];
s32 teresa_fuwafuwa[54];
__declspec(section ".data") s32 resaresa_talk[8];
s32 resaresa_entry[35];
__declspec(section ".data") s32 sebaschan_talk[8];
s32 sebaschan_entry[35];
s32 koopa_door_evt[227];
s32 pik_01_koopa_evt[241];
static s32 delete_npc_regl_evt[35];
static __declspec(section ".data") s32 sekai_yami_shake[11];
static s32 sekai_yami_evt[140];
static s32 minnnanokoe_evt[391];
static s32 evt_switch_init[17];
s32 iri_27_npc_entry[26];
s32 pik_01_init_evt[486];

void envAddTev(s32 type, MapTevCallbackInfo* info);

void test_tev2(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}

void envAddTev(s32 type, MapTevCallbackInfo* info);

void test_tev(MapTevCallbackInfo* info) {
    envAddTev(4, info);
}

__declspec(section ".data") u64 fd_pik_01_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_pik_01_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_pik_01___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_pik_01___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_pik_01_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_pik_01___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_pik_01_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_pik_01_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_pik_01_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_pik_01___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_pik_01___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_pik_01_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_pik_01___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_pik_01_one_364[] = {
    1065353216,
};

static s32 dmgReturnPt[] = {
    (s32)"mod_00", 0, -998637568, 0, (s32)"mod_01", 0, -998637568, 0,
    (s32)"mod_02", 0, -998637568, 0, (s32)"mod_03", 0, -998637568, 0,
    (s32)"mod_04", 0, -998637568, 0, (s32)"mod_05", 0, -998637568, 0,
    (s32)"mod_06", 0, -998637568, 0, (s32)"mod_07", 0, -998637568, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(n_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("sha_4_3"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("sha_5_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("sha_4_3"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("sha_5_1"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"nw_bero", 0, 7, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"pik_04", (s32)"se_bero", 65537, 0, 0, (s32)"n_bero",
    65542, 1, 100000, 0, 0, -1, 0, -1,
    0, (s32)"pik_02", (s32)"s_bero", 327685, (s32)n_door_close, (s32)n_door_open, (s32)"dokan_1", 131072,
    9, 100000, 0, 0, -1, 0, 6, 0,
    (s32)"tik_17", (s32)"dokan_1", 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static __declspec(section ".data") s32 name_tbl[] = {
    (s32)"yajirusi_1", (s32)"yajirusi_2",
};

EVT_BEGIN(evt_powan)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_msg_print, 0, STRING("sha_6_1_c"), 0, 0)
    WAIT_MS(300)
    CALL(evt_npc_flag_onoff, 1, STRING("sha_6_2_c"), 131088)
    CALL(evt_npc_set_position, STRING("sha_6_2_c"), -50, 10, -235)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("pik_00"), 0, STRING("sha_6_3"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("pik_01"), 0, STRING("sha_6_3"))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("pik_02"), 0, STRING("sha_6_3"))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING("sha_5_3"), 0, STRING("sha_6_3"))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING("pik_03"), 0, STRING("sha_6_3"))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("pik_04"), 0, STRING("sha_6_3"))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING("pik"), 0, STRING("sha_6_3"))
    END_SWITCH
    WAIT_MS(500)
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_set_dir_to_target, STRING("sha_6_2_c"), STRING("bou_2_c"))
    CALL(evt_msg_print, 0, STRING("bou_3_c"), 0, STRING("sha_6_2_c"))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_party_set_dir, 0, 270, 200)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("bou_4_c"))
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, -350, 120, 40, -55, 50, -236, 500, 11)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_off, 4000, 11)
    CALL(evt_npc_status_onoff, 1, STRING("sha_6_2_c"), 2)
    CALL(evt_npc_move_position, STRING("sha_6_2_c"), 85, -100, 0, FLOAT(50.0f), 1)
    CALL(evt_cam3d_evt_set, -108, 131, 121, 188, 58, -167, 1000, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 228, -140, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 190, -136, FLOAT(80.0f))
        CALL(evt_mario_set_dir, 270, 200, 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("sha_6_2_c"), 159, -171, 0, FLOAT(50.0f), 1)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("jimen"), 0, STRING("sha_6_3"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("yama"), 0, STRING("sha_6_3"))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("iwayama"), 0, STRING("sha_6_3"))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING("hosi_right"), 0, STRING("sha_6_3"))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING("hosi_left"), 0, STRING("sha_6_3"))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("hosi_center"), 0, STRING("sha_6_3"))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING("hosi_right_c"), 0, STRING("sha_6_3"))
    END_SWITCH
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("hosi_left_c"), 0, STRING("sha_6_2_c"))
    CALL(evt_mario_set_pose, STRING("hosi_center_c"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("ranpu"))
    CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_BELL1"), 0, STRING("sha_6_2_c"))
    WAIT_MS(500)
    CALL(evt_npc_move_position, STRING("sha_6_2_c"), 210, -193, 0, FLOAT(50.0f), 1)
    CALL(evt_mobj_lock_unlock, STRING("gor_04"))
    WAIT_MS(1000)
    CALL(evt_npc_move_position, STRING("sha_6_2_c"), 180, -220, 0, FLOAT(50.0f), 1)
    CALL(evt_set_dir_to_target, STRING("sha_6_2_c"), STRING("bou_2_c"))
    SET_VALUE(GSW(0), 335)
    SET_VALUE(LW(0), 1)
    CALL_CHILD(PTR(bero_case_switch_on))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_snd_bgmon, 160, 0)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(init_powan)
    SWITCH(GSW(0))
        CASE_EQUAL(335)
        CALL(evt_npc_set_position, STRING("sha_6_1_c"), 165, 20, -190)
        CALL(evt_npc_flag_onoff, 1, STRING("sha_6_1_c"), 131088)
    END_SWITCH
    RETURN
EVT_END()

USER_FUNC(kpa_lock_hit_scale) {
    MapObjectEntry* mobj = mobjNameToPtr("lock");

    mobj->scale2.x *= 2.0f;
    mobj->scale2.y *= 2.0f;
    mobjCalcMtx2(mobj);
    mobj->flags &= ~4;
    return EVT_RETURN_DONE;
}

USER_FUNC(set_r) {
    MapObjectEntry* mobj = mobjNameToPtr("lock");

    mobj->rotation.y = -45.0f;
    return EVT_RETURN_DONE;
}

static USER_FUNC(starstone_set_ry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 ry = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[7] = ry;
    return EVT_RETURN_DONE;
}

static USER_FUNC(starstone_set_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[2] = x;
    ((f32*)eff->userdata)[3] = y;
    ((f32*)eff->userdata)[4] = z;
    return EVT_RETURN_DONE;
}

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

static USER_FUNC(starstone_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effSetName(effStarStoneEntry(5, x, y, z, 1.0f), name);
    return EVT_RETURN_DONE;
}

static USER_FUNC(anim_tevcallback) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr_NoAssert(name);

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(npc->poseId, (flag & 0xF) << 24);
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") EVT_BEGIN(talk_powan)
    CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_BELL1"), 0, STRING("sha_6_1_c"))
    RETURN
EVT_END()

EVT_BEGIN(miyageya_talk)
    IF_INT_EQUAL(GSW(1420), 27)
        CALL(chk_luigi_color, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            IF_INT_EQUAL(GSWF(5405), 0)
                CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_MOVE1"), 0, 0)
                CALL(evt_mario_set_pose, STRING("hosi_center_c"))
                WAIT_MS(300)
                CALL(evt_mario_set_pose, STRING("hom_00"))
                WAIT_MS(800)
                CALL(evt_mario_set_pose, STRING("ranpu"))
                CALL(evt_msg_print, 0, STRING("sha_6_1_c"), 0, 0)
                SET_VALUE(GSWF(5405), 1)
                ELSE
                CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_MOVE1_2"), 0, 0)
            END_IF
            ELSE
            CALL(evt_npc_flag_onoff, 1, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), 32)
            CALL(evt_cam3d_evt_set, -545, 90, 530, -290, 55, 285, 800, 11)
            BEGIN_INLINE_EVENT
                LOOP(0)
                    CALL(evt_mario_party_use_check, LW(0))
                    IF_INT_EQUAL(LW(0), 0)
                        BREAK_LOOP
                    END_IF
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(evt_party_stop, 0)
                CALL(evt_party_move_pos, 0, -225, 321, 800)
                CALL(evt_party_set_dir, 0, 270, 300)
            END_INLINE_EVENT
            CALL(evt_mario_mov_pos, -245, 300, 800)
            CALL(evt_mario_set_dir, 270, 300, 0)
            WAIT_MS(800)
            CALL(evt_set_dir_to_target, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), STRING("bou_2_c"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("pik_00"), 0, 0)
            CALL(evt_mario_set_pose, STRING("SFX_STG6_TRAIN_MOVE1_3"))
            WAIT_MS(1000)
            CALL(evt_mario_set_pose, STRING("ranpu"))
            CALL(evt_msg_print, 0, STRING("train"), 0, 0)
            CALL(evt_mario_set_pose, STRING("SFX_STG6_TRAIN_MOVE1_2_3"))
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_MOVE2"), 0, 0)
            CALL(evt_npc_get_position, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), LW(0), LW(1), LW(2))
            CALL(evt_get_target_dir, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), STRING("bou_2_c"), LW(3))
            SET_VALUE(LW(4), LW(0))
            SET_VALUE(LW(5), LW(2))
            CALL(evt_npc_add_dirdist, LW(4), LW(5), LW(3), 30)
            CALL(evt_npc_flag_onoff, 1, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), 32)
            CALL(evt_npc_move_position, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), LW(4), LW(5), 0, 50, 0)
            CALL(evt_pouch_get_haveitemcnt, LW(3))
            CALL(evt_pouch_check_item, 1, LW(4))
            IF_INT_EQUAL(LW(4), 0)
                SET_VALUE(LW(4), 10)
                ELSE
                SET_VALUE(LW(4), 20)
            END_IF
            IF_INT_LESS(LW(3), LW(4))
                CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_MOVE2_2"), 0, 0)
                CALL(evt_item_entry, STRING("SFX_STG6_TRAIN_MOVE2_3"), 214, 0, -1000, 0, 17, -1, 0)
                CALL(evt_item_get_item, STRING("SFX_STG6_TRAIN_MOVE2_3"))
                CALL(evt_item_get_item_end_wait, STRING("SFX_STG6_TRAIN_MOVE2_3"))
                SET_VALUE(GSWF(3278), 1)
                CALL(evt_npc_move_position, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), LW(0), LW(2), 0, 50, 0)
                CALL(evt_npc_flag_onoff, 0, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), 32)
                ELSE
                WAIT_MS(500)
                CALL(evt_npc_move_position, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), LW(0), LW(2), 0, 80, 0)
                CALL(evt_npc_flag_onoff, 0, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), 32)
                CALL(evt_msg_print, 0, STRING("SFX_STG6_TRAIN_MOVE2_2_2"), 0, STRING("SFX_STG6_TRAIN_MOVE1_2_2"))
                WAIT_MS(300)
                CALL(evt_item_entry, STRING("pik_01"), 214, -246, 15, 246, 16, GSWF(3278), 0)
                WAIT_MS(300)
                CALL(evt_msg_print, 0, STRING("ranpu_c"), 0, STRING("SFX_STG6_TRAIN_MOVE1_2_2"))
            END_IF
            CALL(evt_npc_set_position, STRING("pika_1_1"), -386, 0, 214)
            CALL(evt_npc_flag_onoff, 1, STRING("pika_1_1"), 131120)
            CALL(evt_npc_move_position, STRING("pika_1_1"), -330, 272, 0, 60, 0)
            CALL(evt_msg_print, 0, STRING("pika_1_2"), 0, STRING("pika_1_1"))
            CALL(evt_mario_set_pose, STRING("ranpu"))
            CALL(evt_mario_set_dir_npc, STRING("pika_1_1"))
            CALL(evt_set_dir_to_target, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), STRING("pika_1_1"))
            WAIT_MS(300)
            CALL(evt_eff_fukidashi, 1, STRING("pika_1_3"), STRING("SFX_STG6_TRAIN_MOVE1_2_2"), 0, 0, 0, 0, 0, 0, 0, 60)
            WAIT_MS(1200)
            CALL(evt_msg_print, 0, STRING("pika_1_4"), 0, 0)
            CALL(evt_npc_get_position, STRING("pika_1_1"), LW(0), LW(1), LW(2))
            CALL(evt_npc_jump_position_nohit, STRING("pika_1_1"), LW(0), LW(1), LW(2), 300, 10)
            CALL(evt_msg_print, 0, STRING("pika_2"), 0, STRING("pika_1_1"))
            CALL(evt_mario_set_pose, STRING("pika_3"))
            WAIT_MS(500)
            CALL(evt_mario_set_pose, STRING("ranpu"))
            CALL(evt_msg_print, 0, STRING("pika_4"), 0, 0)
            CALL(evt_msg_print, 0, STRING("pika_5"), 0, STRING("pika_1_1"))
            CALL(evt_npc_move_position, STRING("pika_1_1"), -386, 214, 0, 150, 0)
            CALL(evt_npc_flag_onoff, 0, STRING("pika_1_1"), 131088)
            CALL(evt_npc_set_position, STRING("pika_1_1"), 0, -1000, 0)
            CALL(evt_set_dir_to_target, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), STRING("bou_2_c"))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("pika_6"), 0, 0)
            CALL(evt_mario_set_dir_npc, STRING("SFX_STG6_TRAIN_MOVE1_2_2"))
            WAIT_MS(600)
            CALL(evt_mario_set_pose, STRING("SFX_STG6_TRAIN_MOVE1_3"))
            WAIT_MS(500)
            CALL(evt_mario_set_pose, STRING("ranpu"))
            CALL(evt_msg_print, 0, STRING("pika_1_1_c"), 0, 0)
            CALL(evt_cam3d_evt_off, 800, 11)
            WAIT_MS(800)
            SET_VALUE(GSW(1420), 0)
            SET_VALUE(GSWF(5401), 1)
            CALL(evt_msg_print, 0, STRING("pika_1_2_c"), 0, 0)
            CALL(evt_party_run, 0)
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING("pika_1_3_c"), 0, STRING("sha_6_1_c"))
        CASE_BETWEEN(373, 376)
        IF_INT_EQUAL(LSWF(1), 0)
            CALL(evt_npc_set_force_regl_anim, STRING("sha_6_1_c"), STRING("pika_1_4_c"))
            CALL(evt_npc_set_anim, STRING("sha_6_1_c"), STRING("pika_6_c"))
            CALL(evt_npc_set_autotalkpose, STRING("sha_6_1_c"), STRING("pika_1_4_c"), STRING("hom_10"))
            CALL(evt_msg_print, 0, STRING("hom_11"), 0, STRING("sha_6_1_c"))
            CALL(evt_npc_flag_onoff, 0, STRING("sha_6_1_c"), 512)
            SET_VALUE(LSWF(1), 1)
            ELSE
            CALL(evt_msg_print, 0, STRING("hom_12"), 0, STRING("sha_6_1_c"))
        END_IF
        CASE_DEFAULT
        CALL(chk_luigi_color, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            IF_INT_LESS_OR_EQUAL(GSW(0), 402)
                CALL(evt_msg_print, 0, STRING("rsh_06_a"), 0, STRING("sha_6_1_c"))
                ELSE
                CALL(evt_msg_print, 0, STRING("train_7"), 0, STRING("sha_6_1_c"))
            END_IF
            ELSE
            IF_INT_EQUAL(GSWF(5401), 0)
                CALL(evt_msg_print, 0, STRING("train_8"), 0, STRING("sha_6_1_c"))
                ELSE
                CALL(evt_npc_get_position, STRING("sha_6_1_c"), LW(0), LW(1), LW(2))
                CALL(evt_npc_jump_position_nohit, STRING("sha_6_1_c"), LW(0), LW(1), LW(2), 200, 10)
                CALL(evt_msg_print, 0, STRING("renketu_6"), 0, STRING("sha_6_1_c"))
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(miyageya_init)
    CALL(evt_npc_set_position, STRING("sha_6_1_c"), -270, -5, 260)
    SWITCH(GSW(0))
        CASE_BETWEEN(373, 376)
        CALL(evt_npc_flag_onoff, 0, STRING("sha_6_1_c"), 1024)
    END_SWITCH
    CALL(evt_npc_change_interrupt, STRING("sha_6_1_c"), 6, PTR(miyageya_talk))
    RETURN
EVT_END()

__declspec(section ".data") s32 iri_29_item_tbl1[] = {
    204, -1,
};

__declspec(section ".data") s32 iri_29_item_tbl2[] = {
    170, -1,
};

__declspec(section ".data") s32 iri_29_item_tbl3[] = {
    162, -1,
};

EVT_BEGIN(konarikin_talk)
    IF_INT_EQUAL(GSW(1420), 29)
        IF_INT_EQUAL(GSWF(5406), 0)
            IF_INT_EQUAL(GSWF(5405), 0)
                CALL(evt_msg_print, 0, STRING("renketu_7"), 0, 0)
                CALL(evt_msg_select, 0, STRING("train_1"))
                IF_INT_GREATER_OR_EQUAL(LW(0), 3)
                    CALL(evt_msg_continue)
                    RETURN
                END_IF
                SET_VALUE(GSW(1469), LW(0))
                CALL(evt_msg_print_add, 0, STRING("train_6"))
                SET_VALUE(GSWF(5405), 1)
                ELSE
                CALL(evt_pouch_check_item, 100, LW(0))
                IF_INT_GREATER(LW(0), 0)
                    CALL(evt_msg_print, 0, STRING("renketu_1"), 0, 0)
                    RETURN
                END_IF
                SWITCH(GSW(1469))
                    CASE_EQUAL(0)
                    CALL(evt_pouch_check_item, 204, LW(0))
                    IF_INT_GREATER(LW(0), 0)
                        CALL(evt_msg_print, 0, STRING("renketu_5"), 0, 0)
                        CALL(evt_win_item_select, 0, PTR(iri_29_item_tbl1), LW(0), 0)
                        IF_INT_NOT_EQUAL(LW(0), -1)
                            CALL(evt_pouch_remove_item, 204, LW(0))
                            CALL(evt_msg_print, 0, STRING("ENV_STG6_RSH2"), 0, 0)
                            CALL(evt_item_entry, STRING("renketu"), 100, 0, -1000, 0, 17, -1, 0)
                            CALL(evt_item_get_item, STRING("renketu"))
                            CALL(evt_item_get_item_end_wait, STRING("renketu"))
                        END_IF
                        ELSE
                        CALL(evt_msg_print, 0, STRING("renketu_2"), 0, 0)
                    END_IF
                    CASE_EQUAL(1)
                    CALL(evt_pouch_check_item, 170, LW(0))
                    IF_INT_GREATER(LW(0), 0)
                        CALL(evt_msg_print, 0, STRING("renketu_3"), 0, 0)
                        CALL(evt_win_item_select, 0, PTR(iri_29_item_tbl2), LW(0), 0)
                        IF_INT_NOT_EQUAL(LW(0), -1)
                            CALL(evt_pouch_remove_item, 170, LW(0))
                            CALL(evt_msg_print, 0, STRING("renketu_4"), 0, 0)
                            CALL(evt_item_entry, STRING("renketu"), 100, 0, -1000, 0, 17, -1, 0)
                            CALL(evt_item_get_item, STRING("renketu"))
                            CALL(evt_item_get_item_end_wait, STRING("renketu"))
                        END_IF
                        ELSE
                        CALL(evt_msg_print, 0, STRING("rsh_02_a"), 0, 0)
                    END_IF
                    CASE_EQUAL(2)
                    CALL(evt_pouch_check_item, 162, LW(0))
                    IF_INT_GREATER(LW(0), 0)
                        CALL(evt_msg_print, 0, STRING("nidome"), 0, 0)
                        CALL(evt_win_item_select, 0, PTR(iri_29_item_tbl3), LW(0), 0)
                        IF_INT_NOT_EQUAL(LW(0), -1)
                            CALL(evt_pouch_remove_item, 162, LW(0))
                            CALL(evt_msg_print, 0, STRING("se_bero"), 0, 0)
                            CALL(evt_item_entry, STRING("renketu"), 100, 0, -1000, 0, 17, -1, 0)
                            CALL(evt_item_get_item, STRING("renketu"))
                            CALL(evt_item_get_item_end_wait, STRING("renketu"))
                        END_IF
                        ELSE
                        CALL(evt_msg_print, 0, STRING("pik_04"), 0, 0)
                    END_IF
                END_SWITCH
            END_IF
            ELSE
            CALL(evt_msg_print, 0, STRING("nw_bero"), 0, 0)
            CALL(evt_mario_set_pose, STRING("sha_6_1"))
            WAIT_MS(500)
            CALL(evt_mario_set_pose, STRING("ranpu"))
            CALL(evt_msg_print, 0, STRING("sha_5_3"), 0, 0)
            CALL(evt_sub_get_coin, 3)
            BEGIN_INLINE_EVENT
                WAIT_MS(300)
                CALL(evt_mario_set_dir_npc, STRING("sha_5_2"))
            END_INLINE_EVENT
            BEGIN_INLINE_EVENT
                WAIT_MS(300)
                CALL(evt_party_set_dir_npc, 0, STRING("sha_5_2"))
            END_INLINE_EVENT
            CALL(evt_npc_flag_onoff, 1, STRING("sha_6_1_c"), 32)
            CALL(evt_npc_status_onoff, 1, STRING("sha_6_1_c"), 2)
            CALL(evt_npc_move_position, STRING("sha_6_1_c"), -222, -225, 0, 120, 0)
            CALL(evt_npc_set_position, STRING("sha_6_1_c"), 0, -1000, 0)
            SET_VALUE(GSW(1420), 0)
            SET_VALUE(GSWF(5403), 1)
            CALL(evt_msg_print, 0, STRING("pika_1_2_c"), 0, 0)
        END_IF
        RETURN
    END_IF
    CALL(evt_msg_print, 0, STRING("sha_6_2"), 0, STRING("sha_6_1_c"))
    CALL(evt_msg_select, 0, STRING("n_bero"))
    CALL(evt_msg_continue)
    CALL(evt_npc_set_autotalkpose, STRING("bou_2_c"), STRING("sha_1_1_c"), STRING("rsh_01_a"))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_msg_print, 0, STRING("s_bero"), 0, STRING("bou_2_c"))
        CALL(evt_npc_set_autotalkpose, STRING("sha_6_1_c"), STRING("sha_1_4_c"), STRING("sha_1_5_c"))
        CALL(evt_msg_print, 0, STRING("n_1_door_close"), 0, STRING("sha_6_1_c"))
        CALL(evt_npc_flag_onoff, 1, STRING("sha_6_1_c"), 32)
        CALL(evt_npc_flag_onoff, 0, STRING("sha_6_1_c"), 1024)
        CALL(evt_npc_status_onoff, 1, STRING("sha_6_1_c"), 2)
        CALL(evt_npc_set_anim, STRING("sha_6_1_c"), STRING("n_1_door_open"))
        CALL(evt_npc_get_position, STRING("sha_6_1_c"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("yajirusi_1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_move_position, STRING("sha_6_1_c"), -200, 380, 0, FLOAT(150.0f), 0)
        CALL(evt_npc_set_position, STRING("sha_6_1_c"), 0, -1000, 0)
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("yajirusi_2"), 0, STRING("bou_2_c"))
        CALL(evt_msg_print, 0, STRING("yajirusi_3"), 0, STRING("sha_6_1_c"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("yajirusi_4"), 0, STRING("bou_2_c"))
        CALL(evt_msg_print, 0, STRING("yajirusi_5"), 0, STRING("sha_6_1_c"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(konarikin_init)
    CALL_CHILD(PTR(npc_init_evt))
    IF_INT_EQUAL(GSW(1420), 29)
        CALL(evt_npc_set_position, STRING("sha_6_1_c"), -62, -5, -367)
        RETURN
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        IF_INT_LESS(GSW(0), 376)
            CALL(evt_npc_set_position, STRING("sha_6_1_c"), 145, 0, 380)
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(narikin_papa_mama_talk)
    CALL(evt_cam3d_evt_set, -109, 163, 752, -109, 67, 211, 800, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("yajirusi_6"), 0, STRING("SFX_DOOR_OPEN_SLIDE1_3"))
    CALL(evt_msg_print, 0, STRING("tobira"), 0, STRING("SFX_DOOR_SHUT_SLIDE1_3"))
    CALL(evt_msg_print, 0, STRING("駅員"), 0, STRING("SFX_DOOR_OPEN_SLIDE1_3"))
    CALL(evt_msg_print, 0, STRING("train_07"), 0, STRING("SFX_DOOR_SHUT_SLIDE1_3"))
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_npc_set_autotalkpose, STRING("bou_2_c"), STRING("sha_1_1_c"), STRING("rsh_01_a"))
    CALL(evt_msg_print, 0, STRING("nidome_start"), 0, STRING("bou_2_c"))
    RETURN
EVT_END()

EVT_BEGIN(narikin_papa_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_flag_onoff, 1, STRING("sha_6_1_c"), 16777216)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        IF_INT_LESS(GSW(0), 376)
            CALL(evt_npc_set_position, STRING("sha_6_1_c"), -6, -5, 161)
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(narikin_mama_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_flag_onoff, 1, STRING("sha_6_1_c"), 16777216)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        IF_INT_LESS(GSW(0), 376)
            CALL(evt_npc_set_position, STRING("sha_6_1_c"), 18, -5, 185)
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(madam_talk)
    CALL(evt_msg_print, 0, STRING("me"), 0, STRING("sha_6_1_c"))
    CALL(evt_npc_set_autotalkpose, STRING("bou_2_c"), STRING("sha_1_1_c"), STRING("rsh_01_a"))
    CALL(evt_msg_print, 0, STRING("stg6_pik_00"), 0, STRING("bou_2_c"))
    RETURN
EVT_END()

EVT_BEGIN(madam_init)
    CALL_CHILD(PTR(npc_init_evt))
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        IF_INT_LESS(GSW(0), 376)
            CALL(evt_npc_set_position, STRING("sha_6_1_c"), -395, 0, -72)
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(baba_talk)
    CALL(evt_msg_print, 0, STRING("train_06"), 0, STRING("sha_6_1_c"))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(baba_init)
    CALL_CHILD(PTR(npc_init_evt))
    CALL(evt_npc_status_onoff, 1, STRING("sha_6_1_c"), 2)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(takun4_init)
    CALL(evt_npc_flag_onoff, 1, STRING("train_00"), 1536)
    RETURN
EVT_END()

EVT_BEGIN(takun4_talk)
    SWITCH(GSW(0))
        CASE_LESS(347)
        CALL(evt_msg_print, 0, STRING("train_01"), 0, STRING("sha_6_1_c"))
        CASE_BETWEEN(373, 376)
        CALL(evt_msg_print, 0, STRING("train_03"), 0, STRING("sha_6_1_c"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("train_05"), 0, STRING("sha_6_1_c"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("M_C_3"), 0, STRING("sha_6_1_c"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(takun5_init)
    CALL(evt_npc_flag_onoff, 1, STRING("ticket"), 1536)
    SWITCH(GSW(0))
        CASE_BETWEEN(373, 376)
        CALL(evt_npc_set_position, STRING("ticket"), 0, -1000, 0)
        CASE_DEFAULT
        CALL(evt_npc_flag_onoff, 1, STRING("ticket"), 131088)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(takun5_talk)
    SWITCH(GSW(0))
        CASE_LESS(347)
        CALL(evt_msg_print, 0, STRING("M_S_1"), 0, STRING("sha_6_1_c"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("train_04"), 0, STRING("sha_6_1_c"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("train_02"), 0, STRING("sha_6_1_c"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(takun6_init)
    CALL(evt_npc_flag_onoff, 1, STRING("stg7_pik_01"), 1536)
    SWITCH(GSW(0))
        CASE_BETWEEN(373, 376)
        CALL(evt_npc_set_position, STRING("stg7_pik_01"), 0, -1000, 0)
        CASE_DEFAULT
        CALL(evt_npc_flag_onoff, 1, STRING("stg7_pik_01"), 131088)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(takun6_talk)
    SWITCH(GSW(0))
        CASE_LESS(347)
        CALL(evt_msg_print, 0, STRING("ナリキンパパ"), 0, STRING("sha_6_1_c"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("M_I_2"), 0, STRING("sha_6_1_c"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg7_pik_02"), 0, STRING("sha_6_1_c"))
    END_SWITCH
    RETURN
EVT_END()

static s32 npc_data[] = {
    (s32)/*"ポワン探偵"*/"\x83\x7C\x83\x8F\x83\x93\x92\x54\x92\xE3", 1073743360, 0, (s32)init_powan, 0, (s32)talk_powan, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"土産屋"*/"\x93\x79\x8E\x59\x89\xAE",
    1073743360, 0, (s32)miyageya_init, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ナリキンママ"*/"\x83\x69\x83\x8A\x83\x4C\x83\x93\x83\x7D\x83\x7D", 0,
    0, (s32)narikin_mama_init, 0, (s32)narikin_papa_mama_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"ナリキンパパ"*/"\x83\x69\x83\x8A\x83\x4C\x83\x93\x83\x70\x83\x70", 0, 0,
    (s32)narikin_papa_init, 0, (s32)narikin_papa_mama_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"コナリキン"*/"\x83\x52\x83\x69\x83\x8A\x83\x4C\x83\x93", 0, 0, (s32)konarikin_init,
    0, (s32)konarikin_talk, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"マダム"*/"\x83\x7D\x83\x5F\x83\x80", 0, 0, (s32)madam_init, 0,
    (s32)madam_talk, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"ババ"*/"\x83\x6F\x83\x6F", 0, 0, (s32)baba_init, 0, (s32)baba_talk,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(teresa_fuwafuwa)
    CALL(evt_npc_get_position, STRING("sha_6_1_c"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), 0)
    CALL(evt_seq_wait, 2)
    CALL(evt_sub_random, 14, LW(4))
    ADD(LW(4), 1)
    MULTIPLY(LW(4), 30)
    WAIT_MS(LW(4))
    LOOP(0)
        CALL(evt_sub_get_sincos, LW(3), LW(4), LW(5))
        MULTIPLY_FLOAT(LW(4), FLOAT(1.5f))
        ADD_FLOAT(LW(4), LW(1))
        CALL(evt_npc_set_position, STRING("sha_6_1_c"), LW(0), LW(4), LW(2))
        ADD(LW(3), 3)
        MODULO(LW(3), 360)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(resaresa_talk)
    CALL(evt_msg_print, 0, STRING("stg7_pik_06"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(resaresa_entry)
    CALL(evt_npc_entry, STRING("stg7_pik_08"), STRING("stg7_pik_07"))
    CALL(evt_npc_set_tribe, STRING("stg7_pik_08"), STRING("stg7_pik_08"))
    CALL(evt_npc_set_position, STRING("stg7_pik_08"), 30, 15, 120)
    CALL(evt_npc_set_ry, STRING("stg7_pik_08"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("stg7_pik_08"), 4194816)
    CALL(evt_npc_change_interrupt, STRING("stg7_pik_08"), 1, PTR(teresa_fuwafuwa))
    CALL(evt_npc_change_interrupt, STRING("stg7_pik_08"), 6, PTR(resaresa_talk))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(sebaschan_talk)
    CALL(evt_msg_print, 0, STRING("stg7_pik_09"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(sebaschan_entry)
    CALL(evt_npc_entry, STRING("stg7_pik_10"), STRING("stg7_pik_11"))
    CALL(evt_npc_set_tribe, STRING("stg7_pik_10"), STRING("stg7_pik_10"))
    CALL(evt_npc_set_position, STRING("stg7_pik_10"), 75, 4, 90)
    CALL(evt_npc_set_ry, STRING("stg7_pik_10"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("stg7_pik_10"), 20972032)
    CALL(evt_npc_change_interrupt, STRING("stg7_pik_10"), 1, PTR(teresa_fuwafuwa))
    CALL(evt_npc_change_interrupt, STRING("stg7_pik_10"), 6, PTR(sebaschan_talk))
    RETURN
EVT_END()

EVT_BEGIN(koopa_door_evt)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mobj_get_position, STRING("gor_04"), LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dir, LW(3), LW(5), LW(0), LW(2), LW(6))
    SUBTRACT(LW(6), 45)
    IF_INT_LESS(LW(6), 0)
        ADD(LW(6), 360)
    END_IF
    IF_INT_LESS(LW(6), 180)
        CALL(evt_mario_set_dir, 270, 300, 0)
        ELSE
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_IF
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -132, 120, 148, 185, 90, -170, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg7_pik_11_yn"), 0, 0)
    CALL(kpa_chg_pose, STRING("stg7_pik_12"))
    SET_VALUE(GF(0), 0)
    SET_VALUE(GF(1), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(1), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.009765625f), 150)
            WAIT_MS(150)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("stg7_pik_13"), LW(0), LW(1), LW(2), 0)
            CALL(evt_snd_sfxon_3d, STRING("stg7_pik_14"), LW(0), LW(1), LW(2), 0)
            WAIT_MS(300)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(1000)
    SET_VALUE(GF(1), 1)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_msg_print, 0, STRING("stg7_pik_15"), 0, STRING("bou_2_c"))
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mobj_lock_unlock, STRING("gor_04"))
    WAIT_MS(600)
    SET_VALUE(GF(0), 1)
    CALL(evt_msg_print, 0, STRING("stg7_pik_16"), 0, 0)
    CALL(evt_npc_set_autotalkpose, STRING("bou_2_c"), STRING("stg7_pik_17"), STRING("a"))
    CALL(evt_msg_print, 0, STRING("stg7_pik_18"), 0, STRING("bou_2_c"))
    SET_VALUE(LW(1), 1)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(10))
        IF_INT_EQUAL(LW(10), 0)
            SET_FLOAT_VALUE(LW(0), FLOAT(180.0f))
            CALL_CHILD(PTR(n_door_open))
            BREAK_LOOP
            ELSE
            CALL_CHILD(PTR(n_door_open))
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos, 230, -215, 600)
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_bero_mapchange, STRING("stg7_pik_19"), STRING("pika_1_3"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(pik_01_koopa_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, -325, -5, -325)
    CALL(evt_npc_set_position, STRING("irai_25_00"), -425, 25, -425)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("irai_25_00"), 32768)
    CALL(evt_npc_set_ry, STRING("irai_25_00"), 90)
    CALL(evt_cam3d_evt_set, -273, 145, 196, -273, 69, -237, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_npc_flag_onoff, 0, STRING("irai_25_00"), 32768)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("irai_25_00"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("butu"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_kamek_move_position, STRING("irai_25_00"), -327, -327, 10, 0, FLOAT(60.0f), 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -227, -227, FLOAT(60.0f))
    WAIT_MS(500)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("bou_2_c"), STRING("sha_1_1_c"), STRING("rsh_01_a"))
    CALL(evt_msg_print, 0, STRING("irai_25_01"), 0, STRING("bou_2_c"))
    CALL(evt_msg_print, 0, STRING("irai_25_02"), 0, STRING("irai_25_00"))
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_npc_set_anim, STRING("irai_25_00"), STRING("irai_25_03"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -150, 95, 514, 114, 130, -241, 2000, 11)
    WAIT_MS(2000)
    CALL(evt_npc_set_anim, STRING("irai_25_00"), STRING("irai_25_04"))
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -273, 145, 196, -273, 69, -237, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_dir, 270, 300, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, STRING("bou_2_c"))
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_mario_set_dir, 90, 400, 0)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_off, 800, 11)
    SET_VALUE(GSW(0), 374)
    SET_VALUE(GF(1), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(1), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("irai_25_00"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("butu"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_kamek_move_position, STRING("irai_25_00"), -255, -300, 10, 0, 80, 0)
    SET_VALUE(GF(1), 1)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

void envSetYamiView(Mtx mtx);

static USER_FUNC(yami_view) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){0.0f, 100.0f, 100.0f + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){0.0f, 0.0f, z});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}

USER_FUNC(chk_luigi_color) {
    s32* args = event->args;

    if (marioGetColor() == 1) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(delete_npc_regl_evt)
    CALL(evt_npc_get_reglid, STRING("train_00"), LW(0))
    CALL(evt_npc_change_interrupt, STRING("train_00"), 1, 0)
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("ticket"), LW(0))
    CALL(evt_npc_change_interrupt, STRING("ticket"), 1, 0)
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_reglid, STRING("stg7_pik_01"), LW(0))
    CALL(evt_npc_change_interrupt, STRING("stg7_pik_01"), 1, 0)
    DELETE_EVENT(LW(0))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(sekai_yami_shake)
    LOOP(0)
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.009765625f), 500)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(sekai_yami_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("sha_6_2_c"), 40, -5, 100)
    CALL(evt_npc_set_ry, STRING("sha_6_2_c"), 270)
    CALL(evt_map_set_tevcallback, 3, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("stg6_pik_04_03"), 50331648)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("stg6_pik_04_03"), 256)
    CALL(anim_tevcallback, STRING("sha_6_2_c"), 3)
    CALL(anim_tevcallback, STRING("ticket"), 3)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(yami_view, -800)
    CALL(evt_cam3d_evt_set, 15, 134, 667, 15, 38, 126, 0, 11)
    SPAWN_EVENT(PTR(sekai_yami_shake))
    CALL(evt_seq_wait, 2)
    CALL(evt_snd_sfxon, STRING("stg6_pik_04"), LW(0))
    WAIT_MS(800)
    CALL(evt_npc_reverse_ry, STRING("sha_6_2_c"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("sha_6_2_c"))
    CALL(evt_npc_reverse_ry, STRING("sha_6_2_c"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("sha_6_2_c"))
    CALL(evt_msg_print, 0, STRING("stg7_pik_clear_01"), 0, STRING("sha_6_2_c"))
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_reverse_ry, STRING("sha_6_2_c"))
            WAIT_FRAMES(1)
            CALL(evt_npc_wait_pera, STRING("sha_6_2_c"))
            WAIT_MS(200)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_snd_sfxoff, LW(0))
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING("stg7_pik_clear_01_1"), STRING("stg6_pik_05"))
    RETURN
EVT_END()

static EVT_BEGIN(minnnanokoe_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("sha_6_2_c"), 90, -5, 10)
    CALL(evt_npc_set_ry, STRING("sha_6_2_c"), 270)
    CALL(evt_npc_set_position, STRING("stg7_pik_03"), 10, -5, 0)
    CALL(evt_npc_set_ry, STRING("stg7_pik_03"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("stg7_pik_03"), 32768)
    CALL(evt_npc_set_position, STRING("sha_5_2"), 70, 0, -70)
    CALL(evt_npc_set_ry, STRING("sha_5_2"), 270)
    CALL(evt_npc_set_position, STRING("SFX_DOOR_SHUT_SLIDE1_3"), 30, 0, -105)
    CALL(evt_npc_set_ry, STRING("SFX_DOOR_SHUT_SLIDE1_3"), 90)
    CALL(evt_npc_set_position, STRING("SFX_DOOR_OPEN_SLIDE1_3"), 100, 5, -75)
    CALL(evt_npc_set_ry, STRING("SFX_DOOR_OPEN_SLIDE1_3"), 270)
    CALL(evt_map_set_tevcallback, 3, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("stg6_pik_04_03"), 50331648)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("stg6_pik_04_03"), 256)
    CALL(anim_tevcallback, STRING("sha_6_2_c"), 3)
    CALL(anim_tevcallback, STRING("stg7_pik_03"), 3)
    CALL(anim_tevcallback, STRING("sha_5_2"), 3)
    CALL(anim_tevcallback, STRING("SFX_DOOR_SHUT_SLIDE1_3"), 3)
    CALL(anim_tevcallback, STRING("SFX_DOOR_OPEN_SLIDE1_3"), 3)
    CALL(anim_tevcallback, STRING("train_00"), 3)
    CALL(anim_tevcallback, STRING("ticket"), 3)
    CALL(anim_tevcallback, STRING("stg7_pik_01"), 3)
    CALL(yami_view, -800)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(evt_cam3d_evt_set, 50, 120, 750, 50, 55, 0, 0, 11)
    CALL(starstone_entry, STRING("コナリキン"), 50, 50, 0)
    SET_VALUE(GW(0), 50)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(starstone_set_pos, STRING("コナリキン"), 50, GW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(0)
            CALL(starstone_set_ry, STRING("コナリキン"), LW(0))
            SUBTRACT_FLOAT(LW(0), FLOAT(3.0f))
            IF_INT_LESS_OR_EQUAL(LW(0), FLOAT(0.0f))
                ADD_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 5000, 5500, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, 5500, 5000, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(2)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_seq_wait, 2)
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 0, STRING("stg7_pik_03"), 32768)
    CALL(evt_msg_print, 0, STRING("サラリーマン"), 0, STRING("stg7_pik_03"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("door_1"), 0, STRING("sha_6_2_c"))
    CALL(evt_cam3d_evt_set, 50, 78, 349, 50, 47, 0, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("ie_1_N"), 0, STRING("SFX_DOOR_SHUT_SLIDE1_3"))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("ie_1_H"), 0, STRING("SFX_DOOR_OPEN_SLIDE1_3"))
    CALL(evt_npc_set_ry, STRING("sha_5_2"), 90)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("mobj_badge_gat"), 0, STRING("sha_5_2"))
    CALL(evt_npc_set_ry, STRING("sha_5_2"), 270)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("a_door_1_N"), 0, STRING("sha_5_2"))
    CALL(evt_cam3d_evt_set, 50, 120, 750, 50, 55, 0, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("a_door_1"), 0, STRING("stg7_pik_03"))
    CALL(evt_msg_print, 0, STRING("soto_1"), 0, STRING("SFX_DOOR_OPEN_SLIDE1_3"))
    CALL(evt_msg_print, 0, STRING("naka"), 0, STRING("SFX_DOOR_SHUT_SLIDE1_3"))
    CALL(evt_npc_reverse_ry, STRING("sha_6_2_c"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("sha_6_2_c"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("a_ie_1_naka"), 0, STRING("sha_6_2_c"))
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_reverse_ry, STRING("sha_6_2_c"))
            WAIT_MS(500)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(2000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING("stg7_pik_clear_01_1"), STRING("door_2"))
    RETURN
EVT_END()

static EVT_BEGIN(evt_switch_init)
    IF_INT_EQUAL(GSWF(1348), 0)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ie_2_N"), 1)
        CALL(evt_hitobj_onoff, STRING("ie_2_H"), 1, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(iri_27_npc_entry)
    CALL(evt_npc_entry, STRING("pika_1_1"), STRING("ie_2_U"))
    CALL(evt_npc_set_tribe, STRING("pika_1_1"), STRING("pika_1_1"))
    CALL(evt_npc_flag_onoff, 1, STRING("pika_1_1"), 1536)
    CALL(evt_npc_status_onoff, 1, STRING("pika_1_1"), 2)
    CALL(evt_npc_set_position, STRING("pika_1_1"), 0, -1000, 0)
    RETURN
EVT_END()

EVT_BEGIN(pik_01_init_evt)
    SET_VALUE(LF(0), 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 373)
        IF_INT_LESS(GSW(0), 375)
            CALL(evt_mario_set_mode, 2)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    CALL_CHILD(PTR(evt_switch_init))
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mobj_powerupblk, STRING("a_door_2_N"), 400, 95, 125, 0, GSWF(5563), 0)
    IF_INT_EQUAL(LF(0), 1)
        SET_VALUE(LW(0), 0)
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_hitobj_attr_onoff, 1, 0, STRING("a_door_2"), 8388612)
    END_IF
    SET_VALUE(LF(1), 0)
    IF_INT_EQUAL(LF(0), 0)
        IF_INT_EQUAL(GSW(0), 400)
            CALL(evt_bero_get_entername, LW(0))
            IF_STR_EQUAL(LW(0), STRING("stg6_pik_05"))
                CALL(evt_snd_bgmoff, 512)
                CALL(evt_snd_envoff, 512)
                SET_VALUE(LF(1), 1)
            END_IF
            IF_STR_EQUAL(LW(0), STRING("door_2"))
                CALL(evt_snd_bgmon, 512, STRING("stg7_pik_05"))
                CALL(evt_snd_envoff, 512)
                SET_VALUE(LF(1), 1)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(1), 0)
            CALL(evt_snd_bgmon, 512, STRING("soto_2"))
            CALL(evt_snd_envon, 272, STRING("naka_"))
        END_IF
        ELSE
        CALL(evt_snd_bgmon, 512, STRING("a_ie_2_nak"))
        CALL(evt_snd_bgm_scope, 0, 1)
        CALL(evt_snd_bgmon, 512, STRING("naka_"))
    END_IF
    CALL(evt_map_playanim, STRING("a_door_3"), 1, 0)
    CALL(evt_map_playanim, STRING("door_3"), 1, 0)
    CALL(evt_map_playanim, STRING("SFX_DOOR_OPEN_TURN1"), 1, 0)
    CALL(evt_map_playanim, STRING("w_bero"), 1, 0)
    SET_INT_READ_ADDR(PTR(name_tbl))
    LOOP(2)
        READ_INT(LW(9))
        SPAWN_EVENT(PTR(evt_pik_yajirushi))
    END_LOOP
    CALL(evt_hit_damage_return_set, PTR(dmgReturnPt))
    CALL_CHILD(PTR(evt_gazigazi_entry))
    CALL(evt_map_set_tevcallback, 1, PTR(test_tev))
    CALL(evt_map_set_tevcallback, 2, PTR(test_tev2))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("pik_touchaku"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("pik_touchaku"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("OFF_d_two_meku_up"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("OFF_d_two_meku_up"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("img"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("img"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ofs"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ofs"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("SFX_STG6_MAP_CHANGE1"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("SFX_STG6_MAP_CHANGE1"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("A_1"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("A_1"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("naka_1"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("naka_1"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ie_1_1_yuka"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ie_1_1_yuka"), 256)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("SFX_STG6_MAP_CHANGE2"), 33554432)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("SFX_STG6_MAP_CHANGE2"), 256)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(0)
            CALL(evt_mapobj_rotate, 1, STRING("pik_touchaku"), 0, LW(0), 0)
            ADD(LW(0), 1)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_setup, PTR(npc_data))
    IF_INT_EQUAL(LF(1), 0)
        IF_INT_EQUAL(GSW(1420), 27)
            CALL_CHILD(PTR(iri_27_npc_entry))
        END_IF
        IF_INT_EQUAL(GSWF(5401), 1)
            CALL(evt_item_entry, STRING("pik_01"), 214, -246, 15, 246, 16, GSWF(3278), 0)
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 403)
        CALL_CHILD(PTR(resaresa_entry))
        CALL_CHILD(PTR(sebaschan_entry))
    END_IF
    CALL_CHILD(PTR(takun4_init))
    CALL(evt_npc_change_interrupt, STRING("train_00"), 6, PTR(takun4_talk))
    CALL_CHILD(PTR(takun5_init))
    CALL(evt_npc_change_interrupt, STRING("ticket"), 6, PTR(takun5_talk))
    CALL_CHILD(PTR(takun6_init))
    CALL(evt_npc_change_interrupt, STRING("stg7_pik_01"), 6, PTR(takun6_talk))
    IF_INT_LESS(GSW(0), 335)
        CALL(evt_mobj_entry, STRING("gor_04"), STRING("A_2"))
        CALL(evt_mobj_set_position, STRING("gor_04"), 226, 30, -216)
        CALL(evt_mobj_set_anim, STRING("gor_04"), STRING("stg7_pik_04"))
        CALL(set_r)
        SET_VALUE(LW(0), 1)
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_run_case_evt, 9, 1, STRING("item00"), 0, PTR(evt_powan), 0)
        ELSE
        CALL(evt_mapobj_flag_onoff, 0, 1, STRING("train_5"), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mobj_entry, STRING("gor_04"), STRING("A_2"))
        CALL(evt_mobj_flag_onoff, 1, STRING("gor_04"), 32)
        CALL(evt_mobj_set_position, STRING("gor_04"), 226, 30, -216)
        CALL(evt_mobj_set_anim, STRING("gor_04"), STRING("stg7_pik_04"))
        CALL(set_r)
        CALL(kpa_lock_hit_scale)
        SET_VALUE(LW(0), 1)
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("resha"), 1)
        CALL(evt_run_case_evt, 9, 1, STRING("ENV_STG6_PIK1"), 0, PTR(koopa_door_evt), 0)
    END_IF
    IF_INT_EQUAL(GSW(0), 373)
        CALL(evt_mario_kill_party, 0)
        SPAWN_EVENT(PTR(pik_01_koopa_evt))
    END_IF
    IF_INT_EQUAL(GSW(0), 374)
        CALL(evt_mario_set_pos, -227, 0, -227)
        CALL(evt_npc_set_position, STRING("irai_25_00"), -255, 25, -300)
        CALL(evt_mario_set_dir, 90, 0, 0)
        CALL(evt_npc_set_ry, STRING("irai_25_00"), 90)
    END_IF
    IF_INT_EQUAL(GSW(0), 400)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("stg6_pik_05"))
            CALL_CHILD(PTR(delete_npc_regl_evt))
            SPAWN_EVENT(PTR(sekai_yami_evt))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("door_2"))
            CALL_CHILD(PTR(delete_npc_regl_evt))
            SPAWN_EVENT(PTR(minnnanokoe_evt))
        END_IF
    END_IF
    RETURN
EVT_END()

