// Flurrie (cloud): partner init, follow, hover and the gust (breath) ability.
#define _MATH_H_
#define fabs(x) __fabs(x)
#define fabsf(x) __fabsf(x)
#include "party/party_cloud.h"
#include "dolphin/types.h"
#include "musyx/musyx.h"
#include "party.h"
#include "mario/mario.h"
#include "mario/mario_sbr.h"
#include "mario/mario_party.h"
#include "mario/mario_cam.h"
#include "system.h"
#include <dolphin/pad.h>

Vec cloud_at;

#include "driver/hitdrv.h"
#include "driver/effdrv.h"
#include "memory.h"
#include "pmario_sound.h"
#include "mario/mario_motion.h"
void N__cloud_use(PartyEntry* party);
static void getHitBreatheout2(PartyEntry* party, f32 tilt);

#define CW(p) ((PartyCloud*)(p)->useStruct)
#define KUMO(p) ((EffKumokumoN64Particle*)(p)->work.cloud.breathEffect->userdata)

/**
 * Swings one of the two side rays of Flurrie's gust back and forth:
 * the ray's angle steps 1 degree per frame between -20 and +20 and turns around at either end.
 * The sign argument is unused here; the caller applies it.
 */
static inline void cloudSweep(PartyEntry* party, f32 sign, s32 i) {
    PartyCloud* cl = CW(party);
    if (cl->sweep[i].reverse == 0) {
        cl->sweep[i].angle += 1.0f;
        cl = CW(party);
        if (cl->sweep[i].angle >= 20.0f) {
            cl->sweep[i].angle = 20.0f;
            CW(party)->sweep[i].reverse = 1;
        }
    } else {
        cl->sweep[i].angle -= 1.0f;
        cl = CW(party);
        if (cl->sweep[i].angle <= -20.0f) {
            cl->sweep[i].angle = -20.0f;
            CW(party)->sweep[i].reverse = 0;
        }
    }
}
#include "eff/n64/eff_kumokumo_n64.h"
#include "libc_decls.h"
#include "party/party_move.h"
#include "libc_decls.h"
#include <math.h>
#include "version.h"

#define cloudCalcPos(party)                                                           \
    {                                                                                 \
        MarioWork* m_ = (party)->playerPtr;                                           \
        f32 dir_;                                                                     \
        (party)->moveTarget = m_->position;                                           \
        dir_ = m_->displayDirectionTarget;                                            \
        dir_ = toMovedir(dir_ + ((dir_ < 90.0f || dir_ >= 270.0f) ? -90.0f : 90.0f)); \
        movePos(&(party)->moveTarget.x, &(party)->moveTarget.z, 3.3f, dir_);          \
        (party)->moveTarget.y += 10.0f;                                               \
    }

#if VERSION <= VERSION_DEMO_US
// The demo defines its functions in a different order (the compiler emits them in reverse), has no hover helpers or
// mot_cloud, and cloud_use is the whole breath state machine.

static void getHitBreatheout2(PartyEntry* party, f32 tilt);

// Returns the collision object one of the gust's rays is touching this frame (0 straight ahead, 1 aimed 45 degrees
// down, 2 and 3 the swinging side rays), or NULL when Flurrie is not mid-gust. Read by evt_cloud.c for map objects.
struct HitEntry* cloudGetHitBreathout(s32 rayId) {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    struct HitEntry* hitBreathout;

    if (party == NULL) {
        return 0;
    }

    if (
        party->currentMemberId != PARTY_MEMBER_FLURRIE || (party->flags & PARTY_FLAG_IS_BEING_USED) == 0 || party->useMotionId < MARIO_MOTION_FALL) {
        return 0;
    }

    hitBreathout = NULL;
    if (rayId == 0) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitFront;
    } else if (rayId == 1) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitDown;
    } else if (rayId == 2) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitSweep[0];
    } else if (rayId == 3) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitSweep[1];
    }

    return hitBreathout;
}

/**
 * Current reach of Flurrie's gust in units (grows 2 per frame up to 120), or 0 when she is not mid-gust.
 * No callers in this tree.
 */
f32 cloudGetBreathDist() {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathDist;

    if (party == NULL) {
        breathDist = 0.0f;
        return breathDist;
    }

    if ((party->currentMemberId != PARTY_MEMBER_FLURRIE || (party->flags & PARTY_FLAG_IS_BEING_USED) == 0) || party->useMotionId < MARIO_MOTION_FALL) {
        breathDist = 0.0f;
    } else {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDist = cloud->breathDist;
    }

    return breathDist;
}

/** Resets Flurrie's idle bob: phase 0 degrees, advancing 4.25 degrees per frame. */
static inline void cloud_hover_init(PartyEntry* party) {
    party->work.cloud.hoverAngle = 0.0f;
    party->work.cloud.hoverSpeed = 4.25f;
}

/** Advances Flurrie's idle bob and sets her display offset to a 0-6 unit sine wave above her position. */
static inline void cloud_hover_main(PartyEntry* party) {
    f32 a;
    party->work.cloud.hoverAngle = revise360(party->work.cloud.hoverAngle - party->work.cloud.hoverSpeed);
    a = sin((3.1415927f * party->work.cloud.hoverAngle) / 180.0f);
    party->dispOfs.y = 3.0f + 3.0f * a;
}

/**
 * Flurrie's follow handler (party_data.c move slot): flies after Mario with partyFlyMain and bobs in the air.
 * The first frame after a run-mode change sets up the fly movement and the bob.
 */
void cloud_move(PartyEntry* party) {
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        partyMoveFlyInit(party, 1);
        cloud_hover_init(party);
    }
    partyFlyMain(party);
    cloud_hover_main(party);
    if (party->moveMode != 2) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
}

/**
 * Flurrie's init handler (party_data.c): marks her a flying partner,
 * sets her collision size (38 tall, 36 wide in the demo, 24 in later versions) and clears her gust state.
 */
void cloud_init(PartyEntry* party) {
    party->memberKind = 5;
    party->moveKind = 1;
    party->height = 38.0f;
    party->width = 36.0f;
    party->work.cloud.reserved_174 = 0;
    party->work.cloud.breathEffect = NULL;
    party->work.cloud.hoverAngleBits = 0;
    party->work.cloud.hoverSpeedBits = 0;
    party->useStruct = NULL;
    party->work.cloud.breathEffect = NULL;
}

/**
 * Gale Force (X): Flurrie moves beside Mario over 4 frames,
 * then blows a gust while X is held (or for actionTime ms when a script started it),
 * casting rays that map objects and NPCs read; ends by freeing the work and following.
 */
void cloud_use(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 ofsX, ofsZ;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 yc, ys, dirCos, dirSin;
    HitEntry* hit;
    s32 flag;
    f32 dir;
    PartyCloud* cl;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        party->work.cloud.hoverAngleBits = 0;
        party->work.cloud.hoverSpeedBits = 0;
        marioAdjustMoveDir();
        party->useMotionId = 0;
        party->useStruct = __memAlloc(HEAP_DEFAULT, sizeof(PartyCloud));
        memset(party->useStruct, 0, sizeof(PartyCloud));
        CW(party)->sfxId = -1;
        CW(party)->reserved_0 = 100.0f;
        CW(party)->breathDistMax = 120.0f;
        CW(party)->sweep[0].angle = 0.0f;
        CW(party)->sweep[0].reverse = 0;
        CW(party)->sweep[1].angle = 0.0f;
        CW(party)->sweep[1].reverse = 1;
        party->work.cloud.breathEffect = NULL;
        if (party->flags & PARTY_FLAG_IS_EVT_USE) {
            CW(party)->autoTimer = sysMsec2Frame(party->actionTime);
        }
    }

    switch (party->useMotionId) {
        case 0:
            mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
            party->moveFrames = 4;
            party->useMotionId = 1;
        case 1:
            cloudCalcPos(party);
            party->displayDirection = mario->displayDirection;
            party->displayDirectionTarget = mario->displayDirectionTarget;
            party->position.x += (party->moveTarget.x - party->position.x) / (f32)party->moveFrames;
            party->position.y += (party->moveTarget.y - party->position.y) / (f32)party->moveFrames;
            party->position.z += (party->moveTarget.z - party->position.z) / (f32)party->moveFrames;
            if (--party->moveFrames > 0) {
                break;
            }
            party->useMotionId = 10;
        case 10:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            if (party->work.cloud.breathEffect == NULL) {
                party->work.cloud.breathEffect = effKumokumoN64Entry(0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -2.0f, 0.0f);
                KUMO(party)->camera = party->camId;
                KUMO(party)->r1 = 0x4C;
                KUMO(party)->g1 = 0xA7;
                KUMO(party)->b1 = 0xCA;
                KUMO(party)->r2 = 0x7D;
                KUMO(party)->g2 = 0x1B;
                KUMO(party)->b2 = 0xF5;
            }
            marioChgMot(MARIO_MOTION_CLOUD);
            marioChgPose("M_A_2A");
            partyChgPose(party, "PWD_A_5");
            party->moveFrames = 16;
            party->useMotionId = 11;
            mario->dispFlags |= MARIO_DISP_FLAG_FRONT_POSE;
            mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
            party->flags2 |= PARTY_DISP_FLAG_DIR_LOCK;
            CW(party)->breathDist = 0.0f;
            CW(party)->breathDir = mario->displayDirection;
            if (!(party->flags & PARTY_FLAG_IS_EVT_USE)) {
                mario->camShiftRate.x = 0.03f;
                mario->camShiftTargetX = 70.0f * (revise360(270.0f - mario->displayDirectionTarget) <= 180.0f ? -1.0f : 1.0f);
            }
            CW(party)->sfxId = psndSFXOn_3D((const char*)0x930, &mario->position);
        case 11:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            if (--party->moveFrames > 0) {
                break;
            }
            partyChgPose(party, "PWD_A_6");
            marioChgPose("M_A_2B");
            party->useMotionId = 12;
        case 12:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            partyUpdateKeyData(party);
            mario->displayDirection = CW(party)->breathDir;
            mario->displayDirectionTarget = CW(party)->breathDir;
            party->displayDirection = CW(party)->breathDir;
            party->displayDirectionTarget = CW(party)->breathDir;
            ofsX = mario->position.x;
            ofsZ = mario->position.z;
            flag = 0;
            dir = mario->displayDirection;
            if (dir < 90.0f || dir >= 270.0f) {
                flag = 1;
            }
            movePos(&ofsX, &ofsZ, 3.3f, toMovedir(dir + (flag ? -90.0f : 90.0f)));
            party->position.x = ofsX;
            party->position.z = ofsZ;
            party->position.y = 10.0f + mario->position.y;
            {
                Vec zero = {0.0f, 0.0f, 0.0f};
                party->dispOfs = zero;
            }
            CW(party)->breathDist += 2.0f;
            cl = CW(party);
            mario = party->playerPtr;
            if (cl->breathDist >= cl->breathDistMax) {
                cl->breathDist = cl->breathDistMax;
            }
            sincosf(&dirSin, &dirCos, toMovedir(CW(party)->breathDir));
            sincosf(&ys, &yc, -45.0f);
            dist = CW(party)->breathDist;
            hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                                 party->position.x, 18.0f + mario->position.y, party->position.z,
                                 dirSin, ys, dirCos);
            if (hit != NULL && (hitGetAttr(hit) & 4)) {
                hit = NULL;
            }
            CW(party)->hitDown = hit;
            getHitBreatheout2(party, 0.0f);
            if (++CW(party)->breathLevel > 2) {
                CW(party)->breathLevel = 0;
            }
            if (!(party->flags & PARTY_FLAG_IS_EVT_USE)) {
                if (party->buttonHold & PAD_BUTTON_X) {
                    if (marioKeyOffChk() == 0) {
                        break;
                    }
                }
            } else if (--CW(party)->autoTimer > 0) {
                break;
            }
            if ((u32)CW(party)->sfxId != 0xFFFFFFFF) {
                psndSFXOff(CW(party)->sfxId);
                CW(party)->sfxId = -1;
            }
            CW(party)->hitFront = NULL;
            CW(party)->hitDown = NULL;
            CW(party)->hitSweep[0] = NULL;
            CW(party)->hitSweep[1] = NULL;
            party->moveFrames = sysMsec2Frame(200);
            party->useMotionId = 13;
            if (party->flags & PARTY_FLAG_IS_EVT_USE) {
                party->useMotionId = 20;
            }
            break;
        case 13:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            partyUpdateKeyData(party);
            if (party->buttonTrg & PAD_BUTTON_X) {
                party->useMotionId = 10;
            }
            if (--party->moveFrames <= 0) {
                party->useMotionId = 20;
                break;
            }
            if (party->stickX == 0 && party->stickY == 0) {
                break;
            }
            party->useMotionId = 20;
        case 20:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            party->flags &= ~PARTY_FLAG_IS_BEING_USED;
            party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
            mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
            mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
            marioAdjustMoveDir();
            party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
            partyChgRunMode(party, 2);
            party->moveArg = 0;
            partyChgMoveMode(party, 2);
            partyChgMot(party, 1);
            party->flags2 |= PARTY_DISP_FLAG_DIR_LOCK;
            mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
            marioChgMot(MARIO_MOTION_STAY);
            if (!(party->flags & PARTY_FLAG_IS_EVT_USE)) {
                mario->camShiftRate.x = 0.01f;
                mario->camShiftTargetX = 0.0f;
            }
            party->flags &= ~PARTY_FLAG_IS_EVT_USE;
            if (party->work.cloud.breathEffect != NULL) {
                effSoftDelete(party->work.cloud.breathEffect);
                party->work.cloud.breathEffect = NULL;
            }
            if (party->useStruct != NULL) {
                __memFree(HEAP_DEFAULT, party->useStruct);
                party->useStruct = NULL;
            }
            break;
    }
}

/**
 * Flurrie's exit handler (party_data.c), run when she leaves the field:
 * stops the gust sound and effect, frees the gust work
 * and puts Mario back in his standing motion with the camera shift cleared.
 */
void cloud_exit(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;

    if (party->work.cloud.breathEffect != NULL) {
        effSoftDelete(party->work.cloud.breathEffect);
        party->work.cloud.breathEffect = NULL;
    }
    if (party->useStruct != NULL) {
        if ((u32)CW(party)->sfxId != 0xFFFFFFFF) {
            psndSFXOff(CW(party)->sfxId);
            CW(party)->sfxId = -1;
        }
        __memFree(HEAP_DEFAULT, party->useStruct);
        party->useStruct = NULL;
    }
    mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
    mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
    marioAdjustMoveDir();
    marioChgMot(MARIO_MOTION_STAY);
    mario->camShiftRate.x = 0.01f;
    mario->camShiftTargetX = 0.0f;
}

/**
 * Gust strength (0-100) at a point: nonzero only while Flurrie is mid-gust,
 * the point is within 10 units of 18 below her,
 * within reach (allowing half the target's width)
 * and within 30 degrees of the gust's direction (cosine falloff).
 * npcdrv.c uses it to tell whether an NPC is caught by the gust.
 */
f32 cloudGetBreathPower(Vec pos, f32 width) {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathPower;
    f32 dist;
    f32 angle;
    f32 breathDist;
    f32 val;

    breathPower = 0.0f;
    if (party == NULL) {
        return breathPower;
    }

    val = 10.0f;
    if (
        party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) != 0 && party->useMotionId >= MARIO_MOTION_FALL && ((fabs(party->position.y - pos.y - 18.0f)) <= val)) {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDist = cloud->breathDist;
        if (-((0.5f * width) - distABf(party->position.x, party->position.z, pos.x, pos.z)) <= breathDist) {
            PartyCloud* cloud = (PartyCloud*)party->useStruct;
            dist = toMovedir(cloud->breathDir);
            angle = angleABf(party->position.x, party->position.z, pos.x, pos.z);
            dist = revise360(angle - dist);

            if (dist <= 30.0f || dist >= 330.0f) {
                breathPower = cos((3.1415927f * dist) / 180.0f);
                val = 100.0f;
                breathPower = val * fabsf(breathPower);
            }
        }
    }

    return breathPower;
}

/**
 * Direction of Flurrie's gust in movement degrees:
 * -1 while she is still moving into position, 0 when there is no gust work. No callers in this tree.
 */
f32 cloudGetBreathDir() {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathDir;

    if (party == NULL) {
        return 0.0f;
    }

    if ((party->flags & PARTY_FLAG_IS_BEING_USED) != 0 && (party->useMotionId < MARIO_MOTION_FALL)) {
        breathDir = -1.0f;
    } else if (party->useStruct == NULL) {
        breathDir = 0.0f;
    } else {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDir = toMovedir(cloud->breathDir);
    }

    return breathDir;
}

/**
 * Per-frame gust update: casts the straight ray at one of three heights (8, 20, 40 above Mario, cycling each
 * frame), places and scales the cloud effect in front of Flurrie, then casts the two swinging side rays.
 * Rays that hit collision with attribute 4 are ignored.
 */
static void getHitBreatheout2(PartyEntry* party, f32 tilt) {
    f32 dirSin, dirCos, ys, yc;
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 ofsX, ofsZ;
    f32 dir, sign, height;
    s16 kind;
    HitEntry* hit;
    PartyCloud* cl = CW(party);
    MarioWork* mario = party->playerPtr;

    kind = cl->breathLevel;

    if (kind == 0) {
        height = 8.0f;
    } else if (kind == 1) {
        height = 20.0f;
    } else {
        if (kind == 2) {
            height = 40.0f;
        }
        do {
        } while (0);
    }
    if (cl->breathDist >= cl->breathDistMax) {
        cl->breathDist = cl->breathDistMax;
    }
    sincosf(&ys, &yc, tilt);
    dir = toMovedir(CW(party)->breathDir);
    sincosf(&dirSin, &dirCos, dir);
    dist = CW(party)->breathDist;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         party->position.x, mario->position.y + height, party->position.z,
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CW(party)->hitFront = hit;
    ofsX = 0.0f;
    ofsZ = 0.0f;
    movePos(&ofsX, &ofsZ, 24.0f, dir);
    KUMO(party)->x = party->position.x + ofsX;
    KUMO(party)->y = 18.0f + party->position.y;
    KUMO(party)->z = party->position.z + ofsZ;
    cl = CW(party);
    KUMO(party)->scale = 0.6f * (cl->breathDist / cl->breathDistMax);
    cl = CW(party);
    if (cl->breathDir >= 90.0f && cl->breathDir <= 270.0f) {
        KUMO(party)->rot = -25.0f;
    } else {
        KUMO(party)->rot = 205.0f;
    }
    cl = CW(party);
    if (cl->breathDir >= 90.0f && cl->breathDir <= 270.0f) {
        sign = 1.0f;
    } else {
        sign = -1.0f;
    }

    cloudSweep(party, sign, 0);
    cl = CW(party);
    sincosf(&dirSin, &dirCos, toMovedir(cl->sweep[0].angle * sign + cl->breathDir));
    dist = CW(party)->breathDist;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         party->position.x, mario->position.y + height, party->position.z,
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CW(party)->hitSweep[0] = hit;

    cloudSweep(party, sign, 1);
    cl = CW(party);
    sincosf(&dirSin, &dirCos, toMovedir(cl->sweep[1].angle * sign + cl->breathDir));
    dist = CW(party)->breathDist;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         party->position.x, mario->position.y + height, party->position.z,
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CW(party)->hitSweep[1] = hit;
}

/**
 * Gale Force state for evt_party.c's script wait:
 * 0 when there is no partner or Flurrie is not gusting, 1 while the gust is in its start state (10),
 * otherwise 2 (also when the partner is not Flurrie).
 */
u8 cloudGetStatus() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    u8 status = 2;

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        status = 0;
        return status;
    } else if (party->useMotionId == 10 && party->useMotionId < 20) {
        status = 1;
    }

    return status;
}

/**
 * Saves the 3D camera's look-at point into cloud_at and, if Mario's camera is zoomed in,
 * requests a zoom-out (marioCamZoomOffReq2(600)).
 * Called when Mario's Flurrie motion ends (mot_cloud_post in mario_motion.c).
 */
void cloudResetAt() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);

    if (party == NULL || party->currentMemberId != PARTY_MEMBER_FLURRIE) {
        return;
    } else {
        cloud_at.x = camGetPtr(CAMERA_3D)->cameraAt.x;
        cloud_at.y = camGetPtr(CAMERA_3D)->cameraAt.y;
        cloud_at.z = camGetPtr(CAMERA_3D)->cameraAt.z;

        marioCamZoomOffReq2(600);
    }
}

/**
 * Called by marioCamZoomUp: while the 3D camera's stateA is 0, remembers the given look-at point in cloud_at;
 * otherwise replaces it with the remembered point.
 * Does nothing with no partner or when Flurrie is out but not gusting.
 */
void cloudGetAt(Vec* position) {
    MarioWork* mario = marioGetPtr();
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        return;
    }

    if ((mario->dispFlags & (MARIO_DISP_FLAG_HIDDEN << 20)) == 0) {
        CameraEntry* camera = camGetPtr(CAMERA_3D);

        if (camera->stateA == 0) {
            cloud_at = *position;
        } else {
            *position = cloud_at;
        }
    }
}
#else
/**
 * Mario's motion while Flurrie gusts (MARIO_MOTION_CLOUD):
 * on its first frame clears his jump, step and fall flags and timers so he stands still.
 * The demo keeps this handler in mario_motion.c.
 */
void mot_cloud() {
    MarioWork* mario = marioGetPtr();

    if ((mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) != 0) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        mario->flags &= ~(MARIO_FLAG_HAS_INPUT_JUMP | MARIO_FLAG_IS_STEPPING | MARIO_FLAG_IS_FALLING | MARIO_FLAG_IS_JUMPING);
        mario->multiTimer = 0;
        mario->airTimer = 0;
        mario->currSubMotionId = 0;
    }
}

/**
 * Post handler of Mario's Flurrie motion (mario_motion.c table):
 * saves the 3D camera's look-at point in cloud_at, requests a camera zoom-out if zoomed in,
 * unlocks Mario's facing and front pose and clears the camera side shift.
 */
void cloudResetAt() {
    MarioWork* mario = marioGetPtr();
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);

    if (party != NULL && party->currentMemberId == PARTY_MEMBER_FLURRIE) {
        cloud_at.x = camGetPtr(CAMERA_3D)->cameraAt.x;
        cloud_at.y = camGetPtr(CAMERA_3D)->cameraAt.y;
        cloud_at.z = camGetPtr(CAMERA_3D)->cameraAt.z;

        marioCamZoomOffReq2(600);
    }

    mario->dispFlags &= ~(MARIO_DISP_FLAG_HIDDEN << 8); // kDisableMakeDispDir
    mario->dispFlags &= ~(MARIO_DISP_FLAG_HIDDEN << 2); // kForceFrontPose
    marioAdjustMoveDir();
    mario->camShiftRate.x = 0.01f;
    mario->camShiftTargetX = 0.0f;
}

/**
 * Gale Force state for evt_party.c's script wait:
 * 0 when there is no partner or Flurrie is not gusting, 1 while the gust is in its start state (10),
 * otherwise 2 (also when the partner is not Flurrie).
 */
u8 cloudGetStatus() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    u8 status = 2;

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        status = 0;
        return status;
    } else if (party->useMotionId == 10 && party->useMotionId < 20) {
        status = 1;
    }

    return status;
}

/**
 * Direction of Flurrie's gust in movement degrees:
 * -1 while she is still moving into position, 0 when there is no gust work. No callers in this tree.
 */
f32 cloudGetBreathDir() {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathDir;

    if (party == NULL) {
        return 0.0f;
    }

    if ((party->flags & PARTY_FLAG_IS_BEING_USED) != 0 && (party->useMotionId < MARIO_MOTION_FALL)) {
        breathDir = -1.0f;
    } else if (party->useStruct == NULL) {
        breathDir = 0.0f;
    } else {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDir = toMovedir(cloud->breathDir);
    }

    return breathDir;
}

/**
 * Gust strength (0-100) at a point: nonzero only while Flurrie is mid-gust,
 * the point is within 10 units of 18 below her,
 * within reach (allowing half the target's width)
 * and within 30 degrees of the gust's direction (cosine falloff).
 * npcdrv.c uses it to tell whether an NPC is caught by the gust.
 */
f32 cloudGetBreathPower(Vec pos, f32 width) {
    PartyEntry* party = partyGetPtr(PARTY_SLOT_PARTY);
    f32 breathPower;
    f32 dist;
    f32 angle;
    f32 breathDist;
    f32 val;

    breathPower = 0.0f;
    if (party == NULL) {
        return breathPower;
    }

    val = 10.0f;
    if (
        party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) != 0 && party->useMotionId >= MARIO_MOTION_FALL && ((fabs(party->position.y - pos.y - 18.0f)) <= val)) {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDist = cloud->breathDist;
        if (-((0.5f * width) - distABf(party->position.x, party->position.z, pos.x, pos.z)) <= breathDist) {
            PartyCloud* cloud = (PartyCloud*)party->useStruct;
            dist = toMovedir(cloud->breathDir);
            angle = angleABf(party->position.x, party->position.z, pos.x, pos.z);
            dist = revise360(angle - dist);

            if (dist <= 30.0f || dist >= 330.0f) {
                breathPower = cos((3.1415927f * dist) / 180.0f);
                val = 100.0f;
                breathPower = val * fabsf(breathPower);
            }
        }
    }

    return breathPower;
}

// Returns the collision object one of the gust's rays is touching this frame (0 straight ahead, 1 aimed 45 degrees
// down, 2 and 3 the swinging side rays), or NULL when Flurrie is not mid-gust. Read by evt_cloud.c for map objects.
struct HitEntry* cloudGetHitBreathout(s32 rayId) {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    struct HitEntry* hitBreathout;

    if (party == NULL) {
        return 0;
    }

    if (
        party->currentMemberId != PARTY_MEMBER_FLURRIE || (party->flags & PARTY_FLAG_IS_BEING_USED) == 0 || party->useMotionId < MARIO_MOTION_FALL) {
        return 0;
    }

    hitBreathout = NULL;
    if (rayId == 0) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitFront;
    } else if (rayId == 1) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitDown;
    } else if (rayId == 2) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitSweep[0];
    } else if (rayId == 3) {
        hitBreathout = ((PartyCloud*)party->useStruct)->hitSweep[1];
    }

    return hitBreathout;
}

/**
 * Current reach of Flurrie's gust in units (grows 2 per frame up to 120), or 0 when she is not mid-gust.
 * No callers in this tree.
 */
f32 cloudGetBreathDist() {
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);
    f32 breathDist;

    if (party == NULL) {
        breathDist = 0.0f;
        return breathDist;
    }

    if ((party->currentMemberId != PARTY_MEMBER_FLURRIE || (party->flags & PARTY_FLAG_IS_BEING_USED) == 0) || party->useMotionId < MARIO_MOTION_FALL) {
        breathDist = 0.0f;
    } else {
        PartyCloud* cloud = (PartyCloud*)party->useStruct;
        breathDist = cloud->breathDist;
    }

    return breathDist;
}

#if VERSION >= VERSION_US
/**
 * Lets Flurrie follow and bob again after a cutscene froze her,
 * and puts her back in her standing pose (PWD_S_1).
 * Called by the US-only N_evt_party_cloud_lock_animations_on_off script helper.
 */
void N_cloudLockAnimationsOff(PartyEntry* party) {
    party->work.cloud.lockAnims = 0;
    partyChgPose(party, "PWD_S_1");
}

/**
 * Freezes Flurrie for a cutscene: cloud_move stops following and bobbing, and she takes pose PWD_Z_1.
 * Called by the US-only N_evt_party_cloud_lock_animations_on_off script helper.
 */
void N_cloudLockAnimationsOn(PartyEntry* party) {
    party->work.cloud.lockAnims = 1;
    partyChgPose(party, "PWD_Z_1");
}
#endif

/**
 * Resets Flurrie's idle bob: phase 0 degrees, advancing 4.25 degrees per frame.
 * Inlined into cloud_move from the US release on.
 */
void cloud_hover_init(PartyEntry* party) {
    party->work.cloud.hoverAngle = 0.0f;
    party->work.cloud.hoverSpeed = 4.25f;
}

/** Advances Flurrie's idle bob and sets her display offset to a 0-6 unit sine wave above her position. */
void cloud_hover_main(PartyEntry* party) {
    f32 a;
    party->work.cloud.hoverAngle = revise360(party->work.cloud.hoverAngle - party->work.cloud.hoverSpeed);
    a = sin((3.1415927f * party->work.cloud.hoverAngle) / 180.0f);
    party->dispOfs.y = 3.0f + 3.0f * a;
}

/**
 * Flurrie's follow handler (party_data.c move slot): flies after Mario with partyFlyMain and bobs in the air.
 * The first frame after a run-mode change sets up the fly movement and the bob.
 * From the US release on, it does nothing while a cutscene has locked her (N_cloudLockAnimationsOn).
 */
#if VERSION >= VERSION_US
void cloud_move(PartyEntry* party) {
    f32 a;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        partyMoveFlyInit(party, 1);
        party->work.cloud.hoverAngle = 0.0f;
        party->work.cloud.hoverSpeed = 4.25f;
    }
    if (party->work.cloud.lockAnims == 0) {
        partyFlyMain(party);
        party->work.cloud.hoverAngle = revise360(party->work.cloud.hoverAngle - party->work.cloud.hoverSpeed);
        a = sin((3.1415927f * party->work.cloud.hoverAngle) / 180.0f);
        party->dispOfs.y = 3.0f + 3.0f * a;
        if (party->moveMode != 2) {
            party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
        }
    }
}
#else
/** Japanese release: follows and bobs every frame, with no cutscene lock. */
void cloud_move(PartyEntry* party) {
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        partyMoveFlyInit(party, 1);
        cloud_hover_init(party);
    }
    partyFlyMain(party);
    cloud_hover_main(party);
    if (party->moveMode != 2) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
}
#endif

/**
 * Flurrie's init handler (party_data.c): marks her a flying partner,
 * sets her collision size (38 tall, 24 wide) and clears her gust and cutscene-lock state.
 */
void cloud_init(PartyEntry* party) {
    party->memberKind = 5;
    party->moveKind = 1;
    party->height = 38.0f;
    party->width = 24.0f;
    party->work.cloud.reserved_174 = 0;
    party->work.cloud.breathEffect = NULL;
    party->work.cloud.hoverAngleBits = 0;
    party->work.cloud.hoverSpeedBits = 0;
#if VERSION >= VERSION_US
    party->work.cloud.lockAnims = 0;
#endif
    party->useStruct = NULL;
    party->work.cloud.breathEffect = NULL;
}

/**
 * Gale Force (X), party_data.c use slot: runs the gust state machine in N__cloud_use, then,
 * if Mario has left his Flurrie, standing or dash motion (taking damage, say),
 * cancels the gust and sends Flurrie back to following, or into her damage run mode when he was hurt.
 */
void cloud_use(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    u16 mot;
    s32 flag;
    f32 dir;
    u8* m;

    N__cloud_use(party);
    if (mario->currMotionId == MARIO_MOTION_CLOUD || mario->currMotionId <= 1 || mario->currMotionId == MARIO_MOTION_DASH) {
        return;
    }
    party->flags &= ~PARTY_FLAG_IS_BEING_USED;
    if (CW(party) != NULL && (u32)CW(party)->sfxId != 0xFFFFFFFF) {
        psndSFXOff(CW(party)->sfxId);
        CW(party)->sfxId = -1;
    }
    if (party->work.cloud.breathEffect != NULL) {
        effSoftDelete(party->work.cloud.breathEffect);
        party->work.cloud.breathEffect = NULL;
    }
    cloudCalcPos(party);
    party->position = party->moveTarget;
    party->flags2 |= PARTY_DISP_FLAG_DIR_LOCK;
    party->flags &= ~PARTY_FLAG_IS_EVT_USE;
    if (party->useStruct != NULL) {
        __memFree(HEAP_DEFAULT, party->useStruct);
        party->useStruct = NULL;
    }
    if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE) {
        partyChgRunMode(party, 13);
    } else {
        partyChgPose(party, partyChgPoseId(party, 1));
        partyChgRunMode(party, 2);
        partyChgMot(party, 0);
    }
}

/**
 * The gust itself: Flurrie moves beside Mario over 4 frames,
 * then blows while X is held (or for actionTime ms when a script started it),
 * casting the rays map objects and NPCs read; 200 ms after release she goes back to following.
 */
void N__cloud_use(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 ofsX, ofsZ;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 yc, ys, dirCos, dirSin;
    HitEntry* hit;
    s32 flag;
    f32 dir;
    PartyCloud* cl;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        party->work.cloud.hoverAngleBits = 0;
        party->work.cloud.hoverSpeedBits = 0;
        marioAdjustMoveDir();
        party->useMotionId = 0;
        party->useStruct = __memAlloc(HEAP_DEFAULT, sizeof(PartyCloud));
        memset(party->useStruct, 0, sizeof(PartyCloud));
        CW(party)->reserved_0 = 100.0f;
        CW(party)->breathDistMax = 120.0f;
        CW(party)->sweep[0].angle = 0.0f;
        CW(party)->sweep[0].reverse = 0;
        CW(party)->sweep[1].angle = 0.0f;
        CW(party)->sweep[1].reverse = 1;
        party->work.cloud.breathEffect = NULL;
        if (CW(party) != NULL) {
            CW(party)->sfxId = -1;
        }
        if (party->flags & PARTY_FLAG_IS_EVT_USE) {
            CW(party)->autoTimer = sysMsec2Frame(party->actionTime);
        }
    }

    switch (party->useMotionId) {
        case 0:
            mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
            party->moveFrames = 4;
            party->useMotionId = 1;
        case 1:
            cloudCalcPos(party);
            party->displayDirection = mario->displayDirection;
            party->displayDirectionTarget = mario->displayDirectionTarget;
            party->position.x += (party->moveTarget.x - party->position.x) / (f32)party->moveFrames;
            party->position.y += (party->moveTarget.y - party->position.y) / (f32)party->moveFrames;
            party->position.z += (party->moveTarget.z - party->position.z) / (f32)party->moveFrames;
            if (--party->moveFrames > 0) {
                break;
            }
            party->useMotionId = 10;
        case 10:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            if (party->work.cloud.breathEffect == NULL) {
                party->work.cloud.breathEffect = effKumokumoN64Entry(0, 0, 0.0f, 0.0f, 0.0f, 0.0f, -2.0f, 0.0f);
                KUMO(party)->camera = party->camId;
                KUMO(party)->r1 = 0x4C;
                KUMO(party)->g1 = 0xA7;
                KUMO(party)->b1 = 0xCA;
                KUMO(party)->r2 = 0x7D;
                KUMO(party)->g2 = 0x1B;
                KUMO(party)->b2 = 0xF5;
            }
            marioChgMot(MARIO_MOTION_CLOUD);
            marioChgPose("M_A_2A");
            partyChgPose(party, "PWD_A_5");
            party->moveFrames = 16;
            party->useMotionId = 11;
            mario->dispFlags |= MARIO_DISP_FLAG_FRONT_POSE;
            mario->dispFlags |= MARIO_DISP_FLAG_DIR_LOCK;
            party->flags2 |= PARTY_DISP_FLAG_DIR_LOCK;
            CW(party)->breathDist = 0.0f;
            CW(party)->breathDir = mario->displayDirection;
            if (!(party->flags & PARTY_FLAG_IS_EVT_USE)) {
                mario->camShiftRate.x = 0.03f;
                mario->camShiftTargetX = 70.0f * (revise360(270.0f - mario->displayDirectionTarget) <= 180.0f ? -1.0f : 1.0f);
            }
            if (CW(party) != NULL && (u32)CW(party)->sfxId == 0xFFFFFFFF) {
                CW(party)->sfxId = psndSFXOn_3D((const char*)0x930, &party->playerPtr->position);
            }
        case 11:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            if (--party->moveFrames > 0) {
                break;
            }
            partyChgPose(party, "PWD_A_6");
#if VERSION >= VERSION_US
            if (mario->currMotionId == MARIO_MOTION_CLOUD)
#endif
                marioChgPose("M_A_2B");
            party->useMotionId = 12;
        case 12:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            partyUpdateKeyData(party);
            mario->displayDirection = CW(party)->breathDir;
            mario->displayDirectionTarget = CW(party)->breathDir;
            party->displayDirection = CW(party)->breathDir;
            party->displayDirectionTarget = CW(party)->breathDir;
            ofsX = mario->position.x;
            ofsZ = mario->position.z;
            flag = 0;
            dir = mario->displayDirection;
            if (dir < 90.0f || dir >= 270.0f) {
                flag = 1;
            }
            movePos(&ofsX, &ofsZ, 3.3f, toMovedir(dir + (flag ? -90.0f : 90.0f)));
            party->position.x = ofsX;
            party->position.z = ofsZ;
            party->position.y = 10.0f + mario->position.y;
            {
                Vec zero = {0.0f, 0.0f, 0.0f};
                party->dispOfs = zero;
            }
            CW(party)->breathDist += 2.0f;
            cl = CW(party);
            mario = party->playerPtr;
            if (cl->breathDist >= cl->breathDistMax) {
                cl->breathDist = cl->breathDistMax;
            }
            sincosf(&dirSin, &dirCos, toMovedir(CW(party)->breathDir));
            sincosf(&ys, &yc, -45.0f);
            dist = CW(party)->breathDist;
            hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                                 party->position.x, 18.0f + mario->position.y, party->position.z,
                                 dirSin, ys, dirCos);
            if (hit != NULL && (hitGetAttr(hit) & 4)) {
                hit = NULL;
            }
            CW(party)->hitDown = hit;
            getHitBreatheout2(party, 0.0f);
            if (++CW(party)->breathLevel > 2) {
                CW(party)->breathLevel = 0;
            }
            if (!(party->flags & PARTY_FLAG_IS_EVT_USE)) {
                if (party->buttonHold & PAD_BUTTON_X) {
                    if (marioKeyOffChk() == 0) {
                        break;
                    }
                }
            } else if (--CW(party)->autoTimer > 0) {
                break;
            }
            CW(party)->hitFront = NULL;
            CW(party)->hitDown = NULL;
            CW(party)->hitSweep[0] = NULL;
            CW(party)->hitSweep[1] = NULL;
            party->moveFrames = sysMsec2Frame(200);
            party->useMotionId = 13;
            if (party->flags & PARTY_FLAG_IS_EVT_USE) {
                party->useMotionId = 20;
            }
            if (CW(party) != NULL && (u32)CW(party)->sfxId != 0xFFFFFFFF) {
                psndSFXOff(CW(party)->sfxId);
                CW(party)->sfxId = -1;
            }
            break;
        case 13:
            cloudCalcPos(party);
            party->position = party->moveTarget;
            partyUpdateKeyData(party);
            if (party->buttonTrg & PAD_BUTTON_X) {
                party->useMotionId = 10;
            }
            if (--party->moveFrames <= 0) {
                party->useMotionId = 20;
                break;
            }
            if (party->stickX == 0 && party->stickY == 0) {
                break;
            }
            party->useMotionId = 20;
        case 20:
            party->flags &= ~PARTY_FLAG_IS_BEING_USED;
            if (CW(party) != NULL && (u32)CW(party)->sfxId != 0xFFFFFFFF) {
                psndSFXOff(CW(party)->sfxId);
                CW(party)->sfxId = -1;
            }
            if (party->work.cloud.breathEffect != NULL) {
                effSoftDelete(party->work.cloud.breathEffect);
                party->work.cloud.breathEffect = NULL;
            }
            cloudCalcPos(party);
            party->position = party->moveTarget;
            party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
            if (mario->currMotionId == MARIO_MOTION_CLOUD) {
                mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
                mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
                marioAdjustMoveDir();
                party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
                mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
                marioChgMot(MARIO_MOTION_STAY);
            }
            party->flags2 |= PARTY_DISP_FLAG_DIR_LOCK;
            partyChgRunMode(party, 2);
            party->moveArg = 0;
            partyChgMoveMode(party, 2);
            partyChgMot(party, 1);
            if (!(party->flags & PARTY_FLAG_IS_EVT_USE)) {
                mario->camShiftRate.x = 0.01f;
                mario->camShiftTargetX = 0.0f;
            }
            party->flags &= ~PARTY_FLAG_IS_EVT_USE;
            if (party->useStruct != NULL) {
                __memFree(HEAP_DEFAULT, party->useStruct);
                party->useStruct = NULL;
            }
            break;
    }
}

/**
 * Flurrie's exit handler (party_data.c), run when she leaves the field:
 * stops the gust sound and effect, frees the gust work
 * and puts Mario back in his standing motion with the camera shift cleared.
 */
void cloud_exit(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;

    if (CW(party) != NULL && (u32)CW(party)->sfxId != 0xFFFFFFFF) {
        psndSFXOff(CW(party)->sfxId);
        CW(party)->sfxId = -1;
    }
    if (party->work.cloud.breathEffect != NULL) {
        effSoftDelete(party->work.cloud.breathEffect);
        party->work.cloud.breathEffect = NULL;
    }
    if (party->useStruct != NULL) {
        __memFree(HEAP_DEFAULT, party->useStruct);
        party->useStruct = NULL;
    }
    mario->dispFlags &= ~MARIO_DISP_FLAG_DIR_LOCK;
    mario->dispFlags &= ~MARIO_DISP_FLAG_FRONT_POSE;
    marioAdjustMoveDir();
    marioChgMot(MARIO_MOTION_STAY);
    mario->camShiftRate.x = 0.01f;
    mario->camShiftTargetX = 0.0f;
}

/**
 * Per-frame gust update: casts the straight ray at one of three heights (8, 20, 40 above Mario, cycling each
 * frame), places and scales the cloud effect in front of Flurrie, then casts the two swinging side rays.
 * Rays that hit collision with attribute 4 are ignored.
 */
static void getHitBreatheout2(PartyEntry* party, f32 tilt) {
    f32 dirSin, dirCos, ys, yc;
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 ofsZ, ofsX;
    f32 dir, sign, height;
    s16 kind;
    HitEntry* hit;
    PartyCloud* cl = CW(party);
    MarioWork* mario = party->playerPtr;

    kind = cl->breathLevel;

    if (kind == 0) {
        height = 8.0f;
    } else if (kind == 1) {
        height = 20.0f;
    } else {
        if (kind == 2) {
            height = 40.0f;
        }
        do {
        } while (0);
    }
    if (cl->breathDist >= cl->breathDistMax) {
        cl->breathDist = cl->breathDistMax;
    }
    sincosf(&ys, &yc, tilt);
    dir = toMovedir(CW(party)->breathDir);
    sincosf(&dirSin, &dirCos, dir);
    dist = CW(party)->breathDist;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         party->position.x, mario->position.y + height, party->position.z,
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CW(party)->hitFront = hit;
    ofsX = 0.0f;
    ofsZ = 0.0f;
    if (party->work.cloud.breathEffect != NULL) {
        movePos(&ofsX, &ofsZ, 24.0f, dir);
        KUMO(party)->x = party->position.x + ofsX;
        KUMO(party)->y = 18.0f + party->position.y;
        KUMO(party)->z = party->position.z + ofsZ;
        cl = CW(party);
        KUMO(party)->scale = 0.6f * (cl->breathDist / cl->breathDistMax);
        cl = CW(party);
        if (cl->breathDir >= 90.0f && cl->breathDir <= 270.0f) {
            KUMO(party)->rot = -25.0f;
        } else {
            KUMO(party)->rot = 205.0f;
        }
    }
    cl = CW(party);
    if (cl->breathDir >= 90.0f && cl->breathDir <= 270.0f) {
        sign = 1.0f;
    } else {
        sign = -1.0f;
    }

    cloudSweep(party, sign, 0);
    cl = CW(party);
    sincosf(&dirSin, &dirCos, toMovedir(cl->sweep[0].angle * sign + cl->breathDir));
    dist = CW(party)->breathDist;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         party->position.x, mario->position.y + height, party->position.z,
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CW(party)->hitSweep[0] = hit;

    cloudSweep(party, sign, 1);
    cl = CW(party);
    sincosf(&dirSin, &dirCos, toMovedir(cl->sweep[1].angle * sign + cl->breathDir));
    dist = CW(party)->breathDist;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz,
                         party->position.x, mario->position.y + height, party->position.z,
                         dirSin, ys, dirCos);
    if (hit != NULL && (hitGetAttr(hit) & 4)) {
        hit = NULL;
    }
    CW(party)->hitSweep[1] = hit;
}

/**
 * Called by marioCamZoomUp: while the 3D camera's stateA is 0, remembers the given look-at point in cloud_at;
 * otherwise replaces it with the remembered point.
 * Does nothing with no partner or when Flurrie is out but not gusting.
 */
void cloudGetAt(Vec* position) {
    MarioWork* mario = marioGetPtr();
    u32 partyId = marioGetPartyId();
    PartyEntry* party = partyGetPtr(partyId);

    if (party == NULL || (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED) == 0)) {
        return;
    }

    if ((mario->dispFlags & (MARIO_DISP_FLAG_HIDDEN << 20)) == 0) {
        CameraEntry* camera = camGetPtr(CAMERA_3D);

        if (camera->stateA == 0) {
            cloud_at = *position;
        } else {
            *position = cloud_at;
        }
    }
}

#endif

// FAKE: never called (the link drops it); compiled first (deferred mode works bottom-up), it puts 0.0f, 70.0f, 180.0f
// at the head of .sdata2 and the int-to-float double ahead of the strings in .rodata, as in every version.
void partyCloudStrippedPool(f32* f, s32 i) {
    f[0] = 0.0f;
    f[1] = 70.0f;
    f[2] = 180.0f;
    f[3] = (f32)i;
}
