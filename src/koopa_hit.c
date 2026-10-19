#include "driver/camdrv.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <string.h>
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_802fe320[3];
__declspec(section ".rodata") extern const f32 vec3_802fe32c[3];
__declspec(section ".rodata") extern const f32 vec3_802fe338[3];
__declspec(section ".rodata") extern const char str_802FE344[];
__declspec(section ".rodata") extern const char str_802FE35C[];
__declspec(section ".rodata") extern const f64 double_to_int_802fe368;
__declspec(section ".rodata") extern const f64 double_0p6_802fe370;
__declspec(section ".rodata") extern const f64 double_0p5_802fe378;
__declspec(section ".rodata") extern const f64 double_3_802fe380;
__declspec(section ".rodata") extern const f64 double_0_802fe388;
__declspec(section ".sdata2") extern const f32 float_0p5_80420e70;
__declspec(section ".sdata2") extern const f32 float_1000_80420e74;
__declspec(section ".sdata2") extern const f32 float_3p1416_80420e78;
__declspec(section ".sdata2") extern const f32 float_180_80420e7c;
__declspec(section ".sdata2") extern const f32 float_0_80420e80;
__declspec(section ".sdata2") extern const f32 float_neg1_80420e84;
__declspec(section ".sdata2") extern const f32 float_2_80420e88;
__declspec(section ".sdata2") extern const f32 float_35_80420e8c;
__declspec(section ".sdata2") extern const f32 float_10_80420e90;
__declspec(section ".sdata2") extern const f32 float_1_80420e94;
__declspec(section ".sdata2") extern const f32 float_100_80420e98;
__declspec(section ".sdata2") extern const f32 float_0p01_80420e9c;
__declspec(section ".sdata2") extern const f32 float_0p25_80420ea0;
__declspec(section ".sdata2") extern const f32 float_0p6_80420ea4;
__declspec(section ".sdata2") extern const f32 float_3_80420ea8;
__declspec(section ".sdata2") extern const f32 float_0p05_80420eac;
__declspec(section ".sdata2") extern const f32 float_50_80420eb0;
__declspec(section ".sdata2") extern const f32 float_deg2rad_80420eb4;
__declspec(section ".sdata2") extern const f32 float_90_80420eb8;
__declspec(section ".sdata2") extern const f32 float_270_80420ebc;
__declspec(section ".sdata2") extern const f32 float_7_80420ec0;
__declspec(section ".sdata2") extern const u32 gap_09_80420EC4_sdata2;
#define EXT_LIT(sym, val) (sym)

#endif
s32 kpaEnemyFireHitChk(f32 x, f32 y, f32 z, f32 h, f32 w);
void _restfpr_28(void);
void _savefpr_28(void);
BOOL kpaFlameHitFilter(HitCheckQuery* query, HitEntry* entry);

#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#endif

extern int __float_nan[];
extern double sin(double);
extern double cos(double);
extern f32 toMovedir(f32 angle);
extern MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);
extern s32 kpaGetLevel(void);
extern s32 kpaGetStageType(void);
extern s32 kpaFireAttackCheck(void);
extern s32 kpaMutekiCheck(void);
extern u8* getKoopaFireEfp(void);

typedef struct KpaHitWork {
    u8 pad0[0x18];
    HitEntry* flame;  // 0x18
    HitEntry* obj;    // 0x1C
    HitEntry* head[10];
    s32 pad48;
    HitEntry* ride_[10];
    f32 headDist[10];
} KpaHitWork;

#define KPW (*(KpaHitWork**)((u8*)marioGetPtr() + 0x28C))
#define MF(m, off) (*(f32*)((u8*)(m) + (off)))
#define MS16(m, off) (*(s16*)((u8*)(m) + (off)))
#define KHEAD(i) (*(HitEntry**)((u8*)KPW + 0x20 + (i) * 4))
#define KHEADD(i) (*(f32*)((u8*)KPW + 0x78 + (i) * 4))
#define KRIDE(i) (*(HitEntry**)((u8*)KPW + 0x4C + (i) * 4))
#define KRIDED(i) (*(f32*)((u8*)KPW + 0xA4 + (i) * 4))

#ifdef NONMATCHING
static inline s32 party_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 party_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (party_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif

#ifdef NONMATCHING
static inline f32 kpa_nrmToAngle(f32 x, f32 y, f32 z) {
    return angleABf(0.0f, 0.0f, party_sqrtf(x * x + z * z), -y);
}
#endif

#ifdef NONMATCHING
static inline f32 kpa_nrmSet(MarioWork* m, f32 x, f32 y, f32 z) {
    MF(m, 0x218) = (s32)(angleABf(0.0f, 0.0f, 100.0f * z, 100.0f * y) - 180.0f);
    MF(m, 0x21C) = 0.0f;
    MF(m, 0x220) = (s32)(angleABf(0.0f, 0.0f, 100.0f * x, 100.0f * y) - 180.0f);
    return kpa_nrmToAngle(x, y, z);
}
#endif


static f32 kpaHalf(f32 v);



#ifndef NONMATCHING
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
f32 PSVECMag(const Vec* v);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
extern u32 g5_headchkofs_s581[4];
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 kpaEnemyFireHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
	asm volatile {
		opword 0x9421FE90
		opword 0x7C0802A6
		opword 0x90010174
		opword 0xDBE10160
		opword 0xF3E10168
		opword 0xDBC10150
		opword 0xF3C10158
		opword 0xDBA10140
		opword 0xF3A10148
		opword 0xDB810130
		opword 0xF3810138
		opword 0xDB610120
		opword 0xF3610128
		opword 0x93E1011C
		opword 0x93C10118
		opword 0x93A10114
		opword 0xFF600890
		opword 0xFF801090
		opword 0xFFE01890
		opword 0xFFA02090
		opword 0xFFC02890
		bl getKoopaFireEfp
		opword 0x7C7F1B78
		opword 0x38600004
		bl camGetPtr
		lis r3, vec3_802fe320@ha
		lfs f0, float_0p5_80420e70(r2)
		addi r5, r3, vec3_802fe320@l
		opword 0x281F0000
		opword 0x80850000
		opword 0xEC00E77A
		opword 0x80650004
		opword 0x80050008
		opword 0x90810014
		opword 0x90610018
		opword 0x9001001C
		opword 0xD3610014
		opword 0xD0010018
		opword 0x80810014
		opword 0xD3E1001C
		opword 0x80610018
		opword 0x8001001C
		opword 0x9081002C
		opword 0x90610030
		opword 0x90010034
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000198
		opword 0x83DF000C
		opword 0x386100A4
		opword 0xC3BE0040
		opword 0xC03E0004
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		opword 0x38600004
		bl camGetPtr
		opword 0xC0430114
		opword 0x38610074
		opword 0xC03E0048
		opword 0x38800079
		lfs f0, float_deg2rad_80420eb4(r2)
		opword 0xEC211028
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0xC03E0048
		lfs f0, float_90_80420eb8(r2)
		opword 0xFC010040
		opword 0x40810028
		lfs f0, float_270_80420ebc(r2)
		opword 0xFC010040
		opword 0x4080001C
		opword 0xC03E0040
		opword 0x386100D4
		opword 0xFC400890
		opword 0xFC600850
		bl PSMTXScale
		opword 0x48000018
		opword 0xC03E0040
		opword 0x386100D4
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386100A4
		opword 0x38810074
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100A4
		opword 0x388100D4
		opword 0x38A10044
		bl PSMTXConcat
		lfs f0, float_0p5_80420e70(r2)
		opword 0x3BA00001
		opword 0x3BDE0050
		opword 0xEFE007B2
		opword 0x480000C8
		opword 0x801E0044
		opword 0x2C000000
		opword 0x408200B4
		lfs f2, float_7_80420ec0(r2)
		opword 0x386100A4
		opword 0xC01E0040
		opword 0xC03E0004
		opword 0xEFC20032
		opword 0xC05E0008
		opword 0xC07E000C
		bl PSMTXTrans
		opword 0xFC20F090
		opword 0x386100D4
		opword 0xFC40F090
		opword 0xFC60F090
		bl PSMTXScale
		opword 0x386100A4
		opword 0x388100D4
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x388100A4
		opword 0x38610044
		opword 0x7C852378
		bl PSMTXConcat
		lis r4, vec3_802fe32c@ha
		opword 0x386100A4
		addi r8, r4, vec3_802fe32c@l
		opword 0x38810008
		opword 0x80E80000
		opword 0x38A10038
		opword 0x80C80004
		opword 0x80080008
		opword 0x90E10008
		opword 0x90C1000C
		opword 0x90010010
		bl PSMTXMultVec
		opword 0x3861002C
		opword 0x38810038
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x38610020
		bl PSVECMag
		opword 0xEC1EFF7A
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600001
		opword 0x4800001C
		opword 0x3BBD0001
		opword 0x3BDE0050
		opword 0x801F0008
		opword 0x7C1D0000
		opword 0x4180FF34
		opword 0x38600000
		opword 0xE3E10168
		opword 0xCBE10160
		opword 0xE3C10158
		opword 0xCBC10150
		opword 0xE3A10148
		opword 0xCBA10140
		opword 0xE3810138
		opword 0xCB810130
		opword 0xE3610128
		opword 0xCB610120
		opword 0x83E1011C
		opword 0x83C10118
		opword 0x80010174
		opword 0x83A10114
		opword 0x7C0803A6
		opword 0x38210170
	}
}
#pragma pop
#endif
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
#ifdef NONMATCHING
    MarioWork* m;
    f32 dh, dw, dx, dy;

    m = marioGetPtr();

    if (kpaEnemyFireHitChk(x, y, z, h, w)) {
        return 2;
    }
    dh = 0.5f * (m->wPlayerCollisionBox.y + h);
    dw = 0.5f * (m->wPlayerCollisionBox.x + w);
    dx = __fabsf(m->position.x - x);
    dy = __fabsf(m->position.y + 0.5f * m->wPlayerCollisionBox.y - y - 0.5f * h);
    if (dy <= dh && dx <= dw) {
        if ((m->flags & 0x20000) && m->position.y > y) {
            if (kpaGetLevel() == 0 && kpaGetStageType() != 1 && m->unk4C == 0 && z < 50.0f) {
                marioChgMot(4);
            }
            return 1;
        }
        if (kpaMutekiCheck() == 1) {
            return 3;
        }
        if (m->unk4C != 0) {
            return 3;
        }
        if (MS16(m, 0x78) == 0) {
            return 4;
        }
    }
    return 0;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xDBC10040
		opword 0xF3C10048
		opword 0xDBA10030
		opword 0xF3A10038
		opword 0xDB810020
		opword 0xF3810028
		opword 0xDB610010
		opword 0xF3610018
		opword 0x93E1000C
		opword 0xFF600890
		opword 0xFFC01090
		opword 0xFFE01890
		opword 0xFF802090
		opword 0xFFA02890
		bl marioGetPtr
		opword 0xFC20D890
		opword 0x7C7F1B78
		opword 0xFC40F090
		opword 0xFC60F890
		opword 0xFC80E090
		opword 0xFCA0E890
		bl kpaEnemyFireHitChk
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38600002
		opword 0x480000EC
		opword 0xC01F01B8
		lfs f5, float_0p5_80420e70(r2)
		opword 0xEC80E02A
		opword 0xC03F0090
		opword 0xC07F01B4
		opword 0xEC05083A
		opword 0xC05F008C
		opword 0xEC63E82A
		opword 0xEC42D828
		opword 0xEC00F028
		opword 0xEC850132
		opword 0xEC6500F2
		opword 0xEC05073C
		opword 0xFC401210
		opword 0xFC000210
		opword 0xFC002040
		opword 0x4C401382
		opword 0x408200A0
		opword 0xFC021840
		opword 0x4C401382
		opword 0x40820094
		opword 0x801F0000
		opword 0x5400039D
		opword 0x4182004C
		opword 0xFC01F040
		opword 0x40810044
		bl kpaGetLevel
		opword 0x2C030000
		opword 0x40820030
		bl kpaGetStageType
		opword 0x2C030001
		opword 0x41820024
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x40820018
		lfs f0, float_50_80420eb0(r2)
		opword 0xFC1F0040
		opword 0x4080000C
		opword 0x38600004
		bl marioChgMot
		opword 0x38600001
		opword 0x48000044
		bl kpaMutekiCheck
		opword 0x2C030001
		opword 0x4082000C
		opword 0x38600003
		opword 0x48000030
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38600003
		opword 0x4800001C
		opword 0xA81F0078
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600004
		opword 0x48000008
		opword 0x38600000
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xE3C10048
		opword 0xCBC10040
		opword 0xE3A10038
		opword 0xCBA10030
		opword 0xE3810028
		opword 0xCB810020
		opword 0xE3610018
		opword 0xCB610010
		opword 0x80010064
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210060
	}
#endif
}
#ifdef NONMATCHING

static inline void kpa_headClear(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        KHEAD(i) = NULL;
        KHEADD(i) = 1000.0f;
    }
}

HitEntry* kpaSearchGround(f32 range, f32* outY, f32* outDepth, f32* outAng) {
    s32 n, i;
    MarioWork* m;
    MarioWork* m2;
    HitEntry* hit;
    HitEntry* best;
    Vec zero = {0.0f, 0.0f, 0.0f};
    f32 hx, hy, hz, dist, nx, ny, nz, nv;
    f32 h, deg, ex, ez, fx, fz, ang;
    f32 rad, r2b, r3, bd, yh, r2, px, py, pz, ox, oz;

    m = marioGetPtr();
    best = NULL;
    MF(m, 0x218) = 0.0f;
    MF(m, 0x21C) = 0.0f;
    MF(m, 0x220) = 0.0f;
    MF(m, 0x214) = 0.0f;
    if (m->flags & 0x200) {
        *outY = m->position.y;
        return NULL;
    }
    range += 0.01f;
    if (kpaGetLevel() == 0) {
        h = m->wPlayerCollisionBox.y;
    } else {
        h = 0.25f * m->wPlayerCollisionBox.y;
    }
    *outY = m->position.y;
    *outDepth = -1.0f;
    if (m->baseSpeed) {
        deg = m->directionView;
    } else {
        deg = toMovedir(m->displayDirection);
    }
    px = m->position.x;
    py = m->position.y;
    pz = m->position.z;
    for (i = 0; i < 10; i++) {
        KRIDE(i) = NULL;
        KRIDED(i) = 1000.0f;
    }
    switch (kpaGetLevel()) {
    case 0:
    case 1:
    case 2:
        n = 3;
        r2 = 0.6f * (0.5 * m->wPlayerCollisionBox.x);
        break;
    case 3:
        n = 7;
        r2 = 0.6f * (0.5f * m->wPlayerCollisionBox.x / 3.0f);
        break;
    }
    r2b = 2.0f * r2 - 0.05f;
    rad = 3.1415927f * deg; bd = h + range; yh = py + h;
    r3 = 3.0f * r2 - 0.05f;
    for (i = 0; i < n; i++) {
        switch (i) {
        case 0:
            ox = 0.0f;
            oz = ox;
            break;
        case 1:
            ang = rad / 180.0f;
            ox = (r2 - 0.05f) * (f32)sin(ang);
            nv = (f32)cos(ang); oz = (r2 - 0.05f) * -nv;
            break;
        case 2:
            ang = rad / 180.0f;
            nv = (f32)sin(ang); ox = (r2 - 0.05f) * -nv;
            nv = (f32)cos(ang); oz = (r2 - 0.05f) * -nv;
            break;
        case 3:
            ang = rad / 180.0f;
            ox = r2b * (f32)sin(ang);
            oz = r2b * -(f32)cos(ang);
            break;
        case 4:
            ang = rad / 180.0f;
            ox = r2b * -(f32)sin(ang);
            oz = r2b * -(f32)cos(ang);
            break;
        case 5:
            ang = rad / 180.0f;
            ox = r3 * (f32)sin(ang);
            oz = r3 * -(f32)cos(ang);
            break;
        case 6:
            ang = rad / 180.0f;
            ox = r3 * -(f32)sin(ang);
            oz = r3 * -(f32)cos(ang);
            break;
        }
        dist = bd;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, px + ox, yh, pz + oz, 0.0f, -1.0f, 0.0f);
        if (hit) {
            if (kpa_nrmSet(marioGetPtr(), nx, ny, nz) >= 50.0f) {
                hit = NULL;
            }
        }
        hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
        if (hit) {
            MF(m, 0x214) = kpa_nrmSet(marioGetPtr(), nx, ny, nz);
            if (hy < py && __fabsf(hy - py) >= 2.0f) {
                *outDepth = py - hy;
                *outAng = angleABf(px, pz, hx, hz);
                hit = NULL;
            } else {
                if (!nx && !nz) {
                    hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
                }
                *outY = hy;
                *outDepth = 0.0f;
                *outAng = angleABf(px, pz, hx, hz);
                best = hit;
            }
        }
        KRIDE(i) = hit;
        KRIDED(i) = ox;
    }
    return best;
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif


#ifndef NONMATCHING
HitEntry* kpaSearchGround(f32 range, f32* outY, f32* outDepth, f32* outAng);
__declspec(section ".data") static void* jumptable_803ADC44[7];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* kpaSearchGround(f32 range, f32* outY, f32* outDepth, f32* outAng) {
	char _af_pad[76];
	asm volatile {
		opword 0xFE000890
		lis r6, vec3_802fe320@ha
		opword 0x7C741B78
		opword 0x7C952378
		opword 0x7CB62B78
		addi r28, r6, vec3_802fe320@l
		bl marioGetPtr
		lfs f0, float_0_80420e80(r2)
		opword 0x7C7D1B78
		opword 0x3AE00000
		opword 0xD0030218
		opword 0xD003021C
		opword 0xD0030220
		opword 0xD0030214
		opword 0x80030000
		opword 0x540005AD
		opword 0x41820014
		opword 0xC01D0090
		opword 0x38600000
		opword 0xD0140000
		opword 0x480007A8
		lfs f0, float_0p01_80420e9c(r2)
		opword 0xEE10002A
		bl kpaGetLevel
		opword 0x2C030000
		opword 0x4082000C
		opword 0xC1FD01B8
		opword 0x48000010
		lfs f1, float_0p25_80420ea0(r2)
		opword 0xC01D01B8
		opword 0xEDE10032
		opword 0xC01D0090
		lfs f1, float_neg1_80420e84(r2)
		opword 0xD0140000
		lfs f0, float_0_80420e80(r2)
		opword 0xD0350000
		opword 0xC03D0180
		opword 0xFC010000
		opword 0x4182000C
		lfs f14, 0x1a0(r29)
		opword 0x48000010
		opword 0xC03D01A8
		bl toMovedir
		opword 0xFDC00890
		opword 0x3B000000
		opword 0xC2DD008C
		opword 0xC2BD0090
		mr r19, r24
		opword 0xC29D0094
		opword 0x3B400000
		lfs f17, float_1000_80420e74(r2)
		bl marioGetPtr
		opword 0x8063028C
		opword 0x3818004C
		opword 0x7E63012E
		bl marioGetPtr
		opword 0x3B5A0001
		opword 0x8063028C
		opword 0x381800A4
		opword 0x3B180004
		opword 0x2C1A000A
		opword 0x7E23052E
		opword 0x4180FFD4
		bl kpaGetLevel
		opword 0x2C030003
		opword 0x41820034
		opword 0x40800050
		opword 0x2C030000
		opword 0x40800008
		opword 0x48000044
		opword 0xC83C0058
		opword 0x3B200003
		opword 0xC01D01B4
		opword 0xC85C0050
		opword 0xFC010032
		opword 0xFEE20032
		opword 0xFEE0B818
		opword 0x48000024
		lfs f2, float_0p5_80420e70(r2)
		opword 0x3B200007
		opword 0xC03D01B4
		lfs f0, float_3_80420ea8(r2)
		opword 0xEC220072
		lfs f2, float_0p6_80420ea4(r2)
		opword 0xEC010024
		opword 0xEEE20032
		lfs f0, float_3p1416_80420e78(r2)
		opword 0x3B400000
		lfs f2, float_2_80420e88(r2)
		opword 0xEF2F802A
		lfs f1, float_0p05_80420eac(r2)
		opword 0xEF8003B2
		lfs f0, float_3_80420ea8(r2)
		opword 0xEF15782A
		opword 0xEF620DF8
		opword 0xEF400DF8
		lfs f29, float_100_80420e98(r2)
		lfs f19, float_0p5_80420e70(r2)
		opword 0x7F53D378
		opword 0xC9DC0048
		opword 0x7F5BD378
		opword 0x3FC04330
		opword 0x48000654
		opword 0x281A0006
		opword 0x4181016C
		lis r3, jumptable_803ADC44@ha
		addi r3, r3, jumptable_803ADC44@l
		opword 0x7C03982E
		opword 0x7C0903A6
		opword 0x4E800420
		lfs f31, float_0_80420e80(r2)
		opword 0xFFC0F890
		opword 0x4800014C
		lfs f0, float_180_80420e7c(r2)
		opword 0xEDFC0024
		opword 0xFC207890
		bl sin
		lfs f0, float_0p05_80420eac(r2)
		opword 0xFC400818
		opword 0xFC207890
		opword 0xEC170028
		opword 0xEFE000B2
		bl cos
		opword 0xFC400818
		lfs f0, float_0p05_80420eac(r2)
		opword 0xEC370028
		opword 0xFC001050
		opword 0xEFC10032
		opword 0x4800010C
		lfs f0, float_180_80420e7c(r2)
		opword 0xEDFC0024
		opword 0xFC207890
		bl sin
		opword 0xFC600818
		lfs f0, float_0p05_80420eac(r2)
		opword 0xFC207890
		opword 0xEC570028
		opword 0xFC001850
		opword 0xEFE20032
		bl cos
		opword 0xFC400818
		lfs f0, float_0p05_80420eac(r2)
		opword 0xEC370028
		opword 0xFC001050
		opword 0xEFC10032
		opword 0x480000C8
		lfs f0, float_180_80420e7c(r2)
		opword 0xEDFC0024
		opword 0xFC207890
		bl sin
		opword 0xFC000818
		opword 0xFC207890
		opword 0xEFFB0032
		bl cos
		opword 0xFC000818
		opword 0xFC000050
		opword 0xEFDB0032
		opword 0x48000098
		lfs f0, float_180_80420e7c(r2)
		opword 0xEDFC0024
		opword 0xFC207890
		bl sin
		opword 0xFC000818
		opword 0xFC207890
		opword 0xFC000050
		opword 0xEFFB0032
		bl cos
		opword 0xFC000818
		opword 0xFC000050
		opword 0xEFDB0032
		opword 0x48000064
		lfs f0, float_180_80420e7c(r2)
		opword 0xEDFC0024
		opword 0xFC207890
		bl sin
		opword 0xFC000818
		opword 0xFC207890
		opword 0xEFFA0032
		bl cos
		opword 0xFC000818
		opword 0xFC000050
		opword 0xEFDA0032
		opword 0x48000034
		lfs f0, float_180_80420e7c(r2)
		opword 0xEDFC0024
		opword 0xFC207890
		bl sin
		opword 0xFC000818
		opword 0xFC207890
		opword 0xFC000050
		opword 0xEFFA0032
		bl cos
		opword 0xFC000818
		opword 0xFC000050
		opword 0xEFDA0032
		lfs f4, float_0_80420e80(r2)
		opword 0xFC40C090
		opword 0xEC36F82A
		stfs f25, _af_pad+20(r1)
		opword 0xFCC02090
		lfs f5, float_neg1_80420e84(r2)
		opword 0xEC74F02A
		opword 0x38810028
		opword 0x38A10024
		opword 0x38C10020
		opword 0x38E1001C
		opword 0x39010018
		opword 0x39210014
		opword 0x39410010
		opword 0x38600000
		bl hitCheckFilter
		opword 0x7C781B79
		opword 0x418201BC
		opword 0xC2010010
		opword 0xC2210014
		opword 0xC2410018
		bl marioGetPtr
		lfs f0, float_100_80420e98(r2)
		opword 0x7C7F1B78
		lfs f1, float_0_80420e80(r2)
		opword 0xEDE00472
		opword 0xFC400890
		opword 0xEC600432
		opword 0xFC807890
		bl angleABf
		lfs f0, float_180_80420e7c(r2)
		opword 0x3C004330
		opword 0x90010038
		opword 0xFC807890
		opword 0xEC610028
		lfs f2, float_0_80420e80(r2)
		lfs f0, float_100_80420e98(r2)
		opword 0xC8BC0048
		opword 0xFC201090
		opword 0xFCC0181E
		opword 0xEC6004B2
		opword 0xD8C10030
		opword 0x80010034
		opword 0x6C008000
		opword 0x9001003C
		opword 0xC8010038
		opword 0xEC002828
		opword 0xD01F0218
		opword 0xD05F021C
		bl angleABf
		lfs f0, float_180_80420e7c(r2)
		opword 0x3C004330
		opword 0xEC500432
		opword 0x90010048
		opword 0xEC810028
		opword 0xC83C0048
		lfs f0, float_0_80420e80(r2)
		opword 0xEC7214BA
		opword 0xFC40201E
		opword 0xFC030040
		opword 0xD8410040
		opword 0x80010044
		opword 0x6C008000
		opword 0x9001004C
		opword 0xC8010048
		opword 0xEC000828
		opword 0xD01F0220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89C0058
		opword 0xC85C0060
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81C0068
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD061000C
		opword 0x3C007F80
		opword 0x8081000C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_80420e80(r2)
		opword 0xFC808850
		opword 0xFC400890
		bl angleABf
		lfs f0, float_50_80420eb0(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		opword 0x3B000000
		opword 0xC0010024
		opword 0x28180000
		opword 0x93C10040
		opword 0xEC1D983A
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC007028
		opword 0xEC00E824
		opword 0xD0010024
		opword 0x41820280
		opword 0xC2410010
		opword 0xC2210014
		opword 0xC2010018
		bl marioGetPtr
		lfs f0, float_100_80420e98(r2)
		opword 0x7C7F1B78
		lfs f1, float_0_80420e80(r2)
		opword 0xEDE00472
		opword 0xFC400890
		opword 0xEC6004B2
		opword 0xFC807890
		bl angleABf
		lfs f0, float_180_80420e7c(r2)
		opword 0x3C004330
		opword 0x90010040
		opword 0xFC807890
		opword 0xEC610028
		lfs f2, float_0_80420e80(r2)
		lfs f0, float_100_80420e98(r2)
		opword 0xC8BC0048
		opword 0xFC201090
		opword 0xFCC0181E
		opword 0xEC600432
		opword 0xD8C10048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC002828
		opword 0xD01F0218
		opword 0xD05F021C
		bl angleABf
		lfs f0, float_180_80420e7c(r2)
		opword 0x3C004330
		opword 0xEC5204B2
		opword 0x90010030
		opword 0xEC810028
		opword 0xC83C0048
		lfs f0, float_0_80420e80(r2)
		opword 0xEC70143A
		opword 0xFC40201E
		opword 0xFC030040
		opword 0xD8410038
		opword 0x8001003C
		opword 0x6C008000
		opword 0x90010034
		opword 0xC8010030
		opword 0xEC000828
		opword 0xD01F0220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89C0058
		opword 0xC85C0060
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81C0068
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0610008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_80420e80(r2)
		opword 0xFC808850
		opword 0xFC400890
		bl angleABf
		opword 0xD03D0214
		opword 0xC0410024
		opword 0xFC02A840
		opword 0x40800044
		opword 0xEC22A828
		lfs f0, float_2_80420e88(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082002C
		opword 0xEC151028
		opword 0xFC20B090
		opword 0xFC40A090
		opword 0xD0150000
		opword 0xC0610028
		opword 0xC0810020
		bl angleABf
		opword 0xD0360000
		opword 0x3B000000
		opword 0x4800008C
		opword 0xC0010018
		lfs f1, float_0_80420e80(r2)
		opword 0xFC000800
		opword 0x40820050
		opword 0xC0010010
		opword 0xFC000800
		opword 0x40820044
		lfs f2, float_100_80420e98(r2)
		opword 0x3C004330
		opword 0xC0210024
		lfs f0, float_0p5_80420e70(r2)
		opword 0x90010040
		opword 0xEC02007A
		opword 0xC83C0048
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010024
		opword 0xC0610024
		opword 0xFC20B090
		lfs f0, float_0_80420e80(r2)
		opword 0xFC40A090
		opword 0xD0740000
		opword 0xD0150000
		opword 0xC0610028
		opword 0xC0810020
		bl angleABf
		opword 0xD0360000
		opword 0x7F17C378
		bl marioGetPtr
		opword 0x8063028C
		opword 0x381B004C
		opword 0x7F03012E
		bl marioGetPtr
		opword 0x8063028C
		opword 0x381B00A4
		opword 0x3A730004
		opword 0x3B7B0004
		opword 0x7FE3052E
		opword 0x3B5A0001
		opword 0x7C1AC800
		opword 0x4180F9AC
		opword 0x7EE3BB78
	}
}
#pragma pop


// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
HitEntry* kpaSearchHead(f32 hgt, f32* outA, f32* outB) {
#ifdef NONMATCHING
    static s32 _ofs0[] = {3, 12, 16, 1, 0, 16, 0, -9, 16, 0};
    static s32 _ofs1[] = {4, 25, 74, 0, 50, 65, 1, 0, 67, 0, -25, 62, 0};
    static s32 _ofs2[] = {6, 50, 102, 0, 76, 90, 1, 25, 100, 0, 0, 94, 0, -25, 90, 0, -45, 68, 0};
    static s32 _ofs3[] = {13, 170, 194, 1, 145, 204, 0, 120, 232, 0, 95, 227, 0, 70, 232, 0, 55, 232, 0,
                          30, 194, 0, 5, 187, 0, -20, 210, 0, -45, 201, 0, -70, 181, 0, -95, 153, 0, -120, 56, 0};
    static s32* headchkofs[] = {_ofs0, _ofs1, _ofs2, _ofs3};
    s32 i, j, n;
    s32* tbl;
    HitEntry* hit;
    HitEntry* best;
    MarioWork* m;
    f32 deg, rad, off, c, s_, x, y, z, hx, hy, hz, nx, ny, nz, d;
    f32 oy, oz, mode;
    s32 md;

    m = marioGetPtr();
    if (m->flags & 0x20000) {
        return NULL;
    }
    best = NULL;
    if (m->baseSpeed) {
        deg = m->directionView;
    } else {
        deg = toMovedir(m->displayDirection);
    }
    off = *outB;
    *outB = -1.0f;
    kpa_headClear();
    tbl = headchkofs[kpaGetLevel()];
    n = *tbl++;
    if (!(m->flags & 0x10000)) {
        switch (kpaGetLevel()) {
        case 0:
            off = 2.0f;
            break;
        case 1:
            off = 0.0f;
            break;
        case 2:
            off = 0.0f;
            break;
        case 3:
            off = 35.0f;
            break;
        }
    } else {
        switch (kpaGetLevel()) {
        case 0:
            if (m->currMotionId == 0x25) {
                off = 10.0f;
            } else {
                off = hgt;
            }
            break;
        default:
            off = hgt;
            break;
        }
    }
    rad = 3.1415927f * deg / 180.0f;
    for (i = 0; i < n; i++) {
        s_ = tbl[0] * (f32)sin(rad);
        c = (f32)cos(rad);
        oz = tbl[0] * -c;
        oy = tbl[1];
        md = tbl[2];
        tbl += 3;
        if (md == 0 && !(m->flags & 0x10000)) {
            continue;
        }
        x = m->position.x + s_;
        y = m->position.y + oy;
        z = m->position.z + oz;
        d = off;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &d, &nx, &ny, &nz, x, y, z, 0.0f, 1.0f, 0.0f);
        if (hit) {
            hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            if (y + off >= hy) {
                outA[1] = hy;
                best = hit;
                *outB = 0.0f;
                KHEAD(i) = hit;
            } else {
                *outB = hy - outA[1] - off;
            }
        }
    }
    return best;
#endif
#ifndef NONMATCHING
	char _af_pad[56];
	asm volatile {
		opword 0xFF800890
		opword 0x7C771B78
		opword 0x7C982378
		bl marioGetPtr
		opword 0x80030000
		opword 0x7C7E1B78
		opword 0x5400039D
		opword 0x4182000C
		opword 0x38600000
		opword 0x480002BC
		opword 0xC03E0180
		opword 0x3B200000
		lfs f0, float_0_80420e80(r2)
		opword 0xFC010000
		opword 0x4182000C
		opword 0xC3FE01A0
		opword 0x48000010
		opword 0xC03E01A8
		bl toMovedir
		opword 0xFFE00890
		opword 0xC3B80000
		opword 0x3B600000
		lfs f0, float_neg1_80420e84(r2)
		opword 0x7F7CDB78
		lfs f30, float_1000_80420e74(r2)
		opword 0x7F7ADB78
		opword 0xD0180000
		bl marioGetPtr
		opword 0x8063028C
		opword 0x381C0020
		opword 0x7F43012E
		bl marioGetPtr
		opword 0x3B7B0001
		opword 0x8063028C
		opword 0x381C0078
		opword 0x3B9C0004
		opword 0x2C1B000A
		opword 0x7FC3052E
		opword 0x4180FFD4
		bl kpaGetLevel
		opword 0x801E0000
		opword 0x5464103A
		la r3, g5_headchkofs_s581(r13)
		opword 0x7F43202E
		opword 0x540003DF
		opword 0x837A0000
		opword 0x3B5A0004
		opword 0x40820050
		bl kpaGetLevel
		opword 0x2C030002
		opword 0x41820034
		opword 0x40800014
		opword 0x2C030000
		opword 0x41820018
		opword 0x4080001C
		opword 0x48000060
		opword 0x2C030004
		opword 0x40800058
		opword 0x4800001C
		lfs f29, float_2_80420e88(r2)
		opword 0x4800004C
		lfs f29, float_0_80420e80(r2)
		opword 0x48000044
		lfs f29, float_0_80420e80(r2)
		opword 0x4800003C
		lfs f29, float_35_80420e8c(r2)
		opword 0x48000034
		bl kpaGetLevel
		opword 0x2C030000
		opword 0x41820008
		opword 0x48000020
		opword 0xA01E002E
		opword 0x28000025
		opword 0x4082000C
		lfs f29, float_10_80420e90(r2)
		opword 0x48000010
		opword 0xFFA0E090
		opword 0x48000008
		opword 0xFFA0E090
		lfs f1, float_3p1416_80420e78(r2)
		lis r3, double_to_int_802fe368@ha
		lfs f0, float_180_80420e7c(r2)
		opword 0x3B800000
		opword 0xEC2107F2
		lfd f31, double_to_int_802fe368@l(r3)
		opword 0x3BA00000
		opword 0x3FE04330
		opword 0xEFC10024
		opword 0x48000174
		opword 0xFC20F090
		bl sin
		opword 0x801A0000
		opword 0xFC400818
		stw r31, _af_pad+32(r1)
		opword 0xFC20F090
		opword 0x6C008000
		opword 0x9001002C
		opword 0xC8010028
		opword 0xEC00F828
		fmuls f28, f0, f2
		bl cos
		opword 0x807A0000
		opword 0xFC000818
		opword 0x801A0004
		opword 0x6C638000
		opword 0x809A0008
		opword 0x90610034
		opword 0x6C008000
		opword 0xFC200050
		opword 0x2C040000
		opword 0x93E10030
		opword 0x3B5A000C
		opword 0xC8010030
		opword 0x9001003C
		opword 0xEC40F828
		opword 0x93E10038
		opword 0xC8010038
		opword 0xECA20072
		opword 0xEC60F828
		opword 0x40820010
		opword 0x801E0000
		opword 0x540003DF
		opword 0x418200E4
		opword 0xC03E008C
		opword 0x38810020
		opword 0xC05E0090
		opword 0x38A1001C
		opword 0xEC21E02A
		opword 0xC01E0094
		opword 0xEF82182A
		lfs f4, float_0_80420e80(r2)
		opword 0xEC60282A
		opword 0xD3A10008
		opword 0xFC40E090
		lfs f5, float_1_80420e94(r2)
		opword 0xFCC02090
		opword 0x38C10018
		opword 0x38E10008
		opword 0x39010014
		opword 0x39210010
		opword 0x3941000C
		opword 0x38600000
		bl hitCheckFilter
		mr. r22, r3
		opword 0x4182008C
		lfs f3, float_100_80420e98(r2)
		opword 0x3C004330
		opword 0xC041001C
		lis r3, double_to_int_802fe368@ha
		lfs f1, float_0p5_80420e70(r2)
		opword 0xEC1CE82A
		opword 0x90010030
		opword 0xEC2308BA
		lfd f2, double_to_int_802fe368@l(r3)
		opword 0xFC20081E
		opword 0xD8210038
		opword 0x8001003C
		opword 0x6C008000
		opword 0x90010034
		opword 0xC8210030
		opword 0xEC211028
		opword 0xEC211824
		opword 0xFC000840
		opword 0xD021001C
		opword 0x4C411382
		opword 0x40820028
		opword 0xD0370004
		opword 0x7ED9B378
		lfs f0, float_0_80420e80(r2)
		opword 0xD0180000
		bl marioGetPtr
		opword 0x8063028C
		opword 0x381D0020
		opword 0x7EC3012E
		opword 0x48000014
		opword 0xC0170004
		opword 0xEC010028
		opword 0xEC00E828
		opword 0xD0180000
		opword 0x3BBD0004
		opword 0x3B9C0001
		opword 0x7C1CD800
		opword 0x4180FE8C
		opword 0x7F23CB78
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

HitEntry* kpaSearchFrontUnder(void) {
    return NULL;
}

HitEntry* kpaGetHitobjHead(s32 i) {
    return KHEAD(i);
}

HitEntry* kpaGetHitobjHead2(void) {
    return KPW->head[0];
}

HitEntry* kpaGetHitobjRide(s32 i) {
    return KRIDE(i);
}

HitEntry* kpaChkHitobjRide(void) {
KpaHitWork* w = KPW;
HitEntry* r;
r = w->ride_[0];
if (!r) {
r = w->ride_[1];
if (!r) {
r = w->ride_[2];
if (!r) {
r = w->ride_[3];
if (!r) {
r = w->ride_[4];
if (!r) {
r = w->ride_[5];
if (!r) {
r = w->ride_[6];
if (!r) {
r = w->ride_[7];
if (!r) {
r = w->ride_[8];
if (!r) {
r = w->ride_[9];
if (r) { return r; } else { return r; }
}
}
}
}
}
}
}
}
}
return r;
}

long kpaClearHitobjRide(void) {
    MarioWork* m = marioGetPtr();
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x4C) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x50) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x54) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x58) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x5C) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x60) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x64) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x68) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x6C) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x70) = NULL;
}

HitEntry* kpaGetHitobj(void) {
    MarioWork* m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    return (*(KpaHitWork**)((u8*)m + 0x28C))->obj;
}

HitEntry* kpaGetHitFlame(void) {
    MarioWork* m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    return (*(KpaHitWork**)((u8*)m + 0x28C))->flame;
}

static s32 _ofs0[] = {3, 12, 16, 1, 0, 16, 0, -9, 16, 0};
static s32 _ofs1[] = {4, 25, 74, 0, 50, 65, 1, 0, 67, 0, -25, 62, 0};
static s32 _ofs2[] = {6, 50, 102, 0, 76, 90, 1, 25, 100, 0, 0, 94, 0, -25, 90, 0, -45, 68, 0};
static s32 _ofs3[] = {13, 170, 194, 1, 145, 204, 0, 120, 232, 0, 95, 227, 0, 70, 232, 0, 55, 232, 0,
30, 194, 0, 5, 187, 0, -20, 210, 0, -45, 201, 0, -70, 181, 0, -95, 153, 0, -120, 56, 0};
static s32* kpaHeadChkOfs[] = {_ofs0, _ofs1, _ofs2, _ofs3};
static s32 head_sphere_data_lv1[] = {3, 32, 55, 24, 0, 26, 30, 16, 2, -10, 44, 25, 1};
static s32 head_sphere_data_lv2[] = {3, 45, 75, 34, 0, 36, 30, 16, 2, -15, 59, 36, 1};
static s32 head_sphere_data_lv3[] = {4, 100, 162, 80, 0, 90, 75, 30, 2, 50, 40, 30, 3, -43, 142, 74, 1};
#ifndef NONMATCHING
__declspec(section ".data") static void* jumptable_803ADC44[7] = {
    (char*)kpaSearchGround + 0x258,
    (char*)kpaSearchGround + 0x264,
    (char*)kpaSearchGround + 0x2A4,
    (char*)kpaSearchGround + 0x2E8,
    (char*)kpaSearchGround + 0x318,
    (char*)kpaSearchGround + 0x34C,
    (char*)kpaSearchGround + 0x37C,
};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") u32 g5_headchkofs_s581[4] = {(u32)_ofs0, (u32)_ofs1, (u32)_ofs2, (u32)_ofs3};
#endif
static s32 head_sphere_data_lv0[] = {1, 10, 15, 6, 0};
static s32* head_sphere_data[] = {head_sphere_data_lv0, head_sphere_data_lv1, head_sphere_data_lv2, head_sphere_data_lv3};

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
HitEntry* kpaHitCheck(void) {
#ifdef NONMATCHING
    s32* p;
    s32 j;
    s32 i;
    HitEntry* hit;
    s32 n;
    MarioWork* m;
    HitEntry* best;
    f32 rad, x, y, z, r, sn;

    best = NULL;
    m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    (*(KpaHitWork**)((u8*)m + 0x28C))->obj = NULL;
    kpa_headClear();
    if (kpaFireAttackCheck() == 1) {
        return NULL;
    }
    p = head_sphere_data[kpaGetLevel()];
    n = *p++;
    for (j = 0; j < n; j++) {
        sn = (f32)sin(3.1415927f * m->directionView / 180.0f);
        x = m->position.x + p[0] * sn;
        sn = (f32)cos(3.1415927f * m->directionView / 180.0f);
        z = m->position.z - p[0] * sn;
        y = m->position.y + p[1];
        r = p[2];
        i = p[3];
        p += 4;
        switch (i) {
        case 1:
            if (!(m->flags & 0x10000)) {
                continue;
            }
            break;
        case 2:
            if (m->flags & 0x10000) {
                continue;
            }
            break;
        case 3:
            if (m->flags & 0x30000) {
                continue;
            }
            break;
        }
        hit = hitCheckSphereFilter(NULL, x, y, z, r);
        if ((m->flags & 0x10000) && (hitGetAttr(hit) & 0x80000000) && *(f32*)((u8*)mobjHitObjPtrToPtr(hit) + 0x3C) > y) {
            KHEAD(j) = hit;
        }
        if (hit) {
            if (1) {
            }
            best = hit;
        }
    }
    (*(KpaHitWork**)((u8*)m + 0x28C))->obj = best;
    return best;
#endif
#ifndef NONMATCHING
	char _af_pad[32];
	asm volatile {
		opword 0x3B200000
		bl marioGetPtr
		opword 0x8803003C
		opword 0x7C7E1B78
		opword 0x2C000002
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000208
		opword 0x807E028C
		opword 0x3B400000
		lfs f29, float_1000_80420e74(r2)
		opword 0x7F5BD378
		opword 0x9343001C
		opword 0x7F5CD378
		bl marioGetPtr
		opword 0x8063028C
		opword 0x381C0020
		opword 0x7F43012E
		bl marioGetPtr
		opword 0x3B7B0001
		opword 0x8063028C
		opword 0x381C0078
		opword 0x3B9C0004
		opword 0x2C1B000A
		opword 0x7FA3052E
		opword 0x4180FFD4
		bl kpaFireAttackCheck
		opword 0x2C030001
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001AC
		bl kpaGetLevel
		opword 0x5460103A
		la r3, head_sphere_data(r13)
		opword 0x7F83002E
		lis r3, double_to_int_802fe368@ha
		lfs f31, float_3p1416_80420e78(r2)
		opword 0x3B600000
		opword 0x835C0000
		opword 0x3BA00000
		lfs f29, float_180_80420e7c(r2)
		opword 0x3FE04330
		lfd f30, double_to_int_802fe368@l(r3)
		opword 0x3B9C0004
		opword 0x48000160
		opword 0xC01E01A0
		opword 0xEC1F0032
		opword 0xEC20E824
		bl sin
		opword 0xC01E01A0
		opword 0xFC600818
		opword 0x801C0000
		opword 0xEC1F0032
		stw r31, _af_pad+0(r1)
		opword 0x6C008000
		opword 0xC05E008C
		opword 0x9001000C
		opword 0xEC20E824
		opword 0xC8010008
		opword 0xEC00F028
		opword 0xEF8010FA
		bl cos
		opword 0x801C0000
		opword 0xFC800818
		opword 0x807C0004
		opword 0x6C048000
		opword 0x801C0008
		opword 0x90810014
		opword 0x6C638000
		opword 0x809C000C
		opword 0x6C008000
		opword 0x93E10010
		opword 0x3B9C0010
		opword 0xC03E0094
		opword 0x2C040002
		opword 0xC8010010
		opword 0x9061001C
		opword 0xEC60F028
		opword 0xC05E0090
		opword 0x93E10018
		opword 0xC8010018
		opword 0xEC63093C
		opword 0x90010024
		opword 0xEC20F028
		opword 0x93E10020
		opword 0xC8010020
		fadds f27, f2, f1
		opword 0xEC80F028
		opword 0x41820030
		opword 0x40800010
		opword 0x2C040001
		opword 0x40800014
		opword 0x4800003C
		opword 0x2C040004
		opword 0x40800034
		opword 0x48000024
		opword 0x801E0000
		opword 0x540003DF
		opword 0x41820080
		opword 0x48000020
		opword 0x801E0000
		opword 0x540003DF
		opword 0x40820070
		opword 0x48000010
		opword 0x801E0000
		opword 0x5400039F
		opword 0x40820060
		opword 0xFC20E090
		opword 0x38600000
		opword 0xFC40D890
		bl hitCheckSphereFilter
		opword 0x801E0000
		mr r24, r3
		opword 0x540003DF
		opword 0x41820034
		bl hitGetAttr
		opword 0x54600001
		opword 0x41820028
		opword 0x7F03C378
		bl mobjHitObjPtrToPtr
		opword 0xC003003C
		opword 0xFC00D840
		opword 0x40810014
		bl marioGetPtr
		opword 0x8063028C
		opword 0x381D0020
		opword 0x7F03012E
		opword 0x28180000
		opword 0x41820008
		opword 0x7F19C378
		opword 0x3BBD0004
		opword 0x3B7B0001
		opword 0x7C1BD000
		opword 0x4180FEA0
		opword 0x809E028C
		opword 0x7F23CB78
		opword 0x9324001C
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

BOOL kpaFlameHitFilter(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj = mobjHitObjPtrToPtr(entry);
#ifdef NONMATCHING
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock")) {
#endif
#ifndef NONMATCHING
    if (!strcmp(mobj->animName, EXT_LIT((char*)str_802FE344, "MOBJ_HiddenHatenaBlock"))) {
#endif
        return FALSE;
    }
#ifdef NONMATCHING
    if (!strcmp(mobj->animName, "MOBJ_Block")) {
#endif
#ifndef NONMATCHING
    if (!strcmp(mobj->animName, EXT_LIT((char*)str_802FE35C, "MOBJ_Block"))) {
#endif
        return FALSE;
    }
    return TRUE;
}


#ifdef NONMATCHING
static f32 kpaHalf(f32 v) {
    return EXT_LIT(float_0p5_80420e70, 0.5f) * v;
}
#endif


HitEntry* kpaFlameHitCheck(f32 x, f32 y, f32 z, f32 r) {
    marioGetPtr();
    return hitCheckSphereFilter(kpaFlameHitFilter, x, y, z, r);
}



#pragma force_active on
#ifndef NONMATCHING
#pragma explicit_zero_data on
#endif
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80415B84_sdata[1] = {0};
#ifndef NONMATCHING
#pragma explicit_zero_data reset
#endif
#pragma force_active reset


#ifdef NONMATCHING
s32 kpaEnemyFireHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
    Mtx m3;
    Mtx m1;
    Mtx m2;
    Mtx m4;
    Vec out;
    Vec b;
    Vec diff;
    Vec a;
    u8* efp;
    u8* e;
    f32 half;
    f32 r;
    f32 s;
    s32 i;
    efp = getKoopaFireEfp();
    camGetPtr(4);
    {
        Vec zero0 = {0.0f, 0.0f, 0.0f};
        a = zero0;
    }
    a.x = x;
    a.y = EXT_LIT(float_0p5_80420e70, 0.5f) * h + y;
    a.z = z;
    b = a;
    if (!efp) {
        return 0;
    }
    e = *(u8**)(efp + 0xC);
    s = MF(e, 0x40);
    PSMTXTrans(m1, MF(e, 4), MF(e, 8), MF(e, 0xC));
    PSMTXRotRad(m2, 'y', 0.017453292f * (MF(e, 0x48) - MF(camGetPtr(4), 0x114)));
    if (MF(e, 0x48) > 90.0f && MF(e, 0x48) < 270.0f) {
        PSMTXScale(m3, MF(e, 0x40), MF(e, 0x40), -MF(e, 0x40));
    } else {
        PSMTXScale(m3, MF(e, 0x40), MF(e, 0x40), MF(e, 0x40));
    }
    PSMTXConcat(m1, m2, m1);
    PSMTXConcat(m1, m3, m4);
    half = kpaHalf(w);
    e += 0x50;
    for (i = 1; i < *(s32*)(efp + 8); i++, e += 0x50) {
        if (*(s32*)(e + 0x44) == 0) {
            r = 7.0f * MF(e, 0x40);
            PSMTXTrans(m1, MF(e, 4), MF(e, 8), MF(e, 0xC));
            PSMTXScale(m3, r, r, r);
            PSMTXConcat(m1, m3, m1);
            PSMTXConcat(m4, m1, m1);
            {
                Vec zero = {0.0f, 0.0f, 0.0f};
                PSMTXMultVec(m1, &zero, &out);
            }
            PSVECSubtract(&b, &out, &diff);
            if (PSVECMag(&diff) < r * s + half) {
                return 1;
            }
        }
    }
    return 0;
}
#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fe320[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fe32c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fe338[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const char str_802FE344[] = "MOBJ_HiddenHatenaBlock\0";
__declspec(section ".rodata") const char str_802FE35C[] = "MOBJ_Block\0";
__declspec(section ".rodata") const f64 double_to_int_802fe368 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_0p6_802fe370 = 0.6000000238418579;
__declspec(section ".rodata") const f64 double_0p5_802fe378 = 0.5;
__declspec(section ".rodata") const f64 double_3_802fe380 = 3.0;
__declspec(section ".rodata") const f64 double_0_802fe388 = 0.0;
__declspec(section ".sdata2") const f32 float_0p5_80420e70 = 0.5f;
__declspec(section ".sdata2") const f32 float_1000_80420e74 = 1000.0f;
__declspec(section ".sdata2") const f32 float_3p1416_80420e78 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_80420e7c = 180.0f;
__declspec(section ".sdata2") const f32 float_0_80420e80 = 0.0f;
__declspec(section ".sdata2") const f32 float_neg1_80420e84 = -1.0f;
__declspec(section ".sdata2") const f32 float_2_80420e88 = 2.0f;
__declspec(section ".sdata2") const f32 float_35_80420e8c = 35.0f;
__declspec(section ".sdata2") const f32 float_10_80420e90 = 10.0f;
__declspec(section ".sdata2") const f32 float_1_80420e94 = 1.0f;
__declspec(section ".sdata2") const f32 float_100_80420e98 = 100.0f;
__declspec(section ".sdata2") const f32 float_0p01_80420e9c = 0.01f;
__declspec(section ".sdata2") const f32 float_0p25_80420ea0 = 0.25f;
__declspec(section ".sdata2") const f32 float_0p6_80420ea4 = 0.6f;
__declspec(section ".sdata2") const f32 float_3_80420ea8 = 3.0f;
__declspec(section ".sdata2") const f32 float_0p05_80420eac = 0.05f;
__declspec(section ".sdata2") const f32 float_50_80420eb0 = 50.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80420eb4 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_90_80420eb8 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_80420ebc = 270.0f;
__declspec(section ".sdata2") const f32 float_7_80420ec0 = 7.0f;
__declspec(section ".sdata2") const u32 gap_09_80420EC4_sdata2 = 0x00000000;
#endif
