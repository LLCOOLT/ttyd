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

f32 roll_grx;
f32 roll_grz;
s32 roll_flyout_flag2;
static __declspec(section ".rodata") Vec rollOfs = {0.0f, 40.0f, 0.0f};

f32 rollData[] = {3.0f, -0.05f, -0.5f, 0.5f, 7.0f, 180.0f, 140.0f, 10.0f, 1.2f, 2.0f, 0.8f};

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

static inline f32 trunc10(f32 x) {
    s32 i = (s32)(10.0f * x);
    f32 f = (f32)i;
    return f / 10.0f;
}

static inline s32 angOutT(f32 center, f32 half, f32 x) {
    s32 w = 0;
    s32 r = w;
    f32 c = trunc10(center);
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

static inline s32 angOut(f32 center, f32 half, f32 x) {
    return angOutT(center, half, x);
}

/* repurposed unused inline: angOut on the mario stick angle, with everything read inside */
// FAKE: k025/rabs/rollRad/rollCos/rSin are invented one-line inline helpers. Their result temps get
// later inline numbering, which gives the target FPR colouring in mot_roll (fmadds operand order, makeVec c
// in f31) and marioRollCan (v26 in f26, fabs/sin/cos volatiles). Behaviour-identical to the expressions they wrap.
static inline f32 k025(void) { return 0.025f; }
static inline f32 rSin(f32 a) { return (f32)sin(a); }
static inline f32 rabs(f32 x) { return __fabsf(x); }
static inline f32 rollRad(f32 d) { return 3.1415927f * d / 180.0f; }
static inline f32 rollCos(f32 a) { return (f32)cos(a); }
static inline s32 makeVec(f32 half) {
    s32 w = 0;
    s32 r = w;
    MarioWork* m = marioGetPtr();
    f32 c = (f32)(s32)(10.0f * m->moveDirection) / 10.0f;
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

#define DISPDIR_BODY(a, b, m2)                                                                    \
    if (angOut(b, 135.0f, a) == 1) {                                                              \
        b = revise360(180.0f + b);                                                                \
    }                                                                                             \
    {                                                                                             \
        f32 ty_ = trunc10((m2)->targetYaw); f32 dd = revise360(-(ty_ - trunc10(b))); \
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

// FAKE: marioSetRollDispDir copy of DISPDIR_BODY: dd = tb_ - ty_ (was -(ty_ - tb_); differs only in the sign of zero, and dd is
// only compared with 180) and a dead int-guarded re-def of ty_ (COLOURING M) keep ty_ as a named value created before tb_, as the target fsubs f1,f0,f1
#define DISPDIR_BODY2(a, b, m2)                                                                    \
    if (angOut(b, 135.0f, a) == 1) {                                                              \
        b = revise360(180.0f + b);                                                                \
    }                                                                                             \
    {                                                                                             \
        s32 g_; f32 ty_; f32 dd; s32 sgn; f32 tb_; ty_ = trunc10((m2)->targetYaw); tb_ = trunc10(b); g_ = 0; if (g_ != 0) { ty_ = 0.0f; } dd = revise360(tb_ - ty_); sgn = (dd < 180.0f) ? 0 : 1;                                                          \
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

void marioResetRollSpd(void) {
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
}

void marioForceRollAnime(void) {
    MarioWork* mario = marioGetPtr();
    marioPaperOff();
    if (mario) {
    }
    marioChgPaper(0);
    marioPaperOn("p_roll");
    marioChgPose("M_I_U");
    marioChgPaper("PM_R_1B");
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

void mot_roll_post(void) {
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
}

void marioRollForceCancel(void) {
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
}

void marioSetRollDispDir(void) {
    MarioWork* mario = marioGetPtr();
    f32 b, a;
    MarioWork* m2;
    a = mario->directionView;
    b = mario->moveDirection;
    m2 = marioGetPtr();
    DISPDIR_BODY2(a, b, m2)
}

void rollEvtJumpSetup(void) {
    MarioWork* mario = marioGetPtr();
    camFollowYOff();
    mario->flags |= 0x10000;
    mario->airTimer = 1;
}

void marioReInit_roll(void) {
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
}

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

void mot_roll(void) {
    MarioWork* mario = marioGetPtr();
    f32 v31;
    f32 v29;
    f32 v28;
    f32 v30;
    f32 v27;
    f32 v26;
    f32 tcA;
    f32 nx;
    f32 nz;
    f32 a31;
    f32 b31;
    f32 s;
    f32 rd;
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
    nx = 0.0f;
    nz = nx;
    if (!(mario->flags & 0x30000)) {
        f32 a26, a30;
        a26 = (f32)(s32)(s8)mario->wStickDir1;
        a30 = (f32)(s32)(s8)mario->wStickDir2;
        nz = distABf(nx, nx, a26, a30);
        v31 = angleABf(0.0f, 0.0f, a26, a30);
        v31 = revise360(mario->targetYaw + v31);
        v26 = 3.1415927f * v31 / 180.0f;
        nx = nz * (f32)sin(v26);
        nz = nz * -(f32)cos(v26);
        v31 = angleABf(0.0f, 0.0f, nx, nz);
        tcA = MF(0x1a0);
        if (angOut(tcA, 135.0f, v31) == 1) {
            nz = distABf(0.0f, 0.0f, nx, nz);
            nx = -nz * (f32)sin(3.1415927f * MF(0x1a0) / 180.0f);
            nz = nz * (f32)cos(3.1415927f * MF(0x1a0) / 180.0f);
        }
    }
    if (!(mario->flags & 0x30000) && !(MI(0x2a4) & 0x20)) {
        v31 = angleABf(0.0f, 0.0f, v29, -v28);
        if (MF(0x220) > 0.05f) {
            v26 = (v31 > 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x220) / 180.0f);
                t = t * v26;
                nx = nx - t;
            }
            if (nx <= -100.0f) {
                nx = -100.0f;
            }
        } else if (MF(0x220) < -0.05f) {
            v26 = (v31 < 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x220) / 180.0f);
                t = t * v26;
                nx = nx - t;
            }
            if (nx >= 100.0f) {
                nx = 100.0f;
            }
        }
        if (MF(0x218) > 0.05f) {
            v26 = (v31 > 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x218) / 180.0f);
                t = t * v26;
                nz = nz - t;
            }
            if (nz <= -100.0f) {
                nz = -100.0f;
            }
        } else if (MF(0x218) < -0.05f) {
            v26 = (v31 < 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * MF(0x218) / 180.0f);
                t = t * v26;
                nz = nz - t;
            }
            if (nz >= 100.0f) {
                nz = 100.0f;
            }
        }
        v31 = angleABf(0.0f, 0.0f, nx, nz);
        tcA = MF(0x1a0);
        if (angOut(tcA, 135.0f, v31) == 1) {
            nz = distABf(0.0f, 0.0f, nx, -nz);
            nx = -nz * (f32)sin(3.1415927f * MF(0x1a0) / 180.0f);
            nz = nz * (f32)cos(3.1415927f * MF(0x1a0) / 180.0f);
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
    if (mario->forceMoveTimer == 0 && !nx && !nz) {
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
        {
            f32 l = rollData[3];
            if (__fabsf(v29) < l) {
                v29 = 0.0f;
            }
        }
        {
            f32 l = rollData[3];
            if (__fabsf(v28) < l) {
                v28 = 0.0f;
            }
        }
    } else {  // correctness: target runs the speed clamp only on this path (first branch jumps past it)
        if ((MI(0x2a4) & 0x10) && MF(0x220) == 0.0f) {
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
        a31 = rollData[0] / 0.05f;
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
        a31 = a31 * v26;
        v26 = v28 * v28;
        if (v29 * v29 + v26 <= a31 * a31) {
            v29 = nx * k025() + v29;
        } else {
            f32 n = -a31;
            v29 = nx * k025() + v29;
            if (v29 < n) {
                v29 = n;
            }
            if (v29 > a31) {
                v29 = a31;
            }
        }
        b31 = rollData[0] / 0.05f;
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
        b31 = b31 * v30;
        if (v29 * v29 + v26 <= b31 * b31) {
            v28 = v28 - nz * k025();
        } else {
            f32 n = -b31;
            v28 = v28 - nz * k025();
            if (v28 < n) {
                v28 = n;
            }
            if (v28 > b31) {
                v28 = b31;
            }
        }
    }
    RW()->x = v29;
    RW()->z = v28;
    v31 = -v28;
    v30 = angleABf(0.0f, 0.0f, v29, v31);
    v27 = 3.1415927f * v30 / 180.0f;
    v26 = rollCos(v27);
    v27 = distABf(0.0f, 0.0f, v29 * (f32)sin(v27), v28 * v26);
    s = 0.05f * v27;
    if (!getRollEvtFlag() && mario->forceMoveTimer == 0) {
        v30 = angleABf(0.0f, 0.0f, v29, v31);
        if (!(MI(0x2a4) & 0x10000)) {
            s = s * mario->playerGravity;
            if (s < 0.05f) {
                s = 0.0f;
            }
            mario->baseSpeed = s;
            if (s) {
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
    rd = rollData[4];
    {
        s32 flip;
        f32 sgn;
        f32 mv = toMovedir(mario->displayDirection);
        f32 pre;
        tcA = MF(0x1a0);
        flip = angOut(tcA, 90.0f, mv);
        pre = mario->baseSpeed * rd;
        sgn = (flip == 1) ? -1.0f : 1.0f;
        mario->rot.z = revise360(pre * sgn + mario->rot.z);
    }
    if (mario->forceMoveTimer == 0 && !getRollEvtFlag() && s) {
        v31 = mario->moveDirection;
        {
            MarioWork* m2 = marioGetPtr();
            DISPDIR_BODY2(v30, v31, m2)
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
}

void roll_upstairs_on(void) {
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
}

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

void mot_fall_roll(void) {
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
}

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
            if (rabs(ang) < 45.0) {
                v26 = rollRad(r);
                s = rSin(v26);
                c = rollCos(v26);
                {
                    f32 t1 = s * 5.0f;
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
