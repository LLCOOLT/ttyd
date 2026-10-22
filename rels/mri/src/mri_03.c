#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/mapdrv.h"
#include "dolphin/gx.h"
#include "memory.h"
#include "dolphin/mtx.h"

static u8* _ap;
typedef struct PuniData { u8 field_0x0[0x4]; u32 flags; u8 field_0x8[0xC - 0x8]; s16 field_0xC; u8 field_0xE[0x114 - 0xE]; u16 field_0x114; u8 field_0x116[0x118 - 0x116]; s16 field_0x118; u8 field_0x11A[0x11E - 0x11A]; s16 field_0x11E; u8 field_0x120[0x12C - 0x120]; Vec position; u8 field_0x138[0x15C - 0x138]; Vec field_0x15C; u8 field_0x168[0x174 - 0x168]; f32 field_0x174; u8 field_0x178[0x180 - 0x178]; f32 field_0x180; u8 field_0x184[0x1E0 - 0x184]; s32 field_0x1E0; s32 field_0x1E4; u8 field_0x1E8[0x56C - 0x1E8]; void* field_0x56C; void* field_0x570; u8 field_0x574[0x5A8 - 0x574]; } PuniData;
extern s32 JailAwayTable_New[];
void puniMoveAtari(PuniData* puni, Vec pos, Vec dir, s32 flag, f32 speed);
PuniData* puniGetPunidat(void);
void puniModeEventparent(PuniData* puni);
void puniMoveDecel(PuniData* puni);

USER_FUNC(evt_bero_exec_onoff);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_in);
USER_FUNC(evt_fade_out);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_flag_on);
USER_FUNC(evt_item_get_position);
USER_FUNC(evt_item_move_3d_position);
USER_FUNC(evt_item_set_position);
USER_FUNC(evt_item_set_scale);
USER_FUNC(evt_map_blend_off);
USER_FUNC(evt_map_blend_set_flag);
USER_FUNC(evt_map_blend_set_mobj_flag);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_blend);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_dispdir);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_dispdir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_sleep_off);
USER_FUNC(evt_mario_sleep_on);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mri_get16bitdata);
USER_FUNC(evt_msg_close);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_repeat);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_msg_togelr);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_get_reglid);
USER_FUNC(evt_npc_jump_position_nohit);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_restart_regular_event);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_autotalkpose);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_ry_lr);
USER_FUNC(evt_npc_set_scale);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_dispflg_onoff);
USER_FUNC(evt_party_get_dispdir);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_jump_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_dispdir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_sleep_off);
USER_FUNC(evt_party_sleep_on);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_puni_flag_onoff);
USER_FUNC(evt_puni_get_lsw_index);
USER_FUNC(evt_puni_get_position);
USER_FUNC(evt_puni_init_puni);
USER_FUNC(evt_puni_mem_init);
USER_FUNC(evt_puni_move_position);
USER_FUNC(evt_puni_pera_onoff);
USER_FUNC(evt_puni_puninum_onoff);
USER_FUNC(evt_puni_set_anim);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_lsw_index);
USER_FUNC(evt_puni_set_mode);
USER_FUNC(evt_puni_set_position);
USER_FUNC(evt_puni_set_trap_index);
USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_puni_wait_systemmode);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_get_value_para);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_spline_get_value);
USER_FUNC(evt_sub_spline_init);
USER_FUNC(evt_win_item_desttable);
USER_FUNC(evt_win_item_maketable);
USER_FUNC(evt_win_item_select);
USER_FUNC(puni_away);
USER_FUNC(puni_parent);
static void alpha_tev(MapTevCallbackInfo* info);
static USER_FUNC(alpha_init_func);
static USER_FUNC(alpha_set_func);
void puniModeEventparent(PuniData* puni);
extern s32 evt_bero_info_run[];
extern s32 evt_sub_kusa_access_entry[];
extern s32 mri_countdown[];
extern s32 mri_guide_goryu[];
extern s32 mri_guide_hagure_check[];
extern s32 mri_puni_init[];
extern s32 mri_puni_walk_se[];
extern s32 puni_disp_info[];

__declspec(section ".data") u64 fd_mri_03_negone_one_374;
__declspec(section ".data") s32 fd_mri_03_neg_one_382[1];
__declspec(section ".data") s32 fd_mri_03___local_PI_383[1];
__declspec(section ".data") s32 fd_mri_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mri_03_one_negone_373;
__declspec(section ".data") s32 fd_mri_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mri_03_one_381[1];
__declspec(section ".data") u64 fd_mri_03_negone_one_360;
__declspec(section ".data") s32 fd_mri_03_neg_one_365[1];
__declspec(section ".data") s32 fd_mri_03___local_PI_366[1];
__declspec(section ".data") s32 fd_mri_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mri_03_one_negone_359;
__declspec(section ".data") s32 fd_mri_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mri_03_one_364[1];
s32 jail_alpha_mario_check[24];
s32 jail_alpha[220];
s32 after_2hours[73];
static s32 spline_dt[24];
s32 spline_dt1[15];
s32 elder_rescue[771];
static s32 elder_init[13];
static s32 elder_talk[13];
static s32 sister_init[13];
s32 sister_regl[21];
static __declspec(section ".data") s32 sister_talk[8];
static s32 guide_init[16];
static __declspec(section ".data") s32 guide_talk[8];
s32 puni_3_init[17];
s32 puni_3_talk[20];
static s32 npcEnt[115];
s32 bero_custom_00[37];
static s32 bero_entry_data[45];
static s32 puni_rand_position[89];
s32 jail_init_00[52];
s32 red_jail_open[63];
s32 evt_opendoor00[19];
static __declspec(section ".data") s32 evt_unlock00[6];
__declspec(section ".data") s32 evt_unlock00_01[4];
__declspec(section ".data") s32 key_table00[2];
s32 evt_check00[23];
s32 blue_jail_open[65];
s32 evt_opendoor01[19];
static __declspec(section ".data") s32 evt_unlock01[8];
__declspec(section ".data") s32 key_table01[3];
s32 evt_check01[90];
s32 bluejail_alpha[119];
s32 bluejail_event[249];
static s32 mario_kirimomi_event[50];
s32 party_kirimomi_event[57];
s32 JailAwayTable_New[15];
s32 kinoko_small[35];
s32 guide_sister[775];
s32 elder_shaberi[13];
s32 toraware_elder[423];
s32 guide_sister_before[128];
static s32 ueki_access_data[20];
s32 mri_03_init_evt[206];

static void alpha_tev(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    u8* alpha = _ap;

    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, *alpha});
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
    info->tevStage++;
}

static USER_FUNC(alpha_init_func) {
    _ap = _mapAlloc(1);
    *_ap = 255;
    return EVT_RETURN_DONE;
}

static USER_FUNC(alpha_set_func) {
    *_ap = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_mri_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mri_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mri_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mri_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mri_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mri_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mri_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mri_03_one_364[] = {
    1065353216,
};

EVT_BEGIN(jail_alpha_mario_check)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS_OR_EQUAL(LW(2), -81)
            SET_VALUE(GW(2), 80)
            ELSE
            SET_VALUE(GW(2), 255)
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(jail_alpha)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_l_saku"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_l_doa"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_l_01"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_saku"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_doa"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_01"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("mario"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("party"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("プニ族長老"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイド妹"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイド"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("プニ族"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("プニ族３"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイドsp"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイド妹sp"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ちびトゲsp"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ライバルsp"), 2048)
    IF_INT_EQUAL(GSWF(2832), 0)
        CALL(evt_map_blend_set_mobj_flag, 1, STRING("mobj_lock00"), 2048)
    END_IF
    IF_INT_EQUAL(GSWF(2834), 0)
        CALL(evt_map_blend_set_mobj_flag, 1, STRING("mobj_lock01"), 2048)
    END_IF
    IF_INT_EQUAL(GSWF(5613), 0)
        CALL(evt_map_blend_set_mobj_flag, 1, STRING("kururin1"), 2048)
    END_IF
    SPAWN_EVENT(PTR(jail_alpha_mario_check))
    SET_VALUE(LW(10), 255)
    SET_VALUE(GW(2), 255)
    SET_VALUE(GW(3), 255)
    SET_VALUE(GF(2), 0)
    LOOP(0)
        IF_INT_EQUAL(GF(2), 0)
            IF_INT_LESS(GW(2), LW(10))
                ADD(LW(10), -5)
                IF_INT_GREATER(GW(2), LW(10))
                    SET_VALUE(LW(10), GW(2))
                END_IF
            END_IF
            IF_INT_GREATER(GW(2), LW(10))
                ADD(LW(10), 5)
                IF_INT_LESS(GW(2), LW(10))
                    SET_VALUE(LW(10), GW(2))
                END_IF
            END_IF
            CALL(evt_map_set_blend, 0, 255, 255, 255, LW(10))
            ELSE
            IF_INT_LESS(GW(3), LW(10))
                ADD(LW(10), -5)
                IF_INT_GREATER(GW(3), LW(10))
                    SET_VALUE(LW(10), GW(3))
                END_IF
            END_IF
            IF_INT_GREATER(GW(3), LW(10))
                ADD(LW(10), 5)
                IF_INT_LESS(GW(3), LW(10))
                    SET_VALUE(LW(10), GW(3))
                END_IF
            END_IF
            CALL(evt_map_set_blend, 0, 255, 255, 255, LW(10))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(after_2hours)
    CALL(evt_map_blend_off, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("mario"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("party"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("プニ族長老"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("ガイド妹"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("ガイド"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("プニ族"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("プニ族３"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("ガイドsp"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("ガイド妹sp"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("ちびトゲsp"), 2048)
    CALL(evt_map_blend_set_flag, 0, STRING("ライバルsp"), 2048)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 255)
    RETURN
EVT_END()

static s32 spline_dt[] = {
    1124335616, 0, -1021771776, 1119783119, 0, -1026019771, 1117953286, 0,
    -1026988710, 1117746339, 0, -1030576294, 1122675534, 0, -1033062897, 1126304632,
    0, -1034662334, 1130669741, 0, 1108430112, 1131770994, 0, 1102220859,
};

s32 spline_dt1[] = {
    1120141312, 0, -1021575168, 1115830412, 0, -1029670663, 1113754391, 0,
    -1033531819, -1064650175, 0, -1037864458, -1022296064, 0, -1032847360,
};

EVT_BEGIN(elder_rescue)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_cam3d_evt_set, 105, 82, 92, 105, 30, -203, 1000, 11)
    CALL(evt_npc_flag_onoff, 1, STRING("プニ族長老"), 1073741856)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1073741856)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1536)
    CALL_CHILD(PTR(mri_guide_goryu))
    CALL(evt_puni_set_mode, 1, 30)
    CALL(evt_puni_get_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_puni_set_position, 1, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    SET_VALUE(GW(3), 80)
    SET_VALUE(GF(2), 1)
    SET_VALUE(LW(0), STRING("ガイド"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイド"), 98, -156, 0, FLOAT(120.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_npc_set_ry, STRING("ガイド"), 90)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_00"), 0, STRING("ガイド"))
    CALL(evt_npc_set_ry, STRING("プニ族長老"), 270)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_mario_mov_pos2, 69, -144, FLOAT(100.0f))
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    CALL(evt_party_move_pos2, 0, 63, -170, FLOAT(150.0f))
    CALL(evt_party_set_dir, 0, 90, -1)
    WAIT_MS(300)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, FLOAT(105.0f), FLOAT(73.59961f), FLOAT(44.299805f), FLOAT(105.0f), FLOAT(30.0f), FLOAT(-203.0f), 1000, 8)
        WAIT_MS(900)
        CALL(evt_cam3d_evt_set, 105, 82, 92, 105, 30, -203, 400, 11)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("プニ族長老"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_CHOUROU_BIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_sub_intpl_msec_init, 8, FLOAT(1.0f), FLOAT(2.5f), 700)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_npc_set_scale, STRING("プニ族長老"), LW(0), LW(0), LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_7"))
        WAIT_MS(1000)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), 2)
        CALL(evt_party_jump_pos, 0, LW(0), LW(1), LW(2), 400, 1, -1000)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_EVT_STG2_PUNI1"))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_01"), 0, STRING("プニ族長老"))
    WAIT_WHILE(GF(0))
    CALL(evt_sub_intpl_msec_init, 5, FLOAT(2.5f), FLOAT(1.0f), 200)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_npc_set_scale, STRING("プニ族長老"), LW(0), LW(0), LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_continue)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_02"), 0, STRING("ガイド"))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_03"), 0, STRING("プニ族長老"))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_04"), 0, STRING("ガイド"))
    CALL(evt_npc_get_position, STRING("プニ族長老"), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("プニ族長老"), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("プニ族長老"), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_npc_get_position, STRING("プニ族長老"), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("プニ族長老"), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("プニ族長老"), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_05"), 0, STRING("プニ族長老"))
    CALL(evt_snd_bgmoff, 26625)
    CALL(evt_fade_out, 1000)
    WAIT_MS(100)
    CALL(evt_fade_entry, 12, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_06"), 0, 0)
    BEGIN_INLINE_EVENT_GET_ID(GW(1))
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SLEEP1"), LW(0), LW(1), LW(2), 0)
            WAIT_MS(3000)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_mario_sleep_on)
    CALL(evt_party_sleep_on, 0)
    WAIT_MS(1000)
    CALL(evt_fade_entry, 11, 0, 0, 0, 0)
    CALL(evt_snd_bgmon, 161, 0)
    CALL(evt_fade_in, 1000)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_07"), 0, STRING("プニ族長老"))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_08"), 0, STRING("ガイド"))
    CALL(evt_npc_get_position, STRING("プニ族長老"), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("プニ族長老"), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("プニ族長老"), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_npc_get_position, STRING("プニ族長老"), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("プニ族長老"), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("プニ族長老"), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_09"), 0, STRING("プニ族長老"))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_10"), 0, STRING("ガイド"))
    CALL(evt_npc_get_position, STRING("プニ族長老"), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("プニ族長老"), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("プニ族長老"), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_11"), 0, STRING("プニ族長老"))
    CALL(evt_snd_bgmoff_f, 513, 1000)
    CALL(evt_cam3d_evt_off, 1000, 11)
    CALL(evt_npc_status_onoff, 1, STRING("プニ族長老"), 2)
    CALL(evt_sub_spline_init, 0, 0, PTR(spline_dt), 8, 30, 0)
    LABEL(0)
    CALL(evt_sub_spline_get_value, LW(3), LW(4), LW(5), LW(6))
    SET_VALUE(LW(0), STRING("プニ族長老"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("プニ族長老"), LW(3), LW(5), 160, 0, 0)
    DELETE_EVENT(LW(9))
    IF_INT_EQUAL(LW(6), 1)
        GOTO(0)
    END_IF
    CALL(evt_npc_set_position, STRING("プニ族長老"), 0, -1000, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_12"), 0, STRING("ガイド"))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_cam3d_evt_set, -155, 85, 204, -155, 50, 7, 1500, 11)
    END_INLINE_EVENT
    CALL(evt_npc_status_onoff, 1, STRING("ガイド"), 2)
    CALL(evt_sub_spline_init, 0, 0, PTR(spline_dt1), 5, 15, 0)
    LABEL(1)
    CALL(evt_sub_spline_get_value, LW(3), LW(4), LW(5), LW(6))
    SET_VALUE(LW(0), STRING("ガイド"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイド"), LW(3), LW(5), 160, 0, 0)
    DELETE_EVENT(LW(9))
    IF_INT_EQUAL(LW(6), 1)
        GOTO(1)
    END_IF
    WAIT_MS(100)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_12_01"), 0, STRING("ガイド"))
    DELETE_EVENT(GW(1))
    CALL(evt_mario_sleep_off)
    CALL(evt_party_sleep_off, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_pos, -10, 0, -52)
        CALL(evt_mario_mov_pos2, -110, -52, FLOAT(120.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_pos, 0, 32, 0, -52)
        CALL(evt_party_move_pos2, 0, -68, -52, FLOAT(120.0f))
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_12_02"), 0, STRING("ガイド妹"))
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_npc_get_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ガイド"), 0, -1000, 0)
    CALL(evt_puni_set_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_puni_set_mode, 1, 1)
    SET_VALUE(GF(2), 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSW(0), 94)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(elder_init)
    SWITCH(GSW(0))
        CASE_LESS(94)
        CALL(evt_npc_set_position, STRING("me"), 132, 0, -153)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(elder_talk)
    IF_INT_EQUAL(GSWF(2832), 0)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e14_13"), 0, STRING("me"))
        ELSE
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(sister_init)
    SWITCH(GSW(0))
        CASE_LESS(101)
        CALL(evt_npc_set_position, STRING("me"), -192, 0, -142)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(sister_regl)
    IF_INT_EQUAL(GSW(0), 91)
        RETURN
    END_IF
    IF_INT_EQUAL(GSW(0), 98)
        RETURN
    END_IF
    LOOP(0)
        CALL(evt_set_dir_to_target, STRING("me"), STRING("ガイドsp"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(sister_talk)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e14_14"), 0, STRING("me"))
    RETURN
EVT_END()

static EVT_BEGIN(guide_init)
    IF_INT_EQUAL(GSWF(2836), 1)
        CALL(evt_npc_set_position, STRING("me"), -145, 0, -60)
        CALL(evt_npc_set_ry, STRING("me"), 270)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(guide_talk)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_04_02"), 0, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(puni_3_init)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(118)
        IF_INT_EQUAL(GSWF(2884), 1)
            CALL(evt_npc_set_position, STRING("me"), 50, 0, 30)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(puni_3_talk)
    SWITCH(GSW(0))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_018"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg2_mri_re_018_1"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"プニ族長老"*/"\x83\x76\x83\x6A\x91\xB0\x92\xB7\x98\x56", 1536, 0, (s32)elder_init, 0, (s32)elder_talk, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ガイド妹"*/"\x83\x4B\x83\x43\x83\x68\x96\x85",
    1536, 0, (s32)sister_init, (s32)sister_regl, (s32)sister_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ガイド"*/"\x83\x4B\x83\x43\x83\x68", 1536,
    0, (s32)guide_init, 0, (s32)guide_talk, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"プニ族３"*/"\x83\x76\x83\x6A\x91\xB0\x82\x52", 1536, 0,
    (s32)puni_3_init, 0, (s32)puni_3_talk, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(bero_custom_00)
    SET_VALUE(GF(0), 1)
    IF_INT_EQUAL(GSW(0), 91)
        CALL(evt_bero_exec_onoff, 0, 4)
        BEGIN_INLINE_EVENT
            WAIT_MS(2000)
            CALL(evt_bero_exec_onoff, 0, 2)
            WAIT_MS(1000)
            SET_VALUE(GF(0), 0)
            CALL(evt_bero_exec_onoff, 1, 2)
            CALL(evt_bero_exec_onoff, 1, 4)
        END_INLINE_EVENT
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"dokan", 131072, 9, 100000, 0, 0, -1, (s32)bero_custom_00,
    6, 0, (s32)"mri_20", (s32)"dokan1", 65537, 0, 0, (s32)"w_bero",
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"mri_04", (s32)"e_bero", 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 puni_rand_position[] = {
    -4391055, -9502919, -6553886, -8192253, -9371797, -14942434, -11927743, -2556104,
    -10813642, -14221465, -5046432, -12845327, -15925460, -9437363, -3801321, -4128982,
    -11534576, -2818228, -15007991, -9568554, -7471256, -16974025, -13762776, -7143692,
    -9109743, -11403546, -6357154, -14155950, -2556144, -5046471, -10486012, -10748048,
    -11469019, -8519844, -16253181, -5636342, -3211546, -13828333, -15335715, -10748086,
    -4718772, -9175258, -6029494, -6226130, -14549267, -12845212, -17432839, -6947064,
    -5767312, -14745802, -5177571, -13566240, -5832971, -15925521, -9371911, -7995601,
    -11665575, -8323261, -15401139, -16187625, -15466654, -3080340, -7799078, -4325647,
    -3801283, -2818268, -7864550, -8388884, -3080450, -11665670, -16711831, -10092824,
    -3735718, -16711861, -8388744, -12648698, -7405743, -12583121, -13893890, -10354851,
    -4325627, -7078082, -13566147, -6946950, -10354919, -12648677, -6488293, -5243166,
    -12845232,
};

EVT_BEGIN(jail_init_00)
    SET_VALUE(LW(10), 14)
    SET_VALUE(LW(11), 0)
    LOOP(0)
        CALL(evt_mri_get16bitdata, PTR(puni_rand_position), LW(11), LW(0))
        ADD(LW(11), 1)
        CALL(evt_mri_get16bitdata, PTR(puni_rand_position), LW(11), LW(2))
        ADD(LW(11), 1)
        CALL(evt_puni_init_puni, LW(10), 14, LW(0), 0, LW(2), 0)
        CALL(evt_puni_flag_onoff, LW(10), 0, 8388608)
        CALL(evt_puni_pera_onoff, LW(10), 1)
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(red_jail_open)
    SET_VALUE(GSWF(2833), 1)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, STRING("S_hako_r_doa"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_DOOR_GRID_OPEN1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 85, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("S_hako_r_doa"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_hitobj_onoff, STRING("A_hako_r1"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_hako_r_01"), 1, 0)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(evt_opendoor00)
    CALL(evt_mapobj_rotate, 1, STRING("S_hako_r_doa"), 0, 85, 0)
    CALL(evt_hitobj_onoff, STRING("A_hako_r1"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("A_hako_r_01"), 1, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_unlock00)
    CALL_CHILD(PTR(red_jail_open))
    SPAWN_EVENT(PTR(elder_rescue))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_unlock00_01)
    SPAWN_EVENT(PTR(red_jail_open))
    RETURN
EVT_END()

__declspec(section ".data") s32 key_table00[] = {
    16, -1,
};

EVT_BEGIN(evt_check00)
    CALL(evt_pouch_check_item, 16, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(evt_win_item_select, 0, PTR(key_table00), LW(0), 0)
        IF_INT_EQUAL(LW(0), -1)
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(blue_jail_open)
    SET_VALUE(GSWF(2835), 1)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, STRING("S_hako_l_doa"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_DOOR_GRID_OPEN1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 85, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mapobj_rotate, 1, STRING("S_hako_l_doa"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_hitobj_onoff, STRING("A_hako_l_01"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("S_hako_l1"), 1, 0)
    CALL(evt_mario_key_onoff, 1)
    SPAWN_EVENT(PTR(guide_sister))
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(evt_opendoor01)
    CALL(evt_mapobj_rotate, 1, STRING("S_hako_l_doa"), 0, 85, 0)
    CALL(evt_hitobj_onoff, STRING("A_hako_l_01"), 1, 0)
    CALL(evt_hitobj_onoff, STRING("S_hako_l1"), 1, 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_unlock01)
    CALL(evt_pouch_remove_item, 17, LW(0))
    SPAWN_EVENT(PTR(blue_jail_open))
    RETURN
EVT_END()

__declspec(section ".data") s32 key_table01[] = {
    16, 17, -1,
};

EVT_BEGIN(evt_check01)
    CALL(evt_win_item_maketable, PTR(key_table01), LW(10))
    IF_INT_NOT_EQUAL(LW(10), 0)
        CALL(evt_win_item_select, 0, LW(10), LW(0), 0)
        SWITCH(LW(0))
            CASE_EQUAL(17)
            CASE_EQUAL(16)
            CALL(evt_mobj_exec_cancel, STRING("me"))
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_msg_toge, 1, 0, 0, 0)
            CALL(evt_msg_print, 0, STRING("stg2_mri_e14_15"), 0, 0)
            CALL(evt_puni_get_lsw_index, LSW(0), 0, LW(0), LW(1), LW(2), LW(3))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_puni_flag_onoff, 1, 0, 262144)
                CALL(evt_npc_flag_onoff, 1, STRING("ガイドsp"), 1536)
                CALL(evt_msg_print, 0, STRING("stg2_mri_e14_16"), 0, STRING("ガイドsp"))
                CALL(evt_puni_flag_onoff, 1, 1, 262144)
                CALL(evt_msg_print, 0, STRING("stg2_mri_e14_17"), 0, STRING("ガイド妹"))
            END_IF
            CALL(evt_mario_key_onoff, 1)
            CASE_DEFAULT
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_SWITCH
    END_IF
    CALL(evt_win_item_desttable, LW(10), 2)
EVT_END()

EVT_BEGIN(bluejail_alpha)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("S"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_l_saku"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_l_doa"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_l_01"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_saku"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_doa"), 2048)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_01"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("mario"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("party"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("プニ族長老"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイド妹"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイド"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("プニ族"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイドsp"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ガイド妹sp"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ちびトゲsp"), 2048)
    CALL(evt_map_blend_set_flag, 1, STRING("ライバルsp"), 2048)
    CALL(evt_map_set_blend, 0, 255, 255, 255, 255)
    IF_INT_EQUAL(GSWF(2832), 0)
        CALL(evt_map_blend_set_mobj_flag, 1, STRING("mobj_lock00"), 2048)
    END_IF
    IF_INT_EQUAL(GSWF(2834), 0)
        CALL(evt_map_blend_set_mobj_flag, 1, STRING("mobj_lock01"), 2048)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(bluejail_event)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_puni_puninum_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    DELETE_EVENT(GW(0))
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envoff, 512)
    CALL_CHILD(PTR(bluejail_alpha))
    CALL(evt_npc_set_position, STRING("ガイド妹"), -192, 0, -120)
    CALL(evt_npc_set_ry_lr, STRING("ガイド妹"), 1)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド妹"), 1073741856)
    CALL(evt_puni_set_position, 14, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("プニ族"), -114, 0, -120)
    CALL(evt_npc_set_ry_lr, STRING("プニ族"), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("プニ族"), 1073741856)
    CALL(evt_npc_flag_onoff, 1, STRING("プニ族"), 1536)
    CALL(evt_cam3d_evt_set, -160, 160, 540, -160, 60, 0, 0, 11)
    CALL(evt_seq_wait, 2)
    BEGIN_INLINE_EVENT
        WAIT_MS(1500)
        CALL(evt_sub_intpl_msec_init, 11, 255, 80, 1500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_map_set_blend, 0, 255, 255, 255, LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, -160, 90, 147, -160, 60, 0, 3000, 11)
    WAIT_MS(3000)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_00"), 0, STRING("プニ族"))
    CALL(evt_npc_get_position, STRING("ガイド妹"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNIKO_KINOKO1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_item_entry, STRING("item00"), 152, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 2)
    ADD(LW(0), 20)
    CALL(evt_item_move_3d_position, STRING("item00"), LW(0), LW(1), LW(2), 300, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_01"), 0, STRING("ガイド妹"))
    CALL(evt_cam3d_evt_set, -159, 197, 270, -159, 81, -32, 0, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_02"), 0, STRING("プニ族"))
    CALL(evt_npc_get_position, STRING("ガイド妹"), LW(0), LW(1), LW(2))
    CALL(evt_item_move_3d_position, STRING("item00"), LW(0), LW(1), LW(2), 300, 0)
    CALL(evt_item_set_position, STRING("item00"), 0, -1000, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_03"), 0, STRING("ガイド妹"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_04"), 0, STRING("プニ族"))
    WAIT_MS(1500)
    SET_VALUE(GSW(0), 99)
    CALL(evt_fade_set_mapchange_type, 0, 2, 500, 1, 500)
    CALL(evt_bero_mapchange, STRING("mri_08"), STRING("e_bero"))
    RETURN
EVT_END()




static EVT_BEGIN(mario_kirimomi_event)
    WAIT_MS(300)
    CALL(evt_mario_dispflag_onoff, 1, 256)
    CALL(evt_mario_get_dispdir, LW(8))
    SET_VALUE(LW(9), 1980)
    ADD(LW(9), LW(8))
    CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(9), 2000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_mario_set_dispdir, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_dispflag_onoff, 0, 256)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

EVT_BEGIN(party_kirimomi_event)
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    CALL(evt_party_dispflg_onoff, 0, 16, 1)
    CALL(evt_party_get_dispdir, 0, LW(8))
    SET_VALUE(LW(9), 1980)
    ADD(LW(9), LW(8))
    CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(9), 2000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_party_set_dispdir, 0, LW(0))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_dispflg_onoff, 0, 16, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

s32 JailAwayTable_New[] = {
    -83, -216, -153, -195, -205, -154, -241, -95,
    -220, -25, -190, 0, -160, 40, 10000,
};

void puniModeEventparent(PuniData* puni) {
    s32* tbl = JailAwayTable_New;
    s32 i;
    s32 bestIdx;
    f32 best;
    f32 d;
    Vec dir;
    Vec p;
    Vec pos;
    f32 mag;

    switch (puni->field_0x114) {
        case 0:
            best = 1000000.0f;
            bestIdx = -1;
            for (i = 0; i < 4; i++) {
                p.x = tbl[i * 2];
                p.y = 0.0f;
                p.z = tbl[i * 2 + 1];
                d = PSVECSquareDistance(&p, &puni->position);
                if (best > d) {
                    best = d;
                    bestIdx = i;
                }
            }
            puni->field_0x1E0 = bestIdx;
            puni->field_0x11E = 2;
            puni->field_0x114 = 1;
        case 1:
            p.x = tbl[puni->field_0x1E0 * 2];
            p.y = 0.0f;
            p.z = tbl[puni->field_0x1E0 * 2 + 1];
            if (PSVECSquareDistance(&p, &puni->position) > 100.0f) {
                PSVECSubtract(&p, &puni->position, &dir);
                PSVECNormalize(&dir, &dir);
                dir.y = 0.0f;
                PSVECScale(&dir, &dir, 1.5f);
                PSVECAdd(&puni->field_0x15C, &dir, &puni->field_0x15C);
            } else if (puni->field_0x1E0 == puni->field_0x1E4 + 5) {
                puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
                puni->field_0x114 = 2;
            } else if (tbl[puni->field_0x1E0 * 2 + 2] != 10000) {
                puni->field_0x1E0++;
            } else {
                puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
                puni->field_0x114 = 2;
            }
            break;
        case 2:
            puni->field_0x11E = 0;
            puni->field_0x114 = 3;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        case 10:
            p = (Vec){-160.0f, 0.0f, 40.0f};
            if (PSVECSquareDistance(&p, &puni->position) < 4900.0f) {
                PSVECSubtract(&puni->position, &p, &dir);
                PSVECNormalize(&dir, &dir);
                dir.y = 0.0f;
                PSVECScale(&dir, &dir, 0.7f);
                PSVECAdd(&puni->field_0x15C, &dir, &puni->field_0x15C);
                puni->field_0x174 = 2.1f;
                mag = PSVECMag(&puni->field_0x15C);
                pos = puni->position;
                pos.y += 1.0f;
                if (mag != 0.0f) {
                    PSVECNormalize(&puni->field_0x15C, &dir);
                } else {
                    dir = (Vec){0.0f, 0.0f, 0.0f};
                }
                puniMoveAtari(puni, pos, dir, 0, mag);
            } else {
                puni->field_0x114 = 11;
            }
            break;
        case 11:
            puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
            if (puni->position.x < -160.0f) {
                puni->field_0x180 = 90.0f;
            } else {
                puni->field_0x180 = 270.0f;
            }
            puni->field_0x114 = 12;
            break;
        case 12:
            break;
    }
}

USER_FUNC(puni_parent) {
    s32 offset = evtGetValue(event, event->args[0]) * sizeof(PuniData);
    PuniData* puni = (PuniData*)((u8*)puniGetPunidat() + offset);
    s16 side;

    if (puni->position.x > -180.0f) {
        side = 1;
        puni->field_0x1E4 = event->lwData[11] % 2;
        event->lwData[11]++;
    } else {
        side = 2;
        puni->field_0x1E4 = event->lwData[12] % 2;
        event->lwData[12]++;
    }
    puni->flags |= 0x100000;
    puni->field_0x118 = side;
    puni->field_0xC = 29;
    puni->field_0x114 = 0;
    puni->field_0x11E = 1000;
    puni->field_0x56C = puniModeEventparent;
    puni->field_0x570 = puniMoveDecel;
    return EVT_RETURN_DONE;
}

USER_FUNC(puni_away) {
    s32 offset = evtGetValue(event, event->args[0]) * sizeof(PuniData);
    PuniData* puni = (PuniData*)((u8*)puniGetPunidat() + offset);

    puni->field_0x114 = 10;
    return EVT_RETURN_DONE;
}

EVT_BEGIN(kinoko_small)
    CALL(evt_item_get_position, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(10), STRING("item00"))
    SET_FLOAT_VALUE(LW(11), FLOAT(0.69921875f))
    CALL(evt_item_set_scale, LW(10), LW(11))
    WAIT_MS(750)
    SET_FLOAT_VALUE(LW(11), FLOAT(0.34960938f))
    CALL(evt_item_set_scale, LW(10), LW(11))
    WAIT_MS(750)
    CALL(evt_item_set_position, STRING("item00"), 0, -1000, 0)
    RETURN
EVT_END()

EVT_BEGIN(guide_sister)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(LW(10), 14)
    SET_VALUE(LW(11), 0)
    SET_VALUE(LW(12), 0)
    LOOP(0)
        CALL(puni_parent, LW(10))
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_puni_set_mode, 4, 14)
    CALL(evt_puni_set_anim, 4, 0)
    CALL(evt_puni_flag_onoff, 4, 0, 1048576)
    CALL(evt_puni_set_mode, 3, 14)
    CALL(evt_puni_set_anim, 3, 0)
    CALL(evt_puni_flag_onoff, 3, 0, 1048576)
    SET_VALUE(LW(10), 5)
    LOOP(9)
        CALL(evt_puni_set_mode, LW(10), 14)
        CALL(evt_puni_set_anim, LW(10), 0)
        CALL(evt_puni_flag_onoff, LW(10), 0, 1048576)
        ADD(LW(10), 1)
    END_LOOP
    SPAWN_EVENT(PTR(mario_kirimomi_event))
    SPAWN_EVENT(PTR(party_kirimomi_event))
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_NOKO_SAIKAI1"))
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1073741856)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド妹"), 1073741856)
    WAIT_MS(2000)
    CALL(evt_npc_get_reglid, STRING("ガイド妹"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_set_ry, STRING("ガイド妹"), 270)
    SET_VALUE(LW(0), STRING("ガイド妹"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイド妹"), -245, -108, 0, FLOAT(180.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_npc_set_ry, STRING("ガイド妹"), 90)
    SET_VALUE(LW(0), STRING("ガイド妹"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイド妹"), -180, 40, 0, FLOAT(180.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_00"), 0, STRING("ガイド妹"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -230, -45, FLOAT(120.0f))
        WAIT_FRAMES(1)
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -250, -40, FLOAT(120.0f))
        WAIT_FRAMES(1)
        CALL(evt_party_set_dir, 0, 90, -1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ガイド"), 0, 0, 0, 0, 0, 0, 0, 60)
        WAIT_MS(1000)
        SET_VALUE(LW(0), STRING("ガイド"))
        SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
        CALL(evt_npc_move_position, STRING("ガイド"), -140, 40, 0, FLOAT(180.0f), 0)
        DELETE_EVENT(LW(9))
        CALL(evt_npc_set_ry, STRING("ガイド"), 270)
    END_INLINE_EVENT
    WAIT_MS(1000)
    SET_VALUE(LW(10), 14)
    LOOP(0)
        CALL(puni_away, LW(10))
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_cam3d_evt_set, -160, 90, 352, -160, 30, 7, 500, 11)
    WAIT_MS(1500)
    SET_VALUE(LW(10), STRING("ガイド"))
    SET_VALUE(LW(11), STRING("ガイド妹"))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, LW(10), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, LW(10), LW(0), LW(1), LW(2), 200, 18)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, LW(10), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, LW(10), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_01"), 0, LW(10))
    CALL(evt_npc_get_position, LW(11), LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, LW(11), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, LW(11), LW(0), LW(1), LW(2), 200, 18)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, LW(11), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, LW(11), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_02"), 0, LW(11))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_03"), 0, LW(10))
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_04"), 0, LW(11))
    CALL(evt_npc_set_ry, LW(11), 270)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_05"), 0, LW(11))
    CALL(evt_npc_set_ry, LW(11), 90)
    WAIT_MS(200)
    CALL(evt_npc_get_position, LW(11), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNIKO_KINOKO1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_item_entry, STRING("item00"), 152, LW(0), LW(1), LW(2), 16, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), 2)
    ADD(LW(0), 20)
    CALL(evt_item_move_3d_position, STRING("item00"), LW(0), LW(1), LW(2), 500, 0)
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_06"), 0, LW(11))
    CALL(evt_cam3d_evt_set, -150, 73, 278, -150, 25, 7, 500, 11)
    SET_VALUE(LW(0), LW(10))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, LW(10), -150, 40, 0, FLOAT(60.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_npc_set_autotalkpose, LW(10), STRING("T_1"), STRING("T_1"))
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT_GET_ID(LW(9))
        LOOP(0)
            CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_EAT1"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(30)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, LW(10), STRING("T_1"))
    WAIT_MS(2000)
    SPAWN_EVENT(PTR(kinoko_small))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_07"), 0, LW(10))
    WAIT_FRAMES(1)
    DELETE_EVENT(LW(9))
    CALL(evt_npc_set_anim, LW(10), STRING("S_1"))
    CALL(evt_npc_set_autotalkpose, LW(10), STRING("S_1"), STRING("T_1"))
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_08"), 0, LW(11))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_09"), 0, LW(10))
    CALL(evt_eff_fukidashi, 1, STRING(""), LW(11), 1, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_10"), 0, LW(11))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_11"), 0, LW(10))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(0), -20)
    CALL(evt_cam3d_evt_set, -175, 73, 278, -175, 25, 7, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, LW(10), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG2_PUNI_JUMP1"), LW(10), LW(11), LW(12), 0)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, LW(10), LW(0), LW(1), LW(2), 200, 18)
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_12"), 0, LW(11))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_13"), 0, LW(10))
    WAIT_MS(2000)
    CALL(evt_msg_togelr, 0)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e20_14"), 0, LW(11))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSWF(2836), 0)
    SET_VALUE(GSWF(2877), 1)
    SET_VALUE(GSW(651), 98)
    CALL(evt_npc_get_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ガイド"), 0, -1000, 0)
    CALL(evt_puni_init_puni, 1, 1, LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_get_position, STRING("ガイド妹"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ガイド妹"), 0, -1000, 0)
    CALL(evt_puni_init_puni, 2, 1, LW(0), LW(1), LW(2), 0)
    SET_VALUE(LW(10), 1)
    LOOP(0)
        CALL(evt_puni_set_mode, LW(10), 1)
        CALL(evt_puni_flag_onoff, LW(10), 1, 8388608)
        ADD(LW(10), 1)
        IF_INT_EQUAL(LW(10), 103)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_GET_PARTY1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_msg_toge, 1, 0, 0, 0)
    IF_INT_EQUAL(GSWF(2878), 0)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e20_16"), 0, 0)
        ELSE
        CALL(evt_msg_print, 0, STRING("stg2_mri_e20_16_1"), 0, 0)
    END_IF
    SET_VALUE(GSW(0), 101)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(elder_shaberi)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_06"), 0, LW(10))
    LOOP(0)
        CALL(evt_msg_repeat)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(toraware_elder)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_puni_wait_systemmode, 2)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_WHILE(GF(0))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 200, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL_CHILD(PTR(mri_guide_hagure_check))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_puni_set_lsw_index, LSW(0), 0, 0, 0, 0, 0)
        CALL(evt_puni_set_trap_index, 1, 0)
        CALL(evt_puni_init_puni, 1, 30, 0, -1000, 0, 0)
        CALL(evt_puni_flag_onoff, 1, 1, 65536)
        CALL(evt_puni_set_position, 1, 240, 0, 0)
        CALL(evt_puni_move_position, 1, 240, 40, FLOAT(120.0f))
        CALL(evt_puni_set_mode, 1, 1)
    END_IF
    CALL(evt_puni_flag_onoff, 1, 0, 262144)
    CALL(evt_puni_set_anim, 1, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイドsp"), 1073743392)
    CALL(evt_npc_set_ry, STRING("ガイドsp"), 270)
    SET_VALUE(LW(0), STRING("ガイドsp"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイドsp"), 195, 40, 0, FLOAT(120.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ガイドsp"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_01"), 0, STRING("ガイドsp"))
    CALL(evt_cam3d_evt_set, 135, 85, 204, 135, 50, 7, 500, 11)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), STRING("ガイドsp"))
        SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
        CALL(evt_npc_move_position, STRING("ガイドsp"), 145, -60, 0, FLOAT(120.0f), 0)
        DELETE_EVENT(LW(9))
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    SET_VALUE(LW(10), STRING("プニ族長老"))
    CALL(evt_npc_flag_onoff, 1, LW(10), 1073741856)
    CALL(evt_npc_set_ry, LW(10), 90)
    SET_VALUE(LW(0), LW(10))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, LW(10), 115, -100, 0, FLOAT(60.0f), 0)
    DELETE_EVENT(LW(9))
    WAIT_WHILE(GF(0))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_02"), 0, LW(10))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 175, -30, FLOAT(120.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_stop, 0)
        CALL(evt_party_move_pos2, 0, 210, -30, FLOAT(120.0f))
    END_INLINE_EVENT
    WAIT_MS(333)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_03"), 0, STRING("ガイドsp"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_04"), 0, LW(10))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_05"), 0, STRING("ガイドsp"))
    SPAWN_EVENT_GET_ID(PTR(elder_shaberi), LW(15))
    SET_VALUE(LW(10), STRING("ガイド妹"))
    CALL(evt_npc_set_ry, LW(10), 90)
    CALL(evt_npc_set_position, LW(10), -165, 0, -100)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_07"), 0, LW(10))
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ガイドsp"), 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, -155, 85, 240, -155, 50, 7, 3000, 11)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        DELETE_EVENT(LW(15))
        CALL(evt_msg_close, STRING("stg2_mri_e12_26_06"))
    END_INLINE_EVENT
    SET_VALUE(LW(0), STRING("ガイドsp"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイドsp"), -140, -40, 0, FLOAT(120.0f), 0)
    DELETE_EVENT(LW(9))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_08"), 0, STRING("ガイドsp"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -110, -30, FLOAT(120.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -75, -30, FLOAT(120.0f))
    END_INLINE_EVENT
    WAIT_MS(250)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_09"), 0, LW(10))
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_10"), 0, STRING("ガイドsp"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_11"), 0, LW(10))
    WAIT_MS(500)
    CALL(evt_npc_set_ry, STRING("ガイドsp"), 90)
    WAIT_MS(833)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e12_26_12"), 0, STRING("ガイドsp"))
    SET_VALUE(LW(0), STRING("ガイドsp"))
    SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
    CALL(evt_npc_move_position, STRING("ガイドsp"), -125, -10, 0, FLOAT(120.0f), 0)
    DELETE_EVENT(LW(9))
    CALL(evt_puni_flag_onoff, 1, 1, 262144)
    CALL(evt_npc_get_position, STRING("ガイドsp"), LW(0), LW(1), LW(2))
    CALL(evt_puni_set_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSW(0), 92)
    CALL(evt_npc_restart_regular_event, STRING("ガイド妹"))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(guide_sister_before)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_puni_wait_systemmode, 2)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_bero_exec_wait, 65536)
    WAIT_MS(500)
    CALL_CHILD(PTR(mri_guide_hagure_check))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_puni_set_position, 1, 240, 0, 0)
        CALL(evt_puni_move_position, 1, 240, 40, FLOAT(120.0f))
    END_IF
    CALL(evt_puni_get_position, 1, LW(0), LW(1), LW(2))
    CALL(evt_puni_set_position, 1, 0, -1000, 0)
    CALL(evt_puni_set_mode, 1, 30)
    CALL(evt_puni_flag_onoff, 1, 0, 8388608)
    SET_VALUE(GSWF(2836), 1)
    CALL(evt_npc_set_position, STRING("ガイド"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_ry, STRING("ガイド"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("ガイド"), 1073743392)
    CALL(evt_msg_print, 0, STRING("stg2_mri_e19_04_01"), 0, STRING("ガイド"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_change_interrupt, STRING("ガイド"), 6, 0)
        SET_VALUE(LW(0), STRING("ガイド"))
        SPAWN_EVENT_GET_ID(PTR(mri_puni_walk_se), LW(9))
        CALL(evt_npc_move_position, STRING("ガイド"), -145, -60, 0, FLOAT(120.0f), 0)
        DELETE_EVENT(LW(9))
        CALL(evt_npc_flag_onoff, 0, STRING("ガイド"), 1073741856)
        CALL(evt_npc_change_interrupt, STRING("ガイド"), 6, PTR(guide_talk))
    END_INLINE_EVENT
    SET_VALUE(GSW(0), 100)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 ueki_access_data[] = {
    1, (s32)"A_ueki01", (s32)"S_ueki01", 0, 1, (s32)"A_ueki03", (s32)"S_ueki03", 0,
    1, (s32)"A_ueki04", (s32)"S_ueki04", 0, 1, (s32)"A_ueki05", (s32)"S_ueki05", 0,
    4, 0, 0, 0,
};

EVT_BEGIN(mri_03_init_evt)
    CALL(evt_puni_mem_init)
    CALL(evt_puni_set_yuka, 3, 0, -310, -1000, -1000, 0, 0)
    CALL(evt_puni_set_hamari, 0, 0, 0, 2, -2, -1000, -1000)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 0)
    CALL_CHILD(PTR(mri_puni_init))
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    SPAWN_EVENT(PTR(puni_disp_info))
    SPAWN_EVENT(PTR(mri_countdown))
    SET_VALUE(LW(0), PTR(ueki_access_data))
    CALL_CHILD(PTR(evt_sub_kusa_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(109, 110)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI9"))
        CASE_EQUAL(98)
        CASE_GREATER_OR_EQUAL(101)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_STG2_PUNI2"))
        CALL(evt_snd_envoff, 512)
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG2_MRI1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG2_MRI4"))
    END_SWITCH
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_hako_r_saku"), 2)
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -150, 0, -200, STRING("S_yuka_oku"), 125, GSWF(5613))
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_map_playanim, STRING("mizu_01"), 1, 0)
    CALL(evt_map_playanim, STRING("mizu_02"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_01"), 1, 0)
    CALL(evt_map_playanim, STRING("awa_02"), 1, 0)
    CALL(evt_map_playanim, STRING("hikari_01\0\0"), 1, 0)
    SWITCH(GSW(0))
        CASE_BETWEEN(90, 100)
        SPAWN_EVENT(PTR(jail_init_00))
    END_SWITCH
    CALL(evt_mobj_lock, STRING("mobj_lock00"), 16, 65, 10, -70, 0, PTR(evt_check00), PTR(evt_unlock00), GSWF(2832))
    IF_INT_EQUAL(GSWF(2832), 1)
        IF_INT_EQUAL(GSWF(2833), 1)
            SPAWN_EVENT(PTR(evt_opendoor00))
            ELSE
            SPAWN_EVENT(PTR(evt_unlock00_01))
        END_IF
    END_IF
    CALL(evt_mobj_lock, STRING("mobj_lock01"), PTR(key_table01), -245, 10, -70, 0, PTR(evt_check01), PTR(evt_unlock01), GSWF(2834))
    IF_INT_EQUAL(GSWF(2834), 1)
        IF_INT_EQUAL(GSWF(2835), 1)
            SPAWN_EVENT(PTR(evt_opendoor01))
            ELSE
            SPAWN_EVENT(PTR(evt_unlock01))
        END_IF
    END_IF
    SPAWN_EVENT_GET_ID(PTR(jail_alpha), GW(0))
    IF_INT_EQUAL(GSW(0), 98)
        SPAWN_EVENT(PTR(bluejail_event))
    END_IF
    IF_INT_EQUAL(GSW(0), 91)
        SPAWN_EVENT(PTR(toraware_elder))
    END_IF
    IF_INT_EQUAL(GSW(0), 99)
        SPAWN_EVENT(PTR(guide_sister_before))
    END_IF
    RETURN
EVT_END()

