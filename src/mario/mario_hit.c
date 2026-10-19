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
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_802c5730[3];
__declspec(section ".rodata") extern const f32 vec3_802c573c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5748[3];
__declspec(section ".rodata") extern const f32 vec3_802c5754[3];
__declspec(section ".rodata") extern const f32 vec3_802c5760[3];
__declspec(section ".rodata") extern const f32 vec3_802c576c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5778[3];
__declspec(section ".rodata") extern const f32 vec3_802c5784[3];
__declspec(section ".rodata") extern const f32 vec3_802c5790[3];
__declspec(section ".rodata") extern const f32 vec3_802c579c[3];
__declspec(section ".rodata") extern const f32 vec3_802c57a8[3];
__declspec(section ".rodata") extern const f32 vec3_802c57b4[3];
__declspec(section ".rodata") extern const f32 vec3_802c57c0[3];
__declspec(section ".rodata") extern const f32 vec3_802c57cc[3];
__declspec(section ".rodata") extern const f32 vec3_802c57d8[3];
__declspec(section ".rodata") extern const f32 vec3_802c57e4[3];
__declspec(section ".rodata") extern const f32 vec3_802c57f0[3];
__declspec(section ".rodata") extern const f32 vec3_802c57fc[3];
__declspec(section ".rodata") extern const f32 vec3_802c5808[3];
__declspec(section ".rodata") extern const f32 vec3_802c5814[3];
__declspec(section ".rodata") extern const f32 vec3_802c5820[3];
__declspec(section ".rodata") extern const f32 vec3_802c582c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5838[3];
__declspec(section ".rodata") extern const f32 vec3_802c5844[3];
__declspec(section ".rodata") extern const f32 vec3_802c5850[3];
__declspec(section ".rodata") extern const f32 vec3_802c585c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5868[3];
__declspec(section ".rodata") extern const f32 vec3_802c5874[3];
__declspec(section ".rodata") extern const f32 vec3_802c5880[3];
__declspec(section ".rodata") extern const f32 vec3_802c588c[3];
__declspec(section ".rodata") extern const f32 vec3_802c5898[3];
__declspec(section ".rodata") extern const f32 vec3_802c58a4[3];
__declspec(section ".rodata") extern const f32 vec3_802c58b0[3];
__declspec(section ".rodata") extern const f32 vec3_802c58bc[3];
__declspec(section ".rodata") extern const f32 vec3_802c58c8[3];
__declspec(section ".rodata") extern const f32 vec3_802c58d4[3];
__declspec(section ".rodata") extern const f32 vec3_802c58e0[3];
__declspec(section ".rodata") extern const f32 vec3_802c58ec[3];
__declspec(section ".rodata") extern const f32 vec3_802c58f8[3];
__declspec(section ".rodata") extern const f32 vec3_802c5904[3];
__declspec(section ".rodata") extern const f32 vec3_802c5910[3];
__declspec(section ".rodata") extern const f64 double_to_int_802c5920;
__declspec(section ".rodata") extern const f64 double_0p5_802c5928;
__declspec(section ".rodata") extern const f64 double_3_802c5930;
__declspec(section ".rodata") extern const f64 double_0_802c5938;
__declspec(section ".rodata") extern const u32 gap_04_802C59EC_rodata;
__declspec(section ".sdata2") extern const f32 float_1000_8041a7a0;
__declspec(section ".sdata2") extern const f32 float_0_8041a7a4;
__declspec(section ".sdata2") extern const f32 float_4_8041a7a8;
__declspec(section ".sdata2") extern const f32 float_11_8041a7ac;
__declspec(section ".sdata2") extern const f32 float_13_8041a7b0;
__declspec(section ".sdata2") extern const f32 float_45_8041a7b4;
__declspec(section ".sdata2") extern const f32 float_5_8041a7b8;
__declspec(section ".sdata2") extern const f32 float_1_8041a7bc;
__declspec(section ".sdata2") extern const f32 float_360_8041a7c0;
__declspec(section ".sdata2") extern const f32 float_0p5_8041a7c4;
__declspec(section ".sdata2") extern const f32 float_neg0p5_8041a7c8;
__declspec(section ".sdata2") extern const f32 float_180_8041a7cc;
__declspec(section ".sdata2") extern const f32 float_0p125_8041a7d0;
__declspec(section ".sdata2") extern const f32 float_0p25_8041a7d4;
__declspec(section ".sdata2") extern const f32 float_0p75_8041a7d8;
__declspec(section ".sdata2") extern const f32 float_neg1_8041a7dc;
__declspec(section ".sdata2") extern const f32 float_3p1416_8041a7e0;
__declspec(section ".sdata2") extern const f32 float_0p1_8041a7e4;
__declspec(section ".sdata2") extern const f32 float_2_8041a7e8;
__declspec(section ".sdata2") extern const f32 float_18p5_8041a7ec;
__declspec(section ".sdata2") extern const f32 float_3_8041a7f0;
__declspec(section ".sdata2") extern const f32 float_0p265_8041a7f4;
__declspec(section ".sdata2") extern const f32 float_100_8041a7f8;
__declspec(section ".sdata2") extern const f32 float_10_8041a7fc;
__declspec(section ".sdata2") extern const f32 float_40_8041a800;
__declspec(section ".sdata2") extern const f32 float_neg10_8041a804;
__declspec(section ".sdata2") extern const f32 float_60_8041a808;
__declspec(section ".sdata2") extern const f32 float_0p8_8041a80c;
__declspec(section ".sdata2") extern const f32 float_20_8041a810;
__declspec(section ".sdata2") extern const f32 float_8_8041a814;
__declspec(section ".sdata2") extern const f32 float_270_8041a818;
__declspec(section ".sdata2") extern const f32 float_90_8041a81c;
__declspec(section ".sdata2") extern const f32 float_27p75_8041a820;
__declspec(section ".sdata2") extern const f32 float_12_8041a824;
__declspec(section ".sdata2") extern const f32 float_7_8041a828;
__declspec(section ".sdata2") extern const f32 float_30_8041a82c;
__declspec(section ".sdata2") extern const f32 float_16p8_8041a830;
__declspec(section ".sdata2") extern const f32 float_neg23p7_8041a834;
__declspec(section ".sdata2") extern const f32 float_5p8_8041a838;
__declspec(section ".sdata2") extern const f32 float_9_8041a83c;
__declspec(section ".sdata2") extern const f32 float_75_8041a840;
__declspec(section ".sdata2") extern const f32 float_50_8041a844;
__declspec(section ".sdata2") extern const f32 float_0p05_8041a848;
__declspec(section ".sdata2") extern const f32 float_47_8041a84c;
__declspec(section ".sdata2") extern const f32 float_18_8041a850;
__declspec(section ".sdata2") extern const f32 float_0p01_8041a854;
__declspec(section ".sdata2") extern const f32 float_neg10000_8041a858;
__declspec(section ".sdata2") extern const f32 float_8p64_8041a85c;
__declspec(section ".sdata2") extern const f32 float_105_8041a860;
__declspec(section ".sdata2") extern const f32 float_0p425_8041a864;
__declspec(section ".sdata2") extern const f32 float_0p375_8041a868;
__declspec(section ".sdata2") extern const f32 float_37_8041a86c;
__declspec(section ".sdata2") extern const f32 float_neg3000_8041a870;
__declspec(section ".sdata2") extern const f32 float_5000_8041a874;
__declspec(section ".sdata2") extern const f32 float_neg0p4_8041a878;
__declspec(section ".sdata2") extern const f32 float_neg0p06_8041a87c;
__declspec(section ".sdata2") extern const f32 float_neg0p04_8041a880;
__declspec(section ".sdata2") extern const f32 float_neg0p02_8041a884;
__declspec(section ".sdata2") extern const f32 float_1037_8041a888;
__declspec(section ".sdata2") extern const f32 float_6_8041a88c;
#define EXT_LIT(sym, val) (sym)

#endif
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

static const Vec zv0 = {0.0f, 0.0f, 0.0f};
static const Vec zv1 = {0.0f, 0.0f, 0.0f};

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
#ifdef NONMATCHING
static inline s32 hit_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 hit_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (hit_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

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

static inline f32 marioHitNrmAnglePtr(Vec* nrm) {
    MarioWork* mp = marioGetPtr();
    MF(mp, 0x218, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nrm->z, 100.0f * nrm->y) - 180.0f) + 0.5f) / 100.0f;
    MF(mp, 0x21c, f32) = 0.0f;
    MF(mp, 0x220, f32) = (s32)(100.0f * (angleABf(0.0f, 0.0f, 100.0f * nrm->x, 100.0f * nrm->y) - 180.0f) + 0.5f) / 100.0f;
    return angleABf(0.0f, 0.0f, hit_sqrtf(nrm->x * nrm->x + nrm->z * nrm->z), -nrm->y);
}

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
#ifndef NONMATCHING
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
int marioGetJabaraState();
s32 marioGetPartyId(void);
s32 psndSFXOn_3D(const char* name, Vec* position);
int strcmp(const char *s1, const char *s2);
extern BOOL chkBalloon(HitEntry* hit);
extern HitEntry* kpaChkHitobjRide(void);
extern s32 kpaGetBodyStatus(void);
extern s32 kpaGetStageViewType(void);
extern HitEntry* kpaSearchHead(Vec* pos, f32* h, f32 d);
extern BOOL marioChgMotSub(s32 mot, s32 a);
extern void marioChgStayMotion(void);
extern HitEntry* marioChkFrontStep(f32* y, f32* b, f32* c);
extern BOOL marioChkShipMoveMode(void);
extern BOOL marioChkSlitEnd(void);
extern void marioClearJumpPara(void);
extern HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d);
extern void marioSetFallPara(void);
extern void marioShipChgFall(void);
extern void marioUpdateCamCollision(Vec pos);
extern f32 partyGetHeight(PartyEntry* p);
extern void roll_upstairs_on(void);
void marioHitCheckWidth(void);
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
#ifndef NONMATCHING
BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry);
#endif

#ifdef NONMATCHING
static inline HitEntry* marioHitCheckVecInl(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    HitCheckQuery query;
    HitEntry* hit;
    f32 rf;
#endif
#ifndef NONMATCHING
BOOL chkfilterVec(HitCheckQuery* query, HitEntry* entry);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
BOOL chkfilterVecRoll(HitCheckQuery* query, HitEntry* entry);
#endif

#ifdef NONMATCHING
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    return marioHitCheckVecInl(pos, dir, outPos, outNrm, dist);
}
#endif
#ifndef NONMATCHING
BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry);


HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
#endif

HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx,
#ifdef NONMATCHING
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
#ifndef NONMATCHING
                        f32 dy, f32 dz);
#endif

#ifdef NONMATCHING
static inline HitEntry* marioHitCheckAttr2Inl(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
    HitCheckQuery query;
    HitEntry* hit;
    f32 rf;
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
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
#ifndef NONMATCHING
void clear_hitobj_ride(void);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
BOOL marioChkBero(HitEntry* hit);
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
#ifndef NONMATCHING
HitEntry* marioSearchUnder(void);
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
#ifndef NONMATCHING
HitEntry* searchUnder2(f32* out, f32 x, f32 y, f32 z);
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
#ifndef NONMATCHING
void marioChkGnd(void);
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
#ifndef NONMATCHING
void marioChkGnd2(void);
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
#ifndef NONMATCHING
HitEntry* marioSearchGround(f32* y, f32* b, f32* c, f32 spd, f32 h);
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
#ifndef NONMATCHING
__declspec(section ".data") static void* jumptable_8030E5C0[] = {
    (char*)marioSearchGroundRoll + 0x170,
    (char*)marioSearchGroundRoll + 0x180,
    (char*)marioSearchGroundRoll + 0x1D4,
    (char*)marioSearchGroundRoll + 0x228,
    (char*)marioSearchGroundRoll + 0x24C,
    (char*)marioSearchGroundRoll + 0x25C,
    (char*)marioSearchGroundRoll + 0x2C4,
};
HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h);
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
#ifndef NONMATCHING
void marioChkToge(void);
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
#ifndef NONMATCHING
HitEntry* marioChkLandon(f32* a, f32 d);
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
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
HitEntry* marioLandonChk_old(f32* outY, f32 spd);
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
#ifndef NONMATCHING
HitEntry* marioChkLandon2(f32* y, f32 spd, f32 ofs);
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
#ifndef NONMATCHING
f32 marioChkOverhead(void);
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
#ifndef NONMATCHING
f32 marioChkOverheadJabara(HitEntry** hitOut, f32* distOut);
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
#ifndef NONMATCHING
HitEntry* marioSearchHead(Vec* pos, f32* h, f32 dd);
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
#ifndef NONMATCHING
HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d);
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
#ifndef NONMATCHING
HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d);
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
#ifndef NONMATCHING
void marioCheckWall(f32 dx, f32 dz);
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
#ifndef NONMATCHING
void marioSearchFrontWall_staying(f32 dz);
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
#ifndef NONMATCHING
void marioCheckWall_roll(f32 dx, f32 dz);
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
#ifndef NONMATCHING
HitEntry* marioChkFront(f32* out, Vec* pos, f32 angle, f32 dist);
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
#endif
#ifndef NONMATCHING
HitEntry* searchFrontWall(Vec* pos, f32* h, f32 dx, f32 dz, f32 w);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
HitEntry* dou10_yoko_yari(f32* out);
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
#ifndef NONMATCHING
HitEntry* dou10_yoko_yari2(f32* out);
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
#ifndef NONMATCHING
HitEntry* N_dou10_yoko_yari3(void);
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
#ifndef NONMATCHING
HitEntry* marioChkFrontStep(f32* y, f32* h, f32* ang);
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
#endif
#ifndef NONMATCHING
BOOL marioChkWallAround(Vec* pos, void* p, f32 unused, f32 dir, f32 w, f32 h);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
BOOL marioSlitChkWallAround(void);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
void marioCheckWallShip(f32 dx, f32 dz);
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
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
f32 marioChkOverhead(void) {
	char _af_pad[36];
	asm volatile {
		lis r3, vec3_802c5730@ha
		addi r30, r3, vec3_802c5730@l
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0xA003002E
		opword 0x28000008
		opword 0x4082000C
		opword 0xC03F0090
		opword 0x4800041C
		opword 0x28000014
		opword 0x40820090
		opword 0x807F008C
		opword 0x801F0090
		stw r3, _af_pad+8(r1)
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC01F01B8
		opword 0xD0010008
		bl jabaraNoHitChk
		opword 0x2C030000
		opword 0x40820108
		opword 0xC0410008
		opword 0x38610010
		lfs f0, float_5_8041a7b8(r2)
		opword 0x38810008
		lfs f1, float_0_8041a7a4(r2)
		opword 0x38A1000C
		opword 0xEC02002A
		opword 0xD0010008
		bl marioSearchHead_jabara
		opword 0x907F01F4
		opword 0x801F01F4
		opword 0x28000000
		opword 0x408200D4
		opword 0x801F0000
		opword 0x38610010
		opword 0x38810008
		opword 0x540003DF
		opword 0x4182000C
		opword 0xC03F007C
		opword 0x48000008
		lfs f1, float_10_8041a7fc(r2)
		bl marioSearchHead
		opword 0x907F01F4
		opword 0x480000A8
		opword 0x801F0000
		opword 0x540001CF
		opword 0x41820034
		opword 0x80BF008C
		opword 0x38610010
		opword 0x801F0090
		opword 0x38810008
		lfs f1, float_40_8041a800(r2)
		opword 0x90A10010
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		bl marioSearchHead_roll
		opword 0x907F01F4
		opword 0x4800006C
		opword 0x807F008C
		opword 0x801F0090
		opword 0x90610010
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC01F01B8
		opword 0xD0010008
		opword 0x801F0000
		opword 0x540003DF
		opword 0x4182000C
		opword 0xC03F007C
		opword 0x48000008
		lfs f1, float_10_8041a7fc(r2)
		opword 0x881F003C
		opword 0x2C000002
		opword 0x40820018
		opword 0x38610010
		opword 0x38810008
		bl kpaSearchHead
		opword 0x907F01F4
		opword 0x48000014
		opword 0x38610010
		opword 0x38810008
		bl marioSearchHead
		opword 0x907F01F4
		opword 0xC0010010
		opword 0xD01F008C
		lwz r29, 0x1f4(r31)
		opword 0x281D0000
		opword 0x4182023C
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000084
		opword 0x7FA3EB78
		bl hitGetAttr
		opword 0x54600001
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800006C
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x7C7D1B78
		opword 0x389E0220
		opword 0x387D0015
		bl strcmp
		opword 0x2C030000
		opword 0x41820040
		opword 0x387D0015
		opword 0x389E0234
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387D0015
		opword 0x389E0244
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387D0015
		opword 0x389E0258
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820018
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD01F0180
		opword 0x801F0000
		opword 0x60000080
		opword 0x901F0000
		opword 0x801F0000
		opword 0x64000800
		opword 0x901F0000
		opword 0x881F003C
		opword 0x2C000002
		opword 0x40820018
		bl marioItemGetDisable
		bl kpaGetBodyStatus
		opword 0x2C030000
		opword 0x40820008
		bl marioClearJumpPara
		bl marioGetPtr
		opword 0xA003002E
		lfs f31, 0x1b8(r3)
		opword 0x2800001A
		opword 0x4082001C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x4182000C
		bl partyGetHeight
		opword 0xFFE00890
		opword 0xC0010014
		opword 0x3C004330
		lfs f3, float_10_8041a7fc(r2)
		opword 0xEC20F828
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x90010028
		opword 0xC85E01F0
		opword 0xEC23007A
		lfs f0, float_1_8041a7bc(r2)
		opword 0xFC20081E
		opword 0xD8210020
		opword 0x80010024
		opword 0x6C008000
		opword 0x9001002C
		opword 0xC8210028
		opword 0xEC211028
		opword 0xEC211824
		opword 0xEC010028
		opword 0xD0010014
		opword 0x807F0000
		opword 0x5460039D
		opword 0x40820090
		opword 0xC03F0120
		opword 0xFC000840
		opword 0x40800084
		opword 0x546001CF
		opword 0xD0210014
		opword 0x40820078
		opword 0xA01F002E
		opword 0x28000019
		opword 0x4182006C
		opword 0x28000018
		opword 0x41820064
		opword 0x2800001C
		opword 0x4182005C
		opword 0x881F003C
		opword 0x2C000002
		opword 0x41820050
		bl marioChkSlitEnd
		opword 0x2C030000
		opword 0x40820044
		lfs f0, float_0_8041a7a4(r2)
		opword 0xC03F0180
		opword 0xFC000800
		opword 0x40820018
		opword 0xA01F002E
		opword 0x28000000
		opword 0x41820028
		bl marioChgStayMotion
		opword 0x48000020
		opword 0xC01F0184
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38600002
		opword 0x48000008
		opword 0x38600001
		bl marioChgMot
		opword 0xA01F002E
		opword 0x28000003
		opword 0x4182000C
		opword 0x28000006
		opword 0x408200D4
		opword 0x389F008C
		opword 0x38600156
		bl psndSFXOn_3D
		bl marioClearJumpPara
		opword 0x801F0000
		opword 0x54000416
		opword 0x901F0000
		opword 0x881F003C
		opword 0x2C000002
		opword 0x41820010
		opword 0x3860000A
		bl marioChgMot
		bl marioSetFallPara
		opword 0xC0010014
		opword 0xD01F0090
		opword 0x48000094
		opword 0x807F0000
		opword 0x546001CF
		opword 0x40820044
		opword 0xC0210008
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820020
		lfs f0, float_5_8041a7b8(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820010
		opword 0x64600800
		opword 0x901F0000
		opword 0x48000058
		opword 0x801F0000
		opword 0x54000146
		opword 0x901F0000
		opword 0x48000048
		opword 0xC0410008
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC020040
		opword 0x4C411382
		opword 0x40820028
		opword 0xC03F01B8
		lfs f0, float_47_8041a84c(r2)
		opword 0xEC22082A
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820010
		opword 0x64600800
		opword 0x901F0000
		opword 0x48000010
		opword 0x801F0000
		opword 0x54000146
		opword 0x901F0000
		opword 0xC0210014
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
f32 marioChkOverheadJabara(HitEntry** hitOut, f32* distOut) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0x93E1002C
		opword 0x93C10028
		opword 0x7C9E2378
		opword 0x93A10024
		opword 0x7C7D1B78
		bl marioGetPtr
		opword 0x38000000
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0x901D0000
		opword 0x7C7F1B78
		opword 0xD01E0000
		opword 0x8063008C
		opword 0x801F0090
		opword 0x9061000C
		opword 0x90010010
		opword 0x801F0094
		opword 0x90010014
		opword 0xC01F01B8
		opword 0xD0010008
		opword 0xA01F002E
		opword 0x28000008
		opword 0x4082000C
		opword 0xC0210010
		opword 0x480000EC
		bl jabaraNoHitChk
		opword 0x2C030000
		opword 0x4082005C
		opword 0xC0410008
		opword 0x7FA5EB78
		lfs f0, float_5_8041a7b8(r2)
		opword 0x3861000C
		lfs f1, float_0_8041a7a4(r2)
		opword 0x38810008
		opword 0xEC02002A
		opword 0xD0010008
		bl marioSearchHead_jabara
		opword 0x907F01F4
		opword 0x801F01F4
		opword 0x28000000
		opword 0x40820028
		opword 0xC05F01B8
		opword 0x3861000C
		lfs f0, float_5_8041a7b8(r2)
		opword 0x38810008
		lfs f1, float_0_8041a7a4(r2)
		opword 0xEC02002A
		opword 0xD0010008
		bl marioSearchHead
		opword 0x907F01F4
		opword 0xC001000C
		opword 0xD01F008C
		opword 0x801F01F4
		opword 0x28000000
		opword 0x41820040
		opword 0x801F0000
		lfs f0, float_0p1_8041a7e4(r2)
		opword 0x64000800
		opword 0x901F0000
		opword 0xC0410010
		opword 0xC03F01B8
		opword 0xEC220828
		opword 0xEC010028
		opword 0xD0010010
		opword 0xA01F002E
		opword 0x28000003
		opword 0x40820040
		opword 0x38600000
		bl marioChgMot
		opword 0x48000034
		opword 0xC0210008
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x40810018
		opword 0xD03E0000
		opword 0x801F0000
		opword 0x64000800
		opword 0x901F0000
		opword 0x48000010
		opword 0x801F0000
		opword 0x54000146
		opword 0x901F0000
		opword 0xC0210010
		opword 0x80010034
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x83A10024
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioSearchHead(Vec* pos, f32* h, f32 dd) {
	char _af_pad[100];
	asm volatile {
		opword 0xFEC00890
		lis r5, vec3_802c5730@ha
		opword 0x7C7A1B78
		opword 0x7C9B2378
		addi r30, r5, vec3_802c5730@l
		bl marioGetPtr
		opword 0x7C7F1B78
		lfs f0, float_0_8041a7a4(r2)
		opword 0xC0230180
		opword 0xFC010000
		opword 0x4182000C
		opword 0xC03F01A0
		opword 0x4800000C
		opword 0xC03F01A8
		bl toMovedir
		lfs f2, float_3p1416_8041a7e0(r2)
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEEE10024
		opword 0xFC20B890
		bl sin
		lfs f2, float_0p5_8041a7c4(r2)
		opword 0xFC600818
		opword 0xC01F01B4
		opword 0xFC20B890
		opword 0xEC001028
		opword 0xEC0000F2
		opword 0xEF220032
		bl cos
		opword 0xFC200818
		opword 0xC2FB0000
		lfs f3, float_0p5_8041a7c4(r2)
		opword 0xFF60C850
		opword 0xC01F01B4
		opword 0xEED7B02A
		opword 0xEC401828
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0xFC200850
		opword 0x3B800000
		opword 0xEF4305F2
		opword 0xD01B0000
		opword 0xEC020072
		opword 0xEF030032
		opword 0xFF80C050
		opword 0x2C1C0000
		opword 0x40820010
		lfs f21, float_0_8041a7a4(r2)
		opword 0xFE80A890
		opword 0x48000050
		opword 0x2C1C0001
		opword 0x40820010
		opword 0xFEA0C890
		opword 0xFE80C090
		opword 0x4800003C
		opword 0x2C1C0002
		opword 0x40820010
		opword 0xFEA0E090
		opword 0xFE80C890
		opword 0x48000028
		opword 0x2C1C0003
		opword 0x40820010
		opword 0xFEA0C090
		opword 0xFE80D890
		opword 0x48000014
		opword 0x2C1C0004
		opword 0x4082000C
		opword 0xFEA0D890
		opword 0xFE80E090
		stfs f22, _af_pad+4(r1)
		opword 0x38610040
		opword 0x80FE00C0
		opword 0x38810034
		opword 0xC05A0000
		opword 0x38A10028
		opword 0xC03A0004
		opword 0x38C1001C
		opword 0xC01A0008
		opword 0xEC42A82A
		opword 0x811E00C4
		opword 0xEC21D02A
		opword 0x801E00C8
		opword 0xEC00A02A
		opword 0x90E10010
		opword 0x813E00CC
		opword 0x38E1000C
		opword 0x91010014
		opword 0x811E00D0
		opword 0x90010018
		opword 0x801E00D4
		opword 0xD0410010
		opword 0xD0210014
		opword 0x81810010
		opword 0xD0010018
		opword 0x81610014
		opword 0x81410018
		opword 0x91810040
		opword 0x91610044
		opword 0x91410048
		opword 0x91210034
		opword 0x91010038
		opword 0x9001003C
		bl marioHitCheck2
		opword 0x7C7D1B79
		opword 0x4182020C
		opword 0xC3A10024
		opword 0xC3C10020
		opword 0xC3E1001C
		bl marioGetPtr
		lfs f0, float_100_8041a7f8(r2)
		mr r25, r3
		lfs f1, float_0_8041a7a4(r2)
		fmuls f19, f0, f30
		opword 0xFC400890
		opword 0xEC600772
		opword 0xFC809890
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		lfs f6, float_100_8041a7f8(r2)
		opword 0xFC809890
		opword 0xEC410028
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x90010058
		opword 0xEC6607F2
		opword 0xC8BE01F0
		opword 0xEC0600BA
		lfs f1, float_0_8041a7a4(r2)
		opword 0xFC00001E
		opword 0xFC400890
		opword 0xD8010050
		opword 0x80010054
		opword 0x6C008000
		opword 0x9001005C
		opword 0xC8010058
		opword 0xEC002828
		opword 0xEC003024
		opword 0xD0190218
		opword 0xD039021C
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		opword 0xEC5D0772
		lfs f5, float_100_8041a7f8(r2)
		opword 0xEC610028
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x90010068
		opword 0xC83E01F0
		opword 0xEC8500FA
		lfs f0, float_0_8041a7a4(r2)
		opword 0xEC7F17FA
		opword 0xFC40201E
		opword 0xFC030040
		opword 0xD8410060
		opword 0x80010064
		opword 0x6C008000
		opword 0x9001006C
		opword 0xC8010068
		opword 0xEC000828
		opword 0xEC002824
		opword 0xD0190220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89E01F8
		opword 0xC85E0200
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81E0208
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0610008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_8041a7a4(r2)
		opword 0xFC80F050
		opword 0xFC400890
		bl angleABf
		opword 0x801F0000
		opword 0x540001CF
		opword 0x40820040
		opword 0x801F0004
		opword 0x540001CF
		opword 0x4182000C
		lfs f2, float_75_8041a840(r2)
		opword 0x48000008
		lfs f2, float_50_8041a844(r2)
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC001028
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820014
		opword 0xFC011040
		opword 0x4C411382
		opword 0x40820008
		opword 0x3BA00000
		opword 0x801F0000
		opword 0x540001CF
		opword 0x41820090
		opword 0x281D0000
		opword 0x41820108
		lfs f3, float_100_8041a7f8(r2)
		opword 0x3C004330
		opword 0xC001002C
		opword 0x90010060
		opword 0xEC23D03A
		opword 0xC85E01F0
		lfs f0, float_0p05_8041a848(r2)
		opword 0xFC20081E
		opword 0xD8210068
		opword 0x8001006C
		opword 0x6C008000
		opword 0x90010064
		opword 0xC8210060
		opword 0xEC211028
		opword 0xEC411824
		opword 0xEC2015FC
		opword 0xD041002C
		opword 0xD021002C
		opword 0xC05A0004
		opword 0xEC02B82A
		opword 0xFC000840
		opword 0x4C411382
		opword 0x40820018
		opword 0xD03A0004
		opword 0x7FA3EB78
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD01B0000
		opword 0x480000A8
		opword 0xEC011028
		opword 0x38600000
		opword 0xEC00B828
		opword 0xD01B0000
		opword 0x48000094
		opword 0x281D0000
		opword 0x4182007C
		lfs f2, float_100_8041a7f8(r2)
		opword 0x3C004330
		opword 0xC001002C
		opword 0x90010060
		opword 0xEC02D03A
		opword 0xC83E01F0
		opword 0xFC00001E
		opword 0xD8010068
		opword 0x8001006C
		opword 0x6C008000
		opword 0x90010064
		opword 0xC8010060
		opword 0xEC000828
		opword 0xEC201024
		opword 0xD021002C
		opword 0xC05A0004
		opword 0xEC02B82A
		opword 0xFC000840
		opword 0x4C411382
		opword 0x40820018
		opword 0xD03A0004
		opword 0x7FA3EB78
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD01B0000
		opword 0x48000028
		opword 0xEC011028
		opword 0x38600000
		opword 0xEC00B828
		opword 0xD01B0000
		opword 0x48000014
		opword 0x3B9C0001
		opword 0x2C1C0005
		opword 0x4180FBE8
		opword 0x38600000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioSearchHead_roll(Vec* pos, f32* h, f32 d) {
	char _af_pad[168];
	asm volatile {
		opword 0xFF800890
		mr r26, r3
		opword 0x7C9B2378
		bl marioGetPtr
		lfs f0, float_neg1_8041a7dc(r2)
		lis r5, vec3_802c5808@ha
		lis r4, vec3_802c5814@ha
		opword 0x7C7D1B78
		opword 0xD01B0000
		addi r30, r5, vec3_802c5808@l
		lfs f31, float_1_8041a7bc(r2)
		addi r31, r4, vec3_802c5814@l
		opword 0xC3C301B8
		opword 0x3B800000
		opword 0xEFBEE02A
		opword 0x2C1C0002
		opword 0x418200A0
		opword 0x40800014
		opword 0x2C1C0000
		opword 0x4182001C
		opword 0x40800028
		opword 0x480001D0
		opword 0x2C1C0004
		opword 0x4182015C
		opword 0x408001C4
		opword 0x480000E4
		lfs f0, float_0_8041a7a4(r2)
		stfs f0, _af_pad+4(r1)
		opword 0xD0010008
		opword 0x480001B0
		lfs f1, float_90_8041a81c(r2)
		opword 0xC01D01A0
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC21002A
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		fdivs f28, f1, f0
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		lfs f0, float_9_8041a83c(r2)
		opword 0xFC20E090
		opword 0xEC0000B2
		opword 0xD001000C
		bl cos
		opword 0xFC000818
		lfs f2, float_9_8041a83c(r2)
		lfs f1, float_3_8041a7f0(r2)
		opword 0x3861000C
		opword 0x38810008
		opword 0xFC000050
		opword 0xEC020032
		opword 0xD0010008
		opword 0xC05D01A0
		bl movePos
		opword 0x48000148
		opword 0xC03D01A0
		lfs f0, float_90_8041a81c(r2)
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC210028
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEF810024
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		lfs f0, float_9_8041a83c(r2)
		opword 0xFC20E090
		opword 0xEC0000B2
		opword 0xD001000C
		bl cos
		opword 0xFC000818
		lfs f2, float_9_8041a83c(r2)
		lfs f1, float_3_8041a7f0(r2)
		opword 0x3861000C
		opword 0x38810008
		opword 0xFC000050
		opword 0xEC020032
		opword 0xD0010008
		opword 0xC05D01A0
		bl movePos
		opword 0x480000E0
		lfs f1, float_90_8041a81c(r2)
		opword 0xC01D01A0
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC21002A
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEF810024
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		lfs f0, float_9_8041a83c(r2)
		opword 0xFC20E090
		opword 0xEC0000B2
		opword 0xD001000C
		bl cos
		opword 0xFC000818
		lfs f3, float_9_8041a83c(r2)
		lfs f2, float_180_8041a7cc(r2)
		opword 0x3861000C
		lfs f1, float_3_8041a7f0(r2)
		opword 0x38810008
		opword 0xFC000050
		opword 0xEC030032
		opword 0xD0010008
		opword 0xC01D01A0
		opword 0xEC42002A
		bl movePos
		opword 0x48000070
		opword 0xC03D01A0
		lfs f0, float_90_8041a81c(r2)
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC210028
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEF810024
		opword 0xFC20E090
		bl sin
		opword 0xFC400818
		lfs f0, float_9_8041a83c(r2)
		opword 0xFC20E090
		opword 0xEC0000B2
		opword 0xD001000C
		bl cos
		opword 0xFC000818
		lfs f3, float_9_8041a83c(r2)
		lfs f2, float_180_8041a7cc(r2)
		opword 0x3861000C
		lfs f1, float_3_8041a7f0(r2)
		opword 0x38810008
		opword 0xFC000050
		opword 0xEC030032
		opword 0xD0010008
		opword 0xC01D01A0
		opword 0xEC42002A
		bl movePos
		opword 0xC01A0004
		opword 0x809E0000
		opword 0x807E0004
		opword 0xEC5F002A
		opword 0x801E0008
		opword 0x90610020
		opword 0xC07A0000
		opword 0xC001000C
		opword 0xC03A0008
		opword 0x80FF0000
		opword 0xEC63002A
		opword 0x80DF0004
		opword 0x80BF0008
		opword 0xC0010008
		opword 0x9081001C
		opword 0xEC01002A
		opword 0x90010024
		opword 0xD061001C
		opword 0xD0410020
		opword 0x8081001C
		opword 0xD0010024
		opword 0x80610020
		opword 0x80010024
		opword 0x90E10010
		opword 0x90C10014
		opword 0x90A10018
		opword 0x9081004C
		opword 0x90610050
		opword 0x90010054
		opword 0x90E10058
		opword 0x90C1005C
		opword 0x90A10060
		opword 0xD3A1007C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610040
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610040
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610040
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000150
		opword 0x80010064
		opword 0x80810068
		opword 0x90010034
		opword 0x8001006C
		opword 0xC0210034
		lfs f0, float_0_8041a7a4(r2)
		opword 0x90810038
		opword 0xFC010040
		opword 0x9001003C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010088
		lis r4, double_to_int_802c5920@ha
		opword 0xEC03007A
		opword 0xC0810038
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410080
		opword 0x80010084
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010034
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010098
		opword 0xEC03013A
		opword 0xC081003C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410090
		opword 0x80010094
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010038
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A8
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x34010028
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD80100A0
		opword 0x800100A4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD001003C
		opword 0x4182001C
		opword 0x80A10070
		opword 0x80810074
		opword 0x80010078
		opword 0x90A10028
		opword 0x9081002C
		opword 0x90010030
		opword 0x28030000
		opword 0x41820064
		opword 0xC03A0004
		opword 0xC0410038
		opword 0xEC01F02A
		opword 0xFC001040
		opword 0x4C411382
		opword 0x40820020
		opword 0xEC42F028
		lfs f1, float_1_8041a7bc(r2)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xEC220828
		opword 0xD03A0004
		opword 0xD01B0000
		opword 0x48000040
		opword 0xEC220828
		opword 0xC05B0000
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC020040
		opword 0xEC01F028
		opword 0x4080000C
		opword 0xD01B0000
		opword 0x48000010
		opword 0xFC020040
		opword 0x40810008
		opword 0xD01B0000
		opword 0x3B9C0001
		opword 0x2C1C0005
		opword 0x4180FB70
		opword 0x38600000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioSearchHead_jabara(Vec* pos, f32* h, HitEntry** out, f32 d) {
	char _af_pad[56];
	asm volatile {
		opword 0xFF200890
		mr r26, r3
		opword 0x7C9B2378
		opword 0x7CBC2B78
		bl marioGetPtr
		opword 0x38000000
		lis r4, vec3_802c5820@ha
		opword 0x901C0000
		addi r5, r4, vec3_802c5820@l
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0x7C7F1B78
		opword 0xC3BB0000
		opword 0x3BA00000
		lfs f27, float_neg23p7_8041a834(r2)
		opword 0xD01B0000
		opword 0xEF9DC82A
		lfs f30, float_3p1416_8041a7e0(r2)
		opword 0x80850000
		opword 0x80650004
		opword 0x80050008
		stw r4, _af_pad+28(r1)
		lfs f31, float_180_8041a7cc(r2)
		opword 0x90610028
		lfs f25, float_0p5_8041a7c4(r2)
		opword 0x9001002C
		lfs f26, float_5p8_8041a838(r2)
		opword 0xD3810008
		opword 0xC01F0198
		opword 0xEC1E0032
		opword 0xEC20F824
		bl sin
		opword 0xFC200818
		opword 0xC01A0000
		opword 0xEC1B007A
		opword 0xD0010030
		opword 0xC01F0198
		opword 0xEC1E0032
		opword 0xEC20F824
		bl cos
		opword 0xFC200818
		opword 0xC01A0008
		opword 0x38610030
		opword 0x38810024
		opword 0x38A10018
		opword 0x38C1000C
		opword 0xEC1B007C
		opword 0x38E10008
		opword 0xD0010038
		opword 0xC01A0004
		opword 0xEC19002A
		opword 0xD0010034
		bl marioHitCheck2
		opword 0x7C7E1B79
		opword 0x418200B8
		bl hitGetAttr
		opword 0x5460035B
		opword 0x41820064
		opword 0xC03A0004
		opword 0xC041001C
		opword 0xEC01E82A
		opword 0xFC001040
		opword 0x4C411382
		opword 0x4082003C
		opword 0xD05A0004
		lfs f2, float_0_8041a7a4(r2)
		opword 0xD05B0000
		opword 0xC0210038
		opword 0xC01A0008
		opword 0xEC010028
		opword 0xFC001040
		opword 0x4080000C
		opword 0x3800FFFF
		opword 0x48000008
		opword 0x38000001
		opword 0x901C0000
		opword 0x7FC3F378
		opword 0x48000070
		opword 0xEC020828
		opword 0xEC00E828
		opword 0xD01B0000
		opword 0x4800004C
		opword 0x2C1D0003
		opword 0x40820044
		opword 0xC03A0004
		opword 0xC041001C
		opword 0xEC01E82A
		opword 0xFC001040
		opword 0x4C411382
		opword 0x40820020
		opword 0xD05A0004
		opword 0x38000000
		lfs f0, float_0_8041a7a4(r2)
		opword 0x7FC3F378
		opword 0xD01B0000
		opword 0x901C0000
		opword 0x48000024
		opword 0xEC020828
		opword 0xEC00E828
		opword 0xD01B0000
		opword 0x3BBD0001
		opword 0xEF7BD02A
		opword 0x2C1D0008
		opword 0x4180FED0
		opword 0x38600000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void marioCheckWall(f32 dx, f32 dz) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xDBE10040
		opword 0xF3E10048
		opword 0xDBC10030
		opword 0xF3C10038
		opword 0x93E1002C
		opword 0x93C10028
		opword 0x93A10024
		opword 0xFFC00890
		opword 0xFFE01090
		bl marioGetPtr
		lfs f0, float_0_8041a7a4(r2)
		opword 0x7C7F1B78
		lfs f1, float_1000_8041a7a0(r2)
		opword 0xFC1E0000
		opword 0xD0230210
		opword 0x4182005C
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x40820050
		opword 0xC01F01C8
		opword 0xFC00F040
		opword 0x40800018
		opword 0xD3DF01C8
		opword 0x3800000E
		opword 0xD3FF01CC
		opword 0x901F01D0
		opword 0x48000024
		opword 0x807F01D0
		opword 0x3403FFFF
		opword 0x901F01D0
		opword 0x41810014
		opword 0x38000000
		opword 0x901F01D0
		opword 0xD3DF01C8
		opword 0xD3FF01CC
		opword 0xC01F01CC
		opword 0xD01F019C
		opword 0x4800000C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD01F01C8
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1E0000
		opword 0x40820018
		opword 0xFC20F890
		bl marioSearchFrontWall_staying
		opword 0x387F0210
		bl dou10_yoko_yari
		opword 0x48000198
		opword 0x809F008C
		opword 0x38000000
		opword 0x80BF0090
		opword 0xFC20F090
		opword 0xFC40F890
		opword 0x3861000C
		opword 0x9081000C
		opword 0x38810008
		opword 0x90A10010
		opword 0x80BF0094
		opword 0x90A10014
		opword 0x901F020C
		opword 0xC07F01BC
		bl searchFrontWall
		opword 0x7C7E1B79
		opword 0x4182011C
		opword 0x801F020C
		opword 0x28000000
		opword 0x4182000C
		opword 0x901F01E0
		opword 0x48000008
		opword 0x93DF01E0
		opword 0x7FC3F378
		bl hitGetAttr
		opword 0x7C7D1B78
		bl marioGetPtr
		opword 0x57A00319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x57A00631
		opword 0x4082000C
		opword 0x57A04FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820030
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1E0000
		opword 0x4182000C
		opword 0x93DF01EC
		opword 0x93DF01F0
		opword 0xFC20F090
		opword 0x387F008C
		opword 0xFC40F890
		opword 0x389F0094
		bl movePos
		opword 0x4800009C
		opword 0xC0010008
		opword 0xD01F0210
		opword 0x93DF01F0
		opword 0x887F003F
		opword 0x38630001
		opword 0x7C600774
		opword 0x987F003F
		opword 0x2C000014
		opword 0x41800044
		opword 0x38000014
		opword 0x7FC3F378
		opword 0x981F003F
		bl hitGetAttr
		opword 0x54600631
		opword 0x4082000C
		opword 0x38000001
		opword 0x48000018
		bl marioGetPtr
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x93DF01EC
		opword 0x8061000C
		opword 0x80010010
		opword 0x907F008C
		opword 0x901F0090
		opword 0x80010014
		opword 0x901F0094
		opword 0x4800001C
		opword 0x8061000C
		opword 0x80010010
		opword 0x907F008C
		opword 0x901F0090
		opword 0x80010014
		opword 0x901F0094
		opword 0xFC20F090
		opword 0xC07F01BC
		opword 0xFC40F890
		opword 0xC09F01B8
		opword 0x387F008C
		opword 0x38800000
		bl marioChkWallAround
		opword 0x387F0210
		bl dou10_yoko_yari
		opword 0xE3E10048
		opword 0xCBE10040
		opword 0xE3C10038
		opword 0xCBC10030
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x80010054
		opword 0x83A10024
		opword 0x7C0803A6
		opword 0x38210050
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void marioSearchFrontWall_staying(f32 dz) {
	char _af_pad[28];
	asm volatile {
		opword 0xFFE00890
		bl marioGetPtr
		opword 0x38000000
		lfs f1, float_0p5_8041a7c4(r2)
		opword 0x9803003F
		mr r31, r3
		opword 0x80030000
		opword 0xC00301B4
		opword 0x540002D7
		opword 0xEFA10032
		opword 0x41820008
		lfs f29, float_0_8041a7a4(r2)
		opword 0x80BF008C
		opword 0xFC20E890
		opword 0x801F0090
		la r3, _af_pad+8
		opword 0x3881000C
		opword 0x90A10010
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC05F01A0
		opword 0xC01F0198
		opword 0xC07F01BC
		opword 0xEC420028
		bl searchFrontWall
		opword 0xA01F002E
		opword 0x28000013
		opword 0x4182000C
		opword 0x907F01E0
		opword 0x4800000C
		opword 0x38000000
		opword 0x901F01E0
		opword 0x28030000
		opword 0x40820060
		opword 0xC03F01A8
		bl toMovedir
		opword 0x80BF008C
		opword 0xFC000890
		opword 0x801F0090
		opword 0xFC20E890
		opword 0x38610010
		opword 0x3881000C
		opword 0x90A10010
		opword 0xFC400090
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC07F01BC
		bl searchFrontWall
		opword 0xA01F002E
		opword 0x28000013
		opword 0x4182000C
		opword 0x907F01E0
		opword 0x480000E0
		opword 0x38000000
		opword 0x901F01E0
		opword 0x480000D4
		lwz r5, gp(r13)
		lis r3, str_802C5940@ha
		addi r4, r3, str_802C5940@l
		opword 0x3865012C
		bl strcmp
		opword 0x2C030000
		opword 0x408200B8
		bl vivianGetStatus
		opword 0x2C030002
		opword 0x418200AC
		bl vivianGetStatus
		opword 0x2C030001
		opword 0x418200A0
		bl vivianGetStatus
		opword 0x2C030003
		opword 0x41820094
		opword 0xC03F01A8
		bl toMovedir
		opword 0x80BF008C
		opword 0xFFC00890
		opword 0x801F0090
		opword 0x38610010
		lfs f3, float_0p5_8041a7c4(r2)
		opword 0x38810018
		opword 0x90A10010
		opword 0xFC40F090
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC01F01B4
		opword 0xEC230032
		bl movePos
		lfs f0, float_180_8041a7cc(r2)
		opword 0x38610010
		opword 0xC03F01B4
		opword 0x38810008
		opword 0xEFDE002A
		opword 0xC07F01BC
		opword 0xFC40F090
		bl searchFrontWall
		opword 0x28030000
		opword 0x4182002C
		opword 0xC03F01B4
		opword 0xC0010008
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820018
		opword 0x907F01E0
		lfs f1, float_0p5_8041a7c4(r2)
		opword 0xC0010008
		opword 0xEC010032
		opword 0xD001000C
		opword 0x801F01E0
		opword 0x28000000
		opword 0x4182000C
		opword 0xC001000C
		opword 0xD01F0210
		opword 0xA01F0248
		opword 0x540005EF
		opword 0x4182004C
		opword 0x38000000
		opword 0xFC20E890
		opword 0x901F01DC
		opword 0x38610010
		opword 0x3881000C
		opword 0x80BF008C
		opword 0x801F0090
		opword 0x90A10010
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC05F01A0
		opword 0xC07F01BC
		bl searchFrontWall
		opword 0x28030000
		opword 0x4182000C
		opword 0x801F01E0
		opword 0x901F01DC
		opword 0x80BF008C
		opword 0xFC40F890
		opword 0x801F0090
		opword 0x38610010
		lfs f1, float_0_8041a7a4(r2)
		opword 0x38800000
		opword 0x90A10010
		opword 0x90010014
		opword 0x801F0094
		opword 0x90010018
		opword 0xC07F01BC
		opword 0xC09F01B8
		bl marioChkWallAround
		opword 0xC0010010
		opword 0xD01F008C
		opword 0xC0010018
		opword 0xD01F0094
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void marioCheckWall_roll(f32 dx, f32 dz) {
	char _af_pad[164];
	asm volatile {
		fmr f29, f1
		opword 0xFFC01090
		bl marioGetPtr
		lfs f0, float_0_8041a7a4(r2)
		opword 0x7C7F1B78
		lfs f1, float_1000_8041a7a0(r2)
		opword 0xFC1D0000
		opword 0xD0230210
		opword 0x41820054
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x40820048
		opword 0xC01F01C8
		opword 0xFC00E840
		opword 0x40800018
		opword 0xD3BF01C8
		opword 0x3800000E
		opword 0xD3DF01CC
		opword 0x901F01D0
		opword 0x48000030
		opword 0x807F01D0
		opword 0x3403FFFF
		opword 0x901F01D0
		opword 0x41810020
		opword 0x38000000
		opword 0x901F01D0
		opword 0xD3BF01C8
		opword 0xD3DF01CC
		opword 0x4800000C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD01F01C8
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1D0000
		opword 0x41820018
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x4082000C
		opword 0xC01F01CC
		opword 0xD01F019C
		opword 0x801F0000
		opword 0x540003DF
		opword 0x41820288
		opword 0x809F008C
		lis r3, vec3_802c582c@ha
		opword 0x801F0090
		addi r5, r3, vec3_802c582c@l
		lfs f31, float_30_8041a82c(r2)
		stw r4, _af_pad+52(r1)
		opword 0x80850000
		opword 0x90010040
		opword 0x80650004
		opword 0x80DF0094
		opword 0x80050008
		opword 0x90C10044
		opword 0x90810048
		opword 0x9061004C
		opword 0x90010050
		opword 0xD3E1006C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610030
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610030
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610030
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001AC
		opword 0xC021006C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3CA04330
		lis r4, double_to_int_802c5920@ha
		opword 0x80010054
		opword 0xEC02007A
		addi r6, r4, double_to_int_802c5920@l
		opword 0x90010018
		opword 0x80810058
		opword 0xFC00001E
		opword 0x8001005C
		opword 0x90A10078
		opword 0xC8260000
		opword 0xD8010070
		opword 0xC0810018
		opword 0x80A10074
		lfs f0, float_0_8041a7a4(r2)
		opword 0x6CA58000
		opword 0x9081001C
		opword 0xFC040040
		opword 0x90A1007C
		opword 0xC8010078
		opword 0x90010020
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010088
		opword 0xEC03013A
		opword 0xC081001C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410080
		opword 0x80010084
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010018
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010098
		opword 0xEC03013A
		opword 0xC0810020
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410090
		opword 0x80010094
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001001C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A8
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x3401000C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD80100A0
		opword 0x800100A4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010020
		opword 0x4182001C
		opword 0x80A10060
		opword 0x80810064
		opword 0x80010068
		opword 0x90A1000C
		opword 0x90810010
		opword 0x90010014
		opword 0x28030000
		opword 0x41820014
		lfs f0, float_16p8_8041a830(r2)
		opword 0xFC1F0040
		opword 0x40810008
		opword 0x38600000
		opword 0x28030000
		opword 0x907F01F4
		opword 0x41820014
		opword 0xC021001C
		opword 0xC01F01B8
		opword 0xEC010028
		opword 0xD01F0090
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1D0000
		opword 0x40820010
		opword 0xFC20F090
		bl marioSearchFrontWall_staying
		opword 0x480001BC
		opword 0x801F01F4
		opword 0x28000000
		opword 0x4182001C
		opword 0xD01F0180
		opword 0xFFA00090
		opword 0xD01F007C
		opword 0xD01F0080
		opword 0xD01F0084
		opword 0xD01F0088
		opword 0x80BF008C
		opword 0xFC20E890
		opword 0x801F0090
		opword 0xFC40F090
		opword 0x38610024
		opword 0x38810008
		opword 0x90A10024
		opword 0x90010028
		opword 0x801F0094
		opword 0x9001002C
		opword 0xC07F01BC
		bl searchFrontWall
		opword 0x7C7E1B79
		opword 0x41820104
		opword 0x93DF01E0
		bl hitGetAttr
		mr r29, r3
		bl marioGetPtr
		opword 0x57A00319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x57A00631
		opword 0x4082000C
		opword 0x57A04FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820030
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1D0000
		opword 0x4182000C
		opword 0x93DF01EC
		opword 0x93DF01F0
		opword 0xFC20E890
		opword 0x387F008C
		opword 0xFC40F090
		opword 0x389F0094
		bl movePos
		opword 0x4800009C
		opword 0xC0010008
		opword 0xD01F0210
		opword 0x93DF01F0
		opword 0x887F003F
		opword 0x38630001
		opword 0x7C600774
		opword 0x987F003F
		opword 0x2C000014
		opword 0x41800044
		opword 0x38000014
		opword 0x7FC3F378
		opword 0x981F003F
		bl hitGetAttr
		opword 0x54600631
		opword 0x4082000C
		opword 0x38000001
		opword 0x48000018
		bl marioGetPtr
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x93DF01EC
		opword 0x80610024
		opword 0x80010028
		opword 0x907F008C
		opword 0x901F0090
		opword 0x8001002C
		opword 0x901F0094
		opword 0x4800001C
		opword 0x80610024
		opword 0x80010028
		opword 0x907F008C
		opword 0x901F0090
		opword 0x8001002C
		opword 0x901F0094
		opword 0x80BF008C
		opword 0xFC20E890
		opword 0x801F0090
		opword 0xFC40F090
		opword 0x38610024
		opword 0x38800000
		opword 0x90A10024
		opword 0x90010028
		opword 0x801F0094
		opword 0x9001002C
		opword 0xC07F01BC
		opword 0xC09F01B8
		bl marioChkWallAround
		opword 0xC0010024
		opword 0xD01F008C
		opword 0xC001002C
		opword 0xD01F0094
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* marioChkFront(f32* out, Vec* pos, f32 angle, f32 dist) {
	asm volatile {
		opword 0x9421FF10
		opword 0x7C0802A6
		opword 0x900100F4
		opword 0xDBE100E0
		opword 0xF3E100E8
		opword 0xDBC100D0
		opword 0xF3C100D8
		opword 0x93E100CC
		opword 0x93C100C8
		opword 0x93A100C4
		opword 0xFFC01090
		opword 0x7C7E1B78
		opword 0x7C9F2378
		opword 0x3861000C
		opword 0x38810008
		bl sincosf
		lis r3, vec3_802c5838@ha
		opword 0x80DF0000
		addi r4, r3, vec3_802c5838@l
		opword 0x80BF0004
		opword 0x80640000
		opword 0xFFE0F090
		opword 0x80040008
		opword 0x90610010
		opword 0xC021000C
		opword 0x90010018
		opword 0xC0010008
		opword 0x80E40004
		opword 0xD0210010
		opword 0x809F0008
		opword 0xD0010018
		opword 0x80610010
		opword 0x80010018
		opword 0x90E10014
		opword 0x90C10040
		opword 0x90A10044
		opword 0x90810048
		opword 0x9061004C
		opword 0x90E10050
		opword 0x90010054
		opword 0xD3C10070
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610034
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610034
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610034
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3BA00000
		opword 0x480001B0
		opword 0xC0210070
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3CA04330
		lis r4, double_to_int_802c5920@ha
		opword 0x80010058
		opword 0xEC02007A
		addi r6, r4, double_to_int_802c5920@l
		opword 0x90010028
		opword 0x8081005C
		opword 0xFC00001E
		opword 0x80010060
		opword 0x90A10080
		opword 0xC8260000
		opword 0xD8010078
		opword 0xC0810028
		opword 0x80A1007C
		lfs f0, float_0_8041a7a4(r2)
		opword 0x6CA58000
		opword 0x9081002C
		opword 0xFC040040
		opword 0x90A10084
		opword 0xC8010080
		opword 0x90010030
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010090
		opword 0xEC03013A
		opword 0xC081002C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410088
		opword 0x8001008C
		opword 0x6C008000
		opword 0x90010094
		opword 0xC8010090
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010028
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x900100A0
		opword 0xEC03013A
		opword 0xC0810030
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001002C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100B0
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x3401001C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD80100A8
		opword 0x800100AC
		opword 0x6C008000
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010030
		opword 0x4182001C
		opword 0x80A10064
		opword 0x80810068
		opword 0x8001006C
		opword 0x90A1001C
		opword 0x90810020
		opword 0x90010024
		opword 0x7C7D1B78
		opword 0x281D0000
		opword 0x41820030
		opword 0xFC1FF040
		opword 0x4C401382
		opword 0x40820024
		opword 0xC03F0000
		opword 0xC05F0008
		opword 0xC0610028
		opword 0xC0810030
		bl distABf
		opword 0xD03E0000
		opword 0x7FA3EB78
		opword 0x48000010
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0x38600000
		opword 0xD01E0000
		opword 0xE3E100E8
		opword 0xCBE100E0
		opword 0xE3C100D8
		opword 0xCBC100D0
		opword 0x83E100CC
		opword 0x83C100C8
		opword 0x800100F4
		opword 0x83A100C4
		opword 0x7C0803A6
		opword 0x382100F0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* searchFrontWall(Vec* pos, f32* h, f32 dx, f32 dz, f32 w) {
	char _af_pad[396];
	asm volatile {
		fmr f24, f1
		lis r5, vec3_802c5730@ha
		opword 0xFF201090
		opword 0x7C7E1B78
		opword 0xFF401890
		opword 0x7C942378
		addi r31, r5, vec3_802c5730@l
		bl marioGetPtr
		opword 0x7C781B78
		bl vivianGetStatus
		opword 0x2C030002
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000874
		opword 0xFC20C890
		la r3, _af_pad+12
		opword 0x38810010
		bl sincosf
		opword 0x38600010
		bl marioChkSts
		opword 0x2C030000
		opword 0x41820070
		lwz r3, gp(r13)
		opword 0x389F0218
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x40820058
		opword 0xC0180218
		lfs f1, float_45_8041a7b4(r2)
		opword 0xFC000210
		opword 0xFC000840
		opword 0x4C411382
		opword 0x41820018
		opword 0xC0180220
		opword 0xFC000210
		opword 0xFC000840
		opword 0x4C411382
		opword 0x4082002C
		opword 0xC0210014
		opword 0x38600000
		opword 0xC01E0000
		opword 0xEC18007A
		opword 0xD01E0000
		opword 0xC0210010
		opword 0xC01E0008
		opword 0xEC18007A
		opword 0xD01E0008
		opword 0x480007E8
		opword 0x8818003C
		opword 0x3BA00002
		opword 0x2C000002
		opword 0x40820058
		opword 0x80180014
		opword 0x540007FF
		opword 0x41820030
		lfs f0, float_0p75_8041a7d8(r2)
		opword 0x3BA00003
		opword 0xC07801B8
		lfs f1, float_0p5_8041a7c4(r2)
		opword 0xEC4000F2
		lfs f0, float_11_8041a7ac(r2)
		opword 0xEC2100F2
		opword 0xD0010050
		opword 0xD0410048
		opword 0xD021004C
		opword 0x480000D0
		lfs f2, float_0p75_8041a7d8(r2)
		opword 0xC03801B8
		lfs f0, float_11_8041a7ac(r2)
		opword 0xEC220072
		opword 0xD001004C
		opword 0xD0210048
		opword 0x480000B4
		opword 0xA018002E
		opword 0x2800001A
		opword 0x40820048
		bl marioGetPtr
		opword 0xA003002E
		opword 0xC36301B8
		opword 0x2800001A
		opword 0x4082001C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x4182000C
		bl partyGetHeight
		opword 0xFF600890
		lfs f1, float_0p75_8041a7d8(r2)
		lfs f0, float_11_8041a7ac(r2)
		opword 0xEC2106F2
		opword 0xD001004C
		opword 0xD0210048
		opword 0x48000064
		opword 0x80180000
		opword 0x540001CF
		opword 0x40820030
		opword 0xA8180050
		lfs f1, float_27p75_8041a820(r2)
		lfs f0, float_11_8041a7ac(r2)
		opword 0x2C000000
		opword 0xD0210048
		opword 0xD001004C
		opword 0x4182003C
		lfs f0, float_0p1_8041a7e4(r2)
		opword 0x3BA00003
		opword 0xD0010050
		opword 0x4800002C
		opword 0xA8180050
		lfs f1, float_12_8041a824(r2)
		lfs f0, float_11_8041a7ac(r2)
		opword 0x2C000000
		opword 0xD0210048
		opword 0xD001004C
		opword 0x41820010
		lfs f0, float_7_8041a828(r2)
		opword 0x3BA00003
		opword 0xD0010050
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x3B810048
		opword 0x807F0114
		opword 0x7F97E378
		opword 0x801F011C
		opword 0xEFE006B2
		opword 0x9061003C
		opword 0x3B600000
		opword 0xC0010014
		opword 0x3AC00000
		opword 0xEFDFC02A
		opword 0xD001003C
		opword 0x833F0118
		opword 0x80BE0000
		opword 0xFF60F090
		opword 0x809E0004
		opword 0x807E0008
		opword 0x8341003C
		opword 0x90010044
		opword 0xC0010010
		opword 0x90A10088
		opword 0xD0010044
		opword 0x82A10044
		opword 0x9081008C
		opword 0x90610090
		opword 0x93210040
		opword 0x9341007C
		opword 0x93210080
		opword 0x92A10084
		opword 0x480002B8
		opword 0xC03E0004
		opword 0xFF40F090
		opword 0xC0170000
		opword 0x80610088
		opword 0xEC01002A
		opword 0x80010090
		opword 0x90610120
		opword 0xD001008C
		opword 0x8061008C
		opword 0x90010128
		opword 0x90610124
		opword 0x9341012C
		opword 0x93210130
		opword 0x92A10134
		opword 0xD3C10150
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610114
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610114
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610114
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		li r19, 0x0
		opword 0x4800019C
		opword 0xC0210150
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3CA04330
		opword 0x80010138
		opword 0xEC02007A
		opword 0x8081013C
		opword 0x90010070
		opword 0x80010140
		opword 0xFC00001E
		opword 0x90A10160
		opword 0xC83F01F0
		opword 0xC0810070
		opword 0xD8010158
		lfs f0, float_0_8041a7a4(r2)
		opword 0x80A1015C
		opword 0xFC040040
		opword 0x90810074
		opword 0x6CA48000
		opword 0x90810164
		opword 0xC8010160
		opword 0x90010078
		opword 0xEC000828
		opword 0xEF401024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010170
		opword 0xEC43013A
		opword 0xC83F01F0
		opword 0xC0810074
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410168
		opword 0x8001016C
		opword 0x6C008000
		opword 0x90010174
		opword 0xC8010170
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010070
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010180
		opword 0xEC43013A
		opword 0xC83F01F0
		opword 0xC0810078
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410178
		opword 0x8001017C
		opword 0x6C008000
		opword 0x90010184
		opword 0xC8010180
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010074
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010190
		opword 0x34010058
		opword 0xEC02013A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010188
		opword 0x8001018C
		opword 0x6C008000
		opword 0x90010194
		opword 0xC8010190
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010078
		opword 0x4182001C
		opword 0x80A10144
		opword 0x80810148
		opword 0x8001014C
		opword 0x90A10058
		opword 0x9081005C
		opword 0x90010060
		opword 0x7C731B78
		opword 0x28130000
		opword 0x4182006C
		opword 0x7E639B78
		bl chkBalloon
		opword 0x2C030000
		opword 0x41820008
		opword 0x9278020C
		opword 0x281B0000
		opword 0x41820030
		opword 0xFC1AD840
		opword 0x40800048
		opword 0x80810058
		opword 0xFF60D090
		opword 0x8061005C
		opword 0x7E7B9B78
		opword 0x80010060
		opword 0x90810064
		opword 0x90610068
		opword 0x9001006C
		opword 0x48000024
		opword 0x80810058
		opword 0xFF60D090
		opword 0x8061005C
		opword 0x7E7B9B78
		opword 0x80010060
		opword 0x90810064
		opword 0x90610068
		opword 0x9001006C
		opword 0x3AF70004
		opword 0x3AD60001
		opword 0x7C16E800
		opword 0x4180FD48
		opword 0x281B0000
		opword 0x41820038
		opword 0xC0210010
		opword 0xC0010014
		opword 0xEC810632
		opword 0xC0A1006C
		opword 0xEC600632
		opword 0xC0210064
		lfs f2, float_0p5_8041a7c4(r2)
		opword 0xEC040172
		opword 0xEC03007A
		opword 0xEC20187C
		opword 0xEC00217C
		opword 0xEFA20072
		opword 0xEF820032
		lfs f0, float_45_8041a7b4(r2)
		opword 0x3861000C
		opword 0x38810008
		opword 0x3B400000
		opword 0xEC20C82A
		bl sincosf
		opword 0x807F0120
		opword 0xFF40F890
		opword 0x801F0128
		opword 0x7F97E378
		opword 0x90610030
		opword 0x3B000000
		opword 0xC021000C
		opword 0x90010038
		opword 0xC0010008
		opword 0x82DF0124
		opword 0xD0210030
		opword 0x809E0000
		opword 0xD0010038
		opword 0x807E0004
		opword 0x801E0008
		opword 0x82A10030
		opword 0x83210038
		opword 0x90810088
		opword 0x9061008C
		opword 0x90010090
		opword 0x92C10034
		opword 0x92A10018
		opword 0x92C1001C
		opword 0x93210020
		opword 0x48000110
		opword 0xC03E0004
		opword 0xFF40F890
		opword 0xC0170000
		opword 0x80610088
		opword 0xEC01002A
		opword 0x80010090
		opword 0x906100E0
		opword 0xD001008C
		opword 0x8061008C
		opword 0x900100E8
		opword 0x906100E4
		opword 0x92A100EC
		opword 0x92C100F0
		opword 0x932100F4
		opword 0xD3E10110
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x386100D4
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x386100D4
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x386100D4
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000058
		opword 0xC0210110
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010188
		opword 0xEC02007A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010190
		opword 0x80010194
		opword 0x6C008000
		opword 0x9001018C
		opword 0xC8010188
		opword 0xEC000828
		opword 0xEF401024
		opword 0x28030000
		opword 0x7C7A1B78
		opword 0x40820014
		opword 0x3AF70004
		opword 0x3B180001
		opword 0x7C18E800
		opword 0x4180FEF0
		opword 0x281A0000
		opword 0x41820160
		lfs f0, float_45_8041a7b4(r2)
		opword 0x3861000C
		opword 0x38810008
		opword 0x3B400000
		opword 0xEC390028
		bl sincosf
		opword 0x3AA00000
		opword 0x48000138
		opword 0xC03E0004
		opword 0xFF40F890
		opword 0xC01C0000
		opword 0x807F012C
		opword 0x801F0134
		opword 0xEC21002A
		opword 0x90610024
		opword 0xC001000C
		opword 0xD021008C
		opword 0x80FF0130
		opword 0xD0010024
		opword 0x80C10088
		opword 0x80A1008C
		opword 0x80810090
		opword 0x80610024
		opword 0x9001002C
		opword 0xC0010008
		opword 0x90E10028
		opword 0xD001002C
		opword 0x8001002C
		opword 0x90C100A0
		opword 0x90A100A4
		opword 0x908100A8
		opword 0x906100AC
		opword 0x90E100B0
		opword 0x900100B4
		opword 0xD3E100D0
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610094
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610094
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610094
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000058
		opword 0xC02100D0
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010188
		opword 0xEC02007A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010190
		opword 0x80010194
		opword 0x6C008000
		opword 0x9001018C
		opword 0xC8010188
		opword 0xEC000828
		opword 0xEF401024
		opword 0x7C7A1B78
		opword 0x3B9C0004
		opword 0x3AB50001
		opword 0x7C15E800
		opword 0x4180FEC8
		opword 0x281B0000
		opword 0x4182003C
		opword 0x281A0000
		opword 0x40820024
		opword 0xD3540000
		opword 0xC01E0000
		opword 0xEC00E82A
		opword 0xD01E0000
		opword 0xC01E0008
		opword 0xEC00E02A
		opword 0xD01E0008
		opword 0x4800000C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD0140000
		opword 0x7F63DB78
		opword 0x48000030
		opword 0x281A0000
		opword 0x40820024
		opword 0xC0210014
		opword 0xC01E0000
		opword 0xEC18007A
		opword 0xD01E0000
		opword 0xC0210010
		opword 0xC01E0008
		opword 0xEC18007A
		opword 0xD01E0008
		opword 0x38600000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* dou10_yoko_yari(f32* out) {
	char _af_pad[160];
	asm volatile {
		opword 0x7C7E1B78
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0xA003002E
		opword 0x28000016
		opword 0x4082000C
		opword 0x38600000
		opword 0x480003F4
		opword 0xC03F01A8
		bl toMovedir
		lwz r28, 0x1e0(r31)
		opword 0x281C0000
		opword 0x4182000C
		opword 0x7F83E378
		opword 0x480003D8
		opword 0x80BF008C
		lis r3, str_802C5940@ha
		opword 0x801F0090
		addi r4, r3, str_802C5940@l
		lwz r3, gp(r13)
		stw r5, _af_pad+40(r1)
		opword 0x3863012C
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl strcmp
		opword 0x2C030000
		opword 0x408203A0
		bl vivianGetStatus
		opword 0x2C030002
		opword 0x41820394
		bl vivianGetStatus
		opword 0x2C030001
		opword 0x41820388
		bl vivianGetStatus
		opword 0x2C030003
		opword 0x4182037C
		opword 0x281C0000
		opword 0x40820374
		opword 0x801F0000
		opword 0x540002D7
		opword 0x4182000C
		lfs f31, float_2_8041a7e8(r2)
		opword 0x48000008
		lfs f31, float_8_8041a814(r2)
		opword 0x80010034
		lis r3, vec3_802c5868@ha
		addi r5, r3, vec3_802c5868@l
		opword 0x80E10030
		opword 0x90010028
		opword 0x80C10038
		opword 0xC0210028
		lfs f0, float_60_8041a808(r2)
		opword 0x80850000
		opword 0xEC21002A
		opword 0x80650004
		opword 0x80050008
		lfs f0, float_100_8041a7f8(r2)
		opword 0xD0210028
		opword 0x80A10028
		opword 0x90E10024
		opword 0x90C1002C
		opword 0x90E10048
		opword 0x90A1004C
		opword 0x90C10050
		opword 0x90810054
		opword 0x90610058
		opword 0x9001005C
		opword 0xD0010078
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x3861003C
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x3861003C
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x3861003C
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3BA00000
		opword 0x48000154
		opword 0x80010060
		opword 0x80810064
		opword 0x90010018
		opword 0x80010068
		opword 0xC0210018
		lfs f0, float_0_8041a7a4(r2)
		opword 0x9081001C
		opword 0xFC010040
		opword 0x90010020
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010088
		lis r4, double_to_int_802c5920@ha
		opword 0xEC03007A
		opword 0xC081001C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410080
		opword 0x80010084
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010018
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010098
		opword 0xEC03013A
		opword 0xC0810020
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410090
		opword 0x80010094
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001001C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A8
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x3401000C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD80100A0
		opword 0x800100A4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010020
		opword 0x4182001C
		opword 0x80A1006C
		opword 0x80810070
		opword 0x80010074
		opword 0x90A1000C
		opword 0x90810010
		opword 0x90010014
		opword 0x7C7D1B78
		opword 0x281D0000
		opword 0x41820020
		opword 0x7FA3EB78
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x93BF01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x80BF008C
		opword 0x38610030
		opword 0x801F0090
		opword 0x38810008
		lfs f1, float_20_8041a810(r2)
		opword 0x90A10030
		opword 0xFC600890
		lfs f2, float_0_8041a7a4(r2)
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl searchFrontWall
		opword 0x7C7D1B79
		opword 0x4182001C
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x93BF01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x807F008C
		opword 0x3B810038
		opword 0x801F0090
		opword 0xFC20F890
		lfs f2, float_270_8041a818(r2)
		opword 0x7F84E378
		opword 0x90610030
		opword 0x38610030
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl movePos
		lfs f1, float_20_8041a810(r2)
		opword 0x38610030
		lfs f2, float_0_8041a7a4(r2)
		opword 0x38810008
		opword 0xFC600890
		bl searchFrontWall
		opword 0x7C7D1B79
		opword 0x4182001C
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x93BF01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x80BF008C
		opword 0xFC20F890
		opword 0x801F0090
		opword 0x7F84E378
		lfs f2, float_90_8041a81c(r2)
		opword 0x38610030
		opword 0x90A10030
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl movePos
		lfs f1, float_20_8041a810(r2)
		opword 0x38610030
		lfs f2, float_0_8041a7a4(r2)
		opword 0x38810008
		opword 0xFC600890
		bl searchFrontWall
		opword 0x7C7C1B79
		opword 0x4182001C
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x939F01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x7F83E378
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* dou10_yoko_yari2(f32* out) {
	asm volatile {
		opword 0x9421FF40
		opword 0x7C0802A6
		opword 0x900100C4
		opword 0x93E100BC
		opword 0x93C100B8
		opword 0x7C7E1B78
		opword 0x93A100B4
		opword 0x938100B0
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0xC02301A8
		bl toMovedir
		opword 0x80BF008C
		lis r3, str_802C5940@ha
		opword 0x801F0090
		addi r4, r3, str_802C5940@l
		lwz r3, gp(r13)
		opword 0x90A10030
		opword 0x3863012C
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl strcmp
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000360
		opword 0x80010034
		lis r3, vec3_802c5874@ha
		addi r5, r3, vec3_802c5874@l
		opword 0x80E10030
		opword 0x90010028
		opword 0x80C10038
		opword 0xC0210028
		lfs f0, float_60_8041a808(r2)
		opword 0x80850000
		opword 0xEC21002A
		opword 0x80650004
		opword 0x80050008
		lfs f0, float_100_8041a7f8(r2)
		opword 0xD0210028
		opword 0x80A10028
		opword 0x90E10024
		opword 0x90C1002C
		opword 0x90E10048
		opword 0x90A1004C
		opword 0x90C10050
		opword 0x90810054
		opword 0x90610058
		opword 0x9001005C
		opword 0xD0010078
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x3861003C
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x3861003C
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x3861003C
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3BA00000
		opword 0x48000154
		opword 0x80010060
		opword 0x80810064
		opword 0x90010018
		opword 0x80010068
		opword 0xC0210018
		lfs f0, float_0_8041a7a4(r2)
		opword 0x9081001C
		opword 0xFC010040
		opword 0x90010020
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010088
		lis r4, double_to_int_802c5920@ha
		opword 0xEC03007A
		opword 0xC081001C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410080
		opword 0x80010084
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010018
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010098
		opword 0xEC03013A
		opword 0xC0810020
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410090
		opword 0x80010094
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001001C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A8
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x3401000C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD80100A0
		opword 0x800100A4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010020
		opword 0x4182001C
		opword 0x80A1006C
		opword 0x80810070
		opword 0x80010074
		opword 0x90A1000C
		opword 0x90810010
		opword 0x90010014
		opword 0x7C7D1B78
		opword 0x281D0000
		opword 0x41820020
		opword 0x7FA3EB78
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x93BF01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x80BF008C
		opword 0x38610030
		opword 0x801F0090
		opword 0x38810008
		lfs f1, float_20_8041a810(r2)
		opword 0x90A10030
		opword 0xFC600890
		lfs f2, float_0_8041a7a4(r2)
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl searchFrontWall
		opword 0x7C7D1B79
		opword 0x4182001C
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x93BF01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x80BF008C
		opword 0x3B810038
		opword 0x801F0090
		opword 0x7F84E378
		lfs f1, float_8_8041a814(r2)
		opword 0x38610030
		opword 0x90A10030
		lfs f2, float_270_8041a818(r2)
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl movePos
		lfs f1, float_20_8041a810(r2)
		opword 0x38610030
		lfs f2, float_0_8041a7a4(r2)
		opword 0x38810008
		opword 0xFC600890
		bl searchFrontWall
		opword 0x7C7D1B79
		opword 0x4182001C
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x93BF01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x80BF008C
		opword 0x7F84E378
		opword 0x801F0090
		opword 0x38610030
		lfs f1, float_8_8041a814(r2)
		opword 0x90A10030
		lfs f2, float_90_8041a81c(r2)
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		bl movePos
		lfs f1, float_20_8041a810(r2)
		opword 0x38610030
		lfs f2, float_0_8041a7a4(r2)
		opword 0x38810008
		opword 0xFC600890
		bl searchFrontWall
		opword 0x7C7C1B79
		opword 0x4182001C
		bl hitGetAttr
		opword 0x54600529
		opword 0x41820010
		opword 0x939F01E0
		lfs f0, float_0p8_8041a80c(r2)
		opword 0xD01E0000
		opword 0x7F83E378
		opword 0x800100C4
		opword 0x83E100BC
		opword 0x83C100B8
		opword 0x83A100B4
		opword 0x838100B0
		opword 0x7C0803A6
		opword 0x382100C0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* N_dou10_yoko_yari3(void) {
	char _af_pad[120];
	asm volatile {
		lis r3, vec3_802c5730@ha
		addi r30, r3, vec3_802c5730@l
		bl marioGetPtr
		lwz r5, gp(r13)
		opword 0x7C7F1B78
		opword 0x389E0210
		opword 0x3865012C
		bl strcmp
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38600000
		opword 0x480001D8
		opword 0xC01F008C
		la r3, _af_pad+4
		lfs f1, float_10_8041a7fc(r2)
		opword 0x38810008
		opword 0xD001000C
		lfs f31, 0x90(r31)
		opword 0xC01F0094
		opword 0xD0010008
		opword 0xC05F01A0
		bl movePos
		opword 0x801E0154
		opword 0x38610014
		opword 0x80DE0150
		opword 0x38810010
		opword 0x90010040
		opword 0x80BE0158
		opword 0xD3E10040
		opword 0xC061000C
		opword 0x80010040
		opword 0x90C1003C
		opword 0xC0410008
		opword 0x90010058
		lfs f0, float_5_8041a7b8(r2)
		opword 0x90A10044
		opword 0xC0210058
		opword 0xD061003C
		opword 0xEC01002A
		lfs f1, float_0_8041a7a4(r2)
		opword 0xD0410044
		opword 0x80A1003C
		opword 0x80010044
		opword 0x90A10054
		opword 0x9001005C
		opword 0xD0010058
		bl sincosf
		opword 0x80BE015C
		opword 0x38610048
		opword 0x801E0164
		opword 0x38800000
		opword 0x90A10030
		opword 0xC0010014
		opword 0x90010038
		opword 0xC0210010
		opword 0x80DE0160
		opword 0xD0010030
		lfs f0, float_40_8041a800(r2)
		opword 0xD0210038
		opword 0x80A10030
		opword 0x80010038
		opword 0x90C10034
		opword 0x90A10060
		opword 0x90C10064
		opword 0x90010068
		opword 0xD0010084
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4182000C
		opword 0x907F01E0
		opword 0x480000EC
		opword 0xC01F008C
		opword 0x3861000C
		lfs f1, float_neg10_8041a804(r2)
		opword 0x38810008
		opword 0xD001000C
		opword 0xC3FF0090
		opword 0xC01F0094
		opword 0xD0010008
		opword 0xC05F01A0
		bl movePos
		opword 0x801E016C
		opword 0x38610014
		opword 0x80DE0168
		opword 0x38810010
		opword 0x90010028
		opword 0x80BE0170
		opword 0xD3E10028
		opword 0xC061000C
		opword 0x80010028
		opword 0x90C10024
		opword 0xC0410008
		opword 0x90010058
		lfs f0, float_5_8041a7b8(r2)
		opword 0x90A1002C
		opword 0xC0210058
		opword 0xD0610024
		opword 0xEC01002A
		lfs f1, float_0_8041a7a4(r2)
		opword 0xD041002C
		opword 0x80A10024
		opword 0x8001002C
		opword 0x90A10054
		opword 0x9001005C
		opword 0xD0010058
		bl sincosf
		opword 0x80BE0174
		opword 0x38610048
		opword 0x801E017C
		opword 0x38800000
		opword 0x90A10018
		opword 0xC0010014
		opword 0x90010020
		opword 0xC0210010
		opword 0x80DE0178
		opword 0xD0010018
		lfs f0, float_40_8041a800(r2)
		opword 0xD0210020
		opword 0x80A10018
		opword 0x80010020
		opword 0x90C1001C
		opword 0x90A10060
		opword 0x90C10064
		opword 0x90010068
		opword 0xD0010084
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x41820008
		opword 0x907F01E0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioChkFrontStep(f32* y, f32* h, f32* ang) {
	char _af_pad[148];
	asm volatile {
		lis r6, vec3_802c5730@ha
		opword 0x7C7A1B78
		opword 0x7C9B2378
		opword 0x7CBC2B78
		addi r30, r6, vec3_802c5730@l
		bl marioGetPtr
		lfs f0, float_0_8041a7a4(r2)
		opword 0x7C7F1B78
		opword 0xD0030218
		opword 0xD003021C
		opword 0xD0030220
		opword 0xD0030214
		opword 0x80030000
		opword 0x540001CF
		opword 0x4182000C
		lfs f31, float_18p5_8041a7ec(r2)
		opword 0x48000010
		lfs f1, float_0p5_8041a7c4(r2)
		opword 0xC01F01B8
		opword 0xEFE10032
		opword 0xC01F0090
		lfs f1, float_neg1_8041a7dc(r2)
		opword 0xD01A0000
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD03B0000
		opword 0xC03F0180
		opword 0xFC010000
		opword 0x4182000C
		opword 0xC03F01A0
		opword 0x4800000C
		opword 0xC03F01A8
		bl toMovedir
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x3C004330
		stw r0, _af_pad+112(r1)
		opword 0xEC00082A
		opword 0xC83E01F0
		opword 0xFC00001E
		opword 0xD8010070
		opword 0x80010074
		opword 0x6C008000
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC200828
		bl revise360
		opword 0x801F0000
		opword 0x540001CF
		opword 0x4182000C
		lfs f27, float_3_8041a7f0(r2)
		opword 0x48000010
		lfs f2, float_0p265_8041a7f4(r2)
		opword 0xC01F01B4
		opword 0xEF620032
		lfs f2, float_3p1416_8041a7e0(r2)
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEFA10024
		opword 0xFC20E890
		bl sin
		opword 0xFF800818
		opword 0xFC20E890
		bl cos
		opword 0xFC200818
		opword 0xC3BF0090
		opword 0x809E0180
		opword 0xEC1B0732
		opword 0xC3DF008C
		opword 0xEC7DF82A
		opword 0xFC200850
		opword 0x807E0184
		opword 0x801E0188
		opword 0xEC9E002A
		lfs f0, float_11_8041a7ac(r2)
		opword 0xEC3B0072
		opword 0xC39F0094
		opword 0xEC00F82A
		opword 0x9081000C
		opword 0xEC5C082A
		lfs f1, float_0p1_8041a7e4(r2)
		opword 0x90610010
		opword 0xEC01002A
		opword 0x809E018C
		opword 0x90010014
		opword 0x807E0190
		opword 0xD081000C
		opword 0x801E0194
		opword 0xD0610010
		opword 0x80E1000C
		opword 0xD0410014
		opword 0x80C10010
		opword 0x80A10014
		opword 0x90E1003C
		opword 0x90C10040
		opword 0x90A10044
		opword 0x90810048
		opword 0x9061004C
		opword 0x90010050
		opword 0xD001006C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610030
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610030
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610030
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000144
		opword 0x80010054
		opword 0x80810058
		opword 0x90010024
		opword 0x8001005C
		opword 0xC0210024
		lfs f0, float_0_8041a7a4(r2)
		opword 0x90810028
		opword 0xFC010040
		opword 0x9001002C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010070
		opword 0xEC43007A
		opword 0xC83E01F0
		opword 0xC0810028
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010088
		opword 0xEC43013A
		opword 0xC83E01F0
		opword 0xC081002C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410080
		opword 0x80010084
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010028
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010098
		opword 0x34010018
		opword 0xEC02013A
		opword 0xC83E01F0
		opword 0xFC00001E
		opword 0xD8010090
		opword 0x80010094
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD001002C
		opword 0x4182001C
		opword 0x80A10060
		opword 0x80810064
		opword 0x80010068
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90010020
		opword 0x28030000
		opword 0x7C7D1B78
		opword 0x41820250
		bl marioGetPtr
		lfs f1, float_0_8041a7a4(r2)
		mr r25, r3
		lfs f4, float_100_8041a7f8(r2)
		opword 0xC0610020
		opword 0xFC400890
		opword 0xC001001C
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		lfs f7, float_100_8041a7f8(r2)
		opword 0xEC810028
		lfs f0, float_0p5_8041a7c4(r2)
		lfs f2, float_0_8041a7a4(r2)
		opword 0xC0610018
		opword 0xECC7013A
		opword 0xC001001C
		opword 0x90010090
		opword 0xFC201090
		opword 0xEC870032
		opword 0xC8BE01F0
		opword 0xFC00301E
		opword 0xEC6700F2
		opword 0xD8010098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x90010094
		opword 0xC8010090
		opword 0xEC002828
		opword 0xEC003824
		opword 0xD0190218
		opword 0xD059021C
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		opword 0xC0410018
		opword 0xEC610028
		opword 0xC0010020
		lfs f5, float_100_8041a7f8(r2)
		opword 0xEC2200B2
		lfs f2, float_0p5_8041a7c4(r2)
		opword 0xEC000032
		opword 0xEC8510FA
		opword 0x90010080
		opword 0xC85E01F0
		opword 0xEC61002A
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20201E
		opword 0xFC030040
		opword 0xD8210088
		opword 0x8001008C
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8010080
		opword 0xEC001028
		opword 0xEC002824
		opword 0xD0190220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89E01F8
		opword 0xC85E0200
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81E0208
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0610008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_8041a7a4(r2)
		opword 0xC001001C
		opword 0xFC400890
		opword 0xFC800050
		bl angleABf
		opword 0xC0410028
		opword 0xD03F0214
		opword 0xFC02E840
		opword 0x40800040
		opword 0xEC22E828
		lfs f0, float_2_8041a7e8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820028
		opword 0xEC1D1028
		opword 0xC0610024
		opword 0xFC20F090
		opword 0xC081002C
		opword 0xFC40E090
		opword 0xD01B0000
		bl angleABf
		opword 0xD03C0000
		opword 0x48000034
		opword 0xC0610028
		opword 0xFC20F090
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40E090
		opword 0xD07A0000
		opword 0xC0610024
		opword 0xD01B0000
		opword 0xC081002C
		bl angleABf
		opword 0xD03C0000
		opword 0x7FA3EB78
		opword 0x48000008
		opword 0x38600000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
BOOL marioChkWallAround(Vec* pos, void* p, f32 unused, f32 dir, f32 w, f32 h) {
	char _af_pad[412];
	asm volatile {
		opword 0xFF001090
		lis r5, vec3_802c5730@ha
		opword 0xFF201890
		opword 0x7C761B78
		opword 0xFF402090
		opword 0x7C952378
		addi r31, r5, vec3_802c5730@l
		opword 0x3B600008
		opword 0x3B000000
		bl kpaGetStageViewType
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B600002
		opword 0x6F638000
		opword 0x3C004330
		stw r3, _af_pad+396(r1)
		opword 0xFFC0C090
		opword 0x80B60004
		opword 0x3BA00000
		opword 0x90010190
		opword 0xC83F01F0
		opword 0xC8010190
		lfs f2, float_360_8041a7c0(r2)
		opword 0xEC200828
		opword 0x83D60000
		opword 0x83960008
		lfs f0, float_1_8041a7bc(r2)
		opword 0xEF620824
		opword 0x90A10088
		lfs f1, float_0p5_8041a7c4(r2)
		opword 0x809F0198
		opword 0x807F019C
		opword 0x90A1007C
		opword 0xEFE10672
		opword 0x801F01A0
		opword 0xEC1A0028
		opword 0xC021007C
		opword 0xC0610088
		lfs f2, float_11_8041a7ac(r2)
		opword 0xEC01002A
		opword 0x93C10030
		opword 0xEC23102A
		opword 0x90A10034
		opword 0xD0210088
		opword 0xD001007C
		opword 0x83410088
		opword 0x93810038
		opword 0x8321007C
		opword 0x93C10084
		opword 0x9381008C
		opword 0x93C10078
		opword 0x93810080
		opword 0x90810060
		opword 0x90610064
		opword 0x90010068
		opword 0x48000350
		opword 0xFC20F090
		opword 0x38610014
		opword 0x38810010
		bl sincosf
		opword 0x807F01A4
		opword 0xFFA0F890
		opword 0x801F01AC
		opword 0xFF80F890
		opword 0x90610048
		opword 0xC0210014
		opword 0x90010050
		opword 0xC0010010
		opword 0x809F01A8
		opword 0xD0210048
		opword 0x80610048
		opword 0xD0010050
		opword 0x80010050
		opword 0x9081004C
		opword 0x9061006C
		opword 0x90810070
		opword 0x90010074
		opword 0x93C1015C
		opword 0x93410160
		opword 0x93810164
		opword 0x90610168
		opword 0x9081016C
		opword 0x90010170
		opword 0xD3E1018C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610150
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610150
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610150
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3AE00000
		opword 0x4800005C
		opword 0xC021018C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010198
		opword 0x7C771B78
		opword 0xEC02007A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010190
		opword 0x80010194
		opword 0x6C008000
		opword 0x9001019C
		opword 0xC8010198
		opword 0xEC000828
		opword 0xEFA01024
		opword 0x8081006C
		opword 0x80610070
		opword 0x80010074
		opword 0x93C1011C
		opword 0x93210120
		opword 0x93810124
		opword 0x90810128
		opword 0x9061012C
		opword 0x90010130
		opword 0xD381014C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610110
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610110
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610110
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		li r19, 0x0
		opword 0x4800005C
		opword 0xC021014C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010190
		opword 0x7C731B78
		opword 0xEC02007A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010198
		opword 0x8001019C
		opword 0x6C008000
		opword 0x90010194
		opword 0xC8010190
		opword 0xEC000828
		opword 0xEF801024
		opword 0x7EE3BB78
		bl hitGetAttr
		opword 0x7C741B78
		bl marioGetPtr
		opword 0x56800319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x56800631
		opword 0x4082000C
		opword 0x56804FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x3AE00000
		opword 0x7E639B78
		bl hitGetAttr
		opword 0x7C741B78
		bl marioGetPtr
		opword 0x56800319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x56800631
		opword 0x4082000C
		opword 0x56804FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x3A600000
		opword 0x28170000
		opword 0x41820020
		opword 0x28130000
		opword 0x41820018
		opword 0xFC1DE040
		opword 0x40810020
		opword 0xFFA0E090
		opword 0x7E779B78
		opword 0x48000014
		opword 0x28130000
		opword 0x4182000C
		opword 0x7E779B78
		opword 0xFFA0E090
		opword 0x28170000
		opword 0x41820044
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3861000C
		opword 0x38810008
		opword 0xEC20F02A
		bl sincosf
		opword 0xEC1FE828
		opword 0xC081000C
		opword 0xC0410060
		opword 0x3B000001
		opword 0xC0210008
		opword 0xFC600210
		opword 0xC0010068
		opword 0xEC4410FA
		opword 0xEC0100FA
		opword 0xD0410060
		opword 0xD0010068
		opword 0xEFDED82A
		opword 0x3BBD0001
		opword 0x7C1DD800
		opword 0x4180FCB0
		opword 0x2C180000
		opword 0x4082000C
		opword 0x7F03C378
		opword 0x480004B8
		lfs f0, float_0p125_8041a7d0(r2)
		opword 0x2C150000
		opword 0xEF800672
		opword 0x40820024
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800000A
		opword 0x4182000C
		opword 0x2800000B
		opword 0x4082000C
		lfs f0, float_0p25_8041a7d4(r2)
		opword 0xEF800672
		lfs f0, float_1_8041a7bc(r2)
		opword 0xFC1C0040
		opword 0x40800008
		opword 0xFF800090
		opword 0x80A10060
		opword 0x38610060
		opword 0x80810064
		opword 0x80010068
		opword 0x90A10054
		opword 0x90810058
		opword 0x9001005C
		bl PSVECMag
		opword 0xFC01E040
		opword 0x40810014
		opword 0xEC3C0824
		opword 0x38610060
		opword 0x7C641B78
		bl PSVECScale
		opword 0x7EC3B378
		opword 0x7EC5B378
		opword 0x38810060
		bl PSVECAdd
		opword 0x80B60004
		opword 0xFFC0C090
		lfs f0, float_1_8041a7bc(r2)
		opword 0x3BC00000
		opword 0x90A10088
		opword 0xEC1A0028
		opword 0x83960000
		opword 0x90A1007C
		opword 0xC0610088
		lfs f2, float_11_8041a7ac(r2)
		opword 0xC021007C
		opword 0xEC43102A
		opword 0x83B60008
		opword 0xEC01002A
		opword 0x809F01B0
		opword 0x807F01B4
		opword 0xD0410088
		opword 0x801F01B8
		opword 0xD001007C
		opword 0x83210088
		opword 0x93810024
		opword 0x8341007C
		opword 0x90A10028
		opword 0x93A1002C
		opword 0x93810084
		opword 0x93A1008C
		opword 0x93810078
		opword 0x93A10080
		opword 0x90810060
		opword 0x90610064
		opword 0x90010068
		opword 0x48000350
		opword 0xFC20F090
		opword 0x38610014
		opword 0x38810010
		bl sincosf
		opword 0x807F01BC
		opword 0xFF00F890
		opword 0x801F01C4
		opword 0xFF20F890
		opword 0x9061003C
		opword 0xC0210014
		opword 0x90010044
		opword 0xC0010010
		opword 0x809F01C0
		opword 0xD021003C
		opword 0x8061003C
		opword 0xD0010044
		opword 0x80010044
		opword 0x90810040
		opword 0x90610018
		opword 0x9081001C
		opword 0x90010020
		opword 0x938100DC
		opword 0x932100E0
		opword 0x93A100E4
		opword 0x906100E8
		opword 0x908100EC
		opword 0x900100F0
		opword 0xD3E1010C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x386100D0
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x386100D0
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x386100D0
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3AE00000
		opword 0x4800005C
		opword 0xC021010C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010190
		opword 0x7C771B78
		opword 0xEC02007A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010198
		opword 0x8001019C
		opword 0x6C008000
		opword 0x90010194
		opword 0xC8010190
		opword 0xEC000828
		fdivs f24, f0, f2
		opword 0x80810018
		opword 0x8061001C
		opword 0x80010020
		opword 0x9381009C
		opword 0x934100A0
		opword 0x93A100A4
		opword 0x908100A8
		opword 0x906100AC
		opword 0x900100B0
		opword 0xD32100CC
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610090
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610090
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610090
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3A600000
		opword 0x4800005C
		opword 0xC02100CC
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010190
		opword 0x7C731B78
		opword 0xEC02007A
		opword 0xC83F01F0
		opword 0xFC00001E
		opword 0xD8010198
		opword 0x8001019C
		opword 0x6C008000
		opword 0x90010194
		opword 0xC8010190
		opword 0xEC000828
		opword 0xEF201024
		opword 0x7EE3BB78
		bl hitGetAttr
		opword 0x7C741B78
		bl marioGetPtr
		opword 0x56800319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x56800631
		opword 0x4082000C
		opword 0x56804FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x3AE00000
		opword 0x7E639B78
		bl hitGetAttr
		opword 0x7C741B78
		bl marioGetPtr
		opword 0x56800319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x56800631
		opword 0x4082000C
		opword 0x56804FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x3A600000
		opword 0x28170000
		opword 0x41820020
		opword 0x28130000
		opword 0x41820018
		opword 0xFC18C840
		opword 0x40810020
		opword 0xFF00C890
		opword 0x7E779B78
		opword 0x48000014
		opword 0x28130000
		opword 0x4182000C
		opword 0x7E779B78
		opword 0xFF00C890
		opword 0x28170000
		opword 0x41820044
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3861000C
		opword 0x38810008
		opword 0xEC20F02A
		bl sincosf
		opword 0xEC1FC028
		opword 0xC081000C
		opword 0xC0410060
		opword 0x3B000001
		opword 0xC0210008
		opword 0xFC600210
		opword 0xC0010068
		opword 0xEC4410FA
		opword 0xEC0100FA
		opword 0xD0410060
		opword 0xD0010068
		opword 0xEFDED82A
		opword 0x3BDE0001
		opword 0x7C1ED800
		opword 0x4180FCB0
		opword 0x2C180000
		opword 0x4082000C
		opword 0x38600001
		opword 0x4800004C
		opword 0x38610054
		opword 0x38810060
		bl PSVECDotProduct
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000028
		opword 0x38610060
		lfs f1, float_0p5_8041a7c4(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x7EC3B378
		opword 0x7EC5B378
		opword 0x38810060
		bl PSVECAdd
		opword 0x38600001
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
BOOL marioSlitChkWallAround(void) {
	char _af_pad[284];
	asm volatile {
		lis r3, vec3_802c5730@ha
		addi r31, r3, vec3_802c5730@l
		bl marioGetPtr
		opword 0x7C7D1B78
		la r30, _af_pad+56
		opword 0x80030090
		opword 0x7FD9F378
		opword 0x8343008C
		opword 0x3B000000
		opword 0x90010038
		opword 0x83630094
		opword 0xC0210038
		lfs f0, float_11_8041a7ac(r2)
		opword 0x93410034
		opword 0xEC01002A
		lfs f29, float_0_8041a7a4(r2)
		opword 0x9361003C
		lfs f30, float_13_8041a7b0(r2)
		opword 0xD0010038
		lfs f31, float_45_8041a7b4(r2)
		opword 0x83810038
		opword 0x38000000
		opword 0xFC20E890
		opword 0x90190000
		opword 0x3861000C
		opword 0x38810008
		bl sincosf
		opword 0x807F01C8
		opword 0x801F01D0
		opword 0x90610028
		opword 0xC021000C
		opword 0x90010030
		opword 0xC0010008
		opword 0x809F01CC
		opword 0xD0210028
		opword 0xD0010030
		opword 0x80610028
		opword 0x80010030
		opword 0x9081002C
		opword 0x934100EC
		opword 0x938100F0
		opword 0x936100F4
		opword 0x906100F8
		opword 0x908100FC
		opword 0x90010100
		opword 0xD3C1011C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x386100E0
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x386100E0
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x386100E0
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x40820008
		opword 0x38600000
		opword 0x28030000
		opword 0x4182005C
		bl hitGetAttr
		mr r23, r3
		bl marioGetPtr
		opword 0x56E00319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x56E00631
		opword 0x4082000C
		opword 0x56E04FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38000001
		opword 0x90190000
		opword 0x3B180001
		opword 0xEFBDF82A
		opword 0x2C180008
		opword 0x3B390004
		opword 0x4180FEC8
		opword 0xC03D0090
		opword 0x7FD9F378
		lfs f0, float_5_8041a7b8(r2)
		opword 0x3B400000
		lfs f30, float_0_8041a7a4(r2)
		opword 0xEC01002A
		lfs f31, float_45_8041a7b4(r2)
		opword 0xD0010038
		opword 0x80190000
		opword 0x2C000001
		opword 0x41820134
		opword 0xFC20F090
		opword 0x3861000C
		opword 0x38810008
		bl sincosf
		opword 0x807F01D4
		opword 0x801F01DC
		opword 0x9061001C
		opword 0xC021000C
		opword 0x90010024
		opword 0xC0010008
		opword 0x80FF01D8
		opword 0xD021001C
		opword 0x80C10034
		opword 0xD0010024
		opword 0x80A10038
		opword 0x8081003C
		opword 0x8061001C
		opword 0x80010024
		lfs f0, float_13_8041a7b0(r2)
		opword 0x90E10020
		opword 0x90C100AC
		opword 0x90A100B0
		opword 0x908100B4
		opword 0x906100B8
		opword 0x90E100BC
		opword 0x900100C0
		opword 0xD00100DC
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x386100A0
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x386100A0
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x386100A0
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x40820008
		opword 0x38600000
		opword 0x28030000
		opword 0x4182005C
		bl hitGetAttr
		opword 0x7C781B78
		bl marioGetPtr
		opword 0x57000319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x57000631
		opword 0x4082000C
		opword 0x57004FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38000001
		opword 0x90190000
		opword 0x3B5A0001
		opword 0xEFDEF82A
		opword 0x2C1A0008
		opword 0x3B390004
		opword 0x4180FEB4
		opword 0xC03D01B8
		opword 0x7FD9F378
		lfs f0, float_1_8041a7bc(r2)
		opword 0x3B400000
		opword 0xC05D0090
		opword 0xEC010028
		lfs f30, float_0_8041a7a4(r2)
		lfs f31, float_45_8041a7b4(r2)
		opword 0xEC02002A
		opword 0xD0010038
		opword 0x80190000
		opword 0x2C000001
		opword 0x41820134
		opword 0xFC20F090
		opword 0x3861000C
		opword 0x38810008
		bl sincosf
		opword 0x807F01E0
		opword 0x801F01E8
		opword 0x90610010
		opword 0xC021000C
		opword 0x90010018
		opword 0xC0010008
		opword 0x80FF01E4
		opword 0xD0210010
		opword 0x80C10034
		opword 0xD0010018
		opword 0x80A10038
		opword 0x8081003C
		opword 0x80610010
		opword 0x80010018
		lfs f0, float_13_8041a7b0(r2)
		opword 0x90E10014
		opword 0x90C1006C
		opword 0x90A10070
		opword 0x90810074
		opword 0x90610078
		opword 0x90E1007C
		opword 0x90010080
		opword 0xD001009C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610060
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610060
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610060
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x40820008
		opword 0x38600000
		opword 0x28030000
		opword 0x4182005C
		bl hitGetAttr
		opword 0x7C781B78
		bl marioGetPtr
		opword 0x57000319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x57000631
		opword 0x4082000C
		opword 0x57004FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38000001
		opword 0x90190000
		opword 0x3B5A0001
		opword 0xEFDEF82A
		opword 0x2C1A0008
		opword 0x3B390004
		opword 0x4180FEB4
		opword 0x38000002
		opword 0x38610040
		opword 0x38800000
		opword 0x7C0903A6
		opword 0x801E0000
		opword 0x2C000000
		opword 0x40820034
		opword 0x38040001
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x40820020
		opword 0x38040002
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480000C8
		opword 0x801E0004
		opword 0x2C000000
		opword 0x40820034
		opword 0x38040002
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x40820020
		opword 0x38040003
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x4800008C
		opword 0x801E0008
		opword 0x2C000000
		opword 0x40820034
		opword 0x38040003
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x40820020
		opword 0x38040004
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000050
		opword 0x801E000C
		opword 0x2C000000
		opword 0x40820034
		opword 0x38040004
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x40820020
		opword 0x38040005
		opword 0x540016FA
		opword 0x7C03002E
		opword 0x2C000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000014
		opword 0x3BDE0010
		opword 0x38840004
		opword 0x4200FF08
		opword 0x38600001
	}
}
#pragma pop

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void marioCheckWallShip(f32 dx, f32 dz) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xDBE10060
		opword 0xF3E10068
		opword 0xDBC10050
		opword 0xF3C10058
		opword 0x93E1004C
		opword 0x93C10048
		opword 0x93A10044
		opword 0xFFC00890
		opword 0xFFE01090
		bl marioGetPtr
		lfs f0, float_0_8041a7a4(r2)
		opword 0x7C7F1B78
		lfs f1, float_1000_8041a7a0(r2)
		opword 0xFC1E0000
		opword 0xD0230210
		opword 0x41820054
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x40820048
		opword 0xC01F01C8
		opword 0xFC00F040
		opword 0x40800018
		opword 0xD3DF01C8
		opword 0x3800000E
		opword 0xD3FF01CC
		opword 0x901F01D0
		opword 0x48000030
		opword 0x807F01D0
		opword 0x3403FFFF
		opword 0x901F01D0
		opword 0x41810020
		opword 0x38000000
		opword 0x901F01D0
		opword 0xD3DF01C8
		opword 0xD3FF01CC
		opword 0x4800000C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD01F01C8
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1E0000
		opword 0x41820018
		opword 0xA81F0050
		opword 0x2C000000
		opword 0x4082000C
		opword 0xC01F01CC
		opword 0xD01F019C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1E0000
		opword 0x40820010
		opword 0xFC20F890
		bl marioSearchFrontWall_staying
		opword 0x480001F8
		opword 0x80BF008C
		opword 0xFC20F090
		opword 0x801F0090
		opword 0xFC40F890
		opword 0x38610030
		opword 0x38810008
		opword 0x90A10030
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		opword 0xC07F01BC
		bl searchFrontWall
		opword 0x7C7E1B79
		opword 0x41820130
		opword 0x93DF01E0
		bl hitGetAttr
		opword 0x7C7D1B78
		bl marioGetPtr
		opword 0x57A00319
		opword 0x41820018
		opword 0x80030000
		opword 0x540001CF
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000024
		opword 0x57A00631
		opword 0x4082000C
		opword 0x57A04FFE
		opword 0x48000014
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820048
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1E0000
		opword 0x4182000C
		opword 0x93DF01EC
		opword 0x93DF01F0
		opword 0xFC20F090
		opword 0x387F008C
		opword 0xFC40F890
		opword 0x389F0094
		bl movePos
		opword 0x807F008C
		opword 0x801F0090
		opword 0x90610030
		opword 0x90010034
		opword 0x801F0094
		opword 0x90010038
		opword 0x48000128
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC1E0000
		opword 0x40820010
		opword 0x38000000
		opword 0x981F003F
		opword 0x48000068
		opword 0xC0010008
		opword 0xD01F0210
		opword 0x93DF01F0
		opword 0x887F003F
		opword 0x38630001
		opword 0x7C600774
		opword 0x987F003F
		opword 0x2C000014
		opword 0x41800044
		opword 0x38000014
		opword 0x7FC3F378
		opword 0x981F003F
		bl hitGetAttr
		opword 0x54600631
		opword 0x4082000C
		opword 0x38000001
		opword 0x48000018
		bl marioGetPtr
		opword 0xA003002E
		opword 0x20000019
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x2C000000
		opword 0x41820008
		opword 0x93DF01EC
		opword 0x80610030
		opword 0x80010034
		opword 0x907F008C
		opword 0x901F0090
		opword 0x80010038
		opword 0x901F0094
		opword 0x80C10030
		opword 0xFC20F090
		opword 0x80A10034
		opword 0xFC40F890
		opword 0x80010038
		opword 0x387F008C
		opword 0x90C10024
		lfs f4, float_4_8041a7a8(r2)
		opword 0x38800000
		opword 0x90A10028
		opword 0x9001002C
		opword 0x90DF008C
		opword 0x90BF0090
		opword 0x901F0094
		opword 0x90C1000C
		opword 0xC07F01BC
		opword 0x90A10010
		opword 0x90010014
		bl marioChkWallAround
		opword 0xC3FF0188
		opword 0x387F008C
		opword 0x38810024
		opword 0x38A10018
		bl PSVECSubtract
		opword 0x38610018
		bl PSVECMag
		opword 0xFC01F840
		opword 0x40810024
		opword 0xEC3F0824
		opword 0x38610018
		opword 0x7C641B78
		bl PSVECScale
		opword 0x38610024
		opword 0x38810018
		opword 0x38BF008C
		bl PSVECAdd
		opword 0xE3E10068
		opword 0xCBE10060
		opword 0xE3C10058
		opword 0xCBC10050
		opword 0x83E1004C
		opword 0x83C10048
		opword 0x80010074
		opword 0x83A10044
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
	beq L_af_1
	lfs f0, 0x90(r28)
	li r3, 0x0
	stfs f0, 0x0(r24)
	b L_af_2
L_af_1:
	rlwinm. r0, r3, 0, 23, 23
	beq L_af_3
	lfs f0, 0x90(r28)
	li r3, 0x0
	stfs f0, 0x0(r24)
	b L_af_2
L_af_3:
	fabs f3, f24
	lfs f4, float_0p1_8041a7e4(r2)
	lfs f0, 0x180(r28)
	lfs f2, float_0p5_8041a7c4(r2)
	lfs f1, 0x1b8(r28)
	fcmpu cr0, f0, f5
	fadds f29, f4, f3
	fmuls f28, f2, f1
	beq L_af_4
	lfs f1, 0x1a0(r28)
	b L_af_5
L_af_4:
	lfs f1, 0x1a8(r28)
	bl toMovedir
L_af_5:
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
L_af_6:
	cmpwi r25, 0x0
	bne L_af_7
	lfs f22, float_0_8041a7a4(r2)
	fmr f21, f22
	b L_af_8
L_af_7:
	cmpwi r25, 0x1
	bne L_af_9
	fmr f22, f27
	fmr f21, f26
	b L_af_8
L_af_9:
	cmpwi r25, 0x2
	bne L_af_10
	fmr f22, f31
	fmr f21, f26
	b L_af_8
L_af_10:
	cmpwi r25, 0x3
	bne L_af_11
	fmr f22, f26
	fmr f21, f30
	b L_af_8
L_af_11:
	cmpwi r25, 0x4
	bne L_af_8
	fmr f22, f30
	fmr f21, f31
L_af_8:
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
	bne L_af_12
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b L_af_13
L_af_12:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq L_af_14
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b L_af_13
L_af_14:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x3c
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
L_af_13:
	cmplwi r3, 0x0
	bne L_af_15
	li r26, 0x0
	b L_af_16
L_af_15:
	lfs f1, 0x78(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_af_17
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_18
L_af_17:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_18:
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
	bne L_af_19
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_20
L_af_19:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_20:
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
	bne L_af_21
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_22
L_af_21:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_22:
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
	bne L_af_23
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_24
L_af_23:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_24:
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
	beq L_af_25
	lwz r5, 0x6c(r1)
	lwz r4, 0x70(r1)
	lwz r0, 0x74(r1)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
L_af_25:
	mr r26, r3
L_af_16:
	cmplwi r26, 0x0
	beq L_af_26
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
	ble L_af_27
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
	b L_af_28
L_af_27:
	lfd f0, 0x208(r27)
	fcmpo cr0, f3, f0
	bge L_af_29
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b L_af_28
L_af_29:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_30
	bge L_af_31
	cmpwi r3, 0x0
	beq L_af_32
	b L_af_31
L_af_30:
	clrlwi. r0, r4, 9
	beq L_af_33
	li r0, 0x1
	b L_af_34
L_af_33:
	li r0, 0x2
	b L_af_34
L_af_32:
	clrlwi. r0, r4, 9
	beq L_af_35
	li r0, 0x5
	b L_af_34
L_af_35:
	li r0, 0x3
	b L_af_34
L_af_31:
	li r0, 0x4
L_af_34:
	cmpwi r0, 0x1
	bne L_af_28
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
L_af_28:
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
	bge L_af_26
	stfs f5, 0x0(r24)
	mr r3, r26
	b L_af_2
L_af_26:
	addi r25, r25, 0x1
	cmpwi r25, 0x5
	blt L_af_6
	li r3, 0x0
L_af_2:
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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void marioChkGnd2(void) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		bl marioGetPtr
		opword 0x80030000
		opword 0x7C7F1B78
		opword 0x540003DF
		opword 0x40820130
		opword 0x881F003C
		opword 0x2C000002
		opword 0x41820020
		lfs f1, float_0p1_8041a7e4(r2)
		opword 0x3861000C
		opword 0xC05F007C
		opword 0x38810010
		opword 0x38A10008
		bl marioSearchGround
		opword 0x48000018
		lfs f1, float_0p1_8041a7e4(r2)
		opword 0x3861000C
		opword 0x38810010
		opword 0x38A10008
		bl kpaSearchGround
		opword 0x28030000
		opword 0x418200EC
		opword 0xC05F0090
		opword 0xC001000C
		lfs f1, float_0_8041a7a4(r2)
		opword 0xEC420028
		opword 0xFC020840
		opword 0x408000D4
		lfs f0, float_neg10_8041a804(r2)
		opword 0xFC020040
		opword 0x4C411382
		opword 0x408200C4
		opword 0x907F01E4
		opword 0x38000000
		opword 0xC001000C
		opword 0xD01F0090
		opword 0x807F0000
		opword 0x546306AE
		opword 0x907F0000
		opword 0xB01F0050
		opword 0xB01F0052
		opword 0x881F003C
		opword 0x2C000002
		opword 0x40820068
		opword 0xC01F0190
		opword 0xFC000800
		opword 0x40820010
		bl kpaFireAttackCheck
		opword 0x2C030000
		opword 0x40820040
		opword 0x887F024E
		opword 0x881F024F
		opword 0x7C630774
		opword 0x7C000774
		opword 0x7C6319D6
		opword 0x7C0001D6
		opword 0x7C030214
		opword 0x2C000BD1
		opword 0x40810010
		opword 0x38600002
		bl marioChgMot
		opword 0x48000018
		opword 0x38600001
		bl marioChgMot
		opword 0x4800000C
		opword 0x38600000
		bl marioChgMot
		bl quake_kpaLandOn
		opword 0x4800000C
		opword 0x38600000
		bl marioChgMot
		opword 0x881F003C
		opword 0x2C000002
		opword 0x41820018
		bl marioBgmodeChk
		opword 0x2C030000
		opword 0x40820010
		bl camFollowYOn
		opword 0x48000008
		bl kpaCamFollow
		opword 0x80010024
		opword 0x83E1001C
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioSearchGround(f32* y, f32* b, f32* c, f32 spd, f32 h) {
	char _af_pad[192];
	asm volatile {
		opword 0xFE400890
		lis r6, vec3_802c5730@ha
		opword 0xFFA01090
		opword 0x7C771B78
		opword 0x7C982378
		opword 0x7CB92B78
		addi r28, r6, vec3_802c5730@l
		bl marioGetPtr
		lfs f3, float_0_8041a7a4(r2)
		opword 0x7C7D1B78
		opword 0xD0630218
		opword 0xD063021C
		opword 0xD0630220
		opword 0xD0630214
		opword 0x80630000
		opword 0x546005AD
		opword 0x41820014
		opword 0xC01D0090
		opword 0x38600000
		opword 0xD0170000
		opword 0x480008E4
		opword 0x546005EF
		opword 0x41820014
		opword 0xC01D0090
		opword 0x38600000
		opword 0xD0170000
		opword 0x480008CC
		opword 0xC01D0090
		opword 0xFE409210
		lfs f2, float_0p01_8041a854(r2)
		opword 0xFC20EA10
		opword 0xD0170000
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0xEE52102A
		lfs f2, float_5_8041a7b8(r2)
		opword 0xD0180000
		opword 0xEE82082A
		opword 0xC01D0180
		opword 0xFC001800
		opword 0x41820018
		opword 0xC03D01A0
		opword 0xC01D0198
		opword 0xEC210028
		bl revise360
		opword 0x4800000C
		opword 0xC03D01A8
		bl toMovedir
		opword 0x801D0000
		opword 0x540002D7
		opword 0x41820054
		lfs f2, float_3p1416_8041a7e0(r2)
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEE610024
		opword 0xFC209890
		bl sin
		opword 0xFC600818
		opword 0xC01D01B4
		lfs f2, float_0p425_8041a864(r2)
		opword 0xFC209890
		opword 0xEC0000F2
		opword 0xEF020032
		bl cos
		opword 0xFC000818
		opword 0xC03D01B4
		lfs f2, float_0p425_8041a864(r2)
		opword 0xFC000050
		opword 0xEC010032
		opword 0xEEE20032
		opword 0x48000050
		lfs f2, float_3p1416_8041a7e0(r2)
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEE610024
		opword 0xFC209890
		bl sin
		opword 0xFC600818
		opword 0xC01D01B4
		lfs f2, float_0p375_8041a868(r2)
		opword 0xFC209890
		opword 0xEC0000F2
		opword 0xEF020032
		bl cos
		opword 0xFC000818
		opword 0xC03D01B4
		lfs f2, float_0p375_8041a868(r2)
		opword 0xFC000050
		opword 0xEC010032
		opword 0xEEE20032
		opword 0xC2BD0090
		opword 0xFF80B850
		opword 0x83DC0048
		opword 0xFF60C050
		opword 0x83FC004C
		opword 0xEE75A02A
		opword 0x82DC0050
		opword 0xEF54902A
		stw r30, _af_pad+68(r1)
		opword 0xC2DD008C
		opword 0x3B600000
		opword 0x93E10050
		opword 0x3B400000
		opword 0x92C10054
		opword 0xC29D0094
		lfs f25, float_neg10000_8041a858(r2)
		opword 0x2C1A0000
		opword 0x40820010
		lfs f31, float_0_8041a7a4(r2)
		opword 0xFFC0F890
		opword 0x48000050
		opword 0x2C1A0001
		opword 0x40820010
		opword 0xFFE0C090
		opword 0xFFC0B890
		opword 0x4800003C
		opword 0x2C1A0002
		opword 0x40820010
		opword 0xFFE0E090
		opword 0xFFC0C090
		opword 0x48000028
		opword 0x2C1A0003
		opword 0x40820010
		opword 0xFFE0B890
		opword 0xFFC0D890
		opword 0x48000014
		opword 0x2C1A0004
		opword 0x4082000C
		opword 0xFFE0D890
		opword 0xFFC0E090
		opword 0x809C0054
		opword 0xEC36F82A
		opword 0x807C0058
		opword 0xEC14F02A
		opword 0x801C005C
		opword 0x90810028
		opword 0x9061002C
		opword 0x90010030
		opword 0xD0210028
		opword 0xD261002C
		opword 0x80810028
		opword 0xD0010030
		opword 0x8061002C
		opword 0x80010030
		opword 0x90810064
		opword 0x90610068
		opword 0x9001006C
		opword 0x93C10070
		opword 0x93E10074
		opword 0x92C10078
		opword 0xD3410094
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610058
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610058
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610058
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000144
		opword 0x8001007C
		opword 0x80810080
		opword 0x90010040
		opword 0x80010084
		opword 0xC0210040
		lfs f0, float_0_8041a7a4(r2)
		opword 0x90810044
		opword 0xFC010040
		opword 0x90010048
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A0
		opword 0xEC43007A
		opword 0xC83C01F0
		opword 0xC0810044
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100B0
		opword 0xEC43013A
		opword 0xC83C01F0
		opword 0xC0810048
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD84100A8
		opword 0x800100AC
		opword 0x6C008000
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010044
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100C0
		opword 0x34010034
		opword 0xEC02013A
		opword 0xC83C01F0
		opword 0xFC00001E
		opword 0xD80100B8
		opword 0x800100BC
		opword 0x6C008000
		opword 0x900100C4
		opword 0xC80100C0
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010048
		opword 0x4182001C
		opword 0x80A10088
		opword 0x8081008C
		opword 0x80010090
		opword 0x90A10034
		opword 0x90810038
		opword 0x9001003C
		opword 0x28030000
		opword 0x7C741B78
		opword 0x41820210
		opword 0x801D0004
		opword 0x540001CF
		opword 0x4182000C
		lfs f18, float_75_8041a840(r2)
		opword 0x4800001C
		opword 0xA01D002E
		opword 0x28000010
		opword 0x4082000C
		lfs f18, float_75_8041a840(r2)
		opword 0x48000008
		lfs f18, float_50_8041a844(r2)
		bl marioGetPtr
		lfs f1, float_0_8041a7a4(r2)
		opword 0x7C751B78
		lfs f4, float_100_8041a7f8(r2)
		opword 0xC061003C
		opword 0xFC400890
		opword 0xC0010038
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		lfs f7, float_100_8041a7f8(r2)
		opword 0xEC810028
		lfs f0, float_0p5_8041a7c4(r2)
		lfs f2, float_0_8041a7a4(r2)
		opword 0xC0610034
		opword 0xECC7013A
		opword 0xC0010038
		opword 0x900100B8
		opword 0xFC201090
		opword 0xEC870032
		opword 0xC8BC01F0
		opword 0xFC00301E
		opword 0xEC6700F2
		opword 0xD80100C0
		opword 0x800100C4
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC80100B8
		opword 0xEC002828
		opword 0xEC003824
		opword 0xD0150218
		opword 0xD055021C
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		opword 0xC0410034
		opword 0xEC610028
		opword 0xC001003C
		lfs f5, float_100_8041a7f8(r2)
		opword 0xEC2200B2
		lfs f2, float_0p5_8041a7c4(r2)
		opword 0xEC000032
		opword 0xEC8510FA
		opword 0x900100A8
		opword 0xC85C01F0
		opword 0xEC61002A
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20201E
		opword 0xFC030040
		opword 0xD82100B0
		opword 0x800100B4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC001028
		opword 0xEC002824
		opword 0xD0150220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89C01F8
		opword 0xC85C0200
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81C0208
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD061000C
		opword 0x3C007F80
		opword 0x8081000C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_8041a7a4(r2)
		opword 0xC0010038
		opword 0xFC400890
		opword 0xFC800050
		bl angleABf
		opword 0xFC019040
		opword 0x4C411382
		opword 0x40820008
		li r20, 0x0
		opword 0x28140000
		opword 0x418202F8
		bl marioGetPtr
		lfs f1, float_0_8041a7a4(r2)
		opword 0x7C751B78
		lfs f4, float_100_8041a7f8(r2)
		opword 0xC061003C
		opword 0xFC400890
		opword 0xC0010038
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		lfs f7, float_100_8041a7f8(r2)
		opword 0xEC810028
		lfs f0, float_0p5_8041a7c4(r2)
		lfs f2, float_0_8041a7a4(r2)
		opword 0xC0610034
		opword 0xECC7013A
		opword 0xC0010038
		opword 0x900100B8
		opword 0xFC201090
		opword 0xEC870032
		opword 0xC8BC01F0
		opword 0xFC00301E
		opword 0xEC6700F2
		opword 0xD80100C0
		opword 0x800100C4
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC80100B8
		opword 0xEC002828
		opword 0xEC003824
		opword 0xD0150218
		opword 0xD055021C
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		opword 0xC0410034
		opword 0xEC610028
		opword 0xC001003C
		lfs f5, float_100_8041a7f8(r2)
		opword 0xEC2200B2
		lfs f2, float_0p5_8041a7c4(r2)
		opword 0xEC000032
		opword 0xEC8510FA
		opword 0x900100A8
		opword 0xC85C01F0
		opword 0xEC61002A
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20201E
		opword 0xFC030040
		opword 0xD82100B0
		opword 0x800100B4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC001028
		opword 0xEC002824
		opword 0xD0150220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89C01F8
		opword 0xC85C0200
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81C0208
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0610008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_8041a7a4(r2)
		opword 0xC0010038
		opword 0xFC400890
		opword 0xFC800050
		bl angleABf
		opword 0xC0410044
		opword 0xD03D0214
		opword 0xFC02A840
		opword 0x408000A8
		opword 0xEC22A828
		lfs f0, float_2_8041a7e8(r2)
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820090
		opword 0xFC00EA10
		opword 0xFC010040
		opword 0x4081002C
		opword 0xEC151028
		opword 0xC0610040
		opword 0xFC20B090
		opword 0xC0810048
		opword 0xFC40A090
		opword 0xFC000210
		opword 0xD0180000
		bl angleABf
		opword 0xD0390000
		opword 0x480000CC
		opword 0xFC02C840
		opword 0x408100C4
		opword 0xD0570000
		opword 0xFF201090
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20B090
		opword 0xFC40A090
		opword 0xC0610040
		opword 0xD0180000
		opword 0xC0810048
		bl angleABf
		opword 0xD0390000
		opword 0x3861001C
		opword 0x80A10040
		opword 0x80810044
		opword 0x80010048
		opword 0x90A1001C
		opword 0x90810020
		opword 0x90010024
		bl marioUpdateCamCollision
		opword 0x7E9BA378
		opword 0x48000074
		opword 0xC0410044
		lfs f0, float_11_8041a7ac(r2)
		opword 0xEC22A828
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820058
		opword 0xFC02C840
		opword 0x40810050
		opword 0xD0570000
		opword 0xFF201090
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20B090
		opword 0xFC40A090
		opword 0xC0610040
		opword 0xD0180000
		opword 0xC0810048
		bl angleABf
		opword 0xD0390000
		opword 0x38610010
		opword 0x80A10040
		opword 0x80810044
		opword 0x80010048
		opword 0x90A10010
		opword 0x90810014
		opword 0x90010018
		bl marioUpdateCamCollision
		opword 0x7E9BA378
		opword 0x3B5A0001
		opword 0x2C1A0005
		opword 0x4180F888
		opword 0x281B0000
		opword 0x4182000C
		opword 0x7F63DB78
		opword 0x48000008
		opword 0x38600000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioSearchGroundRoll(f32* y, f32* b, f32* c, f32 spd, f32 h) {
	char _af_pad[168];
	asm volatile {
		opword 0xFEE00890
		lis r6, vec3_802c5730@ha
		opword 0xFF001090
		opword 0x7C761B78
		opword 0x7C972378
		opword 0x7CB82B78
		addi r28, r6, vec3_802c5730@l
		bl marioGetPtr
		lfs f0, float_0_8041a7a4(r2)
		opword 0x7C7D1B78
		opword 0xD0030218
		opword 0xD003021C
		opword 0xD0030220
		opword 0x80630000
		opword 0x546005AD
		opword 0x41820014
		opword 0xC01D0090
		opword 0x38600000
		opword 0xD0160000
		opword 0x48000788
		opword 0x546005EF
		opword 0x41820014
		opword 0xC01D0090
		opword 0x38600000
		opword 0xD0160000
		opword 0x48000770
		opword 0xC05D01B8
		fabs f23, f23
		opword 0xC03D0090
		opword 0x3B600000
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0xD0360000
		lfs f1, float_0p01_8041a854(r2)
		opword 0xD0170000
		opword 0xEEF7082A
		lfs f28, float_neg10000_8041a858(r2)
		opword 0xC01D0214
		opword 0x809C0060
		opword 0xFC000210
		opword 0x807C0064
		opword 0x801C0068
		stw r4, _af_pad+48(r1)
		opword 0xFC000840
		opword 0xC35D0090
		opword 0x9061003C
		opword 0xC37D008C
		opword 0x90010040
		opword 0xC33D0094
		opword 0x40800014
		lfs f29, float_2_8041a7e8(r2)
		opword 0x3B400000
		opword 0x3B200004
		opword 0x48000010
		lfs f29, float_10_8041a7fc(r2)
		opword 0x3B400004
		opword 0x3B200007
		opword 0xEFFA102A
		opword 0x83C10038
		opword 0xEFC2B82A
		opword 0x82A1003C
		opword 0x82810040
		opword 0x575F103A
		opword 0x480006C0
		opword 0x281A0006
		opword 0x418101D0
		lis r3, jumptable_8030E5C0@ha
		addi r3, r3, jumptable_8030E5C0@l
		opword 0x7C03F82E
		opword 0x7C0903A6
		opword 0x4E800420
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD0010010
		opword 0xD001000C
		opword 0x480001AC
		lfs f1, float_90_8041a81c(r2)
		opword 0xC01D01A0
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC21002A
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEEE10024
		opword 0xFC20B890
		bl sin
		opword 0xFC400818
		lfs f0, float_8p64_8041a85c(r2)
		opword 0xFC20B890
		opword 0xEC0000B2
		opword 0xD0010010
		bl cos
		opword 0xFC000818
		lfs f1, float_8p64_8041a85c(r2)
		opword 0xFC000050
		opword 0xEC010032
		opword 0xD001000C
		opword 0x48000158
		opword 0xC03D01A0
		lfs f0, float_90_8041a81c(r2)
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC210028
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEEE10024
		opword 0xFC20B890
		bl sin
		opword 0xFC400818
		lfs f0, float_8p64_8041a85c(r2)
		opword 0xFC20B890
		opword 0xEC0000B2
		opword 0xD0010010
		bl cos
		opword 0xFC000818
		lfs f1, float_8p64_8041a85c(r2)
		opword 0xFC000050
		opword 0xEC010032
		opword 0xD001000C
		opword 0x48000104
		lfs f0, float_0_8041a7a4(r2)
		opword 0x38610010
		lfs f1, float_3_8041a7f0(r2)
		opword 0x3881000C
		opword 0xD0010010
		opword 0xD001000C
		opword 0xC05D01A0
		bl movePos
		opword 0x480000E0
		lfs f0, float_0_8041a7a4(r2)
		opword 0xD0010010
		opword 0xD001000C
		opword 0x480000D0
		lfs f1, float_90_8041a81c(r2)
		opword 0xC01D01A0
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC21002A
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEEE10024
		opword 0xFC20B890
		bl sin
		opword 0xFC400818
		lfs f0, float_8p64_8041a85c(r2)
		opword 0xFC20B890
		opword 0xEC0000B2
		opword 0xD0010010
		bl cos
		opword 0xFC000818
		lfs f2, float_8p64_8041a85c(r2)
		lfs f1, float_3_8041a7f0(r2)
		opword 0x38610010
		opword 0x3881000C
		opword 0xFC000050
		opword 0xEC020032
		opword 0xD001000C
		opword 0xC05D01A0
		bl movePos
		opword 0x48000068
		opword 0xC03D01A0
		lfs f0, float_90_8041a81c(r2)
		lfs f2, float_3p1416_8041a7e0(r2)
		opword 0xEC210028
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEEE10024
		opword 0xFC20B890
		bl sin
		opword 0xFC400818
		lfs f0, float_8p64_8041a85c(r2)
		opword 0xFC20B890
		opword 0xEC0000B2
		opword 0xD0010010
		bl cos
		opword 0xFC000818
		lfs f2, float_8p64_8041a85c(r2)
		lfs f1, float_3_8041a7f0(r2)
		opword 0x38610010
		opword 0x3881000C
		opword 0xFC000050
		opword 0xEC020032
		opword 0xD001000C
		opword 0xC05D01A0
		bl movePos
		opword 0xC0210010
		opword 0xC001000C
		opword 0x809C006C
		opword 0xEC3B082A
		opword 0x807C0070
		opword 0xEC19002A
		opword 0x801C0074
		opword 0x90810014
		opword 0x90610018
		opword 0x9001001C
		opword 0xD0210014
		opword 0xD3E10018
		opword 0x80810014
		opword 0xD001001C
		opword 0x80610018
		opword 0x8001001C
		opword 0x90810050
		opword 0x90610054
		opword 0x90010058
		opword 0x93C1005C
		opword 0x92A10060
		opword 0x92810064
		opword 0xD3C10080
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610044
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610044
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610044
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		li r18, 0x0
		opword 0x48000148
		opword 0x80010068
		opword 0x8081006C
		opword 0x9001002C
		opword 0x80010070
		opword 0xC021002C
		lfs f0, float_0_8041a7a4(r2)
		opword 0x90810030
		opword 0xFC010040
		opword 0x90010034
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010090
		opword 0xEC43007A
		opword 0xC83C01F0
		opword 0xC0810030
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410088
		opword 0x8001008C
		opword 0x6C008000
		opword 0x90010094
		opword 0xC8010090
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001002C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A0
		opword 0xEC43013A
		opword 0xC83C01F0
		opword 0xC0810034
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010030
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100B0
		opword 0x34010020
		opword 0xEC02013A
		opword 0xC83C01F0
		opword 0xFC00001E
		opword 0xD80100A8
		opword 0x800100AC
		opword 0x6C008000
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010034
		opword 0x4182001C
		opword 0x80A10074
		opword 0x80810078
		opword 0x8001007C
		opword 0x90A10020
		opword 0x90810024
		opword 0x90010028
		opword 0x7C721B78
		opword 0x28120000
		opword 0x418202D4
		bl marioGetPtr
		lfs f1, float_0_8041a7a4(r2)
		opword 0x7C731B78
		lfs f4, float_100_8041a7f8(r2)
		opword 0xC0610028
		opword 0xFC400890
		opword 0xC0010024
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		lfs f7, float_100_8041a7f8(r2)
		opword 0xEC810028
		lfs f0, float_0p5_8041a7c4(r2)
		lfs f2, float_0_8041a7a4(r2)
		opword 0xC0610020
		opword 0xECC7013A
		opword 0xC0010024
		opword 0x900100A8
		opword 0xFC201090
		opword 0xEC870032
		opword 0xC8BC01F0
		opword 0xFC00301E
		opword 0xEC6700F2
		opword 0xD80100B0
		opword 0x800100B4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC002828
		opword 0xEC003824
		opword 0xD0130218
		opword 0xD053021C
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		opword 0xC0410020
		opword 0xEC610028
		opword 0xC0010028
		lfs f5, float_100_8041a7f8(r2)
		opword 0xEC2200B2
		lfs f2, float_0p5_8041a7c4(r2)
		opword 0xEC000032
		opword 0xEC8510FA
		opword 0x90010098
		opword 0xC85C01F0
		opword 0xEC61002A
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20201E
		opword 0xFC030040
		opword 0xD82100A0
		opword 0x800100A4
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC001028
		opword 0xEC002824
		opword 0xD0130220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89C01F8
		opword 0xC85C0200
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81C0208
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0610008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_8041a7a4(r2)
		opword 0xC0010024
		opword 0xFC400890
		opword 0xFC800050
		bl angleABf
		lfs f0, float_105_8041a860(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820014
		lfs f0, float_75_8041a840(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x418200E4
		opword 0xC0410030
		opword 0xD03D0214
		opword 0xFC02D040
		opword 0x40800084
		opword 0xEC02D028
		opword 0xFC200210
		opword 0xFC01E840
		opword 0x4C411382
		opword 0x40820070
		opword 0xFC00C210
		opword 0xFC010040
		opword 0x4081002C
		opword 0xEC1A1028
		opword 0xC061002C
		opword 0xFC20D890
		opword 0xC0810034
		opword 0xFC40C890
		opword 0xFC000210
		opword 0xD0170000
		bl angleABf
		opword 0xD0380000
		opword 0x4800008C
		opword 0xFC02E040
		opword 0x40810084
		opword 0xD0560000
		opword 0xFF801090
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20D890
		opword 0xFC40C890
		opword 0xC061002C
		opword 0xD0170000
		opword 0xC0810034
		bl angleABf
		opword 0xD0380000
		opword 0x7E5B9378
		opword 0x48000054
		opword 0xC0410030
		lfs f0, float_11_8041a7ac(r2)
		opword 0xEC22D028
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820038
		opword 0xFC02E040
		opword 0x40810030
		opword 0xD0560000
		opword 0xFF801090
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20D890
		opword 0xFC40C890
		opword 0xC061002C
		opword 0xD0170000
		opword 0xC0810034
		bl angleABf
		opword 0xD0380000
		opword 0x7E5B9378
		opword 0x3B5A0001
		opword 0x3BFF0004
		opword 0x7C1AC800
		opword 0x4180F940
		opword 0x281B0000
		opword 0x4182000C
		opword 0x7F63DB78
		opword 0x48000008
		opword 0x38600000
	}
}
#pragma pop

void marioChkToge(void) {
    MarioWork* w = marioGetPtr();
    s32 attr;
    if (vivianGetStatus() == 2 || vivianGetStatus() == 1 || vivianGetStatus() == 3) {
        return;
    }
    if (w->hitobjFront != NULL) {
        attr = hitGetAttr(w->hitobjFront);
        if (w->currMotionId != 0x20 && (attr & 0x800) && MF(w, 0x210, f32) < EXT_LIT(float_0p5_8041a7c4, 0.5f) * w->wPlayerCollisionBox.x) {
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

#pragma dont_inline on
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
#pragma dont_inline reset

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioLandonChk_old(f32* outY, f32 spd) {
	char _af_pad[184];
	asm volatile {
		opword 0xFDC00890
		lis r4, vec3_802c5730@ha
		opword 0x7C7B1B78
		addi r30, r4, vec3_802c5730@l
		bl marioGetPtr
		lfs f5, float_0_8041a7a4(r2)
		opword 0x7C7F1B78
		opword 0xD0A30218
		opword 0xD0A3021C
		opword 0xD0A30220
		opword 0xD0A30214
		opword 0x80630000
		opword 0x546005AD
		opword 0x41820014
		opword 0xC01F0090
		opword 0x38600000
		opword 0xD01B0000
		opword 0x48000648
		opword 0x546005EF
		opword 0x41820014
		opword 0xC01F0090
		opword 0x38600000
		opword 0xD01B0000
		opword 0x48000630
		opword 0xFC607210
		lfs f4, float_0p01_8041a854(r2)
		opword 0xC01F0180
		lfs f2, float_0p75_8041a7d8(r2)
		opword 0xC03F01B8
		opword 0xFC002800
		opword 0xEDE4182A
		fmuls f14, f2, f1
		opword 0x41820018
		opword 0xC03F01A0
		opword 0xC01F0198
		opword 0xEC210028
		bl revise360
		opword 0x4800000C
		opword 0xC03F01A8
		bl toMovedir
		lfs f2, float_3p1416_8041a7e0(r2)
		lfs f0, float_180_8041a7cc(r2)
		opword 0xEC220072
		opword 0xEE010024
		opword 0xFC208090
		bl sin
		opword 0xFC600818
		opword 0xC01F01B4
		lfs f2, float_0p25_8041a7d4(r2)
		opword 0xFC208090
		opword 0xEC0000F2
		opword 0xEE820032
		bl cos
		opword 0xFC000818
		opword 0x881F003C
		opword 0xC03F01B4
		lfs f2, float_0p25_8041a7d4(r2)
		opword 0x2C000002
		opword 0xFC000050
		opword 0xC2BF008C
		opword 0xC07F0090
		opword 0xEC010032
		opword 0xC25F0094
		opword 0xEE620032
		opword 0x40820024
		lfs f1, float_11_8041a7ac(r2)
		la r3, _af_pad+12
		opword 0x38810010
		opword 0x38A1000C
		bl kpaSearchGround
		opword 0xC0010014
		opword 0xD01B0000
		opword 0x4800056C
		opword 0xFF209850
		lfs f27, float_0_8041a7a4(r2)
		opword 0xFF00A050
		lfs f28, float_neg1_8041a7dc(r2)
		opword 0xEEEE782A
		opword 0x3B800000
		opword 0xEEC3702A
		opword 0x2C1C0000
		opword 0x40820010
		lfs f30, float_0_8041a7a4(r2)
		opword 0xFFA0F090
		opword 0x48000050
		opword 0x2C1C0001
		opword 0x40820010
		opword 0xFFC0A090
		opword 0xFFA09890
		opword 0x4800003C
		opword 0x2C1C0002
		opword 0x40820010
		opword 0xFFC0C890
		opword 0xFFA09890
		opword 0x48000028
		opword 0x2C1C0003
		opword 0x40820010
		opword 0xFFC09890
		opword 0xFFA0C090
		opword 0x48000014
		opword 0x2C1C0004
		opword 0x4082000C
		opword 0xFFC0C090
		opword 0xFFA0C890
		opword 0x80FE0000
		opword 0xEC35F02A
		opword 0x80DE0004
		opword 0xEC12E82A
		opword 0x80BE0008
		opword 0xFF40B890
		opword 0x809E000C
		opword 0x807E0010
		opword 0x801E0014
		opword 0x90E10030
		opword 0x90C10034
		opword 0x90A10038
		opword 0x9081003C
		opword 0x90610040
		opword 0x90010044
		opword 0xD0210030
		opword 0xD2C10034
		opword 0x80E10030
		opword 0xD0010038
		opword 0x80C10034
		opword 0xD361003C
		opword 0x80A10038
		opword 0xD3810040
		opword 0x8081003C
		opword 0xD3610044
		opword 0x80610040
		opword 0x80010044
		opword 0x90E10054
		opword 0x90C10058
		opword 0x90A1005C
		opword 0x90810060
		opword 0x90610064
		opword 0x90010068
		opword 0xD2E10084
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610048
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610048
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610048
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x3BA00000
		opword 0x4800019C
		opword 0xC0210084
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3CA04330
		opword 0x8001006C
		opword 0xEC02007A
		opword 0x80810070
		opword 0x90010018
		opword 0x80010074
		opword 0xFC00001E
		opword 0x90A10090
		opword 0xC83E01F0
		opword 0xC0810018
		opword 0xD8010088
		lfs f0, float_0_8041a7a4(r2)
		opword 0x80A1008C
		opword 0xFC040040
		opword 0x9081001C
		opword 0x6CA48000
		opword 0x90810094
		opword 0xC8010090
		opword 0x90010020
		opword 0xEC000828
		opword 0xEF401024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A0
		opword 0xEC43013A
		opword 0xC83E01F0
		opword 0xC081001C
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD8410098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010018
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100B0
		opword 0xEC43013A
		opword 0xC83E01F0
		opword 0xC0810020
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC40101E
		opword 0xFC040040
		opword 0xD84100A8
		opword 0x800100AC
		opword 0x6C008000
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001001C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100C0
		opword 0x34010024
		opword 0xEC02013A
		opword 0xC83E01F0
		opword 0xFC00001E
		opword 0xD80100B8
		opword 0x800100BC
		opword 0x6C008000
		opword 0x900100C4
		opword 0xC80100C0
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010020
		opword 0x4182001C
		opword 0x80A10078
		opword 0x8081007C
		opword 0x80010080
		opword 0x90A10024
		opword 0x90810028
		opword 0x9001002C
		opword 0x7C7D1B78
		opword 0x281D0000
		opword 0xC221001C
		opword 0xC2010024
		opword 0xC3E10028
		opword 0xC1E1002C
		opword 0x41820240
		bl marioGetPtr
		lfs f0, float_100_8041a7f8(r2)
		mr r26, r3
		lfs f1, float_0_8041a7a4(r2)
		opword 0xEDC007F2
		opword 0xFC400890
		opword 0xEC6003F2
		opword 0xFC807090
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		lfs f6, float_100_8041a7f8(r2)
		opword 0xFC807090
		opword 0xEC410028
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x900100B8
		opword 0xEC660432
		opword 0xC8BE01F0
		opword 0xEC0600BA
		lfs f1, float_0_8041a7a4(r2)
		opword 0xFC00001E
		opword 0xFC400890
		opword 0xD80100C0
		opword 0x800100C4
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC80100B8
		opword 0xEC002828
		opword 0xEC003024
		opword 0xD01A0218
		opword 0xD03A021C
		bl angleABf
		lfs f0, float_180_8041a7cc(r2)
		opword 0x3C004330
		opword 0xEC4F03F2
		lfs f5, float_100_8041a7f8(r2)
		opword 0xEC610028
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x900100A8
		opword 0xC83E01F0
		opword 0xEC8500FA
		lfs f0, float_0_8041a7a4(r2)
		opword 0xEC70143A
		opword 0xFC40201E
		opword 0xFC030040
		opword 0xD84100B0
		opword 0x800100B4
		opword 0x6C008000
		opword 0x900100AC
		opword 0xC80100A8
		opword 0xEC000828
		opword 0xEC002824
		opword 0xD01A0220
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89E01F8
		opword 0xC85E0200
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81E0208
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0610008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_8041a7a4(r2)
		opword 0xFC80F850
		opword 0xFC400890
		bl angleABf
		opword 0xEC168828
		opword 0x3C004330
		lfs f5, float_100_8041a7f8(r2)
		lfs f4, float_0p5_8041a7c4(r2)
		opword 0xEC60D028
		opword 0x900100B8
		opword 0xC85E01F0
		lfs f0, float_0p1_8041a7e4(r2)
		opword 0xEC6520FA
		opword 0xD03F0214
		opword 0xFC20181E
		opword 0xD82100C0
		opword 0x806100C4
		opword 0x6C638000
		opword 0x906100BC
		opword 0xC82100B8
		opword 0xEC211028
		opword 0xEC212824
		opword 0xFC200A10
		opword 0xFC010040
		opword 0x40800038
		opword 0xEC05247A
		opword 0x900100B8
		opword 0x7FA3EB78
		opword 0xFC00001E
		opword 0xD80100C0
		opword 0x800100C4
		opword 0x6C008000
		opword 0x900100BC
		opword 0xC80100B8
		opword 0xEC001028
		opword 0xEC002824
		opword 0xD01B0000
		opword 0x48000014
		opword 0x3B9C0001
		opword 0x2C1C0005
		opword 0x4180FABC
		opword 0x38600000
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
	beq L_af_1
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq L_af_1
	bl vivianGetStatus
	cmpwi r3, 0x3
	bne L_af_2
L_af_1:
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
	beq L_af_3
	lfs f0, float_0p5_8041a7c4(r2)
	fmuls f1, f1, f0
L_af_3:
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
	bne L_af_4
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b L_af_5
L_af_4:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq L_af_6
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b L_af_5
L_af_6:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x110
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
L_af_5:
	cmplwi r3, 0x0
	bne L_af_7
	li r3, 0x0
	b L_af_8
L_af_7:
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
	bne L_af_9
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_10
L_af_9:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_10:
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
	bne L_af_11
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_12
L_af_11:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_12:
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
	bne L_af_13
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_14
L_af_13:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_14:
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
	beq L_af_8
	lwz r5, 0x140(r1)
	lwz r4, 0x144(r1)
	lwz r0, 0x148(r1)
	stw r5, 0x84(r1)
	stw r4, 0x88(r1)
	stw r0, 0x8c(r1)
L_af_8:
	cmplwi r3, 0x0
	beq L_af_15
	lfs f0, 0x7c(r1)
	b L_af_16
L_af_15:
	lfs f0, float_neg3000_8041a870(r2)
L_af_16:
	stfs f0, 0x1c0(r29)
	stw r3, 0x1f8(r31)
	b L_af_17
L_af_2:
	li r0, 0x0
	stw r0, 0x1e4(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne L_af_18
	bl kpaClearHitobjRide
L_af_18:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r29, r3
	lfs f1, 0x1b8(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq L_af_19
	lfs f0, float_0p5_8041a7c4(r2)
	fmuls f1, f1, f0
L_af_19:
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
	bne L_af_20
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b L_af_21
L_af_20:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq L_af_22
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b L_af_21
L_af_22:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0xd0
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
L_af_21:
	cmplwi r3, 0x0
	bne L_af_23
	li r3, 0x0
	b L_af_24
L_af_23:
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
	bne L_af_25
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_26
L_af_25:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_26:
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
	bne L_af_27
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_28
L_af_27:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_28:
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
	bne L_af_29
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_30
L_af_29:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_30:
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
	beq L_af_24
	lwz r5, 0x100(r1)
	lwz r4, 0x104(r1)
	lwz r0, 0x108(r1)
	stw r5, 0x60(r1)
	stw r4, 0x64(r1)
	stw r0, 0x68(r1)
L_af_24:
	cmplwi r3, 0x0
	beq L_af_31
	lfs f0, 0x58(r1)
	b L_af_32
L_af_31:
	lfs f0, float_neg3000_8041a870(r2)
L_af_32:
	stfs f0, 0x1c0(r29)
	stw r3, 0x1f8(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 15
	bne L_af_17
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq L_af_33
	li r0, 0x0
	b L_af_34
L_af_33:
	lfs f1, 0x90(r3)
	lfs f0, float_5000_8041a874(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_af_35
	li r0, 0x0
	b L_af_34
L_af_35:
	li r0, 0x1
L_af_34:
	cmpwi r0, 0x0
	beq L_af_17
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 22, 22
	bne L_af_36
	rlwinm. r0, r3, 0, 7, 7
	beq L_af_37
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x1c
	lfs f2, 0x7c(r31)
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl marioSearchGroundRoll
	cmplwi r3, 0x0
	beq L_af_38
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
	b L_af_38
L_af_37:
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne L_af_39
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x1c
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl kpaSearchGround
	b L_af_40
L_af_39:
	lfs f1, float_11_8041a7ac(r2)
	addi r3, r1, 0x1c
	lfs f2, 0x7c(r31)
	addi r4, r1, 0x20
	addi r5, r1, 0x18
	bl marioSearchGround
L_af_40:
	cmplwi r3, 0x0
	beq L_af_38
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
	b L_af_38
L_af_36:
	lfs f0, 0x90(r31)
	stfs f0, 0x1c(r1)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne L_af_41
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne L_af_38
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
	b L_af_17
L_af_41:
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne L_af_38
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
	b L_af_17
L_af_38:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x19
	bne L_af_42
	bl marioChkShipMoveMode
	cmpwi r3, 0x0
	beq L_af_17
	lwz r0, 0x1e4(r31)
	cmplwi r0, 0x0
	bne L_af_43
	bl marioShipChgFall
	b L_af_17
L_af_43:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 15, 13
	stw r0, 0x0(r31)
	b L_af_17
L_af_42:
	cmplwi r0, 0x1f
	beq L_af_44
	lwz r3, 0x1e4(r31)
	cmplwi r3, 0x0
	beq L_af_44
	bl hitGetAttr
	rlwinm. r0, r3, 0, 22, 22
	beq L_af_44
	lfs f1, 0x7c(r31)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_af_45
	bl marioSetFallPara
L_af_45:
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x1f
	bl marioChgMot
	b L_af_17
L_af_44:
	lwz r3, 0x1e4(r31)
	cmplwi r3, 0x0
	beq L_af_46
	bl hitGetAttr
	rlwinm. r0, r3, 0, 20, 20
	beq L_af_46
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq L_af_17
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq L_af_17
	bl vivianGetStatus
	cmpwi r3, 0x3
	beq L_af_17
	lfs f1, 0x90(r31)
	bl set_damage_root_ypos
	li r3, 0x20
	bl marioChgMot
	b L_af_17
L_af_46:
	lha r0, 0x50(r31)
	cmpwi r0, 0x0
	bne L_af_47
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne L_af_48
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	bl marioChkFrontStep
	lfs f2, 0x14(r1)
	cmplwi r3, 0x0
	lfs f0, 0x90(r31)
	fsubs f1, f2, f0
	beq L_af_47
	lfs f0, float_11_8041a7ac(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne L_af_47
	lfs f0, float_5_8041a7b8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_af_47
	lfs f1, 0x214(r31)
	lfs f0, float_30_8041a82c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne L_af_47
	stfs f2, 0x1c4(r31)
	lfs f0, float_0_8041a7a4(r2)
	lfs f1, 0x180(r31)
	fcmpu cr0, f1, f0
	beq L_af_47
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne L_af_49
	li r3, 0xc
	bl marioChgMot
	b L_af_17
L_af_49:
	li r3, 0xc
	li r4, 0x0
	bl marioChgMotSub
	b L_af_17
L_af_48:
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	bl marioChkFrontStep
	lfs f2, 0x14(r1)
	cmplwi r3, 0x0
	lfs f0, 0x90(r31)
	fsubs f1, f2, f0
	beq L_af_47
	lfs f0, float_11_8041a7ac(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne L_af_47
	lfs f0, float_5_8041a7b8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_af_47
	lfs f1, 0x214(r31)
	lfs f0, float_30_8041a82c(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne L_af_47
	stfs f2, 0x1c4(r31)
	lfs f0, float_0_8041a7a4(r2)
	lfs f1, 0x180(r31)
	fcmpu cr0, f1, f0
	beq L_af_47
	bl roll_upstairs_on
	b L_af_17
L_af_47:
	lfs f0, 0x1c(r1)
	stfs f0, 0x90(r31)
	lbz r0, 0x3c(r31)
	cmpwi r0, 0x2
	bne L_af_50
	bl kpaChkHitobjRide
	b L_af_51
L_af_50:
	lwz r3, 0x1e4(r31)
L_af_51:
	cmplwi r3, 0x0
	beq L_af_52
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	beq L_af_17
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
	bne L_af_53
	lis r4, chkfilterVecVivian@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVecVivian@l
	bl hitCheckVecFilter
	b L_af_54
L_af_53:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 7, 7
	beq L_af_55
	lis r4, chkfilterVecRoll@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVecRoll@l
	bl hitCheckVecFilter
	b L_af_54
L_af_55:
	lis r4, chkfilterVec@ha
	addi r3, r1, 0x90
	addi r4, r4, chkfilterVec@l
	bl hitCheckVecFilter
L_af_54:
	cmplwi r3, 0x0
	bne L_af_56
	li r29, 0x0
	b L_af_57
L_af_56:
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
	bne L_af_58
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_59
L_af_58:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_59:
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
	bne L_af_60
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_61
L_af_60:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_61:
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
	bne L_af_62
	lfs f0, float_0p5_8041a7c4(r2)
	b L_af_63
L_af_62:
	lfs f0, float_neg0p5_8041a7c8(r2)
L_af_63:
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
	beq L_af_64
	lwz r5, 0xc0(r1)
	lwz r4, 0xc4(r1)
	lwz r0, 0xc8(r1)
	stw r5, 0x3c(r1)
	stw r4, 0x40(r1)
	stw r0, 0x44(r1)
L_af_64:
	mr r29, r3
L_af_57:
	cmplwi r29, 0x0
	beq L_af_65
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
	ble L_af_66
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
	b L_af_67
L_af_66:
	lfd f0, 0x208(r30)
	fcmpo cr0, f3, f0
	bge L_af_68
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b L_af_67
L_af_68:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq L_af_69
	bge L_af_70
	cmpwi r3, 0x0
	beq L_af_71
	b L_af_70
L_af_69:
	clrlwi. r0, r4, 9
	beq L_af_72
	li r0, 0x1
	b L_af_73
L_af_72:
	li r0, 0x2
	b L_af_73
L_af_71:
	clrlwi. r0, r4, 9
	beq L_af_74
	li r0, 0x5
	b L_af_73
L_af_74:
	li r0, 0x3
	b L_af_73
L_af_70:
	li r0, 0x4
L_af_73:
	cmpwi r0, 0x1
	bne L_af_67
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
L_af_67:
	lfs f1, float_0_8041a7a4(r2)
	lfs f0, 0x40(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
L_af_65:
	cmplwi r29, 0x0
	beq L_af_17
	stfs f31, roll_grx(r13)
	stfs f30, roll_grz(r13)
	b L_af_17
L_af_52:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 7, 7
	bne L_af_75
	rlwinm. r0, r3, 0, 14, 14
	bne L_af_17
	lfs f1, 0x20(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	bge L_af_76
	li r3, 0xa
	bl marioChgMot
	bl marioSetFallPara
L_af_76:
	lfs f1, 0x20(r1)
	lfs f0, float_0_8041a7a4(r2)
	fcmpo cr0, f1, f0
	ble L_af_17
	li r3, 0xb
	bl marioChgMot
	bl marioSetFallPara
	b L_af_17
L_af_75:
	rlwinm. r0, r3, 0, 14, 14
	bne L_af_17
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
L_af_17:
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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void marioHitCheckWidth(void) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		bl marioGetPtr
		opword 0x80830000
		opword 0x548002D7
		opword 0x40820038
		opword 0x548001CF
		opword 0x4082000C
		opword 0xC04301B4
		opword 0x48000008
		lfs f2, float_18_8041a850(r2)
		opword 0xC02301BC
		lfs f0, float_1_8041a7bc(r2)
		opword 0xEC01002A
		opword 0xFC001040
		opword 0xD00301BC
		opword 0x4081005C
		opword 0xD04301BC
		opword 0x48000054
		opword 0xC04301BC
		lfs f1, float_6_8041a88c(r2)
		opword 0xFC020840
		opword 0x4081001C
		lfs f0, float_1_8041a7bc(r2)
		opword 0xEC020028
		opword 0xFC000840
		opword 0xD00301BC
		opword 0x40800008
		opword 0xD02301BC
		opword 0xC04301BC
		lfs f1, float_6_8041a88c(r2)
		opword 0xFC020840
		opword 0x4080001C
		lfs f0, float_1_8041a7bc(r2)
		opword 0xEC02002A
		opword 0xFC000840
		opword 0xD00301BC
		opword 0x40810008
		opword 0xD02301BC
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

BOOL chkFilterAttr2(HitCheckQuery* query, HitEntry* entry) {
    s32 ret = 0;
    s32 attr = entry->attributes;
    if ((attr & query->user0) == 0 || (attr & query->user1) != 0) {
        ret = 1;
    }
    return ret;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
BOOL chkfilterVec(HitCheckQuery* query, HitEntry* entry) {
	asm {
		lis r3, 0x8
		addi r0, r3, 0x80
		lis r3, vec3_802c5730@ha
		addi r30, r3, vec3_802c5730@l
	}
	asm volatile {
		mr r29, r4
		opword 0x80840004
		opword 0x7C800039
		opword 0x4182000C
		opword 0x38600001
		opword 0x48000088
		opword 0x54800211
		opword 0x40820014
		opword 0x5480077B
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000070
		opword 0x54800001
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000060
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x7C7F1B78
		opword 0x389E0274
		opword 0x387F0015
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F0015
		opword 0x389E028C
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F0015
		opword 0x389E02A4
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x38600000
		opword 0x48000008
		opword 0x38600001
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
BOOL chkfilterVecRoll(HitCheckQuery* query, HitEntry* entry) {
	asm {
		lis r3, vec3_802c5730@ha
		addi r30, r3, vec3_802c5730@l
	}
	asm volatile {
		mr r29, r4
		opword 0x80840004
		opword 0x54800631
		opword 0x4182000C
		opword 0x38600001
		opword 0x48000090
		opword 0x54800211
		opword 0x4082001C
		opword 0x3C600008
		opword 0x38030004
		opword 0x7C800039
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000070
		opword 0x54800001
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000060
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x7C7F1B78
		opword 0x389E0274
		opword 0x387F0015
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F0015
		opword 0x389E028C
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F0015
		opword 0x389E02A4
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x38600000
		opword 0x48000008
		opword 0x38600001
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
BOOL chkfilterVecVivian(HitCheckQuery* query, HitEntry* entry) {
	asm {
		lis r3, 0x8
		addi r0, r3, 0x804
		lis r3, vec3_802c5730@ha
		addi r30, r3, vec3_802c5730@l
	}
	asm volatile {
		mr r29, r4
		opword 0x80840004
		opword 0x7C800039
		opword 0x41820014
		opword 0x54800211
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000070
		opword 0x54800001
		opword 0x4082000C
		opword 0x38600001
		opword 0x48000060
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x7C7F1B78
		opword 0x389E0274
		opword 0x387F0015
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F0015
		opword 0x389E028C
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F0015
		opword 0x389E02A4
		bl strcmp
		opword 0x2C030000
		opword 0x40820014
		opword 0x7FA3EB78
		bl mobjHitObjPtrToPtr
		opword 0x38600000
		opword 0x48000008
		opword 0x38600001
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* marioHitCheckVec(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
	asm volatile {
		opword 0x9421FF70
		opword 0x7C0802A6
		opword 0x90010094
		opword 0x93E1008C
		opword 0x7CFF3B78
		opword 0x93C10088
		opword 0x7CDE3378
		opword 0x93A10084
		opword 0x7CBD2B78
		opword 0x81030000
		opword 0x80030004
		opword 0x91010014
		opword 0x90010018
		opword 0x80030008
		opword 0x9001001C
		opword 0x80640000
		opword 0x80040004
		opword 0x90610020
		opword 0x90010024
		opword 0x80040008
		opword 0x90010028
		opword 0xC0070000
		opword 0xD0010044
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610008
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610008
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610008
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001B4
		opword 0xC0210044
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010050
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0x281D0000
		opword 0xFC00001E
		opword 0xD8010048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010054
		opword 0xC8010050
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01F0000
		opword 0x41820130
		opword 0x8081002C
		opword 0x80010030
		lfs f0, float_0_8041a7a4(r2)
		opword 0x909D0000
		opword 0x901D0004
		opword 0x80010034
		opword 0x901D0008
		opword 0xC03D0000
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010048
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210050
		opword 0x80010054
		opword 0x6C008000
		opword 0x9001004C
		opword 0xC8210048
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03D0000
		opword 0xC03D0004
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010060
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210058
		opword 0x8001005C
		opword 0x6C008000
		opword 0x90010064
		opword 0xC8210060
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03D0004
		opword 0xC03D0008
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010070
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010068
		opword 0x8001006C
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01D0008
		opword 0x281E0000
		opword 0x4182001C
		opword 0x80810038
		opword 0x8001003C
		opword 0x909E0000
		opword 0x901E0004
		opword 0x80010040
		opword 0x901E0008
		opword 0x80010094
		opword 0x83E1008C
		opword 0x83C10088
		opword 0x83A10084
		opword 0x7C0803A6
		opword 0x38210090
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* marioHitCheck(f32* ox, f32* oy, f32* oz, f32* dist, f32* nx, f32* ny, f32* nz, f32 x, f32 y, f32 z, f32 dx,
                        f32 dy, f32 dz) {
	char _af_pad[180];
	asm volatile {
		lis r11, vec3_802c5730@ha
		lis r10, vec3_802c573c@ha
		addi r26, r11, vec3_802c5730@l
		opword 0x7CDC3378
		addi r6, r10, vec3_802c573c@l
		opword 0x819A0000
		opword 0x817A0004
		mr r25, r3
		opword 0x815A0008
		opword 0x7C9A2378
		opword 0x80860000
		opword 0x7CBB2B78
		opword 0x80660004
		opword 0x7CFD3B78
		opword 0x80060008
		opword 0x7D1E4378
		stw r12, _af_pad+12(r1)
		opword 0x7D3F4B78
		lfs f31, 0x0(r28)
		opword 0x91610018
		opword 0x9141001C
		opword 0x90810008
		opword 0x9061000C
		opword 0x90010010
		opword 0xD0210014
		opword 0xD0410018
		opword 0x80E10014
		opword 0xD061001C
		opword 0x80C10018
		opword 0xD0810008
		opword 0x80A1001C
		opword 0xD0A1000C
		opword 0x80810008
		opword 0xD0C10010
		opword 0x8061000C
		opword 0x80010010
		opword 0x90E10044
		opword 0x90C10048
		opword 0x90A1004C
		opword 0x90810050
		opword 0x90610054
		opword 0x90010058
		opword 0xD3E10074
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610038
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610038
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610038
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001AC
		opword 0xC0210074
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3CA04330
		lis r4, double_to_int_802c5920@ha
		opword 0x8001005C
		opword 0xEC02007A
		addi r6, r4, double_to_int_802c5920@l
		opword 0x9001002C
		opword 0x80810060
		opword 0xFC00001E
		opword 0x80010064
		opword 0x90A10080
		opword 0xC8260000
		opword 0xD8010078
		opword 0xC081002C
		opword 0x80A1007C
		lfs f0, float_0_8041a7a4(r2)
		opword 0x6CA58000
		opword 0x90810030
		opword 0xFC040040
		opword 0x90A10084
		opword 0xC8010080
		opword 0x90010034
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010090
		opword 0xEC03013A
		opword 0xC0810030
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410088
		opword 0x8001008C
		opword 0x6C008000
		opword 0x90010094
		opword 0xC8010090
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD001002C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x900100A0
		opword 0xEC03013A
		opword 0xC0810034
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010030
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100B0
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x34010020
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD80100A8
		opword 0x800100AC
		opword 0x6C008000
		opword 0x900100B4
		opword 0xC80100B0
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010034
		opword 0x4182001C
		opword 0x80A10068
		opword 0x8081006C
		opword 0x80010070
		opword 0x90A10020
		opword 0x90810024
		opword 0x90010028
		opword 0xD3FC0000
		opword 0xC021002C
		opword 0xC0010030
		opword 0xD0390000
		opword 0xC0210034
		opword 0xD01A0000
		opword 0xC0010020
		opword 0xD03B0000
		opword 0xC0210024
		opword 0xD01D0000
		opword 0xC0010028
		opword 0xD03E0000
		opword 0xD01F0000
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* marioHitCheck2(Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist) {
	asm volatile {
		opword 0x9421FEA0
		opword 0x7C0802A6
		opword 0x90010164
		opword 0xDBE10150
		opword 0xF3E10158
		opword 0xBF61013C
		opword 0x7C7B1B78
		opword 0x7C9C2378
		opword 0x7CBF2B78
		opword 0x7CDE3378
		opword 0x7CFD3B78
		bl marioGetPtr
		opword 0xA003002E
		opword 0xC3FD0000
		opword 0x28000014
		opword 0x41820470
		opword 0x80030000
		opword 0x5400039D
		opword 0x40820218
		opword 0x80FB0000
		lis r3, chkFilterAttr2@ha
		opword 0x80DB0004
		addi r4, r3, chkFilterAttr2@l
		opword 0x38A00004
		opword 0x3C000080
		opword 0x90E100D4
		opword 0x386100C8
		opword 0x90C100D8
		opword 0x80DB0008
		opword 0x90C100DC
		opword 0x80FC0000
		opword 0x80DC0004
		opword 0x90E100E0
		opword 0x90C100E4
		opword 0x80DC0008
		opword 0x90C100E8
		opword 0xD3E10104
		opword 0x90A100CC
		opword 0x900100D0
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000868
		opword 0xC0210104
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010110
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0x281F0000
		opword 0xFC00001E
		opword 0xD8010108
		opword 0x8001010C
		opword 0x6C008000
		opword 0x90010114
		opword 0xC8010110
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x41820130
		opword 0x808100EC
		opword 0x800100F0
		lfs f0, float_0_8041a7a4(r2)
		opword 0x909F0000
		opword 0x901F0004
		opword 0x800100F4
		opword 0x901F0008
		opword 0xC03F0000
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010108
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210110
		opword 0x80010114
		opword 0x6C008000
		opword 0x9001010C
		opword 0xC8210108
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0000
		opword 0xC03F0004
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010120
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210118
		opword 0x8001011C
		opword 0x6C008000
		opword 0x90010124
		opword 0xC8210120
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0004
		opword 0xC03F0008
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010130
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010128
		opword 0x8001012C
		opword 0x6C008000
		opword 0x90010134
		opword 0xC8010130
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01F0008
		opword 0x281E0000
		opword 0x418206D4
		opword 0x808100F8
		opword 0x800100FC
		opword 0x909E0000
		opword 0x901E0004
		opword 0x80010100
		opword 0x901E0008
		opword 0x480006B8
		opword 0x807B0000
		opword 0x801B0004
		opword 0x90610094
		opword 0x90010098
		opword 0x801B0008
		opword 0x9001009C
		opword 0x807C0000
		opword 0x801C0004
		opword 0x906100A0
		opword 0x900100A4
		opword 0x801C0008
		opword 0x900100A8
		opword 0xD3E100C4
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610088
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610088
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610088
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x4800061C
		opword 0xC02100C4
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010128
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0x281F0000
		opword 0xFC00001E
		opword 0xD8010130
		opword 0x80010134
		opword 0x6C008000
		opword 0x9001012C
		opword 0xC8010128
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x41820130
		opword 0x808100AC
		opword 0x800100B0
		lfs f0, float_0_8041a7a4(r2)
		opword 0x909F0000
		opword 0x901F0004
		opword 0x800100B4
		opword 0x901F0008
		opword 0xC03F0000
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010128
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210130
		opword 0x80010134
		opword 0x6C008000
		opword 0x9001012C
		opword 0xC8210128
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0000
		opword 0xC03F0004
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010118
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210120
		opword 0x80010124
		opword 0x6C008000
		opword 0x9001011C
		opword 0xC8210118
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0004
		opword 0xC03F0008
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010108
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010110
		opword 0x80010114
		opword 0x6C008000
		opword 0x9001010C
		opword 0xC8010108
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01F0008
		opword 0x281E0000
		opword 0x41820488
		opword 0x808100B8
		opword 0x800100BC
		opword 0x909E0000
		opword 0x901E0004
		opword 0x800100C0
		opword 0x901E0008
		opword 0x4800046C
		bl marioGetJabaraState
		opword 0x2C030001
		opword 0x40820218
		opword 0x80FB0000
		lis r3, chkFilterAttr2@ha
		opword 0x80DB0004
		addi r4, r3, chkFilterAttr2@l
		opword 0x38A00004
		opword 0x3C000080
		opword 0x90E10054
		opword 0x38610048
		opword 0x90C10058
		opword 0x80DB0008
		opword 0x90C1005C
		opword 0x80FC0000
		opword 0x80DC0004
		opword 0x90E10060
		opword 0x90C10064
		opword 0x80DC0008
		opword 0x90C10068
		opword 0xD3E10084
		opword 0x90A1004C
		opword 0x90010050
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480003FC
		opword 0xC0210084
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010128
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0x281F0000
		opword 0xFC00001E
		opword 0xD8010130
		opword 0x80010134
		opword 0x6C008000
		opword 0x9001012C
		opword 0xC8010128
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x41820130
		opword 0x8081006C
		opword 0x80010070
		lfs f0, float_0_8041a7a4(r2)
		opword 0x909F0000
		opword 0x901F0004
		opword 0x80010074
		opword 0x901F0008
		opword 0xC03F0000
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010128
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210130
		opword 0x80010134
		opword 0x6C008000
		opword 0x9001012C
		opword 0xC8210128
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0000
		opword 0xC03F0004
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010118
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210120
		opword 0x80010124
		opword 0x6C008000
		opword 0x9001011C
		opword 0xC8210118
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0004
		opword 0xC03F0008
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010108
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010110
		opword 0x80010114
		opword 0x6C008000
		opword 0x9001010C
		opword 0xC8010108
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01F0008
		opword 0x281E0000
		opword 0x41820268
		opword 0x80810078
		opword 0x8001007C
		opword 0x909E0000
		opword 0x901E0004
		opword 0x80010080
		opword 0x901E0008
		opword 0x4800024C
		opword 0x807B0000
		opword 0x801B0004
		opword 0x90610014
		opword 0x90010018
		opword 0x801B0008
		opword 0x9001001C
		opword 0x807C0000
		opword 0x801C0004
		opword 0x90610020
		opword 0x90010024
		opword 0x801C0008
		opword 0x90010028
		opword 0xD3E10044
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610008
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610008
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610008
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001B0
		opword 0xC0210044
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010128
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0x281F0000
		opword 0xFC00001E
		opword 0xD8010130
		opword 0x80010134
		opword 0x6C008000
		opword 0x9001012C
		opword 0xC8010128
		opword 0xEC000828
		opword 0xEFE01024
		opword 0x41820130
		opword 0x8081002C
		opword 0x80010030
		lfs f0, float_0_8041a7a4(r2)
		opword 0x909F0000
		opword 0x901F0004
		opword 0x80010034
		opword 0x901F0008
		opword 0xC03F0000
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010128
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210130
		opword 0x80010134
		opword 0x6C008000
		opword 0x9001012C
		opword 0xC8210128
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0000
		opword 0xC03F0004
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010118
		opword 0xEC23007A
		lfd f2, double_to_int_802c5920@l(r4)
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC20081E
		opword 0xD8210120
		opword 0x80010124
		opword 0x6C008000
		opword 0x9001011C
		opword 0xC8210118
		opword 0xEC211028
		opword 0xEC211824
		opword 0xD03F0004
		opword 0xC03F0008
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010108
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02007A
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010110
		opword 0x80010114
		opword 0x6C008000
		opword 0x9001010C
		opword 0xC8010108
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD01F0008
		opword 0x281E0000
		opword 0x4182001C
		opword 0x80810038
		opword 0x8001003C
		opword 0x909E0000
		opword 0x901E0004
		opword 0x80010040
		opword 0x901E0008
		opword 0xD3FD0000
		opword 0xE3E10158
		opword 0xCBE10150
		opword 0xBB61013C
		opword 0x80010164
		opword 0x7C0803A6
		opword 0x38210160
	}
}
#pragma pop

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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* marioSearchUnder(void) {
	asm volatile {
		opword 0x9421FF50
		opword 0x7C0802A6
		opword 0x900100B4
		opword 0x93E100AC
		bl marioGetPtr
		opword 0x80030000
		opword 0x7C7F1B78
		opword 0xC02301B8
		opword 0x540001CF
		opword 0x4182000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0xEC210032
		opword 0x801F0090
		lis r3, vec3_802c5754@ha
		addi r5, r3, vec3_802c5754@l
		opword 0x80FF008C
		opword 0x90010024
		opword 0x80DF0094
		opword 0xC0010024
		opword 0x80850000
		opword 0xEC20082A
		opword 0x80650004
		opword 0x80050008
		lfs f0, float_1000_8041a7a0(r2)
		opword 0xD0210024
		opword 0x80A10024
		opword 0x90E10020
		opword 0x90C10028
		opword 0x90E10038
		opword 0x90A1003C
		opword 0x90C10040
		opword 0x90810044
		opword 0x90610048
		opword 0x9001004C
		opword 0xD0010068
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x3861002C
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x3861002C
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x3861002C
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000150
		opword 0x80010050
		opword 0x80810054
		opword 0x90010014
		opword 0x80010058
		opword 0xC0210014
		lfs f0, float_0_8041a7a4(r2)
		opword 0x90810018
		opword 0xFC010040
		opword 0x9001001C
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010078
		lis r4, double_to_int_802c5920@ha
		opword 0xEC03007A
		opword 0xC0810018
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410070
		opword 0x80010074
		opword 0x6C008000
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010014
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010088
		opword 0xEC03013A
		opword 0xC081001C
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410080
		opword 0x80010084
		opword 0x6C008000
		opword 0x9001008C
		opword 0xC8010088
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010018
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010098
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x34010008
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010090
		opword 0x80010094
		opword 0x6C008000
		opword 0x9001009C
		opword 0xC8010098
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD001001C
		opword 0x4182001C
		opword 0x80A1005C
		opword 0x80810060
		opword 0x80010064
		opword 0x90A10008
		opword 0x9081000C
		opword 0x90010010
		opword 0x28030000
		opword 0x4182000C
		opword 0xC0010018
		opword 0x48000008
		lfs f0, float_neg3000_8041a870(r2)
		opword 0xD01F01C0
		opword 0x800100B4
		opword 0x83E100AC
		opword 0x7C0803A6
		opword 0x382100B0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* searchUnder2(f32* out, f32 x, f32 y, f32 z) {
	asm volatile {
		opword 0x9421FF50
		opword 0x7C0802A6
		lis r5, vec3_802c5760@ha
		lis r4, vec3_802c576c@ha
		opword 0x900100B4
		addi r6, r5, vec3_802c5760@l
		addi r5, r4, vec3_802c576c@l
		lfs f0, float_1037_8041a888(r2)
		opword 0x93E100AC
		opword 0x7C7F1B78
		opword 0x80060004
		opword 0x80E60000
		opword 0x9001000C
		opword 0x80C60008
		opword 0xD041000C
		opword 0x80850000
		opword 0x8001000C
		opword 0x90E10008
		opword 0x80650004
		opword 0x90010030
		lfs f2, float_37_8041a86c(r2)
		opword 0xC0810030
		opword 0x90C10010
		opword 0xEC44102A
		opword 0x80050008
		opword 0xD0210008
		opword 0xD0610010
		opword 0x80E10008
		opword 0x80C10010
		opword 0xD0410030
		opword 0x80A10030
		opword 0x90E1002C
		opword 0x90C10034
		opword 0x90E10044
		opword 0x90A10048
		opword 0x90C1004C
		opword 0x90810050
		opword 0x90610054
		opword 0x90010058
		opword 0xD0010074
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001C
		opword 0x40820018
		lis r4, chkfilterVecVivian@ha
		opword 0x38610038
		addi r4, r4, chkfilterVecVivian@l
		bl hitCheckVecFilter
		opword 0x48000038
		bl marioGetPtr
		opword 0x80030000
		opword 0x540001CF
		opword 0x41820018
		lis r4, chkfilterVecRoll@ha
		opword 0x38610038
		addi r4, r4, chkfilterVecRoll@l
		bl hitCheckVecFilter
		opword 0x48000014
		lis r4, chkfilterVec@ha
		opword 0x38610038
		addi r4, r4, chkfilterVec@l
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000150
		opword 0x8001005C
		opword 0x80810060
		opword 0x90010020
		opword 0x80010064
		opword 0xC0210020
		lfs f0, float_0_8041a7a4(r2)
		opword 0x90810024
		opword 0xFC010040
		opword 0x90010028
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x90010080
		lis r4, double_to_int_802c5920@ha
		opword 0xEC03007A
		opword 0xC0810024
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410078
		opword 0x8001007C
		opword 0x6C008000
		opword 0x90010084
		opword 0xC8010080
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010020
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f3, float_1000_8041a7a0(r2)
		opword 0x3C004330
		lis r4, double_to_int_802c5920@ha
		opword 0x90010090
		opword 0xEC03013A
		opword 0xC0810028
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC40001E
		lfs f0, float_0_8041a7a4(r2)
		opword 0xFC040040
		opword 0xD8410088
		opword 0x8001008C
		opword 0x6C008000
		opword 0x90010094
		opword 0xC8010090
		opword 0xEC000828
		opword 0xEC001824
		opword 0xD0010024
		opword 0x4C411382
		opword 0x4082000C
		lfs f0, float_0p5_8041a7c4(r2)
		opword 0x48000008
		lfs f0, float_neg0p5_8041a7c8(r2)
		lfs f2, float_1000_8041a7a0(r2)
		opword 0x3C004330
		opword 0x900100A0
		lis r4, double_to_int_802c5920@ha
		opword 0xEC02013A
		opword 0x34010014
		lfd f1, double_to_int_802c5920@l(r4)
		opword 0xFC00001E
		opword 0xD8010098
		opword 0x8001009C
		opword 0x6C008000
		opword 0x900100A4
		opword 0xC80100A0
		opword 0xEC000828
		opword 0xEC001024
		opword 0xD0010028
		opword 0x4182001C
		opword 0x80A10068
		opword 0x8081006C
		opword 0x80010070
		opword 0x90A10014
		opword 0x90810018
		opword 0x9001001C
		opword 0x28030000
		opword 0x4182000C
		opword 0xC0010024
		opword 0x48000008
		lfs f0, float_neg1_8041a7dc(r2)
		opword 0xD01F0000
		opword 0x800100B4
		opword 0x83E100AC
		opword 0x7C0803A6
		opword 0x382100B0
	}
}
#pragma pop


// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c5730[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c573c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5748[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5754[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5760[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c576c[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5778[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5784[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5790[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c579c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57a8[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57b4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57c0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57cc[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57d8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57e4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57f0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c57fc[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5808[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5814[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5820[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c582c[3] = {0.0f, 1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5838[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5844[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5850[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c585c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5868[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5874[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5880[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c588c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5898[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58a4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58b0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58bc[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58c8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58d4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58e0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58ec[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c58f8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5904[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c5910[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802c5920 = 4503601774854144.0;
__declspec(section ".rodata") const f64 double_0p5_802c5928 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c5930 = 3.0;
__declspec(section ".rodata") const f64 double_0_802c5938 = 0.0;
__declspec(section ".rodata") const char str_802C5940[] = "dou_10\0";
__declspec(section ".rodata") const char str_802C5948[] = "eki_04\0";
__declspec(section ".rodata") const char str_802C5950[] = "MOBJ_PowerUpBlock\0\0";
__declspec(section ".rodata") const char str_802C5964[] = "MOBJ_SaveBlock\0";
__declspec(section ".rodata") const char str_802C5974[] = "MOBJ_RecoveryBlock\0";
__declspec(section ".rodata") const char str_802C5988[] = "MOBJ_CoinTakenRecoveryBlock";
__declspec(section ".rodata") const char str_802C59A4[] = "MOBJ_HiddenHatenaBlock\0";
__declspec(section ".rodata") const char str_802C59BC[] = "MOBJ_HiddenBadgeBlock\0\0";
__declspec(section ".rodata") const char str_802C59D4[] = "MOBJ_Hidden10CountBlock";
__declspec(section ".rodata") const u32 gap_04_802C59EC_rodata = 0x00000000;
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


#endif