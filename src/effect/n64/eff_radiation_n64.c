#include "eff/eff_n64.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct EffRadiationN64Work {
    s32 type;       // 0x0
    Vec pos0;       // 0x4
    Vec position;   // 0x10
    f32 scale1c;    // 0x1C
    f32 scale20;    // 0x20
    s32 alpha;      // 0x24
    s32 life;       // 0x28
    s32 frame;      // 0x2C
    f32 unk30;      // 0x30
    f32 scroll0;    // 0x34
    f32 scroll2;    // 0x38
    f32 scroll1;    // 0x3C
    f32 scroll3;    // 0x40
    f32 unk44;      // 0x44
    f32 scrollVel0; // 0x48
    f32 scrollVel2; // 0x4C
    f32 scrollVel1; // 0x50
    f32 scrollVel3; // 0x54
    f32 y;          // 0x58
    f32 rotX;       // 0x5C
    f32 rotY;       // 0x60
    f32 rotZ;       // 0x64
    f32 initY;      // 0x68
    f32 initYVel;   // 0x6C
    f32 initRotX;   // 0x70
    f32 initRotY;   // 0x74
    f32 initRotZ;   // 0x78
    s32 initLife;   // 0x7C
    f32 rotVelX;    // 0x80
    f32 rotVelY;    // 0x84
    f32 rotVelZ;    // 0x88
    f32 yVel;       // 0x8C
    s32 delay;      // 0x90
    s32 flag;       // 0x94
    s32 camera;     // 0x98
} EffRadiationN64Work;

void effRadiationMain(EffectEntry* effect);
void effRadiationDisp(CameraId cameraId, EffectEntry* effect);

u32 size150x20_tex32x32[] = {
    0x0000000A, 0x00000000, 0x0000FFFF, 0xFFFF0000, 0xFFF60000, 0x04000000, 0xFFFFFFFF,
    0x0096FFF6, 0x00000400, 0x0400FFFF, 0xFFFF0096, 0x000A0000, 0x00000400, 0xFFFFFFFF,
};

s32 r_data[] = {
    0x00000000, 0xFFFFFFEC, 0x00000000, 0x00000001, 0x00000012, 0xFFFFFFF6, 0xFFFFFFC4, 0x0000002D,
    0xFFFFFFFF, 0x00000004, 0xFFFFFFEC, 0xFFFFFFEC, 0x0000005A, 0x00000001, 0x00000001, 0xFFFFFFF6,
    0xFFFFFFC4, 0x00000087, 0x00000001, 0xFFFFFFFC, 0x00000000, 0xFFFFFFEC, 0x000000B4, 0xFFFFFFF8,
    0x00000001, 0xFFFFFFF6, 0xFFFFFFC4, 0x000000E1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFEC, 0xFFFFFFEC,
    0x0000010E, 0x00000001, 0xFFFFFFF7, 0xFFFFFFF6, 0xFFFFFFC4, 0x0000013B, 0x00000004, 0x00000004,
    0x00000000, 0x0000000A, 0x00000016, 0x00000004, 0x00000001, 0xFFFFFFF6, 0x00000014, 0x00000043,
    0x00000001, 0xFFFFFFFF, 0xFFFFFFEC, 0x0000000A, 0x00000070, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF6,
    0x00000014, 0x0000009D, 0xFFFFFFF8, 0x00000001, 0x00000000, 0x0000000A, 0x000000CA, 0x00000001,
    0xFFFFFFFC, 0xFFFFFFF6, 0x00000014, 0x000000F7, 0x00000001, 0xFFFFFFEE, 0xFFFFFFEC, 0x0000000A,
    0x00000124, 0xFFFFFFFF, 0x00000009, 0xFFFFFFF6, 0x00000014, 0x00000151, 0x00000001, 0x00000001,
};

u32 size300x40_tex32x32[] = {
    0x00000000, 0x00000010, 0x0000FFFF, 0xFFFF012C, 0x00140000, 0x00000400,
    0xEBFFF500, 0x012CFFEC, 0x00000400, 0x0400EBFF, 0xF5000000,
};

EffectEntry* effRadiationN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffRadiationN64Work* work;
    EffRadiationN64Work* p;
    s32 flag;
    s32 count;
    s32 camera;
    s32 i;

    effect = effEntry();
    flag = 0;
    if (type >= 10) {
        flag = 1;
        type = type % 10;
    }
    count = 0x11;
    if (type <= 1) {
        count = 9;
    }
    effect->type = "RadiationN64\0\0\0";
    effect->count = count;
    work = __memAlloc(HEAP_EFFECT, count * sizeof(EffRadiationN64Work));
    effect->userdata = work;
    effect->callback = effRadiationMain;
    effect->flags |= 2;
    work->type = type;
    work->frame = 0;
    work->life = 100;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale20 = scale;
    work->scale1c = scale;
    work->flag = flag;
    camera = 4;
    work->camera = camera;
    switch (type) {
    case 0:
    case 1:
        p = work + 1;
        for (i = 1; i < effect->count; i++) {
            p->initY = (f32)((i - 1) * 30 / (count - 1) - 10);
            p->initLife = 50 - (i - 1) * 20 / (count - 1);
            p->initYVel = 2.5f + 25.0f / (f32)p->initLife;
            p->initRotX = (f32)(s32)effTblRandN64(180, i * 3);
            p->initRotY = (f32)(s32)effTblRandN64(180, i * 3 + 1);
            p->initRotZ = (f32)(s32)effTblRandN64(180, i * 3 + 2);
            p->y = p->initY;
            p->life = p->initLife;
            p->yVel = p->initYVel;
            p->rotX = p->initRotX;
            p->rotY = p->initRotY;
            p->rotZ = p->initRotZ;
            p->alpha = 0;
            p->frame = 0;
            p++;
        }
        break;
    default:
        p = work + 1;
        for (i = 1; i < effect->count; i++) {
            p->y = 0.0f;
            p->life = 0x20 + (i - 1) * 2;
            p->rotX = (f32)r_data[(i - 1) * 5];
            p->rotY = (f32)r_data[(i - 1) * 5 + 1];
            p->rotZ = (f32)r_data[(i - 1) * 5 + 2];
            p->alpha = 0;
            p->frame = 0;
            p->scroll2 = 0.0f;
            p->scroll0 = 0.0f;
            p->scrollVel0 = 0.0f;
            p->scrollVel2 = -0.6f;
            p->scroll1 = 10.0f;
            p->scroll3 = 0.0f;
            p->scrollVel1 = 0.0f;
            p->scrollVel3 = 0.6f;
            p->rotVelX = 0.0f;
            p->rotVelY = 0.0f;
            p->rotVelZ = 0.1f * (f32)r_data[(i - 1) * 5 + 4];
            p->delay = 0;
            p++;
        }
        break;
    }
    return effect;
}

void effRadiationMain(EffectEntry* effect) {
    EffRadiationN64Work* p = effect->userdata;
    EffRadiationN64Work* w2;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 type;
    s32 base;
    s32 base1;
    s32 base2;
    s32 life;
    s32 i;

    tmp.x = p->pos0.x;
    tmp.y = p->pos0.y;
    tmp.z = p->pos0.z;
    position = tmp;
    type = p->type;
    if (p->life <= 10) {
        p->life--;
    }
    p->frame++;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        p->life = 10;
    }
    life = p->life;
    if (life < 0) {
        effDelete(effect);
        return;
    }
    switch (type) {
    case 0:
    case 1:
        base = (p->frame * 10 + 1) * 3;
        base1 = base + 1;
        base2 = base + 2;
        p++;
        for (i = 1; i < effect->count; i++) {
            p->life--;
            p->frame++;
            if (p->frame < 10) {
                p->alpha = p->frame * 12;
            }
            if (p->life < 5) {
                p->alpha = p->life * 25;
            }
            p->y += p->yVel;
            if (p->life <= 0) {
                p->initRotX = (f32)(s32)effTblRandN64(180, base);
                p->initRotY = (f32)(s32)effTblRandN64(180, base1);
                p->initRotZ = (f32)(s32)effTblRandN64(180, base2);
                p->y = p->initY;
                p->life = p->initLife;
                p->yVel = p->initYVel;
                p->rotX = p->initRotX;
                p->rotY = p->initRotY;
                p->rotZ = p->initRotZ;
                p->alpha = 0;
                p->frame = 0;
            }
            p++;
        }
        break;
    default:
        p++;
        for (i = 1; i < effect->count; i++) {
            p->scroll0 += p->scrollVel0;
            if (p->scroll0 > 256.0f) {
                p->scroll0 -= 256.0f;
            }
            if (p->scroll0 < 0.0f) {
                p->scroll0 += 256.0f;
            }
            p->scroll1 += p->scrollVel1;
            if (p->scroll1 > 256.0f) {
                p->scroll1 -= 256.0f;
            }
            if (p->scroll1 < 0.0f) {
                p->scroll1 += 256.0f;
            }
            p->scroll2 += p->scrollVel2;
            if (p->scroll2 > 256.0f) {
                p->scroll2 -= 256.0f;
            }
            if (p->scroll2 < 0.0f) {
                p->scroll2 += 256.0f;
            }
            p->scroll3 += p->scrollVel3;
            if (p->scroll3 > 256.0f) {
                p->scroll3 -= 256.0f;
            }
            if (p->scroll3 < 0.0f) {
                p->scroll3 += 256.0f;
            }
            p->life--;
            p->frame++;
            if (p->frame < 5) {
                p->alpha = p->frame * 50;
            }
            if (p->life < 5) {
                p->alpha = p->life * 50;
            }
            if (life < 10) {
                p->alpha = p->alpha * life / 10;
            }
            if (p->life <= 0) {
                p->y = 0.0f;
                p->life = 0x20 + (i - 1) * 2;
                p->rotX = (f32)r_data[(i - 1) * 5];
                p->rotY = (f32)r_data[(i - 1) * 5 + 1];
                p->rotZ = (f32)r_data[(i - 1) * 5 + 2];
                p->alpha = 0;
                p->frame = 0;
                p->scroll2 = 0.0f;
                p->scroll0 = 0.0f;
                p->scrollVel0 = 0.0f;
                p->scrollVel2 = -0.6f;
                p->scroll1 = 10.0f;
                p->scroll3 = 0.0f;
                p->scrollVel1 = 0.0f;
                p->scrollVel3 = 0.6f;
                p->rotVelX = 0.0f;
                p->rotVelY = 0.0f;
                p->rotVelZ = 0.1f * (f32)r_data[(i - 1) * 5 + 4];
                p->delay = 0;
            }
            if (p->delay <= 0 || (--p->delay, p->delay <= 0)) {
                p->rotX += p->rotVelX;
                p->rotY += p->rotVelY;
                p->rotZ += p->rotVelZ;
            }
            p++;
        }
        break;
    }
    w2 = effect->userdata;
    if (w2->flag == 0) {
        dispEntry(w2->camera, dispCalcZ(&position), 2, (DispCallback)effRadiationDisp, effect);
    } else {
        dispEntry(w2->camera, dispCalcZ(&position), 8, (DispCallback)effRadiationDisp, effect);
    }
}

void effRadiationDisp(CameraId cameraId, EffectEntry* effect) {
    CameraEntry* camera;
    EffRadiationN64Work* p;
    GXTexObj texObj;
    Mtx mtx;
    Mtx scale;
    Mtx rot;
    Mtx tmp;
    Mtx trans;
    u32* vtx;
    s32 i;
    s32 type;
    f32 a;
    f32 sx;
    f32 sz;
    f32 sy;

    camera = camGetPtr(cameraId);
    p = effect->userdata;
    type = p->type;
    if (p->flag != 0) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    switch (type) {
    case 0:
    case 1:
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        effGetTexObjN64(0x2C, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        PSMTXScale(scale, 0.03125f, 0.03125f, 0.0f);
        GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
        break;
    default:
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
        GXSetNumTexGens(0);
        break;
    }
    GXSetCullMode(GX_CULL_NONE);
    PSMTXTrans(mtx, p->position.x, p->position.y, p->position.z);
    p++;
    for (i = 1; i < effect->count; i++) {
        a = (f32)p->alpha / 255.0f;
        PSMTXRotRad(rot, 'x', 0.017453292f * p->rotX);
        PSMTXConcat(mtx, rot, tmp);
        if (type >= 2) {
            PSMTXRotRad(rot, 'z', 0.017453292f * (p->rotZ + (f32)(type == 3 ? 45 : 0)));
            PSMTXConcat(tmp, rot, tmp);
            PSMTXRotRad(rot, 'y', 0.017453292f * p->rotY);
            PSMTXConcat(tmp, rot, tmp);
            PSMTXTrans(trans, p->y, 0.0f, 0.0f);
            PSMTXConcat(tmp, trans, tmp);
            sz = 0.25f * (3.0f + a);
            sx = sz;
            switch (i & 3) {
            case 0:
                sy = 0.3f * a;
                break;
            case 1:
                sy = 0.5f * a;
                break;
            case 2:
                sy = 0.9f * a;
                break;
            default:
                sy = a;
                break;
            }
            PSMTXScale(scale, sx, sy, sz);
            PSMTXConcat(tmp, scale, tmp);
            GXSetTevColor(GX_TEVREG0, (GXColor){0xFF, 0xFF, 0xFA, p->alpha});
        } else {
            PSMTXRotRad(rot, 'y', 0.017453292f * p->rotY);
            PSMTXConcat(tmp, rot, tmp);
            PSMTXRotRad(rot, 'z', 0.017453292f * (p->rotZ + (f32)(type == 3 ? 45 : 0)));
            PSMTXConcat(tmp, rot, tmp);
            PSMTXTrans(trans, p->y, 0.0f, 0.0f);
            PSMTXConcat(tmp, trans, tmp);
            GXSetTevColor(GX_TEVREG0, (GXColor){0xFF, 0xFF, 0xB5, p->alpha});
        }
        PSMTXConcat(camera->view, tmp, tmp);
        GXLoadPosMtxImm(tmp, GX_PNMTX0);
        GXSetCurrentMtx(0);
        switch (type) {
        case 0:
        case 1:
            vtx = size150x20_tex32x32;
            break;
        default:
            vtx = size300x40_tex32x32;
            break;
        }
        effSetVtxDescN64((effN64Vtx*)vtx);
        switch (type) {
        case 0:
        case 1:
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
            tri2(0, 1, 2, 0, 0, 2, 3, 0);
            break;
        default:
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
            tri1(0, 1, 2, 0);
            break;
        }
        p++;
    }
}
