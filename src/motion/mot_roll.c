#pragma defer_codegen on
#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mariost.h"
#include "memory.h"
#include "pmario_sound.h"
#include <string.h>
#ifndef NONMATCHING
#include "driver/camdrv.h"
__declspec(section ".rodata") extern const f32 vec3_802c5d40[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d4c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d58[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d64[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d70[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d7c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d88[3];
__declspec(section ".rodata") extern const f32 vec3_802c5d94[3];
__declspec(section ".rodata") extern const f32 vec3_802c5da0[3];
__declspec(section ".rodata") extern const u32 gap_04_802C5DAC_rodata;
__declspec(section ".rodata") extern const f64 double_0p5_802c5db0;
__declspec(section ".rodata") extern const f64 double_3_802c5db8;
__declspec(section ".rodata") extern const f64 double_0_802c5dc0;
__declspec(section ".rodata") extern const f64 double_45_802c5dc8;
__declspec(section ".rodata") extern const f64 double_to_int_802c5dd0;
__declspec(section ".rodata") extern const char str_802C5DD8[];
__declspec(section ".rodata") extern const char str_802C5DE0[];
__declspec(section ".rodata") extern const char str_802C5DE8[];
__declspec(section ".rodata") extern const char str_802C5DF0[];
__declspec(section ".rodata") extern const char str_802C5DF8[];
__declspec(section ".sdata2") extern const f32 float_100_8041acb8;
__declspec(section ".sdata2") extern const f32 float_0_8041acbc;
__declspec(section ".sdata2") extern const f32 float_0p5_8041acc0;
__declspec(section ".sdata2") extern const f32 float_3p1416_8041acc4;
__declspec(section ".sdata2") extern const f32 float_180_8041acc8;
__declspec(section ".sdata2") extern const f32 float_6_8041accc;
__declspec(section ".sdata2") extern const f32 float_5_8041acd0;
__declspec(section ".sdata2") extern const f32 float_neg4_8041acd4;
__declspec(section ".sdata2") extern const f32 float_90_8041acd8;
__declspec(section ".sdata2") extern const f32 float_270_8041acdc;
__declspec(section ".sdata2") extern const f32 float_360_8041ace0;
__declspec(section ".sdata2") extern const f32 float_10_8041ace4;
__declspec(section ".sdata2") extern const f32 float_135_8041ace8;
__declspec(section ".sdata2") extern const f32 float_1p2_8041acec;
__declspec(section ".sdata2") extern const f32 float_neg10_8041acf0;
__declspec(section ".sdata2") extern const f32 float_4_8041acf4;
__declspec(section ".sdata2") extern const f32 float_neg0p42_8041acf8;
__declspec(section ".sdata2") extern const f32 float_0p04_8041acfc;
__declspec(section ".sdata2") extern const f32 float_neg0p01_8041ad00;
__declspec(section ".sdata2") extern const char str_8041AD04[];
__declspec(section ".sdata2") extern const f32 float_14p8_8041ad0c;
__declspec(section ".sdata2") extern const f32 float_neg6_8041ad10;
__declspec(section ".sdata2") extern const f32 float_1_8041ad14;
__declspec(section ".sdata2") extern const f32 float_0p4_8041ad18;
__declspec(section ".sdata2") extern const f32 float_0p01_8041ad1c;
__declspec(section ".sdata2") extern const f32 float_2_8041ad20;
__declspec(section ".sdata2") extern const f32 float_0p1_8041ad24;
__declspec(section ".sdata2") extern const f32 float_3_8041ad28;
__declspec(section ".sdata2") extern const f32 float_neg3_8041ad2c;
__declspec(section ".sdata2") extern const f32 float_0p004_8041ad30;
__declspec(section ".sdata2") extern const char str_8041AD34[];
__declspec(section ".sdata2") extern const f32 float_1p4_8041ad3c;
__declspec(section ".sdata2") extern const f32 float_1p45_8041ad40;
__declspec(section ".sdata2") extern const f32 float_0p35_8041ad44;
__declspec(section ".sdata2") extern const f32 float_1p05_8041ad48;
__declspec(section ".sdata2") extern const f32 float_0p2_8041ad4c;
__declspec(section ".sdata2") extern const f32 float_40_8041ad50;
__declspec(section ".sdata2") extern const f32 float_2p85_8041ad54;
__declspec(section ".sdata2") extern const f32 float_neg0p14_8041ad58;
__declspec(section ".sdata2") extern const f32 float_0p08_8041ad5c;
__declspec(section ".sdata2") extern const f32 float_neg0p02_8041ad60;
__declspec(section ".sdata2") extern const f32 float_neg0p03_8041ad64;
__declspec(section ".sdata2") extern const f32 float_neg0p002_8041ad68;
__declspec(section ".sdata2") extern const f32 float_0p05_8041ad6c;
__declspec(section ".sdata2") extern const f32 float_neg100_8041ad70;
__declspec(section ".sdata2") extern const f32 float_neg0p05_8041ad74;
__declspec(section ".sdata2") extern const f32 float_0p6_8041ad78;
__declspec(section ".sdata2") extern const f32 float_6p4_8041ad7c;
__declspec(section ".sdata2") extern const f32 float_0p025_8041ad80;
__declspec(section ".sdata2") extern const f32 float_neg1_8041ad84;
__declspec(section ".sdata2") extern const f32 float_neg180_8041ad88;
__declspec(section ".sdata2") extern const f32 float_200_8041ad8c;
__declspec(section ".sdata2") extern const f32 float_170_8041ad90;
__declspec(section ".sdata2") extern const u32 gap_09_8041AD94_sdata2;
#define EXT_LIT(sym, val) (sym)

#endif

f32 revise360(f32);
f32 distABf(f32, f32, f32, f32);
f32 angleABf(f32, f32, f32, f32);
f32 toMovedir(f32);
void sincosf(f32* s, f32* c, f32 deg);
double sin(double);
double cos(double);
BOOL marioChkBero(HitEntry* hit);
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
HitEntry* marioChkLandon(f32* outY, f32 y);
f32 marioGetFallSpd(void);
void marioLandOn(void);
void marioClearJumpPara(void);
void marioChgMotSub(s32 a, s32 b);
void marioGetRubInit(void);
void allPartyRideShip(void);
void allPartyRideOff(void);
void allPartyForceRideOn(void);
s32 marioSlitChkWallAround(void);
void marioUpdateCamCollision(Vec* pos);
void camFollowYOff(void);
void camFollowYOn(void);
void marioOfsRotReset(void);
void marioSetSpec(void);
void marioAdjustMoveDir(void);
extern int __float_nan[];

#define PF(p, o) (*(f32*)((u8*)(p) + (o)))
#define PI(p, o) (*(s32*)((u8*)(p) + (o)))
#define MF(o) (*(f32*)((u8*)mario + (o)))
#define MI(o) (*(s32*)((u8*)mario + (o)))
#define MH(o) (*(s16*)((u8*)mario + (o)))
#define MV(o) (*(Vec*)((u8*)mario + (o)))
#define MB(o) (*(s8*)((u8*)mario + (o)))
#define MU(o) (*(u16*)((u8*)mario + (o)))
#define CAMF() (*(u16*)camGetPtr(8))

typedef struct RollWork {
    f32 x;
    f32 z;
    s32 state;
    s32 scaleState;
    s32 pad;
} RollWork;

#define RW() ((RollWork*)marioGetPtr()->motStruct)


#ifndef NONMATCHING
static u8 gap_08_8041888C_sbss[4];  // .sbss pad after roll_grx
#endif
f32 roll_grx;
f32 roll_grz;
s32 roll_flyout_flag2;

#ifdef NONMATCHING
f32 rollData[] = {3.0f, -0.05f, -0.5f, 0.5f, 7.0f, 180.0f, 140.0f, 10.0f, 1.2f, 2.0f, 0.8f};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") f32 rollData[] = {3.0f, -0.05f, -0.5f, 0.5f, 7.0f, 180.0f, 140.0f, 10.0f, 1.2f, 2.0f, 0.8f};
#endif

#ifdef NONMATCHING
static inline s32 roll_fpclassifyf(f32 x) {
    switch (*(s32*)&x & 0x7F800000) {
    case 0x7F800000:
        if (*(s32*)&x & 0x007FFFFF) {
            return 1;
        } else {
            return 2;
        }
        break;
    case 0:
        if (*(s32*)&x & 0x007FFFFF) {
            return 5;
        } else {
            return 3;
        }
        break;
    default:
        return 4;
    }
}
#endif

#ifdef NONMATCHING
static inline f32 roll_sqrtf(f32 x) {
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x < 0.0) {
        return *(f32*)__float_nan;
    } else if (roll_fpclassifyf(x) == 1) {
        return *(f32*)__float_nan;
    }
    return x;
}
#endif

static inline f32 trunc10(f32 x) {
    s32 i = (s32)(10.0f * x);
    f32 f = (f32)i;
#ifdef NONMATCHING
    return f / 10.0f;
#endif
#ifndef NONMATCHING
    return f / EXT_LIT(float_10_8041ace4, 10.0f);
#endif
}

static inline s32 angOutT(f32 center, f32 half, f32 x) {
    s32 w = 0;
    s32 r = w;
    f32 c = trunc10(center);
    f32 lo;
    f32 hi;
    lo = c - half;
#ifdef NONMATCHING
    if (lo < 0.0f) {
#endif
#ifndef NONMATCHING
    if (lo < EXT_LIT(float_0_8041acbc, 0.0f)) {
#endif
        w = 1;
#ifdef NONMATCHING
        lo += 360.0f;
#endif
#ifndef NONMATCHING
        lo += EXT_LIT(float_360_8041ace0, 360.0f);
#endif
    }
    hi = c + half;
#ifdef NONMATCHING
    if (hi > 360.0f) {
#endif
#ifndef NONMATCHING
    if (hi > EXT_LIT(float_360_8041ace0, 360.0f)) {
#endif
        hi -= 360.0f;
        w = 2;
    }
    if (w == 1) {
        if (hi < x && x < lo) {
            r = 1;
        }
    } else if (w == 2) {
        if (hi < x && x < lo) {
            r = 1;
        }
    } else if (w == 0) {
        if (x < lo || hi < x) {
            r = 1;
        }
    }
    return r;
}

static inline s32 angOut(f32 center, f32 half, f32 x) {
    return angOutT(center, half, x);
}

/* repurposed unused inline: angOut on the mario stick angle, with everything read inside */
#ifdef NONMATCHING
static inline s32 makeVec(f32 half) {
    s32 w = 0;
    s32 r = w;
    MarioWork* m = marioGetPtr();
    f32 c = trunc10(m->moveDirection);
    f32 x = angleABf(0.0f, 0.0f, (f32)(s32)*((s8*)m + 0x24e), (f32)(s32)*((s8*)m + 0x24f));
    f32 lo;
    f32 hi;
    lo = c - half;
    if (lo < 0.0f) {
        w = 1;
        lo += 360.0f;
    }
    hi = c + half;
    if (hi > 360.0f) {
        hi -= 360.0f;
        w = 2;
    }
    if (w == 1) {
        if (hi < x && x < lo) {
            r = 1;
        }
    } else if (w == 2) {
        if (hi < x && x < lo) {
            r = 1;
        }
    } else if (w == 0) {
        if (x < lo || hi < x) {
            r = 1;
        }
    }
    return r;
}
#endif

#ifdef NONMATCHING
#define DISPDIR_BODY(a, b, m2)                                                                    \
    if (angOut(b, 135.0f, a) == 1) {                                                              \
        b = revise360(180.0f + b);                                                                \
    }                                                                                             \
    {                                                                                             \
        f32 ty_ = trunc10((m2)->targetYaw); f32 dd = revise360(trunc10(b) - ty_);  \
        s32 sgn = (dd < 180.0f) ? 0 : 1;                                                          \
        if (sgn == 0) {                                                                           \
            if (__fabsf(b - a) > 90.0f) {                                                            \
                if (a > b) {                                                                      \
                    b += 360.0f;                                                                  \
                }                                                                                 \
            }                                                                                     \
        } else {                                                                                  \
            if (__fabsf(b - a) > 90.0f) {                                                            \
                if (a < b) {                                                                      \
                    a += 360.0f;                                                                  \
                }                                                                                 \
            }                                                                                     \
        }                                                                                         \
    }                                                                                             \
    if (angOut(b, 90.0f, a) == 0) {                                                               \
        if (__fabsf(b - a) > 180.0f) {                                                               \
            if (b > a) {                                                                          \
                b -= 360.0f;                                                                      \
            } else {                                                                              \
                a -= 360.0f;                                                                      \
            }                                                                                     \
        }                                                                                         \
    }                                                                                             \
    b = 1.2f * (a - b) + b;                                                                       \
    b = revise360(b);                                                                             \
    {                                                                                             \
        f32 md = toMovedir(MF(0x1a8));                                                            \
        if (MB(0x43)) {                                                                           \
            md = revise360(180.0f + md);                                                          \
        }                                                                                         \
        if (angOut(b, 135.0f, md) == 1) {                                                         \
            MB(0x43) = (MB(0x43) + 1) & 1;                                                        \
        }                                                                                         \
    }                                                                                             \
    { f32 t_ = 270.0f + MF(0x198) - b; MF(0x1a8) = revise360(t_ + (MB(0x43) ? -180.0f : 0.0f)); } \
    if (MF(0x1a8) >= 200.0f) {                                                                    \
        MF(0x1a8) = revise360(270.0f + MF(0x198) - b + (MB(0x43) ? -180.0f : 0.0f));              \
    }                                                                                             \
    if (MF(0x1a8) < 170.0f) {                                                                     \
        MF(0x1a8) = revise360(270.0f + MF(0x198) - b + (MB(0x43) ? -180.0f : 0.0f));              \
    }
#endif
#ifndef NONMATCHING
#define DISPDIR_BODY(a, b, m2)                                                                    \
    if (angOut(b, (135.0f), a) == 1) {                                                              \
        b = revise360(EXT_LIT(float_180_8041acc8, 180.0f) + b);                                                                \
    }                                                                                             \
    {                                                                                             \
        f32 ty_ = trunc10((m2)->targetYaw); f32 dd = revise360(trunc10(b) - ty_);  \
        s32 sgn = (dd < EXT_LIT(float_180_8041acc8, 180.0f)) ? 0 : 1;                                                          \
        if (sgn == 0) {                                                                           \
            if (__fabsf(b - a) > EXT_LIT(float_90_8041acd8, 90.0f)) {                                                            \
                if (a > b) {                                                                      \
                    b += EXT_LIT(float_360_8041ace0, 360.0f);                                                                  \
                }                                                                                 \
            }                                                                                     \
        } else {                                                                                  \
            if (__fabsf(b - a) > EXT_LIT(float_90_8041acd8, 90.0f)) {                                                            \
                if (a < b) {                                                                      \
                    a += EXT_LIT(float_360_8041ace0, 360.0f);                                                                  \
                }                                                                                 \
            }                                                                                     \
        }                                                                                         \
    }                                                                                             \
    if (angOut(b, (90.0f), a) == 0) {                                                               \
        if (__fabsf(b - a) > EXT_LIT(float_180_8041acc8, 180.0f)) {                                                               \
            if (b > a) {                                                                          \
                b -= EXT_LIT(float_360_8041ace0, 360.0f);                                                                      \
            } else {                                                                              \
                a -= EXT_LIT(float_360_8041ace0, 360.0f);                                                                      \
            }                                                                                     \
        }                                                                                         \
    }                                                                                             \
    b = (1.2f) * (a - b) + b;                                                                       \
    b = revise360(b);                                                                             \
    {                                                                                             \
        f32 md = toMovedir(MF(0x1a8));                                                            \
        if (MB(0x43)) {                                                                           \
            md = revise360(EXT_LIT(float_180_8041acc8, 180.0f) + md);                                                          \
        }                                                                                         \
        if (angOut(b, EXT_LIT(float_135_8041ace8, 135.0f), md) == 1) {                                                         \
            MB(0x43) = (MB(0x43) + 1) & 1;                                                        \
        }                                                                                         \
    }                                                                                             \
    { f32 t_ = 270.0f + MF(0x198) - b; MF(0x1a8) = revise360(t_ + (MB(0x43) ? -180.0f : 0.0f)); } \
    if (MF(0x1a8) >= (200.0f)) {                                                                    \
        MF(0x1a8) = revise360(EXT_LIT(float_270_8041acdc, 270.0f) + MF(0x198) - b + (MB(0x43) ? EXT_LIT(float_neg180_8041ad88, -180.0f) : EXT_LIT(float_0_8041acbc, 0.0f)));              \
    }                                                                                             \
    if (MF(0x1a8) < (170.0f)) {                                                                     \
        MF(0x1a8) = revise360(EXT_LIT(float_270_8041acdc, 270.0f) + MF(0x198) - b + (MB(0x43) ? EXT_LIT(float_neg180_8041ad88, -180.0f) : EXT_LIT(float_0_8041acbc, 0.0f)));              \
    }
#endif

void roll_upstairs(void);
static inline void marioRollCan(void);


#pragma inline_max_size(20000)
#pragma inline_max_total_size(200000)


void marioRollFixOn(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == 0x16) {
        MI(0x2a4) |= 0x200;
    }
}

s32 unk_8009fcbc(void) {
    MarioWork* mario = marioGetPtr();
    if (MI(0x2a4) & 0x200) {
        return 1;
    }
    if ((mario->flags & 0x8000000) != 0) {
        return 1;
    }
    return !mario->hitobjStandOn ? 1 : (marioSlitChkWallAround() != 0);
}

s32 marioRollKeyDisable(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId != 0x16) {
        return 1;
    }
    {
        s32 sub = MI(0x44);
        if (sub >= 0 && sub <= 1) {
            return 0;
        }
        if (sub >= 0x14 && sub <= 0x16) {
            return 0;
        }
    }
    return 1;
}

void setRollEvtFlag(void) {
    MarioWork* mario = marioGetPtr();
    MI(0x2a4) |= 0x100;
}

void clrRollEvtFlag(void) {
    MarioWork* mario = marioGetPtr();
    MI(0x2a4) &= ~0x100;
}

s32 getRollEvtFlag(void) {
    s32 r = 0;
    MarioWork* mario = marioGetPtr();
    if (mario->flags & 0x1000000) {
        if (MI(0x2a4) & 0x100) {
            r = 1;
        }
    }
    return r;
}

#ifndef NONMATCHING
void *memset(void *dest, int ch, size_t count);
int strcmp(const char *s1, const char *s2);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void marioResetRollSpd(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == 0x16) {
        if (marioGetPtr()->motStruct) {
            f32 a = 0.0f;
            f32 b;
            RW()->x = a;
            b = 0.0f;
            RW()->z = b;
        }
        mario->baseSpeed = 0.0f;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		bl marioGetPtr
		mr r31, r3
		opword 0xA003002E
		opword 0x28000016
		opword 0x4082003C
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x41820024
		lfs f30, float_0_8041acbc(r2)
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041acbc(r2)
		opword 0xD3C30000
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3E30004
		lfs f0, float_0_8041acbc(r2)
		opword 0xD01F0180
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void marioForceRollAnime(void) {
    MarioWork* mario = marioGetPtr();
    marioPaperOff();
    if (mario) {
    }
    marioChgPaper(0);
#ifdef NONMATCHING
    marioPaperOn("p_roll");
    marioChgPose("M_I_U");
    marioChgPaper("PM_R_1B");
#endif
#ifndef NONMATCHING
    marioPaperOn(EXT_LIT((char*)str_802C5DD8, "p_roll"));
    marioChgPose(EXT_LIT((char*)str_8041AD04, "M_I_U"));
    marioChgPaper(EXT_LIT((char*)str_802C5DE8, "PM_R_1B"));
#endif
    mario->dispFlags |= 8;
    mario->dispFlags |= 0x100;
}

s32 unk_8009f9c8(void) {
    s32 ret = 0;
    MarioWork* mario = marioGetPtr();
    if (!(mario->flags & 0x1000000)) {
        return 0;
    }
    if (MI(0x2a4) & 0x200) {
        return 0;
    }
    {
        s32 r;
        MarioWork* m = marioGetPtr();
        if (*(s32*)((u8*)m + 0x2a4) & 0x200) {
            r = 1;
        } else if (m->flags & 0x8000000) {
            r = 1;
        } else if (!m->hitobjStandOn) {
            r = 1;
        } else if (marioSlitChkWallAround()) {
            r = 1;
        } else {
            r = 0;
        }
        if (!r) {
            ret = 1;
            mario->currSubMotionId = 0x14;
            CAMF() |= 0x200;
        }
    }
    return ret;
}


s32 marioRollCancel(void) {
    MarioWork* mario = marioGetPtr();
    if (!(mario->flags & 0x1000000)) {
        return 0;
    }
    if (MI(0x2a4) & 0x200) {
        return 0;
    }
    mario->currSubMotionId = 0x14;
    CAMF() |= 0x200;
    return 1;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void mot_roll_post(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    MarioWork* m = marioGetPtr();
    if (*(u32*)((u8*)m + 0x2a8) != (u32)-1) {
        psndSFXOff(*(s32*)((u8*)m + 0x2a8));
        *(s32*)((u8*)m + 0x2a8) = -1;
    }
    m = marioGetPtr();
    m->camShiftTargetZ = 0.0f;
    m->camShiftRate.z = 0.004f;
    {
        f32 d = revise360(mario->directionView - mario->targetYaw);
        do { if (d >= 180.0f) { mario->displayDirection = 0.0f; mario->displayDirectionTarget = 0.0f; mario->moveDirection = 270.0f; mario->directionView = 270.0f; } else { mario->displayDirection = 180.0f; mario->displayDirectionTarget = 180.0f; mario->moveDirection = 90.0f; mario->directionView = 90.0f; } } while (0);
    }
    marioSetSpec();
    mario->field_0x8 = 0;
    mario->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
    mario->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
    mario->rot = (Vec){0.0f, 0.0f, 0.0f};
    mario->dispFlags &= ~0x100;
    mario->dispFlags &= ~8;
    mario->flags &= ~0x1000000;
    marioPaperOff();
    marioAdjustMoveDir();
    marioChgPose("M_S_1");
    if (marioGetPtr()->motStruct) {
        __memFree(0, marioGetPtr()->motStruct);
        mario = 0;
        marioGetPtr()->motStruct = (void*)mario;
    }
    allPartyRideOff();
#endif
#ifndef NONMATCHING
	asm {
		lis r3, vec3_802c5d40@ha
	}
	asm volatile {
		addi r29, r3, vec3_802c5d40@l
		bl marioGetPtr
		opword 0x7C7F1B78
		bl marioGetPtr
		opword 0x7C7E1B78
		opword 0x806302A8
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820010
		bl psndSFXOff
		opword 0x3800FFFF
		opword 0x901E02A8
		bl marioGetPtr
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_0p004_8041ad30(r2)
		opword 0xD0230148
		opword 0xD0030158
		opword 0xC03F01A0
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		lfs f2, float_180_8041acc8(r2)
		opword 0xFC011040
		opword 0x4C411382
		opword 0x40820020
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_270_8041acdc(r2)
		opword 0xD03F01A8
		opword 0xD03F01AC
		opword 0xD01F019C
		opword 0xD01F01A0
		opword 0x48000018
		opword 0xD05F01A8
		lfs f0, float_90_8041acd8(r2)
		opword 0xD05F01AC
		opword 0xD01F019C
		opword 0xD01F01A0
		bl marioSetSpec
		opword 0x38000000
		opword 0x901F0008
		opword 0x807D000C
		opword 0x801D0010
		opword 0x907F00B0
		opword 0x901F00B4
		opword 0x801D0014
		opword 0x901F00B8
		opword 0x807D0018
		opword 0x801D001C
		opword 0x907F0098
		opword 0x901F009C
		opword 0x801D0020
		opword 0x901F00A0
		opword 0x807D0024
		opword 0x801D0028
		opword 0x907F00BC
		opword 0x901F00C0
		opword 0x801D002C
		opword 0x901F00C4
		opword 0x801F0004
		opword 0x5400062C
		opword 0x901F0004
		opword 0x801F0004
		opword 0x54000776
		opword 0x901F0004
		opword 0x801F0000
		opword 0x5400020C
		opword 0x901F0000
		bl marioPaperOff
		bl marioAdjustMoveDir
		la r3, str_8041AD34(r2)
		bl marioChgPose
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x41820024
		bl marioGetPtr
		opword 0x7C641B78
		opword 0x38600000
		opword 0x80840288
		bl __memFree
		opword 0x3BE00000
		bl marioGetPtr
		opword 0x93E30288
		bl allPartyRideOff
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void marioRollForceCancel(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == 0x16) {
        MarioWork* m = marioGetPtr();
        if (*(u32*)((u8*)m + 0x2a8) != (u32)-1) {
            psndSFXOff(*(s32*)((u8*)m + 0x2a8));
            *(s32*)((u8*)m + 0x2a8) = -1;
        }
        m = marioGetPtr();
        m->camShiftTargetZ = 0.0f;
        m->camShiftRate.z = 0.004f;
        {
            f32 d = revise360(mario->directionView - mario->targetYaw);
            if (d >= 180.0f) {
                mario->displayDirection = 0.0f;
                mario->displayDirectionTarget = 0.0f;
                mario->moveDirection = 270.0f;
                do { mario->directionView = 270.0f; } while (0);
            } else {
                mario->displayDirection = 180.0f;
                mario->displayDirectionTarget = 180.0f;
                mario->moveDirection = 90.0f;
                mario->directionView = 90.0f;
            }
        }
        marioSetSpec();
        mario->field_0x8 = 0;
        mario->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
        mario->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
        mario->rot = (Vec){0.0f, 0.0f, 0.0f};
        mario->dispFlags &= ~0x100;
        mario->dispFlags &= ~8;
        mario->flags &= ~0x1000000;
        marioPaperOff();
        marioAdjustMoveDir();
        marioChgPose("M_S_1");
        if (marioGetPtr()->motStruct) {
            __memFree(0, marioGetPtr()->motStruct);
            mario = 0;
            marioGetPtr()->motStruct = (void*)mario;
        }
        allPartyRideOff();
        marioChgMotSub(0, 0);
    }
#endif
#ifndef NONMATCHING
	asm {
		lis r3, vec3_802c5d40@ha
	}
	asm volatile {
		addi r29, r3, vec3_802c5d40@l
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0xA003002E
		opword 0x28000016
		opword 0x40820154
		bl marioGetPtr
		opword 0x7C7E1B78
		opword 0x806302A8
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820010
		bl psndSFXOff
		opword 0x3800FFFF
		opword 0x901E02A8
		bl marioGetPtr
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_0p004_8041ad30(r2)
		opword 0xD0230148
		opword 0xD0030158
		opword 0xC03F01A0
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		lfs f2, float_180_8041acc8(r2)
		opword 0xFC011040
		opword 0x4C411382
		opword 0x40820020
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_270_8041acdc(r2)
		opword 0xD03F01A8
		opword 0xD03F01AC
		opword 0xD01F019C
		opword 0xD01F01A0
		opword 0x48000018
		opword 0xD05F01A8
		lfs f0, float_90_8041acd8(r2)
		opword 0xD05F01AC
		opword 0xD01F019C
		opword 0xD01F01A0
		bl marioSetSpec
		opword 0x38000000
		opword 0x901F0008
		opword 0x807D0030
		opword 0x801D0034
		opword 0x907F00B0
		opword 0x901F00B4
		opword 0x801D0038
		opword 0x901F00B8
		opword 0x807D003C
		opword 0x801D0040
		opword 0x907F0098
		opword 0x901F009C
		opword 0x801D0044
		opword 0x901F00A0
		opword 0x807D0048
		opword 0x801D004C
		opword 0x907F00BC
		opword 0x901F00C0
		opword 0x801D0050
		opword 0x901F00C4
		opword 0x801F0004
		opword 0x5400062C
		opword 0x901F0004
		opword 0x801F0004
		opword 0x54000776
		opword 0x901F0004
		opword 0x801F0000
		opword 0x5400020C
		opword 0x901F0000
		bl marioPaperOff
		bl marioAdjustMoveDir
		la r3, str_8041AD34(r2)
		bl marioChgPose
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x41820024
		bl marioGetPtr
		opword 0x7C641B78
		opword 0x38600000
		opword 0x80840288
		bl __memFree
		opword 0x3BE00000
		bl marioGetPtr
		opword 0x93E30288
		bl allPartyRideOff
		opword 0x38600000
		opword 0x38800000
		bl marioChgMotSub
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void marioSetRollDispDir(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    f32 b, a;
    MarioWork* m2;
    a = mario->directionView;
    b = mario->moveDirection;
    m2 = marioGetPtr();
    DISPDIR_BODY(a, b, m2)
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xDBE10040
		opword 0xF3E10048
		opword 0xDBC10030
		opword 0xF3C10038
		opword 0x93E1002C
		opword 0x93C10028
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0xC3C301A0
		opword 0xC3E3019C
		bl marioGetPtr
		lfs f4, float_10_8041ace4(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5dd0@ha
		opword 0x90010010
		opword 0xEC0407F2
		lfd f3, double_to_int_802c5dd0@l(r4)
		lfs f1, float_135_8041ace8(r2)
		opword 0x38A00000
		opword 0x7C7E1B78
		opword 0xFC40001E
		lfs f0, float_0_8041acbc(r2)
		opword 0x7CA32B78
		opword 0xD8410008
		opword 0x8001000C
		opword 0x6C008000
		opword 0x90010014
		opword 0xC8410010
		opword 0xEC421828
		opword 0xEC622024
		opword 0xEC430828
		opword 0xFC020040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38A00001
		opword 0xEC42002A
		lfs f1, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC23082A
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC210028
		opword 0x38A00002
		opword 0x2C050001
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800050
		opword 0xFC1E1040
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C050002
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800030
		opword 0xFC1E1040
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C050000
		opword 0x40820018
		opword 0xFC1E1040
		opword 0x4180000C
		opword 0xFC01F040
		opword 0x40800008
		opword 0x38600001
		opword 0x2C030001
		opword 0x40820014
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC20F82A
		bl revise360
		opword 0xFFE00890
		lfs f3, float_10_8041ace4(r2)
		opword 0x3C004330
		opword 0xC03E0198
		lis r3, double_to_int_802c5dd0@ha
		opword 0xEC0307F2
		opword 0x90010008
		opword 0xEC230072
		lfd f2, double_to_int_802c5dd0@l(r3)
		opword 0x90010020
		opword 0xFC00001E
		opword 0xFC20081E
		opword 0xD8010018
		opword 0xD8210010
		opword 0x8001001C
		opword 0x80610014
		opword 0x6C008000
		opword 0x6C638000
		opword 0x90010024
		opword 0x9061000C
		opword 0xC8010020
		opword 0xC8210008
		opword 0xEC001028
		opword 0xEC211028
		opword 0xEC001824
		opword 0xEC211824
		opword 0xEC200828
		bl revise360
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4082002C
		opword 0xEC3FF028
		lfs f0, float_90_8041acd8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4081003C
		opword 0xFC1EF840
		opword 0x40810034
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFFF002A
		opword 0x48000028
		opword 0xEC3FF028
		lfs f0, float_90_8041acd8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810014
		opword 0xFC1EF840
		opword 0x4080000C
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFDE002A
		lfs f4, float_10_8041ace4(r2)
		opword 0x3C004330
		lis r3, double_to_int_802c5dd0@ha
		opword 0x38A00000
		opword 0xEC0407F2
		opword 0x90010018
		lfd f3, double_to_int_802c5dd0@l(r3)
		opword 0x7CA42B78
		lfs f1, float_90_8041acd8(r2)
		opword 0xFC40001E
		lfs f0, float_0_8041acbc(r2)
		opword 0xD8410020
		opword 0x80010024
		opword 0x6C008000
		opword 0x9001001C
		opword 0xC8410018
		opword 0xEC421828
		opword 0xEC622024
		opword 0xEC430828
		opword 0xFC020040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38A00001
		opword 0xEC42002A
		lfs f1, float_90_8041acd8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC23082A
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC210028
		opword 0x38A00002
		opword 0x2C050001
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800050
		opword 0xFC1E1040
		opword 0x40800048
		opword 0x38800001
		opword 0x48000040
		opword 0x2C050002
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800030
		opword 0xFC1E1040
		opword 0x40800028
		opword 0x38800001
		opword 0x48000020
		opword 0x2C050000
		opword 0x40820018
		opword 0xFC1E1040
		opword 0x4180000C
		opword 0xFC01F040
		opword 0x40800008
		opword 0x38800001
		opword 0x2C040000
		opword 0x40820034
		opword 0xEC3FF028
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810020
		opword 0xFC1FF040
		opword 0x40810010
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFFF0028
		opword 0x4800000C
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFDE0028
		opword 0xEC1EF828
		lfs f1, float_1p2_8041acec(r2)
		opword 0xEFE1F83A
		opword 0xFC20F890
		bl revise360
		opword 0xFFE00890
		opword 0xC03F01A8
		bl toMovedir
		opword 0x881F0043
		opword 0x7C000775
		opword 0x41820010
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC20082A
		bl revise360
		lfs f5, float_10_8041ace4(r2)
		opword 0x3C004330
		lis r3, double_to_int_802c5dd0@ha
		opword 0x38A00000
		opword 0xEC0507F2
		opword 0x90010018
		lfd f4, double_to_int_802c5dd0@l(r3)
		opword 0x7CA42B78
		lfs f2, float_135_8041ace8(r2)
		opword 0xFC60001E
		lfs f0, float_0_8041acbc(r2)
		opword 0xD8610020
		opword 0x80010024
		opword 0x6C008000
		opword 0x9001001C
		opword 0xC8610018
		opword 0xEC632028
		opword 0xEC832824
		opword 0xEC641028
		opword 0xFC030040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38A00001
		opword 0xEC63002A
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC44102A
		opword 0xFC020040
		opword 0x4081000C
		opword 0xEC420028
		opword 0x38A00002
		opword 0x2C050001
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800050
		opword 0xFC011840
		opword 0x40800048
		opword 0x38800001
		opword 0x48000040
		opword 0x2C050002
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800030
		opword 0xFC011840
		opword 0x40800028
		opword 0x38800001
		opword 0x48000020
		opword 0x2C050000
		opword 0x40820018
		opword 0xFC011840
		opword 0x4180000C
		opword 0xFC020840
		opword 0x40800008
		opword 0x38800001
		opword 0x2C040001
		opword 0x40820014
		opword 0x887F0043
		opword 0x38030001
		opword 0x540007FE
		opword 0x981F0043
		lfs f1, float_270_8041acdc(r2)
		opword 0xC01F0198
		opword 0x881F0043
		opword 0xEC01002A
		opword 0x7C000775
		opword 0xEC20F828
		opword 0x4182000C
		lfs f0, float_neg180_8041ad88(r2)
		opword 0x48000008
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03F01A8
		lfs f0, float_200_8041ad8c(r2)
		opword 0xC03F01A8
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820038
		lfs f1, float_270_8041acdc(r2)
		opword 0xC01F0198
		opword 0x881F0043
		opword 0xEC01002A
		opword 0x7C000775
		opword 0xEC20F828
		opword 0x4182000C
		lfs f0, float_neg180_8041ad88(r2)
		opword 0x48000008
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03F01A8
		opword 0xC03F01A8
		lfs f0, float_170_8041ad90(r2)
		opword 0xFC010040
		opword 0x40800038
		lfs f1, float_270_8041acdc(r2)
		opword 0xC01F0198
		opword 0x881F0043
		opword 0xEC01002A
		opword 0x7C000775
		opword 0xEC20F828
		opword 0x4182000C
		lfs f0, float_neg180_8041ad88(r2)
		opword 0x48000008
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03F01A8
		opword 0xE3E10048
		opword 0xCBE10040
		opword 0xE3C10038
		opword 0xCBC10030
		opword 0x83E1002C
		opword 0x80010054
		opword 0x83C10028
		opword 0x7C0803A6
		opword 0x38210050
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void rollEvtJumpSetup(void) {
    MarioWork* mario = marioGetPtr();
    camFollowYOff();
    mario->flags |= 0x10000;
    mario->airTimer = 1;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void marioReInit_roll(void) {
#ifdef NONMATCHING
    void* p;
    MarioWork* mario = marioGetPtr();
    f32 z0;
    f32 z1;
    p = __memAlloc(0, 0x14);
    marioGetPtr()->motStruct = p;
    memset(marioGetPtr()->motStruct, 0, 0x14);
    {
        MarioWork* t = marioGetPtr();
        PI(t, 0x2a8) = -1;
    }
    mario->trigFlags &= ~1;
    mario->currMotionId = 0x16;
    mario->flags |= 0x1000000;
    mario->field_0x8 = 0x10;
    marioPaperOn("p_roll");
    marioChgPose("M_I_U");
    marioChgPaper("PM_R_1B");
    mario->dispFlags |= 8;
    mario->dispFlags |= 0x100;
    mario->currSubMotionId = 0x1e;
    mario = marioGetPtr();
    z0 = 0.0f;
    mario->wPlayerCollisionBox.x = 14.8f;
    mario->wPlayerCollisionBox.y = 14.8f;
    mario->mBaseDashSpeed = rollData[0];
    RW()->x = z0;
    z1 = 0.0f;
    RW()->z = z1;
    *(f32*)(0xb0 + (u8*)mario) = -6.0f;
    mario->rotOfs.y = 6.0f;
    *(f32*)((u8*)mario + 0x98) = 6.0f;
    mario->dispOfs.y = 0.0f;
    mario->scale.x = 1.0f;
    mario->scale.y = 1.0f;
    mario->scale.z = 1.0f;
    mario->unk130 = 1.0f;
    allPartyForceRideOn();
#endif
#ifndef NONMATCHING
	asm volatile {
		bl marioGetPtr
		mr r30, r3
		opword 0x38600000
		opword 0x38800014
		bl __memAlloc
		opword 0x7C7F1B78
		bl marioGetPtr
		opword 0x93E30288
		bl marioGetPtr
		opword 0x80630288
		opword 0x38800000
		opword 0x38A00014
		bl memset
		bl marioGetPtr
		opword 0x3800FFFF
		lis r4, str_802C5DD8@ha
		opword 0x900302A8
		addi r3, r4, str_802C5DD8@l
		opword 0x38800016
		opword 0x38000010
		opword 0x80BE000C
		opword 0x54A5003C
		opword 0x90BE000C
		opword 0xB09E002E
		opword 0x809E0000
		opword 0x64840100
		opword 0x909E0000
		opword 0x901E0008
		bl marioPaperOn
		la r3, str_8041AD04(r2)
		bl marioChgPose
		lis r3, str_802C5DE8@ha
		addi r3, r3, str_802C5DE8@l
		bl marioChgPaper
		opword 0x807E0004
		opword 0x3800001E
		opword 0x60630008
		opword 0x907E0004
		opword 0x807E0004
		opword 0x60630100
		opword 0x907E0004
		opword 0x901E0044
		bl marioGetPtr
		lfs f0, float_14p8_8041ad0c(r2)
		opword 0x7C7F1B78
		lfs f30, float_0_8041acbc(r2)
		opword 0xD00301B4
		opword 0xD00301B8
		lfs f0, rollData(r13)
		opword 0xD0030188
		bl marioGetPtr
		opword 0x80630288
		lfs f31, float_0_8041acbc(r2)
		opword 0xD3C30000
		bl marioGetPtr
		opword 0x80630288
		lfs f0, float_neg6_8041ad10(r2)
		opword 0xD3E30004
		lfs f2, float_6_8041accc(r2)
		opword 0xD01F00B0
		lfs f1, float_0_8041acbc(r2)
		opword 0xD05F00B4
		lfs f0, float_1_8041ad14(r2)
		opword 0xD05F0098
		opword 0xD03F009C
		opword 0xD01F00C8
		opword 0xD01F00CC
		opword 0xD01F00D0
		opword 0xD01F0130
		bl allPartyForceRideOn
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif




#ifdef NONMATCHING
static inline s32 rollChk(void) {
    s32 r;
    MarioWork* m = marioGetPtr();
    if (PI(m, 0x2a4) & 0x200) {
        r = 1;
    } else if (m->flags & 0x8000000) {
        r = 1;
    } else if (!m->hitobjStandOn) {
        r = 1;
    } else if (marioSlitChkWallAround()) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
#endif



#ifdef NONMATCHING
static __declspec(section ".rodata") Vec rollOfs = {0.0f, 40.0f, 0.0f};
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void mot_roll(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    f32 v31;
    f32 v29;
    f32 v28;
    f32 v30;
    f32 v27;
    f32 v26;
    f32 tcA;
    if (mario->trigFlags & 1) {
        mario->trigFlags &= ~1;
        mario->flags &= ~0xF0000;
        MI(0x2a4) = 0;
        MI(0x2a8) = 0;
        MI(0x2ac) = 0;
        MI(0x2b0) = 0;
        MI(0x2b4) = 0;
        {
            void* p = __memAlloc(0, 0x14);
            marioGetPtr()->motStruct = p;
        }
        memset(marioGetPtr()->motStruct, 0, 0x14);
        {
            MarioWork* t = marioGetPtr();
            PI(t, 0x2a8) = -1;
        }
        MI(0x44) = 0;
    }
    switch (MI(0x44)) {
    case 0: {
        MarioWork* m;
        s32 z0 = 0;
        s32 z1;
        CAMF() |= 0x200;
        marioAdjustMoveDir();
        v31 = mario->displayDirection;
        if (v31 < 90.0f || v31 > 270.0f) {
            MB(0x43) = 1;
            MF(0x1a0) = revise360(270.0f - mario->targetYaw);
            mario->moveDirection = 270.0f;
        } else {
            MB(0x43) = 0;
            MF(0x1a0) = revise360(90.0f - mario->targetYaw);
            mario->moveDirection = 90.0f;
        }
        marioGetRubInit();
        mario->flags |= 0x1000000;
        mario->field_0x8 = 0x10;
        mario->dispFlags |= 8;
        mario->dispFlags |= 0x100;
        marioPaperOn("p_roll");
        marioChgPose("M_I_U");
        marioChgPaper("PM_R_1A");
        MI(0x48) = 0x41;
        m = marioGetPtr();
        v28 = 0.0f;
        m->wPlayerCollisionBox.x = 14.8f;
        m->wPlayerCollisionBox.y = 14.8f;
        m->mBaseDashSpeed = rollData[0];
        RW()->x = v28;
        v27 = 0.0f;
        RW()->z = v27;
        m->rotOfs.x = -6.0f;
        m->rotOfs.y = 6.0f;
        m->dispOfs.x = 6.0f;
        m->dispOfs.y = 0.0f;
        m->scale.x = 1.0f;
        m->scale.y = 1.0f;
        m->scale.z = 1.0f;
        m->unk130 = 1.0f;
        mario->airTimer = 0;
        if (mario->forceMoveTimer == 0) {
            mario->baseSpeed = 0.0f;
        }
        m = marioGetPtr();
        m->camShiftTargetZ = 0.4f;
        m->camShiftRate.z = 0.01f;
        m->field_68 = 2.0f;
        ((MarioWork*)m)->field_6C = rollOfs;
        RW()->state = z0;
        z1 = 0;
        RW()->scaleState = z1;
        psndSFXOn_3D((char*)0x179, &mario->position);
        psndSFXOn_3D((char*)0x9f, &mario->position);
        MI(0x44) = 1;
        break;
    }
    case 1:
        if (MI(0x48) == 0x36) {
            allPartyRideShip();
        }
        mario->dispOfs.y += 0.1f;
        if (mario->dispOfs.y > 1.0f) {
            mario->dispOfs.y = 1.0f;
        }
        if (--MI(0x48) <= 0) {
            MI(0x44) = 0x1e;
            marioChgPose("M_I_U");
            marioChgPaper("PM_R_1B");
            CAMF() &= ~0x200;
        }
        break;
    case 0x14:
        mario->baseSpeed = 0.0f;
        mario->rot.x = 0.0f;
        mario->rot.z = 0.0f;
        mario->rotOfs.x = 0.0f;
        mario->rotOfs.y = 0.0f;
        v31 = revise360(MF(0x1a0) - mario->targetYaw);
        mario->dispOfs.x = (v31 < 180.0f) ? 3.0f : -3.0f;
        mario->dispOfs.y = 0.0f;
        MI(0x48) = 0x41;
        MI(0x44) = 0x15;
        mario->displayDirection = 0.0f;
        {
            MarioWork* m = marioGetPtr();
            if ((u32)PI(m, 0x2a8) != (u32)-1) {
                psndSFXOff(PI(m, 0x2a8));
                PI(m, 0x2a8) = -1;
            }
        }
        {
            MarioWork* m = marioGetPtr();
            m->camShiftTargetZ = 0.0f;
            m->camShiftRate.z = 0.004f;
        }
        marioChgPaper("PM_R_1C");
        marioPaperLightOff();
        psndSFXOn_3D((char*)0x17a, &mario->position);
    case 0x15:
        if (--MI(0x48) > 0) {
            v31 = revise360(MF(0x1a0) - mario->targetYaw);
            if (v31 < 180.0f) {
                f32 t = 90.0f;
                f32 diff = t - mario->displayDirection;
                f32 n = 0.1f * diff;
                n += mario->displayDirection;
                if (__fabsf((f32)((t - n) < 1.0f))) {
                    n = t;
                }
                mario->displayDirection = n;
                mario->displayDirectionTarget = n;
            } else {
                f32 t = 270.0f;
                f32 diff = t - mario->displayDirection;
                f32 n = 0.1f * diff;
                n += mario->displayDirection;
                if (__fabsf((f32)((t - n) < 1.0f))) {
                    n = t;
                }
                mario->displayDirection = n;
                mario->displayDirectionTarget = n;
            }
        } else {
            v31 = revise360(MF(0x1a0) - mario->targetYaw);
            if (v31 >= 180.0f) {
                mario->displayDirection = 0.0f;
                mario->displayDirectionTarget = 0.0f;
                mario->moveDirection = 270.0f;
                MF(0x1a0) = 270.0f;
            } else {
                mario->displayDirection = 180.0f;
                mario->displayDirectionTarget = 180.0f;
                mario->moveDirection = 90.0f;
                MF(0x1a0) = 90.0f;
            }
            marioSetSpec();
            mario->field_0x8 = 0;
            marioOfsRotReset();
            mario->dispFlags &= ~0x100;
            mario->dispFlags &= ~8;
            mario->flags &= ~0x1000000;
            marioPaperOff();
            marioAdjustMoveDir();
            marioChgPose("M_S_1");
            if (marioGetPtr()->motStruct) {
                void* z;
                __memFree(0, marioGetPtr()->motStruct);
                z = 0;
                marioGetPtr()->motStruct = z;
            }
            allPartyRideOff();
            CAMF() &= ~0x200;
            MI(0x44) = 0x16;
        }
        break;
    case 0x16:
        marioChgMotSub(0, 0);
        break;
    }
    if (MI(0x44) < 0x1e) {
        return;
    }
    if (mario->flags & 0x40000) {
        roll_upstairs();
        return;
    }
    if (mario->buttonBuffer & 0x200) {
        if (!rollChk()) {
            MI(0x44) = 0x14;
            CAMF() |= 0x200;
        } else {
            mario->buttonBuffer |= 0x100;
        }
    }
    v26 = mario->unk130;
    if (RW()->state) {
        s32 z = 0;
        s32 one;
        RW()->state = z;
        one = 1;
        RW()->scaleState = one;
        v26 = 1.0f;
    }
    switch (RW()->scaleState) {
    case 1:
        if (v26 < 1.4f) {
            { f32 k = 1.0f; v26 = k * (1.4499999f - v26) + v26; }
            if (v26 >= 1.4f) {
                v26 = 1.4f;
            }
        }
        if (mario->airTimer == 0) {
            s32 t = 2;
            RW()->scaleState = t;
        }
        break;
    case 2:
        if (v26 > 0.4f) {
            v26 = 0.4f * (0.35f - v26) + v26;
            if (v26 <= 0.4f) {
                s32 t = 3;
                v26 = 0.4f;
                RW()->scaleState = t;
            }
        }
        break;
    case 3:
        if (v26 < 1.0f) {
            v26 = 0.5f * (1.05f - v26) + v26;
            if (v26 >= 1.0f) {
                s32 t = 0;
                RW()->scaleState = t;
                v26 = 1.0f;
            }
        }
        break;
    }
    mario->unk130 = v26;
    if (!mario->hitobjStandOn && mario->hitobjFront && !marioChkBero(mario->hitobjFront)) {
        v26 = RW()->x;
        v27 = RW()->z;
        v26 += 0.2f * -v26;
        v27 += 0.2f * -v27;
        if (__fabsf(v26) < 1.0f) {
            v26 = 0.0f;
        }
        if (__fabsf(v27) < 1.0f) {
            v27 = 0.0f;
        }
        RW()->x = v26;
        RW()->z = v27;
    }
    if (mario->hitobjStandOn) {
        if (!(hitGetAttr(mario->hitobjStandOn) & 0xa00) && mario->airTimer == 0 && (mario->buttonBuffer & 0x100)) {
            if (!(strcmp(gp->currentMapName, "eki_04") == 0 && __fabsf(MF(0x214)) >= 40.0f)) {
                MarioWork* m = marioGetPtr();
                camFollowYOff();
                m->jumpVelocityY = 2.85f;
                m->jumpAccelerationY = -0.14f;
                m->jumpJerkY = 0.08f;
                m->jumpSnapY = -0.02f;
                m->flags |= 0x10000;
                m->airTimer = 1;
                psndSFXOn_3D((char*)0x17c, &marioGetPtr()->position);
                mario->hitobjJumpFrom = mario->hitobjStandOn;
                mario->hitobjStandOn = 0;
                MV(0xd4) = mario->position;
                MV(0x11c) = mario->position;
                camFollowYOff();
            }
        }
        {
            Vec pv = mario->position;
            marioUpdateCamCollision(&pv);
        }
        mario->airTimer = 0;
    }
    if (mario->flags & 0x30000) {
        if (mario->hitobjHead) {
            if (mario->jumpVelocityY >= 0.0f) {
                mario->jumpVelocityY = -0.03f;
                mario->jumpAccelerationY = -0.02f;
                mario->jumpJerkY = -0.02f;
                mario->jumpSnapY = -0.002f;
            }
            mario->flags |= 0x20000;
        }
        if (mario->airTimer == 0 && mario->jumpVelocityY < 0.0f) {
            MV(0xd4) = mario->position;
            camFollowYOn();
        }
        if (mario->position.y < mario->lastGroundPos.y) {
            camFollowYOn();
        }
        mario->airTimer++;
    }
    v29 = RW()->x;
    v28 = RW()->z;
    v27 = 0.0f;
    v30 = v27;
    if (!(mario->flags & 0x30000)) {
        f32 a26, a30;
        a26 = (f32)(s32)(s8)mario->wStickDir1;
        a30 = (f32)(s32)(s8)mario->wStickDir2;
        v27 = distABf(v30, v30, a26, a30);
        v31 = angleABf(0.0f, 0.0f, a26, a30);
        v31 = revise360(mario->targetYaw + v31);
        v26 = 3.1415927f * v31 / 180.0f;
        v30 = v27 * (f32)sin(v26);
        v27 = v27 * -(f32)cos(v26);
        v31 = angleABf(0.0f, 0.0f, v30, v27);
        tcA = MF(0x1a0);
        if (angOut(tcA, 135.0f, v31) == 1) {
            v27 = distABf(0.0f, 0.0f, v30, v27);
            v30 = -v27 * (f32)sin(3.1415927f * MF(0x1a0) / 180.0f);
            v27 = v27 * (f32)cos(3.1415927f * MF(0x1a0) / 180.0f);
        }
    }
    if (!(mario->flags & 0x30000) && !(MI(0x2a4) & 0x20)) {
        v31 = angleABf(0.0f, 0.0f, v29, -v28);
        if (MF(0x220) > 0.05f) {
            v26 = (v31 > 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x220) / 180.0f) * v26;
                v30 = v30 - t;
            }
            if (v30 <= -100.0f) {
                v30 = -100.0f;
            }
        } else if (MF(0x220) < -0.05f) {
            v26 = (v31 < 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x220) / 180.0f) * v26;
                v30 = v30 - t;
            }
            if (v30 >= 100.0f) {
                v30 = 100.0f;
            }
        }
        if (MF(0x218) > 0.05f) {
            v26 = (v31 > 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x218) / 180.0f) * v26;
                v27 = v27 - t;
            }
            if (v27 <= -100.0f) {
                v27 = -100.0f;
            }
        } else if (MF(0x218) < -0.05f) {
            v26 = (v31 < 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x218) / 180.0f) * v26;
                v27 = v27 - t;
            }
            if (v27 >= 100.0f) {
                v27 = 100.0f;
            }
        }
        v31 = angleABf(0.0f, 0.0f, v30, v27);
        tcA = MF(0x1a0);
        if (angOut(tcA, 135.0f, v31) == 1) {
            v27 = distABf(0.0f, 0.0f, v30, -v27);
            v30 = -v27 * (f32)sin(3.1415927f * MF(0x1a0) / 180.0f);
            v27 = v27 * (f32)cos(3.1415927f * MF(0x1a0) / 180.0f);
        }
    }
    if (*(void**)((u8*)mario + 0x1d8)) {
        if (!marioChkBero(mario->hitobjFront)) {
            v29 = 0.05f * -v29 + v29;
            v28 = 0.05f * -v28 + v28;
            if (__fabsf(v29) < 0.1f) {
                v29 = 0.0f;
            }
            if (__fabsf(v28) < 0.1f) {
                v28 = 0.0f;
            }
        }
    }
    if (mario->hitobjFront && !MB(0x24e) && !MB(0x24f) && !marioChkBero(mario->hitobjFront)) {
        v29 = 0.6f * -v29 + v29;
        v28 = 0.6f * -v28 + v28;
        if (__fabsf(v29) < 0.1f) {
            v29 = 0.0f;
        }
        if (__fabsf(v28) < 0.1f) {
            v28 = 0.0f;
        }
    }
    if (mario->forceMoveTimer == 0 && !v30 && !v27) {
        if (mario->hitobjWall) {
            if (!marioChkBero(mario->hitobjWall)) {
                f32 k = rollData[2];
                v29 = v29 * k + v29;
                v28 = v28 * k + v28;
            }
        } else if (mario->hitobjStandOn && mario->airTimer == 0) {
            if (__fabsf((f32)(MF(0x214) <= 1.0f))) {
                f32 k = rollData[1];
                v29 = v29 * k + v29;
                v28 = v28 * k + v28;
            } else {
                f32 k = rollData[1];
                f32 a = v29 * k;
                f32 b = v28 * k;
                v29 = 6.4f * a + v29;
                v28 = 6.4f * b + v28;
            }
        }
        if (__fabsf(v29) < rollData[3]) {
            v29 = 0.0f;
        }
        if (__fabsf(v28) < rollData[3]) {
            v28 = 0.0f;
        }
    } else if ((MI(0x2a4) & 0x10) && MF(0x220) == 0.0f) {
        if (makeVec(135.0f) == 1) {
            v29 = 0.2f * -v29 + v29;
            v28 = 0.2f * -v28 + v28;
            if (__fabsf(v29) < 1.0f) {
                v29 = 0.0f;
            }
            if (__fabsf(v28) < 1.0f) {
                v28 = 0.0f;
            }
            if (v29 == 0.0f && v28 == 0.0f) {
                mario->moveDirection = revise360(180.0f + mario->moveDirection);
                MF(0x1a0) = mario->moveDirection;
            }
        }
    }
    v31 = rollData[0] / 0.05f;
    v26 = 1.0f;
    if (mario->forceMoveTimer == 0 && __fabsf(MF(0x214)) >= v26) {
        f32 ang = angleABf(0.0f, 0.0f, v29, -v28);
        f32 sp = MF(0x220);
        if (sp > 0.0f) {
            if (ang > 180.0f) {
                v26 = rollData[9];
            } else {
                v26 = 1.0f;
            }
        } else if (sp < 0.0f) {
            if (ang < 180.0f) {
                v26 = rollData[9];
            } else {
                v26 = 1.0f;
            }
        }
    }
    v31 = v31 * v26;
    v26 = v28 * v28;
    if (v29 * v29 + v26 <= v31 * v31) {
        v29 = v30 * 0.025f + v29;
    } else {
        f32 n = -v31;
        v29 = v30 * 0.025f + v29;
        if (v29 < n) {
            v29 = n;
        }
        if (v29 > v31) {
            v29 = v31;
        }
    }
    v31 = rollData[0] / 0.05f;
    v30 = 1.0f;
    if (mario->forceMoveTimer == 0 && __fabsf(MF(0x214)) >= v30) {
        f32 ang = angleABf(0.0f, 0.0f, v29, -v28);
        f32 sp = MF(0x218);
        if (sp > 0.0f) {
            if (ang > 180.0f) {
                v30 = rollData[9];
            } else {
                v30 = 1.0f;
            }
        } else if (sp < 0.0f) {
            if (ang < 180.0f) {
                v30 = rollData[9];
            } else {
                v30 = 1.0f;
            }
        }
    }
    v31 = v31 * v30;
    if (v29 * v29 + v26 <= v31 * v31) {
        v28 = v28 - v27 * 0.025f;
    } else {
        f32 n = -v31;
        v28 = v28 - v27 * 0.025f;
        if (v28 < n) {
            v28 = n;
        }
        if (v28 > v31) {
            v28 = v31;
        }
    }
    RW()->x = v29;
    RW()->z = v28;
    v31 = -v28;
    v30 = angleABf(0.0f, 0.0f, v29, v31);
    v27 = 3.1415927f * v30 / 180.0f;
    v26 = (f32)cos(v27);
    v27 = distABf(0.0f, 0.0f, v29 * (f32)sin(v27), v28 * v26);
    v27 = 0.05f * v27;
    if (!getRollEvtFlag() && mario->forceMoveTimer == 0) {
        v30 = angleABf(0.0f, 0.0f, v29, v31);
        if (!(MI(0x2a4) & 0x10000)) {
            v27 = v27 * mario->playerGravity;
            if (v27 < 0.05f) {
                v27 = 0.0f;
            }
            mario->baseSpeed = v27;
            if (v27) {
                MF(0x1a0) = v30;
            }
        }
    }
    if (mario->baseSpeed) {
        MarioWork* m = marioGetPtr();
        if ((u32)PI(m, 0x2a8) == (u32)-1) {
            PI(m, 0x2a8) = (s32)psndSFXOn_3D((char*)0x17b, &m->position);
            PI(m, 0x2a4) |= 0x1000;
        }
    } else {
        MarioWork* m = marioGetPtr();
        if ((u32)PI(m, 0x2a8) != (u32)-1) {
            psndSFXOff(PI(m, 0x2a8));
            PI(m, 0x2a8) = -1;
        }
    }
    v28 = rollData[4];
    {
        s32 flip;
        f32 sgn;
        f32 mv = toMovedir(mario->displayDirection);
        f32 pre;
        tcA = MF(0x1a0);
        flip = angOut(tcA, 90.0f, mv);
        pre = mario->baseSpeed * v28;
        sgn = (flip == 1) ? -1.0f : 1.0f;
        mario->rot.z = revise360(pre * sgn + mario->rot.z);
    }
    if (mario->forceMoveTimer == 0 && !getRollEvtFlag() && v27) {
        v31 = mario->moveDirection;
        {
            MarioWork* m2 = marioGetPtr();
            DISPDIR_BODY(v30, v31, m2)
        }
        MF(0x1a0) = v31;
        mario->moveDirection = v31;
    }
    if (MF(0x220) != 0.0f) {
        mario->rot.x = revise360(-MF(0x220) * (f32)sin(3.1415927f * mario->displayDirection / 180.0f));
    } else {
        mario->rot.x = 0.0f;
    }
    if (MB(0x24e) || MB(0x24f)) {
        MI(0x2a4) |= 0x4000;
    }
    if (mario->baseSpeed) {
        MarioWork* m = marioGetPtr();
        m->camShiftTargetZ = 0.0f;
        m->camShiftRate.z = 0.004f;
    }
    marioRollCan();
#endif
#ifndef NONMATCHING
	char _af_pad[112];
	asm volatile {
		lis r3, vec3_802c5d40@ha
		addi r30, r3, vec3_802c5d40@l
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0x8063000C
		opword 0x546007FF
		opword 0x41820070
		opword 0x5463003C
		opword 0x38000000
		opword 0x907F000C
		opword 0x38600000
		opword 0x38800014
		opword 0x80BF0000
		opword 0x54A50416
		opword 0x90BF0000
		opword 0x901F02A4
		opword 0x901F02A8
		opword 0x901F02AC
		opword 0x901F02B0
		opword 0x901F02B4
		bl __memAlloc
		opword 0x7C7C1B78
		bl marioGetPtr
		opword 0x93830288
		bl marioGetPtr
		opword 0x80630288
		opword 0x38800000
		opword 0x38A00014
		bl memset
		bl marioGetPtr
		opword 0x3880FFFF
		opword 0x38000000
		opword 0x908302A8
		opword 0x901F0044
		opword 0x801F0044
		opword 0x2C000014
		opword 0x4182026C
		opword 0x4080001C
		opword 0x2C000001
		opword 0x418201EC
		opword 0x408004FC
		opword 0x2C000000
		opword 0x40800018
		opword 0x480004F0
		opword 0x2C000016
		opword 0x418204DC
		opword 0x408004E4
		opword 0x480002F0
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x60000200
		opword 0xB0030000
		bl marioAdjustMoveDir
		opword 0xC05F01A8
		lfs f1, float_90_8041acd8(r2)
		opword 0xFC020840
		opword 0x41800010
		lfs f0, float_270_8041acdc(r2)
		opword 0xFC020040
		opword 0x4081002C
		opword 0x38000001
		lfs f1, float_270_8041acdc(r2)
		opword 0x981F0043
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		opword 0xD03F01A0
		lfs f0, float_270_8041acdc(r2)
		opword 0xD01F019C
		opword 0x48000024
		opword 0x38000000
		opword 0x981F0043
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		opword 0xD03F01A0
		lfs f0, float_90_8041acd8(r2)
		opword 0xD01F019C
		bl marioGetRubInit
		opword 0x809F0000
		opword 0x38000010
		opword 0x387E0098
		opword 0x64840100
		opword 0x909F0000
		opword 0x901F0008
		opword 0x801F0004
		opword 0x60000008
		opword 0x901F0004
		opword 0x801F0004
		opword 0x60000100
		opword 0x901F0004
		bl marioPaperOn
		la r3, str_8041AD04(r2)
		bl marioChgPose
		opword 0x387E00A0
		bl marioChgPaper
		opword 0x38000041
		opword 0x901F0048
		bl marioGetPtr
		lfs f0, float_14p8_8041ad0c(r2)
		opword 0x7C7C1B78
		lfs f28, float_0_8041acbc(r2)
		opword 0xD00301B4
		opword 0xD00301B8
		lfs f0, rollData(r13)
		opword 0xD0030188
		bl marioGetPtr
		opword 0x80630288
		lfs f27, float_0_8041acbc(r2)
		opword 0xD3830000
		bl marioGetPtr
		opword 0x80630288
		opword 0x38000000
		lfs f0, float_neg6_8041ad10(r2)
		opword 0xD3630004
		lfs f2, float_6_8041accc(r2)
		opword 0xD01C00B0
		lfs f1, float_0_8041acbc(r2)
		opword 0xD05C00B4
		lfs f0, float_1_8041ad14(r2)
		opword 0xD05C0098
		opword 0xD03C009C
		opword 0xD01C00C8
		opword 0xD01C00CC
		opword 0xD01C00D0
		opword 0xD01C0130
		opword 0xB01F0050
		opword 0xA81F004E
		opword 0x2C000000
		opword 0x40820008
		opword 0xD03F0180
		bl marioGetPtr
		lfs f0, float_0p4_8041ad18(r2)
		opword 0x3BA00000
		lfs f1, float_0p01_8041ad1c(r2)
		opword 0xD0030148
		lfs f0, float_2_8041ad20(r2)
		opword 0xD0230158
		opword 0xD0030068
		opword 0x809E0000
		opword 0x801E0004
		opword 0x9083006C
		opword 0x90030070
		opword 0x801E0008
		opword 0x90030074
		bl marioGetPtr
		opword 0x80630288
		li r28, 0x0
		opword 0x93A30008
		bl marioGetPtr
		opword 0x80A30288
		opword 0x389F008C
		opword 0x38600179
		opword 0x9385000C
		bl psndSFXOn_3D
		opword 0x389F008C
		opword 0x3860009F
		bl psndSFXOn_3D
		opword 0x38000001
		opword 0x901F0044
		opword 0x48000318
		opword 0x801F0048
		opword 0x2C000036
		opword 0x40820008
		bl allPartyRideShip
		opword 0xC05F009C
		lfs f1, float_0p1_8041ad24(r2)
		lfs f0, float_1_8041ad14(r2)
		opword 0xEC22082A
		opword 0xD03F009C
		opword 0xC03F009C
		opword 0xFC010040
		opword 0x40810008
		opword 0xD01F009C
		opword 0x807F0048
		opword 0x3403FFFF
		opword 0x901F0048
		opword 0x418102D4
		opword 0x3800001E
		la r3, str_8041AD04(r2)
		opword 0x901F0044
		bl marioChgPose
		opword 0x387E00A8
		bl marioChgPaper
		opword 0x38600008
		bl camGetPtr
		opword 0xA0030000
		opword 0x540005EA
		opword 0xB0030000
		opword 0x480002A4
		lfs f0, float_0_8041acbc(r2)
		opword 0xD01F0180
		opword 0xD01F00BC
		opword 0xD01F00C4
		opword 0xD01F00B0
		opword 0xD01F00B4
		opword 0xC03F01A0
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_3_8041ad28(r2)
		opword 0x48000008
		lfs f0, float_neg3_8041ad2c(r2)
		opword 0xD01F0098
		opword 0x38600041
		lfs f0, float_0_8041acbc(r2)
		opword 0x38000015
		opword 0xD01F009C
		opword 0x907F0048
		opword 0x901F0044
		opword 0xD01F01A8
		bl marioGetPtr
		opword 0x7C7C1B78
		opword 0x806302A8
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820010
		bl psndSFXOff
		opword 0x3800FFFF
		opword 0x901C02A8
		bl marioGetPtr
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_0p004_8041ad30(r2)
		opword 0xD0230148
		opword 0xD0030158
		opword 0x387E00B0
		bl marioChgPaper
		bl marioPaperLightOff
		opword 0x389F008C
		opword 0x3860017A
		bl psndSFXOn_3D
		opword 0x807F0048
		opword 0x3403FFFF
		opword 0x901F0048
		opword 0x408100F0
		opword 0xC03F01A0
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x4080006C
		lfs f3, float_90_8041acd8(r2)
		opword 0xC09F01A8
		lfs f2, float_0p1_8041ad24(r2)
		opword 0xEC232028
		lfs f0, float_1_8041ad14(r2)
		opword 0xECA20072
		opword 0xECA5202A
		opword 0xEC232828
		opword 0xFC010040
		opword 0x7C600026
		opword 0x3C004330
		opword 0x54630FFE
		stw r0, _af_pad+88(r1)
		opword 0x6C608000
		opword 0xC85E0090
		opword 0x90010064
		lfs f0, float_0_8041acbc(r2)
		opword 0xC8210060
		opword 0xEC211028
		opword 0xFC200A10
		opword 0xFC010000
		opword 0x41820008
		opword 0xFCA01890
		opword 0xD0BF01A8
		opword 0xD0BF01AC
		opword 0x48000160
		lfs f3, float_270_8041acdc(r2)
		opword 0xC09F01A8
		lfs f2, float_0p1_8041ad24(r2)
		opword 0xEC232028
		lfs f0, float_1_8041ad14(r2)
		opword 0xECA20072
		opword 0xECA5202A
		opword 0xEC232828
		opword 0xFC010040
		opword 0x7C600026
		opword 0x3C004330
		opword 0x54630FFE
		opword 0x90010060
		opword 0x6C608000
		opword 0xC85E0090
		opword 0x90010064
		lfs f0, float_0_8041acbc(r2)
		opword 0xC8210060
		opword 0xEC211028
		opword 0xFC200A10
		opword 0xFC010000
		opword 0x41820008
		opword 0xFCA01890
		opword 0xD0BF01A8
		opword 0xD0BF01AC
		opword 0x480000F8
		opword 0xC03F01A0
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		lfs f2, float_180_8041acc8(r2)
		opword 0xFC011040
		opword 0x4C411382
		opword 0x40820020
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_270_8041acdc(r2)
		opword 0xD03F01A8
		opword 0xD03F01AC
		opword 0xD01F019C
		opword 0xD01F01A0
		opword 0x48000018
		opword 0xD05F01A8
		lfs f0, float_90_8041acd8(r2)
		opword 0xD05F01AC
		opword 0xD01F019C
		opword 0xD01F01A0
		bl marioSetSpec
		opword 0x38000000
		opword 0x901F0008
		bl marioOfsRotReset
		opword 0x801F0004
		opword 0x5400062C
		opword 0x901F0004
		opword 0x801F0004
		opword 0x54000776
		opword 0x901F0004
		opword 0x801F0000
		opword 0x5400020C
		opword 0x901F0000
		bl marioPaperOff
		bl marioAdjustMoveDir
		la r3, str_8041AD34(r2)
		bl marioChgPose
		bl marioGetPtr
		opword 0x80030288
		opword 0x28000000
		opword 0x41820024
		bl marioGetPtr
		opword 0x7C641B78
		opword 0x38600000
		opword 0x80840288
		bl __memFree
		opword 0x3B800000
		bl marioGetPtr
		opword 0x93830288
		bl allPartyRideOff
		opword 0x38600008
		bl camGetPtr
		opword 0xA0830000
		opword 0x38000016
		opword 0x548405EA
		opword 0xB0830000
		opword 0x901F0044
		opword 0x48000010
		opword 0x38600000
		opword 0x38800000
		bl marioChgMotSub
		opword 0x801F0044
		opword 0x2C00001E
		opword 0x41801954
		opword 0x801F0000
		opword 0x5400035B
		opword 0x4182000C
		bl roll_upstairs
		opword 0x48001940
		opword 0xA01F0248
		opword 0x540005AD
		opword 0x41820090
		bl marioGetPtr
		opword 0x800302A4
		opword 0x540005AD
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000044
		opword 0x80030000
		opword 0x54000109
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000030
		opword 0x800301E4
		opword 0x28000000
		opword 0x4082000C
		opword 0x38000001
		opword 0x4800001C
		bl marioSlitChkWallAround
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x40820024
		opword 0x38000014
		opword 0x38600008
		opword 0x901F0044
		bl camGetPtr
		opword 0xA0030000
		opword 0x60000200
		opword 0xB0030000
		opword 0x48000010
		opword 0xA01F0248
		opword 0x60000100
		opword 0xB01F0248
		opword 0xC35F0130
		bl marioGetPtr
		opword 0x80630288
		opword 0x80030008
		opword 0x2C000000
		opword 0x41820028
		opword 0x3B800000
		bl marioGetPtr
		opword 0x80630288
		opword 0x3BA00001
		opword 0x93830008
		bl marioGetPtr
		opword 0x80630288
		lfs f26, float_1_8041ad14(r2)
		opword 0x93A3000C
		bl marioGetPtr
		opword 0x80630288
		opword 0x8003000C
		opword 0x2C000002
		opword 0x4182006C
		opword 0x40800010
		opword 0x2C000001
		opword 0x40800014
		opword 0x480000D4
		opword 0x2C000004
		opword 0x408000CC
		opword 0x4800008C
		lfs f2, float_1p4_8041ad3c(r2)
		opword 0xFC1A1040
		opword 0x40800024
		lfs f0, float_1p45_8041ad40(r2)
		lfs f1, float_1_8041ad14(r2)
		opword 0xEC00D028
		opword 0xEF41D03A
		opword 0xFC1A1040
		opword 0x4C411382
		opword 0x40820008
		opword 0xFF401090
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x40820090
		opword 0x3BA00002
		bl marioGetPtr
		opword 0x80630288
		opword 0x93A3000C
		opword 0x4800007C
		lfs f1, float_0p4_8041ad18(r2)
		opword 0xFC1A0840
		opword 0x40810070
		lfs f0, float_0p35_8041ad44(r2)
		opword 0xEC00D028
		opword 0xEF41D03A
		opword 0xFC1A0840
		opword 0x4C401382
		opword 0x40820058
		opword 0xFF400890
		opword 0x3BA00003
		bl marioGetPtr
		opword 0x80630288
		opword 0x93A3000C
		opword 0x48000040
		lfs f2, float_1_8041ad14(r2)
		opword 0xFC1A1040
		opword 0x40800034
		lfs f0, float_1p05_8041ad48(r2)
		lfs f1, float_0p5_8041acc0(r2)
		opword 0xEC00D028
		opword 0xEF41D03A
		opword 0xFC1A1040
		opword 0x4C411382
		opword 0x40820018
		opword 0x3BA00000
		bl marioGetPtr
		opword 0x80630288
		lfs f26, float_1_8041ad14(r2)
		opword 0x93A3000C
		opword 0xD35F0130
		opword 0x801F01E4
		opword 0x28000000
		opword 0x40820088
		opword 0x807F01E0
		opword 0x28030000
		opword 0x4182007C
		bl marioChkBero
		opword 0x2C030000
		opword 0x40820070
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3430000
		bl marioGetPtr
		opword 0xFC20D050
		lfs f3, float_0p2_8041ad4c(r2)
		opword 0x80630288
		lfs f0, float_1_8041ad14(r2)
		opword 0xEF43D07A
		opword 0xC3630004
		opword 0xFC40D850
		opword 0xFC20D210
		opword 0xEF63D8BA
		opword 0xFC010040
		opword 0x40800008
		lfs f26, float_0_8041acbc(r2)
		opword 0xFC20DA10
		lfs f0, float_1_8041ad14(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f27, float_0_8041acbc(r2)
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3430000
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3630004
		opword 0x807F01E4
		opword 0x28030000
		opword 0x41820118
		bl hitGetAttr
		opword 0x70600A00
		opword 0x408200E4
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x408200D8
		opword 0xA01F0248
		opword 0x540005EF
		opword 0x418200CC
		lwz r3, gp(r13)
		opword 0x389E00B8
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x4082001C
		opword 0xC03F0214
		lfs f0, float_40_8041ad50(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4182009C
		bl marioGetPtr
		opword 0x7C7D1B78
		bl camFollowYOff
		lfs f1, float_2p85_8041ad54(r2)
		opword 0x38000001
		lfs f0, float_neg0p14_8041ad58(r2)
		opword 0xD03D007C
		lfs f1, float_0p08_8041ad5c(r2)
		opword 0xD01D0080
		lfs f0, float_neg0p02_8041ad60(r2)
		opword 0xD03D0084
		opword 0xD01D0088
		opword 0x807D0000
		opword 0x64630001
		opword 0x907D0000
		opword 0xB01D0050
		bl marioGetPtr
		opword 0x7C641B78
		opword 0x3860017C
		opword 0x3884008C
		bl psndSFXOn_3D
		opword 0x807F01E4
		opword 0x38000000
		opword 0x907F01E8
		opword 0x901F01E4
		opword 0x807F008C
		opword 0x801F0090
		opword 0x907F00D4
		opword 0x901F00D8
		opword 0x801F0094
		opword 0x901F00DC
		opword 0x807F008C
		opword 0x801F0090
		opword 0x907F011C
		opword 0x901F0120
		opword 0x801F0094
		opword 0x901F0124
		bl camFollowYOff
		opword 0x809F008C
		opword 0x38610054
		opword 0x801F0090
		opword 0x90810054
		opword 0x90010058
		opword 0x801F0094
		opword 0x9001005C
		bl marioUpdateCamCollision
		opword 0x38000000
		opword 0xB01F0050
		opword 0x801F0000
		opword 0x5400039F
		opword 0x418200A4
		opword 0x801F01F4
		opword 0x28000000
		opword 0x41820040
		opword 0xC03F007C
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820020
		lfs f0, float_neg0p03_8041ad64(r2)
		lfs f1, float_neg0p02_8041ad60(r2)
		opword 0xD01F007C
		lfs f0, float_neg0p002_8041ad68(r2)
		opword 0xD03F0080
		opword 0xD03F0084
		opword 0xD01F0088
		opword 0x801F0000
		opword 0x64000002
		opword 0x901F0000
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x40820030
		opword 0xC03F007C
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC010040
		opword 0x40800020
		opword 0x807F008C
		opword 0x801F0090
		opword 0x907F00D4
		opword 0x901F00D8
		opword 0x801F0094
		opword 0x901F00DC
		bl camFollowYOn
		opword 0xC03F0090
		opword 0xC01F0120
		opword 0xFC010040
		opword 0x40800008
		bl camFollowYOn
		opword 0xA87F0050
		opword 0x38030001
		opword 0xB01F0050
		bl marioGetPtr
		opword 0x80630288
		opword 0xC3A30000
		bl marioGetPtr
		opword 0x801F0000
		lfs f30, float_0_8041acbc(r2)
		opword 0x80630288
		opword 0x5400039F
		opword 0xFF60F090
		opword 0xC3830004
		opword 0x40820200
		opword 0x889F024E
		opword 0x3C604330
		opword 0x881F024F
		opword 0xFC20F090
		opword 0x7C840774
		opword 0x90610060
		opword 0x7C000774
		opword 0xC89E0090
		opword 0x6C848000
		opword 0x6C008000
		opword 0x90810064
		opword 0xFC40F090
		opword 0xC8010060
		opword 0x9001006C
		opword 0xEF402028
		opword 0x90610068
		opword 0xC8010068
		opword 0xFC60D090
		opword 0xEFC02028
		opword 0xFC80F090
		bl distABf
		opword 0xFF600890
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60D090
		opword 0xFC400890
		opword 0xFC80F090
		bl angleABf
		opword 0xC01F0198
		opword 0xEC20082A
		bl revise360
		lfs f2, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC220072
		opword 0xEF410024
		opword 0xFC20D090
		bl sin
		opword 0xFC000818
		opword 0xFC20D090
		opword 0xEFDB0032
		bl cos
		opword 0xFC000818
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60F090
		opword 0xFC400890
		opword 0xFC000050
		opword 0xEF7B0032
		opword 0xFC80D890
		bl angleABf
		opword 0xC01F01A0
		opword 0x3C004330
		lfs f5, float_10_8041ace4(r2)
		opword 0x38800000
		opword 0x90010078
		opword 0x7C832378
		opword 0xEC650032
		opword 0xC89E0090
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC60181E
		opword 0xD8610070
		opword 0x80010074
		opword 0x6C008000
		opword 0x9001007C
		opword 0xC8610078
		opword 0xEC632028
		opword 0xEC832824
		opword 0xEC641028
		opword 0xFC030040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38800001
		opword 0xEC63002A
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC44102A
		opword 0xFC020040
		opword 0x4081000C
		opword 0xEC420028
		opword 0x38800002
		opword 0x2C040001
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800050
		opword 0xFC011840
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C040002
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800030
		opword 0xFC011840
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C040000
		opword 0x40820018
		opword 0xFC011840
		opword 0x4180000C
		opword 0xFC020840
		opword 0x40800008
		opword 0x38600001
		opword 0x2C030001
		opword 0x40820060
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60F090
		opword 0xFC80D890
		opword 0xFC400890
		bl distABf
		lfs f2, float_3p1416_8041acc4(r2)
		opword 0xFF600890
		opword 0xC03F01A0
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		lfs f2, float_3p1416_8041acc4(r2)
		opword 0xFC800818
		opword 0xC03F01A0
		opword 0xFC60D850
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC220072
		opword 0xEFC30132
		opword 0xEC210024
		bl cos
		opword 0xFC000818
		opword 0xEF7B0032
		opword 0x801F0000
		opword 0x5400039F
		opword 0x40820308
		opword 0x801F02A4
		opword 0x540006B5
		opword 0x408202FC
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60E890
		opword 0xFC80E050
		opword 0xFC400890
		bl angleABf
		opword 0xC05F0220
		opword 0xFFE00890
		lfs f0, float_0p05_8041ad6c(r2)
		opword 0xFC020040
		opword 0x4081005C
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC1F0040
		opword 0x40810010
		la r3, rollData(r13)
		opword 0xC3430014
		opword 0x4800000C
		la r3, rollData(r13)
		opword 0xC3430018
		lfs f1, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC2100B2
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		lfs f0, float_neg100_8041ad70(r2)
		opword 0xEC2106B2
		opword 0xEFDE0828
		opword 0xFC1E0040
		opword 0x4C401382
		opword 0x4082006C
		opword 0xFFC00090
		opword 0x48000064
		lfs f0, float_neg0p05_8041ad74(r2)
		opword 0xFC020040
		opword 0x40800058
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC1F0040
		opword 0x40800010
		la r3, rollData(r13)
		opword 0xC3430014
		opword 0x4800000C
		la r3, rollData(r13)
		opword 0xC3430018
		lfs f1, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC2100B2
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		lfs f0, float_100_8041acb8(r2)
		opword 0xEC2106B2
		opword 0xEFDE0828
		opword 0xFC1E0040
		opword 0x4C411382
		opword 0x40820008
		opword 0xFFC00090
		opword 0xC05F0218
		lfs f0, float_0p05_8041ad6c(r2)
		opword 0xFC020040
		opword 0x4081005C
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC1F0040
		opword 0x40810010
		la r3, rollData(r13)
		opword 0xC3430014
		opword 0x4800000C
		la r3, rollData(r13)
		opword 0xC3430018
		lfs f1, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC2100B2
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		lfs f0, float_neg100_8041ad70(r2)
		opword 0xEC2106B2
		opword 0xEF7B0828
		opword 0xFC1B0040
		opword 0x4C401382
		opword 0x4082006C
		opword 0xFF600090
		opword 0x48000064
		lfs f0, float_neg0p05_8041ad74(r2)
		opword 0xFC020040
		opword 0x40800058
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC1F0040
		opword 0x40800010
		la r3, rollData(r13)
		opword 0xC3430014
		opword 0x4800000C
		la r3, rollData(r13)
		opword 0xC3430018
		lfs f1, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC2100B2
		opword 0xEC210024
		bl sin
		opword 0xFC200818
		lfs f0, float_100_8041acb8(r2)
		opword 0xEC2106B2
		opword 0xEF7B0828
		opword 0xFC1B0040
		opword 0x4C411382
		opword 0x40820008
		opword 0xFF600090
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60F090
		opword 0xFC80D890
		opword 0xFC400890
		bl angleABf
		opword 0xC01F01A0
		opword 0x3C004330
		lfs f5, float_10_8041ace4(r2)
		opword 0x38800000
		opword 0x90010070
		opword 0x7C832378
		opword 0xEC650032
		opword 0xC89E0090
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC60181E
		opword 0xD8610078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8610070
		opword 0xEC632028
		opword 0xEC832824
		opword 0xEC641028
		opword 0xFC030040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38800001
		opword 0xEC63002A
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC44102A
		opword 0xFC020040
		opword 0x4081000C
		opword 0xEC420028
		opword 0x38800002
		opword 0x2C040001
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800050
		opword 0xFC011840
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C040002
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800030
		opword 0xFC011840
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C040000
		opword 0x40820018
		opword 0xFC011840
		opword 0x4180000C
		opword 0xFC020840
		opword 0x40800008
		opword 0x38600001
		opword 0x2C030001
		opword 0x40820060
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60F090
		opword 0xFC80D850
		opword 0xFC400890
		bl distABf
		lfs f2, float_3p1416_8041acc4(r2)
		opword 0xFF600890
		opword 0xC03F01A0
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		lfs f2, float_3p1416_8041acc4(r2)
		opword 0xFC800818
		opword 0xC03F01A0
		opword 0xFC60D850
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC220072
		opword 0xEFC30132
		opword 0xEC210024
		bl cos
		opword 0xFC000818
		opword 0xEF7B0032
		opword 0x801F01D8
		opword 0x28000000
		opword 0x41820050
		opword 0x807F01E0
		bl marioChkBero
		opword 0x2C030000
		opword 0x40820040
		opword 0xFC40E850
		lfs f3, float_0p05_8041ad6c(r2)
		opword 0xFC20E050
		lfs f0, float_0p1_8041ad24(r2)
		opword 0xEFA3E8BA
		opword 0xEF83E07A
		opword 0xFC20EA10
		opword 0xFC010040
		opword 0x40800008
		lfs f29, float_0_8041acbc(r2)
		opword 0xFC20E210
		lfs f0, float_0p1_8041ad24(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f28, float_0_8041acbc(r2)
		opword 0x807F01E0
		opword 0x28030000
		opword 0x41820064
		opword 0x881F024E
		opword 0x7C000775
		opword 0x40820058
		opword 0x881F024F
		opword 0x7C000775
		opword 0x4082004C
		bl marioChkBero
		opword 0x2C030000
		opword 0x40820040
		opword 0xFC40E850
		lfs f3, float_0p6_8041ad78(r2)
		opword 0xFC20E050
		lfs f0, float_0p1_8041ad24(r2)
		opword 0xEFA3E8BA
		opword 0xEF83E07A
		opword 0xFC20EA10
		opword 0xFC010040
		opword 0x40800008
		lfs f29, float_0_8041acbc(r2)
		opword 0xFC20E210
		lfs f0, float_0p1_8041ad24(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f28, float_0_8041acbc(r2)
		opword 0xA81F004E
		opword 0x2C000000
		opword 0x408200FC
		lfs f2, float_0_8041acbc(r2)
		opword 0xFC1E1000
		opword 0x408200F0
		opword 0xFC1B1000
		opword 0x408200E8
		opword 0x807F01F0
		opword 0x28030000
		opword 0x41820024
		bl marioChkBero
		opword 0x2C030000
		opword 0x408200A0
		la r3, rollData(r13)
		opword 0xC0030008
		opword 0xEFBDE83A
		opword 0xEF9CE03A
		opword 0x4800008C
		opword 0x801F01E4
		opword 0x28000000
		opword 0x41820080
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x40820074
		opword 0xC03F0214
		lfs f0, float_1_8041ad14(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x7C600026
		opword 0x3C004330
		opword 0x54631FFE
		opword 0x90010078
		opword 0x6C608000
		opword 0xC83E0090
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC000828
		opword 0xFC000210
		opword 0xFC001000
		opword 0x41820018
		la r3, rollData(r13)
		opword 0xC0030004
		opword 0xEFBDE83A
		opword 0xEF9CE03A
		opword 0x48000020
		la r3, rollData(r13)
		lfs f2, float_6p4_8041ad7c(r2)
		opword 0xC0030004
		opword 0xEC3D0032
		opword 0xEC1C0032
		opword 0xEFA2E87A
		opword 0xEF82E03A
		la r3, rollData(r13)
		opword 0xFC00EA10
		opword 0xC023000C
		opword 0xFC000840
		opword 0x40800008
		lfs f29, float_0_8041acbc(r2)
		opword 0xFC00E210
		opword 0xC023000C
		opword 0xFC000840
		opword 0x40800378
		lfs f28, float_0_8041acbc(r2)
		opword 0x48000370
		opword 0x801F02A4
		opword 0x540006F7
		opword 0x418201A8
		lfs f1, float_0_8041acbc(r2)
		opword 0xC01F0220
		opword 0xFC010000
		opword 0x40820198
		opword 0x3BA00000
		opword 0x7FBCEB78
		bl marioGetPtr
		lfs f6, float_10_8041ace4(r2)
		opword 0x3CA04330
		opword 0xC003019C
		opword 0x8883024E
		opword 0xEC060032
		opword 0x8803024F
		opword 0x7C830774
		lfs f1, float_0_8041acbc(r2)
		opword 0x7C000774
		opword 0x90A10070
		opword 0xFC00001E
		opword 0x6C638000
		opword 0x6C008000
		opword 0xC8BE0090
		opword 0x9061006C
		opword 0xFC400890
		opword 0xD8010078
		opword 0x8061007C
		opword 0x90A10068
		opword 0x6C638000
		opword 0x90610074
		opword 0xC8010068
		opword 0xC8810070
		opword 0x90010064
		opword 0xEC602828
		opword 0xEC042828
		opword 0x90A10060
		opword 0xEFE03024
		opword 0xC8010060
		opword 0xEC802828
		bl angleABf
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC7F1028
		opword 0xFC030040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x3BA00001
		opword 0xEC63002A
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC5F102A
		opword 0xFC020040
		opword 0x4081000C
		opword 0xEC420028
		opword 0x3BA00002
		opword 0x2C1D0001
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800050
		opword 0xFC011840
		opword 0x40800048
		opword 0x3B800001
		opword 0x48000040
		opword 0x2C1D0002
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800030
		opword 0xFC011840
		opword 0x40800028
		opword 0x3B800001
		opword 0x48000020
		opword 0x2C1D0000
		opword 0x40820018
		opword 0xFC011840
		opword 0x4180000C
		opword 0xFC020840
		opword 0x40800008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820070
		opword 0xFC40E850
		lfs f3, float_0p2_8041ad4c(r2)
		opword 0xFC20E050
		lfs f0, float_1_8041ad14(r2)
		opword 0xEFA3E8BA
		opword 0xEF83E07A
		opword 0xFC20EA10
		opword 0xFC010040
		opword 0x40800008
		lfs f29, float_0_8041acbc(r2)
		opword 0xFC20E210
		lfs f0, float_1_8041ad14(r2)
		opword 0xFC010040
		opword 0x40800008
		lfs f28, float_0_8041acbc(r2)
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC00E800
		opword 0x40820028
		opword 0xFC00E000
		opword 0x40820020
		lfs f1, float_180_8041acc8(r2)
		opword 0xC01F019C
		opword 0xEC21002A
		bl revise360
		opword 0xD03F019C
		opword 0xC01F019C
		opword 0xD01F01A0
		lfs f1, rollData(r13)
		lfs f0, float_0p05_8041ad6c(r2)
		opword 0xA81F004E
		opword 0xEFE10024
		lfs f26, float_1_8041ad14(r2)
		opword 0x2C000000
		opword 0x4082007C
		opword 0xC01F0214
		opword 0xFC000210
		opword 0xFC00D040
		opword 0x4C411382
		opword 0x40820068
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60E890
		opword 0xFC80E050
		opword 0xFC400890
		bl angleABf
		opword 0xC05F0220
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC020040
		opword 0x40810024
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x40810010
		la r3, rollData(r13)
		opword 0xC3430024
		opword 0x4800002C
		lfs f26, float_1_8041ad14(r2)
		opword 0x48000024
		opword 0x40800020
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x40800010
		la r3, rollData(r13)
		opword 0xC3430024
		opword 0x48000008
		lfs f26, float_1_8041ad14(r2)
		opword 0xEFFF06B2
		opword 0xEF5C0732
		opword 0xEC1F07F2
		opword 0xEC3DD77A
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820010
		lfs f0, float_0p025_8041ad80(r2)
		opword 0xEFBEE83A
		opword 0x48000028
		lfs f0, float_0p025_8041ad80(r2)
		opword 0xFC20F850
		opword 0xEFBEE83A
		opword 0xFC1D0840
		opword 0x40800008
		opword 0xFFA00890
		opword 0xFC1DF840
		opword 0x40810008
		opword 0xFFA0F890
		lfs f1, rollData(r13)
		lfs f0, float_0p05_8041ad6c(r2)
		opword 0xA81F004E
		opword 0xEFE10024
		lfs f30, float_1_8041ad14(r2)
		opword 0x2C000000
		opword 0x4082007C
		opword 0xC01F0214
		opword 0xFC000210
		opword 0xFC00F040
		opword 0x4C411382
		opword 0x40820068
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60E890
		opword 0xFC80E050
		opword 0xFC400890
		bl angleABf
		opword 0xC05F0218
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC020040
		opword 0x40810024
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x40810010
		la r3, rollData(r13)
		opword 0xC3C30024
		opword 0x4800002C
		lfs f30, float_1_8041ad14(r2)
		opword 0x48000024
		opword 0x40800020
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x40800010
		la r3, rollData(r13)
		opword 0xC3C30024
		opword 0x48000008
		lfs f30, float_1_8041ad14(r2)
		opword 0xEFFF07B2
		opword 0xEC3DD77A
		opword 0xEC1F07F2
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820010
		lfs f0, float_0p025_8041ad80(r2)
		opword 0xEF9BE03C
		opword 0x48000028
		lfs f0, float_0p025_8041ad80(r2)
		opword 0xFC20F850
		opword 0xEF9BE03C
		opword 0xFC1C0840
		opword 0x40800008
		opword 0xFF800890
		opword 0xFC1CF840
		opword 0x40810008
		opword 0xFF80F890
		bl marioGetPtr
		opword 0x80630288
		opword 0xD3A30000
		bl marioGetPtr
		opword 0xFFE0E050
		lfs f1, float_0_8041acbc(r2)
		opword 0x80630288
		opword 0xFC60E890
		opword 0xFC400890
		opword 0xFC80F890
		opword 0xD3830004
		bl angleABf
		opword 0xFFC00890
		lfs f2, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC2207B2
		opword 0xEF610024
		opword 0xFC20D890
		bl cos
		opword 0xFF400818
		opword 0xFC20D890
		bl sin
		opword 0xFC000818
		lfs f1, float_0_8041acbc(r2)
		opword 0xEC9C06B2
		opword 0xFC400890
		opword 0xEC7D0032
		bl distABf
		lfs f0, float_0p05_8041ad6c(r2)
		opword 0x3B800000
		opword 0xEF600072
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820014
		opword 0x800302A4
		opword 0x540005EF
		opword 0x41820008
		opword 0x3B800001
		opword 0x2C1C0000
		opword 0x40820060
		opword 0xA81F004E
		opword 0x2C000000
		opword 0x40820054
		lfs f1, float_0_8041acbc(r2)
		opword 0xFC60E890
		opword 0xFC80F890
		opword 0xFC400890
		bl angleABf
		opword 0x801F02A4
		opword 0xFFC00890
		opword 0x540003DF
		opword 0x40820030
		opword 0xC03F0224
		lfs f0, float_0p05_8041ad6c(r2)
		opword 0xEF7B0072
		opword 0xFC1B0040
		opword 0x40800008
		lfs f27, float_0_8041acbc(r2)
		lfs f0, float_0_8041acbc(r2)
		opword 0xD37F0180
		opword 0xFC1B0000
		opword 0x41820008
		opword 0xD3DF01A0
		opword 0xC03F0180
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC010000
		opword 0x4182003C
		bl marioGetPtr
		opword 0x7C7D1B78
		opword 0x806302A8
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x40820048
		opword 0x389D008C
		opword 0x3860017B
		bl psndSFXOn_3D
		opword 0x907D02A8
		opword 0x801D02A4
		opword 0x60001000
		opword 0x901D02A4
		opword 0x48000028
		bl marioGetPtr
		opword 0x7C7D1B78
		opword 0x806302A8
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820010
		bl psndSFXOff
		opword 0x3800FFFF
		opword 0x901D02A8
		la r3, rollData(r13)
		opword 0xC03F01A8
		opword 0xC3830010
		bl toMovedir
		opword 0xC01F01A0
		opword 0x3C004330
		lfs f5, float_10_8041ace4(r2)
		opword 0x38800000
		opword 0x90010070
		opword 0x7C832378
		opword 0xEC650032
		opword 0xC89E0090
		lfs f2, float_90_8041acd8(r2)
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC60181E
		opword 0xD8610078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8610070
		opword 0xEC632028
		opword 0xEC832824
		opword 0xEC641028
		opword 0xFC030040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38800001
		opword 0xEC63002A
		lfs f2, float_90_8041acd8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC44102A
		opword 0xFC020040
		opword 0x4081000C
		opword 0xEC420028
		opword 0x38800002
		opword 0x2C040001
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800050
		opword 0xFC011840
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C040002
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800030
		opword 0xFC011840
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C040000
		opword 0x40820018
		opword 0xFC011840
		opword 0x4180000C
		opword 0xFC020840
		opword 0x40800008
		opword 0x38600001
		opword 0xC01F0180
		opword 0x2C030001
		opword 0xEC400732
		opword 0x4082000C
		lfs f1, float_neg1_8041ad84(r2)
		opword 0x48000008
		lfs f1, float_1_8041ad14(r2)
		opword 0xC01F00C4
		opword 0xEC22007A
		bl revise360
		opword 0xD03F00C4
		opword 0xA81F004E
		opword 0x2C000000
		opword 0x40820500
		opword 0x3B800000
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820014
		opword 0x800302A4
		opword 0x540005EF
		opword 0x41820008
		opword 0x3B800001
		opword 0x2C1C0000
		opword 0x408204D4
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC1B0000
		opword 0x418204C8
		opword 0xC3FF019C
		bl marioGetPtr
		lfs f4, float_10_8041ace4(r2)
		opword 0x3C004330
		opword 0x38800000
		opword 0x90010070
		opword 0xEC4407F2
		opword 0xC87E0090
		lfs f1, float_135_8041ace8(r2)
		opword 0x7C7D1B78
		lfs f0, float_0_8041acbc(r2)
		opword 0x7C832378
		opword 0xFC40101E
		opword 0xD8410078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8410070
		opword 0xEC421828
		opword 0xEC622024
		opword 0xEC430828
		opword 0xFC020040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38800001
		opword 0xEC42002A
		lfs f1, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC23082A
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC210028
		opword 0x38800002
		opword 0x2C040001
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800050
		opword 0xFC1E1040
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C040002
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800030
		opword 0xFC1E1040
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C040000
		opword 0x40820018
		opword 0xFC1E1040
		opword 0x4180000C
		opword 0xFC01F040
		opword 0x40800008
		opword 0x38600001
		opword 0x2C030001
		opword 0x40820014
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC20F82A
		bl revise360
		opword 0xFFE00890
		lfs f3, float_10_8041ace4(r2)
		opword 0x3C004330
		opword 0xC03D0198
		opword 0xEC0307F2
		opword 0x90010070
		opword 0xEC230072
		opword 0xC85E0090
		opword 0x90010060
		opword 0xFC00001E
		opword 0xFC20081E
		opword 0xD8010068
		opword 0xD8210078
		opword 0x8001006C
		opword 0x8061007C
		opword 0x6C008000
		opword 0x6C638000
		opword 0x90010064
		opword 0x90610074
		opword 0xC8010060
		opword 0xC8210070
		opword 0xEC001028
		opword 0xEC211028
		opword 0xEC001824
		opword 0xEC211824
		opword 0xEC200828
		bl revise360
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4082002C
		opword 0xEC3FF028
		lfs f0, float_90_8041acd8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4081003C
		opword 0xFC1EF840
		opword 0x40810034
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFFF002A
		opword 0x48000028
		opword 0xEC3FF028
		lfs f0, float_90_8041acd8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810014
		opword 0xFC1EF840
		opword 0x4080000C
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFDE002A
		lfs f4, float_10_8041ace4(r2)
		opword 0x3C004330
		opword 0x38800000
		opword 0x90010070
		opword 0xEC4407F2
		opword 0xC87E0090
		lfs f1, float_90_8041acd8(r2)
		opword 0x7C832378
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC40101E
		opword 0xD8410078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8410070
		opword 0xEC421828
		opword 0xEC622024
		opword 0xEC430828
		opword 0xFC020040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38800001
		opword 0xEC42002A
		lfs f1, float_90_8041acd8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC23082A
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC210028
		opword 0x38800002
		opword 0x2C040001
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800050
		opword 0xFC1E1040
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C040002
		opword 0x4082001C
		opword 0xFC01F040
		opword 0x40800030
		opword 0xFC1E1040
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C040000
		opword 0x40820018
		opword 0xFC1E1040
		opword 0x4180000C
		opword 0xFC01F040
		opword 0x40800008
		opword 0x38600001
		opword 0x2C030000
		opword 0x40820034
		opword 0xEC3FF028
		lfs f0, float_180_8041acc8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40810020
		opword 0xFC1FF040
		opword 0x40810010
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFFF0028
		opword 0x4800000C
		lfs f0, float_360_8041ace0(r2)
		opword 0xEFDE0028
		opword 0xEC1EF828
		lfs f1, float_1p2_8041acec(r2)
		opword 0xEFE1F83A
		opword 0xFC20F890
		bl revise360
		opword 0xFFE00890
		opword 0xC03F01A8
		bl toMovedir
		opword 0x881F0043
		opword 0x7C000775
		opword 0x41820010
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC20082A
		bl revise360
		lfs f5, float_10_8041ace4(r2)
		opword 0x3C004330
		opword 0x38800000
		opword 0x90010070
		opword 0xEC6507F2
		opword 0xC89E0090
		lfs f2, float_135_8041ace8(r2)
		opword 0x7C832378
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC60181E
		opword 0xD8610078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8610070
		opword 0xEC632028
		opword 0xEC832824
		opword 0xEC641028
		opword 0xFC030040
		opword 0x40800010
		lfs f0, float_360_8041ace0(r2)
		opword 0x38800001
		opword 0xEC63002A
		lfs f2, float_135_8041ace8(r2)
		lfs f0, float_360_8041ace0(r2)
		opword 0xEC44102A
		opword 0xFC020040
		opword 0x4081000C
		opword 0xEC420028
		opword 0x38800002
		opword 0x2C040001
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800050
		opword 0xFC011840
		opword 0x40800048
		opword 0x38600001
		opword 0x48000040
		opword 0x2C040002
		opword 0x4082001C
		opword 0xFC020840
		opword 0x40800030
		opword 0xFC011840
		opword 0x40800028
		opword 0x38600001
		opword 0x48000020
		opword 0x2C040000
		opword 0x40820018
		opword 0xFC011840
		opword 0x4180000C
		opword 0xFC020840
		opword 0x40800008
		opword 0x38600001
		opword 0x2C030001
		opword 0x40820014
		opword 0x887F0043
		opword 0x38030001
		opword 0x540007FE
		opword 0x981F0043
		lfs f1, float_270_8041acdc(r2)
		opword 0xC01F0198
		opword 0x881F0043
		opword 0xEC01002A
		opword 0x7C000775
		opword 0xEC20F828
		opword 0x4182000C
		lfs f0, float_neg180_8041ad88(r2)
		opword 0x48000008
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03F01A8
		lfs f0, float_200_8041ad8c(r2)
		opword 0xC03F01A8
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820038
		lfs f1, float_270_8041acdc(r2)
		opword 0xC01F0198
		opword 0x881F0043
		opword 0xEC01002A
		opword 0x7C000775
		opword 0xEC20F828
		opword 0x4182000C
		lfs f0, float_neg180_8041ad88(r2)
		opword 0x48000008
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03F01A8
		opword 0xC03F01A8
		lfs f0, float_170_8041ad90(r2)
		opword 0xFC010040
		opword 0x40800038
		lfs f1, float_270_8041acdc(r2)
		opword 0xC01F0198
		opword 0x881F0043
		opword 0xEC01002A
		opword 0x7C000775
		opword 0xEC20F828
		opword 0x4182000C
		lfs f0, float_neg180_8041ad88(r2)
		opword 0x48000008
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC21002A
		bl revise360
		opword 0xD03F01A8
		opword 0xD3FF01A0
		opword 0xD3FF019C
		lfs f1, float_0_8041acbc(r2)
		opword 0xC01F0220
		opword 0xFC010000
		opword 0x41820038
		lfs f2, float_3p1416_8041acc4(r2)
		opword 0xC03F01A8
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC220072
		opword 0xEC210024
		bl sin
		opword 0xC01F0220
		opword 0xFC200818
		opword 0xFC000050
		opword 0xEC200072
		bl revise360
		opword 0xD03F00BC
		opword 0x48000008
		opword 0xD03F00BC
		opword 0x881F024E
		opword 0x7C000775
		opword 0x40820010
		opword 0x881F024F
		opword 0x7C000775
		opword 0x41820010
		opword 0x801F02A4
		opword 0x60004000
		opword 0x901F02A4
		opword 0xC03F0180
		lfs f0, float_0_8041acbc(r2)
		opword 0xFC010000
		opword 0x41820018
		bl marioGetPtr
		lfs f1, float_0_8041acbc(r2)
		lfs f0, float_0p004_8041ad30(r2)
		opword 0xD0230148
		opword 0xD0030158
		bl marioGetPtr
		lfs f0, float_100_8041acb8(r2)
		opword 0x7C7F1B78
		opword 0x813E0054
		opword 0x38610018
		opword 0xD0010014
		opword 0x38810024
		opword 0x811E0058
		opword 0x38A10030
		opword 0x817F008C
		opword 0x38C1003C
		opword 0x815F0090
		opword 0x38E10014
		opword 0x801E005C
		opword 0x9141001C
		opword 0x91610018
		opword 0xC021001C
		opword 0x815F0094
		opword 0x91410020
		opword 0xC01F01B8
		opword 0xEC01002A
		opword 0x91210024
		opword 0x91010028
		opword 0xD001001C
		opword 0x9001002C
		bl marioHitCheckVec
		opword 0x28030000
		opword 0x41820224
		opword 0xC001003C
		opword 0xC0210044
		opword 0xEC400032
		lfs f0, float_0_8041acbc(r2)
		opword 0xEC210072
		opword 0xEC62082A
		opword 0xFC030040
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89E0070
		opword 0xC85E0078
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
		opword 0xC81E0080
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
		lfs f1, float_0_8041acbc(r2)
		opword 0xC0010040
		opword 0xFC400890
		opword 0xFC800050
		bl angleABf
		lfs f0, float_0p5_8041acc0(r2)
		opword 0x3C004330
		opword 0x90010070
		opword 0xFC600A10
		opword 0xEC40082A
		opword 0xC81E0088
		opword 0xC83E0090
		opword 0xFC030040
		opword 0xFC00101E
		opword 0xD8010078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC400828
		opword 0x40800060
		lfs f1, float_3p1416_8041acc4(r2)
		lfs f0, float_180_8041acc8(r2)
		opword 0xEC2100B2
		opword 0xEF410024
		opword 0xFC20D090
		bl sin
		opword 0xFC000818
		opword 0xFC20D090
		opword 0xD001000C
		bl cos
		lfs f3, float_5_8041acd0(r2)
		opword 0xFCA00818
		opword 0xC001000C
		lfs f4, float_6_8041accc(r2)
		opword 0xEC430032
		lfs f1, float_neg4_8041acd4(r2)
		opword 0xEC030172
		opword 0xD0A10010
		opword 0xEC44102A
		opword 0xEC01002A
		opword 0xD05F0098
		opword 0xD01F009C
		opword 0x48000088
		lfs f1, float_90_8041acd8(r2)
		opword 0x3861000C
		opword 0x38810010
		bl sincosf
		lfs f0, float_100_8041acb8(r2)
		opword 0x38610018
		opword 0x80FE0060
		opword 0x38810024
		opword 0xD0010014
		opword 0x38A10030
		opword 0x801E0068
		opword 0x38C1003C
		opword 0x90E10048
		opword 0x38E10014
		opword 0xC021000C
		opword 0x90010050
		opword 0xC0010010
		opword 0xD0210048
		opword 0x813E0064
		opword 0xD0010050
		opword 0x801F008C
		opword 0x815F0090
		opword 0x81010048
		opword 0x90010018
		opword 0x80010050
		opword 0x9141001C
		opword 0x815F0094
		opword 0x9121004C
		opword 0x91410020
		opword 0x91010024
		opword 0x91210028
		opword 0x9001002C
		bl marioHitCheckVec
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void roll_upstairs_on(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    mario->flags |= 0x40000;
    mario->flags |= 0x80;
    marioClearJumpPara();
    mario->multiTimer = 3;
    mario->jumpVelocityY = (MF(0x1c4) - mario->position.y) / (f32)(s32)mario->multiTimer;
    mario->jumpVelocityY = 4.0f;
    mario->jumpAccelerationY = -0.42f;
    mario->jumpJerkY = 0.04f;
    mario->jumpSnapY = -0.01f;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0x80030000
		opword 0x64000004
		opword 0x90030000
		opword 0x80030000
		opword 0x60000080
		opword 0x90030000
		bl marioClearJumpPara
		opword 0x38600003
		opword 0x3C004330
		opword 0x907F0048
		lis r3, double_to_int_802c5dd0@ha
		lfd f1, double_to_int_802c5dd0@l(r3)
		opword 0x809F0048
		opword 0x90010008
		opword 0x6C808000
		opword 0xC09F01C4
		opword 0x9001000C
		opword 0xC05F0090
		opword 0xC8010008
		opword 0xECA41028
		lfs f3, float_4_8041acf4(r2)
		opword 0xEC800828
		lfs f2, float_neg0p42_8041acf8(r2)
		lfs f1, float_0p04_8041acfc(r2)
		lfs f0, float_neg0p01_8041ad00(r2)
		opword 0xEC852024
		opword 0xD09F007C
		opword 0xD07F007C
		opword 0xD05F0080
		opword 0xD03F0084
		opword 0xD01F0088
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#pragma dont_inline on
void roll_upstairs(void) {
    MarioWork* mario = marioGetPtr();
    mario->position.y = mario->position.y + mario->jumpVelocityY;
    if ((s32)--mario->multiTimer <= 0) {
        mario->flags &= ~0x80;
        mario->flags &= ~0x40;
        mario->flags &= ~0x40000;
    }
}

#pragma dont_inline reset

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void mot_fall_roll(void) {
#ifdef NONMATCHING
    MarioWork* mario = marioGetPtr();
    f32 spd = marioGetFallSpd();
    f32 y;
    HitEntry* h;
    if (spd < -10.0f) {
        spd = -10.0f;
    }
    h = marioChkLandon(&y, spd);
    if (h) {
        mario->position.y = y;
        mario->hitobjStandOn = h;
        mario->hitobjJumpFrom = 0;
    } else {
        mario->position.y += spd;
    }
    if (mario->hitobjStandOn) {
        marioLandOn();
        roll_flyout_flag2 = 0;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0x93E1001C
		bl marioGetPtr
		opword 0x7C7F1B78
		bl marioGetFallSpd
		opword 0xFFE00890
		lfs f0, float_neg10_8041acf0(r2)
		opword 0xFC1F0040
		opword 0x40800008
		opword 0xFFE00090
		opword 0xFC20F890
		opword 0x38610008
		bl marioChkLandon
		opword 0x28030000
		opword 0x4182001C
		opword 0xC0010008
		opword 0x38000000
		opword 0xD01F0090
		opword 0x907F01E4
		opword 0x901F01E8
		opword 0x48000010
		opword 0xC01F0090
		opword 0xEC00F82A
		opword 0xD01F0090
		opword 0x801F01E4
		opword 0x28000000
		opword 0x41820010
		bl marioLandOn
		opword 0x38000000
		stw r0, roll_flyout_flag2(r13)
		opword 0xE3E10028
		opword 0x80010034
		opword 0xCBE10020
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210030
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
static inline void marioRollCan(void) {
    MarioWork* mario = marioGetPtr();
    f32 v26;
    {
        f32 s;
        f32 c;
        f32 dist;
        Vec pos;
        Vec dir;
        Vec out;
        Vec nrm;
        Vec d2;
        dist = 100.0f;
        pos = mario->position;
        pos.y = pos.y + mario->wPlayerCollisionBox.y;
        dir = (Vec){0.0f, -1.0f, 0.0f};
        if (marioHitCheckVec(&pos, &dir, &out, &nrm, &dist)) {
            f32 sq = roll_sqrtf(nrm.x * nrm.x + nrm.z * nrm.z);
            f32 ang = angleABf(0.0f, 0.0f, sq, -nrm.y);
            f32 r = (f32)(s32)(0.5f + ang);
            if (__fabsf(ang) < 45.0) {
                v26 = 3.1415927f * r / 180.0f;
                s = (f32)sin(v26);
                c = (f32)cos(v26);
                {
                    f32 t1 = 5.0f * s;
                    f32 t2 = 5.0f * c;
                    mario->dispOfs.x = 6.0f + t1;
                    mario->dispOfs.y = -4.0f + t2;
                }
            } else {
                sincosf(&s, &c, 90.0f);
                dist = 100.0f;
                pos = mario->position;
                d2 = (Vec){0.0f, 0.0f, 0.0f};
                d2.x = s;
                d2.z = c;
                dir = d2;
                marioHitCheckVec(&pos, &dir, &out, &nrm, &dist);
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void marioRollStrippedPool(void) {
    MarioWork* mario = marioGetPtr();
    MF(0x98) = 100.0f;
    MF(0x9c) = 0.0f;
    MF(0xa0) = 0.5f;
    MF(0xa4) = 3.1415927f;
    MF(0xa8) = 180.0f;
    MF(0xac) = 6.0f;
    MF(0xb0) = 5.0f;
    MF(0xb4) = -4.0f;
    MF(0xb8) = 90.0f;
    MF(0xbc) = 270.0f;
    MF(0xc0) = 360.0f;
    MF(0xc4) = 10.0f;
    MF(0xc8) = 135.0f;
    MF(0xcc) = 1.2f;
    MF(0xd0) = roll_sqrtf(MF(0xd4));
    MF(0xd8) = __fabsf(MF(0xdc)) < 45.0;
}
#endif


// prototypes for asm stopgap forward references
void mot_fall_roll(void);
void roll_upstairs(void);
void roll_upstairs_on(void);
void mot_roll(void);
void marioReInit_roll(void);
void rollEvtJumpSetup(void);
void marioSetRollDispDir(void);
void marioRollForceCancel(void);
void mot_roll_post(void);
s32 marioRollCancel(void);
s32 unk_8009f9c8(void);
void marioForceRollAnime(void);
void marioResetRollSpd(void);
s32 getRollEvtFlag(void);
void clrRollEvtFlag(void);
void setRollEvtFlag(void);
s32 marioRollKeyDisable(void);
s32 unk_8009fcbc(void);
void marioRollFixOn(void);

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c5d40[3] = {0.0f, 40.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d58[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d70[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d7c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d88[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5d94[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5da0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 gap_04_802C5DAC_rodata = 0x00000000;
__declspec(section ".rodata") const f64 double_0p5_802c5db0 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c5db8 = 3.0;
__declspec(section ".rodata") const f64 double_0_802c5dc0 = 0.0;
__declspec(section ".rodata") const f64 double_45_802c5dc8 = 45.0;
__declspec(section ".rodata") const f64 double_to_int_802c5dd0 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802C5DD8[] = "p_roll\0";
__declspec(section ".rodata") const char str_802C5DE0[] = "PM_R_1A";
__declspec(section ".rodata") const char str_802C5DE8[] = "PM_R_1B";
__declspec(section ".rodata") const char str_802C5DF0[] = "PM_R_1C";
__declspec(section ".rodata") const char str_802C5DF8[] = "eki_04\0";
__declspec(section ".sdata2") const f32 float_100_8041acb8 = 100.0f;
__declspec(section ".sdata2") const f32 float_0_8041acbc = 0.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041acc0 = 0.5f;
__declspec(section ".sdata2") const f32 float_3p1416_8041acc4 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_8041acc8 = 180.0f;
__declspec(section ".sdata2") const f32 float_6_8041accc = 6.0f;
__declspec(section ".sdata2") const f32 float_5_8041acd0 = 5.0f;
__declspec(section ".sdata2") const f32 float_neg4_8041acd4 = -4.0f;
__declspec(section ".sdata2") const f32 float_90_8041acd8 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_8041acdc = 270.0f;
__declspec(section ".sdata2") const f32 float_360_8041ace0 = 360.0f;
__declspec(section ".sdata2") const f32 float_10_8041ace4 = 10.0f;
__declspec(section ".sdata2") const f32 float_135_8041ace8 = 135.0f;
__declspec(section ".sdata2") const f32 float_1p2_8041acec = 1.2f;
__declspec(section ".sdata2") const f32 float_neg10_8041acf0 = -10.0f;
__declspec(section ".sdata2") const f32 float_4_8041acf4 = 4.0f;
__declspec(section ".sdata2") const f32 float_neg0p42_8041acf8 = -0.42f;
__declspec(section ".sdata2") const f32 float_0p04_8041acfc = 0.04f;
__declspec(section ".sdata2") const f32 float_neg0p01_8041ad00 = -0.01f;
__declspec(section ".sdata2") const char str_8041AD04[] = "M_I_U\0\0";
__declspec(section ".sdata2") const f32 float_14p8_8041ad0c = 14.8f;
__declspec(section ".sdata2") const f32 float_neg6_8041ad10 = -6.0f;
__declspec(section ".sdata2") const f32 float_1_8041ad14 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p4_8041ad18 = 0.4f;
__declspec(section ".sdata2") const f32 float_0p01_8041ad1c = 0.01f;
__declspec(section ".sdata2") const f32 float_2_8041ad20 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041ad24 = 0.1f;
__declspec(section ".sdata2") const f32 float_3_8041ad28 = 3.0f;
__declspec(section ".sdata2") const f32 float_neg3_8041ad2c = -3.0f;
__declspec(section ".sdata2") const f32 float_0p004_8041ad30 = 0.004f;
__declspec(section ".sdata2") const char str_8041AD34[] = "M_S_1\0\0";
__declspec(section ".sdata2") const f32 float_1p4_8041ad3c = 1.4f;
__declspec(section ".sdata2") const f32 float_1p45_8041ad40 = 1.4499999f;
__declspec(section ".sdata2") const f32 float_0p35_8041ad44 = 0.35f;
__declspec(section ".sdata2") const f32 float_1p05_8041ad48 = 1.05f;
__declspec(section ".sdata2") const f32 float_0p2_8041ad4c = 0.2f;
__declspec(section ".sdata2") const f32 float_40_8041ad50 = 40.0f;
__declspec(section ".sdata2") const f32 float_2p85_8041ad54 = 2.85f;
__declspec(section ".sdata2") const f32 float_neg0p14_8041ad58 = -0.14f;
__declspec(section ".sdata2") const f32 float_0p08_8041ad5c = 0.08f;
__declspec(section ".sdata2") const f32 float_neg0p02_8041ad60 = -0.02f;
__declspec(section ".sdata2") const f32 float_neg0p03_8041ad64 = -0.03f;
__declspec(section ".sdata2") const f32 float_neg0p002_8041ad68 = -0.002f;
__declspec(section ".sdata2") const f32 float_0p05_8041ad6c = 0.05f;
__declspec(section ".sdata2") const f32 float_neg100_8041ad70 = -100.0f;
__declspec(section ".sdata2") const f32 float_neg0p05_8041ad74 = -0.05f;
__declspec(section ".sdata2") const f32 float_0p6_8041ad78 = 0.6f;
__declspec(section ".sdata2") const f32 float_6p4_8041ad7c = 6.4f;
__declspec(section ".sdata2") const f32 float_0p025_8041ad80 = 0.025f;
__declspec(section ".sdata2") const f32 float_neg1_8041ad84 = -1.0f;
__declspec(section ".sdata2") const f32 float_neg180_8041ad88 = -180.0f;
__declspec(section ".sdata2") const f32 float_200_8041ad8c = 200.0f;
__declspec(section ".sdata2") const f32 float_170_8041ad90 = 170.0f;
__declspec(section ".sdata2") const u32 gap_09_8041AD94_sdata2 = 0x00000000;

#endif