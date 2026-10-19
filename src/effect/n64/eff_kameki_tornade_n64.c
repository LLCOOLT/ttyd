#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSFastCast.h>
#include <stdlib.h>
#include <string.h>
__declspec(section ".sdata2") u32 gap_10_80423164_sbss2[1];
__declspec(section ".sdata2") u32 unk_80423160;
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802fa840[3];
__declspec(section ".rodata") extern const f32 vec3_802fa84c[3];
__declspec(section ".rodata") extern const f32 vec3_802fa858[3];
__declspec(section ".rodata") extern const f64 double_to_int_802fa868;
__declspec(section ".rodata") extern const char str_802FA870[20];
__declspec(section ".rodata") extern const u32 gap_04_802FA884_rodata;
__declspec(section ".sdata2") extern const u32 dat_8041f1d8;
__declspec(section ".sdata2") extern const f32 float_6p2832_8041f1dc;
__declspec(section ".sdata2") extern const f32 float_360_8041f1e0;
__declspec(section ".sdata2") extern const f32 float_100_8041f1e4;
__declspec(section ".sdata2") extern const f32 float_deg2rad_8041f1e8;
__declspec(section ".sdata2") extern const f32 float_0p1_8041f1ec;
__declspec(section ".sdata2") extern const f32 float_0p02_8041f1f0;
__declspec(section ".sdata2") extern const f32 float_10_8041f1f4;
__declspec(section ".sdata2") extern const f32 float_0_8041f1f8;
__declspec(section ".sdata2") extern const f32 float_0p015625_8041f1fc;
__declspec(section ".sdata2") extern const f32 float_0p03125_8041f200;
__declspec(section ".sdata2") extern const f32 float_5_8041f204;
__declspec(section ".sdata2") extern const f32 float_4_8041f208;
__declspec(section ".sdata2") extern const f32 float_90_8041f20c;
__declspec(section ".sdata2") extern const f32 float_neg90_8041f210;
__declspec(section ".sdata2") extern const f32 float_12p96_8041f214;
__declspec(section ".sdata2") extern const f32 float_17p28_8041f218;
__declspec(section ".sdata2") extern const f32 float_64_8041f21c;
__declspec(section ".sdata2") extern const f32 float_1_8041f220;
__declspec(section ".sdata2") extern const f32 float_0p2_8041f224;
__declspec(section ".sdata2") extern const f32 float_2_8041f228;
#endif

double sin(double);
double cos(double);

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

static inline void OSf32tos16(f32* f, s16* out) {
    *out = __OSf32tos16(*f);
}

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

void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXInvalidateVtxCache(void);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetNumChans(u8 nChans);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void *memcpy(void *dest, const void *src, size_t num);
int rand(void);
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
        work->sc[i] = EXT_LIT(float_0p2_8041f224, 0.2f) * (f32)i + EXT_LIT(float_1_8041f220, 1.0f);
        work->ang[i] = (f32)(rand() % 360);
        work->angVel[i] = EXT_LIT(float_0p1_8041f1ec, 0.1f) * (f32)(rand() % 100) + EXT_LIT(float_2_8041f228, 2.0f);
        work->radius[i] = EXT_LIT(float_0p1_8041f1ec, 0.1f) * (f32)(rand() % 30);
        work->rot[i] = EXT_LIT(float_0_8041f1f8, 0.0f);
    }
    work->twist = EXT_LIT(float_0_8041f1f8, 0.0f);
    work->unk144 = EXT_LIT(float_0_8041f1f8, 0.0f);
    work->scrollS = EXT_LIT(float_0_8041f1f8, 0.0f);
    work->scrollT = EXT_LIT(float_0_8041f1f8, 0.0f);
    work->unk148 = EXT_LIT(float_1_8041f220, 1.0f);
    return effect;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
EffectEntry* effKamekiTornadeN64Entry(s32 type, s32 life, f32 x, f32 y, f32 z, f32 scale) {
	char _af_pad[32];
	asm volatile {
		opword 0xFF600890
		opword 0x7C791B78
		opword 0xFF801090
		opword 0x7C982378
		opword 0xFFA01890
		opword 0xFEE02090
		bl effEntry
		lis r4, str_802FA870@ha
		opword 0x7C7B1B78
		addi r4, r4, str_802FA870@l
		opword 0x38000001
		opword 0x909B0014
		opword 0x38600003
		opword 0x3880014C
		opword 0x901B0008
		bl __memAlloc
		opword 0x7C7A1B78
		lis r4, effKamekiTornadeMain@ha
		opword 0x935B000C
		addi r3, r4, effKamekiTornadeMain@l
		opword 0x2C180000
		opword 0x38000000
		opword 0x907B0010
		opword 0x807B0000
		opword 0x60630002
		opword 0x907B0000
		opword 0x933A0000
		opword 0x901A0014
		opword 0x41810010
		opword 0x380003E8
		opword 0x901A0010
		opword 0x48000008
		opword 0x931A0010
		opword 0x38000000
		lis r3, double_to_int_802fa868@ha
		opword 0x901A0024
		addi r6, r3, double_to_int_802fa868@l
		opword 0x3CA0B60B
		opword 0x3C8051EC
		opword 0xD37A0004
		opword 0x3C608889
		opword 0x38E000FF
		opword 0x380000EB
		opword 0xD39A0008
		opword 0x7F5CD378
		lfs f30, float_0p2_8041f224(r2)
		opword 0x3BC560B7
		opword 0xD3BA000C
		opword 0x3BE4851F
		opword 0xCBE60000
		subi r24, r3, 0x7777
		opword 0xD2FA0034
		opword 0x3B200000
		lfs f23, float_1_8041f220(r2)
		opword 0x3FA04330
		opword 0x90FA0018
		lfs f24, float_0p1_8041f1ec(r2)
		opword 0x90FA001C
		lfs f25, float_2_8041f228(r2)
		opword 0x90FA0020
		lfs f26, float_0_8041f1f8(r2)
		opword 0x90FA0028
		opword 0x90FA002C
		opword 0x901A0030
		opword 0x6F208000
		opword 0xD37C0038
		stw r0, _af_pad+4(r1)
		opword 0x93A10008
		opword 0xC8010008
		opword 0xD39C0058
		opword 0xEC00F828
		opword 0xD3BC0078
		opword 0xEC1EB83A
		opword 0xD01C0098
		bl rand
		opword 0x7C1E1896
		opword 0x93A10010
		opword 0x7C001A14
		opword 0x7C004670
		opword 0x54040FFE
		opword 0x7C002214
		opword 0x1C000168
		opword 0x7C001850
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8010010
		opword 0xEC00F828
		opword 0xD01C00B8
		bl rand
		opword 0x7C1F1896
		opword 0x93A10018
		opword 0x7C002E70
		opword 0x54040FFE
		opword 0x7C002214
		opword 0x1C000064
		opword 0x7C001850
		opword 0x6C008000
		opword 0x9001001C
		opword 0xC8010018
		opword 0xEC00F828
		opword 0xEC18C83A
		opword 0xD01C00D8
		bl rand
		opword 0x7C181896
		opword 0x3B390001
		opword 0x93A10020
		opword 0x2C190008
		opword 0x7C001A14
		opword 0x7C002670
		opword 0x54040FFE
		opword 0x7C002214
		opword 0x1C00001E
		opword 0x7C001850
		opword 0x6C008000
		opword 0x90010024
		opword 0xC8010020
		opword 0xEC00F828
		opword 0xEC180032
		opword 0xD01C00F8
		opword 0xD35C0118
		opword 0x3B9C0004
		opword 0x4180FF1C
		lfs f1, float_0_8041f1f8(r2)
		opword 0x7F63DB78
		lfs f0, float_1_8041f220(r2)
		opword 0xD03A0138
		opword 0xD03A0144
		opword 0xD03A013C
		opword 0xD03A0140
		opword 0xD01A0148
	}
}
#pragma pop
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
        work->py[i] = work->py[i - 1] + EXT_LIT(float_5_8041f204, 5.0f) * scale;
        work->pz[i] = work->pz[i - 1];
        if (work->rot[i] > EXT_LIT(float_90_8041f20c, 90.0f)) {
            work->rot[i] = 90.0f;
        } else if (work->rot[i] < EXT_LIT(float_neg90_8041f210, -90.0f)) {
            work->rot[i] = -90.0f;
        }
    }
    work->twist += EXT_LIT(float_10_8041f1f4, 10.0f);
    work->scrollS += EXT_LIT(float_12p96_8041f214, 12.959999f);
    work->scrollT += EXT_LIT(float_17p28_8041f218, 17.28f);
    if (work->scrollS > EXT_LIT(float_64_8041f21c, 64.0f)) {
        work->scrollS -= 64.0f;
    }
    if (work->scrollT > EXT_LIT(float_64_8041f21c, 64.0f)) {
        work->scrollT -= 64.0f;
    }
    for (i = 0; i < 8; i++) {
        work->ang[i] += work->angVel[i];
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effKamekiTornadeDisp, effect);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void effKamekiTornadeMain(EffectEntry* effect) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		lis r4, vec3_802fa840@ha
		opword 0x90010034
		addi r5, r4, vec3_802fa840@l
		opword 0x93E1002C
		opword 0x7C7F1B78
		opword 0x80C3000C
		opword 0x80850000
		opword 0x80650004
		opword 0x80050008
		opword 0x90810008
		opword 0xC0060004
		opword 0x9061000C
		opword 0xC0260008
		opword 0xD0010008
		opword 0xC006000C
		opword 0x90010010
		opword 0x80810008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x8061000C
		opword 0x80010010
		opword 0x90810014
		opword 0x90610018
		opword 0x9001001C
		opword 0x807F0000
		opword 0x5460077B
		opword 0x41820014
		opword 0x546307B8
		opword 0x38000010
		opword 0x907F0000
		opword 0x90060010
		opword 0x80660010
		opword 0x2C0303E8
		opword 0x4080000C
		opword 0x3803FFFF
		opword 0x90060010
		opword 0x80660014
		opword 0x38030001
		opword 0x90060014
		opword 0x80060010
		opword 0x2C000000
		opword 0x40800010
		opword 0x7FE3FB78
		bl effDelete
		opword 0x480001C0
		opword 0x2C000010
		opword 0x80660014
		opword 0xC0460034
		opword 0x4080000C
		opword 0x54002036
		opword 0x90060024
		opword 0x2C030010
		opword 0x40800010
		opword 0x54632036
		opword 0x3803000F
		opword 0x90060024
		opword 0xC0260004
		opword 0x38000007
		lfs f0, float_5_8041f204(r2)
		opword 0x3866001C
		opword 0xD0260038
		opword 0xECA000B2
		lfs f4, float_4_8041f208(r2)
		opword 0xC0060008
		lfs f1, float_90_8041f20c(r2)
		opword 0xD0060058
		lfs f0, float_neg90_8041f210(r2)
		opword 0xC046000C
		opword 0xD0460078
		opword 0x7C0903A6
		opword 0xC0630034
		opword 0xC0430038
		opword 0xEC431028
		opword 0xEC4400B2
		opword 0xD0430118
		opword 0xC0430034
		opword 0xD0430038
		opword 0xC0430054
		opword 0xEC42282A
		opword 0xD0430058
		opword 0xC0430074
		opword 0xD0430078
		opword 0xC0430118
		opword 0xFC020840
		opword 0x4081000C
		opword 0xD0230118
		opword 0x48000010
		opword 0xFC020040
		opword 0x40800008
		opword 0xD0030118
		opword 0x3863FFFC
		opword 0x4200FFAC
		opword 0xC0260138
		lfs f0, float_10_8041f1f4(r2)
		lfs f2, float_12p96_8041f214(r2)
		opword 0xEC61002A
		lfs f1, float_17p28_8041f218(r2)
		lfs f0, float_64_8041f21c(r2)
		opword 0xD0660138
		opword 0xC066013C
		opword 0xEC43102A
		opword 0xD046013C
		opword 0xC0460140
		opword 0xEC22082A
		opword 0xD0260140
		opword 0xC026013C
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC010028
		opword 0xD006013C
		opword 0xC0260140
		lfs f0, float_64_8041f21c(r2)
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC010028
		opword 0xD0060140
		opword 0xC02600B8
		opword 0x38610014
		opword 0xC00600D8
		opword 0xEC01002A
		opword 0xD00600B8
		opword 0xC02600BC
		opword 0xC00600DC
		opword 0xEC01002A
		opword 0xD00600BC
		opword 0xC02600C0
		opword 0xC00600E0
		opword 0xEC01002A
		opword 0xD00600C0
		opword 0xC02600C4
		opword 0xC00600E4
		opword 0xEC01002A
		opword 0xD00600C4
		opword 0xC02600C8
		opword 0xC00600E8
		opword 0xEC01002A
		opword 0xD00600C8
		opword 0xC02600CC
		opword 0xC00600EC
		opword 0xEC01002A
		opword 0xD00600CC
		opword 0xC02600D0
		opword 0xC00600F0
		opword 0xEC01002A
		opword 0xD00600D0
		opword 0xC02600D4
		opword 0xC00600F4
		opword 0xEC01002A
		opword 0xD00600D4
		bl dispCalcZ
		lis r3, effKamekiTornadeDisp@ha
		opword 0x7FE6FB78
		addi r5, r3, effKamekiTornadeDisp@l
		opword 0x38800002
		opword 0x38600004
		bl dispEntry
		opword 0x80010034
		opword 0x83E1002C
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
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
        r = (EXT_LIT(float_6p2832_8041f1dc, 6.2831855f) * (f32)(i * 360 / 15)) / EXT_LIT(float_360_8041f1e0, 360.0f);
        p->x = EXT_LIT(float_100_8041f1e4, 100.0f) * (f32)cos(r);
        p->y = EXT_LIT(float_0_8041f1f8, 0.0f);
        p->z = EXT_LIT(float_100_8041f1e4, 100.0f) * (f32)sin(r);
        p->s = k;
        p->t = 0;
        q = &tmpl[i + 16];
        q->x = EXT_LIT(float_100_8041f1e4, 100.0f) * (f32)cos(r);
        q->y = EXT_LIT(float_0_8041f1f8, 0.0f);
        q->z = EXT_LIT(float_100_8041f1e4, 100.0f) * (f32)sin(r);
        q->s = i * 512;
        q->t = 1024;
    }
    PSMTXRotRad(rot, 'z', EXT_LIT(float_deg2rad_8041f1e8, 0.017453292f) * work->unk144);
    PSMTXScale(base, EXT_LIT(float_0p1_8041f1ec, 0.1f), EXT_LIT(float_0p1_8041f1ec, 0.1f), EXT_LIT(float_0p1_8041f1ec, 0.1f));
    PSMTXConcat(rot, base, base);
    for (i = 0; i < 7; i++) {
        vtx = (effN64Vtx*)smartAlloc(sizeof(effN64Vtx) * 32, 3)->address;
        effSetVtxDescN64(vtx);
        PSMTXTrans(mtx, EXT_LIT(float_10_8041f1f4, 10.0f) * work->px[i], EXT_LIT(float_10_8041f1f4, 10.0f) * work->py[i], EXT_LIT(float_10_8041f1f4, 10.0f) * work->pz[i]);
        PSMTXRotRad(rot, 'z', EXT_LIT(float_deg2rad_8041f1e8, 0.017453292f) * work->rot[i]);
        PSMTXConcat(mtx, rot, mtx);
        axis = (Vec){-0.03f, EXT_LIT(float_1_8041f220, 1.0f), EXT_LIT(float_0p1_8041f1ec, 0.1f)};
        PSMTXRotAxisRad(rot, &axis, EXT_LIT(float_deg2rad_8041f1e8, 0.017453292f) * (work->twist + (f32)(i * i)));
        PSMTXConcat(mtx, rot, mtx);
        s = work->sc[i] * scale;
        if (life < 16) {
            s += 0.02f * (f32)(127 - a);
        }
        PSMTXScale(tex, s, scale, s);
        PSMTXConcat(mtx, tex, mtx);
        ang = EXT_LIT(float_10_8041f1f4, 10.0f) * work->radius[i];
        s = EXT_LIT(float_6p2832_8041f1dc, 6.2831855f) * work->ang[i] / EXT_LIT(float_360_8041f1e0, 360.0f);
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
        PSMTXTrans(mtx, EXT_LIT(float_10_8041f1f4, 10.0f) * work->px[i + 1], EXT_LIT(float_10_8041f1f4, 10.0f) * work->py[i + 1], EXT_LIT(float_10_8041f1f4, 10.0f) * work->pz[i + 1]);
        PSMTXRotRad(rot, 'z', EXT_LIT(float_deg2rad_8041f1e8, 0.017453292f) * work->rot[i + 1]);
        PSMTXConcat(mtx, rot, mtx);
        axis = (Vec){0.03f, EXT_LIT(float_1_8041f220, 1.0f), EXT_LIT(float_0_8041f1f8, 0.0f)};
        PSMTXRotAxisRad(rot, &axis, EXT_LIT(float_deg2rad_8041f1e8, 0.017453292f) * (work->twist + (f32)(i * i)));
        PSMTXConcat(mtx, rot, mtx);
        PSMTXScale(tex, work->sc[i + 1] * scale, scale, work->sc[i + 1] * scale);
        PSMTXConcat(mtx, tex, mtx);
        r = EXT_LIT(float_10_8041f1f4, 10.0f) * work->radius[i];
        s = (f32)sin(EXT_LIT(float_6p2832_8041f1dc, 6.2831855f) * work->ang[i] / EXT_LIT(float_360_8041f1e0, 360.0f));
        PSMTXTrans(tex, r * s, EXT_LIT(float_0_8041f1f8, 0.0f), r * (f32)cos(EXT_LIT(float_6p2832_8041f1dc, 6.2831855f) * work->ang[i] / EXT_LIT(float_360_8041f1e0, 360.0f)));
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
        PSMTXScale(tex, EXT_LIT(float_0p015625_8041f1fc, 0.015625f), EXT_LIT(float_0p03125_8041f200, 0.03125f), EXT_LIT(float_0_8041f1f8, 0.0f));
        PSMTXTrans(mtx, work->scrollS + (f32)(i * 4), EXT_LIT(float_0_8041f1f8, 0.0f), EXT_LIT(float_0_8041f1f8, 0.0f));
        PSMTXConcat(tex, mtx, tex);
        GXLoadTexMtxImm(tex, GX_TEXMTX0, GX_MTX2x4);
        PSMTXScale(tex, EXT_LIT(float_0p015625_8041f1fc, 0.015625f), EXT_LIT(float_0p03125_8041f200, 0.03125f), EXT_LIT(float_0_8041f1f8, 0.0f));
        PSMTXTrans(mtx, work->scrollT + (f32)(i * 2), EXT_LIT(float_0_8041f1f8, 0.0f), EXT_LIT(float_0_8041f1f8, 0.0f));
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void effKamekiTornadeDisp(CameraId cameraId, EffectEntry* effect) {
	char _af_pad[336];
	asm volatile {
		opword 0x7C902378
		bl camGetPtr
		opword 0x83D0000C
		opword 0x7C771B78
		opword 0x38600000
		opword 0x801E0024
		opword 0x83BE0010
		opword 0xC3FE0034
		srawi r16, r0, 1
		bl GXSetNumChans
		opword 0x38600003
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00008
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00007
		opword 0x38C00007
		opword 0x38E00004
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00001
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600001
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600001
		opword 0x38800008
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C000FF
		bl GXSetTevOrder
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600002
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600002
		opword 0x38800002
		opword 0x38A00004
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600002
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600002
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		opword 0x38600001
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C00021
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		la r4, _af_pad+76
		opword 0x3860006C
		bl effGetTexObjN64
		opword 0x38610054
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x38610054
		opword 0x38800001
		bl GXLoadTexObj
		opword 0x6E048000
		opword 0x3C004330
		opword 0x9081013C
		lis r5, double_to_int_802fa868@ha
		lfd f2, double_to_int_802fa868@l(r5)
		opword 0x3881002C
		opword 0x90010138
		opword 0x38600001
		lwz r7, unk_80423160(r2)
		opword 0xC8210138
		opword 0xC01E0148
		opword 0xEC211028
		opword 0x90E10028
		opword 0x801E001C
		opword 0x80DE0018
		opword 0xEC010032
		opword 0x80BE0020
		opword 0x98010029
		opword 0xFC00001E
		opword 0x98C10028
		opword 0x98A1002A
		opword 0xD8010140
		opword 0x80010144
		opword 0x9801002B
		opword 0x80010028
		opword 0x9001002C
		bl GXSetTevColor
		lwz r0, dat_8041f1d8(r2)
		opword 0x38810024
		opword 0x80DE0028
		opword 0x38600002
		opword 0x90010020
		opword 0x80BE002C
		opword 0x801E0030
		opword 0x98C10020
		opword 0x98A10021
		opword 0x98010022
		opword 0x80010020
		opword 0x90010024
		bl GXSetTevColor
		opword 0x38600000
		bl GXSetCullMode
		opword 0x386001C0
		opword 0x38800003
		bl smartAlloc
		lis r4, double_to_int_802fa868@ha
		opword 0x83830000
		opword 0x3B600000
		opword 0x3CA08889
		lfs f29, float_6p2832_8041f1dc(r2)
		opword 0x7F9AE378
		lfd f28, double_to_int_802fa868@l(r4)
		opword 0x7F74DB78
		lfs f27, float_360_8041f1e0(r2)
		opword 0x3B258889
		lfs f26, float_100_8041f1e4(r2)
		opword 0x3A200000
		opword 0x3A600000
		opword 0x3F004330
		opword 0x7C19D896
		opword 0x93010140
		opword 0x7C00DA14
		opword 0x7C001E70
		opword 0x54040FFE
		opword 0x7C002214
		opword 0x6C008000
		opword 0x90010144
		opword 0xC8010140
		opword 0xEC00E028
		opword 0xEC1D0032
		opword 0xEE60D824
		opword 0xFC209890
		bl cos
		opword 0xFC000818
		opword 0x38000000
		opword 0xFC209890
		opword 0xEC1A0032
		opword 0xFC00001E
		opword 0xD8010138
		opword 0x8081013C
		opword 0xB09A0000
		opword 0xB01A0002
		bl sin
		opword 0xFC000818
		opword 0x38110010
		opword 0x1C00000E
		opword 0xFC209890
		opword 0x38800000
		opword 0xEC1A0032
		opword 0x7E5C0214
		opword 0xFC00001E
		opword 0xD8010148
		opword 0x8001014C
		opword 0xB01A0004
		opword 0xB27A0006
		opword 0xB09A0008
		bl cos
		opword 0xFC000818
		opword 0x38000000
		opword 0xFC209890
		opword 0xEC1A0032
		opword 0xFC00001E
		opword 0xD8010150
		opword 0x80810154
		opword 0xB0920000
		opword 0xB0120002
		bl sin
		opword 0xFC000818
		opword 0x3A310001
		opword 0x2C110010
		opword 0x38000400
		opword 0x3B5A000E
		opword 0x3B7B0168
		opword 0xEC1A0032
		opword 0x3A730080
		opword 0xFC00001E
		opword 0xD8010158
		opword 0x8081015C
		opword 0xB0920004
		opword 0xB2920006
		opword 0x3A940200
		opword 0xB0120008
		opword 0x4180FF04
		lfs f1, float_deg2rad_8041f1e8(r2)
		opword 0x386100A4
		opword 0xC01E0144
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_0p1_8041f1ec(r2)
		opword 0x38610074
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38810074
		opword 0x386100A4
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x2010007F
		opword 0x3BE00000
		opword 0x6C008000
		opword 0x3F004330
		lis r4, double_to_int_802fa868@ha
		opword 0x9001015C
		addi r6, r4, double_to_int_802fa868@l
		lis r5, vec3_802fa84c@ha
		opword 0x93010158
		lis r4, vec3_802fa858@ha
		opword 0xCB460000
		opword 0x7FD4F378
		opword 0xC8010158
		opword 0x7FF3FB78
		lfs f1, float_0p02_8041f1f0(r2)
		opword 0x7FF2FB78
		opword 0xEC00D028
		lfs f27, float_10_8041f1f4(r2)
		lfs f28, float_deg2rad_8041f1e8(r2)
		addi r25, r5, vec3_802fa84c@l
		lfs f29, float_6p2832_8041f1dc(r2)
		addi r26, r4, vec3_802fa858@l
		opword 0xEE610032
		lfs f30, float_360_8041f1e0(r2)
		opword 0x386001C0
		opword 0x38800003
		bl smartAlloc
		opword 0x83630000
		opword 0x7F63DB78
		bl effSetVtxDescN64
		opword 0xC0340038
		opword 0x38610104
		opword 0xC0540058
		opword 0xC0140078
		opword 0xEC3B0072
		opword 0xEC5B00B2
		opword 0xEC7B0032
		bl PSMTXTrans
		opword 0xC0140118
		opword 0x386100A4
		opword 0x3880007A
		opword 0xEC3C0032
		bl PSMTXRotRad
		opword 0x38610104
		opword 0x388100A4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x7E3FF9D6
		opword 0x80F90000
		opword 0x80D90004
		opword 0x386100A4
		opword 0x80B90008
		opword 0x38810048
		opword 0x6E208000
		opword 0x93010158
		opword 0x9001015C
		opword 0xC8010158
		opword 0x90E10048
		opword 0xEC00D028
		opword 0x90C1004C
		opword 0x90A10050
		opword 0xC03E0138
		opword 0xEC01002A
		opword 0xEC3C0032
		bl PSMTXRotAxisRad
		opword 0x38610104
		opword 0x388100A4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC0140098
		opword 0x2C1D0010
		opword 0xEC2007F2
		opword 0x40800008
		opword 0xEC21982A
		opword 0xFC40F890
		opword 0x386100D4
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38610104
		opword 0x388100D4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC01400B8
		opword 0xC03400F8
		opword 0xEC1D0032
		fmuls f16, f27, f1
		opword 0xEE20F024
		opword 0xFC208890
		bl sin
		opword 0xFE400818
		opword 0xFC208890
		bl cos
		opword 0xFC000818
		lfs f2, float_0_8041f1f8(r2)
		opword 0xEC3004B2
		opword 0x386100D4
		opword 0xEC700032
		bl PSMTXTrans
		opword 0x38610104
		opword 0x388100D4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38810104
		opword 0x38610074
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x7F96E378
		opword 0x7F75DB78
		opword 0x3A000000
		opword 0x7EA3AB78
		opword 0x7EC4B378
		opword 0x38A0000E
		bl memcpy
		opword 0x38600004
		opword 0x64630004
		opword 0x7C72E3A6
		opword 0x38600005
		opword 0x64630005
		opword 0x7C73E3A6
		opword 0x38600006
		opword 0x64630006
		opword 0x7C74E3A6
		opword 0x38600007
		opword 0x64630007
		opword 0x7C75E3A6
		opword 0xE015D000
		opword 0xD001003C
		opword 0xE015D002
		opword 0xD0010040
		opword 0xE015D004
		opword 0x3881003C
		opword 0x7C852378
		opword 0x38610104
		opword 0xD0010044
		bl PSMTXMultVec
		opword 0x38600004
		opword 0x64630004
		opword 0x7C72E3A6
		opword 0x38600005
		opword 0x64630005
		opword 0x7C73E3A6
		opword 0x38600006
		opword 0x64630006
		opword 0x7C74E3A6
		opword 0x38600007
		opword 0x64630007
		opword 0x7C75E3A6
		opword 0xC321003C
		opword 0xF321D01C
		opword 0xA801001C
		opword 0xB0150000
		opword 0xC3010040
		opword 0xF301D018
		opword 0xA8010018
		opword 0xB0150002
		opword 0xC2E10044
		opword 0xF2E1D014
		opword 0x3AD6000E
		opword 0x3A100001
		opword 0xA8010014
		opword 0xB0150004
		opword 0x3AB5000E
		opword 0x2C100010
		opword 0x4180FF28
		opword 0xC034003C
		opword 0x38610104
		opword 0xC054005C
		opword 0xC014007C
		opword 0xEC3B0072
		opword 0xEC5B00B2
		opword 0xEC7B0032
		bl PSMTXTrans
		opword 0xC014011C
		opword 0x386100A4
		opword 0x3880007A
		opword 0xEC3C0032
		bl PSMTXRotRad
		opword 0x38610104
		opword 0x388100A4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x6E208000
		opword 0x80DA0000
		opword 0x9001015C
		opword 0x386100A4
		opword 0x80BA0004
		opword 0x38810048
		opword 0x93010158
		opword 0x801A0008
		opword 0xC8010158
		opword 0x90C10048
		opword 0xEC00D028
		opword 0x90A1004C
		opword 0x90010050
		opword 0xC03E0138
		opword 0xEC01002A
		opword 0xEC3C0032
		bl PSMTXRotAxisRad
		opword 0x38610104
		opword 0x388100A4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC014009C
		opword 0xFC40F890
		opword 0x386100D4
		opword 0xEC2007F2
		opword 0xFC600890
		bl PSMTXScale
		opword 0x38610104
		opword 0x388100D4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xC01400B8
		opword 0xC03400F8
		opword 0xEC1D0032
		opword 0xEE5B0072
		opword 0xEC20F024
		bl sin
		opword 0xC01400B8
		opword 0xFE200818
		opword 0xEC1D0032
		opword 0xEC20F024
		bl cos
		opword 0xFC000818
		lfs f2, float_0_8041f1f8(r2)
		opword 0xEC320472
		opword 0x386100D4
		opword 0xEC720032
		bl PSMTXTrans
		opword 0x38610104
		opword 0x388100D4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38810104
		opword 0x38610074
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x3ABC00E0
		opword 0x3ADB00E0
		opword 0x3A200010
		opword 0x7EC3B378
		opword 0x7EA4AB78
		opword 0x38A0000E
		bl memcpy
		opword 0x38600004
		opword 0x64630004
		opword 0x7C72E3A6
		opword 0x38600005
		opword 0x64630005
		opword 0x7C73E3A6
		opword 0x38600006
		opword 0x64630006
		opword 0x7C74E3A6
		opword 0x38600007
		opword 0x64630007
		opword 0x7C75E3A6
		opword 0xE016D000
		opword 0xD0010030
		opword 0xE016D002
		opword 0xD0010034
		opword 0xE016D004
		opword 0x38810030
		opword 0x7C852378
		opword 0x38610104
		opword 0xD0010038
		bl PSMTXMultVec
		opword 0x38600004
		opword 0x64630004
		opword 0x7C72E3A6
		opword 0x38600005
		opword 0x64630005
		opword 0x7C73E3A6
		opword 0x38600006
		opword 0x64630006
		opword 0x7C74E3A6
		opword 0x38600007
		opword 0x64630007
		opword 0x7C75E3A6
		opword 0xC2C10030
		opword 0xF2C1D010
		opword 0xA8010010
		opword 0xB0160000
		opword 0xC2A10034
		opword 0xF2A1D00C
		opword 0xA801000C
		opword 0xB0160002
		opword 0xC2810038
		opword 0xF281D008
		opword 0x3AB5000E
		opword 0x3A310001
		opword 0xA8010008
		opword 0xB0160004
		opword 0x3AD6000E
		opword 0x2C110020
		opword 0x4180FF28
		bl GXInvalidateVtxCache
		opword 0x7F63DB78
		opword 0x388001C0
		bl DCFlushRange
		lfs f1, float_0p015625_8041f1fc(r2)
		opword 0x386100D4
		lfs f2, float_0p03125_8041f200(r2)
		lfs f3, float_0_8041f1f8(r2)
		bl PSMTXScale
		opword 0x6E608000
		lfs f2, float_0_8041f1f8(r2)
		opword 0x9001015C
		opword 0x38610104
		opword 0xC03E013C
		opword 0xFC601090
		opword 0x93010158
		opword 0xC8010158
		opword 0xEC00D028
		opword 0xEC21002A
		bl PSMTXTrans
		opword 0x386100D4
		opword 0x38810104
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100D4
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		lfs f1, float_0p015625_8041f1fc(r2)
		opword 0x386100D4
		lfs f2, float_0p03125_8041f200(r2)
		lfs f3, float_0_8041f1f8(r2)
		bl PSMTXScale
		opword 0x6E408000
		lfs f2, float_0_8041f1f8(r2)
		opword 0x90010154
		opword 0x38610104
		opword 0xC03E0140
		opword 0xFC601090
		opword 0x93010150
		opword 0xC8010150
		opword 0xEC00D028
		opword 0xEC21002A
		bl PSMTXTrans
		opword 0x386100D4
		opword 0x38810104
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100D4
		opword 0x38800021
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x3877011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x3A000000
		opword 0x38600090
		opword 0x38800000
		opword 0x38A00006
		bl GXBegin
		opword 0x38700010
		opword 0x38900001
		opword 0x7E058378
		opword 0x39300011
		opword 0x7C872378
		opword 0x7C681B78
		opword 0x38C00000
		opword 0x39400001
		bl tri2
		opword 0x3A100001
		opword 0x2C10000F
		opword 0x4180FFC4
		opword 0x3BFF0001
		opword 0x3A730004
		opword 0x2C1F0007
		opword 0x3A520002
		opword 0x3A940004
		opword 0x4180FA88
	}
}
#pragma pop
#endif

#pragma force_active on
#pragma explicit_zero_data on
#pragma explicit_zero_data reset

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fa840[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fa84c[3] = {-0.03f, 1.0f, 0.1f};
__declspec(section ".rodata") const f32 vec3_802fa858[3] = {0.03f, 1.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802fa868 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802FA870[20] = "KamekiTornadeN64\0\0\0";
__declspec(section ".rodata") const u32 gap_04_802FA884_rodata = 0x00000000;
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
__declspec(section ".sdata2") const u32 gap_09_8041F22C_sdata2[1] = {0};
#endif
