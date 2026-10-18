#include "eff/eff_starpoint.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "memory.h"
#include <dolphin/mtx.h>
#include <stdlib.h>

#define PI 3.1415927f
#define HALF_PI 1.5707964f

typedef struct EffStarPointWork {
    s32 type;                // 0x0
    s32 timer;               // 0x4
    s32 frame;               // 0x8
    Vec position;            // 0xC
    f32 velX;                // 0x18
    f32 velZ;                // 0x1C
    f32 velY;                // 0x20
    f32 gravity;             // 0x24
    u8 field_0x28[4];        // 0x28
    s32 alpha;               // 0x2C
    s32 delay;               // 0x30
} EffStarPointWork;

// cheap polynomial approximations, valid for x in [0, 2pi]
static inline f32 _sinf(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 x2;

    if (x <= PI) {
        if (x <= HALF_PI) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        }
        else {
            x = HALF_PI - (x - HALF_PI);
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        }
    }
    else if (x < 4.712389f) {
        x = x - PI;
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * x;
        a = -a;
    }
    else {
        x = HALF_PI - (x - 4.712389f);
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * x;
        a = -a;
    }
    return a;
}

static inline f32 _cosf(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 x2;

    if (x <= PI) {
        if (x <= HALF_PI) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        }
        else {
            x = HALF_PI - (x - HALF_PI);
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    }
    else if (x < 4.712389f) {
        x = x - PI;
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    }
    else {
        x = HALF_PI - (x - 4.712389f);
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
EffectEntry* effStarPointEntry(s32 type, s32 count, f32 x, f32 y, f32 z) {
    s32 delay;
    EffectEntry* effect;
    EffStarPointWork* work;
    s32 i;
    f32 r;
    f32 angle;
    f32 speed;

    effect = effEntry();
    effect->type = "StarPoint";
    effect->count = count + 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffStarPointWork) * effect->count);
    effect->userdata = work;
    effect->callback = effStarPointMain;
    work->type = type;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->timer = 60;
    work->frame = 0;

    for (i = 1, delay = 4, work++; i < effect->count; i++, delay += 3, work++) {
        r = (f32)(rand() % 360);
        work->position.x = 0.0f;
        work->position.y = 0.0f;
        work->position.z = 0.0f;
        angle = r * 6.2831855f / 360.0f;
        work->velX = (speed = 2.0f) * _sinf(angle);
        work->velZ = speed * _cosf(angle);
        work->velY = 14.0f;
        work->gravity = speed;
        work->alpha = 0;
        work->delay = delay;
    }
    return effect;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
void effStarPointMain(EffectEntry* effect) {
    EffStarPointWork* work = effect->userdata;
    Vec position;
    s32 i;

    position = (Vec){ work->position.x, work->position.y, work->position.z };
    work->timer--;
    work->frame++;
    if (work->timer < 0) {
        effDelete(effect);
        return;
    }
    for (i = 1, work++; i < effect->count; i++, work++) {
        if (work->delay) {
            work->delay--;
            work->alpha = 0;
        }
        else {
            work->velY -= work->gravity;
            work->position.x += work->velX;
            work->position.y += work->velY;
            work->position.z += work->velZ;
            if (work->velY < 0.0f) {
                work->alpha -= 2;
                if (work->alpha < 0) {
                    work->alpha = 0;
                }
            }
            else {
                work->alpha = 255;
            }
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 1, (DispCallback)effStarPointDisp, effect);
}
#endif

#ifdef NONMATCHING
void effStarPointDisp(CameraId cameraId, EffectEntry* effect) {
    EffStarPointWork* work = effect->userdata;
    Mtx mtx;
    Mtx rot;
    Mtx trans;
    s32 i;

    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rot, 'y', MTXDegToRad(-camGetPtr(CAMERA_3D)->viewYaw));
    PSMTXConcat(mtx, rot, mtx);
    for (i = 1, work++; i < effect->count; i++, work++) {
        if (work->alpha) {
            PSMTXTrans(trans, work->position.x, work->position.y, work->position.z);
            PSMTXConcat(mtx, trans, trans);
            iconDispGx2(trans, 0, 0x18C);
        }
    }
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): effStarPointEntry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".rodata") const f32 vec3_802fdbe0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_802FDBEC[12] = "StarPoint\0\0";
__declspec(section ".rodata") const f64 double_to_int_802fdbf8 = 4503601774854144.0;
__declspec(section ".sdata2") const f32 float_deg2rad_804209c8 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_0_804209cc = 0.0f;
__declspec(section ".sdata2") const f32 float_6p2832_804209d0 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_804209d4 = 360.0f;
__declspec(section ".sdata2") const f32 float_0p00761_804209d8 = 0.00761f;
__declspec(section ".sdata2") const f32 float_0p16605_804209dc = 0.16605f;
__declspec(section ".sdata2") const f32 float_1_804209e0 = 1.0f;
__declspec(section ".sdata2") const f32 float_3p1416_804209e4 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_1p5708_804209e8 = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_804209ec = 4.712389f;
__declspec(section ".sdata2") const f32 float_2_804209f0 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p03705_804209f4 = 0.03705f;
__declspec(section ".sdata2") const f32 float_0p4967_804209f8 = 0.4967f;
__declspec(section ".sdata2") const f32 float_14_804209fc = 14.0f;

asm void effStarPointDisp(CameraId cameraId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	addi r3, r1, 0x68
	stw r31, 0xac(r1)
	stw r30, 0xa8(r1)
	stw r29, 0xa4(r1)
	mr r29, r4
	lwz r31, 0xc(r4)
	lfs f1, 0xc(r31)
	lfs f2, 0x10(r31)
	lfs f3, 0x14(r31)
	bl PSMTXTrans
	li r3, 0x4
	bl camGetPtr
	lfs f1, 0x114(r3)
	addi r3, r1, 0x38
	lfs f0, float_deg2rad_804209c8(r2)
	li r4, 0x79
	fneg f1, f1
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r3, r1, 0x68
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	li r30, 0x1
	addi r31, r31, 0x34
	b @1
	@2:
	lwz r0, 0x2c(r31)
	cmpwi r0, 0x0
	beq @3
	lfs f1, 0xc(r31)
	addi r3, r1, 0x8
	lfs f2, 0x10(r31)
	lfs f3, 0x14(r31)
	bl PSMTXTrans
	addi r4, r1, 0x8
	addi r3, r1, 0x68
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x8
	li r4, 0x0
	li r5, 0x18c
	bl iconDispGx2
	@3:
	addi r30, r30, 0x1
	addi r31, r31, 0x34
	@1:
	lwz r0, 0x8(r29)
	cmpw r30, r0
	blt @2
	lwz r0, 0xb4(r1)
	lwz r31, 0xac(r1)
	lwz r30, 0xa8(r1)
	lwz r29, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm void effStarPointMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r4, vec3_802fdbe0@ha
	stw r0, 0x34(r1)
	addi r6, r4, vec3_802fdbe0@l
	stw r31, 0x2c(r1)
	mr r31, r3
	lwz r7, 0xc(r3)
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x8(r1)
	lfs f0, 0xc(r7)
	stw r4, 0xc(r1)
	lfs f1, 0x10(r7)
	stfs f0, 0x8(r1)
	lfs f0, 0x14(r7)
	stw r0, 0x10(r1)
	lwz r5, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r4, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r5, 0x14(r1)
	stw r4, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r4, 0x4(r7)
	subi r0, r4, 0x1
	stw r0, 0x4(r7)
	lwz r4, 0x8(r7)
	addi r0, r4, 0x1
	stw r0, 0x8(r7)
	lwz r0, 0x4(r7)
	cmpwi r0, 0x0
	bge @1
	bl effDelete
	b @2
	@1:
	li r4, 0x1
	addi r7, r7, 0x34
	b @3
	@4:
	lwz r3, 0x30(r7)
	cmpwi r3, 0x0
	beq @5
	subi r3, r3, 0x1
	li r0, 0x0
	stw r3, 0x30(r7)
	stw r0, 0x2c(r7)
	b @6
	@5:
	lfs f2, 0x20(r7)
	lfs f1, 0x24(r7)
	lfs f0, float_0_804209cc(r2)
	fsubs f1, f2, f1
	stfs f1, 0x20(r7)
	lfs f2, 0xc(r7)
	lfs f1, 0x18(r7)
	fadds f1, f2, f1
	stfs f1, 0xc(r7)
	lfs f2, 0x10(r7)
	lfs f1, 0x20(r7)
	fadds f1, f2, f1
	stfs f1, 0x10(r7)
	lfs f2, 0x14(r7)
	lfs f1, 0x1c(r7)
	fadds f1, f2, f1
	stfs f1, 0x14(r7)
	lfs f1, 0x20(r7)
	fcmpo cr0, f1, f0
	bge @7
	lwz r3, 0x2c(r7)
	subi r0, r3, 0x2
	stw r0, 0x2c(r7)
	lwz r0, 0x2c(r7)
	cmpwi r0, 0x0
	bge @6
	li r0, 0x0
	stw r0, 0x2c(r7)
	b @6
	@7:
	li r0, 0xff
	stw r0, 0x2c(r7)
	@6:
	addi r4, r4, 0x1
	addi r7, r7, 0x34
	@3:
	lwz r0, 0x8(r31)
	cmpw r4, r0
	blt @4
	addi r3, r1, 0x14
	bl dispCalcZ
	lis r3, effStarPointDisp@ha
	mr r6, r31
	addi r5, r3, effStarPointDisp@l
	li r4, 0x1
	li r3, 0x4
	bl dispEntry
	@2:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm EffectEntry* effStarPointEntry(s32 type, s32 count, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stfd f31, 0xc0(r1)
	psq_st f31, 0xc8(r1), 0, 0
	stfd f30, 0xb0(r1)
	psq_st f30, 0xb8(r1), 0, 0
	stfd f29, 0xa0(r1)
	psq_st f29, 0xa8(r1), 0, 0
	stfd f28, 0x90(r1)
	psq_st f28, 0x98(r1), 0, 0
	stfd f27, 0x80(r1)
	psq_st f27, 0x88(r1), 0, 0
	stfd f26, 0x70(r1)
	psq_st f26, 0x78(r1), 0, 0
	stfd f25, 0x60(r1)
	psq_st f25, 0x68(r1), 0, 0
	stfd f24, 0x50(r1)
	psq_st f24, 0x58(r1), 0, 0
	stfd f23, 0x40(r1)
	psq_st f23, 0x48(r1), 0, 0
	stfd f22, 0x30(r1)
	psq_st f22, 0x38(r1), 0, 0
	stmw r26, 0x18(r1)
	fmr f24, f1
	mr r27, r3
	fmr f23, f2
	mr r26, r4
	fmr f22, f3
	bl effEntry
	lis r4, str_802FDBEC@ha
	mr r30, r3
	addi r4, r4, str_802FDBEC@l
	addi r0, r26, 0x1
	stw r4, 0x14(r30)
	li r3, 0x3
	stw r0, 0x8(r30)
	lwz r0, 0x8(r30)
	mulli r4, r0, 0x34
	bl __memAlloc
	lis r4, effStarPointMain@ha
	stw r3, 0xc(r30)
	addi r0, r4, effStarPointMain@l
	lis r5, 0xb60b
	stw r0, 0x10(r30)
	lis r4, double_to_int_802fdbf8@ha
	li r6, 0x3c
	li r0, 0x0
	stw r27, 0x0(r3)
	addi r29, r3, 0x34
	lfd f26, double_to_int_802fdbf8@l(r4)
	addi r26, r5, 0x60b7
	stfs f24, 0xc(r3)
	li r28, 0x1
	lfs f27, float_0_804209cc(r2)
	li r31, 0x4
	stfs f23, 0x10(r3)
	lis r27, 0x4330
	lfs f28, float_6p2832_804209d0(r2)
	stfs f22, 0x14(r3)
	lfs f29, float_360_804209d4(r2)
	stw r6, 0x4(r3)
	lfs f24, float_0p16605_804209dc(r2)
	stw r0, 0x8(r3)
	lfs f25, float_1_804209e0(r2)
	lfs f30, float_3p1416_804209e4(r2)
	lfs f31, float_2_804209f0(r2)
	lfs f23, float_0p4967_804209f8(r2)
	lfs f22, float_14_804209fc(r2)
	b @1
	@2:
	bl rand
	mulhw r0, r26, r3
	stfs f27, 0xc(r29)
	lfs f2, float_0p00761_804209d8(r2)
	stfs f27, 0x10(r29)
	stw r27, 0x8(r1)
	add r0, r0, r3
	srawi r0, r0, 8
	stfs f27, 0x14(r29)
	srwi r4, r0, 31
	add r0, r0, r4
	mulli r0, r0, 0x168
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f26
	fmuls f0, f28, f0
	fdivs f3, f0, f29
	fcmpo cr0, f3, f30
	cror eq, lt, eq
	bne @3
	lfs f1, float_1p5708_804209e8(r2)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @4
	fmuls f0, f3, f3
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f3
	b @5
	@4:
	fsubs f0, f3, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	b @5
	@3:
	lfs f0, float_4p7124_804209ec(r2)
	fcmpo cr0, f3, f0
	bge @6
	fsubs f1, f3, f30
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	fneg f2, f2
	b @5
	@6:
	fsubs f0, f3, f0
	lfs f1, float_1p5708_804209e8(r2)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	fneg f2, f2
	@5:
	fmuls f0, f31, f2
	lfs f2, float_0p03705_804209f4(r2)
	fcmpo cr0, f3, f30
	stfs f0, 0x18(r29)
	cror eq, lt, eq
	bne @7
	lfs f1, float_1p5708_804209e8(r2)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @8
	fmuls f0, f3, f3
	fmsubs f2, f2, f0, f23
	fmadds f2, f2, f0, f25
	b @9
	@8:
	fsubs f0, f3, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f2, f2, f0, f23
	fmadds f2, f2, f0, f25
	fneg f2, f2
	b @9
	@7:
	lfs f0, float_4p7124_804209ec(r2)
	fcmpo cr0, f3, f0
	bge @10
	fsubs f0, f3, f30
	fmuls f0, f0, f0
	fmsubs f2, f2, f0, f23
	fmadds f2, f2, f0, f25
	fneg f2, f2
	b @9
	@10:
	fsubs f0, f3, f0
	lfs f1, float_1p5708_804209e8(r2)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f2, f2, f0, f23
	fmadds f2, f2, f0, f25
	@9:
	fmuls f0, f31, f2
	li r0, 0x0
	addi r28, r28, 0x1
	stfs f0, 0x1c(r29)
	stfs f22, 0x20(r29)
	stfs f31, 0x24(r29)
	stw r0, 0x2c(r29)
	stw r31, 0x30(r29)
	addi r31, r31, 0x3
	addi r29, r29, 0x34
	@1:
	lwz r0, 0x8(r30)
	cmpw r28, r0
	blt @2
	mr r3, r30
	psq_l f31, 0xc8(r1), 0, 0
	lfd f31, 0xc0(r1)
	psq_l f30, 0xb8(r1), 0, 0
	lfd f30, 0xb0(r1)
	psq_l f29, 0xa8(r1), 0, 0
	lfd f29, 0xa0(r1)
	psq_l f28, 0x98(r1), 0, 0
	lfd f28, 0x90(r1)
	psq_l f27, 0x88(r1), 0, 0
	lfd f27, 0x80(r1)
	psq_l f26, 0x78(r1), 0, 0
	lfd f26, 0x70(r1)
	psq_l f25, 0x68(r1), 0, 0
	lfd f25, 0x60(r1)
	psq_l f24, 0x58(r1), 0, 0
	lfd f24, 0x50(r1)
	psq_l f23, 0x48(r1), 0, 0
	lfd f23, 0x40(r1)
	psq_l f22, 0x38(r1), 0, 0
	lfd f22, 0x30(r1)
	lmw r26, 0x18(r1)
	lwz r0, 0xd4(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}
// clang-format on
#endif
