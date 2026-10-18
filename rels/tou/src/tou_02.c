#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "string.h"
#include "mario/mariost.h"
#include "dolphin/os.h"
#include "stdlib.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "party/party_cloud.h"
#include "driver/npcdrv.h"
#include "driver/hitdrv.h"
#include "driver/dispdrv.h"
#include "party.h"

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
static s32 fan_bss_pad;
FanWork* fan_wp;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static void pose_init(void);
static void pose_change(Fan* fan, const char* name, const char* anim);
static f32 randf(f32 min, f32 max);
u8 psndSFX_get_vol(s32 id);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
static inline f32 fan_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
static inline f32 fan_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
s32 check_hammer(Fan* fan);
void psndSFX_pos(s32 id, Vec* pos);
void psndSFX_vol(s32 id, u8 vol);
static void pose_main(void);
void fan_disp(CameraId camera, void* param);
f32 cloudGetBreathDist(void);

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cloud_ent);
USER_FUNC(evt_cloud_init);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_end_count);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_item_set_bound_rate);
USER_FUNC(evt_item_set_gravity);
USER_FUNC(evt_item_set_jump_power);
USER_FUNC(evt_item_set_move_dir_speed);
USER_FUNC(evt_item_status_on);
USER_FUNC(evt_key_get_buttontrg);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_balloon_bikkuri);
USER_FUNC(evt_mario_balloon_off);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_party);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_insert);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_scale);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_move_pos);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_party_yoshi_ride);
USER_FUNC(evt_pouch_all_party_recovery);
USER_FUNC(evt_pouch_get_yoshiname);
USER_FUNC(evt_pouch_mario_recovery);
USER_FUNC(evt_pouch_open_mail);
USER_FUNC(evt_pouch_receive_mail);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_sub_rumble_onoff);
USER_FUNC(evt_tou_get_ranking_27_text_1ED4);
s32 check_hammer(Fan* fan);
void ext_fan_dispent(void);
void ext_fan_main(void);
void fan_disp(CameraId camera, void* param);
void ext_fan_init(void);
static f32 randf(f32 min, f32 max);
static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_main(void);
static void pose_init(void);
extern s32 bero_case_entry[];
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 evt_bero_info_run[];
extern s32 evt_sub_mail_vibration[];

__declspec(section ".data") u64 fd_tou_02_negone_one_374;
__declspec(section ".data") s32 fd_tou_02_neg_one_382[1];
__declspec(section ".data") s32 fd_tou_02___local_PI_383[1];
__declspec(section ".data") s32 fd_tou_02___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_tou_02_one_negone_373;
__declspec(section ".data") s32 fd_tou_02___local_PIO2_384[1];
__declspec(section ".data") s32 fd_tou_02_one_381[1];
__declspec(section ".data") u64 fd_tou_02_negone_one_360;
__declspec(section ".data") s32 fd_tou_02_neg_one_365[1];
__declspec(section ".data") s32 fd_tou_02___local_PI_366[1];
__declspec(section ".data") s32 fd_tou_02___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_tou_02_one_negone_359;
__declspec(section ".data") s32 fd_tou_02___local_PIO2_367[1];
__declspec(section ".data") s32 fd_tou_02_one_364[1];
static s32 s_door_open[58];
static s32 s_door_close[58];
s32 n_1_door_open[22];
s32 n_1_door_close[22];
static s32 n_2_door_open[22];
static s32 n_2_door_close[22];
__declspec(section ".data") s32 n_3_door_open[12];
__declspec(section ".data") s32 n_3_door_close[12];
__declspec(section ".data") s32 n_4_door_open[12];
__declspec(section ".data") s32 n_4_door_close[12];
static s32 bero_data[90];
s32 evt_move_g[63];
s32 init_gard1[39];
s32 talk_gard1[70];
s32 init_gard2[39];
s32 talk_gard2[70];
static s32 init_madam[39];
static s32 talk_madam[67];
__declspec(section ".data") s32 init_repo[8];
s32 talk_repo[112];
__declspec(section ".data") s32 init_cam1[8];
s32 talk_cam1[112];
s32 init_cam2[19];
s32 talk_cam2[112];
s32 init_kino4[13];
s32 reg_kino4[31];
s32 talk_kino4[112];
__declspec(section ".data") s32 init_kino5[8];
s32 talk_kino5[236];
__declspec(section ".data") s32 init_kinopiko[8];
s32 talk_kinopiko[112];
__declspec(section ".data") s32 init_kinopio_f[8];
s32 talk_kinopio_f[112];
s32 init_chu[20];
s32 talk_chu[67];
static s32 init_champ[32];
s32 move_pos[26];
s32 move_champ[155];
s32 talk_champ[34];
s32 init_shikowa[32];
s32 talk_shikowa[13];
static s32 init_uranoko[32];
static s32 talk_uranoko[13];
s32 init_ironA[38];
s32 talk_ironA[13];
s32 init_ironB[38];
s32 talk_ironB[13];
s32 init_borodo[32];
s32 talk_borodo[13];
static s32 npcEnt[391];
s32 evt_tougi2[285];
s32 ext_fan_data[84];
s32 mario_momikucha_msg[111];
s32 evt_momikucha[105];
static s32 evt_key[173];
static __declspec(section ".data") s32 evt_poster_1[5];
static __declspec(section ".data") s32 evt_poster_2[5];
static __declspec(section ".data") s32 evt_poster_3[5];
static __declspec(section ".data") s32 evt_poster_4[5];
static __declspec(section ".data") s32 evt_poster_5[5];
static __declspec(section ".data") s32 evt_poster_6[5];
static __declspec(section ".data") s32 evt_poster_7[5];
static s32 evt_poster_8[46];
static __declspec(section ".data") s32 evt_poster_9[5];
static s32 evt_after_peach[188];
s32 tou_02_init_evt[576];

static void pose_init(void) {
    char name[32];
    char anim[32];
    FanData* d = (FanData*)ext_fan_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    fan_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            fan_wp->animNum++;
        }
        strcpy(fan_wp->anim[fan_wp->animNum].name, name);
        strcpy(fan_wp->anim[fan_wp->animNum].anim, anim);
        fan_wp->anim[fan_wp->animNum].start = start;
        fan_wp->anim[fan_wp->animNum].count = i - start + 1;
        fan_wp->anim[fan_wp->animNum].rate = d->rate;
        fan_wp->anim[fan_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    fan_wp->animNum++;
}

static void pose_main(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;
    FanAnim* a;
    f32 t;

    pose = extGetPosePtr();
    fan = fan_wp->fans;

    for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
        a = &fan_wp->anim[fan->animIdx];
        t = 60.0f * OSTicksToMilliseconds((u64)(gp->renderTime - fan->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            fan->time = gp->renderTime;
            t = 0.0f;
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}

static void pose_change(Fan* fan, const char* name, const char* anim) {
    FanAnim* a;
    s32 i;

    for (i = 0, a = fan_wp->anim; i < fan_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < fan_wp->animNum && fan->animIdx != i) {
        fan->animIdx = i;
        fan->time = gp->renderTime;
    }
}

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

__declspec(section ".data") u64 fd_tou_02_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_02_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_02___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_02___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_02_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_02___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_02_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_tou_02_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_tou_02_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_tou_02___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_tou_02___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_tou_02_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_tou_02___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_tou_02_one_364[] = {
    1065353216,
};

static EVT_BEGIN(s_door_open)
    IF_FLOAT_EQUAL(LW(0), FLOAT(0.0f))
        IF_INT_EQUAL(GSWF(2526), 0)
            SET_VALUE(GSWF(2526), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AUTO_DOOR1"), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        SET_VALUE(GSWF(2526), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_b"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_a"), LW(0), 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_close)
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        IF_INT_EQUAL(GSWF(2526), 0)
            SET_VALUE(GSWF(2526), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AUTO_DOOR1"), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT(0.0f))
        SET_VALUE(GSWF(2526), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_b"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_a"), LW(0), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(n_1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_a"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(n_1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_a"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_a"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_a"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_3_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_4"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_3_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_4"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_4_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_5"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n_4_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_5"), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)"s_bero", 65536, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"tou_01", (s32)"a_door_mon", 327685, (s32)s_door_close, (s32)s_door_open, (s32)"n_bero_1",
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"tou_03", (s32)"s_bero_1", 327685, (s32)n_1_door_close, (s32)n_1_door_open, (s32)"n_bero_2", 65542,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"tou_03", (s32)"s_bero_2", 327685, (s32)n_2_door_close, (s32)n_2_door_open, (s32)"n_bero_3", 65540, 20000,
    100000, 0, 0, -1, 0, -1, 0, (s32)"tou_04",
    (s32)"e_bero", 327685, (s32)n_3_door_close, (s32)n_3_door_open, (s32)"n_bero_4", 65540, 20000, 100000,
    0, 0, -1, 0, -1, 0, (s32)"tou_04", (s32)"w_bero",
    327685, (s32)n_4_door_close, (s32)n_4_door_open, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

EVT_BEGIN(evt_move_g)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    ADD(LW(2), 100)
    CALL(evt_mario_mov_pos, LW(0), LW(2), 500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ガードマン１"), -530, -185, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING("ガードマン１"), STRING("mario"))
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("ガードマン２"), 530, -185, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING("ガードマン２"), STRING("mario"))
    SET_VALUE(LW(0), 3)
    CALL_CHILD(PTR(bero_case_switch_on))
    SET_VALUE(LW(0), 4)
    CALL_CHILD(PTR(bero_case_switch_on))
    IF_INT_LESS(GSW(0), 129)
        SET_VALUE(GSW(0), 129)
        ELSE
        SET_VALUE(GSWF(2497), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(init_gard1)
    SWITCH(GSW(0))
        CASE_LESS(129)
        CALL(evt_npc_set_position, STRING("me"), -470, 0, -185)
        CASE_LESS(171)
        CALL(evt_npc_set_position, STRING("me"), -530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2497), 0)
            CALL(evt_npc_set_position, STRING("me"), -470, 0, -185)
            ELSE
            CALL(evt_npc_set_position, STRING("me"), -530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_gard1)
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_msg_print, 0, STRING("stg3_tou_24"), 0, 0)
        CASE_LESS(129)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37"), 0, 0)
        CALL_CHILD(PTR(evt_move_g))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_01"), 0, 0)
        CASE_LESS(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_02"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_re_002_1"), 0, 0)
            ELSE
            IF_INT_EQUAL(GSWF(2497), 0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_001"), 0, 0)
                CALL_CHILD(PTR(evt_move_g))
                ELSE
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_002"), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_gard2)
    SWITCH(GSW(0))
        CASE_LESS(129)
        CALL(evt_npc_set_position, STRING("me"), 470, 0, -185)
        CASE_LESS(171)
        CALL(evt_npc_set_position, STRING("me"), 530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2497), 0)
            CALL(evt_npc_set_position, STRING("me"), 470, 0, -185)
            ELSE
            CALL(evt_npc_set_position, STRING("me"), 530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_gard2)
    SWITCH(GSW(0))
        CASE_LESS(128)
        CALL(evt_msg_print, 0, STRING("stg3_tou_24"), 0, 0)
        CASE_LESS(129)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37"), 0, 0)
        CALL_CHILD(PTR(evt_move_g))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_01"), 0, 0)
        CASE_LESS(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_02"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_re_002_1"), 0, 0)
            ELSE
            IF_INT_EQUAL(GSWF(2497), 0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_001"), 0, 0)
                CALL_CHILD(PTR(evt_move_g))
                ELSE
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_002"), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_madam)
    SWITCH(GSW(0))
        CASE_LESS(172)
        CALL(evt_npc_set_position, STRING("me"), 525, 0, 0)
        CASE_EQUAL(172)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), 525, 0, 0)
            ELSE
            CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_madam)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_07"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_repo)
    CALL(evt_npc_set_position, STRING("me"), -100, 0, -25)
    RETURN
EVT_END()

EVT_BEGIN(talk_repo)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_07"), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_024"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_024_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_023"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_024_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_cam1)
    CALL(evt_npc_set_position, STRING("me"), -150, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(talk_cam1)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_07"), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_026"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_026_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_025"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_026_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_cam2)
    IF_INT_LESS(GSW(0), 128)
        CALL(evt_npc_set_position, STRING("me"), 80, 200, -125)
        ELSE
        CALL(evt_npc_set_position, STRING("me"), 30, 200, -60)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(talk_cam2)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_07"), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_028"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_028_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_027"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_028_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_kino4)
    CALL(evt_npc_set_position, STRING("me"), -350, 0, 75)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    RETURN
EVT_END()

EVT_BEGIN(reg_kino4)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("me"), -350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
        CALL(evt_npc_move_position, STRING("me"), 350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(talk_kino4)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_07"), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_030"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_030_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_029"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_030_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kino5)
    CALL(evt_npc_set_position, STRING("me"), -520, 0, 25)
    RETURN
EVT_END()

EVT_BEGIN(talk_kino5)
    CALL(evt_pouch_get_yoshiname, LW(10))
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_04_yos"), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_04"), 0, 0, LW(10))
            END_IF
            CASE_GREATER(0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05_yos"), 0, 0, LW(10), LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05"), 0, 0, LW(10))
            END_IF
            CASE_DEFAULT
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_06_yos"), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_06"), 0, 0, LW(10))
            END_IF
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_07_yos"), 0, 0, LW(10))
                ELSE
                CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_07"), 0, 0)
            END_IF
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_yos"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032"), 0, 0)
                END_IF
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1_yos"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1"), 0, 0)
                END_IF
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print_insert, 0, STRING("stg3_npc_re_031_yos"), 0, 0, LW(10))
                        ELSE
                        CALL(evt_msg_print, 0, STRING("stg3_npc_re_031"), 0, 0)
                    END_IF
                    ELSE
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1_yos"), 0, 0)
                        ELSE
                        CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1"), 0, 0)
                    END_IF
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kinopiko)
    CALL(evt_npc_set_position, STRING("me"), -490, 0, 25)
    RETURN
EVT_END()

EVT_BEGIN(talk_kinopiko)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_07"), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_034"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_034_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_033"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_034_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_kinopio_f)
    CALL(evt_npc_set_position, STRING("キノピオ女"), 100, 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(talk_kinopio_f)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(2500), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_07"), 0, 0)
            ELSE
            CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_036"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_036_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(2504), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_035"), 0, 0)
                    ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_036_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_chu)
    SWITCH(GSW(0))
        CASE_LESS(144)
        CALL(evt_npc_set_position, STRING("me"), 245, 0, 125)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_chu)
    SWITCH(GSW(0))
        CASE_LESS(131)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_01"), 0, 0)
        CASE_LESS(164)
        CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_07"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_champ)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), -15, 0, 25)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

s32 move_pos[] = {
    0, 0, -100, -70, -225, 50, -230, 135,
    -105, 110, 10, -10, 135, 135, 220, 40,
    138, -65, 35, -50, 0, 110, -80, -40,
    110, -40,
};

EVT_BEGIN(move_champ)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        SET_INT_READ_ADDR(PTR(move_pos))
        LOOP(13)
            READ_INT2(LW(0), LW(1))
            CALL(evt_sub_random, 5, LW(0))
            ADD(LW(0), 2)
            MULTIPLY(LW(0), 1000)
            WAIT_MS(LW(0))
            CALL(evt_npc_get_position, STRING("me"), LW(5), LW(6), LW(7))
            CALL(evt_sub_random, 100, LW(0))
            CALL(evt_sub_random, 100, LW(1))
            SUBTRACT(LW(0), 50)
            ADD(LW(5), LW(0))
            ADD(LW(6), 40)
            SUBTRACT(LW(7), LW(1))
            CALL(evt_msg_toge, 2, LW(5), LW(6), LW(7))
            CALL(evt_end_count, LW(0))
            IF_INT_LESS(LW(0), 10)
                RETURN
            END_IF
            BEGIN_INLINE_EVENT
                SWITCH(LW(10))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_182"), 0, 0)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_183"), 0, 0)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_184"), 0, 0)
                    CASE_EQUAL(3)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_185"), 0, 0)
                    CASE_EQUAL(4)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_186"), 0, 0)
                    CASE_EQUAL(5)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_187"), 0, 0)
                    CASE_EQUAL(6)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_188"), 0, 0)
                    CASE_EQUAL(7)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_189"), 0, 0)
                    CASE_EQUAL(8)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_186_01"), 0, 0)
                END_SWITCH
            END_INLINE_EVENT
            ADD(LW(10), 1)
            IF_INT_GREATER(LW(10), 8)
                SET_VALUE(LW(10), 0)
            END_IF
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(talk_champ)
    SWITCH(GSW(0))
        CASE_LESS(171)
        CALL(evt_end_count, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_190_01"), 0, STRING("me"))
            ELSE
            CALL(evt_msg_print, 0, STRING("stg3_tou_190"), 0, STRING("me"))
        END_IF
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_02"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_shikowa)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), -25, 0, 75)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_shikowa)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_01"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_uranoko)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), -75, 0, 50)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_uranoko)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_03"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_ironA)
    CALL(evt_npc_set_scale, STRING("me"), FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.0f))
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), -30, 0, -50)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_ironA)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_04"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_ironB)
    CALL(evt_npc_set_scale, STRING("me"), FLOAT(1.5f), FLOAT(1.5f), FLOAT(1.0f))
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), -60, 0, -25)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_ironB)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_05"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(init_borodo)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("me"), -100, 0, 100)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), 32768)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), 32768)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_borodo)
    SWITCH(GSW(0))
        CASE_EQUAL(171)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_06"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"ガードマン１"*/"\x83\x4B\x81\x5B\x83\x68\x83\x7D\x83\x93\x82\x50", 1074267648, 0, (s32)init_gard1, 0, (s32)talk_gard1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ガードマン２"*/"\x83\x4B\x81\x5B\x83\x68\x83\x7D\x83\x93\x82\x51",
    1074267648, 0, (s32)init_gard2, 0, (s32)talk_gard2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"マダム"*/"\x83\x7D\x83\x5F\x83\x80", 1074267648,
    0, (s32)init_madam, 0, (s32)talk_madam, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"レポーター"*/"\x83\x8C\x83\x7C\x81\x5B\x83\x5E\x81\x5B", 1074267648, 0,
    (s32)init_repo, 0, (s32)talk_repo, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"カメラマン１"*/"\x83\x4A\x83\x81\x83\x89\x83\x7D\x83\x93\x82\x50", 1074267648, 0, (s32)init_cam1,
    0, (s32)talk_cam1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"カメラマン２"*/"\x83\x4A\x83\x81\x83\x89\x83\x7D\x83\x93\x82\x51", 1074267648, 0, (s32)init_cam2, 0,
    (s32)talk_cam2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"キノピオ４"*/"\x83\x4C\x83\x6D\x83\x73\x83\x49\x82\x53", 1074267648, 0, (s32)init_kino4, (s32)reg_kino4, (s32)talk_kino4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"キノピオ５"*/"\x83\x4C\x83\x6D\x83\x73\x83\x49\x82\x54", 1074267648, 0, (s32)init_kino5, 0, (s32)talk_kino5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"キノピコ"*/"\x83\x4C\x83\x6D\x83\x73\x83\x52", 1074267648, 0, (s32)init_kinopiko, 0, (s32)talk_kinopiko, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"バッジ屋"*/"\x83\x6F\x83\x62\x83\x57\x89\xAE",
    1074267648, 0, (s32)init_chu, 0, (s32)talk_chu, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"チャンピョン"*/"\x83\x60\x83\x83\x83\x93\x83\x73\x83\x87\x83\x93", 1074267648,
    0, (s32)init_champ, 0, (s32)talk_champ, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"キノシコワ"*/"\x83\x4C\x83\x6D\x83\x56\x83\x52\x83\x8F", 1074267648, 0,
    (s32)init_shikowa, 0, (s32)talk_shikowa, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ウラノコ"*/"\x83\x45\x83\x89\x83\x6D\x83\x52", 1074267648, 0, (s32)init_uranoko,
    0, (s32)talk_uranoko, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"アイアンＡ"*/"\x83\x41\x83\x43\x83\x41\x83\x93\x82\x60", 1074267648, 0, (s32)init_ironA, 0,
    (s32)talk_ironA, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"アイアンＢ"*/"\x83\x41\x83\x43\x83\x41\x83\x93\x82\x61", 1074267648, 0, (s32)init_ironB, 0, (s32)talk_ironB,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"ボロドー"*/"\x83\x7B\x83\x8D\x83\x68\x81\x5B", 1074267648, 0, (s32)init_borodo, 0, (s32)talk_borodo, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_tougi2)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SET_VALUE(LF(0), 0)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("n_bero_2"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mario_set_pos, -25, 200, -220)
        CALL(evt_party_set_pos, 0, 25, 200, -220)
        ELSE
        CALL(evt_mario_set_pos, -25, 0, -220)
        CALL(evt_party_set_pos, 0, 25, 0, -220)
    END_IF
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, -1)
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_cam3d_evt_set, 0, 290, 190, 0, 238, -158, 0, 11)
        ELSE
        CALL(evt_cam3d_evt_set, 0, 90, 190, 0, 38, -158, 0, 11)
    END_IF
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(PTR(bero_open_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(PTR(n_2_door_open))
            ELSE
            CALL_CHILD(PTR(n_1_door_open))
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_mario_mov_pos, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_party_move_pos, 0, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    WAIT_MS(700)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(PTR(bero_close_door_play_se))
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(PTR(n_2_door_close))
            ELSE
            CALL_CHILD(PTR(n_1_door_close))
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_msg_print_party, STRING("stg3_tou_33"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_33_yn"))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_34_kur"))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_34_nok"))
            CASE_EQUAL(5)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_34_win"))
        END_SWITCH
        ELSE
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_35_kur"))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_35_nok"))
            CASE_EQUAL(5)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_35_win"))
        END_SWITCH
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_36"))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSWF(2374), 0)
    SET_VALUE(GSW(0), 128)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

s32 ext_fan_data[] = {
    (s32)"c_kinopio", (s32)"KNP_W_1", 1073741824, (s32)"c_kinopio", (s32)"KNP_W_1", 1086324736, (s32)"c_kinopio", (s32)"KNP_W_1",
    1092616192, (s32)"c_kinopio", (s32)"KNP_W_1", 1096810496, (s32)"c_kinopio", (s32)"KNP_W_1", 1099956224, (s32)"c_kinopio",
    (s32)"KNP_W_1", 1102053376, (s32)"c_kinopio", (s32)"KNP_W_1", 1104150528, (s32)"c_kinopio", (s32)"KNP_W_1", 1106247680,
    (s32)"c_kinopio", (s32)"KNP_W_1", 1107820544, (s32)"c_kinopiko", (s32)"KNF_W_1", 1073741824, (s32)"c_kinopiko", (s32)"KNF_W_1",
    1086324736, (s32)"c_kinopiko", (s32)"KNF_W_1", 1092616192, (s32)"c_kinopiko", (s32)"KNF_W_1", 1096810496, (s32)"c_kinopiko",
    (s32)"KNF_W_1", 1099956224, (s32)"c_kinopiko", (s32)"KNF_W_1", 1102053376, (s32)"c_kinopiko", (s32)"KNF_W_1", 1104150528,
    (s32)"c_kinopiko", (s32)"KNF_W_1", 1106247680, (s32)"c_kinopiko", (s32)"KNF_W_1", 1107820544, (s32)"c_kinopiko", (s32)"KNF_W_1",
    1108869120, (s32)"c_jugemu", (s32)"JGM_W_1", 0, (s32)"c_jugemu", (s32)"JGM_W_1", 1082130432, (s32)"c_jugemu",
    (s32)"JGM_W_1", 1090519040, (s32)"c_jugemu", (s32)"JGM_W_1", 1094713344, (s32)"c_jugemu", (s32)"JGM_W_1", 1098907648,
    (s32)"c_jugemu", (s32)"JGM_W_1", 1101004800, (s32)"c_jugemu", (s32)"JGM_W_1", 1103101952, (s32)"c_jugemu", (s32)"JGM_W_1",
    1105199104, 0, 0, 0,
};

void ext_fan_init(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;

    fan_wp = _mapAlloc(sizeof(FanWork));
    memset(fan_wp, 0, sizeof(FanWork));
    fan_wp->num = extGetPoseNum();
    fan_wp->fans = _mapAlloc(fan_wp->num * sizeof(Fan));
    memset(fan_wp->fans, 0, fan_wp->num * sizeof(Fan));
    pose_init();
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = 0.0f;
        pose->mtx[1][3] = 0.0f;
        pose->mtx[2][3] = 0.0f;
        pose->rot = randf(0.0f, 360.0f);
        switch (irand(1000) % 3) {
            case 0:
                pose_change(fan, "c_kinopio", "KNP_W_1");
                break;
            case 1:
                pose_change(fan, "c_kinopiko", "KNF_W_1");
                break;
            case 2:
            default:
                pose_change(fan, "c_jugemu", "JGM_W_1");
                break;
        }
        fan->state = 0;
        {
            Vec pos = {0.0f, 0.0f, 0.0f};

            pos.x = randf(-100.0f, 100.0f);
            pos.z = randf(-100.0f, 100.0f);
            fan->pos = pos;
            fan->vel = (Vec){0.0f, 0.0f, 0.0f};
        }
    }
    fan_wp->sfxId = psndSFXOn_3D("SFX_STG3_AUDIENCE_FAN1\0", &(Vec){0.0f, 0.0f, 0.0f});
    fan_wp->vol = psndSFX_get_vol(fan_wp->sfxId);
}

void fan_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

static __declspec(section ".rodata") Vec fan_zero = {0.0f, 0.0f, 0.0f};
#pragma opt_propagation off
#pragma opt_lifetimes off
void ext_fan_main(void) {
    MarioWork* mario = marioGetPtr();
    ExtPose* pose;
    Fan* fan;
    Fan* other;
    s32 i;
    s32 j;
    s32 found;
    Vec target = {0.0f, 0.0f, 0.0f};
    Vec dir;
    f32 angle;
    f32 dist;
    f32 dy;
    f32 spd;
    f32 x;
    f32 z;
    f32 breath;
    HitCheckQuery query;
    const char* sfx;

    if (mario->currMotionId == 0x12) {
        fan_wp->hammerTimer++;
    } else {
        fan_wp->hammerTimer = 0;
    }

    // the first free fan follows Mario; in the second variant a second one follows Champion
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    if (evtGetValue(NULL, GF(10))) {
        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                fan->pos = mario->position;
                target = fan->pos;
                pose->flags &= ~1;
                fan->flags |= 1;
                break;
            }
        }
    } else {
        found = 0;
        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state != 0) {
                continue;
            }
            if (!found) {
                found = 1;
                fan->pos = mario->position;
                pose->flags &= ~1;
                fan->flags |= 1;
            } else {
                fan->pos = npcNameToPtr("\203`\203\203\203\223\203s\203\207\203\223")->position;
                target = fan->pos;
                pose->flags &= ~1;
                fan->flags |= 1;
                break;
            }
        }
    }

    // steer every idle fan towards the target
    for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
        if (fan->state != 0) {
            continue;
        }
        PSVECSubtract(&target, &fan->pos, &dir);
        if (PSVECMag(&dir)) {
            PSVECNormalize(&dir, &dir);
            dir.y = 0.0f;
            PSVECScale(&dir, &dir, 0.1f);
            PSVECAdd(&fan->vel, &dir, &fan->vel);
        }
    }

    // push idle fans apart
    for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
        if (fan->state != 0) {
            continue;
        }
        for (j = 0, other = fan_wp->fans; j < fan_wp->num; j++, other++) {
            if (other->state == 0 && i != j && PSVECSquareDistance(&fan->pos, &other->pos) < 900.0f) {
                PSVECSubtract(&fan->pos, &other->pos, &dir);
                dir.y = 0.0f;
                PSVECNormalize(&dir, &dir);
                PSVECScale(&dir, &dir, 5.0f);
                PSVECAdd(&fan->vel, &dir, &fan->vel);
                PSVECSubtract(&other->vel, &dir, &other->vel);
            }
        }
    }

    // hammer and gust reactions
    sfx = "SFX_STG3_AUDIENCE_FAN_FLY1";
    for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
        if (fan->state != 0) {
            continue;
        }
        switch (check_hammer(fan)) {
            case 1:
                fan->state = 10;
                angle = 6.2831855f * randf(135.0f, 225.0f) / 360.0f;
                dist = randf(400.0f, 500.0f);
                x = fan->pos.x + dist * fan_sin(angle);
                z = fan->pos.z - dist * fan_cos(angle);
                {
                    Vec tgt = {0.0f, 0.0f, 0.0f};

                    tgt.x = x;
                    tgt.y = -100.0f;
                    tgt.z = z;
                    fan->target = tgt;
                }
                fan->param.y = randf(4.0f, 6.0f);
                fan->param.z = randf(0.1f, 0.2f);
                dy = fan->target.y - fan->pos.y;
                dist = distABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                fan->timer = dist / fan->param.y;
                fan->param.x = dy / fan->timer + fan->param.z * fan->timer / 2.0f;
                psndSFXOn_3D(sfx, &fan->pos);
                break;
            case 2:
                angle = angleABf(mario->position.x, mario->position.z, fan->pos.x, fan->pos.z);
                breath = cloudGetBreathDir();
                fan->state = 20;
                fan->target = fan_zero;
                angle = (angle + breath) / 2.0f;
                spd = randf(0.1f, 0.2f);
                angle = 6.2831855f * angle / 360.0f;
                fan->param.x = spd * fan_sin(angle);
                fan->param.y = randf(0.03f, 0.06f);
                fan->param.z = spd * -fan_cos(angle);
                fan->timer = 120;
                psndSFXOn_3D(sfx, &fan->pos);
                break;
        }
    }

    // move every fan and count the ones still in the crowd
    fan_wp->count = fan_wp->num;
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        switch (fan->state) {
            case 0:
                PSVECNormalize(&fan->vel, &fan->vel);
                dist = PSVECMag(&fan->vel);
                query.targetPos = fan->pos;
                query.targetPos.y += 4.0f;
                query.targetDir = fan->vel;
                query.targetDir.y = 0.0f;
                query.targetDistance = 25.0f + dist;
                if (hitCheckVecFilter(&query, NULL)) {
                    C_VECReflect(&fan->vel, &query.hitNormal, &fan->vel);
                } else {
                    fan->pos.x += fan->vel.x;
                    fan->pos.z += fan->vel.z;
                    fan->vel.x *= 0.6f;
                    fan->vel.z *= 0.6f;
                }
                if (fan->pos.x < -350.0f) {
                    fan->pos.x = -350.0f;
                }
                if (fan->pos.x > 350.0f) {
                    fan->pos.x = 350.0f;
                }
                if (fan->pos.z > 195.0f + i / 100.0f) {
                    fan->pos.z = 195.0f + i / 100.0f;
                }
                break;
            case 10:
                fan->pos.y += fan->param.x;
                fan->param.x -= fan->param.z;
                angle = angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                angle = 6.2831855f * angle / 360.0f;
                fan->pos.x += fan->param.y * fan_sin(angle);
                fan->pos.z += fan->param.y * -fan_cos(angle);
                if (--fan->timer < 0) {
                    fan->state = 100;
                }
                break;
            case 20:
                if (--fan->timer > 0) {
                    fan->target.x += fan->param.x;
                    fan->target.y += fan->param.y;
                    fan->target.z += fan->param.z;
                    fan->pos.x += fan->target.x;
                    fan->pos.y += fan->target.y;
                    fan->pos.z += fan->target.z;
                } else {
                    fan->state = 100;
                }
                break;
            case 100:
                pose->flags &= ~3;
                fan->state++;
                break;
            case 101:
                break;
        }
        if (fan->flags & 1) {
            fan_wp->count--;
        } else if (fan->state != 0) {
            fan_wp->count--;
        }
        pose->mtx[0][3] = fan->pos.x;
        pose->mtx[1][3] = fan->pos.y;
        pose->mtx[2][3] = fan->pos.z;
        pose->rot = angleABf(target.x, target.z, fan->pos.x, fan->pos.z);
    }
    psndSFX_pos(fan_wp->sfxId, &target);
    psndSFX_vol(fan_wp->sfxId, fan_wp->vol * fan_wp->count / fan_wp->num);
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

EVT_BEGIN(mario_momikucha_msg)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        CALL(evt_sub_random, 5, LW(0))
        ADD(LW(0), 2)
        MULTIPLY(LW(0), 1000)
        WAIT_MS(LW(0))
        CALL(evt_sub_random, 200, LW(0))
        CALL(evt_sub_random, 200, LW(1))
        SUBTRACT(LW(0), 50)
        SUBTRACT(LW(1), 50)
        CALL(evt_msg_toge, 2, LW(0), 30, LW(1))
        CALL(evt_end_count, LW(0))
        IF_INT_LESS(LW(0), 10)
            RETURN
        END_IF
        BEGIN_INLINE_EVENT
            SWITCH(LW(10))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_236"), 0, 0)
                CASE_EQUAL(1)
                CALL(evt_msg_print, 0, STRING("stg3_tou_237"), 0, 0)
                CASE_EQUAL(2)
                CALL(evt_msg_print, 0, STRING("stg3_tou_238"), 0, 0)
                CASE_EQUAL(3)
                CALL(evt_msg_print, 0, STRING("stg3_tou_239"), 0, 0)
                CASE_EQUAL(4)
                CALL(evt_msg_print, 0, STRING("stg3_tou_240"), 0, 0)
                CASE_EQUAL(5)
                CALL(evt_msg_print, 0, STRING("stg3_tou_240_01"), 0, 0)
            END_SWITCH
        END_INLINE_EVENT
        ADD(LW(10), 1)
        IF_INT_GREATER(LW(10), 5)
            SET_VALUE(LW(10), 0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_momikucha)
    SET_VALUE(LF(0), 0)
    SET_VALUE(GF(10), 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 133)
        IF_INT_EQUAL(GSWF(2402), 0)
            SET_VALUE(GSWF(2402), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 0)
        END_IF
    END_IF
    CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        IF_INT_EQUAL(GSWF(2403), 0)
            SET_VALUE(GSWF(2403), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        RETURN
    END_IF
    CALL(evt_npc_entry, STRING("fan"), STRING("c_kinopio"))
    CALL(evt_npc_entry, STRING("fan2"), STRING("c_kinopiko"))
    CALL(evt_npc_entry, STRING("fan3"), STRING("c_jugemu"))
    CALL(evt_npc_set_position, STRING("fan"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("fan2"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("fan3"), 0, -1000, 0)
    CALL(evt_ext_entry, 200, PTR(ext_fan_data), PTR(ext_fan_init), PTR(ext_fan_main), PTR(ext_fan_dispent))
    IF_INT_EQUAL(GF(10), 0)
        CALL(evt_npc_set_position, STRING("チャンピョン"), 0, 0, 0)
        CALL(evt_npc_change_interrupt, STRING("チャンピョン"), 1, PTR(move_champ))
        ELSE
        SPAWN_EVENT(PTR(mario_momikucha_msg))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_key)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_yoshi_ride, 0, 0)
    SET_VALUE(GSW(0), 154)
    CALL(evt_item_get_item_end_wait, STRING("key"))
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg3_tou_307_08"))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, 513)
    CALL(evt_snd_bgmon, 288, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_307_09"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_pouch_receive_mail, 15)
    CALL(evt_pouch_open_mail, 15)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

void ext_fan_dispent(void) {
    pose_main();
    dispEntry(CAMERA_3D, 0.0f, 1, fan_disp, NULL);
}

#pragma opt_propagation off
#pragma opt_lifetimes off
s32 check_hammer(Fan* fan) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    f32 rot;
    f32 x;
    f32 z;
    f32 angle;
    f32 dist;
    Vec pos;

    if (mario->position.y > 0.0f) {
        return 0;
    }
    if (fan->flags & 1) {
        return 0;
    }
    if (mario->currMotionId == 0x12 && fan_wp->hammerTimer > 10) {
        rot = 6.2831855f * reviseAngle(mario->displayDirection - 90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;

        x = mario->position.x + 35.0f * fan_sin(rot);
        z = mario->position.z - 35.0f * fan_cos(rot);
        if (distABf(fan->pos.x, fan->pos.z, x, z) < 35.0f) {
            return 1;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14 && PSVECDistance(&mario->position, &fan->pos) < 65.0f) {
        return 1;
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == 5 && (party->flags & 0x100)) {
        angle = 6.2831855f * cloudGetBreathDir() / 360.0f;
        dist = cloudGetBreathDist();
        pos.x = party->position.x + dist * fan_sin(angle);
        pos.y = party->position.y;
        pos.z = party->position.z - dist * fan_cos(angle);
        if (angle >= 0.0f && PSVECDistance(&pos, &fan->pos) < 30.0f) {
            return 2;
        }
    }
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

USER_FUNC(evt_end_count) {
    evtSetValue(event, event->args[0], fan_wp->count);
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") EVT_BEGIN(evt_poster_1)
    SET_VALUE(GSWF(2456), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_2)
    SET_VALUE(GSWF(2457), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_3)
    SET_VALUE(GSWF(2458), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_4)
    SET_VALUE(GSWF(2459), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_5)
    SET_VALUE(GSWF(2460), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_6)
    SET_VALUE(GSWF(2461), 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_7)
    SET_VALUE(GSWF(2462), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_poster_8)
    SET_VALUE(GSWF(2463), 1)
    IF_INT_EQUAL(GSW(0), 153)
        CALL(evt_mapobj_get_position, STRING("p_m_8"), LW(0), LW(1), LW(2))
        CALL(evt_item_entry, STRING("key"), 19, LW(0), LW(1), LW(2), 4, -1, PTR(evt_key))
        CALL(evt_item_set_move_dir_speed, STRING("key"), FLOAT(180.0f), FLOAT(90.0f))
        CALL(evt_item_set_gravity, STRING("key"), FLOAT(1.0f))
        CALL(evt_item_set_bound_rate, STRING("key"), FLOAT(0.5996094f))
        CALL(evt_item_set_jump_power, STRING("key"), FLOAT(500.0f))
        CALL(evt_item_status_on, STRING("key"), 16)
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_poster_9)
    SET_VALUE(GSWF(2464), 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_after_peach)
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 0, 11)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_pos, 25, 0, 75)
    CALL(evt_party_set_pos, 0, 60, 0, 100)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("door_1_a"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("door_1_b"), 1)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_01"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_02"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -40, 100, 395, -40, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_03"), 0, STRING("チャンピョン"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_04"), 0, STRING("ウラノコ"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_05"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 500, 11)
    CALL(evt_party_run, 0)
    CALL(evt_mario_mov_pos2, 0, 190, FLOAT(80.0f))
    CALL(evt_bero_mapchange, STRING("tou_01"), STRING("a_door_mon"))
    RETURN
EVT_END()

EVT_BEGIN(tou_02_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(127, 137)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU2"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU2"))
        CALL(evt_snd_bgmoff, 26624)
        CASE_GREATER_OR_EQUAL(165)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU2"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU2"))
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG3_TOU1"))
        CALL(evt_snd_bgmon, 160, 0)
        CALL(evt_snd_envon, 272, STRING("ENV_STG3_TOU2"))
    END_SWITCH
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    IF_INT_EQUAL(GSWF(2374), 1)
        CALL_CHILD(PTR(bero_case_entry))
        SPAWN_EVENT(PTR(evt_tougi2))
        ELSE
        CALL_CHILD(PTR(evt_bero_info_run))
    END_IF
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(PTR(init_kinopio_f))
    CALL(evt_npc_change_interrupt, STRING("キノピオ女"), 6, PTR(talk_kinopio_f))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -260, 0, -120, STRING("sita"), 125, GSWF(5623))
    IF_INT_LESS(GSW(0), 129)
        SET_VALUE(LW(0), 3)
        CALL_CHILD(PTR(bero_case_switch_off))
        SET_VALUE(LW(0), 4)
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 172)
        IF_INT_EQUAL(GSWF(2497), 0)
            SET_VALUE(LW(0), 3)
            CALL_CHILD(PTR(bero_case_switch_off))
            SET_VALUE(LW(0), 4)
            CALL_CHILD(PTR(bero_case_switch_off))
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 171)
        IF_INT_EQUAL(GSWF(2496), 0)
            CALL(evt_npc_set_position, STRING("キノピオ女"), 0, -1000, 0)
            CALL(evt_npc_set_position, STRING("キノピオ４"), 0, -1000, 0)
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(0), 171)
        CALL(evt_mario_get_party, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
            CALL(evt_pouch_mario_recovery)
            CALL(evt_pouch_all_party_recovery)
        END_IF
        CALL(evt_pouch_remove_item, 65, LW(0))
        SPAWN_EVENT(PTR(evt_after_peach))
        SET_VALUE(GSWF(2402), 1)
        SET_VALUE(GSWF(2403), 1)
    END_IF
    CALL(evt_map_playanim, STRING("anm_paneru"), 1, 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING("anm_paneru"), LW(0), LW(1))
                IF_INT_LESS(LW(1), 5333)
                    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN2"), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(10)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN1"), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING("anm_paneru"), LW(0), LW(1))
                IF_INT_LESS(LW(1), 2000)
                    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN2"), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(5)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN1"), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING("anm_paneru"), LW(0), LW(1))
                IF_INT_GREATER(LW(1), 6333)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
    END_INLINE_EVENT
    CALL_CHILD(PTR(evt_momikucha))
    CALL(evt_tou_get_ranking_27_text_1ED4, LW(0))
    SWITCH(LW(0))
        CASE_LESS(2)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("p_p_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("p_p_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("p_p_3"), 1)
        CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 1)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(2457), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_2"), STRING("a_p_m_2"), PTR(evt_poster_2))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_2"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_2"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2458), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_3"), STRING("a_p_m_3"), PTR(evt_poster_3))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_3"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_3"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2459), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_4"), STRING("a_p_m_4"), PTR(evt_poster_4))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_4"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_4"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2460), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_5"), STRING("a_p_m_5"), PTR(evt_poster_5))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_5"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_5"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2461), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_6"), STRING("a_p_m_6"), PTR(evt_poster_6))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_6"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_6"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2462), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_7"), STRING("a_p_m_7"), PTR(evt_poster_7))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_7"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_7"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2463), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_8"), STRING("a_p_m_8"), PTR(evt_poster_8))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_8"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_8"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(2464), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_9"), STRING("a_p_m_9"), PTR(evt_poster_9))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_9"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_9"), 1, 0)
        END_IF
        CASE_LESS(11)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("p_p_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("p_p_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("p_p_3"), 1)
        CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 1)
        CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(2456), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_1"), STRING("a_p_m_1"), PTR(evt_poster_1))
            ELSE
            CALL(evt_mapobj_flag_onoff, 0, 1, STRING("p_m_1"), 1)
            CALL(evt_hitobj_onoff, STRING("a_p_m_1"), 1, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("p_p_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("p_p_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("p_p_3"), 1)
        CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
    END_SWITCH
    IF_INT_EQUAL(GSWF(2463), 1)
        IF_INT_EQUAL(GSW(0), 153)
            CALL(evt_item_entry, STRING("key"), 19, -110, 200, -180, 16, -1, PTR(evt_key))
        END_IF
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_kaidan_7"), 2)
    RETURN
EVT_END()

