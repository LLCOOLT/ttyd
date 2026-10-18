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

void roll_upstairs(void);
static inline void marioRollCan(void);


#pragma inline_max_size(20000)
#pragma inline_max_total_size(200000)


#ifdef NONMATCHING
void marioRollFixOn(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == 0x16) {
        MI(0x2a4) |= 0x200;
    }
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void setRollEvtFlag(void) {
    MarioWork* mario = marioGetPtr();
    MI(0x2a4) |= 0x100;
}
#endif

#ifdef NONMATCHING
void clrRollEvtFlag(void) {
    MarioWork* mario = marioGetPtr();
    MI(0x2a4) &= ~0x100;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif


#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void marioSetRollDispDir(void) {
    MarioWork* mario = marioGetPtr();
    f32 b, a;
    MarioWork* m2;
    a = mario->directionView;
    b = mario->moveDirection;
    m2 = marioGetPtr();
    DISPDIR_BODY(a, b, m2)
}
#endif

#ifdef NONMATCHING
void rollEvtJumpSetup(void) {
    MarioWork* mario = marioGetPtr();
    camFollowYOff();
    mario->flags |= 0x10000;
    mario->airTimer = 1;
}
#endif

#ifdef NONMATCHING
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
#endif




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



#ifdef NONMATCHING  // restored C definition (nmrepair)
static __declspec(section ".rodata") Vec rollOfs = {0.0f, 40.0f, 0.0f};
#endif
#ifdef NONMATCHING
void mot_roll(void) {
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
}
#endif

#ifdef NONMATCHING
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
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void roll_upstairs(void) {
    MarioWork* mario = marioGetPtr();
    mario->position.y = mario->position.y + mario->jumpVelocityY;
    if ((s32)--mario->multiTimer <= 0) {
        mario->flags &= ~0x80;
        mario->flags &= ~0x40;
        mario->flags &= ~0x40000;
    }
}
#endif

#pragma dont_inline reset

#ifdef NONMATCHING
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
// ASM-STOPGAP: marioRollFixOn (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c5d40[3] = { 0.0f, 40.0f, 0.0f };
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c5d4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5d58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5d64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5d70[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5d7c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5d88[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5d94[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5da0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 gap_04_802C5DAC_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_0p5_802c5db0 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c5db8 = 3;
__declspec(section ".rodata") const f64 double_0_802c5dc0 = 0;
__declspec(section ".rodata") const f64 double_45_802c5dc8 = 45;
__declspec(section ".rodata") const f64 double_to_int_802c5dd0 = 4503601774854144;
__declspec(section ".rodata") const char str_802C5DD8[] = "p_roll\000";
__declspec(section ".rodata") const char str_802C5DE0[] = "PM_R_1A";
__declspec(section ".rodata") const char str_802C5DE8[] = "PM_R_1B";
__declspec(section ".rodata") const char str_802C5DF0[] = "PM_R_1C";
__declspec(section ".rodata") const char str_802C5DF8[] = "eki_04\000";
#pragma force_active reset
#pragma force_active on
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
__declspec(section ".sdata2") const char str_8041AD04[8] = "M_I_U\0\0";
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
__declspec(section ".sdata2") const char str_8041AD34[8] = "M_S_1\0\0";
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

asm void mot_fall_roll(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	bl marioGetPtr
	mr r31, r3
	bl marioGetFallSpd
	fmr f31, f1
	lfs f0, float_neg10_8041acf0(r2)
	fcmpo cr0, f31, f0
	bge @1
	fmr f31, f0
	@1:
	fmr f1, f31
	addi r3, r1, 0x8
	bl marioChkLandon
	cmplwi r3, 0x0
	beq @2
	lfs f0, 0x8(r1)
	li r0, 0x0
	stfs f0, 0x90(r31)
	stw r3, 0x1e4(r31)
	stw r0, 0x1e8(r31)
	b @3
	@2:
	lfs f0, 0x90(r31)
	fadds f0, f0, f31
	stfs f0, 0x90(r31)
	@3:
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	beq @4
	bl marioLandOn
	li r0, 0x0
	stw r0, roll_flyout_flag2(r13)
	@4:
	psq_l f31, 0x28(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f31, 0x20(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void roll_upstairs(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lfs f1, 0x90(r3)
	lfs f0, 0x7c(r3)
	fadds f0, f1, f0
	stfs f0, 0x90(r3)
	lwz r4, 0x48(r3)
	subic. r0, r4, 0x1
	stw r0, 0x48(r3)
	bgt @1
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r3)
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 26, 24
	stw r0, 0x0(r3)
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 14, 12
	stw r0, 0x0(r3)
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void roll_upstairs_on(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	bl marioGetPtr
	mr r31, r3
	lwz r0, 0x0(r3)
	oris r0, r0, 0x4
	stw r0, 0x0(r3)
	lwz r0, 0x0(r3)
	ori r0, r0, 0x80
	stw r0, 0x0(r3)
	bl marioClearJumpPara
	li r3, 0x3
	lis r0, 0x4330
	stw r3, 0x48(r31)
	lis r3, double_to_int_802c5dd0@ha
	lfd f1, double_to_int_802c5dd0@l(r3)
	lwz r4, 0x48(r31)
	stw r0, 0x8(r1)
	xoris r0, r4, 0x8000
	lfs f4, 0x1c4(r31)
	stw r0, 0xc(r1)
	lfs f2, 0x90(r31)
	lfd f0, 0x8(r1)
	fsubs f5, f4, f2
	lfs f3, float_4_8041acf4(r2)
	fsubs f4, f0, f1
	lfs f2, float_neg0p42_8041acf8(r2)
	lfs f1, float_0p04_8041acfc(r2)
	lfs f0, float_neg0p01_8041ad00(r2)
	fdivs f4, f5, f4
	stfs f4, 0x7c(r31)
	stfs f3, 0x7c(r31)
	stfs f2, 0x80(r31)
	stfs f1, 0x84(r31)
	stfs f0, 0x88(r31)
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mot_roll(void) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stfd f30, 0xd0(r1)
	psq_st f30, 0xd8(r1), 0, 0
	stfd f29, 0xc0(r1)
	psq_st f29, 0xc8(r1), 0, 0
	stfd f28, 0xb0(r1)
	psq_st f28, 0xb8(r1), 0, 0
	stfd f27, 0xa0(r1)
	psq_st f27, 0xa8(r1), 0, 0
	stfd f26, 0x90(r1)
	psq_st f26, 0x98(r1), 0, 0
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	stw r29, 0x84(r1)
	stw r28, 0x80(r1)
	lis r3, vec3_802c5d40@ha
	addi r30, r3, vec3_802c5d40@l
	bl marioGetPtr
	mr r31, r3
	lwz r3, 0xc(r3)
	clrlwi. r0, r3, 31
	beq @1
	clrrwi r3, r3, 1
	li r0, 0x0
	stw r3, 0xc(r31)
	li r3, 0x0
	li r4, 0x14
	lwz r5, 0x0(r31)
	rlwinm r5, r5, 0, 16, 11
	stw r5, 0x0(r31)
	stw r0, 0x2a4(r31)
	stw r0, 0x2a8(r31)
	stw r0, 0x2ac(r31)
	stw r0, 0x2b0(r31)
	stw r0, 0x2b4(r31)
	bl __memAlloc
	mr r28, r3
	bl marioGetPtr
	stw r28, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r4, 0x0
	li r5, 0x14
	bl memset
	bl marioGetPtr
	li r4, -0x1
	li r0, 0x0
	stw r4, 0x2a8(r3)
	stw r0, 0x44(r31)
	@1:
	lwz r0, 0x44(r31)
	cmpwi r0, 0x14
	beq @2
	bge @3
	cmpwi r0, 0x1
	beq @4
	bge @5
	cmpwi r0, 0x0
	bge @6
	b @5
	@3:
	cmpwi r0, 0x16
	beq @7
	bge @5
	b @8
	@6:
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	bl marioAdjustMoveDir
	lfs f2, 0x1a8(r31)
	lfs f1, float_90_8041acd8(r2)
	fcmpo cr0, f2, f1
	blt @9
	lfs f0, float_270_8041acdc(r2)
	fcmpo cr0, f2, f0
	ble @10
	@9:
	li r0, 0x1
	lfs f1, float_270_8041acdc(r2)
	stb r0, 0x43(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	stfs f1, 0x1a0(r31)
	lfs f0, float_270_8041acdc(r2)
	stfs f0, 0x19c(r31)
	b @11
	@10:
	li r0, 0x0
	stb r0, 0x43(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	stfs f1, 0x1a0(r31)
	lfs f0, float_90_8041acd8(r2)
	stfs f0, 0x19c(r31)
	@11:
	bl marioGetRubInit
	lwz r4, 0x0(r31)
	li r0, 0x10
	addi r3, r30, 0x98
	oris r4, r4, 0x100
	stw r4, 0x0(r31)
	stw r0, 0x8(r31)
	lwz r0, 0x4(r31)
	ori r0, r0, 0x8
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	ori r0, r0, 0x100
	stw r0, 0x4(r31)
	bl marioPaperOn
	la r3, str_8041AD04(r2)
	bl marioChgPose
	addi r3, r30, 0xa0
	bl marioChgPaper
	li r0, 0x41
	stw r0, 0x48(r31)
	bl marioGetPtr
	lfs f0, float_14p8_8041ad0c(r2)
	mr r28, r3
	lfs f28, float_0_8041acbc(r2)
	stfs f0, 0x1b4(r3)
	stfs f0, 0x1b8(r3)
	lfs f0, rollData(r13)
	stfs f0, 0x188(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f27, float_0_8041acbc(r2)
	stfs f28, 0x0(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r0, 0x0
	lfs f0, float_neg6_8041ad10(r2)
	stfs f27, 0x4(r3)
	lfs f2, float_6_8041accc(r2)
	stfs f0, 0xb0(r28)
	lfs f1, float_0_8041acbc(r2)
	stfs f2, 0xb4(r28)
	lfs f0, float_1_8041ad14(r2)
	stfs f2, 0x98(r28)
	stfs f1, 0x9c(r28)
	stfs f0, 0xc8(r28)
	stfs f0, 0xcc(r28)
	stfs f0, 0xd0(r28)
	stfs f0, 0x130(r28)
	sth r0, 0x50(r31)
	lha r0, 0x4e(r31)
	cmpwi r0, 0x0
	bne @12
	stfs f1, 0x180(r31)
	@12:
	bl marioGetPtr
	lfs f0, float_0p4_8041ad18(r2)
	li r29, 0x0
	lfs f1, float_0p01_8041ad1c(r2)
	stfs f0, 0x148(r3)
	lfs f0, float_2_8041ad20(r2)
	stfs f1, 0x158(r3)
	stfs f0, 0x68(r3)
	lwz r4, 0x0(r30)
	lwz r0, 0x4(r30)
	stw r4, 0x6c(r3)
	stw r0, 0x70(r3)
	lwz r0, 0x8(r30)
	stw r0, 0x74(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r28, 0x0
	stw r29, 0x8(r3)
	bl marioGetPtr
	lwz r5, 0x288(r3)
	addi r4, r31, 0x8c
	li r3, 0x179
	stw r28, 0xc(r5)
	bl psndSFXOn_3D
	addi r4, r31, 0x8c
	li r3, 0x9f
	bl psndSFXOn_3D
	li r0, 0x1
	stw r0, 0x44(r31)
	b @5
	@4:
	lwz r0, 0x48(r31)
	cmpwi r0, 0x36
	bne @13
	bl allPartyRideShip
	@13:
	lfs f2, 0x9c(r31)
	lfs f1, float_0p1_8041ad24(r2)
	lfs f0, float_1_8041ad14(r2)
	fadds f1, f2, f1
	stfs f1, 0x9c(r31)
	lfs f1, 0x9c(r31)
	fcmpo cr0, f1, f0
	ble @14
	stfs f0, 0x9c(r31)
	@14:
	lwz r3, 0x48(r31)
	subic. r0, r3, 0x1
	stw r0, 0x48(r31)
	bgt @5
	li r0, 0x1e
	la r3, str_8041AD04(r2)
	stw r0, 0x44(r31)
	bl marioChgPose
	addi r3, r30, 0xa8
	bl marioChgPaper
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	b @5
	@2:
	lfs f0, float_0_8041acbc(r2)
	stfs f0, 0x180(r31)
	stfs f0, 0xbc(r31)
	stfs f0, 0xc4(r31)
	stfs f0, 0xb0(r31)
	stfs f0, 0xb4(r31)
	lfs f1, 0x1a0(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	bge @15
	lfs f0, float_3_8041ad28(r2)
	b @16
	@15:
	lfs f0, float_neg3_8041ad2c(r2)
	@16:
	stfs f0, 0x98(r31)
	li r3, 0x41
	lfs f0, float_0_8041acbc(r2)
	li r0, 0x15
	stfs f0, 0x9c(r31)
	stw r3, 0x48(r31)
	stw r0, 0x44(r31)
	stfs f0, 0x1a8(r31)
	bl marioGetPtr
	mr r28, r3
	lwz r3, 0x2a8(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @17
	bl psndSFXOff
	li r0, -0x1
	stw r0, 0x2a8(r28)
	@17:
	bl marioGetPtr
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_0p004_8041ad30(r2)
	stfs f1, 0x148(r3)
	stfs f0, 0x158(r3)
	addi r3, r30, 0xb0
	bl marioChgPaper
	bl marioPaperLightOff
	addi r4, r31, 0x8c
	li r3, 0x17a
	bl psndSFXOn_3D
	@8:
	lwz r3, 0x48(r31)
	subic. r0, r3, 0x1
	stw r0, 0x48(r31)
	ble @18
	lfs f1, 0x1a0(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	bge @19
	lfs f3, float_90_8041acd8(r2)
	lfs f4, 0x1a8(r31)
	lfs f2, float_0p1_8041ad24(r2)
	fsubs f1, f3, f4
	lfs f0, float_1_8041ad14(r2)
	fmuls f5, f2, f1
	fadds f5, f5, f4
	fsubs f1, f3, f5
	fcmpo cr0, f1, f0
	mfcr r3
	lis r0, 0x4330
	srwi r3, r3, 31
	stw r0, 0x60(r1)
	xoris r0, r3, 0x8000
	lfd f2, 0x90(r30)
	stw r0, 0x64(r1)
	lfs f0, float_0_8041acbc(r2)
	lfd f1, 0x60(r1)
	fsubs f1, f1, f2
	fabs f1, f1
	fcmpu cr0, f1, f0
	beq @20
	fmr f5, f3
	@20:
	stfs f5, 0x1a8(r31)
	stfs f5, 0x1ac(r31)
	b @5
	@19:
	lfs f3, float_270_8041acdc(r2)
	lfs f4, 0x1a8(r31)
	lfs f2, float_0p1_8041ad24(r2)
	fsubs f1, f3, f4
	lfs f0, float_1_8041ad14(r2)
	fmuls f5, f2, f1
	fadds f5, f5, f4
	fsubs f1, f3, f5
	fcmpo cr0, f1, f0
	mfcr r3
	lis r0, 0x4330
	srwi r3, r3, 31
	stw r0, 0x60(r1)
	xoris r0, r3, 0x8000
	lfd f2, 0x90(r30)
	stw r0, 0x64(r1)
	lfs f0, float_0_8041acbc(r2)
	lfd f1, 0x60(r1)
	fsubs f1, f1, f2
	fabs f1, f1
	fcmpu cr0, f1, f0
	beq @21
	fmr f5, f3
	@21:
	stfs f5, 0x1a8(r31)
	stfs f5, 0x1ac(r31)
	b @5
	@18:
	lfs f1, 0x1a0(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f2, float_180_8041acc8(r2)
	fcmpo cr0, f1, f2
	cror eq, gt, eq
	bne @22
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_270_8041acdc(r2)
	stfs f1, 0x1a8(r31)
	stfs f1, 0x1ac(r31)
	stfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	b @23
	@22:
	stfs f2, 0x1a8(r31)
	lfs f0, float_90_8041acd8(r2)
	stfs f2, 0x1ac(r31)
	stfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	@23:
	bl marioSetSpec
	li r0, 0x0
	stw r0, 0x8(r31)
	bl marioOfsRotReset
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 8, 6
	stw r0, 0x0(r31)
	bl marioPaperOff
	bl marioAdjustMoveDir
	la r3, str_8041AD34(r2)
	bl marioChgPose
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @24
	bl marioGetPtr
	mr r4, r3
	li r3, 0x0
	lwz r4, 0x288(r4)
	bl __memFree
	li r28, 0x0
	bl marioGetPtr
	stw r28, 0x288(r3)
	@24:
	bl allPartyRideOff
	li r3, 0x8
	bl camGetPtr
	lhz r4, 0x0(r3)
	li r0, 0x16
	rlwinm r4, r4, 0, 23, 21
	sth r4, 0x0(r3)
	stw r0, 0x44(r31)
	b @5
	@7:
	li r3, 0x0
	li r4, 0x0
	bl marioChgMotSub
	@5:
	lwz r0, 0x44(r31)
	cmpwi r0, 0x1e
	blt @25
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 13, 13
	beq @26
	bl roll_upstairs
	b @25
	@26:
	lhz r0, 0x248(r31)
	rlwinm. r0, r0, 0, 22, 22
	beq @27
	bl marioGetPtr
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 22, 22
	beq @28
	li r0, 0x1
	b @29
	@28:
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 4, 4
	beq @30
	li r0, 0x1
	b @29
	@30:
	lwz r0, 0x1e4(r3)
	cmplwi r0, 0x0
	bne @31
	li r0, 0x1
	b @29
	@31:
	bl marioSlitChkWallAround
	cmpwi r3, 0x0
	beq @32
	li r0, 0x1
	b @29
	@32:
	li r0, 0x0
	@29:
	cmpwi r0, 0x0
	bne @33
	li r0, 0x14
	li r3, 0x8
	stw r0, 0x44(r31)
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	b @27
	@33:
	lhz r0, 0x248(r31)
	ori r0, r0, 0x100
	sth r0, 0x248(r31)
	@27:
	lfs f26, 0x130(r31)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0x8(r3)
	cmpwi r0, 0x0
	beq @34
	li r28, 0x0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r29, 0x1
	stw r28, 0x8(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f26, float_1_8041ad14(r2)
	stw r29, 0xc(r3)
	@34:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lwz r0, 0xc(r3)
	cmpwi r0, 0x2
	beq @35
	bge @36
	cmpwi r0, 0x1
	bge @37
	b @38
	@36:
	cmpwi r0, 0x4
	bge @38
	b @39
	@37:
	lfs f2, float_1p4_8041ad3c(r2)
	fcmpo cr0, f26, f2
	bge @40
	lfs f0, float_1p45_8041ad40(r2)
	lfs f1, float_1_8041ad14(r2)
	fsubs f0, f0, f26
	fmadds f26, f1, f0, f26
	fcmpo cr0, f26, f2
	cror eq, gt, eq
	bne @40
	fmr f26, f2
	@40:
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @38
	li r29, 0x2
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r29, 0xc(r3)
	b @38
	@35:
	lfs f1, float_0p4_8041ad18(r2)
	fcmpo cr0, f26, f1
	ble @38
	lfs f0, float_0p35_8041ad44(r2)
	fsubs f0, f0, f26
	fmadds f26, f1, f0, f26
	fcmpo cr0, f26, f1
	cror eq, lt, eq
	bne @38
	fmr f26, f1
	li r29, 0x3
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stw r29, 0xc(r3)
	b @38
	@39:
	lfs f2, float_1_8041ad14(r2)
	fcmpo cr0, f26, f2
	bge @38
	lfs f0, float_1p05_8041ad48(r2)
	lfs f1, float_0p5_8041acc0(r2)
	fsubs f0, f0, f26
	fmadds f26, f1, f0, f26
	fcmpo cr0, f26, f2
	cror eq, gt, eq
	bne @38
	li r29, 0x0
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f26, float_1_8041ad14(r2)
	stw r29, 0xc(r3)
	@38:
	stfs f26, 0x130(r31)
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	bne @41
	lwz r3, 0x1e0(r31)
	cmplwi r3, 0x0
	beq @41
	bl marioChkBero
	cmpwi r3, 0x0
	bne @41
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f26, 0x0(r3)
	bl marioGetPtr
	fneg f1, f26
	lfs f3, float_0p2_8041ad4c(r2)
	lwz r3, 0x288(r3)
	lfs f0, float_1_8041ad14(r2)
	fmadds f26, f3, f1, f26
	lfs f27, 0x4(r3)
	fneg f2, f27
	fabs f1, f26
	fmadds f27, f3, f2, f27
	fcmpo cr0, f1, f0
	bge @42
	lfs f26, float_0_8041acbc(r2)
	@42:
	fabs f1, f27
	lfs f0, float_1_8041ad14(r2)
	fcmpo cr0, f1, f0
	bge @43
	lfs f27, float_0_8041acbc(r2)
	@43:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f26, 0x0(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f27, 0x4(r3)
	@41:
	lwz r3, 0x1e4(r31)
	cmplwi r3, 0x0
	beq @44
	bl hitGetAttr
	andi. r0, r3, 0xa00
	bne @45
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @45
	lhz r0, 0x248(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @45
	lwz r3, gp(r13)
	addi r4, r30, 0xb8
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @46
	lfs f1, 0x214(r31)
	lfs f0, float_40_8041ad50(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @45
	@46:
	bl marioGetPtr
	mr r29, r3
	bl camFollowYOff
	lfs f1, float_2p85_8041ad54(r2)
	li r0, 0x1
	lfs f0, float_neg0p14_8041ad58(r2)
	stfs f1, 0x7c(r29)
	lfs f1, float_0p08_8041ad5c(r2)
	stfs f0, 0x80(r29)
	lfs f0, float_neg0p02_8041ad60(r2)
	stfs f1, 0x84(r29)
	stfs f0, 0x88(r29)
	lwz r3, 0x0(r29)
	oris r3, r3, 0x1
	stw r3, 0x0(r29)
	sth r0, 0x50(r29)
	bl marioGetPtr
	mr r4, r3
	li r3, 0x17c
	addi r4, r4, 0x8c
	bl psndSFXOn_3D
	lwz r3, 0x1e4(r31)
	li r0, 0x0
	stw r3, 0x1e8(r31)
	stw r0, 0x1e4(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xd4(r31)
	stw r0, 0xd8(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xdc(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0x11c(r31)
	stw r0, 0x120(r31)
	lwz r0, 0x94(r31)
	stw r0, 0x124(r31)
	bl camFollowYOff
	@45:
	lwz r4, 0x8c(r31)
	addi r3, r1, 0x54
	lwz r0, 0x90(r31)
	stw r4, 0x54(r1)
	stw r0, 0x58(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x5c(r1)
	bl marioUpdateCamCollision
	li r0, 0x0
	sth r0, 0x50(r31)
	@44:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 15
	beq @47
	lwz r0, 0x1f4(r31)
	cmplwi r0, 0x0
	beq @48
	lfs f1, 0x7c(r31)
	lfs f0, float_0_8041acbc(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @49
	lfs f0, float_neg0p03_8041ad64(r2)
	lfs f1, float_neg0p02_8041ad60(r2)
	stfs f0, 0x7c(r31)
	lfs f0, float_neg0p002_8041ad68(r2)
	stfs f1, 0x80(r31)
	stfs f1, 0x84(r31)
	stfs f0, 0x88(r31)
	@49:
	lwz r0, 0x0(r31)
	oris r0, r0, 0x2
	stw r0, 0x0(r31)
	@48:
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @50
	lfs f1, 0x7c(r31)
	lfs f0, float_0_8041acbc(r2)
	fcmpo cr0, f1, f0
	bge @50
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xd4(r31)
	stw r0, 0xd8(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xdc(r31)
	bl camFollowYOn
	@50:
	lfs f1, 0x90(r31)
	lfs f0, 0x120(r31)
	fcmpo cr0, f1, f0
	bge @51
	bl camFollowYOn
	@51:
	lha r3, 0x50(r31)
	addi r0, r3, 0x1
	sth r0, 0x50(r31)
	@47:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f29, 0x0(r3)
	bl marioGetPtr
	lwz r0, 0x0(r31)
	lfs f30, float_0_8041acbc(r2)
	lwz r3, 0x288(r3)
	rlwinm. r0, r0, 0, 14, 15
	fmr f27, f30
	lfs f28, 0x4(r3)
	bne @52
	lbz r4, 0x24e(r31)
	lis r3, 0x4330
	lbz r0, 0x24f(r31)
	fmr f1, f30
	extsb r4, r4
	stw r3, 0x60(r1)
	extsb r0, r0
	lfd f4, 0x90(r30)
	xoris r4, r4, 0x8000
	xoris r0, r0, 0x8000
	stw r4, 0x64(r1)
	fmr f2, f30
	lfd f0, 0x60(r1)
	stw r0, 0x6c(r1)
	fsubs f26, f0, f4
	stw r3, 0x68(r1)
	lfd f0, 0x68(r1)
	fmr f3, f26
	fsubs f30, f0, f4
	fmr f4, f30
	bl distABf
	fmr f27, f1
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f26
	fmr f2, f1
	fmr f4, f30
	bl angleABf
	lfs f0, 0x198(r31)
	fadds f1, f0, f1
	bl revise360
	lfs f2, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f1
	fdivs f26, f1, f0
	fmr f1, f26
	bl sin
	frsp f0, f1
	fmr f1, f26
	fmuls f30, f27, f0
	bl cos
	frsp f0, f1
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f30
	fmr f2, f1
	fneg f0, f0
	fmuls f27, f27, f0
	fmr f4, f27
	bl angleABf
	lfs f0, 0x1a0(r31)
	lis r0, 0x4330
	lfs f5, float_10_8041ace4(r2)
	li r4, 0x0
	stw r0, 0x78(r1)
	mr r3, r4
	fmuls f3, f5, f0
	lfd f4, 0x90(r30)
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_0_8041acbc(r2)
	fctiwz f3, f3
	stfd f3, 0x70(r1)
	lwz r0, 0x74(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f3, 0x78(r1)
	fsubs f3, f3, f4
	fdivs f4, f3, f5
	fsubs f3, f4, f2
	fcmpo cr0, f3, f0
	bge @53
	lfs f0, float_360_8041ace0(r2)
	li r4, 0x1
	fadds f3, f3, f0
	@53:
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f2, f4, f2
	fcmpo cr0, f2, f0
	ble @54
	fsubs f2, f2, f0
	li r4, 0x2
	@54:
	cmpwi r4, 0x1
	bne @55
	fcmpo cr0, f2, f1
	bge @56
	fcmpo cr0, f1, f3
	bge @56
	li r3, 0x1
	b @56
	@55:
	cmpwi r4, 0x2
	bne @57
	fcmpo cr0, f2, f1
	bge @56
	fcmpo cr0, f1, f3
	bge @56
	li r3, 0x1
	b @56
	@57:
	cmpwi r4, 0x0
	bne @56
	fcmpo cr0, f1, f3
	blt @58
	fcmpo cr0, f2, f1
	bge @56
	@58:
	li r3, 0x1
	@56:
	cmpwi r3, 0x1
	bne @52
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f30
	fmr f4, f27
	fmr f2, f1
	bl distABf
	lfs f2, float_3p1416_8041acc4(r2)
	fmr f27, f1
	lfs f1, 0x1a0(r31)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, float_3p1416_8041acc4(r2)
	frsp f4, f1
	lfs f1, 0x1a0(r31)
	fneg f3, f27
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f1
	fmuls f30, f3, f4
	fdivs f1, f1, f0
	bl cos
	frsp f0, f1
	fmuls f27, f27, f0
	@52:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 15
	bne @59
	lwz r0, 0x2a4(r31)
	rlwinm. r0, r0, 0, 26, 26
	bne @59
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f29
	fneg f4, f28
	fmr f2, f1
	bl angleABf
	lfs f2, 0x220(r31)
	fmr f31, f1
	lfs f0, float_0p05_8041ad6c(r2)
	fcmpo cr0, f2, f0
	ble @60
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f31, f0
	ble @61
	la r3, rollData(r13)
	lfs f26, 0x14(r3)
	b @62
	@61:
	la r3, rollData(r13)
	lfs f26, 0x18(r3)
	@62:
	lfs f1, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, float_neg100_8041ad70(r2)
	fmuls f1, f1, f26
	fsubs f30, f30, f1
	fcmpo cr0, f30, f0
	cror eq, lt, eq
	bne @63
	fmr f30, f0
	b @63
	@60:
	lfs f0, float_neg0p05_8041ad74(r2)
	fcmpo cr0, f2, f0
	bge @63
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f31, f0
	bge @64
	la r3, rollData(r13)
	lfs f26, 0x14(r3)
	b @65
	@64:
	la r3, rollData(r13)
	lfs f26, 0x18(r3)
	@65:
	lfs f1, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, float_100_8041acb8(r2)
	fmuls f1, f1, f26
	fsubs f30, f30, f1
	fcmpo cr0, f30, f0
	cror eq, gt, eq
	bne @63
	fmr f30, f0
	@63:
	lfs f2, 0x218(r31)
	lfs f0, float_0p05_8041ad6c(r2)
	fcmpo cr0, f2, f0
	ble @66
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f31, f0
	ble @67
	la r3, rollData(r13)
	lfs f26, 0x14(r3)
	b @68
	@67:
	la r3, rollData(r13)
	lfs f26, 0x18(r3)
	@68:
	lfs f1, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, float_neg100_8041ad70(r2)
	fmuls f1, f1, f26
	fsubs f27, f27, f1
	fcmpo cr0, f27, f0
	cror eq, lt, eq
	bne @69
	fmr f27, f0
	b @69
	@66:
	lfs f0, float_neg0p05_8041ad74(r2)
	fcmpo cr0, f2, f0
	bge @69
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f31, f0
	bge @70
	la r3, rollData(r13)
	lfs f26, 0x14(r3)
	b @71
	@70:
	la r3, rollData(r13)
	lfs f26, 0x18(r3)
	@71:
	lfs f1, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, float_100_8041acb8(r2)
	fmuls f1, f1, f26
	fsubs f27, f27, f1
	fcmpo cr0, f27, f0
	cror eq, gt, eq
	bne @69
	fmr f27, f0
	@69:
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f30
	fmr f4, f27
	fmr f2, f1
	bl angleABf
	lfs f0, 0x1a0(r31)
	lis r0, 0x4330
	lfs f5, float_10_8041ace4(r2)
	li r4, 0x0
	stw r0, 0x70(r1)
	mr r3, r4
	fmuls f3, f5, f0
	lfd f4, 0x90(r30)
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_0_8041acbc(r2)
	fctiwz f3, f3
	stfd f3, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f3, 0x70(r1)
	fsubs f3, f3, f4
	fdivs f4, f3, f5
	fsubs f3, f4, f2
	fcmpo cr0, f3, f0
	bge @72
	lfs f0, float_360_8041ace0(r2)
	li r4, 0x1
	fadds f3, f3, f0
	@72:
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f2, f4, f2
	fcmpo cr0, f2, f0
	ble @73
	fsubs f2, f2, f0
	li r4, 0x2
	@73:
	cmpwi r4, 0x1
	bne @74
	fcmpo cr0, f2, f1
	bge @75
	fcmpo cr0, f1, f3
	bge @75
	li r3, 0x1
	b @75
	@74:
	cmpwi r4, 0x2
	bne @76
	fcmpo cr0, f2, f1
	bge @75
	fcmpo cr0, f1, f3
	bge @75
	li r3, 0x1
	b @75
	@76:
	cmpwi r4, 0x0
	bne @75
	fcmpo cr0, f1, f3
	blt @77
	fcmpo cr0, f2, f1
	bge @75
	@77:
	li r3, 0x1
	@75:
	cmpwi r3, 0x1
	bne @59
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f30
	fneg f4, f27
	fmr f2, f1
	bl distABf
	lfs f2, float_3p1416_8041acc4(r2)
	fmr f27, f1
	lfs f1, 0x1a0(r31)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f2, float_3p1416_8041acc4(r2)
	frsp f4, f1
	lfs f1, 0x1a0(r31)
	fneg f3, f27
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f1
	fmuls f30, f3, f4
	fdivs f1, f1, f0
	bl cos
	frsp f0, f1
	fmuls f27, f27, f0
	@59:
	lwz r0, 0x1d8(r31)
	cmplwi r0, 0x0
	beq @78
	lwz r3, 0x1e0(r31)
	bl marioChkBero
	cmpwi r3, 0x0
	bne @78
	fneg f2, f29
	lfs f3, float_0p05_8041ad6c(r2)
	fneg f1, f28
	lfs f0, float_0p1_8041ad24(r2)
	fmadds f29, f3, f2, f29
	fmadds f28, f3, f1, f28
	fabs f1, f29
	fcmpo cr0, f1, f0
	bge @79
	lfs f29, float_0_8041acbc(r2)
	@79:
	fabs f1, f28
	lfs f0, float_0p1_8041ad24(r2)
	fcmpo cr0, f1, f0
	bge @78
	lfs f28, float_0_8041acbc(r2)
	@78:
	lwz r3, 0x1e0(r31)
	cmplwi r3, 0x0
	beq @80
	lbz r0, 0x24e(r31)
	extsb. r0, r0
	bne @80
	lbz r0, 0x24f(r31)
	extsb. r0, r0
	bne @80
	bl marioChkBero
	cmpwi r3, 0x0
	bne @80
	fneg f2, f29
	lfs f3, float_0p6_8041ad78(r2)
	fneg f1, f28
	lfs f0, float_0p1_8041ad24(r2)
	fmadds f29, f3, f2, f29
	fmadds f28, f3, f1, f28
	fabs f1, f29
	fcmpo cr0, f1, f0
	bge @81
	lfs f29, float_0_8041acbc(r2)
	@81:
	fabs f1, f28
	lfs f0, float_0p1_8041ad24(r2)
	fcmpo cr0, f1, f0
	bge @80
	lfs f28, float_0_8041acbc(r2)
	@80:
	lha r0, 0x4e(r31)
	cmpwi r0, 0x0
	bne @82
	lfs f2, float_0_8041acbc(r2)
	fcmpu cr0, f30, f2
	bne @82
	fcmpu cr0, f27, f2
	bne @82
	lwz r3, 0x1f0(r31)
	cmplwi r3, 0x0
	beq @83
	bl marioChkBero
	cmpwi r3, 0x0
	bne @84
	la r3, rollData(r13)
	lfs f0, 0x8(r3)
	fmadds f29, f29, f0, f29
	fmadds f28, f28, f0, f28
	b @84
	@83:
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	beq @84
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @84
	lfs f1, 0x214(r31)
	lfs f0, float_1_8041ad14(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	mfcr r3
	lis r0, 0x4330
	extrwi r3, r3, 1, 2
	stw r0, 0x78(r1)
	xoris r0, r3, 0x8000
	lfd f1, 0x90(r30)
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f1
	fabs f0, f0
	fcmpu cr0, f0, f2
	beq @85
	la r3, rollData(r13)
	lfs f0, 0x4(r3)
	fmadds f29, f29, f0, f29
	fmadds f28, f28, f0, f28
	b @84
	@85:
	la r3, rollData(r13)
	lfs f2, float_6p4_8041ad7c(r2)
	lfs f0, 0x4(r3)
	fmuls f1, f29, f0
	fmuls f0, f28, f0
	fmadds f29, f2, f1, f29
	fmadds f28, f2, f0, f28
	@84:
	la r3, rollData(r13)
	fabs f0, f29
	lfs f1, 0xc(r3)
	fcmpo cr0, f0, f1
	bge @86
	lfs f29, float_0_8041acbc(r2)
	@86:
	fabs f0, f28
	lfs f1, 0xc(r3)
	fcmpo cr0, f0, f1
	bge @87
	lfs f28, float_0_8041acbc(r2)
	b @87
	@82:
	lwz r0, 0x2a4(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @88
	lfs f1, float_0_8041acbc(r2)
	lfs f0, 0x220(r31)
	fcmpu cr0, f1, f0
	bne @88
	li r29, 0x0
	mr r28, r29
	bl marioGetPtr
	lfs f6, float_10_8041ace4(r2)
	lis r5, 0x4330
	lfs f0, 0x19c(r3)
	lbz r4, 0x24e(r3)
	fmuls f0, f6, f0
	lbz r0, 0x24f(r3)
	extsb r3, r4
	lfs f1, float_0_8041acbc(r2)
	extsb r0, r0
	stw r5, 0x70(r1)
	fctiwz f0, f0
	xoris r3, r3, 0x8000
	xoris r0, r0, 0x8000
	lfd f5, 0x90(r30)
	stw r3, 0x6c(r1)
	fmr f2, f1
	stfd f0, 0x78(r1)
	lwz r3, 0x7c(r1)
	stw r5, 0x68(r1)
	xoris r3, r3, 0x8000
	stw r3, 0x74(r1)
	lfd f0, 0x68(r1)
	lfd f4, 0x70(r1)
	stw r0, 0x64(r1)
	fsubs f3, f0, f5
	fsubs f0, f4, f5
	stw r5, 0x60(r1)
	fdivs f31, f0, f6
	lfd f0, 0x60(r1)
	fsubs f4, f0, f5
	bl angleABf
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_0_8041acbc(r2)
	fsubs f3, f31, f2
	fcmpo cr0, f3, f0
	bge @89
	lfs f0, float_360_8041ace0(r2)
	li r29, 0x1
	fadds f3, f3, f0
	@89:
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f2, f31, f2
	fcmpo cr0, f2, f0
	ble @90
	fsubs f2, f2, f0
	li r29, 0x2
	@90:
	cmpwi r29, 0x1
	bne @91
	fcmpo cr0, f2, f1
	bge @92
	fcmpo cr0, f1, f3
	bge @92
	li r28, 0x1
	b @92
	@91:
	cmpwi r29, 0x2
	bne @93
	fcmpo cr0, f2, f1
	bge @92
	fcmpo cr0, f1, f3
	bge @92
	li r28, 0x1
	b @92
	@93:
	cmpwi r29, 0x0
	bne @92
	fcmpo cr0, f1, f3
	blt @94
	fcmpo cr0, f2, f1
	bge @92
	@94:
	li r28, 0x1
	@92:
	cmpwi r28, 0x1
	bne @88
	fneg f2, f29
	lfs f3, float_0p2_8041ad4c(r2)
	fneg f1, f28
	lfs f0, float_1_8041ad14(r2)
	fmadds f29, f3, f2, f29
	fmadds f28, f3, f1, f28
	fabs f1, f29
	fcmpo cr0, f1, f0
	bge @95
	lfs f29, float_0_8041acbc(r2)
	@95:
	fabs f1, f28
	lfs f0, float_1_8041ad14(r2)
	fcmpo cr0, f1, f0
	bge @96
	lfs f28, float_0_8041acbc(r2)
	@96:
	lfs f0, float_0_8041acbc(r2)
	fcmpu cr0, f0, f29
	bne @88
	fcmpu cr0, f0, f28
	bne @88
	lfs f1, float_180_8041acc8(r2)
	lfs f0, 0x19c(r31)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x19c(r31)
	lfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	@88:
	lfs f1, rollData(r13)
	lfs f0, float_0p05_8041ad6c(r2)
	lha r0, 0x4e(r31)
	fdivs f31, f1, f0
	lfs f26, float_1_8041ad14(r2)
	cmpwi r0, 0x0
	bne @97
	lfs f0, 0x214(r31)
	fabs f0, f0
	fcmpo cr0, f0, f26
	cror eq, gt, eq
	bne @97
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f29
	fneg f4, f28
	fmr f2, f1
	bl angleABf
	lfs f2, 0x220(r31)
	lfs f0, float_0_8041acbc(r2)
	fcmpo cr0, f2, f0
	ble @98
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	ble @99
	la r3, rollData(r13)
	lfs f26, 0x24(r3)
	b @97
	@99:
	lfs f26, float_1_8041ad14(r2)
	b @97
	@98:
	bge @97
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	bge @100
	la r3, rollData(r13)
	lfs f26, 0x24(r3)
	b @97
	@100:
	lfs f26, float_1_8041ad14(r2)
	@97:
	fmuls f31, f31, f26
	fmuls f26, f28, f28
	fmuls f0, f31, f31
	fmadds f1, f29, f29, f26
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @101
	lfs f0, float_0p025_8041ad80(r2)
	fmadds f29, f30, f0, f29
	b @102
	@101:
	lfs f0, float_0p025_8041ad80(r2)
	fneg f1, f31
	fmadds f29, f30, f0, f29
	fcmpo cr0, f29, f1
	bge @103
	fmr f29, f1
	@103:
	fcmpo cr0, f29, f31
	ble @102
	fmr f29, f31
	@102:
	lfs f1, rollData(r13)
	lfs f0, float_0p05_8041ad6c(r2)
	lha r0, 0x4e(r31)
	fdivs f31, f1, f0
	lfs f30, float_1_8041ad14(r2)
	cmpwi r0, 0x0
	bne @104
	lfs f0, 0x214(r31)
	fabs f0, f0
	fcmpo cr0, f0, f30
	cror eq, gt, eq
	bne @104
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f29
	fneg f4, f28
	fmr f2, f1
	bl angleABf
	lfs f2, 0x218(r31)
	lfs f0, float_0_8041acbc(r2)
	fcmpo cr0, f2, f0
	ble @105
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	ble @106
	la r3, rollData(r13)
	lfs f30, 0x24(r3)
	b @104
	@106:
	lfs f30, float_1_8041ad14(r2)
	b @104
	@105:
	bge @104
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	bge @107
	la r3, rollData(r13)
	lfs f30, 0x24(r3)
	b @104
	@107:
	lfs f30, float_1_8041ad14(r2)
	@104:
	fmuls f31, f31, f30
	fmadds f1, f29, f29, f26
	fmuls f0, f31, f31
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @108
	lfs f0, float_0p025_8041ad80(r2)
	fnmsubs f28, f27, f0, f28
	b @87
	@108:
	lfs f0, float_0p025_8041ad80(r2)
	fneg f1, f31
	fnmsubs f28, f27, f0, f28
	fcmpo cr0, f28, f1
	bge @109
	fmr f28, f1
	@109:
	fcmpo cr0, f28, f31
	ble @87
	fmr f28, f31
	@87:
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f29, 0x0(r3)
	bl marioGetPtr
	fneg f31, f28
	lfs f1, float_0_8041acbc(r2)
	lwz r3, 0x288(r3)
	fmr f3, f29
	fmr f2, f1
	fmr f4, f31
	stfs f28, 0x4(r3)
	bl angleABf
	fmr f30, f1
	lfs f2, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f30
	fdivs f27, f1, f0
	fmr f1, f27
	bl cos
	frsp f26, f1
	fmr f1, f27
	bl sin
	frsp f0, f1
	lfs f1, float_0_8041acbc(r2)
	fmuls f4, f28, f26
	fmr f2, f1
	fmuls f3, f29, f0
	bl distABf
	lfs f0, float_0p05_8041ad6c(r2)
	li r28, 0x0
	fmuls f27, f0, f1
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @110
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @110
	li r28, 0x1
	@110:
	cmpwi r28, 0x0
	bne @111
	lha r0, 0x4e(r31)
	cmpwi r0, 0x0
	bne @111
	lfs f1, float_0_8041acbc(r2)
	fmr f3, f29
	fmr f4, f31
	fmr f2, f1
	bl angleABf
	lwz r0, 0x2a4(r31)
	fmr f30, f1
	rlwinm. r0, r0, 0, 15, 15
	bne @111
	lfs f1, 0x224(r31)
	lfs f0, float_0p05_8041ad6c(r2)
	fmuls f27, f27, f1
	fcmpo cr0, f27, f0
	bge @112
	lfs f27, float_0_8041acbc(r2)
	@112:
	lfs f0, float_0_8041acbc(r2)
	stfs f27, 0x180(r31)
	fcmpu cr0, f27, f0
	beq @111
	stfs f30, 0x1a0(r31)
	@111:
	lfs f1, 0x180(r31)
	lfs f0, float_0_8041acbc(r2)
	fcmpu cr0, f1, f0
	beq @113
	bl marioGetPtr
	mr r29, r3
	lwz r3, 0x2a8(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	bne @114
	addi r4, r29, 0x8c
	li r3, 0x17b
	bl psndSFXOn_3D
	stw r3, 0x2a8(r29)
	lwz r0, 0x2a4(r29)
	ori r0, r0, 0x1000
	stw r0, 0x2a4(r29)
	b @114
	@113:
	bl marioGetPtr
	mr r29, r3
	lwz r3, 0x2a8(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @114
	bl psndSFXOff
	li r0, -0x1
	stw r0, 0x2a8(r29)
	@114:
	la r3, rollData(r13)
	lfs f1, 0x1a8(r31)
	lfs f28, 0x10(r3)
	bl toMovedir
	lfs f0, 0x1a0(r31)
	lis r0, 0x4330
	lfs f5, float_10_8041ace4(r2)
	li r4, 0x0
	stw r0, 0x70(r1)
	mr r3, r4
	fmuls f3, f5, f0
	lfd f4, 0x90(r30)
	lfs f2, float_90_8041acd8(r2)
	lfs f0, float_0_8041acbc(r2)
	fctiwz f3, f3
	stfd f3, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f3, 0x70(r1)
	fsubs f3, f3, f4
	fdivs f4, f3, f5
	fsubs f3, f4, f2
	fcmpo cr0, f3, f0
	bge @115
	lfs f0, float_360_8041ace0(r2)
	li r4, 0x1
	fadds f3, f3, f0
	@115:
	lfs f2, float_90_8041acd8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f2, f4, f2
	fcmpo cr0, f2, f0
	ble @116
	fsubs f2, f2, f0
	li r4, 0x2
	@116:
	cmpwi r4, 0x1
	bne @117
	fcmpo cr0, f2, f1
	bge @118
	fcmpo cr0, f1, f3
	bge @118
	li r3, 0x1
	b @118
	@117:
	cmpwi r4, 0x2
	bne @119
	fcmpo cr0, f2, f1
	bge @118
	fcmpo cr0, f1, f3
	bge @118
	li r3, 0x1
	b @118
	@119:
	cmpwi r4, 0x0
	bne @118
	fcmpo cr0, f1, f3
	blt @120
	fcmpo cr0, f2, f1
	bge @118
	@120:
	li r3, 0x1
	@118:
	lfs f0, 0x180(r31)
	cmpwi r3, 0x1
	fmuls f2, f0, f28
	bne @121
	lfs f1, float_neg1_8041ad84(r2)
	b @122
	@121:
	lfs f1, float_1_8041ad14(r2)
	@122:
	lfs f0, 0xc4(r31)
	fmadds f1, f2, f1, f0
	bl revise360
	stfs f1, 0xc4(r31)
	lha r0, 0x4e(r31)
	cmpwi r0, 0x0
	bne @123
	li r28, 0x0
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @124
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @124
	li r28, 0x1
	@124:
	cmpwi r28, 0x0
	bne @123
	lfs f0, float_0_8041acbc(r2)
	fcmpu cr0, f27, f0
	beq @123
	lfs f31, 0x19c(r31)
	bl marioGetPtr
	lfs f4, float_10_8041ace4(r2)
	lis r0, 0x4330
	li r4, 0x0
	stw r0, 0x70(r1)
	fmuls f2, f4, f31
	lfd f3, 0x90(r30)
	lfs f1, float_135_8041ace8(r2)
	mr r29, r3
	lfs f0, float_0_8041acbc(r2)
	mr r3, r4
	fctiwz f2, f2
	stfd f2, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f2, 0x70(r1)
	fsubs f2, f2, f3
	fdivs f3, f2, f4
	fsubs f2, f3, f1
	fcmpo cr0, f2, f0
	bge @125
	lfs f0, float_360_8041ace0(r2)
	li r4, 0x1
	fadds f2, f2, f0
	@125:
	lfs f1, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f1, f3, f1
	fcmpo cr0, f1, f0
	ble @126
	fsubs f1, f1, f0
	li r4, 0x2
	@126:
	cmpwi r4, 0x1
	bne @127
	fcmpo cr0, f1, f30
	bge @128
	fcmpo cr0, f30, f2
	bge @128
	li r3, 0x1
	b @128
	@127:
	cmpwi r4, 0x2
	bne @129
	fcmpo cr0, f1, f30
	bge @128
	fcmpo cr0, f30, f2
	bge @128
	li r3, 0x1
	b @128
	@129:
	cmpwi r4, 0x0
	bne @128
	fcmpo cr0, f30, f2
	blt @130
	fcmpo cr0, f1, f30
	bge @128
	@130:
	li r3, 0x1
	@128:
	cmpwi r3, 0x1
	bne @131
	lfs f0, float_180_8041acc8(r2)
	fadds f1, f0, f31
	bl revise360
	fmr f31, f1
	@131:
	lfs f3, float_10_8041ace4(r2)
	lis r0, 0x4330
	lfs f1, 0x198(r29)
	fmuls f0, f3, f31
	stw r0, 0x70(r1)
	fmuls f1, f3, f1
	lfd f2, 0x90(r30)
	stw r0, 0x60(r1)
	fctiwz f0, f0
	fctiwz f1, f1
	stfd f0, 0x68(r1)
	stfd f1, 0x78(r1)
	lwz r0, 0x6c(r1)
	lwz r3, 0x7c(r1)
	xoris r0, r0, 0x8000
	xoris r3, r3, 0x8000
	stw r0, 0x64(r1)
	stw r3, 0x74(r1)
	lfd f0, 0x60(r1)
	lfd f1, 0x70(r1)
	fsubs f0, f0, f2
	fsubs f1, f1, f2
	fdivs f0, f0, f3
	fdivs f1, f1, f3
	fsubs f1, f0, f1
	bl revise360
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	bge @132
	li r0, 0x0
	b @133
	@132:
	li r0, 0x1
	@133:
	cmpwi r0, 0x0
	bne @134
	fsubs f1, f31, f30
	lfs f0, float_90_8041acd8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @135
	fcmpo cr0, f30, f31
	ble @135
	lfs f0, float_360_8041ace0(r2)
	fadds f31, f31, f0
	b @135
	@134:
	fsubs f1, f31, f30
	lfs f0, float_90_8041acd8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @135
	fcmpo cr0, f30, f31
	bge @135
	lfs f0, float_360_8041ace0(r2)
	fadds f30, f30, f0
	@135:
	lfs f4, float_10_8041ace4(r2)
	lis r0, 0x4330
	li r4, 0x0
	stw r0, 0x70(r1)
	fmuls f2, f4, f31
	lfd f3, 0x90(r30)
	lfs f1, float_90_8041acd8(r2)
	mr r3, r4
	lfs f0, float_0_8041acbc(r2)
	fctiwz f2, f2
	stfd f2, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f2, 0x70(r1)
	fsubs f2, f2, f3
	fdivs f3, f2, f4
	fsubs f2, f3, f1
	fcmpo cr0, f2, f0
	bge @136
	lfs f0, float_360_8041ace0(r2)
	li r4, 0x1
	fadds f2, f2, f0
	@136:
	lfs f1, float_90_8041acd8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f1, f3, f1
	fcmpo cr0, f1, f0
	ble @137
	fsubs f1, f1, f0
	li r4, 0x2
	@137:
	cmpwi r4, 0x1
	bne @138
	fcmpo cr0, f1, f30
	bge @139
	fcmpo cr0, f30, f2
	bge @139
	li r3, 0x1
	b @139
	@138:
	cmpwi r4, 0x2
	bne @140
	fcmpo cr0, f1, f30
	bge @139
	fcmpo cr0, f30, f2
	bge @139
	li r3, 0x1
	b @139
	@140:
	cmpwi r4, 0x0
	bne @139
	fcmpo cr0, f30, f2
	blt @141
	fcmpo cr0, f1, f30
	bge @139
	@141:
	li r3, 0x1
	@139:
	cmpwi r3, 0x0
	bne @142
	fsubs f1, f31, f30
	lfs f0, float_180_8041acc8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @142
	fcmpo cr0, f31, f30
	ble @143
	lfs f0, float_360_8041ace0(r2)
	fsubs f31, f31, f0
	b @142
	@143:
	lfs f0, float_360_8041ace0(r2)
	fsubs f30, f30, f0
	@142:
	fsubs f0, f30, f31
	lfs f1, float_1p2_8041acec(r2)
	fmadds f31, f1, f0, f31
	fmr f1, f31
	bl revise360
	fmr f31, f1
	lfs f1, 0x1a8(r31)
	bl toMovedir
	lbz r0, 0x43(r31)
	extsb. r0, r0
	beq @144
	lfs f0, float_180_8041acc8(r2)
	fadds f1, f0, f1
	bl revise360
	@144:
	lfs f5, float_10_8041ace4(r2)
	lis r0, 0x4330
	li r4, 0x0
	stw r0, 0x70(r1)
	fmuls f3, f5, f31
	lfd f4, 0x90(r30)
	lfs f2, float_135_8041ace8(r2)
	mr r3, r4
	lfs f0, float_0_8041acbc(r2)
	fctiwz f3, f3
	stfd f3, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f3, 0x70(r1)
	fsubs f3, f3, f4
	fdivs f4, f3, f5
	fsubs f3, f4, f2
	fcmpo cr0, f3, f0
	bge @145
	lfs f0, float_360_8041ace0(r2)
	li r4, 0x1
	fadds f3, f3, f0
	@145:
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f2, f4, f2
	fcmpo cr0, f2, f0
	ble @146
	fsubs f2, f2, f0
	li r4, 0x2
	@146:
	cmpwi r4, 0x1
	bne @147
	fcmpo cr0, f2, f1
	bge @148
	fcmpo cr0, f1, f3
	bge @148
	li r3, 0x1
	b @148
	@147:
	cmpwi r4, 0x2
	bne @149
	fcmpo cr0, f2, f1
	bge @148
	fcmpo cr0, f1, f3
	bge @148
	li r3, 0x1
	b @148
	@149:
	cmpwi r4, 0x0
	bne @148
	fcmpo cr0, f1, f3
	blt @150
	fcmpo cr0, f2, f1
	bge @148
	@150:
	li r3, 0x1
	@148:
	cmpwi r3, 0x1
	bne @151
	lbz r3, 0x43(r31)
	addi r0, r3, 0x1
	clrlwi r0, r0, 31
	stb r0, 0x43(r31)
	@151:
	lfs f1, float_270_8041acdc(r2)
	lfs f0, 0x198(r31)
	lbz r0, 0x43(r31)
	fadds f0, f1, f0
	extsb. r0, r0
	fsubs f1, f0, f31
	beq @152
	lfs f0, float_neg180_8041ad88(r2)
	b @153
	@152:
	lfs f0, float_0_8041acbc(r2)
	@153:
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x1a8(r31)
	lfs f0, float_200_8041ad8c(r2)
	lfs f1, 0x1a8(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @154
	lfs f1, float_270_8041acdc(r2)
	lfs f0, 0x198(r31)
	lbz r0, 0x43(r31)
	fadds f0, f1, f0
	extsb. r0, r0
	fsubs f1, f0, f31
	beq @155
	lfs f0, float_neg180_8041ad88(r2)
	b @156
	@155:
	lfs f0, float_0_8041acbc(r2)
	@156:
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x1a8(r31)
	@154:
	lfs f1, 0x1a8(r31)
	lfs f0, float_170_8041ad90(r2)
	fcmpo cr0, f1, f0
	bge @157
	lfs f1, float_270_8041acdc(r2)
	lfs f0, 0x198(r31)
	lbz r0, 0x43(r31)
	fadds f0, f1, f0
	extsb. r0, r0
	fsubs f1, f0, f31
	beq @158
	lfs f0, float_neg180_8041ad88(r2)
	b @159
	@158:
	lfs f0, float_0_8041acbc(r2)
	@159:
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x1a8(r31)
	@157:
	stfs f31, 0x1a0(r31)
	stfs f31, 0x19c(r31)
	@123:
	lfs f1, float_0_8041acbc(r2)
	lfs f0, 0x220(r31)
	fcmpu cr0, f1, f0
	beq @160
	lfs f2, float_3p1416_8041acc4(r2)
	lfs f1, 0x1a8(r31)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f0
	bl sin
	lfs f0, 0x220(r31)
	frsp f1, f1
	fneg f0, f0
	fmuls f1, f0, f1
	bl revise360
	stfs f1, 0xbc(r31)
	b @161
	@160:
	stfs f1, 0xbc(r31)
	@161:
	lbz r0, 0x24e(r31)
	extsb. r0, r0
	bne @162
	lbz r0, 0x24f(r31)
	extsb. r0, r0
	beq @163
	@162:
	lwz r0, 0x2a4(r31)
	ori r0, r0, 0x4000
	stw r0, 0x2a4(r31)
	@163:
	lfs f1, 0x180(r31)
	lfs f0, float_0_8041acbc(r2)
	fcmpu cr0, f1, f0
	beq @164
	bl marioGetPtr
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_0p004_8041ad30(r2)
	stfs f1, 0x148(r3)
	stfs f0, 0x158(r3)
	@164:
	bl marioGetPtr
	lfs f0, float_100_8041acb8(r2)
	mr r31, r3
	lwz r9, 0x54(r30)
	addi r3, r1, 0x18
	stfs f0, 0x14(r1)
	addi r4, r1, 0x24
	lwz r8, 0x58(r30)
	addi r5, r1, 0x30
	lwz r11, 0x8c(r31)
	addi r6, r1, 0x3c
	lwz r10, 0x90(r31)
	addi r7, r1, 0x14
	lwz r0, 0x5c(r30)
	stw r10, 0x1c(r1)
	stw r11, 0x18(r1)
	lfs f1, 0x1c(r1)
	lwz r10, 0x94(r31)
	stw r10, 0x20(r1)
	lfs f0, 0x1b8(r31)
	fadds f0, f1, f0
	stw r9, 0x24(r1)
	stw r8, 0x28(r1)
	stfs f0, 0x1c(r1)
	stw r0, 0x2c(r1)
	bl marioHitCheckVec
	cmplwi r3, 0x0
	beq @25
	lfs f0, 0x3c(r1)
	lfs f1, 0x44(r1)
	fmuls f2, f0, f0
	lfs f0, float_0_8041acbc(r2)
	fmuls f1, f1, f1
	fadds f3, f2, f1
	fcmpo cr0, f3, f0
	ble @165
	frsqrte f1, f3
	lfd f4, 0x70(r30)
	lfd f2, 0x78(r30)
	fmul f0, f1, f1
	fmul f1, f4, f1
	fnmsub f0, f3, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f4, f1
	fnmsub f0, f3, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f4, f1
	fnmsub f0, f3, f0, f2
	fmul f0, f1, f0
	fmul f3, f3, f0
	frsp f3, f3
	b @166
	@165:
	lfd f0, 0x80(r30)
	fcmpo cr0, f3, f0
	bge @167
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @166
	@167:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @168
	bge @169
	cmpwi r3, 0x0
	beq @170
	b @169
	@168:
	clrlwi. r0, r4, 9
	beq @171
	li r0, 0x1
	b @172
	@171:
	li r0, 0x2
	b @172
	@170:
	clrlwi. r0, r4, 9
	beq @173
	li r0, 0x5
	b @172
	@173:
	li r0, 0x3
	b @172
	@169:
	li r0, 0x4
	@172:
	cmpwi r0, 0x1
	bne @166
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@166:
	lfs f1, float_0_8041acbc(r2)
	lfs f0, 0x40(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f0, float_0p5_8041acc0(r2)
	lis r0, 0x4330
	stw r0, 0x70(r1)
	fabs f3, f1
	fadds f2, f0, f1
	lfd f0, 0x88(r30)
	lfd f1, 0x90(r30)
	fcmpo cr0, f3, f0
	fctiwz f0, f2
	stfd f0, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f2, f0, f1
	bge @174
	lfs f1, float_3p1416_8041acc4(r2)
	lfs f0, float_180_8041acc8(r2)
	fmuls f1, f1, f2
	fdivs f26, f1, f0
	fmr f1, f26
	bl sin
	frsp f0, f1
	fmr f1, f26
	stfs f0, 0xc(r1)
	bl cos
	lfs f3, float_5_8041acd0(r2)
	frsp f5, f1
	lfs f0, 0xc(r1)
	lfs f4, float_6_8041accc(r2)
	fmuls f2, f3, f0
	lfs f1, float_neg4_8041acd4(r2)
	fmuls f0, f3, f5
	stfs f5, 0x10(r1)
	fadds f2, f4, f2
	fadds f0, f1, f0
	stfs f2, 0x98(r31)
	stfs f0, 0x9c(r31)
	b @25
	@174:
	lfs f1, float_90_8041acd8(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x10
	bl sincosf
	lfs f0, float_100_8041acb8(r2)
	addi r3, r1, 0x18
	lwz r7, 0x60(r30)
	addi r4, r1, 0x24
	stfs f0, 0x14(r1)
	addi r5, r1, 0x30
	lwz r0, 0x68(r30)
	addi r6, r1, 0x3c
	stw r7, 0x48(r1)
	addi r7, r1, 0x14
	lfs f1, 0xc(r1)
	stw r0, 0x50(r1)
	lfs f0, 0x10(r1)
	stfs f1, 0x48(r1)
	lwz r9, 0x64(r30)
	stfs f0, 0x50(r1)
	lwz r0, 0x8c(r31)
	lwz r10, 0x90(r31)
	lwz r8, 0x48(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x50(r1)
	stw r10, 0x1c(r1)
	lwz r10, 0x94(r31)
	stw r9, 0x4c(r1)
	stw r10, 0x20(r1)
	stw r8, 0x24(r1)
	stw r9, 0x28(r1)
	stw r0, 0x2c(r1)
	bl marioHitCheckVec
	@25:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	psq_l f29, 0xc8(r1), 0, 0
	lfd f29, 0xc0(r1)
	psq_l f28, 0xb8(r1), 0, 0
	lfd f28, 0xb0(r1)
	psq_l f27, 0xa8(r1), 0, 0
	lfd f27, 0xa0(r1)
	psq_l f26, 0x98(r1), 0, 0
	lfd f26, 0x90(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	lwz r29, 0x84(r1)
	lwz r0, 0xf4(r1)
	lwz r28, 0x80(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void marioReInit_roll(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	bl marioGetPtr
	mr r30, r3
	li r3, 0x0
	li r4, 0x14
	bl __memAlloc
	mr r31, r3
	bl marioGetPtr
	stw r31, 0x288(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	li r4, 0x0
	li r5, 0x14
	bl memset
	bl marioGetPtr
	li r0, -0x1
	lis r4, str_802C5DD8@ha
	stw r0, 0x2a8(r3)
	addi r3, r4, str_802C5DD8@l
	li r4, 0x16
	li r0, 0x10
	lwz r5, 0xc(r30)
	clrrwi r5, r5, 1
	stw r5, 0xc(r30)
	sth r4, 0x2e(r30)
	lwz r4, 0x0(r30)
	oris r4, r4, 0x100
	stw r4, 0x0(r30)
	stw r0, 0x8(r30)
	bl marioPaperOn
	la r3, str_8041AD04(r2)
	bl marioChgPose
	lis r3, str_802C5DE8@ha
	addi r3, r3, str_802C5DE8@l
	bl marioChgPaper
	lwz r3, 0x4(r30)
	li r0, 0x1e
	ori r3, r3, 0x8
	stw r3, 0x4(r30)
	lwz r3, 0x4(r30)
	ori r3, r3, 0x100
	stw r3, 0x4(r30)
	stw r0, 0x44(r30)
	bl marioGetPtr
	lfs f0, float_14p8_8041ad0c(r2)
	mr r31, r3
	lfs f30, float_0_8041acbc(r2)
	stfs f0, 0x1b4(r3)
	stfs f0, 0x1b8(r3)
	lfs f0, rollData(r13)
	stfs f0, 0x188(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041acbc(r2)
	stfs f30, 0x0(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f0, float_neg6_8041ad10(r2)
	stfs f31, 0x4(r3)
	lfs f2, float_6_8041accc(r2)
	stfs f0, 0xb0(r31)
	lfs f1, float_0_8041acbc(r2)
	stfs f2, 0xb4(r31)
	lfs f0, float_1_8041ad14(r2)
	stfs f2, 0x98(r31)
	stfs f1, 0x9c(r31)
	stfs f0, 0xc8(r31)
	stfs f0, 0xcc(r31)
	stfs f0, 0xd0(r31)
	stfs f0, 0x130(r31)
	bl allPartyForceRideOn
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lfd f30, 0x10(r1)
	lwz r31, 0xc(r1)
	lwz r0, 0x34(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void rollEvtJumpSetup(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPtr
	mr r31, r3
	bl camFollowYOff
	lwz r3, 0x0(r31)
	li r0, 0x1
	oris r3, r3, 0x1
	stw r3, 0x0(r31)
	sth r0, 0x50(r31)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioSetRollDispDir(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	bl marioGetPtr
	mr r31, r3
	lfs f30, 0x1a0(r3)
	lfs f31, 0x19c(r3)
	bl marioGetPtr
	lfs f4, float_10_8041ace4(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5dd0@ha
	stw r0, 0x10(r1)
	fmuls f0, f4, f31
	lfd f3, double_to_int_802c5dd0@l(r4)
	lfs f1, float_135_8041ace8(r2)
	li r5, 0x0
	mr r30, r3
	fctiwz f2, f0
	lfs f0, float_0_8041acbc(r2)
	mr r3, r5
	stfd f2, 0x8(r1)
	lwz r0, 0xc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f2, 0x10(r1)
	fsubs f2, f2, f3
	fdivs f3, f2, f4
	fsubs f2, f3, f1
	fcmpo cr0, f2, f0
	bge @1
	lfs f0, float_360_8041ace0(r2)
	li r5, 0x1
	fadds f2, f2, f0
	@1:
	lfs f1, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f1, f3, f1
	fcmpo cr0, f1, f0
	ble @2
	fsubs f1, f1, f0
	li r5, 0x2
	@2:
	cmpwi r5, 0x1
	bne @3
	fcmpo cr0, f1, f30
	bge @4
	fcmpo cr0, f30, f2
	bge @4
	li r3, 0x1
	b @4
	@3:
	cmpwi r5, 0x2
	bne @5
	fcmpo cr0, f1, f30
	bge @4
	fcmpo cr0, f30, f2
	bge @4
	li r3, 0x1
	b @4
	@5:
	cmpwi r5, 0x0
	bne @4
	fcmpo cr0, f30, f2
	blt @6
	fcmpo cr0, f1, f30
	bge @4
	@6:
	li r3, 0x1
	@4:
	cmpwi r3, 0x1
	bne @7
	lfs f0, float_180_8041acc8(r2)
	fadds f1, f0, f31
	bl revise360
	fmr f31, f1
	@7:
	lfs f3, float_10_8041ace4(r2)
	lis r0, 0x4330
	lfs f1, 0x198(r30)
	lis r3, double_to_int_802c5dd0@ha
	fmuls f0, f3, f31
	stw r0, 0x8(r1)
	fmuls f1, f3, f1
	lfd f2, double_to_int_802c5dd0@l(r3)
	stw r0, 0x20(r1)
	fctiwz f0, f0
	fctiwz f1, f1
	stfd f0, 0x18(r1)
	stfd f1, 0x10(r1)
	lwz r0, 0x1c(r1)
	lwz r3, 0x14(r1)
	xoris r0, r0, 0x8000
	xoris r3, r3, 0x8000
	stw r0, 0x24(r1)
	stw r3, 0xc(r1)
	lfd f0, 0x20(r1)
	lfd f1, 0x8(r1)
	fsubs f0, f0, f2
	fsubs f1, f1, f2
	fdivs f0, f0, f3
	fdivs f1, f1, f3
	fsubs f1, f0, f1
	bl revise360
	lfs f0, float_180_8041acc8(r2)
	fcmpo cr0, f1, f0
	bge @8
	li r0, 0x0
	b @9
	@8:
	li r0, 0x1
	@9:
	cmpwi r0, 0x0
	bne @10
	fsubs f1, f31, f30
	lfs f0, float_90_8041acd8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @11
	fcmpo cr0, f30, f31
	ble @11
	lfs f0, float_360_8041ace0(r2)
	fadds f31, f31, f0
	b @11
	@10:
	fsubs f1, f31, f30
	lfs f0, float_90_8041acd8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @11
	fcmpo cr0, f30, f31
	bge @11
	lfs f0, float_360_8041ace0(r2)
	fadds f30, f30, f0
	@11:
	lfs f4, float_10_8041ace4(r2)
	lis r0, 0x4330
	lis r3, double_to_int_802c5dd0@ha
	li r5, 0x0
	fmuls f0, f4, f31
	stw r0, 0x18(r1)
	lfd f3, double_to_int_802c5dd0@l(r3)
	mr r4, r5
	lfs f1, float_90_8041acd8(r2)
	fctiwz f2, f0
	lfs f0, float_0_8041acbc(r2)
	stfd f2, 0x20(r1)
	lwz r0, 0x24(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x1c(r1)
	lfd f2, 0x18(r1)
	fsubs f2, f2, f3
	fdivs f3, f2, f4
	fsubs f2, f3, f1
	fcmpo cr0, f2, f0
	bge @12
	lfs f0, float_360_8041ace0(r2)
	li r5, 0x1
	fadds f2, f2, f0
	@12:
	lfs f1, float_90_8041acd8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f1, f3, f1
	fcmpo cr0, f1, f0
	ble @13
	fsubs f1, f1, f0
	li r5, 0x2
	@13:
	cmpwi r5, 0x1
	bne @14
	fcmpo cr0, f1, f30
	bge @15
	fcmpo cr0, f30, f2
	bge @15
	li r4, 0x1
	b @15
	@14:
	cmpwi r5, 0x2
	bne @16
	fcmpo cr0, f1, f30
	bge @15
	fcmpo cr0, f30, f2
	bge @15
	li r4, 0x1
	b @15
	@16:
	cmpwi r5, 0x0
	bne @15
	fcmpo cr0, f30, f2
	blt @17
	fcmpo cr0, f1, f30
	bge @15
	@17:
	li r4, 0x1
	@15:
	cmpwi r4, 0x0
	bne @18
	fsubs f1, f31, f30
	lfs f0, float_180_8041acc8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @18
	fcmpo cr0, f31, f30
	ble @19
	lfs f0, float_360_8041ace0(r2)
	fsubs f31, f31, f0
	b @18
	@19:
	lfs f0, float_360_8041ace0(r2)
	fsubs f30, f30, f0
	@18:
	fsubs f0, f30, f31
	lfs f1, float_1p2_8041acec(r2)
	fmadds f31, f1, f0, f31
	fmr f1, f31
	bl revise360
	fmr f31, f1
	lfs f1, 0x1a8(r31)
	bl toMovedir
	lbz r0, 0x43(r31)
	extsb. r0, r0
	beq @20
	lfs f0, float_180_8041acc8(r2)
	fadds f1, f0, f1
	bl revise360
	@20:
	lfs f5, float_10_8041ace4(r2)
	lis r0, 0x4330
	lis r3, double_to_int_802c5dd0@ha
	li r5, 0x0
	fmuls f0, f5, f31
	stw r0, 0x18(r1)
	lfd f4, double_to_int_802c5dd0@l(r3)
	mr r4, r5
	lfs f2, float_135_8041ace8(r2)
	fctiwz f3, f0
	lfs f0, float_0_8041acbc(r2)
	stfd f3, 0x20(r1)
	lwz r0, 0x24(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x1c(r1)
	lfd f3, 0x18(r1)
	fsubs f3, f3, f4
	fdivs f4, f3, f5
	fsubs f3, f4, f2
	fcmpo cr0, f3, f0
	bge @21
	lfs f0, float_360_8041ace0(r2)
	li r5, 0x1
	fadds f3, f3, f0
	@21:
	lfs f2, float_135_8041ace8(r2)
	lfs f0, float_360_8041ace0(r2)
	fadds f2, f4, f2
	fcmpo cr0, f2, f0
	ble @22
	fsubs f2, f2, f0
	li r5, 0x2
	@22:
	cmpwi r5, 0x1
	bne @23
	fcmpo cr0, f2, f1
	bge @24
	fcmpo cr0, f1, f3
	bge @24
	li r4, 0x1
	b @24
	@23:
	cmpwi r5, 0x2
	bne @25
	fcmpo cr0, f2, f1
	bge @24
	fcmpo cr0, f1, f3
	bge @24
	li r4, 0x1
	b @24
	@25:
	cmpwi r5, 0x0
	bne @24
	fcmpo cr0, f1, f3
	blt @26
	fcmpo cr0, f2, f1
	bge @24
	@26:
	li r4, 0x1
	@24:
	cmpwi r4, 0x1
	bne @27
	lbz r3, 0x43(r31)
	addi r0, r3, 0x1
	clrlwi r0, r0, 31
	stb r0, 0x43(r31)
	@27:
	lfs f1, float_270_8041acdc(r2)
	lfs f0, 0x198(r31)
	lbz r0, 0x43(r31)
	fadds f0, f1, f0
	extsb. r0, r0
	fsubs f1, f0, f31
	beq @28
	lfs f0, float_neg180_8041ad88(r2)
	b @29
	@28:
	lfs f0, float_0_8041acbc(r2)
	@29:
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x1a8(r31)
	lfs f0, float_200_8041ad8c(r2)
	lfs f1, 0x1a8(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @30
	lfs f1, float_270_8041acdc(r2)
	lfs f0, 0x198(r31)
	lbz r0, 0x43(r31)
	fadds f0, f1, f0
	extsb. r0, r0
	fsubs f1, f0, f31
	beq @31
	lfs f0, float_neg180_8041ad88(r2)
	b @32
	@31:
	lfs f0, float_0_8041acbc(r2)
	@32:
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x1a8(r31)
	@30:
	lfs f1, 0x1a8(r31)
	lfs f0, float_170_8041ad90(r2)
	fcmpo cr0, f1, f0
	bge @33
	lfs f1, float_270_8041acdc(r2)
	lfs f0, 0x198(r31)
	lbz r0, 0x43(r31)
	fadds f0, f1, f0
	extsb. r0, r0
	fsubs f1, f0, f31
	beq @34
	lfs f0, float_neg180_8041ad88(r2)
	b @35
	@34:
	lfs f0, float_0_8041acbc(r2)
	@35:
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x1a8(r31)
	@33:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r0, 0x54(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void marioRollForceCancel(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802c5d40@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	addi r29, r3, vec3_802c5d40@l
	bl marioGetPtr
	mr r31, r3
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x16
	bne @1
	bl marioGetPtr
	mr r30, r3
	lwz r3, 0x2a8(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @2
	bl psndSFXOff
	li r0, -0x1
	stw r0, 0x2a8(r30)
	@2:
	bl marioGetPtr
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_0p004_8041ad30(r2)
	stfs f1, 0x148(r3)
	stfs f0, 0x158(r3)
	lfs f1, 0x1a0(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f2, float_180_8041acc8(r2)
	fcmpo cr0, f1, f2
	cror eq, gt, eq
	bne @3
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_270_8041acdc(r2)
	stfs f1, 0x1a8(r31)
	stfs f1, 0x1ac(r31)
	stfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	b @4
	@3:
	stfs f2, 0x1a8(r31)
	lfs f0, float_90_8041acd8(r2)
	stfs f2, 0x1ac(r31)
	stfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	@4:
	bl marioSetSpec
	li r0, 0x0
	stw r0, 0x8(r31)
	lwz r3, 0x30(r29)
	lwz r0, 0x34(r29)
	stw r3, 0xb0(r31)
	stw r0, 0xb4(r31)
	lwz r0, 0x38(r29)
	stw r0, 0xb8(r31)
	lwz r3, 0x3c(r29)
	lwz r0, 0x40(r29)
	stw r3, 0x98(r31)
	stw r0, 0x9c(r31)
	lwz r0, 0x44(r29)
	stw r0, 0xa0(r31)
	lwz r3, 0x48(r29)
	lwz r0, 0x4c(r29)
	stw r3, 0xbc(r31)
	stw r0, 0xc0(r31)
	lwz r0, 0x50(r29)
	stw r0, 0xc4(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 8, 6
	stw r0, 0x0(r31)
	bl marioPaperOff
	bl marioAdjustMoveDir
	la r3, str_8041AD34(r2)
	bl marioChgPose
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @5
	bl marioGetPtr
	mr r4, r3
	li r3, 0x0
	lwz r4, 0x288(r4)
	bl __memFree
	li r31, 0x0
	bl marioGetPtr
	stw r31, 0x288(r3)
	@5:
	bl allPartyRideOff
	li r3, 0x0
	li r4, 0x0
	bl marioChgMotSub
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mot_roll_post(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802c5d40@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	addi r29, r3, vec3_802c5d40@l
	bl marioGetPtr
	mr r31, r3
	bl marioGetPtr
	mr r30, r3
	lwz r3, 0x2a8(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq @1
	bl psndSFXOff
	li r0, -0x1
	stw r0, 0x2a8(r30)
	@1:
	bl marioGetPtr
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_0p004_8041ad30(r2)
	stfs f1, 0x148(r3)
	stfs f0, 0x158(r3)
	lfs f1, 0x1a0(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f2, float_180_8041acc8(r2)
	fcmpo cr0, f1, f2
	cror eq, gt, eq
	bne @2
	lfs f1, float_0_8041acbc(r2)
	lfs f0, float_270_8041acdc(r2)
	stfs f1, 0x1a8(r31)
	stfs f1, 0x1ac(r31)
	stfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	b @3
	@2:
	stfs f2, 0x1a8(r31)
	lfs f0, float_90_8041acd8(r2)
	stfs f2, 0x1ac(r31)
	stfs f0, 0x19c(r31)
	stfs f0, 0x1a0(r31)
	@3:
	bl marioSetSpec
	li r0, 0x0
	stw r0, 0x8(r31)
	lwz r3, 0xc(r29)
	lwz r0, 0x10(r29)
	stw r3, 0xb0(r31)
	stw r0, 0xb4(r31)
	lwz r0, 0x14(r29)
	stw r0, 0xb8(r31)
	lwz r3, 0x18(r29)
	lwz r0, 0x1c(r29)
	stw r3, 0x98(r31)
	stw r0, 0x9c(r31)
	lwz r0, 0x20(r29)
	stw r0, 0xa0(r31)
	lwz r3, 0x24(r29)
	lwz r0, 0x28(r29)
	stw r3, 0xbc(r31)
	stw r0, 0xc0(r31)
	lwz r0, 0x2c(r29)
	stw r0, 0xc4(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 8, 6
	stw r0, 0x0(r31)
	bl marioPaperOff
	bl marioAdjustMoveDir
	la r3, str_8041AD34(r2)
	bl marioChgPose
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @4
	bl marioGetPtr
	mr r4, r3
	li r3, 0x0
	lwz r4, 0x288(r4)
	bl __memFree
	li r31, 0x0
	bl marioGetPtr
	stw r31, 0x288(r3)
	@4:
	bl allPartyRideOff
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 marioRollCancel(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 22, 22
	beq @3
	li r3, 0x0
	b @2
	@3:
	li r0, 0x14
	stw r0, 0x44(r3)
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	li r3, 0x1
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unk_8009f9c8(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	li r30, 0x0
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r31, r3
	rlwinm. r0, r0, 0, 7, 7
	bne @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x2a4(r31)
	rlwinm. r0, r0, 0, 22, 22
	beq @3
	li r3, 0x0
	b @2
	@3:
	bl marioGetPtr
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 22, 22
	beq @4
	li r0, 0x1
	b @5
	@4:
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 4, 4
	beq @6
	li r0, 0x1
	b @5
	@6:
	lwz r0, 0x1e4(r3)
	cmplwi r0, 0x0
	bne @7
	li r0, 0x1
	b @5
	@7:
	bl marioSlitChkWallAround
	cmpwi r3, 0x0
	beq @8
	li r0, 0x1
	b @5
	@8:
	li r0, 0x0
	@5:
	cmpwi r0, 0x0
	bne @9
	li r0, 0x14
	li r30, 0x1
	stw r0, 0x44(r31)
	li r3, 0x8
	bl camGetPtr
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	@9:
	mr r3, r30
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioForceRollAnime(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPtr
	mr r31, r3
	bl marioPaperOff
	li r3, 0x0
	bl marioChgPaper
	lis r3, str_802C5DD8@ha
	addi r3, r3, str_802C5DD8@l
	bl marioPaperOn
	la r3, str_8041AD04(r2)
	bl marioChgPose
	lis r3, str_802C5DE8@ha
	addi r3, r3, str_802C5DE8@l
	bl marioChgPaper
	lwz r0, 0x4(r31)
	ori r0, r0, 0x8
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	ori r0, r0, 0x100
	stw r0, 0x4(r31)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioResetRollSpd(void) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	stw r31, 0xc(r1)
	bl marioGetPtr
	mr r31, r3
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x16
	bne @1
	bl marioGetPtr
	lwz r0, 0x288(r3)
	cmplwi r0, 0x0
	beq @2
	lfs f30, float_0_8041acbc(r2)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	lfs f31, float_0_8041acbc(r2)
	stfs f30, 0x0(r3)
	bl marioGetPtr
	lwz r3, 0x288(r3)
	stfs f31, 0x4(r3)
	@2:
	lfs f0, float_0_8041acbc(r2)
	stfs f0, 0x180(r31)
	@1:
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lfd f30, 0x10(r1)
	lwz r0, 0x34(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 getRollEvtFlag(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	li r31, 0x0
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @1
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @1
	li r31, 0x1
	@1:
	lwz r0, 0x14(r1)
	mr r3, r31
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void clrRollEvtFlag(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r0, 0x2a4(r3)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x2a4(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void setRollEvtFlag(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r0, 0x2a4(r3)
	ori r0, r0, 0x100
	stw r0, 0x2a4(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 marioRollKeyDisable(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x16
	beq @1
	li r3, 0x1
	b @2
	@1:
	lwz r0, 0x44(r3)
	cmpwi r0, 0x0
	blt @3
	cmpwi r0, 0x1
	bgt @3
	li r3, 0x0
	b @2
	@3:
	cmpwi r0, 0x14
	blt @4
	cmpwi r0, 0x16
	bgt @4
	li r3, 0x0
	b @2
	@4:
	li r3, 0x1
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unk_8009fcbc(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r0, 0x2a4(r3)
	rlwinm. r0, r0, 0, 22, 22
	beq @1
	li r3, 0x1
	b @2
	@1:
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 4, 4
	beq @3
	li r3, 0x1
	b @2
	@3:
	lwz r0, 0x1e4(r3)
	cmplwi r0, 0x0
	bne @4
	li r3, 0x1
	b @2
	@4:
	bl marioSlitChkWallAround
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioRollFixOn(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x16
	bne @1
	lwz r0, 0x2a4(r3)
	ori r0, r0, 0x200
	stw r0, 0x2a4(r3)
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
