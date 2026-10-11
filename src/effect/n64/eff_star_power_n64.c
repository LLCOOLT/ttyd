#include "eff/eff_n64.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

double sin(double);

typedef struct EffStarPowerN64Work {
    s16 unk0;      // 0x0
    s16 id;        // 0x2
    Vec position;  // 0x4
    s32 lifetime;  // 0x10
    s32 frame;     // 0x14
    s32 c18;       // 0x18
    s32 c1c;       // 0x1C
    s32 c20;       // 0x20
    s32 c24;       // 0x24
    s32 c28;       // 0x28
    s32 c2c;       // 0x2C
    s32 c30;       // 0x30
    s32 c34;       // 0x34
    f32 scale;     // 0x38
    f32 rotX;      // 0x3C
    f32 rotY;      // 0x40
    f32 rotZ;      // 0x44
    f32 prevRotX;  // 0x48
    f32 prevRotY;  // 0x4C
    f32 prevRotZ;  // 0x50
    f32 prevScale; // 0x54
} EffStarPowerN64Work;

void effStarPowerMain(EffectEntry* effect);
void effStarPowerDisp(CameraId cameraId, EffectEntry* effect);

EffectEntry* effStarPowerN64Entry(s32 id, s32 lifetime, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffStarPowerN64Work* work;

    effect = effEntry();
    effect->type = "StarPowerN64\0\0\0";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffStarPowerN64Work));
    effect->userdata = work;
    effect->callback = effStarPowerMain;
    effect->flags |= 2;
    work->unk0 = 1;
    work->id = id;
    work->frame = 0;
    if (lifetime <= 0) {
        work->lifetime = 1000;
    } else {
        work->lifetime = lifetime;
    }
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale = scale;
    work->c18 = 255;
    work->c1c = 255;
    work->c20 = 120;
    work->c28 = 255;
    work->c2c = 120;
    work->c30 = 0;
    work->c34 = 255;
    work->c24 = 255;
    work->rotX = 0.0f;
    work->rotY = 0.0f;
    work->rotZ = 0.0f;
    return effect;
}

void effStarPowerMain(EffectEntry* effect) {
    EffStarPowerN64Work* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 id;
    s32 frame;
    s32 life;
    f32 sn;

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    id = work->id;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        work->lifetime = 16;
    }
    if (work->lifetime < 1000) {
        work->lifetime--;
    }
    work->frame++;
    life = work->lifetime;
    if (life < 0) {
        effDelete(effect);
        return;
    }
    frame = work->frame;
    if (life < 16) {
        life = life * 16;
        if (work->c24 > life) {
            work->c24 = life;
        }
        if (work->c34 > life) {
            work->c34 = life;
        }
    }
    if (frame < 16) {
        life = frame * 16 + 15;
        if (work->c24 < life) {
            work->c24 = life;
        }
        if (work->c34 < life) {
            work->c34 = life;
        }
    }
    work->prevRotX = work->rotX;
    work->prevRotY = work->rotY;
    work->prevRotZ = work->rotZ;
    work->prevScale = work->scale;
    if (id == 1) {
        work->rotX = (f32)(frame * 4);
        work->rotY = 0.4953f * (4.0f * (f32)frame);
        work->rotZ = 0.2234f * (4.0f * (f32)frame);
        work->c24 = 255;
        sn = (f32)sin(6.2831855f * (7.12343f * (f32)frame) / 360.0f);
        work->c34 = (s32)(127.0f * sn + 128.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (1.231f * (f32)frame) / 360.0f);
        work->c18 = (s32)(127.0f * sn + 215.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (0.531f * (f32)frame) / 360.0f);
        work->c1c = (s32)(127.0f * sn + 215.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (3.231f * (f32)frame) / 360.0f);
        work->c20 = (s32)(127.0f * sn + 215.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (0.298f * (f32)frame) / 360.0f);
        work->c28 = (s32)(127.0f * sn + 188.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (0.831f * (f32)frame) / 360.0f);
        work->c2c = (s32)(127.0f * sn + 188.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (2.231f * (f32)frame) / 360.0f);
        work->c30 = (s32)(127.0f * sn + 188.0f) & 0xFF;
        sn = (f32)sin(6.2831855f * (2.044f * (f32)frame) / 360.0f);
        work->scale = 0.7f + 0.3f * sn;
    }
    if (frame == 1) {
        work->prevRotX = work->rotX;
        work->prevRotY = work->rotY;
        work->prevRotZ = work->rotZ;
        work->prevScale = work->scale;
    }
    dispEntry(4, dispCalcZ(&position), 2, (DispCallback)effStarPowerDisp, effect);
}

u32 testsrc_akari_v[] = {
    0x0093FF36, 0x00000000, 0x0000FFFF, 0xFFFF008F, 0xFFD20000, 0x00000000, 0x000000FF,
    0x0085FFD5, 0x00000000, 0x00000000, 0x00FF0088, 0xFF450000, 0x00000000, 0xFFFFFFFF,
    0x0000FF6A, 0x00000000, 0x00000000, 0x00FF0000, 0xFF740000, 0x00000000, 0x000000FF,
    0x00EE004D, 0x00000000, 0x0000FFFF, 0xFFFF00DC, 0x00480000, 0x00000000, 0xFFFFFFFF,
    0x00580079, 0x00000000, 0x00000000, 0x00FF0052, 0x00710000, 0x00000000, 0x000000FF,
    0x000000E8, 0x00000000, 0x0000FFFF, 0xFFFF0000, 0x00FA0000, 0x00000000, 0xFFFFFFFF,
    0xFFA80079, 0x00000000, 0x00000000, 0x00FFFFAE, 0x00710000, 0x00000000, 0x000000FF,
    0xFF6DFF36, 0x00000000, 0x0000FFFF, 0xFFFFFF78, 0xFF450000, 0x00000000, 0xFFFFFFFF,
    0xFF12004D, 0x00000000, 0x0000FFFF, 0xFFFFFF24, 0x00480000, 0x00000000, 0xFFFFFFFF,
    0xFF71FFD2, 0x00000000, 0x00000000, 0x00FFFF7B, 0xFFD50000, 0x00000000, 0x000000FF,
    0x00A8FF19, 0x0000067B, 0xFFFEFFFF, 0xFFFF00A3, 0xFFCB0000, 0x066902BA, 0x000000FF,
    0x006BFFDD, 0x00000594, 0x03020000, 0x00FF006D, 0xFF6A0000, 0x059D013C, 0xFFFFFFFF,
    0x0000FF55, 0x00000400, 0x00E80000, 0x00FF0000, 0xFF900000, 0x040001D0, 0x000000FF,
    0x010F0058, 0x00000804, 0x04E4FFFF, 0xFFFF00B0, 0x00390000, 0x069D046C, 0xFFFFFFFF,
    0x0065008A, 0x0000057D, 0x05AA0000, 0x00FF0042, 0x005B0000, 0x04FA04EE, 0x000000FF,
    0x000000B9, 0x00000400, 0x0664FFFF, 0xFFFF0000, 0x011D0000, 0x040007EC, 0xFFFFFFFF,
    0xFF9B008A, 0x00000283, 0x05AA0000, 0x00FFFFBE, 0x005B0000, 0x030604EE, 0x000000FF,
    0xFF58FF19, 0x00000185, 0xFFFEFFFF, 0xFFFFFF93, 0xFF6A0000, 0x0263013C, 0xFFFFFFFF,
    0xFEF10058, 0x0000FFFC, 0x04E4FFFF, 0xFFFFFF50, 0x00390000, 0x0163046C, 0xFFFFFFFF,
    0xFF5DFFCB, 0x00000197, 0x02BA0000, 0x00FFFF95, 0xFFDD0000, 0x026C0302, 0x000000FF,
};

void effStarPowerDisp(CameraId cameraId, EffectEntry* effect) {
    CameraEntry* camera;
    s32 half;
    EffStarPowerN64Work* work;
    s32 c18, c1c, c20, c24, c28, c2c, c30, c34;
    Mtx mtx;
    Mtx scale;
    Mtx rot;
    Mtx tmp;
    GXTexObj texObj;

    camera = camGetPtr(cameraId);
    work = effect->userdata;
    c18 = work->c18;
    c1c = work->c1c;
    c20 = work->c20;
    c24 = work->c24;
    c28 = work->c28;
    c2c = work->c2c;
    c30 = work->c30;
    c34 = work->c34;
    if (c18 > 255) {
        c18 = 255;
    }
    if (c1c > 255) {
        c1c = 255;
    }
    if (c20 > 255) {
        c20 = 255;
    }
    if (c24 > 255) {
        c24 = 255;
    }
    if (c28 > 255) {
        c28 = 255;
    }
    if (c2c > 255) {
        c2c = 255;
    }
    if (c30 > 255) {
        c30 = 255;
    }
    if (c34 > 255) {
        c34 = 255;
    }
    if (c18 < 0) {
        c18 = 0;
    }
    if (c1c < 0) {
        c1c = 0;
    }
    if (c20 < 0) {
        c20 = 0;
    }
    if (c24 < 0) {
        c24 = 0;
    }
    if (c28 < 0) {
        c28 = 0;
    }
    if (c2c < 0) {
        c2c = 0;
    }
    if (c30 < 0) {
        c30 = 0;
    }
    if (c34 < 0) {
        c34 = 0;
    }
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    PSMTXScale(scale, 0.015625f, 0.015625f, 0.0f);
    GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
    effGetTexObjN64(0x49, &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetCullMode(GX_CULL_NONE);
    if (c34 != 0) {
        PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
        PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(CAMERA_3D)->viewYaw);
        PSMTXScale(scale, 0.4f * work->prevScale, 0.4f * work->prevScale, 0.4f * work->prevScale);
        PSMTXConcat(mtx, rot, mtx);
        PSMTXConcat(mtx, scale, mtx);
        PSMTXRotRad(rot, 'x', 0.017453292f * work->prevRotX);
        PSMTXConcat(mtx, rot, mtx);
        PSMTXRotRad(rot, 'y', 0.017453292f * work->prevRotY);
        PSMTXConcat(mtx, rot, mtx);
        PSMTXRotRad(rot, 'z', 0.017453292f * work->prevRotZ);
        PSMTXConcat(mtx, rot, mtx);
        PSMTXConcat(camera->view, mtx, tmp);
        GXLoadPosMtxImm(tmp, GX_PNMTX0);
        GXSetCurrentMtx(0);
        half = c34 >> 1;
        GXSetTevColor(GX_TEVREG0, (GXColor){c18, c1c, c20, half});
        GXSetTevColor(GX_TEVREG1, (GXColor){c28, c2c, c30, half});
        GXSetNumChans(1);
        GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_C0, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        effSetVtxDescN64((effN64Vtx*)((u8*)testsrc_akari_v + 0x118));
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, 60);
        tri2(0, 1, 2, 0, 0, 2, 3, 0);
        tri2(4, 0, 3, 0, 4, 3, 5, 0);
        tri2(1, 6, 7, 0, 1, 7, 2, 0);
        tri2(6, 8, 9, 0, 6, 9, 7, 0);
        tri2(10, 9, 8, 0, 10, 8, 11, 0);
        tri2(11, 12, 13, 0, 11, 13, 10, 0);
        tri2(14, 4, 5, 0, 14, 5, 15, 0);
        tri2(12, 16, 17, 0, 12, 17, 13, 0);
        tri2(16, 18, 19, 0, 16, 19, 17, 0);
        tri2(18, 14, 15, 0, 18, 15, 19, 0);
    }
    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(CAMERA_3D)->viewYaw);
    PSMTXScale(scale, 0.4f * work->scale, 0.4f * work->scale, 0.4f * work->scale);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXConcat(mtx, scale, mtx);
    PSMTXRotRad(rot, 'x', 0.017453292f * work->rotX);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXRotRad(rot, 'y', 0.017453292f * work->rotY);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXRotRad(rot, 'z', 0.017453292f * work->rotZ);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXConcat(camera->view, mtx, tmp);
    GXLoadPosMtxImm(tmp, GX_PNMTX0);
    GXSetCurrentMtx(0);
    if (c34 != 0) {
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, 60);
        tri2(0, 1, 2, 0, 0, 2, 3, 0);
        tri2(4, 0, 3, 0, 4, 3, 5, 0);
        tri2(1, 6, 7, 0, 1, 7, 2, 0);
        tri2(6, 8, 9, 0, 6, 9, 7, 0);
        tri2(10, 9, 8, 0, 10, 8, 11, 0);
        tri2(11, 12, 13, 0, 11, 13, 10, 0);
        tri2(14, 4, 5, 0, 14, 5, 15, 0);
        tri2(12, 16, 17, 0, 12, 17, 13, 0);
        tri2(16, 18, 19, 0, 16, 19, 17, 0);
        tri2(18, 14, 15, 0, 18, 15, 19, 0);
    }
    GXSetTevColor(GX_TEVREG0, (GXColor){c18, c1c, c20, c24});
    GXSetTevColor(GX_TEVREG1, (GXColor){c28, c2c, c30, c24});
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_C0, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    effSetVtxDescN64((effN64Vtx*)testsrc_akari_v);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 60);
    tri2(0, 1, 2, 0, 0, 2, 3, 0);
    tri2(4, 0, 3, 0, 4, 3, 5, 0);
    tri2(1, 6, 7, 0, 1, 7, 2, 0);
    tri2(6, 8, 9, 0, 6, 9, 7, 0);
    tri2(10, 9, 8, 0, 10, 8, 11, 0);
    tri2(11, 12, 13, 0, 11, 13, 10, 0);
    tri2(14, 4, 5, 0, 14, 5, 15, 0);
    tri2(12, 16, 17, 0, 12, 17, 13, 0);
    tri2(16, 18, 19, 0, 16, 19, 17, 0);
    tri2(18, 14, 15, 0, 18, 15, 19, 0);
}
