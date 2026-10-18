#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSFastCast.h>
#include <stdlib.h>
#include <string.h>

double sin(double);
double cos(double);

#ifdef NONMATCHING
static inline s16 __OSf32tos16(register f32 inF) {
    u32 tmp;
    register u32* tmpPtr = &tmp;
    register s16 out;
    asm {
        psq_st inF, 0(tmpPtr), 1, OS_FASTCAST_S16
        lha out, 0(tmpPtr)
    }
    return out;
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

#define Vec2Vtx(v, o) do { OSf32tos16(&(v)->x, &(o)[0]); OSf32tos16(&(v)->y, &(o)[1]); OSf32tos16(&(v)->z, &(o)[2]); } while (0)

typedef struct effN64Vtx {
    s16 x, y, z;   // 0x0
    s16 s, t;      // 0x6
    u8 r, g, b, a; // 0xA
} effN64Vtx;

void effGetTexObjN64(u32 id, GXTexObj* obj);
void effSetVtxDescN64(effN64Vtx* vtx);
void tri2();

typedef struct EffKamekiTornadeN64Work {
    s32 type;      // 0x0
    Vec position;  // 0x4
    s32 life;      // 0x10
    s32 frame;     // 0x14
    s32 c0r;       // 0x18
    s32 c0g;       // 0x1C
    s32 c0b;       // 0x20
    s32 alpha;     // 0x24
    s32 c1r;       // 0x28
    s32 c1g;       // 0x2C
    s32 c1b;       // 0x30
    f32 scale;     // 0x34
    f32 px[8];     // 0x38
    f32 py[8];     // 0x58
    f32 pz[8];     // 0x78
    f32 sc[8];     // 0x98
    f32 ang[8];    // 0xB8
    f32 angVel[8]; // 0xD8
    f32 radius[8]; // 0xF8
    f32 rot[8];    // 0x118
    f32 twist;     // 0x138
    f32 scrollS;   // 0x13C
    f32 scrollT;   // 0x140
    f32 unk144;    // 0x144
    f32 unk148;    // 0x148
} EffKamekiTornadeN64Work;

void effKamekiTornadeMain(EffectEntry* effect);
void effKamekiTornadeDisp(CameraId cameraId, EffectEntry* effect);

#ifdef NONMATCHING
EffectEntry* effKamekiTornadeN64Entry(s32 type, s32 life, f32 x, f32 y, f32 z, f32 scale) {
    EffectEntry* effect;
    EffKamekiTornadeN64Work* work;
    s32 i;
    s32 k;

    effect = effEntry();
    effect->type = "KamekiTornadeN64\0\0\0";
    effect->count = 1;
    work = __memAlloc(HEAP_EFFECT, sizeof(EffKamekiTornadeN64Work));
    effect->userdata = work;
    effect->callback = effKamekiTornadeMain;
    effect->flags |= 2;
    work->type = type;
    work->frame = 0;
    if (life <= 0) {
        work->life = 1000;
    } else {
        work->life = life;
    }
    work->alpha = 0;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->scale = scale;
    work->c0r = 255;
    work->c0g = 255;
    work->c0b = 255;
    work->c1r = 255;
    work->c1g = 255;
    work->c1b = 235;
    for (i = 0; i < 8; i++) {
        work->px[i] = x;
        work->py[i] = y;
        work->pz[i] = z;
        work->sc[i] = 0.2f * (f32)i + 1.0f;
        work->ang[i] = (f32)(rand() % 360);
        work->angVel[i] = 0.1f * (f32)(rand() % 100) + 2.0f;
        work->radius[i] = 0.1f * (f32)(rand() % 30);
        work->rot[i] = 0.0f;
    }
    work->twist = 0.0f;
    work->unk144 = 0.0f;
    work->scrollS = 0.0f;
    work->scrollT = 0.0f;
    work->unk148 = 1.0f;
    return effect;
}
#endif

#ifdef NONMATCHING
void effKamekiTornadeMain(EffectEntry* effect) {
    EffKamekiTornadeN64Work* work = effect->userdata;
    Vec position;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    s32 i;
    s32 k;
    s32 life;
    s32 frame;
    f32 scale;

    tmp.x = work->position.x;
    tmp.y = work->position.y;
    tmp.z = work->position.z;
    position = tmp;
    if (effect->flags & 4) {
        effect->flags &= ~4;
        work->life = 16;
    }
    if (work->life < 1000) {
        work->life--;
    }
    work->frame++;
    life = work->life;
    if (life < 0) {
        effDelete(effect);
        return;
    }
    frame = work->frame;
    scale = work->scale;
    if (life < 16) {
        work->alpha = life * 16;
    }
    if (frame < 16) {
        work->alpha = frame * 16 + 15;
    }
    work->px[0] = work->position.x;
    work->py[0] = work->position.y;
    work->pz[0] = work->position.z;
    for (i = 7; i > 0; i--) {
        work->rot[i] = 4.0f * (work->px[i - 1] - work->px[i]);
        work->px[i] = work->px[i - 1];
        work->py[i] = work->py[i - 1] + 5.0f * scale;
        work->pz[i] = work->pz[i - 1];
        if (work->rot[i] > 90.0f) {
            work->rot[i] = 90.0f;
        } else if (work->rot[i] < -90.0f) {
            work->rot[i] = -90.0f;
        }
    }
    work->twist += 10.0f;
    work->scrollS += 12.959999f;
    work->scrollT += 17.28f;
    if (work->scrollS > 64.0f) {
        work->scrollS -= 64.0f;
    }
    if (work->scrollT > 64.0f) {
        work->scrollT -= 64.0f;
    }
    for (i = 0; i < 8; i++) {
        work->ang[i] += work->angVel[i];
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effKamekiTornadeDisp, effect);
}
#endif

#ifdef NONMATCHING
void effKamekiTornadeDisp(CameraId cameraId, EffectEntry* effect) {
    f32 scale;
    s32 i;
    EffKamekiTornadeN64Work* work;
    s32 life;
    effN64Vtx* tmpl;
    effN64Vtx* vtx;
    effN64Vtx* p;
    effN64Vtx* q;
    s32 k;
    s32 j;
    CameraEntry* camera;
    s32 a;
    f32 s;
    f32 r;
    f32 ang;
    Mtx mtx;
    Mtx tex;
    Mtx rot;
    Mtx base;
    GXTexObj texObj;
    Vec axis;
    Vec v1;
    Vec v2;

    camera = camGetPtr(cameraId);
    work = effect->userdata;
    a = work->alpha >> 1;
    life = work->life;
    scale = work->scale;
    GXSetNumChans(0);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_CPREV, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    effGetTexObjN64(0x6C, &texObj);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    GXSetTevColor(GX_TEVREG0, (GXColor){work->c0r, work->c0g, work->c0b, (s32)((f32)a * work->unk148)});
    GXSetTevColor(GX_TEVREG1, (GXColor){work->c1r, work->c1g, work->c1b, 32});
    GXSetCullMode(GX_CULL_NONE);
    tmpl = (effN64Vtx*)smartAlloc(sizeof(effN64Vtx) * 32, 3)->address;
    p = tmpl;
    for (i = 0, k = 0; i < 16; i++, k += 128) {
        p = &tmpl[i];
        r = (6.2831855f * (f32)(i * 360 / 15)) / 360.0f;
        p->x = 100.0f * (f32)cos(r);
        p->y = 0.0f;
        p->z = 100.0f * (f32)sin(r);
        p->s = k;
        p->t = 0;
        q = &tmpl[i + 16];
        q->x = 100.0f * (f32)cos(r);
        q->y = 0.0f;
        q->z = 100.0f * (f32)sin(r);
        q->s = i * 512;
        q->t = 1024;
    }
    PSMTXRotRad(rot, 'z', 0.017453292f * work->unk144);
    PSMTXScale(base, 0.1f, 0.1f, 0.1f);
    PSMTXConcat(rot, base, base);
    for (i = 0; i < 7; i++) {
        vtx = (effN64Vtx*)smartAlloc(sizeof(effN64Vtx) * 32, 3)->address;
        effSetVtxDescN64(vtx);
        PSMTXTrans(mtx, 10.0f * work->px[i], 10.0f * work->py[i], 10.0f * work->pz[i]);
        PSMTXRotRad(rot, 'z', 0.017453292f * work->rot[i]);
        PSMTXConcat(mtx, rot, mtx);
        axis = (Vec){-0.03f, 1.0f, 0.1f};
        PSMTXRotAxisRad(rot, &axis, 0.017453292f * (work->twist + (f32)(i * i)));
        PSMTXConcat(mtx, rot, mtx);
        s = work->sc[i] * scale;
        if (life < 16) {
            s += 0.02f * (f32)(127 - a);
        }
        PSMTXScale(tex, s, scale, s);
        PSMTXConcat(mtx, tex, mtx);
        ang = 10.0f * work->radius[i];
        s = 6.2831855f * work->ang[i] / 360.0f;
        r = (f32)sin(s);
        PSMTXTrans(tex, ang * r, 0, ang * (f32)cos(s));
        PSMTXConcat(mtx, tex, mtx);
        PSMTXConcat(base, mtx, mtx);
        for (j = 0; j < 16; j++) {
            memcpy(&vtx[j], &tmpl[j], sizeof(effN64Vtx));
            OSInitFastCast();
            OSs16tof32(&vtx[j].x, &v1.x);
            OSs16tof32(&vtx[j].y, &v1.y);
            OSs16tof32(&vtx[j].z, &v1.z);
            PSMTXMultVec(mtx, &v1, &v1);
            OSInitFastCast();
            Vec2Vtx(&v1, &vtx[j].x);
        }
        PSMTXTrans(mtx, 10.0f * work->px[i + 1], 10.0f * work->py[i + 1], 10.0f * work->pz[i + 1]);
        PSMTXRotRad(rot, 'z', 0.017453292f * work->rot[i + 1]);
        PSMTXConcat(mtx, rot, mtx);
        axis = (Vec){0.03f, 1.0f, 0.0f};
        PSMTXRotAxisRad(rot, &axis, 0.017453292f * (work->twist + (f32)(i * i)));
        PSMTXConcat(mtx, rot, mtx);
        PSMTXScale(tex, work->sc[i + 1] * scale, scale, work->sc[i + 1] * scale);
        PSMTXConcat(mtx, tex, mtx);
        r = 10.0f * work->radius[i];
        s = (f32)sin(6.2831855f * work->ang[i] / 360.0f);
        PSMTXTrans(tex, r * s, 0.0f, r * (f32)cos(6.2831855f * work->ang[i] / 360.0f));
        PSMTXConcat(mtx, tex, mtx);
        PSMTXConcat(base, mtx, mtx);
        for (j = 16; j < 32; j++) {
            memcpy(&vtx[j], &tmpl[j], sizeof(effN64Vtx));
            OSInitFastCast();
            OSs16tof32(&vtx[j].x, &v2.x);
            OSs16tof32(&vtx[j].y, &v2.y);
            OSs16tof32(&vtx[j].z, &v2.z);
            PSMTXMultVec(mtx, &v2, &v2);
            OSInitFastCast();
            Vec2Vtx(&v2, &vtx[j].x);
        }
        GXInvalidateVtxCache();
        DCFlushRange(vtx, sizeof(effN64Vtx) * 32);
        PSMTXScale(tex, 0.015625f, 0.03125f, 0.0f);
        PSMTXTrans(mtx, work->scrollS + (f32)(i * 4), 0.0f, 0.0f);
        PSMTXConcat(tex, mtx, tex);
        GXLoadTexMtxImm(tex, GX_TEXMTX0, GX_MTX2x4);
        PSMTXScale(tex, 0.015625f, 0.03125f, 0.0f);
        PSMTXTrans(mtx, work->scrollT + (f32)(i * 2), 0.0f, 0.0f);
        PSMTXConcat(tex, mtx, tex);
        GXLoadTexMtxImm(tex, GX_TEXMTX1, GX_MTX2x4);
        GXLoadPosMtxImm(camera->view, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        for (j = 0; j < 15; j++) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 6);
            tri2(j + 16, j + 1, j, 0, j + 1, j + 16, j + 17, 1);
        }
    }
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: effKamekiTornadeN64Entry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fa840[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fa84c[3] = { -0.03f, 1.0f, 0.1f };
__declspec(section ".rodata") const f32 vec3_802fa858[3] = { 0.03f, 1.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802fa868 = 4503601774854144;
__declspec(section ".rodata") const char str_802FA870[] = "KamekiTornadeN64\000\000\000";
__declspec(section ".rodata") const u32 gap_04_802FA884_rodata[1] = { 0x00000000 };
__declspec(section ".sdata2") const u32 dat_8041f1d8 = 0x00000020;
__declspec(section ".sdata2") const f32 float_6p2832_8041f1dc = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041f1e0 = 360.0f;
__declspec(section ".sdata2") const f32 float_100_8041f1e4 = 100.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041f1e8 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_0p1_8041f1ec = 0.1f;
__declspec(section ".sdata2") const f32 float_0p02_8041f1f0 = 0.02f;
__declspec(section ".sdata2") const f32 float_10_8041f1f4 = 10.0f;
__declspec(section ".sdata2") const f32 float_0_8041f1f8 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p015625_8041f1fc = 0.015625f;
__declspec(section ".sdata2") const f32 float_0p03125_8041f200 = 0.03125f;
__declspec(section ".sdata2") const f32 float_5_8041f204 = 5.0f;
__declspec(section ".sdata2") const f32 float_4_8041f208 = 4.0f;
__declspec(section ".sdata2") const f32 float_90_8041f20c = 90.0f;
__declspec(section ".sdata2") const f32 float_neg90_8041f210 = -90.0f;
__declspec(section ".sdata2") const f32 float_12p96_8041f214 = 12.959999f;
__declspec(section ".sdata2") const f32 float_17p28_8041f218 = 17.28f;
__declspec(section ".sdata2") const f32 float_64_8041f21c = 64.0f;
__declspec(section ".sdata2") const f32 float_1_8041f220 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p2_8041f224 = 0.2f;
__declspec(section ".sdata2") const f32 float_2_8041f228 = 2.0f;

__declspec(section ".sdata2") const u32 gap_10_80423164_sbss2;
__declspec(section ".sdata2") const u32 unk_80423160;
// FAKE: whole-unit asm stopgap (C under NONMATCHING); data in target order, force_active, gaps
asm void effKamekiTornadeDisp(CameraId cameraId, EffectEntry* effect) {
	nofralloc
	stwu r1, -0x2a0(r1)
	mflr r0
	stw r0, 0x2a4(r1)
	stfd f31, 0x290(r1)
	psq_st f31, 0x298(r1), 0, 0
	stfd f30, 0x280(r1)
	psq_st f30, 0x288(r1), 0, 0
	stfd f29, 0x270(r1)
	psq_st f29, 0x278(r1), 0, 0
	stfd f28, 0x260(r1)
	psq_st f28, 0x268(r1), 0, 0
	stfd f27, 0x250(r1)
	psq_st f27, 0x258(r1), 0, 0
	stfd f26, 0x240(r1)
	psq_st f26, 0x248(r1), 0, 0
	stfd f25, 0x230(r1)
	psq_st f25, 0x238(r1), 0, 0
	stfd f24, 0x220(r1)
	psq_st f24, 0x228(r1), 0, 0
	stfd f23, 0x210(r1)
	psq_st f23, 0x218(r1), 0, 0
	stfd f22, 0x200(r1)
	psq_st f22, 0x208(r1), 0, 0
	stfd f21, 0x1f0(r1)
	psq_st f21, 0x1f8(r1), 0, 0
	stfd f20, 0x1e0(r1)
	psq_st f20, 0x1e8(r1), 0, 0
	stfd f19, 0x1d0(r1)
	psq_st f19, 0x1d8(r1), 0, 0
	stfd f18, 0x1c0(r1)
	psq_st f18, 0x1c8(r1), 0, 0
	stfd f17, 0x1b0(r1)
	psq_st f17, 0x1b8(r1), 0, 0
	stfd f16, 0x1a0(r1)
	psq_st f16, 0x1a8(r1), 0, 0
	stmw r16, 0x160(r1)
	mr r16, r4
	bl camGetPtr
	lwz r30, 0xc(r16)
	mr r23, r3
	li r3, 0x0
	lwz r0, 0x24(r30)
	lwz r29, 0x10(r30)
	lfs f31, 0x34(r30)
	srawi r16, r0, 1
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
	li r7, 0x8
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
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x4
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
	li r4, 0x2
	li r5, 0x4
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x1
	li r7, 0x7
	bl GXSetTevAlphaIn
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
	addi r4, r1, 0x54
	li r3, 0x6c
	bl effGetTexObjN64
	addi r3, r1, 0x54
	li r4, 0x0
	bl GXLoadTexObj
	addi r3, r1, 0x54
	li r4, 0x1
	bl GXLoadTexObj
	xoris r4, r16, 0x8000
	lis r0, 0x4330
	stw r4, 0x13c(r1)
	lis r5, double_to_int_802fa868@ha
	lfd f2, double_to_int_802fa868@l(r5)
	addi r4, r1, 0x2c
	stw r0, 0x138(r1)
	li r3, 0x1
	lwz r7, unk_80423160(r0)
	lfd f1, 0x138(r1)
	lfs f0, 0x148(r30)
	fsubs f1, f1, f2
	stw r7, 0x28(r1)
	lwz r0, 0x1c(r30)
	lwz r6, 0x18(r30)
	fmuls f0, f1, f0
	lwz r5, 0x20(r30)
	stb r0, 0x29(r1)
	fctiwz f0, f0
	stb r6, 0x28(r1)
	stb r5, 0x2a(r1)
	stfd f0, 0x140(r1)
	lwz r0, 0x144(r1)
	stb r0, 0x2b(r1)
	lwz r0, 0x28(r1)
	stw r0, 0x2c(r1)
	bl GXSetTevColor
	lwz r0, dat_8041f1d8(r0)
	addi r4, r1, 0x24
	lwz r6, 0x28(r30)
	li r3, 0x2
	stw r0, 0x20(r1)
	lwz r5, 0x2c(r30)
	lwz r0, 0x30(r30)
	stb r6, 0x20(r1)
	stb r5, 0x21(r1)
	stb r0, 0x22(r1)
	lwz r0, 0x20(r1)
	stw r0, 0x24(r1)
	bl GXSetTevColor
	li r3, 0x0
	bl GXSetCullMode
	li r3, 0x1c0
	li r4, 0x3
	bl smartAlloc
	lis r4, double_to_int_802fa868@ha
	lwz r28, 0x0(r3)
	li r27, 0x0
	lis r5, 0x8889
	lfs f29, float_6p2832_8041f1dc(r0)
	mr r26, r28
	lfd f28, double_to_int_802fa868@l(r4)
	mr r20, r27
	lfs f27, float_360_8041f1e0(r0)
	subi r25, r5, 0x7777
	lfs f26, float_100_8041f1e4(r0)
	li r17, 0x0
	li r19, 0x0
	lis r24, 0x4330
	L_at1:
	mulhw r0, r25, r27
	stw r24, 0x140(r1)
	add r0, r0, r27
	srawi r0, r0, 3
	srwi r4, r0, 31
	add r0, r0, r4
	xoris r0, r0, 0x8000
	stw r0, 0x144(r1)
	lfd f0, 0x140(r1)
	fsubs f0, f0, f28
	fmuls f0, f29, f0
	fdivs f19, f0, f27
	fmr f1, f19
	bl cos
	frsp f0, f1
	li r0, 0x0
	fmr f1, f19
	fmuls f0, f26, f0
	fctiwz f0, f0
	stfd f0, 0x138(r1)
	lwz r4, 0x13c(r1)
	sth r4, 0x0(r26)
	sth r0, 0x2(r26)
	bl sin
	frsp f0, f1
	addi r0, r17, 0x10
	mulli r0, r0, 0xe
	fmr f1, f19
	li r4, 0x0
	fmuls f0, f26, f0
	add r18, r28, r0
	fctiwz f0, f0
	stfd f0, 0x148(r1)
	lwz r0, 0x14c(r1)
	sth r0, 0x4(r26)
	sth r19, 0x6(r26)
	sth r4, 0x8(r26)
	bl cos
	frsp f0, f1
	li r0, 0x0
	fmr f1, f19
	fmuls f0, f26, f0
	fctiwz f0, f0
	stfd f0, 0x150(r1)
	lwz r4, 0x154(r1)
	sth r4, 0x0(r18)
	sth r0, 0x2(r18)
	bl sin
	frsp f0, f1
	addi r17, r17, 0x1
	cmpwi r17, 0x10
	li r0, 0x400
	addi r26, r26, 0xe
	addi r27, r27, 0x168
	fmuls f0, f26, f0
	addi r19, r19, 0x80
	fctiwz f0, f0
	stfd f0, 0x158(r1)
	lwz r4, 0x15c(r1)
	sth r4, 0x4(r18)
	sth r20, 0x6(r18)
	addi r20, r20, 0x200
	sth r0, 0x8(r18)
	blt L_at1
	lfs f1, float_deg2rad_8041f1e8(r0)
	addi r3, r1, 0xa4
	lfs f0, 0x144(r30)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_0p1_8041f1ec(r0)
	addi r3, r1, 0x74
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r4, r1, 0x74
	addi r3, r1, 0xa4
	mr r5, r4
	bl PSMTXConcat
	subfic r0, r16, 0x7f
	li r31, 0x0
	xoris r0, r0, 0x8000
	lis r24, 0x4330
	lis r4, double_to_int_802fa868@ha
	stw r0, 0x15c(r1)
	addi r6, r4, double_to_int_802fa868@l
	lis r5, vec3_802fa84c@ha
	stw r24, 0x158(r1)
	lis r4, vec3_802fa858@ha
	lfd f26, 0x0(r6)
	mr r20, r30
	lfd f0, 0x158(r1)
	mr r19, r31
	lfs f1, float_0p02_8041f1f0(r0)
	mr r18, r31
	fsubs f0, f0, f26
	lfs f27, float_10_8041f1f4(r0)
	lfs f28, float_deg2rad_8041f1e8(r0)
	addi r25, r5, vec3_802fa84c@l
	lfs f29, float_6p2832_8041f1dc(r0)
	addi r26, r4, vec3_802fa858@l
	fmuls f19, f1, f0
	lfs f30, float_360_8041f1e0(r0)
	L_at2:
	li r3, 0x1c0
	li r4, 0x3
	bl smartAlloc
	lwz r27, 0x0(r3)
	mr r3, r27
	bl effSetVtxDescN64
	lfs f1, 0x38(r20)
	addi r3, r1, 0x104
	lfs f2, 0x58(r20)
	lfs f0, 0x78(r20)
	fmuls f1, f27, f1
	fmuls f2, f27, f2
	fmuls f3, f27, f0
	bl PSMTXTrans
	lfs f0, 0x118(r20)
	addi r3, r1, 0xa4
	li r4, 0x7a
	fmuls f1, f28, f0
	bl PSMTXRotRad
	addi r3, r1, 0x104
	addi r4, r1, 0xa4
	mr r5, r3
	bl PSMTXConcat
	mullw r17, r31, r31
	lwz r7, 0x0(r25)
	lwz r6, 0x4(r25)
	addi r3, r1, 0xa4
	lwz r5, 0x8(r25)
	addi r4, r1, 0x48
	xoris r0, r17, 0x8000
	stw r24, 0x158(r1)
	stw r0, 0x15c(r1)
	lfd f0, 0x158(r1)
	stw r7, 0x48(r1)
	fsubs f0, f0, f26
	stw r6, 0x4c(r1)
	stw r5, 0x50(r1)
	lfs f1, 0x138(r30)
	fadds f0, f1, f0
	fmuls f1, f28, f0
	bl PSMTXRotAxisRad
	addi r3, r1, 0x104
	addi r4, r1, 0xa4
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0x98(r20)
	cmpwi r29, 0x10
	fmuls f1, f0, f31
	bge L_at3
	fadds f1, f1, f19
	L_at3:
	fmr f2, f31
	addi r3, r1, 0xd4
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x104
	addi r4, r1, 0xd4
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0xb8(r20)
	lfs f1, 0xf8(r20)
	fmuls f0, f29, f0
	fmuls f16, f27, f1
	fdivs f17, f0, f30
	fmr f1, f17
	bl sin
	frsp f18, f1
	fmr f1, f17
	bl cos
	frsp f0, f1
	lfs f2, float_0_8041f1f8(r0)
	fmuls f1, f16, f18
	addi r3, r1, 0xd4
	fmuls f3, f16, f0
	bl PSMTXTrans
	addi r3, r1, 0x104
	addi r4, r1, 0xd4
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0x104
	addi r3, r1, 0x74
	mr r5, r4
	bl PSMTXConcat
	mr r22, r28
	mr r21, r27
	li r16, 0x0
	L_at4:
	mr r3, r21
	mr r4, r22
	li r5, 0xe
	bl memcpy
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
	psq_l f0, 0x0(r21), 1, 5
	stfs f0, 0x3c(r1)
	psq_l f0, 0x2(r21), 1, 5
	stfs f0, 0x40(r1)
	psq_l f0, 0x4(r21), 1, 5
	addi r4, r1, 0x3c
	mr r5, r4
	addi r3, r1, 0x104
	stfs f0, 0x44(r1)
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
	lfs f25, 0x3c(r1)
	psq_st f25, 0x1c(r1), 1, 5
	lha r0, 0x1c(r1)
	sth r0, 0x0(r21)
	lfs f24, 0x40(r1)
	psq_st f24, 0x18(r1), 1, 5
	lha r0, 0x18(r1)
	sth r0, 0x2(r21)
	lfs f23, 0x44(r1)
	psq_st f23, 0x14(r1), 1, 5
	addi r22, r22, 0xe
	addi r16, r16, 0x1
	lha r0, 0x14(r1)
	sth r0, 0x4(r21)
	addi r21, r21, 0xe
	cmpwi r16, 0x10
	blt L_at4
	lfs f1, 0x3c(r20)
	addi r3, r1, 0x104
	lfs f2, 0x5c(r20)
	lfs f0, 0x7c(r20)
	fmuls f1, f27, f1
	fmuls f2, f27, f2
	fmuls f3, f27, f0
	bl PSMTXTrans
	lfs f0, 0x11c(r20)
	addi r3, r1, 0xa4
	li r4, 0x7a
	fmuls f1, f28, f0
	bl PSMTXRotRad
	addi r3, r1, 0x104
	addi r4, r1, 0xa4
	mr r5, r3
	bl PSMTXConcat
	xoris r0, r17, 0x8000
	lwz r6, 0x0(r26)
	stw r0, 0x15c(r1)
	addi r3, r1, 0xa4
	lwz r5, 0x4(r26)
	addi r4, r1, 0x48
	stw r24, 0x158(r1)
	lwz r0, 0x8(r26)
	lfd f0, 0x158(r1)
	stw r6, 0x48(r1)
	fsubs f0, f0, f26
	stw r5, 0x4c(r1)
	stw r0, 0x50(r1)
	lfs f1, 0x138(r30)
	fadds f0, f1, f0
	fmuls f1, f28, f0
	bl PSMTXRotAxisRad
	addi r3, r1, 0x104
	addi r4, r1, 0xa4
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0x9c(r20)
	fmr f2, f31
	addi r3, r1, 0xd4
	fmuls f1, f0, f31
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x104
	addi r4, r1, 0xd4
	mr r5, r3
	bl PSMTXConcat
	lfs f0, 0xb8(r20)
	lfs f1, 0xf8(r20)
	fmuls f0, f29, f0
	fmuls f18, f27, f1
	fdivs f1, f0, f30
	bl sin
	lfs f0, 0xb8(r20)
	frsp f17, f1
	fmuls f0, f29, f0
	fdivs f1, f0, f30
	bl cos
	frsp f0, f1
	lfs f2, float_0_8041f1f8(r0)
	fmuls f1, f18, f17
	addi r3, r1, 0xd4
	fmuls f3, f18, f0
	bl PSMTXTrans
	addi r3, r1, 0x104
	addi r4, r1, 0xd4
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0x104
	addi r3, r1, 0x74
	mr r5, r4
	bl PSMTXConcat
	addi r21, r28, 0xe0
	addi r22, r27, 0xe0
	li r17, 0x10
	L_at5:
	mr r3, r22
	mr r4, r21
	li r5, 0xe
	bl memcpy
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
	stfs f0, 0x30(r1)
	psq_l f0, 0x2(r22), 1, 5
	stfs f0, 0x34(r1)
	psq_l f0, 0x4(r22), 1, 5
	addi r4, r1, 0x30
	mr r5, r4
	addi r3, r1, 0x104
	stfs f0, 0x38(r1)
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
	lfs f22, 0x30(r1)
	psq_st f22, 0x10(r1), 1, 5
	lha r0, 0x10(r1)
	sth r0, 0x0(r22)
	lfs f21, 0x34(r1)
	psq_st f21, 0xc(r1), 1, 5
	lha r0, 0xc(r1)
	sth r0, 0x2(r22)
	lfs f20, 0x38(r1)
	psq_st f20, 0x8(r1), 1, 5
	addi r21, r21, 0xe
	addi r17, r17, 0x1
	lha r0, 0x8(r1)
	sth r0, 0x4(r22)
	addi r22, r22, 0xe
	cmpwi r17, 0x20
	blt L_at5
	bl GXInvalidateVtxCache
	mr r3, r27
	li r4, 0x1c0
	bl DCFlushRange
	lfs f1, float_0p015625_8041f1fc(r0)
	addi r3, r1, 0xd4
	lfs f2, float_0p03125_8041f200(r0)
	lfs f3, float_0_8041f1f8(r0)
	bl PSMTXScale
	xoris r0, r19, 0x8000
	lfs f2, float_0_8041f1f8(r0)
	stw r0, 0x15c(r1)
	addi r3, r1, 0x104
	lfs f1, 0x13c(r30)
	fmr f3, f2
	stw r24, 0x158(r1)
	lfd f0, 0x158(r1)
	fsubs f0, f0, f26
	fadds f1, f1, f0
	bl PSMTXTrans
	addi r3, r1, 0xd4
	addi r4, r1, 0x104
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xd4
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	lfs f1, float_0p015625_8041f1fc(r0)
	addi r3, r1, 0xd4
	lfs f2, float_0p03125_8041f200(r0)
	lfs f3, float_0_8041f1f8(r0)
	bl PSMTXScale
	xoris r0, r18, 0x8000
	lfs f2, float_0_8041f1f8(r0)
	stw r0, 0x154(r1)
	addi r3, r1, 0x104
	lfs f1, 0x140(r30)
	fmr f3, f2
	stw r24, 0x150(r1)
	lfd f0, 0x150(r1)
	fsubs f0, f0, f26
	fadds f1, f1, f0
	bl PSMTXTrans
	addi r3, r1, 0xd4
	addi r4, r1, 0x104
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xd4
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	addi r3, r23, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r16, 0x0
	L_at6:
	li r3, 0x90
	li r4, 0x0
	li r5, 0x6
	bl GXBegin
	addi r3, r16, 0x10
	addi r4, r16, 0x1
	mr r5, r16
	addi r9, r16, 0x11
	mr r7, r4
	mr r8, r3
	li r6, 0x0
	li r10, 0x1
	bl tri2
	addi r16, r16, 0x1
	cmpwi r16, 0xf
	blt L_at6
	addi r31, r31, 0x1
	addi r19, r19, 0x4
	cmpwi r31, 0x7
	addi r18, r18, 0x2
	addi r20, r20, 0x4
	blt L_at2
	psq_l f31, 0x298(r1), 0, 0
	lfd f31, 0x290(r1)
	psq_l f30, 0x288(r1), 0, 0
	lfd f30, 0x280(r1)
	psq_l f29, 0x278(r1), 0, 0
	lfd f29, 0x270(r1)
	psq_l f28, 0x268(r1), 0, 0
	lfd f28, 0x260(r1)
	psq_l f27, 0x258(r1), 0, 0
	lfd f27, 0x250(r1)
	psq_l f26, 0x248(r1), 0, 0
	lfd f26, 0x240(r1)
	psq_l f25, 0x238(r1), 0, 0
	lfd f25, 0x230(r1)
	psq_l f24, 0x228(r1), 0, 0
	lfd f24, 0x220(r1)
	psq_l f23, 0x218(r1), 0, 0
	lfd f23, 0x210(r1)
	psq_l f22, 0x208(r1), 0, 0
	lfd f22, 0x200(r1)
	psq_l f21, 0x1f8(r1), 0, 0
	lfd f21, 0x1f0(r1)
	psq_l f20, 0x1e8(r1), 0, 0
	lfd f20, 0x1e0(r1)
	psq_l f19, 0x1d8(r1), 0, 0
	lfd f19, 0x1d0(r1)
	psq_l f18, 0x1c8(r1), 0, 0
	lfd f18, 0x1c0(r1)
	psq_l f17, 0x1b8(r1), 0, 0
	lfd f17, 0x1b0(r1)
	psq_l f16, 0x1a8(r1), 0, 0
	lfd f16, 0x1a0(r1)
	lmw r16, 0x160(r1)
	lwz r0, 0x2a4(r1)
	mtlr r0
	addi r1, r1, 0x2a0
	blr
}

asm void effKamekiTornadeMain(EffectEntry* effect) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r4, vec3_802fa840@ha
	stw r0, 0x34(r1)
	addi r5, r4, vec3_802fa840@l
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
	beq L_at1
	rlwinm r3, r3, 0, 30, 28
	li r0, 0x10
	stw r3, 0x0(r31)
	stw r0, 0x10(r6)
	L_at1:
	lwz r3, 0x10(r6)
	cmpwi r3, 0x3e8
	bge L_at2
	subi r0, r3, 0x1
	stw r0, 0x10(r6)
	L_at2:
	lwz r3, 0x14(r6)
	addi r0, r3, 0x1
	stw r0, 0x14(r6)
	lwz r0, 0x10(r6)
	cmpwi r0, 0x0
	bge L_at3
	mr r3, r31
	bl effDelete
	b L_at4
	L_at3:
	cmpwi r0, 0x10
	lwz r3, 0x14(r6)
	lfs f2, 0x34(r6)
	bge L_at5
	slwi r0, r0, 4
	stw r0, 0x24(r6)
	L_at5:
	cmpwi r3, 0x10
	bge L_at6
	slwi r3, r3, 4
	addi r0, r3, 0xf
	stw r0, 0x24(r6)
	L_at6:
	lfs f1, 0x4(r6)
	li r0, 0x7
	lfs f0, float_5_8041f204(r0)
	addi r3, r6, 0x1c
	stfs f1, 0x38(r6)
	fmuls f5, f0, f2
	lfs f4, float_4_8041f208(r0)
	lfs f0, 0x8(r6)
	lfs f1, float_90_8041f20c(r0)
	stfs f0, 0x58(r6)
	lfs f0, float_neg90_8041f210(r0)
	lfs f2, 0xc(r6)
	stfs f2, 0x78(r6)
	mtctr r0
	L_at7:
	lfs f3, 0x34(r3)
	lfs f2, 0x38(r3)
	fsubs f2, f3, f2
	fmuls f2, f4, f2
	stfs f2, 0x118(r3)
	lfs f2, 0x34(r3)
	stfs f2, 0x38(r3)
	lfs f2, 0x54(r3)
	fadds f2, f2, f5
	stfs f2, 0x58(r3)
	lfs f2, 0x74(r3)
	stfs f2, 0x78(r3)
	lfs f2, 0x118(r3)
	fcmpo cr0, f2, f1
	ble L_at8
	stfs f1, 0x118(r3)
	b L_at9
	L_at8:
	fcmpo cr0, f2, f0
	bge L_at9
	stfs f0, 0x118(r3)
	L_at9:
	subi r3, r3, 0x4
	bdnz L_at7
	lfs f1, 0x138(r6)
	lfs f0, float_10_8041f1f4(r0)
	lfs f2, float_12p96_8041f214(r0)
	fadds f3, f1, f0
	lfs f1, float_17p28_8041f218(r0)
	lfs f0, float_64_8041f21c(r0)
	stfs f3, 0x138(r6)
	lfs f3, 0x13c(r6)
	fadds f2, f3, f2
	stfs f2, 0x13c(r6)
	lfs f2, 0x140(r6)
	fadds f1, f2, f1
	stfs f1, 0x140(r6)
	lfs f1, 0x13c(r6)
	fcmpo cr0, f1, f0
	ble L_at10
	fsubs f0, f1, f0
	stfs f0, 0x13c(r6)
	L_at10:
	lfs f1, 0x140(r6)
	lfs f0, float_64_8041f21c(r0)
	fcmpo cr0, f1, f0
	ble L_at11
	fsubs f0, f1, f0
	stfs f0, 0x140(r6)
	L_at11:
	lfs f1, 0xb8(r6)
	addi r3, r1, 0x14
	lfs f0, 0xd8(r6)
	fadds f0, f1, f0
	stfs f0, 0xb8(r6)
	lfs f1, 0xbc(r6)
	lfs f0, 0xdc(r6)
	fadds f0, f1, f0
	stfs f0, 0xbc(r6)
	lfs f1, 0xc0(r6)
	lfs f0, 0xe0(r6)
	fadds f0, f1, f0
	stfs f0, 0xc0(r6)
	lfs f1, 0xc4(r6)
	lfs f0, 0xe4(r6)
	fadds f0, f1, f0
	stfs f0, 0xc4(r6)
	lfs f1, 0xc8(r6)
	lfs f0, 0xe8(r6)
	fadds f0, f1, f0
	stfs f0, 0xc8(r6)
	lfs f1, 0xcc(r6)
	lfs f0, 0xec(r6)
	fadds f0, f1, f0
	stfs f0, 0xcc(r6)
	lfs f1, 0xd0(r6)
	lfs f0, 0xf0(r6)
	fadds f0, f1, f0
	stfs f0, 0xd0(r6)
	lfs f1, 0xd4(r6)
	lfs f0, 0xf4(r6)
	fadds f0, f1, f0
	stfs f0, 0xd4(r6)
	bl dispCalcZ
	lis r3, effKamekiTornadeDisp@ha
	mr r6, r31
	addi r5, r3, effKamekiTornadeDisp@l
	li r4, 0x2
	li r3, 0x4
	bl dispEntry
	L_at4:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm EffectEntry* effKamekiTornadeN64Entry(s32 type, s32 life, f32 x, f32 y, f32 z, f32 scale) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stfd f31, 0xd0(r1)
	psq_st f31, 0xd8(r1), 0, 0
	stfd f30, 0xc0(r1)
	psq_st f30, 0xc8(r1), 0, 0
	stfd f29, 0xb0(r1)
	psq_st f29, 0xb8(r1), 0, 0
	stfd f28, 0xa0(r1)
	psq_st f28, 0xa8(r1), 0, 0
	stfd f27, 0x90(r1)
	psq_st f27, 0x98(r1), 0, 0
	stfd f26, 0x80(r1)
	psq_st f26, 0x88(r1), 0, 0
	stfd f25, 0x70(r1)
	psq_st f25, 0x78(r1), 0, 0
	stfd f24, 0x60(r1)
	psq_st f24, 0x68(r1), 0, 0
	stfd f23, 0x50(r1)
	psq_st f23, 0x58(r1), 0, 0
	stmw r24, 0x30(r1)
	fmr f27, f1
	mr r25, r3
	fmr f28, f2
	mr r24, r4
	fmr f29, f3
	fmr f23, f4
	bl effEntry
	lis r4, str_802FA870@ha
	mr r27, r3
	addi r4, r4, str_802FA870@l
	li r0, 0x1
	stw r4, 0x14(r27)
	li r3, 0x3
	li r4, 0x14c
	stw r0, 0x8(r27)
	bl __memAlloc
	mr r26, r3
	lis r4, effKamekiTornadeMain@ha
	stw r26, 0xc(r27)
	addi r3, r4, effKamekiTornadeMain@l
	cmpwi r24, 0x0
	li r0, 0x0
	stw r3, 0x10(r27)
	lwz r3, 0x0(r27)
	ori r3, r3, 0x2
	stw r3, 0x0(r27)
	stw r25, 0x0(r26)
	stw r0, 0x14(r26)
	bgt L_at1
	li r0, 0x3e8
	stw r0, 0x10(r26)
	b L_at2
	L_at1:
	stw r24, 0x10(r26)
	L_at2:
	li r0, 0x0
	lis r3, double_to_int_802fa868@ha
	stw r0, 0x24(r26)
	addi r6, r3, double_to_int_802fa868@l
	lis r5, 0xb60b
	lis r4, 0x51ec
	stfs f27, 0x4(r26)
	lis r3, 0x8889
	li r7, 0xff
	li r0, 0xeb
	stfs f28, 0x8(r26)
	mr r28, r26
	lfs f30, float_0p2_8041f224(r0)
	addi r30, r5, 0x60b7
	stfs f29, 0xc(r26)
	subi r31, r4, 0x7ae1
	lfd f31, 0x0(r6)
	subi r24, r3, 0x7777
	stfs f23, 0x34(r26)
	li r25, 0x0
	lfs f23, float_1_8041f220(r0)
	lis r29, 0x4330
	stw r7, 0x18(r26)
	lfs f24, float_0p1_8041f1ec(r0)
	stw r7, 0x1c(r26)
	lfs f25, float_2_8041f228(r0)
	stw r7, 0x20(r26)
	lfs f26, float_0_8041f1f8(r0)
	stw r7, 0x28(r26)
	stw r7, 0x2c(r26)
	stw r0, 0x30(r26)
	L_at3:
	xoris r0, r25, 0x8000
	stfs f27, 0x38(r28)
	stw r0, 0xc(r1)
	stw r29, 0x8(r1)
	lfd f0, 0x8(r1)
	stfs f28, 0x58(r28)
	fsubs f0, f0, f31
	stfs f29, 0x78(r28)
	fmadds f0, f30, f0, f23
	stfs f0, 0x98(r28)
	bl rand
	mulhw r0, r30, r3
	stw r29, 0x10(r1)
	add r0, r0, r3
	srawi r0, r0, 8
	srwi r4, r0, 31
	add r0, r0, r4
	mulli r0, r0, 0x168
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f31
	stfs f0, 0xb8(r28)
	bl rand
	mulhw r0, r31, r3
	stw r29, 0x18(r1)
	srawi r0, r0, 5
	srwi r4, r0, 31
	add r0, r0, r4
	mulli r0, r0, 0x64
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0x1c(r1)
	lfd f0, 0x18(r1)
	fsubs f0, f0, f31
	fmadds f0, f24, f0, f25
	stfs f0, 0xd8(r28)
	bl rand
	mulhw r0, r24, r3
	addi r25, r25, 0x1
	stw r29, 0x20(r1)
	cmpwi r25, 0x8
	add r0, r0, r3
	srawi r0, r0, 4
	srwi r4, r0, 31
	add r0, r0, r4
	mulli r0, r0, 0x1e
	subf r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0x24(r1)
	lfd f0, 0x20(r1)
	fsubs f0, f0, f31
	fmuls f0, f24, f0
	stfs f0, 0xf8(r28)
	stfs f26, 0x118(r28)
	addi r28, r28, 0x4
	blt L_at3
	lfs f1, float_0_8041f1f8(r0)
	mr r3, r27
	lfs f0, float_1_8041f220(r0)
	stfs f1, 0x138(r26)
	stfs f1, 0x144(r26)
	stfs f1, 0x13c(r26)
	stfs f1, 0x140(r26)
	stfs f0, 0x148(r26)
	psq_l f31, 0xd8(r1), 0, 0
	lfd f31, 0xd0(r1)
	psq_l f30, 0xc8(r1), 0, 0
	lfd f30, 0xc0(r1)
	psq_l f29, 0xb8(r1), 0, 0
	lfd f29, 0xb0(r1)
	psq_l f28, 0xa8(r1), 0, 0
	lfd f28, 0xa0(r1)
	psq_l f27, 0x98(r1), 0, 0
	lfd f27, 0x90(r1)
	psq_l f26, 0x88(r1), 0, 0
	lfd f26, 0x80(r1)
	psq_l f25, 0x78(r1), 0, 0
	lfd f25, 0x70(r1)
	psq_l f24, 0x68(r1), 0, 0
	lfd f24, 0x60(r1)
	psq_l f23, 0x58(r1), 0, 0
	lfd f23, 0x50(r1)
	lmw r24, 0x30(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}
// clang-format on
#endif
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".sdata2") const u32 gap_09_8041F22C_sdata2[1] = {0};
#pragma explicit_zero_data reset
