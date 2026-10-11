#include "eff/eff_n64.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern double sin(double x);
extern int rand(void);

typedef struct EffMagic2N64Work {
    s32 type;     // 0x0
    Vec position; // 0x4
    Vec offset;   // 0x10
    f32 scale;    // 0x1C
    f32 scaleTarget; // 0x20
    s32 alpha;    // 0x24
    s32 life;     // 0x28
    s32 age;      // 0x2C
    s32 a30;
    s32 a34;
    s32 a38;
    s32 a3c;
    s32 a40;
    s32 a44;
    s32 a48;
    s32 a4c;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5c;
} EffMagic2N64Work;

GXColor unk_804231b0;
GXColor unk_804231b4;

static u8 color_rotation_data[24] = {0xFF, 0xC5, 0x9C, 0xFF, 0x9C, 0xFF, 0xFF, 0x73, 0xD6, 0xFF, 0x9C, 0xFF,
                                     0xFF, 0xC5, 0x7B, 0xFF, 0xB4, 0xFF, 0xDE, 0x73, 0xFF, 0xFF, 0x94, 0x9C};

void effMagic2Main(EffectEntry* effect);
void effMagic2Disp(CameraId cameraId, EffectEntry* effect);
void magic2_2_line_dl(void);
void magic2_4_dl(void);

u32 stg_magic2_2_line_v[] = {
    0xFFA90032,
    0x00001555,
    0x0800FFFF,
    0xFF00FFA9,
    0x0032F830,
    0x15550000,
    0xFFFFFFFF,
    0xFFCE0057,
    0xF83012AB,
    0x0000FFFF,
    0xFFFFFFCE,
    0x00570000,
    0x12AB0800,
    0xFFFFFF00,
    0xFF9C0000,
    0x00001800,
    0x0800FFFF,
    0xFF00FF9C,
    0x0000F830,
    0x18000000,
    0xFFFFFFFF,
    0x00000064,
    0xF8301000,
    0x0000FFFF,
    0xFFFF0000,
    0x00640000,
    0x10000800,
    0xFFFFFF00,
    0xFFA9FFCE,
    0x00001AAB,
    0x0800FFFF,
    0xFF00FFA9,
    0xFFCEF830,
    0x1AAB0000,
    0xFFFFFFFF,
    0xFFCEFFA9,
    0x00001D55,
    0x0800FFFF,
    0xFF00FFCE,
    0xFFA9F830,
    0x1D550000,
    0xFFFFFFFF,
    0x0000FF9C,
    0x00002000,
    0x0800FFFF,
    0xFF000000,
    0xFF9CF830,
    0x20000000,
    0xFFFFFFFF,
    0x00320057,
    0xF8300D55,
    0x0000FFFF,
    0xFFFF0032,
    0x00570000,
    0x0D550800,
    0xFFFFFF00,
    0x0057FFCE,
    0x00000555,
    0x0800FFFF,
    0xFF000057,
    0xFFCEF830,
    0x05550000,
    0xFFFFFFFF,
    0x0032FFA9,
    0xF83002AB,
    0x0000FFFF,
    0xFFFF0032,
    0xFFA90000,
    0x02AB0800,
    0xFFFFFF00,
    0x0000FF9C,
    0xF8300000,
    0x0000FFFF,
    0xFFFF0000,
    0xFF9C0000,
    0x00000800,
    0xFFFFFF00,
    0x00640000,
    0x00000800,
    0x0800FFFF,
    0xFF000064,
    0x0000F830,
    0x08000000,
    0xFFFFFFFF,
    0x00570032,
    0x00000AAB,
    0x0800FFFF,
    0xFF000057,
    0x0032F830,
    0x0AAB0000,
    0xFFFFFFFF,
};

u32 stg_magic2_1_v[] = {
    0xFFA90032,
    0x00001555,
    0x0200FFFF,
    0xFFFFFFA9,
    0x0032FFCE,
    0x15550000,
    0xFFFFFFFF,
    0xFFCE0057,
    0xFFCE12AB,
    0x0000FFFF,
    0xFFFFFFCE,
    0x00570000,
    0x12AB0200,
    0xFFFFFFFF,
    0xFF9C0000,
    0x00001800,
    0x0200FFFF,
    0xFFFFFF9C,
    0x0000FFCE,
    0x18000000,
    0xFFFFFFFF,
    0x00000064,
    0xFFCE1000,
    0x0000FFFF,
    0xFFFF0000,
    0x00640000,
    0x10000200,
    0xFFFFFFFF,
    0xFFA9FFCE,
    0x00001AAB,
    0x0200FFFF,
    0xFFFFFFA9,
    0xFFCEFFCE,
    0x1AAB0000,
    0xFFFFFFFF,
    0xFFCEFFA9,
    0x00001D55,
    0x0200FFFF,
    0xFFFFFFCE,
    0xFFA9FFCE,
    0x1D550000,
    0xFFFFFFFF,
    0x0000FF9C,
    0x00002000,
    0x0200FFFF,
    0xFFFF0000,
    0xFF9CFFCE,
    0x20000000,
    0xFFFFFFFF,
    0x00320057,
    0xFFCE0D55,
    0x0000FFFF,
    0xFFFF0032,
    0x00570000,
    0x0D550200,
    0xFFFFFFFF,
    0x0057FFCE,
    0x00000555,
    0x0200FFFF,
    0xFFFF0057,
    0xFFCEFFCE,
    0x05550000,
    0xFFFFFFFF,
    0x0032FFA9,
    0xFFCE02AB,
    0x0000FFFF,
    0xFFFF0032,
    0xFFA90000,
    0x02AB0200,
    0xFFFFFFFF,
    0x0000FF9C,
    0xFFCE0000,
    0x0000FFFF,
    0xFFFF0000,
    0xFF9C0000,
    0x00000200,
    0xFFFFFFFF,
    0x00640000,
    0x00000800,
    0x0200FFFF,
    0xFFFF0064,
    0x0000FFCE,
    0x08000000,
    0xFFFFFFFF,
    0x00570032,
    0x00000AAB,
    0x0200FFFF,
    0xFFFF0057,
    0x0032FFCE,
    0x0AAB0000,
    0xFFFFFFFF,
};

EffectEntry* effMagic2N64Entry(s32 type, s32 life, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffMagic2N64Work* w;

    effect = effEntry();
    effect->type = "Magic2N64\0\0";
    effect->count = 1;
    w = __memAlloc(HEAP_EFFECT, sizeof(EffMagic2N64Work));
    effect->userdata = w;
    effect->callback = effMagic2Main;
    w->type = type;
    w->life = life;
    w->alpha = w->age = 0;
    w->offset.x = x;
    w->offset.y = y;
    w->offset.z = z;
    w->a40 = w->a44 = 0;
    w->a48 = w->a4c = 0;
    w->a30 = w->a34 = 0;
    w->a38 = w->a3c = 0;
    w->position.x = x;
    w->position.y = y;
    w->position.z = z;
    w->scale = 10.0f;
    w->f58 = (f32)(rand() % 360);
    w->f5c = 4.0f;
    w->f50 = 0.0f;
    w->f54 = 0.0f;
    if (type == 1) {
        w->a3c = 0x60;
        w->scaleTarget = scale;
    } else {
        w->a44 = -2;
        w->a4c = -4;
        w->scaleTarget = 0.2f * scale;
    }
    return effect;
}

#pragma opt_common_subs off
void effMagic2Main(EffectEntry* effect) {
    EffMagic2N64Work* w = effect->userdata;
    Vec position;
    Vec pos2;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 i;
    s32 life;

    tmp.x = w->offset.x;
    tmp.y = w->offset.y;
    tmp.z = w->offset.z;
    position = tmp;
    w->life--;
    w->age++;
    life = w->life;
    if (life < 0) {
        effDelete(effect);
        return;
    }
    if (w->age <= 10) {
        w->alpha = w->age * 255 / 10;
    }
    if (life < 6) {
        w->alpha = life * 255 / 6;
    }
    if (life < 10 && w->type == 0) {
        w->scale *= 0.7f;
    }
    if (w->type == 1) {
        {
            f32 sn = (f32)sin(6.2831855f * (f32)(life * 10) / 360.0f);
            w->scale = 0.4f * ((w->scaleTarget * (0.1f * sn) + w->scaleTarget) - w->scale) + w->scale;
        }
    } else {
        {
            f32 sn = (f32)sin(6.2831855f * (f32)(life * 10) / 360.0f);
            w->scale = 0.3f * ((w->scaleTarget * (0.1f * sn) + w->scaleTarget) - w->scale) + w->scale;
        }
    }
    {
    Vec tmp2 = {0.0f, 0.0f, 0.0f};
    tmp2.x = w->position.x;
    tmp2.y = w->position.y;
    tmp2.z = w->position.z;
    pos2 = tmp2;
    }
    PSMTXMultVec(camGetPtr(CAMERA_3D)->view, &pos2, &pos2);
    PSMTX44MultVec(camGetPtr(CAMERA_3D)->projection, &pos2, &pos2);
    w->offset.x = 304.0f * pos2.x;
    w->offset.y = 240.0f * pos2.y;
    w->offset.z = 0.0f;
    for (i = 0; i < effect->count; i++, w++) {
        w->f58 += w->f5c;
        w->f50 += w->f54;
        w->a30 += w->a34;
        w->a38 += w->a3c;
        w->a40 += w->a44;
        w->a48 += w->a4c;
        if (w->a40 < 0) {
            w->a40 += 0x100;
        }
        if (w->a48 < 0) {
            w->a48 += 0x100;
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effMagic2Disp, effect);
}

#pragma opt_common_subs reset
void effMagic2Disp(CameraId cameraId, EffectEntry* effect) {
    s32 fov;
    s32 half;
    EffMagic2N64Work* w;
    s32 i;
    s32 idx;
    s32 alpha;
    s32 type;
    Mtx m13c;
    Mtx m10c;
    Mtx44 mcc;
    Mtx44 m8c;
    Mtx44 m4c;
    f32 proj[7];
    f32 vp[6];
    GXColor c1;
    GXColor c0;

    camGetPtr(cameraId);
    w = effect->userdata;
    type = w->type;
    GXGetProjectionv(proj);
    GXGetViewportv(vp);
    PSMTX44Trans(m8c, w->offset.x, w->offset.y, w->offset.z);
    PSMTX44Scale(m4c, w->scale, w->scale, 1.0f);
    PSMTX44Concat(m8c, m4c, m8c);
    fov = (type == 1) ? 130 : 30;
    C_MTXPerspective(mcc, fov, 1.2666667f, 1.0f, 32768.0f);
    PSMTX44Concat(mcc, m8c, mcc);
    GXSetProjection(mcc, 0);
    switch (type) {
        case 1:
            PSMTXTrans(m13c, 0.0f, 0.0f, -70.0f);
            break;
        case 0:
            PSMTXTrans(m13c, 0.0f, 0.0f, -80.0f);
            break;
    }
    GXLoadPosMtxImm(m13c, 0);
    GXSetCurrentMtx(0);
    alpha = w->alpha;
    idx = w->age * 3;
    half = alpha / 2;
    for (i = 0; i < effect->count; i++, w++) {
        u8* d;
        s32 b30;
        s32 b40;
        s32 b38;
        s32 b48;
        idx += 30;
        c0 = unk_804231b0;
        c0.a = alpha;
        idx = idx % 24;
        d = color_rotation_data + idx;
        c0.r = d[0];
        c0.b = d[2];
        GXSetTevColor(GX_TEVREG0, c0);
        c1 = unk_804231b4;
        c1.a = half;
        GXSetTevColor(GX_TEVREG1, c1);
        b30 = w->a30;
        b40 = w->a40;
        b38 = w->a38;
        b48 = w->a48;
        if (type == 0) {
            PSMTXScale(m10c, 0.015625f, 0.015625f, 1.0f);
            PSMTXTrans(m13c, (f32)(b30 / 4), (f32)(b40 / 4), 0.0f);
            PSMTXConcat(m10c, m13c, m13c);
            GXLoadTexMtxImm(m13c, 0x1e, 1);
            PSMTXScale(m10c, 0.015625f, 0.015625f, 1.0f);
            PSMTXTrans(m13c, (f32)(b38 / 4), (f32)(b48 / 4), 0.0f);
            PSMTXConcat(m10c, m13c, m13c);
            GXLoadTexMtxImm(m13c, 0x21, 1);
        } else {
            PSMTXScale(m10c, 0.015625f, 0.0625f, 0.0f);
            PSMTXTrans(m13c, (f32)(b30 / 4), (f32)(b40 / 4), 0.0f);
            PSMTXConcat(m10c, m13c, m13c);
            GXLoadTexMtxImm(m13c, 0x1e, 1);
            PSMTXScale(m10c, 0.015625f, 0.0625f, 1.0f);
            PSMTXTrans(m13c, (f32)(b38 / 4), (f32)(b48 / 4), 0.0f);
            PSMTXConcat(m10c, m13c, m13c);
            GXLoadTexMtxImm(m13c, 0x21, 1);
        }
        switch (type) {
            case 0:
                magic2_2_line_dl();
                break;
            case 1:
                magic2_4_dl();
                break;
        }
    }
    GXSetProjectionv(proj);
    GXSetScissorBoxOffset(0, 0);
}

void magic2_2_line_dl(void) {
    GXTexObj texObj;
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(0, 1, 4, 30, 0, 125);
    GXSetTexCoordGen2(1, 1, 4, 33, 0, 125);
    effGetTexObjN64(17, &texObj);
    GXLoadTexObj(&texObj, 0);
    GXLoadTexObj(&texObj, 1);
    GXSetNumTevStages(3);
    GXSetTevOrder(0, 0, 0, 255);
    GXSetTevColorOp(0, 1, 0, 0, 1, 3);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevColorIn(0, 15, 4, 8, 12);
    GXSetTevAlphaIn(0, 7, 2, 4, 7);
    GXSetTevOrder(1, 1, 1, 4);
    GXSetTevColorOp(1, 0, 0, 0, 1, 0);
    GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
    GXSetTevColorIn(1, 15, 2, 8, 2);
    GXSetTevAlphaIn(1, 7, 0, 5, 7);
    GXSetTevOrder(2, 1, 1, 4);
    GXSetTevColorOp(2, 1, 0, 0, 1, 0);
    GXSetTevAlphaOp(2, 0, 0, 0, 1, 0);
    GXSetTevColorIn(2, 15, 8, 6, 0);
    GXSetTevAlphaIn(2, 7, 4, 5, 0);
    GXSetCullMode(0);
    effSetVtxDescN64((effN64Vtx*)stg_magic2_2_line_v);
    GXBegin(144, 0, 72);
    tri2(0, 1, 2, 0, 0, 2, 3, 0);
    tri2(4, 5, 1, 0, 4, 1, 0, 0);
    tri2(3, 2, 6, 0, 3, 6, 7, 0);
    tri2(8, 9, 5, 0, 8, 5, 4, 0);
    tri2(10, 11, 9, 0, 10, 9, 8, 0);
    tri2(12, 13, 11, 0, 12, 11, 10, 0);
    tri2(7, 6, 14, 0, 7, 14, 15, 0);
    tri2(16, 17, 18, 0, 16, 18, 19, 0);
    tri2(19, 18, 20, 0, 19, 20, 21, 0);
    tri2(22, 23, 17, 0, 22, 17, 16, 0);
    tri2(24, 25, 23, 0, 24, 23, 22, 0);
    tri2(15, 14, 25, 0, 15, 25, 24, 0);
}

void magic2_4_dl(void) {
    GXTexObj texObj;
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(0, 1, 4, 30, 0, 125);
    GXSetTexCoordGen2(1, 1, 4, 33, 0, 125);
    effGetTexObjN64(18, &texObj);
    GXLoadTexObj(&texObj, 0);
    effGetTexObjN64(19, &texObj);
    GXLoadTexObj(&texObj, 1);
    GXSetNumTevStages(3);
    GXSetTevOrder(0, 0, 0, 255);
    GXSetTevColorOp(0, 1, 0, 0, 1, 3);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevColorIn(0, 15, 4, 8, 12);
    GXSetTevAlphaIn(0, 7, 2, 4, 7);
    GXSetTevOrder(1, 1, 1, 255);
    GXSetTevColorOp(1, 0, 0, 0, 1, 0);
    GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
    GXSetTevColorIn(1, 15, 2, 8, 2);
    GXSetTevAlphaIn(1, 7, 0, 1, 7);
    GXSetTevOrder(2, 1, 1, 255);
    GXSetTevColorOp(2, 1, 0, 0, 1, 0);
    GXSetTevAlphaOp(2, 0, 0, 0, 1, 0);
    GXSetTevColorIn(2, 15, 8, 6, 0);
    GXSetTevAlphaIn(2, 7, 4, 1, 0);
    GXSetCullMode(0);
    effSetVtxDescN64((effN64Vtx*)stg_magic2_1_v);
    GXBegin(144, 0, 72);
    tri2(0, 1, 2, 0, 0, 2, 3, 0);
    tri2(4, 5, 1, 0, 4, 1, 0, 0);
    tri2(3, 2, 6, 0, 3, 6, 7, 0);
    tri2(8, 9, 5, 0, 8, 5, 4, 0);
    tri2(10, 11, 9, 0, 10, 9, 8, 0);
    tri2(12, 13, 11, 0, 12, 11, 10, 0);
    tri2(7, 6, 14, 0, 7, 14, 15, 0);
    tri2(16, 17, 18, 0, 16, 18, 19, 0);
    tri2(19, 18, 20, 0, 19, 20, 21, 0);
    tri2(22, 23, 17, 0, 22, 17, 16, 0);
    tri2(24, 25, 23, 0, 24, 23, 22, 0);
    tri2(15, 14, 25, 0, 15, 25, 24, 0);
}
