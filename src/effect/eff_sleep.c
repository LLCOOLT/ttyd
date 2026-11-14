// Sleep: three sleep marks fade in one after another along a line from a point; the sleep status in battle.
// The second argument is the lifetime in frames (0 or less: until removed).
#include "eff/eff_sleep.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "memory.h"
#include "mario/mariost.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "version.h"
#include "libc_decls.h"

/** Single-precision sine for this file, routed through the double sin() (as in mapdrv.c). */
static inline f32 sinf(f32 x) {
    return sin(x);
}

static void effSleepMain(EffectEntry* effect);
// US effect texture ids are 0x1C lower for these entries.
#define EFF_TEX(id) ((id) - VERSION_PICK(0, 0x1C))

// local prototypes
static void effSleepDisp(CameraId camId, void* param);

/**
 * Spawns the sleep marks at (x, y, z).
 * `lifetime` is in frames (0 or less: until soft deleted), `rotation` is the line direction in degrees.
 * Used for the sleep status in battle, audience Toads and a sleeping NPC in Glitzville.
 */
EffectEntry* effSleepEntry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale, f32 rotation) {
    EffectEntry* effect;
    s32 smth;
    effSleepData* data;
    s32 alpha;
    f32 radians;
    int i;
    f32 r;

    effect = effEntry();
    effect->type = "Sleep";
    effect->count = 4;
    data = __memAlloc(HEAP_EFFECT, effect->count * sizeof(effSleepData));
    effect->userdata = data;
    effect->callback = effSleepMain;
    effect->flags |= EFFECT_FLAG_SOFT_DELETE;
    data->type = type;
    data->position.x = x;
    data->position.y = y;
    data->position.z = z;
    data->scale = scale;
    data->alpha = 0;
    if (lifetime <= 0) {
        data->lifetime = 1000;
    } else {
        data->lifetime = lifetime;
    }
    data->age = 0;

    radians = (6.2831855f * rotation) / 360.0f;
    for (data++, i = 1, smth = 16; i < effect->count; i++, smth += 16, data++) {
        data->position.x = (r = 16.0f * (f32)i) * (f32)cos(radians);
        data->position.y = r * (f32)sin(radians);
        data->position.z = 0.0f;
        data->scale = (0.2f * (f32)i) + 1.0f;
        data->alpha = 0;
        data->delay = smth;
    }
    return effect;
}

/** Fades the base alpha in and out, and fades in each of the 3 marks after its staggered delay. */
static void effSleepMain(EffectEntry* effect) {
    effSleepData* data = effect->userdata;
    int i;
    Vec position;

    position = (Vec){data->position.x, data->position.y, data->position.z};
    if (effect->flags & EFFECT_FLAG_DELETE_REQUESTED) {
        effect->flags &= ~EFFECT_FLAG_DELETE_REQUESTED;
        data->lifetime = 16;
    }
    if (data->lifetime < 1000) {
        data->lifetime--;
    }
    if (data->lifetime < 32) {
        data->alpha = data->lifetime * 8;
    }
    if (data->lifetime < 0) {
        effDelete(effect);
        return;
    }
    data->age++;
    if (data->age < 32) {
        data->alpha = data->age * 8 + 7;
    }
    for (i = 1, data++; i < effect->count; i++, data++) {
        if (data->delay != 0) {
            data->delay--;
        } else {
            data->alpha += 8;
            if (data->alpha > 255) {
                data->alpha = 255;
            }
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, effSleepDisp, effect);
}

/**
 * Draws each visible mark as a camera-facing strip of 8 quads whose x offset follows a sine wave,
 * giving a wavy ribbon texture.
 */
static void effSleepDisp(CameraId camId, void* param) {
    EffectEntry* effect = param;
    CameraEntry* cam;
    s32 base;
    effSleepData* data;
    s32 i;
    s32 j;
    s32 alpha;
    Mtx mtx, scale, rot, res;
    GXTexObj texObj;
    f32 w, s0, s1;

    data = effect->userdata;
    cam = camGetPtr(camId);
    alpha = data->alpha;

    PSMTXTrans(mtx, data->position.x, data->position.y, data->position.z);
    PSMTXScale(scale, data->scale, data->scale, data->scale);
    PSMTXRotRad(rot, 'y', MTXDegToRad(-camGetPtr(camId)->viewYaw));
    PSMTXConcat(mtx, rot, mtx);
    PSMTXConcat(mtx, scale, res);
    PSMTXConcat(cam->view, res, res);

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    effGetTexObj(EFF_TEX(0x8C), &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    w = 8.0f;
    data++;
    for (i = 1, base = 50; i < effect->count; base += 50, i++, data++) {
        if (data->delay == 0) {
            GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, data->alpha * alpha / 255});
            PSMTXTrans(mtx, data->position.x, data->position.y, data->position.z);
            PSMTXScale(scale, data->scale, data->scale, data->scale);
            PSMTXConcat(mtx, scale, mtx);
            PSMTXConcat(res, mtx, mtx);
            GXLoadPosMtxImm(mtx, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            for (j = 0; j < 8; j++) {
                s0 = 0.5f * sinf(6.2831855f * (gp->retraceCount + base + j * 10) / 64);
                s1 = 0.5f * sinf(6.2831855f * (gp->retraceCount + base + (j + 1) * 10) / 64);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(-w / 2 + s1, w / 8 * (j + 1), 0.0f);
                GXTexCoord2f32(0.0f, 0.125f * (7 - j));
                GXPosition3f32(w / 2 + s1, w / 8 * (j + 1), 0.0f);
                GXTexCoord2f32(1.0f, 0.125f * (7 - j));
                GXPosition3f32(w / 2 + s0, w / 8 * j, 0.0f);
                GXTexCoord2f32(1.0f, 0.125f * (8 - j));
                GXPosition3f32(-w / 2 + s0, w / 8 * j, 0.0f);
                GXTexCoord2f32(0.0f, 0.125f * (8 - j));
                GXEnd();
            }
        }
    }
}

// target pad words (G5: section sizes must match or later DOL addresses shift)
