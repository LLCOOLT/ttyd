#include "system.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSFastCast.h>
#include <stdlib.h>

typedef struct effN64Vtx {
    s16 x, y, z;   // 0x0
    s16 s, t;      // 0x6
    u8 r, g, b, a; // 0xA
} effN64Vtx;

void effGetTexObjN64(u32 id, GXTexObj* obj);
void effSetVtxDescN64(effN64Vtx* vtx);
void tri2();
#ifdef NONMATCHING
static inline s16 __OSf32tos16(register f32 inF) {
    s32 out;
    register s16* outPtr = (s16*)&out;
    asm { psq_st inF, 0(outPtr), 1, OS_FASTCAST_S16 }
    return *(s16*)&out;
}
#endif

#ifdef NONMATCHING
static inline void OSf32tos16(f32* f, s16* out) {
    *out = __OSf32tos16(*f);
}
#endif

#ifdef NONMATCHING
static inline f32 __OSs16tof32(register s16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, OS_FASTCAST_S16 }
    return ret;
}
#endif

#ifdef NONMATCHING
static inline void OSs16tof32(s16* in, f32* out) {
    *out = __OSs16tof32(in);
}
#endif
double sin(double);
double cos(double);

static inline f32 dsin(f32 a) { return sin(6.2831855f * a / 360.0f); }
typedef struct EffOpukuWgunN64Work {
    s32 type;        // 0x0
    Vec position;    // 0x4
    Vec start;       // 0x10
    Vec end;         // 0x1C
    s32 total;       // 0x28
    s32 lifetime;    // 0x2C
    s32 frame;       // 0x30
    s32 colorR;      // 0x34
    s32 colorG;      // 0x38
    s32 colorB;      // 0x3C
    s32 alpha;       // 0x40
    s32 color2R;     // 0x44
    s32 color2G;     // 0x48
    s32 color2B;     // 0x4C
    f32 scale;       // 0x50
    s32 count;       // 0x54
    f32 a[12];       // 0x58
    f32 b[12];       // 0x88
    f32 c[12];       // 0xB8
    f32 x[12];       // 0xE8
    f32 y[12];       // 0x118
    f32 z[12];       // 0x148
    s32 delay[12];   // 0x178
    s32 counter[12]; // 0x1A8
    u8 alphas[12];   // 0x1D8
} EffOpukuWgunN64Work;

void effOpukuWgunMain(EffectEntry* effect);
void effOpukuWgunDisp(CameraId cameraId, EffectEntry* effect);

#ifdef NONMATCHING
EffectEntry* effOpukuWgunN64Entry(s32 type, s32 lifetime, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2,
                                  f32 scale) {
    EffectEntry* effect;
    EffOpukuWgunN64Work* work;
    s32 i;
    s32 k;

    effect = effEntry();
    effect->type = "OpukuWgunN64\0\0\0";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffOpukuWgunN64Work));
    effect->userdata = work;
    effect->callback = effOpukuWgunMain;
    effect->flags |= 2;
    work->type = type;
    work->frame = 0;
    if (lifetime <= 0) {
        work->lifetime = 1000;
    } else if (type == 0) {
        work->lifetime = lifetime * 2;
    } else {
        work->lifetime = lifetime * 4;
    }
    work->total = lifetime;
    if (type == 0) {
        work->alpha = 200;
    } else {
        work->alpha = 255;
    }
    work->start.x = x1;
    work->start.y = y1;
    work->start.z = z1;
    work->end.x = x2;
    work->end.y = y2;
    work->end.z = z2;
    work->scale = scale;
    work->colorR = 210;
    work->colorG = 230;
    work->colorB = 255;
    work->color2R = 0;
    work->color2G = 30;
    work->color2B = 205;
    work->count = 0;
    work->position.x = work->start.x;
    work->position.y = work->start.y;
    work->position.z = work->start.z;
    for (i = 0; i < 12; i++) {
        work->a[i] = 10.0f;
        work->b[i] = 2.0f;
        work->c[i] = 0.0f;
        if (type == 0) {
            work->delay[i] = i + 1;
        } else {
            work->delay[i] = 1 + i * 5;
        }
        work->x[i] = work->position.x;
        work->y[i] = work->position.y;
        work->z[i] = work->position.z;
        work->counter[i] = 0;
    }
    return effect;
}
#endif

#ifdef NONMATCHING
void effOpukuWgunMain(EffectEntry* effect) {
    EffOpukuWgunN64Work* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 i;
    s32 type;
    s32 total;
    s32 c;
    f32 t;

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    type = work->type;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        work->lifetime = 16;
    }
    if (work->lifetime < 1000) {
        work->lifetime--;
    }
    work->frame++;
    if (work->lifetime < 0) {
        effDelete(effect);
        return;
    }
    total = work->total;
    work->count++;
    if (work->count > 12) {
        work->count = 12;
    }
    for (i = 0; i < 12; i++) {
        if (work->delay[i] != 0) {
            work->delay[i]--;
            if (work->delay[i] != 0) {
                continue;
            }
        }
        work->counter[i]++;
        c = work->counter[i];
        if (c >= total) {
            c = total;
        }
        t = (f32)c / (f32)total;
        if (type == 0) {
            work->x[i] = work->start.x + t * (work->end.x - work->start.x);
            work->y[i] = work->start.y + t * (work->end.y - work->start.y);
            work->z[i] = work->start.z + t * (work->end.z - work->start.z);
        } else {
            work->x[i] = work->start.x + t * (work->end.x - work->start.x);

            work->y[i] = 120.0f * dsin(180.0f * t) + (work->start.y + t * (work->end.y - work->start.y));
            work->z[i] = work->start.z + t * (work->end.z - work->start.z);
            work->alphas[i] = (u8)(255.0f - 255.0f * t);
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effOpukuWgunDisp, effect);
}
#endif

static u8 a_data[12] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 200, 128, 32};
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".sdata") u32 gap_07_80413BFC_sdata[1] = {0};
#pragma explicit_zero_data reset
#ifdef NONMATCHING
void effOpukuWgunDisp(CameraId cameraId, EffectEntry* effect) {
    s32 k;
    CameraEntry* camera;
    EffOpukuWgunN64Work* work;
    Mtx scale;
    GXTexObj texObj;
    Vec v;
    f32 scl;
    f32 zero = 0.0f;
    f32 rad;
    f32 dx;
    f32 dy;
    f32 ang;
    f32 s;
    s32 i;
    s32 type;
    effN64Vtx* vtx;
    effN64Vtx* p;
    effN64Vtx* q;
    s32 n;
    s32 j;
    s32 a;

    camera = camGetPtr(cameraId);
    work = effect->userdata;
    type = work->type;
    scl = work->scale;



    GXSetTevColor(GX_TEVREG0, (GXColor){work->colorR, work->colorG, work->colorB, work->alpha});
    GXSetTevColor(GX_TEVREG1, (GXColor){work->color2R, work->color2G, work->color2B, 200});
    GXSetCullMode(GX_CULL_NONE);
    p = (effN64Vtx*)smartAlloc(sizeof(effN64Vtx) * 48, 3)->address;
    k = 0;
    vtx = p;
    for (i = 0; i < 12; i++) {
        if (i == 0 || i == 0) {
            ang = -angleABf(work->y[i + 1], -work->x[i + 1], work->y[i], -work->x[i]);
        } else if (i != 11 && work->delay[i] == 0) {
            ang = -angleABf(work->y[i + 1], -work->x[i + 1], work->y[i], -work->x[i]);
        }
        if (work->type == 0) {
            s = 2.0f + 0.5f * (f32)work->counter[i];
            if (s > 6.0f) {
                s = 6.0f;
            }
            a = a_data[i];
        } else {
            s = 1.0f + 0.5f * (f32)work->counter[i];
            if (s > 30.0f) {
                s = 30.0f;
            }
            a = a_data[i] * work->alphas[i] / 255;
        }
        s = s * scl;
        rad = 6.2831855f * ang / 360.0f;
        dx = s * (f32)sin(rad);
        dy = s * (f32)cos(rad);
        p->x = 20.0f * (work->x[i] + dx);
        p->y = 20.0f * (work->y[i] + dy);
        p->z = 20.0f * (work->z[i] + zero);
        p->s = k;
        p->t = 0;
        p->r = (i & 1) * 255;
        p->g = ((i >> 1) & 1) * 255;
        p->b = ((i >> 2) & 1) * 255;
        p->a = a;
        p++;
        p->x = 20.0f * (work->x[i] - dx);
        p->y = 20.0f * (work->y[i] - dy);
        p->z = 20.0f * (work->z[i] + zero);
        p->s = k;
        p->t = 1024;
        p->r = (i & 1) * 255;
        p->g = ((i >> 1) & 1) * 255;
        p->b = ((i >> 2) & 1) * 255;
        p->a = a;
        p++;
        k += 320;
    }
    PSMTXScale(scale, 0.05f, 0.05f, 0.05f);
    q = vtx;
    n = i * 2;
    for (j = 0; j < n; j++) {
        OSInitFastCast();
        OSs16tof32(&q->x, &v.x);
        OSs16tof32(&q->y, &v.y);
        OSs16tof32(&q->z, &v.z);
        PSMTXMultVec(scale, &v, &v);
        OSInitFastCast();
        OSf32tos16(&v.x, &q->x);
        OSf32tos16(&v.y, &q->y);
        OSf32tos16(&v.z, &q->z);
        q++;
    }
    DCFlushRange(vtx, sizeof(effN64Vtx) * 48);
    GXInvalidateVtxCache();
    effSetVtxDescN64(vtx);
    GXLoadPosMtxImm(camera->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (type == 0) {
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumTevStages(2);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        PSMTXScale(scale, 0.015625f, 0.03125f, 0.0f);
        GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
        effGetTexObjN64(0x8D, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
    } else {
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumTevStages(2);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C1, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        PSMTXScale(scale, 0.03125f, 0.03125f, 0.0f);
        GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
        effGetTexObjN64(0x8E, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
    }
    a = i - 1;
    j = 0;
    n = j;
    for (; j < a; j++) {
        if (j >= 0) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
            tri2(n, n + 2, n + 1, n, n + 1, n + 2, n + 3, n);
        }
        n += 2;
    }
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: effOpukuWgunN64Entry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fb2c0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802fb2d0 = 4503601774854144;
__declspec(section ".rodata") const char str_802FB2D8[] = "OpukuWgunN64\000\000\000";
__declspec(section ".sdata2") const u32 dat_8041f840 = 0x000000C8;
__declspec(section ".sdata2") const f32 float_2_8041f844 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041f848 = 0.5f;
__declspec(section ".sdata2") const f32 float_6_8041f84c = 6.0f;
__declspec(section ".sdata2") const f32 float_1_8041f850 = 1.0f;
__declspec(section ".sdata2") const f32 float_30_8041f854 = 30.0f;
__declspec(section ".sdata2") const f32 float_6p2832_8041f858 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041f85c = 360.0f;
__declspec(section ".sdata2") const f32 float_20_8041f860 = 20.0f;
__declspec(section ".sdata2") const f32 float_0_8041f864 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p05_8041f868 = 0.05f;
__declspec(section ".sdata2") const f32 float_0p015625_8041f86c = 0.015625f;
__declspec(section ".sdata2") const f32 float_0p03125_8041f870 = 0.03125f;
__declspec(section ".sdata2") const f32 float_180_8041f874 = 180.0f;
__declspec(section ".sdata2") const f32 float_120_8041f878 = 120.0f;
__declspec(section ".sdata2") const f32 float_255_8041f87c = 255.0f;
__declspec(section ".sdata2") const f32 float_10_8041f880 = 10.0f;

__declspec(section ".sdata2") const u32 gap_10_804231EC_sbss2;
__declspec(section ".sdata2") const u32 unk_804231e8;
// FAKE: whole-unit asm stopgap (C under NONMATCHING); data in target order, force_active, gaps
asm void effOpukuWgunDisp(CameraId cameraId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0x190(r1)
	mflr r0
	stw r0, 0x194(r1)
	stfd f31, 0x180(r1)
	psq_st f31, 0x188(r1), 0, 0
	stfd f30, 0x170(r1)
	psq_st f30, 0x178(r1), 0, 0
	stfd f29, 0x160(r1)
	psq_st f29, 0x168(r1), 0, 0
	stfd f28, 0x150(r1)
	psq_st f28, 0x158(r1), 0, 0
	stfd f27, 0x140(r1)
	psq_st f27, 0x148(r1), 0, 0
	stfd f26, 0x130(r1)
	psq_st f26, 0x138(r1), 0, 0
	stfd f25, 0x120(r1)
	psq_st f25, 0x128(r1), 0, 0
	stfd f24, 0x110(r1)
	psq_st f24, 0x118(r1), 0, 0
	stfd f23, 0x100(r1)
	psq_st f23, 0x108(r1), 0, 0
	stfd f22, 0xf0(r1)
	psq_st f22, 0xf8(r1), 0, 0
	stfd f21, 0xe0(r1)
	psq_st f21, 0xe8(r1), 0, 0
	stmw r22, 0xb8(r1)
	mr r22, r4
	bl camGetPtr
	lwz r27, 0xc(r22)
	mr r31, r3
	lwz r0, unk_804231e8(r0)
	addi r4, r1, 0x20
	lwz r7, 0x34(r27)
	li r3, 0x1
	stw r0, 0x1c(r1)
	lwz r6, 0x38(r27)
	lwz r5, 0x3c(r27)
	lwz r0, 0x40(r27)
	stb r7, 0x1c(r1)
	lwz r25, 0x0(r27)
	stb r6, 0x1d(r1)
	lfs f24, 0x50(r27)
	stb r5, 0x1e(r1)
	stb r0, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x20(r1)
	bl GXSetTevColor
	lwz r0, dat_8041f840(r0)
	addi r4, r1, 0x18
	lwz r6, 0x44(r27)
	li r3, 0x2
	stw r0, 0x14(r1)
	lwz r5, 0x48(r27)
	lwz r0, 0x4c(r27)
	stb r6, 0x14(r1)
	stb r5, 0x15(r1)
	stb r0, 0x16(r1)
	lwz r0, 0x14(r1)
	stw r0, 0x18(r1)
	bl GXSetTevColor
	li r3, 0x0
	bl GXSetCullMode
	li r3, 0x2a0
	li r4, 0x3
	bl smartAlloc
	lwz r23, 0x0(r3)
	li r28, 0x0
	lfs f28, float_6p2832_8041f858(r0)
	mr r30, r27
	lfs f29, float_360_8041f85c(r0)
	mr r24, r23
	lfs f30, float_20_8041f860(r0)
	li r26, 0x0
	lfs f31, float_0_8041f864(r0)
	la r29, a_data(r0)
	L_at1:
	cmpwi r26, 0x0
	beq L_at2
	bne L_at3
	L_at2:
	lfs f1, 0xec(r30)
	lfs f0, 0xe8(r30)
	fneg f2, f1
	lfs f1, 0x11c(r30)
	fneg f4, f0
	lfs f3, 0x118(r30)
	bl angleABf
	fneg f22, f1
	b L_at4
	L_at3:
	cmpwi r26, 0xb
	beq L_at4
	lwz r0, 0x178(r30)
	cmpwi r0, 0x0
	bne L_at4
	lfs f1, 0xec(r30)
	lfs f0, 0xe8(r30)
	fneg f2, f1
	lfs f1, 0x11c(r30)
	fneg f4, f0
	lfs f3, 0x118(r30)
	bl angleABf
	fneg f22, f1
	L_at4:
	lwz r0, 0x0(r27)
	cmpwi r0, 0x0
	bne L_at5
	lwz r5, 0x1a8(r30)
	lis r0, 0x4330
	stw r0, 0x80(r1)
	lis r4, double_to_int_802fb2d0@ha
	xoris r0, r5, 0x8000
	lfd f2, double_to_int_802fb2d0@l(r4)
	stw r0, 0x84(r1)
	lfs f3, float_0p5_8041f848(r0)
	lfd f0, 0x80(r1)
	lfs f1, float_2_8041f844(r0)
	fsubs f2, f0, f2
	lfs f0, float_6_8041f84c(r0)
	fmadds f1, f3, f2, f1
	fmr f21, f1
	fcmpo cr0, f1, f0
	ble L_at6
	fmr f21, f0
	L_at6:
	lbz r22, 0x0(r29)
	b L_at7
	L_at5:
	lwz r5, 0x1a8(r30)
	lis r0, 0x4330
	stw r0, 0x80(r1)
	lis r4, double_to_int_802fb2d0@ha
	xoris r0, r5, 0x8000
	lfd f2, double_to_int_802fb2d0@l(r4)
	stw r0, 0x84(r1)
	lfs f3, float_0p5_8041f848(r0)
	lfd f0, 0x80(r1)
	lfs f1, float_1_8041f850(r0)
	fsubs f2, f0, f2
	lfs f0, float_30_8041f854(r0)
	fmadds f1, f3, f2, f1
	fmr f21, f1
	fcmpo cr0, f1, f0
	ble L_at8
	fmr f21, f0
	L_at8:
	addi r0, r26, 0x1d8
	lis r4, 0x8081
	lbz r5, 0x0(r29)
	subi r4, r4, 0x7f7f
	lbzx r0, r27, r0
	mullw r0, r5, r0
	mulhw r4, r4, r0
	add r0, r4, r0
	srawi r0, r0, 7
	srwi r4, r0, 31
	add r22, r0, r4
	L_at7:
	fmuls f0, f28, f22
	fmuls f21, f21, f24
	fdivs f23, f0, f29
	fmr f1, f23
	bl sin
	frsp f0, f1
	fmr f1, f23
	fmuls f23, f21, f0
	bl cos
	lfs f0, 0xe8(r30)
	extrwi r4, r26, 1, 29
	frsp f1, f1
	clrlwi r5, r26, 31
	fadds f0, f0, f23
	extrwi r0, r26, 1, 30
	mulli r6, r5, 0xff
	addi r26, r26, 0x1
	fmuls f0, f30, f0
	li r5, 0x0
	mulli r7, r0, 0xff
	fmuls f1, f21, f1
	li r0, 0x400
	fctiwz f0, f0
	mulli r8, r4, 0xff
	cmpwi r26, 0xc
	addi r29, r29, 0x1
	stfd f0, 0x80(r1)
	lwz r4, 0x84(r1)
	sth r4, 0x0(r23)
	lfs f0, 0x118(r30)
	fadds f0, f0, f1
	fmuls f0, f30, f0
	fctiwz f0, f0
	stfd f0, 0x88(r1)
	lwz r4, 0x8c(r1)
	sth r4, 0x2(r23)
	lfs f0, 0x148(r30)
	fadds f0, f0, f31
	fmuls f0, f30, f0
	fctiwz f0, f0
	stfd f0, 0x90(r1)
	lwz r4, 0x94(r1)
	sth r4, 0x4(r23)
	sth r28, 0x6(r23)
	sth r5, 0x8(r23)
	stb r6, 0xa(r23)
	stb r7, 0xb(r23)
	stb r8, 0xc(r23)
	stb r22, 0xd(r23)
	lfs f0, 0xe8(r30)
	fsubs f0, f0, f23
	fmuls f0, f30, f0
	fctiwz f0, f0
	stfd f0, 0x98(r1)
	lwz r4, 0x9c(r1)
	sth r4, 0xe(r23)
	lfs f0, 0x118(r30)
	fsubs f0, f0, f1
	fmuls f0, f30, f0
	fctiwz f0, f0
	stfd f0, 0xa0(r1)
	lwz r4, 0xa4(r1)
	sth r4, 0x10(r23)
	lfs f0, 0x148(r30)
	addi r30, r30, 0x4
	fadds f0, f0, f31
	fmuls f0, f30, f0
	fctiwz f0, f0
	stfd f0, 0xa8(r1)
	lwz r4, 0xac(r1)
	sth r4, 0x12(r23)
	sth r28, 0x14(r23)
	addi r28, r28, 0x140
	sth r0, 0x16(r23)
	stb r6, 0x18(r23)
	stb r7, 0x19(r23)
	stb r8, 0x1a(r23)
	stb r22, 0x1b(r23)
	addi r23, r23, 0x1c
	blt L_at1
	lfs f1, float_0p05_8041f868(r0)
	addi r3, r1, 0x50
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r22, r24
	slwi r23, r26, 1
	li r27, 0x0
	b L_at9
	L_at10:
	li r3, 0x4
	oris r3, r3, 0x4
	mtspr GQR2, r3
	li r3, 0x5
	oris r3, r3, 0x5
	mtspr GQR3, r3
	li r3, 0x6
	oris r3, r3, 0x6
	mtspr GQR4, r3
	li r3, 0x7
	oris r3, r3, 0x7
	mtspr GQR5, r3
	psq_l f0, 0x0(r22), 1, 5
	stfs f0, 0x24(r1)
	psq_l f0, 0x2(r22), 1, 5
	stfs f0, 0x28(r1)
	psq_l f0, 0x4(r22), 1, 5
	addi r4, r1, 0x24
	mr r5, r4
	addi r3, r1, 0x50
	stfs f0, 0x2c(r1)
	bl PSMTXMultVec
	li r3, 0x4
	oris r3, r3, 0x4
	mtspr GQR2, r3
	li r3, 0x5
	oris r3, r3, 0x5
	mtspr GQR3, r3
	li r3, 0x6
	oris r3, r3, 0x6
	mtspr GQR4, r3
	li r3, 0x7
	oris r3, r3, 0x7
	mtspr GQR5, r3
	lfs f27, 0x24(r1)
	psq_st f27, 0x10(r1), 1, 5
	lha r0, 0x10(r1)
	sth r0, 0x0(r22)
	lfs f26, 0x28(r1)
	psq_st f26, 0xc(r1), 1, 5
	lha r0, 0xc(r1)
	sth r0, 0x2(r22)
	lfs f25, 0x2c(r1)
	psq_st f25, 0x8(r1), 1, 5
	addi r27, r27, 0x1
	lha r0, 0x8(r1)
	sth r0, 0x4(r22)
	addi r22, r22, 0xe
	L_at9:
	cmpw r27, r23
	blt L_at10
	mr r3, r24
	li r4, 0x2a0
	bl DCFlushRange
	bl GXInvalidateVtxCache
	mr r3, r24
	bl effSetVtxDescN64
	addi r3, r31, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	cmpwi r25, 0x0
	bne L_at11
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
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
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
	li r4, 0x4
	li r5, 0x2
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
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
	li r5, 0xf
	li r6, 0xf
	li r7, 0x0
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
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
	lfs f1, float_0p015625_8041f86c(r0)
	addi r3, r1, 0x50
	lfs f2, float_0p03125_8041f870(r0)
	lfs f3, float_0_8041f864(r0)
	bl PSMTXScale
	addi r3, r1, 0x50
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	addi r4, r1, 0x30
	li r3, 0x8d
	bl effGetTexObjN64
	addi r3, r1, 0x30
	li r4, 0x0
	bl GXLoadTexObj
	b L_at12
	L_at11:
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
	li r4, 0x2
	li r5, 0x8
	li r6, 0xb
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
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
	li r4, 0x4
	li r5, 0x2
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
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
	lfs f1, float_0p03125_8041f870(r0)
	addi r3, r1, 0x50
	lfs f3, float_0_8041f864(r0)
	fmr f2, f1
	bl PSMTXScale
	addi r3, r1, 0x50
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	addi r4, r1, 0x30
	li r3, 0x8e
	bl effGetTexObjN64
	addi r3, r1, 0x30
	li r4, 0x0
	bl GXLoadTexObj
	L_at12:
	li r24, 0x0
	subi r22, r26, 0x1
	mr r23, r24
	b L_at13
	L_at14:
	cmpwi r24, 0x0
	blt L_at15
	li r3, 0x90
	li r4, 0x0
	li r5, 0x6
	bl GXBegin
	addi r4, r23, 0x2
	addi r5, r23, 0x1
	mr r3, r23
	mr r6, r23
	mr r7, r5
	mr r8, r4
	mr r10, r23
	addi r9, r23, 0x3
	bl tri2
	L_at15:
	addi r23, r23, 0x2
	addi r24, r24, 0x1
	L_at13:
	cmpw r24, r22
	blt L_at14
	psq_l f31, 0x188(r1), 0, 0
	lfd f31, 0x180(r1)
	psq_l f30, 0x178(r1), 0, 0
	lfd f30, 0x170(r1)
	psq_l f29, 0x168(r1), 0, 0
	lfd f29, 0x160(r1)
	psq_l f28, 0x158(r1), 0, 0
	lfd f28, 0x150(r1)
	psq_l f27, 0x148(r1), 0, 0
	lfd f27, 0x140(r1)
	psq_l f26, 0x138(r1), 0, 0
	lfd f26, 0x130(r1)
	psq_l f25, 0x128(r1), 0, 0
	lfd f25, 0x120(r1)
	psq_l f24, 0x118(r1), 0, 0
	lfd f24, 0x110(r1)
	psq_l f23, 0x108(r1), 0, 0
	lfd f23, 0x100(r1)
	psq_l f22, 0xf8(r1), 0, 0
	lfd f22, 0xf0(r1)
	psq_l f21, 0xe8(r1), 0, 0
	lfd f21, 0xe0(r1)
	lmw r22, 0xb8(r1)
	lwz r0, 0x194(r1)
	mtlr r0
	addi r1, r1, 0x190
	blr
}

asm void effOpukuWgunMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stmw r26, 0x38(r1)
	lis r4, vec3_802fb2c0@ha
	lwz r30, 0xc(r3)
	addi r5, r4, vec3_802fb2c0@l
	mr r26, r3
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x8(r1)
	lfs f0, 0x4(r30)
	stw r3, 0xc(r1)
	lfs f1, 0x8(r30)
	stfs f0, 0x8(r1)
	lfs f0, 0xc(r30)
	stw r0, 0x10(r1)
	lwz r4, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r3, 0x0(r26)
	lwz r28, 0x0(r30)
	rlwinm. r0, r3, 0, 29, 29
	beq L_at1
	rlwinm r3, r3, 0, 30, 28
	li r0, 0x10
	stw r3, 0x0(r26)
	stw r0, 0x2c(r30)
	L_at1:
	lwz r3, 0x2c(r30)
	cmpwi r3, 0x3e8
	bge L_at2
	subi r0, r3, 0x1
	stw r0, 0x2c(r30)
	L_at2:
	lwz r3, 0x30(r30)
	addi r0, r3, 0x1
	stw r0, 0x30(r30)
	lwz r0, 0x2c(r30)
	cmpwi r0, 0x0
	bge L_at3
	mr r3, r26
	bl effDelete
	b L_at4
	L_at3:
	lwz r3, 0x54(r30)
	lwz r27, 0x28(r30)
	addi r0, r3, 0x1
	stw r0, 0x54(r30)
	lwz r0, 0x54(r30)
	cmpwi r0, 0xc
	ble L_at5
	li r0, 0xc
	stw r0, 0x54(r30)
	L_at5:
	li r29, 0x0
	mr r31, r30
	L_at6:
	lwz r3, 0x178(r31)
	cmpwi r3, 0x0
	beq L_at7
	subi r0, r3, 0x1
	stw r0, 0x178(r31)
	lwz r0, 0x178(r31)
	cmpwi r0, 0x0
	bne L_at8
	L_at7:
	lwz r3, 0x1a8(r31)
	addi r0, r3, 0x1
	stw r0, 0x1a8(r31)
	lwz r0, 0x1a8(r31)
	cmpw r0, r27
	blt L_at9
	mr r0, r27
	L_at9:
	lis r3, 0x4330
	xoris r4, r0, 0x8000
	stw r4, 0x24(r1)
	xoris r0, r27, 0x8000
	lis r5, double_to_int_802fb2d0@ha
	cmpwi r28, 0x0
	stw r3, 0x20(r1)
	lfd f2, double_to_int_802fb2d0@l(r5)
	lfd f0, 0x20(r1)
	stw r0, 0x2c(r1)
	fsubs f1, f0, f2
	stw r3, 0x28(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f2
	fdivs f31, f1, f0
	bne L_at10
	lfs f1, 0x10(r30)
	lfs f0, 0x1c(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0xe8(r31)
	lfs f1, 0x14(r30)
	lfs f0, 0x20(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x118(r31)
	lfs f1, 0x18(r30)
	lfs f0, 0x24(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x148(r31)
	b L_at8
	L_at10:
	lfs f0, float_180_8041f874(r0)
	lfs f2, float_6p2832_8041f858(r0)
	fmuls f1, f0, f31
	lfs f0, float_360_8041f85c(r0)
	lfs f4, 0x10(r30)
	lfs f3, 0x1c(r30)
	fmuls f1, f2, f1
	fsubs f2, f3, f4
	fdivs f1, f1, f0
	fmadds f0, f31, f2, f4
	stfs f0, 0xe8(r31)
	bl sin
	lfs f4, 0x14(r30)
	frsp f3, f1
	lfs f1, 0x20(r30)
	addi r0, r29, 0x1d8
	lfs f0, float_255_8041f87c(r0)
	fsubs f1, f1, f4
	lfs f2, float_120_8041f878(r0)
	fnmsubs f0, f0, f31, f0
	fmadds f1, f31, f1, f4
	fctiwz f0, f0
	fmadds f1, f2, f3, f1
	stfd f0, 0x28(r1)
	stfs f1, 0x118(r31)
	lwz r3, 0x2c(r1)
	lfs f1, 0x18(r30)
	lfs f0, 0x24(r30)
	fsubs f0, f0, f1
	fmadds f0, f31, f0, f1
	stfs f0, 0x148(r31)
	stbx r3, r30, r0
	L_at8:
	addi r29, r29, 0x1
	addi r31, r31, 0x4
	cmpwi r29, 0xc
	blt L_at6
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effOpukuWgunDisp@ha
	mr r6, r26
	addi r5, r3, effOpukuWgunDisp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	L_at4:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	lmw r26, 0x38(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm EffectEntry* effOpukuWgunN64Entry(s32 type, s32 lifetime, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2,
                                  f32 scale) {
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
	stfd f27, 0x40(r1)
	psq_st f27, 0x48(r1), 0, 0
	stfd f26, 0x30(r1)
	psq_st f26, 0x38(r1), 0, 0
	stfd f25, 0x20(r1)
	psq_st f25, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	fmr f25, f1
	mr r30, r3
	fmr f26, f2
	mr r29, r4
	fmr f27, f3
	fmr f28, f4
	fmr f29, f5
	fmr f30, f6
	fmr f31, f7
	bl effEntry
	lis r4, str_802FB2D8@ha
	mr r31, r3
	addi r4, r4, str_802FB2D8@l
	li r0, 0x1
	stw r4, 0x14(r31)
	li r3, 0x3
	li r4, 0x1e4
	stw r0, 0x8(r31)
	bl __memAlloc
	lis r4, effOpukuWgunMain@ha
	stw r3, 0xc(r31)
	addi r4, r4, effOpukuWgunMain@l
	cmpwi r29, 0x0
	stw r4, 0x10(r31)
	li r0, 0x0
	lwz r4, 0x0(r31)
	ori r4, r4, 0x2
	stw r4, 0x0(r31)
	stw r30, 0x0(r3)
	stw r0, 0x30(r3)
	bgt L_at1
	li r0, 0x3e8
	stw r0, 0x2c(r3)
	b L_at2
	L_at1:
	cmpwi r30, 0x0
	bne L_at3
	slwi r0, r29, 1
	stw r0, 0x2c(r3)
	b L_at2
	L_at3:
	slwi r0, r29, 2
	stw r0, 0x2c(r3)
	L_at2:
	cmpwi r30, 0x0
	stw r29, 0x28(r3)
	bne L_at4
	li r0, 0xc8
	stw r0, 0x40(r3)
	b L_at5
	L_at4:
	li r0, 0xff
	stw r0, 0x40(r3)
	L_at5:
	stfs f25, 0x10(r3)
	li r8, 0xd2
	li r7, 0xe6
	li r6, 0xff
	stfs f26, 0x14(r3)
	li r5, 0x0
	li r4, 0x1e
	li r0, 0xcd
	stfs f27, 0x18(r3)
	cmpwi r30, 0x0
	lfs f3, float_10_8041f880(r0)
	mr r9, r3
	stfs f28, 0x1c(r3)
	li r11, 0x0
	lfs f2, float_2_8041f844(r0)
	li r10, 0x1
	stfs f29, 0x20(r3)
	lfs f1, float_0_8041f864(r0)
	stfs f30, 0x24(r3)
	stfs f31, 0x50(r3)
	stw r8, 0x34(r3)
	stw r7, 0x38(r3)
	stw r6, 0x3c(r3)
	stw r5, 0x44(r3)
	stw r4, 0x48(r3)
	stw r0, 0x4c(r3)
	stw r5, 0x54(r3)
	lfs f0, 0x10(r3)
	stfs f0, 0x4(r3)
	lfs f0, 0x14(r3)
	stfs f0, 0x8(r3)
	lfs f0, 0x18(r3)
	stfs f0, 0xc(r3)
	bne L_at6
	li r0, 0x3
	mtctr r0
	L_at7:
	stfs f3, 0x58(r9)
	addi r0, r11, 0x1
	stfs f2, 0x88(r9)
	stfs f1, 0xb8(r9)
	stw r0, 0x178(r9)
	addi r0, r11, 0x2
	lfs f0, 0x4(r3)
	stfs f0, 0xe8(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x118(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x148(r9)
	stw r5, 0x1a8(r9)
	stfs f3, 0x5c(r9)
	stfs f2, 0x8c(r9)
	stfs f1, 0xbc(r9)
	stw r0, 0x17c(r9)
	addi r0, r11, 0x3
	lfs f0, 0x4(r3)
	stfs f0, 0xec(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x11c(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x14c(r9)
	stw r5, 0x1ac(r9)
	stfs f3, 0x60(r9)
	stfs f2, 0x90(r9)
	stfs f1, 0xc0(r9)
	stw r0, 0x180(r9)
	addi r0, r11, 0x4
	addi r11, r11, 0x4
	lfs f0, 0x4(r3)
	stfs f0, 0xf0(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x120(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x150(r9)
	stw r5, 0x1b0(r9)
	stfs f3, 0x64(r9)
	stfs f2, 0x94(r9)
	stfs f1, 0xc4(r9)
	stw r0, 0x184(r9)
	lfs f0, 0x4(r3)
	stfs f0, 0xf4(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x124(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x154(r9)
	stw r5, 0x1b4(r9)
	addi r9, r9, 0x10
	bdnz L_at7
	b L_at8
	L_at6:
	li r0, 0x3
	mtctr r0
	L_at9:
	stfs f3, 0x58(r9)
	stfs f2, 0x88(r9)
	stfs f1, 0xb8(r9)
	stw r10, 0x178(r9)
	addi r10, r10, 0x5
	lfs f0, 0x4(r3)
	stfs f0, 0xe8(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x118(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x148(r9)
	stw r5, 0x1a8(r9)
	stfs f3, 0x5c(r9)
	stfs f2, 0x8c(r9)
	stfs f1, 0xbc(r9)
	stw r10, 0x17c(r9)
	addi r10, r10, 0x5
	lfs f0, 0x4(r3)
	stfs f0, 0xec(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x11c(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x14c(r9)
	stw r5, 0x1ac(r9)
	stfs f3, 0x60(r9)
	stfs f2, 0x90(r9)
	stfs f1, 0xc0(r9)
	stw r10, 0x180(r9)
	addi r10, r10, 0x5
	lfs f0, 0x4(r3)
	stfs f0, 0xf0(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x120(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x150(r9)
	stw r5, 0x1b0(r9)
	stfs f3, 0x64(r9)
	stfs f2, 0x94(r9)
	stfs f1, 0xc4(r9)
	stw r10, 0x184(r9)
	addi r10, r10, 0x5
	lfs f0, 0x4(r3)
	stfs f0, 0xf4(r9)
	lfs f0, 0x8(r3)
	stfs f0, 0x124(r9)
	lfs f0, 0xc(r3)
	stfs f0, 0x154(r9)
	stw r5, 0x1b4(r9)
	addi r9, r9, 0x10
	bdnz L_at9
	L_at8:
	mr r3, r31
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	psq_l f27, 0x48(r1), 0, 0
	lfd f27, 0x40(r1)
	psq_l f26, 0x38(r1), 0, 0
	lfd f26, 0x30(r1)
	psq_l f25, 0x28(r1), 0, 0
	lfd f25, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x94(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}
// clang-format on
#endif
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".sdata2") const u32 gap_09_8041F884_sdata2[1] = {0};
#pragma explicit_zero_data reset
