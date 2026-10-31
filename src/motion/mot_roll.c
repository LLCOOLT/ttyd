// Mario's tube (roll) motion: rolling up, moving through small gaps and unrolling.
#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mariost.h"
#include "libc_decls.h"
#include "mario/mario_sbr.h"
#include "party.h"
#include "system.h"
#include "memory.h"
#include "pmario_sound.h"
#include <string.h>
#include <math.h>
#include "mario/mario_hit.h"
#include "version.h"
#include <dolphin/pad.h>

// Bits of MarioWork.mot.roll.flags (all cleared when the roll starts).
enum MotRollFlag {
    ROLL_FLAG_FLAT_TURN = 0x10,     // Unknown: never set; on flat ground damps the speed and turns Mario round (makeVec)
    ROLL_FLAG_NO_SLOPE = 0x20,      // Unknown: never set; skips the push down a sloped floor
    ROLL_FLAG_EVT = 0x100,          // setRollEvtFlag: a script moves the tube (getRollEvtFlag)
    ROLL_FLAG_FIXED = 0x200,        // marioRollFixOn: Mario cannot leave Tube Mode
    ROLL_FLAG_SFX_ON = 0x1000,      // the rolling sound has been started
    ROLL_FLAG_STICK_MOVED = 0x4000, // the stick was tilted; nothing reads it
    ROLL_FLAG_KEEP_SPEED = 0x10000, // Unknown: never set; skips the base speed update from the roll velocity
};

typedef struct MotRollWork {
    f32 spdX;          // 0x00: roll velocity x (marioResetRollSpd clears it)
    f32 spdZ;          // 0x04: roll velocity z
    s32 squashTrigger; // 0x08: nonzero restarts the squash animation (-> squashState 1)
    s32 squashState;   // 0x0C: y-scale squash state machine (1.4 / back to 1.0)
    s32 squashTimer;   // 0x10: never used
#if VERSION >= VERSION_US
    s32 sfxId; // 0x14: US only, roll loop (0x17B), -1 when off
#endif
} MotRollWork; // size 0x14 JP, 0x18 US

f32 roll_grx;
f32 roll_grz;
s32 roll_flyout_flag2;
static __declspec(section ".rodata") Vec rollOfs = {0.0f, 40.0f, 0.0f};

/**
 * Tuning values of Mario's paper tube rolling: top speed, slowing, the slope push (180 or 140
 * by which way he rolls across the tilt), and the speed factor on slopes.
 */
f32 rollData[] = {3.0f, -0.05f, -0.5f, 0.5f, 7.0f, 180.0f, 140.0f, 10.0f, 1.2f, 2.0f, 0.8f};

// ground tilt (degrees) below which a slope does not push the roll
#if VERSION <= VERSION_DEMO_US
#define ROLL_TILT_POS 0.0f
#define ROLL_TILT_NEG 0.0f
#else
#define ROLL_TILT_POS 0.05f
#define ROLL_TILT_NEG -0.05f
#endif

/** Truncates x to one decimal place (toward zero). */
static inline f32 trunc10(f32 x) {
    s32 i = (s32)(10.0f * x);
    f32 f = (f32)i;
    return f / 10.0f;
}

/** 1 if angle x (degrees) lies outside the arc of +/-half around center, handling the wrap at 0/360; 0 if inside. */
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

/** Wrapper of angOutT: 1 if angle x is outside +/-half degrees of center. */
static inline s32 angOut(f32 center, f32 half, f32 x) {
    return angOutT(center, half, x);
}

/* repurposed unused inline: angOut on the mario stick angle, with everything read inside */
// FAKE: k025/rabs/rollRad/rollCos/rSin are invented one-line inline helpers. Their result temps get
// later inline numbering, which gives the target FPR colouring in mot_roll (fmadds operand order, makeVec c
// in f31) and marioRollCan (v26 in f26, fabs/sin/cos volatiles). Behaviour-identical to the expressions they wrap.
static inline f32 k025(void) {
    return 0.025f;
}
/** sin of a (radians) as a float. */
static inline f32 rSin(f32 a) {
    return (f32)sin(a);
}
/** Absolute value of x. */
static inline f32 rabs(f32 x) {
    return __fabsf(x);
}
/** Degrees to radians. */
static inline f32 rollRad(f32 d) {
    return 3.1415927f * d / 180.0f;
}
/** cos of a (radians) as a float. */
static inline f32 rollCos(f32 a) {
    return (f32)cos(a);
}
/** 1 if the control stick points outside +/-half degrees of Mario's move direction (angOut with the stick angle). */
static inline s32 makeVec(f32 half) {
    s32 w = 0;
    s32 r = w;
    MarioWork* mario = marioGetPtr();
    f32 c = (f32)(s32)(10.0f * mario->moveDirection) / 10.0f;
    f32 x = angleABf(0.0f, 0.0f, (f32)(s32)mario->wStickDir1, (f32)(s32)mario->wStickDir2);
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

// The displayed facing while rolling (marioSetRollDispDir, mot_roll): b (the move direction) is pulled towards
// a and the facing is turned to match. A statement macro, not an inline function: as an inline, both callers
// compile differently.
// FAKE: in ROLL_DISP_DIR, dd = tb_ - ty_ (was -(ty_ - tb_); differs only in the sign of zero, and dd is
// only compared with 180) and a dead int-guarded re-def of ty_ (COLOURING M) keep ty_ as a named value created before tb_, as the target fsubs f1,f0,f1
#define ROLL_DISP_DIR(a, b, m2)                                                                                   \
    if (angOut(b, 135.0f, a) == 1) {                                                                              \
        b = revise360(180.0f + b);                                                                                \
    }                                                                                                             \
    {                                                                                                             \
        s32 g_;                                                                                                   \
        f32 ty_;                                                                                                  \
        f32 dd;                                                                                                   \
        s32 sgn;                                                                                                  \
        f32 tb_;                                                                                                  \
        ty_ = trunc10((m2)->targetYaw);                                                                           \
        tb_ = trunc10(b);                                                                                         \
        g_ = 0;                                                                                                   \
        if (g_ != 0) {                                                                                            \
            ty_ = 0.0f;                                                                                           \
        }                                                                                                         \
        dd = revise360(tb_ - ty_);                                                                                \
        sgn = (dd < 180.0f) ? 0 : 1;                                                                              \
        if (sgn == 0) {                                                                                           \
            if (__fabsf(b - a) > 90.0f) {                                                                         \
                if (a > b) {                                                                                      \
                    b += 360.0f;                                                                                  \
                }                                                                                                 \
            }                                                                                                     \
        } else {                                                                                                  \
            if (__fabsf(b - a) > 90.0f) {                                                                         \
                if (a < b) {                                                                                      \
                    a += 360.0f;                                                                                  \
                }                                                                                                 \
            }                                                                                                     \
        }                                                                                                         \
    }                                                                                                             \
    if (angOut(b, 90.0f, a) == 0) {                                                                               \
        if (__fabsf(b - a) > 180.0f) {                                                                            \
            if (b > a) {                                                                                          \
                b -= 360.0f;                                                                                      \
            } else {                                                                                              \
                a -= 360.0f;                                                                                      \
            }                                                                                                     \
        }                                                                                                         \
    }                                                                                                             \
    b = 1.2f * (a - b) + b;                                                                                       \
    b = revise360(b);                                                                                             \
    {                                                                                                             \
        f32 md = toMovedir(mario->displayDirection);                                                              \
        if (mario->hammerDir) {                                                                                   \
            md = revise360(180.0f + md);                                                                          \
        }                                                                                                         \
        if (angOut(b, 135.0f, md) == 1) {                                                                         \
            mario->hammerDir = (mario->hammerDir + 1) & 1;                                                        \
        }                                                                                                         \
    }                                                                                                             \
    {                                                                                                             \
        f32 t_ = 270.0f + mario->targetYaw - b;                                                                   \
        mario->displayDirection = revise360(t_ + (mario->hammerDir ? -180.0f : 0.0f));                            \
    }                                                                                                             \
    if (mario->displayDirection >= 200.0f) {                                                                      \
        mario->displayDirection = revise360(270.0f + mario->targetYaw - b + (mario->hammerDir ? -180.0f : 0.0f)); \
    }                                                                                                             \
    if (mario->displayDirection < 170.0f) {                                                                       \
        mario->displayDirection = revise360(270.0f + mario->targetYaw - b + (mario->hammerDir ? -180.0f : 0.0f)); \
    }

void roll_upstairs(void);
static inline void marioRollCan(void);

/** Locks Tube Mode on (roll flag 0x200) so Mario cannot unroll; only while in the roll motion. */
void marioRollFixOn(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_ROLL) {
        mario->mot.roll.flags |= ROLL_FLAG_FIXED;
    }
}

/**
 * 1 when Mario could not unroll right now (locked, under a ceiling, not on the ground,
 * or walls too close around him); the item menu refuses items then.
 */
s32 marioRollCancelDisable(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->mot.roll.flags & ROLL_FLAG_FIXED) {
        return 1;
    }
    if ((mario->flags & MARIO_FLAG_IS_TOUCHING_CEILING) != 0) {
        return 1;
    }
    return !mario->hitobjStandOn ? 1 : (marioSlitChkWallAround() != 0);
}

/**
 * 0 while Mario is rolling up or unrolling (sub-motions 0-1, 0x14-0x16), 1 otherwise;
 * marioChkKey treats 0 as no control.
 */
s32 marioRollKeyDisable(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId != MARIO_MOTION_ROLL) {
        return 1;
    }
    {
        s32 sub = (s32)mario->currSubMotionId;
        if (sub >= 0 && sub <= 1) {
            return 0;
        }
        if (sub >= 0x14 && sub <= 0x16) {
            return 0;
        }
    }
    return 1;
}

/**
 * Marks the roll as script-driven (roll flag 0x100);
 * set by evt_mario's move commands while they move Mario in Tube Mode.
 */
void setRollEvtFlag(void) {
    MarioWork* mario = marioGetPtr();
    mario->mot.roll.flags |= ROLL_FLAG_EVT;
}

/** Clears the script-driven roll flag once evt_mario's move ends. */
void clrRollEvtFlag(void) {
    MarioWork* mario = marioGetPtr();
    mario->mot.roll.flags &= ~ROLL_FLAG_EVT;
}

/**
 * 1 while a script is moving Mario in Tube Mode (roll flag 0x100);
 * mario.c and mario_motion.c then skip the player-driven movement.
 */
s32 getRollEvtFlag(void) {
    s32 r = 0;
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_TUBE_MODE) {
        if (mario->mot.roll.flags & ROLL_FLAG_EVT) {
            r = 1;
        }
    }
    return r;
}

/** Stops the roll: clears the roll velocity and Mario's speed, if he is in Tube Mode. */
void marioResetRollSpd(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_ROLL) {
        if (marioGetPtr()->motStruct) {
            f32 a = 0.0f;
            f32 b;
            marioGetPtr()->motRoll->spdX = a;
            b = 0.0f;
            marioGetPtr()->motRoll->spdZ = b;
        }
        mario->baseSpeed = 0.0f;
    }
}

/** Re-applies the tube paper animation (p_roll, PM_R_1B) when mario.c rebuilds Mario's look while he is rolled up. */
void marioForceRollAnime(void) {
    MarioWork* mario = marioGetPtr();
    marioPaperOff();
    if (mario) {
    }
    marioChgPaper(0);
    marioPaperOn("p_roll");
    marioChgPose("M_I_U");
    marioChgPaper("PM_R_1B");
    mario->dispFlags |= MARIO_DISP_FLAG_NO_MIRROR;
    mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
}

/**
 * Starts unrolling (sub-motion 0x14) if Mario is in Tube Mode and could stand up here; returns 1 if it started.
 * Used by evt_mario when a script needs Mario out of Tube Mode (JP and later).
 */
s32 marioRollTryCancel(void) {
    s32 ret = 0;
    MarioWork* mario = marioGetPtr();
    if (!(mario->flags & MARIO_FLAG_TUBE_MODE)) {
        return 0;
    }
    if (mario->mot.roll.flags & ROLL_FLAG_FIXED) {
        return 0;
    }
    {
        s32 r;
        MarioWork* m = marioGetPtr();
        if (m->mot.roll.flags & ROLL_FLAG_FIXED) {
            r = 1;
        } else if (m->flags & MARIO_FLAG_IS_TOUCHING_CEILING) {
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
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
        }
    }
    return ret;
}

#if VERSION <= VERSION_DEMO_US
/**
 * Starts unrolling (sub-motion 0x14) unless Tube Mode is locked or there is a ceiling overhead;
 * returns 1 if it started. Called from evt_mario.
 */
s32 marioRollCancel(void) {
    s32 ret = 0;
    MarioWork* mario = marioGetPtr();
    if (!(mario->flags & MARIO_FLAG_TUBE_MODE)) {
        return 0;
    }
    if (mario->mot.roll.flags & ROLL_FLAG_FIXED) {
        return 0;
    }
    if (!(mario->flags & MARIO_FLAG_IS_TOUCHING_CEILING)) {
        ret = 1;
        mario->currSubMotionId = 0x14;
        camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
    }
    return ret;
}
#else
/**
 * Starts unrolling (sub-motion 0x14) unless Tube Mode is locked; returns 1 if it started. Called from evt_mario.
 * Unlike the demo it no longer checks for a ceiling here.
 */
s32 marioRollCancel(void) {
    MarioWork* mario = marioGetPtr();
    if (!(mario->flags & MARIO_FLAG_TUBE_MODE)) {
        return 0;
    }
    if (mario->mot.roll.flags & ROLL_FLAG_FIXED) {
        return 0;
    }
    mario->currSubMotionId = 0x14;
    camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
    return 1;
}
#endif

/**
 * Cleanup when the roll motion ends: stops the roll sound, resets the camera shift,
 * turns Mario to face left or right on screen, restores his normal collision (marioSetSpec),
 * clears Tube Mode and the paper animation, frees the motion's work and dismounts the partners.
 */
void mot_roll_post(void) {
    MarioWork* mario = marioGetPtr();
#if VERSION <= VERSION_DEMO_US
    MarioWork* m;
#else
    MarioWork* m = marioGetPtr();
#endif
#if VERSION <= VERSION_DEMO_US
#elif VERSION >= VERSION_US
    if (marioGetPtr()->motStruct && (u32)marioGetPtr()->motRoll->sfxId != (u32)-1) {
        psndSFXOff(marioGetPtr()->motRoll->sfxId);
        marioGetPtr()->motRoll->sfxId = -1;
    }
#else
    if ((u32)m->mot.roll.sfxId != (u32)-1) {
        psndSFXOff(m->mot.roll.sfxId);
        m->mot.roll.sfxId = -1;
    }
#endif
    m = marioGetPtr();
    m->camShiftTargetZ = 0.0f;
    m->camShiftRate.z = 0.004f;
    {
        f32 d = revise360(mario->directionView - mario->targetYaw);
        do {
            if (d >= 180.0f) {
                mario->displayDirection = 0.0f;
                mario->displayDirectionTarget = 0.0f;
                mario->moveDirection = 270.0f;
                mario->directionView = 270.0f;
            } else {
                mario->displayDirection = 180.0f;
                mario->displayDirectionTarget = 180.0f;
                mario->moveDirection = 90.0f;
                mario->directionView = 90.0f;
            }
        } while (0);
    }
    marioSetSpec();
    mario->rollFlags = 0;
    mario->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
    mario->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
    mario->rot = (Vec){0.0f, 0.0f, 0.0f};
    mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
    mario->dispFlags &= ~MARIO_DISP_FLAG_NO_MIRROR;
    mario->flags &= ~MARIO_FLAG_TUBE_MODE;
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

/**
 * Instantly turns Mario back from Tube Mode (the same reset as mot_roll_post) and puts him in the stay motion;
 * used by evt_mario.
 */
void marioRollForceCancel(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_ROLL) {
#if VERSION <= VERSION_DEMO_US
        MarioWork* m;
#else
        MarioWork* m = marioGetPtr();
#endif
#if VERSION <= VERSION_DEMO_US
#elif VERSION >= VERSION_US
        if (marioGetPtr()->motStruct && (u32)marioGetPtr()->motRoll->sfxId != (u32)-1) {
            psndSFXOff(marioGetPtr()->motRoll->sfxId);
            marioGetPtr()->motRoll->sfxId = -1;
        }
#else
        if ((u32)m->mot.roll.sfxId != (u32)-1) {
            psndSFXOff(m->mot.roll.sfxId);
            m->mot.roll.sfxId = -1;
        }
#endif
        m = marioGetPtr();
        m->camShiftTargetZ = 0.0f;
        m->camShiftRate.z = 0.004f;
        {
            f32 d = revise360(mario->directionView - mario->targetYaw);
            if (d >= 180.0f) {
                mario->displayDirection = 0.0f;
                mario->displayDirectionTarget = 0.0f;
                mario->moveDirection = 270.0f;
                do {
                    mario->directionView = 270.0f;
                } while (0);
            } else {
                mario->displayDirection = 180.0f;
                mario->displayDirectionTarget = 180.0f;
                mario->moveDirection = 90.0f;
                mario->directionView = 90.0f;
            }
        }
        marioSetSpec();
        mario->rollFlags = 0;
        mario->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
        mario->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
        mario->rot = (Vec){0.0f, 0.0f, 0.0f};
        mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
        mario->dispFlags &= ~MARIO_DISP_FLAG_NO_MIRROR;
        mario->flags &= ~MARIO_FLAG_TUBE_MODE;
        marioPaperOff();
        marioAdjustMoveDir();
        marioChgPose("M_S_1");
        if (marioGetPtr()->motStruct) {
            __memFree(0, marioGetPtr()->motStruct);
            mario = 0;
            marioGetPtr()->motStruct = (void*)mario;
        }
        allPartyRideOff();
        marioChgMotSub(MARIO_MOTION_STAY, 0);
    }
}

/**
 * Updates the facing shown while a script moves Mario in Tube Mode (ROLL_DISP_DIR),
 * called from mario.c's forced movement.
 */
void marioSetRollDispDir(void) {
    MarioWork* mario = marioGetPtr();
    f32 b, a;
    MarioWork* m2;
    a = mario->directionView;
    b = mario->moveDirection;
    m2 = marioGetPtr();
    ROLL_DISP_DIR(a, b, m2)
}

/** Starts a scripted jump in Tube Mode: evt_mario's jump command calls this instead of switching to the jump motion. */
void rollEvtJumpSetup(void) {
    MarioWork* mario = marioGetPtr();
    camFollowYOff();
    mario->flags |= MARIO_FLAG_IS_JUMPING;
    mario->airTimer = 1;
}

/**
 * Restores Tube Mode when Mario is re-entered on a new map while rolled up (marioEntry):
 * allocates the roll work, sets the tube animation, the 14.8 collision box and roll speed,
 * and seats the partners.
 */
void marioReInit_roll(void) {
    void* p;
    MarioWork* mario = marioGetPtr();
    f32 z0;
    f32 z1;
    p = __memAlloc(0, sizeof(MotRollWork));
    marioGetPtr()->motStruct = p;
    memset(marioGetPtr()->motStruct, 0, sizeof(MotRollWork));
    {
        MarioWork* t = marioGetPtr();
#if VERSION >= VERSION_US
        if (marioGetPtr()->motStruct)
            marioGetPtr()->motRoll->sfxId = -1;
#else
        t->mot.roll.sfxId = -1;
#endif
    }
    mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
    mario->currMotionId = MARIO_MOTION_ROLL;
    mario->flags |= MARIO_FLAG_TUBE_MODE;
    mario->rollFlags = 0x10;
    marioPaperOn("p_roll");
    marioChgPose("M_I_U");
    marioChgPaper("PM_R_1B");
    mario->dispFlags |= MARIO_DISP_FLAG_NO_MIRROR;
    mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
    mario->currSubMotionId = 0x1e;
    mario = marioGetPtr();
    z0 = 0.0f;
    mario->wPlayerCollisionBox.x = 14.8f;
    mario->wPlayerCollisionBox.y = 14.8f;
    mario->baseDashSpeed = rollData[0];
    marioGetPtr()->motRoll->spdX = z0;
    z1 = 0.0f;
    marioGetPtr()->motRoll->spdZ = z1;
    mario->rotOfs.x = -6.0f;
    mario->rotOfs.y = 6.0f;
    mario->dispOfs.x = 6.0f;
    mario->dispOfs.y = 0.0f;
    mario->scale.x = 1.0f;
    mario->scale.y = 1.0f;
    mario->scale.z = 1.0f;
    mario->tubeScaleY = 1.0f;
    allPartyForceRideOn();
}

/** 1 when Mario cannot unroll here: roll locked, ceiling overhead, no floor under him or walls around him. */
static inline s32 rollChk(void) {
    s32 r;
    MarioWork* mario = marioGetPtr();
    if (mario->mot.roll.flags & ROLL_FLAG_FIXED) {
        r = 1;
    } else if (mario->flags & MARIO_FLAG_IS_TOUCHING_CEILING) {
        r = 1;
    } else if (!mario->hitobjStandOn) {
        r = 1;
    } else if (marioSlitChkWallAround()) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

/**
 * Tube Mode motion: Mario rolls up into a tube, then rolls along with the stick,
 * momentum and slope push (rollData constants), jumps a little with A (not on eki_04's steep slopes),
 * and unrolls with B when there is room. Plays the rolling loop sound and squashes the tube on landing.
 */
void mot_roll(void) {
    MarioWork* mario = marioGetPtr();
    f32 angle;
    f32 velX;
    f32 velZ;
    f32 unusedF;
    f32 velZ2;
    f32 tmp;
    f32 tcA;
    f32 nx;
    f32 nz;
    f32 a31;
    f32 b31;
    f32 s;
    f32 rd;
    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
        mario->mot.roll.flags = 0;
        mario->mot.word[2] = 0;
        mario->mot.word[3] = 0;
        mario->mot.word[4] = 0;
        mario->mot.word[5] = 0;
        {
            void* p = __memAlloc(0, sizeof(MotRollWork));
            marioGetPtr()->motStruct = p;
        }
        memset(marioGetPtr()->motStruct, 0, sizeof(MotRollWork));
        {
            MarioWork* t = marioGetPtr();
#if VERSION >= VERSION_US
            if (marioGetPtr()->motStruct)
                marioGetPtr()->motRoll->sfxId = -1;
#else
            t->mot.roll.sfxId = -1;
#endif
        }
        mario->currSubMotionId = 0;
    }
    switch (mario->currSubMotionId) {
        case 0: {
            MarioWork* m;
            s32 z0 = 0;
            s32 z1;
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
            marioAdjustMoveDir();
#if VERSION <= VERSION_DEMO_US
            mario->hammerDir = 0;
#else
            angle = mario->displayDirection;
            if (angle < 90.0f || angle > 270.0f) {
                mario->hammerDir = 1;
                mario->directionView = revise360(270.0f - mario->targetYaw);
                mario->moveDirection = 270.0f;
            } else {
                mario->hammerDir = 0;
                mario->directionView = revise360(90.0f - mario->targetYaw);
                mario->moveDirection = 90.0f;
            }
#endif
            marioGetRubInit();
            mario->flags |= MARIO_FLAG_TUBE_MODE;
            mario->rollFlags = 0x10;
            mario->dispFlags |= MARIO_DISP_FLAG_NO_MIRROR;
            mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
            marioPaperOn("p_roll");
            marioChgPose("M_I_U");
            marioChgPaper("PM_R_1A");
            mario->multiTimer = 0x41;
            m = marioGetPtr();
            velZ = 0.0f;
            m->wPlayerCollisionBox.x = 14.8f;
            m->wPlayerCollisionBox.y = 14.8f;
            m->baseDashSpeed = rollData[0];
            marioGetPtr()->motRoll->spdX = velZ;
            velZ2 = 0.0f;
            marioGetPtr()->motRoll->spdZ = velZ2;
            m->rotOfs.x = -6.0f;
            m->rotOfs.y = 6.0f;
            m->dispOfs.x = 6.0f;
            m->dispOfs.y = 0.0f;
            m->scale.x = 1.0f;
            m->scale.y = 1.0f;
            m->scale.z = 1.0f;
            m->tubeScaleY = 1.0f;
            mario->airTimer = 0;
            if (mario->forceMoveTimer == 0) {
                mario->baseSpeed = 0.0f;
            }
            m = marioGetPtr();
            m->camShiftTargetZ = 0.4f;
            m->camShiftRate.z = 0.01f;
            m->camZoom = 2.0f;
            ((MarioWork*)m)->camZoomOfs = rollOfs;
            marioGetPtr()->motRoll->squashTrigger = z0;
            z1 = 0;
            marioGetPtr()->motRoll->squashState = z1;
            psndSFXOn_3D((char*)0x179, &mario->position);
            psndSFXOn_3D((char*)0x9f, &mario->position);
            mario->currSubMotionId = 1;
            break;
        }
        case 1:
            if (mario->multiTimer == 0x36) {
                allPartyRideShip();
            }
            mario->dispOfs.y += 0.1f;
            if (mario->dispOfs.y > 1.0f) {
                mario->dispOfs.y = 1.0f;
            }
            if (--mario->multiTimer <= 0) {
#if VERSION <= VERSION_DEMO_US
                angle = mario->displayDirection;
                if (angle < 90.0f || angle > 270.0f) {
                    mario->hammerDir = 1;
                    mario->directionView = revise360(270.0f - mario->targetYaw);
                    mario->moveDirection = 270.0f;
                } else {
                    mario->hammerDir = 0;
                    mario->directionView = revise360(90.0f - mario->targetYaw);
                    mario->moveDirection = 90.0f;
                }
#endif
                mario->currSubMotionId = 0x1e;
                marioChgPose("M_I_U");
                marioChgPaper("PM_R_1B");
                camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX_DISABLE;
            }
            break;
        case 0x14:
            mario->baseSpeed = 0.0f;
            mario->rot.x = 0.0f;
            mario->rot.z = 0.0f;
            mario->rotOfs.x = 0.0f;
            mario->rotOfs.y = 0.0f;
            angle = revise360(mario->directionView - mario->targetYaw);
            mario->dispOfs.x = (angle < 180.0f) ? 3.0f : -3.0f;
            mario->dispOfs.y = 0.0f;
            mario->multiTimer = 0x41;
            mario->currSubMotionId = 0x15;
            mario->displayDirection = 0.0f;
#if VERSION >= VERSION_JP
            {
                MarioWork* m = marioGetPtr();
#if VERSION >= VERSION_US
                if (marioGetPtr()->motStruct && (u32)marioGetPtr()->motRoll->sfxId != (u32)-1) {
                    psndSFXOff(marioGetPtr()->motRoll->sfxId);
                    marioGetPtr()->motRoll->sfxId = -1;
                }
#else
                if ((u32)m->mot.roll.sfxId != (u32)-1) {
                    psndSFXOff(m->mot.roll.sfxId);
                    m->mot.roll.sfxId = -1;
                }
#endif
            }
#endif
            {
                MarioWork* m = marioGetPtr();
                m->camShiftTargetZ = 0.0f;
                m->camShiftRate.z = 0.004f;
            }
            marioChgPaper("PM_R_1C");
            marioPaperLightOff();
            psndSFXOn_3D((char*)0x17a, &mario->position);
        case 0x15:
            if (--mario->multiTimer > 0) {
                angle = revise360(mario->directionView - mario->targetYaw);
                if (angle < 180.0f) {
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
                angle = revise360(mario->directionView - mario->targetYaw);
                if (angle >= 180.0f) {
                    mario->displayDirection = 0.0f;
                    mario->displayDirectionTarget = 0.0f;
                    mario->moveDirection = 270.0f;
                    mario->directionView = 270.0f;
                } else {
                    mario->displayDirection = 180.0f;
                    mario->displayDirectionTarget = 180.0f;
                    mario->moveDirection = 90.0f;
                    mario->directionView = 90.0f;
                }
                marioSetSpec();
                mario->rollFlags = 0;
#if VERSION <= VERSION_DEMO_US
                mario->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
                mario->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
                mario->rot = (Vec){0.0f, 0.0f, 0.0f};
#else
                marioOfsRotReset();
#endif
                mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
                mario->dispFlags &= ~MARIO_DISP_FLAG_NO_MIRROR;
                mario->flags &= ~MARIO_FLAG_TUBE_MODE;
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
                camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX_DISABLE;
                mario->currSubMotionId = 0x16;
            }
            break;
        case 0x16:
            marioChgMotSub(MARIO_MOTION_STAY, 0);
            break;
    }
    if (mario->currSubMotionId < 0x1e) {
        return;
    }
    if (mario->flags & MARIO_FLAG_IS_STEPPING) {
        roll_upstairs();
        return;
    }
#if VERSION <= VERSION_DEMO_US
    if (!(mario->mot.roll.flags & ROLL_FLAG_FIXED) && (mario->buttonTrg & PAD_BUTTON_B)) {
        if (!(mario->flags & MARIO_FLAG_IS_TOUCHING_CEILING)) {
            mario->currSubMotionId = 0x14;
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
        } else {
            mario->buttonTrg |= PAD_BUTTON_A;
        }
    }
#else
    if (mario->buttonTrg & PAD_BUTTON_B) {
        if (!rollChk()) {
            mario->currSubMotionId = 0x14;
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
        } else {
            mario->buttonTrg |= PAD_BUTTON_A;
        }
    }
#endif
    tmp = mario->tubeScaleY;
    if (marioGetPtr()->motRoll->squashTrigger) {
        s32 z = 0;
        s32 one;
        marioGetPtr()->motRoll->squashTrigger = z;
        one = 1;
        marioGetPtr()->motRoll->squashState = one;
        tmp = 1.0f;
    }
    switch (marioGetPtr()->motRoll->squashState) {
        case 1:
            if (tmp < 1.4f) {
                {
                    f32 k = 1.0f;
                    tmp = k * (1.4499999f - tmp) + tmp;
                }
                if (tmp >= 1.4f) {
                    tmp = 1.4f;
                }
            }
            if (mario->airTimer == 0) {
                s32 t = 2;
                marioGetPtr()->motRoll->squashState = t;
            }
            break;
        case 2:
            if (tmp > 0.4f) {
                tmp = 0.4f * (0.35f - tmp) + tmp;
                if (tmp <= 0.4f) {
                    s32 t = 3;
                    tmp = 0.4f;
                    marioGetPtr()->motRoll->squashState = t;
                }
            }
            break;
        case 3:
            if (tmp < 1.0f) {
                tmp = 0.5f * (1.05f - tmp) + tmp;
                if (tmp >= 1.0f) {
                    s32 t = 0;
                    marioGetPtr()->motRoll->squashState = t;
                    tmp = 1.0f;
                }
            }
            break;
    }
    mario->tubeScaleY = tmp;
#if VERSION <= VERSION_DEMO_US
    if (mario->airTimer == 0) {
        camFollowYOn();
    }
#endif
    if (!mario->hitobjStandOn && mario->hitobjFront && !marioChkBero(mario->hitobjFront)) {
        tmp = marioGetPtr()->motRoll->spdX;
        velZ2 = marioGetPtr()->motRoll->spdZ;
        tmp += 0.2f * -tmp;
        velZ2 += 0.2f * -velZ2;
        if (__fabsf(tmp) < 1.0f) {
            tmp = 0.0f;
        }
        if (__fabsf(velZ2) < 1.0f) {
            velZ2 = 0.0f;
        }
        marioGetPtr()->motRoll->spdX = tmp;
        marioGetPtr()->motRoll->spdZ = velZ2;
    }
    if (mario->hitobjStandOn) {
#if VERSION <= VERSION_DEMO_US
        if (mario->airTimer == 0 && (mario->buttonTrg & PAD_BUTTON_A)) {
            {
#else
        if (!(hitGetAttr(mario->hitobjStandOn) & (HIT_ATTR_DEEP_WATER | HIT_ATTR_SPIKES)) && mario->airTimer == 0 && (mario->buttonTrg & PAD_BUTTON_A)) {
            if (!(strcmp(gp->currentMapName, "eki_04") == 0 && __fabsf(mario->groundSlope) >= 40.0f)) {
#endif
                MarioWork* m = marioGetPtr();
                camFollowYOff();
                m->jumpVelocityY = 2.85f;
                m->jumpAccelerationY = -0.14f;
                m->jumpJerkY = 0.08f;
                m->jumpSnapY = -0.02f;
                m->flags |= MARIO_FLAG_IS_JUMPING;
                m->airTimer = 1;
                psndSFXOn_3D((char*)0x17c, &marioGetPtr()->position);
#if VERSION >= VERSION_JP
                mario->hitobjJumpFrom = mario->hitobjStandOn;
                mario->hitobjStandOn = 0;
                mario->fallStartPos = mario->position;
                mario->lastGroundPos = mario->position;
                camFollowYOff();
#endif
            }
        }
        marioUpdateCamCollision(mario->position);
#if VERSION <= VERSION_DEMO_US
    } else {
        mario->airTimer++;
        mario->airTimer--;
    }
    if (mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING)) {
        if (mario->hitobjHead) {
            mario->jumpVelocityY = -0.03f;
            mario->jumpAccelerationY = -0.02f;
            mario->jumpJerkY = -0.02f;
            mario->jumpSnapY = -0.002f;
            mario->flags |= MARIO_FLAG_IS_FALLING;
        }
    }
#else
        mario->airTimer = 0;
    }
    if (mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING)) {
        if (mario->hitobjHead) {
            if (mario->jumpVelocityY >= 0.0f) {
                mario->jumpVelocityY = -0.03f;
                mario->jumpAccelerationY = -0.02f;
                mario->jumpJerkY = -0.02f;
                mario->jumpSnapY = -0.002f;
            }
            mario->flags |= MARIO_FLAG_IS_FALLING;
        }
        if (mario->airTimer == 0 && mario->jumpVelocityY < 0.0f) {
            mario->fallStartPos = mario->position;
            camFollowYOn();
        }
        if (mario->position.y < mario->lastGroundPos.y) {
            camFollowYOn();
        }
        mario->airTimer++;
    }
#endif
    velX = marioGetPtr()->motRoll->spdX;
    velZ = marioGetPtr()->motRoll->spdZ;
    nx = 0.0f;
    nz = nx;
    if (!(mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING))) {
        f32 stickX, stickY;
        stickX = (f32)(s32)(s8)mario->wStickDir1;
        stickY = (f32)(s32)(s8)mario->wStickDir2;
        nz = distABf(nx, nx, stickX, stickY);
        angle = angleABf(0.0f, 0.0f, stickX, stickY);
        angle = revise360(mario->targetYaw + angle);
        tmp = 3.1415927f * angle / 180.0f;
        nx = nz * (f32)sin(tmp);
        nz = nz * -(f32)cos(tmp);
        angle = angleABf(0.0f, 0.0f, nx, nz);
        // FAKE: no-op (MarioWork*) cast on the directionView/groundRot reads below (were raw MWOFF offsets); the plain field reorders a const load
        tcA = ((MarioWork*)mario)->directionView;
        if (angOut(tcA, 135.0f, angle) == 1) {
            nz = distABf(0.0f, 0.0f, nx, nz);
            nx = -nz * (f32)sin(3.1415927f * mario->directionView / 180.0f);
            nz = nz * (f32)cos(3.1415927f * ((MarioWork*)mario)->directionView / 180.0f);
        }
    }
    if (!(mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING)) && !(mario->mot.roll.flags & ROLL_FLAG_NO_SLOPE)) {
        angle = angleABf(0.0f, 0.0f, velX, -velZ);
        if (((MarioWork*)mario)->groundRot.z > ROLL_TILT_POS) {
            tmp = (angle > 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * ((MarioWork*)mario)->groundRot.z / 180.0f);
                t = t * tmp;
                nx = nx - t;
            }
            if (nx <= -100.0f) {
                nx = -100.0f;
            }
        } else if (mario->groundRot.z < ROLL_TILT_NEG) {
            tmp = (angle < 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * mario->groundRot.z / 180.0f);
                t = t * tmp;
                nx = nx - t;
            }
            if (nx >= 100.0f) {
                nx = 100.0f;
            }
        }
        if (((MarioWork*)mario)->groundRot.x > ROLL_TILT_POS) {
            tmp = (angle > 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * ((MarioWork*)mario)->groundRot.x / 180.0f);
                t = t * tmp;
                nz = nz - t;
            }
            if (nz <= -100.0f) {
                nz = -100.0f;
            }
        } else if (mario->groundRot.x < ROLL_TILT_NEG) {
            tmp = (angle < 180.0f) ? rollData[5] : rollData[6];
            {
                f32 t = (f32)sin(3.1415927f * mario->groundRot.x / 180.0f);
                t = t * tmp;
                nz = nz - t;
            }
            if (nz >= 100.0f) {
                nz = 100.0f;
            }
        }
        angle = angleABf(0.0f, 0.0f, nx, nz);
        // FAKE: no-op (MarioWork*) cast on the directionView/groundRot reads below (were raw MWOFF offsets); the plain field reorders a const load
        tcA = ((MarioWork*)mario)->directionView;
        if (angOut(tcA, 135.0f, angle) == 1) {
            nz = distABf(0.0f, 0.0f, nx, -nz);
            nx = -nz * (f32)sin(3.1415927f * mario->directionView / 180.0f);
            nz = nz * (f32)cos(3.1415927f * ((MarioWork*)mario)->directionView / 180.0f);
        }
    }
#if VERSION >= VERSION_JP
    if (mario->targetNpc) {
        if (!marioChkBero(mario->hitobjFront)) {
            velX = 0.05f * -velX + velX;
            velZ = 0.05f * -velZ + velZ;
            if (__fabsf(velX) < 0.1f) {
                velX = 0.0f;
            }
            if (__fabsf(velZ) < 0.1f) {
                velZ = 0.0f;
            }
        }
    }
#endif
    if (mario->hitobjFront && !mario->wStickDir1 && !mario->wStickDir2 && !marioChkBero(mario->hitobjFront)) {
        velX = 0.6f * -velX + velX;
        velZ = 0.6f * -velZ + velZ;
        if (__fabsf(velX) < 0.1f) {
            velX = 0.0f;
        }
        if (__fabsf(velZ) < 0.1f) {
            velZ = 0.0f;
        }
    }
    if (mario->forceMoveTimer == 0 && !nx && !nz) {
        if (mario->hitobjWall) {
            if (!marioChkBero(mario->hitobjWall)) {
                f32 k = rollData[2];
                velX = velX * k + velX;
                velZ = velZ * k + velZ;
            }
        } else if (mario->hitobjStandOn && mario->airTimer == 0) {
            if (__fabsf((f32)(mario->groundSlope <= 1.0f))) {
                f32 k = rollData[1];
                velX = velX * k + velX;
                velZ = velZ * k + velZ;
            } else {
                f32 k = rollData[1];
                f32 a = velX * k;
                f32 b = velZ * k;
                velX = 6.4f * a + velX;
                velZ = 6.4f * b + velZ;
            }
        }
        {
            f32 l = rollData[3];
            if (__fabsf(velX) < l) {
                velX = 0.0f;
            }
        }
        {
            f32 l = rollData[3];
            if (__fabsf(velZ) < l) {
                velZ = 0.0f;
            }
        }
    } else { // correctness: target runs the speed clamp only on this path (first branch jumps past it)
        if ((mario->mot.roll.flags & ROLL_FLAG_FLAT_TURN) && mario->groundRot.z == 0.0f) {
            if (makeVec(135.0f) == 1) {
                velX = 0.2f * -velX + velX;
                velZ = 0.2f * -velZ + velZ;
                if (__fabsf(velX) < 1.0f) {
                    velX = 0.0f;
                }
                if (__fabsf(velZ) < 1.0f) {
                    velZ = 0.0f;
                }
                if (velX == 0.0f && velZ == 0.0f) {
                    mario->moveDirection = revise360(180.0f + mario->moveDirection);
                    mario->directionView = mario->moveDirection;
                }
            }
        }
        a31 = rollData[0] / 0.05f;
        tmp = 1.0f;
        if (mario->forceMoveTimer == 0 && __fabsf(mario->groundSlope) >= tmp) {
            f32 ang = angleABf(0.0f, 0.0f, velX, -velZ);
            f32 sp = mario->groundRot.z;
            if (sp > 0.0f) {
                if (ang > 180.0f) {
                    tmp = rollData[9];
                } else {
                    tmp = 1.0f;
                }
            } else if (sp < 0.0f) {
                if (ang < 180.0f) {
                    tmp = rollData[9];
                } else {
                    tmp = 1.0f;
                }
            }
        }
        a31 = a31 * tmp;
        tmp = velZ * velZ;
        if (velX * velX + tmp <= a31 * a31) {
            velX = nx * k025() + velX;
        } else {
            f32 n = -a31;
            velX = nx * k025() + velX;
            if (velX < n) {
                velX = n;
            }
            if (velX > a31) {
                velX = a31;
            }
        }
        b31 = rollData[0] / 0.05f;
        unusedF = 1.0f;
        if (mario->forceMoveTimer == 0 && __fabsf(mario->groundSlope) >= unusedF) {
            f32 ang = angleABf(0.0f, 0.0f, velX, -velZ);
            f32 sp = mario->groundRot.x;
            if (sp > 0.0f) {
                if (ang > 180.0f) {
                    unusedF = rollData[9];
                } else {
                    unusedF = 1.0f;
                }
            } else if (sp < 0.0f) {
                if (ang < 180.0f) {
                    unusedF = rollData[9];
                } else {
                    unusedF = 1.0f;
                }
            }
        }
        b31 = b31 * unusedF;
        if (velX * velX + tmp <= b31 * b31) {
            velZ = velZ - nz * k025();
        } else {
            f32 n = -b31;
            velZ = velZ - nz * k025();
            if (velZ < n) {
                velZ = n;
            }
            if (velZ > b31) {
                velZ = b31;
            }
        }
    }
    marioGetPtr()->motRoll->spdX = velX;
    marioGetPtr()->motRoll->spdZ = velZ;
    angle = -velZ;
    unusedF = angleABf(0.0f, 0.0f, velX, angle);
    velZ2 = 3.1415927f * unusedF / 180.0f;
    tmp = rollCos(velZ2);
    velZ2 = distABf(0.0f, 0.0f, velX * (f32)sin(velZ2), velZ * tmp);
    s = 0.05f * velZ2;
    if (!getRollEvtFlag() && mario->forceMoveTimer == 0) {
        unusedF = angleABf(0.0f, 0.0f, velX, angle);
        if (!(mario->mot.roll.flags & ROLL_FLAG_KEEP_SPEED)) {
            s = s * mario->playerGravity;
            if (s < 0.05f) {
                s = 0.0f;
            }
            mario->baseSpeed = s;
            if (s) {
                mario->directionView = unusedF;
            }
        }
    }
    if (mario->baseSpeed) {
        MarioWork* m = marioGetPtr();
#if VERSION >= VERSION_US
        if (marioGetPtr()->motStruct && (u32)marioGetPtr()->motRoll->sfxId == (u32)-1) {
            marioGetPtr()->motRoll->sfxId = (s32)psndSFXOn_3D((char*)0x17b, &m->position);
            m->mot.roll.flags |= ROLL_FLAG_SFX_ON;
        }
#else
        if ((u32)m->mot.roll.sfxId == (u32)-1) {
            m->mot.roll.sfxId = (s32)psndSFXOn_3D((char*)0x17b, &m->position);
            m->mot.roll.flags |= ROLL_FLAG_SFX_ON;
        }
#endif
    } else {
        MarioWork* m = marioGetPtr();
#if VERSION >= VERSION_US
        if (marioGetPtr()->motStruct && (u32)marioGetPtr()->motRoll->sfxId != (u32)-1) {
            psndSFXOff(marioGetPtr()->motRoll->sfxId);
            marioGetPtr()->motRoll->sfxId = -1;
        }
#else
        if ((u32)m->mot.roll.sfxId != (u32)-1) {
            psndSFXOff(m->mot.roll.sfxId);
            m->mot.roll.sfxId = -1;
        }
#endif
    }
    rd = rollData[4];
    {
        s32 flip;
        f32 sgn;
        f32 mv = toMovedir(mario->displayDirection);
        f32 pre;
        // FAKE: no-op (MarioWork*) cast on the directionView/groundRot reads below (were raw MWOFF offsets); the plain field reorders a const load
        tcA = ((MarioWork*)mario)->directionView;
        flip = angOut(tcA, 90.0f, mv);
        pre = mario->baseSpeed * rd;
        sgn = (flip == 1) ? -1.0f : 1.0f;
        mario->rot.z = revise360(pre * sgn + mario->rot.z);
    }
    if (mario->forceMoveTimer == 0 && !getRollEvtFlag() && s) {
        angle = mario->moveDirection;
        {
            MarioWork* m2 = marioGetPtr();
            ROLL_DISP_DIR(unusedF, angle, m2)
        }
        ((MarioWork*)mario)->directionView = angle;
        mario->moveDirection = angle;
    }
    if (mario->groundRot.z != 0.0f) {
        mario->rot.x = revise360(-mario->groundRot.z * (f32)sin(3.1415927f * mario->displayDirection / 180.0f));
    } else {
        mario->rot.x = 0.0f;
    }
    if (mario->wStickDir1 || mario->wStickDir2) {
        mario->mot.roll.flags |= ROLL_FLAG_STICK_MOVED;
    }
#if VERSION <= VERSION_DEMO_US
    if (!(mario->mot.roll.flags & ROLL_FLAG_FIXED) && (mario->buttonTrg & PAD_BUTTON_B) && !(mario->flags & MARIO_FLAG_IS_TOUCHING_CEILING) && mario->hitobjStandOn) {
        mario->currSubMotionId = 0x14;
        camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
    }
#endif
    if (mario->baseSpeed) {
        MarioWork* m = marioGetPtr();
        m->camShiftTargetZ = 0.0f;
        m->camShiftRate.z = 0.004f;
    }
    marioRollCan();
}

/**
 * Starts climbing a small step while rolling: Mario rises to mario->stepUpY over 3 frames.
 * Called from mario_hit.c when the step ahead is 5-11 units high.
 */
void roll_upstairs_on(void) {
    MarioWork* mario = marioGetPtr();
    mario->flags |= MARIO_FLAG_IS_STEPPING;
    mario->flags |= MARIO_FLAG_STOP_AIR_MOVEMENT;
    marioClearJumpPara();
    mario->multiTimer = 3;
    mario->jumpVelocityY = (mario->stepUpY - mario->position.y) / (f32)(s32)mario->multiTimer;
    mario->jumpVelocityY = 4.0f;
    mario->jumpAccelerationY = -0.42f;
    mario->jumpJerkY = 0.04f;
    mario->jumpSnapY = -0.01f;
}

// FAKE: keeps the following function(s) out of line as in the target; removing it changes the code
#pragma dont_inline on
/** Advances the rolling step climb started by roll_upstairs_on, clearing the step flags when it ends. */
void roll_upstairs(void) {
    MarioWork* mario = marioGetPtr();
    mario->position.y = mario->position.y + mario->jumpVelocityY;
    if ((s32)--mario->multiTimer <= 0) {
        mario->flags &= ~MARIO_FLAG_STOP_AIR_MOVEMENT;
        mario->flags &= ~MARIO_FLAG_USE_FORCE_DIRECTION;
        mario->flags &= ~MARIO_FLAG_IS_STEPPING;
    }
}

#pragma dont_inline reset

/** Falling in Tube Mode: drops at up to 10 units a frame and lands on the first floor found. */
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

/**
 * Tilts the tube to the slope of the ground under Mario (offsets it along the floor normal when the slope is
 * under 45 degrees).
 */
static inline void marioRollCan(void) {
    MarioWork* mario = marioGetPtr();
    f32 v26;
#if VERSION <= VERSION_DEMO_US
    {
        f32 s;
        f32 c;
        f32 ox, oy, oz;
        f32 dist;
        f32 nx, ny, nz;
        dist = 100.0f;
        if (marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y, mario->position.z, 0.0f, -1.0f, 0.0f)) {
            f32 sq = sqrtf(nx * nx + nz * nz);
            f32 ang = angleABf(0.0f, 0.0f, sq, -ny);
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
                marioHitCheck(&ox, &oy, &oz, &dist, &nx, &ny, &nz, mario->position.x, mario->position.y, mario->position.z, s, 0.0f, c);
            }
        }
    }
#else
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
            f32 sq = sqrtf(nrm.x * nrm.x + nrm.z * nrm.z);
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
#endif
}

// FAKE: stand-in for a stripped function; it only orders this file's float constants in .sdata2
/**
 * Never called (the link strips it): its stores only place float constants in the order the rest of the file
 * expects in the constant pool.
 */
void marioRollStrippedPool(void) {
    MarioWork* mario = marioGetPtr();
    mario->dispOfs.x = 100.0f;
    mario->dispOfs.y = 0.0f;
#if VERSION <= VERSION_DEMO_US
    // FAKE: DEMO: dead store that puts -1.0f third in the .sdata2 pool (the demo marioRollCan passes -1.0f to marioHitCheck); this function is never called and the link strips it
    mario->jumpVelocityY = -1.0f;
#endif
    mario->dispOfs.z = 0.5f;
    mario->dispOfs2.x = 3.1415927f;
    mario->dispOfs2.y = 180.0f;
    mario->dispOfs2.z = 6.0f;
    mario->rotOfs.x = 5.0f;
    mario->rotOfs.y = -4.0f;
    mario->rotOfs.z = 90.0f;
    mario->rot.x = 270.0f;
    mario->rot.y = 360.0f;
    mario->rot.z = 10.0f;
    mario->scale.x = 135.0f;
    mario->scale.y = 1.2f;
    mario->scale.z = sqrtf(mario->fallStartPos.x);
    mario->fallStartPos.y = __fabsf(mario->fallStartPos.z) < 45.0;
}
