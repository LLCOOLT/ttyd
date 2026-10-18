// FAKE: whole unit as G5 asm stopgap; C under #ifdef NONMATCHING. Best pure C: 3/6 (effFallMain 99.15, effFallDispWater 99.35, effFallEntry 99.93).
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern double sin(double);
extern double cos(double);

typedef struct EffFallWork {
    s32 type;       // 0x0
    Vec position;   // 0x4
    u8 pad10[0x6C - 0x10];
    Vec pos2;       // 0x6C
    u8 pad78[0x80 - 0x78];
    f32 angle;      // 0x80
    u8 pad84[0x8C - 0x84];
    s32 timer;      // 0x8C
    u8 pad90[0x94 - 0x90];
    f32 scale;      // 0x94
    u8 pad98[0xA0 - 0x98];
    s32 state;      // 0xA0
    u32 alpha;      // 0xA4
    u8 padA8[0xB0 - 0xA8];
    f32 rotation;   // 0xB0
    u8 padB4[0xB8 - 0xB4];
    Vec pos3;       // 0xB8
    s32 pose0;      // 0xC4
    s32 pose1;      // 0xC8
} EffFallWork;

typedef struct EffFallVtx {
    f32 x, y, z;
    f32 u, v;
} EffFallVtx;

typedef struct EffFallElem {
    s32 type;         // 0x0
    Vec pos;          // 0x4
    f32 arg4;         // 0x10
    f32 arg5;         // 0x14
    f32 rotY;         // 0x18
    s32 arg7;         // 0x1C
    s32 arg8;         // 0x20
    s32 timer;        // 0x24
    s32 scroll;       // 0x28
    f32 scale;        // 0x2C
    f32 f30;          // 0x30
    f32 f34;          // 0x34
    s32 state;        // 0x38
    s32 alpha;        // 0x3C
    EffFallVtx** vtx; // 0x40
    f32 f44;          // 0x44
    f32 rot2;         // 0x48
    f32 rot3;         // 0x4C
    Vec vel;          // 0x50
    s32 pose0;        // 0x5C
    s32 pose1;        // 0x60
    s32 sfx;          // 0x64
} EffFallElem;

#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".data") f32 lbl_803ADD20[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_374[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_803ADD30[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_373[] = { 1.0f, -1.0f };
__declspec(section ".data") f32 lbl_803ADD40[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_360[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_803ADD50[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_359[] = { 1.0f, -1.0f };
static s16 shibuki_vertex_tbl[] = { -14012, 946, -2560, -7355, 946, -2560, -697, 946, -2560, 5959, 946, -2560, 12617, 946, -2560, -17337, 7417, -2560, -8130, 10717, -2560, -697, 12271, -2560, 6734, 10717, -2560, 15942, 7417, -2560, -23097, 11535, -2560, -11577, 18594, -2560, -697, 20431, -2560, 10822, 18594, -2560, 21702, 11535, -2560, -14777, 3888, -2560, -7591, 3922, -2560, -697, 3922, -2560, 6195, 3922, -2560, 13262, 3922, -2560, -19292, 8815, -2560, -9810, 14556, -2560, -697, 16241, -2560, 8831, 14757, -2560, 17896, 8815, -2560, -12537, 0, -3520, 262, 0, -3520, 13062, 0, -3520, -12537, 1702, -3520, 262, 4006, -3520, 13062, 1702, -3520, -12537, 4940, -3520, 262, 8012, -3520, 13062, 4940, -3520, 10533, 5964, -3520, 10439, 2726, -3520, 10468, 0, -3520, -10037, 5964, -3520, -10021, 2726, -3520, -10006, 0, -3520, 0, 0, 0, 0, 0, 0, 0, 0 };
static s16 shibuki_texcoord0_tbl[] = { 0, 12018, 4096, 12749, 4096, 14745, 0, 14745, 8192, 13023, 8192, 14745, 12288, 12749, 12288, 14745, 16384, 12018, 16384, 14745, 0, 1638, 4096, 1638, 4096, 4997, 0, 5968, 8192, 1638, 8192, 5003, 12288, 1638, 12288, 4830, 16384, 1638, 16384, 5968, 0, 8192, 4096, 8192, 8192, 8192, 12288, 8192, 16384, 8192, -3220, 8192, -16384, 8192, -16384, 16384, -3240, 16384, 13026, 8192, 16384, 16384, 13064, 16384, -3200, 0, -16384, 0, 13147, 0, 16384, 0, 0, 0, 0, 16384, 0, 0, 0, 0 };
static u8 shibuki_dl_0_0[] = { 0x98, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x0A, 0x0B, 0x00, 0x00, 0x0B, 0x14, 0x00, 0x00, 0x0D, 0x15, 0x00, 0x02, 0x0C, 0x05, 0x00, 0x00, 0x14, 0x06, 0x00, 0x03, 0x15, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_0_1[] = { 0x98, 0x00, 0x0A, 0x0B, 0x00, 0x00, 0x0B, 0x0C, 0x00, 0x00, 0x0E, 0x15, 0x00, 0x02, 0x0C, 0x16, 0x00, 0x02, 0x0F, 0x06, 0x00, 0x03, 0x15, 0x07, 0x00, 0x03, 0x16, 0x10, 0x00, 0x01, 0x01, 0x11, 0x00, 0x01, 0x04, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_0_2[] = { 0x98, 0x00, 0x0A, 0x0C, 0x00, 0x00, 0x0E, 0x0D, 0x00, 0x00, 0x10, 0x16, 0x00, 0x02, 0x0F, 0x17, 0x00, 0x02, 0x11, 0x07, 0x00, 0x03, 0x16, 0x08, 0x00, 0x03, 0x17, 0x11, 0x00, 0x01, 0x04, 0x12, 0x00, 0x01, 0x06, 0x02, 0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_0_3[] = { 0x98, 0x00, 0x0A, 0x0D, 0x00, 0x00, 0x10, 0x0E, 0x00, 0x00, 0x12, 0x17, 0x00, 0x02, 0x11, 0x18, 0x00, 0x00, 0x13, 0x08, 0x00, 0x03, 0x17, 0x09, 0x00, 0x00, 0x18, 0x12, 0x00, 0x01, 0x06, 0x13, 0x00, 0x00, 0x08, 0x03, 0x00, 0x00, 0x07, 0x04, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static s8 shibuki_normal_tbl[] = { 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static u8 shibuki_color0_tbl[] = { 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x19, 0xFF, 0xFF, 0xFF, 0x4C, 0xB6, 0xCC, 0xCB, 0x33, 0xB6, 0xCC, 0xCB, 0x4C, 0xB6, 0xCC, 0xCB, 0x99, 0xB6, 0xCC, 0xCB, 0x00 };
static u8 shibuki_dl_1_0[] = { 0x98, 0x00, 0x06, 0x1F, 0x00, 0x07, 0x24, 0x25, 0x00, 0x04, 0x20, 0x1C, 0x00, 0x07, 0x14, 0x26, 0x00, 0x04, 0x19, 0x19, 0x00, 0x07, 0x25, 0x27, 0x00, 0x06, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_1_1[] = { 0x98, 0x00, 0x06, 0x20, 0x00, 0x04, 0x24, 0x22, 0x00, 0x04, 0x22, 0x1D, 0x00, 0x05, 0x14, 0x23, 0x00, 0x04, 0x1D, 0x1A, 0x00, 0x06, 0x25, 0x24, 0x00, 0x06, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_1_2[] = { 0x98, 0x00, 0x06, 0x22, 0x00, 0x04, 0x22, 0x21, 0x00, 0x07, 0x23, 0x23, 0x00, 0x04, 0x1D, 0x1E, 0x00, 0x07, 0x18, 0x24, 0x00, 0x06, 0x1F, 0x1B, 0x00, 0x07, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00 };
static u8 shibuki_dl_1_3[] = { 0x98, 0x00, 0x06, 0x25, 0x00, 0x04, 0x20, 0x20, 0x00, 0x04, 0x21, 0x26, 0x00, 0x04, 0x19, 0x1D, 0x00, 0x05, 0x1A, 0x27, 0x00, 0x06, 0x1C, 0x1A, 0x00, 0x06, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00 };

USER_FUNC(evt_cam_shake);

static EVT_BEGIN(evt_shake)
    CALL(evt_cam_shake, 4, FLOAT(0.009765625f), FLOAT(0.009765625f), 300)
    RETURN
EVT_END()

s32 psndSFXOn_3D(const char* name, Vec* position);
void psndSFXOff(s32 id);
extern EffectEntry* effWaterDamageN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);
EffectEntry* effKemuri1N64Entry(s32 type, f32 a2, f32 a3, f32 a4, f32 a5);
void effFallMain(EffectEntry* effect);
void effFallDisp(CameraId cameraId, EffectEntry* effect);
void effFallDispInseki(CameraId cameraId, EffectEntry* effect);
void effFallDispWater(CameraId cameraId, EffectEntry* effect);

static inline f32 fall_sinf(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;

    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        }
        else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * y;
        }
    }
    else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    return a;
}

static inline f32 fall_cosf(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;

    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        }
        else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    }
    else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    }
    else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}

#ifdef NONMATCHING
EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8) {
    const char* sfxName;
    EffectEntry* effect;
    EffFallElem* e;
    s32 i;
    EffFallElem* w;
    s32 count;
    f32 a;
    f32 r;

    effect = effEntry();
    count = arg7 + 1;
    switch (type) {
    case 0:
        count = arg7 + 1;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        arg7 = 1;
        count = 2;
        break;
    }
    effect->type = "Fall";
    effect->count = count;
    w = __memAlloc(HEAP_EFFECT, effect->count * sizeof(EffFallElem));
    effect->userdata = w;
    effect->callback = effFallMain;
    effect->flags |= 2;
    sfxName = (0, "SFX_BTL_STAGE_FALL_WATER1\0\0");
    w->type = type;
    w->pos.x = x;
    w->pos.y = y;
    w->pos.z = z;
    w->arg4 = arg4;
    w->arg5 = arg5;
    w->rotY = arg6;
    w->arg7 = arg7;
    w->timer = 0;
    w->scroll = 0;
    w->arg8 = arg8;
    w->pose0 = -1;
    w->pose1 = -1;
    for (i = 1, e = w + 1; i < effect->count; i++, e++) {
        a = 3.1415927f * irand(360) / 180.0f;
        r = irand((s32)arg4);
        e->pos.x = r * (f32)sin(a);
        e->pos.y = 300.0f + irand(effect->count);
        e->pos.z = r * (f32)cos(a);
        e->timer = 0;
        e->scroll = 0;
        e->alpha = 255;
        e->rot2 = 0.0f;
        e->rotY = irand(100) > 50 ? 0 : 180;
        e->state = 0;
        e->pose0 = -1;
        e->pose1 = -1;
        switch (type) {
            case 0:
            case 1:
                e->f34 = 0.0f;
                e->f30 = 0.2f;
                if (i == 1) {
                    e->pos.x = 0.0f;
                    e->pos.z = 0.0f;
                    e->timer = 0;
                } else {
                    e->timer = irand(effect->count) + 60;
                }
                e->scale = type == 0 ? 0.5f : 1.2f;
                break;
            case 2:
                e->f34 = 0.0f;
                e->f30 = 1.6f;
                e->pos.x = 0.0f;
                e->pos.z = 0.0f;
                e->timer = 0;
                e->f44 = 0.0f;
                e->scale = 0.5f;
                break;
            case 3: {
                e->f34 = 0.0f;
                e->f30 = 0.1f;
                e->pos.x = 0.0f;
                e->pos.y = 200.0f;
                e->pos.z = 0.0f;
                e->vel.x = 0.0f;
                e->vel.y = 0.0f;
                e->vel.z = 0.0f;
                e->scale = 1.0f;
                {
                    Vec v = { 0.0f, 0.0f, 0.0f };
                    v.x = x;
                    v.y = y;
                    v.z = z;
                    e->sfx = psndSFXOn_3D(sfxName, &v);
                }
                break;
            }
            case 4:
            case 5:
                e->f34 = 0.0f;
                e->f30 = 0.6f;
                e->pos.x = 0.0f;
                e->pos.z = 0.0f;
                e->timer = 0;
                e->scale = 1.0f;
                break;
            case 6:
                e->pos.x = 0.0f;
                e->pos.y = 200.0f;
                e->pos.z = 0.0f;
                e->vel.x = -e->pos.x / 30.0f;
                e->vel.y = -e->pos.y / 30.0f;
                e->vel.z = -e->pos.z / 30.0f;
                e->scale = 1.3f;
                e->rot2 = 30.0f;
                e->rot3 = 0.0f;
                break;
            case 7:
                e->pos.x = 400.0f;
                e->pos.y = 200.0f;
                e->pos.z = 0.0f;
                e->scale = 0.5f;
                break;
            case 8:
                e->f34 = 0.0f;
                e->f30 = 0.25f;
                e->pos.x = 0.0f;
                e->pos.y = 400.0f;
                e->pos.z = 0.0f;
                e->scale = 1.0f;
                break;
        }
    }
    return effect;
}
#endif
#pragma opt_propagation off

static inline void effFallRelease(EffectEntry* effect) {
    EffFallElem* e;
    s32 i;
    for (i = 0, e = effect->userdata; i < effect->count; i++, e++) {
        if (e->pose0 != -1) {
            animPoseRelease(e->pose0);
        }
        if (e->pose1 != -1) {
            animPoseRelease(e->pose1);
        }
        psndSFXOff(e->sfx);
    }
}
#ifdef NONMATCHING
void effFallMain(EffectEntry* effect) {
    Vec sndPos;
    const char* bug[2];
    const char* fork1;
    s32 i;
    const char* meteor1;
    const char* light1;

    EffFallElem* e;
    const char* koopa1;
    s32 type;
    s32 arg8;
    s32 played;
    s32 done;
    s32 group;
    const char* meteor2;
    f32 y;
    f32 angle;
    f32 top;
    f32 arg4;
    f32 ground;
    f32 a;
    s32 j;
    f32 rotY;

    e = effect->userdata;
    {
        Vec v = { 0.0f, 0.0f, 0.0f };
        v.x = e->pos.x;
        v.y = (y = e->pos.y);
        v.z = e->pos.z;
        sndPos = v;
    }
    played = 0;
    ground = y + e->arg5;
    type = e->type;
    arg4 = e->arg4;
    rotY = e->rotY;
    arg8 = e->arg8;
    group = gp->inBattle != 0;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        effFallRelease(effect);
        effDelete(effect);
        return;
    }
    bug[1] = "SFX_BTL_STAGE_FALL_BUG1";
    bug[0] = "SFX_BTL_STAGE_FALL_BUG2";
    fork1 = "SFX_BTL_STAGE_DAMAGE_FORK1\0";
    koopa1 = "SFX_BTL_STAGE_FALL_KOOPA1\0\0";
    meteor1 = "SFX_BTL_STAGE_FALL_METEOR1\0";
    meteor2 = "SFX_BTL_STAGE_DAMAGE_METEOR2\0\0\0";
    light1 = "SFX_BTL_STAGE_DAMAGE_LIGHT1";
    angle = 6.2831855f * rotY;
    top = 30.0f + y;
    done = 0;
    for (i = 1, e++; i < effect->count; i++, e++) {
        switch (type) {
            case 0:
            case 1:
                switch (e->state) {
                    case 0:
                        if (e->timer) {
                            e->timer--;
                        }
                        if (e->timer == 0) {
                            e->state++;
                            if (type == 1) {
                                psndSFXOn_3D(bug[1], &sndPos);
                            } else if (i == 1) {
                                psndSFXOn_3D(bug[0], &sndPos);
                            }
                        }
                        break;
                    case 1:
                        if (type == 0 && i > 1 && !played && gp->retraceCount % 6 == 0) {
                            psndSFXOn_3D(bug[0], &sndPos);
                            played = 1;
                        }
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (distABf(e->pos.x, e->pos.z, 0.0f, 0.0f) < arg4 / 2.0f) {
                            if (e->pos.y < ground) {
                                e->pos.y = ground;
                                e->f34 *= -0.3f;
                                e->state++;
                            }
                        } else if (e->pos.y < y) {
                            e->pos.y = y;
                            e->f34 *= -0.3f;
                            e->state++;
                        }
                        break;
                    case 2:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        a = (6.2831855f * angleABf(0.0f, 0.0f, e->pos.x, e->pos.z)) / 360.0f;
                        if (i == 1) {
                            a = angle / 360.0f;
                        }
                        e->pos.x += 0.5f * (f32)sin(a);
                        e->pos.z += 0.5f * -(f32)cos(a);
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                        }
                        break;
                    case 3:
                        e->timer++;
                        if (e->timer > 30) {
                            e->state++;
                        }
                        break;
                    case 4:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                        }
                        break;
                    case 5:
                        done++;
                        break;
                }
                if (((gp->retraceCount >> 1) >> 1) & 1) {
                    e->scroll++;
                }
                if (e->scroll >= 3) {
                    e->scroll = 0;
                }
                e->rot2 = 35.0f * (f32)sin(gp->retraceCount / 2.0f + i);
                break;
            case 2:
                switch (e->state) {
                    case 0:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                            psndSFXOn_3D(fork1, &sndPos);
                        }
                        break;
                    case 1:
                        a = (f32)sin((62.831856f * e->timer) / 60.0f);
                        e->f44 = ((60.0f - e->timer) * a) / 60.0f;
                        e->timer++;
                        if (e->timer > 60) {
                            e->state++;
                        }
                        break;
                    case 2:
                        e->timer++;
                        if (e->timer > 30) {
                            e->state++;
                        }
                        break;
                    case 3:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                        }
                        break;
                    case 4:
                        done++;
                        break;
                }
                e->vtx = (EffFallVtx**)smartAlloc(0x280, 3);
                {
                    EffFallVtx* v = *e->vtx;
                    for (j = 0; j < 32; j++, v++) {
                        v->x = (j & 1) ? 16.0f : -16.0f;
                        v->y = 128.0f - 8.533334f * (j / 2);
                        v->z = 0.0f;
                        v->u = (j & 1) ? 2.0f : 0.0f;
                        v->v = 0.06666667f * (j / 2);
                    }
                }
                {
                    EffFallVtx* v = *e->vtx;
                    for (i = 0; i < 32; i++, v++) {
                        v->x += e->f44 * ((v->y * v->y) / 600.0f);
                    }
                }
                DCFlushRange(*e->vtx, 0x280);
                break;
            case 3:
                switch (e->state) {
                    case 0:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                        }
                        break;
                    case 1:
                        if (e->timer % 10 == 0) {
                            effWaterDamageN64Entry(4, 20, sndPos.x, sndPos.y, sndPos.z, 1.0f);
                        }
                        e->timer++;
                        if (e->timer > arg8) {
                            e->state++;
                        }
                        break;
                    case 2:
                        e->alpha *= 0.9f;
                        e->scale *= 0.9f;
                        if (e->scale < 0.01f) {
                            psndSFXOff(e->sfx);
                            effDelete(effect);
                            return;
                        }
                        break;
                }
                e->vel.y -= 0.2f;
                break;
            case 4:
            case 5:
                switch (e->state) {
                    case 0:
                        if (type == 5) {
                            if (!animGroupBaseAsync("EFF_Baketu\0", group, 0)) {
                                break;
                            }
                            if (e->pose0 == -1) {
                                e->pose0 = animPoseEntry("EFF_Baketu\0", group);
                                animPoseSetAnim(e->pose0, "Z_1", 1);
                            }
                        } else {
                            if (!animGroupBaseAsync("EFF_Tarai\0\0", group, 0)) {
                                break;
                            }
                            if (e->pose0 == -1) {
                                e->pose0 = animPoseEntry("EFF_Tarai\0\0", group);
                                animPoseSetAnim(e->pose0, "Z_1", 1);
                            }
                        }
                        if (e->timer) {
                            e->timer--;
                        }
                        if (e->timer == 0) {
                            e->state++;
                        }
                        break;
                    case 1:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (distABf(e->pos.x, e->pos.z, 0.0f, 0.0f) < arg4 / 2.0f) {
                            if (e->pos.y < ground) {
                                e->pos.y = ground;
                                e->f34 *= -0.3f;
                                e->state++;
                            }
                        } else if (e->pos.y < y) {
                            e->pos.y = y;
                            e->f34 *= -0.3f;
                            e->state++;
                        }
                        break;
                    case 2:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        a = (6.2831855f * angleABf(0.0f, 0.0f, e->pos.x, e->pos.z)) / 360.0f;
                        if (i == 1) {
                            a = angle / 360.0f;
                        }
                        e->pos.x += 2.0f * (f32)sin(a);
                        e->pos.z += 2.0f * -(f32)cos(a);
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->f34 *= -0.5f;
                            e->pos.y = y;
                            e->timer = 0;
                            if (e->f34 < 1.0f) {
                                e->state++;
                            }
                        }
                        break;
                    case 3:
                        e->timer++;
                        if (e->timer > 30) {
                            e->state++;
                        }
                        break;
                    case 4:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                            animPoseRelease(e->pose0);
                            e->pose0 = -1;
                        }
                        break;
                    case 5:
                        done++;
                        break;
                }
                switch (type) {
                    case 4:
                        if (e->state > 1) {
                            e->rot2 += (360.0f - e->rot2) / 10.0f;
                        }
                        break;
                    case 5:
                        if (e->state > 1) {
                            e->rot2 += (430.0f - e->rot2) / 10.0f;
                        }
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                break;
            case 6:
                switch (e->state) {
                    case 0:
                        if (!animGroupBaseAsync("EFF_koopa\0\0", group, 0)) {
                            break;
                        }
                        if (e->pose0 == -1) {
                            e->pose0 = animPoseEntry("EFF_koopa\0\0", group);
                            animPoseSetAnim(e->pose0, "Z_1", 1);
                            psndSFXOn_3D(koopa1, &sndPos);
                        }
                        e->pos.x += e->vel.x;
                        e->pos.y += e->vel.y;
                        e->pos.z += e->vel.z;
                        e->timer++;
                        if (e->timer > 30) {
                            e->timer = 0;
                            e->state++;
                            effKemuri1N64Entry(4, sndPos.x + e->pos.x, sndPos.y + e->pos.y, sndPos.z + e->pos.z, 0.0f);
                            evtEntry(evt_shake, 0, 0);
                        }
                        break;
                    case 1:
                        e->rot2 = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(30.0f, -27.0f, 11, e->timer, 180);
                        if (e->rot2 < 0.0f) {
                            e->rot3 = e->rot2;
                            e->rot2 = 0.0f;
                        }
                        e->timer++;
                        if (e->timer > 180) {
                            e->timer = 0;
                            e->state++;
                        }
                        if (e->timer == 100) {
                            psndSFXOn_3D(koopa1, &sndPos);
                        }
                        break;
                    case 2:
                        e->rot2 = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(-27.0f, 80.0f, 11, e->timer, 200);
                        if (e->rot2 < 0.0f) {
                            e->rot3 = e->rot2;
                            e->rot2 = 0.0f;
                        }
                        e->timer++;
                        if (e->timer > 200) {
                            animPoseRelease(e->pose0);
                            e->pose0 = -1;
                            done++;
                        }
                        if (e->timer == 70) {
                            psndSFXOn_3D(koopa1, &sndPos);
                        }
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                break;
            case 7:
                switch (e->state) {
                    case 0:
                        if (!animGroupBaseAsync("EFF_inseki\0", group, 0)) {
                            break;
                        }
                        psndSFXOn_3D(meteor1, &sndPos);
                        if (e->pose0 == -1) {
                            e->pose0 = animPoseEntry("EFF_inseki\0", group);
                            animPoseSetAnim(e->pose0, "Z_1", 1);
                        }
                        if (e->pose1 == -1) {
                            e->pose1 = animPoseEntry("EFF_inseki\0", group);
                            animPoseSetAnim(e->pose1, "Z_2", 1);
                        }
                    case 2:
                    case 4:
                    case 6: {
                        f32 tbl[4][3] = {
                            { 140.0f, 40.0f, -10.0f },
                            { 0.0f, 40.0f, -40.0f },
                            { -140.0f, 40.0f, -10.0f },
                            { -400.0f, 40.0f, -40.0f }
                        };
                        e->vel.x = tbl[e->state / 2][0];
                        e->vel.y = tbl[e->state / 2][1];
                        e->vel.z = tbl[e->state / 2][2];
                        e->f30 = 0.4f;
                        e->timer = distABf(e->vel.x, e->vel.z, e->pos.x, e->pos.z) / 5.0f;
                        e->f34 = ((e->vel.y - e->pos.y) / e->timer) + (e->f30 * e->timer) / 2.0f;
                        e->rotY = angleABf(e->pos.x, e->pos.z, e->vel.x, e->vel.z);
                        e->rot2 = 0.0f;
                        e->state++;
                        break;
                    }
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        e->pos.x += 5.0f * fall_sinf((6.2831855f * e->rotY) / 360.0f);
                        e->pos.z += 5.0f * -fall_cosf((6.2831855f * e->rotY) / 360.0f);
                        if ((--e->timer) < 0) {
                            e->pos.x = e->vel.x;
                            e->pos.y = e->vel.y;
                            e->pos.z = e->vel.z;
                            e->state++;
                            if (e->state == 2) {
                                e->sfx = psndSFXOn_3D(meteor2, &sndPos);
                            }
                            if (e->state != 8) {
                                effKemuri1N64Entry(4, sndPos.x + e->pos.x, sndPos.y + e->pos.y - 40.0f, sndPos.z + e->pos.z, 0.0f);
                                evtEntry(evt_shake, 0, 0);
                            }
                        }
                        e->rot2 += (360.0f - e->rot2) / 30.0f;
                        break;
                    case 8:
                        psndSFXOff(e->sfx);
                        animPoseRelease(e->pose0);
                        animPoseRelease(e->pose1);
                        e->pose0 = -1;
                        e->pose1 = -1;
                        e->state++;
                        break;
                    case 9:
                        done++;
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                if (e->pose1 != -1) {
                    animPoseMain(e->pose1);
                }
                break;
            case 8:
                switch (e->state) {
                    case 0:
                        if (!animGroupBaseAsync("EFF_light\0\0", group, 0)) {
                            break;
                        }
                        e->pose0 = animPoseEntry("EFF_light\0\0", group);
                        animPoseSetAnim(e->pose0, "Z_1", 1);
                        e->state++;
                        break;
                    case 1:
                    case 2:
                        e->pos.y += e->f34;
                        e->f34 -= e->f30;
                        if (e->pos.y < y) {
                            e->pos.y = y;
                            e->timer = 0;
                            e->state++;
                        }
                        if (1 == e->state && e->pos.y < top) {
                            effKemuri1N64Entry(4, sndPos.x + e->pos.x, sndPos.y + y, sndPos.z + e->pos.z, 0.0f);
                            evtEntry(evt_shake, 0, 0);
                            animPoseSetAnim(e->pose0, "A_1", 1);
                            e->state++;
                            psndSFXOn_3D(light1, &sndPos);
                        }
                        break;
                    case 3:
                        if (animPoseGetLoopTimes(e->pose0) < 1.0f) {
                            break;
                        }
                        e->timer++;
                        if (e->timer > e->arg8) {
                            e->state++;
                        }
                        break;
                    case 4:
                        e->alpha -= 10;
                        if (e->alpha < 0) {
                            e->alpha = 0;
                            e->state++;
                        }
                        break;
                    case 5:
                        animPoseRelease(e->pose0);
                        e->pose0 = -1;
                        e->state++;
                        break;
                    case 6:
                        done++;
                        break;
                }
                if (e->pose0 != -1) {
                    animPoseMain(e->pose0);
                }
                break;
        }
    }
    if (done >= effect->count - 1) {
        effDelete(effect);
        return;
    }
    switch (type) {
        case 3:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 2, (DispCallback)effFallDispWater, effect);
            break;
        case 4:
        case 5:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 0, (DispCallback)effFallDisp, effect);
            break;
        case 7:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 2, (DispCallback)effFallDispInseki, effect);
            break;
        case 6:
        default:
            dispEntry(CAMERA_3D, dispCalcZ(&sndPos), 2, (DispCallback)effFallDisp, effect);
            break;
    }
}
#endif

#pragma opt_propagation reset
#ifdef NONMATCHING
void effFallDisp(CameraId cameraId, EffectEntry* effect) {
    Mtx trans;
    Mtx scl;
    Mtx rot;
    Mtx mtx;
    GXTexObj tex;
    Vec axis;
    CameraEntry* cam;
    EffFallElem* e;
    s32 i;
    s32 type;
    f32 angle;
    s32 j;
    f32 hw, hh, s;

    e = effect->userdata;
    cam = camGetPtr(cameraId);
    type = e->type;
    angle = e->rotY;
    PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
    PSMTXRotRad(rot, 'y', -camGetPtr(cameraId)->viewYaw * 0.017453292f);
    PSMTXConcat(trans, rot, mtx);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    switch (type) {
        case 0:
        case 1:
            effGetTexObj(0x32, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            break;
        case 2:
            effGetTexObj(0x33, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            break;
    }
    for (i = 1, e++; i < effect->count; i++, e++) {
        switch (type) {
            case 0:
            case 1:
                hw = 64.0f;
                hh = 42.666668f;
                hw /= 2.0f;
                hh /= 2.0f;
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXRotRad(rot, 'y', e->rotY * 0.017453292f);
                PSMTXConcat(trans, rot, trans);
                PSMTXTrans(rot, 0.0f, hh / 2.0f * e->scale, 0.0f);
                PSMTXConcat(trans, rot, trans);
                PSMTXRotRad(rot, 'z', e->rot2 * 0.017453292f);
                PSMTXConcat(trans, rot, trans);
                PSMTXTrans(rot, 0.0f, -hh / 2.0f * e->scale, 0.0f);
                PSMTXConcat(trans, rot, trans);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(cam->view, trans, trans);
                GXLoadPosMtxImm(trans, 0);
                GXSetCurrentMtx(0);
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 255, 255, 255, e->alpha });
                PSMTXScale(scl, 1.0f, 0.33333334f, 1.0f);
                PSMTXTrans(trans, 0.0f, (f32)e->scroll, 0.0f);
                PSMTXConcat(scl, trans, trans);
                GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(-hw / 2.0f, hh, 0.0f);
                GXTexCoord2f32(0.0f, 0.0f);
                GXPosition3f32(hw / 2.0f, hh, 0.0f);
                GXTexCoord2f32(1.0f, 0.0f);
                GXPosition3f32(hw / 2.0f, 0.0f, 0.0f);
                GXTexCoord2f32(1.0f, 1.0f);
                GXPosition3f32(-hw / 2.0f, 0.0f, 0.0f);
                GXTexCoord2f32(0.0f, 1.0f);
                break;
            case 2:
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(cam->view, trans, trans);
                GXLoadPosMtxImm(trans, 0);
                GXSetCurrentMtx(0);
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 255, 255, 255, e->alpha });
                PSMTXIdentity(trans);
                GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
                for (j = 0; j < 30; j += 2) {
                    EffFallVtx* v = &(*e->vtx)[j];
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    GXPosition3f32(v[0].x, v[0].y, v[0].z);
                    GXTexCoord2f32(v[0].u, v[0].v);
                    GXPosition3f32(v[2].x, v[2].y, v[2].z);
                    GXTexCoord2f32(v[2].u, v[2].v);
                    GXPosition3f32(v[3].x, v[3].y, v[3].z);
                    GXTexCoord2f32(v[3].u, v[3].v);
                    GXPosition3f32(v[1].x, v[1].y, v[1].z);
                    GXTexCoord2f32(v[1].u, v[1].v);
                }
                break;
            case 4:
            case 5: {
                Vec v = { 0.0f, 0.0f, 0.0f };
                v.x = (f32)cos(6.2831855f * angle / 360.0f);
                v.z = (f32)sin(6.2831855f * angle / 360.0f);
                axis = v;
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXTrans(scl, 0.0f, (f32)(type == 4 ? 8 : 16), 0.0f);
                PSMTXConcat(trans, scl, trans);
                PSMTXRotAxisRad(rot, &axis, -e->rot2 * 0.017453292f);
                PSMTXConcat(trans, rot, trans);
                PSMTXTrans(scl, 0.0f, (f32)-(type == 4 ? 8 : 16), 0.0f);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                if (e->pose0 != -1) {
                    animPoseDrawMtx(e->pose0, trans, 1, 0.0f, 10.0f);
                    animPoseDrawMtx(e->pose0, trans, 2, 0.0f, 10.0f);
                    animPoseDrawMtx(e->pose0, trans, 3, 0.0f, 10.0f);
                }
                break;
            }
            case 6:
                if (e->pose0 == -1) {
                    break;
                }
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                if (angle < 180.0f) {
                    PSMTXScale(scl, e->scale, e->scale, e->scale);
                } else {
                    PSMTXScale(scl, -e->scale, e->scale, e->scale);
                }
                PSMTXConcat(trans, scl, trans);
                if (e->rot2) {
                    PSMTXRotRad(rot, 'z', -e->rot2 * 0.017453292f);
                    PSMTXConcat(trans, rot, trans);
                } else {
                    PSMTXTrans(scl, -200.0f, 0.0f, 0.0f);
                    PSMTXConcat(trans, scl, trans);
                    PSMTXRotRad(rot, 'z', -e->rot3 * 0.017453292f);
                    PSMTXConcat(trans, rot, trans);
                    PSMTXTrans(scl, 200.0f, 0.0f, 0.0f);
                    PSMTXConcat(trans, scl, trans);
                }
                PSMTXConcat(mtx, trans, trans);
                PSMTXTrans(scl, -82.655f, 88.8f, 0.0f);
                PSMTXConcat(trans, scl, scl);
                PSMTXScale(rot, 1.03f, 1.03f, 1.03f);
                PSMTXConcat(scl, rot, rot);
                PSMTXTrans(scl, 82.655f, -88.8f, 0.0f);
                PSMTXConcat(rot, scl, scl);
                animPoseSetMaterialFlagOn(e->pose0, 0x40);
                animPoseSetMaterialEvtColor(e->pose0, (GXColor){ 0, 0, 0, 255 });
                animPoseDrawMtx(e->pose0, scl, 1, 0.0f, 10.0f);
                animPoseDrawMtx(e->pose0, scl, 2, 0.0f, 10.0f);
                animPoseDrawMtx(e->pose0, scl, 3, 0.0f, 10.0f);
                animPoseSetMaterialFlagOn(e->pose0, 0x40);
                animPoseSetMaterialEvtColor(e->pose0, (GXColor){ 255, 255, 255, 255 });
                animPoseDrawMtx(e->pose0, trans, 1, 0.0f, 10.0f);
                animPoseDrawMtx(e->pose0, trans, 2, 0.0f, 10.0f);
                animPoseDrawMtx(e->pose0, trans, 3, 0.0f, 10.0f);
                break;
            case 8:
                if (e->pose0 == -1) {
                    break;
                }
                PSMTXTrans(trans, e->pos.x, e->pos.y, e->pos.z);
                PSMTXScale(scl, e->scale, e->scale, e->scale);
                PSMTXConcat(trans, scl, trans);
                PSMTXConcat(mtx, trans, trans);
                animPoseSetMaterialFlagOn(e->pose0, 0x40);
                animPoseSetMaterialEvtColor(e->pose0, (GXColor){ 255, 255, 255, e->alpha });
                animPoseDrawMtx(e->pose0, trans, 1, 0.0f, 10.0f);
                animPoseDrawMtx(e->pose0, trans, 2, 0.0f, 10.0f);
                animPoseDrawMtx(e->pose0, trans, 3, 0.0f, 10.0f);
                break;
        }
    }
}
#endif

#ifdef NONMATCHING
void effFallDispInseki(CameraId cameraId, EffectEntry* effect) {
    Mtx trans;
    Mtx scl;
    Mtx rot;
    Mtx mtx;
    Vec axis;
    EffFallWork* w;
    s32 i;

    w = effect->userdata;
    camGetPtr(cameraId);
    PSMTXTrans(trans, w->position.x, w->position.y, w->position.z);
    PSMTXRotRad(rot, 'y', -camGetPtr(cameraId)->viewYaw * 0.017453292f);
    PSMTXConcat(trans, rot, mtx);
    if (w->pose0 != -1 && w->pose1 != -1) {
        Vec v = { 0.0f, 0.0f, 0.0f };
        v.x = (f32)cos(6.2831855f * w->angle / 360.0f);
        v.z = (f32)sin(6.2831855f * w->angle / 360.0f);
        axis = v;
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
                PSMTXRotAxisRad(rot, &axis, -w->rotation * 0.017453292f);
                PSMTXScale(scl, 2.05f * w->scale, 2.05f * w->scale, 2.05f * w->scale);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(trans, rot, trans);
                PSMTXConcat(trans, scl, trans);
                animPoseSetMaterialFlagOn(w->pose0, 0x40);
                animPoseSetMaterialEvtColor(w->pose0, (GXColor){ 0, 0, 0, 255 });
            } else {
                PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
                PSMTXRotAxisRad(rot, &axis, -w->rotation * 0.017453292f);
                PSMTXScale(scl, 2.0f * w->scale, 2.0f * w->scale, 2.0f * w->scale);
                PSMTXConcat(mtx, trans, trans);
                PSMTXConcat(trans, rot, trans);
                PSMTXConcat(trans, scl, trans);
                animPoseSetMaterialFlagOn(w->pose0, 0x40);
                animPoseSetMaterialEvtColor(w->pose0, (GXColor){ 255, 255, 255, 255 });
            }
            animPoseDrawMtx(w->pose0, trans, 1, 0.0f, 10.0f);
            animPoseDrawMtx(w->pose0, trans, 2, 0.0f, 10.0f);
            animPoseDrawMtx(w->pose0, trans, 3, 0.0f, 10.0f);
        }
        PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
        PSMTXScale(scl, 2.1f * w->scale, 2.1f * w->scale, 2.1f * w->scale);
        PSMTXConcat(mtx, trans, trans);
        PSMTXConcat(trans, scl, trans);
        animPoseDrawMtx(w->pose1, trans, 1, 0.0f, 10.0f);
        animPoseDrawMtx(w->pose1, trans, 2, 0.0f, 10.0f);
        animPoseDrawMtx(w->pose1, trans, 3, 0.0f, 10.0f);
    }
}
#endif

#ifdef NONMATCHING
#pragma opt_propagation off
static const GXColor white255 = { 255, 255, 255, 255 };
void effFallDispWater(CameraId cameraId, EffectEntry *effect) {
    Mtx trans;
    Mtx scl;
    Mtx rot;
    Mtx mtx;
    GXTexObj tex;
    GXColor color;
    CameraEntry *cam;
    EffFallWork *w;
    f32 hw;
    f32 hh;
    f32 s;
    w = effect->userdata;
    cam = camGetPtr(cameraId);
    PSMTXTrans(trans, w->position.x, w->position.y, w->position.z);
    PSMTXRotRad(rot, 'y', (-camGetPtr(cameraId)->viewYaw) * 0.017453292f);
    PSMTXConcat(trans, rot, mtx);
    PSMTXConcat(cam->view, mtx, mtx);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_APREV, GX_CA_ZERO);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    effGetTexObj(0x35, &tex);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    hw = 64.0f;
    hh = 704.0f;
    hw /= 2.0f;
    hh /= 2.0f;
    PSMTXTrans(trans, w->pos3.x, w->pos3.y, w->pos3.z);
    PSMTXScale(scl, 1.0f, hh / ((f32) GXGetTexObjHeight(&tex)), 1.0f);
    PSMTXConcat(trans, scl, trans);
    GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
    PSMTXTrans(trans, w->pos2.x, w->pos2.y, w->pos2.z);
    PSMTXScale(scl, w->scale, 1.0f, 1.0f);
    PSMTXConcat(trans, scl, trans);
    PSMTXConcat(mtx, trans, trans);
    GXLoadPosMtxImm(trans, 0);
    GXSetTevColor(GX_TEVREG0, white255);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32((-hw) / 2.0f, hh, 0.0f);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(hw / 2.0f, hh, 0.0f);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(2.0f, 0.0f);
    GXPosition3f32(hw / 2.0f, 0.0f, 0.0f);
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(2.0f, 1.0f);
    GXPosition3f32((-hw) / 2.0f, 0.0f, 0.0f);
    GXColor4u8(255, 255, 255, 0);
    GXTexCoord2f32(0.0f, 1.0f);
    {
        EffFallWork *w2 = effect->userdata;
        if (w2->state > 0) {
            PSMTXTrans(trans, w2->pos2.x, w2->pos2.y, w2->pos2.z);
            PSMTXScale(scl, 0.56f, 0.4f, 0.8f);
            PSMTXConcat(mtx, trans, trans);
            PSMTXConcat(trans, scl, trans);
            GXLoadPosMtxImm(trans, 0);
            PSMTXTrans(trans, w2->pos3.y / 8.0f, 0.0f, 0.0f);
            GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
            GXSetTevColor(GX_TEVREG0, (GXColor){255, 255, 255, w2->alpha});
            effGetTexObj(0x37, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 8);
            GXSetArray(GX_VA_POS, shibuki_vertex_tbl, 6);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
            GXSetArray(GX_VA_NRM, shibuki_normal_tbl, 3);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, shibuki_color0_tbl, 4);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 14);
            GXSetArray(GX_VA_TEX0, shibuki_texcoord0_tbl, 4);
            GXCallDisplayList(shibuki_dl_1_0, 0x20);
            GXCallDisplayList(shibuki_dl_1_1, 0x20);
            GXCallDisplayList(shibuki_dl_1_2, 0x20);
            GXCallDisplayList(shibuki_dl_1_3, 0x20);
            PSMTXTrans(trans, w2->pos2.x, w2->pos2.y, w2->pos2.z);
            s = w2->scale;
            s = s * 0.8f;
            PSMTXScale(scl, 0.7f * s, 0.5f * s, s);
            PSMTXConcat(mtx, trans, trans);
            PSMTXConcat(trans, scl, trans);
            GXLoadPosMtxImm(trans, 0);
            PSMTXTrans(trans, 0.0f, (-w2->pos3.y) / 4.0f, 0.0f);
            GXLoadTexMtxImm(trans, GX_TEXMTX0, GX_MTX2x4);
            {
                static const GXColor white255b = {255, 255, 255, 255};
                GXSetTevColor(GX_TEVREG0, white255b);
            }
            effGetTexObj(0x36, &tex);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 8);
            GXSetArray(GX_VA_POS, shibuki_vertex_tbl, 6);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
            GXSetArray(GX_VA_NRM, shibuki_normal_tbl, 3);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetArray(GX_VA_CLR0, shibuki_color0_tbl, 4);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 14);
            GXSetArray(GX_VA_TEX0, shibuki_texcoord0_tbl, 4);
            GXCallDisplayList(shibuki_dl_0_0, 0x40);
            GXCallDisplayList(shibuki_dl_0_1, 0x40);
            GXCallDisplayList(shibuki_dl_0_2, 0x40);
            GXCallDisplayList(shibuki_dl_0_3, 0x40);
        }
    }
}
#endif

#ifdef NONMATCHING
s32 effFallCheckHit(EffectEntry* effect) {
    EffFallWork* w = effect->userdata;
    switch (w->type) {
        case 0:
        case 1:
        case 4:
        case 5:
            if (w->state >= 2) return 1;
            break;
        case 2:
        case 3:
            if (w->state >= 1) return 1;
            break;
        case 6:
            if (w->state >= 2 || (w->state == 1 && w->timer > 90)) return 1;
            break;
        case 7:
            if (w->state >= 4) return 1;
            break;
        case 8:
            if (w->state >= 3) return 1;
            break;
    }
    return 0;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: effFallEntry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".rodata") const f32 vec3_802fe418[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fe424[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 dat_802fe430[12] = { 0x430C0000, 0x42200000, 0xC1200000, 0x00000000, 0x42200000, 0xC2200000, 0xC30C0000, 0x42200000, 0xC1200000, 0xC3C80000, 0x42200000, 0xC2200000 };
__declspec(section ".rodata") const f32 vec3_802fe460[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fe46c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_802fe478 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802fe480 = 4503601774854144;
__declspec(section ".rodata") const char str_802FE488[] = "SFX_BTL_STAGE_FALL_BUG1";
__declspec(section ".rodata") const char str_802FE4A0[] = "SFX_BTL_STAGE_FALL_BUG2";
__declspec(section ".rodata") const char str_802FE4B8[] = "SFX_BTL_STAGE_DAMAGE_FORK1\000";
__declspec(section ".rodata") const char str_802FE4D4[] = "SFX_BTL_STAGE_FALL_KOOPA1\000\000";
__declspec(section ".rodata") const char str_802FE4F0[] = "SFX_BTL_STAGE_FALL_METEOR1\000";
__declspec(section ".rodata") const char str_802FE50C[] = "SFX_BTL_STAGE_DAMAGE_METEOR2\000\000\000";
__declspec(section ".rodata") const char str_802FE52C[] = "SFX_BTL_STAGE_DAMAGE_LIGHT1";
__declspec(section ".rodata") const char str_802FE548[] = "EFF_Baketu\000";
__declspec(section ".rodata") const char str_802FE554[] = "EFF_Tarai\000\000";
__declspec(section ".rodata") const char str_802FE560[] = "EFF_koopa\000\000";
__declspec(section ".rodata") const char str_802FE56C[] = "EFF_inseki\000";
__declspec(section ".rodata") const char str_802FE578[] = "EFF_light\000\000";
__declspec(section ".rodata") const char str_802FE584[] = "SFX_BTL_STAGE_FALL_WATER1\000\000";
__declspec(section ".sdata2") const u32 dat_80420f48 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f4c = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f50 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80420f54 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80420f58 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f5c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80420f60 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80420f64 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80420f68 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80420f6c = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_deg2rad_80420f70 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_64_80420f74 = 64.0f;
__declspec(section ".sdata2") const f32 float_704_80420f78 = 704.0f;
__declspec(section ".sdata2") const f32 float_0p5_80420f7c = 0.5f;
__declspec(section ".sdata2") const f32 float_1_80420f80 = 1.0f;
__declspec(section ".sdata2") const f32 float_0_80420f84 = 0.0f;
__declspec(section ".sdata2") const f32 float_2_80420f88 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p56_80420f8c = 0.56f;
__declspec(section ".sdata2") const f32 float_0p4_80420f90 = 0.4f;
__declspec(section ".sdata2") const f32 float_0p8_80420f94 = 0.8f;
__declspec(section ".sdata2") const f32 float_0p125_80420f98 = 0.125f;
__declspec(section ".sdata2") const f32 float_0p7_80420f9c = 0.7f;
__declspec(section ".sdata2") const f32 float_0p25_80420fa0 = 0.25f;
__declspec(section ".sdata2") const f32 float_6p2832_80420fa4 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_80420fa8 = 360.0f;
__declspec(section ".sdata2") const f32 float_2p05_80420fac = 2.05f;
__declspec(section ".sdata2") const f32 float_10_80420fb0 = 10.0f;
__declspec(section ".sdata2") const f32 float_2p1_80420fb4 = 2.1f;
__declspec(section ".sdata2") const f32 float_42p667_80420fb8 = 42.666668f;
__declspec(section ".sdata2") const f32 float_0p33333_80420fbc = 0.33333334f;
__declspec(section ".sdata2") const f32 float_180_80420fc0 = 180.0f;
__declspec(section ".sdata2") const f32 float_neg200_80420fc4 = -200.0f;
__declspec(section ".sdata2") const f32 float_200_80420fc8 = 200.0f;
__declspec(section ".sdata2") const f32 float_neg82p655_80420fcc = -82.655f;
__declspec(section ".sdata2") const f32 float_88p8_80420fd0 = 88.8f;
__declspec(section ".sdata2") const f32 float_1p03_80420fd4 = 1.03f;
__declspec(section ".sdata2") const f32 float_82p655_80420fd8 = 82.655f;
__declspec(section ".sdata2") const f32 float_neg88p8_80420fdc = -88.8f;
__declspec(section ".sdata2") const f32 float_30_80420fe0 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg0p3_80420fe4 = -0.3f;
__declspec(section ".sdata2") const f32 float_35_80420fe8 = 35.0f;
__declspec(section ".sdata2") const f32 float_62p832_80420fec = 62.831856f;
__declspec(section ".sdata2") const f32 float_60_80420ff0 = 60.0f;
__declspec(section ".sdata2") const f32 float_16_80420ff4 = 16.0f;
__declspec(section ".sdata2") const f32 float_neg16_80420ff8 = -16.0f;
__declspec(section ".sdata2") const f32 float_128_80420ffc = 128.0f;
__declspec(section ".sdata2") const f32 float_8p5333_80421000 = 8.533334f;
__declspec(section ".sdata2") const f32 float_0p066667_80421004 = 0.06666667f;
__declspec(section ".sdata2") const f32 float_600_80421008 = 600.0f;
__declspec(section ".sdata2") const f32 float_0p9_8042100c = 0.9f;
__declspec(section ".sdata2") const f32 float_0p01_80421010 = 0.01f;
__declspec(section ".sdata2") const f32 float_0p2_80421014 = 0.2f;
__declspec(section ".sdata2") const char str_80421018[4] = "Z_1";
__declspec(section ".sdata2") const f32 float_neg0p5_8042101c = -0.5f;
__declspec(section ".sdata2") const f32 float_430_80421020 = 430.0f;
__declspec(section ".sdata2") const f32 float_neg27_80421024 = -27.0f;
__declspec(section ".sdata2") const f32 float_80_80421028 = 80.0f;
__declspec(section ".sdata2") const char str_8042102C[4] = "Z_2";
__declspec(section ".sdata2") const f32 float_5_80421030 = 5.0f;
__declspec(section ".sdata2") const f32 float_0p00761_80421034 = 0.00761f;
__declspec(section ".sdata2") const f32 float_0p16605_80421038 = 0.16605f;
__declspec(section ".sdata2") const f32 float_3p1416_8042103c = 3.1415927f;
__declspec(section ".sdata2") const f32 float_1p5708_80421040 = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_80421044 = 4.712389f;
__declspec(section ".sdata2") const f32 float_0p03705_80421048 = 0.03705f;
__declspec(section ".sdata2") const f32 float_0p4967_8042104c = 0.4967f;
__declspec(section ".sdata2") const f32 float_40_80421050 = 40.0f;
__declspec(section ".sdata2") const char str_80421054[4] = "A_1";
__declspec(section ".sdata2") const char str_80421058[8] = "Fall\0\0\0";
__declspec(section ".sdata2") const f32 float_300_80421060 = 300.0f;
__declspec(section ".sdata2") const f32 float_1p2_80421064 = 1.2f;
__declspec(section ".sdata2") const f32 float_1p6_80421068 = 1.6f;
__declspec(section ".sdata2") const f32 float_0p1_8042106c = 0.1f;
__declspec(section ".sdata2") const f32 float_0p6_80421070 = 0.6f;
__declspec(section ".sdata2") const f32 float_1p3_80421074 = 1.3f;
__declspec(section ".sdata2") const f32 float_400_80421078 = 400.0f;

asm s32 effFallCheckHit(EffectEntry* effect) {
	nofralloc
	lwz r3, 0xc(r3)
	lwz r0, 0x0(r3)
	cmpwi r0, 0x6
	beq @1
	bge @2
	cmpwi r0, 0x2
	bge @3
	cmpwi r0, 0x0
	bge @4
	b @5
	@3:
	cmpwi r0, 0x4
	bge @4
	b @6
	@2:
	cmpwi r0, 0x8
	beq @7
	bge @5
	b @8
	@4:
	lwz r0, 0xa0(r3)
	cmpwi r0, 0x2
	blt @5
	li r3, 0x1
	blr
	@6:
	lwz r0, 0xa0(r3)
	cmpwi r0, 0x1
	blt @5
	li r3, 0x1
	blr
	@1:
	lwz r0, 0xa0(r3)
	cmpwi r0, 0x2
	bge @9
	cmpwi r0, 0x1
	bne @5
	lwz r0, 0x8c(r3)
	cmpwi r0, 0x5a
	ble @5
	@9:
	li r3, 0x1
	blr
	@8:
	lwz r0, 0xa0(r3)
	cmpwi r0, 0x4
	blt @5
	li r3, 0x1
	blr
	@7:
	lwz r0, 0xa0(r3)
	cmpwi r0, 0x3
	blt @5
	li r3, 0x1
	blr
	@5:
	li r3, 0x0
	blr
}

void effFallDisp(CameraId cameraId, EffectEntry* effect);
__declspec(section ".data") static void* jumptable_803AE000[] = {
    (char*)effFallDisp + 0x214,
    (char*)effFallDisp + 0x214,
    (char*)effFallDisp + 0x484,
    (char*)effFallDisp + 0xB04,
    (char*)effFallDisp + 0x608,
    (char*)effFallDisp + 0x608,
    (char*)effFallDisp + 0x7D4,
    (char*)effFallDisp + 0xB04,
    (char*)effFallDisp + 0xA38,
};
void effFallMain(EffectEntry* effect);
__declspec(section ".data") static void* jumptable_803AE024[] = {
    (char*)effFallMain + 0xF08,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0xF84,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0xF84,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0xF84,
    (char*)effFallMain + 0x10FC,
    (char*)effFallMain + 0x1364,
    (char*)effFallMain + 0x1398,
};
void effFallMain(EffectEntry* effect);
__declspec(section ".data") static void* jumptable_803AE04C[] = {
    (char*)effFallMain + 0x194,
    (char*)effFallMain + 0x194,
    (char*)effFallMain + 0x4B0,
    (char*)effFallMain + 0x808,
    (char*)effFallMain + 0x960,
    (char*)effFallMain + 0x960,
    (char*)effFallMain + 0xCC4,
    (char*)effFallMain + 0xEE4,
    (char*)effFallMain + 0x13C0,
};
EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8);
__declspec(section ".data") static void* jumptable_803AE070[] = {
    (char*)effFallEntry + 0x278,
    (char*)effFallEntry + 0x278,
    (char*)effFallEntry + 0x2D0,
    (char*)effFallEntry + 0x2FC,
    (char*)effFallEntry + 0x370,
    (char*)effFallEntry + 0x370,
    (char*)effFallEntry + 0x39C,
    (char*)effFallEntry + 0x3F8,
    (char*)effFallEntry + 0x41C,
};
asm void effFallDispWater(CameraId cameraId, EffectEntry *effect) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stmw r27, 0x10c(r1)
	mr r28, r4
	lis r4, lbl_803ADD20@ha
	lwz r29, 0xc(r28)
	mr r27, r3
	addi r30, r4, lbl_803ADD20@l
	bl camGetPtr
	lfs f1, 0x4(r29)
	mr r31, r3
	lfs f2, 0x8(r29)
	addi r3, r1, 0xc8
	lfs f3, 0xc(r29)
	bl PSMTXTrans
	mr r3, r27
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x68
	lfs f0, float_deg2rad_80420f70(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r3, r1, 0xc8
	addi r4, r1, 0x68
	addi r5, r1, 0x38
	bl PSMTXConcat
	addi r4, r1, 0x38
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	li r3, 0x2
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x0
	bl GXSetTevOp
	li r3, 0x1
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x2
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x1
	li r6, 0x0
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x2
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	addi r4, r1, 0x18
	li r3, 0x35
	bl effGetTexObj
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadTexObj
	lfs f31, float_64_80420f74(r2)
	addi r3, r1, 0xc8
	lfs f0, float_0p5_80420f7c(r2)
	lfs f30, float_704_80420f78(r2)
	fmuls f31, f31, f0
	lfs f1, 0xb8(r29)
	fmuls f30, f30, f0
	lfs f2, 0xbc(r29)
	lfs f3, 0xc0(r29)
	bl PSMTXTrans
	addi r3, r1, 0x18
	bl GXGetTexObjHeight
	clrlwi r4, r3, 16
	lis r0, 0x4330
	lis r3, double_to_int_mask_802fe478@ha
	stw r4, 0xfc(r1)
	addi r4, r3, double_to_int_mask_802fe478@l
	lfs f1, float_1_80420f80(r2)
	stw r0, 0xf8(r1)
	addi r3, r1, 0x98
	lfd f2, 0x0(r4)
	fmr f3, f1
	lfd f0, 0xf8(r1)
	fsubs f0, f0, f2
	fdivs f2, f30, f0
	bl PSMTXScale
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xc8
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	lfs f1, 0x6c(r29)
	addi r3, r1, 0xc8
	lfs f2, 0x70(r29)
	lfs f3, 0x74(r29)
	bl PSMTXTrans
	lfs f2, float_1_80420f80(r2)
	addi r3, r1, 0x98
	lfs f1, 0x94(r29)
	fmr f3, f2
	bl PSMTXScale
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0xc8
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xc8
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, dat_80420f64(r2)
	addi r4, r1, 0x14
	li r3, 0x1
	stw r0, 0x14(r1)
	bl GXSetTevColor
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	fneg f1, f31
	lfs f0, float_0p5_80420f7c(r2)
	lis r4, 0xcc01
	li r3, 0xff
	fmuls f2, f31, f0
	li r0, 0x0
	fmuls f1, f1, f0
	stfs f1, -0x8000(r4)
	stfs f30, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	stfs f2, -0x8000(r4)
	stfs f30, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	lfs f0, float_2_80420f88(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	stfs f2, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r0, -0x8000(r4)
	lfs f0, float_2_80420f88(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_80420f80(r2)
	stfs f0, -0x8000(r4)
	stfs f1, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r3, -0x8000(r4)
	stb r0, -0x8000(r4)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_80420f80(r2)
	stfs f0, -0x8000(r4)
	lwz r31, 0xc(r28)
	lwz r0, 0xa0(r31)
	cmpwi r0, 0x0
	ble @1
	lfs f1, 0x6c(r31)
	addi r3, r1, 0xc8
	lfs f2, 0x70(r31)
	lfs f3, 0x74(r31)
	bl PSMTXTrans
	lfs f1, float_0p56_80420f8c(r2)
	addi r3, r1, 0x98
	lfs f2, float_0p4_80420f90(r2)
	lfs f3, float_0p8_80420f94(r2)
	bl PSMTXScale
	addi r4, r1, 0xc8
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xc8
	li r4, 0x0
	bl GXLoadPosMtxImm
	lfs f2, float_0_80420f84(r2)
	addi r3, r1, 0xc8
	lfs f1, 0xbc(r31)
	lfs f0, float_0p125_80420f98(r2)
	fmr f3, f2
	fmuls f1, f1, f0
	bl PSMTXTrans
	addi r3, r1, 0xc8
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	lwz r5, dat_80420f68(r2)
	addi r4, r1, 0x10
	lwz r0, 0xa4(r31)
	li r3, 0x1
	stw r5, 0xc(r1)
	stb r0, 0xf(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x10(r1)
	bl GXSetTevColor
	addi r4, r1, 0x18
	li r3, 0x37
	bl effGetTexObj
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadTexObj
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x3
	li r7, 0x8
	bl GXSetVtxAttrFmt
	addi r4, r30, 0x40
	li r3, 0x9
	li r5, 0x6
	bl GXSetArray
	li r3, 0xa
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xa
	li r5, 0x0
	li r6, 0x1
	li r7, 0x6
	bl GXSetVtxAttrFmt
	li r3, 0xa
	la r4, shibuki_normal_tbl(r13)
	li r5, 0x3
	bl GXSetArray
	li r3, 0xb
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0xb
	la r4, shibuki_color0_tbl(r13)
	li r5, 0x4
	bl GXSetArray
	li r3, 0xd
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x3
	li r7, 0xe
	bl GXSetVtxAttrFmt
	addi r4, r30, 0x140
	li r3, 0xd
	li r5, 0x4
	bl GXSetArray
	la r3, shibuki_dl_1_0(r13)
	li r4, 0x20
	bl GXCallDisplayList
	la r3, shibuki_dl_1_1(r13)
	li r4, 0x20
	bl GXCallDisplayList
	la r3, shibuki_dl_1_2(r13)
	li r4, 0x20
	bl GXCallDisplayList
	la r3, shibuki_dl_1_3(r13)
	li r4, 0x20
	bl GXCallDisplayList
	lfs f1, 0x6c(r31)
	addi r3, r1, 0xc8
	lfs f2, 0x70(r31)
	lfs f3, 0x74(r31)
	bl PSMTXTrans
	lfs f2, 0x94(r31)
	addi r3, r1, 0x98
	lfs f0, float_0p8_80420f94(r2)
	lfs f1, float_0p7_80420f9c(r2)
	fmuls f3, f2, f0
	lfs f0, float_0p5_80420f7c(r2)
	fmuls f1, f1, f3
	fmuls f2, f0, f3
	bl PSMTXScale
	addi r4, r1, 0xc8
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xc8
	li r4, 0x0
	bl GXLoadPosMtxImm
	lfs f0, 0xbc(r31)
	addi r3, r1, 0xc8
	lfs f1, float_0_80420f84(r2)
	fneg f2, f0
	lfs f0, float_0p25_80420fa0(r2)
	fmr f3, f1
	fmuls f2, f2, f0
	bl PSMTXTrans
	addi r3, r1, 0xc8
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	lwz r0, dat_80420f6c(r2)
	addi r4, r1, 0x8
	li r3, 0x1
	stw r0, 0x8(r1)
	bl GXSetTevColor
	addi r4, r1, 0x18
	li r3, 0x36
	bl effGetTexObj
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadTexObj
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x3
	li r7, 0x8
	bl GXSetVtxAttrFmt
	addi r4, r30, 0x40
	li r3, 0x9
	li r5, 0x6
	bl GXSetArray
	li r3, 0xa
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xa
	li r5, 0x0
	li r6, 0x1
	li r7, 0x6
	bl GXSetVtxAttrFmt
	li r3, 0xa
	la r4, shibuki_normal_tbl(r13)
	li r5, 0x3
	bl GXSetArray
	li r3, 0xb
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0xb
	la r4, shibuki_color0_tbl(r13)
	li r5, 0x4
	bl GXSetArray
	li r3, 0xd
	li r4, 0x2
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x3
	li r7, 0xe
	bl GXSetVtxAttrFmt
	addi r4, r30, 0x140
	li r3, 0xd
	li r5, 0x4
	bl GXSetArray
	addi r3, r30, 0x1e0
	li r4, 0x40
	bl GXCallDisplayList
	addi r3, r30, 0x220
	li r4, 0x40
	bl GXCallDisplayList
	addi r3, r30, 0x260
	li r4, 0x40
	bl GXCallDisplayList
	addi r3, r30, 0x2a0
	li r4, 0x40
	bl GXCallDisplayList
	@1:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	lmw r27, 0x10c(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void effFallDispInseki(CameraId cameraId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stw r31, 0xec(r1)
	stw r30, 0xe8(r1)
	mr r30, r3
	lwz r31, 0xc(r4)
	bl camGetPtr
	lfs f1, 0x4(r31)
	addi r3, r1, 0xb8
	lfs f2, 0x8(r31)
	lfs f3, 0xc(r31)
	bl PSMTXTrans
	mr r3, r30
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x58
	lfs f0, float_deg2rad_80420f70(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r3, r1, 0xb8
	addi r4, r1, 0x58
	addi r5, r1, 0x28
	bl PSMTXConcat
	lwz r0, 0xc4(r31)
	cmpwi r0, -0x1
	beq @1
	lwz r0, 0xc8(r31)
	cmpwi r0, -0x1
	beq @1
	lfs f1, float_6p2832_80420fa4(r2)
	lis r3, vec3_802fe46c@ha
	lfs f0, 0x80(r31)
	addi r5, r3, vec3_802fe46c@l
	lwz r4, 0x0(r5)
	fmuls f1, f1, f0
	lfs f0, float_360_80420fa8(r2)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	fdivs f1, f1, f0
	stw r4, 0x10(r1)
	stw r3, 0x14(r1)
	stw r0, 0x18(r1)
	bl cos
	lfs f2, float_6p2832_80420fa4(r2)
	frsp f3, f1
	lfs f1, 0x80(r31)
	lfs f0, float_360_80420fa8(r2)
	fmuls f1, f2, f1
	stfs f3, 0x10(r1)
	fdivs f1, f1, f0
	bl sin
	frsp f0, f1
	lwz r0, 0x10(r1)
	lwz r3, 0x14(r1)
	li r30, 0x0
	stw r0, 0x1c(r1)
	stfs f0, 0x18(r1)
	lwz r0, 0x18(r1)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	@2:
	cmpwi r30, 0x0
	bne @3
	lfs f1, 0x6c(r31)
	addi r3, r1, 0xb8
	lfs f2, 0x70(r31)
	lfs f3, 0x74(r31)
	bl PSMTXTrans
	lfs f0, 0xb0(r31)
	addi r3, r1, 0x58
	lfs f1, float_deg2rad_80420f70(r2)
	addi r4, r1, 0x1c
	fneg f0, f0
	fmuls f1, f1, f0
	bl PSMTXRotAxisRad
	lfs f1, float_2p05_80420fac(r2)
	addi r3, r1, 0x88
	lfs f0, 0x94(r31)
	fmuls f1, f1, f0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r4, r1, 0xb8
	addi r3, r1, 0x28
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xb8
	addi r4, r1, 0x58
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xb8
	addi r4, r1, 0x88
	mr r5, r3
	bl PSMTXConcat
	lwz r3, 0xc4(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r0, dat_80420f5c(r2)
	addi r4, r1, 0xc
	stw r0, 0xc(r1)
	lwz r3, 0xc4(r31)
	bl animPoseSetMaterialEvtColor
	b @4
	@3:
	lfs f1, 0x6c(r31)
	addi r3, r1, 0xb8
	lfs f2, 0x70(r31)
	lfs f3, 0x74(r31)
	bl PSMTXTrans
	lfs f0, 0xb0(r31)
	addi r3, r1, 0x58
	lfs f1, float_deg2rad_80420f70(r2)
	addi r4, r1, 0x1c
	fneg f0, f0
	fmuls f1, f1, f0
	bl PSMTXRotAxisRad
	lfs f1, float_2_80420f88(r2)
	addi r3, r1, 0x88
	lfs f0, 0x94(r31)
	fmuls f1, f1, f0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r4, r1, 0xb8
	addi r3, r1, 0x28
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xb8
	addi r4, r1, 0x58
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xb8
	addi r4, r1, 0x88
	mr r5, r3
	bl PSMTXConcat
	lwz r3, 0xc4(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r0, dat_80420f60(r2)
	addi r4, r1, 0x8
	stw r0, 0x8(r1)
	lwz r3, 0xc4(r31)
	bl animPoseSetMaterialEvtColor
	@4:
	lwz r3, 0xc4(r31)
	addi r4, r1, 0xb8
	lfs f1, float_0_80420f84(r2)
	li r5, 0x1
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0xc4(r31)
	addi r4, r1, 0xb8
	lfs f1, float_0_80420f84(r2)
	li r5, 0x2
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0xc4(r31)
	addi r4, r1, 0xb8
	lfs f1, float_0_80420f84(r2)
	li r5, 0x3
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	addi r30, r30, 0x1
	cmpwi r30, 0x2
	blt @2
	lfs f1, 0x6c(r31)
	addi r3, r1, 0xb8
	lfs f2, 0x70(r31)
	lfs f3, 0x74(r31)
	bl PSMTXTrans
	lfs f1, float_2p1_80420fb4(r2)
	addi r3, r1, 0x88
	lfs f0, 0x94(r31)
	fmuls f1, f1, f0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r4, r1, 0xb8
	addi r3, r1, 0x28
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xb8
	addi r4, r1, 0x88
	mr r5, r3
	bl PSMTXConcat
	lwz r3, 0xc8(r31)
	addi r4, r1, 0xb8
	lfs f1, float_0_80420f84(r2)
	li r5, 0x1
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0xc8(r31)
	addi r4, r1, 0xb8
	lfs f1, float_0_80420f84(r2)
	li r5, 0x2
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0xc8(r31)
	addi r4, r1, 0xb8
	lfs f1, float_0_80420f84(r2)
	li r5, 0x3
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	@1:
	lwz r0, 0xf4(r1)
	lwz r31, 0xec(r1)
	lwz r30, 0xe8(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void effFallDisp(CameraId cameraId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0x1a0(r1)
	mflr r0
	stw r0, 0x1a4(r1)
	stfd f31, 0x190(r1)
	psq_st f31, 0x198(r1), 0, 0
	stfd f30, 0x180(r1)
	psq_st f30, 0x188(r1), 0, 0
	stfd f29, 0x170(r1)
	psq_st f29, 0x178(r1), 0, 0
	stfd f28, 0x160(r1)
	psq_st f28, 0x168(r1), 0, 0
	stmw r23, 0x13c(r1)
	mr r27, r4
	mr r23, r3
	lwz r30, 0xc(r4)
	bl camGetPtr
	lwz r28, 0x0(r30)
	mr r31, r3
	lfs f30, 0x18(r30)
	addi r3, r1, 0xf0
	lfs f1, 0x4(r30)
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	mr r3, r23
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x90
	lfs f0, float_deg2rad_80420f70(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	addi r5, r1, 0x60
	bl PSMTXConcat
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x0
	bl GXSetTevOp
	li r3, 0x0
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	cmpwi r28, 0x2
	beq @1
	bge @2
	cmpwi r28, 0x0
	bge @3
	b @2
	@3:
	addi r4, r1, 0x40
	li r3, 0x32
	bl effGetTexObj
	addi r3, r1, 0x40
	li r4, 0x0
	bl GXLoadTexObj
	b @2
	@1:
	addi r4, r1, 0x40
	li r3, 0x33
	bl effGetTexObj
	addi r3, r1, 0x40
	li r4, 0x0
	bl GXLoadTexObj
	@2:
	lfs f0, float_6p2832_80420fa4(r2)
	li r29, 0x1
	addi r30, r30, 0x68
	fmuls f31, f0, f30
	b @4
	@5:
	cmplwi r28, 0x8
	bgt @6
	lis r3, jumptable_803AE000@ha
	slwi r0, r28, 2
	addi r3, r3, jumptable_803AE000@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@7:
	lfs f29, float_64_80420f74(r2)
	addi r3, r1, 0xf0
	lfs f0, float_0p5_80420f7c(r2)
	lfs f28, float_42p667_80420fb8(r2)
	fmuls f29, f29, f0
	lfs f1, 0x4(r30)
	fmuls f28, f28, f0
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	lfs f1, float_deg2rad_80420f70(r2)
	addi r3, r1, 0x90
	lfs f0, 0x18(r30)
	li r4, 0x79
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	lfs f0, float_0p5_80420f7c(r2)
	addi r3, r1, 0x90
	lfs f1, float_0_80420f84(r2)
	fmuls f2, f28, f0
	lfs f0, 0x2c(r30)
	fmr f3, f1
	fmuls f2, f2, f0
	bl PSMTXTrans
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	lfs f1, float_deg2rad_80420f70(r2)
	addi r3, r1, 0x90
	lfs f0, 0x48(r30)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	fneg f3, f28
	lfs f2, float_0p5_80420f7c(r2)
	lfs f1, float_0_80420f84(r2)
	addi r3, r1, 0x90
	lfs f0, 0x2c(r30)
	fmuls f2, f3, f2
	fmr f3, f1
	fmuls f2, f2, f0
	bl PSMTXTrans
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	lfs f1, 0x2c(r30)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0xf0
	addi r3, r1, 0x60
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xf0
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xf0
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r5, dat_80420f48(r2)
	addi r4, r1, 0x24
	lwz r0, 0x3c(r30)
	li r3, 0x4
	stw r5, 0x20(r1)
	stb r0, 0x23(r1)
	lwz r0, 0x20(r1)
	stw r0, 0x24(r1)
	bl GXSetChanMatColor
	lfs f1, float_1_80420f80(r2)
	addi r3, r1, 0xc0
	lfs f2, float_0p33333_80420fbc(r2)
	fmr f3, f1
	bl PSMTXScale
	lwz r3, 0x28(r30)
	lis r0, 0x4330
	lis r4, double_to_int_802fe480@ha
	lfs f1, float_0_80420f84(r2)
	xoris r3, r3, 0x8000
	stw r0, 0x120(r1)
	lfd f2, double_to_int_802fe480@l(r4)
	fmr f3, f1
	stw r3, 0x124(r1)
	addi r3, r1, 0xf0
	lfd f0, 0x120(r1)
	fsubs f2, f0, f2
	bl PSMTXTrans
	addi r4, r1, 0xf0
	addi r3, r1, 0xc0
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xf0
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	fneg f1, f29
	lfs f0, float_0p5_80420f7c(r2)
	lis r3, 0xcc01
	fmuls f2, f29, f0
	fmuls f1, f1, f0
	stfs f1, -0x8000(r3)
	stfs f28, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	stfs f2, -0x8000(r3)
	stfs f28, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_80420f80(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	stfs f2, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_80420f80(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_80420f80(r2)
	stfs f0, -0x8000(r3)
	stfs f1, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_80420f84(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_80420f80(r2)
	stfs f0, -0x8000(r3)
	b @6
	@8:
	lfs f1, 0x4(r30)
	addi r3, r1, 0xf0
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	lfs f1, 0x2c(r30)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0xf0
	addi r3, r1, 0x60
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xf0
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xf0
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r5, dat_80420f4c(r2)
	addi r4, r1, 0x1c
	lwz r0, 0x3c(r30)
	li r3, 0x4
	stw r5, 0x18(r1)
	stb r0, 0x1b(r1)
	lwz r0, 0x18(r1)
	stw r0, 0x1c(r1)
	bl GXSetChanMatColor
	addi r3, r1, 0xf0
	bl PSMTXIdentity
	addi r3, r1, 0xf0
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r24, 0x0
	li r25, 0x0
	lis r26, 0xcc01
	@9:
	lwz r6, 0x40(r30)
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	lwz r0, 0x0(r6)
	add r23, r0, r25
	bl GXBegin
	lfs f2, 0x8(r23)
	addi r24, r24, 0x2
	lfs f1, 0x4(r23)
	cmpwi r24, 0x1e
	lfs f0, 0x0(r23)
	addi r25, r25, 0x28
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	stfs f2, -0x8000(r26)
	lfs f1, 0x10(r23)
	lfs f0, 0xc(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	lfs f2, 0x30(r23)
	lfs f1, 0x2c(r23)
	lfs f0, 0x28(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	stfs f2, -0x8000(r26)
	lfs f1, 0x38(r23)
	lfs f0, 0x34(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	lfs f2, 0x44(r23)
	lfs f1, 0x40(r23)
	lfs f0, 0x3c(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	stfs f2, -0x8000(r26)
	lfs f1, 0x4c(r23)
	lfs f0, 0x48(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	lfs f2, 0x1c(r23)
	lfs f1, 0x18(r23)
	lfs f0, 0x14(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	stfs f2, -0x8000(r26)
	lfs f1, 0x24(r23)
	lfs f0, 0x20(r23)
	stfs f0, -0x8000(r26)
	stfs f1, -0x8000(r26)
	blt @9
	b @6
	@10:
	lfs f0, float_360_80420fa8(r2)
	lis r3, vec3_802fe460@ha
	addi r5, r3, vec3_802fe460@l
	fdivs f28, f31, f0
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x28(r1)
	stw r3, 0x2c(r1)
	fmr f1, f28
	stw r0, 0x30(r1)
	bl cos
	frsp f0, f1
	fmr f1, f28
	stfs f0, 0x28(r1)
	bl sin
	frsp f0, f1
	lwz r0, 0x28(r1)
	lwz r4, 0x2c(r1)
	addi r3, r1, 0xf0
	stw r0, 0x34(r1)
	stfs f0, 0x30(r1)
	lwz r0, 0x30(r1)
	stw r4, 0x38(r1)
	stw r0, 0x3c(r1)
	lfs f1, 0x4(r30)
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	lfs f1, 0x2c(r30)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	cmpwi r28, 0x4
	lfs f1, float_0_80420f84(r2)
	addi r3, r1, 0xc0
	li r0, 0x10
	bne @11
	li r0, 0x8
	@11:
	xoris r4, r0, 0x8000
	lis r0, 0x4330
	stw r4, 0x124(r1)
	lis r5, double_to_int_802fe480@ha
	lfd f2, double_to_int_802fe480@l(r5)
	stw r0, 0x120(r1)
	lfs f3, float_0_80420f84(r2)
	lfd f0, 0x120(r1)
	fsubs f2, f0, f2
	bl PSMTXTrans
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0x48(r30)
	addi r3, r1, 0x90
	lfs f1, float_deg2rad_80420f70(r2)
	addi r4, r1, 0x34
	fneg f0, f0
	fmuls f1, f1, f0
	bl PSMTXRotAxisRad
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	cmpwi r28, 0x4
	lfs f1, float_0_80420f84(r2)
	addi r3, r1, 0xc0
	li r0, 0x10
	bne @12
	li r0, 0x8
	@12:
	neg r4, r0
	lis r0, 0x4330
	xoris r4, r4, 0x8000
	lis r5, double_to_int_802fe480@ha
	stw r4, 0x12c(r1)
	lfd f2, double_to_int_802fe480@l(r5)
	stw r0, 0x128(r1)
	lfs f3, float_0_80420f84(r2)
	lfd f0, 0x128(r1)
	fsubs f2, f0, f2
	bl PSMTXTrans
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0xf0
	addi r3, r1, 0x60
	mr r5, r4
	bl PSMTXConcat
	lwz r3, 0x5c(r30)
	cmpwi r3, -0x1
	beq @6
	lfs f1, float_0_80420f84(r2)
	addi r4, r1, 0xf0
	lfs f2, float_10_80420fb0(r2)
	li r5, 0x1
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x2
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x3
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	b @6
	@13:
	lwz r0, 0x5c(r30)
	cmpwi r0, -0x1
	beq @6
	lfs f1, 0x4(r30)
	addi r3, r1, 0xf0
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	lfs f0, float_180_80420fc0(r2)
	fcmpo cr0, f30, f0
	bge @14
	lfs f1, 0x2c(r30)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	b @15
	@14:
	lfs f2, 0x2c(r30)
	addi r3, r1, 0xc0
	fmr f3, f2
	fneg f1, f2
	bl PSMTXScale
	@15:
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0x48(r30)
	lfs f2, float_0_80420f84(r2)
	fcmpu cr0, f0, f2
	beq @16
	fneg f0, f0
	lfs f1, float_deg2rad_80420f70(r2)
	addi r3, r1, 0x90
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	b @17
	@16:
	fmr f3, f2
	lfs f1, float_neg200_80420fc4(r2)
	addi r3, r1, 0xc0
	bl PSMTXTrans
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0x4c(r30)
	addi r3, r1, 0x90
	lfs f1, float_deg2rad_80420f70(r2)
	li r4, 0x7a
	fneg f0, f0
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0xf0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	lfs f2, float_0_80420f84(r2)
	addi r3, r1, 0xc0
	lfs f1, float_200_80420fc8(r2)
	fmr f3, f2
	bl PSMTXTrans
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	@17:
	addi r4, r1, 0xf0
	addi r3, r1, 0x60
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_neg82p655_80420fcc(r2)
	addi r3, r1, 0xc0
	lfs f2, float_88p8_80420fd0(r2)
	lfs f3, float_0_80420f84(r2)
	bl PSMTXTrans
	addi r4, r1, 0xc0
	addi r3, r1, 0xf0
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_1p03_80420fd4(r2)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r4, r1, 0x90
	addi r3, r1, 0xc0
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_82p655_80420fd8(r2)
	addi r3, r1, 0xc0
	lfs f2, float_neg88p8_80420fdc(r2)
	lfs f3, float_0_80420f84(r2)
	bl PSMTXTrans
	addi r4, r1, 0xc0
	addi r3, r1, 0x90
	mr r5, r4
	bl PSMTXConcat
	lwz r3, 0x5c(r30)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r0, dat_80420f50(r2)
	addi r4, r1, 0x14
	stw r0, 0x14(r1)
	lwz r3, 0x5c(r30)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xc0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x1
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xc0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x2
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xc0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x3
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r0, dat_80420f54(r2)
	addi r4, r1, 0x10
	stw r0, 0x10(r1)
	lwz r3, 0x5c(r30)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x1
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x2
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x3
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	b @6
	@18:
	lwz r0, 0x5c(r30)
	cmpwi r0, -0x1
	beq @6
	lfs f1, 0x4(r30)
	addi r3, r1, 0xf0
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	lfs f1, 0x2c(r30)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0xf0
	addi r3, r1, 0x60
	mr r5, r4
	bl PSMTXConcat
	lwz r3, 0x5c(r30)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r3, dat_80420f58(r2)
	addi r4, r1, 0xc
	lwz r0, 0x3c(r30)
	stw r3, 0x8(r1)
	stb r0, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	lwz r3, 0x5c(r30)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x1
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x2
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	lwz r3, 0x5c(r30)
	addi r4, r1, 0xf0
	lfs f1, float_0_80420f84(r2)
	li r5, 0x3
	lfs f2, float_10_80420fb0(r2)
	bl animPoseDrawMtx
	@6:
	addi r29, r29, 0x1
	addi r30, r30, 0x68
	@4:
	lwz r0, 0x8(r27)
	cmpw r29, r0
	blt @5
	psq_l f31, 0x198(r1), 0, 0
	lfd f31, 0x190(r1)
	psq_l f30, 0x188(r1), 0, 0
	lfd f30, 0x180(r1)
	psq_l f29, 0x178(r1), 0, 0
	lfd f29, 0x170(r1)
	psq_l f28, 0x168(r1), 0, 0
	lfd f28, 0x160(r1)
	lmw r23, 0x13c(r1)
	lwz r0, 0x1a4(r1)
	mtlr r0
	addi r1, r1, 0x1a0
	blr
}

asm void effFallMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	stfd f31, 0x110(r1)
	psq_st f31, 0x118(r1), 0, 0
	stfd f30, 0x100(r1)
	psq_st f30, 0x108(r1), 0, 0
	stfd f29, 0xf0(r1)
	psq_st f29, 0xf8(r1), 0, 0
	stfd f28, 0xe0(r1)
	psq_st f28, 0xe8(r1), 0, 0
	stfd f27, 0xd0(r1)
	psq_st f27, 0xd8(r1), 0, 0
	stfd f26, 0xc0(r1)
	psq_st f26, 0xc8(r1), 0, 0
	stmw r15, 0x7c(r1)
	lis r4, vec3_802fe418@ha
	lwz r26, 0xc(r3)
	addi r31, r4, vec3_802fe418@l
	mr r19, r3
	lwz r4, 0xc(r31)
	li r22, 0x0
	lwz r3, 0x10(r31)
	lwz r0, 0x14(r31)
	stw r4, 0x8(r1)
	lfs f0, 0x4(r26)
	stw r3, 0xc(r1)
	lfs f31, 0x8(r26)
	stfs f0, 0x8(r1)
	lfs f0, 0xc(r26)
	stw r0, 0x10(r1)
	lwz r5, 0x8(r1)
	stfs f31, 0xc(r1)
	lwz r4, gp(r13)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r5, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r3, 0x0(r19)
	lfs f0, 0x14(r26)
	lwz r4, 0x14(r4)
	rlwinm. r0, r3, 0, 29, 29
	fadds f27, f31, f0
	lwz r24, 0x0(r26)
	neg r0, r4
	lfs f28, 0x10(r26)
	or r0, r0, r4
	lfs f2, 0x18(r26)
	lwz r23, 0x20(r26)
	srwi r20, r0, 31
	beq @1
	rlwinm r0, r3, 0, 30, 28
	li r16, 0x0
	stw r0, 0x0(r19)
	lwz r15, 0xc(r19)
	b @2
	@3:
	lwz r3, 0x5c(r15)
	cmpwi r3, -0x1
	beq @4
	bl animPoseRelease
	@4:
	lwz r3, 0x60(r15)
	cmpwi r3, -0x1
	beq @5
	bl animPoseRelease
	@5:
	lwz r3, 0x64(r15)
	bl psndSFXOff
	addi r16, r16, 0x1
	addi r15, r15, 0x68
	@2:
	lwz r0, 0x8(r19)
	cmpw r16, r0
	blt @3
	mr r3, r19
	bl effDelete
	b @6
	@1:
	lfs f1, float_6p2832_80420fa4(r2)
	addi r0, r31, 0x70
	lfs f0, float_30_80420fe0(r2)
	addi r29, r31, 0xbc
	stw r0, 0x6c(r1)
	addi r0, r31, 0xa0
	fmuls f30, f1, f2
	addi r30, r31, 0x88
	fadds f29, f0, f31
	stw r0, 0x68(r1)
	addi r15, r31, 0xd8
	addi r28, r31, 0xf4
	addi r27, r31, 0x114
	li r21, 0x0
	li r25, 0x1
	addi r26, r26, 0x68
	b @7
	@8:
	cmplwi r24, 0x8
	bgt @9
	lis r3, jumptable_803AE04C@ha
	slwi r0, r24, 2
	addi r3, r3, jumptable_803AE04C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@10:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x3
	beq @11
	bge @12
	cmpwi r0, 0x1
	beq @13
	bge @14
	cmpwi r0, 0x0
	bge @15
	b @16
	@12:
	cmpwi r0, 0x5
	beq @17
	bge @16
	b @18
	@15:
	lwz r3, 0x24(r26)
	cmpwi r3, 0x0
	beq @19
	subi r0, r3, 0x1
	stw r0, 0x24(r26)
	@19:
	lwz r0, 0x24(r26)
	cmpwi r0, 0x0
	bne @16
	lwz r3, 0x38(r26)
	cmpwi r24, 0x1
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	bne @20
	lwz r3, 0x6c(r1)
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	b @16
	@20:
	cmpwi r25, 0x1
	bne @16
	mr r3, r30
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	b @16
	@13:
	cmpwi r24, 0x0
	bne @21
	cmpwi r25, 0x1
	ble @21
	cmpwi r22, 0x0
	bne @21
	lwz r4, gp(r13)
	lis r3, 0xaaab
	subi r0, r3, 0x5555
	lwz r3, 0x1c(r4)
	mulhwu r0, r0, r3
	srwi r0, r0, 2
	mulli r0, r0, 0x6
	subf. r0, r0, r3
	bne @21
	mr r3, r30
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	li r22, 0x1
	@21:
	lfs f1, 0x8(r26)
	lfs f0, 0x34(r26)
	lfs f3, float_0_80420f84(r2)
	fadds f0, f1, f0
	fmr f4, f3
	stfs f0, 0x8(r26)
	lfs f1, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f1, f0
	stfs f0, 0x34(r26)
	lfs f1, 0x4(r26)
	lfs f2, 0xc(r26)
	bl distABf
	lfs f0, float_0p5_80420f7c(r2)
	fmuls f0, f28, f0
	fcmpo cr0, f1, f0
	bge @22
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f27
	bge @16
	stfs f27, 0x8(r26)
	lfs f0, float_neg0p3_80420fe4(r2)
	lfs f1, 0x34(r26)
	fmuls f0, f1, f0
	stfs f0, 0x34(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @16
	@22:
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @16
	stfs f31, 0x8(r26)
	lfs f0, float_neg0p3_80420fe4(r2)
	lfs f1, 0x34(r26)
	fmuls f0, f1, f0
	stfs f0, 0x34(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @16
	@14:
	lfs f2, 0x8(r26)
	lfs f0, 0x34(r26)
	lfs f1, float_0_80420f84(r2)
	fadds f0, f2, f0
	fmr f2, f1
	stfs f0, 0x8(r26)
	lfs f3, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f3, f0
	stfs f0, 0x34(r26)
	lfs f3, 0x4(r26)
	lfs f4, 0xc(r26)
	bl angleABf
	lfs f2, float_6p2832_80420fa4(r2)
	cmpwi r25, 0x1
	lfs f0, float_360_80420fa8(r2)
	fmuls f1, f2, f1
	fdivs f26, f1, f0
	bne @23
	fdivs f26, f30, f0
	@23:
	fmr f1, f26
	bl sin
	frsp f3, f1
	lfs f2, float_0p5_80420f7c(r2)
	lfs f0, 0x4(r26)
	fmr f1, f26
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r26)
	bl cos
	frsp f1, f1
	lfs f2, float_0p5_80420f7c(r2)
	lfs f0, 0xc(r26)
	fneg f1, f1
	fmadds f0, f2, f1, f0
	stfs f0, 0xc(r26)
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @16
	stfs f31, 0x8(r26)
	li r0, 0x0
	stw r0, 0x24(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @16
	@11:
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0x1e
	ble @16
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @16
	@18:
	lwz r3, 0x3c(r26)
	subi r0, r3, 0xa
	stw r0, 0x3c(r26)
	lwz r0, 0x3c(r26)
	cmpwi r0, 0x0
	bge @16
	li r0, 0x0
	stw r0, 0x3c(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @16
	@17:
	addi r21, r21, 0x1
	@16:
	lwz r3, gp(r13)
	lwz r0, 0x1c(r3)
	extrwi. r0, r0, 1, 29
	beq @24
	lwz r3, 0x28(r26)
	addi r0, r3, 0x1
	stw r0, 0x28(r26)
	@24:
	lwz r0, 0x28(r26)
	cmpwi r0, 0x3
	blt @25
	li r0, 0x0
	stw r0, 0x28(r26)
	@25:
	lwz r4, gp(r13)
	lis r3, 0x4330
	xoris r0, r25, 0x8000
	stw r3, 0x50(r1)
	lwz r4, 0x1c(r4)
	stw r0, 0x5c(r1)
	lfd f3, 0x60(r31)
	stw r4, 0x54(r1)
	lfd f1, 0x68(r31)
	stw r3, 0x58(r1)
	lfd f2, 0x50(r1)
	lfd f0, 0x58(r1)
	fsubs f3, f2, f3
	lfs f2, float_0p5_80420f7c(r2)
	fsubs f0, f0, f1
	fmadds f1, f3, f2, f0
	bl sin
	frsp f1, f1
	lfs f0, float_35_80420fe8(r2)
	fmuls f0, f0, f1
	stfs f0, 0x48(r26)
	b @9
	@26:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x2
	beq @27
	bge @28
	cmpwi r0, 0x0
	beq @29
	bge @30
	b @31
	@28:
	cmpwi r0, 0x4
	beq @32
	bge @31
	b @33
	@29:
	lfs f1, 0x8(r26)
	lfs f0, 0x34(r26)
	fadds f0, f1, f0
	stfs f0, 0x8(r26)
	lfs f1, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f1, f0
	stfs f0, 0x34(r26)
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @31
	stfs f31, 0x8(r26)
	li r0, 0x0
	lwz r3, 0x68(r1)
	addi r4, r1, 0x14
	stw r0, 0x24(r26)
	lwz r5, 0x38(r26)
	addi r0, r5, 0x1
	stw r0, 0x38(r26)
	bl psndSFXOn_3D
	b @31
	@30:
	lwz r3, 0x24(r26)
	lis r0, 0x4330
	stw r0, 0x58(r1)
	xoris r0, r3, 0x8000
	lfd f2, 0x68(r31)
	stw r0, 0x5c(r1)
	lfs f3, float_62p832_80420fec(r2)
	lfd f1, 0x58(r1)
	lfs f0, float_60_80420ff0(r2)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl sin
	lwz r3, 0x24(r26)
	lis r0, 0x4330
	stw r0, 0x50(r1)
	frsp f3, f1
	xoris r0, r3, 0x8000
	lfd f1, 0x68(r31)
	stw r0, 0x54(r1)
	lfs f2, float_60_80420ff0(r2)
	lfd f0, 0x50(r1)
	fsubs f0, f0, f1
	fsubs f0, f2, f0
	fmuls f0, f0, f3
	fdivs f0, f0, f2
	stfs f0, 0x44(r26)
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0x3c
	ble @31
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @31
	@27:
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0x1e
	ble @31
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @31
	@33:
	lwz r3, 0x3c(r26)
	subi r0, r3, 0xa
	stw r0, 0x3c(r26)
	lwz r0, 0x3c(r26)
	cmpwi r0, 0x0
	bge @31
	li r0, 0x0
	stw r0, 0x3c(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @31
	@32:
	addi r21, r21, 0x1
	@31:
	li r3, 0x280
	li r4, 0x3
	bl smartAlloc
	stw r3, 0x40(r26)
	li r0, 0x10
	lfs f6, float_8p5333_80421000(r2)
	li r5, 0x0
	lwz r4, 0x40(r26)
	lis r3, 0x4330
	lfd f5, 0x68(r31)
	lwz r6, 0x0(r4)
	lfs f4, float_128_80420ffc(r2)
	lfs f3, float_0_80420f84(r2)
	lfs f1, float_0p066667_80421004(r2)
	mtctr r0
	@34:
	clrlwi. r4, r5, 31
	beq @35
	lfs f0, float_16_80420ff4(r2)
	b @36
	@35:
	lfs f0, float_neg16_80420ff8(r2)
	@36:
	srwi r0, r5, 31
	stw r3, 0x58(r1)
	add r0, r0, r5
	cmpwi r4, 0x0
	srawi r4, r0, 1
	stfs f0, 0x0(r6)
	xoris r0, r4, 0x8000
	stw r0, 0x5c(r1)
	lfd f0, 0x58(r1)
	fsubs f0, f0, f5
	fnmsubs f0, f6, f0, f4
	stfs f0, 0x4(r6)
	stfs f3, 0x8(r6)
	beq @37
	lfs f2, float_2_80420f88(r2)
	b @38
	@37:
	fmr f2, f3
	@38:
	xoris r0, r4, 0x8000
	addi r5, r5, 0x1
	stw r0, 0x54(r1)
	clrlwi. r4, r5, 31
	stw r3, 0x50(r1)
	lfd f0, 0x50(r1)
	stfs f2, 0xc(r6)
	fsubs f0, f0, f5
	fmuls f0, f1, f0
	stfs f0, 0x10(r6)
	beq @39
	lfs f0, float_16_80420ff4(r2)
	b @40
	@39:
	lfs f0, float_neg16_80420ff8(r2)
	@40:
	srwi r0, r5, 31
	stw r3, 0x58(r1)
	add r0, r0, r5
	cmpwi r4, 0x0
	srawi r4, r0, 1
	stfs f0, 0x14(r6)
	xoris r0, r4, 0x8000
	stw r0, 0x5c(r1)
	lfd f0, 0x58(r1)
	fsubs f0, f0, f5
	fnmsubs f0, f6, f0, f4
	stfs f0, 0x18(r6)
	stfs f3, 0x1c(r6)
	beq @41
	lfs f2, float_2_80420f88(r2)
	b @42
	@41:
	fmr f2, f3
	@42:
	xoris r0, r4, 0x8000
	stw r3, 0x50(r1)
	addi r5, r5, 0x1
	stw r0, 0x54(r1)
	lfd f0, 0x50(r1)
	stfs f2, 0x20(r6)
	fsubs f0, f0, f5
	fmuls f0, f1, f0
	stfs f0, 0x24(r6)
	addi r6, r6, 0x28
	bdnz @34
	lwz r3, 0x40(r26)
	li r0, 0x8
	lfs f2, float_600_80421008(r2)
	li r25, 0x0
	lwz r3, 0x0(r3)
	mtctr r0
	@43:
	lfs f0, 0x4(r3)
	addi r25, r25, 0x4
	lfs f3, 0x44(r26)
	fmuls f1, f0, f0
	lfs f0, 0x0(r3)
	fdivs f1, f1, f2
	fmadds f0, f3, f1, f0
	stfs f0, 0x0(r3)
	lfs f0, 0x18(r3)
	lfs f3, 0x44(r26)
	fmuls f1, f0, f0
	lfs f0, 0x14(r3)
	fdivs f1, f1, f2
	fmadds f0, f3, f1, f0
	stfs f0, 0x14(r3)
	lfs f0, 0x2c(r3)
	lfs f3, 0x44(r26)
	fmuls f1, f0, f0
	lfs f0, 0x28(r3)
	fdivs f1, f1, f2
	fmadds f0, f3, f1, f0
	stfs f0, 0x28(r3)
	lfs f0, 0x40(r3)
	lfs f3, 0x44(r26)
	fmuls f1, f0, f0
	lfs f0, 0x3c(r3)
	fdivs f1, f1, f2
	fmadds f0, f3, f1, f0
	stfs f0, 0x3c(r3)
	addi r3, r3, 0x50
	bdnz @43
	lwz r3, 0x40(r26)
	li r4, 0x280
	lwz r3, 0x0(r3)
	bl DCFlushRange
	b @9
	@44:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x1
	beq @45
	bge @46
	cmpwi r0, 0x0
	bge @47
	b @48
	@46:
	cmpwi r0, 0x3
	bge @48
	b @49
	@47:
	lfs f1, 0x8(r26)
	lfs f0, 0x34(r26)
	fadds f0, f1, f0
	stfs f0, 0x8(r26)
	lfs f1, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f1, f0
	stfs f0, 0x34(r26)
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @48
	stfs f31, 0x8(r26)
	li r0, 0x0
	stw r0, 0x24(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @48
	@45:
	lis r3, 0x6666
	lwz r4, 0x24(r26)
	addi r0, r3, 0x6667
	mulhw r0, r0, r4
	srawi r0, r0, 2
	srwi r3, r0, 31
	add r0, r0, r3
	mulli r0, r0, 0xa
	subf. r0, r0, r4
	bne @50
	lfs f1, 0x14(r1)
	li r3, 0x4
	lfs f2, 0x18(r1)
	li r4, 0x14
	lfs f3, 0x1c(r1)
	lfs f4, float_1_80420f80(r2)
	bl effWaterDamageN64Entry
	@50:
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpw r0, r23
	ble @48
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @48
	@49:
	lwz r3, 0x3c(r26)
	lis r0, 0x4330
	stw r0, 0x58(r1)
	xoris r0, r3, 0x8000
	lfd f3, 0x68(r31)
	stw r0, 0x5c(r1)
	lfs f2, float_0p9_8042100c(r2)
	lfd f1, 0x58(r1)
	lfs f0, float_0p01_80421010(r2)
	fsubs f1, f1, f3
	fmuls f1, f1, f2
	fctiwz f1, f1
	stfd f1, 0x50(r1)
	lwz r0, 0x54(r1)
	stw r0, 0x3c(r26)
	lfs f1, 0x2c(r26)
	fmuls f1, f1, f2
	stfs f1, 0x2c(r26)
	lfs f1, 0x2c(r26)
	fcmpo cr0, f1, f0
	bge @48
	lwz r3, 0x64(r26)
	bl psndSFXOff
	mr r3, r19
	bl effDelete
	b @6
	@48:
	lfs f1, 0x54(r26)
	lfs f0, float_0p2_80421014(r2)
	fsubs f0, f1, f0
	stfs f0, 0x54(r26)
	b @9
	@51:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x3
	beq @52
	bge @53
	cmpwi r0, 0x1
	beq @54
	bge @55
	cmpwi r0, 0x0
	bge @56
	b @57
	@53:
	cmpwi r0, 0x5
	beq @58
	bge @57
	b @59
	@56:
	cmpwi r24, 0x5
	bne @60
	mr r4, r20
	addi r3, r31, 0x130
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @57
	lwz r0, 0x5c(r26)
	cmpwi r0, -0x1
	bne @61
	mr r4, r20
	addi r3, r31, 0x130
	bl animPoseEntry
	stw r3, 0x5c(r26)
	la r4, str_80421018(r2)
	li r5, 0x1
	lwz r3, 0x5c(r26)
	bl animPoseSetAnim
	b @61
	@60:
	mr r4, r20
	addi r3, r31, 0x13c
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @57
	lwz r0, 0x5c(r26)
	cmpwi r0, -0x1
	bne @61
	mr r4, r20
	addi r3, r31, 0x13c
	bl animPoseEntry
	stw r3, 0x5c(r26)
	la r4, str_80421018(r2)
	li r5, 0x1
	lwz r3, 0x5c(r26)
	bl animPoseSetAnim
	@61:
	lwz r3, 0x24(r26)
	cmpwi r3, 0x0
	beq @62
	subi r0, r3, 0x1
	stw r0, 0x24(r26)
	@62:
	lwz r0, 0x24(r26)
	cmpwi r0, 0x0
	bne @57
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @57
	@54:
	lfs f1, 0x8(r26)
	lfs f0, 0x34(r26)
	lfs f3, float_0_80420f84(r2)
	fadds f0, f1, f0
	fmr f4, f3
	stfs f0, 0x8(r26)
	lfs f1, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f1, f0
	stfs f0, 0x34(r26)
	lfs f1, 0x4(r26)
	lfs f2, 0xc(r26)
	bl distABf
	lfs f0, float_0p5_80420f7c(r2)
	fmuls f0, f28, f0
	fcmpo cr0, f1, f0
	bge @63
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f27
	bge @57
	stfs f27, 0x8(r26)
	lfs f0, float_neg0p3_80420fe4(r2)
	lfs f1, 0x34(r26)
	fmuls f0, f1, f0
	stfs f0, 0x34(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @57
	@63:
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @57
	stfs f31, 0x8(r26)
	lfs f0, float_neg0p3_80420fe4(r2)
	lfs f1, 0x34(r26)
	fmuls f0, f1, f0
	stfs f0, 0x34(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @57
	@55:
	lfs f2, 0x8(r26)
	lfs f0, 0x34(r26)
	lfs f1, float_0_80420f84(r2)
	fadds f0, f2, f0
	fmr f2, f1
	stfs f0, 0x8(r26)
	lfs f3, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f3, f0
	stfs f0, 0x34(r26)
	lfs f3, 0x4(r26)
	lfs f4, 0xc(r26)
	bl angleABf
	lfs f2, float_6p2832_80420fa4(r2)
	cmpwi r25, 0x1
	lfs f0, float_360_80420fa8(r2)
	fmuls f1, f2, f1
	fdivs f26, f1, f0
	bne @64
	fdivs f26, f30, f0
	@64:
	fmr f1, f26
	bl sin
	frsp f3, f1
	lfs f2, float_2_80420f88(r2)
	lfs f0, 0x4(r26)
	fmr f1, f26
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r26)
	bl cos
	frsp f1, f1
	lfs f2, float_2_80420f88(r2)
	lfs f0, 0xc(r26)
	fneg f1, f1
	fmadds f0, f2, f1, f0
	stfs f0, 0xc(r26)
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @57
	stfs f31, 0x8(r26)
	li r0, 0x0
	lfs f1, float_neg0p5_8042101c(r2)
	lfs f2, 0x34(r26)
	lfs f0, float_1_80420f80(r2)
	fmuls f1, f2, f1
	stfs f1, 0x34(r26)
	stfs f31, 0x8(r26)
	stw r0, 0x24(r26)
	lfs f1, 0x34(r26)
	fcmpo cr0, f1, f0
	bge @57
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @57
	@52:
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0x1e
	ble @57
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @57
	@59:
	lwz r3, 0x3c(r26)
	subi r0, r3, 0xa
	stw r0, 0x3c(r26)
	lwz r0, 0x3c(r26)
	cmpwi r0, 0x0
	bge @57
	li r0, 0x0
	stw r0, 0x3c(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	lwz r3, 0x5c(r26)
	bl animPoseRelease
	li r0, -0x1
	stw r0, 0x5c(r26)
	b @57
	@58:
	addi r21, r21, 0x1
	@57:
	cmpwi r24, 0x5
	beq @65
	bge @66
	cmpwi r24, 0x4
	bge @67
	b @66
	@67:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x1
	ble @66
	lfs f2, 0x48(r26)
	lfs f1, float_360_80420fa8(r2)
	lfs f0, float_10_80420fb0(r2)
	fsubs f1, f1, f2
	fdivs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x48(r26)
	b @66
	@65:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x1
	ble @66
	lfs f2, 0x48(r26)
	lfs f1, float_430_80421020(r2)
	lfs f0, float_10_80420fb0(r2)
	fsubs f1, f1, f2
	fdivs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x48(r26)
	@66:
	lwz r3, 0x5c(r26)
	cmpwi r3, -0x1
	beq @9
	bl animPoseMain
	b @9
	@68:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x1
	beq @69
	bge @70
	cmpwi r0, 0x0
	bge @71
	b @72
	@70:
	cmpwi r0, 0x3
	bge @72
	b @73
	@71:
	mr r4, r20
	addi r3, r31, 0x148
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @72
	lwz r0, 0x5c(r26)
	cmpwi r0, -0x1
	bne @74
	mr r4, r20
	addi r3, r31, 0x148
	bl animPoseEntry
	stw r3, 0x5c(r26)
	la r4, str_80421018(r2)
	li r5, 0x1
	lwz r3, 0x5c(r26)
	bl animPoseSetAnim
	mr r3, r29
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	@74:
	lfs f1, 0x4(r26)
	lfs f0, 0x50(r26)
	fadds f0, f1, f0
	stfs f0, 0x4(r26)
	lfs f1, 0x8(r26)
	lfs f0, 0x54(r26)
	fadds f0, f1, f0
	stfs f0, 0x8(r26)
	lfs f1, 0xc(r26)
	lfs f0, 0x58(r26)
	fadds f0, f1, f0
	stfs f0, 0xc(r26)
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0x1e
	ble @72
	li r0, 0x0
	lfs f4, float_0_80420f84(r2)
	stw r0, 0x24(r26)
	li r3, 0x4
	lwz r4, 0x38(r26)
	addi r0, r4, 0x1
	stw r0, 0x38(r26)
	lfs f1, 0x14(r1)
	lfs f0, 0x4(r26)
	lfs f5, 0x18(r1)
	lfs f2, 0x8(r26)
	fadds f1, f1, f0
	lfs f3, 0x1c(r1)
	lfs f0, 0xc(r26)
	fadds f2, f5, f2
	fadds f3, f3, f0
	bl effKemuri1N64Entry
	la r3, evt_shake(r13)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	b @72
	@69:
	lfs f1, float_30_80420fe0(r2)
	li r3, 0xb
	lfs f2, float_neg27_80421024(r2)
	li r5, 0xb4
	lwz r4, 0x24(r26)
	bl intplGetValue
	stfs f1, 0x48(r26)
	lfs f0, float_0_80420f84(r2)
	lfs f1, 0x48(r26)
	fcmpo cr0, f1, f0
	bge @75
	stfs f1, 0x4c(r26)
	stfs f0, 0x48(r26)
	@75:
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0xb4
	ble @76
	li r0, 0x0
	stw r0, 0x24(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	@76:
	lwz r0, 0x24(r26)
	cmpwi r0, 0x64
	bne @72
	mr r3, r29
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	b @72
	@73:
	lfs f1, float_neg27_80421024(r2)
	li r3, 0xb
	lfs f2, float_80_80421028(r2)
	li r5, 0xc8
	lwz r4, 0x24(r26)
	bl intplGetValue
	stfs f1, 0x48(r26)
	lfs f0, float_0_80420f84(r2)
	lfs f1, 0x48(r26)
	fcmpo cr0, f1, f0
	bge @77
	stfs f1, 0x4c(r26)
	stfs f0, 0x48(r26)
	@77:
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0xc8
	ble @78
	lwz r3, 0x5c(r26)
	bl animPoseRelease
	li r0, -0x1
	addi r21, r21, 0x1
	stw r0, 0x5c(r26)
	@78:
	lwz r0, 0x24(r26)
	cmpwi r0, 0x46
	bne @72
	mr r3, r29
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	@72:
	lwz r3, 0x5c(r26)
	cmpwi r3, -0x1
	beq @9
	bl animPoseMain
	b @9
	@79:
	lwz r0, 0x38(r26)
	cmplwi r0, 0x9
	bgt @80
	lis r3, jumptable_803AE024@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_803AE024@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@81:
	mr r4, r20
	addi r3, r31, 0x154
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @80
	mr r3, r15
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	lwz r0, 0x5c(r26)
	cmpwi r0, -0x1
	bne @82
	mr r4, r20
	addi r3, r31, 0x154
	bl animPoseEntry
	stw r3, 0x5c(r26)
	la r4, str_80421018(r2)
	li r5, 0x1
	lwz r3, 0x5c(r26)
	bl animPoseSetAnim
	@82:
	lwz r0, 0x60(r26)
	cmpwi r0, -0x1
	bne @83
	mr r4, r20
	addi r3, r31, 0x154
	bl animPoseEntry
	stw r3, 0x60(r26)
	la r4, str_8042102C(r2)
	li r5, 0x1
	lwz r3, 0x60(r26)
	bl animPoseSetAnim
	@83:
	lwz r4, 0x38(r26)
	addi r3, r1, 0x20
	lwz r16, 0x18(r31)
	srwi r0, r4, 31
	lwz r17, 0x1c(r31)
	add r0, r0, r4
	lwz r18, 0x20(r31)
	srawi r0, r0, 1
	lwz r12, 0x24(r31)
	lwz r11, 0x28(r31)
	mulli r0, r0, 0xc
	lwz r10, 0x2c(r31)
	lwz r9, 0x30(r31)
	lwz r8, 0x34(r31)
	lwz r7, 0x38(r31)
	lwz r6, 0x3c(r31)
	lwz r5, 0x40(r31)
	lwz r4, 0x44(r31)
	stw r16, 0x20(r1)
	lfs f0, float_0p4_80420f90(r2)
	stw r17, 0x24(r1)
	stw r18, 0x28(r1)
	stw r12, 0x2c(r1)
	stw r11, 0x30(r1)
	stw r10, 0x34(r1)
	stw r9, 0x38(r1)
	stw r8, 0x3c(r1)
	stw r7, 0x40(r1)
	stw r6, 0x44(r1)
	stw r5, 0x48(r1)
	stw r4, 0x4c(r1)
	lfsx f1, r3, r0
	stfs f1, 0x50(r26)
	lwz r4, 0x38(r26)
	srwi r0, r4, 31
	add r0, r0, r4
	srawi r0, r0, 1
	mulli r4, r0, 0xc
	addi r0, r4, 0x4
	lfsx f1, r3, r0
	stfs f1, 0x54(r26)
	lwz r4, 0x38(r26)
	srwi r0, r4, 31
	add r0, r0, r4
	srawi r0, r0, 1
	mulli r4, r0, 0xc
	addi r0, r4, 0x8
	lfsx f1, r3, r0
	stfs f1, 0x58(r26)
	stfs f0, 0x30(r26)
	lfs f1, 0x50(r26)
	lfs f2, 0x58(r26)
	lfs f3, 0x4(r26)
	lfs f4, 0xc(r26)
	bl distABf
	lfs f0, float_5_80421030(r2)
	lis r0, 0x4330
	stw r0, 0x60(r1)
	fdivs f0, f1, f0
	lfd f4, 0x68(r31)
	stw r0, 0x50(r1)
	lfs f2, float_0p5_80420f7c(r2)
	fctiwz f0, f0
	stfd f0, 0x58(r1)
	lwz r0, 0x5c(r1)
	stw r0, 0x24(r26)
	lwz r0, 0x24(r26)
	lfs f1, 0x54(r26)
	xoris r0, r0, 0x8000
	lfs f0, 0x8(r26)
	stw r0, 0x64(r1)
	fsubs f1, f1, f0
	lfs f5, 0x30(r26)
	lfd f0, 0x60(r1)
	stw r0, 0x54(r1)
	fsubs f0, f0, f4
	lfd f3, 0x50(r1)
	fdivs f0, f1, f0
	fsubs f1, f3, f4
	fmuls f1, f5, f1
	fmadds f0, f1, f2, f0
	stfs f0, 0x34(r26)
	lfs f1, 0x4(r26)
	lfs f2, 0xc(r26)
	lfs f3, 0x50(r26)
	lfs f4, 0x58(r26)
	bl angleABf
	stfs f1, 0x18(r26)
	lfs f0, float_0_80420f84(r2)
	stfs f0, 0x48(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @80
	@84:
	lfs f1, 0x8(r26)
	lfs f0, 0x34(r26)
	lfs f3, float_6p2832_80420fa4(r2)
	fadds f2, f1, f0
	lfs f0, float_360_80420fa8(r2)
	lfs f1, float_3p1416_8042103c(r2)
	lfs f7, float_0p00761_80421034(r2)
	stfs f2, 0x8(r26)
	lfs f6, float_0p16605_80421038(r2)
	lfs f4, 0x34(r26)
	lfs f2, 0x30(r26)
	lfs f5, float_1_80420f80(r2)
	fsubs f2, f4, f2
	stfs f2, 0x34(r26)
	lfs f2, 0x18(r26)
	fmuls f2, f3, f2
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @85
	lfs f1, float_1p5708_80421040(r2)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @86
	fmuls f0, f2, f2
	fmsubs f7, f7, f0, f6
	fmadds f7, f7, f0, f5
	fmuls f7, f7, f2
	b @87
	@86:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f7, f7, f0, f6
	fmadds f7, f7, f0, f5
	fmuls f7, f7, f2
	b @87
	@85:
	lfs f0, float_4p7124_80421044(r2)
	fcmpo cr0, f2, f0
	bge @88
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f7, f7, f0, f6
	fmadds f7, f7, f0, f5
	fmuls f7, f7, f2
	fneg f7, f7
	b @87
	@88:
	fsubs f0, f2, f0
	lfs f1, float_1p5708_80421040(r2)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f7, f7, f0, f6
	fmadds f7, f7, f0, f5
	fmuls f7, f7, f2
	fneg f7, f7
	@87:
	lfs f1, float_5_80421030(r2)
	lfs f0, 0x4(r26)
	lfs f3, float_6p2832_80420fa4(r2)
	fmadds f2, f1, f7, f0
	lfs f0, float_360_80420fa8(r2)
	lfs f1, float_3p1416_8042103c(r2)
	lfs f6, float_0p03705_80421048(r2)
	stfs f2, 0x4(r26)
	lfs f5, float_0p4967_8042104c(r2)
	lfs f2, 0x18(r26)
	lfs f4, float_1_80420f80(r2)
	fmuls f2, f3, f2
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @89
	lfs f1, float_1p5708_80421040(r2)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @90
	fmuls f0, f2, f2
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	b @91
	@90:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fneg f6, f6
	b @91
	@89:
	lfs f0, float_4p7124_80421044(r2)
	fcmpo cr0, f2, f0
	bge @92
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	fneg f6, f6
	b @91
	@92:
	fsubs f0, f2, f0
	lfs f1, float_1p5708_80421040(r2)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f4
	@91:
	fneg f1, f6
	lfs f2, float_5_80421030(r2)
	lfs f0, 0xc(r26)
	fmadds f0, f2, f1, f0
	stfs f0, 0xc(r26)
	lwz r3, 0x24(r26)
	subic. r0, r3, 0x1
	stw r0, 0x24(r26)
	bge @93
	lfs f0, 0x50(r26)
	stfs f0, 0x4(r26)
	lfs f0, 0x54(r26)
	stfs f0, 0x8(r26)
	lfs f0, 0x58(r26)
	stfs f0, 0xc(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	lwz r0, 0x38(r26)
	cmpwi r0, 0x2
	bne @94
	mr r3, r28
	addi r4, r1, 0x14
	bl psndSFXOn_3D
	stw r3, 0x64(r26)
	@94:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x8
	beq @93
	lfs f1, 0x18(r1)
	li r3, 0x4
	lfs f0, 0x8(r26)
	lfs f6, 0x14(r1)
	lfs f5, 0x4(r26)
	fadds f4, f1, f0
	lfs f2, float_40_80421050(r2)
	lfs f3, 0x1c(r1)
	fadds f1, f6, f5
	lfs f0, 0xc(r26)
	fsubs f2, f4, f2
	lfs f4, float_0_80420f84(r2)
	fadds f3, f3, f0
	bl effKemuri1N64Entry
	la r3, evt_shake(r13)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	@93:
	lfs f2, 0x48(r26)
	lfs f1, float_360_80420fa8(r2)
	lfs f0, float_30_80420fe0(r2)
	fsubs f1, f1, f2
	fdivs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x48(r26)
	b @80
	@95:
	lwz r3, 0x64(r26)
	bl psndSFXOff
	lwz r3, 0x5c(r26)
	bl animPoseRelease
	lwz r3, 0x60(r26)
	bl animPoseRelease
	li r0, -0x1
	stw r0, 0x5c(r26)
	stw r0, 0x60(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @80
	@96:
	addi r21, r21, 0x1
	@80:
	lwz r3, 0x5c(r26)
	cmpwi r3, -0x1
	beq @97
	bl animPoseMain
	@97:
	lwz r3, 0x60(r26)
	cmpwi r3, -0x1
	beq @9
	bl animPoseMain
	b @9
	@98:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x4
	beq @99
	bge @100
	cmpwi r0, 0x0
	beq @101
	blt @102
	cmpwi r0, 0x3
	bge @103
	b @104
	@100:
	cmpwi r0, 0x6
	beq @105
	bge @102
	b @106
	@101:
	mr r4, r20
	addi r3, r31, 0x160
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @102
	mr r4, r20
	addi r3, r31, 0x160
	bl animPoseEntry
	stw r3, 0x5c(r26)
	la r4, str_80421018(r2)
	li r5, 0x1
	lwz r3, 0x5c(r26)
	bl animPoseSetAnim
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @102
	@104:
	lfs f1, 0x8(r26)
	lfs f0, 0x34(r26)
	fadds f0, f1, f0
	stfs f0, 0x8(r26)
	lfs f1, 0x34(r26)
	lfs f0, 0x30(r26)
	fsubs f0, f1, f0
	stfs f0, 0x34(r26)
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f31
	bge @107
	stfs f31, 0x8(r26)
	li r0, 0x0
	stw r0, 0x24(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	@107:
	lwz r0, 0x38(r26)
	cmpwi r0, 0x1
	bne @102
	lfs f0, 0x8(r26)
	fcmpo cr0, f0, f29
	bge @102
	lfs f0, 0x18(r1)
	li r3, 0x4
	lfs f4, 0x14(r1)
	lfs f1, 0x4(r26)
	fadds f2, f0, f31
	lfs f3, 0x1c(r1)
	lfs f0, 0xc(r26)
	fadds f1, f4, f1
	lfs f4, float_0_80420f84(r2)
	fadds f3, f3, f0
	bl effKemuri1N64Entry
	la r3, evt_shake(r13)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	lwz r3, 0x5c(r26)
	la r4, str_80421054(r2)
	li r5, 0x1
	bl animPoseSetAnim
	lwz r5, 0x38(r26)
	mr r3, r27
	addi r4, r1, 0x14
	addi r0, r5, 0x1
	stw r0, 0x38(r26)
	bl psndSFXOn_3D
	b @102
	@103:
	lwz r3, 0x5c(r26)
	bl animPoseGetLoopTimes
	lfs f0, float_1_80420f80(r2)
	fcmpo cr0, f1, f0
	blt @102
	lwz r3, 0x24(r26)
	addi r0, r3, 0x1
	stw r0, 0x24(r26)
	lwz r3, 0x24(r26)
	lwz r0, 0x20(r26)
	cmpw r3, r0
	ble @102
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @102
	@99:
	lwz r3, 0x3c(r26)
	subi r0, r3, 0xa
	stw r0, 0x3c(r26)
	lwz r0, 0x3c(r26)
	cmpwi r0, 0x0
	bge @102
	li r0, 0x0
	stw r0, 0x3c(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @102
	@106:
	lwz r3, 0x5c(r26)
	bl animPoseRelease
	li r0, -0x1
	stw r0, 0x5c(r26)
	lwz r3, 0x38(r26)
	addi r0, r3, 0x1
	stw r0, 0x38(r26)
	b @102
	@105:
	addi r21, r21, 0x1
	@102:
	lwz r3, 0x5c(r26)
	cmpwi r3, -0x1
	beq @9
	bl animPoseMain
	@9:
	addi r25, r25, 0x1
	addi r26, r26, 0x68
	@7:
	lwz r3, 0x8(r19)
	cmpw r25, r3
	blt @8
	subi r0, r3, 0x1
	cmpw r21, r0
	blt @108
	mr r3, r19
	bl effDelete
	b @6
	@108:
	cmpwi r24, 0x6
	beq @109
	bge @110
	cmpwi r24, 0x3
	beq @111
	bge @112
	b @109
	@110:
	cmpwi r24, 0x8
	bge @109
	b @113
	@111:
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effFallDispWater@ha
	mr r6, r19
	addi r5, r3, effFallDispWater@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	b @6
	@112:
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effFallDisp@ha
	mr r6, r19
	addi r5, r3, effFallDisp@l
	li r4, 0x0
	li r3, 0x4
	bl dispEntry
	b @6
	@113:
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effFallDispInseki@ha
	mr r6, r19
	addi r5, r3, effFallDispInseki@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	b @6
	@109:
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effFallDisp@ha
	mr r6, r19
	addi r5, r3, effFallDisp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	@6:
	psq_l f31, 0x118(r1), 0, 0
	lfd f31, 0x110(r1)
	psq_l f30, 0x108(r1), 0, 0
	lfd f30, 0x100(r1)
	psq_l f29, 0xf8(r1), 0, 0
	lfd f29, 0xf0(r1)
	psq_l f28, 0xe8(r1), 0, 0
	lfd f28, 0xe0(r1)
	psq_l f27, 0xd8(r1), 0, 0
	lfd f27, 0xd0(r1)
	psq_l f26, 0xc8(r1), 0, 0
	lfd f26, 0xc0(r1)
	lmw r15, 0x7c(r1)
	lwz r0, 0x124(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stfd f27, 0xb0(r1)
	psq_st f27, 0xb8(r1), 0, 0
	stfd f26, 0xa0(r1)
	psq_st f26, 0xa8(r1), 0, 0
	stfd f25, 0x90(r1)
	psq_st f25, 0x98(r1), 0, 0
	stfd f24, 0x80(r1)
	psq_st f24, 0x88(r1), 0, 0
	stfd f23, 0x70(r1)
	psq_st f23, 0x78(r1), 0, 0
	stfd f22, 0x60(r1)
	psq_st f22, 0x68(r1), 0, 0
	stmw r23, 0x3c(r1)
	fmr f24, f1
	mr r23, r3
	fmr f25, f2
	mr r24, r4
	fmr f26, f3
	mr r25, r5
	fmr f31, f4
	fmr f23, f5
	fmr f22, f6
	bl effEntry
	cmpwi r23, 0x0
	mr r28, r3
	addi r4, r24, 0x1
	beq @1
	blt @1
	cmpwi r23, 0x9
	bge @1
	b @2
	b @1
	@2:
	li r24, 0x1
	li r4, 0x2
	@1:
	la r0, str_80421058(r2)
	li r3, 0x3
	stw r0, 0x14(r28)
	stw r4, 0x8(r28)
	lwz r0, 0x8(r28)
	mulli r4, r0, 0x68
	bl __memAlloc
	lis r4, effFallMain@ha
	stw r3, 0xc(r28)
	addi r0, r4, effFallMain@l
	lis r5, str_802FE584@ha
	stw r0, 0x10(r28)
	addi r29, r5, str_802FE584@l
	fctiwz f0, f31
	lis r4, double_to_int_802fe480@ha
	lwz r0, 0x0(r28)
	li r5, 0x0
	lfd f27, double_to_int_802fe480@l(r4)
	addi r27, r3, 0x68
	ori r0, r0, 0x2
	stfd f0, 0x18(r1)
	lfs f28, float_3p1416_8042103c(r2)
	li r26, 0x1
	stw r0, 0x0(r28)
	li r0, -0x1
	lwz r30, 0x1c(r1)
	lis r31, 0x4330
	stw r23, 0x0(r3)
	lfs f29, float_180_80420fc0(r2)
	stfs f24, 0x4(r3)
	lfs f30, float_300_80421060(r2)
	stfs f25, 0x8(r3)
	stfs f26, 0xc(r3)
	stfs f31, 0x10(r3)
	lfs f31, float_0_80420f84(r2)
	stfs f23, 0x14(r3)
	stfs f22, 0x18(r3)
	stw r24, 0x1c(r3)
	stw r5, 0x24(r3)
	stw r5, 0x28(r3)
	stw r25, 0x20(r3)
	stw r0, 0x5c(r3)
	stw r0, 0x60(r3)
	b @3
	@4:
	li r3, 0x168
	bl irand
	xoris r0, r3, 0x8000
	stw r31, 0x18(r1)
	mr r3, r30
	stw r0, 0x1c(r1)
	lfd f0, 0x18(r1)
	fsubs f0, f0, f27
	fmuls f0, f28, f0
	fdivs f23, f0, f29
	bl irand
	xoris r0, r3, 0x8000
	stw r31, 0x20(r1)
	fmr f1, f23
	stw r0, 0x24(r1)
	lfd f0, 0x20(r1)
	fsubs f22, f0, f27
	bl sin
	frsp f0, f1
	fmuls f0, f22, f0
	stfs f0, 0x4(r27)
	lwz r3, 0x8(r28)
	bl irand
	xoris r0, r3, 0x8000
	stw r31, 0x28(r1)
	fmr f1, f23
	stw r0, 0x2c(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f27
	fadds f0, f30, f0
	stfs f0, 0x8(r27)
	bl cos
	frsp f0, f1
	li r4, 0x0
	li r0, 0xff
	li r3, 0x64
	fmuls f0, f22, f0
	stfs f0, 0xc(r27)
	stw r4, 0x24(r27)
	stw r4, 0x28(r27)
	stw r0, 0x3c(r27)
	stfs f31, 0x48(r27)
	bl irand
	li r5, 0x32
	srwi r4, r3, 31
	subfc r0, r3, r5
	li r0, 0xb4
	srwi r3, r5, 31
	stw r31, 0x30(r1)
	subfe r3, r3, r4
	li r4, 0x0
	andc r3, r0, r3
	li r0, -0x1
	xoris r3, r3, 0x8000
	cmplwi r23, 0x8
	stw r3, 0x34(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f27
	stfs f0, 0x18(r27)
	stw r4, 0x38(r27)
	stw r0, 0x5c(r27)
	stw r0, 0x60(r27)
	bgt @5
	lis r3, jumptable_803AE070@ha
	slwi r0, r23, 2
	addi r3, r3, jumptable_803AE070@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@6:
	lfs f1, float_0_80420f84(r2)
	cmpwi r26, 0x1
	lfs f0, float_0p2_80421014(r2)
	stfs f1, 0x34(r27)
	stfs f0, 0x30(r27)
	bne @7
	stfs f1, 0x4(r27)
	li r0, 0x0
	stfs f1, 0xc(r27)
	stw r0, 0x24(r27)
	b @8
	@7:
	lwz r3, 0x8(r28)
	bl irand
	addi r0, r3, 0x3c
	stw r0, 0x24(r27)
	@8:
	cmpwi r23, 0x0
	bne @9
	lfs f0, float_0p5_80420f7c(r2)
	b @10
	@9:
	lfs f0, float_1p2_80421064(r2)
	@10:
	stfs f0, 0x2c(r27)
	b @5
	@11:
	lfs f2, float_0_80420f84(r2)
	lfs f1, float_1p6_80421068(r2)
	stfs f2, 0x34(r27)
	lfs f0, float_0p5_80420f7c(r2)
	stfs f1, 0x30(r27)
	stfs f2, 0x4(r27)
	stfs f2, 0xc(r27)
	stw r4, 0x24(r27)
	stfs f2, 0x44(r27)
	stfs f0, 0x2c(r27)
	b @5
	@12:
	lfs f2, float_0_80420f84(r2)
	lis r3, vec3_802fe418@ha
	lfs f0, float_0p1_8042106c(r2)
	addi r7, r3, vec3_802fe418@l
	stfs f2, 0x34(r27)
	mr r3, r29
	lfs f1, float_200_80420fc8(r2)
	addi r4, r1, 0x8
	stfs f0, 0x30(r27)
	lfs f0, float_1_80420f80(r2)
	stfs f2, 0x4(r27)
	stfs f1, 0x8(r27)
	stfs f2, 0xc(r27)
	stfs f2, 0x50(r27)
	stfs f2, 0x54(r27)
	stfs f2, 0x58(r27)
	stfs f0, 0x2c(r27)
	lwz r6, 0x0(r7)
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f24, 0x8(r1)
	stfs f25, 0xc(r1)
	stfs f26, 0x10(r1)
	bl psndSFXOn_3D
	stw r3, 0x64(r27)
	b @5
	@13:
	lfs f2, float_0_80420f84(r2)
	li r0, 0x0
	lfs f1, float_0p6_80421070(r2)
	stfs f2, 0x34(r27)
	lfs f0, float_1_80420f80(r2)
	stfs f1, 0x30(r27)
	stfs f2, 0x4(r27)
	stfs f2, 0xc(r27)
	stw r0, 0x24(r27)
	stfs f0, 0x2c(r27)
	b @5
	@14:
	lfs f3, float_0_80420f84(r2)
	lfs f0, float_200_80420fc8(r2)
	stfs f3, 0x4(r27)
	lfs f2, float_30_80420fe0(r2)
	stfs f0, 0x8(r27)
	lfs f0, float_1p3_80421074(r2)
	stfs f3, 0xc(r27)
	lfs f1, 0x4(r27)
	fneg f1, f1
	fdivs f1, f1, f2
	stfs f1, 0x50(r27)
	lfs f1, 0x8(r27)
	fneg f1, f1
	fdivs f1, f1, f2
	stfs f1, 0x54(r27)
	lfs f1, 0xc(r27)
	fneg f1, f1
	fdivs f1, f1, f2
	stfs f1, 0x58(r27)
	stfs f0, 0x2c(r27)
	stfs f2, 0x48(r27)
	stfs f3, 0x4c(r27)
	b @5
	@15:
	lfs f1, float_400_80421078(r2)
	lfs f0, float_200_80420fc8(r2)
	stfs f1, 0x4(r27)
	lfs f1, float_0_80420f84(r2)
	stfs f0, 0x8(r27)
	lfs f0, float_0p5_80420f7c(r2)
	stfs f1, 0xc(r27)
	stfs f0, 0x2c(r27)
	b @5
	@16:
	lfs f2, float_0_80420f84(r2)
	lfs f0, float_0p25_80420fa0(r2)
	stfs f2, 0x34(r27)
	lfs f1, float_400_80421078(r2)
	stfs f0, 0x30(r27)
	lfs f0, float_1_80420f80(r2)
	stfs f2, 0x4(r27)
	stfs f1, 0x8(r27)
	stfs f2, 0xc(r27)
	stfs f0, 0x2c(r27)
	@5:
	addi r26, r26, 0x1
	addi r27, r27, 0x68
	@3:
	lwz r0, 0x8(r28)
	cmpw r26, r0
	blt @4
	mr r3, r28
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	psq_l f27, 0xb8(r1), 0, 0
	lfd f27, 0xb0(r1)
	psq_l f26, 0xa8(r1), 0, 0
	lfd f26, 0xa0(r1)
	psq_l f25, 0x98(r1), 0, 0
	lfd f25, 0x90(r1)
	psq_l f24, 0x88(r1), 0, 0
	lfd f24, 0x80(r1)
	psq_l f23, 0x78(r1), 0, 0
	lfd f23, 0x70(r1)
	psq_l f22, 0x68(r1), 0, 0
	lfd f22, 0x60(r1)
	lmw r23, 0x3c(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_803AE094_data[1] = {0};
__declspec(section ".sdata2") const u32 gap_09_8042107C_sdata2[1] = {0};
