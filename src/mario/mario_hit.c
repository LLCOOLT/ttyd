#include "mario/mario.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "party/party_vivian.h"
#include "system.h"
#include "mario/mariost.h"
#include "mario/mario_sbr.h"
#include "party.h"
#include <dolphin/types.h>
#include <string.h>
#include <dolphin/mtx.h>
extern const char str_802C5940[];
extern const char str_802C5948[];
extern const char str_802C5950[];
extern const char str_802C5964[];
extern const char str_802C5974[];
extern const char str_802C5988[];
extern const char str_802C59A4[];
extern const char str_802C59BC[];
extern const char str_802C59D4[];

extern MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);
extern double sin(double);
extern double cos(double);

#define MF(w, off, T) (*(T*)((u8*)(w) + (off)))

#ifdef NONMATCHING
static const Vec zv0 = {0.0f, 0.0f, 0.0f};
static const Vec zv1 = {0.0f, 0.0f, 0.0f};
#endif

extern HitEntry* marioSearchGround(f32* a, f32* b, f32* c, f32 d, f32 e);
extern HitEntry* marioSearchGroundRoll(f32* a, f32* b, f32* c, f32 d, f32 e);
extern HitEntry* marioLandonChk_old(f32* a, f32 d);
extern void set_damage_root_ypos(f32 y);
extern void kpaClearHitobjRide(void);
extern BOOL marioChgMot(s32 mot);
extern HitEntry* kpaSearchGround(f32* a, f32* b, f32* c, f32 d);
extern BOOL kpaFireAttackCheck(void);
extern void quake_kpaLandOn(void);
extern BOOL marioBgmodeChk(void);
extern void camFollowYOn(void);
extern void kpaCamFollow(void);
extern BOOL jabaraNoHitChk(void);
extern HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d);
extern HitEntry* marioSearchHead(Vec* pos, f32* h, f32 d);
extern HitEntry* searchFrontWall(Vec* pos, f32* h, f32 dx, f32 dz, f32 w);
extern void marioSearchFrontWall_staying(f32 dz);
extern HitEntry* dou10_yoko_yari(f32* p);
extern BOOL marioChkWallAround(Vec* pos, void* p, f32 dx, f32 dz, f32 w, f32 h);

#ifdef NONMATCHING
static inline BOOL marioChkBeroSub(s32 attr) {
    BOOL r = TRUE;
    if (attr & 0x80) {
        r = FALSE;
        if (marioGetPtr()->currMotionId == 0x19) {
            r = TRUE;
        }
    }
    return r;
}
#endif
extern HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);

#ifdef NONMATCHING
static inline BOOL marioChkBeroInl(HitEntry* hit) {
    s32 attr = hitGetAttr(hit);
    MarioWork* w = marioGetPtr();
    if ((attr & 0x80000) && !(w->flags & 0x1000000)) {
        return FALSE;
    }
    if (!(attr & 0x80)) {
        return (attr & 0x800000) ? 1 : 0;
    }
    return w->currMotionId == 0x19;
}
#endif

#ifdef NONMATCHING
static inline BOOL marioChkBeroSub2(s32 attr) {
    if (!(attr & 0x80)) {
        return TRUE;
    }
    return marioGetPtr()->currMotionId == 0x19;
}
#endif

#ifdef NONMATCHING
static inline BOOL marioChkBeroSub3(s32 attr) {
    return (attr & 0x80) ? (marioGetPtr()->currMotionId == 0x19) : TRUE;
}
#endif

#ifdef NONMATCHING
static inline BOOL marioChkBeroSub4(s32 attr) {
    BOOL r = TRUE;
    if (attr & 0x80) {
        r = marioGetPtr()->currMotionId == 0x19;
    }
    return r;
}
#endif

#ifdef NONMATCHING
static inline BOOL marioChkBeroSub5(HitEntry* hit) {
    s32 attr = hitGetAttr(hit);
    if (!(attr & 0x80)) {
        return TRUE;
    }
    return marioGetPtr()->currMotionId == 0x19;
}
#endif

#ifdef NONMATCHING
static inline BOOL marioChkBeroSub6(s32 attr) {
    if (attr & 0x80) {
        return marioGetPtr()->currMotionId == 0x19;
    } else {
        return TRUE;
    }
}
#endif

extern int __float_nan[];
static inline s32 hit_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 hit_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (hit_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

#ifdef NONMATCHING
static inline f32 marioHitNrmAngle(Vec* nrm) {
    f32 nz = nrm->z;
    f32 ny = nrm->y;
    f32 nx = nrm->x;
    MarioWork* mp = marioGetPtr();
    f32 y100 = 100.0f * ny;
    MF(mp, 0x218, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nz, y100) - 180.0f) + 0.5f) / 100.0f;
    MF(mp, 0x21c, f32) = 0.0f;
    MF(mp, 0x220, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nx, y100) - 180.0f) + 0.5f) / 100.0f;
    return angleABf(0.0f, 0.0f, hit_sqrtf(nx * nx + nz * nz), -ny);
}
#endif

#ifdef NONMATCHING
static inline f32 marioHitNrmAnglePtr(Vec* nrm) {
    MarioWork* mp = marioGetPtr();
    MF(mp, 0x218, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nrm->z, 100.0f * nrm->y) - 180.0f) + 0.5f) / 100.0f;
    MF(mp, 0x21c, f32) = 0.0f;
    MF(mp, 0x220, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nrm->x, 100.0f * nrm->y) - 180.0f) + 0.5f) / 100.0f;
    return angleABf(0.0f, 0.0f, hit_sqrtf(nrm->x * nrm->x + nrm->z * nrm->z), -nrm->y);
}
#endif

#ifdef NONMATCHING
void marioHitCheckWidth(void) {
    MarioWork* w = marioGetPtr();
    f32 v;
    if (!(w->flags & 0x100000)) {
        f32 lim = !(w->flags & 0x1000000) ? w->wPlayerCollisionBox.x : 18.0f;
        f32 s = (w->wPlayerCollisionBox.z += 1.0f);
        if (s > lim) {
            w->wPlayerCollisionBox.z = lim;
        }
    } else {
        v = w->wPlayerCollisionBox.z;
        if (v > 6.0f) {
            f32 t = v - 1.0f;
            w->wPlayerCollisionBox.z = t;
            if (t < 6.0f) {
                w->wPlayerCollisionBox.z = 6.0f;
            }
        }
        v = w->wPlayerCollisionBox.z;
        if (v < 6.0f) {
            v += 1.0f;
            w->wPlayerCollisionBox.z = v;
            if (v > 6.0f) {
                w->wPlayerCollisionBox.z = 6.0f;
            }
        }
    }
}
#endif


#ifdef NONMATCHING
BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry) {
    s32 ret = 0;
    s32 attr = entry->attributes;
    if ((attr & query->user0) == 0 || (attr & query->user1) != 0) {
        ret = 1;
    }
    return ret;
}
#endif

#ifdef NONMATCHING
BOOL chkfilterVec(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    if (entry->attributes & 0x80080) {
        return TRUE;
    }
    if (!(entry->attributes & 0x800000) && (entry->attributes & 0x4)) {
        return FALSE;
    }
    if (!(entry->attributes & 0x80000000)) {
        return TRUE;
    }
    mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, (char*)str_802C59A4) || !strcmp(mobj->animName, (char*)str_802C59BC) ||
        !strcmp(mobj->animName, (char*)str_802C59D4)) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL chkfilterVecRoll(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    if (entry->attributes & 0x80) {
        return TRUE;
    }
    if (!(entry->attributes & 0x800000) && (entry->attributes & 0x80004)) {
        return FALSE;
    }
    if (!(entry->attributes & 0x80000000)) {
        return TRUE;
    }
    mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, (char*)str_802C59A4) || !strcmp(mobj->animName, (char*)str_802C59BC) ||
        !strcmp(mobj->animName, (char*)str_802C59D4)) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    if ((entry->attributes & 0x80804) && !(entry->attributes & 0x800000)) {
        return FALSE;
    }
    if (!(entry->attributes & 0x80000000)) {
        return TRUE;
    }
    mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, (char*)str_802C59A4) || !strcmp(mobj->animName, (char*)str_802C59BC) ||
        !strcmp(mobj->animName, (char*)str_802C59D4)) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
static inline HitEntry* marioHitCheckVecInl(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    HitCheckQuery query;
    HitEntry* hit;
    f32 rf;

    query.targetPos = *pos;
    query.targetDir = *dir;
    query.targetDistance = *dist;
    if (marioGetPtr()->currMotionId == 0x1c) {
        hit = hitCheckVecFilter(&query, chkfilterVecVivian);
    } else if (marioGetPtr()->flags & 0x1000000) {
        hit = hitCheckVecFilter(&query, chkfilterVecRoll);
    } else {
        hit = hitCheckVecFilter(&query, chkfilterVec);
    }
    if (!hit) {
        return NULL;
    }
    if (query.targetDistance >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    *dist = (s32)((1000.0f * query.targetDistance) + rf) / 1000.0f;
    if (outPos) {
        *outPos = query.hitPos;
        if (outPos->x >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->x = (s32)((1000.0f * outPos->x) + rf) / 1000.0f;
        if (outPos->y >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->y = (s32)((1000.0f * outPos->y) + rf) / 1000.0f;
        if (outPos->z >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->z = (s32)((1000.0f * outPos->z) + rf) / 1000.0f;
    }
    if (outNrm) {
        *outNrm = query.hitNormal;
    }
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    return marioHitCheckVecInl(pos, dir, outPos, outNrm, dist);
}
#endif

#ifdef NONMATCHING
HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx,
                        f32 dy, f32 dz) {
    Vec outPos, outNrm;
    Vec pos = zv0;
    Vec dir = zv1;
    f32 d;
    HitEntry* hit;
    d = *dist;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    dir.x = dx;
    dir.y = dy;
    dir.z = dz;
    hit = marioHitCheckVecInl(&pos, &dir, &outPos, &outNrm, &d);
    *dist = d;
    *ox = outPos.x;
    *oy = outPos.y;
    *oz = outPos.z;
    *nx = outNrm.x;
    *ny = outNrm.y;
    *nz = outNrm.z;
    return hit;
}
#endif

#ifdef NONMATCHING
static inline HitEntry* marioHitCheckAttr2Inl(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    HitCheckQuery query;
    HitEntry* hit;
    f32 rf;

    query.targetPos = *pos;
    query.targetDir = *dir;
    query.targetDistance = *dist;
    query.user0 = 4;
    query.user1 = 0x800000;
    hit = hitCheckVecFilter(&query, chkFilterAttr2);
    if (!hit) {
        return NULL;
    }
    if (query.targetDistance >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    *dist = (s32)((1000.0f * query.targetDistance) + rf) / 1000.0f;
    if (outPos) {
        *outPos = query.hitPos;
        if (outPos->x >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->x = (s32)((1000.0f * outPos->x) + rf) / 1000.0f;
        if (outPos->y >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->y = (s32)((1000.0f * outPos->y) + rf) / 1000.0f;
        if (outPos->z >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->z = (s32)((1000.0f * outPos->z) + rf) / 1000.0f;
    }
    if (outNrm) {
        *outNrm = query.hitNormal;
    }
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    f32 d = *dist;
    if (w->currMotionId != 0x14) {
        if (!(w->flags & 0x20000)) {
            hit = marioHitCheckAttr2Inl(pos, dir, outPos, outNrm, &d);
        } else {
            hit = marioHitCheckVecInl(pos, dir, outPos, outNrm, &d);
        }
    } else if (marioGetJabaraState() == 1) {
        hit = marioHitCheckAttr2Inl(pos, dir, outPos, outNrm, &d);
    } else {
        hit = marioHitCheckVecInl(pos, dir, outPos, outNrm, &d);
    }
    *dist = d;
    return hit;
}
#endif

#ifdef NONMATCHING
void clear_hitobj_ride(void) {
    MarioWork* w = marioGetPtr();
    w->hitobjStandOn = NULL;
    if (w->characterId == 2) {
        kpaClearHitobjRide();
    }
}
#endif

#ifdef NONMATCHING
BOOL marioChkBero(HitEntry* hit) {
    s32 attr = hitGetAttr(hit);
    MarioWork* w = marioGetPtr();
    if ((attr & 0x80000) && !(w->flags & 0x1000000)) {
        return FALSE;
    }
    if (!(attr & 0x80)) {
        return (attr & 0x800000) ? 1 : 0;
    }
    return w->currMotionId == 0x19;
}
#endif

extern f32 roll_grx;
extern f32 roll_grz;
#pragma inline_max_size(1000)
#ifdef NONMATCHING
static inline void marioChkGndRoll(MarioWork* w) {
            HitEntry* hit;
            f32 gz, gx;
            Vec pos, outPos, outNrm;
            f32 dist = 47.0f;
            MF(w, 0x164, f32) = MF(w, 0x114, f32) - w->position.y;
            pos = w->position;
            pos.y += 10.0f;
            {
            Vec dir = {0.0f, -1.0f, 0.0f};
            hit = marioHitCheckVecInl(&pos, &dir, &outPos, &outNrm, &dist);
            }
            if (hit) {
                gx = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * outNrm.z, 100.0f * outNrm.y) - 180.0f) + 0.5f) / 100.0f;
                gz = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * outNrm.x, 100.0f * outNrm.y) - 180.0f) + 0.5f) / 100.0f;
                angleABf(0.0f, 0.0f, hit_sqrtf(outNrm.x * outNrm.x + outNrm.z * outNrm.z), -outNrm.y);
            }
            if (hit) {
                roll_grx = gx;
                roll_grz = gz;
            }
        }
#endif


#ifdef NONMATCHING
HitEntry* marioSearchUnder(void) {
    Vec pos, outPos, outNrm;
    f32 d = 1000.0f;
    HitEntry* hit;
    f32 h;
    MarioWork* w = marioGetPtr();
    h = w->wPlayerCollisionBox.y;
    if (w->flags & 0x1000000) {
        h *= 0.5f;
    }
    pos = w->position;
    pos.y += h;
    {
    Vec dir = {0.0f, -1.0f, 0.0f};
    hit = marioHitCheckVecInl(&pos, &dir, &outPos, &outNrm, &d);
    }
    MF(w, 0x1c0, f32) = hit ? outPos.y : -3000.0f;
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* searchUnder2(f32* out, f32 x, f32 y, f32 z) {
    Vec pos2, outPos, outNrm;
    HitEntry* hit;
    Vec pos = {0.0f, 0.0f, 0.0f};
    f32 d = 1037.0f;
    pos.y = y;
    pos.x = x;
    pos.z = z;
    pos2 = pos;
    pos2.y += 37.0f;
    if (x) {
    }
    {
    Vec dir = {0.0f, -1.0f, 0.0f};
    hit = marioHitCheckVecInl(&pos2, &dir, &outPos, &outNrm, &d);
    }
    *out = hit ? outPos.y : -1.0f;
    return hit;
}
#endif

extern f32 roll_grx;
extern f32 roll_grz;
extern BOOL marioChkShipMoveMode(void);
extern void marioShipChgFall(void);
extern HitEntry* kpaChkHitobjRide(void);
extern void roll_upstairs_on(void);
extern void marioSetFallPara(void);
extern BOOL marioChgMotSub(s32 mot, s32 a);
extern HitEntry* marioChkFrontStep(f32* y, f32* b, f32* c);

#ifdef NONMATCHING
static inline BOOL marioChkGndOk(void) {
    MarioWork* w = marioGetPtr();
    if (w->flags & 0x100) {
        return FALSE;
    }
    if (w->position.y >= 5000.0f) {
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
void marioChkGnd(void) {
    f32 b, y, c;
    f32 sy, sb, sc;
    f32 d;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    if (vivianGetStatus() == 2 || vivianGetStatus() == 1 || vivianGetStatus() == 3) {
        w->hitobjStandOn = marioSearchGround(&y, &b, &c, 37.0f, 0.0f);
        w->hitobjUnder = marioSearchUnder();
        return;
    }
    w->hitobjStandOn = NULL;
    if (w->characterId == 2) {
        kpaClearHitobjRide();
    }
    w->hitobjUnder = marioSearchUnder();
    if (w->flags & 0x30000) {
        return;
    }
    if (!marioChkGndOk()) {
        return;
    }
    if (!(w->flags & 0x200)) {
        if (w->flags & 0x1000000) {
            hit = marioSearchGroundRoll(&y, &b, &c, 11.0f, w->jumpVelocityY);
            if (hit) {
                w->hitobjStandOn = hit;
                MF(w, 0x1c0, f32) = (s32)(100.0f * y + 0.5f) / 100.0f;
            }
        } else {
            if (w->characterId == 2) {
                hit = kpaSearchGround(&y, &b, &c, 11.0f);
            } else {
                hit = marioSearchGround(&y, &b, &c, 11.0f, w->jumpVelocityY);
            }
            if (hit) {
                w->hitobjStandOn = hit;
                MF(w, 0x1c0, f32) = (s32)(100.0f * y + 0.5f) / 100.0f;
            }
        }
    } else {
        y = w->position.y;
        if (w->characterId == 2) {
            if (w->airTimer == 0) {
                marioChgMot(10);
                marioSetFallPara();
                return;
            }
        } else {
            if (w->airTimer == 0) {
                marioChgMot(10);
                marioSetFallPara();
                return;
            }
        }
    }
    if (w->currMotionId == 0x19) {
        if (marioChkShipMoveMode()) {
            if (!w->hitobjStandOn) {
                marioShipChgFall();
            } else {
                w->flags &= ~0x20000;
            }
        }
        return;
    }
    if (w->currMotionId != 0x1f && w->hitobjStandOn && (hitGetAttr(w->hitobjStandOn) & 0x200)) {
        if (w->jumpVelocityY >= 0.0f) {
            marioSetFallPara();
        }
        set_damage_root_ypos(w->position.y);
        marioChgMot(0x1f);
        return;
    }
    if (w->hitobjStandOn && (hitGetAttr(w->hitobjStandOn) & 0x800)) {
        if (vivianGetStatus() != 2 && vivianGetStatus() != 1 && vivianGetStatus() != 3) {
            set_damage_root_ypos(w->position.y);
            marioChgMot(0x20);
        }
        return;
    }
    if (w->airTimer == 0) {
        if (!(w->flags & 0x1000000)) {
            hit = marioChkFrontStep(&sy, &sb, &sc);
            d = sy - w->position.y;
            if (hit && d <= 11.0f && d >= 5.0f && *(f32*)((u8*)w + 0x214) <= 30.0f) {
                MF(w, 0x1c4, f32) = sy;
                if (w->baseSpeed) {
                    if (!(MF(w, 0x4, u32) & 0x1000000)) {
                        marioChgMot(0xc);
                    } else {
                        marioChgMotSub(0xc, 0);
                    }
                    return;
                }
            }
        } else {
            hit = marioChkFrontStep(&sy, &sb, &sc);
            d = sy - w->position.y;
            if (hit && d <= 11.0f && d >= 5.0f && MF(w, 0x214, f32) <= 30.0f) {
                MF(w, 0x1c4, f32) = sy;
                if (w->baseSpeed) {
                    roll_upstairs_on();
                    return;
                }
            }
        }
    }
    w->position.y = y;
    if (w->characterId == 2) {
        hit = kpaChkHitobjRide();
    } else {
        hit = w->hitobjStandOn;
    }
    if (hit) {
        if (w->flags & 0x1000000) {
            marioChkGndRoll(w);
        }
        return;
    }
    if (!(w->flags & 0x1000000)) {
        if (w->flags & 0x20000) {
            return;
        }
        if (b < 0.0f) {
            marioChgMot(10);
            marioSetFallPara();
        }
        if (b > 0.0f) {
            marioChgMot(11);
            marioSetFallPara();
        }
    } else {
        if (w->flags & 0x20000) {
            return;
        }
        w->flags &= ~0x10000;
        w->flags |= 0x20000;
        w->jumpVelocityY = -0.4f;
        w->jumpAccelerationY = -0.06f;
        w->jumpJerkY = -0.04f;
        w->jumpSnapY = -0.02f;
    }
}
#endif

#ifdef NONMATCHING
void marioChkGnd2(void) {
    f32 b, y, c;
    HitEntry* hit;
    f32 d;
    MarioWork* w = marioGetPtr();
    if (!(w->flags & 0x10000)) {
        if (w->characterId != 2) {
            hit = marioSearchGround(&y, &b, &c, 0.1f, w->jumpVelocityY);
        } else {
            hit = kpaSearchGround(&y, &b, &c, 0.1f);
        }
        if (hit) {
            d = w->position.y - y;
            if (d < 0.0f && d >= -10.0f) {
                w->hitobjStandOn = hit;
                w->position.y = y;
                w->flags &= ~0xC0;
                w->airTimer = 0;
                w->jumpPeakAirTime = 0;
                if (w->characterId == 2) {
                    if (w->controlStickSensitivity || !kpaFireAttackCheck()) {
                        s32 sx = (s8)w->wStickDir1;
                        s32 sy = (s8)w->wStickDir2;
                        if (sx * sx + sy * sy > 0xbd1) {
                            marioChgMot(2);
                        } else {
                            marioChgMot(1);
                        }
                    } else {
                        marioChgMot(0);
                    }
                    quake_kpaLandOn();
                } else {
                    marioChgMot(0);
                }
                if (w->characterId != 2) {
                    if (!marioBgmodeChk()) {
                        camFollowYOn();
                    }
                } else {
                    kpaCamFollow();
                }
            }
        }
    }
}
#endif

extern void marioUpdateCamCollision(Vec pos);

#ifdef NONMATCHING
HitEntry* marioSearchGround(f32* y, f32* b, f32* c, f32 spd, f32 h) {
    f32 dist;
    f32 best, yl, sx, sz, x0, y0, z0, a;
    f32 x, z;
    f32 lim;
    f32 dir;
    f32 sn;
    HitEntry* found;
    s32 i;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x218, f32) = 0.0f;
    MF(w, 0x21c, f32) = 0.0f;
    MF(w, 0x220, f32) = 0.0f;
    MF(w, 0x214, f32) = 0.0f;
    if (w->flags & 0x200) {
        *y = w->position.y;
        return NULL;
        if (b) {
        }
    }
    if (w->flags & 0x100) {
        *y = w->position.y;
        return NULL;
    }
    *y = w->position.y;
    spd = __fabsf(spd);
    spd += 0.01f;
    yl = 5.0f + __fabsf(h);
    *b = -1.0f;
    if (w->baseSpeed) {
        a = revise360(w->directionView - w->targetYaw);
    } else {
        a = toMovedir(w->displayDirection);
    }
    if (w->flags & 0x100000) {
        a = (3.1415927f * a) / 180.0f;
        sn = (f32)sin(a);
        sx = 0.425f * (w->wPlayerCollisionBox.x * sn);
        sn = (f32)cos(a);
        sz = 0.425f * (w->wPlayerCollisionBox.x * -sn);
    } else {
        a = (3.1415927f * a) / 180.0f;
        sn = (f32)sin(a);
        sx = 0.375f * (w->wPlayerCollisionBox.x * sn);
        sn = (f32)cos(a);
        sz = 0.375f * (w->wPlayerCollisionBox.x * -sn);
    }
    y0 = w->position.y;
    {
    Vec dir = {0.0f, -1.0f, 0.0f};
    Vec outPos;
    Vec outNrm;
    x0 = w->position.x;
    found = NULL;
    z0 = w->position.z;
    best = -10000.0f;
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            z = x = 0.0f;
        } else if (i == 1) {
            x = sx;
            z = sz;
        } else if (i == 2) {
            x = -sz;
            z = sx;
        } else if (i == 3) {
            x = sz;
            z = -sx;
        } else if (i == 4) {
            x = -sx;
            z = -sz;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            v.x = x0 + x;
            v.y = y0 + yl;
            v.z = z0 + z;
            dist = yl + spd;
            hit = marioHitCheckVecInl(&v, &dir, &outPos, &outNrm, &dist);
        }
        if (hit) {
            if (MF(w, 0x4, u32) & 0x1000000) {
                lim = 75.0f;
            } else if (w->currMotionId == 0x10) {
                lim = 75.0f;
            } else {
                lim = 50.0f;
            }
            if (marioHitNrmAnglePtr(&outNrm) >= lim) {
                hit = NULL;
            }
        }
        if (hit) {
            MF(w, 0x214, f32) = marioHitNrmAnglePtr(&outNrm);
            if (outPos.y < y0 && __fabsf(outPos.y - y0) >= 2.0f) {
                if (__fabsf(outPos.y - y0) > __fabsf(h)) {
                    *b = __fabsf(y0 - outPos.y);
                    *c = angleABf(x0, z0, outPos.x, outPos.z);
                } else if (outPos.y > best) {
                    *y = outPos.y;
                    best = outPos.y;
                    *b = 0.0f;
                    *c = angleABf(x0, z0, outPos.x, outPos.z);
                    marioUpdateCamCollision(outPos);
                    found = hit;
                }
            } else if (__fabsf(outPos.y - y0) <= 11.0f && outPos.y > best) {
                *y = outPos.y;
                best = outPos.y;
                *b = 0.0f;
                *c = angleABf(x0, z0, outPos.x, outPos.z);
                marioUpdateCamCollision(outPos);
                found = hit;
            }
        }
    }
    }
    if (found) {
        return found;
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h) {
    f32 dist;
    f32 lim, best, hh, x0, y0, z0, a, r;
    f32 sn;
    HitEntry* found;
    s32 i;
    s32 end;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x218, f32) = 0.0f;
    MF(w, 0x21c, f32) = 0.0f;
    MF(w, 0x220, f32) = 0.0f;
    if (w->flags & 0x200) {
        *y = w->position.y;
        return NULL;
        if (b) {
        }
    }
    if (w->flags & 0x100) {
        *y = w->position.y;
        return NULL;
    }
    hh = w->wPlayerCollisionBox.y;
    spd = __fabsf(spd);
    found = NULL;
    *y = w->position.y;
    *b = -1.0f;
    spd += 0.01f;
    best = -10000.0f;
    {
    Vec dir = {0.0f, -1.0f, 0.0f};
    Vec outPos;
    Vec outNrm;
    f32 x, z;
    y0 = w->position.y;
    x0 = w->position.x;
    z0 = w->position.z;
    if (__fabsf(MF(w, 0x214, f32)) < 0.01f) {
        lim = 2.0f;
        i = 0;
        end = 4;
    } else {
        lim = 10.0f;
        i = 4;
        end = 7;
    }
    for (; i < end; i++) {
        switch (i) {
        case 0:
            z = x = 0.0f;
            break;
        case 1:
            a = (3.1415927f * (90.0f + w->directionView)) / 180.0f;
            x = 8.6399994f * (f32)sin(a);
            sn = (f32)cos(a);
            z = 8.6399994f * -sn;
            break;
        case 2:
            a = (3.1415927f * (w->directionView - 90.0f)) / 180.0f;
            x = 8.6399994f * (f32)sin(a);
            sn = (f32)cos(a);
            z = 8.6399994f * -sn;
            break;
        case 3:
            z = x = 0.0f;
            movePos(&x, &z, 3.0f, w->directionView);
            break;
        case 4:
            z = x = 0.0f;
            break;
        case 5:
            a = (3.1415927f * (90.0f + w->directionView)) / 180.0f;
            x = 8.6399994f * (f32)sin(a);
            sn = (f32)cos(a);
            z = 8.6399994f * -sn;
            movePos(&x, &z, 3.0f, w->directionView);
            break;
        case 6:
            a = (3.1415927f * (w->directionView - 90.0f)) / 180.0f;
            x = 8.6399994f * (f32)sin(a);
            sn = (f32)cos(a);
            z = 8.6399994f * -sn;
            movePos(&x, &z, 3.0f, w->directionView);
            break;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            v.x = x0 + x;
            v.y = y0 + hh;
            v.z = z0 + z;
            dist = hh + spd;
            hit = marioHitCheckVecInl(&v, &dir, &outPos, &outNrm, &dist);
        }
        if (hit) {
            r = marioHitNrmAnglePtr(&outNrm);
            if (r <= 105.0f && r >= 75.0f) {
                continue;
            }
            MF(w, 0x214, f32) = r;
            if (outPos.y < y0 && __fabsf(outPos.y - y0) >= lim) {
                if (__fabsf(outPos.y - y0) > __fabsf(h)) {
                    *b = __fabsf(y0 - outPos.y);
                    *c = angleABf(x0, z0, outPos.x, outPos.z);
                } else if (outPos.y > best) {
                    *y = outPos.y;
                    best = outPos.y;
                    *b = 0.0f;
                    *c = angleABf(x0, z0, outPos.x, outPos.z);
                    found = hit;
                }
            } else if (__fabsf(outPos.y - y0) <= 11.0f && outPos.y > best) {
                *y = outPos.y;
                best = outPos.y;
                *b = 0.0f;
                *c = angleABf(x0, z0, outPos.x, outPos.z);
                found = hit;
            }
        }
    }
    }
    if (found) {
        return found;
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
void marioChkToge(void) {
    MarioWork* w = marioGetPtr();
    s32 attr;
    if (vivianGetStatus() == 2 || vivianGetStatus() == 1 || vivianGetStatus() == 3) {
        return;
    }
    if (w->hitobjFront != NULL) {
        attr = hitGetAttr(w->hitobjFront);
        if (w->currMotionId != 0x20 && (attr & 0x800) && MF(w, 0x210, f32) < 0.5f * w->wPlayerCollisionBox.x) {
            set_damage_root_ypos(w->position.y);
            marioChgMot(0x20);
        }
    }
    if (w->hitobjWall != NULL) {
        attr = hitGetAttr(w->hitobjWall);
        if (w->currMotionId != 0x20 && (attr & 0x800)) {
            set_damage_root_ypos(w->position.y);
            marioChgMot(0x20);
        }
    }
    if (w->hitobjHead != NULL) {
        attr = hitGetAttr(w->hitobjHead);
        if (w->currMotionId != 0x20 && (attr & 0x800)) {
            set_damage_root_ypos(w->position.y);
            marioChgMot(0x20);
        }
    }
}
#endif

#ifdef NONMATCHING
HitEntry* marioChkLandon(f32* a, f32 d) {
    f32 b, c;
    HitEntry* ret;
    MarioWork* w = marioGetPtr();
    if (w->characterId != 2) {
        if (!(w->flags & 0x1000000)) {
            ret = marioSearchGround(a, &b, &c, d, d);
        } else {
            ret = marioSearchGroundRoll(a, &b, &c, d, d);
        }
    } else {
        ret = marioLandonChk_old(a, d);
    }
    return ret;
}
#endif

typedef struct LandonRay {
    Vec pos;
    Vec dir;
} LandonRay;

#ifdef NONMATCHING
static inline f32 landonNrmAngle(f32 nx, f32 ny, f32 nz) {
    MarioWork* mp = marioGetPtr();
    f32 y100 = 100.0f * ny;
    MF(mp, 0x218, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nz, y100) - 180.0f) + 0.5f) / 100.0f;
    MF(mp, 0x21c, f32) = 0.0f;
    MF(mp, 0x220, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nx, y100) - 180.0f) + 0.5f) / 100.0f;
    return angleABf(0.0f, 0.0f, hit_sqrtf(nx * nx + nz * nz), -ny);
}
#endif

#ifdef NONMATCHING
static inline HitEntry* landonHitCheck(LandonRay* ray, Vec* outPos, Vec* outNrm, f32* dist) {
    HitCheckQuery query;
    HitEntry* hit;
    f32 rf;

    *(LandonRay*)&query.targetPos = *ray;
    query.targetDistance = *dist;
    if (marioGetPtr()->currMotionId == 0x1c) {
        hit = hitCheckVecFilter(&query, chkfilterVecVivian);
    } else if (marioGetPtr()->flags & 0x1000000) {
        hit = hitCheckVecFilter(&query, chkfilterVecRoll);
    } else {
        hit = hitCheckVecFilter(&query, chkfilterVec);
    }
    if (!hit) {
        return NULL;
    }
    if (query.targetDistance >= 0.0f) {
        rf = 0.5f;
    } else {
        rf = -0.5f;
    }
    *dist = (s32)((1000.0f * query.targetDistance) + rf) / 1000.0f;
    if (outPos) {
        *outPos = query.hitPos;
        if (outPos->x >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->x = (s32)((1000.0f * outPos->x) + rf) / 1000.0f;
        if (outPos->y >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->y = (s32)((1000.0f * outPos->y) + rf) / 1000.0f;
        if (outPos->z >= 0.0f) {
            rf = 0.5f;
        } else {
            rf = -0.5f;
        }
        outPos->z = (s32)((1000.0f * outPos->z) + rf) / 1000.0f;
    }
    if (outNrm) {
        *outNrm = query.hitNormal;
    }
    return hit;
}
#endif


#ifdef NONMATCHING
HitEntry* marioLandonChk_old(f32* outY, f32 spd) {
    LandonRay ray;
    Vec nrm;
    Vec hp;
    f32 hy;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 dx;
    f32 dz;
    f32 mone;
    f32 zero;
    f32 dist;
    f32 d;
    f32 noz;
    f32 nox;
    f32 ystart;
    f32 px;
    f32 top;
    f32 oz;
    f32 pz;
    f32 hh;
    f32 range;
    f32 sn;
    f32 ox;
    f32 py;
    s32 i;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    f32 a;

    MF(w, 0x218, f32) = 0.0f;
    MF(w, 0x21c, f32) = 0.0f;
    MF(w, 0x220, f32) = 0.0f;
    MF(w, 0x214, f32) = 0.0f;
    if (w->flags & 0x200) {
        *outY = w->position.y;
        return NULL;
    }
    if (w->flags & 0x100) {
        *outY = w->position.y;
        return NULL;
    }
    range = 0.01f + __fabsf(spd);
    hh = 0.75f * w->wPlayerCollisionBox.y;
    if (w->baseSpeed) {
        a = revise360(w->directionView - w->targetYaw);
    } else {
        a = toMovedir(w->displayDirection);
    }
    a = (3.1415927f * a) / 180.0f;
    sn = (f32)sin(a);
    ox = 0.25f * (w->wPlayerCollisionBox.x * sn);
    sn = (f32)cos(a);
    oz = 0.25f * (w->wPlayerCollisionBox.x * -sn);
    px = w->position.x;
    py = w->position.y;
    pz = w->position.z;
    if (w->characterId == 2) {
        f32 gy, gb, gc;
        hit = kpaSearchGround(&gy, &gb, &gc, 11.0f);
        *outY = gy;
        return hit;
    }
    noz = -oz;
    nox = -ox;
    zero = 0.0f;
    mone = -1.0f;
    top = hh + range;
    ystart = py + hh;
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            dx = 0.0f;
            dz = dx;
        } else if (i == 1) {
            dx = ox;
            dz = oz;
        } else if (i == 2) {
            dx = noz;
            dz = oz;
        } else if (i == 3) {
            dx = oz;
            dz = nox;
        } else if (i == 4) {
            dx = nox;
            dz = noz;
        }
        ray = *(volatile LandonRay*)&zv0; // FAKE: copies a 24-byte zero template; a real (LandonRay){0} adds a .rodata object and shifts every pool
        ray.pos.x = px + dx; ray.pos.y = ystart; ray.pos.z = pz + dz;
        ray.dir.x = zero; ray.dir.y = mone; ray.dir.z = zero;
        dist = top;
        hit = landonHitCheck(&ray, &hp, &nrm, &dist);
        hy = hp.y;
        nx = nrm.x;
        ny = nrm.y;
        nz = nrm.z;
        if (hit) {
            MF(w, 0x214, f32) = landonNrmAngle(nx, ny, nz);
            d = (s32)(100.0f * ((ystart - hy) - dist) + 0.5f) / 100.0f;
            if (__fabsf(d) < 0.1f) {
                *outY = (s32)(100.0f * hy + 0.5f) / 100.0f;
                return hit;
            }
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry* marioChkLandon2(f32* y, f32 spd, f32 ofs) {
    Vec dir;
    Vec outPos;
    Vec outNrm;
    f32 nsx;
    f32 yl;
    f32 d0;
    f32 sx;
    f32 sz;
    f32 x0;
    f32 z0;
    f32 a;
    f32 sn;
    f32 dist;
    f32 py;
    f32 x, z;
    s32 i;
    HitEntry* hit;
    void* vp;
    MarioWork* w = marioGetPtr();
    vp = (void*)y;
    MF(w, 0x218, f32) = 0.0f;
    MF(w, 0x21c, f32) = 0.0f;
    MF(w, 0x220, f32) = 0.0f;
    MF(w, 0x214, f32) = 0.0f;
    if (w->flags & 0x200) {
        *((f32*)vp) = w->position.y;
        return NULL;
    }
    if (w->flags & 0x100) {
        *((f32*)vp) = w->position.y;
        return NULL;
    }
    d0 = 0.1f + __fabsf(spd);
    yl = 0.5f * w->wPlayerCollisionBox.y;
    if (w->baseSpeed) {
        a = w->directionView;
    } else {
        a = toMovedir(w->displayDirection);
    }
    a = (3.1415927f * a) / 180.0f;
    sn = (f32)sin(a);
    sx = 0.25f * (w->wPlayerCollisionBox.x * sn);
    sn = (f32)cos(a);
    sz = 0.25f * (w->wPlayerCollisionBox.x * -sn);
    nsx = -sx;
    d0 = yl + d0;
    py = w->position.y + ofs;
    x0 = w->position.x;
    z0 = w->position.z;
    {
    dir = (Vec){0.0f, -1.0f, 0.0f};
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            z = x = 0.0f;
        } else if (i == 1) {
            x = sx;
            z = sz;
        } else if (i == 2) {
            x = -sz;
            z = sz;
        } else if (i == 3) {
            x = sz;
            z = nsx;
        } else if (i == 4) {
            x = nsx;
            z = -sz;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            v.x = x0 + x;
            v.y = py + yl;
            v.z = z0 + z;
            dist = d0;
            hit = marioHitCheckVecInl(&v, &dir, &outPos, &outNrm, &dist);
        }
        if (hit) {
            MF(w, 0x214, f32) = marioHitNrmAnglePtr(&outNrm);
            if (__fabsf((s32)(100.0f * (((py + yl) - outPos.y) - dist) + 0.5f) / 100.0f) < 0.1f) {
                *((f32*)vp) = outPos.y;
                return hit;
            }
        }
    }
    }
    return NULL;
}
#endif

extern HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d);
extern HitEntry* kpaSearchHead(Vec* pos, f32* h, f32 d);
extern s32 kpaGetBodyStatus(void);
extern void marioClearJumpPara(void);
extern f32 partyGetHeight(PartyEntry* p);
extern BOOL marioChkSlitEnd(void);
extern void marioChgStayMotion(void);
extern void marioSetFallPara(void);
extern s32 psndSFXOn_3D(const char* name, Vec* position);
extern s32 marioGetPartyId(void);
extern PartyEntry* partyGetPtr(s32 index);
extern void marioItemGetDisable(void);

typedef struct { u8 pad[0x15]; char name[16]; } MobjNameView;

#ifdef NONMATCHING
static inline BOOL marioChkHeadBlock(HitEntry* hit) {
    MobjNameView* mobj;
    char* name;
    if (!hit) {
        return FALSE;
    }
    if (!(hitGetAttr(hit) & 0x80000000)) {
        return FALSE;
    }
    mobj = (MobjNameView*)mobjHitObjPtrToPtr(hit);
    if (!strcmp(mobj->name, (char*)str_802C5950) || !strcmp(mobj->name, (char*)str_802C5964) ||
        !strcmp(mobj->name, (char*)str_802C5974) || !strcmp(mobj->name, (char*)str_802C5988)) {
        return TRUE;
    }
    return FALSE;
}
#endif

#ifdef NONMATCHING
static inline f32 marioGetHeightInl(void) {
    MarioWork* m = marioGetPtr();
    f32 ph = m->wPlayerCollisionBox.y;
    if (m->currMotionId == 0x1a) {
        PartyEntry* p = partyGetPtr(marioGetPartyId());
        if (p) {
            ph = partyGetHeight(p);
        }
    }
    return ph;
}
#endif

#ifdef NONMATCHING
void marioHitStrippedPool2(f32* f) {
    f[0] = 18.0f;
}
#endif

#ifdef NONMATCHING
f32 marioChkOverhead(void) {
    Vec pa = {0.0f, 0.0f, 0.0f};
    Vec pb = {0.0f, -1.0f, 0.0f};
    Vec pc = {0.0f, 0.0f, 0.0f};
    Vec pd = {0.0f, 0.0f, 0.0f};
    Vec pos;
    HitEntry* hj;
    f32 h;
    MarioWork* w = marioGetPtr();
    if (w->currMotionId == 8) {
        return w->position.y;
    }
    if (w->currMotionId == 0x14) {
        pos = w->position;
        h = w->wPlayerCollisionBox.y;
        if (!jabaraNoHitChk()) {
            h += 5.0f;
            w->hitobjHead = marioSearchHead_jabara(&pos, &h, &hj, 0.0f);
            if (!w->hitobjHead) {
                w->hitobjHead = marioSearchHead(&pos, &h, (w->flags & 0x10000) ? w->jumpVelocityY : 10.0f);
            }
        }
    } else if (w->flags & 0x1000000) {
        pos = w->position;
        w->hitobjHead = marioSearchHead_roll(&pos, &h, 40.0f);
    } else {
        f32 d;
        pos = w->position;
        h = w->wPlayerCollisionBox.y;
        d = (w->flags & 0x10000) ? w->jumpVelocityY : 10.0f;
        if (w->characterId == 2) {
            w->hitobjHead = kpaSearchHead(&pos, &h, d);
        } else {
            w->hitobjHead = marioSearchHead(&pos, &h, d);
        }
    }
    w->position.x = pos.x;
    if (w->hitobjHead) {
        if (marioChkHeadBlock(w->hitobjHead)) {
            w->baseSpeed = 0.0f;
            w->flags |= 0x80;
        }
        w->flags |= 0x8000000;
        if (w->characterId == 2) {
            marioItemGetDisable();
            if (!kpaGetBodyStatus()) {
                marioClearJumpPara();
            }
        }
        pos.y = (s32)(10.0f * (pos.y - marioGetHeightInl()) + 0.5f) / 10.0f - 1.0f;
        if (!(w->flags & 0x20000) && pos.y < w->lastGroundPos.y) {
            pos.y = w->lastGroundPos.y;
            if (!(w->flags & 0x1000000) && w->currMotionId != 0x19 && w->currMotionId != 0x18 &&
                w->currMotionId != 0x1c && w->characterId != 2 && !marioChkSlitEnd()) {
                if (w->baseSpeed == 0.0f) {
                    if (w->currMotionId != 0) {
                        marioChgStayMotion();
                    }
                } else {
                    marioChgMot(w->baseSpeed > w->mBaseWalkSpeed ? 2 : 1);
                }
            }
        }
        if (w->currMotionId == 3 || w->currMotionId == 6) {
            psndSFXOn_3D((const char*)0x156, &w->position);
            marioClearJumpPara();
            w->flags &= ~0xf0000;
            if (w->characterId != 2) {
                marioChgMot(10);
                marioSetFallPara();
            }
            w->position.y = pos.y;
        }
    } else if (!(w->flags & 0x1000000)) {
        if (h >= 0.0f && h <= 5.0f) {
            w->flags |= 0x8000000;
        } else {
            w->flags &= ~0x8000000;
        }
    } else {
        if (h >= 0.0f && h + w->wPlayerCollisionBox.y <= 47.0f) {
            w->flags |= 0x8000000;
        } else {
            w->flags &= ~0x8000000;
        }
    }
    return pos.y;
}
#endif

#ifdef NONMATCHING
f32 marioChkOverheadJabara(HitEntry** hitOut, f32* distOut) {
    Vec pos;
    f32 new_var; // FAKE: constant temp needed for 100%
    f32 h;
    MarioWork* w;
    w = marioGetPtr();
    *hitOut = NULL;
    *distOut = -1.0f;
    pos = w->position;
    new_var = 5.0f;
    h = w->wPlayerCollisionBox.y;
    if (w->currMotionId == 8) {
        return pos.y;
    }
    if (!jabaraNoHitChk()) {
        h += new_var;
        w->hitobjHead = marioSearchHead_jabara(&pos, &h, hitOut, 0.0f);
        if (!w->hitobjHead) {
            { f32 t = w->wPlayerCollisionBox.y; h = t + new_var; }
            w->hitobjHead = marioSearchHead(&pos, &h, 0.0f);
        }
    }
    w->position.x = pos.x;
    if (w->hitobjHead) {
        w->flags |= 0x8000000;
        pos.y = pos.y - w->wPlayerCollisionBox.y - 0.1f;
        if (w->currMotionId == 3) {
            marioChgMot(0);
        }
    } else if (h > 0.0f) {
        *distOut = h;
        w->flags |= 0x8000000;
    } else {
        w->flags &= ~0x8000000;
    }
    return pos.y;
}
#endif

#ifdef NONMATCHING
static inline HitEntry* marioHitCheck2Val(Vec p, Vec d, Vec* op, Vec* on, f32* dist) {
    return marioHitCheck2(&p, &d, op, on, dist);
}
#endif

#ifdef NONMATCHING
HitEntry* marioSearchHead(Vec* pos, f32* h, f32 dd) {
    Vec p;
    Vec d;
    Vec outPos, outNrm;
    f32 dist;
    f32 hh;
    f32 sx, sz;
    f32 a, ang;
    f32 top;
    f32 x, z;
    HitEntry* hit;
    s32 i;
    void* vp;
    MarioWork* w = marioGetPtr();
    vp = (void*)h;
    if (w->baseSpeed) {
        hh = w->directionView;
    } else {
        hh = toMovedir(w->displayDirection);
    }
    ang = (3.1415927f * hh) / 180.0f;
    sx = sin(ang);
    sx = 0.5f * ((w->wPlayerCollisionBox.x - 0.5f) * sx);
    sz = cos(ang);
    sz = 0.5f * ((w->wPlayerCollisionBox.x - 0.5f) * -sz);
    a = *((f32*)vp);
    hh = 0.5f * a;
    top = a + dd;
    *((f32*)vp) = -1.0f;
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            z = x = 0.0f;
        } else if (i == 1) {
            x = sx;
            z = sz;
        } else if (i == 2) {
            x = -sz;
            z = sx;
        } else if (i == 3) {
            x = sz;
            z = -sx;
        } else if (i == 4) {
            x = -sx;
            z = -sz;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            Vec dir = {0.0f, 1.0f, 0.0f};
            dist = top;
            v.x = pos->x + x;
            v.y = pos->y + hh;
            v.z = pos->z + z;
            p = v;
            d = dir;
            hit = marioHitCheck2(&p, &d, &outPos, &outNrm, &dist);
        }
        if (hit) {
            f32 r = marioHitNrmAngle(&outNrm);
            if (!(w->flags & 0x1000000)) {
                f32 lim = (MF(w, 0x4, u32) & 0x1000000) ? 75.0f : 50.0f;
                if (r <= 180.0f - lim && r >= lim) {
                    hit = NULL;
                }
            }
        }
        if (w->flags & 0x1000000) {
            if (hit) {
                outPos.y = (s32)(100.0f * outPos.y + hh) / 100.0f;
                outPos.y = outPos.y - 0.05f * a;
                if (pos->y + a >= outPos.y) {
                    pos->y = outPos.y;
                    *((f32*)vp) = 0.0f;
                    return hit;
                }
                *((f32*)vp) = outPos.y - pos->y - a;
                return NULL;
            }
        } else {
            if (hit) {
                outPos.y = (s32)(100.0f * outPos.y + hh) / 100.0f;
                if (pos->y + a >= outPos.y) {
                    pos->y = outPos.y;
                    *((f32*)vp) = 0.0f;
                    return hit;
                }
                *((f32*)vp) = outPos.y - pos->y - a;
                return NULL;
            }
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
inline f32 marioSearchHead_roll_cos(f32 a) {
    return (f32)cos(a);
}
#endif

#ifdef NONMATCHING
HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d) {
    f32 a;
    Vec outPos, outNrm;
    f32 x, z;
    f32 dist;
    f32 base, top;
    Vec* pdir;
    s32 i;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    *h = -1.0f;
    base = w->wPlayerCollisionBox.y;
    i = 0;
    top = base + d;
    for (; i < 5; i++) {
        switch (i) {
        case 0:
            z = x = 0.0f;
            break;
        case 1:
            a = (3.1415927f * (90.0f + w->directionView)) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -marioSearchHead_roll_cos(a);
            movePos(&x, &z, 3.0f, w->directionView);
            break;
        case 2:
            a = (3.1415927f * (w->directionView - 90.0f)) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -marioSearchHead_roll_cos(a);
            movePos(&x, &z, 3.0f, w->directionView);
            break;
        case 3:
            a = (3.1415927f * (90.0f + w->directionView)) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -marioSearchHead_roll_cos(a);
            movePos(&x, &z, 3.0f, 180.0f + w->directionView);
            break;
        case 4:
            a = (3.1415927f * (w->directionView - 90.0f)) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -marioSearchHead_roll_cos(a);
            movePos(&x, &z, 3.0f, 180.0f + w->directionView);
            break;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            Vec dir = {0.0f, 1.0f, 0.0f};
            v.x = pos->x + x;
            pdir = &dir;
            v.y = 1.0f + pos->y;
            v.z = pos->z + z;
            dist = top;
            hit = marioHitCheckVecInl(&v, pdir, &outPos, &outNrm, &dist);
        }
        if (hit) {
            if (pos->y + base >= outPos.y) {
                pos->y = outPos.y - base - 1.0f;
                *h = 0.0f;
                return hit;
            }
            {
                f32 t = outPos.y - pos->y - base;
                if (*h < 0.0f) {
                    *h = t;
                } else if (*h > t) {
                    *h = t;
                }
            }
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d) {
    Vec v, dir, outPos, outNrm;
    f32 dist;
    f32 base, top, off;
    HitEntry* hit;
    s32 i;
    MarioWork* w = marioGetPtr();
    *out = NULL;
    i = 0;
    base = *h;
    off = -23.7f;
    *h = -1.0f;
    top = base + d;
    {
    dir = (Vec){0.0f, 1.0f, 0.0f};
    for (; i < 8; i++, off += 5.8f) {
        dist = top;
        v.x = pos->x + off * (f32)sin((3.1415927f * w->targetYaw) / 180.0f);
        v.z = pos->z - off * (f32)cos((3.1415927f * w->targetYaw) / 180.0f);
        v.y = 0.5f + pos->y;
        hit = marioHitCheck2(&v, &dir, &outPos, &outNrm, &dist);
        if (hit) {
            if (hitGetAttr(hit) & 0x40000) {
                if (pos->y + base >= outPos.y) {
                    pos->y = outPos.y;
                    *h = 0.0f;
                    *out = (v.z - pos->z < 0.0f) ? (HitEntry*)-1 : (HitEntry*)1;
                    return hit;
                }
                *h = outPos.y - pos->y - base;
            } else if (i == 3) {
                if (pos->y + base >= outPos.y) {
                    pos->y = outPos.y;
                    *h = 0.0f;
                    *out = NULL;
                    return hit;
                }
                *h = outPos.y - pos->y - base;
            }
        }
    }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
void marioCheckWall(f32 dx, f32 dz) {
    Vec pos;
    f32 h;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x210, f32) = 1000.0f;
    if (dx && w->airTimer == 0) {
        if (MF(w, 0x1c8, f32) < dx) {
            MF(w, 0x1c8, f32) = dx;
            MF(w, 0x1cc, f32) = dz;
            MF(w, 0x1d0, s32) = 14;
        } else {
            if (--MF(w, 0x1d0, s32) <= 0) {
                MF(w, 0x1d0, s32) = 0;
                MF(w, 0x1c8, f32) = dx;
                MF(w, 0x1cc, f32) = dz;
            }
        }
        w->moveDirection = MF(w, 0x1cc, f32);
    } else {
        MF(w, 0x1c8, f32) = 0.0f;
    }
    if (!dx) {
        marioSearchFrontWall_staying(dz);
        dou10_yoko_yari((f32*)((u32)w + 0x210));
        return;
    }
    pos = w->position;
    MF(w, 0x20c, HitEntry*) = NULL;
    hit = searchFrontWall(&pos, &h, dx, dz, w->wPlayerCollisionBox.z);
    if (hit) {
        if (MF(w, 0x20c, HitEntry*)) {
            w->hitobjFront = MF(w, 0x20c, HitEntry*);
        } else {
            w->hitobjFront = hit;
        }
        if (marioChkBero(hit)) {
            if (dx) {
                w->hitobjPush = hit;
                w->hitobjWall = hit;
            }
            movePos(&w->position.x, &w->position.z, dx, dz);
        } else {
            MF(w, 0x210, f32) = h;
            w->hitobjWall = hit;
            if (++MF(w, 0x3f, s8) >= 20) {
                MF(w, 0x3f, s8) = 20;
                if (!(hitGetAttr(hit) & 0x80) ? TRUE : marioGetPtr()->currMotionId == 0x19) {
                    w->hitobjPush = hit;
                }
            }
            w->position = pos;
        }
    } else {
        w->position = pos;
    }
    marioChkWallAround(&w->position, NULL, dx, dz, w->wPlayerCollisionBox.z, w->wPlayerCollisionBox.y);
    dou10_yoko_yari((f32*)((u32)w + 0x210));
}
#endif

#ifdef NONMATCHING
void marioSearchFrontWall_staying(f32 dz) {
    Vec pos;
    f32 h;
    f32 h2;
    f32 ang;
    f32 r;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x3f, s8) = 0;
    r = 0.5f * w->wPlayerCollisionBox.x;
    if (w->flags & 0x100000) {
        r = 0.0f;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, r, w->directionView - w->targetYaw, w->wPlayerCollisionBox.z);
    if (w->currMotionId != 0x13) {
        w->hitobjFront = hit;
    } else {
        w->hitobjFront = NULL;
    }
    if (!hit) {
        f32 a = toMovedir(w->displayDirection);
        pos = w->position;
        hit = searchFrontWall(&pos, &h, r, a, w->wPlayerCollisionBox.z);
        if (w->currMotionId != 0x13) {
            w->hitobjFront = hit;
        } else {
            w->hitobjFront = NULL;
        }
    } else if (!strcmp(gp->currentMapName, (char*)str_802C5940) && vivianGetStatus() != 2 && vivianGetStatus() != 1 && vivianGetStatus() != 3) {
        ang = toMovedir(w->displayDirection);
        pos = w->position;
        movePos(&pos.x, &pos.z, 0.5f * w->wPlayerCollisionBox.x, ang);
        ang += 180.0f;
        hit = searchFrontWall(&pos, &h2, w->wPlayerCollisionBox.x, ang, w->wPlayerCollisionBox.z);
        if (hit && w->wPlayerCollisionBox.x >= h2) {
            w->hitobjFront = hit;
            h = 0.5f * h2;
        }
    }
    if (w->hitobjFront) {
        MF(w, 0x210, f32) = h;
    }
    if (w->buttonBuffer & 0x100) {
        w->hitobjFrontA = NULL;
        pos = w->position;
        if (searchFrontWall(&pos, &h, r, w->directionView, w->wPlayerCollisionBox.z)) {
            w->hitobjFrontA = w->hitobjFront;
        }
    }
    pos = w->position;
    marioChkWallAround(&pos, NULL, 0.0f, dz, w->wPlayerCollisionBox.z, w->wPlayerCollisionBox.y);
    w->position.x = pos.x;
    w->position.z = pos.z;
}
#endif

#ifdef NONMATCHING
void marioCheckWall_roll(f32 dx, f32 dz) {
    Vec pos;
    Vec outPos;
    Vec outNrm;
    f32 h;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x210, f32) = 1000.0f;
    if (dx && w->airTimer == 0) {
        if (MF(w, 0x1c8, f32) < dx) {
            MF(w, 0x1c8, f32) = dx;
            MF(w, 0x1cc, f32) = dz;
            MF(w, 0x1d0, s32) = 14;
        } else {
            if (--MF(w, 0x1d0, s32) <= 0) {
                MF(w, 0x1d0, s32) = 0;
                MF(w, 0x1c8, f32) = dx;
                MF(w, 0x1cc, f32) = dz;
            }
        }
    } else {
        MF(w, 0x1c8, f32) = 0.0f;
    }
    if (dx && w->airTimer == 0) {
        w->moveDirection = MF(w, 0x1cc, f32);
    }
    if (w->flags & 0x10000) {
        f32 dist = 30.0f;
        Vec dir = {0.0f, 1.0f, 0.0f};
        hit = marioHitCheckVecInl(&w->position, &dir, &outPos, &outNrm, &dist);
        if (hit && dist > 16.8f) {
            hit = NULL;
        }
        w->hitobjHead = hit;
        if (hit) {
            w->position.y = outPos.y - w->wPlayerCollisionBox.y;
        }
    }
    if (!dx) {
        marioSearchFrontWall_staying(dz);
        return;
    }
    if (w->hitobjHead) {
        w->baseSpeed = dx = 0.0f;
        w->jumpVelocityY = 0.0f;
        w->jumpAccelerationY = 0.0f;
        w->jumpJerkY = 0.0f;
        w->jumpSnapY = 0.0f;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, dx, dz, w->wPlayerCollisionBox.z);
    if (hit) {
        w->hitobjFront = hit;
        if (marioChkBeroInl(hit)) {
            if (dx) {
                w->hitobjPush = hit;
                do { } while (0);
                w->hitobjWall = hit;
            }
            movePos(&w->position.x, &w->position.z, dx, dz);
        } else {
            MF(w, 0x210, f32) = h;
            w->hitobjWall = hit;
            if (++MF(w, 0x3f, s8) >= 20) {
                MF(w, 0x3f, s8) = 20;
                if (!(hitGetAttr(hit) & 0x80) ? 1 : marioGetPtr()->currMotionId == 0x19) {
                    w->hitobjPush = hit;
                }
            }
            w->position = pos;
        }
    } else {
        w->position = pos;
    }
    pos = w->position;
    marioChkWallAround(&pos, NULL, dx, dz, w->wPlayerCollisionBox.z, w->wPlayerCollisionBox.y);
    w->position.x = pos.x;
    w->position.z = pos.z;
}
#endif

#ifdef NONMATCHING
HitEntry* marioChkFront(f32* out, Vec* pos, f32 angle, f32 dist) {
    Vec outPos, outNrm;
    f32 s, c;
    f32 d;
    HitEntry* hit;
    sincosf(&s, &c, angle);
    d = dist;
    {
        Vec dir = {0.0f, 0.0f, 0.0f};
        dir.x = s;
        dir.z = c;
        hit = marioHitCheckVecInl(pos, &dir, &outPos, &outNrm, &d);
    }
    if (hit && d <= dist) {
        *out = distABf(pos->x, pos->z, outPos.x, outPos.z);
        return hit;
    }
    *out = -1.0f;
    return NULL;
}
#endif

extern BOOL chkBalloon(HitEntry* hit);
#ifdef NONMATCHING
HitEntry* searchFrontWall(Vec* pos, f32* h, f32 dx, f32 dz, f32 w) {
    Vec p;
    Vec dir;
    Vec hp;
    Vec bestNrm;
    Vec nrm;
    f32 heights[4];
    f32 s, c;
    f32 s2, c2;
    f32 half;
    f32 range;
    f32 mx, mz;
    f32 bestDist;
    f32 dist;
    HitEntry* hit2;
    s32 i;
    s32 count;
    HitEntry* best;
    HitEntry* hit;
    MarioWork* mp;

    mp = marioGetPtr();
    if (vivianGetStatus() == 2) {
        return NULL;
    }
    sincosf(&s, &c, dz);
    if (marioChkSts(0x10) && !strcmp(gp->currentMapName, (char*)str_802C5948) &&
        (__fabsf(MF(mp, 0x218, f32)) >= 45.0f || __fabsf(MF(mp, 0x220, f32)) >= 45.0f)) {
        pos->x += dx * s;
        pos->z += dx * c;
        return NULL;
    }
    count = 2;
    if (mp->characterId == 2) {
        if (MF(mp, 0x14, u32) & 1) {
            count = 3;
            heights[0] = 0.75f * mp->wPlayerCollisionBox.y;
            heights[1] = 0.5f * mp->wPlayerCollisionBox.y;
            heights[2] = 11.0f;
        } else {
            heights[0] = 0.75f * mp->wPlayerCollisionBox.y;
            heights[1] = 11.0f;
        }
    } else if (mp->currMotionId == 0x1a) {
        heights[0] = 0.75f * marioGetHeightInl();
        heights[1] = 11.0f;
    } else if (!(mp->flags & 0x1000000)) {
        heights[0] = 27.75f;
        heights[1] = 11.0f;
        if (mp->airTimer) {
            count = 3;
            heights[2] = 0.1f;
        }
    } else {
        heights[0] = 12.0f;
        heights[1] = 11.0f;
        if (mp->airTimer) {
            count = 3;
            heights[2] = 7.0f;
        }
    }
    half = 0.5f * w;
    best = NULL;
    range = half + dx;
    bestDist = range;
    p = *pos;
    dir = (Vec){s, 0.0f, c};
    for (i = 0; i < count; i++) {
        p.y = pos->y + heights[i];
        dist = range;
        hit = marioHitCheckVecInl(&p, &dir, &hp, &nrm, &dist);
        if (hit) {
            if (chkBalloon(hit)) {
                MF(mp, 0x20c, HitEntry*) = hit;
            }
            if (best) {
                if (dist < bestDist) {
                    bestDist = dist;
                    best = hit;
                    bestNrm = nrm;
                }
            } else {
                bestDist = dist;
                best = hit;
                bestNrm = nrm;
            }
        }
    }
    if (best) {
        f32 dot, vz, vx;
        vz = c * dx;
        vx = s * dx;
        dot = vx * bestNrm.x + vz * bestNrm.z;
        mx = 0.5f * (vx - dot * bestNrm.x);
        mz = 0.5f * (vz - dot * bestNrm.z);
    }
    hit2 = NULL;
    sincosf(&s2, &c2, dz + 45.0f);
    {
    Vec dir2;
    p = *pos;
    dir2 = (Vec){s2, 0.0f, c2};
    dist = half;
    for (i = 0; i < count; i++) {
        p.y = pos->y + heights[i];
        dist = half;
        hit2 = marioHitCheckVecInl(&p, &dir2, NULL, NULL, &dist);
        if (hit2) {
            break;
        }
    }
    }
    if (hit2) {
        hit2 = NULL;
        sincosf(&s2, &c2, dz - 45.0f);
        for (i = 0; i < count; i++) {
            p.y = pos->y + heights[i];
            dist = half;
            hit2 = marioHitCheckVecInl(&p, &(Vec){s2, 0.0f, c2}, NULL, NULL, &dist);
        }
    }
    if (best) {
        if (!hit2) {
            *h = dist;
            pos->x += mx;
            pos->z += mz;
        } else {
            *h = 0.0f;
        }
        return best;
    }
    if (!hit2) {
        pos->x += dx * s;
        pos->z += dx * c;
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry* dou10_yoko_yari(f32* out) {
    Vec pos, pos2, outPos, outNrm;
    f32 h;
    f32 d;
    HitEntry* hit;
    f32 step;
    MarioWork* w = marioGetPtr();
    if (w->currMotionId == 0x16) {
        return NULL;
    }
    toMovedir(w->displayDirection);
    hit = w->hitobjFront;
    if (hit) {
        return hit;
    }
    pos = w->position;
    if (!strcmp(gp->currentMapName, (char*)str_802C5940) && vivianGetStatus() != 2 && vivianGetStatus() != 1 && vivianGetStatus() != 3 && !hit) {
        if (w->flags & 0x100000) {
            step = 2.0f;
        } else {
            step = 8.0f;
        }
        d = 100.0f;
        pos2 = pos;
        pos2.y += 60.0f;
        {
            Vec dir = {0.0f, -1.0f, 0.0f};
            hit = marioHitCheckVecInl(&pos2, &dir, &outPos, &outNrm, &d);
        }
        if (hit && (hitGetAttr(hit) & 0x800)) {
            w->hitobjFront = hit;
            *out = 0.8f;
        }
        pos = w->position;
        hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            w->hitobjFront = hit;
            *out = 0.8f;
        }
        pos = w->position;
        movePos(&pos.x, &pos.z, step, 270.0f);
        hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            w->hitobjFront = hit;
            *out = 0.8f;
        }
        if ((!w->flags) && (!w->flags)) {
        }
        pos = w->position;
        movePos(&pos.x, &pos.z, step, 90.0f);
        hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            w->hitobjFront = hit;
            *out = 0.8f;
        }
    }
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* dou10_yoko_yari2(f32* out) {
    Vec pos, pos2, outPos, outNrm;
    f32 h;
    f32 d;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    toMovedir(w->displayDirection);
    pos = w->position;
    if (strcmp(gp->currentMapName, (char*)str_802C5940)) {
        return NULL;
    }
    d = 100.0f;
    pos2 = pos;
    pos2.y += 60.0f;
    {
        Vec dir = {0.0f, -1.0f, 0.0f};
        hit = marioHitCheckVecInl(&pos2, &dir, &outPos, &outNrm, &d);
    }
    if (hit && (hitGetAttr(hit) & 0x800)) {
        w->hitobjFront = hit;
        *out = 0.8f;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
    if (hit && (hitGetAttr(hit) & 0x800)) {
        w->hitobjFront = hit;
        *out = 0.8f;
    }
    pos = w->position;
    movePos(&pos.x, &pos.z, 8.0f, 270.0f);
    hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
    if (hit && (hitGetAttr(hit) & 0x800)) {
        w->hitobjFront = hit;
        *out = 0.8f;
    }
    pos = w->position;
    movePos(&pos.x, &pos.z, 8.0f, 90.0f);
    hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
    if (hit && (hitGetAttr(hit) & 0x800)) {
        w->hitobjFront = hit;
        *out = 0.8f;
    }
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* N_dou10_yoko_yari3(void) {
    HitCheckQuery query;
    f32 s, c;
    f32 x, z;
    f32 y;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    if (strcmp(gp->currentMapName, (char*)str_802C5940)) {
        return NULL;
    }
    x = w->position.x;
    y = w->position.y;
    z = w->position.z;
    movePos(&x, &z, 10.0f, w->directionView);
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.y = y;
        pos.x = x;
        pos.z = z;
        query.targetPos = pos;
        query.targetPos.y += 5.0f;
    }
    sincosf(&s, &c, 0.0f);
    {
        Vec dir = {0.0f, 0.0f, 0.0f};
        dir.x = s;
        dir.z = c;
        query.targetDir = dir;
    }
    query.targetDistance = 40.0f;
    hit = hitCheckVecFilter(&query, NULL);
    if (hit) {
        w->hitobjFront = hit;
        if (1) {
            return hit;
        }
    }
    x = w->position.x;
    y = w->position.y;
    z = w->position.z;
    movePos(&x, &z, -10.0f, w->directionView);
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.y = y;
        pos.x = x;
        pos.z = z;
        query.targetPos = pos;
        query.targetPos.y += 5.0f;
    }
    sincosf(&s, &c, 0.0f);
    {
        Vec dir = {0.0f, 0.0f, 0.0f};
        dir.x = s;
        dir.z = c;
        query.targetDir = dir;
    }
    query.targetDistance = 40.0f;
    hit = hitCheckVecFilter(&query, NULL);
    if (hit) {
        w->hitobjFront = hit;
    }
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* marioChkFrontStep(f32* y, f32* h, f32* ang) {
    Vec outPos;
    Vec outNrm;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 a;
    f32 hh;
    f32 s;
    f32 r;
    f32 dist;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x218, f32) = 0.0f;
    MF(w, 0x21c, f32) = 0.0f;
    MF(w, 0x220, f32) = 0.0f;
    MF(w, 0x214, f32) = 0.0f;
    hh = (w->flags & 0x1000000) ? 18.5f : 0.5f * w->wPlayerCollisionBox.y;
    *y = w->position.y;
    *h = -1.0f;
    if (w->baseSpeed) {
        a = w->directionView;
    } else {
        a = toMovedir(w->displayDirection);
    }
    a = revise360((s32)(0.5f + a));
    if (w->flags & 0x1000000) {
        r = 3.0f;
    } else {
        r = 0.265f * w->wPlayerCollisionBox.x;
    }
    {f32 c; f32 rad = (3.1415927f * a) / 180.0f;
    s = (f32)sin(rad);
    c = (f32)cos(rad);
    s = r * s;
    a = r * -c;}
    y0 = w->position.y;
    x0 = w->position.x;
    z0 = w->position.z;
    {
        Vec v = {0.0f, 0.0f, 0.0f};
        Vec dir = {0.0f, -1.0f, 0.0f};
        v.x = x0 + s;
        v.y = y0 + hh;
        v.z = z0 + a;
        dist = 0.1f + (11.0f + hh);
        hit = marioHitCheckVecInl(&v, &dir, &outPos, &outNrm, &dist);
    }
    if (hit) {
        MF(w, 0x214, f32) = marioHitNrmAnglePtr(&outNrm);
        if (outPos.y < y0 && __fabsf(outPos.y - y0) >= 2.0f) {
            *h = y0 - outPos.y;
            *ang = angleABf(x0, z0, outPos.x, outPos.z);
        } else {
            *y = outPos.y;
            *h = 0.0f;
            *ang = angleABf(x0, z0, outPos.x, outPos.z);
            return hit;
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
void marioHitStrippedPool(f32* f) {
    f[0] = 0.75f;
    f[1] = -1.0f;
    f[2] = 3.1415927f;
    f[3] = 0.1f;
    f[4] = 2.0f;
}
#endif

extern s32 kpaGetStageViewType(void);
#ifdef NONMATCHING
BOOL marioChkWallAround(Vec* pos, void* p, f32 unused, f32 dir, f32 w, f32 h) {
    Vec hi;
    Vec lo;
    Vec d;
    Vec acc;
    Vec saved;
    Vec base2;
    Vec base;
    f32 s, c;
    f32 s2, c2;
    f32 a;
    f32 half;
    f32 d1, d2;
    Vec dd;
    f32 lim;
    f32 step;
    s32 i;
    s32 n;
    BOOL hitAny;
    HitEntry* hit1;
    HitEntry* hit2;

    n = 8;
    hitAny = FALSE;
    if (kpaGetStageViewType() == 0) {
        n = 2;
    }
    step = 360.0f / n;
    a = dir;
    half = 0.5f * w;
    base = *pos;
    hi = base;
    hi.y += 11.0f;
    lo = base;
    lo.y += h - 1.0f;
    acc = (Vec){0.0f, 0.0f, 0.0f};
    for (i = 0; i < n; i++) {
        sincosf(&s, &c, a);
        d1 = half;
        d2 = half;
        d = (Vec){s, 0.0f, c};
        hit1 = marioHitCheckVecInl(&hi, &d, NULL, NULL, &d1);
        hit2 = marioHitCheckVecInl(&lo, &d, NULL, NULL, &d2);
        if (marioChkBeroInl(hit1)) {
            hit1 = NULL;
        }
        if (marioChkBeroInl(hit2)) {
            hit2 = NULL;
        }
        if (hit1 && hit2) {
            if (d1 > d2) {
                d1 = d2;
                hit1 = hit2;
            }
        } else if (hit2) {
            hit1 = hit2;
            d1 = d2;
        }
        if (hit1) {
            f32 t;
            sincosf(&s2, &c2, 180.0f + a);
            t = __fabsf(half - d1);
            hitAny = TRUE;
            acc.x += t * s2;
            acc.z += c2 * t;
        }
        a += step;
    }
    if (!hitAny) {
        return hitAny;
    }
    lim = 0.125f * w;
    if ((s32)p == 0) {
        MarioWork* m = marioGetPtr();
        if (m->currMotionId == 10 || m->currMotionId == 11) {
            lim = 0.25f * w;
        }
    }
    if (lim < 1.0f) {
        lim = 1.0f;
    }
    saved = acc;
    {
        f32 mag = PSVECMag(&acc);
        if (mag > lim) {
            PSVECScale(&acc, &acc, lim / mag);
        }
    }
    PSVECAdd(pos, &acc, pos);

    a = dir;
    base2 = *pos;
    hi = base2;
    hi.y += 11.0f;
    lo = base2;
    lo.y += h - 1.0f;
    acc = (Vec){0.0f, 0.0f, 0.0f};
    for (i = 0; i < n; i++) {
        sincosf(&s, &c, a);
        d1 = half;
        d2 = half;
        dd = (Vec){s, 0.0f, c};
        hit1 = marioHitCheckVecInl(&hi, &dd, NULL, NULL, &d1);
        hit2 = marioHitCheckVecInl(&lo, &dd, NULL, NULL, &d2);
        if (marioChkBeroInl(hit1)) {
            hit1 = NULL;
        }
        if (marioChkBeroInl(hit2)) {
            hit2 = NULL;
        }
        if (hit1 && hit2) {
            if (d1 > d2) {
                d1 = d2;
                hit1 = hit2;
            }
        } else if (hit2) {
            hit1 = hit2;
            d1 = d2;
        }
        if (hit1) {
            f32 t;
            sincosf(&s2, &c2, 180.0f + a);
            t = __fabsf(half - d1);
            hitAny = TRUE;
            acc.x += t * s2;
            acc.z += c2 * t;
        }
        a += step;
    }
    if (!hitAny) {
        return TRUE;
    }
    if (PSVECDotProduct(&saved, &acc) >= 0.0f) {
        return TRUE;
    }
    PSVECScale(&acc, &acc, 0.5f);
    PSVECAdd(pos, &acc, pos);
    return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL marioSlitChkWallAround(void) {
    s32 flags[8];
    Vec pos;
    s32 i;
    f32 a;
    f32 s, c;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    pos = w->position;
    pos.y += 11.0f;
    for (i = 0, a = 0.0f; i < 8; i++, a += 45.0f) {
        Vec dir;
        f32 dist;
        flags[i] = 0;
        sincosf(&s, &c, a);
        dir = (Vec){s, 0.0f, c};
        dist = 13.0f;
        hit = marioHitCheckVecInl(&pos, &dir, NULL, NULL, &dist);
        if (hit && !marioChkBeroInl(hit)) {
            flags[i] = 1;
        }
    }
    { f32 k = 5.0f; pos.y = w->position.y + k; }
    for (i = 0, a = 0.0f; i < 8; i++, a += 45.0f) {
        if (flags[i] != 1) {
            Vec dir;
            f32 dist;
            sincosf(&s, &c, a);
            dir = (Vec){s, 0.0f, c};
            dist = 13.0f;
            hit = marioHitCheckVecInl(&pos, &dir, NULL, NULL, &dist);
            if (hit && !marioChkBeroInl(hit)) {
                flags[i] = 1;
            }
        }
    }
    pos.y = w->position.y + (w->wPlayerCollisionBox.y - 1.0f);
    for (i = 0, a = 0.0f; i < 8; i++, a += 45.0f) {
        if (flags[i] != 1) {
            Vec dir;
            f32 dist;
            sincosf(&s, &c, a);
            dir = (Vec){s, 0.0f, c};
            dist = 13.0f;
            hit = marioHitCheckVecInl(&pos, &dir, NULL, NULL, &dist);
            if (hit && !marioChkBeroInl(hit)) {
                flags[i] = 1;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        if (!flags[i] && !flags[(i + 1) & 7] && !flags[(i + 2) & 7]) {
            return FALSE;
        }
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
void marioCheckWallShip(f32 dx, f32 dz) {
    Vec pos;
    Vec old;
    Vec diff;
    Vec tmp;
    f32 h;
    f32 max;
    f32 mag;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x210, f32) = 1000.0f;
    if (dx && w->airTimer == 0) {
        if (MF(w, 0x1c8, f32) < dx) {
            MF(w, 0x1c8, f32) = dx;
            MF(w, 0x1cc, f32) = dz;
            MF(w, 0x1d0, s32) = 14;
        } else {
            if (--MF(w, 0x1d0, s32) <= 0) {
                MF(w, 0x1d0, s32) = 0;
                MF(w, 0x1c8, f32) = dx;
                MF(w, 0x1cc, f32) = dz;
            }
        }
    } else {
        MF(w, 0x1c8, f32) = 0.0f;
    }
    if (dx && w->airTimer == 0) {
        w->moveDirection = MF(w, 0x1cc, f32);
    }
    if (!dx) {
        marioSearchFrontWall_staying(dz);
        return;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, dx, dz, w->wPlayerCollisionBox.z);
    if (hit) {
        w->hitobjFront = hit;
        if (marioChkBeroInl(hit)) {
            if (dx) {
                w->hitobjPush = hit;
                w->hitobjWall = hit;
            }
            movePos(&w->position.x, &w->position.z, dx, dz);
            pos = w->position;
            return;
        }
        if (!dx) {
            MF(w, 0x3f, s8) = 0;
        } else {
            MF(w, 0x210, f32) = h;
            w->hitobjWall = hit;
            if (++MF(w, 0x3f, s8) >= 20) {
                s32 attr;
                BOOL r;
                MF(w, 0x3f, s8) = 20;
                attr = hitGetAttr(hit);
                r = !(attr & 0x80) ? TRUE : marioGetPtr()->currMotionId == 0x19;
                if (r) w->hitobjPush = hit;
            }
        }
        w->position = pos;
    }
    old = pos;
    w->position = pos;
    tmp = pos;
    marioChkWallAround(&w->position, NULL, dx, dz, w->wPlayerCollisionBox.z, 4.0f);
    max = w->mBaseDashSpeed;
    PSVECSubtract(&w->position, &old, &diff);
    mag = PSVECMag(&diff);
    if (mag > max) {
        PSVECScale(&diff, &diff, max / mag);
        PSVECAdd(&old, &diff, &w->position);
    }
}
#endif


// prototypes for asm stopgap forward references
void marioCheckWallShip(f32 dx, f32 dz);
BOOL marioSlitChkWallAround(void);
BOOL marioChkWallAround(Vec* pos, void* p, f32 unused, f32 dir, f32 w, f32 h);
HitEntry* marioChkFrontStep(f32* y, f32* h, f32* ang);
HitEntry* N_dou10_yoko_yari3(void);
HitEntry* dou10_yoko_yari2(f32* out);
HitEntry* dou10_yoko_yari(f32* out);
HitEntry* searchFrontWall(Vec* pos, f32* h, f32 dx, f32 dz, f32 w);
HitEntry* marioChkFront(f32* out, Vec* pos, f32 angle, f32 dist);
void marioCheckWall_roll(f32 dx, f32 dz);
void marioSearchFrontWall_staying(f32 dz);
void marioCheckWall(f32 dx, f32 dz);
HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d);
HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d);
HitEntry* marioSearchHead(Vec* pos, f32* h, f32 dd);
f32 marioChkOverheadJabara(HitEntry** hitOut, f32* distOut);
f32 marioChkOverhead(void);
HitEntry* marioChkLandon2(f32* y, f32 spd, f32 ofs);
HitEntry* marioLandonChk_old(f32* outY, f32 spd);
HitEntry* marioChkLandon(f32* a, f32 d);
void marioChkToge(void);
HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h);
HitEntry* marioSearchGround(f32* y, f32* b, f32* c, f32 spd, f32 h);
void marioChkGnd2(void);
void marioChkGnd(void);
HitEntry* searchUnder2(f32* out, f32 x, f32 y, f32 z);
HitEntry* marioSearchUnder(void);
BOOL marioChkBero(HitEntry* hit);
void clear_hitobj_ride(void);
HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilterVecRoll(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilterVec(HitCheckQuery* query, HitEntry* entry);
BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry);
void marioHitCheckWidth(void);
#ifndef NONMATCHING
// ASM-STOPGAP: marioHitCheckWidth (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c5730[3] = { 0.0f, 0.0f, 0.0f };
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c573c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5748[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5754[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5760[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c576c[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5778[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5784[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5790[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c579c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57a8[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57b4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57c0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57cc[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57d8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57e4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57f0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c57fc[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5808[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5814[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5820[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c582c[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5838[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5844[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5850[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c585c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5868[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5874[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5880[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c588c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5898[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58a4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58b0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58bc[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58c8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58d4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58e0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58ec[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c58f8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5904[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5910[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802c5920 = 4503601774854144;
__declspec(section ".rodata") const f64 double_0p5_802c5928 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c5930 = 3;
__declspec(section ".rodata") const f64 double_0_802c5938 = 0;
__declspec(section ".rodata") const char str_802C5940[] = "dou_10\000";
__declspec(section ".rodata") const char str_802C5948[] = "eki_04\000";
__declspec(section ".rodata") const char str_802C5950[] = "MOBJ_PowerUpBlock\000\000";
__declspec(section ".rodata") const char str_802C5964[] = "MOBJ_SaveBlock\000";
__declspec(section ".rodata") const char str_802C5974[] = "MOBJ_RecoveryBlock\000";
__declspec(section ".rodata") const char str_802C5988[] = "MOBJ_CoinTakenRecoveryBlock";
__declspec(section ".rodata") const char str_802C59A4[] = "MOBJ_HiddenHatenaBlock\000";
__declspec(section ".rodata") const char str_802C59BC[] = "MOBJ_HiddenBadgeBlock\000\000";
__declspec(section ".rodata") const char str_802C59D4[] = "MOBJ_Hidden10CountBlock";
__declspec(section ".rodata") const u32 gap_04_802C59EC_rodata[1] = { 0x00000000 };
#pragma force_active reset
#pragma force_active on
__declspec(section ".sdata2") const f32 float_1000_8041a7a0 = 1000.0f;
__declspec(section ".sdata2") const f32 float_0_8041a7a4 = 0.0f;
__declspec(section ".sdata2") const f32 float_4_8041a7a8 = 4.0f;
__declspec(section ".sdata2") const f32 float_11_8041a7ac = 11.0f;
__declspec(section ".sdata2") const f32 float_13_8041a7b0 = 13.0f;
__declspec(section ".sdata2") const f32 float_45_8041a7b4 = 45.0f;
__declspec(section ".sdata2") const f32 float_5_8041a7b8 = 5.0f;
__declspec(section ".sdata2") const f32 float_1_8041a7bc = 1.0f;
__declspec(section ".sdata2") const f32 float_360_8041a7c0 = 360.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041a7c4 = 0.5f;
__declspec(section ".sdata2") const f32 float_neg0p5_8041a7c8 = -0.5f;
__declspec(section ".sdata2") const f32 float_180_8041a7cc = 180.0f;
__declspec(section ".sdata2") const f32 float_0p125_8041a7d0 = 0.125f;
__declspec(section ".sdata2") const f32 float_0p25_8041a7d4 = 0.25f;
__declspec(section ".sdata2") const f32 float_0p75_8041a7d8 = 0.75f;
__declspec(section ".sdata2") const f32 float_neg1_8041a7dc = -1.0f;
__declspec(section ".sdata2") const f32 float_3p1416_8041a7e0 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_0p1_8041a7e4 = 0.1f;
__declspec(section ".sdata2") const f32 float_2_8041a7e8 = 2.0f;
__declspec(section ".sdata2") const f32 float_18p5_8041a7ec = 18.5f;
__declspec(section ".sdata2") const f32 float_3_8041a7f0 = 3.0f;
__declspec(section ".sdata2") const f32 float_0p265_8041a7f4 = 0.265f;
__declspec(section ".sdata2") const f32 float_100_8041a7f8 = 100.0f;
__declspec(section ".sdata2") const f32 float_10_8041a7fc = 10.0f;
__declspec(section ".sdata2") const f32 float_40_8041a800 = 40.0f;
__declspec(section ".sdata2") const f32 float_neg10_8041a804 = -10.0f;
__declspec(section ".sdata2") const f32 float_60_8041a808 = 60.0f;
__declspec(section ".sdata2") const f32 float_0p8_8041a80c = 0.8f;
__declspec(section ".sdata2") const f32 float_20_8041a810 = 20.0f;
__declspec(section ".sdata2") const f32 float_8_8041a814 = 8.0f;
__declspec(section ".sdata2") const f32 float_270_8041a818 = 270.0f;
__declspec(section ".sdata2") const f32 float_90_8041a81c = 90.0f;
__declspec(section ".sdata2") const f32 float_27p75_8041a820 = 27.75f;
__declspec(section ".sdata2") const f32 float_12_8041a824 = 12.0f;
__declspec(section ".sdata2") const f32 float_7_8041a828 = 7.0f;
__declspec(section ".sdata2") const f32 float_30_8041a82c = 30.0f;
__declspec(section ".sdata2") const f32 float_16p8_8041a830 = 16.8f;
__declspec(section ".sdata2") const f32 float_neg23p7_8041a834 = -23.7f;
__declspec(section ".sdata2") const f32 float_5p8_8041a838 = 5.8f;
__declspec(section ".sdata2") const f32 float_9_8041a83c = 9.0f;
__declspec(section ".sdata2") const f32 float_75_8041a840 = 75.0f;
__declspec(section ".sdata2") const f32 float_50_8041a844 = 50.0f;
__declspec(section ".sdata2") const f32 float_0p05_8041a848 = 0.05f;
__declspec(section ".sdata2") const f32 float_47_8041a84c = 47.0f;
__declspec(section ".sdata2") const f32 float_18_8041a850 = 18.0f;
__declspec(section ".sdata2") const f32 float_0p01_8041a854 = 0.01f;
__declspec(section ".sdata2") const f32 float_neg10000_8041a858 = -10000.0f;
__declspec(section ".sdata2") const f32 float_8p64_8041a85c = 8.639999f;
__declspec(section ".sdata2") const f32 float_105_8041a860 = 105.0f;
__declspec(section ".sdata2") const f32 float_0p425_8041a864 = 0.425f;
__declspec(section ".sdata2") const f32 float_0p375_8041a868 = 0.375f;
__declspec(section ".sdata2") const f32 float_37_8041a86c = 37.0f;
__declspec(section ".sdata2") const f32 float_neg3000_8041a870 = -3000.0f;
__declspec(section ".sdata2") const f32 float_5000_8041a874 = 5000.0f;
__declspec(section ".sdata2") const f32 float_neg0p4_8041a878 = -0.4f;
__declspec(section ".sdata2") const f32 float_neg0p06_8041a87c = -0.06f;
__declspec(section ".sdata2") const f32 float_neg0p04_8041a880 = -0.04f;
__declspec(section ".sdata2") const f32 float_neg0p02_8041a884 = -0.02f;
__declspec(section ".sdata2") const f32 float_1037_8041a888 = 1037.0f;
__declspec(section ".sdata2") const f32 float_6_8041a88c = 6.0f;

HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h);
#pragma force_active on
__declspec(section ".data") static void* jumptable_8030E5C0[] = {
    (char*)marioSearchGroundRoll + 0x170,
    (char*)marioSearchGroundRoll + 0x180,
    (char*)marioSearchGroundRoll + 0x1D4,
    (char*)marioSearchGroundRoll + 0x228,
    (char*)marioSearchGroundRoll + 0x24C,
    (char*)marioSearchGroundRoll + 0x25C,
    (char*)marioSearchGroundRoll + 0x2C4,
};
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback);
s32 hitGetAttr(HitEntry* hit);
BOOL marioChkSts(s32 flags);
void marioGetJabaraState();
MarioWork* marioGetPtr(void);
void movePos(float* ret_sin, float* ret_cos, f32 a3, f32 degree);
f32 revise360(f32 angle);
void sincosf(f32* ret_sin, f32* ret_cos, f32 degree);
int strcmp(const char *s1, const char *s2);
f32 toMovedir(f32 angle);
s32 vivianGetStatus(void);
BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilterVec(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilterVecRoll(HitCheckQuery* query, HitEntry* entry);
BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry);
asm void marioCheckWallShip(f32 dx, f32 dz) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	fmr f30, f1
	fmr f31, f2
	bl marioGetPtr
	lfs f0, float_0_8041a7a4(r2)
	mr r31, r3
	lfs f1, float_1000_8041a7a0(r2)
	fcmpu cr0, f30, f0
	stfs f1, 0x210(r3)
	beq @1
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @1
	lfs f0, 0x1c8(r31)
	fcmpo cr0, f0, f30
	bge @2
	stfs f30, 0x1c8(r31)
	li r0, 0xe
	stfs f31, 0x1cc(r31)
	stw r0, 0x1d0(r31)
	b @3
	@2:
	lwz r3, 0x1d0(r31)
	subic. r0, r3, 0x1
	stw r0, 0x1d0(r31)
	bgt @3
	li r0, 0x0
	stw r0, 0x1d0(r31)
	stfs f30, 0x1c8(r31)
	stfs f31, 0x1cc(r31)
	b @3
	@1:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x1c8(r31)
	@3:
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f30, f0
	beq @4
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @4
	lfs f0, 0x1cc(r31)
	stfs f0, 0x19c(r31)
	@4:
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f30, f0
	bne @5
	fmr f1, f31
	bl marioSearchFrontWall_staying
	b @6
	@5:
	lwz r5, 0x8c(r31)
	fmr f1, f30
	lwz r0, 0x90(r31)
	fmr f2, f31
	addi r3, r1, 0x30
	addi r4, r1, 0x8
	stw r5, 0x30(r1)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	lfs f3, 0x1bc(r31)
	bl searchFrontWall
	mr. r30, r3
	beq @7
	stw r30, 0x1e0(r31)
	bl hitGetAttr
	mr r29, r3
	bl marioGetPtr
	rlwinm. r0, r29, 0, 12, 12
	beq @8
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @8
	li r0, 0x0
	b @9
	@8:
	rlwinm. r0, r29, 0, 24, 24
	bne @10
	extrwi r0, r29, 1, 8
	b @9
	@10:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@9:
	cmpwi r0, 0x0
	beq @11
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f30, f0
	beq @12
	stw r30, 0x1ec(r31)
	stw r30, 0x1f0(r31)
	@12:
	fmr f1, f30
	addi r3, r31, 0x8c
	fmr f2, f31
	addi r4, r31, 0x94
	bl movePos
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0x30(r1)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	b @6
	@11:
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f30, f0
	bne @13
	li r0, 0x0
	stb r0, 0x3f(r31)
	b @14
	@13:
	lfs f0, 0x8(r1)
	stfs f0, 0x210(r31)
	stw r30, 0x1f0(r31)
	lbz r3, 0x3f(r31)
	addi r3, r3, 0x1
	extsb r0, r3
	stb r3, 0x3f(r31)
	cmpwi r0, 0x14
	blt @14
	li r0, 0x14
	mr r3, r30
	stb r0, 0x3f(r31)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 24, 24
	bne @15
	li r0, 0x1
	b @16
	@15:
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@16:
	cmpwi r0, 0x0
	beq @14
	stw r30, 0x1ec(r31)
	@14:
	lwz r3, 0x30(r1)
	lwz r0, 0x34(r1)
	stw r3, 0x8c(r31)
	stw r0, 0x90(r31)
	lwz r0, 0x38(r1)
	stw r0, 0x94(r31)
	@7:
	lwz r6, 0x30(r1)
	fmr f1, f30
	lwz r5, 0x34(r1)
	fmr f2, f31
	lwz r0, 0x38(r1)
	addi r3, r31, 0x8c
	stw r6, 0x24(r1)
	lfs f4, float_4_8041a7a8(r2)
	li r4, 0x0
	stw r5, 0x28(r1)
	stw r0, 0x2c(r1)
	stw r6, 0x8c(r31)
	stw r5, 0x90(r31)
	stw r0, 0x94(r31)
	stw r6, 0xc(r1)
	lfs f3, 0x1bc(r31)
	stw r5, 0x10(r1)
	stw r0, 0x14(r1)
	bl marioChkWallAround
	lfs f31, 0x188(r31)
	addi r3, r31, 0x8c
	addi r4, r1, 0x24
	addi r5, r1, 0x18
	bl PSVECSubtract
	addi r3, r1, 0x18
	bl PSVECMag
	fcmpo cr0, f1, f31
	ble @6
	fdivs f1, f31, f1
	addi r3, r1, 0x18
	mr r4, r3
	bl PSVECScale
	addi r3, r1, 0x24
	addi r4, r1, 0x18
	addi r5, r31, 0x8c
	bl PSVECAdd
	@6:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r0, 0x74(r1)
	lwz r29, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm BOOL marioSlitChkWallAround(void) {
	nofralloc
	stwu r1, -0x180(r1)
	mflr r0
	stw r0, 0x184(r1)
	stfd f31, 0x170(r1)
	psq_st f31, 0x178(r1), 0, 0
	stfd f30, 0x160(r1)
	psq_st f30, 0x168(r1), 0, 0
	stfd f29, 0x150(r1)
	psq_st f29, 0x158(r1), 0, 0
	stmw r23, 0x12c(r1)
	lis r3, vec3_802c5730@ha
	addi r31, r3, vec3_802c5730@l
	bl marioGetPtr
	mr r29, r3
	addi r30, r1, 0x40
	lwz r0, 0x90(r3)
	mr r25, r30
	lwz r26, 0x8c(r3)
	li r24, 0x0
	stw r0, 0x38(r1)
	lwz r27, 0x94(r3)
	lfs f1, 0x38(r1)
	lfs f0, float_11_8041a7ac(r2)
	stw r26, 0x34(r1)
	fadds f0, f1, f0
	lfs f29, float_0_8041a7a4(r2)
	stw r27, 0x3c(r1)
	lfs f30, float_13_8041a7b0(r2)
	stfs f0, 0x38(r1)
	lfs f31, float_45_8041a7b4(r2)
	lwz r28, 0x38(r1)
	@1:
	li r0, 0x0
	fmr f1, f29
	stw r0, 0x0(r25)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl sincosf
	lwz r3, 0x1c8(r31)
	lwz r0, 0x1d0(r31)
	stw r3, 0x28(r1)
	lfs f1, 0xc(r1)
	stw r0, 0x30(r1)
	lfs f0, 0x8(r1)
	lwz r4, 0x1cc(r31)
	stfs f1, 0x28(r1)
	stfs f0, 0x30(r1)
	lwz r3, 0x28(r1)
	lwz r0, 0x30(r1)
	stw r4, 0x2c(r1)
	stw r26, 0xec(r1)
	stw r28, 0xf0(r1)
	stw r27, 0xf4(r1)
	stw r3, 0xf8(r1)
	stw r4, 0xfc(r1)
	stw r0, 0x100(r1)
	stfs f30, 0x11c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @2
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0xe0
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @3
	@2:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @4
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0xe0
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @3
	@4:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0xe0
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@3:
	cmplwi r3, 0x0
	bne @5
	li r3, 0x0
	@5:
	cmplwi r3, 0x0
	beq @6
	bl hitGetAttr
	mr r23, r3
	bl marioGetPtr
	rlwinm. r0, r23, 0, 12, 12
	beq @7
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @7
	li r0, 0x0
	b @8
	@7:
	rlwinm. r0, r23, 0, 24, 24
	bne @9
	extrwi r0, r23, 1, 8
	b @8
	@9:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@8:
	cmpwi r0, 0x0
	bne @6
	li r0, 0x1
	stw r0, 0x0(r25)
	@6:
	addi r24, r24, 0x1
	fadds f29, f29, f31
	cmpwi r24, 0x8
	addi r25, r25, 0x4
	blt @1
	lfs f1, 0x90(r29)
	mr r25, r30
	lfs f0, float_5_8041a7b8(r2)
	li r26, 0x0
	lfs f30, float_0_8041a7a4(r2)
	fadds f0, f1, f0
	lfs f31, float_45_8041a7b4(r2)
	stfs f0, 0x38(r1)
	@10:
	lwz r0, 0x0(r25)
	cmpwi r0, 0x1
	beq @11
	fmr f1, f30
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl sincosf
	lwz r3, 0x1d4(r31)
	lwz r0, 0x1dc(r31)
	stw r3, 0x1c(r1)
	lfs f1, 0xc(r1)
	stw r0, 0x24(r1)
	lfs f0, 0x8(r1)
	lwz r7, 0x1d8(r31)
	stfs f1, 0x1c(r1)
	lwz r6, 0x34(r1)
	stfs f0, 0x24(r1)
	lwz r5, 0x38(r1)
	lwz r4, 0x3c(r1)
	lwz r3, 0x1c(r1)
	lwz r0, 0x24(r1)
	lfs f0, float_13_8041a7b0(r2)
	stw r7, 0x20(r1)
	stw r6, 0xac(r1)
	stw r5, 0xb0(r1)
	stw r4, 0xb4(r1)
	stw r3, 0xb8(r1)
	stw r7, 0xbc(r1)
	stw r0, 0xc0(r1)
	stfs f0, 0xdc(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @12
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0xa0
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @13
	@12:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @14
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0xa0
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @13
	@14:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0xa0
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@13:
	cmplwi r3, 0x0
	bne @15
	li r3, 0x0
	@15:
	cmplwi r3, 0x0
	beq @11
	bl hitGetAttr
	mr r24, r3
	bl marioGetPtr
	rlwinm. r0, r24, 0, 12, 12
	beq @16
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @16
	li r0, 0x0
	b @17
	@16:
	rlwinm. r0, r24, 0, 24, 24
	bne @18
	extrwi r0, r24, 1, 8
	b @17
	@18:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@17:
	cmpwi r0, 0x0
	bne @11
	li r0, 0x1
	stw r0, 0x0(r25)
	@11:
	addi r26, r26, 0x1
	fadds f30, f30, f31
	cmpwi r26, 0x8
	addi r25, r25, 0x4
	blt @10
	lfs f1, 0x1b8(r29)
	mr r25, r30
	lfs f0, float_1_8041a7bc(r2)
	li r26, 0x0
	lfs f2, 0x90(r29)
	fsubs f0, f1, f0
	lfs f30, float_0_8041a7a4(r2)
	lfs f31, float_45_8041a7b4(r2)
	fadds f0, f2, f0
	stfs f0, 0x38(r1)
	@19:
	lwz r0, 0x0(r25)
	cmpwi r0, 0x1
	beq @20
	fmr f1, f30
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl sincosf
	lwz r3, 0x1e0(r31)
	lwz r0, 0x1e8(r31)
	stw r3, 0x10(r1)
	lfs f1, 0xc(r1)
	stw r0, 0x18(r1)
	lfs f0, 0x8(r1)
	lwz r7, 0x1e4(r31)
	stfs f1, 0x10(r1)
	lwz r6, 0x34(r1)
	stfs f0, 0x18(r1)
	lwz r5, 0x38(r1)
	lwz r4, 0x3c(r1)
	lwz r3, 0x10(r1)
	lwz r0, 0x18(r1)
	lfs f0, float_13_8041a7b0(r2)
	stw r7, 0x14(r1)
	stw r6, 0x6c(r1)
	stw r5, 0x70(r1)
	stw r4, 0x74(r1)
	stw r3, 0x78(r1)
	stw r7, 0x7c(r1)
	stw r0, 0x80(r1)
	stfs f0, 0x9c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @21
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x60
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @22
	@21:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @23
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x60
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @22
	@23:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x60
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@22:
	cmplwi r3, 0x0
	bne @24
	li r3, 0x0
	@24:
	cmplwi r3, 0x0
	beq @20
	bl hitGetAttr
	mr r24, r3
	bl marioGetPtr
	rlwinm. r0, r24, 0, 12, 12
	beq @25
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @25
	li r0, 0x0
	b @26
	@25:
	rlwinm. r0, r24, 0, 24, 24
	bne @27
	extrwi r0, r24, 1, 8
	b @26
	@27:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@26:
	cmpwi r0, 0x0
	bne @20
	li r0, 0x1
	stw r0, 0x0(r25)
	@20:
	addi r26, r26, 0x1
	fadds f30, f30, f31
	cmpwi r26, 0x8
	addi r25, r25, 0x4
	blt @19
	li r0, 0x2
	addi r3, r1, 0x40
	li r4, 0x0
	mtctr r0
	@28:
	lwz r0, 0x0(r30)
	cmpwi r0, 0x0
	bne @29
	addi r0, r4, 0x1
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @29
	addi r0, r4, 0x2
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @29
	li r3, 0x0
	b @30
	@29:
	lwz r0, 0x4(r30)
	cmpwi r0, 0x0
	bne @31
	addi r0, r4, 0x2
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @31
	addi r0, r4, 0x3
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @31
	li r3, 0x0
	b @30
	@31:
	lwz r0, 0x8(r30)
	cmpwi r0, 0x0
	bne @32
	addi r0, r4, 0x3
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @32
	addi r0, r4, 0x4
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @32
	li r3, 0x0
	b @30
	@32:
	lwz r0, 0xc(r30)
	cmpwi r0, 0x0
	bne @33
	addi r0, r4, 0x4
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @33
	addi r0, r4, 0x5
	clrlslwi r0, r0, 29, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x0
	bne @33
	li r3, 0x0
	b @30
	@33:
	addi r30, r30, 0x10
	addi r4, r4, 0x4
	bdnz @28
	li r3, 0x1
	@30:
	psq_l f31, 0x178(r1), 0, 0
	lfd f31, 0x170(r1)
	psq_l f30, 0x168(r1), 0, 0
	lfd f30, 0x160(r1)
	psq_l f29, 0x158(r1), 0, 0
	lfd f29, 0x150(r1)
	lmw r23, 0x12c(r1)
	lwz r0, 0x184(r1)
	mtlr r0
	addi r1, r1, 0x180
	blr
}

asm BOOL marioChkWallAround(Vec* pos, void* p, f32 unused, f32 dir, f32 w, f32 h) {
	nofralloc
	stwu r1, -0x260(r1)
	mflr r0
	stw r0, 0x264(r1)
	stfd f31, 0x250(r1)
	psq_st f31, 0x258(r1), 0, 0
	stfd f30, 0x240(r1)
	psq_st f30, 0x248(r1), 0, 0
	stfd f29, 0x230(r1)
	psq_st f29, 0x238(r1), 0, 0
	stfd f28, 0x220(r1)
	psq_st f28, 0x228(r1), 0, 0
	stfd f27, 0x210(r1)
	psq_st f27, 0x218(r1), 0, 0
	stfd f26, 0x200(r1)
	psq_st f26, 0x208(r1), 0, 0
	stfd f25, 0x1f0(r1)
	psq_st f25, 0x1f8(r1), 0, 0
	stfd f24, 0x1e0(r1)
	psq_st f24, 0x1e8(r1), 0, 0
	stmw r19, 0x1ac(r1)
	fmr f24, f2
	lis r5, vec3_802c5730@ha
	fmr f25, f3
	mr r22, r3
	fmr f26, f4
	mr r21, r4
	addi r31, r5, vec3_802c5730@l
	li r27, 0x8
	li r24, 0x0
	bl kpaGetStageViewType
	cmpwi r3, 0x0
	bne @1
	li r27, 0x2
	@1:
	xoris r3, r27, 0x8000
	lis r0, 0x4330
	stw r3, 0x194(r1)
	fmr f30, f24
	lwz r5, 0x4(r22)
	li r29, 0x0
	stw r0, 0x190(r1)
	lfd f1, 0x1f0(r31)
	lfd f0, 0x190(r1)
	lfs f2, float_360_8041a7c0(r2)
	fsubs f1, f0, f1
	lwz r30, 0x0(r22)
	lwz r28, 0x8(r22)
	lfs f0, float_1_8041a7bc(r2)
	fdivs f27, f2, f1
	stw r5, 0x88(r1)
	lfs f1, float_0p5_8041a7c4(r2)
	lwz r4, 0x198(r31)
	lwz r3, 0x19c(r31)
	stw r5, 0x7c(r1)
	fmuls f31, f1, f25
	lwz r0, 0x1a0(r31)
	fsubs f0, f26, f0
	lfs f1, 0x7c(r1)
	lfs f3, 0x88(r1)
	lfs f2, float_11_8041a7ac(r2)
	fadds f0, f1, f0
	stw r30, 0x30(r1)
	fadds f1, f3, f2
	stw r5, 0x34(r1)
	stfs f1, 0x88(r1)
	stfs f0, 0x7c(r1)
	lwz r26, 0x88(r1)
	stw r28, 0x38(r1)
	lwz r25, 0x7c(r1)
	stw r30, 0x84(r1)
	stw r28, 0x8c(r1)
	stw r30, 0x78(r1)
	stw r28, 0x80(r1)
	stw r4, 0x60(r1)
	stw r3, 0x64(r1)
	stw r0, 0x68(r1)
	b @2
	@3:
	fmr f1, f30
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	bl sincosf
	lwz r3, 0x1a4(r31)
	fmr f29, f31
	lwz r0, 0x1ac(r31)
	fmr f28, f31
	stw r3, 0x48(r1)
	lfs f1, 0x14(r1)
	stw r0, 0x50(r1)
	lfs f0, 0x10(r1)
	lwz r4, 0x1a8(r31)
	stfs f1, 0x48(r1)
	lwz r3, 0x48(r1)
	stfs f0, 0x50(r1)
	lwz r0, 0x50(r1)
	stw r4, 0x4c(r1)
	stw r3, 0x6c(r1)
	stw r4, 0x70(r1)
	stw r0, 0x74(r1)
	stw r30, 0x15c(r1)
	stw r26, 0x160(r1)
	stw r28, 0x164(r1)
	stw r3, 0x168(r1)
	stw r4, 0x16c(r1)
	stw r0, 0x170(r1)
	stfs f31, 0x18c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @4
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x150
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @5
	@4:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @6
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x150
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @5
	@6:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x150
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@5:
	cmplwi r3, 0x0
	bne @7
	li r23, 0x0
	b @8
	@7:
	lfs f1, 0x18c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @9
	lfs f0, float_0p5_8041a7c4(r2)
	b @10
	@9:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@10:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x198(r1)
	mr r23, r3
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x190(r1)
	lwz r0, 0x194(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x19c(r1)
	lfd f0, 0x198(r1)
	fsubs f0, f0, f1
	fdivs f29, f0, f2
	@8:
	lwz r4, 0x6c(r1)
	lwz r3, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r30, 0x11c(r1)
	stw r25, 0x120(r1)
	stw r28, 0x124(r1)
	stw r4, 0x128(r1)
	stw r3, 0x12c(r1)
	stw r0, 0x130(r1)
	stfs f28, 0x14c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @11
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @12
	@11:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @13
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @12
	@13:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@12:
	cmplwi r3, 0x0
	bne @14
	li r19, 0x0
	b @15
	@14:
	lfs f1, 0x14c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @16
	lfs f0, float_0p5_8041a7c4(r2)
	b @17
	@16:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@17:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x190(r1)
	mr r19, r3
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x198(r1)
	lwz r0, 0x19c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x194(r1)
	lfd f0, 0x190(r1)
	fsubs f0, f0, f1
	fdivs f28, f0, f2
	@15:
	mr r3, r23
	bl hitGetAttr
	mr r20, r3
	bl marioGetPtr
	rlwinm. r0, r20, 0, 12, 12
	beq @18
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @18
	li r0, 0x0
	b @19
	@18:
	rlwinm. r0, r20, 0, 24, 24
	bne @20
	extrwi r0, r20, 1, 8
	b @19
	@20:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@19:
	cmpwi r0, 0x0
	beq @21
	li r23, 0x0
	@21:
	mr r3, r19
	bl hitGetAttr
	mr r20, r3
	bl marioGetPtr
	rlwinm. r0, r20, 0, 12, 12
	beq @22
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @22
	li r0, 0x0
	b @23
	@22:
	rlwinm. r0, r20, 0, 24, 24
	bne @24
	extrwi r0, r20, 1, 8
	b @23
	@24:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@23:
	cmpwi r0, 0x0
	beq @25
	li r19, 0x0
	@25:
	cmplwi r23, 0x0
	beq @26
	cmplwi r19, 0x0
	beq @26
	fcmpo cr0, f29, f28
	ble @27
	fmr f29, f28
	mr r23, r19
	b @27
	@26:
	cmplwi r19, 0x0
	beq @27
	mr r23, r19
	fmr f29, f28
	@27:
	cmplwi r23, 0x0
	beq @28
	lfs f0, float_180_8041a7cc(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	fadds f1, f0, f30
	bl sincosf
	fsubs f0, f31, f29
	lfs f4, 0xc(r1)
	lfs f2, 0x60(r1)
	li r24, 0x1
	lfs f1, 0x8(r1)
	fabs f3, f0
	lfs f0, 0x68(r1)
	fmadds f2, f4, f3, f2
	fmadds f0, f1, f3, f0
	stfs f2, 0x60(r1)
	stfs f0, 0x68(r1)
	@28:
	fadds f30, f30, f27
	addi r29, r29, 0x1
	@2:
	cmpw r29, r27
	blt @3
	cmpwi r24, 0x0
	bne @29
	mr r3, r24
	b @30
	@29:
	lfs f0, float_0p125_8041a7d0(r2)
	cmpwi r21, 0x0
	fmuls f28, f0, f25
	bne @31
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0xa
	beq @32
	cmplwi r0, 0xb
	bne @31
	@32:
	lfs f0, float_0p25_8041a7d4(r2)
	fmuls f28, f0, f25
	@31:
	lfs f0, float_1_8041a7bc(r2)
	fcmpo cr0, f28, f0
	bge @33
	fmr f28, f0
	@33:
	lwz r5, 0x60(r1)
	addi r3, r1, 0x60
	lwz r4, 0x64(r1)
	lwz r0, 0x68(r1)
	stw r5, 0x54(r1)
	stw r4, 0x58(r1)
	stw r0, 0x5c(r1)
	bl PSVECMag
	fcmpo cr0, f1, f28
	ble @34
	fdivs f1, f28, f1
	addi r3, r1, 0x60
	mr r4, r3
	bl PSVECScale
	@34:
	mr r3, r22
	mr r5, r22
	addi r4, r1, 0x60
	bl PSVECAdd
	lwz r5, 0x4(r22)
	fmr f30, f24
	lfs f0, float_1_8041a7bc(r2)
	li r30, 0x0
	stw r5, 0x88(r1)
	fsubs f0, f26, f0
	lwz r28, 0x0(r22)
	stw r5, 0x7c(r1)
	lfs f3, 0x88(r1)
	lfs f2, float_11_8041a7ac(r2)
	lfs f1, 0x7c(r1)
	fadds f2, f3, f2
	lwz r29, 0x8(r22)
	fadds f0, f1, f0
	lwz r4, 0x1b0(r31)
	lwz r3, 0x1b4(r31)
	stfs f2, 0x88(r1)
	lwz r0, 0x1b8(r31)
	stfs f0, 0x7c(r1)
	lwz r25, 0x88(r1)
	stw r28, 0x24(r1)
	lwz r26, 0x7c(r1)
	stw r5, 0x28(r1)
	stw r29, 0x2c(r1)
	stw r28, 0x84(r1)
	stw r29, 0x8c(r1)
	stw r28, 0x78(r1)
	stw r29, 0x80(r1)
	stw r4, 0x60(r1)
	stw r3, 0x64(r1)
	stw r0, 0x68(r1)
	b @35
	@36:
	fmr f1, f30
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	bl sincosf
	lwz r3, 0x1bc(r31)
	fmr f24, f31
	lwz r0, 0x1c4(r31)
	fmr f25, f31
	stw r3, 0x3c(r1)
	lfs f1, 0x14(r1)
	stw r0, 0x44(r1)
	lfs f0, 0x10(r1)
	lwz r4, 0x1c0(r31)
	stfs f1, 0x3c(r1)
	lwz r3, 0x3c(r1)
	stfs f0, 0x44(r1)
	lwz r0, 0x44(r1)
	stw r4, 0x40(r1)
	stw r3, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	stw r28, 0xdc(r1)
	stw r25, 0xe0(r1)
	stw r29, 0xe4(r1)
	stw r3, 0xe8(r1)
	stw r4, 0xec(r1)
	stw r0, 0xf0(r1)
	stfs f31, 0x10c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @37
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @38
	@37:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @39
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @38
	@39:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@38:
	cmplwi r3, 0x0
	bne @40
	li r23, 0x0
	b @41
	@40:
	lfs f1, 0x10c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @42
	lfs f0, float_0p5_8041a7c4(r2)
	b @43
	@42:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@43:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x190(r1)
	mr r23, r3
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x198(r1)
	lwz r0, 0x19c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x194(r1)
	lfd f0, 0x190(r1)
	fsubs f0, f0, f1
	fdivs f24, f0, f2
	@41:
	lwz r4, 0x18(r1)
	lwz r3, 0x1c(r1)
	lwz r0, 0x20(r1)
	stw r28, 0x9c(r1)
	stw r26, 0xa0(r1)
	stw r29, 0xa4(r1)
	stw r4, 0xa8(r1)
	stw r3, 0xac(r1)
	stw r0, 0xb0(r1)
	stfs f25, 0xcc(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @44
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @45
	@44:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @46
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @45
	@46:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@45:
	cmplwi r3, 0x0
	bne @47
	li r19, 0x0
	b @48
	@47:
	lfs f1, 0xcc(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @49
	lfs f0, float_0p5_8041a7c4(r2)
	b @50
	@49:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@50:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x190(r1)
	mr r19, r3
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x198(r1)
	lwz r0, 0x19c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x194(r1)
	lfd f0, 0x190(r1)
	fsubs f0, f0, f1
	fdivs f25, f0, f2
	@48:
	mr r3, r23
	bl hitGetAttr
	mr r20, r3
	bl marioGetPtr
	rlwinm. r0, r20, 0, 12, 12
	beq @51
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @51
	li r0, 0x0
	b @52
	@51:
	rlwinm. r0, r20, 0, 24, 24
	bne @53
	extrwi r0, r20, 1, 8
	b @52
	@53:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@52:
	cmpwi r0, 0x0
	beq @54
	li r23, 0x0
	@54:
	mr r3, r19
	bl hitGetAttr
	mr r20, r3
	bl marioGetPtr
	rlwinm. r0, r20, 0, 12, 12
	beq @55
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @55
	li r0, 0x0
	b @56
	@55:
	rlwinm. r0, r20, 0, 24, 24
	bne @57
	extrwi r0, r20, 1, 8
	b @56
	@57:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@56:
	cmpwi r0, 0x0
	beq @58
	li r19, 0x0
	@58:
	cmplwi r23, 0x0
	beq @59
	cmplwi r19, 0x0
	beq @59
	fcmpo cr0, f24, f25
	ble @60
	fmr f24, f25
	mr r23, r19
	b @60
	@59:
	cmplwi r19, 0x0
	beq @60
	mr r23, r19
	fmr f24, f25
	@60:
	cmplwi r23, 0x0
	beq @61
	lfs f0, float_180_8041a7cc(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	fadds f1, f0, f30
	bl sincosf
	fsubs f0, f31, f24
	lfs f4, 0xc(r1)
	lfs f2, 0x60(r1)
	li r24, 0x1
	lfs f1, 0x8(r1)
	fabs f3, f0
	lfs f0, 0x68(r1)
	fmadds f2, f4, f3, f2
	fmadds f0, f1, f3, f0
	stfs f2, 0x60(r1)
	stfs f0, 0x68(r1)
	@61:
	fadds f30, f30, f27
	addi r30, r30, 0x1
	@35:
	cmpw r30, r27
	blt @36
	cmpwi r24, 0x0
	bne @62
	li r3, 0x1
	b @30
	@62:
	addi r3, r1, 0x54
	addi r4, r1, 0x60
	bl PSVECDotProduct
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @63
	li r3, 0x1
	b @30
	@63:
	addi r3, r1, 0x60
	lfs f1, float_0p5_8041a7c4(r2)
	mr r4, r3
	bl PSVECScale
	mr r3, r22
	mr r5, r22
	addi r4, r1, 0x60
	bl PSVECAdd
	li r3, 0x1
	@30:
	psq_l f31, 0x258(r1), 0, 0
	lfd f31, 0x250(r1)
	psq_l f30, 0x248(r1), 0, 0
	lfd f30, 0x240(r1)
	psq_l f29, 0x238(r1), 0, 0
	lfd f29, 0x230(r1)
	psq_l f28, 0x228(r1), 0, 0
	lfd f28, 0x220(r1)
	psq_l f27, 0x218(r1), 0, 0
	lfd f27, 0x210(r1)
	psq_l f26, 0x208(r1), 0, 0
	lfd f26, 0x200(r1)
	psq_l f25, 0x1f8(r1), 0, 0
	lfd f25, 0x1f0(r1)
	psq_l f24, 0x1e8(r1), 0, 0
	lfd f24, 0x1e0(r1)
	lmw r19, 0x1ac(r1)
	lwz r0, 0x264(r1)
	mtlr r0
	addi r1, r1, 0x260
	blr
}

asm HitEntry* marioChkFrontStep(f32* y, f32* h, f32* ang) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stfd f27, 0xc0(r1)
	psq_st f27, 0xc8(r1), 0, 0
	stmw r25, 0xa4(r1)
	lis r6, vec3_802c5730@ha
	mr r26, r3
	mr r27, r4
	mr r28, r5
	addi r30, r6, vec3_802c5730@l
	bl marioGetPtr
	lfs f0, float_0_8041a7a4(r2)
	mr r31, r3
	stfs f0, 0x218(r3)
	stfs f0, 0x21c(r3)
	stfs f0, 0x220(r3)
	stfs f0, 0x214(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @1
	lfs f31, float_18p5_8041a7ec(r2)
	b @2
	@1:
	lfs f1, float_0p5_8041a7c4(r2)
	lfs f0, 0x1b8(r31)
	fmuls f31, f1, f0
	@2:
	lfs f0, 0x90(r31)
	lfs f1, float_neg1_8041a7dc(r2)
	stfs f0, 0x0(r26)
	lfs f0, float_0_8041a7a4(r2)
	stfs f1, 0x0(r27)
	lfs f1, 0x180(r31)
	fcmpu cr0, f1, f0
	beq @3
	lfs f1, 0x1a0(r31)
	b @4
	@3:
	lfs f1, 0x1a8(r31)
	bl toMovedir
	@4:
	lfs f0, float_0p5_8041a7c4(r2)
	lis r0, 0x4330
	stw r0, 0x78(r1)
	fadds f0, f0, f1
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x70(r1)
	lwz r0, 0x74(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f1, f0, f1
	bl revise360
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq @5
	lfs f27, float_3_8041a7f0(r2)
	b @6
	@5:
	lfs f2, float_0p265_8041a7f4(r2)
	lfs f0, 0x1b4(r31)
	fmuls f27, f2, f0
	@6:
	lfs f2, float_3p1416_8041a7e0(r2)
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f29, f1, f0
	fmr f1, f29
	bl sin
	frsp f28, f1
	fmr f1, f29
	bl cos
	frsp f1, f1
	lfs f29, 0x90(r31)
	lwz r4, 0x180(r30)
	fmuls f0, f27, f28
	lfs f30, 0x8c(r31)
	fadds f3, f29, f31
	fneg f1, f1
	lwz r3, 0x184(r30)
	lwz r0, 0x188(r30)
	fadds f4, f30, f0
	lfs f0, float_11_8041a7ac(r2)
	fmuls f1, f27, f1
	lfs f28, 0x94(r31)
	fadds f0, f0, f31
	stw r4, 0xc(r1)
	fadds f2, f28, f1
	lfs f1, float_0p1_8041a7e4(r2)
	stw r3, 0x10(r1)
	fadds f0, f1, f0
	lwz r4, 0x18c(r30)
	stw r0, 0x14(r1)
	lwz r3, 0x190(r30)
	stfs f4, 0xc(r1)
	lwz r0, 0x194(r30)
	stfs f3, 0x10(r1)
	lwz r7, 0xc(r1)
	stfs f2, 0x14(r1)
	lwz r6, 0x10(r1)
	lwz r5, 0x14(r1)
	stw r7, 0x3c(r1)
	stw r6, 0x40(r1)
	stw r5, 0x44(r1)
	stw r4, 0x48(r1)
	stw r3, 0x4c(r1)
	stw r0, 0x50(r1)
	stfs f0, 0x6c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @7
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @8
	@7:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @9
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @8
	@9:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@8:
	cmplwi r3, 0x0
	bne @10
	li r3, 0x0
	b @11
	@10:
	lwz r0, 0x54(r1)
	lwz r4, 0x58(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x5c(r1)
	lfs f1, 0x24(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x28(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x2c(r1)
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041a7c4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@13:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x70(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x28(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x24(r1)
	cror eq, gt, eq
	bne @14
	lfs f0, float_0p5_8041a7c4(r2)
	b @15
	@14:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@15:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x88(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x2c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x28(r1)
	cror eq, gt, eq
	bne @16
	lfs f0, float_0p5_8041a7c4(r2)
	b @17
	@16:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@17:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x98(r1)
	addic. r0, r1, 0x18
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x2c(r1)
	beq @11
	lwz r5, 0x60(r1)
	lwz r4, 0x64(r1)
	lwz r0, 0x68(r1)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	@11:
	cmplwi r3, 0x0
	mr r29, r3
	beq @18
	bl marioGetPtr
	lfs f1, float_0_8041a7a4(r2)
	mr r25, r3
	lfs f4, float_100_8041a7f8(r2)
	lfs f3, 0x20(r1)
	fmr f2, f1
	lfs f0, 0x1c(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f7, float_100_8041a7f8(r2)
	fsubs f4, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	lfs f2, float_0_8041a7a4(r2)
	lfs f3, 0x18(r1)
	fmadds f6, f7, f4, f0
	lfs f0, 0x1c(r1)
	stw r0, 0x90(r1)
	fmr f1, f2
	fmuls f4, f7, f0
	lfd f5, 0x1f0(r30)
	fctiwz f0, f6
	fmuls f3, f7, f3
	stfd f0, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f7
	stfs f0, 0x218(r25)
	stfs f2, 0x21c(r25)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f2, 0x18(r1)
	fsubs f3, f1, f0
	lfs f0, 0x20(r1)
	lfs f5, float_100_8041a7f8(r2)
	fmuls f1, f2, f2
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f0, f0
	fmadds f4, f5, f3, f2
	stw r0, 0x80(r1)
	lfd f2, 0x1f0(r30)
	fadds f3, f1, f0
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f0, 0x80(r1)
	fsubs f0, f0, f2
	fdivs f0, f0, f5
	stfs f0, 0x220(r25)
	ble @19
	frsqrte f1, f3
	lfd f4, 0x1f8(r30)
	lfd f2, 0x200(r30)
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
	lfd f0, 0x208(r30)
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
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x1c(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f2, 0x28(r1)
	stfs f1, 0x214(r31)
	fcmpo cr0, f2, f29
	bge @28
	fsubs f1, f2, f29
	lfs f0, float_2_8041a7e8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @28
	fsubs f0, f29, f2
	lfs f3, 0x24(r1)
	fmr f1, f30
	lfs f4, 0x2c(r1)
	fmr f2, f28
	stfs f0, 0x0(r27)
	bl angleABf
	stfs f1, 0x0(r28)
	b @18
	@28:
	lfs f3, 0x28(r1)
	fmr f1, f30
	lfs f0, float_0_8041a7a4(r2)
	fmr f2, f28
	stfs f3, 0x0(r26)
	lfs f3, 0x24(r1)
	stfs f0, 0x0(r27)
	lfs f4, 0x2c(r1)
	bl angleABf
	stfs f1, 0x0(r28)
	mr r3, r29
	b @29
	@18:
	li r3, 0x0
	@29:
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	psq_l f27, 0xc8(r1), 0, 0
	lfd f27, 0xc0(r1)
	lmw r25, 0xa4(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm HitEntry* N_dou10_yoko_yari3(void) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stw r31, 0x8c(r1)
	stw r30, 0x88(r1)
	lis r3, vec3_802c5730@ha
	addi r30, r3, vec3_802c5730@l
	bl marioGetPtr
	lwz r5, gp(r13)
	mr r31, r3
	addi r4, r30, 0x210
	addi r3, r5, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	li r3, 0x0
	b @2
	@1:
	lfs f0, 0x8c(r31)
	addi r3, r1, 0xc
	lfs f1, float_10_8041a7fc(r2)
	addi r4, r1, 0x8
	stfs f0, 0xc(r1)
	lfs f31, 0x90(r31)
	lfs f0, 0x94(r31)
	stfs f0, 0x8(r1)
	lfs f2, 0x1a0(r31)
	bl movePos
	lwz r0, 0x154(r30)
	addi r3, r1, 0x14
	lwz r6, 0x150(r30)
	addi r4, r1, 0x10
	stw r0, 0x40(r1)
	lwz r5, 0x158(r30)
	stfs f31, 0x40(r1)
	lfs f3, 0xc(r1)
	lwz r0, 0x40(r1)
	stw r6, 0x3c(r1)
	lfs f2, 0x8(r1)
	stw r0, 0x58(r1)
	lfs f0, float_5_8041a7b8(r2)
	stw r5, 0x44(r1)
	lfs f1, 0x58(r1)
	stfs f3, 0x3c(r1)
	fadds f0, f1, f0
	lfs f1, float_0_8041a7a4(r2)
	stfs f2, 0x44(r1)
	lwz r5, 0x3c(r1)
	lwz r0, 0x44(r1)
	stw r5, 0x54(r1)
	stw r0, 0x5c(r1)
	stfs f0, 0x58(r1)
	bl sincosf
	lwz r5, 0x15c(r30)
	addi r3, r1, 0x48
	lwz r0, 0x164(r30)
	li r4, 0x0
	stw r5, 0x30(r1)
	lfs f0, 0x14(r1)
	stw r0, 0x38(r1)
	lfs f1, 0x10(r1)
	lwz r6, 0x160(r30)
	stfs f0, 0x30(r1)
	lfs f0, float_40_8041a800(r2)
	stfs f1, 0x38(r1)
	lwz r5, 0x30(r1)
	lwz r0, 0x38(r1)
	stw r6, 0x34(r1)
	stw r5, 0x60(r1)
	stw r6, 0x64(r1)
	stw r0, 0x68(r1)
	stfs f0, 0x84(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @3
	stw r3, 0x1e0(r31)
	b @2
	@3:
	lfs f0, 0x8c(r31)
	addi r3, r1, 0xc
	lfs f1, float_neg10_8041a804(r2)
	addi r4, r1, 0x8
	stfs f0, 0xc(r1)
	lfs f31, 0x90(r31)
	lfs f0, 0x94(r31)
	stfs f0, 0x8(r1)
	lfs f2, 0x1a0(r31)
	bl movePos
	lwz r0, 0x16c(r30)
	addi r3, r1, 0x14
	lwz r6, 0x168(r30)
	addi r4, r1, 0x10
	stw r0, 0x28(r1)
	lwz r5, 0x170(r30)
	stfs f31, 0x28(r1)
	lfs f3, 0xc(r1)
	lwz r0, 0x28(r1)
	stw r6, 0x24(r1)
	lfs f2, 0x8(r1)
	stw r0, 0x58(r1)
	lfs f0, float_5_8041a7b8(r2)
	stw r5, 0x2c(r1)
	lfs f1, 0x58(r1)
	stfs f3, 0x24(r1)
	fadds f0, f1, f0
	lfs f1, float_0_8041a7a4(r2)
	stfs f2, 0x2c(r1)
	lwz r5, 0x24(r1)
	lwz r0, 0x2c(r1)
	stw r5, 0x54(r1)
	stw r0, 0x5c(r1)
	stfs f0, 0x58(r1)
	bl sincosf
	lwz r5, 0x174(r30)
	addi r3, r1, 0x48
	lwz r0, 0x17c(r30)
	li r4, 0x0
	stw r5, 0x18(r1)
	lfs f0, 0x14(r1)
	stw r0, 0x20(r1)
	lfs f1, 0x10(r1)
	lwz r6, 0x178(r30)
	stfs f0, 0x18(r1)
	lfs f0, float_40_8041a800(r2)
	stfs f1, 0x20(r1)
	lwz r5, 0x18(r1)
	lwz r0, 0x20(r1)
	stw r6, 0x1c(r1)
	stw r5, 0x60(r1)
	stw r6, 0x64(r1)
	stw r0, 0x68(r1)
	stfs f0, 0x84(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	beq @2
	stw r3, 0x1e0(r31)
	@2:
	psq_l f31, 0x98(r1), 0, 0
	lwz r0, 0xa4(r1)
	lfd f31, 0x90(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm HitEntry* dou10_yoko_yari2(f32* out) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stw r31, 0xbc(r1)
	stw r30, 0xb8(r1)
	mr r30, r3
	stw r29, 0xb4(r1)
	stw r28, 0xb0(r1)
	bl marioGetPtr
	mr r31, r3
	lfs f1, 0x1a8(r3)
	bl toMovedir
	lwz r5, 0x8c(r31)
	lis r3, str_802C5940@ha
	lwz r0, 0x90(r31)
	addi r4, r3, str_802C5940@l
	lwz r3, gp(r13)
	stw r5, 0x30(r1)
	addi r3, r3, 0x12c
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r0, 0x34(r1)
	lis r3, vec3_802c5874@ha
	addi r5, r3, vec3_802c5874@l
	lwz r7, 0x30(r1)
	stw r0, 0x28(r1)
	lwz r6, 0x38(r1)
	lfs f1, 0x28(r1)
	lfs f0, float_60_8041a808(r2)
	lwz r4, 0x0(r5)
	fadds f1, f1, f0
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	lfs f0, float_100_8041a7f8(r2)
	stfs f1, 0x28(r1)
	lwz r5, 0x28(r1)
	stw r7, 0x24(r1)
	stw r6, 0x2c(r1)
	stw r7, 0x48(r1)
	stw r5, 0x4c(r1)
	stw r6, 0x50(r1)
	stw r4, 0x54(r1)
	stw r3, 0x58(r1)
	stw r0, 0x5c(r1)
	stfs f0, 0x78(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @3
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @4
	@3:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @5
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @4
	@5:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@4:
	cmplwi r3, 0x0
	bne @6
	li r29, 0x0
	b @7
	@6:
	lwz r0, 0x60(r1)
	lwz r4, 0x64(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x68(r1)
	lfs f1, 0x18(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x1c(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x20(r1)
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041a7c4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@9:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x88(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f3, f1, f0
	lfs f4, 0x1c(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x18(r1)
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041a7c4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@11:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x98(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x20(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x1c(r1)
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041a7c4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@13:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa8(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0xc
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0xa0(r1)
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x20(r1)
	beq @14
	lwz r5, 0x6c(r1)
	lwz r4, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r5, 0xc(r1)
	stw r4, 0x10(r1)
	stw r0, 0x14(r1)
	@14:
	mr r29, r3
	@7:
	cmplwi r29, 0x0
	beq @15
	mr r3, r29
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @15
	stw r29, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@15:
	lwz r5, 0x8c(r31)
	addi r3, r1, 0x30
	lwz r0, 0x90(r31)
	addi r4, r1, 0x8
	lfs f1, float_20_8041a810(r2)
	stw r5, 0x30(r1)
	fmr f3, f1
	lfs f2, float_0_8041a7a4(r2)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl searchFrontWall
	mr. r29, r3
	beq @16
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @16
	stw r29, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@16:
	lwz r5, 0x8c(r31)
	addi r28, r1, 0x38
	lwz r0, 0x90(r31)
	mr r4, r28
	lfs f1, float_8_8041a814(r2)
	addi r3, r1, 0x30
	stw r5, 0x30(r1)
	lfs f2, float_270_8041a818(r2)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl movePos
	lfs f1, float_20_8041a810(r2)
	addi r3, r1, 0x30
	lfs f2, float_0_8041a7a4(r2)
	addi r4, r1, 0x8
	fmr f3, f1
	bl searchFrontWall
	mr. r29, r3
	beq @17
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @17
	stw r29, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@17:
	lwz r5, 0x8c(r31)
	mr r4, r28
	lwz r0, 0x90(r31)
	addi r3, r1, 0x30
	lfs f1, float_8_8041a814(r2)
	stw r5, 0x30(r1)
	lfs f2, float_90_8041a81c(r2)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl movePos
	lfs f1, float_20_8041a810(r2)
	addi r3, r1, 0x30
	lfs f2, float_0_8041a7a4(r2)
	addi r4, r1, 0x8
	fmr f3, f1
	bl searchFrontWall
	mr. r28, r3
	beq @18
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @18
	stw r28, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@18:
	mr r3, r28
	@2:
	lwz r0, 0xc4(r1)
	lwz r31, 0xbc(r1)
	lwz r30, 0xb8(r1)
	lwz r29, 0xb4(r1)
	lwz r28, 0xb0(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm HitEntry* dou10_yoko_yari(f32* out) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stfd f31, 0xc0(r1)
	psq_st f31, 0xc8(r1), 0, 0
	stw r31, 0xbc(r1)
	stw r30, 0xb8(r1)
	stw r29, 0xb4(r1)
	stw r28, 0xb0(r1)
	mr r30, r3
	bl marioGetPtr
	mr r31, r3
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x16
	bne @1
	li r3, 0x0
	b @2
	@1:
	lfs f1, 0x1a8(r31)
	bl toMovedir
	lwz r28, 0x1e0(r31)
	cmplwi r28, 0x0
	beq @3
	mr r3, r28
	b @2
	@3:
	lwz r5, 0x8c(r31)
	lis r3, str_802C5940@ha
	lwz r0, 0x90(r31)
	addi r4, r3, str_802C5940@l
	lwz r3, gp(r13)
	stw r5, 0x30(r1)
	addi r3, r3, 0x12c
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @4
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq @4
	bl vivianGetStatus
	cmpwi r3, 0x3
	beq @4
	cmplwi r28, 0x0
	bne @4
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 11, 11
	beq @5
	lfs f31, float_2_8041a7e8(r2)
	b @6
	@5:
	lfs f31, float_8_8041a814(r2)
	@6:
	lwz r0, 0x34(r1)
	lis r3, vec3_802c5868@ha
	addi r5, r3, vec3_802c5868@l
	lwz r7, 0x30(r1)
	stw r0, 0x28(r1)
	lwz r6, 0x38(r1)
	lfs f1, 0x28(r1)
	lfs f0, float_60_8041a808(r2)
	lwz r4, 0x0(r5)
	fadds f1, f1, f0
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	lfs f0, float_100_8041a7f8(r2)
	stfs f1, 0x28(r1)
	lwz r5, 0x28(r1)
	stw r7, 0x24(r1)
	stw r6, 0x2c(r1)
	stw r7, 0x48(r1)
	stw r5, 0x4c(r1)
	stw r6, 0x50(r1)
	stw r4, 0x54(r1)
	stw r3, 0x58(r1)
	stw r0, 0x5c(r1)
	stfs f0, 0x78(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @7
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @8
	@7:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @9
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @8
	@9:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@8:
	cmplwi r3, 0x0
	bne @10
	li r29, 0x0
	b @11
	@10:
	lwz r0, 0x60(r1)
	lwz r4, 0x64(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x68(r1)
	lfs f1, 0x18(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x1c(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x20(r1)
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041a7c4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@13:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x88(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f3, f1, f0
	lfs f4, 0x1c(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x18(r1)
	cror eq, gt, eq
	bne @14
	lfs f0, float_0p5_8041a7c4(r2)
	b @15
	@14:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@15:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x98(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x20(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x1c(r1)
	cror eq, gt, eq
	bne @16
	lfs f0, float_0p5_8041a7c4(r2)
	b @17
	@16:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@17:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa8(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0xc
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0xa0(r1)
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x20(r1)
	beq @18
	lwz r5, 0x6c(r1)
	lwz r4, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r5, 0xc(r1)
	stw r4, 0x10(r1)
	stw r0, 0x14(r1)
	@18:
	mr r29, r3
	@11:
	cmplwi r29, 0x0
	beq @19
	mr r3, r29
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @19
	stw r29, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@19:
	lwz r5, 0x8c(r31)
	addi r3, r1, 0x30
	lwz r0, 0x90(r31)
	addi r4, r1, 0x8
	lfs f1, float_20_8041a810(r2)
	stw r5, 0x30(r1)
	fmr f3, f1
	lfs f2, float_0_8041a7a4(r2)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl searchFrontWall
	mr. r29, r3
	beq @20
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @20
	stw r29, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@20:
	lwz r3, 0x8c(r31)
	addi r28, r1, 0x38
	lwz r0, 0x90(r31)
	fmr f1, f31
	lfs f2, float_270_8041a818(r2)
	mr r4, r28
	stw r3, 0x30(r1)
	addi r3, r1, 0x30
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl movePos
	lfs f1, float_20_8041a810(r2)
	addi r3, r1, 0x30
	lfs f2, float_0_8041a7a4(r2)
	addi r4, r1, 0x8
	fmr f3, f1
	bl searchFrontWall
	mr. r29, r3
	beq @21
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @21
	stw r29, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@21:
	lwz r5, 0x8c(r31)
	fmr f1, f31
	lwz r0, 0x90(r31)
	mr r4, r28
	lfs f2, float_90_8041a81c(r2)
	addi r3, r1, 0x30
	stw r5, 0x30(r1)
	stw r0, 0x34(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x38(r1)
	bl movePos
	lfs f1, float_20_8041a810(r2)
	addi r3, r1, 0x30
	lfs f2, float_0_8041a7a4(r2)
	addi r4, r1, 0x8
	fmr f3, f1
	bl searchFrontWall
	mr. r28, r3
	beq @4
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @4
	stw r28, 0x1e0(r31)
	lfs f0, float_0p8_8041a80c(r2)
	stfs f0, 0x0(r30)
	@4:
	mr r3, r28
	@2:
	psq_l f31, 0xc8(r1), 0, 0
	lwz r0, 0xd4(r1)
	lfd f31, 0xc0(r1)
	lwz r31, 0xbc(r1)
	lwz r30, 0xb8(r1)
	lwz r29, 0xb4(r1)
	lwz r28, 0xb0(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm HitEntry* searchFrontWall(Vec* pos, f32* h, f32 dx, f32 dz, f32 w) {
	nofralloc
	stwu r1, -0x250(r1)
	mflr r0
	stw r0, 0x254(r1)
	stfd f31, 0x240(r1)
	psq_st f31, 0x248(r1), 0, 0
	stfd f30, 0x230(r1)
	psq_st f30, 0x238(r1), 0, 0
	stfd f29, 0x220(r1)
	psq_st f29, 0x228(r1), 0, 0
	stfd f28, 0x210(r1)
	psq_st f28, 0x218(r1), 0, 0
	stfd f27, 0x200(r1)
	psq_st f27, 0x208(r1), 0, 0
	stfd f26, 0x1f0(r1)
	psq_st f26, 0x1f8(r1), 0, 0
	stfd f25, 0x1e0(r1)
	psq_st f25, 0x1e8(r1), 0, 0
	stfd f24, 0x1d0(r1)
	psq_st f24, 0x1d8(r1), 0, 0
	stmw r19, 0x19c(r1)
	fmr f24, f1
	lis r5, vec3_802c5730@ha
	fmr f25, f2
	mr r30, r3
	fmr f26, f3
	mr r20, r4
	addi r31, r5, vec3_802c5730@l
	bl marioGetPtr
	mr r24, r3
	bl vivianGetStatus
	cmpwi r3, 0x2
	bne @1
	li r3, 0x0
	b @2
	@1:
	fmr f1, f25
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	bl sincosf
	li r3, 0x10
	bl marioChkSts
	cmpwi r3, 0x0
	beq @3
	lwz r3, gp(r13)
	addi r4, r31, 0x218
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @3
	lfs f0, 0x218(r24)
	lfs f1, float_45_8041a7b4(r2)
	fabs f0, f0
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	beq @4
	lfs f0, 0x220(r24)
	fabs f0, f0
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @3
	@4:
	lfs f1, 0x14(r1)
	li r3, 0x0
	lfs f0, 0x0(r30)
	fmadds f0, f24, f1, f0
	stfs f0, 0x0(r30)
	lfs f1, 0x10(r1)
	lfs f0, 0x8(r30)
	fmadds f0, f24, f1, f0
	stfs f0, 0x8(r30)
	b @2
	@3:
	lbz r0, 0x3c(r24)
	li r29, 0x2
	cmpwi r0, 0x2
	bne @5
	lwz r0, 0x14(r24)
	clrlwi. r0, r0, 31
	beq @6
	lfs f0, float_0p75_8041a7d8(r2)
	li r29, 0x3
	lfs f3, 0x1b8(r24)
	lfs f1, float_0p5_8041a7c4(r2)
	fmuls f2, f0, f3
	lfs f0, float_11_8041a7ac(r2)
	fmuls f1, f1, f3
	stfs f0, 0x50(r1)
	stfs f2, 0x48(r1)
	stfs f1, 0x4c(r1)
	b @7
	@6:
	lfs f2, float_0p75_8041a7d8(r2)
	lfs f1, 0x1b8(r24)
	lfs f0, float_11_8041a7ac(r2)
	fmuls f1, f2, f1
	stfs f0, 0x4c(r1)
	stfs f1, 0x48(r1)
	b @7
	@5:
	lhz r0, 0x2e(r24)
	cmplwi r0, 0x1a
	bne @8
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	lfs f27, 0x1b8(r3)
	cmplwi r0, 0x1a
	bne @9
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @9
	bl partyGetHeight
	fmr f27, f1
	@9:
	lfs f1, float_0p75_8041a7d8(r2)
	lfs f0, float_11_8041a7ac(r2)
	fmuls f1, f1, f27
	stfs f0, 0x4c(r1)
	stfs f1, 0x48(r1)
	b @7
	@8:
	lwz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 7, 7
	bne @10
	lha r0, 0x50(r24)
	lfs f1, float_27p75_8041a820(r2)
	lfs f0, float_11_8041a7ac(r2)
	cmpwi r0, 0x0
	stfs f1, 0x48(r1)
	stfs f0, 0x4c(r1)
	beq @7
	lfs f0, float_0p1_8041a7e4(r2)
	li r29, 0x3
	stfs f0, 0x50(r1)
	b @7
	@10:
	lha r0, 0x50(r24)
	lfs f1, float_12_8041a824(r2)
	lfs f0, float_11_8041a7ac(r2)
	cmpwi r0, 0x0
	stfs f1, 0x48(r1)
	stfs f0, 0x4c(r1)
	beq @7
	lfs f0, float_7_8041a828(r2)
	li r29, 0x3
	stfs f0, 0x50(r1)
	@7:
	lfs f0, float_0p5_8041a7c4(r2)
	addi r28, r1, 0x48
	lwz r3, 0x114(r31)
	mr r23, r28
	lwz r0, 0x11c(r31)
	fmuls f31, f0, f26
	stw r3, 0x3c(r1)
	li r27, 0x0
	lfs f0, 0x14(r1)
	li r22, 0x0
	fadds f30, f31, f24
	stfs f0, 0x3c(r1)
	lwz r25, 0x118(r31)
	lwz r5, 0x0(r30)
	fmr f27, f30
	lwz r4, 0x4(r30)
	lwz r3, 0x8(r30)
	lwz r26, 0x3c(r1)
	stw r0, 0x44(r1)
	lfs f0, 0x10(r1)
	stw r5, 0x88(r1)
	stfs f0, 0x44(r1)
	lwz r21, 0x44(r1)
	stw r4, 0x8c(r1)
	stw r3, 0x90(r1)
	stw r25, 0x40(r1)
	stw r26, 0x7c(r1)
	stw r25, 0x80(r1)
	stw r21, 0x84(r1)
	b @11
	@12:
	lfs f1, 0x4(r30)
	fmr f26, f30
	lfs f0, 0x0(r23)
	lwz r3, 0x88(r1)
	fadds f0, f1, f0
	lwz r0, 0x90(r1)
	stw r3, 0x120(r1)
	stfs f0, 0x8c(r1)
	lwz r3, 0x8c(r1)
	stw r0, 0x128(r1)
	stw r3, 0x124(r1)
	stw r26, 0x12c(r1)
	stw r25, 0x130(r1)
	stw r21, 0x134(r1)
	stfs f30, 0x150(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @13
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x114
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @14
	@13:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @15
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x114
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @14
	@15:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x114
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@14:
	cmplwi r3, 0x0
	bne @16
	li r19, 0x0
	b @17
	@16:
	lfs f1, 0x150(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @18
	lfs f0, float_0p5_8041a7c4(r2)
	b @19
	@18:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@19:
	lfs f2, float_1000_8041a7a0(r2)
	lis r5, 0x4330
	lwz r0, 0x138(r1)
	fmadds f0, f2, f1, f0
	lwz r4, 0x13c(r1)
	stw r0, 0x70(r1)
	lwz r0, 0x140(r1)
	fctiwz f0, f0
	stw r5, 0x160(r1)
	lfd f1, 0x1f0(r31)
	lfs f4, 0x70(r1)
	stfd f0, 0x158(r1)
	lfs f0, float_0_8041a7a4(r2)
	lwz r5, 0x15c(r1)
	fcmpo cr0, f4, f0
	stw r4, 0x74(r1)
	xoris r4, r5, 0x8000
	stw r4, 0x164(r1)
	lfd f0, 0x160(r1)
	stw r0, 0x78(r1)
	fsubs f0, f0, f1
	fdivs f26, f0, f2
	cror eq, gt, eq
	bne @20
	lfs f0, float_0p5_8041a7c4(r2)
	b @21
	@20:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@21:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x170(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r31)
	lfs f4, 0x74(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x168(r1)
	lwz r0, 0x16c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x70(r1)
	cror eq, gt, eq
	bne @22
	lfs f0, float_0p5_8041a7c4(r2)
	b @23
	@22:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@23:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x180(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r31)
	lfs f4, 0x78(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x178(r1)
	lwz r0, 0x17c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x184(r1)
	lfd f0, 0x180(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x74(r1)
	cror eq, gt, eq
	bne @24
	lfs f0, float_0p5_8041a7c4(r2)
	b @25
	@24:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@25:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x190(r1)
	addic. r0, r1, 0x58
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x188(r1)
	lwz r0, 0x18c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x194(r1)
	lfd f0, 0x190(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x78(r1)
	beq @26
	lwz r5, 0x144(r1)
	lwz r4, 0x148(r1)
	lwz r0, 0x14c(r1)
	stw r5, 0x58(r1)
	stw r4, 0x5c(r1)
	stw r0, 0x60(r1)
	@26:
	mr r19, r3
	@17:
	cmplwi r19, 0x0
	beq @27
	mr r3, r19
	bl chkBalloon
	cmpwi r3, 0x0
	beq @28
	stw r19, 0x20c(r24)
	@28:
	cmplwi r27, 0x0
	beq @29
	fcmpo cr0, f26, f27
	bge @27
	lwz r4, 0x58(r1)
	fmr f27, f26
	lwz r3, 0x5c(r1)
	mr r27, r19
	lwz r0, 0x60(r1)
	stw r4, 0x64(r1)
	stw r3, 0x68(r1)
	stw r0, 0x6c(r1)
	b @27
	@29:
	lwz r4, 0x58(r1)
	fmr f27, f26
	lwz r3, 0x5c(r1)
	mr r27, r19
	lwz r0, 0x60(r1)
	stw r4, 0x64(r1)
	stw r3, 0x68(r1)
	stw r0, 0x6c(r1)
	@27:
	addi r23, r23, 0x4
	addi r22, r22, 0x1
	@11:
	cmpw r22, r29
	blt @12
	cmplwi r27, 0x0
	beq @30
	lfs f1, 0x10(r1)
	lfs f0, 0x14(r1)
	fmuls f4, f1, f24
	lfs f5, 0x6c(r1)
	fmuls f3, f0, f24
	lfs f1, 0x64(r1)
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f4, f5
	fmadds f0, f3, f1, f0
	fnmsubs f1, f0, f1, f3
	fnmsubs f0, f0, f5, f4
	fmuls f29, f2, f1
	fmuls f28, f2, f0
	@30:
	lfs f0, float_45_8041a7b4(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	li r26, 0x0
	fadds f1, f0, f25
	bl sincosf
	lwz r3, 0x120(r31)
	fmr f26, f31
	lwz r0, 0x128(r31)
	mr r23, r28
	stw r3, 0x30(r1)
	li r24, 0x0
	lfs f1, 0xc(r1)
	stw r0, 0x38(r1)
	lfs f0, 0x8(r1)
	lwz r22, 0x124(r31)
	stfs f1, 0x30(r1)
	lwz r4, 0x0(r30)
	stfs f0, 0x38(r1)
	lwz r3, 0x4(r30)
	lwz r0, 0x8(r30)
	lwz r21, 0x30(r1)
	lwz r25, 0x38(r1)
	stw r4, 0x88(r1)
	stw r3, 0x8c(r1)
	stw r0, 0x90(r1)
	stw r22, 0x34(r1)
	stw r21, 0x18(r1)
	stw r22, 0x1c(r1)
	stw r25, 0x20(r1)
	b @31
	@32:
	lfs f1, 0x4(r30)
	fmr f26, f31
	lfs f0, 0x0(r23)
	lwz r3, 0x88(r1)
	fadds f0, f1, f0
	lwz r0, 0x90(r1)
	stw r3, 0xe0(r1)
	stfs f0, 0x8c(r1)
	lwz r3, 0x8c(r1)
	stw r0, 0xe8(r1)
	stw r3, 0xe4(r1)
	stw r21, 0xec(r1)
	stw r22, 0xf0(r1)
	stw r25, 0xf4(r1)
	stfs f31, 0x110(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @33
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0xd4
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @34
	@33:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @35
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0xd4
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @34
	@35:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0xd4
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@34:
	cmplwi r3, 0x0
	bne @36
	li r3, 0x0
	b @37
	@36:
	lfs f1, 0x110(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @38
	lfs f0, float_0p5_8041a7c4(r2)
	b @39
	@38:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@39:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x188(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x190(r1)
	lwz r0, 0x194(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x18c(r1)
	lfd f0, 0x188(r1)
	fsubs f0, f0, f1
	fdivs f26, f0, f2
	@37:
	cmplwi r3, 0x0
	mr r26, r3
	bne @40
	addi r23, r23, 0x4
	addi r24, r24, 0x1
	@31:
	cmpw r24, r29
	blt @32
	@40:
	cmplwi r26, 0x0
	beq @41
	lfs f0, float_45_8041a7b4(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	li r26, 0x0
	fsubs f1, f25, f0
	bl sincosf
	li r21, 0x0
	b @42
	@43:
	lfs f1, 0x4(r30)
	fmr f26, f31
	lfs f0, 0x0(r28)
	lwz r3, 0x12c(r31)
	lwz r0, 0x134(r31)
	fadds f1, f1, f0
	stw r3, 0x24(r1)
	lfs f0, 0xc(r1)
	stfs f1, 0x8c(r1)
	lwz r7, 0x130(r31)
	stfs f0, 0x24(r1)
	lwz r6, 0x88(r1)
	lwz r5, 0x8c(r1)
	lwz r4, 0x90(r1)
	lwz r3, 0x24(r1)
	stw r0, 0x2c(r1)
	lfs f0, 0x8(r1)
	stw r7, 0x28(r1)
	stfs f0, 0x2c(r1)
	lwz r0, 0x2c(r1)
	stw r6, 0xa0(r1)
	stw r5, 0xa4(r1)
	stw r4, 0xa8(r1)
	stw r3, 0xac(r1)
	stw r7, 0xb0(r1)
	stw r0, 0xb4(r1)
	stfs f31, 0xd0(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @44
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x94
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @45
	@44:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @46
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x94
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @45
	@46:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x94
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@45:
	cmplwi r3, 0x0
	bne @47
	li r3, 0x0
	b @48
	@47:
	lfs f1, 0xd0(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @49
	lfs f0, float_0p5_8041a7c4(r2)
	b @50
	@49:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@50:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x188(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r31)
	fctiwz f0, f0
	stfd f0, 0x190(r1)
	lwz r0, 0x194(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x18c(r1)
	lfd f0, 0x188(r1)
	fsubs f0, f0, f1
	fdivs f26, f0, f2
	@48:
	mr r26, r3
	addi r28, r28, 0x4
	addi r21, r21, 0x1
	@42:
	cmpw r21, r29
	blt @43
	@41:
	cmplwi r27, 0x0
	beq @51
	cmplwi r26, 0x0
	bne @52
	stfs f26, 0x0(r20)
	lfs f0, 0x0(r30)
	fadds f0, f0, f29
	stfs f0, 0x0(r30)
	lfs f0, 0x8(r30)
	fadds f0, f0, f28
	stfs f0, 0x8(r30)
	b @53
	@52:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x0(r20)
	@53:
	mr r3, r27
	b @2
	@51:
	cmplwi r26, 0x0
	bne @54
	lfs f1, 0x14(r1)
	lfs f0, 0x0(r30)
	fmadds f0, f24, f1, f0
	stfs f0, 0x0(r30)
	lfs f1, 0x10(r1)
	lfs f0, 0x8(r30)
	fmadds f0, f24, f1, f0
	stfs f0, 0x8(r30)
	@54:
	li r3, 0x0
	@2:
	psq_l f31, 0x248(r1), 0, 0
	lfd f31, 0x240(r1)
	psq_l f30, 0x238(r1), 0, 0
	lfd f30, 0x230(r1)
	psq_l f29, 0x228(r1), 0, 0
	lfd f29, 0x220(r1)
	psq_l f28, 0x218(r1), 0, 0
	lfd f28, 0x210(r1)
	psq_l f27, 0x208(r1), 0, 0
	lfd f27, 0x200(r1)
	psq_l f26, 0x1f8(r1), 0, 0
	lfd f26, 0x1f0(r1)
	psq_l f25, 0x1e8(r1), 0, 0
	lfd f25, 0x1e0(r1)
	psq_l f24, 0x1d8(r1), 0, 0
	lfd f24, 0x1d0(r1)
	lmw r19, 0x19c(r1)
	lwz r0, 0x254(r1)
	mtlr r0
	addi r1, r1, 0x250
	blr
}

asm HitEntry* marioChkFront(f32* out, Vec* pos, f32 angle, f32 dist) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stfd f30, 0xd0(r1)
	psq_st f30, 0xd8(r1), 0, 0
	stw r31, 0xcc(r1)
	stw r30, 0xc8(r1)
	stw r29, 0xc4(r1)
	fmr f30, f2
	mr r30, r3
	mr r31, r4
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl sincosf
	lis r3, vec3_802c5838@ha
	lwz r6, 0x0(r31)
	addi r4, r3, vec3_802c5838@l
	lwz r5, 0x4(r31)
	lwz r3, 0x0(r4)
	fmr f31, f30
	lwz r0, 0x8(r4)
	stw r3, 0x10(r1)
	lfs f1, 0xc(r1)
	stw r0, 0x18(r1)
	lfs f0, 0x8(r1)
	lwz r7, 0x4(r4)
	stfs f1, 0x10(r1)
	lwz r4, 0x8(r31)
	stfs f0, 0x18(r1)
	lwz r3, 0x10(r1)
	lwz r0, 0x18(r1)
	stw r7, 0x14(r1)
	stw r6, 0x40(r1)
	stw r5, 0x44(r1)
	stw r4, 0x48(r1)
	stw r3, 0x4c(r1)
	stw r7, 0x50(r1)
	stw r0, 0x54(r1)
	stfs f30, 0x70(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @1
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x34
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @2
	@1:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @3
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x34
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @2
	@3:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x34
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@2:
	cmplwi r3, 0x0
	bne @4
	li r29, 0x0
	b @5
	@4:
	lfs f1, 0x70(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_0p5_8041a7c4(r2)
	b @7
	@6:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@7:
	lfs f2, float_1000_8041a7a0(r2)
	lis r5, 0x4330
	lis r4, double_to_int_802c5920@ha
	lwz r0, 0x58(r1)
	fmadds f0, f2, f1, f0
	addi r6, r4, double_to_int_802c5920@l
	stw r0, 0x28(r1)
	lwz r4, 0x5c(r1)
	fctiwz f0, f0
	lwz r0, 0x60(r1)
	stw r5, 0x80(r1)
	lfd f1, 0x0(r6)
	stfd f0, 0x78(r1)
	lfs f4, 0x28(r1)
	lwz r5, 0x7c(r1)
	lfs f0, float_0_8041a7a4(r2)
	xoris r5, r5, 0x8000
	stw r4, 0x2c(r1)
	fcmpo cr0, f4, f0
	stw r5, 0x84(r1)
	lfd f0, 0x80(r1)
	stw r0, 0x30(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041a7c4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@9:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x90(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x2c(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x28(r1)
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041a7c4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@11:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0xa0(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x30(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x2c(r1)
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041a7c4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@13:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0x1c
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x30(r1)
	beq @14
	lwz r5, 0x64(r1)
	lwz r4, 0x68(r1)
	lwz r0, 0x6c(r1)
	stw r5, 0x1c(r1)
	stw r4, 0x20(r1)
	stw r0, 0x24(r1)
	@14:
	mr r29, r3
	@5:
	cmplwi r29, 0x0
	beq @15
	fcmpo cr0, f31, f30
	cror eq, lt, eq
	bne @15
	lfs f1, 0x0(r31)
	lfs f2, 0x8(r31)
	lfs f3, 0x28(r1)
	lfs f4, 0x30(r1)
	bl distABf
	stfs f1, 0x0(r30)
	mr r3, r29
	b @16
	@15:
	lfs f0, float_neg1_8041a7dc(r2)
	li r3, 0x0
	stfs f0, 0x0(r30)
	@16:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	lwz r31, 0xcc(r1)
	lwz r30, 0xc8(r1)
	lwz r0, 0xf4(r1)
	lwz r29, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void marioCheckWall_roll(f32 dx, f32 dz) {
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
	stw r31, 0xbc(r1)
	stw r30, 0xb8(r1)
	stw r29, 0xb4(r1)
	fmr f29, f1
	fmr f30, f2
	bl marioGetPtr
	lfs f0, float_0_8041a7a4(r2)
	mr r31, r3
	lfs f1, float_1000_8041a7a0(r2)
	fcmpu cr0, f29, f0
	stfs f1, 0x210(r3)
	beq @1
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @1
	lfs f0, 0x1c8(r31)
	fcmpo cr0, f0, f29
	bge @2
	stfs f29, 0x1c8(r31)
	li r0, 0xe
	stfs f30, 0x1cc(r31)
	stw r0, 0x1d0(r31)
	b @3
	@2:
	lwz r3, 0x1d0(r31)
	subic. r0, r3, 0x1
	stw r0, 0x1d0(r31)
	bgt @3
	li r0, 0x0
	stw r0, 0x1d0(r31)
	stfs f29, 0x1c8(r31)
	stfs f30, 0x1cc(r31)
	b @3
	@1:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x1c8(r31)
	@3:
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f29, f0
	beq @4
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @4
	lfs f0, 0x1cc(r31)
	stfs f0, 0x19c(r31)
	@4:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 15, 15
	beq @5
	lwz r4, 0x8c(r31)
	lis r3, vec3_802c582c@ha
	lwz r0, 0x90(r31)
	addi r5, r3, vec3_802c582c@l
	lfs f31, float_30_8041a82c(r2)
	stw r4, 0x3c(r1)
	lwz r4, 0x0(r5)
	stw r0, 0x40(r1)
	lwz r3, 0x4(r5)
	lwz r6, 0x94(r31)
	lwz r0, 0x8(r5)
	stw r6, 0x44(r1)
	stw r4, 0x48(r1)
	stw r3, 0x4c(r1)
	stw r0, 0x50(r1)
	stfs f31, 0x6c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @6
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @7
	@6:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @8
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @7
	@8:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x30
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@7:
	cmplwi r3, 0x0
	bne @9
	li r3, 0x0
	b @10
	@9:
	lfs f1, 0x6c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @11
	lfs f0, float_0p5_8041a7c4(r2)
	b @12
	@11:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@12:
	lfs f2, float_1000_8041a7a0(r2)
	lis r5, 0x4330
	lis r4, double_to_int_802c5920@ha
	lwz r0, 0x54(r1)
	fmadds f0, f2, f1, f0
	addi r6, r4, double_to_int_802c5920@l
	stw r0, 0x18(r1)
	lwz r4, 0x58(r1)
	fctiwz f0, f0
	lwz r0, 0x5c(r1)
	stw r5, 0x78(r1)
	lfd f1, 0x0(r6)
	stfd f0, 0x70(r1)
	lfs f4, 0x18(r1)
	lwz r5, 0x74(r1)
	lfs f0, float_0_8041a7a4(r2)
	xoris r5, r5, 0x8000
	stw r4, 0x1c(r1)
	fcmpo cr0, f4, f0
	stw r5, 0x7c(r1)
	lfd f0, 0x78(r1)
	stw r0, 0x20(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	cror eq, gt, eq
	bne @13
	lfs f0, float_0p5_8041a7c4(r2)
	b @14
	@13:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@14:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x88(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x1c(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x18(r1)
	cror eq, gt, eq
	bne @15
	lfs f0, float_0p5_8041a7c4(r2)
	b @16
	@15:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@16:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x98(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x20(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x1c(r1)
	cror eq, gt, eq
	bne @17
	lfs f0, float_0p5_8041a7c4(r2)
	b @18
	@17:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@18:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa8(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0xc
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0xa0(r1)
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x20(r1)
	beq @10
	lwz r5, 0x60(r1)
	lwz r4, 0x64(r1)
	lwz r0, 0x68(r1)
	stw r5, 0xc(r1)
	stw r4, 0x10(r1)
	stw r0, 0x14(r1)
	@10:
	cmplwi r3, 0x0
	beq @19
	lfs f0, float_16p8_8041a830(r2)
	fcmpo cr0, f31, f0
	ble @19
	li r3, 0x0
	@19:
	cmplwi r3, 0x0
	stw r3, 0x1f4(r31)
	beq @5
	lfs f1, 0x1c(r1)
	lfs f0, 0x1b8(r31)
	fsubs f0, f1, f0
	stfs f0, 0x90(r31)
	@5:
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f29, f0
	bne @20
	fmr f1, f30
	bl marioSearchFrontWall_staying
	b @21
	@20:
	lwz r0, 0x1f4(r31)
	cmplwi r0, 0x0
	beq @22
	stfs f0, 0x180(r31)
	fmr f29, f0
	stfs f0, 0x7c(r31)
	stfs f0, 0x80(r31)
	stfs f0, 0x84(r31)
	stfs f0, 0x88(r31)
	@22:
	lwz r5, 0x8c(r31)
	fmr f1, f29
	lwz r0, 0x90(r31)
	fmr f2, f30
	addi r3, r1, 0x24
	addi r4, r1, 0x8
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x2c(r1)
	lfs f3, 0x1bc(r31)
	bl searchFrontWall
	mr. r30, r3
	beq @23
	stw r30, 0x1e0(r31)
	bl hitGetAttr
	mr r29, r3
	bl marioGetPtr
	rlwinm. r0, r29, 0, 12, 12
	beq @24
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @24
	li r0, 0x0
	b @25
	@24:
	rlwinm. r0, r29, 0, 24, 24
	bne @26
	extrwi r0, r29, 1, 8
	b @25
	@26:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@25:
	cmpwi r0, 0x0
	beq @27
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f29, f0
	beq @28
	stw r30, 0x1ec(r31)
	stw r30, 0x1f0(r31)
	@28:
	fmr f1, f29
	addi r3, r31, 0x8c
	fmr f2, f30
	addi r4, r31, 0x94
	bl movePos
	b @29
	@27:
	lfs f0, 0x8(r1)
	stfs f0, 0x210(r31)
	stw r30, 0x1f0(r31)
	lbz r3, 0x3f(r31)
	addi r3, r3, 0x1
	extsb r0, r3
	stb r3, 0x3f(r31)
	cmpwi r0, 0x14
	blt @30
	li r0, 0x14
	mr r3, r30
	stb r0, 0x3f(r31)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 24, 24
	bne @31
	li r0, 0x1
	b @32
	@31:
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@32:
	cmpwi r0, 0x0
	beq @30
	stw r30, 0x1ec(r31)
	@30:
	lwz r3, 0x24(r1)
	lwz r0, 0x28(r1)
	stw r3, 0x8c(r31)
	stw r0, 0x90(r31)
	lwz r0, 0x2c(r1)
	stw r0, 0x94(r31)
	b @29
	@23:
	lwz r3, 0x24(r1)
	lwz r0, 0x28(r1)
	stw r3, 0x8c(r31)
	stw r0, 0x90(r31)
	lwz r0, 0x2c(r1)
	stw r0, 0x94(r31)
	@29:
	lwz r5, 0x8c(r31)
	fmr f1, f29
	lwz r0, 0x90(r31)
	fmr f2, f30
	addi r3, r1, 0x24
	li r4, 0x0
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x2c(r1)
	lfs f3, 0x1bc(r31)
	lfs f4, 0x1b8(r31)
	bl marioChkWallAround
	lfs f0, 0x24(r1)
	stfs f0, 0x8c(r31)
	lfs f0, 0x2c(r1)
	stfs f0, 0x94(r31)
	@21:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	psq_l f29, 0xc8(r1), 0, 0
	lfd f29, 0xc0(r1)
	lwz r31, 0xbc(r1)
	lwz r30, 0xb8(r1)
	lwz r0, 0xf4(r1)
	lwz r29, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void marioSearchFrontWall_staying(f32 dz) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	fmr f31, f1
	bl marioGetPtr
	li r0, 0x0
	lfs f1, float_0p5_8041a7c4(r2)
	stb r0, 0x3f(r3)
	mr r31, r3
	lwz r0, 0x0(r3)
	lfs f0, 0x1b4(r3)
	rlwinm. r0, r0, 0, 11, 11
	fmuls f29, f1, f0
	beq @1
	lfs f29, float_0_8041a7a4(r2)
	@1:
	lwz r5, 0x8c(r31)
	fmr f1, f29
	lwz r0, 0x90(r31)
	addi r3, r1, 0x10
	addi r4, r1, 0xc
	stw r5, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f2, 0x1a0(r31)
	lfs f0, 0x198(r31)
	lfs f3, 0x1bc(r31)
	fsubs f2, f2, f0
	bl searchFrontWall
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x13
	beq @2
	stw r3, 0x1e0(r31)
	b @3
	@2:
	li r0, 0x0
	stw r0, 0x1e0(r31)
	@3:
	cmplwi r3, 0x0
	bne @4
	lfs f1, 0x1a8(r31)
	bl toMovedir
	lwz r5, 0x8c(r31)
	fmr f0, f1
	lwz r0, 0x90(r31)
	fmr f1, f29
	addi r3, r1, 0x10
	addi r4, r1, 0xc
	stw r5, 0x10(r1)
	fmr f2, f0
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f3, 0x1bc(r31)
	bl searchFrontWall
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x13
	beq @5
	stw r3, 0x1e0(r31)
	b @6
	@5:
	li r0, 0x0
	stw r0, 0x1e0(r31)
	b @6
	@4:
	lwz r5, gp(r13)
	lis r3, str_802C5940@ha
	addi r4, r3, str_802C5940@l
	addi r3, r5, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne @6
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @6
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq @6
	bl vivianGetStatus
	cmpwi r3, 0x3
	beq @6
	lfs f1, 0x1a8(r31)
	bl toMovedir
	lwz r5, 0x8c(r31)
	fmr f30, f1
	lwz r0, 0x90(r31)
	addi r3, r1, 0x10
	lfs f3, float_0p5_8041a7c4(r2)
	addi r4, r1, 0x18
	stw r5, 0x10(r1)
	fmr f2, f30
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f0, 0x1b4(r31)
	fmuls f1, f3, f0
	bl movePos
	lfs f0, float_180_8041a7cc(r2)
	addi r3, r1, 0x10
	lfs f1, 0x1b4(r31)
	addi r4, r1, 0x8
	fadds f30, f30, f0
	lfs f3, 0x1bc(r31)
	fmr f2, f30
	bl searchFrontWall
	cmplwi r3, 0x0
	beq @6
	lfs f1, 0x1b4(r31)
	lfs f0, 0x8(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	stw r3, 0x1e0(r31)
	lfs f1, float_0p5_8041a7c4(r2)
	lfs f0, 0x8(r1)
	fmuls f0, f1, f0
	stfs f0, 0xc(r1)
	@6:
	lwz r0, 0x1e0(r31)
	cmplwi r0, 0x0
	beq @7
	lfs f0, 0xc(r1)
	stfs f0, 0x210(r31)
	@7:
	lhz r0, 0x248(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @8
	li r0, 0x0
	fmr f1, f29
	stw r0, 0x1dc(r31)
	addi r3, r1, 0x10
	addi r4, r1, 0xc
	lwz r5, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r5, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f2, 0x1a0(r31)
	lfs f3, 0x1bc(r31)
	bl searchFrontWall
	cmplwi r3, 0x0
	beq @8
	lwz r0, 0x1e0(r31)
	stw r0, 0x1dc(r31)
	@8:
	lwz r5, 0x8c(r31)
	fmr f2, f31
	lwz r0, 0x90(r31)
	addi r3, r1, 0x10
	lfs f1, float_0_8041a7a4(r2)
	li r4, 0x0
	stw r5, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f3, 0x1bc(r31)
	lfs f4, 0x1b8(r31)
	bl marioChkWallAround
	lfs f0, 0x10(r1)
	stfs f0, 0x8c(r31)
	lfs f0, 0x18(r1)
	stfs f0, 0x94(r31)
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lwz r0, 0x64(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void marioCheckWall(f32 dx, f32 dz) {
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
	stw r29, 0x24(r1)
	fmr f30, f1
	fmr f31, f2
	bl marioGetPtr
	lfs f0, float_0_8041a7a4(r2)
	mr r31, r3
	lfs f1, float_1000_8041a7a0(r2)
	fcmpu cr0, f30, f0
	stfs f1, 0x210(r3)
	beq @1
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @1
	lfs f0, 0x1c8(r31)
	fcmpo cr0, f0, f30
	bge @2
	stfs f30, 0x1c8(r31)
	li r0, 0xe
	stfs f31, 0x1cc(r31)
	stw r0, 0x1d0(r31)
	b @3
	@2:
	lwz r3, 0x1d0(r31)
	subic. r0, r3, 0x1
	stw r0, 0x1d0(r31)
	bgt @3
	li r0, 0x0
	stw r0, 0x1d0(r31)
	stfs f30, 0x1c8(r31)
	stfs f31, 0x1cc(r31)
	@3:
	lfs f0, 0x1cc(r31)
	stfs f0, 0x19c(r31)
	b @4
	@1:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x1c8(r31)
	@4:
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f30, f0
	bne @5
	fmr f1, f31
	bl marioSearchFrontWall_staying
	addi r3, r31, 0x210
	bl dou10_yoko_yari
	b @6
	@5:
	lwz r4, 0x8c(r31)
	li r0, 0x0
	lwz r5, 0x90(r31)
	fmr f1, f30
	fmr f2, f31
	addi r3, r1, 0xc
	stw r4, 0xc(r1)
	addi r4, r1, 0x8
	stw r5, 0x10(r1)
	lwz r5, 0x94(r31)
	stw r5, 0x14(r1)
	stw r0, 0x20c(r31)
	lfs f3, 0x1bc(r31)
	bl searchFrontWall
	mr. r30, r3
	beq @7
	lwz r0, 0x20c(r31)
	cmplwi r0, 0x0
	beq @8
	stw r0, 0x1e0(r31)
	b @9
	@8:
	stw r30, 0x1e0(r31)
	@9:
	mr r3, r30
	bl hitGetAttr
	mr r29, r3
	bl marioGetPtr
	rlwinm. r0, r29, 0, 12, 12
	beq @10
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @10
	li r0, 0x0
	b @11
	@10:
	rlwinm. r0, r29, 0, 24, 24
	bne @12
	extrwi r0, r29, 1, 8
	b @11
	@12:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@11:
	cmpwi r0, 0x0
	beq @13
	lfs f0, float_0_8041a7a4(r2)
	fcmpu cr0, f30, f0
	beq @14
	stw r30, 0x1ec(r31)
	stw r30, 0x1f0(r31)
	@14:
	fmr f1, f30
	addi r3, r31, 0x8c
	fmr f2, f31
	addi r4, r31, 0x94
	bl movePos
	b @15
	@13:
	lfs f0, 0x8(r1)
	stfs f0, 0x210(r31)
	stw r30, 0x1f0(r31)
	lbz r3, 0x3f(r31)
	addi r3, r3, 0x1
	extsb r0, r3
	stb r3, 0x3f(r31)
	cmpwi r0, 0x14
	blt @16
	li r0, 0x14
	mr r3, r30
	stb r0, 0x3f(r31)
	bl hitGetAttr
	rlwinm. r0, r3, 0, 24, 24
	bne @17
	li r0, 0x1
	b @18
	@17:
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r0, r0, 5
	@18:
	cmpwi r0, 0x0
	beq @16
	stw r30, 0x1ec(r31)
	@16:
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r3, 0x8c(r31)
	stw r0, 0x90(r31)
	lwz r0, 0x14(r1)
	stw r0, 0x94(r31)
	b @15
	@7:
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r3, 0x8c(r31)
	stw r0, 0x90(r31)
	lwz r0, 0x14(r1)
	stw r0, 0x94(r31)
	@15:
	fmr f1, f30
	lfs f3, 0x1bc(r31)
	fmr f2, f31
	lfs f4, 0x1b8(r31)
	addi r3, r31, 0x8c
	li r4, 0x0
	bl marioChkWallAround
	addi r3, r31, 0x210
	bl dou10_yoko_yari
	@6:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r0, 0x54(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stfd f31, 0xc0(r1)
	psq_st f31, 0xc8(r1), 0, 0
	stfd f30, 0xb0(r1)
	psq_st f30, 0xb8(r1), 0, 0
	stfd f29, 0xa0(r1)
	psq_st f29, 0xa8(r1), 0, 0
	stfd f28, 0x90(r1)
	psq_st f28, 0x98(r1), 0, 0
	stfd f27, 0x80(r1)
	psq_st f27, 0x88(r1), 0, 0
	stfd f26, 0x70(r1)
	psq_st f26, 0x78(r1), 0, 0
	stfd f25, 0x60(r1)
	psq_st f25, 0x68(r1), 0, 0
	stmw r26, 0x48(r1)
	fmr f25, f1
	mr r26, r3
	mr r27, r4
	mr r28, r5
	bl marioGetPtr
	li r0, 0x0
	lis r4, vec3_802c5820@ha
	stw r0, 0x0(r28)
	addi r5, r4, vec3_802c5820@l
	lfs f0, float_neg1_8041a7dc(r2)
	mr r31, r3
	lfs f29, 0x0(r27)
	li r29, 0x0
	lfs f27, float_neg23p7_8041a834(r2)
	stfs f0, 0x0(r27)
	fadds f28, f29, f25
	lfs f30, float_3p1416_8041a7e0(r2)
	lwz r4, 0x0(r5)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r4, 0x24(r1)
	lfs f31, float_180_8041a7cc(r2)
	stw r3, 0x28(r1)
	lfs f25, float_0p5_8041a7c4(r2)
	stw r0, 0x2c(r1)
	lfs f26, float_5p8_8041a838(r2)
	@1:
	stfs f28, 0x8(r1)
	lfs f0, 0x198(r31)
	fmuls f0, f30, f0
	fdivs f1, f0, f31
	bl sin
	frsp f1, f1
	lfs f0, 0x0(r26)
	fmadds f0, f27, f1, f0
	stfs f0, 0x30(r1)
	lfs f0, 0x198(r31)
	fmuls f0, f30, f0
	fdivs f1, f0, f31
	bl cos
	frsp f1, f1
	lfs f0, 0x8(r26)
	addi r3, r1, 0x30
	addi r4, r1, 0x24
	addi r5, r1, 0x18
	addi r6, r1, 0xc
	fnmsubs f0, f27, f1, f0
	addi r7, r1, 0x8
	stfs f0, 0x38(r1)
	lfs f0, 0x4(r26)
	fadds f0, f25, f0
	stfs f0, 0x34(r1)
	bl marioHitCheck2
	mr. r30, r3
	beq @2
	bl hitGetAttr
	rlwinm. r0, r3, 0, 13, 13
	beq @3
	lfs f1, 0x4(r26)
	lfs f2, 0x1c(r1)
	fadds f0, f1, f29
	fcmpo cr0, f0, f2
	cror eq, gt, eq
	bne @4
	stfs f2, 0x4(r26)
	lfs f2, float_0_8041a7a4(r2)
	stfs f2, 0x0(r27)
	lfs f1, 0x38(r1)
	lfs f0, 0x8(r26)
	fsubs f0, f1, f0
	fcmpo cr0, f0, f2
	bge @5
	li r0, -0x1
	b @6
	@5:
	li r0, 0x1
	@6:
	stw r0, 0x0(r28)
	mr r3, r30
	b @7
	@4:
	fsubs f0, f2, f1
	fsubs f0, f0, f29
	stfs f0, 0x0(r27)
	b @2
	@3:
	cmpwi r29, 0x3
	bne @2
	lfs f1, 0x4(r26)
	lfs f2, 0x1c(r1)
	fadds f0, f1, f29
	fcmpo cr0, f0, f2
	cror eq, gt, eq
	bne @8
	stfs f2, 0x4(r26)
	li r0, 0x0
	lfs f0, float_0_8041a7a4(r2)
	mr r3, r30
	stfs f0, 0x0(r27)
	stw r0, 0x0(r28)
	b @7
	@8:
	fsubs f0, f2, f1
	fsubs f0, f0, f29
	stfs f0, 0x0(r27)
	@2:
	addi r29, r29, 0x1
	fadds f27, f27, f26
	cmpwi r29, 0x8
	blt @1
	li r3, 0x0
	@7:
	psq_l f31, 0xc8(r1), 0, 0
	lfd f31, 0xc0(r1)
	psq_l f30, 0xb8(r1), 0, 0
	lfd f30, 0xb0(r1)
	psq_l f29, 0xa8(r1), 0, 0
	lfd f29, 0xa0(r1)
	psq_l f28, 0x98(r1), 0, 0
	lfd f28, 0x90(r1)
	psq_l f27, 0x88(r1), 0, 0
	lfd f27, 0x80(r1)
	psq_l f26, 0x78(r1), 0, 0
	lfd f26, 0x70(r1)
	psq_l f25, 0x68(r1), 0, 0
	lfd f25, 0x60(r1)
	lmw r26, 0x48(r1)
	lwz r0, 0xd4(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stmw r26, 0xb8(r1)
	fmr f28, f1
	mr r26, r3
	mr r27, r4
	bl marioGetPtr
	lfs f0, float_neg1_8041a7dc(r2)
	lis r5, vec3_802c5808@ha
	lis r4, vec3_802c5814@ha
	mr r29, r3
	stfs f0, 0x0(r27)
	addi r30, r5, vec3_802c5808@l
	lfs f31, float_1_8041a7bc(r2)
	addi r31, r4, vec3_802c5814@l
	lfs f30, 0x1b8(r3)
	li r28, 0x0
	fadds f29, f30, f28
	@1:
	cmpwi r28, 0x2
	beq @2
	bge @3
	cmpwi r28, 0x0
	beq @4
	bge @5
	b @6
	@3:
	cmpwi r28, 0x4
	beq @7
	bge @6
	b @8
	@4:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0xc(r1)
	stfs f0, 0x8(r1)
	b @6
	@5:
	lfs f1, float_90_8041a81c(r2)
	lfs f0, 0x1a0(r29)
	lfs f2, float_3p1416_8041a7e0(r2)
	fadds f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, float_9_8041a83c(r2)
	fmr f1, f28
	fmuls f0, f0, f2
	stfs f0, 0xc(r1)
	bl cos
	frsp f0, f1
	lfs f2, float_9_8041a83c(r2)
	lfs f1, float_3_8041a7f0(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	fneg f0, f0
	fmuls f0, f2, f0
	stfs f0, 0x8(r1)
	lfs f2, 0x1a0(r29)
	bl movePos
	b @6
	@2:
	lfs f1, 0x1a0(r29)
	lfs f0, float_90_8041a81c(r2)
	lfs f2, float_3p1416_8041a7e0(r2)
	fsubs f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, float_9_8041a83c(r2)
	fmr f1, f28
	fmuls f0, f0, f2
	stfs f0, 0xc(r1)
	bl cos
	frsp f0, f1
	lfs f2, float_9_8041a83c(r2)
	lfs f1, float_3_8041a7f0(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	fneg f0, f0
	fmuls f0, f2, f0
	stfs f0, 0x8(r1)
	lfs f2, 0x1a0(r29)
	bl movePos
	b @6
	@8:
	lfs f1, float_90_8041a81c(r2)
	lfs f0, 0x1a0(r29)
	lfs f2, float_3p1416_8041a7e0(r2)
	fadds f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, float_9_8041a83c(r2)
	fmr f1, f28
	fmuls f0, f0, f2
	stfs f0, 0xc(r1)
	bl cos
	frsp f0, f1
	lfs f3, float_9_8041a83c(r2)
	lfs f2, float_180_8041a7cc(r2)
	addi r3, r1, 0xc
	lfs f1, float_3_8041a7f0(r2)
	addi r4, r1, 0x8
	fneg f0, f0
	fmuls f0, f3, f0
	stfs f0, 0x8(r1)
	lfs f0, 0x1a0(r29)
	fadds f2, f2, f0
	bl movePos
	b @6
	@7:
	lfs f1, 0x1a0(r29)
	lfs f0, float_90_8041a81c(r2)
	lfs f2, float_3p1416_8041a7e0(r2)
	fsubs f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f28, f1, f0
	fmr f1, f28
	bl sin
	frsp f2, f1
	lfs f0, float_9_8041a83c(r2)
	fmr f1, f28
	fmuls f0, f0, f2
	stfs f0, 0xc(r1)
	bl cos
	frsp f0, f1
	lfs f3, float_9_8041a83c(r2)
	lfs f2, float_180_8041a7cc(r2)
	addi r3, r1, 0xc
	lfs f1, float_3_8041a7f0(r2)
	addi r4, r1, 0x8
	fneg f0, f0
	fmuls f0, f3, f0
	stfs f0, 0x8(r1)
	lfs f0, 0x1a0(r29)
	fadds f2, f2, f0
	bl movePos
	@6:
	lfs f0, 0x4(r26)
	lwz r4, 0x0(r30)
	lwz r3, 0x4(r30)
	fadds f2, f31, f0
	lwz r0, 0x8(r30)
	stw r3, 0x20(r1)
	lfs f3, 0x0(r26)
	lfs f0, 0xc(r1)
	lfs f1, 0x8(r26)
	lwz r7, 0x0(r31)
	fadds f3, f3, f0
	lwz r6, 0x4(r31)
	lwz r5, 0x8(r31)
	lfs f0, 0x8(r1)
	stw r4, 0x1c(r1)
	fadds f0, f1, f0
	stw r0, 0x24(r1)
	stfs f3, 0x1c(r1)
	stfs f2, 0x20(r1)
	lwz r4, 0x1c(r1)
	stfs f0, 0x24(r1)
	lwz r3, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r7, 0x10(r1)
	stw r6, 0x14(r1)
	stw r5, 0x18(r1)
	stw r4, 0x4c(r1)
	stw r3, 0x50(r1)
	stw r0, 0x54(r1)
	stw r7, 0x58(r1)
	stw r6, 0x5c(r1)
	stw r5, 0x60(r1)
	stfs f29, 0x7c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @9
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x40
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @10
	@9:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @11
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x40
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @10
	@11:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x40
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@10:
	cmplwi r3, 0x0
	bne @12
	li r3, 0x0
	b @13
	@12:
	lwz r0, 0x64(r1)
	lwz r4, 0x68(r1)
	stw r0, 0x34(r1)
	lwz r0, 0x6c(r1)
	lfs f1, 0x34(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x38(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x3c(r1)
	cror eq, gt, eq
	bne @14
	lfs f0, float_0p5_8041a7c4(r2)
	b @15
	@14:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@15:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x88(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f3, f1, f0
	lfs f4, 0x38(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x34(r1)
	cror eq, gt, eq
	bne @16
	lfs f0, float_0p5_8041a7c4(r2)
	b @17
	@16:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@17:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x98(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x3c(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x38(r1)
	cror eq, gt, eq
	bne @18
	lfs f0, float_0p5_8041a7c4(r2)
	b @19
	@18:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@19:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa8(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0x28
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0xa0(r1)
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x3c(r1)
	beq @13
	lwz r5, 0x70(r1)
	lwz r4, 0x74(r1)
	lwz r0, 0x78(r1)
	stw r5, 0x28(r1)
	stw r4, 0x2c(r1)
	stw r0, 0x30(r1)
	@13:
	cmplwi r3, 0x0
	beq @20
	lfs f1, 0x4(r26)
	lfs f2, 0x38(r1)
	fadds f0, f1, f30
	fcmpo cr0, f0, f2
	cror eq, gt, eq
	bne @21
	fsubs f2, f2, f30
	lfs f1, float_1_8041a7bc(r2)
	lfs f0, float_0_8041a7a4(r2)
	fsubs f1, f2, f1
	stfs f1, 0x4(r26)
	stfs f0, 0x0(r27)
	b @22
	@21:
	fsubs f1, f2, f1
	lfs f2, 0x0(r27)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f2, f0
	fsubs f0, f1, f30
	bge @23
	stfs f0, 0x0(r27)
	b @20
	@23:
	fcmpo cr0, f2, f0
	ble @20
	stfs f0, 0x0(r27)
	@20:
	addi r28, r28, 0x1
	cmpwi r28, 0x5
	blt @1
	li r3, 0x0
	@22:
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	lmw r26, 0xb8(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm HitEntry* marioSearchHead(Vec* pos, f32* h, f32 dd) {
	nofralloc
	stwu r1, -0x160(r1)
	mflr r0
	stw r0, 0x164(r1)
	stfd f31, 0x150(r1)
	psq_st f31, 0x158(r1), 0, 0
	stfd f30, 0x140(r1)
	psq_st f30, 0x148(r1), 0, 0
	stfd f29, 0x130(r1)
	psq_st f29, 0x138(r1), 0, 0
	stfd f28, 0x120(r1)
	psq_st f28, 0x128(r1), 0, 0
	stfd f27, 0x110(r1)
	psq_st f27, 0x118(r1), 0, 0
	stfd f26, 0x100(r1)
	psq_st f26, 0x108(r1), 0, 0
	stfd f25, 0xf0(r1)
	psq_st f25, 0xf8(r1), 0, 0
	stfd f24, 0xe0(r1)
	psq_st f24, 0xe8(r1), 0, 0
	stfd f23, 0xd0(r1)
	psq_st f23, 0xd8(r1), 0, 0
	stfd f22, 0xc0(r1)
	psq_st f22, 0xc8(r1), 0, 0
	stfd f21, 0xb0(r1)
	psq_st f21, 0xb8(r1), 0, 0
	stfd f20, 0xa0(r1)
	psq_st f20, 0xa8(r1), 0, 0
	stfd f19, 0x90(r1)
	psq_st f19, 0x98(r1), 0, 0
	stmw r25, 0x74(r1)
	fmr f22, f1
	lis r5, vec3_802c5730@ha
	mr r26, r3
	mr r27, r4
	addi r30, r5, vec3_802c5730@l
	bl marioGetPtr
	mr r31, r3
	lfs f0, float_0_8041a7a4(r2)
	lfs f1, 0x180(r3)
	fcmpu cr0, f1, f0
	beq @1
	lfs f1, 0x1a0(r31)
	b @2
	@1:
	lfs f1, 0x1a8(r31)
	bl toMovedir
	@2:
	lfs f2, float_3p1416_8041a7e0(r2)
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f23, f1, f0
	fmr f1, f23
	bl sin
	lfs f2, float_0p5_8041a7c4(r2)
	frsp f3, f1
	lfs f0, 0x1b4(r31)
	fmr f1, f23
	fsubs f0, f0, f2
	fmuls f0, f0, f3
	fmuls f25, f2, f0
	bl cos
	frsp f1, f1
	lfs f23, 0x0(r27)
	lfs f3, float_0p5_8041a7c4(r2)
	fneg f27, f25
	lfs f0, 0x1b4(r31)
	fadds f22, f23, f22
	fsubs f2, f0, f3
	lfs f0, float_neg1_8041a7dc(r2)
	fneg f1, f1
	li r28, 0x0
	fmuls f26, f3, f23
	stfs f0, 0x0(r27)
	fmuls f0, f2, f1
	fmuls f24, f3, f0
	fneg f28, f24
	@3:
	cmpwi r28, 0x0
	bne @4
	lfs f21, float_0_8041a7a4(r2)
	fmr f20, f21
	b @5
	@4:
	cmpwi r28, 0x1
	bne @6
	fmr f21, f25
	fmr f20, f24
	b @5
	@6:
	cmpwi r28, 0x2
	bne @7
	fmr f21, f28
	fmr f20, f25
	b @5
	@7:
	cmpwi r28, 0x3
	bne @8
	fmr f21, f24
	fmr f20, f27
	b @5
	@8:
	cmpwi r28, 0x4
	bne @5
	fmr f21, f27
	fmr f20, f28
	@5:
	stfs f22, 0xc(r1)
	addi r3, r1, 0x40
	lwz r7, 0xc0(r30)
	addi r4, r1, 0x34
	lfs f2, 0x0(r26)
	addi r5, r1, 0x28
	lfs f1, 0x4(r26)
	addi r6, r1, 0x1c
	lfs f0, 0x8(r26)
	fadds f2, f2, f21
	lwz r8, 0xc4(r30)
	fadds f1, f1, f26
	lwz r0, 0xc8(r30)
	fadds f0, f0, f20
	stw r7, 0x10(r1)
	lwz r9, 0xcc(r30)
	addi r7, r1, 0xc
	stw r8, 0x14(r1)
	lwz r8, 0xd0(r30)
	stw r0, 0x18(r1)
	lwz r0, 0xd4(r30)
	stfs f2, 0x10(r1)
	stfs f1, 0x14(r1)
	lwz r12, 0x10(r1)
	stfs f0, 0x18(r1)
	lwz r11, 0x14(r1)
	lwz r10, 0x18(r1)
	stw r12, 0x40(r1)
	stw r11, 0x44(r1)
	stw r10, 0x48(r1)
	stw r9, 0x34(r1)
	stw r8, 0x38(r1)
	stw r0, 0x3c(r1)
	bl marioHitCheck2
	mr. r29, r3
	beq @9
	lfs f29, 0x24(r1)
	lfs f30, 0x20(r1)
	lfs f31, 0x1c(r1)
	bl marioGetPtr
	lfs f0, float_100_8041a7f8(r2)
	mr r25, r3
	lfs f1, float_0_8041a7a4(r2)
	fmuls f19, f0, f30
	fmr f2, f1
	fmuls f3, f0, f29
	fmr f4, f19
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f6, float_100_8041a7f8(r2)
	fmr f4, f19
	fsubs f2, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0x58(r1)
	fmuls f3, f6, f31
	lfd f5, 0x1f0(r30)
	fmadds f0, f6, f2, f0
	lfs f1, float_0_8041a7a4(r2)
	fctiwz f0, f0
	fmr f2, f1
	stfd f0, 0x50(r1)
	lwz r0, 0x54(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x5c(r1)
	lfd f0, 0x58(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f6
	stfs f0, 0x218(r25)
	stfs f1, 0x21c(r25)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	fmuls f2, f29, f29
	lfs f5, float_100_8041a7f8(r2)
	fsubs f3, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0x68(r1)
	lfd f1, 0x1f0(r30)
	fmadds f4, f5, f3, f0
	lfs f0, float_0_8041a7a4(r2)
	fmadds f3, f31, f31, f2
	fctiwz f2, f4
	fcmpo cr0, f3, f0
	stfd f2, 0x60(r1)
	lwz r0, 0x64(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x6c(r1)
	lfd f0, 0x68(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f5
	stfs f0, 0x220(r25)
	ble @10
	frsqrte f1, f3
	lfd f4, 0x1f8(r30)
	lfd f2, 0x200(r30)
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
	b @11
	@10:
	lfd f0, 0x208(r30)
	fcmpo cr0, f3, f0
	bge @12
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @11
	@12:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @13
	bge @14
	cmpwi r3, 0x0
	beq @15
	b @14
	@13:
	clrlwi. r0, r4, 9
	beq @16
	li r0, 0x1
	b @17
	@16:
	li r0, 0x2
	b @17
	@15:
	clrlwi. r0, r4, 9
	beq @18
	li r0, 0x5
	b @17
	@18:
	li r0, 0x3
	b @17
	@14:
	li r0, 0x4
	@17:
	cmpwi r0, 0x1
	bne @11
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@11:
	lfs f1, float_0_8041a7a4(r2)
	fneg f4, f30
	fmr f2, f1
	bl angleABf
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne @9
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq @19
	lfs f2, float_75_8041a840(r2)
	b @20
	@19:
	lfs f2, float_50_8041a844(r2)
	@20:
	lfs f0, float_180_8041a7cc(r2)
	fsubs f0, f0, f2
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @9
	fcmpo cr0, f1, f2
	cror eq, gt, eq
	bne @9
	li r29, 0x0
	@9:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq @21
	cmplwi r29, 0x0
	beq @22
	lfs f3, float_100_8041a7f8(r2)
	lis r0, 0x4330
	lfs f0, 0x2c(r1)
	stw r0, 0x60(r1)
	fmadds f1, f3, f0, f26
	lfd f2, 0x1f0(r30)
	lfs f0, float_0p05_8041a848(r2)
	fctiwz f1, f1
	stfd f1, 0x68(r1)
	lwz r0, 0x6c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	lfd f1, 0x60(r1)
	fsubs f1, f1, f2
	fdivs f2, f1, f3
	fnmsubs f1, f0, f23, f2
	stfs f2, 0x2c(r1)
	stfs f1, 0x2c(r1)
	lfs f2, 0x4(r26)
	fadds f0, f2, f23
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @23
	stfs f1, 0x4(r26)
	mr r3, r29
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x0(r27)
	b @24
	@23:
	fsubs f0, f1, f2
	li r3, 0x0
	fsubs f0, f0, f23
	stfs f0, 0x0(r27)
	b @24
	@21:
	cmplwi r29, 0x0
	beq @22
	lfs f2, float_100_8041a7f8(r2)
	lis r0, 0x4330
	lfs f0, 0x2c(r1)
	stw r0, 0x60(r1)
	fmadds f0, f2, f0, f26
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x68(r1)
	lwz r0, 0x6c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	lfd f0, 0x60(r1)
	fsubs f0, f0, f1
	fdivs f1, f0, f2
	stfs f1, 0x2c(r1)
	lfs f2, 0x4(r26)
	fadds f0, f2, f23
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @25
	stfs f1, 0x4(r26)
	mr r3, r29
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x0(r27)
	b @24
	@25:
	fsubs f0, f1, f2
	li r3, 0x0
	fsubs f0, f0, f23
	stfs f0, 0x0(r27)
	b @24
	@22:
	addi r28, r28, 0x1
	cmpwi r28, 0x5
	blt @3
	li r3, 0x0
	@24:
	psq_l f31, 0x158(r1), 0, 0
	lfd f31, 0x150(r1)
	psq_l f30, 0x148(r1), 0, 0
	lfd f30, 0x140(r1)
	psq_l f29, 0x138(r1), 0, 0
	lfd f29, 0x130(r1)
	psq_l f28, 0x128(r1), 0, 0
	lfd f28, 0x120(r1)
	psq_l f27, 0x118(r1), 0, 0
	lfd f27, 0x110(r1)
	psq_l f26, 0x108(r1), 0, 0
	lfd f26, 0x100(r1)
	psq_l f25, 0xf8(r1), 0, 0
	lfd f25, 0xf0(r1)
	psq_l f24, 0xe8(r1), 0, 0
	lfd f24, 0xe0(r1)
	psq_l f23, 0xd8(r1), 0, 0
	lfd f23, 0xd0(r1)
	psq_l f22, 0xc8(r1), 0, 0
	lfd f22, 0xc0(r1)
	psq_l f21, 0xb8(r1), 0, 0
	lfd f21, 0xb0(r1)
	psq_l f20, 0xa8(r1), 0, 0
	lfd f20, 0xa0(r1)
	psq_l f19, 0x98(r1), 0, 0
	lfd f19, 0x90(r1)
	lmw r25, 0x74(r1)
	lwz r0, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x160
	blr
}

asm f32 marioChkOverheadJabara(HitEntry** hitOut, f32* distOut) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	mr r30, r4
	stw r29, 0x24(r1)
	mr r29, r3
	bl marioGetPtr
	li r0, 0x0
	lfs f0, float_neg1_8041a7dc(r2)
	stw r0, 0x0(r29)
	mr r31, r3
	stfs f0, 0x0(r30)
	lwz r3, 0x8c(r3)
	lwz r0, 0x90(r31)
	stw r3, 0xc(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x14(r1)
	lfs f0, 0x1b8(r31)
	stfs f0, 0x8(r1)
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x8
	bne @1
	lfs f1, 0x10(r1)
	b @2
	@1:
	bl jabaraNoHitChk
	cmpwi r3, 0x0
	bne @3
	lfs f2, 0x8(r1)
	mr r5, r29
	lfs f0, float_5_8041a7b8(r2)
	addi r3, r1, 0xc
	lfs f1, float_0_8041a7a4(r2)
	addi r4, r1, 0x8
	fadds f0, f2, f0
	stfs f0, 0x8(r1)
	bl marioSearchHead_jabara
	stw r3, 0x1f4(r31)
	lwz r0, 0x1f4(r31)
	cmplwi r0, 0x0
	bne @3
	lfs f2, 0x1b8(r31)
	addi r3, r1, 0xc
	lfs f0, float_5_8041a7b8(r2)
	addi r4, r1, 0x8
	lfs f1, float_0_8041a7a4(r2)
	fadds f0, f2, f0
	stfs f0, 0x8(r1)
	bl marioSearchHead
	stw r3, 0x1f4(r31)
	@3:
	lfs f0, 0xc(r1)
	stfs f0, 0x8c(r31)
	lwz r0, 0x1f4(r31)
	cmplwi r0, 0x0
	beq @4
	lwz r0, 0x0(r31)
	lfs f0, float_0p1_8041a7e4(r2)
	oris r0, r0, 0x800
	stw r0, 0x0(r31)
	lfs f2, 0x10(r1)
	lfs f1, 0x1b8(r31)
	fsubs f1, f2, f1
	fsubs f0, f1, f0
	stfs f0, 0x10(r1)
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x3
	bne @5
	li r3, 0x0
	bl marioChgMot
	b @5
	@4:
	lfs f1, 0x8(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	ble @6
	stfs f1, 0x0(r30)
	lwz r0, 0x0(r31)
	oris r0, r0, 0x800
	stw r0, 0x0(r31)
	b @5
	@6:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 5, 3
	stw r0, 0x0(r31)
	@5:
	lfs f1, 0x10(r1)
	@2:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm f32 marioChkOverhead(void) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	lis r3, vec3_802c5730@ha
	addi r30, r3, vec3_802c5730@l
	bl marioGetPtr
	mr r31, r3
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x8
	bne @1
	lfs f1, 0x90(r31)
	b @2
	@1:
	cmplwi r0, 0x14
	bne @3
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f0, 0x1b8(r31)
	stfs f0, 0x8(r1)
	bl jabaraNoHitChk
	cmpwi r3, 0x0
	bne @4
	lfs f2, 0x8(r1)
	addi r3, r1, 0x10
	lfs f0, float_5_8041a7b8(r2)
	addi r4, r1, 0x8
	lfs f1, float_0_8041a7a4(r2)
	addi r5, r1, 0xc
	fadds f0, f2, f0
	stfs f0, 0x8(r1)
	bl marioSearchHead_jabara
	stw r3, 0x1f4(r31)
	lwz r0, 0x1f4(r31)
	cmplwi r0, 0x0
	bne @4
	lwz r0, 0x0(r31)
	addi r3, r1, 0x10
	addi r4, r1, 0x8
	rlwinm. r0, r0, 0, 15, 15
	beq @5
	lfs f1, 0x7c(r31)
	b @6
	@5:
	lfs f1, float_10_8041a7fc(r2)
	@6:
	bl marioSearchHead
	stw r3, 0x1f4(r31)
	b @4
	@3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq @7
	lwz r5, 0x8c(r31)
	addi r3, r1, 0x10
	lwz r0, 0x90(r31)
	addi r4, r1, 0x8
	lfs f1, float_40_8041a800(r2)
	stw r5, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	bl marioSearchHead_roll
	stw r3, 0x1f4(r31)
	b @4
	@7:
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x18(r1)
	lfs f0, 0x1b8(r31)
	stfs f0, 0x8(r1)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 15, 15
	beq @8
	lfs f1, 0x7c(r31)
	b @9
	@8:
	lfs f1, float_10_8041a7fc(r2)
	@9:
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @10
	addi r3, r1, 0x10
	addi r4, r1, 0x8
	bl kpaSearchHead
	stw r3, 0x1f4(r31)
	b @4
	@10:
	addi r3, r1, 0x10
	addi r4, r1, 0x8
	bl marioSearchHead
	stw r3, 0x1f4(r31)
	@4:
	lfs f0, 0x10(r1)
	stfs f0, 0x8c(r31)
	lwz r29, 0x1f4(r31)
	cmplwi r29, 0x0
	beq @11
	bne @12
	li r0, 0x0
	b @13
	@12:
	mr r3, r29
	bl hitGetAttr
	clrrwi. r0, r3, 31
	bne @14
	li r0, 0x0
	b @13
	@14:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	mr r29, r3
	addi r4, r30, 0x220
	addi r3, r29, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	addi r3, r29, 0x15
	addi r4, r30, 0x234
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	addi r3, r29, 0x15
	addi r4, r30, 0x244
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	addi r3, r29, 0x15
	addi r4, r30, 0x258
	bl strcmp
	cmpwi r3, 0x0
	bne @16
	@15:
	li r0, 0x1
	b @13
	@16:
	li r0, 0x0
	@13:
	cmpwi r0, 0x0
	beq @17
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x180(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x80
	stw r0, 0x0(r31)
	@17:
	lwz r0, 0x0(r31)
	oris r0, r0, 0x800
	stw r0, 0x0(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @18
	bl marioItemGetDisable
	bl kpaGetBodyStatus
	cmpwi r3, 0x0
	bne @18
	bl marioClearJumpPara
	@18:
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	lfs f31, 0x1b8(r3)
	cmplwi r0, 0x1a
	bne @19
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @19
	bl partyGetHeight
	fmr f31, f1
	@19:
	lfs f0, 0x14(r1)
	lis r0, 0x4330
	lfs f3, float_10_8041a7fc(r2)
	fsubs f1, f0, f31
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0x28(r1)
	lfd f2, 0x1f0(r30)
	fmadds f1, f3, f1, f0
	lfs f0, float_1_8041a7bc(r2)
	fctiwz f1, f1
	stfd f1, 0x20(r1)
	lwz r0, 0x24(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x2c(r1)
	lfd f1, 0x28(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	fsubs f0, f1, f0
	stfs f0, 0x14(r1)
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 14, 14
	bne @20
	lfs f1, 0x120(r31)
	fcmpo cr0, f0, f1
	bge @20
	rlwinm. r0, r3, 0, 7, 7
	stfs f1, 0x14(r1)
	bne @20
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x19
	beq @20
	cmplwi r0, 0x18
	beq @20
	cmplwi r0, 0x1c
	beq @20
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	beq @20
	bl marioChkSlitEnd
	cmpwi r3, 0x0
	bne @20
	lfs f0, float_0_8041a7a4(r2)
	lfs f1, 0x180(r31)
	fcmpu cr0, f0, f1
	bne @21
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x0
	beq @20
	bl marioChgStayMotion
	b @20
	@21:
	lfs f0, 0x184(r31)
	fcmpo cr0, f1, f0
	ble @22
	li r3, 0x2
	b @23
	@22:
	li r3, 0x1
	@23:
	bl marioChgMot
	@20:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x3
	beq @24
	cmplwi r0, 0x6
	bne @25
	@24:
	addi r4, r31, 0x8c
	li r3, 0x156
	bl psndSFXOn_3D
	bl marioClearJumpPara
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 11
	stw r0, 0x0(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	beq @26
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
	@26:
	lfs f0, 0x14(r1)
	stfs f0, 0x90(r31)
	b @25
	@11:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 7, 7
	bne @27
	lfs f1, 0x8(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @28
	lfs f0, float_5_8041a7b8(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @28
	oris r0, r3, 0x800
	stw r0, 0x0(r31)
	b @25
	@28:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 5, 3
	stw r0, 0x0(r31)
	b @25
	@27:
	lfs f2, 0x8(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @29
	lfs f1, 0x1b8(r31)
	lfs f0, float_47_8041a84c(r2)
	fadds f1, f2, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @29
	oris r0, r3, 0x800
	stw r0, 0x0(r31)
	b @25
	@29:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 5, 3
	stw r0, 0x0(r31)
	@25:
	lfs f1, 0x14(r1)
	@2:
	psq_l f31, 0x48(r1), 0, 0
	lwz r0, 0x54(r1)
	lfd f31, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm HitEntry* marioChkLandon2(f32* y, f32 spd, f32 ofs) {
	nofralloc
	stwu r1, -0x1a0(r1)
	mflr r0
	stw r0, 0x1a4(r1)
	stfd f31, 0x190(r1)
	psq_st f31, 0x198(r1), 0, 0
	stfd f30, 0x180(r1)
	psq_st f30, 0x188(r1), 0, 0
	stfd f29, 0x170(r1)
	psq_st f29, 0x178(r1), 0, 0
	stfd f28, 0x160(r1)
	psq_st f28, 0x168(r1), 0, 0
	stfd f27, 0x150(r1)
	psq_st f27, 0x158(r1), 0, 0
	stfd f26, 0x140(r1)
	psq_st f26, 0x148(r1), 0, 0
	stfd f25, 0x130(r1)
	psq_st f25, 0x138(r1), 0, 0
	stfd f24, 0x120(r1)
	psq_st f24, 0x128(r1), 0, 0
	stfd f23, 0x110(r1)
	psq_st f23, 0x118(r1), 0, 0
	stfd f22, 0x100(r1)
	psq_st f22, 0x108(r1), 0, 0
	stfd f21, 0xf0(r1)
	psq_st f21, 0xf8(r1), 0, 0
	stmw r23, 0xcc(r1)
	fmr f24, f1
	lis r4, vec3_802c5730@ha
	fmr f23, f2
	mr r24, r3
	addi r27, r4, vec3_802c5730@l
	bl marioGetPtr
	lfs f5, float_0_8041a7a4(r2)
	mr r28, r3
	stfs f5, 0x218(r3)
	stfs f5, 0x21c(r3)
	stfs f5, 0x220(r3)
	stfs f5, 0x214(r3)
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 22, 22
	beq @1
	lfs f0, 0x90(r28)
	li r3, 0x0
	stfs f0, 0x0(r24)
	b @2
	@1:
	rlwinm. r0, r3, 0, 23, 23
	beq @3
	lfs f0, 0x90(r28)
	li r3, 0x0
	stfs f0, 0x0(r24)
	b @2
	@3:
	fabs f3, f24
	lfs f4, float_0p1_8041a7e4(r2)
	lfs f0, 0x180(r28)
	lfs f2, float_0p5_8041a7c4(r2)
	lfs f1, 0x1b8(r28)
	fcmpu cr0, f0, f5
	fadds f29, f4, f3
	fmuls f28, f2, f1
	beq @4
	lfs f1, 0x1a0(r28)
	b @5
	@4:
	lfs f1, 0x1a8(r28)
	bl toMovedir
	@5:
	lfs f2, float_3p1416_8041a7e0(r2)
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f24, f1, f0
	fmr f1, f24
	bl sin
	frsp f3, f1
	lfs f0, 0x1b4(r28)
	lfs f2, float_0p25_8041a7d4(r2)
	fmr f1, f24
	fmuls f0, f0, f3
	fmuls f27, f2, f0
	bl cos
	frsp f1, f1
	lfs f0, 0x90(r28)
	lwz r29, 0x78(r27)
	fneg f30, f27
	fadds f0, f0, f23
	lwz r30, 0x7c(r27)
	fneg f1, f1
	lfs f2, 0x1b4(r28)
	lwz r31, 0x80(r27)
	fadds f29, f28, f29
	lfs f3, float_0p25_8041a7d4(r2)
	fadds f28, f0, f28
	fmuls f0, f2, f1
	stw r29, 0x30(r1)
	lfs f25, 0x8c(r28)
	li r25, 0x0
	stw r30, 0x34(r1)
	fmuls f26, f3, f0
	stw r31, 0x38(r1)
	lfs f24, 0x94(r28)
	fneg f31, f26
	@6:
	cmpwi r25, 0x0
	bne @7
	lfs f22, float_0_8041a7a4(r2)
	fmr f21, f22
	b @8
	@7:
	cmpwi r25, 0x1
	bne @9
	fmr f22, f27
	fmr f21, f26
	b @8
	@9:
	cmpwi r25, 0x2
	bne @10
	fmr f22, f31
	fmr f21, f26
	b @8
	@10:
	cmpwi r25, 0x3
	bne @11
	fmr f22, f26
	fmr f21, f30
	b @8
	@11:
	cmpwi r25, 0x4
	bne @8
	fmr f22, f30
	fmr f21, f31
	@8:
	lwz r4, 0x84(r27)
	fadds f1, f25, f22
	lwz r3, 0x88(r27)
	fadds f0, f24, f21
	lwz r0, 0x8c(r27)
	fmr f23, f29
	stw r4, 0xc(r1)
	stw r3, 0x10(r1)
	stw r0, 0x14(r1)
	stfs f1, 0xc(r1)
	stfs f28, 0x10(r1)
	lwz r4, 0xc(r1)
	stfs f0, 0x14(r1)
	lwz r3, 0x10(r1)
	lwz r0, 0x14(r1)
	stw r4, 0x48(r1)
	stw r3, 0x4c(r1)
	stw r0, 0x50(r1)
	stw r29, 0x54(r1)
	stw r30, 0x58(r1)
	stw r31, 0x5c(r1)
	stfs f29, 0x78(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @12
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @13
	@12:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @14
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @13
	@14:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@13:
	cmplwi r3, 0x0
	bne @15
	li r26, 0x0
	b @16
	@15:
	lfs f1, 0x78(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @17
	lfs f0, float_0p5_8041a7c4(r2)
	b @18
	@17:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@18:
	lfs f2, float_1000_8041a7a0(r2)
	lis r5, 0x4330
	lwz r0, 0x60(r1)
	fmadds f0, f2, f1, f0
	lwz r4, 0x64(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x68(r1)
	fctiwz f0, f0
	stw r5, 0x88(r1)
	lfd f1, 0x1f0(r27)
	lfs f4, 0x24(r1)
	stfd f0, 0x80(r1)
	lfs f0, float_0_8041a7a4(r2)
	lwz r5, 0x84(r1)
	fcmpo cr0, f4, f0
	stw r4, 0x28(r1)
	xoris r4, r5, 0x8000
	stw r4, 0x8c(r1)
	lfd f0, 0x88(r1)
	stw r0, 0x2c(r1)
	fsubs f0, f0, f1
	fdivs f23, f0, f2
	cror eq, gt, eq
	bne @19
	lfs f0, float_0p5_8041a7c4(r2)
	b @20
	@19:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@20:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x98(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r27)
	lfs f4, 0x28(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x24(r1)
	cror eq, gt, eq
	bne @21
	lfs f0, float_0p5_8041a7c4(r2)
	b @22
	@21:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@22:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa8(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r27)
	lfs f4, 0x2c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0xa0(r1)
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x28(r1)
	cror eq, gt, eq
	bne @23
	lfs f0, float_0p5_8041a7c4(r2)
	b @24
	@23:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@24:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xb8(r1)
	addic. r0, r1, 0x18
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r27)
	fctiwz f0, f0
	stfd f0, 0xb0(r1)
	lwz r0, 0xb4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x2c(r1)
	beq @25
	lwz r5, 0x6c(r1)
	lwz r4, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	@25:
	mr r26, r3
	@16:
	cmplwi r26, 0x0
	beq @26
	bl marioGetPtr
	lfs f1, float_0_8041a7a4(r2)
	mr r23, r3
	lfs f4, float_100_8041a7f8(r2)
	lfs f3, 0x20(r1)
	fmr f2, f1
	lfs f0, 0x1c(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f7, float_100_8041a7f8(r2)
	fsubs f4, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	lfs f2, float_0_8041a7a4(r2)
	lfs f3, 0x18(r1)
	fmadds f6, f7, f4, f0
	lfs f0, 0x1c(r1)
	stw r0, 0xb0(r1)
	fmr f1, f2
	fmuls f4, f7, f0
	lfd f5, 0x1f0(r27)
	fctiwz f0, f6
	fmuls f3, f7, f3
	stfd f0, 0xb8(r1)
	lwz r0, 0xbc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f7
	stfs f0, 0x218(r23)
	stfs f2, 0x21c(r23)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f2, 0x18(r1)
	fsubs f3, f1, f0
	lfs f0, 0x20(r1)
	lfs f5, float_100_8041a7f8(r2)
	fmuls f1, f2, f2
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f0, f0
	fmadds f4, f5, f3, f2
	stw r0, 0xa0(r1)
	lfd f2, 0x1f0(r27)
	fadds f3, f1, f0
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f2
	fdivs f0, f0, f5
	stfs f0, 0x220(r23)
	ble @27
	frsqrte f1, f3
	lfd f4, 0x1f8(r27)
	lfd f2, 0x200(r27)
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
	b @28
	@27:
	lfd f0, 0x208(r27)
	fcmpo cr0, f3, f0
	bge @29
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @28
	@29:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @30
	bge @31
	cmpwi r3, 0x0
	beq @32
	b @31
	@30:
	clrlwi. r0, r4, 9
	beq @33
	li r0, 0x1
	b @34
	@33:
	li r0, 0x2
	b @34
	@32:
	clrlwi. r0, r4, 9
	beq @35
	li r0, 0x5
	b @34
	@35:
	li r0, 0x3
	b @34
	@31:
	li r0, 0x4
	@34:
	cmpwi r0, 0x1
	bne @28
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@28:
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x1c(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f5, 0x28(r1)
	lis r0, 0x4330
	lfs f6, float_100_8041a7f8(r2)
	fsubs f0, f28, f5
	lfs f3, float_0p5_8041a7c4(r2)
	stw r0, 0xb0(r1)
	lfd f2, 0x1f0(r27)
	fsubs f4, f0, f23
	lfs f0, float_0p1_8041a7e4(r2)
	stfs f1, 0x214(r28)
	fmadds f1, f6, f4, f3
	fctiwz f1, f1
	stfd f1, 0xb8(r1)
	lwz r0, 0xbc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f6
	fabs f1, f1
	fcmpo cr0, f1, f0
	bge @26
	stfs f5, 0x0(r24)
	mr r3, r26
	b @2
	@26:
	addi r25, r25, 0x1
	cmpwi r25, 0x5
	blt @6
	li r3, 0x0
	@2:
	psq_l f31, 0x198(r1), 0, 0
	lfd f31, 0x190(r1)
	psq_l f30, 0x188(r1), 0, 0
	lfd f30, 0x180(r1)
	psq_l f29, 0x178(r1), 0, 0
	lfd f29, 0x170(r1)
	psq_l f28, 0x168(r1), 0, 0
	lfd f28, 0x160(r1)
	psq_l f27, 0x158(r1), 0, 0
	lfd f27, 0x150(r1)
	psq_l f26, 0x148(r1), 0, 0
	lfd f26, 0x140(r1)
	psq_l f25, 0x138(r1), 0, 0
	lfd f25, 0x130(r1)
	psq_l f24, 0x128(r1), 0, 0
	lfd f24, 0x120(r1)
	psq_l f23, 0x118(r1), 0, 0
	lfd f23, 0x110(r1)
	psq_l f22, 0x108(r1), 0, 0
	lfd f22, 0x100(r1)
	psq_l f21, 0xf8(r1), 0, 0
	lfd f21, 0xf0(r1)
	lmw r23, 0xcc(r1)
	lwz r0, 0x1a4(r1)
	mtlr r0
	addi r1, r1, 0x1a0
	blr
}

asm HitEntry* marioLandonChk_old(f32* outY, f32 spd) {
	nofralloc
	stwu r1, -0x200(r1)
	mflr r0
	stw r0, 0x204(r1)
	stfd f31, 0x1f0(r1)
	psq_st f31, 0x1f8(r1), 0, 0
	stfd f30, 0x1e0(r1)
	psq_st f30, 0x1e8(r1), 0, 0
	stfd f29, 0x1d0(r1)
	psq_st f29, 0x1d8(r1), 0, 0
	stfd f28, 0x1c0(r1)
	psq_st f28, 0x1c8(r1), 0, 0
	stfd f27, 0x1b0(r1)
	psq_st f27, 0x1b8(r1), 0, 0
	stfd f26, 0x1a0(r1)
	psq_st f26, 0x1a8(r1), 0, 0
	stfd f25, 0x190(r1)
	psq_st f25, 0x198(r1), 0, 0
	stfd f24, 0x180(r1)
	psq_st f24, 0x188(r1), 0, 0
	stfd f23, 0x170(r1)
	psq_st f23, 0x178(r1), 0, 0
	stfd f22, 0x160(r1)
	psq_st f22, 0x168(r1), 0, 0
	stfd f21, 0x150(r1)
	psq_st f21, 0x158(r1), 0, 0
	stfd f20, 0x140(r1)
	psq_st f20, 0x148(r1), 0, 0
	stfd f19, 0x130(r1)
	psq_st f19, 0x138(r1), 0, 0
	stfd f18, 0x120(r1)
	psq_st f18, 0x128(r1), 0, 0
	stfd f17, 0x110(r1)
	psq_st f17, 0x118(r1), 0, 0
	stfd f16, 0x100(r1)
	psq_st f16, 0x108(r1), 0, 0
	stfd f15, 0xf0(r1)
	psq_st f15, 0xf8(r1), 0, 0
	stfd f14, 0xe0(r1)
	psq_st f14, 0xe8(r1), 0, 0
	stmw r26, 0xc8(r1)
	fmr f14, f1
	lis r4, vec3_802c5730@ha
	mr r27, r3
	addi r30, r4, vec3_802c5730@l
	bl marioGetPtr
	lfs f5, float_0_8041a7a4(r2)
	mr r31, r3
	stfs f5, 0x218(r3)
	stfs f5, 0x21c(r3)
	stfs f5, 0x220(r3)
	stfs f5, 0x214(r3)
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 22, 22
	beq @1
	lfs f0, 0x90(r31)
	li r3, 0x0
	stfs f0, 0x0(r27)
	b @2
	@1:
	rlwinm. r0, r3, 0, 23, 23
	beq @3
	lfs f0, 0x90(r31)
	li r3, 0x0
	stfs f0, 0x0(r27)
	b @2
	@3:
	fabs f3, f14
	lfs f4, float_0p01_8041a854(r2)
	lfs f0, 0x180(r31)
	lfs f2, float_0p75_8041a7d8(r2)
	lfs f1, 0x1b8(r31)
	fcmpu cr0, f0, f5
	fadds f15, f4, f3
	fmuls f14, f2, f1
	beq @4
	lfs f1, 0x1a0(r31)
	lfs f0, 0x198(r31)
	fsubs f1, f1, f0
	bl revise360
	b @5
	@4:
	lfs f1, 0x1a8(r31)
	bl toMovedir
	@5:
	lfs f2, float_3p1416_8041a7e0(r2)
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f16, f1, f0
	fmr f1, f16
	bl sin
	frsp f3, f1
	lfs f0, 0x1b4(r31)
	lfs f2, float_0p25_8041a7d4(r2)
	fmr f1, f16
	fmuls f0, f0, f3
	fmuls f20, f2, f0
	bl cos
	frsp f0, f1
	lbz r0, 0x3c(r31)
	lfs f1, 0x1b4(r31)
	lfs f2, float_0p25_8041a7d4(r2)
	cmpwi r0, 0x2
	fneg f0, f0
	lfs f21, 0x8c(r31)
	lfs f3, 0x90(r31)
	fmuls f0, f1, f0
	lfs f18, 0x94(r31)
	fmuls f19, f2, f0
	bne @6
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	bl kpaSearchGround
	lfs f0, 0x14(r1)
	stfs f0, 0x0(r27)
	b @2
	@6:
	fneg f25, f19
	lfs f27, float_0_8041a7a4(r2)
	fneg f24, f20
	lfs f28, float_neg1_8041a7dc(r2)
	fadds f23, f14, f15
	li r28, 0x0
	fadds f22, f3, f14
	@7:
	cmpwi r28, 0x0
	bne @8
	lfs f30, float_0_8041a7a4(r2)
	fmr f29, f30
	b @9
	@8:
	cmpwi r28, 0x1
	bne @10
	fmr f30, f20
	fmr f29, f19
	b @9
	@10:
	cmpwi r28, 0x2
	bne @11
	fmr f30, f25
	fmr f29, f19
	b @9
	@11:
	cmpwi r28, 0x3
	bne @12
	fmr f30, f19
	fmr f29, f24
	b @9
	@12:
	cmpwi r28, 0x4
	bne @9
	fmr f30, f24
	fmr f29, f25
	@9:
	lwz r7, 0x0(r30)
	fadds f1, f21, f30
	lwz r6, 0x4(r30)
	fadds f0, f18, f29
	lwz r5, 0x8(r30)
	fmr f26, f23
	lwz r4, 0xc(r30)
	lwz r3, 0x10(r30)
	lwz r0, 0x14(r30)
	stw r7, 0x30(r1)
	stw r6, 0x34(r1)
	stw r5, 0x38(r1)
	stw r4, 0x3c(r1)
	stw r3, 0x40(r1)
	stw r0, 0x44(r1)
	stfs f1, 0x30(r1)
	stfs f22, 0x34(r1)
	lwz r7, 0x30(r1)
	stfs f0, 0x38(r1)
	lwz r6, 0x34(r1)
	stfs f27, 0x3c(r1)
	lwz r5, 0x38(r1)
	stfs f28, 0x40(r1)
	lwz r4, 0x3c(r1)
	stfs f27, 0x44(r1)
	lwz r3, 0x40(r1)
	lwz r0, 0x44(r1)
	stw r7, 0x54(r1)
	stw r6, 0x58(r1)
	stw r5, 0x5c(r1)
	stw r4, 0x60(r1)
	stw r3, 0x64(r1)
	stw r0, 0x68(r1)
	stfs f23, 0x84(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @13
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x48
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @14
	@13:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @15
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x48
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @14
	@15:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x48
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@14:
	cmplwi r3, 0x0
	bne @16
	li r29, 0x0
	b @17
	@16:
	lfs f1, 0x84(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @18
	lfs f0, float_0p5_8041a7c4(r2)
	b @19
	@18:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@19:
	lfs f2, float_1000_8041a7a0(r2)
	lis r5, 0x4330
	lwz r0, 0x6c(r1)
	fmadds f0, f2, f1, f0
	lwz r4, 0x70(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x74(r1)
	fctiwz f0, f0
	stw r5, 0x90(r1)
	lfd f1, 0x1f0(r30)
	lfs f4, 0x18(r1)
	stfd f0, 0x88(r1)
	lfs f0, float_0_8041a7a4(r2)
	lwz r5, 0x8c(r1)
	fcmpo cr0, f4, f0
	stw r4, 0x1c(r1)
	xoris r4, r5, 0x8000
	stw r4, 0x94(r1)
	lfd f0, 0x90(r1)
	stw r0, 0x20(r1)
	fsubs f0, f0, f1
	fdivs f26, f0, f2
	cror eq, gt, eq
	bne @20
	lfs f0, float_0p5_8041a7c4(r2)
	b @21
	@20:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@21:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa0(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x1c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x18(r1)
	cror eq, gt, eq
	bne @22
	lfs f0, float_0p5_8041a7c4(r2)
	b @23
	@22:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@23:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x20(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x1c(r1)
	cror eq, gt, eq
	bne @24
	lfs f0, float_0p5_8041a7c4(r2)
	b @25
	@24:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@25:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xc0(r1)
	addic. r0, r1, 0x24
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0xb8(r1)
	lwz r0, 0xbc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xc4(r1)
	lfd f0, 0xc0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x20(r1)
	beq @26
	lwz r5, 0x78(r1)
	lwz r4, 0x7c(r1)
	lwz r0, 0x80(r1)
	stw r5, 0x24(r1)
	stw r4, 0x28(r1)
	stw r0, 0x2c(r1)
	@26:
	mr r29, r3
	@17:
	cmplwi r29, 0x0
	lfs f17, 0x1c(r1)
	lfs f16, 0x24(r1)
	lfs f31, 0x28(r1)
	lfs f15, 0x2c(r1)
	beq @27
	bl marioGetPtr
	lfs f0, float_100_8041a7f8(r2)
	mr r26, r3
	lfs f1, float_0_8041a7a4(r2)
	fmuls f14, f0, f31
	fmr f2, f1
	fmuls f3, f0, f15
	fmr f4, f14
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f6, float_100_8041a7f8(r2)
	fmr f4, f14
	fsubs f2, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0xb8(r1)
	fmuls f3, f6, f16
	lfd f5, 0x1f0(r30)
	fmadds f0, f6, f2, f0
	lfs f1, float_0_8041a7a4(r2)
	fctiwz f0, f0
	fmr f2, f1
	stfd f0, 0xc0(r1)
	lwz r0, 0xc4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f6
	stfs f0, 0x218(r26)
	stfs f1, 0x21c(r26)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	fmuls f2, f15, f15
	lfs f5, float_100_8041a7f8(r2)
	fsubs f3, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0xa8(r1)
	lfd f1, 0x1f0(r30)
	fmadds f4, f5, f3, f0
	lfs f0, float_0_8041a7a4(r2)
	fmadds f3, f16, f16, f2
	fctiwz f2, f4
	fcmpo cr0, f3, f0
	stfd f2, 0xb0(r1)
	lwz r0, 0xb4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f5
	stfs f0, 0x220(r26)
	ble @28
	frsqrte f1, f3
	lfd f4, 0x1f8(r30)
	lfd f2, 0x200(r30)
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
	b @29
	@28:
	lfd f0, 0x208(r30)
	fcmpo cr0, f3, f0
	bge @30
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @29
	@30:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @31
	bge @32
	cmpwi r3, 0x0
	beq @33
	b @32
	@31:
	clrlwi. r0, r4, 9
	beq @34
	li r0, 0x1
	b @35
	@34:
	li r0, 0x2
	b @35
	@33:
	clrlwi. r0, r4, 9
	beq @36
	li r0, 0x5
	b @35
	@36:
	li r0, 0x3
	b @35
	@32:
	li r0, 0x4
	@35:
	cmpwi r0, 0x1
	bne @29
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@29:
	lfs f1, float_0_8041a7a4(r2)
	fneg f4, f31
	fmr f2, f1
	bl angleABf
	fsubs f0, f22, f17
	lis r0, 0x4330
	lfs f5, float_100_8041a7f8(r2)
	lfs f4, float_0p5_8041a7c4(r2)
	fsubs f3, f0, f26
	stw r0, 0xb8(r1)
	lfd f2, 0x1f0(r30)
	lfs f0, float_0p1_8041a7e4(r2)
	fmadds f3, f5, f3, f4
	stfs f1, 0x214(r31)
	fctiwz f1, f3
	stfd f1, 0xc0(r1)
	lwz r3, 0xc4(r1)
	xoris r3, r3, 0x8000
	stw r3, 0xbc(r1)
	lfd f1, 0xb8(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f5
	fabs f1, f1
	fcmpo cr0, f1, f0
	bge @27
	fmadds f0, f5, f17, f4
	stw r0, 0xb8(r1)
	mr r3, r29
	fctiwz f0, f0
	stfd f0, 0xc0(r1)
	lwz r0, 0xc4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f2
	fdivs f0, f0, f5
	stfs f0, 0x0(r27)
	b @2
	@27:
	addi r28, r28, 0x1
	cmpwi r28, 0x5
	blt @7
	li r3, 0x0
	@2:
	psq_l f31, 0x1f8(r1), 0, 0
	lfd f31, 0x1f0(r1)
	psq_l f30, 0x1e8(r1), 0, 0
	lfd f30, 0x1e0(r1)
	psq_l f29, 0x1d8(r1), 0, 0
	lfd f29, 0x1d0(r1)
	psq_l f28, 0x1c8(r1), 0, 0
	lfd f28, 0x1c0(r1)
	psq_l f27, 0x1b8(r1), 0, 0
	lfd f27, 0x1b0(r1)
	psq_l f26, 0x1a8(r1), 0, 0
	lfd f26, 0x1a0(r1)
	psq_l f25, 0x198(r1), 0, 0
	lfd f25, 0x190(r1)
	psq_l f24, 0x188(r1), 0, 0
	lfd f24, 0x180(r1)
	psq_l f23, 0x178(r1), 0, 0
	lfd f23, 0x170(r1)
	psq_l f22, 0x168(r1), 0, 0
	lfd f22, 0x160(r1)
	psq_l f21, 0x158(r1), 0, 0
	lfd f21, 0x150(r1)
	psq_l f20, 0x148(r1), 0, 0
	lfd f20, 0x140(r1)
	psq_l f19, 0x138(r1), 0, 0
	lfd f19, 0x130(r1)
	psq_l f18, 0x128(r1), 0, 0
	lfd f18, 0x120(r1)
	psq_l f17, 0x118(r1), 0, 0
	lfd f17, 0x110(r1)
	psq_l f16, 0x108(r1), 0, 0
	lfd f16, 0x100(r1)
	psq_l f15, 0xf8(r1), 0, 0
	lfd f15, 0xf0(r1)
	psq_l f14, 0xe8(r1), 0, 0
	lfd f14, 0xe0(r1)
	lmw r26, 0xc8(r1)
	lwz r0, 0x204(r1)
	mtlr r0
	addi r1, r1, 0x200
	blr
}

asm HitEntry* marioChkLandon(f32* a, f32 d) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x18(r1)
	fmr f31, f1
	stw r31, 0x14(r1)
	mr r31, r3
	bl marioGetPtr
	lbz r0, 0x3c(r3)
	cmpwi r0, 0x2
	beq @1
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @2
	fmr f1, f31
	mr r3, r31
	fmr f2, f31
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	bl marioSearchGround
	b @3
	@2:
	fmr f1, f31
	mr r3, r31
	fmr f2, f31
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	bl marioSearchGroundRoll
	b @3
	@1:
	fmr f1, f31
	mr r3, r31
	bl marioLandonChk_old
	@3:
	lwz r0, 0x24(r1)
	lfd f31, 0x18(r1)
	lwz r31, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void marioChkToge(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPtr
	mr r31, r3
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @1
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq @1
	bl vivianGetStatus
	cmpwi r3, 0x3
	bne @2
	b @1
	@2:
	lwz r3, 0x1e0(r31)
	cmplwi r3, 0x0
	beq @3
	bl hitGetAttr
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x20
	beq @3
	rlwinm. r0, r3, 0, 20, 20
	beq @3
	lfs f1, float_0p5_8041a7c4(r2)
	lfs f0, 0x1b4(r31)
	lfs f2, 0x210(r31)
	fmuls f0, f1, f0
	fcmpo cr0, f2, f0
	bge @3
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x20
	bl marioChgMot
	@3:
	lwz r3, 0x1f0(r31)
	cmplwi r3, 0x0
	beq @4
	bl hitGetAttr
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x20
	beq @4
	rlwinm. r0, r3, 0, 20, 20
	beq @4
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x20
	bl marioChgMot
	@4:
	lwz r3, 0x1f4(r31)
	cmplwi r3, 0x0
	beq @1
	bl hitGetAttr
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x20
	beq @1
	rlwinm. r0, r3, 0, 20, 20
	beq @1
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x20
	bl marioChgMot
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h) {
	nofralloc
	stwu r1, -0x180(r1)
	mflr r0
	stw r0, 0x184(r1)
	stfd f31, 0x170(r1)
	psq_st f31, 0x178(r1), 0, 0
	stfd f30, 0x160(r1)
	psq_st f30, 0x168(r1), 0, 0
	stfd f29, 0x150(r1)
	psq_st f29, 0x158(r1), 0, 0
	stfd f28, 0x140(r1)
	psq_st f28, 0x148(r1), 0, 0
	stfd f27, 0x130(r1)
	psq_st f27, 0x138(r1), 0, 0
	stfd f26, 0x120(r1)
	psq_st f26, 0x128(r1), 0, 0
	stfd f25, 0x110(r1)
	psq_st f25, 0x118(r1), 0, 0
	stfd f24, 0x100(r1)
	psq_st f24, 0x108(r1), 0, 0
	stfd f23, 0xf0(r1)
	psq_st f23, 0xf8(r1), 0, 0
	stmw r18, 0xb8(r1)
	fmr f23, f1
	lis r6, vec3_802c5730@ha
	fmr f24, f2
	mr r22, r3
	mr r23, r4
	mr r24, r5
	addi r28, r6, vec3_802c5730@l
	bl marioGetPtr
	lfs f0, float_0_8041a7a4(r2)
	mr r29, r3
	stfs f0, 0x218(r3)
	stfs f0, 0x21c(r3)
	stfs f0, 0x220(r3)
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 22, 22
	beq @1
	lfs f0, 0x90(r29)
	li r3, 0x0
	stfs f0, 0x0(r22)
	b @2
	@1:
	rlwinm. r0, r3, 0, 23, 23
	beq @3
	lfs f0, 0x90(r29)
	li r3, 0x0
	stfs f0, 0x0(r22)
	b @2
	@3:
	lfs f2, 0x1b8(r29)
	fabs f23, f23
	lfs f1, 0x90(r29)
	li r27, 0x0
	lfs f0, float_neg1_8041a7dc(r2)
	stfs f1, 0x0(r22)
	lfs f1, float_0p01_8041a854(r2)
	stfs f0, 0x0(r23)
	fadds f23, f23, f1
	lfs f28, float_neg10000_8041a858(r2)
	lfs f0, 0x214(r29)
	lwz r4, 0x60(r28)
	fabs f0, f0
	lwz r3, 0x64(r28)
	lwz r0, 0x68(r28)
	stw r4, 0x38(r1)
	fcmpo cr0, f0, f1
	lfs f26, 0x90(r29)
	stw r3, 0x3c(r1)
	lfs f27, 0x8c(r29)
	stw r0, 0x40(r1)
	lfs f25, 0x94(r29)
	bge @4
	lfs f29, float_2_8041a7e8(r2)
	li r26, 0x0
	li r25, 0x4
	b @5
	@4:
	lfs f29, float_10_8041a7fc(r2)
	li r26, 0x4
	li r25, 0x7
	@5:
	fadds f31, f26, f2
	lwz r30, 0x38(r1)
	fadds f30, f2, f23
	lwz r21, 0x3c(r1)
	lwz r20, 0x40(r1)
	slwi r31, r26, 2
	b @6
	@7:
	cmplwi r26, 0x6
	bgt @8
	lis r3, jumptable_8030E5C0@ha
	addi r3, r3, jumptable_8030E5C0@l
	lwzx r0, r3, r31
	mtctr r0
	bctr
	@9:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x10(r1)
	stfs f0, 0xc(r1)
	b @8
	@10:
	lfs f1, float_90_8041a81c(r2)
	lfs f0, 0x1a0(r29)
	lfs f2, float_3p1416_8041a7e0(r2)
	fadds f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f23, f1, f0
	fmr f1, f23
	bl sin
	frsp f2, f1
	lfs f0, float_8p64_8041a85c(r2)
	fmr f1, f23
	fmuls f0, f0, f2
	stfs f0, 0x10(r1)
	bl cos
	frsp f0, f1
	lfs f1, float_8p64_8041a85c(r2)
	fneg f0, f0
	fmuls f0, f1, f0
	stfs f0, 0xc(r1)
	b @8
	@11:
	lfs f1, 0x1a0(r29)
	lfs f0, float_90_8041a81c(r2)
	lfs f2, float_3p1416_8041a7e0(r2)
	fsubs f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f23, f1, f0
	fmr f1, f23
	bl sin
	frsp f2, f1
	lfs f0, float_8p64_8041a85c(r2)
	fmr f1, f23
	fmuls f0, f0, f2
	stfs f0, 0x10(r1)
	bl cos
	frsp f0, f1
	lfs f1, float_8p64_8041a85c(r2)
	fneg f0, f0
	fmuls f0, f1, f0
	stfs f0, 0xc(r1)
	b @8
	@12:
	lfs f0, float_0_8041a7a4(r2)
	addi r3, r1, 0x10
	lfs f1, float_3_8041a7f0(r2)
	addi r4, r1, 0xc
	stfs f0, 0x10(r1)
	stfs f0, 0xc(r1)
	lfs f2, 0x1a0(r29)
	bl movePos
	b @8
	@13:
	lfs f0, float_0_8041a7a4(r2)
	stfs f0, 0x10(r1)
	stfs f0, 0xc(r1)
	b @8
	@14:
	lfs f1, float_90_8041a81c(r2)
	lfs f0, 0x1a0(r29)
	lfs f2, float_3p1416_8041a7e0(r2)
	fadds f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f23, f1, f0
	fmr f1, f23
	bl sin
	frsp f2, f1
	lfs f0, float_8p64_8041a85c(r2)
	fmr f1, f23
	fmuls f0, f0, f2
	stfs f0, 0x10(r1)
	bl cos
	frsp f0, f1
	lfs f2, float_8p64_8041a85c(r2)
	lfs f1, float_3_8041a7f0(r2)
	addi r3, r1, 0x10
	addi r4, r1, 0xc
	fneg f0, f0
	fmuls f0, f2, f0
	stfs f0, 0xc(r1)
	lfs f2, 0x1a0(r29)
	bl movePos
	b @8
	@15:
	lfs f1, 0x1a0(r29)
	lfs f0, float_90_8041a81c(r2)
	lfs f2, float_3p1416_8041a7e0(r2)
	fsubs f1, f1, f0
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f23, f1, f0
	fmr f1, f23
	bl sin
	frsp f2, f1
	lfs f0, float_8p64_8041a85c(r2)
	fmr f1, f23
	fmuls f0, f0, f2
	stfs f0, 0x10(r1)
	bl cos
	frsp f0, f1
	lfs f2, float_8p64_8041a85c(r2)
	lfs f1, float_3_8041a7f0(r2)
	addi r3, r1, 0x10
	addi r4, r1, 0xc
	fneg f0, f0
	fmuls f0, f2, f0
	stfs f0, 0xc(r1)
	lfs f2, 0x1a0(r29)
	bl movePos
	@8:
	lfs f1, 0x10(r1)
	lfs f0, 0xc(r1)
	lwz r4, 0x6c(r28)
	fadds f1, f27, f1
	lwz r3, 0x70(r28)
	fadds f0, f25, f0
	lwz r0, 0x74(r28)
	stw r4, 0x14(r1)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	stfs f1, 0x14(r1)
	stfs f31, 0x18(r1)
	lwz r4, 0x14(r1)
	stfs f0, 0x1c(r1)
	lwz r3, 0x18(r1)
	lwz r0, 0x1c(r1)
	stw r4, 0x50(r1)
	stw r3, 0x54(r1)
	stw r0, 0x58(r1)
	stw r30, 0x5c(r1)
	stw r21, 0x60(r1)
	stw r20, 0x64(r1)
	stfs f30, 0x80(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @16
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x44
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @17
	@16:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @18
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x44
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @17
	@18:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x44
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@17:
	cmplwi r3, 0x0
	bne @19
	li r18, 0x0
	b @20
	@19:
	lwz r0, 0x68(r1)
	lwz r4, 0x6c(r1)
	stw r0, 0x2c(r1)
	lwz r0, 0x70(r1)
	lfs f1, 0x2c(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x30(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x34(r1)
	cror eq, gt, eq
	bne @21
	lfs f0, float_0p5_8041a7c4(r2)
	b @22
	@21:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@22:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x90(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0x1f0(r28)
	lfs f4, 0x30(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x2c(r1)
	cror eq, gt, eq
	bne @23
	lfs f0, float_0p5_8041a7c4(r2)
	b @24
	@23:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@24:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa0(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r28)
	lfs f4, 0x34(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x30(r1)
	cror eq, gt, eq
	bne @25
	lfs f0, float_0p5_8041a7c4(r2)
	b @26
	@25:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@26:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	addic. r0, r1, 0x20
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r28)
	fctiwz f0, f0
	stfd f0, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x34(r1)
	beq @27
	lwz r5, 0x74(r1)
	lwz r4, 0x78(r1)
	lwz r0, 0x7c(r1)
	stw r5, 0x20(r1)
	stw r4, 0x24(r1)
	stw r0, 0x28(r1)
	@27:
	mr r18, r3
	@20:
	cmplwi r18, 0x0
	beq @28
	bl marioGetPtr
	lfs f1, float_0_8041a7a4(r2)
	mr r19, r3
	lfs f4, float_100_8041a7f8(r2)
	lfs f3, 0x28(r1)
	fmr f2, f1
	lfs f0, 0x24(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f7, float_100_8041a7f8(r2)
	fsubs f4, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	lfs f2, float_0_8041a7a4(r2)
	lfs f3, 0x20(r1)
	fmadds f6, f7, f4, f0
	lfs f0, 0x24(r1)
	stw r0, 0xa8(r1)
	fmr f1, f2
	fmuls f4, f7, f0
	lfd f5, 0x1f0(r28)
	fctiwz f0, f6
	fmuls f3, f7, f3
	stfd f0, 0xb0(r1)
	lwz r0, 0xb4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f7
	stfs f0, 0x218(r19)
	stfs f2, 0x21c(r19)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f2, 0x20(r1)
	fsubs f3, f1, f0
	lfs f0, 0x28(r1)
	lfs f5, float_100_8041a7f8(r2)
	fmuls f1, f2, f2
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f0, f0
	fmadds f4, f5, f3, f2
	stw r0, 0x98(r1)
	lfd f2, 0x1f0(r28)
	fadds f3, f1, f0
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0xa0(r1)
	lwz r0, 0xa4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f2
	fdivs f0, f0, f5
	stfs f0, 0x220(r19)
	ble @29
	frsqrte f1, f3
	lfd f4, 0x1f8(r28)
	lfd f2, 0x200(r28)
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
	b @30
	@29:
	lfd f0, 0x208(r28)
	fcmpo cr0, f3, f0
	bge @31
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @30
	@31:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @32
	bge @33
	cmpwi r3, 0x0
	beq @34
	b @33
	@32:
	clrlwi. r0, r4, 9
	beq @35
	li r0, 0x1
	b @36
	@35:
	li r0, 0x2
	b @36
	@34:
	clrlwi. r0, r4, 9
	beq @37
	li r0, 0x5
	b @36
	@37:
	li r0, 0x3
	b @36
	@33:
	li r0, 0x4
	@36:
	cmpwi r0, 0x1
	bne @30
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@30:
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x24(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f0, float_105_8041a860(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @38
	lfs f0, float_75_8041a840(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @28
	@38:
	lfs f2, 0x30(r1)
	stfs f1, 0x214(r29)
	fcmpo cr0, f2, f26
	bge @39
	fsubs f0, f2, f26
	fabs f1, f0
	fcmpo cr0, f1, f29
	cror eq, gt, eq
	bne @39
	fabs f0, f24
	fcmpo cr0, f1, f0
	ble @40
	fsubs f0, f26, f2
	lfs f3, 0x2c(r1)
	fmr f1, f27
	lfs f4, 0x34(r1)
	fmr f2, f25
	fabs f0, f0
	stfs f0, 0x0(r23)
	bl angleABf
	stfs f1, 0x0(r24)
	b @28
	@40:
	fcmpo cr0, f2, f28
	ble @28
	stfs f2, 0x0(r22)
	fmr f28, f2
	lfs f0, float_0_8041a7a4(r2)
	fmr f1, f27
	fmr f2, f25
	lfs f3, 0x2c(r1)
	stfs f0, 0x0(r23)
	lfs f4, 0x34(r1)
	bl angleABf
	stfs f1, 0x0(r24)
	mr r27, r18
	b @28
	@39:
	lfs f2, 0x30(r1)
	lfs f0, float_11_8041a7ac(r2)
	fsubs f1, f2, f26
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @28
	fcmpo cr0, f2, f28
	ble @28
	stfs f2, 0x0(r22)
	fmr f28, f2
	lfs f0, float_0_8041a7a4(r2)
	fmr f1, f27
	fmr f2, f25
	lfs f3, 0x2c(r1)
	stfs f0, 0x0(r23)
	lfs f4, 0x34(r1)
	bl angleABf
	stfs f1, 0x0(r24)
	mr r27, r18
	@28:
	addi r26, r26, 0x1
	addi r31, r31, 0x4
	@6:
	cmpw r26, r25
	blt @7
	cmplwi r27, 0x0
	beq @41
	mr r3, r27
	b @2
	@41:
	li r3, 0x0
	@2:
	psq_l f31, 0x178(r1), 0, 0
	lfd f31, 0x170(r1)
	psq_l f30, 0x168(r1), 0, 0
	lfd f30, 0x160(r1)
	psq_l f29, 0x158(r1), 0, 0
	lfd f29, 0x150(r1)
	psq_l f28, 0x148(r1), 0, 0
	lfd f28, 0x140(r1)
	psq_l f27, 0x138(r1), 0, 0
	lfd f27, 0x130(r1)
	psq_l f26, 0x128(r1), 0, 0
	lfd f26, 0x120(r1)
	psq_l f25, 0x118(r1), 0, 0
	lfd f25, 0x110(r1)
	psq_l f24, 0x108(r1), 0, 0
	lfd f24, 0x100(r1)
	psq_l f23, 0xf8(r1), 0, 0
	lfd f23, 0xf0(r1)
	lmw r18, 0xb8(r1)
	lwz r0, 0x184(r1)
	mtlr r0
	addi r1, r1, 0x180
	blr
}

asm HitEntry* marioSearchGround(f32* y, f32* b, f32* c, f32 spd, f32 h) {
	nofralloc
	stwu r1, -0x1e0(r1)
	mflr r0
	stw r0, 0x1e4(r1)
	stfd f31, 0x1d0(r1)
	psq_st f31, 0x1d8(r1), 0, 0
	stfd f30, 0x1c0(r1)
	psq_st f30, 0x1c8(r1), 0, 0
	stfd f29, 0x1b0(r1)
	psq_st f29, 0x1b8(r1), 0, 0
	stfd f28, 0x1a0(r1)
	psq_st f28, 0x1a8(r1), 0, 0
	stfd f27, 0x190(r1)
	psq_st f27, 0x198(r1), 0, 0
	stfd f26, 0x180(r1)
	psq_st f26, 0x188(r1), 0, 0
	stfd f25, 0x170(r1)
	psq_st f25, 0x178(r1), 0, 0
	stfd f24, 0x160(r1)
	psq_st f24, 0x168(r1), 0, 0
	stfd f23, 0x150(r1)
	psq_st f23, 0x158(r1), 0, 0
	stfd f22, 0x140(r1)
	psq_st f22, 0x148(r1), 0, 0
	stfd f21, 0x130(r1)
	psq_st f21, 0x138(r1), 0, 0
	stfd f20, 0x120(r1)
	psq_st f20, 0x128(r1), 0, 0
	stfd f19, 0x110(r1)
	psq_st f19, 0x118(r1), 0, 0
	stfd f18, 0x100(r1)
	psq_st f18, 0x108(r1), 0, 0
	stmw r20, 0xd0(r1)
	fmr f18, f1
	lis r6, vec3_802c5730@ha
	fmr f29, f2
	mr r23, r3
	mr r24, r4
	mr r25, r5
	addi r28, r6, vec3_802c5730@l
	bl marioGetPtr
	lfs f3, float_0_8041a7a4(r2)
	mr r29, r3
	stfs f3, 0x218(r3)
	stfs f3, 0x21c(r3)
	stfs f3, 0x220(r3)
	stfs f3, 0x214(r3)
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 22, 22
	beq @1
	lfs f0, 0x90(r29)
	li r3, 0x0
	stfs f0, 0x0(r23)
	b @2
	@1:
	rlwinm. r0, r3, 0, 23, 23
	beq @3
	lfs f0, 0x90(r29)
	li r3, 0x0
	stfs f0, 0x0(r23)
	b @2
	@3:
	lfs f0, 0x90(r29)
	fabs f18, f18
	lfs f2, float_0p01_8041a854(r2)
	fabs f1, f29
	stfs f0, 0x0(r23)
	lfs f0, float_neg1_8041a7dc(r2)
	fadds f18, f18, f2
	lfs f2, float_5_8041a7b8(r2)
	stfs f0, 0x0(r24)
	fadds f20, f2, f1
	lfs f0, 0x180(r29)
	fcmpu cr0, f0, f3
	beq @4
	lfs f1, 0x1a0(r29)
	lfs f0, 0x198(r29)
	fsubs f1, f1, f0
	bl revise360
	b @5
	@4:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	@5:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 11, 11
	beq @6
	lfs f2, float_3p1416_8041a7e0(r2)
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f19, f1, f0
	fmr f1, f19
	bl sin
	frsp f3, f1
	lfs f0, 0x1b4(r29)
	lfs f2, float_0p425_8041a864(r2)
	fmr f1, f19
	fmuls f0, f0, f3
	fmuls f24, f2, f0
	bl cos
	frsp f0, f1
	lfs f1, 0x1b4(r29)
	lfs f2, float_0p425_8041a864(r2)
	fneg f0, f0
	fmuls f0, f1, f0
	fmuls f23, f2, f0
	b @7
	@6:
	lfs f2, float_3p1416_8041a7e0(r2)
	lfs f0, float_180_8041a7cc(r2)
	fmuls f1, f2, f1
	fdivs f19, f1, f0
	fmr f1, f19
	bl sin
	frsp f3, f1
	lfs f0, 0x1b4(r29)
	lfs f2, float_0p375_8041a868(r2)
	fmr f1, f19
	fmuls f0, f0, f3
	fmuls f24, f2, f0
	bl cos
	frsp f0, f1
	lfs f1, 0x1b4(r29)
	lfs f2, float_0p375_8041a868(r2)
	fneg f0, f0
	fmuls f0, f1, f0
	fmuls f23, f2, f0
	@7:
	lfs f21, 0x90(r29)
	fneg f28, f23
	lwz r30, 0x48(r28)
	fneg f27, f24
	lwz r31, 0x4c(r28)
	fadds f19, f21, f20
	lwz r22, 0x50(r28)
	fadds f26, f20, f18
	stw r30, 0x4c(r1)
	lfs f22, 0x8c(r29)
	li r27, 0x0
	stw r31, 0x50(r1)
	li r26, 0x0
	stw r22, 0x54(r1)
	lfs f20, 0x94(r29)
	lfs f25, float_neg10000_8041a858(r2)
	@8:
	cmpwi r26, 0x0
	bne @9
	lfs f31, float_0_8041a7a4(r2)
	fmr f30, f31
	b @10
	@9:
	cmpwi r26, 0x1
	bne @11
	fmr f31, f24
	fmr f30, f23
	b @10
	@11:
	cmpwi r26, 0x2
	bne @12
	fmr f31, f28
	fmr f30, f24
	b @10
	@12:
	cmpwi r26, 0x3
	bne @13
	fmr f31, f23
	fmr f30, f27
	b @10
	@13:
	cmpwi r26, 0x4
	bne @10
	fmr f31, f27
	fmr f30, f28
	@10:
	lwz r4, 0x54(r28)
	fadds f1, f22, f31
	lwz r3, 0x58(r28)
	fadds f0, f20, f30
	lwz r0, 0x5c(r28)
	stw r4, 0x28(r1)
	stw r3, 0x2c(r1)
	stw r0, 0x30(r1)
	stfs f1, 0x28(r1)
	stfs f19, 0x2c(r1)
	lwz r4, 0x28(r1)
	stfs f0, 0x30(r1)
	lwz r3, 0x2c(r1)
	lwz r0, 0x30(r1)
	stw r4, 0x64(r1)
	stw r3, 0x68(r1)
	stw r0, 0x6c(r1)
	stw r30, 0x70(r1)
	stw r31, 0x74(r1)
	stw r22, 0x78(r1)
	stfs f26, 0x94(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @14
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x58
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @15
	@14:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @16
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x58
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @15
	@16:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x58
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@15:
	cmplwi r3, 0x0
	bne @17
	li r3, 0x0
	b @18
	@17:
	lwz r0, 0x7c(r1)
	lwz r4, 0x80(r1)
	stw r0, 0x40(r1)
	lwz r0, 0x84(r1)
	lfs f1, 0x40(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x44(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x48(r1)
	cror eq, gt, eq
	bne @19
	lfs f0, float_0p5_8041a7c4(r2)
	b @20
	@19:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@20:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa0(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0x1f0(r28)
	lfs f4, 0x44(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x40(r1)
	cror eq, gt, eq
	bne @21
	lfs f0, float_0p5_8041a7c4(r2)
	b @22
	@21:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@22:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r28)
	lfs f4, 0x48(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x44(r1)
	cror eq, gt, eq
	bne @23
	lfs f0, float_0p5_8041a7c4(r2)
	b @24
	@23:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@24:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xc0(r1)
	addic. r0, r1, 0x34
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r28)
	fctiwz f0, f0
	stfd f0, 0xb8(r1)
	lwz r0, 0xbc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xc4(r1)
	lfd f0, 0xc0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x48(r1)
	beq @18
	lwz r5, 0x88(r1)
	lwz r4, 0x8c(r1)
	lwz r0, 0x90(r1)
	stw r5, 0x34(r1)
	stw r4, 0x38(r1)
	stw r0, 0x3c(r1)
	@18:
	cmplwi r3, 0x0
	mr r20, r3
	beq @25
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 7, 7
	beq @26
	lfs f18, float_75_8041a840(r2)
	b @27
	@26:
	lhz r0, 0x2e(r29)
	cmplwi r0, 0x10
	bne @28
	lfs f18, float_75_8041a840(r2)
	b @27
	@28:
	lfs f18, float_50_8041a844(r2)
	@27:
	bl marioGetPtr
	lfs f1, float_0_8041a7a4(r2)
	mr r21, r3
	lfs f4, float_100_8041a7f8(r2)
	lfs f3, 0x3c(r1)
	fmr f2, f1
	lfs f0, 0x38(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f7, float_100_8041a7f8(r2)
	fsubs f4, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	lfs f2, float_0_8041a7a4(r2)
	lfs f3, 0x34(r1)
	fmadds f6, f7, f4, f0
	lfs f0, 0x38(r1)
	stw r0, 0xb8(r1)
	fmr f1, f2
	fmuls f4, f7, f0
	lfd f5, 0x1f0(r28)
	fctiwz f0, f6
	fmuls f3, f7, f3
	stfd f0, 0xc0(r1)
	lwz r0, 0xc4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f7
	stfs f0, 0x218(r21)
	stfs f2, 0x21c(r21)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f2, 0x34(r1)
	fsubs f3, f1, f0
	lfs f0, 0x3c(r1)
	lfs f5, float_100_8041a7f8(r2)
	fmuls f1, f2, f2
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f0, f0
	fmadds f4, f5, f3, f2
	stw r0, 0xa8(r1)
	lfd f2, 0x1f0(r28)
	fadds f3, f1, f0
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0xb0(r1)
	lwz r0, 0xb4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f2
	fdivs f0, f0, f5
	stfs f0, 0x220(r21)
	ble @29
	frsqrte f1, f3
	lfd f4, 0x1f8(r28)
	lfd f2, 0x200(r28)
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
	b @30
	@29:
	lfd f0, 0x208(r28)
	fcmpo cr0, f3, f0
	bge @31
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @30
	@31:
	stfs f3, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @32
	bge @33
	cmpwi r3, 0x0
	beq @34
	b @33
	@32:
	clrlwi. r0, r4, 9
	beq @35
	li r0, 0x1
	b @36
	@35:
	li r0, 0x2
	b @36
	@34:
	clrlwi. r0, r4, 9
	beq @37
	li r0, 0x5
	b @36
	@37:
	li r0, 0x3
	b @36
	@33:
	li r0, 0x4
	@36:
	cmpwi r0, 0x1
	bne @30
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@30:
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x38(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	fcmpo cr0, f1, f18
	cror eq, gt, eq
	bne @25
	li r20, 0x0
	@25:
	cmplwi r20, 0x0
	beq @38
	bl marioGetPtr
	lfs f1, float_0_8041a7a4(r2)
	mr r21, r3
	lfs f4, float_100_8041a7f8(r2)
	lfs f3, 0x3c(r1)
	fmr f2, f1
	lfs f0, 0x38(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f7, float_100_8041a7f8(r2)
	fsubs f4, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	lfs f2, float_0_8041a7a4(r2)
	lfs f3, 0x34(r1)
	fmadds f6, f7, f4, f0
	lfs f0, 0x38(r1)
	stw r0, 0xb8(r1)
	fmr f1, f2
	fmuls f4, f7, f0
	lfd f5, 0x1f0(r28)
	fctiwz f0, f6
	fmuls f3, f7, f3
	stfd f0, 0xc0(r1)
	lwz r0, 0xc4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f5
	fdivs f0, f0, f7
	stfs f0, 0x218(r21)
	stfs f2, 0x21c(r21)
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f2, 0x34(r1)
	fsubs f3, f1, f0
	lfs f0, 0x3c(r1)
	lfs f5, float_100_8041a7f8(r2)
	fmuls f1, f2, f2
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f0, f0
	fmadds f4, f5, f3, f2
	stw r0, 0xa8(r1)
	lfd f2, 0x1f0(r28)
	fadds f3, f1, f0
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0xb0(r1)
	lwz r0, 0xb4(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f2
	fdivs f0, f0, f5
	stfs f0, 0x220(r21)
	ble @39
	frsqrte f1, f3
	lfd f4, 0x1f8(r28)
	lfd f2, 0x200(r28)
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
	b @40
	@39:
	lfd f0, 0x208(r28)
	fcmpo cr0, f3, f0
	bge @41
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @40
	@41:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @42
	bge @43
	cmpwi r3, 0x0
	beq @44
	b @43
	@42:
	clrlwi. r0, r4, 9
	beq @45
	li r0, 0x1
	b @46
	@45:
	li r0, 0x2
	b @46
	@44:
	clrlwi. r0, r4, 9
	beq @47
	li r0, 0x5
	b @46
	@47:
	li r0, 0x3
	b @46
	@43:
	li r0, 0x4
	@46:
	cmpwi r0, 0x1
	bne @40
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@40:
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x38(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f2, 0x44(r1)
	stfs f1, 0x214(r29)
	fcmpo cr0, f2, f21
	bge @48
	fsubs f1, f2, f21
	lfs f0, float_2_8041a7e8(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @48
	fabs f0, f29
	fcmpo cr0, f1, f0
	ble @49
	fsubs f0, f21, f2
	lfs f3, 0x40(r1)
	fmr f1, f22
	lfs f4, 0x48(r1)
	fmr f2, f20
	fabs f0, f0
	stfs f0, 0x0(r24)
	bl angleABf
	stfs f1, 0x0(r25)
	b @38
	@49:
	fcmpo cr0, f2, f25
	ble @38
	stfs f2, 0x0(r23)
	fmr f25, f2
	lfs f0, float_0_8041a7a4(r2)
	fmr f1, f22
	fmr f2, f20
	lfs f3, 0x40(r1)
	stfs f0, 0x0(r24)
	lfs f4, 0x48(r1)
	bl angleABf
	stfs f1, 0x0(r25)
	addi r3, r1, 0x1c
	lwz r5, 0x40(r1)
	lwz r4, 0x44(r1)
	lwz r0, 0x48(r1)
	stw r5, 0x1c(r1)
	stw r4, 0x20(r1)
	stw r0, 0x24(r1)
	bl marioUpdateCamCollision
	mr r27, r20
	b @38
	@48:
	lfs f2, 0x44(r1)
	lfs f0, float_11_8041a7ac(r2)
	fsubs f1, f2, f21
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @38
	fcmpo cr0, f2, f25
	ble @38
	stfs f2, 0x0(r23)
	fmr f25, f2
	lfs f0, float_0_8041a7a4(r2)
	fmr f1, f22
	fmr f2, f20
	lfs f3, 0x40(r1)
	stfs f0, 0x0(r24)
	lfs f4, 0x48(r1)
	bl angleABf
	stfs f1, 0x0(r25)
	addi r3, r1, 0x10
	lwz r5, 0x40(r1)
	lwz r4, 0x44(r1)
	lwz r0, 0x48(r1)
	stw r5, 0x10(r1)
	stw r4, 0x14(r1)
	stw r0, 0x18(r1)
	bl marioUpdateCamCollision
	mr r27, r20
	@38:
	addi r26, r26, 0x1
	cmpwi r26, 0x5
	blt @8
	cmplwi r27, 0x0
	beq @50
	mr r3, r27
	b @2
	@50:
	li r3, 0x0
	@2:
	psq_l f31, 0x1d8(r1), 0, 0
	lfd f31, 0x1d0(r1)
	psq_l f30, 0x1c8(r1), 0, 0
	lfd f30, 0x1c0(r1)
	psq_l f29, 0x1b8(r1), 0, 0
	lfd f29, 0x1b0(r1)
	psq_l f28, 0x1a8(r1), 0, 0
	lfd f28, 0x1a0(r1)
	psq_l f27, 0x198(r1), 0, 0
	lfd f27, 0x190(r1)
	psq_l f26, 0x188(r1), 0, 0
	lfd f26, 0x180(r1)
	psq_l f25, 0x178(r1), 0, 0
	lfd f25, 0x170(r1)
	psq_l f24, 0x168(r1), 0, 0
	lfd f24, 0x160(r1)
	psq_l f23, 0x158(r1), 0, 0
	lfd f23, 0x150(r1)
	psq_l f22, 0x148(r1), 0, 0
	lfd f22, 0x140(r1)
	psq_l f21, 0x138(r1), 0, 0
	lfd f21, 0x130(r1)
	psq_l f20, 0x128(r1), 0, 0
	lfd f20, 0x120(r1)
	psq_l f19, 0x118(r1), 0, 0
	lfd f19, 0x110(r1)
	psq_l f18, 0x108(r1), 0, 0
	lfd f18, 0x100(r1)
	lmw r20, 0xd0(r1)
	lwz r0, 0x1e4(r1)
	mtlr r0
	addi r1, r1, 0x1e0
	blr
}

asm void marioChkGnd2(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r31, r3
	rlwinm. r0, r0, 0, 15, 15
	bne @1
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	beq @2
	lfs f1, float_0p1_8041a7e4(r2)
	addi r3, r1, 0xc
	lfs f2, 0x7c(r31)
	addi r4, r1, 0x10
	addi r5, r1, 0x8
	bl marioSearchGround
	b @3
	@2:
	lfs f1, float_0p1_8041a7e4(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x10
	addi r5, r1, 0x8
	bl kpaSearchGround
	@3:
	cmplwi r3, 0x0
	beq @1
	lfs f2, 0x90(r31)
	lfs f0, 0xc(r1)
	lfs f1, float_0_8041a7a4(r2)
	fsubs f2, f2, f0
	fcmpo cr0, f2, f1
	bge @1
	lfs f0, float_neg10_8041a804(r2)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne @1
	stw r3, 0x1e4(r31)
	li r0, 0x0
	lfs f0, 0xc(r1)
	stfs f0, 0x90(r31)
	lwz r3, 0x0(r31)
	rlwinm r3, r3, 0, 26, 23
	stw r3, 0x0(r31)
	sth r0, 0x50(r31)
	sth r0, 0x52(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @4
	lfs f0, 0x190(r31)
	fcmpu cr0, f0, f1
	bne @5
	bl kpaFireAttackCheck
	cmpwi r3, 0x0
	bne @6
	@5:
	lbz r3, 0x24e(r31)
	lbz r0, 0x24f(r31)
	extsb r3, r3
	extsb r0, r0
	mullw r3, r3, r3
	mullw r0, r0, r0
	add r0, r3, r0
	cmpwi r0, 0xbd1
	ble @7
	li r3, 0x2
	bl marioChgMot
	b @8
	@7:
	li r3, 0x1
	bl marioChgMot
	b @8
	@6:
	li r3, 0x0
	bl marioChgMot
	@8:
	bl quake_kpaLandOn
	b @9
	@4:
	li r3, 0x0
	bl marioChgMot
	@9:
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	beq @10
	bl marioBgmodeChk
	cmpwi r3, 0x0
	bne @1
	bl camFollowYOn
	b @1
	@10:
	bl kpaCamFollow
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void marioChkGnd(void) {
	nofralloc
	stwu r1, -0x1b0(r1)
	mflr r0
	stw r0, 0x1b4(r1)
	stfd f31, 0x1a0(r1)
	psq_st f31, 0x1a8(r1), 0, 0
	stfd f30, 0x190(r1)
	psq_st f30, 0x198(r1), 0, 0
	stw r31, 0x18c(r1)
	stw r30, 0x188(r1)
	stw r29, 0x184(r1)
	lis r3, vec3_802c5730@ha
	addi r30, r3, vec3_802c5730@l
	bl marioGetPtr
	mr r31, r3
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @1
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq @1
	bl vivianGetStatus
	cmpwi r3, 0x3
	bne @2
	@1:
	lfs f1, float_37_8041a86c(r2)
	addi r3, r1, 0x1c
	lfs f2, float_0_8041a7a4(r2)
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl marioSearchGround
	stw r3, 0x1e4(r31)
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r29, r3
	lfs f1, 0x1b8(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @3
	lfs f0, float_0p5_8041a7c4(r2)
	fmuls f1, f1, f0
	@3:
	lwz r0, 0x90(r29)
	lwz r7, 0x8c(r29)
	stw r0, 0x70(r1)
	lwz r6, 0x94(r29)
	lfs f0, 0x70(r1)
	lwz r4, 0x24(r30)
	fadds f1, f0, f1
	lwz r3, 0x28(r30)
	lwz r0, 0x2c(r30)
	lfs f0, float_1000_8041a7a0(r2)
	stfs f1, 0x70(r1)
	lwz r5, 0x70(r1)
	stw r7, 0x6c(r1)
	stw r6, 0x74(r1)
	stw r7, 0x11c(r1)
	stw r5, 0x120(r1)
	stw r6, 0x124(r1)
	stw r4, 0x128(r1)
	stw r3, 0x12c(r1)
	stw r0, 0x130(r1)
	stfs f0, 0x14c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @4
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @5
	@4:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @6
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @5
	@6:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@5:
	cmplwi r3, 0x0
	bne @7
	li r3, 0x0
	b @8
	@7:
	lwz r0, 0x134(r1)
	lwz r4, 0x138(r1)
	stw r0, 0x78(r1)
	lwz r0, 0x13c(r1)
	lfs f1, 0x78(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x7c(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x80(r1)
	cror eq, gt, eq
	bne @9
	lfs f0, float_0p5_8041a7c4(r2)
	b @10
	@9:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@10:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x158(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x7c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x150(r1)
	lwz r0, 0x154(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x15c(r1)
	lfd f0, 0x158(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x78(r1)
	cror eq, gt, eq
	bne @11
	lfs f0, float_0p5_8041a7c4(r2)
	b @12
	@11:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@12:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x168(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x80(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x160(r1)
	lwz r0, 0x164(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x16c(r1)
	lfd f0, 0x168(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x7c(r1)
	cror eq, gt, eq
	bne @13
	lfs f0, float_0p5_8041a7c4(r2)
	b @14
	@13:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@14:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x178(r1)
	addic. r0, r1, 0x84
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x170(r1)
	lwz r0, 0x174(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x17c(r1)
	lfd f0, 0x178(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x80(r1)
	beq @8
	lwz r5, 0x140(r1)
	lwz r4, 0x144(r1)
	lwz r0, 0x148(r1)
	stw r5, 0x84(r1)
	stw r4, 0x88(r1)
	stw r0, 0x8c(r1)
	@8:
	cmplwi r3, 0x0
	beq @15
	lfs f0, 0x7c(r1)
	b @16
	@15:
	lfs f0, float_neg3000_8041a870(r2)
	@16:
	stfs f0, 0x1c0(r29)
	stw r3, 0x1f8(r31)
	b @17
	@2:
	li r0, 0x0
	stw r0, 0x1e4(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @18
	bl kpaClearHitobjRide
	@18:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r29, r3
	lfs f1, 0x1b8(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @19
	lfs f0, float_0p5_8041a7c4(r2)
	fmuls f1, f1, f0
	@19:
	lwz r0, 0x90(r29)
	lwz r7, 0x8c(r29)
	stw r0, 0x4c(r1)
	lwz r6, 0x94(r29)
	lfs f0, 0x4c(r1)
	lwz r4, 0x24(r30)
	fadds f1, f0, f1
	lwz r3, 0x28(r30)
	lwz r0, 0x2c(r30)
	lfs f0, float_1000_8041a7a0(r2)
	stfs f1, 0x4c(r1)
	lwz r5, 0x4c(r1)
	stw r7, 0x48(r1)
	stw r6, 0x50(r1)
	stw r7, 0xdc(r1)
	stw r5, 0xe0(r1)
	stw r6, 0xe4(r1)
	stw r4, 0xe8(r1)
	stw r3, 0xec(r1)
	stw r0, 0xf0(r1)
	stfs f0, 0x10c(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @20
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @21
	@20:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @22
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @21
	@22:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@21:
	cmplwi r3, 0x0
	bne @23
	li r3, 0x0
	b @24
	@23:
	lwz r0, 0xf4(r1)
	lwz r4, 0xf8(r1)
	stw r0, 0x54(r1)
	lwz r0, 0xfc(r1)
	lfs f1, 0x54(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x58(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x5c(r1)
	cror eq, gt, eq
	bne @25
	lfs f0, float_0p5_8041a7c4(r2)
	b @26
	@25:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@26:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x170(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x58(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x178(r1)
	lwz r0, 0x17c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x54(r1)
	cror eq, gt, eq
	bne @27
	lfs f0, float_0p5_8041a7c4(r2)
	b @28
	@27:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@28:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x160(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x5c(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x168(r1)
	lwz r0, 0x16c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x164(r1)
	lfd f0, 0x160(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x58(r1)
	cror eq, gt, eq
	bne @29
	lfs f0, float_0p5_8041a7c4(r2)
	b @30
	@29:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@30:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x150(r1)
	addic. r0, r1, 0x60
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x158(r1)
	lwz r0, 0x15c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x154(r1)
	lfd f0, 0x150(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x5c(r1)
	beq @24
	lwz r5, 0x100(r1)
	lwz r4, 0x104(r1)
	lwz r0, 0x108(r1)
	stw r5, 0x60(r1)
	stw r4, 0x64(r1)
	stw r0, 0x68(r1)
	@24:
	cmplwi r3, 0x0
	beq @31
	lfs f0, 0x58(r1)
	b @32
	@31:
	lfs f0, float_neg3000_8041a870(r2)
	@32:
	stfs f0, 0x1c0(r29)
	stw r3, 0x1f8(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 15
	bne @17
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @33
	li r0, 0x0
	b @34
	@33:
	lfs f1, 0x90(r3)
	lfs f0, float_5000_8041a874(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @35
	li r0, 0x0
	b @34
	@35:
	li r0, 0x1
	@34:
	cmpwi r0, 0x0
	beq @17
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 22, 22
	bne @36
	rlwinm. r0, r3, 0, 7, 7
	beq @37
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x1c
	lfs f2, 0x7c(r31)
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl marioSearchGroundRoll
	cmplwi r3, 0x0
	beq @38
	stw r3, 0x1e4(r31)
	lis r0, 0x4330
	lfs f2, float_100_8041a7f8(r2)
	lfs f1, 0x1c(r1)
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0x170(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x178(r1)
	lwz r0, 0x17c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x1c0(r31)
	b @38
	@37:
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @39
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x1c
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl kpaSearchGround
	b @40
	@39:
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x1c
	lfs f2, 0x7c(r31)
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl marioSearchGround
	@40:
	cmplwi r3, 0x0
	beq @38
	stw r3, 0x1e4(r31)
	lis r0, 0x4330
	lfs f2, float_100_8041a7f8(r2)
	lfs f1, 0x1c(r1)
	lfs f0, float_0p5_8041a7c4(r2)
	stw r0, 0x170(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x178(r1)
	lwz r0, 0x17c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x1c0(r31)
	b @38
	@36:
	lfs f0, 0x90(r31)
	stfs f0, 0x1c(r1)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @41
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @38
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
	b @17
	@41:
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @38
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
	b @17
	@38:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x19
	bne @42
	bl marioChkShipMoveMode
	cmpwi r3, 0x0
	beq @17
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	bne @43
	bl marioShipChgFall
	b @17
	@43:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 15, 13
	stw r0, 0x0(r31)
	b @17
	@42:
	cmplwi r0, 0x1f
	beq @44
	lwz r3, 0x1e4(r31)
	cmplwi r3, 0x0
	beq @44
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq @44
	lfs f1, 0x7c(r31)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @45
	bl marioSetFallPara
	@45:
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x1f
	bl marioChgMot
	b @17
	@44:
	lwz r3, 0x1e4(r31)
	cmplwi r3, 0x0
	beq @46
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq @46
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @17
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq @17
	bl vivianGetStatus
	cmpwi r3, 0x3
	beq @17
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x20
	bl marioChgMot
	b @17
	@46:
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne @47
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne @48
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	bl marioChkFrontStep
	lfs f2, 0x14(r1)
	cmplwi r3, 0x0
	lfs f0, 0x90(r31)
	fsubs f1, f2, f0
	beq @47
	lfs f0, float_11_8041a7ac(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @47
	lfs f0, float_5_8041a7b8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @47
	lfs f1, 0x214(r31)
	lfs f0, float_30_8041a82c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @47
	stfs f2, 0x1c4(r31)
	lfs f0, float_0_8041a7a4(r2)
	lfs f1, 0x180(r31)
	fcmpu cr0, f1, f0
	beq @47
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne @49
	li r3, 0xc
	bl marioChgMot
	b @17
	@49:
	li r3, 0xc
	li r4, 0x0
	bl marioChgMotSub
	b @17
	@48:
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	bl marioChkFrontStep
	lfs f2, 0x14(r1)
	cmplwi r3, 0x0
	lfs f0, 0x90(r31)
	fsubs f1, f2, f0
	beq @47
	lfs f0, float_11_8041a7ac(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @47
	lfs f0, float_5_8041a7b8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @47
	lfs f1, 0x214(r31)
	lfs f0, float_30_8041a82c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @47
	stfs f2, 0x1c4(r31)
	lfs f0, float_0_8041a7a4(r2)
	lfs f1, 0x180(r31)
	fcmpu cr0, f1, f0
	beq @47
	bl roll_upstairs_on
	b @17
	@47:
	lfs f0, 0x1c(r1)
	stfs f0, 0x90(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne @50
	bl kpaChkHitobjRide
	b @51
	@50:
	lwz r3, 0x1e4(r31)
	@51:
	cmplwi r3, 0x0
	beq @52
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq @17
	lfs f2, 0x114(r31)
	lfs f0, 0x90(r31)
	lfs f1, float_10_8041a7fc(r2)
	fsubs f2, f2, f0
	lfs f0, float_47_8041a84c(r2)
	stfs f2, 0x164(r31)
	lwz r0, 0x90(r31)
	lwz r7, 0x8c(r31)
	stw r0, 0x28(r1)
	lwz r6, 0x94(r31)
	lfs f2, 0x28(r1)
	lwz r4, 0x18(r30)
	fadds f1, f2, f1
	lwz r3, 0x1c(r30)
	lwz r0, 0x20(r30)
	stw r7, 0x24(r1)
	stfs f1, 0x28(r1)
	lwz r5, 0x28(r1)
	stw r6, 0x2c(r1)
	stw r7, 0x9c(r1)
	stw r5, 0xa0(r1)
	stw r6, 0xa4(r1)
	stw r4, 0xa8(r1)
	stw r3, 0xac(r1)
	stw r0, 0xb0(r1)
	stfs f0, 0xcc(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @53
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @54
	@53:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @55
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @54
	@55:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@54:
	cmplwi r3, 0x0
	bne @56
	li r29, 0x0
	b @57
	@56:
	lwz r0, 0xb4(r1)
	lwz r4, 0xb8(r1)
	stw r0, 0x30(r1)
	lwz r0, 0xbc(r1)
	lfs f1, 0x30(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x34(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x38(r1)
	cror eq, gt, eq
	bne @58
	lfs f0, float_0p5_8041a7c4(r2)
	b @59
	@58:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@59:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x170(r1)
	fmadds f2, f3, f1, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x34(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x178(r1)
	lwz r0, 0x17c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x30(r1)
	cror eq, gt, eq
	bne @60
	lfs f0, float_0p5_8041a7c4(r2)
	b @61
	@60:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@61:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x160(r1)
	fmadds f2, f3, f4, f0
	lfd f1, 0x1f0(r30)
	lfs f4, 0x38(r1)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f2, f2
	fcmpo cr0, f4, f0
	stfd f2, 0x168(r1)
	lwz r0, 0x16c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x164(r1)
	lfd f0, 0x160(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x34(r1)
	cror eq, gt, eq
	bne @62
	lfs f0, float_0p5_8041a7c4(r2)
	b @63
	@62:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@63:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x150(r1)
	addic. r0, r1, 0x3c
	fmadds f0, f2, f4, f0
	lfd f1, 0x1f0(r30)
	fctiwz f0, f0
	stfd f0, 0x158(r1)
	lwz r0, 0x15c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x154(r1)
	lfd f0, 0x150(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x38(r1)
	beq @64
	lwz r5, 0xc0(r1)
	lwz r4, 0xc4(r1)
	lwz r0, 0xc8(r1)
	stw r5, 0x3c(r1)
	stw r4, 0x40(r1)
	stw r0, 0x44(r1)
	@64:
	mr r29, r3
	@57:
	cmplwi r29, 0x0
	beq @65
	lfs f1, float_0_8041a7a4(r2)
	lfs f4, float_100_8041a7f8(r2)
	lfs f3, 0x44(r1)
	fmr f2, f1
	lfs f0, 0x40(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f7, float_100_8041a7f8(r2)
	fsubs f2, f1, f0
	lfs f0, float_0p5_8041a7c4(r2)
	lfs f1, float_0_8041a7a4(r2)
	lfs f3, 0x3c(r1)
	fmadds f4, f7, f2, f0
	lfs f0, 0x40(r1)
	stw r0, 0x170(r1)
	fmr f2, f1
	lfd f5, 0x1f0(r30)
	fmuls f3, f7, f3
	fctiwz f6, f4
	fmuls f4, f7, f0
	stfd f6, 0x178(r1)
	lwz r0, 0x17c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f5
	fdivs f31, f0, f7
	bl angleABf
	lfs f0, float_180_8041a7cc(r2)
	lis r0, 0x4330
	lfs f2, 0x3c(r1)
	fsubs f3, f1, f0
	lfs f0, 0x44(r1)
	lfs f5, float_100_8041a7f8(r2)
	fmuls f1, f2, f2
	lfs f2, float_0p5_8041a7c4(r2)
	fmuls f0, f0, f0
	fmadds f4, f5, f3, f2
	stw r0, 0x160(r1)
	lfd f2, 0x1f0(r30)
	fadds f3, f1, f0
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f4
	fcmpo cr0, f3, f0
	stfd f1, 0x168(r1)
	lwz r0, 0x16c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x164(r1)
	lfd f0, 0x160(r1)
	fsubs f0, f0, f2
	fdivs f30, f0, f5
	ble @66
	frsqrte f1, f3
	lfd f4, 0x1f8(r30)
	lfd f2, 0x200(r30)
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
	b @67
	@66:
	lfd f0, 0x208(r30)
	fcmpo cr0, f3, f0
	bge @68
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @67
	@68:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @69
	bge @70
	cmpwi r3, 0x0
	beq @71
	b @70
	@69:
	clrlwi. r0, r4, 9
	beq @72
	li r0, 0x1
	b @73
	@72:
	li r0, 0x2
	b @73
	@71:
	clrlwi. r0, r4, 9
	beq @74
	li r0, 0x5
	b @73
	@74:
	li r0, 0x3
	b @73
	@70:
	li r0, 0x4
	@73:
	cmpwi r0, 0x1
	bne @67
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@67:
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x40(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	@65:
	cmplwi r29, 0x0
	beq @17
	stfs f31, roll_grx(r13)
	stfs f30, roll_grz(r13)
	b @17
	@52:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 7, 7
	bne @75
	rlwinm. r0, r3, 0, 14, 14
	bne @17
	lfs f1, 0x20(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	bge @76
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
	@76:
	lfs f1, 0x20(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	ble @17
	li r3, 0xb
	bl marioChgMot
	bl marioSetFallPara
	b @17
	@75:
	rlwinm. r0, r3, 0, 14, 14
	bne @17
	rlwinm r0, r3, 0, 16, 14
	lfs f3, float_neg0p4_8041a878(r2)
	stw r0, 0x0(r31)
	lfs f2, float_neg0p06_8041a87c(r2)
	lwz r0, 0x0(r31)
	lfs f1, float_neg0p04_8041a880(r2)
	oris r0, r0, 0x2
	lfs f0, float_neg0p02_8041a884(r2)
	stw r0, 0x0(r31)
	stfs f3, 0x7c(r31)
	stfs f2, 0x80(r31)
	stfs f1, 0x84(r31)
	stfs f0, 0x88(r31)
	@17:
	psq_l f31, 0x1a8(r1), 0, 0
	lfd f31, 0x1a0(r1)
	psq_l f30, 0x198(r1), 0, 0
	lfd f30, 0x190(r1)
	lwz r31, 0x18c(r1)
	lwz r30, 0x188(r1)
	lwz r0, 0x1b4(r1)
	lwz r29, 0x184(r1)
	mtlr r0
	addi r1, r1, 0x1b0
	blr
}

asm HitEntry* searchUnder2(f32* out, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	lis r5, vec3_802c5760@ha
	lis r4, vec3_802c576c@ha
	stw r0, 0xb4(r1)
	addi r6, r5, vec3_802c5760@l
	addi r5, r4, vec3_802c576c@l
	lfs f0, float_1037_8041a888(r2)
	stw r31, 0xac(r1)
	mr r31, r3
	lwz r0, 0x4(r6)
	lwz r7, 0x0(r6)
	stw r0, 0xc(r1)
	lwz r6, 0x8(r6)
	stfs f2, 0xc(r1)
	lwz r4, 0x0(r5)
	lwz r0, 0xc(r1)
	stw r7, 0x8(r1)
	lwz r3, 0x4(r5)
	stw r0, 0x30(r1)
	lfs f2, float_37_8041a86c(r2)
	lfs f4, 0x30(r1)
	stw r6, 0x10(r1)
	fadds f2, f4, f2
	lwz r0, 0x8(r5)
	stfs f1, 0x8(r1)
	stfs f3, 0x10(r1)
	lwz r7, 0x8(r1)
	lwz r6, 0x10(r1)
	stfs f2, 0x30(r1)
	lwz r5, 0x30(r1)
	stw r7, 0x2c(r1)
	stw r6, 0x34(r1)
	stw r7, 0x44(r1)
	stw r5, 0x48(r1)
	stw r6, 0x4c(r1)
	stw r4, 0x50(r1)
	stw r3, 0x54(r1)
	stw r0, 0x58(r1)
	stfs f0, 0x74(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @1
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x38
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @2
	@1:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @3
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x38
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @2
	@3:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x38
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@2:
	cmplwi r3, 0x0
	bne @4
	li r3, 0x0
	b @5
	@4:
	lwz r0, 0x5c(r1)
	lwz r4, 0x60(r1)
	stw r0, 0x20(r1)
	lwz r0, 0x64(r1)
	lfs f1, 0x20(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x24(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x28(r1)
	cror eq, gt, eq
	bne @6
	lfs f0, float_0p5_8041a7c4(r2)
	b @7
	@6:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@7:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x80(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f3, f1, f0
	lfs f4, 0x24(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x78(r1)
	lwz r0, 0x7c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f0, 0x80(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x20(r1)
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041a7c4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@9:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x90(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x28(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x24(r1)
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041a7c4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@11:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xa0(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0x14
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x28(r1)
	beq @5
	lwz r5, 0x68(r1)
	lwz r4, 0x6c(r1)
	lwz r0, 0x70(r1)
	stw r5, 0x14(r1)
	stw r4, 0x18(r1)
	stw r0, 0x1c(r1)
	@5:
	cmplwi r3, 0x0
	beq @12
	lfs f0, 0x24(r1)
	b @13
	@12:
	lfs f0, float_neg1_8041a7dc(r2)
	@13:
	stfs f0, 0x0(r31)
	lwz r0, 0xb4(r1)
	lwz r31, 0xac(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm HitEntry* marioSearchUnder(void) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stw r31, 0xac(r1)
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r31, r3
	lfs f1, 0x1b8(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @1
	lfs f0, float_0p5_8041a7c4(r2)
	fmuls f1, f1, f0
	@1:
	lwz r0, 0x90(r31)
	lis r3, vec3_802c5754@ha
	addi r5, r3, vec3_802c5754@l
	lwz r7, 0x8c(r31)
	stw r0, 0x24(r1)
	lwz r6, 0x94(r31)
	lfs f0, 0x24(r1)
	lwz r4, 0x0(r5)
	fadds f1, f0, f1
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	lfs f0, float_1000_8041a7a0(r2)
	stfs f1, 0x24(r1)
	lwz r5, 0x24(r1)
	stw r7, 0x20(r1)
	stw r6, 0x28(r1)
	stw r7, 0x38(r1)
	stw r5, 0x3c(r1)
	stw r6, 0x40(r1)
	stw r4, 0x44(r1)
	stw r3, 0x48(r1)
	stw r0, 0x4c(r1)
	stfs f0, 0x68(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @2
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x2c
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @3
	@2:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @4
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x2c
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @3
	@4:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x2c
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@3:
	cmplwi r3, 0x0
	bne @5
	li r3, 0x0
	b @6
	@5:
	lwz r0, 0x50(r1)
	lwz r4, 0x54(r1)
	stw r0, 0x14(r1)
	lwz r0, 0x58(r1)
	lfs f1, 0x14(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x18(r1)
	fcmpo cr0, f1, f0
	stw r0, 0x1c(r1)
	cror eq, gt, eq
	bne @7
	lfs f0, float_0p5_8041a7c4(r2)
	b @8
	@7:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@8:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x78(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f3, f1, f0
	lfs f4, 0x18(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x70(r1)
	lwz r0, 0x74(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x14(r1)
	cror eq, gt, eq
	bne @9
	lfs f0, float_0p5_8041a7c4(r2)
	b @10
	@9:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@10:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x88(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x1c(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x80(r1)
	lwz r0, 0x84(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f0, 0x88(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x18(r1)
	cror eq, gt, eq
	bne @11
	lfs f0, float_0p5_8041a7c4(r2)
	b @12
	@11:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@12:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x98(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0x8
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x90(r1)
	lwz r0, 0x94(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x9c(r1)
	lfd f0, 0x98(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x1c(r1)
	beq @6
	lwz r5, 0x5c(r1)
	lwz r4, 0x60(r1)
	lwz r0, 0x64(r1)
	stw r5, 0x8(r1)
	stw r4, 0xc(r1)
	stw r0, 0x10(r1)
	@6:
	cmplwi r3, 0x0
	beq @13
	lfs f0, 0x18(r1)
	b @14
	@13:
	lfs f0, float_neg3000_8041a870(r2)
	@14:
	stfs f0, 0x1c0(r31)
	lwz r0, 0xb4(r1)
	lwz r31, 0xac(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm BOOL marioChkBero(HitEntry* hit) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl hitGetAttr
	mr r31, r3
	bl marioGetPtr
	rlwinm. r0, r31, 0, 12, 12
	beq @1
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	bne @1
	li r3, 0x0
	b @2
	@1:
	rlwinm. r0, r31, 0, 24, 24
	bne @3
	extrwi r3, r31, 1, 8
	b @2
	@3:
	lhz r0, 0x2e(r3)
	subfic r0, r0, 0x19
	cntlzw r0, r0
	srwi r3, r0, 5
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void clear_hitobj_ride(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	li r0, 0x0
	stw r0, 0x1e4(r3)
	lbz r0, 0x3c(r3)
	cmpwi r0, 0x2
	bne @1
	bl kpaClearHitobjRide
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
	nofralloc
	stwu r1, -0x160(r1)
	mflr r0
	stw r0, 0x164(r1)
	stfd f31, 0x150(r1)
	psq_st f31, 0x158(r1), 0, 0
	stmw r27, 0x13c(r1)
	mr r27, r3
	mr r28, r4
	mr r31, r5
	mr r30, r6
	mr r29, r7
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	lfs f31, 0x0(r29)
	cmplwi r0, 0x14
	beq @1
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 14, 14
	bne @2
	lwz r7, 0x0(r27)
	lis r3, chkFilterAttr2@ha
	lwz r6, 0x4(r27)
	addi r4, r3, chkFilterAttr2@l
	li r5, 0x4
	lis r0, 0x80
	stw r7, 0xd4(r1)
	addi r3, r1, 0xc8
	stw r6, 0xd8(r1)
	lwz r6, 0x8(r27)
	stw r6, 0xdc(r1)
	lwz r7, 0x0(r28)
	lwz r6, 0x4(r28)
	stw r7, 0xe0(r1)
	stw r6, 0xe4(r1)
	lwz r6, 0x8(r28)
	stw r6, 0xe8(r1)
	stfs f31, 0x104(r1)
	stw r5, 0xcc(r1)
	stw r0, 0xd0(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	bne @3
	li r3, 0x0
	b @4
	@3:
	lfs f1, 0x104(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @5
	lfs f0, float_0p5_8041a7c4(r2)
	b @6
	@5:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@6:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x110(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	cmplwi r31, 0x0
	fctiwz f0, f0
	stfd f0, 0x108(r1)
	lwz r0, 0x10c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x114(r1)
	lfd f0, 0x110(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	beq @7
	lwz r4, 0xec(r1)
	lwz r0, 0xf0(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0xf4(r1)
	stw r0, 0x8(r31)
	lfs f1, 0x0(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041a7c4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@9:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x108(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x110(r1)
	lwz r0, 0x114(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x10c(r1)
	lfd f1, 0x108(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r31)
	lfs f1, 0x4(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041a7c4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@11:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x120(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x118(r1)
	lwz r0, 0x11c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x124(r1)
	lfd f1, 0x120(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r31)
	lfs f1, 0x8(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041a7c4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@13:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x130(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x128(r1)
	lwz r0, 0x12c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x134(r1)
	lfd f0, 0x130(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r31)
	@7:
	cmplwi r30, 0x0
	beq @4
	lwz r4, 0xf8(r1)
	lwz r0, 0xfc(r1)
	stw r4, 0x0(r30)
	stw r0, 0x4(r30)
	lwz r0, 0x100(r1)
	stw r0, 0x8(r30)
	b @4
	@2:
	lwz r3, 0x0(r27)
	lwz r0, 0x4(r27)
	stw r3, 0x94(r1)
	stw r0, 0x98(r1)
	lwz r0, 0x8(r27)
	stw r0, 0x9c(r1)
	lwz r3, 0x0(r28)
	lwz r0, 0x4(r28)
	stw r3, 0xa0(r1)
	stw r0, 0xa4(r1)
	lwz r0, 0x8(r28)
	stw r0, 0xa8(r1)
	stfs f31, 0xc4(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @14
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x88
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @15
	@14:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @16
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x88
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @15
	@16:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x88
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@15:
	cmplwi r3, 0x0
	bne @17
	li r3, 0x0
	b @4
	@17:
	lfs f1, 0xc4(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @18
	lfs f0, float_0p5_8041a7c4(r2)
	b @19
	@18:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@19:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x128(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	cmplwi r31, 0x0
	fctiwz f0, f0
	stfd f0, 0x130(r1)
	lwz r0, 0x134(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x12c(r1)
	lfd f0, 0x128(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	beq @20
	lwz r4, 0xac(r1)
	lwz r0, 0xb0(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0xb4(r1)
	stw r0, 0x8(r31)
	lfs f1, 0x0(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @21
	lfs f0, float_0p5_8041a7c4(r2)
	b @22
	@21:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@22:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x128(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x130(r1)
	lwz r0, 0x134(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x12c(r1)
	lfd f1, 0x128(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r31)
	lfs f1, 0x4(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @23
	lfs f0, float_0p5_8041a7c4(r2)
	b @24
	@23:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@24:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x118(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x120(r1)
	lwz r0, 0x124(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x11c(r1)
	lfd f1, 0x118(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r31)
	lfs f1, 0x8(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @25
	lfs f0, float_0p5_8041a7c4(r2)
	b @26
	@25:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@26:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x108(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x110(r1)
	lwz r0, 0x114(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x10c(r1)
	lfd f0, 0x108(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r31)
	@20:
	cmplwi r30, 0x0
	beq @4
	lwz r4, 0xb8(r1)
	lwz r0, 0xbc(r1)
	stw r4, 0x0(r30)
	stw r0, 0x4(r30)
	lwz r0, 0xc0(r1)
	stw r0, 0x8(r30)
	b @4
	@1:
	bl marioGetJabaraState
	cmpwi r3, 0x1
	bne @27
	lwz r7, 0x0(r27)
	lis r3, chkFilterAttr2@ha
	lwz r6, 0x4(r27)
	addi r4, r3, chkFilterAttr2@l
	li r5, 0x4
	lis r0, 0x80
	stw r7, 0x54(r1)
	addi r3, r1, 0x48
	stw r6, 0x58(r1)
	lwz r6, 0x8(r27)
	stw r6, 0x5c(r1)
	lwz r7, 0x0(r28)
	lwz r6, 0x4(r28)
	stw r7, 0x60(r1)
	stw r6, 0x64(r1)
	lwz r6, 0x8(r28)
	stw r6, 0x68(r1)
	stfs f31, 0x84(r1)
	stw r5, 0x4c(r1)
	stw r0, 0x50(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	bne @28
	li r3, 0x0
	b @4
	@28:
	lfs f1, 0x84(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @29
	lfs f0, float_0p5_8041a7c4(r2)
	b @30
	@29:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@30:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x128(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	cmplwi r31, 0x0
	fctiwz f0, f0
	stfd f0, 0x130(r1)
	lwz r0, 0x134(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x12c(r1)
	lfd f0, 0x128(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	beq @31
	lwz r4, 0x6c(r1)
	lwz r0, 0x70(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0x74(r1)
	stw r0, 0x8(r31)
	lfs f1, 0x0(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @32
	lfs f0, float_0p5_8041a7c4(r2)
	b @33
	@32:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@33:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x128(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x130(r1)
	lwz r0, 0x134(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x12c(r1)
	lfd f1, 0x128(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r31)
	lfs f1, 0x4(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @34
	lfs f0, float_0p5_8041a7c4(r2)
	b @35
	@34:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@35:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x118(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x120(r1)
	lwz r0, 0x124(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x11c(r1)
	lfd f1, 0x118(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r31)
	lfs f1, 0x8(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @36
	lfs f0, float_0p5_8041a7c4(r2)
	b @37
	@36:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@37:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x108(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x110(r1)
	lwz r0, 0x114(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x10c(r1)
	lfd f0, 0x108(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r31)
	@31:
	cmplwi r30, 0x0
	beq @4
	lwz r4, 0x78(r1)
	lwz r0, 0x7c(r1)
	stw r4, 0x0(r30)
	stw r0, 0x4(r30)
	lwz r0, 0x80(r1)
	stw r0, 0x8(r30)
	b @4
	@27:
	lwz r3, 0x0(r27)
	lwz r0, 0x4(r27)
	stw r3, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x8(r27)
	stw r0, 0x1c(r1)
	lwz r3, 0x0(r28)
	lwz r0, 0x4(r28)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x8(r28)
	stw r0, 0x28(r1)
	stfs f31, 0x44(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @38
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x8
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @39
	@38:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @40
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x8
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @39
	@40:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x8
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@39:
	cmplwi r3, 0x0
	bne @41
	li r3, 0x0
	b @4
	@41:
	lfs f1, 0x44(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @42
	lfs f0, float_0p5_8041a7c4(r2)
	b @43
	@42:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@43:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x128(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	cmplwi r31, 0x0
	fctiwz f0, f0
	stfd f0, 0x130(r1)
	lwz r0, 0x134(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x12c(r1)
	lfd f0, 0x128(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	beq @44
	lwz r4, 0x2c(r1)
	lwz r0, 0x30(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0x34(r1)
	stw r0, 0x8(r31)
	lfs f1, 0x0(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @45
	lfs f0, float_0p5_8041a7c4(r2)
	b @46
	@45:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@46:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x128(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x130(r1)
	lwz r0, 0x134(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x12c(r1)
	lfd f1, 0x128(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r31)
	lfs f1, 0x4(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @47
	lfs f0, float_0p5_8041a7c4(r2)
	b @48
	@47:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@48:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x118(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x120(r1)
	lwz r0, 0x124(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x11c(r1)
	lfd f1, 0x118(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r31)
	lfs f1, 0x8(r31)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @49
	lfs f0, float_0p5_8041a7c4(r2)
	b @50
	@49:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@50:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x108(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x110(r1)
	lwz r0, 0x114(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x10c(r1)
	lfd f0, 0x108(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r31)
	@44:
	cmplwi r30, 0x0
	beq @4
	lwz r4, 0x38(r1)
	lwz r0, 0x3c(r1)
	stw r4, 0x0(r30)
	stw r0, 0x4(r30)
	lwz r0, 0x40(r1)
	stw r0, 0x8(r30)
	@4:
	stfs f31, 0x0(r29)
	psq_l f31, 0x158(r1), 0, 0
	lfd f31, 0x150(r1)
	lmw r27, 0x13c(r1)
	lwz r0, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x160
	blr
}

asm HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx,
                        f32 dy, f32 dz) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stmw r25, 0xc4(r1)
	lis r11, vec3_802c5730@ha
	lis r10, vec3_802c573c@ha
	addi r26, r11, vec3_802c5730@l
	mr r28, r6
	addi r6, r10, vec3_802c573c@l
	lwz r12, 0x0(r26)
	lwz r11, 0x4(r26)
	mr r25, r3
	lwz r10, 0x8(r26)
	mr r26, r4
	lwz r4, 0x0(r6)
	mr r27, r5
	lwz r3, 0x4(r6)
	mr r29, r7
	lwz r0, 0x8(r6)
	mr r30, r8
	stw r12, 0x14(r1)
	mr r31, r9
	lfs f31, 0x0(r28)
	stw r11, 0x18(r1)
	stw r10, 0x1c(r1)
	stw r4, 0x8(r1)
	stw r3, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f1, 0x14(r1)
	stfs f2, 0x18(r1)
	lwz r7, 0x14(r1)
	stfs f3, 0x1c(r1)
	lwz r6, 0x18(r1)
	stfs f4, 0x8(r1)
	lwz r5, 0x1c(r1)
	stfs f5, 0xc(r1)
	lwz r4, 0x8(r1)
	stfs f6, 0x10(r1)
	lwz r3, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r7, 0x44(r1)
	stw r6, 0x48(r1)
	stw r5, 0x4c(r1)
	stw r4, 0x50(r1)
	stw r3, 0x54(r1)
	stw r0, 0x58(r1)
	stfs f31, 0x74(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @1
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x38
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @2
	@1:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @3
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x38
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @2
	@3:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x38
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@2:
	cmplwi r3, 0x0
	bne @4
	li r3, 0x0
	b @5
	@4:
	lfs f1, 0x74(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_0p5_8041a7c4(r2)
	b @7
	@6:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@7:
	lfs f2, float_1000_8041a7a0(r2)
	lis r5, 0x4330
	lis r4, double_to_int_802c5920@ha
	lwz r0, 0x5c(r1)
	fmadds f0, f2, f1, f0
	addi r6, r4, double_to_int_802c5920@l
	stw r0, 0x2c(r1)
	lwz r4, 0x60(r1)
	fctiwz f0, f0
	lwz r0, 0x64(r1)
	stw r5, 0x80(r1)
	lfd f1, 0x0(r6)
	stfd f0, 0x78(r1)
	lfs f4, 0x2c(r1)
	lwz r5, 0x7c(r1)
	lfs f0, float_0_8041a7a4(r2)
	xoris r5, r5, 0x8000
	stw r4, 0x30(r1)
	fcmpo cr0, f4, f0
	stw r5, 0x84(r1)
	lfd f0, 0x80(r1)
	stw r0, 0x34(r1)
	fsubs f0, f0, f1
	fdivs f31, f0, f2
	cror eq, gt, eq
	bne @8
	lfs f0, float_0p5_8041a7c4(r2)
	b @9
	@8:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@9:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x90(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x30(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x88(r1)
	lwz r0, 0x8c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x94(r1)
	lfd f0, 0x90(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x2c(r1)
	cror eq, gt, eq
	bne @10
	lfs f0, float_0p5_8041a7c4(r2)
	b @11
	@10:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@11:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0xa0(r1)
	fmadds f0, f3, f4, f0
	lfs f4, 0x34(r1)
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f2, f0
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f4, f0
	stfd f2, 0x98(r1)
	lwz r0, 0x9c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xa4(r1)
	lfd f0, 0xa0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f3
	stfs f0, 0x30(r1)
	cror eq, gt, eq
	bne @12
	lfs f0, float_0p5_8041a7c4(r2)
	b @13
	@12:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@13:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f4, f0
	addic. r0, r1, 0x20
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0xa8(r1)
	lwz r0, 0xac(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x34(r1)
	beq @5
	lwz r5, 0x68(r1)
	lwz r4, 0x6c(r1)
	lwz r0, 0x70(r1)
	stw r5, 0x20(r1)
	stw r4, 0x24(r1)
	stw r0, 0x28(r1)
	@5:
	stfs f31, 0x0(r28)
	lfs f1, 0x2c(r1)
	lfs f0, 0x30(r1)
	stfs f1, 0x0(r25)
	lfs f1, 0x34(r1)
	stfs f0, 0x0(r26)
	lfs f0, 0x20(r1)
	stfs f1, 0x0(r27)
	lfs f1, 0x24(r1)
	stfs f0, 0x0(r29)
	lfs f0, 0x28(r1)
	stfs f1, 0x0(r30)
	stfs f0, 0x0(r31)
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	lmw r25, 0xc4(r1)
	lwz r0, 0xf4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stw r31, 0x8c(r1)
	mr r31, r7
	stw r30, 0x88(r1)
	mr r30, r6
	stw r29, 0x84(r1)
	mr r29, r5
	lwz r8, 0x0(r3)
	lwz r0, 0x4(r3)
	stw r8, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x8(r3)
	stw r0, 0x1c(r1)
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x8(r4)
	stw r0, 0x28(r1)
	lfs f0, 0x0(r7)
	stfs f0, 0x44(r1)
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1c
	bne @1
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x8
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b @2
	@1:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq @3
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x8
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b @2
	@3:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x8
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
	@2:
	cmplwi r3, 0x0
	bne @4
	li r3, 0x0
	b @5
	@4:
	lfs f1, 0x44(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_0p5_8041a7c4(r2)
	b @7
	@6:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@7:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x50(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	cmplwi r29, 0x0
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x54(r1)
	lfd f0, 0x50(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x0(r31)
	beq @8
	lwz r4, 0x2c(r1)
	lwz r0, 0x30(r1)
	lfs f0, float_0_8041a7a4(r2)
	stw r4, 0x0(r29)
	stw r0, 0x4(r29)
	lwz r0, 0x34(r1)
	stw r0, 0x8(r29)
	lfs f1, 0x0(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @9
	lfs f0, float_0p5_8041a7c4(r2)
	b @10
	@9:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@10:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x48(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x50(r1)
	lwz r0, 0x54(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x4c(r1)
	lfd f1, 0x48(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x0(r29)
	lfs f1, 0x4(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @11
	lfs f0, float_0p5_8041a7c4(r2)
	b @12
	@11:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@12:
	lfs f3, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	lis r4, double_to_int_802c5920@ha
	stw r0, 0x60(r1)
	fmadds f1, f3, f1, f0
	lfd f2, double_to_int_802c5920@l(r4)
	lfs f0, float_0_8041a7a4(r2)
	fctiwz f1, f1
	stfd f1, 0x58(r1)
	lwz r0, 0x5c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	lfd f1, 0x60(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	stfs f1, 0x4(r29)
	lfs f1, 0x8(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @13
	lfs f0, float_0p5_8041a7c4(r2)
	b @14
	@13:
	lfs f0, float_neg0p5_8041a7c8(r2)
	@14:
	lfs f2, float_1000_8041a7a0(r2)
	lis r0, 0x4330
	stw r0, 0x70(r1)
	lis r4, double_to_int_802c5920@ha
	fmadds f0, f2, f1, f0
	lfd f1, double_to_int_802c5920@l(r4)
	fctiwz f0, f0
	stfd f0, 0x68(r1)
	lwz r0, 0x6c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x8(r29)
	@8:
	cmplwi r30, 0x0
	beq @5
	lwz r4, 0x38(r1)
	lwz r0, 0x3c(r1)
	stw r4, 0x0(r30)
	stw r0, 0x4(r30)
	lwz r0, 0x40(r1)
	stw r0, 0x8(r30)
	@5:
	lwz r0, 0x94(r1)
	lwz r31, 0x8c(r1)
	lwz r30, 0x88(r1)
	lwz r29, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, 0x8
	stw r0, 0x24(r1)
	addi r0, r3, 0x804
	lis r3, vec3_802c5730@ha
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802c5730@l
	stw r29, 0x14(r1)
	mr r29, r4
	lwz r4, 0x4(r4)
	and. r0, r4, r0
	beq @1
	rlwinm. r0, r4, 0, 8, 8
	bne @1
	li r3, 0x0
	b @2
	@1:
	clrrwi. r0, r4, 31
	bne @3
	li r3, 0x1
	b @2
	@3:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	mr r31, r3
	addi r4, r30, 0x274
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	addi r3, r31, 0x15
	addi r4, r30, 0x28c
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	addi r3, r31, 0x15
	addi r4, r30, 0x2a4
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	@4:
	mr r3, r29
	bl mobjHitObjPtrToPtr
	li r3, 0x0
	b @2
	@5:
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

asm BOOL chkfilterVecRoll(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802c5730@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802c5730@l
	stw r29, 0x14(r1)
	mr r29, r4
	lwz r4, 0x4(r4)
	rlwinm. r0, r4, 0, 24, 24
	beq @1
	li r3, 0x1
	b @2
	@1:
	rlwinm. r0, r4, 0, 8, 8
	bne @3
	lis r3, 0x8
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
	addi r4, r30, 0x274
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0x28c
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0x2a4
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

asm BOOL chkfilterVec(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, 0x8
	stw r0, 0x24(r1)
	addi r0, r3, 0x80
	lis r3, vec3_802c5730@ha
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r3, vec3_802c5730@l
	stw r29, 0x14(r1)
	mr r29, r4
	lwz r4, 0x4(r4)
	and. r0, r4, r0
	beq @1
	li r3, 0x1
	b @2
	@1:
	rlwinm. r0, r4, 0, 8, 8
	bne @3
	rlwinm. r0, r4, 0, 29, 29
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
	addi r4, r30, 0x274
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0x28c
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r3, r31, 0x15
	addi r4, r30, 0x2a4
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

asm BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	lwz r5, 0x4(r4)
	li r4, 0x0
	lwz r0, 0x4(r3)
	and. r0, r5, r0
	beq @1
	lwz r0, 0x8(r3)
	and. r0, r5, r0
	beq @2
	@1:
	li r4, 0x1
	@2:
	mr r3, r4
	blr
}

asm void marioHitCheckWidth(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r4, 0x0(r3)
	rlwinm. r0, r4, 0, 11, 11
	bne @1
	rlwinm. r0, r4, 0, 7, 7
	bne @2
	lfs f2, 0x1b4(r3)
	b @3
	@2:
	lfs f2, float_18_8041a850(r2)
	@3:
	lfs f1, 0x1bc(r3)
	lfs f0, float_1_8041a7bc(r2)
	fadds f0, f1, f0
	fcmpo cr0, f0, f2
	stfs f0, 0x1bc(r3)
	ble @4
	stfs f2, 0x1bc(r3)
	b @4
	@1:
	lfs f2, 0x1bc(r3)
	lfs f1, float_6_8041a88c(r2)
	fcmpo cr0, f2, f1
	ble @5
	lfs f0, float_1_8041a7bc(r2)
	fsubs f0, f2, f0
	fcmpo cr0, f0, f1
	stfs f0, 0x1bc(r3)
	bge @5
	stfs f1, 0x1bc(r3)
	@5:
	lfs f2, 0x1bc(r3)
	lfs f1, float_6_8041a88c(r2)
	fcmpo cr0, f2, f1
	bge @4
	lfs f0, float_1_8041a7bc(r2)
	fadds f0, f2, f0
	fcmpo cr0, f0, f1
	stfs f0, 0x1bc(r3)
	ble @4
	stfs f1, 0x1bc(r3)
	@4:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
