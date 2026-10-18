#include "driver/camdrv.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <string.h>
s32 kpaEnemyFireHitChk(f32 x, f32 y, f32 z, f32 h, f32 w);
void _restfpr_28(void);
void _savefpr_28(void);
BOOL kpaFlameHitFilter(HitCheckQuery* query, HitEntry* entry);

#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const f32 float_0p5_80420e70;
#endif

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


#ifdef NONMATCHING
static f32 kpaHalf(f32 v);
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: kpaEnemyHitChk (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fe320[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fe32c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fe338[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_802FE344[] = "MOBJ_HiddenHatenaBlock\000";
__declspec(section ".rodata") const char str_802FE35C[] = "MOBJ_Block\000";
__declspec(section ".rodata") const f64 double_to_int_802fe368 = 4503601774854144;
__declspec(section ".rodata") const f64 double_0p6_802fe370 = 0.6000000238418579;
__declspec(section ".rodata") const f64 double_0p5_802fe378 = 0.5;
__declspec(section ".rodata") const f64 double_3_802fe380 = 3;
__declspec(section ".rodata") const f64 double_0_802fe388 = 0;
__declspec(section ".sdata2") const f32 float_0p5_80420e70 = 0.5f;
__declspec(section ".sdata2") const f32 float_1000_80420e74 = 1000.0f;
__declspec(section ".sdata2") const f32 float_3p1416_80420e78 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_80420e7c = 180.0f;
__declspec(section ".sdata2") const f32 float_0_80420e80 = 0.0f;
__declspec(section ".sdata2") const f32 float_neg1_80420e84 = -1.0f;
__declspec(section ".sdata2") const f32 float_2_80420e88 = 2.0f;
__declspec(section ".sdata2") const f32 float_35_80420e8c = 35.0f;
__declspec(section ".sdata2") const f32 float_10_80420e90 = 10.0f;
__declspec(section ".sdata2") const f32 float_1_80420e94 = 1.0f;
__declspec(section ".sdata2") const f32 float_100_80420e98 = 100.0f;
__declspec(section ".sdata2") const f32 float_0p01_80420e9c = 0.01f;
__declspec(section ".sdata2") const f32 float_0p25_80420ea0 = 0.25f;
__declspec(section ".sdata2") const f32 float_0p6_80420ea4 = 0.6f;
__declspec(section ".sdata2") const f32 float_3_80420ea8 = 3.0f;
__declspec(section ".sdata2") const f32 float_0p05_80420eac = 0.05f;
__declspec(section ".sdata2") const f32 float_50_80420eb0 = 50.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80420eb4 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_90_80420eb8 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_80420ebc = 270.0f;
__declspec(section ".sdata2") const f32 float_7_80420ec0 = 7.0f;
#pragma force_active on
#pragma explicit_zero_data on
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_sdata2_80420EC4 = 0;
#pragma explicit_zero_data reset
#pragma force_active reset
#endif


#ifdef NONMATCHING
s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
    MarioWork* m;
    f32 dh, dw, dx, dy;

    m = marioGetPtr();

    if (kpaEnemyFireHitChk(x, y, z, h, w)) {
        return 2;
    }
    dh = 0.5f * (m->wPlayerCollisionBox.y + h);
    dw = 0.5f * (m->wPlayerCollisionBox.x + w);
    dx = __fabsf(m->position.x - x);
    dy = __fabsf(m->position.y + 0.5f * m->wPlayerCollisionBox.y - y - 0.5f * h);
    if (dy <= dh && dx <= dw) {
        if ((m->flags & 0x20000) && m->position.y > y) {
            if (kpaGetLevel() == 0 && kpaGetStageType() != 1 && m->unk4C == 0 && z < 50.0f) {
                marioChgMot(4);
            }
            return 1;
        }
        if (kpaMutekiCheck() == 1) {
            return 3;
        }
        if (m->unk4C != 0) {
            return 3;
        }
        if (MS16(m, 0x78) == 0) {
            return 4;
        }
    }
    return 0;
}
#endif

static inline void kpa_headClear(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        KHEAD(i) = NULL;
        KHEADD(i) = 1000.0f;
    }
}

#ifdef NONMATCHING
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
        *outY = m->position.y;
        return NULL;
    }
    range += 0.01f;
    if (kpaGetLevel() == 0) {
        h = m->wPlayerCollisionBox.y;
    } else {
        h = 0.25f * m->wPlayerCollisionBox.y;
    }
    *outY = m->position.y;
    *outDepth = -1.0f;
    if (m->baseSpeed) {
        deg = m->directionView;
    } else {
        deg = toMovedir(m->displayDirection);
    }
    px = m->position.x;
    py = m->position.y;
    pz = m->position.z;
    for (i = 0; i < 10; i++) {
        KRIDE(i) = NULL;
        KRIDED(i) = 1000.0f;
    }
    switch (kpaGetLevel()) {
    case 0:
    case 1:
    case 2:
        n = 3;
        r2 = 0.6f * (0.5 * m->wPlayerCollisionBox.x);
        break;
    case 3:
        n = 7;
        r2 = 0.6f * (0.5f * m->wPlayerCollisionBox.x / 3.0f);
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
            if (kpa_nrmSet(marioGetPtr(), nx, ny, nz) >= 50.0f) {
                hit = NULL;
            }
        }
        hy = (s32)(100.0f * hy + 0.5f) / 100.0f;
        if (hit) {
            MF(m, 0x214) = kpa_nrmSet(marioGetPtr(), nx, ny, nz);
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
#endif


#ifdef NONMATCHING
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
        deg = toMovedir(m->displayDirection);
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
        x = m->position.x + s_;
        y = m->position.y + oy;
        z = m->position.z + oz;
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
#endif

#ifdef NONMATCHING
HitEntry* kpaSearchFrontUnder(void) {
    return NULL;
}
#endif

#ifdef NONMATCHING
HitEntry* kpaGetHitobjHead(s32 i) {
    return KHEAD(i);
}
#endif

#ifdef NONMATCHING
HitEntry* kpaGetHitobjHead2(void) {
    return KPW->head[0];
}
#endif

#ifdef NONMATCHING
HitEntry* kpaGetHitobjRide(s32 i) {
    return KRIDE(i);
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
HitEntry* kpaGetHitobj(void) {
    MarioWork* m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    return (*(KpaHitWork**)((u8*)m + 0x28C))->obj;
}
#endif

#ifdef NONMATCHING
HitEntry* kpaGetHitFlame(void) {
    MarioWork* m = marioGetPtr();
    if (m->characterId != 2) {
        return NULL;
    }
    return (*(KpaHitWork**)((u8*)m + 0x28C))->flame;
}
#endif

static s32 _ofs0[] = {3, 12, 16, 1, 0, 16, 0, -9, 16, 0};
static s32 _ofs1[] = {4, 25, 74, 0, 50, 65, 1, 0, 67, 0, -25, 62, 0};
static s32 _ofs2[] = {6, 50, 102, 0, 76, 90, 1, 25, 100, 0, 0, 94, 0, -25, 90, 0, -45, 68, 0};
static s32 _ofs3[] = {13, 170, 194, 1, 145, 204, 0, 120, 232, 0, 95, 227, 0, 70, 232, 0, 55, 232, 0,
30, 194, 0, 5, 187, 0, -20, 210, 0, -45, 201, 0, -70, 181, 0, -95, 153, 0, -120, 56, 0};
static s32* kpaHeadChkOfs[] = {_ofs0, _ofs1, _ofs2, _ofs3};
static s32 head_sphere_data_lv1[] = {3, 32, 55, 24, 0, 26, 30, 16, 2, -10, 44, 25, 1};
static s32 head_sphere_data_lv2[] = {3, 45, 75, 34, 0, 36, 30, 16, 2, -15, 59, 36, 1};
static s32 head_sphere_data_lv3[] = {4, 100, 162, 80, 0, 90, 75, 30, 2, 50, 40, 30, 3, -43, 142, 74, 1};
static s32 head_sphere_data_lv0[] = {1, 10, 15, 6, 0};
static s32* head_sphere_data[] = {head_sphere_data_lv0, head_sphere_data_lv1, head_sphere_data_lv2, head_sphere_data_lv3};

#ifdef NONMATCHING
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
        x = m->position.x + p[0] * sn;
        sn = (f32)cos(3.1415927f * m->directionView / 180.0f);
        z = m->position.z - p[0] * sn;
        y = m->position.y + p[1];
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
#endif

#ifdef NONMATCHING
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
#endif


#ifdef NONMATCHING
static f32 kpaHalf(f32 v) {
    return EXT_LIT(float_0p5_80420e70, 0.5f) * v;
}
#endif


#ifdef NONMATCHING
HitEntry* kpaFlameHitCheck(f32 x, f32 y, f32 z, f32 r) {
    marioGetPtr();
    return hitCheckSphereFilter(kpaFlameHitFilter, x, y, z, r);
}
#endif



#pragma force_active on
#pragma explicit_zero_data on
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80415B84_sdata[1] = {0};
#pragma explicit_zero_data reset
#pragma force_active reset

#ifndef NONMATCHING
asm HitEntry* kpaFlameHitCheck(f32 x, f32 y, f32 z, f32 r) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	addi r11, r1, 0x30
	bl _savefpr_28
	fmr f28, f1
	fmr f29, f2
	fmr f30, f3
	fmr f31, f4
	bl marioGetPtr
	fmr f1, f28
	lis r3, kpaFlameHitFilter@ha
	fmr f2, f29
	addi r3, r3, kpaFlameHitFilter@l
	fmr f3, f30
	fmr f4, f31
	bl hitCheckSphereFilter
	addi r11, r1, 0x30
	bl _restfpr_28
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL kpaFlameHitFilter(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	mr r3, r4
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl mobjHitObjPtrToPtr
	lis r4, str_802FE344@ha
	mr r31, r3
	addi r4, r4, str_802FE344@l
	addi r3, r31, 0x15
	bl strcmp
	cmpwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lis r4, str_802FE35C@ha
	addi r3, r31, 0x15
	addi r4, r4, str_802FE35C@l
	bl strcmp
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaHitCheck(void) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stfd f27, 0x50(r1)
	psq_st f27, 0x58(r1), 0, 0
	stmw r24, 0x30(r1)
	li r25, 0x0
	bl marioGetPtr
	lbz r0, 0x3c(r3)
	mr r30, r3
	cmpwi r0, 0x2
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, 0x28c(r30)
	li r26, 0x0
	lfs f29, float_1000_80420e74(r2)
	mr r27, r26
	stw r26, 0x1c(r3)
	mr r28, r26
	@3:
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r28, 0x20
	stwx r26, r3, r0
	bl marioGetPtr
	addi r27, r27, 0x1
	lwz r3, 0x28c(r3)
	addi r0, r28, 0x78
	addi r28, r28, 0x4
	cmpwi r27, 0xa
	stfsx f29, r3, r0
	blt @3
	bl kpaFireAttackCheck
	cmpwi r3, 0x1
	bne @4
	li r3, 0x0
	b @2
	@4:
	bl kpaGetLevel
	slwi r0, r3, 2
	la r3, head_sphere_data(r13)
	lwzx r28, r3, r0
	lis r3, double_to_int_802fe368@ha
	lfs f31, float_3p1416_80420e78(r2)
	li r27, 0x0
	lwz r26, 0x0(r28)
	li r29, 0x0
	lfs f29, float_180_80420e7c(r2)
	lis r31, 0x4330
	lfd f30, double_to_int_802fe368@l(r3)
	addi r28, r28, 0x4
	b @5
	@6:
	lfs f0, 0x1a0(r30)
	fmuls f0, f31, f0
	fdivs f1, f0, f29
	bl sin
	lfs f0, 0x1a0(r30)
	frsp f3, f1
	lwz r0, 0x0(r28)
	fmuls f0, f31, f0
	stw r31, 0x8(r1)
	xoris r0, r0, 0x8000
	lfs f2, 0x8c(r30)
	stw r0, 0xc(r1)
	fdivs f1, f0, f29
	lfd f0, 0x8(r1)
	fsubs f0, f0, f30
	fmadds f28, f0, f3, f2
	bl cos
	lwz r0, 0x0(r28)
	frsp f4, f1
	lwz r3, 0x4(r28)
	xoris r4, r0, 0x8000
	lwz r0, 0x8(r28)
	stw r4, 0x14(r1)
	xoris r3, r3, 0x8000
	lwz r4, 0xc(r28)
	xoris r0, r0, 0x8000
	stw r31, 0x10(r1)
	addi r28, r28, 0x10
	lfs f1, 0x94(r30)
	cmpwi r4, 0x2
	lfd f0, 0x10(r1)
	stw r3, 0x1c(r1)
	fsubs f3, f0, f30
	lfs f2, 0x90(r30)
	stw r31, 0x18(r1)
	lfd f0, 0x18(r1)
	fnmsubs f3, f3, f4, f1
	stw r0, 0x24(r1)
	fsubs f1, f0, f30
	stw r31, 0x20(r1)
	lfd f0, 0x20(r1)
	fadds f27, f2, f1
	fsubs f4, f0, f30
	beq @7
	bge @8
	cmpwi r4, 0x1
	bge @9
	b @10
	@8:
	cmpwi r4, 0x4
	bge @10
	b @11
	@9:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 15, 15
	beq @12
	b @10
	@7:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 15, 15
	bne @12
	b @10
	@11:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 14, 15
	bne @12
	@10:
	fmr f1, f28
	li r3, 0x0
	fmr f2, f27
	bl hitCheckSphereFilter
	lwz r0, 0x0(r30)
	mr r24, r3
	rlwinm. r0, r0, 0, 15, 15
	beq @13
	bl hitGetAttr
	clrrwi. r0, r3, 31
	beq @13
	mr r3, r24
	bl mobjHitObjPtrToPtr
	lfs f0, 0x3c(r3)
	fcmpo cr0, f0, f27
	ble @13
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r29, 0x20
	stwx r24, r3, r0
	@13:
	cmplwi r24, 0x0
	beq @12
	mr r25, r24
	@12:
	addi r29, r29, 0x4
	addi r27, r27, 0x1
	@5:
	cmpw r27, r26
	blt @6
	lwz r4, 0x28c(r30)
	mr r3, r25
	stw r25, 0x1c(r4)
	@2:
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	psq_l f27, 0x58(r1), 0, 0
	lfd f27, 0x50(r1)
	lmw r24, 0x30(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm HitEntry* kpaGetHitFlame(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lbz r0, 0x3c(r3)
	cmpwi r0, 0x2
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, 0x28c(r3)
	lwz r3, 0x18(r3)
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaGetHitobj(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lbz r0, 0x3c(r3)
	cmpwi r0, 0x2
	beq @1
	li r3, 0x0
	b @2
	@1:
	lwz r3, 0x28c(r3)
	lwz r3, 0x1c(r3)
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm long kpaClearHitobjRide(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r4, 0x28c(r3)
	li r0, 0x0
	stw r0, 0x4c(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x50(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x54(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x58(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x5c(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x60(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x64(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x68(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x6c(r4)
	lwz r4, 0x28c(r3)
	stw r0, 0x70(r4)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaChkHitobjRide(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r4, 0x28c(r3)
	lwz r3, 0x4c(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x50(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x54(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x58(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x5c(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x60(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x64(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x68(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x6c(r4)
	cmplwi r3, 0x0
	bne @1
	lwz r3, 0x70(r4)
	cmplwi r3, 0x0
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaGetHitobjRide(s32 i) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl marioGetPtr
	slwi r4, r31, 2
	lwz r3, 0x28c(r3)
	addi r0, r4, 0x4c
	lwzx r3, r3, r0
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaGetHitobjHead2(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	lwz r0, 0x14(r1)
	lwz r3, 0x20(r3)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaGetHitobjHead(s32 i) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl marioGetPtr
	slwi r4, r31, 2
	lwz r3, 0x28c(r3)
	addi r0, r4, 0x20
	lwzx r3, r3, r0
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm HitEntry* kpaSearchFrontUnder(void) {
	nofralloc
	li r3, 0x0
	blr
}

asm HitEntry* kpaSearchHead(f32 hgt, f32* outA, f32* outB) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stfd f29, 0x80(r1)
	psq_st f29, 0x88(r1), 0, 0
	stfd f28, 0x70(r1)
	psq_st f28, 0x78(r1), 0, 0
	stmw r22, 0x48(r1)
	fmr f28, f1
	mr r23, r3
	mr r24, r4
	bl marioGetPtr
	lwz r0, 0x0(r3)
	mr r30, r3
	rlwinm. r0, r0, 0, 14, 14
	beq @1
	li r3, 0x0
	b @2
	@1:
	lfs f1, 0x180(r30)
	li r25, 0x0
	lfs f0, float_0_80420e80(r2)
	fcmpu cr0, f1, f0
	beq @3
	lfs f31, 0x1a0(r30)
	b @4
	@3:
	lfs f1, 0x1a8(r30)
	bl toMovedir
	fmr f31, f1
	@4:
	lfs f29, 0x0(r24)
	li r27, 0x0
	lfs f0, float_neg1_80420e84(r2)
	mr r28, r27
	lfs f30, float_1000_80420e74(r2)
	mr r26, r27
	stfs f0, 0x0(r24)
	@5:
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r28, 0x20
	stwx r26, r3, r0
	bl marioGetPtr
	addi r27, r27, 0x1
	lwz r3, 0x28c(r3)
	addi r0, r28, 0x78
	addi r28, r28, 0x4
	cmpwi r27, 0xa
	stfsx f30, r3, r0
	blt @5
	bl kpaGetLevel
	lwz r0, 0x0(r30)
	slwi r4, r3, 2
	la r3, kpaHeadChkOfs(r13)
	lwzx r26, r3, r4
	rlwinm. r0, r0, 0, 15, 15
	lwz r27, 0x0(r26)
	addi r26, r26, 0x4
	bne @6
	bl kpaGetLevel
	cmpwi r3, 0x2
	beq @7
	bge @8
	cmpwi r3, 0x0
	beq @9
	bge @10
	b @11
	@8:
	cmpwi r3, 0x4
	bge @11
	b @12
	@9:
	lfs f29, float_2_80420e88(r2)
	b @11
	@10:
	lfs f29, float_0_80420e80(r2)
	b @11
	@7:
	lfs f29, float_0_80420e80(r2)
	b @11
	@12:
	lfs f29, float_35_80420e8c(r2)
	b @11
	@6:
	bl kpaGetLevel
	cmpwi r3, 0x0
	beq @13
	b @14
	@13:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x25
	bne @15
	lfs f29, float_10_80420e90(r2)
	b @11
	@15:
	fmr f29, f28
	b @11
	@14:
	fmr f29, f28
	@11:
	lfs f1, float_3p1416_80420e78(r2)
	lis r3, double_to_int_802fe368@ha
	lfs f0, float_180_80420e7c(r2)
	li r28, 0x0
	fmuls f1, f1, f31
	lfd f31, double_to_int_802fe368@l(r3)
	li r29, 0x0
	lis r31, 0x4330
	fdivs f30, f1, f0
	b @16
	@17:
	fmr f1, f30
	bl sin
	lwz r0, 0x0(r26)
	frsp f2, f1
	stw r31, 0x28(r1)
	fmr f1, f30
	xoris r0, r0, 0x8000
	stw r0, 0x2c(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f31
	fmuls f28, f0, f2
	bl cos
	lwz r3, 0x0(r26)
	frsp f0, f1
	lwz r0, 0x4(r26)
	xoris r3, r3, 0x8000
	lwz r4, 0x8(r26)
	stw r3, 0x34(r1)
	xoris r0, r0, 0x8000
	fneg f1, f0
	cmpwi r4, 0x0
	stw r31, 0x30(r1)
	addi r26, r26, 0xc
	lfd f0, 0x30(r1)
	stw r0, 0x3c(r1)
	fsubs f2, f0, f31
	stw r31, 0x38(r1)
	lfd f0, 0x38(r1)
	fmuls f5, f2, f1
	fsubs f3, f0, f31
	bne @18
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 15, 15
	beq @19
	@18:
	lfs f1, 0x8c(r30)
	addi r4, r1, 0x20
	lfs f2, 0x90(r30)
	addi r5, r1, 0x1c
	fadds f1, f1, f28
	lfs f0, 0x94(r30)
	fadds f28, f2, f3
	lfs f4, float_0_80420e80(r2)
	fadds f3, f0, f5
	stfs f29, 0x8(r1)
	fmr f2, f28
	lfs f5, float_1_80420e94(r2)
	fmr f6, f4
	addi r6, r1, 0x18
	addi r7, r1, 0x8
	addi r8, r1, 0x14
	addi r9, r1, 0x10
	addi r10, r1, 0xc
	li r3, 0x0
	bl hitCheckFilter
	mr. r22, r3
	beq @19
	lfs f3, float_100_80420e98(r2)
	lis r0, 0x4330
	lfs f2, 0x1c(r1)
	lis r3, double_to_int_802fe368@ha
	lfs f1, float_0p5_80420e70(r2)
	fadds f0, f28, f29
	stw r0, 0x30(r1)
	fmadds f1, f3, f2, f1
	lfd f2, double_to_int_802fe368@l(r3)
	fctiwz f1, f1
	stfd f1, 0x38(r1)
	lwz r0, 0x3c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x34(r1)
	lfd f1, 0x30(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f3
	fcmpo cr0, f0, f1
	stfs f1, 0x1c(r1)
	cror eq, gt, eq
	bne @20
	stfs f1, 0x4(r23)
	mr r25, r22
	lfs f0, float_0_80420e80(r2)
	stfs f0, 0x0(r24)
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r29, 0x20
	stwx r22, r3, r0
	b @19
	@20:
	lfs f0, 0x4(r23)
	fsubs f0, f1, f0
	fsubs f0, f0, f29
	stfs f0, 0x0(r24)
	@19:
	addi r29, r29, 0x4
	addi r28, r28, 0x1
	@16:
	cmpw r28, r27
	blt @17
	mr r3, r25
	@2:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	psq_l f28, 0x78(r1), 0, 0
	lfd f28, 0x70(r1)
	lmw r22, 0x48(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

HitEntry* kpaSearchGround(f32 range, f32* outY, f32* outDepth, f32* outAng);
#pragma force_active on
__declspec(section ".data") static void* jumptable_803ADC44[] = {
    (char*)kpaSearchGround + 0x258,
    (char*)kpaSearchGround + 0x264,
    (char*)kpaSearchGround + 0x2A4,
    (char*)kpaSearchGround + 0x2E8,
    (char*)kpaSearchGround + 0x318,
    (char*)kpaSearchGround + 0x34C,
    (char*)kpaSearchGround + 0x37C,
};
asm HitEntry* kpaSearchGround(f32 range, f32* outY, f32* outDepth, f32* outAng) {
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
	stfd f17, 0xc0(r1)
	psq_st f17, 0xc8(r1), 0, 0
	stfd f16, 0xb0(r1)
	psq_st f16, 0xb8(r1), 0, 0
	stfd f15, 0xa0(r1)
	psq_st f15, 0xa8(r1), 0, 0
	stfd f14, 0x90(r1)
	psq_st f14, 0x98(r1), 0, 0
	stmw r19, 0x5c(r1)
	fmr f16, f1
	lis r6, vec3_802fe320@ha
	mr r20, r3
	mr r21, r4
	mr r22, r5
	addi r28, r6, vec3_802fe320@l
	bl marioGetPtr
	lfs f0, float_0_80420e80(r2)
	mr r29, r3
	li r23, 0x0
	stfs f0, 0x218(r3)
	stfs f0, 0x21c(r3)
	stfs f0, 0x220(r3)
	stfs f0, 0x214(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 22, 22
	beq @1
	lfs f0, 0x90(r29)
	li r3, 0x0
	stfs f0, 0x0(r20)
	b @2
	@1:
	lfs f0, float_0p01_80420e9c(r2)
	fadds f16, f16, f0
	bl kpaGetLevel
	cmpwi r3, 0x0
	bne @3
	lfs f15, 0x1b8(r29)
	b @4
	@3:
	lfs f1, float_0p25_80420ea0(r2)
	lfs f0, 0x1b8(r29)
	fmuls f15, f1, f0
	@4:
	lfs f0, 0x90(r29)
	lfs f1, float_neg1_80420e84(r2)
	stfs f0, 0x0(r20)
	lfs f0, float_0_80420e80(r2)
	stfs f1, 0x0(r21)
	lfs f1, 0x180(r29)
	fcmpu cr0, f1, f0
	beq @5
	lfs f14, 0x1a0(r29)
	b @6
	@5:
	lfs f1, 0x1a8(r29)
	bl toMovedir
	fmr f14, f1
	@6:
	li r24, 0x0
	lfs f22, 0x8c(r29)
	lfs f21, 0x90(r29)
	mr r19, r24
	lfs f20, 0x94(r29)
	li r26, 0x0
	lfs f17, float_1000_80420e74(r2)
	@7:
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r24, 0x4c
	stwx r19, r3, r0
	bl marioGetPtr
	addi r26, r26, 0x1
	lwz r3, 0x28c(r3)
	addi r0, r24, 0xa4
	addi r24, r24, 0x4
	cmpwi r26, 0xa
	stfsx f17, r3, r0
	blt @7
	bl kpaGetLevel
	cmpwi r3, 0x3
	beq @8
	bge @9
	cmpwi r3, 0x0
	bge @10
	b @9
	@10:
	lfd f1, 0x58(r28)
	li r25, 0x3
	lfs f0, 0x1b4(r29)
	lfd f2, 0x50(r28)
	fmul f0, f1, f0
	fmul f23, f2, f0
	frsp f23, f23
	b @9
	@8:
	lfs f2, float_0p5_80420e70(r2)
	li r25, 0x7
	lfs f1, 0x1b4(r29)
	lfs f0, float_3_80420ea8(r2)
	fmuls f1, f2, f1
	lfs f2, float_0p6_80420ea4(r2)
	fdivs f0, f1, f0
	fmuls f23, f2, f0
	@9:
	lfs f0, float_3p1416_80420e78(r2)
	li r26, 0x0
	lfs f2, float_2_80420e88(r2)
	fadds f25, f15, f16
	lfs f1, float_0p05_80420eac(r2)
	fmuls f28, f0, f14
	lfs f0, float_3_80420ea8(r2)
	fadds f24, f21, f15
	fmsubs f27, f2, f23, f1
	fmsubs f26, f0, f23, f1
	lfs f29, float_100_80420e98(r2)
	lfs f19, float_0p5_80420e70(r2)
	mr r19, r26
	lfd f14, 0x48(r28)
	mr r27, r26
	lis r30, 0x4330
	b @11
	@12:
	cmplwi r26, 0x6
	bgt @13
	lis r3, jumptable_803ADC44@ha
	addi r3, r3, jumptable_803ADC44@l
	lwzx r0, r3, r19
	mtctr r0
	bctr
	@14:
	lfs f31, float_0_80420e80(r2)
	fmr f30, f31
	b @13
	@15:
	lfs f0, float_180_80420e7c(r2)
	fdivs f15, f28, f0
	fmr f1, f15
	bl sin
	lfs f0, float_0p05_80420eac(r2)
	frsp f2, f1
	fmr f1, f15
	fsubs f0, f23, f0
	fmuls f31, f0, f2
	bl cos
	frsp f2, f1
	lfs f0, float_0p05_80420eac(r2)
	fsubs f1, f23, f0
	fneg f0, f2
	fmuls f30, f1, f0
	b @13
	@16:
	lfs f0, float_180_80420e7c(r2)
	fdivs f15, f28, f0
	fmr f1, f15
	bl sin
	frsp f3, f1
	lfs f0, float_0p05_80420eac(r2)
	fmr f1, f15
	fsubs f2, f23, f0
	fneg f0, f3
	fmuls f31, f2, f0
	bl cos
	frsp f2, f1
	lfs f0, float_0p05_80420eac(r2)
	fsubs f1, f23, f0
	fneg f0, f2
	fmuls f30, f1, f0
	b @13
	@17:
	lfs f0, float_180_80420e7c(r2)
	fdivs f15, f28, f0
	fmr f1, f15
	bl sin
	frsp f0, f1
	fmr f1, f15
	fmuls f31, f27, f0
	bl cos
	frsp f0, f1
	fneg f0, f0
	fmuls f30, f27, f0
	b @13
	@18:
	lfs f0, float_180_80420e7c(r2)
	fdivs f15, f28, f0
	fmr f1, f15
	bl sin
	frsp f0, f1
	fmr f1, f15
	fneg f0, f0
	fmuls f31, f27, f0
	bl cos
	frsp f0, f1
	fneg f0, f0
	fmuls f30, f27, f0
	b @13
	@19:
	lfs f0, float_180_80420e7c(r2)
	fdivs f15, f28, f0
	fmr f1, f15
	bl sin
	frsp f0, f1
	fmr f1, f15
	fmuls f31, f26, f0
	bl cos
	frsp f0, f1
	fneg f0, f0
	fmuls f30, f26, f0
	b @13
	@20:
	lfs f0, float_180_80420e7c(r2)
	fdivs f15, f28, f0
	fmr f1, f15
	bl sin
	frsp f0, f1
	fmr f1, f15
	fneg f0, f0
	fmuls f31, f26, f0
	bl cos
	frsp f0, f1
	fneg f0, f0
	fmuls f30, f26, f0
	@13:
	lfs f4, float_0_80420e80(r2)
	fmr f2, f24
	fadds f1, f22, f31
	stfs f25, 0x1c(r1)
	fmr f6, f4
	lfs f5, float_neg1_80420e84(r2)
	fadds f3, f20, f30
	addi r4, r1, 0x28
	addi r5, r1, 0x24
	addi r6, r1, 0x20
	addi r7, r1, 0x1c
	addi r8, r1, 0x18
	addi r9, r1, 0x14
	addi r10, r1, 0x10
	li r3, 0x0
	bl hitCheckFilter
	mr. r24, r3
	beq @21
	lfs f16, 0x10(r1)
	lfs f17, 0x14(r1)
	lfs f18, 0x18(r1)
	bl marioGetPtr
	lfs f0, float_100_80420e98(r2)
	mr r31, r3
	lfs f1, float_0_80420e80(r2)
	fmuls f15, f0, f17
	fmr f2, f1
	fmuls f3, f0, f16
	fmr f4, f15
	bl angleABf
	lfs f0, float_180_80420e7c(r2)
	lis r0, 0x4330
	stw r0, 0x38(r1)
	fmr f4, f15
	fsubs f3, f1, f0
	lfs f2, float_0_80420e80(r2)
	lfs f0, float_100_80420e98(r2)
	lfd f5, 0x48(r28)
	fmr f1, f2
	fctiwz f6, f3
	fmuls f3, f0, f18
	stfd f6, 0x30(r1)
	lwz r0, 0x34(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x3c(r1)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f5
	stfs f0, 0x218(r31)
	stfs f2, 0x21c(r31)
	bl angleABf
	lfs f0, float_180_80420e7c(r2)
	lis r0, 0x4330
	fmuls f2, f16, f16
	stw r0, 0x48(r1)
	fsubs f4, f1, f0
	lfd f1, 0x48(r28)
	lfs f0, float_0_80420e80(r2)
	fmadds f3, f18, f18, f2
	fctiwz f2, f4
	fcmpo cr0, f3, f0
	stfd f2, 0x40(r1)
	lwz r0, 0x44(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x4c(r1)
	lfd f0, 0x48(r1)
	fsubs f0, f0, f1
	stfs f0, 0x220(r31)
	ble @22
	frsqrte f1, f3
	lfd f4, 0x58(r28)
	lfd f2, 0x60(r28)
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
	b @23
	@22:
	lfd f0, 0x68(r28)
	fcmpo cr0, f3, f0
	bge @24
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @23
	@24:
	stfs f3, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @25
	bge @26
	cmpwi r3, 0x0
	beq @27
	b @26
	@25:
	clrlwi. r0, r4, 9
	beq @28
	li r0, 0x1
	b @29
	@28:
	li r0, 0x2
	b @29
	@27:
	clrlwi. r0, r4, 9
	beq @30
	li r0, 0x5
	b @29
	@30:
	li r0, 0x3
	b @29
	@26:
	li r0, 0x4
	@29:
	cmpwi r0, 0x1
	bne @23
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@23:
	lfs f1, float_0_80420e80(r2)
	fneg f4, f17
	fmr f2, f1
	bl angleABf
	lfs f0, float_50_80420eb0(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @21
	li r24, 0x0
	@21:
	lfs f0, 0x24(r1)
	cmplwi r24, 0x0
	stw r30, 0x40(r1)
	fmadds f0, f29, f0, f19
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f14
	fdivs f0, f0, f29
	stfs f0, 0x24(r1)
	beq @31
	lfs f18, 0x10(r1)
	lfs f17, 0x14(r1)
	lfs f16, 0x18(r1)
	bl marioGetPtr
	lfs f0, float_100_80420e98(r2)
	mr r31, r3
	lfs f1, float_0_80420e80(r2)
	fmuls f15, f0, f17
	fmr f2, f1
	fmuls f3, f0, f18
	fmr f4, f15
	bl angleABf
	lfs f0, float_180_80420e7c(r2)
	lis r0, 0x4330
	stw r0, 0x40(r1)
	fmr f4, f15
	fsubs f3, f1, f0
	lfs f2, float_0_80420e80(r2)
	lfs f0, float_100_80420e98(r2)
	lfd f5, 0x48(r28)
	fmr f1, f2
	fctiwz f6, f3
	fmuls f3, f0, f16
	stfd f6, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f5
	stfs f0, 0x218(r31)
	stfs f2, 0x21c(r31)
	bl angleABf
	lfs f0, float_180_80420e7c(r2)
	lis r0, 0x4330
	fmuls f2, f18, f18
	stw r0, 0x30(r1)
	fsubs f4, f1, f0
	lfd f1, 0x48(r28)
	lfs f0, float_0_80420e80(r2)
	fmadds f3, f16, f16, f2
	fctiwz f2, f4
	fcmpo cr0, f3, f0
	stfd f2, 0x38(r1)
	lwz r0, 0x3c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x34(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f1
	stfs f0, 0x220(r31)
	ble @32
	frsqrte f1, f3
	lfd f4, 0x58(r28)
	lfd f2, 0x60(r28)
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
	b @33
	@32:
	lfd f0, 0x68(r28)
	fcmpo cr0, f3, f0
	bge @34
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b @33
	@34:
	stfs f3, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @35
	bge @36
	cmpwi r3, 0x0
	beq @37
	b @36
	@35:
	clrlwi. r0, r4, 9
	beq @38
	li r0, 0x1
	b @39
	@38:
	li r0, 0x2
	b @39
	@37:
	clrlwi. r0, r4, 9
	beq @40
	li r0, 0x5
	b @39
	@40:
	li r0, 0x3
	b @39
	@36:
	li r0, 0x4
	@39:
	cmpwi r0, 0x1
	bne @33
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	@33:
	lfs f1, float_0_80420e80(r2)
	fneg f4, f17
	fmr f2, f1
	bl angleABf
	stfs f1, 0x214(r29)
	lfs f2, 0x24(r1)
	fcmpo cr0, f2, f21
	bge @41
	fsubs f1, f2, f21
	lfs f0, float_2_80420e88(r2)
	fabs f1, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @41
	fsubs f0, f21, f2
	fmr f1, f22
	fmr f2, f20
	stfs f0, 0x0(r21)
	lfs f3, 0x28(r1)
	lfs f4, 0x20(r1)
	bl angleABf
	stfs f1, 0x0(r22)
	li r24, 0x0
	b @31
	@41:
	lfs f0, 0x18(r1)
	lfs f1, float_0_80420e80(r2)
	fcmpu cr0, f0, f1
	bne @42
	lfs f0, 0x10(r1)
	fcmpu cr0, f0, f1
	bne @42
	lfs f2, float_100_80420e98(r2)
	lis r0, 0x4330
	lfs f1, 0x24(r1)
	lfs f0, float_0p5_80420e70(r2)
	stw r0, 0x40(r1)
	fmadds f0, f2, f1, f0
	lfd f1, 0x48(r28)
	fctiwz f0, f0
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f1
	fdivs f0, f0, f2
	stfs f0, 0x24(r1)
	@42:
	lfs f3, 0x24(r1)
	fmr f1, f22
	lfs f0, float_0_80420e80(r2)
	fmr f2, f20
	stfs f3, 0x0(r20)
	stfs f0, 0x0(r21)
	lfs f3, 0x28(r1)
	lfs f4, 0x20(r1)
	bl angleABf
	stfs f1, 0x0(r22)
	mr r23, r24
	@31:
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r27, 0x4c
	stwx r24, r3, r0
	bl marioGetPtr
	lwz r3, 0x28c(r3)
	addi r0, r27, 0xa4
	addi r19, r19, 0x4
	addi r27, r27, 0x4
	stfsx f31, r3, r0
	addi r26, r26, 0x1
	@11:
	cmpw r26, r25
	blt @12
	mr r3, r23
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
	psq_l f17, 0xc8(r1), 0, 0
	lfd f17, 0xc0(r1)
	psq_l f16, 0xb8(r1), 0, 0
	lfd f16, 0xb0(r1)
	psq_l f15, 0xa8(r1), 0, 0
	lfd f15, 0xa0(r1)
	psq_l f14, 0x98(r1), 0, 0
	lfd f14, 0x90(r1)
	lmw r19, 0x5c(r1)
	lwz r0, 0x1b4(r1)
	mtlr r0
	addi r1, r1, 0x1b0
	blr
}

asm s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
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
	stfd f28, 0x20(r1)
	psq_st f28, 0x28(r1), 0, 0
	stfd f27, 0x10(r1)
	psq_st f27, 0x18(r1), 0, 0
	stw r31, 0xc(r1)
	fmr f27, f1
	fmr f30, f2
	fmr f31, f3
	fmr f28, f4
	fmr f29, f5
	bl marioGetPtr
	fmr f1, f27
	mr r31, r3
	fmr f2, f30
	fmr f3, f31
	fmr f4, f28
	fmr f5, f29
	bl kpaEnemyFireHitChk
	cmpwi r3, 0x0
	beq @1
	li r3, 0x2
	b @2
	@1:
	lfs f0, 0x1b8(r31)
	lfs f5, float_0p5_80420e70(r2)
	fadds f4, f0, f28
	lfs f1, 0x90(r31)
	lfs f3, 0x1b4(r31)
	fmadds f0, f5, f0, f1
	lfs f2, 0x8c(r31)
	fadds f3, f3, f29
	fsubs f2, f2, f27
	fsubs f0, f0, f30
	fmuls f4, f5, f4
	fmuls f3, f5, f3
	fnmsubs f0, f5, f28, f0
	fabs f2, f2
	fabs f0, f0
	fcmpo cr0, f0, f4
	cror eq, lt, eq
	bne @3
	fcmpo cr0, f2, f3
	cror eq, lt, eq
	bne @3
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 14
	beq @4
	fcmpo cr0, f1, f30
	ble @4
	bl kpaGetLevel
	cmpwi r3, 0x0
	bne @5
	bl kpaGetStageType
	cmpwi r3, 0x1
	beq @5
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bne @5
	lfs f0, float_50_80420eb0(r2)
	fcmpo cr0, f31, f0
	bge @5
	li r3, 0x4
	bl marioChgMot
	@5:
	li r3, 0x1
	b @2
	@4:
	bl kpaMutekiCheck
	cmpwi r3, 0x1
	bne @6
	li r3, 0x3
	b @2
	@6:
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	beq @7
	li r3, 0x3
	b @2
	@7:
	lha r0, 0x78(r31)
	cmpwi r0, 0x0
	bne @3
	li r3, 0x4
	b @2
	@3:
	li r3, 0x0
	@2:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	psq_l f28, 0x28(r1), 0, 0
	lfd f28, 0x20(r1)
	psq_l f27, 0x18(r1), 0, 0
	lfd f27, 0x10(r1)
	lwz r0, 0x64(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}
// clang-format on
#endif

#ifdef NONMATCHING
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
    a.y = EXT_LIT(float_0p5_80420e70, 0.5f) * h + y;
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
    half = kpaHalf(w);
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
#else
// FAKE: whole-function asm stopgap (asm-stopgap pipeline; target inlines kpaHalf)
asm s32 kpaEnemyFireHitChk(f32 x, f32 y, f32 z, f32 h, f32 w) {
    nofralloc
    stwu r1, -0x170(r1)
    mflr r0
    stw r0, 0x174(r1)
    stfd f31, 0x160(r1)
    psq_st f31, 0x168(r1), 0, 0
    stfd f30, 0x150(r1)
    psq_st f30, 0x158(r1), 0, 0
    stfd f29, 0x140(r1)
    psq_st f29, 0x148(r1), 0, 0
    stfd f28, 0x130(r1)
    psq_st f28, 0x138(r1), 0, 0
    stfd f27, 0x120(r1)
    psq_st f27, 0x128(r1), 0, 0
    stw r31, 0x11c(r1)
    stw r30, 0x118(r1)
    stw r29, 0x114(r1)
    fmr f27, f1
    fmr f28, f2
    fmr f31, f3
    fmr f29, f4
    fmr f30, f5
    bl getKoopaFireEfp
    mr r31, r3
    li r3, 0x4
    bl camGetPtr
    lis r3, vec3_802fe320@ha
    lfs f0, float_0p5_80420e70(r2)
    addi r5, r3, vec3_802fe320@l
    cmplwi r31, 0x0
    lwz r4, 0x0(r5)
    fmadds f0, f0, f29, f28
    lwz r3, 0x4(r5)
    lwz r0, 0x8(r5)
    stw r4, 0x14(r1)
    stw r3, 0x18(r1)
    stw r0, 0x1c(r1)
    stfs f27, 0x14(r1)
    stfs f0, 0x18(r1)
    lwz r4, 0x14(r1)
    stfs f31, 0x1c(r1)
    lwz r3, 0x18(r1)
    lwz r0, 0x1c(r1)
    stw r4, 0x2c(r1)
    stw r3, 0x30(r1)
    stw r0, 0x34(r1)
    bne L_80215E18
    li r3, 0x0
    b L_80215FAC
L_80215E18:
    lwz r30, 0xc(r31)
    addi r3, r1, 0xa4
    lfs f29, 0x40(r30)
    lfs f1, 0x4(r30)
    lfs f2, 0x8(r30)
    lfs f3, 0xc(r30)
    bl PSMTXTrans
    li r3, 0x4
    bl camGetPtr
    lfs f2, 0x114(r3)
    addi r3, r1, 0x74
    lfs f1, 0x48(r30)
    li r4, 0x79
    lfs f0, float_deg2rad_80420eb4(r2)
    fsubs f1, f1, f2
    fmuls f1, f0, f1
    bl PSMTXRotRad
    lfs f1, 0x48(r30)
    lfs f0, float_90_80420eb8(r2)
    fcmpo cr0, f1, f0
    ble L_80215E90
    lfs f0, float_270_80420ebc(r2)
    fcmpo cr0, f1, f0
    bge L_80215E90
    lfs f1, 0x40(r30)
    addi r3, r1, 0xd4
    fmr f2, f1
    fneg f3, f1
    bl PSMTXScale
    b L_80215EA4
L_80215E90:
    lfs f1, 0x40(r30)
    addi r3, r1, 0xd4
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
L_80215EA4:
    addi r3, r1, 0xa4
    addi r4, r1, 0x74
    mr r5, r3
    bl PSMTXConcat
    addi r3, r1, 0xa4
    addi r4, r1, 0xd4
    addi r5, r1, 0x44
    bl PSMTXConcat
    lfs f0, float_0p5_80420e70(r2)
    li r29, 0x1
    addi r30, r30, 0x50
    fmuls f31, f0, f30
    b L_80215F9C
L_80215ED8:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x0
    bne L_80215F94
    lfs f2, float_7_80420ec0(r2)
    addi r3, r1, 0xa4
    lfs f0, 0x40(r30)
    lfs f1, 0x4(r30)
    fmuls f30, f2, f0
    lfs f2, 0x8(r30)
    lfs f3, 0xc(r30)
    bl PSMTXTrans
    fmr f1, f30
    addi r3, r1, 0xd4
    fmr f2, f30
    fmr f3, f30
    bl PSMTXScale
    addi r3, r1, 0xa4
    addi r4, r1, 0xd4
    mr r5, r3
    bl PSMTXConcat
    addi r4, r1, 0xa4
    addi r3, r1, 0x44
    mr r5, r4
    bl PSMTXConcat
    lis r4, vec3_802fe32c@ha
    addi r3, r1, 0xa4
    addi r8, r4, vec3_802fe32c@l
    addi r4, r1, 0x8
    lwz r7, 0x0(r8)
    addi r5, r1, 0x38
    lwz r6, 0x4(r8)
    lwz r0, 0x8(r8)
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl PSMTXMultVec
    addi r3, r1, 0x2c
    addi r4, r1, 0x38
    addi r5, r1, 0x20
    bl PSVECSubtract
    addi r3, r1, 0x20
    bl PSVECMag
    fmadds f0, f30, f29, f31
    fcmpo cr0, f1, f0
    bge L_80215F94
    li r3, 0x1
    b L_80215FAC
L_80215F94:
    addi r29, r29, 0x1
    addi r30, r30, 0x50
L_80215F9C:
    lwz r0, 0x8(r31)
    cmpw r29, r0
    blt L_80215ED8
    li r3, 0x0
L_80215FAC:
    psq_l f31, 0x168(r1), 0, 0
    lfd f31, 0x160(r1)
    psq_l f30, 0x158(r1), 0, 0
    lfd f30, 0x150(r1)
    psq_l f29, 0x148(r1), 0, 0
    lfd f29, 0x140(r1)
    psq_l f28, 0x138(r1), 0, 0
    lfd f28, 0x130(r1)
    psq_l f27, 0x128(r1), 0, 0
    lfd f27, 0x120(r1)
    lwz r31, 0x11c(r1)
    lwz r30, 0x118(r1)
    lwz r0, 0x174(r1)
    lwz r29, 0x114(r1)
    mtlr r0
    addi r1, r1, 0x170
    blr
}
#endif
