// Mario's paper slit motion (side-step through bars): turning sideways, sliding along walls and turning back.
#include "dolphin/types.h"
#include "driver/hitdrv.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "mot/mot_slit.h"
#include "mario/mario_hit.h"
#include "mario/mario_sbr.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#include "version.h"

#include "driver/mapdrv.h"
#include "mario/mario_pouch.h"
#include "party/party_motion.h"
#include <dolphin/pad.h>

double fabs(double);

int __abs(int);
#define abs __abs

#if VERSION >= VERSION_JP
void marioSlitReenter(void) {
    MarioWork* mario = marioGetPtr();
    marioChgMot2(MARIO_MOTION_SLIT);
    mario->slitState = 10;
    mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
}

void N_marioSlitSetAfterLand(void) {
    MarioWork* mario = marioGetPtr();
    marioChgMot2(MARIO_MOTION_SLIT);
    mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
}
#endif

BOOL marioSlitAbilityChk(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_SLIT_ABILITY_DISABLED) {
        return FALSE;
    }
    if (!pouchCheckItem(ITEM_PAPER_CURSE)) {
        return FALSE;
    }
    if (mario->flags & MARIO_FLAG_IS_8_BIT) {
        return FALSE;
    }
    return marioBgmodeChk() != 1;
}

s32 marioSlitButton(void) {
    MarioWork* mario = marioGetPtr();
#if VERSION >= VERSION_JP
    if (mario->trigFlags & MARIO_TRIG_FLAG_USE_PARTNER) {
        return 0;
    }
#endif
    if (marioKeyOffChk()) {
        return 0;
    }
    if (marioBgmodeChk() == 1) {
        return 0;
    }
#if VERSION <= VERSION_DEMO_US
    if (!(mario->flags & MARIO_FLAG_PAPER_MODE)) {
#else
    if (!(mario->dispFlags & MARIO_DISP_FLAG_SLIT)) {
#endif
        if (mario->buttonHold & PAD_TRIGGER_R) {
            return 1;
        }
    } else {
        if (mario->buttonHold & PAD_TRIGGER_R) {
            return 2;
        }
        if (mario->triggerR >= 50) {
            return 2;
        }
    }
    return 0;
}

BOOL marioSlitKeyDisable(void) {
    MarioWork* mario = marioGetPtr();
    s32 st;
    if (!(mario->flags & MARIO_FLAG_PAPER_MODE)) {
        return TRUE;
    }
    st = mario->slitState;
    if (st >= 0x50 && st <= 0x52) {
        return FALSE;
    }
    if (st >= 0x5a && st <= 0x5e) {
        return FALSE;
    }
    return TRUE;
}

#if VERSION >= VERSION_JP
BOOL U_marioSlitContinueChk(void) {
    MarioWork* mario = marioGetPtr();
    Vec pos;
    if (marioSlitButton()) {
        return TRUE;
    }
    if (marioSlitChkWallAround()) {
        return TRUE;
    }
    pos = mario->position;
    return marioCreviceWallChk(&pos) != 0;
}
#endif

BOOL marioCreviceWallChk(const Vec* p) {
    f32 offX;
    f32 offZ;
    f32 angA;
    f32 angB;
    HitEntry* hitA;
    HitEntry* hitB;
    f32 s;
    f32 c;
    f32 dist;
    f32 h = 10.0f;
    Vec pos;
    Vec dir;
    Vec outPos;
    Vec outNrm;

    marioGetPtr();
    sincosf(&s, &c, toMovedirSimple(270.0f));
    offX = 0.5f * (20.0f * s);
    offZ = 0.5f * (20.0f * c);
    angA = 0.0f;
    angB = angA;
    sincosf(&s, &c, toMovedirSimple(180.0f));
    dist = 20.0f;
    pos = *p;
    pos.y += 10.0f;
    {
        Vec t1 = {0, 0, 0};
        t1.x = s;
        t1.z = c;
        dir = t1;
    }
    hitA = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
    if (hitA) {
        angA = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
    }
    if (!hitA) {
        Vec t2 = {0, 0, 0};
        dist = 20.0f;
        t2.x = p->x + offX;
        t2.y = p->y + h;
        t2.z = p->z + offZ;
        pos = t2;
        hitA = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
        if (hitA) {
            angA = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
        }
    }
    if (!hitA) {
        Vec t3 = {0, 0, 0};
        dist = 20.0f;
        t3.x = p->x - offX;
        t3.y = p->y + h;
        t3.z = p->z - offZ;
        pos = t3;
        hitA = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
        if (hitA) {
            angA = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
        }
    }
    sincosf(&s, &c, toMovedirSimple(0.0f));
    dist = 20.0f;
    pos = *p;
    pos.y += 10.0f;
    {
        Vec u1 = {0, 0, 0};
        u1.x = s;
        u1.z = c;
        dir = u1;
    }
    hitB = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
    if (hitB) {
        angB = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
    }
    if (!hitB) {
        Vec u2 = {0, 0, 0};
        dist = 20.0f;
        u2.x = p->x + offX;
        u2.y = p->y + h;
        u2.z = p->z + offZ;
        pos = u2;
        hitB = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
        if (hitB) {
            angB = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
        }
    }
    if (!hitB) {
        Vec u3 = {0, 0, 0};
        dist = 20.0f;
        u3.x = p->x - offX;
        u3.y = p->y + h;
        u3.z = p->z - offZ;
        pos = u3;
        hitB = marioHitCheckVec(&pos, &dir, &outPos, &outNrm, &dist);
        if (hitB) {
            angB = angleABf(0.0f, 0.0f, outNrm.x, outNrm.z);
        }
    }
    if (hitA && hitB && __fabsf(180.0f - 0.5f * (angA + angB)) <= 10.0f) {
        return TRUE;
    }
    return FALSE;
}

void marioClearSlitFloor(void) {
    MarioWork* mario = marioGetPtr();
    mario->slitPosSet = 0;
}

BOOL marioGetSlitFloorPos(Vec* out) {
    MarioWork* mario = marioGetPtr();
    if (mario->slitPosSet) {
        *out = mario->slitPos;
        return TRUE;
    }
    return FALSE;
}

BOOL marioChkSlitThrouh(void) {
    MarioWork* mario = marioGetPtr();
    s32 st;
    if (mario->currMotionId != MARIO_MOTION_SLIT) {
        return FALSE;
    }
    st = mario->slitState;
    if (st >= 0x50 && st <= 0x5e) {
        return TRUE;
    }
    return FALSE;
}

BOOL marioChkSlitThrouhEnd(void) {
    MarioWork* mario = marioGetPtr();
    s32 st;
    if (mario->currMotionId != MARIO_MOTION_SLIT) {
        return FALSE;
    }
    st = mario->slitState;
    if (st == 0x52 || st == 0x5e) {
        return TRUE;
    }
    return FALSE;
}

void motSlitContinue(void) {
    s16 v;
    v = 0x14;
    marioChgMot2(MARIO_MOTION_SLIT);
    marioGetPtr()->slitState = v;
}

#if VERSION <= VERSION_DEMO_US
void motSlitContinue2(void) {
    MarioWork* mario = marioGetPtr();
    marioChgMot2(MARIO_MOTION_SLIT);
    if (!(mario->mot.slit.flags & 0x10)) {
        mario->slitState = 0x64;
    } else {
        mario->slitState = mario->mot.slit.resumeState;
    }
}
#endif

BOOL marioChkSlitEnd(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId != MARIO_MOTION_SLIT) {
        return FALSE;
    }
    return mario->slitState >= 0x64;
}

void motSlitCancel(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        mario->slitState = 0x64;
    }
}

void motSlitCancel2(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
#if VERSION >= VERSION_JP
        allPartyForceSlitOff();
#endif
        mario->slitState = 0x6e;
    }
}

void motSlitCancel3(void) {
    MarioWork* mario = marioGetPtr();
    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        mario->slitState = 0x78;
    }
}

BOOL marioGetMotSlitCancel3(void) {
    s32 st;
    BOOL r = FALSE;
    MarioWork* mario = marioGetPtr();
    if (mario->currMotionId == MARIO_MOTION_SLIT) {
        st = mario->slitState;
        if ((st >= 0x78 && st <= 0x7a) || (st >= 0x6e && st <= 0x70)) {
            r = TRUE;
        }
    }
    return r;
}

#define CLR_DISP 0xFEFFF3FF
static inline void slitSetDir(MarioWork* mario, f32 a) {
    if (revise360(mario->directionView - mario->targetYaw) <= 180.0f) {
        mario->displayDirection = 260.0f;
    } else {
        mario->displayDirection = 280.0f;
    }
}

void marioSlitForceCancel(void) {
    MarioWork* m = marioGetPtr();
    if (m->flags & MARIO_FLAG_PAPER_MODE) {
        m->flags &= ~MARIO_FLAG_PAPER_MODE;
        if (m->directionView >= 180.0f) {
            m->displayDirection = 0.0f;
            m->displayDirectionTarget = m->displayDirection;
        } else {
            m->displayDirection = 180.0f;
            m->displayDirectionTarget = m->displayDirection;
        }
        m->dispFlags &= CLR_DISP;
        m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
        m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
#if VERSION <= VERSION_DEMO_US
        m->wPlayerCollisionBox.x = 20.0f;
#else
        m->wPlayerCollisionBox.x = 10.0f;
#endif
        m->dispFlags &= CLR_DISP;
        marioPaperOff();
        mapResetPaperAmbColor();
        m->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
        marioAdjustMoveDir();
        {
            MarioWork* p = marioGetPtr();
            p->camShiftTargetZ = 0.0f;
            p->camShiftRate.z = 0.004f;
        }
        allPartyForceSlitOff();
    }
}

void mot_slit_post(void) {
#if VERSION <= VERSION_DEMO_US
    MarioWork* mario = marioGetPtr();
    u16 id;
    if (!(mario->flags & MARIO_FLAG_PAPER_MODE)) {
        if (mario->dispFlags & MARIO_DISP_FLAG_SLIT) {
            mario->wPlayerCollisionBox.x = 20.0f;
            if (mario->directionView >= 180.0f) {
                mario->displayDirection = 0.0f;
                mario->displayDirectionTarget = mario->displayDirection;
            } else {
                mario->displayDirection = 180.0f;
                mario->displayDirectionTarget = mario->displayDirection;
            }
            mario->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
            mario->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
            mario->dispFlags &= CLR_DISP;
            mario->dispFlags &= CLR_DISP;
            marioPaperOff();
            mapResetPaperAmbColor();
            mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
            marioAdjustMoveDir();
            allPartyForceSlitOff();
        }
    } else {
        id = mario->currMotionId;
        if (id == 1 || (u16)(id - 2) <= 5 || mario->currMotionId == MARIO_MOTION_JUMP_3) {
            return;
        }
        mario->flags &= ~MARIO_FLAG_PAPER_MODE;
        mario->wPlayerCollisionBox.x = 20.0f;
        if (mario->directionView >= 180.0f) {
            mario->displayDirection = 0.0f;
            mario->displayDirectionTarget = mario->displayDirection;
        } else {
            mario->displayDirection = 180.0f;
            mario->displayDirectionTarget = mario->displayDirection;
        }
        mario->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
        mario->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
        mario->dispFlags &= CLR_DISP;
        mario->dispFlags &= CLR_DISP;
        marioPaperOff();
        mapResetPaperAmbColor();
        mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
        marioAdjustMoveDir();
        allPartyForceSlitOff();
    }
}
#else
#if VERSION >= VERSION_US
    MarioWork* m = marioGetPtr();
    u16 id;
    if (m->slitState >= 10) {
        id = m->currMotionId;
        if (id == 0x15 || (u16)(id - 0xb) <= 1 || m->currMotionId <= 7 || m->currMotionId == MARIO_MOTION_JUMP_3) {
            return;
        }
    }
#else
    MarioWork* m = marioGetPtr();
    u16 id = m->currMotionId;
    if (id == 0x15 || (u16)(id - 0xb) <= 1 || m->currMotionId <= 7 || m->currMotionId == MARIO_MOTION_JUMP_3) {
        return;
    }
#endif
    if (!(m->flags & MARIO_FLAG_PAPER_MODE)) {
        if (m->dispFlags & MARIO_DISP_FLAG_SLIT) {
            m->wPlayerCollisionBox.x = 20.0f;
            if (m->directionView >= 180.0f) {
                m->displayDirection = 0.0f;
                m->displayDirectionTarget = m->displayDirection;
            } else {
                m->displayDirection = 180.0f;
                m->displayDirectionTarget = m->displayDirection;
            }
            m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
            m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
            m->dispFlags &= CLR_DISP;
            m->dispFlags &= CLR_DISP;
            marioPaperOff();
            mapResetPaperAmbColor();
            m->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
#if VERSION == VERSION_EU
            if (!(m->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                marioAdjustMoveDir();
            }
#else
            marioAdjustMoveDir();
#endif
            allPartyForceSlitOff();
        }
    } else if (m->currMotionId != MARIO_MOTION_FALL) {
        m->flags &= ~MARIO_FLAG_PAPER_MODE;
        m->wPlayerCollisionBox.x = 20.0f;
        if (m->directionView >= 180.0f) {
            m->displayDirection = 0.0f;
            m->displayDirectionTarget = m->displayDirection;
        } else {
            m->displayDirection = 180.0f;
            m->displayDirectionTarget = m->displayDirection;
        }
        m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
        m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
        m->dispFlags &= 0xFEFFF3FF;
        m->dispFlags &= CLR_DISP;
        marioPaperOff();
        mapResetPaperAmbColor();
        m->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
        marioAdjustMoveDir();
#if VERSION >= VERSION_US
        if (m->currMotionId != MARIO_MOTION_ROLL) {
            allPartyForceSlitOff();
        } else {
            U_allPartySlitOffReq();
        }
#else
        allPartyForceSlitOff();
#endif
    }
}
#endif

void marioForceSlitAnime(void) {
    MarioWork* mario = marioGetPtr();
    marioPaperOff();
    marioChgPaper(NULL);
    marioPaperOn("p_slit");
    marioChgPose("M_S_1");
    marioChgPaper("PM_S_1A");
    mario->dispFlags |= MARIO_DISP_FLAG_FRONT_POSE;
}

static inline void slitInit(void) {
    MarioWork* mario = marioGetPtr();
    mario->mot.slit.reserved_0 = 0.0f;
    mario->mot.slit.counter = 0;
    mario->mot.slit.count = 0;
    mario->mot.slit.timer = 0;
    mario->mot.slit.side = 0;
    mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
    mario->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
    mario->dispFlags |= MARIO_DISP_FLAG_FRONT_POSE;
    mario->dispFlags |= MARIO_DISP_FLAG_SLIT;
    if (mario->paperPoseId == -1) {
        GXColor tmp;
        GXColor col = {0, 0, 0, 255};
        col.r = 0xa8;
        col.g = 0xa8;
        col.b = 0xa8;
        tmp = col;
        mapSetPaperAmbColor(&tmp);
        marioPaperOn("p_slit");
    }
    if (!mario->controlStickSensitivity) {
        marioChgPose("M_S_1");
    }
    marioChgPaper("PM_S_1A");
}

void marioReInit_slit(void) {
    MarioWork* mario = marioGetPtr();
    slitInit();
    mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
    mario->currMotionId = MARIO_MOTION_SLIT;
    mario->slitState = 10;
    mario->displayDirection = 270.0f;
    mario->displayDirectionTarget = mario->displayDirection;
    marioChgPose("M_S_1");
    marioChgPaper("PM_S_1B");
    mario->slitState = 10;
    mario->mot.slit.count = 0;
    mario->wPlayerCollisionBox.x = 6.0f;
    mario->flags |= MARIO_FLAG_PAPER_MODE;
    mario->dispFlags |= MARIO_DISP_FLAG_SLIT;
    allPartySlitOn();
}

static inline BOOL slitContinueChk(void) {
    MarioWork* mario = marioGetPtr();
    Vec pos;
#if VERSION <= VERSION_DEMO_US
    if (marioSlitButton() == 2) {
#else
    if (marioSlitButton()) {
#endif
        return TRUE;
    }
    if (marioSlitChkWallAround()) {
        return TRUE;
    }
    pos = mario->position;
    if (marioCreviceWallChk(&pos)) {
        return TRUE;
    }
    return FALSE;
}

// In the slit, a dash drops to walking speed with the running pose.
static inline void slitLimitSpeed(MarioWork* mario) {
    mario->baseSpeed = mario->baseWalkSpeed;
    if (!(mario->trigFlags & MARIO_TRIG_FLAG_EVT_POSE)) {
        marioChgPose("M_R_1");
    }
    mario->mot.slit.flags |= 1;
}

static inline f32 slitWalkSpeed(void) {
    MarioWork* mario = marioGetPtr();
    f32 spd = mario->baseWalkSpeed;
    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        if (mario->mot.slit.timer != 0)
            return spd;
        {
            int a = mario->wStickDir1;
            int b = mario->wStickDir2;
            if (a * a + b * b <= 0xbd1) {
                spd *= 0.5f;
            }
        }
    } else if (mario->flags & MARIO_FLAG_BG_MODE) {
        spd *= 0.5f;
    }
    return spd;
}

// The camera stops shifting along z.
static inline void slitCamReset(void) {
    MarioWork* mario = marioGetPtr();
    mario->camShiftTargetZ = 0.0f;
    mario->camShiftRate.z = 0.004f;
}

void mot_slit(void) {
    MarioWork* m = marioGetPtr();
    f32 d;
    s32 st;
    if (!m->controlStickSensitivity) {
        m->trigFlags &= ~MARIO_TRIG_FLAG_EVT_POSE;
    }
    if (m->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        slitInit();
        m->slitState = 0;
        m->airTimer = 0;
    }
    if (marioRollChgChk()) {
        if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
            m->displayDirection = 0.0f;
            m->displayDirectionTarget = m->displayDirection;
        } else {
            m->displayDirection = 180.0f;
            m->displayDirectionTarget = m->displayDirection;
        }
        m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
        m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
        m->dispFlags &= CLR_DISP;
        marioPaperOff();
        m->flags &= ~MARIO_FLAG_PAPER_MODE;
        return;
    }
    switch (m->slitState) {
        case 0:
            m->slitTimer = 30;
            m->mot.slit.counter = 0;
            m->slitState = 2;
            m->mot.slit.lastY = m->position.y;
#if VERSION >= VERSION_US
            if (m->baseSpeed >= m->baseDashSpeed || m->controlStickSensitivity) {
#else
            if (m->baseSpeed >= m->baseDashSpeed) {
#endif
                slitLimitSpeed(m);
            }
            marioGetPtr();
            psndSFXOn_3D((char*)0x177, &m->position);
            break;
        case 2:
#if VERSION == VERSION_EU
            if (m->flags & MARIO_FLAG_FORCED_MOVEMENT) {
                break;
            }
#endif
#if VERSION >= VERSION_US
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                marioChgPose("M_S_1");
            } else {
                if (m->baseSpeed >= m->baseDashSpeed || m->controlStickSensitivity) {
                    slitLimitSpeed(m);
                }
                m->directionView = m->controlStickAngle;
            }
            if (--m->slitTimer <= 0) {
#else
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                marioChgPose("M_S_1");
            }
            if (--m->slitTimer <= 0) {
#endif
                m->flags |= MARIO_FLAG_PAPER_MODE;
                m->slitState = 4;
                m->wPlayerCollisionBox.x = 6.0f;
            }
            if (m->slitTimer == 0x14) {
                allPartySlitOn();
            }
            break;
        case 4:
            if (marioChkKey()) {
                if (!m->controlStickSensitivity) {
                    m->baseSpeed = 0.0f;
                    marioChgPose("M_S_1");
                }
                m->directionView = toMovedirSimple(m->displayDirection);
            }
#if VERSION == VERSION_EU
            if (!(m->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                if (m->baseSpeed >= m->baseDashSpeed) {
                    slitLimitSpeed(m);
                }
            }
#else
            if (m->baseSpeed >= m->baseDashSpeed) {
                slitLimitSpeed(m);
            }
#endif
            m->displayDirection = 270.0f;
            m->displayDirectionTarget = m->displayDirection;
            if (!m->controlStickSensitivity) {
                marioChgPose("M_S_1");
            }
            marioChgPaper("PM_S_1B");
            m->slitState = 10;
            m->mot.slit.count = 0;
        case 10:
            if (m->position.y != m->mot.slit.lastY) {
                slitCamReset();
            }
            m->mot.slit.lastY = m->position.y;
            if (m->forceMoveTimer != 0) {
                if (!(m->trigFlags & MARIO_TRIG_FLAG_EVT_POSE)) {
                    marioChgPose("M_W_1");
                }
                marioChgPaper("PM_S_1D");
                if (revise360(m->directionView - m->targetYaw) <= 180.0f) {
                    m->mot.slit.side = 1;
                    m->displayDirection = 260.0f;
                } else {
                    m->mot.slit.side = 2;
                    m->displayDirection = 280.0f;
                }
                break;
            }
            if (m->baseSpeed >= m->baseDashSpeed) {
                slitLimitSpeed(m);
            }
            if (marioChkKey()) {
                if (slitContinueChk() != TRUE) {
#if VERSION >= VERSION_JP
                    m->directionView = m->controlStickAngle;
#endif
                    m->slitState = 0x64;
                    break;
                }
            }
            if (marioChkJump()) {
                return;
            }
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                if (!m->mot.slit.counter) {
                    marioChgPose("M_S_1");
                    marioChgPaper("PM_S_1B");
                }
                break;
            }
            if (strcmp(m->animName, "M_I_Y") == 0) {
                marioChgPose("M_W_1");
            }
            if (!(m->mot.slit.flags & 1)) {
                slitCamReset();
            } else {
                m->mot.slit.flags &= ~1;
                slitCamReset();
            }
            m->baseSpeed = slitWalkSpeed();
            m->directionView = m->controlStickAngle;
            if (!(m->trigFlags & MARIO_TRIG_FLAG_EVT_POSE)) {
                marioChgPose("M_W_1");
            }
            d = revise360(m->controlStickAngle - m->targetYaw);
            if (d >= 315.0f || d <= 45.0f || (d >= 135.0f && d <= 225.0f)) {
                marioChgPaper("PM_S_1E");
            } else {
                marioChgPaper("PM_S_1D");
                if (revise360(m->directionView - m->targetYaw) <= 180.0f) {
                    m->mot.slit.side = 1;
                    m->displayDirection = 260.0f;
                } else {
                    m->mot.slit.side = 2;
                    m->displayDirection = 280.0f;
                }
            }
            m->slitState = 0x14;
            break;
    }
    switch (m->slitState) {
        case 0x14:
#if VERSION >= VERSION_JP
            if (m->mot.slit.timer > 0) {
                m->mot.slit.timer = 0;
                marioChgPaper("PM_S_1D");
                m->displayDirection = (revise360(m->directionView - m->targetYaw) <= 180.0f) ? 260.0f : 280.0f;
#if VERSION >= VERSION_US
                // US: stop as soon as the stick is released
                if (!marioChkKey()) {
                    m->baseSpeed = 0.0f;
                    m->slitState = 10;
                    m->mot.slit.count = 0;
                    marioChgPose("M_S_1");
                    marioChgPaper("PM_S_1B");
                    break;
                }
#endif
            }
#endif
            if (marioChkKey()) {
                if (slitContinueChk() != TRUE) {
                    m->slitState = 0x64;
                }
            }
            if (!(m->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING))) {
                marioChkJump();
            }
            if (marioChkKey()) {
                if (!m->controlStickSensitivity) {
                    m->baseSpeed = 0.0f;
                    if (++m->mot.slit.count < 6) {
                        if (slitContinueChk() != TRUE) {
                            m->slitState = 0x64;
                        }
                        break;
                    } else {
                        m->slitState = 4;
                        break;
                    }
                } else {
                    s32 sum;
                    m->mot.slit.count = 0;
                    sum = abs((s8)m->wStickDir1) + abs((s8)m->wStickDir2);
                    if (!(m->trigFlags & MARIO_TRIG_FLAG_EVT_POSE)) {
                        marioChgPose((sum < 0x44) ? "M_W_1" : "M_R_1");
                    }
                }
            }
            if (marioChkKey()) {
                m->directionView = m->controlStickAngle;
                m->baseSpeed = slitWalkSpeed();
            }
            d = revise360(m->controlStickAngle - m->targetYaw);
            if (d >= 315.0f || d <= 45.0f || (d >= 135.0f && d <= 225.0f)) {
                marioChgPaper("PM_S_1E");
                m->mot.slit.count = 6;
                m->mot.slit.side = 0;
                m->displayDirection = (revise360(m->directionView - m->targetYaw) <= 180.0f) ? 260.0f : 280.0f;
                break;
            } else {
                marioChgPaper("PM_S_1D");
                d = revise360(m->directionView - m->targetYaw);
                if (m->mot.slit.side == 0) {
                    m->mot.slit.side = (d >= 180.0f) ? 2 : 1;
                }
                if (m->mot.slit.side == 1) {
                    if (d >= 180.0f) {
                        marioChgPaper("PM_S_2");
                        m->mot.slit.timer = 6;
                        m->slitState = 0x15;
                        m->mot.slit.side = 2;
                        m->baseSpeed = slitWalkSpeed();
#if VERSION >= VERSION_JP
                        m->displayDirection = 260.0f;
#endif
#if VERSION >= VERSION_US
                        // US: stop as soon as the stick is released
                        if (!marioChkKey()) {
                            m->mot.slit.timer = 0;
                            m->baseSpeed = 0.0f;
                            m->slitState = 10;
                            m->mot.slit.count = 0;
                            marioChgPose("M_S_1");
                            marioChgPaper("PM_S_1B");
                            break;
                        }
#endif
                    }
                } else if (m->mot.slit.side == 2) {
                    if (d <= 180.0f) {
                        marioChgPaper("PM_S_2");
                        m->mot.slit.timer = 6;
                        m->slitState = 0x15;
                        m->mot.slit.side = 1;
                        m->baseSpeed = slitWalkSpeed();
#if VERSION >= VERSION_JP
                        m->displayDirection = 280.0f;
#endif
#if VERSION >= VERSION_US
                        // US: stop as soon as the stick is released
                        if (!marioChkKey()) {
                            m->mot.slit.timer = 0;
                            m->baseSpeed = 0.0f;
                            m->slitState = 10;
                            m->mot.slit.count = 0;
                            marioChgPose("M_S_1");
                            marioChgPaper("PM_S_1B");
                            break;
                        }
#endif
                    }
                }
            }
            break;
        case 0x15:
            if (--m->mot.slit.timer > 0) {
#if VERSION >= VERSION_US
                // US: stop as soon as the stick is released
                if (!marioChkKey()) {
                    m->mot.slit.timer = 0;
                    m->baseSpeed = 0.0f;
                    m->slitState = 10;
                    m->mot.slit.count = 0;
                    marioChgPose("M_S_1");
                    marioChgPaper("PM_S_1B");
                    break;
                }
#endif
                break;
            }
            marioChgPaper("PM_S_1D");
            m->slitState = 0x14;
#if VERSION <= VERSION_DEMO_US
            m->displayDirection = (revise360(m->directionView - m->targetYaw) <= 180.0f) ? 260.0f : 280.0f;
#else
            m->displayDirection = (m->mot.slit.side == 1) ? 260.0f : 280.0f;
#endif
            break;
    }
    if (m->flags & MARIO_FLAG_PAPER_MODE) {
        if (m->hitobjPush != NULL) {
#if VERSION <= VERSION_DEMO_US
            if (hitGetAttr(m->hitobjPush) & 0x2000) {
                HitCheckQuery q;
                f32 sn, cs;
                d = revise360(m->controlStickAngle - m->targetYaw);
                if (d > 90.0f && d < 270.0f) {
                    m->mot.slit.pushDir = 180.0f;
                } else {
                    m->mot.slit.pushDir = 0.0f;
                }
                if (++m->mot.slit.counter >= sysMsec2Frame(50)) {
                    m->directionView = revise360(m->mot.slit.pushDir + m->targetYaw);
                    sincosf(&sn, &cs, m->directionView);
                    q.targetPos = m->position;
                    q.targetPos.y += 11.0f;
                    {
                        Vec tmp = {0, 0, 0};
                        tmp.x = sn;
                        tmp.z = cs;
                        q.targetDir = tmp;
                    }
                    q.targetDistance = 20.0f;
                    if (hitCheckVecHitObjXZ(&q, m->hitobjPush)) {
                        m->slitState = 0x50;
                    }
                }
            } else {
                m->mot.slit.counter = 0;
            }
#else
            if (m->hitobjStandOn != NULL && m->currMotionId == MARIO_MOTION_SLIT) {
                if (hitGetAttr(m->hitobjPush) & 0x2000) {
                    HitCheckQuery q;
                    HitCheckQuery* qp;
                    f32 sn, cs;
                    d = revise360(m->controlStickAngle - m->targetYaw);
                    if (d > 90.0f && d < 270.0f) {
                        m->mot.slit.pushDir = 180.0f;
                    } else {
                        m->mot.slit.pushDir = 0.0f;
                    }
                    if (++m->mot.slit.counter >= sysMsec2Frame(50)) {
                        qp = &q;
                        m->directionView = revise360(m->mot.slit.pushDir + m->targetYaw);
                        m->mot.slit.counter = 0;
                        sincosf(&sn, &cs, m->directionView);
                        {
                            Vec tmp = {0, 0, 0};
                            q.targetPos.x = m->position.x;
                            q.targetPos.y = 11.0f + m->position.y;
                            q.targetPos.z = m->position.z;
                            tmp.x = sn;
                            tmp.z = cs;
                            q.targetDir = tmp;
                        }
                        q.targetDistance = 20.0f;
                        if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
                            q.targetPos.x = m->position.x;
                            q.targetPos.z = m->position.z;
                            q.targetDistance = 20.0f;
                            movePos(&qp->targetPos.x, &qp->targetPos.z, 1.0f, reviseAngle(90.0f + m->moveDirection));
                            if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
                                q.targetPos.x = m->position.x;
                                q.targetPos.z = m->position.z;
                                q.targetDistance = 20.0f;
                                movePos(&qp->targetPos.x, &qp->targetPos.z, 1.0f, reviseAngle(m->moveDirection - 90.0f));
                                if (hitCheckVecHitObjXZ(qp, m->hitobjPush)) {
                                    m->slitState = 0x50;
                                }
                            }
                        }
                    }
                } else {
                    m->mot.slit.counter = 0;
                }
            }
#endif
        } else {
            st = m->slitState;
            if (!(st >= 0x5a && st <= 0x5e) && m->hitobjStandOn != NULL && (hitGetAttr(m->hitobjStandOn) & 0x2000)) {
                m->mot.slit.counter += 3;
                marioChgPaper("PM_S_1H");
#if VERSION <= VERSION_DEMO_US
                if (m->mot.slit.counter >= 0xf) {
#else
                if (m->mot.slit.counter >= 0xf && m->currMotionId == MARIO_MOTION_SLIT) {
#endif
                    m->slitState = 0x5a;
                }
            } else {
                m->mot.slit.counter--;
                if (m->mot.slit.counter < 0) {
                    m->mot.slit.counter = 0;
                }
            }
        }
    }
    switch (m->slitState) {
        case 0x50:
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
            slitCamReset();
            m->flags |= MARIO_FLAG_CHG_MOT_DISABLED;
            if (0.0f == m->mot.slit.pushDir) {
                marioChgPaper("PM_S_1F");
            } else {
                marioChgPaper("PM_S_1G");
            }
            m->flags |= MARIO_FLAG_WALLS_DISABLED;
            m->slitTimer = 20;
            m->baseSpeed = (2.0f * m->wPlayerCollisionBox.x) / (f32)m->slitTimer;
            m->slitState = 0x51;
            m->flags |= MARIO_FLAG_GONE_THROUGH_BARS;
            break;
        case 0x51:
            if (--m->slitTimer <= 0) {
                m->slitState = 0x52;
            }
            break;
        case 0x52:
            camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX_DISABLE;
            m->flags &= ~MARIO_FLAG_WALLS_DISABLED;
            m->slitState = 0x14;
            m->flags &= ~MARIO_FLAG_CHG_MOT_DISABLED;
            break;
    }
    switch (m->slitState) {
        case 0x5a:
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
            slitCamReset();
            m->flags |= MARIO_FLAG_CHG_MOT_DISABLED;
            marioChgPaper("PM_S_1H");
            m->slitTimer = sysMsec2Frame(500);
            m->baseSpeed = 0.0f;
            m->slitState = 0x5b;
            {
                MarioWork* p = marioGetPtr();
                p->slitPosSet = 1;
                // copy
                p->slitPos = p->position;
            }
        case 0x5b:
#if VERSION <= VERSION_DEMO_US
            m->slitTimer = 20;
#else
            m->slitTimer = 15;
#endif
            m->slitState = 0x5c;
            m->flags |= MARIO_FLAG_FLOORS_DISABLED;
            marioSetFallPara();
            m->flags &= ~MARIO_FLAG_IS_JUMPING;
            m->flags |= (MARIO_FLAG_IS_FALLING | MARIO_FLAG_HAS_INPUT_JUMP);
        case 0x5c:
            m->displayDirection = (revise360(m->directionView - m->targetYaw) <= 180.0f) ? 260.0f : 280.0f;
            if (--m->slitTimer > 0) {
                break;
            }
            m->slitState = 0x5d;
            m->flags &= ~MARIO_FLAG_FLOORS_DISABLED;
#if VERSION >= VERSION_JP
            m->flags &= ~MARIO_FLAG_CHG_MOT_DISABLED;
#endif
        case 0x5d:
            if (m->hitobjStandOn == NULL) {
                break;
            }
            m->flags &= ~(MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_HAS_INPUT_JUMP);
            m->slitState = 0x5e;
        case 0x5e:
            camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX_DISABLE;
            m->slitState = 0x14;
#if VERSION <= VERSION_DEMO_US
            m->flags &= ~MARIO_FLAG_CHG_MOT_DISABLED;
#endif
            break;
    }
    switch (m->slitState) {
        case 0x64:
            m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
            m->mot.slit.flags |= 0x10;
#endif
            m->slitTimer2 = 0;
            m->flags &= ~MARIO_FLAG_PAPER_MODE;
            m->wPlayerCollisionBox.x = 20.0f;
#if VERSION >= VERSION_US
            if (m->controlStickSensitivity) {
                slitLimitSpeed(m);
            }
#endif
            if (m->baseSpeed == 0.0f) {
                marioChgPose("M_S_1");
            }
            marioChgPaper("PM_S_1C");
            m->slitTimer2 = 30;
            m->slitState = 0x65;
            if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
                m->displayDirection = 0.0f;
                m->displayDirectionTarget = m->displayDirection;
                if (!m->controlStickSensitivity) {
                    m->directionView = toMovedirSimple(m->displayDirection);
                }
            } else {
                m->displayDirection = 180.0f;
                m->displayDirectionTarget = m->displayDirection;
                if (!m->controlStickSensitivity) {
                    m->directionView = toMovedirSimple(m->displayDirection);
                }
            }
            psndSFXOn_3D((char*)0x178, &m->position);
        case 0x65:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
#endif
#if VERSION == VERSION_EU
            if (m->flags & MARIO_FLAG_FORCED_MOVEMENT) {
                break;
            }
#endif
#if VERSION >= VERSION_US
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                marioChgPose("M_S_1");
            } else {
                slitLimitSpeed(m);
                m->directionView = m->controlStickAngle;
            }
#else
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                marioChgPose("M_S_1");
            }
#endif
            if (--m->slitTimer2 > 0) {
                break;
            }
            m->slitState = 0x66;
            break;
        case 0x66:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
#endif
#if VERSION == VERSION_EU
            if (!(m->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                if (!m->controlStickSensitivity) {
                    m->baseSpeed = 0.0f;
                    marioChgPose("M_S_1");
                } else {
                    slitLimitSpeed(m);
                }
            }
#elif VERSION >= VERSION_US
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                marioChgPose("M_S_1");
            } else {
                slitLimitSpeed(m);
            }
#else
            if (!m->controlStickSensitivity) {
                m->baseSpeed = 0.0f;
                marioChgPose("M_S_1");
            }
#endif
            m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
            m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
            m->dispFlags &= CLR_DISP;
            marioPaperOff();
            mapResetPaperAmbColor();
            m->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
#if VERSION == VERSION_EU
            if (!(m->flags & MARIO_FLAG_FORCED_MOVEMENT)) {
                marioAdjustMoveDir();
            }
#else
            marioAdjustMoveDir();
#endif
#if VERSION <= VERSION_JP
            allPartySlitOff();
#endif
            slitCamReset();
            marioChgMotSub(MARIO_MOTION_STAY, 0);
            break;
        case 0x6e:
            m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
            m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
            m->flags &= ~MARIO_FLAG_CHG_MOT_DISABLED;
            m->flags &= ~MARIO_FLAG_WALLS_DISABLED;
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
            m->mot.slit.flags |= 0x10;
#endif
            m->slitTimer2 = 0;
            m->flags &= ~MARIO_FLAG_PAPER_MODE;
            m->wPlayerCollisionBox.x = 20.0f;
            if (!m->controlStickSensitivity) {
                marioChgPose("M_S_1");
            }
            marioChgPaper("PM_S_1C");
            m->slitTimer2 = 30;
            m->slitState = 0x6f;
            m->baseSpeed = 0.0f;
            if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
                m->displayDirection = 0.0f;
                m->displayDirectionTarget = m->displayDirection;
                m->directionView = toMovedirSimple(m->displayDirection);
            } else {
                m->displayDirection = 180.0f;
                m->displayDirectionTarget = m->displayDirection;
                m->directionView = toMovedirSimple(m->displayDirection);
            }
            psndSFXOn_3D((char*)0x178, &m->position);
        case 0x6f:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
#endif
            if (--m->slitTimer2 > 0) {
                break;
            }
            m->slitState = 0x70;
            break;
        case 0x70:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
#endif
            m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
            m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
            m->dispFlags &= CLR_DISP;
            marioPaperOff();
            mapResetPaperAmbColor();
            m->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
            marioAdjustMoveDir();
            allPartySlitOff();
            slitCamReset();
            marioChgMot(MARIO_MOTION_STAY);
            break;
        case 0x78:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
            m->mot.slit.flags |= 0x10;
#endif
            m->slitTimer2 = 0;
            m->flags &= ~MARIO_FLAG_PAPER_MODE;
            m->wPlayerCollisionBox.x = 20.0f;
            if (!m->controlStickSensitivity) {
                marioChgPose("M_S_1");
            }
            marioChgPaper("PM_S_1C");
            m->slitTimer2 = 30;
            m->slitState = 0x79;
            m->baseSpeed = 0.0f;
            if (revise360(m->directionView - m->targetYaw) >= 180.0f) {
                m->displayDirection = 0.0f;
                m->displayDirectionTarget = m->displayDirection;
                m->directionView = toMovedirSimple(m->displayDirection);
            } else {
                m->displayDirection = 180.0f;
                m->displayDirectionTarget = m->displayDirection;
                m->directionView = toMovedirSimple(m->displayDirection);
            }
            psndSFXOn_3D((char*)0x178, &m->position);
        case 0x79:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
#endif
            if (--m->slitTimer2 > 0) {
                break;
            }
            m->slitState = 0x7a;
            break;
        case 0x7a:
#if VERSION <= VERSION_DEMO_US
            m->mot.slit.resumeState = m->slitState;
#endif
            m->flags &= ~MARIO_FLAG_PARTY_WALK_DISABLED;
            m->flags &= ~MARIO_FLAG_GONE_THROUGH_BARS;
            m->flags &= ~MARIO_FLAG_WALLS_DISABLED;
            m->dispFlags &= CLR_DISP;
            marioPaperOff();
            mapResetPaperAmbColor();
            m->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
            marioAdjustMoveDir();
            allPartySlitOff();
            slitCamReset();
            marioChgMot(MARIO_MOTION_STAY);
            break;
    }
}
