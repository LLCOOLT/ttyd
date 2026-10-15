#include "driver/camdrv.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <string.h>

extern int __float_nan[];
extern double sin(double);
extern double cos(double);
extern f32 toMovedir(f32 angle);
extern MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hit);
extern s32 kpaGetLevel(void);
extern s32 kpaGetStageType(void);
extern s32 kpaFireAttackCheck(void);
extern s32 kpaMutekiCheck(void);
extern u8* getKoopaFireEfp(void);

typedef struct KpaHitWork {
    u8 pad0[0x18];
    HitEntry* flame;  // 0x18
    HitEntry* obj;    // 0x1C
    HitEntry* head[10];
    s32 pad48;
    HitEntry* ride_[10];
    f32 headDist[10];
} KpaHitWork;

#define KPW (*(KpaHitWork**)((u8*)marioGetPtr() + 0x28C))
#define MF(m, off) (*(f32*)((u8*)(m) + (off)))
#define MS16(m, off) (*(s16*)((u8*)(m) + (off)))
#define KHEAD(i) (*(HitEntry**)((u8*)KPW + 0x20 + (i) * 4))
#define KHEADD(i) (*(f32*)((u8*)KPW + 0x78 + (i) * 4))
#define KRIDE(i) (*(HitEntry**)((u8*)KPW + 0x4C + (i) * 4))
#define KRIDED(i) (*(f32*)((u8*)KPW + 0xA4 + (i) * 4))

static inline s32 party_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 party_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (party_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

static inline f32 kpa_nrmToAngle(f32 x, f32 y, f32 z) {
    return angleABf(0.0f, 0.0f, party_sqrtf(x * x + z * z), -y);
}

static inline f32 kpa_nrmSet(MarioWork* m, f32 x, f32 y, f32 z) {
    MF(m, 0x218) = (s32)(angleABf(0.0f, 0.0f, 100.0f * z, 100.0f * y) - 180.0f);
    MF(m, 0x21C) = 0.0f;
    MF(m, 0x220) = (s32)(angleABf(0.0f, 0.0f, 100.0f * x, 100.0f * y) - 180.0f);
    return kpa_nrmToAngle(x, y, z);
}

s32 kpaEnemyFireHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
    Mtx m3;
    Mtx m1;
    Mtx m2;
    Mtx m4;
    Vec out;
    Vec b;
    Vec diff;
    Vec a;
    u8* efp;
    u8* e;
    f32 half;
    f32 r;
    f32 s;
    s32 i;

    efp = getKoopaFireEfp();
    camGetPtr(4);
    {
        Vec zero0 = {0.0f, 0.0f, 0.0f};
        a = zero0;
    }
    a.x = x;
    a.y = 0.5f * h + y;
    a.z = z;
    b = a;
    if (!efp) {
        return 0;
    }
    e = *(u8**)(efp + 0xC);
    s = MF(e, 0x40);
    PSMTXTrans(m1, MF(e, 4), MF(e, 8), MF(e, 0xC));
    PSMTXRotRad(m2, 'y', 0.017453292f * (MF(e, 0x48) - MF(camGetPtr(4), 0x114)));
    if (MF(e, 0x48) > 90.0f && MF(e, 0x48) < 270.0f) {
        PSMTXScale(m3, MF(e, 0x40), MF(e, 0x40), -MF(e, 0x40));
    } else {
        PSMTXScale(m3, MF(e, 0x40), MF(e, 0x40), MF(e, 0x40));
    }
    PSMTXConcat(m1, m2, m1);
    PSMTXConcat(m1, m3, m4);
    half = 0.5f * w;
    e += 0x50;
    for (i = 1; i < *(s32*)(efp + 8); i++, e += 0x50) {
        if (*(s32*)(e + 0x44) == 0) {
            r = 7.0f * MF(e, 0x40);
            PSMTXTrans(m1, MF(e, 4), MF(e, 8), MF(e, 0xC));
            PSMTXScale(m3, r, r, r);
            PSMTXConcat(m1, m3, m1);
            PSMTXConcat(m4, m1, m1);
            {
                Vec zero = {0.0f, 0.0f, 0.0f};
                PSMTXMultVec(m1, &zero, &out);
            }
            PSVECSubtract(&b, &out, &diff);
            if (PSVECMag(&diff) < r * s + half) {
                return 1;
            }
        }
    }
    return 0;
}

s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
    MarioWork* m = marioGetPtr();
    f32 dh, dw, dx, dy;

    if (kpaEnemyFireHitChk(x, y, z, h, w)) {
        return 2;
    }
    dh = 0.5f * (MF(m, 0x1B8) + h);
    dw = 0.5f * (MF(m, 0x1B4) + w);
    dx = __fabsf(MF(m, 0x8C) - x);
    dy = __fabsf(MF(m, 0x90) + 0.5f * MF(m, 0x1B8) - y - 0.5f * h);
    if (dy <= dh && dx <= dw) {
        if ((m->flags & 0x20000) && MF(m, 0x90) > y) {
            if (kpaGetLevel() == 0 && kpaGetStageType() != 1 && MS16(m, 0x4C) == 0 && z < 50.0f) {
                marioChgMot(4);
            }
            return 1;
        }
        if (kpaMutekiCheck() == 1) {
            return 3;
        }
        if (MS16(m, 0x4C) != 0) {
            return 3;
        }
        if (MS16(m, 0x78) == 0) {
            return 4;
        }
    }
    return 0;
}

static inline void kpa_headClear(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        KHEAD(i) = NULL;
        KHEADD(i) = 1000.0f;
    }
}

HitEntry* kpaSearchGround(f32 range, f32* outY, f32* outDepth, f32* outAng) {
    s32 n, i;
    MarioWork* m;
    MarioWork* m2;
    HitEntry* hit;
    HitEntry* best;
    Vec zero = {0.0f, 0.0f, 0.0f};
    f32 hx, hy, hz, dist, nx, ny, nz, nv;
    f32 h, deg, ex, ez, fx, fz, ang;
    f32 rad, r2b, r3, bd, yh, r2, px, py, pz, ox, oz;

    m = marioGetPtr();
    best = NULL;
    MF(m, 0x218) = 0.0f;
    MF(m, 0x21C) = 0.0f;
    MF(m, 0x220) = 0.0f;
    MF(m, 0x214) = 0.0f;
    if (m->flags & 0x200) {
        *outY = MF(m, 0x90);
        return NULL;
    }
    range += 0.01f;
    if (kpaGetLevel() == 0) {
        h = MF(m, 0x1B8);
    } else {
        h = 0.25f * MF(m, 0x1B8);
    }
    *outY = MF(m, 0x90);
    *outDepth = -1.0f;
    if (m->baseSpeed) {
        deg = m->directionView;
    } else {
        deg = toMovedir(m->unk1A8);
    }
    px = MF(m, 0x8C);
    py = MF(m, 0x90);
    pz = MF(m, 0x94);
    for (i = 0; i < 10; i++) {
        KRIDE(i) = NULL;
        KRIDED(i) = 1000.0f;
    }
    switch (kpaGetLevel()) {
    case 0:
    case 1:
    case 2:
        n = 3;
        r2 = 0.6f * (0.5 * MF(m, 0x1B4));
        break;
    case 3:
        n = 7;
        r2 = 0.6f * (0.5f * MF(m, 0x1B4) / 3.0f);
        break;
    }
    r2b = 2.0f * r2 - 0.05f;
    rad = 3.1415927f * deg; bd = h + range; yh = py + h;
    r3 = 3.0f * r2 - 0.05f;
    for (i = 0; i < n; i++) {
        switch (i) {
        case 0:
            ox = 0.0f;
            oz = ox;
            break;
        case 1:
            ang = rad / 180.0f;
            ox = (r2 - 0.05f) * (f32)sin(ang);
            nv = (f32)cos(ang); oz = (r2 - 0.05f) * -nv;
            break;
        case 2:
            ang = rad / 180.0f;
            nv = (f32)sin(ang); ox = (r2 - 0.05f) * -nv;
            nv = (f32)cos(ang); oz = (r2 - 0.05f) * -nv;
            break;
        case 3:
            ang = rad / 180.0f;
            ox = r2b * (f32)sin(ang);
            oz = r2b * -(f32)cos(ang);
            break;
        case 4:
            ang = rad / 180.0f;
            ox = r2b * -(f32)sin(ang);
            oz = r2b * -(f32)cos(ang);
            break;
        case 5:
            ang = rad / 180.0f;
            ox = r3 * (f32)sin(ang);
            oz = r3 * -(f32)cos(ang);
            break;
        case 6:
            ang = rad / 180.0f;
            ox = r3 * -(f32)sin(ang);
            oz = r3 * -(f32)cos(ang);
            break;
        }
        dist = bd;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, px + ox, yh, pz + oz, 0.0f, -1.0f, 0.0f);
        if (hit) {
            f32 tx = nx, tz = nz, ty = ny;
            m2 = marioGetPtr();
            if (kpa_nrmSet(m2, tz, ty, tx) >= 50.0f) {
                hit = NULL;
            }
        }
        hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
        if (hit) {
            f32 ty = ny, tz = nz, tx = nx;
            m2 = marioGetPtr();
            MF(m, 0x214) = kpa_nrmSet(m2, tz, ty, tx);
            if (hy < py && __fabsf(hy - py) >= 2.0f) {
                *outDepth = py - hy;
                *outAng = angleABf(px, pz, hx, hz);
                hit = NULL;
            } else {
                if (!nx && !nz) {
                    hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
                }
                *outY = hy;
                *outDepth = 0.0f;
                *outAng = angleABf(px, pz, hx, hz);
                best = hit;
            }
        }
        KRIDE(i) = hit;
        KRIDED(i) = ox;
    }
    return best;
}


HitEntry* kpaSearchHead(f32 hgt, f32* outA, f32* outB) {
    static s32 _ofs0[] = {3, 12, 16, 1, 0, 16, 0, -9, 16, 0};
    static s32 _ofs1[] = {4, 25, 74, 0, 50, 65, 1, 0, 67, 0, -25, 62, 0};
    static s32 _ofs2[] = {6, 50, 102, 0, 76, 90, 1, 25, 100, 0, 0, 94, 0, -25, 90, 0, -45, 68, 0};
    static s32 _ofs3[] = {13, 170, 194, 1, 145, 204, 0, 120, 232, 0, 95, 227, 0, 70, 232, 0, 55, 232, 0,
                          30, 194, 0, 5, 187, 0, -20, 210, 0, -45, 201, 0, -70, 181, 0, -95, 153, 0, -120, 56, 0};
    static s32* headchkofs[] = {_ofs0, _ofs1, _ofs2, _ofs3};
    s32 i, j, n;
    s32* tbl;
    HitEntry* hit;
    HitEntry* best;
    MarioWork* m;
    f32 deg, rad, off, c, s_, x, y, z, hx, hy, hz, nx, ny, nz, d;
    f32 oy, oz, mode;
    s32 md;

    m = marioGetPtr();
    if (m->flags & 0x20000) {
        return NULL;
    }
    best = NULL;
    if (m->baseSpeed) {
        deg = m->directionView;
    } else {
        deg = toMovedir(m->unk1A8);
    }
    off = *outB;
    *outB = -1.0f;
    kpa_headClear();
    tbl = headchkofs[kpaGetLevel()];
    n = *tbl++;
    if (!(m->flags & 0x10000)) {
        switch (kpaGetLevel()) {
        case 0:
            off = 2.0f;
            break;
        case 1:
            off = 0.0f;
            break;
        case 2:
            off = 0.0f;
            break;
        case 3:
            off = 35.0f;
            break;
        }
    } else {
        switch (kpaGetLevel()) {
        case 0:
            if (m->currMotionId == 0x25) {
                off = 10.0f;
            } else {
                off = hgt;
            }
            break;
        default:
            off = hgt;
            break;
        }
    }
    rad = 3.1415927f * deg / 180.0f;
    for (i = 0; i < n; i++) {
        s_ = tbl[0] * (f32)sin(rad);
        c = (f32)cos(rad);
        oz = tbl[0] * -c;
        oy = tbl[1];
        md = tbl[2];
        tbl += 3;
        if (md == 0 && !(m->flags & 0x10000)) {
            continue;
        }
        x = MF(m, 0x8C) + s_;
        y = MF(m, 0x90) + oy;
        z = MF(m, 0x94) + oz;
        d = off;
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &d, &nx, &ny, &nz, x, y, z, 0.0f, 1.0f, 0.0f);
        if (hit) {
            hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
            if (y + off >= hy) {
                outA[1] = hy;
                best = hit;
                *outB = 0.0f;
                KHEAD(i) = hit;
            } else {
                *outB = hy - outA[1] - off;
            }
        }
    }
    return best;
}

HitEntry* kpaSearchFrontUnder(void) {
    return NULL;
}

HitEntry* kpaGetHitobjHead(s32 i) {
    return KHEAD(i);
}

HitEntry* kpaGetHitobjHead2(void) {
    return KPW->head[0];
}

HitEntry* kpaGetHitobjRide(s32 i) {
    return KRIDE(i);
}

HitEntry* kpaChkHitobjRide(void) {
KpaHitWork* w = KPW;
HitEntry* r;
r = w->ride_[0];
if (!r) {
r = w->ride_[1];
if (!r) {
r = w->ride_[2];
if (!r) {
r = w->ride_[3];
if (!r) {
r = w->ride_[4];
if (!r) {
r = w->ride_[5];
if (!r) {
r = w->ride_[6];
if (!r) {
r = w->ride_[7];
if (!r) {
r = w->ride_[8];
if (!r) {
r = w->ride_[9];
if (r) { return r; } else { return r; }
}
}
}
}
}
}
}
}
}
return r;
}

long kpaClearHitobjRide(void) {
    MarioWork* m = marioGetPtr();
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x4C) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x50) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x54) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x58) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x5C) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x60) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x64) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x68) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x6C) = NULL;
    *(HitEntry**)(*(u8**)((u8*)m + 0x28C) + 0x70) = NULL;
}

HitEntry* kpaGetHitobj(void) {
    MarioWork* m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    return (*(KpaHitWork**)((u8*)m + 0x28C))->obj;
}

HitEntry* kpaGetHitFlame(void) {
    MarioWork* m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    return (*(KpaHitWork**)((u8*)m + 0x28C))->flame;
}

static s32 head_sphere_data_lv1[] = {3, 32, 55, 24, 0, 26, 30, 16, 2, -10, 44, 25, 1};
static s32 head_sphere_data_lv2[] = {3, 45, 75, 34, 0, 36, 30, 16, 2, -15, 59, 36, 1};
static s32 head_sphere_data_lv3[] = {4, 100, 162, 80, 0, 90, 75, 30, 2, 50, 40, 30, 3, -43, 142, 74, 1};
static s32 head_sphere_data_lv0[] = {1, 10, 15, 6, 0};
static s32* head_sphere_data[] = {head_sphere_data_lv0, head_sphere_data_lv1, head_sphere_data_lv2, head_sphere_data_lv3};

HitEntry* kpaHitCheck(void) {
    s32* p;
    s32 j;
    s32 i;
    HitEntry* hit;
    s32 n;
    MarioWork* m;
    HitEntry* best;
    f32 rad, x, y, z, r, sn;

    best = NULL;
    m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    (*(KpaHitWork**)((u8*)m + 0x28C))->obj = NULL;
    kpa_headClear();
    if (kpaFireAttackCheck() == 1) {
        return NULL;
    }
    p = head_sphere_data[kpaGetLevel()];
    n = *p++;
    for (j = 0; j < n; j++) {
        sn = (f32)sin(3.1415927f * m->directionView / 180.0f);
        x = MF(m, 0x8C) + p[0] * sn;
        sn = (f32)cos(3.1415927f * m->directionView / 180.0f);
        z = MF(m, 0x94) - p[0] * sn;
        y = MF(m, 0x90) + p[1];
        r = p[2];
        i = p[3];
        p += 4;
        switch (i) {
        case 1:
            if (!(m->flags & 0x10000)) {
                continue;
            }
            break;
        case 2:
            if (m->flags & 0x10000) {
                continue;
            }
            break;
        case 3:
            if (m->flags & 0x30000) {
                continue;
            }
            break;
        }
        hit = hitCheckSphereFilter(NULL, x, y, z, r);
        if ((m->flags & 0x10000) && (hitGetAttr(hit) & 0x80000000) && *(f32*)((u8*)mobjHitObjPtrToPtr(hit) + 0x3C) > y) {
            KHEAD(j) = hit;
        }
        if (hit) {
            if (1) {
            }
            best = hit;
        }
    }
    (*(KpaHitWork**)((u8*)m + 0x28C))->obj = best;
    return best;
}

BOOL kpaFlameHitFilter(HitCheckQuery* query, HitEntry* entry) {
    MapObjectEntry* mobj = mobjHitObjPtrToPtr(entry);
    if (!strcmp(mobj->animName, "MOBJ_HiddenHatenaBlock")) {
        return FALSE;
    }
    if (!strcmp(mobj->animName, "MOBJ_Block")) {
        return FALSE;
    }
    return TRUE;
}

HitEntry* kpaFlameHitCheck(f32 x, f32 y, f32 z, f32 r) {
    marioGetPtr();
    return hitCheckSphereFilter(kpaFlameHitFilter, x, y, z, r);
}


// Stand-in for a function the original linker dead-stripped; its 0.5f is first in the .sdata2 pool.
void kpaStrippedPool(f32* f) {
    *f = 0.5f;
}
