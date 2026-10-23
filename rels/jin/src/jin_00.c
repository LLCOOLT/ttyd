#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "mario/mario.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "memory.h"
#include "mario/mariost.h"
#include "party.h"
#include "evt/evt_bero.h"
#include "pmario_sound.h"
#include "driver/dispdrv.h"
#include "dolphin/gx.h"
#include "driver/camdrv.h"
#include "driver/extdrv.h"
#include "eff/eff_teresa.h"

int rand(void);
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Teresa { Vec vel; f32 angle; Vec ofs; f32 field_0x1C; f32 field_0x20; Vec from; Vec to; s32 wait; u8 alpha; u8 seq; } Teresa;
static Teresa* pTeresa;
Vec g_vecRotCenter;
s32 g_bMove;
s32 g_nMarioMoveCnt;
s32 g_nNumHuttobasu[1];
s32 g_nNumHarituku[1];
static s32 g_nNumEndProc[1];
f32 g_fSpeed;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static f32 randf(f32 min, f32 max);
double sin(double x);
static inline f32 sinf(f32 x) { return sin(x); }
f32 marioGetAngleKaitenHammer(void);
static void computePos(Teresa* ter, Vec* out);
s32 computeAlpha(Teresa* ter, MarioWork* mp, f32 angle);
void computeMtx(ExtPose* pose, f32 angle);
f32 computeAngle(ExtPose* pose, MarioWork* mp);
static void senteresa_ext_disp(CameraId camera, void* param);
void extLoadVertex(void);
void extLoadTexture(void);
void extPoseDraw(s32 i);
void extLoadTextureExit(void);
void senteresa_loadTev(void);
void senteresa_loadRenderMode(void);
void extLoadShadowMtx(Mtx mtx);
void extLoadShadowRenderMode(void);
void extLoadShadowVertex(void);
void extLoadShadowTev(void);
void extDrawShadow(void);
double cos(double x);
static inline f32 cosf(f32 x) { return cos(x); }

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_eff);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_hitobj_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_kagemario_init);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_get_pose);
USER_FUNC(evt_mario_jump_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_check_delete);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_set_color);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_start_for_event);
USER_FUNC(evt_party_jump_pos);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_dist);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_win_item_select);
USER_FUNC(get_npc_color);
USER_FUNC(teresa_eff);
USER_FUNC(senteresa_mario_spd);
USER_FUNC(senteresa_get_rot_center);
USER_FUNC(senteresa_wait_end_seq);
USER_FUNC(senteresa_end);
USER_FUNC(senteresa_turiageru);
USER_FUNC(senteresa_huttobu);
USER_FUNC(senteresa_dispoff);
USER_FUNC(senteresa_syugo);
USER_FUNC(senteresa_tikaduku_stop);
USER_FUNC(senteresa_get_random_position);
USER_FUNC(senteresa_get_seq);
static void senteresa_ext_shadow_disp(void);
static void senteresa_ext_disp(CameraId camera, void* param);
void senteresa_loadTev(void);
void senteresa_loadRenderMode(void);
static void senteresa_ext_dispent(void);
static void senteresa_ext_main(void);
static void senteresa_ext_init(void);
static void computePos(Teresa* ter, Vec* out);
s32 computeAlpha(Teresa* ter, MarioWork* mp, f32 angle);
void computeMtx(ExtPose* pose, f32 angle);
f32 computeAngle(ExtPose* pose, MarioWork* mp);
static f32 randf(f32 min, f32 max);
s32 randn(s32 min, s32 max);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_cam3d_event_from_road[];
extern s32 evt_cam3d_get_shift[];
extern s32 evt_ext_entry[];
extern s32 evt_item_flag_on[];
extern s32 evt_mario_cam_y_off[];
extern s32 evt_mario_cont_onoff[];
extern s32 evt_msg_continue[];
extern s32 evt_msg_print_add[];
extern s32 evt_msg_select[];
extern s32 evt_msg_toge[];
extern s32 evt_npc_battle_start[];
extern s32 evt_npc_get_dir[];
extern s32 evt_npc_glide_position[];
extern s32 evt_npc_set_anim[];
extern s32 evt_npc_set_battle_info[];
extern s32 evt_npc_set_scale[];
extern s32 evt_npc_wait_battle_end[];
extern s32 evt_party_cont_onoff[];
extern s32 evt_party_dispflg_onoff[];
extern s32 evt_party_get_pos[];
extern s32 evt_party_run[];
extern s32 evt_party_stop[];
extern s32 evt_usu_kagemario_party_kill[];
extern s32 npc_init_evt[];

__declspec(section ".data") u64 fd_jin_00_negone_one_374;
__declspec(section ".data") s32 fd_jin_00_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_00___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_00_one_negone_373;
__declspec(section ".data") s32 fd_jin_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_00_one_381[1];
__declspec(section ".data") u64 fd_jin_00_negone_one_360;
__declspec(section ".data") s32 fd_jin_00_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_00___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_00_one_negone_359;
__declspec(section ".data") s32 fd_jin_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_00_one_364[1];
static s32 w_open[22];
static s32 w_close[22];
__declspec(section ".data") s32 n3_open[12];
__declspec(section ".data") s32 n3_close[12];
static __declspec(section ".data") s32 s_open[12];
static __declspec(section ".data") s32 s_close[12];
static __declspec(section ".data") s32 n2_open[12];
static __declspec(section ".data") s32 n2_close[12];
__declspec(section ".data") s32 e3_open[12];
__declspec(section ".data") s32 e3_close[12];
__declspec(section ".data") s32 e1_open[12];
__declspec(section ".data") s32 e1_close[12];
__declspec(section ".data") s32 e2_open[12];
__declspec(section ".data") s32 e2_close[12];
s32 jin_00_dai[16];
s32 jin_00_dai_in_sub[83];
__declspec(section ".data") s32 jin_00_dai_in[9];
static s32 check_roll[16];
s32 teresa_n_fadein[48];
s32 teresa_n_fadeout[35];
s32 door_teresa_n[90];
s32 teresa_s_fadein[48];
s32 teresa_s_fadeout[35];
s32 door_teresa_s[90];
s32 bero_stg4majo3nin[15];
static s32 bero_entry_data[150];
s32 first_jin00[69];
static s32 push_evt[297];
__declspec(section ".data") s32 nopush_evt[5];
static __declspec(section ".data") s32 evt_key[5];
static __declspec(section ".data") s32 lock_tbl[2];
static s32 lock_item_check[23];
static __declspec(section ".data") s32 evt_unlock[10];
s32 tyuou_teresa_kusukusu[42];
s32 tyuou_teresa_look_mario[14];
s32 tyuou_teresa_init[35];
s32 tyuou_teresa_talk[391];
s32 oku_teresa_init[21];
s32 temae_teresa_init[21];
__declspec(section ".data") s32 atomic_teresa_init[2];
static s32 npcEnt[276];
static s32 senteresa_ext_entry_data[141];
s32 senteresa_evt[1248];
s32 jin_00_init_evt[221];

USER_FUNC(get_npc_color) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetValue(event, args[1], npc->color.r);
    evtSetValue(event, args[2], npc->color.g);
    evtSetValue(event, args[3], npc->color.b);
    evtSetValue(event, args[4], npc->color.a);
    return EVT_RETURN_DONE;
}

s32 randn(s32 min, s32 max) {
    return min + rand() % (max - min);
}

int rand(void);

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

f32 computeAngle(ExtPose* pose, MarioWork* mp) {
    f32 a = angleABf(mp->position.x, mp->position.z, pose->mtx[0][3], pose->mtx[2][3]);

    if (0.0f <= a && a < 90.0f) {
        return 90.0f - a;
    }
    if (90.0f <= a && a < 180.0f) {
        return 360.0f - (a - 90.0f);
    }
    if (180.0f <= a && a < 270.0f) {
        return 180.0f + (270.0f - a);
    }
    return 90.0f + (360.0f - a);
}

void computeMtx(ExtPose* pose, f32 angle) {
    Mtx m;

    PSMTXRotRad(m, 'Y', 0.017453292f * angle);
    pose->mtx[0][0] = m[0][0];
    pose->mtx[0][1] = m[0][1];
    pose->mtx[0][2] = m[0][2];
    pose->mtx[1][0] = m[1][0];
    pose->mtx[1][1] = m[1][1];
    pose->mtx[1][2] = m[1][2];
    pose->mtx[2][0] = m[2][0];
    pose->mtx[2][1] = m[2][1];
    pose->mtx[2][2] = m[2][2];
}

s32 computeAlpha(Teresa* ter, MarioWork* mp, f32 angle) {
    f32 dir;

    if (angle > 180.0f) {
        angle = 360.0f - angle;
    }
    dir = mp->displayDirectionTarget - 180.0f;
    if (dir < 0.0f) {
        dir += 360.0f;
    }
    if (dir < 90.0f) {
        if (angle < 90.0f) {
            ter->alpha = 128.0f * (angle / 90.0f) + 128.0f;
            return 0;
        }
        ter->alpha = 255;
        return 1;
    } else {
        if (angle > 90.0f) {
            ter->alpha = 128.0f * ((180.0f - angle) / 90.0f) + 128.0f;
            return 0;
        }
        ter->alpha = 255;
        return 1;
    }
}

static void computePos(Teresa* ter, Vec* out) {
    Vec v;
    Mtx m;

    v.x = ter->ofs.x;
    v.y = 0.0f;
    v.z = ter->ofs.z;

    PSMTXRotRad(m, 'Y', 0.017453292f * ter->angle);
    PSMTXMultVec(m, &v, out);
}

static void senteresa_ext_init(void) {
    ExtPose* pose = extGetPosePtr();
    MarioWork* mp = marioGetPtr();
    s32 n = extGetPoseNum();
    s32 i;

    pTeresa = _mapAlloc(sizeof(Teresa) * 200);
    for (i = 0; i < n; i++, pose++) {
        pose->flags = 3;
        PSMTXIdentity(pose->mtx);
        pTeresa[i].angle = 0.0f;
        pTeresa[i].wait = (i % 100 + 1) * 3;
        pTeresa[i].alpha = 0;
        pTeresa[i].seq = 0;
        pTeresa[i].field_0x20 = randf(0.0f, 0.1f);
        pTeresa[i].ofs.x = randf(-300.0f, 300.0f);
        pTeresa[i].ofs.y = 0.0f;
        pTeresa[i].ofs.z = randf(-235.0f, 235.0f);
        pose->mtx[0][3] = mp->position.x + pTeresa[i].ofs.x;
        pose->mtx[1][3] = randf(10.0f, 400.0f);
        pose->mtx[2][3] = mp->position.z + pTeresa[i].ofs.z;
        if (mp->position.x < pose->mtx[0][3]) {
            pose->rot = 90.0f;
        } else {
            pose->rot = 270.0f;
        }
    }
    g_nNumEndProc[0] = 0;
    g_nNumHarituku[0] = 0;
    g_nNumHuttobasu[0] = 0;
    g_nMarioMoveCnt = 0;
    g_fSpeed = 0.0f;
    g_bMove = 0;
    g_vecRotCenter.x = mp->position.x;
    g_vecRotCenter.y = 0.0f;
    g_vecRotCenter.z = mp->position.z;
}

__declspec(section ".data") u64 fd_jin_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_00_one_364[] = {
    1065353216,
};

static EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("door01L"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("door01R"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 0, STRING("door01L"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 0, STRING("door01R"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n3_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door03"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(n3_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door03"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door07"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door07"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n2_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(n2_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(e3_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door06"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(e3_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door06"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(e1_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door04"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(e1_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door04"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(e2_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door05"), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(e2_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door05"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_00_dai)
    DEBUG_PUT_MSG(STRING("出る"))
    CALL(evt_mario_normalize)
    SET_VALUE(GSWF(2079), 1)
    CALL(evt_bero_mapchange, STRING("jin_06"), 0)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(jin_00_dai_in_sub)
    CALL(evt_seq_wait, 2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, 390, -60, 0)
    CALL(evt_party_set_pos, 0, 390, -60, -10)
    CALL(evt_party_set_pos, 1, 390, -60, -20)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, -1)
    CALL(evt_party_set_dir, 1, 270, -1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_jump_pos, 365, 40, 0, 700, 0, -1000)
        CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_party_jump_pos, 0, 365, 40, -10, 700, 0, -1000)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(800)
        CALL(evt_party_jump_pos, 1, 365, 40, -20, 700, 0, -1000)
    END_INLINE_EVENT
    WAIT_MS(1500)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(jin_00_dai_in)
    DEBUG_PUT_MSG(STRING("入る"))
    SPAWN_EVENT(PTR(jin_00_dai_in_sub))
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(check_roll)
    CALL(evt_mario_get_motion, LW(0))
    IF_INT_EQUAL(LW(0), 22)
        SET_VALUE(LW(0), 0)
        ELSE
        SET_VALUE(LW(0), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(teresa_n_fadein)
    IS_EVENT_RUNNING(GW(0), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        DELETE_EVENT(GW(0))
    END_IF
    CALL(get_npc_color, STRING("奥扉テレサ"), LW(0), LW(1), LW(2), LW(3))
    LOOP(0)
        ADD(LW(3), 4)
        IF_INT_GREATER_OR_EQUAL(LW(3), 255)
            SET_VALUE(LW(3), 255)
            BREAK_LOOP
        END_IF
        CALL(evt_npc_set_color, STRING("奥扉テレサ"), 255, 255, 255, LW(3))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_color, STRING("奥扉テレサ"), 255, 255, 255, 255)
    RETURN
EVT_END()

EVT_BEGIN(teresa_n_fadeout)
    SET_VALUE(LW(0), 255)
    LOOP(0)
        SUBTRACT(LW(0), 4)
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            SET_VALUE(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_npc_set_color, STRING("奥扉テレサ"), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_color, STRING("奥扉テレサ"), 255, 255, 255, 0)
    RETURN
EVT_END()

EVT_BEGIN(door_teresa_n)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 197)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_start_for_event)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("奥扉テレサ"), LW(3), LW(4), LW(5))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_npc_set_ry, STRING("奥扉テレサ"), 270)
        CALL(evt_mario_set_dir, 90, 0, 0)
        SET_VALUE(LW(6), -20)
        SET_VALUE(LW(7), 90)
        ELSE
        CALL(evt_npc_set_ry, STRING("奥扉テレサ"), 90)
        CALL(evt_mario_set_dir, 270, 0, 0)
        SET_VALUE(LW(6), 20)
        SET_VALUE(LW(7), 270)
    END_IF
    CALL_CHILD(PTR(teresa_n_fadein))
    IF_INT_LESS(GSW(0), 196)
        CALL(evt_msg_print, 0, STRING("stg4_jin_49"), 0, STRING("奥扉テレサ"))
        ELSE
        CALL(evt_msg_print, 0, STRING("stg4_jin_51"), 0, STRING("奥扉テレサ"))
    END_IF
    SPAWN_EVENT_GET_ID(PTR(teresa_n_fadeout), GW(0))
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(teresa_s_fadein)
    IS_EVENT_RUNNING(GW(1), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        DELETE_EVENT(GW(1))
    END_IF
    CALL(get_npc_color, STRING("手前扉テレサ"), LW(0), LW(1), LW(2), LW(3))
    LOOP(0)
        ADD(LW(3), 4)
        IF_INT_GREATER_OR_EQUAL(LW(3), 255)
            SET_VALUE(LW(3), 255)
            BREAK_LOOP
        END_IF
        CALL(evt_npc_set_color, STRING("手前扉テレサ"), 255, 255, 255, LW(3))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_color, STRING("手前扉テレサ"), 255, 255, 255, 255)
    RETURN
EVT_END()

EVT_BEGIN(teresa_s_fadeout)
    SET_VALUE(LW(0), 255)
    LOOP(0)
        SUBTRACT(LW(0), 4)
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            SET_VALUE(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_npc_set_color, STRING("手前扉テレサ"), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_color, STRING("手前扉テレサ"), 255, 255, 255, 0)
    RETURN
EVT_END()

EVT_BEGIN(door_teresa_s)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 197)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_start_for_event)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("手前扉テレサ"), LW(3), LW(4), LW(5))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_npc_set_ry, STRING("手前扉テレサ"), 270)
        CALL(evt_mario_set_dir, 90, 0, 0)
        SET_VALUE(LW(6), -30)
        SET_VALUE(LW(7), 90)
        ELSE
        CALL(evt_npc_set_ry, STRING("手前扉テレサ"), 90)
        CALL(evt_mario_set_dir, 270, 0, 0)
        SET_VALUE(LW(6), 20)
        SET_VALUE(LW(7), 270)
    END_IF
    CALL_CHILD(PTR(teresa_s_fadein))
    IF_INT_LESS(GSW(0), 196)
        CALL(evt_msg_print, 0, STRING("stg4_jin_50"), 0, STRING("手前扉テレサ"))
        ELSE
        CALL(evt_msg_print, 0, STRING("stg4_jin_52"), 0, STRING("手前扉テレサ"))
    END_IF
    SPAWN_EVENT_GET_ID(PTR(teresa_s_fadeout), GW(1))
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

s32 bero_stg4majo3nin[] = {
    (s32)"w_bero", 65542, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"usu_00", (s32)"evt_majo3", 327685, (s32)w_close, (s32)w_open,
};

static s32 bero_entry_data[] = {
    (s32)"n_bero_1", 0, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)check_roll, (s32)"jin_05", (s32)"s_bero", 65537, 0, 0, (s32)"ana",
    251658240, 20000, 100000, 0, 0, -1, (s32)jin_00_dai_in, 0,
    (s32)jin_00_dai, (s32)"jin_06", 0, 262148, 0, 0, (s32)"w_bero", 65542,
    20000, 100000, 0, 0, 120, 0, -1, 0,
    (s32)"gra_06", (s32)"n_bero", 327685, (s32)w_close, (s32)w_open, (s32)"n_bero_3", 65538, 20000,
    100000, 0, 0, -1, 0, -1, (s32)door_teresa_n, (s32)"jin_01",
    (s32)"s_bero_1", 327685, (s32)n3_close, (s32)n3_open, (s32)"s_bero", 65538, 20000, 100000,
    0, 0, -1, 0, -1, (s32)door_teresa_s, (s32)"jin_02", (s32)"n_bero_1",
    327685, (s32)s_close, (s32)s_open, (s32)"n_bero_2", 65538, 20000, 100000, 0,
    0, -1, 0, -1, 0, (s32)"jin_04", (s32)"s_bero", 327685,
    (s32)n2_close, (s32)n2_open, (s32)"e_bero_3", 65538, 20000, 100000, 0, 0,
    -1, 0, -1, 0, (s32)"jin_03", (s32)"w_bero3", 327685, (s32)e3_close,
    (s32)e3_open, (s32)"e_bero_1", 65538, 20000, 100000, 0, 0, -1,
    0, -1, 0, (s32)"jin_03", (s32)"w_bero1", 327685, (s32)e1_close, (s32)e1_open,
    (s32)"e_bero_2", 65538, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"jin_03", (s32)"w_bero2", 327685, (s32)e2_close, (s32)e2_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

EVT_BEGIN(first_jin00)
    CALL(evt_mario_set_pos, -640, 0, 0)
    CALL(evt_party_set_pos, 0, -640, 0, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 227, 365, 1120, 227, 128, -223, 0, 11)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_seq_wait, 2)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -328, 365, 1120, -328, 128, -223, 5000, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL_CHILD(PTR(evt_bero_info_run))
    END_INLINE_EVENT
    WAIT_MS(5000)
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(1000)
    SET_VALUE(GSW(0), 194)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(push_evt)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_mario_get_pose, LW(0))
    IF_STR_NOT_EQUAL(LW(0), STRING("M_O_1"))
        CALL(evt_mario_set_pose, STRING("M_O_1"))
    END_IF
    SET_VALUE(LW(0), GW(10))
    MODULO(LW(0), 4)
    DIVIDE(LW(0), 2)
    IF_INT_LESS(GW(10), 40)
        MULTIPLY(LW(0), 1)
        ELSE
        MULTIPLY(LW(0), 2)
        BEGIN_INLINE_EVENT
            CALL(evt_sub_random, 100, LW(0))
            IF_INT_LESS(LW(0), 10)
                CALL(evt_mapobj_get_position, STRING("oki01"), LW(0), LW(1), LW(2))
                CALL(evt_eff, 0, STRING("kemuri"), 2, LW(0), 35, 40, 0, 0, 0, 0, 0, 0, 0, 0)
                ADD(LW(0), 20)
                CALL(evt_eff, 0, STRING("kemuri"), 2, LW(0), 35, 40, 0, 0, 0, 0, 0, 0, 0, 0)
            END_IF
        END_INLINE_EVENT
    END_IF
    CALL(evt_mapobj_trans, 1, STRING("oki01"), LW(0), 0, 0)
    ADD(GW(10), 1)
    IF_INT_GREATER_OR_EQUAL(GW(10), 80)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_mario_dispflag_onoff, 1, 2)
        CALL(evt_mario_set_pose, STRING("M_O_1"))
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SUCCESS1"))
        BEGIN_INLINE_EVENT
            CALL(evt_cam_shake, 4, FLOAT(0.0048828125f), FLOAT(0.0f), 1600)
        END_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_MOVE_PEDESTAL1"), LW(2), LW(3), LW(4), LW(8))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_MOVE_PEDESTAL2"), LW(2), LW(3), LW(4), LW(9))
        BEGIN_INLINE_EVENT
            LOOP(8)
                CALL(evt_mapobj_get_position, STRING("oki01"), LW(0), LW(1), LW(2))
                CALL(evt_eff, 0, STRING("kemuri"), 2, LW(0), 35, 40, 0, 0, 0, 0, 0, 0, 0, 0)
                ADD(LW(0), 20)
                CALL(evt_eff, 0, STRING("kemuri"), 2, LW(0), 35, 40, 0, 0, 0, 0, 0, 0, 0, 0)
                WAIT_MS(200)
            END_LOOP
        END_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 500, 1600)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_trans, 1, STRING("oki01"), LW(0), 0, 0)
        CALL(evt_hit_bind_update, STRING("a_oki01"))
        ADD(LW(0), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(0), 396)
            CALL(evt_mario_get_pose, LW(5))
            IF_STR_NOT_EQUAL(LW(5), STRING("M_N_7"))
                BEGIN_INLINE_EVENT
                    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED1"), LW(0), LW(1), LW(2), 0)
                END_INLINE_EVENT
                CALL(evt_mario_set_pose, STRING("M_N_7"))
            END_IF
            ELSE
            CALL(evt_mario_set_pos, LW(0), LW(3), LW(4))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        CALL(evt_snd_sfxoff, LW(8))
        CALL(evt_snd_sfxoff, LW(9))
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
        CALL(evt_mario_dispflag_onoff, 0, 2)
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_hitobj_onoff, STRING("a_futa"), 0, 0)
        SET_VALUE(GSW(0), 195)
        CALL(evt_exit_case_evt)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(nopush_evt)
    SET_VALUE(GW(10), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_key)
    SET_VALUE(GSW(0), 198)
    RETURN
EVT_END()

static __declspec(section ".data") s32 lock_tbl[] = {
    22, -1,
};

static EVT_BEGIN(lock_item_check)
    CALL(evt_pouch_check_item, 22, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(evt_win_item_select, 0, PTR(lock_tbl), LW(0), 0)
        IF_INT_EQUAL(LW(0), -1)
            CALL(evt_mobj_exec_cancel, STRING("me"))
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_unlock)
    SET_VALUE(GSW(0), 199)
    SET_VALUE(LW(0), STRING("n_bero_2"))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

EVT_BEGIN(tyuou_teresa_kusukusu)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_get_position, STRING("中央テレサ"), LW(3), LW(4), LW(5))
        CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(6))
        IF_INT_LESS(LW(6), 125)
            CALL(evt_msg_print, 0, STRING("stg4_jin_53"), 0, STRING("中央テレサ"))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(tyuou_teresa_look_mario)
    CALL(evt_seq_wait, 2)
    LOOP(0)
        CALL(evt_set_dir_to_target, STRING("中央テレサ"), STRING("mario"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(tyuou_teresa_init)
    SPAWN_EVENT(PTR(npc_init_evt))
    IF_INT_EQUAL(GSW(0), 196)
        CALL(evt_npc_set_position, STRING("me"), 70, 0, 0)
    END_IF
    IF_INT_EQUAL(GSW(0), 197)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), 32)
        CALL(evt_npc_set_color, STRING("me"), 255, 255, 255, 0)
        CALL(evt_npc_change_interrupt, STRING("me"), 6, 0)
    END_IF
    RETURN
EVT_END()

s32 tyuou_teresa_talk[] = {
    327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_54", 0, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 196699, (s32)evt_msg_select,
    0, (s32)"stg4_jin_54_yn", 131096, -30000000, 0, 196699, (s32)evt_msg_print_add, 0,
    (s32)"stg4_jin_55", 2, 32, 65627, (s32)evt_msg_continue, 33, 589915, (s32)evt_cam3d_evt_set,
    70, 165, 472, 70, 72, -45, 1000, 11,
    196699, (s32)evt_npc_set_anim, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", (s32)"A_1", 65546, 1000, 107, 131163,
    (s32)evt_mario_set_pose, (s32)"M_I_O", 196699, (s32)evt_mario_dispflag_onoff, 1, 2, 196699, (s32)evt_mario_dispflag_onoff,
    1, 256, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998,
    393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_SURPRISED1", -30000000, -29999999, -29999998, 0, 327771,
    (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54",
    -29999997, -29999996, -29999995, 131098, -30000000, -29999997, 196699, (s32)evt_npc_set_ry,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 270, 131126, -30000000, 40, 32, 196699, (s32)evt_npc_set_ry,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 90, 131125, -30000000, 40, 33, 458843, (s32)evt_mario_jump_pos,
    -30000000, -29999999, -29999998, 300, 0, -1000, 65546, 300,
    196699, (s32)evt_mario_dispflag_onoff, 0, 256, 196699, (s32)evt_mario_dispflag_onoff, 0, 2,
    109, 131163, (s32)evt_party_stop, 0, 107, 262235, (s32)evt_party_dispflg_onoff, 0,
    16, 1, 327771, (s32)evt_party_get_pos, 0, -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -29999997, -29999996, -29999995, 131098, -30000000,
    -29999997, 131126, -30000000, 40, 32, 131125, -30000000, 40,
    33, 524379, (s32)evt_party_jump_pos, 0, -30000000, -29999999, -29999998, 300,
    0, -1000, 65546, 300, 262235, (s32)evt_party_dispflg_onoff, 0, 16,
    0, 109, 131122, -90000000, 0, 107, 65541, 0,
    589915, (s32)evt_cam3d_evt_set, 70, 193, 689, 70, 72, 0,
    60, 11, 65546, 60, 131096, -90000000, 1, 7,
    33, 589915, (s32)evt_cam3d_evt_set, 70, 165, 472, 70, 72,
    -45, 60, 11, 65546, 60, 6, 109, 107,
    327771, (s32)evt_sub_intpl_msec_init, 11, 100, 400, 100, 65539, 1,
    65627, (s32)evt_sub_intpl_msec_get_value, 131133, -30000000, -229897600, 327771, (s32)evt_npc_set_scale, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54",
    -30000000, -30000000, -30000000, 65545, 1, 131096, -29999999, 1,
    65540, 1, 33, 109, 327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG4_TELESA_SURPRISED1", -30000000, -29999999, -29999998,
    0, 196699, (s32)evt_npc_set_anim, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", (s32)"S_1", 327771, (s32)evt_msg_toge, 1,
    0, 0, 0, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_56", 0,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 131163, (s32)evt_mario_set_pose, (s32)"M_S_1", 131122, -90000000, 1, 65545,
    1, 589915, (s32)evt_cam3d_evt_set, 70, 165, 472, 70, 72,
    -45, 500, 11, 327771, (s32)evt_sub_intpl_msec_init, 11, 400, 100,
    500, 65539, 2, 65627, (s32)evt_sub_intpl_msec_get_value, 131133, -30000000, -229897600,
    327771, (s32)evt_npc_set_scale, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -30000000, -30000000, 65545, 1,
    131096, -29999999, 1, 65540, 2, 33, 65546, 300,
    327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_57", 0, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 589915, (s32)evt_cam3d_evt_set,
    70, 400, 1125, 70, 200, -13, 1000, 11,
    65546, 1000, 107, 65546, 1000, 327771, (s32)evt_sub_intpl_msec_init, 11,
    255, 0, 500, 65539, 3, 65627, (s32)evt_sub_intpl_msec_get_value, 393307,
    (s32)evt_npc_set_color, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 255, 255, 255, -30000000, 65545, 1,
    131096, -29999999, 1, 65540, 3, 33, 393307, (s32)evt_npc_set_color,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 255, 255, 255, 0, 109, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 32, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -2147483648,
    262235, (s32)evt_npc_change_interrupt, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 6, 0, 65628, (s32)senteresa_evt, 65627,
    (s32)senteresa_wait_end_seq, 65546, 3500, 196699, (s32)evt_cam3d_evt_off, 500, 11, 131163,
    (s32)evt_party_run, 0, 131122, -170000000, 197, 2, 1,
};

EVT_BEGIN(oku_teresa_init)
    SPAWN_EVENT(PTR(npc_init_evt))
    IF_INT_LESS(GSW(0), 197)
        CALL(evt_npc_set_position, STRING("me"), -60, 45, -238)
        CALL(evt_npc_set_color, STRING("me"), 255, 255, 255, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(temae_teresa_init)
    SPAWN_EVENT(PTR(npc_init_evt))
    IF_INT_LESS(GSW(0), 197)
        CALL(evt_npc_set_position, STRING("me"), -60, 45, 238)
        CALL(evt_npc_set_color, STRING("me"), 255, 255, 255, 0)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(atomic_teresa_init)
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"テレサ"*/"\x83\x65\x83\x8C\x83\x54", 1073743360, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54",
    1073743360, 0, (s32)tyuou_teresa_init, 0, (s32)tyuou_teresa_talk, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"奥扉テレサ"*/"\x89\x9C\x94\xE0\x83\x65\x83\x8C\x83\x54", 1073743392,
    0, (s32)oku_teresa_init, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"手前扉テレサ"*/"\x8E\xE8\x91\x4F\x94\xE0\x83\x65\x83\x8C\x83\x54", 1073743392, 0,
    (s32)temae_teresa_init, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", 262304, 0, (s32)atomic_teresa_init,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"1001テレサ"*/"\x31\x30\x30\x31\x83\x65\x83\x8C\x83\x54", 262304, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)/*"1002テレサ"*/"\x31\x30\x30\x32\x83\x65\x83\x8C\x83\x54", 262304, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)/*"1003テレサ"*/"\x31\x30\x30\x33\x83\x65\x83\x8C\x83\x54", 262304, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)/*"1004テレサ"*/"\x31\x30\x30\x34\x83\x65\x83\x8C\x83\x54", 262304, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"1005テレサ"*/"\x31\x30\x30\x35\x83\x65\x83\x8C\x83\x54",
    262304, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"1006テレサ"*/"\x31\x30\x30\x36\x83\x65\x83\x8C\x83\x54", 262304,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 senteresa_ext_entry_data[] = {
    (s32)"c_teresa", (s32)"S_1", 0, (s32)"c_teresa", (s32)"S_1", 1084227584, (s32)"c_teresa", (s32)"S_1",
    1092616192, (s32)"c_teresa", (s32)"S_1", 1097859072, (s32)"c_teresa", (s32)"S_1", 1101004800, (s32)"c_teresa",
    (s32)"S_1", 1103626240, (s32)"c_teresa", (s32)"S_1", 1106247680, (s32)"c_teresa", (s32)"S_1", 1108082688,
    (s32)"c_teresa", (s32)"S_1", 1109393408, (s32)"c_teresa", (s32)"S_1", 1110704128, (s32)"c_teresa", (s32)"S_1",
    1112014848, (s32)"c_teresa", (s32)"S_1", 1113325568, (s32)"c_teresa", (s32)"S_1", 1114636288, (s32)"c_teresa",
    (s32)"S_1", 1115815936, (s32)"c_teresa", (s32)"S_1", 1116471296, (s32)"c_teresa", (s32)"S_1", 1117126656,
    (s32)"c_teresa", (s32)"W_1", 0, (s32)"c_teresa", (s32)"W_1", 1065353216, (s32)"c_teresa", (s32)"W_1",
    1073741824, (s32)"c_teresa", (s32)"W_1", 1077936128, (s32)"c_teresa", (s32)"W_1", 1082130432, (s32)"c_teresa",
    (s32)"W_1", 1084227584, (s32)"c_teresa", (s32)"W_1", 1086324736, (s32)"c_teresa", (s32)"W_1", 1088421888,
    (s32)"c_teresa", (s32)"W_1", 1090519040, (s32)"c_teresa", (s32)"W_1", 1091567616, (s32)"c_teresa", (s32)"D_1",
    0, (s32)"c_teresa", (s32)"D_1", 1065353216, (s32)"c_teresa", (s32)"D_1", 1073741824, (s32)"c_teresa",
    (s32)"D_1", 1077936128, (s32)"c_teresa", (s32)"D_1", 1082130432, (s32)"c_teresa", (s32)"D_1", 1084227584,
    (s32)"c_teresa", (s32)"D_1", 1086324736, (s32)"c_teresa", (s32)"D_1", 1088421888, (s32)"c_teresa", (s32)"A_2",
    0, (s32)"c_teresa", (s32)"A_2", 1065353216, (s32)"c_teresa", (s32)"A_2", 1073741824, (s32)"c_teresa",
    (s32)"A_2", 1077936128, (s32)"c_teresa", (s32)"A_2", 1082130432, (s32)"c_teresa", (s32)"A_2", 1084227584,
    (s32)"c_teresa", (s32)"A_2", 1086324736, (s32)"c_teresa", (s32)"A_2", 1088421888, (s32)"c_teresa", (s32)"A_2",
    1090519040, (s32)"c_teresa", (s32)"A_2", 1091567616, (s32)"c_teresa", (s32)"A_2", 1092616192, (s32)"c_teresa",
    (s32)"A_2", 1093664768, 0, 0, 0,
};

static void senteresa_ext_main(void) {
    ExtPose* pose = extGetPosePtr();
    MarioWork* mp = marioGetPtr();
    s32 n = extGetPoseNum();
    s32 i;
    s32 hammer = 0;
    s32 bero;
    s32 party;
    s32 res;
    u8 alpha;
    f32 angle;
    f32 spd;
    Vec v;
    Vec d;

    if (marioGetAngleKaitenHammer() > 0.0f) {
        hammer = 1;
    }
    PSVECSubtract(&mp->position, &g_vecRotCenter, &d);
    if (mp->baseSpeed > 0.0f) {
        g_bMove = 1;
    }
    if (g_bMove) {
        g_nMarioMoveCnt++;
    }
    if (g_nMarioMoveCnt > 12) {
        g_fSpeed += 0.01f;
        if (g_fSpeed > 2.6f) {
            g_fSpeed = 2.6f;
        }
        if (d.x == 0.0f && d.y == 0.0f && d.z == 0.0f) {
            g_vecRotCenter = mp->position;
            if (mp->baseSpeed == 0.0f) {
                g_fSpeed = 0.0f;
                g_bMove = 0;
                g_nMarioMoveCnt = 0;
            }
        } else {
            f32 mag = PSVECMag(&d);
            if (mag > 50.0f) {
                spd = 2.6f;
            } else {
                spd = 2.6f * mag / 50.0f;
            }
            if (g_fSpeed > spd) {
                g_fSpeed = spd;
            }
            PSVECNormalize(&d, &d);
            PSVECScale(&d, &d, g_fSpeed);
            PSVECAdd(&g_vecRotCenter, &d, &g_vecRotCenter);
            PSVECSubtract(&g_vecRotCenter, &mp->position, &v);
            if (PSVECMag(&v) < 0.3f) {
                g_vecRotCenter = mp->position;
                if (mp->baseSpeed == 0.0f) {
                    g_fSpeed = 0.0f;
                    g_bMove = 0;
                    g_nMarioMoveCnt = 0;
                }
            }
        }
    }
    bero = (bero_get_BeroEXEC() & 3) != 0;
    party = 0;
    if (partyGetPtr(0) != NULL && (partyGetPtr(0)->flags & 0x100)) {
        party = 1;
    }
    for (i = 0; i < n; i++, pose++) {
        switch (pTeresa[i].seq) {
            case 0:
                pose->frame = 0;
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    if (i == 0) {
                        Vec pos = {0.0f, 200.0f, 0.0f};
                        psndSFXOn_3D((const char*)0x5D3, &pos);
                    }
                    pTeresa[i].seq++;
                }
                break;
            case 1:
                pose->frame = (gp->retraceCount / 5 + i * i) % 16;
                if (mp->position.x < pose->mtx[0][3]) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                computePos(&pTeresa[i], &v);
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                v.y = pose->mtx[1][3];
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                angle = computeAngle(pose, mp);
                pTeresa[i].alpha += 3;
                alpha = pTeresa[i].alpha;
                computeAlpha(&pTeresa[i], mp, angle);
                if (pTeresa[i].alpha < alpha) {
                    pTeresa[i].seq++;
                    g_nNumEndProc[0]++;
                    if (i == 0) {
                        Vec pos = {0.0f, 200.0f, 0.0f};
                        psndSFXOn_3D((const char*)0x5D3, &pos);
                    }
                } else {
                    pTeresa[i].alpha = alpha;
                    if (pTeresa[i].alpha >= 250) {
                        pTeresa[i].alpha = 255;
                        pTeresa[i].seq++;
                        g_nNumEndProc[0]++;
                        if (i == 0) {
                            Vec pos = {0.0f, 200.0f, 0.0f};
                            psndSFXOn_3D((const char*)0x5D3, &pos);
                        }
                    }
                }
                break;
            case 2:
                pose->frame = (gp->retraceCount / 5 + i * i) % 16;
                if (mp->position.x < pose->mtx[0][3]) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                computePos(&pTeresa[i], &v);
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                v.y = pose->mtx[1][3];
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                angle = computeAngle(pose, mp);
                computeAlpha(&pTeresa[i], mp, angle);
                if (g_nNumEndProc[0] == 200) {
                    pTeresa[i].wait = i + 1;
                    pTeresa[i].seq++;
                }
                break;
            case 3:
                pose->frame = (gp->retraceCount / 5 + i * i) % 16;
                if (mp->position.x < pose->mtx[0][3]) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                computePos(&pTeresa[i], &v);
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                v.y = pose->mtx[1][3];
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pTeresa[i].field_0x1C += 0.08f;
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    pose->flags &= ~2;
                    pTeresa[i].wait = i * 30 + rand() % 10 + 295;
                    pTeresa[i].seq++;
                }
                break;
            case 4:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                computePos(&pTeresa[i], &v);
                v.y = pose->mtx[1][3];
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[1][3] = v.y;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                pTeresa[i].field_0x20 += 0.01f;
                if (pTeresa[i].field_0x20 > 1.2f) {
                    pTeresa[i].field_0x20 = 1.2f;
                }
                pTeresa[i].angle += pTeresa[i].field_0x20;
                if (pTeresa[i].angle > 360.0f) {
                    pTeresa[i].angle -= 360.0f;
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                res = computeAlpha(&pTeresa[i], mp, angle);
                if (g_nNumHuttobasu[0] >= 20) {
                    break;
                }
                if (res && rand() % 1000 == 312) {
                    pTeresa[i].wait = 100;
                    pTeresa[i].seq = 9;
                }
                if (!party && g_nNumHuttobasu[0] < 20) {
                    pTeresa[i].wait--;
                    if (pTeresa[i].wait == 0) {
                        pTeresa[i].field_0x1C = 0.0f;
                        pTeresa[i].seq++;
                    }
                }
                break;
            case 5:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                v.x = pose->mtx[0][3];
                v.y = pose->mtx[1][3];
                v.z = pose->mtx[2][3];
                PSVECSubtract(&mp->position, &v, &d);
                PSVECNormalize(&d, &d);
                PSVECScale(&d, &d, 1.8f);
                PSVECAdd(&v, &d, &v);
                pose->mtx[0][3] = v.x;
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pose->mtx[2][3] = v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                if (!party) {
                    PSVECSubtract(&v, &mp->position, &v);
                    if (PSVECMag(&v) <= 25.0f) {
                        f32 dy = pose->mtx[1][3] - mp->position.y;
                        if (dy > -2.0f && dy < 10.0f) {
                            pTeresa[i].ofs.x = pose->mtx[0][3] - mp->position.x;
                            pTeresa[i].ofs.y = pose->mtx[1][3] - mp->position.y;
                            pTeresa[i].ofs.z = pose->mtx[2][3] - mp->position.z;
                            pTeresa[i].seq++;
                            if (!bero) {
                                g_nNumHarituku[0]++;
                            }
                        }
                    }
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                computeAlpha(&pTeresa[i], mp, angle);
                break;
            case 6:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                pose->mtx[0][3] = mp->position.x + pTeresa[i].ofs.x;
                pose->mtx[1][3] = mp->position.y + pTeresa[i].ofs.y;
                pose->mtx[2][3] = mp->position.z + pTeresa[i].ofs.z;
                angle = computeAngle(pose, mp);
                computeAlpha(&pTeresa[i], mp, angle);
                if (hammer) {
                    v.x = pose->mtx[0][3];
                    v.y = pose->mtx[1][3];
                    v.z = pose->mtx[2][3];
                    PSVECSubtract(&v, &mp->position, &d);
                    PSVECNormalize(&d, &d);
                    pTeresa[i].vel.x = 4.2f * d.x;
                    if (d.z > 0.0f) {
                        spd = d.z * randf(5.2f, 12.7f);
                    } else {
                        spd = d.z * randf(-5.0f, -2.0f);
                    }
                    pTeresa[i].vel.z = spd;
                    pTeresa[i].vel.y = randf(6.0f, 10.0f);
                    pTeresa[i].seq = 10;
                    computeMtx(pose, 0.0f);
                    g_nNumHarituku[0]--;
                    g_nNumHuttobasu[0]++;
                    {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        psndSFXOn_3D((const char*)0x5D7, &pos);
                    }
                }
                break;
            case 9:
                pose->frame = (s32)(12.0f * ((100.0f - pTeresa[i].wait) / 100.0f)) + 34;
                computePos(&pTeresa[i], &v);
                v.y = pose->mtx[1][3];
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                pTeresa[i].angle += 1.2f;
                if (pTeresa[i].angle > 360.0f) {
                    pTeresa[i].angle -= 360.0f;
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                res = computeAlpha(&pTeresa[i], mp, angle);
                pTeresa[i].wait--;
                if (!res || pTeresa[i].wait == 0) {
                    pTeresa[i].wait = rand() % 300 + 200;
                    pTeresa[i].seq = 4;
                }
                break;
            case 10:
                pose->frame = (gp->retraceCount + i * i) % 8 + 26;
                pose->mtx[0][3] += pTeresa[i].vel.x;
                pose->mtx[1][3] += pTeresa[i].vel.y;
                pose->mtx[2][3] += pTeresa[i].vel.z;
                pTeresa[i].vel.y -= 0.3f;
                if (pose->mtx[1][3] < -20.0f) {
                    pose->flags = 0;
                    pTeresa[i].seq = 99;
                }
                break;
            case 20:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                computePos(&pTeresa[i], &v);
                v.y = pose->mtx[1][3];
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                pTeresa[i].angle += 1.2f;
                if (pTeresa[i].angle > 360.0f) {
                    pTeresa[i].angle -= 360.0f;
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                computeAlpha(&pTeresa[i], mp, angle);
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    pose->flags = 3;
                    pTeresa[i].from.x = pose->mtx[0][3];
                    pTeresa[i].from.y = pose->mtx[1][3];
                    pTeresa[i].from.z = pose->mtx[2][3];
                    pTeresa[i].field_0x1C = 0.0f;
                    pTeresa[i].seq++;
                }
                break;
            case 21: {
                f32 t;

                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                t = pTeresa[i].field_0x1C;
                if (t >= 1.0f) {
                    pTeresa[i].seq = 22;
                    {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        psndSFXOn_3D((const char*)0x5D4, &pos);
                    }
                    g_nNumEndProc[0]++;
                } else {
                    v.x = (1.0f - t) * pTeresa[i].from.x + t * pTeresa[i].to.x;
                    v.y = (1.0f - t) * pTeresa[i].from.y + t * pTeresa[i].to.y;
                    v.z = (1.0f - t) * pTeresa[i].from.z + t * pTeresa[i].to.z;
                    pose->mtx[0][3] = v.x;
                    pose->mtx[1][3] = 20.0f * (f32)sin(6.28f * pTeresa[i].field_0x1C) + v.y;
                    pose->mtx[2][3] = v.z;
                    pTeresa[i].field_0x1C += 0.01f;
                }
                break;
            }
            case 22:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                if ((pTeresa[i].wait & 7) == 0) {
                    pose->mtx[0][3] += 2.0f;
                } else if ((pTeresa[i].wait & 7) == 3) {
                    pose->mtx[0][3] -= 2.0f;
                }
                pTeresa[i].wait++;
                break;
            case 30:
                pose->frame = (gp->retraceCount + i * i) % 8 + 26;
                pose->mtx[0][3] += pTeresa[i].vel.x;
                pose->mtx[1][3] += pTeresa[i].vel.y;
                pose->mtx[2][3] += pTeresa[i].vel.z;
                pTeresa[i].vel.y -= 0.3f;
                if (pose->mtx[1][3] < -10.0f) {
                    pose->flags = 0;
                    pTeresa[i].seq = 99;
                    g_nNumEndProc[0]++;
                }
                break;
            case 80:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                pose->mtx[1][3] = mp->position.y + pTeresa[i].ofs.y;
                break;
            case 99:
                break;
        }
    }
}

static void senteresa_ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, senteresa_ext_disp, NULL);
}

void senteresa_loadRenderMode(void) {
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}

void senteresa_loadTev(void) {
    GXColor fogColor = {0xFF, 0xFF, 0xFF, 0xFF};

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogColor);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
}

static void senteresa_ext_disp(CameraId camera, void* param) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    s32 n = extGetPoseNum();
    s32 i;

    senteresa_loadRenderMode();
    extLoadVertex();
    extLoadTexture();
    senteresa_loadTev();
    for (i = 0; i < n; i++) {
        color.a = pTeresa[i].alpha;
        GXSetTevColor(GX_TEVREG0, color);
        extPoseDraw(i);
    }
    extLoadTextureExit();
}

static void senteresa_ext_shadow_disp(void) {
    static Mtx mt = {
        {10.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 10.0f, 0.0f, 0.1f},
        {0.0f, 0.0f, 10.0f, 0.0f},
    };

    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}

USER_FUNC(senteresa_get_seq) {
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], pTeresa[i].seq);
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_get_random_position) {
    s32* args = event->args;
    ExtPose* pose = extGetPosePtr();
    s32 n = extGetPoseNum();

    pose += rand() % n;
    evtSetFloat(event, args[0], pose->mtx[0][3]);
    evtSetFloat(event, args[1], pose->mtx[1][3]);
    evtSetFloat(event, args[2], pose->mtx[2][3]);
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_tikaduku_stop) {
    s32 n = extGetPoseNum();
    s32 i;

    for (i = 0; i < n; i++) {
        if (pTeresa[i].seq != 10) {
            pTeresa[i].seq = 4;
            pTeresa[i].wait = 99999;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_syugo) {
    ExtPose* pose = extGetPosePtr();
    NpcEntry* npc = npcNameToPtr("\222\206\211\233\203e\203\214\203T");
    s32 n = extGetPoseNum();
    s32 i;
    f32 a;
    f32 r;

    g_nNumEndProc[0] = 0;
    for (i = 0; i < n; i++, pose++) {
        pTeresa[i].from.x = pose->mtx[0][3];
        pTeresa[i].from.y = pose->mtx[1][3];
        pTeresa[i].from.z = pose->mtx[2][3];
        a = randf(0.0f, 6.2831f);
        r = randf(0.0f, 25.0f);
        pTeresa[i].to.x = r * cosf(a) + npc->position.x;
        pTeresa[i].to.y = r * sinf(a) + npc->position.y;
        pTeresa[i].to.z = npc->position.z;
        pTeresa[i].field_0x1C = 0.0f;
        pTeresa[i].wait = (i & 15) + rand() % 10 * 30 + 1;
        pTeresa[i].alpha = 255;
        pTeresa[i].seq = 20;
        if (pTeresa[i].from.x < pTeresa[i].to.x) {
            pose->rot = 270.0f;
        } else {
            pose->rot = 90.0f;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_dispoff) {
    ExtPose* pose = extGetPosePtr();
    s32 n = extGetPoseNum();
    s32 i;

    for (i = 0; i < n; i++, pose++) {
        pose->flags = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_huttobu) {
    ExtPose* pose = extGetPosePtr();
    NpcEntry* npc = npcNameToPtr("\203A\203g\203~\203b\203N\203e\203\214\203T");
    s32 n = extGetPoseNum();
    s32 i;
    f32 scale;

    g_nNumEndProc[0] = 0;
    for (i = 0; i < n; i++, pose++) {
        pose->flags = 3;
        pose->mtx[0][3] = npc->position.x;
        pose->mtx[1][3] = npc->position.y;
        pose->mtx[2][3] = npc->position.z;
        pTeresa[i].vel.x = 4.0f * (f32)sin(pTeresa[i].angle);
        pTeresa[i].vel.y = randf(6.0f, 12.0f);
        pTeresa[i].vel.z = cos(pTeresa[i].angle);
        if (pTeresa[i].vel.z > 0.0f) {
            scale = randf(5.0f, 12.5f);
        } else {
            scale = randf(-5.0f, -2.0f);
        }
        pTeresa[i].vel.z *= scale;
        pTeresa[i].alpha = 255;
        pTeresa[i].seq = 30;
        if (i & 1) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = pose->mtx[0][3];
            pos.y = pose->mtx[1][3];
            pos.z = pose->mtx[2][3];
            psndSFXOn_3D((const char*)0x5D7, &pos);
        }
    }
    return EVT_RETURN_DONE;
}

s32 senteresa_evt[] = {
    393307, (s32)evt_ext_entry, 200, (s32)senteresa_ext_entry_data, (s32)senteresa_ext_init, (s32)senteresa_ext_main, (s32)senteresa_ext_dispent, 65541,
    0, 196699, (s32)senteresa_get_seq, 199, -30000000, 131101, -30000000, 4,
    7, 33, 65545, 1, 6, 131122, -50000000, 0,
    107, 65546, 600, 65541, 0, 327771, (s32)evt_mario_get_pos, 0,
    -30000000, -29999999, -29999998, 327771, (s32)evt_cam3d_get_shift, -30000000, -29999999, -29999998,
    -29999992, 262235, (s32)senteresa_get_rot_center, -30000000, -29999999, -29999998, 131122, -29999997,
    -30000000, 131125, -29999997, -29999992, 131125, -29999997, 65, 196699,
    (s32)evt_sub_random, 65, -29999996, 131125, -29999997, -29999996, 131122, -29999995,
    -29999999, 131125, -29999995, 5, 196699, (s32)evt_sub_random, 40, -29999994,
    131125, -29999995, -29999994, 131122, -29999993, -29999998, 131126, -29999993,
    90, 327771, (s32)evt_msg_toge, 3, -29999997, -29999995, -29999993, 327771,
    (s32)evt_msg_print, 0, (s32)"stg4_jin_58", 0, 0, 196699, (s32)evt_sub_random, 200,
    -30000000, 131125, -30000000, 100, 65546, -30000000, 131096, -50000000,
    1, 7, 33, 6, 109, 107, 65546, 600,
    65541, 0, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998,
    327771, (s32)evt_cam3d_get_shift, -30000000, -29999999, -29999998, -29999992, 262235, (s32)senteresa_get_rot_center,
    -30000000, -29999999, -29999998, 131122, -29999997, -30000000, 131125, -29999997,
    -29999992, 131126, -29999997, 32, 196699, (s32)evt_sub_random, 65, -29999996,
    131125, -29999997, -29999996, 131122, -29999995, -29999999, 131125, -29999995,
    5, 196699, (s32)evt_sub_random, 70, -29999994, 131125, -29999995, -29999994,
    131122, -29999993, -29999998, 131126, -29999993, 90, 327771, (s32)evt_msg_toge,
    3, -29999997, -29999995, -29999993, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_59",
    0, 0, 196699, (s32)evt_sub_random, 200, -30000000, 131125, -30000000,
    100, 65546, -30000000, 131096, -50000000, 1, 7, 33,
    6, 109, 107, 65546, 900, 65541, 0, 327771,
    (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 327771, (s32)evt_cam3d_get_shift, -30000000,
    -29999999, -29999998, -29999992, 262235, (s32)senteresa_get_rot_center, -30000000, -29999999, -29999998,
    131122, -29999997, -30000000, 131125, -29999997, -29999992, 131126, -29999997,
    110, 196699, (s32)evt_sub_random, 45, -29999996, 131125, -29999997, -29999996,
    131122, -29999995, -29999999, 131125, -29999995, 45, 196699, (s32)evt_sub_random,
    30, -29999994, 131125, -29999995, -29999994, 131122, -29999993, -29999998,
    131126, -29999993, 90, 327771, (s32)evt_msg_toge, 3, -29999997, -29999995,
    -29999993, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_60", 0, 0, 196699,
    (s32)evt_sub_random, 300, -30000000, 131125, -30000000, 100, 65546, -30000000,
    131096, -50000000, 1, 7, 33, 6, 109, 107,
    65546, 750, 65541, 0, 327771, (s32)evt_mario_get_pos, 0, -30000000,
    -29999999, -29999998, 327771, (s32)evt_cam3d_get_shift, -30000000, -29999999, -29999998, -29999992,
    262235, (s32)senteresa_get_rot_center, -30000000, -29999999, -29999998, 131122, -29999997, -30000000,
    131125, -29999997, -29999992, 131125, -29999997, 55, 196699, (s32)evt_sub_random,
    75, -29999996, 131125, -29999997, -29999996, 131122, -29999995, -29999999,
    131126, -29999995, 80, 196699, (s32)evt_sub_random, 30, -29999994, 131126,
    -29999995, -29999994, 131122, -29999993, -29999998, 131126, -29999993, 90,
    327771, (s32)evt_msg_toge, 3, -29999997, -29999995, -29999993, 327771, (s32)evt_msg_print,
    0, (s32)"stg4_jin_59", 0, 0, 196699, (s32)evt_sub_random, 200, -30000000,
    131125, -30000000, 100, 65546, -30000000, 131096, -50000000, 1,
    7, 33, 6, 109, 107, 65546, 900, 65541,
    0, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 327771,
    (s32)evt_cam3d_get_shift, -30000000, -29999999, -29999998, -29999992, 262235, (s32)senteresa_get_rot_center, -30000000,
    -29999999, -29999998, 131122, -29999997, -30000000, 131125, -29999997, -29999992,
    131126, -29999997, 110, 196699, (s32)evt_sub_random, 75, -29999996, 131125,
    -29999997, -29999996, 131122, -29999995, -29999999, 131126, -29999995, 80,
    196699, (s32)evt_sub_random, 30, -29999994, 131126, -29999995, -29999994, 131122,
    -29999993, -29999998, 131126, -29999993, 90, 327771, (s32)evt_msg_toge, 3,
    -29999997, -29999995, -29999993, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_58", 0,
    0, 196699, (s32)evt_sub_random, 300, -30000000, 131125, -30000000, 100,
    65546, -30000000, 131096, -50000000, 1, 7, 33, 6,
    109, 65541, 0, 131157, -30000000, (s32)g_nNumHuttobasu, 131101, -30000000,
    20, 131122, -50000000, 1, 7, 33, 65627, (s32)senteresa_mario_spd,
    65545, 1, 131157, -30000000, (s32)g_nNumHarituku, 131101, -30000000, 20,
    131163, (s32)evt_mario_key_onoff, 0, 65627, (s32)evt_mario_normalize, 131163, (s32)evt_mario_cont_onoff, 0,
    196699, (s32)evt_party_cont_onoff, 0, 0, 327771, (s32)evt_mario_get_pos, 0, -30000000,
    -29999999, -29999998, 327771, (s32)evt_cam3d_get_shift, -30000000, -29999999, -29999998, -29999997,
    720987, (s32)evt_cam3d_event_from_road, -30000000, -29999999, -29999998, -29999997, -29999996, -29999995,
    -29999994, -29999993, -29999992, -29999991, 589915, (s32)evt_cam3d_evt_set, -29999996, -29999995,
    -29999994, -29999993, -29999992, -29999991, 0, 11, 131163, (s32)evt_mario_set_pose,
    (s32)"M_I_O", 65627, (s32)evt_mario_cam_y_off, 65627, (s32)senteresa_turiageru, 327771, (s32)evt_mario_get_pos, 0,
    -30000000, -29999999, -29999998, 327771, (s32)evt_party_set_pos, 0, -30000000, -29999999,
    -29999998, 65541, 150, 131130, -29999999, -229998976, 262235, (s32)evt_mario_set_pos,
    -30000000, -29999999, -29999998, 327771, (s32)evt_party_set_pos, 0, -30000000, -29999999,
    -29999998, 65545, 1, 6, 131122, -129997773, 1, 65627,
    (s32)evt_mario_normalize, 131096, -170000000, 201, 196699, (s32)evt_bero_mapchange, (s32)"usu_00", (s32)"evt_majo3",
    32, 196699, (s32)evt_bero_mapchange, (s32)"gra_06", (s32)"n_bero", 33, 33, 65545,
    1, 6, 65627, (s32)senteresa_tikaduku_stop, 131163, (s32)evt_mario_key_onoff, 0, 65546,
    2500, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131125,
    -29999999, 60, 327771, (s32)evt_npc_set_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_set_scale, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 1, 1, 1, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -2147483648, 107, 65546, 300, 327771, (s32)evt_npc_get_position,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 131126, -29999999, 20, 720987,
    (s32)evt_cam3d_event_from_road, -30000000, -29999999, -29999998, 0, -29999996, -29999995, -29999994,
    -29999993, -29999992, -29999991, 589915, (s32)evt_cam3d_evt_set, -29999996, -29999995, -29999994,
    -29999993, -29999992, -29999991, 1000, 11, 109, 131122, -30000000,
    0, 65541, 25, 131125, -30000000, 10, 393307, (s32)evt_npc_set_color,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 255, 255, 255, -30000000, 65545, 1, 6,
    393307, (s32)evt_npc_set_color, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 255, 255, 255, 255, 65546,
    800, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_61", 0, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 65546,
    500, 327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 131126,
    -29999999, 20, 720987, (s32)evt_cam3d_event_from_road, -30000000, -29999999, -29999998, 0,
    -29999996, -29999995, -29999994, -29999993, -29999992, -29999991, 131125, -29999995,
    160, 131125, -29999992, 160, 107, 589915, (s32)evt_cam3d_evt_set, -29999996,
    -29999995, -29999994, -29999993, -29999992, -29999991, 2000, 11, 65546,
    1000, 109, 327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -29999998, -29999997, -29999996,
    131122, -29999995, -29999997, 131125, -29999995, 200, 327771, (s32)evt_sub_intpl_msec_init,
    11, -29999997, -29999995, 2000, 65539, 0, 65627, (s32)evt_sub_intpl_msec_get_value,
    327771, (s32)evt_npc_set_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -29999998, -30000000, -29999996, 65545, 1,
    131096, -29999999, 1, 65540, 0, 33, 327771, (s32)evt_npc_get_position,
    (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 196699, (s32)evt_npc_get_dir, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -29999997,
    327771, (s32)evt_npc_set_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 196699, (s32)evt_npc_set_ry,
    (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -29999997, 65627, (s32)senteresa_syugo, 65541, 0, 131157, -30000000,
    (s32)g_nNumEndProc, 131096, -30000000, 200, 7, 33, 65545, 1,
    6, 327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 262235,
    (s32)teresa_eff, -30000000, -29999999, -29999998, 65546, 500, 65627, (s32)senteresa_dispoff,
    327771, (s32)evt_npc_get_position, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 131126, -29999999,
    25, 327771, (s32)evt_npc_set_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"中央テレサ"*/"\x92\x86\x89\x9B\x83\x65\x83\x8C\x83\x54", 128, 262235, (s32)evt_npc_flag_onoff, 0, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54",
    128, 327771, (s32)evt_msg_toge, 1, 0, 0, 0, 327771,
    (s32)evt_msg_print, 0, (s32)"stg4_jin_62", 0, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", 196699, (s32)evt_cam3d_evt_off, 400,
    11, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 393307,
    (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_SURPRISED1_2", -30000000, -29999999, -29999998, 0, 131163, (s32)evt_mario_set_pose,
    (s32)"M_I_O", 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131125,
    -29999999, 30, 131125, -29999998, 3, 655451, (s32)evt_npc_glide_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54",
    -30000000, -29999999, -29999998, 0, -229539200, 1, 11, 0,
    327771, (s32)evt_cam_shake, 4, -229999990, -230000000, 1000, 131163, (s32)evt_mario_set_pose,
    (s32)"M_S_1", 107, 65541, 100, 327771, (s32)evt_npc_get_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000,
    -29999999, -29999998, 131126, -29999999, 4, 327771, (s32)evt_npc_set_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54",
    -30000000, -29999999, -29999998, 65546, 10, 327771, (s32)evt_npc_get_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54",
    -30000000, -29999999, -29999998, 131125, -29999999, 4, 327771, (s32)evt_npc_set_position,
    (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998, 65546, 10, 6, 109,
    107, 65541, 50, 327771, (s32)evt_npc_get_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000, -29999999,
    -29999998, 131126, -30000000, 4, 327771, (s32)evt_npc_set_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000,
    -29999999, -29999998, 65546, 20, 327771, (s32)evt_npc_get_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000,
    -29999999, -29999998, 131125, -30000000, 4, 327771, (s32)evt_npc_set_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54",
    -30000000, -29999999, -29999998, 65546, 20, 6, 109, 65546,
    300, 131122, -50000000, 0, 107, 65546, 100, 327771,
    (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131125, -30000000, 110,
    131125, -29999999, 70, 131126, -29999998, 90, 327771, (s32)evt_msg_toge,
    3, -30000000, -29999999, -29999998, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_63",
    0, 0, 65546, 750, 109, 107, 65546, 100,
    327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131125, -30000000,
    70, 131126, -29999999, 90, 131126, -29999998, 90, 327771,
    (s32)evt_msg_toge, 3, -30000000, -29999999, -29999998, 327771, (s32)evt_msg_print, 0,
    (s32)"stg4_jin_64", 0, 0, 65546, 750, 109, 107, 65546,
    250, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131125,
    -30000000, 30, 131125, -29999999, 30, 131126, -29999998, 90,
    327771, (s32)evt_msg_toge, 3, -30000000, -29999999, -29999998, 327771, (s32)evt_msg_print,
    0, (s32)"stg4_jin_65", 0, 0, 65546, 750, 109, 107,
    65546, 200, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998,
    131126, -30000000, 40, 131126, -29999999, 20, 131126, -29999998,
    90, 327771, (s32)evt_msg_toge, 3, -30000000, -29999999, -29999998, 327771,
    (s32)evt_msg_print, 0, (s32)"stg4_jin_64", 0, 0, 65546, 750, 109,
    107, 65546, 300, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999,
    -29999998, 131126, -30000000, 80, 131126, -29999999, 100, 131126,
    -29999998, 90, 327771, (s32)evt_msg_toge, 3, -30000000, -29999999, -29999998,
    327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_65", 0, 0, 65546, 750,
    109, 107, 65546, 150, 327771, (s32)evt_mario_get_pos, 0, -30000000,
    -29999999, -29999998, 131126, -30000000, 105, 131125, -29999999, 75,
    131126, -29999998, 90, 327771, (s32)evt_msg_toge, 3, -30000000, -29999999,
    -29999998, 327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_63", 0, 0, 65546,
    750, 109, 327771, (s32)evt_npc_get_position, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", -30000000, -29999999, -29999998,
    196699, (s32)evt_npc_set_battle_info, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", 7, 131163, (s32)evt_npc_battle_start, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", 65627,
    (s32)evt_npc_wait_battle_end, 131125, -29999999, 50, 589915, (s32)evt_item_entry, (s32)"item_99", 326,
    -30000000, -29999999, -29999998, 4, -129997758, 0, 196699, (s32)evt_item_flag_on,
    (s32)"item_99", 256, 131122, -129997758, 1, 65627, (s32)senteresa_huttobu, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)/*"アトミックテレサ"*/"\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54", 128, 65541, 0, 131157, -30000000,
    (s32)g_nNumEndProc, 131096, -30000000, 200, 131122, -50000000, 1, 7,
    33, 65545, 1, 6, 65546, 300, 65627, (s32)senteresa_end,
    131163, (s32)evt_mario_key_onoff, 1, 131122, -129997774, 1, 2, 1,
};

EVT_BEGIN(jin_00_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -500, 260, -200, 0, 0)
    IF_INT_LESS(GSW(0), 194)
        SET_VALUE(LW(0), PTR(bero_entry_data))
        CALL(evt_bero_get_info)
        SPAWN_EVENT(PTR(first_jin00))
        ELSE
        SET_VALUE(LW(0), PTR(bero_entry_data))
        CALL(evt_bero_get_info)
        CALL_CHILD(PTR(evt_bero_info_run))
    END_IF
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_LESS(GSW(0), 198)
        CALL(evt_item_entry, STRING("key00"), 22, -555, 200, 190, 0, -1, PTR(evt_key))
    END_IF
    IF_INT_LESS(GSW(0), 199)
        CALL(evt_mobj_lock, STRING("mobj_lock00"), 22, -435, 210, -245, 0, PTR(lock_item_check), PTR(evt_unlock), GSWF(2228))
        SET_VALUE(LW(0), STRING("n_bero_2"))
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    SET_VALUE(GW(0), -1)
    SET_VALUE(GW(1), -1)
    IF_INT_EQUAL(GSW(0), 196)
        SPAWN_EVENT(PTR(tyuou_teresa_kusukusu))
        SPAWN_EVENT(PTR(tyuou_teresa_look_mario))
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(0), 197)
        IF_INT_EQUAL(GSWF(2226), 0)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                WAIT_MS(1000)
                SPAWN_EVENT(PTR(senteresa_evt))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(2226), 0)
        CALL(evt_npc_check_delete, STRING("テレサ１"))
        CALL(evt_npc_check_delete, STRING("テレサ２"))
        CALL(evt_npc_check_delete, STRING("テレサ３"))
        CALL(evt_npc_check_delete, STRING("テレサ４"))
        CALL(evt_npc_check_delete, STRING("テレサ５"))
        CALL(evt_npc_check_delete, STRING("テレサ８"))
    END_IF
    CALL(evt_hit_bind_mapobj, STRING("a_oki01"), STRING("oki01"))
    IF_INT_LESS(GSW(0), 195)
        SET_VALUE(GW(10), 0)
        CALL(evt_run_case_evt, 10, 1, STRING("A_dai"), 0, PTR(push_evt), 0)
        CALL(evt_run_case_evt, 11, 1, STRING("A_dai"), 0, PTR(nopush_evt), 0)
        ELSE
        CALL(evt_mapobj_trans, 1, STRING("oki01"), FLOAT(50.0f), 0, 0)
        CALL(evt_hit_bind_update, STRING("a_oki01"))
        CALL(evt_hitobj_onoff, STRING("a_futa"), 0, 0)
    END_IF
    CALL(evt_map_playanim, STRING("hikari"), 1, 0)
    IF_INT_EQUAL(GSW(0), 201)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_off))
        CALL(evt_bero_overwrite, STRING("w_bero"), PTR(bero_stg4majo3nin))
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(PTR(bero_case_switch_on))
    END_IF
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("e_bero_2"))
        CALL(evt_cam_road_reset)
    END_IF
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("a_futa"), 4)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("hahen"), 2)
    RETURN
EVT_END()

USER_FUNC(senteresa_turiageru) {
    s32 n = extGetPoseNum();
    s32 i;

    g_nNumEndProc[0] = 0;
    for (i = 0; i < n; i++) {
        if (pTeresa[i].seq == 6) {
            pTeresa[i].seq = 80;
        } else if (pTeresa[i].seq != 9) {
            pTeresa[i].wait = 99999;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_end) {
    extReset();
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_wait_end_seq) {
    return g_nNumEndProc[0] == 200 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(senteresa_get_rot_center) {
    s32* args = event->args;

    evtSetValue(event, args[0], g_vecRotCenter.x);
    evtSetValue(event, args[1], g_vecRotCenter.y);
    evtSetValue(event, args[2], g_vecRotCenter.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_mario_spd) {
    MarioWork* mp = marioGetPtr();
    f32 scale = (20 - g_nNumHarituku[0]) / 20.0f;

    if (mp->currMotionId == 1) {
        mp->baseSpeed = mp->mBaseWalkSpeed * scale;
    } else if (mp->currMotionId == 2) {
        mp->baseSpeed = mp->mBaseDashSpeed * scale;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(teresa_eff) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effTeresaEntry(0, x, y + 20.0f, z + 20.0f);
    return EVT_RETURN_DONE;
}

