#include "eff/n64/eff_kemuri12_n64.h"
#include "eff/eff_n64.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 float_0_8041f55c;
#endif

typedef struct EffKemuri12N64Work {
    u16 type;       // 0x0
    u8 pad_2[2];    // 0x2
    Vec position;   // 0x4
    f32 scale;      // 0x10
    s32 timer;      // 0x14
    s32 frame;      // 0x18
    s32 duration;   // 0x1C
    f32 progress;   // 0x20
    u8 r, g, b, a;  // 0x24
} EffKemuri12N64Work;

static effN64Vtx size32x32_tex32x32_vtx[] = {
    {-16, -16, 0, 0, 0, 0, 0, 0, 255},
    {16, -16, 0, -1024, 0, 0, 0, 0, 255},
    {16, 16, 0, -1024, 1024, 0, 0, 0, 255},
    {-16, 16, 0, 0, 1024, 0, 0, 0, 255},
};

effN64Vtx size32x32_tex32x32_yougan_vtx[] = {
    {-16, -16, 15, 0, 0, 0, 0, 0, 255},
    {16, -16, 15, -1024, 0, 0, 0, 0, 255},
    {16, 16, 15, -1024, 1024, 0, 0, 0, 255},
    {-16, 16, 15, 0, 1024, 0, 0, 0, 255},
    {-6, -16, -15, 0, 0, 0, 0, 0, 255},
    {26, -16, -15, -1024, 0, 0, 0, 0, 255},
    {26, 16, -15, -1024, 1024, 0, 0, 0, 255},
    {-6, 16, -15, 0, 1024, 0, 0, 0, 255},
    {-26, -16, -15, 0, 0, 0, 0, 0, 255},
    {6, -16, -15, -1024, 0, 0, 0, 0, 255},
    {6, 16, -15, -1024, 1024, 0, 0, 0, 255},
    {-26, 16, -15, 0, 1024, 0, 0, 0, 255},
};

void effKemuri12Main(EffectEntry* effect);
void effKemuri12Disp(CameraId cameraId, EffectEntry* effect);

EffectEntry* effKemuri12N64Entry(s32 type, s32 duration, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffKemuri12N64Work* work;

    effect = effEntry();
    effect->type = "Kemuri12N64";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffKemuri12N64Work));
    effect->userdata = work;
    effect->callback = effKemuri12Main;
    work->timer = duration;
    work->frame = 0;
    work->duration = duration;
    work->progress = EXT_LIT(float_0_8041f55c, 0.0f);
    work->type = type;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale = scale;
    switch (type) {
    case 0:
        work->b = 0;
        work->g = 0;
        work->r = 0;
        work->a = 130;
        break;
    case 1:
        work->r = 255;
        work->b = 0;
        work->g = 0;
        work->a = 130;
        break;
    default:
        work->r = 225;
        work->g = 215;
        work->b = 255;
        work->a = 180;
        break;
    }
    return effect;
}

#ifdef NONMATCHING
void effKemuri12Main(EffectEntry* effect) {
    EffKemuri12N64Work* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    work->progress = 8.0f * work->frame / work->duration;
    work->frame++;
    work->timer--;
    if (work->timer < 0) {
        effDelete(effect);
        return;
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effKemuri12Disp, effect);
}
#endif

#pragma opt_propagation off

#ifdef NONMATCHING
void effKemuri12Disp(CameraId cameraId, EffectEntry *effect)
{
  u16 type;
  s32 idx;
  s32 last;
  CameraEntry *camera;
  EffKemuri12N64Work *work;
  s32 ofs;
  s32 alpha;
  effN64Vtx *vtx;
  Mtx mtx;
  Mtx scaleMtx;
  Mtx rot;
  GXTexObj texObj;
  camera = camGetPtr(cameraId);
  work = effect->userdata;
  idx = (s32) work->progress;
  alpha = 256.0f * (work->progress - ((f32) idx));
  type = work->type;
  last = idx == 7;
  GXSetNumChans(0);
  GXSetNumTevStages(3);
  GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
  GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
  GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
  GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
  GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
  GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
  GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
  GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, (GXBool) 1, GX_TEVPREV);
  GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
  GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
  effGetTexObjN64(0xE, &texObj);
  GXLoadTexObj(&texObj, GX_TEXMAP0);
  GXLoadTexObj(&texObj, GX_TEXMAP1);
  PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
  PSMTXRotRad(rot, 'y', 0.017453292f * (-camGetPtr(CAMERA_3D)->viewYaw));
  PSMTXScale(scaleMtx, work->scale, work->scale, work->scale);
  PSMTXConcat(mtx, rot, mtx);
  PSMTXConcat(mtx, scaleMtx, mtx);
  PSMTXRotRad(rot, 'z', 0.34906584f);
  PSMTXConcat(mtx, rot, mtx);
  PSMTXConcat(camera->view, mtx, mtx);
  GXLoadPosMtxImm(mtx, GX_PNMTX0);
  GXSetCurrentMtx(GX_PNMTX0);
  GXSetTevColor(GX_TEVREG0, (GXColor){work->r, work->g, work->b, work->a});
  GXSetTevColor(GX_TEVREG1, (GXColor){0, 0, 0, alpha});
  GXSetNumTexGens(2);
  GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, (GXBool) 0, GX_PTIDENTITY);
  GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, (GXBool) 0, GX_PTIDENTITY);
  ofs = idx << 5;
  PSMTXScale(scaleMtx, 0.00390625f, 0.03125f, 0.0f);
  PSMTXTrans(mtx, ofs, 0.0f, 0.0f);
  PSMTXConcat(scaleMtx, mtx, scaleMtx);
  GXLoadTexMtxImm(scaleMtx, GX_TEXMTX0, GX_MTX2x4);
  if (last)
  {
    PSMTXScale(scaleMtx, 0.00390625f, 0.03125f, 0.0f);
    PSMTXTrans(mtx, ofs + 32, 32.0f, 0.0f);
    PSMTXConcat(scaleMtx, mtx, scaleMtx);
    GXLoadTexMtxImm(scaleMtx, GX_TEXMTX1, GX_MTX2x4);
  }
  else
  {
    PSMTXScale(scaleMtx, 0.00390625f, 0.03125f, 0.0f);
    PSMTXTrans(mtx, ofs + 32, 0.0f, 0.0f);
    PSMTXConcat(scaleMtx, mtx, scaleMtx);
    GXLoadTexMtxImm(scaleMtx, GX_TEXMTX1, GX_MTX2x4);
  }
  switch (type)
  {
    case 0:

    case 2:
      vtx = size32x32_tex32x32_vtx;
      break;

    default:
      work->position.z = work->position.z;
      vtx = size32x32_tex32x32_yougan_vtx;
      break;

  }

  GXSetCullMode(GX_CULL_NONE);
  effSetVtxDescN64(vtx);
  switch (type)
  {
    case 0:

    case 2:
      GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
      tri2(0, 1, 2, 0, 0, 2, 3, 0);
      break;

    default:
      GXBegin(GX_TRIANGLES, GX_VTXFMT0, 18);
      tri2(8, 9, 10, 0, 8, 10, 11, 0);
      tri2(4, 5, 6, 0, 4, 6, 7, 0);
      tri2(0, 1, 2, 0, 0, 2, 3, 0);
      break;

  }

}
#endif
#pragma opt_propagation reset

#ifndef NONMATCHING
// FAKE (asm stopgap): effKemuri12Disp + effKemuri12Main (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".rodata") const Vec vec3_802faa28 = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802faa38 = 4503601774854144.0;
__declspec(section ".sdata2") const f32 float_256_8041f548 = 256.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041f54c = 0.017453292f;
__declspec(section ".sdata2") const f32 float_0p34907_8041f550 = 0.34906584f;
__declspec(section ".sdata2") const f32 float_0p0039062_8041f554 = 0.00390625f;
__declspec(section ".sdata2") const f32 float_0p03125_8041f558 = 0.03125f;
__declspec(section ".sdata2") const f32 float_0_8041f55c = 0.0f;
__declspec(section ".sdata2") const f32 float_32_8041f560 = 32.0f;
__declspec(section ".sdata2") const f32 float_8_8041f564 = 8.0f;
__declspec(section ".sdata2") const u32 unk_80423194;
__declspec(section ".sdata2") const u32 unk_80423190;

asm void effKemuri12Disp(CameraId cameraId, EffectEntry *effect) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stmw r26, 0xe8(r1)
	mr r26, r4
	bl camGetPtr
	lwz r28, 0xc(r26)
	lis r4, double_to_int_802faa38@ha
	lis r0, 0x4330
	mr r30, r3
	lfs f3, 0x20(r28)
	li r3, 0x0
	lfd f1, double_to_int_802faa38@l(r4)
	fctiwz f0, f3
	stw r0, 0xd0(r1)
	lfs f2, float_256_8041f548(r2)
	lhz r31, 0x0(r28)
	stfd f0, 0xc8(r1)
	lwz r27, 0xcc(r1)
	xoris r4, r27, 0x8000
	subfic r0, r27, 0x7
	stw r4, 0xd4(r1)
	cntlzw r0, r0
	srwi r29, r0, 5
	lfd f0, 0xd0(r1)
	fsubs f0, f0, f1
	fsubs f0, f3, f0
	fmuls f0, f2, f0
	fctiwz f0, f0
	stfd f0, 0xd8(r1)
	lwz r26, 0xdc(r1)
	bl GXSetNumChans
	li r3, 0x3
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
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
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
	li r5, 0xf
	li r6, 0xf
	li r7, 0x0
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x4
	li r6, 0x2
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x0
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x1
	li r7, 0x7
	bl GXSetTevAlphaIn
	addi r4, r1, 0x18
	li r3, 0xe
	bl effGetTexObjN64
	addi r3, r1, 0x18
	li r4, 0x0
	bl GXLoadTexObj
	addi r3, r1, 0x18
	li r4, 0x1
	bl GXLoadTexObj
	lfs f1, 0x4(r28)
	addi r3, r1, 0x98
	lfs f2, 0x8(r28)
	lfs f3, 0xc(r28)
	bl PSMTXTrans
	li r3, 0x4
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x38
	lfs f0, float_deg2rad_8041f54c(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	lfs f1, 0x10(r28)
	addi r3, r1, 0x68
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x98
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x98
	addi r4, r1, 0x68
	mr r5, r3
	bl PSMTXConcat
	lfs f1, float_0p34907_8041f550(r2)
	addi r3, r1, 0x38
	li r4, 0x7a
	bl PSMTXRotRad
	addi r3, r1, 0x98
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0x98
	addi r3, r30, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x98
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r0, unk_80423190(r2)
	addi r4, r1, 0x14
	lbz r7, 0x24(r28)
	li r3, 0x1
	stw r0, 0x10(r1)
	lbz r6, 0x25(r28)
	lbz r5, 0x26(r28)
	lbz r0, 0x27(r28)
	stb r7, 0x10(r1)
	stb r6, 0x11(r1)
	stb r5, 0x12(r1)
	stb r0, 0x13(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	bl GXSetTevColor
	lwz r0, unk_80423194(r2)
	addi r4, r1, 0xc
	li r3, 0x2
	stw r0, 0x8(r1)
	stb r26, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl GXSetTevColor
	li r3, 0x2
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	li r4, 0x1
	li r5, 0x4
	li r6, 0x21
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lfs f1, float_0p0039062_8041f554(r2)
	slwi r27, r27, 5
	lfs f2, float_0p03125_8041f558(r2)
	addi r3, r1, 0x68
	lfs f3, float_0_8041f55c(r2)
	bl PSMTXScale
	xoris r3, r27, 0x8000
	lis r0, 0x4330
	stw r3, 0xe4(r1)
	lis r4, double_to_int_802faa38@ha
	lfs f2, float_0_8041f55c(r2)
	addi r3, r1, 0x98
	stw r0, 0xe0(r1)
	lfd f1, double_to_int_802faa38@l(r4)
	fmr f3, f2
	lfd f0, 0xe0(r1)
	fsubs f1, f0, f1
	bl PSMTXTrans
	addi r3, r1, 0x68
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x68
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	cmpwi r29, 0x0
	beq @1
	lfs f1, float_0p0039062_8041f554(r2)
	addi r3, r1, 0x68
	lfs f2, float_0p03125_8041f558(r2)
	lfs f3, float_0_8041f55c(r2)
	bl PSMTXScale
	addi r3, r27, 0x20
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802faa38@ha
	stw r3, 0xe4(r1)
	addi r3, r1, 0x98
	lfd f1, double_to_int_802faa38@l(r4)
	stw r0, 0xe0(r1)
	lfs f2, float_32_8041f560(r2)
	lfd f0, 0xe0(r1)
	lfs f3, float_0_8041f55c(r2)
	fsubs f1, f0, f1
	bl PSMTXTrans
	addi r3, r1, 0x68
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x68
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	b @2
	@1:
	lfs f1, float_0p0039062_8041f554(r2)
	addi r3, r1, 0x68
	lfs f2, float_0p03125_8041f558(r2)
	lfs f3, float_0_8041f55c(r2)
	bl PSMTXScale
	addi r3, r27, 0x20
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802faa38@ha
	stw r3, 0xe4(r1)
	addi r3, r1, 0x98
	lfs f2, float_0_8041f55c(r2)
	stw r0, 0xe0(r1)
	lfd f1, double_to_int_802faa38@l(r4)
	fmr f3, f2
	lfd f0, 0xe0(r1)
	fsubs f1, f0, f1
	bl PSMTXTrans
	addi r3, r1, 0x68
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x68
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	@2:
	cmpwi r31, 0x1
	beq @3
	bge @4
	cmpwi r31, 0x0
	bge @5
	b @3
	@4:
	cmpwi r31, 0x3
	bge @3
	@5:
	lis r3, size32x32_tex32x32_vtx@ha
	addi r0, r3, size32x32_tex32x32_vtx@l
	mr r26, r0
	b @6
	@3:
	lis r3, size32x32_tex32x32_yougan_vtx@ha
	addi r0, r3, size32x32_tex32x32_yougan_vtx@l
	mr r26, r0
	@6:
	li r3, 0x0
	bl GXSetCullMode
	mr r3, r26
	bl effSetVtxDescN64
	cmpwi r31, 0x1
	beq @7
	bge @8
	cmpwi r31, 0x0
	bge @9
	b @7
	@8:
	cmpwi r31, 0x3
	bge @7
	@9:
	li r3, 0x90
	li r4, 0x0
	li r5, 0x6
	bl GXBegin
	li r3, 0x0
	li r4, 0x1
	li r5, 0x2
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x3
	li r10, 0x0
	bl tri2
	b @10
	@7:
	li r3, 0x90
	li r4, 0x0
	li r5, 0x12
	bl GXBegin
	li r3, 0x8
	li r4, 0x9
	li r5, 0xa
	li r6, 0x0
	li r7, 0x8
	li r8, 0xa
	li r9, 0xb
	li r10, 0x0
	bl tri2
	li r3, 0x4
	li r4, 0x5
	li r5, 0x6
	li r6, 0x0
	li r7, 0x4
	li r8, 0x6
	li r9, 0x7
	li r10, 0x0
	bl tri2
	li r3, 0x0
	li r4, 0x1
	li r5, 0x2
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x3
	li r10, 0x0
	bl tri2
	@10:
	lmw r26, 0xe8(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void effKemuri12Main(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, 0x4330
	lis r5, vec3_802faa28@ha
	stw r0, 0x44(r1)
	addi r8, r5, vec3_802faa28@l
	lis r5, double_to_int_802faa38@ha
	lfs f3, float_8_8041f564(r2)
	stw r31, 0x3c(r1)
	mr r31, r3
	lfd f2, double_to_int_802faa38@l(r5)
	lwz r9, 0xc(r3)
	lwz r7, 0x0(r8)
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x8(r1)
	lfs f0, 0x4(r9)
	stw r6, 0xc(r1)
	lfs f1, 0x8(r9)
	stfs f0, 0x8(r1)
	lfs f0, 0xc(r9)
	stw r0, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r5, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r6, 0x14(r1)
	stw r5, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r5, 0x18(r9)
	lwz r0, 0x1c(r9)
	xoris r5, r5, 0x8000
	stw r4, 0x20(r1)
	xoris r0, r0, 0x8000
	stw r5, 0x24(r1)
	lfd f0, 0x20(r1)
	stw r0, 0x2c(r1)
	fsubs f1, f0, f2
	stw r4, 0x28(r1)
	lfd f0, 0x28(r1)
	fmuls f1, f3, f1
	fsubs f0, f0, f2
	fdivs f0, f1, f0
	stfs f0, 0x20(r9)
	lwz r4, 0x18(r9)
	addi r0, r4, 0x1
	stw r0, 0x18(r9)
	lwz r4, 0x14(r9)
	subi r0, r4, 0x1
	stw r0, 0x14(r9)
	lwz r0, 0x14(r9)
	cmpwi r0, 0x0
	bge @1
	bl effDelete
	b @2
	@1:
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effKemuri12Disp@ha
	mr r6, r31
	addi r5, r3, effKemuri12Disp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	@2:
	lwz r0, 0x44(r1)
	lwz r31, 0x3c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}
// clang-format on
#endif
