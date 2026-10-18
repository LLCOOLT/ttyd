#include "eff/eff_sleep.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "memory.h"
#include "mario/mariost.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern double sin(double x);
extern double cos(double x);

//local prototypes
void effSleepDisp(CameraId camId, EffectEntry* effect);

#ifdef NONMATCHING
EffectEntry* effSleepEntry(s32 a1, s32 a2, f32 x, f32 y, f32 z, f32 scale, f32 rotation) {
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
	effect->flags |= 2;
	data->type = a1;
	data->position.x = x;
	data->position.y = y;
	data->position.z = z;
	data->scale = scale;
	data->alpha = 0;
	if (a2 <= 0) {
		data->lifetime = 1000;
	}
	else {
		data->lifetime = a2;
	}
	data->age = 0;

	radians = (6.2831855f * rotation) / 360.0f; //TODO: get radians to f26
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
#endif

#ifdef NONMATCHING
void effSleepMain(EffectEntry* effect) {
	effSleepData* data = effect->userdata;
	int i;
	Vec position;

	position = (Vec){ data->position.x, data->position.y, data->position.z };
	if (effect->flags & 4) {
		effect->flags &= ~4;
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
		}
		else {
			data->alpha += 8;
			if (data->alpha > 255) {
				data->alpha = 255;
			}
		}
	}
	dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effSleepDisp, effect);
}
#endif

#pragma push
#pragma opt_propagation off
#pragma opt_lifetimes off


#ifdef NONMATCHING
void effSleepDisp(CameraId camId, EffectEntry* effect) {
	int i;
	s32 off;
	f32 half;
	f32 k;
	f32 one;
	f32 tau;
	f32 x0;
	Mtx mtx;
	Mtx scale;
	s32 base;
	Mtx rot;
	Mtx res;
	GXTexObj texObj;
	f32 w;
	CameraEntry* cam;
	effSleepData* data;
	s32 alpha;
	s32 j;
	f32 xh;
	f32 s0, s1;

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
	effGetTexObj(0x8C, &texObj);
	GXLoadTexObj(&texObj, GX_TEXMAP0);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	w = 8.0f;
	x0 = -w;

	for (i = 1, data++, base = 50; i < effect->count; base += 50, i++, data++) {
		if (data->delay == 0) {
			GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 0xFF, 0xFF, 0xFF, data->alpha * alpha / 255 });
			PSMTXTrans(mtx, data->position.x, data->position.y, data->position.z);
			PSMTXScale(scale, data->scale, data->scale, data->scale);
			PSMTXConcat(mtx, scale, mtx);
			PSMTXConcat(res, mtx, mtx);
			GXLoadPosMtxImm(mtx, GX_PNMTX0);
			GXSetCurrentMtx(GX_PNMTX0);
			tau = 6.2831855f;
			k = 0.015625f;
			half = 0.5f;
			one = 1.0f;
			xh = x0 * half;
			j = 0;
			off = 0;
			do {
				s0 = half * (f32)sin((tau * (f32)(u32)(gp->retraceCount + base + off)) * k);
				s1 = half * (f32)sin((tau * (f32)(u32)(gp->retraceCount + base + (j + 1) * 10)) * k);
				GXBegin(GX_QUADS, GX_VTXFMT0, 4);
				GXPosition3f32(xh + s1, one * (f32)(j + 1), 0.0f);
				GXTexCoord2f32(0.0f, 0.125f * (f32)(7 - j));
				GXPosition3f32(4.0f + s1, one * (f32)(j + 1), 0.0f);
				GXTexCoord2f32(1.0f, 0.125f * (f32)(7 - j));
				GXPosition3f32(4.0f + s0, one * (f32)j, 0.0f);
				GXTexCoord2f32(1.0f, 0.125f * (f32)(8 - j));
				GXPosition3f32(xh + s0, one * (f32)j, 0.0f);
				GXTexCoord2f32(0.0f, 0.125f * (f32)(8 - j));
				j++;
				off += 10;
			} while (j < 8);
		}
	}
}
#endif
#pragma pop

#ifndef NONMATCHING
// FAKE (asm stopgap): effSleepEntry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_80301460[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_80301470 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_80301478 = 4503601774854144;
#pragma force_active reset
__declspec(section ".sdata2") const u32 dat_80422420 = 0xFFFFFF00;
__declspec(section ".sdata2") const f32 float_deg2rad_80422424 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_8_80422428 = 8.0f;
__declspec(section ".sdata2") const f32 float_6p2832_8042242c = 6.2831855f;
__declspec(section ".sdata2") const f32 float_0p015625_80422430 = 0.015625f;
__declspec(section ".sdata2") const f32 float_0p5_80422434 = 0.5f;
__declspec(section ".sdata2") const f32 float_1_80422438 = 1.0f;
__declspec(section ".sdata2") const f32 float_0_8042243c = 0.0f;
__declspec(section ".sdata2") const f32 float_0p125_80422440 = 0.125f;
__declspec(section ".sdata2") const f32 float_4_80422444 = 4.0f;
__declspec(section ".sdata2") const char str_80422448[8] = "Sleep\0\0";
__declspec(section ".sdata2") const f32 float_360_80422450 = 360.0f;
__declspec(section ".sdata2") const f32 float_16_80422454 = 16.0f;
__declspec(section ".sdata2") const f32 float_0p2_80422458 = 0.2f;

asm void effSleepDisp(CameraId camId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0x210(r1)
	mflr r0
	stw r0, 0x214(r1)
	stfd f31, 0x200(r1)
	psq_st f31, 0x208(r1), 0, 0
	stfd f30, 0x1f0(r1)
	psq_st f30, 0x1f8(r1), 0, 0
	stfd f29, 0x1e0(r1)
	psq_st f29, 0x1e8(r1), 0, 0
	stfd f28, 0x1d0(r1)
	psq_st f28, 0x1d8(r1), 0, 0
	stfd f27, 0x1c0(r1)
	psq_st f27, 0x1c8(r1), 0, 0
	stfd f26, 0x1b0(r1)
	psq_st f26, 0x1b8(r1), 0, 0
	stfd f25, 0x1a0(r1)
	psq_st f25, 0x1a8(r1), 0, 0
	stfd f24, 0x190(r1)
	psq_st f24, 0x198(r1), 0, 0
	stfd f23, 0x180(r1)
	psq_st f23, 0x188(r1), 0, 0
	stfd f22, 0x170(r1)
	psq_st f22, 0x178(r1), 0, 0
	stfd f21, 0x160(r1)
	psq_st f21, 0x168(r1), 0, 0
	stfd f20, 0x150(r1)
	psq_st f20, 0x158(r1), 0, 0
	stmw r23, 0x12c(r1)
	mr r24, r4
	mr r26, r3
	lwz r28, 0xc(r4)
	bl camGetPtr
	lwz r25, 0x14(r28)
	mr r23, r3
	lfs f1, 0x4(r28)
	addi r3, r1, 0xc0
	lfs f2, 0x8(r28)
	lfs f3, 0xc(r28)
	bl PSMTXTrans
	lfs f1, 0x10(r28)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r26
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x60
	lfs f0, float_deg2rad_80422424(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r3, r1, 0xc0
	addi r4, r1, 0x60
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xc0
	addi r4, r1, 0x90
	addi r5, r1, 0x30
	bl PSMTXConcat
	addi r4, r1, 0x30
	addi r3, r23, 0x11c
	mr r5, r4
	bl PSMTXConcat
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
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
	bl GXSetTevOp
	addi r4, r1, 0x10
	li r3, 0x8c
	bl effGetTexObj
	addi r3, r1, 0x10
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x0
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	lfs f0, float_8_80422428(r2)
	li r27, 0x1
	li r29, 0x32
	addi r28, r28, 0x24
	fneg f23, f0
	b @1
	@2:
	lwz r0, 0x20(r28)
	cmpwi r0, 0x0
	bne @3
	lwz r0, 0x14(r28)
	lis r3, 0x8081
	subi r5, r3, 0x7f7f
	lwz r6, dat_80422420(r2)
	mullw r0, r0, r25
	addi r4, r1, 0xc
	stw r6, 0x8(r1)
	li r3, 0x4
	mulhw r5, r5, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl GXSetChanMatColor
	lfs f1, 0x4(r28)
	addi r3, r1, 0xc0
	lfs f2, 0x8(r28)
	lfs f3, 0xc(r28)
	bl PSMTXTrans
	lfs f1, 0x10(r28)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0xc0
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0xc0
	addi r3, r1, 0x30
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xc0
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lfs f27, float_0p5_80422434(r2)
	lis r4, double_to_int_mask_80301470@ha
	lis r3, double_to_int_80301478@ha
	lfs f24, float_6p2832_8042242c(r2)
	fmuls f22, f23, f27
	lfd f25, double_to_int_mask_80301470@l(r4)
	lfs f26, float_0p015625_80422430(r2)
	li r26, 0x0
	lfs f28, float_1_80422438(r2)
	li r30, 0x0
	lfd f29, double_to_int_80301478@l(r3)
	lis r31, 0x4330
	lfs f30, float_0p125_80422440(r2)
	lis r23, 0xcc01
	lfs f31, float_4_80422444(r2)
	@4:
	lwz r3, gp(r13)
	add r0, r29, r30
	stw r31, 0xf0(r1)
	lwz r3, 0x1c(r3)
	add r0, r3, r0
	stw r0, 0xf4(r1)
	lfd f0, 0xf0(r1)
	fsubs f0, f0, f25
	fmuls f0, f24, f0
	fmuls f1, f0, f26
	bl sin
	addi r0, r26, 0x1
	lwz r3, gp(r13)
	mulli r0, r0, 0xa
	frsp f0, f1
	lwz r3, 0x1c(r3)
	stw r31, 0xf8(r1)
	add r0, r29, r0
	fmuls f21, f27, f0
	add r0, r3, r0
	stw r0, 0xfc(r1)
	lfd f0, 0xf8(r1)
	fsubs f0, f0, f25
	fmuls f0, f24, f0
	fmuls f1, f0, f26
	bl sin
	frsp f0, f1
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	fmuls f20, f27, f0
	bl GXBegin
	addi r3, r26, 0x1
	subfic r0, r26, 0x7
	xoris r3, r3, 0x8000
	fadds f5, f22, f20
	stw r3, 0x104(r1)
	xoris r4, r0, 0x8000
	xoris r3, r26, 0x8000
	subfic r0, r26, 0x8
	stw r31, 0x100(r1)
	xoris r0, r0, 0x8000
	addi r26, r26, 0x1
	lfd f0, 0x100(r1)
	fadds f3, f31, f20
	stw r4, 0x10c(r1)
	fadds f2, f31, f21
	fsubs f4, f0, f29
	cmpwi r26, 0x8
	stw r31, 0x108(r1)
	fadds f0, f22, f21
	addi r30, r30, 0xa
	lfd f1, 0x108(r1)
	fmuls f6, f28, f4
	stfs f5, -0x8000(r23)
	fsubs f1, f1, f29
	stw r3, 0x114(r1)
	stfs f6, -0x8000(r23)
	fmuls f5, f30, f1
	lfs f1, float_0_8042243c(r2)
	stw r31, 0x110(r1)
	stfs f1, -0x8000(r23)
	lfs f4, float_0_8042243c(r2)
	lfd f1, 0x110(r1)
	stfs f4, -0x8000(r23)
	fsubs f1, f1, f29
	stfs f5, -0x8000(r23)
	stfs f3, -0x8000(r23)
	fmuls f3, f28, f1
	stfs f6, -0x8000(r23)
	lfs f1, float_0_8042243c(r2)
	stw r0, 0x11c(r1)
	stfs f1, -0x8000(r23)
	lfs f1, float_1_80422438(r2)
	stw r31, 0x118(r1)
	stfs f1, -0x8000(r23)
	lfd f1, 0x118(r1)
	stfs f5, -0x8000(r23)
	fsubs f1, f1, f29
	stfs f2, -0x8000(r23)
	stfs f3, -0x8000(r23)
	fmuls f2, f30, f1
	lfs f1, float_0_8042243c(r2)
	stfs f1, -0x8000(r23)
	lfs f1, float_1_80422438(r2)
	stfs f1, -0x8000(r23)
	stfs f2, -0x8000(r23)
	stfs f0, -0x8000(r23)
	stfs f3, -0x8000(r23)
	lfs f0, float_0_8042243c(r2)
	stfs f0, -0x8000(r23)
	lfs f0, float_0_8042243c(r2)
	stfs f0, -0x8000(r23)
	stfs f2, -0x8000(r23)
	blt @4
	@3:
	addi r29, r29, 0x32
	addi r27, r27, 0x1
	addi r28, r28, 0x24
	@1:
	lwz r0, 0x8(r24)
	cmpw r27, r0
	blt @2
	psq_l f31, 0x208(r1), 0, 0
	lfd f31, 0x200(r1)
	psq_l f30, 0x1f8(r1), 0, 0
	lfd f30, 0x1f0(r1)
	psq_l f29, 0x1e8(r1), 0, 0
	lfd f29, 0x1e0(r1)
	psq_l f28, 0x1d8(r1), 0, 0
	lfd f28, 0x1d0(r1)
	psq_l f27, 0x1c8(r1), 0, 0
	lfd f27, 0x1c0(r1)
	psq_l f26, 0x1b8(r1), 0, 0
	lfd f26, 0x1b0(r1)
	psq_l f25, 0x1a8(r1), 0, 0
	lfd f25, 0x1a0(r1)
	psq_l f24, 0x198(r1), 0, 0
	lfd f24, 0x190(r1)
	psq_l f23, 0x188(r1), 0, 0
	lfd f23, 0x180(r1)
	psq_l f22, 0x178(r1), 0, 0
	lfd f22, 0x170(r1)
	psq_l f21, 0x168(r1), 0, 0
	lfd f21, 0x160(r1)
	psq_l f20, 0x158(r1), 0, 0
	lfd f20, 0x150(r1)
	lmw r23, 0x12c(r1)
	lwz r0, 0x214(r1)
	mtlr r0
	addi r1, r1, 0x210
	blr
}

asm void effSleepMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r4, vec3_80301460@ha
	stw r0, 0x34(r1)
	addi r6, r4, vec3_80301460@l
	stw r31, 0x2c(r1)
	mr r31, r3
	lwz r3, 0xc(r3)
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x8(r1)
	lfs f0, 0x4(r3)
	stw r4, 0xc(r1)
	lfs f1, 0x8(r3)
	stfs f0, 0x8(r1)
	lfs f0, 0xc(r3)
	stw r0, 0x10(r1)
	lwz r5, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r4, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r5, 0x14(r1)
	stw r4, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r4, 0x0(r31)
	rlwinm. r0, r4, 0, 29, 29
	beq @1
	rlwinm r4, r4, 0, 30, 28
	li r0, 0x10
	stw r4, 0x0(r31)
	stw r0, 0x18(r3)
	@1:
	lwz r4, 0x18(r3)
	cmpwi r4, 0x3e8
	bge @2
	subi r0, r4, 0x1
	stw r0, 0x18(r3)
	@2:
	lwz r0, 0x18(r3)
	cmpwi r0, 0x20
	bge @3
	slwi r0, r0, 3
	stw r0, 0x14(r3)
	@3:
	lwz r0, 0x18(r3)
	cmpwi r0, 0x0
	bge @4
	mr r3, r31
	bl effDelete
	b @5
	@4:
	lwz r4, 0x1c(r3)
	addi r0, r4, 0x1
	stw r0, 0x1c(r3)
	lwz r0, 0x1c(r3)
	cmpwi r0, 0x20
	bge @6
	slwi r4, r0, 3
	addi r0, r4, 0x7
	stw r0, 0x14(r3)
	@6:
	li r6, 0x1
	li r4, 0xff
	addi r3, r3, 0x24
	b @7
	@8:
	lwz r5, 0x20(r3)
	cmpwi r5, 0x0
	beq @9
	subi r0, r5, 0x1
	stw r0, 0x20(r3)
	b @10
	@9:
	lwz r5, 0x14(r3)
	addi r0, r5, 0x8
	stw r0, 0x14(r3)
	lwz r0, 0x14(r3)
	cmpwi r0, 0xff
	ble @10
	stw r4, 0x14(r3)
	@10:
	addi r6, r6, 0x1
	addi r3, r3, 0x24
	@7:
	lwz r0, 0x8(r31)
	cmpw r6, r0
	blt @8
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effSleepDisp@ha
	mr r6, r31
	addi r5, r3, effSleepDisp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	@5:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm EffectEntry* effSleepEntry(s32 a1, s32 a2, f32 x, f32 y, f32 z, f32 scale, f32 rotation) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stfd f27, 0x50(r1)
	psq_st f27, 0x58(r1), 0, 0
	stfd f26, 0x40(r1)
	psq_st f26, 0x48(r1), 0, 0
	stfd f25, 0x30(r1)
	psq_st f25, 0x38(r1), 0, 0
	stmw r27, 0x1c(r1)
	fmr f29, f1
	mr r28, r3
	fmr f28, f2
	mr r27, r4
	fmr f27, f3
	fmr f26, f4
	fmr f25, f5
	bl effEntry
	la r4, str_80422448(r2)
	mr r31, r3
	stw r4, 0x14(r3)
	li r0, 0x4
	li r3, 0x3
	stw r0, 0x8(r31)
	lwz r0, 0x8(r31)
	mulli r4, r0, 0x24
	bl __memAlloc
	lis r4, effSleepMain@ha
	stw r3, 0xc(r31)
	addi r0, r4, effSleepMain@l
	cmpwi r27, 0x0
	stw r0, 0x10(r31)
	li r0, 0x0
	lwz r4, 0x0(r31)
	ori r4, r4, 0x2
	stw r4, 0x0(r31)
	stw r28, 0x0(r3)
	stfs f29, 0x4(r3)
	stfs f28, 0x8(r3)
	stfs f27, 0xc(r3)
	stfs f26, 0x10(r3)
	stw r0, 0x14(r3)
	bgt @1
	li r0, 0x3e8
	stw r0, 0x18(r3)
	b @2
	@1:
	stw r27, 0x18(r3)
	@2:
	lfs f0, float_6p2832_8042242c(r2)
	lis r4, double_to_int_80301478@ha
	li r0, 0x0
	lfs f27, float_16_80422454(r2)
	fmuls f1, f0, f25
	lfs f0, float_360_80422450(r2)
	stw r0, 0x1c(r3)
	addi r28, r3, 0x24
	lfd f28, double_to_int_80301478@l(r4)
	li r27, 0x1
	fdivs f26, f1, f0
	lfs f29, float_0_8042243c(r2)
	lfs f30, float_0p2_80422458(r2)
	li r29, 0x10
	lfs f31, float_1_80422438(r2)
	lis r30, 0x4330
	b @3
	@4:
	fmr f1, f26
	bl cos
	xoris r0, r27, 0x8000
	frsp f2, f1
	stw r0, 0xc(r1)
	fmr f1, f26
	stw r30, 0x8(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f28
	fmuls f25, f27, f0
	fmuls f0, f25, f2
	stfs f0, 0x4(r28)
	bl sin
	xoris r0, r27, 0x8000
	frsp f0, f1
	stw r0, 0x14(r1)
	li r0, 0x0
	addi r27, r27, 0x1
	fmuls f1, f25, f0
	stw r30, 0x10(r1)
	lfd f0, 0x10(r1)
	stfs f1, 0x8(r28)
	fsubs f0, f0, f28
	stfs f29, 0xc(r28)
	fmadds f0, f30, f0, f31
	stfs f0, 0x10(r28)
	stw r0, 0x14(r28)
	stw r29, 0x20(r28)
	addi r29, r29, 0x10
	addi r28, r28, 0x24
	@3:
	lwz r0, 0x8(r31)
	cmpw r27, r0
	blt @4
	mr r3, r31
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	psq_l f27, 0x58(r1), 0, 0
	lfd f27, 0x50(r1)
	psq_l f26, 0x48(r1), 0, 0
	lfd f26, 0x40(r1)
	psq_l f25, 0x38(r1), 0, 0
	lfd f25, 0x30(r1)
	lmw r27, 0x1c(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8042245C_sdata2[1] = {0};
#pragma force_active reset
