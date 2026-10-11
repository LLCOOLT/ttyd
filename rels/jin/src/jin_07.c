#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/extdrv.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
void extLoadShadowMtx(Mtx mtx);
void extLoadShadowRenderMode(void);
void extLoadShadowVertex(void);
void extLoadShadowTev(void);
void extDrawShadow(void);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
static void senteresa_ext_disp(CameraId camera, void* param);
typedef struct Teresa { Vec pos; Vec dst; f32 t; f32 field_0x1C; f32 field_0x20; f32 field_0x24; s32 wait; u8 state; } Teresa;
static Teresa* pTeresa;
static s32 g_nNumEndProc[1];
s32 g_nNumOutBox[1];
void computePosHermite(ExtPose* pose, Teresa* ter);
f32 randf(f32 min, f32 max);
int rand(void);
double cos(double x);
static inline f32 cosf(f32 x) { return cos(x); }

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_cam_shift_reset);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_set_bound_rate);
USER_FUNC(evt_item_set_gravity);
USER_FUNC(evt_item_set_jump_power);
USER_FUNC(evt_item_set_move_dir_speed);
USER_FUNC(evt_item_status_on);
USER_FUNC(evt_kagemario_init_14_text_4DB8);
USER_FUNC(evt_map_replace_mapobj);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_party_get_pos);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(senteresa_okure_move);
USER_FUNC(senteresa_okure_move_init);
USER_FUNC(senteresa_get_position);
static void senteresa_ext_shadow_disp(void);
static void senteresa_ext_disp(CameraId camera, void* param);
static void senteresa_ext_dispent(void);
static void senteresa_ext_main(void);
void computePosHermite(ExtPose* pose, Teresa* ter);
static f32 computePos(f32 a, f32 b, f32 t);
static void senteresa_ext_init(void);
static f32 randf(f32 min, f32 max);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_usu_kagemario_party_kill_14_data_AF00[];

__declspec(section ".data") u64 fd_jin_07_negone_one_374;
__declspec(section ".data") s32 fd_jin_07_neg_one_382[1];
__declspec(section ".data") s32 fd_jin_07___local_PI_383[1];
__declspec(section ".data") s32 fd_jin_07___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jin_07_one_negone_373;
__declspec(section ".data") s32 fd_jin_07___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jin_07_one_381[1];
__declspec(section ".data") u64 fd_jin_07_negone_one_360;
__declspec(section ".data") s32 fd_jin_07_neg_one_365[1];
__declspec(section ".data") s32 fd_jin_07___local_PI_366[1];
__declspec(section ".data") s32 fd_jin_07___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jin_07_one_negone_359;
__declspec(section ".data") s32 fd_jin_07___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jin_07_one_364[1];
static __declspec(section ".data") s32 w_close[12];
static __declspec(section ".data") s32 w_open[12];
static __declspec(section ".data") s32 e_close[12];
static __declspec(section ".data") s32 e_open[12];
s32 jin_07_juyo_oumu_vivian[59];
static s32 check_roll[16];
static s32 bero_entry_data[60];
s32 evt_locked[14];
static __declspec(section ".data") s32 evt_unlock[7];
static s32 npcEnt[46];
static s32 senteresa_ext_entry_data[15];
s32 evt_teresa_box_open[576];
s32 jin_07_init_evt[151];

__declspec(section ".data") u64 fd_jin_07_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_07_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_07___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_07___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_07_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_07___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_07_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jin_07_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jin_07_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jin_07___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jin_07___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jin_07_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jin_07___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jin_07_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(w_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door08"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(w_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door08"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door06"), 0, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(e_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door06"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_07_juyo_oumu_vivian)
    IF_INT_NOT_EQUAL(LSWF(1), 0)
        SET_VALUE(LSWF(1), 0)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_seq_wait, 2)
        CALL(evt_bero_exec_wait, 65536)
        CALL(evt_party_stop, 0)
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_cam3d_evt_set, -214, 129, 454, -214, 57, 48, 500, 11)
        WAIT_MS(500)
        CALL(evt_msg_print_party, STRING("stg4_jin_46"))
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(500)
        CALL(evt_msg_print_party, STRING("stg4_jin_47"))
        CALL(evt_cam3d_evt_off, 1000, 11)
        CALL(evt_party_run, 0)
        CALL(evt_mario_key_onoff, 1)
    END_IF
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

static s32 bero_entry_data[] = {
    (s32)"w_bero_2", 0, 20000, 100000, 0, 0, -1, 0,
    -1, (s32)check_roll, (s32)"jin_08", (s32)"e_bero_2", 65537, 0, 0, (s32)"w_bero_1",
    65538, 20000, 100000, 0, 0, 70, 0, -1,
    0, (s32)"jin_08", (s32)"e_bero_1", 327685, (s32)w_close, (s32)w_open, (s32)"e_bero", 65538,
    20000, 100000, 0, 0, -1, 0, -1, 0,
    (s32)"jin_06", (s32)"w_bero", 327685, (s32)e_close, (s32)e_open, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(evt_locked)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg4_jin_48"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(evt_unlock)
    SET_VALUE(LW(0), STRING("w_bero_1"))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"テレサ"*/"\x83\x65\x83\x8C\x83\x54", 1073743392, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static s32 senteresa_ext_entry_data[] = {
    (s32)"c_teresa", (s32)"W_1", 1065353216, (s32)"c_teresa", (s32)"W_1", 1073741824, (s32)"c_teresa", (s32)"W_1",
    1077936128, (s32)"c_teresa", (s32)"W_1", 1082130432, 0, 0, 0,
};

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

static void senteresa_ext_init(void) {
    ExtPose* pose = extGetPosePtr();
    s32 n = extGetPoseNum();
    s32 i;
    f32 a;
    f32 r;

    pTeresa = _mapAlloc(sizeof(Teresa) * 200);
    for (i = 0; i < n; i++, pose++) {
        pose->flags = 2;
        pose->rot = 270.0f;
        PSMTXIdentity(pose->mtx);
        pTeresa[i].pos.x = 0.0f;
        pose->mtx[0][3] = 0.0f;
        pTeresa[i].pos.y = 6.0f;
        pose->mtx[1][3] = 6.0f;
        pTeresa[i].pos.z = 80.0f;
        pose->mtx[2][3] = 80.0f;
        a = randf(0.0f, 360.0f);
        r = randf(10.0f, 30.0f);
        pTeresa[i].dst.x = 200.0f;
        pTeresa[i].dst.y = pTeresa[i].pos.y + randf(27.0f, 170.0f);
        pTeresa[i].dst.z = pTeresa[i].pos.z + r * cosf(a);
        pTeresa[i].field_0x1C = 0.0f;
        pTeresa[i].field_0x20 = randf(-0.1f, 0.1f);
        pTeresa[i].t = 0.0f;
        pTeresa[i].wait = 1.7f * (i + 1);
        pTeresa[i].state = 0;
        pTeresa[i].field_0x24 = randf(0.0f, 350.0f);
    }
    g_nNumOutBox[0] = 0;
    g_nNumEndProc[0] = 0;
}

static f32 computePos(f32 a, f32 b, f32 t) {
    return (1.0f - t) * a + t * b;
}

void computePosHermite(ExtPose* pose, Teresa* ter) {
    Vec m0 = {0.0f, 0.0f, 0.0f};
    Vec m1 = {1.0f, 0.0f, 0.0f};
    f32 t = ter->t;
    f32 u = 1.0f - t;
    f32 tt = t * t;
    f32 t2 = 2.0f * t;
    f32 h00 = (1.0f + t2) * u * u;
    f32 h10 = t * u * u;
    f32 h11 = (t - 1.0f) * tt;
    f32 h01 = (3.0f - t2) * tt;

    m0.x = ter->field_0x24;
    m0.y = 3.4f * ter->dst.y;
    pose->mtx[0][3] = ter->pos.x * h00 + m0.x * h10 + m1.x * h11 + ter->dst.x * h01;
    pose->mtx[1][3] = ter->pos.y * h00 + m0.y * h10 + m1.y * h11 + ter->dst.y * h01;
    pose->mtx[2][3] = ter->pos.z * h00 + m0.z * h10 + m1.z * h11 + ter->dst.z * h01;
}

static void senteresa_ext_main(void) {
    ExtPose* pose = extGetPosePtr();
    s32 n;
    s32 i;

    marioGetPtr();
    n = extGetPoseNum();
    for (i = 0; i < n; i++, pose++) {
        switch (pTeresa[i].state) {
            case 0:
                pose->frame = 0;
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    pose->flags |= 1;
                    g_nNumOutBox[0]++;
                    pTeresa[i].state++;
                }
                break;
            case 1:
                pose->frame = (gp->retraceCount + i * i) % 3 + 1;
                computePosHermite(pose, &pTeresa[i]);
                pTeresa[i].t += 0.015f;
                if (pTeresa[i].t >= 1.0f) {
                    pTeresa[i].pos.x = pose->mtx[0][3];
                    pTeresa[i].pos.y = pose->mtx[1][3];
                    pTeresa[i].pos.z = pose->mtx[2][3];
                    pTeresa[i].dst.x = 200.0f;
                    pTeresa[i].dst.y = pose->mtx[1][3];
                    pTeresa[i].dst.z = 50.0f;
                    pTeresa[i].t = 0.01f;
                    pTeresa[i].state = 99;
                    g_nNumEndProc[0]++;
                }
                break;
            case 99:
                break;
        }
    }
    if (g_nNumEndProc[0] == 200) {
        extReset();
    }
}

static void senteresa_ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, senteresa_ext_disp, NULL);
}

static void senteresa_ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
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

USER_FUNC(senteresa_get_position) {
    s32* args = event->args;
    ExtPose* pose = extGetPosePtr();

    pose += evtGetValue(event, args[0]);
    evtSetFloat(event, args[1], pose->mtx[0][3]);
    evtSetFloat(event, args[2], pose->mtx[1][3]);
    evtSetFloat(event, args[3], pose->mtx[2][3]);
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_okure_move_init) {
    s32* args = event->args;

    event->lwData[10] = evtGetValue(event, args[0]);
    event->lwData[11] = evtGetValue(event, args[1]);
    event->lwData[12] = evtGetValue(event, args[2]);
    event->lwData[13] = evtGetValue(event, args[3]);
    event->lwData[14] = evtGetValue(event, args[4]);
    event->lwData[15] = evtGetValue(event, args[5]);
    return EVT_RETURN_DONE;
}

USER_FUNC(senteresa_okure_move) {
    s32* args = event->args;
    NpcEntry* npc = npcNameToPtr("\203e\203\214\203T");
    f32 t = evtGetFloat(event, args[0]);
    Vec pos;
    Vec m0 = {0.0f, 250.0f, 0.0f};
    Vec m1 = {1.0f, 0.0f, 0.0f};
    f32 u = 1.0f - t;
    f32 t2 = 2.0f * t;
    f32 h00 = (1.0f + t2) * u * u;
    f32 h10 = t * u * u;
    f32 tt = (0, t * t);
    f32 h11 = (t - 1.0f) * tt;
    f32 h01 = (3.0f - t2) * tt;

    pos.x = event->lwData[10] * h00 + m0.x * h10 + m1.x * h11 + event->lwData[13] * h01;
    pos.y = event->lwData[11] * h00 + m0.y * h10 + m1.y * h11 + event->lwData[14] * h01;
    pos.z = event->lwData[12] * h00 + m0.z * h10 + m1.z * h11 + event->lwData[15] * h01;
    npc->position = pos;
    return EVT_RETURN_DONE;
}

EVT_BEGIN(evt_teresa_box_open)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envoff, 1024)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 1, 100, 400, 0, 38, 48, 500, 11)
    CALL(evt_mapobj_get_position, STRING("hako"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_BOX_SWING1"), LW(10), LW(11), LW(12), LW(13))
    LOOP(30)
        CALL(evt_sub_random, 3, LW(0))
        CALL(evt_mapobj_trans, 1, STRING("hako"), LW(0), 0, 0)
        WAIT_FRAMES(2)
        CALL(evt_sub_random, 3, LW(0))
        MULTIPLY(LW(0), -1)
        CALL(evt_mapobj_trans, 1, STRING("hako"), LW(0), 0, 0)
        WAIT_FRAMES(2)
    END_LOOP
    CALL(evt_snd_sfxoff, LW(13))
    CALL(evt_mapobj_trans, 1, STRING("hako"), 0, 0, 0)
    WAIT_MS(300)
    CALL(evt_mapobj_get_position, STRING("hako"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_TBOX_OPEN1"), LW(10), LW(11), LW(12), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 950, 50, 800)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, STRING("hako_futa"), LW(0), 0, 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(100)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 0, 175, 703, 0, 57, 26, 300, 4)
        WAIT_MS(350)
        CALL(evt_cam3d_evt_set, 0, 152, 567, 0, 57, 26, 250, 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_ext_entry, 200, PTR(senteresa_ext_entry_data), PTR(senteresa_ext_init), PTR(senteresa_ext_main), PTR(senteresa_ext_dispent))
    CALL(evt_snd_bgmoff, 1024)
    CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SURPRISED2"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_TELESA_APPEAR1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(500)
        CALL(evt_mario_set_pose, STRING("M_I_O"))
        WAIT_MS(5500)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_EQUAL(GF(0), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(0)
            PEEK_INT(LW(0), PTR(g_nNumEndProc))
            IF_INT_GREATER_OR_EQUAL(LW(0), 175)
                BREAK_LOOP
            END_IF
            PEEK_INT(LW(1), PTR(g_nNumOutBox))
            IF_INT_GREATER(LW(1), LW(0))
                CALL(evt_sub_random, 50, LW(1))
                ADD(LW(1), 30)
                CALL(evt_sub_random, LW(1), LW(0))
                CALL(evt_msg_toge, 3, LW(0), LW(1), 100)
                CALL(evt_sub_random, 1000, LW(0))
                MODULO(LW(0), 3)
                SWITCH(LW(0))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print, 0, STRING("stg4_jin_66"), 0, 0)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print, 0, STRING("stg4_jin_67"), 0, 0)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print, 0, STRING("stg4_jin_68"), 0, 0)
                END_SWITCH
            END_IF
            CALL(evt_sub_random, 200, LW(0))
            ADD(LW(0), 100)
            WAIT_MS(LW(0))
        END_LOOP
    END_INLINE_EVENT
    LOOP(0)
        PEEK_INT(LW(0), PTR(g_nNumEndProc))
        IF_INT_EQUAL(LW(0), 200)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1200)
    CALL(evt_npc_set_position, STRING("テレサ"), 0, 6, 80)
    CALL(evt_npc_set_ry, STRING("テレサ"), 90)
    CALL(evt_npc_flag_onoff, 0, STRING("テレサ"), 128)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(14), 0)
        SET_VALUE(LW(15), 0)
        LOOP(100)
            CALL(evt_npc_get_position, STRING("テレサ"), LW(0), LW(1), LW(2))
            CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
            CALL(evt_party_get_pos, 0, LW(6), LW(7), LW(8))
            IF_INT_GREATER(LW(0), LW(3))
                IF_INT_EQUAL(LW(14), 0)
                    CALL(evt_mario_set_dir, 90, 300, 0)
                    SET_VALUE(LW(14), 1)
                END_IF
            END_IF
            IF_INT_GREATER(LW(0), LW(6))
                IF_INT_EQUAL(LW(15), 0)
                    CALL(evt_party_set_dir, 0, 90, -1)
                    SET_VALUE(LW(15), 1)
                END_IF
            END_IF
            IF_INT_EQUAL(LW(14), 1)
                IF_INT_EQUAL(LW(15), 1)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(senteresa_okure_move_init, 0, 6, 80, 200, 30, 80)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("テレサ"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_TELESA_APPEAR1_2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    SET_VALUE(LF(0), 0)
    SET_FLOAT_VALUE(LW(9), FLOAT(0.0f))
    LOOP(70)
        CALL(senteresa_okure_move, LW(9))
        ADD_FLOAT(LW(9), FLOAT(0.0146484375f))
        CALL(evt_npc_get_position, STRING("テレサ"), LW(1), LW(2), LW(3))
        IF_INT_GREATER(LW(1), 75)
            IF_INT_EQUAL(LF(0), 0)
                SET_VALUE(LF(0), 1)
                WAIT_MS(300)
                CALL(evt_set_dir_to_target, STRING("テレサ"), STRING("mario"))
                CALL(evt_msg_print, 0, STRING("stg4_jin_69"), 0, STRING("テレサ"))
                CALL(evt_msg_select, 0, STRING("stg4_jin_69_yn"))
                SWITCH(LW(0))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print_add, 0, STRING("stg4_jin_71"))
                    SET_VALUE(LW(0), 121)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print_add, 0, STRING("stg4_jin_71"))
                    SET_VALUE(LW(0), 121)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print_add, 0, STRING("stg4_jin_70"))
                    SET_VALUE(LW(0), 150)
                END_SWITCH
                CALL(evt_item_entry, STRING("teresa"), LW(0), LW(1), LW(2), LW(3), 4, -1, 0)
                ADD(LW(2), 5)
                CALL(evt_item_set_move_dir_speed, STRING("teresa"), 0, FLOAT(0.0f))
                CALL(evt_item_set_gravity, STRING("teresa"), FLOAT(1.0f))
                CALL(evt_item_set_bound_rate, STRING("teresa"), FLOAT(1.0f))
                CALL(evt_item_set_jump_power, STRING("teresa"), FLOAT(100.0f))
                CALL(evt_item_status_on, STRING("teresa"), 16)
                CALL(evt_msg_print, 0, STRING("stg4_jin_72"), 0, STRING("テレサ"))
                CALL(evt_npc_reverse_ry, STRING("テレサ"))
                CALL(evt_npc_get_position, STRING("テレサ"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_TELESA_APPEAR1_2"), LW(0), LW(1), LW(2), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_position, STRING("テレサ"), 0, -1000, 0)
    CALL(evt_cam_shift_reset)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSW(0), 196)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envoff, 513)
    CALL(evt_snd_envon, 288, 0)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

EVT_BEGIN(jin_07_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG4_JIN3"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init_14_text_4DB8)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill_14_data_AF00))
    CALL(evt_npc_setup, PTR(npcEnt))
    SPAWN_EVENT(PTR(jin_07_juyo_oumu_vivian))
    CALL(evt_item_entry, STRING("item_00"), 125, 220, 75, -20, 16, GSWF(5636), 0)
    IF_INT_NOT_EQUAL(GSWF(2079), 0)
        SET_VALUE(GSWF(2079), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_key_onoff, 0)
            CALL(evt_mario_set_pos, 0, 365, -50)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(evt_party_set_pos, 0, 0, 465, -50)
            END_IF
            CALL(evt_cam_road_reset)
            CALL(evt_seq_wait, 2)
            CALL(evt_mario_wait_landon)
            CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
            CALL(evt_mario_key_onoff, 1)
        END_INLINE_EVENT
    END_IF
    IF_INT_EQUAL(GSWF(2231), 1)
        SET_VALUE(LW(0), STRING("w_bero_1"))
        CALL_CHILD(PTR(bero_case_switch_on))
        ELSE
        SET_VALUE(LW(0), STRING("w_bero_1"))
        CALL_CHILD(PTR(bero_case_switch_off))
    END_IF
    IF_INT_EQUAL(GSWF(2231), 0)
        CALL(evt_run_case_evt, 9, 1, STRING("w_bero_1"), 0, PTR(evt_locked), 0)
    END_IF
    IF_INT_LESS(GSW(0), 196)
        CALL(evt_mapobj_rotate, 1, STRING("hako_futa"), 95, 0, 0)
        CALL(evt_run_case_evt, 9, 1, STRING("a_hako"), 0, PTR(evt_teresa_box_open), 0)
        ELSE
        CALL(evt_mapobj_rotate, 1, STRING("hako_futa"), 5, 0, 0)
    END_IF
    CALL(evt_map_replace_mapobj, STRING("honou01"), 0)
    CALL(evt_map_replace_mapobj, STRING("honou02"), 0)
    CALL(evt_map_replace_mapobj, STRING("honou03"), 0)
    CALL(evt_map_replace_mapobj, STRING("honou04"), 0)
    RETURN
EVT_END()



