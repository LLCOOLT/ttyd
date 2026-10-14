#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <stdio.h>
#include <string.h>

typedef struct EffPointGetWork {
    s32 type;      // 0x0
    Vec position;  // 0x4
    s32 number;    // 0x10
    f32 scale;     // 0x14
    s32 duration;  // 0x18
    s32 timer;     // 0x1C
    s32 state;     // 0x20
} EffPointGetWork;

EffectEntry* effPointGetEntry(s32 type, f32 x, f32 y, f32 z, s32 number, s32 duration);
void effPointGetMain(EffectEntry* effect);
void effPointGetDisp(CameraId cameraId, EffectEntry* effect);

static s32 texid_tbl[2][4] = { { 0x98, 0x99, 0x9A, 0x9B }, { 0x98, 0x99, 0x9A, 0x9B } };

EffectEntry* effPointGetEntry(s32 type, f32 x, f32 y, f32 z, s32 number, s32 duration) {
    EffectEntry* effect;
    EffPointGetWork* work;

    effect = effEntry();
    effect->type = "PointGet\0\0\0";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffPointGetWork) * effect->count);
    effect->userdata = work;
    effect->callback = effPointGetMain;
    effect->flags |= 2;
    work->type = type;
    work->position.x = x - 2000.0f;
    work->position.y = y;
    work->position.z = z;
    work->number = number;
    work->scale = 1.0f;
    work->duration = duration;
    work->timer = 0;
    work->state = 0;
    return effect;
}

void effPointGetMain(EffectEntry* effect) {
    EffPointGetWork* work = effect->userdata;
    Vec position;
    Vec tmp = { 0.0f, 0.0f, 0.0f };

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    work->timer++;
    switch (work->state) {
        case 0:
            work->position.x = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(-1000.0f, 0.0f, 11, work->timer, 45);
            if (work->timer >= 45) {
                work->timer = 0;
                work->state++;
            }
            break;
        case 1:
            if (work->duration == 0) {
                if (effect->flags & 4) {
                    effect->flags &= ~4;
                    work->timer = 0;
                    work->state++;
                }
            } else if (work->timer >= work->duration) {
                work->timer = 0;
                work->state++;
            }
            break;
        case 2:
            work->position.x = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, 1000.0f, 11, work->timer, 60);
            if (work->timer >= 60) {
                effDelete(effect);
                return;
            }
            break;
    }
    dispEntry(CAMERA_2D, dispCalcZ(&position), 2, (DispCallback)effPointGetDisp, effect);
}

void effPointGetDisp(CameraId cameraId, EffectEntry* effect) {
    EffPointGetWork* work = effect->userdata;
    CameraEntry* camera = camGetPtr(cameraId);
    f32 scale = work->scale;
    f32 width;
    f32 base;
    f32 x0;
    f32 y1;
    f32 wide;
    f32 ox;
    f32 oy;
    GXTexObj texObj;
    GXColor c1, c2, c3, c4;
    Mtx mtx;
    Mtx scaleMtx;
    Mtx baseMtx;
    char buf[32];
    s32 i;
    s32 pass;

    sprintf(buf, "%d", work->number);
    width = 32.0f * (f32)strlen(buf);
    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXScale(scaleMtx, scale, scale, scale);
    PSMTXConcat(mtx, scaleMtx, baseMtx);
    PSMTXConcat(camera->view, baseMtx, baseMtx);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
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
    base = -(362.0f + width);
    width = 48.0f;
    y1 = 24.0f;
    wide = 352.0f;
    x0 = -width;
    x0 *= 0.5f;
    for (pass = 1; pass >= 0; pass--) {
        ox = (f32)(pass * 4);
        oy = (f32)(-pass * 4);
        if (pass != 0) {
            effGetTexObj(texid_tbl[gp->language != 0][3], &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            c1 = (GXColor){ 0, 0, 0, 0x80 };
            GXSetChanMatColor(GX_COLOR0A0, c1);
        } else {
            effGetTexObj(texid_tbl[gp->language != 0][2], &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            c2 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
            GXSetChanMatColor(GX_COLOR0A0, c2);
        }
        for (i = 0; i < strlen(buf); i++) {
            PSMTXTrans(mtx, ox + (32.0f * (f32)i + base / 2.0f), oy, 0.0f);
            PSMTXConcat(baseMtx, mtx, mtx);
            GXLoadPosMtxImm(mtx, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            PSMTXScale(scaleMtx, 0.1f, 1.0f, 1.0f);
            PSMTXTrans(mtx, (f32)((s8)buf[i] - 0x30), 0.0f, 0.0f);
            PSMTXConcat(scaleMtx, mtx, mtx);
            GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, y1, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(width, y1, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(width, x0, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(0.0f, x0, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
        }
        if (pass != 0) {
            effGetTexObj(texid_tbl[gp->language != 0][1], &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            c3 = (GXColor){ 0, 0, 0, 0x80 };
            GXSetChanMatColor(GX_COLOR0A0, c3);
        } else {
            effGetTexObj(texid_tbl[gp->language != 0][0], &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            c4 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
            GXSetChanMatColor(GX_COLOR0A0, c4);
        }
        PSMTXTrans(mtx, 10.0f + (ox + (32.0f * (f32)strlen(buf) + base / 2.0f)), oy, 0.0f);
        PSMTXConcat(baseMtx, mtx, mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        PSMTXIdentity(mtx);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, y1, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(wide, y1, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(wide, x0, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(0.0f, x0, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
    }
}
