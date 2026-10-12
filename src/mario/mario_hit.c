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

extern MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);
extern double sin(double);
extern double cos(double);

#define MF(w, off, T) (*(T*)((u8*)(w) + (off)))

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
extern void marioChkWallAround(Vec* pos, void* p, f32 dx, f32 dz, f32 w, f32 h);

static inline BOOL marioChkBeroSub(s32 attr) {
    if (!(attr & 0x80)) {
        return TRUE;
    }
    return marioGetPtr()->currMotionId == 0x19;
}
extern HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);

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

static inline BOOL marioChkBeroSub2(s32 attr) {
    BOOL r;
    if (!(attr & 0x80)) {
        r = TRUE;
    } else {
        r = marioGetPtr()->currMotionId == 0x19;
    }
    return r;
}

static inline BOOL marioChkBeroSub3(s32 attr) {
    return (attr & 0x80) ? (marioGetPtr()->currMotionId == 0x19) : TRUE;
}

static inline BOOL marioChkBeroSub4(s32 attr) {
    BOOL r = TRUE;
    if (attr & 0x80) {
        r = marioGetPtr()->currMotionId == 0x19;
    }
    return r;
}

static inline BOOL marioChkBeroSub5(HitEntry* hit) {
    s32 attr = hitGetAttr(hit);
    if (!(attr & 0x80)) {
        return TRUE;
    }
    return marioGetPtr()->currMotionId == 0x19;
}

static inline BOOL marioChkBeroSub6(s32 attr) {
    if (attr & 0x80) {
        return marioGetPtr()->currMotionId == 0x19;
    } else {
        return TRUE;
    }
}

void marioHitCheckWidth(void) {
    MarioWork* w = marioGetPtr();
    f32 v;
    if (!(w->flags & 0x100000)) {
        f32 lim = (w->flags & 0x1000000) ? 18.0f : MF(w, 0x1b4, f32);
        v = MF(w, 0x1bc, f32) + 1.0f;
        MF(w, 0x1bc, f32) = v;
        if (v > lim) {
            MF(w, 0x1bc, f32) = lim;
        }
    } else {
        v = MF(w, 0x1bc, f32);
        if (v > 6.0f) {
            v -= 1.0f;
            MF(w, 0x1bc, f32) = v;
            if (v < 6.0f) {
                MF(w, 0x1bc, f32) = 6.0f;
            }
        }
        v = MF(w, 0x1bc, f32);
        if (v < 6.0f) {
            v += 1.0f;
            MF(w, 0x1bc, f32) = v;
            if (v > 6.0f) {
                MF(w, 0x1bc, f32) = 6.0f;
            }
        }
    }
}


BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry) {
    s32 ret = 0;
    s32 attr = entry->attributes;
    if ((attr & query->user0) == 0 || (attr & query->user1) != 0) {
        ret = 1;
    }
    return ret;
}

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
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock") || !strcmp(mobj->animName, "MOBJ_HiddenBadgeBlock") ||
        !strcmp(mobj->animName, "MOBJ_Hidden10CountBlock")) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}

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
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock") || !strcmp(mobj->animName, "MOBJ_HiddenBadgeBlock") ||
        !strcmp(mobj->animName, "MOBJ_Hidden10CountBlock")) {
        mobjHitObjPtrToPtr(entry);
        return FALSE;
    }
    return TRUE;
}

BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj;
    if ((entry->attributes & 0x80804) && !(entry->attributes & 0x800000)) {
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

void clear_hitobj_ride(void) {
    MarioWork* w = marioGetPtr();
    w->hitobjStandOn = NULL;
    if (w->characterId == 2) {
        kpaClearHitobjRide();
    }
}

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

void marioChkToge(void) {
    MarioWork* w = marioGetPtr();
    s32 attr;
    if (vivianGetStatus() == 2 || vivianGetStatus() == 1 || vivianGetStatus() == 3) {
        return;
    }
    if (MF(w, 0x1e0, void*) != NULL) {
        attr = hitGetAttr(MF(w, 0x1e0, HitEntry*));
        if (w->currMotionId != 0x20 && (attr & 0x800) && MF(w, 0x210, f32) < 0.5f * MF(w, 0x1b4, f32)) {
            set_damage_root_ypos(MF(w, 0x90, f32));
            marioChgMot(0x20);
        }
    }
    if (MF(w, 0x1f0, void*) != NULL) {
        attr = hitGetAttr(MF(w, 0x1f0, HitEntry*));
        if (w->currMotionId != 0x20 && (attr & 0x800)) {
            set_damage_root_ypos(MF(w, 0x90, f32));
            marioChgMot(0x20);
        }
    }
    if (MF(w, 0x1f4, void*) != NULL) {
        attr = hitGetAttr(MF(w, 0x1f4, HitEntry*));
        if (w->currMotionId != 0x20 && (attr & 0x800)) {
            set_damage_root_ypos(MF(w, 0x90, f32));
            marioChgMot(0x20);
        }
    }
}

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

HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    return marioHitCheckVecInl(pos, dir, outPos, outNrm, dist);
}

HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx,
                        f32 dy, f32 dz) {
    Vec outPos, outNrm;
    Vec pos = {0.0f, 0.0f, 0.0f};
    Vec dir = {0.0f, 0.0f, 0.0f};
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

void marioSearchUnder(void) {
    Vec pos, outPos, outNrm;
    f32 d = 1000.0f;
    HitEntry* hit;
    f32 h;
    MarioWork* w = marioGetPtr();
    h = MF(w, 0x1b8, f32);
    if (w->flags & 0x1000000) {
        h *= 0.5f;
    }
    pos = w->position;
    pos.y = pos.y + h;
    {
    Vec dir = {0.0f, 0.0f, 0.0f};
    hit = marioHitCheckVecInl(&pos, &dir, &outPos, &outNrm, &d);
    }
    if (hit) {
        MF(w, 0x1c0, f32) = outPos.y;
    } else {
        MF(w, 0x1c0, f32) = -3000.0f;
    }
}

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
    {
    Vec dir = {0.0f, -1.0f, 0.0f};
    hit = marioHitCheckVecInl(&pos2, &dir, &outPos, &outNrm, &d);
    }
    if (hit) {
        *out = outPos.y;
    } else {
        *out = -1.0f;
    }
    return hit;
}

void marioChkGnd2(void) {
    f32 b, y, c;
    HitEntry* hit;
    f32 d;
    MarioWork* w = marioGetPtr();
    if (!(w->flags & 0x10000)) {
        if (w->characterId != 2) {
            hit = marioSearchGround(&y, &b, &c, 0.1f, MF(w, 0x7c, f32));
        } else {
            hit = kpaSearchGround(&y, &b, &c, 0.1f);
        }
        if (hit) {
            d = MF(w, 0x90, f32) - y;
            if (d < 0.0f && d >= -10.0f) {
                w->hitobjStandOn = hit;
                MF(w, 0x90, f32) = y;
                w->flags &= ~0xC0;
                w->airTimer = 0;
                MF(w, 0x52, s16) = 0;
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
    if (!strcmp(mobj->name, "MOBJ_PowerUpBlock") || !strcmp(mobj->name, "MOBJ_SaveBlock") ||
        !strcmp(mobj->name, "MOBJ_RecoveryBlock") || !strcmp(mobj->name, "MOBJ_CoinTakenRecoveryBlock")) {
        return TRUE;
    }
    return FALSE;
}

static inline f32 marioGetHeightInl(void) {
    MarioWork* m = marioGetPtr();
    f32 ph = MF(m, 0x1b8, f32);
    if (m->currMotionId == 0x1a) {
        PartyEntry* p = partyGetPtr(marioGetPartyId());
        if (p) {
            ph = partyGetHeight(p);
        }
    }
    return ph;
}

f32 marioChkOverhead(void) {
    Vec pos;
    HitEntry* hj;
    f32 h;
    MarioWork* w = marioGetPtr();
    if (w->currMotionId == 8) {
        return w->position.y;
    }
    if (w->currMotionId == 0x14) {
        pos = w->position;
        h = MF(w, 0x1b8, f32);
        if (!jabaraNoHitChk()) {
            h += 5.0f;
            MF(w, 0x1f4, HitEntry*) = marioSearchHead_jabara(&pos, &h, &hj, 0.0f);
            if (!MF(w, 0x1f4, HitEntry*)) {
                MF(w, 0x1f4, HitEntry*) = marioSearchHead(&pos, &h, (w->flags & 0x10000) ? MF(w, 0x7c, f32) : 10.0f);
            }
        }
    } else if (w->flags & 0x1000000) {
        pos = w->position;
        MF(w, 0x1f4, HitEntry*) = marioSearchHead_roll(&pos, &h, 40.0f);
    } else {
        f32 d;
        pos = w->position;
        h = MF(w, 0x1b8, f32);
        d = (w->flags & 0x10000) ? MF(w, 0x7c, f32) : 10.0f;
        if (MF(w, 0x3c, s8) == 2) {
            MF(w, 0x1f4, HitEntry*) = kpaSearchHead(&pos, &h, d);
        } else {
            MF(w, 0x1f4, HitEntry*) = marioSearchHead(&pos, &h, d);
        }
    }
    w->position.x = pos.x;
    if (MF(w, 0x1f4, HitEntry*)) {
        if (marioChkHeadBlock(MF(w, 0x1f4, HitEntry*))) {
            MF(w, 0x180, f32) = 0.0f;
            w->flags |= 0x80;
        }
        w->flags |= 0x8000000;
        if (MF(w, 0x3c, s8) == 2) {
            marioItemGetDisable();
            if (!kpaGetBodyStatus()) {
                marioClearJumpPara();
            }
        }
        pos.y = (s32)(10.0f * (pos.y - marioGetHeightInl()) + 0.5f) / 10.0f - 1.0f;
        if (!(w->flags & 0x20000) && pos.y < MF(w, 0x120, f32)) {
            pos.y = MF(w, 0x120, f32);
            if (!(w->flags & 0x1000000) && w->currMotionId != 0x19 && w->currMotionId != 0x18 &&
                w->currMotionId != 0x1c && MF(w, 0x3c, s8) != 2 && !marioChkSlitEnd()) {
                if (MF(w, 0x180, f32) == 0.0f) {
                    if (w->currMotionId != 0) {
                        marioChgStayMotion();
                    }
                } else {
                    marioChgMot(MF(w, 0x180, f32) > MF(w, 0x184, f32) ? 2 : 1);
                }
            }
        }
        if (w->currMotionId == 3 || w->currMotionId == 6) {
            psndSFXOn_3D((const char*)0x156, &w->position);
            marioClearJumpPara();
            w->flags &= ~0xf0000;
            if (MF(w, 0x3c, s8) != 2) {
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
        if (h >= 0.0f && h + MF(w, 0x1b8, f32) <= 47.0f) {
            w->flags |= 0x8000000;
        } else {
            w->flags &= ~0x8000000;
        }
    }
    return pos.y;
}

f32 marioChkOverheadJabara(HitEntry** hitOut, f32* distOut) {
    Vec pos;
    f32 h;
    MarioWork* w;
    w = marioGetPtr();
    *hitOut = NULL;
    *distOut = -1.0f;
    pos = w->position;
    h = MF(w, 0x1b8, f32);
    if (w->currMotionId == 8) {
        return pos.y;
    }
    if (!jabaraNoHitChk()) {
        h += 5.0f;
        MF(w, 0x1f4, HitEntry*) = marioSearchHead_jabara(&pos, &h, hitOut, 0.0f);
        if (!MF(w, 0x1f4, HitEntry*)) {
            h = MF(w, 0x1b8, f32);
            h += 5.0f;
            MF(w, 0x1f4, HitEntry*) = marioSearchHead(&pos, &h, 0.0f);
        }
    }
    w->position.x = pos.x;
    if (MF(w, 0x1f4, HitEntry*)) {
        w->flags |= 0x8000000;
        pos.y = pos.y - MF(w, 0x1b8, f32) - 0.1f;
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

HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d) {
    Vec outPos, outNrm;
    f32 x, z;
    f32 dist;
    f32 base, top;
    f32 a;
    s32 i;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    *h = -1.0f;
    base = MF(w, 0x1b8, f32);
    i = 0;
    top = base + d;
    for (; i < 5; i++) {
        switch (i) {
        case 0:
            z = x = 0.0f;
            break;
        case 1:
            a = (3.1415927f * (90.0f + MF(w, 0x1a0, f32))) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -(f32)cos(a);
            movePos(&x, &z, 3.0f, MF(w, 0x1a0, f32));
            break;
        case 2:
            a = (3.1415927f * (MF(w, 0x1a0, f32) - 90.0f)) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -(f32)cos(a);
            movePos(&x, &z, 3.0f, MF(w, 0x1a0, f32));
            break;
        case 3:
            a = (3.1415927f * (90.0f + MF(w, 0x1a0, f32))) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -(f32)cos(a);
            movePos(&x, &z, 3.0f, 180.0f + MF(w, 0x1a0, f32));
            break;
        case 4:
            a = (3.1415927f * (MF(w, 0x1a0, f32) - 90.0f)) / 180.0f;
            x = 9.0f * (f32)sin(a);
            z = 9.0f * -(f32)cos(a);
            movePos(&x, &z, 3.0f, 180.0f + MF(w, 0x1a0, f32));
            break;
        }
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            Vec dir = {0.0f, 1.0f, 0.0f};
            v.x = pos->x + x;
            v.y = 1.0f + pos->y;
            v.z = pos->z + z;
            dist = top;
            hit = marioHitCheckVecInl(&v, &dir, &outPos, &outNrm, &dist);
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

HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d) {
    Vec v, outPos, outNrm;
    f32 dist;
    f32 base, top, off;
    s32 i;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    *out = NULL;
    i = 0;
    base = *h;
    off = -23.7f;
    *h = -1.0f;
    top = base + d;
    {
    Vec dir = {0.0f, 0.0f, 0.0f};
    for (; i < 8; i++, off += 5.8f) {
        dist = top;
        v.x = pos->x + off * (f32)sin((3.1415927f * MF(w, 0x198, f32)) / 180.0f);
        v.z = pos->z - off * (f32)cos((3.1415927f * MF(w, 0x198, f32)) / 180.0f);
        v.y = 0.5f + pos->y;
        hit = marioHitCheck2(&v, &dir, &outPos, &outNrm, &dist);
        if (hit) {
            if (hitGetAttr(hit) & 0x40000) {
                if (pos->y + base >= outPos.y) {
                    pos->y = outPos.y;
                    *h = 0.0f;
                    if (v.z - pos->z < 0.0f) {
                        *out = (HitEntry*)-1;
                    } else {
                        *out = (HitEntry*)1;
                    }
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
        MF(w, 0x19c, f32) = MF(w, 0x1cc, f32);
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
    hit = searchFrontWall(&pos, &h, dx, dz, MF(w, 0x1bc, f32));
    if (hit) {
        if (MF(w, 0x20c, HitEntry*)) {
            MF(w, 0x1e0, HitEntry*) = MF(w, 0x20c, HitEntry*);
        } else {
            MF(w, 0x1e0, HitEntry*) = hit;
        }
        if (marioChkBero(hit)) {
            if (dx) {
                MF(w, 0x1ec, HitEntry*) = hit;
                MF(w, 0x1f0, HitEntry*) = hit;
            }
            movePos(&w->position.x, &w->position.z, dx, dz);
        } else {
            MF(w, 0x210, f32) = h;
            MF(w, 0x1f0, HitEntry*) = hit;
            if (++MF(w, 0x3f, s8) >= 20) {
                MF(w, 0x3f, s8) = 20;
                if (marioChkBeroSub(hitGetAttr(hit))) {
                    MF(w, 0x1ec, HitEntry*) = hit;
                }
            }
            w->position = pos;
        }
    } else {
        w->position = pos;
    }
    marioChkWallAround(&w->position, NULL, dx, dz, MF(w, 0x1bc, f32), MF(w, 0x1b8, f32));
    dou10_yoko_yari(&MF(w, 0x210, f32));
}

void marioSearchFrontWall_staying(f32 dz) {
    Vec pos;
    f32 h;
    f32 h2;
    f32 ang;
    f32 r;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    MF(w, 0x3f, s8) = 0;
    r = 0.5f * MF(w, 0x1b4, f32);
    if (w->flags & 0x100000) {
        r = 0.0f;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, r, MF(w, 0x1a0, f32) - MF(w, 0x198, f32), MF(w, 0x1bc, f32));
    if (w->currMotionId != 0x13) {
        MF(w, 0x1e0, HitEntry*) = hit;
    } else {
        MF(w, 0x1e0, HitEntry*) = NULL;
    }
    if (!hit) {
        f32 a = toMovedir(MF(w, 0x1a8, f32));
        pos = w->position;
        hit = searchFrontWall(&pos, &h, r, a, MF(w, 0x1bc, f32));
        if (w->currMotionId != 0x13) {
            MF(w, 0x1e0, HitEntry*) = hit;
        } else {
            MF(w, 0x1e0, HitEntry*) = NULL;
        }
    } else if (!strcmp(gp->currentMapName, "dou_10") && vivianGetStatus() != 2 && vivianGetStatus() != 1 && vivianGetStatus() != 3) {
        ang = toMovedir(MF(w, 0x1a8, f32));
        pos = w->position;
        movePos(&pos.x, &pos.z, 0.5f * MF(w, 0x1b4, f32), ang);
        ang += 180.0f;
        hit = searchFrontWall(&pos, &h2, MF(w, 0x1b4, f32), ang, MF(w, 0x1bc, f32));
        if (hit && MF(w, 0x1b4, f32) >= h2) {
            MF(w, 0x1e0, HitEntry*) = hit;
            h = 0.5f * h2;
        }
    }
    if (MF(w, 0x1e0, HitEntry*)) {
        MF(w, 0x210, f32) = h;
    }
    if (MF(w, 0x248, u16) & 0x100) {
        MF(w, 0x1dc, HitEntry*) = NULL;
        pos = w->position;
        if (searchFrontWall(&pos, &h, r, MF(w, 0x1a0, f32), MF(w, 0x1bc, f32))) {
            MF(w, 0x1dc, HitEntry*) = MF(w, 0x1e0, HitEntry*);
        }
    }
    pos = w->position;
    marioChkWallAround(&pos, NULL, 0.0f, dz, MF(w, 0x1bc, f32), MF(w, 0x1b8, f32));
    w->position.x = pos.x;
    w->position.z = pos.z;
}

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
    toMovedir(MF(w, 0x1a8, f32));
    hit = MF(w, 0x1e0, HitEntry*);
    if (hit) {
        return hit;
    }
    pos = w->position;
    if (!strcmp(gp->currentMapName, "dou_10") && vivianGetStatus() != 2 && vivianGetStatus() != 1 && vivianGetStatus() != 3 && !hit) {
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
            MF(w, 0x1e0, HitEntry*) = hit;
            *out = 0.8f;
        }
        pos = w->position;
        hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            MF(w, 0x1e0, HitEntry*) = hit;
            *out = 0.8f;
        }
        pos = w->position;
        movePos(&pos.x, &pos.z, step, 270.0f);
        hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            MF(w, 0x1e0, HitEntry*) = hit;
            *out = 0.8f;
        }
        pos = w->position;
        movePos(&pos.x, &pos.z, step, 90.0f);
        hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
        if (hit && (hitGetAttr(hit) & 0x800)) {
            MF(w, 0x1e0, HitEntry*) = hit;
            *out = 0.8f;
        }
    }
    return hit;
}

HitEntry* dou10_yoko_yari2(f32* out) {
    Vec pos, pos2, outPos, outNrm;
    f32 h;
    f32 d;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    toMovedir(MF(w, 0x1a8, f32));
    pos = w->position;
    if (strcmp(gp->currentMapName, "dou_10")) {
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
        MF(w, 0x1e0, HitEntry*) = hit;
        *out = 0.8f;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
    if (hit && (hitGetAttr(hit) & 0x800)) {
        MF(w, 0x1e0, HitEntry*) = hit;
        *out = 0.8f;
    }
    pos = w->position;
    movePos(&pos.x, &pos.z, 8.0f, 270.0f);
    hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
    if (hit && (hitGetAttr(hit) & 0x800)) {
        MF(w, 0x1e0, HitEntry*) = hit;
        *out = 0.8f;
    }
    pos = w->position;
    movePos(&pos.x, &pos.z, 8.0f, 90.0f);
    hit = searchFrontWall(&pos, &h, 20.0f, 0.0f, 20.0f);
    if (hit && (hitGetAttr(hit) & 0x800)) {
        MF(w, 0x1e0, HitEntry*) = hit;
        *out = 0.8f;
    }
    return hit;
}

HitEntry* N_dou10_yoko_yari3(void) {
    HitCheckQuery query;
    f32 s, c;
    f32 x, z;
    f32 y;
    HitEntry* hit;
    MarioWork* w = marioGetPtr();
    if (strcmp(gp->currentMapName, "dou_10")) {
        return NULL;
    }
    x = w->position.x;
    y = w->position.y;
    z = w->position.z;
    movePos(&x, &z, 10.0f, MF(w, 0x1a0, f32));
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
        MF(w, 0x1e0, HitEntry*) = hit;
        return hit;
    }
    x = w->position.x;
    y = w->position.y;
    z = w->position.z;
    movePos(&x, &z, -10.0f, MF(w, 0x1a0, f32));
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
        MF(w, 0x1e0, HitEntry*) = hit;
    }
    return hit;
}

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
        MF(w, 0x19c, f32) = MF(w, 0x1cc, f32);
    }
    if (!dx) {
        marioSearchFrontWall_staying(dz);
        return;
    }
    pos = w->position;
    hit = searchFrontWall(&pos, &h, dx, dz, MF(w, 0x1bc, f32));
    if (hit) {
        MF(w, 0x1e0, HitEntry*) = hit;
        if (marioChkBeroInl(hit)) {
            if (dx) {
                MF(w, 0x1ec, HitEntry*) = hit;
                MF(w, 0x1f0, HitEntry*) = hit;
            }
            movePos(&w->position.x, &w->position.z, dx, dz);
            pos = w->position;
            return;
        }
        if (!dx) {
            MF(w, 0x3f, s8) = 0;
        } else {
            MF(w, 0x210, f32) = h;
            MF(w, 0x1f0, HitEntry*) = hit;
            if (++MF(w, 0x3f, s8) >= 20) {
                MF(w, 0x3f, s8) = 20;
                if (marioChkBeroSub4(hitGetAttr(hit))) {
                    MF(w, 0x1ec, HitEntry*) = hit;
                }
            }
        }
        w->position = pos;
    }
    old = pos;
    w->position = pos;
    tmp = pos;
    marioChkWallAround(&w->position, NULL, dx, dz, MF(w, 0x1bc, f32), 4.0f);
    max = MF(w, 0x188, f32);
    PSVECSubtract(&w->position, &old, &diff);
    mag = PSVECMag(&diff);
    if (mag > max) {
        PSVECScale(&diff, &diff, max / mag);
        PSVECAdd(&old, &diff, &w->position);
    }
}

