// Partner motions: following Mario (behind/beside/homing), jumping, falling, staying, slit, roll, damage and
// flying partners' height.
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include "driver/hitdrv.h"
#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include "mario/mariost.h"
#include <string.h>
#include "version.h"
#include "libc_decls.h"

#include "party.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_sbr.h"
#include "party/party_bomhei.h"
#include "party/party_motion.h"
#include "party/party_nokonoko.h"
#include "system.h"
#include <math.h>
#include "party/party_hit.h"
#include "party/party_chuchu.h"
#include "mot/mot_stay.h"
#include "party/party_move.h"
#include "mot/mot_slit.h"
#include "mario/mario_hit.h"
// FAKE: party_motion.c calls partySearchHead through this prototype (the types it was compiled with) instead of the one in party/party_hit.h; same registers, behaviour-identical.
typedef void* (*PartySearchHeadRetVoidptrFn)(PartyEntry*, Vec*, f32*, f32);

static BOOL partyChkMarioFollowY(MarioWork* mario);
void partyChgMotSlitFloor(PartyEntry* party);

#if VERSION <= VERSION_DEMO_US
static s32 touch_wall_ct; // demo: frames the fly follow found no floor in front (reset when the way is clear)
#else
static f32 gnd_probe_dy; // height above a point at which the ground probes start (60)
static s32 upstairs_count;
static f32 upstairs_dy;
#endif

static BOOL party_slit(PartyEntry* party);
static BOOL party_roll(PartyEntry* party);
void partyFlyAdjustY(PartyEntry* party);
void partyWalkChkGnd(PartyEntry* party);

#if VERSION <= VERSION_DEMO_US
/* The demo's partner motion code: an older arrangement of the retail functions below (other order, fewer
   helpers), kept as its own copy. */
static inline u32 partyGetFrontAttr(PartyEntry* party, f32 dir);
static inline u32 partyGetFrontAttrFar(PartyEntry* party);
static s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir);

static void party_force_reset_outofscreen(PartyEntry* party);

/* The demo keeps the footstep helpers here, not in party_move.c. */
void partyWalkSe(PartyEntry* party, s32 arg) {
    s32 a;
    s32 b;

    party->footstepTimer++;
    if (party->currentMemberId == PARTY_MEMBER_FLAVIO) {
        if (arg == 0) {
            a = 20;
            b = 40;
        } else {
            a = 10;
            b = 20;
        }
        if (party->footstepTimer >= b) {
            party->footstepTimer = 0;
            psndSFXOn_3D((const char*)0x60D, &party->position);
        } else if (party->footstepTimer == a) {
            psndSFXOn_3D((const char*)0x60C, &party->position);
        }
    } else if (party->currentMemberId == PARTY_MEMBER_EGG) {
        if (party->footstepTimer >= 15) {
            party->footstepTimer = 0;
            psndSFXOn_3D((const char*)0x942, &party->position);
        }
    } else if (party->currentMemberId == PARTY_MEMBER_PUNIO) {
        if (arg == 0) {
            a = 5;
            b = 10;
        } else {
            a = 5;
            b = 10;
        }
        if (party->footstepTimer >= b) {
            party->footstepTimer = 0;
            psndSFXOn_3D((const char*)0x3FF, &party->position);
        } else if (party->footstepTimer == a) {
            psndSFXOn_3D((const char*)0x3FF, &party->position);
        }
    } else if (party->moveKind == 1) {
        if (party->footstepTimer >= (!arg ? 40 : 20)) {
            party->footstepTimer = 0;
            psndSFXOn_3D((const char*)0x926, &party->position);
        }
    } else {
        if (arg == 0) {
            a = 20;
            b = 40;
        } else {
            a = 10;
            b = 20;
        }
        if (party->footstepTimer >= b) {
            party->footstepTimer = 0;
            psndSFXOn_3D((const char*)0x925, &party->position);
        } else if (party->footstepTimer == a) {
            psndSFXOn_3D((const char*)0x924, &party->position);
        }
    }
}

/**
 * Demos: walk (pose 3) at 1.25 units/frame or faster, otherwise the slow walk (pose 2),
 * with the matching footstep sound. Retail keeps this in party_move.c.
 */
void partyMoveAnime(PartyEntry* party, f32 spd) {
    if (spd >= 1.25f) {
        partyChgPoseId(party, 3);
        partyWalkSe(party, 1);
    } else {
        partyChgPoseId(party, 2);
        partyWalkSe(party, 0);
    }
}

/** Height of the floor below (x, y + 40, z), rounded to 0.01, or -2000 when there is none. */
static inline void partyGetGndYTo(f32* out, f32 x, f32 y, f32 z) {
    f32 hx, hy, hz, dist, nx, ny, nz;
    HitEntry* hit;
    y += 40.0f;
    dist = 1000.0f;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, 0.0f, -1.0f, 0.0f);
    if (!hit) {
        *out = -2000.0f;
    } else {
        *out = (s32)(100.0f * hy + 0.5f) / 100.0f;
        hitGetAttr(hit);
    }
}

/**
 * Demos: FALSE while the partner should not chase Mario's height:
 * he is in the air without moving, or in his damage or Spin Jump motion.
 * The retail check below also covers the spike damage motion.
 */
static inline BOOL partyChkMarioFollowYDemo(MarioWork* mario) {
    if (mario->airTimer != 0 && mario->baseSpeed == 0.0f) {
        return FALSE;
    }
    if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_HIP || mario->currMotionId == MARIO_MOTION_HIP_2) {
        return FALSE;
    }
    return TRUE;
}

/**
 * Demos: the walking partner's follow motion (motion 1 of move mode 1):
 * walks along Mario's footmarks, jumps up ledges and onto their marked jump spots, steps up stairs,
 * falls off edges and enters slits.
 * Older and simpler than the retail copy (fixed 40/homingDist follow distances, no speed catch-up).
 */
void party_motion_homing_walk(PartyEntry* party) {
    HitEntry* hit;
    s32 id;
    MarioWork* mario;
    s32 i;
    PartyFootmark* fm;
    u32 attr;
    f32 lim;
    f32 lim2;
    f32 spd;
    f32 dir;
    f32 sp;
    f32 d3;
    f32 px, py, pz;
    f32 a;
    Vec v;
    Vec t;
    Vec t2;
    Vec t3;
    Vec hp;
    Vec p2;
    Vec p3;
    f32 fsy, fsa, fsb;
    f32 hh;

    id = partyGetFootmarkId(party);
    mario = party->playerPtr;
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    if (party->forceMoveFrames != 0) {
        lim = 28.0f;
    } else {
        lim = 40.0f;
    }
    lim2 = party->homingDist;
    if (mario->characterId == 2) {
        lim2 = 70.0f;
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12")) {
        if (!marioKeyOffChk()) {
            lim = 24.0f;
            lim2 = lim;
            party->trigFlags |= PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        }
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
        lim2 = 24.0f;
    }
    if (!party_slit(party)) {
        return;
    }
    if (!party_roll(party)) {
        return;
    }
    if (mario->currMotionId == MARIO_MOTION_TALK && !(party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (!partyChkMarioFollowYDemo(party->playerPtr)) {
        partyChgMot(party, 0);
        return;
    }
    spd = ((party->flags & PARTY_FLAG_IN_SHALLOW_WATER) ? 0.75f : 1.0f) * partyGetTargetMovespd2(party);
    party->moveSpeed = spd;
    if ((party->flags & PARTY_FLAG_IS_PARTNER) && partyGetPtr(marioGetPartyId())) {
        lim2 = 20.0f;
        lim = lim2;
        party->moveSpeed = 2.0f;
    }
    px = party->position.x;
    i = 0;
    py = party->position.y;
    pz = party->position.z;
    do {
        fm = partyGetFootmarkPtr(id);
        t = fm->pos;
        // dir is not set yet on the first pass: the demo reads it uninitialized here.
        attr = partyGetFrontAttr(party, dir);
        if (!(attr & HIT_ATTR_SPIKES)) {
            goto found;
        }
        partyNextReadId(id);
        partyGetReadId2(id, &t);
    } while (++i <= 10);
    t = marioGetPtr()->position;
found:
    p2 = party->position;
    if (partyGetTargetDist3D(id, &p2) >= lim) {
        party->moveSpeed = spd;
    }
    if (lim2 < 20.0f) {
        party->moveSpeed = spd;
    }
    while (TRUE) {
        d3 = distABf(px, pz, t.x, t.z);
        dir = angleABf(px, pz, t.x, t.z);
        if (d3 > 0.5f * party->width + party->moveSpeed) {
            p3 = (Vec){px, py, pz};
            d3 = partyGetTargetDist3D(id, &p3);
            if (d3 >= lim) {
                if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    party->moveSpeed = mario->baseSpeed + a;
                }
                break;
            }
            if (marioGetSlitFloorPos(&v)) {
                party->moveSpeed = 1.5f;
                partyNextReadId(id);
                if (marioGetSlitFloorPos(&v)) {
                    t = v;
                    d3 = distABf(px, pz, t.x, t.z);
                    dir = angleABf(px, pz, t.x, t.z);
                    if (d3 <= 5.0f) {
                        // FAKE: called through a cast so it stays a call (a direct call is inlined here; see docs/FAKES.md)
                        ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
                    }
                }
                break;
            }
            if (d3 > lim2) {
                if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    party->moveSpeed = mario->baseSpeed + a;
                } else {
                    party->moveSpeed = d3 - lim2;
                    if (party->moveSpeed >= 1.0f) {
                        party->moveSpeed = 1.0f;
                        if (lim2 < 20.0f) {
                            party->moveSpeed = spd;
                        }
                    } else {
                        party->moveSpeed += 0.2f;
                    }
                }
                break;
            }
            party->moveSpeed = 0.0f;
        }
        if (partyGetFootmarkReadId(id) == partyGetFootmarkWriteId(id)) {
            dir = party->targetDir;
            party->moveSpeed = 0.0f;
            party->gravity = 0.0f;
            if (!(party->flags & PARTY_FLAG_POSE_TILTED)) {
                partyChgPoseId(party, 1);
            }
            partyChgMot(party, 0);
            break;
        }
        partyNextReadId(id);
        partyGetReadId2(id, &t);
        if (!(party->flags & PARTY_FLAG_DISABLE_FLOORS)) {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
            hit = _partySearchGround(party, &py, &d3, 10.0f, 0.0f);
            if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
                hit = NULL;
                if (!party->splashTimer) {
                    party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                    party->flags |= PARTY_FLAG_FORCE_FALL;
                }
            }
            party->hitobjStandOn = hit;
            if (!hit) {
                partyChgMot(party, 3);
                party->gravity = -1.0f;
            } else {
                attr = hitGetAttr(hit);
                if (attr & HIT_ATTR_SHALLOW_WATER) {
                    party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
                } else {
                    party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
                }
                if (attr & HIT_ATTR_SPIKES) {
                    partyChgMot(party, 0);
                    break;
                }
            }
        }
        if ((party->flags & PARTY_FLAG_IS_GROUNDED) && (fm->flags & PARTY_FOOTMARK_JUMP)) {
            partyChgMot(party, 2);
            break;
        }
        if ((party->flags & PARTY_FLAG_IS_GROUNDED) && (fm->flags & PARTY_FOOTMARK_SLIT)) {
            d3 = distABf(px, pz, t.x, t.z);
            if (d3 <= 5.0f) {
                // FAKE: called through a cast so it stays a call (a direct call is inlined here; see docs/FAKES.md)
                ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
            }
            break;
        }
    }
    if (party->moveSpeed) {
        partyMoveAnime(party, party->moveSpeed);
    } else if (!(fm->flags & PARTY_FOOTMARK_SLIT)) {
        partyChgMot(party, 0);
    }
    party->targetDir = dir;
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &sp);
    hit = partySearchFrontWall(party, &v, sp, dir);
    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        hit = NULL;
    }
    if (!hit) {
        if (!(party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE)) {
            getFrontFloor(party, &t, party->targetDir);
        } else {
            party->homeDir = revise360(270.0f + mario->targetYaw);
            partyGetAppearPos4(party, &t);
        }
        if (t.y > party->position.y) {
            if (t.y - party->position.y > 5.0f) {
                partyChgMot(party, 2);
                return;
            }
            if (t.y > party->position.y) {
                party->position.y = t.y;
            }
        }
        if (party->moveSpeed) {
            attr = partyGetFrontAttrFar(party);
            if (!(attr & HIT_ATTR_DEEP_WATER)) {
                v.x = party->position.x;
                v.z = party->position.z;
                movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
            }
        }
    } else {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
            if (hitGetAttr(hit) & HIT_ATTR_PAPER_SLIT) {
                if (party->slitOn != 1) {
                    party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
                    party->slitOn = 1;
                } else if (party->moveSpeed) {
                    v.x = party->position.x;
                    v.z = party->position.z;
                    movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
                }
            } else {
                d3 = partyGetTargetDistY(id, party->position.y);
                if (d3 >= 100.0f) {
                    partyChgMot(party, 0);
                    if (++party->wallStuckCount > 60) {
                        party->wallStuckCount = 100;
                        partyGetAppearPos(party, &party->position);
                        return;
                    }
                } else if (d3 >= 1.0f) {
                    getFrontFloor(party, &t2, party->targetDir);
                    if (t2.y - party->position.y > 5.0f) {
                        partyChgMot(party, 2);
                        return;
                    }
                    if (!(party->flags & (PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING))) {
                        partyChkFrontStep(party, 11.0f, &fsy, &fsa, &fsb);
                        if (fsy - party->position.y >= 5.0f && party->groundSlope <= 30.0f) {
                            party->stepY = fsy;
                            if (party->moveSpeed) {
                                partyChgMot(party, 6);
                                return;
                            }
                        }
                    }
                } else {
                    dir = partyGetTargetDir(id, party->position.x, party->position.z);
                    getFrontFloor(party, &t3, dir);
                    a = t3.y - party->position.y;
                    if (a > 100.0f) {
                        party->position = t3;
                        partyChgMot(party, 1);
                    } else if (a >= 0.0f) {
                        partyChgMot(party, 2);
                    } else {
                        partyChgMot(party, 0);
                    }
                }
            }
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    hh = party->height;
    hp = party->position;
    hit = ((PartySearchHeadRetVoidptrFn)partySearchHead)(party, &hp, &hh, party->displayDirection);
    if (hit) {
        party->hitobjHead = hit;
    }
    party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
    hit = _partySearchGround(party, &v.y, &d3, 10.0f, 10.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_DEEP_WATER) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        } else if (attr & HIT_ATTR_SPIKES) {
            partyChgRunMode(party, 13);
            return;
        }
    }
    party->hitobjStandOn = hit;
    if (!hit) {
        partyChgMot(party, 3);
        party->gravity = -1.0f;
    } else {
        if (hitGetAttr(hit) & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
        if (hitGetAttr(hit) & HIT_ATTR_DAMAGE_RETURN) {
            party->damageHit = hit;
        }
    }
    party->position.y = v.y;
    party_force_reset_outofscreen(party);
}

/**
 * Demos: floor point one partner width ahead in direction dir, rounded to 0.001, written to out;
 * returns its hit attributes, or 0 with out = the partner's position when there is none.
 * Probes from at most 40 above the partner, staying under any ceiling found in front.
 */
static s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir) {
    f32 s2, c2;
    HitCheckQuery q2;
    HitCheckQuery q;
    f32 c, s;
    f32 r;
    f32 wallct;
    f32 y;
    f32 rf;
    s32 i;
    HitEntry* hit;

    r = 2.0f * party->width / 3.0f;
    q.targetDir = (Vec){0.0f, 1.0f, 0.0f};
    wallct = 40.0f;
    sincosf(&s, &c, dir);
    for (i = 0; i < 3; i++) {
        q.targetPos.x = party->position.x + (f32)i * (s * r);
        q.targetPos.z = party->position.z + (f32)i * (c * r);
        q.targetPos.y = party->position.y + party->height;
        q.targetDistance = 100.0f;
        if (hitCheckVecFilter(&q, NULL)) {
            if (sqrtf(q.hitNormal.x * q.hitNormal.x + q.hitNormal.z * q.hitNormal.z) < 45.0f) {
                y = q.hitPos.y;
                goto found;
            }
        }
    }
    y = -2000.0f;
found:
    if (y > -2000.0f) {
        f32 u;
        f32 t;
        t = party->position.y + wallct;
        u = y - 2.0f;
        if (t < u) {
            q2.targetPos.y = t;
        } else {
            q2.targetPos.y = u;
        }
    } else {
        q2.targetPos.y = party->position.y + wallct;
    }
    r = party->width;
    sincosf(&s2, &c2, dir);
    q2.targetPos.x = s2 * r + party->position.x;
    q2.targetPos.z = c2 * r + party->position.z;
    q2.targetDistance = 300.0f;
    q2.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q2, NULL);
    if (!hit) {
        out->x = party->position.x;
        out->y = party->position.y;
        out->z = party->position.z;
        return 0;
    }
    rf = q2.hitPos.x >= 0.0f ? 0.5f : -0.5f;
    out->x = (s32)((1000.0f * q2.hitPos.x) + rf) / 1000.0f;
    rf = q2.hitPos.y >= 0.0f ? 0.5f : -0.5f;
    out->y = (s32)((1000.0f * q2.hitPos.y) + rf) / 1000.0f;
    rf = q2.hitPos.z >= 0.0f ? 0.5f : -0.5f;
    out->z = (s32)((1000.0f * q2.hitPos.z) + rf) / 1000.0f;
    return hitGetAttr(hit);
}

/** Unused helpers (as in the retail copy below); each keeps its down-vector literal in .rodata. */
static inline void partyDownDirX(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}

/**
 * Demos: hit attributes of the floor 20 units ahead in direction dir (probed from 20 up, 40 down), 0 if none.
 * Homing walk uses it to skip footmarks over 0x800 floors.
 */
static inline u32 partyGetFrontAttr(PartyEntry* party, f32 dir) {
    HitCheckQuery q;
    HitEntry* hit;
    f32 s, c;
    sincosf(&s, &c, dir);
    q.targetDistance = 40.0f;
    q.targetPos.x = 20.0f * s + party->position.x;
    q.targetPos.z = 20.0f * c + party->position.z;
    q.targetPos.y = 20.0f + party->position.y;
    q.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q, NULL);
    return hit ? hitGetAttr(hit) : 0;
}

/**
 * Demos: hit attributes of the floor 40 units ahead along targetDir (probed from 40 up, 100 down), 0 if none.
 * Homing walk does not step forward when it is 0x200 (water).
 */
static inline u32 partyGetFrontAttrFar(PartyEntry* party) {
    HitCheckQuery q;
    HitEntry* hit;
    f32 s, c;
    f32 k = 40.0f;
    sincosf(&s, &c, party->targetDir);
    q.targetDistance = 100.0f;
    q.targetPos.x = s * k + party->position.x;
    q.targetPos.z = c * k + party->position.z;
    q.targetPos.y = party->position.y + k;
    q.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q, NULL);
    return hit ? hitGetAttr(hit) : 0;
}

/** Unused: sets a hit query's direction to straight down. */
static inline void partyDownDirY(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}

/**
 * Demos: while Mario has control, pulls a partner that has left the screen (more than 40 px past the sides or
 * 650 px down) back toward Mario step by step onto the floor until it is on screen, and clears the footmarks.
 * A partner right under Mario but far down the screen is put at its appear position instead.
 */
static void party_force_reset_outofscreen(PartyEntry* party) {
    MarioWork* m2;
    s32 i;
    s32 margin;
    s32 j;
    MarioWork* mario = party->playerPtr;
    f32 speed;
    f32 y;
    f32 up;
    HitEntry* hit;
    f32 dist;
    f32 sx, sy, sz;
    Vec pos;
    Vec start;
    Vec dir;
    Vec hitPos;
    Vec nrm;

    if (marioCtrlOffChk()) {
        return;
    }
    if (marioKeyOffChk()) {
        return;
    }
    marioGetScreenPos(party->position, &sx, &sy, &sz);
    if (distABf(mario->position.x, mario->position.z, party->position.x, party->position.z) < 20.0f &&
        sy > 800.0f) {
        partyGetAppearPos3(party, &pos);
        party->position = pos;
        return;
    }
    margin = 40;
    if (-40.0f <= sx && sx <= 640.0f && sy <= 650.0f) {
        return;
    }
    partyClearFootmark();
    m2 = party->playerPtr;
    i = 0;
    pos = party->position;
    if (party->moveKind == 0) {
        speed = party->width;
    } else if (party->currentMemberId == PARTY_MEMBER_FLURRIE) {
        speed = 10.0f;
        margin = 70;
    } else {
        speed = 10.0f;
        margin = 50;
    }
    {
        Vec d = {0.0f, -1.0f, 0.0f};
        dir = d;
    }
    while (TRUE) {
        marioGetScreenPos(pos, &sx, &sy, &sz);
        if ((f32)-margin <= sx && sx <= (f32)(margin + 600)) {
            party->position = pos;
            return;
        }
        if (i > 100) {
            return;
        }
        {
            f32 a = angleABf(pos.x, pos.z, m2->position.x, m2->position.z);
            movePos(&pos.x, &pos.z, speed, a);
        }
        up = 200.0f;
        j = 0;
        while (TRUE) {
            dist = 300.0f;
            start = pos;
            start.y += up;
            hit = partyHitCheck(party, &start, &dir, &hitPos, &nrm, &dist);
            if (hit) {
                y = hitPos.y;
            } else {
                y = m2->position.y;
            }
            start.y = y;
            marioGetScreenPos(start, &sx, &sy, &sz);
            if (sy > 100.0f) {
                dist = 100.0f;
                start = pos;
                if (pos.y + 74.0f > y) {
                    start.y += 74.0f;
                    hit = partyHitCheck(party, &start, &dir, &hitPos, &nrm, &dist);
                    if (hit) {
                        y = hitPos.y;
                    }
                }
                break;
            }
            if (++j > 4) {
                break;
            }
            up -= 50.0f;
            if (up < 0.0f) {
                up = 0.0f;
            }
        }
        pos.y = y;
        i++;
    }
}

/**
 * Moves a jumping partner forward by moveSpeed along targetDir, stopped by walls;
 * records the wall in hitobjFront/hitobjPush.
 * With the front wall check disabled it moves a scratch vector that is never stored,
 * so the partner does not move sideways at all.
 */
static inline void partyJumpFrontMove(PartyEntry* party) {
    Vec v;
    HitEntry* hit;
    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
        return;
    }
    v = party->position;
    hit = partySearchFrontWall(party, &v, party->moveSpeed, party->targetDir);
    if (hit) {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
}

/**
 * Demos: the follow jump (motion 2): aims at the next footmark or moveTarget,
 * sets up an arc by distance and height, plays the jump sound,
 * then flies it until landing (motion 0) or a splash in water (motion 3).
 */
void party_motion_jump(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 id;
    HitEntry* hit;
    f32 dir;
    f32 d;
    f32 gy;
    f32 dy;
    f32 t;
    f32 g;
    Vec fl;
    Vec fl2;
    f32 x, y, z;
    f32 s, c;

    id = partyGetFootmarkId(party);
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->motionStep = 0;
    }
    switch (party->motionStep) {
        case 0:
            if (party->forceMoveFrames == 0 && party->runMode != 9) {
                if (partyGetFootmarkReadId(0) == partyGetFootmarkWriteId(0)) {
                    d = partyGetTargetDist(id, party->position.x, party->position.z);
                    if (d > 2.0f * mario->wPlayerCollisionBox.x) {
                        dir = partyGetTargetDir(id, party->position.x, party->position.z);
                        getFrontFloor(party, &fl, dir);
                        fl.y += 10.0f;
                        y = party->position.y + fl.y;
                        x = party->position.x;
                        z = party->position.z;
                        movePos(&x, &z, 0.6f * party->width, dir);
                    }
                    partyNextReadId(partyGetFootmarkId(party));
                } else {
                    partyNextReadId(0);
                    partyGetReadId(0, &x, &y, &z);
                    d = distABf(party->position.x, party->position.z, x, z);
                    sincosf(&s, &c, angleABf(party->position.x, party->position.z, x, z));
                    x += d * s;
                    z += d * c;
                }
            } else {
                x = party->position.x;
                y = party->position.y;
                z = party->position.z;
                movePos(&x, &z, party->moveSpeed, party->targetDir);
                partyNextReadId(partyGetFootmarkId(party));
            }
            party->moveTarget = (Vec){x, y, z};
            party->moveDistance = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
            if (party->forceMoveFrames == 0) {
                party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
                party->moveSpeed = 2.25f;
            }
            party->moveFrames = (s32)(10.0f * (party->moveDistance / party->moveSpeed) + 0.5f) / 10.0f;
            if (party->moveFrames < 16) {
                party->moveFrames = 16;
            }
            if (party->moveFrames > 30) {
                party->moveFrames = 30;
            }
            dy = party->moveTarget.y - party->position.y;
            t = 0.5f * party->moveFrames;
            if (__fabsf(dy) < 1.0f) {
                dy = 10.0f;
            } else if (dy >= 0.0f) {
                dy += 0.5f * party->height;
            } else {
                dy = 10.0f;
            }
            getFrontFloor(party, &fl2, party->targetDir);
            if (fl2.y >= party->position.y) {
                dy = 10.0f + (fl2.y - party->position.y);
            }
            g = (dy + dy) / (t * t - t);
            party->velY = g * t;
            party->gravity = -g;
            partyChgPoseId(party, 4);
            party->flags |= PARTY_FLAG_IS_JUMPING;
            party->flags &= ~PARTY_FLAG_IS_GROUNDED;
            psndSFXOn_3D((const char*)0x927, &party->position);
            party->motionStep = 10;
            break;
        case 10:
            partyNextReadId(partyGetFootmarkId(party));
            party->velY += party->gravity;
            party->position.y += party->velY;
            if (party->position.y < -2000.0f) {
                party->flags &= ~PARTY_FLAG_IS_JUMPING;
                party->velY = 0.0f;
                party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
                party->position = mario->position;
                partyChgMot(party, 0);
                break;
            }
            if (party->velY <= 0.0f) {
                hit = _partySearchGround(party, &gy, &d, __fabsf(party->velY), 0.0f);
                if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
                    if (!party->splashTimer) {
                        party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                        party->flags |= PARTY_FLAG_FORCE_FALL;
                    }
                    party->hitobjStandOn = NULL;
                    partyChgMot(party, 3);
                    party->gravity = -1.0f;
                    break;
                }
                party->position.y = gy;
                party->hitobjStandOn = hit;
                if (hit) {
                    psndSFXOn_3D((const char*)0x928, &party->position);
                    party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
                    party->flags |= PARTY_FLAG_IS_GROUNDED;
                    party->velY = 0.0f;
                    partyChgMot(party, distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z) < 5.0f ? 0 : 1);
                    break;
                }
            }
            partyJumpFrontMove(party);
            break;
    }
}

/**
 * Demos: the jump to moveTarget used by the behind/beside-Mario modes (motion 2 there):
 * at most 50 units across, at least 10 frames; on landing it goes to stay
 * or follow depending on how close moveTarget is.
 */
void party_motion_jump2(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    Vec pos;
    f32 d;
    f32 dy;
    s32 frames;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->moveFrames = 0;
        party->gravity = -1.0f;
        party->moveSpeed = 2.25f;
        party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        d = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        if (d > 50.0f) {
            d = 50.0f;
        }
        party->moveDistance = d;
        dy = party->moveTarget.y - party->position.y;
        frames = (s16)(d / party->moveSpeed);
        if (frames < 10) {
            frames = 10;
        }
        party->moveSpeed = party->moveDistance / frames;
        party->moveFrames = frames;
        party->velY = (frames * (frames * __fabsf(party->gravity)) / 2.0f + dy) / frames;
        if (party->velY > 20.0f) {
            party->velY = 20.0f;
        }
        if (party->velY < 0.0f) {
            party->velY = 0.0f;
        }
        partyChgPoseId(party, 4);
        party->flags |= PARTY_FLAG_IS_JUMPING;
        party->flags &= ~PARTY_FLAG_IS_GROUNDED;
        psndSFXOn_3D((const char*)0x927, &party->position);
        party->motionStep = 0;
    }
    switch (party->motionStep) {
        case 0:
            party->motionStep = 1;
            break;
        case 1:
            party->velY += party->gravity;
            party->position.y += party->velY;
            pos = party->position;
            partySearchFrontWall(party, &pos, party->moveSpeed, party->targetDir);
            party->position.x = pos.x;
            party->position.z = pos.z;
            if (party->velY <= 0.0f) {
                hit = _partySearchGround(party, &pos.y, &d, __fabsf(party->velY), 0.0f);
                if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
                    if (!party->splashTimer) {
                        party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                        party->flags |= PARTY_FLAG_FORCE_FALL;
                    }
                    party->hitobjStandOn = NULL;
                    partyChgMot(party, 3);
                    party->gravity = -1.0f;
                    return;
                }
                party->position.y = pos.y;
                party->hitobjStandOn = hit;
                if (hit) {
                    psndSFXOn_3D((const char*)0x928, &party->position);
                    party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
                    party->flags |= PARTY_FLAG_IS_GROUNDED;
                    party->velY = 0.0f;
                    partyChgMot(party, distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z) < 5.0f ? 0 : 1);
                }
            }
            break;
    }
    if (party->position.y < -2000.0f) {
        party->flags &= ~PARTY_FLAG_IS_JUMPING;
        party->velY = 0.0f;
        party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
        party->position = mario->position;
        partyChgMot(party, 0);
    }
}

/**
 * Demos: the flying partner's follow motion (Flurrie, Vivian and the like; motion 1 of move mode 1):
 * floats along Mario's footmarks, easing its height toward the floor ahead or Mario.
 * touch_wall_ct counts frames against a wall with no floor behind it; after 10 it heads straight for Mario.
 */
void party_motion_homing_fly(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 id;
    s32 near;
    HitEntry* hit;
    MarioWork* m2;
    PartyFootmark* fm;
    u32 attr;
    f32 lim2;
    f32 lim;
    f32 spd;
    f32 px, pz;
    f32 dir, sp;
    f32 dd;
    f32 py;
    f32 tx, ty, tz;
    f32 x, z;
    f32 y;
    Vec v;
    Vec ap;
    Vec p;
    Vec p3;

    id = partyGetFootmarkId(party);
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    if (party->forceMoveFrames != 0) {
        lim = 28.0f;
    } else {
        lim = 40.0f;
    }
    lim2 = party->homingDist;
    if (!party_slit(party)) {
        return;
    }
    if (!party_roll(party)) {
        return;
    }
    spd = ((party->flags & PARTY_FLAG_IN_SHALLOW_WATER) ? 0.75f : 1.0f) * partyGetTargetMovespd2(party);
    party->moveSpeed = spd;
    p = party->position;
    if (partyGetTargetDist3D(id, &p) >= lim) {
        party->moveSpeed = spd;
    }
    if (lim2 < 20.0f) {
        party->moveSpeed = spd;
    }
    fm = partyGetFootmarkPtr(id);
    near = 0;
    tx = fm->pos.x;
    ty = 5.0f + fm->pos.y;
    tz = fm->pos.z;
    px = party->position.x;
    py = party->position.y;
    pz = party->position.z;
    while (TRUE) {
        dir = angleABf(px, pz, tx, tz);
        dd = distABf(px, pz, tx, tz);
        if (dd > 0.5f * party->width + party->moveSpeed) {
            p3 = party->position;
            dd = partyGetTargetDist3D(id, &p3);
            if (dd >= lim) {
                near = 1;
                break;
            }
            if (dd > lim2) {
                party->moveSpeed = dd - lim2;
                if (party->moveSpeed >= 1.0f) {
                    party->moveSpeed = 1.0f;
                    if (lim2 < 20.0f) {
                        party->moveSpeed = spd;
                    }
                } else {
                    party->moveSpeed += 0.2f;
                }
                break;
            }
            party->moveSpeed = 0.0f;
            party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
            partyChgPoseId(party, 1);
        }
        if (partyGetFootmarkReadId(id) == partyGetFootmarkWriteId(id)) {
            dir = party->targetDir;
            party->moveSpeed += 0.1f * (-1.0f - party->moveSpeed);
            if (party->moveSpeed < 0.0f) {
                party->moveSpeed = 0.0f;
                party->gravity = 0.0f;
                if (!(party->flags & PARTY_FLAG_POSE_TILTED)) {
                    partyChgPoseId(party, 1);
                }
                partyChgMot(party, 0);
            }
            break;
        }
        partyNextReadId(id);
        partyGetReadId(id, &tx, &ty, &tz);
        if (party->flags & PARTY_FLAG_DISABLE_FLOORS) {
            continue;
        }
        party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        hit = _partySearchGround(party, &py, &dd, 100.0f, 100.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
        }
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
            continue;
        }
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
        if (attr & HIT_ATTR_SPIKES) {
            partyChgMot(party, 0);
            break;
        }
    }
    if (party->moveSpeed) {
        partyMoveAnime(party, party->moveSpeed);
    } else {
        partyChgMot(party, 0);
    }
    if (touch_wall_ct > 10) {
        dir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
    }
    if (near) {
        m2 = party->playerPtr;
        partyGetAppearPos3(party, &ap);
        dir = angleABf(party->position.x, party->position.z, ap.x, ap.z);
        hit = _partySearchGround(party, &ap.y, &dd, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
        }
        if (hit) {
            party->position.y = ap.y;
        } else {
            party->position.y += 0.05f * ((10.0f + m2->position.y) - party->position.y);
        }
    }
    party->targetDir = dir;
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &sp);
    hit = partySearchFrontWall(party, &v, sp, dir);
    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        hit = NULL;
    }
    if (hit) {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
            if (hitGetAttr(hit) & HIT_ATTR_PAPER_SLIT) {
                if (party->slitOn != 1) {
                    party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
                    party->slitOn = 1;
                } else if (party->moveSpeed) {
                    v.x = party->position.x;
                    v.z = party->position.z;
                    movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
                }
            } else {
                x = party->position.x;
                y = party->position.y;
                z = party->position.z;
                movePos(&x, &z, party->width, dir);
                partyGetGndYTo(&py, x, y, z);
                if (py > -2000.0f) {
                    party->position.y += 0.05f * ((py + party->height) - party->position.y);
                } else {
                    touch_wall_ct++;
                    if (partyGetTargetDistY(id, party->position.y) >= 1.0f &&
                        __fabsf(mario->position.y - party->position.y) >= 10.0f) {
                        party->position.y = party->position.y + 0.1f * ((10.0f + mario->position.y) - party->position.y);
                        party->position.x = v.x;
                        party->position.z = v.z;
                        return;
                    }
                }
            }
        }
    } else {
        touch_wall_ct = 0;
        if (party->moveSpeed) {
            v.x = party->position.x;
            v.z = party->position.z;
            movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    party_force_reset_outofscreen(party);
}
/**
 * Demos: the fall motion (motion 3): applies gravity,
 * lands on a floor (stay or follow by speed, landing sound) and drops the partner back behind Mario
 * when it falls below -2000. Returns 2 while falling, 3 on landing.
 */
s32 party_motion_fall(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    f32 gy;
    f32 depth;

    partyNextReadId(partyGetFootmarkId(party));
    if (__fabsf(mario->position.y - party->position.y) <= 74.0f) {
        party->flags &= ~PARTY_FLAG_FORCE_FALL;
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        partyChgPoseId(party, 4);
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    hit = NULL;
    if (!(party->flags & PARTY_FLAG_FORCE_FALL)) {
        hit = _partySearchGround(party, &gy, &depth, 10.0f, __fabsf(party->velY));
    }
    if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
        hit = NULL;
        if (party->moveKind == 0 && !party->splashTimer) {
            party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
            party->flags |= PARTY_FLAG_FORCE_FALL;
        }
    }
    party->hitobjStandOn = hit;
    if (!hit) {
        party->flags &= ~PARTY_FLAG_IS_GROUNDED;
        if (!(party->flags & PARTY_FLAG_IS_FALLING)) {
            party->flags |= PARTY_FLAG_IS_FALLING;
            if (party->gravity == 0.0f) {
                party->gravity = -1.4f;
            }
        }
        party->velY += party->gravity;
        if (party->velY < -16.0f) {
            party->velY = -16.0f;
        }
        party->position.y += party->velY;
        if (party->position.y < -2000.0f) {
            party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
            party->velY = 0.0f;
            party->gravity = 0.0f;
            party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
            party->homeDir = revise360(180.0f + toMovedir(mario->displayDirectionTarget));
            partyGetAppearPos4(party, &party->position);
            party->position.y += 37.0f;
            partyChgMot(party, 0);
        }
        if (party->moveSpeed) {
            Vec pos = party->position;
            partySearchFrontWall(party, &pos, 1.3f * party->moveSpeed, party->targetDir);
            party->position.x = pos.x;
            party->position.z = pos.z;
        }
        return 2;
    }
    if (party->flags & PARTY_FLAG_IS_FALLING) {
        party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
        party->flags |= PARTY_FLAG_IS_GROUNDED;
        party->velY = 0.0f;
        party->position.y = gy;
        if (party->moveSpeed == 0.0f) {
            partyChgMot(party, 0);
        } else {
            partyChgMot(party, 1);
        }
        psndSFXOn_3D((const char*)0x928, &party->position);
        return 3;
    }
    if (hit) {
        party->flags &= ~PARTY_FLAG_MOT_SLIT_FLOOR;
        party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
        party->flags |= PARTY_FLAG_IS_GROUNDED;
        party->velY = 0.0f;
        party->position.y = gy;
        if (party->moveSpeed == 0.0f) {
            partyChgMot(party, 0);
        } else {
            partyChgMot(party, 1);
        }
        psndSFXOn_3D((const char*)0x928, &party->position);
        partyClearFootmark();
        return 3;
    }
    party->position.y = gy;
    if (party->moveSpeed) {
        Vec pos = party->position;
        partySearchFrontWall(party, &pos, 1.3f * party->moveSpeed, party->targetDir);
        party->position.x = pos.x;
        party->position.z = pos.z;
    }
    return 0;
}

/** Demos: the step-up motion (motion 6): rises to stepY over 3 frames, then goes back to following (motion 1). */
void party_motion_upstairs(PartyEntry* party) {
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->motionStep = 0;
        party->flags |= PARTY_FLAG_IS_STEPPING;
        party->velY = 0.0f;
        party->accelY = 0.0f;
        party->gravity = 0.0f;
        party->moveFrames = 3;
        party->velY = (party->stepY - party->position.y) / party->moveFrames;
    }
    switch (party->motionStep) {
        case 0:
            party->position.y += party->velY;
            if (--party->moveFrames <= 0) {
                party->flags &= ~PARTY_FLAG_IS_STEPPING;
                partyChgMot(party, 1);
            }
            break;
    }
}

/**
 * Demos: makes the next behind-Mario walk stand at direction dir (degrees) from Mario instead of behind his
 * facing. Retail adds the camera yaw.
 */
void party_set_behind_dir(PartyEntry* party, f32 dir) {
    party->homeDir = dir;
    party->trigFlags |= PARTY_TRIG_FLAG_HOME_DIR_SET;
}

/**
 * Movement direction (degrees) of whoever this partner follows:
 * Mario, or for a second partner the first one when it is out.
 */
static inline f32 partyGetFollowDir(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* other;
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        return toMovedir(mario->displayDirection);
    }
    other = partyGetPtr(marioGetPartyId());
    if (other) {
        return partyToMovedir(party, other->displayDirection);
    }
    return toMovedir(mario->displayDirection);
}

/**
 * Demos: walks the partner to its spot behind Mario (or at homeDir) for move mode 2 (partyMoveBehindMario,
 * talking), jumping where the floor height changes;
 * when it arrives or hits a wall it goes back to normal following (move mode 1).
 */
void party_motion_behind_mario(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    f32 ang;
    f32 thr;
    f32 ty;
    f32 spd;
    Vec target;
    f32 x, z;
    f32 dist;
    f32 gy;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET)) {
            {
                f32 t;
                if (!(party->trigFlags & PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET)) {
                    t = partyGetFollowDir(party);
                    t += 180.0f;
                    t = revise360(t);
                } else {
                    party->trigFlags &= ~PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET;
                    t = revise360(180.0f + angleABf(mario->position.x, mario->position.z, party->moveTarget.x, party->moveTarget.z));
                }
                party->homeDir = t;
            }
        }
        partyGetAppearPos4(party, &target);
        party->moveFrames = distABf(party->position.x, party->position.z, target.x, target.z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET) && marioKeyOffChk()) {
        {
            f32 t2 = partyGetFollowDir(party);
            t2 += 180.0f;
            party->homeDir = revise360(t2);
        }
    }
    partyGetAppearPos4(party, &target);
    x = target.x;
    z = target.z;
    ty = target.y;
    ang = angleABf(party->position.x, party->position.z, x, z);
    {
        f32 py = ty;
        f32 nz, ny, nx, dd, hz, hy, hx;
        py += 40.0f;
        dd = 1000.0f;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
        if (!hit) {
            gy = -2000.0f;
        } else {
            gy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            hitGetAttr(hit);
        }
    }
    if (gy <= -2000.0f) {
        dist = 1.5f * mario->wPlayerCollisionBox.x;
        movePos(&x, &z, dist, toMovedir(mario->displayDirection));
    }
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    dist = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (dist >= thr && party->moveFrames > 0) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        spd = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET)) {
            if (spd > 2.0f) {
                spd = 2.0f;
            }
            if (spd < 1.0f) {
                spd = 1.0f;
            }
        } else {
            if (spd > 4.0f) {
                spd = 4.0f;
            }
            if (spd < 2.0f) {
                spd = 2.0f;
            }
        }
        party->moveSpeed = spd;
        partyMoveCheckWall(party);
        partyMoveAnime(party, party->moveSpeed);
        if (party->hitobjFront) {
            x = party->position.x;
            z = party->position.z;
            movePos(&x, &z, dist, ang);
            angleABf(party->position.x, party->position.z, x, z);
            {
                f32 py = ty;
                f32 GG;
                f32 nz, ny, nx, dd, hz, hy, hx;
                py += 40.0f;
                dd = 1000.0f;
                hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
                if (!hit) {
                    GG = -2000.0f;
                } else {
                    GG = (s32)(100.0f * hy + 0.5f) / 100.0f;
                    hitGetAttr(hit);
                }
                thr = GG;
            }
            if (__fabsf(party->position.y - thr) > 1.0f) {
                party->moveTarget.x = x;
                party->moveTarget.y = thr;
                party->moveTarget.z = z;
                partyChgMot(party, 2);
                return;
            }
        } else if (ty > party->position.y) {
            x = party->position.x;
            z = party->position.z;
            movePos(&x, &z, dist, ang);
            angleABf(party->position.x, party->position.z, x, z);
            {
                f32 py = ty;
                f32 GG;
                f32 nz, ny, nx, dd, hz, hy, hx;
                py += 40.0f;
                dd = 1000.0f;
                hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
                if (!hit) {
                    GG = -2000.0f;
                } else {
                    GG = (s32)(100.0f * hy + 0.5f) / 100.0f;
                    hitGetAttr(hit);
                }
                thr = GG;
            }
            if (__fabsf(party->position.y - thr) > 1.0f) {
                party->moveTarget.x = x;
                party->moveTarget.y = thr;
                party->moveTarget.z = z;
                partyChgMot(party, 2);
                return;
            }
        }
        hit = _partySearchGround(party, &gy, &dist, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        }
        party->position.y = gy;
    } else {
        party->moveFrames = 0;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
        party->trigFlags &= ~PARTY_TRIG_FLAG_HOME_DIR_SET;
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
    if (party->hitobjPush) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, x, z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
}

/**
 * Demos: move mode 6, set by partyReInit when the partner may not walk after a map change:
 * keeps the partner walking to the spot behind Mario's facing;
 * hands back to normal following once Mario stands still there.
 */
void party_motion_behind_mario_continue(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* other;
    HitEntry* hit;
    f32 y;
    f32 thr;
    f32 spd;
    f32 x, z;
    f32 sp;
    f32 gy;

    {
        f32 t = partyGetFollowDir(party);
        t += 180.0f;
        party->homeDir = revise360(t);
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, party->homeDir);
        party->moveFrames = distABf(party->position.x, party->position.z, x, z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (marioKeyOffChk()) {
        {
            f32 t = partyGetFollowDir(party);
            t += 180.0f;
            party->homeDir = revise360(t);
        }
    }
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        y = mario->position.y;
    } else {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        other = anotherPartyGetPtr(party->currentSlotId);
        if (other) {
            x = other->position.x;
            z = other->position.z;
            y = other->position.y;
        } else {
            x = mario->position.x;
            z = mario->position.z;
            y = mario->position.y;
        }
    }
    movePos(&x, &z, sp, party->homeDir);
    angleABf(party->position.x, party->position.z, x, z);
    partyGetGndYTo(&gy, x, y, z);
    if (gy <= -2000.0f) {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        movePos(&x, &z, sp, toMovedir(mario->displayDirection));
    }
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    sp = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (sp >= thr) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        spd = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (spd > 2.0f) {
            spd = 2.0f;
        }
        if (spd < 1.0f) {
            spd = 1.0f;
        }
        party->moveSpeed = spd;
        partyMoveCheckWall(party);
        partyMoveAnime(party, party->moveSpeed);
        hit = _partySearchGround(party, &gy, &sp, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        }
        party->position.y = gy;
    } else {
        party->moveFrames = 0;
        if (mario->baseSpeed == 0.0f) {
            party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
            partyChgMoveMode(party, 1);
            partyChgMot(party, 0);
            partySetDir(party, mario->position.x, mario->position.z);
            party->homingDist = 50.0f;
            party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        }
    }
    if (party->hitobjPush) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, x, z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
    }
}

/**
 * Demos: the flying partner's behind-Mario motion (move modes 2 and 6):
 * floats to the spot behind Mario, then returns to normal following facing him.
 */
void party_motion_behind_mario_fly(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* other;
    HitEntry* hit;
    f32 thr;
    f32 r;
    f32 ty;
    f32 spd;
    f32 d;
    Vec v;
    f32 x, z;
    f32 sp, dir;
    f32 gy, depth;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET)) {
            f32 t;
            if (!(party->trigFlags & PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET)) {
                t = partyGetFollowDir(party);
                t += 180.0f;
                t = revise360(t);
            } else {
                party->trigFlags &= ~PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET;
                t = revise360(180.0f + angleABf(mario->position.x, mario->position.z, party->moveTarget.x, party->moveTarget.z));
            }
            party->homeDir = t;
        }
        r = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, r, party->homeDir);
        party->moveFrames = distABf(party->position.x, party->position.z, x, z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET) && marioKeyOffChk()) {
        f32 t2 = partyGetFollowDir(party);
        t2 += 180.0f;
        party->homeDir = revise360(t2);
    }
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        r = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        ty = mario->position.y;
        movePos(&x, &z, r, party->homeDir);
    } else {
        r = 1.5f * mario->wPlayerCollisionBox.x;
        other = anotherPartyGetPtr(party->currentSlotId);
        if (other) {
            x = other->position.x;
            z = other->position.z;
            ty = other->position.y;
        } else {
            x = mario->position.x;
            z = mario->position.z;
            ty = mario->position.y;
        }
    }
    movePos(&x, &z, r, party->homeDir);
    angleABf(party->position.x, party->position.z, x, z);
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    d = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (d >= thr && party->moveFrames > 0) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        spd = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET)) {
            if (spd > 2.0f) {
                spd = 2.0f;
            }
            if (spd < 1.0f) {
                spd = 1.0f;
            }
        } else {
            if (spd > 4.0f) {
                spd = 4.0f;
            }
            if (spd < 2.0f) {
                spd = 2.0f;
            }
        }
        party->moveSpeed = spd;
        v = party->position;
        partyGetMoveDirSpd(party, &dir, &sp);
        hit = partySearchFrontWall(party, &v, sp, dir);
        if (hit) {
            party->hitobjFront = hit;
            if (party->moveSpeed) {
                party->hitobjPush = hit;
            }
        }
        party->position.x = v.x;
        party->position.z = v.z;
        party->position.y += 0.05f * (ty - party->position.y);
        partyMoveAnime(party, party->moveSpeed);
    } else {
        party->moveFrames = 0;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
        party->trigFlags &= ~PARTY_TRIG_FLAG_HOME_DIR_SET;
        party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
    if (party->hitobjPush) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
    hit = _partySearchGround(party, &gy, &depth, 100.0f, 100.0f);
    if (hit) {
        if (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        if (depth > party->height) {
            hit = NULL;
        }
        party->position.y += 0.05f * (gy - party->position.y);
    }
    party->hitobjStandOn = hit;
}

/**
 * Demos: move mode 3 (partyMoveBesideMario): walks the partner to the spot at Mario's side (90 degrees from his
 * facing), then returns to normal following.
 */
void party_motion_beside_mario(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    f32 x, z;
    f32 sp;
    f32 y;
    f32 my;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 thr;
    f32 t;
    f32 spd;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        t = partyGetFollowDir(party);
        t += 90.0f;
        party->homeDir = revise360(t);
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, party->homeDir);
        party->moveFrames = distABf(party->position.x, party->position.z, x, z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (marioKeyOffChk()) {
        t = partyGetFollowDir(party);
        t += 90.0f;
        party->homeDir = revise360(t);
    }
    sp = 1.5f * mario->wPlayerCollisionBox.x;
    x = mario->position.x;
    z = mario->position.z;
    my = mario->position.y;
    movePos(&x, &z, sp, party->homeDir);
    angleABf(party->position.x, party->position.z, x, z);
    partyGetGndYTo(&y, x, my, z);
    if (y <= -2000.0f) {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, toMovedir(mario->displayDirection));
    }
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    sp = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (sp >= thr && party->moveFrames > 0) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        spd = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (spd > 2.0f) {
            spd = 2.0f;
        }
        if (spd < 1.0f) {
            spd = 1.0f;
        }
        party->moveSpeed = spd;
        partyMoveCheckWall(party);
        partyMoveAnime(party, party->moveSpeed);
        hit = _partySearchGround(party, &y, &sp, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        }
        party->position.y = y;
    } else {
        party->moveFrames = 0;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
    }
    if (party->hitobjPush) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
    }
}

static void partyStayFlyY(PartyEntry* party);
static void partyStayChkGnd(PartyEntry* party);

/**
 * Demos: the standing motion (motion 0 of the stay and walk modes):
 * clears the footmarks on entry, runs the slit and roll states,
 * starts following (motion 1) once Mario gets far enough away,
 * and keeps the partner on the floor or at flying height.
 * Ms. Mowz plays her sniffing pose when chuchu_searchObject finds something.
 */
void party_motion_stay(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 id;
    PartyEntry* other;
    HitEntry* hit;
    f32 lim;
    f32 d;
    Vec v;
    Vec p;
    f32 x, z;
    f32 dir, spd;

    id = partyGetFootmarkId(party);
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        partyChgPoseId(party, 1);
        partyClearFootmark();
        party->yoshiPsndSFXId = -1;
    }
    if (mario->currMotionId != MARIO_MOTION_TALK && (party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    lim = party->homingDist;
    if (mario->characterId == 2) {
        lim = 70.0f;
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12")) {
        if (!marioKeyOffChk()) {
            lim = 24.0f;
            party->trigFlags |= PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        }
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
        lim = 24.0f;
    }
    party_slit(party);
    party_roll(party);
    if (party->runMode != 0) {
        if (marioChkDeepSleep() == 1 || (party->flags & PARTY_FLAG_SLEEP_ON)) {
            partyChgPoseId(party, 6);
        } else if (party->currentMemberId != PARTY_MEMBER_MS_MOWZ) {
            partyChgPoseId(party, 1);
        } else if (!chuchu_searchObject()) {
            partyChgPoseId(party, 1);
        }
    }
    if (mario->currMotionId == MARIO_MOTION_TALK && !(party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (party->runMode != 0) {
        if (!party->currentSlotId || !partyGetPtr(marioGetPartyId())) {
            if (partyChkMarioFollowYDemo(party->playerPtr)) {
                if (party->moveKind == 0) {
                    p = party->position;
                    d = partyGetTargetDist3D(id, &p);
                } else {
                    x = party->position.x;
                    z = party->position.z;
                    movePos(&x, &z, 0.5f * party->width,
                            angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z));
                    d = distABf(x, z, mario->position.x, mario->position.z);
                }
                if (marioChkSlitThrouh() || d >= lim) {
                    partyChgMot(party, 1);
                }
            }
        } else {
            other = anotherPartyGetPtr(party->currentSlotId);
            if (other) {
                if (nokonokoGetStatus(other) == 3) {
                    if (partyGetTargetDist(id, party->position.x, party->position.z) >= lim) {
                        partyChgMot(party, 1);
                        partyClearFootmark2();
                    }
                    // 3 = PARTY_MEMBER_BOBBERY, 4 = PARTY_MEMBER_YOSHI: the char-sized enum constants change the s8 compares
                } else if (other->currentMemberId == 3 && other->runMode == 3) {
                    if (mario->currMotionId != MARIO_MOTION_DAMAGE && mario->currMotionId != MARIO_MOTION_HIP && mario->currMotionId != MARIO_MOTION_HIP_2 &&
                        distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) >= lim) {
                        partyChgMot(party, 1);
                    }
                } else if (!(other->flags & PARTY_FLAG_IS_BEING_USED) || other->currentMemberId == 4) {
                    if (distABf(party->position.x, party->position.z, other->position.x, other->position.z) >= lim) {
                        partyChgMot(party, 1);
                    }
                }
                // d is only set in the branch above: on this path the demo compares an uninitialised value (the demo's own bug)
                if (marioChkSlitThrouh() || d >= lim) {
                    partyChgMot(party, 1);
                }
            }
        }
    }
    v = party->position;
    party->moveSpeed = 0.0f;
    partyGetMoveDirSpd(party, &dir, &spd);
    hit = partySearchFrontWall(party, &v, spd, dir);
    if (hit) {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    partyGetMoveDirSpd(party, &dir, &spd);
    marioChkWallAround(&v, spd, dir, party->width, party->height);
    party->position.x = v.x;
    party->position.z = v.z;
    if (party->moveKind == 1) {
        partyStayFlyY(party);
        return;
    }
    partyStayChkGnd(party);
    party_force_reset_outofscreen(party);
    if (!(party->flags2 & PARTY_DISP_FLAG_FAMICOM) && !marioKeyOffChk() && marioChkDeepSleep() != 1 && party->currentMemberId == PARTY_MEMBER_MS_MOWZ &&
        chuchu_searchObject()) {
        switch (party->useMotionId) {
            case 1:
                if (--party->moveFrames > 0) {
                    break;
                }
                partyChgPoseId(party, 1);
                party->moveFrames = 30;
                party->useMotionId = 2;
                break;
            case 2:
                if (--party->moveFrames > 0) {
                    break;
                }
                party->useMotionId = 0;
                break;
            case 0:
            default:
                partyChgPose(party, "PCH_A2_1");
                party->useMotionId = 1;
                party->moveFrames = 30;
                break;
        }
    }
}

/** Stay helpers: inlined into party_motion_stay; the linker drops the out-of-line copies. */
static void partyStayFlyY(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 depth, gy;

    if (party->flags & PARTY_FLAG_DISABLE_FLOORS) {
        return;
    }
    if (_partySearchGround(party, &gy, &depth, 10.0f, 0.0f)) {
        party->position.y = 1.0f + gy;
    } else {
        party->position.y += 0.1f * ((10.0f + mario->position.y) - party->position.y);
    }
}

/**
 * Demos: head and floor probe for a standing partner:
 * snaps it to the floor, flags shallow water and damage floors,
 * and starts a fall (motion 3, gravity -1.5) or a water splash when there is no floor.
 */
static void partyStayChkGnd(PartyEntry* party) {
    HitEntry* hit;
    f32 depth2;
    f32 hh;
    Vec g2;
    Vec hp;

    hp = party->position;
    hh = party->height;
    hit = ((PartySearchHeadRetVoidptrFn)partySearchHead)(party, &hp, &hh, party->displayDirection);
    if (hit) {
        party->hitobjHead = hit;
    }
    if (!(party->flags & PARTY_FLAG_DISABLE_FLOORS)) {
        party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        hit = _partySearchGround(party, &g2.y, &depth2, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        party->hitobjStandOn = hit;
        if (!hit) {
            party->flags &= ~PARTY_FLAG_IS_GROUNDED;
            partyChgMot(party, 3);
            party->gravity = -1.5f;
        } else {
            party->flags |= PARTY_FLAG_IS_GROUNDED;
            if (hitGetAttr(hit) & HIT_ATTR_SHALLOW_WATER) {
                party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
            } else {
                party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
            }
            if (hitGetAttr(hit) & HIT_ATTR_DAMAGE_RETURN) {
                party->damageHit = hit;
            }
        }
        party->position.y = g2.y;
    }
}

/**
 * Demos: motion 7, the partner knocked away: it flies up off the top of the screen,
 * waits until Mario's damage motion is over, drops in from 200 above partyGetReturnPos and,
 * 30 frames after landing, returns to normal (run mode 2, move mode 0).
 */
void party_motion_damage(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 x, y, z;
    Vec ret;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->motionStep = 0;
    }
    switch (party->motionStep) {
        case 0:
            partyChgPoseId(party, 9);
            party->velY = 15.0f;
            party->accelY = 0.0f;
            party->moveFrames = 60;
            party->motionStep = 1;
        case 1:
            party->position.y += party->velY;
            marioGetScreenPos(party->position, &x, &y, &z);
            if (y <= -300.0f) {
                party->moveFrames = 20;
                party->motionStep = 10;
            }
            break;
        case 10:
            if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE) {
                break;
            }
            if (--party->moveFrames <= 0) {
                partyGetReturnPos(&ret);
                party->position.x = ret.x;
                party->position.y = 200.0f + ret.y;
                party->position.z = ret.z;
                party->velY = 0.0f;
                party->accelY = -1.0f;
                party->moveSpeed = 0.0f;
                party->flags |= PARTY_FLAG_IS_FALLING;
                party->flags |= PARTY_FLAG_FORCE_FALL;
                party->motionStep = 11;
            }
            break;
        case 11:
            marioGetScreenPos(party->position, &x, &y, &z);
            if (y > 240.0f) {
                party->flags &= ~PARTY_FLAG_FORCE_FALL;
            }
            partyMove(party);
            if (party->velY <= -6.0f) {
                party->accelY = 0.0f;
                party->velY = -6.0f;
            }
            if (party->position.y < -2000.0f) {
                party->position = mario->position;
                party->position.y += 200.0f;
                party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
            }
            if (party->hitobjStandOn && !((hitGetAttr(party->hitobjStandOn) >> 9) & 1)) {
                party->motionStep = 12;
                party->moveFrames = 30;
            }
            break;
        case 12:
            if (--party->moveFrames <= 0) {
                partyChgRunMode(party, 2);
                party->moveMode = 0;
                party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
            }
            break;
    }
}

/** Demos: Mario entered Paper Mode: both partners turn sideways too (slitOn 1, set up by party_slit). */
void allPartySlitOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
        party->slitOn = 1;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
        party->slitOn = 1;
    }
}

/**
 * Mario left Paper Mode: both partners still in it start their turn-back animation (slitStep 40).
 * Called from mot_slit.c.
 */
void allPartySlitOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && (party->flags & PARTY_FLAG_PAPER_MODE) && party->slitStep < 0x28) {
        party->slitStep = 0x28;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && (party->flags & PARTY_FLAG_PAPER_MODE) && party->slitStep < 0x28) {
        party->slitStep = 0x28;
    }
}

/**
 * Demos: ends Paper Mode on this partner at once, facing left or right from its direction, and resets its pose.
 */
static inline void partyForceSlitOff(PartyEntry* party) {
    party->displayDirection = revise360(party->targetDir - party->camDir) >= 180.0f ? 0.0f : 180.0f;
    party->displayDirectionTarget = party->displayDirection;
    party->moveDir = revise360(270.0f - party->displayDirection);
    party->targetDir = party->moveDir;
    party->flags2 &= ~(PARTY_DISP_FLAG_HALF_TURN_MIRRORED | PARTY_DISP_FLAG_HALF_TURN | PARTY_DISP_FLAG_SLIT | PARTY_DISP_FLAG_SLIT_FLIP);
    partyPaperOff(party);
    party->flags &= ~(PARTY_FLAG_PAPER_MODE | PARTY_FLAG_MOT_SLIT_FLOOR);
    party->slitOn = 0;
    partyChgPoseId(party, 1);
}

/**
 * Ends Paper Mode at once on both partners; used when Mario's own Paper Mode is cut short (mot_slit.c)
 * and by the all_party_slit_off script helper.
 */
void allPartyForceSlitOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        partyForceSlitOff(party);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        partyForceSlitOff(party);
    }
}

/**
 * Demos: the partner reached a Paper Mode floor grate in Mario's footmarks:
 * enters Paper Mode and marks it to slip through the floor (party_slit's fall steps).
 */
void partyChgMotSlitFloor(PartyEntry* party) {
    if (party->flags & PARTY_FLAG_MOT_SLIT_FLOOR) {
        return;
    }
    party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
    party->slitOn = 1;
    party->flags |= PARTY_FLAG_MOT_SLIT_FLOOR;
}

/**
 * Demos: per-frame Paper Mode state for a partner while slitOn is 1:
 * turns sideways ("p_slit" paper animation), walks sideways, slips down through floor grates,
 * and turns back when Mario leaves Paper Mode and no slit wall is in the way.
 * Returns FALSE on the frame the turn completes, so the motion skips it.
 */
static BOOL party_slit(PartyEntry* party) {
    BOOL ret = TRUE;
    MarioWork* mario;
    f32 a;

    mario = party->playerPtr;
    if (party->slitOn != 1) {
        return TRUE;
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_SLIT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_SLIT;
        party->flags2 |= PARTY_DISP_FLAG_SLIT;
        partyPaperOn(party, "p_slit");
        partyChgPaper(party, "PM_S_1A");
        party->moveFrames = 30;
        party->moveSpeed = 0.0f;
        if (revise360(party->targetDir - mario->targetYaw) <= 180.0f) {
            party->flags2 &= ~PARTY_DISP_FLAG_SLIT_FLIP;
            party->slitStep = 0;
        } else {
            party->flags2 |= PARTY_DISP_FLAG_SLIT_FLIP;
            party->slitStep = 2;
        }
    }
    switch (party->slitStep) {
        case 0:
            if (--party->moveFrames < 0) {
                party->flags |= PARTY_FLAG_PAPER_MODE;
                party->displayDirection = 270.0f;
                party->displayDirectionTarget = party->displayDirection;
                partyChgPaper(party, "PM_S_1B");
                if (!(party->flags & PARTY_FLAG_MOT_SLIT_FLOOR)) {
                    party->slitStep = 10;
                    ret = FALSE;
                } else {
                    party->slitStep = 20;
                }
            }
            break;
        case 2:
            if (--party->moveFrames < 0) {
                party->flags |= PARTY_FLAG_PAPER_MODE;
                party->displayDirection = 270.0f;
                party->displayDirectionTarget = party->displayDirection;
                partyChgPaper(party, "PM_S_1B");
                if (!(party->flags & PARTY_FLAG_MOT_SLIT_FLOOR)) {
                    party->slitStep = 10;
                    ret = FALSE;
                } else {
                    party->slitStep = 20;
                }
            }
            break;
        case 10:
            if (!party->moveSpeed) {
                partyChgPaper(party, "PM_S_1B");
                party->displayDirection = 270.0f;
            } else {
                if (revise360(party->targetDir - mario->targetYaw) >= 180.0) {
                    party->flags2 |= PARTY_DISP_FLAG_SLIT_FLIP;
                } else {
                    party->flags2 &= ~PARTY_DISP_FLAG_SLIT_FLIP;
                }
                party->displayDirection = (party->flags2 & PARTY_DISP_FLAG_SLIT_FLIP) ? 280.0f : 260.0f;
                a = revise360(party->targetDir - mario->targetYaw);
                if (a >= 315.0f || a <= 45.0f || (a >= 135.0f && a <= 225.0f)) {
                    partyChgPaper(party, "PM_S_1E");
                } else {
                    partyChgPaper(party, "PM_S_1D");
                }
            }
            if (!(mario->flags & MARIO_FLAG_PAPER_MODE) && !(hitGetAttr(party->hitobjFront) & HIT_ATTR_PAPER_SLIT) &&
                !(hitGetAttr(party->hitobjPush) & HIT_ATTR_PAPER_SLIT)) {
                party->slitStep = 40;
            }
            break;
    }
    switch (party->slitStep) {
        case 20:
            partyChgPaper(party, "PM_S_1H");
            party->flags |= PARTY_FLAG_FORCE_FALL;
            party->flags |= PARTY_FLAG_IS_FALLING;
            party->moveFrames = 20;
            party->moveSpeed = 0.0f;
            party->slitStep = 21;
            break;
        case 21:
            party->displayDirection = revise360(party->targetDir - party->camDir) <= 180.0f ? 260.0f : 280.0f;
            party->position.y += -3.0f;
            if (--party->moveFrames <= 0) {
                party->slitStep = 22;
            }
            break;
        case 22:
            party->slitStep = 10;
            party->flags &= ~PARTY_FLAG_FORCE_FALL;
            marioClearSlitFloor();
            break;
    }
    switch (party->slitStep) {
        case 40:
            partyChgPaper(party, "PM_S_1C");
            party->moveFrames = 30;
            party->slitStep = 41;
            party->displayDirection = revise360(party->targetDir - mario->targetYaw) >= 180.0f ? 0.0f : 180.0f;
            party->displayDirectionTarget = party->displayDirection;
        case 41:
            if (--party->moveFrames <= 0) {
                party->slitStep = 42;
            }
            break;
        case 42:
            party->flags2 &= ~(PARTY_DISP_FLAG_HALF_TURN_MIRRORED | PARTY_DISP_FLAG_HALF_TURN | PARTY_DISP_FLAG_SLIT | PARTY_DISP_FLAG_SLIT_FLIP);
            partyPaperOff(party);
            party->flags &= ~(PARTY_FLAG_PAPER_MODE | PARTY_FLAG_MOT_SLIT_FLOOR);
            party->slitOn = 0;
            break;
    }
    return ret;
}

/**
 * A roll state like Mario's tube mode ("p_roll" paper animation, PM_R_1A/1B) for slitOn 2,
 * spinning with speed and ending at slitStep 100; returns FALSE while ending.
 * Nothing in the tree sets slitOn to 2, so as built it returns TRUE at once.
 * Guess: an unused partner tube mode.
 */
static BOOL party_roll(PartyEntry* party) {
    BOOL ret = TRUE;
    f32 d;
    f32 x;
    f32 t;

    if (party->slitOn != 2) {
        return TRUE;
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_SLIT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_SLIT;
        partyPaperOn(party, "p_roll");
        partyChgPaper(party, "PM_R_1A");
        partyChgPoseId(party, 0);
        party->rotOfs.x = -6.0f;
        party->rotOfs.y = 6.0f;
        party->dispOfs.x = 6.0f;
        party->dispOfs.y = 2.0f;
        party->moveFrames = 0x41;
        party->slitStep = 0;
        party->moveSpeed = 0.0f;
    }
    switch (party->slitStep) {
        case 0:
            party->moveFrames--;
            if (party->moveFrames <= 0) {
                partyChgPaper(party, "PM_R_1B");
                party->slitStep = 10;
            }
            break;
        case 10:
            party->displayDirection = revise360(270.0f - party->targetDir);
            if (revise360(party->moveDir + party->displayDirection) > 180.0f) {
                party->rotation = revise360(7.0f * party->moveSpeed + party->rotation);
            } else {
                party->rotation = revise360(party->rotation - 7.0f * party->moveSpeed);
            }
            break;
    }
    switch (party->slitStep) {
        case 100:
            party->moveSpeed = 0.0f;
            party->rot.x = 0.0f;
            party->rotation = 0.0f;
            party->rotOfs.x = 0.0f;
            party->rotOfs.y = 0.0f;
            party->dispOfs.x = party->targetDir < 180.0f ? 3.0f : -3.0f;
            party->dispOfs.y = 0.0f;
            party->moveFrames = 0x41;
            party->slitStep = 101;
            partyChgPaper(party, "PM_R_1C");
            partyPaperLightOff(party);
        case 101:
            ret = FALSE;
            party->moveFrames--;
            if (party->moveFrames > 0) {
                if (party->targetDir < 180.0f) {
                    x = 0.1f * (90.0f - party->displayDirection);
                    x += party->displayDirection;
                    if (__fabsf(90.0f - x < 1.0f)) {
                        x = 90.0f;
                    }
                    party->displayDirection = x;
                    party->displayDirectionTarget = x;
                } else {
                    x = 0.1f * (270.0f - party->displayDirection);
                    x += party->displayDirection;
                    if (__fabsf(270.0f - x < 1.0f)) {
                        x = 270.0f;
                    }
                    party->displayDirection = x;
                    party->displayDirectionTarget = x;
                }
            } else {
                ret = TRUE;
                if (party->targetDir >= 180.0f) {
                    party->displayDirection = 0.0f;
                    party->displayDirectionTarget = 0.0f;
                    party->moveDir = 270.0f;
                    party->targetDir = 270.0f;
                } else {
                    party->displayDirection = 180.0f;
                    party->displayDirectionTarget = 180.0f;
                    party->moveDir = 90.0f;
                    party->targetDir = 90.0f;
                }
                party->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
                party->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
                party->slitOn = 0;
                party->flags &= ~PARTY_FLAG_PAPER_MODE;
                party->flags2 &= ~PARTY_DISP_FLAG_SLIT;
                party->flags &= ~PARTY_FLAG_POSE_TILTED;
                party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
                party->flags2 &= ~PARTY_DISP_FLAG_NO_MIRROR;
                party->slitStep = 100;
                partyPaperOff(party);
            }
            break;
    }
    return ret;
}
#else
/** Resets the height above a point that the floor probes start from to 60; partyReInit calls it on map load. */
void partyResetGndProbeDy(void) {
    gnd_probe_dy = 60.0f;
}

/**
 * Makes the partner follow at close distance and keep up with Mario's speed;
 * evt_mario door and pipe moves turn it on while Mario walks through.
 */
void N_partyFollowCloseOn(PartyEntry* party) {
    party->trigFlags |= PARTY_TRIG_FLAG_FOLLOW_CLOSE;
}

/** Back to normal follow distance after a door or pipe move (evt_mario). */
void N_partyFollowCloseOff(PartyEntry* party) {
    party->trigFlags &= ~PARTY_TRIG_FLAG_FOLLOW_CLOSE;
}

/**
 * Floor under the partner for the behind-Mario walks;
 * water (attribute 0x200) counts as no floor and starts a splash.
 */
static inline HitEntry* partyBehindGround(PartyEntry* party) {
    HitEntry* hit = _partySearchGround(party, 10.0f, 0.0f);
    if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
        hit = NULL;
        if (!party->splashTimer) {
            party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
            party->flags |= PARTY_FLAG_FORCE_FALL;
        }
    }
    return hit;
}

static f32 partyStayDist(PartyEntry* party);
static u32 partyGetFrontAttr(PartyEntry* party, f32 dir);
static f32 partyHomingOff(PartyEntry* party);
static f32 partyGetGndY(f32 x, f32 y, f32 z);
static f32 partyGetDirGndY(Vec u, f32 md);
static u32 partyGetFrontAttrFar(PartyEntry* party);
static void partyGorFix(PartyEntry* party);
static void partyPoseA2(PartyEntry* party);
static s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir);

static void party_force_reset_outofscreen(PartyEntry* party);

/**
 * The standing motion (motion 0 of the stay and walk modes):
 * clears the footmarks on entry unless coming from a jump, runs the slit and roll states,
 * starts following (motion 1) once Mario or the first partner is far enough away,
 * and keeps the partner on the floor or at flying height.
 * On aji_02, aji_05 and aji_12 (X-Naut Fortress) it follows close.
 * Ms. Mowz plays her sniffing pose when chuchu_searchObject finds something.
 */
void party_motion_stay(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 id;
    PartyEntry* other;
    HitEntry* hit;
    f32 lim;
    f32 x, z;
    f32 dir, spd;
    Vec v;
    Vec p;

    id = partyGetFootmarkId(party);
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        partyChgPoseId(party, 1);
        if (!(party->trigFlags & PARTY_TRIG_FLAG_KEEP_FOOTMARKS)) {
            if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
                partyClearFootmark();
            } else {
                partyClearFootmark2();
            }
        }
        party->trigFlags &= ~PARTY_TRIG_FLAG_KEEP_FOOTMARKS;
        party->yoshiPsndSFXId = -1;
        partyForceSetSpd(party, 0.0f);
    }
    if (mario->currMotionId != MARIO_MOTION_TALK && (party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    lim = party->homingDist;
    if (!mario->controlStickSensitivity && mario->baseSpeed < 1.0f) {
        lim = 100.0f;
    }
    if ((s8)mario->characterId == 2) {
        lim = 70.0f;
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12")) {
        if (!marioKeyOffChk()) {
            {
                f32 sd;
                if (party->moveKind == 0) {
                    sd = 18.0f;
                } else if (party->currentMemberId == PARTY_MEMBER_FLURRIE) {
                    if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
                        sd = 8.0f;
                    } else {
                        sd = 30.0f;
                    }
                } else if (party->currentMemberId == PARTY_MEMBER_VIVIAN) {
                    if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
                        sd = 8.0f;
                    } else {
                        sd = 30.0f;
                    }
                }
                lim = sd;
            }
            party->trigFlags |= PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        }
    }
    if ((party->trigFlags >> 17) & 1) {
        {
            f32 sd;
            if (party->moveKind == 0) {
                sd = 18.0f;
            } else if (party->currentMemberId == PARTY_MEMBER_FLURRIE) {
                if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
                    sd = 8.0f;
                } else {
                    sd = 30.0f;
                }
            } else if (party->currentMemberId == PARTY_MEMBER_VIVIAN) {
                if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
                    sd = 8.0f;
                } else {
                    sd = 30.0f;
                }
            }
            lim = sd;
        }
    }
    party_slit(party);
    party_roll(party);
    partyChgStayPose(party);
    if (mario->currMotionId == MARIO_MOTION_TALK && !(party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (party->runMode != 0) {
        if (!party->currentSlotId || !partyGetPtr(marioGetPartyId())) {
            if (partyChkMarioFollowY(party->playerPtr)) {
                f32 d;
                if (party->moveKind == 0) {
                    p = party->position;
                    d = partyGetTargetDist3D(id, &p);
                    partyGetTargetDist(id, party->position.x, party->position.z);
                } else {
                    x = party->position.x;
                    z = party->position.z;
                    movePos(&x, &z, 0.5f * party->width,
                            angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z));
                    d = distABf(x, z, mario->position.x, mario->position.z);
                }
                if (marioChkSlitThrouh() || d >= lim) {
                    if (!marioChkDeepSleep()) {
                        partyChgMot(party, 1);
                    }
                }
            }
        } else {
            other = anotherPartyGetPtr(party->currentSlotId);
            if (other) {
                if (nokonokoGetStatus(other) == 3 || PSVECDistance(&mario->position, &other->position) >= 150.0f) {
                    if (partyGetTargetDist(id, party->position.x, party->position.z) >= lim) {
                        partyChgMot(party, 1);
                        partyClearFootmark2();
                    }
                    // 3 = PARTY_MEMBER_BOBBERY, 4 = PARTY_MEMBER_YOSHI: the char-sized enum constants change the s8 compares
                } else if (other->currentMemberId == 3 && other->runMode == 3) {
                    if (mario->currMotionId != MARIO_MOTION_DAMAGE && mario->currMotionId != MARIO_MOTION_HIP && mario->currMotionId != MARIO_MOTION_HIP_2 &&
                        distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) >= lim) {
                        partyChgMot(party, 1);
                    }
                } else if (!(other->flags & PARTY_FLAG_IS_BEING_USED) || other->currentMemberId == 4) {
                    if (distABf(party->position.x, party->position.z, other->position.x, other->position.z) >= lim) {
                        partyChgMot(party, 1);
                    }
                }
                if (marioChkSlitThrouh()) {
                    partyChgMot(party, 1);
                }
            }
        }
    }
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &spd);
    hit = partySearchFrontWall(party, &v, spd, dir);
    if (hit) {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    partyGetMoveDirSpd(party, &dir, &spd);
#if VERSION >= VERSION_US
    partyChkWallAround(party, &v, spd, dir, party->width, party->height);
#else
    marioChkWallAround(&v, 1, spd, dir, party->width, party->height);
#endif
    party->position.x = v.x;
    party->position.z = v.z;
    if (party->moveKind == 1) {
        partyFlyAdjustY(party);
        return;
    }
    partyWalkChkGnd(party);
    party_force_reset_outofscreen(party);
    if (party->currentMemberId == PARTY_MEMBER_MS_MOWZ && !(party->flags2 & PARTY_DISP_FLAG_FAMICOM) && !marioKeyOffChk() && marioChkDeepSleep() != 1 &&
        chuchu_searchObject()) {
        switch (party->useMotionId) {
            case 1:
                if (--party->moveFrames > 0) {
                    break;
                }
                partyChgPoseId(party, 1);
                party->moveFrames = 30;
                party->useMotionId = 2;
                break;
            case 2:
                if (--party->moveFrames > 0) {
                    break;
                }
                party->useMotionId = 0;
                break;
            case 0:
            default:
                partyPoseA2(party);
                break;
        }
    }
}

/**
 * Motion 0 of the wait move mode: stands, clears the footmarks on entry
 * and goes back to run mode 2 once Mario is over 31 units away;
 * otherwise the same floor, talk and Ms. Mowz handling as party_motion_stay.
 */
void party_motion_wait(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        partyChgPoseId(party, 1);
        if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
            partyClearFootmark();
        } else {
            partyClearFootmark2();
        }
        party->yoshiPsndSFXId = -1;
    }
    party_slit(party);
    party_roll(party);
    partyChgStayPose(party);
    if (!(party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK)) {
        partyChkWall(party);
    }
    partyChkGnd(party);
    if (distABf(party->position.x, party->position.z, mario->position.x, mario->position.z) > 31.0f) {
        partyChgRunMode(party, 2);
    }
    if (mario->currMotionId == MARIO_MOTION_TALK && !(party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        partyMoveBehindMario(party, 0);
    } else if (party->moveKind == 1) {
        partyFlyAdjustY(party);
    } else {
        partyWalkChkGnd(party);
        if (party->currentMemberId == PARTY_MEMBER_MS_MOWZ && !(party->flags2 & PARTY_DISP_FLAG_FAMICOM) && !marioKeyOffChk() &&
            marioChkDeepSleep() != 1 && chuchu_searchObject()) {
            switch (party->useMotionId) {
                case 1:
                    if (--party->moveFrames <= 0) {
                        partyChgPoseId(party, 1);
                        party->moveFrames = 30;
                        party->useMotionId = 2;
                    }
                    break;
                case 2:
                    if (--party->moveFrames <= 0) {
                        party->useMotionId = 0;
                    }
                    break;
                case 0:
                default:
                    partyPoseA2(party);
                    break;
            }
        }
    }
}

/**
 * Head and floor probe for a walking partner: snaps it to the floor, flags shallow water and damage floors,
 * falls (motion 3) or splashes when there is none, and jumps off objects that cannot be stood on.
 */
void partyWalkChkGnd(PartyEntry* party) {
    Vec pos;
    f32 height;
    void* head;
    HitEntry* hit;
    s32 attr;

    pos = party->position;
    height = party->height;
    head = ((PartySearchHeadRetVoidptrFn)partySearchHead)(party, &pos, &height, party->displayDirection);
    if (head) {
        party->hitobjHead = head;
    }
    if (party->flags & PARTY_FLAG_DISABLE_FLOORS) {
        return;
    }
    party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
    hit = _partySearchGround(party, 15.0f, -15.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_DEEP_WATER) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
    }
    party->hitobjStandOn = hit;
    if (!hit) {
        party->flags &= ~PARTY_FLAG_IS_GROUNDED;
        partyChgMot(party, 3);
        party->gravity = -1.5f;
        return;
    }
    party->position.y = party->groundY;
    party->flags |= PARTY_FLAG_IS_GROUNDED;
    if (attr & HIT_ATTR_SHALLOW_WATER) {
        party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
    } else {
        party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
    }
    if (attr & HIT_ATTR_DAMAGE_RETURN) {
        party->damageHit = hit;
    }
    if (partyChkNoStandMobj(hit)) {
        partyGetAppearPos5(party, hit, &party->moveTarget);
        party->trigFlags |= PARTY_TRIG_FLAG_JUMP_OFF_MOBJ;
        party->moveTarget.y = party->position.y;
        partyChgMot(party, 2);
    }
}

/**
 * FALSE while the partner should not follow Mario:
 * he is in the air without moving, or in a damage or Spin Jump motion.
 */
static inline BOOL partyChkMarioFollowY(MarioWork* mario) {
    if (mario->airTimer != 0 && mario->baseSpeed == 0.0f) {
        return FALSE;
    }
    if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE || mario->currMotionId == MARIO_MOTION_HIP ||
        mario->currMotionId == MARIO_MOTION_HIP_2) {
        return FALSE;
    }
    return TRUE;
}

#if VERSION >= VERSION_US
/**
 * US: eases a flying partner's height toward target + 5 (+1 in 8-bit mode) by rate per frame,
 * unless it is already up to 5 above it.
 */
static inline void partyFlyMoveY(PartyEntry* party, f32 target, f32 rate) {
    f32 add;
    f32 diff;

    add = 5.0f;
    if (party->flags2 & PARTY_DISP_FLAG_FAMICOM) {
        add = 1.0f;
    }
    diff = target + add - party->position.y;
    if (-5.0f > diff || diff >= 0.0f) {
        party->position.y += diff * rate;
    }
}

/** US: on las_10 the flying partner is pushed down out of low ceilings */
static inline void partyFlyHeadCheck(PartyEntry* party) {
    Vec pos;
    f32 height;
    void* head;
    f32 diff;
    f32 rate;

    if (!strcmp(gp->currentMapName, "las_10")) {
        pos = party->position;
        height = party->height;
        head = ((PartySearchHeadRetVoidptrFn)partySearchHead)(party, &pos, &height, party->displayDirection);
        if (head) {
            party->hitobjHead = head;
            diff = pos.y - party->height - party->position.y;
            if (-5.0f > diff || diff >= 0.0f) {
                rate = 0.1f;
                party->position.y += diff * rate;
            }
        }
    }
}

/**
 * US: keeps a flying partner at Mario's height or the floor's,
 * whichever is higher (faster when below the floor), and hands floors with attribute 0x800 to run mode 13.
 * Also pushes it down from las_10's ceilings.
 */
void partyFlyAdjustY(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    s32 attr;
    f32 target;
    f32 rate;

    if (party->flags & PARTY_FLAG_DISABLE_FLOORS) {
        return;
    }
    partyFlyHeadCheck(party);
    hit = _partySearchGround(party, 10.0f, 0.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_SPIKES) {
            partyChgRunMode(party, 0xD);
            return;
        }
        if (attr & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
    }
    if (partyChkMarioFollowY(party->playerPtr)) {
        if (hit) {
            if (mario->position.y > party->groundY) {
                target = mario->position.y;
                rate = 0.1f;
            } else {
                target = party->groundY;
                rate = 0.1f;
            }
            if (party->position.y < party->groundY) {
                target = party->groundY;
                rate = 0.2f;
            }
            partyFlyMoveY(party, target, rate);
        } else if (party->dropDepth >= 0.0f) {
            if (mario->position.y > party->groundY) {
                target = mario->position.y;
                rate = 0.1f;
            } else {
                target = party->groundY;
                rate = 0.1f;
            }
            if (party->position.y < party->groundY) {
                target = party->groundY;
                rate = 0.2f;
            }
            partyFlyMoveY(party, target, rate);
        }
    } else {
        f32 t;
        rate = 0.05f;
        if (hit) {
            t = mario->position.y;
            if (t > party->groundY) {
                t = mario->position.y;
            } else {
                t = party->groundY;
            }
            if (party->position.y < party->groundY) {
                t = 18.5f + party->groundY;
                rate = 0.2f;
            }
            partyFlyMoveY(party, t, rate);
        }
    }
}

#else
/**
 * JP: keeps a flying partner at Mario's height or the floor's, whichever is higher,
 * and hands floors with attribute 0x800 to run mode 13.
 */
void partyFlyAdjustY(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    s32 attr;
    f32 target;
    f32 rate;
    f32 diff;
    f32 add;

    if (party->flags & PARTY_FLAG_DISABLE_FLOORS) {
        return;
    }
    hit = _partySearchGround(party, 10.0f, 0.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_SPIKES) {
            partyChgRunMode(party, 0xD);
            return;
        }
        if (attr & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
    }
    if (partyChkMarioFollowY(party->playerPtr)) {
        rate = 0.05f;
        if (hit) {
            if (mario->position.y > party->groundY) {
                target = mario->position.y;
                rate = 0.1f;
            } else {
                target = party->groundY;
                rate = 0.1f;
            }
            if (party->position.y < party->groundY) {
                target = 18.5f + party->groundY;
                rate = 0.1f;
            }
        } else {
            target = mario->position.y;
        }
        add = 5.0f;
        if (party->flags2 & PARTY_DISP_FLAG_FAMICOM) {
            add = 1.0f;
        }
        target += add;
        diff = target - party->position.y;
        if (diff > 5.0f || 0.0f > diff) {
            party->position.y += diff * rate;
        }
    } else {
        if (hit) {
            if (mario->position.y > party->groundY) {
                target = mario->position.y;
            } else {
                target = party->groundY;
            }
            if (party->position.y < party->groundY) {
                target = 18.5f + party->groundY;
            }
        } else {
            target = party->position.y;
        }
        add = 5.0f;
        if (party->flags2 & PARTY_DISP_FLAG_FAMICOM) {
            add = 1.0f;
        }
        target += add;
        diff = target - party->position.y;
        if (diff > 5.0f || 0.0f > diff) {
            rate = 0.05f;
            party->position.y += diff * rate;
        }
    }
}

#endif

/**
 * The walking partner's follow motion (motion 1 of move mode 1):
 * walks along Mario's footmarks at a speed set by its distance, jumps up ledges and at marked jump spots,
 * steps up stairs, falls off edges, enters slits and Paper Mode floor grates, and snaps back on screen.
 * The US release also speeds up to catch up.
 */
void party_motion_homing_walk(PartyEntry* party) {
    HitEntry* hit = NULL;
    s32 id;
    MarioWork* mario;
    PartyEntry* other;
    s32 i;
    PartyFootmark* fm;
    MarioWork* m3;
    u32 attr;
    f32 lim;
    f32 lim2;
    f32 spd;
    f32 px, py, pz;
    f32 d3;
    f32 a;
    f32 gy;
    f32 md;
    Vec v;
    Vec t;
    Vec tp;
    Vec hp;
    Vec p2;
    Vec p3;
    Vec u;
    f32 sp;
    f32 dir;
    f32 s4;
    f32 c4;
    f32 rx, ry, rz;
    f32 fsy, fsa, fsb;
    f32 c, s;
    f32 s2, c2;
    f32 c3, s3;
    f32 hh;
    HitCheckQuery q;
    HitCheckQuery q2;
    HitCheckQuery q3;

    id = partyGetFootmarkId(party);
    mario = party->playerPtr;
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    if (party->forceMoveFrames != 0) {
        lim = 28.0f;
    } else {
        lim = VERSION_PICK(37.5f, 45.0f);
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12")) {
        if (!marioKeyOffChk()) {
            lim = partyStayDist(party);
            party->trigFlags |= PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        }
    }
    if (partyGetTargetMovespd(id)) {
        lim2 = 50.0f;
    } else {
        lim2 = VERSION_PICK(35.0f, 45.0f);
    }
    if ((s32)mario->characterId == 2) {
        lim2 = 70.0f;
    }
    if ((party->trigFlags >> 17) & 1) {
        lim2 = partyStayDist(party);
    }
    if (!party_slit(party)) {
        return;
    }
    if (!party_roll(party)) {
        return;
    }
    if (mario->currMotionId == MARIO_MOTION_TALK && !(party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (!partyChkMarioFollowY(party->playerPtr)) {
        partyChgMot(party, 0);
        return;
    }
    spd = partyGetTargetMovespd2(party);
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        d3 = PSVECDistance(&mario->position, &party->position);
        if (d3 < VERSION_PICK(35.0f, 45.0f)) {
            spd = 1.0f;
        } else if (d3 >= 50.0f) {
            spd = 3.0f;
        }
        if (party->playerPtr->flags & MARIO_FLAG_IS_PUSHING) {
            spd = 1.0f;
            lim = 100.0f;
        }
        partySetTargetSpd(party, spd);
    } else if ((other = partyGetPtr(marioGetPartyId()))) {
        v = other->position;
        if (nokonokoGetStatus(other) == 3 || PSVECDistance(&mario->position, &other->position) >= 150.0f) {
            d3 = PSVECDistance(&mario->position, &party->position);
            if (d3 < VERSION_PICK(35.0f, 45.0f)) {
                spd = 1.0f;
            } else if (d3 >= 50.0f) {
                spd = 3.0f;
            }
            if (party->playerPtr->flags & MARIO_FLAG_IS_PUSHING) {
                spd = 1.0f;
            }
            partySetTargetSpd(party, spd);
        } else {
            d3 = PSVECDistance(&other->position, &party->position);
            if (d3 < VERSION_PICK(35.0f, 45.0f)) {
                spd = 1.0f;
            } else if (d3 >= 50.0f) {
                spd = 3.0f;
            }
            if (party->playerPtr->flags & MARIO_FLAG_IS_PUSHING) {
                spd = 1.0f;
            }
            partySetTargetSpd(party, spd);
        }
    }
    px = party->position.x;
    i = 0;
    py = party->position.y;
    pz = party->position.z;
    do {
        fm = partyGetFootmarkPtr(id);
        t = fm->pos;
        dir = angleABf(px, pz, t.x, t.z);
        attr = partyGetFrontAttr(party, dir);
        if (!(attr & HIT_ATTR_SPIKES)) {
            goto found;
        }
        partyNextReadId(id);
        partyGetReadId2(id, &t);
    } while (++i <= 10);
    t = marioGetPtr()->position;
found:
    p2 = party->position;
    if (partyGetTargetDist3D(id, &p2) >= lim) {
        partySetTargetSpd(party, spd);
    }
    if (lim2 < 20.0f) {
        partySetTargetSpd(party, spd);
    }
    while (TRUE) {
        d3 = distABf(px, pz, t.x, t.z);
        dir = angleABf(px, pz, t.x, t.z);
        if (mario->flags & MARIO_FLAG_IS_PUSHING) {
            a = party->width + mario->wPlayerCollisionBox.x;
        } else {
            a = 0.5f * party->width + party->moveSpeed;
        }
        if (d3 > a) {
            p3 = (Vec){px, py, pz};
            d3 = partyGetTargetDist3D(id, &p3);
            if (d3 >= lim) {
                if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    partyForceSetSpd(party, mario->baseSpeed + a);
                }
#if VERSION >= VERSION_US
                else {
                    // US: catch up with the speed of Mario when far behind
                    a = 0.1f * (d3 - lim);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    partyForceSetSpd(party, mario->baseSpeed + a);
                }
#endif
                break;
            }
            if (marioGetSlitFloorPos(&v)) {
                partySetTargetSpd(party, 1.5f);
                partyNextReadId(id);
                if (marioGetSlitFloorPos(&v)) {
                    t = v;
                    py = distABf(px, pz, t.x, t.z);
                    dir = angleABf(px, pz, t.x, t.z);
                    if (py <= 5.0f) {
                        // FAKE: called through a cast so it stays a call (a direct call is inlined here; see docs/FAKES.md)
                        ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
                    }
                }
                break;
            }
            if (d3 > lim2) {
                if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    partyForceSetSpd(party, mario->baseSpeed + a);
                } else {
                    a = d3 - lim2;
                    if (a >= 1.0f) {
                        a = 1.0f;
                        if (lim2 < 20.0f) {
                            a = spd;
                        }
                    }
                    partySetTargetSpd(party, a);
                }
                break;
            } else if (party->pushVelX == 0.0f && party->pushVelZ == 0.0f) {
                partySetTargetSpd(party, party->playerPtr->baseSpeed);
            } else {
                partyForceSetSpd(party, 0.0f);
                party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
                partyChgPoseId(party, 1);
            }
        }
        if (partyGetFootmarkReadId(id) == (i = partyGetFootmarkWriteId(id))) {
            partySetTargetSpd(party, party->playerPtr->baseSpeed);
            if (party->playerPtr->baseSpeed == 0.0f || party->pushVelX != 0.0f || party->pushVelZ != 0.0f) {
                dir = party->targetDir;
                partySetTargetSpd(party, 0.0f);
                party->gravity = 0.0f;
                if (!(party->flags & PARTY_FLAG_POSE_TILTED)) {
                    partyChgPoseId(party, 1);
                }
                partyChgMot(party, 0);
            }
            break;
        }
        partyNextReadId(id);
        partyGetReadId2(id, &t);
        if (!(party->flags & PARTY_FLAG_DISABLE_FLOORS)) {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
            hit = _partySearchGround(party, 10.0f, 0.0f);
            if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
                hit = NULL;
                if (!party->splashTimer) {
                    party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                    party->flags |= PARTY_FLAG_FORCE_FALL;
                }
            }
            party->hitobjStandOn = hit;
            if (!hit) {
                partyChgMot(party, 3);
                party->gravity = -1.0f;
            } else {
                attr = hitGetAttr(hit);
                if (attr & HIT_ATTR_SHALLOW_WATER) {
                    party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
                } else {
                    party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
                }
                if (attr & HIT_ATTR_SPIKES) {
                    partyChgMot(party, 0);
                    break;
                }
            }
        }
        if ((party->flags & PARTY_FLAG_IS_GROUNDED) && (fm->flags & PARTY_FOOTMARK_JUMP)) {
            md = toMovedir(party->displayDirectionTarget);
            partyGetReadId(id, &rx, &ry, &rz);
            L_getTargetPos(id, &tp);
            if (tp.y < ry) {
                ry = tp.y;
            }
            party->moveTarget.x = rx;
            party->moveTarget.z = rz;
            party->moveTarget.y = ry;
            gy = partyGetDirGndY(party->moveTarget, md);
            if (gy > party->position.y) {
                dir = partyToMovedir(party, party->displayDirectionTarget);
                sincosf(&s4, &c4, dir);
                {
                    f32 k = 40.0f;
                    party->moveTarget.x = s4 * k;
                    party->moveTarget.z = c4 * k;
                }
                party->moveTarget.y = gy;
            }
            partyChgMot(party, 2);
            break;
        }
        if (partyChkNoStandMobj(hit)) {
            partyGetAppearPos5(party, hit, &party->moveTarget);
            party->trigFlags |= PARTY_TRIG_FLAG_JUMP_OFF_MOBJ;
            partyChgMot(party, 2);
            break;
        }
        if ((party->flags & PARTY_FLAG_IS_GROUNDED) && (fm->flags & PARTY_FOOTMARK_SLIT)) {
            if (distABf(px, pz, t.x, t.z) <= 5.0f) {
                // FAKE: called through a cast so it stays a call (a direct call is inlined here; see docs/FAKES.md)
                ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
            }
            break;
        }
    }
    if (party->moveSpeed) {
        partyMoveAnime(party, party->moveSpeed);
    } else if (!(fm->flags & PARTY_FOOTMARK_SLIT)) {
        partyChgMot(party, 0);
    }
    party->targetDir = dir;
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &sp);
    hit = partySearchFrontWall(party, &v, sp, dir);
    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        hit = NULL;
    }
    if (!hit) {
        party->wallStuckFrames = 0;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE)) {
            getFrontFloor(party, &t, party->targetDir);
        } else {
            party->homeDir = revise360(270.0f + mario->targetYaw);
            partyGetAppearPos4(party, &t);
        }
        if (t.y > party->position.y) {
            a = t.y - party->position.y;
            if (a > 12.0 && a < 60.0f) {
                party->moveTarget = t;
                partyChgMot(party, 2);
                return;
            }
            if (t.y > party->position.y) {
                party->position.y = t.y;
            }
        }
        if (party->moveSpeed) {
            attr = partyGetFrontAttrFar(party);
            if (!(attr & HIT_ATTR_DEEP_WATER)) {
                v.x = party->position.x;
                v.z = party->position.z;
                movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
            }
        }
    } else {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
            if (hitGetAttr(hit) & HIT_ATTR_PAPER_SLIT) {
                if (party->slitOn != 1) {
                    if (!(party->playerPtr->trigFlags & MARIO_TRIG_FLAG_NORMALIZING)) {
                        party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
                        party->slitOn = 1;
                    }
                } else if (party->moveSpeed) {
                    v.x = party->position.x;
                    v.z = party->position.z;
                    movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
                }
            } else {
                party->wallStuckFrames++;
                if (party->wallStuckFrames > 8) {
                    party->wallStuckFrames = 0;
                    if (partyGetTargetDistY(id, party->position.y) >= 1.0f) {
                        getFrontFloor(party, &t, party->targetDir);
                        if (t.y - party->position.y > 5.0f) {
                            party->moveTarget = t;
                            partyChgMot(party, 2);
                            return;
                        }
                        if (!(party->flags & (PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING))) {
                            partyChkFrontStep(party, 11.0f, &fsy, &fsa, &fsb);
                            if (fsy - party->position.y >= 5.0f && party->groundSlope <= 30.0f) {
                                party->stepY = fsy;
                                if (party->moveSpeed) {
                                    partyChgMot(party, 6);
                                    return;
                                }
                            }
                        }
                    } else {
                        dir = partyGetTargetDir(id, party->position.x, party->position.z);
                        getFrontFloor(party, &t, dir);
                        a = t.y - party->position.y;
                        if (a > 100.0f) {
                            party->position = t;
                            partyChgMot(party, 1);
                        } else if (a >= 0.0f) {
                            party->moveTarget = t;
                            partyChgMot(party, 2);
                        } else {
                            partyChgMot(party, 0);
                        }
                    }
                }
            }
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
    hh = party->height;
    hp = party->position;
    hit = ((PartySearchHeadRetVoidptrFn)partySearchHead)(party, &hp, &hh, party->displayDirection);
    if (hit) {
        party->hitobjHead = hit;
    }
    party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
    hit = _partySearchGround(party, 10.0f, 10.0f);
    v.y = party->groundY;
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_DEEP_WATER) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        } else if (attr & HIT_ATTR_SPIKES) {
            partyChgRunMode(party, 13);
            return;
        }
    }
    party->hitobjStandOn = hit;
    if (!hit) {
        partyChgMot(party, 3);
        party->gravity = -1.0f;
    } else {
        if (hitGetAttr(hit) & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
        if (hitGetAttr(hit) & HIT_ATTR_DAMAGE_RETURN) {
            party->damageHit = hit;
        }
    }
    party->position.y = v.y;
    party_force_reset_outofscreen(party);
    partyGorFix(party);
}

/**
 * The flying partner's follow motion (motion 1 of move mode 1):
 * floats along Mario's footmarks, easing its height toward the floor ahead or Mario;
 * after 10 frames without floor behind a wall it heads straight for Mario.
 * The US release keeps the floor (no fall) when a footmark has none and avoids las_10's ceilings.
 */
void party_motion_homing_fly(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 id;
    s32 near;
    s32 w;
    HitEntry* hit;
    MarioWork* m2;
    PartyFootmark* fm;
    u32 attr;
    f32 lim;
    f32 lim2;
    f32 spd;
    f32 px, py, pz;
    f32 d3;
    f32 dd;
    f32 a;
    f32 off;
    f32 gy;
    Vec v;
    Vec s2;
    Vec ap;
    Vec ff;
#if VERSION >= VERSION_US
    Vec hp;
#endif
    Vec p2;
    Vec p3;
    f32 dir, sp;
    f32 tx, ty, tz;
    f32 x, z;
#if VERSION >= VERSION_US
    f32 hh;
    f32 hd;
    void* head;
    f32 u1;
#endif

    id = partyGetFootmarkId(party);
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
        party->noFloorFrames = 0;
    }
    if (party->forceMoveFrames != 0) {
        lim = 28.0f;
    } else {
        lim = VERSION_PICK(32.0f, 45.0f);
    }
    if (!strcmp(gp->currentMapName, "aji_02") || !strcmp(gp->currentMapName, "aji_05") ||
        !strcmp(gp->currentMapName, "aji_12")) {
        if (!marioKeyOffChk()) {
            lim = partyStayDist(party);
            party->trigFlags |= PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        }
    }
    if (partyGetTargetMovespd(id)) {
        lim2 = 50.0f;
    } else {
        lim2 = VERSION_PICK(35.0f, 45.0f);
    }
    if ((party->trigFlags >> 17) & 1) {
        lim2 = partyStayDist(party);
    }
    if (!party_slit(party)) {
        return;
    }
    if (!party_roll(party)) {
        return;
    }
    if (mario->currMotionId == MARIO_MOTION_TALK && !(party->flags & PARTY_FLAG_IS_BEHIND_MARIO)) {
        partyMoveBehindMario(party, 0);
        return;
    }
    if (!partyChkMarioFollowY(party->playerPtr)) {
        partyChgMot(party, 0);
        return;
    }
    spd = partyGetTargetMovespd2(party);
    d3 = PSVECDistance(&mario->position, &party->position);
    if (d3 < VERSION_PICK(35.0f, 45.0f)) {
        spd = 1.0f;
    } else if (d3 >= 50.0f) {
        spd = 3.0f;
    }
    if (party->playerPtr->flags & MARIO_FLAG_IS_PUSHING) {
        spd = 1.0f;
        lim = 100.0f;
    }
    partySetTargetSpd(party, spd);
    px = party->position.x;
    py = party->position.y;
    pz = party->position.z;
    fm = partyGetFootmarkPtr(id);
    tx = fm->pos.x;
    off = partyHomingOff(party);
    ty = fm->pos.y + off;
    tz = fm->pos.z;
    p2 = party->position;
    if (partyGetTargetDist3D(id, &p2) >= lim) {
        partySetTargetSpd(party, spd);
    }
    if (lim2 < 20.0f) {
        partySetTargetSpd(party, spd);
    }
    near = 0;
    while (TRUE) {
        dir = angleABf(px, pz, tx, tz);
        dd = distABf(px, pz, tx, tz);
        if (mario->flags & MARIO_FLAG_IS_PUSHING) {
            a = party->width + mario->wPlayerCollisionBox.x;
        } else {
            a = 0.5f * party->width + party->moveSpeed;
        }
        if (dd > a) {
            p3 = (Vec){px, py, pz};
            d3 = partyGetTargetDist3D(id, &p3);
            if (d3 >= lim) {
                if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    partyForceSetSpd(party, mario->baseSpeed + a);
                }
#if VERSION >= VERSION_US
                else {
                    // US: catch up with the speed of Mario when far behind
                    a = 0.1f * (d3 - lim);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    partyForceSetSpd(party, mario->baseSpeed + a);
                }
#endif
                near = 1;
                break;
            }
            if (marioGetSlitFloorPos(&v)) {
                partySetTargetSpd(party, 1.5f);
                partyNextReadId(id);
                if (marioGetSlitFloorPos(&v)) {
                    s2 = v;
                    py = distABf(px, pz, s2.x, s2.z);
                    dir = angleABf(px, pz, s2.x, s2.z);
                    if (py <= 5.0f) {
                        // FAKE: called through a cast so it stays a call (a direct call is inlined here; see docs/FAKES.md)
                        ((void (*)(PartyEntry*))partyChgMotSlitFloor)(party);
                    }
                }
                break;
            }
            if (d3 > lim2) {
                if (party->trigFlags & PARTY_TRIG_FLAG_FOLLOW_CLOSE) {
                    a = 0.1f * (d3 - lim2);
                    if (a > 4.0f) {
                        a = 4.0f;
                    }
                    if (a < 0.5f) {
                        a = 0.0f;
                    }
                    partyForceSetSpd(party, mario->baseSpeed + a);
                } else {
                    a = d3 - lim2;
                    if (a >= 1.0f) {
                        a = 1.0f;
                        if (lim2 < 20.0f) {
                            a = spd;
                        }
                    }
                    partySetTargetSpd(party, a);
                    break;
                }
            } else if (party->pushVelX == 0.0f && party->pushVelZ == 0.0f) {
                partySetTargetSpd(party, party->playerPtr->baseSpeed);
            } else {
                partyForceSetSpd(party, 0.0f);
                party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
                partyChgPoseId(party, 1);
            }
        }
        if (partyGetFootmarkReadId(id) == (w = partyGetFootmarkWriteId(id))) {
            partySetTargetSpd(party, party->playerPtr->baseSpeed);
            if (party->playerPtr->baseSpeed == 0.0f || party->pushVelX != 0.0f || party->pushVelZ != 0.0f) {
                dir = party->targetDir;
                partySetTargetSpd(party, 0.0f);
                party->gravity = 0.0f;
                if (!(party->flags & PARTY_FLAG_POSE_TILTED)) {
                    partyChgPoseId(party, 1);
                }
                partyChgMot(party, 0);
            }
            break;
        }
        partyNextReadId(id);
        partyGetReadId(id, &tx, &ty, &tz);
        if (party->flags & PARTY_FLAG_DISABLE_FLOORS) {
            continue;
        }
        party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        hit = _partySearchGround(party, 100.0f, 100.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
        }
        party->hitobjStandOn = hit;
        if (!hit) {
#if VERSION <= VERSION_JP
            partyChgMot(party, 3);
            party->gravity = -1.0f;
#endif
            continue;
        }
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
        if (attr & HIT_ATTR_SPIKES) {
            partyChgMot(party, 0);
            break;
        }
    }
    if (party->moveSpeed) {
        partyMoveAnime(party, party->moveSpeed);
    } else {
        partyChgMot(party, 0);
    }
    if (party->noFloorFrames > 10) {
        dir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
    }
    if (near) {
        m2 = party->playerPtr;
        partyGetAppearPos3(party, &ap);
        dir = angleABf(party->position.x, party->position.z, ap.x, ap.z);
        hit = _partySearchGround(party, 10.0f, 0.0f);
        ap.y = party->groundY;
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
        }
        if (hit) {
            party->position.y = ap.y;
        } else {
            off = partyHomingOff(party);
            party->position.y += 0.05f * ((m2->position.y + off) - party->position.y);
        }
    }
    party->targetDir = dir;
    v = party->position;
    partyGetMoveDirSpd(party, &dir, &sp);
    hit = partySearchFrontWall(party, &v, sp, dir);
    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        hit = NULL;
    }
    if (!hit) {
        if (!(party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE)) {
            getFrontFloor(party, &ff, party->targetDir);
        } else {
            party->homeDir = revise360(270.0f + mario->targetYaw);
            partyGetAppearPos4(party, &ff);
        }
        if (ff.y >= mario->position.y) {
            off = partyHomingOff(party);
            party->position.y += 0.05f * ((ff.y + off) - party->position.y);
        }
        party->noFloorFrames = 0;
        if (party->moveSpeed) {
            v.x = party->position.x;
            v.z = party->position.z;
            movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
        }
    } else {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
            if (hitGetAttr(hit) & HIT_ATTR_PAPER_SLIT) {
                if (party->slitOn != 1) {
                    if (!(party->playerPtr->trigFlags & MARIO_TRIG_FLAG_NORMALIZING)) {
                        party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
                        party->slitOn = 1;
                    }
                } else if (party->moveSpeed) {
                    v.x = party->position.x;
                    v.z = party->position.z;
                    movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
                }
            } else {
                x = party->position.x;
                gy = party->position.y;
                z = party->position.z;
                movePos(&x, &z, party->width, dir);
                gy = partyGetGndY(x, gy, z);
                if (gy > -2000.0f) {
                    party->position.y += 0.05f * ((gy + party->height) - party->position.y);
                } else {
                    party->noFloorFrames++;
                    if (partyGetTargetDistY(id, party->position.y) >= 1.0f &&
                        __fabsf(mario->position.y - party->position.y) >= 10.0f) {
                        party->position.y = party->position.y + 0.1f * ((10.0f + mario->position.y) - party->position.y);
                        party->position.x = v.x;
                        party->position.z = v.z;
                        return;
                    }
                }
            }
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
#if VERSION >= VERSION_US
    // US: on las_10 the partner is pushed down out of low ceilings
    if (!strcmp(gp->currentMapName, "las_10")) {
        hp = party->position;
        hh = party->height;
        head = ((PartySearchHeadRetVoidptrFn)partySearchHead)(party, &hp, &hh, party->displayDirection);
        if (head) {
            party->hitobjHead = head;
            hd = hp.y - party->height - party->position.y;
            if (-5.0f > hd || hd >= 0.0f) {
                a = 0.1f;
                party->position.y += hd * a;
            }
        }
    }
#endif
    party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
    hit = _partySearchGround(party, 10.0f, 10.0f);
    if (hit) {
        attr = hitGetAttr(hit);
        if (attr & HIT_ATTR_SPIKES) {
            partyChgRunMode(party, 13);
            return;
        }
        if (attr & HIT_ATTR_SHALLOW_WATER) {
            party->flags |= PARTY_FLAG_IN_SHALLOW_WATER;
        } else {
            party->flags &= ~PARTY_FLAG_IN_SHALLOW_WATER;
        }
    }
    party_force_reset_outofscreen(party);
}

/**
 * Makes the next behind-Mario walk stand at direction dir (degrees, relative to the camera) from Mario instead
 * of behind his facing; partyMoveBehindMario3 calls it without passing dir.
 */
void party_set_behind_dir(PartyEntry* party, f32 dir) {
    party->homeDir = revise360(dir + camGetPtr((CameraId)4)->viewYaw);
    party->trigFlags |= PARTY_TRIG_FLAG_HOME_DIR_SET;
}

/**
 * Movement direction (degrees) of whoever this partner follows:
 * Mario, or for a second partner the first one when it is out.
 */
static inline f32 partyGetFollowDir(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* other;
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        return toMovedir(mario->displayDirection);
    }
    other = partyGetPtr(marioGetPartyId());
    if (other) {
        return partyToMovedir(party, other->displayDirection);
    }
    return toMovedir(mario->displayDirection);
}

/**
 * Move mode 2 (partyMoveBehindMario, and whenever Mario talks):
 * walks the partner to its spot behind Mario (or at homeDir), jumping where the floor height changes;
 * when it arrives or hits a wall it goes back to normal following (move mode 1).
 */
void party_motion_behind_mario(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    f32 ang;
    f32 gy;
    f32 dist;
    f32 thr;
    f32 ty;
    f32 x, z;
    Vec target;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET)) {
            {
                f32 t;
                if (!(party->trigFlags & PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET)) {
                    t = partyGetFollowDir(party);
                    t += 180.0f;
                    t = revise360(t);
                } else {
                    party->trigFlags &= ~PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET;
                    t = revise360(180.0f + angleABf(mario->position.x, mario->position.z, party->moveTarget.x, party->moveTarget.z));
                }
                party->homeDir = t;
            }
        }
        partyGetAppearPos4(party, &target);
        party->moveFrames = distABf(party->position.x, party->position.z, target.x, target.z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET) && marioKeyOffChk()) {
        {
            f32 t2 = partyGetFollowDir(party);
            t2 += 180.0f;
            party->homeDir = revise360(t2);
        }
    }
    partyGetAppearPos4(party, &target);
    x = target.x;
    z = target.z;
    ty = target.y;
    ang = angleABf(party->position.x, party->position.z, x, z);
    {
        f32 py = ty;
        f32 nz, ny, nx, dd, hz, hy, hx;
        py += gnd_probe_dy;
        dd = 1000.0f;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
        if (!hit) {
            gy = -2000.0f;
        } else {
            gy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            hitGetAttr(hit);
        }
    }
    if (gy <= -2000.0f) {
        gy = 1.5f * mario->wPlayerCollisionBox.x;
        movePos(&x, &z, gy, toMovedir(mario->displayDirection));
    }
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    dist = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (dist >= thr && party->moveFrames > 0) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        distABf(party->position.x, party->position.z, x, z);
        partyForceSetSpd(party, (party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET) ? 3.6f : 2.0f);
        partyMoveCheckWall(party);
        partyMoveAnime(party, party->moveSpeed);
        if (party->hitobjFront) {
            x = party->position.x;
            z = party->position.z;
            movePos(&x, &z, dist, ang);
            angleABf(party->position.x, party->position.z, x, z);
            {
                f32 py = ty;
                f32 GG;
                f32 nz, ny, nx, dd, hz, hy, hx;
                py += gnd_probe_dy;
                dd = 1000.0f;
                hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
                if (!hit) {
                    GG = -2000.0f;
                } else {
                    GG = (s32)(100.0f * hy + 0.5f) / 100.0f;
                    hitGetAttr(hit);
                }
                thr = GG;
            }
            if (__fabsf(party->position.y - thr) > 1.0f) {
                party->moveTarget.x = x;
                party->moveTarget.y = thr;
                party->moveTarget.z = z;
                partyChgMot(party, 2);
                return;
            }
        } else if (ty > party->position.y) {
            x = party->position.x;
            z = party->position.z;
            movePos(&x, &z, dist, ang);
            angleABf(party->position.x, party->position.z, x, z);
            {
                f32 py = ty;
                f32 GG;
                f32 nz, ny, nx, dd, hz, hy, hx;
                py += gnd_probe_dy;
                dd = 1000.0f;
                hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dd, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
                if (!hit) {
                    GG = -2000.0f;
                } else {
                    GG = (s32)(100.0f * hy + 0.5f) / 100.0f;
                    hitGetAttr(hit);
                }
                thr = GG;
            }
            if (__fabsf(party->position.y - thr) > 1.0f) {
                party->moveTarget.x = x;
                party->moveTarget.y = thr;
                party->moveTarget.z = z;
                partyChgMot(party, 2);
                return;
            }
        }
        hit = partyBehindGround(party);
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        }
        party->position.y = party->groundY;
    } else {
        party->moveFrames = 0;
        if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
            party->trigFlags &= ~PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        }
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
        party->trigFlags &= ~PARTY_TRIG_FLAG_HOME_DIR_SET;
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
#if VERSION >= VERSION_US
        party->trigFlags &= ~PARTY_TRIG_FLAG_DOOR_MOVE;
#endif
    }
    if (party->hitobjPush) {
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, x, z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
#if VERSION >= VERSION_US
        party->trigFlags &= ~PARTY_TRIG_FLAG_DOOR_MOVE;
#endif
    }
}

/**
 * Move mode 6, set by partyReInit when the partner may not walk after a map change:
 * keeps the partner walking to the spot behind Mario's facing;
 * hands back to normal following once Mario stands still there.
 */
void party_motion_behind_mario_continue(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* other;
    HitEntry* hit;
    f32 y;
    f32 gy;
    f32 sp;
    f32 thr;
    f32 x, z;

    {
        f32 t = partyGetFollowDir(party);
        t += 180.0f;
        party->homeDir = revise360(t);
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, party->homeDir);
        party->moveFrames = distABf(party->position.x, party->position.z, x, z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (marioKeyOffChk()) {
        {
            f32 t = partyGetFollowDir(party);
            t += 180.0f;
            party->homeDir = revise360(t);
        }
    }
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        y = mario->position.y;
    } else {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        other = anotherPartyGetPtr(party->currentSlotId);
        if (other) {
            x = other->position.x;
            z = other->position.z;
            y = other->position.y;
        } else {
            x = mario->position.x;
            z = mario->position.z;
            y = mario->position.y;
        }
    }
    movePos(&x, &z, sp, party->homeDir);
    angleABf(party->position.x, party->position.z, x, z);
    {
        f32 py = y;
        f32 nz, ny, nx, dist, hz, hy, hx;
        py += gnd_probe_dy;
        dist = 1000.0f;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, py, z, 0.0f, -1.0f, 0.0f);
        if (!hit) {
            gy = -2000.0f;
        } else {
            gy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            hitGetAttr(hit);
        }
    }
    if (gy <= -2000.0f) {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        movePos(&x, &z, sp, toMovedir(mario->displayDirection));
    }
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    sp = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (sp >= thr) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        sp = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (sp > 2.0f) {
            sp = 2.0f;
        }
        if (sp < 1.0f) {
            sp = 1.0f;
        }
        partyForceSetSpd(party, sp);
        partyMoveCheckWall(party);
        partyMoveAnime(party, party->moveSpeed);
        hit = partyBehindGround(party);
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        }
        party->position.y = party->groundY;
    } else {
        party->moveFrames = 0;
        if (mario->baseSpeed == 0.0f) {
            party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
            partyChgMoveMode(party, 1);
            partyChgMot(party, 0);
            partySetDir(party, mario->position.x, mario->position.z);
            party->homingDist = 50.0f;
            party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        }
    }
    if (party->hitobjPush) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, x, z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
    }
}

/**
 * The flying partner's behind-Mario motion (move modes 2 and 6):
 * floats to moveTarget behind Mario, then returns to normal following facing him.
 */
void party_motion_behind_mario_fly(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    f32 thr;
    f32 spd;
    f32 dist;
    Vec pos;
    f32 sp, dir;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->trigFlags |= PARTY_TRIG_FLAG_SMALL_HOSEI;
        if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET)) {
            {
                f32 t;
                if (!(party->trigFlags & PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET)) {
                    t = partyGetFollowDir(party);
                    t += 180.0f;
                    t = revise360(t);
                } else {
                    party->trigFlags &= ~PARTY_TRIG_FLAG_BEHIND_MOVE_TARGET;
                    t = revise360(angleABf(mario->position.x, mario->position.z, party->moveTarget.x, party->moveTarget.z) + 180.0f);
                }
                party->homeDir = t;
            }
        }
        partyGetAppearPos4(party, &party->moveTarget);
        party->moveFrames = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (!(party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET) && marioKeyOffChk()) {
        f32 t2 = partyGetFollowDir(party);
        t2 += 180.0f;
        party->homeDir = revise360(t2);
    }
    angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
    if (mario->baseSpeed > 1.0f) {
        thr = 6.0f;
    } else {
        thr = 2.0f;
    }
    dist = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
    party->moveFrames--;
    if ((dist >= thr || __fabsf(party->moveTarget.y - party->position.y) > 2.0f) && party->moveFrames > 0) {
        party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        if (party->trigFlags & PARTY_TRIG_FLAG_HOME_DIR_SET) {
            spd = 3.6f;
        } else {
            spd = 2.0f;
        }
        if (dist < thr) {
            spd = 0.0f;
            partyForceSetSpd(party, spd);
        }
        partySetTargetSpd(party, spd);
        pos = party->position;
        partyGetMoveDirSpd(party, &dir, &sp);
        hit = partySearchFrontWall(party, &pos, sp, dir);
        if (hit) {
            party->hitobjFront = hit;
            if (party->moveSpeed) {
                party->hitobjPush = hit;
            }
        }
        party->position.x = pos.x;
        party->position.z = pos.z;
        party->position.y += 0.05f * (party->moveTarget.y - party->position.y);
        partyMoveAnime(party, party->moveSpeed);
        return;
    }
    party->moveFrames = 0;
    if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_FOLLOW_CLOSE;
        if (party->moveKind == 1) {
            party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        }
    }
    partyChgMoveMode(party, 1);
    partyChgMot(party, 0);
    partySetDir(party, mario->position.x, mario->position.z);
    party->homingDist = 50.0f;
    party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
    partyForceSetSpd(party, 0.0f);
    party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
    party->trigFlags &= ~PARTY_TRIG_FLAG_HOME_DIR_SET;
    party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
#if VERSION >= VERSION_US
    party->trigFlags &= ~PARTY_TRIG_FLAG_DOOR_MOVE;
#endif
    partySetDispDirToMario(party);
    if (party->hitobjPush) {
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->trigFlags &= ~PARTY_TRIG_FLAG_SMALL_HOSEI;
    }
    hit = _partySearchGround(party, 100.0f, 100.0f);
    if (hit) {
        if (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        if (dist > party->height) {
            hit = NULL;
        }
        party->position.y += 0.05f * (party->groundY - party->position.y);
    }
    party->hitobjStandOn = hit;
}

/**
 * Move mode 3 (partyMoveBesideMario): walks the partner to the spot at Mario's side (90 degrees from his
 * facing), then returns to normal following.
 */
void party_motion_beside_mario(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    f32 x, z;
    f32 y;
    f32 nz, ny, nx, dist, hz, hy, hx;
    f32 thr;
    f32 sp;
    f32 t;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        t = partyGetFollowDir(party);
        t += 90.0f;
        party->homeDir = revise360(t);
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, party->homeDir);
        party->moveFrames = distABf(party->position.x, party->position.z, x, z);
        if (party->moveFrames <= 0) {
            party->moveFrames = 1;
        }
    }
    if (marioKeyOffChk()) {
        t = partyGetFollowDir(party);
        t += 90.0f;
        party->homeDir = revise360(t);
    }
    sp = 1.5f * mario->wPlayerCollisionBox.x;
    x = mario->position.x;
    z = mario->position.z;
    y = mario->position.y;
    movePos(&x, &z, sp, party->homeDir);
    angleABf(party->position.x, party->position.z, x, z);
    y = partyGetGndY(x, y, z);
    if (y <= -2000.0f) {
        sp = 1.5f * mario->wPlayerCollisionBox.x;
        x = mario->position.x;
        z = mario->position.z;
        movePos(&x, &z, sp, toMovedir(mario->displayDirection));
    }
    thr = 2.0f;
    if (mario->baseSpeed > 1.0f) {
        thr = 10.0f;
    }
    sp = distABf(party->position.x, party->position.z, x, z);
    party->moveFrames--;
    if (sp >= thr && party->moveFrames > 0) {
        party->targetDir = angleABf(party->position.x, party->position.z, x, z);
        sp = distABf(party->position.x, party->position.z, x, z) / 10.0f;
        if (sp > 2.0f) {
            sp = 2.0f;
        }
        if (sp < 1.0f) {
            sp = 1.0f;
        }
        partyForceSetSpd(party, sp);
        partyMoveCheckWall(party);
        partyMoveAnime(party, party->moveSpeed);
        hit = _partySearchGround(party, 10.0f, 0.0f);
        if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
            hit = NULL;
            if (!party->splashTimer) {
                party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                party->flags |= PARTY_FLAG_FORCE_FALL;
            }
        }
        party->hitobjStandOn = hit;
        if (!hit) {
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        }
        party->position.y = party->groundY;
    } else {
        party->moveFrames = 0;
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
        party->flags |= PARTY_FLAG_IS_BEHIND_MARIO;
    }
    if (party->hitobjPush) {
        partyChgMoveMode(party, 1);
        partyChgMot(party, 0);
        partySetDir(party, mario->position.x, mario->position.z);
        party->homingDist = 50.0f;
        party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
    }
}

/** Unused copy of partyJumpFrontMove. */
static inline void partyJumpWallMove(PartyEntry* party) {
    Vec v;
    HitEntry* hit;

    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
        return;
    }
    v = party->position;
    hit = partySearchFrontWall(party, &v, party->moveSpeed, party->targetDir);
    if (hit) {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
}

/**
 * Moves a jumping partner forward by moveSpeed along targetDir, stopped by walls;
 * records the wall in hitobjFront/hitobjPush.
 * With the front wall check disabled it moves a scratch vector that is never stored,
 * so the partner does not move sideways at all.
 */
static inline void partyJumpFrontMove(PartyEntry* party) {
    Vec v;
    HitEntry* hit;
    if (party->flags & PARTY_FLAG_DISABLE_FRONT_WALL_CHK) {
        movePos(&v.x, &v.z, party->moveSpeed, party->targetDir);
        return;
    }
    v = party->position;
    hit = partySearchFrontWall(party, &v, party->moveSpeed, party->targetDir);
    if (hit) {
        party->hitobjFront = hit;
        if (party->moveSpeed) {
            party->hitobjPush = hit;
        }
    }
    party->position.x = v.x;
    party->position.z = v.z;
}

/** Jump arc height for a rise of dy: 25 for a level jump, dy going up, 10 going down. */
static inline f32 partyJumpHeight(f32 dy) {
    if (__fabsf(dy) < 1.0f) {
        return 25.0f;
    } else if (dy >= 0.0f) {
        return dy;
    } else {
        return 10.0f;
    }
}

/**
 * Sets up a follow jump over distance d: 12 to 40 frames, initial velY 3 to 13 and the gravity,
 * scaled by Mario's playerGravity.
 */
static inline void partyJumpCalc(PartyEntry* party, MarioWork* mario, f32 d) {
    f32 t;
    f32 dy;
    f32 g;
    s32 gz;
    party->moveFrames = (10.0f * (0.9f * (d / party->moveSpeed)) + 0.5f) / 10.0f;
    if (party->moveFrames < 12) {
        party->moveFrames = 12;
    }
    if (party->moveFrames > 40) {
        party->moveFrames = 40;
    }
    t = 0.5f * party->moveFrames;
    dy = partyJumpHeight(party->moveTarget.y - party->position.y);
    // FAKE: dead int-guarded re-definition (folded only by the post-RA peephole) keeps the moveDistance value d live
    // across the jump-height block so it takes f5 and dy f6 as in the target; behaviour-identical (gz is 0).
    gz = 0;
    if (gz != 0) {
        t = d;
    }
    g = (dy + dy) / (t * t - t);
    party->velY = mario->playerGravity * (g * t);
    if (party->velY > 13.0f) {
        party->velY = 13.0f;
    }
    if (party->velY < 3.0f) {
        party->velY = 3.0f;
    }
    party->gravity = -g * mario->playerGravity;
}

/**
 * The follow jump (motion 2): aims at moveTarget,
 * the next footmark (at most 50 units or 1.4 times the rise away) or the floor ahead, sets up the arc,
 * plays the jump sound, then flies it until landing (motion 0) or a splash in water (motion 3).
 */
void party_motion_jump(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 id;
    HitEntry* hit;
    f32 dir;
    f32 dist;
    f32 lim;
#if VERSION >= VERSION_US
    f32 dist2;
#endif
    Vec fl;
    f32 s, c;
    f32 x, y, z;

    id = partyGetFootmarkId(party);
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->motionStep = 0;
    }
    switch (party->motionStep) {
        case 0:
            x = party->moveTarget.x;
            y = party->moveTarget.y;
            z = party->moveTarget.z;
            if (party->forceMoveFrames != 0 || party->runMode == 9) {
                x = party->position.x;
                y = party->position.y;
                z = party->position.z;
                movePos(&x, &z, party->moveSpeed, party->targetDir);
                party->moveTarget = (Vec){x, y, z};
            } else if (!(party->trigFlags & PARTY_TRIG_FLAG_JUMP_OFF_MOBJ)) {
                if (partyGetFootmarkReadId(id) == partyGetFootmarkWriteId(id)) {
                    if (partyGetTargetDist(id, party->position.x, party->position.z) > 2.0f * mario->wPlayerCollisionBox.x) {
                        dir = partyGetTargetDir(id, party->position.x, party->position.z);
                        getFrontFloor(party, &fl, dir);
                        fl.y += 10.0f;
                        y = fl.y;
                        x = party->position.x;
                        z = party->position.z;
                        movePos(&x, &z, 0.6f * party->width, dir);
                    }
                    party->moveTarget = (Vec){x, y, z};
                } else {
                    partyGetReadId(id, &x, &y, &z);
                    lim = 50.0f;
                    dist = distABf(party->position.x, party->position.z, x, z);
#if VERSION >= VERSION_US
                    dist2 = __fabsf(y - party->position.y);
                    if (50.0f > 1.4f * dist2) {
                        lim = 1.4f * dist2;
                    }
#else
                    if (50.0f > 1.4f * (y - party->position.y)) {
                        lim = 1.4f * (y - party->position.y);
                    }
#endif
                    sincosf(&s, &c, angleABf(party->position.x, party->position.z, x, z));
                    if (dist > lim) {
                        dist = lim;
                        if (partyGetTargetMovespd(id) == 0.0f) {
                            dist = 0.0f;
                        }
                        x = party->position.x;
                        z = party->position.z;
                        x = x + dist * s;
                        z = z + dist * c;
                        y += 10.0f;
                        party->moveTarget = (Vec){x, y, z};
                    } else {
                        if (partyGetTargetMovespd(id) == 0.0f) {
                            dist = 0.0f;
                        }
                        x = x + dist * s;
                        z = z + dist * c;
                        party->moveTarget = (Vec){x, y, z};
                    }
                    if (dist < lim) {
                        partyNextReadId(id);
                    }
                }
            }
            party->moveDistance = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
            if (party->forceMoveFrames == 0) {
                party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
                party->moveSpeed = 2.25f * party->playerPtr->playerGravity;
            }
            partyJumpCalc(party, mario, party->moveDistance);
            party->flags |= PARTY_FLAG_IS_JUMPING;
            party->flags &= ~PARTY_FLAG_IS_GROUNDED;
            partyChgPoseId(party, 4);
            psndSFXOn_3D((const char*)0x927, &party->position);
            party->motionStep = 10;
            if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
                partyNextReadId(partyGetFootmarkId(party));
            }
            break;
        case 10:
            if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
                partyNextReadId(partyGetFootmarkId(party));
            }
            party->velY += party->gravity;
            party->position.y += party->velY;
            if (party->position.y < -2000.0f) {
                party->flags &= ~PARTY_FLAG_IS_JUMPING;
                party->velY = 0.0f;
                party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
                party->position = mario->position;
                partyChgMot(party, 0);
                break;
            }
            if (party->velY <= 0.0f) {
                party->flags &= ~PARTY_FLAG_IS_JUMPING;
                party->flags |= PARTY_FLAG_IS_FALLING;
                hit = _partySearchGround(party, __fabsf(party->velY), 0.0f);
                if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
                    if (!party->splashTimer) {
                        party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                        party->flags |= PARTY_FLAG_FORCE_FALL;
                    }
                    party->hitobjStandOn = NULL;
                    partyChgMot(party, 3);
                    party->gravity = -1.0f;
                    break;
                }
                party->hitobjStandOn = hit;
                party->position.y = party->groundY;
                if (hit) {
                    party->flags |= PARTY_FLAG_IS_GROUNDED;
#if VERSION >= VERSION_US
                    party->trigFlags &= ~PARTY_TRIG_FLAG_JUMP_OFF_MOBJ;
#endif
                    party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
                    N_partyPlaySfxPartyLanding1(party);
                    party->velY = 0.0f;
                    partyChgMot(party, 0);
                    party->trigFlags |= PARTY_TRIG_FLAG_KEEP_FOOTMARKS;
                    break;
                }
            }
            partyJumpFrontMove(party);
            break;
    }
}
/**
 * The jump to moveTarget used by the behind/beside-Mario modes (motion 2 there):
 * at most 50 units across, at least 10 frames; on landing it goes to stay
 * or follow depending on how close moveTarget is.
 */
void party_motion_jump2(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    Vec pos;
    f32 dist;
    f32 dy;
    f32 fr;
    s32 frames;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->moveFrames = 0;
        party->gravity = -1.0f * mario->playerGravity;
        party->moveSpeed = 2.25f * mario->playerGravity;
        party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        dist = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        if (dist > 50.0f) {
            dist = 50.0f;
        }
        party->moveDistance = dist;
        dy = party->moveTarget.y - party->position.y;
        frames = (10.0f * (dist / party->moveSpeed) + 0.5f) / 10.0f;
        if (frames < 10) {
            frames = 10;
        }
        fr = frames;
        party->moveFrames = frames;
        party->moveSpeed = mario->playerGravity * (party->moveDistance / fr);
        party->velY = (0.5f * (fr * (fr * __fabsf(party->gravity))) + dy) / fr;
        party->velY *= mario->playerGravity;
        if (party->velY > 20.0f) {
            party->velY = 20.0f;
        }
        if (party->velY < 0.0f) {
            party->velY = 0.0f;
        }
        partyChgPoseId(party, 4);
        party->flags |= PARTY_FLAG_IS_JUMPING;
        party->flags &= ~PARTY_FLAG_IS_GROUNDED;
        psndSFXOn_3D((const char*)0x927, &party->position);
        party->motionStep = 0;
    }
    switch (party->motionStep) {
        case 0:
            party->motionStep = 1;
            break;
        case 1:
            party->velY += party->gravity;
            party->position.y += party->velY;
            pos = party->position;
            partySearchFrontWall(party, &pos, party->moveSpeed, party->targetDir);
            party->position.x = pos.x;
            party->position.z = pos.z;
            if (party->velY <= 0.0f) {
                hit = _partySearchGround(party, __fabsf(party->velY), 0.0f);
                pos.y = party->groundY;
                if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
                    if (!party->splashTimer) {
                        party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
                        party->flags |= PARTY_FLAG_FORCE_FALL;
                    }
                    party->hitobjStandOn = NULL;
                    partyChgMot(party, 3);
                    party->gravity = -1.0f;
                    return;
                }
                party->position.y = pos.y;
                party->hitobjStandOn = hit;
                if (hit) {
                    N_partyPlaySfxPartyLanding1(party);
                    party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
                    party->flags |= PARTY_FLAG_IS_GROUNDED;
#if VERSION >= VERSION_US
                    party->trigFlags &= ~PARTY_TRIG_FLAG_JUMP_OFF_MOBJ;
#endif
                    party->velY = 0.0f;
                    partyChgMot(party, distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z) < 5.0f ? 0 : 1);
                }
            }
            break;
    }
    if (party->position.y < -2000.0f) {
        party->flags &= ~PARTY_FLAG_IS_JUMPING;
        party->velY = 0.0f;
        party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
        party->position = mario->position;
        partyChgMot(party, 0);
    }
}

/**
 * The fall motion (motion 3): gravity up to -16 a frame,
 * lands on a floor (stay or follow by speed, landing sound) and drops the partner back behind Mario
 * when it falls below -2000. Returns 2 while falling, 3 on landing.
 * The US release slows the sideways drift when the stick is held.
 */
s32 party_motion_fall(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    HitEntry* hit;
    Vec pos;

    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        partyNextReadId(partyGetFootmarkId(party));
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        partyChgPoseId(party, 4);
        party->flags &= ~PARTY_FLAG_IS_BEHIND_MARIO;
    }
    hit = NULL;
    if (!(party->flags & PARTY_FLAG_FORCE_FALL)) {
        hit = _partySearchGround(party, 10.0f, __fabsf(party->velY));
    }
    if (hit && (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER)) {
        hit = NULL;
        if (party->moveKind == 0 && !party->splashTimer) {
            party->trigFlags |= PARTY_TRIG_FLAG_SPLASH;
            party->flags |= PARTY_FLAG_FORCE_FALL;
        }
    }
    party->hitobjStandOn = hit;
    if (!hit) {
        party->flags &= ~PARTY_FLAG_IS_GROUNDED;
        if (!(party->flags & PARTY_FLAG_IS_FALLING)) {
            party->flags |= PARTY_FLAG_IS_FALLING;
            if (party->gravity == 0.0f) {
                party->gravity = -1.4f;
            }
        }
        party->velY += party->gravity;
        if (party->velY < -16.0f) {
            party->velY = -16.0f;
        }
        party->position.y += party->velY;
#if VERSION >= VERSION_US
        // US: with the stick released the drift of the partner slows down while falling
        if (!marioKeyOffChk()) {
            party->moveSpeed += -0.2f;
            if (party->moveSpeed < 0.0f) {
                party->moveSpeed = 0.0f;
            }
        }
#endif
        if (party->position.y < -2000.0f) {
            party->position.y = -2001.0f;
            if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE) {
                return 2;
            }
            party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
            party->velY = 0.0f;
            party->gravity = 0.0f;
            party->targetDir = angleABf(party->position.x, party->position.z, mario->position.x, mario->position.z);
            party->homeDir = revise360(180.0f + toMovedir(mario->displayDirectionTarget));
            partyGetAppearPos4(party, &party->position);
            party->position.y += 37.0f;
            partyChgMot(party, 0);
            party->flags &= ~PARTY_FLAG_FORCE_FALL;
        }
        if (party->moveSpeed) {
            pos = party->position;
            partySearchFrontWall(party, &pos, 1.3f * party->moveSpeed, party->targetDir);
            party->position.x = pos.x;
            party->position.z = pos.z;
        }
        return 2;
    }
    if (party->flags & PARTY_FLAG_IS_FALLING) {
        party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
        party->flags |= PARTY_FLAG_IS_GROUNDED;
#if VERSION >= VERSION_US
        party->trigFlags &= ~PARTY_TRIG_FLAG_JUMP_OFF_MOBJ;
#endif
        party->velY = 0.0f;
        party->position.y = party->groundY;
        if (party->moveSpeed == 0.0f) {
            partyChgMot(party, 0);
        } else {
            partyChgMot(party, 1);
        }
        N_partyPlaySfxPartyLanding1(party);
        return 3;
    }
    party->flags &= ~PARTY_FLAG_MOT_SLIT_FLOOR;
    party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
    party->flags |= PARTY_FLAG_IS_GROUNDED;
#if VERSION >= VERSION_US
    party->trigFlags &= ~PARTY_TRIG_FLAG_JUMP_OFF_MOBJ;
#endif
    party->velY = 0.0f;
    party->position.y = party->groundY;
    if (party->moveSpeed == 0.0f) {
        partyChgMot(party, 0);
    } else {
        partyChgMot(party, 1);
    }
    N_partyPlaySfxPartyLanding1(party);
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        partyClearFootmark();
    } else {
        partyClearFootmark2();
    }
    return 3;
}

/**
 * The step-up motion (motion 6, from homing walk or partyHit):
 * rises to stepY over 3 frames, then goes back to following (motion 1).
 */
void party_motion_upstairs(PartyEntry* party) {
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->flags |= PARTY_FLAG_IS_STEPPING;
        upstairs_count = 3;
        upstairs_dy = (party->stepY - party->position.y) / 3.0f;
    }
    party->position.y += upstairs_dy;
    if (--upstairs_count <= 0) {
        party->flags &= ~PARTY_FLAG_IS_STEPPING;
        partyChgMot(party, 1);
    }
}

/** TRUE when hit is water (attribute 0x200). */
static inline BOOL partyChkHitAttr200(HitEntry* hit) {
    if (!hit) {
        return FALSE;
    }
    if (hitGetAttr(hit) & HIT_ATTR_DEEP_WATER) {
        return TRUE;
    }
    return FALSE;
}

/**
 * Motion 7, the partner knocked away: it flies up off the top of the screen,
 * waits until Mario's damage motion is over, drops in from 200 above partyGetReturnPos and,
 * 30 frames after landing on dry floor, returns to normal (run mode 2, move mode 0).
 */
void party_motion_damage(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 x, y, z;
    Vec ret;

    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_MOT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_MOT;
        party->motionStep = 0;
    }
    switch (party->motionStep) {
        case 0:
            partyChgPoseId(party, 8);
            party->velY = 15.0f;
            party->accelY = 0.0f;
            party->moveFrames = 60;
            party->motionStep = 1;
        case 1:
            party->position.y += party->velY;
            marioGetScreenPos(party->position, &x, &y, &z);
            if (y <= -300.0f) {
                party->moveFrames = 20;
                party->motionStep = 10;
            }
            break;
        case 10:
            if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE) {
                break;
            }
            if (--party->moveFrames <= 0) {
                partyGetReturnPos(&ret);
                party->position.x = ret.x;
                party->position.y = 200.0f + ret.y;
                party->position.z = ret.z;
                party->velY = 0.0f;
                party->accelY = -1.0f;
                partyForceSetSpd(party, 0.0f);
                party->flags |= PARTY_FLAG_IS_FALLING;
                party->flags |= PARTY_FLAG_FORCE_FALL;
                party->motionStep = 11;
            }
            break;
        case 11:
            marioGetScreenPos(party->position, &x, &y, &z);
            if (y > 240.0f) {
                party->flags &= ~PARTY_FLAG_FORCE_FALL;
            }
            partyMove(party);
            if (party->velY <= -6.0f) {
                party->accelY = 0.0f;
                party->velY = -6.0f;
            }
            if (party->position.y < -2000.0f) {
                party->position = mario->position;
                party->position.y += 200.0f;
                party->flags &= ~(PARTY_FLAG_IS_JUMPING | PARTY_FLAG_IS_FALLING | PARTY_FLAG_IS_STEPPING);
            }
            if (party->hitobjStandOn && !partyChkHitAttr200(party->hitobjStandOn)) {
                party->motionStep = 12;
                party->moveFrames = 30;
            }
            break;
        case 12:
            if (--party->moveFrames <= 0) {
                partyChgRunMode(party, 2);
                party->moveMode = 0;
                party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
            }
            break;
    }
}

/**
 * Mario entered Paper Mode (mot_slit.c): both partners turn sideways too (slitOn 1, set up by party_slit),
 * unless Mario is being normalized.
 */
void allPartySlitOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        if (!(party->playerPtr->trigFlags & MARIO_TRIG_FLAG_NORMALIZING)) {
            party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
            party->slitOn = 1;
        }
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        if (!(party->playerPtr->trigFlags & MARIO_TRIG_FLAG_NORMALIZING)) {
            party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
            party->slitOn = 1;
        }
    }
}

/**
 * Mario left Paper Mode: both partners still in it start their turn-back animation (slitStep 40).
 * Called from mot_slit.c.
 */
void allPartySlitOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && (party->flags & PARTY_FLAG_PAPER_MODE) && party->slitStep < 0x28) {
        party->slitStep = 0x28;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && (party->flags & PARTY_FLAG_PAPER_MODE) && party->slitStep < 0x28) {
        party->slitStep = 0x28;
    }
}

/**
 * Ends Paper Mode at once on both partners; used when Mario's own Paper Mode is cut short (mot_slit.c),
 * by the all_party_slit_off script helper and when the pause menu opens (win_main.c).
 */
void allPartyForceSlitOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        L_partyForceSlitOff(party);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        L_partyForceSlitOff(party);
    }
}

#if VERSION >= VERSION_US
/**
 * US: ends Paper Mode on both partners without changing their facing;
 * mot_slit.c uses it instead of allPartyForceSlitOff when Mario leaves Paper Mode while in his roll motion.
 */
void U_allPartySlitOffReq(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && ((party->flags & PARTY_FLAG_PAPER_MODE) || (party->flags2 & PARTY_DISP_FLAG_SLIT))) {
        party->flags2 &= ~(PARTY_DISP_FLAG_HALF_TURN_MIRRORED | PARTY_DISP_FLAG_HALF_TURN | PARTY_DISP_FLAG_SLIT | PARTY_DISP_FLAG_SLIT_FLIP);
        partyPaperOff(party);
        party->flags &= ~(PARTY_FLAG_PAPER_MODE | PARTY_FLAG_MOT_SLIT_FLOOR);
        party->slitOn = 0;
        partyChgPoseId(party, 1);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && ((party->flags & PARTY_FLAG_PAPER_MODE) || (party->flags2 & PARTY_DISP_FLAG_SLIT))) {
        party->flags2 &= ~(PARTY_DISP_FLAG_HALF_TURN_MIRRORED | PARTY_DISP_FLAG_HALF_TURN | PARTY_DISP_FLAG_SLIT | PARTY_DISP_FLAG_SLIT_FLIP);
        partyPaperOff(party);
        party->flags &= ~(PARTY_FLAG_PAPER_MODE | PARTY_FLAG_MOT_SLIT_FLOOR);
        party->slitOn = 0;
        partyChgPoseId(party, 1);
    }
}

#endif
/**
 * Ends Paper Mode on one partner at once, facing left or right from its direction, and resets its pose.
 * Used when a partner ability or ride starts, in 8-bit mode and by Vivian's ability (party.c, party_vivian.c).
 */
void L_partyForceSlitOff(PartyEntry* party) {
    if ((party->flags & PARTY_FLAG_PAPER_MODE) || (party->flags2 & PARTY_DISP_FLAG_SLIT)) {
        party->displayDirection = revise360(party->targetDir - party->camDir) >= 180.0f ? 0.0f : 180.0f;
        party->displayDirectionTarget = party->displayDirection;
        party->moveDir = revise360(270.0f - party->displayDirection);
        party->targetDir = party->moveDir;
        party->flags2 &= ~(PARTY_DISP_FLAG_HALF_TURN_MIRRORED | PARTY_DISP_FLAG_HALF_TURN | PARTY_DISP_FLAG_SLIT | PARTY_DISP_FLAG_SLIT_FLIP);
        partyPaperOff(party);
        party->flags &= ~(PARTY_FLAG_PAPER_MODE | PARTY_FLAG_MOT_SLIT_FLOOR);
        party->slitOn = 0;
        partyChgPoseId(party, 1);
    }
}

/**
 * The partner reached a Paper Mode floor grate in Mario's footmarks:
 * enters Paper Mode (unless Mario is being normalized)
 * and marks it to slip through the floor (party_slit's fall steps).
 */
void partyChgMotSlitFloor(PartyEntry* party) {
    if (party->flags & PARTY_FLAG_MOT_SLIT_FLOOR) {
        return;
    }
    if (!(party->playerPtr->trigFlags & MARIO_TRIG_FLAG_NORMALIZING)) {
        party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
        party->slitOn = 1;
    }
    party->flags |= PARTY_FLAG_MOT_SLIT_FLOOR;
}

#if VERSION >= VERSION_US
/** US: evt_mario_normalize takes the partner out of Paper Mode and clears slitOn. */
void partySlitReset(PartyEntry* party) {
    if (party) {
        if (party->slitOn == 1) {
            L_partyForceSlitOff(party);
        }
        party->slitOn = 0;
    }
}

#endif
/**
 * Per-frame Paper Mode state for a partner while slitOn is 1:
 * turns sideways ("p_slit" paper animation), walks sideways, slips down through floor grates,
 * and turns back when Mario leaves Paper Mode and no slit wall is in the way.
 * Returns FALSE on the frame the turn completes.
 * The US release also joins Mario's Paper Mode on its own and checks for walls on both sides
 * before turning back.
 */
static BOOL party_slit(PartyEntry* party) {
    BOOL ret = TRUE;
    MarioWork* mario;
    f32 a;

    mario = party->playerPtr;
#if VERSION >= VERSION_US
    // US: a partner not yet in slit mode joins in while Mario is on a slit floor
    if (party->slitOn != 1) {
        if (mario->flags & MARIO_FLAG_PAPER_MODE) {
            if (mario->trigFlags & MARIO_TRIG_FLAG_NORMALIZING) {
                return TRUE;
            }
            party->trigFlags |= PARTY_TRIG_FLAG_CHG_SLIT;
            party->slitOn = 1;
        } else {
            return TRUE;
        }
    }
#else
    if (party->slitOn != 1) {
        return TRUE;
    }
#endif
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_SLIT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_SLIT;
        party->flags2 |= PARTY_DISP_FLAG_SLIT;
        partyPaperOn(party, "p_slit");
        partyChgPaper(party, "PM_S_1A");
        party->moveFrames = 30;
        partyForceSetSpd(party, 0.0f);
        if (revise360(party->targetDir - mario->targetYaw) <= 180.0f) {
            party->flags2 &= ~PARTY_DISP_FLAG_SLIT_FLIP;
            party->slitStep = 0;
        } else {
            party->flags2 |= PARTY_DISP_FLAG_SLIT_FLIP;
            party->slitStep = 2;
        }
    }
    switch (party->slitStep) {
        case 0:
            if (--party->moveFrames < 0) {
                party->flags |= PARTY_FLAG_PAPER_MODE;
                party->displayDirection = 270.0f;
                party->displayDirectionTarget = party->displayDirection;
                partyChgPaper(party, "PM_S_1B");
                if (!(party->flags & PARTY_FLAG_MOT_SLIT_FLOOR)) {
                    party->slitStep = 10;
                    ret = FALSE;
                } else {
                    party->slitStep = 20;
                }
            }
            break;
        case 2:
            if (--party->moveFrames < 0) {
                party->flags |= PARTY_FLAG_PAPER_MODE;
                party->displayDirection = 270.0f;
                party->displayDirectionTarget = party->displayDirection;
                partyChgPaper(party, "PM_S_1B");
                if (!(party->flags & PARTY_FLAG_MOT_SLIT_FLOOR)) {
                    party->slitStep = 10;
                    ret = FALSE;
                } else {
                    party->slitStep = 20;
                }
            }
            break;
        case 10:
            if (!party->moveSpeed) {
                partyChgPaper(party, "PM_S_1B");
                party->displayDirection = 270.0f;
            } else {
                if (revise360(party->targetDir - mario->targetYaw) >= 180.0) {
                    party->flags2 |= PARTY_DISP_FLAG_SLIT_FLIP;
                } else {
                    party->flags2 &= ~PARTY_DISP_FLAG_SLIT_FLIP;
                }
                party->displayDirection = (party->flags2 & PARTY_DISP_FLAG_SLIT_FLIP) ? 280.0f : 260.0f;
                a = revise360(party->targetDir - mario->targetYaw);
                if (a >= 315.0f || a <= 45.0f || (a >= 135.0f && a <= 225.0f)) {
                    partyChgPaper(party, "PM_S_1E");
                } else {
                    partyChgPaper(party, "PM_S_1D");
                }
            }
#if VERSION >= VERSION_US
            if (!partyChkBetweenWalls(party, party->position) && !(mario->flags & MARIO_FLAG_PAPER_MODE) &&
                !(hitGetAttr(party->hitobjFront) & HIT_ATTR_PAPER_SLIT) && !(hitGetAttr(party->hitobjPush) & HIT_ATTR_PAPER_SLIT)) {
                party->slitStep = 40;
            }
#else
            if (!(mario->flags & MARIO_FLAG_PAPER_MODE) && !(hitGetAttr(party->hitobjFront) & HIT_ATTR_PAPER_SLIT) &&
                !(hitGetAttr(party->hitobjPush) & HIT_ATTR_PAPER_SLIT)) {
                party->slitStep = 40;
            }
#endif
            break;
    }
    switch (party->slitStep) {
        case 20:
            partyChgPaper(party, "PM_S_1H");
            party->flags |= PARTY_FLAG_FORCE_FALL;
            party->flags |= PARTY_FLAG_IS_FALLING;
            party->moveFrames = 20;
            partyForceSetSpd(party, 0.0f);
            party->slitStep = 21;
            break;
        case 21:
            party->displayDirection = revise360(party->targetDir - party->camDir) <= 180.0f ? 260.0f : 280.0f;
            party->position.y += -3.0f;
            if (--party->moveFrames <= 0) {
                party->slitStep = 22;
            }
            break;
        case 22:
            party->slitStep = 10;
            party->flags &= ~PARTY_FLAG_FORCE_FALL;
            marioClearSlitFloor();
            break;
    }
    switch (party->slitStep) {
        case 40:
            partyChgPaper(party, "PM_S_1C");
            party->moveFrames = 30;
            party->slitStep = 41;
            party->displayDirection = revise360(party->targetDir - mario->targetYaw) >= 180.0f ? 0.0f : 180.0f;
            party->displayDirectionTarget = party->displayDirection;
        case 41:
            if (--party->moveFrames <= 0) {
                party->slitStep = 42;
            }
            break;
        case 42:
            party->flags2 &= ~(PARTY_DISP_FLAG_HALF_TURN_MIRRORED | PARTY_DISP_FLAG_HALF_TURN | PARTY_DISP_FLAG_SLIT | PARTY_DISP_FLAG_SLIT_FLIP);
            partyPaperOff(party);
            party->flags &= ~(PARTY_FLAG_PAPER_MODE | PARTY_FLAG_MOT_SLIT_FLOOR);
            party->slitOn = 0;
            break;
    }
    return ret;
}

/**
 * A roll state like Mario's tube mode ("p_roll" paper animation, PM_R_1A/1B) for slitOn 2,
 * spinning with speed and ending at slitStep 100; returns FALSE while ending.
 * Nothing in the tree sets slitOn to 2, so as built it returns TRUE at once.
 * Guess: an unused partner tube mode.
 */
static BOOL party_roll(PartyEntry* party) {
    BOOL ret = TRUE;
    f32 d;
    f32 x;
    f32 t;

    if (party->slitOn != 2) {
        return TRUE;
    }
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_SLIT) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_SLIT;
        partyPaperOn(party, "p_roll");
        partyChgPaper(party, "PM_R_1A");
        partyChgPoseId(party, 0);
        party->rotOfs.x = -6.0f;
        party->rotOfs.y = 6.0f;
        party->dispOfs.x = 6.0f;
        party->dispOfs.y = 2.0f;
        party->moveFrames = 0x41;
        party->slitStep = 0;
        partyForceSetSpd(party, 0.0f);
    }
    switch (party->slitStep) {
        case 0:
            party->moveFrames--;
            if (party->moveFrames <= 0) {
                partyChgPaper(party, "PM_R_1B");
                party->slitStep = 10;
            }
            break;
        case 10:
            party->displayDirection = revise360(270.0f - party->targetDir);
            if (revise360(party->moveDir + party->displayDirection) > 180.0f) {
                party->rotation = revise360(7.0f * party->moveSpeed + party->rotation);
            } else {
                party->rotation = revise360(party->rotation - 7.0f * party->moveSpeed);
            }
            break;
    }
    switch (party->slitStep) {
        case 100:
            party->moveSpeed = 0.0f;
            party->rot.x = 0.0f;
            party->rotation = 0.0f;
            party->rotOfs.x = 0.0f;
            party->rotOfs.y = 0.0f;
            party->dispOfs.x = party->targetDir < 180.0f ? 3.0f : -3.0f;
            party->dispOfs.y = 0.0f;
            party->moveFrames = 0x41;
            party->slitStep = 101;
            partyChgPaper(party, "PM_R_1C");
            partyPaperLightOff(party);
        case 101:
            ret = FALSE;
            party->moveFrames--;
            if (party->moveFrames > 0) {
                if (party->targetDir < 180.0f) {
                    x = 0.1f * (90.0f - party->displayDirection);
                    x += party->displayDirection;
                    if (__fabsf(90.0f - x < 1.0f)) {
                        x = 90.0f;
                    }
                    party->displayDirection = x;
                    party->displayDirectionTarget = x;
                } else {
                    x = 0.1f * (270.0f - party->displayDirection);
                    x += party->displayDirection;
                    if (__fabsf(270.0f - x < 1.0f)) {
                        x = 270.0f;
                    }
                    party->displayDirection = x;
                    party->displayDirectionTarget = x;
                }
            } else {
                ret = TRUE;
                if (party->targetDir >= 180.0f) {
                    party->displayDirection = 0.0f;
                    party->displayDirectionTarget = 0.0f;
                    party->moveDir = 270.0f;
                    party->targetDir = 270.0f;
                } else {
                    party->displayDirection = 180.0f;
                    party->displayDirectionTarget = 180.0f;
                    party->moveDir = 90.0f;
                    party->targetDir = 90.0f;
                }
                party->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
                party->dispOfs = (Vec){0.0f, 0.0f, 0.0f};
                party->slitOn = 0;
                party->flags &= ~PARTY_FLAG_PAPER_MODE;
                party->flags2 &= ~PARTY_DISP_FLAG_SLIT;
                party->flags &= ~PARTY_FLAG_POSE_TILTED;
                party->flags2 &= ~PARTY_DISP_FLAG_DIR_LOCK;
                party->flags2 &= ~PARTY_DISP_FLAG_NO_MIRROR;
                party->slitStep = 100;
                partyPaperOff(party);
            }
            break;
    }
    return ret;
}

/**
 * Close-follow distance: 18 for walking partners; 30 for Flurrie and Vivian, 8 during a door move.
 * Any other flying partner gets an unset value.
 */
static f32 partyStayDist(PartyEntry* party) {
    f32 d;
    if (party->moveKind == 0) {
        d = 18.0f;
    } else if (party->currentMemberId == PARTY_MEMBER_FLURRIE) {
        if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
            d = 8.0f;
        } else {
            d = 30.0f;
        }
    } else if (party->currentMemberId == PARTY_MEMBER_VIVIAN) {
        if (party->trigFlags & PARTY_TRIG_FLAG_DOOR_MOVE) {
            d = 8.0f;
        } else {
            d = 30.0f;
        }
    }
    return d;
}

/** Height a flying partner hovers above its target: 5, or 1 in 8-bit mode. */
static f32 partyHomingOff(PartyEntry* party) {
    f32 off = 5.0f;
    if (party->flags2 & PARTY_DISP_FLAG_FAMICOM) {
        off = 1.0f;
    }
    return off;
}

/**
 * Floor point 0.75 partner widths ahead in direction dir, rounded to 0.001, written to out;
 * returns its hit attributes, or 0 with out = the partner's position when there is none.
 * Probes from at most gnd_probe_dy above the partner, staying under any ceiling found in front.
 */
static s32 getFrontFloor(PartyEntry* party, Vec* out, f32 dir) {
    f32 s2, c2;
    HitCheckQuery q2;
    HitCheckQuery q;
    f32 c, s;
    f32 r;
    f32 probeDy;
    f32 y;
    f32 rf;
    s32 i;
    HitEntry* hit;

    r = 2.0f * party->width / 3.0f;
    q.targetDir = (Vec){0.0f, 1.0f, 0.0f};
    probeDy = gnd_probe_dy;
    sincosf(&s, &c, dir);
    for (i = 0; i < 3; i++) {
        q.targetPos.x = party->position.x + (f32)i * (s * r);
        q.targetPos.z = party->position.z + (f32)i * (c * r);
        q.targetPos.y = party->position.y + party->height;
        q.targetDistance = 100.0f;
        if (hitCheckVecFilter(&q, NULL)) {
            if (sqrtf(q.hitNormal.x * q.hitNormal.x + q.hitNormal.z * q.hitNormal.z) < 45.0f) {
                y = q.hitPos.y;
                goto found;
            }
        }
    }
    y = -2000.0f;
found:
    if (y > -2000.0f) {
        f32 t = party->position.y + probeDy;
        f32 u = y - 2.0f;
        if (t < u) {
            q2.targetPos.y = t;
        } else {
            q2.targetPos.y = u;
        }
    } else {
        q2.targetPos.y = party->position.y + probeDy;
    }
    r = 0.75f * party->width;
    sincosf(&s2, &c2, dir);
    q2.targetPos.x = s2 * r + party->position.x;
    q2.targetPos.z = c2 * r + party->position.z;
    q2.targetDistance = 300.0f;
    q2.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q2, NULL);
    if (!hit) {
        out->x = party->position.x;
        out->y = party->position.y;
        out->z = party->position.z;
        return 0;
    }
    rf = q2.hitPos.x >= 0.0f ? 0.5f : -0.5f;
    out->x = (s32)((1000.0f * q2.hitPos.x) + rf) / 1000.0f;
    rf = q2.hitPos.y >= 0.0f ? 0.5f : -0.5f;
    out->y = (s32)((1000.0f * q2.hitPos.y) + rf) / 1000.0f;
    rf = q2.hitPos.z >= 0.0f ? 0.5f : -0.5f;
    out->z = (s32)((1000.0f * q2.hitPos.z) + rf) / 1000.0f;
    return hitGetAttr(hit);
}

/** Unused: sets a hit query's direction to straight down. */
static inline void partyDownDirX(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}

/** Floor height 40 units from u in direction md (probed from gnd_probe_dy up), rounded to 0.001, or -2000. */
static f32 partyGetDirGndY(Vec u, f32 md) {
    f32 k = 40.0f;
    HitCheckQuery q2;
    HitEntry* hit;
    f32 s2, c2;
    f32 gy;
    f32 a;
    gy = gnd_probe_dy;
    sincosf(&s2, &c2, md);
    q2.targetPos = u;
    q2.targetPos.x = s2 * k + q2.targetPos.x;
    q2.targetPos.z = c2 * k + q2.targetPos.z;
    q2.targetPos.y = q2.targetPos.y + gy;
    q2.targetDistance = 1000.0f;
    q2.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q2, NULL);
    if (hit) {
        a = q2.hitPos.y >= 0.0f ? 0.5f : -0.5f;
        gy = (s32)((1000.0f * q2.hitPos.y) + a) / 1000.0f;
        hitGetAttr(hit);
    } else {
        gy = -2000.0f;
    }
    return gy;
}

/** Floor height below (x, y + gnd_probe_dy, z), rounded to 0.01, or -2000 when there is none. */
static f32 partyGetGndY(f32 x, f32 y, f32 z) {
    f32 r;
    f32 hx, hy, hz, dist, nx, ny, nz;
    HitEntry* hit;
    y += gnd_probe_dy;
    dist = 1000.0f;
    hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, x, y, z, 0.0f, -1.0f, 0.0f);
    if (!hit) {
        r = -2000.0f;
    } else {
        r = (s32)(100.0f * hy + 0.5f) / 100.0f;
        hitGetAttr(hit);
    }
    return r;
}

/**
 * Hit attributes of the floor 20 units ahead in direction dir (probed from 20 up, 40 down), 0 if none.
 * Homing walk uses it to skip footmarks over 0x800 floors.
 */
static u32 partyGetFrontAttr(PartyEntry* party, f32 dir) {
    HitCheckQuery q;
    HitEntry* hit;
    f32 s, c;
    sincosf(&s, &c, dir);
    q.targetDistance = 40.0f;
    q.targetPos.x = 20.0f * s + party->position.x;
    q.targetPos.z = 20.0f * c + party->position.z;
    q.targetPos.y = 20.0f + party->position.y;
    q.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q, NULL);
    return hit ? hitGetAttr(hit) : 0;
}

/**
 * Hit attributes of the floor 40 units ahead along targetDir (probed from 40 up, 100 down), 0 if none.
 * Homing walk does not step forward when it is 0x200 (water).
 */
static inline u32 partyGetFrontAttrFar(PartyEntry* party) {
    HitCheckQuery q;
    HitEntry* hit;
    f32 s, c;
    f32 k = 40.0f;
    sincosf(&s, &c, party->targetDir);
    q.targetDistance = 100.0f;
    q.targetPos.x = s * k + party->position.x;
    q.targetPos.z = c * k + party->position.z;
    q.targetPos.y = party->position.y + k;
    q.targetDir = (Vec){0.0f, -1.0f, 0.0f};
    hit = hitCheckVecFilter(&q, NULL);
    return hit ? hitGetAttr(hit) : 0;
}

/** Unused: sets a hit query's direction to straight down. */
static inline void partyDownDirY(HitCheckQuery* q) {
    q->targetDir = (Vec){0.0f, -1.0f, 0.0f};
}

/**
 * While Mario has control, pulls a partner that has left the screen (more than 100 px past the sides or 650 px
 * down) back toward Mario step by step onto dry floor until it is on screen, and clears the footmarks.
 * A partner right under Mario but far down the screen is put at its appear position instead.
 */
static void party_force_reset_outofscreen(PartyEntry* party) {
    MarioWork* m2;
    s32 i;
    s32 margin;
    s32 j;
    MarioWork* mario = party->playerPtr;
    f32 speed;
    f32 y;
    f32 up;
    HitEntry* hit;
    f32 dist;
    f32 sx, sy, sz;
    Vec pos;
    Vec start;
    Vec dir;
    Vec hitPos;
    Vec nrm;

    if (marioCtrlOffChk()) {
        return;
    }
    if (marioKeyOffChk()) {
        return;
    }
    marioGetScreenPos(party->position, &sx, &sy, &sz);
    if (distABf(mario->position.x, mario->position.z, party->position.x, party->position.z) < 20.0f &&
        sy > 800.0f) {
        partyGetAppearPos3(party, &pos);
        party->position = pos;
        return;
    }
    margin = 100;
    if (-100.0f <= sx && sx <= 700.0f && sy <= 650.0f) {
        return;
    }
    if (!(party->flags & PARTY_FLAG_IS_PARTNER)) {
        partyClearFootmark();
    } else {
        partyClearFootmark();
    }
    m2 = party->playerPtr;
    i = 0;
    pos = party->position;
    if (party->moveKind == 0) {
        speed = party->width;
    } else if (party->currentMemberId == PARTY_MEMBER_FLURRIE) {
        speed = 10.0f;
        margin = 70;
    } else {
        speed = 10.0f;
        margin = 50;
    }
    {
        Vec d = {0.0f, -1.0f, 0.0f};
        dir = d;
    }
    while (TRUE) {
        marioGetScreenPos(pos, &sx, &sy, &sz);
        if ((f32)-margin <= sx && sx <= (f32)(margin + 600)) {
            party->position = pos;
            return;
        }
        if (i > 100) {
            return;
        }
        {
            f32 a = angleABf(pos.x, pos.z, m2->position.x, m2->position.z);
            movePos(&pos.x, &pos.z, speed, a);
        }
        up = 200.0f;
        j = 0;
        y = pos.y;
        while (TRUE) {
            dist = 300.0f;
            start = pos;
            start.y += up;
            hit = partyHitCheck(party, &start, &dir, &hitPos, &nrm, &dist);
            if (hit) {
                if (!partyChkHitAttr200(hit)) {
                    y = hitPos.y;
                }
            } else {
                y = m2->position.y;
            }
            start.y = y;
            marioGetScreenPos(start, &sx, &sy, &sz);
            if (sy > 100.0f) {
                dist = 100.0f;
                start = pos;
                if (pos.y + 74.0f > y) {
                    start.y += 74.0f;
                    hit = partyHitCheck(party, &start, &dir, &hitPos, &nrm, &dist);
                    if (hit && !partyChkHitAttr200(hit)) {
                        y = hitPos.y;
                    }
                }
                break;
            }
            if (++j > 4) {
                break;
            }
            up -= 50.0f;
            if (up < 0.0f) {
                up = 0.0f;
            }
        }
        pos.y = y;
        i++;
    }
}

/**
 * Rogueport (gor_01): when Mario stands on one floor of a house and the partner on the floor above it,
 * moves the partner to (122, 130, -313). Guess: works around a partner stuck on the upper floor.
 */
static void partyGorFix(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    if (!strcmp(gp->currentMapName, "gor_01") && mario->hitobjStandOn && party->hitobjStandOn &&
        !strcmp(hitGetName(mario->hitobjStandOn), "A_ie_03_yuka_f1_C") && !strcmp(hitGetName(party->hitobjStandOn), "A_ie_03_yuka_f2_C")) {
        Vec fix = {122.0f, 130.0f, -313.0f};
        party->position = fix;
    }
}

/**
 * Ms. Mowz's sniffing pose (PCH_A2_1) for 30 frames,
 * when chuchu_searchObject finds an item or hidden treasure within 150 units of Mario.
 */
static void partyPoseA2(PartyEntry* party) {
    partyChgPose(party, "PCH_A2_1");
    party->useMotionId = 1;
    party->moveFrames = 30;
}
#endif
