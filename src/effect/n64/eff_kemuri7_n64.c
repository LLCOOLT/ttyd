#include "eff/n64/eff_kemuri7_n64.h"
#include "eff/eff_n64.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

double sin(double x);
double cos(double x);

typedef struct EffKemuri7N64Work {
    BOOL active;      // 0x0
    s16 field_0x4;    // 0x4
    s16 timer;        // 0x6
    u8 alpha;         // 0x8
    u8 pad_9[3];      // 0x9
    Vec position;     // 0xC
    Vec scale;        // 0x18
    Vec rotation;     // 0x24
    Mtx mtx;          // 0x30
    f32 side;         // 0x60
    f32 field_0x64;   // 0x64
    f32 field_0x68;   // 0x68
    f32 field_0x6C;   // 0x6C
    f32 field_0x70;   // 0x70
    f32 field_0x74;   // 0x74
    f32 field_0x78;   // 0x78
    f32 field_0x7C;   // 0x7C
    f32 sinAngle;     // 0x80
    f32 cosAngle;     // 0x84
} EffKemuri7N64Work;

effN64Vtx foot_vtx[] = {
    {-5, 0, -5, 0, 1024, 0, 0, 0, 255},
    {5, 0, -5, 1024, 1024, 0, 0, 0, 255},
    {5, 0, 5, 1024, 0, 0, 0, 0, 255},
    {-5, 0, 5, 0, 0, 0, 0, 0, 255},
};

void effKemuri7Main(EffectEntry* effect);
void effKemuri7Disp(CameraId cameraId, EffectEntry* effect);

#pragma opt_propagation off
#pragma opt_lifetimes off
EffectEntry* effKemuri7N64Entry(f32 x, f32 y, f32 z, f32 angle, f32 side) {
    EffectEntry* effect;
    EffKemuri7N64Work* work;
    f32 full;
    f32 twoPi;
    f32 ofs;
    f32 dist;
    f32 sideAngle;
    f32 rad;

    effect = effEntry();
    effect->type = "Kemuri7N64";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffKemuri7N64Work));
    effect->userdata = work;
    effect->callback = effKemuri7Main;
    work->active = TRUE;
    work->field_0x6C = 0.0f;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale.x = 1.0f;
    work->scale.y = 1.0f;
    work->scale.z = 1.0f;
    work->alpha = 255;
    work->side = side;
    work->field_0x70 = 0.0f;
    work->field_0x74 = 0.0f;
    work->timer = 255;
    work->rotation.x = 0.0f;
    work->rotation.y = 30.0f * side + angle - 15.0f;
    work->rotation.z = 0.0f;
    twoPi = 6.2831855f;
    full = 360.0f;
    ofs = 45.0f;
    dist = 5.0f;
    sideAngle = 180.0f * side;
    z = reviseAngle(angle);
    rad = twoPi * z / full;
    work->sinAngle = sin(rad);
    work->cosAngle = cos(rad);
    rad = twoPi * (ofs + z - sideAngle) / full;
    work->position.x += dist * (f32)sin(rad);
    work->position.z += dist * (f32)cos(rad);
    work->alpha = 255;
    return effect;
}

#pragma opt_propagation reset
#pragma opt_lifetimes reset
void effKemuri7Main(EffectEntry* effect) {
    EffKemuri7N64Work* work = effect->userdata;
    s32 i;
    BOOL alive;
    Mtx rot;
    Mtx trans;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};

    alive = FALSE;
    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    for (i = 0; i < effect->count; i++, work++) {
        if (!work->active) {
            continue;
        }
        if (--work->timer <= 0) {
            work->active = FALSE;
            continue;
        }
        alive = TRUE;
        PSMTXTrans(trans, work->position.x, work->position.y, work->position.z);
        PSMTXRotRad(rot, 'y', 0.017453292f * work->rotation.y);
        PSMTXConcat(trans, rot, work->mtx);
        work->alpha--;
    }
    if (!alive) {
        effDelete(effect);
        return;
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effKemuri7Disp, effect);
}

void effKemuri7Disp(CameraId cameraId, EffectEntry* effect) {
    CameraEntry* camera;
    EffKemuri7N64Work* work;
    s32 i;
    Mtx mtx;
    Mtx scale;
    GXTexObj texObj;

    camera = camGetPtr(cameraId);
    work = effect->userdata;
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    PSMTXScale(scale, 0.03125f, 0.03125f, 0.0f);
    GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    effGetTexObjN64(0x4F, &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetCullMode(GX_CULL_NONE);
    effSetVtxDescN64(foot_vtx);
    for (i = 0; i < effect->count; i++, work++) {
        if (!work->active) {
            continue;
        }
        GXSetTevColor(GX_TEVREG0, (GXColor){0x70, 0x60, 0x18, work->alpha});
        PSMTXConcat(camera->view, work->mtx, mtx);
        if (!work->side) {
            PSMTXScale(scale, -1.0f, 1.0f, 1.0f);
            PSMTXConcat(mtx, scale, mtx);
        }
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
        tri2(0, 1, 2, 0, 0, 2, 3, 0);
    }
}
