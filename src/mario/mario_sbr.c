// Mario subroutines: stick and rub input, falling out of the map (bottomless respawn), move rate, gravity,
// touched NPC, and the paper/plane/boat checks.
#include "mario/mario_sbr.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "mario/mario_motion.h"
#include "mario/mario_party.h"
#include "driver/hitdrv.h"
#include "driver/seqdrv.h"
#include "party.h"
#include "system.h"
#include <string.h>
#include "party/party_yoshi.h"
#include <demo/DEMOPad.h>
#include "koopa.h"
#include "mot/mot_slit.h"
#include "mot/mot_walk.h"
#include "libc_decls.h"
#include "version.h"

#define REVISE360(a)        \
    while ((a) < 0.0f) {    \
        (a) += 360.0f;      \
    }                       \
    while ((a) >= 360.0f) { \
        (a) -= 360.0f;      \
    }

typedef struct RubWork {
    s32 state;              // 0x0, never used
    s32 count;              // 0x4
    s32 num;                // 0x8
    s32 idx;                // 0xC
    s32 dir;                // 0x10
    s32 start;              // 0x14
    s32 lastAngle;          // 0x18, never used
    s32 stallFrames;        // 0x1C, cleared on each turning step, never read
    s32 revDir;             // 0x20
    s32 idleTimer;          // 0x24
    u8 pad_28[0x3C - 0x28]; // 0x28, never accessed
    s16 hist[21];           // 0x3C
} RubWork;

void marioGetStick(f32* dir, f32* mag);

RubWork rubwork;

#if VERSION == VERSION_DEMO
// The demo has no respawn position in MarioWork: falling out of eki_04, gon_10 or muj_00 puts Mario at a fixed
// spot for that map, and anywhere else at (0, 74, 0) with the partners.
void marioBottomless(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (mario->position.y > -2000.0f) {
        return;
    }
    if (marioBgmodeChk() == TRUE) {
        marioChgMot(MARIO_MOTION_BOTTOMLESS);
        return;
    }
    if (strcmp(gp->currentMapName, "eki_04") == 0) {
        mario->position = (Vec){344.0f, 840.0f, 30.0f};
    } else if (strcmp(gp->currentMapName, "gon_10") == 0) {
        mario->position = (Vec){980.0f, 74.0f, -17.0f};
    } else if (strcmp(gp->currentMapName, "muj_00") == 0) {
        mario->position = (Vec){-182.0f, 25.0f, -104.0f};
    } else {
        mario->position = (Vec){0.0f, 74.0f, 0.0f};
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            party->position = mario->position;
        }
        party = partyGetPtr(marioGetExtraPartyId());
        if (party) {
            party->position = mario->position;
        }
        if (marioBgmodeChk() == TRUE) {
            mario->position.z = -450.0f;
        }
    }
    marioChgMot(MARIO_MOTION_FORCE_RESET);
}
#else
void marioBottomless(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (mario->position.y > -2000.0f) {
        return;
    }
    if (marioBgmodeChk() == TRUE) {
        marioChgMot(MARIO_MOTION_BOTTOMLESS);
    } else if (mario->bottomlessReload) {
        seqSetSeq(SEQ_MAP_CHANGE, gp->currentMapName, gp->beroEnterName);
    } else {
        mario->position = mario->bottomlessResetPosition;
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            party->position = mario->position;
        }
        party = partyGetPtr(marioGetExtraPartyId());
        if (party) {
            party->position = mario->position;
        }
        if (marioBgmodeChk() == TRUE) {
            mario->position.z = -450.0f;
        }
        marioChgMot(MARIO_MOTION_FORCE_RESET);
    }
}

void N_marioSetBottomlessRespawnPosOnBeroEntry(f32 x, f32 y, f32 z) {
    MarioWork* mario = marioGetPtr();
    Vec position;

    position = (Vec){x, y + 37.0f, z};
    mario->bottomlessResetPosition = position;
}

void N_marioSetBottomlessRespawnPos(f32 x, f32 y, f32 z) {
    MarioWork* mario = marioGetPtr();
    Vec position;

    position = (Vec){x, y, z};
    mario->bottomlessResetPosition = position;
}

void N_marioReloadMapOnBottomlessOn(void) {
    MarioWork* mario = marioGetPtr();
    mario->bottomlessReload = 1;
}

void N_marioReloadMapOnBottomlessOff(void) {
    MarioWork* mario = marioGetPtr();
    mario->bottomlessReload = 0;
}
#endif

BOOL marioSetDirEventMain(void) {
    MarioWork* mario = marioGetPtr();
    s32 frames;
    f32 target;

    if (!(mario->dispFlags & MARIO_DISP_FLAG_DIR_EVENT)) {
        return TRUE;
    }
    frames = sysMsec2Frame(mario->dirEvtMsec);
    if (frames > 0) {
        target = revise360(270.0f - mario->dirEvtTargetDir);
        target = (target - mario->dirEvtStartDir) * ((f32)mario->dirEvtFrame / (f32)frames);
        mario->displayDirection = revise360(mario->dirEvtStartDir + target);
        mario->displayDirectionTarget = mario->displayDirection;
        mario->directionView = toMovedirSimple(mario->displayDirection);
        mario->moveDirection = mario->directionView;
        if (++mario->dirEvtFrame > frames) {
            mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_EVENT;
            return TRUE;
        }
        return FALSE;
    } else {
        mario->displayDirection = revise360(270.0f - mario->dirEvtTargetDir);
        mario->displayDirectionTarget = mario->displayDirection;
        mario->directionView = toMovedirSimple(mario->displayDirection);
        mario->moveDirection = mario->directionView;
        mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_EVENT;
        return TRUE;
    }
}

f32 marioGetMoveRate(f32 dir) {
    f32 c = cos(3.1415927f * (dir - marioGetPtr()->targetYaw) / 180.0f);
    return 1.0f + (1.19f - 1.0f) * __fabsf(c);
}

static inline void marioSetGravity(f32 g) {
    marioGetPtr()->playerGravity = g;
}

void marioResetGravity(void) {
    marioSetGravity(1.0f);
}

struct NpcEntry* marioGetTouchNpcPtr(void) {
    return marioGetPtr()->touchNpc;
}

BOOL marioChkPlanePlace(HitEntry* hit) {
    return (hitGetAttr(hit) & 0x38) != 0;
}

void marioSetPeakYpos(void) {
    MarioWork* mario = marioGetPtr();
    mario->jumpPeakY = mario->position.y;
}

void marioAdjustMoveDir(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->displayDirection >= 90.0f && mario->displayDirection <= 270.0f) {
#if VERSION >= VERSION_US
        mario->moveDirection = toMovedir(180.0f);
#else
        mario->moveDirection = toMovedir(90.0f);
#endif
        mario->directionView = mario->moveDirection;
        mario->displayDirection = 180.0f;
        mario->displayDirectionTarget = 180.0f;
    } else {
#if VERSION >= VERSION_US
        mario->moveDirection = toMovedir(0.0f);
#else
        mario->moveDirection = toMovedir(90.0f);
#endif
        mario->directionView = mario->moveDirection;
        mario->displayDirection = 0.0f;
        mario->displayDirectionTarget = 0.0f;
    }
}

f32 marioGetDispDir(void) {
    MarioWork* mario = marioGetPtr();
    return revise360(mario->displayDirection - 90.0f + mario->targetYaw);
}

f32 revise360(f32 angle) {
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    while (angle >= 360.0f) {
        angle -= 360.0f;
    }
    return angle;
}

f32 toMovedir(f32 angle) {
    MarioWork* mario = marioGetPtr();

    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        if (mario->displayDirection == 280.0f || mario->displayDirection == 460.0f) {
            angle = 0.0f;
        } else if (mario->displayDirection == 260.0f || mario->displayDirection == 440.0f) {
            angle = 180.0f;
        } else if (revise360(mario->displayDirection) >= 180.0f) {
            angle = 0.0f;
        } else {
            angle = 180.0f;
        }
    }
#if VERSION >= VERSION_US
    angle = (s32)(1000.0f * (270.0f - angle + mario->targetYaw) + ((270.0f - angle + mario->targetYaw) >= 0.0f ? 0.5f : -0.5f)) / 1000.0f;
#else
    angle = (s32)(100.0f * (0.05f + (270.0f - angle + mario->targetYaw))) / 100.0f;
#endif
    REVISE360(angle);
    return angle;
}

f32 partyToMovedir(PartyEntry* party, f32 angle) {
    void* cam = party->playerPtr;

    if (party->flags & PARTY_FLAG_PAPER_MODE) {
        if (party->displayDirection == 280.0f || party->displayDirection == 460.0f) {
            angle = 0.0f;
        } else if (party->displayDirection == 260.0f || party->displayDirection == 440.0f) {
            angle = 180.0f;
        } else if (revise360(party->displayDirection) >= 180.0f) {
            angle = 0.0f;
        } else {
            angle = 180.0f;
        }
    }
#if VERSION >= VERSION_US
    angle = (s32)(1000.0f * (270.0f - angle + ((MarioWork*)cam)->targetYaw) + ((270.0f - angle + ((MarioWork*)cam)->targetYaw) >= 0.0f ? 0.5f : -0.5f)) / 1000.0f;
#else
    angle = (s32)(100.0f * (0.05f + (270.0f - angle + ((MarioWork*)cam)->targetYaw))) / 100.0f;
#endif
    REVISE360(angle);
    return angle;
}

f32 toMovedirSimple(f32 angle) {
    MarioWork* mario = marioGetPtr();
#if VERSION >= VERSION_US
    angle = (s32)(1000.0f * (270.0f - angle + mario->targetYaw) + ((270.0f - angle + mario->targetYaw) >= 0.0f ? 0.5f : -0.5f)) / 1000.0f;
#else
    angle = (s32)(100.0f * (0.05f + (270.0f - angle + mario->targetYaw))) / 100.0f;
#endif
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    while (angle >= 360.0f) {
        angle -= 360.0f;
    }
    return angle;
}

f32 toMovedir2(f32 angle, f32 ofs) {
    MarioWork* mario = marioGetPtr();

    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
        if (mario->displayDirection == 280.0f || mario->displayDirection == 460.0f) {
            angle = 0.0f;
        } else if (mario->displayDirection == 260.0f || mario->displayDirection == 440.0f) {
            angle = 180.0f;
        } else if (revise360(mario->displayDirection) >= 180.0f) {
            angle = 0.0f;
        } else {
            angle = 180.0f;
        }
    }
#if VERSION >= VERSION_US
    angle = (s32)(1000.0f * (270.0f - angle + mario->targetYaw) + ((270.0f - angle + mario->targetYaw) >= 0.0f ? 0.5f : -0.5f)) / 1000.0f;
#else
    angle = (s32)(100.0f * (0.05f + (270.0f - angle + mario->targetYaw))) / 100.0f;
#endif
    REVISE360(angle);
    angle += revise360(angle - mario->targetYaw) >= 180.0f ? -ofs : ofs;
    return revise360(angle);
}

void marioForceMoveMain(void) {
    MarioWork* mario = marioGetPtr();

    if (mario->flags & MARIO_FLAG_FORCED_MOVEMENT) {
        if (--mario->forceMoveTimer <= 0) {
            mario->forceMoveTimer = 0;
            mario->flags &= ~MARIO_FLAG_FORCED_MOVEMENT;
            mario->baseSpeed = 0.0f;
            if (mario->controlStickSensitivity > 1.0f) {
                mario->baseSpeed = marioGetDashSpd();
            } else if (mario->controlStickSensitivity > 0.0f) {
                mario->baseSpeed = marioGetWalkSpd();
            }
        }
    }
}

void marioSetForceMove(f32 dir, s32 time, f32 speed) {
    MarioWork* mario = marioGetPtr();

    mario->flags |= MARIO_FLAG_FORCED_MOVEMENT;
    mario->moveDirection = dir;
    mario->directionView = dir;
    mario->forceMoveTimer = time;
    mario->baseSpeed = speed;
    if (mario->currMotionId == MARIO_MOTION_SHIP || (mario->currMotionId == MARIO_MOTION_SLIT || mario->currMotionId == MARIO_MOTION_ROLL) || mario->currMotionId == MARIO_MOTION_YOSHI) {
        return;
    } else {
#if VERSION >= VERSION_US
        marioChgMot(speed >= mario->baseDashSpeed ? MARIO_MOTION_DASH : MARIO_MOTION_WALK);
#else
        marioChgMot(speed > mario->baseWalkSpeed ? MARIO_MOTION_DASH : MARIO_MOTION_WALK);
#endif
#if VERSION != VERSION_DEMO
        mario->moveDirection = dir;
        mario->directionView = dir;
        mario->forceMoveTimer = time;
        mario->baseSpeed = speed;
#endif
    }
}

void marioUpdateKeyData(void) {
    MarioWork* mario = marioGetPtr();
    u32 mask = 0xFFFFFFFF;
    u16 btn;

    mario->wStickDir1 = gp->stickX[0];
    mario->wStickDir2 = -gp->stickY[0];
    mario->substickX = gp->substickX[0];
    mario->substickY = -gp->substickY[0];
    mario->triggerL = gp->triggerLeft[0];
    mario->triggerR = gp->triggerRight[0];
    mario->analogA = 0;
    mario->analogB = 0;
    mask = mario->enableKeyMask ? mario->enableKeyMask : 0xFFFFFFFF;
    mario->buttonHold = gp->button[0] & mask;
    mario->buttonTrg = gp->buttonNew[0] & mask;
    mario->buttonRepeat = gp->buttonRepeat[0] & mask;
    mario->buttonUp = gp->buttonUp[0] & mask;
    // The demo has no CTRL_OFF_2 lock (and keeps its input lock bits elsewhere, see MarioTrigFlags).
#if VERSION == VERSION_DEMO
    if (!(mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_KEY_OFF))) {
#else
    if (!(mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_CTRL_OFF_2 | MARIO_FLAG_KEY_OFF))) {
#endif
        if (mario->trigFlags & MARIO_TRIG_FLAG_DISABLE_STICK) {
            mario->wStickDir1 = 0;
            mario->wStickDir2 = 0;
        }
        if (mario->trigFlags & MARIO_TRIG_FLAG_DISABLE_SUB_STICK) {
            mario->substickX = 0;
            mario->substickY = 0;
        }
        if (mario->trigFlags & MARIO_TRIG_FLAG_DISABLE_TRIGGERS) {
            mario->triggerL = 0;
            mario->triggerR = 0;
        }
        if (mario->trigFlags & MARIO_TRIG_FLAG_DISABLE_UNUSED_INPUT) {
            mario->analogA = 0;
            mario->analogB = 0;
        }
    }
#if VERSION == VERSION_DEMO
    if ((mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_KEY_OFF)) || !marioChkKey()) {
#else
    if ((mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_CTRL_OFF_2 | MARIO_FLAG_KEY_OFF)) || !marioChkKey()) {
#endif
        mario->wStickDir1 = 0;
        mario->wStickDir2 = 0;
        mario->substickX = 0;
        mario->substickY = 0;
        mario->triggerL = 0;
        mario->triggerR = 0;
        mario->analogA = 0;
        mario->analogB = 0;
        if (!mario->enableKeyMask) {
            mario->buttonHold = 0;
            mario->buttonTrg = 0;
            mario->buttonRepeat = 0;
            mario->buttonUp = 0;
        }
        if (!marioGetMotSlitCancel3() && (mario->dispFlags & MARIO_DISP_FLAG_SLIT)) {
            mario->buttonHold = 0x20;
        }
    }
    btn = DemoPad[0].dirs;
    mario->demoButtonNew = btn & (btn ^ mario->demoButtonPrev);
    mario->demoButtonPrev = btn;
}

void marioGetStick(f32* dir, f32* mag) {
    MarioWork* mario = marioGetPtr();
    s32 x;
    s32 y;
    f32 m;
    f32 a;

    if (mario->flags & MARIO_FLAG_FORCED_MOVEMENT) {
        *dir = mario->directionView;
        *mag = mario->baseSpeed;
        return;
    }
    x = mario->wStickDir1;
    y = ((mario->flags & MARIO_FLAG_BG_MODE) || kpaGetStageViewType() == 0) ? 0 : -mario->wStickDir2;
    if (yoshiGetStatus() == 2) {
        y = 0;
    }
    y = -y;
    m = distABf(0.0f, 0.0f, x, y);
    if (m >= 70.0f) {
        m = 70.0f;
    }
    a = angleABf(0.0f, 0.0f, x, y);
    if (!m) {
        a = mario->moveDirection;
    }
    *dir = revise360(a + mario->targetYaw);
    *mag = m;
}

#if VERSION != VERSION_DEMO
s32 N_marioGetMovementSpeed(void) {
    MarioWork* mario = marioGetPtr();
    s8 x = mario->wStickDir1;

    if (x == 0 && mario->wStickDir2 == 0) {
        return 0;
    }
    if (x * x + mario->wStickDir2 * mario->wStickDir2 > 3025) {
        return 2;
    }
    return 1;
}
#endif

void marioGetRubInit(void) {
    memset(&rubwork, 0, sizeof(rubwork));
    rubwork.revDir = -1;
}

s32 chkRevolveDir(s32* cw, s32* ccw) {
    s32 base;
    s32 i;
    RubWork* rw = &rubwork;
    s32 off = 0;
    s32 cwCount = 0;
    s32 cur;
    s32 j;
    s32 ccwCount = 0;
    s32 prev;
    s32 d;

    base = rw->idx;
    for (i = 0; i < 10; i++) {
        j = base + off;
        while (j < 0) {
            j += 20;
        }
        cur = rw->hist[j];
        d = base + (off - 1);
        while (d < 0) {
            d += 20;
        }
        prev = rw->hist[d];
        off--;
        if (i == 0 && cur == prev) {
            continue;
        }
        d = cur - prev;
        if (__fabsf(d) > 180.0f) {
            cur += d > 0 ? 360 : -360;
        }
        d = cur - prev;
        if (d > -90 && d < 0) {
            cwCount++;
        }
        if (d > 0 && d < 90) {
            ccwCount++;
        }
    }
    if (cwCount == 0 && ccwCount >= 4) {
        rw->revDir = 0;
        *cw = cwCount;
        *ccw = ccwCount;
        return 0;
    }
    if (ccwCount == 0 && cwCount >= 4) {
        rw->revDir = 1;
        *cw = cwCount;
        *ccw = ccwCount;
        return 1;
    }
    *cw = cwCount;
    *ccw = ccwCount;
    rw->revDir = -1;
    return -1;
}

s32 checkOneRevolution(s32 dir) {
    RubWork* rw;
    s32 idx;
    s32 j;
    s32 cur;
    s32 v;
    s32 start;
    s32 i;
    s32 ret = 0;

    rw = &rubwork;
    if (rw->num < 2) {
        return -1;
    }
    start = rw->start;
    cur = rw->hist[rw->idx];
    for (i = 1; i <= 20; i++) {
        j = rubwork.idx - i;
        while (j < 0) {
            j += 20;
        }
        v = rw->hist[j];
        if (cur != v) {
            break;
        }
    }
    if (cur == v) {
        return -1;
    }
    if (v == -1) {
        return -1;
    }
    if (dir) {
        if (cur > v) {
            if (start < v || cur <= start) {
                ret = 1;
            }
        } else {
            if (cur <= start && start < v) {
                ret = 1;
            }
        }
    } else {
        if (cur < v) {
            if (start > v || start <= cur) {
                ret = 1;
            }
        } else {
            if (cur >= start && start > v) {
                ret = 1;
            }
        }
    }
    return ret;
}

static inline void rubClearHist(s32 v) {
    u32 i;
    s16* p = rubwork.hist;
    for (i = 0; i < 21; i++) {
        p[i] = v;
    }
}

s32 marioGetRub(u32 btn, s32* dirOut, s32* countOut, f32* magOut) {
    s32 ret = 0;
    MarioWork* mario = marioGetPtr();
    RubWork* rw = &rubwork;
    f32 dir;
    f32 mag;
    s32 a;
    s32 r;
    s32 j;
    s32 cw;
    s32 ccw;

    if (btn && !(mario->buttonHold & btn)) {
        marioGetRubInit();
        *dirOut = -1;
        *countOut = 0;
        *magOut = 0.0f;
        return -1;
    }
    marioGetStick(&dir, &mag);
    a = dir;
    if (mag < 50.0f) {
        if (++rw->idleTimer > 10) {
            rubClearHist(a);
            rw->num = 0;
        }
        return -1;
    }
    rw->idleTimer = 0;
    rw->hist[rw->idx] = a;
    j = rubwork.idx;
    j++;
    while (j < 0) {
        j += 20;
    }
    rw->hist[j] = -1;
    r = chkRevolveDir(&cw, &ccw);
    if (r == 0) {
        if (rw->dir == 2) {
            rw->num = 0;
            rw->count = 0;
        }
        if (rw->num == 0) {
            rw->start = a;
            rubClearHist(a);
        }
        rw->stallFrames = 0;
        rw->num++;
        if (checkOneRevolution(0) == 1) {
            ret = 1;
            rubClearHist(rw->start);
            rw->count++;
        }
        rw->dir = 1;
    }
    if (r == 0) {
        *dirOut = rw->dir - 1;
        *countOut = rw->count;
        rw->idx++;
        if (rw->idx >= 20) {
            rw->idx -= 20;
        }
        return ret;
    }
    if (r == 1) {
        if (rw->dir == 1) {
            rw->num = 0;
            rw->count = 0;
        }
        if (rw->num == 0) {
            rw->start = a;
            rubClearHist(a);
        }
        rw->stallFrames = 0;
        rw->num++;
        if (checkOneRevolution(1) == 1) {
            ret = 1;
            rubClearHist(rw->start);
            rw->count++;
        }
        rw->dir = 2;
    }
    if (r == 1) {
        *dirOut = rw->dir - 1;
        *countOut = rw->count;
        rw->idx++;
        if (rw->idx >= 20) {
            rw->idx -= 20;
        }
        return ret;
    }
    rw->idx++;
    if (rw->idx >= 20) {
        rw->idx -= 20;
    }
    return -1;
}
