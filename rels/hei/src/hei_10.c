#pragma defer_codegen on
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "memory.h"
#include "string.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "system.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "stdlib.h"
#include "driver/dispdrv.h"
#include "driver/npcdrv.h"
#include "manager/evtmgr_cmd.h"
#include "driver/animdrv.h"
extern const char str_00001B38[];
extern const char str_00001B40[];
extern const char str_00001B48[];
extern const char str_00001B50[];
extern const char str_00001B58[];
extern const char str_00001B60[];
extern const char str_00001B68[];
extern const char str_00001B74[];
extern const char str_00001BC4[];
extern const char str_00001BD8[];
extern const char str_00001BF0[];
extern const char str_00001C08[];
extern const char str_00001C20[];
extern const char str_00001C28[];
extern const char str_00001C40[];
extern const char str_00001C48[];
extern const char str_00001C50[];
extern const char str_00001C5C[];
extern const char str_00001C7C[];
extern const char str_00001C84[];
extern const char str_00001C8C[];
extern const char str_00001CA0[];
extern const char str_00001CAC[];
extern const char str_00001CBC[];
extern const char str_00001CC0[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
typedef struct ChorobonWork { s32 field_0x0; s32 count; Chorobon* chb; } ChorobonWork;
u8 gap_05_00000004_bss[4];
static ChorobonWork* wp;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static f32 randf(f32 min, f32 max);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
void extLoadShadowMtx(Mtx mtx);
void extLoadShadowRenderMode(void);
void extLoadShadowVertex(void);
void extLoadShadowTev(void);
void extDrawShadow(void);
static inline f32 chb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = a * y; a = -a; } return a; }
static inline f32 chb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a; } return a; }
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
void extReset(void);

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_event_from_road);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_chorobon_escape);
USER_FUNC(evt_chorobon_wait);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mario_dispflag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_mario_wait_movable);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_npc_battle_start);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_jump_position);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_wait_battle_end);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfxon_3d);
static USER_FUNC(npc_jump);
USER_FUNC(wait_anim_end);
USER_FUNC(wait_anim_frame);
static void ext_dispent(void);
static void ext_main(void);
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_init(void);
static f32 randf(f32 min, f32 max);
extern s32 evt_bero_info_run[];
extern s32 hei_test_water_tev[];

__declspec(section ".data") u64 fd_hei_10_negone_one_374;
__declspec(section ".data") s32 fd_hei_10_neg_one_382[1];
__declspec(section ".data") s32 fd_hei_10___local_PI_383[1];
__declspec(section ".data") s32 fd_hei_10___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_hei_10_one_negone_373;
__declspec(section ".data") s32 fd_hei_10___local_PIO2_384[1];
__declspec(section ".data") s32 fd_hei_10_one_381[1];
__declspec(section ".data") u64 fd_hei_10_negone_one_360;
__declspec(section ".data") s32 fd_hei_10_neg_one_365[1];
__declspec(section ".data") s32 fd_hei_10___local_PI_366[1];
__declspec(section ".data") s32 fd_hei_10___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_hei_10_one_negone_359;
__declspec(section ".data") s32 fd_hei_10___local_PIO2_367[1];
__declspec(section ".data") s32 fd_hei_10_one_364[1];
static s32 bero_entry_data[60];
static s32 ext_data[63];
s32 golden_se[55];
s32 evt_golden[319];
s32 hei_10_init_evt[80];

int rand(void);

#ifdef NONMATCHING
static inline f32 rand01(void) {
    return rand() / 32767.0f;
}
#endif

#ifdef NONMATCHING
static inline f32 randf_scale(f32 r, f32 min, f32 max) {
    return r * (max - min) + min;
}
#endif

#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
#endif

#ifdef NONMATCHING
static void ext_init(void) {
    s32 i;
    ExtPose* pose;
    Chorobon* chb;

    wp = _mapAlloc(sizeof(ChorobonWork));
    memset(wp, 0, sizeof(ChorobonWork));
    wp->count = extGetPoseNum();
    wp->chb = _mapAlloc(wp->count * sizeof(Chorobon));
    memset(wp->chb, 0, wp->count * sizeof(Chorobon));
    pose = extGetPosePtr();
    chb = wp->chb;
    for (i = 0; i < wp->count; i++, pose++, chb++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-230.0f, 230.0f);
        pose->mtx[1][3] = -15.0f;
        pose->mtx[2][3] = randf(-100.0f, 100.0f);
        chb->flags = 0;
        chb->state = 0;
        chb->field_0x4 = 0;
    }
}
#endif

#ifdef NONMATCHING
static void ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}
#endif

__declspec(section ".data") u64 fd_hei_10_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_10_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_10___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_10___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_10_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_10___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_10_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_hei_10_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_hei_10_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_hei_10___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_hei_10___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_hei_10_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_hei_10___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_hei_10_one_364[] = {
    1065353216,
};

static s32 bero_entry_data[] = {
    (s32)((char*)str_00001B38), 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00001B40), (s32)((char*)str_00001B48), 65537, 0, 0, (s32)((char*)str_00001B48),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00001B50), (s32)((char*)str_00001B38), 65537, 0, 0, (s32)((char*)str_00001B58), 131072,
    6, 100000, 0, 0, -1, 0, 10, 0,
    (s32)((char*)str_00001B60), (s32)((char*)str_00001B58), 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 ext_data[] = {
    (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 0, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1073741824, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74),
    1082130432, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1086324736, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1090519040, (s32)((char*)str_00001B68),
    (s32)((char*)str_00001B74), 1092616192, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1094713344, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1096810496,
    (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1098907648, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1099956224, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74),
    1101004800, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1102053376, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1103101952, (s32)((char*)str_00001B68),
    (s32)((char*)str_00001B74), 1104150528, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1105199104, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1106247680,
    (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1107296256, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1107820544, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74),
    1108344832, (s32)((char*)str_00001B68), (s32)((char*)str_00001B74), 1108869120, 0, 0, 0,
};

#ifdef NONMATCHING
static void ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };

    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
}
#endif

#ifdef NONMATCHING
void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    f32 dy;
    f32 dist;
    f32 angle;

    chb->target = (Vec){x, y, z};
    chb->speed = speed;
    chb->gravity = gravity;
    dy = chb->target.y - pose->mtx[1][3];
    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
    chb->timer = dist / chb->speed;
    chb->vy = dy / chb->timer + chb->gravity * chb->timer / 2;
    chb->state = 100;
    chb->next = next;
}
#endif
static inline void jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 rs, f32 smin, f32 smax, f32 rg, f32 gmin, f32 gmax) { chb_jump(pose, chb, next, x, y, z, rs * (smax - smin) + smin, rg * (gmax - gmin) + gmin); } static inline void escape(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 rs, f32 smin, f32 smax, f32 rg, f32 gmin, f32 gmax) { chb_jump(pose, chb, next, x, y, z, 2.0f * (rs * (smax - smin) + smin), rg * (gmax - gmin) + gmin); }
#pragma push
#pragma opt_lifetimes off
#pragma opt_dead_assignments off
#ifdef NONMATCHING
static void ext_main(void) {
    MarioWork* mario = marioGetPtr();
    const char* sfx;
    s32 i;
    ExtPose* pose;
    Chorobon* chb;
    f32 dist;
    f32 speed;
    f32 x;
    f32 z;
    f32 gravity;
    f32 angle;
    f32 y;
    Vec pos;

    pose = extGetPosePtr();
    chb = wp->chb;
    sfx = (0, "SFX_STG1_CHORO_ESCAPE1");
    for (i = 0; i < wp->count; i++, pose++, chb++) {
        switch (chb->state) {
            case 0: {
                f32 z, speed, gravity, dist, x, y;
                x = rand() / 32767.0f;
                dist = randf(4.0f, 7.0f);
                {
                    f32 rad = 3.1415927f * randf_scale(x, 0.0f, 360.0f) / 180.0f;
                    x = pose->mtx[0][3] + chb_sin(rad) * dist;
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - dist * chb_cos(rad);
                }
                speed = rand() / 32767.0f;
                gravity = rand01();
                jump(pose, chb, chb->state, x, y, z, speed, 0.3f, 0.5f, gravity, 0.5f, 0.8f);
                break;
            }
            case 1:
                if (distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]) < 800.0f) {
                    speed = rand() / 32767.0f;
                    z = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
                    z = z + randf_scale(speed, -45.0f, 45.0f);
                    dist = randf(15.0f, 20.0f);
                    {
                        f32 rad = 3.1415927f * z / 180.0f;
                        x = pose->mtx[0][3] + chb_sin(rad) * dist;
                        y = pose->mtx[1][3];
                        z = pose->mtx[2][3] - dist * chb_cos(rad);
                    }
                    speed = rand() / 32767.0f;
                    gravity = rand01();
                    escape(pose, chb, chb->state, x, y, z, speed, 1.0f, 1.2f, gravity, 0.8f, 0.8f);
                    if (rand() % 150 == 0) {
                        pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
                        psndSFXOn_3D(sfx, &pos);
                    }
                } else {
                    chb->state = 99;
                }
                break;
            case 99:
                break;
            case 100:
                pose->mtx[1][3] += chb->vy;
                chb->vy -= chb->gravity;
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
                {
                    f32 rad = 3.1415927f * angle / 180.0f;
                    pose->mtx[0][3] += chb->speed * chb_sin(rad);
                    pose->mtx[2][3] += chb->speed * -chb_cos(rad);
                }
                if (--chb->timer < 0) {
                    pose->mtx[0][3] = chb->target.x;
                    pose->mtx[1][3] = chb->target.y;
                    pose->mtx[2][3] = chb->target.z;
                    chb->state = chb->next;
                }
                break;
        }
        switch (chb->state) {
            case 0:
                if (pose->mtx[0][3] > 230.0f) {
                    pose->mtx[0][3] = 230.0f;
                }
                if (pose->mtx[0][3] < -230.0f) {
                    pose->mtx[0][3] = -230.0f;
                }
                if (pose->mtx[2][3] > 100.0f) {
                    pose->mtx[2][3] = 100.0f;
                }
                if (pose->mtx[2][3] < -100.0f) {
                    pose->mtx[2][3] = -100.0f;
                }
                break;
            case 1:
                break;
        }
        if (gp->retraceCount & 1) {
            pose->frame = (gp->retraceCount + i) % 20;
        }
    }
}
#endif
#pragma pop

/* unused in the original build; only its Vec template survives in .rodata */
#ifdef NONMATCHING
static inline void chb_zero(Vec* v) {
    *v = (Vec){0.0f, 0.0f, 0.0f};
}
#endif

#ifdef NONMATCHING
static void ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
}
#endif

#ifdef NONMATCHING
s32 evt_chorobon_escape(EventEntry* event, BOOL isFirstCall) {
    ExtPose* pose = extGetPosePtr();
    s32 i;
    Chorobon* chb = wp->chb;

    for (i = 0; i < wp->count; i++, chb++) {
        chb->state = 1;
        chb->next = 1;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 evt_chorobon_wait(EventEntry* event, BOOL isFirstCall) {
    ExtPose* pose = extGetPosePtr();
    Chorobon* chb = wp->chb;
    s32 i;

    for (i = 0; i < wp->count; i++, chb++) {
        if (chb->state != 99) {
            return EVT_RETURN_BLOCK;
        }
    }
    extReset();
    return EVT_RETURN_DONE;
}
#endif


#ifdef NONMATCHING
static inline s32 npc_jump_get_time(EventEntry* event, s32* args) {
    return evtGetValue(event, args[6]);
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 speed = evtGetFloat(event, args[4]);
    f32 gravity = evtGetFloat(event, args[5]);
    f32 t = 60.0f * (f32)npc_jump_get_time(event, args) / 1000.0f;
    NpcEntry* npc = npcNameToPtr(name);
    f32 vy;
    f32 dist;
    f32 dy;
    f32 angle;

    if (isFirstCall) {
        static const Vec va = {0.0f, 0.0f, 0.0f};
        static const Vec vb = {0.0f, 0.0f, 0.0f};
        Vec a;
        Vec b;

        b = vb; b.x = npc->position.x; b.z = npc->position.z;
        a = va; a.x = x; a.z = z;
        dist = PSVECDistance(&a, &b);
        dy = y - npc->position.y;
        if (t == 0.0f) {
            t = dist / speed;
        } else {
            speed = dist / t;
        }
        vy = dy / t + gravity * t / 2.0f;
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&speed;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    speed = event->userdataf[2];
    angle = 6.2831855f * angleABf(npc->position.x, npc->position.z, x, z) / 360.0f;
    npc->position.x = speed * chb_sin(angle) + npc->position.x;
    npc->position.z = npc->position.z - speed * chb_cos(angle);
    npc->position.y += vy;
    vy -= gravity;
    t -= 1.0f;
    if (t < 0.0f) {
        npc->position = (Vec){x, y, z};
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return 0;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall) {
    f32 frame = evtGetFloat(event, *event->args);
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203\173\203\223");

    if (animPoseGetAnimPosePtr(npc->poseId)->localFrame < frame) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 wait_anim_end(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203\173\203\223");

    if (isFirstCall) {
        event->lwData[15] = animPoseGetLoopTimes(npc->poseId);
    }
    if (event->lwData[15] == (s32)animPoseGetLoopTimes(npc->poseId)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
#endif

static Mtx fs_mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };
EVT_BEGIN(golden_se)
    LOOP(0)
        CALL(wait_anim_frame, 35)
        CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BD8)), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_frame, 50)
        CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BF0)), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_frame, 95)
        CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001C08)), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_end)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_golden)
    CALL(evt_npc_entry, STRING(((char*)str_00001C20)), STRING(((char*)str_00001B68)))
    CALL(evt_npc_set_position, STRING(((char*)str_00001C20)), 0, -1000, 0)
    SPAWN_EVENT_GET_ID(PTR(golden_se), LW(15))
    WAIT_FRAMES(10)
    CALL(evt_mario_wait_movable)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001C28)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_00001C40)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)str_00001C48)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 58, 227, 0, 5, -68, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00001C50)), 0, STRING(((char*)str_00001BC4)))
    WAIT_MS(300)
    CALL(evt_cam3d_event_from_road, 0, -15, 0, 0, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 500, 11)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 1000, 11)
    DELETE_EVENT(LW(15))
    CALL(evt_npc_set_anim, STRING(((char*)str_00001BC4)), STRING(((char*)str_00001B74)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    DIVIDE_FLOAT(LW(0), FLOAT(4.0f))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00001BC4)), 131088)
    LOOP(3)
        ADD_FLOAT(LW(3), LW(0))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BD8)), LW(3), LW(1), LW(2), 0)
        CALL(evt_npc_jump_position, STRING(((char*)str_00001BC4)), LW(3), LW(1), LW(2), 300, 0, FLOAT(30.0f), 0)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00001BC4)), 1073741856)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 30)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001C5C)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00001C7C)))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING(((char*)str_00001BC4)), LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00001BD8)), LW(3), LW(4), LW(5), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00001BC4)), 131088)
    CALL(npc_jump, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(2), FLOAT(3.5f), FLOAT(2.0f), 0)
    CALL(evt_npc_battle_start, STRING(((char*)str_00001BC4)))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(((char*)str_00001C84)))
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00001C8C)))
    CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -15, 0)
    CALL(evt_ext_entry, 500, PTR(ext_data), PTR(ext_init), PTR(ext_main), PTR(ext_dispent))
    CALL(evt_msg_print, 0, STRING(((char*)str_00001CA0)), 0, STRING(((char*)str_00001BC4)))
    WAIT_MS(300)
    CALL(evt_chorobon_escape)
    CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -1000, 0)
    SET_VALUE(GSW(0), 32)
    CALL(evt_mario_key_onoff, 1)
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        SET_FLOAT_VALUE(LW(1), FLOAT(0.0f))
        SET_FLOAT_VALUE(LW(2), FLOAT(500.0f))
        DIVIDE_FLOAT(LW(2), FLOAT(40.0f))
        SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
        CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00001BC4)), 131088)
        LOOP(40)
            ADD_FLOAT(LW(3), LW(2))
            CALL(npc_jump, STRING(((char*)str_00001BC4)), LW(0), LW(1), LW(3), FLOAT(0.7998047f), FLOAT(1.0f), 0)
        END_LOOP
        CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_chorobon_wait)
    RETURN
EVT_END()

EVT_BEGIN(hei_10_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00001C8C)))
    CALL(evt_snd_envon, 272, STRING(((char*)str_00001CAC)))
    CALL(evt_snd_set_rev_mode, 1)
    CALL(evt_mobj_badgeblk, STRING(((char*)str_00001CBC)), 100, 46, -75, 241, 0, GSWF(1796), 1)
    CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -1000, 0)
    IF_INT_EQUAL(GSWF(1774), 1)
        IF_INT_EQUAL(GSWF(1775), 1)
            IF_INT_LESS(GSW(0), 32)
                CALL(evt_npc_set_position, STRING(((char*)str_00001BC4)), 0, -15, 0)
                CALL(evt_npc_change_fbat_mode, 1)
                SPAWN_EVENT(PTR(evt_golden))
            END_IF
        END_IF
    END_IF
    CALL(evt_map_playanim, STRING(((char*)str_00001CC0)), 1, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(hei_test_water_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00001CC0)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00001CC0)), 256)
    RETURN
EVT_END()

#pragma explicit_zero_data on
__declspec(section ".data") u32 gap_04_0000A464_data[1] = {0};
#pragma explicit_zero_data reset

#ifndef NONMATCHING
// ASM-STOPGAP: randf (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const char str_00001B38[] = "w_bero\000";
__declspec(section ".rodata") const char str_00001B40[] = "hei_09\000";
__declspec(section ".rodata") const char str_00001B48[] = "e_bero\000";
__declspec(section ".rodata") const char str_00001B50[] = "hei_11\000";
__declspec(section ".rodata") const char str_00001B58[] = "dokan\000\000";
__declspec(section ".rodata") const char str_00001B60[] = "hei_07\000";
__declspec(section ".rodata") const char str_00001B68[] = "c_chorobon\000";
__declspec(section ".rodata") const char str_00001B74[] = "CBN_W_1";
__declspec(section ".rodata") const f32 vec3_hei_00007a34[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_hei_00007a40[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_hei_00007a4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_hei_00007a58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_hei_00007a64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_hei_00007a70[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_00001BC4[] = "\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223\000";
__declspec(section ".rodata") const char str_00001BD8[] = "SFX_STG1_CHORO_MOVE1\000\000\000";
__declspec(section ".rodata") const char str_00001BF0[] = "SFX_STG1_CHORO_G_WAIT2\000";
__declspec(section ".rodata") const char str_00001C08[] = "SFX_STG1_CHORO_G_WAIT1\000";
__declspec(section ".rodata") const char str_00001C20[] = "dummy\000\000";
__declspec(section ".rodata") const char str_00001C28[] = "SFX_VOICE_MARIO_FIND1_3";
__declspec(section ".rodata") const char str_00001C40[] = "eff0\000\000\000";
__declspec(section ".rodata") const char str_00001C48[] = "eff1\000\000\000";
__declspec(section ".rodata") const char str_00001C50[] = "stg1_hei_42";
__declspec(section ".rodata") const char str_00001C5C[] = "SFX_VOICE_MARIO_SURPRISED2_2\000\000\000";
__declspec(section ".rodata") const char str_00001C7C[] = "M_N_7\000\000";
__declspec(section ".rodata") const char str_00001C84[] = "M_S_1\000\000";
__declspec(section ".rodata") const char str_00001C8C[] = "BGM_STG1_TORIDE1\000\000\000";
__declspec(section ".rodata") const char str_00001CA0[] = "stg1_hei_44";
__declspec(section ".rodata") const char str_00001CAC[] = "ENV_STG1_HEI3\000\000";
__declspec(section ".rodata") const char str_00001CBC[] = "m\000\000";
__declspec(section ".rodata") const char str_00001CC0[] = "mizu\000\000\000";
__declspec(section ".rodata") const f32 float_60_hei_00007b80[1] = { 60.0f };
__declspec(section ".rodata") const f32 float_1000_hei_00007b84[1] = { 1000.0f };
__declspec(section ".rodata") const f32 zero_hei_00007b88[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_0p5_hei_00007b8c[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_6p2832_hei_00007b90[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_360_hei_00007b94[1] = { 360.0f };
__declspec(section ".rodata") const f32 float_0p00761_hei_00007b98[1] = { 0.00761f };
__declspec(section ".rodata") const f32 float_0p16605_hei_00007b9c[1] = { 0.16605f };
__declspec(section ".rodata") const f32 float_1_hei_00007ba0[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_3p1416_hei_00007ba4[1] = { 3.1415927f };
__declspec(section ".rodata") const f32 float_1p5708_hei_00007ba8[1] = { 1.5707964f };
__declspec(section ".rodata") const f32 float_4p7124_hei_00007bac[1] = { 4.712389f };
__declspec(section ".rodata") const f32 float_0p03705_hei_00007bb0[1] = { 0.03705f };
__declspec(section ".rodata") const f32 float_0p4967_hei_00007bb4[1] = { 0.4967f };
__declspec(section ".rodata") const f64 double_to_int_hei_00007bb8 = 4503601774854144;
__declspec(section ".rodata") const char str_00001D08[] = "SFX_STG1_CHORO_ESCAPE1\000";
__declspec(section ".rodata") const f32 float_32767_hei_00007bd8[1] = { 32767.0f };
__declspec(section ".rodata") const f32 float_4_hei_00007bdc[1] = { 4.0f };
__declspec(section ".rodata") const f32 float_3_hei_00007be0[1] = { 3.0f };
__declspec(section ".rodata") const f32 float_180_hei_00007be4[1] = { 180.0f };
__declspec(section ".rodata") const f32 float_0p3_hei_00007be8[1] = { 0.3f };
__declspec(section ".rodata") const f32 float_0p2_hei_00007bec[1] = { 0.19999999f };
__declspec(section ".rodata") const f32 float_800_hei_00007bf0[1] = { 800.0f };
__declspec(section ".rodata") const f32 float_neg45_hei_00007bf4[1] = { -45.0f };
__declspec(section ".rodata") const f32 float_90_hei_00007bf8[1] = { 90.0f };
__declspec(section ".rodata") const f32 float_15_hei_00007bfc[1] = { 15.0f };
__declspec(section ".rodata") const f32 float_5_hei_00007c00[1] = { 5.0f };
__declspec(section ".rodata") const f32 float_2_hei_00007c04[1] = { 2.0f };
__declspec(section ".rodata") const f32 float_0p2_hei_00007c08[1] = { 0.20000005f };
__declspec(section ".rodata") const f32 float_0p8_hei_00007c0c[1] = { 0.8f };
__declspec(section ".rodata") const f32 float_230_hei_00007c10[1] = { 230.0f };
__declspec(section ".rodata") const f32 float_neg230_hei_00007c14[1] = { -230.0f };
__declspec(section ".rodata") const f32 float_100_hei_00007c18[1] = { 100.0f };
__declspec(section ".rodata") const f32 float_neg100_hei_00007c1c[1] = { -100.0f };
__declspec(section ".rodata") const f32 float_460_hei_00007c20[1] = { 460.0f };
__declspec(section ".rodata") const f32 float_neg15_hei_00007c24[1] = { -15.0f };
__declspec(section ".rodata") const f32 float_200_hei_00007c28[1] = { 200.0f };
__declspec(section ".rodata") const u32 gap_03_00001D74_rodata[1] = { 0x00000000 };
#pragma force_active reset

// FAKE: whole-unit asm stopgap (C under NONMATCHING); data in target order, force_active, gaps
asm s32 wait_anim_end(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r5, str_00001BC4@ha
	stw r0, 0x24(r1)
	stmw r30, 0x18(r1)
	mr r30, r3
	addi r3, r5, str_00001BC4@l
	mr r31, r4
	bl npcNameToPtr
	cmpwi r31, 0x0
	mr r31, r3
	beq L_at1
	lwz r3, 0x104(r31)
	bl animPoseGetLoopTimes
	fctiwz f0, f1
	stfd f0, 0x8(r1)
	lwz r0, 0xc(r1)
	stw r0, 0xd8(r30)
	L_at1:
	lwz r3, 0x104(r31)
	bl animPoseGetLoopTimes
	fctiwz f0, f1
	lwz r0, 0xd8(r30)
	stfd f0, 0x8(r1)
	lwz r3, 0xc(r1)
	cmpw r0, r3
	bne L_at2
	li r3, 0x0
	b L_at3
	L_at2:
	li r3, 0x2
	L_at3:
	lmw r30, 0x18(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x10(r1)
	psq_st f31, 0x18(r1), 0, 0
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetFloat
	fmr f31, f1
	lis r3, str_00001BC4@ha
	addi r3, r3, str_00001BC4@l
	bl npcNameToPtr
	lwz r3, 0x104(r3)
	bl animPoseGetAnimPosePtr
	lfs f0, 0x24(r3)
	fcmpo cr0, f0, f31
	bge L_at1
	li r3, 0x0
	b L_at2
	L_at1:
	li r3, 0x2
	L_at2:
	psq_l f31, 0x18(r1), 0, 0
	lwz r0, 0x24(r1)
	lfd f31, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stfd f28, 0x50(r1)
	psq_st f28, 0x58(r1), 0, 0
	stmw r28, 0x40(r1)
	mr r30, r3
	mr r28, r4
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r29, r3
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x10(r31)
	mr r3, r30
	bl evtGetFloat
	stfs f1, 0x10(r1)
	mr r3, r30
	lwz r4, 0x14(r31)
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x18(r31)
	mr r3, r30
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_hei_00007bb8@ha
	stw r3, 0x3c(r1)
	addi r3, r4, double_to_int_hei_00007bb8@l
	lis r4, float_60_hei_00007b80@ha
	stw r0, 0x38(r1)
	addi r5, r4, float_60_hei_00007b80@l
	lfd f1, 0x0(r3)
	lis r3, float_1000_hei_00007b84@ha
	lfd f0, 0x38(r1)
	addi r4, r3, float_1000_hei_00007b84@l
	lfs f2, 0x0(r5)
	mr r3, r29
	fsubs f1, f0, f1
	lfs f0, 0x0(r4)
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0xc(r1)
	bl npcNameToPtr
	cmpwi r28, 0x0
	mr r31, r3
	beq L_at1
	lis r3, vec3_hei_00007a64@ha
	lis r4, vec3_hei_00007a58@ha
	addi r7, r3, vec3_hei_00007a64@l
	addi r3, r1, 0x2c
	lwz r6, 0x0(r7)
	addi r5, r4, vec3_hei_00007a58@l
	lwz r0, 0x4(r7)
	addi r4, r1, 0x20
	lwz r7, 0x8(r7)
	stw r6, 0x20(r1)
	lwz r6, 0x0(r5)
	stw r0, 0x24(r1)
	lwz r0, 0x8(r5)
	stw r7, 0x28(r1)
	lwz r5, 0x4(r5)
	lfs f0, 0x8c(r31)
	stfs f0, 0x20(r1)
	lfs f0, 0x94(r31)
	stw r6, 0x2c(r1)
	stw r0, 0x34(r1)
	stfs f0, 0x28(r1)
	stw r5, 0x30(r1)
	stfs f29, 0x2c(r1)
	stfs f28, 0x34(r1)
	bl PSVECDistance
	lis r3, zero_hei_00007b88@ha
	lfs f2, 0x90(r31)
	lfs f3, 0xc(r1)
	lfs f0, zero_hei_00007b88@l(r3)
	fsubs f4, f30, f2
	fcmpu cr0, f0, f3
	mfcr r0
	extrwi. r0, r0, 1, 2
	beq L_at2
	lfs f0, 0x10(r1)
	fdivs f0, f1, f0
	stfs f0, 0xc(r1)
	L_at2:
	cmpwi r0, 0x0
	bne L_at3
	fdivs f0, f1, f3
	stfs f0, 0x10(r1)
	L_at3:
	lfs f2, 0xc(r1)
	lis r3, float_0p5_hei_00007b8c@ha
	lwz r0, 0xc(r1)
	fdivs f0, f4, f2
	lfs f1, float_0p5_hei_00007b8c@l(r3)
	stw r0, 0x78(r30)
	lwz r0, 0x10(r1)
	fmuls f2, f31, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x8(r1)
	lwz r3, 0x8(r1)
	stw r3, 0x7c(r30)
	stw r0, 0x80(r30)
	L_at1:
	lfs f1, 0x78(r30)
	fmr f3, f29
	lfs f2, 0x7c(r30)
	fmr f4, f28
	lfs f0, 0x80(r30)
	stfs f1, 0xc(r1)
	lfs f1, 0x8c(r31)
	stfs f2, 0x8(r1)
	lfs f2, 0x94(r31)
	stfs f0, 0x10(r1)
	bl angleABf
	lis r3, float_6p2832_hei_00007b90@ha
	lis r6, float_0p00761_hei_00007b98@ha
	addi r5, r3, float_6p2832_hei_00007b90@l
	lis r4, float_360_hei_00007b94@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_hei_00007b9c@ha
	lis r3, float_3p1416_hei_00007ba4@ha
	lfs f4, float_0p00761_hei_00007b98@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_hei_00007b94@l(r4)
	lfs f1, float_3p1416_hei_00007ba4@l(r3)
	lis r4, float_1_hei_00007ba0@ha
	lfs f3, float_0p16605_hei_00007b9c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_hei_00007ba0@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne L_at4
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne L_at5
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b L_at6
	L_at5:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b L_at6
	L_at4:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f5, f0
	bge L_at7
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b L_at6
	L_at7:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	L_at6:
	lis r3, float_3p1416_hei_00007ba4@ha
	lfs f2, 0x10(r1)
	lfs f1, float_3p1416_hei_00007ba4@l(r3)
	lis r4, float_0p4967_hei_00007bb4@ha
	lfs f0, 0x8c(r31)
	lis r5, float_0p03705_hei_00007bb0@ha
	fcmpo cr0, f5, f1
	lis r3, float_1_hei_00007ba0@ha
	fmadds f0, f2, f4, f0
	lfs f4, float_0p03705_hei_00007bb0@l(r5)
	lfs f3, float_0p4967_hei_00007bb4@l(r4)
	lfs f2, float_1_hei_00007ba0@l(r3)
	stfs f0, 0x8c(r31)
	cror eq, lt, eq
	bne L_at8
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne L_at9
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b L_at10
	L_at9:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at10
	L_at8:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f5, f0
	bge L_at11
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at10
	L_at11:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	L_at10:
	lfs f1, 0x10(r1)
	lis r3, float_1_hei_00007ba0@ha
	lfs f0, 0x94(r31)
	addi r4, r3, float_1_hei_00007ba0@l
	lfs f3, 0x8(r1)
	lis r3, zero_hei_00007b88@ha
	fnmsubs f4, f1, f4, f0
	lfs f1, 0xc(r1)
	fsubs f2, f3, f31
	lfs f0, 0x0(r4)
	stfs f4, 0x94(r31)
	fsubs f1, f1, f0
	lfs f0, zero_hei_00007b88@l(r3)
	lfs f4, 0x90(r31)
	stfs f2, 0x8(r1)
	fcmpo cr0, f1, f0
	fadds f2, f4, f3
	stfs f1, 0xc(r1)
	stfs f2, 0x90(r31)
	bge L_at12
	lis r4, vec3_hei_00007a70@ha
	li r3, 0x1
	addi r5, r4, vec3_hei_00007a70@l
	lwz r0, 0x0(r5)
	lwz r4, 0x4(r5)
	stw r0, 0x14(r1)
	lwz r0, 0x8(r5)
	stw r4, 0x18(r1)
	stfs f29, 0x14(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x14(r1)
	stfs f30, 0x18(r1)
	stfs f28, 0x1c(r1)
	lwz r4, 0x18(r1)
	stw r0, 0x8c(r31)
	lwz r0, 0x1c(r1)
	stw r4, 0x90(r31)
	stw r0, 0x94(r31)
	b L_at13
	L_at12:
	lwz r4, 0xc(r1)
	li r3, 0x0
	lwz r0, 0x8(r1)
	stw r4, 0x78(r30)
	stw r0, 0x7c(r30)
	L_at13:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	lmw r28, 0x40(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm s32 evt_chorobon_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extGetPosePtr
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	lwz r3, 0x8(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble L_at1
	L_at2:
	lha r0, 0x2(r3)
	cmpwi r0, 0x63
	beq L_at3
	li r3, 0x0
	b L_at4
	L_at3:
	addi r3, r3, 0x30
	bdnz L_at2
	L_at1:
	bl extReset
	li r3, 0x2
	L_at4:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_chorobon_escape(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extGetPosePtr
	lis r3, wp@ha
	li r6, 0x0
	addi r5, r3, wp@l
	li r4, 0x1
	lwz r3, 0x0(r5)
	lwz r7, 0x8(r3)
	b L_at1
	L_at2:
	sth r4, 0x2(r7)
	addi r6, r6, 0x1
	sth r4, 0x24(r7)
	addi r7, r7, 0x30
	L_at1:
	lwz r3, 0x0(r5)
	lwz r0, 0x4(r3)
	cmpw r6, r0
	blt L_at2
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_dispent(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, zero_hei_00007b88@ha
	lis r4, ext_disp@ha
	addi r6, r3, zero_hei_00007b88@l
	stw r0, 0x14(r1)
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_main(void) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stfd f30, 0xa0(r1)
	psq_st f30, 0xa8(r1), 0, 0
	stfd f29, 0x90(r1)
	psq_st f29, 0x98(r1), 0, 0
	stfd f28, 0x80(r1)
	psq_st f28, 0x88(r1), 0, 0
	stmw r24, 0x60(r1)
	bl marioGetPtr
	mr r29, r3
	bl extGetPosePtr
	lis r5, wp@ha
	lis r4, str_00001D08@ha
	addi r30, r5, wp@l
	mr r25, r3
	lwz r5, 0x0(r30)
	addi r27, r4, str_00001D08@l
	lis r4, gp@ha
	li r26, 0x0
	lwz r24, 0x8(r5)
	addi r31, r4, gp@l
	b L_at1
	L_at2:
	lha r0, 0x2(r24)
	cmpwi r0, 0x63
	beq L_at3
	bge L_at4
	cmpwi r0, 0x1
	beq L_at5
	bge L_at3
	cmpwi r0, 0x0
	bge L_at6
	b L_at3
	L_at4:
	cmpwi r0, 0x65
	bge L_at3
	b L_at7
	L_at6:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x3c(r1)
	lis r4, double_to_int_hei_00007bb8@ha
	lis r3, float_32767_hei_00007bd8@ha
	lfd f2, double_to_int_hei_00007bb8@l(r4)
	stw r0, 0x38(r1)
	lfs f0, float_32767_hei_00007bd8@l(r3)
	lfd f1, 0x38(r1)
	fsubs f1, f1, f2
	fdivs f30, f1, f0
	bl rand
	lis r5, float_360_hei_00007b94@ha
	lis r4, zero_hei_00007b88@ha
	lfs f1, float_360_hei_00007b94@l(r5)
	xoris r6, r3, 0x8000
	lfs f0, zero_hei_00007b88@l(r4)
	lis r0, 0x4330
	lis r3, float_3p1416_hei_00007ba4@ha
	lis r5, double_to_int_hei_00007bb8@ha
	addi r4, r3, float_3p1416_hei_00007ba4@l
	stw r6, 0x44(r1)
	addi r6, r5, double_to_int_hei_00007bb8@l
	lfs f2, 0x0(r4)
	stw r0, 0x40(r1)
	fmadds f0, f30, f1, f0
	lfd f4, 0x0(r6)
	lis r3, float_180_hei_00007be4@ha
	lfd f3, 0x40(r1)
	lis r5, float_32767_hei_00007bd8@ha
	fmuls f1, f2, f0
	lfs f0, float_180_hei_00007be4@l(r3)
	fsubs f4, f3, f4
	lfs f3, float_32767_hei_00007bd8@l(r5)
	lis r4, float_3_hei_00007be0@ha
	fdivs f8, f1, f0
	addi r7, r4, float_3_hei_00007be0@l
	lis r3, float_4_hei_00007bdc@ha
	addi r6, r3, float_4_hei_00007bdc@l
	lis r5, float_0p00761_hei_00007b98@ha
	lis r4, float_0p16605_hei_00007b9c@ha
	fdivs f3, f4, f3
	lis r3, float_1_hei_00007ba0@ha
	lfs f1, 0x0(r7)
	lfs f0, 0x0(r6)
	lfs f6, float_0p00761_hei_00007b98@l(r5)
	lfs f5, float_0p16605_hei_00007b9c@l(r4)
	fcmpo cr0, f8, f2
	lfs f4, float_1_hei_00007ba0@l(r3)
	fmadds f7, f3, f1, f0
	cror eq, lt, eq
	bne L_at8
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f8, f1
	cror eq, lt, eq
	bne L_at9
	fmuls f0, f8, f8
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f8
	b L_at10
	L_at9:
	fsubs f0, f8, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f1
	b L_at10
	L_at8:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f8, f0
	bge L_at11
	fsubs f1, f8, f2
	fmuls f0, f1, f1
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f1
	fneg f6, f6
	b L_at10
	L_at11:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f8, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f1
	fneg f6, f6
	L_at10:
	lwz r6, 0xc(r25)
	lis r3, float_3p1416_hei_00007ba4@ha
	lfs f1, float_3p1416_hei_00007ba4@l(r3)
	lis r5, float_0p03705_hei_00007bb0@ha
	lfs f0, 0xc(r6)
	lis r4, float_0p4967_hei_00007bb4@ha
	fcmpo cr0, f8, f1
	lis r3, float_1_hei_00007ba0@ha
	fmadds f30, f7, f6, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_hei_00007bb0@l(r5)
	lfs f3, float_0p4967_hei_00007bb4@l(r4)
	lfs f2, float_1_hei_00007ba0@l(r3)
	cror eq, lt, eq
	bne L_at12
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f8, f1
	cror eq, lt, eq
	bne L_at13
	fmuls f0, f8, f8
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b L_at14
	L_at13:
	fsubs f0, f8, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at14
	L_at12:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f8, f0
	bge L_at15
	fsubs f0, f8, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at14
	L_at15:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f8, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	L_at14:
	lfs f0, 0x2c(r6)
	fnmsubs f28, f7, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x44(r1)
	lis r4, double_to_int_hei_00007bb8@ha
	lis r3, float_32767_hei_00007bd8@ha
	lfd f2, double_to_int_hei_00007bb8@l(r4)
	stw r0, 0x40(r1)
	lfs f0, float_32767_hei_00007bd8@l(r3)
	lfd f1, 0x40(r1)
	fsubs f1, f1, f2
	fdivs f29, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_hei_00007bb8@ha
	stw r3, 0x3c(r1)
	addi r5, r4, double_to_int_hei_00007bb8@l
	lis r3, float_32767_hei_00007bd8@ha
	stw r0, 0x38(r1)
	addi r4, r3, float_32767_hei_00007bd8@l
	lfd f2, 0x0(r5)
	lis r3, vec3_hei_00007a34@ha
	lfd f1, 0x38(r1)
	addi r6, r3, vec3_hei_00007a34@l
	lfs f0, 0x0(r4)
	lis r4, float_0p2_hei_00007bec@ha
	fsubs f1, f1, f2
	lwz r5, 0x0(r6)
	lwz r0, 0x4(r6)
	lis r3, float_0p3_hei_00007be8@ha
	stw r5, 0x14(r1)
	addi r5, r4, float_0p2_hei_00007bec@l
	fdivs f3, f1, f0
	stw r0, 0x18(r1)
	addi r4, r3, float_0p3_hei_00007be8@l
	lwz r0, 0x8(r6)
	stfs f30, 0x14(r1)
	lis r3, float_0p5_hei_00007b8c@ha
	stw r0, 0x1c(r1)
	lha r28, 0x2(r24)
	stfs f31, 0x18(r1)
	lwz r6, 0x14(r1)
	stfs f28, 0x1c(r1)
	lwz r0, 0x18(r1)
	stw r6, 0x8(r24)
	lfs f1, 0x0(r5)
	lfs f2, 0x0(r4)
	stw r0, 0xc(r24)
	lwz r0, 0x1c(r1)
	fmadds f1, f29, f1, f2
	lfs f0, float_0p5_hei_00007b8c@l(r3)
	stw r0, 0x10(r24)
	fmadds f0, f3, f2, f0
	stfs f1, 0x1c(r24)
	stfs f0, 0x20(r24)
	lwz r3, 0xc(r25)
	lfs f2, 0xc(r24)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f29, f2, f0
	lfs f2, 0x2c(r3)
	lfs f3, 0x8(r24)
	lfs f4, 0x10(r24)
	bl distABf
	lwz r3, 0xc(r25)
	fmr f30, f1
	lfs f3, 0x8(r24)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r24)
	bl angleABf
	lfs f0, 0x1c(r24)
	lis r4, 0x4330
	lis r3, float_0p5_hei_00007b8c@ha
	lis r5, double_to_int_hei_00007bb8@ha
	fdivs f0, f30, f0
	lfs f1, float_0p5_hei_00007b8c@l(r3)
	stw r4, 0x58(r1)
	li r0, 0x64
	lfd f3, double_to_int_hei_00007bb8@l(r5)
	stw r4, 0x50(r1)
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r3, 0x4c(r1)
	sth r3, 0x18(r24)
	lha r3, 0x18(r24)
	lfs f4, 0x20(r24)
	xoris r3, r3, 0x8000
	stw r3, 0x5c(r1)
	lfd f0, 0x58(r1)
	stw r3, 0x54(r1)
	fsubs f0, f0, f3
	lfd f2, 0x50(r1)
	fdivs f0, f29, f0
	fsubs f2, f2, f3
	fmuls f2, f4, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x14(r24)
	sth r0, 0x2(r24)
	sth r28, 0x24(r24)
	b L_at3
	L_at5:
	lwz r3, 0xc(r25)
	lfs f1, 0x8c(r29)
	lfs f2, 0x94(r29)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl distABf
	lis r3, float_800_hei_00007bf0@ha
	lfs f0, float_800_hei_00007bf0@l(r3)
	fcmpo cr0, f1, f0
	bge L_at16
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x5c(r1)
	lis r4, double_to_int_hei_00007bb8@ha
	lis r3, float_32767_hei_00007bd8@ha
	lwz r5, 0xc(r25)
	stw r0, 0x58(r1)
	lfd f2, double_to_int_hei_00007bb8@l(r4)
	lfd f1, 0x58(r1)
	lfs f0, float_32767_hei_00007bd8@l(r3)
	fsubs f4, f1, f2
	lfs f1, 0x8c(r29)
	lfs f2, 0x94(r29)
	lfs f3, 0xc(r5)
	fdivs f29, f4, f0
	lfs f4, 0x2c(r5)
	bl angleABf
	lis r4, float_90_hei_00007bf8@ha
	lis r3, float_neg45_hei_00007bf4@ha
	lfs f2, float_90_hei_00007bf8@l(r4)
	lfs f0, float_neg45_hei_00007bf4@l(r3)
	fmadds f0, f29, f2, f0
	fadds f28, f1, f0
	bl rand
	xoris r4, r3, 0x8000
	lis r0, 0x4330
	lis r3, float_3p1416_hei_00007ba4@ha
	lis r5, double_to_int_hei_00007bb8@ha
	lfs f2, float_3p1416_hei_00007ba4@l(r3)
	addi r6, r5, double_to_int_hei_00007bb8@l
	stw r4, 0x54(r1)
	lis r3, float_180_hei_00007be4@ha
	lis r4, float_32767_hei_00007bd8@ha
	lfd f4, 0x0(r6)
	stw r0, 0x50(r1)
	addi r5, r4, float_32767_hei_00007bd8@l
	lfs f0, float_180_hei_00007be4@l(r3)
	fmuls f1, f2, f28
	lfd f3, 0x50(r1)
	lis r4, float_5_hei_00007c00@ha
	lis r3, float_15_hei_00007bfc@ha
	fsubs f4, f3, f4
	lfs f3, 0x0(r5)
	fdivs f8, f1, f0
	addi r7, r4, float_5_hei_00007c00@l
	addi r6, r3, float_15_hei_00007bfc@l
	lis r5, float_0p00761_hei_00007b98@ha
	lis r4, float_0p16605_hei_00007b9c@ha
	lfs f1, 0x0(r7)
	fdivs f3, f4, f3
	lfs f0, 0x0(r6)
	lis r3, float_1_hei_00007ba0@ha
	lfs f6, float_0p00761_hei_00007b98@l(r5)
	lfs f5, float_0p16605_hei_00007b9c@l(r4)
	lfs f4, float_1_hei_00007ba0@l(r3)
	fcmpo cr0, f8, f2
	fmadds f7, f3, f1, f0
	cror eq, lt, eq
	bne L_at17
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f8, f1
	cror eq, lt, eq
	bne L_at18
	fmuls f0, f8, f8
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f8
	b L_at19
	L_at18:
	fsubs f0, f8, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f1
	b L_at19
	L_at17:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f8, f0
	bge L_at20
	fsubs f1, f8, f2
	fmuls f0, f1, f1
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f1
	fneg f6, f6
	b L_at19
	L_at20:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f8, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fmuls f6, f6, f1
	fneg f6, f6
	L_at19:
	lwz r6, 0xc(r25)
	lis r3, float_3p1416_hei_00007ba4@ha
	lfs f1, float_3p1416_hei_00007ba4@l(r3)
	lis r5, float_0p03705_hei_00007bb0@ha
	lfs f0, 0xc(r6)
	lis r4, float_0p4967_hei_00007bb4@ha
	fcmpo cr0, f8, f1
	lis r3, float_1_hei_00007ba0@ha
	fmadds f31, f7, f6, f0
	lfs f30, 0x1c(r6)
	lfs f4, float_0p03705_hei_00007bb0@l(r5)
	lfs f3, float_0p4967_hei_00007bb4@l(r4)
	lfs f2, float_1_hei_00007ba0@l(r3)
	cror eq, lt, eq
	bne L_at21
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f8, f1
	cror eq, lt, eq
	bne L_at22
	fmuls f0, f8, f8
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b L_at23
	L_at22:
	fsubs f0, f8, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at23
	L_at21:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f8, f0
	bge L_at24
	fsubs f0, f8, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at23
	L_at24:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f8, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	L_at23:
	lfs f0, 0x2c(r6)
	fnmsubs f28, f7, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x5c(r1)
	lis r4, double_to_int_hei_00007bb8@ha
	lis r3, float_32767_hei_00007bd8@ha
	lfd f2, double_to_int_hei_00007bb8@l(r4)
	stw r0, 0x58(r1)
	lfs f0, float_32767_hei_00007bd8@l(r3)
	lfd f1, 0x58(r1)
	fsubs f1, f1, f2
	fdivs f29, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_hei_00007bb8@ha
	stw r3, 0x54(r1)
	addi r5, r4, double_to_int_hei_00007bb8@l
	lis r3, float_32767_hei_00007bd8@ha
	stw r0, 0x50(r1)
	addi r4, r3, float_32767_hei_00007bd8@l
	lfd f2, 0x0(r5)
	lis r3, vec3_hei_00007a34@ha
	lfd f1, 0x50(r1)
	addi r7, r3, vec3_hei_00007a34@l
	lfs f0, 0x0(r4)
	lis r4, float_0p2_hei_00007c08@ha
	fsubs f1, f1, f2
	lwz r5, 0x0(r7)
	lwz r0, 0x4(r7)
	addi r6, r4, float_0p2_hei_00007c08@l
	stw r5, 0x8(r1)
	lis r3, float_1_hei_00007ba0@ha
	fdivs f3, f1, f0
	stw r0, 0xc(r1)
	addi r5, r3, float_1_hei_00007ba0@l
	lwz r0, 0x8(r7)
	lis r3, float_2_hei_00007c04@ha
	stfs f31, 0x8(r1)
	stw r0, 0x10(r1)
	addi r7, r3, float_2_hei_00007c04@l
	lha r28, 0x2(r24)
	lis r4, zero_hei_00007b88@ha
	lwz r0, 0x8(r1)
	lis r3, float_0p8_hei_00007c0c@ha
	stfs f30, 0xc(r1)
	lfs f1, 0x0(r6)
	lfs f0, 0x0(r5)
	stw r0, 0x8(r24)
	lwz r0, 0xc(r1)
	fmadds f0, f29, f1, f0
	lfs f1, 0x0(r7)
	stfs f28, 0x10(r1)
	fmuls f2, f1, f0
	lfs f1, zero_hei_00007b88@l(r4)
	stw r0, 0xc(r24)
	lwz r0, 0x10(r1)
	lfs f0, float_0p8_hei_00007c0c@l(r3)
	stw r0, 0x10(r24)
	fmadds f0, f3, f1, f0
	stfs f2, 0x1c(r24)
	stfs f0, 0x20(r24)
	lwz r3, 0xc(r25)
	lfs f2, 0xc(r24)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f29, f2, f0
	lfs f2, 0x2c(r3)
	lfs f3, 0x8(r24)
	lfs f4, 0x10(r24)
	bl distABf
	lwz r3, 0xc(r25)
	fmr f30, f1
	lfs f3, 0x8(r24)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r24)
	bl angleABf
	lfs f0, 0x1c(r24)
	lis r4, 0x4330
	lis r3, float_0p5_hei_00007b8c@ha
	lis r5, double_to_int_hei_00007bb8@ha
	fdivs f0, f30, f0
	lfs f1, float_0p5_hei_00007b8c@l(r3)
	stw r4, 0x38(r1)
	li r0, 0x64
	lfd f3, double_to_int_hei_00007bb8@l(r5)
	stw r4, 0x40(r1)
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r3, 0x4c(r1)
	sth r3, 0x18(r24)
	lha r3, 0x18(r24)
	lfs f4, 0x20(r24)
	xoris r3, r3, 0x8000
	stw r3, 0x3c(r1)
	lfd f0, 0x38(r1)
	stw r3, 0x44(r1)
	fsubs f0, f0, f3
	lfd f2, 0x40(r1)
	fdivs f0, f29, f0
	fsubs f2, f2, f3
	fmuls f2, f4, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x14(r24)
	sth r0, 0x2(r24)
	sth r28, 0x24(r24)
	bl rand
	li r4, 0x96
	divw r0, r3, r4
	mullw r0, r0, r4
	subf. r0, r0, r3
	bne L_at3
	lis r3, vec3_hei_00007a40@ha
	lwz r5, 0xc(r25)
	addi r8, r3, vec3_hei_00007a40@l
	mr r3, r27
	lwz r7, 0x0(r8)
	addi r4, r1, 0x2c
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x20(r1)
	lfs f0, 0xc(r5)
	stw r6, 0x24(r1)
	lfs f1, 0x1c(r5)
	stfs f0, 0x20(r1)
	lfs f0, 0x2c(r5)
	stw r0, 0x28(r1)
	lwz r6, 0x20(r1)
	stfs f1, 0x24(r1)
	stfs f0, 0x28(r1)
	lwz r5, 0x24(r1)
	lwz r0, 0x28(r1)
	stw r6, 0x2c(r1)
	stw r5, 0x30(r1)
	stw r0, 0x34(r1)
	bl psndSFXOn_3D
	b L_at3
	L_at16:
	li r0, 0x63
	sth r0, 0x2(r24)
	b L_at3
	L_at7:
	lwz r3, 0xc(r25)
	lfs f0, 0x14(r24)
	lfs f1, 0x1c(r3)
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lfs f1, 0x14(r24)
	lfs f0, 0x20(r24)
	fsubs f0, f1, f0
	stfs f0, 0x14(r24)
	lwz r3, 0xc(r25)
	lfs f3, 0x8(r24)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r24)
	bl angleABf
	lis r4, float_3p1416_hei_00007ba4@ha
	lis r3, float_180_hei_00007be4@ha
	lfs f2, float_3p1416_hei_00007ba4@l(r4)
	addi r6, r3, float_180_hei_00007be4@l
	lis r5, float_0p00761_hei_00007b98@ha
	lis r4, float_0p16605_hei_00007b9c@ha
	fmuls f1, f2, f1
	lfs f0, 0x0(r6)
	lis r3, float_1_hei_00007ba0@ha
	lfs f5, float_0p00761_hei_00007b98@l(r5)
	lfs f4, float_0p16605_hei_00007b9c@l(r4)
	fdivs f6, f1, f0
	lfs f3, float_1_hei_00007ba0@l(r3)
	fcmpo cr0, f6, f2
	cror eq, lt, eq
	bne L_at25
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne L_at26
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f6
	b L_at27
	L_at26:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b L_at27
	L_at25:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f6, f0
	bge L_at28
	fsubs f1, f6, f2
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b L_at27
	L_at28:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	L_at27:
	lwz r7, 0xc(r25)
	lis r3, float_3p1416_hei_00007ba4@ha
	lfs f1, float_3p1416_hei_00007ba4@l(r3)
	lis r6, float_0p03705_hei_00007bb0@ha
	lfs f2, 0x1c(r24)
	lis r5, float_0p4967_hei_00007bb4@ha
	lfs f0, 0xc(r7)
	fcmpo cr0, f6, f1
	lis r4, float_1_hei_00007ba0@ha
	lfs f4, float_0p03705_hei_00007bb0@l(r6)
	fmadds f0, f2, f5, f0
	lfs f3, float_0p4967_hei_00007bb4@l(r5)
	lfs f2, float_1_hei_00007ba0@l(r4)
	stfs f0, 0xc(r7)
	cror eq, lt, eq
	bne L_at29
	lis r3, float_1p5708_hei_00007ba8@ha
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne L_at30
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b L_at31
	L_at30:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at31
	L_at29:
	lis r3, float_4p7124_hei_00007bac@ha
	lfs f0, float_4p7124_hei_00007bac@l(r3)
	fcmpo cr0, f6, f0
	bge L_at32
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b L_at31
	L_at32:
	lis r3, float_1p5708_hei_00007ba8@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_hei_00007ba8@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	L_at31:
	lwz r3, 0xc(r25)
	fneg f1, f4
	lfs f2, 0x1c(r24)
	lfs f0, 0x2c(r3)
	fmadds f0, f2, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0x18(r24)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x18(r24)
	bge L_at3
	lfs f0, 0x8(r24)
	lwz r3, 0xc(r25)
	stfs f0, 0xc(r3)
	lfs f0, 0xc(r24)
	lwz r3, 0xc(r25)
	stfs f0, 0x1c(r3)
	lfs f0, 0x10(r24)
	lwz r3, 0xc(r25)
	stfs f0, 0x2c(r3)
	lha r0, 0x24(r24)
	sth r0, 0x2(r24)
	L_at3:
	lha r0, 0x2(r24)
	cmpwi r0, 0x1
	beq L_at33
	bge L_at33
	cmpwi r0, 0x0
	bge L_at34
	b L_at33
	L_at34:
	lwz r4, 0xc(r25)
	lis r3, float_230_hei_00007c10@ha
	lfs f0, float_230_hei_00007c10@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	ble L_at35
	stfs f0, 0xc(r4)
	L_at35:
	lwz r4, 0xc(r25)
	lis r3, float_neg230_hei_00007c14@ha
	lfs f0, float_neg230_hei_00007c14@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	bge L_at36
	stfs f0, 0xc(r4)
	L_at36:
	lwz r4, 0xc(r25)
	lis r3, float_100_hei_00007c18@ha
	lfs f0, float_100_hei_00007c18@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	ble L_at37
	stfs f0, 0x2c(r4)
	L_at37:
	lwz r4, 0xc(r25)
	lis r3, float_neg100_hei_00007c1c@ha
	lfs f0, float_neg100_hei_00007c1c@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	bge L_at33
	stfs f0, 0x2c(r4)
	L_at33:
	lwz r3, 0x0(r31)
	lwz r3, 0x1c(r3)
	clrlwi. r0, r3, 31
	beq L_at38
	add r4, r3, r26
	li r3, 0x14
	divwu r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	stw r0, 0x10(r25)
	L_at38:
	addi r26, r26, 0x1
	addi r25, r25, 0x20
	addi r24, r24, 0x30
	L_at1:
	lwz r3, 0x0(r30)
	lwz r0, 0x4(r3)
	cmpw r26, r0
	blt L_at2
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	psq_l f30, 0xa8(r1), 0, 0
	lfd f30, 0xa0(r1)
	psq_l f29, 0x98(r1), 0, 0
	lfd f29, 0x90(r1)
	psq_l f28, 0x88(r1), 0, 0
	lfd f28, 0x80(r1)
	lmw r24, 0x60(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stmw r29, 0x34(r1)
	lis r6, vec3_hei_00007a34@ha
	mr r30, r4
	addi r4, r6, vec3_hei_00007a34@l
	mr r29, r3
	lwz r0, 0x0(r4)
	mr r31, r5
	lwz r3, 0x4(r4)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r4)
	stw r3, 0xc(r1)
	stfs f1, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f2, 0xc(r1)
	stfs f3, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x8(r30)
	lwz r0, 0x10(r1)
	stw r3, 0xc(r30)
	stw r0, 0x10(r30)
	stfs f4, 0x1c(r30)
	stfs f5, 0x20(r30)
	lwz r3, 0xc(r29)
	lfs f2, 0xc(r30)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f30, f2, f0
	lfs f2, 0x2c(r3)
	lfs f3, 0x8(r30)
	lfs f4, 0x10(r30)
	bl distABf
	lwz r3, 0xc(r29)
	fmr f31, f1
	lfs f3, 0x8(r30)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r30)
	bl angleABf
	lfs f0, 0x1c(r30)
	lis r4, 0x4330
	lis r3, float_0p5_hei_00007b8c@ha
	lis r5, double_to_int_hei_00007bb8@ha
	fdivs f0, f31, f0
	lfs f1, float_0p5_hei_00007b8c@l(r3)
	stw r4, 0x28(r1)
	li r0, 0x64
	lfd f3, double_to_int_hei_00007bb8@l(r5)
	stw r4, 0x20(r1)
	fctiwz f0, f0
	stfd f0, 0x18(r1)
	lwz r3, 0x1c(r1)
	sth r3, 0x18(r30)
	lha r3, 0x18(r30)
	lfs f4, 0x20(r30)
	xoris r3, r3, 0x8000
	stw r3, 0x2c(r1)
	lfd f0, 0x28(r1)
	stw r3, 0x24(r1)
	fsubs f0, f0, f3
	lfd f2, 0x20(r1)
	fdivs f0, f30, f0
	fsubs f2, f2, f3
	fmuls f2, f4, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x14(r30)
	sth r0, 0x2(r30)
	sth r31, 0x24(r30)
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	lmw r29, 0x34(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm static void ext_shadow_disp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, fs_mt@ha
	stw r0, 0x14(r1)
	addi r3, r3, fs_mt@l
	bl extLoadShadowMtx
	bl extLoadShadowRenderMode
	bl extLoadShadowVertex
	bl extLoadShadowTev
	bl extDrawShadow
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_disp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extLoadRenderMode
	bl extLoadVertex
	bl extLoadTexture
	bl extLoadTev
	bl extDraw
	bl extLoadTextureExit
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_init(void) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stfd f27, 0x50(r1)
	psq_st f27, 0x58(r1), 0, 0
	stfd f26, 0x40(r1)
	psq_st f26, 0x48(r1), 0, 0
	stfd f25, 0x30(r1)
	psq_st f25, 0x38(r1), 0, 0
	stmw r27, 0x1c(r1)
	li r3, 0xc
	bl _mapAlloc
	lis r5, wp@ha
	li r4, 0x0
	addi r6, r5, wp@l
	li r5, 0xc
	stw r3, 0x0(r6)
	bl memset
	bl extGetPoseNum
	lis r4, wp@ha
	addi r5, r4, wp@l
	lwz r4, 0x0(r5)
	stw r3, 0x4(r4)
	lwz r3, 0x0(r5)
	lwz r0, 0x4(r3)
	mulli r3, r0, 0x30
	bl _mapAlloc
	lis r5, wp@ha
	li r4, 0x0
	addi r6, r5, wp@l
	lwz r5, 0x0(r6)
	stw r3, 0x8(r5)
	lwz r3, 0x0(r6)
	lwz r0, 0x4(r3)
	lwz r3, 0x8(r3)
	mulli r5, r0, 0x30
	bl memset
	bl extGetPosePtr
	lis r4, wp@ha
	lis r10, double_to_int_hei_00007bb8@ha
	addi r31, r4, wp@l
	lis r9, float_32767_hei_00007bd8@ha
	lwz r11, 0x0(r31)
	lis r8, float_460_hei_00007c20@ha
	lis r7, float_neg230_hei_00007c14@ha
	lis r6, float_neg15_hei_00007c24@ha
	lis r5, float_200_hei_00007c28@ha
	lis r4, float_neg100_hei_00007c1c@ha
	lwz r28, 0x8(r11)
	mr r29, r3
	lfd f25, double_to_int_hei_00007bb8@l(r10)
	li r30, 0x0
	lfs f26, float_32767_hei_00007bd8@l(r9)
	lis r27, 0x4330
	lfs f27, float_460_hei_00007c20@l(r8)
	lfs f28, float_neg230_hei_00007c14@l(r7)
	lfs f29, float_neg15_hei_00007c24@l(r6)
	lfs f30, float_200_hei_00007c28@l(r5)
	lfs f31, float_neg100_hei_00007c1c@l(r4)
	b L_at1
	L_at2:
	lwz r0, 0x0(r29)
	ori r0, r0, 0x7
	stw r0, 0x0(r29)
	lwz r3, 0xc(r29)
	bl PSMTXIdentity
	bl rand
	xoris r0, r3, 0x8000
	stw r27, 0x8(r1)
	lwz r3, 0xc(r29)
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f25
	fdivs f0, f0, f26
	fmadds f0, f0, f27, f28
	stfs f0, 0xc(r3)
	lwz r3, 0xc(r29)
	stfs f29, 0x1c(r3)
	bl rand
	xoris r0, r3, 0x8000
	lwz r3, 0xc(r29)
	stw r0, 0x14(r1)
	li r0, 0x0
	addi r30, r30, 0x1
	addi r29, r29, 0x20
	stw r27, 0x10(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f25
	fdivs f0, f0, f26
	fmadds f0, f0, f30, f31
	stfs f0, 0x2c(r3)
	sth r0, 0x0(r28)
	sth r0, 0x2(r28)
	sth r0, 0x4(r28)
	addi r28, r28, 0x30
	L_at1:
	lwz r3, 0x0(r31)
	lwz r0, 0x4(r3)
	cmpw r30, r0
	blt L_at2
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	psq_l f27, 0x58(r1), 0, 0
	lfd f27, 0x50(r1)
	psq_l f26, 0x48(r1), 0, 0
	lfd f26, 0x40(r1)
	psq_l f25, 0x38(r1), 0, 0
	lfd f25, 0x30(r1)
	lmw r27, 0x1c(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm static f32 randf(f32 min, f32 max) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	fmr f30, f1
	fmr f31, f2
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_hei_00007bb8@ha
	lis r3, float_32767_hei_00007bd8@ha
	lfd f3, double_to_int_hei_00007bb8@l(r4)
	stw r0, 0x8(r1)
	fsubs f0, f31, f30
	lfs f1, float_32767_hei_00007bd8@l(r3)
	lfd f2, 0x8(r1)
	fsubs f2, f2, f3
	fdivs f1, f2, f1
	fmadds f1, f1, f0, f30
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f30, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}
// clang-format on
#endif
#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset
