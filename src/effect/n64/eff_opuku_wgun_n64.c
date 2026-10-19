#include "system.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSFastCast.h>
#include <stdlib.h>
__declspec(section ".sdata2") u32 gap_10_804231EC_sbss2[1];
__declspec(section ".sdata2") u32 unk_804231e8;
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802fb2c0[3];
__declspec(section ".rodata") extern const f64 double_to_int_802fb2d0;
__declspec(section ".rodata") extern const char str_802FB2D8[16];
__declspec(section ".sdata2") extern const u32 dat_8041f840;
__declspec(section ".sdata2") extern const f32 float_2_8041f844;
__declspec(section ".sdata2") extern const f32 float_0p5_8041f848;
__declspec(section ".sdata2") extern const f32 float_6_8041f84c;
__declspec(section ".sdata2") extern const f32 float_1_8041f850;
__declspec(section ".sdata2") extern const f32 float_30_8041f854;
__declspec(section ".sdata2") extern const f32 float_6p2832_8041f858;
__declspec(section ".sdata2") extern const f32 float_360_8041f85c;
__declspec(section ".sdata2") extern const f32 float_20_8041f860;
__declspec(section ".sdata2") extern const f32 float_0_8041f864;
__declspec(section ".sdata2") extern const f32 float_0p05_8041f868;
__declspec(section ".sdata2") extern const f32 float_0p015625_8041f86c;
__declspec(section ".sdata2") extern const f32 float_0p03125_8041f870;
__declspec(section ".sdata2") extern const f32 float_180_8041f874;
__declspec(section ".sdata2") extern const f32 float_120_8041f878;
__declspec(section ".sdata2") extern const f32 float_255_8041f87c;
__declspec(section ".sdata2") extern const f32 float_10_8041f880;
#endif

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

#ifdef NONMATCHING
static inline f32 dsin(f32 a) { return sin(6.2831855f * a / 360.0f); }
#endif
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

void DCFlushRange(void* addr, u32 nBytes);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXInvalidateVtxCache(void);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
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
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
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
        work->b[i] = EXT_LIT(float_2_8041f844, 2.0f);
        work->c[i] = EXT_LIT(float_0_8041f864, 0.0f);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
EffectEntry* effOpukuWgunN64Entry(s32 type, s32 lifetime, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2,
                                  f32 scale) {
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0xDBE10080
		opword 0xF3E10088
		opword 0xDBC10070
		opword 0xF3C10078
		opword 0xDBA10060
		opword 0xF3A10068
		opword 0xDB810050
		opword 0xF3810058
		opword 0xDB610040
		opword 0xF3610048
		opword 0xDB410030
		opword 0xF3410038
		opword 0xDB210020
		opword 0xF3210028
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0xFF200890
		opword 0x7C7E1B78
		opword 0xFF401090
		opword 0x7C9D2378
		opword 0xFF601890
		opword 0xFF802090
		opword 0xFFA02890
		opword 0xFFC03090
		opword 0xFFE03890
		bl effEntry
		lis r4, str_802FB2D8@ha
		opword 0x7C7F1B78
		addi r4, r4, str_802FB2D8@l
		opword 0x38000001
		opword 0x909F0014
		opword 0x38600003
		opword 0x388001E4
		opword 0x901F0008
		bl __memAlloc
		lis r4, effOpukuWgunMain@ha
		opword 0x907F000C
		addi r4, r4, effOpukuWgunMain@l
		opword 0x2C1D0000
		opword 0x909F0010
		opword 0x38000000
		opword 0x809F0000
		opword 0x60840002
		opword 0x909F0000
		opword 0x93C30000
		opword 0x90030030
		opword 0x41810010
		opword 0x380003E8
		opword 0x9003002C
		opword 0x48000020
		opword 0x2C1E0000
		opword 0x40820010
		opword 0x57A0083C
		opword 0x9003002C
		opword 0x4800000C
		opword 0x57A0103A
		opword 0x9003002C
		opword 0x2C1E0000
		opword 0x93A30028
		opword 0x40820010
		opword 0x380000C8
		opword 0x90030040
		opword 0x4800000C
		opword 0x380000FF
		opword 0x90030040
		opword 0xD3230010
		opword 0x390000D2
		opword 0x38E000E6
		opword 0x38C000FF
		opword 0xD3430014
		opword 0x38A00000
		opword 0x3880001E
		opword 0x380000CD
		opword 0xD3630018
		opword 0x2C1E0000
		lfs f3, float_10_8041f880(r2)
		opword 0x7C691B78
		opword 0xD383001C
		opword 0x39600000
		lfs f2, float_2_8041f844(r2)
		opword 0x39400001
		opword 0xD3A30020
		lfs f1, float_0_8041f864(r2)
		opword 0xD3C30024
		opword 0xD3E30050
		opword 0x91030034
		opword 0x90E30038
		opword 0x90C3003C
		opword 0x90A30044
		opword 0x90830048
		opword 0x9003004C
		opword 0x90A30054
		opword 0xC0030010
		opword 0xD0030004
		opword 0xC0030014
		opword 0xD0030008
		opword 0xC0030018
		opword 0xD003000C
		opword 0x408200DC
		opword 0x38000003
		opword 0x7C0903A6
		opword 0xD0690058
		opword 0x380B0001
		opword 0xD0490088
		opword 0xD02900B8
		opword 0x90090178
		opword 0x380B0002
		opword 0xC0030004
		opword 0xD00900E8
		opword 0xC0030008
		opword 0xD0090118
		opword 0xC003000C
		opword 0xD0090148
		opword 0x90A901A8
		opword 0xD069005C
		opword 0xD049008C
		opword 0xD02900BC
		opword 0x9009017C
		opword 0x380B0003
		opword 0xC0030004
		opword 0xD00900EC
		opword 0xC0030008
		opword 0xD009011C
		opword 0xC003000C
		opword 0xD009014C
		opword 0x90A901AC
		opword 0xD0690060
		opword 0xD0490090
		opword 0xD02900C0
		opword 0x90090180
		opword 0x380B0004
		opword 0x396B0004
		opword 0xC0030004
		opword 0xD00900F0
		opword 0xC0030008
		opword 0xD0090120
		opword 0xC003000C
		opword 0xD0090150
		opword 0x90A901B0
		opword 0xD0690064
		opword 0xD0490094
		opword 0xD02900C4
		opword 0x90090184
		opword 0xC0030004
		opword 0xD00900F4
		opword 0xC0030008
		opword 0xD0090124
		opword 0xC003000C
		opword 0xD0090154
		opword 0x90A901B4
		opword 0x39290010
		opword 0x4200FF38
		opword 0x480000D4
		opword 0x38000003
		opword 0x7C0903A6
		opword 0xD0690058
		opword 0xD0490088
		opword 0xD02900B8
		opword 0x91490178
		opword 0x394A0005
		opword 0xC0030004
		opword 0xD00900E8
		opword 0xC0030008
		opword 0xD0090118
		opword 0xC003000C
		opword 0xD0090148
		opword 0x90A901A8
		opword 0xD069005C
		opword 0xD049008C
		opword 0xD02900BC
		opword 0x9149017C
		opword 0x394A0005
		opword 0xC0030004
		opword 0xD00900EC
		opword 0xC0030008
		opword 0xD009011C
		opword 0xC003000C
		opword 0xD009014C
		opword 0x90A901AC
		opword 0xD0690060
		opword 0xD0490090
		opword 0xD02900C0
		opword 0x91490180
		opword 0x394A0005
		opword 0xC0030004
		opword 0xD00900F0
		opword 0xC0030008
		opword 0xD0090120
		opword 0xC003000C
		opword 0xD0090150
		opword 0x90A901B0
		opword 0xD0690064
		opword 0xD0490094
		opword 0xD02900C4
		opword 0x91490184
		opword 0x394A0005
		opword 0xC0030004
		opword 0xD00900F4
		opword 0xC0030008
		opword 0xD0090124
		opword 0xC003000C
		opword 0xD0090154
		opword 0x90A901B4
		opword 0x39290010
		opword 0x4200FF3C
		opword 0x7FE3FB78
		opword 0xE3E10088
		opword 0xCBE10080
		opword 0xE3C10078
		opword 0xCBC10070
		opword 0xE3A10068
		opword 0xCBA10060
		opword 0xE3810058
		opword 0xCB810050
		opword 0xE3610048
		opword 0xCB610040
		opword 0xE3410038
		opword 0xCB410030
		opword 0xE3210028
		opword 0xCB210020
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x80010094
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210090
	}
}
#pragma pop
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

            work->y[i] = EXT_LIT(float_120_8041f878, 120.0f) * dsin(EXT_LIT(float_180_8041f874, 180.0f) * t) + (work->start.y + t * (work->end.y - work->start.y));
            work->z[i] = work->start.z + t * (work->end.z - work->start.z);
            work->alphas[i] = (u8)(EXT_LIT(float_255_8041f87c, 255.0f) - 255.0f * t);
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&position), 2, (DispCallback)effOpukuWgunDisp, effect);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void effOpukuWgunMain(EffectEntry* effect) {
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xBF410038
		lis r4, vec3_802fb2c0@ha
		opword 0x83C3000C
		addi r5, r4, vec3_802fb2c0@l
		opword 0x7C7A1B78
		opword 0x80850000
		opword 0x80650004
		opword 0x80050008
		opword 0x90810008
		opword 0xC01E0004
		opword 0x9061000C
		opword 0xC03E0008
		opword 0xD0010008
		opword 0xC01E000C
		opword 0x90010010
		opword 0x80810008
		opword 0xD021000C
		opword 0xD0010010
		opword 0x8061000C
		opword 0x80010010
		opword 0x90810014
		opword 0x90610018
		opword 0x9001001C
		opword 0x807A0000
		opword 0x839E0000
		opword 0x5460077B
		opword 0x41820014
		opword 0x546307B8
		opword 0x38000010
		opword 0x907A0000
		opword 0x901E002C
		opword 0x807E002C
		opword 0x2C0303E8
		opword 0x4080000C
		opword 0x3803FFFF
		opword 0x901E002C
		opword 0x807E0030
		opword 0x38030001
		opword 0x901E0030
		opword 0x801E002C
		opword 0x2C000000
		opword 0x40800010
		opword 0x7F43D378
		bl effDelete
		opword 0x4800019C
		opword 0x807E0054
		opword 0x837E0028
		opword 0x38030001
		opword 0x901E0054
		opword 0x801E0054
		opword 0x2C00000C
		opword 0x4081000C
		opword 0x3800000C
		opword 0x901E0054
		opword 0x3BA00000
		opword 0x7FDFF378
		opword 0x807F0178
		opword 0x2C030000
		opword 0x41820018
		opword 0x3803FFFF
		opword 0x901F0178
		opword 0x801F0178
		opword 0x2C000000
		opword 0x40820120
		opword 0x807F01A8
		opword 0x38030001
		opword 0x901F01A8
		opword 0x801F01A8
		opword 0x7C00D800
		opword 0x41800008
		opword 0x7F60DB78
		opword 0x3C604330
		opword 0x6C048000
		opword 0x90810024
		opword 0x6F608000
		lis r5, double_to_int_802fb2d0@ha
		opword 0x2C1C0000
		opword 0x90610020
		lfd f2, double_to_int_802fb2d0@l(r5)
		opword 0xC8010020
		opword 0x9001002C
		opword 0xEC201028
		opword 0x90610028
		opword 0xC8010028
		opword 0xEC001028
		opword 0xEFE10024
		opword 0x40820044
		opword 0xC03E0010
		opword 0xC01E001C
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F00E8
		opword 0xC03E0014
		opword 0xC01E0020
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0118
		opword 0xC03E0018
		opword 0xC01E0024
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0148
		opword 0x48000084
		lfs f0, float_180_8041f874(r2)
		lfs f2, float_6p2832_8041f858(r2)
		opword 0xEC2007F2
		lfs f0, float_360_8041f85c(r2)
		opword 0xC09E0010
		opword 0xC07E001C
		opword 0xEC220072
		opword 0xEC432028
		opword 0xEC210024
		opword 0xEC1F20BA
		opword 0xD01F00E8
		bl sin
		opword 0xC09E0014
		opword 0xFC600818
		opword 0xC03E0020
		opword 0x381D01D8
		lfs f0, float_255_8041f87c(r2)
		opword 0xEC212028
		lfs f2, float_120_8041f878(r2)
		opword 0xEC0007FC
		opword 0xEC3F207A
		opword 0xFC00001E
		opword 0xEC2208FA
		opword 0xD8010028
		opword 0xD03F0118
		opword 0x8061002C
		opword 0xC03E0018
		opword 0xC01E0024
		opword 0xEC000828
		opword 0xEC1F083A
		opword 0xD01F0148
		opword 0x7C7E01AE
		opword 0x3BBD0001
		opword 0x3BFF0004
		opword 0x2C1D000C
		opword 0x4180FEB8
		opword 0x38610014
		bl dispCalcZ
		lis r3, effOpukuWgunDisp@ha
		opword 0x7F46D378
		addi r5, r3, effOpukuWgunDisp@l
		opword 0x38800002
		opword 0x38600004
		bl dispEntry
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xBB410038
		opword 0x80010064
		opword 0x7C0803A6
		opword 0x38210060
	}
}
#pragma pop
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
    f32 zero = EXT_LIT(float_0_8041f864, 0.0f);
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
            if (s > EXT_LIT(float_6_8041f84c, 6.0f)) {
                s = 6.0f;
            }
            a = a_data[i];
        } else {
            s = 1.0f + 0.5f * (f32)work->counter[i];
            if (s > EXT_LIT(float_30_8041f854, 30.0f)) {
                s = 30.0f;
            }
            a = a_data[i] * work->alphas[i] / 255;
        }
        s = s * scl;
        rad = EXT_LIT(float_6p2832_8041f858, 6.2831855f) * ang / EXT_LIT(float_360_8041f85c, 360.0f);
        dx = s * (f32)sin(rad);
        dy = s * (f32)cos(rad);
        p->x = EXT_LIT(float_20_8041f860, 20.0f) * (work->x[i] + dx);
        p->y = EXT_LIT(float_20_8041f860, 20.0f) * (work->y[i] + dy);
        p->z = EXT_LIT(float_20_8041f860, 20.0f) * (work->z[i] + zero);
        p->s = k;
        p->t = 0;
        p->r = (i & 1) * 255;
        p->g = ((i >> 1) & 1) * 255;
        p->b = ((i >> 2) & 1) * 255;
        p->a = a;
        p++;
        p->x = EXT_LIT(float_20_8041f860, 20.0f) * (work->x[i] - dx);
        p->y = EXT_LIT(float_20_8041f860, 20.0f) * (work->y[i] - dy);
        p->z = EXT_LIT(float_20_8041f860, 20.0f) * (work->z[i] + zero);
        p->s = k;
        p->t = 1024;
        p->r = (i & 1) * 255;
        p->g = ((i >> 1) & 1) * 255;
        p->b = ((i >> 2) & 1) * 255;
        p->a = a;
        p++;
        k += 320;
    }
    PSMTXScale(scale, EXT_LIT(float_0p05_8041f868, 0.05f), EXT_LIT(float_0p05_8041f868, 0.05f), EXT_LIT(float_0p05_8041f868, 0.05f));
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
        PSMTXScale(scale, EXT_LIT(float_0p015625_8041f86c, 0.015625f), EXT_LIT(float_0p03125_8041f870, 0.03125f), EXT_LIT(float_0_8041f864, 0.0f));
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
        PSMTXScale(scale, EXT_LIT(float_0p03125_8041f870, 0.03125f), EXT_LIT(float_0p03125_8041f870, 0.03125f), EXT_LIT(float_0_8041f864, 0.0f));
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void effOpukuWgunDisp(CameraId cameraId, EffectEntry* effect) {
	char _af_pad[168];
	asm volatile {
		opword 0x7C962378
		bl camGetPtr
		opword 0x8376000C
		opword 0x7C7F1B78
		lwz r0, unk_804231e8(r2)
		la r4, _af_pad+24
		opword 0x80FB0034
		opword 0x38600001
		opword 0x9001001C
		opword 0x80DB0038
		opword 0x80BB003C
		opword 0x801B0040
		opword 0x98E1001C
		opword 0x833B0000
		opword 0x98C1001D
		opword 0xC31B0050
		opword 0x98A1001E
		opword 0x9801001F
		opword 0x8001001C
		opword 0x90010020
		bl GXSetTevColor
		lwz r0, dat_8041f840(r2)
		opword 0x38810018
		opword 0x80DB0044
		opword 0x38600002
		opword 0x90010014
		opword 0x80BB0048
		opword 0x801B004C
		opword 0x98C10014
		opword 0x98A10015
		opword 0x98010016
		opword 0x80010014
		opword 0x90010018
		bl GXSetTevColor
		opword 0x38600000
		bl GXSetCullMode
		opword 0x386002A0
		opword 0x38800003
		bl smartAlloc
		opword 0x82E30000
		opword 0x3B800000
		lfs f28, float_6p2832_8041f858(r2)
		opword 0x7F7EDB78
		lfs f29, float_360_8041f85c(r2)
		opword 0x7EF8BB78
		lfs f30, float_20_8041f860(r2)
		opword 0x3B400000
		lfs f31, float_0_8041f864(r2)
		la r29, a_data(r13)
		opword 0x2C1A0000
		opword 0x41820008
		opword 0x40820028
		opword 0xC03E00EC
		opword 0xC01E00E8
		opword 0xFC400850
		opword 0xC03E011C
		opword 0xFC800050
		opword 0xC07E0118
		bl angleABf
		opword 0xFEC00850
		opword 0x48000038
		opword 0x2C1A000B
		opword 0x41820030
		opword 0x801E0178
		opword 0x2C000000
		opword 0x40820024
		opword 0xC03E00EC
		opword 0xC01E00E8
		opword 0xFC400850
		opword 0xC03E011C
		opword 0xFC800050
		opword 0xC07E0118
		bl angleABf
		opword 0xFEC00850
		opword 0x801B0000
		opword 0x2C000000
		opword 0x40820050
		opword 0x80BE01A8
		opword 0x3C004330
		opword 0x90010080
		lis r4, double_to_int_802fb2d0@ha
		opword 0x6CA08000
		lfd f2, double_to_int_802fb2d0@l(r4)
		opword 0x90010084
		lfs f3, float_0p5_8041f848(r2)
		opword 0xC8010080
		lfs f1, float_2_8041f844(r2)
		opword 0xEC401028
		lfs f0, float_6_8041f84c(r2)
		opword 0xEC2308BA
		opword 0xFEA00890
		opword 0xFC010040
		opword 0x40810008
		opword 0xFEA00090
		lbz r22, 0x0(r29)
		opword 0x48000074
		opword 0x80BE01A8
		opword 0x3C004330
		opword 0x90010080
		lis r4, double_to_int_802fb2d0@ha
		opword 0x6CA08000
		lfd f2, double_to_int_802fb2d0@l(r4)
		opword 0x90010084
		lfs f3, float_0p5_8041f848(r2)
		opword 0xC8010080
		lfs f1, float_1_8041f850(r2)
		opword 0xEC401028
		lfs f0, float_30_8041f854(r2)
		opword 0xEC2308BA
		opword 0xFEA00890
		opword 0xFC010040
		opword 0x40810008
		opword 0xFEA00090
		opword 0x381A01D8
		opword 0x3C808081
		opword 0x88BD0000
		opword 0x38848081
		opword 0x7C1B00AE
		opword 0x7C0501D6
		opword 0x7C840096
		opword 0x7C040214
		opword 0x7C003E70
		opword 0x54040FFE
		opword 0x7EC02214
		opword 0xEC1C05B2
		fmuls f21, f21, f24
		opword 0xEEE0E824
		opword 0xFC20B890
		bl sin
		opword 0xFC000818
		opword 0xFC20B890
		opword 0xEEF50032
		bl cos
		opword 0xC01E00E8
		opword 0x5744F7FE
		opword 0xFC200818
		opword 0x574507FE
		opword 0xEC00B82A
		opword 0x5740FFFE
		opword 0x1CC500FF
		opword 0x3B5A0001
		opword 0xEC1E0032
		opword 0x38A00000
		opword 0x1CE000FF
		opword 0xEC350072
		opword 0x38000400
		opword 0xFC00001E
		opword 0x1D0400FF
		opword 0x2C1A000C
		opword 0x3BBD0001
		opword 0xD8010080
		opword 0x80810084
		opword 0xB0970000
		opword 0xC01E0118
		opword 0xEC00082A
		opword 0xEC1E0032
		opword 0xFC00001E
		opword 0xD8010088
		opword 0x8081008C
		opword 0xB0970002
		opword 0xC01E0148
		opword 0xEC00F82A
		opword 0xEC1E0032
		opword 0xFC00001E
		opword 0xD8010090
		opword 0x80810094
		opword 0xB0970004
		opword 0xB3970006
		opword 0xB0B70008
		opword 0x98D7000A
		opword 0x98F7000B
		opword 0x9917000C
		opword 0x9AD7000D
		opword 0xC01E00E8
		opword 0xEC00B828
		opword 0xEC1E0032
		opword 0xFC00001E
		opword 0xD8010098
		opword 0x8081009C
		opword 0xB097000E
		opword 0xC01E0118
		opword 0xEC000828
		opword 0xEC1E0032
		opword 0xFC00001E
		opword 0xD80100A0
		opword 0x808100A4
		opword 0xB0970010
		opword 0xC01E0148
		opword 0x3BDE0004
		opword 0xEC00F82A
		opword 0xEC1E0032
		opword 0xFC00001E
		opword 0xD80100A8
		opword 0x808100AC
		opword 0xB0970012
		opword 0xB3970014
		opword 0x3B9C0140
		opword 0xB0170016
		opword 0x98D70018
		opword 0x98F70019
		opword 0x9917001A
		opword 0x9AD7001B
		opword 0x3AF7001C
		opword 0x4180FD98
		lfs f1, float_0p05_8041f868(r2)
		opword 0x38610050
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7F16C378
		opword 0x5757083C
		opword 0x3B600000
		opword 0x480000C4
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
		opword 0xD0010024
		opword 0xE016D002
		opword 0xD0010028
		opword 0xE016D004
		opword 0x38810024
		opword 0x7C852378
		opword 0x38610050
		opword 0xD001002C
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
		opword 0xC3610024
		opword 0xF361D010
		opword 0xA8010010
		opword 0xB0160000
		opword 0xC3410028
		opword 0xF341D00C
		opword 0xA801000C
		opword 0xB0160002
		opword 0xC321002C
		opword 0xF321D008
		opword 0x3B7B0001
		opword 0xA8010008
		opword 0xB0160004
		opword 0x3AD6000E
		opword 0x7C1BB800
		opword 0x4180FF3C
		opword 0x7F03C378
		opword 0x388002A0
		bl DCFlushRange
		bl GXInvalidateVtxCache
		opword 0x7F03C378
		bl effSetVtxDescN64
		opword 0x387F011C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x38600000
		bl GXSetCurrentMtx
		opword 0x2C190000
		opword 0x40820190
		opword 0x38600001
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600002
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
		opword 0x38800004
		opword 0x38A00002
		opword 0x38C00008
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
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
		opword 0x3880000F
		opword 0x38A0000F
		opword 0x38C0000F
		opword 0x38E00000
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00000
		opword 0x38C00005
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lfs f1, float_0p015625_8041f86c(r2)
		opword 0x38610050
		lfs f2, float_0p03125_8041f870(r2)
		lfs f3, float_0_8041f864(r2)
		bl PSMTXScale
		opword 0x38610050
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38810030
		opword 0x3860008D
		bl effGetTexObjN64
		opword 0x38610030
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x4800018C
		opword 0x38600001
		bl GXSetNumChans
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00000
		opword 0x39000000
		opword 0x39200002
		bl GXSetChanCtrl
		opword 0x38600002
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
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
		opword 0x38800002
		opword 0x38A00008
		opword 0x38C0000B
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00001
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		opword 0x388000FF
		opword 0x38A000FF
		opword 0x38C00004
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
		opword 0x38800004
		opword 0x38A00002
		opword 0x38C00000
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600001
		opword 0x38800007
		opword 0x38A00005
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600001
		bl GXSetNumTexGens
		opword 0x38600000
		opword 0x38800001
		opword 0x38A00004
		opword 0x38C0001E
		opword 0x38E00000
		opword 0x3900007D
		bl GXSetTexCoordGen2
		lfs f1, float_0p03125_8041f870(r2)
		opword 0x38610050
		lfs f3, float_0_8041f864(r2)
		opword 0xFC400890
		bl PSMTXScale
		opword 0x38610050
		opword 0x3880001E
		opword 0x38A00001
		bl GXLoadTexMtxImm
		opword 0x38810030
		opword 0x3860008E
		bl effGetTexObjN64
		opword 0x38610030
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x3B000000
		opword 0x3ADAFFFF
		opword 0x7F17C378
		opword 0x48000048
		opword 0x2C180000
		opword 0x41800038
		opword 0x38600090
		opword 0x38800000
		opword 0x38A00006
		bl GXBegin
		opword 0x38970002
		opword 0x38B70001
		opword 0x7EE3BB78
		opword 0x7EE6BB78
		opword 0x7CA72B78
		opword 0x7C882378
		opword 0x7EEABB78
		opword 0x39370003
		bl tri2
		opword 0x3AF70002
		opword 0x3B180001
		opword 0x7C18B000
		opword 0x4180FFB8
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
__declspec(section ".rodata") const f32 vec3_802fb2c0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802fb2d0 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802FB2D8[16] = "OpukuWgunN64\0\0\0";
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
__declspec(section ".sdata2") const u32 gap_09_8041F884_sdata2[1] = {0};
#endif
