#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <stdio.h>
#include <string.h>

static const f32 padz = 0.0f;

#ifdef NONMATCHING
void effNumberGX(Mtx mtx, s32 type, s32 number, u8 alpha, s32 extra) {
    CameraEntry* cam;
    GXColor cols[2];
    GXColor tevColor;
    GXTexObj texObj;
    Mtx posMtx;
    Mtx scaleMtx;
    s8 buf[32];
    s32 len;
    s32 offset;
    s32 pass;
    f32 lo;
    f32 hi;
    s32 half;
    s32 i;

    cam = camGetCurPtr();
    switch (type) {
    case 0:
        cols[1] = (GXColor){ 0xDE, 0x0B, 0x16, alpha };
        cols[0] = (GXColor){ 0xFF, 0xF0, 0xF1, alpha };
        break;
    case 1:
        cols[1] = (GXColor){ 0x68, 0xC0, 0x03, alpha };
        cols[0] = (GXColor){ 0xEB, 0xFE, 0x6F, alpha };
        break;
    case 2:
        cols[1] = (GXColor){ 0xFF, 0x56, 0x27, alpha };
        cols[0] = (GXColor){ 0xFF, 0xC5, 0x18, alpha };
        break;
    case 3:
    default:
        cols[1] = (GXColor){ 0xFF, 0xFF, 0xFF, alpha };
        cols[0] = (GXColor){ 0xFF, 0xFF, 0xFF, alpha };
        break;
    }

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);


    lo = -24.0f;
    hi = 24.0f;
    sprintf((char*)buf, "%d", number);
    len = strlen((char*)buf);
    half = len / 2;
    for (pass = 0, offset = 0; pass < extra + 1; offset += 2, pass++) {
        if (pass == 0) {
            effGetTexObj(1, &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        } else {
            effGetTexObj(0x88, &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            GXSetNumTevStages(3);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE0, (GXTevOp)0xE, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE0, (GXTevOp)0xE, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
            GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            tevColor = (GXColor){ 0x3C, 0x3C, 0x3C, 0xFF };
            GXSetTevColor(GX_TEVREG0, tevColor);
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        }
        for (i = 0; i < len; i++) {
            PSMTXTrans(posMtx, 32.0f * (f32)(half - i) - (f32)offset, (f32)offset, 0.0f);
            PSMTXConcat(mtx, posMtx, posMtx);
            PSMTXConcat(cam->view, posMtx, posMtx);
            GXLoadPosMtxImm(posMtx, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            if (buf[len - 1 - i] == '-') {
                PSMTXScale(scaleMtx, 1.0f / 11.0f, 1.0f, 1.0f);
                PSMTXTrans(posMtx, 10.0f, 0.0f, 0.0f);
                PSMTXConcat(scaleMtx, posMtx, posMtx);
                GXLoadTexMtxImm(posMtx, GX_TEXMTX0, GX_MTX2x4);
            } else {
                PSMTXScale(scaleMtx, 1.0f / 11.0f, 1.0f, 1.0f);
                PSMTXTrans(posMtx, (f32)(buf[len - 1 - i] - '0'), 0.0f, 0.0f);
                PSMTXConcat(scaleMtx, posMtx, posMtx);
                GXLoadTexMtxImm(posMtx, GX_TEXMTX0, GX_MTX2x4);
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(lo, hi, 0.0f);
            GXColor4u8(cols[1].r, cols[1].g, cols[1].b, cols[1].a);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(hi, hi, 0.0f);
            GXColor4u8(cols[1].r, cols[1].g, cols[1].b, cols[1].a);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(hi, lo, 0.0f);
            GXColor4u8(cols[0].r, cols[0].g, cols[0].b, cols[0].a);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(lo, lo, 0.0f);
            GXColor4u8(cols[0].r, cols[0].g, cols[0].b, cols[0].a);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): effNumberGX (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f64 double_to_int_803013f8 = 4503601774854144;
#pragma force_active reset
__declspec(section ".sdata2") const u32 dat_80422358 = 0xDE0B1600;
__declspec(section ".sdata2") const u32 dat_8042235c = 0xFFF0F100;
__declspec(section ".sdata2") const u32 dat_80422360 = 0x68C00300;
__declspec(section ".sdata2") const u32 dat_80422364 = 0xEBFE6F00;
__declspec(section ".sdata2") const u32 dat_80422368 = 0xFF562700;
__declspec(section ".sdata2") const u32 dat_8042236c = 0xFFC51800;
__declspec(section ".sdata2") const u32 dat_80422370 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80422374 = 0xFFFFFF00;
__declspec(section ".sdata2") const f32 float_0p011489_80422378 = 0.011489152f;
__declspec(section ".sdata2") const char str_8042237C[4] = "%d\0";
__declspec(section ".sdata2") const f32 float_32_80422380 = 32.0f;
__declspec(section ".sdata2") const f32 float_0_80422384 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p090909_80422388 = 0.09090909f;
__declspec(section ".sdata2") const f32 float_1_8042238c = 1.0f;
__declspec(section ".sdata2") const f32 float_10_80422390 = 10.0f;
__declspec(section ".sdata2") const f32 float_neg24_80422394 = -24.0f;
__declspec(section ".sdata2") const f32 float_24_80422398 = 24.0f;

asm void effNumberGX(Mtx mtx, s32 type, s32 number, u8 alpha, s32 extra) {
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
	stmw r14, 0x108(r1)
	mr r15, r3
	mr r19, r4
	mr r14, r5
	mr r17, r6
	mr r16, r7
	bl camGetCurPtr
	cmpwi r19, 0x2
	mr r18, r3
	beq @1
	bge @2
	cmpwi r19, 0x0
	beq @3
	bge @4
	b @2
	b @2
	@3:
	lwz r3, dat_80422358(r2)
	lwz r0, dat_8042235c(r2)
	stw r3, 0x28(r1)
	stw r0, 0x24(r1)
	stb r17, 0x2b(r1)
	stb r17, 0x27(r1)
	lwz r3, 0x28(r1)
	lwz r0, 0x24(r1)
	stw r3, 0x30(r1)
	stw r0, 0x2c(r1)
	b @5
	@4:
	lwz r3, dat_80422360(r2)
	lwz r0, dat_80422364(r2)
	stw r3, 0x20(r1)
	stw r0, 0x1c(r1)
	stb r17, 0x23(r1)
	stb r17, 0x1f(r1)
	lwz r3, 0x20(r1)
	lwz r0, 0x1c(r1)
	stw r3, 0x30(r1)
	stw r0, 0x2c(r1)
	b @5
	@1:
	lwz r3, dat_80422368(r2)
	lwz r0, dat_8042236c(r2)
	stw r3, 0x18(r1)
	stw r0, 0x14(r1)
	stb r17, 0x1b(r1)
	stb r17, 0x17(r1)
	lwz r3, 0x18(r1)
	lwz r0, 0x14(r1)
	stw r3, 0x30(r1)
	stw r0, 0x2c(r1)
	b @5
	@2:
	lwz r3, dat_80422370(r2)
	lwz r0, dat_80422374(r2)
	stw r3, 0x10(r1)
	stw r0, 0xc(r1)
	stb r17, 0x13(r1)
	stb r17, 0xf(r1)
	lwz r3, 0x10(r1)
	lwz r0, 0xc(r1)
	stw r3, 0x30(r1)
	stw r0, 0x2c(r1)
	@5:
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
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x0
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xb
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
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	mr r5, r14
	addi r3, r1, 0x34
	la r4, str_8042237C(r2)
	crclr 6
	bl sprintf
	addi r3, r1, 0x34
	bl strlen
	mr r19, r3
	lis r3, double_to_int_803013f8@ha
	srwi r0, r19, 31
	lbz r20, 0x30(r1)
	add r0, r0, r19
	lbz r21, 0x31(r1)
	srawi r17, r0, 1
	lbz r22, 0x32(r1)
	addi r0, r16, 0x1
	lbz r23, 0x33(r1)
	stw r0, 0xf8(r1)
	li r0, 0x0
	lbz r24, 0x2c(r1)
	subi r14, r19, 0x1
	stw r0, 0xf0(r1)
	li r0, 0x0
	lbz r25, 0x2d(r1)
	lis r28, 0x4330
	lbz r26, 0x2e(r1)
	lis r31, 0xcc01
	lbz r27, 0x2f(r1)
	lfs f30, float_32_80422380(r2)
	lfd f31, double_to_int_803013f8@l(r3)
	lfs f28, float_neg24_80422394(r2)
	lfs f29, float_24_80422398(r2)
	stw r0, 0xf4(r1)
	b @6
	@7:
	lwz r0, 0xf0(r1)
	cmpwi r0, 0x0
	bne @8
	addi r4, r1, 0x54
	li r3, 0x1
	bl effGetTexObj
	addi r3, r1, 0x54
	li r4, 0x0
	bl GXLoadTexObj
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
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	b @9
	@8:
	addi r4, r1, 0x54
	li r3, 0x88
	bl effGetTexObj
	addi r3, r1, 0x54
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x3
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0xe
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xe
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x8
	li r5, 0xf
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x4
	li r5, 0x7
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x1
	li r6, 0x2
	li r7, 0x0
	bl GXSetTevSwapModeTable
	li r3, 0x0
	li r4, 0x1
	li r5, 0x1
	bl GXSetTevSwapMode
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
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
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
	li r4, 0x2
	li r5, 0x0
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x4
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	lwz r0, float_0p011489_80422378(r2)
	addi r4, r1, 0x8
	li r3, 0x1
	stw r0, 0x8(r1)
	bl GXSetTevColor
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	@9:
	lwz r0, 0xf4(r1)
	li r16, 0x0
	xoris r29, r0, 0x8000
	b @10
	@11:
	subf r0, r16, r17
	stw r28, 0xd8(r1)
	xoris r0, r0, 0x8000
	lfs f3, float_0_80422384(r2)
	stw r0, 0xdc(r1)
	addi r3, r1, 0xa4
	lfd f0, 0xd8(r1)
	stw r29, 0xe4(r1)
	fsubs f2, f0, f31
	stw r28, 0xe0(r1)
	lfd f0, 0xe0(r1)
	stw r29, 0xec(r1)
	fsubs f1, f0, f31
	stw r28, 0xe8(r1)
	lfd f0, 0xe8(r1)
	fmsubs f1, f30, f2, f1
	fsubs f2, f0, f31
	bl PSMTXTrans
	addi r4, r1, 0xa4
	mr r3, r15
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xa4
	addi r3, r18, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xa4
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	subf r30, r16, r14
	addi r3, r1, 0x34
	lbzx r0, r3, r30
	extsb r0, r0
	cmpwi r0, 0x2d
	bne @12
	lfs f2, float_1_8042238c(r2)
	addi r3, r1, 0x74
	lfs f1, float_0p090909_80422388(r2)
	fmr f3, f2
	bl PSMTXScale
	lfs f2, float_0_80422384(r2)
	addi r3, r1, 0xa4
	lfs f1, float_10_80422390(r2)
	fmr f3, f2
	bl PSMTXTrans
	addi r4, r1, 0xa4
	addi r3, r1, 0x74
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xa4
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	b @13
	@12:
	lfs f2, float_1_8042238c(r2)
	addi r3, r1, 0x74
	lfs f1, float_0p090909_80422388(r2)
	fmr f3, f2
	bl PSMTXScale
	addi r3, r1, 0x34
	lis r0, 0x4330
	lbzx r4, r3, r30
	lis r3, double_to_int_803013f8@ha
	lfs f2, float_0_80422384(r2)
	extsb r4, r4
	stw r0, 0xe8(r1)
	subi r0, r4, 0x30
	lfd f1, double_to_int_803013f8@l(r3)
	xoris r0, r0, 0x8000
	fmr f3, f2
	stw r0, 0xec(r1)
	addi r3, r1, 0xa4
	lfd f0, 0xe8(r1)
	fsubs f1, f0, f1
	bl PSMTXTrans
	addi r4, r1, 0xa4
	addi r3, r1, 0x74
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0xa4
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	@13:
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	stfs f28, -0x8000(r31)
	addi r16, r16, 0x1
	stfs f29, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	stb r20, -0x8000(r31)
	stb r21, -0x8000(r31)
	stb r22, -0x8000(r31)
	stb r23, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	stfs f29, -0x8000(r31)
	stfs f29, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	stb r20, -0x8000(r31)
	stb r21, -0x8000(r31)
	stb r22, -0x8000(r31)
	stb r23, -0x8000(r31)
	lfs f0, float_1_8042238c(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	stfs f29, -0x8000(r31)
	stfs f28, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	stb r24, -0x8000(r31)
	stb r25, -0x8000(r31)
	stb r26, -0x8000(r31)
	stb r27, -0x8000(r31)
	lfs f0, float_1_8042238c(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_1_8042238c(r2)
	stfs f0, -0x8000(r31)
	stfs f28, -0x8000(r31)
	stfs f28, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	stb r24, -0x8000(r31)
	stb r25, -0x8000(r31)
	stb r26, -0x8000(r31)
	stb r27, -0x8000(r31)
	lfs f0, float_0_80422384(r2)
	stfs f0, -0x8000(r31)
	lfs f0, float_1_8042238c(r2)
	stfs f0, -0x8000(r31)
	@10:
	cmpw r16, r19
	blt @11
	lwz r3, 0xf4(r1)
	addi r3, r3, 0x2
	stw r3, 0xf4(r1)
	lwz r3, 0xf0(r1)
	addi r3, r3, 0x1
	stw r3, 0xf0(r1)
	@6:
	lwz r3, 0xf0(r1)
	lwz r0, 0xf8(r1)
	cmpw r3, r0
	blt @7
	li r3, 0x1
	li r4, 0x0
	li r5, 0x1
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	psq_l f31, 0x188(r1), 0, 0
	lfd f31, 0x180(r1)
	psq_l f30, 0x178(r1), 0, 0
	lfd f30, 0x170(r1)
	psq_l f29, 0x168(r1), 0, 0
	lfd f29, 0x160(r1)
	psq_l f28, 0x158(r1), 0, 0
	lfd f28, 0x150(r1)
	lmw r14, 0x108(r1)
	lwz r0, 0x194(r1)
	mtlr r0
	addi r1, r1, 0x190
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8042239C_sdata2[1] = {0};
#pragma force_active reset
