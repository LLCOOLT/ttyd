#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSFastCast.h>
#include <stdlib.h>

#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 float_0_8041f820;
#endif

typedef struct effN64Vtx {
    s16 x, y, z;   // 0x0
    s16 s, t;      // 0x6
    u8 r, g, b, a; // 0xA
} effN64Vtx;

void effGetTexObjN64(u32 id, GXTexObj* obj);
void effSetVtxDescN64(effN64Vtx* vtx);
void tri2();

typedef struct EffOpukuWcurtainN64Work {
    s32 type;       // 0x0
    Vec position;   // 0x4
    s32 lifetime;   // 0x10
    s32 frame;      // 0x14
    s32 colorR;     // 0x18
    s32 colorG;     // 0x1C
    s32 colorB;     // 0x20
    s32 alpha;      // 0x24
    f32 scale;      // 0x28
    f32 offset[12]; // 0x2C
    f32 speed[12];  // 0x5C
} EffOpukuWcurtainN64Work;

static inline s16 __OSf32tos16(register f32 inF) {
    s32 out;
    register s16* outPtr = (s16*)&out;
    asm { psq_st inF, 0(outPtr), 1, OS_FASTCAST_S16 }
    return *(s16*)&out;
}

static inline void OSf32tos16(f32* f, s16* out) {
    *out = __OSf32tos16(*f);
}

static inline f32 __OSs16tof32(register s16* arg) {
    register f32 ret;
    asm { psq_l ret, 0(arg), 1, OS_FASTCAST_S16 }
    return ret;
}

static inline void OSs16tof32(s16* in, f32* out) {
    *out = __OSs16tof32(in);
}

void effOpukuWcurtainMain(EffectEntry* effect);
void effOpukuWcurtainDisp(CameraId cameraId, EffectEntry* effect);

EffectEntry* effOpukuWcurtainN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffOpukuWcurtainN64Work* work;
    s32 i;

    effect = effEntry();
    effect->type = "OpukuWcurtainN64";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffOpukuWcurtainN64Work));
    effect->userdata = work;
    effect->callback = effOpukuWcurtainMain;
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
    work->colorR = 20;
    work->colorG = 120;
    work->colorB = 255;
    for (i = 0; i < 12; i++) {
        work->offset[i] = EXT_LIT(float_0_8041f820, 0.0f);
        work->speed[i] = -1.0f + 0.01f * (f32)(rand() % 11);
        work->speed[i] *= 0.5f;
    }
    return effect;
}

#ifdef NONMATCHING
void effOpukuWcurtainMain(EffectEntry* effect) {
    EffOpukuWcurtainN64Work* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 i;

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
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
    i = work->frame;
    if (work->lifetime < 16) {
        work->alpha = work->lifetime << 4;
    }
    if (i < 16) {
        work->alpha = (i << 4) + 15;
    }
    for (i = 0; i < 12; i++) {
        work->offset[i] += work->speed[i];
        work->speed[i] += -0.05f;
        if (work->speed[i] > 5.0f) {
            work->speed[i] += 0.1f * (5.0f - work->speed[i]);
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effOpukuWcurtainDisp, effect);
}
#endif

#ifdef NONMATCHING
void effOpukuWcurtainDisp(CameraId cameraId, EffectEntry* effect) {
    CameraEntry* camera;
    EffOpukuWcurtainN64Work* work;
    Mtx mtx;
    Mtx scale;
    GXTexObj texObj;
    Vec v;
    f32 s;
    s32 i;
    effN64Vtx* vtx;
    effN64Vtx* p;
    effN64Vtx* q;
    s32 k;
    s32 j;
    s32 frame;
    s32 m;
    s32 n;
    s32 t;

    camera = camGetPtr(cameraId);
    work = effect->userdata;
    frame = work->frame;
    s = 0.1f * work->scale;
    GXSetTevColor(GX_TEVREG0, (GXColor){work->colorR, work->colorG, work->colorB, work->alpha});
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    effGetTexObjN64(0x8F, &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    PSMTXScale(scale, 0.03125f, 0.03125f, 0.0f);
    GXLoadTexMtxImm(scale, GX_TEXMTX0, GX_MTX2x4);
    GXSetCullMode(GX_CULL_NONE);
    p = (effN64Vtx*)smartAlloc(sizeof(effN64Vtx) * 48, 3)->address;
    vtx = p;
    for (i = 0; i < 12; i++) {
        t = (frame + i * 4) << 5;
        p[0].x = (i * 5 - 30) * 10;
        p[0].y = 600;
        p[0].z = 0;
        p[0].s = t;
        p[0].t = (s32)work->offset[i] << 5;
        p[0].r = 255;
        p[0].g = 255;
        p[0].b = 255;
        p[0].a = 255 - i * 20;
        p[1].x = (i * 5 - 30) * 10;
        p[1].y = (s32)(10.0f * (60.0f + work->offset[i]));
        p[1].z = 0;
        p[1].s = t;
        p[1].t = 0x400;
        p[1].r = 255;
        p[1].g = 255;
        p[1].b = 255;
        p[1].a = 255 - i * 20;
        p += 2;
    }
    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXScale(scale, s, s, s);
    PSMTXConcat(mtx, scale, mtx);
    q = vtx;
    k = i * 2;
    for (j = 0; j < k; j++) {
        OSInitFastCast();
        OSs16tof32(&q->x, &v.x);
        OSs16tof32(&q->y, &v.y);
        OSs16tof32(&q->z, &v.z);
        PSMTXMultVec(mtx, &v, &v);
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

    for (j = 0; j < i - 1; j++) {
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
        frame = j << 1;
        tri2(frame, frame + 2, frame + 1, frame, frame + 1, frame + 2, frame + 3, frame);
    }
}
#endif

#pragma force_active on
__declspec(section ".sdata2") const u32 gap_10_804231E4_sbss2;
#pragma force_active reset

#ifndef NONMATCHING
// FAKE (asm stopgap): effOpukuWcurtainMain (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".rodata") const f32 vec3_802fb298[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".sdata2") const f32 float_0p1_8041f818 = 0.1f;
__declspec(section ".sdata2") const f32 float_0p03125_8041f81c = 0.03125f;
__declspec(section ".sdata2") const f32 float_0_8041f820 = 0.0f;
__declspec(section ".sdata2") const f32 float_10_8041f824 = 10.0f;
__declspec(section ".sdata2") const f32 float_60_8041f828 = 60.0f;
__declspec(section ".sdata2") const f32 float_neg0p05_8041f82c = -0.05f;
__declspec(section ".sdata2") const f32 float_5_8041f830 = 5.0f;

__declspec(section ".sdata2") const u32 unk_804231e0;
asm void effOpukuWcurtainDisp(CameraId cameraId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stmw r26, 0xb8(r1)
	mr r26, r4
	bl camGetPtr
	lwz r30, 0xc(r26)
	mr r31, r3
	lwz r0, unk_804231e0(r2)
	addi r4, r1, 0x18
	lwz r7, 0x18(r30)
	li r3, 0x1
	stw r0, 0x14(r1)
	lwz r6, 0x1c(r30)
	lwz r5, 0x20(r30)
	lwz r0, 0x24(r30)
	stb r7, 0x14(r1)
	lfs f1, float_0p1_8041f818(r2)
	lfs f0, 0x28(r30)
	stb r6, 0x15(r1)
	lwz r26, 0x14(r30)
	fmuls f28, f1, f0
	stb r5, 0x16(r1)
	stb r0, 0x17(r1)
	lwz r0, 0x14(r1)
	stw r0, 0x18(r1)
	bl GXSetTevColor
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
	li r4, 0x2
	li r5, 0xc
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x4
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	addi r4, r1, 0x28
	li r3, 0x8f
	bl effGetTexObjN64
	addi r3, r1, 0x28
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lfs f1, float_0p03125_8041f81c(r2)
	addi r3, r1, 0x48
	lfs f3, float_0_8041f820(r2)
	fmr f2, f1
	bl PSMTXScale
	addi r3, r1, 0x48
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x0
	bl GXSetCullMode
	li r3, 0x2a0
	li r4, 0x3
	bl smartAlloc
	lwz r12, 0x0(r3)
	li r0, 0xc
	mr r9, r30
	slwi r4, r26, 5
	mr r28, r12
	lfs f2, float_10_8041f824(r2)
	lfs f1, float_60_8041f828(r2)
	li r29, 0x0
	li r5, -0x12c
	li r10, 0x0
	mtctr r0
	@1:
	sth r5, 0x0(r12)
	li r0, 0x258
	subfic r11, r10, 0xff
	li r8, 0x0
	sth r0, 0x2(r12)
	li r7, 0xff
	li r0, 0x400
	addi r10, r10, 0x14
	sth r8, 0x4(r12)
	addi r29, r29, 0x1
	sth r4, 0x6(r12)
	lfs f0, 0x2c(r9)
	fctiwz f0, f0
	stfd f0, 0xa8(r1)
	lwz r6, 0xac(r1)
	slwi r6, r6, 5
	sth r6, 0x8(r12)
	stb r7, 0xa(r12)
	stb r7, 0xb(r12)
	stb r7, 0xc(r12)
	stb r11, 0xd(r12)
	sth r5, 0xe(r12)
	addi r5, r5, 0x32
	lfs f0, 0x2c(r9)
	addi r9, r9, 0x4
	fadds f0, f1, f0
	fmuls f0, f2, f0
	fctiwz f0, f0
	stfd f0, 0xb0(r1)
	lwz r6, 0xb4(r1)
	sth r6, 0x10(r12)
	sth r8, 0x12(r12)
	sth r4, 0x14(r12)
	addi r4, r4, 0x80
	sth r0, 0x16(r12)
	stb r7, 0x18(r12)
	stb r7, 0x19(r12)
	stb r7, 0x1a(r12)
	stb r11, 0x1b(r12)
	addi r12, r12, 0x1c
	bdnz @1
	lfs f1, 0x4(r30)
	addi r3, r1, 0x78
	lfs f2, 0x8(r30)
	lfs f3, 0xc(r30)
	bl PSMTXTrans
	fmr f1, f28
	addi r3, r1, 0x48
	fmr f2, f28
	fmr f3, f28
	bl PSMTXScale
	addi r3, r1, 0x78
	addi r4, r1, 0x48
	mr r5, r3
	bl PSMTXConcat
	mr r30, r28
	slwi r27, r29, 1
	li r26, 0x0
	b @2
	@3:
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
	psq_l f0, 0x0(r30), 1, 5
	stfs f0, 0x1c(r1)
	psq_l f0, 0x2(r30), 1, 5
	stfs f0, 0x20(r1)
	psq_l f0, 0x4(r30), 1, 5
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x78
	stfs f0, 0x24(r1)
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
	lfs f31, 0x1c(r1)
	psq_st f31, 0x10(r1), 1, 5
	lha r0, 0x10(r1)
	sth r0, 0x0(r30)
	lfs f30, 0x20(r1)
	psq_st f30, 0xc(r1), 1, 5
	lha r0, 0xc(r1)
	sth r0, 0x2(r30)
	lfs f29, 0x24(r1)
	psq_st f29, 0x8(r1), 1, 5
	addi r26, r26, 0x1
	lha r0, 0x8(r1)
	sth r0, 0x4(r30)
	addi r30, r30, 0xe
	@2:
	cmpw r26, r27
	blt @3
	mr r3, r28
	li r4, 0x2a0
	bl DCFlushRange
	bl GXInvalidateVtxCache
	mr r3, r28
	bl effSetVtxDescN64
	addi r3, r31, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r30, 0x0
	subi r28, r29, 0x1
	mr r27, r30
	b @4
	@5:
	li r3, 0x90
	li r4, 0x0
	li r5, 0x6
	bl GXBegin
	addi r4, r27, 0x2
	addi r5, r27, 0x1
	mr r3, r27
	mr r6, r27
	mr r7, r5
	mr r8, r4
	mr r10, r27
	addi r9, r27, 0x3
	bl tri2
	addi r27, r27, 0x2
	addi r30, r30, 0x1
	@4:
	cmpw r30, r28
	blt @5
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	lmw r26, 0xb8(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm void effOpukuWcurtainMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r4, vec3_802fb298@ha
	stw r0, 0x34(r1)
	addi r5, r4, vec3_802fb298@l
	stw r31, 0x2c(r1)
	mr r31, r3
	lwz r6, 0xc(r3)
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x8(r1)
	lfs f0, 0x4(r6)
	stw r3, 0xc(r1)
	lfs f1, 0x8(r6)
	stfs f0, 0x8(r1)
	lfs f0, 0xc(r6)
	stw r0, 0x10(r1)
	lwz r4, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 29, 29
	beq @1
	rlwinm r3, r3, 0, 30, 28
	li r0, 0x10
	stw r3, 0x0(r31)
	stw r0, 0x10(r6)
	@1:
	lwz r3, 0x10(r6)
	cmpwi r3, 0x3e8
	bge @2
	subi r0, r3, 0x1
	stw r0, 0x10(r6)
	@2:
	lwz r3, 0x14(r6)
	addi r0, r3, 0x1
	stw r0, 0x14(r6)
	lwz r0, 0x10(r6)
	cmpwi r0, 0x0
	bge @3
	mr r3, r31
	bl effDelete
	b @4
	@3:
	cmpwi r0, 0x10
	lwz r3, 0x14(r6)
	bge @5
	slwi r0, r0, 4
	stw r0, 0x24(r6)
	@5:
	cmpwi r3, 0x10
	bge @6
	slwi r3, r3, 4
	addi r0, r3, 0xf
	stw r0, 0x24(r6)
	@6:
	li r0, 0x3
	mr r3, r6
	lfs f3, float_neg0p05_8041f82c(r2)
	li r4, 0x0
	lfs f2, float_5_8041f830(r2)
	lfs f1, float_0p1_8041f818(r2)
	mtctr r0
	@7:
	lfs f4, 0x2c(r3)
	lfs f0, 0x5c(r3)
	fadds f0, f4, f0
	stfs f0, 0x2c(r3)
	lfs f0, 0x5c(r3)
	fadds f0, f0, f3
	stfs f0, 0x5c(r3)
	lfs f4, 0x5c(r3)
	fcmpo cr0, f4, f2
	ble @8
	fsubs f0, f2, f4
	fmadds f0, f1, f0, f4
	stfs f0, 0x5c(r3)
	@8:
	lfs f4, 0x30(r3)
	lfs f0, 0x60(r3)
	fadds f0, f4, f0
	stfs f0, 0x30(r3)
	lfs f0, 0x60(r3)
	fadds f0, f0, f3
	stfs f0, 0x60(r3)
	lfs f4, 0x60(r3)
	fcmpo cr0, f4, f2
	ble @9
	fsubs f0, f2, f4
	fmadds f0, f1, f0, f4
	stfs f0, 0x60(r3)
	@9:
	lfs f4, 0x34(r3)
	lfs f0, 0x64(r3)
	fadds f0, f4, f0
	stfs f0, 0x34(r3)
	lfs f0, 0x64(r3)
	fadds f0, f0, f3
	stfs f0, 0x64(r3)
	lfs f4, 0x64(r3)
	fcmpo cr0, f4, f2
	ble @10
	fsubs f0, f2, f4
	fmadds f0, f1, f0, f4
	stfs f0, 0x64(r3)
	@10:
	lfs f4, 0x38(r3)
	lfs f0, 0x68(r3)
	fadds f0, f4, f0
	stfs f0, 0x38(r3)
	lfs f0, 0x68(r3)
	fadds f0, f0, f3
	stfs f0, 0x68(r3)
	lfs f4, 0x68(r3)
	fcmpo cr0, f4, f2
	ble @11
	fsubs f0, f2, f4
	fmadds f0, f1, f0, f4
	stfs f0, 0x68(r3)
	@11:
	addi r3, r3, 0x10
	addi r4, r4, 0x3
	bdnz @7
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effOpukuWcurtainDisp@ha
	mr r6, r31
	addi r5, r3, effOpukuWcurtainDisp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	@4:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}
// clang-format on
#endif
