#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct effN64Vtx {
    s16 x, y, z;   // 0x0
    s16 s, t;      // 0x6
    u8 r, g, b, a; // 0xA
} effN64Vtx;

void effSetVtxDescN64(effN64Vtx* vtx);
void tri2();
double sin(double);
void sysWaitDrawSync(void);

typedef struct EffOpukuJetwrainN64Work {
    s32 type;        // 0x0
    Vec position;    // 0x4
    s32 lifetime;    // 0x10
    s32 frame;       // 0x14
    f32 scale;       // 0x18
    u8 color[3];     // 0x1C
    u8 alpha;        // 0x1F
    u8 color2[3];    // 0x20
    s8 grid[19][13]; // 0x23
    s16 vel[19][13]; // 0x11A
} EffOpukuJetwrainN64Work;

effN64Vtx opuku_jetwrain_vtx[] = {
    {-160, -120, -320, 0, 0, 0, 0, 0, 255},
    {-144, -120, -320, 512, 0, 0, 0, 0, 255},
    {-160, -104, -320, 0, 512, 0, 0, 0, 255},
    {-144, -104, -320, 512, 512, 0, 0, 0, 255},
    {-160, -120, -320, 0, 0, 0, 0, 0, 255},
    {-144, -120, -320, 640, 0, 0, 0, 0, 255},
    {-160, -104, -320, 0, 512, 0, 0, 0, 255},
    {-144, -104, -320, 640, 512, 0, 0, 0, 255},
    {-160, -120, -320, 0, 0, 0, 0, 0, 255},
    {-144, -120, -320, 512, 0, 0, 0, 0, 255},
    {-160, -104, -320, 0, 640, 0, 0, 0, 255},
    {-144, -104, -320, 512, 640, 0, 0, 0, 255},
    {-160, -120, -320, 0, 0, 0, 0, 0, 255},
    {-144, -120, -320, 640, 0, 0, 0, 0, 255},
    {-160, -104, -320, 0, 640, 0, 0, 0, 255},
    {-144, -104, -320, 640, 640, 0, 0, 0, 255},
};

void effOpukuJetwrainDisp(CameraId cameraId, EffectEntry* effect);
void effOpukuJetwrainMain(EffectEntry* effect);

EffectEntry* effOpukuJetwrainN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffOpukuJetwrainN64Work* work;
    s32 i, j;

    effect = effEntry();
    effect->type = "OpukuJetwrainN64\0\0\0";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffOpukuJetwrainN64Work));
    effect->userdata = work;
    effect->callback = effOpukuJetwrainMain;
    effect->flags |= 2;
    work->type = type;
    work->frame = 0;
    if (lifetime <= 0) {
        work->lifetime = 1000;
    } else {
        work->lifetime = lifetime;
    }
    work->alpha = 0;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale = scale;
    work->color[0] = 10;
    work->color[1] = 110;
    work->color[2] = 255;
    work->color2[0] = 190;
    work->color2[1] = 220;
    work->color2[2] = 255;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 13; j++) {
            work->grid[i][j] = 0;
            work->vel[i][j] = 0;
        }
    }
    return effect;
}

void effOpukuJetwrainMain(EffectEntry* effect) {
    s32 lifetime;
    EffOpukuJetwrainN64Work* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 i, j;
    s32 frame;
    s32 alpha;
    f32 fa;
    f32 g4, cs, sd;

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        work->lifetime = 32;
    }
    if (work->lifetime < 1000) {
        work->lifetime--;
    }
    work->frame++;
    lifetime = work->lifetime;
    if (lifetime < 0) {
        effDelete(effect);
        return;
    }
    frame = work->frame;
    alpha = 255;
    if (lifetime < 32) {
        alpha = lifetime * 8;
    }
    if (frame < 16) {
        alpha = frame * 16 + 15;
    }
    work->alpha = alpha;
    fa = (f32)alpha / 255.0f;
    for (i = 1; i < 18; i++) {
        f32 s = (f32)sin(6.2831855f * (f32)((i - frame) * -20) / 360.0f);
        work->grid[i][6] = (s8)(fa * (-64.0f * s));
    }
    for (i = 1; i < 18; i++) {
        for (j = 1; j < 12; j++) {
            g4 = 4.0f * (f32)work->grid[i][j];
            cs = (f32)work->grid[i+1][j+1] + (f32)work->grid[i-1][j+1] + (f32)work->grid[i+1][j-1] + (f32)work->grid[i-1][j-1];
            sd = (f32)work->grid[i+1][j] + (f32)work->grid[i-1][j] + (f32)work->grid[i][j+1] + (f32)work->grid[i][j-1];
            cs *= 0.5f;
            work->vel[i][j] = (s16)((f32)work->vel[i][j] + (cs + (sd - g4) - 0.7f * g4));
            work->vel[i][j] = (s16)((f32)work->vel[i][j] * 0.98f);
            if (lifetime < 32) {
                work->grid[i][j] = (s8)((f32)work->grid[i][j] * fa);
            }
        }
    }
    for (i = 1; i < 18; i++) {
        for (j = 1; j < 12; j++) {
            work->grid[i][j] = (s8)((f32)work->grid[i][j] + 0.02f * (f32)work->vel[i][j]);
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effOpukuJetwrainDisp, effect);
}

void effOpukuJetwrainDisp(CameraId cameraId, EffectEntry* effect) {
    Mtx trans;
    Mtx scale;
    Mtx44 ortho;
    Mtx view;
    GXTexObj texObj;
    f32 proj[7];
    EffOpukuJetwrainN64Work* work;
    s32 alpha;
    s32 row, col;
    u8* buf;

    camGetPtr(cameraId);
    work = effect->userdata;
    alpha = work->alpha;
    GXGetProjectionv(proj);
    MTXOrtho(ortho, 0.0f, 480.0f, 0.0f, 608.0f, 1.0f, 32768.0f);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    buf = smartAlloc(GXGetTexBufferSize(304, 240, GX_TF_RGB565, GX_FALSE, 0), 3)->address;
    GXSetTexCopySrc(0, 0, 608, 480);
    GXSetTexCopyDst(304, 240, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(buf, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&texObj, buf, 304, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_A0, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevColor(GX_TEVREG0, (GXColor){work->color[0], work->color[1], work->color[2], alpha >> 1});
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    effSetVtxDescN64(opuku_jetwrain_vtx);
    {
        Vec up = {0.0f, 1.0f, 0.0f};
        Vec target = {304.0f, 240.0f, 0.0f};
        Vec pos = {304.0f, 240.0f, 100.0f};
        MTXLookAt(view, &pos, &up, &target);
    }
    GXLoadPosMtxImm(view, GX_PNMTX0);
    GXSetCurrentMtx(0);
    for (row = 0; row < 12; row++) {
        s32 rflag = 0, yo0, yo1, y0, y1, yb;
        if (row == 0) {
            yo0 = -4;
            rflag = 1;
        } else {
            yo0 = 0;
        }
        if (row == 11) {
            yo1 = 4;
            rflag = 1;
        } else {
            yo1 = 0;
        }
        yb = row * 16 + 24;
        y0 = yb + yo0;
        y1 = yb + (yo1 + 16);
        for (col = 0; col < 18; col++) {
            s32 cflag = 0, x0, x1, v;
            s32 xo0, xo1;
            if (col == 0) {
                xo0 = -4;
                cflag = 1;
            } else {
                xo0 = 0;
            }
            if (col == 17) {
                xo1 = 4;
                cflag = 1;
            } else {
                xo1 = 0;
            }
            PSMTXScale(scale, 0.00390625f, 0.00390625f, 1.0f);
            x0 = col * 16 + 16 + xo0;
            x1 = col * 16 + 16 + 16 + xo1;
            PSMTXTrans(trans, (f32)x0, (f32)y0, 0.0f);
            PSMTXConcat(scale, trans, scale);
            GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
            if (cflag && rflag) {
                v = 12;
            } else if (cflag) {
                v = 4;
            } else if (rflag) {
                v = 8;
            } else {
                v = 0;
            }
            opuku_jetwrain_vtx[v].x = x0 * 4;
            opuku_jetwrain_vtx[v].y = work->grid[col][row] + y0 * 4;
            opuku_jetwrain_vtx[v + 1].x = x1 * 4;
            opuku_jetwrain_vtx[v + 1].y = work->grid[col + 1][row] + y0 * 4;
            opuku_jetwrain_vtx[v + 2].x = x0 * 4;
            opuku_jetwrain_vtx[v + 2].y = work->grid[col][row + 1] + y1 * 4;
            opuku_jetwrain_vtx[v + 3].x = x1 * 4;
            opuku_jetwrain_vtx[v + 3].y = work->grid[col + 1][row + 1] + y1 * 4;
            DCFlushRange(opuku_jetwrain_vtx, sizeof(opuku_jetwrain_vtx));
            GXInvalidateVtxCache();
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
            tri2(v, v + 3, v + 1, 0, v, v + 2, v + 3, 0);
            sysWaitDrawSync();
        }
    }
    GXSetProjectionv(proj);
}
