#include "party.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "mario/mario.h"
#include "system.h"
#include <dolphin/types.h>
#include <string.h>
#include <dolphin/mtx.h>

extern MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);

#include "mario/mario_party.h"
#include "mario/mario_sbr.h"

extern int __float_nan[];

extern double sin(double);
extern double cos(double);
extern f32 partyGetHeight(PartyEntry* party);
extern f32 partyToMovedir(PartyEntry* party, f32 angle);


extern HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
extern s32 yoshiGetStatus(void);

#define PF(p, off) (*(f32*)((u8*)(p) + (off)))

extern void partyChgMot(PartyEntry* party, s32 mot);
HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth);
extern HitEntry* partySearchGround(PartyEntry* party, f32 a, f32 b);
HitEntry* partyChkFrontStep(PartyEntry* party, f32 range, f32* outY, f32* outDist, f32* outAng);
extern HitEntry* partyChkFrontStep(PartyEntry* party, f32 a, f32* x, f32* y, f32* z);

#ifdef NONMATCHING
BOOL chkfilter(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    marioGetPtr();
    if (entry->attributes & 0x80080) {
        return TRUE;
    }
    if (entry->attributes & 0x800004) {
        return FALSE;
    }
    if (!(entry->attributes & 0x80000000)) {
        return TRUE;
    }
    mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock") || !strcmp(mobj->animName, "MOBJ_HiddenBadgeBlock") ||
        !strcmp(mobj->animName, "MOBJ_Hidden10CountBlock")) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL chkfilterYoshi(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    marioGetPtr();
    if (entry->attributes & 0x80080) {
        return TRUE;
    }
    if (entry->attributes & 0x800000) {
        return TRUE;
    }
    if (entry->attributes & 0x4) {
        return FALSE;
    }
    if (!(entry->attributes & 0x80000000)) {
        return TRUE;
    }
    mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock") || !strcmp(mobj->animName, "MOBJ_HiddenBadgeBlock") ||
        !strcmp(mobj->animName, "MOBJ_Hidden10CountBlock")) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL chkfilterNokotaro(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    marioGetPtr();
    if (entry->attributes & 0x800005) {
        return FALSE;
    }
    if (entry->attributes & 0x80080) {
        return TRUE;
    }
    if (!(entry->attributes & 0x80000000)) {
        return TRUE;
    }
    mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock") || !strcmp(mobj->animName, "MOBJ_HiddenBadgeBlock") ||
        !strcmp(mobj->animName, "MOBJ_Hidden10CountBlock")) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
static inline s32 party_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
#endif
#ifdef NONMATCHING
static inline f32 party_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (party_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif

#pragma fp_contract off
#ifdef NONMATCHING
static inline f32 party_sumsq(f32 x, f32 z) { return x * x + z * z; }
#endif
#pragma fp_contract reset

#ifdef NONMATCHING
static inline HitEntry* partyHitCheckInl(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    HitCheckQuery query;
    Vec d = *dir;
    HitEntry* hit;
    f32 rf;

    query.targetPos = *pos;
    query.targetDir = d;
    query.targetDistance = *dist;
    if (yoshiGetStatus()) {
        hit = hitCheckVecFilter(&query, chkfilterYoshi);
    } else if (party->currentMemberId == PARTY_MEMBER_KOOPS && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        hit = hitCheckVecFilter(&query, chkfilterNokotaro);
    } else {
        hit = hitCheckVecFilter(&query, chkfilter);
    }
    if (!hit) {
        return hit;
    }
    if (query.targetDistance >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    *dist = (s32)((1000.0f * query.targetDistance) + rf) / 1000.0f;
    if (query.hitPos.x >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    outPos->x = (s32)((1000.0f * query.hitPos.x) + rf) / 1000.0f;
    if (query.hitPos.y >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    outPos->y = (s32)((1000.0f * query.hitPos.y) + rf) / 1000.0f;
    if (query.hitPos.z >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    outPos->z = (s32)((1000.0f * query.hitPos.z) + rf) / 1000.0f;
    outNrm->x = query.hitNormal.x;
    outNrm->y = query.hitNormal.y;
    outNrm->z = query.hitNormal.z;
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    return partyHitCheckInl(party, pos, dir, outPos, outNrm, dist);
}
#endif


#ifdef NONMATCHING
static inline f32 partyNrmTo(Vec* n) {
    return angleABf(0.0f, 0.0f, party_sqrtf(n->x * n->x + n->z * n->z), -n->y);
}
#endif

#ifdef NONMATCHING
f32 partyNrmToAngle(Vec n) {
    return angleABf(0.0f, 0.0f, party_sqrtf(n.x * n.x + n.z * n.z), -n.y);
}
#endif

#ifdef NONMATCHING
void partyChkGnd(PartyEntry* party) {
    s32 attr;
    HitEntry* hit;
    f32 a, b, c;

    if (!(party->flags & 0x2000000)) {
        attr = 0;
        hit = partySearchGround(party, 11.0f, party->velY);
        if (hit) {
            attr = hitGetAttr(hit);
            if (attr & 0x200) {
                hit = NULL;
            }
        }
        party->field_138 = hit;
        party->flags &= ~0x80;
        if (hit == NULL) {
            party->flags &= ~0x2;
            partyChgMot(party, 3);
            party->gravity = -1.0f;
        } else {
            party->flags |= 0x2;
            if (attr & 0x100) {
                party->flags |= 0x80;
            } else {
                party->flags &= ~0x80;
            }
        }
        party->position.y = PF(party, 0xE4);
        if (!(party->flags & 0x30)) {
            partyChkFrontStep(party, 11.0f, &a, &b, &c);
            if (a - party->position.y >= 5.0f && PF(party, 0xE0) <= 30.0f) {
                PF(party, 0x120) = a;
                if (party->moveSpeed) {
                    partyChgMot(party, 6);
                }
            }
        }
    }
}
#endif

#ifdef NONMATCHING
static inline f32 partyNrmSet(PartyEntry* party, Vec n) {
    PF(party, 0xC4) = (s32)(angleABf(0.0f, 0.0f, 100.0f * n.z, 100.0f * n.y) - 180.0f);
    PF(party, 0xC8) = 0.0f;
    PF(party, 0xCC) = (s32)(angleABf(0.0f, 0.0f, 100.0f * n.x, 100.0f * n.y) - 180.0f);
    return partyNrmTo(&n);
}
#endif

#ifdef NONMATCHING
HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth) {
    HitEntry* hit;
    HitEntry* best;
    s32 i;
    f32 probeY, nsz, nsx, len, bestY, sx, sz, px, baseY, pz, gy, ox, oz, rad, d;
    Vec pos;
    Vec dir;
    Vec outPos, outNrm;
    f32 dist;

    if (party->flags & 0x2000000) {
        return NULL;
    }
    {
        Vec zero = {0.0f, 0.0f, 0.0f};
        *(Vec*)((u8*)party + 0xC4) = zero;
    }
    PF(party, 0xE0) = 0.0f;
    range = __fabsf(range); range += 0.1f;
    if (marioGetPtr()->currMotionId == 0x1A) {
        d = 5.0f;
    } else {
        d = 0.75f * partyGetHeight(party);
    }
    PF(party, 0xE4) = party->position.y;
    PF(party, 0xE8) = -1.0f;
    if (party->moveSpeed) {
        rad = party->targetDir;
    } else {
        rad = partyToMovedir(party, party->displayDirection);
    }
    rad = 3.1415927f * rad / 180.0f;
    nsz = (f32)sin(rad); sx = 0.375f * (party->width * nsz); nsz = (f32)cos(rad); sz = 0.375f * (party->width * -nsz);
    nsx = -sx;
    nsz = -sz;
    baseY = party->position.y;
    probeY = baseY + d;
    len = d + range;
    {
    {Vec d0 = {0.0f, -1.0f, 0.0f}; dir = d0;}
    best = NULL;
    px = party->position.x;
    pz = party->position.z;
    bestY = -10000.0f;
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            ox = 0.0f;
            oz = 0.0f;
        } else if (i == 1) {
            ox = sx;
            oz = sz;
        } else if (i == 2) {
            ox = nsz;
            oz = sx;
        } else if (i == 3) {
            ox = sz;
            oz = nsx;
        } else if (i == 4) {
            ox = nsx;
            oz = nsz;
        }
        pos.x = px + ox;
        pos.y = probeY;
        pos.z = pz + oz;
        dist = len;
        hit = partyHitCheckInl(party, &pos, &dir, &outPos, &outNrm, &dist);
        gy = outPos.y;
        if (hit) {
            if (partyNrmSet(party, outNrm) >= 50.0f) {
                hit = NULL;
            }
        }
        if (hit) {
            PF(party, 0xE0) = partyNrmSet(party, outNrm);
            if (gy < baseY && __fabsf(gy - baseY) >= 2.0f) {
                if (__fabsf(gy - baseY) > __fabsf(depth)) {
                    PF(party, 0xE8) = __fabsf(baseY - gy);
                } else if (gy > bestY) {
                    bestY = gy;
                    best = hit;
                }
            } else if (__fabsf(gy - baseY) <= 11.0f) {
                if (gy > bestY) {
                    bestY = gy;
                    best = hit;
                }
            }
        }
    }
    }
    if (best) {
        PF(party, 0xE4) = bestY;
        PF(party, 0xE8) = 0.0f;
        return best;
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry* partyChkFrontStep(PartyEntry* party, f32 range, f32* outY, f32* outDist, f32* outAng) {
    HitEntry* hit;
    f32 dx, sn, cs, h, ang, ox, oy, oz, gy;
    Vec pos, outPos, outNrm;
    f32 dist, rad;

    range += 0.01f;
    {
        Vec zero = {0.0f, 0.0f, 0.0f};
        *(Vec*)((u8*)party + 0xC4) = zero;
    }
    PF(party, 0xE0) = 0.0f;
    h = partyGetHeight(party);
    *outY = party->position.y;
    *outDist = -1.0f;
    if (party->moveSpeed) {
        ang = party->targetDir;
    } else {
        ang = toMovedir(party->displayDirection);
    }
    ang = revise360((s32)(0.5f + ang));
    dx = 0.265f * party->width;
    rad = 3.1415927f * ang / 180.0f;
    sn = (f32)sin(rad);
    cs = (f32)cos(rad);
    oy = party->position.y;
    ox = party->position.x;
    oz = party->position.z;
    {
        Vec p = {0.0f, 0.0f, 0.0f};
        Vec dir = {0.0f, -1.0f, 0.0f};
        f32 mx;
        f32 mz;
        mx = dx * sn;
        mz = dx * -cs;
        p.x = ox + mx;
        p.y = oy + h;
        p.z = oz + mz;
        pos = p;
        dist = h + range;
        hit = partyHitCheckInl(party, &pos, &dir, &outPos, &outNrm, &dist);
    }
    if (hit) {
        Vec n = outNrm;
        PF(party, 0xC4) = (s32)(angleABf(0.0f, 0.0f, 100.0f * n.z, 100.0f * n.y) - 180.0f);
        PF(party, 0xC8) = 0.0f;
        PF(party, 0xCC) = (s32)(angleABf(0.0f, 0.0f, 100.0f * n.x, 100.0f * n.y) - 180.0f);
        PF(party, 0xE0) = partyNrmTo(&n);
        gy = outPos.y;
        if (gy < oy && __fabsf(gy - oy) >= 2.0f) {
            *outDist = oy - gy;
            *outAng = angleABf(ox, oz, outPos.x, outPos.z);
        } else {
            *outY = gy;
            *outDist = 0.0f;
            *outAng = angleABf(ox, oz, outNrm.x, outNrm.z);
            return hit;
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
static inline void partyWallSlide(Vec* out, Vec n, f32 d, f32 sn, f32 cs) {
    Vec unused = {0.0f, 0.0f, 0.0f};
    f32 mx = sn * d;
    f32 mz = cs * d;
    f32 dot = mx * n.x + mz * n.z;
    out->x += 0.5f * (mx - dot * n.x);
    out->z += 0.5f * (mz - dot * n.z);
}
#endif

#ifdef NONMATCHING
HitEntry* partySearchWallFront(PartyEntry* party, Vec* pos, f32 dist, f32 ang) {
    Vec qpos;
    Vec qdir;
    Vec outPos;
    Vec bestNrm;
    Vec nrm;
    Vec v = {0.0f, 0.0f, 0.0f};
    f32 arr[4];
    f32 sn, cs, sn2, cs2;
    f32 bestD, d;
    f32 rd, maxD;
    HitEntry* best;
    HitEntry* hit;
    s32 i;

    sincosf(&sn, &cs, ang);
    arr[0] = 0.75f * partyGetHeight(party);
    arr[1] = 0.5f * partyGetHeight(party);
    if ((party->flags & 0x30) || yoshiGetStatus() == 2) {
        arr[2] = 1.0f;
    } else {
        arr[2] = 11.0f;
    }
    rd = 0.5f * party->width;
    best = NULL;
    maxD = rd + dist;
    bestD = maxD;
    do {
    qpos = *pos;
    {
    Vec dir1 = {0.0f, 0.0f, 0.0f};
    dir1.x = sn;
    dir1.z = cs;
    qdir = dir1;
    }
    for (i = 0; i < 3; i++) {
        d = maxD;
        qpos.y = pos->y + arr[i];
        hit = marioHitCheckVec(&qpos, &qdir, &outPos, &nrm, &d);
        if (hit) {
            if (best) {
                if (d < bestD) {
                    best = hit;
                    bestD = d;
                    bestNrm = nrm;
                }
            } else {
                best = hit;
                bestD = d;
                bestNrm = nrm;
            }
        }
    }
    if (best) {
        Vec nn;
        f32 dot;
        f32 mx, mz;
        f32 nz;
        nn = bestNrm;
        mx = sn * dist;
        mz = cs * dist;
        nz = nn.z;
        dot = mx * nn.x + mz * nz;
        v.x += 0.5f * (mx - dot * nn.x);
        v.z += 0.5f * (mz - dot * nz);
    }
    sincosf(&sn2, &cs2, ang + 45.0f);
    bestD = rd;
    qpos = *pos;
    {
    Vec dir2 = {0.0f, 0.0f, 0.0f};
    dir2.x = sn2;
    dir2.z = cs2;
    qdir = dir2;
    }
    for (i = 0; i < 3; i++) {
        bestD = rd;
        qpos.y = pos->y + arr[i];
        hit = marioHitCheckVec(&qpos, &qdir, NULL, NULL, &bestD);
        if (hit) {
            break;
        }
    }
    if (hit) {
        sincosf(&sn2, &cs2, ang - 45.0f);
        for (i = 0; i < 3; i++) {
            bestD = rd;
            qpos.y = pos->y + arr[i];
            {
            Vec dd = {0.0f, 0.0f, 0.0f};
            dd.x = sn2;
            dd.z = cs2;
            qdir = dd;
            }
            hit = marioHitCheckVec(&qpos, &qdir, NULL, NULL, &bestD);
        }
    }
    if (best) {
        if (!hit) {
            pos->x += v.x;
            pos->z += v.z;
        }
        return best;
    }
    if (!hit) {
        pos->x += dist * sn;
        pos->z += dist * cs;
    }
    return NULL;
    } while (0);
}
#endif

#ifdef NONMATCHING
HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 ang) {
    f32 sn, cs;
    f32 d, dy, hh;
    HitEntry* hit;
    Vec p, nrm;

    sincosf(&sn, &cs, ang);
    d = 0.5f * party->width + dist;
    hh = 0.75f * partyGetHeight(party);
    p = party->position;
    p.y += hh;
    {
    Vec dir = {0.0f, 0.0f, 0.0f};
    Vec outPos = {0.0f, 0.0f, 0.0f};
    dir.x = sn;
    dir.z = cs;
    hit = partyHitCheckInl(party, &p, &dir, &outPos, &nrm, &d);
    if (hit) {
        PF(party, 0xEC) = d;
        partyWallSlide(pos, nrm, dist, sn, cs);
        return hit;
    }
    dy = 11.0f;
    if (party->currentMemberId == PARTY_MEMBER_BOBBERY && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        dy = 1.0f;
    }
    p = party->position;
    d = 0.5f * party->width + dist;
    p.y += dy;
    hit = partyHitCheckInl(party, &p, &dir, &outPos, &nrm, &d);
    if (hit) {
        if (partyNrmTo(&nrm) >= 45.0f) {
            PF(party, 0xEC) = d;
            partyWallSlide(pos, nrm, dist, sn, cs);
            return hit;
        }
    }
    }
    PF(party, 0xEC) = -1.0f;
    pos->x += dist * sn;
    pos->z += dist * cs;
    return NULL;
}
#endif

#ifdef NONMATCHING
void partySearchHead(PartyEntry *party, Vec *pos, f32 *dist, f32 angle)
{
  f32 lx;
  f32 ly;
  f32 lz;
  f32 best;
  f32 oz;
  f32 ox;
  Vec t;
  f32 s;
  f32 c;
  volatile f32 px;
  volatile f32 py;
  volatile f32 pz;
  f32 d0;
  f32 nz0;
  f32 ny0;
  f32 nx0;
  float new_var;
  f32 hz0;
  f32 hy0;
  f32 hx0;
  f32 d1;
  f32 nz1;
  f32 ny1;
  f32 nx1;
  f32 hz1;
  f32 hy1;
  f32 hx1;
  f32 d2;
  f32 nz2;
  f32 ny2;
  f32 nx2;
  f32 hz2;
  f32 hy2;
  f32 hx2;
  f32 d3;
  f32 nz3;
  f32 ny3;
  f32 nx3;
  f32 hz3;
  f32 hy3;
  f32 hx3;
  HitEntry *hit;
  f32 zero = 0.0f;
  f32 one = 1.0f;
  oz = party->width * 0.3f;
  sincosf(&s, &c, angle);
  px = pos->x;
  ox = (-oz) * c;
  oz = oz * s;
  py = pos->y;
  pz = pos->z;
  best = *dist;
  {
    lx = px + oz;
    lz = pz + ox;
    ly = py;
    t = (Vec){lx, ly, lz};
    d0 = best;
    if ((t.z && t.z) && t.z)
    {
    }
    new_var = 10.0f;
    hit = hitCheckFilter((void *) 0, &hx0, &hy0, &hz0, &d0, &nx0, &ny0, &nz0, t.x, t.y + new_var, t.z, zero, one, zero);
    if (hit && (best >= d0))
    {
      best = d0;
    }
  }
  if (!hit)
  {
    lx = px - oz;
    ly = py;
    lz = pz - ox;
    t = (Vec){lx, ly, lz};
    d1 = best;
    hit = hitCheckFilter((void *) 0, &hx1, &hy1, &hz1, &d1, &nx1, &ny1, &nz1, t.x, t.y + new_var, t.z, zero, one, zero);
    if (hit && (best >= d1))
    {
      best = d1;
    }
    if (!hit)
    {
      lx = px + ox;
      ly = py;
      lz = pz + oz;
      t = (Vec){lx, ly, lz};
      if ((t.z && t.z) && t.z) { }
      d2 = best;
      new_var = 10.0f;
      hit = hitCheckFilter((void *) 0, &hx2, &hy2, &hz2, &d2, &nx2, &ny2, &nz2, t.x, t.y + new_var, t.z, zero, one, zero);
      if (hit && (best >= d2))
      {
        best = d2;
      }
      if (!hit)
      {
        lx = px - ox;
        ly = py;
        lz = pz - oz;
        t = (Vec){lx, ly, lz};
        d3 = best;
        hit = hitCheckFilter((void *) 0, &hx3, &hy3, &hz3, &d3, &nx3, &ny3, &nz3, t.x, t.y + new_var, t.z, zero, one, zero);
        if (hit && (best >= d3))
        {
          best = d3;
        }
      }
    }
  }
  if (hit)
  {
    pos->x = lx;
    pos->y = ly;
    pos->z = lz;
    *dist = best;
  }
  if (!hit)
  {
    pos->x = lx;
    pos->y = ly;
    pos->z = lz;
    *dist = 0.0f;
  }
}
#endif

#ifdef NONMATCHING
void partyHitStrippedPool(f32* f, s32 i) {
    f[0] = 10.0f;
    f[1] = 0.0f;
    f[2] = 1.0f;
    f[3] = 0.5f;
    f[4] = 100.0f;
    f[5] = (f32)i;
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): chkfilter (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".sdata2") const f32 float_10_8041b3e8 = 10.0f;
__declspec(section ".sdata2") const f32 float_0_8041b3ec = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041b3f0 = 1.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041b3f4 = 0.5f;
__declspec(section ".sdata2") const f32 float_100_8041b3f8 = 100.0f;
__declspec(section ".sdata2") const f32 float_0p3_8041b3fc = 0.3f;
__declspec(section ".sdata2") const f32 float_0p75_8041b400 = 0.75f;
__declspec(section ".sdata2") const f32 float_neg0p5_8041b404 = -0.5f;
__declspec(section ".sdata2") const f32 float_1000_8041b408 = 1000.0f;
__declspec(section ".sdata2") const f32 float_11_8041b40c = 11.0f;
__declspec(section ".sdata2") const f32 float_45_8041b410 = 45.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041b414 = -1.0f;
__declspec(section ".sdata2") const f32 float_0p01_8041b418 = 0.01f;
__declspec(section ".sdata2") const f32 float_0p265_8041b41c = 0.265f;
__declspec(section ".sdata2") const f32 float_3p1416_8041b420 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_8041b424 = 180.0f;
__declspec(section ".sdata2") const f32 float_2_8041b428 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041b42c = 0.1f;
__declspec(section ".sdata2") const f32 float_5_8041b430 = 5.0f;
__declspec(section ".sdata2") const f32 float_0p375_8041b434 = 0.375f;
__declspec(section ".sdata2") const f32 float_neg10000_8041b438 = -10000.0f;
__declspec(section ".sdata2") const f32 float_50_8041b43c = 50.0f;
__declspec(section ".sdata2") const f32 float_30_8041b440 = 30.0f;
__declspec(section ".sdata2") const u32 gap_09_8041B444_sdata2 = 0x00000000;
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802cd320[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd32c[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd338[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd344[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd350[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd35c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd368[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd374[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd380[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd38c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd398[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd3a4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd3b0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd3bc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd3c8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cd3d4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802cd3e0 = 4503601774854144;
__declspec(section ".rodata") const f64 double_0p5_802cd3e8 = 0.5;
__declspec(section ".rodata") const f64 double_3_802cd3f0 = 3;
__declspec(section ".rodata") const f64 double_0_802cd3f8 = 0;
__declspec(section ".rodata") const char str_802CD400[] = "MOBJ_HiddenHatenaBlock\000";
__declspec(section ".rodata") const char str_802CD418[] = "MOBJ_HiddenBadgeBlock\000\000";
__declspec(section ".rodata") const char str_802CD430[] = "MOBJ_Hidden10CountBlock";
#pragma force_active reset
void partySearchHead(PartyEntry *party, Vec *pos, f32 *dist, f32 angle);
HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
HitEntry* partySearchWallFront(PartyEntry* party, Vec* pos, f32 dist, f32 ang);
HitEntry* partyChkFrontStep(PartyEntry* party, f32 range, f32* outY, f32* outDist, f32* outAng);
HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth);
void partyChkGnd(PartyEntry* party);
f32 partyNrmToAngle(Vec n);
HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
BOOL chkfilterNokotaro(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilterYoshi(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilter(HitCheckQuery* query, HitEntry* entry);

asm void partySearchHead(PartyEntry *party, Vec *pos, f32 *dist, f32 angle) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stfd f26, 0xe0(r1)
	psq_st f26, 0xe8(r1), 0, 0
	stw r31, 0xdc(r1)
	stw r30, 0xd8(r1)
	stw r29, 0xd4(r1)
	lfs f0, 0xf4(r3)
	lis r3, vec3_802cd320@ha
	lfs f2, float_0p3_8041b3fc(r2)
	mr r29, r4
	mr r30, r5
	addi r31, r3, vec3_802cd320@l
	fmuls f27, f2, f0
	addi r3, r1, 0x88
	addi r4, r1, 0x84
	bl sincosf
	lfs f0, 0x0(r29)
	fneg f3, f27
	lfs f2, 0x84(r1)
	addi r4, r1, 0x5c
	stfs f0, 0x80(r1)
	addi r5, r1, 0x60
	lfs f0, 0x88(r1)
	lfs f1, 0x4(r29)
	fmuls f26, f3, f2
	fmuls f27, f27, f0
	lfs f0, 0x8(r29)
	lwz r11, 0x94(r31)
	addi r6, r1, 0x64
	stfs f1, 0x7c(r1)
	lwz r0, 0x98(r31)
	stfs f0, 0x78(r1)
	addi r7, r1, 0x74
	lfs f1, 0x80(r1)
	addi r8, r1, 0x68
	lfs f0, 0x78(r1)
	addi r9, r1, 0x6c
	lwz r12, 0x90(r31)
	fadds f31, f1, f27
	fadds f29, f0, f26
	stw r0, 0xb8(r1)
	lfs f30, 0x7c(r1)
	addi r10, r1, 0x70
	stw r11, 0xb4(r1)
	lfs f4, float_0_8041b3ec(r2)
	stfs f30, 0xb4(r1)
	li r3, 0x0
	lfs f28, 0x0(r30)
	fmr f6, f4
	stw r12, 0xb0(r1)
	lwz r11, 0xb4(r1)
	stfs f29, 0xb8(r1)
	lfs f0, float_10_8041b3e8(r2)
	stw r11, 0xc0(r1)
	lwz r0, 0xb8(r1)
	stfs f31, 0xb0(r1)
	lfs f1, 0xc0(r1)
	lwz r11, 0xb0(r1)
	stw r0, 0xc4(r1)
	fadds f2, f0, f1
	lfs f5, float_1_8041b3f0(r2)
	stw r11, 0xbc(r1)
	lfs f3, 0xc4(r1)
	stfs f28, 0x74(r1)
	lfs f1, 0xbc(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @1
	lfs f0, 0x74(r1)
	fcmpo cr0, f28, f0
	cror eq, gt, eq
	bne @1
	fmr f28, f0
	@1:
	cmplwi r3, 0x0
	bne @2
	lwz r3, 0xa0(r31)
	addi r4, r1, 0x40
	lfs f1, 0x80(r1)
	addi r5, r1, 0x44
	lfs f30, 0x7c(r1)
	addi r6, r1, 0x48
	stw r3, 0xa8(r1)
	fsubs f31, f1, f27
	lfs f0, 0x78(r1)
	addi r7, r1, 0x58
	lwz r0, 0xa4(r31)
	addi r8, r1, 0x4c
	lwz r12, 0x9c(r31)
	fsubs f29, f0, f26
	stfs f30, 0xa8(r1)
	lfs f4, float_0_8041b3ec(r2)
	addi r9, r1, 0x50
	stw r0, 0xac(r1)
	addi r10, r1, 0x54
	stw r12, 0xa4(r1)
	fmr f6, f4
	lwz r11, 0xa8(r1)
	li r3, 0x0
	stfs f29, 0xac(r1)
	lfs f0, float_10_8041b3e8(r2)
	stw r11, 0xc0(r1)
	lwz r0, 0xac(r1)
	stfs f31, 0xa4(r1)
	lfs f1, 0xc0(r1)
	lwz r11, 0xa4(r1)
	stw r0, 0xc4(r1)
	fadds f2, f0, f1
	lfs f5, float_1_8041b3f0(r2)
	stw r11, 0xbc(r1)
	lfs f3, 0xc4(r1)
	stfs f28, 0x58(r1)
	lfs f1, 0xbc(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @3
	lfs f0, 0x58(r1)
	fcmpo cr0, f28, f0
	cror eq, gt, eq
	bne @3
	fmr f28, f0
	@3:
	cmplwi r3, 0x0
	bne @2
	lwz r3, 0xac(r31)
	addi r4, r1, 0x24
	lfs f1, 0x80(r1)
	addi r5, r1, 0x28
	lfs f30, 0x7c(r1)
	addi r6, r1, 0x2c
	stw r3, 0x9c(r1)
	fadds f31, f1, f26
	lfs f0, 0x78(r1)
	addi r7, r1, 0x3c
	lwz r0, 0xb0(r31)
	addi r8, r1, 0x30
	lwz r12, 0xa8(r31)
	fadds f29, f0, f27
	stfs f30, 0x9c(r1)
	lfs f4, float_0_8041b3ec(r2)
	addi r9, r1, 0x34
	stw r0, 0xa0(r1)
	addi r10, r1, 0x38
	stw r12, 0x98(r1)
	fmr f6, f4
	lwz r11, 0x9c(r1)
	li r3, 0x0
	stfs f29, 0xa0(r1)
	lfs f0, float_10_8041b3e8(r2)
	stw r11, 0xc0(r1)
	lwz r0, 0xa0(r1)
	stfs f31, 0x98(r1)
	lfs f1, 0xc0(r1)
	lwz r11, 0x98(r1)
	stw r0, 0xc4(r1)
	fadds f2, f0, f1
	lfs f5, float_1_8041b3f0(r2)
	stw r11, 0xbc(r1)
	lfs f3, 0xc4(r1)
	stfs f28, 0x3c(r1)
	lfs f1, 0xbc(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @4
	lfs f0, 0x3c(r1)
	fcmpo cr0, f28, f0
	cror eq, gt, eq
	bne @4
	fmr f28, f0
	@4:
	cmplwi r3, 0x0
	bne @2
	lwz r3, 0xb8(r31)
	addi r4, r1, 0x8
	lfs f1, 0x80(r1)
	addi r5, r1, 0xc
	lfs f30, 0x7c(r1)
	addi r6, r1, 0x10
	stw r3, 0x90(r1)
	fsubs f31, f1, f26
	lfs f0, 0x78(r1)
	addi r7, r1, 0x20
	lwz r0, 0xbc(r31)
	addi r8, r1, 0x14
	lwz r12, 0xb4(r31)
	fsubs f29, f0, f27
	stfs f30, 0x90(r1)
	lfs f4, float_0_8041b3ec(r2)
	addi r9, r1, 0x18
	stw r0, 0x94(r1)
	addi r10, r1, 0x1c
	stw r12, 0x8c(r1)
	fmr f6, f4
	lwz r11, 0x90(r1)
	li r3, 0x0
	stfs f29, 0x94(r1)
	lfs f0, float_10_8041b3e8(r2)
	stw r11, 0xc0(r1)
	lwz r0, 0x94(r1)
	stfs f31, 0x8c(r1)
	lfs f1, 0xc0(r1)
	lwz r11, 0x8c(r1)
	stw r0, 0xc4(r1)
	fadds f2, f0, f1
	lfs f5, float_1_8041b3f0(r2)
	stw r11, 0xbc(r1)
	lfs f3, 0xc4(r1)
	stfs f28, 0x20(r1)
	lfs f1, 0xbc(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @2
	lfs f0, 0x20(r1)
	fcmpo cr0, f28, f0
	cror eq, gt, eq
	bne @2
	fmr f28, f0
	@2:
	cmplwi r3, 0x0
	beq @5
	stfs f31, 0x0(r29)
	stfs f30, 0x4(r29)
	stfs f29, 0x8(r29)
	stfs f28, 0x0(r30)
	@5:
	cmplwi r3, 0x0
	bne @6
	stfs f31, 0x0(r29)
	lfs f0, float_0_8041b3ec(r2)
	stfs f30, 0x4(r29)
	stfs f29, 0x8(r29)
	stfs f0, 0x0(r30)
	@6:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	psq_l f26, 0xe8(r1), 0, 0
	lfd f26, 0xe0(r1)
	lwz r31, 0xdc(r1)
	lwz r30, 0xd8(r1)
	lwz r0, 0x144(r1)
	lwz r29, 0xd4(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm HitEntry* partySearchFrontWall(PartyEntry* party, Vec* pos, f32 dist, f32 ang) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stw r31, 0xec(r1)
	stw r30, 0xe8(r1)
	stw r29, 0xe4(r1)
	stw r28, 0xe0(r1)
	fmr f30, f1
	lis r5, vec3_802cd320@ha
	fmr f1, f2
	mr r30, r3
	mr r31, r4
	addi r29, r5, vec3_802cd320@l
	addi r3, r1, 0x10
	addi r4, r1, 0xc
	bl sincosf
	lfs f1, float_0p5_8041b3f4(r2)
	mr r3, r30
	lfs f0, 0xf4(r30)
	fmadds f31, f1, f0, f30
	bl partyGetHeight
	lwz r0, 0x5c(r30)
	lfs f0, float_0p75_8041b400(r2)
	stw r0, 0x48(r1)
	fmuls f1, f0, f1
	lwz r3, 0x78(r29)
	lfs f0, 0x48(r1)
	lwz r0, 0x80(r29)
	fadds f0, f0, f1
	lwz r7, 0x58(r30)
	stw r3, 0x2c(r1)
	lfs f1, 0x10(r1)
	stfs f0, 0x48(r1)
	lfs f0, 0xc(r1)
	lwz r6, 0x60(r30)
	lwz r5, 0x7c(r29)
	stw r0, 0x34(r1)
	lwz r4, 0x48(r1)
	stfs f1, 0x2c(r1)
	stfs f0, 0x34(r1)
	lwz r3, 0x2c(r1)
	lwz r0, 0x34(r1)
	stw r7, 0x44(r1)
	stw r6, 0x4c(r1)
	stw r5, 0x30(r1)
	stw r7, 0x9c(r1)
	stw r4, 0xa0(r1)
	stw r6, 0xa4(r1)
	stw r3, 0xa8(r1)
	stw r5, 0xac(r1)
	stw r0, 0xb0(r1)
	stfs f31, 0xcc(r1)
	bl yoshiGetStatus
	cmpwi r3, 0x0
	beq @1
	lis r4, chkfilterYoshi@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterYoshi@l
	bl hitCheckVecFilter
	b @2
	@1:
	lbz r0, 0x31(r30)
	cmpwi r0, 0x2
	bne @3
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 23, 23
	beq @3
	lis r4, chkfilterNokotaro@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterNokotaro@l
	bl hitCheckVecFilter
	b @2
	@3:
	lis r4, chkfilter@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilter@l
	bl hitCheckVecFilter
	@2:
	cmplwi r3, 0x0
	bne @4
	b @5
	@4:
	lfs f1, 0xcc(r1)
	lfs f0, float_0_8041b3ec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_0p5_8041b3f4(r2)
	b @7
	@6:
	lfs f0, float_neg0p5_8041b404(r2)
	@7:
	lfs f5, float_1000_8041b408(r2)
	lis r0, 0x4330
	lfs f2, 0xc0(r1)
	fmadds f3, f5, f1, f0
	lfs f1, 0xc4(r1)
	lfs f0, 0xc8(r1)
	stw r0, 0xd8(r1)
	fctiwz f4, f3
	lfd f3, 0xc0(r29)
	stfs f1, 0x3c(r1)
	stfd f4, 0xd0(r1)
	lwz r0, 0xd4(r1)
	stfs f0, 0x40(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xdc(r1)
	lfd f1, 0xd8(r1)
	stfs f2, 0x38(r1)
	fsubs f0, f1, f3
	fdivs f31, f0, f5
	@5:
	cmplwi r3, 0x0
	beq @8
	stfs f31, 0xec(r30)
	lwz r0, 0x40(r1)
	lfs f0, 0xc(r1)
	stw r0, 0x28(r1)
	lwz r0, 0x38(r1)
	fmuls f5, f0, f30
	lfs f0, 0x10(r1)
	stw r0, 0x20(r1)
	lfs f6, 0x28(r1)
	fmuls f2, f0, f30
	lfs f1, 0x20(r1)
	fmuls f0, f5, f6
	lwz r0, 0x3c(r1)
	lfs f3, float_0p5_8041b3f4(r2)
	stw r0, 0x24(r1)
	fmadds f4, f2, f1, f0
	lfs f0, 0x0(r31)
	fnmsubs f2, f4, f1, f2
	fnmsubs f1, f4, f6, f5
	fmadds f0, f3, f2, f0
	stfs f0, 0x0(r31)
	lfs f0, 0x8(r31)
	fmadds f0, f3, f1, f0
	stfs f0, 0x8(r31)
	b @9
	@8:
	lbz r0, 0x31(r30)
	lfs f2, float_11_8041b40c(r2)
	cmpwi r0, 0x3
	bne @10
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 23, 23
	beq @10
	lfs f2, float_1_8041b3f0(r2)
	@10:
	lwz r0, 0x5c(r30)
	lwz r7, 0x58(r30)
	stw r0, 0x48(r1)
	lwz r6, 0x60(r30)
	lfs f0, 0x48(r1)
	lfs f1, 0xf4(r30)
	fadds f0, f0, f2
	lfs f2, float_0p5_8041b3f4(r2)
	lwz r4, 0x2c(r1)
	fmadds f31, f2, f1, f30
	lwz r3, 0x30(r1)
	stfs f0, 0x48(r1)
	lwz r0, 0x34(r1)
	lwz r5, 0x48(r1)
	stw r7, 0x44(r1)
	stw r6, 0x4c(r1)
	stw r7, 0x5c(r1)
	stw r5, 0x60(r1)
	stw r6, 0x64(r1)
	stw r4, 0x68(r1)
	stw r3, 0x6c(r1)
	stw r0, 0x70(r1)
	stfs f31, 0x8c(r1)
	bl yoshiGetStatus
	cmpwi r3, 0x0
	beq @11
	lis r4, chkfilterYoshi@ha
	addi r3, r1, 0x50
	addi r4, r4, chkfilterYoshi@l
	bl hitCheckVecFilter
	b @12
	@11:
	lbz r0, 0x31(r30)
	cmpwi r0, 0x2
	bne @13
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 23, 23
	beq @13
	lis r4, chkfilterNokotaro@ha
	addi r3, r1, 0x50
	addi r4, r4, chkfilterNokotaro@l
	bl hitCheckVecFilter
	b @12
	@13:
	lis r4, chkfilter@ha
	addi r3, r1, 0x50
	addi r4, r4, chkfilter@l
	bl hitCheckVecFilter
	@12:
	cmplwi r3, 0x0
	bne @14
	mr r28, r3
	b @15
	@14:
	lfs f1, 0x8c(r1)
	lfs f0, float_0_8041b3ec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @16
	lfs f0, float_0p5_8041b3f4(r2)
	b @17
	@16:
	lfs f0, float_neg0p5_8041b404(r2)
	@17:
	lfs f5, float_1000_8041b408(r2)
	lis r0, 0x4330
	lfs f2, 0x80(r1)
	mr r28, r3
	fmadds f3, f5, f1, f0
	lfs f1, 0x84(r1)
	lfs f0, 0x88(r1)
	stw r0, 0xd0(r1)
	fctiwz f4, f3
	lfd f3, 0xc0(r29)
	stfs f2, 0x38(r1)
	stfd f4, 0xd8(r1)
	lwz r0, 0xdc(r1)
	stfs f1, 0x3c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xd4(r1)
	lfd f1, 0xd0(r1)
	stfs f0, 0x40(r1)
	fsubs f0, f1, f3
	fdivs f31, f0, f5
	@15:
	cmplwi r28, 0x0
	beq @18
	lfs f0, 0x40(r1)
	lfs f2, 0x38(r1)
	fmuls f1, f0, f0
	lfs f0, float_0_8041b3ec(r2)
	fmadds f3, f2, f2, f1
	fcmpo cr0, f3, f0
	ble @19
	frsqrte f1, f3
	lfd f4, 0xc8(r29)
	lfd f2, 0xd0(r29)
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
	b @20
	@19:
	lfd f0, 0xd8(r29)
	fcmpo cr0, f3, f0
	bge @21
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @20
	@21:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @22
	bge @23
	cmpwi r3, 0x0
	beq @24
	b @23
	@22:
	clrlwi. r0, r4, 9
	beq @25
	li r0, 0x1
	b @26
	@25:
	li r0, 0x2
	b @26
	@24:
	clrlwi. r0, r4, 9
	beq @27
	li r0, 0x5
	b @26
	@27:
	li r0, 0x3
	b @26
	@23:
	li r0, 0x4
	@26:
	cmpwi r0, 0x1
	bne @20
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@20:
	lfs f1, float_0_8041b3ec(r2)
	lfs f0, 0x3c(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f0, float_45_8041b410(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @18
	stfs f31, 0xec(r30)
	mr r3, r28
	lwz r0, 0x40(r1)
	lfs f0, 0xc(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x38(r1)
	fmuls f5, f0, f30
	lfs f0, 0x10(r1)
	lfs f6, 0x1c(r1)
	stw r0, 0x14(r1)
	fmuls f2, f0, f30
	fmuls f0, f5, f6
	lwz r0, 0x3c(r1)
	lfs f1, 0x14(r1)
	lfs f3, float_0p5_8041b3f4(r2)
	fmadds f4, f2, f1, f0
	lfs f0, 0x0(r31)
	stw r0, 0x18(r1)
	fnmsubs f2, f4, f1, f2
	fnmsubs f1, f4, f6, f5
	fmadds f0, f3, f2, f0
	stfs f0, 0x0(r31)
	lfs f0, 0x8(r31)
	fmadds f0, f3, f1, f0
	stfs f0, 0x8(r31)
	b @9
	@18:
	lfs f0, float_neg1_8041b414(r2)
	li r3, 0x0
	stfs f0, 0xec(r30)
	lfs f1, 0x10(r1)
	lfs f0, 0x0(r31)
	fmadds f0, f30, f1, f0
	stfs f0, 0x0(r31)
	lfs f1, 0xc(r1)
	lfs f0, 0x8(r31)
	fmadds f0, f30, f1, f0
	stfs f0, 0x8(r31)
	@9:
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	lwz r31, 0xec(r1)
	lwz r30, 0xe8(r1)
	lwz r29, 0xe4(r1)
	lwz r0, 0x114(r1)
	lwz r28, 0xe0(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm HitEntry* partySearchWallFront(PartyEntry* party, Vec* pos, f32 dist, f32 ang) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stmw r26, 0xa8(r1)
	lis r5, vec3_802cd320@ha
	fmr f30, f2
	addi r31, r5, vec3_802cd320@l
	fmr f29, f1
	lwz r6, 0x48(r31)
	mr r27, r3
	lwz r5, 0x4c(r31)
	lwz r0, 0x50(r31)
	fmr f1, f30
	mr r26, r4
	stw r6, 0x60(r1)
	addi r3, r1, 0x1c
	addi r4, r1, 0x18
	stw r5, 0x64(r1)
	stw r0, 0x68(r1)
	bl sincosf
	mr r3, r27
	bl partyGetHeight
	lfs f0, float_0p75_8041b400(r2)
	mr r3, r27
	fmuls f0, f0, f1
	stfs f0, 0x50(r1)
	bl partyGetHeight
	lfs f0, float_0p5_8041b3f4(r2)
	lwz r0, 0x0(r27)
	fmuls f0, f0, f1
	rlwinm. r0, r0, 0, 26, 27
	stfs f0, 0x54(r1)
	bne @1
	bl yoshiGetStatus
	cmpwi r3, 0x2
	bne @2
	@1:
	lfs f0, float_1_8041b3f0(r2)
	stfs f0, 0x58(r1)
	b @3
	@2:
	lfs f0, float_11_8041b40c(r2)
	stfs f0, 0x58(r1)
	@3:
	lfs f1, float_0p5_8041b3f4(r2)
	addi r29, r1, 0x50
	lfs f0, 0xf4(r27)
	mr r30, r29
	lwz r3, 0x54(r31)
	li r28, 0x0
	fmuls f31, f1, f0
	lwz r0, 0x5c(r31)
	lwz r4, 0x58(r31)
	li r27, 0x0
	stw r3, 0x44(r1)
	fadds f28, f31, f29
	lfs f1, 0x1c(r1)
	stw r0, 0x4c(r1)
	lfs f0, 0x18(r1)
	stfs f28, 0xc(r1)
	stfs f1, 0x44(r1)
	lwz r0, 0x0(r26)
	lwz r5, 0x4(r26)
	stfs f0, 0x4c(r1)
	lwz r3, 0x44(r1)
	stw r0, 0x9c(r1)
	lwz r0, 0x4c(r1)
	stw r5, 0xa0(r1)
	lwz r5, 0x8(r26)
	stw r4, 0x48(r1)
	stw r5, 0xa4(r1)
	stw r3, 0x90(r1)
	stw r4, 0x94(r1)
	stw r0, 0x98(r1)
	@4:
	stfs f28, 0x8(r1)
	addi r3, r1, 0x9c
	lfs f0, 0x0(r30)
	addi r4, r1, 0x90
	lfs f1, 0x4(r26)
	addi r5, r1, 0x84
	addi r6, r1, 0x6c
	addi r7, r1, 0x8
	fadds f0, f1, f0
	stfs f0, 0xa0(r1)
	bl marioHitCheckVec
	cmplwi r3, 0x0
	beq @5
	cmplwi r28, 0x0
	beq @6
	lfs f1, 0x8(r1)
	lfs f0, 0xc(r1)
	fcmpo cr0, f1, f0
	bge @5
	lwz r4, 0x6c(r1)
	mr r28, r3
	lwz r3, 0x70(r1)
	lwz r0, 0x74(r1)
	stfs f1, 0xc(r1)
	stw r4, 0x78(r1)
	stw r3, 0x7c(r1)
	stw r0, 0x80(r1)
	b @5
	@6:
	lfs f0, 0x8(r1)
	mr r28, r3
	lwz r4, 0x6c(r1)
	lwz r3, 0x70(r1)
	lwz r0, 0x74(r1)
	stfs f0, 0xc(r1)
	stw r4, 0x78(r1)
	stw r3, 0x7c(r1)
	stw r0, 0x80(r1)
	@5:
	addi r27, r27, 0x1
	addi r30, r30, 0x4
	cmpwi r27, 0x3
	blt @4
	cmplwi r28, 0x0
	beq @7
	lwz r0, 0x80(r1)
	lfs f0, 0x18(r1)
	stw r0, 0x40(r1)
	lwz r0, 0x78(r1)
	fmuls f6, f0, f29
	lfs f0, 0x1c(r1)
	lfs f7, 0x40(r1)
	stw r0, 0x38(r1)
	fmuls f3, f0, f29
	fmuls f0, f6, f7
	lwz r0, 0x7c(r1)
	lfs f1, 0x38(r1)
	lfs f4, float_0p5_8041b3f4(r2)
	fmadds f5, f3, f1, f0
	lfs f2, 0x60(r1)
	lfs f0, 0x68(r1)
	stw r0, 0x3c(r1)
	fnmsubs f3, f5, f1, f3
	fnmsubs f1, f5, f7, f6
	fmadds f2, f4, f3, f2
	fmadds f0, f4, f1, f0
	stfs f2, 0x60(r1)
	stfs f0, 0x68(r1)
	@7:
	lfs f0, float_45_8041b410(r2)
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	fadds f1, f0, f30
	bl sincosf
	stfs f31, 0xc(r1)
	mr r27, r29
	lwz r3, 0x60(r31)
	li r30, 0x0
	lwz r0, 0x68(r31)
	stw r3, 0x2c(r1)
	lfs f1, 0x14(r1)
	stw r0, 0x34(r1)
	lfs f0, 0x10(r1)
	stfs f1, 0x2c(r1)
	lwz r4, 0x64(r31)
	stfs f0, 0x34(r1)
	lwz r0, 0x0(r26)
	lwz r5, 0x4(r26)
	lwz r3, 0x2c(r1)
	stw r0, 0x9c(r1)
	lwz r0, 0x34(r1)
	stw r5, 0xa0(r1)
	lwz r5, 0x8(r26)
	stw r4, 0x30(r1)
	stw r5, 0xa4(r1)
	stw r3, 0x90(r1)
	stw r4, 0x94(r1)
	stw r0, 0x98(r1)
	@8:
	stfs f31, 0xc(r1)
	addi r3, r1, 0x9c
	lfs f0, 0x0(r27)
	addi r4, r1, 0x90
	lfs f1, 0x4(r26)
	addi r7, r1, 0xc
	li r5, 0x0
	li r6, 0x0
	fadds f0, f1, f0
	stfs f0, 0xa0(r1)
	bl marioHitCheckVec
	cmplwi r3, 0x0
	bne @9
	addi r30, r30, 0x1
	addi r27, r27, 0x4
	cmpwi r30, 0x3
	blt @8
	@9:
	cmplwi r3, 0x0
	beq @10
	lfs f0, float_45_8041b410(r2)
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	fsubs f1, f30, f0
	bl sincosf
	li r27, 0x0
	@11:
	lwz r6, 0x6c(r31)
	addi r3, r1, 0x9c
	lwz r0, 0x74(r31)
	addi r4, r1, 0x90
	stfs f31, 0xc(r1)
	addi r7, r1, 0xc
	lfs f1, 0x14(r1)
	li r5, 0x0
	stw r6, 0x20(r1)
	li r6, 0x0
	lfs f0, 0x10(r1)
	stw r0, 0x28(r1)
	lwz r9, 0x70(r31)
	lfs f3, 0x4(r26)
	lfs f2, 0x0(r29)
	stfs f1, 0x20(r1)
	fadds f1, f3, f2
	stfs f0, 0x28(r1)
	lwz r8, 0x20(r1)
	lwz r0, 0x28(r1)
	stfs f1, 0xa0(r1)
	stw r9, 0x24(r1)
	stw r8, 0x90(r1)
	stw r9, 0x94(r1)
	stw r0, 0x98(r1)
	bl marioHitCheckVec
	addi r27, r27, 0x1
	addi r29, r29, 0x4
	cmpwi r27, 0x3
	blt @11
	@10:
	cmplwi r28, 0x0
	beq @12
	cmplwi r3, 0x0
	bne @13
	lfs f2, 0x0(r26)
	lfs f1, 0x60(r1)
	lfs f0, 0x68(r1)
	fadds f1, f2, f1
	stfs f1, 0x0(r26)
	lfs f1, 0x8(r26)
	fadds f0, f1, f0
	stfs f0, 0x8(r26)
	@13:
	mr r3, r28
	b @14
	@12:
	cmplwi r3, 0x0
	bne @15
	lfs f1, 0x1c(r1)
	lfs f0, 0x0(r26)
	fmadds f0, f29, f1, f0
	stfs f0, 0x0(r26)
	lfs f1, 0x18(r1)
	lfs f0, 0x8(r26)
	fmadds f0, f29, f1, f0
	stfs f0, 0x8(r26)
	@15:
	li r3, 0x0
	@14:
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	lmw r26, 0xa8(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm HitEntry* partyChkFrontStep(PartyEntry* party, f32 range, f32* outY, f32* outDist, f32* outAng) {
	nofralloc
	stwu r1, -0x150(r1)
	mflr r0
	stw r0, 0x154(r1)
	stfd f31, 0x140(r1)
	psq_st f31, 0x148(r1), 0, 0
	stfd f30, 0x130(r1)
	psq_st f30, 0x138(r1), 0, 0
	stfd f29, 0x120(r1)
	psq_st f29, 0x128(r1), 0, 0
	stfd f28, 0x110(r1)
	psq_st f28, 0x118(r1), 0, 0
	stfd f27, 0x100(r1)
	psq_st f27, 0x108(r1), 0, 0
	stfd f26, 0xf0(r1)
	psq_st f26, 0xf8(r1), 0, 0
	stfd f25, 0xe0(r1)
	psq_st f25, 0xe8(r1), 0, 0
	stfd f24, 0xd0(r1)
	psq_st f24, 0xd8(r1), 0, 0
	stfd f23, 0xc0(r1)
	psq_st f23, 0xc8(r1), 0, 0
	stmw r26, 0xa8(r1)
	lis r7, vec3_802cd320@ha
	lfs f0, float_0p01_8041b418(r2)
	addi r31, r7, vec3_802cd320@l
	mr r26, r3
	lwz r7, 0x18(r31)
	fadds f24, f1, f0
	lwz r0, 0x1c(r31)
	mr r27, r4
	lfs f0, float_0_8041b3ec(r2)
	mr r28, r5
	stw r7, 0xc4(r3)
	mr r29, r6
	stw r0, 0xc8(r3)
	lwz r0, 0x20(r31)
	stw r0, 0xcc(r3)
	stfs f0, 0xe0(r3)
	bl partyGetHeight
	lfs f0, 0x5c(r26)
	fmr f31, f1
	lfs f1, float_neg1_8041b414(r2)
	stfs f0, 0x0(r27)
	lfs f0, float_0_8041b3ec(r2)
	stfs f1, 0x0(r28)
	lfs f1, 0x104(r26)
	fcmpu cr0, f1, f0
	beq @1
	lfs f1, 0x100(r26)
	b @2
	@1:
	lfs f1, 0x10c(r26)
	bl toMovedir
	@2:
	lfs f0, float_0p5_8041b3f4(r2)
	lis r0, 0x4330
	stw r0, 0x78(r1)
	fadds f0, f0, f1
	lfd f1, 0xc0(r31)
	fctiwz f0, f0
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f1, f0, f1
	bl revise360
	lfs f2, float_3p1416_8041b420(r2)
	lfs f0, float_180_8041b424(r2)
	fmuls f1, f2, f1
	lfs f3, float_0p265_8041b41c(r2)
	lfs f2, 0xf4(r26)
	fdivs f25, f1, f0
	fmr f1, f25
	fmuls f23, f3, f2
	bl sin
	frsp f26, f1
	fmr f1, f25
	bl cos
	frsp f1, f1
	lfs f25, 0x5c(r26)
	lwz r4, 0x24(r31)
	fmuls f0, f23, f26
	lfs f26, 0x58(r26)
	fadds f2, f25, f31
	fneg f1, f1
	lwz r3, 0x28(r31)
	lwz r0, 0x2c(r31)
	fadds f3, f26, f0
	stw r4, 0x18(r1)
	fadds f0, f31, f24
	lfs f24, 0x60(r26)
	fmuls f1, f23, f1
	stw r3, 0x1c(r1)
	lwz r4, 0x30(r31)
	fadds f1, f24, f1
	stw r0, 0x20(r1)
	lwz r3, 0x34(r31)
	stfs f3, 0x18(r1)
	lwz r0, 0x38(r31)
	stfs f2, 0x1c(r1)
	lwz r7, 0x18(r1)
	stfs f1, 0x20(r1)
	lwz r6, 0x1c(r1)
	lwz r5, 0x20(r1)
	stw r7, 0x3c(r1)
	stw r6, 0x40(r1)
	stw r5, 0x44(r1)
	stw r4, 0x48(r1)
	stw r3, 0x4c(r1)
	stw r0, 0x50(r1)
	stfs f0, 0x6c(r1)
	bl yoshiGetStatus
	cmpwi r3, 0x0
	beq @3
	lis r4, chkfilterYoshi@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterYoshi@l
	bl hitCheckVecFilter
	b @4
	@3:
	lbz r0, 0x31(r26)
	cmpwi r0, 0x2
	bne @5
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 23, 23
	beq @5
	lis r4, chkfilterNokotaro@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterNokotaro@l
	bl hitCheckVecFilter
	b @4
	@5:
	lis r4, chkfilter@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilter@l
	bl hitCheckVecFilter
	@4:
	cmplwi r3, 0x0
	bne @6
	mr r30, r3
	b @7
	@6:
	lfs f1, 0x54(r1)
	lfs f0, float_0_8041b3ec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041b3f4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041b404(r2)
	@9:
	lfs f3, float_1000_8041b408(r2)
	lis r0, 0x4330
	stw r0, 0x70(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0xc0(r31)
	lfs f4, 0x58(r1)
	lfs f0, float_0_8041b3ec(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	fdivs f30, f0, f3
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041b3f4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041b404(r2)
	@11:
	lfs f3, float_1000_8041b408(r2)
	lis r0, 0x4330
	stw r0, 0x88(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0xc0(r31)
	lfs f4, 0x5c(r1)
	lfs f0, float_0_8041b3ec(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f29, f0, f3
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041b3f4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041b404(r2)
	@13:
	lfs f5, float_1000_8041b408(r2)
	lis r0, 0x4330
	lfs f2, 0x60(r1)
	mr r30, r3
	fmadds f3, f5, f4, f0
	lfs f1, 0x64(r1)
	lfs f0, 0x68(r1)
	stw r0, 0x98(r1)
	fctiwz f4, f3
	lfd f3, 0xc0(r31)
	stfs f2, 0x24(r1)
	stfd f4, 0x90(r1)
	lwz r0, 0x94(r1)
	stfs f1, 0x28(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f1, 0x98(r1)
	stfs f0, 0x2c(r1)
	fsubs f0, f1, f3
	fdivs f28, f0, f5
	@7:
	cmplwi r30, 0x0
	beq @14
	lwz r3, 0x28(r1)
	lwz r0, 0x2c(r1)
	stw r3, 0x10(r1)
	lfs f1, float_0_8041b3ec(r2)
	lfs f0, float_100_8041b3f8(r2)
	lfs f27, 0x10(r1)
	fmr f2, f1
	stw r0, 0x14(r1)
	fmuls f23, f0, f27
	lwz r0, 0x24(r1)
	lfs f31, 0x14(r1)
	stw r0, 0xc(r1)
	fmr f4, f23
	fmuls f3, f0, f31
	bl angleABf
	lfs f0, float_180_8041b424(r2)
	lis r0, 0x4330
	stw r0, 0x90(r1)
	fmr f4, f23
	fsubs f0, f1, f0
	lfs f2, float_0_8041b3ec(r2)
	lfs f3, float_100_8041b3f8(r2)
	lfd f5, 0xc0(r31)
	fmr f1, f2
	fctiwz f6, f0
	lfs f0, 0xc(r1)
	stfd f6, 0x98(r1)
	fmuls f3, f3, f0
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f5
	stfs f0, 0xc4(r26)
	stfs f2, 0xc8(r26)
	bl angleABf
	lfs f2, float_180_8041b424(r2)
	lis r0, 0x4330
	stw r0, 0x80(r1)
	fmuls f0, f31, f31
	fsubs f4, f1, f2
	lfs f1, 0xc(r1)
	lfd f2, 0xc0(r31)
	fmadds f3, f1, f1, f0
	lfs f0, float_0_8041b3ec(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f0, 0x80(r1)
	fsubs f0, f0, f2
	stfs f0, 0xcc(r26)
	ble @15
	frsqrte f1, f3
	lfd f4, 0xc8(r31)
	lfd f2, 0xd0(r31)
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
	b @16
	@15:
	lfd f0, 0xd8(r31)
	fcmpo cr0, f3, f0
	bge @17
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @16
	@17:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @18
	bge @19
	cmpwi r3, 0x0
	beq @20
	b @19
	@18:
	clrlwi. r0, r4, 9
	beq @21
	li r0, 0x1
	b @22
	@21:
	li r0, 0x2
	b @22
	@20:
	clrlwi. r0, r4, 9
	beq @23
	li r0, 0x5
	b @22
	@23:
	li r0, 0x3
	b @22
	@19:
	li r0, 0x4
	@22:
	cmpwi r0, 0x1
	bne @16
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@16:
	lfs f1, float_0_8041b3ec(r2)
	fneg f4, f27
	fmr f2, f1
	bl angleABf
	fcmpo cr0, f29, f25
	stfs f1, 0xe0(r26)
	bge @24
	fsubs f1, f29, f25
	lfs f0, float_2_8041b428(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @24
	fsubs f0, f25, f29
	fmr f1, f26
	fmr f2, f24
	fmr f3, f30
	stfs f0, 0x0(r28)
	fmr f4, f28
	bl angleABf
	stfs f1, 0x0(r29)
	b @14
	@24:
	stfs f29, 0x0(r27)
	fmr f1, f26
	lfs f0, float_0_8041b3ec(r2)
	fmr f2, f24
	lfs f3, 0x24(r1)
	stfs f0, 0x0(r28)
	lfs f4, 0x2c(r1)
	bl angleABf
	stfs f1, 0x0(r29)
	mr r3, r30
	b @25
	@14:
	li r3, 0x0
	@25:
	psq_l f31, 0x148(r1), 0, 0
	lfd f31, 0x140(r1)
	psq_l f30, 0x138(r1), 0, 0
	lfd f30, 0x130(r1)
	psq_l f29, 0x128(r1), 0, 0
	lfd f29, 0x120(r1)
	psq_l f28, 0x118(r1), 0, 0
	lfd f28, 0x110(r1)
	psq_l f27, 0x108(r1), 0, 0
	lfd f27, 0x100(r1)
	psq_l f26, 0xf8(r1), 0, 0
	lfd f26, 0xf0(r1)
	psq_l f25, 0xe8(r1), 0, 0
	lfd f25, 0xe0(r1)
	psq_l f24, 0xd8(r1), 0, 0
	lfd f24, 0xd0(r1)
	psq_l f23, 0xc8(r1), 0, 0
	lfd f23, 0xc0(r1)
	lmw r26, 0xa8(r1)
	lwz r0, 0x154(r1)
	mtlr r0
	addi r1, r1, 0x150
	blr
}

asm HitEntry* partySearchGround(PartyEntry* party, f32 range, f32 depth) {
	nofralloc
	stwu r1, -0x1b0(r1)
	mflr r0
	stw r0, 0x1b4(r1)
	stfd f31, 0x1a0(r1)
	psq_st f31, 0x1a8(r1), 0, 0
	stfd f30, 0x190(r1)
	psq_st f30, 0x198(r1), 0, 0
	stfd f29, 0x180(r1)
	psq_st f29, 0x188(r1), 0, 0
	stfd f28, 0x170(r1)
	psq_st f28, 0x178(r1), 0, 0
	stfd f27, 0x160(r1)
	psq_st f27, 0x168(r1), 0, 0
	stfd f26, 0x150(r1)
	psq_st f26, 0x158(r1), 0, 0
	stfd f25, 0x140(r1)
	psq_st f25, 0x148(r1), 0, 0
	stfd f24, 0x130(r1)
	psq_st f24, 0x138(r1), 0, 0
	stfd f23, 0x120(r1)
	psq_st f23, 0x128(r1), 0, 0
	stfd f22, 0x110(r1)
	psq_st f22, 0x118(r1), 0, 0
	stfd f21, 0x100(r1)
	psq_st f21, 0x108(r1), 0, 0
	stfd f20, 0xf0(r1)
	psq_st f20, 0xf8(r1), 0, 0
	stfd f19, 0xe0(r1)
	psq_st f19, 0xe8(r1), 0, 0
	stfd f18, 0xd0(r1)
	psq_st f18, 0xd8(r1), 0, 0
	stmw r24, 0xb0(r1)
	mr r24, r3
	lis r3, vec3_802cd320@ha
	lwz r0, 0x0(r24)
	fmr f18, f2
	addi r28, r3, vec3_802cd320@l
	rlwinm. r0, r0, 0, 6, 6
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, 0x0(r28)
	fabs f22, f1
	lwz r0, 0x4(r28)
	lfs f0, float_0p1_8041b42c(r2)
	stw r3, 0xc4(r24)
	lfs f1, float_0_8041b3ec(r2)
	fadds f22, f22, f0
	stw r0, 0xc8(r24)
	lwz r0, 0x8(r28)
	stw r0, 0xcc(r24)
	stfs f1, 0xe0(r24)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1a
	bne @3
	lfs f20, float_5_8041b430(r2)
	b @4
	@3:
	mr r3, r24
	bl partyGetHeight
	lfs f0, float_0p75_8041b400(r2)
	fmuls f20, f0, f1
	@4:
	lfs f0, 0x5c(r24)
	lfs f1, float_neg1_8041b414(r2)
	stfs f0, 0xe4(r24)
	lfs f0, float_0_8041b3ec(r2)
	stfs f1, 0xe8(r24)
	lfs f1, 0x104(r24)
	fcmpu cr0, f1, f0
	beq @5
	lfs f1, 0x100(r24)
	b @6
	@5:
	lfs f1, 0x10c(r24)
	mr r3, r24
	bl partyToMovedir
	@6:
	lfs f2, float_3p1416_8041b420(r2)
	lfs f0, float_180_8041b424(r2)
	fmuls f1, f2, f1
	fdivs f19, f1, f0
	fmr f1, f19
	bl sin
	frsp f3, f1
	lfs f0, 0xf4(r24)
	lfs f2, float_0p375_8041b434(r2)
	fmr f1, f19
	fmuls f0, f0, f3
	fmuls f24, f2, f0
	bl cos
	frsp f0, f1
	lfs f21, 0x5c(r24)
	lwz r29, 0xc(r28)
	fneg f27, f24
	lwz r30, 0x10(r28)
	fadds f19, f21, f20
	fneg f0, f0
	lfs f1, 0xf4(r24)
	lwz r31, 0x14(r28)
	fadds f26, f20, f22
	lfs f2, float_0p375_8041b434(r2)
	li r26, 0x0
	fmuls f0, f1, f0
	stw r29, 0x34(r1)
	lfs f22, 0x58(r24)
	li r25, 0x0
	stw r30, 0x38(r1)
	fmuls f23, f2, f0
	stw r31, 0x3c(r1)
	lfs f20, 0x60(r24)
	fneg f28, f23
	lfs f25, float_neg10000_8041b438(r2)
	@7:
	cmpwi r25, 0x0
	bne @8
	lfs f31, float_0_8041b3ec(r2)
	fmr f30, f31
	b @9
	@8:
	cmpwi r25, 0x1
	bne @10
	fmr f31, f24
	fmr f30, f23
	b @9
	@10:
	cmpwi r25, 0x2
	bne @11
	fmr f31, f28
	fmr f30, f24
	b @9
	@11:
	cmpwi r25, 0x3
	bne @12
	fmr f31, f23
	fmr f30, f27
	b @9
	@12:
	cmpwi r25, 0x4
	bne @9
	fmr f31, f27
	fmr f30, f28
	@9:
	fadds f1, f22, f31
	stfs f19, 0x44(r1)
	fadds f0, f20, f30
	lwz r3, 0x44(r1)
	stfs f1, 0x40(r1)
	stfs f0, 0x48(r1)
	lwz r4, 0x40(r1)
	lwz r0, 0x48(r1)
	stw r4, 0x58(r1)
	stw r3, 0x5c(r1)
	stw r0, 0x60(r1)
	stw r29, 0x64(r1)
	stw r30, 0x68(r1)
	stw r31, 0x6c(r1)
	stfs f26, 0x88(r1)
	bl yoshiGetStatus
	cmpwi r3, 0x0
	beq @13
	lis r4, chkfilterYoshi@ha
	addi r3, r1, 0x4c
	addi r4, r4, chkfilterYoshi@l
	bl hitCheckVecFilter
	b @14
	@13:
	lbz r0, 0x31(r24)
	cmpwi r0, 0x2
	bne @15
	lwz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 23, 23
	beq @15
	lis r4, chkfilterNokotaro@ha
	addi r3, r1, 0x4c
	addi r4, r4, chkfilterNokotaro@l
	bl hitCheckVecFilter
	b @14
	@15:
	lis r4, chkfilter@ha
	addi r3, r1, 0x4c
	addi r4, r4, chkfilter@l
	bl hitCheckVecFilter
	@14:
	cmplwi r3, 0x0
	bne @16
	b @17
	@16:
	lfs f1, 0x74(r1)
	lfs f0, float_0_8041b3ec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @18
	lfs f0, float_0p5_8041b3f4(r2)
	b @19
	@18:
	lfs f0, float_neg0p5_8041b404(r2)
	@19:
	lfs f5, float_1000_8041b408(r2)
	lis r0, 0x4330
	lfs f2, 0x7c(r1)
	fmadds f3, f5, f1, f0
	lfs f1, 0x80(r1)
	lfs f0, 0x84(r1)
	stw r0, 0x98(r1)
	fctiwz f4, f3
	lfd f3, 0xc0(r28)
	stfs f1, 0x2c(r1)
	stfd f4, 0x90(r1)
	lwz r0, 0x94(r1)
	stfs f0, 0x30(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f1, 0x98(r1)
	stfs f2, 0x28(r1)
	fsubs f0, f1, f3
	fdivs f29, f0, f5
	@17:
	cmplwi r3, 0x0
	mr r27, r3
	beq @20
	lwz r3, 0x2c(r1)
	lwz r0, 0x30(r1)
	stw r3, 0x20(r1)
	lfs f1, float_0_8041b3ec(r2)
	stw r0, 0x24(r1)
	lwz r0, 0x28(r1)
	fmr f2, f1
	lfs f4, float_100_8041b3f8(r2)
	lfs f3, 0x24(r1)
	lfs f0, 0x20(r1)
	fmuls f3, f4, f3
	stw r0, 0x1c(r1)
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041b424(r2)
	lis r0, 0x4330
	stw r0, 0x90(r1)
	fsubs f0, f1, f0
	lfs f2, float_0_8041b3ec(r2)
	lfs f4, float_100_8041b3f8(r2)
	lfs f3, 0x1c(r1)
	fmr f1, f2
	fctiwz f6, f0
	lfs f0, 0x20(r1)
	fmuls f3, f4, f3
	lfd f5, 0xc0(r28)
	stfd f6, 0x98(r1)
	fmuls f4, f4, f0
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f5
	stfs f0, 0xc4(r24)
	stfs f2, 0xc8(r24)
	bl angleABf
	lfs f0, float_180_8041b424(r2)
	lis r0, 0x4330
	lfs f2, 0x1c(r1)
	fsubs f0, f1, f0
	lfs f1, 0x24(r1)
	stw r0, 0xa8(r1)
	fmuls f2, f2, f2
	fmuls f1, f1, f1
	lfd f4, 0xc0(r28)
	fctiwz f5, f0
	lfs f0, float_0_8041b3ec(r2)
	fadds f3, f2, f1
	stfd f5, 0xa0(r1)
	fcmpo cr0, f3, f0
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f4
	stfs f0, 0xcc(r24)
	ble @21
	frsqrte f1, f3
	lfd f4, 0xc8(r28)
	lfd f2, 0xd0(r28)
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
	b @22
	@21:
	lfd f0, 0xd8(r28)
	fcmpo cr0, f3, f0
	bge @23
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @22
	@23:
	stfs f3, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @24
	bge @25
	cmpwi r3, 0x0
	beq @26
	b @25
	@24:
	clrlwi. r0, r4, 9
	beq @27
	li r0, 0x1
	b @28
	@27:
	li r0, 0x2
	b @28
	@26:
	clrlwi. r0, r4, 9
	beq @29
	li r0, 0x5
	b @28
	@29:
	li r0, 0x3
	b @28
	@25:
	li r0, 0x4
	@28:
	cmpwi r0, 0x1
	bne @22
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@22:
	lfs f1, float_0_8041b3ec(r2)
	lfs f0, 0x20(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f0, float_50_8041b43c(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @20
	li r27, 0x0
	@20:
	cmplwi r27, 0x0
	beq @30
	lwz r3, 0x2c(r1)
	lwz r0, 0x30(r1)
	stw r3, 0x14(r1)
	lfs f1, float_0_8041b3ec(r2)
	stw r0, 0x18(r1)
	lwz r0, 0x28(r1)
	fmr f2, f1
	lfs f4, float_100_8041b3f8(r2)
	lfs f3, 0x18(r1)
	lfs f0, 0x14(r1)
	fmuls f3, f4, f3
	stw r0, 0x10(r1)
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041b424(r2)
	lis r0, 0x4330
	stw r0, 0xa0(r1)
	fsubs f0, f1, f0
	lfs f2, float_0_8041b3ec(r2)
	lfs f4, float_100_8041b3f8(r2)
	lfs f3, 0x10(r1)
	fmr f1, f2
	fctiwz f6, f0
	lfs f0, 0x14(r1)
	fmuls f3, f4, f3
	lfd f5, 0xc0(r28)
	stfd f6, 0xa8(r1)
	fmuls f4, f4, f0
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f5
	stfs f0, 0xc4(r24)
	stfs f2, 0xc8(r24)
	bl angleABf
	lfs f0, float_180_8041b424(r2)
	lis r0, 0x4330
	lfs f2, 0x10(r1)
	fsubs f0, f1, f0
	lfs f1, 0x18(r1)
	stw r0, 0x90(r1)
	fmuls f2, f2, f2
	fmuls f1, f1, f1
	lfd f4, 0xc0(r28)
	fctiwz f5, f0
	lfs f0, float_0_8041b3ec(r2)
	fadds f3, f2, f1
	stfd f5, 0x98(r1)
	fcmpo cr0, f3, f0
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f4
	stfs f0, 0xcc(r24)
	ble @31
	frsqrte f1, f3
	lfd f4, 0xc8(r28)
	lfd f2, 0xd0(r28)
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
	b @32
	@31:
	lfd f0, 0xd8(r28)
	fcmpo cr0, f3, f0
	bge @33
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @32
	@33:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @34
	bge @35
	cmpwi r3, 0x0
	beq @36
	b @35
	@34:
	clrlwi. r0, r4, 9
	beq @37
	li r0, 0x1
	b @38
	@37:
	li r0, 0x2
	b @38
	@36:
	clrlwi. r0, r4, 9
	beq @39
	li r0, 0x5
	b @38
	@39:
	li r0, 0x3
	b @38
	@35:
	li r0, 0x4
	@38:
	cmpwi r0, 0x1
	bne @32
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@32:
	lfs f1, float_0_8041b3ec(r2)
	lfs f0, 0x14(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	fcmpo cr0, f29, f21
	stfs f1, 0xe0(r24)
	bge @40
	fsubs f1, f29, f21
	lfs f0, float_2_8041b428(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @40
	fabs f0, f18
	fcmpo cr0, f1, f0
	ble @41
	fsubs f0, f21, f29
	fabs f0, f0
	stfs f0, 0xe8(r24)
	b @30
	@41:
	fcmpo cr0, f29, f25
	ble @30
	fmr f25, f29
	mr r26, r27
	b @30
	@40:
	fsubs f1, f29, f21
	lfs f0, float_11_8041b40c(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @30
	fcmpo cr0, f29, f25
	ble @30
	fmr f25, f29
	mr r26, r27
	@30:
	addi r25, r25, 0x1
	cmpwi r25, 0x5
	blt @7
	cmplwi r26, 0x0
	beq @42
	stfs f25, 0xe4(r24)
	mr r3, r26
	lfs f0, float_0_8041b3ec(r2)
	stfs f0, 0xe8(r24)
	b @2
	@42:
	li r3, 0x0
	@2:
	psq_l f31, 0x1a8(r1), 0, 0
	lfd f31, 0x1a0(r1)
	psq_l f30, 0x198(r1), 0, 0
	lfd f30, 0x190(r1)
	psq_l f29, 0x188(r1), 0, 0
	lfd f29, 0x180(r1)
	psq_l f28, 0x178(r1), 0, 0
	lfd f28, 0x170(r1)
	psq_l f27, 0x168(r1), 0, 0
	lfd f27, 0x160(r1)
	psq_l f26, 0x158(r1), 0, 0
	lfd f26, 0x150(r1)
	psq_l f25, 0x148(r1), 0, 0
	lfd f25, 0x140(r1)
	psq_l f24, 0x138(r1), 0, 0
	lfd f24, 0x130(r1)
	psq_l f23, 0x128(r1), 0, 0
	lfd f23, 0x120(r1)
	psq_l f22, 0x118(r1), 0, 0
	lfd f22, 0x110(r1)
	psq_l f21, 0x108(r1), 0, 0
	lfd f21, 0x100(r1)
	psq_l f20, 0xf8(r1), 0, 0
	lfd f20, 0xf0(r1)
	psq_l f19, 0xe8(r1), 0, 0
	lfd f19, 0xe0(r1)
	psq_l f18, 0xd8(r1), 0, 0
	lfd f18, 0xd0(r1)
	lmw r24, 0xb0(r1)
	lwz r0, 0x1b4(r1)
	mtlr r0
	addi r1, r1, 0x1b0
	blr
}

asm void partyChkGnd(PartyEntry* party) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	mr r31, r3
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 6, 6
	bne @1
	lfs f1, float_11_8041b40c(r2)
	li r30, 0x0
	lfs f2, 0x114(r31)
	bl partySearchGround
	mr. r29, r3
	beq @2
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	mr r30, r3
	beq @2
	li r29, 0x0
	@2:
	stw r29, 0x138(r31)
	cmplwi r29, 0x0
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r31)
	bne @3
	lwz r0, 0x0(r31)
	mr r3, r31
	li r4, 0x3
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r31)
	bl partyChgMot
	lfs f0, float_neg1_8041b414(r2)
	stfs f0, 0x11c(r31)
	b @4
	@3:
	lwz r3, 0x0(r31)
	rlwinm. r0, r30, 0, 23, 23
	ori r0, r3, 0x2
	stw r0, 0x0(r31)
	beq @5
	lwz r0, 0x0(r31)
	ori r0, r0, 0x80
	stw r0, 0x0(r31)
	b @4
	@5:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r31)
	@4:
	lfs f0, 0xe4(r31)
	stfs f0, 0x5c(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 26, 27
	bne @1
	lfs f1, float_11_8041b40c(r2)
	mr r3, r31
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	bl partyChkFrontStep
	lfs f2, 0x10(r1)
	lfs f1, 0x5c(r31)
	lfs f0, float_5_8041b430(r2)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @1
	lfs f1, 0xe0(r31)
	lfs f0, float_30_8041b440(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @1
	stfs f2, 0x120(r31)
	lfs f0, float_0_8041b3ec(r2)
	lfs f1, 0x104(r31)
	fcmpu cr0, f1, f0
	beq @1
	mr r3, r31
	li r4, 0x6
	bl partyChgMot
	@1:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm f32 partyNrmToAngle(Vec n) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lfs f0, 0x0(r3)
	lis r4, vec3_802cd320@ha
	lfs f1, 0x8(r3)
	addi r4, r4, vec3_802cd320@l
	fmuls f2, f0, f0
	lfs f0, float_0_8041b3ec(r2)
	fmuls f1, f1, f1
	stw r0, 0x14(r1)
	fadds f3, f2, f1
	fcmpo cr0, f3, f0
	ble @1
	frsqrte f1, f3
	lfd f4, 0xc8(r4)
	lfd f2, 0xd0(r4)
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
	b @2
	@1:
	lfd f0, 0xd8(r4)
	fcmpo cr0, f3, f0
	bge @3
	lis r4, __float_nan@ha
	lfs f3, __float_nan@l(r4)
	b @2
	@3:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r5, 0x8(r1)
	rlwinm r4, r5, 0, 1, 8
	cmpw r4, r0
	beq @4
	bge @5
	cmpwi r4, 0x0
	beq @6
	b @5
	@4:
	clrlwi. r0, r5, 9
	beq @7
	li r0, 0x1
	b @8
	@7:
	li r0, 0x2
	b @8
	@6:
	clrlwi. r0, r5, 9
	beq @9
	li r0, 0x5
	b @8
	@9:
	li r0, 0x3
	b @8
	@5:
	li r0, 0x4
	@8:
	cmpwi r0, 0x1
	bne @2
	lis r4, __float_nan@ha
	lfs f3, __float_nan@l(r4)
	@2:
	lfs f1, float_0_8041b3ec(r2)
	lfs f0, 0x4(r3)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stw r31, 0xac(r1)
	mr r31, r8
	stw r30, 0xa8(r1)
	mr r30, r7
	stw r29, 0xa4(r1)
	mr r29, r6
	stw r28, 0xa0(r1)
	mr r28, r3
	lwz r9, 0x0(r5)
	lwz r8, 0x4(r5)
	lwz r5, 0x8(r5)
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r9, 0x8(r1)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x8(r4)
	stw r8, 0xc(r1)
	stw r0, 0x28(r1)
	stw r9, 0x2c(r1)
	stw r8, 0x30(r1)
	stw r5, 0x34(r1)
	lfs f0, 0x0(r31)
	stw r5, 0x10(r1)
	stfs f0, 0x50(r1)
	bl yoshiGetStatus
	cmpwi r3, 0x0
	beq @1
	lis r4, chkfilterYoshi@ha
	addi r3, r1, 0x14
	addi r4, r4, chkfilterYoshi@l
	bl hitCheckVecFilter
	b @2
	@1:
	lbz r0, 0x31(r28)
	cmpwi r0, 0x2
	bne @3
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 23, 23
	beq @3
	lis r4, chkfilterNokotaro@ha
	addi r3, r1, 0x14
	addi r4, r4, chkfilterNokotaro@l
	bl hitCheckVecFilter
	b @2
	@3:
	lis r4, chkfilter@ha
	addi r3, r1, 0x14
	addi r4, r4, chkfilter@l
	bl hitCheckVecFilter
	@2:
	cmplwi r3, 0x0
	bne @4
	b @5
	@4:
	lfs f1, 0x50(r1)
	lfs f0, float_0_8041b3ec(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_0p5_8041b3f4(r2)
	b @7
	@6:
	lfs f0, float_neg0p5_8041b404(r2)
	@7:
	lfs f3, float_1000_8041b408(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802cd3e0@ha
	stw r0, 0x60(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802cd3e0@l(r4)
	lfs f0, float_0_8041b3ec(r2)
	fctiwz f1, f1
	stfd f1, 0x58(r1)
	lwz r0, 0x5c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	lfd f1, 0x60(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r31)
	lfs f1, 0x38(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041b3f4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041b404(r2)
	@9:
	lfs f3, float_1000_8041b408(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802cd3e0@ha
	stw r0, 0x70(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802cd3e0@l(r4)
	lfs f0, float_0_8041b3ec(r2)
	fctiwz f1, f1
	stfd f1, 0x68(r1)
	lwz r0, 0x6c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f1, 0x70(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r29)
	lfs f1, 0x3c(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041b3f4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041b404(r2)
	@11:
	lfs f3, float_1000_8041b408(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802cd3e0@ha
	stw r0, 0x80(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802cd3e0@l(r4)
	lfs f0, float_0_8041b3ec(r2)
	fctiwz f1, f1
	stfd f1, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f1, 0x80(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r29)
	lfs f1, 0x40(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041b3f4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041b404(r2)
	@13:
	lfs f2, float_1000_8041b408(r2)
	lis r0, 0x4330
	stw r0, 0x90(r1)
	lis r4, double_to_int_802cd3e0@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802cd3e0@l(r4)
	fctiwz f0, f0
	stfd f0, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r29)
	lfs f0, 0x44(r1)
	stfs f0, 0x0(r30)
	lfs f0, 0x48(r1)
	stfs f0, 0x4(r30)
	lfs f0, 0x4c(r1)
	stfs f0, 0x8(r30)
	@5:
	lwz r0, 0xb4(r1)
	lwz r31, 0xac(r1)
	lwz r30, 0xa8(r1)
	lwz r29, 0xa4(r1)
	lwz r28, 0xa0(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm BOOL chkfilterNokotaro(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802cd320@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802cd320@l
	stw r29, 0x14(r1)
	mr r29, r4
	bl marioGetPtr
	lis r3, 0x80
	lwz r4, 0x4(r29)
	addi r0, r3, 0x5
	and. r0, r4, r0
	beq @1
	li r3, 0x0
	b @2
	@1:
	lis r3, 0x8
	addi r0, r3, 0x80
	and. r0, r4, r0
	beq @3
	li r3, 0x1
	b @2
	@3:
	clrrwi. r0, r4, 31
	bne @4
	li r3, 0x1
	b @2
	@4:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	mr r31, r3
	addi r4, r30, 0xe0
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0xf8
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0x110
	bl strcmp
	cmpwi r3, 0x0
	bne @6
	@5:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	li r3, 0x0
	b @2
	@6:
	li r3, 0x1
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL chkfilterYoshi(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802cd320@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802cd320@l
	stw r29, 0x14(r1)
	mr r29, r4
	bl marioGetPtr
	lis r3, 0x8
	lwz r4, 0x4(r29)
	addi r0, r3, 0x80
	and. r0, r4, r0
	beq @1
	li r3, 0x1
	b @2
	@1:
	rlwinm. r0, r4, 0, 8, 8
	beq @3
	li r3, 0x1
	b @2
	@3:
	rlwinm. r0, r4, 0, 29, 29
	beq @4
	li r3, 0x0
	b @2
	@4:
	clrrwi. r0, r4, 31
	bne @5
	li r3, 0x1
	b @2
	@5:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	mr r31, r3
	addi r4, r30, 0xe0
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @6
	addi r3, r31, 0x15
	addi r4, r30, 0xf8
	bl strcmp
	cmpwi r3, 0x0
	beq @6
	addi r3, r31, 0x15
	addi r4, r30, 0x110
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	@6:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	li r3, 0x0
	b @2
	@7:
	li r3, 0x1
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL chkfilter(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802cd320@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802cd320@l
	stw r29, 0x14(r1)
	mr r29, r4
	bl marioGetPtr
	lis r3, 0x8
	lwz r4, 0x4(r29)
	addi r0, r3, 0x80
	and. r0, r4, r0
	beq @1
	li r3, 0x1
	b @2
	@1:
	lis r3, 0x80
	addi r0, r3, 0x4
	and. r0, r4, r0
	beq @3
	li r3, 0x0
	b @2
	@3:
	clrrwi. r0, r4, 31
	bne @4
	li r3, 0x1
	b @2
	@4:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	mr r31, r3
	addi r4, r30, 0xe0
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0xf8
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0x110
	bl strcmp
	cmpwi r3, 0x0
	bne @6
	@5:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	li r3, 0x0
	b @2
	@6:
	li r3, 0x1
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}
// clang-format on
#endif
