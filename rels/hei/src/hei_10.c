#pragma defer_codegen on
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

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
void PSMTXIdentity(Mtx m);
f32 PSVECDistance(const Vec* a, const Vec* b);
void* _mapAlloc(u32 size);
AnimationPose* animPoseGetAnimPosePtr(s32 poseId);
f32 animPoseGetLoopTimes(s32 id);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 evtGetFloat(EventEntry* entry, s32 index);
MarioWork* marioGetPtr(void);
void *memset(void *dest, int ch, size_t count);
NpcEntry* npcNameToPtr(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
typedef struct ChorobonWork { s32 field_0x0; s32 count; Chorobon* chb; } ChorobonWork;
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

s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_event_from_road(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_chorobon_escape(EventEntry* event, BOOL isFirstCall);
s32 evt_chorobon_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_tevcallback(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dispflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_wait_movable(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_badgeblk(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_battle_start(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_fbat_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_jump_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_wait_battle_end(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_set_rev_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
static s32 npc_jump(EventEntry* event, BOOL isFirstCall);
s32 wait_anim_end(EventEntry* event, BOOL isFirstCall);
s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall);
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

static inline f32 rand01(void) {
    return rand() / 32767.0f;
}

static inline f32 randf_scale(f32 r, f32 min, f32 max) {
    return r * (max - min) + min;
}

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

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

static void ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

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
    (s32)("w_bero"), 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)("hei_09"), (s32)("e_bero"), 65537, 0, 0, (s32)("e_bero"),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)("hei_11"), (s32)("w_bero"), 65537, 0, 0, (s32)("dokan"), 131072,
    6, 100000, 0, 0, -1, 0, 10, 0,
    (s32)("hei_07"), (s32)("dokan"), 65537, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static s32 ext_data[] = {
    (s32)("c_chorobon"), (s32)("CBN_W_1"), 0, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1073741824, (s32)("c_chorobon"), (s32)("CBN_W_1"),
    1082130432, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1086324736, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1090519040, (s32)("c_chorobon"),
    (s32)("CBN_W_1"), 1092616192, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1094713344, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1096810496,
    (s32)("c_chorobon"), (s32)("CBN_W_1"), 1098907648, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1099956224, (s32)("c_chorobon"), (s32)("CBN_W_1"),
    1101004800, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1102053376, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1103101952, (s32)("c_chorobon"),
    (s32)("CBN_W_1"), 1104150528, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1105199104, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1106247680,
    (s32)("c_chorobon"), (s32)("CBN_W_1"), 1107296256, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1107820544, (s32)("c_chorobon"), (s32)("CBN_W_1"),
    1108344832, (s32)("c_chorobon"), (s32)("CBN_W_1"), 1108869120, 0, 0, 0,
};

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
static inline void jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 rs, f32 smin, f32 smax, f32 rg, f32 gmin, f32 gmax) { chb_jump(pose, chb, next, x, y, z, rs * (smax - smin) + smin, rg * (gmax - gmin) + gmin); } static inline void escape(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 rs, f32 smin, f32 smax, f32 rg, f32 gmin, f32 gmax) { chb_jump(pose, chb, next, x, y, z, 2.0f * (rs * (smax - smin) + smin), rg * (gmax - gmin) + gmin); }
#pragma push
#pragma opt_lifetimes off
#pragma opt_dead_assignments off
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
#pragma pop

/* unused in the original build; only its Vec template survives in .rodata */
static inline void chb_zero(Vec* v) {
    *v = (Vec){0.0f, 0.0f, 0.0f};
}

static void ext_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
}

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

static inline s32 npc_jump_get_time(EventEntry* event, s32* args) {
    return evtGetValue(event, args[6]);
}

#pragma opt_propagation off
#pragma opt_lifetimes off
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
#pragma opt_propagation reset
#pragma opt_lifetimes reset

s32 wait_anim_frame(EventEntry* event, BOOL isFirstCall) {
    f32 frame = evtGetFloat(event, *event->args);
    NpcEntry* npc = npcNameToPtr("\203S\201[\203\213\203h\203`\203\207\203\215\203\173\203\223");

    if (animPoseGetAnimPosePtr(npc->poseId)->localFrame < frame) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

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

EVT_BEGIN(golden_se)
    LOOP(0)
        CALL(wait_anim_frame, 35)
        CALL(evt_npc_get_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(("SFX_STG1_CHORO_MOVE1")), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_frame, 50)
        CALL(evt_npc_get_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(("SFX_STG1_CHORO_G_WAIT2")), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_frame, 95)
        CALL(evt_npc_get_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(("SFX_STG1_CHORO_G_WAIT1")), LW(0), LW(1), LW(2), 0)
        CALL(wait_anim_end)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_golden)
    CALL(evt_npc_entry, STRING(("dummy")), STRING(("c_chorobon")))
    CALL(evt_npc_set_position, STRING(("dummy")), 0, -1000, 0)
    SPAWN_EVENT_GET_ID(PTR(golden_se), LW(15))
    WAIT_FRAMES(10)
    CALL(evt_mario_wait_movable)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(("SFX_VOICE_MARIO_FIND1_3")), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(("eff0")), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(("eff1")), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(evt_cam3d_evt_set, 0, 58, 227, 0, 5, -68, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(("stg1_hei_42")), 0, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")))
    WAIT_MS(300)
    CALL(evt_cam3d_event_from_road, 0, -15, 0, 0, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 500, 11)
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 1000, 11)
    DELETE_EVENT(LW(15))
    CALL(evt_npc_set_anim, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), STRING(("CBN_W_1")))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    DIVIDE_FLOAT(LW(0), FLOAT((4.0f)))
    SET_FLOAT_VALUE(LW(3), FLOAT((0.0f)))
    CALL(evt_npc_flag_onoff, 1, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 131088)
    LOOP(3)
        ADD_FLOAT(LW(3), LW(0))
        CALL(evt_snd_sfxon_3d, STRING(("SFX_STG1_CHORO_MOVE1")), LW(3), LW(1), LW(2), 0)
        CALL(evt_npc_jump_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(3), LW(1), LW(2), 300, 0, FLOAT(30.0f), 0)
    END_LOOP
    CALL(evt_npc_flag_onoff, 1, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 1073741856)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 30)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(("SFX_VOICE_MARIO_SURPRISED2_2")), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING(("M_N_7")))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(("SFX_STG1_CHORO_MOVE1")), LW(3), LW(4), LW(5), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 131088)
    CALL(npc_jump, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(0), LW(1), LW(2), FLOAT(3.5f), FLOAT((2.0f)), 0)
    CALL(evt_npc_battle_start, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING(("M_S_1")))
    CALL(evt_snd_bgmon, 512, STRING(("BGM_STG1_TORIDE1")))
    CALL(evt_npc_set_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 0, -15, 0)
    CALL(evt_ext_entry, 500, PTR(ext_data), PTR(ext_init), PTR(ext_main), PTR(ext_dispent))
    CALL(evt_msg_print, 0, STRING(("stg1_hei_44")), 0, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")))
    WAIT_MS(300)
    CALL(evt_chorobon_escape)
    CALL(evt_npc_set_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 0, -1000, 0)
    SET_VALUE(GSW(0), 32)
    CALL(evt_mario_key_onoff, 1)
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
        SET_FLOAT_VALUE(LW(1), FLOAT((0.0f)))
        SET_FLOAT_VALUE(LW(2), FLOAT(500.0f))
        DIVIDE_FLOAT(LW(2), FLOAT(40.0f))
        SET_FLOAT_VALUE(LW(3), FLOAT((0.0f)))
        CALL(evt_npc_flag_onoff, 0, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 131088)
        LOOP(40)
            ADD_FLOAT(LW(3), LW(2))
            CALL(npc_jump, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), LW(0), LW(1), LW(3), FLOAT(0.7998047f), FLOAT((1.0f)), 0)
        END_LOOP
        CALL(evt_npc_set_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 0, -1000, 0)
    END_INLINE_EVENT
    CALL(evt_chorobon_wait)
    RETURN
EVT_END()

EVT_BEGIN(hei_10_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_snd_bgmon, 512, STRING(("BGM_STG1_TORIDE1")))
    CALL(evt_snd_envon, 272, STRING(("ENV_STG1_HEI3")))
    CALL(evt_snd_set_rev_mode, 1)
    CALL(evt_mobj_badgeblk, STRING(("m")), 100, 46, -75, 241, 0, GSWF(1796), 1)
    CALL(evt_npc_set_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 0, -1000, 0)
    IF_INT_EQUAL(GSWF(1774), 1)
        IF_INT_EQUAL(GSWF(1775), 1)
            IF_INT_LESS(GSW(0), 32)
                CALL(evt_npc_set_position, STRING(("\203S\201[\203\213\203h\203`\203\207\203\215\203{\203\223")), 0, -15, 0)
                CALL(evt_npc_change_fbat_mode, 1)
                SPAWN_EVENT(PTR(evt_golden))
            END_IF
        END_IF
    END_IF
    CALL(evt_map_playanim, STRING(("mizu")), 1, 0)
    CALL(evt_map_set_tevcallback, 1, PTR(hei_test_water_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(("mizu")), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(("mizu")), 256)
    RETURN
EVT_END()


